/* Full movie/archive dispatch and retry bodies. Data structures use original
 * byte names,12-byte DDS3 entries and GP-relative globals. */
#include "movie_archive.h"
#include "libc_printf.h"
#include "libc_stream.h"
#include "cd_stream.h"
#include "cd_services.h"
#include "file_operations.h"
#include "disc_platform.h"
#include "ps2_memory.h"
#include "ps2_sdk_frontier.h"
#include "ps2_sdk_helpers.h"
#include "heap_queue.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMovieArchiveAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v>>31)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
static uint32_t local(void *p,uint32_t n){
#if UINTPTR_MAX > UINT32_MAX
    return nocturneLibcStreamLocalAddress(p,n);
#else
    (void)n;return (uint32_t)(uintptr_t)p;
#endif
}
static void endLocal(void){
#if UINTPTR_MAX > UINT32_MAX
    nocturneLibcStreamEndLocal();
#endif
}
/* SignalSema's native stub leaves the full kernel V0 live. The movie seek
 * caller returns it; the older uint32_t convenience API narrows that value. */
static uint64_t signalRaw(uint32_t id){uint64_t arg=sx(id);return nocturneDiscPlatformKernel(0x42,1,&arg);}
_Noreturn void ps2FatalSpin(uint64_t format,...)
{
    (void)format;
    /* 002a82b0 saves private argument words then loops in NOPs. No printf,
     * error return or recovery branch exists in the original body. */
    for(;;){}
}
uint64_t ps2MovieWaitForDisc(void)
{
    uint8_t record[48];uint32_t p=local(record,sizeof(record));
    (void)ps2LibcPrintf(0x5495d8);
    (void)ps2KernelWaitSema(word(0x552108));
    for(;;){
        (void)ps2FileDelay(100);(void)ps2CdDiskReady(0);
        (void)ps2LibcPrintf(0x5495f0);
        uint64_t type=ps2CdGetDiskType();
        if(type!=(word(0x551918)==2?20u:18u))continue;
        if(ps2CdSearchFile(p,sx(word(0x5520e8))))break;
    }
    (void)ps2KernelSignalSema(word(0x552108));
    uint64_t result=ps2LibcPrintf(0x549600);endLocal();return result;
}
uint64_t ps2MovieStreamSeek(uint64_t sector)
{
    uint8_t mode[4]={0,(uint8_t)(*at(0x552110)!=1),0,0};uint32_t p=local(mode,4);
    uint64_t result;
    for(;;){
        (void)ps2KernelWaitSema(word(0x552108));
        uint64_t started=ps2CdStreamStart(sector,p);
        result=signalRaw(word(0x552108));
        if(started)break;
        if(ps2CdGetError()==1)ps2MovieWaitForDisc();else (void)ps2FileDelay(100);
    }
    put(0x55210c,(uint32_t)sector);endLocal();return result;
}
uint64_t ps2MovieStreamRead(uint64_t sectors,uint64_t output)
{
    uint32_t error[4],p=local(error,sizeof(error));
    for(;;){
        (void)ps2KernelWaitSema(word(0x552108));
        uint64_t read=ps2CdStreamRead(sectors,output,1,p);
        (void)ps2KernelSignalSema(word(0x552108));
        if(!error[0]&&read==sectors)break;
        if(ps2CdGetError()==1)ps2MovieWaitForDisc();
        else{
            (void)ps2LibcPrintf(0x549618);
            (void)ps2KernelWaitSema(word(0x552108));
            (void)ps2CdStreamStop();(void)ps2KernelSignalSema(word(0x552108));
        }
        (void)ps2MovieStreamSeek(sx(word(0x55210c)));
    }
    uint32_t result=word(0x55210c)+(uint32_t)sectors;
    put(0x55210c,result);endLocal();return sx(result);
}
uint64_t ps2MovieLookupDiscFile(uint64_t path,uint64_t sector,uint64_t direct)
{
    uint8_t scratch[0x130];uint32_t frame=local(scratch,sizeof(scratch)),name=frame+48;
    ps2Strcpy((char *)at(name),(const char *)at((uint32_t)path));
    const uint8_t *start=at(name),*found=(const uint8_t *)ps2Strchr((const char *)start,':');
    uint32_t cursor=found?name+(uint32_t)(found-start)+1:1;
    uint32_t end=cursor;
    while(*at(end)){
        uint8_t c=*at(end);
        if(c=='/')*at(end)='\\';else if((uint32_t)((int8_t)c-'a')<26)*at(end)=(uint8_t)(c-32);
        end++;
    }
    if((int8_t)*at(end-2)!=';'){*at(end)=';';*at(end+1)='1';*at(end+2)=0;}
    uint64_t result=0;
    for(;;){
        (void)ps2KernelWaitSema(word(0x552108));
        if(!ps2CdSearchFile(frame,cursor)){
            uint64_t error=ps2CdGetError();(void)ps2KernelSignalSema(word(0x552108));
            if(error!=1)break;
            ps2MovieWaitForDisc();continue;
        }
        uint64_t descriptor=ps2FileRpcOpen(name,1,nocturneMovieArchiveOpenMode());
        if(descriptor>>63){(void)ps2KernelSignalSema(word(0x552108));continue;}
        uint64_t bytes=ps2FileRpcSeek(descriptor,0,2);put(0x58f788,(uint32_t)bytes);
        (void)ps2FileRpcClose(descriptor);(void)ps2KernelSignalSema(word(0x552108));
        put((uint32_t)sector,word(frame));if(direct)*at((uint32_t)direct)=1;
        result=0x58f780;break;
    }
    endLocal();return result;
}
uint64_t ps2MovieLookupArchiveFile(uint64_t path,uint64_t sector,uint64_t direct)
{
    uint32_t input=(uint32_t)path;
    if(ps2Memcmp(at(input),at(0x551910),5)==0)return ps2MovieLookupDiscFile(path,sx((uint32_t)sector),direct);
    uint32_t base=word(0x5520f4),record=base,cursor=input;
    char component[32];
    for(;;){
        if((int8_t)*at(cursor)=='/')cursor++;
        uint32_t start=cursor;
        while(*at(cursor)&&*at(cursor)!='/')cursor++;
        uint32_t length=cursor-start;
        if(length>31)ps2FatalSpin(0x549628,path);
        ps2Memcpy(component,at(start),length);component[length]=0;
        uint32_t list=base+word(record+4);int32_t low=0,high=s32(0-word(record+8));
        for(;;){
            if(high<=low)return 0;
            int32_t middle=s32((uint32_t)low+(uint32_t)high)>>1;
            record=list+(uint32_t)middle*12;
            int32_t order=ps2Strcmp(component,(const char *)at(base+word(record)));
            if(!order)break;
            if(order<0)high=middle;else low=middle+1;
        }
        if(!*at(cursor)){
            put((uint32_t)sector,word(0x5520f0)+word(record+4));
            if(direct)*at((uint32_t)direct)=0;
            return sx(record);
        }
    }
}


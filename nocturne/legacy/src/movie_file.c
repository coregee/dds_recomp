/* Movie file frontends: actual archive lookup, stream I/O and native cache. */
#include "movie_file.h"
#include "movie_archive.h"
#include "disc_platform.h"
#include "cd_stream.h"
#include "heap_queue.h"
#include "libc_stream.h"
#include "ps2_memory.h"
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
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int positive(uint64_t v){return v&&!(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint64_t signal(uint32_t sem){uint64_t a=sx(sem);return nocturneDiscPlatformKernel(0x42,1,&a);}
uint64_t ps2MovieFileOpen(uint64_t path)
{
    uint32_t sector;
#if UINTPTR_MAX > UINT32_MAX
    uint32_t scratch=nocturneLibcStreamLocalAddress(&sector,4);
#else
    uint32_t scratch=(uint32_t)(uintptr_t)&sector;
#endif
    uint64_t record=ps2MovieLookupArchiveFile(path,scratch,0x552110);
#if UINTPTR_MAX > UINT32_MAX
    nocturneLibcStreamEndLocal();
#endif
    if(!record)return UINT64_MAX;
    put(0x5520fc,word((uint32_t)record+8));put(0x5520f8,(uint32_t)record);put(0x552104,0);
    (void)ps2MovieStreamSeek(sx(sector));return sx(word((uint32_t)record+8));
}
uint64_t ps2MovieFileClose(void)
{
    if(!word(0x5520f8))return 0;
    (void)ps2KernelWaitSema(word(0x552108));(void)ps2CdStreamStop();
    uint64_t result=signal(word(0x552108));put(0x5520f8,0);return result;
}
uint64_t ps2MovieFileSize(void)
{
    uint32_t record=word(0x5520f8);
    if(!record)ps2FatalSpin(0x549640);
    return sx(word(record+8));
}
/* The unaligned sector copy loads all four doublewords before any stores.
 * Preserve that behavior for overlapping scratch/output ranges. */
static void sectorCopy(uint32_t output,uint32_t input)
{
    for(uint32_t k=0;k<2048;k+=32){
        uint64_t words[4];for(unsigned j=0;j<4;j++)memcpy(words+j,at(input+k+j*8),8);
        for(unsigned j=0;j<4;j++)memcpy(at(output+k+j*8),words+j,8);
    }
}
uint64_t ps2MovieFileRead(uint64_t output,uint64_t bytes)
{
    uint64_t remaining=sx(word(0x5520fc));if(!positive(remaining))return 0;
    if(less(remaining,bytes))bytes=remaining;
    if(!bytes)return 0;
    uint32_t destination=(uint32_t)output,request=(uint32_t)bytes,left=request;
    uint64_t cached=sx(word(0x552104));
    if(positive(cached)){
        if(less(bytes,cached))cached=bytes;
        uint32_t n=(uint32_t)cached;ps2Memcpy(at(destination),at(word(0x552100)),n);
        destination+=n;left=request-n;put(0x552100,word(0x552100)+n);put(0x552104,word(0x552104)-n);
    }
    if(positive(sx(left))){
        if(!(destination&15)){
            uint32_t tail=left&2047,aligned=left-tail;
            if(positive(sx(aligned)))(void)ps2MovieStreamRead(sx(aligned>>11),sx(destination));
            if(positive(sx(tail))){
                (void)ps2MovieStreamRead(1,0x58f7c0);ps2Memcpy(at(destination+aligned),at(0x58f7c0),tail);
                put(0x552100,0x58f7c0+tail);put(0x552104,2048-tail);
            }
        }else{
            while((int32_t)left>=2048){
                (void)ps2MovieStreamRead(1,0x58f7c0);sectorCopy(destination,0x58f7c0);destination+=2048;left-=2048;
            }
            if(positive(sx(left))){
                (void)ps2MovieStreamRead(1,0x58f7c0);ps2Memcpy(at(destination),at(0x58f7c0),left);
                put(0x552100,0x58f7c0+left);put(0x552104,2048-left);
            }
        }
    }
    uint32_t rest=(uint32_t)remaining-request;put(0x5520fc,rest);
    if(!rest)(void)ps2MovieFileClose();
    return bytes;
}

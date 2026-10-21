#include "heap_queue.h"
#include "material_fiveword_pool.h"
#include "array_lists.h"
#include <string.h>
#define ROOT UINT32_C(0x52be30)
#define REM (ROOT+8)
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveHeapAddress(a),4);return v;}
static uint64_t r64(uint32_t a){uint64_t v;memcpy(&v,nocturneResolveHeapAddress(a),8);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(nocturneResolveHeapAddress(a),&v,4);}
static void w64(uint32_t a,uint64_t v){memcpy(nocturneResolveHeapAddress(a),&v,8);}
static void w16(uint32_t a,uint16_t v){memcpy(nocturneResolveHeapAddress(a),&v,2);}
static int32_t signed32(uint32_t v){return (int32_t)((int64_t)v-((v>>31)?INT64_C(4294967296):0));}
static int64_t signed64(uint64_t v){return v>>63?-1-(int64_t)~v:(int64_t)v;}
static uint64_t sx32(uint32_t v){return (uint64_t)(int64_t)signed32(v);}
static int64_t difference(uint32_t a,uint32_t b){return a<b?-(int64_t)(uint32_t)(b-a):(int64_t)(uint32_t)(a-b);}
static uint32_t binIndex(uint32_t size)
{
    uint32_t n=size>>9;
    if(!n)return size>>3;
    if(n<5)return (size>>6)+56;
    if(n<=20)return n+91;
    if(n<85)return (size>>12)+110;
    if(n<341)return (size>>15)+119;
    if(n<1365)return (size>>18)+124;
    return 126;
}
static void unlinkChunk(uint32_t chunk)
{uint32_t back=r32(chunk+12),forward=r32(chunk+8);w32(forward+12,back);w32(back+8,forward);}
/* Shared insertion sequence in the two original bodies. Retains the actual
 * forward traversal, live reads, and store order instead of a host container. */
static void insertChunk(uint32_t chunk,uint32_t size)
{
    uint32_t index=binIndex(size),back=ROOT+index*8,forward;
    if(size<512){
        uint32_t bitmap=r32(ROOT+4);forward=r32(back+8);
        w32(chunk+12,back);w32(chunk+8,forward);
        w32(ROOT+4,bitmap|(uint32_t)(UINT64_C(1)<<((index>>2)&63)));
    }else{
        forward=r32(back+8);
        if(forward==back){
            /* MOVN's signed-index correction exists in the original code;
             * binIndex is nonnegative over all raw32 extents. */
            uint32_t shift=(uint32_t)(signed32(index)/4);
            w32(ROOT+4,r32(ROOT+4)|(uint32_t)(UINT64_C(1)<<(shift&63)));
        }else{
            while(size<(r32(forward+4)&~UINT32_C(3))){
                forward=r32(forward+8);
                if(forward==back)break;
            }
            back=r32(forward+12);
        }
        w32(chunk+12,back);w32(chunk+8,forward);
    }
    w32(back+8,chunk);w32(forward+12,chunk);
}
static void splitRemainder(uint32_t chunk,uint32_t size,uint32_t delta)
{
    uint32_t remainder=chunk+size;
    w32(chunk+4,size|1);w32(REM+12,remainder);w32(REM+8,remainder);
    w32(remainder+4,delta|1);w32(remainder+8,REM);
    w32(remainder+delta,delta);w32(remainder+12,REM);
}
uint32_t ps2KernelGetThreadId(void){return nocturneHeapKernelValue(0x2f,0);}
uint32_t ps2KernelEndOfHeap(void){return nocturneHeapKernelValue(0x3e,0);}
uint32_t ps2KernelWaitSema(uint32_t id){return nocturneHeapKernelValue(0x44,id);}
uint32_t ps2KernelSignalSema(uint32_t id){return nocturneHeapKernelValue(0x42,id);}
uint32_t ps2KernelCreateSema(const void *parameters){return nocturneHeapKernelCreateValue(parameters);}
void ps2HeapLock(void)
{
    uint32_t thread=ps2KernelGetThreadId();
    if(r32(0x52c288)!=thread){ps2KernelWaitSema(r32(0x52c378));w32(0x52c288,thread);}
    w32(0x52c28c,r32(0x52c28c)+1);
}
void ps2HeapUnlock(void)
{
    uint32_t depth=r32(0x52c28c)-1;w32(0x52c28c,depth);
    if(!depth){uint32_t sem=r32(0x52c378);w32(0x52c288,UINT32_MAX);(void)ps2KernelSignalSema(sem);}
}
uint32_t ps2HeapSbrk(uint32_t increment)
{
    uint32_t enabled=EE_SYSTEM_READ_STATUS()&0x10000;
    if(enabled){do{EE_SYSTEM_DI();EE_SYSTEM_SYNC(16);}while(EE_SYSTEM_READ_STATUS()&0x10000);}
    uint32_t next=r32(0x52c2a8)+increment;
    uint32_t limit=ps2KernelEndOfHeap();
    uint32_t previous=r32(0x52c2a8);
    if(limit<next){w32(nocturneHeapRuntimeStateRaw(),12);if(enabled)EE_SYSTEM_EI();return UINT32_MAX;}
    w32(0x52c2a8,next);if(enabled)EE_SYSTEM_EI();return previous;
}
uint32_t ps2HeapSbrkReentrant(uint32_t context,uint32_t increment)
{
    w32(0x552178,0);uint32_t result=ps2HeapSbrk(increment);
    if(result==UINT32_MAX){uint32_t error=r32(0x552178);if(error)w32(context,error);}
    return result;
}
uint32_t ps2HeapTrim(uint32_t context,uint32_t pad)
{
    ps2HeapLock();uint32_t size=r32(r32(ROOT+8)+4)&~UINT32_C(3);
    uint64_t amount=((((uint64_t)size-pad+UINT64_C(0xfef))>>12)-1)<<12;
    if(signed64(amount)<4096){ps2HeapUnlock();return 0;}
    uint32_t current=ps2HeapSbrkReentrant(context,0);
    if(current!=r32(ROOT+8)+size){ps2HeapUnlock();return 0;}
    uint32_t result=ps2HeapSbrkReentrant(context,0-(uint32_t)amount);
    if(result!=UINT32_MAX){
        w32(r32(ROOT+8)+4,(size-(uint32_t)amount)|1);
        w32(0x52c260,r32(0x52c260)-(uint32_t)amount);ps2HeapUnlock();return 1;
    }
    current=ps2HeapSbrkReentrant(context,0);
    uint32_t top=r32(ROOT+8),recovered=current-top;
    if(signed32(recovered)>=16){w32(0x52c260,current-r32(0x52c248));w32(top+4,recovered|1);}
    ps2HeapUnlock();return 0;
}
void ps2HeapFree(uint32_t context,uint32_t payload)
{
    if(!payload)return;
    ps2HeapLock();uint32_t chunk=payload-8,flags=r32(chunk+4),extent=flags&~UINT32_C(1);
    uint32_t next=chunk+extent,top=r32(ROOT+8),nextSize=r32(next+4)&~UINT32_C(3);
    if(next==top){
        extent+=nextSize;
        if(!(flags&1)){uint32_t previous=r32(chunk);chunk-=previous;extent+=previous;unlinkChunk(chunk);}
        w32(ROOT+8,chunk);w32(chunk+4,extent|1);
        if((uint64_t)extent>=r64(0x52c238))(void)ps2HeapTrim(context,r32(0x52c240));
        ps2HeapUnlock();return;
    }
    w32(next+4,nextSize);uint32_t isRemainder=0;
    if(!(flags&1)){
        uint32_t previous=r32(chunk);chunk-=previous;extent+=previous;
        uint32_t forward=r32(chunk+8);
        if(forward==REM)isRemainder=1;
        else{uint32_t back=r32(chunk+12);w32(forward+12,back);w32(back+8,forward);}
    }
    if(!(r32(next+nextSize+4)&1)){
        extent+=nextSize;
        uint32_t forward=r32(next+8);
        if(!isRemainder&&forward==REM){
            w32(forward+12,chunk);isRemainder=1;w32(forward+8,chunk);
            w32(chunk+8,forward);w32(chunk+12,forward);
        }else{uint32_t back=r32(next+12);w32(forward+12,back);w32(back+8,forward);}
    }
    w32(chunk+4,extent|1);w32(chunk+extent,extent);
    if(!isRemainder)insertChunk(chunk,extent);
    ps2HeapUnlock();
}
void ps2HeapGrow(uint32_t context,uint32_t size)
{
    uint32_t oldTop=r32(ROOT+8),oldSize=r32(oldTop+4)&~UINT32_C(3);
    uint32_t bytes=(uint32_t)((uint64_t)size+r64(0x52c240)+16),oldEnd=oldTop+oldSize;
    if(r32(0x52c248)!=UINT32_MAX)bytes=(uint32_t)(((uint64_t)bytes+4095)&~UINT64_C(4095));
    uint32_t first=ps2HeapSbrkReentrant(context,bytes);
    if(first==UINT32_MAX||(first<oldEnd&&oldTop!=ROOT))return;
    uint32_t total=r32(0x52c260)+bytes;w32(0x52c260,total);
    if(first==oldEnd)w32(r32(ROOT+8)+4,(bytes+oldSize)|1);
    else{
        if(r32(0x52c248)==UINT32_MAX)w32(0x52c248,first);
        else w32(0x52c260,total+first-oldEnd);
        uint32_t misalignment=(first+8)&15,correction=misalignment?16-misalignment:0;
        uint32_t adjusted=first+correction;
        correction+=4096-((adjusted+bytes)&4095);
        uint32_t second=ps2HeapSbrkReentrant(context,correction);
        if(second==UINT32_MAX)return;
        w32(0x52c260,r32(0x52c260)+correction);w32(ROOT+8,adjusted);
        w32(adjusted+4,(second-adjusted+correction)|1);
        if(oldTop!=ROOT){
            if(oldSize<16){w32(adjusted+4,1);return;}
            oldSize=(oldSize-12)&~UINT32_C(15);
            uint32_t oldFlags=r32(oldTop+4);w32(oldTop+4,(oldFlags&1)|oldSize);
            w32(oldTop+oldSize+8,5);w32(oldTop+oldSize+4,5);
            if(oldSize>=16)ps2HeapFree(context,oldTop+8);
        }
    }
    uint64_t current=sx32(r32(0x52c260));
    if(r64(0x52c250)<current)w64(0x52c250,current);
    if(r64(0x52c258)<current)w64(0x52c258,current);
}
uint32_t ps2HeapMallocReentrant(uint32_t context,uint32_t size)
{
    uint32_t expanded=size+19,needed=expanded<31?16:expanded&~UINT32_C(15);
    ps2HeapLock();uint32_t chunk,index;
    if(needed<504){
        uint32_t anchor=ROOT+needed;chunk=r32(anchor+12);
        if(chunk!=anchor){
            uint32_t extent=r32(chunk+4)&~UINT32_C(3),back=r32(chunk+12),forward=r32(chunk+8);
            uint32_t following=chunk+extent,flags=r32(following+4);
            w32(forward+12,back);w32(back+8,forward);w32(following+4,flags|1);
            ps2HeapUnlock();return chunk+8;
        }
        index=(needed>>3)+2;
    }else{
        index=binIndex(needed);uint32_t anchor=ROOT+index*8;
        chunk=r32(anchor+12);
        while(chunk!=anchor){
            uint32_t extent=r32(chunk+4)&~UINT32_C(3);int64_t delta=difference(extent,needed);
            if(delta>=16)break;
            if(delta>=0){
                uint32_t back=r32(chunk+12),flags=r32(chunk+extent+4),forward=r32(chunk+8);
                w32(chunk+extent+4,flags|1);w32(forward+12,back);w32(back+8,forward);
                ps2HeapUnlock();return chunk+8;
            }
            chunk=r32(chunk+12);
        }
        if(chunk==anchor)index++;
    }
    chunk=r32(REM+8);
    if(chunk!=REM){
        uint32_t extent=r32(chunk+4)&~UINT32_C(3);int64_t delta=difference(extent,needed);
        if(delta>=16){splitRemainder(chunk,needed,(uint32_t)delta);ps2HeapUnlock();return chunk+8;}
        w32(REM+12,REM);w32(REM+8,REM);
        if(delta>=0){w32(chunk+extent+4,r32(chunk+extent+4)|1);ps2HeapUnlock();return chunk+8;}
        insertChunk(chunk,extent);
    }
    uint32_t corrected=index;
    if(signed32(index)<0)corrected+=3;
    uint64_t mask=UINT64_C(1)<<(((uint32_t)(signed32(corrected)>>2))&63);
    uint64_t bitmap=r32(ROOT+4);
    if(mask<=bitmap){
        if(!(mask&bitmap)){index&=~UINT32_C(3);do{mask<<=1;index+=4;}while(!(mask&bitmap));}
        for(;;){
            uint32_t groupIndex=index,groupAnchor=ROOT+index*8,anchor=groupAnchor;
            do{
                chunk=r32(anchor+12);
                while(chunk!=anchor){
                    uint32_t extent=r32(chunk+4)&~UINT32_C(3);int64_t delta=difference(extent,needed);
                    if(delta>=16){unlinkChunk(chunk);splitRemainder(chunk,needed,(uint32_t)delta);ps2HeapUnlock();return chunk+8;}
                    if(delta>=0){
                        uint32_t back=r32(chunk+12),flags=r32(chunk+extent+4),forward=r32(chunk+8);
                        w32(chunk+extent+4,flags|1);w32(forward+12,back);w32(back+8,forward);
                        ps2HeapUnlock();return chunk+8;
                    }
                    chunk=r32(chunk+12);
                }
                anchor+=8;
                if(signed32(index)<63){anchor+=8;index++;}
                index++;
            }while(index&3);
            uint32_t cursor=groupIndex;
            for(;;){
                uint32_t low=cursor&3;cursor--;
                if(!low){w32(ROOT+4,r32(ROOT+4)&~(uint32_t)mask);break;}
                groupAnchor-=8;
                if(r32(groupAnchor+8)!=groupAnchor)break;
            }
            bitmap=r32(ROOT+4);mask<<=1;
            if(mask>bitmap||!mask)break;
            if(!(mask&bitmap)){do{mask<<=1;index+=4;}while(!(mask&bitmap));}
        }
    }
    uint32_t extent=r32(r32(ROOT+8)+4)&~UINT32_C(3);int64_t delta=difference(extent,needed);
    if((r32(r32(ROOT+8)+4)&~UINT32_C(3))<needed||delta<16){
        ps2HeapGrow(context,needed);extent=r32(r32(ROOT+8)+4)&~UINT32_C(3);delta=difference(extent,needed);
        if((r32(r32(ROOT+8)+4)&~UINT32_C(3))<needed||delta<16){ps2HeapUnlock();return 0;}
    }
    chunk=r32(ROOT+8);uint32_t next=chunk+needed;
    w32(chunk+4,needed|1);w32(ROOT+8,next);w32(next+4,(uint32_t)delta|1);
    ps2HeapUnlock();return chunk+8;
}
uint32_t ps2HeapMalloc(uint32_t size)
{ps2HeapLock();uint32_t result=ps2HeapMallocReentrant(r32(0x52be28),size);ps2HeapUnlock();return result;}
uint32_t ps2CreateSemaphore(uint32_t initial,uint32_t maximum,uint32_t option)
{
    unsigned char parameters[24];memcpy(parameters+8,&initial,4);memcpy(parameters+4,&maximum,4);memcpy(parameters+20,&option,4);
    return ps2KernelCreateSema(parameters);
}
void ps2DeferredQueueInitialize(uint32_t queue,uint32_t callback)
{
    if(signed32(r32(0x551864))<0)w32(0x551864,ps2CreateSemaphore(1,127,0));
    w32(queue,callback);w32(queue+4,0);
}
void ps2DeferredQueueAppend(uint32_t queue,uint32_t value)
{
    if(!value)return;
    (void)ps2KernelWaitSema(r32(0x551864));uint32_t node=r32(queue+4);
    if(!node){
        node=ps2PoolAllocate(16);uint32_t head=r32(0x5520b0);
        w32(node+12,0);w32(node,head);w32(node+8,0);w32(queue+4,node);w32(node+4,queue);w32(0x5520b0,node);
    }
    uint32_t remaining=r32(node+12),block=r32(node+8);
    if(!remaining){uint32_t next=ps2PoolAllocate(256);remaining=63;w32(next,block);block=next;w32(node+8,next);}
    uint32_t semaphore=r32(0x551864);
    w32(block+(63-remaining)*4+4,value);w32(node+12,remaining-1);
    (void)ps2KernelSignalSema(semaphore);
}
void ps2MatListReleasePolicy(uint32_t list,uint32_t deferred)
{if(!list)return;if(deferred)ps2DeferredQueueAppend(0x5520c0,list);else ps2ArrayFree(list);}
void ps2MemoryArenaInitialize(uint32_t size)
{
    uint32_t record=0x577f18,payload=ps2HeapMalloc(size);w32(record+36,size);w32(record+32,payload);
    uint32_t descriptor=ps2PoolAllocate(16),start=r32(record+32);
    uint32_t end=(start+size)&~UINT32_C(127);start=(start+127)&~UINT32_C(127);
    w16(record+28,2);w16(record+30,UINT16_MAX);w32(record+24,end);
    w32(record,0);w32(record+4,descriptor);w16(record+12,2);w16(record+14,UINT16_MAX);
    w32(record+16,descriptor);w32(record+20,0);w32(record+8,start);w32(descriptor,record);
    w16(descriptor+14,0);w32(descriptor+4,record+16);w32(descriptor+8,start);w16(descriptor+12,0);
    w32(0x551830,0);ps2DeferredQueueInitialize(0x552078,0x2a9558);
}

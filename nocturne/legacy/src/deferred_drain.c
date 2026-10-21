/* Reconstructed from original Nocturne EE instructions; raw PS2 addresses. */
#include "deferred_drain.h"
#include <string.h>
#include "heap_queue.h"
#include "material_fiveword_pool.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
extern void ps2PoolRelease(uint32_t allocation);
extern void nocturneCallDeferredRelease(uint32_t callback,uint32_t value);
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveHeapAddress(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(nocturneResolveHeapAddress(a),&v,4);}
static void w8(uint32_t a,uint8_t v){memcpy(nocturneResolveHeapAddress(a),&v,1);}
static uint8_t r8(uint32_t a){uint8_t v;memcpy(&v,nocturneResolveHeapAddress(a),1);return v;}
static int64_t sx32(uint32_t v){return (int64_t)v-((v>>31)?INT64_C(4294967296):0);}
uint32_t ps2DeferredQueueDetachActive(void)
{
    uint32_t head=r32(0x5520b0),node=head;
    w32(0x5520b0,0);
    while(node){uint32_t owner=r32(node+4);w32(owner+4,0);node=r32(node);}
    return head;
}
void ps2DeferredQueueDrain(uint32_t node)
{
    while(node){
        uint32_t used=63-r32(node+12),owner=r32(node+4),block=r32(node+8);
        uint32_t callback=r32(owner);
        while(block){
            uint32_t cursor=block+4,count=0;
            /* The original executes one callback even when used is zero.
             * The loop comparison sign-extends both wrapping 32-bit words. */
            do{uint32_t value=r32(cursor);cursor+=4;++count;nocturneCallDeferredRelease(callback,value);}while(sx32(count)<sx32(used));
            uint32_t previous=r32(block);ps2PoolRelease(block);block=previous;used=63;
        }
        uint32_t next=r32(node);ps2PoolRelease(node);node=next;
    }
}
void ps2DeferredQueueAdvance(void)
{
    uint32_t sema=r32(0x551864);w8(0x5520b4,1);
    ps2KernelWaitSema(sema);
    ps2DeferredQueueDrain(r32(0x5520a8));
    uint32_t pending=r32(0x5520ac);w32(0x5520a8,pending);
    uint32_t detached=ps2DeferredQueueDetachActive();
    sema=r32(0x551864);w32(0x5520ac,detached);
    ps2KernelSignalSema(sema);w8(0x5520b4,0);
}
uint32_t ps2DeferredQueueIsBusy(void)
{
    if(r8(0x5520b4))return 1;
    if(r32(0x5520b0))return 1;
    for(uint32_t index=0;index<2;index++)if(r32(0x5520a8+4*index))return 1;
    return 0;
}
uint32_t ps2DeferredQueueIsBusyAtomic(void)
{
    uint32_t enabled=ps2KernelDisableInterrupts();
    uint32_t busy=ps2DeferredQueueIsBusy();
    if(enabled)ps2KernelEnableInterrupts();
    return busy;
}
void ps2WorkBufferReplace(uint32_t size)
{
    uint32_t handle=r32(0x551868);
    if(handle){ps2MemoryHandleFree(handle);w32(0x551868,0);}
    uint32_t rounded=(size+127)&UINT32_C(0xffffff80);
    w32(0x55186c,rounded);
    handle=ps2MemoryHandleAllocate((int32_t)sx32(rounded<<1));w32(0x551868,handle);
    uint32_t data=ps2MemoryHandleAcquirePointer(handle);
    w32(0x551870,data);w32(0x551874,data+rounded);
}
void ps2WorkBufferSelect(uint32_t index)
{
    uint32_t extent=r32(0x55186c),base=r32(0x551870+(index<<2));
    w32(0x551878,base);w32(0x55187c,base+extent);
}
uint32_t ps2WorkBufferTake(uint32_t size)
{
    uint32_t cursor=r32(0x551878);size=(size+15)&UINT32_C(0xfffffff0);
    w32(0x551878,cursor+size);return cursor;
}
uint32_t ps2WorkBufferGetCursor(void){return r32(0x551878);}
void ps2WorkBufferSetCursor(uint32_t cursor){w32(0x551878,(cursor+15)&UINT32_C(0xfffffff0));}
void ps2DmaChainInitialize(uint32_t chain)
{
    w32(chain+28,0);w32(chain+12,0xffff);w32(chain,0);w32(chain+4,0);
    w32(chain+8,0);w32(chain+16,0);w32(chain+20,0);w32(chain+24,0);
}
void ps2DmaChainAppend(uint32_t chain,uint32_t tag)
{
    uint32_t previous=r32(chain+8);
    if(!previous)w32(chain+4,tag);
    else{w8(previous+3,0x20);w32(previous+4,tag&UINT32_C(0x0fffffff));}
    w32(chain+8,tag);
}
void ps2DmaChainAppendWithTail(uint32_t chain,uint32_t tag,uint32_t tail)
{
    uint32_t previous=r32(chain+8);
    if(!previous)w32(chain+4,tag);
    else{w8(previous+3,0x20);w32(previous+4,tag&UINT32_C(0x0fffffff));}
    w32(chain+8,tail);
}

uint32_t ps2WorkBufferGetRemaining(void)
{
    uint32_t end=r32(0x55187c),cursor=r32(0x551878);
    return end-cursor;
}

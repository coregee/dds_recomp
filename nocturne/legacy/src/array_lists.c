/* Original generic-array/material-list path; preserve signed halfword policy and live reads. */
#include <stdint.h>
#include <string.h>
#include "array_lists.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
extern void *nocturneResolveMemoryHandleAddress(uint32_t address);
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMemoryHandleAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t address){uint32_t word;memcpy(&word,at(address),4);return word;}
static uint32_t r16(uint32_t address){uint16_t word;memcpy(&word,at(address),2);return word;}
static void w32(uint32_t address,uint32_t word){memcpy(at(address),&word,4);}
static void w16(uint32_t address,uint32_t word){uint16_t half=(uint16_t)word;memcpy(at(address),&half,2);}
static int32_t s16(uint32_t word){return (int32_t)(word&32767)-(int32_t)(word&32768);}
static int32_t s32(uint32_t word){return (int32_t)((int64_t)word-((word&0x80000000)?INT64_C(4294967296):0));}

uint32_t ps2ArrayCreate(int32_t capacity,int32_t stride,int32_t growth)
{
    uint32_t array=ps2PoolAllocate(16),bytes=(uint32_t)capacity*(uint32_t)stride;
    w16(array+10,(uint32_t)growth);w16(array+4,0);w16(array+6,(uint32_t)capacity);w16(array+8,(uint32_t)stride);
    if(capacity){uint32_t handle=ps2MemoryHandleAllocate(s32(bytes));w32(array,handle);uint32_t data=ps2MemoryHandleAcquirePointer(handle);w32(array+12,data);}
    else{w32(array,0);w32(array+12,0);}
    return array;
}
void ps2ArrayFree(uint32_t array)
{uint32_t handle=r32(array);ps2MemoryHandleFree(handle);ps2PoolRelease(array);}
void ps2ArrayGrow(uint32_t array)
{
    uint32_t handle=r32(array);
    if(!handle){ps2ArrayResize(array,s16(r16(array+10)));return;}
    ps2MemoryHandleReleasePointer(handle);
    uint32_t capacity=r16(array+6),growth=r16(array+10);int32_t stride=s16(r16(array+8));
    uint32_t sum=capacity+growth;handle=r32(array);uint32_t bytes=(uint32_t)s16(sum)*(uint32_t)stride;
    w16(array+6,sum);ps2MemoryHandleReallocate(handle,s32(bytes));
    handle=r32(array);uint32_t data=ps2MemoryHandleAcquirePointer(handle);w32(array+12,data);
}
void ps2ArrayResize(uint32_t array,int32_t capacity)
{
    uint32_t handle=r32(array);
    if(!handle){
        if(capacity<=0)return;
        int32_t stride=s16(r16(array+8));w16(array+6,(uint32_t)capacity);
        handle=ps2MemoryHandleAllocate(s32((uint32_t)stride*(uint32_t)capacity));w32(array,handle);
        uint32_t data=ps2MemoryHandleAcquirePointer(handle);w32(array+12,data);return;
    }
    if(capacity<=0){ps2MemoryHandleFree(handle);w32(array,0);w32(array+12,0);w16(array+4,0);w16(array+6,0);return;}
    ps2MemoryHandleReleasePointer(handle);w16(array+6,(uint32_t)capacity);
    int32_t stride=s16(r16(array+8));handle=r32(array);
    ps2MemoryHandleReallocate(handle,s32((uint32_t)stride*(uint32_t)capacity));
    handle=r32(array);uint32_t data=ps2MemoryHandleAcquirePointer(handle);int32_t count=s16(r16(array+4));
    int trim=capacity<count;w32(array+12,data);if(trim)w16(array+4,(uint32_t)capacity);
}
uint32_t ps2MatListCreate(int32_t capacity){return ps2ArrayCreate(capacity,4,8);}
void ps2MatListGrow(uint32_t list){ps2ArrayGrow(list);}
void ps2MatListAppend(uint32_t list,uint32_t material)
{
    int32_t count=s16(r16(list+4)),capacity=s16(r16(list+6));
    if(count>=capacity)ps2MatListGrow(list);
    uint32_t raw_count=r16(list+4),data=r32(list+12),slot=data+(uint32_t)(s16(raw_count)*4);
    w16(list+4,raw_count+1);w32(slot,material);
}
uint32_t ps2MatListMake(uint32_t textures,uint32_t definitions)
{
    uint32_t cursor=definitions+4,count=r32(definitions),capacity=count<32?32:count;
    uint32_t list=ps2MatListCreate(s32(capacity));
    while(count){--count;uint32_t material=ps2MatCreate();cursor=ps2MatReadDefinition(material,textures,cursor);ps2MatListAppend(list,material);}
    return list;
}
void ps2MatListFreeMaterials(uint32_t list)
{
    int32_t count=s16(r16(list+4));
    if(count>0){uint32_t index=0,data=r32(list+12);for(;;){uint32_t material=r32(data+(index<<2));++index;ps2MatRelease(material);count=s16(r16(list+4));if((int32_t)index>=count)break;data=r32(list+12);}}
    ps2ArrayFree(list);
}

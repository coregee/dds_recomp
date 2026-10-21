/* Complete native ownership and release prerequisites for camera/model cleanup. */
#include "model_cleanup.h"
#include "world_arrays.h"
#include "path_control.h"
#include "script_construction.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "array_lists.h"
#include "heap_queue.h"
#include "process_shutdown.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static uint32_t half(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t p){return p&0x80000000u?UINT64_C(0xffffffff00000000)|p:p;}
static int32_t sh(uint32_t v){return (int32_t)(v&32767)-(int32_t)(v&32768);}
uint64_t dds3AreaBasicTypeToItemType(uint64_t type){return type==8;}
uint64_t dds3AreaBasicGetItemArray(uint64_t area,uint64_t type)
{return sx(word(word((uint32_t)area+24)+((uint32_t)type<<2)));}
void dds3AreaBasicReleaseItem(uint64_t area,uint64_t item)
{uint64_t type=dds3AreaBasicTypeToItemType(*at((uint32_t)item+15));uint64_t array=dds3AreaBasicGetItemArray(area,type);(void)dds3SearchDeleteBasicArray(array,item,0);}
void ps2MemoryHandleDeferredRelease(uint64_t handle){if(handle)ps2DeferredQueueAppend(0x552078,(uint32_t)handle);}
void ps2MaterialDeferredRelease(uint64_t material){if(material)ps2DeferredQueueAppend(0x5520c8,(uint32_t)material);}
void ps2ModelRootRelease(uint64_t root,uint64_t deferred,uint64_t releaseMaterials)
{
 if(!root)return;uint32_t r=(uint32_t)root;
 if(releaseMaterials)ps2MatListReleasePolicy(word(r+12),1);
 uint32_t array=word(r+16);if(array)ps2ArrayFree(array);
 if(deferred)ps2DeferredQueueAppend(0x5520b8,r);
 else{ps2ArrayFree(word(r));ps2PoolRelease(r);}
}
void ps2ModelTextureListRelease(uint64_t list,uint64_t releaseItems)
{
 if(!list)return;uint32_t l=(uint32_t)list;
 if(releaseItems){int32_t count=sh(half(l+4));for(int32_t i=0;i<count;i++)ps2TextureDeferredRelease(sx(word(word(l+12)+(uint32_t)i*4)));}
 ps2ArrayFree(l);
}
void ps2MotionNodePoolDestroy(uint64_t node){ps2PoolRelease((uint32_t)node);}
void sdfMotionNodeFree(uint64_t node){nocturneCallMotionNodeDestructor(word(word((uint32_t)node)),node);}
void sdfMotionCtrlrFree(uint64_t controller)
{
 if(!controller)return;uint32_t c=(uint32_t)controller,model=word(c+4);
 if(model){uint32_t slot=model+20,n=word(slot);while(n){if(sx(n)==controller){put(slot,word(c));break;}slot=n;n=word(slot);}}
 uint32_t array=word(c+16);int32_t count=sh(half(array+4));uint32_t data=word(array+12);
 for(int32_t i=0;i<count;i++){sdfMotionNodeFree(sx(word(data)));data+=4;}
 /* The native body reloads the array only after a positive-length loop. */
 if(count>0)array=word(c+16);ps2ArrayFree(array);ps2PoolRelease(c);
}
uint64_t mdlGetMajorNum(uint64_t handle){return half(word((uint32_t)handle+12)+8);}
uint64_t mdlGetMinorNum(uint64_t handle){return half(word((uint32_t)handle+12)+10);}
uint64_t ps2ModelNeedsSpecialRelease(uint64_t handle)
{if(mdlGetMajorNum(handle)!=1)return 0;uint64_t minor=mdlGetMinorNum(handle);return minor==192||(minor>=339&&minor<342);}
void mdlFreeBlur(uint64_t handle)
{
 uint32_t h=(uint32_t)handle,blur=word(h+48);if(!blur)return;uint32_t node=word(blur);
 while(node){uint32_t current=node;node=word(current);ps2ModelRootRelease(sx(word(current+4)),1,1);ps2PoolRelease(current);}
 ps2PoolRelease(blur);put(h+48,0);
}
uint64_t evtDeleteUnitHandle(uint64_t handle)
{
 if(!handle)return 1;uint32_t h=(uint32_t)handle;put(word(word(h+140)+24)+128,0);
 uint32_t value=word(h+104);if(value){ps2PoolRelease(value);put(h+104,0);}
 value=word(h+156);if(value){dds3PathBasicFreeControl(sx(value));put(h+156,0);}
 ps2PoolRelease(h);return 1;
}

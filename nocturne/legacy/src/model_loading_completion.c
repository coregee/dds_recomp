/* Original SLUS_209.11 model completion, registration and ownership chain. */
#include "model_loading_completion.h"
#include "model_bootstrap_resources.h"
#include "model_cleanup.h"
#include "model_effect_creation.h"
#include "resource_request_lifecycle.h"
#include "resource_loader_support.h"
#include "resource_loader_flow.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "pac_texture_array.h"
#include "pac_binary.h"
#include "texture_upload.h"
#include "heap_queue.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelLoadingCompletionAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint8_t r8(uint32_t a){uint8_t v;memcpy(&v,at(a),1);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint8_t v){memcpy(at(a),&v,1);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
#endif
void ps2ModelRegisterResource(uint64_t group,uint64_t id,uint64_t flags,uint64_t textures,uint64_t definition,uint64_t handle){
 ENTER(0x40);ps2ModelRemoveRegisteredResource(group,id);uint32_t p=ps2PoolAllocate(180),head=0x32c458+((uint32_t)group<<2),old=r32(head);
 if(old)w32(old+4,p);w32(head,p);w32(p,old);w16(p+8,(uint16_t)group);w16(p+10,(uint16_t)id);
 w32(p+20,(uint32_t)textures);w32(p+24,(uint32_t)definition);w32(p+28,(uint32_t)handle);w32(p+4,0);w32(p+16,0);
 for(unsigned i=0;i<8;i++){uint32_t slot=p+32+i*16;w32(slot,0);w32(slot+8,0);w32(slot+12,0);}
 /* The slot halfwords and bytes 0D..0F retain their allocator contents. */
 w8(p+12,(uint8_t)(flags&1));w32(p+176,0x42c80000);w32(p+172,0x3f800000);w32(p+160,0);w32(p+164,0);w32(p+168,0);LEAVE(0x40);
}
void ps2ModelDestroyResource(uint64_t resource){
 ENTER(0x30);if(!resource){LEAVE(0x30);return;}uint32_t p=(uint32_t)resource,previous=r32(p+4),next=r32(p);
 if(!previous)w32(0x32c458+((uint32_t)r16(p+8)<<2),next);else w32(previous,next);
 if(next)w32(next+4,previous);uint32_t context=r32(p+16);uint8_t owned=r8(p+12);w8(p+12,0);
 while(context){ps2ModelContextRelease(sx(context));context=r32(p+16);}
 if(owned){ps2ModelTextureListRelease(sx(r32(p+20)),1);ps2MemoryHandleDeferredRelease(sx(r32(p+28)));for(unsigned i=0;i<8;i++){uint32_t handle=r32(p+44+i*16);if(handle)ps2MemoryHandleFree(handle);}}
 ps2ModelResourceListRelease(sx(r32(p+168)));ps2MemoryHandleFree(r32(p+160));LEAVE(0x30);ps2PoolRelease(p);
}
void ps2ModelRemoveRegisteredResource(uint64_t group,uint64_t id){
 ENTER(0x10);uint64_t p=ps2ModelFindRegisteredResource(group,id);LEAVE(0x10);ps2ModelDestroyResource(p);
}
void ps2ModelReleaseContextMotion(uint64_t context,uint64_t motion){
 ENTER(0x10);uint32_t m=(uint32_t)motion,slot=(uint32_t)context+32+((uint32_t)(int32_t)(int16_t)r16(m+42)<<2);
 if(sx(r32(slot))==motion)w32(slot,0);LEAVE(0x10);sdfMotionCtrlrFree(motion);
}
void ps2ModelReleaseContextSlot(uint64_t context,uint64_t slot){
 ENTER(0x10);uint32_t m=r32(r32((uint32_t)context+24)+20);
 while(m){if((uint64_t)(int64_t)(int16_t)r16(m+40)==slot){ps2ModelReleaseContextMotion(context,sx(m));break;}m=r32(m);}LEAVE(0x10);
}
void ps2ModelReleaseResourceSlot(uint64_t resource,uint64_t slot){
 ENTER(0x30);if(!resource){LEAVE(0x30);return;}uint32_t p=(uint32_t)resource,offset=(uint32_t)slot<<4;
 if(!r32(p+40+offset)){LEAVE(0x30);return;}uint32_t c=r32(p+16);
 while(c){ps2ModelReleaseContextSlot(sx(c),slot);c=r32(c+4);}
 if(r8(p+12)){uint32_t h=r32(p+44+offset);if(h)ps2MemoryHandleFree(h);}w32(p+40+offset,0);w32(p+44+offset,0);LEAVE(0x30);
}
void ps2ModelConfigureResourceSlot(uint64_t group,uint64_t id,uint64_t flags,uint64_t cut,uint64_t slot,uint64_t index,uint64_t motion,uint64_t handle){
 ENTER(0x40);uint64_t owner=ps2ModelFindRegisteredResource(group,id);uint32_t p=(uint32_t)owner+((uint32_t)slot<<4)+32;
 ps2ModelReleaseResourceSlot(owner,slot);w16(p+4,(uint16_t)index);w16(p+6,(uint16_t)cut);w32(p+8,(uint32_t)motion);w32(p+12,(uint32_t)handle);w32(p,0);
 if(flags&0x100)w32(p,1);if(flags&0x200)w32(p,r32(p)|2);LEAVE(0x40);
}
void ps2ModelRegisterLoadedFields(uint64_t group,uint64_t id,uint64_t flags,uint64_t fields){
 ENTER(0x30);uint32_t f=(uint32_t)fields;ps2ModelRegisterResource(group,id,flags,sx(r32(f)),sx(r32(f+4)),sx(r32(f+8)));
 uint32_t motion=r32(f+12);if(motion)ps2ModelConfigureResourceSlot(group,id,flags,0,0,0,sx(motion),sx(r32(f+16)));
 if(r32(f+20)){uint32_t p=(uint32_t)ps2ModelFindRegisteredResource(group,id),info=r32(f+20),list=r32(f+28),handle=r32(f+24);w32(p+168,list);w32(p+164,info);w32(p+160,handle);}LEAVE(0x30);
}
void ps2ModelCompleteLoading(uint64_t loading){
 ENTER(0x10);uint32_t p=(uint32_t)loading;ps2ModelRegisterLoadedFields(r16(p),r16(p+2),sx(r32(p+8)),sx(p+12));
 (void)ps2KernelWaitSema(r32(0x551efc));ps2ModelRemovePending(r16(p),r16(p+2));(void)ps2KernelSignalSema(r32(0x551efc));LEAVE(0x10);ps2PoolRelease(p);
}
uint64_t ps2ModelTextureBookRead(uint64_t book){
 ENTER(0x30);uint32_t p=(uint32_t)book,n=r32(p+16),array=(uint32_t)ps2PointerArrayCreate((int32_t)n),i=0,table=p+20;
 if(n)do{uint32_t offset=r32(table);table+=4;i++;uint64_t texture=ps2TextureTmxCopy(sx(p+offset));ps2PointerArrayAppend(sx(array),texture);}while(i!=n);LEAVE(0x30);return sx(array);
}
uint64_t ps2ModelDefinitionBookRead(uint64_t book){
 ENTER(0x10);uint32_t p=(uint32_t)book,body=p+32,delta=r32(p+16),size=r32(p+20);ps2PacRelocatePointers(sx(body),sx(body),sx(body+delta),sx(size));LEAVE(0x10);return sx(body);
}
uint64_t ps2ModelMotionBookRead(uint64_t book){
 ENTER(0x10);uint32_t p=(uint32_t)book,body=p+32,delta=r32(p+16),size=r32(p+20);ps2PacRelocatePointers(sx(body),sx(body),sx(body+delta),sx(size));LEAVE(0x10);return sx(body);
}
void ps2ModelTextureLoadComplete(uint64_t request,uint64_t loading){
 ENTER(0x20);uint64_t list=ps2ModelTextureBookRead(fileGetLoadPtr(request));w32((uint32_t)loading+12,(uint32_t)list);ps2MemoryHandleFree((uint32_t)fileGetMemHandle(request));LEAVE(0x20);(void)ps2ResourceRequestRelease(request);
}
void ps2ModelDefinitionLoadComplete(uint64_t request,uint64_t loading){
 ENTER(0x20);uint32_t p=(uint32_t)loading;w32(p+20,(uint32_t)fileGetMemHandle(request));w32(p+16,(uint32_t)ps2ModelDefinitionBookRead(fileGetLoadPtr(request)));(void)ps2ResourceRequestRelease(request);
 uint8_t hasMotion=r8(p+6);LEAVE(0x20);if(!hasMotion)ps2ModelCompleteLoading(loading);
}
void ps2ModelMotionLoadComplete(uint64_t request,uint64_t loading){
 ENTER(0x20);uint32_t p=(uint32_t)loading;w32(p+28,(uint32_t)fileGetMemHandle(request));w32(p+24,(uint32_t)ps2ModelMotionBookRead(fileGetLoadPtr(request)));(void)ps2ResourceRequestRelease(request);LEAVE(0x20);ps2ModelCompleteLoading(loading);
}
void ps2ModelUnlinkContext(uint64_t context){
 ENTER(0x10);uint32_t p=(uint32_t)context,next=r32(p+4),previous=r32(p+8);if(next)w32(next+8,previous);
 if(previous)w32(previous+4,next);else{uint32_t owner=r32(p+12);w32(owner+16,next);if(!next&&r8(owner+12)){LEAVE(0x10);ps2ModelDestroyResource(sx(owner));return;}}LEAVE(0x10);
}
void ps2ModelContextRelease(uint64_t context){
 ENTER(0x20);uint32_t p=(uint32_t)context,root=r32(p+24),motion=r32(root+20);
 while(motion){sdfMotionCtrlrFree(sx(motion));motion=r32(root+20);}ps2ModelTextureListRelease(sx(r32(root+8)),1);
 uint32_t effect=r32(p+20);while(effect){uint32_t next=r32(effect);mdlFreeEffect(sx(effect));effect=next;}
 mdlFreeBlur(context);ps2ModelRootRelease(sx(root),1,1);ps2ModelUnlinkContext(context);LEAVE(0x20);ps2PoolRelease(p);
}

/* Original PAC ownership and full model acquire/construction bodies. */
#include "model_pac_loading.h"
#include "model_loading_completion.h"
#include "model_bootstrap_resources.h"
#include "model_motion_creation.h"
#include "model_effect_creation.h"
#include "model_draw_commands.h"
#include "resource_request_lifecycle.h"
#include "resource_loader_flow.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "heap_queue.h"
#include "ps2_sdk_helpers.h"
#include "ps2_sdk_neighbors.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelPacLoadingAddress(a);
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
static uint64_t sh(uint16_t v){return (uint64_t)(int64_t)(int16_t)v;}
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static uint32_t local(void *p,uint32_t n){return nocturneModelPacLocal(p,n);}
static void endLocal(void){nocturneModelPacEndLocal();}
static uint64_t strchrAddress(uint64_t p,uint64_t c){return nocturneModelPacStrchr(p,c);}
static void notify(uint32_t target,uint64_t p){nocturneModelPacNotify(target,p);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static uint32_t local(void *p,uint32_t n){(void)n;return (uint32_t)(uintptr_t)p;}
static void endLocal(void){}
static uint64_t strchrAddress(uint64_t p,uint64_t c){return (uint64_t)(uintptr_t)ps2Strchr((const char *)(uintptr_t)p,(int32_t)c);}
static void notify(uint32_t target,uint64_t p){((void(*)(uint64_t))(uintptr_t)target)(p);}
#endif
uint64_t ps2ModelPacRecordIsPib(uint64_t record){uint32_t p=(uint32_t)record;return r8(p+16)==1&&r32(p+24)==0x30424950;}
uint64_t ps2ModelPibVersion(uint64_t header){return sx(r32((uint32_t)header+8));}
uint64_t ps2ModelPibEffectCount(uint64_t header){return r16((uint32_t)header+14);}
uint64_t ps2ModelPibMotionCount(uint64_t header){return r16((uint32_t)header+16);}
uint64_t ps2PacDiscardRecord(uint64_t record){
 ENTER(0x10);uint32_t p=(uint32_t)record,owner=r32(p+4),link=owner+48,current=r32(link),previous=0;
 while(sx(current)!=record){previous=current;link=current;current=r32(link);}
 uint32_t next=r32(p);w32(link,next);if(sx(r32(owner+52))==record)w32(owner+52,previous);ps2PoolRelease(p);LEAVE(0x10);return sx(next);
}
uint64_t ps2ModelRegisterLegacyPac(uint64_t record,uint64_t group,uint64_t id,uint64_t flags){
 ENTER(0x50);uint32_t fields[8];ps2Memset(fields,0,32);uint32_t list=0;uint64_t current=record;
 while(current){uint32_t p=(uint32_t)current,kind=r8(p+16);
  if(kind==1){uint32_t tag=r32(p+24);
   if(tag==0x30424950){fields[5]=r32(p+12);fields[6]=r32(p+8);uint64_t n=ps2ModelPibEffectCount(sx(fields[5]));if((int64_t)n>0){list=(uint32_t)ps2ModelResourceListCreate(n);fields[7]=list;}}
   else if(tag==0x00413250){ps2ModelResourceAppendBillboard(sx(list),sx(r32(p+12)));ps2MemoryHandleFree(r32(p+8));}
   else if(tag==0x00503344){ps2ModelResourceAppendEffect(sx(list),sx(r32(p+12)));ps2MemoryHandleFree(r32(p+8));}
  }else if(kind==9)fields[0]=r32(p+8);
  else if(kind==6){if(!fields[2]){fields[2]=r32(p+8);fields[1]=r32(p+12);}}
  else if(kind==8){if(!fields[4]){fields[4]=r32(p+8);fields[3]=r32(p+12);}}
  current=ps2PacDiscardRecord(current);
 }
 uint32_t f=local(fields,32);ps2ModelRegisterLoadedFields(group,id,flags,sx(f));endLocal();LEAVE(0x50);return current;
}
uint64_t ps2ModelRegisterPac(uint64_t record,uint64_t group,uint64_t id,uint64_t flags){
 ENTER(0x90);uint32_t p=(uint32_t)record,header;
 if(!ps2ModelPacRecordIsPib(record)||((header=r32(p+12)),(int64_t)ps2ModelPibVersion(sx(header))<=0)){
  uint64_t result=ps2ModelRegisterLegacyPac(record,group,id,sx((uint32_t)flags));LEAVE(0x90);return result;
 }
 uint32_t fields[8];ps2Memset(fields,0,32);fields[5]=header;fields[6]=r32(p+8);uint64_t current=ps2PacDiscardRecord(record);
 int32_t count=(int32_t)ps2ModelPibEffectCount(sx(header));
 if(count>0){uint32_t list=(uint32_t)ps2ModelResourceListCreate(sx((uint32_t)count));fields[7]=list;
  do{p=(uint32_t)current;uint32_t tag=r32(p+24);
   if(tag==0x00413250){ps2ModelResourceAppendBillboard(sx(list),sx(r32(p+12)));ps2MemoryHandleFree(r32(p+8));}
   else if(tag==0x00503344){ps2ModelResourceAppendEffect(sx(list),sx(r32(p+12)));ps2MemoryHandleFree(r32(p+8));}
   else if(tag==0x00555049){uint32_t size=r32(p+28),data=r32(p+12);if(!size)size=r32(p+20)+(r8(p+17)&0xf0)-16;ps2ModelResourceAppendMovie(sx(list),sx(data),sx(r32(p+8)),sx(size));}
   /* Unknown effect tags only write unused original frame scratch. */
   current=ps2PacDiscardRecord(current);count--;
  }while(count!=0);
 }
 p=(uint32_t)current;if(r8(p+16)==9){fields[0]=r32(p+8);current=ps2PacDiscardRecord(current);p=(uint32_t)current;}
 fields[2]=r32(p+8);fields[1]=r32(p+12);current=ps2PacDiscardRecord(current);
 uint32_t f=local(fields,32);ps2ModelRegisterLoadedFields(group,id,sx((uint32_t)flags),sx(f));endLocal();count=(int32_t)ps2ModelPibMotionCount(sx(header));
 while(count>0){p=(uint32_t)current;uint32_t motion=r32(p+12),handle=r32(p+8),meta=motion-16;
  ps2ModelConfigureResourceSlot(group,id,sx((uint32_t)flags),sh(r16(meta+12)),r16(meta+8),r16(meta+10),sx(motion),sx(handle));current=ps2PacDiscardRecord(current);count--;
 }
 LEAVE(0x90);return current;
}
void ps2ModelPacJobRelease(uint64_t job){ENTER(0x10);uint32_t p=(uint32_t)job;(void)ps2ResourcePacRequestFree(sx(r32(p+8)));LEAVE(0x10);ps2PoolRelease(p);}
void ps2ModelPacLoadComplete(uint64_t request,uint64_t job){
 ENTER(0x10);uint32_t p=(uint32_t)job;w32(p+8,(uint32_t)request);(void)ps2ModelRegisterPac(sx(r32((uint32_t)request+96)),r16(p),r16(p+2),sx(r32(p+4)));
 (void)ps2KernelWaitSema(r32(0x551efc));ps2ModelRemovePending(r16(p),r16(p+2));(void)ps2KernelSignalSema(r32(0x551efc));uint32_t callback=r32(p+12);
 if(callback){notify(callback,sx(r32(p+16)));LEAVE(0x10);ps2ModelPacJobRelease(job);return;}LEAVE(0x10);
}
uint64_t ps2ModelRequestPac(uint64_t group,uint64_t id,uint64_t flags,uint64_t path,uint64_t callback,uint64_t parameter){
 ENTER(0x40);uint32_t p=ps2PoolAllocateZeroed(20);w16(p,(uint16_t)group);w16(p+2,(uint16_t)id);w32(p+4,(uint32_t)flags);w32(p+16,(uint32_t)parameter);w32(p+12,(uint32_t)callback);
 uint64_t request=ps2ResourcePacRequestCreate(path,0,0,0x1de1a0,sx(p));w32(p+8,(uint32_t)request);
 if(!callback){(void)ps2ResourcePacWait(request);ps2ModelPacJobRelease(sx(p));}LEAVE(0x40);return 0;
}
uint64_t ps2ModelWaitRegistered(uint64_t group,uint64_t id){
 ENTER(0x20);while(ps2ModelIsPending(group,id))(void)ps2ResourcePump();LEAVE(0x20);return ps2ModelFindRegisteredResource(group,id);
}
uint64_t ps2ModelAcquireResource(uint64_t group,uint64_t id,uint64_t blocking){
 ENTER(0xb0);(void)ps2KernelWaitSema(r32(0x551efc));uint64_t resource=ps2ModelFindRegisteredResource(group,id);
 if(resource){(void)ps2KernelSignalSema(r32(0x551efc));LEAVE(0xb0);return resource;}
 if(ps2ModelIsPending(group,id)){(void)ps2KernelSignalSema(r32(0x551efc));if(blocking){resource=ps2ModelWaitRegistered(group,id);LEAVE(0xb0);return resource;}LEAVE(0xb0);return UINT64_MAX;}
 uint32_t selection=r32(0x32c420+((uint32_t)group<<3))+((uint32_t)id<<3),table=r16(selection),index=r16(selection+2),pathRecord=r32(0x32a820+(table<<3))+index*12;
 uint64_t extension=strchrAddress(sx(r32(pathRecord+4)),46);int packed=extension&&ps2Strcasecmp(at((uint32_t)extension),at(0x54f630))==0;
 ps2ModelMarkPending(group,id);(void)ps2KernelSignalSema(r32(0x551efc));uint8_t path[128];uint32_t pathAddress=local(path,128);
 if(packed){(void)ps2ModelBuildPrefixedPath(sx(pathAddress),sx(r32(pathRecord+4)));(void)ps2ModelRequestPac(group,id,0x101,sx(pathAddress),0x2a8078,0);}
 else{uint32_t work=ps2PoolAllocateZeroed(44),motion=r32(pathRecord+8);w32(work+8,0x101);w16(work,(uint16_t)group);w16(work+2,(uint16_t)id);if(motion)w8(work+6,1);
  if(r32(pathRecord)){w8(work+4,1);(void)ps2ModelBuildPrefixedPath(sx(pathAddress),sx(r32(pathRecord)));(void)ps2ResourceReadRequestCreate(sx(pathAddress),0,0x1dc968,sx(work));}
  w8(work+5,1);(void)ps2ModelBuildPrefixedPath(sx(pathAddress),sx(r32(pathRecord+4)));(void)ps2ResourceReadRequestCreate(sx(pathAddress),0,0x1dc9b8,sx(work));
  if(r32(pathRecord+8)){(void)ps2ModelBuildPrefixedPath(sx(pathAddress),sx(r32(pathRecord+8)));(void)ps2ResourceReadRequestCreate(sx(pathAddress),0,0x1dca30,sx(work));}
 }
 endLocal();if(blocking){resource=ps2ModelWaitRegistered(group,id);LEAVE(0xb0);return resource;}LEAVE(0xb0);return 0;
}
uint64_t ps2ModelAcquireResourceBlocking(uint64_t group,uint64_t id){return ps2ModelAcquireResource(group,id,1);}
void ps2ModelChangeMotionDefault(uint64_t context,uint64_t group,uint64_t cut){ps2ModelChangeMotionEffects(context,group,cut,1,0.0f,0.0f);}
uint64_t ps2ModelContextCreate(uint64_t group,uint64_t id){
 ENTER(0x50);uint32_t owner=(uint32_t)ps2ModelAcquireResourceBlocking(group,id),p=ps2PoolAllocateZeroed(56),next=r32(owner+16);w32(p+12,owner);w32(p+4,next);if(next)w32(next+8,p);
 w32(owner+16,p);uint64_t textures=ps2ModelTextureListClone(sx(r32(owner+20))),root=ps2ModelMake(textures,sx(r32(owner+24)));uint32_t scale=r32(owner+172);w32(p+24,(uint32_t)root);w32((uint32_t)root+112,scale);w32((uint32_t)root+116,scale);w32((uint32_t)root+120,scale);w32((uint32_t)root+124,0x3f800000);w16(p+18,65535);w32(p+52,r32(owner+176));w16(p+16,65535);
 for(unsigned slot=0;slot<8;slot++){uint32_t s=owner+32+slot*16;if(r32(s+8)&&(r32(s)&1)){(void)mdlCreateMotion(sx(p),slot);if(slot>0){uint16_t cut=r16(s+6);if((int16_t)cut>=0)ps2ModelChangeMotionDefault(sx(p),slot,sh(cut));}}}
 w32(p+20,0);mdlGenEffect(sx(p),UINT64_MAX,UINT64_MAX);LEAVE(0x50);return sx(p);
}

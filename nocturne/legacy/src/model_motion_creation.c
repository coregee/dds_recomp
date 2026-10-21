/* Complete original controller/node creation and cut binding. Original callback
 * tables decide targets; host adapters execute recovered bodies only. */
#include "model_motion_creation.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "array_lists.h"
#include "motion_callback_leaves.h"
#include "battle_check1_packets.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelMotionCreationAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t sh(uint16_t v){return (uint64_t)(int64_t)(int16_t)v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float unbits(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint64_t generate(uint32_t target,uint64_t controller,uint64_t command,uint64_t argument){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneCallMotionFactory(target,controller,command,argument);
#else
 return ((uint64_t(*)(uint64_t,uint64_t,uint64_t))(uintptr_t)target)(controller,command,argument);
#endif
}
static void capture(uint32_t target,uint64_t node){
#if UINTPTR_MAX > UINT32_MAX
 nocturneCallMotionCapture(target,node);
#else
 ((void(*)(uint64_t))(uintptr_t)target)(node);
#endif
}
static void bind(uint32_t target,uint64_t node,uint64_t track){
#if UINTPTR_MAX > UINT32_MAX
 nocturneCallMotionBind(target,node,track);
#else
 ((void(*)(uint64_t,uint64_t))(uintptr_t)target)(node,track);
#endif
}
/* 002B08E8: signed count, full incoming index/ID comparisons, original flags. */
uint64_t sdfModelSearchNode(uint64_t model,uint64_t index){
 uint32_t m=(uint32_t)model,array=r32(m),data=r32(array+12);int16_t count=(int16_t)r16(array+4);
 if(*at(m+0x19)&1){for(int32_t k=0;k<count;k++){uint32_t node=r32(data+(uint32_t)k*4u);if(sx(r32(node+0x18))==index)return sx(node);}return 0;}
 if(index<sh((uint16_t)count))return sx(r32(data+(uint32_t)index*4u));return 0;
}
uint64_t sdfMotGenNode(uint64_t controller,uint64_t command,uint64_t argument){return generate(r32(0x529448+((uint32_t)command>>16)*4u),controller,command,argument);}
uint64_t ps2MotionModelFactory(uint64_t controller,uint64_t command,uint64_t argument){return generate(r32(0x529458+(uint16_t)command*4u),controller,command,argument);}
void sdfMotGenModelInit(uint64_t node,uint64_t controller,uint64_t vtable,uint64_t argument){
 sdfMotionNodeBaseInit(at((uint32_t)node),(uint32_t)controller,(uint32_t)vtable);
 uint64_t target=sdfModelSearchNode(sx(r32((uint32_t)controller+4)),argument);w32((uint32_t)node+12,(uint32_t)target);
}
static uint64_t model_node(uint64_t controller,uint64_t argument,uint32_t size,uint32_t vtable){uint32_t p=ps2PoolAllocate((int32_t)size);sdfMotGenModelInit(sx(p),controller,sx(vtable),argument);return sx(p);}
uint64_t sdfMotGenModelLinerPos(uint64_t c,uint64_t command,uint64_t argument){(void)command;return model_node(c,argument,32,0x529470);}
uint64_t sdfMotGenModelLinerRotXYZ(uint64_t c,uint64_t command,uint64_t argument){(void)command;return model_node(c,argument,32,0x529488);}
uint64_t sdfMotGenModelLinerScale(uint64_t c,uint64_t command,uint64_t argument){(void)command;return model_node(c,argument,32,0x5294a0);}
uint64_t sdfMotGenModelLerpRotQuat(uint64_t c,uint64_t command,uint64_t argument){(void)command;return model_node(c,argument,32,0x5294b8);}
uint64_t sdfMotGenModelVisible(uint64_t c,uint64_t command,uint64_t argument){(void)command;return model_node(c,argument,20,0x5294d0);}
/* 002B3B88: publish controller before creating nodes; native reloads retained. */
uint64_t sdfMotionCtrlrNew(uint64_t model,uint64_t book){
 uint32_t m=(uint32_t)model,b=(uint32_t)book,p=ps2PoolAllocateZeroed(0x34),count=r16(b+2);
 w32(p,r32(m+0x14));w32(p+4,m);w32(m+0x14,p);w32(p+8,b);
 uint32_t array=ps2ArrayCreate((int32_t)count,4,8);w16(array+4,(uint16_t)count);w32(p+16,array);
 uint32_t record=r32(p+8)+8;
 for(uint32_t k=0;k<count;k++,record+=8){uint64_t node=sdfMotGenNode(sx(p),sx(r32(record)),sx(r32(record+4)));uint32_t a=r32(p+16);w32(r32(a+12)+k*4u,(uint32_t)node);}
 *at(p+0x30)=0;w32(p+0x20,0x3f800000);return sx(p);
}
/* 001DC550: unchecked lowword group selects a model-definition record. */
uint64_t mdlCreateMotion(uint64_t model,uint64_t group){
 uint32_t m=(uint32_t)model,record=r32(m+12)+((uint32_t)group<<4)+0x20;uint64_t slot=sh(r16(record+4));
 uint64_t result=sdfMotionCtrlrNew(sx(r32(m+0x18)),sx(r32(record+8)));uint32_t p=(uint32_t)result;
 w16(p+0x28,(uint16_t)group);w32(m+0x20+(uint32_t)slot*4u,p);w16(p+0x2a,(uint16_t)slot);if(slot==0)w32(m+0x1c,p);return result;
}
/* 002B3D28: full cut word for pointer arithmetic, SH state, real callbacks. */
void sdfMotionChangeBlend(uint64_t controller,uint64_t cut,uint64_t type,float lead,float duration){
 uint32_t p=(uint32_t)controller;w16(p+0x2c,(uint16_t)cut);
 if(EE_FPU_COMPARE_S(0,bits(duration),1)){
  w32(p+0x14,bits(duration));w32(p+0x18,bits(lead)^0x80000000u);int32_t k=0;
  while(k<(int16_t)r16(r32(p+16)+4)){uint32_t a=r32(p+16),node=r32(r32(a+12)+(uint32_t)k*4u);uint32_t target=r32(r32(node)+12);k++;capture(target,sx(node));}
 }else{w32(p+0x14,0);w32(p+0x18,0);}
 *at(p+0x32)=(uint8_t)type;*at(p+0x30)=1;
 uint32_t b=r32(p+8);w32(p+0x1c,r32(p+0x18));uint32_t entry=r32(r32(b+4)+((uint32_t)cut<<2));
 if(!entry){w16(p+0x2e,0);*at(p+0x30)=5;return;}
 w16(p+0x2e,r16(entry));uint32_t track=entry+4;int32_t k=0;
 while(k<(int16_t)r16(r32(p+16)+4)){uint32_t a=r32(p+16),node=r32(r32(a+12)+(uint32_t)k*4u);uint32_t target=r32(r32(node)+4);k++;bind(target,sx(node),sx(track));uint32_t stride=r32(track);track+=stride;}
}
void nocturneMotionChangeBlendBits(uint64_t c,uint64_t cut,uint64_t type,uint64_t lead,uint64_t duration){sdfMotionChangeBlend(c,cut,type,unbits((uint32_t)lead),unbits((uint32_t)duration));}
uint64_t mdlCreateEffectCtrlr(uint64_t model,uint64_t type,uint64_t group){uint32_t m=(uint32_t)model,p=ps2PoolAllocateZeroed(32),old=r32(m+0x14);w16(p+4,(uint16_t)type);w32(p,old);w16(p+6,(uint16_t)group);w32(m+0x14,p);return sx(p);}
uint64_t mdlGetEffectResrc(uint64_t model,uint64_t index){uint32_t array=r32(r32((uint32_t)model+12)+0xa8);if(!array)return 0;uint64_t count=sh(r16(array+4));if((int64_t)index<(int64_t)count)return sx(r32(array+12)+((uint32_t)index<<4));return 0;}
uint64_t ps2ModelActiveMotionCut(uint64_t model,uint64_t group){uint64_t c=mdlGetMotionCtrlr(model,group);return c?r16((uint32_t)c+0x2c):UINT64_MAX;}
uint64_t ps2ModelResourceFind(uint64_t id){uint32_t p=r32(0x551860);while(p){if(sx(r32(p+0x20))==id)return sx(p);p=r32(p+4);}return 0;}
uint64_t ps2ModelTagFind(uint64_t start,uint64_t tag){if(!start)return 0;uint64_t cursor=start;uint32_t p=(uint32_t)cursor;while(r32(p)){if(sx(r32(p))==tag)return cursor;p+=r32(p+4);cursor=sx(p);}return 0;}
uint64_t ps2ModelRootTagFind(uint64_t root,uint64_t tag){return ps2ModelTagFind(sx(r32((uint32_t)root+0x90)),tag);}
uint64_t ps2ModelPositionFind(uint64_t root,uint64_t index){uint64_t found=ps2ModelRootTagFind(root,0x534f504d);if(!found)return 0;uint32_t p=(uint32_t)found,end=p+r32(p+4);for(uint32_t item=p+16;item<end;item+=64)if(sx(r32(item+4))==index)return sx(item);return 0;}

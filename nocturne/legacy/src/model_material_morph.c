/* Original material factories, direct keys and two-influence morph blending. */
#include "model_material_morph.h"
#include "model_motion_creation.h"
#include "material_construction_release.h"
#include "material_fiveword_pool.h"
#include "motion_callback_leaves.h"
#include "motion_key_search.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelMotionCreationAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t word(uint32_t address){uint32_t value;memcpy(&value,at(address),4);return value;}
static void store(uint32_t address,uint32_t value){memcpy(at(address),&value,4);}
static uint32_t bits(float value){uint32_t result;memcpy(&result,&value,4);return result;}
static uint64_t sx(uint32_t value){return (uint64_t)(int64_t)(int32_t)value;}
static uint64_t generate(uint32_t table,uint64_t controller,uint64_t command,uint64_t argument){
 uint32_t target=word(table+(uint16_t)command*4u);
#if UINTPTR_MAX > UINT32_MAX
 return nocturneCallMotionFactory(target,controller,command,argument);
#else
 return ((uint64_t(*)(uint64_t,uint64_t,uint64_t))(uintptr_t)target)(controller,command,argument);
#endif
}
uint64_t ps2MotionMaterialFactory(uint64_t c,uint64_t command,uint64_t argument){return generate(0x5294e8,c,command,argument);}
uint64_t ps2MotionMorphFactory(uint64_t c,uint64_t command,uint64_t argument){return generate(0x529600,c,command,argument);}
static uint64_t material_node(uint64_t c,uint64_t argument,int32_t size,uint32_t table){
 uint32_t node=ps2PoolAllocate(size);ps2MotionBindMaterialNode(at(node),(uint32_t)c,table,(uint32_t)argument);return sx(node);
}
#define MATERIAL_NODE(name,size,table) \
uint64_t name(uint64_t c,uint64_t command,uint64_t argument){(void)command;return material_node(c,argument,size,table);}
MATERIAL_NODE(ps2MotionCreateMaterialWord14,20,0x529510)
MATERIAL_NODE(ps2MotionCreateMaterialWord10,20,0x529528)
MATERIAL_NODE(ps2MotionCreateMaterialWord20,20,0x529540)
MATERIAL_NODE(ps2MotionCreateMaterialWord28,20,0x529558)
MATERIAL_NODE(ps2MotionCreateMaterialScalar1C,20,0x529570)
MATERIAL_NODE(ps2MotionCreateMaterialDirect38,36,0x5295d0)
MATERIAL_NODE(ps2MotionCreateMaterialDirect3C,36,0x5295e8)
#undef MATERIAL_NODE
static void direct(uint64_t node,float frame,unsigned role){
 uint32_t n=(uint32_t)node,key[3];sdfMotGetKey(at(n),bits(frame),key);
 if(role==0x38)ps2MatSetFiveWords38(at(word(n+12)),at(key[0]));
 else ps2MatSetFiveWords3C(at(word(n+12)),at(key[0]));
}
void ps2MotionMaterialDirect38Seek(uint64_t n,float f){direct(n,f,0x38);}
void ps2MotionMaterialDirect38Blend(uint64_t n,float f,float w){(void)w;direct(n,f,0x38);}
void ps2MotionMaterialDirect3CSeek(uint64_t n,float f){direct(n,f,0x3c);}
void ps2MotionMaterialDirect3CBlend(uint64_t n,float f,float w){(void)w;direct(n,f,0x3c);}
void ps2MotionMorphInit(uint64_t node,uint64_t controller,uint64_t vtable,uint64_t argument){
 uint32_t n=(uint32_t)node,c=(uint32_t)controller;
 sdfMotionNodeBaseInit(at(n),c,(uint32_t)vtable);
 uint32_t root=word(c+4),array=word(root+16),data=word(array+12);
 store(n+12,data+((uint32_t)argument<<4));
}
uint64_t ps2MotionCreateMorph(uint64_t c,uint64_t command,uint64_t argument){
 (void)command;uint32_t node=ps2PoolAllocate(32);ps2MotionMorphInit(sx(node),c,0x529608,argument);return sx(node);
}
void ps2MotionMorphSeek(uint64_t node,float frame){
 uint32_t n=(uint32_t)node,key[3];sdfMotGetKey(at(n),bits(frame),key);
 uint32_t a=word(key[0]),b=word(key[1]),inverse=EE_FPU_SUB_S(0x3f800000,key[2]);
 uint32_t target=word(n+12),left=word(key[0]+4),right=word(key[1]+4);
 if(a==b){
  left=EE_FPU_MUL_S(left,inverse);store(target+8,b);right=EE_FPU_MUL_S(right,key[2]);
  store(target+12,0);store(target,b);store(target+4,EE_FPU_ADD_S(left,right));
 }else{
  left=EE_FPU_MUL_S(left,inverse);store(target,a);right=EE_FPU_MUL_S(right,key[2]);
  store(target+8,b);store(target+4,left);store(target+12,right);
 }
}
void ps2MotionMorphBlend(uint64_t node,float frame,float weight){
 uint32_t n=(uint32_t)node,key[3],w=bits(weight);sdfMotGetKey(at(n),bits(frame),key);
 uint32_t inverse=EE_FPU_SUB_S(0x3f800000,key[2]),a=word(key[0]);
 uint32_t rate=EE_FPU_MUL_S(key[2],w),b=word(key[1]);
 uint32_t left=word(key[0]+4),right=word(key[1]+4),scaled_inverse=EE_FPU_MUL_S(inverse,w),target=word(n+12);
 unsigned slots;
 if(a==b){
  left=EE_FPU_MUL_S(left,scaled_inverse);store(target,b);right=EE_FPU_MUL_S(right,rate);
  slots=1;store(target+4,EE_FPU_ADD_S(left,right));
 }else{
  left=EE_FPU_MUL_S(left,scaled_inverse);store(target,a);right=EE_FPU_MUL_S(right,rate);
  store(target+8,b);slots=2;store(target+4,left);store(target+12,right);
 }
 uint32_t threshold=word(0x54e748),remaining=EE_FPU_SUB_S(0x3f800000,w);
 for(unsigned k=0;k<2;k++){
  uint32_t captured=EE_FPU_MUL_S(word(n+20+k*8),remaining);
  if(EE_FPU_COMPARE_S(captured,threshold,2))continue;
  uint32_t id=word(n+16+k*8);
  if(slots==1){
   if(word(target)==id)store(target+4,EE_FPU_ADD_S(word(target+4),captured));
   else{store(target+8,id);slots=2;store(target+12,captured);}
  }else if(word(target)==id)store(target+4,EE_FPU_ADD_S(word(target+4),captured));
  else if(word(target+8)==id)store(target+12,EE_FPU_ADD_S(word(target+12),captured));
  else{
   uint32_t first=word(target+4),second=word(target+12);
   if(EE_FPU_COMPARE_S(first,second,1)){
    if(EE_FPU_COMPARE_S(first,captured,1)){store(target,id);store(target+4,captured);}
   }else if(EE_FPU_COMPARE_S(second,captured,1)){store(target+8,id);store(target+12,captured);}
  }
 }
 if(slots==1){store(target+12,0);store(target+8,0);}
}

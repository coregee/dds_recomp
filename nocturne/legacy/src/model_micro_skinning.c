/* Complete EE loops at002B6A70/002B6AF8 and original uploaded VU0 entries0/9. */
#include "model_micro_skinning.h"
#include "ee_vu_rotation.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
extern void EE_MODEL_MICRO_CPU_QUAD(unsigned gpr,const uint32_t words[4]);
#else
#define EE_MODEL_MICRO_CPU_QUAD(gpr,words) ((void)0)
#endif
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelMicroSkinningAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void packedNormal(uint32_t a,uint32_t v[4]){memcpy(v,at(a),8);v[2]=word(a+8);v[3]=v[2]&0x80000000u?UINT32_MAX:0;EE_MODEL_MICRO_CPU_QUAD(3,v);}
static void vector(uint32_t a,uint32_t v[4]){memcpy(v,at(a),16);}
static void load(unsigned r,uint32_t a){uint32_t v[4];vector(a,v);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void matrices(uint32_t a){for(unsigned k=0;k<4;k++)load(28+k,a+k*16);for(unsigned k=0;k<3;k++)load(24+k,a+64+k*16);}
static void acc(unsigned fs,unsigned ft,unsigned bc,unsigned mask,unsigned add){
 uint32_t a[4],b[4],v[4],of[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t x=add?EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],0):EE_ROT_VU_MUL(a[k],b[bc]);v[k]=(uint32_t)x;of[k]=(uint32_t)(x>>32)&1;}
 EE_ROT_ACC_WRITE(v,of);
}
static void mac(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask){
 uint32_t a[4],b[4],v[4],of[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],0);
 EE_ROT_VU_WRITE(fd,out);
}
static void mul(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask){
 uint32_t a[4],b[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[bc]);EE_ROT_VU_WRITE(fd,out);
}
/* Original paired upper/lower instruction0 reads the same incoming VF2. */
static void originalMicro0(void){
 uint32_t incoming[4];EE_ROT_VU_READ(2,incoming);mul(5,3,2,3,14);EE_ROT_VU_WRITE(6,incoming);
 acc(28,2,0,15,0);acc(29,2,1,15,1);acc(30,2,2,15,1);mac(4,31,0,3,15);
 acc(24,5,0,14,0);acc(25,5,1,14,1);mac(7,26,5,2,14);
 /* E on pair7 still executes pair8. */
 mul(4,4,6,3,14);
}
static void originalMicro9(void){
 mul(2,2,2,3,14);acc(24,3,0,14,0);acc(25,3,1,14,1);mac(3,26,3,2,14);
 acc(5,0,3,15,0);acc(28,2,0,15,1);acc(29,2,1,15,1);acc(30,2,2,15,1);mac(4,31,2,3,15);
 acc(6,0,3,14,0);mac(3,3,2,3,14); /* E pair18 and its pair19 delay. */
}
void ps2RenderTransformWeightedVertices(uint64_t output,uint64_t count,uint64_t matrix,uint64_t positions,uint64_t normals){
 uint32_t p=(uint32_t)output,pos=(uint32_t)positions,n=(uint32_t)normals,remaining=(uint32_t)count,point[4],normal[4];matrices((uint32_t)matrix);
 packedNormal(n,normal);n+=12;vector(pos,point);EE_MODEL_MICRO_CPU_QUAD(2,point);pos+=16;
 do{
  EE_ROT_VU_WRITE(2,point);EE_ROT_VU_WRITE(3,normal);originalMicro0();
  /* Native prefetch executes even on the last iteration, before output stores. */
  packedNormal(n,normal);n+=12;vector(pos,point);EE_MODEL_MICRO_CPU_QUAD(2,point);pos+=16;--remaining;
  uint32_t result[4];EE_ROT_VU_READ(7,result);EE_MODEL_MICRO_CPU_QUAD(4,result);store(4,p);memcpy(at(p+16),result,16);p+=96;
 }while(remaining);
}
void ps2RenderAccumulateWeightedVertices(uint64_t output,uint64_t count,uint64_t matrix,uint64_t positions,uint64_t normals){
 uint32_t p=(uint32_t)output,pos=(uint32_t)positions,n=(uint32_t)normals,remaining=(uint32_t)count-1;
 uint32_t point[4],normal[4],oldPoint[4],oldNormal[4];matrices((uint32_t)matrix);
 packedNormal(n,normal);n+=12;vector(pos,point);EE_MODEL_MICRO_CPU_QUAD(2,point);pos+=16;vector(p,oldPoint);EE_MODEL_MICRO_CPU_QUAD(4,oldPoint);vector(p+16,oldNormal);EE_MODEL_MICRO_CPU_QUAD(5,oldNormal);
 do{
  EE_ROT_VU_WRITE(2,point);EE_ROT_VU_WRITE(3,normal);EE_ROT_VU_WRITE(5,oldPoint);EE_ROT_VU_WRITE(6,oldNormal);originalMicro9();--remaining;
  packedNormal(n,normal);n+=12;vector(pos,point);EE_MODEL_MICRO_CPU_QUAD(2,point);pos+=16;vector(p+96,oldPoint);EE_MODEL_MICRO_CPU_QUAD(4,oldPoint);vector(p+112,oldNormal);EE_MODEL_MICRO_CPU_QUAD(5,oldNormal);
  uint32_t result[4];EE_ROT_VU_READ(4,result);EE_MODEL_MICRO_CPU_QUAD(6,result);store(3,p+16);memcpy(at(p),result,16);p+=96;
 }while(remaining);
 EE_ROT_VU_WRITE(2,point);EE_ROT_VU_WRITE(3,normal);EE_ROT_VU_WRITE(5,oldPoint);EE_ROT_VU_WRITE(6,oldNormal);originalMicro9();
 uint32_t result[4];EE_ROT_VU_READ(4,result);EE_MODEL_MICRO_CPU_QUAD(6,result);store(3,p+16);memcpy(at(p),result,16);
}

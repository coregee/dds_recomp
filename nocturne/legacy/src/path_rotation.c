/* Complete native quaternion path bodies, preserving VU operation grouping. */
#include "path_rotation.h"
#include "path_evaluation.h"
#include "script_construction.h"
#include "ee_vu_rotation.h"
#include "ee_fpu.h"
#include <string.h>
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,nocturneResolveScriptConstructionAddress(p),4);return v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static void load(unsigned reg,uint32_t p){uint32_t v[4];memcpy(v,nocturneResolveScriptConstructionAddress(p),16);EE_ROT_VU_WRITE(reg,v);}
static void result(uint64_t r,uint32_t *v,uint32_t *of){*v=(uint32_t)r;*of=(uint32_t)(r>>32)&1;}
/* 002C04E8: sum squares in W+X,Y,Z order; normalize all four lanes. */
void ps2QuaternionNormalize(void)
{
 uint32_t a[4],s[4],t[4],acc[4],of[4];EE_ROT_VU_READ(10,a);EE_ROT_VU_READ(3,t);EE_ROT_ACC_READ(acc,of);
 for(unsigned i=0;i<4;i++)s[i]=(uint32_t)EE_ROT_VU_MUL(a[i],a[i]);EE_ROT_VU_WRITE(2,s);
 result(EE_ROT_VU_ADD(s[3],s[0]),&acc[3],&of[3]);
 result(EE_ROT_VU_MAC(acc[3],0x3f800000u,s[1],of[3],0),&acc[3],&of[3]);EE_ROT_ACC_WRITE(acc,of);
 t[3]=(uint32_t)EE_ROT_VU_MAC(acc[3],0x3f800000u,s[2],of[3],0);EE_ROT_VU_WRITE(3,t);
 uint32_t q=EE_ROT_VU_RSQRT(0x3f800000u,t[3]);EE_ROT_Q_WRITE(q);
 for(unsigned i=0;i<4;i++)a[i]=(uint32_t)EE_ROT_VU_MUL(a[i],q);EE_ROT_VU_WRITE(10,a);
}
/* 002C0AE0: native dot chooses the sign of B, blend then tail-normalize.
 * This is not spherical interpolation and the rate is not clamped. */
void ps2QuaternionBlendNormalized(float rate)
{
 uint32_t a[4],b[4],c[4],one[4],product[4],acc[4],of[4];EE_ROT_VU_READ(10,a);EE_ROT_VU_READ(11,b);EE_ROT_VU_READ(1,one);EE_ROT_ACC_READ(acc,of);
 one[0]=one[1]=one[2]=0x3f800000u;EE_ROT_VU_WRITE(1,one);
 for(unsigned i=0;i<4;i++)product[i]=(uint32_t)EE_ROT_VU_MUL(a[i],b[i]);
 result(EE_ROT_VU_ADD(product[0],product[1]),&acc[0],&of[0]);
 result(EE_ROT_VU_MAC(acc[0],one[0],product[2],of[0],0),&acc[0],&of[0]);
 uint32_t dot=(uint32_t)EE_ROT_VU_MAC(acc[0],one[0],product[3],of[0],0);
 if((dot&0x80000000u)&&(dot&0x7f800000u)){
  for(unsigned i=0;i<4;i++){acc[i]=0;of[i]=0;c[i]=(uint32_t)EE_ROT_VU_MAC(0,b[i],0x3f800000u,0,1);}
 }else memcpy(c,b,16);
 EE_ROT_VU_WRITE(12,c);
 uint32_t r=bits(rate),inverse=EE_FPU_SUB_S(0x3f800000u,r);
 for(unsigned i=0;i<4;i++){result(EE_ROT_VU_MUL(a[i],inverse),&acc[i],&of[i]);a[i]=(uint32_t)EE_ROT_VU_MAC(acc[i],c[i],r,of[i],0);}
 EE_ROT_ACC_WRITE(acc,of);EE_ROT_VU_WRITE(10,a);ps2QuaternionNormalize();
}
/* 00116528: unchecked resource pointers and count-one negative prefix retained. */
void dds3PathBasicControlGetRot(uint64_t control)
{
 uint32_t p=(uint32_t)control;
 if(!(word(p+4)&2)){uint32_t identity[4]={0,0,0,0x3f800000u};EE_ROT_VU_WRITE(10,identity);return;}
 uint32_t channel=word(p+24),key[2];
 /* Native outputs are two caller-private stack words, not guest allocations. */
 /* The canonical key routine writes guest addresses, so use its shared
  * private-output boundary rather than synthetic fixed guest scratch. */
 nocturnePathElementPrivate(key,channel,word(p+12));
 uint32_t points=word(channel+4);
 load(10,points+key[0]*16);load(11,points+(key[0]+1)*16);ps2QuaternionBlendNormalized(real(key[1]));
}

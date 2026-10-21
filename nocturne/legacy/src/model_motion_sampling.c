/* Complete original basic-model key sampling and blend callbacks. */
#include "model_motion_sampling.h"
#include "model_motion_creation.h"
#include "motion_key_search.h"
#include "battle_panel_support.h"
#include "basic_pose.h"
#include "path_rotation.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "script_compare.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelMotionCreationAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static void store(unsigned reg,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(reg,v);memcpy(at(a),v,16);}
static void load(unsigned reg,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(reg,v);}
static void interval(uint32_t node,float frame,uint32_t out[3]){sdfMotGetKey(at(node),bits(frame),out);}
static void vec3(unsigned reg,uint32_t a){uint32_t v[4];memcpy(v,at(a),12);v[3]=(v[2]&0x80000000u)?UINT32_MAX:0;EE_ROT_VU_WRITE(reg,v);}
/* Native QMTC2 keeps the preceding PCPYLD's upper doubleword. */
static void linear(uint32_t rate,uint32_t highz,uint32_t highsign){
 uint32_t a[4],b[4],zero[4],r[4]={rate,(rate&0x80000000u)?UINT32_MAX:0,highz,highsign},three[4],acc[4],of[4];
 EE_ROT_VU_READ(10,a);EE_ROT_VU_READ(11,b);EE_ROT_VU_READ(0,zero);EE_ROT_VU_READ(3,three);
 EE_ROT_VU_WRITE(2,r);three[3]=(uint32_t)EE_ROT_VU_SUB(zero[3],rate);EE_ROT_VU_WRITE(3,three);
 for(unsigned k=0;k<4;k++){uint64_t v=EE_ROT_VU_MUL(b[k],rate);acc[k]=(uint32_t)v;of[k]=(uint32_t)(v>>32)&1;a[k]=(uint32_t)EE_ROT_VU_MAC(acc[k],a[k],three[3],of[k],0);}
 EE_ROT_ACC_WRITE(acc,of);EE_ROT_VU_WRITE(10,a);
}
static void interpolated(uint32_t key[3]){vec3(10,key[0]);vec3(11,key[1]);uint32_t b[4];EE_ROT_VU_READ(11,b);linear(key[2],b[2],b[3]);}
static void vector_node(uint64_t node,float frame,float rate,unsigned offset,int blend){
 uint32_t n=(uint32_t)node,key[3],b[4];interval(n,frame,key);interpolated(key);EE_ROT_VU_READ(11,b);
 if(blend){uint32_t v[4];EE_ROT_VU_READ(10,v);EE_ROT_VU_WRITE(11,v);load(10,n+16);linear(bits(rate),b[2],b[3]);}
 uint32_t v[4],z[4];EE_ROT_VU_READ(10,v);EE_ROT_VU_READ(0,z);v[3]=z[3];EE_ROT_VU_WRITE(10,v);store(10,word(n+12)+offset);
}
void sdfMotCLBK_modelLinerPosSeek(uint64_t n,float f){vector_node(n,f,0,0x60,0);}
void ps2MotionPositionBlend(uint64_t n,float f,float w){vector_node(n,f,w,0x60,1);}
void sdfMotCLBK_modelLinerScaleSeek(uint64_t n,float f){vector_node(n,f,0,0x70,0);}
void ps2MotionScaleBlend(uint64_t n,float f,float w){vector_node(n,f,w,0x70,1);}
/* 002C0160: original GP-relative quarter-turn constant, real sine body. */
uint32_t sdfCosBits(uint32_t angle){return sdfSinBits(EE_FPU_ADD_S(angle,word(0x54e774)));}
/* 002C0788: retail COP1 grouping retained; result in implicit VF10. */
void sdfQuatFromEuler(float x,float y,float z){
 uint32_t hx=EE_FPU_MUL_S(bits(x)^0x80000000u,0x3f000000u),hy=EE_FPU_MUL_S(bits(y)^0x80000000u,0x3f000000u),hz=EE_FPU_MUL_S(bits(z)^0x80000000u,0x3f000000u);
 uint32_t cx=sdfCosBits(hx),sx=sdfSinBits(hx),cy=sdfCosBits(hy),sy=sdfSinBits(hy),cz=sdfCosBits(hz),sz=sdfSinBits(hz);
 uint32_t a=EE_FPU_MUL_S(cz,cy),b=EE_FPU_MUL_S(cz,sy),c=EE_FPU_MUL_S(sz,cy),d=EE_FPU_MUL_S(sz,sy);
 uint32_t q[4]={EE_FPU_ADD_S(EE_FPU_MUL_S(d,cx),EE_FPU_MUL_S(a,sx)),EE_FPU_SUB_S(EE_FPU_MUL_S(b,cx),EE_FPU_MUL_S(c,sx)),EE_FPU_ADD_S(EE_FPU_MUL_S(c,cx),EE_FPU_MUL_S(b,sx)),EE_FPU_SUB_S(EE_FPU_MUL_S(a,cx),EE_FPU_MUL_S(d,sx))};
 EE_ROT_VU_WRITE(10,q);
}
static void rotation_store(uint32_t target){store(10,target+0x50);sdfQuatToMatrix();store(28,target+0x80);store(29,target+0x90);store(30,target+0xa0);}
/* The existing implicit-VU helper defines vector values. Its original COP1
 * dot-sign condition is also observable by these complete callback paths. */
static void blend_quaternion(float rate){
 uint32_t a[4],b[4],product[4];EE_ROT_VU_READ(10,a);EE_ROT_VU_READ(11,b);
 for(unsigned k=0;k<4;k++)product[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[k]);
 uint64_t v=EE_ROT_VU_ADD(product[0],product[1]);v=EE_ROT_VU_MAC((uint32_t)v,0x3f800000u,product[2],(uint32_t)(v>>32)&1,0);
 uint32_t dot=(uint32_t)EE_ROT_VU_MAC((uint32_t)v,0x3f800000u,product[3],(uint32_t)(v>>32)&1,0);
 (void)EE_FPU_COMPARE_S(dot,0,1);ps2QuaternionBlendNormalized(rate);
}
static void euler(uint64_t node,float frame,float rate,int blend){
 uint32_t n=(uint32_t)node,key[3],v[4],z[4];interval(n,frame,key);interpolated(key);EE_ROT_VU_READ(10,v);EE_ROT_VU_READ(0,z);v[3]=(uint32_t)EE_ROT_VU_MUL(v[3],z[0]);EE_ROT_VU_WRITE(10,v);
 sdfQuatFromEuler(real(v[0]),real(v[1]),real(v[2]));
 if(blend){EE_ROT_VU_READ(10,v);EE_ROT_VU_WRITE(11,v);load(10,n+16);blend_quaternion(rate);}
 rotation_store(word(n+12));
}
void ps2MotionEulerSeek(uint64_t n,float f){euler(n,f,0,0);}
void ps2MotionEulerBlend(uint64_t n,float f,float w){euler(n,f,w,1);}
static void packed_quaternion(unsigned reg,uint32_t a){int16_t h[4];uint32_t v[4];memcpy(h,at(a),8);for(unsigned k=0;k<4;k++)v[k]=(uint32_t)EE_ROT_VU_MUL(EE_FPU_CVT_S_W((uint32_t)(int32_t)h[k]),0x39800000u);EE_ROT_VU_WRITE(reg,v);}
static void quaternion(uint64_t node,float frame,float rate,int blend){
 uint32_t n=(uint32_t)node,key[3];interval(n,frame,key);packed_quaternion(10,key[0]);packed_quaternion(11,key[1]);blend_quaternion(real(key[2]));uint32_t target=word(n+12);
 if(blend){uint32_t v[4];EE_ROT_VU_READ(10,v);EE_ROT_VU_WRITE(11,v);load(10,n+16);blend_quaternion(rate);}
 rotation_store(target);
}
void ps2MotionQuaternionSeek(uint64_t n,float f){quaternion(n,f,0,0);}
void ps2MotionQuaternionBlend(uint64_t n,float f,float w){quaternion(n,f,w,1);}
static void visible(uint64_t node,float frame){uint32_t n=(uint32_t)node,key[3];interval(n,frame,key);uint8_t value=*at(key[0]);uint32_t target=word(n+12);uint16_t flags;memcpy(&flags,at(target+0x14),2);flags=value?(uint16_t)(flags&0xffefu):(uint16_t)(flags|0x10u);memcpy(at(target+0x14),&flags,2);}
void sdfMotCLBK_modelVisibleSeek(uint64_t n,float f){visible(n,f);}
void sdfMotCLBK_modelVisibleBlendSeek(uint64_t n,float f,float w){(void)w;visible(n,f);}

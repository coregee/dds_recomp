/* Original track-history/gradient constructors and packed-colour transition.
 * Parameter copies retain original read-before-write groups and field widths. */
#include "model_track_creation.h"
#include "model_motion_creation.h"
#include "model_cleanup.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "material_motion_scalars.h"
#include "ps2_memory.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "script_compare.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
void nocturneTrackFillConstantGradient(uint64_t data,uint32_t color);
uint64_t nocturneCreateNativeSpecialTrack(uint32_t model,uint32_t kind,uint32_t color,uint32_t rate);
void *nocturneResolveTrackDrawStateAddress(uint32_t address);
#endif
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 if(a>=0x56af00&&a<0x56af2c)return nocturneResolveTrackDrawStateAddress(a);
 return nocturneResolveModelMotionCreationAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void store(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void shalf(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t a){return (uint64_t)(int64_t)(int32_t)a;}
static uint32_t bits(float a){uint32_t v;memcpy(&v,&a,4);return v;}
static float real(uint32_t a){float v;memcpy(&v,&a,4);return v;}
/* LDL/LDR groups load all four doublewords before the corresponding stores. */
static void copy32(uint32_t dst,uint32_t src){uint8_t bytes[32];memcpy(bytes,at(src),32);memcpy(at(dst),bytes,32);}
static void copy16(uint32_t dst,uint32_t src){uint8_t bytes[16];memcpy(bytes,at(src),16);memcpy(at(dst),bytes,16);}
static void copy8(uint32_t dst,uint32_t src){uint8_t bytes[8];memcpy(bytes,at(src),8);memcpy(at(dst),bytes,8);}
static uint32_t mul(uint32_t a,uint32_t b){return (uint32_t)EE_ROT_VU_MUL(a,b);}
static void scalar(unsigned reg,uint32_t x){uint32_t v[4]={x,(x&0x80000000u)?UINT32_MAX:0,0,0};EE_ROT_VU_WRITE(reg,v);}
static void unpack(uint32_t color,uint32_t v[4]){for(unsigned k=0;k<4;k++)v[k]=mul(EE_FPU_CVT_S_W((color>>(8*k))&255),0x3c000000);}
uint64_t ps2TrackPolyAllocateHistory(uint64_t length,uint64_t steps){
 uint32_t count=((uint32_t)length*(uint32_t)steps)*2u+4u,bytes=count*20u;
 uint32_t handle=ps2MemoryHandleAllocate((int32_t)(bytes+40u)),base=ps2MemoryHandleAcquirePointer(handle),data=base+bytes;
 store(data+0x18,base);store(data+4,0x80808080);store(data+0x10,2);store(data,2);store(data+8,count);store(data+0x14,(uint32_t)steps);store(data+0x24,handle);store(data+0x1c,base+(count<<4));store(data+12,0);
 uint32_t material=ps2MatCreate();store(data+0x20,material);sdfMatSetConstant(at(material),0x3f800000);
 ps2Memset(at(0x56af00),0,0x2c);shalf(0x56af04,0x4000);store(0x56af0c,0x31ffe0);return sx(data);
}
void ps2TrackPolySetDrawKind(uint64_t data,uint64_t kind){store((uint32_t)data,(uint32_t)kind);}
uint64_t ps2EffectBlendColor(uint64_t first,uint64_t second,float amount){
 uint32_t t=bits(amount);if(EE_FPU_COMPARE_S(0x3f800000,t,2))return second;
 uint32_t a[4],b[4];unpack((uint32_t)second,a);EE_ROT_VU_WRITE(10,a);scalar(2,0x3c000000);EE_ROT_VU_WRITE(11,a);
 unpack((uint32_t)first,b);EE_ROT_VU_WRITE(10,b);scalar(2,0x3c000000);
 uint32_t reverse=EE_FPU_SUB_S(0x3f800000,t);scalar(2,reverse);for(unsigned k=0;k<4;k++)b[k]=mul(b[k],reverse);EE_ROT_VU_WRITE(10,b);
 scalar(2,t);for(unsigned k=0;k<4;k++)a[k]=mul(a[k],t);EE_ROT_VU_WRITE(11,a);
 for(unsigned k=0;k<4;k++)b[k]=(uint32_t)EE_ROT_VU_ADD(b[k],a[k]);EE_ROT_VU_WRITE(10,b);
 scalar(2,0x43000000);uint32_t result=0;for(unsigned k=0;k<4;k++){b[k]=mul(b[k],0x43000000);b[k]=EE_FPU_CVT_W_S(b[k]);result|=(b[k]&255)<<(8*k);}EE_ROT_VU_WRITE(10,b);return result;
}
void ps2TrackPolyFillGradient(uint64_t data,uint64_t gradient){
 uint32_t d=(uint32_t)data,g=(uint32_t)gradient,count=(uint32_t)((int32_t)word(d+8)>>1),denominator;
 if((int32_t)count<0){denominator=EE_FPU_CVT_S_W((count&1)|(count>>1));denominator=EE_FPU_ADD_S(denominator,denominator);}else denominator=EE_FPU_CVT_S_W(count);
 uint32_t step=EE_FPU_DIV_S(0x3f800000,denominator),t=0,out=word(d+0x1c);
 for(uint32_t k=0;k<count;k++,out+=8){store(out,(uint32_t)ps2EffectBlendColor(sx(word(g+8)),sx(word(g)),real(t)));uint32_t previous=t;t=EE_FPU_ADD_S(t,step);store(out+4,(uint32_t)ps2EffectBlendColor(sx(word(g+12)),sx(word(g+4)),real(previous)));}
}
uint64_t ps2SpecialTrackBundleCreate(uint64_t parameters){
 uint32_t p=(uint32_t)parameters,b=ps2PoolAllocate(0x34);copy32(b,p);copy8(b+32,p+32);store(b+0x28,0);
 uint32_t reciprocal=EE_FPU_DIV_S(0x3f800000,word(p+0x18)),steps=EE_FPU_CVT_W_S(reciprocal);
 uint32_t data=(uint32_t)ps2TrackPolyAllocateHistory(sx(word(p+0x14)),sx(steps));store(b+0x30,data);
 /* Four stack words are copied from the same native parameter load. */
 uint32_t color=word(p+0x20);
 /* The target's stack argument is represented by a temporary backed area in
  * the host adapter; canonical target builds use the actual local words. */
#if UINTPTR_MAX > UINT32_MAX
 nocturneTrackFillConstantGradient(sx(data),color);
#else
 uint32_t gradient[4]={color,color,color,color};ps2TrackPolyFillGradient(sx(data),(uintptr_t)gradient);
#endif
 ps2TrackPolySetDrawKind(sx(data),sx(word(p+0x1c)));return sx(b);
}
uint64_t ps2ModelTrackPolyCreate(uint64_t parameters){
 uint32_t p=(uint32_t)parameters,w=ps2PoolAllocate(0x3c);copy32(w,p);copy16(w+32,p+32);store(w+0x30,word(p+0x30));
 if(ps2ModelNeedsSpecialRelease(sx(word(w)))){
  uint64_t cut=ps2ModelActiveMotionCut(sx(word(p)),0);uint32_t kind,color;
  if(cut==10){kind=6;color=0x80c8c8c8;}else if(cut==9){kind=5;color=0xc0c0c0c0;}else if(cut==17){kind=5;color=0xb8a8a8a8;}else if(cut==18){kind=7;color=0xc8c8c8c8;}else{kind=6;color=0xb8b8b8b8;}
  /* Native local parameter record is adapted without replacing its consumers. */
#if UINTPTR_MAX > UINT32_MAX
  uint64_t bundle=nocturneCreateNativeSpecialTrack(word(p),kind,color,word(0x54c9f0));
#else
  uint32_t record[10];record[0]=word(p);record[1]=101;record[2]=100;record[3]=8;record[4]=200;record[5]=kind;record[6]=word(0x54c9f0);record[7]=1;record[8]=color;
  /* Word9 is original untouched private-frame padding, copied as raw bytes. */
  uint64_t bundle=ps2SpecialTrackBundleCreate((uintptr_t)record);
#endif
  store(w+0x38,(uint32_t)bundle);
 }else{
  store(w+0x34,0);store(w+0x1c,6);uint32_t data=(uint32_t)ps2TrackPolyAllocateHistory(sx(word(w+0x18)),6);store(w+0x38,data);ps2TrackPolyFillGradient(sx(data),sx(p+0x24));ps2TrackPolySetDrawKind(sx(word(w+0x38)),sx(word(p+0x20)));
 }
 return sx(w);
}
void ps2ModelCreateColorTransition(uint64_t model,uint64_t frames,uint64_t count,uint64_t end,uint64_t start){
 uint32_t m=(uint32_t)model;mdlFreeBlur(model);if((int64_t)count<=0)return;
 uint32_t d=ps2PoolAllocateZeroed(0x30),product=(uint32_t)count*(uint32_t)frames,denom=EE_FPU_CVT_S_W(product),step=EE_FPU_DIV_S(0x3f800000,denom);
 shalf(d+10,1);store(d+12,product);store(m+0x30,d);shalf(d+4,(uint16_t)count);shalf(d+6,(uint16_t)count);shalf(d+8,(uint16_t)frames);
 uint32_t a[4],b[4];unpack((uint32_t)start,a);scalar(2,0x3c000000);EE_ROT_VU_WRITE(10,a);memcpy(at(d+16),a,16);EE_ROT_VU_WRITE(11,a);
 unpack((uint32_t)end,b);scalar(2,0x3c000000);EE_ROT_VU_WRITE(10,b);for(unsigned k=0;k<4;k++)b[k]=(uint32_t)EE_ROT_VU_SUB(b[k],a[k]);EE_ROT_VU_WRITE(10,b);scalar(2,step);for(unsigned k=0;k<4;k++)b[k]=mul(b[k],step);EE_ROT_VU_WRITE(10,b);memcpy(at(d+32),b,16);
}
void ps2ModelCreateColorTransitionRecord(uint64_t model,uint64_t record,uint64_t slot){(void)slot;uint32_t r=(uint32_t)record;uint32_t start=word(r+16),frames=half(r+8),count=half(r+10),end=word(r+12);ps2ModelCreateColorTransition(model,frames,count,sx(end),sx(start));}

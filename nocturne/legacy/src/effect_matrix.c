/* Complete SLUS_209.11 matrix consumers. Raw VU words and ACC overflow are
 * retained; managed Matrix4x4 operations are semantic reference only. */
#include "effect_matrix.h"
#include "ee_vu_rotation.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolveEffectMatrixAddress(a);}
static void call(uint32_t target,uint64_t object,uint64_t matrix){nocturneEffectMatrixCall(target,object,matrix);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
static void call(uint32_t target,uint64_t object,uint64_t matrix){((void (*)(uint64_t,uint64_t))(uintptr_t)target)(object,matrix);}
#endif
static uint32_t read32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t read16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t sx(uint32_t a){return (uint64_t)(int64_t)(int32_t)a;}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void loadMatrix(uint32_t a){for(unsigned k=0;k<4;k++)load(28+k,a+k*16);}
static void storeMatrix(uint32_t a){for(unsigned k=0;k<4;k++)store(28+k,a+k*16);}

void sdfMultiplyEffectVuMatrices(void){
 uint32_t left[4][4],right[4],result[4],acc[4],overflow[4];
 for(unsigned k=0;k<4;k++)EE_ROT_VU_READ(28+k,left[k]);
 for(unsigned row=0;row<4;row++){
  EE_ROT_VU_READ(24+row,right);
  for(unsigned lane=0;lane<4;lane++){
   uint64_t v=EE_ROT_VU_MUL(left[0][lane],right[0]);
   acc[lane]=(uint32_t)v;overflow[lane]=(uint32_t)(v>>32)&1;
  }
  EE_ROT_ACC_WRITE(acc,overflow);
  for(unsigned k=1;k<3;k++){
   for(unsigned lane=0;lane<4;lane++){
    uint64_t v=EE_ROT_VU_MAC(acc[lane],left[k][lane],right[k],overflow[lane],0);
    acc[lane]=(uint32_t)v;overflow[lane]=(uint32_t)(v>>32)&1;
   }
   EE_ROT_ACC_WRITE(acc,overflow);
  }
  for(unsigned lane=0;lane<4;lane++)result[lane]=(uint32_t)EE_ROT_VU_MAC(acc[lane],left[3][lane],right[3],overflow[lane],0);
  EE_ROT_VU_WRITE(row==3?31:2+row,result);
 }
 for(unsigned k=0;k<3;k++){EE_ROT_VU_READ(2+k,result);EE_ROT_VU_WRITE(28+k,result);}
}

void ps2ParticleSetMatrix(uint64_t object,uint64_t matrix){
 ENTER(16);uint32_t p=(uint32_t)object;loadMatrix((uint32_t)matrix);
 for(unsigned k=0;k<4;k++)load(24+k,p+0x100+k*16);
 sdfMultiplyEffectVuMatrices();storeMatrix(p+0xb0);LEAVE(16);
}
void ps2ExpParticleSetMatrix(uint64_t object,uint64_t matrix){ps2ParticleSetMatrix(object,matrix);}
void ps2SpecialPolygonSetMatrix(uint64_t object,uint64_t matrix){
 ENTER(16);uint32_t p=(uint32_t)object;loadMatrix((uint32_t)matrix);
 for(unsigned k=0;k<4;k++)load(24+k,p+0x70+k*16);
 sdfMultiplyEffectVuMatrices();storeMatrix(p+0x20);LEAVE(16);
}
void ps2TrackType2SetMatrix(uint64_t object,uint64_t matrix){loadMatrix((uint32_t)matrix);storeMatrix((uint32_t)object);}
void ps2TrackType3SetMatrix(uint64_t object,uint64_t matrix){loadMatrix((uint32_t)matrix);storeMatrix((uint32_t)object);}
void ps2TrackType4SetMatrix(uint64_t object,uint64_t matrix){loadMatrix((uint32_t)matrix);storeMatrix((uint32_t)object);}
void ps2MaterialBillboardSetMatrix(uint64_t object,uint64_t matrix){loadMatrix((uint32_t)matrix);storeMatrix((uint32_t)object+0x40);}
void ps2ModelPartSetMatrix(uint64_t object,uint64_t matrix){
 uint32_t p=(uint32_t)object;loadMatrix((uint32_t)matrix);
 /* Reload the root after each store: a destination may alias context+18. */
 for(unsigned k=0;k<3;k++)store(28+k,read32(p+0x18)+0x20+k*16);
}
void ps2TrackBundleSetMatrix(uint64_t object,uint64_t matrix){
 ENTER(16);uint32_t p=(uint32_t)object,target=read32(0x320054+read32(p)*24);
 if(target)call(target,sx(read32(p+4)),matrix);LEAVE(16);
}
void ps2EffectPartSetMatrix(uint64_t object,uint64_t matrix){
 ENTER(16);uint32_t p=(uint32_t)object,target=read32(0x31de58+read16(p)*40);
 if(target)call(target,sx(read32(p+4)),matrix);LEAVE(16);
}
void ps2PcpWrapperSetMatrix(uint64_t object,uint64_t matrix){
 ENTER(16);uint32_t p=(uint32_t)object,target=read32(0x31dfa8+read32(p)*40);
 if(target)call(target,sx(read32(p+8)),matrix);LEAVE(16);
}
void ps2EffectSetMatrix(uint64_t object,uint64_t matrix){
 ENTER(16);uint32_t p=(uint32_t)object,target=read32(0x316f08+read32(p)*48);
 call(target,sx(read32(p+8)),matrix);LEAVE(16);
}

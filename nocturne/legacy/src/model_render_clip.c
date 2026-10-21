/* Four original point/light/clip loops, including final-record prefetch. */
#include "model_render_clip.h"
#include "ee_vu_rotation.h"
#include "ee_vu_clip.h"
#include "ee_vu_minmax.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveRenderClipAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void byte(uint32_t a,uint32_t v){uint8_t x=(uint8_t)v;memcpy(at(a),&x,1);}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void packed(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),8);v[2]=word(a+8);v[3]=v[2]&0x80000000u?UINT32_MAX:0;EE_RENDER_CLIP_PACKED_TO_VU(r,v);}
static void load64(unsigned r,unsigned gpr,uint32_t a){uint64_t low;memcpy(&low,at(a),8);EE_RENDER_CLIP_LD_TO_VU(r,gpr,low);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void acc(unsigned fs,unsigned ft,unsigned bc,unsigned mask,unsigned add){
 uint32_t a[4],b[4],v[4],of[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t x=add?EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],0):EE_ROT_VU_MUL(a[k],b[bc]);v[k]=(uint32_t)x;of[k]=(uint32_t)(x>>32)&1;}EE_ROT_ACC_WRITE(v,of);
}
static void addAcc(unsigned fs,unsigned ft,unsigned bc,unsigned mask){
 uint32_t a[4],b[4],v[4],of[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t x=EE_ROT_VU_ADD(a[k],b[bc]);v[k]=(uint32_t)x;of[k]=(uint32_t)(x>>32)&1;}EE_ROT_ACC_WRITE(v,of);
}
static void mac(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask,unsigned sub){
 uint32_t a[4],b[4],v[4],of[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],sub);EE_ROT_VU_WRITE(fd,out);
}
static void mul(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask){
 uint32_t a[4],b[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[bc]);EE_ROT_VU_WRITE(fd,out);
}
static void minmaxW(unsigned ft,unsigned bc,unsigned minimum){uint32_t v[4],b[4];EE_ROT_VU_READ(8,v);EE_ROT_VU_READ(ft,b);v[3]=EE_VU_MINMAX_BITS(v[3],b[bc],minimum);EE_ROT_VU_WRITE(8,v);}
static void setup(void){load(19,0x58f030);load(20,0x58f040);load(21,0x58f050);for(unsigned r=24;r<=26;r++)mul(r,19,r,0,1);}
static void transform(void){
 acc(0,19,1,1,0);acc(24,6,0,1,1);acc(25,6,1,1,1);mac(7,26,6,2,1,0);
 acc(28,2,0,15,0);acc(29,2,1,15,1);acc(30,2,2,15,1);mac(3,31,0,3,15,0);
 addAcc(7,7,3,1);mac(6,0,0,3,1,1);
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(7,a);EE_ROT_VU_READ(0,b);EE_ROT_VU_READ(8,v);v[3]=EE_VU_MINMAX_BITS(a[3],b[0],0);EE_ROT_VU_WRITE(8,v);EE_VU_CLIP(3,3);
}
static void clipAxis(void){uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(0,a);EE_ROT_VU_READ(6,b);EE_ROT_VU_READ(9,v);v[0]=(uint32_t)EE_ROT_VU_ADD(a[0],b[3]);EE_ROT_VU_WRITE(9,v);}
static void light(void){acc(20,0,3,15,0);mac(8,21,8,3,15,0);}
static void uvMatrix(uint32_t a){load64(16,2,a);load64(17,3,a+8);load64(18,2,a+16);}
void ps2RenderLightClipPacked(uint64_t output,uint64_t count,uint64_t positions,uint64_t normals){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,pos=(uint32_t)positions,normal=(uint32_t)normals;setup();
 do{
  packed(6,normal);normal+=12;packed(2,pos);pos+=12;transform();store(3,p);--n;clipAxis();minmaxW(0,3,1);store(6,p+16);p+=96;
  acc(20,0,3,15,0);uint32_t first=EE_VU_CLIP_READ();mac(8,21,8,3,15,0);EE_VU_CLIP(9,0);store(8,p-64);byte(p-15,first);byte(p-16,EE_VU_CLIP_READ()&3);
 }while(n);
}
void ps2RenderLightClipRecords(uint64_t output,uint64_t count){
 uint32_t p=(uint32_t)output,n=(uint32_t)count;setup();load(6,p+16);load(2,p);
 do{
  transform();store(3,p);--n;clipAxis();minmaxW(0,3,1);store(6,p+16);p+=96;
  acc(20,0,3,15,0);uint32_t first=EE_VU_CLIP_READ();mac(8,21,8,3,15,0);EE_VU_CLIP(9,0);
  /* Original prefetch runs before current light/flag stores, even last. */
  load(6,p+16);load(2,p);store(8,p-64);byte(p-15,first);byte(p-16,EE_VU_CLIP_READ()&3);
 }while(n);
}
void ps2RenderLightClipPackedUV(uint64_t output,uint64_t count,uint64_t positions,uint64_t normals,uint64_t uv,uint64_t matrix){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,pos=(uint32_t)positions,normal=(uint32_t)normals,t=(uint32_t)uv;setup();uvMatrix((uint32_t)matrix);
 do{
  packed(6,normal);normal+=12;packed(2,pos);pos+=12;
  acc(0,19,1,1,0);acc(24,6,0,1,1);acc(25,6,1,1,1);mac(7,26,6,2,1,0);load64(4,2,t);t+=8;
  acc(28,2,0,15,0);acc(29,2,1,15,1);acc(30,2,2,15,1);mac(3,31,0,3,15,0);addAcc(7,7,3,1);mac(6,0,0,3,1,1);
  uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(7,a);EE_ROT_VU_READ(0,b);EE_ROT_VU_READ(8,v);v[3]=EE_VU_MINMAX_BITS(a[3],b[0],0);EE_ROT_VU_WRITE(8,v);EE_VU_CLIP(3,3);
  acc(16,4,0,12,0);clipAxis();acc(17,4,1,12,1);minmaxW(0,3,1);mac(5,18,0,3,12,0);uint32_t first=EE_VU_CLIP_READ();EE_VU_CLIP(9,0);light();
  store(3,p);store(6,p+16);store(5,p+48);store(8,p+32);byte(p+81,first);uint32_t second=EE_VU_CLIP_READ();p+=96;--n;byte(p-16,second&3);
 }while(n);
}
void ps2RenderLightClipRecordsUV(uint64_t output,uint64_t count,uint64_t uv,uint64_t matrix){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,t=(uint32_t)uv;setup();uvMatrix((uint32_t)matrix);
 do{
  load(6,p+16);load(2,p);load64(4,2,t);t+=8;transform();acc(16,4,0,12,0);clipAxis();acc(17,4,1,12,1);minmaxW(0,3,1);mac(5,18,0,3,12,0);
  uint32_t first=EE_VU_CLIP_READ();EE_VU_CLIP(9,0);light();store(3,p);store(6,p+16);store(5,p+48);store(8,p+32);byte(p+81,first);uint32_t second=EE_VU_CLIP_READ();p+=96;--n;byte(p-16,second&3);
 }while(n);
}

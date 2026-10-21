/* Original clipped edge/UV/colour loops and DMA packet finalization. */
#include "model_render_packet_support.h"
#include "ee_vu_rotation.h"
#include "ee_vu_clip.h"
#include "ee_vu_minmax.h"
#include "ee_fpu.h"
#include "deferred_drain.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveRenderPacketAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static void sb(uint32_t a,uint32_t v){uint8_t b=(uint8_t)v;memcpy(at(a),&b,1);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void load64(unsigned r,unsigned gpr,uint32_t a){uint64_t v;memcpy(&v,at(a),8);EE_RENDER_PACKET_LD_TO_VU(r,gpr,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void acc(unsigned fs,unsigned ft,unsigned bc,unsigned mask,unsigned add){
 uint32_t a[4],b[4],v[4],of[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t x=add?EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],0):EE_ROT_VU_MUL(a[k],b[bc]);v[k]=(uint32_t)x;of[k]=(uint32_t)(x>>32)&1;}EE_ROT_ACC_WRITE(v,of);
}
static void mac(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask,unsigned sub){
 uint32_t a[4],b[4],v[4],of[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],sub);EE_ROT_VU_WRITE(fd,out);
}
static void mul(unsigned fd,unsigned fs,unsigned ft,int bc,unsigned mask){
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,v);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))v[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[bc<0?k:(unsigned)bc]);EE_ROT_VU_WRITE(fd,v);
}
static void sub(unsigned fd,unsigned fs,unsigned ft,int bc,unsigned mask){
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,v);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))v[k]=(uint32_t)EE_ROT_VU_SUB(a[k],b[bc<0?k:(unsigned)bc]);EE_ROT_VU_WRITE(fd,v);
}
static void add(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask){
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,v);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))v[k]=(uint32_t)EE_ROT_VU_ADD(a[k],b[bc]);EE_ROT_VU_WRITE(fd,v);
}
static void clampW(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned minimum){
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,v);v[3]=EE_VU_MINMAX_BITS(a[3],b[bc],minimum);EE_ROT_VU_WRITE(fd,v);
}
static void copyColourList(uint32_t p){
 while(p){uint32_t source=word(p+68)+32,v[4];memcpy(v,at(source),16);EE_RENDER_PACKET_CPU_QUAD(2,v);memcpy(at(p+32),v,16);p=word(p+64);}
}
void ps2RenderRelightRecords(uint64_t output,uint64_t count){
 uint32_t p=(uint32_t)output,n=(uint32_t)count;load(19,0x58f030);load(20,0x58f040);load(21,0x58f050);
 for(unsigned r=24;r<=26;r++)mul(r,19,r,0,1);
 do{
  load(6,p+16);sub(6,0,6,-1,14);acc(0,19,1,1,0);acc(24,6,0,1,1);acc(25,6,1,1,1);mac(7,26,6,2,1,0);
  uint32_t a[4],v[4],of[4];EE_ROT_VU_READ(7,a);EE_ROT_ACC_READ(v,of);uint64_t sum=EE_ROT_VU_ADD(a[3],a[3]);v[3]=(uint32_t)sum;of[3]=(uint32_t)(sum>>32)&1;EE_ROT_ACC_WRITE(v,of);
  mac(6,0,0,3,1,1);clampW(8,7,0,0,0);add(9,0,6,3,8);clampW(8,8,0,3,1);EE_VU_CLIP(9,0);store(6,p+16);
  acc(20,0,3,15,0);mac(8,21,8,3,15,0);uint32_t flags=EE_VU_CLIP_READ();store(8,p+32);p+=96;--n;sb(p-16,flags&3);
 }while(n);
}
void ps2RenderTransformUVRecords(uint64_t output,uint64_t count,uint64_t uv,uint64_t matrix){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,t=(uint32_t)uv,m=(uint32_t)matrix;
 load64(16,2,m);load64(17,3,m+8);load64(18,2,m+16);load64(2,2,t);
 acc(18,0,3,12,0);acc(16,2,0,12,1);mac(3,17,2,1,12,0);
 do{
  t+=8;load64(2,2,t);uint32_t v[4];EE_ROT_VU_READ(3,v);EE_RENDER_PACKET_CPU_QUAD(2,v);
  acc(18,0,3,12,0);acc(16,2,0,12,1);mac(3,17,2,1,12,0);--n;p+=96;sd(p-48,(uint64_t)v[0]|((uint64_t)v[1]<<32));
 }while(n);
}
static void clipped(uint32_t p,unsigned colour){
 while(p){
  uint32_t first=word(p+68),second=word(p+72);load(2,p+64);load(8,first+48);load(9,second+48);
  if(colour){load(10,first+32);load(11,second+32);}
  acc(8,0,3,12,0);acc(9,2,3,12,1);mac(15,8,2,3,12,1);
  if(colour){acc(10,0,3,15,0);acc(11,2,3,15,1);mac(16,10,2,3,15,1);}
  store(15,p+48);if(colour)store(16,p+32);p=word(p+64);
 }
}
void ps2RenderInterpolateClippedUV(uint64_t head){clipped((uint32_t)head,0);}
void ps2RenderInterpolateClippedUVColour(uint64_t head){clipped((uint32_t)head,1);}
void ps2RenderRebuildRecordColours(uint64_t context,uint64_t lighting){
 uint32_t c=(uint32_t)context,p,n;sub(12,0,0,-1,15);load(10,(uint32_t)lighting+16);load(11,(uint32_t)lighting+32);
 EE_RENDER_PACKET_WORD_TO_VU(2,2,0x3f000000);add(12,12,2,0,15);p=word(c+100);n=(uint32_t)(int32_t)(int16_t)half(c+66);load(2,p+16);
 acc(12,0,3,1,0);mac(3,2,12,3,1,0);
 do{
  clampW(4,3,0,0,0);p+=96;load(2,p+16);clampW(5,4,0,3,1);acc(12,0,3,1,0);mac(3,2,12,3,1,0);
  acc(10,0,3,15,0);mac(6,11,5,3,15,0);--n;store(6,p-64);
 }while(n);
 copyColourList(word(c+120));
}
void ps2RenderFillRecordColours(uint64_t context,uint64_t colour){
 uint32_t c=(uint32_t)context,first=word(c+88),second=(uint32_t)colour,a[4],b[4],rawA[4],rawB[4];
 for(unsigned k=0;k<4;k++){rawA[k]=(first>>(k*8))&255;rawB[k]=(second>>(k*8))&255;a[k]=EE_FPU_CVT_S_W(rawA[k]);b[k]=EE_FPU_CVT_S_W(rawB[k]);}
 EE_RENDER_PACKET_CPU_QUAD(2,rawA);EE_RENDER_PACKET_CPU_QUAD(3,rawB);EE_ROT_VU_WRITE(2,a);EE_ROT_VU_WRITE(3,b);EE_RENDER_PACKET_WORD_TO_VU(4,7,0x3c000000);mul(2,2,3,-1,15);mul(2,2,4,0,15);
 uint32_t v[4];EE_ROT_VU_READ(2,v);EE_RENDER_PACKET_CPU_QUAD(4,v);uint32_t n=(uint32_t)(int32_t)(int16_t)half(c+66),p=word(c+100);
 if(n)do{--n;memcpy(at(p+32),v,16);p+=96;}while(n);
 copyColourList(word(c+120));
}
void ps2RenderInterpolateClippedEdge(uint64_t output,uint64_t first,uint64_t second){
 uint32_t p=(uint32_t)output,a=(uint32_t)first,b=(uint32_t)second;sw(p+68,a);sw(p+72,b);add(2,0,0,0,1);uint8_t flags;memcpy(&flags,at(a+80),1);
 load(4,a+16);load(5,b+16);load(6,a);if(!(flags&1))sub(2,1,0,3,1);load(7,b);load(8,a+48);load(9,b+48);
 sub(12,2,4,3,1);sub(13,5,4,3,1);sub(14,7,6,-1,15);uint32_t left[4],right[4];EE_ROT_VU_READ(12,left);EE_ROT_VU_READ(13,right);uint32_t q=EE_RENDER_PACKET_DIV(left[3],right[3]);EE_ROT_Q_WRITE(q);
 load(10,a+32);sub(15,9,8,-1,15);acc(6,0,3,15,0);store(10,p+32);
 uint32_t accv[4],of[4],out[4],delta[4];EE_ROT_ACC_READ(accv,of);EE_ROT_VU_READ(14,out);memcpy(delta,out,16);for(unsigned k=0;k<4;k++)out[k]=(uint32_t)EE_ROT_VU_MAC(accv[k],delta[k],q,of[k],0);EE_ROT_VU_WRITE(14,out);
 acc(8,0,3,15,0);EE_ROT_ACC_READ(accv,of);EE_ROT_VU_READ(15,out);memcpy(delta,out,16);for(unsigned k=0;k<2;k++)out[k]=(uint32_t)EE_ROT_VU_MAC(accv[k],delta[k],q,of[k],0);EE_ROT_VU_WRITE(15,out);
 store(14,p);sw(p+76,q);store(15,p+48);store(2,p+16);
}
uint64_t ps2RenderFinalizePacket(uint64_t context){
 uint32_t c=(uint32_t)context,base=word(c+128);if(!base)return 0;uint32_t end=word(c+140),start=word(c+136);
 if(end==start){ps2WorkBufferSetCursor(base);return 0;}
 while(end&12){sw(end,0);end+=4;}
 uint32_t count=(uint32_t)((int32_t)(end-start)>>4),zero[4]={0,0,0,0};
 while(end&48){memcpy(at(end),zero,16);EE_RENDER_PACKET_CPU_QUAD(2,zero);end+=16;}
 ps2WorkBufferSetCursor(end&0x0fffffff);uint32_t packet=word(c+132);sd(packet+8,UINT64_C(0x1100000000000000));sd(packet,0x20000000u|(count&65535));return sx(packet);
}

/* Original triangle classification, split topology and connected packet builder. */
#include "model_render_clipping.h"
#include "model_render_packet_support.h"
#include "model_render_emission.h"
#include "model_render_context.h"
#include "resource_loader_flow.h"
#include "deferred_drain.h"
#include "ee_vu_rotation.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolveRenderClippingAddress(a);}
static uint32_t frame(void){return nocturneRenderClippingFrameAddress();}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint8_t byte(uint32_t a){uint8_t v;memcpy(&v,at(a),1);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void sub(unsigned fd,unsigned fs,unsigned ft){
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,v);
 for(unsigned k=0;k<3;k++)v[k]=(uint32_t)EE_ROT_VU_SUB(a[k],b[k]);EE_ROT_VU_WRITE(fd,v);
}
static uint32_t winding(uint32_t p0,uint32_t p1,uint32_t p2,uint32_t scale){
 load(2,p0);load(3,p1);load(4,p2);sub(2,2,3);sub(4,4,3);sub(3,21,3);
 uint32_t a[4],b[4],ac[4],of[4],v[4];EE_ROT_VU_READ(2,a);EE_ROT_VU_READ(4,b);EE_ROT_ACC_READ(ac,of);
 for(unsigned k=0;k<3;k++){uint64_t x=EE_ROT_VU_MUL(a[(k+1)%3],b[(k+2)%3]);ac[k]=(uint32_t)x;of[k]=(uint32_t)(x>>32)&1;}EE_ROT_ACC_WRITE(ac,of);
 memcpy(v,a,16);for(unsigned k=0;k<3;k++)v[k]=(uint32_t)EE_ROT_VU_MAC(ac[k],b[(k+1)%3],a[(k+2)%3],of[k],1);EE_ROT_VU_WRITE(2,v);
 EE_ROT_VU_READ(3,b);for(unsigned k=0;k<3;k++)v[k]=(uint32_t)EE_ROT_VU_MUL(v[k],b[k]);EE_ROT_VU_WRITE(2,v);
 uint64_t x=EE_ROT_VU_ADD(v[0],v[1]);ac[0]=(uint32_t)x;of[0]=(uint32_t)(x>>32)&1;EE_ROT_ACC_WRITE(ac,of);
 EE_ROT_VU_READ(1,b);v[0]=(uint32_t)EE_ROT_VU_MAC(ac[0],b[0],v[2],of[0],0);EE_ROT_VU_WRITE(2,v);EE_RENDER_CLIPPING_CPU_QUAD(2,v);
 return EE_FPU_COMPARE_S(EE_FPU_MUL_S(v[0],scale),0,1);
}
static void setup(unsigned gpr){
 EE_RENDER_CLIPPING_LD_TO_VU(2,gpr,sx(word(0x5520e0)));load(21,0x529790);load(22,0x5296e0);load(23,0x5296f0);
 uint32_t a[4],b[4];EE_ROT_VU_READ(23,a);EE_ROT_VU_READ(2,b);a[0]=(uint32_t)EE_ROT_VU_ADD(a[0],b[2]);EE_ROT_VU_WRITE(23,a);
}
/* Each next capacity is prefetched before the preceding link stores. The last
 * node updates the tail slot before writing the link; intermediate nodes do
 * the reverse. These orders matter when fields and records overlap. */
static void allocate(uint32_t c,uint32_t nodes[4],unsigned count){
 uint32_t remaining=word(c+112)-1,record=word(c+104);sw(c+112,remaining);
 for(unsigned k=0;k<count;k++){
  nodes[k]=record;
  if(!remaining){uint32_t next=word(c+108),capacity=word(c+116);sw(c+104,next);sw(c+112,capacity);}else sw(c+104,record+96);
  uint32_t tail=word(c+124);
  if(k+1==count){sw(c+124,record+64);sw(tail,record);}
  else{remaining=word(c+112)-1;sw(tail,record);sw(c+124,record+64);sw(c+112,remaining);record=word(c+104);}
 }
}
static uint32_t split(uint32_t c,uint32_t out,uint32_t p0,uint32_t p1,uint32_t p2,uint32_t override){
 uint32_t b0=byte(p0+80),b1=byte(p1+80),b2=byte(p2+80),n[4];
 if(override||(b0==b1&&b0==b2)){sw(out,p0);sw(out+4,p1);sw(out+8,p2);return out+12;}
 for(;;){
  if(b1==b2)break;
  if(!b0&&(b1^b2)==3){
   allocate(c,n,4);ps2RenderInterpolateClippedEdge(sx(n[0]),sx(p1),sx(p0));ps2RenderInterpolateClippedEdge(sx(n[1]),sx(p2),sx(p0));ps2RenderInterpolateClippedEdge(sx(n[2]),sx(p1),sx(p2));ps2RenderInterpolateClippedEdge(sx(n[3]),sx(p2),sx(p1));
   sw(out,p0);sw(out+16,p1);sw(out+28,n[0]);sw(out+40,n[2]);sw(out+48,n[1]);sw(out+52,n[3]);sw(out+56,p2);sw(out+4,n[0]);sw(out+8,n[1]);sw(out+12,n[0]);sw(out+20,n[2]);sw(out+24,n[1]);sw(out+32,n[2]);sw(out+36,n[1]);sw(out+44,n[3]);return out+60;
  }
  uint32_t p=p0,b=b0;p0=p1;p1=p2;p2=p;b0=b1;b1=b2;b2=b;
 }
 allocate(c,n,2);uint32_t a=n[0],b=n[1];
 if(!b0){
  ps2RenderInterpolateClippedEdge(sx(a),sx(p1),sx(p0));ps2RenderInterpolateClippedEdge(sx(b),sx(p2),sx(p0));
  sw(out,p0);sw(out+16,a);sw(out+24,b);sw(out+28,p1);sw(out+32,p2);sw(out+4,a);sw(out+8,b);sw(out+12,b);sw(out+20,p1);return out+36;
 }
 ps2RenderInterpolateClippedEdge(sx(a),sx(p0),sx(p1));ps2RenderInterpolateClippedEdge(sx(b),sx(p0),sx(p2));sw(out,p0);sw(out+4,a);sw(out+8,b);out+=12;
 if(!b1){sw(out+8,a);sw(out+12,p1);sw(out+16,p2);sw(out+20,b);sw(out,p1);sw(out+4,b);return out+24;}
 allocate(c,n,2);uint32_t d=n[0],e=n[1];ps2RenderInterpolateClippedEdge(sx(d),sx(p1),sx(p0));ps2RenderInterpolateClippedEdge(sx(e),sx(p2),sx(p0));
 sw(out,b);sw(out+4,a);sw(out+12,b);sw(out+28,d);sw(out+36,e);sw(out+40,p1);sw(out+44,p2);sw(out+8,d);sw(out+16,d);sw(out+20,e);sw(out+24,e);sw(out+32,p1);return out+48;
}
static void terminate(uint32_t c,uint32_t out,unsigned deferred,uint32_t count){
 uint32_t triangles=(uint32_t)((int32_t)(out-0x581030)>>2)*0xaaaaaaabu,tail=word(c+124);
 if(deferred)sh(c+82,count);sh(c+80,triangles);sw(tail,0);
}
void ps2RenderBuildDeferredTriangles(uint64_t context){
 ENTER(128);uint32_t c=(uint32_t)context,out=0x581030,override=byte(0x55189c),scale=word(c+172);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t f=frame();
#else
 uint32_t locals[6];uint32_t f=(uint32_t)(uintptr_t)locals;
#endif
 sw(f+16,0);sw(f,(uint32_t)(int32_t)(int16_t)half(c+64));sw(f+20,override);sw(f+4,0);sw(f+8,word(c+148));sw(f+12,word(c+100));
 if(word(f))do{
  uint32_t index=word(f+8),i1=half(index+2),i2=half(index+4),i0=half(index);sw(f+8,index+6);uint32_t base=word(f+12),p0=base+i0*96,p1=base+i1*96,p2=base+i2*96;
  uint32_t b1=byte(p1+81),b2=byte(p2+81),b0=byte(p0+81);
  if(!((b0&b1&b2)&63)&&!((b0|b1|b2)&48)){
   if(winding(p0,p1,p2,scale)){uint32_t n=word(f+16);sw(f+16,n+1);sh(0x58d030+n*2,word(f+4));}
   else out=split(c,out,p0,p1,p2,word(f+20));
  }
  uint32_t ordinal=word(f+4)+1,count=word(f);sw(f+4,ordinal);if(ordinal==count)break;
 }while(1);
 terminate(c,out,1,word(f+16));LEAVE(128);
}
void ps2RenderBuildFrontTriangles(uint64_t context){
 ENTER(112);uint32_t c=(uint32_t)context,out=0x581030,scale=word(c+172);setup(2);if(word(c+68)&0x4000)ps2RenderBuildDeferredTriangles(context);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t f=frame();
#else
 uint32_t locals[4];uint32_t f=(uint32_t)(uintptr_t)locals;
#endif
 uint32_t count=(uint32_t)(int32_t)(int16_t)half(c+64),override=byte(0x55189c);sw(f,count);sw(f+12,override);sw(f+4,word(c+148));sw(f+8,word(c+100));
 if(word(f))do{
  uint32_t index=word(f+4),i1=half(index+2),i2=half(index+4),i0=half(index);sw(f+4,index+6);uint32_t base=word(f+8),p0=base+i0*96,p1=base+i1*96,p2=base+i2*96;
  uint32_t b1=byte(p1+81),b2=byte(p2+81),b0=byte(p0+81);
  if(!((b0&b1&b2)&63)&&!((b0|b1|b2)&48)&&!winding(p0,p1,p2,scale))out=split(c,out,p0,p1,p2,word(f+12));
  count=word(f)-1;sw(f,count);
 }while(count);
 terminate(c,out,0,0);LEAVE(112);
}
void ps2RenderBuildBackTriangles(uint64_t context){
 ENTER(112);uint32_t c=(uint32_t)context,out=0x581030;setup(4);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t f=frame();
#else
 uint32_t locals[5];uint32_t f=(uint32_t)(uintptr_t)locals;
#endif
 sw(f+16,byte(0x55189c));sw(f,(uint32_t)(int32_t)(int16_t)half(c+82));sw(f+8,0x58d030);sw(f+4,word(c+148));sw(f+12,word(c+100));
 uint32_t count=word(f);if(count)do{
  uint32_t cursor=word(f+8),indexBase=word(f+4),ordinal=half(cursor);sw(f+8,cursor+2);uint32_t index=indexBase+ordinal*6,i2=half(index+4),i1=half(index+2),i0=half(index),base=word(f+12);
  out=split(c,out,base+i0*96,base+i1*96,base+i2*96,word(f+16));count=word(f)-1;sw(f,count);
 }while(count);
 terminate(c,out,0,0);LEAVE(112);
}
void ps2RenderBuildPacket(uint64_t context){
 ENTER(64);uint32_t c=(uint32_t)context,cursor=ps2WorkBufferGetCursor(),aligned=(cursor+63)&~63u,payload=((aligned+64)&0x0fffffff)|0x30000000,flags=word(c+68);
 sw(c+128,cursor);sw(c+132,aligned+48);sw(c+140,payload);sw(c+136,payload);
 if(flags&0x4000){
#if UINTPTR_MAX > UINT32_MAX
  uint32_t f=frame();
#else
  uint32_t locals[12];uint32_t f=(uint32_t)(uintptr_t)locals;
#endif
  store(24,f);store(25,f+16);store(26,f+32);ps2RenderBuildFrontTriangles(context);ps2RenderEmitAllPasses(context);ps2RenderConfigureBuffers(context,sx((uint32_t)(int32_t)(int16_t)half(c+66)));
  load(24,f);load(25,f+16);load(26,f+32);uint32_t count=(uint32_t)(int32_t)(int16_t)half(c+66),base=word(c+100);ps2RenderRelightRecords(sx(base),sx(count));ps2RenderBuildBackTriangles(context);ps2RenderEmitAllPasses(context);
 }else{ps2RenderBuildFrontTriangles(context);ps2RenderEmitAllPasses(context);}LEAVE(64);
}

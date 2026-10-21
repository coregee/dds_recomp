/* Complete original triangle VIF/GIF emission and material/auxiliary passes. */
#include "model_render_emission.h"
#include "model_render_packet_support.h"
#include "model_render_context.h"
#include "ee_vu_rotation.h"
#include "ee_fpu.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolveRenderEmissionAddress(a);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t qword(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static void pushWord(uint32_t *p,uint32_t v){sw(*p,v);*p+=4;}
static void pushDouble(uint32_t *p,uint64_t v){sd(*p,v);*p+=8;}
static void quad(uint32_t source,uint32_t output,unsigned gpr){uint32_t v[4];memcpy(v,at(source),16);EE_RENDER_EMISSION_CPU_QUAD(gpr,v);memcpy(at(output),v,16);}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void acc(unsigned fs,unsigned ft,unsigned bc,unsigned mask,unsigned add){
 uint32_t a[4],b[4],v[4],of[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t x=add?EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],0):EE_ROT_VU_MUL(a[k],b[bc]);v[k]=(uint32_t)x;of[k]=(uint32_t)(x>>32)&1;}EE_ROT_ACC_WRITE(v,of);
}
static void mac(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask){
 uint32_t a[4],b[4],v[4],of[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MAC(v[k],a[k],b[bc],of[k],0);EE_ROT_VU_WRITE(fd,out);
}
static void mul(unsigned fd,unsigned fs,unsigned ft,int bc,unsigned mask){
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,v);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))v[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[bc<0?k:(unsigned)bc]);EE_ROT_VU_WRITE(fd,v);
}
static void add(unsigned fd,unsigned fs,unsigned ft,unsigned bc,unsigned mask){
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,v);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))v[k]=(uint32_t)EE_ROT_VU_ADD(a[k],b[bc]);EE_ROT_VU_WRITE(fd,v);
}
static void colour(unsigned r,unsigned gpr,uint32_t packed){uint32_t raw[4],v[4];for(unsigned k=0;k<4;k++){raw[k]=(packed>>(k*8))&255;v[k]=EE_FPU_CVT_S_W(raw[k]);}EE_RENDER_EMISSION_CPU_QUAD(gpr,raw);EE_ROT_VU_WRITE(r,v);}
static void emit(uint32_t c,unsigned kind,uint64_t state0,uint64_t state1,uint64_t state2,uint64_t state3,uint64_t disable){
 uint32_t remaining=(uint32_t)(int32_t)(int16_t)half(c+80);if(!remaining)return;
 uint32_t p=word(c+140),table=0x581030,first=1,cap=kind==0?24:16;
 do{
  uint32_t count=(int32_t)remaining<(int32_t)(cap+1)?remaining:cap;remaining-=count;
  if((p&12)!=4){pushWord(&p,0);while((p&12)!=4)pushWord(&p,0);}
  pushWord(&p,0x6501c000);
  if(kind==0){pushWord(&p,0x10000);pushWord(&p,0x6c00c001u|((count*6u+1u)<<16));}
  else if(first){
   pushWord(&p,kind==1?4:6);uint32_t material=kind==1?word(c+84):0;pushWord(&p,0x6c00c001u|((count*9u+(kind==1?5u:7u))<<16));
   if(kind==1){
    pushDouble(&p,UINT64_C(0x1000000000000003));pushDouble(&p,14);
    pushDouble(&p,qword(material+56));pushDouble(&p,20);pushDouble(&p,qword(material+64));pushDouble(&p,6);pushDouble(&p,qword(material+72));pushDouble(&p,8);
   }else{
    pushDouble(&p,UINT64_C(0x1000000000000005));pushDouble(&p,14);pushDouble(&p,state0);pushDouble(&p,21);pushDouble(&p,state1);pushDouble(&p,7);pushDouble(&p,state2);pushDouble(&p,9);pushDouble(&p,0x51801);pushDouble(&p,72);pushDouble(&p,state3);pushDouble(&p,67);
   }
   first=0;
  }else{pushWord(&p,0);pushWord(&p,0x6c00c001u|((count*9u+1u)<<16));}
  uint64_t flags=half(0x5520d4);
  flags=kind==2?(flags&~disable)|0x203:flags|3;
  uint64_t tag=(flags<<47)|(count*3u)|(kind==0?UINT64_C(0x2000400000008000):UINT64_C(0x3000400000008000));
  pushDouble(&p,tag);pushDouble(&p,kind==0?0x41:0x412);
  do{
   uint32_t a=word(table),b=word(table+4),d=word(table+8);table+=12;--count;
   if(kind==0){quad(a,p,3);quad(a+32,p+16,2);quad(b,p+32,3);quad(b+32,p+48,2);quad(d,p+64,3);quad(d+32,p+80,2);p+=96;}
   else{quad(a,p,3);quad(a+48,p+16,2);quad(a+32,p+32,3);quad(b,p+48,2);quad(b+48,p+64,3);quad(b+32,p+80,2);quad(d,p+96,3);quad(d+48,p+112,2);quad(d+32,p+128,3);p+=144;}
  }while(count);
  pushWord(&p,0x14000004);
 }while(remaining);
 sw(c+140,p);
}
void ps2RenderEmitTexturedTriangles(uint64_t context){ENTER(64);emit((uint32_t)context,1,0,0,0,0,0);LEAVE(64);}
void ps2RenderEmitStateTriangles(uint64_t context,uint64_t state0,uint64_t state1,uint64_t state2,uint64_t state3,uint64_t disable){ENTER(80);emit((uint32_t)context,2,state0,state1,state2,state3,disable);LEAVE(80);}
void ps2RenderEmitColourTriangles(uint64_t context){ENTER(16);emit((uint32_t)context,0,0,0,0,0,0);LEAVE(16);}
void ps2RenderEmitBaseTriangles(uint64_t context){ENTER(16);uint32_t flags=word((uint32_t)context+68);LEAVE(16);if(flags&16)ps2RenderEmitTexturedTriangles(context);else ps2RenderEmitColourTriangles(context);}
void ps2RenderEmitMaterialPass(uint64_t context){
 ENTER(80);uint32_t c=(uint32_t)context,material=word(c+84);ps2RenderTransformUVRecords(sx(word(c+100)),sx((uint32_t)(int32_t)(int16_t)half(c+66)),sx(word(c+164)),sx(material+128));ps2RenderInterpolateClippedUV(sx(word(c+120)));
 material=word(c+84);uint32_t mode=word(material+36),second=word(material+12),first=word(material+8);
 if(mode<3){
  if(first!=second){
   uint32_t range=EE_FPU_ADD_S(word(material+44),word(c+92)),phase=EE_FPU_ADD_S(word(material+40),word(c+96)),lighting=word(0x5520d8),packed=word(c+88),third=word(material+4),blend=word(material+28);
#if UINTPTR_MAX > UINT32_MAX
   uint32_t local=nocturneRenderEmissionFrameAddress();
#else
   uint32_t words[12];uint32_t local=(uint32_t)(uintptr_t)words;
#endif
   uint32_t raw[4];for(unsigned k=0;k<4;k++)raw[k]=(second>>(k*8))&255;EE_RENDER_EMISSION_CPU_QUAD(2,raw);for(unsigned k=0;k<4;k++)raw[k]=(third>>(k*8))&255;EE_RENDER_EMISSION_CPU_QUAD(3,raw);for(unsigned k=0;k<4;k++)raw[k]=(packed>>(k*8))&255;EE_RENDER_EMISSION_CPU_QUAD(4,raw);
   ps2RenderBuildLighting(sx(local),sx(lighting),sx(packed),sx(second),sx(third),real(blend),real(range),real(phase));ps2RenderRebuildRecordColours(context,sx(local));
  }
 }else if(mode==3)ps2RenderFillRecordColours(context,sx(second));
 uint64_t state3=word(material+32),state0=qword(material+80),state1=qword(material+88),state2=qword(material+96);ps2RenderEmitStateTriangles(context,state0,state1,state2,state3,0);LEAVE(80);
}
void ps2RenderEmitAuxiliaryPass(uint64_t context){
 ENTER(16);uint32_t c=(uint32_t)context,lighting=word(0x5520d8),mode;load(10,lighting+208);mode=word(c+72);
 if(!(mode&0x800)){load(24,0x58f070);load(25,0x58f080);load(26,0x58f090);for(unsigned r=24;r<=26;r++){mul(r,r,10,-1,14);add(r,r,r,1,8);add(r,r,r,2,8);}}
 else{add(24,0,10,0,8);add(25,0,10,1,8);add(26,0,10,2,8);}
 uint32_t material=word(c+84),p=word(c+100),n=half(c+66),packed=word(c+88),mask=word(material+16);colour(4,2,mask);colour(6,2,packed);load(2,p+16);EE_RENDER_EMISSION_LD_TO_VU(5,7,UINT64_C(0x3c0000003c000000));
 mul(6,6,5,0,14);mul(5,5,4,3,4);mul(6,6,4,-1,14);
 do{acc(24,2,0,8,0);acc(25,2,1,8,1);mac(5,26,2,2,8);p+=96;--n;load(2,p+16);store(6,p-64);store(5,p-48);}while(n);
 ps2RenderInterpolateClippedUVColour(sx(word(c+120)));uint64_t state1=qword(0x5518c0);LEAVE(16);ps2RenderEmitStateTriangles(context,0,state1,5,72,32);
}
void ps2RenderEmitAllPasses(uint64_t context){
 ENTER(16);uint32_t c=(uint32_t)context;ps2RenderEmitBaseTriangles(context);uint32_t flags=word(c+68);
 if(flags&0x1000){ps2RenderEmitMaterialPass(context);flags=word(c+68);}
 if(flags&1){LEAVE(16);ps2RenderEmitAuxiliaryPass(context);return;}LEAVE(16);
}

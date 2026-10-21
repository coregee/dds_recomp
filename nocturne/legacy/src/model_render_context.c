/* Original buffer/definition, normal-basis and colour/context setup. */
#include "model_render_context.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "ee_vu_minmax.h"
#include "script_compare.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
extern void EE_RENDER_CONTEXT_CPU_QUAD(unsigned gpr,const uint32_t words[4]);
static void colourCpu(unsigned gpr,uint32_t value){uint32_t v[4];for(unsigned k=0;k<4;k++)v[k]=(value>>(k*8))&255;EE_RENDER_CONTEXT_CPU_QUAD(gpr,v);}
#else
#define colourCpu(gpr,value) ((void)0)
#endif
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveRenderContextAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static int64_t signed64(uint64_t v){return v>>63?-1-(int64_t)~v:(int64_t)v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void acc(unsigned fs,unsigned ft,int bc,unsigned mask,unsigned add){
 uint32_t a[4],b[4],v[4],of[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t x=add?EE_ROT_VU_MAC(v[k],a[k],b[bc<0?k:(unsigned)bc],of[k],0):EE_ROT_VU_MUL(a[k],b[bc<0?k:(unsigned)bc]);v[k]=(uint32_t)x;of[k]=(uint32_t)(x>>32)&1;}
 EE_ROT_ACC_WRITE(v,of);
}
static void mac(unsigned fd,unsigned fs,unsigned ft,int bc,unsigned mask,unsigned sub){
 uint32_t a[4],b[4],v[4],of[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);EE_ROT_ACC_READ(v,of);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MAC(v[k],a[k],b[bc<0?k:(unsigned)bc],of[k],sub);EE_ROT_VU_WRITE(fd,out);
}
static void mul(unsigned fd,unsigned fs,unsigned ft,int bc,unsigned mask){
 uint32_t a[4],b[4],out[4];EE_ROT_VU_READ(fs,a);EE_ROT_VU_READ(ft,b);EE_ROT_VU_READ(fd,out);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k))out[k]=(uint32_t)EE_ROT_VU_MUL(a[k],b[bc<0?k:(unsigned)bc]);EE_ROT_VU_WRITE(fd,out);
}
static void colour(unsigned r,uint32_t value){uint32_t v[4];for(unsigned k=0;k<4;k++)v[k]=EE_FPU_CVT_S_W((value>>(k*8))&255);EE_ROT_VU_WRITE(r,v);}
void ps2RenderConfigureBuffers(uint64_t output,uint64_t count){
 uint32_t p=(uint32_t)output,n=(uint32_t)count,offset=(n*3u)<<5,base=word(0x5520d0);
 if(signed64(count)<128){sw(p+0x70,128u-n);sw(p+0x6c,base);sw(p+0x68,0x70001000u+offset);sw(p+0x74,0x2000);sw(p+0x64,0x70001000);}
 else if(count==128){sw(p+0x64,0x70001000);sw(p+0x68,base);sw(p+0x70,0x2000);sw(p+0x6c,0);sw(p+0x74,0);}
 else{sw(p+0x70,128);sw(p+0x68,0x70001000);sw(p+0x6c,base+offset);sw(p+0x74,0x2000u-n);sw(p+0x64,base);}
 sw(p+0x7c,p+0x78);
}
void ps2RenderReadDefinition(uint64_t output,uint64_t definition,uint64_t mask){
 uint32_t p=(uint32_t)output,d=(uint32_t)definition;sh(p+0x40,half(d));uint16_t count=half(d+2);sh(p+0x42,count);
 uint32_t flags=half(d+4),upperFlags=half(d+6),effective=flags&(uint32_t)mask;sw(p+0x4c,flags);sw(p+0x48,upperFlags);sw(p+0x44,effective);
 sh(0x5520d4,(uint16_t)(effective&0x78));sw(p+0x90,d+8);sw(p+0x80,0);ps2RenderConfigureBuffers(output,count);
}
void ps2RenderComposeNormalBasis(uint64_t basis){
 uint32_t b=(uint32_t)basis,context=word(0x5520d8);load(2,b+0x40);load(5,context+0x10);load(6,context+0x20);load(7,context+0x30);load(3,b+0x50);load(4,b+0x60);
 for(unsigned r=2;r<5;r++){acc(5,r,0,14,0);acc(6,r,1,14,1);mac(24+r-2,7,r,2,14,0);}
 store(2,0x58f070);store(3,0x58f080);store(4,0x58f090);
}
void ps2RenderBuildLighting(uint64_t output,uint64_t context,uint64_t colour0,uint64_t colour1,uint64_t colour2,float blend,float range,float phase){
 uint32_t p=(uint32_t)output,c=(uint32_t)context,b=bits(blend),r=bits(range),f=bits(phase);
 if(EE_FPU_COMPARE_S(r,0x3f800000,1))r=0x3f800000;uint32_t product=EE_FPU_MUL_S(f,r);sw(p+12,r);sw(p+4,product);
 colourCpu(2,(uint32_t)colour1);colourCpu(3,(uint32_t)colour2);colourCpu(4,(uint32_t)colour0);
 colour(2,(uint32_t)colour1);colour(3,(uint32_t)colour2);colour(4,(uint32_t)colour0);
 EE_RENDER_CONTEXT_WORD_TO_VU(5,11,b);EE_RENDER_CONTEXT_WORD_TO_VU(6,12,0x3c000000);EE_RENDER_CONTEXT_WORD_TO_VU(7,5,0x437f0000);
 load(8,c+0x40);load(9,c+0x80);mul(2,2,6,0,15);mul(3,3,6,0,15);
 uint32_t v[4],zero[4];EE_ROT_VU_READ(9,v);EE_ROT_VU_READ(0,zero);v[3]=zero[3];EE_ROT_VU_WRITE(9,v);
 mul(8,8,0,0,1);mul(4,4,2,3,1);mul(9,3,9,-1,14);mul(8,2,8,-1,14);
 acc(9,0,3,14,0);acc(8,5,0,14,1);mac(9,9,5,0,14,1);mul(8,8,4,-1,15);mul(9,9,4,-1,15);
 uint32_t limit[4];EE_ROT_VU_READ(8,v);EE_ROT_VU_READ(7,limit);for(unsigned k=0;k<4;k++)v[k]=EE_VU_MINMAX_BITS(v[k],limit[0],1);EE_ROT_VU_WRITE(8,v);
 EE_ROT_VU_READ(9,limit);for(unsigned k=0;k<3;k++)v[k]=(uint32_t)EE_ROT_VU_SUB(v[k],limit[k]);EE_ROT_VU_WRITE(8,v);store(9,p+16);store(8,p+32);
}
void ps2RenderUpdateLighting(uint64_t output,uint64_t material,uint64_t colour0,float rangeBias,float phaseBias){
 uint32_t m=(uint32_t)material,context=word(0x5520d8),r=word(m+0x2c),f=word(m+0x28);
 r=EE_FPU_ADD_S(r,bits(rangeBias));uint32_t b=word(m+0x1c);f=EE_FPU_ADD_S(f,bits(phaseBias));uint32_t colour1=word(m+8),colour2=word(m+4);
 ps2RenderBuildLighting(output,sx(context),colour0,sx(colour1),sx(colour2),real(b),real(r),real(f));
}

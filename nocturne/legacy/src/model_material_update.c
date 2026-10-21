/* Original frame-selected material packets and ordered COP1 UV transform. */
#include "model_material_update.h"
#include "material_lists.h"
#include "dev_packets.h"
#include "panel_draw.h"
#include "battle_panel_support.h"
#include "model_motion_sampling.h"
#include "ee_fpu.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveMaterialUpdateAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 002B3598: retain texture before the first store; other fields load in order. */
void ps2MaterialCopyBase(uint64_t material,uint64_t output){
 uint32_t m=(uint32_t)material,p=(uint32_t)output,value=word(m+0x10),texture=word(m+0x2c);
 sw(p+4,value);uint32_t scalar=word(m+0x1c);value=word(m+0x14);
 sw(p+0x1c,scalar);sw(p+8,value);sw(p+0x10,word(m+0x20));sw(p+0x14,word(m+0x28));
 if(texture){uint64_t v=ps2TextureGetFilterRegister(sx(texture));sd(p+0x38,v);
  v=ps2TextureGetRegister(sx(texture));sd(p+0x40,v);v=ps2TextureGetWrapRegister(sx(texture));sd(p+0x48,v);}
}
/* 002B3620: every arithmetic operation is an original COP1 boundary. */
void ps2MaterialBuildUVTransform(uint64_t output,uint64_t input){
 uint32_t p=(uint32_t)output,m=(uint32_t)input;
 if(!input){sd(p,UINT64_C(0x3f800000));sd(p+8,UINT64_C(0x3f80000000000000));sd(p+16,0);return;}
 uint32_t angle=word(m+16)^0x80000000u,sine=sdfSinBits(angle),cosine=sdfCosBits(angle);
 uint32_t sy=word(m+12),ns=sine^0x80000000u,sxv=word(m+8),x=word(m);
 sine=EE_FPU_MUL_S(sine,sy);uint32_t cx=EE_FPU_MUL_S(cosine,sxv),y=word(m+4);
 ns=EE_FPU_MUL_S(ns,sxv);x=EE_FPU_ADD_S(x,0x3f000000);y=EE_FPU_SUB_S(0x3f000000,y);
 sw(p+4,sine);cosine=EE_FPU_MUL_S(cosine,sy);sw(p,cx);sw(p+8,ns);
 sine=EE_FPU_MUL_S(sine,x);cx=EE_FPU_MUL_S(cx,x);sw(p+12,cosine);
 cosine=EE_FPU_MUL_S(cosine,y);ns=EE_FPU_MUL_S(ns,y);
 sine=EE_FPU_SUB_S(0x3f000000,sine);cx=EE_FPU_SUB_S(0x3f000000,cx);
 sine=EE_FPU_SUB_S(sine,cosine);cx=EE_FPU_SUB_S(cx,ns);sw(p+20,sine);sw(p+16,cx);
}
/* 002B3708: the wrapper loads its input before adding the output displacement. */
void ps2MaterialUpdatePrimaryUV(uint64_t material,uint64_t output){uint32_t uv=word((uint32_t)material+0x38);ps2MaterialBuildUVTransform(sx((uint32_t)output+0x68),sx(uv));}
/* 002B3728: the secondary input pointer is deliberately reloaded last. */
void ps2MaterialUpdateSecondaryUV(uint64_t material,uint64_t output){
 uint32_t m=(uint32_t)material,p=(uint32_t)output,value=word(m+0x18),texture=word(m+0x30);
 sw(p+12,value);value=word(m+0x34);sw(p+0x24,value);sw(p+0x20,half(0x529438+(value<<1)));
 if(texture){uint64_t v=ps2TextureGetFilterRegister(sx(texture));sd(p+0x50,v);
  v=ps2TextureGetRegister(sx(texture));sd(p+0x58,v);v=ps2TextureGetWrapRegister(sx(texture));sd(p+0x60,v);}
 value=word(m+0x3c);ps2MaterialBuildUVTransform(sx(p+0x80),sx(value));
}
/* 002B37D0: all tests and final pending bits use the initial flag snapshot. */
void ps2MaterialUpdateFrame(uint64_t material,uint64_t frame){
 uint32_t m=(uint32_t)material,shift=(uint32_t)frame&31,flags=*(uint8_t *)at(m+6),p=word(m+8+((uint32_t)frame<<2));
 if((flags>>shift)&1)ps2MaterialCopyBase(material,sx(p));
 if(flags&(4u<<shift))ps2MaterialUpdatePrimaryUV(material,sx(p));
 if(flags&(0x10u<<shift))ps2MaterialUpdateSecondaryUV(material,sx(p));
 if(flags&(0x40u<<shift))ps2MatCopyScalars40And44(m,p);
 *(uint8_t *)at(m+6)=(uint8_t)(flags&(0x55u<<(((uint32_t)frame^1u)&31)));
}
/* 002B3940: signed halfword count, including the empty list's pointer read. */
void ps2MaterialUpdateList(uint64_t definition,uint64_t frame){
 uint32_t d=(uint32_t)definition,c=half(d+4),array=word(d+12);int32_t count=c&0x8000u?(int32_t)c-65536:(int32_t)c;
 while(count>0){uint32_t material=word(array);ps2MaterialUpdateFrame(sx(material),frame);array+=4;--count;}
}

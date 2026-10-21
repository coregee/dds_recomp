/* Original effect-copy dispatch, cut creation and selected hit constructors.
 * Callbacks are real original table targets; no constructor results are faked. */
#include "battle_effect_copy.h"
#include "battle_work_access.h"
#include "script_construction.h"
#include "material_fiveword_pool.h"
#include "libc_printf.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveBattleEffectCopyAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static float unbits(uint32_t bits){float f;memcpy(&f,&bits,4);return f;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static uint64_t copy_call(uint32_t target,uint64_t source){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneCallEffectCopy(target,source);
#else
 return ((uint64_t(*)(uint64_t))(uintptr_t)target)(source);
#endif
}
static void scale_call(uint32_t target,uint64_t object,uint32_t scale){
#if UINTPTR_MAX > UINT32_MAX
 nocturneCallEffectScale(target,object,scale);
#else
 ((void(*)(float,uint64_t))(uintptr_t)target)(unbits(scale),object);
#endif
}
/* 0016E560: null/inactive formation returns512, synthetic work flag4 returns0. */
uint64_t effBTLModelGetID(uint64_t form){
 if(!form||!(r32((uint32_t)form+0x78)&1))return 0x200;
 uint32_t work=(uint32_t)nbGetUnitWorkFromFormindex((uint64_t)(int64_t)(int16_t)r16((uint32_t)form+0x92));
 return r32(work)&4?0:r16(work+4);
}
/* 0016E638: preserve COP1 grouping and original clamp order. */
float effBTLPartGetScalePtrSub(uint64_t form){
 uint32_t a=(uint32_t)form;
 uint32_t value=EE_FPU_MUL_S(r32(a+0x54),0x3f000000);
 value=EE_FPU_ADD_S(r32(a+0x50),value);value=EE_FPU_MUL_S(value,0x3f000000);
 value=EE_FPU_MUL_S(value,r32(a+0x5c));value=EE_FPU_MUL_S(value,r32(0x54c674));
 if(EE_FPU_COMPARE_S(0x40000000,value,1))return unbits(0x40000000);
 uint32_t minimum=r32(0x54c678);if(EE_FPU_COMPARE_S(value,minimum,1))value=minimum;
 return unbits(value);
}
/* 0016E698: ID-specific scale from the original87-way table, then default. */
float effBTLPartGetScalePtr(uint64_t form){
 uint64_t index=sx((uint32_t)effBTLModelGetID(form)-0x102u);
 if(index<0x57){uint32_t target=r32(0x533080+(uint32_t)index*4u);if(target==0x16e6d8)return unbits(r32(0x54c67c));if(target==0x16e6e8)return 3.0f;}
 return effBTLPartGetScalePtrSub(form);
}
float effBTLSystem_GetScalePtr(uint64_t form){return r32((uint32_t)form+0x8c)?effBTLPartGetScalePtr(form):effBTLPartGetScalePtrSub(form);}
uint64_t effBTLSkillGetID(void){return sx(r32(0x551d7c));}
uint64_t dds3EffectPartGetHandle(uint64_t part){return sx(r32((uint32_t)part+4));}
/* 00175A88: reload source type after SH before the callback lookup. */
uint64_t dds3EffectPartCopy(uint64_t part){
 uint32_t source=(uint32_t)part,p=ps2PoolAllocate(8);uint16_t type=r16(source);w16(p,type);
 uint64_t child=sx(r32(source+4));type=r16(source);
 uint64_t result=copy_call(r32(0x31de4c+type*40u),child);w32(p+4,(uint32_t)result);return sx(p);
}
void dds3EffectPartSetScale(float scale,uint64_t part){uint32_t p=(uint32_t)part,target=r32(0x31de54+r16(p)*40u);if(target)scale_call(target,sx(r32(p+4)),bits(scale));}
/* 00176038: explicit copy callback or parameter-indexed asset initializer. */
uint64_t dds3EffectPCPCopy(uint64_t source){
 uint32_t s=(uint32_t)source,p=ps2PoolAllocate(12),kind=r32(s),table=0x31df90+kind*40u;
 w32(p,kind);uint32_t callback=r32(table+12),parameter=r32(s+4);w32(p+4,parameter);uint64_t child;
 if(callback)child=copy_call(callback,sx(r32(s+8)));
 else child=copy_call(r32(table),sx(r32(r32(0x31ddd0+kind*4u)+parameter*4u)));
 w32(p+8,(uint32_t)child);return sx(p);
}
void dds3EffectPCPSetScale(float scale,uint64_t pcp){uint32_t p=(uint32_t)pcp,target=r32(0x31dfa4+r32(p)*40u);if(target)scale_call(target,sx(r32(p+8)),bits(scale));}
void ps2EffectPCPScale_00176538(float scale,uint64_t object){uint32_t p=(uint32_t)object,b=bits(scale),x=EE_FPU_MUL_S(r32(p+0x54),b),y=EE_FPU_MUL_S(r32(p+0x58),b);w32(p+0x1c,x);w32(p+0x20,y);}
/* Original unowned PCP43 create/copy rows: flag byte, zero return, no heap. */
uint64_t ps2EffectPCP43Create(uint64_t object){(void)object;*at(0x54f1ec)=1;return 0;}
uint64_t ps2EffectPCP43Copy(uint64_t object){(void)object;*at(0x54f1ec)=1;return 0;}
uint64_t ps2BillboardTextureBase(uint64_t kind){return sx(r32(r32(r32(0x569848+(uint32_t)kind*4u)+0x30)));}
/* Unaligned LDL/LDR blocks snapshot each32-byte group before storing it. */
uint64_t ps2EffectCopy_001a1ff8(uint64_t source){uint32_t p=ps2PoolAllocate(48),s=(uint32_t)source;w32(p+0x2c,(uint32_t)ps2BillboardTextureBase(2));uint8_t first[32],last[8];memcpy(first,at(s),32);memcpy(at(p),first,32);memcpy(last,at(s+32),8);uint32_t tail=r32(s+40);memcpy(at(p+32),last,8);w32(p+40,tail);return sx(p);}
uint64_t ps2EffectCreate_0018e1c8(uint64_t source){
 uint32_t s=(uint32_t)source,p=ps2PoolAllocate(56);uint64_t child=ps2EffectCopy_001a1ff8(sx(s+0x14));
 uint32_t first=r32(s+0x18);w32(p+0x18,0);w32(p+0x14,first);w32(p+0x10,0x80808080);w32(p,0);w32(p+4,0);w32(p+0x20,r32(s));w32(p+8,0);w32(p+0x1c,0);w32(p+0x24,r32(s+4));
 uint32_t f=r32(s+12),v=r32(s+8);w32(p+0x34,(uint32_t)child);w32(p+0x28,v);w32(p+0x2c,f);w32(p+0x30,r32(s+16));return sx(p);
}
/* 0016AC70: zero288-byte cut, link before part copies, native bank selection. */
uint64_t effBTLCutCreate(uint64_t effect,uint64_t cut,uint64_t form,uint64_t state){
 uint32_t e=(uint32_t)effect,p=ps2PoolAllocate(0x120);memset(at(p),0,0x120);w32(p+4,e);uint32_t number=(uint16_t)cut,bank=e+(number<2?8u:0x620u);
 uint32_t old=r32(e+0xc40),frame=r32(bank);w32(p+0x11c,old);w32(p+12,frame);w32(e+0xc40,p);w16(p+0x14,(uint16_t)number);w32(p+0x1c,bank);
 w32(p+16,r32(number==2?bank:bank+0x70));bank=r32(p+0x1c);w32(p+0x18,(uint32_t)state);w32(p,(uint32_t)form);
 uint32_t count=r16(bank+0x6c),scalable=*at(bank+0x74),record=bank+0x78,slot=p+0x20;
 for(uint32_t i=0;i<count;i++,record+=24,slot+=4){
  if(r16(record)==0xfffe)w32(slot,0);
  else{uint64_t child=dds3EffectPartCopy(sx(r32(record+4)));w32(slot,(uint32_t)child);
   if(scalable&&form&&(*at(record+8)==0||*at(record+8)==4))dds3EffectPartSetScale(effBTLPartGetScalePtr(sx(r32(p))),sx(r32(slot)));
  }
 }
 uint32_t owner=r32(p+4);w32(p+8,0);(void)ps2LibcPrintf(0x532e50,r16(p+0x14),sx(owner),sx(r32(owner+0xc3c)));owner=r32(p+4);w32(owner+0xc3c,r32(owner+0xc3c)+1u);return sx(p);
}
uint64_t effBTLCutGetCutEndFrame(uint64_t cut){return sx(r32((uint32_t)cut+12));}
static uint64_t cut_root(uint64_t form,uint32_t global){uint32_t p=ps2PoolAllocate(12);w32(p,(uint32_t)form);w32(p+4,0);uint64_t cut=effBTLCutCreate(sx(r32(global)),3,form,0);w32(p+8,(uint32_t)cut);return sx(p);}
uint64_t ps2HitEffectCreate20(uint64_t f){return cut_root(f,0x31bd24);}
uint64_t ps2HitEffectCreate26(uint64_t f){return cut_root(f,0x31be94);}
uint64_t ps2HitEffectCreate27(uint64_t f){return cut_root(f,0x31beb4);}
uint64_t ps2HitEffectCreate28(uint64_t f){return cut_root(f,0x31bed4);}
uint64_t ps2HitEffectCreate29(uint64_t f){return cut_root(f,0x31bef4);}
static uint64_t multi_root(uint64_t form,uint32_t count){uint32_t p=ps2PoolAllocate((count+2)*4u);w32(p,(uint32_t)form);w32(p+4,0);for(uint32_t k=0;k<count;k++){uint32_t table=0x31bd30+(k/6)*0xa8;uint64_t child=dds3EffectPartCopy(sx(r32(table+0x10+(k%6)*28)));w32(p+8+k*4,(uint32_t)child);}return sx(p);}
uint64_t ps2HitEffectCreate24(uint64_t f){return multi_root(f,6);}
uint64_t ps2HitEffectCreate25(uint64_t f){return multi_root(f,12);}
#define CUT_LENGTH(k) uint64_t ps2HitEffectLength##k(uint64_t o){return effBTLCutGetCutEndFrame(sx(r32((uint32_t)o+8)));}
CUT_LENGTH(20) CUT_LENGTH(26) CUT_LENGTH(27) CUT_LENGTH(28) CUT_LENGTH(29)
#undef CUT_LENGTH
uint64_t ps2HitEffectLength14(uint64_t o){(void)o;return 50;}
uint64_t ps2HitEffectLength17(uint64_t o){(void)o;return 15;}
uint64_t ps2HitEffectLength18(uint64_t o){(void)o;return 25;}
uint64_t ps2HitEffectLength24(uint64_t o){(void)o;return 20;}
uint64_t ps2HitEffectLength25(uint64_t o){(void)o;return 20;}
uint64_t nocturneEffectScaleSubBits(uint64_t f){return bits(effBTLPartGetScalePtrSub(f));}
uint64_t nocturneEffectScaleBits(uint64_t f){return bits(effBTLPartGetScalePtr(f));}
uint64_t nocturneEffectSystemScaleBits(uint64_t f){return bits(effBTLSystem_GetScalePtr(f));}
void nocturneEffectPartScaleBits(uint64_t s,uint64_t p){dds3EffectPartSetScale(unbits((uint32_t)s),p);}
void nocturneEffectPCPScaleBits(uint64_t s,uint64_t p){dds3EffectPCPSetScale(unbits((uint32_t)s),p);}
void nocturneEffectPCP0ScaleBits(uint64_t s,uint64_t p){ps2EffectPCPScale_00176538(unbits((uint32_t)s),p);}

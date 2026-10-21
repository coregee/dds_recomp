/* Original PCP field-control callbacks, with native store and VU ordering. */
#include "pcp_field_controls.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "libm_trig.h"
#include "effect_matrix.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolvePcpFieldControlsAddress(a);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t read32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void write32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t bits(float v){uint32_t w;memcpy(&w,&v,4);return w;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static void position(uint32_t d,uint32_t s){uint32_t v[4];memcpy(v,at(s),16);memcpy(at(d),v,16);}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void delta(uint32_t p,uint32_t s){
 uint32_t previous[4],next[4],difference[4],base[4],moved[4];
 memcpy(previous,at(p+16),16);EE_ROT_VU_WRITE(10,previous);
 memcpy(next,at(s),16);EE_ROT_VU_WRITE(11,next);memcpy(at(p+16),next,16);
 for(unsigned k=0;k<4;k++)difference[k]=(uint32_t)EE_ROT_VU_SUB(next[k],previous[k]);
 EE_ROT_VU_WRITE(11,difference);memcpy(base,at(p),16);EE_ROT_VU_WRITE(10,base);
 for(unsigned k=0;k<4;k++)moved[k]=(uint32_t)EE_ROT_VU_ADD(base[k],difference[k]);
 EE_ROT_VU_WRITE(10,moved);memcpy(at(p),moved,16);
}
static void matrix(uint32_t p,uint32_t s){for(unsigned k=0;k<4;k++)load(28+k,s+k*16);for(unsigned k=0;k<4;k++)store(28+k,p+k*16);}
static void halfTurn(uint32_t p,uint32_t s){
 ENTER(32);sdfRotationYFloat(real(read32(0x54c88c)));
 for(unsigned k=0;k<4;k++)load(24+k,s+k*16);
 sdfMultiplyEffectVuMatrices();for(unsigned k=0;k<4;k++)store(28+k,p+k*16);LEAVE(32);
}
void ps2PcpType36SetMatrix(uint64_t object,uint64_t value){halfTurn((uint32_t)object,(uint32_t)value);}
void ps2PcpType8SetPosition(uint64_t object,uint64_t value){delta((uint32_t)object,(uint32_t)value);}
void ps2PcpType40SetMatrix(uint64_t object,uint64_t value){matrix((uint32_t)object+16,(uint32_t)value);}
void ps2PcpType41SetMatrix(uint64_t object,uint64_t value){matrix((uint32_t)object+16,(uint32_t)value);}
void ps2PcpType42SetMatrix(uint64_t object,uint64_t value){matrix((uint32_t)object+16,(uint32_t)value);}
void ps2PcpType37SetScale(float value,uint64_t object){uint32_t p=(uint32_t)object,v=bits(value);uint32_t f0=read32(p+60);uint32_t f1=read32(p+76);uint32_t f2=read32(p+80);f0=EE_FPU_MUL_S(f0,v);f1=EE_FPU_MUL_S(f1,v);f2=EE_FPU_MUL_S(f2,v);write32(p+60,f0);write32(p+76,f1);write32(p+80,f2);}
void ps2PcpType38SetScale(float value,uint64_t object){uint32_t p=(uint32_t)object,v=bits(value);uint32_t f0=read32(p+64);uint32_t f1=read32(p+68);f0=EE_FPU_MUL_S(f0,v);f1=EE_FPU_MUL_S(f1,v);write32(p+64,f0);write32(p+68,f1);}
void ps2PcpType27SetPosition(uint64_t object,uint64_t value){(void)object;position(read32(0x551dd0),(uint32_t)value);}
void ps2PcpType36SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+64,(uint32_t)value);}
void ps2PcpType18SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType14SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType16SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType17SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType19SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType37SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType38SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType13SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType11SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType7SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType9SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType21SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType22SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType23SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType12SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType20SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType24SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType29SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType25SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType10SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType26SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType33SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType32SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType34SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType35SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType39SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType40SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType41SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType42SetPosition(uint64_t object,uint64_t value){position((uint32_t)object+0,(uint32_t)value);}
void ps2PcpType27SetColor(uint64_t object,uint64_t value){(void)object;write32(read32(0x551dd0)+16,(uint32_t)value);}
void ps2PcpType8SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+88,(uint32_t)value);}
void ps2PcpType18SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+56,(uint32_t)value);}
void ps2PcpType18SetScale(float value,uint64_t object){write32((uint32_t)object+60,bits(value));}
void ps2PcpType14SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+72,(uint32_t)value);}
void ps2PcpType14SetScale(float value,uint64_t object){write32((uint32_t)object+76,bits(value));}
void ps2PcpType16SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+80,(uint32_t)value);}
void ps2PcpType16SetScale(float value,uint64_t object){write32((uint32_t)object+84,bits(value));}
void ps2PcpType17SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+88,(uint32_t)value);}
void ps2PcpType17SetScale(float value,uint64_t object){write32((uint32_t)object+92,bits(value));}
void ps2PcpType19SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+96,(uint32_t)value);}
void ps2PcpType19SetScale(float value,uint64_t object){write32((uint32_t)object+100,bits(value));}
void ps2PcpType37SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+124,(uint32_t)value);}
void ps2PcpType38SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+108,(uint32_t)value);}
void ps2PcpType13SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+20,(uint32_t)value);}
void ps2PcpType11SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+16,(uint32_t)value);}
void ps2PcpType7SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+16,(uint32_t)value);}
void ps2PcpType9SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+24,(uint32_t)value);}
void ps2PcpType21SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+24,(uint32_t)value);}
void ps2PcpType22SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+24,(uint32_t)value);}
void ps2PcpType23SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+24,(uint32_t)value);}
void ps2PcpType12SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+24,(uint32_t)value);}
void ps2PcpType20SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+24,(uint32_t)value);}
void ps2PcpType24SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+20,(uint32_t)value);}
void ps2PcpType29SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+24,(uint32_t)value);}
void ps2PcpType25SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+20,(uint32_t)value);}
void ps2PcpType10SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+16,(uint32_t)value);}
void ps2PcpType26SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+20,(uint32_t)value);}
void ps2PcpType33SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+20,(uint32_t)value);}
void ps2PcpType30SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+36,(uint32_t)value);}
void ps2PcpType31SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+52,(uint32_t)value);}
void ps2PcpType32SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+32,(uint32_t)value);}
void ps2PcpType34SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+20,(uint32_t)value);}
void ps2PcpType35SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+20,(uint32_t)value);}
void ps2PcpType36SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+100,(uint32_t)value);}
void ps2PcpType39SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+84,(uint32_t)value);}
void ps2PcpType40SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+92,(uint32_t)value);}
void ps2PcpType40SetScale(float value,uint64_t object){write32((uint32_t)object+88,bits(value));}
void ps2PcpType41SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+92,(uint32_t)value);}
void ps2PcpType41SetScale(float value,uint64_t object){write32((uint32_t)object+88,bits(value));}
void ps2PcpType42SetColor(uint64_t object,uint64_t value){write32((uint32_t)object+92,(uint32_t)value);}
void ps2PcpType42SetScale(float value,uint64_t object){write32((uint32_t)object+88,bits(value));}

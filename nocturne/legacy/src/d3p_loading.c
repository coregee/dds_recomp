/* Original serialized D3P conversion, loading and live wrapper creation. */
#include "d3p_loading.h"
#include "material_fiveword_pool.h"
#include "emitter_initialization.h"
#include "libc_printf.h"
#include "nocturne.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "script_compare.h"
#include "resource_loader_flow.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveD3PLoadingAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
/* 0015AAD0: full table dispatch after halfword argument masking. */
uint64_t dds3EffectCreate(uint64_t major,uint64_t minor,uint64_t source){uint32_t m=(uint16_t)major,n=(uint16_t)minor,p=ps2PoolAllocate(16),target;w32(p,m);w32(p+12,r32(0x54c5a0));w32(p+4,n);target=r32(0x316ef0+m*48u);uint64_t child;
#if UINTPTR_MAX > UINT32_MAX
 child=nocturneCallEffectCreation(target,n,source);
#else
 child=((uint64_t (*)(uint64_t,uint64_t))(uintptr_t)target)(n,source);
#endif
 w32(p+8,(uint32_t)child);return sx(p);
}
/* 0015AF88: complete-word tags decide compatibility changes. The second
 * major1 relative traversal starts from the cursor left by the 1.0 branch. */
void dds3EffectDataRevision(uint64_t descriptor){uint32_t d=(uint32_t)descriptor,v=r32(d+12),cursor=d+16;
 if(EE_FPU_COMPARE_S(v,0x3f800000,0)){
  uint32_t major=r32(d);
  if(major==1){cursor+=r32(cursor+4)+16u;w32(cursor+160,172);}
  else if(major==0)w32(cursor+160,172);
  else if(major==2)w32(cursor+24,32);
 }
 if(EE_FPU_COMPARE_S(v,r32(0x54c5ac),2)){
  uint32_t major=r32(d);
  if(major==1){cursor+=r32(cursor+4)+16u;uint32_t value=EE_FPU_MUL_S(r32(cursor+140),r32(0x54c5b0));value=EE_FPU_MUL_S(value,EE_FPU_CVT_S_W(r32(cursor+36)));value=EE_FPU_ADD_S(value,r32(cursor+16));w32(cursor+140,value);}
  if(major<2&&r32(d+4)==0)(void)ps2LibcPrintf(0x532b40,ps2SoftDoubleFromFloat(real(r32(d+12))));
 }
}
static void identity(uint32_t matrix){uint32_t v[4];EE_ROT_VU_READ(0,v);uint32_t words[16]={v[3],0,0,0,0,v[3],0,0,v[2],0,v[3],0,v[0],v[1],v[2],v[3]};for(unsigned k=0;k<16;k++)w32(matrix+k*4,words[k]);}
/* 0015ADA0 */
uint64_t dds3EffectLoad(uint64_t descriptor){uint32_t d=(uint32_t)descriptor,v=r32(d+12);
 if(EE_FPU_COMPARE_S(v,r32(0x54c5a4),1)){(void)ps2LibcPrintf(0x532af0,ps2SoftDoubleFromFloat(real(v)));dds3EffectDataRevision(descriptor);}
 uint64_t object=dds3EffectCreate(r16(d),r16(d+4),sx(d+16));uint32_t p=(uint32_t)object;
 if(EE_FPU_COMPARE_S(r32(d+12),r32(0x54c5a8),2)){uint32_t major=r32(p);if(major<2)identity(r32(p+8)+176u);else if(major==2)identity(r32(p+8)+32u);(void)ps2LibcPrintf(0x532b08);}
 return object;
}
/* 00175998: the upper half of the first allocation word stays dirty. */
uint64_t dds3EffectPartCreate(uint64_t type,uint64_t source){
#if UINTPTR_MAX > UINT32_MAX
 nocturneResourceFrameEnter(0x20);
#endif
 uint32_t minor=(uint16_t)type,p=ps2PoolAllocate(8);w16(p,(uint16_t)minor);uint32_t target=r32(0x31de40+minor*40u);uint64_t child;
#if UINTPTR_MAX > UINT32_MAX
 child=nocturneCallEffectPartCreation(target,source);
#else
 child=((uint64_t (*)(uint64_t))(uintptr_t)target)(source);
#endif
 w32(p+4,(uint32_t)child);
#if UINTPTR_MAX > UINT32_MAX
 nocturneResourceFrameLeave(0x20);
#endif
 return sx(p);
}
uint64_t ps2EffectPartBillboardNormalCreate(uint64_t source){return dds3BillboardCreate(0,source);}
uint64_t ps2EffectPartBillboardAnimationCreate(uint64_t source){return dds3BillboardCreate(1,source);}

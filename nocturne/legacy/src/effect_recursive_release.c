/* Original table dispatch and recursive PCP cleanup. No managed guards added. */
#include "effect_recursive_release.h"
#include "effect_leaf_release.h"
#include "script_construction.h"
#include "memory_handle_allocation.h"
#include "material_construction_release.h"
#include <string.h>
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,nocturneResolveScriptConstructionAddress(p),4);return v;}
static uint32_t half(uint32_t p){uint16_t v;memcpy(&v,nocturneResolveScriptConstructionAddress(p),2);return v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
#define BEGIN(entry) nocturneTraceRecursiveEffectRelease(entry,object);uint32_t o=(uint32_t)object
void dds3EffectDelete(uint64_t object)
{BEGIN(0x15ab58);nocturneCallRecursiveEffectDelete(word(0x316ef8+word(o)*48),sx(word(o+8)));ps2PoolRelease(o);}
void dds3EffectPartDeleteO(uint64_t object)
{BEGIN(0x175a08);nocturneCallRecursiveEffectDelete(word(0x31de48+half(o)*40),sx(word(o+4)));ps2PoolRelease(o);}
void dds3EffectPCPDelete(uint64_t object)
{BEGIN(0x175fb8);nocturneCallRecursiveEffectDelete(word(0x31df98+word(o)*40),sx(word(o+8)));ps2PoolRelease(o);}
/* Reload the child-array pointer each time; count is captured before cleanup. */
static void scatterChildren(uint32_t o,uint32_t countOffset,uint32_t arrayOffset,uint32_t handleOffset)
{
 uint32_t handle=word(o+handleOffset);
 if(handle){uint64_t count=sx(word(o+countOffset));uint32_t i=0;
  if(count)do{uint32_t array=word(o+arrayOffset);i++;dds3EffectPartDeleteO(sx(word(array+((i-1)<<2))));}while(sx(i)<count);
  ps2MemoryHandleFree(word(o+handleOffset));}
}
void ps2EffectRelease_00183cf8(uint64_t object)
{BEGIN(0x183cf8);scatterChildren(o,0x88,0x8c,0x90);ps2EffectRelease_00185d88(sx(word(o+0x80)));ps2MemoryHandleFree(word(o+0x84));}
void ps2EffectRelease_00184950(uint64_t object)
{BEGIN(0x184950);scatterChildren(o,0x78,0x7c,0x80);ps2EffectRelease_00185d88(sx(word(o+0x70)));ps2MemoryHandleFree(word(o+0x74));}
void ps2EffectRelease_0018a5d8(uint64_t object)
{BEGIN(0x18a5d8);for(uint32_t i=0;i<8;i++){dds3EffectPartDeleteO(sx(word(o+0x5c+i*4)));dds3EffectPartDeleteO(sx(word(o+0x20+i*8)));dds3EffectPartDeleteO(sx(word(o+0x1c+i*8)));}ps2PoolRelease(o);}
void ps2EffectRelease_0018aab0(uint64_t object)
{BEGIN(0x18aab0);for(uint32_t i=0;i<8;i++){dds3EffectPartDeleteO(sx(word(o+0x38+i*8)));dds3EffectPartDeleteO(sx(word(o+0x3c+i*8)));}ps2PoolRelease(o);}
void ps2EffectRelease_0018afd8(uint64_t object)
{BEGIN(0x18afd8);dds3EffectPartDeleteO(sx(word(o+0x18)));for(uint32_t i=0;i<4;i++)for(uint32_t j=0;j<3;j++)dds3EffectPartDeleteO(sx(word(o+0x1c+i*12+j*4)));ps2PoolRelease(o);}
void ps2EffectRelease_0018b430(uint64_t object)
{BEGIN(0x18b430);for(uint32_t i=0;i<6;i++){dds3EffectPartDeleteO(sx(word(o+0x18+i*8)));dds3EffectPartDeleteO(sx(word(o+0x1c+i*8)));}ps2PoolRelease(o);}
void ps2EffectRelease_0018b708(uint64_t object)
{BEGIN(0x18b708);dds3EffectPartDeleteO(sx(word(o+0x134c)));dds3EffectPartDeleteO(sx(word(o+0x1348)));ps2MemoryHandleFree(word(o+0x1350));}
void ps2EffectRelease_0018bbd0(uint64_t object)
{BEGIN(0x18bbd0);dds3EffectPartDeleteO(sx(word(o+0x14)));dds3EffectPartDeleteO(sx(word(o+0x18)));ps2PoolRelease(o);}
void ps2EffectRelease_0018fc70(uint64_t object)
{BEGIN(0x18fc70);uint32_t child=word(o+0x74);if(child)dds3EffectDelete(sx(child));ps2PoolRelease(o);}
void ps2EffectRelease_001902c8(uint64_t object)
{BEGIN(0x1902c8);for(uint32_t i=0;i<7;i++){dds3EffectDelete(sx(word(o+0x90+i*4)));dds3EffectDelete(sx(word(o+0x74+i*4)));dds3EffectDelete(sx(word(o+0x58+i*4)));}ps2PoolRelease(o);}
void ps2EffectRelease_00190bf0(uint64_t object)
{
 BEGIN(0x190bf0);
 if(!word(o+0x108)){
  dds3EffectPartDeleteO(sx(word(o+0xc0)));
  for(uint32_t i=0;i<5;i++)dds3EffectPartDeleteO(sx(word(o+0xc4+i*4)));
  for(uint32_t j=0;j<3;j++)if(word(o+0xfc+j*4)){
   uint64_t count=sx(word(o+0xb4)*word(o+0x7c+j*4));uint32_t i=0;
   if(count)do{uint32_t array=word(o+0xd8+j*4),child=word(array+(i<<2));i++;if(child)dds3EffectPartDeleteO(sx(child));}while(sx(i)<count);
   ps2MemoryHandleFree(word(o+0xfc+j*4));
  }
  for(uint32_t i=0;i<5;i++)dds3EffectPartDeleteO(sx(word(o+0xe4+i*4)));
  dds3EffectPartDeleteO(sx(word(o+0xf8)));
 }
 ps2PoolRelease(o);
}
void ps2EffectRelease_00192348(uint64_t object)
{BEGIN(0x192348);dds3EffectPartDeleteO(sx(word(o+0x60)));ps2PoolRelease(o);}
void ps2EffectRelease_001925e8(uint64_t object)
{BEGIN(0x1925e8);dds3EffectPartDeleteO(sx(word(o+0x64)));dds3EffectPartDeleteO(sx(word(o+0x60)));ps2PoolRelease(o);}
void ps2EffectRelease_001928e8(uint64_t object)
{BEGIN(0x1928e8);dds3EffectPartDeleteO(sx(word(o+0x64)));dds3EffectPartDeleteO(sx(word(o+0x60)));ps2PoolRelease(o);}
void ps2EffectRelease_001948e0(uint64_t object)
{
 BEGIN(0x1948e0);uint64_t count=sx(word(o+0x58));uint32_t array=word(o+0x164),i=0;
 if(count)do{ps2EffectRelease_001785e8(sx(word(array)));array+=24;i++;}while(sx(i)<count);
 array=word(o+0x174);uint64_t length=sx((uint32_t)count<<2);
 if(array){i=0;if(length)do{uint32_t child=word(array);array+=4;i++;if(child)dds3EffectPartDeleteO(sx(child));}while(sx(i)<length);ps2MemoryHandleFree(word(o+0x178));}
 ps2MemoryHandleFree(word(o+0x17c));
}
#undef BEGIN

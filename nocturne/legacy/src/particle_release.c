/* Complete original billboard and particle destructor family. */
#include "particle_release.h"
#include "effect_release.h"
#include "script_construction.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "process_shutdown.h"
#include "libc_printf.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static uint32_t half(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int64_t signedWord(uint32_t v){return (int64_t)v-(v&0x80000000u?INT64_C(4294967296):0);}
void ps2BillTextureRelease(uint64_t resource)
{
 uint32_t r=(uint32_t)resource,count=word(r+8)-1;put(r+8,count);
 if(count)return;
 (void)ps2LibcPrintf(0x532c58);ps2TextureDeferredRelease(sx(word(r)));ps2MemoryHandleFree(word(r+64));
}
void ps2BillAnimationRelease(uint64_t resource)
{
 uint32_t r=(uint32_t)resource,count=word(r+20)-1;put(r+20,count);
 if(count)return;
 (void)ps2LibcPrintf(0x532d18);
 int64_t length=signedWord(word(r+16));uint32_t i=0;
 if(length>0)do{uint32_t data=word(r+24);uint64_t item=sx(word(data+(i<<2)));i++;ps2BillTextureRelease(item);length=signedWord(word(r+16));}while(signedWord(i)<length);
 ps2MemoryHandleFree(word(r));
}
void ps2BillNormalDelete(uint64_t object)
{uint32_t o=(uint32_t)object;ps2BillTextureRelease(sx(word(o+48)));ps2PoolRelease(o);}
void ps2BillAnimationDelete(uint64_t object)
{uint32_t o=(uint32_t)object;ps2BillAnimationRelease(sx(word(o+48)));ps2PoolRelease(o);}
void dds3BillboardDelete(uint64_t object)
{uint32_t o=(uint32_t)object;nocturneCallParticleRelease(word(0x317088+half(o+44)*12),object);}
void ps2ParticlePhysicsRelease(uint64_t resource){ps2MemoryHandleFree(word((uint32_t)resource+12));}
void ps2ParticleBackingRelease(uint64_t resource){ps2MemoryHandleFree(word((uint32_t)resource));}
void Eff_ModelTrackPolyListDelete(uint64_t list)
{
 uint32_t l=(uint32_t)list,i=0;uint64_t count=sx(word(l+4));
 if(count)do{uint32_t data=word(l);uint64_t item=sx(word(data+(i<<2)));i++;Eff_ModelTrackPolyDelete(item);}while(sx(i)<count);
 ps2MemoryHandleFree(word(l+8));
}
void dds3Particle_BasicDelete(uint64_t object)
{
 uint32_t o=(uint32_t)object;
 switch(half(o+48)){
 case 1:ps2ParticlePhysicsRelease(sx(word(o+56)));break;
 case 2:dds3TrackPolyDelete(sx(word(o+64)));break;
 case 3:dds3TrackPolyDelete(sx(word(o+68)));break;
 case 4:Eff_ModelTrackPolyListDelete(sx(word(o+68)));break;
 default:break;
 }
 dds3BillboardDelete(sx(word(o+244)));ps2ParticleBackingRelease(sx(word(o+248)));
}
#define PARTICLE_LEAF(kind) void ps2ParticleKind##kind##Delete(uint64_t object){dds3Particle_BasicDelete(object);ps2PoolRelease((uint32_t)object);}
PARTICLE_LEAF(0) PARTICLE_LEAF(1) PARTICLE_LEAF(2) PARTICLE_LEAF(3)
PARTICLE_LEAF(4) PARTICLE_LEAF(5) PARTICLE_LEAF(6) PARTICLE_LEAF(7)
PARTICLE_LEAF(8) PARTICLE_LEAF(9) PARTICLE_LEAF(10)
#undef PARTICLE_LEAF
void ps2ParticleKind11Delete(uint64_t object)
{ps2MemoryHandleFree(word((uint32_t)object+380));dds3Particle_BasicDelete(object);ps2PoolRelease((uint32_t)object);}
void ps2ParticleKind12Delete(uint64_t object)
{uint32_t handle=word((uint32_t)object+372);if(handle)ps2MemoryHandleFree(handle);dds3Particle_BasicDelete(object);ps2PoolRelease((uint32_t)object);}
void dds3ParticleDelete(uint64_t object)
{uint32_t o=(uint32_t)object;nocturneCallParticleRelease(word(0x317278+half(o+320)*12),object);}
void dds3ParticleExpDelete(uint64_t object)
{uint32_t o=(uint32_t)object;nocturneCallParticleRelease(word(0x317278+half(o+320)*12),object);}

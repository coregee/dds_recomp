/* Original model-track and special-polygon release bodies. Guest pointers and
 * release order are retained; Unity's managed ownership is only a name reference. */
#include "effect_release.h"
#include "model_cleanup.h"
#include "script_construction.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static uint32_t half(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
void ps2HermitianTrackPolyRelease(uint64_t record)
{uint32_t r=(uint32_t)record;ps2MaterialDeferredRelease(sx(word(r+32)));ps2MemoryHandleFree(word(r+36));}
void ps2SpecialTrackBundleRelease(uint64_t bundle)
{uint32_t b=(uint32_t)bundle;ps2HermitianTrackPolyRelease(sx(word(b+48)));ps2PoolRelease(b);}
void Eff_ModelTrackPolyDelete(uint64_t effect)
{
 uint32_t e=(uint32_t)effect;
 if(ps2ModelNeedsSpecialRelease(sx(word(e)))){ps2SpecialTrackBundleRelease(sx(word(e+56)));put(e+56,0);}
 uint32_t record=word(e+56);if(record)ps2HermitianTrackPolyRelease(sx(record));ps2PoolRelease(e);
}
void dds3TrackPolyDelete(uint64_t record)
{uint32_t r=(uint32_t)record;ps2MaterialDeferredRelease(sx(word(r+32)));ps2MemoryHandleFree(word(r+16));}
void ps2SpPolyKind0Delete(uint64_t object)
{uint32_t o=(uint32_t)object;dds3TrackPolyDelete(sx(word(o+220)));ps2PoolRelease(o);}
void ps2SpPolyKind1Delete(uint64_t object)
{uint32_t o=(uint32_t)object;dds3TrackPolyDelete(sx(word(o+240)));ps2MemoryHandleFree(word(o+248));}
void ps2SpPolyKind2Delete(uint64_t object)
{uint32_t o=(uint32_t)object;dds3TrackPolyDelete(sx(word(o+224)));ps2MemoryHandleFree(word(o+232));}
void ps2SpPolyKind3Delete(uint64_t object)
{uint32_t o=(uint32_t)object;dds3TrackPolyDelete(sx(word(o+244)));ps2MemoryHandleFree(word(o+252));}
void dds3SpPolyDelete(uint64_t object)
{uint32_t o=(uint32_t)object;nocturneCallSpPolyDestructor(word(0x317678+half(o+176)*12),object);}

/* Original Magatsuhi and P2A polygon ownership. Native unchecked reads and
 * callback order are retained; Unity provides semantic names only. */
#include "magatuhi_release.h"
#include "particle_release.h"
#include "model_cleanup.h"
#include "script_construction.h"
#include "memory_handle_allocation.h"
#include "material_construction_release.h"
#include <string.h>
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,nocturneResolveScriptConstructionAddress(p),4);return v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
void ps2Bezier4PRelease(uint64_t object){ps2MemoryHandleFree(word((uint32_t)object+8));}
void ps2MagatuhiBillRelease(uint64_t object){ps2MemoryHandleFree(word((uint32_t)object+52));}
void effMagatuhiDelete(uint64_t object)
{uint32_t o=(uint32_t)object;ps2MagatuhiBillRelease(sx(word(o+28)));ps2PoolRelease(o);}
void effMagaSmokeConvDelete(uint64_t object)
{uint32_t o=(uint32_t)object;ps2Bezier4PRelease(sx(word(o+384)));effMagatuhiDelete(sx(word(o+396)));ps2MemoryHandleFree(word(o+400));}
void effMagaPoint4Delete(uint64_t object)
{uint32_t o=(uint32_t)object;ps2Bezier4PRelease(sx(word(o+388)));effMagatuhiDelete(sx(word(o+392)));ps2MemoryHandleFree(word(o+396));}
void effMagaCylinderDelete(uint64_t object)
{uint32_t o=(uint32_t)object;effMagatuhiDelete(sx(word(o+288)));ps2MemoryHandleFree(word(o+296));}
void effMagaSpiralDelete(uint64_t object)
{uint32_t o=(uint32_t)object;effMagatuhiDelete(sx(word(o+292)));ps2MemoryHandleFree(word(o+300));}
void effMagaSmokeDelete(uint64_t object)
{uint32_t o=(uint32_t)object;effMagatuhiDelete(sx(word(o+292)));ps2MemoryHandleFree(word(o+296));}
void dds3MagatuhiParDelete(uint64_t object)
{uint32_t o=(uint32_t)object;nocturneCallMagatuhiRelease(word(0x320048+word(o)*24),sx(word(o+4)));ps2PoolRelease(o);}
void dds3P2APolygonDelete(uint64_t object)
{uint32_t o=(uint32_t)object;ps2MaterialDeferredRelease(sx(word(o+132)));dds3BillboardDelete(sx(word(o+128)));ps2PoolRelease(o);}

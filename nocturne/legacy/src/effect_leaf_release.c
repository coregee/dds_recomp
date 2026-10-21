/* Original PCP cleanup leaves. Recipes and field order are in recover_effect_leaves.py. */
#include "effect_leaf_release.h"
#include "effect_release.h"
#include "particle_release.h"
#include "model_cleanup.h"
#include "process_shutdown.h"
#include "libc_printf.h"
#include "script_construction.h"
#include "memory_handle_allocation.h"
#include "material_construction_release.h"
#include <string.h>
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,nocturneResolveScriptConstructionAddress(p),4);return v;}
static void put(uint32_t p,uint32_t v){memcpy(nocturneResolveScriptConstructionAddress(p),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
void ps2EffectRelease_001764f0(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001764f0,object);
 uint32_t o=(uint32_t)object;
 nocturneTraceEffectLeafRelease(0x001660d0,sx(word(o+92)));dds3TrackPolyDelete(sx(word(o+92)));
 ps2MemoryHandleFree(word(o+96));
}
void ps2EffectRelease_001785e8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001785e8,object);
 uint32_t o=(uint32_t)object;
 nocturneTraceEffectLeafRelease(0x001660d0,sx(word(o+96)));dds3TrackPolyDelete(sx(word(o+96)));
 ps2MemoryHandleFree(word(o+100));
}
void ps2EffectRelease_001790e0(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001790e0,object);
 uint32_t o=(uint32_t)object;
 nocturneTraceEffectLeafRelease(0x001660d0,sx(word(o+92)));dds3TrackPolyDelete(sx(word(o+92)));
 nocturneTraceEffectLeafRelease(0x001660d0,sx(word(o+96)));dds3TrackPolyDelete(sx(word(o+96)));
 ps2MemoryHandleFree(word(o+100));
}
void ps2EffectRelease_00179b08(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00179b08,object);
 uint32_t o=(uint32_t)object;
 nocturneTraceEffectLeafRelease(0x001660d0,sx(word(o+80)));dds3TrackPolyDelete(sx(word(o+80)));
 ps2MemoryHandleFree(word(o+84));
}
void ps2EffectRelease_0017d1f8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0017d1f8,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_00183060(sx(word(o+68)));
 ps2MemoryHandleFree(word(o+64));
}
void ps2EffectRelease_0017d8a8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0017d8a8,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_00182c40(sx(word(o+84)));
 ps2MemoryHandleFree(word(o+80));
}
void ps2EffectRelease_0017e260(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0017e260,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_00182c40(sx(word(o+92)));
 ps2MemoryHandleFree(word(o+88));
}
void ps2EffectRelease_0017ea88(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0017ea88,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_00183368(sx(word(o+100)));
 ps2MemoryHandleFree(word(o+96));
}
void ps2EffectRelease_0017f388(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0017f388,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_00182c40(sx(word(o+124)));
 ps2MemoryHandleFree(word(o+120));
}
void ps2EffectRelease_0017fc00(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0017fc00,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_00182c40(sx(word(o+96)));
 ps2MemoryHandleFree(word(o+92));
}
void ps2EffectRelease_00182c40(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00182c40,object);
 uint32_t o=(uint32_t)object;
 ps2MaterialDeferredRelease(sx(word(o+104)));
 ps2MemoryHandleFree(word(o+108));
}
void ps2EffectRelease_00183060(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00183060,object);
 uint32_t o=(uint32_t)object;
 ps2MaterialDeferredRelease(sx(word(o+104)));
 ps2MemoryHandleFree(word(o+108));
}
void ps2EffectRelease_00183368(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00183368,object);
 uint32_t o=(uint32_t)object;
 ps2MaterialDeferredRelease(sx(word(o+104)));
 ps2MemoryHandleFree(word(o+108));
}
void ps2EffectRelease_00185d88(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00185d88,object);
 uint32_t o=(uint32_t)object;
 if(word(o+48)){dds3ScatterPolyListTexResourceDelete(sx(word(o+48)));}
 ps2MaterialDeferredRelease(sx(word(o+40)));
 ps2MemoryHandleFree(word(o+44));
}
void dds3ScatterPolyListTexResourceDelete(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00186080,object);
 uint32_t o=(uint32_t)object;
 uint32_t count=word(o+4)-1;put(o+4,count);if(!count){ps2TextureDeferredRelease(sx(word(o)));ps2PoolRelease(o);}
}
void ps2EffectRelease_00186390(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00186390,object);
 uint32_t o=(uint32_t)object;
 dds3ScatterPolyListDelete(sx(word(o+388)));
 ps2MemoryHandleFree(word(o+392));
}
void ps2EffectRelease_001884c8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001884c8,object);
 uint32_t o=(uint32_t)object;
 dds3ScatterPolyListDelete(sx(word(o+308)));
 ps2MemoryHandleFree(word(o+312));
}
void dds3ScatterPolyListDelete(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00188da0,object);
 uint32_t o=(uint32_t)object;
 if(word(o+124)){dds3ScatterPolyListTexResourceDelete(sx(word(o+124)));}
 ps2MaterialDeferredRelease(sx(word(o+116)));
 ps2MemoryHandleFree(word(o+120));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_001893d0(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001893d0,object);
 uint32_t o=(uint32_t)object;
 nocturneTraceEffectLeafRelease(0x001660d0,sx(word(o+104)));dds3TrackPolyDelete(sx(word(o+104)));
 ps2EffectRelease_00189b68(sx(word(o+108)));
 ps2MemoryHandleFree(word(o+112));
}
void ps2EffectRelease_00189b68(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00189b68,object);
 uint32_t o=(uint32_t)object;
 ps2MaterialDeferredRelease(sx(word(o+108)));
 dds3NeedleModelVNCListDelete(object);
 ps2MemoryHandleFree(word(o+112));
}
void dds3NeedleModelVNCListDelete(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018a070,object);
 uint32_t o=(uint32_t)object;
 if(word(o+104)){(void)ps2LibcPrintf(0x533c90,sx(word(o+104)));ps2MemoryHandleFree(word(o+104));}
}
void ps2EffectRelease_0018a1d8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018a1d8,object);
 uint32_t o=(uint32_t)object;
 nocturneTraceEffectLeafRelease(0x0015cf40,sx(word(o+28)));dds3BillboardDelete(sx(word(o+28)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018c000(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018c000,object);
 uint32_t o=(uint32_t)object;
 for(uint32_t i=0;i<12;i++){ps2EffectRelease_001785e8(sx(word(o+28+i*4)));}
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018c478(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018c478,object);
 uint32_t o=(uint32_t)object;
 for(uint32_t i=0;i<12;i++){ps2EffectRelease_001785e8(sx(word(o+28+i*4)));}
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018c910(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018c910,object);
 uint32_t o=(uint32_t)object;
 for(uint32_t i=0;i<30;i++){ps2EffectRelease_001785e8(sx(word(o+28+i*4)));}
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018cd88(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018cd88,object);
 uint32_t o=(uint32_t)object;
 for(uint32_t i=0;i<12;i++){ps2EffectRelease_001785e8(sx(word(o+28+i*4)));}
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018d0f8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018d0f8,object);
 uint32_t o=(uint32_t)object;
 for(uint32_t i=0;i<12;i++){ps2EffectRelease_001785e8(sx(word(o+28+i*4)));}
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018d468(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018d468,object);
 uint32_t o=(uint32_t)object;
 for(uint32_t i=0;i<8;i++){ps2EffectRelease_001785e8(sx(word(o+28+i*4)));}
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018d678(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018d678,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001764f0(sx(word(o+28)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018db50(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018db50,object);
 uint32_t o=(uint32_t)object;
 for(uint32_t i=0;i<30;i++){ps2EffectRelease_001785e8(sx(word(o+28+i*4)));}
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018dd60(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018dd60,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001764f0(sx(word(o+28)));
 ps2PoolRelease((uint32_t)object);
}
void ps2SharedNeedleInstanceDelete(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018e000,object);
 uint32_t o=(uint32_t)object;
 ps2PoolRelease(o);uint32_t count=word(0x54f1e8)-1;put(0x54f1e8,count);if(!count){ps2EffectRelease_001a2098(sx(word(word(0x551dd0)+56)));ps2PoolRelease(word(0x551dd0));}
}
void ps2EffectRelease_0018e260(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018e260,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001a2098(sx(word(o+52)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018e4e0(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018e4e0,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001a2eb8(sx(word(o+56)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018e838(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018e838,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001a2098(sx(word(o+56)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018eaf8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018eaf8,object);
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018ed10(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018ed10,object);
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018efa8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018efa8,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001a23e0(sx(word(o+52)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018f318(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018f318,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001a28c8(sx(word(o+52)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018f5c0(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018f5c0,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001764f0(sx(word(o+28)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_0018f870(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x0018f870,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001764f0(sx(word(o+28)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_00192a90(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00192a90,object);
 (void)object;
}
void ps2EffectRelease_00192f90(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00192f90,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001785e8(sx(word(o+32)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_001932e0(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001932e0,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001764f0(sx(word(o+48)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_001935c8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001935c8,object);
 uint32_t o=(uint32_t)object;
 ps2MaterialDeferredRelease(sx(word(o+168)));
 ps2MemoryHandleFree(word(o+172));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_00193b58(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x00193b58,object);
 uint32_t o=(uint32_t)object;
 ps2EffectRelease_001935c8(sx(word(o+92)));
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_001a2098(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001a2098,object);
 ps2PoolRelease((uint32_t)object);
}
void ps2EffectRelease_001a23e0(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001a23e0,object);
 uint32_t o=(uint32_t)object;
 ps2MemoryHandleFree(word(o+48));
}
void ps2EffectRelease_001a28c8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001a28c8,object);
 uint32_t o=(uint32_t)object;
 ps2MemoryHandleFree(word(o+48));
}
void ps2EffectRelease_001a2eb8(uint64_t object)
{
 nocturneTraceEffectLeafRelease(0x001a2eb8,object);
 ps2PoolRelease((uint32_t)object);
}

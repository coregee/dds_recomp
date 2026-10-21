/* Original raw-vector stores and major/track position dispatch. */
#include "effect_position.h"
#include "pcp_construction.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER() nocturneResourceFrameEnter(16)
#define LEAVE() nocturneResourceFrameLeave(16)
static void *at(uint32_t p){return nocturneResolvePcpConstructionAddress(p);}
#else
#define ENTER() ((void)0)
#define LEAVE() ((void)0)
static void *at(uint32_t p){return (void *)(uintptr_t)p;}
#endif
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void copy(uint32_t p,uint32_t v){uint32_t words[4];memcpy(words,at(v),16);memcpy(at(p),words,16);}
static void call(uint32_t target,uint64_t object,uint64_t vector){
#if UINTPTR_MAX > UINT32_MAX
 nocturneEffectPositionCall(target,object,vector);
#else
 ((void(*)(uint64_t,uint64_t))(uintptr_t)target)(object,vector);
#endif
}
void ps2MajorEffectSetPosition(uint64_t object,uint64_t vector){
 ENTER();uint32_t p=(uint32_t)object,target=word(0x316f04+word(p)*48);
 call(target,sx(word(p+8)),vector);LEAVE();
}
void ps2BillboardSetPositionVector(uint64_t object,uint64_t vector){copy((uint32_t)object,(uint32_t)vector);}
void ps2MaterialBillboardSetPosition(uint64_t object,uint64_t vector){
 ENTER();uint64_t child=sx(word((uint32_t)object+128));LEAVE();ps2BillboardSetPositionVector(child,vector);
}
void ps2PolygonSetPosition(uint64_t object,uint64_t vector){copy((uint32_t)object,(uint32_t)vector);}
void ps2PolygonAlternateSetPosition(uint64_t object,uint64_t vector){copy((uint32_t)object,(uint32_t)vector);}
void ps2SpecialPolygonSetPosition(uint64_t object,uint64_t vector){copy((uint32_t)object,(uint32_t)vector);}
void ps2MagatuhiWrapperSetPosition(uint64_t object,uint64_t vector){
 ENTER();uint32_t p=(uint32_t)object,target=word(0x32004c+word(p)*24);
 if(target)call(target,sx(word(p+4)),vector);LEAVE();
}
void ps2MagatuhiType2SetPosition(uint64_t object,uint64_t vector){copy((uint32_t)object+64,(uint32_t)vector);}
void ps2MagatuhiType3SetPosition(uint64_t object,uint64_t vector){copy((uint32_t)object+64,(uint32_t)vector);}
void ps2MagatuhiType4SetPosition(uint64_t object,uint64_t vector){copy((uint32_t)object+64,(uint32_t)vector);}

/* Original raw effect dispatchers. Source offsets and table indices retain
 * native word wrapping; constructors and billboard ownership execute normally. */
#include "raw_effect_creation.h"
#include "emitter_copy.h"
#include "special_polygon_copy.h"
#include "emitter_initialization.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveRawEffectAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static float f32(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static uint64_t particle(uint64_t type,uint64_t source){uint32_t target=r32(0x317270+(uint32_t)type*12u);
#if UINTPTR_MAX > UINT32_MAX
 return nocturneCallEmitterCopy(target,source);
#else
 return ((uint64_t (*)(uint64_t))(uintptr_t)target)(source);
#endif
}
/* 00164B90 */
uint64_t dds3ParticleCreate(uint64_t type,uint64_t source){uint64_t p=particle(type,source);w16((uint32_t)p+0x140,(uint16_t)type);return p;}
/* 00164FF8: resource header followed by a relative emitter record. Only
 * kind3 with offset0 omits the billboard. The other branch mutates the input
 * clone marker before construction, then owns a newly created billboard. */
uint64_t dds3ParticleExpCreate(uint64_t type,uint64_t source){uint32_t s=(uint32_t)source,offset=r32(s+4),record=s+offset+16u;uint64_t p;
 if(r32(s)==3&&offset==0)p=particle(type,sx(record));
 else{w32(record+40,UINT32_MAX);p=particle(type,sx(record));uint64_t bill=dds3BillboardCreate(sx(r32(s)),sx(s+16));
  dds3BillboardSetScale(bill,f32(r32((uint32_t)p+16)),f32(r32((uint32_t)p+20)));
  dds3BillboardSetMode(bill,(uint64_t)(int64_t)(int16_t)r16((uint32_t)p+44));
  dds3BillboardSetAnimColorAdvMode(bill);w32((uint32_t)p+244,(uint32_t)bill);
 }
 w16((uint32_t)p+320,(uint16_t)type);return sx((uint32_t)p);
}
/* 00169CD8 */
uint64_t dds3SpPolyCreate(uint64_t type,uint64_t source){uint32_t target=r32(0x317670+(uint32_t)type*12u);uint64_t p;
#if UINTPTR_MAX > UINT32_MAX
 p=nocturneCallSpecialPolygonCopy(target,source);
#else
 p=((uint64_t (*)(uint64_t))(uintptr_t)target)(source);
#endif
 w16((uint32_t)p+176,(uint16_t)type);w16((uint32_t)p+178,1);return p;
}

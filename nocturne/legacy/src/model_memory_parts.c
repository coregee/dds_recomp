/* Original memory bundle loader, model-part initialization and colour dispatch. */
#include "model_memory_parts.h"
#include "model_pac_loading.h"
#include "pac_parser.h"
#include "resource_loader_flow.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "material_motion_scalars.h"
#include "emitter_initialization.h"
#include "basic_pose.h"
#include "ee_vu_rotation.h"
#include "ps2_memory.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelMemoryPartsAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void vector(uint32_t a,const uint32_t v[4]){memcpy(at(a),v,16);}
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void call(uint32_t target,uint64_t object,uint64_t color){nocturneModelMemoryColorCall(target,object,color);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void call(uint32_t target,uint64_t object,uint64_t color){((void(*)(uint64_t,uint64_t))(uintptr_t)target)(object,color);}
#endif
void ps2PacSetReferenceFlag(uint64_t parser){uint8_t *p=at((uint32_t)parser+1);*p=(uint8_t)(*p|1);}
void ps2ModelBundleLoadMemory(uint64_t group,uint64_t id,uint64_t flags,uint64_t data,uint64_t size){
 ENTER(0x70);uint8_t parser[64];
#if UINTPTR_MAX > UINT32_MAX
 uint32_t p=nocturneModelMemoryParserLocal(parser,64);
#else
 uint32_t p=(uint32_t)(uintptr_t)parser;
#endif
 ps2PacInitialize(sx(p),0);if(flags&2)ps2PacSetReferenceFlag(sx(p));(void)ps2PacDecodeChunk(sx(p),data,size);(void)ps2ModelRegisterPac(sx(r32(p+48)),group,id,flags);ps2PacReleaseRecords(sx(p));
#if UINTPTR_MAX > UINT32_MAX
 nocturneModelMemoryParserEnd();
#endif
 LEAVE(0x70);
}
void ps2ModelSetPositionVu(uint64_t context){uint32_t v[4],zero[4];EE_ROT_VU_READ(10,v);EE_ROT_VU_READ(0,zero);v[3]=zero[3];EE_ROT_VU_WRITE(10,v);vector(r32((uint32_t)context+24)+80,v);}
void ps2ModelSetRotationVu(uint64_t context){ENTER(0x10);uint32_t v[4],p=(uint32_t)context;EE_ROT_VU_READ(10,v);vector(r32(p+24)+96,v);sdfQuatToMatrix();EE_ROT_VU_READ(28,v);vector(r32(p+24)+32,v);EE_ROT_VU_READ(29,v);vector(r32(p+24)+48,v);EE_ROT_VU_READ(30,v);vector(r32(p+24)+64,v);LEAVE(0x10);}
void ps2ModelSetScaleVu(uint64_t context){uint32_t v[4];EE_ROT_VU_READ(10,v);vector(r32((uint32_t)context+24)+112,v);}
void ps2ModelSetColor(uint64_t context,uint64_t color){ENTER(0x10);w32(r32((uint32_t)context+24)+28,(uint32_t)color);uint64_t attached=(color&UINT64_C(0xffffffffff000000))|UINT64_C(0x00808080);LEAVE(0x10);ps2ModelSetAttachedColor(context,attached);}
void ps2ModelSetAttachedColor(uint64_t context,uint64_t color){ENTER(0x20);uint32_t node=r32((uint32_t)context+20);while(node){ps2ModelSetEffectColor(context,sx(node),color);node=r32(node);}LEAVE(0x20);}
void ps2ModelSetEffectColor(uint64_t context,uint64_t node,uint64_t color){(void)context;ENTER(0x10);uint32_t p=(uint32_t)node,kind=r16(p+4);if(!kind){uint64_t b=sx(r32(p+8));LEAVE(0x10);ps2BillboardSetColor(b,color);return;}if(kind==1)ps2EffectSetColor(sx(r32(p+8)),color);LEAVE(0x10);}
void ps2EffectSetColor(uint64_t effect,uint64_t color){ENTER(0x10);uint32_t p=(uint32_t)effect,kind=r32(p),target=r32(0x316f0c+kind*48);call(target,sx(r32(p+8)),color);LEAVE(0x10);}
void ps2BillboardSetColor(uint64_t billboard,uint64_t color){w32((uint32_t)billboard+36,(uint32_t)color);}
void ps2ParticleSetColor(uint64_t object,uint64_t color){w32((uint32_t)object+240,(uint32_t)color);}
void ps2ExpParticleSetColor(uint64_t object,uint64_t color){w32((uint32_t)object+240,(uint32_t)color);}
void ps2SpecialPolygonSetColor(uint64_t object,uint64_t color){w32((uint32_t)object+96,(uint32_t)color);}
void ps2TrackType2SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+292,(uint32_t)color);}
void ps2TrackType3SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+296,(uint32_t)color);}
void ps2TrackType4SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+288,(uint32_t)color);}
void ps2TrackBundleSetColor(uint64_t object,uint64_t color){ENTER(0x10);uint32_t p=(uint32_t)object,target=r32(0x320050+r32(p)*24);if(target)call(target,sx(r32(p+4)),color);LEAVE(0x10);}
void ps2EffectPartSetColor(uint64_t object,uint64_t color){ENTER(0x10);uint32_t p=(uint32_t)object,target=r32(0x31de5c+(uint32_t)r16(p)*40);if(target)call(target,sx(r32(p+4)),color);LEAVE(0x10);}
void ps2PcpWrapperSetColor(uint64_t object,uint64_t color){ENTER(0x10);uint32_t p=(uint32_t)object,target=r32(0x31dfac+r32(p)*40);if(target)call(target,sx(r32(p+8)),color);LEAVE(0x10);}
void ps2PcpType0SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+80,(uint32_t)color);}
void ps2PcpType1SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+88,(uint32_t)color);}
void ps2PcpType2SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+76,(uint32_t)color);}
void ps2PcpType3SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+16,(uint32_t)color);}
void ps2PcpType4SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+16,(uint32_t)color);}
void ps2PcpType5SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+16,(uint32_t)color);}
void ps2PcpType6SetColor(uint64_t object,uint64_t color){w32((uint32_t)object+4916,(uint32_t)color);}
void ps2ModelPartSetColor(uint64_t object,uint64_t color){ENTER(0x10);LEAVE(0x10);ps2ModelSetColor(object,color);}
void ps2MaterialBillboardSetColor(uint64_t object,uint64_t color){ENTER(0x10);uint64_t b=sx(r32((uint32_t)object+128));LEAVE(0x10);ps2BillboardSetColor(b,color);}
uint64_t ps2MaterialBillboardCreate(uint64_t source){ENTER(0x20);uint32_t p=ps2PoolAllocate(136),b=(uint32_t)dds3BillboardCreate(1,source);w32(p+128,b);uint32_t m=ps2MatCreate();w32(p+132,m);sdfMatSetConstant(at(m),0x3f800000);uint32_t zero[4],v[4];EE_ROT_VU_READ(0,zero);for(unsigned i=0;i<4;i++){for(unsigned j=0;j<4;j++)v[j]=i==j?zero[3]:zero[0];vector(p+64+i*16,v);}LEAVE(0x20);return sx(p);}
void ps2ModelPartInitialize(uint64_t context){ENTER(0x10);uint32_t v[4];memcpy(v,at(0x31df60),16);EE_ROT_VU_WRITE(10,v);ps2ModelSetPositionVu(context);memcpy(v,at(0x31df70),16);EE_ROT_VU_WRITE(10,v);ps2ModelSetRotationVu(context);memcpy(v,at(0x31df80),16);EE_ROT_VU_WRITE(10,v);ps2ModelSetScaleVu(context);ps2ModelSetColor(context,UINT64_C(0xffffffff80808080));uint32_t p=(uint32_t)context;if(r32(p+28)){ps2ModelChangeMotionDefault(context,0,0);w32(r32(p+28)+32,0x3f800000);}w32(p,r32(p)&0xfffffffe);LEAVE(0x10);}
uint64_t ps2ModelPartFromBundle(uint64_t blob){ENTER(0x10);uint32_t b=(uint32_t)blob;ps2ModelBundleLoadMemory(7,sx(r32(0x54f1e4)),0x101,sx(b+16),sx(r32(b)));uint64_t context=ps2ModelContextCreate(7,sx(r32(0x54f1e4)));ps2ModelPartInitialize(context);w32(0x54f1e4,r32(0x54f1e4)+1);LEAVE(0x10);return context;}

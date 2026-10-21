/* Original PCP position/scale/area callbacks. Names describe verified native
 * roles; managed reference guards and layouts are not imported. */
#include "pcp_controls.h"
#include "ee_vu_rotation.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER() nocturneResourceFrameEnter(16)
#define LEAVE() nocturneResourceFrameLeave(16)
static void *at(uint32_t p){return nocturneResolvePcpControlsAddress(p);}
#else
#define ENTER() ((void)0)
#define LEAVE() ((void)0)
static void *at(uint32_t p){return (void *)(uintptr_t)p;}
#endif
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void position(uint32_t destination,uint32_t source){uint32_t v[4];memcpy(v,at(source),16);memcpy(at(destination),v,16);}
static void scalar(float v,uint32_t p){memcpy(at(p),&v,4);}
void ps2PcpType0SetPosition(uint64_t o,uint64_t v){position((uint32_t)o,(uint32_t)v);}
void ps2PcpType2SetPosition(uint64_t o,uint64_t v){position((uint32_t)o,(uint32_t)v);}
void ps2PcpType3SetPosition(uint64_t o,uint64_t v){position((uint32_t)o,(uint32_t)v);}
void ps2PcpType4SetPosition(uint64_t o,uint64_t v){position((uint32_t)o,(uint32_t)v);}
void ps2PcpType5SetPosition(uint64_t o,uint64_t v){position((uint32_t)o,(uint32_t)v);}
void ps2PcpType6SetPosition(uint64_t o,uint64_t v){position((uint32_t)o+0xaf0,(uint32_t)v);}
void ps2PcpType1SetPosition(uint64_t object,uint64_t vector){
 uint32_t p=(uint32_t)object,previous[4],next[4],base[4],delta[4],moved[4];
 memcpy(previous,at(p+0x10),16);EE_ROT_VU_WRITE(10,previous);
 memcpy(next,at((uint32_t)vector),16);EE_ROT_VU_WRITE(11,next);
 memcpy(at(p+0x10),next,16);
 for(unsigned k=0;k<4;k++)delta[k]=(uint32_t)EE_ROT_VU_SUB(next[k],previous[k]);
 EE_ROT_VU_WRITE(11,delta);
 /* The base is reloaded after publishing the new origin, as in the native code. */
 memcpy(base,at(p),16);EE_ROT_VU_WRITE(10,base);
 for(unsigned k=0;k<4;k++)moved[k]=(uint32_t)EE_ROT_VU_ADD(base[k],delta[k]);
 EE_ROT_VU_WRITE(10,moved);memcpy(at(p),moved,16);
}
void ps2PcpType3SetScale(float v,uint64_t o){scalar(v,(uint32_t)o+0x18);}
void ps2PcpType4SetScale(float v,uint64_t o){scalar(v,(uint32_t)o+0x14);}
void ps2PcpType5SetScale(float v,uint64_t o){scalar(v,(uint32_t)o+0x14);}
void ps2PcpType6SetScale(float v,uint64_t o){scalar(v,(uint32_t)o+0x1338);}
void ps2PcpType10SetArea(float v,uint64_t o){scalar(v,(uint32_t)o+0x1c);}
void ps2PcpType13SetArea(float v,uint64_t o){scalar(v,(uint32_t)o+0x18);}
void ps2PcpType26SetArea(float v,uint64_t o){scalar(v,(uint32_t)o+0x34);}
void ps2PcpSharedSetArea(float v){scalar(v,word(0x551dd0)+0x1c);}
static void vectorCall(uint32_t target,uint64_t o,uint64_t v){
#if UINTPTR_MAX > UINT32_MAX
 nocturnePcpControlsVectorCall(target,o,v);
#else
 ((void (*)(uint64_t,uint64_t))(uintptr_t)target)(o,v);
#endif
}
static void floatCall(uint32_t target,float v,uint64_t o){
#if UINTPTR_MAX > UINT32_MAX
 nocturnePcpControlsFloatCall(target,v,o);
#else
 ((void (*)(float,uint64_t))(uintptr_t)target)(v,o);
#endif
}
void ps2PcpWrapperSetPosition(uint64_t object,uint64_t vector){
 ENTER();uint32_t p=(uint32_t)object,target=word(0x31dfa0+word(p)*40);
 if(target)vectorCall(target,sx(word(p+8)),vector);LEAVE();
}
void ps2PcpWrapperSetDirection(uint64_t object,uint64_t matrix){
 ENTER();uint32_t p=(uint32_t)object,target=word(0x31dfb0+word(p)*40);
 if(target)vectorCall(target,sx(word(p+8)),matrix);LEAVE();
}
void ps2PcpWrapperSetArea(float area,uint64_t object){
 ENTER();uint32_t p=(uint32_t)object,target=word(0x31dfb4+word(p)*40);
 if(target)floatCall(target,area,sx(word(p+8)));LEAVE();
}

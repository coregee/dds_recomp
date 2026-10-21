/* Original PIB-driven attachment, cached-resource flags and motion cleanup. */
#include "model_effect_creation.h"
#include "model_motion_creation.h"
#include "model_track_creation.h"
#include "billboard_copy.h"
#include "magatuhi_creation.h"
#include "effect_release.h"
#include "effect_recursive_release.h"
#include "particle_release.h"
#include "material_construction_release.h"
#include "pib_chunk_leaves.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelEffectCreationAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t hs(uint16_t v){return (uint64_t)(int64_t)(int16_t)v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t original(const void *p){if(!p)return 0;
#if UINTPTR_MAX > UINT32_MAX
 return sx(nocturneOriginalModelEffectCreationAddress(p));
#else
 return (uintptr_t)p;
#endif
}
void ps2ModelCreateCopiedEffects(uint64_t model,uint64_t record,uint64_t group,uint64_t type,uint64_t target){uint32_t m=(uint32_t)model,r=(uint32_t)record;uint64_t resource=mdlGetEffectResrc(model,half(r+14));if(!resource)return;uint32_t root=word(m+24),index=word(r+8),remaining=half(r+12),time=word(r+4)>16?word(r+16):0;do{uint64_t position=ps2ModelPositionFind(sx(root),sx(index));index++;if(position){uint32_t node=(uint32_t)mdlCreateEffectCtrlr(model,type,group);uint64_t object;
#if UINTPTR_MAX > UINT32_MAX
 object=nocturneCallModelEffectCopy((uint32_t)target,resource);
#else
 object=((uint64_t(*)(uint64_t))(uintptr_t)target)(resource);
#endif
 put(node+8,(uint32_t)object);put(node+12,(uint32_t)resource);put(node+16,(uint32_t)position);put(node+20,time);}remaining--;}while(remaining);}
void mdlCreateEffect_TRACK(uint64_t model,uint64_t record,uint64_t group){uint32_t r=(uint32_t)record,params[13];params[0]=(uint32_t)model;params[1]=word(r+8);params[2]=word(r+12);params[3]=EE_FPU_CVT_S_W(half(r+16));params[4]=EE_FPU_CVT_S_W(half(r+18));params[5]=half(r+20);params[6]=*at(r+22);params[7]=3;params[8]=*at(r+23);params[9]=word(r+24);params[10]=word(r+28);params[11]=word(r+32);params[12]=word(r+36);uint32_t node=(uint32_t)mdlCreateEffectCtrlr(model,2,group);uint64_t object;
#if UINTPTR_MAX > UINT32_MAX
 object=nocturneCreateAttachedModelTrack(params);
#else
 object=ps2ModelTrackPolyCreate((uintptr_t)params);
#endif
 put(node+8,(uint32_t)object);}
void ps2ModelCreateCachedResourceEffect(uint64_t model,uint64_t record,uint64_t group){uint32_t m=(uint32_t)model,r=(uint32_t)record;uint64_t resource=mdlGetEffectResrc(model,half(r+18));if(!resource)return;uint32_t data=word((uint32_t)resource+8);if(*at(data+8))return;uint64_t cached=ps2ModelResourceFind(sx(word(r+8)));if(!cached)return;*at(data+8)=1;uint32_t node=(uint32_t)mdlCreateEffectCtrlr(model,3,group);put(node+12,data);put(node+16,(uint32_t)cached);put(node+8,m);put(node+20,word(r+12));*at(node+25)=1;*at(node+26)=*at(r+17);*at(node+27)=*at(r+16);}
void mdlCreateEffect(uint64_t model,uint64_t record,uint64_t group){switch(word((uint32_t)record)){case 1:ps2ModelCreateCopiedEffects(model,record,group,0,0x1df5c8);break;case 2:ps2ModelCreateCopiedEffects(model,record,group,1,0x1df600);break;case 3:mdlCreateEffect_TRACK(model,record,group);break;case 4:ps2ModelCreateColorTransitionRecord(model,record,group);break;case 5:ps2ModelCreateCachedResourceEffect(model,record,group);break;default:break;}}
void mdlGenEffect(uint64_t model,uint64_t cut,uint64_t group){void *chunk=mdlPibGetChunk(at((uint32_t)model),(int32_t)cut);if(!chunk)return;void *item=mdlPibGetFirstChunkItem(chunk);while(item){mdlCreateEffect(model,original(item),group);item=mdlPibGetNextChunkItem(item);}}
void mdlFreeEffect(uint64_t node){uint32_t n=(uint32_t)node;switch(half(n+4)){case 0:dds3BillboardDelete(sx(word(n+8)));break;case 1:dds3EffectDelete(sx(word(n+8)));break;case 2:Eff_ModelTrackPolyDelete(sx(word(n+8)));break;default:break;}ps2PoolRelease(n);}
void ps2ModelUnlinkEffectGroup(uint64_t model,uint64_t group){uint32_t link=(uint32_t)model+20;uint64_t node=sx(word(link));while(node){uint32_t n=(uint32_t)node;if(hs(half(n+6))==group){uint64_t next=sx(word(n));mdlFreeEffect(node);put(link,(uint32_t)next);node=next;}else{link=n;node=sx(word(n));}}}
void ps2ModelChangeMotionEffects(uint64_t model,uint64_t motion,uint64_t cut,uint64_t type,float lead,float duration){uint32_t m=(uint32_t)model;uint64_t controller=sx(word(word(m+24)+20));while(controller&&hs(half((uint32_t)controller+40))!=motion)controller=sx(word((uint32_t)controller));if(!controller)controller=mdlCreateMotion(model,motion);uint64_t group=hs(half((uint32_t)controller+42));put(m+32+((uint32_t)group<<2),(uint32_t)controller);if(!group)put(m+28,(uint32_t)controller);sdfMotionChangeBlend(controller,cut,type,lead,duration);sh(m+16,(uint16_t)motion);sh(m+18,(uint16_t)cut);ps2ModelUnlinkEffectGroup(model,group);mdlGenEffect(model,cut,group);}

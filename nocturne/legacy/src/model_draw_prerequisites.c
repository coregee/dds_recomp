/* Complete original bounds, VU-matrix, packet and surface-setup prerequisites. */
#include "model_draw_prerequisites.h"
#include "model_pose_evaluation.h"
#include "ee_vu_rotation.h"
#include "ee_vu_clip.h"
#include "resource_loader_flow.h"
#if defined(NOCTURNE_MODEL_RENDERER_PROFILE)
#include "model_renderer.h"
#endif
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t p){return nocturneResolveModelDrawAddress(p);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t p){return (void *)(uintptr_t)p;}
#endif
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void store(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void corner(unsigned destination,unsigned x,unsigned y,unsigned z){
 uint32_t row[4],value[4],acc[4],of[4],zero[4],out[4];
 EE_ROT_VU_READ(28,row);EE_ROT_VU_READ(x,value);
 for(unsigned lane=0;lane<4;lane++){uint64_t r=EE_ROT_VU_MUL(row[lane],value[0]);acc[lane]=(uint32_t)r;of[lane]=(uint32_t)(r>>32)&1;}
 EE_ROT_ACC_WRITE(acc,of);
 for(unsigned k=1;k<3;k++){
  EE_ROT_VU_READ(28+k,row);EE_ROT_VU_READ(k==1?y:z,value);
  for(unsigned lane=0;lane<4;lane++){uint64_t r=EE_ROT_VU_MAC(acc[lane],row[lane],value[k],of[lane],0);acc[lane]=(uint32_t)r;of[lane]=(uint32_t)(r>>32)&1;}
  EE_ROT_ACC_WRITE(acc,of);
 }
 EE_ROT_VU_READ(31,row);EE_ROT_VU_READ(0,zero);
 for(unsigned lane=0;lane<4;lane++)out[lane]=(uint32_t)EE_ROT_VU_MAC(acc[lane],row[lane],zero[3],of[lane],0);
 EE_ROT_VU_WRITE(destination,out);
}
uint64_t ps2ModelBoundsClipMask(uint64_t bounds){
 uint32_t b=(uint32_t)bounds,v[4];
 memcpy(v,at(b),12);v[3]=(v[2]&0x80000000u)?0xffffffffu:0;
#if defined(NOCTURNE_MODEL_RENDERER_PROFILE)
 if(g_modelRendererActive)EE_RENDERER_CPU_QUAD(2,v);
#endif
 EE_ROT_VU_WRITE(2,v);
 memcpy(v,at(b+12),12);v[3]=(v[2]&0x80000000u)?0xffffffffu:0;
#if defined(NOCTURNE_MODEL_RENDERER_PROFILE)
 if(g_modelRendererActive)EE_RENDERER_CPU_QUAD(6,v);
#endif
 EE_ROT_VU_WRITE(3,v);
 corner(4,2,2,2);corner(5,3,2,2);EE_VU_CLIP(4,4);
 corner(4,2,3,2);EE_VU_CLIP(5,5);
 corner(5,3,3,2);EE_VU_CLIP(4,4);
 corner(4,2,2,3);EE_VU_CLIP(5,5);corner(5,3,2,3);
 uint32_t first=EE_VU_CLIP_READ();EE_VU_CLIP(4,4);
 corner(4,2,3,3);EE_VU_CLIP(5,5);
 corner(5,3,3,3);EE_VU_CLIP(4,4);EE_VU_CLIP(5,5);
 uint32_t both=first&EE_VU_CLIP_READ();return both&(both>>6)&(both>>12)&(both>>18)&63;
}
void ps2ModelLoadComposeVuMatrix(uint64_t matrix){
 ENTER(16);for(unsigned k=0;k<4;k++){uint32_t row[4];memcpy(row,at((uint32_t)matrix+k*16),16);EE_ROT_VU_WRITE(24+k,row);}
 LEAVE(16);ps2ModelComposeVuMatrices();
}
uint64_t ps2ModelWriteNodeMatrixReference(uint64_t node,uint64_t packet,uint64_t frame){
 uint32_t p=(uint32_t)packet,address=(word((uint32_t)node+48)+((uint32_t)frame<<7))&0x0fffffffu;
 uint64_t tag=((uint64_t)address<<32)|0x30000008u;store(p+12,0x6c07c000);memcpy(at(p),&tag,8);store(p+8,0);return sx(p+16);
}
void ps2ModelDrawStoreWord(uint64_t value){store(0x5520d8,(uint32_t)value);}
void ps2ModelDrawCacheVector(uint64_t object){
 if(sx(word(0x5520dc))==object)return;
 uint32_t p=(uint32_t)object+16;store(0x5520dc,(uint32_t)object);uint32_t v[4];memcpy(v,at(p),16);
#if defined(NOCTURNE_MODEL_RENDERER_PROFILE)
 if(g_modelRendererActive)EE_RENDERER_CPU_QUAD(2,v);
#endif
 memcpy(at(0x58f060),v,16);
}
void ps2ModelDrawStoreFloat(float value){memcpy(at(0x5520e0),&value,4);}
void ps2ModelSetDrawSurfaces(uint64_t table,uint64_t first,uint64_t second,uint64_t third,uint64_t fourth){
 ENTER(16);uint32_t p=(uint32_t)table;store(p+12,(uint32_t)fourth);store(p,(uint32_t)first);store(p+8,(uint32_t)third);store(p+4,(uint32_t)second);
 LEAVE(16);ps2ModelInitializeSurfaceCallbacks(second);
}
void ps2ModelInitializeSurfaceCallbacks(uint64_t surface){store((uint32_t)surface+16,0x2c7f88);store((uint32_t)surface+20,0x2c8128);}

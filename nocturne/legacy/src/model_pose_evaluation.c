/* Original model pose, recursive world transforms and buffered light packet. */
#include "model_pose_evaluation.h"
#include "model_root_creation.h"
#include "model_motion_sampling.h"
#include "basic_pose.h"
#include "ee_vu_rotation.h"
#include "libc_stream.h"
#include <string.h>
#if defined(NOCTURNE_MODEL_RENDERER_PROFILE)
#include "model_renderer.h"
static void cpuQuad(unsigned r,const uint32_t v[4]){if(g_modelRendererActive)EE_RENDERER_CPU_QUAD(r,v);}
#else
#define cpuQuad(r,v) ((void)0)
#endif
#if defined(NOCTURNE_MODEL_CONTEXT_CHILD_PROFILE)
extern uint32_t g_modelContextChildActive;
static void childCpuQuad(unsigned r,const uint32_t v[4]){if(g_modelContextChildActive)EE_RENDERER_CPU_QUAD(r,v);}
#else
#define childCpuQuad(r,v) ((void)0)
#endif
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelPoseAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static void load(unsigned r,uint32_t a){uint32_t v[4];memcpy(v,at(a),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t a){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(a),v,16);}
static void mul(unsigned reg,const uint32_t factor[4],unsigned mask){uint32_t v[4];EE_ROT_VU_READ(reg,v);for(unsigned k=0;k<4;k++)if(mask&(8u>>k))v[k]=(uint32_t)EE_ROT_VU_MUL(v[k],factor[k]);EE_ROT_VU_WRITE(reg,v);}
void sdfModelMakeLocalTm(uint64_t node){uint32_t n=(uint32_t)node;load(10,n+80);sdfQuatToMatrix();load(31,n+96);for(unsigned k=0;k<4;k++)store(28+k,n+128+k*16);}
void ps2ModelNodeBaseSet(uint64_t node,uint64_t definition){uint32_t n=(uint32_t)node,d=(uint32_t)definition;w32(n+56,d);w32(n+24,r32(d+8));sdfQuatFromEuler(real(r32(d+16)),real(r32(d+20)),real(r32(d+24)));store(10,n+80);uint32_t v[4];memcpy(v,at(d+32),16);childCpuQuad(2,v);memcpy(at(n+96),v,16);memcpy(v,at(d+48),16);childCpuQuad(2,v);memcpy(at(n+112),v,16);w32(n+108,0x3f800000);sdfModelMakeLocalTm(node);w32(n+52,r32(d+64));}
uint64_t sdfModelMakeEarly(uint64_t textures,uint64_t definition){uint32_t d=(uint32_t)definition,r=(uint32_t)sdfModelMakeRoot(textures,definition);uint8_t *flag=at(r+25);*flag|=4;uint32_t list=r32(d),count=r32(list),record=list+16,i=0;if(count)do{uint32_t array=r32(r),node=r32(r32(array+12)+i*4u);i++;ps2ModelNodeBaseSet(sx(node),sx(record));record+=80;}while(i!=count);return sx(r);}
void ps2ModelComposeVuMatrices(void){uint32_t parent[4][4],row[4],out[4],acc[4],of[4];for(unsigned k=0;k<4;k++)EE_ROT_VU_READ(24+k,parent[k]);for(unsigned r=28;r<32;r++){EE_ROT_VU_READ(r,row);for(unsigned lane=0;lane<4;lane++){uint64_t v=EE_ROT_VU_MUL(parent[0][lane],row[0]);acc[lane]=(uint32_t)v;of[lane]=(uint32_t)(v>>32)&1;}EE_ROT_ACC_WRITE(acc,of);for(unsigned k=1;k<3;k++){for(unsigned lane=0;lane<4;lane++){uint64_t v=EE_ROT_VU_MAC(acc[lane],parent[k][lane],row[k],of[lane],0);acc[lane]=(uint32_t)v;of[lane]=(uint32_t)(v>>32)&1;}EE_ROT_ACC_WRITE(acc,of);}for(unsigned lane=0;lane<4;lane++)out[lane]=(uint32_t)EE_ROT_VU_MAC(acc[lane],parent[3][lane],row[3],of[lane],0);EE_ROT_VU_WRITE(r,out);}}
void ps2ModelWriteLightingPacket(uint64_t packet){uint32_t p=(uint32_t)packet,rows[3][4],acc[4],of[4],length[4],v0[4],normal[4],v[4];for(unsigned k=0;k<3;k++)EE_ROT_VU_READ(28+k,rows[k]);EE_ROT_ACC_READ(acc,of);for(unsigned lane=0;lane<3;lane++){uint64_t r=EE_ROT_VU_MUL(rows[0][lane],rows[0][lane]);acc[lane]=(uint32_t)r;of[lane]=(uint32_t)(r>>32)&1;}EE_ROT_ACC_WRITE(acc,of);for(unsigned lane=0;lane<3;lane++){uint64_t r=EE_ROT_VU_MAC(acc[lane],rows[1][lane],rows[1][lane],of[lane],0);acc[lane]=(uint32_t)r;of[lane]=(uint32_t)(r>>32)&1;}EE_ROT_ACC_WRITE(acc,of);EE_ROT_VU_READ(2,length);for(unsigned lane=0;lane<3;lane++)length[lane]=(uint32_t)EE_ROT_VU_MAC(acc[lane],rows[2][lane],rows[2][lane],of[lane],0);EE_ROT_VU_WRITE(2,length);cpuQuad(2,length);EE_ROT_VU_READ(0,v0);uint32_t q=EE_ROT_VU_RSQRT(v0[3],length[1]);EE_ROT_Q_WRITE(q);uint32_t x=EE_MODEL_CPU_RSQRT(0x3f800000,length[0]);for(unsigned k=0;k<4;k++)store(28+k,p+k*16);EE_ROT_VU_READ(3,normal);normal[1]=(uint32_t)EE_ROT_VU_ADD(v0[1],q);EE_ROT_VU_WRITE(3,normal);q=EE_ROT_VU_RSQRT(v0[3],length[2]);EE_ROT_Q_WRITE(q);v[0]=x;v[1]=x>>31?UINT32_MAX:0;v[2]=length[2];v[3]=length[3];EE_ROT_VU_WRITE(4,v);normal[0]=v[0];EE_ROT_VU_WRITE(3,normal);normal[2]=(uint32_t)EE_ROT_VU_ADD(v0[2],q);EE_ROT_VU_WRITE(3,normal);for(unsigned k=0;k<3;k++){EE_ROT_VU_READ(4+k,v);for(unsigned lane=0;lane<3;lane++)v[lane]=(uint32_t)EE_ROT_VU_MUL(rows[k][lane],normal[lane]);EE_ROT_VU_WRITE(4+k,v);store(4+k,p+64+k*16);}w32(p+116,0x14000000);w32(p+112,0x04000010);w32(p+124,0);w32(p+120,0);}
void sdfModelEvalNode(uint64_t node,uint64_t parentMatrix,uint64_t frame){uint32_t n=(uint32_t)node,m=(uint32_t)parentMatrix,s[4],factor[4];for(unsigned k=0;k<3;k++)load(28+k,n+128+k*16);load(10,n+112);EE_ROT_VU_READ(10,s);for(unsigned k=0;k<3;k++){for(unsigned lane=0;lane<4;lane++)factor[lane]=s[k];mul(28+k,factor,15);}load(31,n+96);for(unsigned k=0;k<4;k++)load(24+k,m+k*16);ps2ModelComposeVuMatrices();for(unsigned k=0;k<4;k++)store(28+k,n+192+k*16);uint32_t workspace=r32(n+48);if(workspace)ps2ModelWriteLightingPacket(sx(workspace+((uint32_t)frame<<7)));uint32_t child=r32(n+12);if(child)do{sdfModelEvalNode(sx(child),sx(n+192),frame);child=r32(child+4);}while(child!=r32(n+12));}
void sdfModelEvalTm2(uint64_t root,uint64_t frame){uint32_t r=(uint32_t)root,scale[4],matrix[16];for(unsigned k=0;k<4;k++)load(28+k,r+32+k*16);load(10,r+112);EE_ROT_VU_READ(10,scale);for(unsigned k=0;k<3;k++)mul(28+k,scale,14);for(unsigned k=0;k<4;k++)EE_ROT_VU_READ(28+k,matrix+k*4);uint32_t node=r32(r32(r32(r)+12));
#if UINTPTR_MAX > UINT32_MAX
 uint32_t address=nocturneLibcStreamLocalAddress(matrix,64);sdfModelEvalNode(sx(node),address,frame);nocturneLibcStreamEndLocal();
#else
 sdfModelEvalNode(sx(node),(uint32_t)(uintptr_t)matrix,frame);
#endif
}
void sdfModelEvalTm(uint64_t root){int8_t frame;memcpy(&frame,at(0x551842),1);sdfModelEvalTm2(root,(uint64_t)(int64_t)frame);}

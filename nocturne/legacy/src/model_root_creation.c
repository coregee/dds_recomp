/* Native root/node ownership, circular child rings and borrowed extra chunks. */
#include "model_root_creation.h"
#include "material_construction_release.h"
#include "array_lists.h"
#include "ee_vu_rotation.h"
#include <string.h>
#if defined(NOCTURNE_MODEL_CONTEXT_CHILD_PROFILE)
#include "model_renderer.h"
extern uint32_t g_modelContextChildActive;
static void identityCpu(const uint32_t v[4]){
 if(g_modelContextChildActive){
  uint32_t a0[4]={v[2],0,v[3],0},v0[4]={v[3],0,0,0},v1[4]={0,v[3],0,0};
  EE_RENDERER_CPU_QUAD(5,v);EE_RENDERER_CPU_QUAD(4,a0);
  EE_RENDERER_CPU_QUAD(2,v0);EE_RENDERER_CPU_QUAD(3,v1);
 }
}
#else
#define identityCpu(v) ((void)0)
#endif
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelRootCreationAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static int32_t s16(uint32_t a){int16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void vector(uint32_t a,const uint32_t v[4]){memcpy(at(a),v,16);}
static void identity(uint32_t a,const uint32_t v[4]){identityCpu(v);uint32_t m[16]={v[3],0,0,0,0,v[3],0,0,v[2],0,v[3],0,v[0],v[1],v[2],v[3]};for(unsigned k=0;k<16;k++)w32(a+k*4,m[k]);}
static void scale(uint32_t a,const uint32_t v[4]){uint32_t s[4];for(unsigned k=0;k<3;k++)s[k]=(uint32_t)EE_ROT_VU_ADD(v[k],v[3]);s[3]=(uint32_t)EE_ROT_VU_MUL(v[3],v[0]);EE_ROT_VU_WRITE(10,s);vector(a,s);}
uint64_t sdfModelNodeNew(void){uint32_t p=ps2PoolAllocateZeroed(256),v[4];w32(p+28,0x80808080);w16(p+22,UINT16_MAX);w32(p,p);w32(p+4,p);EE_ROT_VU_READ(0,v);vector(p+80,v);vector(p+96,v);scale(p+112,v);identity(p+128,v);return sx(p);}
uint64_t sdfModelRootNew(void){uint32_t p=ps2PoolAllocateZeroed(152),a=ps2ArrayCreate(0,4,32),v[4];w32(p,a);EE_ROT_VU_READ(0,v);identity(p+32,v);vector(p+96,v);scale(p+112,v);w16(p+26,UINT16_MAX);w32(p+28,0x80808080);return sx(p);}
void sdfModelAllocNodeList(uint64_t root,uint64_t capacity){ps2ArrayResize(r32((uint32_t)root),(int32_t)capacity);}
/* Unlink leaves the node's parent word intact, as in the original body. */
void sdfModelNodeUnlink(uint64_t node){uint32_t n=(uint32_t)node,parent=r32(n+8);if(parent){uint32_t previous=r32(n+4);if(sx(previous)!=node){uint32_t next=r32(n);w32(previous,next);w32(next+4,previous);if(sx(r32(parent+12))==node)w32(parent+12,previous);w32(n+4,n);w32(n,n);}else if(sx(r32(parent+12))==node)w32(parent+12,0);}else{uint32_t root=r32(n+16);if(sx(r32(root+4))==node)w32(root+4,0);}}
void sdfModelNodeSetParent(uint64_t node,uint64_t parent){uint32_t n=(uint32_t)node,p=(uint32_t)parent;if(!parent){uint32_t root=r32(n+16),head=r32(root+4);if(sx(head)==node)return;w32(root+4,n);if(head){w32(n+12,head);w32(head+8,n);}w32(n+8,0);return;}if(sx(r32(n+8))==parent)return;sdfModelNodeUnlink(node);uint32_t head=r32(p+12);if(!head)w32(p+12,n);else{uint32_t next=r32(head);w32(n,next);w32(next+4,n);w32(head,n);w32(n+4,head);}w32(n+8,p);}
void sdfModelNodeAdd(uint64_t root,uint64_t parent,uint64_t node){uint32_t r=(uint32_t)root,n=(uint32_t)node,a=r32(r);int32_t count=s16(a+4),next=count+1;if(s16(a+6)<next){ps2ArrayGrow(a);a=r32(r);}uint32_t data=r32(a+12);w32(n+16,r);w16(a+4,(uint16_t)next);w32(data+(uint32_t)count*4u,n);sdfModelNodeSetParent(node,parent);}
void ps2ModelMakeMorphList(uint64_t root,uint64_t count){if((int64_t)count<=0)return;uint32_t a=ps2ArrayCreate((int32_t)count,16,1);w32((uint32_t)root+16,a);uint32_t data=r32(a+12),i=0;do{for(unsigned k=0;k<4;k++)w32(data+i*16u+k*4u,0);i++;}while(sx(i)!=count);w16(a+4,(uint16_t)count);}
uint64_t sdfModelMakeRoot(uint64_t textures,uint64_t definition){uint32_t d=(uint32_t)definition,r=(uint32_t)sdfModelRootNew();w32(r+8,(uint32_t)textures);w32(r+12,ps2MatListMake((uint32_t)textures,r32(d+4)));uint32_t extra=r32(d+12);w32(r+144,extra);ps2ModelMakeMorphList(sx(r),sx(r32(d+8)));uint32_t list=r32(d),count=r32(list),record=list+16;sdfModelAllocNodeList(sx(r),sx(count));uint32_t i=0;if(count)do{uint64_t node=sdfModelNodeNew();uint32_t parent=r32(record+12);uint64_t parentNode=0;if(!(parent>>31)){uint32_t a=r32(r);parentNode=sx(r32(r32(a+12)+parent*4u));}sdfModelNodeAdd(sx(r),parentNode,node);i++;w32((uint32_t)node+24,r32(record+8));record+=80;}while(i!=count);return sx(r);}

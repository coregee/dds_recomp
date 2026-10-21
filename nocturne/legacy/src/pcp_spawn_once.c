/* Original two-part PCP construction/copy and mapped model-position paths. */
#include "pcp_spawn_once.h"
#include "pcp_construction.h"
#include "model_motion_creation.h"
#include "model_memory_parts.h"
#include "battle_effect_copy.h"
#include "material_fiveword_pool.h"
#include "resource_loader_flow.h"
#include "ee_vu_rotation.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolvePcpConstructionAddress(a);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t read32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t read16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void write32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t copyPart(uint32_t p){ENTER(32);uint64_t v=dds3EffectPartCopy(sx(p));LEAVE(32);return v;}
uint64_t ps2PcpSpawnOnceCreate(uint64_t descriptor){
 ENTER(32);uint32_t p=ps2PoolAllocate(28);
 write32(p+20,(uint32_t)ps2PcpDescriptorCreatePart(descriptor,0));
 uint32_t second=(uint32_t)ps2PcpDescriptorCreatePart(descriptor,1);
 write32(p,0);write32(p+24,second);write32(p+4,0);write32(p+16,0x80808080);write32(p+8,0);
 LEAVE(32);return sx(p);
}
uint64_t ps2PcpSpawnOnceCopy(uint64_t source){
 ENTER(32);uint32_t s=(uint32_t)source,p=ps2PoolAllocate(28);
 write32(p+20,(uint32_t)copyPart(read32(s+20)));uint32_t second=(uint32_t)copyPart(read32(s+24));
 write32(p,0);write32(p+24,second);write32(p+4,0);write32(p+16,0x80808080);write32(p+8,0);
 LEAVE(32);return sx(p);
}
void ps2ModelMapPositionRecordToVu(uint64_t root,uint64_t record){
 ENTER(16);uint32_t p=(uint32_t)record,node=(uint32_t)sdfModelSearchNode(root,sx(read32(p)));
 uint32_t rows[4][4],v[4],zero[4],acc[4],overflow[4],result[4];
 for(unsigned k=0;k<4;k++){memcpy(rows[k],at(node+192+k*16),16);EE_ROT_VU_WRITE(28+k,rows[k]);}
 memcpy(v,at(p+16),16);EE_ROT_VU_WRITE(10,v);EE_ROT_VU_READ(0,zero);
 for(unsigned lane=0;lane<4;lane++){uint64_t x=EE_ROT_VU_MUL(rows[0][lane],v[0]);acc[lane]=(uint32_t)x;overflow[lane]=(uint32_t)(x>>32)&1;}
 EE_ROT_ACC_WRITE(acc,overflow);
 for(unsigned k=1;k<3;k++){
  for(unsigned lane=0;lane<4;lane++){uint64_t x=EE_ROT_VU_MAC(acc[lane],rows[k][lane],v[k],overflow[lane],0);acc[lane]=(uint32_t)x;overflow[lane]=(uint32_t)(x>>32)&1;}
  EE_ROT_ACC_WRITE(acc,overflow);
 }
 for(unsigned lane=0;lane<4;lane++)result[lane]=(uint32_t)EE_ROT_VU_MAC(acc[lane],rows[3][lane],zero[3],overflow[lane],0);
 EE_ROT_VU_WRITE(10,result);LEAVE(16);
}
uint64_t ps2ModelMapPositionToVu(uint64_t root,uint64_t index){
 ENTER(16);uint64_t record=ps2ModelPositionFind(root,index);if(record)ps2ModelMapPositionRecordToVu(root,record);LEAVE(16);return record?1:0;
}
void ps2ModelPartSetPosition(uint64_t context,uint64_t vector){
 ENTER(16);uint32_t v[4];memcpy(v,at((uint32_t)vector),16);EE_ROT_VU_WRITE(10,v);LEAVE(16);
 ps2ModelSetPositionVu(context);
}
void ps2EffectPartSetPosition(uint64_t part,uint64_t vector){
 ENTER(16);uint32_t p=(uint32_t)part,target=read32(0x31de50+read16(p)*40);
 if(target){uint64_t object=sx(read32(p+4));
#if UINTPTR_MAX > UINT32_MAX
  nocturneSpawnOncePositionCall(target,object,vector);
#else
  ((void(*)(uint64_t,uint64_t))(uintptr_t)target)(object,vector);
#endif
 }LEAVE(16);
}

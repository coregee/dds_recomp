/* Original Magatuhi creation and copy dispatch. Native record geometry,
 * unsigned loops and delay modulus/RNG order are retained. */
#include "magatuhi_creation.h"
#include "model_track_creation.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "material_fiveword_pool.h"
#include "battle_effect_copy.h"
#include "ee_fpu.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveMagatuhiCreationAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t bits(float f){uint32_t v;memcpy(&v,&f,4);return v;}
static float real(uint32_t v){float f;memcpy(&f,&v,4);return f;}
/* Each native 32-byte block loads all four doublewords before its stores;
 * a final28-byte group likewise reads its three doublewords and word first. */
static void copy_parameters(uint32_t dst,uint32_t src,uint32_t size){
 while(size>=32){uint8_t block[32];memcpy(block,at(src),32);memcpy(at(dst),block,32);src+=32;dst+=32;size-=32;}
 if(size){uint8_t tail[28];memcpy(tail,at(src),size);memcpy(at(dst),tail,size);}
}
static void unit_matrix(uint32_t p){for(unsigned row=0;row<4;row++)for(unsigned column=0;column<4;column++)w32(p+(row*4+column)*4,row==column?0x3f800000u:0);}
static uint64_t factory(uint32_t target,uint64_t parameters){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneCallMagatuhiFactory(target,parameters);
#else
 return ((uint64_t(*)(uint64_t))(uintptr_t)target)(parameters);
#endif
}
static uint64_t effect_copy(uint32_t target,uint64_t object,uint64_t kind){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneCallGenericEffectCopy(target,object,kind);
#else
 return ((uint64_t(*)(uint64_t,uint64_t))(uintptr_t)target)(object,kind);
#endif
}
/* Reset one slot without changing its history position/colour arrays. */
void ps2MagatuhiResetValueSlot(uint64_t work,uint64_t index){
 uint32_t p=(uint32_t)work,k=(uint32_t)index,angles=r32(p+0x2c)+k*16u,valid=r32(p+0x28)+k*2u;
 uint32_t write=r32(p+0x24)+k*2u,color=r32(p+0x20)+k*4u;
 uint32_t first=r32(0x54c9f8),second=r32(0x54c9fc);w32(color,0x80808080);w16(write,0);w32(angles,first);w16(valid,0);w32(angles+8,second);w32(angles+12,0);w32(angles+4,0);
}
uint64_t ps2MagatuhiValueCreate(uint64_t count,uint64_t history,uint64_t mode,float scale,float t){
 uint32_t n=(uint32_t)count,h=(uint32_t)history,product=n*h;
 uint32_t size=(n*8u+(product*4u+n+product+h)*2u+n*2u)*2u+0x38;
 uint32_t handle=ps2MemoryHandleAllocate((int32_t)size),base=ps2MemoryHandleAcquirePointer(handle);
 uint32_t colors=base+product*16u,pad=colors+h*4u,slots=pad+product*4u,write=slots+n*4u,valid=write+n*2u,angles=valid+n*2u,p=angles+n*16u;
 w32(p+0x1c,pad);w16(p+4,(uint16_t)h);w32(p+12,bits(t));w32(p+8,bits(scale));w32(p+16,(uint32_t)mode);w32(p+0x14,base);w32(p+0x18,colors);w32(p+0x20,slots);w32(p+0x24,write);w32(p+0x28,valid);w32(p+0x2c,angles);w32(p+0x34,handle);w32(p,n);
 w32(p+0x30,(uint32_t)ps2BillboardTextureBase(0));
 for(uint32_t k=0;k<15;k++){uint32_t uv=0x56af30+k*16u;w16(uv,0);w16(uv+2,0);w16(uv+4,0x400);w16(uv+6,0);w16(uv+8,0x400);w16(uv+10,0x400);w16(uv+12,0);w16(uv+14,0x400);}
 if(count){uint32_t k=0;do{ps2MagatuhiResetValueSlot(sx(p),sx(k));k++;}while(sx(k)<count);}
 return sx(p);
}
void ps2MagatuhiFillColorTable(uint64_t work,uint64_t first,uint64_t second){
 uint32_t p=(uint32_t)work,count=r16(p+4),cursor=r32(p+0x18),amount=0,step=EE_FPU_DIV_S(0x3f800000,EE_FPU_CVT_S_W(count));
 for(uint32_t k=0;k<count;k++,cursor+=4){uint32_t previous=amount;amount=EE_FPU_ADD_S(amount,step);uint32_t value=(uint32_t)ps2EffectBlendColor(first,second,real(previous));w32(cursor,value);}
}
uint64_t ps2MagatuhiHistoryOwnerCreate(uint64_t parameters){
 uint32_t p=ps2PoolAllocate(32),s=(uint32_t)parameters;copy_parameters(p,s,28);
 uint64_t value=ps2MagatuhiValueCreate(sx(r32(p)),sx(r32(p+4)),sx(r32(p+0x14)),real(r32(p+8)),real(r32(p+0x18)));
 uint32_t first=r32(p+12);w32(p+0x1c,(uint32_t)value);ps2MagatuhiFillColorTable(value,sx(first),sx(r32(p+16)));return sx(p);
}
uint64_t ps2EffectMathSlotArrayCreate(uint64_t count){
 uint32_t n=(uint32_t)count,size=n*56u,handle=ps2MemoryHandleAllocate((int32_t)(size+12)),base=ps2MemoryHandleAcquirePointer(handle),p=base+size;
 w32(p+8,handle);w32(p,base);w32(p+4,n);
 if(count){uint32_t cursor=base,k=0,constant=r32(0x54ca40);do{w32(cursor+0x30,0);k++;w32(cursor+0x34,constant);cursor+=56;}while(sx(k)<count);}
 return sx(p);
}
/* The copied delay spread is signed-clamped before using unsigned DIVU.
 * One actual RNG advance per particle; no particle state is pre-zeroed. */
static void seed_delays(uint32_t particles,uint32_t count,uint32_t spread,uint32_t stride,uint32_t age){
 if(count){uint32_t k=0;do{uint32_t draw=sdfGetRand((uint32_t *)at(0x316fe0));k++;if(!spread)nocturne_break(7);w32(particles+age,0u-draw%spread);particles+=stride;}while(sx(k)<sx(count));}
}
uint64_t ps2MagatuhiSmokeConvCreate(uint64_t parameters){
 uint32_t s=(uint32_t)parameters,count=r32(s+0x60),bytes=count*48u,handle=ps2MemoryHandleAllocate((int32_t)(bytes+0x194)),base=ps2MemoryHandleAcquirePointer(handle),p=base+bytes;
 copy_parameters(p,s,0x17c);w32(p+0x190,handle);w32(p+0x17c,base);if((int32_t)r32(p+0x28)<=0)w32(p+0x28,1);
 w32(p+0x18c,(uint32_t)ps2MagatuhiHistoryOwnerCreate(sx(p+0x60)));w32(p+0x180,(uint32_t)ps2EffectMathSlotArrayCreate(sx(count)));uint32_t spread=r32(p+0x28);seed_delays(base,count,spread,48,32);return sx(p);
}
uint64_t ps2MagatuhiPoint4Create(uint64_t parameters){
 uint32_t s=(uint32_t)parameters,count=r32(s+0x64),handle=ps2MemoryHandleAllocate((int32_t)(count*4u+0x190)),p=ps2MemoryHandleAcquirePointer(handle),particles=p+0x190;
 copy_parameters(p,s,0x180);w32(p+0x18c,handle);w32(p+0x180,particles);if((int32_t)r32(p+0x48)<=0)w32(p+0x48,1);
 w32(p+0x188,(uint32_t)ps2MagatuhiHistoryOwnerCreate(sx(p+0x64)));w32(p+0x184,(uint32_t)ps2EffectMathSlotArrayCreate(sx(count)));seed_delays(particles,count,r32(p+0x48),4,0);return sx(p);
}
uint64_t ps2MagatuhiCylinderCreate(uint64_t parameters){
 uint32_t s=(uint32_t)parameters,count=r32(s+0x40),handle=ps2MemoryHandleAllocate((int32_t)(count*24u+0x12c)),p=ps2MemoryHandleAcquirePointer(handle),particles=p+0x12c;
 copy_parameters(p+0x40,s,0xdc);w32(p+0x128,handle);w32(p+0x124,0x80808080);w32(p+0x11c,particles);unit_matrix(p);if((int32_t)r32(p+0x58)<=0)w32(p+0x58,1);
 w32(p+0x120,(uint32_t)ps2MagatuhiHistoryOwnerCreate(sx(p+0x80)));seed_delays(particles,count,r32(p+0x58),24,0);return sx(p);
}
uint64_t ps2MagatuhiSpiralCreate(uint64_t parameters){
 uint32_t s=(uint32_t)parameters,count=r32(s+0x44),handle=ps2MemoryHandleAllocate((int32_t)(count*28u+0x130)),p=ps2MemoryHandleAcquirePointer(handle),particles=p+0x130;
 copy_parameters(p+0x40,s,0xe0);w32(p+0x12c,handle);w32(p+0x120,particles);w32(p+0x128,0x80808080);unit_matrix(p);if((int32_t)r32(p+0x58)<=0)w32(p+0x58,1);
 w32(p+0x124,(uint32_t)ps2MagatuhiHistoryOwnerCreate(sx(p+0x84)));seed_delays(particles,count,r32(p+0x58),28,0);return sx(p);
}
uint64_t ps2MagatuhiSmokeCreate(uint64_t parameters){
 uint32_t s=(uint32_t)parameters,count=r32(s+0x40),bytes=count*48u,handle=ps2MemoryHandleAllocate((int32_t)(bytes+0x12c)),base=ps2MemoryHandleAcquirePointer(handle),p=base+bytes;
 copy_parameters(p+0x40,s,0xdc);w32(p+0x128,handle);w32(p+0x120,0x80808080);w32(p+0x11c,base);unit_matrix(p);if((int32_t)r32(p+0x58)<=0)w32(p+0x58,1);
 w32(p+0x124,(uint32_t)ps2MagatuhiHistoryOwnerCreate(sx(p+0x80)));seed_delays(base,count,r32(p+0x58),48,32);return sx(p);
}
uint64_t dds3MagatuhiParCreate(uint64_t kind,uint64_t parameters){uint32_t p=ps2PoolAllocate(8),target=r32(0x320040+(uint32_t)kind*24u);uint64_t child=factory(target,parameters);w32(p,(uint32_t)kind);w32(p+4,(uint32_t)child);return sx(p);}
uint64_t dds3MagatuhiParCopy(uint64_t work){uint32_t p=(uint32_t)work;uint64_t kind=sx(r32(p)),parameters=0;if(kind<5){if(kind<2)parameters=sx(r32(p+4));else parameters=sx(r32(p+4)+0x40u);}return dds3MagatuhiParCreate(kind,parameters);}
/* Table and unchecked kind selection remain original. Host tests execute
 * actual recovered kinds3/4; other constructor families remain a frontier. */
uint64_t dds3EffectCopy(uint64_t work){uint32_t s=(uint32_t)work,p=ps2PoolAllocate(16),kind=r32(s);uint64_t child=sx(r32(s+8));w32(p,kind);w32(p+4,r32(s+4));uint64_t index=sx(r32(s));uint32_t target=r32(0x316f18+(uint32_t)index*48u);uint64_t result=effect_copy(target,child,index);w32(p+8,(uint32_t)result);return sx(p);}
uint64_t mdlEffectDupGeneric(uint64_t resource){uint32_t r=(uint32_t)resource;uint64_t child=dds3EffectCopy(sx(r32(r+8)));w32(r+4,r32(r+4)+1u);return child;}

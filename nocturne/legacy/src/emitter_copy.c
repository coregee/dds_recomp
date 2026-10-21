/* Original thirteen emitter copies, age resets and real camera-facing spawn. */
#include "emitter_copy.h"
#include "emitter_initialization.h"
#include "billboard_copy.h"
#include "camera_view.h"
#include "model_motion_sampling.h"
#include "battle_panel_support.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "material_fiveword_pool.h"
#include "ee_fpu.h"
#include "ee_vu_rotation.h"
#include "script_compare.h"
#include "nocturne.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveEmitterCopyAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void store(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void shalf(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint32_t bits(float v){uint32_t r;memcpy(&r,&v,4);return r;}
static float real(uint32_t v){float r;memcpy(&r,&v,4);return r;}
static uint32_t unsignedFloat(uint32_t v){if(v>>31){uint32_t r=EE_FPU_CVT_S_W((v>>1)|(v&1));return EE_FPU_ADD_S(r,r);}return EE_FPU_CVT_S_W(v);}
static void transformDirection(uint32_t vector[4]){uint32_t rows[3][4],acc[4],of[4],out[4];EE_ROT_VU_WRITE(10,vector);for(unsigned row=0;row<3;row++)EE_ROT_VU_READ(28+row,rows[row]);for(unsigned lane=0;lane<4;lane++){uint64_t a=EE_ROT_VU_MUL(rows[0][lane],vector[0]);acc[lane]=(uint32_t)a;of[lane]=(uint32_t)(a>>32);}EE_ROT_ACC_WRITE(acc,of);for(unsigned lane=0;lane<4;lane++){uint64_t a=EE_ROT_VU_MAC(acc[lane],rows[1][lane],vector[1],of[lane],0);acc[lane]=(uint32_t)a;of[lane]=(uint32_t)(a>>32);}EE_ROT_ACC_WRITE(acc,of);for(unsigned lane=0;lane<4;lane++)out[lane]=(uint32_t)EE_ROT_VU_MAC(acc[lane],rows[2][lane],vector[2],of[lane],0);EE_ROT_VU_WRITE(10,out);memcpy(vector,out,16);}
void ps2ParticleRadiateInitializeSlot(uint64_t work,uint64_t index){
 uint32_t w=(uint32_t)work,p=word(word(w+248)+4)+((uint32_t)index<<6);
 sdfVu0LookAtMatrix(0x2f5a50,0x2f5a60,0x2f5a70);ps2RigidInverseMatrix();
 /* S1 remains zero on this original branch, including across both real
  * camera callees. Its unsigned DIVU therefore leads to actual BREAK7. */
 if(*at(w+336))nocturne_break(7);
 uint8_t origin[16];memcpy(origin,at(w),16);memcpy(at(p),origin,16);uint32_t period=word(w+348);if(!period)nocturne_break(7);
 uint32_t phase=EE_FPU_MUL_S(EE_FPU_DIV_S(word(0x54c5d0),unsignedFloat(period)),unsignedFloat((uint32_t)index%period));
 store(p+16,sdfCosBits(phase));store(p+20,sdfSinBits(phase));store(p+24,0);uint32_t direction[4];memcpy(direction,at(p+16),16);transformDirection(direction);memcpy(at(p+16),direction,16);store(p+52,phase);store(p+32,0);store(p+36,0);
 uint32_t jitter=word(w+148),random=bits(sdfGetRandFloat((uint32_t *)at(0x316fe0))),inverse=EE_FPU_SUB_S(0x3f800000,jitter),scale=EE_FPU_MUL_S(random,jitter);scale=EE_FPU_ADD_S(scale,inverse);store(p+40,EE_FPU_MUL_S(word(w+16),scale));jitter=word(w+152);
 if(EE_FPU_COMPARE_S(jitter,0,0))store(p+44,0);else{random=bits(sdfGetRandFloat((uint32_t *)at(0x316fe0)));inverse=EE_FPU_SUB_S(0x3f800000,jitter);scale=EE_FPU_ADD_S(EE_FPU_MUL_S(random,jitter),inverse);store(p+44,EE_FPU_MUL_S(scale,word(0x54c5dc)));}
 ps2ParticleKindReset(sx(w+48),index);
}
static void ages(uint64_t work,unsigned groupOffset,unsigned angle,unsigned radiate){uint32_t w=(uint32_t)work,p=word(word(w+248)+4),i=0,age=radiate?0:0xf0000001;if(!word(w+32))return;do{
 if(radiate)ps2ParticleRadiateInitializeSlot(work,sx(i));store(p+32,age);if(angle)store(p+52,word(w+344));p+=64;i++;
 if(groupOffset){uint32_t divisor=word(w+groupOffset),remainder=divisor?i%divisor:i;if(!divisor)nocturne_break(7);if(!remainder)age-=word(w+340);}
 }while(i<word(w+32));}
void ps2ParticleKind0Reset(uint64_t w){ages(w,348,0,0);}
void ps2ParticleKind1Reset(uint64_t w){ages(w,0,0,0);}
void ps2ParticleKind2Reset(uint64_t w){ages(w,0,0,0);}
void ps2ParticleKind3Reset(uint64_t w){ages(w,348,0,1);}
void ps2ParticleKind4Reset(uint64_t w){ages(w,0,0,0);}
void ps2ParticleKind5Reset(uint64_t w){ages(w,0,0,0);}
void ps2ParticleKind6Reset(uint64_t w){ages(w,352,0,0);}
void ps2ParticleKind7Reset(uint64_t w){ages(w,0,0,0);}
void ps2ParticleKind8Reset(uint64_t w){ages(w,0,1,0);}
void ps2ParticleKind10Reset(uint64_t w){ages(w,0,0,0);}
void ps2ParticleKind11Reset(uint64_t w){ages(w,0,0,0);}
void ps2ParticleKind12Reset(uint64_t w){ages(w,0,0,0);}
static uint32_t copyHead(uint64_t source,uint32_t size,uint32_t tail){uint32_t s=(uint32_t)source,p=ps2PoolAllocate((int32_t)size);ps2Memset(at(p),0,size);ps2Memcpy(at(p),at(s),word(s+160));ps2Memcpy(at(p+336),at(s+word(s+160)),tail);return p;}
static void initialize(uint32_t p,unsigned extra){
#if UINTPTR_MAX > UINT32_MAX
 nocturneEmitterCopyFrame(p,word(p+32),extra);nocturneEmitterCopyObjectInput(sx(p));
#endif
 ps2ParticleBasicInitialize(sx(p));}
#define COPY_STANDARD(k,size,tail) uint64_t ps2ParticleKind##k##Copy(uint64_t source){uint32_t p=copyHead(source,size,tail);initialize(p,0);ps2ParticleKind##k##Reset(sx(p));return sx(p);}
COPY_STANDARD(0,384,48) COPY_STANDARD(1,384,48) COPY_STANDARD(2,384,48)
COPY_STANDARD(3,368,32) COPY_STANDARD(4,368,32) COPY_STANDARD(5,384,48)
COPY_STANDARD(6,368,32) COPY_STANDARD(7,384,48) COPY_STANDARD(8,368,32)
COPY_STANDARD(10,400,64)
#undef COPY_STANDARD
uint64_t ps2ParticleKind9Copy(uint64_t source){uint32_t p=copyHead(source,336,0);store(p+32,1);store(p+36,0);initialize(p,0);return sx(p);}
uint64_t ps2ParticleKind11Copy(uint64_t source){uint32_t p=copyHead(source,512,176),count=word(p+32),h=ps2MemoryHandleAllocate((int32_t)(count<<4));store(p+380,h);store(p+376,ps2MemoryHandleAcquirePointer(h));initialize(p,1);ps2ParticleKind11Reset(sx(p));return sx(p);}
uint64_t ps2ParticleKind12Copy(uint64_t source){uint32_t p=copyHead(source,400,64);initialize(p,0);uint16_t kind=half(p+48);if(kind){uint32_t n=word(p+32),width=(kind>=1&&kind<=4)?half(p+52):0,bytes=n*12+width*n*16;store(p+368,width);uint32_t h=ps2MemoryHandleAllocate((int32_t)bytes),base=ps2MemoryHandleAcquirePointer(h);store(p+372,h);store(p+364,base);uint32_t vectors=base+n*12;for(int32_t i=0;i<(int32_t)n;i++){store(base+8,vectors);store(base,0);store(base+4,0);base+=12;vectors+=width*16;}}else store(p+372,0);ps2ParticleKind12Reset(sx(p));return sx(p);}
static uint64_t copyDispatch(uint64_t source){uint32_t s=(uint32_t)source,index=half(s+320),target=word(0x317270+index*12);uint64_t p;
#if UINTPTR_MAX > UINT32_MAX
 p=nocturneCallEmitterCopy(target,source);
#else
 p=((uint64_t (*)(uint64_t))(uintptr_t)target)(source);
#endif
 shalf((uint32_t)p+320,half(s+320));return p;}
uint64_t dds3ParticleCopy(uint64_t source){return copyDispatch(source);}
uint64_t dds3ParticleExpCopy(uint64_t source){uint32_t s=(uint32_t)source,p=(uint32_t)copyDispatch(source);if(sx(word(s+40))==UINT64_MAX){uint64_t billboard=dds3BillboardCopy(sx(word(s+244)));dds3BillboardSetScale(billboard,real(word(p+16)),real(word(p+20)));dds3BillboardSetMode(billboard,(uint64_t)(int64_t)(int16_t)half(p+44));dds3BillboardSetAnimColorAdvMode(billboard);store(p+244,(uint32_t)billboard);}return sx(p);}

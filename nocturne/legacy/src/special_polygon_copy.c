/* Original four special polygon constructors, reset widths and copy table. */
#include "special_polygon_copy.h"
#include "polygon_prerequisites.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "material_fiveword_pool.h"
#include "nocturne.h"
#include "ps2_memory.h"
#include "ee_vu_rotation.h"
#include <string.h>
_Noreturn void nocturne_break(uint32_t code);
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveSpecialPolygonCopyAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
void ps2SpecialPolygonOldRingReset(uint64_t work){uint32_t w=(uint32_t)work,n=half(w+16),age=0xff000001,ages=word(w+224),system=word(w+220);if(!n)return;uint32_t cells=word(system+20);for(uint32_t i=0;i<n;i++){uint32_t p=cells+i*20;put(p+16,0x00808080);put(p+12,0);put(p+8,0);put(ages+i*4,age);age-=word(w+196);}}
static void reset(uint64_t work,unsigned records,unsigned stride,unsigned groups){uint32_t w=(uint32_t)work,n=word(w+16),age=0xff000001,step=word(w+192),p=word(w+records),i=0;if(!n)return;do{put(p,age);p+=stride;i++;if(groups){uint32_t modulus=word(w+220);if(!modulus)nocturne_break(7);if(!(i%modulus))age-=step;}else age-=step;}while(i<n);}
void ps2SpecialPolygonRingReset(uint64_t work){reset(work,244,8,0);}
void ps2SpecialPolygonRollRingReset(uint64_t work){reset(work,228,8,0);}
void ps2SpecialPolygonSphereRingReset(uint64_t work){reset(work,248,20,1);}
uint64_t ps2SpecialPolygonOldRingCopy(uint64_t source){uint32_t s=(uint32_t)source,p=ps2PoolAllocate((int32_t)((word(s+16)<<2)+240));ps2Memset(at(p),0,240);ps2Memcpy(at(p),at(s),word(s+24));ps2Memcpy(at(p+192),at(s+word(s+24)),48);put(p+24,192);put(p+224,p+240);if(half(p+200)<3)sh(p+200,3);uint64_t system=ps2PolygonVertexCreate(sx(word(p+16)),half(p+200),1,0);put(p+220,(uint32_t)system);ps2PolygonVertexColors(system,0,sx(word(p+212)),sx(word(p+216)));ps2SpecialPolygonOldRingReset(sx(p));return sx(p);}
static uint64_t create(uint64_t source,unsigned family){uint32_t s=(uint32_t)source,n=word(s+16),baseSize=family==2?240:256,stride=family==3?20:8,bytes=baseSize+n*stride,h=ps2MemoryHandleAllocate((int32_t)bytes),p=ps2MemoryHandleAcquirePointer(h);ps2Memset(at(p),0,bytes);ps2Memcpy(at(p),at(s),word(s+24));ps2Memcpy(at(p+192),at(s+word(s+24)),baseSize-192);put(p+24,192);unsigned systemOffset=family==1?240:family==2?224:244,recordOffset=family==1?244:family==2?228:248;put(p+recordOffset,p+baseSize);put(p+recordOffset+4,h);if(word(p+196)<3)put(p+196,3);uint64_t system=ps2PolygonVertexCreate(sx(word(p+16)),sx(word(p+196)),1,0);put(p+systemOffset,(uint32_t)system);unsigned first=family==1?236:family==2?220:240,second=family==1?228:family==2?212:232;ps2PolygonVertexColors(system,0,sx(word(p+first)),sx(word(p+second)));if(family==1)ps2SpecialPolygonRingReset(sx(p));else if(family==2)ps2SpecialPolygonRollRingReset(sx(p));else ps2SpecialPolygonSphereRingReset(sx(p));for(unsigned row=0;row<4;row++){uint32_t v[4];memcpy(v,at(p+32+row*16),16);EE_ROT_VU_WRITE(28+row,v);memcpy(at(p+112+row*16),v,16);}ps2PolygonVertexSetMode(system,half(p+102));return sx(p);}
uint64_t ps2SpecialPolygonRingCopy(uint64_t source){return create(source,1);}
uint64_t ps2SpecialPolygonRollRingCopy(uint64_t source){return create(source,2);}
uint64_t ps2SpecialPolygonSphereRingCopy(uint64_t source){return create(source,3);}
uint64_t dds3SpPolyCopy(uint64_t source){uint32_t s=(uint32_t)source,target=word(0x317670+half(s+176)*12);uint64_t p;
#if UINTPTR_MAX > UINT32_MAX
 p=nocturneCallSpecialPolygonCopy(target,source);
#else
 p=((uint64_t (*)(uint64_t))(uintptr_t)target)(source);
#endif
 sh((uint32_t)p+178,1);sh((uint32_t)p+176,half(s+176));return p;}

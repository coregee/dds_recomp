/* World-owned indexed object arrays and native object control allocation. */
#include "world_arrays.h"
#include "path_control.h"
#include "script_construction.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint32_t half(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static int32_t sh(uint32_t p){uint32_t v=half(p);return (int32_t)(v&32767)-(int32_t)(v&32768);}
static void putHalf(uint32_t p,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(p),&h,2);}
static uint64_t sx(uint32_t p){return p&0x80000000u?UINT64_C(0xffffffff00000000)|p:p;}
static int signedLess(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint32_t data(void){return word(word(0x54e9c4)+24);}
static uint32_t node(uint32_t base,int32_t index){return base+(uint32_t)index*8;}
/* 0010EA90: move a prefix of world free slots to the handle; zero count
 * succeeds before any pointer access, including absent world/handle. */
uint64_t dds3AddBasicArray(uint64_t handle,uint64_t count)
{
 if(!count)return 1;if(!word(0x54e9c4))return 0;
 uint32_t d=data();if(signedLess(half(d+30),count)||(count>>63)||!handle)return 0;
 uint32_t h=(uint32_t)handle,b=word(d+20);int32_t first=sh(d+26),last=first;
 for(uint32_t i=0;i<(uint32_t)count-1;i++){last=(int32_t)half(node(b,last)+4);putHalf(d+26,(uint32_t)last);last=(int32_t)((last&32767)-(last&32768));}
 uint32_t p=node(b,last),next=half(p+4);putHalf(d+26,next);
 if(next==65535)putHalf(d+28,65535);
 else{putHalf(p+4,65535);putHalf(node(b,sh(d+26))+6,65535);}
 putHalf(d+30,half(d+30)-(uint32_t)count);
 int32_t tail=sh(h+2);
 if(tail<0){putHalf(h+2,(uint32_t)last);putHalf(h,(uint32_t)first);}
 else{putHalf(node(b,tail)+4,(uint32_t)first);putHalf(node(b,first)+6,half(h+2));putHalf(h+2,(uint32_t)last);}
 uint32_t oldCount=half(h+6);putHalf(h+4,(uint32_t)first);putHalf(h+6,oldCount+(uint32_t)count);return 1;
}
uint64_t dds3GetBasicArrayHandle(uint64_t count)
{
 if(!word(0x54e9c4))return 0;uint32_t d=data();if(signedLess(half(d+30),count))return 0;
 uint32_t h=ps2PoolAllocate(16);if(!h)return 0;
 put(h+12,0);put(h+8,0);putHalf(h+4,65535);uint32_t tail=word(d+36);
 putHalf(h,65535);putHalf(h+2,65535);putHalf(h+6,0);
 if(!tail){put(d+36,h);put(d+32,h);}else{put(tail+8,h);put(h+12,word(d+36));put(d+36,h);}
 (void)dds3AddBasicArray(sx(h),count);return sx(h);
}
void dds3DeleteBasicArray(uint64_t handle)
{
 if(!handle)return;uint32_t h=(uint32_t)handle;if(!half(h+6)||sh(h+4)<0||!word(0x54e9c4))return;
 uint32_t d=data(),b=word(d+20),p=node(b,sh(h+4));int32_t previous=sh(p+6);put(p,0);int32_t next=sh(p+4);
 if(previous<0)putHalf(h,(uint32_t)next);else putHalf(node(b,previous)+4,(uint32_t)next);
 if(next<0)putHalf(h+2,(uint32_t)previous);else putHalf(node(b,next)+6,(uint32_t)previous);
 putHalf(node(b,sh(h+4))+6,65535);putHalf(node(b,sh(h+4))+4,65535);
 int32_t freeTail=sh(d+28);
 if(freeTail<0)putHalf(d+26,half(h+4));
 else{putHalf(node(b,freeTail)+4,half(h+4));putHalf(node(b,sh(h+4))+6,half(d+28));}
 putHalf(d+28,half(h+4));putHalf(d+30,half(d+30)+1);putHalf(h+4,(uint32_t)next);putHalf(h+6,half(h+6)-1);
}
void dds3DeleteAllBasicArray(uint64_t handle)
{
 if(!handle)return;uint32_t h=(uint32_t)handle;if(!half(h+6)||!word(0x54e9c4))return;
 uint32_t d=data();int32_t index=sh(h);uint32_t first=half(h);
 if(index>=0){uint32_t b=word(d+20);do{uint32_t p=node(b,index);index=sh(p+4);put(p,0);}while(index>=0);}
 int32_t freeTail=sh(d+28);
 if(freeTail<0)putHalf(d+26,first);
 else{uint32_t b=word(d+20);putHalf(node(b,freeTail)+4,first);putHalf(node(b,sh(h))+6,half(d+28));}
 putHalf(d+28,half(h+2));putHalf(d+30,half(d+30)+half(h+6));putHalf(h+4,65535);putHalf(h+6,0);putHalf(h,65535);putHalf(h+2,65535);
}
void dds3FreeBasicArrayHandle(uint64_t handle)
{
 if(!handle||!word(0x54e9c4))return;uint32_t d=data(),h=(uint32_t)handle;dds3DeleteAllBasicArray(handle);
 uint32_t previous=word(h+12);if(!previous)put(d+32,word(h+8));else put(previous+8,word(h+8));
 uint32_t next=word(h+8),prev=word(h+12);if(!next)put(d+36,prev);else put(next+12,prev);ps2PoolRelease(h);
}
uint64_t dds3GetBasicArrayCount(uint64_t h){return h?half((uint32_t)h+6):0;}
uint64_t dds3SetBasicArray(uint64_t handle,uint64_t basic)
{
 uint32_t h=(uint32_t)handle;if(!half(h+6)||sh(h+4)<0)return 0;put(node(word(data()+20),sh(h+4)),(uint32_t)basic);return 1;
}
uint64_t dds3GetBasicArray(uint64_t handle)
{uint32_t h=(uint32_t)handle;if(!half(h+6)||sh(h+4)<0)return 0;return sx(word(node(word(data()+20),sh(h+4))));}
uint64_t dds3SetFirstBasicArray(uint64_t handle){uint32_t h=(uint32_t)handle,v=half(h);putHalf(h+4,v);return !(v&32768);}
uint64_t dds3SetNextBasicArray(uint64_t handle)
{
 uint32_t h=(uint32_t)handle;int32_t current=sh(h+4);if(current<0)return 0;
 uint32_t next=half(node(word(data()+20),current)+4);putHalf(h+4,next);return !(next&32768);
}
uint64_t dds3SetSearchNextBasicArray(uint64_t h,uint64_t basic)
{for(;;){uint64_t p=dds3GetBasicArray(h);if(!p)return 0;if(p==basic)return 1;if(!dds3SetNextBasicArray(h))return 0;}}
uint64_t dds3SearchDeleteBasicArray(uint64_t h,uint64_t basic,uint64_t mode)
{
 uint64_t found=0;if(!dds3GetBasicArrayCount(h))return 0;(void)dds3SetFirstBasicArray(h);
 while(dds3SetSearchNextBasicArray(h,basic)==1){dds3DeleteBasicArray(h);found=1;if(!mode)break;}return found;
}
uint64_t dds3ObjectBaseInitControlWorkData(uint64_t basic)
{
 uint32_t c=ps2PoolAllocate(172);ps2Memset(at(c),0,172);put(c+8,3);
 uint64_t h=dds3GetBasicArrayHandle(0);put(c+16,(uint32_t)basic);put(c+4,(uint32_t)h);
 for(uint32_t i=0;i<24;i++)put(c+168-i*4,0xffffffffu);return sx(c);
}
void dds3ObjectBaseOnFlag(uint64_t b,uint64_t f){uint32_t c=(uint32_t)dds3GetBaseControlWorkData(b);put(c,word(c)|(uint32_t)f);}
void dds3ObjectBaseOffFlag(uint64_t b,uint64_t f){uint32_t c=(uint32_t)dds3GetBaseControlWorkData(b);put(c,word(c)&~(uint32_t)f);}
uint64_t dds3ObjectBaseCheckFlag(uint64_t b,uint64_t f){uint32_t c=(uint32_t)dds3GetBaseControlWorkData(b);return (sx(word(c))&f)!=0;}
uint64_t dds3ObjectBaseBasicTypeToItemType(uint64_t type)
{
 /* ADDIU truncates/sign-extends before the range guard. */
 uint64_t index=sx((uint32_t)type-2);if(index>=12)return 0;
 switch((uint32_t)index){case 0:return 5;case 1:return 1;case 8:case 10:case 11:return 3;case 9:return 4;default:return 0;}
}
uint64_t dds3ObjectBaseSetControlBasicType(uint64_t b,uint64_t control,uint64_t type)
{
 uint64_t old=dds3ObjectBaseGetControlBasic(b,type);uint32_t c=(uint32_t)dds3GetBaseControlWorkData(b);put(c+16+(uint32_t)type*4,(uint32_t)control);return old;
}
uint64_t dds3ObjectBaseSetControlBasic(uint64_t b,uint64_t control)
{return control?dds3ObjectBaseSetControlBasicType(b,control,dds3ObjectBaseBasicTypeToItemType(*at((uint32_t)control+15))):0;}
uint64_t ps2ObjectBaseGetControlBasicSvs(uint64_t b){return sx(word((uint32_t)dds3GetBaseControlWorkData(b)+48));}
void dds3ObjectBaseSetControlBasicSvs(uint64_t b,uint64_t svs){uint32_t c=(uint32_t)dds3GetBaseControlWorkData(b);(void)ps2ObjectBaseGetControlBasicSvs(b);put(c+48,(uint32_t)svs);}
void dds3MoverBasicFreePath(uint64_t mover){uint32_t d=word((uint32_t)mover+24),p=word(d+4);if(p){dds3PathBasicFreeControl(sx(p));put(d+4,0);}}
uint64_t dds3MoverBasicConstructor(uint64_t basic){uint32_t p=ps2PoolAllocate(16);put((uint32_t)basic+24,p);ps2Memset(at(p),0,16);return 1;}

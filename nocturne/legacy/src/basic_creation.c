/* Original basic allocation, scene lists and connected camera/mover creation. */
#include "basic_creation.h"
#include "world_arrays.h"
#include "basic_pose.h"
#include "path_control.h"
#include "scene_lookup.h"
#include "script_construction.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include <string.h>
static uint8_t *at(uint32_t p){return nocturneResolveScriptConstructionAddress(p);}
static uint32_t word(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void put(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static void half(uint32_t p,uint16_t v){memcpy(at(p),&v,2);}
static uint64_t sx(uint32_t p){return p&0x80000000u?UINT64_C(0xffffffff00000000)|p:p;}
uint64_t dds3AddBasic(uint64_t type)
{
 if(type>=18)return 0;uint32_t b=ps2PoolAllocate(68);if(!b)return 0;
 uint32_t record=word(0x2fa5c8+(uint32_t)type*4);
 put(b+12,(uint32_t)type<<24);put(b+52,0x80808080);put(b,0);put(b+4,0);put(b+8,0);put(b+16,record);
 for(uint32_t i=20;i<=48;i+=4)put(b+i,0);
 if(record){uint32_t init=word(record);if(init&&nocturneCallBasicInitializer(init,sx(b))!=1){dds3DeleteBasic(sx(b));return 0;}}
 return sx(b);
}
void dds3DeleteBasic(uint64_t basic)
{
 if(!basic)return;uint32_t b=(uint32_t)basic,record=word(b+16);
 if(record){uint32_t release=word(record+4);if(release)nocturneCallBasicDestructor(release,basic);}
 uint32_t previous=word(b+36);if(previous)put(previous+32,word(b+32));
 uint32_t next=word(b+32);if(next)put(next+36,word(b+36));ps2PoolRelease(b);
}
uint64_t ps2WorldBasicConstructor(uint64_t basic)
{
 uint32_t d=ps2PoolAllocate(40);if(!d)return 0;put((uint32_t)basic+24,d);
 half(d+28,65535);for(uint32_t i=0;i<=20;i+=4)put(d+i,0);
 half(d+24,0);half(d+26,65535);half(d+30,0);put(d+32,0);put(d+36,0);return 1;
}
void dds3DeleteScene(uint64_t scene)
{
 if(!scene)return;uint32_t world=word(0x54e9c4);if(!world)return;uint32_t d=word(world+24),s=(uint32_t)scene;
 if(sx(word(d))==scene)put(d,word(s+32));if(sx(word(d+4))==scene)put(d+4,word(s+36));
 if(sx(word(d+8))==scene)put(d+8,0);if(sx(word(d+12))==scene)put(d+12,0);dds3DeleteBasic(scene);
}
void ps2WorldBasicDestructor(uint64_t basic)
{
 uint32_t d=word((uint32_t)basic+24);if(!d)return;
 while(word(d))dds3DeleteScene(sx(word(d)));
 while(word(d+32))dds3FreeBasicArrayHandle(sx(word(d+32)));
 uint32_t h=word(d+16);if(h)ps2MemoryHandleFree(h);ps2PoolRelease(d);
}
uint64_t dds3AddSceneBasicData(uint64_t type)
{
 if(sx((uint32_t)type-2)>=16)return 0;uint64_t scene=dds3GetControlScene();if(!scene)return 0;
 uint32_t list=word(word((uint32_t)scene+24)+8)+(uint32_t)type*12;
 uint64_t result=dds3AddBasic(type);if(!result)return 0;uint32_t b=(uint32_t)result;put(b+48,(uint32_t)scene);
 uint32_t tail=word(list+8);if(tail){put(tail+32,b);put(b+36,word(list+8));}else put(list+4,b);
 put(list+8,b);put(list,word(list)+1);return result;
}
void dds3DeleteSceneBasicData(uint64_t basic)
{
 if(!basic)return;uint32_t b=(uint32_t)basic,type=*at(b+15);if(type-2>=16)return;
 uint32_t list=word(word(word(b+48)+24)+8)+type*12;
 if(sx(word(list+4))==basic)put(list+4,word(b+32));
 if(sx(word(list+8))==basic)put(list+8,word(b+36));dds3DeleteBasic(basic);put(list,word(list)-1);
}
void dds3MoverBasicDestructor(uint64_t basic)
{
 uint32_t d=word((uint32_t)basic+24);dds3MoverBasicFreePath(basic);
 (void)dds3ObjectBaseSetControlBasicType(sx(word(d)),0,1);ps2PoolRelease(d);
}
uint64_t dds3AddMoverBasic(uint64_t object)
{
 uint64_t mover=dds3AddSceneBasicData(3);uint32_t b=(uint32_t)mover,d=word(b+24);
 uint64_t id=dds3SerializeID();uint32_t index=word(0x54e9c8),next=index+1;
 put(d,(uint32_t)object);put(b+4,(uint32_t)id);put(b+8,0x2fa670+index*16);put(0x54e9c8,next);
 int64_t signedNext=(int64_t)(next&0x7fffffffu)-(int64_t)(next&0x80000000u);put(0x54e9c8,(uint32_t)(signedNext%10));return mover;
}
uint64_t dds3ObjectBaseCreateMover(uint64_t object)
{
 uint64_t existing=dds3ObjectBaseGetControlBasic(object,1);if(existing)return existing;
 uint64_t mover=dds3AddMoverBasic(object);return dds3ObjectBaseSetControlBasic(object,mover);
}
uint64_t dds3CameraObjectBasicConstructor(uint64_t basic)
{
 (void)dds3InitPoseSet(basic);uint32_t d=ps2PoolAllocate(144);put((uint32_t)basic+24,d);
 put(d+128,(uint32_t)dds3ObjectBaseInitControlWorkData(basic));dds3ObjectBaseOnFlag(basic,0x62);put(d+136,0);return 1;
}
uint64_t dds3AddCameraObjectBasicDef(uint64_t serial)
{uint64_t b=dds3AddSceneBasicData(4);put((uint32_t)b+4,(uint32_t)serial);(void)dds3ObjectBaseCreateMover(b);return b;}
uint64_t dds3AddPathBasic(uint64_t serial,uint64_t data,uint64_t name)
{uint64_t b=dds3AddSceneBasicData(17);put((uint32_t)b+8,(uint32_t)name);put((uint32_t)b+24,(uint32_t)data);put((uint32_t)b+4,(uint32_t)serial);return b;}

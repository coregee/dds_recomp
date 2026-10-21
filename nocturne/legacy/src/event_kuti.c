/* Native event-unit lookup and message-driven mouth motion. */
#include "event_kuti.h"
#include "script_construction.h"
#include "script_core.h"
#include "script_movie.h"
#include "message_request.h"
#include <string.h>
static uint8_t *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void half(uint32_t a,uint64_t v){uint16_t x=(uint16_t)v;memcpy(at(a),&x,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 0010e548: native active scene has a nullable world basic. */
uint64_t dds3GetActiveScene(void){uint32_t w=word(0x54e9c4);return w?sx(word(word(w+24)+8)):0;}
/* 0010f208: type*12 native intrusive-list header; compare full raw64 serial
 * against the sign-extended live ID. A nonzero count presumes a valid head. */
uint64_t dds3SearchSceneBasic(uint64_t scene,uint64_t serial,uint64_t type)
{
 uint32_t table=word(word((uint32_t)scene+24)+8),header=table+(uint32_t)type*12;
 if(!word(header))return 0;uint32_t node=word(header+4);
 do{if(serial==sx(word(node+4)))return sx(node);node=word(node+32);}while(node);return 0;
}
/* 001e3988: type five unit object is reached through basic+18/data+8. */
uint64_t evtGetUnitHandle(uint64_t serial)
{uint64_t basic=dds3SearchSceneBasic(dds3GetActiveScene(),serial,5);return basic?sx(word(word((uint32_t)basic+24)+8)):0;}
/* 001e3c30: stores precede the exact raw64 mode tests; indexed fields can alias. */
void evtSetUnitExMotion(uint64_t unit,uint64_t group,uint64_t motion,uint64_t before,uint64_t smooth,uint64_t mode)
{
 uint32_t p=(uint32_t)unit,g=(uint32_t)group,flag=p+g+204,index=p+g*2;
 *at(flag)=3;half(index+240,motion);half(index+264,before);half(index+288,smooth);
 if(mode==1)*at(flag)|=8;else if((int64_t)mode>=2){if(mode==2)*at(flag)|=16;}else if(!mode)*at(flag)|=4;
}
/* 001e3bf0: byte stores retain native order. */
void evtSetUnitKutiMotion(uint64_t unit,uint64_t group,uint64_t motion)
{*at((uint32_t)unit+203)=(uint8_t)motion;*at((uint32_t)unit+202)=(uint8_t)group;}
/* 001e3c00: native signed LB, no null guard; mode two means deferred mouth motion. */
void evtRunUnitKutiMotion(uint64_t unit)
{uint32_t p=(uint32_t)unit;uint32_t g=*at(p+202),m=*at(p+203);evtSetUnitExMotion(unit,sx(g&128?g|0xffffff00u:g),sx(m&128?m|0xffffff00u:m),0,0,2);}
/* 001e52b0: latest selected unit is reloaded when the callback executes. */
void evtCommandKutiFunction(void){evtRunUnitKutiMotion(sx(word(0x54f754)));}
/* 001e52c8/001e5360: actual VM getters, scene search and callback setter. */
static uint64_t command(unsigned run)
{
 uint64_t unit=evtGetUnitHandle(scrGetIntPara(0));if(!unit)return 1;
 uint64_t group=scrGetIntPara(1),motion=scrGetIntPara(2);evtSetUnitKutiMotion(unit,group,motion);
 if(run)evtRunUnitKutiMotion(unit);put(0x54f754,(uint32_t)unit);
 uint64_t id=scrGetMessageHandle();if(!(id>>63))itfMesMngSetKutiCallback(id,0x1e52b0);return 1;
}
uint64_t evtCommand_KUTISET(void){return command(0);}
uint64_t evtCommand_KUTI(void){return command(1);}

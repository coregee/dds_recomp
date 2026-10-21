/* Native camera selection and first-person projection restoration. */
#include "event_camera.h"
#include "event_kuti.h"
#include "script_construction.h"
#include "script_process.h"
#include "script_movie.h"
#include "nocturne.h"
#include "ee_fpu.h"
#include <string.h>
static uint8_t *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t signedByte(uint32_t a){uint32_t v=*at(a);return v&128?(int32_t)v-256:(int32_t)v;}
/* 00101898: signed-byte sum, then reverse exact comparison including NUL.
 * The three process queues are searched in their native traversal order. */
uint64_t dds3SearchProcessName(uint64_t name)
{
 uint32_t p=(uint32_t)name,length=0,sum=0;
 while(*at(p+length)){sum+=(uint32_t)signedByte(p+length);length++;}
 static const uint32_t heads[]={0x54e850,0x54e868,0x54e85c};
 for(unsigned k=0;k<3;k++)for(uint32_t node=word(heads[k]);node;node=word(node+60)){
  if(word(node+24)!=sum)continue;
  uint32_t n=length;
  for(;;){if(*at(p+n)!=*at(node+n))break;if(!n)return sx(node);n--;}
 }
 return 0;
}
/* 0010f1b0 / 0010f178: setter publishes low32 and returns the old signed handle. */
uint64_t dds3GetActiveCameraSceneBasic(uint64_t scene)
{return sx(word(word((uint32_t)scene+24)+12));}
uint64_t dds3SetActiveCameraSceneBasic(uint64_t scene,uint64_t camera)
{uint32_t data=word((uint32_t)scene+24);uint64_t old=dds3GetActiveCameraSceneBasic(scene);put(data+12,(uint32_t)camera);return old;}
/* 001225f8 / 00122608 */
uint64_t fldGetFollowCameraControl(void){return UINT64_C(0x2fc360);}
uint64_t fldGetUnitFollowCamera(void){return sx(word((uint32_t)fldGetFollowCameraControl()+120));}
/* 001e4b50: native wrapper tail-calls the actual scene-list search. */
uint64_t evtSearchBasic(uint64_t type,uint64_t serial)
{return dds3SearchSceneBasic(dds3GetActiveScene(),serial,type);}
/* 00105580: raw SWC1; no arithmetic or HD managed null checks. */
void dds3SetScreenFovy(float fovy){uint32_t bits;memcpy(&bits,&fovy,4);put(0x2f59bc,bits);}
/* 0012fc08: every gate precedes the original field table and COP1 operations. */
void fldCamSyukanSuriawase(void)
{
 if(!dds3SearchProcessName(0x531c18)||word(0x2fbf98)||!evtBitCheck(0xaf0)||scrSearchScriptName(0x531bf0))return;
 if(dds3GetActiveCameraSceneBasic(dds3GetActiveScene())!=fldGetUnitFollowCamera())return;
 uint32_t angle=word(0x2fc7cc+word(0x2fc01c)*16);
 uint32_t bits=EE_FPU_DIV_S(EE_FPU_MUL_S(angle,word(0x54c3b8)),UINT32_C(0x43340000));
 float fovy;memcpy(&fovy,&bits,4);dds3SetScreenFovy(fovy);
}
/* 001e76d0: negative IDs restore the follow camera; missing IDs leave it alone. */
uint64_t evtCommand_CAM_SEL(void)
{
 uint64_t id=scrGetIntPara(0),camera;
 if((int64_t)id<0)camera=fldGetUnitFollowCamera();
 else{fldCamSyukanSuriawase();camera=evtSearchBasic(4,scrGetIntPara(0));}
 if(camera)dds3SetActiveCameraSceneBasic(dds3GetActiveScene(),camera);
 return 1;
}

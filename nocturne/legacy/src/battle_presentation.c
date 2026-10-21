/* Battle-script presentation and formation bodies. Native PS2 layout and
 * instruction order are authoritative; the managed HD layout differs. */
#include "battle_presentation.h"
#include "battle_work_access.h"
#include "basic_pose.h"
#include "world_arrays.h"
#include "ee_vu_rotation.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include "script_core.h"
#include "script_movie.h"
#include "libc_printf.h"
#include "libc_stream.h"
#include <string.h>
static uint8_t *at(uint32_t p){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveBattlePresentationAddress(p);
#else
 return (uint8_t *)(uintptr_t)p;
#endif
}
static uint32_t r32(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static uint16_t r16(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static void w32(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static void w16(uint32_t p,uint16_t v){memcpy(at(p),&v,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint64_t lh(uint32_t p){uint32_t v=r16(p);return sx(v&0x8000u?v|0xffff0000u:v);}
static uint32_t slots(void){return r32((uint32_t)nbGetMainProcessData());}
static void copy16(uint32_t d,uint32_t s){uint32_t v[4];memcpy(v,at(s),16);memcpy(at(d),v,16);}
static void load(unsigned r,uint32_t p){uint32_t v[4];memcpy(v,at(p),16);EE_ROT_VU_WRITE(r,v);}
static void store(unsigned r,uint32_t p){uint32_t v[4];EE_ROT_VU_READ(r,v);memcpy(at(p),v,16);}
static void value(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned bc,unsigned op){
 uint32_t a[4],b[4],v[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_VU_READ(d,v);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint32_t x=b[bc==4?k:bc];v[k]=(uint32_t)(op==0?EE_ROT_VU_ADD(a[k],x):op==1?EE_ROT_VU_SUB(a[k],x):EE_ROT_VU_MUL(a[k],x));}
 EE_ROT_VU_WRITE(d,v);
}
static void accum(unsigned d,unsigned s,unsigned t,unsigned mask,unsigned bc,unsigned op){
 uint32_t a[4],b[4],v[4],ac[4],of[4];EE_ROT_VU_READ(s,a);EE_ROT_VU_READ(t,b);EE_ROT_ACC_READ(ac,of);
 if(d==32)memcpy(v,ac,16);else EE_ROT_VU_READ(d,v);
 for(unsigned k=0;k<4;k++)if(mask&(8u>>k)){uint64_t x=op==1?EE_ROT_VU_MUL(a[k],b[bc]):EE_ROT_VU_MAC(ac[k],a[k],b[bc],of[k],0);v[k]=(uint32_t)x;if(d==32)of[k]=(uint32_t)(x>>32)&1;}
 if(d==32)EE_ROT_ACC_WRITE(v,of);else EE_ROT_VU_WRITE(d,v);
}
static void transform(void){accum(32,28,10,15,0,1);accum(32,29,10,15,1,2);accum(32,30,10,15,2,2);accum(10,31,10,15,3,2);}
void effBTLSkillSetFormationInfo(uint64_t index,uint64_t mask){
 uint32_t first=slots(),count=0;w32(0x569968,(uint32_t)mask);w32(0x5698e0,first+(uint32_t)index*240u);
 for(unsigned k=0;k<32;k++)if(mask&sx(1u<<k))w32(0x5698e4+count++*4,first+k*240u);
 w32(0x569964,count);ps2LibcPrintf(0x532f68);
}
uint64_t effBTLSkillGetInvokeFormation(void){uint32_t p=r32(0x5698e0);if(p)return sx(p);uint32_t m=(uint32_t)nbGetMainProcessData();ps2LibcPrintf(0x532f90);return sx(r32(m));}
uint64_t effBTLSkillGetTargetParty(void){uint32_t p=r32(0x5698e4);return p?r32(p+0x78)&0x700u:0x100;}
uint64_t effBTLSkillGetTargetBit(void){return sx(r32(0x569968));}
void effBTLModelGetSphereCenter(uint64_t raw){
 uint32_t p=(uint32_t)raw;load(10,p+0x30);sdfQuatToMatrix();load(10,p+0x40);
 /* Original MFC1 writes low64 of V0 and QMTC2 also transports its untouched
  * upper64. That architectural input is retained by this processor boundary. */
 EE_BATTLE_QMTC2_SCALE(r32(p+0x5c));value(10,10,2,15,0,2);transform();load(11,p+0x20);value(10,10,11,15,4,0);
}
uint32_t effBTLModelGetHeightBits(uint64_t p){effBTLModelGetSphereCenter(p);uint32_t v[4];EE_ROT_VU_READ(10,v);return EE_FPU_SUB_S(EE_FPU_MUL_S(EE_FPU_MUL_S(r32((uint32_t)p+0x54),r32((uint32_t)p+0x5c)),0x3f000000),v[1]);}
void nbSetFormPos(uint64_t raw,uint64_t source){
 uint32_t p=(uint32_t)raw,s=(uint32_t)source;copy16(p+0x20,s);
 if((r32(p+0x78)&3)==3&&r32(p+0x84)){dds3SetPosPoseSet(sx(r32(p+0x84)),source);copy16(p+0x20,s);}
}
void nbSetFormRot(uint64_t raw,uint64_t source){
 uint32_t p=(uint32_t)raw,s=(uint32_t)source;copy16(p+0x30,s);
 if((r32(p+0x78)&3)==3&&r32(p+0x84)){load(10,s);load(11,0x5458b0);sdfQuatMult();store(10,0x575440);dds3SetRotPoseSet(sx(r32(p+0x84)),0x575440);copy16(p+0x30,s);}
}
void effBTLModelSetPosition(uint64_t p,uint64_t s){nbSetFormPos(p,s);}
void effBTLModelAllPopPosition(void){uint32_t p=slots();for(unsigned k=0;k<32;k++,p+=240)if((r32(p+0x78)&3)==3)effBTLModelSetPosition(sx(p),sx(p));}
void effBTLModelAllPopRotate(void){uint32_t p=slots();for(unsigned k=0;k<32;k++,p+=240)if((r32(p+0x78)&3)==3)nbSetFormRot(sx(p),sx(p+0x10));}
void effBTLModelShow(uint64_t p){*at(0x569a00+(uint32_t)lh((uint32_t)p+0x92))=1;}
void effBTLModelHide(uint64_t p){*at(0x569a00+(uint32_t)lh((uint32_t)p+0x92))=0;}
void effBTLModelAllHide(void){uint32_t p=slots();for(unsigned k=0;k<32;k++,p+=240)if((r32(p+0x78)&3)==3)effBTLModelHide(sx(p));}
void effBTLModelTargetGroupHide(void){
 uint32_t party=(uint32_t)effBTLSkillGetTargetParty(),mask=(uint32_t)effBTLSkillGetTargetBit(),p=slots();
 for(unsigned k=0;k<32;k++,p+=240,mask>>=1)if((r32(p+0x78)&party)&&(r32(p+0x78)&3)==3){if(mask&1)effBTLModelShow(sx(p));else effBTLModelHide(sx(p));}
}
void effBTLModelTargetPartyShow(void){uint32_t party=(uint32_t)effBTLSkillGetTargetParty(),p=slots();for(unsigned k=0;k<32;k++,p+=240)if((r32(p+0x78)&party)&&(r32(p+0x78)&3)==3)effBTLModelShow(sx(p));}
void nbCameraSetState(uint64_t state){w32(0x320e68,(uint16_t)state);if(*at(0x320c5c+(uint16_t)state*16u))w32(0x320e6c,0);}
static void selectCameraTarget(uint64_t target){effBTLSkillSetFormationInfo(lh((uint32_t)effBTLSkillGetInvokeFormation()+0x92),sx(1u<<((uint32_t)lh((uint32_t)target+0x92)&31)));}
void nbCameraScriptSet1Shot(uint64_t target){selectCameraTarget(target);effBTLModelAllPopPosition();effBTLModelAllPopRotate();effBTLModelAllHide();effBTLModelTargetGroupHide();nbCameraSetState(0x1a);}
void nbCameraScriptSet(uint64_t position,uint64_t rotation){
 effBTLModelAllPopPosition();effBTLModelAllPopRotate();load(10,(uint32_t)rotation);sdfQuatToMatrix();load(10,0x320e30);transform();store(10,0x320e50);
 load(11,(uint32_t)position);value(10,10,11,15,4,0);store(10,0x320e40);w32(0x320e60,0x3f800000);w32(0x320e64,r32(0x54ca88));nbCameraSetState(0x1c);
}
uint32_t nbGetPartyDistanceBits(void){return 0x44480000;}
uint32_t sdfAtanBits(uint32_t x){uint32_t square=EE_FPU_MUL_S(x,x),first=EE_FPU_MUL_S(x,r32(0x54e778)),cube=EE_FPU_MUL_S(square,x);return EE_FPU_ADD_S(EE_FPU_ADD_S(first,EE_FPU_MUL_S(cube,r32(0x54e77c))),EE_FPU_MUL_S(EE_FPU_MUL_S(square,cube),r32(0x54e780)));}
void nbCameraScriptSetBougai(uint64_t target){
 uint32_t maximum=0,width=0,count=0;selectCameraTarget(target);effBTLModelAllPopPosition();effBTLModelAllPopRotate();effBTLModelAllHide();effBTLModelTargetPartyShow();
 uint32_t party=r32((uint32_t)target+0x78)&0x200?0x200:0x100,p=slots();
 for(unsigned k=0;k<32;k++,p+=240)if((r32(p+0x78)&party)&&(r32(p+0x78)&1)){
  uint32_t radius=EE_FPU_MUL_S(r32(p+0x50),r32(p+0x5c));width=EE_FPU_ADD_S(width,EE_FPU_ADD_S(radius,radius));
  uint32_t height=effBTLModelGetHeightBits(sx(p));if(EE_FPU_COMPARE_S(maximum,height,1))maximum=height;count++;
 }
 if(!count)return;
 uint32_t angle=sdfAtanBits(EE_FPU_MUL_S(r32(count==1?0x54ca80:0x54ca84),0x3f000000));
 width=EE_FPU_MUL_S(EE_FPU_COMPARE_S(width,maximum,1)?maximum:width,0x3f000000);
 if(EE_FPU_COMPARE_S(width,0x43c80000,1))width=0x43c80000;
 uint32_t distance=EE_FPU_DIV_S(width,angle),z=EE_FPU_MUL_S(nbGetPartyDistanceBits(),0x3f000000);
 /* Original XYZ-only automatic vectors read both untouched stack W words.
  * Preserve those ambient operands instead of silently assigning W=0/1. */
 uint32_t position[4]={0,EE_FPU_MUL_S(maximum,0x3f000000)^0x80000000u,z,EE_BATTLE_FRAME_W(0)},
          aim[4]={0,0xc3200000,EE_FPU_SUB_S(z,distance),EE_BATTLE_FRAME_W(1)};
 EE_ROT_VU_WRITE(10,position);store(10,0x320e40);EE_ROT_VU_WRITE(11,aim);value(10,10,11,15,4,1);
 value(2,10,10,14,4,2);value(2,2,2,8,1,0);value(2,2,2,8,2,0);
 uint32_t v[4];EE_ROT_VU_READ(2,v);uint32_t q=EE_BATTLE_VU_SQRT(v[0]);EE_ROT_Q_WRITE(q);w32(0x320e60,q);
 value(2,10,10,14,4,2);accum(32,0,2,1,0,1);accum(32,0,2,1,1,2);accum(2,0,2,1,2,2);
 EE_ROT_VU_READ(2,v);q=EE_ROT_VU_RSQRT(0x3f800000,v[3]);EE_ROT_Q_WRITE(q);EE_ROT_VU_READ(10,v);for(unsigned k=0;k<3;k++)v[k]=(uint32_t)EE_ROT_VU_MUL(v[k],q);EE_ROT_VU_WRITE(10,v);store(10,0x320e50);nbCameraSetState(0x1b);
}
void nbFormDispOff(uint64_t index){
 uint32_t p=slots()+(uint32_t)index*240u;if((r32(p+0x78)&3)==3&&r32(p+0x84)){uint32_t f=r32(r32(p+0x8c)+0x8c);w32(f,r32(f)|1);dds3ObjectBaseOnFlag(sx(r32(p+0x84)),0x1000);}
}
void nbFormDispOn(uint64_t index){
 uint32_t p=slots()+(uint32_t)index*240u;if((r32(p+0x78)&3)==3&&r32(p+0x84)){uint32_t f=r32(r32(p+0x8c)+0x8c);w32(f,r32(f)&~1u);dds3ObjectBaseOffFlag(sx(r32(p+0x84)),0x1000);}
}
void nbGroupFormDispOff(uint64_t group){unsigned lo,hi;if(group==0){lo=0;hi=4;}else if(group==1){lo=4;hi=14;}else if(group==2){lo=14;hi=16;}else return;for(;lo<hi;lo++)nbFormDispOff(lo);}
void nbGroupFormDispOn(uint64_t group){unsigned lo,hi;if(group==0){lo=0;hi=4;}else if(group==1){lo=4;hi=14;}else if(group==2){lo=14;hi=16;}else return;for(;lo<hi;lo++)nbFormDispOn(lo);}
void nbAllFormDispOn(void){for(unsigned k=0;k<16;k++)nbFormDispOn(k);}
void ps2BattlePanelHideHookA(void){*at(0x55123c)=0;}
void ps2BattlePanelHideHookB(void){*at(0x55123d)=0;}
void nbPanelAutoHide(void){ps2BattlePanelHideHookA();ps2BattlePanelHideHookB();*at(0x5511a5)=0;}
uint64_t nbCommand_BTL_PNL_OFF(void){nbPanelAutoHide();ps2BattlePanelHideHookA();return 1;}
uint64_t nbCommand_BTL_FORM_ALL_ON(void){nbAllFormDispOn();return 1;}
uint64_t nbCommand_BTL_FORM_ENE_ON(void){nbGroupFormDispOff(0);nbGroupFormDispOn(1);return 1;}
uint64_t nbCommand_BTL_AI_CHANGE_OFF(void){uint32_t p=(uint32_t)nbGetMainProcessData()+0x60;w32(p,r32(p)|0x40000);return 1;}
uint64_t nbCommand_BTL_AI_CHANGE_ON(void){uint32_t p=(uint32_t)nbGetMainProcessData()+0x60;w32(p,r32(p)&~0x40000u);return 1;}
uint64_t nbCommand_BTL_EVENT(void){uint32_t ctx=(uint32_t)scrGetData();uint64_t event=scrGetIntPara(0);w32(r32(ctx)+0x88,(uint32_t)event);return 1;}
static uint64_t battleEvent(unsigned event){uint32_t ctx=(uint32_t)scrGetData(),p=r32(ctx),actor=r32(ctx+0x28);uint16_t index=r16(actor+0x92);w32(p+0x94,event);w16(p+0x92,index);w32(ctx+0x68,0);return 1;}
uint64_t nbCommand_BTL_PRESS(void){return battleEvent(4);}
uint64_t nbCommand_BTL_NAKAMA(void){return battleEvent(3);}
uint64_t nbCommand_BTL_CAM_1SHOT(void){uint32_t ctx=(uint32_t)scrGetData();nbCameraScriptSet1Shot(sx(r32(ctx+0x28)));return 1;}
uint64_t nbCommand_BTL_CAM_BOUGAI(void){uint32_t ctx=(uint32_t)scrGetData();nbCameraScriptSetBougai(sx(r32(ctx+0x28)));return 1;}
uint64_t nbCommand_BTL_CAM_SET(void){
 uint32_t vectors[8]={0};(void)scrGetData();for(unsigned k=0;k<3;k++)vectors[k]=scrGetFloatParaBits(k);for(unsigned k=0;k<4;k++)vectors[4+k]=scrGetFloatParaBits(k+3);
 uint32_t address=nocturneLibcStreamLocalAddress(vectors,32);nbCameraScriptSet(address,address+16);nocturneLibcStreamEndLocal();return 1;
}

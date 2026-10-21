/* Original basic AI record evaluation, action selection and command queries. */
#include "battle_ai_execution.h"
#include "battle_ai_conditions.h"
#include "battle_ai_actions.h"
#include "battle_ai_selection.h"
#include "battle_ai_estimates.h"
#include "battle_support_access.h"
#include "battle_work_access.h"
#include "libc_printf.h"
#include "script_core.h"
#include "script_movie.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleAiExecutionAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint64_t lh(uint32_t a){uint32_t v=r16(a);return sx(v&0x8000u?v|0xffff0000u:v);}
static int positive(uint64_t v){return v&&!(v>>63);}
static uint32_t aiRecord(uint32_t ctx){return 0x3989e0+r16(r32(ctx+0x2c)+4)*164u;}
static uint32_t actionRecord(uint32_t ctx,uint64_t table,uint64_t action){return aiRecord(ctx)+0x28+(uint32_t)table*40u+(uint32_t)action*8u;}
uint64_t nbAiAiChk(uint64_t raw,uint64_t n){
 uint32_t ctx=(uint32_t)raw;w32(ctx+0x190,0);
 uint32_t p=aiRecord(ctx)+4+(uint32_t)n*12u,first=r32(p),second=r32(p+4);
 w32(ctx+0x194,(uint32_t)n);
 if(!nbAiChkJoken(raw,sx(first))||!nbAiChkJoken(raw,sx(second)))return 0;
 /* Type21 aliases the same increment callback but does not enter this reset. */
 if((first>>16)==4||(second>>16)==4)nbSetHojoCounter(lh(r32(ctx+0x28)+0x92),sx((uint32_t)n+1u),0);
 return 1;
}
uint64_t nbAiGetKoudou(uint64_t raw,uint64_t table){
 uint32_t ctx=(uint32_t)raw,p=actionRecord(ctx,table,0),indices[5],count=0,total=0;
 for(uint32_t k=0;k<5;k++){
  uint8_t excluded=*at(ctx+0x198+k);
  if(excluded==0||(excluded&0x80)){indices[count++]=k;total+=r16(p+k*8u);}
 }
 if(!count||!total)return UINT64_MAX;
 uint32_t roll=sdfGetRandInt(NULL,total),sum=0;
 for(uint32_t k=0;k<count;k++){sum+=r16(p+indices[k]*8u);if((int32_t)roll<(int32_t)sum)return sx(indices[k]);}
 return UINT64_MAX;
}
void nbAiSetKoudou(uint64_t raw,uint64_t table,uint64_t action){
 uint32_t ctx=(uint32_t)raw,u=r32(ctx+0x2c);w16(u+0x6a,0);w16(u+0x6c,0);
 uint32_t p=actionRecord(ctx,table,action);uint16_t skill=r16(p+2);
 if(skill==0x8000){w16(u+0x6a,0);nbSetNormalSkill0(sx(u));return;}
 if(skill==0x8001){w16(u+0x6a,7);return;}
 if(skill==0x8002){w16(u+0x6a,3);return;}
 if(skill==0x8003){w16(u+0x6a,9);return;}
 if(!(skill&0x8000)){w16(u+0x6a,1);w16(u+0x6c,r16(p+2));return;}
 w16(u+0x6a,1);skill=r16(p+2);
 switch(skill&0xf000){
 case 0x9000:w16(u+0x6c,0xe2);break;
 case 0xa000:w16(u+0x6c,0xe3);break;
 case 0xb000:w16(u+0x6c,0xe5);break;
 case 0xc000:w16(u+0x6c,0xe6);break;
 case 0xd000:w16(u+0x6c,0xfc);break;
 case 0xf000:w16(u+0x6c,0xde);break;
 case 0xe000:w16(u+0x6a,9);w32(r32(ctx)+0x88,r16(p+2)&0xfffu);break;
 default:w32(ctx+0x1a0,skill&0xfffu);return;
 }
 w32(ctx+0x1a0,r16(p+2)&0xfffu);
}
uint64_t nbCheckSkillUse(uint64_t formation,uint64_t skill){
 uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(formation);
 if((r16(u+0xe)&0xfffu)==0x20&&*at(0x3d799a+(uint32_t)skill*60u)==1)return 1;
 uint64_t cost=nbCheckSkillCost(formation,skill);
 return cost==1?2:cost==2?3:0;
}
uint64_t nbAiChkCost(uint64_t raw){
 uint32_t ctx=(uint32_t)raw,u=r32(ctx+0x2c);uint64_t action=lh(u+0x6a),skill=0;
 if(action==1||action==5)skill=r16(u+0x6c);else if(action)return 0;
 if(!nbCheckSkillCost(lh(r32(ctx+0x28)+0x92),skill))return 0;
 uint32_t mode=r16(aiRecord(ctx)+2);return mode!=0&&mode<3;
}
uint64_t nbAiChkClose(uint64_t raw){
 uint32_t ctx=(uint32_t)raw,u=r32(ctx+0x2c);uint64_t action=lh(u+0x6a),skill=0;
 if(action==1||action==5)skill=r16(u+0x6c);else if(action)return 1;
 if(!positive(nbCheckSkillUse(lh(r32(ctx+0x28)+0x92),skill)))return 1;
 uint32_t mode=r16(aiRecord(ctx)+2);return mode==0||mode>=3;
}
uint64_t nbRunAiSub(uint64_t raw,uint64_t table){
 uint32_t ctx=(uint32_t)raw;for(uint32_t k=0;k<5;k++)*at(ctx+0x19c-k)=0;
 uint64_t action;
 for(;;){
  action=nbAiGetKoudou(raw,table);(void)ps2LibcPrintf(0x545830,action);
  if(action>>63)break;
  nbAiSetKoudou(raw,table,action);
  if(!nbAiChkCost(raw)&&nbAiChkClose(raw)){
   uint32_t target=r32(actionRecord(ctx,table,action)+4);
   if(!nbSetAiTarget(raw,target>>16,target&0xffffu))break;
  }
  *at(ctx+0x198+(uint32_t)action)=1;
 }
 if(action>>63){uint32_t u=r32(ctx+0x2c);w32(ctx+0x3c,0);w16(u+0x6a,3);w16(u+0x6c,0);}
 else w32(ctx+0x3c,(uint32_t)nbGetSelectBit(sx(r32(ctx))));
 return 0;
}
uint64_t nbRunAi(uint64_t raw){
 uint32_t ctx=(uint32_t)raw,table=0;
 for(uint32_t n=0;n<3;n++)if(nbAiAiChk(raw,n)){table=r32(aiRecord(ctx)+12+n*12u);break;}
 (void)ps2LibcPrintf(0x545840,sx(table));return nbRunAiSub(raw,sx(table));
}
uint64_t nbGetAisyoTable(uint64_t formation){
 uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(formation);uint64_t result=0;
 if(!(r32(u)&4))result=lh(0x3497ce+r16(u+4)*60u);
 uint64_t support=nbGetHojoCounter(formation,19);if(positive(support))result=support;
 uint32_t status=r16(u+0xe)&0xfffu;
 return status==0x200?0xf7:status==0x400?0xf6:result;
}
uint64_t nbGetEscapeSwitch(uint64_t raw){uint32_t main=(uint32_t)raw;if(r32(main+0x60)&1)return 0;return *at(0x3aefe1+r32(main+0x34)*38u)!=1;}
uint64_t nbCommand_AI(void){(void)nbRunAi(scrGetData());return 1;}
uint64_t nbCommand_AI_GET_TURN(void){uint32_t ctx=(uint32_t)scrGetData();scrSetIntReturnValue(*at(r32(ctx)+0x68));return 1;}
uint64_t nbCommand_AI_GET_PRESSKOUDO(void){uint32_t ctx=(uint32_t)scrGetData();scrSetIntReturnValue(nbGetHojoCounter(lh(r32(ctx+0x28)+0x92),18));return 1;}
uint64_t nbCommand_AI_GET_MYLV(void){uint32_t ctx=(uint32_t)scrGetData();scrSetIntReturnValue(r16(r32(ctx+0x2c)+0x14));return 1;}
uint64_t nbCommand_AI_GET_MYAISYO(void){uint32_t ctx=(uint32_t)scrGetData();scrSetIntReturnValue(nbGetAisyoTable(lh(r32(ctx+0x28)+0x92)));return 1;}
uint64_t nbCommand_AI_GET_FUREA(void){uint32_t raw=evtGetAgeOfMoon16();raw+=raw>>31;uint32_t shifted=(raw>>1)|(raw&0x80000000u);scrSetIntReturnValue(sx(shifted));return 1;}
uint64_t nbCommand_AI_CHK_ESCAPE(void){uint32_t ctx=(uint32_t)scrGetData();scrSetIntReturnValue(nbGetEscapeSwitch(sx(r32(ctx)))!=0);return 1;}
uint64_t nbCommand_AI_ACT_SUMMON(void){
 uint32_t ctx=(uint32_t)scrGetData();uint16_t skill=(uint16_t)scrGetIntPara(0);uint32_t u=r32(ctx+0x2c);
 w16(u+0x6a,1);w16(u+0x6c,skill);uint64_t devil=scrGetIntPara(1);w32(ctx+0x1a0,(uint32_t)devil);
 (void)nbSetEnemySummonFormation(sx(r32(ctx)),devil);return 1;
}

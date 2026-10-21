/* Original retail BF random/wait commands and target-selection wrappers. */
#include "battle_script_commands.h"
#include "battle_ai_selection.h"
#include "battle_ai_actions.h"
#include "script_core.h"
#include "script_movie.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveBattleScriptCommandsAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 0010B908: unsigned low-word limit, then ADDIU +1 before the VM setter.
 * The actual RNG advances before its original BREAK7 on a zero limit. */
uint64_t scrCommand_RND(void){
 uint64_t parameter=scrGetIntPara(0);
 uint32_t value=sdfGetRandInt(NULL,(uint32_t)parameter)+1u;
 scrSetIntReturnValue(sx(value));return 1;
}
/* 00287DD8: action3 and skill0, preserving every other actor field. */
uint64_t nbCommand_AI_ACT_WAIT(void){
 uint32_t context=(uint32_t)scrGetData(),actor=r32(context+0x2c);
 w16(actor+0x6a,3);w16(actor+0x6c,0);return 1;
}
/* These wrappers retain the context across the parameter getter and retry.
 * A first nonzero result stores action3 in the real selector; its retry then
 * returns0 early and the wrapper writes the actual (possibly empty) bitset. */
static uint64_t target(uint64_t context,uint64_t selector,uint64_t parameter){
 uint64_t result=nbSetAiTarget(context,selector,parameter);
 if(result)result=nbSetAiTarget(context,0,0);
 if(!result)w32((uint32_t)context+0x3c,(uint32_t)nbGetSelectBit(sx(r32((uint32_t)context))));
 return 1;
}
uint64_t nbCommand_AI_TAR_LIFEMIN(void){return target(scrGetData(),1,0);}
uint64_t nbCommand_AI_TAR_BAARLV(void){return target(scrGetData(),9,0);}
uint64_t nbCommand_AI_TAR_LVMIN(void){return target(scrGetData(),10,0);}
uint64_t nbCommand_AI_TAR_BAD(void){uint64_t context=scrGetData();return target(context,2,scrGetIntPara(0));}
uint64_t nbCommand_AI_TAR_ID(void){uint64_t context=scrGetData();return target(context,3,scrGetIntPara(0));}
uint64_t nbCommand_AI_TAR_LIGHT(void){return target(scrGetData(),4,0);}
uint64_t nbCommand_AI_TAR_DARK(void){return target(scrGetData(),5,0);}
uint64_t nbCommand_AI_TAR_PLAYER(void){return target(scrGetData(),6,0);}
uint64_t nbCommand_AI_TAR_RND(void){return target(scrGetData(),8,0);}
uint64_t nbCommand_AI_TAR_JOKEN(void){return target(scrGetData(),7,0);}

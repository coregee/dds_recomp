#pragma once
#include <stdint.h>
#include <stddef.h>
/* Native record RAM003989E0/file002999E0, independently checked against all
 * 384 records. Community decision-data offset002999E4 starts after the header.
 * These are Nocturne PS2 fields; other SMT games require separate layout checks. */
typedef struct nbBasicAiCondition_PS2 {
 uint32_t first,second,table;
} nbBasicAiCondition_PS2;
typedef struct nbBasicAiAction_PS2 {
 uint16_t weight,action;
 uint32_t target;
} nbBasicAiAction_PS2;
typedef struct nbBasicAiRecord_PS2 {
 uint16_t procedure,cost_mode;
 nbBasicAiCondition_PS2 conditions[3];
 nbBasicAiAction_PS2 actions[3][5];
 uint32_t unknown_a0; /* Final four bytes are not read by these routines. */
} nbBasicAiRecord_PS2;
_Static_assert(sizeof(nbBasicAiCondition_PS2)==12,"Native AI condition stride");
_Static_assert(sizeof(nbBasicAiAction_PS2)==8,"Native AI action stride");
_Static_assert(offsetof(nbBasicAiRecord_PS2,conditions)==4,"Native AI decisions");
_Static_assert(offsetof(nbBasicAiRecord_PS2,actions)==40,"Native AI action tables");
_Static_assert(offsetof(nbBasicAiRecord_PS2,unknown_a0)==160,"Native AI trailing word");
_Static_assert(sizeof(nbBasicAiRecord_PS2)==164,"Native AI record stride");
uint64_t nbAiAiChk(uint64_t context,uint64_t condition);
uint64_t nbAiGetKoudou(uint64_t context,uint64_t table);
void nbAiSetKoudou(uint64_t context,uint64_t table,uint64_t action);
uint64_t nbAiChkCost(uint64_t context);
uint64_t nbAiChkClose(uint64_t context);
uint64_t nbRunAiSub(uint64_t context,uint64_t table);
uint64_t nbRunAi(uint64_t context);
uint64_t nbCheckSkillUse(uint64_t formation,uint64_t skill);
uint64_t nbGetAisyoTable(uint64_t formation);
uint64_t nbGetEscapeSwitch(uint64_t main);
uint64_t nbCommand_AI(void);
uint64_t nbCommand_AI_GET_TURN(void);
uint64_t nbCommand_AI_GET_PRESSKOUDO(void);
uint64_t nbCommand_AI_GET_MYLV(void);
uint64_t nbCommand_AI_GET_MYAISYO(void);
uint64_t nbCommand_AI_GET_FUREA(void);
uint64_t nbCommand_AI_CHK_ESCAPE(void);
uint64_t nbCommand_AI_ACT_SUMMON(void);
void *nocturneResolveBattleAiExecutionAddress(uint32_t address);

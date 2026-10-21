/* Complete original002E40D0 bank-native heap-lock bootstrap. Zero identity credit.
 * Actual80-byte guest frame and two full CreateSema leaves; no system result
 * provider, object/stack-output patch, router replacement or old source edit.
 */
#include "battle_action_skill_heap_bootstrap_frames.h"
#include "battle_action_skill_bridge_frames.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveBattleActionConsumerAddress(a);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static uint32_t ea(unsigned r,int32_t offset){return (uint32_t)cpu(r)+(uint32_t)offset;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void save(unsigned r,uint32_t a){uint64_t v=cpu(r);memcpy(at(a),&v,8);}
static void restore(unsigned r,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(r,v);}
/* The dispatcher result is only a C handled flag. Actual nativeV0 stays in
 * the shared CPU bank; the genuine four-op leaf owns the system boundary. */
static void callCreateSema(void){if(nocturneBattleActionSkillBridgeBody(UINT32_C(0x002dbea0))!=1u)abort();}
void ps2BattleActionSkillHeapBootstrap_002E40D0(void){
nocturneEffectAxisNoteEntry(UINT32_C(0x002e40d0));
uint64_t incoming=cpu(31),target;
/* 002e40d0: addiu sp,sp,-0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffb0)));
/* 002e40d4: li v0,0x1 */ set(2,sx(UINT32_C(1)));
/* 002e40d8: sd ra,0x40(sp) */ save(31,ea(29,0x40));
/* 002e40dc: move a0,sp */ set(4,cpu(29));
/* 002e40e0: sw v0,0x28(sp) */ sw(ea(29,0x28),(uint32_t)cpu(2));
/* 002e40e4: sw v0,0x4(sp) */ sw(ea(29,0x04),(uint32_t)cpu(2));
/* 002e40e8: sw v0,0x8(sp) */ sw(ea(29,0x08),(uint32_t)cpu(2));
/* 002e40ec: jal 0x002dbea0 */ set(31,UINT64_C(0x002e40f4));
/* 002e40f0: _sw v0,0x24(sp) */ sw(ea(29,0x24),(uint32_t)cpu(2));callCreateSema();
/* 002e40f4: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002e40f8: addiu a0,sp,0x20 */ set(4,sx((uint32_t)cpu(29)+UINT32_C(0x20)));
/* 002e40fc: jal 0x002dbea0 */ set(31,UINT64_C(0x002e4104));
/* 002e4100: _sw v0,-0x3c88(v1) */ sw(ea(3,-0x3c88),(uint32_t)cpu(2));callCreateSema();
/* 002e4104: lui v1,0x53 */ set(3,sx(UINT32_C(0x00530000)));
/* 002e4108: ld ra,0x40(sp) */ restore(31,ea(29,0x40));
/* 002e410c: sw v0,-0x3c84(v1) */ sw(ea(3,-0x3c84),(uint32_t)cpu(2));
/* 002e4110: jr ra */ target=cpu(31);
/* 002e4114: _addiu sp,sp,0x50 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x50)));if((uint32_t)target!=(uint32_t)incoming)abort();return;
}

#ifndef NOCTURNE_BATTLE_ACTION_SKILL_CORE_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_SKILL_CORE_FRAMES_H
#include <stdint.h>
/* Complete native core39: actual raw positional GPR slots and binary32
 * F12 formals. Shared live CPU/FPR/RAM/SP and Formula secondary bank
 * required. External endpoint routes real code, never supplies results. */
void nocturneBattleActionSkillCall(uint32_t target);
uint64_t ps2BattleActionSkill_0024D3A0(uint64_t a0, uint64_t a1, float f12);
float ps2BattleActionSkill_0024D428(uint64_t a0, uint64_t a1, float f12);
void ps2BattleActionSkill_0024F5F0(uint64_t a0, uint64_t a1, uint64_t a2);
void ps2BattleActionSkill_0024F658(uint64_t a0, uint64_t a1);
void ps2BattleActionSkill_0024F728(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionSkill_0024F7B8(uint64_t a0, uint64_t a1);
void ps2BattleActionSkill_0024F7E0(uint64_t a0, uint64_t a1, uint64_t a2);
void ps2BattleActionSkill_0024F8A8(uint64_t a0, uint64_t a1, uint64_t a2);
void ps2BattleActionSkill_0024F938(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_0024F990(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
void ps2BattleActionSkill_0024FB38(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1);
void ps2BattleActionSkill_0024FC28(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1);
void ps2BattleActionSkill_0024FCC0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1);
void ps2BattleActionSkill_0024FE40(uint64_t a0, uint64_t a1, uint64_t a2);
void ps2BattleActionSkill_00251770(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
void ps2BattleActionSkill_002518C8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionSkill_00252060(uint64_t a0);
void ps2BattleActionSkill_00252FB8(uint64_t a0, uint64_t a1, uint64_t a2);
void ps2BattleActionSkill_00255650(uint64_t a0);
uint64_t ps2BattleActionSkill_002594B0(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionSkill_002595A0(void);
uint64_t ps2BattleActionSkill_00261500(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionSkill_00261638(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2);
uint64_t ps2BattleActionSkill_00261E80(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_00262340(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
uint64_t ps2BattleActionSkill_00262430(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionSkill_00262A68(uint64_t a0, uint64_t a1, float f12);
uint64_t ps2BattleActionSkill_00262AC8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionSkill_00262E28(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionSkill_00262E78(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_00262ED8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
uint64_t ps2BattleActionSkill_00263028(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
uint64_t ps2BattleActionSkill_00263250(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_002632D0(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_00263548(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_002636C8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
uint64_t ps2BattleActionSkill_00263778(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_002642E0(uint64_t a0, uint64_t a1, float f12);
uint64_t ps2BattleActionSkill_00264368(uint64_t a0, uint64_t a1, uint64_t a2);
#endif

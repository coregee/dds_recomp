#ifndef NOCTURNE_BATTLE_ACTION_SKILL_SUPPORT_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_SKILL_SUPPORT_FRAMES_H
#include <stdint.h>
/* Exact native positional GPR/FPR formals. Full shared banks/SP required. */
/* This boundary selects code only; it must never supply game results. */
void nocturneBattleActionSkillCall(uint32_t target);
uint64_t ps2BattleActionSkill_00100410(void);
void ps2BattleActionSkill_00104870(void);
uint64_t ps2BattleActionSkill_001049D0(uint64_t a0, uint64_t a1, float f12);
void ps2BattleActionSkill_00104AC0(void);
uint64_t ps2BattleActionSkill_00104AF8(void);
uint64_t ps2BattleActionSkill_0016AB70(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionSkill_0016ABA0(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionSkill_0016AEC0(uint64_t a0);
void ps2BattleActionSkill_0016AEF0(uint64_t a0, uint64_t a1);
void ps2BattleActionSkill_0016B090(uint64_t a0);
void ps2BattleActionSkill_0016BA40(uint64_t a0);
void ps2BattleActionSkill_00197DD0(void);
uint64_t ps2BattleActionSkill_00198200(uint64_t a0);
uint64_t ps2BattleActionSkill_00198860(void);
uint64_t ps2BattleActionSkill_00198868(uint64_t a0);
uint64_t ps2BattleActionSkill_00198FF8(void);
uint64_t ps2BattleActionSkill_001C8268(uint64_t a0);
uint64_t ps2BattleActionSkill_001C9108(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionSkill_001CA0D0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2, uint64_t t3);
uint64_t ps2BattleActionSkill_001CA258(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1);
uint64_t ps2BattleActionSkill_001CEA58(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_001CF960(uint64_t a0);
void ps2BattleActionSkill_001DD578(uint64_t a0, uint64_t a1, uint64_t a2, float f12, float f13);
void ps2BattleActionSkill_00280518(void);
void ps2BattleActionSkill_00288E18(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
void ps2BattleActionSkill_00289008(uint64_t a0);
void ps2BattleActionSkill_00289450(void);
uint64_t ps2BattleActionSkill_0028FA80(void);
uint64_t ps2BattleActionSkill_002901D0(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionSkill_00290780(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionSkill_002AA718(uint64_t a0);
void ps2BattleActionSkill_002AA7F0(uint64_t a0);
uint64_t ps2BattleActionSkill_002AA8D0(uint64_t a0, uint64_t a1, uint64_t a2);
void ps2BattleActionSkill_002AB190(uint64_t a0, uint64_t a1);
void ps2BattleActionSkill_002AB860(uint64_t a0);
void ps2BattleActionSkill_002ABB78(uint64_t a0);
void ps2BattleActionSkill_002B5E30(void);
void ps2BattleActionSkill_002B6690(uint64_t a0);
void ps2BattleActionSkill_002B9E30(uint64_t a0, uint64_t a1, uint64_t a2);
void ps2BattleActionSkill_002BA070(uint64_t a0);
void ps2BattleActionSkill_002BA250(uint64_t a0, uint64_t a1, uint64_t a2);
float ps2BattleActionSkill_002CF6B8(float f12);
float ps2BattleActionSkill_002D0CA8(uint64_t a0, float f12, float f13);
#endif

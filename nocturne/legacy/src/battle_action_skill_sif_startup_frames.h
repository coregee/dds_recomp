#ifndef NOCTURNE_SKILL_SIF_STARTUP_FRAMES_H
#define NOCTURNE_SKILL_SIF_STARTUP_FRAMES_H
#include <stdint.h>
void nocturneBattleActionSkillCall(uint32_t target);
/* Handled flag only. Real guest results remain in the shared CPU bank. */
uint32_t nocturneBattleActionSkillSifStartupBody(uint32_t entry);
#endif

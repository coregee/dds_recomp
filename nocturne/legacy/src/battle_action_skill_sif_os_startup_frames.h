#ifndef NOCTURNE_SKILL_SIF_OS_STARTUP_FRAMES_H
#define NOCTURNE_SKILL_SIF_OS_STARTUP_FRAMES_H
#include <stdint.h>
/* Handled flag only. Inputs, results and volatile carry use the live EE bank. */
uint32_t nocturneBattleActionSkillSifOsStartupBody(uint32_t entry);
#endif

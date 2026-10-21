#ifndef NOCTURNE_SKILL_SIF_CACHE_FRAMES_H
#define NOCTURNE_SKILL_SIF_CACHE_FRAMES_H
#include <stdint.h>
/* Handled flag only. Arguments/results/carry remain in the shared EE bank. */
uint32_t nocturneBattleActionSkillSifCacheBody(uint32_t entry);
/* Actual CACHE: raw_address carries zero-extended wrapping32bit EA. No result. */
void nocturneBattleActionSkillSifReadyCacheValue(uint32_t pc,uint32_t operation,uint64_t raw_address);
#endif

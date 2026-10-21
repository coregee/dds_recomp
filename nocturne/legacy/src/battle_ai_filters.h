#ifndef NOCTURNE_BATTLE_AI_FILTERS_H
#define NOCTURNE_BATTLE_AI_FILTERS_H
#include <stdint.h>
void nbAiSelLifeMin(uint64_t context);
void nbAiSelBaarLv(uint64_t context);
void nbAiSelLvMin(uint64_t context);
void nbAiSelBad(uint64_t context,uint64_t status);
void nbAiSelId(uint64_t context,uint64_t id);
void nbAiSelLight(uint64_t context);
void nbAiSelDark(uint64_t context);
void nbAiSelPlayer(uint64_t context);
void nbAiSelJoken(uint64_t context);
void nbAiSelRnd(uint64_t context);
void *nocturneResolveBattleAiFiltersAddress(uint32_t address);
#endif

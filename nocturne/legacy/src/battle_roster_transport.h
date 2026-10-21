#ifndef NOCTURNE_BATTLE_ROSTER_TRANSPORT_H
#define NOCTURNE_BATTLE_ROSTER_TRANSPORT_H
#include <stdint.h>
/* One real guest RAM resolver and provider-owned SP shared with compendium.
 * No result, Main pointer, constructor or comparator answer is supplied. */
void *nocturneResolveBattleRosterAddress(uint32_t address);
uint32_t nocturneBattleRosterStackPointer(void);
void nocturneBattleRosterSetStackPointer(uint32_t address);
#endif

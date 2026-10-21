#ifndef NOCTURNE_BATTLE_PANEL_COLOR_PREREQUISITES_H
#define NOCTURNE_BATTLE_PANEL_COLOR_PREREQUISITES_H
#include <stdint.h>
/* Complete71 whole registered variants; native actual-bank entry dispatch.
 * Host handled1/0 only. No typed ABI or invented argument/return ownership.
 * Actual low/upper CPU/FPR/HI/LO/secondary state and guest frames carry through
 * all local calls. No native arguments are seeded by this dispatcher. */
uint32_t nocturneBattlePanelColorPrerequisiteBody(uint32_t entry);
/* UNIMPLEMENTED arbitrary-callback boundary. Must validate an actual native
 * target/ABI at its originalPC, execute real code, and retain real clobbers.
 * Unknown/privileged/unavailable routes must stop, never return fake success. */
void nocturneBattlePanelColorPrerequisiteIndirect(uint64_t target,uint32_t pc);
#endif

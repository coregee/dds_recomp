#ifndef NOCTURNE_BATTLE_ACTION_COMMAND_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_COMMAND_FRAMES_H
#include <stdint.h>
/* Genuine registered command payload variants. Real shared CPU/SP and dirty
 * private-frame inputs are retained; no AFTER initialization or patch. */
uint64_t ps2BattleActionCommand_002B0AC0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3);
uint64_t ps2BattleActionCommand_002B0B30(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3);
#endif

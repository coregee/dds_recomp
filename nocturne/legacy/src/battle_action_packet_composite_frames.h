#ifndef NOCTURNE_BATTLE_ACTION_PACKET_COMPOSITE_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_PACKET_COMPOSITE_FRAMES_H
#include <stdint.h>
/* Full registered native variants. Call only with the real shared
 * CPU/SP bank; all positional A0..T2 slots are raw64. Zero identity credit. */
uint64_t ps2BattleActionPacketComposite_00263810(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6);
uint64_t ps2BattleActionPacketComposite_00261E10(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacketComposite_002641F8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacketComposite_002622D0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
#endif

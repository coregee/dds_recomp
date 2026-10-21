#ifndef NOCTURNE_BATTLE_ACTION_PACKET_FRAMES_H
#define NOCTURNE_BATTLE_ACTION_PACKET_FRAMES_H
#include <stdint.h>
/* Whole registered native variants; actual shared CPU/SP/FPR required.
 * F12 formals are raw-bit transported, and no new identity is credited. */
uint64_t ps2BattleActionPacket_002515E8(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionPacket_0026A7D0(uint64_t a0);
void ps2BattleActionPacket_00247ED8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_002C0C60(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionPacket_00101898(uint64_t a0);
uint64_t ps2BattleActionPacket_0025E8E0(void);
uint64_t ps2BattleActionPacket_0025EA48(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
void ps2BattleActionPacket_0025E9C8(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionPacket_0025EF10(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_00261CA0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
uint64_t ps2BattleActionPacket_00261D20(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_00261D90(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
uint64_t ps2BattleActionPacket_00261FF0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_002620F0(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_00262170(float f12, uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_002621E0(float f12, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_00262610(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_00262670(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
void ps2BattleActionPacket_002627C0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6);
void ps2BattleActionPacket_002628D0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
uint64_t ps2BattleActionPacket_002629E8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
uint64_t ps2BattleActionPacket_00262B38(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
uint64_t ps2BattleActionPacket_00262BB8(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_00262C18(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_00262CC0(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_002630A8(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_00263350(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_002633E8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_00263458(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_002635A8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);
uint64_t ps2BattleActionPacket_002638A0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6);
uint64_t ps2BattleActionPacket_00264508(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_00264528(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
uint64_t ps2BattleActionPacket_002645A8(uint64_t a0, uint64_t a1, uint64_t a2);
uint64_t ps2BattleActionPacket_00267788(uint64_t a0);
uint64_t ps2BattleActionPacket_00259AB0(uint64_t a0);
uint64_t ps2BattleActionPacket_00259B70(uint64_t a0);
uint64_t ps2BattleActionPacket_00259A30(uint64_t a0);
/* Address-only adapter for legacy typed RNG callers with genuine bank inputs.
 * It validates the host pointer/lowword limit against actual A0/A1 and
 * invokes the complete native body without narrowing its live GPRs. */
uint32_t ps2BattleActionPacketRandomInt(uint32_t *state,uint32_t limit);
#endif

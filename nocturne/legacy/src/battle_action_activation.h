/* Original resource activation and registered native frame dependencies. */
#ifndef NOCTURNE_BATTLE_ACTION_ACTIVATION_H
#define NOCTURNE_BATTLE_ACTION_ACTIVATION_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
uint64_t ps2BattleAction_0016A9C0(uint64_t a0);
void ps2BattleAction_0016B588(uint64_t a0, uint64_t a1);
void ps2BattleAction_0016FE88(uint64_t a0, uint64_t a1);
/* Already registered functions; native guest frame variants earn no new credit. */
void ps2BattleActionPartScale_00175B38(uint64_t a0, float f12);
void ps2BattleActionPcpScale_00176120(uint64_t a0, float f12);
uint64_t ps2BattleActionPartCreate_00175998(uint64_t a0, uint64_t a1);
uint64_t ps2BattleActionPcpCreate_00175F08(uint64_t a0);
#ifdef __cplusplus
}
#endif
#endif

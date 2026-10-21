#ifndef NOCTURNE_NEGOTIATION_FULLMOON_H
#define NOCTURNE_NEGOTIATION_FULLMOON_H
#include <stdint.h>
void *nocturneResolveNegotiationFullMoonAddress(uint32_t address);
void ps2NegoCameraTarget_001B1810(uint64_t actor);
uint64_t ps2NegoResourcePacket_00262D38(uint64_t side,uint64_t owner,uint64_t resource);
void ps2NegoSetMoneyVariable_0026A918(uint64_t window,uint64_t amount);
void ps2NegoCloseWindow_0026A958(uint64_t context);
uint64_t ps2NegoMoneyReward_0026AC00(uint64_t context,uint64_t source,uint64_t target);
uint64_t ps2NegoMoneyRewardBase_0026AC78(uint64_t context,uint64_t source,uint64_t target);
uint64_t ps2NegoNoMotion_0026BDE0(uint64_t context,uint64_t actor);
uint64_t ps2NegoYesMotion_0026BE40(uint64_t context,uint64_t actor);
uint64_t ps2NegoActorUnitId_0028D070(uint64_t actor);
uint64_t ps2NegoPackMotionId_0028D1A8(uint64_t unit_id);
uint64_t ps2NegoActorMotionId_0028D1B8(uint64_t actor);
uint64_t ps2NegoFullMoon2_1_00274228(uint64_t context);
uint64_t ps2NegoFullMoon2_2_002743E8(uint64_t context);
uint64_t ps2NegoFullMoon2_3_002744B8(uint64_t context);
uint64_t ps2NegoFullMoon2_4_002744E0(uint64_t context);
uint64_t ps2NegoFullMoon2_5_00274540(uint64_t context);
uint64_t ps2NegoFullMoon2_6_00274690(uint64_t context);
uint64_t ps2NegoFullMoon2_7_00274908(uint64_t context);
uint64_t ps2NegoFullMoon2_8_00274948(uint64_t context);
uint64_t ps2NegoFullMoon2_9_00274970(uint64_t context);
uint64_t ps2NegoFullMoon2_10_00274A10(uint64_t context);
uint64_t ps2NegoFullMoon2_11_00274B98(uint64_t context);
uint64_t ps2NegoFullMoon2_12_00274C08(uint64_t context);
uint64_t ps2NegoFullMoon2_13_00274C50(uint64_t context);
uint64_t ps2NegoFullMoon2_14_00274D18(uint64_t context);
uint64_t ps2NegoFullMoon2_15_00274DB8(uint64_t context);
uint64_t ps2NegoFullMoon2_16_00274E00(uint64_t context);
#endif

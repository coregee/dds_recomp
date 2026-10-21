/* Native SLUS_209.11 interfaces; descriptive role leads are not symbols. */
#ifndef NOCTURNE_BATTLE_ACTION_CONSUMER_H
#define NOCTURNE_BATTLE_ACTION_CONSUMER_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

void *nocturneResolveBattleActionConsumerAddress(uint32_t address);

/* Hit14 instance constructor. */
uint64_t ps2BattleAction_00171A00(uint64_t a0);
/* Hit17 instance constructor. */
uint64_t ps2BattleAction_00171CC8(uint64_t a0);
/* Hit18 instance constructor. */
uint64_t ps2BattleAction_00172178(uint64_t a0);
/* Hit constructor table dispatch. */
uint64_t ps2BattleAction_00173CB0(uint64_t a0, uint64_t a1);
/* Hit query table dispatch. */
uint64_t ps2BattleAction_00173EF0(uint64_t a0);
/* Source-motion cleanup. */
void ps2BattleAction_0024F420(uint64_t a0, uint64_t a1);
/* Dead packet orchestration. */
void ps2BattleAction_0024F478(uint64_t a0, uint64_t a1);
/* Press float update. */
void ps2BattleAction_0024F548(uint64_t a0, float f12);
/* Maximum sequence time update. */
void ps2BattleAction_0024F5B0(uint64_t a0, uint64_t a1);
/* Minimum skill end time update. */
void ps2BattleAction_0024F5C8(uint64_t a0, uint64_t a1);
/* Complete action packet consumer. */
void ps2BattleAction_0024FF60(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2, float f12);
/* Timeline unlock query. */
uint64_t ps2BattleAction_00251750(uint64_t a0, uint64_t a1);
/* Counter check/composition. */
uint64_t ps2BattleAction_002521C8(uint64_t a0, uint64_t a1, uint64_t a2);
/* Current action state update. */
void ps2BattleAction_002592B0(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
/* Action command adjustment. */
uint64_t ps2BattleAction_00259300(uint64_t a0, uint64_t a1);
/* Status visual packet. */
uint64_t ps2BattleAction_00262480(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3);
/* Bad-status cure packet. */
uint64_t ps2BattleAction_002634C8(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
/* Death visual composition. */
uint64_t ps2BattleAction_00263918(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0);
/* Damage packet composition. */
uint64_t ps2BattleAction_00263C00(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2, uint64_t t3, uint32_t stack_0, uint32_t stack_8, uint32_t stack_16, uint32_t stack_24);
/* Recovery packet composition. */
uint64_t ps2BattleAction_00264010(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1, uint64_t t2);
/* PCF56 resource/instance record construction. */
uint64_t ps2BattleAction_0018F1B8(uint64_t a0);
/* PCF56 resource creator. */
uint64_t ps2BattleAction_0018F248(uint64_t a0);
/* PCF56 instance copy constructor. */
uint64_t ps2BattleAction_0018F268(uint64_t a0);
/* Four-column ring work allocation. */
uint64_t ps2BattleAction_00193488(uint64_t a0);
/* PCF58 ring geometry update. */
void ps2BattleAction_001937D0(uint64_t a0, float f12);
/* PCF58 geometry reset. */
void ps2BattleAction_00193958(uint64_t a0);
/* PCF58 ring record construction. */
uint64_t ps2BattleAction_00193988(uint64_t a0);
/* PCF58 resource creator. */
uint64_t ps2BattleAction_00193B20(uint64_t a0);
/* PCF58 instance copy constructor. */
uint64_t ps2BattleAction_00193B40(uint64_t a0);
/* PCF58 scale setter. */
void ps2BattleAction_00193DC0(uint64_t a0, float f12);
/* PCF70 oriented ring geometry update. */
void ps2BattleAction_00193E60(uint64_t a0, float f12);
/* PCF70 geometry reset. */
void ps2BattleAction_001940A8(uint64_t a0);
/* PCF70 ring record construction. */
uint64_t ps2BattleAction_00194108(uint64_t a0);
/* PCF70 resource creator. */
uint64_t ps2BattleAction_001942B0(uint64_t a0);
/* PCF70 instance copy constructor. */
uint64_t ps2BattleAction_001942D0(uint64_t a0);
/* PCF70 scale setter. */
void ps2BattleAction_00194450(uint64_t a0, float f12);
/* Blur point record initialization. */
void ps2BattleAction_001A26F0(uint64_t a0, uint64_t a1);
/* Blur trail resource construction. */
uint64_t ps2BattleAction_001A27A8(uint64_t a0);
/* Model attachment scheduler registration. */
uint64_t ps2BattleAction_001DE220(uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0, uint64_t t1);

/* Part-kind3 release adapter; real tail to registered001DD220. */
void ps2BattleAction_00175DF8(uint64_t a0);

#ifdef __cplusplus
}
#endif
#endif

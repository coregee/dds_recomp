#ifndef NOCTURNE_BATTLE_ALARM_PAYLOAD_H
#define NOCTURNE_BATTLE_ALARM_PAYLOAD_H
#include "battle_native_flow.h"
/* Actual pc selects a complete native body or the five-word trampoline.
 * No timer edge, exception, callback response or host-frame unwind is supplied.
 * ERET0, external-transfer8 and unexecuted-SYSCALL9 are router continuations;
 * they do not denote return of the original sleeping caller. */
uint32_t nocturneBattleAlarmPayloadResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif

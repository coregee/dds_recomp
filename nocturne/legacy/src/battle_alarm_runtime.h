#ifndef NOCTURNE_BATTLE_ALARM_RUNTIME_H
#define NOCTURNE_BATTLE_ALARM_RUNTIME_H
#include "battle_native_flow.h"
#include "battle_timer3_clock.h"
/* One source-owned CPU/RAM/device state across actual native continuations.
 * This test-clock profile supplies one HBLNK edge after each complete8-word
 * EENULL spin. It makes no EE-cycle/video/physical-timing equivalence claim.
 * Edge timing is explicit input policy; no Sleep response/count jump occurs. */
typedef struct NocturneAlarmRuntime {
 NocturneTimer3Clock clock;
 uint64_t idle_words,idle_spins,irq_entries,syscall_entries,erets;
 /* Optional passive bus receipt hook. Supplies no read value or reply. */
 void *bus_observer_owner;
 void (*observe_bus)(void *,uint32_t operation,uint32_t physical,uint32_t value);
} NocturneAlarmRuntime;
/* Run a known non-delay positive47/50/51/53/252 user SYSCALL. The outer game
 * instruction owner counts that entry word; internal yielded SYS words are
 * counted here once. Actual ERET into idle/callback continues natively.
 * Outcome0 requires reaching actual entryPC+4; other unowned continuations
 * transfer8. Clock/CPU/RAM are never reset between connected syscalls. */
uint32_t nocturneBattleAlarmRuntimeSyscall(NocturneWakeupMachine *,const NocturneWakeupMemory *,NocturneAlarmRuntime *,uint32_t syscall_pc,uint64_t max_instructions,NocturneWakeupStop *);
#endif

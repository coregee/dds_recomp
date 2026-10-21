#ifndef NOCTURNE_BATTLE_ALARM_REGISTRATION_H
#define NOCTURNE_BATTLE_ALARM_REGISTRATION_H
#include "battle_wakeup_kernel.h"
/* Complete shipped 168-word native entry80076440, not a syscall reply.
 * Incoming RA bits31..0 are the observation return boundary. On normal
 * return pc/stop.pc/stop.target are that zeroextended PC; address/bytes0.
 * Actual banks/RAM and prior partial effects remain on any other stop.
 * Callback/common/GP are stored in queue records, never invoked here.
 * The caller supplies initialized physical RAM aliasing and timer MMIO.
 * No timer ticking, interrupt delivery, CP0 exception or scheduler effects
 * are synthesized. Partial queue accesses use aligned8-byte RAM merge/RMW.
 * instructions counts attempted words including actual delay slots; sync_p
 * counts native SYNC0 value barriers (historical shared counter name).
 */
uint32_t nocturneBattleAlarmRegistration(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t max_instructions,NocturneWakeupStop *);
#endif

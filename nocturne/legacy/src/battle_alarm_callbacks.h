#ifndef NOCTURNE_BATTLE_ALARM_CALLBACKS_H
#define NOCTURNE_BATTLE_ALARM_CALLBACKS_H
#include "battle_native_flow.h"
/* Complete60-word fixed native file/CD alarm callbacks and negative veneers.
 * Enter/resume at actual machine.pc, with one actual720B bank and RAM owner.
 * A syscall yields9 BEFORE that word executes/counts; the outer router counts
 * it once and applies the actual exception. An unowned nextPC yields8 after
 * real branch/JR delay effects, target=SE32(pc). No C-stack kernel invocation,
 * callback reply, ERET, fabricated return0 or timer/interrupt delivery here.
 * All prior partial register/RAM effects persist on limit/fault/transfer.
 * SYNC0 increments the historical sync_p native barrier counter. EI applies
 * the exact EDI/EXL/ERL/KSU permission rule to EIE only, not an IRQ event.
 */
uint32_t nocturneBattleAlarmCallbacks(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t remaining_instructions,NocturneWakeupStop *);
#endif

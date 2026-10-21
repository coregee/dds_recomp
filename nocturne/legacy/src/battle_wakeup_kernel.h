#ifndef NOCTURNE_BATTLE_WAKEUP_KERNEL_H
#define NOCTURNE_BATTLE_WAKEUP_KERNEL_H
#include <stdint.h>
/* Explicit actual-bank state. No thread/result FIFO, private guest RAM or
 * supplied replies. The current diagnostic adapter binds real CP0/SA/FPUacc
 * owners alongside the shared GPR/FPR/HILO/Status/FCSR/RAM owners. */
typedef struct NocturneWakeupMachine {
 uint32_t gpr[32][4],fpr[32];
 uint64_t hi,lo,hi1,lo1;
 uint32_t sa,fcsr,fpu_acc,status,cause,epc,pc;
 uint64_t instructions,sync_p;
} NocturneWakeupMachine;
typedef struct NocturneWakeupMemory {
 void *owner;
 /* Complete initialized read/write or return0 without supplying bytes.
  * Kernel aliases/physical extents are the explicit RAM owner's obligation. */
 int (*read)(void *,uint32_t,void *,uint32_t);
 int (*write)(void *,uint32_t,const void *,uint32_t);
} NocturneWakeupMemory;
enum NocturneWakeupOutcome {
 NOCTURNE_WAKEUP_RETURNED=0, NOCTURNE_WAKEUP_SCHEDULER=1,
 NOCTURNE_WAKEUP_UNBACKED=2, NOCTURNE_WAKEUP_UNKNOWN_CODE=3,
 NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY=4, NOCTURNE_WAKEUP_FPU_DOMAIN=5,
 NOCTURNE_WAKEUP_INPUT_DOMAIN=6, NOCTURNE_WAKEUP_INSTRUCTION_LIMIT=7
};
typedef struct NocturneWakeupStop {
 uint32_t outcome,pc,address,bytes;
 uint64_t target;
} NocturneWakeupStop;
/* Execute one actual non-delay user SYSCALL51 through fixed source-version
 * vector/dispatch/wrapper/helper/context instructions. RawA0 is resolved by
 * the native <256 guard and MOVZ currentID, never by an A0==0 fixed response.
 * Successful helper paths preserve all count/queue writes and stop BEFORE
 * scheduler3940; they are not fabricated user returns. Raw CPU K0/V1/Status
 * and all native scratch/context/frame RAM changes remain observable.
 * FPUacc +/-zero transfer currently supports finite normals and signedzero;
 * unsupported FPU domains stop at the actual instruction after prior effects.
 */
uint32_t nocturneWakeupKernelSyscall51(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint32_t syscall_pc,uint64_t max_instructions,NocturneWakeupStop *);
/* Exact original 47/GetThreadId,51/WakeupThread,53/CancelWakeupThread entry
 * pairs only. The complete shared exception path and all native bank/RAM
 * effects execute; later252/50/scheduler behavior is not supplied. */
uint32_t nocturneThreadKernelSyscall(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint32_t syscall_pc,uint64_t max_instructions,NocturneWakeupStop *);
#endif

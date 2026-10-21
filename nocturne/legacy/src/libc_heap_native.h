#ifndef NOCTURNE_LIBC_HEAP_NATIVE_H
#define NOCTURNE_LIBC_HEAP_NATIVE_H
#include "battle_native_flow.h"
/* Original malloc/free/growth/sbrk and recursive heap locks. Native Create,
 * GetThreadId, Wait/Signal, EndOfHeap and scheduler operate on shared RAM.
 * Initial bins/program break are original ELF state; object/chunk addresses
 * and semaphore IDs are computed. No heap or syscall reply is supplied. */
uint32_t nocturneLibcHeapResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif

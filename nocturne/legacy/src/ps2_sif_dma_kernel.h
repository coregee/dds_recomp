#ifndef NOCTURNE_PS2_SIF_DMA_KERNEL_H
#define NOCTURNE_PS2_SIF_DMA_KERNEL_H
#include "battle_native_flow.h"
/* Original360 words:25 ring initializer plus335 complete service119 closure.
 * Native31-slot capacity, tags, rounded LQ/SQ copies, upper128 clobbers,
 * generation wrap and actual MMIO read/write order. No transfer ID supplied.
 * Memory owner must provide channel6/global DMA registers or reject access.
 * DIV is scoped to actual bounded index/LI31; BREAK7 stays an explicit
 * processor boundary if entered outside its naturally annulled path.
 * Queue submission is not DMA completion or IOP arrival. */
uint32_t nocturneSifDmaKernelResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif

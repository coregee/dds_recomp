#ifndef NOCTURNE_SOUND_THREAD_SUPPORT_NATIVE_H
#define NOCTURNE_SOUND_THREAD_SUPPORT_NATIVE_H
#include "battle_native_flow.h"
/* Complete135 original words: SREG read, thread-with-stack/memset,
 * semaphore constructor, RPC-worker entry and CreateSema veneer.
 * One raw CPU128/RAM owner. PCPYH/PCPYLD write actual full128-bit results;
 * do not replace memset with a host call or clear surrounding frame bytes.
 * Transfer8 and unexecuted-SYS9 retain real guest effects; no semaphore ID,
 * IOP-ready result or RPC response is supplied. */
uint32_t nocturneSoundThreadSupportResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif

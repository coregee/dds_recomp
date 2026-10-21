#ifndef NOCTURNE_SDK_MEMORY_CARD_SUPPORT_NATIVE_H
#define NOCTURNE_SDK_MEMORY_CARD_SUPPORT_NATIVE_H
#include "battle_native_flow.h"
/* Complete original14 BIOS PollSema words plus the actual4-word user veneer
 * and15-word RPC-busy leaf. Poll reads and decrements the real semaphore
 * count; signed-empty and invalid-ID paths return the native error.
 * The real4-word SetAlarm252 veneer also yields an unexecuted SYS.
 * Neither acquisition,alarm registration nor RPC completion is supplied. */
uint32_t nocturneSdkMemoryCardSupportResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif

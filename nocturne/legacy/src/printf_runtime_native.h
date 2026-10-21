#ifndef NOCTURNE_PRINTF_RUNTIME_NATIVE_H
#define NOCTURNE_PRINTF_RUNTIME_NATIVE_H
#include "battle_native_flow.h"
/* Whole original newlib formatter/stream algorithms on the shared machine.
 * Native guest varargs, FILE buffers, callbacks, stack and scratch banks are
 * retained. Heap/console/float helpers outside this owner remain genuine
 * transfers; no formatter, writer, allocation or console reply is supplied. */
uint32_t nocturnePrintfRuntimeResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif

#ifndef NOCTURNE_CONSOLE_NATIVE_H
#define NOCTURNE_CONSOLE_NATIVE_H
#include "battle_native_flow.h"
/* Whole original console/memchr bodies; exact CRLF/capacity/header/locking
 * effects use shared RAM. Syscall124 reaches actual dedicated1123C dispatch,
 * not its unused normal table slot. No console ID/ack/result is supplied. */
uint32_t nocturneConsoleResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif

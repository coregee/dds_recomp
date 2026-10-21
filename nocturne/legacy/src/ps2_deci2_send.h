#ifndef NOCTURNE_PS2_DECI2_SEND_H
#define NOCTURNE_PS2_DECI2_SEND_H
#include "battle_native_flow.h"
/* Actual request-slot scan/list publication, route checks and drain logic.
 * Native callbacks/user bridge/device transport outside this owner remain
 * real transfers. A queued return1 is not transmit completion or an ack. */
uint32_t nocturneDeci2SendResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *);
#endif

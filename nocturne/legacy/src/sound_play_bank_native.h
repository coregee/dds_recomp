#ifndef NOCTURNE_SOUND_PLAY_BANK_NATIVE_H
#define NOCTURNE_SOUND_PLAY_BANK_NATIVE_H
#include "battle_native_flow.h"
/* Five complete original bodies, existing identities only. Packet+4 retains
 * native caller stack storage; no padding is read from a future outcome.
 * Cache operations/TagLo require an explicit processor owner. Missing/pending
 * banks take their real external call and stop until its body is available.
 * This API supplies no resident-bank, cache, wakeup or worker result. */
typedef struct NocturneSoundBankProcessor {
 void *owner;
 int (*cache)(void *,uint32_t pc,uint32_t operation,uint32_t address);
 int (*taglo)(void *,uint32_t *value);
} NocturneSoundBankProcessor;
uint32_t nocturneSoundPlayBankResume(NocturneWakeupMachine *,const NocturneWakeupMemory *,uint64_t,NocturneWakeupStop *,const NocturneSoundBankProcessor *);
int nocturneSoundPlayBankOwns(uint32_t pc);
#endif

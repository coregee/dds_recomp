#ifndef NOCTURNE_FIELD_BGM_TRANSITION_H
#define NOCTURNE_FIELD_BGM_TRANSITION_H
#include <stdint.h>
uint64_t ps2FieldCallField_001E72F8(void);
uint64_t ps2FieldBgmFadeOut_001452F0(void);
uint64_t ps2SoundFadeOut_002C2070(uint64_t midi);
void *nocturneResolveFieldBgmTransitionAddress(uint32_t address);
/* Ordinary guest SP ownership. The caller supplies existing memory, including
 * the twelve unwritten sound packet bytes; no bytes/results are invented. */
uint32_t nocturneFieldBgmTransitionStack(void);
void nocturneFieldBgmTransitionSetStack(uint32_t sp);
#endif

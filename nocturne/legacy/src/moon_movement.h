#ifndef NOCTURNE_MOON_MOVEMENT_H
#define NOCTURNE_MOON_MOVEMENT_H
#include <stdint.h>
void evtMoonAddMove(float length);
void ps2FieldLightClearMessage(void);
extern const uint32_t *g_moonMoveLimitBits;
extern uint32_t *g_moonStepCountdown;
/* Processor condition primitive; target implementation uses C.LT.S.
 * Host proof is restricted to finite normal values and signed zero. */
uint32_t EE_MOON_COMPARE_LESS_S(uint32_t left, uint32_t right);
/* External diagnostic printf at002d4748, not recovered in this batch. */
void nocturneMoonDiagnostic(uint32_t original_format, uint64_t counter);
#endif

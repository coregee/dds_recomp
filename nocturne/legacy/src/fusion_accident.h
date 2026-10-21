#ifndef NOCTURNE_FUSION_ACCIDENT_H
#define NOCTURNE_FUSION_ACCIDENT_H
#include <stdint.h>
/* Raw guest argument slots and defined low64 V0, SLUS_209.11.
 * Names describe the PS2 bodies; the event helper is not HD's UI command. */
uint64_t ps2FusionAccidentEventDisabled_001FD3B0(uint64_t id);
uint64_t ps2FusionAccidentMetaOnly_001FE2C8(uint64_t id);
uint64_t ps2FusionAccidentCheck_001FE2F0(void);
uint64_t ps2FusionAccidentType_001FE368(void);
uint64_t ps2FusionAccidentFallback_001FE388(uint64_t excluded_id);
uint64_t ps2FusionAccidentSelect_001FE410(uint64_t excluded_id);
uint64_t ps2FusionAccidentBoost_001FE570(uint64_t unit);
/* Resolves actual declared RAM; never supplies a game-function result. */
void *nocturneResolveFusionAccidentAddress(uint32_t address);
#endif

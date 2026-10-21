#ifndef NOCTURNE_FIELD_INPUT_RELEASE_H
#define NOCTURNE_FIELD_INPUT_RELEASE_H
#include <stdint.h>
uint64_t ps2FieldGetUnitControl_001225E8(void);
uint64_t ps2FieldReleaseUnitPad_00122718(void);
uint64_t ps2ObjectSetPrimaryControl_001121D8(uint64_t object,uint64_t function);
uint64_t ps2MoverSetPrimaryControl_0010FED0(uint64_t mover,uint64_t function);
void *nocturneResolveFieldInputReleaseAddress(uint32_t address);
#endif

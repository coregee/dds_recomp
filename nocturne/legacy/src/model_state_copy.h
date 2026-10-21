#ifndef NOCTURNE_MODEL_STATE_COPY_H
#define NOCTURNE_MODEL_STATE_COPY_H
#include <stdint.h>
#ifndef NOCTURNE_STATE_COPY_BINDING_API
#define NOCTURNE_STATE_COPY_BINDING_API
#endif
void ps2ModelCopyState(uint64_t destination,uint64_t source);
NOCTURNE_STATE_COPY_BINDING_API void *nocturneResolveModelStateCopyAddress(uint32_t address);
void EE_MODEL_COPY_CPU_QUAD(unsigned gpr,const uint32_t words[4]);
uint32_t nocturneModelStateCopyOptionOutput(uint32_t destinationHeader,uint32_t sourceHeader,uint32_t *byteCount);
void nocturneModelStateCopyObserveOption(uint32_t output,uint32_t byteCount);
#endif

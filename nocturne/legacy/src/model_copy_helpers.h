#ifndef NOCTURNE_MODEL_COPY_HELPERS_H
#define NOCTURNE_MODEL_COPY_HELPERS_H
#include <stdint.h>
#ifndef NOCTURNE_COPY_HELPERS_BINDING_API
#define NOCTURNE_COPY_HELPERS_BINDING_API
#endif
void ps2ModelCopyOptionBuffer(uint64_t destination,uint64_t source);
void ps2MaterialCopyParameters(uint64_t destination,uint64_t source);
void ps2MaterialCopyListParameters(uint64_t destination,uint64_t source);
NOCTURNE_COPY_HELPERS_BINDING_API void *nocturneResolveModelCopyAddress(uint32_t address);
NOCTURNE_COPY_HELPERS_BINDING_API uint32_t nocturneModelCopyOriginalAddress(const void *host);
#if defined(NOCTURNE_MODEL_COPY_HELPERS_PROFILE)
NOCTURNE_COPY_HELPERS_BINDING_API extern uint32_t g_modelCopyHelpersActive;
#endif
#endif

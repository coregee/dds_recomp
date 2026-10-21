#ifndef NOCTURNE_DIAGNOSTIC_TRANSPORT_H
#define NOCTURNE_DIAGNOSTIC_TRANSPORT_H
#include <stdint.h>
/* Native callers discard TextSend's V0; printf preserves the formatter count. */
void ps2DiagnosticTextSend(uint64_t text);
uint64_t ps2DiagnosticPrintf(uint64_t format,...);
#if UINTPTR_MAX > UINT32_MAX
uint32_t nocturneDiagnosticFrameStart(void *frame,uint32_t bytes);
void nocturneDiagnosticFrameEnd(void);
#endif
#endif

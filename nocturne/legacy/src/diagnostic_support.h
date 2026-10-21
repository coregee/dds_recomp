#ifndef NOCTURNE_DIAGNOSTIC_SUPPORT_H
#define NOCTURNE_DIAGNOSTIC_SUPPORT_H
#include <stdint.h>
uint64_t ps2DiagnosticRpcPacketTake(uint64_t queue);
void ps2DiagnosticRpcPacketRelease(uint64_t packet);
uint64_t ps2LibcVsprintf(uint64_t output,uint64_t format,uint64_t arguments);
#endif

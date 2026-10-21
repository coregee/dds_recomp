#ifndef NOCTURNE_DIAGNOSTIC_RPC_H
#define NOCTURNE_DIAGNOSTIC_RPC_H
#include <stdint.h>
uint64_t ps2DiagnosticRpcCall(uint64_t client,uint64_t command,uint64_t mode,
 uint64_t send,uint64_t send_bytes,uint64_t receive,uint64_t receive_bytes,
 uint64_t callback,uint32_t parameter);
#endif

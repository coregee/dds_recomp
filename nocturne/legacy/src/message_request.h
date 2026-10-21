#ifndef NOCTURNE_MESSAGE_REQUEST_H
#define NOCTURNE_MESSAGE_REQUEST_H
#include <stdint.h>
uint64_t itfMesMngMessage(void);
uint64_t itfMesMngRequestMessage(uint64_t id,uint64_t message,uint64_t page);
void ps2MessageReady(uint64_t instance);
uint64_t CountLineMessage(uint64_t top,uint64_t font);
void itfMesMngSetKutiCallback(uint64_t id,uint64_t function);
uint64_t ps2MessageKutiDiagnostic(void);
void nocturneInvokeMessageKutiCallback(uint32_t entry);
#endif

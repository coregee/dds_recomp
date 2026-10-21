#ifndef NOCTURNE_NEGOTIATION_FLOW_H
#define NOCTURNE_NEGOTIATION_FLOW_H
#include <stdint.h>
uint64_t ps2NegotiationFlowQueue_0026A8A0(uint64_t context,uint64_t command);
uint64_t ps2NegotiationFlowMessage_0026A998(uint64_t context,uint64_t message,uint64_t mode,uint64_t flag);
uint64_t ps2NegotiationFlow6_22_00270110(uint64_t context);
uint64_t ps2NegotiationFlow6_24_00270300(uint64_t context);
void *nocturneResolveNegotiationFlowAddress(uint32_t address);
#endif

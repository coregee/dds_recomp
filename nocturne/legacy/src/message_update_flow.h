#ifndef NOCTURNE_MESSAGE_UPDATE_FLOW_H
#define NOCTURNE_MESSAGE_UPDATE_FLOW_H
#include <stdint.h>
void ps2MessageCalcFlow(uint64_t instance);
void ps2MessageCalcMessage(uint64_t instance);
void ps2MessageCalcSelect(uint64_t instance);
uint64_t ps2MessageSelectItem(uint64_t instance);
void ps2MessageSelectItemMove(uint64_t selection,uint64_t direction);
uint64_t ps2MessageCalcManager(void);
#endif

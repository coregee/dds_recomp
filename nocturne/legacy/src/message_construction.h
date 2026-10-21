#ifndef NOCTURNE_MESSAGE_CONSTRUCTION_H
#define NOCTURNE_MESSAGE_CONSTRUCTION_H
#include <stdint.h>
uint64_t itfMiscLinkTake(uint64_t stack);
void itfMiscLinkGive(uint64_t node,uint64_t stack);
void itfMesInitializeSpeaker(uint64_t speaker,uint64_t defaultpos);
void itfMesInitializeMessage(uint64_t message,uint64_t defaultpos);
void itfMesInitializeSelect(uint64_t select);
void itfMesInitializeWindow(uint64_t window);
void itfMesInitializeVariable(uint64_t variable);
void itfMesInitializeCurCtr(uint64_t cursor,uint64_t isdisp);
void itfMesResetWindowPara(uint64_t window,uint64_t type,uint64_t alpha);
void itfMesResolveResourceAddress(uint64_t data);
uint64_t ps2MessageGetTypeHeader2(uint64_t data);
uint64_t itfMesMngSetResourcePtr(uint64_t id,uint64_t data);
uint64_t itfMesMngInitialize(uint64_t data);
void *nocturneResolveMessageConstructionAddress(uint32_t address);
#endif

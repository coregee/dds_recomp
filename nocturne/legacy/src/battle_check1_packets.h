#ifndef NOCTURNE_BATTLE_CHECK1_PACKETS_H
#define NOCTURNE_BATTLE_CHECK1_PACKETS_H
#include <stdint.h>
uint64_t mdlGetMotionCtrlr(uint64_t model,uint64_t group);
uint64_t ps2ModelMotionLength(uint64_t model,uint64_t group);
uint64_t nbAddBadEffKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t bad);
void nbAddNumEffKoukaPacket(uint64_t start,uint64_t duration,uint64_t context,uint64_t form,uint64_t first,uint64_t second,uint64_t type);
void nbAddMojiEffKoukaPacket(uint64_t start,uint64_t duration,uint64_t context,uint64_t form,uint64_t type);
uint64_t nbMakeDeadPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t force);
uint64_t nbMakeBadDamagePacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t bad);
uint64_t nbMakeBadKaifukuPacket(uint64_t frame,uint64_t context,uint64_t form);
uint64_t nbGetDeadEventFadeTime(uint64_t event);
uint64_t nbGetDeadEventFadeOutFrame(uint64_t event);
uint64_t nbGetDeadEventFadeInFrame(uint64_t event);
uint64_t nbGetDeadEventFadeStopFrame(uint64_t event);
void nbActionQueueDeadScripts(uint64_t context);
void *nocturneResolveBattleCheck1PacketsAddress(uint32_t address);
#endif

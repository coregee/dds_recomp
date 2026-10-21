#ifndef NOCTURNE_BATTLE_ACTION_FINISH_H
#define NOCTURNE_BATTLE_ACTION_FINISH_H
#include <stdint.h>
void effBTLDelete(uint64_t effect);
void effBTLCutListRelease(uint64_t cut);
void effBTLCutDelete(uint64_t cut);
void effBTLPartDelete(uint64_t effect);
uint64_t nbActionCheckAfter(uint64_t context);
uint64_t nbActionCheckDeadScript(uint64_t context);
void nbActionSetTimeList(uint64_t context,uint64_t form,uint64_t start,uint64_t lock,uint64_t end);
void nbLinkKoukaPacket(uint64_t data,uint64_t packet);
uint64_t nbAddKoukaPacket(uint64_t data,uint64_t frame,uint64_t type,uint64_t context);
uint64_t nbAddUnitColKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t time);
uint64_t nbAddUnitAKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t time);
uint64_t nbAddReturnKoukaPacket(uint64_t frame,uint64_t context,uint64_t data,uint64_t time);
uint64_t nbMakeUnitFadeOutPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t delta,uint64_t firstTime,uint64_t secondTime);
#endif

#ifndef NOCTURNE_BATTLE_KOUKA_PACKETS_H
#define NOCTURNE_BATTLE_KOUKA_PACKETS_H
#include <stdint.h>
uint64_t nbAddHatudoEffectEndPacket(uint64_t frame,uint64_t context);
uint64_t nbAddUnitHomeColKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t time);
uint64_t nbAddUnitHomeAKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t time);
uint64_t nbAddMotionStopClearPacket(uint64_t frame,uint64_t context,uint64_t form);
uint64_t nbAddMotionKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t motion);
uint64_t nbAddDmgMotKoukaPacket(float ratio,uint64_t frame,uint64_t context,uint64_t form,uint64_t motion);
uint64_t nbAddEasyDmgMotKoukaPacket(float ratio,uint64_t frame,uint64_t context,uint64_t form);
uint64_t nbAddBadDmgMotKoukaPacket(float ratio,uint64_t frame,uint64_t context,uint64_t form,uint64_t motion);
uint64_t nbAddBadEffKaifukuPacket(uint64_t frame,uint64_t context,uint64_t form);
uint64_t nbAddHpMpKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t time);
uint64_t nbAddBadStatKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t time);
uint64_t nbAddBadMotKaifukuPacket(uint64_t frame,uint64_t context,uint64_t form);
uint64_t nbAddDeadPcmPacket(uint64_t frame,uint64_t context,uint64_t form);
uint64_t nbAddSePacket(uint64_t frame,uint64_t context,uint64_t sound);
uint64_t nbAddSkillNamePacket(uint64_t frame,uint64_t context,uint64_t skill);
uint64_t nbAddFormOnOffPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags);
uint64_t nbAddFlyKoukaPacket(uint64_t frame,uint64_t context,uint64_t form);
uint64_t nbAddDeadEventKoukaPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t value);
uint64_t nbAddFadeOutKoukaPacket(uint64_t frame,uint64_t context,uint64_t value,uint64_t time);
uint64_t nbAddFadeInKoukaPacket(uint64_t frame,uint64_t context,uint64_t value,uint64_t time);
uint64_t nbAddPadShockPacket(uint64_t frame,uint64_t context,uint64_t first,uint64_t second,uint64_t time);
uint64_t nbAddPanelStockFadeOutPacket(uint64_t frame,uint64_t context);
uint64_t nbAddPanelStockEndPacket(uint64_t frame,uint64_t context);
uint64_t nbMakeUnitFadeInPacket(uint64_t frame,uint64_t context,uint64_t form,uint64_t flags,uint64_t delta,uint64_t firstTime,uint64_t secondTime);
uint64_t nbMakeFlyBadPacket(uint64_t frame,uint64_t context,uint64_t form);
void nbOnOffKoukaPacketFlag(uint64_t kind,uint64_t mask,uint64_t enabled);
uint64_t nbCheckSePacket(uint64_t frame,uint64_t sound,uint64_t window);
void *nocturneResolveBattleKoukaPacketsAddress(uint32_t address);
#endif

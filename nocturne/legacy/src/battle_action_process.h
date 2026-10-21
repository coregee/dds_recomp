#ifndef NOCTURNE_BATTLE_ACTION_PROCESS_H
#define NOCTURNE_BATTLE_ACTION_PROCESS_H
#include <stdint.h>
uint64_t nbActionProcess1(uint64_t process);
void ps2BattleActionEnterWait(uint64_t context);
void ps2BattleActionEnterCheck3(uint64_t context);
void ps2BattleActionEnterAfter(uint64_t context);
uint64_t nbActionCheckWait(uint64_t context);
void nbActionSetEnd(uint64_t context);
uint64_t ps2BattleActionCheckEnd(uint64_t context);
uint64_t nbGetKoukaProcessData(void);
uint64_t ps2BattleCountContextKouka(uint64_t context);
uint64_t nbActionCheckCheck3(uint64_t context);
uint64_t ps2MovieCheckAdpcmFlag(void);
uint64_t ps2MovieStopAdpcm(void);
uint64_t nocturneInvokeBattleActionUpdate(uint32_t target,uint64_t context);
#endif

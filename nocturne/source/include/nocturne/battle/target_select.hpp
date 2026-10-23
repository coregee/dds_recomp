// Choosing a target (original unit: nbTarSelProcess): the cursor over the
// selectable formation slots, moved with the pad, and its animation. The
// record is TargetSelectData (process.hpp).
//
// Names are the HD remaster's.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

int32_t nbGetTarSelStat();                 // 1 choosing, 0 chosen, 2 cancelled
void nbSetTarSelStat(int32_t stat);
void nbSetTarSelJyokyoTime(int32_t time);
void AnimeTargetCursor(TargetSelectData& t);
void SetCursor(TargetSelectData& t);
bool nbSetTargetProcess(ActionProcessData& act, int32_t partyindex, int32_t ctype, int32_t crule, int32_t carea);
bool CheckFriend(const TargetSelectData& t, int32_t formindex);
bool CheckEnemy(const TargetSelectData& t, int32_t formindex);
void UpdateSelect(TargetSelectData& t);
void OnOffTargetCursor(TargetSelectData& t);
void DispTargetHelp(TargetSelectData& t);
void MemoryCommand(TargetSelectData& t);
void CursorSelect(TargetSelectData& t);
void CursorSelectAuto(TargetSelectData& t);
int32_t nbTarSelProcess1(uint32_t process);
void nbTarSelShutdown(uint32_t process);
uint32_t InitTarSelProcessData(MainProcessData& data);   // the record's address
void nbInitTarSelProcess(MainProcessData& data);

void nbPlaySe(int32_t se);                  // nbSound: a battle sound
int32_t dds3CheckConfigBit(int32_t type);   // dds3ConfigMain: an option

} // namespace nocturne::nb

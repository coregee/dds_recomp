// Choosing a target (original unit: nbTarSelProcess): the cursor over the
// selectable formation slots, moved with the pad, and its animation. The
// record is TargetSelectData (process.hpp).
//
// Names are the HD remaster's.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

int32_t targetCursorState();               // 1 choosing, 0 chosen, 2 cancelled
void setTargetCursorState(int32_t stat);
void setTargetNameDelay(int32_t time);
void animateTargetCursor(TargetCursor& t);
void placeTargetCursor(TargetCursor& t);
bool startTargetCursor(ActionProcessData& act, int32_t partyindex, int32_t ctype, int32_t crule, int32_t carea);
bool onActorSide(const TargetCursor& t, int32_t formindex);
bool onOtherSide(const TargetCursor& t, int32_t formindex);
void markTargets(TargetCursor& t);
void showTargetCursors(TargetCursor& t);
void showTargetName(TargetCursor& t);
void rememberTarget(TargetCursor& t);
void readTargetPad(TargetCursor& t);
void chooseTargetAutomatically(TargetCursor& t);
int32_t runTargetCursor(uint32_t process);
void shutdownTargetCursor(uint32_t process);
uint32_t newTargetCursor(MainProcessData& data);         // the record's address
void startTargetCursorProcess(MainProcessData& data);

void playBattleSound(int32_t se);           // nbSound: a battle sound
int32_t configOption(int32_t type);         // dds3ConfigMain: an option
int32_t configBit(int32_t type, uint32_t config);   // 0x29BA80: ... read from a config word

} // namespace nocturne::nb

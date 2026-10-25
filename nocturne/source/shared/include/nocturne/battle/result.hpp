// The battle's result (original unit: nbResultProcess): the spoils and the
// experience the party earns.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"

namespace nocturne::nb {

// GetAddExp: `exp`, but no more than takes unit `index` (in the global work)
// to one short of its experience for level 256.
int32_t cappedExp(int32_t index, int32_t exp);

// nbResultAddExp: the items and Macca won, and each living unit's
// experience: the party's in full, the stock's by version.
void grantSpoils(MainProcessData& main);

// ---- the result screen's process ----

// nbInitResultProcess: the result process starts as the battle's child.
void startResultProcess(MainProcessData& data);
// nbResultProcess1: its first frame: the battle's other processes stop, the
// experience is counted and the screen loads; the next frame's step.
uint32_t firstResultStep(uint32_t process);
// nbResultShutdown
void shutdownResult(uint32_t process);
// ShutdownProcess (tentative): the battle's helper processes stopped.
void stopBattleProcesses();
// ClearStage (tentative): the units let go and the parties marked gone.
void clearStage();
// nbResultTexDel: the screen's three textures released.
void releaseResultTextures();
// nbResultLvupAnmAdd: a level-up animation (one of 64 slots).
void addLevelUpAnimation(int32_t a, int32_t b);
// nbResultFinWaitChk: the frames waited since the rows finished (to 60).
int32_t finishWait();

// [version] A stock demon's share of `exp` (false: none)
//.
bool stockExpShare(const UnitWork& unit, int32_t& exp);

} // namespace nocturne::nb

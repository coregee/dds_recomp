// The battle camera (original unit: nbCameraProcess), as far as rewritten:
// asking for a camera state.
//
// Names are the HD remaster's.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/ee/float.hpp"

namespace nocturne::nb {

// nbCamera_t: the current camera (nbCameraCurrent, 0x320E40). Only the
// state fields are confirmed; the rest follows the HD order.
struct Camera {
    ee::Float target[4], direction[4];   // tentative
    ee::Float distance, fovy;            // tentative
    uint32_t state_change;               // the state asked for
    uint32_t state;                      // the state's progress (0: starting)
};
static_assert(offsetof(Camera, state_change) == 0x28 && offsetof(Camera, state) == 0x2c);

// nbCameraStateTable_t: a camera state (nbCameraStateTable, 0x320C50).
struct CameraStateTable {
    uint32_t pDebugString;
    uint32_t Init, Calc;    // original code
    int32_t rep;            // nonzero: asking again restarts it
};
static_assert(sizeof(CameraStateTable) == 16);

// The camera states, named by the table's debug strings. Only ENEMY_BAD
// restarts when asked for again.
enum CameraState : uint16_t {
    kCameraWait, kCameraStart, kCameraCommandRoot, kCameraCommandBad, kCameraCommandTargetSelect,
    kCameraSkillAttack, kCameraSkillStart, kCameraSkillCut1, kCameraSkillCut2, kCameraSkillCut3,
    kCameraSkillEnd, kCameraPressTurn, kCameraSummon, kCameraNegoBougai, kCameraNegoTaizi,
    kCameraTalkTarget, kCameraTalkBuff, kCameraTalkEnd, kCameraGameOver, kCameraResult,
    kCameraPlayerSide, kCameraEnemySide, kCameraEnd, kCameraEvent, kCameraEveTarget,
    kCameraEnemyBad, kCameraScript1Shot, kCameraScriptBougai, kCameraScriptFix, kCameraDebugAllShot,
};

void setCameraState(uint16_t state);
void cameraOnPair(const Formation& from, const Formation& to);
// The talks' camera, from the unit acting (the skill's invoker) toward:
void cameraOnObstructor(const Formation& target);    // nbCameraSetBougai: one who breaks in (NEGO_BOUGAI)
void cameraOnTalkTarget(const Formation& target);    // nbCameraSetTarget: the demon talked to (NEGO_TARGET)
void cameraOnHelper(const Formation& helper, const Formation& a, const Formation& b);   // nbCameraSetHojo: a helper, on two others
void cameraOnEventTarget(const Formation& target);   // (0x1B1888) an event's (EVE_TARGET)

} // namespace nocturne::nb

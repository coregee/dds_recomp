// Skill errors (original unit: nbAction): Hardtype's own (shared/src/battle/skill_error.cpp has the rest).
#include "nocturne/battle/skill_error.hpp"

namespace nocturne::nb {

// nbCheckBattleSkillError3 @ 0x00290780 (and 0x2FED80): fourteen more skills
// are refused when nothing they change can move. (A fifteenth, 0xE4, is
// compared with a register its caller leaves holding a float constant's
// upper half, so it never matches.)
bool versionBuffSkill(int32_t nskill)
{
    switch (nskill) {
    case 0x3a: case 0x80: case 0x81: case 0x82: case 0x84: case 0x85: case 0x89:
    case 0x9c: case 0xf4: case 0x106: case 0x10b: case 0x10c: case 0x11b: case 0x11d:
        return true;
    default:
        return false;
    }
}

} // namespace nocturne::nb

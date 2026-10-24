// Choosing a target (original unit: nbTarSelProcess): the cursor over the
// selectable formation slots, moved with the pad, and its animation.
// Rewritten from the original instructions; drawing the cursor is not
// rewritten yet.
#include "nocturne/battle/target_select.hpp"

#include <cstring>

#include "nocturne/battle/action.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/battle/pad.hpp"
#include "nocturne/battle/targeting.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kTarSelName = 0x005442b8;   // "nb_tarsel"

// The cursor's animation keyframes (5 frames apart, 30 frames a loop).
constexpr uint32_t kAlphaA = 0x005442c8;       // int32[7]
constexpr uint32_t kScaleA = 0x005442e8;       // float[7]
constexpr uint32_t kAlphaB = 0x00544308;       // int32[7]
constexpr uint32_t kScaleB = 0x00544328;       // float[7]

// Left / right step through a side's targets, up / down switch sides.
using pad::pressed;
using pad::repeating;
constexpr pad::Button kConfirm = pad::kConfirm, kCancel = pad::kCancel;
constexpr pad::Button kPrevious = pad::kLeft, kNext = pad::kRight, kSidePrevious = pad::kUp, kSideNext = pad::kDown;

constexpr uint32_t kCursorShown = 8;   // Formation::anime: the target cursor is on the slot (tentative)

} // namespace

// ---- the state ------------------------------------------------------------------------------

// nbGetTarSelStat @ 0x0025D6B8: 1 choosing, 0 chosen, 2 cancelled.
int32_t targetCursorState() { return targetSelectData().stat; }

// nbSetTarSelStat @ 0x0025D6D8
void setTargetCursorState(int32_t stat) { targetSelectData().stat = static_cast<uint8_t>(stat); }

// nbSetTarSelJyokyoTime @ 0x0025D700: frames before the target's name shows.
void setTargetNameDelay(int32_t time) { targetSelectData().nameDelay = time; }

// AnimeTargetCursor @ 0x0025D728: the cursor's two rings pulse, their alpha
// and scale moving between keyframes 5 frames apart over a 30-frame loop.
void animateTargetCursor(TargetCursor& t)
{
    if (++t.time >= 30)
        t.time = 0;
    const int32_t i = t.time / 5;
    const ee::Float along = ee::Float::fromInt(t.time % 5) / ee::Float::fromInt(5);
    const ee::Float back = ee::Float::fromInt(1) - along;
    auto lerp = [&](ee::Float a, ee::Float b) { return a * back + b * along; };
    const int32_t* alphaA = guest::table<const int32_t>(kAlphaA);
    const int32_t* alphaB = guest::table<const int32_t>(kAlphaB);
    const uint32_t* scaleA = guest::table<const uint32_t>(kScaleA);
    const uint32_t* scaleB = guest::table<const uint32_t>(kScaleB);
    t.alpha_a = lerp(ee::Float::fromInt(alphaA[i]), ee::Float::fromInt(alphaA[i + 1])).toInt();
    t.alpha_b = lerp(ee::Float::fromInt(alphaB[i]), ee::Float::fromInt(alphaB[i + 1])).toInt();
    t.scale_b = lerp(ee::Float::fromBits(scaleB[i]), ee::Float::fromBits(scaleB[i + 1]));
    t.scale_a = lerp(ee::Float::fromBits(scaleA[i]), ee::Float::fromBits(scaleA[i + 1]));
}

// SetCursor @ 0x0025DE40: on the actor's side if it has targets, else the
// other; on the unit's last target when the cursor-memory option is on (or
// in an auto battle).
void placeTargetCursor(TargetCursor& t)
{
    t.nowcarea = t.friendcnt >= 1 ? 1 : 2;
    t.nowno = 0;
    MainProcessData& main = *t.data;
    const UnitWork& unit = *GetUnitWorkPointer(main, main.party[t.partyindex]);
    int32_t form = unit.prevtform;
    int16_t area = unit.prevtarea;
    if (t.act && !configOption(1) && !(t.act->stat & 0x80)) {
        area = -1;
        form = -1;
    }
    const int8_t* list;
    int8_t count;
    if (area == 1) {
        if (t.friendcnt <= 0)
            return;
        t.nowcarea = 1;
        list = t.friendno;
        count = t.friendcnt;
    } else if (area == 2) {
        if (t.enemycnt <= 0)
            return;
        t.nowcarea = 2;
        list = t.enemyno;
        count = t.enemycnt;
    } else {
        return;
    }
    for (int8_t i = 0; i < count; ++i) {
        if (list[i] == form) {
            t.nowno = i;
            return;
        }
    }
}

// nbSetTargetProcess @ 0x0025DFA0: starts choosing among the targets the
// command allows; false when there are none.
bool startTargetCursor(ActionProcessData& act, int32_t partyindex, int32_t ctype, int32_t crule, int32_t carea)
{
    TargetCursor& t = targetSelectData();
    if (!markTargetable(partyindex, ctype, crule, carea))
        return false;
    t.alpha_b = 0x80;
    t.scale_b = ee::Float::fromInt(1);
    t.alpha_a = 0x80;
    t.scale_a = ee::Float::fromInt(1);
    t.act.address = guest::addressOf(&act);
    t.partyindex = static_cast<int16_t>(partyindex);
    t.ctype = static_cast<int8_t>(ctype);
    t.crule = static_cast<uint8_t>(crule);
    t.carea = static_cast<uint8_t>(carea);
    t.nameDelay = 0;
    t.time = 0;
    placeTargetCursor(t);
    markTargets(t);
    t.stat = 1;
    return true;
}

// CheckFriend @ 0x0025E070 / CheckEnemy @ 0x0025E0B8: whether a slot is on
// the actor's side (0..3, or 4..13 when the sides are swapped) or the other.
bool onActorSide(const TargetCursor& t, int32_t formindex)
{
    if (!(t.data->stat & BattleStat::InitiativeRolled))
        return formindex <= 3;
    return static_cast<uint32_t>(formindex - 4) < 10;
}

// CheckEnemy @ 0x0025E0B8
bool onOtherSide(const TargetCursor& t, int32_t formindex)
{
    if (!(t.data->stat & BattleStat::InitiativeRolled))
        return static_cast<uint32_t>(formindex - 4) < 10;
    return formindex < 4;
}

// UpdateSelect @ 0x0025E100: marks the targets: the slot under the cursor
// (single targets), the cursor's side (groups), or everyone.
void markTargets(TargetCursor& t)
{
    for (int32_t f = 0; f < 16; ++f) {
        Formation& form = t.data->form[f];
        const uint32_t stat = form.stat;
        form.stat = stat & ~FormationStat::Selected;
        if (!(stat & FormationStat::Selectable))
            continue;
        bool selected = false;
        switch (t.ctype) {
        case 0: {
            const int8_t* list = t.nowcarea == 1 ? t.friendno : t.nowcarea == 2 ? t.enemyno : nullptr;
            if (list && list[t.nowno] == f) {
                t.nowform = static_cast<int8_t>(f);
                selected = true;
            }
            break;
        }
        case 1:
            if (t.nowcarea == 1)
                selected = onActorSide(t, f);
            else if (t.nowcarea == 2)
                selected = onOtherSide(t, f);
            break;
        case 2:
            selected = true;
            break;
        default:
            break;
        }
        if (selected)
            form.stat |= FormationStat::Selected;
    }
}

// OnOffTargetCursor @ 0x0025E278: the cursor shows on the marked slots while choosing.
void showTargetCursors(TargetCursor& t)
{
    for (int32_t f = 0; f < 16; ++f) {
        Formation& form = t.data->form[f];
        const bool on = t.stat == 1 && (form.stat & FormationStat::Selected);
        if (on)
            form.anime |= kCursorShown;
        else
            form.anime &= ~kCursorShown;
    }
}

// DispTargetHelp @ 0x0025E300: the single target's name once the delay
// (jyokyotime) has run out.
void showTargetName(TargetCursor& t)
{
    int32_t f = 0;
    bool found = false;
    if (t.stat == 1 && t.ctype == 0) {
        for (; f < 16; ++f) {
            if (t.data->form[f].anime & kCursorShown) {
                found = true;
                break;
            }
        }
    }
    if (found && t.nameDelay == 0) {
        if (const UnitWork* unit = GetUnitWorkFromFormindex(f))
            showDevilName(unit->id);
    }
    if (t.nameDelay > 0)
        --t.nameDelay;
}

// MemoryCommand @ 0x0025E3F8: the unit's chosen target, remembered.
void rememberTarget(TargetCursor& t)
{
    MainProcessData& main = *t.data;
    UnitWork& unit = *GetUnitWorkPointer(main, main.party[t.partyindex]);
    unit.nowtarea = t.nowcarea;
    unit.nowtform = t.nowform;
}

// CursorSelect @ 0x0025E448: the pad moves the cursor. Next / previous step
// through the side's targets (a fresh press wraps around, a held one stops
// at the ends); side next / previous switch sides, and step like next /
// previous when only one side has targets. Confirm chooses, cancel backs
// out (sound 10). Not during an event battle's script (BattleStat 0x200000).
void readTargetPad(TargetCursor& t)
{
    if ((t.data->stat & 0x200000) || t.stat != 1)
        return;
    if (repeating(kConfirm)) {
        rememberTarget(t);
        t.stat = 0;
        return;
    }
    if (pressed(kCancel)) {
        t.stat = 2;
        playBattleSound(10);
    }
    if (t.ctype == 2)
        return;
    const uint8_t side = t.nowcarea;
    const int32_t count = side == 1 ? t.friendcnt : side == 2 ? t.enemycnt : 0;
    const bool bothSides = t.friendcnt > 0 && t.enemycnt > 0;
    bool moved = false;
    if (count >= 2) {
        // next
        if ((pressed(kNext) || (pressed(kSideNext) && !bothSides)) && t.nowno == count - 1) {
            t.nowno = 0;
            moved = true;
        } else if ((repeating(kNext) || (repeating(kSideNext) && !bothSides)) && t.nowno < count - 1) {
            ++t.nowno;
            moved = true;
        }
        // previous
        if ((pressed(kPrevious) || (pressed(kSidePrevious) && !bothSides)) && t.nowno == 0) {
            t.nowno = static_cast<int8_t>(count - 1);
            moved = true;
        } else if ((repeating(kPrevious) || (repeating(kSidePrevious) && !bothSides)) && t.nowno > 0) {
            --t.nowno;
            moved = true;
        }
    }
    if (pressed(kSidePrevious) || pressed(kSideNext)) {
        if (side == 1 && t.enemycnt > 0) {
            t.nowno = 0;
            t.nowcarea = 2;
            moved = true;
        } else if (side == 2 && t.friendcnt > 0) {
            t.nowcarea = 1;
            moved = true;
            t.nowno = 0;
        }
    }
    if (moved) {
        markTargets(t);
        playBattleSound(3);
        t.nameDelay = 0;
    }
}

// CursorSelectAuto @ 0x0025E6E0: an auto battle takes the cursor's target.
void chooseTargetAutomatically(TargetCursor& t)
{
    if (t.stat == 1) {
        rememberTarget(t);
        t.stat = 0;
    }
}

// nbTarSelProcess1 @ 0x0025E720: each frame. A target just chosen still
// shows its cursor this frame.
int32_t runTargetCursor(uint32_t process)
{
    TargetCursor& t = *guest::table<TargetCursor>(dds3::GetProcessData(process));
    bool chosenNow = false;
    if (t.act && (t.act->stat & 0x80)) {
        chooseTargetAutomatically(t);
    } else if (t.stat == 1) {
        readTargetPad(t);
        if (t.stat == 0) {
            t.stat = 1;
            chosenNow = true;
        }
    }
    animateTargetCursor(t);
    showTargetCursors(t);
    showTargetName(t);
    if (chosenNow)
        t.stat = 0;
    return 0;
}

// nbTarSelShutdown @ 0x0025E7D8
void shutdownTargetCursor(uint32_t process)
{
    const uint32_t data = dds3::GetProcessData(process);
    guest::table<TargetCursor>(data)->data->TargetCursorProcessID = 0;
    mem::PoolRelease(data);
}

// InitTarSelProcessData @ 0x0025E800
uint32_t newTargetCursor(MainProcessData& data)
{
    const uint32_t address = mem::PoolAllocate(sizeof(TargetCursor));
    std::memset(guest::table<uint8_t>(address), 0, sizeof(TargetCursor));
    TargetCursor& t = *guest::table<TargetCursor>(address);
    t.act.address = 0;
    t.data.address = guest::addressOf(&data);
    t.alpha_b = 0x80;
    t.scale_b = ee::Float::fromInt(1);
    t.alpha_a = 0x80;
    t.scale_a = ee::Float::fromInt(1);
    t.stat = 0;
    return address;
}

// nbInitTarSelProcess @ 0x0025E870: the process ("nb_tarsel"), a child of the battle.
void startTargetCursorProcess(MainProcessData& data)
{
    const uint32_t t = newTargetCursor(data);
    const uint32_t process = dds3::StartProcess(kTarSelName, 0x3f9, 1, 1, 0x0025e720, 0x0025e7d8, t);
    dds3::LinkProcess(data.MainProcessID, process);
    data.TargetCursorProcessID = process;
}

// ---- around it ----------------------------------------------------------------------------

// nbPlaySe @ 0x0028D090 (nbSound): a battle sound at full volume, centred.
void playBattleSound(int32_t se) { snd::Play(se, 0x7f, 0x3f); }

namespace {

// 0x0029BA80 (no HD name): one bit of a config word; type 0 is inverted,
// 5 always on, others unknown (-1).
int32_t configBit(int32_t type, uint32_t config)
{
    switch (type) {
    case 0: return static_cast<int32_t>(((static_cast<int32_t>(config) >> 1) ^ 1) & 1);
    case 1: return static_cast<int32_t>(config & 4);
    case 2: return static_cast<int32_t>(config & 8);
    case 5: return 1;
    default: return -1;
    }
}

} // namespace

// dds3CheckConfigBit @ 0x0029BAE0: the game's options (type 1: the target
// cursor remembers the last target, tentative).
int32_t configOption(int32_t type) { return configBit(type, dat::globalWork().config); }

} // namespace nocturne::nb

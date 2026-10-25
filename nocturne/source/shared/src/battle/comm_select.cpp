// Choosing a command (original unit: nbCommSelProcess): the lists of what a
// unit can do, the cursor over them and what it chose. Drawing the menu
// (the Disp* functions and nbCommSelProcess1) is still the original's.
// Rewritten from the original instructions.
#include "nocturne/battle/comm_select.hpp"

#include <algorithm>
#include <cstring>

#include "nocturne/address.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/pad.hpp"
#include "nocturne/battle/target_select.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/external.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kCommSelName = addr(0x005441a8);   // "nb_commsel"
constexpr uint32_t kListRows = addr(0x00544190);      // int32[6]: rows each tab shows

// Talk skills (from 0x180) have a record of 0x68 bytes from 0x3E1338 whose
// first word is the kind of talk; kinds 0..6 go in the menu. (The HD
// remaster keeps it as a table of its own; its name is unknown.)
constexpr uint32_t kTalkSkills = addr(0x003e1338);
uint32_t talkKind(int32_t skill) { return guest::table<const uint32_t>(kTalkSkills + 0x68u * static_cast<uint32_t>(skill - 0x180))[0]; }

constexpr uint32_t kHelpPanelHidden = 0xc0e;    // event bit: the menu's help panel off

// MainProcessData::stat bits read here.
constexpr uint32_t kStatNoBossSkills = BattleStat::BossBattle;   // skills and items with flag 1 can't be used
constexpr uint32_t kStatFlag4 = 0x4;                             // ... with skill flag 2 / item flag 8 (tentative)
constexpr uint32_t kStatEventScript = 0x200000;                  // the battle's script has the pad
constexpr uint32_t kStatDebugAllSkills = 0x4000000;              // every skill in the menu

constexpr uint32_t kActAuto = 0x80;   // ActionProcessData::stat: the unit acts on its own

using pad::pressed;
using pad::repeating;

void add(CommandMenu& d, int32_t tab, uint16_t entry, int8_t disable)
{
    int32_t& count = d.counts[tab];
    d.entries[tab][count] = entry;
    d.unavailable[tab][count] = disable;
    ++count;
}

int32_t& cursorOf(CommandMenu& d) { return d.nowcursor[d.tab]; }
uint16_t entryOf(const CommandMenu& d) { return d.entries[d.tab][d.nowcursor[d.tab]]; }

} // namespace

// GetCommSelProcessData @ 0x00259CF8
CommandMenu& commandMenu()
{
    return *guest::table<CommandMenu>(dds3::GetProcessData(dds3::SearchProcessName(kCommSelName)));
}

// GetCommListCnt @ 0x00259C90: 4 rows, the summon list 3 (cnt, 2 until it grows).
int32_t visibleRows(const CommandMenu& d, int32_t tab)
{
    return tab == kTabSummon ? d.cnt : guest::table<const int32_t>(kListRows)[tab];
}

// AnimeCommandList @ 0x0025B408: a frame of the menu's animations: the help
// panel fading in (0x20 a frame) or out (0x15), the menu fading in (0x14)
// or out (0xC), sliding in (half the way each frame) and the summon list
// growing (60% of what's left, at least 0.01).
void animateCommandMenu(CommandMenu& d)
{
    uint32_t flags = d.animation;
    if (flags & CommandMenuAnimation::Help) {
        if (d.helpAlpha < 0x80)
            d.helpAlpha = std::min(d.helpAlpha + 0x20, 0x80);
    } else if (d.helpAlpha > 0) {
        d.helpAlpha = std::max(d.helpAlpha - 0x15, 0);
    }
    if (flags & CommandMenuAnimation::FadeIn) {
        if (d.alpha == 0x80)
            d.animation = flags &= ~CommandMenuAnimation::FadeIn;
        else
            d.alpha = std::min(d.alpha + 0x14, 0x80);
    }
    if (flags & CommandMenuAnimation::FadeOut) {
        if (d.alpha == 0)
            d.animation = flags &= ~CommandMenuAnimation::FadeOut;
        else
            d.alpha = std::max(d.alpha - 0xc, 0);
    }
    if (flags & CommandMenuAnimation::Slide) {
        if (d.ox == 0) {
            d.animation = flags &= ~CommandMenuAnimation::Slide;
        } else {
            int32_t step = (ee::Float::fromInt(d.ox) * ee::Float::fromBits(0x3f000000)).toInt();   // x 0.5
            if (step == 0)
                step = -1;
            d.ox -= step;
        }
    }
    if (flags & CommandMenuAnimation::Grow) {
        const ee::Float least = guest::table<const ee::Float>(addr(0x0054e500))[0];   // 0.01
        const ee::Float rate = guest::table<const ee::Float>(addr(0x0054e504))[0];    // 0.6
        const ee::Float ritu = d.summonGrow;
        if (ritu.abs() < least) {
            d.summonGrow = ee::Float::fromInt(0);
            d.animation = flags & ~CommandMenuAnimation::Grow;
            return;
        }
        ee::Float step = ritu * rate;
        if (step < least)
            step = least;
        d.summonGrow = ritu - step;
        if (d.summonGrow < ee::Float::fromBits(0))
            d.summonGrow = ee::Float::fromBits(0);
    }
}

// CheckSelectError @ 0x0025C190: the tab is empty, or its entry has a
// reason it can't be chosen.
bool entryUnavailable(const CommandMenu& d)
{
    if (d.counts[d.tab] == 0)
        return true;
    return d.unavailable[d.tab][d.nowcursor[d.tab]] > 0;
}

// MemoryCommand @ 0x0025C1D8: the entry under the cursor becomes the
// unit's command (UnitWork::nowcommand: 0 attack, 1 skill, 2 escape, 3
// pass, 4 talk, 5 item, 6 summon, 7 dismiss) and its index.
void commitCommand(CommandMenu& d)
{
    UnitWork& unit = *GetUnitWorkPointer(*d.data, *d.my);
    const uint16_t entry = entryOf(d);
    int16_t command;
    switch (d.tab) {
    case kTabCommand:
    case kTabDismiss:
    case kTabEscape:
        switch (entry) {
        case kEntryAttack:
            unit.nowindex = 0;
            unit.nowcommand = 0;
            return;
        case kEntryEscape: command = 2; unit.nowindex = 0; break;
        case kEntryPass: command = 3; unit.nowindex = 0; break;
        case kEntryDismiss: command = 7; unit.nowindex = 0; break;
        default: command = 1; unit.nowindex = entry; break;
        }
        break;
    case kTabTalk:
        if (entry == kEntryTalk) {
            unit.nowindex = 0x180;
            unit.nowcommand = 4;
            return;
        }
        command = 4;
        unit.nowindex = entry;
        break;
    case kTabItem: command = 5; unit.nowindex = entry; break;
    case kTabSummon: command = 6; unit.nowindex = entry; break;
    default: return;
    }
    unit.nowcommand = command;
}

// GetNextCommType @ 0x0025C308: the next tab to the left or right with
// anything in it, wrapping around (after six tries, wherever it got to).
int32_t nextTab(const CommandMenu& d, bool right)
{
    int32_t tab = d.tab;
    for (int32_t tries = 0; tries < kCommandTabs; ++tries) {
        tab = (tab + (right ? 1 : kCommandTabs - 1)) % kCommandTabs;
        if (d.counts[tab] > 0)
            break;
    }
    return tab;
}

// SelectCommandList @ 0x0025C368: the pad on the menu. Up / down move the
// cursor (a fresh press wraps around) and scroll the list; on the summon
// list's top or second row they first grow it to three rows. Left / right
// change tabs (a held button stops at the ends). Confirm chooses an entry
// that can be chosen (sound 13 if not); cancel goes back to the first
// entry of the first tab; Pass chooses Pass at once; the help button turns
// the help panel on or off. Moves play sound 4, cancel 10, the others 8.
// Not while the battle's script has the pad.
void readCommandPad(CommandMenu& d)
{
    if (d.data->stat & kStatEventScript)
        return;
    int32_t se = -1;
    const bool up = pressed(pad::kUp) || repeating(pad::kUp);
    const bool down = pressed(pad::kDown) || repeating(pad::kDown);
    if (d.tab == kTabSummon && (up || down) && d.cnt == 2) {
        const int32_t row = d.nowcursor[kTabSummon] - d.nowlisty[kTabSummon];
        if ((up && row == 0) || (down && row == 1)) {
            d.cnt = 3;
            d.animation |= CommandMenuAnimation::Grow;
        }
    }
    if (d.animation & CommandMenuAnimation::Grow)
        return;

    const int32_t tab = d.tab;
    const int32_t rows = visibleRows(d, tab);
    const int32_t count = d.counts[tab];
    int32_t cursor = d.nowcursor[tab], top = d.nowlisty[tab];
    if (count >= 2) {
        if (repeating(pad::kUp)) {
            if (cursor == 0) {
                if (pressed(pad::kUp)) {   // around to the bottom
                    cursor = count - 1;
                    top = std::max(count - rows, 0);
                    se = 4;
                }
            } else {
                const bool scroll = cursor <= top + 1 && rows >= 4;
                --cursor;
                se = 4;
                if (scroll)
                    top = std::max(top - 1, 0);
                else if (cursor < top)
                    --top;
            }
        }
        if (repeating(pad::kDown)) {
            if (cursor == count - 1) {
                if (pressed(pad::kDown)) {   // around to the top
                    cursor = 0;
                    top = 0;
                    se = 4;
                }
            } else {
                const int32_t bottom = top + rows;
                const bool scroll = cursor >= bottom - 2 && rows >= 4;
                ++cursor;
                se = 4;
                if (scroll) {
                    ++top;
                    if (top + rows > count)
                        top = count - rows;
                } else if (cursor >= bottom) {
                    ++top;
                }
            }
        }
        d.nowcursor[tab] = cursor;
        d.nowlisty[tab] = top;
        d.counts[tab] = count;
    }

    GetUnitWorkPointer(*d.data, *d.my);
    if (repeating(pad::kLeft)) {
        const int32_t next = nextTab(d, false);
        if (next != d.tab && (pressed(pad::kLeft) || next < d.tab)) {
            d.tab = static_cast<uint8_t>(next);
            se = 4;
        }
    }
    if (repeating(pad::kRight)) {
        const int32_t next = nextTab(d, true);
        if (next != d.tab && (pressed(pad::kRight) || next > d.tab)) {
            d.tab = static_cast<uint8_t>(next);
            se = 4;
        }
    }

    if (repeating(pad::kConfirm)) {
        if (!entryUnavailable(d)) {
            d.state = 3;
            commitCommand(d);
        } else if (pressed(pad::kConfirm)) {
            se = 13;
        }
    } else if (pressed(pad::kCancel)) {
        if (d.tab != kTabCommand || d.nowcursor[kTabCommand] != 0 || d.nowlisty[kTabCommand] != 0) {
            d.tab = kTabCommand;
            d.nowcursor[kTabCommand] = 0;
            d.nowlisty[kTabCommand] = 0;
            se = 10;
        }
    } else if (pressed(pad::kPass)) {
        d.tab = kTabCommand;
        for (int32_t i = 0; i < d.counts[kTabCommand]; ++i) {
            if (d.entries[kTabCommand][i] == kEntryPass) {
                d.nowcursor[kTabCommand] = i;
                break;
            }
        }
        d.state = 3;
        commitCommand(d);
        se = 8;
    }

    if (pressed(pad::kHelpToggle)) {
        if (evt::BitCheck(kHelpPanelHidden))
            evt::BitOff(kHelpPanelHidden);
        else
            evt::BitOn(kHelpPanelHidden);
        se = 8;
    }
    if (se >= 0)
        playBattleSound(se);
}

// SelectCommandListAuto @ 0x0025C840: an auto battle takes the entry
// under the cursor if it can be chosen.
void chooseCommandAutomatically(CommandMenu& d)
{
    if (entryUnavailable(d))
        return;
    d.state = 3;
    commitCommand(d);
}

// nbGetCommSelStat @ 0x0025C888
int32_t commandMenuState() { return commandMenu().state; }

// nbSetCommSelStat @ 0x0025C8A8
void setCommandMenuState(int8_t stat) { commandMenu().state = stat; }

// nbCloseCommSel @ 0x0025C8D0: the menu fades out.
void closeCommandMenu()
{
    CommandMenu& d = commandMenu();
    d.state = 4;
    d.animation = (d.animation & ~CommandMenuAnimation::FadeIn) | CommandMenuAnimation::FadeOut;
}

// nbCommSelShutdown @ 0x0025CB40
void shutdownCommandMenu(uint32_t process)
{
    CommandMenu& d = *guest::table<CommandMenu>(dds3::GetProcessData(process));
    if (d.data->CommandMenuProcessID == process)
        d.data->CommandMenuProcessID = 0;
    mem::HandleFree(d.mem);
}

// SetCommList @ 0x0025CB80: fills the lists for the unit. Commands: Attack,
// the active skills usable in battle, Pass. The Demi-fiend also gets Talk
// and the talk skills, the items he has that work in battle, and the stock
// demons to summon (by version: listsItems, listsSummons); a demon gets
// command 7. Everyone gets Escape. Each
// entry notes why it can't be chosen now, the last reason found winning.
void fillCommandLists(CommandMenu& d, Party& my)
{
    MainProcessData& main = *d.data;
    const UnitWork& unit = *GetUnitWorkPointer(main, my);
    const uint16_t ailment = unit.ailment();
    const bool player = (unit.flag & UnitFlag::PlayerCharacter) != 0;
    for (int32_t& count : d.counts)
        count = 0;

    add(d, kTabCommand, kEntryAttack, kDisableNone);
    if (player)
        add(d, kTabTalk, kEntryTalk, ailment == static_cast<uint16_t>(Ailment::Fly) ? kDisableAilment : kDisableNone);

    const bool allSkills = (main.stat & kStatDebugAllSkills) != 0;
    const int32_t skills = allSkills ? 0x200 : unit.skillcnt;
    for (int32_t i = 0; i < skills; ++i) {
        const int32_t skill = (d.data->stat & kStatDebugAllSkills) ? i : unit.skill[i];
        if (skill == 0)
            continue;
        const int8_t type = dat::skillInfo(skill).type;
        if (type == 0) {
            const NormalSkill& ns = dat::normalSkill(skill);
            if (!(ns.use & 2))
                continue;
            int8_t disable = kDisableNone;
            if ((ns.flag & 1) && (d.data->stat & kStatNoBossSkills))
                disable = kDisableBattle;
            if ((ns.flag & 2) && (d.data->stat & kStatFlag4))
                disable = kDisableBattle2;
            if (checkSkillCost(d.my->formindex, skill) != SkillCheck::Ok)
                disable = kDisableCost;
            if (ns.damageClass == 1 && unit.ailment() == static_cast<uint16_t>(Ailment::Mute))
                disable = kDisableAilment;
            if (skill == 0x48) {   // Escape
                if (!escapeAllowed(*d.data))
                    disable = kDisableBattle;
            } else if (skill == 0xdf) {   // a summoning skill
                if (main.playerpcnt >= 4 || randomSummonableStock() < 0)
                    disable = kDisableNoSummon;
            }
            add(d, kTabCommand, static_cast<uint16_t>(skill), disable);
        } else if (type == 2 && talkKind(skill) < 7) {
            add(d, kTabTalk, static_cast<uint16_t>(skill),
                ailment == static_cast<uint16_t>(Ailment::Fly) ? kDisableAilment : kDisableNone);
        }
    }

    if (!player)
        add(d, kTabDismiss, kEntryDismiss, kDisableNone);
    add(d, kTabEscape, kEntryEscape, escapeAllowed(main) ? kDisableNone : kDisableBattle);
    add(d, kTabCommand, kEntryPass, kDisableNone);

    GlobalWork& global = dat::globalWork();
    if (listsItems(d, my, player)) {
        for (int32_t i = 0; i < 0xa0; ++i) {
            const ItemData& item = dat::item(i);
            if (global.item_counts[i] == 0 || !(item.use & 2))
                continue;
            int8_t disable = kDisableNone;
            if ((item.flag & 1) && (main.stat & kStatNoBossSkills))
                disable = kDisableBattle;
            if ((item.flag & 8) && (d.data->stat & kStatFlag4))
                disable = kDisableBattle2;
            if (i == 0x38 && !escapeAllowed(*d.data))   // an item that escapes
                disable = kDisableBattle;
            add(d, kTabItem, static_cast<uint16_t>(i), disable);
        }
    }
    if (!listsSummons(player))
        return;
    for (int32_t i = 0; i < global.stock_count; ++i) {
        const uint8_t index = global.stock_list[i];
        const UnitWork& demon = global.units[index];
        if (!(demon.flag & UnitFlag::Valid) || (demon.flag & (UnitFlag::PlayerCharacter | UnitFlag::InParty)))
            continue;
        const bool dead = demon.hp == 0 || demon.badstat == static_cast<uint16_t>(Ailment::Dead);
        add(d, kTabSummon, index, dead ? kDisableDead : kDisableNone);
    }
}

// SetPrevCursor @ 0x0025D1E8: the cursor on a tab's entry, the list
// scrolled to show it, unless the entry can't be chosen now (then the
// first tab).
void placeCommandCursor(CommandMenu& d, int32_t tab, int32_t index)
{
    const int32_t rows = visibleRows(d, tab);
    d.tab = static_cast<uint8_t>(tab);
    d.nowcursor[tab] = index;
    d.nowlisty[tab] = index;
    const int32_t count = d.counts[tab];
    if (index + rows >= count)
        d.nowlisty[tab] = std::max(count - rows, 0);
    if (d.unavailable[tab][index] != 0) {
        d.tab = kTabCommand;
        d.nowcursor[tab] = 0;
        d.nowlisty[tab] = 0;
    }
}

// SetCommCursor2 @ 0x0025D2A0: the cursor starts on the unit's previous
// command when the options keep it (option 2 for auto battles, 1 otherwise).
void restorePreviousCommand(CommandMenu& d)
{
    const UnitWork& unit = *GetUnitWorkPointer(*d.data, *d.my);
    int16_t command = unit.prevcommand;
    uint16_t index = unit.previndex;
    if (!configOption(2) && (d.act->stat & kActAuto)) {
        command = 0;
        index = 0;
    }
    if (!configOption(1) && !(d.act->stat & kActAuto)) {
        command = 0;
        index = 0;
    }
    for (int32_t tab = 0; tab < kCommandTabs; ++tab) {
        for (int32_t i = 0; i < d.counts[tab]; ++i) {
            const uint16_t entry = d.entries[tab][i];
            bool found;
            switch (entry) {
            case kEntryAttack: found = command == 0; break;
            case kEntryEscape: found = command == 2; break;
            case kEntryPass: found = command == 3; break;
            case kEntryDismiss: found = command == 7; break;
            case kEntryTalk: found = false; break;
            default:
                switch (tab) {
                case kTabCommand: found = command == 1 && index == entry; break;
                case kTabTalk: found = command == 4 && index == entry; break;
                case kTabItem: found = command == 5 && index == entry; break;
                default: found = false; break;
                }
                break;
            }
            if (found) {
                placeCommandCursor(d, tab, i);
                return;
            }
        }
    }
}

// nbSetAutoCommSel @ 0x0025D4C0: an auto battle's menu starts on the
// previous command and chooses by itself.
void setAutoCommand()
{
    CommandMenu& d = commandMenu();
    restorePreviousCommand(d);
    d.animation |= CommandMenuAnimation::Auto;
}

// InitCommSelProcessData @ 0x0025D500: the menu for the unit of `my`,
// fading and sliding in, its lists filled and the cursor placed.
uint32_t newCommandMenu(MainProcessData& data, Party& my, ActionProcessData& act)
{
    const uint32_t handle = mem::HandleAllocate(sizeof(CommandMenu));
    const uint32_t address = mem::HandleAcquirePointer(handle);
    std::memset(guest::table<uint8_t>(address), 0, sizeof(CommandMenu));
    CommandMenu& d = *guest::table<CommandMenu>(address);
    d.mem = handle;
    d.data.address = guest::addressOf(&data);
    d.act.address = guest::addressOf(&act);
    d.state = (act.stat & kActAuto) ? 2 : 1;
    d.tab = kTabCommand;
    d.oz = 0xff0050;
    d.animation = CommandMenuAnimation::FadeIn | CommandMenuAnimation::Slide;
    d.ox = -30;
    d.cnt = 2;
    d.summonGrow = ee::Float::fromInt(1);
    d.my.address = guest::addressOf(&my);
    d.partytarget.address = 0;
    d.alpha = 0;
    d.scale = ee::Float::fromBits(0);
    fillCommandLists(d, my);
    restorePreviousCommand(d);
    return address;
}

// nbInitCommSelProcess @ 0x0025D620: the process ("nb_commsel"), a child of the battle.
void startCommandMenu(MainProcessData& data, Party& my, ActionProcessData& act)
{
    const uint32_t d = newCommandMenu(data, my, act);
    const uint32_t process = dds3::StartProcess(kCommSelName, 0x2b0e, 1, 1, addr(0x0025c908), addr(0x0025cb40), d);
    dds3::LinkProcess(data.MainProcessID, process);
    data.CommandMenuProcessID = process;
}

} // namespace nocturne::nb

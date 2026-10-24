// Choosing a command (original unit: nbCommSelProcess): the battle menu of
// the unit whose turn it is. Its commands are in six lists ("tabs"), each
// entry a skill, item or stock index or one of the fixed commands below,
// with a reason it can't be chosen now. The process "nb_commsel" keeps a
// CommSelectData; drawing the menu is still the original's.
//
// Names are the HD remaster's except where marked.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

// The lists (HD: DispComm1PanelComm / Talk / Item / Summon).
enum CommandTab : uint8_t {
    kTabCommand = 0,   // Attack, skills, Pass
    kTabTalk = 1,      // the Demi-fiend's Talk and talk skills
    kTabItem = 2,
    kTabSummon = 3,    // the stock
    kTabDismiss = 4,   // a demon's own command 7 (tentative name)
    kTabEscape = 5,
};
inline constexpr int32_t kCommandTabs = 6;
inline constexpr int32_t kCommandListMax = 0x120;

// Entries that aren't skill, item or stock indexes.
enum CommandEntry : uint16_t {
    kEntryAttack = 0x8000,
    kEntryEscape = 0x8001,
    kEntryPass = 0x8002,
    kEntryDismiss = 0x8003,   // command 7 ("Dismiss" in the battle strings; tentative)
    kEntryTalk = 0x8004,
};

// Why an entry can't be chosen (commdisable; 0: it can).
enum CommandUnavailable : int8_t {
    kDisableNone = 0,
    kDisableBattle = 1,     // not in this battle (a boss battle, or escape not allowed)
    kDisableBattle2 = 2,    // BattleStat 4 and the skill or item's flag (tentative)
    kDisableCost = 3,       // not enough HP or MP, or muted (nbCheckSkillCost)
    kDisableDead = 4,       // a stock demon who is dead
    kDisableAilment = 5,    // magic while Mute, talking while Fly
    kDisableNoSummon = 6,   // a summoning skill with the party full or no one to call
};

// nbCommSelProcessData (HD: nbCommSelProcessData_t), 0x14D0 bytes.
struct CommandMenu {
    uint32_t mem;                            // its memory handle
    Ptr32<MainProcessData> data;
    Ptr32<ActionProcessData> act;
    int8_t state;                            // 1 opening, 2 choosing, 3 chosen, 4 closing (HD: nowstat)
    uint8_t tab;                             // the tab (CommTab) (HD: nowtype)
    uint8_t pad0e[2];
    int32_t drawtype, drawcursor, drawlisty; // what was drawn last
    int32_t nowcursor[kCommandTabs];         // the entry under the cursor, per tab
    int32_t nowlisty[kCommandTabs];          // the first entry shown, per tab
    Ptr32<Party> my, partytarget;
    uint16_t entries[kCommandTabs][kCommandListMax];   // (HD: commlist)
    int32_t counts[kCommandTabs];   // (HD: commcnt)
    int8_t unavailable[kCommandTabs][kCommandListMax];   // (HD: commdisable)
    int32_t cnt;                             // rows the summon list shows (2, then 3)
    ee::Float summonGrow;   // (HD: smritu)
    uint32_t animation;                      // CommAnime bits (HD: animeflag)
    int32_t ox, oy, oz;
    int32_t alpha, helpAlpha;   // (HD: helpa)
    ee::Float scale;   // (HD: ritu)
};
static_assert(sizeof(CommandMenu) == 0x14d0);
static_assert(offsetof(CommandMenu, entries) == 0x54 && offsetof(CommandMenu, counts) == 0xdd4);
static_assert(offsetof(CommandMenu, unavailable) == 0xdec && offsetof(CommandMenu, cnt) == 0x14ac);
static_assert(offsetof(CommandMenu, animation) == 0x14b4 && offsetof(CommandMenu, scale) == 0x14cc);

// animeflag
namespace CommandMenuAnimation {
inline constexpr uint32_t FadeIn = 0x01;    // alpha up to 0x80
inline constexpr uint32_t FadeOut = 0x02;   // alpha down to 0
inline constexpr uint32_t Grow = 0x04;      // the summon list grows (smritu to 0); input waits
inline constexpr uint32_t Slide = 0x08;     // ox halves toward 0
inline constexpr uint32_t Auto = 0x10;      // an auto battle chose (nbSetAutoCommSel)
inline constexpr uint32_t Help = 0x20;      // the help panel shows (helpa up)
} // namespace CommAnime

CommandMenu& commandMenu();
int32_t visibleRows(const CommandMenu& d, int32_t tab);         // rows a tab shows
void animateCommandMenu(CommandMenu& d);
bool entryUnavailable(const CommandMenu& d);      // the entry can't be chosen
void commitCommand(CommandMenu& d);               // the entry becomes the unit's command
int32_t nextTab(const CommandMenu& d, bool right);
void readCommandPad(CommandMenu& d);
void chooseCommandAutomatically(CommandMenu& d);
int32_t commandMenuState();
void setCommandMenuState(int8_t stat);
void closeCommandMenu();
void shutdownCommandMenu(uint32_t process);
void fillCommandLists(CommandMenu& d, Party& my);
// [version] Who gets the item and summon lists (source/<version>/src/battle/comm_select.cpp).
bool listsItems(CommandMenu& d, Party& my, bool player);
bool listsSummons(bool player);
void placeCommandCursor(CommandMenu& d, int32_t tab, int32_t index);
void restorePreviousCommand(CommandMenu& d);
void setAutoCommand();
uint32_t newCommandMenu(MainProcessData& data, Party& my, ActionProcessData& act);           // the record's address
void startCommandMenu(MainProcessData& data, Party& my, ActionProcessData& act);

} // namespace nocturne::nb

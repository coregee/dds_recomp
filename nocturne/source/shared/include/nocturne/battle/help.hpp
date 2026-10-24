// The battle's help line (original unit: nbHelpProcess): one line of text
// at the top of the screen naming the skill, item or target chosen, or a
// status message (docs/battle-presentation.md). The process "nb_help"
// keeps a HelpData; the nbDisp* functions set what it shows.
//
// Names are the HD remaster's except where marked.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/interface/font.hpp"

namespace nocturne::nb {

// What the help line shows.
enum HelpType : int32_t {
    kHelpText = 0,      // text1, then text2 (any type other than 1 and 2)
    kHelpMessage = 1,   // message msgno of table msgid
    kHelpPlayer = 2,    // text1, then the name the player entered
};

// nbHelpProcessData (HD: nbHelpProcessData_t), 0x38 bytes from the pool.
struct HelpLine {
    int32_t type;                    // HelpType
    uint32_t text1, text2;           // guest strings (0: none)
    int32_t textframe;               // frames shown so far
    int32_t textmax;                 // frames to show it (< 1: until replaced)
    Ptr32<fr::Request> texthandle;   // the request being drawn this frame
    int32_t textwidth;               // in pixels, both texts and the gap
    int32_t nextwidth;               // where the second text starts
    uint32_t textcol;
    int32_t msgid, msgno;            // the message shown (msgid -1: none)
    int32_t reqmsgid, reqmsgno;      // the message asked for by nbDispMsgHelp
    int32_t alpha;                   // the panel behind it
};
static_assert(sizeof(HelpLine) == 0x38);
static_assert(offsetof(HelpLine, textcol) == 0x20 && offsetof(HelpLine, msgid) == 0x24 && offsetof(HelpLine, alpha) == 0x34);

void showHelpText(uint32_t text1, uint32_t text2, int32_t type, int32_t max, uint32_t col);
void showSkillName(int32_t id);
void showItemName(int32_t id);
void showMiscActionName(int32_t id, int32_t type);     // not in the HD remaster; never called
void showCommandName(int32_t comm);
void showBattleText(int32_t id);                       // not in the HD remaster; never called
void showDevilName(int32_t id);
void showStatusMessage(int32_t msgid, int32_t no, int32_t var_id, int32_t var_ind);
void showHelpMessage(int32_t msgid, int32_t no, int32_t msgtype);
void clearHelpLine();
void shutdownHelpLine(uint32_t process);
uint32_t newHelpLine();           // the record's address
void startHelpLine(MainProcessData& data);

} // namespace nocturne::nb

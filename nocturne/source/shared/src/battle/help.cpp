// The battle's help line (original unit: nbHelpProcess): what it shows and
// how wide it is. Drawing it each frame (nbHelpProcess1, DrawPanel) is still
// the original's. Rewritten from the original instructions.
#include "nocturne/battle/help.hpp"

#include <cstring>

#include "nocturne/address.hpp"
#include "nocturne/data/magatama.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/interface/message.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kHelpName = addr(0x005514f0);   // "nb_help"

// String tables (guest pointers to EUC-JP / ASCII strings).
constexpr uint32_t kSkillNames = addr(0x003e83f0);
constexpr uint32_t kItemNames = addr(0x003e8170);
constexpr uint32_t kMiscActionNames = addr(0x005263f8);   // two leftover Japanese strings
constexpr uint32_t kBattleText = addr(0x003e8bf0);        // "Attack", "Retreat", "Pass", "Summon", ...
constexpr uint32_t kDevilNames = addr(0x003e7328);
constexpr uint32_t kRaceNames = addr(0x003e7930);
constexpr uint32_t kPlayerRaceNames = addr(0x003e7a30);   // "Fiend", "Votary", ...

constexpr uint32_t kWhite = 0x89feff80;
constexpr uint32_t kNameColor = 0xa09dc380;
constexpr uint32_t kDepth = 0xff0051;

uint32_t string(uint32_t table, int32_t index) { return guest::table<uint32_t>(table)[index]; }
const uint8_t* text(uint32_t address) { return guest::table<uint8_t>(address); }

HelpLine& help() { return *guest::table<HelpLine>(dds3::GetProcessData(dds3::SearchProcessName(kHelpName))); }

// The width of a string as the help line draws it.
int32_t textWidth(uint32_t col, uint32_t str)
{
    fr::Request* font = fr::LinkSpacedLetters(0, 0, kDepth, col, text(str), nullptr);
    const int32_t width = fr::frGetChainWidth(*font);
    fr::frDestroyFontRequestAfter(font);
    return width;
}

// nbHelpOff, on a record.
void off(HelpLine& h)
{
    int32_t type;
    if (h.text1 == 0) {
        if (h.type != kHelpMessage || h.msgid < 0)
            return;
        h.text1 = 0;
        type = kHelpMessage;
    } else {
        type = h.type;
        h.text1 = 0;
    }
    h.text2 = 0;
    if (type == kHelpMessage) {
        mes::RequestMessageRelease(h.msgid, false);
        h.msgid = -1;
    }
}

} // namespace

// nbDispText @ 0x00288E18: replaces what the line shows for `max` frames.
// Its width is both texts with 10 pixels between; a message's is the
// message's (asked for by nbDispMsgHelp).
void showHelpText(uint32_t text1, uint32_t text2, int32_t type, int32_t max, uint32_t col)
{
    HelpLine& h = help();
    off(h);
    h.text1 = text1;
    h.text2 = text2;
    if (type == kHelpMessage) {
        h.msgid = h.reqmsgid;
        h.msgno = h.reqmsgno;
    }
    h.textcol = col;
    if (type == kHelpMessage) {
        h.textwidth = mes::GetMessageWidth(h.msgid, h.msgno, 0) >> 4;
    } else if (type == kHelpPlayer) {
        h.textwidth = textWidth(col, h.text1);
        fr::Request* name = fr::AppendNameText(0, 1, nullptr, 0);
        h.nextwidth = h.textwidth + 10;
        h.textwidth += fr::frGetChainWidth(*name) + 10;
        fr::frDestroyFontRequestAfter(name);
    } else {
        h.textwidth = textWidth(h.textcol, h.text1);
        if (h.text2 != 0) {
            const int32_t width = textWidth(h.textcol, h.text2);
            h.nextwidth = h.textwidth + 10;
            h.textwidth += width + 10;
        }
    }
    h.textmax = max;
    h.type = type;
    h.textframe = 0;
}

// nbDispSkillName @ 0x00289008
void showSkillName(int32_t id) { showHelpText(string(kSkillNames, id), 0, kHelpText, 30, kWhite); }

// nbDispItemName @ 0x00289040
void showItemName(int32_t id) { showHelpText(string(kItemNames, id), 0, kHelpText, 30, kWhite); }

// 0x00289078 (no original name)
void showMiscActionName(int32_t id, int32_t type) { showHelpText(string(kMiscActionNames, id), 0, type, 30, kWhite); }

// nbDispMiscActionNameComm @ 0x002890B0: a command's name (attack, escape,
// pass, summon, return); nothing for the others.
void showCommandName(int32_t comm)
{
    int32_t no;
    switch (comm) {
    case 0: no = 0; break;    // "Attack"
    case 2: no = 14; break;   // "Retreated"
    case 3: no = 2; break;    // "Pass"
    case 6: no = 3; break;    // "Summon"
    case 7: no = 4; break;    // "Dismiss"
    default: return;
    }
    showHelpText(string(kBattleText, no), 0, kHelpText, 30, kWhite);
}

// 0x002891A8 (no original name)
void showBattleText(int32_t id) { showHelpText(string(kBattleText, id), 0, kHelpText, 30, kWhite); }

// nbDispDevilName @ 0x002891E0: race and name; for the Demi-fiend (0) his
// race by Magatama and the name the player entered.
void showDevilName(int32_t id)
{
    GetMainProcessData();
    if (id == 0) {
        const int8_t race = static_cast<int8_t>(magatama::playerRace());
        showHelpText(string(kPlayerRaceNames, race), 0, kHelpPlayer, 2, kNameColor);
        return;
    }
    showHelpText(string(kRaceNames, static_cast<uint8_t>(dat::devilFormat(id).race)), string(kDevilNames, id), kHelpText, 2,
               kNameColor);
}

// nbDispJyokyoHelp @ 0x002892A8: a status message; var_id >= 0 fills its
// {var 0} first (a character's name, var_id 1 with index 0, is the
// Demi-fiend's entered name).
void showStatusMessage(int32_t msgid, int32_t no, int32_t var_id, int32_t var_ind)
{
    if (var_id == mes::kVarDevil && var_ind == 0)
        var_id = mes::kVarCharacter;
    if (var_id >= 0)
        mes::SetVarFormatted(msgid, 0, var_ind, static_cast<uint32_t>(var_id));
    showHelpMessage(msgid, no, 1);
}

// nbDispMsgHelp @ 0x00289310: message `no` of table `msgid`; msgtype picks
// how long and in which color (0, 1: 45 frames, 2: 20 in the name color,
// 3: 30), any other shows nothing.
void showHelpMessage(int32_t msgid, int32_t no, int32_t msgtype)
{
    HelpLine& h = help();
    h.reqmsgno = no;
    h.reqmsgid = msgid;
    switch (msgtype) {
    case 0:
    case 1: showHelpText(0, 0, kHelpMessage, 45, kWhite); break;
    case 2: showHelpText(0, 0, kHelpMessage, 20, kNameColor); break;
    case 3: showHelpText(0, 0, kHelpMessage, 30, kWhite); break;
    default: break;
    }
}

// nbHelpOff @ 0x00289450: clears the line (a message is released).
void clearHelpLine() { off(help()); }

// nbHelpShutdown @ 0x002898C0
void shutdownHelpLine(uint32_t process)
{
    const uint32_t data = dds3::GetProcessData(process);
    off(*guest::table<HelpLine>(data));
    mem::PoolRelease(data);
}

// InitHelpProcessData @ 0x00289940
uint32_t newHelpLine()
{
    const uint32_t address = mem::PoolAllocate(sizeof(HelpLine));
    std::memset(guest::table<uint8_t>(address), 0, sizeof(HelpLine));
    HelpLine& h = *guest::table<HelpLine>(address);
    h.msgid = -1;
    h.alpha = 0x80;
    return address;
}

// nbInitHelpProcess @ 0x00289990: the process ("nb_help"), a child of the battle.
void startHelpLine(MainProcessData& data)
{
    const uint32_t h = newHelpLine();
    const uint32_t process = dds3::StartProcess(kHelpName, 0x3f9, 1, 1, addr(0x00289630), addr(0x002898c0), h);
    dds3::LinkProcess(data.MainProcessID, process);
    data.HelpProcessID = process;
}

} // namespace nocturne::nb

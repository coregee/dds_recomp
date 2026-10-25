// The talks' steps: each group's flow, rewritten or still the original's.
#include "nocturne/battle/talk_flow.hpp"

#include "nocturne/address.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kTalkFlows = addr(0x004ef468);   // [step group] the original's flow functions

} // namespace

bool moonproof(uint16_t id)
{
    switch (id) {
    case devil::Barong: case devil::Chimera: case devil::Amaterasu: case devil::Scathach: case devil::BeijiWeng:
    case devil::Sati: case devil::Atavaka: case devil::Odin: case devil::Kali: case devil::Mikazuchi:
    case devil::Baihu: case devil::Yatagarasu:
        return true;
    default:
        return false;
    }
}

// (The original's nbNegoProcess1 calls the group's flow from the table.)
int32_t runTalkStep(TalkState& n)
{
    const uint32_t group = n.talkId >> 16;
    switch (group) {
    case 1: return openingFlow(n);
    case 2: return fullMoonFlow(n);
    case 3: return stockFlow(n);
    case 4: return kinFlow(n);
    case 5: return fatedFlow(n);
    case 6: return bargainFlow(n);
    case 7: return questionFlow(n);
    case 8: return fightFlow(n);
    case 9: return dealFlow(n);
    case 10: return noDealFlow(n);
    case 11: return drainFlow(n);
    case 12: return speakUpFlow(n);
    case 13: return ambushFlow(n);
    case 14: return askToJoinFlow(n);
    case 15: return mercyFlow(n);
    case 16: return tauntFlow(n);
    default: return guest::callTalkStep(guest::table<const uint32_t>(kTalkFlows)[group], guest::addressOf(&n));   // (group 0: none in the game)
    }
}

} // namespace nocturne::nb

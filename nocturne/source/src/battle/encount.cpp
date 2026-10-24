// Random encounters in the field (original unit: nbEncount). Rewritten from
// the original instructions.
#include "nocturne/battle/encount.hpp"

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kThreshold = 0x00551520;      // int32_t: the rolled count needed (HD: encmax)
constexpr uint32_t kBaseThreshold = 0x0054ff1c;  // int32_t: 370
constexpr uint32_t kSkillEstoma = 1;             // GlobalWork::fieldskills
constexpr uint32_t kSkillRiberama = 2;
const ee::Float kStepLength = ee::Float::fromBits(0x42c80000);   // 100.0

int32_t& threshold() { return *guest::table<int32_t>(kThreshold); }

} // namespace

// nbGetEncountJoken @ 0x0028C9F0: in the phases the pack's moon mask names,
// its moon table; otherwise one of four by its two event bits.
int32_t encounterTable(int32_t pack)
{
    const EncountPack& p = dat::encountPack(pack);
    if (p.moonchk != 0 && ((p.moonchk >> (evt::GetAgeOfMoon() & 31)) & 1))
        return p.table2;
    const bool first = p.eventbit1 != 0 && evt::BitCheck(p.eventbit1);
    const bool second = p.eventbit2 != 0 && evt::BitCheck(p.eventbit2);
    return p.table1[(first ? 1 : 0) + (second ? 2 : 0)];
}

// nbGetEncountMax @ 0x0028CB68: rolled once, until an encounter (or a
// reset) clears it.
int32_t encounterThreshold(int32_t pack)
{
    if (pack == 0)
        return 0;
    const EncountTbl& table = dat::encountPack(pack).enctable[encounterTable(pack)];
    int32_t weights = 0;
    for (const EncounterEntry& e : table.entries)
        weights += e.weight;
    if (weights == 0)
        return 0;
    if (threshold() > 0)
        return threshold();
    const int32_t base = *guest::table<int32_t>(kBaseThreshold) - table.normalWeight * 48 / 100;
    threshold() = sdf::GetRandInt(base * 2 - 32) + 16;
    diag::print(diag::Message::EncounterRate, threshold(), base);
    return threshold();
}

// nbGetEncountCnt @ 0x0028CC98
int32_t encounterCount() { return dat::globalWork().encountCount; }

// nbEncountCalc @ 0x0028CCA8: `length` walked in area `pack`.
int32_t walkForEncounter(int32_t pack, ee::Float length)
{
    if (pack == 0 || length == ee::Float::fromBits(0))
        return 0;
    const int32_t table = encounterTable(pack);
    const int32_t needed = encounterThreshold(pack);
    if (needed == 0)
        return 0;
    GlobalWork& work = dat::globalWork();
    const ee::Float walked = work.encountDistance + length;
    work.encountDistance = walked;
    if (walked < kStepLength)
        return 0;
    const int32_t steps = (walked / kStepLength).toInt();
    work.encountDistance = walked - ee::Float::fromInt(steps) * kStepLength;
    for (int32_t i = 0; i < steps; ++i) {
        const bool riberama = (dat::globalWork().fieldskills & kSkillRiberama) != 0;
        const int32_t roll = sdf::GetRandInt(riberama ? 7 : 3);
        dat::globalWork().encountCount = static_cast<uint16_t>(dat::globalWork().encountCount + roll + (riberama ? 6 : 2));
    }
    if (work.encountCount > 65000)
        work.encountCount = 65000;
    if (work.encountCount < needed)
        return 0;
    const int32_t roll = sdf::GetRandInt(1000);
    const EncountTbl& entries = dat::encountPack(pack).enctable[table];
    int32_t sum = 0;
    for (int32_t i = 0; i < 12; ++i) {
        const EncounterEntry& e = entries.entries[i];
        if (e.encountid == 0)
            continue;
        sum += e.weight;
        if (roll >= sum)
            continue;
        if ((dat::globalWork().fieldskills & kSkillEstoma) && !encounterWorthFighting(e.encountid)) {
            resetEncounterCount();
            return 0;
        }
        threshold() = 0;
        return table << 24 | i << 16 | e.encountid;
    }
    return 0;
}

// nbCheckEncountLevel @ 0x0028CEE0: the Demi-fiend's level is at most the
// group's average plus a quarter of his own.
bool encounterWorthFighting(int32_t encno)
{
    if (encno == 0)
        return false;
    const Encount& e = dat::encount(encno);
    const uint16_t* ids = e.devil;
    int32_t count = 0, levels = 0;
    for (int32_t i = 0; i < 11; ++i) {
        if (ids[i] != 0) {
            ++count;
            levels += dat::devilFormat(ids[i]).level;
        }
    }
    if (count == 0)
        return false;
    const int32_t player = dat::playerLevel();
    return player <= levels / count + player / 4;
}

// nbResetEncountCount @ 0x0028CFB0
void resetEncounterCount()
{
    GlobalWork& work = dat::globalWork();
    work.encountCount = 0;
    work.encountDistance = ee::Float::fromBits(0);
    threshold() = 0;
}

// GetBgmCategory @ 0x0028CFC8: pack 0 has none of its own.
int32_t encounterMusic(int32_t pack, int32_t encno)
{
    int32_t type = 0;
    if (pack > 0)
        type = dat::encountPack(pack).btlsound;
    if (dat::encount(encno).btlsound != 0)
        type = dat::encount(encno).btlsound;
    return type != 0 ? type : 1;
}

// nbGetBgmCategoryInBattle @ 0x0028D028
int32_t battleMusic()
{
    const MainProcessData& main = *GetMainProcessData();
    return encounterMusic(main.encpackno, main.encno);
}

// nbGetBgmCategoryInField @ 0x0028D050: the data's top byte is its table
// (0..3), not an area pack, yet it is looked up as one: tables 1..3 lend
// packs 1..3's music to encounters with none.
int32_t fieldMusic(uint32_t encdata) { return encounterMusic(encounterTableOf(encdata), encounterOf(encdata)); }

} // namespace nocturne::nb

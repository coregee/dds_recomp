// The battle's result (original unit: nbResultProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/result.hpp"

#include "nocturne/address.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/data/progression.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/fusion/growth.hpp"
#include "nocturne/build.hpp"
#include "nocturne/data/ids.hpp"
#include "nocturne/data/unit.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x00543608);    // "nb_result"
constexpr uint32_t kFirstStep = addr(0x0024c378), kSecondStep = addr(0x0024c1d0), kShutdown = addr(0x0024c3c8);
constexpr uint32_t kLoad = addr(0x0024a060);           // nbResultLoad (no C yet): the screen's textures and rows
constexpr uint32_t kAfterResult = addr(0x0024cbb8);    // (no C yet) what follows the result screen
constexpr uint32_t kReleaseStage = addr(0x001e1770);   // (no C yet) the stage's resources let go (tentative)
constexpr uint32_t kTextures = addr(0x00551104);       // uint32[3]: the screen's textures
constexpr uint32_t kFinishWait = addr(0x005510dc);     // int32: frames since the rows finished
constexpr uint32_t kSkipped = addr(0x005510e0);        // int32 (tentative)
constexpr uint32_t kExpShown = addr(0x005510e8);       // int32: the experience the screen shows
constexpr uint32_t kRowsFlag = addr(0x005510fc);       // int32 (tentative)
constexpr uint32_t kLevelUps = addr(0x00574f50);       // LevelUpAnimation[64]
constexpr uint32_t kRows = addr(0x00574e80);           // ResultRow[4]

// A level-up animation's slot (typeNbResultLvupAnmWork, tentative fields).
struct LevelUpAnimation {
    int32_t active;
    int32_t a, b;   // its arguments (tentative: who and what)
    int32_t timer;  // frames left
};
static_assert(sizeof(LevelUpAnimation) == 16);

// One of the screen's four rows: done once its count reaches its source's
// value plus its own extra (tentative names).
struct ResultRow {
    int32_t active;
    uint32_t count;
    uint8_t unknown_08[0xc];
    uint32_t source;   // a record whose +0x10 holds the value counted to
    uint8_t unknown_18[0x14];
    uint32_t extra;
    uint8_t unknown_30[4];
};
static_assert(sizeof(ResultRow) == 0x34);

int32_t& word(uint32_t address) { return *guest::table<int32_t>(address); }

} // namespace

// GetAddExp @ 0x0024BFF0
int32_t cappedExp(int32_t index, int32_t exp)
{
    const GlobalWork& global = dat::globalWork();
    const uint32_t ceiling = cmb::expForLevel(global.units[index & 0xff], 0x100);
    int32_t room = static_cast<int32_t>(ceiling - 1 - static_cast<uint32_t>(global.units[index].exp));
    if (room < 0)
        room = 0;
    return exp < room ? exp : room;
}

// nbResultAddExp @ 0x0024C060
void grantSpoils(MainProcessData& main)
{
    for (int32_t i = 0; i < 4; ++i)
        if (main.item[i] != 0 && main.itemcnt[i] != 0)
            dat::addItem(main.item[i], main.itemcnt[i]);
    dat::addMacca(earnedMacca(main));
    for (int32_t i = 0; i < 16; ++i) {
        int32_t exp = earnedExp(main);
        UnitWork& unit = dat::globalWork().units[i];
        if (!(unit.flag & UnitFlag::Valid))
            continue;
        if (!(unit.flag & UnitFlag::InParty) && !stockExpShare(unit, exp))
            continue;
        if (unit.ailment() == static_cast<uint16_t>(Ailment::Dead) || unit.hp == 0)
            continue;
        dat::addExp(unit, cappedExp(i, exp));
    }
}

// nbResultTexDel @ 0x0024A258
void releaseResultTextures()
{
    uint32_t* textures = guest::table<uint32_t>(kTextures);
    for (int32_t i = 0; i < 3; ++i)
        tex::DeferredRelease(textures[i]);
    for (int32_t i = 0; i < 3; ++i)
        textures[i] = 0;
}

// nbResultLvupAnmAdd @ 0x0024A298: the first free slot, for 20 frames;
// none free, nothing.
void addLevelUpAnimation(int32_t a, int32_t b)
{
    LevelUpAnimation* slots = guest::table<LevelUpAnimation>(kLevelUps);
    for (int32_t i = 0; i < 64; ++i) {
        if (slots[i].active != 0)
            continue;
        slots[i] = {1, a, b, 20};
        return;
    }
}

// nbResultFinWaitChk @ 0x0024AFA0: while a row is still counting the wait
// stays; then it counts frames up to 60.
int32_t finishWait()
{
    const ResultRow* rows = guest::table<const ResultRow>(kRows);
    bool counting = false;
    for (int32_t i = 0; i < 4; ++i) {
        const ResultRow& row = rows[i];
        if (row.active != 0 && row.count < static_cast<uint32_t>(word(row.source + 0x10)) + row.extra)
            counting = true;
    }
    int32_t& wait = word(kFinishWait);
    if (!counting && wait < 60)
        ++wait;
    return wait;
}

// ShutdownProcess @ 0x0024BE88 (tentative: the HD name in order): the
// battle's helper processes end.
void stopBattleProcesses()
{
    MainProcessData& main = *GetMainProcessData();
    for (uint32_t* id : {&main.AutoCommProcessID, &main.CameraProcessID, &main.EffectProcessID, &main.UnitProcessID,
                         &main.HelpProcessID, &main.PanelProcessID}) {
        if (*id != 0) {
            dds3::KillProcess(*id, 1);
            *id = 0;
        }
    }
}

// ClearStage @ 0x0024BF40 (tentative: the HD name in order): every unit's
// PAC request freed and its formation cleared, every party marked out
// (0x28), and the stage's resources let go.
void clearStage()
{
    MainProcessData& main = *GetMainProcessData();
    for (int32_t i = 0; i < 32; ++i) {
        Formation& form = guest::table<Formation>(main.form.address)[i];
        if ((form.stat & 1) && form.pacRequest != 0) {
            if (kBuild.vanilla)
                file::RequestRelease(form.pacRequest);   // (the first release frees it as any file)
            else
                file::PacRequestFree(form.pacRequest);
            form.pacRequest = 0;
        }
        form.stat = 0;
    }
    for (int32_t i = 0; i < 14; ++i)
        main.party[i].flag = static_cast<int16_t>(main.party[i].flag | 0x28);
    guest::callOriginal(kReleaseStage);
}

// nbResultProcess1 @ 0x0024C378: the battle's helpers stop, the experience
// earned is noted, the screen loads, its counters start at 0; on to
// nbResultProcess2.
uint32_t firstResultStep(uint32_t)
{
    MainProcessData& main = *GetMainProcessData();
    stopBattleProcesses();
    word(kExpShown) = earnedExp(main);
    guest::callOriginal(kLoad);
    word(kRowsFlag) = 0;
    word(kFinishWait) = 0;
    word(kSkipped) = 0;
    return kSecondStep;
}

// nbResultShutdown @ 0x0024C3C8
void shutdownResult(uint32_t)
{
    GetMainProcessData()->ResultProcessID = 0;
    releaseResultTextures();
    guest::callOriginal(kAfterResult, 0);
}

// nbInitResultProcess @ 0x0024C3F0
void startResultProcess(MainProcessData& data)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kFirstStep, kShutdown, 0);
    dds3::LinkProcess(data.MainProcessID, process);
    data.ResultProcessID = process;
}

} // namespace nocturne::nb

// ===========================================================================
// By version (nocturne/build.hpp): the alternatives the builds choose between
// ===========================================================================

namespace nocturne::nb {

#if NOCTURNE_HARDTYPE
// nbResultAddExp @ 0x0024C060 (in place): every stock demon shares, in full
// with Watchful (skill 0x162) and three quarters without.
bool stockExpShare(const UnitWork& unit, int32_t& exp)
{
    const bool watchful = dat::hasSkill(unit, skill::Watchful);
    if (exp > 0 && !watchful)
        exp = static_cast<int32_t>(static_cast<uint32_t>(exp) * 3u) >> 2;
    return true;
}
#else
// nbResultAddExp @ 0x0024C060: only a stock demon with Watchful (skill 0x162) shares,
// 1/n of the experience (n: that skill's).
bool stockExpShare(const UnitWork& unit, int32_t& exp)
{
    if (!dat::hasSkill(unit, skill::Watchful))
        return false;
    if (exp > 0) {
        const int32_t n = dat::specialSkill(skill::Watchful).n;
        if (n == 0)
            divideByZeroTrap();
        exp /= n;
    }
    return true;
}
#endif

} // namespace nocturne::nb

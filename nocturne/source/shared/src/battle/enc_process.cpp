// The encounter's opening (original unit: nbEncProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/enc_process.hpp"

#include "nocturne/address.hpp"
#include "nocturne/battle/bad_ai.hpp"
#include "nocturne/battle/formation.hpp"
#include "nocturne/battle/help.hpp"
#include "nocturne/effect/cut.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x00551550);     // "nb_enc"
constexpr uint32_t kFrameCount = addr(0x0054e800);      // int32_t: the kernel's frame counter (read by 0x100410)
constexpr uint32_t kLoadStart = addr(0x00551548);       // int32_t: the frame the loading started
constexpr uint32_t kLoadTime = addr(0x0055154c);        // int32_t: frames it took (0 until done)
constexpr uint32_t kEndEffect = addr(0x001741c0);       // (no C yet) effBTLEncountEnd
constexpr uint32_t kCameraDone = addr(0x001b33f8);      // (no C yet) nbCameraState_Start_CheckEnd
constexpr uint32_t kLoadGroup = addr(0x0024e1e0);       // (no C yet) nbLoadUnitGroup(group, a, b): 1 the enemies, 0 the party
constexpr uint32_t kGroupLoading = addr(0x0024e2e0);    // (no C yet) nbCheckLoadGroup: still loading
constexpr uint32_t kFadeQuery = addr(0x0012c148);       // (unidentified) ...
constexpr uint32_t kFadeSet = addr(0x0012c150);         // (unidentified) ... and its follow-up
constexpr uint32_t kRunEncounter = addr(0x0028e2c8);
constexpr uint32_t kShutdownEncounter = addr(0x0028e340);

// MainProcessData::stat bits read here (tentative meanings).
constexpr uint32_t kStatBackAttack = 0x10;
constexpr uint32_t kStatMoonGlow = 0x400;         // the enemies glow under a full Kagutsuchi
constexpr uint32_t kStatFadeIn = 0x800;           // the battle opens from a fade: everyone at once
// Formation::flag bit 8: the unit has not appeared yet; Formation::anime
// bit 0x200: ... and appears without an effect (the party's).
constexpr uint32_t kFlagHidden = 8;
constexpr uint32_t kAnimeQuietAppear = 0x200;

int32_t frameCount() { return *guest::table<int32_t>(kFrameCount); }
int32_t& loadTime() { return *guest::table<int32_t>(kLoadTime); }

// The load time noted the first time the models are all in.
void noteLoadTime()
{
    if (loadTime() == 0)
        loadTime() = frameCount() - *guest::table<int32_t>(kLoadStart);
}

Formation& partyForm(MainProcessData& main, const Party& party) { return guest::table<Formation>(main.form.address)[party.formindex]; }

bool present(const Party& party) { return (party.flag & 9) != 0; }

} // namespace

// nbEncProcess1 @ 0x0028E2C8
uint32_t startEncounterLoad(uint32_t)
{
    MainProcessData& main = *GetMainProcessData();
    eff::startEncounterEffect();
    *guest::table<int32_t>(kLoadStart) = frameCount();
    loadTime() = 0;
    guest::callOriginal(kLoadGroup, 1, 1, (main.stat & kStatFadeIn) ? 0 : 1);
    return addr(0x0028e250);
}

// nbEncProcess2 @ 0x0028E250
uint32_t loadEnemyModels(uint32_t)
{
    MainProcessData& main = *GetMainProcessData();
    if (guest::callOriginal(kGroupLoading, 1) != 0)
        return 0;
    if (main.stat & kStatBackAttack)
        guest::callOriginal(kLoadGroup, 0, 0, 1);
    else
        guest::callOriginal(kLoadGroup, 0, 1, 0);
    return addr(0x0028e0e8);
}

// nbEncProcess2_5 @ 0x0028E0E8 (the party's models may still be loading):
// from a fade every enemy is simply shown;
// otherwise one appears (with hit effect 4) every eighth frame of the
// process.
uint32_t showEnemies(uint32_t process)
{
    MainProcessData& main = *GetMainProcessData();
    if (guest::callOriginal(kGroupLoading, 0) == 0)
        noteLoadTime();
    Party* parties = guest::table<Party>(main.party.address);
    if (main.stat & kStatFadeIn) {
        for (int32_t i = 4; i < 14; ++i)
            if (present(parties[i]))
                partyForm(main, parties[i]).flag &= ~kFlagHidden;
        return addr(0x0028dfc8);
    }
    if (dds3::GetRunTime(process) & 7)
        return 0;
    for (int32_t i = 4; i < 14; ++i) {
        if (!present(parties[i]))
            continue;
        Formation& form = partyForm(main, parties[i]);
        if (form.flag & kFlagHidden) {
            form.flag &= ~kFlagHidden;
            AddHitEffPacket(1, 0, form, 4);
            return 0;
        }
    }
    return addr(0x0028dfc8);
}

// nbEncProcess2_55 @ 0x0028DFC8
uint32_t setUpEncounterScene(uint32_t)
{
    MainProcessData& main = *GetMainProcessData();
    if (main.stat & kStatMoonGlow) {
        for (int32_t i = 4; i < 14; ++i) {
            Formation& form = guest::table<Formation>(main.form.address)[i];
            if ((form.stat & 1) && evt::GetAgeOfMoon() == 8) {
                dds3::ObjectBaseOnFlag(form.basic, 0x400);
                const uint32_t control = *guest::table<uint32_t>(form.basic + 0x1c);
                *guest::table<ee::Float>(control + 0xc4) = ee::Float::fromBits(0x43480000);   // 200.0
            }
        }
    }
    if (main.stat & kStatFadeIn) {
        showSide(1);
        dds3::FadeIn2(0);
        if (guest::callOriginal(kFadeQuery) != 0)
            guest::callOriginal(kFadeSet, 1);
    }
    if (main.stat & kStatBackAttack)
        showHelpMessage(main.statusMessageTable, statusMessage(main, 6), 1);
    return addr(0x0028def0);
}

// nbEncProcess2_6 @ 0x0028DEF0: the party's models in, each member shows
// up; the load time printed.
uint32_t showPlayers(uint32_t)
{
    MainProcessData& main = *GetMainProcessData();
    if (guest::callOriginal(kGroupLoading, 0) != 0)
        return 0;
    noteLoadTime();
    Party* parties = guest::table<Party>(main.party.address);
    for (int32_t i = 0; i < 4; ++i) {
        if (!present(parties[i]))
            continue;
        Formation& form = partyForm(main, parties[i]);
        if (form.flag & kFlagHidden) {
            form.flag &= ~kFlagHidden;
            form.anime |= kAnimeQuietAppear;
        }
    }
    diag::print(diag::Message::UnitLoadTime, loadTime());
    return addr(0x0028de40);
}

// nbEncProcess3 @ 0x0028DE40: every unit present stands with its model
// loaded (its handle's bit 0x10000 clear), for all 32 slots read (past the
// fourteen formations); then the camera's opening.
uint32_t finishEncounter(uint32_t)
{
    const uint32_t forms = GetMainProcessData()->form.address;
    for (uint32_t i = 0; i < 32; ++i) {
        const Formation& form = *guest::table<Formation>(forms + i * sizeof(Formation));
        if (!(form.stat & 1))
            continue;
        if (!(form.stat & 2) || form.hunit == 0 || (*guest::table<uint32_t>(form.hunit + 0xa4) & 0x10000))
            return 0;
    }
    if (guest::callOriginal(kCameraDone) == 0)
        return 0;
    guest::callOriginal(kEndEffect);
    GetMainProcessData()->stat &= ~kStatFadeIn;
    return 0xffffffffu;
}

// nbEncShutdown @ 0x0028E340
void shutdownEncounter(uint32_t) { GetMainProcessData()->EncProcessID = 0; }

// nbInitEncProcess @ 0x0028E360
void startEncounter(MainProcessData& data)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kRunEncounter, kShutdownEncounter, 0);
    dds3::LinkProcess(data.MainProcessID, process);
    data.EncProcessID = process;
}

} // namespace nocturne::nb

// The battle's presentation queue (nbKoukaProcess, nbMakePacket): the
// rewrite against the original instructions, run by the EE interpreter, in a
// random battle with some packets already queued.
#include <bit>
#include <algorithm>
#include <cstring>
#include <deque>
#include <string>
#include <vector>

#include "harness.hpp"
#include "version_map.hpp"
#include "interface_world.hpp"
#include "nocturne/battle/action.hpp"
#include "nocturne/battle/ai_script.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/calc.hpp"
#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/event_process.hpp"
#include "nocturne/battle/formation.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/battle/kouka_process.hpp"
#include "nocturne/battle/opening.hpp"
#include "nocturne/battle/macca_window.hpp"
#include "nocturne/battle/battle_panel.hpp"
#include "nocturne/battle/enc_process.hpp"
#include "nocturne/battle/encount.hpp"
#include "nocturne/battle/sound.hpp"
#include "nocturne/battle/talk.hpp"
#include "nocturne/battle/talk_flow.hpp"
#include "nocturne/data/devil_ai.hpp"
#include "nocturne/effect/boss.hpp"
#include "nocturne/effect/cut.hpp"
#include "nocturne/effect/system.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/event/units.hpp"
#include "nocturne/external.hpp"
#include "nocturne/facility/compendium.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/kernel/main_loop.hpp"
#include "nocturne/variant.hpp"

extern "C" {
uint32_t ps2PoolAllocate(int32_t);
uint32_t ps2MemoryHandleAllocate(int32_t);
uint32_t ps2MemoryHandleAcquirePointer(uint32_t);
uint64_t dds3StartProcess(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
uint64_t dds3GetProcessData(uint64_t);
}

// Action states not rewritten yet are called by address; here they run as
// original code in the interpreter, as on the original side.
extern "C" void nocturneInvokeBattleActionEntry(uint32_t entry, uint64_t context)
{
    difftest::iface::origVmVoidAt(entry, {context});
}
extern "C" uint64_t nocturneInvokeBattleActionUpdate(uint32_t target, uint64_t context)
{
    return difftest::iface::origVmAt(target, {context});
}
// ... and so do the kouka process's players not rewritten yet.
// The colour blend is VU0 code not rewritten yet: both sides run its instructions.
extern "C" uint64_t ps2EffectBlendColor(uint64_t first, uint64_t second, float amount)
{
    return difftest::iface::origVm(0x001abbd0, {first, second}, {std::bit_cast<uint32_t>(amount)});
}
extern "C" uint64_t nocturneInvokeOriginal(uint32_t entry, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t t0)
{
    return difftest::iface::origVmAt(entry, {a0, a1, a2, a3, t0});
}
extern "C" uint64_t nocturneInvokeBattleMovePackets(uint32_t entry, uint64_t startframe, uint64_t uniqueid, uint64_t form,
                                                    uint64_t target)
{
    return difftest::iface::origVmAt(entry, {startframe, uniqueid, form, target});
}
extern "C" uint64_t nocturneInvokeBattleTalkStep(uint32_t entry, uint64_t talk)
{
    return difftest::iface::origVmAt(entry, {talk});
}
extern "C" void nocturneInvokeBattleKoukaPlayer(uint32_t entry, uint64_t queue, uint64_t packet)
{
    difftest::iface::origVmVoidAt(entry, {queue, packet});
}

namespace difftest {

namespace {

using namespace nocturne::nb;
using iface::A;
using iface::I;
using iface::origVm;
using iface::origVmVoid;

// The queue is the data of the fake process 1 (dds3SearchProcessName's).
constexpr uint32_t kQueue = FW_TARSEL;

EffectQueue& queue() { return at<EffectQueue>(kQueue); }
uint32_t formAddress(int f) { return FW_FORMS + 0xf0u * static_cast<uint32_t>(f); }

// A random battle; the queue holds a few packets of earlier actions.
void koukaWorld(Gen& g)
{
    std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
    battleWorld(g);
    MainProcessData& main = at<MainProcessData>(FW_MAIN);
    main.EffectQueueProcessID = 1;
    main.press4_p = static_cast<int16_t>(g.range(0, 8));
    main.press4_ten = static_cast<int16_t>(g.range(0, 8));
    main.playerpcnt = static_cast<int16_t>(g.range(1, 4));
    main.enemypcnt = static_cast<int16_t>(g.range(1, 8));
    auto* forms = &at<Formation>(FW_FORMS);
    for (int f = 0; f < 14; ++f) {
        if (g.chance(60))
            forms[f].stat |= FormationStat::Present | (g.chance(70) ? FormationStat::CheckParty : 0u);
        forms[f].partyindex = static_cast<int16_t>(f);
        forms[f].r = nocturne::ee::Float::fromInt(g.range(10, 200));
    }
    EffectQueue& k = queue();
    std::memset(&k, 0, sizeof k);
    k.data.address = FW_MAIN;
    const int existing = g.range(0, 6);
    for (int i = 0; i < existing; ++i) {
        EffectPacket& p = addPacket(k, g.range(0, 60), g.range(0, 30), g.range(0, 3));
        static const int8_t types[] = {kSe, kSe2, kSe3, kNumberEff, kWordEff, kMotion, kUnitCol, kDamageMotion};
        p.type = g.pick(types);
        p.form.address = formAddress(g.range(0, 13));
        p.data1.setInt(g.chance(50) ? 0x10010 : g.pick<int32_t>({0x1000a, 0x10000, 5}));
        p.flag = static_cast<uint8_t>(g.below(256));
    }
}

int32_t frame(Gen& g) { return g.chance(10) ? g.range(-5, 0x9000) : g.range(0, 60); }
int32_t uid(Gen& g) { return g.range(0, 3); }
uint32_t someForm(Gen& g) { return g.chance(5) ? 0 : formAddress(g.range(0, 13)); }
uint32_t someFloat(Gen& g)
{
    return static_cast<uint32_t>(floatBits(g.chance(80) ? static_cast<float>(g.range(-40, 40)) / 4.0f : 1e6f));
}
uint32_t someVector(Gen& g)
{
    const uint32_t v = ps2PoolAllocate(16);
    for (uint32_t i = 0; i < 4; ++i)
        at<uint32_t>(v + 4 * i) = someFloat(g);
    return v;
}

Formation* F(uint32_t address) { return address ? &at<Formation>(address) : nullptr; }
uint64_t R(const void* p) { return norm(static_cast<int32_t>(iface::addr(p))); }
nocturne::ee::Float Fl(uint32_t bits) { return nocturne::ee::Float::fromBits(bits); }

// The acting unit's action data (FW_ACTION): its time list, and a ring of
// action processes for the sequence queries.
void actionWorld(Gen& g)
{
    ActionProcessData& act = at<ActionProcessData>(FW_ACTION);
    for (TimeList& t : act.timelist) {
        t.lockframe = static_cast<uint16_t>(g.chance(30) ? 0 : g.range(0, 90));
        t.endframe = static_cast<uint16_t>(g.chance(30) ? 0 : g.range(0, 120));
        t.hp = static_cast<uint16_t>(g.chance(30) ? 0 : g.range(0, 999));
    }
    act.seq = static_cast<int8_t>(g.range(0, 22));
    act.nextseq = static_cast<int8_t>(g.range(0, 22));
    act.hEffBTL = g.chance(50) ? 0 : static_cast<uint32_t>(g.rng());
    MainProcessData& main = at<MainProcessData>(FW_MAIN);
    if (g.chance(20))
        main.stat |= 0x20000;
    for (uint32_t& process : main.ActionProcessID) {
        process = 0;
        if (g.chance(70)) {
            const uint32_t data = ps2PoolAllocate(static_cast<int32_t>(sizeof(ActionProcessData)));
            at<ActionProcessData>(data).seq = static_cast<int8_t>(g.chance(40) ? g.range(18, 20) : g.range(-1, 22));
            process = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), 1, 0, 0, 0, 0, data));
        }
    }
    main.NowActionProcess = g.range(0, 3);
}

// The acting unit is in an occupied slot, and the battle is a (fake)
// process whose children the scripts become.
void scriptActor(Gen& g)
{
    ActionProcessData& a = at<ActionProcessData>(FW_ACTION);
    int f = g.range(0, 13);
    while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)))
        f = g.range(0, 13);
    a.form.address = formAddress(f);
    a.form->formindex = static_cast<int16_t>(f);
    a.party.address = FW_PARTY + 128u * static_cast<uint32_t>(f);
    a.work.address = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f));
    a.work->id = static_cast<uint16_t>(g.range(0, lastDevilWithAi()));
    a.adata = g.range(0, at<int32_t>(difftest::version::dataOrDie(0x004f0800) + 0x28) - 1);   // a procedure of the AI script
    a.stat = static_cast<uint32_t>(g.rng());
    auto* forms = &at<Formation>(FW_FORMS);
    for (int s = 0; s < 14; ++s)   // present party slots have units, as in the game
        if (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(forms[s].partyindex)))
            forms[s].stat &= ~FormationStat::CheckParty;
    std::memset(&forms[14], 0, 2 * sizeof(Formation));   // read past the array
    // (AI scripts have a message table, so starting one opens a window.)
    nocturne::mes::Manager& m = nocturne::mes::manager();
    std::memset(&m, 0, sizeof m);
    nocturne::itf::MiscLinkInit(m.list, iface::addr(m.nodes), 0x80, sizeof(nocturne::itf::LinkNode));
    MainProcessData& main = at<MainProcessData>(FW_MAIN);
    main.MainProcessID = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), g.range(1, 9), 0, 0, 0, 0, FW_MAIN));
    main.talkResult = g.chance(50) ? 0 : g.range(-2, 3);
    main.AiScriptProcessID = 0;
    if (g.chance(50))
        main.AiScriptProcessID = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), 2, 0, 0, 0, 0, FW_ACTION));
    else if (g.chance(30))
        main.AiScriptProcessID = 0x00777000;   // ended
}

using Body = std::function<Pair(Gen&)>;

// A system effect at `handle` (effBTLSystemHandle_t): mostly a family of the
// table's (an empty row now and then), its effect's cut ending at any frame.
void systemEffectWorld(Gen& g, uint32_t handle)
{
    constexpr uint32_t kEffects = 0x0077c000u, kCuts = 0x0077c800u;
    const uint32_t k = g.below(0x40);
    const uint32_t effect = kEffects + 0x10u * k, cut = kCuts + 0x20u * k;
    at<uint32_t>(effect + 8) = cut;
    at<nocturne::eff::BattleCut>(cut).cutEndFrame = g.chance(70) ? static_cast<uint32_t>(g.range(0, 200)) : static_cast<uint32_t>(g.rng());
    at<nocturne::eff::SystemEffect>(handle) = {g.range(0, 29), effect, formAddress(g.range(0, 13))};
}

} // namespace

void addKoukaTests(std::vector<TestCase>& t)
{
    auto add = [&](const char* name, Body body) {
        t.push_back({name, [body](Gen& g) {
                         koukaWorld(g);
                         return body(g);
                     }});
    };

    // ---- callees of the packets' runs ----
    add("effBTLSystemCut1Draw", [](Gen&) {
        return Pair{[] { return origVmVoid(0x001740a0, {FW_BTL_CUT}); }, [] { nocturne::eff::drawSystemCut(FW_BTL_CUT); return uint64_t{0}; }};
    });
    add("nbSetPlayerFormation", [](Gen& g) {
        const int32_t empty = g.range(0, 1);
        return Pair{[=] { return origVmVoid(0x0028b0a0, {FW_MAIN, I(empty)}); },
                    [=] { setPlayerFormation(at<MainProcessData>(FW_MAIN), empty); return uint64_t{0}; }};
    });

    // ---- the queue ----
    add("nbGetKoukaProcessData", [](Gen&) {
        return Pair{[] { return origVm(0x0025e8e0, {}); }, [] { return R(&effectQueue()); }};
    });
    add("nbGetUniqueIdKoukaPacketCnt", [](Gen& g) {
        const int32_t id = uid(g);
        return Pair{[=] { return origVm(0x0025e928, {I(id)}); }, [=] { return norm(countActionPackets(id)); }};
    });
    add("nbGetKoukaPacketTypeCnt", [](Gen& g) {
        const int8_t type = static_cast<int8_t>(g.pick<int32_t>({kSe, kNumberEff, kMotion, 0x7f, -1}));
        return Pair{[=] { return origVm(0x0025e978, {I(type)}); }, [=] { return norm(countPacketsOfType(type)); }};
    });
    add("UnlinkKoukaPacket", [](Gen& g) {
        if (!queue().first)
            addPacket(queue(), 1, 1, 1);
        EffectPacket* p = queue().first.get();
        for (int n = g.range(0, 5); n > 0 && p->next; --n)
            p = p->next.get();
        const uint32_t packet = iface::addr(p);
        return Pair{[=] { return origVmVoid(0x0025ea00, {kQueue, packet}); },
                    [=] { unlinkPacket(queue(), at<EffectPacket>(packet)); return uint64_t{0}; }};
    });
    add("nbLinkKoukaPacket", [](Gen& g) {   // a packet taken out, linked again at the end
        if (!queue().first)
            addPacket(queue(), 1, 1, 1);
        EffectPacket* p = queue().first.get();
        for (int n = g.range(0, 5); n > 0 && p->next; --n)
            p = p->next.get();
        unlinkPacket(queue(), *p);
        const uint32_t packet = iface::addr(p);
        return Pair{[=] { return origVmVoid(0x0025e9c8, {kQueue, packet}); },
                    [=] { linkPacket(queue(), at<EffectPacket>(packet)); return uint64_t{0}; }};
    });
    add("nbPanelStockFadeOut (0x27FA88)", [](Gen&) {
        return Pair{[] { return origVmVoid(0x0027fa88, {}); }, [] { startStockPanelFadeOut(); return uint64_t{0}; }};
    });
    add("nbAddKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x0025ea48, {kQueue, I(s), I(l), I(id)}); }, [=] { return R(&addPacket(queue(), s, l, id)); }};
    });
    // ---- deleting packets ----
    // Packets that own effects: skill cuts, hit effect parts, Ongyo-Ki's clones.
    auto effectPackets = [](Gen& g) {
        for (int n = g.range(1, 6); n > 0; --n) {
            EffectPacket& p = addPacket(queue(), g.range(0, 60), g.range(0, 30), uid(g));
            p.type = static_cast<int8_t>(g.pick<int32_t>({kSkillEffect, kSkillEffect2, kSkillEffect3, kSkillEffect1, kHitEff, kHitEff,
                                                          kOngyokiClone, kOngyokiClone2, kOngyokiOut, kOngyokiOut2, kNumberEff, kWordEff, 0x26, -3}));
            p.form.address = formAddress(g.range(0, 13));
            p.cuteff = g.chance(30) ? 0 : 0x00700000u + g.below(0x1000);
            p.data1.setInt(p.type == kHitEff ? g.range(0, 12) : static_cast<int32_t>(0x00710000u + g.below(0x1000)));
            p.data2.setInt(static_cast<int32_t>(0x00720000u + g.below(0x1000)));
        }
    };
    auto somePacket = [](Gen& g) {
        int n = static_cast<int>(g.below(static_cast<uint32_t>(queue().packetcnt)));
        EffectPacket* p = queue().first.get();
        while (n-- > 0 && p->next)
            p = p->next.get();
        return iface::addr(p);
    };
    add("DelKoukaPacket", [=](Gen& g) {
        effectPackets(g);
        const uint32_t p = somePacket(g);
        return Pair{[=] { return origVmVoid(0x0025eaf0, {kQueue, p}); },
                    [=] { deletePacketFrom(queue(), at<EffectPacket>(p)); return uint64_t{0}; }};
    });
    add("nbDelKoukaPacket", [=](Gen& g) {
        effectPackets(g);
        const uint32_t p = somePacket(g);
        return Pair{[=] { return origVmVoid(0x0025ec28, {p}); }, [=] { deletePacket(at<EffectPacket>(p)); return uint64_t{0}; }};
    });
    add("nbDelUniqueIdKoukaPacket", [=](Gen& g) {
        effectPackets(g);
        const int32_t id = uid(g);
        if (g.chance(10))
            at<MainProcessData>(FW_MAIN).EffectQueueProcessID = 0;
        return Pair{[=] { return origVmVoid(0x0025ec58, {I(id)}); }, [=] { deleteActionPackets(id); return uint64_t{0}; }};
    });
    add("nbDelAllKoukaPacketType", [=](Gen& g) {
        effectPackets(g);
        const int32_t type = g.pick<int32_t>({kSkillEffect, kHitEff, kNumberEff, kSe, 0x26, -3, kOngyokiOut});
        if (g.chance(10))
            at<MainProcessData>(FW_MAIN).EffectQueueProcessID = 0;
        return Pair{[=] { return origVmVoid(0x0025ecc0, {I(type)}); }, [=] { deletePacketsOfType(type); return uint64_t{0}; }};
    });
    add("nbDelAllMojiNumEffectKoukaPacket", [=](Gen& g) {
        effectPackets(g);
        const uint32_t form = someForm(g);
        if (g.chance(10))
            at<MainProcessData>(FW_MAIN).EffectQueueProcessID = 0;
        return Pair{[=] { return origVmVoid(0x0025ed28, {form}); }, [=] { deleteNumberWordPackets(F(form)); return uint64_t{0}; }};
    });
    add("nbOnOffKoukaPacketFlag", [](Gen& g) {
        const int32_t type = g.pick<int32_t>({kSe, kNumberEff, kMotion, kUnitCol});
        const uint32_t flag = g.below(256);
        const int32_t sw = g.range(0, 1);
        if (g.chance(10))
            at<MainProcessData>(FW_MAIN).EffectQueueProcessID = 0;
        return Pair{[=] { return origVmVoid(0x0025ee78, {I(type), flag, I(sw)}); },
                    [=] { setPacketTypeFlag(type, flag, sw); return uint64_t{0}; }};
    });
    add("nbCheckSePacket", [](Gen& g) {
        const int32_t start = g.range(0, 70), se = g.pick<int32_t>({0x10010, 0x1000a, 5, 7}), frames = g.range(0, 10);
        return Pair{[=] { return origVm(0x0025ef10, {I(start), I(se), I(frames)}); }, [=] { return norm(soundQueued(start, se, frames)); }};
    });

    // ---- builders: (startframe, uniqueid, ...) ----
    using P = EffectPacket&;
    auto plain = [&](const char* name, uint32_t entry, P (*rewrite)(int32_t, int32_t)) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g);
            return Pair{[=] { return origVm(entry, {I(s), I(id)}); }, [=] { return R(&rewrite(s, id)); }};
        });
    };
    plain("nbAddHatudoEffectEndPacket", 0x00261758, addPassiveEffectEndPacket);
    plain("nbAddSkillColorOffPacket", 0x00262430, addSkillColorOffPacket);
    plain("nbAddHitStopPacket", 0x00262e28, addHitStopPacket);
    plain("nbAddPanelStockFadeOutPacket", 0x00263628, addStockPanelFadeOutPacket);
    plain("nbAddPanelStockEndPacket", 0x00263678, addStockPanelEndPacket);

    auto onForm = [&](const char* name, uint32_t entry, P (*rewrite)(int32_t, int32_t, Formation*)) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g);
            const uint32_t f = someForm(g);
            return Pair{[=] { return origVm(entry, {I(s), I(id), f}); }, [=] { return R(&rewrite(s, id, F(f))); }};
        });
    };
    onForm("nbAddMotionStopPacket", 0x00261f30, addMotionStopPacket);
    onForm("nbAddMotionStopClearPacket", 0x00261f90, addMotionStopClearPacket);
    onForm("nbAddBadEffKaifukuPacket", 0x00262610, addAilmentCureEffectPacket);
    onForm("nbAddBadMotKaifukuPacket", 0x00262bb8, addAilmentMotionCurePacket);
    onForm("nbAddAnalyzePacket", 0x00262e78, addAnalyzePacket);
    onForm("nbAddFlyKoukaPacket", 0x002630a8, addFlyPacket);

    // (startframe, uniqueid, form, int)
    auto onFormInt = [&](const char* name, uint32_t entry, P (*rewrite)(int32_t, int32_t, Formation*, int32_t)) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g), n = g.chance(30) ? static_cast<int32_t>(g.rng()) : g.range(-2, 20);
            const uint32_t f = someForm(g);
            return Pair{[=] { return origVm(entry, {I(s), I(id), f, I(n)}); }, [=] { return R(&rewrite(s, id, F(f), n)); }};
        });
    };
    onFormInt("nbAddUnitHomeColKoukaPacket", 0x00261d20, addUnitColorHomePacket);
    onFormInt("nbAddUnitHomeAKoukaPacket", 0x00261e10, addUnitAlphaHomePacket);
    onFormInt("nbAddMotionKoukaPacket", 0x00261ff0, addMotionPacket);
    onFormInt("nbAddFormOnOffPacket", 0x00262fb8, addFormationShowPacket);
    onFormInt("nbAddDeadEventKoukaPacket", 0x00263350, addDeathEventPacket);
    add("nbAddBadMotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), bad = 1u << g.range(0, 12);
        return Pair{[=] { return origVm(0x00262260, {I(s), I(id), f, bad}); }, [=] { return R(&addAilmentMotionPacket(s, id, F(f), bad)); }};
    });
    // A hit effect: every kind (and some past them), the slot empty or not,
    // the effect of any family (its length any word).
    add("nbAddHitEffKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = formAddress(g.range(0, 13));
        at<Formation>(f).stat ^= g.chance(20) ? 1u : 0u;
        const uint32_t kind = g.chance(85) ? static_cast<uint32_t>(g.range(0, 10)) : static_cast<uint32_t>(g.range(-1, 14));
        for (uint32_t part = 0; part < 0x1e; ++part)
            systemEffectWorld(g, 0x00779400u + part * 0x10u);
        return Pair{[=] { return origVm(0x00262480, {I(s), I(id), f, kind}); }, [=] { return R(addHitEffectPacket(s, id, at<Formation>(f), kind)); }};
    });
    add("effBTLSystemGetLength", [](Gen& g) {
        constexpr uint32_t handle = 0x0077cf00u;
        systemEffectWorld(g, handle);
        return Pair{[=] { return origVm(0x00173ef0, {handle}); },
                    [=] { return norm(static_cast<int32_t>(nocturne::eff::systemEffectLength(at<nocturne::eff::SystemEffect>(handle)))); }};
    });
    {
        using F = nocturne::eff::SystemFamily;
        struct Family { const char* name; uint32_t entry; F family; };
        static const Family families[] = {
            {"effBTLSys_Shock_GetLength", 0x00170150, F::Shock}, {"effBTLSys_Freeze_GetLength", 0x001703a8, F::Freeze},
            {"effBTLSys_Sleep_GetLength", 0x00170590, F::Sleep}, {"effBTLSys_Panic_GetLength", 0x00170778, F::Panic},
            {"effBTLSys_Bind_GetLength", 0x00170960, F::Bind}, {"effBTLSys_Close_GetLength", 0x00170c00, F::Mute},
            {"effBTLSys_Poison_GetLength", 0x00170e00, F::Poison}, {"effBTLSys_Charm_GetLength", 0x00171060, F::Charm},
            {"effBTLSys_Paralyze_GetLength", 0x00171268, F::Stun}, {"effBTLSys_Fly_GetLength", 0x001713d0, F::Fly},
            {"effBTLSys_Stone_GetLength", 0x00171578, F::Stone}, {"effBTLSys_Curse_GetLength", 0x00171728, F::Curse},
            {"effBTLSys_CurseCAMP_GetLength", 0x00171978, F::CurseCamp},
            {"effBTLSys_Stone_Dead_GetLength", 0x00171c40, F::StoneShatter},
            {"effBTLSys_Hansya_GetLength", 0x001720f0, F::Repel}, {"effBTLSys_Kyusyuu_GetLength", 0x00172590, F::Drain},
            {"effBTLSys_Return_GetLength", 0x00172718, F::Return}, {"effBTLSys_Attack_GetLength", 0x00172d18, F::Attack},
            {"effBTLSys_AttackC_GetLength", 0x001735e0, F::AttackC},
            {"effBTLSys_Encount_GetLength", 0x00173768, F::Encounter},
            {"effBTLSys_Nego_Kaihuku_GetLength", 0x001738f8, F::TalkHeal},
            {"effBTLSys_Nego_Kyusyu_GetLength", 0x00173a88, F::TalkDrain},
            {"effBTLSys_Nego_Stone_GetLength", 0x00173c18, F::TalkStone},
        };
        for (const Family& f : families)
            add(f.name, [f](Gen& g) {
                constexpr uint32_t handle = 0x0077cf00u;
                systemEffectWorld(g, handle);
                const uint32_t effect = at<nocturne::eff::SystemEffect>(handle).effect;
                return Pair{[=] { return origVm(f.entry, {effect}); },
                            [=] { return norm(static_cast<int32_t>(nocturne::eff::familyLength(f.family, effect))); }};
            });
    }
    add("nbAddBadEffKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), bad = g.chance(80) ? 1u << g.range(0, 12) : g.below(0x1000);
        return Pair{[=] { return origVm(0x00262670, {I(s), I(id), f, bad}); }, [=] { return R(&addAilmentEffectPacket(s, id, F(f), bad)); }};
    });

    // (startframe, uniqueid, form, int, int)
    auto onForm2 = [&](const char* name, uint32_t entry, auto rewrite) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g), a = static_cast<int32_t>(g.rng()), b = g.range(-2, 20);
            const uint32_t f = someForm(g);
            return Pair{[=] { return origVm(entry, {I(s), I(id), f, I(a), I(b)}); },
                        [=] { return R(&rewrite(s, id, F(f), static_cast<uint32_t>(a), b)); }};
        });
    };
    onForm2("nbAddUnitColKoukaPacket", 0x00261ca0, addUnitColorPacket);
    onForm2("nbAddUnitAKoukaPacket", 0x00261d90, addUnitAlphaPacket);
    onForm2("nbAddHpMpKoukaPacket", 0x002629e8, [](int32_t s, int32_t id, Formation* f, uint32_t n, int32_t type) -> P {
        return addHpMpPacket(s, id, f, static_cast<int32_t>(n), type);
    });
    onForm2("nbAddBadStatKoukaPacket", 0x00262b38, addAilmentPacket);
    onForm2("nbAddHojoKoukaPacket", 0x002634c8, [](int32_t s, int32_t id, Formation* f, uint32_t type, int32_t point) -> P {
        return addBuffPacket(s, id, f, type, point);
    });
    add("nbAddFormFlagOnOffPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), sw = g.range(0, 1);
        const uint32_t f = someForm(g), flag = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x00263028, {I(s), I(id), f, I(sw), flag}); },
                    [=] { return R(&addFormationFlagPacket(s, id, F(f), sw, flag)); }};
    });

    // (startframe, uniqueid, int [, int])
    auto ints = [&](const char* name, uint32_t entry, auto rewrite, int count) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g), a = g.range(-5, 0x20000), b = g.range(-5, 100), c = g.range(-5, 100);
            return Pair{[=] {
                            return count == 1 ? origVm(entry, {I(s), I(id), I(a)})
                                 : count == 2 ? origVm(entry, {I(s), I(id), I(a), I(b)})
                                              : origVm(entry, {I(s), I(id), I(a), I(b), I(c)});
                        },
                        [=] { return R(&rewrite(s, id, a, b, c)); }};
        });
    };
    ints("nbAddSkillNamePacket", 0x00262f58, [](int32_t s, int32_t id, int32_t a, int32_t, int32_t) -> P { return addSkillNamePacket(s, id, a); }, 1);
    ints("nbAddFlareChargePacket", 0x00263548, [](int32_t s, int32_t id, int32_t a, int32_t, int32_t) -> P { return addFlareChargePacket(s, id, a); }, 1);
    ints("nbAddFadeOutKoukaPacket", 0x002633e8, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P { return addFadeOutPacket(s, id, a, b); }, 2);
    ints("nbAddFadeInKoukaPacket", 0x00263458, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P { return addFadeInPacket(s, id, a, b); }, 2);
    ints("nbAddSkillColorPacket", 0x002623c0, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P { return addSkillColorPacket(s, id, a, b); }, 2);
    ints("nbAddHomeRotKoukaPacket", 0x00261c30, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P { return addTurnHomePacket(s, id, a, b); }, 2);
    ints("nbAddNewPressPacket", 0x00262ac8, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P {
        return addPressResultPacket(s, id, static_cast<int16_t>(a), static_cast<int16_t>(b));
    }, 2);
    ints("nbAddSummonKoukaPacket", 0x00262340, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t c) -> P {
        return addSummonPacket(s, id, static_cast<int16_t>(a), static_cast<int16_t>(b), static_cast<int16_t>(c));
    }, 3);
    ints("nbAddPadShockPacket", 0x002635a8, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t c) -> P {
        return addPadShockPacket(s, id, static_cast<int16_t>(a), static_cast<int16_t>(b), static_cast<int16_t>(c));
    }, 3);
    ints("nbAddJyokyoHelpPacket", 0x00262ed8, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t c) -> P {
        return addStatusMessagePacket(s, id, static_cast<int16_t>(a), static_cast<int16_t>(b), c);
    }, 3);

    // (startframe, framelength, uniqueid, ...)
    add("nbAddSkillEffectKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g);
        const uint32_t c = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x00261500, {I(s), I(l), I(id), c}); }, [=] { return R(&addSkillEffectPacket(s, l, id, c)); }};
    });
    add("nbAddSkillEffectKoukaPacket1", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g);
        const uint32_t c = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x002616e8, {I(s), I(l), I(id), c}); }, [=] { return R(&addSkillEffectPacket1(s, l, id, c)); }};
    });
    add("nbAddSkillEffectKoukaPacket2", [](Gen& g) {
        const int32_t s = frame(g), l = g.chance(30) ? 0 : frame(g), id = uid(g);
        const uint32_t h = static_cast<uint32_t>(g.rng()), f = someForm(g);
        const int16_t cut = static_cast<int16_t>(g.range(-2, 40)), j = static_cast<int16_t>(g.range(-2, 40));
        return Pair{[=] { return origVm(0x00261638, {I(s), I(l), I(id), h, I(cut), f, I(j)}); },
                    [=] { return R(&addSkillEffectPacket2(s, l, id, h, cut, F(f), j)); }};
    });
    add("nbAddNumEffKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g), n = g.range(-5, 9999), n2 = g.range(-5, 999), type = g.range(0, 5);
        const uint32_t f = g.chance(50) && queue().first ? queue().first->form.address : someForm(g);
        return Pair{[=] { return origVmVoid(0x002627c0, {I(s), I(l), I(id), f, I(n), I(n2), I(type)}); },
                    [=] { addNumberPacket(s, l, id, F(f), n, n2, type); return uint64_t{0}; }};
    });
    add("nbAddMojiEffKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g), type = g.range(0, 6);
        const uint32_t f = g.chance(50) && queue().first ? queue().first->form.address : someForm(g);
        return Pair{[=] { return origVmVoid(0x002628d0, {I(s), I(l), I(id), f, I(type)}); },
                    [=] { addWordPacket(s, l, id, F(f), type); return uint64_t{0}; }};
    });

    // floats in f12
    add("nbAddTargetMoveKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), party = g.range(-1, 13);
        const uint32_t v = someVector(g), speed = someFloat(g);
        return Pair{[=] { return origVm(0x00261aa0, {I(s), I(id), I(party), v}, {speed}); },
                    [=] { return R(&addMoveToTargetPacket(s, id, party, at<Vec4>(v), Fl(speed))); }};
    });
    add("nbAddHomeMoveKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), party = g.range(-1, 13);
        const uint32_t speed = someFloat(g);
        return Pair{[=] { return origVm(0x00261b30, {I(s), I(id), I(party)}, {speed}); },
                    [=] { return R(&addMoveHomePacket(s, id, party, Fl(speed))); }};
    });
    add("nbAddRotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), party = g.range(-1, 13), speed = g.range(0, 30);
        const uint32_t v = someVector(g);
        return Pair{[=] { return origVm(0x00261ba0, {I(s), I(id), I(party), v, I(speed)}); },
                    [=] { return R(&addTurnPacket(s, id, party, at<Vec4>(v), speed)); }};
    });
    add("nbAddSkillMotionKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const int16_t motion = static_cast<int16_t>(g.range(0, 40)), end = static_cast<int16_t>(g.range(0, 3));
        const uint32_t f = someForm(g), ritu = someFloat(g);
        return Pair{[=] { return origVm(0x00262060, {I(s), I(id), f, I(motion), I(end)}, {ritu}); },
                    [=] { return R(&addSkillMotionPacket(s, id, F(f), motion, end, Fl(ritu))); }};
    });
    add("nbAddDmgMotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), week = g.range(-1, 1);
        const uint32_t f = someForm(g), range = someFloat(g);
        return Pair{[=] { return origVm(0x002620f0, {I(s), I(id), f, I(week)}, {range}); },
                    [=] { return R(&addDamageMotionPacket(s, id, F(f), Fl(range), week)); }};
    });
    add("nbAddEasyDmgMotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), range = someFloat(g);
        return Pair{[=] { return origVm(0x00262170, {I(s), I(id), f}, {range}); },
                    [=] { return R(&addLightDamageMotionPacket(s, id, F(f), Fl(range))); }};
    });
    add("nbAddBadDmgMotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), range = someFloat(g), bad = 1u << g.range(0, 12);
        return Pair{[=] { return origVm(0x002621e0, {I(s), I(id), f, bad}, {range}); },
                    [=] { return R(&addAilmentDamageMotionPacket(s, id, F(f), Fl(range), bad)); }};
    });
    add("nbAddPressPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t press = someFloat(g);
        return Pair{[=] { return origVm(0x00262a68, {I(s), I(id)}, {press}); }, [=] { return R(&addPressPacket(s, id, Fl(press))); }};
    });

    // sounds
    auto sound = [&](const char* name, uint32_t entry, EffectPacket* (*rewrite)(int32_t, int32_t, uint32_t)) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g);
            const uint32_t se = g.pick<uint32_t>({0x10010, 0x1000a, 5, 7});
            return Pair{[=] { return origVm(entry, {I(s), I(id), se}); }, [=] { return R(rewrite(s, id, se)); }};
        });
    };
    sound("nbAddSePacket", 0x00262cc0, addSoundPacket);
    sound("nbAddSePacket2", 0x00262d38, addSoundPacket2);
    sound("nbAddSePacket3", 0x00262db0, addSoundPacket3);

    // units and parties
    add("nbAddSakeKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = formAddress(g.range(0, 13));
        if (g.chance(20))
            at<Formation>(f).r = nocturne::ee::Float::fromInt(g.range(100, 200));
        return Pair{[=] { return origVm(0x00261e80, {I(s), I(id), f}); }, [=] { return R(&addDodgePacket(s, id, at<Formation>(f))); }};
    });
    add("nbAddDeadPcmPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = formAddress(g.range(0, 13));
        return Pair{[=] { return origVm(0x00262c18, {I(s), I(id), f}); }, [=] { return R(addDeathVoicePacket(s, id, at<Formation>(f))); }};
    });
    add("nbAddReturnKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), dead = g.range(0, 1);
        const uint32_t party = FW_PARTY + 128u * g.below(14);
        return Pair{[=] { return origVm(0x002622d0, {I(s), I(id), party, I(dead)}); },
                    [=] { return R(&addReturnPacket(s, id, &at<Party>(party), dead)); }};
    });

    // ---- whole events ----
    add("nbMakeSummonPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const int16_t side = static_cast<int16_t>(g.range(0, 1)), stock = static_cast<int16_t>(g.range(0, 11)),
                      f = static_cast<int16_t>(g.range(0, 13));
        return Pair{[=] { return origVm(0x002636c8, {I(s), I(id), I(side), I(stock), I(f)}); },
                    [=] { return norm(makeSummonPackets(s, id, side, stock, f)); }};
    });
    add("nbMakeReturnPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t party = FW_PARTY + 128u * g.below(14);
        return Pair{[=] { return origVm(0x00263778, {I(s), I(id), party}); }, [=] { return norm(makeReturnPackets(s, id, at<Party>(party))); }};
    });
    add("nbMakeUnitFadeInPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), d = g.range(0, 20), a = g.range(0, 20), c = g.range(0, 20);
        const uint32_t f = someForm(g), col = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x00263810, {I(s), I(id), f, col, I(d), I(a), I(c)}); },
                    [=] { return norm(makeFadeInPackets(s, id, F(f), col, d, a, c)); }};
    });
    add("nbMakeUnitFadeOutPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), d = g.range(0, 20), c = g.range(0, 20), a = g.range(0, 20);
        const uint32_t f = someForm(g), col = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x002638a0, {I(s), I(id), f, col, I(d), I(c), I(a)}); },
                    [=] { return norm(makeFadeOutPackets(s, id, F(f), col, d, c, a)); }};
    });
    add("nbMakeDeadPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), chk = g.range(0, 2);
        // A present slot has a unit (through its own formindex), as in the game.
        // (and through its party, partyindex = the slot here)
        auto unitOf = [](int slot) {
            return at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(at<Formation>(formAddress(slot)).formindex)) &&
                   at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(slot));
        };
        int f = g.range(0, 13);
        for (int tries = 0; tries < 20 && !unitOf(f); ++tries)
            f = g.range(0, 13);
        if (!unitOf(f))
            at<Formation>(formAddress(f)).stat &= ~FormationStat::Present;
        const uint32_t form = formAddress(f);
        return Pair{[=] { return origVm(0x002641f8, {I(s), I(id), form, I(chk)}); },
                    [=] { return norm(makeDeathPackets(s, id, at<Formation>(form), chk)); }};
    });
    struct DeadCheck {
        const char* name;
        uint32_t entry;
        int32_t (*rewrite)(const Formation&);
    };
    static const DeadCheck deadChecks[] = {
        {"nbCheckEventDead", 0x00259ab0, [](const Formation& f) { return diesByEvent(f) ? 1 : 0; }},
        {"nbCheckDeadScript", 0x00259b10, hasDeathScript},
        {"nbCheckDeadEvent", 0x00259b70, hasDeathEvent},
    };
    for (const DeadCheck& d : deadChecks) {
        const uint32_t entry = d.entry;
        auto rewrite = d.rewrite;
        add(d.name, [=](Gen& g) {
            int f = g.range(0, 13);   // a slot with a unit
            for (int tries = 0; tries < 50 && !at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(at<Formation>(formAddress(f)).formindex)); ++tries)
                f = g.range(0, 13);
            const uint32_t form = formAddress(f);
            if (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(at<Formation>(form).formindex)))
                return Pair{[] { return uint64_t{0}; }, [] { return uint64_t{0}; }};
            if (g.chance(50))   // a devil that has a death script or event
                at<nocturne::UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(at<Formation>(form).formindex))).id =
                    g.pick<uint16_t>({0x100, 0x102, 0x10a, 0x10b, 0x114, 0x120});
            return Pair{[=] { return origVm(entry, {form}); }, [=] { return norm(rewrite(at<Formation>(form))); }};
        });
    }
    // ---- the time list and state of the acting unit ----
    auto action = [&](const char* name, std::function<Pair(Gen&)> body) {
        add(name, [=](Gen& g) {
            actionWorld(g);
            return body(g);
        });
    };
    auto act = [] { return std::ref(at<ActionProcessData>(FW_ACTION)); };
    action("ClearTimeList", [=](Gen&) {
        return Pair{[] { return origVmVoid(0x002514f0, {FW_ACTION}); }, [=] { clearTimeList(act()); return uint64_t{0}; }};
    });
    action("CheckAction_NON", [=](Gen& g) {
        scriptActor(g);
        ActionProcessData& a = act();
        a.type = g.chance(50) ? 0 : g.range(1, 6);
        a.target = g.range(0, 13);
        a.party->flag = static_cast<int16_t>((a.party->flag & ~0x10e) | (g.chance(15) ? 8 : 0) | (g.chance(50) ? 2 : 0) |
                                             (g.chance(20) ? 4 : 0) | (g.chance(30) ? 0x100 : 0));
        a.work->badstat = static_cast<uint16_t>(g.pick<int32_t>({0, 0, 0, 1, 2, 4, 8, 0x10, 0x20, 0x80, 0x400, 0x800}));
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.stat ^= g.chance(30) ? 0x10000000u : 0u;
        at<int32_t>(difftest::version::dataOrDie(0x0054e824)) = g.chance(30) ? 1 : 0;   // the debug pad
        return Pair{[] { return origVm(0x00253490, {FW_ACTION}); }, [=] { return norm(updateNone(act())); }};
    });
    action("SetHpForTimeList", [=](Gen&) {
        auto* forms = &at<Formation>(FW_FORMS);
        for (int f = 0; f < 14; ++f)   // present party slots have units, as in the game
            if (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(forms[f].partyindex)))
                forms[f].stat &= ~FormationStat::CheckParty;
        // (slots 14 and 15 are read past the array; keep them empty)
        std::memset(&at<Formation>(formAddress(14)), 0, 2 * sizeof(Formation));
        return Pair{[] { return origVmVoid(0x00251538, {FW_ACTION}); }, [=] { initTimeListHp(act()); return uint64_t{0}; }};
    });
    struct Getter {
        const char* name;
        uint32_t entry;
        int32_t (*rewrite)(ActionProcessData&, int32_t);
    };
    static const Getter getters[] = {
        {"GetTimeListHp", 0x002515d8, timeListHp},
        {"GetUnlockTime", 0x00251750, freeFrame},
        {"GetEndTime", 0x00251760, doneFrame},
        {"CheckTimeListDead", 0x002515e8, [](ActionProcessData& a, int32_t f) { return timeListDead(a, f) ? 1 : 0; }},
        {"CheckTimeListDeadEnemyParty", 0x00251628,
         [](ActionProcessData& a, int32_t f) { return otherSideAllDead(a, f) ? 1 : 0; }},
    };
    for (const Getter& d : getters) {
        const uint32_t entry = d.entry;
        auto rewrite = d.rewrite;
        action(d.name, [=](Gen& g) {
            const int32_t f = g.range(0, 13);
            if (g.chance(50)) {   // the other side all down, but perhaps one
                for (TimeList& t : act().get().timelist)
                    t.hp = 0;
                if (g.chance(70)) {
                    const int32_t alive = f < 4 ? (g.chance(50) ? 13 : g.range(4, 13)) : (g.chance(50) ? 3 : g.range(0, 3));
                    act().get().timelist[alive].hp = static_cast<uint16_t>(g.range(1, 99));
                    at<Formation>(formAddress(alive)).stat |= FormationStat::Present;
                }
            }
            return Pair{[=] { return origVm(entry, {FW_ACTION, I(f)}); }, [=] { return norm(rewrite(act(), f)); }};
        });
    }
    action("nbAddTimeListHp", [=](Gen& g) {
        const int32_t f = g.range(0, 31), amount = g.range(-1200, 1200);
        return Pair{[=] { return origVm(0x002516e8, {FW_ACTION, I(f), I(amount)}); },
                    [=] { return norm(addTimeListHp(act(), f, amount)); }};
    });
    action("AddTimeListHp", [=](Gen& g) {
        const int32_t f = g.range(0, 31), amount = g.range(-1200, 1200);
        return Pair{[=] { return origVmVoid(0x00251738, {FW_ACTION, I(f), I(amount)}); },
                    [=] { addTimeListHpAt(act(), f, amount); return uint64_t{0}; }};
    });
    action("OverwriteTimeList", [=](Gen& g) {
        const int32_t f = g.range(0, 31), s = g.range(0, 90), lock = g.range(-2, 60), end = g.range(-2, 90);
        return Pair{[=] { return origVmVoid(0x00251770, {FW_ACTION, I(f), I(s), I(lock), I(end)}); },
                    [=] { overwriteTimeList(act(), f, s, lock, end); return uint64_t{0}; }};
    });
    action("SetTimeList", [=](Gen& g) {
        const int32_t f = g.range(0, 31), s = g.range(0, 90), lock = g.range(-2, 60), end = g.range(-2, 90);
        return Pair{[=] { return origVmVoid(0x002517e0, {FW_ACTION, I(f), I(s), I(lock), I(end)}); },
                    [=] { setTimeList(act(), f, s, lock, end); return uint64_t{0}; }};
    });
    action("GetAllEndTime", [=](Gen&) {
        return Pair{[] { return origVm(0x00251858, {FW_ACTION}); }, [=] { return norm(lastDoneFrame(act())); }};
    });
    action("GetAllUnlockTime", [=](Gen&) {
        return Pair{[] { return origVm(0x00251890, {FW_ACTION}); }, [=] { return norm(lastFreeFrame(act())); }};
    });
    action("nbGetActionSeq", [](Gen& g) {
        const uint32_t process = g.chance(10) ? 0 : at<MainProcessData>(FW_MAIN).ActionProcessID[g.below(4)];
        return Pair{[=] { return origVm(0x00257bf8, {process}); }, [=] { return norm(actionState(process)); }};
    });
    action("nbGetPrevActionSeq", [](Gen&) {
        return Pair{[] { return origVm(0x00257c20, {}); }, [] { return norm(previousActionState()); }};
    });
    action("SetNextActionSeq", [=](Gen& g) {
        const int32_t next = g.range(-1, 23);
        return Pair{[=] { return origVmVoid(0x00257cc8, {FW_ACTION, I(next)}); }, [=] { setNextState(act(), next); return uint64_t{0}; }};
    });
    struct State {
        const char* name;
        uint32_t entry;
        int32_t (*rewrite)(ActionProcessData&);
        bool result;
    };
    static const State states[] = {
        {"SetAction_NON", 0x00253488, [](ActionProcessData& a) { enterNone(a); return 0; }, false},
        {"CheckAction_AI", 0x00253c20, updateAi, true},
        {"SetAction_INVISIBLE", 0x00257460, [](ActionProcessData& a) { enterInvisible(a); return 0; }, false},
        {"CheckAction_INVISIBLE", 0x00257468, updateInvisible, true},
        {"SetAction_CHECK3", 0x00257a68, [](ActionProcessData& a) { enterPlayOut(a); return 0; }, false},
        {"CheckAction_CHECK3", 0x00257a70, updatePlayOut, true},
        {"SetAction_ATO", 0x00257ab8, [](ActionProcessData& a) { enterCleanup(a); return 0; }, false},
        {"CheckAction_ATO", 0x00257ac0, updateCleanup, true},
        {"CheckAction_END", 0x00257bf0, updateEnd, true},
    };
    auto script = [&](const char* name, std::function<Pair(Gen&)> body) {
        action(name, [=](Gen& g) {
            scriptActor(g);
            return body(g);
        });
    };
    // The battle script commands, run by an AI or event script.
    struct BattleCommand { const char* name; uint32_t original; int32_t (*rewrite)(); };
    static const BattleCommand kBattleCommands[] = {
        {"nbCommand_BTL_CAM_1SHOT", 0x00288a58, ai::script::cameraOneShot},
        {"nbCommand_BTL_CAM_BOUGAI", 0x00288a88, ai::script::cameraObstruct},
        {"nbCommand_BTL_PNL_OFF", 0x00288ab0, ai::script::panelOff},
        {"nbCommand_BTL_EVENT", 0x00288ae0, ai::script::startEvent},
        {"nbCommand_BTL_PRESS", 0x00288ba0, ai::script::pressTalk},
        {"nbCommand_BTL_TAIKYO", 0x00288b20, ai::script::leaveTalk},
        {"nbCommand_BTL_ALLTAIKYO", 0x00288b60, ai::script::allLeaveTalk},
        {"nbCommand_BTL_FORM_PLY_ON", 0x00288c40, ai::script::showPlayerFormations},
        {"nbCommand_BTL_CAM_2SHOT", 0x00288a80, ai::script::cameraTwoShot},
        {"nbCommand_BTL_NAKAMA", 0x00288be0, ai::script::joinTalk},
        {"nbCommand_BTL_FORM_ALL_ON", 0x00288c20, ai::script::showAllFormations},
        {"nbCommand_BTL_FORM_ENE_ON", 0x00288c68, ai::script::showEnemyFormations},
        {"nbCommand_BTL_AI_CHANGE_OFF", 0x00288d10, ai::script::lockAi},
        {"nbCommand_BTL_AI_CHANGE_ON", 0x00288d48, ai::script::unlockAi},
    };
    for (const BattleCommand& c : kBattleCommands) {
        const BattleCommand* command = &c;
        script(command->name, [=](Gen& g) {
            scriptWork();
            scriptParam(0, g.range(-1, 300));
            at<MainProcessData>(FW_MAIN).stat ^= g.chance(50) ? 0x40000u : 0u;
            act().get().talkType = g.range(0, 6);
            const uint32_t original = command->original;
            auto rewrite = command->rewrite;
            return Pair{[=] { return origVm(original, {}); }, [=] { return norm(rewrite()); }};
        });
    }
    script("nbInitAiScript", [=](Gen& g) {
        // (any procedure the version's AI script has: its section 0's count)
        const int32_t procedures = at<int32_t>(difftest::version::dataOrDie(0x004f0800) + 0x28);
        const int32_t procedure = g.range(0, procedures - 1);
        return Pair{[=] { return origVmVoid(0x00288d80, {FW_ACTION, I(procedure)}); },
                    [=] { ai::script::start(act(), procedure); return uint64_t{0}; }};
    });
    // (The camera is in the executable's data, which the harness doesn't
    // compare: return its state.)
    auto camera = [] { return std::ref(at<Camera>(difftest::version::dataOrDie(0x00320e40))); };
    auto cameraState = [=] { return uint64_t{camera().get().state_change} | uint64_t{camera().get().state} << 32; };
    script("nbCameraSetState", [=](Gen& g) {
        const uint16_t state = static_cast<uint16_t>(g.chance(20) ? 25 : g.range(0, 29));
        camera().get().state = g.range(1, 9);
        return Pair{[=] { origVmVoid(0x001b1740, {state}); return cameraState(); },
                    [=] { setCameraState(state); return cameraState(); }};
    });
    // An ailing actor: any ailment, sometimes cursed; a status line maybe
    // pending; any point of its wait.
    auto ailingWorld = [=](Gen& g) {
            ActionProcessData& a = act();
            UnitWork& unit = *a.work;
            unit.badstat = static_cast<uint16_t>(
                (g.chance(15) ? 0 : 1u << g.range(0, 11)) | (g.chance(30) ? nocturne::kBadStatCurse : 0));
            unit.nowcommand = static_cast<int16_t>(g.range(-1, 11));
            // (a chosen skill or item is never index 0, whose name is Japanese)
            unit.nowindex = static_cast<uint16_t>(unit.nowcommand == 5 ? 1 + unit.nowindex % 0x9f : unit.nowindex ? unit.nowindex : 1);
            unit.flag = (unit.flag & ~0x24u) | g.pick<uint32_t>({0, 4, 0x20});
            a.seqtime = static_cast<uint16_t>(g.chance(30) ? 5 : g.chance(50) ? g.range(0, 50) : g.pick<int32_t>({0, 30, 31, 40, 41, 100}));
            MainProcessData& main = at<MainProcessData>(FW_MAIN);
            main.endtype = g.chance(50) ? 3 : g.range(0, 4);
            main.esccnt = static_cast<uint8_t>(g.chance(10) ? 0xff : g.range(0, 5));
            main.TalkProcessID = g.chance(50) ? 0 : 0x00777000;
            main.talkResult = g.range(0, 9);
            unit.maxhp = static_cast<uint16_t>(g.range(1, 999));
            if (g.chance(20))
                nocturne::dat::globalWork().units[0].badstat = static_cast<uint16_t>(g.chance(50) ? 0x800 : 0);
            const iface::HelpWorld help = iface::helpWorld(g);
            a.statusMessage = g.chance(40) ? 0 : g.chance(10) ? -1 : help.messages[g.below(static_cast<uint32_t>(help.messages.size()))];
            a.statusVarType = g.range(-1, 2);
            a.statusVarValue = g.range(0, 0x17f);
            at<MainProcessData>(FW_MAIN).statusMessageTable = help.id;
            if (g.chance(50))
                at<MainProcessData>(FW_MAIN).stat ^= 8;
            camera().get().state_change = 0xffff;
            for (int f = 0; f < 14; ++f)   // (a formation's index is its slot, as in the game)
                at<Formation>(formAddress(f)).formindex = static_cast<int16_t>(f);
    };
    auto ailing = [&, camera, cameraState, ailingWorld](const char* name, uint32_t entry, int32_t (*rewrite)(ActionProcessData&), bool result) {
        script(name, [=](Gen& g) {
            ailingWorld(g);
            // (void states: the camera state they asked for)
            return Pair{[=] {
                            const uint64_t r = result ? origVm(entry, {FW_ACTION}) : origVmVoid(entry, {FW_ACTION});
                            return result ? r : cameraState();
                        },
                        [=] {
                            const int32_t r = rewrite(act());
                            return result ? norm(r) : cameraState();
                        }};
        });
    };
    // ---- entering states and the per-frame driver ----
    // States whose code runs in this world (others call original code the
    // test can't run).
    static const int32_t kEnterable[] = {0, 3, 11, 12, 13, 14, 15, 19, 20, 21, 22};
    static const int32_t kCheckable[] = {3, 4, 9, 10, 11, 12, 13, 14, 15, 19, 20, 21, 22};
    script("SetActionSeq", [=](Gen& g) {
        ailingWorld(g);
        const int32_t seq = g.pick(kEnterable);
        act().get().nextseq = static_cast<int8_t>(g.range(0, 22));
        act().get().seqcnt = g.range(0, 9);
        return Pair{[=] { origVmVoid(0x00257c80, {FW_ACTION, I(seq)}); return cameraState(); },
                    [=] { enterState(act(), seq); return cameraState(); }};
    });
    script("nbActionProcess1", [=](Gen& g) {
        ailingWorld(g);
        ActionProcessData& a = act();
        a.stat = (a.stat & ~0x442u) | (g.chance(40) ? 2u : 0u) | (g.chance(10) ? 0x40u : 0u) | (g.chance(20) ? 0x400u : 0u);
        a.seq = static_cast<int8_t>(g.chance(25) ? kActionReady : g.pick(kCheckable));
        a.nextseq = static_cast<int8_t>(g.chance(30) ? kActionReady : g.pick(kEnterable));
        if (g.chance(10))
            a.seqtime = 0xffff;
        if (a.stat & 2 && a.seq == kActionReady)
            a.seq = static_cast<int8_t>(g.pick(kCheckable));
        // (READY's own functions aren't rewritten; both sides reach fakes of them.)
        at<uint32_t>(difftest::version::dataOrDie(0x005519c8)) = g.chance(20) ? 1u : 0u;   // a streamed voice playing
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        for (uint32_t& p : main.ActionProcessID)
            p = 0;
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), 3, 0, 0, 0, 0, FW_ACTION));
        main.NowActionProcess = g.range(0, 3);
        if (g.chance(70)) {   // the action before this one
            const uint32_t data = ps2PoolAllocate(static_cast<int32_t>(sizeof(ActionProcessData)));
            at<ActionProcessData>(data).seq = static_cast<int8_t>(g.range(-1, 22));
            main.ActionProcessID[main.NowActionProcess == 0 ? 3 : main.NowActionProcess - 1] =
                static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), 1, 0, 0, 0, 0, data));
        }
        return Pair{[=] { const uint64_t r = origVm(0x00257cd0, {process}); return r ^ cameraState() << 8; },
                    [=] { return norm(runActionProcess(process)) ^ cameraState() << 8; }};
    });
    ailing("CheckAction_BAD", 0x00253e00, updateAilment, true);
    ailing("SetAction_BADWAIT", 0x00254010, [](ActionProcessData& a) { enterAilmentWait(a); return 0; }, false);
    ailing("CheckAction_BADWAIT", 0x00254058, updateAilmentWait, true);
    ailing("SetAction_WAIT", 0x002570b8, [](ActionProcessData& a) { enterWait(a); return 0; }, false);
    ailing("CheckAction_WAIT", 0x00257210, updateWait, true);
    ailing("SetAction_ESCAPE", 0x00257230, [](ActionProcessData& a) { enterEscape(a); return 0; }, false);
    ailing("CheckAction_ESCAPE", 0x002572c0, updateEscape, true);
    ailing("SetAction_RETURN", 0x002573a8, [](ActionProcessData& a) { enterReturn(a); return 0; }, false);
    ailing("CheckAction_RETURN", 0x00257440, updateReturn, true);
    ailing("CheckAction_NEGO", 0x00256b88, updateTalk, true);
    ailing("CheckAction_NEGORESULT", 0x00257098, updateTalkResult, true);
    // ---- an action's results ----
    auto occupied = [](Gen& g) {
        int f = g.range(0, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)))
            f = g.range(0, 13);
        return f;
    };
    auto pressBits = [](Gen& g) {
        return g.pick<uint32_t>({0, 0xbf000000, 0xbf800000, 0xc0000000, 0xc1200000, 0x3f000000, 0x3f800000, 0xbfc00000});
    };
    // The action's results so far.
    auto results = [=](Gen& g) {
        ActionProcessData& a = act();
        a.press = nocturne::ee::Float::fromBits(pressBits(g));
        a.newpresstype = g.range(-1, 17);
        a.hitstopframe = g.chance(40) ? 0 : g.range(1, 60);
        a.newaddpresstype = 0;
        a.form->motionend = static_cast<int16_t>(g.pick<int32_t>({0, 2, 2, 1}));
        for (int k = 0; k < 14; ++k)
            if (g.chance(10))
                at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(k)).flag |= 0x20;
        nocturne::dat::globalWork().macca = g.chance(20) ? 0 : g.range(0, 50000);
        initTimeListHp(a);
    };
    auto voidPair = [](uint32_t entry, std::initializer_list<uint64_t> args, std::function<void()> rewrite,
                       std::initializer_list<uint32_t> floats = {}) {
        std::vector<uint64_t> argv(args);
        std::vector<uint32_t> fv(floats);
        return Pair{[=] {
                        switch (argv.size()) {
                        case 2: return fv.empty() ? origVmVoid(entry, {argv[0], argv[1]}) : origVmVoid(entry, {argv[0]}, {fv[0]});
                        case 3: return origVmVoid(entry, {argv[0], argv[1], argv[2]});
                        case 6: return origVmVoid(entry, {argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]});
                        default: return origVmVoid(entry, {argv[0]}, {fv[0]});
                        }
                    },
                    [=] { rewrite(); return uint64_t{0}; }};
    };
    script("UnitKyoseiDisp", [=](Gen& g) {
        results(g);
        const int32_t start = g.range(0, 40);
        return voidPair(0x0024f420, {FW_ACTION, I(start)}, [=] { fadeInHiddenUnit(act(), start); });
    });
    script("SetDeadPacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g);
        Formation& dying = at<Formation>(formAddress(f));   // a dying unit is there
        dying.stat |= FormationStat::Present | FormationStat::CheckParty;
        dying.formindex = static_cast<int16_t>(f);
        // (Hardtype: no devil past 0x17D, as in randomUnit.)
        UnitWork& unit = at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)));
        if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype)
            if (unit.id > 0x17d && unit.id < 0x180)
                unit.id = static_cast<uint16_t>(g.range(1, 0x17d));
        Party& party = at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(dying.partyindex));
        party.flag = static_cast<int16_t>(party.flag | PartyFlag::Active);
        return voidPair(0x0024f478, {FW_ACTION, I(f)}, [=] { queueDeath(act(), f); });
    });
    script("SetPress", [=](Gen& g) {
        results(g);
        const uint32_t press = pressBits(g);
        return voidPair(0x0024f548, {FW_ACTION}, [=] { setPressCost(act(), nocturne::ee::Float::fromBits(press)); }, {press});
    });
    script("SetNewPress", [=](Gen& g) {
        results(g);
        const int32_t type = g.range(-1, 18);
        return voidPair(0x0024f5b0, {FW_ACTION, I(type)}, [=] { setPressResult(act(), type); });
    });
    script("SetHitStopFrame", [=](Gen& g) {
        results(g);
        const int32_t frame = g.range(-10, 70);
        return voidPair(0x0024f5c8, {FW_ACTION, I(frame)}, [=] { setHitStopFrame(act(), frame); });
    });
    script("SetEnemyEscapePacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        return voidPair(0x0024f5f0, {FW_ACTION, I(f), I(frame)}, [=] { queueEnemyEscape(act(), f, frame); });
    });
    script("SetAuroraPacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        setBuffCounter(f, 19, g.pick<int32_t>({0, 0xf8, 0xf9, 0xfa, 0xfb, 5, 0xfc}));
        return voidPair(0x0024f658, {FW_ACTION, I(f), I(frame)}, [=] { queueAurora(act(), f, frame); });
    });
    script("SetAddPressPacket", [=](Gen& g) {
        results(g);
        static std::vector<int32_t> granting;   // skills of program 13
        if (granting.empty())
            for (int32_t s = 0; s < 0x120; ++s)
                if (nocturne::dat::normalSkill(s).program == 13)
                    granting.push_back(s);
        const int32_t skill = !granting.empty() && g.chance(60) ? granting[g.below(static_cast<uint32_t>(granting.size()))]
                                                                 : g.range(0, 0x11f);
        return voidPair(0x0024f728, {FW_ACTION, I(skill)}, [=] { queueExtraPress(act(), skill); });
    });
    script("SetAddFlareChargePacket", [=](Gen& g) {
        results(g);
        const int32_t start = g.range(0, 40);
        return voidPair(0x0024f7b8, {FW_ACTION, I(start)}, [=] { queueFlareCharge(act(), start); });
    });
    script("SetMakaPacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        return voidPair(0x0024f7e0, {FW_ACTION, I(f), I(frame)}, [=] { queueMaccaThrow(act(), f, frame); });
    });
    script("SetTorafuPacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        return voidPair(0x0024f8a8, {FW_ACTION, I(f), I(frame)}, [=] { queueTrafuri(act(), f, frame); });
    });
    script("SetAnalyzePacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        return voidPair(0x0024f938, {FW_ACTION, I(f), I(frame)}, [=] { queueAnalyze(act(), f, frame); });
    });
    script("SetSakePacket", [=](Gen& g) {
        results(g);
        const int32_t skill = g.range(0, 0x11f), s = occupied(g), d = occupied(g), cnt = g.range(0, 3), frame = g.range(0, 40);
        return voidPair(0x0024fb38, {FW_ACTION, I(skill), I(s), I(d), I(cnt), I(frame)},
                        [=] { queueDodge(act(), skill, s, d, cnt, frame); });
    });
    script("SetMissPacket", [=](Gen& g) {
        results(g);
        const int32_t skill = g.range(0, 0x11f), s = occupied(g), d = occupied(g), cnt = g.range(0, 3), frame = g.range(0, 40);
        return voidPair(0x0024fc28, {FW_ACTION, I(skill), I(s), I(d), I(cnt), I(frame)},
                        [=] { queueMiss(act(), skill, s, d, cnt, frame); });
    });
    script("SetDamagePacket", [=](Gen& g) {
        results(g);
        UnitWork& unit = *act().get().work;
        if (g.chance(40))   // Endure (0x159) or Never Yield (0x168) among its skills
            unit.skill[g.below(8)] = static_cast<uint16_t>(g.chance(50) ? 0x159 : 0x168);
        act().get().party->flag = static_cast<int16_t>(act().get().party->flag & ~(PartyFlag::EndureFired | PartyFlag::EndureSpent));
        int32_t hp = g.chance(10) ? g.range(-5, 0) : g.range(1, 600);
        if (g.chance(25))   // exactly the HP left
            hp = timeListHp(act(), act().get().form->formindex);
        return voidPair(0x002532a8, {FW_ACTION, I(hp)}, [=] { queueDamage(act(), hp); });
    });
    // ---- Ongyo-Ki ----
    script("nbAddOngBunshinPacket", [=](Gen& g) {
        const uint32_t s = someForm(g), e = someForm(g);
        const int32_t start = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x00263110, {I(start), I(id), s, e}); },
                    [=] { return R(&addOngyokiClonePacket(start, id, F(s), F(e))); }};
    });
    script("nbAddOngBunshin2Packet", [=](Gen& g) {
        const uint32_t s = someForm(g), f1 = someForm(g), f2 = someForm(g), f3 = someForm(g);
        const int32_t start = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x002631a0, {I(start), I(id), s, f1, f2, f3}); },
                    [=] { return R(&addOngyokiClonePacket2(start, id, F(s), F(f1), F(f2), F(f3))); }};
    });
    script("nbAddOngOutPacket", [=](Gen& g) {
        const uint32_t f = someForm(g);
        const int32_t start = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x00263250, {I(start), I(id), f}); }, [=] { return R(&addOngyokiOutPacket(start, id, F(f))); }};
    });
    script("nbAddOngOut2Packet", [=](Gen& g) {
        const uint32_t f = someForm(g);
        const int32_t start = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x002632d0, {I(start), I(id), f}); }, [=] { return R(&addOngyokiOutPacket2(start, id, F(f))); }};
    });
    // Ongyo-Ki and his clones (formation stat 2) among the enemies.
    auto clones = [=](Gen& g) {
        results(g);
        for (int f = 4; f < 14; ++f) {
            Formation& form = at<Formation>(formAddress(f));
            form.stat &= ~2u;
            if (g.chance(50) && at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)))   // clones are units
                form.stat |= 2;
            form.formindex = static_cast<int16_t>(f);
        }
    };
    script("SetOngShadowPacket", [=](Gen& g) {
        clones(g);
        int32_t d = g.range(4, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(d)))
            d = g.range(4, 13);
        const int32_t frame = g.range(0, 40);
        Formation& real = at<Formation>(formAddress(d));   // the real one is there
        real.stat |= FormationStat::Present | FormationStat::CheckParty;
        Party& party = at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(real.partyindex));
        party.flag = static_cast<int16_t>(party.flag | PartyFlag::Active);
        return voidPair(0x0024fcc0, {FW_ACTION, I(0), I(0), I(d), I(0), I(frame)},
                        [=] { queueOngyokiFound(act(), 0, 0, d, 0, frame); });
    });
    script("SetOngShadowPacket2", [=](Gen& g) {
        clones(g);
        for (int f = 4; f < 14; ++f) {   // the clones that vanish are on the field
            Formation& form = at<Formation>(formAddress(f));
            if ((form.stat & 3) == 3) {
                form.stat |= FormationStat::CheckParty;
                Party& party = at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(form.partyindex));
                party.flag = static_cast<int16_t>(party.flag | PartyFlag::Active);
            }
        }
        const int32_t d = g.range(4, 13), frame = g.range(0, 40);
        return voidPair(0x0024fe40, {FW_ACTION, I(d), I(frame)}, [=] { queueOngyokiClonesVanish(act(), d, frame); });
    });

    // ---- side events: counters, talks, death scripts ----
    // Present, checkable slots have units and active parties, as in the
    // game; the talk conditions are drawn around their edges.
    auto sideWorld = [=](Gen& g) {
        results(g);
        auto* forms = &at<Formation>(FW_FORMS);
        for (int f = 0; f < 14; ++f) {
            Formation& form = forms[f];
            form.partyindex = static_cast<int16_t>(f);
            form.formindex = static_cast<int16_t>(f);
            if (g.chance(30))
                form.stat |= FormationStat::Present | FormationStat::CheckParty;
            if (g.chance(20))
                form.stat ^= FormationStat::Selected;
            if (g.chance(30))
                form.stat |= 0x100;
            Party& party = at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(f));
            const uint32_t unit = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f));
            if (!unit)   // someone on the field is a unit
                form.stat &= ~(FormationStat::Present | FormationStat::CheckParty | 0x100u);
            else if (form.stat & FormationStat::Present)
                form.stat |= FormationStat::CheckParty;
            if ((form.stat & FormationStat::Present) && (form.stat & FormationStat::CheckParty)) {
                {
                    party.flag = static_cast<int16_t>((party.flag | PartyFlag::Active) & ~0x60);
                    if (g.chance(15))
                        party.flag = static_cast<int16_t>(party.flag | g.pick<int32_t>({0x20, 0x40}));
                    UnitWork& u = at<UnitWork>(unit);
                    if (g.chance(40))
                        u.id = static_cast<uint16_t>(g.chance(30) ? 0x123 : g.range(1, lastDevilWithAi()));
                    u.badstat = static_cast<uint16_t>(g.chance(60) ? 0 : 1u << g.range(0, 11));
                    u.flag = (u.flag & ~0x24u) | (f < 4 ? (f == 0 ? 4u : 0u) : 0x20u);
                    u.maxhp = static_cast<uint16_t>(g.range(1, 500));
                    u.level = static_cast<uint16_t>(g.range(1, 99));
                    if (g.chance(30))
                        u.skill[g.below(8)] = static_cast<uint16_t>(g.range(0x131, 0x133));
                }
            } else {
                form.stat &= ~0x100u;
            }
        }
        std::memset(&forms[14], 0, 2 * sizeof(Formation));
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.stageMajor = static_cast<int16_t>(g.chance(15) ? g.range(0xf0, 0xf6) : g.range(0, 3));
        main.stat &= ~(0x1u | 0x10u | 0x80u | 0x100u | 0x2000000u);
        for (uint32_t bit : {0x1u, 0x10u, 0x80u, 0x100u, 0x2000000u})
            if (g.chance(bit == 0x80u ? 50 : 15))
                main.stat |= bit;
        main.enemypcnt = static_cast<int16_t>(g.range(0, 4));
        main.turn = static_cast<uint8_t>(g.range(0, 5));
        main.CommandMenuProcessID = g.chance(50) ? 0 : 0x00777000;
        main.actionstack = ps2PoolAllocate(16 * 16);   // the queue pushed actions go to
        main.actionstackp = g.range(0, 3);
        ActionProcessData& a = act();
        a.stat = static_cast<uint32_t>(g.rng()) & 0x3f0008u;
        a.type = g.range(3, 6);
        for (int k = 0; k < 6; ++k)
            if (g.chance(30))
                nocturne::evt::BitOn(0x851 + k);
        for (int f = 0; f < 14; ++f) {
            a.timelist[f].hp = static_cast<uint16_t>(g.chance(20) ? 0 : g.range(1, 500));
            if (g.chance(20))
                setBuffCounter(f, 0x10, 1);
        }
        nocturne::dat::globalWork().units[0].level = static_cast<uint16_t>(g.range(1, 99));
    };
    // Devils whose talk record allows each kind of talk.
    struct Talkers { std::vector<uint16_t> lastEnemy, ambush, begForLife, askToJoin; };
    static const Talkers talkers = [] {
        Talkers t;
        for (uint16_t id = 1; id < 384; ++id) {
            const auto& n = nocturne::dat::devilTalkFormat(id);
            if (n.lastEnemyTalk) t.lastEnemy.push_back(id);
            if (n.ambushTalk) t.ambush.push_back(id);
            if (n.begForLife) t.begForLife.push_back(id);
            if (n.askToJoin) t.askToJoin.push_back(id);
        }
        return t;
    }();
    auto pickFrom = [](Gen& g, const std::vector<uint16_t>& ids) {
        return ids.empty() ? static_cast<uint16_t>(g.range(1, lastDevilWithAi())) : ids[g.below(static_cast<uint32_t>(ids.size()))];
    };
    auto side = [&](const char* name, std::function<Pair(Gen&)> body) {
        script(name, [=](Gen& g) {
            sideWorld(g);
            return body(g);
        });
    };
    auto sideBool = [=](uint32_t entry, bool (*rewrite)(ActionProcessData&)) {
        return Pair{[=] { return origVm(entry, {FW_ACTION}); }, [=] { return norm(rewrite(act()) ? 1 : 0); }};
    };
    auto sideVoid = [=](uint32_t entry, void (*rewrite)(ActionProcessData&)) {
        return Pair{[=] { return origVmVoid(entry, {FW_ACTION}); }, [=] { rewrite(act()); return uint64_t{0}; }};
    };
    side("SetTargetPlayer", [=](Gen&) { return sideVoid(0x00251ef0, targetDemiFiend); });
    side("SetTargetParty", [=](Gen& g) {
        const int32_t shift = g.range(0, 13);   // party slots needn't match formation slots
        for (int f = 0; f < 14; ++f)
            at<Formation>(formAddress(f)).partyindex = static_cast<int16_t>((f + shift) % 14);
        const int32_t pi = g.range(-1, 14);
        return Pair{[=] { return origVmVoid(0x00251fd8, {FW_ACTION, I(pi)}); }, [=] { targetPartySlot(act(), pi); return uint64_t{0}; }};
    });
    side("CheckArrCounter", [=](Gen& g) {
        act().get().partyindex = g.range(0, 5);
        bool any = false;   // (an enemy is on the field)
        for (int f = 4; f < 14; ++f)
            any = any || (at<Formation>(formAddress(f)).stat & FormationStat::Present);
        for (int f = 4; !any && f < 14; ++f)
            if (at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f))) {
                at<Formation>(formAddress(f)).stat |= FormationStat::Present | FormationStat::CheckParty;
                Party& party = at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(f));
                party.flag = static_cast<int16_t>(party.flag | PartyFlag::Active);
                any = true;
            }
        return sideBool(0x00252060, checkAhrimanCounter);
    });
    side("CheckCounter", [=](Gen& g) {
        int from = occupied(g);
        UnitWork& hit = at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(from)));
        if (g.chance(80)) {   // with a counter passive, able to use it
            hit.skill[g.below(4)] = static_cast<uint16_t>(g.range(0x131, 0x133));
            hit.skillcnt = static_cast<uint16_t>(std::max<int>(hit.skillcnt, 4));
            hit.badstat = static_cast<uint16_t>(g.chance(70) ? 0 : 1u << g.range(0, 11));
        }
        Formation& form = at<Formation>(formAddress(from));
        form.stat |= FormationStat::Present | FormationStat::CheckParty;
        Party& party = at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(from));
        party.flag = static_cast<int16_t>(party.flag | PartyFlag::Active);
        const int to = g.range(0, 13);
        return Pair{[=] { return origVm(0x002521c8, {FW_ACTION, I(from), I(to)}); },
                    [=] { return norm(checkCounter(act(), from, to) ? 1 : 0); }};
    });
    auto talker = [=](Gen& g) {   // the actor: a unit that may talk
        ActionProcessData& a = act();
        a.party->flag = static_cast<int16_t>(g.chance(50) ? (a.party->flag | 2) : (a.party->flag & ~6));
        a.partyindex = g.range(0, 5);
        a.work->nowcommand = static_cast<int16_t>(g.range(-1, 6));
        a.work->badstat = static_cast<uint16_t>(g.chance(80) ? 0 : 0x80);
        if (g.chance(50))
            a.work->id = static_cast<uint16_t>(g.range(1, lastDevilWithAi()));
    };
    side("CheckMukanNego", [=](Gen& g) {
        talker(g);
        if (g.chance(60)) {   // an enemy that may speak up, the last silent one
            ActionProcessData& a = act();
            MainProcessData& main = at<MainProcessData>(FW_MAIN);
            int self = g.range(4, 13);   // the actor is an enemy
            while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(self)))
                self = g.range(4, 13);
            a.form.address = formAddress(self);
            a.party.address = FW_PARTY + 128u * static_cast<uint32_t>(self);
            a.work.address = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(self));
            a.partyindex = self;
            a.party->flag = static_cast<int16_t>(a.party->flag | 2);
            a.work->id = static_cast<uint16_t>(g.range(1, lastDevilWithAi()));
            // No devil talks this way in the shipped data; patch the
            // actor's record so the dormant code runs.
            const_cast<nocturne::DevilTalkFormat&>(nocturne::dat::devilTalkFormat(a.work->id)).lastEnemyTalk = 1;
            a.work->badstat = 0;
            nocturne::dat::globalWork().units[0].badstat = 0;
            main.stat &= ~1u;
            main.enemypcnt = static_cast<int16_t>(g.range(2, 4));
            main.turn = static_cast<uint8_t>(g.range(2, 5));
            for (int f = 4; f < 14; ++f)
                setBuffCounter(f, 0x10, g.chance(80) ? 1 : 0);
            setBuffCounter(a.form->formindex, 0x10, 0);
            a.form->stat |= FormationStat::Present | FormationStat::CheckParty;
            if (g.chance(30))
                main.stat |= 0x2000000;
        }
        if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype)   // its option byte
            at<uint8_t>(difftest::version::dataOrDie(0x002ff388)) = static_cast<uint8_t>(g.chance(30) ? 1 : 0);
        return sideBool(0x00252400, checkLastEnemyTalks);
    });
    side("CheckSenseiNego", [=](Gen& g) {
        talker(g);
        if (g.chance(70)) {   // an ambush by a devil that may talk
            MainProcessData& main = at<MainProcessData>(FW_MAIN);
            act().get().work->id = pickFrom(g, talkers.ambush);
            act().get().work->badstat = 0;
            nocturne::dat::globalWork().units[0].badstat = 0;
            main.stat = (main.stat & ~(0x1u | 0x10u | 0x100u)) | 0x80u;
            main.stageMajor = 0;
            main.enemypcnt = static_cast<int16_t>(g.chance(70) ? 1 : g.range(2, 4));
        }
        if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype)   // its option byte
            at<uint8_t>(difftest::version::dataOrDie(0x002ff388)) = static_cast<uint8_t>(g.chance(30) ? 1 : 0);
        return sideBool(0x002525f0, checkAmbushTalk);
    });
    side("CheckInotiNego", [=](Gen& g) {
        talker(g);
        if (g.chance(60)) {   // the party's attack left the last enemy weak
            ActionProcessData& a = act();
            MainProcessData& main = at<MainProcessData>(FW_MAIN);
            a.party->flag = static_cast<int16_t>(a.party->flag & ~6);
            a.partyindex = g.range(0, 3);
            a.work->nowcommand = static_cast<int16_t>(g.pick<int32_t>({0, 1, 5}));
            main.stat &= ~1u;
            main.enemypcnt = 1;
            for (int f = 4; f < 14; ++f) {
                Formation& form = at<Formation>(formAddress(f));
                if (!(form.stat & FormationStat::Present))
                    continue;
                form.stat |= FormationStat::Selected;
                UnitWork& enemy = at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)));
                enemy.id = pickFrom(g, talkers.begForLife);
                enemy.badstat = 0;
                enemy.level = static_cast<uint16_t>(g.range(1, 40));
                a.timelist[f].hp = static_cast<uint16_t>(g.range(1, enemy.maxhp / 3 + 1));
            }
            nocturne::dat::globalWork().units[0].level = static_cast<uint16_t>(g.range(30, 99));
        }
        return sideBool(0x00252720, checkBegForLife);
    });
    side("CheckBinjoNego", [=](Gen& g) {
        talker(g);
        if (g.chance(60)) {
            ActionProcessData& a = act();
            a.party->flag = static_cast<int16_t>(a.party->flag & ~6);
            a.partyindex = g.range(0, 3);
            a.stat |= 8;
            at<MainProcessData>(FW_MAIN).stat &= ~1u;
            for (int f = 4; f < 14; ++f)
                if (at<Formation>(formAddress(f)).stat & FormationStat::Present) {
                    at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f))).id = pickFrom(g, talkers.askToJoin);
                    at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f))).badstat = 0;
                }
        }
        return sideBool(0x002529d0, checkAskToJoin);
    });
    side("CheckDeadScript", [=](Gen&) { return sideVoid(0x00252c28, checkDeathScripts); });
    side("CheckKoketaNego", [=](Gen& g) { talker(g); return sideBool(0x00252cd8, checkFreeActionAfterEscape); });
    side("KyouseiPress", [=](Gen&) { return sideVoid(0x00252ea8, debugEndPressTurns); });
    side("DokodemoPoa", [=](Gen&) { return sideVoid(0x00252ee8, debugWinBattle); });
    // CHECK1: the aftermath of an action in the side-event world.
    auto aftermath = [=](Gen& g) {
        ActionProcessData& a = act();
        UnitWork& unit = *a.work;
        if (g.chance(40))
            unit.badstat = 0x40;   // poisoned
        unit.nowcommand = static_cast<int16_t>(g.range(-1, 6));
        unit.nowindex = static_cast<uint16_t>(g.pick<int32_t>({0, 1, 0x31, 0x32, 0xa4, 0xa6, 0xf7, 0x10, 0x60}));
        unit.nowtarea = static_cast<int16_t>(g.range(0, 2));
        unit.nowtform = static_cast<int16_t>(g.range(0, 13));
        a.form->motionend = static_cast<int16_t>(g.pick<int32_t>({0, 2, 3}));
        a.form->stat = (a.form->stat & ~0x4010u) | (g.chance(40) ? 0x10u : 0u);
        a.stat = (a.stat & ~0x518u) | (g.chance(20) ? 0x10u : 0u) | (g.chance(30) ? 0x100u : 0u) |
                 (g.chance(30) ? 0x400u : 0u) | (g.chance(30) ? 8u : 0u);
        a.packettime = static_cast<uint32_t>(g.chance(50) ? g.range(0, 15) : g.range(16, 60));
        at<MainProcessData>(FW_MAIN).endtype = static_cast<uint32_t>(g.chance(70) ? 0 : 3);
        for (int i = 0; i < 4; ++i)
            at<int8_t>(0x002f5830 + static_cast<uint32_t>(i)) = static_cast<int8_t>(g.chance(30) ? -1 : 0);
        if (g.chance(25)) {   // a short action that killed no one
            for (TimeList& t : a.timelist) {
                t.lockframe = static_cast<uint16_t>(t.lockframe % 6);
                t.endframe = static_cast<uint16_t>(t.endframe % 9);
                t.hp = static_cast<uint16_t>(t.hp | 1);
            }
            unit.badstat = 0;
        }
    };
    side("SetAction_CHECK1", [=](Gen& g) {
        aftermath(g);
        return Pair{[=] { origVmVoid(0x00257488, {FW_ACTION}); return uint64_t{0}; },
                    [=] { enterAftermath(act()); return uint64_t{0}; }};
    });
    side("CheckAction_CHECK1", [=](Gen& g) {
        aftermath(g);
        return Pair{[=] { return origVm(0x002577d8, {FW_ACTION}); }, [=] { return norm(updateAftermath(act())); }};
    });
    side("SetNowActionStat", [=](Gen& g) {
        act().get().partyindex = g.range(0, 5);
        act().get().stat = 0;
        const int32_t comm = g.chance(50) ? 1 : g.range(-1, 7);
        const int32_t skill = g.chance(40) ? g.pick<int32_t>({0x50, 0xde, 0xe2, 0xe3, 0xdf, 0xff, 0xfc}) : g.range(0, 0x11f);
        return Pair{[=] { return origVmVoid(0x00252fb8, {FW_ACTION, I(comm), I(skill)}); },
                    [=] { noteActionKind(act(), comm, skill); return uint64_t{0}; }};
    });

    // ---- the stock and the enemies' units ----
    // A random stock (the Demi-fiend, devils in and out of the party, dead
    // or spent ones) and enemy units.
    auto stockWorld = [=](Gen& g) {
        nocturne::GlobalWork& global = nocturne::dat::globalWork();
        for (int i = 1; i < 16; ++i) {
            nocturne::UnitWork& unit = global.units[i];
            unit.flag = g.chance(60) ? (1u | (g.chance(40) ? 2u : 0u) | (g.chance(10) ? 0x10u : 0u)) : 0u;
            unit.id = static_cast<uint16_t>(g.range(1, lastDevilWithAi()));
            unit.hp = static_cast<uint16_t>(g.chance(15) ? 0 : g.range(1, 500));
            unit.badstat = static_cast<uint16_t>(g.chance(15) ? 0x800 : 0);
        }
        global.stock_count = g.range(0, 8);
        global.stock_capacity = g.range(4, 12);
        const uint32_t enemies = ps2PoolAllocate(10 * static_cast<int32_t>(sizeof(nocturne::UnitWork)));
        const bool crowded = g.chance(30);   // all but the last slot (or all) taken
        for (uint32_t i = 0; i < 10; ++i)
            at<nocturne::UnitWork>(enemies + i * sizeof(nocturne::UnitWork)).flag =
                crowded ? (i < 9 || g.chance(50) ? 1u : 0u) : (g.chance(50) ? 1u : 0u);
        at<MainProcessData>(FW_MAIN).enemyunit.address = enemies;
        at<MainProcessData>(FW_MAIN).summonallowed = g.range(-1, 3);
    };
    script("nbGetNakama", [=](Gen& g) {
        stockWorld(g);
        const uint32_t s = static_cast<uint32_t>(act().get().work.address);
        if (g.chance(50))   // already in the compendium (with other stats)
            nocturne::fcl::record(at<nocturne::UnitWork>(s), false);
        return Pair{[=] { return origVm(0x00259180, {s}); }, [=] { return norm(recruitDevil(at<nocturne::UnitWork>(s))); }};
    });
    // ---- talks: their start and their result ----
    // Slots marked as the talks' sides, the actor on one of them; an
    // enemy talked to (with a unit), the enemies' parties, a result.
    auto negoWorld = [=](Gen& g) {
        ailingWorld(g);
        stockWorld(g);
        ActionProcessData& a = act();
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        auto* forms = &at<Formation>(FW_FORMS);
        for (int f = 0; f < 16; ++f) {
            forms[f].stat &= ~0x318u;
            if (g.chance(30) && f < 14 && at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(forms[f].partyindex)))
                forms[f].stat |= FormationStat::Present | FormationStat::Selected | g.pick<uint32_t>({0x100, 0x200, 0});
            if (g.chance(20))
                forms[f].stat |= 0x10;
        }
        a.form->stat = (a.form->stat & ~0x310u) | g.pick<uint32_t>({0, 0x100, 0x200, 0x10, 0x110});
        a.talkType = g.range(0, 6);
        int e = g.range(4, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(e)))
            e = g.range(4, 13);
        main.talkEnemySlot = static_cast<int16_t>(e);
        main.talkPlayerSlot = static_cast<int16_t>(g.range(0, 3));
        main.talkResult = g.range(0, 10);
        for (int k = 4; k < 14; ++k) {
            Party& p = at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(k));
            p.flag = static_cast<int16_t>(g.chance(60) ? (1 | 2 | (g.chance(20) ? 0x20 : 0) | (g.chance(20) ? 8 : 0)) : g.below(0x40));
            if (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(k)))   // (active parties have units)
                p.flag = static_cast<int16_t>(p.flag & ~1);
            p.formindex = static_cast<int16_t>(k);
        }
        if (g.chance(40)) {   // others of the talker's kind
            const uint16_t id = at<nocturne::UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(e))).id;
            for (int k = 4; k < 14; ++k)
                if (at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(k)) && g.chance(50))
                    at<nocturne::UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(k))).id = id;
        }
        a.press = nocturne::ee::Float::fromInt(g.range(-3, 3));
    };
    script("SetAction_NEGO", [=](Gen& g) {
        negoWorld(g);
        return Pair{[] { return origVmVoid(0x00256a98, {FW_ACTION}); }, [] { enterTalk(at<ActionProcessData>(FW_ACTION)); return uint64_t{0}; }};
    });
    script("SetAction_NEGORESULT", [=](Gen& g) {
        negoWorld(g);
        return Pair{[] { return origVmVoid(0x00256c00, {FW_ACTION}); },
                    [] { enterTalkResult(at<ActionProcessData>(FW_ACTION)); return uint64_t{0}; }};
    });
    // ---- READY ----
    // The command chosen, with targets; the unit's ailment, skills and the
    // battle's options vary.
    auto readyWorld = [=](Gen& g) {
        negoWorld(g);
        ActionProcessData& a = act();
        UnitWork& unit = *a.work;
        unit.nowcommand = static_cast<int16_t>(g.chance(5) ? -1 : g.range(0, 10));
        if (g.chance(40))   // the commands with the most to set up
            unit.nowcommand = static_cast<int16_t>(g.pick<int32_t>({0, 1, 1, 1, 5}));
        unit.nowindex = static_cast<uint16_t>(
            unit.nowcommand == 5 ? g.range(1, 0x9f)
            : g.chance(50)       ? g.pick<int32_t>({0x73, 0x74, 0x75, 0xe2, 0xe2, 0xf7, 0x130, 0x24, 0x40, 0x31, 0x10, 0xdf,
                                                    0x98, 0x9e, 0x33, 0x60, 0x64, 0x6a})
                                 : g.range(1, 0x17f));
        if (g.chance(30))
            unit.id = static_cast<uint16_t>(g.pick<int32_t>({0x159, 0x15a, 0x15b, 0x15c, 0xc0, 0xc0}));
        if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype) {
            // Hardtype's stand-ins, motion exceptions (and their devils) and
            // the pair an earlier action noted.
            if (unit.nowcommand == 1 && g.chance(50))
                unit.nowindex = static_cast<uint16_t>(g.pick<int32_t>({0x11b, 0x115, 0x9b, 0x113, 0x5a, 0xa4, 0xa5, 0xa6, 0xa7, 0x91, 0x9c, 0xde}));
            if (g.chance(40))
                unit.id = static_cast<uint16_t>(g.pick<int32_t>({0x15e, 0xc8, 0x15f, 0xc9, 0x115, 0x11, 0x15d, 0xc7}));
            const uint32_t pair = g.pick<uint32_t>({0u, 0x005a005au, 0x00330091u, 0x00dc0089u, static_cast<uint32_t>(g.rng()) & 0x00ff00ffu});
            at<uint32_t>(difftest::version::dataOrDie(0x002fe91c)) = pair;
        }
        unit.badstat = static_cast<uint16_t>(g.chance(60) ? 0 : g.pick<int32_t>({8, 0x20, 0x8000, 0x8008, 1}));
        unit.hp = static_cast<uint16_t>(g.chance(30) ? g.range(1, 3) : g.range(1, unit.maxhp));
        // Fields READY clears; a motion that ends by fading the unit out.
        a.autoskill = g.range(0, 3);
        a.allhpdamage = g.range(0, 50);
        a.allmpdamage = g.range(0, 50);
        a.runerr = g.range(0, 3);
        a.statusMessage = g.range(0, 5);
        a.skilltime = g.range(0, 9);
        if (g.chance(30)) {
            auto& visual = const_cast<nocturne::UnitVisual&>(nocturne::nb::unitVisual(unit));
            for (nocturne::UnitMotion& m : visual.motion) {
                m.endtype = 2;
                m.enddata = static_cast<int8_t>(g.range(0, 60));
            }
        }
        unit.mp = static_cast<uint16_t>(g.range(0, 200));
        a.select = g.chance(15) ? 0u : static_cast<uint32_t>(g.rng()) & 0xffffu;
        a.stat = (a.stat & ~0x1a5u) | (g.chance(50) ? 4u : 0u) | (g.chance(30) ? 0x80u : 0u) | (g.chance(40) ? 0x100u : 0u) |
                 (g.chance(30) ? 0x20u : 0u) | (g.chance(50) ? 1u : 0u);
        a.type = g.range(0, 4);
        a.timer = static_cast<uint32_t>(g.range(0, 40));
        nocturne::dat::globalWork().config = static_cast<uint32_t>(g.rng());
        for (uint8_t& count : nocturne::dat::globalWork().item_counts)
            count = static_cast<uint8_t>(g.range(0, 3));
        auto* forms = &at<Formation>(FW_FORMS);
        for (int f = 0; f < 16; ++f) {   // (only slots with a unit are present, as in the game)
            forms[f].formindex = static_cast<int16_t>(f);
            const bool hasUnit = f < 14 && at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(forms[f].partyindex)) &&
                                 at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f));
            if (!hasUnit)
                forms[f].stat &= ~1u;
            else if (g.chance(30))
                forms[f].stat |= g.pick<uint32_t>({0x41, 0x48, 0x49});
        }
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.stat = g.chance(30) ? (main.stat | 8u) : (main.stat & ~8u);
    };
    script("SetAction_READY", [=](Gen& g) {
        readyWorld(g);
        return Pair{[] { return origVmVoid(0x00254488, {FW_ACTION}); }, [] { enterReady(at<ActionProcessData>(FW_ACTION)); return uint64_t{0}; }};
    });
    script("CheckAction_READY", [=](Gen& g) {
        readyWorld(g);
        ActionProcessData& a = act();
        a.seqcnt = g.range(0, 6);
        a.motionSound = g.chance(50) ? 0 : 1;
        a.motion = g.range(-1, 30);
        a.hBed = g.chance(40) ? 0 : 0x00779000u + g.below(0x100);
        a.hSkillSe = g.chance(40) ? 0 : 0x00779100u + g.below(0x100);
        a.hSkillMem = 0x0077a001u + g.below(0x100);
        a.skillmidi = static_cast<uint32_t>(g.range(0x200, 0x2ff)) << 16;
        a.seqtime = static_cast<uint16_t>(g.range(0, 60));
        a.timer = static_cast<uint32_t>(g.chance(30) ? 0 : g.range(0, 60));
        a.skilltime = g.range(0, 20);
        at<MainProcessData>(FW_MAIN).stat ^= g.chance(50) ? 0x200u : 0u;
        return Pair{[] { return origVm(0x00255260, {FW_ACTION}); }, [] { return norm(updateReady(at<ActionProcessData>(FW_ACTION))); }};
    });
    script("SetAllPacket", [=](Gen& g) {
        readyWorld(g);
        ActionProcessData& a = act();
        a.runerr = 0;
        for (TimeList& t : a.timelist)
            t.hp = static_cast<uint16_t>(g.chance(15) ? 0 : g.range(1, 400));
        // An attacker and a target with units.
        auto withUnit = [&](int lo, int hi) {
            int f = g.range(lo, hi);
            for (int tries = 0; tries < 20 && !at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)); ++tries)
                f = g.range(lo, hi);
            return f;
        };
        const int32_t sform = a.form->formindex;
        const int32_t dform = withUnit(0, 13);
        if (dform < 14 && !at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(dform)))
            return Pair{[] { return uint64_t{0}; }, [] { return uint64_t{0}; }};
        int32_t koukatype = g.chance(80) ? g.range(0, 3) : g.range(4, 6);
        int32_t nskill = g.chance(50) ? g.pick<int32_t>({0, 0xa4, 0xa6, 0x10, 0x31, 0x24, 0x40, 0x106, 0x107, 0x108, 0x113, 0xd4,
                                                          0xe0, 0x2b, 0x60, 0x6a, 0xb0, 0x33, 0x44, 0xbe, 0xc0, 0xfa, 0x117})
                                       : g.range(0, 0x17f);
        // Focused cases for the rarer paths.
        switch (g.chance(60) ? g.range(0, 6) : -1) {
        case 0:   // a drain that delays the hit by skill
            koukatype = 2;
            nskill = g.pick<int32_t>({0x106, 0x107, 0x108});
            break;
        case 1:   // a repelled ailment the user is immune to by the 0x100000 flag
            koukatype = 1;
            nskill = g.pick<int32_t>({0x37, 0x3b, 0x3d, 0x80, 0xd2});   // Mute, Bind, Panic, Mute, Sleep
            if (nocturne::nb::Party* party = nocturne::nb::GetPartyFromFormindex(sform))   // (affinities by attribute)
                for (int column = 8; column <= 10; ++column)   // Curse, Nerve, Mind
                    party->affinities[column] = g.chance(70) ? 0x00100000u | 100u : 100u;
            break;
        case 2:   // a repel nulled outright (the unit stays hidden)
            koukatype = 1;
            nskill = 0xd4;
            break;
        case 3:   // a physical hit, maybe countered
            koukatype = g.pick<int32_t>({0, 0, 1, 4, 5});
            nskill = g.pick<int32_t>({0, 0xa4, 0xa5});
            break;
        case 4:   // a draining hit that may kill
            koukatype = 0;
            nskill = g.pick<int32_t>({0xbe, 0xc0, 0xfa, 0x117});
            break;
        case 5:   // the ailments that take a share of HP
            koukatype = 0;
            nskill = 0x110;
            break;
        case 6:   // a killing blow
            koukatype = 0;
            nskill = g.pick<int32_t>({0, 0xa4, 0x24, 0x40});
            break;
        default: break;
        }
        if (g.chance(40))
            a.form->motionend = 2;   // hidden by its motion
        const int32_t cnt = g.range(0, 4);
        const int32_t frame = g.range(0, 60);
        const float ritu = g.chance(70) ? 1.0f : static_cast<float>(g.range(1, 30)) / 10.0f;
        auto* forms = &at<Formation>(FW_FORMS);
        for (int f = 0; f < 16; ++f)
            forms[f].stat = g.chance(30) ? (forms[f].stat | 0x10u) : forms[f].stat;
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.stat = (main.stat & ~0x20400u) | (g.chance(15) ? 0x400u : 0u) | (g.chance(10) ? 0x20000u : 0u);
        a.type = g.chance(70) ? 0 : g.range(1, 3);
        if (dform < 14) {   // its ailments and how close it is to dying
            nocturne::UnitWork& unit = *nocturne::nb::GetUnitWorkFromFormindex(dform);
            unit.badstat = static_cast<uint16_t>(g.chance(60) ? 0 : g.pick<int32_t>({4, 0x400, 0x8000, 0x20, 1}));
            unit.hp = static_cast<uint16_t>(g.range(0, 400));
            a.timelist[dform].hp = static_cast<uint16_t>(g.chance(30) ? g.range(1, 5) : a.timelist[dform].hp);
            const bool devil = !unit.isPlayerCharacter();
            if (devil && g.chance(15)) {   // a devil that can't die, maybe stoned (a physical hit can shatter it)
                unit.id = static_cast<uint16_t>(g.pick<int32_t>({0x10e, 0x10f, 0x110, 0x123, 0x124, 0x125, 0x154}));
                if (g.chance(60))
                    unit.badstat = static_cast<uint16_t>(nocturne::ailment::Stone);
            }
            if (g.chance(30)) {   // Counter, Retaliate or Avenge (an enemy's skills are its devil's)
                if (unit.isEnemy()) {
                    unit.id = static_cast<uint16_t>(g.pick<int32_t>({0x005, 0x010, 0x04d, 0x051, 0x058, 0x059, 0x064, 0x070, 0x09a}));
                } else {
                    unit.skill[0] = static_cast<uint16_t>(g.range(0x131, 0x133));
                    unit.skillcnt = std::max<uint16_t>(unit.skillcnt, 1);
                }
                unit.badstat = 0;
            }
            if (g.chance(20))   // dying from this hit
                a.timelist[dform].hp = 1;
            if (!unit.isEnemy() && g.chance(25)) {   // Endure, hit for exactly what it has left
                unit.skill[1] = nocturne::skill::Endure;
                unit.skillcnt = std::max<uint16_t>(unit.skillcnt, 2);
                a.timelist[dform].hp = static_cast<uint16_t>(std::max(unit.hp >> 1, 1));
            }
            if (g.chance(10))   // its party already gone
                main.party[forms[dform].partyindex].flag = static_cast<int16_t>(main.party[forms[dform].partyindex].flag | 0x20);
        }
        const uint32_t ritubits = static_cast<uint32_t>(floatBits(ritu));
        return Pair{[=] { return origVmVoid(0x0024ff60, {FW_ACTION, I(koukatype), I(nskill), I(sform), I(dform), I(cnt), I(frame)}, {ritubits}); },
                    [=] {
                        queueHitResult(at<ActionProcessData>(FW_ACTION), koukatype, nskill, sform, dform, cnt, frame,
                                     nocturne::ee::Float::fromBits(ritubits));
                        return uint64_t{0};
                    }};
    });
    script("SetAction_SKILL", [=](Gen& g) {
        readyWorld(g);
        ActionProcessData& a = act();
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        // The skill: the ones with a case of their own, else any.
        UnitWork& user = *a.work;
        if (g.chance(60)) {
            user.nowcommand = 1;
            user.nowindex = static_cast<uint16_t>(g.pick<int32_t>({0, 0x31, 0x32, 0x34, 0x35, 0x36, 0x39, 0x40, 0x41, 0x42, 0x43, 0x44,
                                                                   0x45, 0x46, 0x4d, 0xcb, 0xcc, 0xcd, 0xce, 0x103, 0x104, 0x106,
                                                                   0x107, 0x108, 0x109, 0x110, 0x112, 0x114, 0x11a, 0x11e, 0xd4,
                                                                   0x10, 0x24, 0xa4, 0x60, 0x1c, 0x20, 0x07, 0x01, 0x11a, 0x107}));
        }
        if (g.chance(20)) {   // an attack with Drain Attack
            user.nowcommand = 0;
            if (!user.isEnemy()) {
                user.skill[0] = 0x12e;
                user.skillcnt = std::max<uint16_t>(user.skillcnt, 1);
            }
        }
        uint32_t occupied = 0;   // (the game only targets slots with a unit)
        for (int f = 0; f < 14; ++f)
            if (nocturne::nb::GetUnitWorkFromFormindex(f))
                occupied |= 1u << f;
        a.select &= occupied;
        // Some targets null, drain or repel an element (the skills here: physical, fire, ice, Force, Expel, Death).
        for (int f = 0; f < 14; ++f)
            if ((occupied & (1u << f)) && g.chance(30))
                if (nocturne::nb::Party* party = nocturne::nb::GetPartyFromFormindex(f))
                    party->affinities[g.pick<int32_t>({0, 1, 2, 4, 6, 7})] =
                        g.pick<uint32_t>({nocturne::Affinity::Null, nocturne::Affinity::Drain, nocturne::Affinity::Repel});
        if (g.chance(30))   // Ongyo-Ki's clones among the enemies
            for (int f = 4; f < 14; ++f)
                if ((occupied & (1u << f)) && g.chance(50))
                    at<Formation>(FW_FORMS + 0xf0u * static_cast<uint32_t>(f)).stat |= nocturne::nb::FormationStat::Shadow;
        if (g.chance(10)) {   // skill 0x11A (Force) into targets that all drain Force
            user.nowcommand = 1;
            user.nowindex = 0x11a;
            for (int f = 0; f < 14; ++f)
                if (nocturne::nb::Party* party = nocturne::nb::GetPartyFromFormindex(f); party && (occupied & (1u << f)))
                    party->affinities[4] = g.chance(80) ? nocturne::Affinity::Drain : 100u;
        }
        if (!user.isEnemy() && g.chance(25)) {   // Pierce
            user.skill[1] = nocturne::skill::Pierce;
            user.skillcnt = std::max<uint16_t>(user.skillcnt, 2);
        }
        a.runerr = g.chance(80) ? 0 : g.range(1, 3);
        a.type = g.chance(60) ? 0 : g.range(1, 4);
        a.autoskill = g.chance(70) ? 0 : g.range(298, 303);
        a.allhpdamage = g.range(0, 300);
        a.allmpdamage = g.range(0, 100);
        a.statusMessage = g.chance(50) ? 0 : g.range(1, 0x40);
        a.statusVarType = g.range(-1, 3);
        a.statusVarValue = g.range(0, 0x17f);
        a.press = nocturne::ee::Float::fromInt(-g.range(0, 4)) / nocturne::ee::Float::fromInt(g.pick<int32_t>({1, 2}));
        a.newaddpresstype = g.chance(70) ? 0 : g.range(1, 7);
        a.hitstopframe = g.chance(50) ? 0 : g.range(1, 40);
        main.press3 = nocturne::ee::Float::fromInt(g.range(0, 8)) / nocturne::ee::Float::fromInt(4);
        main.playerpcnt = static_cast<int16_t>(g.range(0, 4));
        main.enemypcnt = static_cast<int16_t>(g.range(0, 4));
        main.stat = (main.stat & ~0x21400u) | (g.chance(30) ? 0x400u : 0u) | (g.chance(10) ? 0x20000u : 0u) |
                    (g.chance(20) ? 0x1000u : 0u);
        if (g.chance(10))
            a.party->flag = static_cast<int16_t>(a.party->flag | 0x20);
        for (TimeList& t : a.timelist) {
            t.lockframe = static_cast<uint16_t>(g.range(0, 40));
            t.endframe = static_cast<uint16_t>(g.range(0, 60));
            t.hp = static_cast<uint16_t>(g.chance(15) ? 0 : g.range(1, 400));
        }
        a.form->motionend = static_cast<int16_t>(g.range(0, 2));
        a.form->motiontype = static_cast<int16_t>(g.range(-1, 26));
        a.form->motionenddata = static_cast<int16_t>(g.range(-1, 60));
        // Its effect: the two cuts' frames.
        if (g.chance(70)) {
            a.hEffBTL = FW_BTL_EFFECT;
            at<uint32_t>(FW_BTL_EFFECT + 8) = static_cast<uint32_t>(g.range(0, 80));        // cut 1: end
            at<uint32_t>(FW_BTL_EFFECT + 0x50) = static_cast<uint32_t>(g.range(0, 40));     // ... the hit
            at<uint32_t>(FW_BTL_EFFECT + 0x78) = static_cast<uint32_t>(g.range(0, 90));     // ... drawn until
            at<uint32_t>(FW_BTL_EFFECT + 0x620) = static_cast<uint32_t>(g.range(0, 40));    // cut 2: end
            at<uint32_t>(FW_BTL_EFFECT + 0x668) = static_cast<uint32_t>(g.range(0, 20));    // ... the hit
        } else {
            a.hEffBTL = 0;
        }
        return Pair{[] { return origVmVoid(0x00255650, {FW_ACTION}); }, [] { enterSkill(at<ActionProcessData>(FW_ACTION)); return uint64_t{0}; }};
    });
    script("CheckAction_SKILL", [=](Gen& g) {
        readyWorld(g);
        return Pair{[] { return origVm(0x00256a78, {FW_ACTION}); }, [] { return norm(updateSkill(at<ActionProcessData>(FW_ACTION))); }};
    });
    script("GetKoukaList", [=](Gen& g) {
        readyWorld(g);
        ActionProcessData& a = act();
        a.runerr = g.chance(85) ? 0 : 1;
        for (TimeList& t : a.timelist)
            t.hp = static_cast<uint16_t>(g.chance(25) ? 0 : g.range(1, 300));
        for (int f = 0; f < 14; ++f)
            if (const uint32_t u = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f))) {
                at<nocturne::UnitWork>(u).maxhp = static_cast<uint16_t>(g.range(1, 400));
                at<nocturne::UnitWork>(u).hp = static_cast<uint16_t>(g.chance(40) ? at<nocturne::UnitWork>(u).maxhp
                                                                   : g.chance(20)  ? 0
                                                                                   : g.range(0, at<nocturne::UnitWork>(u).maxhp));
            }
        // Sometimes only one or two targets (so random hits pile up on them).
        const uint32_t select = g.chance(35)   ? (1u << g.range(0, 13)) | (g.chance(50) ? 1u << g.range(0, 13) : 0u)
                                : g.chance(60) ? static_cast<uint32_t>(g.rng()) & 0xffffu
                                               : static_cast<uint32_t>(g.rng());
        const int32_t nskill = g.chance(60) ? g.pick<int32_t>({0x62, 0x6c, 0x73, 0xb0, 0xb5, 0xca, 0xde, 0x9e, 0x9f, 0x9e, 0x9f, 0xcc, 0xcc, 0x10, 0x24})
                                            : g.range(1, 0x17f);
        return Pair{[=] { return origVmVoid(0x002518c8, {FW_ACTION, FW_SCRATCH, I(static_cast<int32_t>(select)), I(nskill)}); },
                    [=] {
                        hitOrder(at<ActionProcessData>(FW_ACTION), &at<HitOrderEntry>(FW_SCRATCH), select, nskill);
                        return uint64_t{0};
                    }};
    });
    // A slot (0..13) whose unit the fake world finds (one is given a unit if none has).
    const auto unitSlot = [](Gen& g) {
        int f = g.range(0, 13);
        for (int tries = 0; tries < 14 && !at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)); ++tries)
            f = (f + 1) % 14;
        if (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)))
            at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)) = nocturne::guest::addressOf(&nocturne::dat::globalWork().units[0]);
        return f;
    };
    script("nbGetMotionEndType", [=](Gen& g) {
        const int f = unitSlot(g);
        const int32_t motion = g.range(0, 25);
        const uint32_t form = formAddress(f);
        at<Formation>(form).formindex = static_cast<int16_t>(f);
        return Pair{[=] { return origVm(0x0024d310, {form, I(motion)}); },
                    [=] { return norm(motionEndType(at<Formation>(form), motion)); }};
    });
    script("nbGetMotionEndData", [=](Gen& g) {
        const int f = unitSlot(g);
        const int32_t motion = g.range(0, 25);
        const uint32_t form = formAddress(f);
        at<Formation>(form).formindex = static_cast<int16_t>(f);
        return Pair{[=] { return origVm(0x0024d358, {form, I(motion)}); },
                    [=] { return norm(motionEndData(at<Formation>(form), motion)); }};
    });
    // A slot with a unit, one of its motions and a speed rate (often 1).
    const auto motionCase = [=](Gen& g, int& f, int32_t& motion, uint32_t& rate) {
        f = unitSlot(g);
        motion = g.range(0, 25);
        at<Formation>(formAddress(f)).formindex = static_cast<int16_t>(f);
        at<Formation>(formAddress(f)).scl = ee::Float(static_cast<float>(g.range(50, 200) / 100.0));
        rate = g.chance(40) ? 0x3f800000u : ee::Float(static_cast<float>(g.range(1, 300) / 100.0)).bits();
    };
    script("nbGetMotionSpeed", [=](Gen& g) {
        int f; int32_t motion; uint32_t rate;
        motionCase(g, f, motion, rate);
        const uint32_t form = formAddress(f);
        return Pair{[=] { origVm(0x0024d428, {form, I(motion)}, {rate}); return uint64_t{difftest::iface::origVmFloat()}; },
                    [=] { return uint64_t{motionSpeed(at<Formation>(form), motion, ee::Float::fromBits(rate)).bits()}; }};
    });
    script("nbGetMotionActframe", [=](Gen& g) {
        int f; int32_t motion; uint32_t rate;
        motionCase(g, f, motion, rate);
        const uint32_t form = formAddress(f);
        return Pair{[=] { return origVm(0x0024d3a0, {form, I(motion)}, {rate}); },
                    [=] { return norm(motionActFrame(at<Formation>(form), motion, ee::Float::fromBits(rate))); }};
    });
    script("nbGetMotionNo", [=](Gen& g) {
        int f; int32_t motion; uint32_t rate;
        motionCase(g, f, motion, rate);
        const uint32_t form = formAddress(f);
        return Pair{[=] { return origVm(0x0024d490, {form, I(motion)}); },
                    [=] { return norm(prepareMotion(at<Formation>(form), motion)); }};
    });
    // A slot's unit posed: any ailment (often one with a pose), sometimes
    // dying, its model with or without the slump; the battle's stat bit.
    const auto poseWorld = [=](Gen& g, int f) {
        UnitWork& unit = at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)));
        unit.badstat = static_cast<uint16_t>(g.chance(60) ? g.pick<int32_t>({4, 8, 0x20, 0x40, 0x80, 0x100, 1, 2, 0x10, 0x200, 0x800})
                                                          : g.range(0, 0xffff));
        if (g.chance(40))
            unit.hp = static_cast<uint16_t>(g.range(0, 5));
        at<MainProcessData>(FW_MAIN).stat ^= g.chance(20) ? 0x1000u : 0u;
        Formation& form = at<Formation>(formAddress(f));
        form.formindex = static_cast<int16_t>(f);
        form.partyindex = static_cast<int16_t>(f);   // (the fake world finds the unit by its party entry's index)
        at<uint32_t>(at<uint32_t>(form.hunit + 0x8c) + 4) = static_cast<uint32_t>(g.range(0x14, 0x1a));
        form.anime = g.chance(20) ? 0x80u : 0u;
        form.blendStart = static_cast<int16_t>(g.range(0, 20));
        form.blendEnd = static_cast<int16_t>(g.range(0, 20));
        form.waitMotion = static_cast<int16_t>(g.range(0, 25));
        at<int16_t>(at<uint32_t>(form.hunit + 0x8c) + 0x12) = static_cast<int16_t>(g.range(0, 3));
        return std::ref(form);
    };
    script("GetDyingBadWaitMotion", [=](Gen& g) {
        const int f = unitSlot(g);
        poseWorld(g, f);
        const int32_t motion = g.chance(60) ? 0 : g.range(0, 25);
        const uint32_t form = formAddress(f), unit = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f));
        return Pair{[=] { return origVm(0x0024ce78, {form, I(motion), unit}); },
                    [=] { return norm(posedMotion(at<Formation>(form), motion, at<UnitWork>(unit))); }};
    });
    script("nbSetUnitMotion", [=](Gen& g) {
        const int f = unitSlot(g);
        poseWorld(g, f);
        int f2; int32_t motion; uint32_t rate;
        motionCase(g, f2, motion, rate);
        (void)f2;
        if (g.chance(40))
            motion = g.pick<int32_t>({0, 1, 2, 0xd, 0xe, 0xf, 0x16, 0x17});
        const int32_t mode = g.range(0, 4);
        const uint32_t form = formAddress(f);
        if (g.chance(40) && motion >= 0 && motion < 26) {   // (sometimes the motion's animation is already playing)
            Formation& fm = at<Formation>(form);
            const int32_t posed = g.chance(50) ? motion : 0x16;   // (the slump a dying unit takes)
            at<int16_t>(at<uint32_t>(fm.hunit + 0x8c) + 0x12) = static_cast<int16_t>(prepareMotion(fm, posed));
        }
        return Pair{[=] { return origVmVoid(0x0024cff8, {form, I(motion), I(mode)}, {rate}); },
                    [=] { startMotion(at<Formation>(form), motion, mode, ee::Float::fromBits(rate)); return uint64_t{0}; }};
    });
    script("nbSetWaitMotion", [=](Gen& g) {
        const int f = unitSlot(g);
        poseWorld(g, f);
        const int32_t motion = g.chance(60) ? 0 : g.range(0, 25);
        const uint32_t rate = g.chance(40) ? 0x3f800000u : ee::Float(static_cast<float>(g.range(1, 300) / 100.0)).bits();
        const uint32_t form = formAddress(f);
        return Pair{[=] { return origVmVoid(0x0024d238, {form, I(motion)}, {rate}); },
                    [=] { setWaitMotion(at<Formation>(form), motion, ee::Float::fromBits(rate)); return uint64_t{0}; }};
    });
    script("evtSetUnitMotion", [=](Gen& g) {
        const uint32_t unit = at<Formation>(formAddress(g.range(0, 13))).hunit;
        at<uint32_t>(unit + 0xa4) = static_cast<uint32_t>(g.rng());
        at<uint32_t>(unit + 0x94) = static_cast<uint32_t>(g.rng());
        const int32_t motion = g.range(-2, 0x40), start = g.range(-2, 30), end = g.range(-2, 30), mode = g.range(-1, 5);
        return Pair{[=] { return origVmVoid(0x001e3cc0, {unit, I(motion), I(start), I(end), I(mode)}); },
                    [=] { nocturne::evt::setUnitMotion(at<nocturne::evt::EventUnit>(unit), motion, start, end, mode); return uint64_t{0}; }};
    });
    // A death: every type, its cry or not, a party slot or not (the
    // Demi-fiend or not); the unit posed, often one whose death runs a
    // script or starts an event.
    script("nbMakeDeadVisualPacket", [=](Gen& g) {
        const int f = unitSlot(g);
        Formation& form = poseWorld(g, f);
        UnitWork& unit = at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)));
        const int32_t last = lastDevilWithAi();
        unit.id = static_cast<uint16_t>(g.range(1, last));
        if (g.chance(40))
            for (uint16_t id = static_cast<uint16_t>(g.range(1, last)); id <= last; ++id) {
                unit.id = id;
                if (nocturne::dat::aiRecord(id).deathEvent() != 0 || (g.chance(20) && nocturne::dat::aiRecord(id).deathScript() != 0))
                    break;
            }
        form.stat ^= g.chance(50) ? 0x100u : 0u;
        unit.flag ^= g.chance(50) ? 4u : 0u;
        const int32_t s = g.range(-3, 30), id = static_cast<int32_t>(g.rng()), type = g.range(-1, 3), pcm = g.chance(70) ? 1 : 0;
        const uint32_t fa = formAddress(f);
        return Pair{[=] { return origVm(0x00263918, {I(s), I(id), fa, I(type), I(pcm)}); },
                    [=] { return norm(makeDeathVisualPackets(s, id, at<Formation>(fa), type, pcm)); }};
    });
    // A hit: every hit type, each ailment or a random stat, death or not,
    // HP and MP lost or not (negative), numbers shown or not; sometimes on a
    // slot past the units' (no reactions or numbers there).
    script("nbMakeDamagePacket", [=](Gen& g) {
        const int f = unitSlot(g);
        Formation& form = poseWorld(g, f);
        UnitWork& unit = at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)));
        unit.id = static_cast<uint16_t>(g.range(1, lastDevilWithAi()));
        const int32_t s = g.range(-3, 30), id = static_cast<int32_t>(g.rng()), type = g.range(-1, 4);
        const int32_t hp = g.chance(30) ? g.range(-3, -1) : g.range(0, 999), mp = g.chance(50) ? -1 : g.range(0, 99);
        const uint32_t bad = g.chance(50) ? 0u
                           : g.chance(80) ? g.pick<uint32_t>({1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800})
                                          : static_cast<uint32_t>(g.rng());
        const int32_t hiteff = g.chance(50) ? 0 : g.range(1, 3), deadtype = g.range(-1, 3);
        int32_t dead = g.chance(20) ? 1 : 0;
        if (g.chance(20)) {   // past the units' slots (14, 15: still a unit's, but no unit to die)
            form.formindex = static_cast<int16_t>(g.range(14, 20));
            dead = form.formindex < 16 ? 0 : dead;
        }
        const int32_t numbers = g.chance(70) ? 1 : 0, animeoff = g.range(-2, 10);
        const uint32_t fa = formAddress(f);
        return Pair{[=] {
                        return origVm(0x00263c00, {I(s), I(id), fa, I(type), I(hp), I(mp), bad, I(hiteff), I(dead),
                                                   I(deadtype), I(numbers), I(animeoff)});
                    },
                    [=] {
                        return norm(makeDamagePackets(s, id, at<Formation>(fa), type, hp, mp, bad, hiteff != 0, dead != 0,
                                                      deadtype, numbers != 0, animeoff));
                    }};
    });
    // A heal: every type, HP and MP gained or not (negative), a cure or not;
    // sometimes on a slot past the units' (no effects or numbers there).
    script("nbMakeKaifukuPacket", [=](Gen& g) {
        const int f = unitSlot(g);
        Formation& form = poseWorld(g, f);
        const int32_t s = g.range(-3, 30), id = static_cast<int32_t>(g.rng()), type = g.range(-1, 4);
        const int32_t hp = g.chance(30) ? g.range(-3, -1) : g.range(0, 999), mp = g.chance(50) ? -1 : g.range(0, 99);
        uint32_t cure = g.chance(60) ? 0u : g.chance(70) ? 0xfffu : static_cast<uint32_t>(g.rng());
        if (g.chance(20)) {   // (no unit there to cure)
            form.formindex = static_cast<int16_t>(g.range(14, 20));
            cure = 0;
        }
        const uint32_t fa = formAddress(f);
        return Pair{[=] { return origVm(0x00264010, {I(s), I(id), fa, I(type), I(hp), I(mp), cure}); },
                    [=] { return norm(makeHealPackets(s, id, at<Formation>(fa), type, hp, mp, cure != 0)); }};
    });
    script("evtSetWaitMotion, Speed, HokanFrame", [=](Gen& g) {
        const uint32_t unit = at<Formation>(formAddress(g.range(0, 13))).hunit;
        const int32_t motion = g.range(-2, 0x40), start = g.range(-2, 30), end = g.range(-2, 30);
        const uint32_t speed = static_cast<uint32_t>(g.rng());
        return Pair{[=] {
                        origVmVoid(0x001e3b68, {unit, I(motion)});
                        origVmVoid(0x001e3b70, {unit}, {speed});
                        return origVmVoid(0x001e3b78, {unit, I(start), I(end)});
                    },
                    [=] {
                        nocturne::evt::EventUnit& u = at<nocturne::evt::EventUnit>(unit);
                        nocturne::evt::setWaitMotion(u, motion);
                        nocturne::evt::setWaitSpeed(u, ee::Float::fromBits(speed));
                        nocturne::evt::setWaitBlend(u, start, end);
                        return uint64_t{0};
                    }};
    });
    script("nbCameraSetTaizi", [=](Gen& g) {
        const uint32_t from = formAddress(g.range(0, 13)), to = formAddress(g.range(0, 15));
        return Pair{[=] { return origVmVoid(0x001b17e0, {from, to}); },
                    [=] { cameraOnPair(at<Formation>(from), at<Formation>(to)); return uint64_t{0}; }};
    });
    script("nbAppendEnemyDevilWork", [=](Gen& g) {
        stockWorld(g);
        const int32_t id = g.range(1, lastDevilWithAi());
        return Pair{[=] { return origVm(0x002594b0, {FW_MAIN, I(id)}); },
                    [=] { return norm(addEnemyUnit(at<MainProcessData>(FW_MAIN), id)); }};
    });
    script("nbGetRandamStock", [=](Gen& g) {
        stockWorld(g);
        return Pair{[] { return origVm(0x002595a0, {}); }, [] { return norm(randomSummonableStock()); }};
    });
    script("nbClearCommandMemeoyRenzoku", [=](Gen& g) {
        for (int f = 0; f < 4; ++f) {
            const uint32_t unit = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f));
            if (unit) {
                at<nocturne::UnitWork>(unit).prevtarea = static_cast<int16_t>(g.range(-1, 3));
                at<nocturne::UnitWork>(unit).prevtform = static_cast<int16_t>(g.range(-1, 13));
            }
        }
        return Pair{[] { return origVmVoid(0x002596d0, {}); }, [] { forgetChainTargets(); return uint64_t{0}; }};
    });
    script("SetPlayerSummonPacket", [=](Gen& g) {
        results(g);
        stockWorld(g);
        ActionProcessData& a = act();
        a.party->flag = static_cast<int16_t>(g.chance(50) ? (a.party->flag | 2) : (a.party->flag & ~2));
        a.aisummonid = static_cast<uint32_t>(g.range(1, lastDevilWithAi()));
        a.work->nowcommand = static_cast<int16_t>(g.pick<int32_t>({1, 1, 0, 5}));
        a.work->nowindex = static_cast<uint16_t>(g.chance(40) ? 0xdf : g.range(0, 15));
        const int32_t d = g.range(0, 13), frame = g.range(0, 40);
        return Pair{[=] { return origVm(0x0024f990, {FW_ACTION, I(0), I(0), I(d), I(frame)}); },
                    [=] { return norm(queuePlayerSummon(act(), 0, 0, d, frame)); }};
    });
    static const State scriptStates[] = {
        {"SetAction_AISCR", 0x00253c40, [](ActionProcessData& a) { enterAiScript(a); return 0; }, false},
        {"CheckAction_AISCR", 0x00253c88, updateAiScript, true},
        {"SetAction_DEADSCRIPT", 0x00253d00, [](ActionProcessData& a) { enterDeathScript(a); return 0; }, false},
        {"CheckAction_DEADSCRIPT", 0x00253d38, updateDeathScript, true},
        {"SetAction_END", 0x00257b08, [](ActionProcessData& a) { enterEnd(a); return 0; }, false},
    };
    for (const State& d : scriptStates) {
        const uint32_t entry = d.entry;
        auto rewrite = d.rewrite;
        const bool result = d.result;
        script(d.name, [=](Gen&) {
            return Pair{[=] { return result ? origVm(entry, {FW_ACTION}) : origVmVoid(entry, {FW_ACTION}); },
                        [=] {
                            const int32_t r = rewrite(act());
                            return result ? norm(r) : uint64_t{0};
                        }};
        });
    }
    for (const State& d : states) {
        const uint32_t entry = d.entry;
        auto rewrite = d.rewrite;
        const bool result = d.result;
        action(d.name, [=](Gen& g) {
            if (g.chance(50) && queue().first)   // a packet of this action still queued
                queue().first->uniqueid = static_cast<int32_t>(FW_ACTION);
            return Pair{[=] { return result ? origVm(entry, {FW_ACTION}) : origVmVoid(entry, {FW_ACTION}); },
                        [=] {
                            const int32_t r = rewrite(act());
                            return result ? norm(r) : uint64_t{0};
                        }};
        });
    }

    add("nbMakePressPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t press = someFloat(g);
        return Pair{[=] { return origVm(0x002642e0, {I(s), I(id)}, {press}); }, [=] { return norm(makePressPackets(s, id, Fl(press))); }};
    });
    add("nbMakeNewPressPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), type = g.range(-1, 19);
        return Pair{[=] { return origVm(0x00264368, {I(s), I(id), I(type)}); }, [=] { return norm(makePressResultPackets(s, id, type)); }};
    });
    add("nbMakeFlyBadPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g);
        return Pair{[=] { return origVm(0x00264508, {I(s), I(id), f}); }, [=] { return norm(makeFlyAilmentPackets(s, id, F(f))); }};
    });
    add("nbMakeBadDamagePacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), bad = 1u << g.range(0, 12);
        return Pair{[=] { return origVm(0x00264528, {I(s), I(id), f, bad}); }, [=] { return norm(makeAilmentPackets(s, id, F(f), bad)); }};
    });
    add("nbMakeBadKaifukuPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = formAddress(g.range(0, 13));
        if (g.chance(20))
            at<Formation>(f).formindex = static_cast<int16_t>(g.range(14, 20));
        return Pair{[=] { return origVm(0x002645a8, {I(s), I(id), f}); }, [=] { return norm(makeAilmentCurePackets(s, id, at<Formation>(f))); }};
    });

    // ---- talks: the helpers ----
    // A talk between two units of the battle, its window a message window.
    static int32_t talkWindow = 0;
    static std::vector<int32_t> talkMessages;   // the window's table's messages
    auto talkWorld = [](Gen& g) {
        for (int f = 0; f < 14; ++f)   // (a formation's index is its slot, as in the game)
            at<Formation>(formAddress(f)).formindex = static_cast<int16_t>(f);
        TalkState& n = at<TalkState>(FW_TALK);
        std::memset(&n, 0, sizeof(TalkState));
        n.stat = static_cast<uint32_t>(g.rng()) & 0xf;
        n.candidateCount = g.range(0, 9);
        for (uint32_t& c : n.candidates)
            c = static_cast<uint32_t>(g.rng());
        n.historyindex = g.range(0, 13);
        for (uint32_t& h : n.history)
            h = static_cast<uint32_t>(g.rng());
        const iface::HelpWorld help = iface::helpWorld(g);
        const int32_t window = talkWindow = help.id;
        talkMessages = help.messages;
        n.nowmsgid = g.chance(20) ? -1 : window;
        n.msgwndid = g.chance(20) ? -1 : window;
        n.nowmes = g.range(0, 40);
        n.nowselect = g.range(-1, 3);
        if (n.nowmsgid >= 0) {   // where the message is
            nocturne::mes::CommandSetPhase(window, static_cast<int8_t>(g.range(-1, 2)));
            nocturne::mes::CommandSetSelPhase(window, static_cast<int16_t>(g.range(-1, 2)));
        }
        for (int f = 0; f < 14; ++f)
            if (const uint32_t u = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f))) {
                UnitWork& unit = at<UnitWork>(u);
                unit.level = static_cast<uint16_t>(g.chance(10) ? g.pick<int32_t>({0, 99, 100, 120}) : g.range(1, 99));
                unit.maxhp = static_cast<uint16_t>(g.range(1, 999));
                unit.maxmp = static_cast<uint16_t>(g.range(0, 999));
                unit.id = static_cast<uint16_t>(g.range(0, lastDevilWithAi()));
            }
    };
    auto someUnit = [](Gen& g) {
        int f = g.range(0, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)))
            f = g.range(0, 13);
        return at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f));
    };
    auto talk = [&, talkWorld](const char* name, std::function<Pair(Gen&)> body) {
        add(name, [=](Gen& g) { talkWorld(g); return body(g); });
    };
    talk("nbAddNegoIdKouho", [](Gen& g) {
        const uint32_t id = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVmVoid(0x0026a8a0, {FW_TALK, id}); }, [=] { addCandidate(at<TalkState>(FW_TALK), id); return uint64_t{0}; }};
    });
    talk("nbGetPrevNegoId", [](Gen&) {
        return Pair{[] { return origVm(0x0026a8d0, {FW_TALK}); }, [] { return norm(static_cast<int32_t>(previousTalkId(at<TalkState>(FW_TALK)))); }};
    });
    talk("nbGetBackNoNegoId", [](Gen& g) {
        const int32_t back = g.range(-3, 20);
        return Pair{[=] { return origVm(0x0026a8e8, {FW_TALK, I(back)}); },
                    [=] { return norm(static_cast<int32_t>(talkIdBack(at<TalkState>(FW_TALK), back))); }};
    });
    talk("nbSetMesMakka", [](Gen& g) {
        const int32_t window = talkWindow, macca = g.range(0, 99999);
        return Pair{[=] { return origVmVoid(0x0026a918, {I(window), I(macca)}); }, [=] { setMaccaVariable(window, macca); return uint64_t{0}; }};
    });
    talk("nbSetMesItem", [](Gen& g) {
        const int32_t window = talkWindow, item = g.range(0, 0x9f);
        return Pair{[=] { return origVmVoid(0x0026a938, {I(window), I(item)}); }, [=] { setItemVariable(window, item); return uint64_t{0}; }};
    });
    talk("nbClsNegoMessage", [](Gen&) {
        return Pair{[] { return origVmVoid(0x0026a958, {FW_TALK}); }, [] { closeTalkWindow(at<TalkState>(FW_TALK)); return uint64_t{0}; }};
    });
    talk("nbDispNegoMessage", [](Gen& g) {
        const int32_t msgid = g.range(-1, 4), msgno = g.range(0, 60), select = g.range(0, 2);
        return Pair{[=] { return origVmVoid(0x0026a998, {FW_TALK, I(msgid), I(msgno), I(select)}); },
                    [=] { showTalkMessage(at<TalkState>(FW_TALK), msgid, msgno, select != 0); return uint64_t{0}; }};
    });
    talk("nbCheckNegoMessage", [](Gen&) {
        return Pair{[] { return origVm(0x0026a9d0, {FW_TALK}); }, [] { return norm(talkMessageDone(at<TalkState>(FW_TALK)) ? 1 : 0); }};
    });
    talk("nbSetNegoMesVar", [=](Gen& g) {
        const int32_t window = talkWindow;
        const uint32_t p = someUnit(g), e = someUnit(g);
        at<UnitWork>(p).flag ^= g.chance(50) ? nocturne::UnitFlag::PlayerCharacter : 0u;
        return Pair{[=] { return origVmVoid(0x0026aa88, {I(window), p, e}); },
                    [=] { setTalkVariables(window, at<UnitWork>(p), at<UnitWork>(e)); return uint64_t{0}; }};
    });
    struct Amount { const char* name; uint32_t original; int32_t (*rewrite)(TalkState&, const UnitWork&, const UnitWork&); };
    static const Amount kAmounts[] = {
        {"nbGetNegoYaruMakkaA", 0x0026ab80, demonGivesMacca}, {"nbGetNegoYaruMakkaB", 0x0026ac00, demonGivesMaccaB},
        {"nbGetNegoKureMakkaA", 0x0026ac78, demonAsksMacca}, {"nbGetNegoKureMakkaB", 0x0026acf8, demonAsksMaccaB},
        {"nbGetNegoKureHpA", 0x0026ad70, demonAsksHp}, {"nbGetNegoKureHpB", 0x0026ade8, demonAsksHpB},
        {"nbGetNegoKureMpA", 0x0026ae38, demonAsksMp}, {"nbGetNegoKureMpB", 0x0026ae88, demonAsksMpB},
        {"nbGetKureItemA", 0x0026aed8, demonAsksItem}, {"nbGetKureItemB", 0x0026afd8, demonAsksItemB},
    };
    for (const Amount& amount : kAmounts) {
        const Amount* am = &amount;
        talk(am->name, [=](Gen& g) {
            const uint32_t a = someUnit(g), b = someUnit(g);
            const uint32_t original = am->original;
            auto rewrite = am->rewrite;
            return Pair{[=] { return origVm(original, {FW_TALK, a, b}); },
                        [=] { return norm(rewrite(at<TalkState>(FW_TALK), at<UnitWork>(a), at<UnitWork>(b))); }};
        });
    }
    struct Pick { const char* name; uint32_t original; int32_t (*rewrite)(int32_t); int32_t count; };
    static const Pick kPicks[] = {
        {"nbSelectKureItemA", 0x0026af58, pickAskedItem, 20}, {"nbSelectKureItemB", 0x0026b058, pickAskedItemB, 20},
        {"nbGetNegoRequestType", 0x0026b0e0, pickRequestType, 7}, {"nbGetNegoTuikaRequestType", 0x0026b160, pickExtraRequestType, 10},
    };
    for (const Pick& pick : kPicks) {
        const Pick* pk = &pick;
        talk(pk->name, [=](Gen& g) {
            const int32_t index = g.range(0, pk->count - 1);
            const uint32_t original = pk->original;
            auto rewrite = pk->rewrite;
            return Pair{[=] { return origVm(original, {I(index)}); }, [=] { return norm(rewrite(index)); }};
        });
    }

    for (const char* which : {"nbGetNegoYaruItemA", "nbGetNegoYaruItemB", "nbGetNegoYaruStone"}) {
        const std::string name = which;
        talk(which, [=](Gen& g) {
            const uint32_t w = someUnit(g);
            const uint32_t original = name == "nbGetNegoYaruItemA" ? 0x0026ba28u : name == "nbGetNegoYaruItemB" ? 0x0026bab8u : 0x0026bb48u;
            int32_t (*rewrite)(const UnitWork&) = name == "nbGetNegoYaruItemA" ? demonGivesItem : name == "nbGetNegoYaruItemB" ? demonGivesItemB : demonGivesStone;
            return Pair{[=] { return origVm(original, {w}); }, [=] { return norm(rewrite(at<UnitWork>(w))); }};
        });
    }
    talk("nbGetQuestionType", [=](Gen& g) {
        const uint32_t w = someUnit(g);
        if (g.chance(75))   // a demon without its own questions (privatesel 0)
            for (int tries = 0; tries < 50; ++tries) {
                at<UnitWork>(w).id = static_cast<uint16_t>(g.range(1, lastDevilWithAi()));
                if (nocturne::dat::devilTalkFormat(at<UnitWork>(w).id).privatesel != 1)
                    break;
            }
        uint8_t* answers = nocturne::dat::globalWork().questionAnswers;
        for (int i = 0; i < 4; ++i)
            answers[i] = static_cast<uint8_t>(g.chance(30) ? g.range(0, 2) : g.range(0, 20));
        if (g.chance(30))   // ties between the kinds
            answers[g.range(1, 3)] = answers[g.range(1, 3)];
        return Pair{[=] { return origVm(0x0026b7c8, {w}); }, [=] { return norm(questionType(at<UnitWork>(w))); }};
    });
    talk("nbGetInfoMsg", [](Gen& g) {
        const int32_t type = g.range(0, 3);
        return Pair{[=] { return origVm(0x0026bbd8, {I(type)}); }, [=] { return norm(pickInfoMessage(type)); }};
    });
    talk("nbCheckSelectMesJoukenAri", [](Gen& g) {
        const int32_t message = g.range(0, 59);
        return Pair{[=] { return origVm(0x0026bd50, {I(message)}); }, [=] { return norm(infoAvailable(message) ? 1 : 0); }};
    });
    for (int yes = 0; yes < 2; ++yes) {
        talk(yes ? "nbSetNegoYesMotion" : "nbSetNegoNoMotion", [=](Gen& g) {
            at<TalkState>(FW_TALK).actdata.address = FW_ACTION;
            int f = g.range(0, 13);   // (the talker, a unit)
            while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)))
                f = g.range(0, 13);
            const uint32_t form = formAddress(f);
            at<Formation>(form).formindex = static_cast<int16_t>(f);
            const uint32_t original = yes ? 0x0026be40u : 0x0026bde0u;
            return Pair{[=] { return origVm(original, {FW_TALK, form}); },
                        [=] { return norm(yes ? agreeMotion(at<TalkState>(FW_TALK), at<Formation>(form))
                                              : refuseMotion(at<TalkState>(FW_TALK), at<Formation>(form))); }};
        });
    }
    talk("nbGetInnenNegoID", [=](Gen& g) {
        TalkState& n = at<TalkState>(FW_TALK);
        n.pwork.address = someUnit(g);
        n.ework.address = someUnit(g);
        if (g.chance(60)) {   // a pair from the table
            const int16_t* pair = nocturne::guest::table<const int16_t>(difftest::version::dataOrDie(0x003e3158) + 0x3cu * static_cast<uint32_t>(g.range(0, 63)));
            n.pwork->id = static_cast<uint16_t>(pair[1]);
            n.ework->id = static_cast<uint16_t>(pair[2]);
        }
        return Pair{[] { return origVm(0x0026bea0, {FW_TALK}); }, [] { return norm(fatedPair(at<TalkState>(FW_TALK))); }};
    });

    // The helpers' talk skills (kind 7: 0x199..0x19F, 0x1A2..0x1A4) among others.
    auto buffWorld = [=](Gen& g) {
        TalkState& n = at<TalkState>(FW_TALK);
        n.data.address = FW_MAIN;
        n.ppartyindex = g.range(-1, 4);
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        for (int i = 0; i < 14; ++i) {
            Party& party = main.party[i];
            party.flag = static_cast<int16_t>(party.flag ^ (g.chance(30) ? 0x80 : 0) ^ (g.chance(20) ? 1 : 0));
            for (uint16_t& s : party.buffSkills)
                s = static_cast<uint16_t>(g.chance(50) ? 0 : g.pick<int32_t>({0x199, 0x1a0, 0x8199, 0x19c, 0x10}));
            if (UnitWork* unit = nocturne::nb::GetUnitWorkPointer(main, party)) {
                unit->skillcnt = static_cast<uint16_t>(g.range(0, 10));
                for (int k = 0; k < 10; ++k)
                    unit->skill[k] = static_cast<uint16_t>(g.chance(50) ? g.pick<int32_t>({0x199, 0x19a, 0x19b, 0x19f, 0x1a2, 0x1a4, 0x180, 0x18c})
                                                                        : g.range(0, 0x17f));
                unit->badstat = static_cast<uint16_t>(g.chance(80) ? 0 : g.pick<int32_t>({4, 8, 0x10, 0x400}));
            } else {
                party.flag = static_cast<int16_t>(party.flag & ~1);   // (a present slot has a unit)
            }
        }
    };
    talk("nbSetAllHojoSkillWork", [=](Gen& g) {
        buffWorld(g);
        return Pair{[] { return origVmVoid(0x0026b1e0, {FW_TALK}); }, [] { collectBuffSkills(at<TalkState>(FW_TALK)); return uint64_t{0}; }};
    });
    talk("nbSearchHojoSkillWork", [=](Gen& g) {
        buffWorld(g);
        TalkState& n = at<TalkState>(FW_TALK);
        n.ework.address = someUnit(g);
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        for (int i = 0; i < 4; ++i)   // the skills that apply at each moment
            for (uint16_t& s : main.party[i].buffSkills)
                if (g.chance(60))
                    s = static_cast<uint16_t>(g.range(0x199, 0x1a5) | (g.chance(10) ? 0x8000 : 0));
        const int32_t type = g.range(-1, 4);
        return Pair{[=] { return origVm(0x0026b3f8, {FW_TALK, I(type)}); }, [=] { return norm(static_cast<int32_t>(useBuffSkill(at<TalkState>(FW_TALK), type))); }};
    });
    talk("nbGetHojoSkillWorkCnt", [=](Gen& g) {
        buffWorld(g);
        return Pair{[] { return origVm(0x0026b368, {FW_TALK}); }, [] { return norm(countBuffSkills(at<TalkState>(FW_TALK))); }};
    });

    // ---- talks: the process ----
    // A running talk: its record a process's data, its steps the tests' stand-in.
    auto talkProcess = [=](Gen& g) {
        TalkState& n = at<TalkState>(FW_TALK);
        n.data.address = FW_MAIN;
        n.actdata.address = FW_ACTION;
        n.talkId = static_cast<uint32_t>(g.range(0, 9));   // (group 0, the stand-in's)
        n.talkPhase = g.range(0, 3);
        n.nextTalkId = g.chance(80) ? 0 : 0x31u;
        n.waitframe = g.chance(80) ? 0 : g.range(1, 3);
        n.endid = g.chance(90) ? 0 : 1;
        n.endtype = g.range(0, 5);
        n.stat = static_cast<uint32_t>(g.rng()) & 4u;
        n.nowmsgid = g.chance(80) ? -1 : talkWindow;
        n.nowmsgno = talkMessages.empty() ? 0 : talkMessages[g.below(static_cast<uint32_t>(talkMessages.size()))];
        n.stat &= ~4u;   // (the table has no selections)
        at<MainProcessData>(FW_MAIN).stat &= ~0x400000u;
        if (g.chance(15)) {   // the debug menu, maybe choosing a step (only with it on)
            at<MainProcessData>(FW_MAIN).stat |= 0x400000u;
            if (g.chance(30))
                n.stat |= 1;
        }
        // Group 0 (the game has none) runs the stand-in; its steps stay in it.
        at<uint32_t>(difftest::version::dataOrDie(0x004ef468)) = 0x00777300;
        return static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00551160), 0x3f9, 0, 0, 0, 0, FW_TALK));
    };
    struct TalkStateFunction { const char* name; uint32_t original; uint32_t (*rewrite)(uint32_t); };
    static const TalkStateFunction kTalkStates[] = {
        {"nbNegoProcess1", 0x0026c4f0, runTalk},
        {"nbNegoProcessMessage", 0x0026c400, showTalkStepMessage},
        {"nbNegoProcessMessageChk", 0x0026c390, waitTalkStepMessage},
        {"nbNegoProcessEnd", 0x0026c4c0, endTalk},
    };
    for (const TalkStateFunction& f : kTalkStates) {
        const TalkStateFunction* fn = &f;
        talk(fn->name, [=](Gen& g) {
            const uint32_t process = talkProcess(g);
            if (fn->original == 0x0026c400) {   // (shown only with a window to show it in, the last read)
                at<TalkState>(FW_TALK).nowmsgid = talkWindow;
                // ... its variables set, as every talk message sets them (the
                // speaker of some is {var 0}).
                setTalkVariables(talkWindow, at<UnitWork>(someUnit(g)), at<UnitWork>(someUnit(g)));
                nocturne::mes::CommandSetPhase(talkWindow, 0);
                nocturne::mes::CommandSetSelPhase(talkWindow, 0);
            }
            const uint32_t original = fn->original;
            auto rewrite = fn->rewrite;
            return Pair{[=] { return origVm(original, {process}); }, [=] { return norm(static_cast<int32_t>(rewrite(process))); }};
        });
    }
    talk("nbNegoShutdown", [=](Gen& g) {
        const uint32_t process = talkProcess(g);
        TalkState& n = at<TalkState>(FW_TALK);
        // Some of its tables open, each in its own window.
        const uint32_t* tables = nocturne::guest::table<const uint32_t>(difftest::version::dataOrDie(0x004e3be8));
        for (int32_t i = 0; i < nocturne::nb::kSpeechStyles; ++i)
            n.flowmsg[i] = tables[i * 4] != 0 && g.chance(20) ? nocturne::mes::Initialize(tables[i * 4]) : -1;
        n.questionmsg = g.chance(50) ? nocturne::mes::Initialize(tables[2]) : -1;
        n.bossmsg = g.chance(50) ? nocturne::mes::Initialize(difftest::version::dataOrDie(0x004eb810)) : -1;
        for (int32_t* w : {n.aisyomsg, n.infomsg})
            for (int32_t i = 0; i < nocturne::nb::kSpeechStyles; ++i)
                w[i] = -1;
        n.helpmsg = n.helpmsg2 = n.innenmsg = -1;
        at<MainProcessData>(FW_MAIN).TalkProcessID = g.chance(50) ? process : 0;
        return Pair{[=] { return origVmVoid(0x0026c780, {process}); }, [=] { shutdownTalk(process); return uint64_t{0}; }};
    });
    talk("InitNegoProcessData", [=](Gen& g) {
        const int32_t p = static_cast<int32_t>(someUnit(g) - someUnit(g)) == 0 ? 0 : g.range(0, 3);
        int32_t e = g.range(4, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(e)))
            e = g.range(4, 13);
        const int32_t type = g.range(-1, 7), skill = g.range(0x180, 0x1a4);
        int32_t pp = p;
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(pp)))
            pp = g.range(0, 3);
        return Pair{[=] { return origVm(0x0026c8f0, {FW_ACTION, I(pp), I(e), I(type), I(skill)}); },
                    [=] { return norm(static_cast<int32_t>(newTalk(at<ActionProcessData>(FW_ACTION), pp, e, type, skill))); }};
    });
    talk("nbInitNegoProcess", [=](Gen& g) {
        int32_t e = g.range(4, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(e)))
            e = g.range(4, 13);
        int32_t p = g.range(0, 3);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(p)))
            p = g.range(0, 3);
        const int32_t type = g.range(-1, 7), skill = g.range(0x180, 0x1a4);
        // (its own instructions: the harness hooks it to the legacy C for other tests)
        return Pair{[=] { iface::origOwn(0x0026ccf0, {FW_ACTION, I(p), I(e), I(type), I(skill)}); return uint64_t{0}; },
                    [=] { startTalk(at<ActionProcessData>(FW_ACTION), p, e, type, skill); return uint64_t{0}; }};
    });
    talk("nbSetNegoPose", [=](Gen& g) {
        const int32_t f = g.range(0, 13);
        if (const uint32_t unit = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)))   // asleep, stoned, ...
            at<UnitWork>(unit).badstat = static_cast<uint16_t>(g.chance(60) ? g.pick<int32_t>({0, 4, 8, 0x200, 0x10}) : g.below(0x10000));
        const uint32_t form = formAddress(f);
        return Pair{[=] { return origVmVoid(0x0024cf70, {form}); }, [=] { takeTalkPose(at<Formation>(form)); return uint64_t{0}; }};
    });
    talk("CheckSkillShinoKeiyaku", [=](Gen& g) {
        TalkState& n = at<TalkState>(FW_TALK);
        n.talkSkill = static_cast<uint32_t>(g.chance(50) ? nocturne::skill::DeathPact : g.range(0x180, 0x1a4));
        n.pwork.address = someUnit(g);
        if (g.chance(30))
            at<UnitWork>(n.pwork.address).hp = 0;
        return Pair{[=] { return origVm(0x002731a8, {FW_TALK}); }, [=] { return norm(deathPact(at<TalkState>(FW_TALK)) ? 1 : 0); }};
    });

    // ---- talks: the steps ----
    // A talk under way between a unit of the party and a demon, the step's
    // messages in one window; the unit is the skill's invoker.
    auto talkStepWorld = [=](Gen& g) {
        buffWorld(g);   // (the helpers' skills)
        for (int i = 0; i < 4; ++i)   // ... some that apply at each moment
            for (uint16_t& s : at<MainProcessData>(FW_MAIN).party[i].buffSkills)
                if (g.chance(40))
                    s = static_cast<uint16_t>(g.range(0x199, 0x1a5));
        TalkState& n = at<TalkState>(FW_TALK);
        n.data.address = FW_MAIN;
        n.actdata.address = FW_ACTION;
        n.candidateCount = 0;
        n.waitframe = 0;
        int p = g.range(0, 3), e = g.range(4, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(p)))
            p = g.range(0, 3);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(e)))
            e = g.range(4, 13);
        n.pformindex = p;
        n.eformindex = e;
        n.pwork.address = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(p));
        n.ework.address = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(e));
        n.pform.address = formAddress(p);
        n.eform.address = formAddress(e);
        for (const int f : {p, e}) {   // the two talking: their slots, present
            Formation& form = at<Formation>(formAddress(f));
            form.formindex = static_cast<int16_t>(f);
            form.partyindex = static_cast<int16_t>(f);
            at<MainProcessData>(FW_MAIN).party[f].flag |= 1;
        }
        at<uint32_t>(difftest::version::dataOrDie(0x005698e0)) = g.chance(95) ? formAddress(p) : 0;
        // (some of the devils the steps single out; sometimes the talker's kind)
        n.ework->id = static_cast<uint16_t>(g.chance(30) ? g.pick<int32_t>({0x5c, 0x3d, 0x61, 0x5b, 0x99, 0x96, 0x1d, 0x24, 0x27, 0x6e, 0x90, 0x9a, 0x38, 0x59, 0x68, 0x71, 109, 111, 113, 0x3a, 0x3c, 0x5a}) : g.range(1, lastDevilWithAi()));
        if (g.chance(20) && !n.pwork->isPlayerCharacter())
            n.pwork->id = n.ework->id;
        n.ekucyo = g.range(0, nocturne::nb::kSpeechStyles - 1);
        for (int32_t& window : n.flowmsg)   // (every style's table open, as the talk opens them)
            window = talkWindow;
        n.infomsg[n.ekucyo] = talkWindow + 100;   // (only noted as the window to show in)
        n.helpmsg = talkWindow;
        n.talkPhase = g.chance(70) ? g.range(0, 3) : g.range(0, 10);   // (the fated exchanges run longer)
        n.talkRequestType = g.chance(30) ? 0 : g.range(-1, 7);
        n.talkSkill = static_cast<uint32_t>(g.pick<int32_t>({0x180, 0x18b, 0x191, 0x199, 0x1a2}));
        n.cnt6_36 = g.range(0, 3);
        n.cnt6_37 = g.chance(50) ? 0 : g.range(0, 2);
        n.getmakka = g.range(1, 5000);
        n.getitem = g.range(1, 0x9f);
        n.getinfotype = g.pick<int32_t>({0, 2});
        n.requestdata = g.chance(80) ? g.range(1, 0x6f) : g.range(0x9d, 0x9f);   // an item asked for
        n.questionmsg = talkWindow + 200;
        n.innenmsg = talkWindow + 300;
        n.innen_id = g.range(0, 63);
        if (g.chance(50))   // the step before, one the steps look back on
            n.history[n.historyindex] = g.pick<uint32_t>({0x40008, 0x40009, 0x4000a, 0xb0005, 0xb0007});
        n.qtype = g.range(0, 3);
        n.qindex = g.chance(10) ? g.range(-1, 6) : g.range(0, n.qtype == 0 ? 4 : 1);
        n.nowselect = g.range(0, n.qtype == 0 ? 1 : 2);   // (two answers to its own questions, three to the others)
        n.requesttype = g.range(-1, 5);
        n.affinity = g.range(0, 3);
        n.buffAffinity = g.range(0, 2);
        n.buffAffinityMessage = g.range(0, 40);
        n.aisyomsg[n.ekucyo] = talkWindow + 400;
        n.helpmsg2 = talkWindow + 500;
        n.temp_param[0] = g.range(0, 7);
        n.talkType = g.range(0, 6);
        // (group 6: the talk skill's rules, helpers, haggles, the Macca window)
        if (g.chance(50))
            n.talkSkill = static_cast<uint32_t>(g.range(0x180, 0x1a5));
        n.buffSkill = g.range(0x198, 0x1a5);
        n.buffPartyIndex = g.range(0, 3);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(n.buffPartyIndex)))
            n.buffPartyIndex = g.range(0, 3);
        at<MainProcessData>(FW_MAIN).party[n.buffPartyIndex].formindex = static_cast<int16_t>(n.buffPartyIndex);
        at<Formation>(formAddress(n.buffPartyIndex)).formindex = static_cast<int16_t>(n.buffPartyIndex);
        n.cnt6_36 = g.range(0, 5);
        n.cnt6_58 = g.range(0, 4);
        n.cnt6_66 = g.range(0, 4);
        n.mes6_2 = g.range(0x1c, 0x1f);
        n.mes6_25 = g.range(0x25, 0x28);
        n.mes6_67 = g.range(0x21, 0x24);
        n.prevreqtype = g.range(-1, 5);
        n.requesttype = g.range(-1, 5);
        n.stat ^= g.chance(30) ? 8u : 0u;
        n.temp_param[1] = g.range(0, 0x60);
        n.history[n.historyindex] = g.chance(50) ? g.pick<uint32_t>({0x6000c, 0x6000d, 0x6003b, 0x6003c, 0x6003d, 0x6003e, 0x6003f, 0x60040})
                                                 : n.history[n.historyindex];
        {
            int32_t* window = &at<int32_t>(FW_MAKA);
            for (int32_t i = 0; i < 16; ++i)
                window[i] = g.range(-1, 3);
        }
        // (group 1: boss talks, other enemies breaking in, the special skills and talkers)
        n.bossmsg = talkWindow + 600;
        n.flag1_6 = g.range(0, 1);
        n.flag1_39 = g.range(0, 1);
        MainProcessData& battle = at<MainProcessData>(FW_MAIN);
        battle.stageMajor = static_cast<int16_t>(g.chance(20) ? g.range(0xef, 0xf7) : g.range(0, 8));
        battle.enemypcnt = static_cast<int16_t>(g.range(1, 6));
        battle.stat ^= (g.chance(30) ? 1u : 0u) | (g.chance(50) ? 0x800000u : 0u);
        for (int32_t slot = 4; slot < 14; ++slot)
            battle.party[slot].flag = static_cast<int16_t>(battle.party[slot].flag ^ (g.chance(30) ? 2 : 0) ^ (g.chance(15) ? 0x10 : 0) ^ (g.chance(15) ? 8 : 0));
        n.epartyindex = e;
        for (int32_t slot = 4; slot < 14; ++slot)   // (other enemies, some unable to talk)
            if (const uint32_t u = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(slot)); u && g.chance(20))
                at<UnitWork>(u).badstat = static_cast<uint16_t>(g.pick<int32_t>({1, 4, 8, 0x200}));
        nocturne::dat::globalWork().macca = g.chance(20) ? g.pick<int32_t>({499, 500, 501}) : g.range(0, 99999);
        if (g.chance(15) && !n.pwork->isPlayerCharacter()) {   // a fated pair
            const uint32_t pair = difftest::version::dataOrDie(0x003e3158) + 0x3cu * static_cast<uint32_t>(g.range(0, 44));
            n.pwork->id = at<uint16_t>(pair + 2);
            n.ework->id = at<uint16_t>(pair + 4);
        }
        n.boupartyindex = g.range(4, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(n.boupartyindex)))
            n.boupartyindex = g.range(4, 13);
        n.actdata->select = static_cast<uint32_t>(g.rng());
        if (g.chance(30))
            n.ework->badstat = static_cast<uint16_t>(g.pick<int32_t>({1, 2, 4, 8, 0x10, 0x200, 0x40}));
        if (g.chance(30) && !n.pwork->isPlayerCharacter())
            n.pwork->id = static_cast<uint16_t>(g.pick<int32_t>({0x8f, 0x71, 2}));
        if (g.chance(30))
            n.talkSkill = static_cast<uint32_t>(g.pick<int32_t>({0x189, 0x18a, 0x18b, 0x193, 0x1a5}));
        n.requesthpmp = g.range(0, 1);
        n.data->stat ^= g.chance(20) ? 0x20000u : 0u;
        for (int32_t i = 0; i < 8; ++i)
            n.workid[i] = 0x60000u | static_cast<uint32_t>(g.range(1, 0x50));
        at<UnitWork>(n.pwork.address).param[1] = static_cast<int8_t>(g.range(0, 3));
        at<UnitWork>(n.ework.address).param[1] = static_cast<int8_t>(g.range(0, 3));
        n.nowselect = g.range(0, 1);
        nocturne::GlobalWork& global = nocturne::dat::globalWork();
        for (uint8_t& answers : global.questionAnswers)
            answers = static_cast<uint8_t>(g.chance(20) ? 0xff : g.range(0, 30));
        for (uint8_t& loans : global.loanCounts)
            loans = static_cast<uint8_t>(g.chance(30) ? 0xff : g.range(0, 14));
        // The stock: some demons (maybe one like the demon), as many as it holds or fewer.
        global.units[0].level = static_cast<uint16_t>(g.chance(20) ? n.ework->level : g.range(1, 99));
        global.stock_capacity = g.range(4, 12);
        for (int32_t i = 4; i < 16; ++i) {
            nocturne::UnitWork& unit = global.units[i];
            unit.flag = g.chance(60) ? (unit.flag | nocturne::UnitFlag::Valid) & ~nocturne::UnitFlag::PlayerCharacter
                                     : unit.flag & ~nocturne::UnitFlag::Valid;
            unit.id = static_cast<uint16_t>(g.chance(10) ? n.ework->id : g.range(1, lastDevilWithAi()));
        }
        if (g.chance(10))   // the talker down
            n.pwork->hp = 0;
        else if (g.chance(30))   // ... or low
            n.pwork->hp = static_cast<uint16_t>(g.range(1, 0x70));
        if (g.chance(30) && n.pwork->skillcnt > 0)   // it may hold on (Endure, Never Yield)
            n.pwork->skill[g.below(std::min<uint32_t>(n.pwork->skillcnt, 24))] = static_cast<uint16_t>(g.pick<int32_t>({0x159, 0x168}));
        if (g.chance(20))
            n.pwork->mp = 0;
        if (g.chance(10))
            n.requestdata = g.chance(50) ? n.pwork->hp : 50;
        for (uint32_t& h : n.history)   // (some look back for group 6's 0x6002A)
            if (g.chance(20))
                h = 0x6002a;
        if (g.chance(30))   // a full bag
            for (uint8_t& count : global.item_counts)
                count = 99;
        if (g.chance(50))
            nocturne::dat::globalWork().item_counts[n.requestdata] = static_cast<uint8_t>(g.range(1, 3));
    };
    // The bargaining's affinity checks (ChkAisyo): conditions of the kinds
    // the talk skills use.
    auto affinityCondition = [](Gen& g) {
        if (g.chance(40))
            return g.pick<uint32_t>({0x80000000u, 0x80000001u, 0x80000001u, 0x80000001u, 0x80000002u});
        uint32_t jo = 0;
        for (const uint32_t bit : {1u, 2u, 4u, 8u, 0x10u, 0x20u, 0x40u, 0x80u, 0x100u, 0x200u, 0x400u, 0x800u, 0x80000000u})
            if (g.chance(15))
                jo |= bit;
        return jo;
    };
    talk("ChkAisyo", [=](Gen& g) {
        talkStepWorld(g);
        const uint32_t a = someUnit(g), b = someUnit(g), jo = affinityCondition(g);
        if (g.chance(40))   // (the gaps the conditions test)
            at<UnitWork>(a).level = static_cast<uint16_t>(std::clamp(at<UnitWork>(b).level + g.pick<int32_t>({-11, -10, -9, 9, 10, 11}), 1, 99));
        if (g.chance(20) && !at<UnitWork>(b).isPlayerCharacter())
            at<UnitWork>(b).id = static_cast<uint16_t>(g.range(109, 113));   // a Tyrant
        const int32_t sw = g.range(0, 1);
        return Pair{[=] { return origVm(0x0026eb08, {a, b, I(static_cast<int32_t>(jo)), I(sw)}); },
                    [=] { return norm(checkAffinity(at<UnitWork>(a), at<UnitWork>(b), jo, sw) ? 1 : 0); }};
    });
    talk("nbChkNegoAisyo", [=](Gen& g) {
        talkStepWorld(g);
        const uint32_t mine = affinityCondition(g), theirs = affinityCondition(g);
        const int32_t sw = g.range(0, 1);
        return Pair{[=] { return origVm(0x0026ee90, {FW_TALK, I(static_cast<int32_t>(mine)), I(static_cast<int32_t>(theirs)), I(sw)}); },
                    [=] { return norm(pairAffinity(at<TalkState>(FW_TALK), mine, theirs, sw) ? 1 : 0); }};
    });
    talk("nbChkNegoAisyo2", [=](Gen& g) {
        talkStepWorld(g);
        const uint32_t s = someUnit(g), d = someUnit(g), mine = affinityCondition(g), theirs = affinityCondition(g);
        const int32_t sw = g.range(0, 1);
        return Pair{[=] { return origVm(0x0026ef18, {s, d, I(static_cast<int32_t>(mine)), I(static_cast<int32_t>(theirs)), I(sw)}); },
                    [=] { return norm(pairAffinity(at<UnitWork>(s), at<UnitWork>(d), mine, theirs, sw) ? 1 : 0); }};
    });
    talk("GetMakaProcessData", [=](Gen& g) {
        talkStepWorld(g);
        return Pair{[] { return origVm(0x0028f218, {}); }, [] { return norm(static_cast<int32_t>(nocturne::guest::addressOf(maccaWindow()))); }};
    });
    talk("nbMakaDispOn", [=](Gen& g) {
        talkStepWorld(g);
        const int32_t keep = g.range(0, 2);
        return Pair{[=] { return origVmVoid(0x0028f258, {I(keep)}); }, [=] { showMacca(keep); return uint64_t{0}; }};
    });
    talk("nbMakaDispOff", [=](Gen& g) {
        talkStepWorld(g);
        return Pair{[] { return origVmVoid(0x0028f2b0, {}); }, [] { hideMacca(); return uint64_t{0}; }};
    });
    // The Macca window's process, its record the fake "nb_maka"'s.
    auto maccaWorld = [=](Gen& g) {
        talkStepWorld(g);
        MaccaWindow& w = at<MaccaWindow>(FW_MAKA);
        w.state = g.range(0, 3);
        w.open = g.range(0, 1);
        w.x = g.range(0, 0x200);
        w.y = g.range(0, 0x1c0);
        w.keep = g.range(0, 1);
        w.closeframes = g.range(-1, 3);
        w.alpha = g.pick<int32_t>({0, 0x14, 0x60, 0x70, 0x80, g.range(-0x20, 0xa0)});
        nocturne::dat::globalWork().macca = g.chance(20) ? g.pick<int32_t>({0, 5, 10, 9999999}) : g.range(0, 9999999);
    };
    talk("maccaDigit", [=](Gen& g) {
        const int32_t value = g.range(-100, 9999999), place = g.range(-1, 7);
        return Pair{[=] { return origVm(0x0028f2f8, {I(value), I(place)}); }, [=] { return norm(maccaDigit(value, place)); }};
    });
    talk("DispMaka", [=](Gen& g) {
        maccaWorld(g);
        const int32_t x = g.range(0, 0x200), y = g.range(0, 0x1c0);
        const uint32_t color = static_cast<uint32_t>(g.rng()), alpha = static_cast<uint32_t>(g.range(0, 0x80));
        return Pair{[=] { return origVmVoid(0x0028f348, {FW_MAKA, I(x), I(y), I(static_cast<int32_t>(color)), alpha}); },
                    [=] { drawMaccaWindow(at<MaccaWindow>(FW_MAKA), x, y, color, alpha); return uint64_t{0}; }};
    });
    talk("stepMaccaWindow", [=](Gen& g) {
        maccaWorld(g);
        return Pair{[] { return origVmVoid(0x0028f600, {FW_MAKA}); }, [] { stepMaccaWindow(at<MaccaWindow>(FW_MAKA)); return uint64_t{0}; }};
    });
    talk("nbMakaProcess1", [=](Gen& g) {
        maccaWorld(g);
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00551560), 0x2b0e, 0, 0, 0, 0, FW_MAKA));
        return Pair{[=] { return origVm(0x0028f698, {process}); }, [=] { return norm(static_cast<int32_t>(runMaccaWindow(process))); }};
    });
    talk("nbMakaShutdown", [=](Gen& g) {
        maccaWorld(g);
        const uint32_t data = g.chance(80) ? ps2PoolAllocate(0x2c) : 0;
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(0x00777500, 0x2b0e, 0, 0, 0, 0, data));
        return Pair{[=] { return origVmVoid(0x0028f6f0, {process}); }, [=] { shutdownMaccaWindow(process); return uint64_t{0}; }};
    });
    talk("InitMakaProcessData", [=](Gen& g) {
        maccaWorld(g);
        return Pair{[] { return origVm(0x0028f728, {}); }, [] { return norm(static_cast<int32_t>(newMaccaWindow())); }};
    });
    talk("nbInitMakaProcess", [=](Gen& g) {
        maccaWorld(g);
        const uint32_t parent = g.chance(70) ? static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), 1, 0, 0, 0, 0, 0)) : 0;
        return Pair{[=] { return origVm(0x0028f770, {parent}); }, [=] { return norm(static_cast<int32_t>(startMaccaWindow(parent))); }};
    });
    // ---- the battle's events (nbEventProcess) ----
    // An event of the battle (eventno), maybe of an encounter with events.
    auto eventWorld = [](Gen& g) {
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.eventno = g.chance(80) ? g.range(0, 15) : g.range(0, 99);
        main.encno = g.chance(60) ? at<int32_t>(difftest::version::dataOrDie(0x00527260) + 0x1c * static_cast<uint32_t>(g.range(0, 15)) + 8) : g.chance(25) ? 0 : g.range(0, 0x400);
        main.MainProcessID = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), 1, 0, 0, 0, 0, 0));
        main.stat = static_cast<uint32_t>(g.range(0, 0xffff));
        main.endtype = static_cast<uint32_t>(g.range(0, 3));
        for (int i = 0; i < 14; ++i)
            at<Formation>(formAddress(i)).stat ^= static_cast<uint32_t>(g.range(0, 3)) << 2;   // (bits 4 and 8)
    };
    // A running event's process and record.
    auto eventProcess = [=](Gen& g) {
        eventWorld(g);
        const uint32_t data = ps2PoolAllocate(0x28);
        EventProcessData& ed = at<EventProcessData>(data);
        ed.data.address = FW_MAIN;
        ed.eventrid = g.range(0, 5);
        ed.time = g.range(0, 100);
        ed.seq = g.range(0, 5);
        ed.seqtime = g.range(0, 100);
        ed.userdata = g.chance(50) ? ps2PoolAllocate(0x10) : 0;
        ed.usershutdown = g.chance(50) ? difftest::version::codeOrDie(0x002c1ca0) : 0;   // (a function the tests log)
        ed.file = g.chance(50) ? static_cast<uint32_t>(g.range(1, 0x1000)) : 0;
        ed.pfile = g.chance(50) ? static_cast<uint32_t>(g.range(1, 0x1000)) : 0;
        ed.mem = g.chance(50) ? static_cast<uint32_t>(g.range(1, 0x1000)) : 0;
        return static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00545dc8), 0x3f9, 0, 0, 0, 0, data));
    };
    add("nbStartBattleEventSound", [=](Gen& g) {
        eventWorld(g);
        return Pair{[] { return origVmVoid(0x0028f7e8, {FW_MAIN}); }, [] { startEventSound(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    add("nbStopBattleEventSound", [=](Gen& g) {
        eventWorld(g);
        return Pair{[] { return origVmVoid(0x0028f840, {FW_MAIN}); }, [] { stopEventSound(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    add("nbLoadBattleEventPack", [=](Gen& g) {
        eventWorld(g);
        return Pair{[] { return origVm(0x0028f890, {FW_MAIN}); }, [] { return norm(eventPacksLoaded(at<MainProcessData>(FW_MAIN)) ? 1 : 0); }};
    });
    add("nbLoadBattleEventPackInit", [=](Gen& g) {
        eventWorld(g);
        return Pair{[] { return origVmVoid(0x0028f958, {FW_MAIN}); }, [] { loadEventPacks(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    add("nbUpdateEventProcessData", [=](Gen& g) {
        const uint32_t process = g.chance(90) ? eventProcess(g) : static_cast<uint32_t>(dds3StartProcess(0x00777700, 1, 0, 0, 0, 0, 0));
        return Pair{[=] { return origVmVoid(0x0028f9f0, {process}); }, [=] { countEventTime(process); return uint64_t{0}; }};
    });
    add("nbNextEventSeq", [=](Gen& g) {
        const uint32_t process = eventProcess(g);
        const uint32_t ed = g.chance(90) ? static_cast<uint32_t>(dds3GetProcessData(process)) : 0;
        return Pair{[=] { return origVmVoid(0x0028fa48, {ed}); },
                    [=] { nextEventStep(ed ? &at<EventProcessData>(ed) : nullptr); return uint64_t{0}; }};
    });
    add("nbGetEventForm", [](Gen& g) {
        for (int i = 4; i < 14; ++i)
            if (g.chance(40))
                at<Formation>(formAddress(i)).stat &= ~1u;
        return Pair{[] { return origVm(0x0028fa80, {}); }, [] { return norm(static_cast<int32_t>(nocturne::guest::addressOf(eventForm()))); }};
    });
    add("nbCreateBasicEffect", [](Gen& g) {
        const uint32_t p = static_cast<uint32_t>(g.range(0, 0x100)), pos = FW_SCRATCH, rot = FW_SCRATCH + 0x10;
        return Pair{[=] { return origVm(0x0028fad8, {p, pos, rot}); }, [=] { return norm(static_cast<int32_t>(createBasicEffect(p, pos, rot))); }};
    });
    for (const char* which : {"ResetWaitMotion", "SetWaitMotion"}) {
        const std::string name = which;
        add(which, [=](Gen& g) {
            const uint32_t ed = static_cast<uint32_t>(dds3GetProcessData(eventProcess(g)));
            const uint32_t original = name == "ResetWaitMotion" ? 0x0028fb10u : 0x0028fb90u;
            return Pair{[=] { return origVmVoid(original, {ed}); }, [=] {
                            if (name == "ResetWaitMotion")
                                resetWaitMotions(at<EventProcessData>(ed));
                            else
                                setWaitMotions(at<EventProcessData>(ed));
                            return uint64_t{0};
                        }};
        });
    }
    struct DeadFade { const char* name; uint32_t original; int32_t (*rewrite)(int32_t); };
    static const DeadFade kDeadFades[] = {
        {"nbGetDeadEventFadeTime", 0x0028fc38, deadEventFadeTime}, {"nbGetDeadEventFadeOutFrame", 0x0028fc70, deadEventFadeOutFrame},
        {"nbGetDeadEventFadeInFrame", 0x0028fca8, deadEventFadeInFrame}, {"nbGetDeadEventFadeStopFrame", 0x0028fce0, deadEventFadeStopFrame},
    };
    for (const DeadFade& fade : kDeadFades) {
        const DeadFade* f = &fade;
        add(f->name, [=](Gen& g) {
            const int32_t eventno = g.range(0, 399);
            return Pair{[=] { return origVm(f->original, {I(eventno)}); }, [=] { return norm(f->rewrite(eventno)); }};
        });
    }
    add("nbEventProcess1", [=](Gen& g) {
        const uint32_t process = eventProcess(g);
        return Pair{[=] { return origVm(0x0028fe48, {process}); }, [=] { return norm(static_cast<int32_t>(runEventStart(process))); }};
    });
    add("nbEventProcess3", [=](Gen& g) {
        const uint32_t process = eventProcess(g);
        return Pair{[=] { return origVm(0x0028fd18, {process}); }, [=] { return norm(static_cast<int32_t>(runEventSetup(process))); }};
    });
    add("nbEventShutdown", [=](Gen& g) {
        const uint32_t process = eventProcess(g);
        at<MainProcessData>(FW_MAIN).EventProcessID = process;
        return Pair{[=] { return origVmVoid(0x0028fec8, {process}); }, [=] { shutdownEvent(process); return uint64_t{0}; }};
    });
    add("nbInitEventProcess", [=](Gen& g) {
        eventWorld(g);
        return Pair{[] { return origVmVoid(0x0028ffb0, {FW_MAIN}); }, [] { startEvent(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    // ---- the battle's sounds (nbSound) ----
    // A formation with a unit, and its id as the sound table knows it.
    auto soundForm = [](Gen& g) {
        int f = g.range(0, 13);
        while (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)))
            f = g.range(0, 13);
        Formation& form = at<Formation>(formAddress(f));
        form.formindex = static_cast<int16_t>(f);
        UnitWork& unit = at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f)));
        unit.id = static_cast<uint16_t>(g.chance(10) ? g.range(0x150, lastDevilWithAi()) : g.range(1, 0x14f));
        return formAddress(f);
    };
    // The table of ten units' banks, some in use (the units' ids, or others),
    // their files loading or loaded.
    auto soundWorld = [=](Gen& g) {
        koukaWorld(g);
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.sound_mem = ps2MemoryHandleAllocate(kSoundEntries * static_cast<int32_t>(sizeof(SoundEntry)));
        main.sound = ps2MemoryHandleAcquirePointer(main.sound_mem);
        std::vector<uint32_t> forms, ids;
        for (int k = 0; k < 4; ++k)
            forms.push_back(soundForm(g));
        for (uint32_t f : forms)
            ids.push_back(static_cast<uint32_t>(formationUnitId(at<Formation>(f))));
        const bool full = g.chance(5);
        for (int i = 0; i < kSoundEntries; ++i) {
            SoundEntry& e = at<SoundEntry>(main.sound + static_cast<uint32_t>(i) * sizeof(SoundEntry));
            e = SoundEntry{};
            if (!full && !g.chance(55))
                continue;
            e.used = 1;
            e.unitid = static_cast<uint16_t>(g.chance(50) ? ids[g.below(4)] : static_cast<uint32_t>(g.range(0, 0x17f)));
            e.refs = g.range(1, 3);
            for (int k = 0; k < kMotionSounds; ++k) {
                if (g.chance(30))
                    e.requests[k] = 0x00779000u + static_cast<uint32_t>(g.range(1, 0xfff));
                if (g.chance(40))
                    e.handles[k] = 0x0077a001u + 0x10u * static_cast<uint32_t>(g.range(0, 0xff));
            }
            if (g.chance(40))
                e.talkRequest = 0x00779000u + static_cast<uint32_t>(g.range(1, 0xfff));
            if (g.chance(50))
                e.talkHandle = 0x0077a001u + 0x10u * static_cast<uint32_t>(g.range(0, 0xff));
        }
        main.stat = static_cast<uint32_t>(g.rng()) & ~0x200u;
        return forms;
    };
    // One of those formations, or any other with a unit.
    auto someSoundForm = [=](Gen& g, const std::vector<uint32_t>& forms) {
        return g.chance(70) ? forms[g.below(static_cast<uint32_t>(forms.size()))] : soundForm(g);
    };
    auto someUnitId = [=](Gen& g, const std::vector<uint32_t>& forms) {
        return g.chance(60) ? static_cast<uint32_t>(formationUnitId(at<Formation>(forms[g.below(static_cast<uint32_t>(forms.size()))])))
                            : static_cast<uint32_t>(g.range(0, 0x17f));
    };
    add("GetUnitID", [=](Gen& g) {
        const uint32_t form = soundForm(g);
        return Pair{[=] { return origVm(0x0028d070, {form}); }, [=] { return norm(formationUnitId(at<Formation>(form))); }};
    });
    add("nbGetMotionSeNo", [](Gen& g) {
        const int32_t model = g.chance(10) ? 0 : g.range(1, 303), motion = g.range(0, 26);
        return Pair{[=] { return origVm(0x0028d0b0, {I(model), I(motion)}); }, [=] { return norm(motionSound(model, motion)); }};
    });
    add("GetMotionMIDI", [](Gen& g) {
        const int32_t id = g.range(0, 0x17f), motion = g.range(0, 25);
        return Pair{[=] { return origVm(0x0028d100, {I(id), I(motion)}); }, [=] { return norm(static_cast<int32_t>(motionBank(id, motion))); }};
    });
    add("nbGetMotionMIDI", [=](Gen& g) {
        const uint32_t form = soundForm(g);
        const int32_t motion = g.range(0, 25);
        return Pair{[=] { return origVm(0x0028d178, {form, I(motion)}); },
                    [=] { return norm(static_cast<int32_t>(formationMotionBank(at<Formation>(form), motion))); }};
    });
    add("GetNegoMIDI", [](Gen& g) {
        const int32_t id = g.range(0, 0x17f);
        return Pair{[=] { return origVm(0x0028d1a8, {I(id)}); }, [=] { return norm(static_cast<int32_t>(talkBank(id))); }};
    });
    add("nbGetNegoMIDI", [=](Gen& g) {
        const uint32_t form = soundForm(g);
        return Pair{[=] { return origVm(0x0028d1b8, {form}); }, [=] { return norm(static_cast<int32_t>(formationTalkBank(at<Formation>(form)))); }};
    });
    add("nbMemoryLoadNegoSe", [=](Gen& g) {
        const uint32_t form = someSoundForm(g, soundWorld(g));
        return Pair{[=] { return origVm(0x0028d1d8, {form}); }, [=] { return norm(loadTalkSound(at<Formation>(form))); }};
    });
    add("nbMemoryLoadMotionSe", [=](Gen& g) {
        const uint32_t form = someSoundForm(g, soundWorld(g));
        const int32_t motion = g.chance(5) ? -1 : g.range(0, 25);
        return Pair{[=] { return origVm(0x0028d298, {form, I(motion)}); }, [=] { return norm(loadMotionSound(at<Formation>(form), motion)); }};
    });
    add("nbReleaseUnitSounds (0x28D3A8)", [=](Gen& g) {
        const uint32_t id = someUnitId(g, soundWorld(g));
        return Pair{[=] { return origVmVoid(0x0028d3a8, {id}); }, [=] { releaseUnitSounds(id); return uint64_t{0}; }};
    });
    add("nbRetainUnitSounds (0x28D418)", [=](Gen& g) {
        const uint32_t id = someUnitId(g, soundWorld(g));
        return Pair{[=] { return origVm(0x0028d418, {id}); }, [=] { return norm(static_cast<int32_t>(nocturne::guest::addressOf(retainUnitSounds(id)))); }};
    });
    add("nbRequestUnitSounds (0x28D4B8)", [=](Gen& g) {
        const uint32_t id = someUnitId(g, soundWorld(g));
        return Pair{[=] { return origVm(0x0028d4b8, {id}); }, [=] { return norm(requestUnitSounds(id)); }};
    });
    add("nbUpdateSoundTable", [=](Gen& g) {
        soundWorld(g);
        return Pair{[] { return origVmVoid(0x0028d5c0, {FW_MAIN}); }, [] { updateSoundTable(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    add("nbEmptySoundEntry", [=](Gen& g) {   // (0x28D6C0)
        soundWorld(g);
        return Pair{[] { return origVm(0x0028d6c0, {}); }, [] { return norm(emptySoundEntry()); }};
    });
    add("nbFindUnitSounds (0x28D718)", [=](Gen& g) {
        const uint32_t id = someUnitId(g, soundWorld(g));
        return Pair{[=] { return origVm(0x0028d718, {id}); }, [=] { return norm(findUnitSounds(id)); }};
    });
    add("nbFreeSound1", [=](Gen& g) {
        soundWorld(g);
        const int32_t index = g.range(0, kSoundEntries - 1);
        return Pair{[=] { return origVmVoid(0x0028d778, {FW_MAIN, I(index)}); },
                    [=] { clearSoundEntry(at<MainProcessData>(FW_MAIN), index); return uint64_t{0}; }};
    });
    add("nbFreeSound", [=](Gen& g) {
        soundWorld(g);
        return Pair{[] { return origVmVoid(0x0028d850, {FW_MAIN}); }, [] { freeSounds(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    add("nbInitSound", [](Gen& g) {
        koukaWorld(g);
        return Pair{[] { return origVmVoid(0x0028d8b0, {FW_MAIN}); }, [] { initSounds(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    // The music: the encounter's type (sometimes an area pack's, or none),
    // and the loader's state.
    auto musicWorld = [](Gen& g) {
        koukaWorld(g);
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.encpackno = g.chance(20) ? 0 : g.chance(5) ? -1 : g.range(1, 255);
        main.encno = g.range(0, 1269);
        uint32_t* state = &at<uint32_t>(difftest::version::dataOrDie(0x00551524));
        static const uint32_t pieces[] = {0, 0x150001, 0x150002, 0x1f0002, 0x40001, 0x110000, 0x800001};
        for (int i = 0; i < 3; ++i)
            state[i] = g.pick(pieces);
        if (g.chance(10))
            state[1] = 0xffffffffu;
        state[3] = static_cast<uint32_t>(g.range(0, 40));
        state[4] = static_cast<uint32_t>(g.range(1, 0x8b)) << 16;
        state[5] = static_cast<uint32_t>(g.range(1, 0x8b)) << 16;
        state[6] = static_cast<uint32_t>(g.chance(30) ? 0 : g.range(0, 6));
        state[7] = static_cast<uint32_t>(g.chance(70) ? 0 : 1);
    };
    auto encdata = [](Gen& g) {
        return g.chance(30) ? 0u : static_cast<uint32_t>(g.range(0, 255)) << 24 | static_cast<uint32_t>(g.range(0, 1269));
    };
    add("GetBgmCategory", [](Gen& g) {
        const int32_t pack = g.chance(20) ? 0 : g.chance(5) ? -g.range(1, 5) : g.range(1, 255), encno = g.range(0, 1269);
        return Pair{[=] { return origVm(0x0028cfc8, {I(pack), I(encno)}); }, [=] { return norm(encounterMusic(pack, encno)); }};
    });
    add("nbGetBgmCategoryInBattle", [=](Gen& g) {
        musicWorld(g);
        return Pair{[] { return origVm(0x0028d028, {}); }, [] { return norm(battleMusic()); }};
    });
    add("nbGetBgmCategoryInField", [=](Gen& g) {
        const uint32_t data = encdata(g);
        return Pair{[=] { return origVm(0x0028d050, {data}); }, [=] { return norm(fieldMusic(data)); }};
    });
    // ---- random encounters (nbEncount) ----
    // The walk so far, the count, the threshold rolled (or not yet), the
    // field skills, Kagutsuchi and the Demi-fiend's level.
    auto encounterWorld = [](Gen& g) {
        GlobalWork& work = nocturne::dat::globalWork();
        work.encountDistance = nocturne::ee::Float::fromBits(static_cast<uint32_t>(floatBits(g.chance(20) ? 0.0f : static_cast<float>(g.range(0, 4000)) / 16.0f)));
        work.encountCount = static_cast<uint16_t>(g.chance(5) ? g.range(64995, 64999) : g.chance(10) ? g.range(64985, 65535) : g.chance(40) ? g.range(0, 60) : g.range(0, 400));
        work.fieldskills = static_cast<uint32_t>(g.range(0, 15));
        work.moon_phase = static_cast<uint8_t>(g.range(0, 15));
        work.units[0].level = static_cast<uint16_t>(g.range(1, 99));
        for (uint32_t& bits : work.event_bits)
            bits = static_cast<uint32_t>(g.rng());
        at<int32_t>(difftest::version::dataOrDie(0x00551520)) = g.chance(40) ? 0 : g.chance(10) ? -g.range(1, 10) : g.chance(50) ? g.range(16, 40) : g.range(16, 700);
        if constexpr (nocturne::kVariant == nocturne::Variant::Hardtype) {   // the moon phase and 25th Magatama it reads
            at<uint8_t>(0x01248f41) = static_cast<uint8_t>(g.chance(40) ? 8 : g.range(0, 15));
            at<uint8_t>(0x0124a213) = static_cast<uint8_t>(g.chance(50) ? 0 : g.range(1, 25));
        }
    };
    // (Pack 169 is the only one with a second event bit.)
    auto somePack = [](Gen& g) { return g.chance(5) ? 0 : g.chance(10) ? 169 : g.range(1, 255); };
    add("nbGetEncountJoken", [=](Gen& g) {
        encounterWorld(g);
        const int32_t pack = somePack(g);
        // (Hardtype's callers go through 0x2FEB00; its nbGetEncountJoken takes a flag in v0)
        const uint32_t entry = nocturne::kVariant == nocturne::Variant::Hardtype ? 0x002feb00u : 0x0028c9f0u;
        return Pair{[=] { return origVm(entry, {I(pack)}); }, [=] { return norm(encounterTable(pack)); }};
    });
    add("nbGetEncountMax", [=](Gen& g) {
        encounterWorld(g);
        const int32_t pack = somePack(g);
        return Pair{[=] { return origVm(0x0028cb68, {I(pack)}); }, [=] { return norm(encounterThreshold(pack)); }};
    });
    add("nbGetEncountCnt", [=](Gen& g) {
        encounterWorld(g);
        return Pair{[] { return origVm(0x0028cc98, {}); }, [] { return norm(encounterCount()); }};
    });
    add("nbEncountCalc", [=](Gen& g) {
        encounterWorld(g);
        const int32_t pack = somePack(g);
        float length = g.chance(10) ? 0.0f : g.chance(10) ? -1.5f : static_cast<float>(g.range(1, 9000)) / 16.0f;
        if (g.chance(10)) {   // (exactly a step)
            const uint32_t walked = nocturne::dat::globalWork().encountDistance.bits();
            float f;
            std::memcpy(&f, &walked, 4);
            length = 100.0f - f;
        }
        if (g.chance(5)) {   // (one step without Riberama onto the count's cap)
            GlobalWork& work = nocturne::dat::globalWork();
            work.encountCount = 64999;
            work.fieldskills &= ~2u;
            work.encountDistance = nocturne::ee::Float::fromBits(0);
            length = 100.0f;
        }
        const uint32_t bits = static_cast<uint32_t>(floatBits(length));
        return Pair{[=] { return origVm(0x0028cca8, {I(pack)}, {bits}); },
                    [=] { return norm(walkForEncounter(pack, nocturne::ee::Float::fromBits(bits))); }};
    });
    add("nbCheckEncountLevel", [=](Gen& g) {
        encounterWorld(g);
        const int32_t encno = g.chance(5) ? 0 : g.range(1, 1269);
        return Pair{[=] { return origVm(0x0028cee0, {I(encno)}); }, [=] { return norm(encounterWorthFighting(encno)); }};
    });
    add("nbResetEncountCount", [=](Gen& g) {
        encounterWorld(g);
        return Pair{[] { return origVmVoid(0x0028cfb0, {}); }, [] { resetEncounterCount(); return uint64_t{0}; }};
    });
    add("nbBgmLoadChk", [=](Gen& g) {
        musicWorld(g);
        return Pair{[] { return origVm(0x0028d918, {}); }, [] { return norm(musicLoaded()); }};
    });
    add("nbBgmLoad", [=](Gen& g) {
        musicWorld(g);
        const uint32_t data = encdata(g);
        if (g.chance(70))
            at<uint32_t>(difftest::version::dataOrDie(0x00551524) + 0x18) = 0;
        return Pair{[=] { return origVmVoid(0x0028d9e0, {data}); }, [=] { loadMusic(data); return uint64_t{0}; }};
    });
    struct MusicCall { const char* name; uint32_t original; void (*rewrite)(); };
    static const MusicCall kMusicCalls[] = {
        {"nbBgmNext", 0x0028dd50, nextMusic}, {"nbBgmPlay", 0x0028dd60, playMusic}, {"nbBgmTrans", 0x0028dd78, switchMusic},
        {"nbBgmFadeOut", 0x0028dda8, fadeOutMusic}, {"nbBgmStop", 0x0028ddd0, stopMusic}, {"nbBgmChannelReset", 0x0028de28, resetMusicChannel},
    };
    for (const MusicCall& call : kMusicCalls) {
        const MusicCall* m = &call;
        add(m->name, [=](Gen& g) {
            musicWorld(g);
            return Pair{[=] { return origVmVoid(m->original, {}); }, [=] { m->rewrite(); return uint64_t{0}; }};
        });
    }
    // The battle's opening (battle/opening.hpp): its steps, with the event
    // packs, the music, and sometimes the flight model's encounter.
    struct OpeningStep { const char* name; uint32_t original; uint32_t (*rewrite)(uint32_t); };
    static const OpeningStep kBattleOpeningSteps[] = {
        {"FUN_00249b68", 0x00249b68, nocturne::nb::openingRequestStage}, {"FUN_00249b18", 0x00249b18, nocturne::nb::openingLoadPacks},
        {"FUN_00249ab0", 0x00249ab0, nocturne::nb::openingWaitPacks},    {"FUN_00249a88", 0x00249a88, nocturne::nb::openingLoadMusic},
        {"FUN_00249a58", 0x00249a58, nocturne::nb::openingWaitMusic},    {"FUN_00249a38", 0x00249a38, nocturne::nb::openingPlayMusic},
    };
    for (const OpeningStep& step : kBattleOpeningSteps) {
        const OpeningStep* o = &step;
        add(o->name, [=](Gen& g) {
            eventWorld(g);
            musicWorld(g);
            MainProcessData& main = at<MainProcessData>(FW_MAIN);
            if (g.chance(30))
                main.encno = 0x14d;   // the flight model's
            main.flyh = g.chance(40) ? 0 : FW_SCRATCH + 0x300;
            at<uint32_t>(FW_SCRATCH + 0x300 + 0x60) = FW_SCRATCH + 0x380;
            at<uint32_t>(FW_SCRATCH + 0x380 + 8) = static_cast<uint32_t>(g.rng());
            main.StageProcessID = static_cast<uint32_t>(g.range(0, 0x1000));
            return Pair{[=] { return origVm(o->original, {0}); }, [=] { return norm(static_cast<int32_t>(o->rewrite(0))); }};
        });
    }
    // ---- the encounter's opening (nbEncProcess) ----
    // Units present or not, hidden until they appear, their models loading;
    // the fade, back attack and moon glow bits; the load timing.
    auto encProcessWorld = [](Gen& g) {
        koukaWorld(g);
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.stat = (main.stat & ~0xc10u) | (g.chance(40) ? 0x10u : 0u) | (g.chance(40) ? 0x400u : 0u) | (g.chance(40) ? 0x800u : 0u);
        // Each formation's object (a control block whose +0xC4 the glow sets)
        // and unit handle (+0xA4 bit 0x10000 while its model loads), in
        // scratch. (nbEncProcess3's slots past the fourteen read the parties'
        // memory as it is.)
        for (int f = 0; f < 14; ++f) {
            Formation& form = at<Formation>(formAddress(f));
            form.formindex = static_cast<int16_t>(f);
            form.stat = (form.stat & ~3u) | static_cast<uint32_t>(g.chance(60) ? 1 : 0) | static_cast<uint32_t>(g.chance(85) ? 2 : 0);
            form.flag = (form.flag & ~8u) | (g.chance(50) ? 8u : 0u);
            form.anime = static_cast<uint32_t>(g.rng()) & ~0x200u;
            const uint32_t block = FW_SCRATCH + 0x20u * static_cast<uint32_t>(f);
            form.basic = block;
            at<uint32_t>(block + 0x1c) = FW_SCRATCH + 0x200u + 0x10u * static_cast<uint32_t>(f) - 0xc4u;
            form.hunit = g.chance(5) ? 0 : FW_SCRATCH + 0x400u + 0x10u * static_cast<uint32_t>(f) - 0xa4u;
            if (form.hunit)
                at<uint32_t>(form.hunit + 0xa4) = g.chance(90) ? 0 : 0x10000u;
            Party& party = *nocturne::guest::table<Party>(FW_PARTY + 128u * static_cast<uint32_t>(f));
            party.flag = static_cast<int16_t>((party.flag & ~9) | (g.chance(60) ? g.pick<int16_t>({1, 8, 9}) : 0));
            party.formindex = static_cast<int16_t>(f);
        }
        at<int32_t>(difftest::version::dataOrDie(0x0054e800)) = g.range(0, 100000);                                  // the frame counter
        at<int32_t>(difftest::version::dataOrDie(0x00551548)) = at<int32_t>(difftest::version::dataOrDie(0x0054e800)) - g.range(0, 300);           // the loading's start
        at<int32_t>(difftest::version::dataOrDie(0x0055154c)) = g.chance(50) ? 0 : g.range(1, 300);                  // ... and time
        at<uint32_t>(FW_SCRATCH + 0xbf0) = static_cast<uint32_t>(g.rng());             // (varies the fakes' answers)
        nocturne::dat::globalWork().moon_phase = static_cast<uint8_t>(g.chance(50) ? 8 : g.range(0, 15));
        main.statusMessageTable = iface::helpWorld(g, {6, 7}).id;   // (a back attack's status message, either form)
    };
    auto encProcess = [=](Gen& g) {
        encProcessWorld(g);
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00551550), 0x3f9, 0, 0, 0, 0, 0));
        at<int32_t>(process + 0x28) = g.range(0, 64);   // its run time
        return process;
    };
    struct EncStep { const char* name; uint32_t original; uint32_t (*rewrite)(uint32_t); };
    static const EncStep kEncSteps[] = {
        {"nbEncProcess1", 0x0028e2c8, startEncounterLoad}, {"nbEncProcess2", 0x0028e250, loadEnemyModels},
        {"nbEncProcess2_5", 0x0028e0e8, showEnemies}, {"nbEncProcess2_55", 0x0028dfc8, setUpEncounterScene},
        {"nbEncProcess2_6", 0x0028def0, showPlayers}, {"nbEncProcess3", 0x0028de40, finishEncounter},
    };
    for (const EncStep& step : kEncSteps) {
        const EncStep* s = &step;
        add(s->name, [=](Gen& g) {
            const uint32_t process = encProcess(g);
            return Pair{[=] { return origVm(s->original, {process}); }, [=] { return norm(static_cast<int32_t>(s->rewrite(process))); }};
        });
    }
    add("nbEncShutdown", [=](Gen& g) {
        const uint32_t process = encProcess(g);
        at<MainProcessData>(FW_MAIN).EncProcessID = process;
        return Pair{[=] { return origVmVoid(0x0028e340, {process}); }, [=] { shutdownEncounter(process); return uint64_t{0}; }};
    });
    add("nbInitEncProcess", [=](Gen& g) {
        encProcessWorld(g);
        at<MainProcessData>(FW_MAIN).MainProcessID = static_cast<uint32_t>(dds3StartProcess(difftest::version::dataOrDie(0x00544350), 1, 0, 0, 0, 0, 0));
        return Pair{[] { return origVmVoid(0x0028e360, {FW_MAIN}); }, [] { startEncounter(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    add("nbFormDispOff2", [](Gen& g) {
        const uint32_t f = formAddress(g.range(0, 13));
        return Pair{[=] { return origVmVoid(0x00289bb8, {f}); }, [=] { hideFormation(at<Formation>(f)); return uint64_t{0}; }};
    });
    struct StepGroup { const char* name; uint32_t group, steps; const TalkStep* rewrite; int32_t count; const char* flow;
                       uint32_t dispatch; int32_t (*flowRewrite)(TalkState&); };
    static const StepGroup kStepGroups[] = {
        {"Flow1", 1, difftest::version::data(0x004ef4b0), kOpeningSteps, 40, "nbNegoFlowOne", 0x0026ead8, openingFlow},
        {"Flow2", 2, difftest::version::data(0x004ef780), kFullMoonSteps, 17, "nbNegoFlowFullMoon", 0x00274e60, fullMoonFlow},
        {"Flow3", 3, difftest::version::data(0x004ef7c8), kStockSteps, 3, "nbNegoFlowStock", 0x00274f08, stockFlow},
        {"Flow4", 4, difftest::version::data(0x004ef7d8), kKinSteps, 14, "nbNegoFlowDouchara", 0x00275750, kinFlow},
        {"Flow5", 5, difftest::version::data(0x004ef810), kFatedSteps, 22, "nbNegoFlowInnen", 0x00275dc8, fatedFlow},
        {"Flow6", 6, difftest::version::data(0x004ef550), kBargainSteps, 82, "nbNegoFlowTwo", 0x002726e8, bargainFlow},
        {"Flow7", 7, difftest::version::data(0x004ef868), kQuestionSteps, 27, "nbNegoFlowQuestion", 0x00276730, questionFlow},
        {"Flow8", 8, difftest::version::data(0x004ef8d8), kFightSteps, 20, "nbNegoFlowFight", 0x00276cd8, fightFlow},
        {"Flow9", 9, difftest::version::data(0x004ef698), kDealSteps, 23, "nbNegoFlowOk", 0x00273178, dealFlow},
        {"Flow10", 10, difftest::version::data(0x004ef6f8), kNoDealSteps, 34, "nbNegoFlowNg", 0x002741f8, noDealFlow},
        {"Flow11", 11, difftest::version::data(0x004ef928), kDrainSteps, 10, "nbNegoFlowDrain", 0x00277388, drainFlow},
        {"Flow12", 12, difftest::version::data(0x004ef960), kSpeakUpSteps, 50, "nbNegoFlowMukan", 0x00278718, speakUpFlow},
        {"Flow13", 13, difftest::version::data(0x004efa28), kAmbushSteps, 13, "nbNegoFlowSensei", 0x00278c88, ambushFlow},
        {"Flow14", 14, difftest::version::data(0x004ef950), kAskToJoinSteps, 3, "nbNegoFlowBinjo", 0x00277478, askToJoinFlow},
        {"Flow15", 15, difftest::version::data(0x004efa60), kMercySteps, 24, "nbNegoFlowInoti", 0x00279480, mercyFlow},
        {"Flow16", 16, difftest::version::data(0x004efac0), kTauntSteps, 4, "nbNegoFlowKoketa", 0x00279660, tauntFlow},
    };
    for (const StepGroup& group : kStepGroups) {
        const StepGroup* gr = &group;
        for (int32_t i = 0; i < gr->count; ++i) {
            if (!gr->rewrite[i])
                continue;
            static std::deque<std::string> names;   // (stable: the names are kept by pointer)
            names.push_back(std::string(gr->name) + "_" + std::to_string(i));
            const char* name = names.back().c_str();
            talk(name, [=](Gen& g) {
                talkStepWorld(g);
                at<TalkState>(FW_TALK).talkId = gr->group << 16 | static_cast<uint32_t>(i);
                const uint32_t original = difftest::version::maniaxCodeOrDie(at<uint32_t>(gr->steps + 4u * static_cast<uint32_t>(i)));   // (the table holds the version's own addresses)
                const TalkStep rewrite = gr->rewrite[i];
                return Pair{[=] { return origVm(original, {FW_TALK}); }, [=] { return norm(rewrite(at<TalkState>(FW_TALK))); }};
            });
        }
        talk(gr->flow, [=](Gen& g) {
            talkStepWorld(g);
            int32_t i = g.range(1, gr->count - 1);
            while (!gr->rewrite[i])
                i = g.range(1, gr->count - 1);
            at<TalkState>(FW_TALK).talkId = gr->group << 16 | static_cast<uint32_t>(i);
            const uint32_t original = gr->dispatch;
            auto rewrite = gr->flowRewrite;
            return Pair{[=] { return origVm(original, {FW_TALK}); }, [=] { return norm(rewrite(at<TalkState>(FW_TALK))); }};
        });
    }
    add("nbFormDispOn2", [](Gen& g) {
        const uint32_t f = formAddress(g.range(0, 13));
        return Pair{[=] { return origVmVoid(0x00289c60, {f}); }, [=] { showFormation(at<Formation>(f)); return uint64_t{0}; }};
    });
    add("nbResetFormPosRot", [](Gen& g) {
        const uint32_t f = formAddress(g.range(0, 13));
        at<Formation>(f).stat ^= g.chance(50) ? 1u : 0u;
        return Pair{[=] { return origVmVoid(0x0028a238, {f}); }, [=] { resetFormationPlace(at<Formation>(f)); return uint64_t{0}; }};
    });
    // A formation's model shown or not (stat bits 1 and 2), any slot.
    auto modelStat = [](Gen& g) {
        for (int f = 0; f < 16; ++f)
            at<Formation>(formAddress(f)).stat = (at<Formation>(formAddress(f)).stat & ~3u) | static_cast<uint32_t>(g.range(0, 3));
    };
    for (int on = 0; on < 2; ++on) {
        add(on ? "nbFormDispOn" : "nbFormDispOff", [=](Gen& g) {
            modelStat(g);
            const int32_t f = g.range(0, 15);
            const uint32_t original = on ? 0x00289bd0u : 0x00289b30u;
            return Pair{[=] { return origVmVoid(original, {I(f)}); },
                        [=] { on ? showFormationModel(f) : hideFormationModel(f); return uint64_t{0}; }};
        });
        add(on ? "nbGroupFormDispOn" : "nbGroupFormDispOff", [=](Gen& g) {
            modelStat(g);
            const int32_t side = g.range(-1, 3);
            const uint32_t original = on ? 0x00289d30u : 0x00289c78u;
            return Pair{[=] { return origVmVoid(original, {I(side)}); }, [=] { on ? showSide(side) : hideSide(side); return uint64_t{0}; }};
        });
        add(on ? "nbAllFormDispOn" : "nbAllFormDispOff (0x289DE8)", [=](Gen& g) {
            modelStat(g);
            const uint32_t original = on ? 0x00289e28u : 0x00289de8u;
            return Pair{[=] { return origVmVoid(original, {}); }, [=] { on ? showAllFormations() : hideAllFormations(); return uint64_t{0}; }};
        });
    }
    add("nbSingleFormExceptedDispOff", [=](Gen& g) {
        modelStat(g);
        const uint32_t f = formAddress(g.range(0, 15));
        return Pair{[=] { return origVmVoid(0x00289e68, {f}); }, [=] { showOnly(at<Formation>(f)); return uint64_t{0}; }};
    });
    add("nbDoubleFormExceptedDispOff (0x289ED0)", [=](Gen& g) {
        modelStat(g);
        const uint32_t f = formAddress(g.range(0, 15)), other = formAddress(g.range(0, 15));
        return Pair{[=] { return origVmVoid(0x00289ed0, {f, other}); }, [=] { showOnly(at<Formation>(f), at<Formation>(other)); return uint64_t{0}; }};
    });
    add("nbSetFormPos", [=](Gen& g) {
        modelStat(g);
        const uint32_t f = formAddress(g.range(0, 15)), pos = FW_SCRATCH + 0x800;
        for (int k = 0; k < 4; ++k)
            at<uint32_t>(pos + 4u * k) = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVmVoid(0x0028a0e8, {f, pos}); },
                    [=] { setFormationPosition(at<Formation>(f), at<Vec4>(pos)); return uint64_t{0}; }};
    });
    add("nbSetFormPosRot", [=](Gen& g) {
        modelStat(g);
        const uint32_t f = formAddress(g.range(0, 15)), pos = FW_SCRATCH + 0x800, rot = FW_SCRATCH + 0x810;
        for (int k = 0; k < 8; ++k)
            at<uint32_t>(pos + 4u * k) = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVmVoid(0x0028a200, {f, pos, rot}); },
                    [=] { setFormationPlace(at<Formation>(f), at<Vec4>(pos), at<Vec4>(rot)); return uint64_t{0}; }};
    });
    add("nbResetAllFormPosRot", [=](Gen& g) {
        modelStat(g);
        return Pair{[] { return origVmVoid(0x0028a288, {}); }, [] { resetAllFormationPlaces(); return uint64_t{0}; }};
    });
    struct FormConstant { const char* name; uint32_t original; nocturne::ee::Float (*rewrite)(); };
    static const FormConstant kFormConstants[] = {
        {"nbGetPartyDistance", 0x0028a300, partyDistance}, {"nbGetSummonInterval", 0x0028a310, summonInterval},
        {"nbFormationGetRadiusDef", 0x0028a320, defaultRadius}, {"nbGetEnemyInterval", 0x0028a338, enemyInterval},
    };
    for (const FormConstant& constant : kFormConstants) {
        const FormConstant* c = &constant;
        add(c->name, [=](Gen& g) {
            at<uint32_t>(difftest::version::dataOrDie(0x005514fc)) = static_cast<uint32_t>(g.rng());
            return Pair{[=] { origVm(c->original, {}); return uint64_t{difftest::iface::origVmFloat()}; },
                        [=] { return uint64_t{c->rewrite().bits()}; }};
        });
    }
    add("nbPanelPartyShow", [](Gen& g) {
        at<uint8_t>(difftest::version::dataOrDie(0x0055123d)) = static_cast<uint8_t>(g.range(0, 1));
        return Pair{[] { return origVmVoid(0x00282258, {}); }, [] { panelPartyShow(); return uint64_t{0}; }};
    });
    add("nbPanelPartyHide", [](Gen& g) {
        at<uint8_t>(difftest::version::dataOrDie(0x0055123d)) = static_cast<uint8_t>(g.range(0, 1));
        return Pair{[] { return origVmVoid(0x00282268, {}); }, [] { panelPartyHide(); return uint64_t{0}; }};
    });
    // ---- a skill effect's cuts (effBTL) and the boss effects' lengths ----
    // An effect of noise at FW_BTL_EFFECT, and a cut playing one of its
    // descriptions at FW_BTL_CUT.
    auto effectWorld = [](Gen& g) {
        for (uint32_t i = 0; i < 0xc48; i += 4)
            at<uint32_t>(FW_BTL_EFFECT + i) = g.chance(70) ? static_cast<uint32_t>(g.range(0, 200)) : static_cast<uint32_t>(g.rng());
        for (uint32_t i = 0; i < 0x120; i += 4)
            at<uint32_t>(FW_BTL_CUT + i) = static_cast<uint32_t>(g.rng());
        eff::BattleCut& cut = at<eff::BattleCut>(FW_BTL_CUT);
        cut.effect = FW_BTL_EFFECT;
        cut.cutNo = static_cast<uint16_t>(g.chance(90) ? g.range(0, 3) : g.range(4, 0xffff));
        cut.description = FW_BTL_EFFECT + (g.chance(50) ? 0 : 0x618u);
        cut.frame = static_cast<uint32_t>(g.range(0, 120));
        cut.cutEndFrame = static_cast<uint32_t>(g.range(0, 120));
        cut.drawEndFrame = static_cast<uint32_t>(g.range(0, 120));
    };
    add("effBTLGetMotionChangeFrame", [=](Gen& g) {
        effectWorld(g);
        const uint32_t cutNo = static_cast<uint32_t>(g.range(0, 4));
        return Pair{[=] { return origVm(0x0016ab70, {FW_BTL_EFFECT, cutNo}); },
                    [=] { return norm(static_cast<int32_t>(eff::motionChangeFrame(FW_BTL_EFFECT, static_cast<uint16_t>(cutNo)))); }};
    });
    add("effBTLGetCutEndFrame", [=](Gen& g) {
        effectWorld(g);
        const uint32_t cutNo = static_cast<uint32_t>(g.range(0, 4));
        return Pair{[=] { return origVm(0x0016aba0, {FW_BTL_EFFECT, cutNo}); },
                    [=] { return norm(static_cast<int32_t>(eff::cutEndFrame(FW_BTL_EFFECT, static_cast<uint16_t>(cutNo)))); }};
    });
    add("effBTLCutGetMotionChangeFrame", [=](Gen& g) {
        effectWorld(g);
        return Pair{[] { return origVm(0x0016aec0, {FW_BTL_CUT}); },
                    [] { return norm(static_cast<int32_t>(eff::motionChangeFrame(at<eff::BattleCut>(FW_BTL_CUT)))); }};
    });
    add("effBTLCutGetCutEndFrame", [=](Gen& g) {
        effectWorld(g);
        return Pair{[] { return origVm(0x0016aee8, {FW_BTL_CUT}); }, [] { return norm(static_cast<int32_t>(eff::cutEndFrame(at<eff::BattleCut>(FW_BTL_CUT)))); }};
    });
    add("effBTLCutGetFrame", [=](Gen& g) {
        effectWorld(g);
        return Pair{[] { return origVm(0x0016aea0, {FW_BTL_CUT}); }, [] { return norm(static_cast<int32_t>(eff::frame(at<eff::BattleCut>(FW_BTL_CUT)))); }};
    });
    add("effBTLCutSetCutEndFrame", [=](Gen& g) {
        effectWorld(g);
        const uint32_t f = static_cast<uint32_t>(g.range(0, 150));
        return Pair{[=] { return origVmVoid(0x0016aed0, {FW_BTL_CUT, f}); },
                    [=] { eff::setCutEndFrame(at<eff::BattleCut>(FW_BTL_CUT), f); return uint64_t{0}; }};
    });
    add("effBTLCutSetDrawEndFrame", [=](Gen& g) {
        effectWorld(g);
        const uint32_t f = static_cast<uint32_t>(g.range(0, 150));
        return Pair{[=] { return origVmVoid(0x0016aef0, {FW_BTL_CUT, f}); },
                    [=] { eff::setDrawEndFrame(at<eff::BattleCut>(FW_BTL_CUT), f); return uint64_t{0}; }};
    });
    add("effBTLCutSetCameraState", [=](Gen& g) {
        effectWorld(g);
        at<MainProcessData>(FW_MAIN).stat ^= g.chance(30) ? 0x1000u : 0u;
        return Pair{[] { return origVmVoid(0x0016b090, {FW_BTL_CUT}); },
                    [] { eff::setCutCameraState(at<eff::BattleCut>(FW_BTL_CUT)); return uint64_t{0}; }};
    });
    add("effBTLSkillSetState", [=](Gen& g) {
        const uint32_t state = g.chance(50) ? static_cast<uint32_t>(g.range(0, 16)) : static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVmVoid(0x0016ba40, {state}); }, [=] { eff::setSkillState(state); return uint64_t{0}; }};
    });
    struct BossLength { const char* name; uint32_t original; int32_t (*rewrite)(); };
    static const BossLength kBossLengths[] = {
        {"effPCPBossONGYGetLength", 0x00198860, eff::ongyokiEffectLength},
        {"effPCPBossONGY2GetLength", 0x00198ff8, eff::ongyokiEffect2Length},
        {"effPCPBossBUNSINGetLength", 0x00199b08, eff::ongyokiCloneEffectLength},
        {"effPCPBossBUNSIN2GetLength", 0x00199cb0, eff::ongyokiCloneEffect2Length},
    };
    for (const BossLength& length : kBossLengths) {
        const BossLength* l = &length;
        add(l->name, [l](Gen&) { return Pair{[l] { return origVm(l->original, {}); }, [l] { return norm(l->rewrite()); }}; });
    }
    for (const char* which : {"nbCameraSetBougai", "nbCameraSetTarget", "nbCameraSetHojo", "nbCameraSetEveTarget", "effBTLSkillGetInvokeFormation"}) {
        const std::string name = which;
        add(which, [=](Gen& g) {
            const uint32_t a = formAddress(g.range(0, 13)), b = formAddress(g.range(0, 13)), c = formAddress(g.range(0, 13));
            at<uint32_t>(difftest::version::dataOrDie(0x005698e0)) = g.chance(90) ? formAddress(g.range(0, 13)) : 0;
            if (name == "nbCameraSetBougai")
                return Pair{[=] { return origVmVoid(0x001b17a0, {a}); }, [=] { cameraOnObstructor(at<Formation>(a)); return uint64_t{0}; }};
            if (name == "nbCameraSetTarget")
                return Pair{[=] { return origVmVoid(0x001b1810, {a}); }, [=] { cameraOnTalkTarget(at<Formation>(a)); return uint64_t{0}; }};
            if (name == "nbCameraSetHojo")
                return Pair{[=] { return origVmVoid(0x001b1850, {a, b, c}); }, [=] { cameraOnHelper(at<Formation>(a), at<Formation>(b), at<Formation>(c)); return uint64_t{0}; }};
            if (name == "nbCameraSetEveTarget")
                return Pair{[=] { return origVmVoid(0x001b1888, {a}); }, [=] { cameraOnEventTarget(at<Formation>(a)); return uint64_t{0}; }};
            return Pair{[] { return origVm(0x0016b940, {}); }, [] { return norm(static_cast<int32_t>(nocturne::guest::addressOf(&nocturne::eff::skillInvoker()))); }};
        });
    }

    // ---- the kouka process: playing the packets ----
    // A packet of one of `types`, its fields random within what the
    // builders put there: a formation (with a model), a party, data words.
    auto playPacket = [](Gen& g, std::initializer_list<int32_t> types) {
        const int f = g.range(0, 13);
        EffectPacket& p = addPacket(queue(), g.range(-1, 2), g.range(-1, 3), uid(g));
        p.type = static_cast<int8_t>(types.begin()[g.below(static_cast<uint32_t>(types.size()))]);
        p.flag = static_cast<uint8_t>(g.chance(70) ? 0 : g.below(4));
        p.time = static_cast<uint16_t>(g.range(0, 3));
        p.form.address = formAddress(f);
        p.party.address = FW_PARTY + 128u * static_cast<uint32_t>(f);
        p.partyno = g.range(0, 13);
        p.data1.setInt(g.chance(30) ? 0 : g.range(-2, 12));
        p.data2.raw = g.chance(50) ? someFloat(g) : static_cast<uint32_t>(g.rng());
        p.v.x = Fl(someFloat(g));
        p.v.y = Fl(someFloat(g));
        p.v.z = Fl(someFloat(g));
        p.v.w = Fl(someFloat(g));
        Formation& form = at<Formation>(p.form.address);
        form.formindex = static_cast<int16_t>(f);
        form.stat = static_cast<uint32_t>(g.rng()) & 0x4fu;
        form.flag = g.chance(70) ? 0 : static_cast<uint32_t>(g.below(8));
        form.anime = (g.chance(50) ? 0x100u : 0u) | (g.chance(50) ? 0x80u : 0u);
        form.ailmentEffect = g.chance(30) ? 0 : 0x00779300u + g.below(0x40);
        form.motionSpeed = Fl(someFloat(g));
        form.dodgeDistance = Fl(someFloat(g));
        form.homeColor = static_cast<uint32_t>(g.rng());
        form.time = static_cast<uint32_t>(g.range(0, 30));
        form.type = g.range(0, 3);
        // An event unit and its model: the unit's flags; the model's
        // animation count (+4, for the fake mdlGetNumOfCut), the animation
        // playing and its speed.
        const uint32_t model = ps2PoolAllocate(0xd0), motion = ps2PoolAllocate(0x40), playing = ps2PoolAllocate(0x40);
        form.hunit = model;
        at<uint32_t>(model + 0x8c) = motion;
        at<uint32_t>(model + 0xa4) = static_cast<uint32_t>(g.rng());
        at<uint32_t>(motion + 4) = static_cast<uint32_t>(g.range(0x10, 0x20));
        at<int16_t>(motion + 0x12) = static_cast<int16_t>(g.range(0, 3));
        at<uint32_t>(motion + 0x1c) = playing;
        at<uint32_t>(playing + 0x20) = someFloat(g);
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        main.party[p.partyno].flag = static_cast<int16_t>(g.chance(70) ? 1 : 0);
        main.actionstackp = g.range(0, 4);
        return iface::addr(&p);
    };
    struct Player {
        const char* name;
        uint32_t original;
        void (*rewrite)(EffectQueue&, EffectPacket&);
        std::vector<int32_t> types;
    };
    static const Player players[] = {
        {"RunBossEffectKouka", 0x0025efd0, playBossEffect, {kOngyokiClone, kOngyokiClone2, kOngyokiOut, kOngyokiOut2, kHitEff}},
        {"RunMoveKouka", 0x0025f1a8, playMove, {kTargetMove, kHomeMove, kRot}},
        {"RunUnitColKouka", 0x0025f370, playUnitColor, {kUnitCol, kUnitHomeCol, kUnitA, kUnitHomeA, kHomeRot}},
        {"RunPressKouka", 0x00260528, playPress, {kPress, kNewPress, kSe}},
        {"RunBadMotKaifukuKouka", 0x00260628, playAilmentMotionCure, {kAilmentMotionCure}},
        {"RunFadeKouka", 0x00260d80, playFade, {kFadeOut, kFadeIn, kSe}},
        {"RunSummonKouka", 0x0025f9a8, playSummon, {kSummon}},
        {"RunDamageMotionKouka", 0x0025f620, playDamageMotion, {kDamageMotion, kAilmentDamageMotion, kAilmentMotion, kAilmentMotion, kLightDamageMotion, kSe}},
        {"RunSkillEffectKouka", 0x0025f100, playSkillEffect, {kSkillEffect, kSkillEffect2, kSkillEffect1, kSkillEffect3, kSe}},
        {"RunMotionKouka", 0x0025f4f0, playMotion, {kMotion, kSkillMotion, kSe}},
        {"RunSeKouka", 0x002606d8, playSound, {kSe, kSe2, kSe3, kMotion}},
        {"RunMotionStopKouka", 0x0025f458, playMotionStop, {kMotionStop, kMotionStopClear, kMotion}},
        {"RunReturnKouka", 0x0025f950, playReturn, {kReturn}},
        {"RunSakeKouka", 0x0025fa50, playDodge, {kDodge}},
        {"RunBadEffKouka", 0x0025fa70, playAilmentEffect, {kAilmentEff}},
        {"RunBadEffKaifukuKouka", 0x0025faf8, playAilmentCureEffect, {kAilmentCureEff}},
        {"RunHitEffectKouka", 0x0025fb58, playHitEffect, {kHitEff}},
        {"RunHpMpKouka", 0x002604e8, playHpMp, {kHpMp}},
        {"RunBadStatKouka", 0x00260600, playAilment, {kAilment}},
        {"RunHitStopKouka", 0x00260928, playHitStop, {kHitStop}},
        {"RunAnalyzeKouka", 0x00260978, playAnalyze, {kAnalyze}},
        {"RunFormOnOffKouka", 0x00260a00, playFormationShow, {kFormOnOff}},
        {"RunFormFlagOnOffKouka", 0x00260a58, playFormationFlag, {kFormFlagOnOff}},
        {"RunDeadEventKouka", 0x00260d68, playDeathEvent, {kDeadEvent}},
        {"RunHojoKouka", 0x00260e30, playBuff, {kBuff}},
        {"RunFlareChargeKouka", 0x00260e58, playFlareCharge, {kFlareCharge}},
        {"RunPadShockKouka", 0x00260e98, playPadShock, {kPadShock}},
        {"RunSkillColorKouka", 0x00260eb8, playSkillColor, {kSkillColorOff, kSkillColor, kSe}},
        {"RunStockPanelFadeOutKouka", 0x00260f08, playStockPanelFadeOut, {kPanelStockFadeOut}},
        {"RunStockPanelEndKouka", 0x00260f20, playStockPanelEnd, {kPanelStockEnd}},
    };
    // A summon: side 0 or 1 (the only ones used), the stock index (an
    // enemy's of ten), the slot; every slot with a unit, as its motion looks
    // the unit up by its slot.
    const auto summonPacket = [](Gen& g, EffectPacket& packet) {
        const int16_t side = static_cast<int16_t>(g.range(0, 1));
        packet.data1.setHalves(side, static_cast<int16_t>(side == 1 ? g.range(0, 9) : g.range(0, 11)));
        packet.data2.setInt(g.range(0, 13));
        for (uint32_t f = 0; f < 16; ++f)
            if (at<uint32_t>(FW_FORM_UNITS + 4u * f) == 0)
                at<uint32_t>(FW_FORM_UNITS + 4u * f) = FW_ENEMIES;
    };
    auto pickPacket = [=](Gen& g, const std::vector<int32_t>& types) {
        const int32_t type = types[g.below(static_cast<uint32_t>(types.size()))];
        return playPacket(g, {type});
    };
    for (const Player& player : players) {
        const Player* pl = &player;
        add(pl->name, [=](Gen& g) {
            const uint32_t p = pickPacket(g, pl->types);
            EffectPacket& packet = at<EffectPacket>(p);
            if (pl->rewrite == playMotion || pl->rewrite == playDamageMotion || pl->rewrite == playAilmentMotionCure) {
                // (A unit's motions need its unit: the slot gets one.)
                uint32_t& unit = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(packet.form->formindex));
                if (unit == 0)
                    unit = FW_ENEMIES;
            }
            if (pl->original == 0x0025fb58)   // a hit effect's kind
                packet.data1.setInt(g.range(-1, 11));
            if (pl->original == 0x00260a58)   // the stat bits to change
                packet.data2.raw = 1u << g.range(0, 7);
            if (pl->original == 0x0025f950 && g.chance(30))
                at<MainProcessData>(FW_MAIN).encno = 0x10f;
            if (pl->original == 0x00260528) {   // the gauge and icons, on either side's turn
                MainProcessData& main = at<MainProcessData>(FW_MAIN);
                main.press3 = Fl(static_cast<uint32_t>(floatBits(static_cast<float>(g.range(-2, 6)) / 4.0f)));
                main.stat ^= (g.chance(50) ? 8u : 0u) | (g.chance(10) ? 0x10000u : 0u);
                main.d31_press_total = static_cast<uint32_t>(g.range(0, 20));
                packet.data1.raw = g.chance(50) ? static_cast<uint32_t>(floatBits(static_cast<float>(g.range(-4, 4)) / 4.0f))
                                                : static_cast<uint32_t>(static_cast<uint16_t>(g.range(-3, 3))) | static_cast<uint32_t>(static_cast<uint16_t>(g.range(-3, 3))) << 16;
            }
            if (pl->original == 0x00260d80)   // black or white
                packet.data2.raw = static_cast<uint32_t>(g.range(0, 2));
            if (pl->original == 0x0025f100) {   // a cut already started, or the effect to start one of
                packet.cuteff = g.chance(50) ? 0 : 0x00700000u + g.below(0x1000);
                packet.data1.raw = FW_BTL_EFFECT;
                packet.data2.setHalves(static_cast<int16_t>(g.range(0, 2)), static_cast<int16_t>(g.range(-1, 2)));
            }
            if (pl->original == 0x0025f620) {   // how far, and the ailment (or a weak hit)
                packet.data1.raw = someFloat(g);
                packet.data2.setInt(g.chance(80) ? g.pick<int32_t>({-1, 0, 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400})
                                                 : g.range(-3, 0x800));
            }
            if (pl->original == 0x0025f9a8) {   // the summon; whose turn
                summonPacket(g, packet);
                at<MainProcessData>(FW_MAIN).stat ^= g.chance(50) ? 8u : 0u;
            }
            if (pl->original == 0x0025f4f0) {   // a motion (0x17 loops); a skill motion's ending
                if (packet.type == kMotion)
                    packet.data1.setInt(g.chance(30) ? 0x17 : g.range(0, 30));
                else
                    packet.data1.setHalves(static_cast<int16_t>(g.range(0, 30)), static_cast<int16_t>(g.range(-1, 4)));
            }
            if (pl->original == 0x002606d8) {   // sounds, and the event boss's music
                MainProcessData& main = at<MainProcessData>(FW_MAIN);
                packet.data1.setInt(g.chance(50) ? g.range(0x10007, 0x1000a) : g.range(0x10000, 0x10020));
                main.d31_repel107 = g.chance(40) ? 1u : 0u;
                main.d31_repel113 = g.chance(40) ? 1u : 0u;
            }
            const uint32_t original = pl->original;
            auto rewrite = pl->rewrite;
            return Pair{[=] { return origVmVoid(original, {kQueue, p}); },
                        [=] { rewrite(queue(), at<EffectPacket>(p)); return uint64_t{0}; }};
        });
    }
    // The help line's players: a status message or a skill's name.
    add("RunHelpKouka", [=](Gen& g) {
        at<MainProcessData>(FW_MAIN).statusMessageTable = iface::helpWorld(g, {0x10, 0x16, 0x4e}).id;
        const uint32_t p = playPacket(g, {kStatusMessage, kStatusMessage, kSe});
        at<EffectPacket>(p).data1.setHalves(static_cast<int16_t>(g.pick<int32_t>({0x10, 0x16, 0x4e})), static_cast<int16_t>(g.range(-1, 1)));
        at<EffectPacket>(p).data2.setInt(g.range(1, 0x17f));
        return Pair{[=] { return origVmVoid(0x002609c0, {kQueue, p}); },
                    [=] { playStatusMessage(queue(), at<EffectPacket>(p)); return uint64_t{0}; }};
    });
    add("RunSkillNameKouka", [=](Gen& g) {
        iface::helpWorld(g);
        const uint32_t p = playPacket(g, {kSkillName});
        at<EffectPacket>(p).data1.setInt(g.range(1, 0x17f));
        return Pair{[=] { return origVmVoid(0x00260e18, {kQueue, p}); },
                    [=] { playSkillName(queue(), at<EffectPacket>(p)); return uint64_t{0}; }};
    });
    // A passive that fired: the action's first cuts end 12 frames on.
    add("RunHatudoEffectEndKouka", [=](Gen& g) {
        const uint32_t p = playPacket(g, {kPassiveEffectEnd});
        for (int n = g.range(1, 5); n > 0; --n) {
            const uint32_t q = playPacket(g, {kSkillEffect1, kSkillEffect1, kSkillEffect, kSe});
            EffectPacket& packet = at<EffectPacket>(q);
            packet.uniqueid = g.chance(70) ? at<EffectPacket>(p).uniqueid : uid(g);
            packet.framelength = static_cast<int16_t>(g.range(0, 30));
            const uint32_t cut = ps2PoolAllocate(0x20);
            at<uint32_t>(cut + 8) = static_cast<uint32_t>(g.range(0, 60));
            at<uint16_t>(cut + 0x14) = static_cast<uint16_t>(g.range(0, 2));
            packet.cuteff = cut;
        }
        return Pair{[=] { return origVmVoid(0x0025f068, {kQueue, p}); },
                    [=] { playPassiveEffectEnd(queue(), at<EffectPacket>(p)); return uint64_t{0}; }};
    });
    // Packets the rewritten players play (the process runs them all).
    static const std::vector<int32_t> kPlayable = {
        kTargetMove, kHomeMove, kReturn, kDodge, kSkillColorOff, kSkillColor, kHitEff, kHpMp, kAilment, kAilmentEff,
        kAilmentCureEff, kHitStop, kMotionStop, kMotionStopClear, kAnalyze, kFormOnOff, kOngyokiClone, kOngyokiOut,
        kFormFlagOnOff, kDeadEvent, kBuff, kFlareCharge, kPadShock, kPanelStockFadeOut, kPanelStockEnd, kPassiveEffectEnd,
        kUnitCol, kUnitHomeCol, kUnitA, kUnitHomeA, kPress, kNewPress, kAilmentMotionCure, kFadeOut, kFadeIn,
        kSummon, kMotion, kSkillMotion, kSe, kSe2, kSe3, kDamageMotion, kAilmentDamageMotion, kAilmentMotion, kLightDamageMotion,
        kSkillEffect, kSkillEffect2, kSkillEffect1, kSkillEffect3};
    add("nbKoukaProcess1", [=](Gen& g) {
        std::memset(&queue(), 0, sizeof(EffectQueue));
        queue().data.address = FW_MAIN;
        for (int n = g.range(0, 8); n > 0; --n) {
            EffectPacket& packet = at<EffectPacket>(pickPacket(g, kPlayable));
            if (packet.type == kSummon)
                summonPacket(g, packet);
        }
        return Pair{[=] { return origVm(0x00260f38, {1}); }, [=] { return norm(runEffectQueue(1)); }};
    });
    add("nbDelUnEventKoukaPacket", [=](Gen& g) {
        for (int n = g.range(0, 6); n > 0; --n)
            pickPacket(g, {kReturn, kSkillColorOff, kSe, kSe2, kSe3, kDeadPcm, kFadeOut, kFadeIn, kHpMp, kFormOnOff, kNumberEff});
        at<MainProcessData>(FW_MAIN).EffectQueueProcessID = g.chance(85) ? 1u : 0u;
        return Pair{[=] { return origVmVoid(0x0025edc0, {}); }, [=] { deleteNonEventPackets(); return uint64_t{0}; }};
    });
    add("nbKoukaShutdown", [=](Gen& g) {
        for (int n = g.range(0, 6); n > 0; --n)
            pickPacket(g, {kSe, kHpMp, kFormOnOff, kNumberEff, kMotion});
        return Pair{[=] { return origVmVoid(0x002613f8, {1}); }, [=] { shutdownEffectQueue(1); return uint64_t{0}; }};
    });
    add("InitKoukaProcessData", [](Gen&) {
        return Pair{[] { return origVm(0x00261450, {FW_MAIN}); },
                    [] { return norm(static_cast<int32_t>(newEffectQueue(at<MainProcessData>(FW_MAIN)))); }};
    });
    add("nbInitKoukaProcess", [](Gen&) {
        return Pair{[] { return origVmVoid(0x00261490, {FW_MAIN}); }, [] { startEffectQueue(at<MainProcessData>(FW_MAIN)); return uint64_t{0}; }};
    });
    add("dds3Stop", [](Gen& g) {
        const int32_t frames = g.range(-2, 30);
        return Pair{[=] { return origVmVoid(0x00100448, {I(frames)}); }, [=] { nocturne::dds3::stop(frames); return uint64_t{0}; }};
    });
    add("dds3SlowOn", [](Gen& g) {
        const int32_t period = g.range(1, 4), frames = g.range(0, 40);
        at<uint32_t>(difftest::version::dataOrDie(0x0054e804)) = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVmVoid(0x00100460, {I(period), I(frames)}); },
                    [=] { nocturne::dds3::slowOn(period, frames); return uint64_t{0}; }};
    });
}

} // namespace difftest

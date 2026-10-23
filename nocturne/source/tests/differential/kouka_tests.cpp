// The battle's presentation queue (nbKoukaProcess, nbMakePacket): the
// rewrite against the original instructions, run by the EE interpreter, in a
// random battle with some packets already queued.
#include <algorithm>
#include <cstring>

#include "harness.hpp"
#include "interface_world.hpp"
#include "nocturne/battle/action.hpp"
#include "nocturne/battle/ai_script.hpp"
#include "nocturne/battle/buffs.hpp"
#include "nocturne/battle/camera.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/facility/compendium.hpp"

extern "C" {
uint32_t ps2PoolAllocate(int32_t);
uint64_t dds3StartProcess(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
}

// Action states not rewritten yet are called by address; here they run as
// original code in the interpreter, as on the original side.
extern "C" void nocturneInvokeBattleActionEntry(uint32_t entry, uint64_t context)
{
    difftest::iface::origVmVoid(entry, {context});
}
extern "C" uint64_t nocturneInvokeBattleActionUpdate(uint32_t target, uint64_t context)
{
    return difftest::iface::origVm(target, {context});
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

KoukaProcessData& queue() { return at<KoukaProcessData>(kQueue); }
uint32_t formAddress(int f) { return FW_FORMS + 0xf0u * static_cast<uint32_t>(f); }

// A random battle; the queue holds a few packets of earlier actions.
void koukaWorld(Gen& g)
{
    std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
    battleWorld(g);
    MainProcessData& main = at<MainProcessData>(FW_MAIN);
    main.KoukaProcessID = 1;
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
    KoukaProcessData& k = queue();
    std::memset(&k, 0, sizeof k);
    k.data.address = FW_MAIN;
    const int existing = g.range(0, 6);
    for (int i = 0; i < existing; ++i) {
        KoukaPacket& p = nbAddKoukaPacket(k, g.range(0, 60), g.range(0, 30), g.range(0, 3));
        static const int8_t types[] = {kSe, kSe2, kSe3, kNumEff, kMojiEff, kMotion, kUnitCol, kDmgMot};
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
            process = static_cast<uint32_t>(dds3StartProcess(0x00544350, 1, 0, 0, 0, 0, data));
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
    a.work->id = static_cast<uint16_t>(g.range(0, 383));
    a.adata = g.range(0, 140);
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
    main.MainProcessID = static_cast<uint32_t>(dds3StartProcess(0x00544350, g.range(1, 9), 0, 0, 0, 0, FW_MAIN));
    main.negoresult = g.chance(50) ? 0 : g.range(-2, 3);
    main.AiScriptProcessID = 0;
    if (g.chance(50))
        main.AiScriptProcessID = static_cast<uint32_t>(dds3StartProcess(0x00544350, 2, 0, 0, 0, 0, FW_ACTION));
    else if (g.chance(30))
        main.AiScriptProcessID = 0x00777000;   // ended
}

using Body = std::function<Pair(Gen&)>;

} // namespace

void addKoukaTests(std::vector<TestCase>& t)
{
    auto add = [&](const char* name, Body body) {
        t.push_back({name, [body](Gen& g) {
                         koukaWorld(g);
                         return body(g);
                     }});
    };

    // ---- the queue ----
    add("nbGetKoukaProcessData", [](Gen&) {
        return Pair{[] { return origVm(0x0025e8e0, {}); }, [] { return R(&nbGetKoukaProcessData()); }};
    });
    add("nbGetUniqueIdKoukaPacketCnt", [](Gen& g) {
        const int32_t id = uid(g);
        return Pair{[=] { return origVm(0x0025e928, {I(id)}); }, [=] { return norm(nbGetUniqueIdKoukaPacketCnt(id)); }};
    });
    add("nbGetKoukaPacketTypeCnt", [](Gen& g) {
        const int8_t type = static_cast<int8_t>(g.pick<int32_t>({kSe, kNumEff, kMotion, 0x7f, -1}));
        return Pair{[=] { return origVm(0x0025e978, {I(type)}); }, [=] { return norm(nbGetKoukaPacketTypeCnt(type)); }};
    });
    add("UnlinkKoukaPacket", [](Gen& g) {
        if (!queue().first)
            nbAddKoukaPacket(queue(), 1, 1, 1);
        KoukaPacket* p = queue().first.get();
        for (int n = g.range(0, 5); n > 0 && p->next; --n)
            p = p->next.get();
        const uint32_t packet = iface::addr(p);
        return Pair{[=] { return origVmVoid(0x0025ea00, {kQueue, packet}); },
                    [=] { UnlinkKoukaPacket(queue(), at<KoukaPacket>(packet)); return uint64_t{0}; }};
    });
    add("nbAddKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x0025ea48, {kQueue, I(s), I(l), I(id)}); }, [=] { return R(&nbAddKoukaPacket(queue(), s, l, id)); }};
    });
    add("nbOnOffKoukaPacketFlag", [](Gen& g) {
        const int32_t type = g.pick<int32_t>({kSe, kNumEff, kMotion, kUnitCol});
        const uint32_t flag = g.below(256);
        const int32_t sw = g.range(0, 1);
        if (g.chance(10))
            at<MainProcessData>(FW_MAIN).KoukaProcessID = 0;
        return Pair{[=] { return origVmVoid(0x0025ee78, {I(type), flag, I(sw)}); },
                    [=] { nbOnOffKoukaPacketFlag(type, flag, sw); return uint64_t{0}; }};
    });
    add("nbCheckSePacket", [](Gen& g) {
        const int32_t start = g.range(0, 70), se = g.pick<int32_t>({0x10010, 0x1000a, 5, 7}), frames = g.range(0, 10);
        return Pair{[=] { return origVm(0x0025ef10, {I(start), I(se), I(frames)}); }, [=] { return norm(nbCheckSePacket(start, se, frames)); }};
    });

    // ---- builders: (startframe, uniqueid, ...) ----
    using P = KoukaPacket&;
    auto plain = [&](const char* name, uint32_t entry, P (*rewrite)(int32_t, int32_t)) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g);
            return Pair{[=] { return origVm(entry, {I(s), I(id)}); }, [=] { return R(&rewrite(s, id)); }};
        });
    };
    plain("nbAddHatudoEffectEndPacket", 0x00261758, nbAddHatudoEffectEndPacket);
    plain("nbAddSkillColorOffPacket", 0x00262430, nbAddSkillColorOffPacket);
    plain("nbAddHitStopPacket", 0x00262e28, nbAddHitStopPacket);
    plain("nbAddPanelStockFadeOutPacket", 0x00263628, nbAddPanelStockFadeOutPacket);
    plain("nbAddPanelStockEndPacket", 0x00263678, nbAddPanelStockEndPacket);

    auto onForm = [&](const char* name, uint32_t entry, P (*rewrite)(int32_t, int32_t, Formation*)) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g);
            const uint32_t f = someForm(g);
            return Pair{[=] { return origVm(entry, {I(s), I(id), f}); }, [=] { return R(&rewrite(s, id, F(f))); }};
        });
    };
    onForm("nbAddMotionStopPacket", 0x00261f30, nbAddMotionStopPacket);
    onForm("nbAddMotionStopClearPacket", 0x00261f90, nbAddMotionStopClearPacket);
    onForm("nbAddBadEffKaifukuPacket", 0x00262610, nbAddBadEffKaifukuPacket);
    onForm("nbAddBadMotKaifukuPacket", 0x00262bb8, nbAddBadMotKaifukuPacket);
    onForm("nbAddAnalyzePacket", 0x00262e78, nbAddAnalyzePacket);
    onForm("nbAddFlyKoukaPacket", 0x002630a8, nbAddFlyKoukaPacket);

    // (startframe, uniqueid, form, int)
    auto onFormInt = [&](const char* name, uint32_t entry, P (*rewrite)(int32_t, int32_t, Formation*, int32_t)) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g), n = g.chance(30) ? static_cast<int32_t>(g.rng()) : g.range(-2, 20);
            const uint32_t f = someForm(g);
            return Pair{[=] { return origVm(entry, {I(s), I(id), f, I(n)}); }, [=] { return R(&rewrite(s, id, F(f), n)); }};
        });
    };
    onFormInt("nbAddUnitHomeColKoukaPacket", 0x00261d20, nbAddUnitHomeColKoukaPacket);
    onFormInt("nbAddUnitHomeAKoukaPacket", 0x00261e10, nbAddUnitHomeAKoukaPacket);
    onFormInt("nbAddMotionKoukaPacket", 0x00261ff0, nbAddMotionKoukaPacket);
    onFormInt("nbAddFormOnOffPacket", 0x00262fb8, nbAddFormOnOffPacket);
    onFormInt("nbAddDeadEventKoukaPacket", 0x00263350, nbAddDeadEventKoukaPacket);
    add("nbAddBadMotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), bad = 1u << g.range(0, 12);
        return Pair{[=] { return origVm(0x00262260, {I(s), I(id), f, bad}); }, [=] { return R(&nbAddBadMotKoukaPacket(s, id, F(f), bad)); }};
    });
    add("nbAddBadEffKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), bad = g.chance(80) ? 1u << g.range(0, 12) : g.below(0x1000);
        return Pair{[=] { return origVm(0x00262670, {I(s), I(id), f, bad}); }, [=] { return R(&nbAddBadEffKoukaPacket(s, id, F(f), bad)); }};
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
    onForm2("nbAddUnitColKoukaPacket", 0x00261ca0, nbAddUnitColKoukaPacket);
    onForm2("nbAddUnitAKoukaPacket", 0x00261d90, nbAddUnitAKoukaPacket);
    onForm2("nbAddHpMpKoukaPacket", 0x002629e8, [](int32_t s, int32_t id, Formation* f, uint32_t n, int32_t type) -> P {
        return nbAddHpMpKoukaPacket(s, id, f, static_cast<int32_t>(n), type);
    });
    onForm2("nbAddBadStatKoukaPacket", 0x00262b38, nbAddBadStatKoukaPacket);
    onForm2("nbAddHojoKoukaPacket", 0x002634c8, [](int32_t s, int32_t id, Formation* f, uint32_t type, int32_t point) -> P {
        return nbAddHojoKoukaPacket(s, id, f, type, point);
    });
    add("nbAddFormFlagOnOffPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), sw = g.range(0, 1);
        const uint32_t f = someForm(g), flag = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x00263028, {I(s), I(id), f, I(sw), flag}); },
                    [=] { return R(&nbAddFormFlagOnOffPacket(s, id, F(f), sw, flag)); }};
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
    ints("nbAddSkillNamePacket", 0x00262f58, [](int32_t s, int32_t id, int32_t a, int32_t, int32_t) -> P { return nbAddSkillNamePacket(s, id, a); }, 1);
    ints("nbAddFlareChargePacket", 0x00263548, [](int32_t s, int32_t id, int32_t a, int32_t, int32_t) -> P { return nbAddFlareChargePacket(s, id, a); }, 1);
    ints("nbAddFadeOutKoukaPacket", 0x002633e8, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P { return nbAddFadeOutKoukaPacket(s, id, a, b); }, 2);
    ints("nbAddFadeInKoukaPacket", 0x00263458, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P { return nbAddFadeInKoukaPacket(s, id, a, b); }, 2);
    ints("nbAddSkillColorPacket", 0x002623c0, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P { return nbAddSkillColorPacket(s, id, a, b); }, 2);
    ints("nbAddHomeRotKoukaPacket", 0x00261c30, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P { return nbAddHomeRotKoukaPacket(s, id, a, b); }, 2);
    ints("nbAddNewPressPacket", 0x00262ac8, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t) -> P {
        return nbAddNewPressPacket(s, id, static_cast<int16_t>(a), static_cast<int16_t>(b));
    }, 2);
    ints("nbAddSummonKoukaPacket", 0x00262340, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t c) -> P {
        return nbAddSummonKoukaPacket(s, id, static_cast<int16_t>(a), static_cast<int16_t>(b), static_cast<int16_t>(c));
    }, 3);
    ints("nbAddPadShockPacket", 0x002635a8, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t c) -> P {
        return nbAddPadShockPacket(s, id, static_cast<int16_t>(a), static_cast<int16_t>(b), static_cast<int16_t>(c));
    }, 3);
    ints("nbAddJyokyoHelpPacket", 0x00262ed8, [](int32_t s, int32_t id, int32_t a, int32_t b, int32_t c) -> P {
        return nbAddJyokyoHelpPacket(s, id, static_cast<int16_t>(a), static_cast<int16_t>(b), c);
    }, 3);

    // (startframe, framelength, uniqueid, ...)
    add("nbAddSkillEffectKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g);
        const uint32_t c = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x00261500, {I(s), I(l), I(id), c}); }, [=] { return R(&nbAddSkillEffectKoukaPacket(s, l, id, c)); }};
    });
    add("nbAddSkillEffectKoukaPacket1", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g);
        const uint32_t c = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x002616e8, {I(s), I(l), I(id), c}); }, [=] { return R(&nbAddSkillEffectKoukaPacket1(s, l, id, c)); }};
    });
    add("nbAddSkillEffectKoukaPacket2", [](Gen& g) {
        const int32_t s = frame(g), l = g.chance(30) ? 0 : frame(g), id = uid(g);
        const uint32_t h = static_cast<uint32_t>(g.rng()), f = someForm(g);
        const int16_t cut = static_cast<int16_t>(g.range(-2, 40)), j = static_cast<int16_t>(g.range(-2, 40));
        return Pair{[=] { return origVm(0x00261638, {I(s), I(l), I(id), h, I(cut), f, I(j)}); },
                    [=] { return R(&nbAddSkillEffectKoukaPacket2(s, l, id, h, cut, F(f), j)); }};
    });
    add("nbAddNumEffKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g), n = g.range(-5, 9999), n2 = g.range(-5, 999), type = g.range(0, 5);
        const uint32_t f = g.chance(50) && queue().first ? queue().first->form.address : someForm(g);
        return Pair{[=] { return origVmVoid(0x002627c0, {I(s), I(l), I(id), f, I(n), I(n2), I(type)}); },
                    [=] { nbAddNumEffKoukaPacket(s, l, id, F(f), n, n2, type); return uint64_t{0}; }};
    });
    add("nbAddMojiEffKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), l = frame(g), id = uid(g), type = g.range(0, 6);
        const uint32_t f = g.chance(50) && queue().first ? queue().first->form.address : someForm(g);
        return Pair{[=] { return origVmVoid(0x002628d0, {I(s), I(l), I(id), f, I(type)}); },
                    [=] { nbAddMojiEffKoukaPacket(s, l, id, F(f), type); return uint64_t{0}; }};
    });

    // floats in f12
    add("nbAddTargetMoveKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), party = g.range(-1, 13);
        const uint32_t v = someVector(g), speed = someFloat(g);
        return Pair{[=] { return origVm(0x00261aa0, {I(s), I(id), I(party), v}, {speed}); },
                    [=] { return R(&nbAddTargetMoveKoukaPacket(s, id, party, at<Vec4>(v), Fl(speed))); }};
    });
    add("nbAddHomeMoveKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), party = g.range(-1, 13);
        const uint32_t speed = someFloat(g);
        return Pair{[=] { return origVm(0x00261b30, {I(s), I(id), I(party)}, {speed}); },
                    [=] { return R(&nbAddHomeMoveKoukaPacket(s, id, party, Fl(speed))); }};
    });
    add("nbAddRotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), party = g.range(-1, 13), speed = g.range(0, 30);
        const uint32_t v = someVector(g);
        return Pair{[=] { return origVm(0x00261ba0, {I(s), I(id), I(party), v, I(speed)}); },
                    [=] { return R(&nbAddRotKoukaPacket(s, id, party, at<Vec4>(v), speed)); }};
    });
    add("nbAddSkillMotionKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const int16_t motion = static_cast<int16_t>(g.range(0, 40)), end = static_cast<int16_t>(g.range(0, 3));
        const uint32_t f = someForm(g), ritu = someFloat(g);
        return Pair{[=] { return origVm(0x00262060, {I(s), I(id), f, I(motion), I(end)}, {ritu}); },
                    [=] { return R(&nbAddSkillMotionKoukaPacket(s, id, F(f), motion, end, Fl(ritu))); }};
    });
    add("nbAddDmgMotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), week = g.range(-1, 1);
        const uint32_t f = someForm(g), range = someFloat(g);
        return Pair{[=] { return origVm(0x002620f0, {I(s), I(id), f, I(week)}, {range}); },
                    [=] { return R(&nbAddDmgMotKoukaPacket(s, id, F(f), Fl(range), week)); }};
    });
    add("nbAddEasyDmgMotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), range = someFloat(g);
        return Pair{[=] { return origVm(0x00262170, {I(s), I(id), f}, {range}); },
                    [=] { return R(&nbAddEasyDmgMotKoukaPacket(s, id, F(f), Fl(range))); }};
    });
    add("nbAddBadDmgMotKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), range = someFloat(g), bad = 1u << g.range(0, 12);
        return Pair{[=] { return origVm(0x002621e0, {I(s), I(id), f, bad}, {range}); },
                    [=] { return R(&nbAddBadDmgMotKoukaPacket(s, id, F(f), Fl(range), bad)); }};
    });
    add("nbAddPressPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t press = someFloat(g);
        return Pair{[=] { return origVm(0x00262a68, {I(s), I(id)}, {press}); }, [=] { return R(&nbAddPressPacket(s, id, Fl(press))); }};
    });

    // sounds
    auto sound = [&](const char* name, uint32_t entry, KoukaPacket* (*rewrite)(int32_t, int32_t, uint32_t)) {
        add(name, [=](Gen& g) {
            const int32_t s = frame(g), id = uid(g);
            const uint32_t se = g.pick<uint32_t>({0x10010, 0x1000a, 5, 7});
            return Pair{[=] { return origVm(entry, {I(s), I(id), se}); }, [=] { return R(rewrite(s, id, se)); }};
        });
    };
    sound("nbAddSePacket", 0x00262cc0, nbAddSePacket);
    sound("nbAddSePacket2", 0x00262d38, nbAddSePacket2);
    sound("nbAddSePacket3", 0x00262db0, nbAddSePacket3);

    // units and parties
    add("nbAddSakeKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = formAddress(g.range(0, 13));
        if (g.chance(20))
            at<Formation>(f).r = nocturne::ee::Float::fromInt(g.range(100, 200));
        return Pair{[=] { return origVm(0x00261e80, {I(s), I(id), f}); }, [=] { return R(&nbAddSakeKoukaPacket(s, id, at<Formation>(f))); }};
    });
    add("nbAddDeadPcmPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = formAddress(g.range(0, 13));
        return Pair{[=] { return origVm(0x00262c18, {I(s), I(id), f}); }, [=] { return R(nbAddDeadPcmPacket(s, id, at<Formation>(f))); }};
    });
    add("nbAddReturnKoukaPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), dead = g.range(0, 1);
        const uint32_t party = FW_PARTY + 128u * g.below(14);
        return Pair{[=] { return origVm(0x002622d0, {I(s), I(id), party, I(dead)}); },
                    [=] { return R(&nbAddReturnKoukaPacket(s, id, &at<Party>(party), dead)); }};
    });

    // ---- whole events ----
    add("nbMakeSummonPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const int16_t side = static_cast<int16_t>(g.range(0, 1)), stock = static_cast<int16_t>(g.range(0, 11)),
                      f = static_cast<int16_t>(g.range(0, 13));
        return Pair{[=] { return origVm(0x002636c8, {I(s), I(id), I(side), I(stock), I(f)}); },
                    [=] { return norm(nbMakeSummonPacket(s, id, side, stock, f)); }};
    });
    add("nbMakeReturnPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t party = FW_PARTY + 128u * g.below(14);
        return Pair{[=] { return origVm(0x00263778, {I(s), I(id), party}); }, [=] { return norm(nbMakeReturnPacket(s, id, at<Party>(party))); }};
    });
    add("nbMakeUnitFadeInPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), d = g.range(0, 20), a = g.range(0, 20), c = g.range(0, 20);
        const uint32_t f = someForm(g), col = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x00263810, {I(s), I(id), f, col, I(d), I(a), I(c)}); },
                    [=] { return norm(nbMakeUnitFadeInPacket(s, id, F(f), col, d, a, c)); }};
    });
    add("nbMakeUnitFadeOutPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), d = g.range(0, 20), c = g.range(0, 20), a = g.range(0, 20);
        const uint32_t f = someForm(g), col = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVm(0x002638a0, {I(s), I(id), f, col, I(d), I(c), I(a)}); },
                    [=] { return norm(nbMakeUnitFadeOutPacket(s, id, F(f), col, d, c, a)); }};
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
                    [=] { return norm(nbMakeDeadPacket(s, id, at<Formation>(form), chk)); }};
    });
    struct DeadCheck {
        const char* name;
        uint32_t entry;
        int32_t (*rewrite)(const Formation&);
    };
    static const DeadCheck deadChecks[] = {
        {"nbCheckEventDead", 0x00259ab0, [](const Formation& f) { return nbCheckEventDead(f) ? 1 : 0; }},
        {"nbCheckDeadScript", 0x00259b10, nbCheckDeadScript},
        {"nbCheckDeadEvent", 0x00259b70, nbCheckDeadEvent},
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
        return Pair{[] { return origVmVoid(0x002514f0, {FW_ACTION}); }, [=] { ClearTimeList(act()); return uint64_t{0}; }};
    });
    action("SetHpForTimeList", [=](Gen&) {
        auto* forms = &at<Formation>(FW_FORMS);
        for (int f = 0; f < 14; ++f)   // present party slots have units, as in the game
            if (!at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(forms[f].partyindex)))
                forms[f].stat &= ~FormationStat::CheckParty;
        // (slots 14 and 15 are read past the array; keep them empty)
        std::memset(&at<Formation>(formAddress(14)), 0, 2 * sizeof(Formation));
        return Pair{[] { return origVmVoid(0x00251538, {FW_ACTION}); }, [=] { SetHpForTimeList(act()); return uint64_t{0}; }};
    });
    struct Getter {
        const char* name;
        uint32_t entry;
        int32_t (*rewrite)(ActionProcessData&, int32_t);
    };
    static const Getter getters[] = {
        {"GetTimeListHp", 0x002515d8, GetTimeListHp},
        {"GetUnlockTime", 0x00251750, GetUnlockTime},
        {"GetEndTime", 0x00251760, GetEndTime},
        {"CheckTimeListDead", 0x002515e8, [](ActionProcessData& a, int32_t f) { return CheckTimeListDead(a, f) ? 1 : 0; }},
        {"CheckTimeListDeadEnemyParty", 0x00251628,
         [](ActionProcessData& a, int32_t f) { return CheckTimeListDeadEnemyParty(a, f) ? 1 : 0; }},
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
                    [=] { return norm(nbAddTimeListHp(act(), f, amount)); }};
    });
    action("AddTimeListHp", [=](Gen& g) {
        const int32_t f = g.range(0, 31), amount = g.range(-1200, 1200);
        return Pair{[=] { return origVmVoid(0x00251738, {FW_ACTION, I(f), I(amount)}); },
                    [=] { AddTimeListHp(act(), f, amount); return uint64_t{0}; }};
    });
    action("OverwriteTimeList", [=](Gen& g) {
        const int32_t f = g.range(0, 31), s = g.range(0, 90), lock = g.range(-2, 60), end = g.range(-2, 90);
        return Pair{[=] { return origVmVoid(0x00251770, {FW_ACTION, I(f), I(s), I(lock), I(end)}); },
                    [=] { OverwriteTimeList(act(), f, s, lock, end); return uint64_t{0}; }};
    });
    action("SetTimeList", [=](Gen& g) {
        const int32_t f = g.range(0, 31), s = g.range(0, 90), lock = g.range(-2, 60), end = g.range(-2, 90);
        return Pair{[=] { return origVmVoid(0x002517e0, {FW_ACTION, I(f), I(s), I(lock), I(end)}); },
                    [=] { SetTimeList(act(), f, s, lock, end); return uint64_t{0}; }};
    });
    action("GetAllEndTime", [=](Gen&) {
        return Pair{[] { return origVm(0x00251858, {FW_ACTION}); }, [=] { return norm(GetAllEndTime(act())); }};
    });
    action("GetAllUnlockTime", [=](Gen&) {
        return Pair{[] { return origVm(0x00251890, {FW_ACTION}); }, [=] { return norm(GetAllUnlockTime(act())); }};
    });
    action("nbGetActionSeq", [](Gen& g) {
        const uint32_t process = g.chance(10) ? 0 : at<MainProcessData>(FW_MAIN).ActionProcessID[g.below(4)];
        return Pair{[=] { return origVm(0x00257bf8, {process}); }, [=] { return norm(nbGetActionSeq(process)); }};
    });
    action("nbGetPrevActionSeq", [](Gen&) {
        return Pair{[] { return origVm(0x00257c20, {}); }, [] { return norm(nbGetPrevActionSeq()); }};
    });
    action("SetNextActionSeq", [=](Gen& g) {
        const int32_t next = g.range(-1, 23);
        return Pair{[=] { return origVmVoid(0x00257cc8, {FW_ACTION, I(next)}); }, [=] { SetNextActionSeq(act(), next); return uint64_t{0}; }};
    });
    struct State {
        const char* name;
        uint32_t entry;
        int32_t (*rewrite)(ActionProcessData&);
        bool result;
    };
    static const State states[] = {
        {"SetAction_NON", 0x00253488, [](ActionProcessData& a) { SetAction_NON(a); return 0; }, false},
        {"CheckAction_AI", 0x00253c20, CheckAction_AI, true},
        {"SetAction_INVISIBLE", 0x00257460, [](ActionProcessData& a) { SetAction_INVISIBLE(a); return 0; }, false},
        {"CheckAction_INVISIBLE", 0x00257468, CheckAction_INVISIBLE, true},
        {"SetAction_CHECK3", 0x00257a68, [](ActionProcessData& a) { SetAction_CHECK3(a); return 0; }, false},
        {"CheckAction_CHECK3", 0x00257a70, CheckAction_CHECK3, true},
        {"SetAction_ATO", 0x00257ab8, [](ActionProcessData& a) { SetAction_ATO(a); return 0; }, false},
        {"CheckAction_ATO", 0x00257ac0, CheckAction_ATO, true},
        {"CheckAction_END", 0x00257bf0, CheckAction_END, true},
    };
    auto script = [&](const char* name, std::function<Pair(Gen&)> body) {
        action(name, [=](Gen& g) {
            scriptActor(g);
            return body(g);
        });
    };
    script("nbInitAiScript", [=](Gen& g) {
        const int32_t procedure = g.range(0, 140);
        return Pair{[=] { return origVmVoid(0x00288d80, {FW_ACTION, I(procedure)}); },
                    [=] { ai::script::start(act(), procedure); return uint64_t{0}; }};
    });
    // (The camera is in the executable's data, which the harness doesn't
    // compare: return its state.)
    auto camera = [] { return std::ref(at<Camera>(0x00320e40)); };
    auto cameraState = [=] { return uint64_t{camera().get().state_change} | uint64_t{camera().get().state} << 32; };
    script("nbCameraSetState", [=](Gen& g) {
        const uint16_t state = static_cast<uint16_t>(g.chance(20) ? 25 : g.range(0, 29));
        camera().get().state = g.range(1, 9);
        return Pair{[=] { origVmVoid(0x001b1740, {state}); return cameraState(); },
                    [=] { nbCameraSetState(state); return cameraState(); }};
    });
    // An ailing actor: any ailment, sometimes cursed; a status line maybe
    // pending; any point of its wait.
    auto ailingWorld = [=](Gen& g) {
            ActionProcessData& a = act();
            UnitWork& unit = *a.work;
            unit.badstat = static_cast<uint16_t>(
                (g.chance(15) ? 0 : 1u << g.range(0, 11)) | (g.chance(30) ? nocturne::kBadStatCurse : 0));
            unit.nowcommand = static_cast<int16_t>(g.range(-1, 11));
            unit.flag = (unit.flag & ~0x24u) | g.pick<uint32_t>({0, 4, 0x20});
            a.seqtime = static_cast<uint16_t>(g.chance(30) ? 5 : g.chance(50) ? g.range(0, 50) : g.pick<int32_t>({0, 30, 31, 40, 41, 100}));
            MainProcessData& main = at<MainProcessData>(FW_MAIN);
            main.endtype = g.chance(50) ? 3 : g.range(0, 4);
            main.esccnt = static_cast<uint8_t>(g.chance(10) ? 0xff : g.range(0, 5));
            main.NegoProcessID = g.chance(50) ? 0 : 0x00777000;
            main.negoresult = g.range(0, 9);
            unit.maxhp = static_cast<uint16_t>(g.range(1, 999));
            if (g.chance(20))
                nocturne::dat::globalWork().units[0].badstat = static_cast<uint16_t>(g.chance(50) ? 0x800 : 0);
            a.jyokyomes = g.chance(40) ? 0 : g.range(-1, 0x50);
            a.jyo_varid = g.range(-1, 2);
            a.jyo_varind = g.range(0, 0x17f);
            at<MainProcessData>(FW_MAIN).jyokyomsgid = g.range(0, 5);
            if (g.chance(50))
                at<MainProcessData>(FW_MAIN).stat ^= 8;
            camera().get().state_change = 0xffff;
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
                    [=] { SetActionSeq(act(), seq); return cameraState(); }};
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
        at<uint32_t>(0x005519c8) = g.chance(20) ? 1u : 0u;   // a streamed voice playing
        MainProcessData& main = at<MainProcessData>(FW_MAIN);
        for (uint32_t& p : main.ActionProcessID)
            p = 0;
        const uint32_t process = static_cast<uint32_t>(dds3StartProcess(0x00544350, 3, 0, 0, 0, 0, FW_ACTION));
        main.NowActionProcess = g.range(0, 3);
        if (g.chance(70)) {   // the action before this one
            const uint32_t data = ps2PoolAllocate(static_cast<int32_t>(sizeof(ActionProcessData)));
            at<ActionProcessData>(data).seq = static_cast<int8_t>(g.range(-1, 22));
            main.ActionProcessID[main.NowActionProcess == 0 ? 3 : main.NowActionProcess - 1] =
                static_cast<uint32_t>(dds3StartProcess(0x00544350, 1, 0, 0, 0, 0, data));
        }
        return Pair{[=] { const uint64_t r = origVm(0x00257cd0, {process}); return r ^ cameraState() << 8; },
                    [=] { return norm(nbActionProcess1(process)) ^ cameraState() << 8; }};
    });
    ailing("CheckAction_BAD", 0x00253e00, CheckAction_BAD, true);
    ailing("SetAction_BADWAIT", 0x00254010, [](ActionProcessData& a) { SetAction_BADWAIT(a); return 0; }, false);
    ailing("CheckAction_BADWAIT", 0x00254058, CheckAction_BADWAIT, true);
    ailing("SetAction_WAIT", 0x002570b8, [](ActionProcessData& a) { SetAction_WAIT(a); return 0; }, false);
    ailing("CheckAction_WAIT", 0x00257210, CheckAction_WAIT, true);
    ailing("SetAction_ESCAPE", 0x00257230, [](ActionProcessData& a) { SetAction_ESCAPE(a); return 0; }, false);
    ailing("CheckAction_ESCAPE", 0x002572c0, CheckAction_ESCAPE, true);
    ailing("SetAction_RETURN", 0x002573a8, [](ActionProcessData& a) { SetAction_RETURN(a); return 0; }, false);
    ailing("CheckAction_RETURN", 0x00257440, CheckAction_RETURN, true);
    ailing("CheckAction_NEGO", 0x00256b88, CheckAction_NEGO, true);
    ailing("CheckAction_NEGORESULT", 0x00257098, CheckAction_NEGORESULT, true);
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
        a.form->unknown_a4 = static_cast<int16_t>(g.pick<int32_t>({0, 2, 2, 1}));
        for (int k = 0; k < 14; ++k)
            if (g.chance(10))
                at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(k)).flag |= 0x20;
        nocturne::dat::globalWork().maka = g.chance(20) ? 0 : g.range(0, 50000);
        SetHpForTimeList(a);
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
        return voidPair(0x0024f420, {FW_ACTION, I(start)}, [=] { UnitKyoseiDisp(act(), start); });
    });
    script("SetDeadPacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g);
        Formation& dying = at<Formation>(formAddress(f));   // a dying unit is there
        dying.stat |= FormationStat::Present | FormationStat::CheckParty;
        dying.formindex = static_cast<int16_t>(f);
        Party& party = at<Party>(FW_PARTY + 128u * static_cast<uint32_t>(dying.partyindex));
        party.flag = static_cast<int16_t>(party.flag | PartyFlag::Active);
        return voidPair(0x0024f478, {FW_ACTION, I(f)}, [=] { SetDeadPacket(act(), f); });
    });
    script("SetPress", [=](Gen& g) {
        results(g);
        const uint32_t press = pressBits(g);
        return voidPair(0x0024f548, {FW_ACTION}, [=] { SetPress(act(), nocturne::ee::Float::fromBits(press)); }, {press});
    });
    script("SetNewPress", [=](Gen& g) {
        results(g);
        const int32_t type = g.range(-1, 18);
        return voidPair(0x0024f5b0, {FW_ACTION, I(type)}, [=] { SetNewPress(act(), type); });
    });
    script("SetHitStopFrame", [=](Gen& g) {
        results(g);
        const int32_t frame = g.range(-10, 70);
        return voidPair(0x0024f5c8, {FW_ACTION, I(frame)}, [=] { SetHitStopFrame(act(), frame); });
    });
    script("SetEnemyEscapePacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        return voidPair(0x0024f5f0, {FW_ACTION, I(f), I(frame)}, [=] { SetEnemyEscapePacket(act(), f, frame); });
    });
    script("SetAuroraPacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        setBuffCounter(f, 19, g.pick<int32_t>({0, 0xf8, 0xf9, 0xfa, 0xfb, 5, 0xfc}));
        return voidPair(0x0024f658, {FW_ACTION, I(f), I(frame)}, [=] { SetAuroraPacket(act(), f, frame); });
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
        return voidPair(0x0024f728, {FW_ACTION, I(skill)}, [=] { SetAddPressPacket(act(), skill); });
    });
    script("SetAddFlareChargePacket", [=](Gen& g) {
        results(g);
        const int32_t start = g.range(0, 40);
        return voidPair(0x0024f7b8, {FW_ACTION, I(start)}, [=] { SetAddFlareChargePacket(act(), start); });
    });
    script("SetMakaPacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        return voidPair(0x0024f7e0, {FW_ACTION, I(f), I(frame)}, [=] { SetMakaPacket(act(), f, frame); });
    });
    script("SetTorafuPacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        return voidPair(0x0024f8a8, {FW_ACTION, I(f), I(frame)}, [=] { SetTorafuPacket(act(), f, frame); });
    });
    script("SetAnalyzePacket", [=](Gen& g) {
        results(g);
        const int32_t f = occupied(g), frame = g.range(0, 40);
        return voidPair(0x0024f938, {FW_ACTION, I(f), I(frame)}, [=] { SetAnalyzePacket(act(), f, frame); });
    });
    script("SetSakePacket", [=](Gen& g) {
        results(g);
        const int32_t skill = g.range(0, 0x11f), s = occupied(g), d = occupied(g), cnt = g.range(0, 3), frame = g.range(0, 40);
        return voidPair(0x0024fb38, {FW_ACTION, I(skill), I(s), I(d), I(cnt), I(frame)},
                        [=] { SetSakePacket(act(), skill, s, d, cnt, frame); });
    });
    script("SetMissPacket", [=](Gen& g) {
        results(g);
        const int32_t skill = g.range(0, 0x11f), s = occupied(g), d = occupied(g), cnt = g.range(0, 3), frame = g.range(0, 40);
        return voidPair(0x0024fc28, {FW_ACTION, I(skill), I(s), I(d), I(cnt), I(frame)},
                        [=] { SetMissPacket(act(), skill, s, d, cnt, frame); });
    });
    script("SetDamagePacket", [=](Gen& g) {
        results(g);
        UnitWork& unit = *act().get().work;
        if (g.chance(40))   // Endure (0x159) or Never Yield (0x168) among its skills
            unit.skill[g.below(8)] = static_cast<uint16_t>(g.chance(50) ? 0x159 : 0x168);
        act().get().party->flag = static_cast<int16_t>(act().get().party->flag & ~(PartyFlag::EndureFired | PartyFlag::EndureSpent));
        int32_t hp = g.chance(10) ? g.range(-5, 0) : g.range(1, 600);
        if (g.chance(25))   // exactly the HP left
            hp = GetTimeListHp(act(), act().get().form->formindex);
        return voidPair(0x002532a8, {FW_ACTION, I(hp)}, [=] { SetDamagePacket(act(), hp); });
    });
    // ---- Ongyo-Ki ----
    script("nbAddOngBunshinPacket", [=](Gen& g) {
        const uint32_t s = someForm(g), e = someForm(g);
        const int32_t start = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x00263110, {I(start), I(id), s, e}); },
                    [=] { return R(&nbAddOngBunshinPacket(start, id, F(s), F(e))); }};
    });
    script("nbAddOngBunshin2Packet", [=](Gen& g) {
        const uint32_t s = someForm(g), f1 = someForm(g), f2 = someForm(g), f3 = someForm(g);
        const int32_t start = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x002631a0, {I(start), I(id), s, f1, f2, f3}); },
                    [=] { return R(&nbAddOngBunshin2Packet(start, id, F(s), F(f1), F(f2), F(f3))); }};
    });
    script("nbAddOngOutPacket", [=](Gen& g) {
        const uint32_t f = someForm(g);
        const int32_t start = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x00263250, {I(start), I(id), f}); }, [=] { return R(&nbAddOngOutPacket(start, id, F(f))); }};
    });
    script("nbAddOngOut2Packet", [=](Gen& g) {
        const uint32_t f = someForm(g);
        const int32_t start = frame(g), id = uid(g);
        return Pair{[=] { return origVm(0x002632d0, {I(start), I(id), f}); }, [=] { return R(&nbAddOngOut2Packet(start, id, F(f))); }};
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
                        [=] { SetOngShadowPacket(act(), 0, 0, d, 0, frame); });
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
        return voidPair(0x0024fe40, {FW_ACTION, I(d), I(frame)}, [=] { SetOngShadowPacket2(act(), d, frame); });
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
                        u.id = static_cast<uint16_t>(g.chance(30) ? 0x123 : g.range(1, 383));
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
        main.press4_hansya = static_cast<int16_t>(g.chance(15) ? g.range(0xf0, 0xf6) : g.range(0, 3));
        main.stat &= ~(0x1u | 0x10u | 0x80u | 0x100u | 0x2000000u);
        for (uint32_t bit : {0x1u, 0x10u, 0x80u, 0x100u, 0x2000000u})
            if (g.chance(bit == 0x80u ? 50 : 15))
                main.stat |= bit;
        main.enemypcnt = static_cast<int16_t>(g.range(0, 4));
        main.turn = static_cast<uint8_t>(g.range(0, 5));
        main.CommSelProcessID = g.chance(50) ? 0 : 0x00777000;
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
    struct Talkers { std::vector<uint16_t> mukan, sensei, inoti, binjo; };
    static const Talkers talkers = [] {
        Talkers t;
        for (uint16_t id = 1; id < 384; ++id) {
            const auto& n = nocturne::dat::devilNegoFormat(id);
            if (n.mukantype) t.mukan.push_back(id);
            if (n.senseitype) t.sensei.push_back(id);
            if (n.inotitype) t.inoti.push_back(id);
            if (n.binjotype) t.binjo.push_back(id);
        }
        return t;
    }();
    auto pickFrom = [](Gen& g, const std::vector<uint16_t>& ids) {
        return ids.empty() ? static_cast<uint16_t>(g.range(1, 383)) : ids[g.below(static_cast<uint32_t>(ids.size()))];
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
    side("SetTargetPlayer", [=](Gen&) { return sideVoid(0x00251ef0, SetTargetPlayer); });
    side("SetTargetParty", [=](Gen& g) {
        const int32_t shift = g.range(0, 13);   // party slots needn't match formation slots
        for (int f = 0; f < 14; ++f)
            at<Formation>(formAddress(f)).partyindex = static_cast<int16_t>((f + shift) % 14);
        const int32_t pi = g.range(-1, 14);
        return Pair{[=] { return origVmVoid(0x00251fd8, {FW_ACTION, I(pi)}); }, [=] { SetTargetParty(act(), pi); return uint64_t{0}; }};
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
        return sideBool(0x00252060, CheckArrCounter);
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
                    [=] { return norm(CheckCounter(act(), from, to) ? 1 : 0); }};
    });
    auto talker = [=](Gen& g) {   // the actor: a unit that may talk
        ActionProcessData& a = act();
        a.party->flag = static_cast<int16_t>(g.chance(50) ? (a.party->flag | 2) : (a.party->flag & ~6));
        a.partyindex = g.range(0, 5);
        a.work->nowcommand = static_cast<int16_t>(g.range(-1, 6));
        a.work->badstat = static_cast<uint16_t>(g.chance(80) ? 0 : 0x80);
        if (g.chance(50))
            a.work->id = static_cast<uint16_t>(g.range(1, 383));
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
            a.work->id = static_cast<uint16_t>(g.range(1, 383));
            // No devil talks this way in the shipped data; patch the
            // actor's record so the dormant code runs.
            const_cast<nocturne::DevilNegoFormat&>(nocturne::dat::devilNegoFormat(a.work->id)).mukantype = 1;
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
        return sideBool(0x00252400, CheckMukanNego);
    });
    side("CheckSenseiNego", [=](Gen& g) {
        talker(g);
        if (g.chance(70)) {   // an ambush by a devil that may talk
            MainProcessData& main = at<MainProcessData>(FW_MAIN);
            act().get().work->id = pickFrom(g, talkers.sensei);
            act().get().work->badstat = 0;
            nocturne::dat::globalWork().units[0].badstat = 0;
            main.stat = (main.stat & ~(0x1u | 0x10u | 0x100u)) | 0x80u;
            main.press4_hansya = 0;
            main.enemypcnt = static_cast<int16_t>(g.chance(70) ? 1 : g.range(2, 4));
        }
        return sideBool(0x002525f0, CheckSenseiNego);
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
                enemy.id = pickFrom(g, talkers.inoti);
                enemy.badstat = 0;
                enemy.level = static_cast<uint16_t>(g.range(1, 40));
                a.timelist[f].hp = static_cast<uint16_t>(g.range(1, enemy.maxhp / 3 + 1));
            }
            nocturne::dat::globalWork().units[0].level = static_cast<uint16_t>(g.range(30, 99));
        }
        return sideBool(0x00252720, CheckInotiNego);
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
                    at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f))).id = pickFrom(g, talkers.binjo);
                    at<UnitWork>(at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f))).badstat = 0;
                }
        }
        return sideBool(0x002529d0, CheckBinjoNego);
    });
    side("CheckDeadScript", [=](Gen&) { return sideVoid(0x00252c28, CheckDeadScript); });
    side("CheckKoketaNego", [=](Gen& g) { talker(g); return sideBool(0x00252cd8, CheckKoketaNego); });
    side("KyouseiPress", [=](Gen&) { return sideVoid(0x00252ea8, KyouseiPress); });
    side("DokodemoPoa", [=](Gen&) { return sideVoid(0x00252ee8, DokodemoPoa); });
    side("SetNowActionStat", [=](Gen& g) {
        act().get().partyindex = g.range(0, 5);
        act().get().stat = 0;
        const int32_t comm = g.chance(50) ? 1 : g.range(-1, 7);
        const int32_t skill = g.chance(40) ? g.pick<int32_t>({0x50, 0xde, 0xe2, 0xe3, 0xdf, 0xff, 0xfc}) : g.range(0, 0x11f);
        return Pair{[=] { return origVmVoid(0x00252fb8, {FW_ACTION, I(comm), I(skill)}); },
                    [=] { SetNowActionStat(act(), comm, skill); return uint64_t{0}; }};
    });

    // ---- the stock and the enemies' units ----
    // A random stock (the Demi-fiend, devils in and out of the party, dead
    // or spent ones) and enemy units.
    auto stockWorld = [=](Gen& g) {
        nocturne::GlobalWork& global = nocturne::dat::globalWork();
        for (int i = 1; i < 16; ++i) {
            nocturne::UnitWork& unit = global.units[i];
            unit.flag = g.chance(60) ? (1u | (g.chance(40) ? 2u : 0u) | (g.chance(10) ? 0x10u : 0u)) : 0u;
            unit.id = static_cast<uint16_t>(g.range(1, 383));
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
        return Pair{[=] { return origVm(0x00259180, {s}); }, [=] { return norm(nbGetNakama(at<nocturne::UnitWork>(s))); }};
    });
    script("nbAppendEnemyDevilWork", [=](Gen& g) {
        stockWorld(g);
        const int32_t id = g.range(1, 383);
        return Pair{[=] { return origVm(0x002594b0, {FW_MAIN, I(id)}); },
                    [=] { return norm(nbAppendEnemyDevilWork(at<MainProcessData>(FW_MAIN), id)); }};
    });
    script("nbGetRandamStock", [=](Gen& g) {
        stockWorld(g);
        return Pair{[] { return origVm(0x002595a0, {}); }, [] { return norm(nbGetRandamStock()); }};
    });
    script("nbClearCommandMemeoyRenzoku", [=](Gen& g) {
        for (int f = 0; f < 4; ++f) {
            const uint32_t unit = at<uint32_t>(FW_FORM_UNITS + 4u * static_cast<uint32_t>(f));
            if (unit) {
                at<nocturne::UnitWork>(unit).prevtarea = static_cast<int16_t>(g.range(-1, 3));
                at<nocturne::UnitWork>(unit).prevtform = static_cast<int16_t>(g.range(-1, 13));
            }
        }
        return Pair{[] { return origVmVoid(0x002596d0, {}); }, [] { nbClearCommandMemeoyRenzoku(); return uint64_t{0}; }};
    });
    script("SetPlayerSummonPacket", [=](Gen& g) {
        results(g);
        stockWorld(g);
        ActionProcessData& a = act();
        a.party->flag = static_cast<int16_t>(g.chance(50) ? (a.party->flag | 2) : (a.party->flag & ~2));
        a.aisummonid = static_cast<uint32_t>(g.range(1, 383));
        a.work->nowcommand = static_cast<int16_t>(g.pick<int32_t>({1, 1, 0, 5}));
        a.work->nowindex = static_cast<uint16_t>(g.chance(40) ? 0xdf : g.range(0, 15));
        const int32_t d = g.range(0, 13), frame = g.range(0, 40);
        return Pair{[=] { return origVm(0x0024f990, {FW_ACTION, I(0), I(0), I(d), I(frame)}); },
                    [=] { return norm(SetPlayerSummonPacket(act(), 0, 0, d, frame)); }};
    });
    static const State scriptStates[] = {
        {"SetAction_AISCR", 0x00253c40, [](ActionProcessData& a) { SetAction_AISCR(a); return 0; }, false},
        {"CheckAction_AISCR", 0x00253c88, CheckAction_AISCR, true},
        {"SetAction_DEADSCRIPT", 0x00253d00, [](ActionProcessData& a) { SetAction_DEADSCRIPT(a); return 0; }, false},
        {"CheckAction_DEADSCRIPT", 0x00253d38, CheckAction_DEADSCRIPT, true},
        {"SetAction_END", 0x00257b08, [](ActionProcessData& a) { SetAction_END(a); return 0; }, false},
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
        return Pair{[=] { return origVm(0x002642e0, {I(s), I(id)}, {press}); }, [=] { return norm(nbMakePressPacket(s, id, Fl(press))); }};
    });
    add("nbMakeNewPressPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g), type = g.range(-1, 19);
        return Pair{[=] { return origVm(0x00264368, {I(s), I(id), I(type)}); }, [=] { return norm(nbMakeNewPressPacket(s, id, type)); }};
    });
    add("nbMakeFlyBadPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g);
        return Pair{[=] { return origVm(0x00264508, {I(s), I(id), f}); }, [=] { return norm(nbMakeFlyBadPacket(s, id, F(f))); }};
    });
    add("nbMakeBadDamagePacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = someForm(g), bad = 1u << g.range(0, 12);
        return Pair{[=] { return origVm(0x00264528, {I(s), I(id), f, bad}); }, [=] { return norm(nbMakeBadDamagePacket(s, id, F(f), bad)); }};
    });
    add("nbMakeBadKaifukuPacket", [](Gen& g) {
        const int32_t s = frame(g), id = uid(g);
        const uint32_t f = formAddress(g.range(0, 13));
        if (g.chance(20))
            at<Formation>(f).formindex = static_cast<int16_t>(g.range(14, 20));
        return Pair{[=] { return origVm(0x002645a8, {I(s), I(id), f}); }, [=] { return norm(nbMakeBadKaifukuPacket(s, id, at<Formation>(f))); }};
    });
}

} // namespace difftest

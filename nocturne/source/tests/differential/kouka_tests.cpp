// The battle's presentation queue (nbKoukaProcess, nbMakePacket): the
// rewrite against the original instructions, run by the EE interpreter, in a
// random battle with some packets already queued.
#include <cstring>

#include "harness.hpp"
#include "interface_world.hpp"
#include "nocturne/battle/action.hpp"
#include "nocturne/battle/ai_script.hpp"
#include "nocturne/battle/camera.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/data/tables.hpp"

extern "C" {
uint32_t ps2PoolAllocate(int32_t);
uint64_t dds3StartProcess(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
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
            at<ActionProcessData>(data).seq = static_cast<int8_t>(g.range(-1, 22));
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
    auto ailing = [&, camera, cameraState](const char* name, uint32_t entry, int32_t (*rewrite)(ActionProcessData&), bool result) {
        script(name, [=](Gen& g) {
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

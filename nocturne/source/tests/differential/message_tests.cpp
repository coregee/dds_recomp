// Message manager (itfMesManager): the rewrite against the original
// instructions, run by the EE interpreter (ee.hpp) in the same fake world.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "harness.hpp"
#include "version_map.hpp"
#include "interface_world.hpp"
#include "nocturne/battle/combatant.hpp"
#include "nocturne/interface/message.hpp"

extern "C" {
void ps2PacRelocatePointers(uint64_t, uint64_t, uint64_t, uint64_t);
}

namespace difftest {

namespace {

using namespace nocturne::mes;
namespace itf = nocturne::itf;
namespace fr = nocturne::fr;
using iface::A;
using iface::addr;
using iface::I;
using iface::orig;
using iface::origVoid;

constexpr uint32_t kKuti = 0x001d1640;   // ps2MessageKutiDiagnostic: a callback the scripts install

// ---- the world ---------------------------------------------------------------------------

struct World {
    int32_t id;              // the window under test (or -1 for the script)
    int32_t ids[3];          // the windows open
    int32_t count;
    bool relocated;
    std::vector<int32_t> messages, selections;   // dialog numbers by kind
};

FileHeader& table() { return at<FileHeader>(FW_MES_TABLE); }

uint32_t dialogAddress(int32_t index)
{
    TypeHeader& h = at<TypeHeader>(FW_MES_TABLE + 0x20 + 8u * static_cast<uint32_t>(index));
    return table().resolveaddress ? h.ptr : FW_MES_TABLE + 0x20 + h.ptr;
}

uint32_t chain(Gen& g, int32_t x, int32_t y) { return addr(iface::chain(g, x, y)); }

uint32_t panel(Gen& g)
{
    uint32_t p = itf::PnlRegist2(g.below(9), 0x00123450);
    at<itf::Panel>(p).color[3] = g.range(-10, 230);
    return p;
}

void randomInstance(Gen& g, Instance& p, const World& w)
{
    std::memset(&p, 0, sizeof p);
    static const uint32_t high[] = {kNoSpeakerName, kMessageOpen, kSelectOpen, kNoCursor, kWindowOpen, kKeepSpeed, kAutoNext};
    p.stat = g.below(8) | g.pick<uint32_t>({0, 0x10, 0x18, 0x20, 0x28}) | g.below(4) << 8 | g.below(4) << 10 |
             g.below(4) << 12;
    for (uint32_t bit : high)
        if (g.chance(25))
            p.stat |= bit;
    p.pdata.address = FW_MES_TABLE;
    p.pext = g.chance(30) ? FW_FONTS + 0x18000 : 0;   // a font for style 8
    p.z = g.below(0x1000000);
    p.otindex = 0x47;
    p.type = static_cast<int16_t>(g.below(3));

    Speaker& s = p.speaker;
    s.pos = {g.range(0, 0x1000), g.range(0x800, 0xb00)};
    s.pfont.address = g.chance(60) ? chain(g, s.pos.x, s.pos.y) : 0;
    TypeHeader2& h2 = GetTypeHeader2(table());
    int32_t speakers = w.relocated ? h2.spknum : 0;
    s.num = speakers && g.chance(50) ? static_cast<uint16_t>(g.below(static_cast<uint32_t>(speakers)))
          : g.chance(50) ? 0xffff : static_cast<uint16_t>(0x8000 | g.below(4));

    Message& m = p.message;
    m.pos = {g.range(0, 0x1000), g.range(0x800, 0xb00)};
    if (!w.messages.empty())
        m.pbinheader.address = dialogAddress(w.messages[g.below(static_cast<uint32_t>(w.messages.size()))]);
    m.pfont.address = g.chance(70) ? chain(g, m.pos.x, m.pos.y) : 0;
    m.phase = g.pick<int8_t>({-1, 0, 1, 1, 1, 2});
    m.wait = static_cast<uint8_t>(g.below(4));
    m.last_style = static_cast<uint8_t>(g.below(4));
    m.last_col = static_cast<uint8_t>(g.below(6));
    m.last_tp = static_cast<uint8_t>(g.below(3));
    m.last_spd = static_cast<uint8_t>(g.below(140));
    m.lines = static_cast<int16_t>(g.range(0, 4));
    const int16_t pages = m.pbinheader && w.relocated ? m.pbinheader->page : 1;   // a page of the message shown
    m.maxpage = pages;
    m.page = static_cast<int16_t>(g.range(0, pages - 1));

    Select& sel = p.select;
    sel.pos = {g.range(0, 0x1000), g.range(0x900, 0xc00)};
    sel.lines = static_cast<int16_t>(g.range(1, 4));
    sel.pfont.address = chain(g, sel.pos.x, sel.pos.y);
    sel.mask = g.chance(70) ? 0 : g.below(64);
    sel.phase = g.pick<int16_t>({-1, 0, 1, 2, 2, 3, 4, 5});
    sel.select = static_cast<int16_t>(g.range(-1, sel.lines - 1));
    sel.select_imm = static_cast<int16_t>(g.range(-1, sel.lines - 1));
    sel.alpha = static_cast<int16_t>(g.range(-20, 160));
    sel.numdef = static_cast<int16_t>(g.range(0, 4));
    for (DefKey& d : sel.defkey) {
        d.key = static_cast<int16_t>(g.below(16));
        d.index = static_cast<int16_t>(g.range(0, 6));
    }

    Window& win = p.window;
    win.mes.address = (p.stat & kWindowPhaseMask) || g.chance(50) ? panel(g) : 0;
    win.spk.address = (p.stat & kSpeakerPhaseMask) || g.chance(50) ? panel(g) : 0;
    for (int i = 0; i < 4; ++i)
        win.mes_offset[i] = g.range(-0x2000, 0x2000);
    win.mes_color[0] = 0x7f;
    win.mes_color[1] = g.range(0, 0x80);
    win.mes_color[2] = 0x7f;
    win.mes_color[3] = g.range(0, 200);

    // {var n} strings; a dialog's speaker may be "var n" (0..3), which scripts set first.
    static const char* const names[] = {"Pixie", "Jack Frost", "Hijiri", "12", "B3F"};
    for (int i = 0; i < 32; ++i) {
        p.variable.pptr[i] = i < 4 || g.chance(40) ? iface::guestString(names[g.below(5)]) : 0;
        p.variable.pmh[i] = g.below(0x100000);
    }
    p.curctr.isdraw = static_cast<uint8_t>(g.below(4));
    p.curctr.phase = static_cast<int16_t>(g.range(0, 2));
    p.curctr.ctr0 = static_cast<int16_t>(g.chance(40) ? g.pick<int32_t>({32, 40, 64, 72, 246, 247, 255}) : g.range(-10, 300));
    p.curctr.ctr1 = static_cast<int16_t>(g.chance(30) ? g.pick<int32_t>({0, 1, 8}) : g.range(-20, 200));
    p.curctr.ctr_key = g.below(8);
    p.mouthCallback = g.chance(50) ? difftest::version::codeOrDie(kKuti) : 0;
}

// Tables are relocated before the game shows them; `raw` sometimes leaves
// one as on disc (for the functions that relocate it).
World world(Gen& g, bool raw = false)
{
    World w{};
    std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
    w.relocated = !raw || g.chance(50);
    iface::loadTable(g, w.relocated);
    iface::fontWorld(g);
    for (uint32_t k = 0; k < table().numtypeheader; ++k)
        (at<TypeHeader>(FW_MES_TABLE + 0x20 + 8 * k).type ? w.selections : w.messages).push_back(static_cast<int32_t>(k));

    Manager& m = manager();
    std::memset(&m, 0, sizeof m);
    itf::MiscLinkInit(m.list, addr(m.nodes), 0x80, sizeof(itf::LinkNode));
    w.count = g.range(1, 3);
    for (int i = 0; i < w.count; ++i) {
        itf::LinkNode& node = *itf::MiscLinkTake(m.list);
        node.instance.address = FW_MES_INSTANCE + 0x200u * static_cast<uint32_t>(i & 1);
        node.handle = 0x00777000 + static_cast<uint32_t>(i);
        w.ids[i] = node.id;
    }
    m.count = w.count;
    m.texture = 0x00123450;
    m.config = static_cast<uint16_t>(g.below(2));
    randomInstance(g, at<Instance>(FW_MES_INSTANCE), w);
    randomInstance(g, at<Instance>(FW_MES_INSTANCE + 0x200), w);
    w.id = w.ids[g.below(static_cast<uint32_t>(w.count))];

    for (uint32_t i = 0; i < 0x20; ++i)
        fw_ram[0x2f5830 + i] = g.chance(60) ? 0 : g.chance(50) ? 0x80 : static_cast<uint8_t>(g.below(256));
    scriptWork();
    for (int32_t i = 0; i < 8; ++i)
        scriptParam(i, g.range(-2, 12));
    scriptMessageHandle() = g.chance(90) ? w.id : -1;
    return w;
}

int32_t pickMessage(Gen& g, const World& w)
{
    return w.messages.empty() ? 0 : w.messages[g.below(static_cast<uint32_t>(w.messages.size()))];
}

// (Every table loaded has selections.)
int32_t pickSelection(Gen& g, const World& w)
{
    return w.selections[g.below(static_cast<uint32_t>(w.selections.size()))];
}

Instance& inst(const World& w) { return instance(w.id); }
uint64_t instA(const World& w) { return A(&inst(w)); }

// A test of a function on the window under test.
TestCase windowTest(const char* name, uint32_t entry, std::function<void(Instance&)> rewrite)
{
    return {name, [=](Gen& g) {
        World w = world(g);
        uint64_t p = instA(w);
        return Pair{[=] { return origVoid(entry, {p}); }, [=] { rewrite(at<Instance>(static_cast<uint32_t>(p))); return uint64_t{0}; }};
    }};
}

// A script command: the window comes from the script's message handle.
TestCase commandTest(const char* name, uint32_t entry, std::function<int32_t()> rewrite,
                     std::function<void(Gen&, const World&)> setup = {})
{
    return {name, [=](Gen& g) {
        World w = world(g);
        if (setup)
            setup(g, w);
        return Pair{[=] { return orig(entry, {}); }, [=] { return norm(rewrite()); }};
    }};
}

} // namespace

void addMessageTests(std::vector<TestCase>& t)
{
    // ---- the instance list ----
    t.push_back({"itfMiscLinkInit", [](Gen& g) {
        World w = world(g);
        int32_t count = g.range(2, 0x80);
        uint64_t stack = A(&manager().list), nodes = A(manager().nodes);
        return Pair{[=] { return origVoid(0x001cae58, {stack, nodes, I(count), 0x14}); },
                    [=] { itf::MiscLinkInit(manager().list, static_cast<uint32_t>(nodes), count, 0x14); return uint64_t{0}; }};
    }});
    t.push_back({"itfMiscLinkTake", [](Gen& g) {
        World w = world(g);
        for (int n = g.chance(5) ? 0x80 : 0; n > 0; --n)
            itf::MiscLinkTake(manager().list);
        uint64_t stack = A(&manager().list);
        return Pair{[=] { return orig(0x001caeb8, {stack}); },
                    [=] {
                        itf::LinkNode* node = itf::MiscLinkTake(manager().list);
                        return norm(static_cast<int32_t>(node ? fw_address_of(node) : 0));
                    }};
    }});
    t.push_back({"itfMiscLinkGive", [](Gen& g) {
        World w = world(g);
        itf::LinkNode& node = manager().nodes[w.ids[g.below(static_cast<uint32_t>(w.count))]];
        uint64_t n = A(&node), stack = A(&manager().list);
        return Pair{[=] { return origVoid(0x001caf20, {n, stack}); },
                    [=] { itf::MiscLinkGive(at<itf::LinkNode>(static_cast<uint32_t>(n)), manager().list); return uint64_t{0}; }};
    }});

    // ---- construction ----
    t.push_back({"itfMesInitializeSpeaker", [](Gen& g) {
        World w = world(g);
        uint64_t s = A(&inst(w).speaker);
        bool d = g.chance(50);
        return Pair{[=] { return origVoid(0x001cfc58, {s, d}); },
                    [=] { InitializeSpeaker(at<Speaker>(static_cast<uint32_t>(s)), d); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesInitializeMessage", [](Gen& g) {
        World w = world(g);
        uint64_t m = A(&inst(w).message);
        bool d = g.chance(50);
        return Pair{[=] { return origVoid(0x001cfc80, {m, d}); },
                    [=] { InitializeMessage(at<Message>(static_cast<uint32_t>(m)), d); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesInitializeSelect", [](Gen& g) {
        World w = world(g);
        uint64_t s = A(&inst(w).select);
        return Pair{[=] { return origVoid(0x001cfcc8, {s}); },
                    [=] { InitializeSelect(at<Select>(static_cast<uint32_t>(s))); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesInitializeWindow", [](Gen& g) {
        World w = world(g);
        uint64_t s = A(&inst(w).window);
        return Pair{[=] { return origVoid(0x001cfd00, {s}); },
                    [=] { InitializeWindow(at<Window>(static_cast<uint32_t>(s))); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesResetWindowPara", [](Gen& g) {
        World w = world(g);
        uint64_t s = A(&inst(w).window);
        int32_t type = g.range(-1, 3), alpha = g.chance(50) ? 0 : g.range(-5, 300);
        return Pair{[=] { return origVoid(0x001cfed0, {s, I(type), I(alpha)}); },
                    [=] { ResetWindowPara(at<Window>(static_cast<uint32_t>(s)), type, alpha); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesInitializeVariable", [](Gen& g) {
        World w = world(g);
        uint64_t s = A(&inst(w).variable);
        return Pair{[=] { return origVoid(0x001cfd28, {s}); },
                    [=] { InitializeVariable(at<Variable>(static_cast<uint32_t>(s))); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesInitializeCurCtr", [](Gen& g) {
        World w = world(g);
        uint64_t s = A(&inst(w).curctr);
        bool d = g.chance(50);
        return Pair{[=] { return origVoid(0x001cfd58, {s, d}); },
                    [=] { InitializeCurCtr(at<CurCtr>(static_cast<uint32_t>(s)), d); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesResolveResourceAddress", [](Gen& g) {
        World w = world(g, true);
        return Pair{[=] { return origVoid(0x001cf100, {FW_MES_TABLE}); },
                    [=] { ResolveResourceAddress(table()); return uint64_t{0}; }};
    }});
    t.push_back({"GetTypeHeader", [](Gen& g) {
        World w = world(g);
        int32_t k = g.range(0, 20);
        uint64_t p = instA(w);
        return Pair{[=] { return orig(0x001cf178, {p, I(k)}); },
                    [=] { return norm(static_cast<int32_t>(addr(&GetTypeHeader(inst(w), k)))); }};
    }});
    t.push_back({"GetTypeHeader2", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return orig(0x001cf190, {FW_MES_TABLE}); },
                    [=] { return norm(static_cast<int32_t>(addr(&GetTypeHeader2(table())))); }};
    }});
    t.push_back({"itfMesMngSetResourcePtr", [](Gen& g) {
        World w = world(g, true);
        return Pair{[=] { return orig(0x001ce838, {I(w.id), FW_MES_TABLE}); },
                    [=] { return norm(static_cast<int32_t>(SetResourcePtr(w.id, FW_MES_TABLE))); }};
    }});
    t.push_back({"itfMesMngInitialize", [](Gen& g) {
        World w = world(g, true);
        return Pair{[=] { return orig(0x001cda40, {FW_MES_TABLE}); }, [=] { return norm(Initialize(FW_MES_TABLE)); }};
    }});
    t.push_back({"itfMesMngRequestMessageRelease", [](Gen& g) {
        World w = world(g);
        int32_t id = g.chance(10) ? -1 : w.id;
        bool speaker = g.chance(50);
        return Pair{[=] { return origVoid(0x001cdd78, {I(id), speaker}); },
                    [=] { RequestMessageRelease(id, speaker); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngRequestSelectRelease", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return origVoid(0x001cdf80, {I(w.id)}); }, [=] { RequestSelectRelease(w.id); return uint64_t{0}; }};
    }});
    t.push_back(windowTest("itfMesReleaseAllWindow", 0x001cfd88, [](Instance& p) { ReleaseAllWindow(p); }));
    t.push_back({"itfMesReleaseAllVariable", [](Gen& g) {
        World w = world(g);
        uint64_t v = A(&inst(w).variable);
        return Pair{[=] { return origVoid(0x001cfdf8, {v}); },
                    [=] { ReleaseAllVariable(at<Variable>(static_cast<uint32_t>(v))); return uint64_t{0}; }};
    }});
    t.push_back({"ps2MessageManagerReleaseInner", [](Gen& g) {
        World w = world(g);
        int32_t id = g.chance(20) ? g.range(0, 5) : w.id;
        return Pair{[=] { return origVoid(0x001cf058, {I(id)}); }, [=] { ReleaseInstance(id); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngRelease", [](Gen& g) {
        World w = world(g);
        int32_t id = g.chance(10) ? -1 : g.chance(20) ? g.range(0, 5) : w.id;
        return Pair{[=] { return origVoid(0x001cdb38, {I(id)}); }, [=] { Release(id); return uint64_t{0}; }};
    }});
    t.push_back({"CommitVarTable", [](Gen& g) {
        World w = world(g);
        uint64_t v = A(&inst(w).variable);
        return Pair{[=] { return origVoid(0x001cf440, {v}); },
                    [=] { CommitVarTable(at<Variable>(static_cast<uint32_t>(v))); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngGetVarLocalize", [](Gen& g) {
        World w = world(g);
        int32_t k = g.range(0, 31);
        return Pair{[=] { return orig(0x001ce510, {I(w.id), I(k)}); },
                    [=] { return norm(static_cast<int32_t>(GetVarLocalize(w.id, k))); }};
    }});
    t.push_back({"GetMessagePagePtr", [](Gen& g) {
        World w = world(g);
        uint64_t h = dialogAddress(pickMessage(g, w));
        int32_t page = g.range(-1, 5);
        return Pair{[=] { return orig(0x001cf1a8, {h, I(page)}); },
                    [=] { return norm(static_cast<int32_t>(GetMessagePagePtr(at<MesHeader>(static_cast<uint32_t>(h)), page))); }};
    }});
    t.push_back({"GetSpeakerName", [](Gen& g) {
        World w = world(g);
        Instance& p = inst(w);
        int32_t speakers = w.relocated ? GetTypeHeader2(table()).spknum : 0;
        p.speaker.num = static_cast<uint16_t>(speakers ? g.below(static_cast<uint32_t>(speakers)) : 0);
        uint64_t a = instA(w);
        return Pair{[=] { return orig(0x001cf490, {a}); }, [=] { return norm(static_cast<int32_t>(GetSpeakerName(inst(w)))); }};
    }});

    // ---- font request chains ----
    auto chainTest = [&](const char* name, std::function<Pair(Gen&, uint64_t)> body) {
        t.push_back({name, [=](Gen& g) {
            World w = world(g);
            return body(g, chain(g, g.range(0, 0x1000), g.range(0x800, 0xb00)));
        }});
    };
    auto R = [](uint64_t a) { return at<fr::Request>(static_cast<uint32_t>(a)); };
    auto P = [](uint64_t a) { return a ? &at<fr::Request>(static_cast<uint32_t>(a)) : nullptr; };
    chainTest("GetLastLinkFontHandle", [=](Gen&, uint64_t c) {
        return Pair{[=] { return orig(0x001cf710, {c}); }, [=] { return norm(static_cast<int32_t>(addr(GetLastLinkFontHandle(P(c))))); }};
    });
    t.push_back({"GetLastMessagePara", [=](Gen& g) {
        World w = world(g);
        uint64_t c = chain(g, 0, 0), m = A(&inst(w).message);
        return Pair{[=] { return origVoid(0x001cf748, {c, m}); },
                    [=] { GetLastMessagePara(R(c), at<Message>(static_cast<uint32_t>(m))); return uint64_t{0}; }};
    }});
    chainTest("CountLineMessage", [=](Gen&, uint64_t c) {
        uint64_t last = A(GetLastLinkFontHandle(P(c)));
        return Pair{[=] { return orig(0x001cf778, {last, c}); }, [=] { return norm(CountLineMessage(R(last), R(c))); }};
    });
    chainTest("ChangeZBuffer", [=](Gen& g, uint64_t c) {
        uint64_t z = g.below(0x1000000);
        if (g.chance(10)) c = 0;
        return Pair{[=] { return origVoid(0x001cf7e0, {c, z}); }, [=] { ChangeZBuffer(P(c), static_cast<uint32_t>(z)); return uint64_t{0}; }};
    });
    chainTest("ChangeFontPosition", [=](Gen& g, uint64_t c) {
        int32_t x = g.range(-300, 300), y = g.range(-300, 300);
        return Pair{[=] { return origVoid(0x001cf7a8, {c, I(x), I(y)}); }, [=] { ChangeFontPosition(P(c), x, y); return uint64_t{0}; }};
    });
    chainTest("ChangeFontColorAll", [=](Gen& g, uint64_t c) {
        uint8_t color = static_cast<uint8_t>(g.below(8));
        return Pair{[=] { return origVoid(0x001cf8b8, {c, color}); }, [=] { ChangeFontColorAll(P(c), color); return uint64_t{0}; }};
    });
    chainTest("ChangeFontAlpha", [=](Gen& g, uint64_t c) {
        uint32_t alpha = g.below(256);
        return Pair{[=] { return origVoid(0x001cf910, {c, alpha}); }, [=] { ChangeFontAlpha(P(c), alpha); return uint64_t{0}; }};
    });
    chainTest("RaiseMessageSpeedMax", [=](Gen&, uint64_t c) {
        return Pair{[=] { return origVoid(0x001cfa00, {c}); }, [=] { RaiseMessageSpeedMax(P(c)); return uint64_t{0}; }};
    });
    chainTest("RaiseMessageSpeedMaxAll", [=](Gen&, uint64_t c) {
        return Pair{[=] { return origVoid(0x001cfa50, {c}); }, [=] { RaiseMessageSpeedMaxAll(P(c)); return uint64_t{0}; }};
    });
    chainTest("UnchainFontHandleUnit", [=](Gen& g, uint64_t c) {
        int32_t lines = g.range(0, 4), index = g.range(-1, 3);
        return Pair{[=] { return orig(0x001cf5f0, {c, I(index), I(lines)}); },
                    [=] { return norm(static_cast<int32_t>(UnchainFontHandleUnit(P(c), index, lines))); }};
    });
    chainTest("MarkSelectionText", [=](Gen& g, uint64_t c) {
        int32_t lines = g.range(0, 4), index = g.range(-1, 3);
        uint8_t mode = static_cast<uint8_t>(g.below(2));
        return Pair{[=] { return origVoid(0x001cf818, {c, I(index), I(lines), mode}); },
                    [=] { MarkSelectionText(P(c), index, lines, mode); return uint64_t{0}; }};
    });
    chainTest("GetMaxLineWidth", [=](Gen& g, uint64_t c) {
        if (g.chance(10)) c = 0;
        return Pair{[=] { return orig(0x001cf960, {c}); }, [=] { return norm(GetMaxLineWidth(P(c))); }};
    });
    t.push_back({"GetFontHandleUnit", [](Gen& g) {
        World w = world(g);
        uint32_t h = dialogAddress(pickSelection(g, w));
        uint32_t ppstr = h + 0x20, mask = g.chance(60) ? 0 : g.below(16), z = g.below(0x1000000);
        int32_t num = g.range(0, at<SelHeader>(h).item), x = g.range(0, 0x1000), y = g.range(0x800, 0xc00);
        return Pair{[=] { return orig(0x001cf500, {ppstr, I(num), mask, I(x), I(y), z}); },
                    [=] { return norm(static_cast<int32_t>(GetFontHandleUnit(ppstr, num, mask, x, y, z))); }};
    }});
    t.push_back({"GetNumSelectItem", [](Gen& g) {
        int32_t n = g.range(-2, 40);
        uint32_t mask = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return orig(0x001cf4d0, {I(n), mask}); }, [=] { return norm(GetNumSelectItem(n, mask)); }};
    }});
    t.push_back({"GetMaskedIndex", [](Gen& g) {
        int32_t n = g.range(-1, 40);
        uint32_t mask = g.chance(30) ? 0xffffffffu : static_cast<uint32_t>(g.rng());
        return Pair{[=] { return orig(0x001cf9b0, {I(n), mask}); }, [=] { return norm(GetMaskedIndex(n, mask)); }};
    }});

    // ---- requests ----
    t.push_back(windowTest("ReadytoMessage", 0x001cf1d8, [](Instance& p) { ReadytoMessage(p); }));
    t.push_back(windowTest("ps2MessageOpenPanel", 0x001cfa90, [](Instance& p) { OpenMessagePanel(p); }));
    t.push_back(windowTest("ps2MessageOpenSpeakerPanel", 0x001cfb68, [](Instance& p) { OpenSpeakerPanel(p); }));
    t.push_back({"itfMesMngRequestMessage", [](Gen& g) {
        World w = world(g);
        int32_t message = pickMessage(g, w);
        int32_t page = g.range(0, std::max<int32_t>(at<MesHeader>(dialogAddress(message)).page - 1, 0));
        return Pair{[=] { return orig(0x001cdb80, {I(w.id), I(message), I(page)}); },
                    [=] { return norm(RequestMessage(w.id, message, page)); }};
    }});
    // ... in a window marked 0x200000, as the talks do.
    t.push_back({"itfMesMngRequestMessage (marked)", [](Gen& g) {
        World w = world(g);
        int32_t message = pickMessage(g, w);
        int32_t page = g.range(0, std::max<int32_t>(at<MesHeader>(dialogAddress(message)).page - 1, 0));
        MarkBitStat(w.id, 0x200000);
        return Pair{[=] { return orig(0x001cdb80, {I(w.id), I(message), I(page)}); },
                    [=] { return norm(RequestMessage(w.id, message, page)); }};
    }});
    // ... over a message already shown.
    t.push_back({"itfMesMngRequestMessage (again)", [](Gen& g) {
        World w = world(g);
        RequestMessage(w.id, pickMessage(g, w), 0);
        int32_t message = pickMessage(g, w);
        return Pair{[=] { return orig(0x001cdb80, {I(w.id), I(message), I(0)}); }, [=] { return norm(RequestMessage(w.id, message, 0)); }};
    }});
    // ... with some of the first variables unset (not {var 0}, which names
    // the speaker of some messages: the game always sets it).
    t.push_back({"itfMesMngRequestMessage (unset)", [](Gen& g) {
        World w = world(g);
        for (int i = 1; i < 8; ++i)
            if (g.chance(50))
                inst(w).variable.pptr[i] = 0;
        int32_t message = pickMessage(g, w);
        return Pair{[=] { return orig(0x001cdb80, {I(w.id), I(message), I(0)}); }, [=] { return norm(RequestMessage(w.id, message, 0)); }};
    }});
    t.push_back({"itfMesMngRequestSelect", [](Gen& g) {
        World w = world(g);
        int32_t select = pickSelection(g, w);
        return Pair{[=] { return origVoid(0x001cde58, {I(w.id), I(select)}); }, [=] { RequestSelect(w.id, select); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngMarkBitStat", [](Gen& g) {
        World w = world(g);
        uint32_t flag = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVoid(0x001ce450, {I(w.id), flag}); }, [=] { MarkBitStat(w.id, flag); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngClearBitStat", [](Gen& g) {
        World w = world(g);
        uint32_t flag = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVoid(0x001ce480, {I(w.id), flag}); }, [=] { ClearBitStat(w.id, flag); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngMsgWndCls", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return origVoid(0x001cd670, {I(w.id)}); }, [=] { MsgWndCls(w.id); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngSetMesPosition", [](Gen& g) {
        World w = world(g);
        Instance& p = inst(w);
        int32_t x = g.chance(20) ? p.message.pos.x : g.range(0, 0x1000), y = g.chance(20) ? p.message.pos.y : g.range(0x800, 0xb00);
        if (!p.message.pfont)
            p.message.pfont.address = chain(g, 0, 0);
        return Pair{[=] { return origVoid(0x001ce190, {I(w.id), I(x), I(y)}); }, [=] { SetMesPosition(w.id, x, y); return uint64_t{0}; }};
    }});
    t.push_back({"MoveMessagePanel", [](Gen& g) {
        World w = world(g);
        int32_t y = g.range(-100, 100);
        if (!inst(w).window.mes)
            inst(w).window.mes.address = panel(g);
        return Pair{[=] { return origVoid(0x001cd380, {I(w.id), I(y)}); }, [=] { MoveMessagePanel(w.id, y); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngChangeWindowType", [](Gen& g) {
        World w = world(g);
        Instance& p = inst(w);
        int32_t type = g.chance(30) ? p.type : g.range(0, 3), alpha = g.chance(30) ? p.window.mes_color[3] : g.range(0, 200);
        return Pair{[=] { return origVoid(0x001ce908, {I(w.id), I(type), I(alpha)}); },
                    [=] { ChangeWindowType(w.id, type, alpha); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngSetSelectDefKey", [](Gen& g) {
        World w = world(g);
        uint16_t key = static_cast<uint16_t>(g.chance(10) ? g.below(0x10000) : g.below(17));
        uint16_t index = static_cast<uint16_t>(g.below(6));
        if (g.chance(20)) inst(w).select.numdef = 15;
        return Pair{[=] { return orig(0x001ce990, {I(w.id), key, index}); }, [=] { return norm(SetSelectDefKey(w.id, key, index)); }};
    }});
    t.push_back({"itfMesMngSetMaskSelect", [](Gen& g) {
        World w = world(g);
        uint32_t mask = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVoid(0x001ce008, {I(w.id), mask}); }, [=] { SetMaskSelect(w.id, mask); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngSetSelect", [](Gen& g) {
        World w = world(g);
        int32_t n = g.range(-1, 8);
        return Pair{[=] { return origVoid(0x001ce028, {I(w.id), I(n)}); }, [=] { SetSelect(w.id, n); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngSetDefaultSpeed", [](Gen& g) {
        World w = world(g);
        uint8_t speed = static_cast<uint8_t>(g.below(256));
        return Pair{[=] { return origVoid(0x001ceb18, {I(w.id), speed}); }, [=] { SetDefaultSpeed(w.id, speed); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngSetKutiCallback", [](Gen& g) {
        World w = world(g);
        uint32_t f = g.chance(50) ? difftest::version::codeOrDie(kKuti) : 0;
        return Pair{[=] { return origVoid(0x001ceb38, {I(w.id), f}); }, [=] { setMouthCallback(w.id, f); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngGetConfig", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return orig(0x001cec68, {}); }, [=] { return uint64_t{GetConfig()}; }};
    }});
    t.push_back({"itfMesMngGetMessageWidth", [](Gen& g) {
        World w = world(g);
        int32_t message = pickMessage(g, w), page = g.range(-1, 3);
        return Pair{[=] { return orig(0x001cea58, {I(w.id), I(message), I(page)}); },
                    [=] { return norm(GetMessageWidth(w.id, message, page)); }};
    }});

    // ---- each frame ----
    t.push_back({"ForceSetCurCtr", [](Gen& g) {
        World w = world(g);
        uint64_t c = A(&inst(w).curctr);
        int16_t a = static_cast<int16_t>(g.range(-2, 3)), b = static_cast<int16_t>(g.range(0, 255)), d = static_cast<int16_t>(g.range(0, 200));
        return Pair{[=] { return origVoid(0x001cfd78, {c, I(a), I(b), I(d)}); },
                    [=] { ForceSetCurCtr(at<CurCtr>(static_cast<uint32_t>(c)), a, b, d); return uint64_t{0}; }};
    }});
    t.push_back(windowTest("CalcWindow", 0x001cffd0, [](Instance& p) { CalcWindow(p); }));
    t.push_back(windowTest("CalcMessage", 0x001d0118, [](Instance& p) { CalcMessage(p); }));
    t.push_back({"SelectItemMove", [](Gen& g) {
        World w = world(g);
        uint64_t s = A(&inst(w).select);
        int32_t d = g.chance(50) ? -1 : 1;
        return Pair{[=] { return origVoid(0x001d0740, {s, I(d)}); },
                    [=] { SelectItemMove(at<Select>(static_cast<uint32_t>(s)), d); return uint64_t{0}; }};
    }});
    t.push_back({"SelectItemDefKey", [](Gen& g) {
        World w = world(g);
        uint64_t s = A(&inst(w).select);
        return Pair{[=] { return orig(0x001d07f0, {s}); }, [=] { return norm(SelectItemDefKey(at<Select>(static_cast<uint32_t>(s)))); }};
    }});
    t.push_back({"SelectItem", [](Gen& g) {
        World w = world(g);
        uint64_t p = instA(w);
        return Pair{[=] { return orig(0x001d05f0, {p}); }, [=] { return norm(SelectItem(at<Instance>(static_cast<uint32_t>(p)))); }};
    }});
    t.push_back({"SlideUpDownMessage", [](Gen& g) {
        World w = world(g);
        uint64_t p = instA(w);
        int32_t y = g.chance(50) ? -64 : 64;
        return Pair{[=] { return origVoid(0x001d0518, {p, I(y)}); },
                    [=] { SlideUpDownMessage(at<Instance>(static_cast<uint32_t>(p)), y); return uint64_t{0}; }};
    }});
    t.push_back(windowTest("CalcSelect", 0x001d02c0, [](Instance& p) { CalcSelect(p); }));
    t.push_back(windowTest("CalcCurCtr", 0x001d0880, [](Instance& p) { CalcCurCtr(p); }));
    t.push_back(windowTest("CalcMesFlow", 0x001cff98, [](Instance& p) { CalcMesFlow(p); }));
    t.push_back({"CalcManagerProc", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return origVoid(0x001d0ff8, {}); }, [=] { CalcManagerProc(); return uint64_t{0}; }};
    }});

    // ---- script commands ----
    auto messageParam = [](Gen& g, const World& w) { scriptParam(0, pickMessage(g, w)); };
    auto selectParam = [](Gen& g, const World& w) { scriptParam(0, pickSelection(g, w)); };
    t.push_back(commandTest("itfMesMngMessage", 0x001cd2e0, CommandMessage, messageParam));
    t.push_back(commandTest("itfMesMngSelect", 0x001cd408, CommandSelect, selectParam));
    t.push_back(commandTest("itfMesMngMaskSelect", 0x001cd510, CommandMaskSelect));
    t.push_back(commandTest("itfMesMng_SEL_SELNO", 0x001cd560, CommandSetSelectNo));
    t.push_back(commandTest("itfMesMngOpenWindow", 0x001cd5b0, CommandOpenWindow));
    t.push_back(commandTest("itfMesMngCloseWindow", 0x001cd5f8, CommandCloseWindow));
    t.push_back(commandTest("itfMesMngOpenSelectWindow", 0x001cd700, CommandOpenSelectWindow));
    t.push_back(commandTest("itfMesMngCloseSelectWindow", 0x001cd708, CommandCloseSelectWindow));
    t.push_back(commandTest("itfMesMngIgnoreConfig", 0x001cd790, CommandIgnoreConfig));
    t.push_back(commandTest("itfMesMngSetMesPositionScript", 0x001cd7f8, CommandSetMesPosition, [](Gen& g, const World& w) {
        if (!inst(w).message.pfont)
            inst(w).message.pfont.address = chain(g, 0, 0);
    }));
    t.push_back(commandTest("itfMesMngSetMesPosDefault", 0x001cd860, CommandSetMesPosDefault, [](Gen& g, const World& w) {
        if (!inst(w).message.pfont)
            inst(w).message.pfont.address = chain(g, 0, 0);
    }));
    t.push_back(commandTest("itfMesMngValidateNext", 0x001cd8a0, CommandValidateNext));
    t.push_back(commandTest("itfMesMngWindowType", 0x001cd920, CommandWindowType));
    t.push_back(commandTest("itfMesMngWindowTypeAlpha", 0x001cd970, CommandWindowTypeAlpha));
    t.push_back(commandTest("itfMesMngSelectDefKey", 0x001cd9d8, CommandSelectDefKey));
    t.push_back({"itfMesMngGetPhase", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return orig(0x001cd3c8, {I(w.id)}); }, [=] { return norm(CommandGetPhase(w.id)); }};
    }});
    t.push_back({"itfMesMngSetPhase", [](Gen& g) {
        World w = world(g);
        int8_t phase = static_cast<int8_t>(g.range(-1, 2));
        return Pair{[=] { return origVoid(0x001cd3e8, {I(w.id), I(phase)}); }, [=] { CommandSetPhase(w.id, phase); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngGetSelPhase", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return orig(0x001cd4b0, {I(w.id)}); }, [=] { return norm(static_cast<int32_t>(CommandGetSelPhase(w.id))); }};
    }});
    t.push_back({"itfMesMngSetSelPhase", [](Gen& g) {
        World w = world(g);
        int16_t phase = static_cast<int16_t>(g.range(-1, 4));
        return Pair{[=] { return origVoid(0x001cd4d0, {I(w.id), I(phase)}); }, [=] { CommandSetSelPhase(w.id, phase); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngGetSelectNo", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return orig(0x001cd4f0, {I(w.id)}); }, [=] { return norm(static_cast<int32_t>(CommandGetSelectNo(w.id))); }};
    }});
    // ---- {var n} strings ----
    auto someString = [](Gen& g) -> uint32_t {
        switch (g.below(3)) {
        case 0: return at<uint32_t>(difftest::version::dataOrDie(0x003e7328) + 4 * g.below(100));       // a devil's name
        case 1: return difftest::version::dataOrDie(0x00311450) + 32 * g.below(20);                      // an area's name
        default: return FW_MES_TABLE + 0x20 + g.below(0x200);              // whatever is in the table
        }
    };
    t.push_back({"SetVar", [=](Gen& g) {
        World w = world(g);
        int32_t index = g.range(0, 31), length = g.chance(50) ? 0 : g.range(-2, 30);
        uint32_t s = someString(g);
        uint64_t p = instA(w);
        return Pair{[=] { return orig(0x001cf320, {p, I(index), s, I(length)}); },
                    [=] { return norm(static_cast<int32_t>(SetVar(at<Instance>(static_cast<uint32_t>(p)), index, s, length))); }};
    }});
    t.push_back({"itfMesMngSetVarImmediate", [=](Gen& g) {
        World w = world(g);
        int32_t index = g.range(0, 31);
        uint32_t s = someString(g);
        return Pair{[=] { return origVoid(0x001ce7d8, {I(w.id), I(index), s}); }, [=] { SetVarImmediate(w.id, index, s); return uint64_t{0}; }};
    }});
    t.push_back({"itfMesMngSetVarImmediate2", [=](Gen& g) {
        World w = world(g);
        int32_t index = g.range(0, 31), length = g.range(0, 30);
        uint32_t s = someString(g);
        return Pair{[=] { return origVoid(0x001ce808, {I(w.id), I(index), s, I(length)}); },
                    [=] { SetVarImmediate2(w.id, index, s, length); return uint64_t{0}; }};
    }});
    t.push_back({"ConvertZenkakuNumber", [](Gen& g) {
        World w = world(g);
        int32_t n = g.chance(10) ? INT32_MIN : g.chance(10) ? g.range(-50, -1) : g.chance(50) ? g.range(0, 2000) : static_cast<int32_t>(g.rng());
        uint32_t out = FW_SCRATCH + g.below(16);
        return Pair{[=] { return orig(0x001cfe48, {I(n), out}); },
                    [=] { return norm(static_cast<int32_t>(fw_address_of(ConvertZenkakuNumber(n, &at<char>(out))))); }};
    }});
#if NOCTURNE_US   // (US Maniax's only)
    t.push_back({"BuildCharacterName", [](Gen& g) {
        World w = world(g);
        int32_t index = g.range(0, 3);
        return Pair{[=] { return origVoid(0x001ce538, {I(index)}); }, [=] { BuildCharacterName(index); return uint64_t{0}; }};
    }});
#endif
    auto varArgs = [](Gen& g, int32_t& num, int64_t& type) {
        type = g.chance(5) ? g.range(-2, 14) : g.range(0, 10);
        switch (type) {
        case kVarNumber: num = g.chance(50) ? g.range(-100, 100) : static_cast<int32_t>(g.rng()); break;
        case kVarFloor: num = g.chance(10) ? INT32_MIN : g.chance(20) ? g.pick<int32_t>({999, 1000, 1001, 0, -1}) : g.range(-20, 1100); break;
        case kVarCharacter: num = g.range(0, 3); break;
        case kVarDevil: num = g.range(0, 383); break;
        case kVarItem: num = g.range(0, 159); break;
        case kVarSkill: num = g.range(0, 300); break;
        case kVarMagatama: num = g.range(0, 24); break;
        default: num = g.range(0, 31); break;         // races, areas, sub-areas
        }
    };
    t.push_back({"itfMesMngSetVar", [=](Gen& g) {
        World w = world(g);
        int32_t index = g.range(0, 31), num;
        int64_t type;
        varArgs(g, num, type);
        return Pair{[=] { return origVoid(0x001ce5e8, {I(w.id), I(index), I(num), static_cast<uint64_t>(type)}); },
                    [=] { SetVarFormatted(w.id, index, num, static_cast<uint64_t>(type)); return uint64_t{0}; }};
    }});
    t.push_back(commandTest("itfMesMngSetVarScr", 0x001cd710, CommandSetVar, [=](Gen& g, const World&) {
        int32_t num;
        int64_t type;
        varArgs(g, num, type);
        scriptParam(0, g.range(0, 31));
        scriptParam(1, num);
        scriptParam(2, static_cast<int32_t>(type));
    }));
    t.push_back({"nbSetDevilNameMes", [](Gen& g) {
        World w = world(g);
        const int32_t index = g.range(0, 31);
        const uint32_t unit = (iface::guestString("a unit's first sixteen bytes") + 3u) & ~3u;   // only its ID is read
        at<uint16_t>(unit + 4) = static_cast<uint16_t>(g.chance(20) ? 0 : g.range(1, 383));
        return Pair{[=] { return origVoid(0x00259268, {I(w.id), I(index), unit}); },
                    [=] {
                        nocturne::nb::setDevilNameVariable(w.id, index, at<nocturne::UnitWork>(unit));
                        return uint64_t{0};
                    }};
    }});
    t.push_back({"itfMesMngInitializeManager", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return origVoid(0x001ceb58, {}); }, [=] { InitializeManager(); return uint64_t{0}; }};
    }});
    t.push_back({"ExitALL", [](Gen& g) {
        World w = world(g);
        return Pair{[=] { return origVoid(0x001d10a8, {}); }, [=] { ExitAll(); return uint64_t{0}; }};
    }});
}

} // namespace difftest

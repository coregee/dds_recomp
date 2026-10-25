// Script VM (scr*): the rewrite against the original instructions, run by
// the EE interpreter in the same fake world. Scripts are the game's own .bf
// files for loading and starting, and small generated programs (compiled the
// way the FlowScript compiler does) for running.
#include <cstring>
#include <deque>
#include <string>
#include <vector>

#include "harness.hpp"
#include "version_map.hpp"
#include "interface_world.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/effect/event.hpp"
#include "nocturne/kernel/draw.hpp"
#include "nocturne/script/commands.hpp"
#include "nocturne/script/vm.hpp"

extern "C" {
uint32_t ps2PoolAllocate(int32_t);
uint64_t dds3StartProcess(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
}

namespace difftest {

namespace {

using namespace nocturne::scr;
namespace mes = nocturne::mes;
namespace dds3 = nocturne::dds3;
namespace eff = nocturne::eff;
namespace itf = nocturne::itf;
using iface::A;
using iface::addr;
using iface::I;
using iface::origVm;
using iface::origVmVoid;

// The VM's state, by US Maniax's address (mapped for another version).
uint32_t D(uint32_t maniax) { return difftest::version::dataOrDie(maniax); }
uint32_t currentWork() { return D(0x00551c78); }
uint32_t operands() { return D(0x00551c58); }
uint32_t opcodeTable() { return D(0x002fa528); }
uint32_t commandTable() { return D(0x0052e350); }

// The command table's entries for the VM's own commands.
// The commands of scrCommonCommand (the VM's own and the screen effects').
constexpr int16_t kVmCommands[] = {7,   8,   9,   10,  13,  14,  15,  16,  17,  26,  36,  65,  66,  67,  83,  84,  109,
                                   114, 153, 165, 166, 167, 168, 169, 171, 172, 189, 234, 235, 236, 237, 238, 239, 240,
                                   241, 242, 243, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308,
                                   309, 310, 311, 322, 323, 324, 325, 326, 327, 180, 181, 182, 187, 188, 71,
                                   // scrParameterCommand
                                   112, 290, 32,  313, 387, 28,  314, 374, 390, 225, 388, 335, 336, 346,
                                   337, 338, 344, 29,  348, 30,  369, 370, 386, 371, 372, 373, 368, 375};
// A command's entry as the version's table holds it, and as US Maniax's
// address (what the tests below name commands by; 0 for none).
uint32_t ownCommandEntry(int16_t index) { return at<uint32_t>(commandTable() + 8u * static_cast<uint32_t>(index)); }
uint32_t commandEntry(int16_t index) { return difftest::version::maniax(ownCommandEntry(index)); }
int32_t commandArity(int16_t index) { return at<int32_t>(commandTable() + 8u * static_cast<uint32_t>(index) + 4); }

constexpr int kProcedures = 4, kLabels = 64, kLocals = 16, kCodeWords = 512;

uint32_t alloc(uint32_t bytes) { return ps2PoolAllocate(static_cast<int32_t>(bytes)); }
ProcessWork& work(uint64_t address) { return at<ProcessWork>(static_cast<uint32_t>(address)); }

uint32_t randomFloat(Gen& g)
{
    static const float values[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, 3.25f, 1e6f, -7.5f, 100.0f, 0.1f};
    if (g.chance(10))
        return static_cast<uint32_t>(g.rng());
    if (g.chance(30))
        return static_cast<uint32_t>(floatBits(static_cast<float>(g.range(-50, 50))));
    return static_cast<uint32_t>(floatBits(g.pick(values)));
}

int32_t randomInt(Gen& g)
{
    if (g.chance(10))
        return static_cast<int32_t>(g.rng());
    return g.chance(30) ? g.range(-1, 1) : g.range(-100, 300);
}

// A fake process, as dds3StartProcess makes one.
uint32_t process(uint32_t data) { return static_cast<uint32_t>(dds3StartProcess(D(0x0052e270), 0x100, 1, 1, difftest::version::code(0x0010a268),
                                                                         difftest::version::code(0x0010a210), data)); }

// A process argument: one that exists, one that ended, or nonsense.
int32_t processArgument(Gen& g)
{
    if (g.chance(60))
        return static_cast<int32_t>(process(0));
    if (g.chance(50)) {
        uint32_t p = process(0);
        at<uint32_t>(p + 0x34) |= 1;
        return static_cast<int32_t>(p);
    }
    return g.chance(50) ? 0 : randomInt(g);
}

void randomBytes(Gen& g, uint32_t address, uint32_t size)
{
    for (uint32_t i = 0; i < size; ++i)
        fw_ram[address + i] = static_cast<uint8_t>(g.rng());
}

// The screen state: effects on or off, fades in progress, settings, and the
// effect library's objects for the partial effects.
void effectWorld(Gen& g)
{
    dds3::dds3DrawFlag() = static_cast<uint32_t>(g.rng());
    randomBytes(g, D(0x0054e960), 6);              // the screen blur
    randomBytes(g, D(0x0054e97c), 8);              // refused settings
    randomBytes(g, D(0x00551bac), 12);             // the screen blur's fade
    randomBytes(g, D(0x00551c10), 0x48);           // the effects' fades
    randomBytes(g, D(0x005572c0), 0x1f0);          // their settings
    for (uint32_t i = 0; i < 6; ++i)
        fw_ram[D(0x0054f278) + i] = static_cast<uint8_t>(g.below(2));
    randomBytes(g, D(0x003201d0), 0x28);           // Eve_Blur's and Eve_Filter's settings
    randomBytes(g, D(0x00320258), 0x18);
    for (uint32_t i = 0; i < 4; ++i) {          // the partial effects' objects
        const uint32_t object = alloc(0x30);
        randomBytes(g, object, 0x30);
        at<uint32_t>(D(0x00551de8) + 4 * i) = object;
    }
    randomBytes(g, D(0x002f59bc), 4);              // the field of view
    randomBytes(g, D(0x002f5b40), 0x34);           // lights, ambient, fog
    for (uint32_t i = 0; i < 4; ++i) {          // lights (sdf3DLight_t), some missing
        uint32_t light = 0;
        if (g.chance(80)) {
            light = alloc(0x30);
            for (uint32_t k = 0; k < 12; ++k)
                at<uint32_t>(light + 4 * k) = randomFloat(g);
        }
        at<uint32_t>(D(0x002f5b40) + 4 * i) = light;
    }
    for (uint32_t i = 0; i < 4; ++i)
        at<uint32_t>(D(0x002f5b50) + 4 * i) = randomFloat(g);
    randomBytes(g, D(0x00551bc0), 0x50);           // the scene's fades
    randomBytes(g, D(0x00557220), 0x20);
    randomBytes(g, D(0x005572a0), 0x20);
    at<uint32_t>(difftest::version::dataOrDie(0x005518a8)) = randomFloat(g);  // soften, bias
    at<uint32_t>(difftest::version::dataOrDie(0x005518ac)) = randomFloat(g);
}

// Global variables, the message manager, an empty script list.
void baseWorld(Gen& g)
{
    std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
    iface::fontWorld(g);
    mes::Manager& m = mes::manager();
    std::memset(&m, 0, sizeof m);
    itf::MiscLinkInit(m.list, addr(m.nodes), 0x80, sizeof(itf::LinkNode));
    at<uint32_t>(difftest::version::dataOrDie(0x0054ea20)) = FW_GLOBAL;
    for (uint32_t i = 0; i < 256; ++i) {
        globalInt(i) = randomInt(g);
        globalFloat(i) = randomFloat(g);
    }
    scriptList() = {};
    for (uint32_t i = 0; i < 0x20; i += 4)
        at<uint32_t>(operands() + i) = static_cast<uint32_t>(g.rng());
    at<uint32_t>(currentWork()) = 0;
    effectWorld(g);
    randomStock(g);
    for (UnitWork& unit : at<GlobalWork>(FW_GLOBAL).units) {
        if (g.chance(20))
            unit.flag |= UnitFlag::Unique;
        if (g.chance(10))
            unit.flag |= UnitFlag::Pixie;
        if (g.chance(30))
            unit.uniqueid = static_cast<uint16_t>(g.range(0, 5));
    }
    for (uint32_t i = 0; i < 32; ++i)   // the pad's buttons
        fw_ram[D(0x005298c8) + i] = static_cast<uint8_t>(g.chance(50) ? 0 : g.pick<int32_t>({0x80, 0x81, 0x01, 0x7f, 0xff}));
    dds3::quake() = {static_cast<uint16_t>(g.below(2)), static_cast<int16_t>(g.range(-1, 50)), static_cast<uint16_t>(g.below(500)),
                     static_cast<uint16_t>(g.below(500))};
}

// ---- the game's scripts ---------------------------------------------------------------

struct Loaded {
    uint32_t types, procs, labels, code, messages, strings;
    int32_t procedures;
};

// One of the .bf files at FW_MES_TABLE, with its sections.
Loaded loadScript(Gen& g)
{
    const auto& files = iface::scriptFiles();
    const std::vector<uint8_t>& f = files[g.below(static_cast<uint32_t>(files.size()))];
    std::memset(fw_ram + FW_MES_TABLE, 0, 0x10000);
    std::memcpy(fw_ram + FW_MES_TABLE, f.data(), f.size());
    Loaded l{};
    l.types = FW_MES_TABLE + sizeof(Header);
    for (int32_t k = 0; k < at<Header>(FW_MES_TABLE).TypeTableCount; ++k) {
        const TypeTable& t = at<TypeTable>(l.types + 16u * static_cast<uint32_t>(k));
        const uint32_t address = FW_MES_TABLE + t.ItemAddress;
        switch (t.Type) {
        case kProcTable: l.procs = address; l.procedures = t.ItemCount; break;
        case kLabelTable: l.labels = address; break;
        case kScrData: l.code = address; break;
        case kMessage: l.messages = t.ItemCount ? address : 0; break;
        default: l.strings = address; break;
        }
    }
    return l;
}

int64_t someProcedure(Gen& g, const Loaded& l)
{
    return g.chance(10) ? g.pick<int64_t>({-1, l.procedures, l.procedures + 3}) : g.range(0, l.procedures - 1);
}

// Scripts already running from the file, a few with processes.
std::vector<uint32_t> running(Gen& g, const Loaded& l, int count)
{
    std::vector<uint32_t> works;
    for (int i = 0; i < count; ++i) {
        ProcessWork* w = scrAddScript(FW_MES_TABLE, l.types, l.procs, l.labels, l.code, i == 0 && g.chance(50) ? l.messages : 0,
                                      l.strings, g.range(0, l.procedures - 1));
        if (g.chance(40))
            w->ProcessID = process(addr(w));
        if (g.chance(30))
            w->MemHandle = alloc(16) + 1;
        w->data = static_cast<uint32_t>(g.rng());
        works.push_back(addr(w));
    }
    return works;
}

// ---- generated programs ---------------------------------------------------------------

// A random stack entry.
void randomEntry(Gen& g, uint8_t& type, uint32_t& data, uint32_t strings)
{
    const uint32_t roll = g.below(100);
    type = roll < 40 ? kInt : roll < 65 ? kFloat : roll < 75 ? kGlobalInt : roll < 85 ? kGlobalFloat : roll < 90 ? kReturn : kString;
    switch (type) {
    case kInt: data = static_cast<uint32_t>(randomInt(g)); break;
    case kFloat: data = randomFloat(g); break;
    case kGlobalInt:
    case kGlobalFloat: data = g.below(256); break;
    case kReturn: data = g.below(kCodeWords - 2); break;
    default: data = strings + g.below(48); break;
    }
}

// A work for a made-up script: its tables, locals and a stack in use.
uint32_t synthetic(Gen& g)
{
    Header& h = at<Header>(alloc(sizeof(Header)));
    std::memcpy(h.MagicCode, "FLW0", 4);
    h.LocalIntCount = kLocals;
    h.LocalFloatCount = kLocals;
    TypeTable* types = &at<TypeTable>(alloc(5 * sizeof(TypeTable)));
    const int32_t counts[] = {kProcedures, kLabels, kCodeWords, 0, 48};
    const int32_t sizes[] = {32, 32, 4, 1, 1};
    for (int i = 0; i < 5; ++i)
        types[i] = {i, sizes[i], counts[i], 0};
    ProcTable* procs = &at<ProcTable>(alloc(kProcedures * sizeof(ProcTable)));
    ProcTable* labels = &at<ProcTable>(alloc(kLabels * sizeof(ProcTable)));
    for (int i = 0; i < kProcedures; ++i) {
        std::snprintf(procs[i].Name, sizeof procs[i].Name, "proc_%d", i);
        procs[i].CodeAddress = static_cast<int32_t>(g.below(kCodeWords - 2));
    }
    for (int i = 0; i < kLabels; ++i) {
        std::snprintf(labels[i].Name, sizeof labels[i].Name, "_%d", i);
        labels[i].CodeAddress = static_cast<int32_t>(g.below(kCodeWords - 2));
    }
    Code* code = &at<Code>(alloc(kCodeWords * 4));
    for (int i = 0; i < kCodeWords; ++i)
        code[i] = {static_cast<int16_t>(g.below(35)), static_cast<int16_t>(g.below(4))};
    const uint32_t strings = alloc(64);
    for (uint32_t i = 0; i < 64; ++i)
        fw_ram[strings + i] = i % 8 == 7 ? 0 : static_cast<uint8_t>('a' + g.below(26));

    ProcessWork& w = work(alloc(sizeof(ProcessWork)));
    std::snprintf(w.Name, sizeof w.Name, "proc_%d", static_cast<int>(g.below(kProcedures)));
    w.header.address = addr(&h);
    w.typeTable.address = addr(types);
    w.procTable.address = addr(procs);
    w.labelTable.address = addr(labels);
    w.code.address = addr(code);
    w.MessageData = 0;
    w.StringData = strings;
    w.StartProc = static_cast<int32_t>(g.below(kProcedures));
    w.MesHandle = -1;
    w.ScriptTimer = g.range(0, 100);
    w.CommandTimer = g.chance(50) ? 0 : g.range(0, 6);
    w.LocalInt.address = alloc(kLocals * 4);
    w.LocalFloat.address = alloc(kLocals * 4);
    for (int i = 0; i < kLocals; ++i) {
        w.LocalInt[i] = randomInt(g);
        w.LocalFloat[i] = randomFloat(g);
    }
    w.ProcessID = g.chance(50) ? process(addr(&w)) : 0;
    w.data = static_cast<uint32_t>(g.rng());
    w.CP = static_cast<int32_t>(g.below(kCodeWords - 2));
    w.SP = g.range(0, kRegister - 1);
    for (int i = 0; i < kStackSize; ++i)
        randomEntry(g, w.StackType[i], w.StackData[i], strings);
    return addr(&w);
}

// Arguments the scripts pass a command, from the first (the top of the stack).
// The arguments a command reads as floats (a mask), which scripts pass as floats.
uint32_t floatArguments(int16_t command)
{
    switch (commandEntry(command)) {
    case 0x0010bc98: return 0x01;   // SET_FOVY
    case 0x0010c330: return 0x03;   // MUL_BLUR_PARA
    case 0x0010c990: return 0x03;   // BLUR2_PARA
    case 0x0010c510: return 0x38;   // DIST_BLUR_PARA
    case 0x0010bf58: case 0x0010c080: case 0x0010c0f0: case 0x0010bfd0: return 0x0e;   // SCENE_LIGHT_RGB/DIR, AMBIENT, FOG_RGB
    case 0x0010c280: return 0x06;   // SOFTEN_BIAS
    case 0x0010c750: return 0x3e;   // RIP_BLUR_PARA
    default: return 0;
    }
}

// Angles whose conversion to radians lands on SET_FOVY's bounds (5 and 180) or next to them.
uint32_t fovyEdge(Gen& g)
{
    static const std::vector<uint32_t> edges = [] {
        const nocturne::ee::Float k = at<nocturne::ee::Float>(difftest::version::dataOrDie(0x0054c194));
        std::vector<uint32_t> found;
        for (float bound : {5.0f, 180.0f}) {
            uint32_t bits = static_cast<uint32_t>(floatBits(bound * 57.29578f)) - 64;
            for (int i = 0; i < 128; ++i, ++bits) {
                const nocturne::ee::Float r = nocturne::ee::Float::fromBits(bits) * k;
                if (r.bits() >= static_cast<uint32_t>(floatBits(bound)) - 1 && r.bits() <= static_cast<uint32_t>(floatBits(bound)) + 1)
                    found.push_back(bits);
            }
        }
        return found;
    }();
    return edges[g.below(static_cast<uint32_t>(edges.size()))];
}

// A lane of a direction near light 0's own, its opposite, an axis, or any.
uint32_t directionLane(Gen& g, int lane)
{
    static int32_t kind = 0;
    if (lane == 0)
        kind = static_cast<int32_t>(g.below(4));
    const uint32_t light = at<uint32_t>(difftest::version::dataOrDie(0x002f5b40));
    const uint32_t own = light ? at<uint32_t>(light + 0x10 + 4u * static_cast<uint32_t>(lane)) : 0;
    switch (kind) {
    case 0: return own;                  // the same direction
    case 1: return own ^ 0x80000000u;    // the opposite
    case 2: return lane == 1 ? static_cast<uint32_t>(floatBits(g.chance(50) ? 1.0f : -1.0f)) : 0;   // along y
    default: return static_cast<uint32_t>(floatBits(static_cast<float>(g.range(-100, 100)) / 50.0f));
    }
}

// A devil in the stock, or another.
int32_t someStockDevil(Gen& g)
{
    if (g.chance(60))
        return at<GlobalWork>(FW_GLOBAL).units[g.range(0, 15)].id;
    return randomDevil(g);
}

int32_t someFrames(Gen& g) { return g.chance(40) ? 0 : g.chance(5) ? randomInt(g) : g.range(1, 90); }

std::vector<int32_t> commandArguments(Gen& g, ProcessWork& w, int16_t command)
{
    const int32_t arity = commandArity(command);
    std::vector<int32_t> args(static_cast<size_t>(arity));
    for (int32_t& a : args)
        a = randomInt(g);
    if (args.empty())   // SYNC
        return args;
    switch (commandEntry(command)) {
    case 0x0010b888: case 0x0010b8b8: case 0x0010b8e0: args[0] = g.range(0, 0x1fff); break;   // BIT_*
    case 0x0010b908: args[0] = g.range(1, 100); break;                                       // RND
    case 0x0010b960: args[0] = g.range(-2, 5); break;                                        // WAIT
    case 0x0010ba38: case 0x0010bad8:                                                        // FADE_*
        args[0] = g.range(-1, 2);
        args[1] = g.range(0, 60);
        break;
    case 0x0010bb78:                                                                         // SEL_JMP
        args[0] = g.range(-1, arity - 2);
        for (int32_t i = 1; i < arity; ++i)
            args[static_cast<size_t>(i)] = g.chance(10) ? -1 : g.range(0, w.typeTable[1].ItemCount - 1);
        break;
    case 0x0010b9a8: break;                                                                  // PUT
    case 0x0010b9f0: args[0] = static_cast<int32_t>(w.StringData + g.below(48)); break;    // PUTS
    case 0x0010bbd0: case 0x0010bc08: args[0] = g.range(0, 31); break;                       // PAD_*
    case 0x0010bef8:                                                                         // QUAKE_ON
        args[0] = g.chance(20) ? 0 : g.range(1, 900);
        args[1] = g.chance(20) ? 0 : g.chance(10) ? randomInt(g) : g.range(1, 200);
        break;
    case 0x0010bd20:                                                                         // SCR_RUN
        args[0] = g.range(-1, w.typeTable[0].ItemCount);
        args[1] = g.range(-5, 5);
        break;
    case 0x0010bde0: case 0x0010be28: case 0x0010be50: case 0x0010be98:                    // SCR_KILL .. SCR_TIME
        args[0] = processArgument(g);
        break;
    case 0x0010bc40:                                                                         // PAD_ACT
        args[0] = g.range(-1, 3);
        args[1] = g.chance(80) ? g.range(0, 255) : randomInt(g);
        args[2] = g.range(0, 120);
        break;
    case 0x0010c2d8:                                                                         // BLUR
        args[0] = someFrames(g);
        args[1] = g.chance(30) ? 0 : g.range(-10, 255);
        args[2] = g.chance(30) ? 0 : g.range(-10, 400);
        break;
    case 0x0010c330: case 0x0010c990: args[2] = g.range(-1, 4); break;                       // MUL_BLUR / BLUR2_PARA
    case 0x0010cb70: case 0x0010ccf0: args[0] = g.range(-1, 5); break;                       // FILTER2 / MFILTER_PARA
    case 0x0010c510:                                                                         // DIST_BLUR_PARA
        args[0] = g.chance(10) ? g.range(101, 300) : g.range(0, 100);
        args[1] = g.range(0, 64);
        args[2] = g.range(0, 64);
        args[6] = g.range(-1, 4);
        break;
    case 0x0010c750:                                                                         // RIP_BLUR_PARA
        args[0] = g.chance(10) ? g.range(41, 100) : g.range(0, 40);
        args[6] = g.range(-1, 4);
        break;
    case 0x0010c3b8: case 0x0010c5f8: case 0x0010c838:                                       // *_RGBA
    case 0x0010ca30: case 0x0010cbf0: case 0x0010cd70:
        for (int32_t& a : args)
            a = g.chance(90) ? g.range(0, 255) : randomInt(g);
        break;
    case 0x0010c440: case 0x0010c680: case 0x0010c8c0: case 0x0010cdf8:                    // *_AREA (area, x, y)
        args[0] = g.range(0, 400);
        args[1] = g.range(-50, 600);
        args[2] = g.range(-50, 500);
        break;
    case 0x0010c148:                                                                         // SCENE_FOG_PARA
        args[0] = someFrames(g);
        for (int i = 1; i < 5; ++i)
            args[static_cast<size_t>(i)] = g.chance(80) ? g.range(0, 5000) : randomInt(g);
        break;
    case 0x0010bf58: case 0x0010c080: case 0x0010c0f0: case 0x0010c280:                     // SCENE_*, SOFTEN_BIAS
        args[0] = someFrames(g);
        break;
    case 0x0010bfd0:                                                                         // SCENE_LIGHT_DIR
        args[0] = someFrames(g);
        if (g.chance(20))   // too short
            for (int i = 1; i < 4; ++i)
                args[static_cast<size_t>(i)] = static_cast<int32_t>(floatBits(static_cast<float>(g.range(-1, 1)) / 200.0f));
        else
            for (int i = 1; i < 4; ++i)
                args[static_cast<size_t>(i)] = static_cast<int32_t>(directionLane(g, i - 1));
        return args;
    case 0x0010cab8:                                                                         // BLUR2_AREA (x, y)
        args[0] = g.range(-50, 600);
        args[1] = g.range(-50, 500);
        break;
    // scrParameterCommand
    case 0x0010cf38: args[0] = g.range(0, 0x9f); args[1] = g.range(-5, 120); break;          // ITEM_PLUS
    case 0x0010cf78: case 0x0010cfa0: args[0] = g.range(0, 26); break;                       // DH_PLUS, DH_EQUIP
    case 0x0010cfe0: case 0x0010d030:                                                        // MAKA_PLUS, MAKA_CHECK
        args[0] = g.chance(10) ? randomInt(g) : g.range(-100000, 1000000);
        break;
    case 0x0010d008: args[0] = g.range(-120, 200); break;                                    // MAKA_PLUS_PER
    case 0x0010d078: args[0] = g.range(0, 7); break;                                         // PARTY_DAMAGE
    case 0x0010d0f0:                                                                         // DV_PLUS
        args[0] = someStockDevil(g);
        args[1] = g.range(0, 2);
        args[2] = g.chance(60) ? 0 : g.range(1, 5);
        break;
    case 0x0010d1a0: case 0x0010d518: case 0x0010d540:                                      // DV_CHECK, NAKAMA_DEAD, NAKAMA_CHK_PIKUKO
        args[0] = someStockDevil(g);
        break;
    case 0x0010d480: args[0] = someStockDevil(g); args[1] = g.range(0, 5); break;           // NAKAMA_GET_PARAM
    case 0x0010d6a0: args[0] = someStockDevil(g); args[1] = randomDevil(g); break;          // DV_COPY_PARAM
    case 0x0010d1f0: case 0x0010d248: case 0x0010d298: case 0x0010d2c8: case 0x0010d330:   // UDV_*
        args[0] = g.range(-1, 5);
        break;
    case 0x0010d390: args[0] = g.range(-3, 12); break;                                       // STOCK_PLUS
    case 0x0010d410: args[0] = g.range(0, 5); break;                                         // PLAYER_GET_PARAM
    case 0x0010d440: args[0] = g.range(0, 5); args[1] = g.range(-5, 10); break;             // PLAYER_ADD_PARAM
    case 0x0010d658:                                                                         // BOSS_PRESS_REC
        args[0] = g.chance(80) ? g.pick<int32_t>({14, 55, 83, 84, 116, 117, 271, 194, 970, 1008, 267}) : g.range(0, 1300);
        args[1] = g.range(-1, 3);
        break;
    default: args[0] = someFrames(g); break;                                                 // *_SWAP, *_ON, *_OFF
    }
    if (commandEntry(command) == 0x0010bc98) {   // SET_FOVY: degrees, large values, and the bounds' edges
        args[0] = static_cast<int32_t>(g.chance(30)   ? fovyEdge(g)
                                       : g.chance(50) ? floatBits(static_cast<float>(g.range(280, 11000)))
                                                      : floatBits(static_cast<float>(g.range(-10, 180))));
        return args;
    }
    for (int32_t i = 0; i < arity; ++i)
        if (floatArguments(command) >> i & 1)
            args[static_cast<size_t>(i)] = static_cast<int32_t>(g.chance(10) ? randomFloat(g)
                                                                            : floatBits(static_cast<float>(g.range(-720, 720)) / 8.0f));
    return args;
}

bool takesString(int16_t command) { return commandEntry(command) == 0x0010b9f0; }   // PUTS

// Puts a command's arguments on top of the stack (as ints, or now and then a
// float; PUTS mostly gets a string).
void placeArguments(Gen& g, ProcessWork& w, int16_t command, const std::vector<int32_t>& args)
{
    for (size_t i = 0; i < args.size(); ++i) {
        const int32_t slot = w.SP - 1 - static_cast<int32_t>(i);
        if (floatArguments(command) >> i & 1) {   // the bits of a float (now and then passed as an int)
            w.StackType[slot] = g.chance(95) ? kFloat : kInt;
            w.StackData[slot] = static_cast<uint32_t>(args[i]);
            continue;
        }
        const bool asFloat = g.chance(5);
        w.StackType[slot] = takesString(command) && g.chance(90) ? kString : asFloat ? kFloat : kInt;
        w.StackData[slot] = asFloat ? static_cast<uint32_t>(floatBits(static_cast<float>(args[i]))) : static_cast<uint32_t>(args[i]);
    }
}

int16_t someCommand(Gen& g) { return g.pick(kVmCommands); }

// The code word at CP made `op`, with an operand and a stack it can work on.
void prepare(Gen& g, ProcessWork& w, Opcode op)
{
    Code& c = w.code[static_cast<uint32_t>(w.CP)];
    c.s0 = op;
    int16_t operand = static_cast<int16_t>(g.rng());
    switch (op) {
    case PUSHIX: case PUSHFX: case POPIX: case POPFX: operand = static_cast<int16_t>(g.below(256)); break;
    case PUSHLIX: case PUSHLFX: case POPLIX: case POPLFX: operand = static_cast<int16_t>(g.below(kLocals)); break;
    case PUSHSTR: operand = static_cast<int16_t>(g.below(48)); break;
    case JUMP: case CALL: operand = static_cast<int16_t>(g.below(kProcedures)); break;
    case GOTO: case IF: operand = static_cast<int16_t>(g.below(kLabels)); break;
    case COMM: operand = someCommand(g); break;
    default: break;
    }
    c.s1 = operand;
    const bool pushes = op == PUSHI || op == PUSHF || op == PUSHIX || op == PUSHFX || op == PUSHREG || op == PUSHIS ||
                        op == PUSHLIX || op == PUSHLFX || op == PUSHSTR || op == CALL;
    if (pushes && w.SP >= kRegister)
        w.SP = kRegister - 1;
    const int32_t needs = op >= ADD && op <= LE && op != MINUS && op != NOT ? 2
                          : op == POPIX || op == POPFX || op == POPLIX || op == POPLFX || op == MINUS || op == NOT || op == IF ? 1
                                                                                                                             : 0;
    if (w.SP < needs)
        w.SP = needs;
    if (op == DIV) {   // the compiled code traps on an integer division by zero
        if ((w.StackType[w.SP - 2] == kInt && w.StackData[w.SP - 2] == 0) ||
            (w.StackType[w.SP - 2] == kGlobalInt && globalInt(w.StackData[w.SP - 2]) == 0))
            w.StackData[w.SP - 2] = w.StackType[w.SP - 2] == kInt ? 7 : w.StackData[w.SP - 2] ^ 1;
        if (w.StackType[w.SP - 2] == kGlobalInt && globalInt(w.StackData[w.SP - 2]) == 0)
            globalInt(w.StackData[w.SP - 2]) = 3;
    }
    if (op == COMM) {
        const std::vector<int32_t> args = commandArguments(g, w, operand);
        if (w.SP < static_cast<int32_t>(args.size()))
            w.SP = static_cast<int32_t>(args.size());
        placeArguments(g, w, operand, args);
    }
}

// A program as the compiler emits it: procedure 0 runs statements and ENDs;
// procedures 1.. are subroutines it CALLs. Jumps only go forward, so every
// program ends.
class Program {
public:
    Program(Gen& g, ProcessWork& w) : g_(g), w_(w) {}

    void build()
    {
        int32_t subroutines[kProcedures] = {};
        procedure(true);
        for (int p = 1; p < kProcedures; ++p) {
            subroutines[p] = static_cast<int32_t>(code_.size());
            procedure(false);
        }
        for (int p = 0; p < kProcedures; ++p)
            w_.procTable[p].CodeAddress = subroutines[p];
        for (size_t i = 0; i < labels_.size(); ++i)
            w_.labelTable[static_cast<uint32_t>(i)].CodeAddress = labels_[i];
        if (code_.size() > kCodeWords)
            std::abort();
        for (size_t i = 0; i < code_.size(); ++i)
            w_.code[static_cast<uint32_t>(i)] = code_[i];
        w_.CP = 0;
        w_.SP = 0;
        w_.CommandTimer = 0;
        // A string or return address left in the register would unbalance the
        // stack (NOT and IF pop neither); compiled scripts don't use them so.
        if (w_.StackType[kRegister] > kGlobalFloat)
            w_.StackType[kRegister] = kInt;
    }

private:
    void emit(Opcode op, int16_t operand = 0) { code_.push_back({op, operand}); }
    void word(uint32_t bits) { code_.push_back({static_cast<int16_t>(bits), static_cast<int16_t>(bits >> 16)}); }
    int16_t label()
    {
        labels_.push_back(0);
        return static_cast<int16_t>(labels_.size() - 1);
    }
    void place(int16_t l) { labels_[static_cast<size_t>(l)] = static_cast<int32_t>(code_.size()); }
    bool roomFor(size_t words) const { return code_.size() + words + 40 < kCodeWords && labels_.size() + 8 < kLabels; }

    void procedure(bool main)
    {
        const int statements = g_.range(1, main ? 10 : 4);
        for (int i = 0; i < statements && roomFor(30); ++i)
            statement(main);
        emit(END);
    }

    void expression(int depth)
    {
        const uint32_t roll = g_.below(100);
        if (depth >= 3 || roll < 45) {
            switch (g_.below(8)) {
            case 0: emit(PUSHI); word(static_cast<uint32_t>(randomInt(g_))); break;
            case 1: emit(PUSHF); word(randomFloat(g_)); break;
            case 2: emit(PUSHIX, static_cast<int16_t>(g_.below(256))); break;
            case 3: emit(PUSHFX, static_cast<int16_t>(g_.below(256))); break;
            case 4: emit(PUSHLIX, static_cast<int16_t>(g_.below(kLocals))); break;
            case 5: emit(PUSHLFX, static_cast<int16_t>(g_.below(kLocals))); break;
            case 6: emit(PUSHREG); break;
            default: emit(PUSHIS, static_cast<int16_t>(randomInt(g_))); break;
            }
        } else if (roll < 60) {
            expression(depth + 1);
            emit(g_.chance(50) ? MINUS : NOT);
        } else {
            static const Opcode binary[] = {ADD, SUB, MUL, DIV, OR, AND, EQ, NEQ, S, L, SE, LE};
            const Opcode op = g_.pick(binary);
            if (op == DIV)   // the divisor is pushed first: a constant that isn't 0
                emit(PUSHIS, static_cast<int16_t>(g_.chance(50) ? g_.range(1, 9) : -g_.range(1, 9)));
            else
                expression(depth + 1);
            expression(depth + 1);
            emit(op);
        }
    }

    void statement(bool main)
    {
        switch (g_.below(main ? 7 : 5)) {
        case 0:
        case 1: {   // an assignment
            expression(0);
            static const Opcode pops[] = {POPIX, POPFX, POPLIX, POPLFX};
            const Opcode op = g_.pick(pops);
            emit(op, static_cast<int16_t>(op == POPIX || op == POPFX ? g_.below(256) : g_.below(kLocals)));
            break;
        }
        case 2: {   // a command, its result sometimes kept
            const int16_t command = someCommand(g_);
            if (commandEntry(command) == 0x0010bb78 && !roomFor(40))
                break;
            std::vector<int32_t> args = commandArguments(g_, w_, command);
            std::vector<int16_t> targets;
            if (commandEntry(command) == 0x0010bb78)   // SEL_JMP: labels just after
                for (size_t i = 1; i < args.size(); ++i)
                    if (args[i] >= 0)
                        targets.push_back(static_cast<int16_t>(args[i] = label()));
            for (size_t i = args.size(); i-- > 0;) {
                if (takesString(command)) {
                    emit(PUSHSTR, static_cast<int16_t>(g_.below(48)));
                    continue;
                }
                emit(floatArguments(command) >> i & 1 ? PUSHF : PUSHI);
                word(static_cast<uint32_t>(args[i]));
            }
            emit(COMM, command);
            for (int16_t l : targets)
                place(l);
            if (g_.chance(50)) {
                emit(PUSHREG);
                emit(POPIX, static_cast<int16_t>(g_.below(256)));
            }
            break;
        }
        case 3: {   // if
            expression(0);
            const int16_t skip = label();
            emit(IF, skip);
            const int n = g_.range(1, 2);
            for (int i = 0; i < n && roomFor(30); ++i)
                statement(false);
            place(skip);
            break;
        }
        case 4: {   // a goto over a statement
            const int16_t skip = label();
            emit(GOTO, skip);
            statement(false);
            place(skip);
            break;
        }
        default:    // a call
            emit(CALL, static_cast<int16_t>(g_.range(1, kProcedures - 1)));
            break;
        }
    }

    Gen& g_;
    ProcessWork& w_;
    std::vector<Code> code_;
    std::vector<int32_t> labels_;
};

uint32_t program(Gen& g)
{
    uint32_t w = synthetic(g);
    Program(g, work(w)).build();
    return w;
}

// Runs a process frame by frame until its procedure ends (at most 16 frames).
template <class Frame> uint64_t frames(Frame frame)
{
    uint64_t results = 0;
    for (int i = 0; i < 16; ++i) {
        const uint64_t r = frame();
        results = results * 3 + r;
        if (r == 2 || r == static_cast<uint64_t>(-1) || r == 0)
            break;
    }
    return results;
}

// The work set as the running COMM's, with its arguments on the stack.
uint32_t commandWorld(Gen& g, int16_t command)
{
    baseWorld(g);
    ProcessWork& w = work(synthetic(g));
    const std::vector<int32_t> args = commandArguments(g, w, command);
    if (w.SP < static_cast<int32_t>(args.size()))
        w.SP = static_cast<int32_t>(args.size());
    placeArguments(g, w, command, args);
    at<uint32_t>(currentWork()) = addr(&w);
    return addr(&w);
}

using Body = std::function<Pair(Gen&)>;

} // namespace

void addScriptTests(std::vector<TestCase>& t)
{
    auto add = [&](const char* name, Body body) { t.push_back({name, body}); };

    // ---- scripts and processes ----
    add("scrLinkScriptHandleList", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        running(g, l, g.range(0, 3));
        uint32_t w = synthetic(g);
        return Pair{[=] { return origVmVoid(0x00109848, {w}); }, [=] { scrLinkScriptHandleList(work(w)); return uint64_t{0}; }};
    });
    add("scrUnlinkScriptHandleList", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        std::vector<uint32_t> works = running(g, l, g.range(1, 4));
        uint32_t w = works[g.below(static_cast<uint32_t>(works.size()))];
        return Pair{[=] { return origVmVoid(0x00109888, {w}); }, [=] { scrUnlinkScriptHandleList(work(w)); return uint64_t{0}; }};
    });
    add("scrAddScript", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        running(g, l, g.range(0, 2));
        uint32_t parts[7] = {FW_MES_TABLE, l.types, l.procs, l.labels, l.code, l.messages, l.strings};
        if (g.chance(15))
            parts[g.below(7)] = 0;
        int64_t start = someProcedure(g, l);
        return Pair{[=] { return origVm(0x001098e0, {parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], static_cast<uint64_t>(start)}); },
                    [=] { return norm(static_cast<int32_t>(addr(scrAddScript(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], start)))); }};
    });
    add("scrAddScriptFirst", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        return Pair{[=] { return origVm(0x00109e38, {FW_MES_TABLE, l.types, l.procs, l.labels, l.code, l.messages, l.strings}); },
                    [=] { return norm(static_cast<int32_t>(addr(scrAddScriptFirst(FW_MES_TABLE, l.types, l.procs, l.labels, l.code, l.messages, l.strings)))); }};
    });
    add("scrAddScript2", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        if (g.chance(10))
            fw_ram[FW_MES_TABLE + 8 + g.below(4)] ^= 0x20;   // not a FlowScript
        if (g.chance(10))
            at<int32_t>(l.types + 16 * g.below(5)) = g.pick<int32_t>({5, 9, -1});
        if (g.chance(10))
            at<int32_t>(FW_MES_TABLE + 0x10) = g.range(0, 4);
        if (g.chance(20))   // a script without messages (the section is there, empty)
            for (uint32_t k = 0; k < 5; ++k)
                if (at<int32_t>(l.types + 16 * k) == kMessage)
                    at<int32_t>(l.types + 16 * k + 8) = 0;
        int64_t start = someProcedure(g, l);
        return Pair{[=] { return origVm(0x00109b48, {FW_MES_TABLE, static_cast<uint64_t>(start)}); },
                    [=] { return norm(static_cast<int32_t>(addr(scrAddScript2(FW_MES_TABLE, start)))); }};
    });
    add("scrAddScript3", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        uint32_t path = iface::guestString("event/e600/e601/scr/e601.bf");
        int64_t start = someProcedure(g, l);
        return Pair{[=] { return origVm(0x00109c58, {path, static_cast<uint64_t>(start)}); },
                    [=] { return norm(static_cast<int32_t>(addr(scrAddScript3(path, start)))); }};
    });
    add("scrStartScriptProcess", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        uint32_t w = running(g, l, 1)[0];
        int32_t priority = g.range(0, 0x3000);
        return Pair{[=] { return origVm(0x00109cb8, {I(priority), w}); }, [=] { return norm(static_cast<int32_t>(scrStartScriptProcess(priority, &work(w)))); }};
    });
    add("scrStartScript1a", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        int32_t priority = g.range(0, 0x3000);
        int64_t start = g.range(0, l.procedures - 1);   // the game passes procedures that exist
        return Pair{[=] { return origVm(0x00109de8, {I(priority), FW_MES_TABLE, l.types, l.procs, l.labels, l.code, l.messages, l.strings, static_cast<uint64_t>(start)}); },
                    [=] { return norm(static_cast<int32_t>(scrStartScript1a(priority, FW_MES_TABLE, l.types, l.procs, l.labels, l.code, l.messages, l.strings, start))); }};
    });
    add("scrStartScript2", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        int32_t priority = g.range(0, 0x3000);
        int64_t start = g.range(0, l.procedures - 1);   // the game passes procedures that exist
        return Pair{[=] { return origVm(0x00109d98, {I(priority), FW_MES_TABLE, static_cast<uint64_t>(start)}); },
                    [=] { return norm(static_cast<int32_t>(scrStartScript2(priority, FW_MES_TABLE, start))); }};
    });
    add("scrStartScript3", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        uint32_t path = iface::guestString("event/e600/e602/scr/e602.bf");
        int32_t priority = g.range(0, 0x3000);
        int64_t start = g.range(0, l.procedures - 1);
        return Pair{[=] { return origVm(0x00109d48, {I(priority), path, static_cast<uint64_t>(start)}); },
                    [=] { return norm(static_cast<int32_t>(scrStartScript3(priority, path, start))); }};
    });
    add("scrInitGlobalWork", [](Gen& g) {
        baseWorld(g);
        return Pair{[=] { return origVmVoid(0x00109d10, {}); }, [=] { scrInitGlobalWork(); return uint64_t{0}; }};
    });
    add("scrReleaseScript", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        std::vector<uint32_t> works = running(g, l, g.range(1, 3));
        uint32_t w = works[g.below(static_cast<uint32_t>(works.size()))];
        return Pair{[=] { return origVmVoid(0x00109e50, {w}); }, [=] { scrReleaseScript(work(w)); return uint64_t{0}; }};
    });
    add("scrAllReleaseScript", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        running(g, l, g.range(0, 4));
        return Pair{[=] { return origVmVoid(0x00109f08, {}); }, [=] { scrAllReleaseScript(); return uint64_t{0}; }};
    });
    add("scrSearchScriptName", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        std::vector<uint32_t> works = running(g, l, g.range(0, 4));
        uint32_t name = g.chance(70) && !works.empty() ? iface::guestString(work(works[g.below(static_cast<uint32_t>(works.size()))]).Name)
                                                       : iface::guestString(g.chance(50) ? "" : "no_such_procedure");
        return Pair{[=] { return origVm(0x0010a078, {name}); },
                    [=] { return norm(static_cast<int32_t>(addr(scrSearchScriptName(&at<char>(name))))); }};
    });
    add("scrSearchProcedureName", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        uint32_t data = g.chance(5) ? 0 : FW_MES_TABLE;
        uint32_t name = g.chance(80) ? iface::guestString(at<ProcTable>(l.procs + 32u * static_cast<uint32_t>(g.below(static_cast<uint32_t>(l.procedures)))).Name)
                                     : iface::guestString("missing");
        if (g.chance(5))
            at<int32_t>(FW_MES_TABLE + 0x10) = 0;
        return Pair{[=] { return origVm(0x0010a0d0, {data, name}); }, [=] { return norm(scrSearchProcedureName(data, &at<char>(name))); }};
    });
    add("scrSetUserData", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        uint32_t p = process(w);
        uint32_t data = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVmVoid(0x0010a1c8, {p, data}); }, [=] { scrSetUserData(p, data); return uint64_t{0}; }};
    });
    add("scrGetUserData", [](Gen& g) {
        baseWorld(g);
        uint32_t p = process(synthetic(g));
        return Pair{[=] { return origVm(0x0010a1f0, {p}); }, [=] { return norm(static_cast<int32_t>(scrGetUserData(p))); }};
    });
    add("scrScriptShutdown", [](Gen& g) {
        baseWorld(g);
        Loaded l = loadScript(g);
        std::vector<uint32_t> works = running(g, l, g.range(1, 3));
        uint32_t p = process(g.chance(80) ? works[g.below(static_cast<uint32_t>(works.size()))] : 0);
        return Pair{[=] { return origVmVoid(0x0010a210, {p}); }, [=] { scrScriptShutdown(p); return uint64_t{0}; }};
    });
    add("scrScriptProcess", [](Gen& g) {
        baseWorld(g);
        uint32_t w = program(g);
        uint32_t p = process(w);
        work(w).ProcessID = p;
        return Pair{[=] { return frames([&] { return origVm(0x0010a268, {p}); }); },
                    [=] { return frames([&] { return norm(scrScriptProcess(p)); }); }};
    });

    // ---- running ----
    add("scrTraceCode", [](Gen& g) {
        baseWorld(g);
        uint32_t w = program(g);
        return Pair{[=] { return frames([&] { return origVm(0x0010b520, {w}); }); },
                    [=] { return frames([&] { return norm(scrTraceCode(work(w))); }); }};
    });
    for (int op = 0; op <= PUSHSTR; ++op) {
        static const char* const names[] = {"PUSHI", "PUSHF", "PUSHIX", "PUSHFX", "PUSHREG", "POPIX", "POPFX", "PROC", "COMM",
                                            "END", "JUMP", "CALL", "RUN", "GOTO", "ADD", "SUB", "MUL", "DIV", "MINUS", "NOT",
                                            "OR", "AND", "EQ", "NEQ", "S", "L", "SE", "LE", "IF", "PUSHIS", "PUSHLIX",
                                            "PUSHLFX", "POPLIX", "POPLFX", "PUSHSTR"};
        static std::deque<std::string> labels;
        labels.push_back(std::string("Execute ") + names[op]);
        add(labels.back().c_str(), [op](Gen& g) {
            baseWorld(g);
            uint32_t w = synthetic(g);
            prepare(g, work(w), static_cast<Opcode>(op));
            uint32_t handler = difftest::version::maniaxCodeOrDie(at<uint32_t>(opcodeTable() + 4u * static_cast<uint32_t>(op)));
            return Pair{[=] { return origVm(handler, {w}); }, [=] { return norm(Execute(work(w), static_cast<Opcode>(op))); }};
        });
    }
    add("scrPushInt", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        int32_t v = randomInt(g);
        return Pair{[=] { return origVmVoid(0x0010a2c0, {w, I(v)}); }, [=] { scrPushInt(work(w), v); return uint64_t{0}; }};
    });
    add("scrPushFloat", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        uint32_t v = randomFloat(g);
        return Pair{[=] { return origVmVoid(0x0010a2f0, {w}, {v}); }, [=] { scrPushFloat(work(w), v); return uint64_t{0}; }};
    });
    add("scrPushStr", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        uint32_t v = work(w).StringData + g.below(48);
        return Pair{[=] { return origVmVoid(0x0010a320, {w, v}); }, [=] { scrPushStr(work(w), v); return uint64_t{0}; }};
    });
    add("scrPushRet", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        int32_t v = g.range(0, kCodeWords);
        return Pair{[=] { return origVmVoid(0x0010a350, {w, I(v)}); }, [=] { scrPushRet(work(w), v); return uint64_t{0}; }};
    });
    add("scrPopInt", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        work(w).SP = g.range(1, kRegister);
        return Pair{[=] { return origVm(0x0010a380, {w}); }, [=] { return norm(scrPopInt(work(w))); }};
    });
    add("scrPopFloat", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        work(w).SP = g.range(1, kRegister);
        return Pair{[=] { origVm(0x0010a458, {w}); return uint64_t{iface::origVmFloat()}; },
                    [=] { return uint64_t{scrPopFloat(work(w))}; }};
    });
    add("TwoOperation", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        // The operations 0..11 are the opcodes ADD..DIV, OR..LE; larger ones push a stale result.
        static const Opcode opcodes[] = {ADD, SUB, MUL, DIV, OR, AND, EQ, NEQ, S, L, SE, LE};
        int32_t op = g.chance(5) ? g.range(12, 20) : g.range(0, 11);
        prepare(g, work(w), op < 12 ? opcodes[op] : ADD);
        return Pair{[=] { return origVmVoid(0x0010ab48, {w, I(op)}); }, [=] { TwoOperation(work(w), op); return uint64_t{0}; }};
    });

    // ---- for commands ----
    enum Result { kIntResult, kFloatResult, kNoResult };
    auto getter = [&](const char* name, uint32_t entry, std::function<uint64_t(int32_t)> rewrite, Result result = kIntResult) {
        add(name, [=](Gen& g) {
            baseWorld(g);
            uint32_t w = synthetic(g);
            at<uint32_t>(currentWork()) = w;
            if (work(w).SP == 0)
                work(w).SP = 1;
            int32_t index = g.range(0, work(w).SP - 1);
            return Pair{[=] {
                            uint64_t r = origVm(entry, {I(index)});
                            return result == kFloatResult ? uint64_t{iface::origVmFloat()} : result == kNoResult ? 0 : r;
                        },
                        [=] { return rewrite(index); }};
        });
    };
    getter("scrGetIntPara", 0x0010b5c8, [](int32_t i) { return norm(scrGetIntPara(i)); });
    getter("scrGetFloatPara", 0x0010b690, [](int32_t i) { return uint64_t{scrGetFloatPara(i)}; }, kFloatResult);
    getter("scrGetStrPara", 0x0010b748, [](int32_t i) { return norm(static_cast<int32_t>(scrGetStrPara(i))); });
    getter("scrSetIntReturnValue", 0x0010b790, [](int32_t i) { scrSetIntReturnValue(i); return uint64_t{0}; }, kNoResult);
    getter("scrSetCodePointer", 0x0010b800, [](int32_t i) { scrSetCodePointer(i); return uint64_t{0}; }, kNoResult);
    add("scrGetLabelCodeAddress", [](Gen& g) {
        baseWorld(g);
        uint32_t w = synthetic(g);
        at<uint32_t>(currentWork()) = w;
        int32_t label = g.range(0, kLabels - 1);
        return Pair{[=] { return origVm(0x0010b7d8, {I(label)}); }, [=] { return norm(scrGetLabelCodeAddress(label)); }};
    });
    auto accessor = [&](const char* name, uint32_t entry, std::function<uint64_t()> rewrite) {
        add(name, [=](Gen& g) {
            baseWorld(g);
            at<uint32_t>(currentWork()) = synthetic(g);
            return Pair{[=] { return origVm(entry, {}); }, [=] { return rewrite(); }};
        });
    };
    accessor("scrGetCommandTimer", 0x0010b820, [] { return norm(scrGetCommandTimer()); });
    accessor("scrGetMessageHandle", 0x0010b830, [] { return norm(scrGetMessageHandle()); });
    accessor("scrGetScriptHandle", 0x0010b840, [] { return norm(static_cast<int32_t>(addr(scrGetScriptHandle()))); });
    accessor("scrGetData", 0x0010b848, [] { return norm(static_cast<int32_t>(scrGetData())); });
    accessor("SDF_ABORT1", 0x0010b858, [] { return norm(SDF_ABORT1()); });

    // ---- the screen effects' state (effEvent, dds3KernelDraw) ----
    auto effect = [&](const char* name, std::function<Pair(Gen&)> body) {
        add(name, [=](Gen& g) {
            baseWorld(g);
            return body(g);
        });
    };
    auto frames = [](Gen& g) { return someFrames(g); };
    // Eve_*ON / OFF: no arguments.
    struct Plain {
        const char* name;
        uint32_t entry;
        void (*rewrite)();
    };
    static const Plain plain[] = {
        {"Eve_BlurON", 0x001ad230, eff::Eve_BlurON},
        {"Eve_BlurOFF", 0x001ad240, eff::Eve_BlurOFF},
        {"Eve_PartialMultiBlurON", 0x001ad2b8, eff::Eve_PartialMultiBlurON},
        {"Eve_PartialMultiBlurOFF", 0x001ad2c8, eff::Eve_PartialMultiBlurOFF},
        {"Eve_DistortionBlurON", 0x001ad370, eff::Eve_DistortionBlurON},
        {"Eve_DistortionBlurOFF", 0x001ad380, eff::Eve_DistortionBlurOFF},
        {"Eve_RippleBlurON", 0x001ad428, eff::Eve_RippleBlurON},
        {"Eve_RippleBlurOFF", 0x001ad438, eff::Eve_RippleBlurOFF},
        {"Eve_FilterON", 0x001ad4e0, eff::Eve_FilterON},
        {"Eve_FilterOFF", 0x001ad4f0, eff::Eve_FilterOFF},
        {"Eve_PartialMultiFilterON", 0x001ad548, eff::Eve_PartialMultiFilterON},
        {"Eve_PartialMultiFilterOFF", 0x001ad558, eff::Eve_PartialMultiFilterOFF},
        {"dds3StopQuake", 0x00104d98, dds3::dds3StopQuake},
    };
    for (const Plain& p : plain) {
        const uint32_t entry = p.entry;
        void (*rewrite)() = p.rewrite;
        effect(p.name, [=](Gen&) { return Pair{[=] { return origVmVoid(entry, {}); }, [=] { rewrite(); return uint64_t{0}; }}; });
    }
    // Eve_*Get*: the settings' address.
    struct Getter {
        const char* name;
        uint32_t entry;
        const void* (*rewrite)();
    };
    static const Getter getters[] = {
        {"Eve_BlurGetParam", 0x001ad2a8, [] { return static_cast<const void*>(eff::Eve_BlurGetParam()); }},
        {"Eve_PartialMultiBlurEditorGetParams", 0x001ad330,
         [] { return static_cast<const void*>(eff::Eve_PartialMultiBlurEditorGetParams()); }},
        {"Eve_DistortionBlurEditorGetParams", 0x001ad3e8,
         [] { return static_cast<const void*>(eff::Eve_DistortionBlurEditorGetParams()); }},
        {"Eve_RippleBlurEditorGetParams", 0x001ad4a0,
         [] { return static_cast<const void*>(eff::Eve_RippleBlurEditorGetParams()); }},
        {"Eve_FilterEditorGetParams", 0x001ad538, [] { return static_cast<const void*>(eff::Eve_FilterEditorGetParams()); }},
        {"Eve_PartialMultiFilterEditorGetParams", 0x001ad5b0,
         [] { return static_cast<const void*>(eff::Eve_PartialMultiFilterEditorGetParams()); }},
    };
    for (const Getter& p : getters) {
        const uint32_t entry = p.entry;
        const void* (*rewrite)() = p.rewrite;
        effect(p.name, [=](Gen&) {
            return Pair{[=] { return origVm(entry, {}); }, [=] { return norm(static_cast<int32_t>(addr(rewrite()))); }};
        });
    }
    // Eve_*SetParam: settings from somewhere in memory.
    struct Setter {
        const char* name;
        uint32_t entry;
        void (*rewrite)(uint32_t);
    };
    static const Setter setters[] = {
        {"Eve_BlurSetParam", 0x001ad248, [](uint32_t a) { eff::Eve_BlurSetParam(at<eff::Blur>(a)); }},
        {"Eve_PartialMultiBlurSetParam", 0x001ad2d0,
         [](uint32_t a) { eff::Eve_PartialMultiBlurSetParam(at<eff::PartialMultiBlurParam>(a)); }},
        {"Eve_DistortionBlurSetParam", 0x001ad388,
         [](uint32_t a) { eff::Eve_DistortionBlurSetParam(at<eff::DistortionBlurParam>(a)); }},
        {"Eve_RippleBlurSetParam", 0x001ad440, [](uint32_t a) { eff::Eve_RippleBlurSetParam(at<eff::RippleBlurParam>(a)); }},
        {"Eve_FilterSetParam", 0x001ad4f8, [](uint32_t a) { eff::Eve_FilterSetParam(at<eff::Filter>(a)); }},
        {"Eve_PartialMultiFilterSetParam", 0x001ad560,
         [](uint32_t a) { eff::Eve_PartialMultiFilterSetParam(at<eff::PartialMultiFilterParam>(a)); }},
    };
    for (const Setter& p : setters) {
        const uint32_t entry = p.entry;
        void (*rewrite)(uint32_t) = p.rewrite;
        effect(p.name, [=](Gen& g) {
            const uint32_t source = alloc(0x30);
            randomBytes(g, source, 0x30);
            return Pair{[=] { return origVmVoid(entry, {source}); }, [=] { rewrite(source); return uint64_t{0}; }};
        });
    }
    effect("Eve_DistortionBlurSetTex", [](Gen& g) {
        const uint32_t texture = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVmVoid(0x001ad3f0, {texture}); }, [=] { eff::Eve_DistortionBlurSetTex(texture); return uint64_t{0}; }};
    });
    // dds3*Swap / On / Off (frames)
    struct Timed {
        const char* name;
        uint32_t entry;
        void (*rewrite)(int32_t);
    };
    static const Timed timed[] = {
        {"dds3Filter2Swap", 0x00105638, dds3::dds3Filter2Swap},     {"dds3Filter2On", 0x00105700, dds3::dds3Filter2On},
        {"dds3Filter2Off", 0x00105788, dds3::dds3Filter2Off},       {"dds3MFilterSwap", 0x00105830, dds3::dds3MFilterSwap},
        {"dds3MFilterOn", 0x00105900, dds3::dds3MFilterOn},         {"dds3MFilterOff", 0x00105978, dds3::dds3MFilterOff},
        {"dds3Blur2Swap", 0x00105aa0, dds3::dds3Blur2Swap},         {"dds3Blur2On", 0x00105b88, dds3::dds3Blur2On},
        {"dds3Blur2Off", 0x00105c10, dds3::dds3Blur2Off},           {"dds3MultiBlurSwap", 0x00105cc0, dds3::dds3MultiBlurSwap},
        {"dds3MultiBlurOn", 0x00105d98, dds3::dds3MultiBlurOn},     {"dds3MultiBlurOff", 0x00105e00, dds3::dds3MultiBlurOff},
        {"dds3DistBlurSwap", 0x00105ee8, dds3::dds3DistBlurSwap},   {"dds3DistBlurOn", 0x00105fc8, dds3::dds3DistBlurOn},
        {"dds3DistBlurOff", 0x00106038, dds3::dds3DistBlurOff},     {"dds3RipBlurSwap", 0x00106110, dds3::dds3RipBlurSwap},
        {"dds3RipBlurOn", 0x001061f0, dds3::dds3RipBlurOn},         {"dds3RipBlurOff", 0x00106270, dds3::dds3RipBlurOff},
    };
    for (const Timed& p : timed) {
        const uint32_t entry = p.entry;
        void (*rewrite)(int32_t) = p.rewrite;
        effect(p.name, [=](Gen& g) {
            const int32_t frame = frames(g);
            return Pair{[=] { return origVmVoid(entry, {I(frame)}); }, [=] { rewrite(frame); return uint64_t{0}; }};
        });
    }
    // dds3Set*RGBA / Para with one int
    struct One {
        const char* name;
        uint32_t entry;
        void (*rewrite)(uint32_t);
    };
    static const One ones[] = {
        {"dds3SetFilter2Para", 0x00105618, [](uint32_t v) { dds3::dds3SetFilter2Para(static_cast<int32_t>(v)); }},
        {"dds3SetFilter2RGBA", 0x00105628, dds3::dds3SetFilter2RGBA},
        {"dds3SetMFilterPara", 0x001057f8, [](uint32_t v) { dds3::dds3SetMFilterPara(static_cast<int32_t>(v)); }},
        {"dds3SetMFilterRGBA", 0x00105808, dds3::dds3SetMFilterRGBA},
        {"dds3SetBlur2RGBA", 0x00105a78, dds3::dds3SetBlur2RGBA},
        {"dds3SetMultiBlurRGBA", 0x00105c98, dds3::dds3SetMultiBlurRGBA},
        {"dds3SetDistBlurRGBA", 0x00105ec0, dds3::dds3SetDistBlurRGBA},
        {"dds3SetRipBlurRGBA", 0x001060e8, dds3::dds3SetRipBlurRGBA},
    };
    for (const One& p : ones) {
        const uint32_t entry = p.entry;
        void (*rewrite)(uint32_t) = p.rewrite;
        effect(p.name, [=](Gen& g) {
            const uint32_t v = static_cast<uint32_t>(g.rng());
            return Pair{[=] { return origVmVoid(entry, {I(static_cast<int32_t>(v))}); }, [=] { rewrite(v); return uint64_t{0}; }};
        });
    }
    // dds3Set*Area (area, x, y)
    struct Area {
        const char* name;
        uint32_t entry;
        void (*rewrite)(int32_t, int32_t, int32_t);
    };
    static const Area areas[] = {
        {"dds3SetMFilterArea", 0x00105818, dds3::dds3SetMFilterArea},
        {"dds3SetMultiBlurArea", 0x00105ca8, dds3::dds3SetMultiBlurArea},
        {"dds3SetDistBlurArea", 0x00105ed0, dds3::dds3SetDistBlurArea},
        {"dds3SetRipBlurArea", 0x001060f8, dds3::dds3SetRipBlurArea},
    };
    for (const Area& p : areas) {
        const uint32_t entry = p.entry;
        void (*rewrite)(int32_t, int32_t, int32_t) = p.rewrite;
        effect(p.name, [=](Gen& g) {
            const int32_t a = randomInt(g), x = randomInt(g), y = randomInt(g);
            return Pair{[=] { return origVmVoid(entry, {I(a), I(x), I(y)}); }, [=] { rewrite(a, x, y); return uint64_t{0}; }};
        });
    }
    effect("dds3SetBlur2Area", [](Gen& g) {
        const int32_t x = randomInt(g), y = randomInt(g);
        return Pair{[=] { return origVmVoid(0x00105a88, {I(x), I(y)}); }, [=] { dds3::dds3SetBlur2Area(x, y); return uint64_t{0}; }};
    });
    auto F = [](uint32_t bits) { return nocturne::ee::Float::fromBits(bits); };
    effect("dds3SetBlur2Para", [=](Gen& g) {
        const uint32_t r = randomFloat(g), sc = randomFloat(g);
        const int32_t blend = randomInt(g);
        return Pair{[=] { return origVmVoid(0x00105a60, {I(blend)}, {r, sc}); },
                    [=] { dds3::dds3SetBlur2Para(F(r), F(sc), blend); return uint64_t{0}; }};
    });
    effect("dds3SetMultiBlurPara", [=](Gen& g) {
        const uint32_t r = randomFloat(g), sc = randomFloat(g);
        const int32_t blend = randomInt(g);
        return Pair{[=] { return origVmVoid(0x00105c80, {I(blend)}, {r, sc}); },
                    [=] { dds3::dds3SetMultiBlurPara(F(r), F(sc), blend); return uint64_t{0}; }};
    });
    effect("dds3SetDistBlurPara", [=](Gen& g) {
        const int32_t number = g.chance(20) ? randomInt(g) : g.range(0, 120), width = randomInt(g), interval = randomInt(g),
                      blend = randomInt(g);
        const uint32_t speed = randomFloat(g), rotate = randomFloat(g), distor = randomFloat(g);
        return Pair{[=] { return origVmVoid(0x00105e78, {I(number), I(width), I(interval), I(blend)}, {speed, rotate, distor}); },
                    [=] {
                        dds3::dds3SetDistBlurPara(number, width, interval, blend, F(speed), F(rotate), F(distor));
                        return uint64_t{0};
                    }};
    });
    effect("dds3SetRipBlurPara", [=](Gen& g) {
        const int32_t number = g.chance(20) ? randomInt(g) : g.range(0, 60), blend = randomInt(g);
        uint32_t f[5];
        for (uint32_t& v : f)
            v = randomFloat(g);
        return Pair{[=] { return origVmVoid(0x001060a0, {I(number), I(blend)}, {f[0], f[1], f[2], f[3], f[4]}); },
                    [=] {
                        dds3::dds3SetRipBlurPara(F(f[0]), F(f[1]), F(f[2]), F(f[3]), F(f[4]), number, blend);
                        return uint64_t{0};
                    }};
    });
    effect("dds3SetBlur", [](Gen& g) {
        const int32_t frame = g.chance(40) ? 0 : randomInt(g), alpha = g.chance(30) ? 0 : randomInt(g),
                      scale = g.chance(30) ? 0 : randomInt(g);
        return Pair{[=] { return origVmVoid(0x001059e8, {I(frame), I(alpha), I(scale)}); },
                    [=] { dds3::dds3SetBlur(static_cast<uint32_t>(frame), alpha, scale); return uint64_t{0}; }};
    });
    effect("dds3SetScreenFovy", [=](Gen& g) {
        const uint32_t v = randomFloat(g);
        return Pair{[=] { return origVmVoid(0x00105580, {}, {v}); }, [=] { dds3::dds3SetScreenFovy(F(v)); return uint64_t{0}; }};
    });
    effect("dds3SetAmbient", [](Gen& g) {
        const uint32_t source = alloc(0x20);
        randomBytes(g, source, 0x20);
        return Pair{[=] { return origVmVoid(0x00105590, {source}); },
                    [=] { dds3::dds3SetAmbient(*reinterpret_cast<const uint32_t(*)[4]>(&at<uint32_t>(source))); return uint64_t{0}; }};
    });
    effect("dds3SetFog", [](Gen& g) {
        const uint32_t source = alloc(0x20) + g.below(4) * 4;   // any word alignment (copied with LDL / LDR)
        randomBytes(g, source, 0x14);
        return Pair{[=] { return origVmVoid(0x001055a8, {source}); }, [=] { dds3::dds3SetFog(at<dds3::FogParam>(source)); return uint64_t{0}; }};
    });
    effect("dds3SetLight", [](Gen& g) {
        const uint32_t light = static_cast<uint32_t>(g.rng());
        const int32_t no = g.range(0, 3);
        return Pair{[=] { return origVmVoid(0x001055e0, {light, I(no)}); }, [=] { dds3::dds3SetLight(light, no); return uint64_t{0}; }};
    });
    effect("setdraw_xy", [](Gen& g) {
        const uint32_t xy = alloc(0x10);
        randomBytes(g, xy, 0x10);
        return Pair{[=] { return origVmVoid(0x001055f8, {xy}); },
                    [=] { dds3::setdraw_xy(*reinterpret_cast<eff::IVector2(*)[2]>(&at<eff::IVector2>(xy))); return uint64_t{0}; }};
    });
    // A colour vector in memory, as the scripts make them.
    auto vector = [](Gen& g) {
        const uint32_t v = alloc(16);
        for (uint32_t k = 0; k < 4; ++k)
            at<uint32_t>(v + 4 * k) = g.chance(70) ? static_cast<uint32_t>(floatBits(static_cast<float>(g.range(0, 300)) / 128.0f))
                                                   : randomFloat(g);
        return v;
    };
    effect("dds3SetLightColor", [=](Gen& g) {
        const int32_t frame = frames(g);
        const uint32_t no = g.below(4), v = vector(g);
        return Pair{[=] { return origVmVoid(0x001070d0, {I(frame), no, v}); },
                    [=] { dds3::dds3SetLightColor(static_cast<uint32_t>(frame), no, at<dds3::Vector4>(v)); return uint64_t{0}; }};
    });
    effect("dds3SetLightDir", [=](Gen& g) {
        const int32_t frame = frames(g);
        const uint32_t no = g.below(3), v = alloc(16);
        const uint32_t light = at<uint32_t>(D(0x002f5b40) + 4 * no);
        const uint32_t kind = g.below(5);
        for (uint32_t k = 0; k < 4; ++k) {
            const uint32_t own = light ? at<uint32_t>(light + 0x10 + 4 * k) : 0;
            uint32_t lane = static_cast<uint32_t>(floatBits(static_cast<float>(g.range(-100, 100)) / 50.0f));
            if (kind == 0) lane = own;                                 // the same direction
            if (kind == 1) lane = own ^ 0x80000000u;                   // the opposite
            if (kind == 2) lane = k == 1 ? 0xbf800000u : 0;            // along -y
            at<uint32_t>(v + 4 * k) = lane;
        }
        if (light && g.chance(20)) {   // the light itself along y (the opposite turn's special case)
            at<uint32_t>(light + 0x10) = 0;
            at<uint32_t>(light + 0x14) = 0x3f800000;
            at<uint32_t>(light + 0x18) = 0;
            at<uint32_t>(v) = 0;
            at<uint32_t>(v + 4) = 0xbf800000;
            at<uint32_t>(v + 8) = 0;
        }
        return Pair{[=] { return origVmVoid(0x001071d0, {I(frame), no, v}); },
                    [=] { dds3::dds3SetLightDir(static_cast<uint32_t>(frame), no, at<dds3::Vector4>(v)); return uint64_t{0}; }};
    });
    effect("dds3SetAmbientColor", [=](Gen& g) {
        const int32_t frame = frames(g);
        const uint32_t v = vector(g);
        return Pair{[=] { return origVmVoid(0x00107310, {I(frame), v}); },
                    [=] { dds3::dds3SetAmbientColor(static_cast<uint32_t>(frame), at<dds3::Vector4>(v)); return uint64_t{0}; }};
    });
    effect("dds3SetFogColor", [=](Gen& g) {
        const int32_t frame = frames(g);
        const uint32_t v = vector(g);
        return Pair{[=] { return origVmVoid(0x001073d0, {I(frame), v}); },
                    [=] { dds3::dds3SetFogColor(static_cast<uint32_t>(frame), at<dds3::Vector4>(v)); return uint64_t{0}; }};
    });
    effect("dds3SetFogPara", [=](Gen& g) {
        const int32_t frame = frames(g);
        uint32_t f[4];
        for (uint32_t& v : f)
            v = randomFloat(g);
        return Pair{[=] { return origVmVoid(0x00107458, {I(frame)}, {f[0], f[1], f[2], f[3]}); },
                    [=] {
                        dds3::dds3SetFogPara(static_cast<uint32_t>(frame), F(f[0]), F(f[1]), F(f[2]), F(f[3]));
                        return uint64_t{0};
                    }};
    });
    effect("dds3SetSoftenBias", [=](Gen& g) {
        const int32_t frame = frames(g);
        const uint32_t soften = randomFloat(g), bias = randomFloat(g);
        return Pair{[=] { return origVmVoid(0x00107af0, {I(frame)}, {soften, bias}); },
                    [=] { dds3::dds3SetSoftenBias(static_cast<uint32_t>(frame), F(soften), F(bias)); return uint64_t{0}; }};
    });
    effect("dds3SetQuake", [](Gen& g) {
        const int32_t frame = g.chance(20) ? 0 : randomInt(g);
        const uint32_t range = g.chance(20) ? 0 : static_cast<uint32_t>(randomInt(g));
        return Pair{[=] { return origVmVoid(0x00104d38, {I(frame), I(static_cast<int32_t>(range))}); },
                    [=] { dds3::dds3SetQuake(frame, range); return uint64_t{0}; }};
    });

    // ---- the VM's commands ----
    for (int16_t command : kVmCommands) {
        static std::deque<std::string> labels;
        labels.push_back("command " + std::to_string(command));
        add(labels.back().c_str(), [command](Gen& g) {
            commandWorld(g, command);
            const uint32_t entry = commandEntry(command), own = ownCommandEntry(command);
            if (own == 0)   // (a command this version doesn't have: Vanilla lacks Maniax's)
                throw difftest::version::NoCounterpart{0x0052e350u + 8u * static_cast<uint32_t>(command), false};
            if (entry < 0x0010b888 || entry >= 0x0010d728)   // not one of the VM's commands
                std::abort();
            return Pair{[=] { return origVm(entry, {}); }, [=] { return norm(CallCommand(own)); }};
        });
    }
}

} // namespace difftest

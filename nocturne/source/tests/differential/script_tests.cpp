// Script VM (scr*): the rewrite against the original instructions, run by
// the EE interpreter in the same fake world. Scripts are the game's own .bf
// files for loading and starting, and small generated programs (compiled the
// way the FlowScript compiler does) for running.
#include <cstring>
#include <deque>
#include <string>
#include <vector>

#include "harness.hpp"
#include "interface_world.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/kernel/quake.hpp"
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
namespace itf = nocturne::itf;
using iface::A;
using iface::addr;
using iface::I;
using iface::origVm;
using iface::origVmVoid;

constexpr uint32_t kCurrentWork = 0x00551c78;
constexpr uint32_t kOperands = 0x00551c58;
constexpr uint32_t kOpcodeTable = 0x002fa528;
constexpr uint32_t kCommandTable = 0x0052e350;

// The command table's entries for the VM's own commands.
constexpr int16_t kVmCommands[] = {7, 8, 9, 10, 13, 14, 15, 16, 17, 36, 83, 84, 114, 165, 166, 167, 168, 169, 171, 172};
uint32_t commandEntry(int16_t index) { return at<uint32_t>(kCommandTable + 8u * static_cast<uint32_t>(index)); }
int32_t commandArity(int16_t index) { return at<int32_t>(kCommandTable + 8u * static_cast<uint32_t>(index) + 4); }

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
uint32_t process(uint32_t data) { return static_cast<uint32_t>(dds3StartProcess(0x0052e270, 0x100, 1, 1, 0x0010a268, 0x0010a210, data)); }

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

// Global variables, the message manager, an empty script list.
void baseWorld(Gen& g)
{
    std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
    iface::fontWorld(g);
    mes::Manager& m = mes::manager();
    std::memset(&m, 0, sizeof m);
    itf::MiscLinkInit(m.list, addr(m.nodes), 0x80, sizeof(itf::LinkNode));
    at<uint32_t>(0x0054ea20) = FW_GLOBAL;
    for (uint32_t i = 0; i < 256; ++i) {
        globalInt(i) = randomInt(g);
        globalFloat(i) = randomFloat(g);
    }
    scriptList() = {};
    for (uint32_t i = 0; i < 0x20; i += 4)
        at<uint32_t>(kOperands + i) = static_cast<uint32_t>(g.rng());
    at<uint32_t>(kCurrentWork) = 0;
    for (uint32_t i = 0; i < 32; ++i)   // the pad's buttons
        fw_ram[0x005298c8 + i] = static_cast<uint8_t>(g.chance(50) ? 0 : g.pick<int32_t>({0x80, 0x81, 0x01, 0x7f, 0xff}));
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
    default: args[0] = processArgument(g); break;                                            // SCR_KILL .. SCR_TIME
    }
    return args;
}

bool takesString(int16_t command) { return commandEntry(command) == 0x0010b9f0; }   // PUTS

// Puts a command's arguments on top of the stack (as ints, or now and then a
// float; PUTS mostly gets a string).
void placeArguments(Gen& g, ProcessWork& w, int16_t command, const std::vector<int32_t>& args)
{
    for (size_t i = 0; i < args.size(); ++i) {
        const int32_t slot = w.SP - 1 - static_cast<int32_t>(i);
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
                emit(PUSHI);
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
    at<uint32_t>(kCurrentWork) = addr(&w);
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
            uint32_t handler = at<uint32_t>(kOpcodeTable + 4u * static_cast<uint32_t>(op));
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
            at<uint32_t>(kCurrentWork) = w;
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
        at<uint32_t>(kCurrentWork) = w;
        int32_t label = g.range(0, kLabels - 1);
        return Pair{[=] { return origVm(0x0010b7d8, {I(label)}); }, [=] { return norm(scrGetLabelCodeAddress(label)); }};
    });
    auto accessor = [&](const char* name, uint32_t entry, std::function<uint64_t()> rewrite) {
        add(name, [=](Gen& g) {
            baseWorld(g);
            at<uint32_t>(kCurrentWork) = synthetic(g);
            return Pair{[=] { return origVm(entry, {}); }, [=] { return rewrite(); }};
        });
    };
    accessor("scrGetCommandTimer", 0x0010b820, [] { return norm(scrGetCommandTimer()); });
    accessor("scrGetMessageHandle", 0x0010b830, [] { return norm(scrGetMessageHandle()); });
    accessor("scrGetScriptHandle", 0x0010b840, [] { return norm(static_cast<int32_t>(addr(scrGetScriptHandle()))); });
    accessor("scrGetData", 0x0010b848, [] { return norm(static_cast<int32_t>(scrGetData())); });

    // ---- the VM's commands ----
    for (int16_t command : kVmCommands) {
        static std::deque<std::string> labels;
        labels.push_back("command " + std::to_string(command));
        add(labels.back().c_str(), [command](Gen& g) {
            commandWorld(g, command);
            uint32_t entry = commandEntry(command);
            if (entry < 0x0010b888 || entry >= 0x0010bf58)   // not one of the VM's commands
                std::abort();
            return Pair{[=] { return origVm(entry, {}); }, [=] { return norm(CallCommand(entry)); }};
        });
    }
}

} // namespace difftest

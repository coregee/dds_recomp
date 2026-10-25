// The FlowScript virtual machine (original units: ScrScriptProcess,
// ScrTraceCode, scrCommonCommand).
//
// A script process runs one procedure of a compiled script (docs/flowscript.md)
// a frame at a time: scrTraceCode executes code words until one ends the
// procedure or yields (a command that isn't done yet returns 0 and is called
// again next frame). Values live on a 28-entry stack of tagged words; the
// last entry doubles as the register commands return results in.
#include "nocturne/script/vm.hpp"

#include <cstring>
#include <iterator>

#include "nocturne/address.hpp"
#include "nocturne/ee/double.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"
#include "nocturne/interface/message.hpp"
#include "nocturne/script/commands.hpp"

namespace nocturne::scr {

namespace {

constexpr uint32_t kScriptList = addr(0x0054e994);
constexpr uint32_t kCurrent = addr(0x00551c78);        // the work of the running COMM
constexpr uint32_t kGlobalWork = addr(0x0054ea20);     // pointer: ints at +0x40, floats at +0x440
constexpr uint32_t kCommands = addr(0x0052e350);       // scrCommandTable_t[]

// TwoOperation keeps its operands and result in globals (0x551C58).
struct Operands {
    int32_t int_top, int_below, int_result;
    uint32_t float_top, float_below, float_result;
    int32_t type_top, type_below;
};
constexpr uint32_t kOperands = addr(0x00551c58);

// scrCommandTable_t
struct CommandEntry {
    uint32_t comm;
    int32_t paranum;
};

Operands& operands() { return *guest::table<Operands>(kOperands); }
uint32_t addressOf(const void* p) { return guest::addressOf(p); }
uint32_t globalWork() { return *guest::table<uint32_t>(kGlobalWork); }

Code& word(ProcessWork& w, int32_t cp) { return w.code[static_cast<uint32_t>(cp)]; }
int16_t operand(ProcessWork& w) { return word(w, w.CP).s1; }

// Most opcodes end by moving to the next code word.
int32_t advance(ProcessWork& w)
{
    ++w.CP;
    return 1;
}

int32_t procedureAddress(ProcessWork& w, int32_t index) { return w.procTable[static_cast<uint32_t>(index)].CodeAddress; }
int32_t labelAddress(ProcessWork& w, int32_t index) { return w.labelTable[static_cast<uint32_t>(index)].CodeAddress; }

void push(ProcessWork& w, StackType type, uint32_t value)
{
    w.StackType[w.SP] = type;
    w.StackData[w.SP] = value;
    ++w.SP;
}

// An entry's value as an int / as float bits (variables are read through).
int32_t asInt(uint8_t type, uint32_t value)
{
    switch (type) {
    case kInt:
    case kReturn: return static_cast<int32_t>(value);
    case kFloat: return ee::Float::fromBits(value).toInt();
    case kGlobalInt: return globalInt(value);
    case kGlobalFloat: return ee::Float::fromBits(globalFloat(value)).toInt();
    default: return 0;
    }
}

uint32_t asFloat(uint8_t type, uint32_t value)
{
    switch (type) {
    case kInt: return ee::Float::fromInt(static_cast<int32_t>(value)).bits();
    case kFloat: return value;
    case kGlobalInt: return ee::Float::fromInt(globalInt(value)).bits();
    case kGlobalFloat: return globalFloat(value);
    default: return 0;
    }
}

bool isInt(uint8_t type) { return type == kInt || type == kGlobalInt; }
bool isFloat(uint8_t type) { return type == kFloat || type == kGlobalFloat; }

// A float's truth, as the compiled C tests it (in double precision).
bool truth(uint32_t bits) { return compare(ee::Double::fromFloat(ee::Float::fromBits(bits)), ee::Double::fromInt(0)) != 0; }

// The EE's own float comparisons.
bool equal(uint32_t a, uint32_t b) { return ee::Float::fromBits(a) == ee::Float::fromBits(b); }
bool less(uint32_t a, uint32_t b) { return ee::Float::fromBits(a) < ee::Float::fromBits(b); }
bool lessEqual(uint32_t a, uint32_t b) { return ee::Float::fromBits(a) <= ee::Float::fromBits(b); }

} // namespace

// scrPrintf @ 0x001097E8 (no original name): a debug print, compiled out.
void scrPrintf(uint32_t, uint32_t) {}

ScriptList& scriptList() { return *guest::table<ScriptList>(kScriptList); }
ProcessWork* current() { return guest::table<Ptr32<ProcessWork>>(kCurrent)->get(); }
int32_t& globalInt(uint32_t index) { return guest::table<int32_t>(globalWork() + 0x40)[index]; }
uint32_t& globalFloat(uint32_t index) { return guest::table<uint32_t>(globalWork() + 0x440)[index]; }

// ---- scripts and processes ---------------------------------------------------------------

// scrLinkScriptHandleList @ 0x00109848
void scrLinkScriptHandleList(ProcessWork& work)
{
    ScriptList& list = scriptList();
    if (ProcessWork* last = list.scrHandleLast.get()) {
        work.prev.address = addressOf(last);
        last->next.address = addressOf(&work);
        work.next.address = 0;
        list.scrHandleLast.address = addressOf(&work);
    } else {
        list.scrHandleFirst.address = addressOf(&work);
        list.scrHandleLast.address = addressOf(&work);
        work.next.address = 0;
        work.prev.address = 0;
    }
    ++list.scrHandleCount;
}

// scrUnlinkScriptHandleList @ 0x00109888
void scrUnlinkScriptHandleList(ProcessWork& work)
{
    ScriptList& list = scriptList();
    const uint32_t self = addressOf(&work);
    if (list.scrHandleFirst.address == self)
        list.scrHandleFirst = work.next;
    else
        work.prev->next = work.next;
    if (list.scrHandleLast.address == self)
        list.scrHandleLast = work.prev;
    else
        work.next->prev = work.prev;
    work.next.address = 0;
    work.prev.address = 0;
    --list.scrHandleCount;
}

// scrAddScript @ 0x001098E0
// A process work for procedure `startproc` of a loaded script: its locals,
// and a message window when the script has messages. Null when a part is
// missing or the procedure doesn't exist.
ProcessWork* scrAddScript(uint32_t header, uint32_t typetable, uint32_t proctable, uint32_t labeltable, uint32_t code,
                          uint32_t mesdata, uint32_t stringdata, int64_t startproc)
{
    if (!header || !typetable || !proctable || !code || startproc < 0)
        return nullptr;
    if (startproc >= guest::table<TypeTable>(typetable)->ItemCount)
        return nullptr;
    ProcessWork* w = guest::table<ProcessWork>(mem::PoolAllocate(sizeof(ProcessWork)));
    if (!w)
        return nullptr;
    const ProcTable& proc = guest::table<ProcTable>(proctable)[startproc];
    for (size_t i = 0;; ++i) {
        w->Name[i] = proc.Name[i];
        if (!proc.Name[i])
            break;
    }
    w->SP = 0;
    w->CP = proc.CodeAddress;
    for (int i = 0; i < kStackSize; ++i) {
        w->StackType[i] = 0;
        w->StackData[i] = 0;
    }
    const Header& h = *guest::table<Header>(header);
    w->typeTable.address = typetable;
    w->code.address = code;
    w->labelTable.address = labeltable;
    w->StringData = stringdata;
    w->StartProc = static_cast<int32_t>(startproc);
    w->MesHandle = -1;
    w->header.address = header;
    w->procTable.address = proctable;
    w->MessageData = mesdata;
    w->ScriptTimer = 0;
    w->CommandTimer = 0;
    w->MemHandle = 0;
    w->LocalInt.address = 0;
    w->LocalFloat.address = 0;
    w->ProcessID = 0;
    w->prev.address = 0;
    w->next.address = 0;
    if (h.LocalIntCount > 0) {
        w->LocalInt.address = mem::PoolAllocate(h.LocalIntCount * 4);
        for (int k = 0; k < h.LocalIntCount; ++k)
            w->LocalInt[k] = 0;
    } else {
        w->LocalInt.address = 0;
    }
    if (h.LocalFloatCount > 0) {
        w->LocalFloat.address = mem::PoolAllocate(h.LocalFloatCount * 4);
        for (int k = 0; k < h.LocalFloatCount; ++k)
            w->LocalFloat[k] = 0;
    } else {
        w->LocalFloat.address = 0;
    }
    if (mesdata)
        w->MesHandle = mes::Initialize(mesdata);
    scrLinkScriptHandleList(*w);
    diag::print(diag::Message::ProcedureStart, addressOf(&proc));
    scrPrintf(optionalAddr(0x0052e288), addressOf(&proc));
    return w;
}

// 0x00109E38 (no original name): procedure 0.
ProcessWork* scrAddScriptFirst(uint32_t header, uint32_t typetable, uint32_t proctable, uint32_t labeltable, uint32_t code,
                               uint32_t mesdata, uint32_t stringdata)
{
    return scrAddScript(header, typetable, proctable, labeltable, code, mesdata, stringdata, 0);
}

// scrAddScript2 @ 0x00109B48
// The same from a whole .bf file in memory ("FLW0"); null for anything
// else. Later sections of a kind win; an empty message section is ignored.
ProcessWork* scrAddScript2(uint32_t data, int64_t startproc)
{
    const Header& h = *guest::table<Header>(data);
    if (std::memcmp(h.MagicCode, "FLW0", 4) != 0)
        return nullptr;
    const uint32_t types = data + sizeof(Header);
    uint32_t proc = 0, labels = 0, code = 0, messages = 0, strings = 0;
    for (uint32_t k = 0; static_cast<int64_t>(k) < static_cast<int64_t>(static_cast<int32_t>(h.TypeTableCount)); ++k) {
        const TypeTable& t = guest::table<TypeTable>(types)[k];
        if (static_cast<uint32_t>(t.Type) >= 5)
            return nullptr;
        const uint32_t address = data + t.ItemAddress;
        switch (t.Type) {
        case kProcTable: proc = address; break;
        case kLabelTable: labels = address; break;
        case kScrData: code = address; break;
        case kMessage:
            if (t.ItemCount)
                messages = address;
            break;
        default: strings = address; break;
        }
    }
    return scrAddScript(data, types, proc, labels, code, messages, strings, startproc);
}

// scrAddScript3 @ 0x00109C58: the same, loading the file first (kept with the work).
ProcessWork* scrAddScript3(uint32_t path, int64_t startproc)
{
    uint32_t data = 0;
    const uint32_t handle = file::Load(path, &data);
    ProcessWork* work = data ? scrAddScript2(data, startproc) : nullptr;
    if (work)
        work->MemHandle = handle;
    return work;
}

// scrStartScriptProcess @ 0x00109CB8
// Starts a process named after the procedure that runs the work every frame.
uint32_t scrStartScriptProcess(int32_t priority, ProcessWork* work)
{
    const uint32_t name = work->procTable.address + static_cast<uint32_t>(work->StartProc) * sizeof(ProcTable);
    const uint32_t process = dds3::StartProcess(name, priority, 1, 1, addr(0x0010a268), addr(0x0010a210), addressOf(work));
    work->ProcessID = process;
    return process;
}

// scrStartScript1a @ 0x00109DE8
// Adds the script and starts its process. None of the StartScript functions
// checks that the script was added: callers pass procedures that exist.
uint32_t scrStartScript1a(int32_t priority, uint32_t header, uint32_t typetable, uint32_t proctable, uint32_t labeltable,
                          uint32_t code, uint32_t mesdata, uint32_t stringdata, int64_t startproc)
{
    return scrStartScriptProcess(priority, scrAddScript(header, typetable, proctable, labeltable, code, mesdata, stringdata, startproc));
}

// scrStartScript2 @ 0x00109D98
uint32_t scrStartScript2(int32_t priority, uint32_t data, int64_t startproc)
{
    return scrStartScriptProcess(priority, scrAddScript2(data, startproc));
}

// scrStartScript3 @ 0x00109D48
uint32_t scrStartScript3(int32_t priority, uint32_t path, int64_t startproc)
{
    return scrStartScriptProcess(priority, scrAddScript3(path, startproc));
}

// scrInitGlobalWork @ 0x00109D10: clears the global variables.
void scrInitGlobalWork()
{
    for (uint32_t i = 0; i < 256; ++i) {
        globalInt(i) = 0;
        globalFloat(i) = 0;
    }
}

// scrReleaseScript @ 0x00109E50
// Frees a work: its locals, message window and file, then itself.
void scrReleaseScript(ProcessWork& work)
{
    const uint32_t proc = work.procTable.address + static_cast<uint32_t>(work.StartProc) * sizeof(ProcTable);
    diag::print(diag::Message::ProcedureEnd, proc);
    scrPrintf(optionalAddr(0x0052e2d0), proc);
    if (work.LocalInt)
        mem::PoolRelease(work.LocalInt.address);
    if (work.LocalFloat)
        mem::PoolRelease(work.LocalFloat.address);
    if (work.MesHandle >= 0)
        mes::Release(work.MesHandle);
    if (work.MemHandle)
        mem::HandleFree(work.MemHandle);
    scrUnlinkScriptHandleList(work);
    mem::PoolRelease(addressOf(&work));
}

// scrAllReleaseScript @ 0x00109F08
// Ends every script: those with a process through it, the others directly.
void scrAllReleaseScript()
{
    diag::print(diag::Message::ScriptsBefore, scriptList().scrHandleCount);
    for (ProcessWork* w = scriptList().scrHandleFirst.get(); w;) {
        diag::print(diag::Message::ScriptRelease, addressOf(w));
        ProcessWork* next = w->next.get();
        if (w->ProcessID) {
            diag::print(diag::Message::ScriptKillProcess);
            dds3::KillProcess(w->ProcessID, 0);
        } else {
            diag::print(diag::Message::ScriptReleaseWork);
            scrReleaseScript(*w);
        }
        w = next;
    }
    diag::print(diag::Message::ScriptsAfter, scriptList().scrHandleCount);
}

// scrSearchScriptName @ 0x0010A078: the running script of that procedure, or null.
ProcessWork* scrSearchScriptName(const char* name)
{
    for (ProcessWork* w = scriptList().scrHandleFirst.get(); w; w = w->next.get())
        if (std::strcmp(name, w->Name) == 0)
            return w;
    return nullptr;
}

// scrSearchProcedureName @ 0x0010A0D0: a procedure's number in a .bf file, or -1.
int32_t scrSearchProcedureName(uint32_t data, const char* name)
{
    if (!data)
        return -1;
    const Header& h = *guest::table<Header>(data);
    const TypeTable* types = guest::table<TypeTable>(data + sizeof(Header));
    int32_t section = 0;
    uint32_t records = 0;
    for (; section < h.TypeTableCount; ++section) {
        if (types[section].Type == kProcTable) {
            records = data + types[section].ItemAddress;
            break;
        }
    }
    if (!records)
        return -1;
    const int32_t count = types[section].ItemCount;
    if (count <= 0)
        return -1;
    const ProcTable* procs = guest::table<ProcTable>(records);
    for (int32_t index = 0; index < count; ++index)
        if (std::strcmp(procs[index].Name, name) == 0)
            return index;
    return -1;
}

// scrSetUserData @ 0x0010A1C8
void scrSetUserData(uint32_t process, uint32_t data) { guest::table<ProcessWork>(dds3::GetProcessData(process))->data = data; }

// scrGetUserData @ 0x0010A1F0 (no original name)
uint32_t scrGetUserData(uint32_t process) { return guest::table<ProcessWork>(dds3::GetProcessData(process))->data; }

// scrScriptShutdown @ 0x0010A210: a script process's end.
void scrScriptShutdown(uint32_t process)
{
    if (uint32_t work = dds3::GetProcessData(process))
        scrReleaseScript(*guest::table<ProcessWork>(work));
    dds3::SetProcessData(process, 0);
}

// scrScriptProcess @ 0x0010A268
// A script process's frame: -1 to keep running (the procedure yielded) or
// to stop (it ended), 0 otherwise.
int32_t scrScriptProcess(uint32_t process)
{
    const int32_t result = scrTraceCode(*guest::table<ProcessWork>(dds3::GetProcessData(process)));
    return result == 0 || result == 2 ? -1 : 0;
}

// ---- running -------------------------------------------------------------------------------

// scrTraceCode @ 0x0010B520
// Runs code words until the procedure ends (2) or a command waits for the
// next frame (1). The command timer counts the frames a command has waited.
int32_t scrTraceCode(ProcessWork& work)
{
    for (;;) {
        const int32_t result = Execute(work, static_cast<Opcode>(word(work, work.CP).s0));
        if (result == 0) {
            work.CommandTimer = 0;
            return 2;
        }
        if (result == 2) {
            ++work.CommandTimer;
            ++work.ScriptTimer;
            return 1;
        }
        if (result == 1)
            work.CommandTimer = 0;
    }
}

// scrPushInt @ 0x0010A2C0
void scrPushInt(ProcessWork& work, int32_t value) { push(work, kInt, static_cast<uint32_t>(value)); }
// scrPushFloat @ 0x0010A2F0
void scrPushFloat(ProcessWork& work, uint32_t bits) { push(work, kFloat, bits); }
// scrPushStr @ 0x0010A320
void scrPushStr(ProcessWork& work, uint32_t address) { push(work, kString, address); }
// scrPushRet @ 0x0010A350
void scrPushRet(ProcessWork& work, int32_t cp) { push(work, kReturn, static_cast<uint32_t>(cp)); }

// scrPopInt @ 0x0010A380 (0 for a string)
int32_t scrPopInt(ProcessWork& work)
{
    const int32_t sp = --work.SP;
    const uint8_t type = work.StackType[sp];
    if (type > kReturn)
        return 0;
    return asInt(type, work.StackData[sp]);
}

// scrPopFloat @ 0x0010A458 (0 for a return address or a string)
uint32_t scrPopFloat(ProcessWork& work)
{
    const int32_t sp = --work.SP;
    const uint8_t type = work.StackType[sp];
    if (type > kGlobalFloat)
        return 0;
    return asFloat(type, work.StackData[sp]);
}

// scrCodeFunc_2Operation @ 0x0010AB48
// A binary operator on the top two entries (the top one is the left
// operand). Ints when both are ints, floats otherwise; comparisons and the
// logical operators give an int.
void TwoOperation(ProcessWork& work, int32_t op)
{
    Operands& o = operands();
    const uint8_t below = work.StackType[work.SP - 2], top = work.StackType[work.SP - 1];
    o.type_below = static_cast<int8_t>(below);
    o.type_top = static_cast<int8_t>(top);
    if (isInt(top) && isInt(below)) {
        o.int_top = scrPopInt(work);
        o.int_below = scrPopInt(work);
        if (op < 12) {
            const int32_t a = o.int_top, b = o.int_below;
            int32_t value = 0;
            switch (op) {
            case 0: value = static_cast<int32_t>(static_cast<uint32_t>(a) + static_cast<uint32_t>(b)); break;
            case 1: value = static_cast<int32_t>(static_cast<uint32_t>(a) - static_cast<uint32_t>(b)); break;
            case 2: value = static_cast<int32_t>(static_cast<uint32_t>(a) * static_cast<uint32_t>(b)); break;
            case 3:
                if (b == 0)
                    divideByZeroTrap();
                value = (a == INT32_MIN && b == -1) ? INT32_MIN : a / b;
                break;
            case 4: value = a != 0 || b != 0; break;
            case 5: value = a != 0 && b != 0; break;
            case 6: value = a == b; break;
            case 7: value = a != b; break;
            case 8: value = a < b; break;
            case 9: value = b < a; break;
            case 10: value = a <= b; break;
            case 11: value = b <= a; break;
            }
            o.int_result = value;
        }
        scrPushInt(work, o.int_result);
        return;
    }
    o.float_top = scrPopFloat(work);
    o.float_below = scrPopFloat(work);
    if (op < 12) {
        const uint32_t a = o.float_top, b = o.float_below;
        const ee::Float fa = ee::Float::fromBits(a), fb = ee::Float::fromBits(b);
        if (op < 4) {
            ee::Float value = op == 0 ? fa + fb : op == 1 ? fa - fb : op == 2 ? fa * fb : fa / fb;
            o.float_result = value.bits();
        } else {
            int32_t value = 0;
            switch (op) {
            case 4: value = truth(a) || truth(o.float_below); break;
            case 5: value = truth(a) && truth(o.float_below); break;
            case 6: value = equal(a, b); break;
            case 7: value = !equal(a, b); break;
            case 8: value = less(a, b); break;
            case 9: value = less(b, a); break;
            case 10: value = lessEqual(a, b); break;
            case 11: value = lessEqual(b, a); break;
            }
            o.int_result = value;
            scrPushInt(work, o.int_result);
            return;
        }
    }
    scrPushFloat(work, o.float_result);
}

// ---- the opcodes (the functions of the opcode table, 0x2FA528) ----
// Each returns 0 to end the procedure, 1 to go on, 2 to wait for the next frame.

namespace {

// scrCodeFunc_PushI @ 0x0010A540: the next word.
int32_t opPushInt(ProcessWork& w)
{
    ++w.CP;
    scrPushInt(w, word(w, w.CP).i());
    return advance(w);
}

// scrCodeFunc_PushIS @ 0x0010A590: the operand.
int32_t opPushShort(ProcessWork& w)
{
    scrPushInt(w, operand(w));
    return advance(w);
}

// scrCodeFunc_PushF @ 0x0010A5D8
int32_t opPushFloat(ProcessWork& w)
{
    ++w.CP;
    scrPushFloat(w, word(w, w.CP).bits());
    return advance(w);
}

// scrCodeFunc_PushIX @ 0x0010A628: a global variable.
int32_t opPushIntVar(ProcessWork& w)
{
    scrPushInt(w, globalInt(static_cast<uint32_t>(operand(w))));
    return advance(w);
}

// scrCodeFunc_PushFX @ 0x0010A680
int32_t opPushFloatVar(ProcessWork& w)
{
    scrPushFloat(w, globalFloat(static_cast<uint32_t>(operand(w))));
    return advance(w);
}

// scrCodeFunc_PushLIX @ 0x0010A6D8: a local.
int32_t opPushLocalIntVar(ProcessWork& w)
{
    scrPushInt(w, w.LocalInt[operand(w)]);
    return advance(w);
}

// scrCodeFunc_PushLFX @ 0x0010A730
int32_t opPushLocalFloatVar(ProcessWork& w)
{
    scrPushFloat(w, w.LocalFloat[operand(w)]);
    return advance(w);
}

// scrCodeFunc_PushSTR @ 0x0010A788: an address in the strings.
int32_t opPushString(ProcessWork& w)
{
    scrPushStr(w, w.StringData + static_cast<uint32_t>(static_cast<int32_t>(operand(w))));
    return advance(w);
}

// scrCodeFunc_PushReg @ 0x0010A7D8: the last command's result.
int32_t opPushResult(ProcessWork& w)
{
    w.StackType[w.SP] = w.StackType[kRegister];
    w.StackData[w.SP] = w.StackData[kRegister];
    ++w.SP;
    return advance(w);
}

// scrCodeFunc_PopIX @ 0x0010A820
int32_t opPopIntVar(ProcessWork& w)
{
    const int32_t value = scrPopInt(w);
    globalInt(static_cast<uint32_t>(operand(w))) = value;
    return advance(w);
}

// scrCodeFunc_PopFX @ 0x0010A878
int32_t opPopFloatVar(ProcessWork& w)
{
    const uint32_t value = scrPopFloat(w);
    const int16_t index = operand(w);
    ++w.CP;
    globalFloat(static_cast<uint32_t>(index)) = value;
    return 1;
}

// scrCodeFunc_PopLIX @ 0x0010A8D0
int32_t opPopLocalIntVar(ProcessWork& w)
{
    const int32_t value = scrPopInt(w);
    w.LocalInt[operand(w)] = value;
    return advance(w);
}

// scrCodeFunc_PopLFX @ 0x0010A928
int32_t opPopLocalFloatVar(ProcessWork& w)
{
    const uint32_t value = scrPopFloat(w);
    const int16_t index = operand(w);
    ++w.CP;
    w.LocalFloat[index] = value;
    return 1;
}

// scrCodeFunc_Proc @ 0x0010A980: a procedure's start marker.
int32_t opProcedure(ProcessWork& w) { return advance(w); }

// scrCodeFunc_Comm @ 0x0010A998: a command, with its arguments on the stack.
// A command that isn't done returns 0 and runs again next frame; one that
// set the code pointer (SEL_JMP) isn't moved past.
int32_t opCommand(ProcessWork& w)
{
    const int32_t cp = w.CP;
    const CommandEntry& command = guest::table<CommandEntry>(kCommands)[word(w, cp).s1];
    guest::table<Ptr32<ProcessWork>>(kCurrent)->address = addressOf(&w);
    if (!CallCommand(command.comm))
        return 2;
    w.SP -= command.paranum;
    if (w.CP == cp)
        ++w.CP;
    return 1;
}

// scrCodeFunc_End @ 0x0010AA38: back to the caller, or the procedure's end.
int32_t opEnd(ProcessWork& w)
{
    if (!w.SP)
        return 0;
    w.CP = scrPopInt(w) + 1;
    return 1;
}

// scrCodeFunc_Jump @ 0x0010AA78
int32_t opJump(ProcessWork& w)
{
    w.CP = procedureAddress(w, operand(w));
    return 1;
}

// scrCodeFunc_Call @ 0x0010AAA8
int32_t opCall(ProcessWork& w)
{
    scrPushRet(w, w.CP);
    w.CP = procedureAddress(w, operand(w));
    return 1;
}

// scrCodeFunc_Run @ 0x0010AB00 (does nothing)
int32_t opRun(ProcessWork& w) { return advance(w); }

// scrCodeFunc_Goto @ 0x0010AB18
int32_t opGoto(ProcessWork& w)
{
    w.CP = labelAddress(w, operand(w));
    return 1;
}

int32_t binary(ProcessWork& w, int32_t op)
{
    TwoOperation(w, op);
    return advance(w);
}

// scrCodeFunc_Add @ 0x0010B030
int32_t opAdd(ProcessWork& w) { return binary(w, 0); }
// scrCodeFunc_Sub @ 0x0010B068
int32_t opSubtract(ProcessWork& w) { return binary(w, 1); }
// scrCodeFunc_Mul @ 0x0010B0A0
int32_t opMultiply(ProcessWork& w) { return binary(w, 2); }
// scrCodeFunc_Div @ 0x0010B0D8
int32_t opDivide(ProcessWork& w) { return binary(w, 3); }
// scrCodeFunc_Or @ 0x0010B2A0
int32_t opOr(ProcessWork& w) { return binary(w, 4); }
// scrCodeFunc_And @ 0x0010B2D8
int32_t opAnd(ProcessWork& w) { return binary(w, 5); }
// scrCodeFunc_EQ @ 0x0010B310
int32_t opEqual(ProcessWork& w) { return binary(w, 6); }
// scrCodeFunc_NEQ @ 0x0010B348
int32_t opNotEqual(ProcessWork& w) { return binary(w, 7); }
// scrCodeFunc_S @ 0x0010B380: smaller
int32_t opLess(ProcessWork& w) { return binary(w, 8); }
// scrCodeFunc_L @ 0x0010B3B8: larger
int32_t opGreater(ProcessWork& w) { return binary(w, 9); }
// scrCodeFunc_SE @ 0x0010B3F0
int32_t opLessEqual(ProcessWork& w) { return binary(w, 10); }
// scrCodeFunc_LE @ 0x0010B428
int32_t opGreaterEqual(ProcessWork& w) { return binary(w, 11); }

// scrCodeFunc_Minus @ 0x0010B110: negates the top entry (a variable in place).
int32_t opNegate(ProcessWork& w)
{
    const uint8_t type = w.StackType[w.SP - 1];
    if (type < kReturn) {
        uint32_t* slot = &w.StackData[w.SP - 1];
        if (type == kGlobalInt)
            slot = reinterpret_cast<uint32_t*>(&globalInt(*slot));
        else if (type == kGlobalFloat)
            slot = &globalFloat(*slot);
        *slot = (type & 1) ? *slot ^ 0x80000000u : 0u - *slot;
    }
    return advance(w);
}

// scrCodeFunc_Not @ 0x0010B1F8 (nothing popped for a string or return address)
int32_t opNot(ProcessWork& w)
{
    const uint8_t type = w.StackType[w.SP - 1];
    if (isInt(type))
        scrPushInt(w, scrPopInt(w) == 0);
    else if (isFloat(type))
        scrPushInt(w, equal(scrPopFloat(w), 0));
    return advance(w);
}

// scrCodeFunc_If @ 0x0010B460: on to the label unless true.
int32_t opIf(ProcessWork& w)
{
    const uint8_t type = w.StackType[w.SP - 1];
    bool taken = false;
    if (isInt(type))
        taken = scrPopInt(w) != 0;
    else if (isFloat(type))
        taken = !equal(scrPopFloat(w), 0);
    if (taken)
        ++w.CP;
    else
        w.CP = labelAddress(w, operand(w));
    return 1;
}

using Handler = int32_t (*)(ProcessWork&);
constexpr Handler kOpcodes[] = {
    opPushInt, opPushFloat, opPushIntVar, opPushFloatVar, opPushResult,
    opPopIntVar, opPopFloatVar, opProcedure, opCommand, opEnd,
    opJump, opCall, opRun, opGoto, opAdd,
    opSubtract, opMultiply, opDivide, opNegate, opNot,
    opOr, opAnd, opEqual, opNotEqual, opLess,
    opGreater, opLessEqual, opGreaterEqual, opIf, opPushShort,
    opPushLocalIntVar, opPushLocalFloatVar, opPopLocalIntVar, opPopLocalFloatVar, opPushString,
};
static_assert(std::size(kOpcodes) == PUSHSTR + 1);

} // namespace

// One code word through the opcode table.
int32_t Execute(ProcessWork& w, Opcode op) { return kOpcodes[op](w); }

// ---- for commands ---------------------------------------------------------------------------

namespace {

// Argument `index` of the running COMM (0 is the first), counting down from the top.
uint8_t argumentType(ProcessWork& w, int32_t index) { return w.StackType[w.SP - index - 1]; }
uint32_t argumentData(ProcessWork& w, int32_t index) { return w.StackData[w.SP - index - 1]; }

} // namespace

// scrGetIntPara @ 0x0010B5C8
int32_t scrGetIntPara(int32_t index)
{
    ProcessWork& w = *current();
    const uint8_t type = argumentType(w, index);
    return type > kReturn ? 0 : asInt(type, argumentData(w, index));
}

// scrGetFloatPara @ 0x0010B690
uint32_t scrGetFloatPara(int32_t index)
{
    ProcessWork& w = *current();
    const uint8_t type = argumentType(w, index);
    if (type > kReturn)
        return 0;
    return type == kReturn ? asFloat(kInt, argumentData(w, index)) : asFloat(type, argumentData(w, index));
}

// scrGetStrPara @ 0x0010B748 (0 unless a string)
uint32_t scrGetStrPara(int32_t index)
{
    ProcessWork& w = *current();
    return argumentType(w, index) == kString ? argumentData(w, index) : 0;
}

// scrSetIntReturnValue @ 0x0010B790
void scrSetIntReturnValue(int32_t value)
{
    ProcessWork& w = *current();
    w.StackType[kRegister] = kInt;
    w.StackData[kRegister] = static_cast<uint32_t>(value);
}

// scrGetLabelCodeAddress @ 0x0010B7D8
int32_t scrGetLabelCodeAddress(int32_t label) { return labelAddress(*current(), label); }

// scrSetCodePointer @ 0x0010B800
void scrSetCodePointer(int32_t cp) { current()->CP = cp; }

// scrGetCommandTimer @ 0x0010B820
int32_t scrGetCommandTimer() { return current()->CommandTimer; }

// scrGetMessageHandle @ 0x0010B830
int32_t scrGetMessageHandle() { return current()->MesHandle; }

// scrGetScriptHandle @ 0x0010B840
ProcessWork* scrGetScriptHandle() { return current(); }

// scrGetData @ 0x0010B848
uint32_t scrGetData() { return current()->data; }

// SDF_ABORT1 @ 0x0010B858
// Whether the player asks to skip a waiting command: it has waited a frame
// and the pad's button 1 was just pressed (DDS3_PADCHECK_TRIG).
bool SDF_ABORT1() { return scrGetCommandTimer() != 0 && guest::table<int8_t>(addr(0x005298c8))[1] < 0; }

} // namespace nocturne::scr

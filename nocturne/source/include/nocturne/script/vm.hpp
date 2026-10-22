// The FlowScript virtual machine (original units: ScrScriptProcess,
// ScrTraceCode, scrCommonCommand): runs the compiled scripts of
// docs/flowscript.md, one process per running procedure.
//
// Records are in their PS2 layout; field names are the HD remaster's.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/guest.hpp"

namespace nocturne::scr {

// scrHeader_t: the 0x20-byte header of a .bf file.
struct Header {
    uint8_t FileType;
    uint8_t FileFormat;
    uint16_t UserID;
    int32_t FileSize;
    char MagicCode[4];           // "FLW0"
    int32_t ExpandSize;
    int32_t TypeTableCount;      // sections
    int16_t LocalIntCount;
    int16_t LocalFloatCount;
    int32_t Reserve2;
    int32_t Reserve3;
};
static_assert(sizeof(Header) == 0x20 && offsetof(Header, LocalIntCount) == 0x14);

// SCR_DATATYPE: the kinds of section.
enum DataType : int32_t {
    kProcTable, kLabelTable, kScrData, kMessage, kStrings,
};

// scrTypeTable_t: a section descriptor.
struct TypeTable {
    int32_t Type;
    int32_t ItemSize;
    int32_t ItemCount;
    uint32_t ItemAddress;        // offset from the file start
};
static_assert(sizeof(TypeTable) == 0x10);

// scrProcTable_t / scrLabelTable_t: a procedure or a jump label.
struct ProcTable {
    char Name[24];
    int32_t CodeAddress;         // in 4-byte code words
    int32_t Reserve1;
};
static_assert(sizeof(ProcTable) == 0x20 && offsetof(ProcTable, CodeAddress) == 0x18);

// scrCode_t: a code word, {opcode, operand}; PUSHI / PUSHF take the next
// word as a whole.
struct Code {
    int16_t s0;                  // opcode
    int16_t s1;                  // operand
    uint32_t bits() const { return static_cast<uint16_t>(s0) | static_cast<uint32_t>(static_cast<uint16_t>(s1)) << 16; }
    int32_t i() const { return static_cast<int32_t>(bits()); }
};
static_assert(sizeof(Code) == 4);

// The opcodes (the table at 0x2FA528).
enum Opcode : int16_t {
    PUSHI, PUSHF, PUSHIX, PUSHFX, PUSHREG, POPIX, POPFX, PROC, COMM, END, JUMP, CALL, RUN, GOTO,
    ADD, SUB, MUL, DIV, MINUS, NOT, OR, AND, EQ, NEQ, S, L, SE, LE, IF,
    PUSHIS, PUSHLIX, PUSHLFX, POPLIX, POPLFX, PUSHSTR,
};

// The kind of each stack entry.
enum StackType : uint8_t {
    kInt,
    kFloat,
    kGlobalInt,                  // the value is a global variable's number
    kGlobalFloat,
    kReturn,                     // a return address (CALL), read as an int
    kString,                     // an address in the string section
};

constexpr int kStackSize = 28;
constexpr int kRegister = 27;    // the last slot is the return register (scrSetIntReturnValue)

// scrProcessWork_s: a running script (0xF4 bytes, from the pool).
struct ProcessWork {
    char Name[24];               // the procedure's
    int32_t CP;                  // code word
    int32_t SP;                  // stack entries
    uint8_t StackType[kStackSize];
    uint32_t StackData[kStackSize];
    Ptr32<Header> header;
    Ptr32<TypeTable> typeTable;
    Ptr32<ProcTable> procTable;
    Ptr32<ProcTable> labelTable;
    Ptr32<Code> code;
    uint32_t MessageData;
    uint32_t StringData;
    int32_t StartProc;
    int32_t MesHandle;           // its message window, or -1
    int32_t ScriptTimer;         // frames run
    int32_t CommandTimer;        // frames the current command has waited
    uint32_t MemHandle;          // the file, when the script loaded it
    Ptr32<int32_t> LocalInt;
    Ptr32<uint32_t> LocalFloat;  // float bits
    uint32_t ProcessID;
    Ptr32<ProcessWork> prev, next;
    uint32_t data;               // the owner's (scrSetUserData)
};
static_assert(offsetof(ProcessWork, StackData) == 0x3c && offsetof(ProcessWork, header) == 0xac);
static_assert(offsetof(ProcessWork, StartProc) == 0xc8 && offsetof(ProcessWork, LocalInt) == 0xdc);
static_assert(sizeof(ProcessWork) == 0xf4);

// The list of running scripts (0x54E994).
struct ScriptList {
    int32_t scrHandleCount;
    Ptr32<ProcessWork> scrHandleFirst;
    Ptr32<ProcessWork> scrHandleLast;
};

ScriptList& scriptList();
ProcessWork* current();

// Global script variables: 256 ints and 256 floats in the global work.
int32_t& globalInt(uint32_t index);
uint32_t& globalFloat(uint32_t index);

// ---- scripts and processes ----
void scrLinkScriptHandleList(ProcessWork& work);
void scrUnlinkScriptHandleList(ProcessWork& work);
ProcessWork* scrAddScript(uint32_t header, uint32_t typetable, uint32_t proctable, uint32_t labeltable, uint32_t code,
                          uint32_t mesdata, uint32_t stringdata, int64_t startproc);
ProcessWork* scrAddScriptFirst(uint32_t header, uint32_t typetable, uint32_t proctable, uint32_t labeltable, uint32_t code,
                               uint32_t mesdata, uint32_t stringdata);
ProcessWork* scrAddScript2(uint32_t data, int64_t startproc);
ProcessWork* scrAddScript3(uint32_t path, int64_t startproc);
uint32_t scrStartScriptProcess(int32_t priority, ProcessWork* work);
uint32_t scrStartScript1a(int32_t priority, uint32_t header, uint32_t typetable, uint32_t proctable, uint32_t labeltable,
                          uint32_t code, uint32_t mesdata, uint32_t stringdata, int64_t startproc);
uint32_t scrStartScript2(int32_t priority, uint32_t data, int64_t startproc);
uint32_t scrStartScript3(int32_t priority, uint32_t path, int64_t startproc);
void scrInitGlobalWork();
void scrReleaseScript(ProcessWork& work);
void scrAllReleaseScript();
ProcessWork* scrSearchScriptName(const char* name);
int32_t scrSearchProcedureName(uint32_t data, const char* name);
void scrSetUserData(uint32_t process, uint32_t data);
uint32_t scrGetUserData(uint32_t process);
void scrScriptShutdown(uint32_t process);
int32_t scrScriptProcess(uint32_t process);

// ---- running ----
int32_t scrTraceCode(ProcessWork& work);
int32_t Execute(ProcessWork& work, Opcode op);
void scrPushInt(ProcessWork& work, int32_t value);
void scrPushFloat(ProcessWork& work, uint32_t bits);
void scrPushStr(ProcessWork& work, uint32_t address);
void scrPushRet(ProcessWork& work, int32_t cp);
int32_t scrPopInt(ProcessWork& work);
uint32_t scrPopFloat(ProcessWork& work);
void TwoOperation(ProcessWork& work, int32_t op);

// ---- for commands: the arguments of the running COMM ----
int32_t scrGetIntPara(int32_t index);
uint32_t scrGetFloatPara(int32_t index);
uint32_t scrGetStrPara(int32_t index);
void scrSetIntReturnValue(int32_t value);
int32_t scrGetLabelCodeAddress(int32_t label);
void scrSetCodePointer(int32_t cp);
int32_t scrGetCommandTimer();
int32_t scrGetMessageHandle();
ProcessWork* scrGetScriptHandle();
uint32_t scrGetData();

// ---- commands ----
int32_t CallCommand(uint32_t entry);   // a command table entry's function
int32_t scrCommand_BIT_CHK();
int32_t scrCommand_BIT_ON();
int32_t scrCommand_BIT_OFF();
int32_t scrCommand_RND();
int32_t scrCommand_SYNC();
int32_t scrCommand_WAIT();
int32_t scrCommand_PUT();
int32_t scrCommand_PUTS();
int32_t scrCommand_FADE_IN();
int32_t scrCommand_FADE_OUT();
int32_t scrCommand_SEL_JMP();
int32_t scrCommand_PAD_TRIG();
int32_t scrCommand_PAD_PRESS();
int32_t scrCommand_SCR_RUN();
int32_t scrCommand_SCR_KILL();
int32_t scrCommand_SCR_WAIT();
int32_t scrCommand_SCR_STAT();
int32_t scrCommand_SCR_TIME();
int32_t scrCommand_QUAKE_ON();
int32_t scrCommand_QUAKE_OFF();

} // namespace nocturne::scr

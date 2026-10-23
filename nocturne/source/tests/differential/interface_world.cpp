#include "interface_world.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

#include "ee.hpp"
#include "nocturne/interface/message.hpp"

extern "C" {
uint64_t scrGetIntPara(uint64_t);
uint64_t ps2SoundPlay(uint64_t, uint64_t, uint64_t);
void dds3LinkProcess(uint64_t, uint64_t);
uint64_t nbRunAi(uint64_t);   // legacy (battle_ai_execution.c), tested against the rewrite
uint32_t ps2MemoryHandleAllocate(int32_t);
uint32_t ps2MemoryHandleAcquirePointer(uint32_t);
void ps2MemoryHandleFree(uint32_t);
void ps2PacRelocatePointers(uint64_t, uint64_t, uint64_t, uint64_t);
void nocturneInvokeMessageKutiCallback(uint32_t);
uint64_t ps2InterfaceLoadTexture(uint64_t);
void ps2TextureDeferredRelease(uint64_t);
uint64_t dds3StartProcess(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
uint32_t ps2PoolAllocate(int32_t);
uint64_t ps2TextureQueueUpload(uint64_t);
uint64_t ps2KernelGetFontContextIndex(void);
uint64_t sdfDevLoadFile(uint64_t, uint64_t, uint64_t);
uint32_t evtBitCheck(int32_t);
void evtBitOn(int32_t);
void evtBitOff(int32_t);
uint32_t sdfGetRandInt(uint32_t*, uint32_t);
float sdfGetRandFloat(uint32_t*);
uint64_t dds3KillProcess(uint64_t, uint64_t);
uint64_t dds3ExistProcess(uint64_t);
uint64_t ps2ProcessGetRunTime(uint64_t);
void dds3SetProcessData(uint64_t, uint64_t);
uint64_t dds3GetProcessData(uint64_t);
void dds3FadeIn(uint64_t, uint64_t, uint64_t, uint64_t);
void dds3PadAct(uint64_t, uint64_t, uint64_t);
uint64_t nbGetMainProcessData(void);
uint64_t nbGetUnitWorkPointer(uint64_t, uint64_t);
uint64_t nbGetPartyFromFormindex(uint64_t);
uint64_t nbGetUnitWorkFromFormindex(uint64_t);
uint64_t dds3SearchProcessName(uint64_t);
int32_t cmpRemoveDevilEx(uint16_t);
void effBTLDelete(uint64_t);
void dds3FadeOut(uint64_t, uint64_t, uint64_t, uint64_t);
void ps2PoolRelease(uint32_t);
}

namespace difftest::iface {

namespace {

namespace fr = nocturne::fr;
namespace mes = nocturne::mes;

constexpr uint32_t kKuti = 0x001d1640;   // ps2MessageKutiDiagnostic
constexpr uint32_t kFontOffset[4] = {0x00000, 0x18000, 0x2e000, 0x33000};

std::vector<std::vector<uint8_t>> gTables;
std::vector<uint8_t> gFonts[4];
std::vector<std::vector<uint8_t>> gScripts;

// The original code around the interface, the script VM and the data it
// changes; the commands read the script work at FW_SCRIPT (script_bridge.cpp).
ee::Interpreter makeOriginal()
{
    ee::Interpreter e;
    e.interpret(0x001c6018, 0x001cae58);   // the font engine (frFont)
    e.interpret(0x001cae58, 0x001caf88);   // itfMiscLink*
    e.interpret(0x001cd2e0, 0x001d1108);   // the message manager (itfMesManager)
    e.interpret(0x00158940, 0x00158948);   // an empty function (HD: the UI's open / close hook)
    e.interpret(0x001097e8, 0x0010d730);   // the script VM, scrCommonCommand and scrParameterCommand
    e.interpret(0x00104d38, 0x00104da0);   // dds3SetQuake, dds3StopQuake
    e.interpret(0x00105580, 0x001062e0);   // dds3KernelDraw: the camera, the screen blur and the event effects
    e.interpret(0x001070d0, 0x00107310);   // dds3SetLightColor, dds3SetLightDir
    e.interpret(0x00106ee0, 0x001070d0);   // dds3RotationArc
    e.interpret(0x002c04e8, 0x002c050c);   // ps2QuaternionNormalize
    e.interpret(0x00107310, 0x001074f0);   // dds3SetAmbientColor, dds3SetFogColor, dds3SetFogPara
    e.interpret(0x00107af0, 0x00107b40);   // dds3SetSoftenBias
    e.interpret(0x001ad230, 0x001ad5c8);
    e.interpret(0x00242a88, 0x002460b0);   // datCalc
    e.interpret(0x0025e8e0, 0x0025eaf0);   // nbKoukaProcess: the queue
    e.interpret(0x0025ee78, 0x0025efd0);
    e.interpret(0x00261500, 0x00264710);   // nbMakePacket
    e.interpret(0x00259a30, 0x00259a5c);   // nbGetUnitID
    e.interpret(0x00259ab0, 0x00259bd0);   // nbCheckEventDead, nbCheckDeadScript, nbCheckDeadEvent
    e.interpret(0x00267788, 0x002677b4);   // nbGetBadStat
    e.interpret(0x002514f0, 0x002518c8);   // nbActionProcess: the time list
    e.interpret(0x0026a7d0, 0x0026a824);   // nbGetDevilFormatFlag
    e.interpret(0x00253488, 0x00253490);   // SetAction_NON
    e.interpret(0x00253bf8, 0x00253de0);   // SetAction_AI .. CheckAction_DEADSCRIPT
    e.interpret(0x00288d80, 0x00288e18);   // nbInitAiScript
    e.interpret(0x00257b08, 0x00257bf0);   // SetAction_END
    e.interpret(0x00257460, 0x00257488);   // WAIT
    e.interpret(0x00257a68, 0x00257b08);   // CHECK3, ATO
    e.interpret(0x00257bf0, 0x00257c80);   // CheckAction_END, nbGetActionSeq, nbGetPrevActionSeq
    e.interpret(0x00257cc8, 0x00257cd0);   // SetNextActionSeq
    e.interpret(0x00223628, 0x00223668);   // cmpCalcLevelUpBaseExp
    e.interpret(0x00223668, 0x00223728);   // cmbCalcLevelUpExp
    e.interpret(0x00222160, 0x002221cc);   // cmbGetMasterHeartsNums
    e.interpret(0x00221f20, 0x002220c0);   // cmbChkMasterHeartsStatNums
    e.interpret(0x00221e70, 0x00221ef4);   // cmbGetPlayerRaceID
    e.interpret(0x00216b78, 0x00216b90);   // fclEncycGetNum
    e.interpret(0x00216b90, 0x00216bec);   // fclEncycGetRatio2
    e.interpret(0x00219df0, 0x00219fbc);   // fclEncyc_SetElem
    e.interpret(0x00216b20, 0x00216b78);   // ps2CompendiumRestore_00216B20
    e.interpret(0x00216a18, 0x00216b20);   // ps2CompendiumRecords_00216A18
    e.interpret(0x00221550, 0x00221558);   // ps2UnitMagatamaEquipHook_00221550
    e.interpret(0x00222408, 0x0022246c);   // ps2HeartsAddParam
    e.interpret(0x00240a98, 0x00240b48);   // ps2UnitRecalculateMaxHpMp_00240A98
    e.interpret(0x00221558, 0x00221560);   // ps2UnitMagatamaUnequipHook_00221558
    e.interpret(0x002222c0, 0x00222318);   // cmbGetHeartsDefaultParam
    e.interpret(0x00222318, 0x0022239c);   // cmbGetHeartsParamEx
    e.interpret(0x00222140, 0x0022215c);   // cmbChkHeartsMaster
    e.interpret(0x002223a0, 0x00222404);   // cmbGetHeartsParam
    e.interpret(0x00222470, 0x002224d4);   // cmbSubHeartsParam
    e.interpret(0x00222550, 0x00222610);   // cmbCreateDefaultHeartsSkill
    e.interpret(0x002328c8, 0x00232920);   // cmpChkHaveHearts
    e.interpret(0x00232880, 0x002328c8);   // cmpChkHaveNormalHeartsAll
    e.interpret(0x002138c0, 0x00213934);   // fclChkItemHearts   // effEvent: the event effects' switches and settings
    e.interpret(0x001caf78, 0x001caff4);   // itfMiscSetRatioRGB
    e.interpret(0x001cc080, 0x001cc2b8);   // itfPanel: registering, releasing, placing, colouring
    e.interpret(0x001cc358, 0x001cc9a0);   // itfPanel: the vertex and colour builders
    e.interpret(0x002d1550, 0x002d1d68);   // libgcc soft double
    e.interpret(0x002d3398, 0x002d3810);
    auto a = [](ee::Cpu& c, int i) { return c.arg(i); };
    auto none = [](auto) { return uint64_t{0}; };
    (void)none;
    e.hook(0x002c18d8, [=](ee::Cpu& c) { return ps2SoundPlay(a(c, 0), a(c, 1), a(c, 2)); });
    e.hook(0x00101af8, [=](ee::Cpu& c) { dds3LinkProcess(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x00287cb8, [=](ee::Cpu& c) { return nbRunAi(a(c, 0)); });
    e.hook(0x002a9038, [=](ee::Cpu& c) { return uint64_t{ps2MemoryHandleAllocate(static_cast<int32_t>(a(c, 0)))}; });
    e.hook(0x002a9688, [=](ee::Cpu& c) { return uint64_t{ps2MemoryHandleAcquirePointer(static_cast<uint32_t>(a(c, 0)))}; });
    e.hook(0x002a9558, [=](ee::Cpu& c) { ps2MemoryHandleFree(static_cast<uint32_t>(a(c, 0))); return uint64_t{0}; });
    e.hook(0x002c39c8, [=](ee::Cpu& c) { ps2PacRelocatePointers(a(c, 0), a(c, 1), a(c, 2), a(c, 3)); return uint64_t{0}; });
    e.hook(0x002d4748, [=](ee::Cpu& c) {
        int64_t args[5];
        for (int i = 0; i < 5; ++i)
            args[i] = static_cast<int64_t>(a(c, i + 1));
        fw_record_print(static_cast<uint32_t>(a(c, 0)), args);
        return uint64_t{0};
    });
    e.hook(0x001cb0d8, [=](ee::Cpu& c) { return ps2InterfaceLoadTexture(a(c, 0)); });
    e.hook(0x002ab8f0, [=](ee::Cpu& c) { ps2TextureDeferredRelease(a(c, 0)); return uint64_t{0}; });
    e.hook(0x001015b0, [=](ee::Cpu& c) { return dds3StartProcess(a(c, 0), a(c, 1), a(c, 2), a(c, 3), a(c, 4), a(c, 5), a(c, 6)); });
    e.hook(0x002a8af8, [=](ee::Cpu& c) { return uint64_t{ps2PoolAllocate(static_cast<int32_t>(a(c, 0)))}; });
    e.hook(0x002aa9e0, [=](ee::Cpu& c) { return ps2TextureQueueUpload(a(c, 0)); });
    e.hook(0x00100418, [](ee::Cpu&) { return ps2KernelGetFontContextIndex(); });
    e.hook(0x002c3718, [=](ee::Cpu& c) { return sdfDevLoadFile(a(c, 0), a(c, 1), a(c, 2)); });
    e.hook(0x001e0f50, [=](ee::Cpu& c) { return uint64_t{evtBitCheck(static_cast<int32_t>(a(c, 0)))}; });
    e.hook(0x001e0ed0, [=](ee::Cpu& c) { evtBitOn(static_cast<int32_t>(a(c, 0))); return uint64_t{0}; });
    e.hook(0x001e0f10, [=](ee::Cpu& c) { evtBitOff(static_cast<int32_t>(a(c, 0))); return uint64_t{0}; });
    e.hook(0x002c0c60, [=](ee::Cpu& c) { return uint64_t{sdfGetRandInt(nullptr, static_cast<uint32_t>(a(c, 1)))}; });
    e.hook(0x00101738, [=](ee::Cpu& c) { return dds3KillProcess(a(c, 0), a(c, 1)); });
    e.hook(0x00101a08, [=](ee::Cpu& c) { return dds3ExistProcess(a(c, 0)); });
    e.hook(0x00101aa0, [=](ee::Cpu& c) { return ps2ProcessGetRunTime(a(c, 0)); });
    e.hook(0x00101aa8, [=](ee::Cpu& c) { dds3SetProcessData(a(c, 0), a(c, 1)); return uint64_t{0}; });
    e.hook(0x00101ab0, [=](ee::Cpu& c) { return dds3GetProcessData(a(c, 0)); });
    e.hook(0x00104fe0, [=](ee::Cpu& c) { dds3FadeIn(a(c, 0), a(c, 1), a(c, 2), a(c, 3)); return uint64_t{0}; });
    e.hook(0x00105098, [=](ee::Cpu& c) { dds3FadeOut(a(c, 0), a(c, 1), a(c, 2), a(c, 3)); return uint64_t{0}; });
    e.hook(0x002c0c00, [](ee::Cpu& c) { c.f[0] = static_cast<uint32_t>(floatBits(sdfGetRandFloat(nullptr))); return uint64_t{0}; });
    e.hook(0x0016ab10, [=](ee::Cpu& c) { effBTLDelete(a(c, 0)); return uint64_t{0}; });
    e.hook(0x0022e168, [=](ee::Cpu& c) { return static_cast<uint64_t>(static_cast<int64_t>(cmpRemoveDevilEx(static_cast<uint16_t>(a(c, 0))))); });
    e.hook(0x002469a0, [](ee::Cpu&) { return nbGetMainProcessData(); });
    e.hook(0x002469c0, [=](ee::Cpu& c) { return nbGetUnitWorkPointer(a(c, 0), a(c, 1)); });
    e.hook(0x00246a40, [=](ee::Cpu& c) { return nbGetPartyFromFormindex(a(c, 0)); });
    e.hook(0x00246ab8, [=](ee::Cpu& c) { return nbGetUnitWorkFromFormindex(a(c, 0)); });
    e.hook(0x00101898, [=](ee::Cpu& c) { return dds3SearchProcessName(a(c, 0)); });
    e.hook(0x001040a8, [=](ee::Cpu& c) { dds3PadAct(a(c, 0), a(c, 1), a(c, 2)); return uint64_t{0}; });
    e.hook(0x002a8bd8, [=](ee::Cpu& c) { ps2PoolRelease(static_cast<uint32_t>(a(c, 0))); return uint64_t{0}; });
    // The C library: plain host versions on guest memory.
    auto checked = [](ee::Cpu& c, uint64_t address) -> char* {
        if (static_cast<uint32_t>(address) >= FW_RAM_SIZE) {
            std::fprintf(stderr, "C library call from %08x with address %08x\n", static_cast<uint32_t>(c.r[31]),
                         static_cast<uint32_t>(address));
            std::abort();
        }
        return &at<char>(static_cast<uint32_t>(address));
    };
    e.hook(0x002d5d0c, [=](ee::Cpu& c) { return uint64_t{std::strlen(checked(c, a(c, 0)))}; });
    e.hook(0x002d5ab4, [=](ee::Cpu& c) {   // strcmp: the difference of the first bytes that differ
        const unsigned char* x = reinterpret_cast<const unsigned char*>(checked(c, a(c, 0)));
        const unsigned char* y = reinterpret_cast<const unsigned char*>(checked(c, a(c, 1)));
        while (*x && *x == *y)
            ++x, ++y;
        return static_cast<uint64_t>(static_cast<int64_t>(*x - *y));
    });
    e.hook(0x002d43a4, [=](ee::Cpu& c) {
        std::memcpy(checked(c, a(c, 0)), checked(c, a(c, 1)), static_cast<uint32_t>(a(c, 2)));
        return a(c, 0);
    });
    e.hook(0x002d4558, [=](ee::Cpu& c) {
        std::memset(checked(c, a(c, 0)), static_cast<int>(a(c, 1)), static_cast<uint32_t>(a(c, 2)));
        return a(c, 0);
    });
    e.hook(0x002d5690, [=](ee::Cpu& c) {   // sprintf, as used here: "%d" only
        if (std::strcmp(checked(c, a(c, 1)), "%d") != 0)
            std::abort();
        return uint64_t(std::snprintf(checked(c, a(c, 0)), 16, "%d", static_cast<int32_t>(a(c, 2))));
    });
    e.hook(kKuti, [](ee::Cpu&) { nocturneInvokeMessageKutiCallback(kKuti); return uint64_t{0}; });
    return e;
}

ee::Interpreter& original()
{
    static ee::Interpreter e = makeOriginal();
    return e;
}

// The guest stack starts zeroed, as the rewrite's local buffers are: the
// original copies a few bytes past a string's end from its stack buffer.
uint64_t call(uint32_t entry, std::initializer_list<uint64_t> args, bool /*vm*/ = false,
              std::initializer_list<uint32_t> floatArgs = {})
{
    std::memset(fw_ram + FW_STACK_TOP - 0x2000, 0, 0x2000 + 0x40);
    return original().call(entry, args, floatArgs);
}

std::vector<uint8_t> readFile(const std::string& path)
{
    std::ifstream f(path, std::ios::binary);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

// The message section of a FlowScript (section type 3).
std::vector<uint8_t> scriptMessages(const std::vector<uint8_t>& script)
{
    if (script.size() < 0x20)
        return {};
    uint32_t count;
    std::memcpy(&count, script.data() + 0x10, 4);
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t s[4];
        std::memcpy(s, script.data() + 0x20 + 16 * i, 16);
        if (s[0] == 3)
            return std::vector<uint8_t>(script.begin() + s[3], script.begin() + s[3] + s[1] * s[2]);
    }
    return {};
}

uint32_t poolString(const char* s)
{
    uint32_t length = static_cast<uint32_t>(std::strlen(s)) + 1;
    uint32_t p = ps2PoolAllocate(static_cast<int32_t>(length));
    std::memcpy(fw_ram + p, s, length);
    return p;
}

} // namespace

uint32_t guestString(const char* s) { return poolString(s); }

uint64_t orig(uint32_t entry, std::initializer_list<uint64_t> args) { return norm(call(entry, args)); }
uint64_t origVm(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> floatArgs)
{
    return norm(call(entry, args, true, floatArgs));
}
uint64_t origVmVoid(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> floatArgs)
{
    call(entry, args, true, floatArgs);
    return 0;
}
uint32_t origVmFloat() { return original().cpu.f[0]; }
uint64_t origVoid(uint32_t entry, std::initializer_list<uint64_t> args) { call(entry, args); return 0; }

const std::vector<std::vector<uint8_t>>& messageTables() { return gTables; }
const std::vector<std::vector<uint8_t>>& scriptFiles() { return gScripts; }

void loadData(const char* elfPath)
{
    std::string root(elfPath);
    root = root.substr(0, root.find_last_of("/\\") + 1) + "dds3/";
    for (const char* name : {"event/e600/e601/scr/e601.bf", "facility/scr/combine/message.bf", "event/e600/e602/scr/e602.bf",
                             "fld/f/f015/f015.bf", "fld/f/f041/f041.bf"}) {
        std::vector<uint8_t> table = scriptMessages(readFile(root + name));
        if (!table.empty() && table.size() <= 0x10000)
            gTables.push_back(std::move(table));
    }
    for (int i = 0; i < 4; ++i)
        gFonts[i] = readFile(root + "font/EngFont/font" + std::to_string(i) + ".fnt");
    for (const char* name : {"event/e600/e601/scr/e601.bf", "event/e600/e602/scr/e602.bf", "facility/scr/combine/message.bf"})
        gScripts.push_back(readFile(root + name));
    if (gTables.empty() || gFonts[0].empty())
        std::fprintf(stderr, "no message tables or fonts under %s; interface tests will fail\n", root.c_str());
}

void loadTable(Gen& g, bool relocate)
{
    const std::vector<uint8_t>& t = gTables[g.below(static_cast<uint32_t>(gTables.size()))];
    std::memset(fw_ram + FW_MES_TABLE, 0, 0x10000);
    std::memcpy(fw_ram + FW_MES_TABLE, t.data(), t.size());
    if (relocate) {
        mes::FileHeader& f = at<mes::FileHeader>(FW_MES_TABLE);
        ps2PacRelocatePointers(FW_MES_TABLE + 0x20, FW_MES_TABLE + 0x20, FW_MES_TABLE + f.ofs_addrinfo, f.size_addrinfo);
        f.resolveaddress = 1;
    }
}

void fontWorld(Gen& g)
{
    // Fonts: style 1 shares style 0's file (as frLoadStyle does).
    for (int i = 0; i < 4; ++i)
        std::memcpy(fw_ram + FW_FONTS + kFontOffset[i], gFonts[i].data(), gFonts[i].size());
    std::memset(&fr::style(0), 0, 9 * sizeof(fr::Style));
    fr::BindStyle(0, 0, FW_FONTS + 1);
    fr::BindStyle(1, 0, FW_FONTS + 1);
    fr::BindStyle(2, 0, FW_FONTS + kFontOffset[2] + 1);
    fr::BindStyle(3, 0, FW_FONTS + kFontOffset[3] + 1);
    if (g.chance(40))
        fr::BindStyle(8, FW_FONTS + kFontOffset[1], 0);
    for (int i = 0; i < 9; ++i)
        at<int32_t>(0x003261e8 + 4u * static_cast<uint32_t>(i)) = i < 4 && g.chance(80) ? 1 : 0;

    fr::Settings& s = fr::settings();
    s.result = g.chance(50) ? g.below(8) : 0xffffffffu;
    s.space = static_cast<int8_t>(g.pick<int32_t>({3, 3, 0, 1, 2, -1}));
    s.step = g.chance(70) ? 0x14 : g.range(12, 28);
    s.base_width = g.chance(70) ? 0x14 : g.range(14, 24);
    s.space_width = g.range(0, 4);
    s.mode = static_cast<uint8_t>(g.chance(50) ? 0x16 : g.below(32));
    s.style = static_cast<uint8_t>(g.below(4));
    at<uint8_t>(0x0054f430) = 0;                     // the empty string

    // Pools and counters (0x56BB74).
    std::memset(fw_ram + 0x0056bb74, 0, 0x0056bbc4 - 0x0056bb74);
    at<uint32_t>(0x0056bb80) = fw_address_of(fr::PoolCreate(0x2c, 2000));
    at<uint32_t>(0x0056bb84) = fw_address_of(fr::PoolCreate(0x30, 400));
    at<int32_t>(0x0056bb90) = 0x200;
    at<int32_t>(0x0056bba0) = 0x1a40 + static_cast<int32_t>(g.below(4));

    // Texture cells: a ring of 400 behind the anchor (cell 0), each with a glyph record.
    constexpr uint32_t kCells = 400;
    const uint32_t cells = ps2PoolAllocate((kCells + 1) * 0x20), glyphs = ps2PoolAllocate((kCells + 1) * 12);
    std::memset(fw_ram + cells, 0, (kCells + 1) * 0x20);
    std::memset(fw_ram + glyphs, 0, (kCells + 1) * 12);
    for (uint32_t k = 0; k <= kCells; ++k) {
        fr::TextureCell& c = at<fr::TextureCell>(cells + 0x20 * k);
        c.index = static_cast<int32_t>(k);
        c.x = static_cast<int32_t>(k % 21) * 24 * 16;
        c.y = static_cast<int32_t>(k / 21) * 24 * 16;
        c.x2 = c.x + 24 * 16;
        c.glyph.address = glyphs + 12 * k;
        c.next.address = cells + 0x20 * (k == kCells ? 0 : k + 1);
        c.prev.address = cells + 0x20 * (k == 0 ? kCells : k - 1);
    }
    fr::TextureCells& tc = at<fr::TextureCells>(0x0056b668);
    std::memset(&tc, 0, sizeof tc);
    tc.free = kCells;
    tc.ring.address = cells;
    tc.count = kCells + 1;

    at<uint32_t>(0x0056bbc4) = 0;
    at<uint32_t>(0x0056bbc8) = 0;
    at<int32_t>(0x00551b80) = static_cast<int32_t>(g.below(2));
    at<uint16_t>(0x0054ea00) = static_cast<uint16_t>(g.chance(50) ? 'A' + g.below(26) : 0x8020 + g.below(0x40));

    // {var n} strings.
    static const char* const strings[] = {"123", "Pixie", "B2F", "Jack Frost", "\x81\x40\x81\x41", "R"};
    for (uint32_t i = 0; i < 32; ++i)
        at<uint32_t>(0x0056bbd0 + 4 * i) = g.chance(50) ? poolString(strings[g.below(6)]) : 0;

    // Entered names (save data at FW_GLOBAL): letter codes, bitmaps and lengths.
    at<uint32_t>(0x0054ea20) = FW_GLOBAL;
    for (uint32_t bank = 0; bank < 4; ++bank) {
        const uint32_t family = g.range(1, 6), given = g.range(1, 6);   // entered names have letters
        fw_ram[FW_GLOBAL + 0x657c + 2 * bank] = static_cast<uint8_t>(family);
        fw_ram[FW_GLOBAL + 0x657d + 2 * bank] = static_cast<uint8_t>(given);
        for (uint32_t k = 0; k < 16; ++k) {
            fw_ram[FW_GLOBAL + 0x6584 + 32 * bank + 2 * k] = 0;
            fw_ram[FW_GLOBAL + 0x6585 + 32 * bank + 2 * k] = static_cast<uint8_t>('A' + g.below(26));
        }
        for (uint32_t k = 0; k < 0x1200; k += 4)
            at<uint32_t>(FW_GLOBAL + 0x1d7c + bank * 0x1200 + k) = static_cast<uint32_t>(g.rng());
        for (uint32_t k = 0; k < 10; ++k) {
            fw_ram[FW_GLOBAL + 0x6604 + 20 * bank + 2 * k] = 0;
            fw_ram[FW_GLOBAL + 0x6605 + 20 * bank + 2 * k] = static_cast<uint8_t>('a' + g.below(26));
        }
        fw_ram[FW_GLOBAL + 0x6654 + bank] = static_cast<uint8_t>(g.range(0, 10));
        at<int32_t>(0x0056bd50 + 4 * bank) = 0;
    }
    std::memset(fw_ram + 0x0056bc50, 0, 0x100);
}

uint32_t someText(Gen& g)
{
    const mes::FileHeader& f = at<mes::FileHeader>(FW_MES_TABLE);
    if (f.resolveaddress && f.numtypeheader && g.chance(80)) {
        for (int attempt = 0; attempt < 8; ++attempt) {
            const mes::TypeHeader& h = at<mes::TypeHeader>(FW_MES_TABLE + 0x20 + 8 * g.below(f.numtypeheader));
            if (h.type == 0) {
                const mes::MesHeader& m = at<mes::MesHeader>(h.ptr);
                if (m.page > 0)
                    return m.addr[g.below(static_cast<uint32_t>(m.page))];
            }
        }
    }
    static const char* const pages[] = {
        "\xF2\x08\xFF\xFF\xF2\x07\x07\xFFHello there.\nHow are you?\n\xF1\x04",
        "\xF2\x08\xFF\xFF\xF1\x12I see... \xF2\x0B\x01\xFF \xF2\x0C\x01\xFF!\n\xF1\x04",
        "\xF2\x08\xFF\xFF\xF2\x02\x05\xFF\xF2\x03\x02\xFF\xF2\x02\x01\xFF Macca\n\xF1\x10",
        "\xF2\x08\xFF\xFF\xF2\x0A\x01\xFF and \xF2\x0D\x02\xFF\xF1\x0F...^\xF1\x13x",
        "Line one\nLine two\nLine three",
    };
    return poolString(pages[g.below(5)]);
}

fr::Request* chain(Gen& g, int32_t x, int32_t y)
{
    return fr::MessageRequest(x, y, static_cast<uint8_t>(g.below(4)), static_cast<uint8_t>(g.below(6)),
                              static_cast<uint8_t>(g.below(3)), static_cast<uint8_t>(g.below(140)), someText(g), nullptr);
}

} // namespace difftest::iface

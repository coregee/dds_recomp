/* Fakes for everything the battle calculations call. See fake_world.h. */
#include "fake_world.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nocturne.h"
#include "battle_action_status.h"
#include "battle_affinity.h"
#include "battle_support_access.h"
#include "battle_targeting.h"
#include "battle_work_access.h"
#include "compiler_numeric.h"
#include "ee_fpu.h"
#include "libc_printf.h"
#include "script_compare.h"
#include "unit_progression.h"
#include "battle_power.h"
#include "battle_effects.h"
#include "combat_calculation.h"
#include "exp.h"
#include "hearts_menu.h"
#include "inheritance_queries.h"
#include "rst_rng_frontier.h"
#include "stat_neighbors.h"
#include "unit_batch.h"
#include "unit_neighbors.h"
#include "battle_ai_conditions.h"

uint8_t *fw_ram;
fw_trace fw_current_trace;
void *fw_trap_target;

static uint64_t case_seed;
static int case_normal;
static uint32_t case_moon;
static uint32_t rng_state;

/* ---- guest memory ------------------------------------------------------ */

void *fw_resolve(uint32_t address)
{
    if (address >= FW_RAM_SIZE) {
        fprintf(stderr, "fake world: address %08x out of range\n", address);
        abort();
    }
    return fw_ram + address;
}

uint32_t fw_address_of(const void *pointer)
{
    return (uint32_t)((const uint8_t *)pointer - fw_ram);
}

void *nocturneResolveCombatCalculationAddress(uint32_t address) { return fw_resolve(address); }

static uint32_t r32(uint32_t a) { uint32_t v; memcpy(&v, fw_resolve(a), 4); return v; }

int fw_load_elf(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *elf = malloc((size_t)size);
    if (!elf || fread(elf, 1, (size_t)size, f) != (size_t)size) { fclose(f); return 0; }
    fclose(f);

    fw_ram = calloc(1, FW_RAM_SIZE);
    g_datGlobalWork = (datGlobalWork_PS2 *)(fw_ram + FW_GLOBAL);
    g_datDevilSkillTable = (const datDevilSkillRecord_PS2 *)(fw_ram + 0x3497c0);
    g_cmbExpConstants = (const cmbExpConstants_PS2 *)(fw_ram + 0x54e434);
    g_cmbHeartsRecords = (const cmbHeartsRecord_PS2 *)(fw_ram + 0x339e00);
    g_cmbEvoFlagRequirements = (const cmbEvoFlagRequirement_PS2 *)(fw_ram + 0x339640);
    g_cmbDarkDevilIds = (const uint16_t *)(fw_ram + 0x339ba8);
    g_cmbPowerUpSkills = (const cmbPowerUpSkill_PS2 *)(fw_ram + 0x339c20);
    g_cmbDemonSkillRows = (const cmbDemonSkillRow_PS2 *)(fw_ram + 0x333cf8);
    g_cmbInheritanceLevelRecords = (const cmbInheritanceLevelRecord_PS2 *)(fw_ram + 0x339658);
    g_cmbInheritanceSkillRecords = (const cmbInheritanceSkillRecord_PS2 *)(fw_ram + 0x3d6998);
    g_cmbInheritanceScoreBytes = fw_ram + 0x3399e8;
    g_cmpHeartsPositions = (const cmpHeartsPosition_PS2 *)(fw_ram + 0x345e58);
    g_fclItemHeartsTable = (const int8_t *)(fw_ram + 0x53d6e8);
    g_cmbHeartsSkillRows = (const cmbHeartsSkillRow_PS2 *)(fw_ram + 0x339e1a);
    uint32_t phoff; uint16_t phnum;
    memcpy(&phoff, elf + 0x1c, 4);
    memcpy(&phnum, elf + 0x2c, 2);
    for (uint16_t i = 0; i < phnum; ++i) {
        const uint8_t *ph = elf + phoff + 32u * i;
        uint32_t type, offset, vaddr, filesz;
        memcpy(&type, ph, 4); memcpy(&offset, ph + 4, 4);
        memcpy(&vaddr, ph + 8, 4); memcpy(&filesz, ph + 16, 4);
        if (type == 1 && vaddr + filesz <= FW_RAM_SIZE)
            memcpy(fw_ram + vaddr, elf + offset, filesz);
    }
    free(elf);
    return 1;
}

/* ---- case control ------------------------------------------------------ */

uint64_t fw_hash(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t x = case_seed ^ (a * 0x9e3779b97f4a7c15ull) ^ (b * 0xc2b2ae3d27d4eb4full) ^ (c * 0x165667b19e3779f9ull);
    x ^= x >> 30; x *= 0xbf58476d1ce4e5b9ull;
    x ^= x >> 27; x *= 0x94d049bb133111ebull;
    return x ^ (x >> 31);
}

void fw_begin_case(uint64_t seed, int normal_difficulty, uint32_t moon_age)
{
    case_seed = seed;
    case_normal = normal_difficulty;
    case_moon = moon_age;
    rng_state = (uint32_t)(seed * 2654435761u) | 1u;
    memset(&fw_current_trace, 0, sizeof fw_current_trace);
}

_Noreturn void fw_trap(uint32_t code)
{
    longjmp(*(jmp_buf *)fw_trap_target, (int)code);
}

_Noreturn void nocturneCompilerArithmeticTrap(uint32_t code) { fw_trap(code); }

/* ---- RNG and debug output --------------------------------------------- */

static uint32_t next_random(void)
{
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 17;
    rng_state ^= rng_state << 5;
    return rng_state;
}

static void record_rng(uint32_t limit, uint32_t value)
{
    fw_trace *t = &fw_current_trace;
    if (t->rng_count < FW_MAX_TRACE) {
        t->rng_limit[t->rng_count] = limit;
        t->rng_value[t->rng_count] = value;
    }
    t->rng_count++;
}

uint32_t sdfGetRandInt(uint32_t *state, uint32_t limit)
{
    (void)state;
    uint32_t value = limit ? next_random() % limit : 0;
    record_rng(limit, value);
    return value;
}

uint32_t sdfGetRand(uint32_t *state)
{
    (void)state;
    uint32_t value = next_random();
    record_rng(0xffffffffu, value);
    return value;
}

float sdfGetRandFloat(uint32_t *state)
{
    (void)state;
    uint32_t bits = next_random() >> 8;
    float value = (float)bits * (1.0f / 16777216.0f);
    uint32_t raw; memcpy(&raw, &value, 4);
    record_rng(0, raw);
    return value;
}

int fw_print_arg_count(uint32_t format)
{
    switch (format) {
    case 0x005449c0: return 3; /* critical */
    case 0x005449e0: case 0x005449f8: case 0x00544bf8:
    case 0x00544c10: case 0x00544de0: return 1;
    case 0x00544d70: return 5; /* first strike */
    case 0x00544da8: return 4; /* back attack */
    case 0x00544df0: return 2; /* consecutive */
    case 0x00551140: return 0; /* MISS */
    case 0x00544d00: case 0x00544d10: case 0x00544be8: return 1; /* %f ratios */
    case 0x00544d30: return 3; /* magic heal */
    case 0x00544b48: case 0x00544b68: case 0x00544b88: return 0;
    case 0x00543188: case 0x00543198: return 1; /* YAMI-B Lv / Exp */
    case 0x0053caf8: return 1;                  /* fusion accident */
    case 0x0053d7e8: return 0;                  /* compendium full */
    case 0x00545830: case 0x00545840: return 1; /* AI action / table */
    case 0x00535a80: return 0;                  /* itfMesMngRequestMessage() escape 1 */
    case 0x00535aa8: return 1;                  /* itfMesMngRequestSelect() - Invalid Type */
    case 0x005457d8: case 0x005457e8: case 0x00544170: return 0;
    case 0x00544ba8: return 4; /* ailment chance */
    default:
        fprintf(stderr, "fake world: unknown print format %08x\n", format);
        abort();
    }
}

void fw_record_print(uint32_t format, const int64_t *args)
{
    fw_trace *t = &fw_current_trace;
    if (t->print_count < FW_MAX_TRACE) {
        t->print_format[t->print_count] = format;
        for (int i = 0; i < 5; ++i) t->print_args[t->print_count][i] = args[i];
    }
    t->print_count++;
}

uint64_t ps2LibcPrintf(uint64_t format, ...)
{
    int64_t args[5] = {0};
    int count = fw_print_arg_count((uint32_t)format);
    va_list ap;
    va_start(ap, format);
    /* Arguments are 64-bit register images: sign-extended integers or
     * software-double bits. Both sides pass the same images. */
    for (int i = 0; i < count; ++i) args[i] = (int64_t)va_arg(ap, uint64_t);
    va_end(ap);
    fw_record_print((uint32_t)format, args);
    return 0;
}

/* ---- EE FPU comparison (C.cond.S), as tests/script_core_bindings.c ----- */

uint32_t EE_FPU_COMPARE_S(uint32_t a, uint32_t b, unsigned predicate)
{
    uint32_t am = (a & 0x7f800000u) ? a & 0x7fffffffu : 0;
    uint32_t bm = (b & 0x7f800000u) ? b & 0x7fffffffu : 0;
    int64_t av = a >> 31 ? -(int64_t)am : am, bv = b >> 31 ? -(int64_t)bm : bm;
    return predicate == 0 ? av == bv : predicate == 1 ? av < bv : predicate == 2 ? av <= bv : 0;
}

/* ---- the engine boundary ------------------------------------------------- */
/* Everything below the battle calculations runs as real code on both sides
 * (legacy C vs. rewrite). Only lookups into engine state, events, RNG and
 * output are faked here. */

datGlobalWork_PS2 *g_datGlobalWork;
const datDevilSkillRecord_PS2 *g_datDevilSkillTable;
const cmbExpConstants_PS2 *g_cmbExpConstants;
const cmbHeartsRecord_PS2 *g_cmbHeartsRecords;
const cmbEvoFlagRequirement_PS2 *g_cmbEvoFlagRequirements;
const uint16_t *g_cmbDarkDevilIds;
const cmbPowerUpSkill_PS2 *g_cmbPowerUpSkills;
const cmbDemonSkillRow_PS2 *g_cmbDemonSkillRows;
const cmbInheritanceLevelRecord_PS2 *g_cmbInheritanceLevelRecords;
const cmbInheritanceSkillRecord_PS2 *g_cmbInheritanceSkillRecords;
const uint8_t *g_cmbInheritanceScoreBytes;
const cmpHeartsPosition_PS2 *g_cmpHeartsPositions;
const int8_t *g_fclItemHeartsTable;
const cmbHeartsSkillRow_PS2 *g_cmbHeartsSkillRows;
const rstResourceWork_PS2 *g_rstResourceWork;      /* not reached */

_Noreturn void nocturne_break(uint32_t code) { fw_trap(code); }

uint64_t nbGetMainProcessData(void) { return FW_MAIN; }

uint64_t nbGetUnitWorkFromFormindex(uint64_t formindex)
{
    return formindex < 16 ? r32(FW_FORM_UNITS + (uint32_t)formindex * 4) : 0;
}

uint64_t nbGetPartyFromFormindex(uint64_t formindex)
{
    return formindex < 14 ? FW_PARTY + (uint32_t)formindex * 128 : 0;
}

uint64_t nbGetUnitWorkPointer(uint64_t main_data, uint64_t party)
{
    (void)main_data;
    return nbGetUnitWorkFromFormindex(((uint32_t)party - FW_PARTY) / 128);
}

int32_t datBossRashChk(int32_t eid) { return fw_hash(9, (uint64_t)eid, 0) % 5 == 0; }

uint32_t evtBitCheck(int32_t no)
{
    if (no == 0xaf2) return (uint32_t)case_normal;
    return fw_hash(11, (uint64_t)no, 0) % 2;
}

uint32_t evtGetAgeOfMoon(void) { return case_moon; }

/* Event bit writes are appended to a log in dynamic RAM, so the RAM
 * comparison checks which bits were set or cleared, in order. */
static void log_event(int32_t no, uint32_t on)
{
    uint32_t *log = (uint32_t *)fw_resolve(FW_LOG);
    uint32_t n = log[0]++;
    if (n < 63) log[1 + n] = ((uint32_t)no & 0x7fffffffu) | (on << 31);
}

void evtBitOn(int32_t no) { log_event(no, 1); }
void evtBitOff(int32_t no) { log_event(no, 0); }

/* A debug print compiled out of the shipped game. */
void ps2ScriptDiagnosticDisabled(uint64_t format, ...) { (void)format; }

/* ---- per-file address resolvers ----------------------------------------- */

void *nocturneResolveBattleActionStatusAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleAffinityAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleEffectsAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattlePowerAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleSupportAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleTargetingAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveUnitProgressionAddress(uint32_t a) { return fw_resolve(a); }

void *nocturneResolveQsortAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveFusionSortAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveFusionAccidentAddress(uint32_t a) { return fw_resolve(a); }
void nocturneQsortNoteCompare(uint32_t pc, uint64_t callback, uint64_t left, uint64_t right, uint64_t result)
{
    (void)pc; (void)callback; (void)left; (void)right; (void)result;
}

static _Noreturn void unreachable(const char *name);

/* ---- the battle AI's surroundings -------------------------------------- */

static uint32_t guest_sp_reserve(uint32_t bytes);
static void guest_sp_release(uint32_t bytes);

/* The process table: only the target-selection process exists. */
uint64_t dds3SearchProcessName(uint64_t name) { (void)name; return 1; }
uint64_t dds3GetProcessData(uint64_t process) { (void)process; return FW_TARSEL; }

uint32_t evtGetAgeOfMoon16(void) { return case_moon * 2u + (uint32_t)(fw_hash(13, 0, 0) & 1); }

/* A fake flowscript VM: the data word, integer parameters and a log of
 * returned values all live in dynamic RAM. */
uint64_t scrGetData(void) { return FW_ACTION; }
uint64_t scrGetIntPara(uint64_t index)
{
    int32_t value; memcpy(&value, fw_resolve(FW_SCRIPT + 4u * ((uint32_t)index & 7u)), 4);
    return (uint64_t)(int64_t)value;
}
void scrSetIntReturnValue(uint64_t value)
{
    uint32_t *log = (uint32_t *)fw_resolve(FW_SCRIPT + 0x20);
    uint32_t n = log[0]++;
    if (n < 15) log[1 + n] = (uint32_t)value;
}

/* Host buffers handed to legacy code as guest addresses: staged on the
 * guest stack and copied back. */
static void *local_buffer;
static uint32_t local_bytes, local_address;
uint32_t nocturneLibcStreamLocalAddress(void *buffer, uint32_t bytes)
{
    local_buffer = buffer;
    local_bytes = bytes;
    local_address = guest_sp_reserve(bytes);
    memcpy(fw_resolve(local_address), buffer, bytes);
    return local_address;
}
void nocturneLibcStreamEndLocal(void)
{
    memcpy(local_buffer, fw_resolve(local_address), local_bytes);
    guest_sp_release(local_bytes);
}

/* The condition table at 0x4F0788, by callback address. */
uint64_t nocturneInvokeBattleAiCondition(uint32_t entry, uint64_t context, uint64_t parameter)
{
    switch (entry) {
    case 0x2853d8: return nbAiChkMyHp(context, parameter);
    case 0x285438: return nbAiChkMyMp(context, parameter);
    case 0x285470: return nbAiChkFrHp(context, parameter);
    case 0x285578: return nbAiChkDmgCnt(context, parameter);
    case 0x2855d8: return nbAiChkChkCnt(context, parameter);
    case 0x285668: return nbAiChkFrCnt(context, parameter);
    case 0x2856f0: return nbAiChkEnCnt(context, parameter);
    case 0x285778: return nbAiChkMyBad(context, parameter);
    case 0x2857b0: return nbAiChkFrBad(context, parameter);
    case 0x285890: return nbAiChkEnBad(context, parameter);
    case 0x285970: return nbAiChkEnAllBad(context, parameter);
    case 0x285a70: return nbAiChkEnId(context, parameter);
    case 0x285b60: return nbAiChkFrId(context, parameter);
    case 0x285ec8: return nbAiChkEnHojo(context, parameter);
    case 0x285fa8: return nbAiChkFrHojo(context, parameter);
    case 0x286088: return nbAiChkEnHojoMax(context, parameter);
    case 0x286168: return nbAiChkFrHojoMax(context, parameter);
    case 0x286248: return nbAiChkBa(context, parameter);
    case 0x2862d0: return nbAiChkSensei(context, parameter);
    case 0x286358: return nbAiChkEnLight(context, parameter);
    case 0x286440: return nbAiChkEnDark(context, parameter);
    case 0x286530: return nbAiChkPow(context, parameter);
    case 0x286580: return nbAiChkPlv(context, parameter);
    case 0x2865b0: return nbAiChkPPartyLv(context, parameter);
    case 0x2865e8: return nbAiChkTurn(context, parameter);
    case 0x286600: return nbAiChkEnHamamHk(context, parameter);
    case 0x2866e8: return nbAiChkSkillNoMp(context, parameter);
    default: unreachable("AI condition callback");
    }
}

/* qsort's comparator dispatch for the compendium sorts. */
uint64_t ps2CompendiumRecords_00219C40(uint64_t p0, uint64_t p1);
uint64_t ps2CompendiumRecords_00219D00(uint64_t p0, uint64_t p1);
uint64_t nocturneCompendiumRecordsCompare(uint64_t target, uint64_t left, uint64_t right)
{
    if ((uint32_t)target == 0x00219c40u) return ps2CompendiumRecords_00219C40(left, right);
    if ((uint32_t)target == 0x00219d00u) return ps2CompendiumRecords_00219D00(left, right);
    unreachable("qsort comparator");
}

/* A guest stack for legacy scratch buffers; outside the compared RAM. */
static uint32_t guest_sp = FW_STACK_TOP;

void *nocturneResolveFusionCoreAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveCompendiumRecordsAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveCompendiumRestoreAddress(uint32_t a) { return fw_resolve(a); }
uint32_t nocturneCompendiumRecordsStackPointer(void) { return guest_sp; }
void nocturneCompendiumRecordsSetStackPointer(uint32_t address) { guest_sp = address; }
uint32_t nocturneCompendiumRestoreStackPointer(void) { return guest_sp; }
void nocturneCompendiumRestoreSetStackPointer(uint32_t address) { guest_sp = address; }
uint32_t nocturneFusionCoreStackPointer(void) { return guest_sp; }
void nocturneFusionCoreSetStackPointer(uint32_t address) { guest_sp = address; }
void nocturneFusionCoreFpuCondition(uint32_t condition) { (void)condition; }

static uint32_t guest_sp_reserve(uint32_t bytes) { guest_sp -= (bytes + 15u) & ~15u; return guest_sp; }
static void guest_sp_release(uint32_t bytes) { guest_sp += (bytes + 15u) & ~15u; }

uint32_t nocturneFusionSortScratchPush(uint32_t bytes)
{
    guest_sp -= (bytes + 15u) & ~15u;
    return guest_sp;
}

void nocturneFusionSortScratchPop(uint32_t address, uint32_t bytes)
{
    if (address != guest_sp) { fprintf(stderr, "fake world: scratch pop out of order\n"); abort(); }
    guest_sp += (bytes + 15u) & ~15u;
}

/* ---- not reached ---------------------------------------------------------- */
/* Called only by other functions in the same legacy files, never by the code
 * under test. Reaching one means the test drifted outside its scope. */

static _Noreturn void unreachable(const char *name)
{
    fprintf(stderr, "fake world: %s should not be reached\n", name);
    abort();
}

int32_t g_nbDebugEnabled;
void *ps2Memset(void *destination, int32_t value, uint32_t count) { return memset(destination, value, count); }
void *nocturneResolveBattleAiConditionsAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleAiActionsAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleAiFiltersAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleAiSelectionAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleAiEstimatesAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleAiExecutionAddress(uint32_t a) { return fw_resolve(a); }
int32_t nocturne_diagnostic_printf(const char *message) { (void)message; unreachable("nocturne_diagnostic_printf"); }

/* ---- the message manager's surroundings ----------------------------------
 *
 * Font requests, panels and memory blocks come from a bump pool in dynamic
 * RAM; calls with side effects outside the code under test are logged. The
 * small font helpers that only store a field are the original behaviour. */

static uint32_t rd32(uint32_t a) { uint32_t v; memcpy(&v, fw_resolve(a), 4); return v; }
static void wr32(uint32_t a, uint32_t v) { memcpy(fw_resolve(a), &v, 4); }

void fw_mes_log(uint32_t kind, uint32_t a, uint32_t b)
{
    uint32_t n = rd32(FW_MES_STATE + 4);
    wr32(FW_MES_STATE + 4, n + 1);
    if (n < 120) {
        wr32(FW_MES_STATE + 8 + 12 * n, kind);
        wr32(FW_MES_STATE + 12 + 12 * n, a);
        wr32(FW_MES_STATE + 16 + 12 * n, b);
    }
}

static uint32_t mes_alloc(uint32_t bytes)
{
    uint32_t at = rd32(FW_MES_STATE);
    if (at < FW_MES_POOL) at = FW_MES_POOL;
    if (at + bytes > FW_MES_POOL_END) fw_trap(98);
    wr32(FW_MES_STATE, (at + bytes + 15u) & ~15u);
    memset(fw_resolve(at), 0, bytes);
    return at;
}

uint64_t scrGetMessageHandle(void)
{
    int32_t id; memcpy(&id, fw_resolve(FW_SCRIPT + 0x60), 4);
    return (uint64_t)(int64_t)id;
}

/* A page of 1..3 lines, each of one or two requests of one to three
 * characters; appended to `font` when given (which is then returned). */
static uint64_t fake_font_request(uint64_t x, uint64_t y, uint64_t style, uint64_t color, uint64_t tp,
                                  uint64_t speed, uint64_t text, uint64_t font)
{
    uint64_t h = fw_hash(text & 0xffffffffu, x & 0xffffffffu, (y & 0xffffffffu) ^ (font << 7));
    uint32_t lines = 1u + (uint32_t)(h % 3u), first = 0, previous = 0;
    int16_t height = (int16_t)(16 + (h >> 8) % 8);
    if ((uint32_t)font) {
        previous = (uint32_t)font;
        while (rd32(previous + 0x24)) previous = rd32(previous + 0x24);
    }
    for (uint32_t line = 0; line < lines; ++line) {
        uint32_t parts = 1u + (uint32_t)((h >> (12 + line)) & 1u);
        for (uint32_t part = 0; part < parts; ++part) {
            uint32_t r = mes_alloc(0x30);
            uint8_t *q = fw_resolve(r);
            uint32_t sp = (uint32_t)(speed & 255u) * 2u;
            int32_t rx = (int32_t)x + (int32_t)(part * 0x200u), ry = (int32_t)y + (int32_t)line * height * 8;
            q[0] = (uint8_t)(sp > 128 ? 128 : sp);
            memcpy(q + 4, &rx, 4);
            memcpy(q + 8, &ry, 4);
            wr32(r + 0xc, 3u + (uint32_t)((h >> (3 * line + part)) % 20u));
            memcpy(q + 0x12, &height, 2);
            uint32_t characters = 1u + (uint32_t)((h >> (20 + 2 * line + part)) % 3u), t_prev = 0;
            for (uint32_t c = 0; c < characters; ++c) {
                uint32_t t = mes_alloc(0x2c);
                uint8_t *tq = fw_resolve(t);
                wr32(t + 0x10, 0x80808080u ^ (uint32_t)(h >> c));
                tq[0x14] = (uint8_t)color;
                tq[0x15] = (uint8_t)style;
                tq[0x16] = (uint8_t)(((h >> (40 + c)) & 3u) == 0 ? 1u : (uint32_t)tp);
                wr32(t + 0x24, t_prev);
                if (t_prev) wr32(t_prev + 0x28, t); else wr32(r + 0x1c, t);
                t_prev = t;
            }
            wr32(r + 0x20, t_prev);
            wr32(r + 0x18, characters);
            wr32(r + 0x2c, r);
            wr32(r + 0x28, previous);
            if (previous) wr32(previous + 0x24, r);
            if (!first) first = r;
            previous = r;
        }
    }
    wr32(0x54f404, (uint32_t)(h >> 50) & 7u);
    fw_mes_log(1, (uint32_t)text, first);
    return (uint32_t)font ? (uint64_t)(int64_t)(int32_t)(uint32_t)font : (uint64_t)(int64_t)(int32_t)first;
}

uint64_t ps2FontMessageRequest(uint64_t x, uint64_t y, uint64_t style, uint64_t color, uint64_t transparency,
                               uint64_t speed, uint64_t text, uint64_t font)
{
    return fake_font_request(x, y, style & 255, color & 255, transparency & 255, speed & 255, text, font);
}

uint64_t ps2BattleActionSkill_001C9108(uint64_t x, uint64_t y, uint64_t text, uint64_t font)
{
    return fake_font_request(x, y, 0, 0, 0, 0x80, text, font);
}

uint64_t frDestroyFontRequestAfter(uint64_t request) { fw_mes_log(2, (uint32_t)request, 0); return 0; }
void ps2FontBindMessageStyle(uint64_t data) { fw_mes_log(3, (uint32_t)data, 0); }
void frSetVariableRequest(uint64_t index, uint64_t value) { wr32(0x56bbd0u + ((uint32_t)index << 2), (uint32_t)value); }
void frSetDrawPosition(uint64_t font, uint64_t x, uint64_t y) { wr32((uint32_t)font + 8, (uint32_t)y); wr32((uint32_t)font + 4, (uint32_t)x); }
void frSetDrawSpeed(uint64_t font, uint64_t speed)
{
    uint32_t v = ((uint32_t)speed & 255u) * 2u;
    *(uint8_t *)fw_resolve((uint32_t)font) = (uint8_t)(v > 128 ? 128 : v);
}
uint64_t ps2FontTestGlobalFlags(uint64_t mask) { return (uint64_t)(int64_t)(int32_t)rd32(0x54f404) & mask; }

uint64_t itfPnlRegist2(uint64_t type, uint64_t texture)
{
    uint32_t p = mes_alloc(0x40);
    *(uint8_t *)fw_resolve(p + 0x30) = (uint8_t)type;
    fw_mes_log(4, (uint32_t)type, (uint32_t)texture);
    return p;
}
void itfPnlSetPosition(uint64_t panel, uint64_t x0, uint64_t y0, uint64_t x1, uint64_t y1, uint64_t z)
{
    uint32_t p = (uint32_t)panel;
    wr32(p + 0x10, (uint32_t)x0); wr32(p + 0x14, (uint32_t)y0); wr32(p + 0x18, (uint32_t)x1); wr32(p + 0x1c, (uint32_t)y1);
    wr32(p + 0xc, (uint32_t)z);
}
void itfPnlSetPositionOffset(uint64_t panel, uint64_t x0, uint64_t y0, uint64_t x1, uint64_t y1, uint64_t z)
{
    uint32_t p = (uint32_t)panel;
    wr32(p + 0x10, rd32(p + 0x10) + (uint32_t)x0); wr32(p + 0x14, rd32(p + 0x14) + (uint32_t)y0);
    wr32(p + 0x18, rd32(p + 0x18) + (uint32_t)x1); wr32(p + 0x1c, rd32(p + 0x1c) + (uint32_t)y1);
    wr32(p + 0xc, rd32(p + 0xc) + (uint32_t)z);
}
void itfPnlSetColor(uint64_t panel, uint64_t red, uint64_t green, uint64_t blue, uint64_t alpha)
{
    uint32_t p = (uint32_t)panel;
    wr32(p + 0x20, (uint32_t)red); wr32(p + 0x24, (uint32_t)green); wr32(p + 0x28, (uint32_t)blue); wr32(p + 0x2c, (uint32_t)alpha);
}
void itfPnlRelease(uint64_t panel) { fw_mes_log(5, (uint32_t)panel, 0); }
uint64_t ps2SoundPlay(uint64_t sound, uint64_t volume, uint64_t pan)
{
    fw_mes_log(6, (uint32_t)sound, (uint32_t)volume << 16 | ((uint32_t)pan & 0xffffu));
    return 0;
}
uint32_t ps2MemoryHandleAllocate(int32_t size)
{
    uint32_t p = mes_alloc((uint32_t)size);
    fw_mes_log(7, (uint32_t)size, p);
    return p + 1u;      /* a handle, not the address */
}
uint32_t ps2MemoryHandleAcquirePointer(uint32_t handle) { return handle - 1u; }
void ps2MemoryHandleFree(uint32_t handle) { fw_mes_log(8, handle, 0); }

/* The relocation table of a resource (docs/messages.md): positions of the
 * offsets to turn into addresses. */
void ps2PacRelocatePointers(uint64_t destination, uint64_t base, uint64_t table, uint64_t bytes)
{
    uint32_t position = 0, i = 0, d = (uint32_t)destination, t = (uint32_t)table, n = (uint32_t)bytes;
    while (i < n) {
        uint8_t b = *(uint8_t *)fw_resolve(t + i);
        uint32_t count = 1, step;
        if ((b & 1) == 0) { step = 2u * b; i += 1; }
        else if ((b & 7) == 7) { step = 4; count = (b >> 3) + 2u; i += 1; }
        else { uint32_t w = b | (uint32_t)*(uint8_t *)fw_resolve(t + i + 1) << 8; step = (w >> 2) * 4u; i += 2; }
        while (count--) {
            position += step;
            wr32(d + position, rd32(d + position) + (uint32_t)base);
        }
    }
}

void nocturneInvokeMessageKutiCallback(uint32_t entry) { fw_mes_log(9, entry, 0); }

uint64_t ps2InterfaceLoadTexture(uint64_t name) { fw_mes_log(10, (uint32_t)name, 0); return 0x00123450; }
void ps2TextureDeferredRelease(uint64_t texture) { fw_mes_log(11, (uint32_t)texture, 0); }
uint64_t dds3StartProcess(uint64_t name, uint64_t priority, uint64_t startdelay, uint64_t shutdowndelay,
                          uint64_t processfunc, uint64_t shutdownfunc, uint64_t data)
{
    fw_mes_log(12, (uint32_t)name, (uint32_t)priority ^ (uint32_t)startdelay << 16 ^ (uint32_t)shutdowndelay << 20);
    fw_mes_log(13, (uint32_t)processfunc, (uint32_t)shutdownfunc ^ (uint32_t)data);
    return 1;
}

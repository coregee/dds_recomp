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
uint64_t dds3GetProcessData(uint64_t process) { (void)process; unreachable("dds3GetProcessData"); }
uint64_t dds3SearchProcessName(uint64_t name) { (void)name; unreachable("dds3SearchProcessName"); }
void *ps2Memset(void *destination, int32_t value, uint32_t count) { return memset(destination, value, count); }
void *nocturneResolveBattleAiConditionsAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleAiEstimatesAddress(uint32_t a) { return fw_resolve(a); }
void *nocturneResolveBattleAiExecutionAddress(uint32_t a) { return fw_resolve(a); }
uint32_t evtGetAgeOfMoon16(void) { unreachable("evtGetAgeOfMoon16"); }
uint64_t nbGetSelectBit(uint64_t main) { (void)main; unreachable("nbGetSelectBit"); }
uint64_t nbSetAiTarget(uint64_t context, uint64_t selector, uint64_t parameter) { (void)context; (void)selector; (void)parameter; unreachable("nbSetAiTarget"); }
uint64_t nocturneInvokeBattleAiCondition(uint32_t entry, uint64_t context, uint64_t parameter) { (void)entry; (void)context; (void)parameter; unreachable("nocturneInvokeBattleAiCondition"); }
uint64_t scrGetData(void) { unreachable("scrGetData"); }
uint64_t scrGetIntPara(uint64_t index) { (void)index; unreachable("scrGetIntPara"); }
void nbSetNormalSkill0(uint64_t unit) { (void)unit; unreachable("nbSetNormalSkill0"); }
void scrSetIntReturnValue(uint64_t value) { (void)value; unreachable("scrSetIntReturnValue"); }
int32_t nocturne_diagnostic_printf(const char *message) { (void)message; unreachable("nocturne_diagnostic_printf"); }

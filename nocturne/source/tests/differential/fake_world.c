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

#ifdef _WIN32
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
/* Prints the host call stack (symbols need the /Zi build). */
static void print_backtrace(void)
{
    void *frames[24];
    HANDLE process = GetCurrentProcess();
    USHORT n = CaptureStackBackTrace(1, 24, frames, NULL);
    union { SYMBOL_INFO info; char bytes[sizeof(SYMBOL_INFO) + 256]; } symbol;
    SymInitialize(process, NULL, TRUE);
    for (USHORT i = 0; i < n; ++i) {
        DWORD64 displacement = 0;
        memset(&symbol, 0, sizeof symbol);
        symbol.info.SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol.info.MaxNameLen = 255;
        if (SymFromAddr(process, (DWORD64)(uintptr_t)frames[i], &displacement, &symbol.info))
            fprintf(stderr, "  %s+0x%llx\n", symbol.info.Name, (unsigned long long)displacement);
        else
            fprintf(stderr, "  %p\n", frames[i]);
    }
}
static LONG WINAPI crash_handler(EXCEPTION_POINTERS *e)
{
    fprintf(stderr, "host exception %08lx at %p\n", e->ExceptionRecord->ExceptionCode, e->ExceptionRecord->ExceptionAddress);
    print_backtrace();
    return EXCEPTION_EXECUTE_HANDLER;
}
static void install_crash_handler(void) { SetUnhandledExceptionFilter(crash_handler); }
#else
static void print_backtrace(void) {}
static void install_crash_handler(void) {}
#endif

void *fw_resolve(uint32_t address)
{
    if (address >= FW_RAM_SIZE) {
        fprintf(stderr, "fake world: address %08x out of range\n", address);
        print_backtrace();
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
    install_crash_handler();
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
    switch (fw_maniax_address(format)) {
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
    case 0x00545d40: return 2;                  /* ailment action weights */
    case 0x005440e8: return 0;                  /* AD-PCM playing */
    case 0x00546138: return 1;                  /* skill skill */
    case 0x00544030: case 0x00544048: case 0x00544058: return 1;   /* dead formindex, allframe, prev commind */
    case 0x00544020: return 0;                  /* returning */
    case 0x00543fb8: return 1;                  /* nego result */
    case 0x005439f8: return 1;                  /* item no */
    case 0x00543fa8: return 2;                  /* NEGO p, e */
    case 0x005437f8: return 2;                  /* hits, select */
    case 0x00543780: return 2;                  /* HP damage, healing */
    case 0x005437a0: return 2;                  /* MP damage, healing */
    case 0x005437c0: return 0;                  /* MISS!!! */
    case 0x00532f20: return 1;                  /* effBTL:Set Stat */
    case 0x00532f90: return 0;                  /* effBTL:InvokeForm == NULL */
    case 0x00544f10: return 0;                  /* msg end */
    case 0x005450e0: return 2;                  /* plv, elv */
    case 0x00544ff0: return 1;                  /* request */
    case 0x00545db0: return 1;                  /* event start */
    case 0x00545018: return 1;                  /* select */
    case 0x00545068: return 2;                  /* helper's skill: p, id */
    case 0x00545218: return 2;                  /* plv, elv (group 12) */
    case 0x005451f8: return 1;                  /* drain */
    case 0x00545208: return 1;                  /* pwork hp */
    case 0x00544e48: return 2;                  /* select info usemestype, mesno */
    case 0x00544e70: return 2;                  /* normal_mesno, jouken_mesno */
    case 0x00544518: return 0;                  /* cutcreate 3 */
    case 0x00543e10: return 2;                  /* mot, cut */
    case 0x00543e20: return 1;                  /* the skill's effect type */
    case 0x00543e38: return 2;                  /* cut3 mottime, endtime */
    case 0x00543e58: return 2;                  /* total damage HP, MP */
    case 0x00543e78: return 1;                  /* skill kouka end time */
    case 0x00543e98: return 1;                  /* skill kouka unlock time */
    case 0x00543eb8: return 0;                  /* Kereijyou Koukaga nai */
    case 0x00543ee8: return 1;                  /* press %f */
    case 0x00545bd0: return 1;                  /* MIDI=0x%08X */
    case 0x00545ce0: return 2;                  /* nbBgmStop(%d,%d) */
    case 0x00545ba0: return 2;                  /* encounter rate %d/%d */
    case 0x00545cf8: return 1;                  /* UNIT LOAD TIME = %d frame */
    case 0x00543d80: return 0;
    case 0x00543d70: return 0;
    case 0x00543d50: return 0;
    case 0x00543d40: return 1;
    case 0x00543d18: return 0;
    case 0x00543cf8: return 1;
    case 0x00543ce0: return 0;
    case 0x00543b78: return 2;
    case 0x00543b68: return 1;
    case 0x00543b58: return 1;
    case 0x00543b30: return 2;
    case 0x00543a08: return 1;                  /* skill no */
    case 0x005435f8: return 0;                  /* pac1 done (the result screen) */
    case 0x00543510: case 0x00543520: case 0x00543530: case 0x00543540:
    case 0x00543550: return 1;   /* the battle's encounter (SetFlag, nbInitMainProcess) */
    case 0x00543448: return 0;   /* an action still queued (nbCheckActionStack) */
    case 0x00543438: return 0;   /* backattack!! (CheckSenseiOrBackAttack) */
    case 0x005453b8: return 0;   /* nbPanelPressTurnStart */
    case 0x005458e8: case 0x00545918: case 0x00545948: case 0x00545978: case 0x005459a0: case 0x005459d0: case 0x00545a00:
    case 0x00545a30: case 0x00545a58: case 0x00545a80: case 0x00545aa8: case 0x00545ad0: case 0x00545af8: return 0;   /* nbSetEnemyFormation:ENC_FORMATION_* */
    case 0x00543458: case 0x00543468: case 0x00543478: return 0;   /* no one can act, game over, level up (the phases) */
    case 0x00543880: case 0x005438c0: case 0x00543908: return 0;   /* counters, a failed escape's hit */
    case 0x005438d8: return 2;                  /* inoti party */
    case 0x005438f0: return 1;                  /* binjo party */
    case 0x00544070: case 0x00544088: case 0x005440a0: case 0x005440b0: case 0x005440c0: case 0x005440d8: return 0; /* what an action did */
    case 0x00535a80: return 0;                  /* itfMesMngRequestMessage() escape 1 */
    case 0x00535aa8: return 1;                  /* itfMesMngRequestSelect() - Invalid Type */
    case 0x00535998: case 0x005359b0: return 1; /* NAME[%d] : Translate. / Restore. */
    case 0x0052e270: case 0x0052e2b8: case 0x0052e2e0: case 0x0052e2f0: case 0x0052e340: return 1; /* script lifecycle */
    case 0x0052e310: case 0x0052e328: case 0x0052f5e8: return 0;
    case 0x0052f588: case 0x0052f5a8: return 1;    /* PUT / PUTS */
    case 0x005457d8: case 0x005457e8: case 0x00544170: return 0;
    case 0x00544ba8: return 4; /* ailment chance */
    default:
        /* Another build: US Maniax's legacy C (its own addresses) may print
         * before the harness sees the test runs no instructions. */
        if (fw_other_version()) {
            fprintf(stderr, "fake world: unknown print format %08x (US Maniax %08x)\n", format, fw_maniax_address(format));
            return 0;
        }
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

/* datBossRashChk is the rewrite's (data_tests.cpp), so the legacy battle
 * code sees the same boss refights. */

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
void *nocturneResolveBattleScriptCommandsAddress(uint32_t a) { return fw_resolve(a); }
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

/* The process table: "nb_help", "nb_commsel" and, for any other name, the
 * target-selection process. */
uint64_t dds3SearchProcessName(uint64_t name)
{
    switch (fw_maniax_address((uint32_t)name)) {
    case 0x005514f0: return FW_HELP_PROCESS;
    case 0x005441a8: return FW_COMMSEL_PROCESS;
    case 0x00551560: return FW_MAKA_PROCESS;
    default: return 1;
    }
}

/* A process at a priority: there or not, by the case. */
uint64_t dds3SearchProcessPriority(uint64_t priority)
{
    return (fw_hash(159, priority, 0) & 1) ? 0x00777700u + ((uint32_t)priority & 0xff) : 0;
}

uint32_t evtGetAgeOfMoon16(void) { return case_moon * 2u + (uint32_t)(fw_hash(13, 0, 0) & 1); }

/* The flowscript VM (scrGetIntPara ...) is the rewrite's: script_bridge.cpp. */

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
    target = fw_maniax_address((uint32_t)target);
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

/* The interpreter's stack starts below what is staged here. */
uint32_t fw_stack_top(void) { return guest_sp; }

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
 * Panels and memory blocks come from a bump pool in dynamic RAM; calls with
 * side effects outside the code under test are logged. */

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
uint64_t ps2ResourcePacCheckEnd(uint64_t request)
{
    fw_mes_log(153, (uint32_t)request, 0);
    return fw_hash(153, (uint32_t)request, 0) % 2;
}
void ps2MemoryHandleDeferredRelease(uint64_t handle) { fw_mes_log(154, (uint32_t)handle, 0); }
uint64_t ps2TextureTmxCopy(uint64_t header)
{
    fw_mes_log(147, (uint32_t)header, 0);
    return fw_hash(147, (uint32_t)header, 0);
}
/* Processes: small records from the pool {name, ..., +0x20 priority,
 * +0x28 run time, +0x30 data, +0x34 alive marker}. */
enum { PROCESS_ALIVE = 0x00a11fe0 };
static int fake_process(uint32_t p)
{
    return p >= FW_MES_POOL && p <= FW_MES_POOL_END - 0x38 && rd32(p + 0x34) == PROCESS_ALIVE;
}
uint64_t dds3StartProcess(uint64_t name, uint64_t priority, uint64_t startdelay, uint64_t shutdowndelay,
                          uint64_t processfunc, uint64_t shutdownfunc, uint64_t data)
{
    fw_mes_log(12, (uint32_t)name, (uint32_t)priority ^ (uint32_t)startdelay << 16 ^ (uint32_t)shutdowndelay << 20);
    fw_mes_log(13, (uint32_t)processfunc, (uint32_t)shutdownfunc ^ (uint32_t)data);
    uint32_t p = mes_alloc(0x38);
    wr32(p, (uint32_t)name);
    wr32(p + 0x20, (uint32_t)priority);
    wr32(p + 0x28, (uint32_t)(fw_hash((uint32_t)name, 0, 0) & 0xff));
    wr32(p + 0x30, (uint32_t)data);
    wr32(p + 0x34, PROCESS_ALIVE);
    return p;
}

/* A process's data: the fake processes', else the target-selection process's. */
uint64_t dds3GetProcessData(uint64_t process)
{
    uint32_t p = (uint32_t)process;
    if (p == FW_HELP_PROCESS)
        return FW_HELP;
    if (p == FW_COMMSEL_PROCESS)
        return FW_COMMSEL;
    if (p == FW_MAKA_PROCESS)
        return FW_MAKA;
    return p >= FW_MES_POOL && p <= FW_MES_POOL_END - 0x38 && (rd32(p + 0x34) & ~1u) == PROCESS_ALIVE ? rd32(p + 0x30)
                                                                                                         : FW_TARSEL;
}

/* ---- the font engine's surroundings -------------------------------------- */

uint32_t ps2PoolAllocate(int32_t size)
{
    uint32_t p = mes_alloc((uint32_t)size);
    fw_mes_log(14, (uint32_t)size, p);
    return p;
}

/* The upload record: pixels, a word the font engine leaves unset, flags,
 * format, width, base, x, y, w, h. */
uint64_t ps2TextureQueueUpload(uint64_t record)
{
    uint32_t r = (uint32_t)record;
    uint8_t *q = fw_resolve(r);
    uint16_t h[6];
    memcpy(h, q + 10, 2); memcpy(h + 1, q + 16, 8); h[5] = 0;
    fw_mes_log(15, rd32(r), (uint32_t)q[8] | (uint32_t)q[9] << 8 | (uint32_t)h[0] << 16);
    fw_mes_log(16, rd32(r + 12), (uint32_t)h[1] | (uint32_t)h[2] << 16);
    fw_mes_log(17, (uint32_t)h[3] | (uint32_t)h[4] << 16, 0);
    return 0;
}

uint64_t ps2KernelGetFontContextIndex(void) { return (uint64_t)(int64_t)(int32_t)rd32(fw_data(0x551b80)); }

/* Files are already in RAM: a .bf path is the script at FW_MES_TABLE; a
 * font path picks one of FW_FONTS by its digit. */
uint64_t sdfDevLoadFile(uint64_t path, uint64_t data_out, uint64_t size_out)
{
    const char *p = (const char *)fw_resolve((uint32_t)path);
    static const uint32_t offset[4] = {0x00000, 0x18000, 0x2e000, 0x33000};
    uint32_t n = 0, length = (uint32_t)strlen(p), data;
    for (const char *q = p; *q; ++q) if (*q >= '0' && *q <= '3') n = (uint32_t)(*q - '0');
    data = length >= 3 && strcmp(p + length - 3, ".bf") == 0 ? FW_MES_TABLE : FW_FONTS + offset[n];
    (void)size_out;
    fw_mes_log(18, (uint32_t)path, n);
    if ((uint32_t)data_out) wr32((uint32_t)data_out, data);
    return data + 1u;   /* a handle (ps2MemoryHandleAcquirePointer subtracts 1) */
}

void dds3SetProcessData(uint64_t process, uint64_t data)
{
    uint32_t p = (uint32_t)process;
    if (p >= FW_MES_POOL && p <= FW_MES_POOL_END - 0x38) wr32(p + 0x30, (uint32_t)data);
    fw_mes_log(19, p, (uint32_t)data);
}
uint64_t dds3KillProcess(uint64_t process, uint64_t delay)
{
    uint32_t p = (uint32_t)process;
    if (fake_process(p)) wr32(p + 0x34, PROCESS_ALIVE | 1u);   /* ending: no longer listed */
    fw_mes_log(20, p, (uint32_t)delay);
    return 0;
}
uint64_t dds3ExistProcess(uint64_t process) { return fake_process((uint32_t)process) ? 1 : 0; }
void dds3LinkProcess(uint64_t parent, uint64_t process) { fw_mes_log(27, (uint32_t)parent, (uint32_t)process); }
void nbMakeKaifukuPacket(uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t type, uint64_t hp, uint64_t mp,
                         uint64_t badstat)
{
    fw_mes_log(28, (uint32_t)startframe ^ (uint32_t)type << 16, (uint32_t)uniqueid ^ (uint32_t)form);
    fw_mes_log(29, (uint32_t)hp, (uint32_t)mp ^ (uint32_t)badstat << 16);
}
uint64_t ps2BattleAction_00263C00(uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t type, uint64_t hp,
                                  uint64_t mp, uint64_t badstat, uint64_t hiteff, uint64_t dead, uint64_t deadtype,
                                  uint64_t moji, uint64_t animeoff)
{
    fw_mes_log(31, (uint32_t)startframe ^ (uint32_t)type << 20, (uint32_t)uniqueid ^ (uint32_t)form);
    fw_mes_log(34, (uint32_t)hp, (uint32_t)mp ^ (uint32_t)badstat << 8 ^ (uint32_t)hiteff << 16);
    fw_mes_log(35, (uint32_t)dead | (uint32_t)deadtype << 8 | (uint32_t)moji << 16 | (uint32_t)animeoff << 24, 0);
    return 0;
}
void nbPanelAnalyzeStart(void) { fw_mes_log(36, 0, 0); }
/* READY's SetAction / CheckAction (not rewritten): logged. */
uint64_t nbPanelStockSelect(uint64_t data, uint64_t sw) { fw_mes_log(41, (uint32_t)data, (uint32_t)sw); return 0; }
uint64_t ps2MovieCheckAdpcmFlag(void) { return (uint64_t)(int64_t)(int32_t)rd32(fw_data(0x5519c8)); }
uint64_t ps2MovieStopAdpcm(void) { fw_mes_log(42, 0, 0); return 0; }
/* Ongyo-Ki's effects: log the parameter words, hand out a handle. */
static uint64_t fake_effect(uint32_t kind, uint64_t param, unsigned words)
{
    uint32_t h = kind;
    for (unsigned i = 0; i < words; ++i) {
        uint32_t w = rd32((uint32_t)param + 4u * i);
        fw_mes_log(kind, i, w);
        h = (uint32_t)fw_hash(h, w, i);
    }
    return 0x00a00000u | (h & 0xffffu);
}
uint64_t ps2BattleActionSkill_00198200(uint64_t param) { return fake_effect(37, param, 1); }
uint64_t ps2BattleActionSkill_00198868(uint64_t param) { return fake_effect(38, param, 1); }
uint64_t effPCPBossBUNSINCreate(uint64_t param) { return fake_effect(39, param, 2); }
uint64_t effPCPBossBUNSIN2Create(uint64_t param) { return fake_effect(40, param, 4); }
uint64_t ps2BattleAction_00263918(uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t deadtype,
                                  uint64_t deadpcm)
{
    fw_mes_log(32, (uint32_t)startframe ^ (uint32_t)deadtype << 16 ^ (uint32_t)deadpcm << 24, (uint32_t)uniqueid ^ (uint32_t)form);
    return 1;
}
void ps2BattlePanelSetEnabled_00282200(uint64_t enabled) { fw_mes_log(33, (uint32_t)enabled, 0); }
uint64_t ps2ProcessGetRunTime(uint64_t process) { return (uint64_t)(int64_t)(int32_t)rd32((uint32_t)process + 0x28); }
void dds3FadeIn(uint64_t r, uint64_t g, uint64_t b, uint64_t frames) { fw_mes_log(21, (uint32_t)r ^ (uint32_t)g << 8 ^ (uint32_t)b << 16, (uint32_t)frames); }
void nbSetDamage(uint64_t form, uint64_t week, uint32_t range) { fw_mes_log(110, (uint32_t)form ^ (uint32_t)week << 24, range); }
void nbSetDamage2(uint64_t form, uint32_t range) { fw_mes_log(111, (uint32_t)form, range); }
void nbSetBadstatMotion(uint64_t form, uint64_t type, uint32_t range) { fw_mes_log(112, (uint32_t)form ^ (uint32_t)type << 20, range); }
void nbSetBadstatMotion2(uint64_t form) { fw_mes_log(113, (uint32_t)form, 0); }
uint64_t ps2NegoActorMotionId_0028D1B8(uint64_t form) { fw_mes_log(118, (uint32_t)form, 0); return (uint64_t)(0x10100u + fw_hash(118, (uint32_t)form, 0) % 0x40u); }
void NegoDebugDraw(uint64_t talk) { fw_mes_log(119, (uint32_t)talk, 0); }
void NegoDebugSelectDraw(uint64_t talk) { fw_mes_log(119, (uint32_t)talk, 1); }
uint64_t NegoDebug(uint64_t talk) { fw_mes_log(119, (uint32_t)talk, 2); return fw_hash(119, (uint32_t)talk, 2) % 2; }
uint64_t nbMemoryLoadNegoSe(uint64_t form) { fw_mes_log(120, (uint32_t)form, 0); return fw_hash(120, (uint32_t)form, 0) % 2; }
void ps2SoundVolumeHalfDown_002C20A0(void) { fw_mes_log(121, 0, 0); }
void ps2SoundVolumeHalfUp_002C20C8(void) { fw_mes_log(121, 1, 0); }
/* A talk step (the tests' stand-in for the flow functions): by the step's
 * phase, it ends the talk, chooses its next step or leaves candidates, and
 * may show a message. */
uint64_t fw_talk_step(uint64_t talk)
{
    uint32_t n = (uint32_t)talk, phase = rd32(n + 0x18), h = (uint32_t)fw_hash(122, rd32(n + 0x14) ^ rd32(n + 0xb0) << 24, phase);
    fw_mes_log(122, rd32(n + 0x14), phase);
    switch (h % 6) {
    case 0: return 1 + h / 6 % 4;                                   /* the talk ends */
    case 1: wr32(n + 0x1c, 1 + h / 6 % 50); break;                  /* the next step */
    case 2: wr32(n + 0x20, 1 + h / 6 % 3); wr32(n + 0x24, 0x40u + h / 18 % 60); wr32(n + 0x28, 0x80u + h / 7 % 60); break;
    case 3: wr32(n + 0x44, rd32(n + 0x50)); wr32(n + 0x48, h / 6 % 20); break;   /* a message */
    case 4: wr32(n + 0x10, h / 6 % 3); break;                        /* a wait */
    default: break;
    }
    return 0;
}
void nbPanelAutoHide(void) { fw_mes_log(116, 0, 0); }
void ps2BattlePanelHideHookA(void) { fw_mes_log(116, 1, 0); }
void nbCameraScriptSet1Shot(uint64_t form) { fw_mes_log(117, (uint32_t)form, 0); }
void nbCameraScriptSetBougai(uint64_t form) { fw_mes_log(117, (uint32_t)form, 1); }
void effBTLCutDraw(uint64_t cut) { fw_mes_log(109, (uint32_t)cut, 0); }
void dds3FadeIn2(uint64_t frames) { fw_mes_log(102, (uint32_t)frames, 0); }
void ps2BattleOutcome_001E3B78(uint64_t unit, uint64_t a, uint64_t b) { fw_mes_log(103, (uint32_t)unit, (uint32_t)a ^ (uint32_t)b << 16); }
void ps2BattleFormation_0028A340(uint64_t data, uint64_t group) { fw_mes_log(104, (uint32_t)data, (uint32_t)group); }
void ps2BattleFormation_0024D8C0(uint64_t side, uint64_t stockno, uint64_t formindex)
{
    fw_mes_log(106, (uint32_t)side ^ (uint32_t)stockno << 16, (uint32_t)formindex);
}
void ps2SoundStopEffectMidi_002C1730(uint64_t sound) { fw_mes_log(108, (uint32_t)sound, 0); }
void dds3FadeOut(uint64_t r, uint64_t g, uint64_t b, uint64_t frames) { fw_mes_log(22, (uint32_t)r ^ (uint32_t)g << 8 ^ (uint32_t)b << 16, (uint32_t)frames); }
void ps2PoolRelease(uint32_t slot) { fw_mes_log(23, slot, 0); }
void effBTLDelete(uint64_t handle) { fw_mes_log(26, (uint32_t)handle, 0); }
void effBTLCutDelete(uint64_t cut) { fw_mes_log(50, (uint32_t)cut, 0); }
/* effBTLCutCreate: the cut's fields as the real one fills them from the
   effect's description (cut 2's is 0x618 bytes after cut 1's). */
uint64_t effBTLCutCreate(uint64_t effect, uint64_t cut, uint64_t form, uint64_t state)
{
    const uint32_t description = (uint32_t)effect + ((cut & 0xffff) > 1 ? 0x620u : 8u);
    const uint32_t c = FW_BTL_CUT;
    memset(fw_resolve(c), 0, 0x120);
    wr32(c, (uint32_t)form);
    wr32(c + 4, (uint32_t)effect);
    wr32(c + 0xc, rd32(description));
    wr32(c + 0x10, (cut & 0xffff) == 2 ? rd32(description) : rd32(description + 0x70));
    wr32(c + 0x14, (uint32_t)cut & 0xffff);
    wr32(c + 0x18, (uint32_t)state);
    wr32(c + 0x1c, description);
    fw_mes_log(90, (uint32_t)effect ^ (uint32_t)cut << 24, (uint32_t)form ^ (uint32_t)state << 24);
    return c;
}
void effBTLSystemCutDelete(uint64_t cut) { fw_mes_log(51, (uint32_t)cut, 0); }
void effBTLPartDelete(uint64_t part) { fw_mes_log(52, (uint32_t)part, 0); }
void effPCPBossONGYDelete(uint64_t handle) { fw_mes_log(53, (uint32_t)handle, 0); }
void effPCPBossONGY2Delete(uint64_t handle) { fw_mes_log(54, (uint32_t)handle, 0); }
void effPCPBossBUNSINDelete(uint64_t handle) { fw_mes_log(55, (uint32_t)handle, 0); }
void effPCPBossBUNSIN2Delete(uint64_t handle) { fw_mes_log(56, (uint32_t)handle, 0); }
/* The kouka process's engine calls: logged; a part handle is handed out. */
void effPCPBossONGYDraw(uint64_t handle) { fw_mes_log(91, (uint32_t)handle, 1); }
void effPCPBossONGY2Draw(uint64_t handle) { fw_mes_log(91, (uint32_t)handle, 2); }
void effPCPBossBUNSINDraw(uint64_t handle) { fw_mes_log(91, (uint32_t)handle, 3); }
void effPCPBossBUNSIN2Draw(uint64_t handle) { fw_mes_log(91, (uint32_t)handle, 4); }
uint64_t ps2BattleAction_00173CB0(uint64_t form, uint64_t kind)
{
    fw_mes_log(92, (uint32_t)form, (uint32_t)kind);
    return 0x00779400u + ((uint32_t)kind & 0xff) * 0x10u;
}
void effBTLPartEnd(uint64_t part) { fw_mes_log(93, (uint32_t)part, 0); }
void effBTLPartDraw(uint64_t part) { fw_mes_log(93, (uint32_t)part, 1); }
void ps2BattlePanelSetAnalyzeUnit_00280538(uint64_t unit) { fw_mes_log(94, (uint32_t)unit, 0); }
/* The VU0 packet makers a helper's coming and going uses (0x265130,
 * 0x265298, 0x2653A0): logged, by which. */
/* The battle panel's drawing and the font's: logged. */
void ps2BattlePanelSetOrderingOffset_002797B0(uint64_t offset) { fw_mes_log(126, (uint32_t)offset, 0); }
void ps2BattlePanelSetPrimitive(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h)
{
    fw_mes_log(126, 1u ^ (uint32_t)a << 4 ^ (uint32_t)b << 8 ^ (uint32_t)c << 12, (uint32_t)d ^ (uint32_t)e << 8 ^ (uint32_t)f << 16 ^ (uint32_t)g << 20 ^ (uint32_t)h << 24);
}
void ps2BattlePanelSetAlpha(uint64_t mode) { fw_mes_log(126, 2, (uint32_t)mode); }
void ps2BattlePanelDrawTexturedRect(uint64_t x, uint64_t y, uint64_t w, uint64_t h, uint64_t u, uint64_t v, uint64_t tw, uint64_t th,
                                    uint64_t color, uint64_t texture)
{
    fw_mes_log(127, (uint32_t)x ^ (uint32_t)y << 16, (uint32_t)w ^ (uint32_t)h << 16);
    fw_mes_log(127, (uint32_t)u ^ (uint32_t)v << 16 ^ (uint32_t)tw << 8, (uint32_t)th ^ (uint32_t)color ^ (uint32_t)texture << 3);
}
uint64_t frDrawFontEx2(uint64_t font, uint64_t mode, uint64_t ot)
{
    fw_mes_log(128, (uint32_t)font, (uint32_t)mode ^ (uint32_t)ot << 8);
    return 0;
}
/* The battle events' surroundings: music, banks, packs, the basic effect. */
uint64_t ps2SoundPlayMidi_002C1670(uint64_t midi) { fw_mes_log(129, (uint32_t)midi, 0); return 0; }
uint64_t ps2SoundFadeOut_002C2070(uint64_t midi) { fw_mes_log(129, (uint32_t)midi, 1); return 0; }
uint64_t ps2SoundSelectOutput_002C20F0(uint64_t value) { fw_mes_log(132, (uint32_t)value, 0); return 0; }
uint64_t ps2SoundSelectChannel_002C1E70(uint64_t value) { fw_mes_log(133, (uint32_t)value, 0); return 0; }
/* The encounter's opening (nbEncProcess): its effect, camera and model loads. */
uint64_t fw_enc_effect(uint64_t end) { fw_mes_log(135, (uint32_t)end, 0); return 0; }
uint64_t fw_enc_camera_done(void) { fw_mes_log(136, 0, 0); return fw_hash(136, rd32(FW_SCRATCH + 0xbf0), 0) % 3 != 0; }
uint64_t fw_load_unit_group(uint64_t group, uint64_t a, uint64_t b) { fw_mes_log(137, (uint32_t)group, (uint32_t)a << 8 | (uint32_t)b); return 0; }
uint64_t fw_unit_group_loading(uint64_t group) { fw_mes_log(138, (uint32_t)group, 0); return fw_hash(138, (uint32_t)group, rd32(FW_SCRATCH + 0xbf0)) % 3 == 0; }
/* An object's control flags and pose (dds3ObjectBase*, dds3SetPosPoseSet). */
void dds3ObjectBaseOnFlag(uint64_t basic, uint64_t flag) { fw_mes_log(139, (uint32_t)basic, (uint32_t)flag); }
void dds3ObjectBaseOffFlag(uint64_t basic, uint64_t flag) { fw_mes_log(142, (uint32_t)basic, (uint32_t)flag); }
void dds3SetPosPoseSet(uint64_t basic, uint64_t pos) { fw_mes_log(143, (uint32_t)basic, rd32((uint32_t)pos) ^ rd32((uint32_t)pos + 4) ^ rd32((uint32_t)pos + 8)); }
uint64_t fw_fade_query(void) { fw_mes_log(140, 0, 0); return fw_hash(140, rd32(FW_SCRATCH + 0xbf0), 0) & 1; }
uint64_t fw_fade_set(uint64_t value) { fw_mes_log(141, (uint32_t)value, 0); return 0; }
/* A memory handle's size (0x2A8FE8). */
uint64_t fw_handle_size(uint64_t handle) { fw_mes_log(134, (uint32_t)handle, 0); return fw_hash(134, (uint32_t)handle, 0) & 0xfff0; }
void ps2SoundEnsureBank(uint64_t bank) { fw_mes_log(129, (uint32_t)bank, 2); }
uint64_t ps2ResourcePacRequestFree(uint64_t request) { fw_mes_log(129, (uint32_t)request, 3); return 0; }
void ps2BattleActionRequest_00296B88(void) { fw_mes_log(129, 0, 4); }
uint64_t fw_event_pack_load(uint64_t resource)
{
    fw_mes_log(130, (uint32_t)resource, 0);
    return dds3StartProcess(0x00777600, 0x3ec, 1, 1, 0, 0, (uint32_t)resource);
}
uint64_t fw_event_pack_state(uint64_t resource) { return fw_hash(130, (uint32_t)resource, 1) % 4; }
uint64_t fw_basic_effect(uint64_t p, uint64_t pos, uint64_t rot)
{
    uint32_t effect = mes_alloc(0x20), state = mes_alloc(0x10);
    fw_mes_log(131, (uint32_t)p ^ (uint32_t)pos << 8, (uint32_t)rot);
    wr32(effect + 0x18, state);
    wr32(state + 4, (uint32_t)fw_hash(131, (uint32_t)p, 0) & 0xfe);
    return effect;
}
uint64_t fw_move_packets(uint64_t entry, uint64_t startframe, uint64_t uniqueid, uint64_t form, uint64_t target)
{
    fw_mes_log(125, (uint32_t)entry ^ (uint32_t)startframe << 24, (uint32_t)uniqueid ^ (uint32_t)form ^ (uint32_t)target << 8);
    return 1;
}
void dds3SetRotPoseSet(uint64_t basic, uint64_t rot) { fw_mes_log(124, (uint32_t)basic, rd32((uint32_t)rot) ^ rd32((uint32_t)rot + 4) ^ rd32((uint32_t)rot + 8) ^ rd32((uint32_t)rot + 12)); }
void nbReturnUnit(uint64_t partyindex, uint64_t arg, uint64_t dead)
{
    fw_mes_log(96, (uint32_t)partyindex ^ (uint32_t)arg << 16, (uint32_t)dead);
}
void nbMoveTarget(uint64_t partyno, uint64_t pos, uint32_t speed)
{
    fw_mes_log(97, (uint32_t)partyno, speed);
    fw_mes_log(98, (uint32_t)pos, rd32((uint32_t)pos) ^ rd32((uint32_t)pos + 4) ^ rd32((uint32_t)pos + 8));
}
void nbMoveHome(uint64_t partyno, uint32_t speed) { fw_mes_log(97, (uint32_t)partyno | 0x100u, speed); }
void evtSetAgeOfMoon(int32_t age) { fw_mes_log(99, (uint32_t)age, 0); }
void nbUnitSetColor(uint64_t unit, uint64_t frames, uint64_t color) { fw_mes_log(100, (uint32_t)unit ^ (uint32_t)frames << 24, (uint32_t)color); }
void nbUnitSetAlpha(uint64_t unit, uint64_t frames, uint64_t alpha) { fw_mes_log(101, (uint32_t)unit ^ (uint32_t)frames << 24, (uint32_t)alpha); }
void nbPanelAllShow(void) { fw_mes_log(57, 0, 0); }
/* READY's loading and presentation (log ids 66..): values from a hash of the arguments. */
void effBTLSkillStart(uint64_t skill, uint64_t arg) { fw_mes_log(66, (uint32_t)skill, (uint32_t)arg); }
void effBTLSkillEnd(void) { fw_mes_log(67, 0, 0); }
uint64_t effBTLBedName(uint64_t skill) { fw_mes_log(68, (uint32_t)skill, 0); return 0x00777400u + ((uint32_t)skill & 0xff); }
uint64_t effBTLLoad(uint64_t data) { fw_mes_log(69, (uint32_t)data, 0); return 0x00778000u + (fw_hash(69, (uint32_t)data, 0) & 0xff); }
uint64_t ps2SoundBankStatus(uint64_t bank) { fw_mes_log(70, (uint32_t)bank, 0); return fw_hash(70, (uint32_t)bank, 0) % 3; }   /* 0 none, 1 loaded, 2 loading */
void ps2SoundSetBankSource(uint64_t data, uint64_t size) { fw_mes_log(71, (uint32_t)data, (uint32_t)size); }
uint64_t fileRequest(uint64_t path) { fw_mes_log(72, (uint32_t)path, 0); return fw_hash(72, (uint32_t)path, 0) % 4 == 0 ? 0 : 0x00779000u + (fw_hash(73, (uint32_t)path, 0) & 0xfff); }
uint64_t fileCheckEnd(uint64_t request) { fw_mes_log(74, (uint32_t)request, 0); return fw_hash(74, (uint32_t)request, 0) % 3 != 0; }
uint64_t fileGetMemHandle(uint64_t request) { fw_mes_log(75, (uint32_t)request, 0); return 0x0077a001u + ((uint32_t)request & 0xff0); }
uint64_t fileGetLoadSize(uint64_t request) { fw_mes_log(76, (uint32_t)request, 0); return fw_hash(76, (uint32_t)request, 0) & 0xffff; }
void ps2ResourceRequestRelease(uint64_t request) { fw_mes_log(77, (uint32_t)request, 0); }
uint64_t nbGetMotionActframe(uint64_t form, uint64_t motion, uint32_t speed)
{
    fw_mes_log(78, (uint32_t)form ^ (uint32_t)motion << 24, speed);
    return fw_hash(78, (uint32_t)motion, speed) % 4 == 0 ? 0 : fw_hash(79, (uint32_t)motion, speed) % 60;
}
uint32_t nbGetMotionSpeed(uint64_t form, uint64_t motion, uint32_t speed)
{
    fw_mes_log(80, (uint32_t)form ^ (uint32_t)motion << 24, speed);
    return speed;   /* the motion's own speed is 1 here */
}
uint64_t nbGetMotionNo(uint64_t form, uint64_t motion) { fw_mes_log(81, (uint32_t)form, (uint32_t)motion); return (uint64_t)(int64_t)(int32_t)(fw_hash(81, (uint32_t)motion, 0) % 40); }
void nbStopMotionSe(void) { fw_mes_log(82, 0, 0); }
uint64_t nbGetMotionSeNo(uint64_t form, uint64_t motion) { fw_mes_log(83, (uint32_t)form, (uint32_t)motion); return 0x00300000u + ((uint32_t)motion & 0xff); }
uint64_t nbMemoryLoadMotionSe(uint64_t form, uint64_t motion) { fw_mes_log(84, (uint32_t)form, (uint32_t)motion); return fw_hash(84, (uint32_t)motion, 0) & 1; }
void nbMakeSkillEffectPacket(uint64_t start, uint64_t timer, uint64_t act, uint64_t form, uint64_t hiteff, uint64_t motiontype,
                             uint64_t skill)
{
    fw_mes_log(85, (uint32_t)start ^ (uint32_t)timer << 8, (uint32_t)act);
    fw_mes_log(86, (uint32_t)form ^ (uint32_t)hiteff << 24, (uint32_t)motiontype ^ (uint32_t)skill << 16);
}
void nbAddHitEffPacket(uint64_t start, uint64_t act, uint64_t form, uint64_t kind)
{
    fw_mes_log(87, (uint32_t)start ^ (uint32_t)kind << 24, (uint32_t)act ^ (uint32_t)form);
}
void nbMakeTargetPacket(uint64_t start, uint64_t act, uint64_t form, uint64_t targets, uint64_t kind, uint32_t speed)
{
    fw_mes_log(88, (uint32_t)start ^ (uint32_t)kind << 8, (uint32_t)act ^ (uint32_t)form);
    fw_mes_log(89, (uint32_t)targets, speed);
}
void effBTLSkillSetFormationInfo(uint64_t formindex, uint64_t targets) { fw_mes_log(61, (uint32_t)formindex, (uint32_t)targets); }
void nbInitNegoProcess(uint64_t act, uint64_t pformindex, uint64_t eformindex, uint64_t negotype, uint64_t skill)
{
    fw_mes_log(62, (uint32_t)act, (uint32_t)pformindex ^ (uint32_t)eformindex << 8);
    fw_mes_log(63, (uint32_t)negotype, (uint32_t)skill);
}
void nbSetWaitMotion(uint64_t form, uint64_t motion, uint32_t speed) { fw_mes_log(64, (uint32_t)form ^ (uint32_t)motion << 24, speed); }
void nbSetUnitMotion(uint64_t form, uint64_t motion, uint64_t loop, uint32_t speed)
{
    fw_mes_log(65, (uint32_t)form ^ (uint32_t)motion << 24 ^ (uint32_t)loop << 28, speed);
}
void nbPanelPressGaugeShow(void) { fw_mes_log(58, 0, 0); }
void nbPanelStockSelectInit(void) { fw_mes_log(59, 0, 0); }
void nbPanelStockEnd(void) { fw_mes_log(60, 0, 0); }
int32_t cmpRemoveDevilEx(uint16_t devil) { fw_mes_log(25, devil, 0); return (int32_t)(fw_hash(14, devil, 0) % 3); }
void dds3PadAct(uint64_t mode, uint64_t pow, uint64_t frame) { fw_mes_log(24, (uint32_t)mode ^ (uint32_t)pow << 24, (uint32_t)frame); }
uint64_t nocturneInvokeScriptFunction(uint32_t entry, uint64_t work, unsigned command)
{
    (void)work; (void)command;
    fprintf(stderr, "fake world: no command at %08x\n", entry);
    abort();
}

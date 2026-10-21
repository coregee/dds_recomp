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
#include "combat_calculation.h"

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

static uint16_t r16(uint32_t a) { uint16_t v; memcpy(&v, fw_resolve(a), 2); return v; }
static uint32_t r32(uint32_t a) { uint32_t v; memcpy(&v, fw_resolve(a), 4); return v; }
static uint64_t sx(int32_t v) { return (uint64_t)(int64_t)v; }

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
    /* The legacy passes sign-extended 64-bit register values; keep the
     * 32-bit value they represent. */
    for (int i = 0; i < count; ++i) args[i] = (int32_t)va_arg(ap, uint64_t);
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

/* ---- battle and data fakes --------------------------------------------- */

static datUnitWork_PS2 *unit_at(uint32_t address) { return (datUnitWork_PS2 *)fw_resolve(address); }

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

uint64_t nbGetNormalSkillAttr(uint64_t skill)
{
    return sx((int32_t)(fw_hash(1, skill, 0) % 17) - 1); /* -1 .. 15 */
}

uint64_t nbGetAisyo(uint64_t skill, uint64_t target, uint64_t attribute)
{
    static const uint32_t values[] = {
        100, 100, 100, 50, 0x80000096u, 0x10000, 0x20000, 0x40000, 0x110000, 200, 0x80100000u, 10,
    };
    return sx((int32_t)values[fw_hash(2, skill * 64 + target, attribute) % 12]);
}

int32_t nbHatudoCheckSkill(datUnitWork_PS2 *work, int32_t skill)
{
    return fw_hash(3, fw_address_of(work), (uint64_t)skill) % 4 == 0;
}

float nbGetHojoRitu(uint64_t formation, uint64_t type)
{
    static const float values[] = { 0.5f, 0.75f, 1.0f, 1.0f, 1.0f, 1.25f, 1.5f, 2.0f };
    return values[fw_hash(4, formation, type) % 8];
}

uint64_t nbGetDevilFormatFlag(uint64_t form) { return fw_hash(5, form, 0) % 3 == 0 ? 0x800 : 0; }

uint64_t nbGetBadStat(uint64_t form)
{
    uint32_t unit = (uint32_t)nbGetUnitWorkFromFormindex(form);
    return unit ? r16(unit + 0xe) & 0xfffu : 0;
}

uint64_t nbCheckFormationPlayerSide(uint64_t form) { return form < 4; }

uint64_t nbGetUnitID(uint64_t work) { return r16((uint32_t)work + 4) % 300u; }

uint64_t datGet3Zokusei(uint64_t unit) { return sx((int32_t)(fw_hash(6, unit, 0) % 3) - 1); }

int32_t datGetParam(datUnitWork_PS2 *work, int32_t paratype)
{
    int32_t value = work->param[paratype];
    if (!(work->flag & 4)) value += work->mitamaparam[paratype];
    if (value < 1) value = 1;
    if (value > 40) value = 40;
    if ((work->badstat & 0xfff) == 0x200 && paratype != 4) value = 1;
    return value;
}

uint32_t datAddHp(datUnitWork_PS2 *work, int32_t hp)
{
    int32_t value = work->hp + hp;
    if (value < 0) value = 0;
    if (value > work->maxhp) value = work->maxhp;
    work->hp = (uint16_t)value;
    return work->hp;
}

uint32_t datAddMp(datUnitWork_PS2 *work, int32_t mp)
{
    int32_t value = work->mp + mp;
    if (value < 0) value = 0;
    if (value > work->maxmp) value = work->maxmp;
    work->mp = (uint16_t)value;
    return work->mp;
}

void datSetBadStat(datUnitWork_PS2 *work, uint32_t badstat)
{
    if (badstat == 0x8000) work->badstat |= 0x8000;
    else if ((work->badstat & 0xfffu) < badstat)
        work->badstat = (uint16_t)((work->badstat & 0xf000u) | (badstat & 0xfffu));
}

void datResetBadStat(datUnitWork_PS2 *work, uint32_t badstat)
{
    if (badstat == 0x8000) work->badstat &= 0x7fff;
    else if ((work->badstat & 0xfffu) == badstat) work->badstat &= 0xf000;
}

int32_t datCheckSyojiSkill(datUnitWork_PS2 *work, uint32_t skill)
{
    return fw_hash(7, fw_address_of(work), skill) % 2;
}

int32_t datCheckSkillInParty(int32_t skillid) { return fw_hash(8, (uint64_t)skillid, 0) % 3 == 0; }

int32_t datGetPlayerLevel(void) { return r16(FW_GLOBAL + 0xa54 + 0x14); }

int32_t datBossRashChk(int32_t eid) { return fw_hash(9, (uint64_t)eid, 0) % 5 == 0; }

uint64_t ps2UnitEvasionPower_00242D50(uint64_t unit)
{
    datUnitWork_PS2 *w = unit_at((uint32_t)unit);
    return sx(datGetParam(w, 4) * 2 + w->level);
}

uint64_t ps2UnitMagicHitPower_00242CB0(uint64_t unit)
{
    datUnitWork_PS2 *w = unit_at((uint32_t)unit);
    /* Zero now and then, to exercise the divide-by-zero trap. */
    return fw_hash(10, unit, 0) % 50 == 0 ? 0 : sx(datGetParam(w, 2) * 2 + w->level / 2);
}

uint32_t evtBitCheck(int32_t no)
{
    if (no == 0xaf2) return (uint32_t)case_normal;
    return fw_hash(11, (uint64_t)no, 0) % 2;
}

uint32_t evtGetAgeOfMoon(void) { return case_moon; }

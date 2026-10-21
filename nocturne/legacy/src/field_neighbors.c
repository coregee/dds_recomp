#include "field_neighbors.h"
#include <string.h>

static int32_t signed_word(uint32_t bits)
{
    return bits <= (uint32_t)INT32_MAX ? (int32_t)bits
        : -1 - (int32_t)(UINT32_MAX - bits);
}

/* The established runtime prefix deliberately leaves field/area unnamed.
 * Read its character representation rather than casting another struct view. */
static int32_t runtime_int(size_t offset)
{
    int32_t value;
    memcpy(&value, (const unsigned char *)g_fldRuntimeFlags + offset, sizeof value);
    return value;
}

static uint32_t effect_flags(void)
{
    uint32_t value;
    memcpy(&value, g_datGlobalWork->unknown_0a4c, sizeof value);
    return value;
}

/* PS2 001233f0; native fldMain$$fldLightMaIdxCalc. */
int32_t fldLightMaIdxCalc(void)
{
    int32_t field = runtime_int(4);
    int32_t area;
    switch (field) {
    case 0x15:
        area = runtime_int(8);
        return area == 2 ? 100 : area == 0x17 ? 101 : 102;
    case 0x1a:
        area = runtime_int(8);
        return area == 0x12 || area == 0x13 || area == 0x15 ? 101 : 102;
    case 0x1d:
        area = runtime_int(8);
        return area == 1 ? 100 : area == 9 || area == 10 ? 101 : 102;
    case 0x25:
        area = runtime_int(8);
        if (area == 0x0f) return 100;
        break;
    default:
        break;
    }
    return 100;
}

/* The original wrappers call Clear, clearing its runtime bit, then reload that
 * same runtime word and set the bit. Do not replace the real calls with a
 * collapsed final-value formula. All three skip runtime on the inactive path. */
void fldRifutoMaClearMsg(void)
{
    if ((effect_flags() & UINT32_C(4)) == 0) return;
    fldRifutoMaClear();
    g_fldRuntimeFlags->flags |= UINT32_C(2);
}

void fldRiberaMaClearMsg(void)
{
    if ((effect_flags() & UINT32_C(2)) == 0) return;
    fldRiberaMaClear();
    g_fldRuntimeFlags->flags |= UINT32_C(4);
}

void fldEsutoMaClearMsg(void)
{
    if ((effect_flags() & UINT32_C(1)) == 0) return;
    fldEsutoMaClear();
    g_fldRuntimeFlags->flags |= UINT32_C(8);
}

static int anahori_eligible(const datUnitWork_PS2 *unit)
{
    uint32_t flags = unit->flag;
    return (flags & UINT32_C(1)) != 0
        && (flags & UINT32_C(4)) == 0
        && (flags & UINT32_C(0x10)) == 0
        && (flags & UINT32_C(0x800)) == 0
        && unit->hp != 0;
}

/* PS2 001238f0: clear index, then count; compute locally over all16 inline
 * records, then store count. ID, capacity and stock-list fields are not gates. */
void fldAnahoriSelectInit(void)
{
    datGlobalWork_PS2 *work = g_datGlobalWork;
    fldAnahoriState_PS2 *state = g_fldAnahoriState;
    int32_t count = 0;
    state->index = 0;
    state->eligible_count = 0;
    for (unsigned slot = 0; slot < 16; ++slot) {
        if (anahori_eligible(&work->units[slot])) ++count;
    }
    state->eligible_count = count;
}

/* PS2 00123970: count is only a zero/nonzero gate. Match eligible ordinal,
 * including duplicates/ID0; the LHU result is returned without sign extension. */
int32_t fldAnahoriSelectGet(void)
{
    if (g_fldAnahoriState->eligible_count == 0) return 0;
    datGlobalWork_PS2 *work = g_datGlobalWork;
    int32_t wanted = g_fldAnahoriState->index;
    int32_t ordinal = 0;
    for (unsigned slot = 0; slot < 16; ++slot) {
        if (anahori_eligible(&work->units[slot])) {
            if (wanted == ordinal) return work->units[slot].id;
            ++ordinal;
        }
    }
    return 0;
}

/* PS2 00123a10: one final SW; ADDIU wraps32 before signed comparison. */
void fldAnahoriSelectNext(void)
{
    int32_t old = g_fldAnahoriState->index;
    int32_t count = g_fldAnahoriState->eligible_count;
    int32_t next = signed_word((uint32_t)old + UINT32_C(1));
    g_fldAnahoriState->index = next < count ? next : 0;
}

/* PS2 0022cf08; native cmpInit$$cmpChkCampProcess. */
int8_t cmpChkCampProcess(void)
{
    int8_t state = *g_cmpCampProcessState;
    if (state == 1) return 1;
    if (state == 2) *g_cmpCampProcessState = 0;
    return 0;
}

/* PS2 00124240: wait first, then real consuming camp check, then process20. */
int32_t fldProcCampChk(void)
{
    if (g_fldProcWait->camp_wait > 0) return 2;
    if (cmpChkCampProcess() != 0) return 1;
    return fldProcCheckFlag(UINT32_C(0x20)) != 0 ? 0 : 3;
}

/* PS2 00149288: return the complete signed mode word, not a Boolean. */
int32_t fldAutoMapChkMode(void)
{
    return *g_fldAutoMapMode;
}

/* PS2 00124508: wait first; only this wrapper Booleanizes the real mode read. */
int32_t fldProcAmChk(void)
{
    if (g_fldProcWait->am_wait > 0) return 2;
    return fldAutoMapChkMode() != 0;
}

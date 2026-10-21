#include "kernel_event_neighbors.h"
#include <string.h>

/* The existing global view deliberately leaves these four bytes unnamed.
 * Use its character representation rather than an incompatible struct cast. */
static uint32_t effect_flags(void)
{
    uint32_t value;
    memcpy(&value, g_datGlobalWork->unknown_0a4c, sizeof value);
    return value;
}

static void store_effect_flags(uint32_t value)
{
    memcpy(g_datGlobalWork->unknown_0a4c, &value, sizeof value);
}

static uint32_t rotate_right_8(uint32_t value)
{
    return (value >> 8) | (value << 24);
}

/* PS2 002c0c98; native identity sdfRand$$sdfRandomize. Preserve the PS2
 * constants; the saved HD body's later seed expressions are different. */
void sdfRandomize(uint32_t *state, uint32_t seed)
{
    if (state == NULL) state = g_sdfDefaultState;
    uint32_t value = seed ^ UINT32_C(0x0aed1a0c);
    state[0] = value;
    value = rotate_right_8(value);
    state[1] = value;
    value = rotate_right_8(value ^ UINT32_C(0xaa5a02fe));
    state[2] = value;
    value = rotate_right_8(value ^ UINT32_C(0x11be81c7));
    state[3] = value;
}

/* PS2 00125990 / 001259a8 / 001259c0. */
void fldSeqOnFlag(uint32_t flag)
{
    g_fldFlagState->sequence_flags |= flag;
}

void fldSeqOffFlag(uint32_t flag)
{
    g_fldFlagState->sequence_flags &= ~flag;
}

int8_t fldSeqCheckFlag(uint32_t flag)
{
    return (g_fldFlagState->sequence_flags & flag) != 0;
}

/* PS2 001259d0 / 001259e0 / 001259f8. */
void fldProcOnFlag(uint32_t flag)
{
    g_fldFlagState->process_flags |= flag;
}

void fldProcOffFlag(uint32_t flag)
{
    g_fldFlagState->process_flags &= ~flag;
}

int8_t fldProcCheckFlag(uint32_t flag)
{
    return (g_fldFlagState->process_flags & flag) != 0;
}

/* PS2 001234f8 / 001235b0. Each mutator stores global-work+A4C before
 * reading and storing the separate runtime word at 002fbf94. */
void fldLightMaClear(void)
{
    store_effect_flags(effect_flags() & ~UINT32_C(8));
    g_fldRuntimeFlags->flags &= ~UINT32_C(1);
}

int32_t fldLightMaChk(void)
{
    if ((effect_flags() & UINT32_C(8)) != 0) return 1;
    return *g_fldLightMaEnabled != 0 ? 0 : -1;
}

/* PS2 001236e8 / 00123718 / 00123748. */
void fldRifutoMaClear(void)
{
    store_effect_flags(effect_flags() & ~UINT32_C(4));
    g_fldRuntimeFlags->flags &= ~UINT32_C(2);
}

void fldRifutoMaStart(void)
{
    store_effect_flags(effect_flags() | UINT32_C(4));
    g_fldRuntimeFlags->flags &= ~UINT32_C(2);
}

int32_t fldRifutoMaChk(void)
{
    return (effect_flags() & UINT32_C(4)) != 0;
}

/* PS2 001237a8 / 001237d8 / 00123810. */
void fldRiberaMaClear(void)
{
    store_effect_flags(effect_flags() & ~UINT32_C(2));
    g_fldRuntimeFlags->flags &= ~UINT32_C(4);
}

void fldRiberaMaStart(void)
{
    store_effect_flags((effect_flags() | UINT32_C(2)) & ~UINT32_C(1));
    g_fldRuntimeFlags->flags &= ~UINT32_C(4);
}

int32_t fldRiberaMaChk(void)
{
    return (effect_flags() & UINT32_C(2)) != 0;
}

/* PS2 00123870 / 001238a0 / 001238d8. */
void fldEsutoMaClear(void)
{
    store_effect_flags(effect_flags() & ~UINT32_C(1));
    g_fldRuntimeFlags->flags &= ~UINT32_C(8);
}

void fldEsutoMaStart(void)
{
    store_effect_flags((effect_flags() | UINT32_C(1)) & ~UINT32_C(2));
    g_fldRuntimeFlags->flags &= ~UINT32_C(8);
}

int32_t fldEsutoMaChk(void)
{
    return (effect_flags() & UINT32_C(1)) != 0;
}

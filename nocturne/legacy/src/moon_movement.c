#include "moon_movement.h"
#include "nocturne.h"
#include "field_neighbors.h"
#include "ee_fpu.h"
#include <string.h>

static uint32_t counter(void)
{
    uint32_t value;
    memcpy(&value, (const uint8_t *)g_datGlobalWork + 0x11a7c, 4);
    return value;
}
static void put_counter(uint32_t value)
{
    memcpy((uint8_t *)g_datGlobalWork + 0x11a7c, &value, 4);
}
static uint64_t sign_word(uint32_t value)
{
    return value & UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000) | value : value;
}
/* 001234b0: execute the actual clear before the later runtime-word reload. */
void ps2FieldLightClearMessage(void)
{
    uint32_t flags;
    memcpy(&flags, g_datGlobalWork->unknown_0a4c, 4);
    if (flags & 8) {
        fldLightMaClear();
        g_fldRuntimeFlags->flags |= 1;
    }
}

/* 001eac20: retains the PS2 random reset; the HD port uses fixed12. */
void evtMoonAddMove(float length)
{
    if (!(g_datGlobalWork->moon_flags & 1)) return;
    uint32_t input;
    memcpy(&input, &length, 4);
    uint32_t accumulated = EE_FPU_ADD_S(g_datGlobalWork->moon_move_bits, input);
    uint32_t advanced = EE_MOON_COMPARE_LESS_S(*g_moonMoveLimitBits, accumulated);
    g_datGlobalWork->moon_move_bits = accumulated; /* BC1F delay-slot store. */
    if (!advanced) return;
    uint32_t next = (g_datGlobalWork->moon_phase + 1u) & 15u;
    g_datGlobalWork->moon_move_bits = 0;
    evtSetAgeOfMoon((int32_t)next);
    *g_moonStepCountdown = 30;
    if (evtGetAgeOfMoon() == 0) {
        fldEsutoMaClearMsg();
        fldRiberaMaClearMsg();
        fldRifutoMaClearMsg();
        ps2FieldLightClearMessage();
    }
    g_datGlobalWork->unknown_0a42[0] = (uint8_t)(g_datGlobalWork->unknown_0a42[0] + 1u);
    uint32_t limit = sdfGetRandInt(NULL, 2) + 12;
    if (g_datGlobalWork->unknown_0a42[0] > limit) g_datGlobalWork->unknown_0a42[0] = 0;
    if (!evtBitCheck(0x502)) {
        if (!evtBitCheck(0x503)) put_counter(0);
        return;
    }
    uint32_t value = counter();
    if (sign_word(value) >> 63 || value < 240) {
        value += 1; /* ADDIU word wrap, including negative counter inputs. */
        put_counter(value);
        nocturneMoonDiagnostic(UINT32_C(0x53b1e0), sign_word(value));
    }
    uint32_t target = evtBitCheck(0x504) ? 112 : 160;
    if (counter() == 48) evtBitOn(0x505);
    if (counter() == target) evtBitOn(0x506);
}

#include "nocturne.h"

/* 001e9998 / 001e99c0: raw unsigned phase; folded value peaks at8. */
uint32_t evtGetAgeOfMoon(void)
{
    uint32_t age = g_datGlobalWork->moon_phase;
    return age > 8 ? 8 - (age & 7) : age;
}

uint32_t evtGetAgeOfMoon16(void)
{
    return g_datGlobalWork->moon_phase;
}

/* 001e99d0: low4 bits, including negative input; clear the move word. */
void evtSetAgeOfMoon(int32_t age)
{
    g_datGlobalWork->moon_phase = (uint8_t)((uint32_t)age & 15);
    g_datGlobalWork->moon_move_bits = 0;
}

/* 001e99e8. */
void evtEnableMoonCalc(void)
{
    g_datGlobalWork->moon_flags |= 1;
}

/* 001e9a00: recovered independently from PS2. This chosen source name is not
 * a reviewed HD match: evtDisableMoonCalc's native body is protected. */
void ps2MoonDisableCalc(void)
{
    g_datGlobalWork->moon_flags &= (uint8_t)~1;
}

/* 001e9a18 / 001e9a38 additionally force draw alpha. */
void evtEnableMoonDraw(void)
{
    g_datGlobalWork->moon_flags |= 2;
    g_evtMoonDrawAlpha = 1.0f;
}

void evtDisableMoonDraw(void)
{
    g_datGlobalWork->moon_flags &= (uint8_t)~2;
    g_evtMoonDrawAlpha = 0.0f;
}

/* 001e9a50 / 001e9a68 leave alpha unchanged. */
void evtEnableMoonDraw2(void)
{
    g_datGlobalWork->moon_flags |= 2;
}

void evtDisableMoonDraw2(void)
{
    g_datGlobalWork->moon_flags &= (uint8_t)~2;
}

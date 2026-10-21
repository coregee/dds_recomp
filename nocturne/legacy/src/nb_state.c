#include "nocturne.h"

/* 002492e0: sixteen local battle event bits. */
void nbMainProcess_ClearLocalBit(void)
{
    for (int32_t i = 0; i < 16; ++i) evtBitOff(0xbf0 + i);
}

/* 002493a8: c04 always maps to800000; the remaining flags are gated.
 * A disabled gate preserves all previously stored gated flags. */
void nbMainProcess_SetDebugFlag(nbMainProcessData_PS2_prefix *data)
{
    static const struct { int32_t bit; uint32_t flag; } mapping[] = {
        {0xc00,0x20000}, {0xc01,0x10000}, {0xc02,0x40000},
        {0xc03,0x400000}, {0xc05,0x2000000}, {0xc06,0x4000000},
        {0xc07,0x8000000}, {0xc0d,0x40000000}, {0xc10,0x80000000},
        {0xc12,0x8000}
    };
    if (evtBitCheck(0xc04)) data->flag |= 0x800000;
    else data->flag &= ~0x800000u;
    if (g_nbDebugEnabled != 0) {
        data->flag |= 0x1000000;
        for (size_t i = 0; i < sizeof(mapping)/sizeof(mapping[0]); ++i) {
            if (evtBitCheck(mapping[i].bit)) data->flag |= mapping[i].flag;
            else data->flag &= ~mapping[i].flag;
        }
    }
}

/* 0026a3d8: skills300/301 need full/new moon respectively. */
int32_t nbHatudoCheckSkill(datUnitWork_PS2 *work, int32_t skill)
{
    if (!datCheckSyojiSkill(work, (uint32_t)skill)) return 0;
    if (skill == 300) return evtGetAgeOfMoon() == 8;
    if (skill == 301) return evtGetAgeOfMoon() == 0;
    return 1;
}

/* 0026ad70: negotiation request based on maximumHP, event8 and default RNG.
 * The first two parameters are retained although unused by these instructions. */
int32_t nbGetNegoKureHpA(void *n, datUnitWork_PS2 *a, datUnitWork_PS2 *b)
{
    (void)n;
    (void)a;
    uint32_t percent = evtBitCheck(8) ? sdfGetRandInt(NULL, 10) + 20 : sdfGetRandInt(NULL, 8) + 14;
    return (int32_t)(b->maxhp * percent) / 100;
}

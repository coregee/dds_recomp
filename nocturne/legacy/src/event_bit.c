#include "nocturne.h"

/* PS2 0x001e0e38. No range checks occur in these original routines. */
void evtBitAllOff(void)
{
    for (int32_t i = 0; i < 128; ++i) g_datGlobalWork->event_bits[i] = 0;
}

/* PS2 0x001e0ed0; signed division truncates toward zero as in the
 * instruction sequence. Bit-number shift counts use the low five bits. */
void evtBitOn(int32_t no)
{
    g_datGlobalWork->event_bits[no / 32] |= UINT32_C(1) << ((uint32_t)no & 31);
}

/* PS2 0x001e0f10. */
void evtBitOff(int32_t no)
{
    g_datGlobalWork->event_bits[no / 32] &= ~(UINT32_C(1) << ((uint32_t)no & 31));
}

/* PS2 0x001e0f50. The HD edition overrides and achievement hooks are absent. */
uint32_t evtBitCheck(int32_t no)
{
    return (g_datGlobalWork->event_bits[no / 32] >> ((uint32_t)no & 31)) & 1;
}

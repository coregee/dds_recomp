#include "nocturne.h"

/* PS2 0x002c0ba8; HD sdfRand::sdfGetRand. */
uint32_t sdfGetRand(uint32_t *state)
{
    if (state == NULL) state = g_sdfDefaultState;
    uint32_t old0 = state[0], old1 = state[1];
    uint32_t old2 = state[2], old3 = state[3];
    uint32_t next = ((old1 << 2) | (old0 >> 30)) ^
                    ((old3 << 1) | (old2 >> 31));
    state[3] = old2;
    state[2] = old1;
    state[1] = old0;
    state[0] = next;
    return next;
}

/* PS2 0x002c0c00; exactly 2^-24 after masking to 24 bits. */
float sdfGetRandFloat(uint32_t *state)
{
    return (float)(sdfGetRand(state) & UINT32_C(0xffffff)) * 0x1p-24f;
}

/* PS2 0x002c0c60. DIVU proves unsigned remainder. The HD zero-limit
 * return of zero is intentionally absent from this PS2 reconstruction. */
uint32_t sdfGetRandInt(uint32_t *state, uint32_t limit)
{
    uint32_t value = sdfGetRand(state);
    if (limit == 0) nocturne_break(7);
    return value % limit;
}

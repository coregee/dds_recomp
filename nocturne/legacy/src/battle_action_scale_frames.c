/* Four whole native JR RA / SWC1 delay-slot PCP scale leaves.
 * Only their actual formal A0/F12 inputs are installed. Raw F12
 * bits are stored in live guest RAM; no arithmetic or host output
 * provider is involved. Ordinary native return domain only. */
#include "battle_action_scale_frames.h"
#include "battle_action_consumer.h"
#include "effect_host_bindings.h"
#include <string.h>

static uint64_t cpu(unsigned r)
{
    uint32_t q[4];nocturneEffectHostCpuRead(r,q);
    return q[0]|((uint64_t)q[1]<<32);
}
static void set(unsigned r,uint64_t value)
{
    uint32_t q[4];nocturneEffectHostCpuRead(r,q);
    q[0]=(uint32_t)value;q[1]=(uint32_t)(value>>32);
    nocturneEffectHostCpuWrite(r,q);
}
static uint32_t bits(float value)
{
    uint32_t raw;memcpy(&raw,&value,4);return raw;
}

void ps2BattleActionPcpScale_00193480(uint64_t object,float scale)
{
    set(4,object);nocturneEffectHostFpr()[12]=bits(scale);
    nocturneEffectAxisNoteEntry(0x00193480u);
    /* 00193480 JR RA: latch the ordinary incoming return before delay. */
    uint64_t target=cpu(31);
    /* 00193484 SWC1 delay: actual shared F12 raw word. */
    uint32_t value=nocturneEffectHostFpr()[12];
    memcpy(nocturneResolveBattleActionConsumerAddress((uint32_t)cpu(4)+0x2cu),&value,4);
    (void)target;return;
}

void ps2BattleActionPcpScale_0017FC48(uint64_t object,float scale)
{
    set(4,object);nocturneEffectHostFpr()[12]=bits(scale);
    nocturneEffectAxisNoteEntry(0x0017fc48u);
    /* 0017fc48 JR RA: latch the ordinary incoming return before delay. */
    uint64_t target=cpu(31);
    /* 0017fc4c SWC1 delay: actual shared F12 raw word. */
    uint32_t value=nocturneEffectHostFpr()[12];
    memcpy(nocturneResolveBattleActionConsumerAddress((uint32_t)cpu(4)+0x58u),&value,4);
    (void)target;return;
}

void ps2BattleActionPcpScale_00180BB0(uint64_t object,float scale)
{
    set(4,object);nocturneEffectHostFpr()[12]=bits(scale);
    nocturneEffectAxisNoteEntry(0x00180bb0u);
    /* 00180bb0 JR RA: latch the ordinary incoming return before delay. */
    uint64_t target=cpu(31);
    /* 00180bb4 SWC1 delay: actual shared F12 raw word. */
    uint32_t value=nocturneEffectHostFpr()[12];
    memcpy(nocturneResolveBattleActionConsumerAddress((uint32_t)cpu(4)+0xdcu),&value,4);
    (void)target;return;
}

void ps2BattleActionPcpScale_00181558(uint64_t object,float scale)
{
    set(4,object);nocturneEffectHostFpr()[12]=bits(scale);
    nocturneEffectAxisNoteEntry(0x00181558u);
    /* 00181558 JR RA: latch the ordinary incoming return before delay. */
    uint64_t target=cpu(31);
    /* 0018155c SWC1 delay: actual shared F12 raw word. */
    uint32_t value=nocturneEffectHostFpr()[12];
    memcpy(nocturneResolveBattleActionConsumerAddress((uint32_t)cpu(4)+0x5cu),&value,4);
    (void)target;return;
}

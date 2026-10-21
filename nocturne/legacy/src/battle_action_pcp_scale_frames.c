/* Four whole native JR RA / SWC1 delay-slot PCP scale leaves.
 * Only their actual formal A0/F12 inputs are installed. Raw F12
 * bits are stored in live guest RAM; no arithmetic or host output
 * provider is involved. Ordinary native return domain only. */
#include "battle_action_pcp_scale_frames.h"
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

void ps2BattleActionPcpScale_0017D8F0(uint64_t object,float scale)
{
    set(4,object);nocturneEffectHostFpr()[12]=bits(scale);
    nocturneEffectAxisNoteEntry(0x0017d8f0u);
    /* 0017d8f0 JR RA: latch the ordinary incoming return before delay. */
    uint64_t target=cpu(31);
    /* 0017d8f4 SWC1 delay: actual shared F12 raw word. */
    uint32_t value=nocturneEffectHostFpr()[12];
    memcpy(nocturneResolveBattleActionConsumerAddress((uint32_t)cpu(4)+0x4cu),&value,4);
    (void)target;return;
}

void ps2BattleActionPcpScale_0017E2A8(uint64_t object,float scale)
{
    set(4,object);nocturneEffectHostFpr()[12]=bits(scale);
    nocturneEffectAxisNoteEntry(0x0017e2a8u);
    /* 0017e2a8 JR RA: latch the ordinary incoming return before delay. */
    uint64_t target=cpu(31);
    /* 0017e2ac SWC1 delay: actual shared F12 raw word. */
    uint32_t value=nocturneEffectHostFpr()[12];
    memcpy(nocturneResolveBattleActionConsumerAddress((uint32_t)cpu(4)+0x54u),&value,4);
    (void)target;return;
}

void ps2BattleActionPcpScale_0017EAD0(uint64_t object,float scale)
{
    set(4,object);nocturneEffectHostFpr()[12]=bits(scale);
    nocturneEffectAxisNoteEntry(0x0017ead0u);
    /* 0017ead0 JR RA: latch the ordinary incoming return before delay. */
    uint64_t target=cpu(31);
    /* 0017ead4 SWC1 delay: actual shared F12 raw word. */
    uint32_t value=nocturneEffectHostFpr()[12];
    memcpy(nocturneResolveBattleActionConsumerAddress((uint32_t)cpu(4)+0x5cu),&value,4);
    (void)target;return;
}

void ps2BattleActionPcpScale_0017F3D0(uint64_t object,float scale)
{
    set(4,object);nocturneEffectHostFpr()[12]=bits(scale);
    nocturneEffectAxisNoteEntry(0x0017f3d0u);
    /* 0017f3d0 JR RA: latch the ordinary incoming return before delay. */
    uint64_t target=cpu(31);
    /* 0017f3d4 SWC1 delay: actual shared F12 raw word. */
    uint32_t value=nocturneEffectHostFpr()[12];
    memcpy(nocturneResolveBattleActionConsumerAddress((uint32_t)cpu(4)+0x64u),&value,4);
    (void)target;return;
}

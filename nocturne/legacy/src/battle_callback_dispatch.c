/* Canonical public parent ownership; zero new native identities. */
#include "battle_callback_dispatch.h"
#include "battle_callback_native.h"
#include "fusion_core_transport.h"
#include <stdlib.h>

extern uint32_t g_nocturneEffectHostActive;
void nocturneEffectHostCpuRead(unsigned reg,uint32_t words[4]);

static int native_domain(void)
{
    uint32_t active=nocturneFusionCoreIsActive(),sp,words[4];
    if(active>1u||g_nocturneEffectHostActive>1u)abort();
    if(!active||!g_nocturneEffectHostActive)return 0;
    /* Both actual owners are active: invalid bank setup is an error, never
     * an excuse to silently fall back to the old private-frame abstraction. */
    sp=nocturneFusionCoreStackPointer();
    nocturneEffectHostCpuRead(29,words);
    if(words[0]!=sp||words[1]!=0||sp<0x630400u||sp>0x64f000u||(sp&15u))abort();
    nocturneEffectHostCpuRead(28,words);
    if(words[0]!=0x554170u||words[1]!=0)abort();
    return 1;
}

void nbActionSetSeq(uint64_t context,uint64_t state)
{
    if(native_domain())ps2BattleCallbackNative_00257C80(context,state);
    else nocturneLegacyNbActionSetSeq(context,state);
}

uint64_t nbActionProcess1(uint64_t process)
{
    if(native_domain())return ps2BattleCallbackNative_00257CD0(process);
    return nocturneLegacyNbActionProcess1(process);
}

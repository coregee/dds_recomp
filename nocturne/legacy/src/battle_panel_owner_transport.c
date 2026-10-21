/* Actual canonical architectural banks and ordinary RAM. Processor SQRT value
 * comes from the pinned LGPL PS2Float source, never a host sqrt or game result.
 * Only explicit unknown callback stops use the local host observation frame. */
#include "battle_panel_owner.h"
#include "fusion_core_transport.h"
#include "ee_fpu_sqrt.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
void *nocturneEffectHostAddress(uint32_t address);
void nocturneEffectHostCpuRead(unsigned reg,uint32_t words[4]);
void nocturneEffectHostCpuWrite(unsigned reg,const uint32_t words[4]);
#if defined(NOCTURNE_PANEL_OWNER_PROBE)
__declspec(dllimport) extern uint32_t g_pathRotationVu[32][4];
__declspec(dllimport) extern uint32_t g_scriptCoreFcsr;
#else
extern uint32_t g_pathRotationVu[32][4];
extern uint32_t g_scriptCoreFcsr;
#endif
static jmp_buf observer;
static uint32_t active;
static uint64_t stop[4];
void nocturneBattlePanelOwnerCpuRead(unsigned reg,uint32_t words[4]){nocturneEffectHostCpuRead(reg,words);}
void nocturneBattlePanelOwnerCpuWrite(unsigned reg,const uint32_t words[4]){nocturneEffectHostCpuWrite(reg,words);}
void nocturneBattlePanelOwnerVuRead(unsigned reg,uint32_t words[4]){
 if(reg>=32u)abort();
 if(!reg){words[0]=words[1]=words[2]=0;words[3]=UINT32_C(0x3f800000);}else memcpy(words,g_pathRotationVu[reg],16);
}
void nocturneBattlePanelOwnerVuWrite(unsigned reg,const uint32_t words[4]){if(reg>=32u)abort();if(reg)memcpy(g_pathRotationVu[reg],words,16);}
void *nocturneResolveBattlePanelOwnerAddress(uint32_t address){
#if defined(NOCTURNE_PANEL_OWNER_PROBE)
 static const uint32_t spans[][2]={{0x2f5f18,0x900},{0x4efad0,0x300},{0x4efff8,0x1b8},{0x5452b0,0x1c0},
  {0x54e5b4,0x3c},{0x551168,0xa4},{0x551868,0x18},{0x64e000,0x2000},{0x880000,0x1000},{0x900000,0x20000}};
 unsigned i;for(i=0;i<sizeof(spans)/sizeof(spans[0]);i++)if(address>=spans[i][0]&&address-spans[i][0]<spans[i][1])break;
 if(i==sizeof(spans)/sizeof(spans[0]))abort();
#endif
 return nocturneEffectHostAddress(address);
}
uint32_t nocturneBattlePanelOwnerStackPointer(void){
 uint32_t words[4],sp=nocturneFusionCoreStackPointer();nocturneEffectHostCpuRead(29,words);
 if(words[0]!=sp||words[1])abort();return sp;
}
void nocturneBattlePanelOwnerSetStackPointer(uint32_t address){
 uint32_t words[4];nocturneEffectHostCpuRead(29,words);nocturneFusionCoreSetStackPointer(address);
 words[0]=address;words[1]=0;nocturneEffectHostCpuWrite(29,words);
}
uint32_t nocturneBattlePanelOwnerFcsr(void){return g_scriptCoreFcsr;}
uint32_t nocturneBattlePanelOwnerSqrtS(uint32_t bits,uint32_t pc){if(pc!=UINT32_C(0x0027a84c))abort();return EE_FPU_SQRT_S(bits);}
void nocturneBattlePanelOwnerIndirect(uint64_t target,uint32_t pc){
 uint32_t words[4];if(!active)abort();nocturneEffectHostCpuRead(29,words);
 stop[0]=1;stop[1]=pc;stop[2]=target;stop[3]=words[0];longjmp(observer,1);
}
uint32_t nocturneBattlePanelOwnerRun(uint32_t entry){
 uint32_t handled;if(active)abort();memset(stop,0,sizeof(stop));active=1;
 if(setjmp(observer)){active=0;return 0;}
 handled=nocturneBattlePanelOwnerBody(entry);active=0;return handled;
}
const uint64_t *nocturneBattlePanelOwnerLastStop(void){return stop;}

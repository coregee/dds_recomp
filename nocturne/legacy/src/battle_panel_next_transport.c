/* Ordinary RAM and genuine dependency/trap stops only. Actual588 owns CPU,
 * VU,FPR,FCSR,SP and known packet/callback code; no shadow state or results. */
#include "battle_panel_next.h"
#include "fusion_core_transport.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
uint32_t nocturneBattlePanelOwnerRun(uint32_t entry);
const uint64_t *nocturneBattlePanelOwnerLastStop(void);
void *nocturneEffectHostAddress(uint32_t address);
#if defined(NOCTURNE_PANEL_NEXT_PROBE)
__declspec(dllimport) extern uint32_t g_scriptCoreFcsr;
#else
extern uint32_t g_scriptCoreFcsr;
#endif
static jmp_buf observer;
static uint32_t active;
static uint64_t stop[4];
void *nocturneResolveBattlePanelNextAddress(uint32_t address){
#if defined(NOCTURNE_PANEL_NEXT_PROBE)
 static const uint32_t spans[][2]={{0x2f5f18,0x900},{0x4efad0,0x300},{0x4efff8,0x1b8},{0x4f0628,0xb0},
  {0x5452b0,0x1c0},{0x54e5ac,0x44},{0x551168,0xa4},{0x551868,0x18},{0x551fe0,0xc},
  {0x64e000,0x2000},{0x880000,0x1000},{0x900000,0x20000}};
 unsigned i;for(i=0;i<sizeof(spans)/sizeof(spans[0]);++i)if(address>=spans[i][0]&&address-spans[i][0]<spans[i][1])break;
 if(i==sizeof(spans)/sizeof(spans[0]))abort();
#endif
 return nocturneEffectHostAddress(address);
}
uint32_t nocturneBattlePanelNextStackPointer(void){
 uint32_t q[4],sp=nocturneFusionCoreStackPointer();nocturneEffectHostCpuRead(29,q);
 if(q[0]!=sp||q[1])abort();return sp;
}
void nocturneBattlePanelNextSetStackPointer(uint32_t address){
 uint32_t q[4];nocturneEffectHostCpuRead(29,q);nocturneFusionCoreSetStackPointer(address);
 q[0]=address;q[1]=0;nocturneEffectHostCpuWrite(29,q);
}
uint32_t nocturneBattlePanelNextFcsr(void){return g_scriptCoreFcsr;}
void nocturneBattlePanelNextDependencyStop(uint32_t entry,uint32_t pc){
 const uint64_t *child=nocturneBattlePanelOwnerLastStop();
 if(!active)abort();
 stop[0]=2;stop[1]=pc;stop[2]=entry;stop[3]=child[1];longjmp(observer,1);
}
_Noreturn void nocturneBattlePanelNextTrap(uint32_t code,uint32_t pc){
 if(!active)abort();stop[0]=1;stop[1]=pc;stop[2]=code;longjmp(observer,1);
}
uint32_t nocturneBattlePanelNextRun(uint32_t entry){
 uint32_t handled;if(active)abort();memset(stop,0,sizeof(stop));active=1;
 if(setjmp(observer)){active=0;return 0;}
 /* Native setup roots use exactly the same actual588 dependency route. */
 handled=nocturneBattlePanelNextBody(entry);
 if(!handled)handled=nocturneBattlePanelOwnerRun(entry);
 active=0;return handled;
}
const uint64_t *nocturneBattlePanelNextLastStop(void){return stop;}

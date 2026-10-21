/* Ordinary RAM and genuine dependency/trap stops only. The admitted panel layer owns CPU,
 * VU,FPR,FCSR,SP and known packet/callback code; no shadow state or results. */
#include "battle_panel_auto.h"
#include "fusion_core_transport.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
uint32_t nocturneBattlePanelOwnerRun(uint32_t entry);
const uint64_t *nocturneBattlePanelOwnerLastStop(void);
void *nocturneEffectHostAddress(uint32_t address);
#if defined(NOCTURNE_PANEL_AUTO_PROBE)
__declspec(dllimport) extern uint32_t g_scriptCoreFcsr;
#else
extern uint32_t g_scriptCoreFcsr;
#endif
static jmp_buf observer;
static uint32_t active;
static uint64_t stop[4];
void *nocturneResolveBattlePanelAutoAddress(uint32_t address){
#if defined(NOCTURNE_PANEL_AUTO_PROBE)
 static const uint32_t spans[][2]={{0x2f5f18,0x900},{0x4efe60,0x30},{0x4f05d8,0x50},
  {0x5452b0,0x50},{0x54e62c,8},{0x54e758,0x1c},{0x551168,0x20},{0x551234,0xc},{0x551868,0x18},
  {0x64e000,0x2000},{0x880000,0x1000},{0x900000,0x20000}};
 unsigned i;for(i=0;i<sizeof(spans)/sizeof(spans[0]);++i)if(address>=spans[i][0]&&address-spans[i][0]<spans[i][1])break;
 if(i==sizeof(spans)/sizeof(spans[0]))abort();
#endif
 return nocturneEffectHostAddress(address);
}
uint32_t nocturneBattlePanelAutoStackPointer(void){
 uint32_t q[4],sp=nocturneFusionCoreStackPointer();nocturneEffectHostCpuRead(29,q);
 if(q[0]!=sp||q[1])abort();return sp;
}
void nocturneBattlePanelAutoSetStackPointer(uint32_t address){
 uint32_t q[4];nocturneEffectHostCpuRead(29,q);nocturneFusionCoreSetStackPointer(address);
 q[0]=address;q[1]=0;nocturneEffectHostCpuWrite(29,q);
}
uint32_t nocturneBattlePanelAutoFcsr(void){return g_scriptCoreFcsr;}
void nocturneBattlePanelAutoDependencyStop(uint32_t entry,uint32_t pc){
 const uint64_t *child=nocturneBattlePanelOwnerLastStop();
 if(!active)abort();
 stop[0]=2;stop[1]=pc;stop[2]=entry;stop[3]=child[1];longjmp(observer,1);
}
_Noreturn void nocturneBattlePanelAutoIndirectStop(uint64_t target,uint32_t pc){
 if(!active)abort();stop[0]=3;stop[1]=pc;stop[2]=target;longjmp(observer,1);
}
_Noreturn void nocturneBattlePanelAutoTrap(uint32_t code,uint32_t pc){
 if(!active)abort();stop[0]=1;stop[1]=pc;stop[2]=code;longjmp(observer,1);
}
uint32_t nocturneBattlePanelAutoRun(uint32_t entry){
 uint32_t handled;if(active)abort();memset(stop,0,sizeof(stop));active=1;
 if(setjmp(observer)){active=0;return 0;}
 /* Native setup roots use exactly the same admitted native dependency route. */
 handled=nocturneBattlePanelAutoBody(entry);
 if(!handled)handled=nocturneBattlePanelOwnerRun(entry);
 active=0;return handled;
}
const uint64_t *nocturneBattlePanelAutoLastStop(void){return stop;}

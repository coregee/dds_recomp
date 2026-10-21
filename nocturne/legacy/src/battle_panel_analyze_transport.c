/* One actual CPU/RAM bank, whole native callees and genuine stop boundaries. */
#include "battle_panel_analyze_transport.h"
#include "fusion_core_transport.h"
#include <stdlib.h>
#include <string.h>
void *nocturneEffectHostAddress(uint32_t);
uint32_t *nocturneEffectHostFpr(void);
uint32_t nocturneBattlePanelAutoBody(uint32_t);
uint32_t nocturneBattlePanelAutoRun(uint32_t);
const uint64_t *nocturneBattlePanelAutoLastStop(void);
#if defined(NOCTURNE_PANEL_ANALYZE_PROBE)
__declspec(dllimport) extern uint32_t g_scriptCoreFcsr;
#else
extern uint32_t g_scriptCoreFcsr;
#endif
static uint64_t low(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return(uint64_t)q[0]|((uint64_t)q[1]<<32);}
static uint32_t typed_entry,typed_armed;
static float floating(unsigned r){float v;uint32_t u=nocturneEffectHostFpr()[r];memcpy(&v,&u,4);return v;}
static uint32_t typed(uint32_t entry){
 switch(entry){
 case 0x27a240u:ps2BattlePanelCenterFontRequest_0027A240(low(4),low(5));return 1;
 case 0x27a630u:ps2BattlePanelDrawScaledGradientRect_0027A630(low(4),low(5),low(6),low(7),low(8),low(9),low(10),floating(12),floating(13));return 1;
 case 0x280508u:nbPanelAnalyzeInit();return 1;
 case 0x280518u:nbPanelAnalyzeStart();return 1;
 case 0x280538u:ps2BattlePanelSetAnalyzeUnit_00280538(low(4));return 1;
 case 0x280540u:nbPanelAnalyzeRun();return 1;
 case 0x282200u:ps2BattlePanelSetEnabled_00282200(low(4));return 1;
 default:return 0;
 }
}
void *nocturneResolveBattlePanelAnalyzeAddress(uint32_t address){return nocturneEffectHostAddress(address);}
uint32_t nocturneBattlePanelAnalyzeStackPointer(void){
 uint32_t sp=nocturneFusionCoreStackPointer();if(low(29)!=(uint64_t)sp)abort();return sp;
}
void nocturneBattlePanelAnalyzeSetStackPointer(uint32_t sp){
 uint32_t q[4];nocturneEffectHostCpuRead(29,q);nocturneFusionCoreSetStackPointer(sp);q[0]=sp;q[1]=0;nocturneEffectHostCpuWrite(29,q);
}
uint32_t nocturneBattlePanelAnalyzeFcsr(void){return g_scriptCoreFcsr;}
void nocturneBattlePanelAnalyzeCall(uint32_t target,uint32_t pc){
 if(typed_armed&&pc==0u&&target==typed_entry){typed_armed=0u;if(typed(target))return;}
 if(nocturneBattlePanelAnalyzeBody(target)||nocturneBattlePanelAnalyzeDependencyBody(target))return;
 /* Reuse the two already admitted complete initializers. The historical
  * renderer bundle predates them; both operate on this same actual bank. */
 if(target==0x2acb78u||target==0x2797b0u){
  if(nocturneBattlePanelOwnerBody(target))return;
  nocturneBattlePanelRendererUnprovided(pc,1u,target);
 }
 if(target==0x281e10u||target==0x281e28u){
  if(nocturneBattlePanelAutoBody(target))return;
  nocturneBattlePanelRendererUnprovided(pc,1u,target);
 }
 if(target==0x27a4e0u){
  const uint64_t *child;
  if(nocturneBattlePanelAutoRun(target))return;
  child=nocturneBattlePanelAutoLastStop();
  nocturneBattlePanelRendererUnprovided((uint32_t)child[1],14u,child[2]);
 }
 if(nocturneBattlePanelAnalyzeRawOwns(target)){nocturneBattlePanelAnalyzeRawCall(target,pc);return;}
 nocturneBattlePanelAnalyzeBaseCall(target,pc);
}
void nocturneBattlePanelAnalyzeIndirect(uint64_t target,uint32_t pc){
 if(pc==0x27a780u||pc==0x2149c4u||pc==0x239dd0u){
  uint32_t loaded;memcpy(&loaded,nocturneEffectHostAddress((uint32_t)low(4)+16u),4);
  if(low(31)!=(uint64_t)(pc+8u)||target!=UINT64_C(0x002acd40)||loaded!=0x2acd40u)
   nocturneBattlePanelRendererUnprovided(pc,2u,target);
  nocturneBattlePanelAnalyzeCall(0x2acd40u,pc);return;
 }
 nocturneBattlePanelRendererIndirect(target,pc);
}
_Noreturn void nocturneBattlePanelAnalyzeTrap(uint32_t code,uint32_t pc){nocturneBattlePanelRendererTrap(code,pc);}
void nocturneBattlePanelAnalyzeSyscall(uint32_t pc,uint64_t selector){nocturneBattlePanelAnalyzeRawSyscall(pc,selector);}
uint32_t nocturneBattlePanelAnalyzeRun(uint32_t entry){return nocturneBattlePanelRendererRun(entry);}
uint32_t nocturneBattlePanelAnalyzeRunTyped(uint32_t entry){
 uint32_t result;typed_entry=entry;typed_armed=1u;result=nocturneBattlePanelRendererRun(entry);typed_armed=0u;return result;
}
const NocturneBattlePanelRendererStop *nocturneBattlePanelAnalyzeLastStop(void){return nocturneBattlePanelRendererLastStop();}

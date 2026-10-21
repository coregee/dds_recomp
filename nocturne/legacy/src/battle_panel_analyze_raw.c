/* Actual resumable native kernel/heap source joined to the shared game bank.
 * No syscall reply, allocation address, context return or RAM repair is given.
 * A selected different thread PC stops the static caller with real state. */
#include "battle_panel_analyze_transport.h"
#include "native_kernel_router.h"
#include "rpc_client_native.h"
#include "sound_thread_support_native.h"
#include <string.h>
void *nocturneEffectHostAddress(uint32_t);
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostHi(void);
uint64_t nocturneEffectHostLo(void);
void nocturneEffectHostSetHilo(uint64_t,uint64_t);
#if defined(NOCTURNE_PANEL_ANALYZE_PROBE)
__declspec(dllimport) extern uint32_t g_scriptCoreFcsr,g_nocturnePoolStatus,g_fusionSortScratchSP;
#else
extern uint32_t g_scriptCoreFcsr,g_nocturnePoolStatus,g_fusionSortScratchSP;
#endif
static NocturneWakeupMachine state;
static NocturneWakeupStop stopped;
static NocturneNativeRouteCounts counts;
static uint32_t ranges[96][2],range_count,configured;
static uint64_t limit;
static uint32_t physical(uint32_t a){
 if(a>=0xffff8000u)return 0x78000u+(a-0xffff8000u);
 if(a>=0x20000000u&&a<0x22000000u)return a-0x20000000u;
 return a>=0x80000000u&&a<0xc0000000u?a&0x1fffffffu:a;
}
static int backed(uint32_t a,uint32_t n){
 a=physical(a);
 for(uint32_t i=0;i<range_count;i++)if(a>=ranges[i][0]&&a-ranges[i][0]<=ranges[i][1]&&n<=ranges[i][1]-(a-ranges[i][0]))return 1;
 return 0;
}
static int read_ram(void *v,uint32_t a,void *p,uint32_t n){
 (void)v;if(!backed(a,n))return 0;a=physical(a);
 for(uint32_t i=0;i<n;i++)((uint8_t*)p)[i]=*(uint8_t*)nocturneEffectHostAddress(a+i);return 1;
}
static int write_ram(void *v,uint32_t a,const void *p,uint32_t n){
 (void)v;if(!backed(a,n))return 0;a=physical(a);
 for(uint32_t i=0;i<n;i++)*(uint8_t*)nocturneEffectHostAddress(a+i)=((const uint8_t*)p)[i];return 1;
}
static int owns(void *v,uint32_t pc){
 (void)v;return nocturneNativeKernelOwns(pc)||(pc>=0x2a8080u&&pc<0x2a80a8u)||(pc>=0x2dbea0u&&pc<0x2dbeb0u)||(pc>=0x2dbee0u&&pc<0x2dbef0u);
}
static uint32_t body(void *v,NocturneWakeupMachine *m,const NocturneWakeupMemory *mem,uint64_t budget,NocturneWakeupStop *s){
 (void)v;
 if((m->pc>=0x2a8080u&&m->pc<0x2a80a8u)||(m->pc>=0x2dbea0u&&m->pc<0x2dbeb0u))return nocturneSoundThreadSupportResume(m,mem,budget,s);
 if(m->pc>=0x2dbee0u&&m->pc<0x2dbef0u)return nocturneRpcClientResume(m,mem,budget,s);
 return nocturneNativeKernelBody(m,mem,budget,s);
}
static void import_banks(void){
 for(unsigned i=0;i<32;i++)nocturneEffectHostCpuRead(i,state.gpr[i]);
 memcpy(state.fpr,nocturneEffectHostFpr(),sizeof(state.fpr));
 state.hi=nocturneEffectHostHi();state.lo=nocturneEffectHostLo();
 state.hi1=nocturneBattleActionFormulaSecondaryHi();state.lo1=nocturneBattleActionFormulaSecondaryLo();
 state.fcsr=g_scriptCoreFcsr;state.status=g_nocturnePoolStatus;
}
static void publish_banks(void){
 for(unsigned i=1;i<32;i++)nocturneEffectHostCpuWrite(i,state.gpr[i]);
 memcpy(nocturneEffectHostFpr(),state.fpr,sizeof(state.fpr));
 nocturneEffectHostSetHilo(state.lo,state.hi);nocturneBattleActionFormulaSecondaryWrite(state.lo1,state.hi1);
 g_scriptCoreFcsr=state.fcsr;g_nocturnePoolStatus=state.status;
 /* The raw source can stop on a real virtual kernel stack. Preserve its SP
  * verbatim in the existing shared bookkeeping; never map it to the user SP.
  * No static game frame resumes unless the raw PC reaches its actual boundary. */
 g_fusionSortScratchSP=state.gpr[29][0];
}
uint32_t nocturneBattlePanelAnalyzeRawConfigure(const NocturneWakeupMachine *before,const uint32_t *spans,uint32_t count,uint64_t budget){
 if(!before||!spans||!count||count>96u||!budget)return 0;
 for(uint32_t i=0;i<count;i++){
  uint32_t a=spans[2*i],n=spans[2*i+1];if(!n||a>=0x2000000u||n>0x2000000u-a)return 0;
  if(i&&a<spans[2*i-2]+spans[2*i-1])return 0;
 }
 state=*before;memcpy(ranges,spans,(size_t)count*8);range_count=count;limit=budget;configured=1;
 memset(&stopped,0,sizeof(stopped));memset(&counts,0,sizeof(counts));return 1;
}
const NocturneWakeupMachine *nocturneBattlePanelAnalyzeRawState(void){return &state;}
const NocturneWakeupStop *nocturneBattlePanelAnalyzeRawStop(void){return &stopped;}
uint32_t nocturneBattlePanelAnalyzeRawOwns(uint32_t pc){return(uint32_t)owns(0,pc);}
static void execute(uint32_t entry,uint32_t stop_pc,uint32_t pc,int syscall){
 const NocturneWakeupMemory mem={0,read_ram,write_ram};const NocturneNativeRouter router={0,owns,body};uint32_t outcome=NOCTURNE_NATIVE_TRANSFER;
 if(!configured)nocturneBattlePanelRendererUnprovided(pc,12u,entry);
 import_banks();state.pc=entry;
 if(syscall){
  outcome=nocturneNativeEnterSyscall(&state,state.instructions<limit?limit-state.instructions:0,&stopped);
  if(outcome==NOCTURNE_NATIVE_TRANSFER)++counts.syscalls;
 }
 if(outcome==NOCTURNE_NATIVE_TRANSFER)outcome=nocturneNativeRouteResume(&state,&mem,&router,state.instructions<limit?limit-state.instructions:0,stop_pc,&stopped,&counts);
 publish_banks();
 if(outcome!=NOCTURNE_NATIVE_TRANSFER||state.pc!=stop_pc)
  nocturneBattlePanelRendererUnprovided(state.pc,13u,((uint64_t)outcome<<32)|stop_pc);
}
void nocturneBattlePanelAnalyzeRawCall(uint32_t entry,uint32_t pc){
 uint32_t q[4];nocturneEffectHostCpuRead(31,q);execute(entry,q[0],pc,0);
}
void nocturneBattlePanelAnalyzeRawSyscall(uint32_t pc,uint64_t selector){
 uint32_t q[4];nocturneEffectHostCpuRead(3,q);
 if(selector!=((uint64_t)q[0]|((uint64_t)q[1]<<32)))nocturneBattlePanelRendererUnprovided(pc,9u,selector);
 if(pc!=0x2dbd94u&&pc!=0x2dbe84u&&pc!=0x2dbec4u&&pc!=0x2dbee4u)
  nocturneBattlePanelRendererUnprovided(pc,3u,selector);
 execute(pc,pc+4u,pc,1);
}

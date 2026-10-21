/* Actual resumable native kernel/heap source joined to the shared game bank.
 * No syscall reply, allocation address, context return or RAM repair is given.
 * A selected different thread PC stops the static caller with real state. */
#include "battle_reward_phase_raw.h"
#include "native_kernel_router.h"
#include "rpc_client_native.h"
#include "sound_thread_support_native.h"
#include "sound_play_bank_native.h"
#include "sound_enqueue_native.h"
#include "sound_thread_bootstrap_native.h"
#include <string.h>
void *nocturneEffectHostAddress(uint32_t);
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostHi(void);
uint64_t nocturneEffectHostLo(void);
void nocturneEffectHostSetHilo(uint64_t,uint64_t);
#if defined(NOCTURNE_BATTLE_REWARD_PROBE)
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
static int cache_op(void *v,uint32_t pc,uint32_t op,uint32_t a){(void)v;return nocturneBattleRewardPhaseRawCache(pc,op,a);}
static int taglo(void *v,uint32_t *out){(void)v;return nocturneBattleRewardPhaseRawTagLo(out);}
static const NocturneSoundBankProcessor processor={0,cache_op,taglo};
static int sound_group(uint32_t pc){
 if(nocturneSoundPlayBankOwns(pc))return 1;
 if((pc>=0x2c10e8u&&pc<0x2c1234u)||(pc>=0x2d43a4u&&pc<0x2d4454u)||(pc>=0x2dbdd0u&&pc<0x2dbde0u))return 2;
 if((pc>=0x2c0fc0u&&pc<0x2c10e4u)||(pc>=0x2dbca0u&&pc<0x2dbcb0u)||(pc>=0x2dbcc0u&&pc<0x2dbcd0u)||(pc>=0x2dbdc0u&&pc<0x2dbdd0u))return 3;
 if((pc>=0x2a8080u&&pc<0x2a8120u)||(pc>=0x2c2580u&&pc<0x2c2614u)||(pc>=0x2d4558u&&pc<0x2d4618u)||(pc>=0x2dddf0u&&pc<0x2dde08u))return 4;
 return 0;
}
static int owns(void *v,uint32_t pc){
 (void)v;return sound_group(pc)||nocturneNativeKernelOwns(pc)||(pc>=0x2dbea0u&&pc<0x2dbeb0u)||(pc>=0x2dbee0u&&pc<0x2dbef0u);
}
static uint32_t wrapper(NocturneWakeupMachine *m,uint64_t budget,NocturneWakeupStop *s){
 /* Exact original four-instruction leaf variants. Return at the real transfer
  * before a broader owner could execute the caller a second time. */
 uint32_t selector=0,part=0;memset(s,0,sizeof(*s));
 switch(m->pc){
 case 0x2dbea0u:selector=64;part=0;break;case 0x2dbea4u:part=1;break;case 0x2dbea8u:part=2;break;case 0x2dbeacu:part=3;break;
 case 0x2dbec0u:selector=66;part=0;break;case 0x2dbec4u:part=1;break;case 0x2dbec8u:part=2;break;case 0x2dbeccu:part=3;break;
 case 0x2dbee0u:selector=68;part=0;break;case 0x2dbee4u:part=1;break;case 0x2dbee8u:part=2;break;case 0x2dbeecu:part=3;break;
 default:s->outcome=NOCTURNE_WAKEUP_INPUT_DOMAIN;s->pc=m->pc;return s->outcome;
 }
 if(part==1u){s->outcome=NOCTURNE_NATIVE_SYSCALL;s->pc=m->pc;s->target=(uint64_t)m->gpr[3][0]|((uint64_t)m->gpr[3][1]<<32);return s->outcome;}
 if(budget<(part==2u?2u:1u)){s->outcome=NOCTURNE_WAKEUP_INSTRUCTION_LIMIT;s->pc=m->pc;return s->outcome;}
 if(part==0u){m->gpr[3][0]=selector;m->gpr[3][1]=0;++m->instructions;m->pc+=4;}
 else if(part==2u){m->instructions+=2;m->pc=m->gpr[31][0];}
 else{++m->instructions;m->pc+=4;}
 s->outcome=NOCTURNE_NATIVE_TRANSFER;s->pc=m->pc;s->target=(uint64_t)(int64_t)(int32_t)m->pc;return s->outcome;
}
static uint32_t body(void *v,NocturneWakeupMachine *m,const NocturneWakeupMemory *mem,uint64_t budget,NocturneWakeupStop *s){
 (void)v;
 if((m->pc>=0x2dbea0u&&m->pc<0x2dbeb0u)||(m->pc>=0x2dbec0u&&m->pc<0x2dbed0u)||(m->pc>=0x2dbee0u&&m->pc<0x2dbef0u))return wrapper(m,budget,s);
 switch(sound_group(m->pc)){
 case 1:return nocturneSoundPlayBankResume(m,mem,budget,s,&processor);
 case 2:return nocturneSoundEnqueueResume(m,mem,budget,s);
 case 3:return nocturneSoundThreadBootstrapResume(m,mem,budget,UINT32_MAX,s);
 case 4:return nocturneSoundThreadSupportResume(m,mem,budget,s);
 default:return nocturneNativeKernelBody(m,mem,budget,s);
 }
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
uint32_t nocturneBattleRewardPhaseRawConfigure(const NocturneWakeupMachine *before,const uint32_t *spans,uint32_t count,uint64_t budget){
 if(!before||!spans||!count||count>96u||!budget)return 0;
 for(uint32_t i=0;i<count;i++){
  uint32_t a=spans[2*i],n=spans[2*i+1];if(!n||a>=0x2000000u||n>0x2000000u-a)return 0;
  if(i&&a<spans[2*i-2]+spans[2*i-1])return 0;
 }
 state=*before;memcpy(ranges,spans,(size_t)count*8);range_count=count;limit=budget;configured=1;
 memset(&stopped,0,sizeof(stopped));memset(&counts,0,sizeof(counts));return 1;
}
const NocturneWakeupMachine *nocturneBattleRewardPhaseRawState(void){return &state;}
const NocturneWakeupStop *nocturneBattleRewardPhaseRawStop(void){return &stopped;}
uint32_t nocturneBattleRewardPhaseRawOwns(uint32_t pc){return(uint32_t)owns(0,pc);}
static void execute(uint32_t entry,uint32_t stop_pc,uint32_t pc,int syscall){
 const NocturneWakeupMemory mem={0,read_ram,write_ram};const NocturneNativeRouter router={0,owns,body};uint32_t outcome=NOCTURNE_NATIVE_TRANSFER;
 if(!configured)nocturneBattleRewardPhaseBoundary(pc,12u,entry);
 import_banks();state.pc=entry;
 if(syscall){
  outcome=nocturneNativeEnterSyscall(&state,state.instructions<limit?limit-state.instructions:0,&stopped);
  if(outcome==NOCTURNE_NATIVE_TRANSFER)++counts.syscalls;
 }
 if(outcome==NOCTURNE_NATIVE_TRANSFER)outcome=nocturneNativeRouteResume(&state,&mem,&router,state.instructions<limit?limit-state.instructions:0,stop_pc,&stopped,&counts);
 publish_banks();
 if(outcome!=NOCTURNE_NATIVE_TRANSFER||state.pc!=stop_pc)
  nocturneBattleRewardPhaseBoundary(state.pc,13u,((uint64_t)outcome<<32)|stop_pc);
}
void nocturneBattleRewardPhaseRawCall(uint32_t entry,uint32_t pc){
 uint32_t q[4];nocturneEffectHostCpuRead(31,q);execute(entry,q[0],pc,0);
}
void nocturneBattleRewardPhaseRawSyscall(uint32_t pc,uint64_t selector){
 uint32_t q[4];nocturneEffectHostCpuRead(3,q);
 if(selector!=((uint64_t)q[0]|((uint64_t)q[1]<<32)))nocturneBattleRewardPhaseBoundary(pc,9u,selector);
 if(pc!=0x2dbd94u&&pc!=0x2dbe84u&&pc!=0x2dbec4u&&pc!=0x2dbee4u)
  nocturneBattleRewardPhaseBoundary(pc,3u,selector);
 execute(pc,pc+4u,pc,1);
}

uint64_t nocturneBattleRewardPhaseRawKernel(uint64_t selector,uint32_t argc,const uint64_t *arguments){
 uint32_t pc,q[4];nocturneEffectHostCpuRead(3,q);
 if(argc!=1u||!arguments||selector!=((uint64_t)q[0]|((uint64_t)q[1]<<32)))nocturneBattleRewardPhaseBoundary(0,9u,selector);
 nocturneEffectHostCpuRead(4,q);if(arguments[0]!=((uint64_t)q[0]|((uint64_t)q[1]<<32)))nocturneBattleRewardPhaseBoundary(0,9u,selector);
 if(selector==64u)pc=0x2dbea4u;else if(selector==66u)pc=0x2dbec4u;else if(selector==68u)pc=0x2dbee4u;else nocturneBattleRewardPhaseBoundary(0,9u,selector);
 /* The native fixed wrapper already executed LI V1. Enter its actual SYS,
  * follow exception/service/ERET and real wrapper JR/NOP to current RA.
  * A switched continuation stops; no saved caller or service result is given. */
 nocturneEffectHostCpuRead(31,q);execute(pc,q[0],pc,1);
 nocturneEffectHostCpuRead(2,q);return(uint64_t)q[0]|((uint64_t)q[1]<<32);
}

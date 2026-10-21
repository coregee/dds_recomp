/* Real native callees share admitted phase699 banks/cache/raw-kernel state.
 * A child observation stop propagates unchanged; it never supplies a return.
 * The new task dispatcher validates callbacks against actual constructor
 * publications before invoking a complete body. No scheduler results feed. */
#include "battle_reward_lifecycle_transport.h"
#include "battle_reward_lifecycle_dependencies.h"
#include "fusion_core_transport.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#if defined(NOCTURNE_BATTLE_REWARD_LIFECYCLE_PROBE)
__declspec(dllimport) extern uint32_t g_scriptCoreFcsr,g_pathRotationVu[32][4];
#else
extern uint32_t g_scriptCoreFcsr,g_pathRotationVu[32][4];
#endif
void *nocturneEffectHostAddress(uint32_t);
static jmp_buf boundary;
static uint32_t observing;
static NocturneBattlePanelRendererStop stopped;
static uint64_t low(unsigned r){uint32_t w[4];nocturneEffectHostCpuRead(r,w);return(uint64_t)w[0]|((uint64_t)w[1]<<32);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveBattleRewardLifecycleNativeAddress(a),4);return v;}
static _Noreturn void stop(uint32_t pc,uint32_t operation,uint64_t target,uint32_t reason){
 stopped.version=1;stopped.reason=reason;stopped.pc=pc;stopped.operation=operation;stopped.target=target;stopped.sp=(uint32_t)low(29);stopped.ra=(uint32_t)low(31);
 if(observing)longjmp(boundary,1);exit(86);
}
static _Noreturn void propagate(void){stopped=*nocturneBattleRewardPhaseLastStop();if(observing)longjmp(boundary,1);exit(86);}
void *nocturneResolveBattleRewardLifecycleNativeAddress(uint32_t a){return nocturneEffectHostAddress(a);}
void nocturneBattleRewardLifecycleNativeCpuRead(unsigned r,uint32_t w[4]){nocturneEffectHostCpuRead(r,w);}
void nocturneBattleRewardLifecycleNativeCpuWrite(unsigned r,const uint32_t w[4]){nocturneEffectHostCpuWrite(r,w);}
void nocturneBattleRewardLifecycleNativeVuRead(unsigned r,uint32_t w[4]){if(r>=32u)stop(0,9,r,1);if(!r){w[0]=w[1]=w[2]=0;w[3]=0x3f800000u;}else memcpy(w,g_pathRotationVu[r],16);}
void nocturneBattleRewardLifecycleNativeVuWrite(unsigned r,const uint32_t w[4]){if(r>=32u)stop(0,9,r,1);if(r)memcpy(g_pathRotationVu[r],w,16);}
uint32_t nocturneBattleRewardLifecycleNativeFcsr(void){return g_scriptCoreFcsr;}
uint32_t nocturneBattleRewardLifecycleNativeStackPointer(void){uint32_t sp=nocturneFusionCoreStackPointer();if(low(29)!=(uint64_t)sp)stop(0,9,low(29),1);return sp;}
void nocturneBattleRewardLifecycleNativeSetStackPointer(uint32_t sp){uint32_t w[4];nocturneEffectHostCpuRead(29,w);w[0]=sp;w[1]=0;nocturneEffectHostCpuWrite(29,w);nocturneFusionCoreSetStackPointer(sp);}
_Noreturn void nocturneBattleRewardLifecycleNativeTrap(uint32_t code,uint32_t pc){stop(pc,8,code,2);}
static void call(uint32_t target,uint32_t pc){
 {size_t length=0;char value[2];if(!getenv_s(&length,value,sizeof(value),"NOCTURNE_BATTLE_REWARD_LIFECYCLE_TRACE")&&length)fprintf(stderr,"Lifecycle call %08x at%08x sp%08x a0%08x a1%08x a2%08x s0%08x\n",target,pc,(uint32_t)low(29),(uint32_t)low(4),(uint32_t)low(5),(uint32_t)low(6),(uint32_t)low(16));}
 (void)nocturneBattleRewardLifecycleNativeStackPointer();
 if(nocturneBattleRewardLifecycleNativeBody(target)||nocturneBattleRewardLifecycleDependencyBody(target))return;
 (void)pc;
 if(!nocturneBattleRewardPhaseRun(target))propagate();
}
void nocturneBattleRewardLifecycleNativeExternal(uint32_t target,uint32_t pc){call(target,pc);}
void nocturneBattleRewardLifecycleNativeIndirect(uint64_t target,uint32_t pc){
 uint32_t process=(uint32_t)low(4),loaded;
 if(low(31)!=(uint64_t)(pc+8u))stop(pc,9,target,1);
 switch(pc){
 case 0x100be0u:
  loaded=word(process+0x30u);
  if(target!=(uint64_t)(int64_t)(int32_t)loaded)break;
  if(loaded==0x24c378u||loaded==0x24c1d0u||loaded==0x297870u){call(loaded,pc);return;}
  break;
 case 0x100dd0u:
  loaded=word(process+0x34u);
  if(target!=(uint64_t)(int64_t)(int32_t)loaded)break;
  if(loaded==0x24c3c8u){call(loaded,pc);return;}
  break;
 default:break;
 }
 stop(pc,2,target,1);
}
uint32_t nocturneBattleRewardLifecycleRun(uint32_t entry){
 if(observing)stop(0,9,entry,1);memset(&stopped,0,sizeof(stopped));observing=1;
 if(setjmp(boundary)){observing=0;return 0;}call(entry,0);observing=0;return 1;
}
const NocturneBattlePanelRendererStop *nocturneBattleRewardLifecycleLastStop(void){return &stopped;}

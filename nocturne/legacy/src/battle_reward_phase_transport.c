/* Whole native owners over one actual bank. No allocator/service/results feed. */
#include "battle_reward_phase_transport.h"
#include "battle_reward_phase_support.h"
#include "battle_reward_phase_rows.h"
#include "battle_reward_phase_recycler.h"
#include "battle_reward_phase_frame.h"
#include "battle_reward_phase_dependencies.h"
#include "battle_reward_phase_texture.h"
#include "battle_action_reward_frames.h"
#include "battle_panel_owner.h"
#include "fusion_core_transport.h"
#include <string.h>
#if defined(NOCTURNE_BATTLE_REWARD_PHASE_PROBE)
__declspec(dllimport) extern uint32_t g_scriptCoreFcsr,g_pathRotationVu[32][4];
#else
extern uint32_t g_scriptCoreFcsr,g_pathRotationVu[32][4];
#endif
void *nocturneEffectHostAddress(uint32_t);
void nocturneEffectHostCpuRead(unsigned,uint32_t[4]);
void nocturneEffectHostCpuWrite(unsigned,const uint32_t[4]);
static uint64_t low(unsigned r){uint32_t w[4];nocturneEffectHostCpuRead(r,w);return(uint64_t)w[0]|((uint64_t)w[1]<<32);}
static void result(uint64_t v){uint32_t w[4];nocturneEffectHostCpuRead(2,w);w[0]=(uint32_t)v;w[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(2,w);}
void *nocturneResolveBattleRewardPhaseNativeAddress(uint32_t a){return nocturneEffectHostAddress(a);}
void nocturneBattleRewardPhaseNativeCpuRead(unsigned r,uint32_t w[4]){nocturneEffectHostCpuRead(r,w);}
void nocturneBattleRewardPhaseNativeCpuWrite(unsigned r,const uint32_t w[4]){nocturneEffectHostCpuWrite(r,w);}
void nocturneBattleRewardPhaseTextureCpuWrite(unsigned r,const uint32_t w[4]){nocturneEffectHostCpuWrite(r,w);if(r==29u)nocturneFusionCoreSetStackPointer(w[0]);}
void nocturneBattleRewardPhaseNativeVuRead(unsigned r,uint32_t w[4]){if(r>=32u)nocturneBattlePanelRendererAbort();if(!r){w[0]=w[1]=w[2]=0;w[3]=0x3f800000u;}else memcpy(w,g_pathRotationVu[r],16);}
void nocturneBattleRewardPhaseNativeVuWrite(unsigned r,const uint32_t w[4]){if(r>=32u)nocturneBattlePanelRendererAbort();if(r)memcpy(g_pathRotationVu[r],w,16);}
uint32_t nocturneBattleRewardPhaseNativeFcsr(void){return g_scriptCoreFcsr;}
uint32_t nocturneBattleRewardPhaseNativeStackPointer(void){uint32_t sp=nocturneFusionCoreStackPointer();if(low(29)!=(uint64_t)sp)nocturneBattlePanelRendererAbort();return sp;}
void nocturneBattleRewardPhaseNativeSetStackPointer(uint32_t sp){uint32_t w[4];nocturneEffectHostCpuRead(29,w);w[0]=sp;w[1]=0;nocturneEffectHostCpuWrite(29,w);nocturneFusionCoreSetStackPointer(sp);}
_Noreturn void nocturneBattleRewardPhaseNativeTrap(uint32_t code,uint32_t pc){nocturneBattlePanelRendererTrap(code,pc);}
_Noreturn void nocturneBattleRewardPhaseCompilerTrap(uint32_t code){nocturneBattlePanelRendererTrap(code,0);}
_Noreturn void nocturneBattleRewardPhaseBoundary(uint32_t pc,uint32_t kind,uint64_t value){nocturneBattlePanelRendererUnprovided(pc,kind,value);}
void nocturneBattleRewardPhaseNativeIndirect(uint64_t target,uint32_t pc){nocturneBattlePanelRendererIndirect(target,pc);}
void nocturneBattleRewardPhaseNativeExternal(uint32_t target,uint32_t pc){nocturneBattleRewardPhaseCall(target,pc);}
void nocturneBattleRewardPhaseCall(uint32_t target,uint32_t pc){
 (void)nocturneBattleRewardPhaseNativeStackPointer();
 if(target==0x1004f8u){nocturneBattleRewardPhaseFrameContextSwap();return;}
 if(nocturneBattleRewardPhaseNativeBody(target)||nocturneBattleRewardPhaseRecyclerBody(target)||nocturneBattleRewardPhaseRowsBody(target)||nocturneBattleRewardPhaseSupportBody(target)||nocturneBattleRewardPhaseDependencyBody(target))return;
 if(nocturneBattleRewardPhaseRawOwns(target)){nocturneBattleRewardPhaseRawCall(target,pc);return;}
 if(target==0x2acb78u||target==0x2797b0u){if(nocturneBattlePanelOwnerBody(target))return;nocturneBattlePanelRendererUnprovided(pc,1u,target);}
 switch(target){
 case 0x2abe08u:result(ps2BattleRewardPhaseTexture_002ABE08(low(4)));return;
 case 0x2aa9e0u:result(ps2BattleRewardPhaseTexture_002AA9E0(low(4)));return;
 /* Same actual fixed-bank formula routes already compared in reward165.
  * The returned scalar is the callee's real result; all its banks/RAM remain. */
 case 0x243f40u:result(ps2BattleActionFormula_00243F40(low(4),low(5)));return;
 case 0x242a88u:result(ps2BattleActionFormula_00242A88(low(4)));return;
 case 0x243ee0u:result(ps2BattleActionFormula_00243EE0(low(4),low(5)));return;
 case 0x2d18b0u:result(ps2BattleActionFormula_002D18B0(low(4),low(5)));return;
 case 0x246038u:result(ps2BattleActionReward_00246038(low(4)));return;
 default:nocturneBattleRewardPhaseBaseCall(target,pc);return;
 }
}
uint32_t nocturneBattleRewardPhaseRun(uint32_t entry){return nocturneBattlePanelRendererRun(entry);}
const NocturneBattlePanelRendererStop *nocturneBattleRewardPhaseLastStop(void){return nocturneBattlePanelRendererLastStop();}

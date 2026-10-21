/* Whole native owners over one actual bank. No allocator/service/results feed. */
#include "battle_reward_levelup_transport.h"
#include "battle_reward_levelup_support.h"
#include "battle_reward_levelup_dependencies.h"
#include "battle_reward_levelup_texture.h"
#include "battle_action_reward_frames.h"
#include "battle_panel_owner.h"
#include "fusion_core_transport.h"
#include <string.h>
#if defined(NOCTURNE_BATTLE_REWARD_LEVELUP_PROBE)
__declspec(dllimport) extern uint32_t g_scriptCoreFcsr,g_pathRotationVu[32][4];
#else
extern uint32_t g_scriptCoreFcsr,g_pathRotationVu[32][4];
#endif
void *nocturneEffectHostAddress(uint32_t);
void nocturneEffectHostCpuRead(unsigned,uint32_t[4]);
void nocturneEffectHostCpuWrite(unsigned,const uint32_t[4]);
static uint64_t low(unsigned r){uint32_t w[4];nocturneEffectHostCpuRead(r,w);return(uint64_t)w[0]|((uint64_t)w[1]<<32);}
static void result(uint64_t v){uint32_t w[4];nocturneEffectHostCpuRead(2,w);w[0]=(uint32_t)v;w[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(2,w);}
void *nocturneResolveBattleRewardLevelupNativeAddress(uint32_t a){return nocturneEffectHostAddress(a);}
void nocturneBattleRewardLevelupNativeCpuRead(unsigned r,uint32_t w[4]){nocturneEffectHostCpuRead(r,w);}
void nocturneBattleRewardLevelupNativeCpuWrite(unsigned r,const uint32_t w[4]){nocturneEffectHostCpuWrite(r,w);}
void nocturneBattleRewardLevelupTextureCpuWrite(unsigned r,const uint32_t w[4]){nocturneEffectHostCpuWrite(r,w);if(r==29u)nocturneFusionCoreSetStackPointer(w[0]);}
void nocturneBattleRewardLevelupNativeVuRead(unsigned r,uint32_t w[4]){if(r>=32u)nocturneBattlePanelRendererAbort();if(!r){w[0]=w[1]=w[2]=0;w[3]=0x3f800000u;}else memcpy(w,g_pathRotationVu[r],16);}
void nocturneBattleRewardLevelupNativeVuWrite(unsigned r,const uint32_t w[4]){if(r>=32u)nocturneBattlePanelRendererAbort();if(r)memcpy(g_pathRotationVu[r],w,16);}
uint32_t nocturneBattleRewardLevelupNativeFcsr(void){return g_scriptCoreFcsr;}
uint32_t nocturneBattleRewardLevelupNativeStackPointer(void){uint32_t sp=nocturneFusionCoreStackPointer();if(low(29)!=(uint64_t)sp)nocturneBattlePanelRendererAbort();return sp;}
void nocturneBattleRewardLevelupNativeSetStackPointer(uint32_t sp){uint32_t w[4];nocturneEffectHostCpuRead(29,w);w[0]=sp;w[1]=0;nocturneEffectHostCpuWrite(29,w);nocturneFusionCoreSetStackPointer(sp);}
_Noreturn void nocturneBattleRewardLevelupNativeTrap(uint32_t code,uint32_t pc){nocturneBattlePanelRendererTrap(code,pc);}
_Noreturn void nocturneBattleRewardLevelupCompilerTrap(uint32_t code){nocturneBattlePanelRendererTrap(code,0);}
_Noreturn void nocturneBattleRewardLevelupBoundary(uint32_t pc,uint32_t kind,uint64_t value){nocturneBattlePanelRendererUnprovided(pc,kind,value);}
void nocturneBattleRewardLevelupNativeIndirect(uint64_t target,uint32_t pc){nocturneBattlePanelRendererIndirect(target,pc);}
void nocturneBattleRewardLevelupNativeExternal(uint32_t target,uint32_t pc){nocturneBattleRewardLevelupCall(target,pc);}
void nocturneBattleRewardLevelupCall(uint32_t target,uint32_t pc){
 (void)nocturneBattleRewardLevelupNativeStackPointer();
 if(nocturneBattleRewardLevelupNativeBody(target)||nocturneBattleRewardLevelupSupportBody(target)||nocturneBattleRewardLevelupDependencyBody(target))return;
 if(nocturneBattleRewardLevelupRawOwns(target)){nocturneBattleRewardLevelupRawCall(target,pc);return;}
 if(target==0x2acb78u||target==0x2797b0u){if(nocturneBattlePanelOwnerBody(target))return;nocturneBattlePanelRendererUnprovided(pc,1u,target);}
 switch(target){
 case 0x2abe08u:result(ps2BattleRewardLevelupTexture_002ABE08(low(4)));return;
 case 0x2aa9e0u:result(ps2BattleRewardLevelupTexture_002AA9E0(low(4)));return;
 /* Same actual fixed-bank formula routes already compared in reward165.
  * The returned scalar is the callee's real result; all its banks/RAM remain. */
 case 0x243f40u:result(ps2BattleActionFormula_00243F40(low(4),low(5)));return;
 case 0x242a88u:result(ps2BattleActionFormula_00242A88(low(4)));return;
 case 0x243ee0u:result(ps2BattleActionFormula_00243EE0(low(4),low(5)));return;
 case 0x2d18b0u:result(ps2BattleActionFormula_002D18B0(low(4),low(5)));return;
 case 0x246038u:result(ps2BattleActionReward_00246038(low(4)));return;
 default:nocturneBattleRewardLevelupBaseCall(target,pc);return;
 }
}
uint32_t nocturneBattleRewardLevelupRun(uint32_t entry){return nocturneBattlePanelRendererRun(entry);}
const NocturneBattlePanelRendererStop *nocturneBattleRewardLevelupLastStop(void){return nocturneBattlePanelRendererLastStop();}

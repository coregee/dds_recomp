/* Native movement source on the real shared EE banks and ordinary RAM.
 * Existing typed owners remain semantic ABI boundaries. Complete native sound
 * and kernel owners preserve real frames, scheduling, cache and all banks.
 * No worker result, allocated handle, context bank or future RAM is supplied. */
#include "field_movement_encounter.h"
#include "field_movement_encounter_transport.h"
#include "fusion_core_transport.h"
#include "field_unit_lifetime_native.h"
#include "field_inf_controller_native.h"
#include "basic_pose.h"
#include "event_kuti.h"
#include "event_camera.h"
#include "world_arrays.h"
#include "scene_lookup.h"
#include "process_lists.h"
#include "process_shutdown.h"
#include "script_process.h"
#include "script_construction.h"
#include "field_sequence_queue.h"
#include "field_input_release.h"
#include "field_door_motion.h"
#include "field_skill.h"
#include "field_encounter.h"
#include "unit_progression.h"
#include "kernel_event_neighbors.h"
#include "moon_movement.h"
#include "screen_fade.h"
#include "battle_action_printf_frames.h"
uint64_t nocturneFieldMovementPrintf_002D4748(uint64_t,...);
#include "battle_presentation.h"
#include "sound_play_bank_native.h"
#include "sound_enqueue_native.h"
#include "sound_thread_bootstrap_native.h"
#include "sound_thread_support_native.h"
#include "native_kernel_router.h"
#include "custom_module_native.h"
#include "nocturne.h"
#include "field_neighbors.h"
#include "path_rotation.h"
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
void *nocturneEffectHostAddress(uint32_t);
void nocturneEffectHostCpuRead(unsigned,uint32_t[4]);
void nocturneEffectHostCpuWrite(unsigned,const uint32_t[4]);
uint32_t *nocturneEffectHostFpr(void);
uint64_t nocturneEffectHostLo(void),nocturneEffectHostHi(void);
void nocturneEffectHostSetHilo(uint64_t,uint64_t);
uint64_t nocturneBattleActionFormulaSecondaryLo(void),nocturneBattleActionFormulaSecondaryHi(void);
void nocturneBattleActionFormulaSecondaryWrite(uint64_t,uint64_t);
uint32_t nocturneRotationSqrtBits(uint32_t);
#if defined(NOCTURNE_FIELD_MOVEMENT_PROBE)
__declspec(dllimport) extern uint32_t g_pathRotationVu[32][4],g_pathRotationQ,g_pathRotationAcc[4],g_pathRotationAccOf[4],g_scriptCoreFcsr,g_nocturnePoolStatus,g_fusionSortScratchSP;
#else
extern uint32_t g_pathRotationVu[32][4],g_pathRotationQ,g_pathRotationAcc[4],g_pathRotationAccOf[4],g_scriptCoreFcsr,g_nocturnePoolStatus,g_fusionSortScratchSP;
#endif
static NocturneWakeupMachine raw;
static NocturneWakeupStop raw_stop;
static NocturneNativeRouteCounts raw_counts;
static NocturneIndexedCacheState cache;
static uint32_t spans[96][2],span_count,configured,observing;
static uint64_t raw_limit,stopped[4],telemetry[4];
static jmp_buf escape;
uint32_t nocturneFieldMovementUnitBody(uint32_t);
uint32_t nocturneFieldMovementCarrierBody(uint32_t);
uint32_t nocturneFieldMovementStateBody(uint32_t);
uint32_t nocturneFieldMovementConstructorBody(uint32_t);
void nocturneFieldMovementUnitExternal(uint32_t,uint32_t);
void nocturneFieldMovementUnitIndirect(uint64_t,uint32_t);
void nocturneFieldMovementUnitLegacyExternal(uint32_t,uint32_t);
void nocturneFieldMovementUnitLegacyIndirect(uint64_t,uint32_t);
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneEffectHostCpuRead(r,q);return(uint64_t)q[0]|((uint64_t)q[1]<<32);}
static uint64_t sx(uint32_t v){return(uint64_t)(int64_t)(int32_t)v;}
static void result(uint64_t v){uint32_t q[4];nocturneEffectHostCpuRead(2,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(2,q);}
static float fp(unsigned r){uint32_t v=nocturneEffectHostFpr()[r];float f;memcpy(&f,&v,4);return f;}
static _Noreturn void boundary(uint32_t kind,uint32_t pc,uint64_t selector){
 if(!observing)abort();stopped[0]=kind;stopped[1]=pc;stopped[2]=selector;stopped[3]=cpu(29);longjmp(escape,1);
}
void *nocturneResolveFieldMovementAddress(uint32_t a){return nocturneEffectHostAddress(a);}
void nocturneFieldMovementCpuRead(unsigned r,uint32_t q[4]){nocturneEffectHostCpuRead(r,q);}
void nocturneFieldMovementCpuWrite(unsigned r,const uint32_t q[4]){nocturneEffectHostCpuWrite(r,q);}
void nocturneFieldMovementVuRead(unsigned r,uint32_t q[4]){if(r>=32u)abort();if(r)memcpy(q,g_pathRotationVu[r],16);else{q[0]=q[1]=q[2]=0;q[3]=0x3f800000u;}}
void nocturneFieldMovementVuWrite(unsigned r,const uint32_t q[4]){if(r>=32u)abort();if(r)memcpy(g_pathRotationVu[r],q,16);}
uint32_t nocturneFieldMovementStackPointer(void){uint32_t sp=nocturneFusionCoreStackPointer();if(cpu(29)!=sp)abort();return sp;}
void nocturneFieldMovementSetStackPointer(uint32_t sp){uint32_t q[4];nocturneEffectHostCpuRead(29,q);q[0]=sp;q[1]=0;nocturneEffectHostCpuWrite(29,q);nocturneFusionCoreSetStackPointer(sp);}
uint32_t nocturneFieldMovementFcsr(void){return g_scriptCoreFcsr;}
uint32_t nocturneFieldMovementQ(void){return g_pathRotationQ;}
uint32_t nocturneFieldMovementVuSqrt(uint32_t bits,uint32_t pc){if(pc!=0x123ce4u)boundary(6u,pc,bits);return nocturneRotationSqrtBits(bits);}
void EE_ROT_Q_WRITE(uint32_t bits){g_pathRotationQ=bits;}
void nocturneFieldMovementAccRead(uint32_t q[4],uint32_t of[4]){memcpy(q,g_pathRotationAcc,16);memcpy(of,g_pathRotationAccOf,16);}
void nocturneFieldMovementAccWrite(const uint32_t q[4],const uint32_t of[4]){memcpy(g_pathRotationAcc,q,16);memcpy(g_pathRotationAccOf,of,16);}
_Noreturn void nocturneFieldMovementTrap(uint32_t code,uint32_t pc){boundary(4u,pc,code);}
static uint32_t physical(uint32_t a){
 if(a>=0xffff8000u)return 0x78000u+(a-0xffff8000u);
 if(a>=0x20000000u&&a<0x22000000u)return a-0x20000000u;
 return a>=0x80000000u&&a<0xc0000000u?a&0x1fffffffu:a;
}
static int backed(uint32_t a,uint32_t n){a=physical(a);for(uint32_t i=0;i<span_count;i++)if(a>=spans[i][0]&&a-spans[i][0]<=spans[i][1]&&n<=spans[i][1]-(a-spans[i][0]))return 1;return 0;}
static int read_ram(void *v,uint32_t a,void *p,uint32_t n){(void)v;if(!backed(a,n))return 0;a=physical(a);for(uint32_t i=0;i<n;i++)((uint8_t*)p)[i]=*(uint8_t*)nocturneEffectHostAddress(a+i);return 1;}
static int write_ram(void *v,uint32_t a,const void *p,uint32_t n){(void)v;if(!backed(a,n))return 0;a=physical(a);for(uint32_t i=0;i<n;i++)*(uint8_t*)nocturneEffectHostAddress(a+i)=((const uint8_t*)p)[i];return 1;}
static int cache_op(void *v,uint32_t pc,uint32_t op,uint32_t a){
 NocturneIndexedCachePreview preview;(void)v;
 if(nocturneIndexedCachePreview(&cache,pc,op,a,&preview))return 0;
 if(preview.writeback&&!write_ram(0,preview.writeback_address,preview.writeback_data,preview.writeback_bytes))return 0;
 return nocturneIndexedCacheCommit(&cache,&preview)==0;
}
static int taglo(void *v,uint32_t *out){(void)v;return nocturneIndexedCacheReadTagLo(&cache,out)==0;}
static const NocturneSoundBankProcessor processor={0,cache_op,taglo};
static int group(uint32_t p){
 if(nocturneSoundPlayBankOwns(p))return 1;
 if((p>=0x2c10e8u&&p<0x2c1234u)||(p>=0x2d43a4u&&p<0x2d4454u)||(p>=0x2dbdd0u&&p<0x2dbde0u))return 2;
 if((p>=0x2c0fc0u&&p<0x2c10e4u)||(p>=0x2dbca0u&&p<0x2dbcb0u)||(p>=0x2dbcc0u&&p<0x2dbcd0u)||(p>=0x2dbdc0u&&p<0x2dbdd0u))return 3;
 if((p>=0x2a8080u&&p<0x2a8120u)||(p>=0x2c2580u&&p<0x2c2614u)||(p>=0x2d4558u&&p<0x2d4618u)||(p>=0x2dbea0u&&p<0x2dbeb0u)||(p>=0x2dddf0u&&p<0x2dde08u))return 4;
 if((p>=0x2a89c0u&&p<0x2a89dcu)||(p>=0x2a89e0u&&p<0x2a8ba8u)||(p>=0x2d5d0cu&&p<0x2d5e44u))return 6;
 return nocturneNativeKernelOwns(p)?5:0;
}
static int owns(void *v,uint32_t p){(void)v;return group(p)!=0;}
static uint32_t resume(void *v,NocturneWakeupMachine *m,const NocturneWakeupMemory *mem,uint64_t budget,NocturneWakeupStop *s){
 (void)v;switch(group(m->pc)){
 case 1:return nocturneSoundPlayBankResume(m,mem,budget,s,&processor);
 case 2:return nocturneSoundEnqueueResume(m,mem,budget,s);
 case 3:return nocturneSoundThreadBootstrapResume(m,mem,budget,UINT32_MAX,s);
 case 4:return nocturneSoundThreadSupportResume(m,mem,budget,s);
 case 6:return nocturneCustomModuleResume(m,mem,budget,s);
 default:return nocturneNativeKernelBody(m,mem,budget,s);
 }
}
static void import_banks(void){
 for(unsigned i=0;i<32;i++)nocturneEffectHostCpuRead(i,raw.gpr[i]);
 memcpy(raw.fpr,nocturneEffectHostFpr(),sizeof(raw.fpr));raw.lo=nocturneEffectHostLo();raw.hi=nocturneEffectHostHi();
 raw.lo1=nocturneBattleActionFormulaSecondaryLo();raw.hi1=nocturneBattleActionFormulaSecondaryHi();raw.status=g_nocturnePoolStatus;raw.fcsr=g_scriptCoreFcsr;
}
static void publish_banks(void){
 for(unsigned i=1;i<32;i++)nocturneEffectHostCpuWrite(i,raw.gpr[i]);
 memcpy(nocturneEffectHostFpr(),raw.fpr,sizeof(raw.fpr));nocturneEffectHostSetHilo(raw.lo,raw.hi);nocturneBattleActionFormulaSecondaryWrite(raw.lo1,raw.hi1);
 g_nocturnePoolStatus=raw.status;g_scriptCoreFcsr=raw.fcsr;g_fusionSortScratchSP=raw.gpr[29][0];
}
static void raw_call(uint32_t entry,uint32_t pc){
 const NocturneWakeupMemory mem={0,read_ram,write_ram};const NocturneNativeRouter router={0,owns,resume};uint32_t outcome,stop_pc=(uint32_t)cpu(31);
 if(!configured)boundary(6u,pc,entry);import_banks();raw.pc=entry;
 outcome=nocturneNativeRouteResume(&raw,&mem,&router,raw.instructions<raw_limit?raw_limit-raw.instructions:0,stop_pc,&raw_stop,&raw_counts);
 publish_banks();++telemetry[0];telemetry[1]=raw_counts.syscalls;telemetry[2]=raw_counts.erets;telemetry[3]=raw.instructions;
 if(outcome!=NOCTURNE_NATIVE_TRANSFER||raw.pc!=stop_pc)boundary(13u,raw.pc,((uint64_t)outcome<<32)|stop_pc);
}
uint32_t nocturneFieldMovementRawStrlen(const char *source){
 uint32_t ra=(uint32_t)cpu(31);if(source!=(const char*)nocturneEffectHostAddress((uint32_t)cpu(4))||(ra!=0x2d6d10u&&ra!=0x2d6e20u))boundary(6u,ra,0x2d5d0cu);
 raw_call(0x2d5d0cu,ra-8u);return (uint32_t)cpu(2);
}
void nocturneFieldMovementUnitExternal(uint32_t target,uint32_t pc){
 if(group(target)){raw_call(target,pc);return;}
 if(nocturneFieldMovementConstructorBody(target))return; if(nocturneFieldMovementStateBody(target))return; if(nocturneFieldMovementCarrierBody(target))return;
 nocturneFieldMovementUnitLegacyExternal(target,pc);
}
void nocturneFieldMovementIndirect(uint64_t target,uint32_t pc){
 if(pc==0x100dd0u&&target==0x10a210u){if(!nocturneFieldMovementCarrierBody((uint32_t)target))boundary(3u,pc,target);return;}
 boundary(3u,pc,target);
}
void nocturneFieldMovementUnitIndirect(uint64_t target,uint32_t pc){
 if((pc==0x10dc78u&&(target==0x112b38u||target==0x10fc38u))||(pc==0x10dce4u&&target==0x112bb0u)){
  uint32_t basic=(uint32_t)cpu(4),record;memcpy(&record,nocturneEffectHostAddress(basic+16u),4);
  uint32_t actual;memcpy(&actual,nocturneEffectHostAddress(record+(pc==0x10dce4u?4u:0u)),4);
  if(actual!=(uint32_t)target)boundary(3u,pc,target);
  if(!nocturneFieldMovementUnitBody((uint32_t)target)&&!nocturneFieldMovementConstructorBody((uint32_t)target))boundary(3u,pc,target);return;
 }
 nocturneFieldMovementUnitLegacyIndirect(target,pc);
}
uint32_t nocturneFieldMovementConfigure(const NocturneWakeupMachine *before,const NocturneIndexedCacheConfig *input,const uint32_t *ranges,uint32_t n,uint64_t budget){
 if(!before||!input||!ranges||!n||n>96u||!budget)return 0;
 for(uint32_t i=0;i<n;i++){uint32_t a=ranges[2*i],size=ranges[2*i+1];if(!size||a>=0x2000000u||size>0x2000000u-a)return 0;if(i&&a<ranges[2*i-2]+ranges[2*i-1])return 0;}
 if(nocturneIndexedCacheInit(&cache,input))return 0;raw=*before;raw.instructions=raw.sync_p=0;memcpy(spans,ranges,(size_t)n*8);span_count=n;raw_limit=budget;
 memset(&raw_stop,0,sizeof(raw_stop));memset(&raw_counts,0,sizeof(raw_counts));memset(telemetry,0,sizeof(telemetry));configured=1;return 1;
}
const uint64_t *nocturneFieldMovementLastStop(void){return stopped;}
const NocturneWakeupMachine *nocturneFieldMovementRawState(void){return &raw;}
const NocturneIndexedCacheState *nocturneFieldMovementCacheState(void){return &cache;}
const uint64_t *nocturneFieldMovementRouteCounts(void){return telemetry;}
void nocturneFieldMovementCall(uint32_t target,uint32_t pc){
 (void)nocturneFieldMovementStackPointer();
 if(group(target)){raw_call(target,pc);return;}
 if(nocturneFieldMovementConstructorBody(target))return; if(nocturneFieldMovementStateBody(target))return; if(nocturneFieldMovementUnitBody(target))return;
 if(nocturneFieldMovementCarrierBody(target))return;
 switch(target){
 case 0x101898u:result(dds3SearchProcessName(cpu(4)));return;
 case 0x101738u:result(dds3KillProcess(cpu(4),cpu(5)));return;
 case 0x102848u:result(ps2FieldSequenceQueue_00102848(cpu(4),cpu(5),cpu(6),cpu(7)));return;
 case 0x104fe0u:dds3FadeIn(cpu(4),cpu(5),cpu(6),cpu(7));return;
 case 0x1097e8u:ps2ScriptDiagnosticDisabled(cpu(4),cpu(5),cpu(6),cpu(7));return;
 case 0x109f08u:if(!nocturneFieldInfControllerNativeBody(target))boundary(3u,pc,target);return;
 case 0x10a078u:result(scrSearchScriptName(cpu(4)));return;
 case 0x10ddf0u:dds3OnPoseSetFlag(cpu(4),cpu(5));return;
 case 0x10dea8u:dds3SetPosPoseSet(cpu(4),cpu(5));return;
 case 0x10ded8u:dds3SetRotPoseSet(cpu(4),cpu(5));return;
 case 0x10df38u:dds3GetPosPoseSetMCR(cpu(4));return;
 case 0x10df50u:dds3GetRotPoseSet(cpu(4));return;
 case 0x10e548u:result(dds3GetActiveScene());return;
 case 0x10e588u:result(dds3GetControlScene());return;
 case 0x10f1f8u:case 0x10f4d8u:case 0x110350u:case 0x125cb8u:case 0x12c360u:
  if(!nocturneFieldInfControllerNativeBody(target))boundary(3u,pc,target);return;
 case 0x10f208u:result(dds3SearchSceneBasic(cpu(4),cpu(5),cpu(6)));return;
 case 0x110138u:dds3ObjectBaseOnFlag(cpu(4),cpu(5));return;
 case 0x1225e8u:result(ps2FieldGetUnitControl_001225E8());return;
 case 0x122718u:result(ps2FieldReleaseUnitPad_00122718());return;
 case 0x125990u:fldSeqOnFlag((uint32_t)cpu(4));return;
 case 0x1259c0u:result(sx((uint32_t)(int32_t)fldSeqCheckFlag((uint32_t)cpu(4))));return;
 case 0x1259e0u:fldProcOffFlag((uint32_t)cpu(4));return;
 case 0x1259f8u:result(sx((uint32_t)(int32_t)fldProcCheckFlag((uint32_t)cpu(4))));return;
 case 0x1e9998u:result(evtGetAgeOfMoon());return;
 case 0x1e99d0u:evtSetAgeOfMoon((int32_t)cpu(4));return;
 case 0x123828u:fldEsutoMaClearMsg();return;
 case 0x123760u:fldRiberaMaClearMsg();return;
 case 0x1236a0u:fldRifutoMaClearMsg();return;
 case 0x1234b0u:ps2FieldLightClearMessage();return;
 case 0x1e0ed0u:evtBitOn((int32_t)cpu(4));return;
 case 0x1e0f50u:result(sx(evtBitCheck((int32_t)cpu(4))));return;
 case 0x1e99c0u:result(evtGetAgeOfMoon16());return;
 case 0x1eac20u:evtMoonAddMove(fp(12));return;
 case 0x244a38u:ps2FieldSkillPartyStatusDamage_00244A38(cpu(4));return;
 case 0x2455b8u:ps2UnitRecoverFieldParty_002455B8();return;
 case 0x2456d0u:result(ps2UnitFindTreasureSkillOwner_002456D0());return;
 case 0x28cca8u:result(ps2FieldEncounterAdvance_0028CCA8(cpu(4),fp(12)));return;
 case 0x28cfb0u:ps2FieldEncounterReset_0028CFB0();return;
 case 0x2c0600u:sdfQuatToMatrix();return;
 case 0x2c04e8u:ps2QuaternionNormalize();return;
 case 0x2c0258u:nocturneEffectHostFpr()[0]=ps2FieldDoorAtan2Bits_002C0258(nocturneEffectHostFpr()[12],nocturneEffectHostFpr()[13]);return;
 case 0x2c0b60u:nocturneEffectHostFpr()[0]=ps2FieldDoorHeadingBits_002C0B60();return;
 case 0x2d4748u:result(nocturneFieldMovementPrintf_002D4748(cpu(4)));return;
 default:boundary(3u,pc,target);
 }
}
uint32_t nocturneFieldMovementRun(uint32_t entry){
 if(observing)abort();memset(stopped,0,sizeof(stopped));observing=1;
 if(setjmp(escape)){observing=0;return 0;}
 if(!nocturneFieldMovementBody(entry)){
  if(entry==0x112a40u||entry==0x1e39e8u){if(!nocturneFieldMovementUnitBody(entry))boundary(3u,entry,entry);}
  else nocturneFieldMovementCall(entry,entry);
 }
 observing=0;return 1;
}

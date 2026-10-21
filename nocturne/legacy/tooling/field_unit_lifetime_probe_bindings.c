/* Real598 banks/RAM and existing whole callees. The original type table is
 * never changed. New type5 callbacks execute complete native bodies. */
#include "field_unit_lifetime_native.h"
#include "fusion_core_transport.h"
#include "basic_creation.h"
#include "basic_pose.h"
#include "world_arrays.h"
#include "scene_lookup.h"
#include "path_control.h"
#include "model_cleanup.h"
#include "model_loading_completion.h"
#include "field_inf_controller_native.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "battle_action_printf_frames.h"
#include "ps2_memory.h"
#include <stdlib.h>
#include <string.h>
void *nocturneEffectHostAddress(uint32_t address);
void nocturneEffectHostCpuRead(unsigned reg,uint32_t words[4]);
void nocturneEffectHostCpuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneEffectHostOriginalAddress(const void *pointer);
#if defined(NOCTURNE_FIELD_UNIT_LIFETIME_PROBE)
__declspec(dllimport) extern uint32_t g_pathRotationVu[32][4],g_scriptCoreFcsr;
#else
extern uint32_t g_pathRotationVu[32][4],g_scriptCoreFcsr;
#endif
static uint64_t cpu(unsigned reg){uint32_t words[4];nocturneEffectHostCpuRead(reg,words);return(uint64_t)words[0]|((uint64_t)words[1]<<32);}
static void result(uint64_t value){uint32_t words[4];nocturneEffectHostCpuRead(2,words);words[0]=(uint32_t)value;words[1]=(uint32_t)(value>>32);nocturneEffectHostCpuWrite(2,words);}
static uint32_t word(uint32_t address){uint32_t value;memcpy(&value,nocturneEffectHostAddress(address),4);return value;}
void nocturneFieldUnitLifetimeNativeCpuRead(unsigned r,uint32_t words[4]){nocturneEffectHostCpuRead(r,words);}
void nocturneFieldUnitLifetimeNativeCpuWrite(unsigned r,const uint32_t words[4]){nocturneEffectHostCpuWrite(r,words);}
void nocturneFieldUnitLifetimeNativeVuRead(unsigned r,uint32_t words[4]){if(r>=32)abort();if(!r){words[0]=words[1]=words[2]=0;words[3]=0x3f800000u;}else memcpy(words,g_pathRotationVu[r],16);}
void nocturneFieldUnitLifetimeNativeVuWrite(unsigned r,const uint32_t words[4]){if(r>=32)abort();if(r)memcpy(g_pathRotationVu[r],words,16);}
void *nocturneResolveFieldUnitLifetimeNativeAddress(uint32_t a){return nocturneEffectHostAddress(a);}
uint32_t nocturneFieldUnitLifetimeNativeStackPointer(void){uint32_t sp=nocturneFusionCoreStackPointer();if(cpu(29)!=sp)abort();return sp;}
void nocturneFieldUnitLifetimeNativeSetStackPointer(uint32_t sp){uint32_t words[4];nocturneEffectHostCpuRead(29,words);words[0]=sp;words[1]=0;nocturneEffectHostCpuWrite(29,words);nocturneFusionCoreSetStackPointer(sp);}
uint32_t nocturneFieldUnitLifetimeNativeFcsr(void){return g_scriptCoreFcsr;}
_Noreturn void nocturneFieldUnitLifetimeNativeTrap(uint32_t code,uint32_t pc){(void)pc;nocturneFusionCoreArithmeticTrap(code);}
void nocturneFieldUnitLifetimeNativeExternal(uint32_t target,uint32_t pc){
 (void)pc;(void)nocturneFieldUnitLifetimeNativeStackPointer();
 switch(target){
 case 0x10dd38u:result(dds3InitPoseSet(cpu(4)));return;
 case 0x10ddb0u:dds3FreePoseSet(cpu(4));return;
 case 0x10de50u:dds3BackupPoseSet(cpu(4));return;
 case 0x10dea8u:dds3SetPosPoseSet(cpu(4),cpu(5));return;
 case 0x10ded8u:dds3SetRotPoseSet(cpu(4),cpu(5));return;
 case 0x10e588u:result(dds3GetControlScene());return;
 case 0x10e748u:dds3FreeBasicArrayHandle(cpu(4));return;
 case 0x10ea38u:result(dds3SetSearchNextBasicArray(cpu(4),cpu(5)));return;
 case 0x10ea90u:result(dds3AddBasicArray(cpu(4),cpu(5)));return;
 case 0x10ebc8u:result(dds3GetBasicArrayCount(cpu(4)));return;
 case 0x10ebe0u:result(dds3SetBasicArray(cpu(4),cpu(5)));return;
 case 0x10ec20u:result(dds3GetBasicArray(cpu(4)));return;
 case 0x10ec58u:result(dds3SetFirstBasicArray(cpu(4)));return;
 case 0x10f270u:result(ps2FieldInfControllerNative_0010F270(cpu(4),cpu(5)));return;
 case 0x10f970u:result(dds3AreaBasicTypeToItemType(cpu(4)));return;
 case 0x10fa68u:dds3AreaBasicReleaseItem(cpu(4),cpu(5));return;
 case 0x10fab8u:result(dds3AreaBasicGetItemArray(cpu(4),cpu(5)));return;
 case 0x10ffe0u:result(dds3ObjectBaseInitControlWorkData(cpu(4)));return;
 case 0x110138u:dds3ObjectBaseOnFlag(cpu(4),cpu(5));return;
 case 0x110298u:result(dds3ObjectBaseSetControlBasicType(cpu(4),cpu(5),cpu(6)));return;
 case 0x110300u:result(dds3ObjectBaseGetControlBasic(cpu(4),cpu(5)));return;
 case 0x112168u:result(dds3ObjectBaseCreateMover(cpu(4)));return;
 case 0x1122a0u:result(dds3GetBaseControlWorkData(cpu(4)));return;
 case 0x1dd220u:ps2ModelContextRelease(cpu(4));return;
 case 0x1e3af0u:result(evtDeleteUnitHandle(cpu(4)));return;
 case 0x2a8af8u:result(ps2PoolAllocate((uint32_t)cpu(4)));return;
 case 0x2a8bd8u:ps2PoolRelease((uint32_t)cpu(4));return;
 case 0x2b0648u:ps2ModelRootRelease(cpu(4),cpu(5),cpu(6));return;
 case 0x2b3c60u:sdfMotionCtrlrFree(cpu(4));return;
 case 0x2d4558u:{void *value=ps2Memset(nocturneEffectHostAddress((uint32_t)cpu(4)),(int)cpu(5),(uint32_t)cpu(6));result((uint64_t)(int64_t)(int32_t)nocturneEffectHostOriginalAddress(value));return;}
 case 0x2d4748u:result(ps2BattleActionPrintf_002D4748(cpu(4)));return;
 default:abort();
 }
}
uint32_t nocturneFieldUnitLifetimeNativeRun(uint32_t entry){if(!nocturneFieldUnitLifetimeNativeBody(entry))nocturneFieldUnitLifetimeNativeExternal(entry,0);return 1;}
const uint64_t *nocturneFieldUnitLifetimeNativeLastStop(void){static const uint64_t none[4]={0,0,0,0};return none;}
void nocturneFieldUnitLifetimeNativeIndirect(uint64_t target,uint32_t pc){
 uint32_t basic=(uint32_t)cpu(4),record=word(basic+16);(void)nocturneFieldUnitLifetimeNativeStackPointer();
 if(pc==0x10dc78u){
  if(word(record)!=(uint32_t)target)abort();
  if(target==0x112b38u){if(!nocturneFieldUnitLifetimeNativeBody((uint32_t)target))abort();return;}
  if(target==0x10fc38u){result(dds3MoverBasicConstructor(cpu(4)));return;}
  if(target==0x112370u){result(dds3CameraObjectBasicConstructor(cpu(4)));return;}
  if(target==0x10e288u){result(ps2WorldBasicConstructor(cpu(4)));return;}
 }else if(pc==0x10dce4u){
  if(word(record+4)!=(uint32_t)target)abort();
  if(target==0x112bb0u){if(!nocturneFieldUnitLifetimeNativeBody((uint32_t)target))abort();return;}
  if(target==0x10fc78u){dds3MoverBasicDestructor(cpu(4));return;}
  if(target==0x10e2f8u){ps2WorldBasicDestructor(cpu(4));return;}
 }abort();
}

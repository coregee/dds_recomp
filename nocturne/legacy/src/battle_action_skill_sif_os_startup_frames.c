/* Whole original three OS leaves and EnableDmac wrapper (38 operations).
 * Native48B frame and shared Status/CPU carry; no supplied OS or DMA result. */
#include "battle_action_skill_sif_os_startup_frames.h"
#include "effect_host_bindings.h"
#include "effect_billboard_dependency_frames.h"
#include "material_fiveword_pool.h"
#include <stdlib.h>
#include <string.h>
extern uint64_t nocturneLibcStreamKernel(uint64_t selector,unsigned argc,const uint64_t *arguments);
extern void *nocturneResolveBattleActionConsumerAddress(uint32_t address);
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t value){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)value;q[1]=(uint32_t)(value>>32);nocturneEffectHostCpuWrite(r,q);}
static uint64_t sx(uint32_t value){return (uint64_t)(int64_t)(int32_t)value;}
static uint32_t ea(int32_t offset){return (uint32_t)cpu(29)+(uint32_t)offset;}
static void save(unsigned r,uint32_t address){uint64_t value=cpu(r);memcpy(nocturneResolveBattleActionConsumerAddress(address),&value,8);}
static void restore(unsigned r,uint32_t address){uint64_t value;memcpy(&value,nocturneResolveBattleActionConsumerAddress(address),8);set(r,value);}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
static void body_002dbc00(void){
    uint64_t incoming=cpu(31);nocturneEffectAxisNoteEntry(0x002dbc00u);
    /* 002dbc00: li v1,0x16 */ set(3,22u);
    /* 002dbc04: syscall 0 */ {uint64_t args[1]={cpu(4)};set(2,nocturneLibcStreamKernel(cpu(3),1,args));}
    /* 002dbc08: jr ra */ {uint64_t target=cpu(31);/* delay 002dbc0c */ checkReturn(target,incoming);}
}
static void body_002dc2a0(void){
    uint64_t incoming=cpu(31);nocturneEffectAxisNoteEntry(0x002dc2a0u);
    /* 002dc2a0: li v1,0x79 */ set(3,121u);
    /* 002dc2a4: syscall 0 */ {uint64_t args[2]={cpu(4),cpu(5)};set(2,nocturneLibcStreamKernel(cpu(3),2,args));}
    /* 002dc2a8: jr ra */ {uint64_t target=cpu(31);/* delay 002dc2ac */ checkReturn(target,incoming);}
}
static void body_002dc2b0(void){
    uint64_t incoming=cpu(31);nocturneEffectAxisNoteEntry(0x002dc2b0u);
    /* 002dc2b0: li v1,0x7a */ set(3,122u);
    /* 002dc2b4: syscall 0 */ {uint64_t args[1]={cpu(4)};set(2,nocturneLibcStreamKernel(cpu(3),1,args));}
    /* 002dc2b8: jr ra */ {uint64_t target=cpu(31);/* delay 002dc2bc */ checkReturn(target,incoming);}
}
static void body_002dcab8(void){
    uint64_t incoming=cpu(31);nocturneEffectAxisNoteEntry(0x002dcab8u);
    /* 002dcab8: addiu sp,sp,-0x30 */ set(29,sx((uint32_t)cpu(29)-0x30u));
    /* 002dcabc: sd s1,0x10(sp) */ save(17,ea(0x10));
    /* 002dcac0: sd ra,0x20(sp) */ save(31,ea(0x20));
    /* 002dcac4: move s1,a0 */ set(17,cpu(4));
    /* 002dcac8: sd s0,0(sp) */ save(16,ea(0));
    /* 002dcacc: mfc0 s0,Status */ set(16,sx(EE_SYSTEM_READ_STATUS()));
    /* 002dcad0: lui v0,1 */ set(2,0x10000u);
    /* 002dcad4: and s0,s0,v0 */ set(16,cpu(16)&cpu(2));
    /* 002dcad8: beq s0,zero,002dcae8 */ {int taken=cpu(16)==0;/* delay 002dcadc */ if(taken)goto L_002dcae8;}
    /* 002dcae0: jal 002e4070 */ set(31,0x002dcae8u);/* delay 002dcae4 */ (void)ps2EffectKernelDisableInterrupts_002E4070();
L_002dcae8:;
    /* 002dcae8: jal 002dbc00 */ set(31,0x002dcaf0u);/* delay 002dcaec */ set(4,cpu(17));body_002dbc00();
    /* 002dcaf0: move s1,v0 */ set(17,cpu(2));
    /* 002dcaf4: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002dcaf8: beq s0,zero,002dcb0c */ {int taken=cpu(16)==0;/* delay 002dcafc */ set(2,cpu(17));if(taken)goto L_002dcb0c;}
    /* 002dcb00: jal 002e40b8 */ set(31,0x002dcb08u);/* delay 002dcb04 */ (void)ps2EffectKernelEnableInterrupts_002E40B8();
    /* 002dcb08: move v0,s1 */ set(2,cpu(17));
L_002dcb0c:;
    /* 002dcb0c: ld ra,0x20(sp) */ restore(31,ea(0x20));
    /* 002dcb10: ld s1,0x10(sp) */ restore(17,ea(0x10));
    /* 002dcb14: ld s0,0(sp) */ restore(16,ea(0));
    /* 002dcb18: jr ra */ {uint64_t target=cpu(31);/* delay 002dcb1c */ set(29,sx((uint32_t)cpu(29)+0x30u));checkReturn(target,incoming);}
}
uint32_t nocturneBattleActionSkillSifOsStartupBody(uint32_t entry){
    switch(entry){case 0x002dbc00u:body_002dbc00();return 1;case 0x002dc2a0u:body_002dc2a0();return 1;case 0x002dc2b0u:body_002dc2b0();return 1;case 0x002dcab8u:body_002dcab8();return 1;default:return 0;}
}

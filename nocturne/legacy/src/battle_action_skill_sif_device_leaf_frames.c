/* Whole original eight instructions; no OS reply or guest RAM writer. */
#include "battle_action_skill_sif_device_leaf_frames.h"
#include "effect_host_bindings.h"
#include <stdlib.h>
extern uint64_t nocturneLibcStreamKernel(uint64_t selector,unsigned argc,const uint64_t *arguments);
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneEffectHostCpuWrite(r,q);}
static void body_002dbbb0(void){
    uint64_t incoming=cpu(31);nocturneEffectAxisNoteEntry(0x002dbbb0u);
    /* 002dbbb0: li v1,0x12 */ set(3,18u);
    /* 002dbbb4: syscall 0 */ {uint64_t args[3]={cpu(4),cpu(5),cpu(6)};set(2,nocturneLibcStreamKernel(cpu(3),3,args));}
    /* 002dbbb8: jr ra; 002dbbbc: nop */ if((uint32_t)cpu(31)!=(uint32_t)incoming)abort();
}
static void body_002dc280(void){
    uint64_t incoming=cpu(31);nocturneEffectAxisNoteEntry(0x002dc280u);
    /* 002dc280: li v1,0x78 */ set(3,120u);
    /* 002dc284: syscall 0 */ set(2,nocturneLibcStreamKernel(cpu(3),0,NULL));
    /* 002dc288: jr ra; 002dc28c: nop */ if((uint32_t)cpu(31)!=(uint32_t)incoming)abort();
}
uint32_t nocturneBattleActionSkillSifDeviceLeafBody(uint32_t entry){
    switch(entry){case 0x002dbbb0u:body_002dbbb0();return 1;case 0x002dc280u:body_002dc280();return 1;default:return 0;}
}

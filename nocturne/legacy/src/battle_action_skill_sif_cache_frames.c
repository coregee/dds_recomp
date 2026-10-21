/* Whole original002DE458:43 operations/172 bytes, no guest stack frame.
 * Actual shared-bank scalar carry and explicit cache boundary; no RAM mutation. */
#include "battle_action_skill_sif_cache_frames.h"
#include "effect_host_bindings.h"
#include "material_fiveword_pool.h"
#include <stdlib.h>
static uint64_t cpu(unsigned r){uint32_t q[4];if(!r)return 0;nocturneEffectHostCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned r,uint64_t value){uint32_t q[4];if(!r)return;nocturneEffectHostCpuRead(r,q);q[0]=(uint32_t)value;q[1]=(uint32_t)(value>>32);nocturneEffectHostCpuWrite(r,q);}
static uint64_t sx(uint32_t value){return (uint64_t)(int64_t)(int32_t)value;}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}
static void body_002de458(void){
    uint64_t incoming=cpu(31);int finishGroups=0;nocturneEffectAxisNoteEntry(0x002de458u);
    /* 002de458: lui t9,0xffff */ set(25,sx(0xffff0000u));
    /* 002de45c: ori t9,t9,0xffc0 */ set(25,cpu(25)|UINT64_C(0xffc0));
    /* 002de460: blez a1,002de4fc */ {int taken=cpu(5)==0||(cpu(5)>>63)!=0;/* delay 002de464 */ set(10,sx((uint32_t)cpu(4)+(uint32_t)cpu(5)));if(taken)goto L_002de4fc;}
    /* 002de468: and t0,a0,t9 */ set(8,cpu(4)&cpu(25));
    /* 002de46c: addiu t2,t2,-1 */ set(10,sx((uint32_t)cpu(10)-1u));
    /* 002de470: and t1,t2,t9 */ set(9,cpu(10)&cpu(25));
    /* 002de474: subu t2,t1,t0 */ set(10,sx((uint32_t)cpu(9)-(uint32_t)cpu(8)));
    /* 002de478: srl t3,t2,6 */ set(11,sx((uint32_t)cpu(10)>>6));
    /* 002de47c: addiu t3,t3,1 */ set(11,sx((uint32_t)cpu(11)+1u));
    /* 002de480: andi t1,t3,7 */ set(9,cpu(11)&7u);
    /* 002de484: beq t1,zero,002de4a8 */ {int taken=cpu(9)==0;/* delay 002de488 */ set(10,sx((uint32_t)cpu(11)>>3));if(taken)goto L_002de4a8;}
L_002de48c:;
    /* 002de48c: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de490: cache DHWBIN,0(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de490u,0x18u,(uint64_t)(uint32_t)cpu(8));
    /* 002de494: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de498: addiu t1,t1,-1 */ set(9,sx((uint32_t)cpu(9)-1u));
    /* 002de49c: nop */
    /* 002de4a0: bgtz t1,002de48c */ {int taken=cpu(9)!=0&&(cpu(9)>>63)==0;/* delay 002de4a4 */ set(8,sx((uint32_t)cpu(8)+0x40u));if(taken)goto L_002de48c;}
L_002de4a8:;
    /* 002de4a8: beq t2,zero,002de4fc */ finishGroups=cpu(10)==0;
L_002de4ac:;
    /* delay 002de4ac */ set(10,sx((uint32_t)cpu(10)-1u));if(finishGroups)goto L_002de4fc;
    /* 002de4b0: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4b4: cache DHWBIN,0(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de4b4u,0x18u,(uint64_t)(uint32_t)cpu(8));
    /* 002de4b8: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4bc: cache DHWBIN,0x40(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de4bcu,0x18u,(uint64_t)((uint32_t)cpu(8)+0x40u));
    /* 002de4c0: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4c4: cache DHWBIN,0x80(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de4c4u,0x18u,(uint64_t)((uint32_t)cpu(8)+0x80u));
    /* 002de4c8: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4cc: cache DHWBIN,0xc0(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de4ccu,0x18u,(uint64_t)((uint32_t)cpu(8)+0xc0u));
    /* 002de4d0: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4d4: cache DHWBIN,0x100(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de4d4u,0x18u,(uint64_t)((uint32_t)cpu(8)+0x100u));
    /* 002de4d8: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4dc: cache DHWBIN,0x140(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de4dcu,0x18u,(uint64_t)((uint32_t)cpu(8)+0x140u));
    /* 002de4e0: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4e4: cache DHWBIN,0x180(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de4e4u,0x18u,(uint64_t)((uint32_t)cpu(8)+0x180u));
    /* 002de4e8: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4ec: cache DHWBIN,0x1c0(t0) */ nocturneBattleActionSkillSifReadyCacheValue(0x002de4ecu,0x18u,(uint64_t)((uint32_t)cpu(8)+0x1c0u));
    /* 002de4f0: sync 0 */ EE_SYSTEM_SYNC(0u);
    /* 002de4f4: bgtz t2,002de4ac */ {int taken=cpu(10)!=0&&(cpu(10)>>63)==0;/* delay 002de4f8 */ set(8,sx((uint32_t)cpu(8)+0x200u));if(taken)goto L_002de4ac;}
L_002de4fc:;
    /* 002de4fc: jr ra */ {uint64_t target=cpu(31);/* delay 002de500 */ checkReturn(target,incoming);}
}
uint32_t nocturneBattleActionSkillSifCacheBody(uint32_t entry){if(entry!=0x002de458u)return 0;body_002de458();return 1;}

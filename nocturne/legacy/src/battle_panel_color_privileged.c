/* Two whole original privileged leaves, zero new identity credit.
 * Genuine instruction hooks are deliberately unresolved, never replaced by
 * an old Status constant, success reply or assumed immediate DI completion. */
#include "battle_panel_color_privileged.h"
#include "battle_panel_color_native.h"
#include <stdlib.h>
static uint64_t cpu(unsigned r){uint32_t q[4];nocturneBattlePanelColorCpuRead(r,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(unsigned r,uint64_t v){uint32_t q[4];if(!r)return;nocturneBattlePanelColorCpuRead(r,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneBattlePanelColorCpuWrite(r,q);}
static void checkReturn(uint64_t actual,uint64_t incoming){if((uint32_t)actual!=(uint32_t)incoming)abort();}

static void body_002e4070(void){uint64_t incoming=cpu(31);
/* 002e4070: mfc0 v1,Status */ set(3,sx(nocturneBattlePanelColorReadStatus(UINT32_C(0x002e4070))));
/* 002e4074: lui v0,0x1 */ set(2,sx(UINT32_C(0x00010000)));
/* 002e4078: and v1,v1,v0 */ set(3,cpu(3)&cpu(2));
/* 002e407c: beq v1,zero,0x002e40ac */ {int taken=(cpu(3)==cpu(0));/* delay 002e4080 */ set(4,cpu(0)<cpu(3));if(taken)goto L_002e40ac;}
/* 002e4084: nop  */ 
L_002e4088:;
/* 002e4088: di  */ nocturneBattlePanelColorDisableInterrupts(UINT32_C(0x002e4088));
/* 002e408c: sync 0x10 */ nocturneBattlePanelColorSync(16u,UINT32_C(0x002e408c));
/* 002e4090: mfc0 v0,Status */ set(2,sx(nocturneBattlePanelColorReadStatus(UINT32_C(0x002e4090))));
/* 002e4094: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 002e4098: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002e409c: bne v0,zero,0x002e4088 */ {int taken=(cpu(2)!=cpu(0));/* delay 002e40a0 */ if(taken)goto L_002e4088;}
/* 002e40a4: jr ra */ {uint64_t target=cpu(31);/* delay 002e40a8 */ set(2,cpu(4));checkReturn(target,incoming);return;}
L_002e40ac:;
/* 002e40ac: move a0,zero */ set(4,cpu(0));
/* 002e40b0: jr ra */ {uint64_t target=cpu(31);/* delay 002e40b4 */ set(2,cpu(4));checkReturn(target,incoming);return;}
}
static void body_002e40b8(void){uint64_t incoming=cpu(31);
/* 002e40b8: mfc0 v0,Status */ set(2,sx(nocturneBattlePanelColorReadStatus(UINT32_C(0x002e40b8))));
/* 002e40bc: lui v1,0x1 */ set(3,sx(UINT32_C(0x00010000)));
/* 002e40c0: and v0,v0,v1 */ set(2,cpu(2)&cpu(3));
/* 002e40c4: ei  */ nocturneBattlePanelColorEnableInterrupts(UINT32_C(0x002e40c4));
/* 002e40c8: jr ra */ {uint64_t target=cpu(31);/* delay 002e40cc */ set(2,cpu(0)<cpu(2));checkReturn(target,incoming);return;}
}
uint32_t nocturneBattlePanelColorPrivilegedBody(uint32_t entry){switch(entry){
case UINT32_C(0x002e4070):(void)nocturneBattlePanelColorStackPointer();body_002e4070();return 1u;case UINT32_C(0x002e40b8):(void)nocturneBattlePanelColorStackPointer();body_002e40b8();return 1u;
default:return 0u;}}

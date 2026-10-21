/* Whole original2C1278/38 plus three4-op native syscall veneers.
 * Unlinked source candidate. Real DMA/cache completion remains external.
 * Every scalar write preserves the physical destination upper64. */
#include "sound_dma_native.h"
#include <stdlib.h>
#include <string.h>
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static uint64_t cpu(unsigned reg){uint32_t q[4];if(!reg)return 0;nocturneBattlePanelColorCpuRead(reg,q);return (uint64_t)q[0]|((uint64_t)q[1]<<32);}
static void set(unsigned reg,uint64_t v){uint32_t q[4];if(!reg)return;nocturneBattlePanelColorCpuRead(reg,q);q[0]=(uint32_t)v;q[1]=(uint32_t)(v>>32);nocturneBattlePanelColorCpuWrite(reg,q);if(reg==29u)nocturneBattlePanelColorSetStackPointer(q[0]);}
static uint32_t ea(unsigned reg,int32_t o){return (uint32_t)cpu(reg)+(uint32_t)o;}
static void *at(uint32_t a){void *p=nocturneResolveBattlePanelColorAddress(a);if(!p)abort();return p;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void save(unsigned reg,uint32_t a){uint64_t v=cpu(reg);memcpy(at(a),&v,8);}
static void restore(unsigned reg,uint32_t a){uint64_t v;memcpy(&v,at(a),8);set(reg,v);}
static void checkReturn(uint64_t target,uint64_t incoming){if((uint32_t)target!=(uint32_t)incoming)abort();}

static void body_002c1278(void);
static void body_002dc120(void);
static void body_002dc260(void);
static void body_002dc240(void);
static void body_002c1278(void){
uint64_t incoming=cpu(31);
/* 002c1278: addiu sp,sp,-0x20 */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0xffffffe0)));
/* 002c127c: sd s1,0x8(sp) */ save(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c1280: lui s1,0x59 */ set(17,sx(UINT32_C(0x00590000)));
/* 002c1284: addiu v0,s1,0x2840 */ set(2,sx((uint32_t)cpu(17)+UINT32_C(0x00002840)));
/* 002c1288: sd s0,0x0(sp) */ save(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c128c: sd ra,0x10(sp) */ save(31,ea(29,(int32_t)UINT32_C(0x00000010)));
/* 002c1290: sw a0,0x4(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000004)),(uint32_t)cpu(4));
/* 002c1294: move a0,zero */ set(4,cpu(0));
/* 002c1298: sw a1,0x0(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000000)),(uint32_t)cpu(5));
/* 002c129c: sw a2,0x8(v0) */ sw(ea(2,(int32_t)UINT32_C(0x00000008)),(uint32_t)cpu(6));
/* 002c12a0: jal 0x002dc120 */ set(31,UINT64_C(0x002c12a8));/* delay 002c12a4 */ sw(ea(2,(int32_t)UINT32_C(0x0000000c)),(uint32_t)cpu(0));body_002dc120();
/* 002c12a8: b 0x002c12d8 */ /* delay 002c12ac */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00002840)));goto L_002c12d8;
L_002c12b0:;
/* 002c12b0: ori v0,v0,0x86a0 */ set(2,cpu(2)|UINT32_C(0x000086a0));
/* 002c12b4: addiu v0,v0,-0x271 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffd8f)));
L_002c12b8:;
/* 002c12b8: nop  */ 
/* 002c12bc: nop  */ 
/* 002c12c0: nop  */ 
/* 002c12c4: nop  */ 
/* 002c12c8: nop  */ 
/* 002c12cc: bnel v0,zero,0x002c12b8 */ {int taken=(cpu(2)!=cpu(0));if(taken){/* delay 002c12d0 */ set(2,sx((uint32_t)cpu(2)+UINT32_C(0xfffffd8f)));goto L_002c12b8;}}
/* 002c12d4: addiu a0,s1,0x2840 */ set(4,sx((uint32_t)cpu(17)+UINT32_C(0x00002840)));
L_002c12d8:;
/* 002c12d8: jal 0x002dc260 */ set(31,UINT64_C(0x002c12e0));/* delay 002c12dc */ set(5,sx(UINT32_C(0x00000001)));body_002dc260();
/* 002c12e0: move s0,v0 */ set(16,cpu(2));
/* 002c12e4: beq s0,zero,0x002c12b0 */ {int taken=(cpu(16)==cpu(0));/* delay 002c12e8 */ set(2,sx(UINT32_C(0x00010000)));if(taken){goto L_002c12b0;}}
/* 002c12ec: nop  */ 
L_002c12f0:;
/* 002c12f0: jal 0x002dc240 */ set(31,UINT64_C(0x002c12f8));/* delay 002c12f4 */ set(4,cpu(16));body_002dc240();
/* 002c12f8: bgez v0,0x002c12f0 */ {int taken=((int64_t)cpu(2)>=0);/* delay 002c12fc */ restore(31,ea(29,(int32_t)UINT32_C(0x00000010)));if(taken){goto L_002c12f0;}}
/* 002c1300: ld s0,0x0(sp) */ restore(16,ea(29,(int32_t)UINT32_C(0x00000000)));
/* 002c1304: ld s1,0x8(sp) */ restore(17,ea(29,(int32_t)UINT32_C(0x00000008)));
/* 002c1308: jr ra */ {uint64_t target=cpu(31);/* delay 002c130c */ set(29,sx((uint32_t)cpu(29)+UINT32_C(0x00000020)));checkReturn(target,incoming);return;}
}
static void body_002dc120(void){
uint64_t incoming=cpu(31);
/* 002dc120: li v1,0x64 */ set(3,sx(UINT32_C(0x00000064)));
/* 002dc124: syscall 0x0 */ nocturneSoundDmaNativeSyscall(UINT32_C(0x002dc124),cpu(3));
/* 002dc128: jr ra */ {uint64_t target=cpu(31);/* delay 002dc12c */ checkReturn(target,incoming);return;}
}
static void body_002dc260(void){
uint64_t incoming=cpu(31);
/* 002dc260: li v1,0x77 */ set(3,sx(UINT32_C(0x00000077)));
/* 002dc264: syscall 0x0 */ nocturneSoundDmaNativeSyscall(UINT32_C(0x002dc264),cpu(3));
/* 002dc268: jr ra */ {uint64_t target=cpu(31);/* delay 002dc26c */ checkReturn(target,incoming);return;}
}
static void body_002dc240(void){
uint64_t incoming=cpu(31);
/* 002dc240: li v1,0x76 */ set(3,sx(UINT32_C(0x00000076)));
/* 002dc244: syscall 0x0 */ nocturneSoundDmaNativeSyscall(UINT32_C(0x002dc244),cpu(3));
/* 002dc248: jr ra */ {uint64_t target=cpu(31);/* delay 002dc24c */ checkReturn(target,incoming);return;}
}
uint32_t nocturneSoundDmaNativeBody(uint32_t entry){if(entry!=UINT32_C(0x002c1278))return 0u;if(nocturneBattlePanelColorStackPointer()!=(uint32_t)cpu(29))abort();body_002c1278();return 1u;}
void ps2SoundDmaNative_002C1278(uint64_t destination,uint64_t source,uint64_t bytes){set(4,destination);set(5,source);set(6,bytes);if(!nocturneSoundDmaNativeBody(UINT32_C(0x002c1278)))abort();}

#include "ps2_semaphore_wait_delete.h"
#include <string.h>
/* Original BIOS source-bound fixed statements. RAM and all MMIO are delegated
 * to the initialized memory owner; no INTC acknowledgement is synthesized.
 * The caller owns actual interrupt/SYSCALL entry, Cause/EPC/Status and clocks. */
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
uint32_t nocturneSemaphoreWaitDeleteResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
{
 uint64_t target,value64=0,started;uint32_t value32=0,address=0;
 if(!m||!ram||!ram->read||!ram->write||!s)return NOCTURNE_WAKEUP_INPUT_DOMAIN;
 memset(s,0,sizeof(*s));
 if(m->gpr[0][0]||m->gpr[0][1]||m->gpr[0][2]||m->gpr[0][3])return stop(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN,0,0,0);
 if(!limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);
 started=m->instructions;target=sx(m->pc);
#define STEP(p) do{m->pc=(p);if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);++m->instructions;}while(0)
#define READ(a,p,n) do{address=(a);if((address&((n)-1u))||!ram->read(ram->owner,address,(p),(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);}while(0)
#define WRITE(a,p,n) do{address=(a);if((address&((n)-1u))||!ram->write(ram->owner,address,(p),(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);}while(0)
dispatch:
 m->pc=(uint32_t)target;
 switch(m->pc){
 case UINT32_C(0x80003440):goto L_80003440;
 case UINT32_C(0x80003444):goto L_80003444;
 case UINT32_C(0x80003448):goto L_80003448;
 case UINT32_C(0x8000344c):goto L_8000344c;
 case UINT32_C(0x80003450):goto L_80003450;
 case UINT32_C(0x80003454):goto L_80003454;
 case UINT32_C(0x80003458):goto L_80003458;
 case UINT32_C(0x8000345c):goto L_8000345c;
 case UINT32_C(0x80003460):goto L_80003460;
 case UINT32_C(0x80003464):goto L_80003464;
 case UINT32_C(0x80003468):goto L_80003468;
 case UINT32_C(0x8000346c):goto L_8000346c;
 case UINT32_C(0x80003470):goto L_80003470;
 case UINT32_C(0x80003474):goto L_80003474;
 case UINT32_C(0x80003478):goto L_80003478;
 case UINT32_C(0x8000347c):goto L_8000347c;
 case UINT32_C(0x80003480):goto L_80003480;
 case UINT32_C(0x80003484):goto L_80003484;
 case UINT32_C(0x80003488):goto L_80003488;
 case UINT32_C(0x8000348c):goto L_8000348c;
 case UINT32_C(0x80003490):goto L_80003490;
 case UINT32_C(0x80003494):goto L_80003494;
 case UINT32_C(0x80003498):goto L_80003498;
 case UINT32_C(0x8000349c):goto L_8000349c;
 case UINT32_C(0x800034a0):goto L_800034a0;
 case UINT32_C(0x800034a4):goto L_800034a4;
 case UINT32_C(0x800034a8):goto L_800034a8;
 case UINT32_C(0x800034ac):goto L_800034ac;
 case UINT32_C(0x800034b0):goto L_800034b0;
 case UINT32_C(0x80003540):goto L_80003540;
 case UINT32_C(0x80003544):goto L_80003544;
 case UINT32_C(0x80003548):goto L_80003548;
 case UINT32_C(0x8000354c):goto L_8000354c;
 case UINT32_C(0x80003550):goto L_80003550;
 case UINT32_C(0x80003554):goto L_80003554;
 case UINT32_C(0x80003558):goto L_80003558;
 case UINT32_C(0x8000355c):goto L_8000355c;
 case UINT32_C(0x80003560):goto L_80003560;
 case UINT32_C(0x80003564):goto L_80003564;
 case UINT32_C(0x80003568):goto L_80003568;
 case UINT32_C(0x8000356c):goto L_8000356c;
 case UINT32_C(0x80003570):goto L_80003570;
 case UINT32_C(0x80003574):goto L_80003574;
 case UINT32_C(0x80003578):goto L_80003578;
 case UINT32_C(0x8000357c):goto L_8000357c;
 case UINT32_C(0x80003580):goto L_80003580;
 case UINT32_C(0x80003584):goto L_80003584;
 case UINT32_C(0x80003588):goto L_80003588;
 case UINT32_C(0x8000358c):goto L_8000358c;
 case UINT32_C(0x80003590):goto L_80003590;
 case UINT32_C(0x80003594):goto L_80003594;
 case UINT32_C(0x80003598):goto L_80003598;
 case UINT32_C(0x8000359c):goto L_8000359c;
 case UINT32_C(0x800035a0):goto L_800035a0;
 case UINT32_C(0x800035a4):goto L_800035a4;
 case UINT32_C(0x800035a8):goto L_800035a8;
 case UINT32_C(0x800035ac):goto L_800035ac;
 case UINT32_C(0x80004a48):goto L_80004a48;
 case UINT32_C(0x80004a4c):goto L_80004a4c;
 case UINT32_C(0x80004a50):goto L_80004a50;
 case UINT32_C(0x80004a54):goto L_80004a54;
 case UINT32_C(0x80004a58):goto L_80004a58;
 case UINT32_C(0x80004a5c):goto L_80004a5c;
 case UINT32_C(0x80004a60):goto L_80004a60;
 case UINT32_C(0x80004a64):goto L_80004a64;
 case UINT32_C(0x80004a68):goto L_80004a68;
 case UINT32_C(0x80004a6c):goto L_80004a6c;
 case UINT32_C(0x80004a70):goto L_80004a70;
 case UINT32_C(0x80004a74):goto L_80004a74;
 case UINT32_C(0x80004a78):goto L_80004a78;
 case UINT32_C(0x80004a7c):goto L_80004a7c;
 case UINT32_C(0x80004a80):goto L_80004a80;
 case UINT32_C(0x80004a84):goto L_80004a84;
 case UINT32_C(0x80004a88):goto L_80004a88;
 case UINT32_C(0x80004a8c):goto L_80004a8c;
 case UINT32_C(0x80004a90):goto L_80004a90;
 case UINT32_C(0x80004a94):goto L_80004a94;
 case UINT32_C(0x80004a98):goto L_80004a98;
 case UINT32_C(0x80004a9c):goto L_80004a9c;
 case UINT32_C(0x80004aa0):goto L_80004aa0;
 case UINT32_C(0x80004aa4):goto L_80004aa4;
 case UINT32_C(0x80004aa8):goto L_80004aa8;
 case UINT32_C(0x80004aac):goto L_80004aac;
 case UINT32_C(0x80004ab0):goto L_80004ab0;
 case UINT32_C(0x80004ab4):goto L_80004ab4;
 case UINT32_C(0x80004ab8):goto L_80004ab8;
 case UINT32_C(0x80004abc):goto L_80004abc;
 case UINT32_C(0x80004ac0):goto L_80004ac0;
 case UINT32_C(0x80004ac4):goto L_80004ac4;
 case UINT32_C(0x80004ac8):goto L_80004ac8;
 case UINT32_C(0x80004acc):goto L_80004acc;
 case UINT32_C(0x80004ad0):goto L_80004ad0;
 case UINT32_C(0x80004ad4):goto L_80004ad4;
 case UINT32_C(0x80004ad8):goto L_80004ad8;
 case UINT32_C(0x80004adc):goto L_80004adc;
 case UINT32_C(0x80004ae0):goto L_80004ae0;
 case UINT32_C(0x80004ae4):goto L_80004ae4;
 case UINT32_C(0x80004ae8):goto L_80004ae8;
 case UINT32_C(0x80004aec):goto L_80004aec;
 case UINT32_C(0x80004af0):goto L_80004af0;
 case UINT32_C(0x80004af4):goto L_80004af4;
 case UINT32_C(0x80004af8):goto L_80004af8;
 case UINT32_C(0x80004afc):goto L_80004afc;
 case UINT32_C(0x80004b00):goto L_80004b00;
 case UINT32_C(0x80004b04):goto L_80004b04;
 case UINT32_C(0x80004b08):goto L_80004b08;
 case UINT32_C(0x80004b0c):goto L_80004b0c;
 case UINT32_C(0x80004b10):goto L_80004b10;
 case UINT32_C(0x80004b14):goto L_80004b14;
 case UINT32_C(0x80004b18):goto L_80004b18;
 case UINT32_C(0x80004b1c):goto L_80004b1c;
 case UINT32_C(0x80004b20):goto L_80004b20;
 case UINT32_C(0x80004b24):goto L_80004b24;
 case UINT32_C(0x80004b28):goto L_80004b28;
 case UINT32_C(0x80004b2c):goto L_80004b2c;
 case UINT32_C(0x80004b30):goto L_80004b30;
 case UINT32_C(0x80004b34):goto L_80004b34;
 case UINT32_C(0x80004b38):goto L_80004b38;
 case UINT32_C(0x80004b3c):goto L_80004b3c;
 case UINT32_C(0x80004b40):goto L_80004b40;
 case UINT32_C(0x80004b44):goto L_80004b44;
 case UINT32_C(0x80004b48):goto L_80004b48;
 case UINT32_C(0x80004b4c):goto L_80004b4c;
 case UINT32_C(0x80004b50):goto L_80004b50;
 case UINT32_C(0x80004b54):goto L_80004b54;
 case UINT32_C(0x80004b58):goto L_80004b58;
 case UINT32_C(0x80004b5c):goto L_80004b5c;
 case UINT32_C(0x80004b60):goto L_80004b60;
 case UINT32_C(0x80004b64):goto L_80004b64;
 case UINT32_C(0x80004b68):goto L_80004b68;
 case UINT32_C(0x80004b6c):goto L_80004b6c;
 case UINT32_C(0x80004b70):goto L_80004b70;
 case UINT32_C(0x80004b74):goto L_80004b74;
 case UINT32_C(0x80004b78):goto L_80004b78;
 case UINT32_C(0x80004b7c):goto L_80004b7c;
 case UINT32_C(0x80004b80):goto L_80004b80;
 case UINT32_C(0x80004b84):goto L_80004b84;
 case UINT32_C(0x80004b88):goto L_80004b88;
 case UINT32_C(0x80004b8c):goto L_80004b8c;
 case UINT32_C(0x80004b90):goto L_80004b90;
 case UINT32_C(0x80004b94):goto L_80004b94;
 case UINT32_C(0x80004b98):goto L_80004b98;
 case UINT32_C(0x80004b9c):goto L_80004b9c;
 case UINT32_C(0x80004ba0):goto L_80004ba0;
 case UINT32_C(0x80004ba4):goto L_80004ba4;
 case UINT32_C(0x80004ba8):goto L_80004ba8;
 case UINT32_C(0x80004bac):goto L_80004bac;
 case UINT32_C(0x80004bb0):goto L_80004bb0;
 case UINT32_C(0x80004bb4):goto L_80004bb4;
 case UINT32_C(0x80004bb8):goto L_80004bb8;
 case UINT32_C(0x80004bbc):goto L_80004bbc;
 case UINT32_C(0x80004bc0):goto L_80004bc0;
 case UINT32_C(0x80004cf8):goto L_80004cf8;
 case UINT32_C(0x80004cfc):goto L_80004cfc;
 case UINT32_C(0x80004d00):goto L_80004d00;
 case UINT32_C(0x80004d04):goto L_80004d04;
 case UINT32_C(0x80004d08):goto L_80004d08;
 case UINT32_C(0x80004d0c):goto L_80004d0c;
 case UINT32_C(0x80004d10):goto L_80004d10;
 case UINT32_C(0x80004d14):goto L_80004d14;
 case UINT32_C(0x80004d18):goto L_80004d18;
 case UINT32_C(0x80004d1c):goto L_80004d1c;
 case UINT32_C(0x80004d20):goto L_80004d20;
 case UINT32_C(0x80004d24):goto L_80004d24;
 case UINT32_C(0x80004d28):goto L_80004d28;
 case UINT32_C(0x80004d2c):goto L_80004d2c;
 case UINT32_C(0x80004d30):goto L_80004d30;
 case UINT32_C(0x80004d34):goto L_80004d34;
 case UINT32_C(0x80004d38):goto L_80004d38;
 case UINT32_C(0x80004d3c):goto L_80004d3c;
 case UINT32_C(0x80004d40):goto L_80004d40;
 case UINT32_C(0x80004d44):goto L_80004d44;
 case UINT32_C(0x80004d48):goto L_80004d48;
 case UINT32_C(0x80004d4c):goto L_80004d4c;
 case UINT32_C(0x80004d50):goto L_80004d50;
 case UINT32_C(0x80004d54):goto L_80004d54;
 case UINT32_C(0x80004d58):goto L_80004d58;
 case UINT32_C(0x80004d5c):goto L_80004d5c;
 case UINT32_C(0x80004d60):goto L_80004d60;
 case UINT32_C(0x80004d64):goto L_80004d64;
 case UINT32_C(0x80004d68):goto L_80004d68;
 case UINT32_C(0x80004d6c):goto L_80004d6c;
 case UINT32_C(0x80004d70):goto L_80004d70;
 case UINT32_C(0x80004d74):goto L_80004d74;
 case UINT32_C(0x80004d78):goto L_80004d78;
 case UINT32_C(0x80004d7c):goto L_80004d7c;
 case UINT32_C(0x80004d80):goto L_80004d80;
 case UINT32_C(0x80004d84):goto L_80004d84;
 case UINT32_C(0x80004d88):goto L_80004d88;
 case UINT32_C(0x80004d8c):goto L_80004d8c;
 case UINT32_C(0x80004d90):goto L_80004d90;
 case UINT32_C(0x80004d94):goto L_80004d94;
 case UINT32_C(0x80004d98):goto L_80004d98;
 case UINT32_C(0x80004d9c):goto L_80004d9c;
 case UINT32_C(0x80004da0):goto L_80004da0;
 case UINT32_C(0x80004da4):goto L_80004da4;
 case UINT32_C(0x80004da8):goto L_80004da8;
 case UINT32_C(0x80004dac):goto L_80004dac;
 case UINT32_C(0x80004db0):goto L_80004db0;
 case UINT32_C(0x80004db4):goto L_80004db4;
 case UINT32_C(0x80004db8):goto L_80004db8;
 case UINT32_C(0x80004dbc):goto L_80004dbc;
 case UINT32_C(0x80004dc0):goto L_80004dc0;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_80003440:
 STEP(UINT32_C(0x80003440)); /* 0c000da0 jal 80003680 */
 set(m,31u,UINT64_C(0x80003448));STEP(UINT32_C(0x80003444));set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003680));goto dispatch;
L_80003444:
 STEP(UINT32_C(0x80003444)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003448));goto dispatch;
L_80003448:
 STEP(UINT32_C(0x80003448)); /* 0c00133e jal 80004cf8 */
 set(m,31u,UINT64_C(0x80003450));STEP(UINT32_C(0x8000344c));/* nop */target=sx(UINT32_C(0x80004cf8));goto dispatch;
L_8000344c:
 STEP(UINT32_C(0x8000344c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003450));goto dispatch;
L_80003450:
 STEP(UINT32_C(0x80003450)); /* 2403fffe addiu v1,zero,-2 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x80003454));goto dispatch;
L_80003454:
 STEP(UINT32_C(0x80003454)); /* 1443000f bne v0,v1,80003494 */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x80003458));/* nop */target=sx(taken?UINT32_C(0x80003494):UINT32_C(0x8000345c));goto dispatch;}
L_80003458:
 STEP(UINT32_C(0x80003458)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000345c));goto dispatch;
L_8000345c:
 STEP(UINT32_C(0x8000345c)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003460));goto dispatch;
L_80003460:
 STEP(UINT32_C(0x80003460)); /* 40047000 cop0 rs0 rta0 rd14 fn0 */
 set(m,4u,sx(m->epc));target=sx(UINT32_C(0x80003464));goto dispatch;
L_80003464:
 STEP(UINT32_C(0x80003464)); /* 8ca510c0 lw a1,0x10c0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003468));goto dispatch;
L_80003468:
 STEP(UINT32_C(0x80003468)); /* 0c000e9e jal 80003a78 */
 set(m,31u,UINT64_C(0x80003470));STEP(UINT32_C(0x8000346c));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x80003a78));goto dispatch;
L_8000346c:
 STEP(UINT32_C(0x8000346c)); /* 24060002 addiu a2,zero,2 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x80003470));goto dispatch;
L_80003470:
 STEP(UINT32_C(0x80003470)); /* 40827000 cop0 rs4 rtv0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x80003474));goto dispatch;
L_80003474:
 STEP(UINT32_C(0x80003474)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003478));goto dispatch;
L_80003478:
 STEP(UINT32_C(0x80003478)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x80003480));STEP(UINT32_C(0x8000347c));set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003800));goto dispatch;
L_8000347c:
 STEP(UINT32_C(0x8000347c)); /* 0060e82d daddu sp,v1,zero */
 set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003480));goto dispatch;
L_80003480:
 STEP(UINT32_C(0x80003480)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x80003484));goto dispatch;
L_80003484:
 STEP(UINT32_C(0x80003484)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x80003488));goto dispatch;
L_80003488:
 STEP(UINT32_C(0x80003488)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x8000348c));goto dispatch;
L_8000348c:
 STEP(UINT32_C(0x8000348c)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003490));goto dispatch;
L_80003490:
 STEP(UINT32_C(0x80003490)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80003494:
 STEP(UINT32_C(0x80003494)); /* 3c1d8000 lui sp,zero,0x8000 */
 set(m,29u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003498));goto dispatch;
L_80003498:
 STEP(UINT32_C(0x80003498)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x800034a0));STEP(UINT32_C(0x8000349c));READ((uint32_t)lo(m,29u)+UINT32_C(0x000010c0),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x80003800));goto dispatch;
L_8000349c:
 STEP(UINT32_C(0x8000349c)); /* 8fbd10c0 lw sp,0x10c0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000010c0),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x800034a0));goto dispatch;
L_800034a0:
 STEP(UINT32_C(0x800034a0)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x800034a4));goto dispatch;
L_800034a4:
 STEP(UINT32_C(0x800034a4)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x800034a8));goto dispatch;
L_800034a8:
 STEP(UINT32_C(0x800034a8)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x800034ac));goto dispatch;
L_800034ac:
 STEP(UINT32_C(0x800034ac)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x800034b0));goto dispatch;
L_800034b0:
 STEP(UINT32_C(0x800034b0)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80003540:
 STEP(UINT32_C(0x80003540)); /* 0c000da0 jal 80003680 */
 set(m,31u,UINT64_C(0x80003548));STEP(UINT32_C(0x80003544));set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003680));goto dispatch;
L_80003544:
 STEP(UINT32_C(0x80003544)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003548));goto dispatch;
L_80003548:
 STEP(UINT32_C(0x80003548)); /* 0c001292 jal 80004a48 */
 set(m,31u,UINT64_C(0x80003550));STEP(UINT32_C(0x8000354c));/* nop */target=sx(UINT32_C(0x80004a48));goto dispatch;
L_8000354c:
 STEP(UINT32_C(0x8000354c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003550));goto dispatch;
L_80003550:
 STEP(UINT32_C(0x80003550)); /* 0440000e regimm0 v0,8000358c */
 {int taken=((int64_t)lo(m,2u)<0);STEP(UINT32_C(0x80003554));/* nop */target=sx(taken?UINT32_C(0x8000358c):UINT32_C(0x80003558));goto dispatch;}
L_80003554:
 STEP(UINT32_C(0x80003554)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003558));goto dispatch;
L_80003558:
 STEP(UINT32_C(0x80003558)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x8000355c));goto dispatch;
L_8000355c:
 STEP(UINT32_C(0x8000355c)); /* 40047000 cop0 rs0 rta0 rd14 fn0 */
 set(m,4u,sx(m->epc));target=sx(UINT32_C(0x80003560));goto dispatch;
L_80003560:
 STEP(UINT32_C(0x80003560)); /* 0c000e50 jal 80003940 */
 set(m,31u,UINT64_C(0x80003568));STEP(UINT32_C(0x80003564));READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003940));goto dispatch;
L_80003564:
 STEP(UINT32_C(0x80003564)); /* 8ca510c0 lw a1,0x10c0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003568));goto dispatch;
L_80003568:
 STEP(UINT32_C(0x80003568)); /* 40827000 cop0 rs4 rtv0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x8000356c));goto dispatch;
L_8000356c:
 STEP(UINT32_C(0x8000356c)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003570));goto dispatch;
L_80003570:
 STEP(UINT32_C(0x80003570)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x80003578));STEP(UINT32_C(0x80003574));set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003800));goto dispatch;
L_80003574:
 STEP(UINT32_C(0x80003574)); /* 0060e82d daddu sp,v1,zero */
 set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003578));goto dispatch;
L_80003578:
 STEP(UINT32_C(0x80003578)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x8000357c));goto dispatch;
L_8000357c:
 STEP(UINT32_C(0x8000357c)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x80003580));goto dispatch;
L_80003580:
 STEP(UINT32_C(0x80003580)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003584));goto dispatch;
L_80003584:
 STEP(UINT32_C(0x80003584)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003588));goto dispatch;
L_80003588:
 STEP(UINT32_C(0x80003588)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_8000358c:
 STEP(UINT32_C(0x8000358c)); /* 3c1d8000 lui sp,zero,0x8000 */
 set(m,29u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003590));goto dispatch;
L_80003590:
 STEP(UINT32_C(0x80003590)); /* 8fbd10c0 lw sp,0x10c0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000010c0),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x80003594));goto dispatch;
L_80003594:
 STEP(UINT32_C(0x80003594)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x8000359c));STEP(UINT32_C(0x80003598));value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80003800));goto dispatch;
L_80003598:
 STEP(UINT32_C(0x80003598)); /* ffa20020 sd v0,0x20(sp) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000359c));goto dispatch;
L_8000359c:
 STEP(UINT32_C(0x8000359c)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x800035a0));goto dispatch;
L_800035a0:
 STEP(UINT32_C(0x800035a0)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x800035a4));goto dispatch;
L_800035a4:
 STEP(UINT32_C(0x800035a4)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x800035a8));goto dispatch;
L_800035a8:
 STEP(UINT32_C(0x800035a8)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x800035ac));goto dispatch;
L_800035ac:
 STEP(UINT32_C(0x800035ac)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80004a48:
 STEP(UINT32_C(0x80004a48)); /* 27bdff60 addiu sp,sp,-160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff60)));target=sx(UINT32_C(0x80004a4c));goto dispatch;
L_80004a4c:
 STEP(UINT32_C(0x80004a4c)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x80004a50));goto dispatch;
L_80004a50:
 STEP(UINT32_C(0x80004a50)); /* 0080a82d daddu s5,a0,zero */
 set(m,21u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80004a54));goto dispatch;
L_80004a54:
 STEP(UINT32_C(0x80004a54)); /* ffbf0090 sd ra,0x90(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x80004a58));goto dispatch;
L_80004a58:
 STEP(UINT32_C(0x80004a58)); /* ffbe0080 sd s8,0x80(sp) */
 value64=lo(m,30u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x80004a5c));goto dispatch;
L_80004a5c:
 STEP(UINT32_C(0x80004a5c)); /* 2ea20100 sltiu v0,s5,256 */
 set(m,2u,(lo(m,21u)<UINT64_C(0x100)));target=sx(UINT32_C(0x80004a60));goto dispatch;
L_80004a60:
 STEP(UINT32_C(0x80004a60)); /* ffb70070 sd s7,0x70(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x80004a64));goto dispatch;
L_80004a64:
 STEP(UINT32_C(0x80004a64)); /* ffb60060 sd s6,0x60(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x80004a68));goto dispatch;
L_80004a68:
 STEP(UINT32_C(0x80004a68)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x80004a6c));goto dispatch;
L_80004a6c:
 STEP(UINT32_C(0x80004a6c)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x80004a70));goto dispatch;
L_80004a70:
 STEP(UINT32_C(0x80004a70)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80004a74));goto dispatch;
L_80004a74:
 STEP(UINT32_C(0x80004a74)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80004a78));goto dispatch;
L_80004a78:
 STEP(UINT32_C(0x80004a78)); /* 10400008 beq v0,zero,80004a9c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80004a7c));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x80004a9c):UINT32_C(0x80004a80));goto dispatch;}
L_80004a7c:
 STEP(UINT32_C(0x80004a7c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80004a80));goto dispatch;
L_80004a80:
 STEP(UINT32_C(0x80004a80)); /* 00151140 sll v0,s5,5 */
 set(m,2u,sx((uint32_t)lo(m,21u)<<5u));target=sx(UINT32_C(0x80004a84));goto dispatch;
L_80004a84:
 STEP(UINT32_C(0x80004a84)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80004a88));goto dispatch;
L_80004a88:
 STEP(UINT32_C(0x80004a88)); /* 2463c000 addiu v1,v1,-16384 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffc000)));target=sx(UINT32_C(0x80004a8c));goto dispatch;
L_80004a8c:
 STEP(UINT32_C(0x80004a8c)); /* 00439021 addu s2,v0,v1 */
 set(m,18u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80004a90));goto dispatch;
L_80004a90:
 STEP(UINT32_C(0x80004a90)); /* 8e440004 lw a0,0x4(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000004),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80004a94));goto dispatch;
L_80004a94:
 STEP(UINT32_C(0x80004a94)); /* 04830003 regimm3 a0,80004aa4 */
 if((int64_t)lo(m,4u)>=0){STEP(UINT32_C(0x80004a98));READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004aa4));}else target=sx(UINT32_C(0x80004a9c));goto dispatch;
L_80004a98:
 STEP(UINT32_C(0x80004a98)); /* 8e430014 lw v1,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004a9c));goto dispatch;
L_80004a9c:
 STEP(UINT32_C(0x80004a9c)); /* 1000003d beq zero,zero,80004b94 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004aa0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80004b94):UINT32_C(0x80004aa4));goto dispatch;}
L_80004aa0:
 STEP(UINT32_C(0x80004aa0)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004aa4));goto dispatch;
L_80004aa4:
 STEP(UINT32_C(0x80004aa4)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004aa8));goto dispatch;
L_80004aa8:
 STEP(UINT32_C(0x80004aa8)); /* 8c4273f8 lw v0,0x73f8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x000073f8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004aac));goto dispatch;
L_80004aac:
 STEP(UINT32_C(0x80004aac)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004ab0));goto dispatch;
L_80004ab0:
 STEP(UINT32_C(0x80004ab0)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004ab4));goto dispatch;
L_80004ab4:
 STEP(UINT32_C(0x80004ab4)); /* ac2273f8 sw v0,0x73f8(at) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000073f8),&value32,4u);target=sx(UINT32_C(0x80004ab8));goto dispatch;
L_80004ab8:
 STEP(UINT32_C(0x80004ab8)); /* 1860002e blez v1,zero,80004b74 */
 {int taken=((int64_t)lo(m,3u)<=0);STEP(UINT32_C(0x80004abc));set(m,19u,sx(UINT32_C(0x286b0000)));target=sx(taken?UINT32_C(0x80004b74):UINT32_C(0x80004ac0));goto dispatch;}
L_80004abc:
 STEP(UINT32_C(0x80004abc)); /* 3c13286b lui s3,zero,0x286b */
 set(m,19u,sx(UINT32_C(0x286b0000)));target=sx(UINT32_C(0x80004ac0));goto dispatch;
L_80004ac0:
 STEP(UINT32_C(0x80004ac0)); /* 3c148001 lui s4,zero,0x8001 */
 set(m,20u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004ac4));goto dispatch;
L_80004ac4:
 STEP(UINT32_C(0x80004ac4)); /* 26947400 addiu s4,s4,29696 */
 set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00007400)));target=sx(UINT32_C(0x80004ac8));goto dispatch;
L_80004ac8:
 STEP(UINT32_C(0x80004ac8)); /* 3673ca1b ori s3,s3,0xca1b */
 set(m,19u,lo(m,19u) | UINT64_C(0xca1b));target=sx(UINT32_C(0x80004acc));goto dispatch;
L_80004acc:
 STEP(UINT32_C(0x80004acc)); /* 241e000c addiu s8,zero,12 */
 set(m,30u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x80004ad0));goto dispatch;
L_80004ad0:
 STEP(UINT32_C(0x80004ad0)); /* 24170001 addiu s7,zero,1 */
 set(m,23u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80004ad4));goto dispatch;
L_80004ad4:
 STEP(UINT32_C(0x80004ad4)); /* 24160008 addiu s6,zero,8 */
 set(m,22u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x80004ad8));goto dispatch;
L_80004ad8:
 STEP(UINT32_C(0x80004ad8)); /* 0c001696 jal 80005a58 */
 set(m,31u,UINT64_C(0x80004ae0));STEP(UINT32_C(0x80004adc));set(m,4u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000018)));target=sx(UINT32_C(0x80005a58));goto dispatch;
L_80004adc:
 STEP(UINT32_C(0x80004adc)); /* 26440018 addiu a0,s2,24 */
 set(m,4u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000018)));target=sx(UINT32_C(0x80004ae0));goto dispatch;
L_80004ae0:
 STEP(UINT32_C(0x80004ae0)); /* 00541023 subu v0,v0,s4 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,20u)));target=sx(UINT32_C(0x80004ae4));goto dispatch;
L_80004ae4:
 STEP(UINT32_C(0x80004ae4)); /* 00531018 mult_rd v0,v0,s3 */
 {int64_t product;if(lo(m,2u)!=sx((uint32_t)lo(m,2u))||lo(m,19u)!=sx((uint32_t)lo(m,19u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,2u)*(int64_t)(int32_t)lo(m,19u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=sx(UINT32_C(0x80004ae8));goto dispatch;
L_80004ae8:
 STEP(UINT32_C(0x80004ae8)); /* 00028883 sra s1,v0,2 */
 set(m,17u,sx((uint32_t)((int32_t)lo(m,2u)>>2u)));target=sx(UINT32_C(0x80004aec));goto dispatch;
L_80004aec:
 STEP(UINT32_C(0x80004aec)); /* 2402004c addiu v0,zero,76 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x80004af0));goto dispatch;
L_80004af0:
 STEP(UINT32_C(0x80004af0)); /* 02228018 mult_rd s0,s1,v0 */
 {int64_t product;if(lo(m,17u)!=sx((uint32_t)lo(m,17u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,17u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,16u,m->lo);}target=sx(UINT32_C(0x80004af4));goto dispatch;
L_80004af4:
 STEP(UINT32_C(0x80004af4)); /* 0c0016ba jal 80005ae8 */
 set(m,31u,UINT64_C(0x80004afc));STEP(UINT32_C(0x80004af8));set(m,4u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,20u)));target=sx(UINT32_C(0x80005ae8));goto dispatch;
L_80004af8:
 STEP(UINT32_C(0x80004af8)); /* 02142021 addu a0,s0,s4 */
 set(m,4u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,20u)));target=sx(UINT32_C(0x80004afc));goto dispatch;
L_80004afc:
 STEP(UINT32_C(0x80004afc)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004b00));goto dispatch;
L_80004b00:
 STEP(UINT32_C(0x80004b00)); /* 24427408 addiu v0,v0,29704 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00007408)));target=sx(UINT32_C(0x80004b04));goto dispatch;
L_80004b04:
 STEP(UINT32_C(0x80004b04)); /* 02028021 addu s0,s0,v0 */
 set(m,16u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80004b08));goto dispatch;
L_80004b08:
 STEP(UINT32_C(0x80004b08)); /* 8e420014 lw v0,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004b0c));goto dispatch;
L_80004b0c:
 STEP(UINT32_C(0x80004b0c)); /* 8e030000 lw v1,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004b10));goto dispatch;
L_80004b10:
 STEP(UINT32_C(0x80004b10)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004b14));goto dispatch;
L_80004b14:
 STEP(UINT32_C(0x80004b14)); /* ae420014 sw v0,0x14(s2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x80004b18));goto dispatch;
L_80004b18:
 STEP(UINT32_C(0x80004b18)); /* 24020004 addiu v0,zero,4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x80004b1c));goto dispatch;
L_80004b1c:
 STEP(UINT32_C(0x80004b1c)); /* 10620005 beq v1,v0,80004b34 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x80004b20));/* nop */target=sx(taken?UINT32_C(0x80004b34):UINT32_C(0x80004b24));goto dispatch;}
L_80004b20:
 STEP(UINT32_C(0x80004b20)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80004b24));goto dispatch;
L_80004b24:
 STEP(UINT32_C(0x80004b24)); /* 507e0010 beql v1,s8,80004b68 */
 if(lo(m,3u)==lo(m,30u)){STEP(UINT32_C(0x80004b28));value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004b68));}else target=sx(UINT32_C(0x80004b2c));goto dispatch;
L_80004b28:
 STEP(UINT32_C(0x80004b28)); /* ae160000 sw s6,0x0(s0) */
 value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004b2c));goto dispatch;
L_80004b2c:
 STEP(UINT32_C(0x80004b2c)); /* 1000000f beq zero,zero,80004b6c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004b30));READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x80004b6c):UINT32_C(0x80004b34));goto dispatch;}
L_80004b30:
 STEP(UINT32_C(0x80004b30)); /* 8e420014 lw v0,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004b34));goto dispatch;
L_80004b34:
 STEP(UINT32_C(0x80004b34)); /* 3c108001 lui s0,zero,0x8001 */
 set(m,16u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004b38));goto dispatch;
L_80004b38:
 STEP(UINT32_C(0x80004b38)); /* 8e1025f0 lw s0,0x25f0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x000025f0),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x80004b3c));goto dispatch;
L_80004b3c:
 STEP(UINT32_C(0x80004b3c)); /* 0c00166e jal 800059b8 */
 set(m,31u,UINT64_C(0x80004b44));STEP(UINT32_C(0x80004b40));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x800059b8));goto dispatch;
L_80004b40:
 STEP(UINT32_C(0x80004b40)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x80004b44));goto dispatch;
L_80004b44:
 STEP(UINT32_C(0x80004b44)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004b48));goto dispatch;
L_80004b48:
 STEP(UINT32_C(0x80004b48)); /* 8c4225f0 lw v0,0x25f0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x000025f0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004b4c));goto dispatch;
L_80004b4c:
 STEP(UINT32_C(0x80004b4c)); /* 0050102a slt v0,v0,s0 */
 set(m,2u,((int64_t)lo(m,2u)<(int64_t)lo(m,16u)));target=sx(UINT32_C(0x80004b50));goto dispatch;
L_80004b50:
 STEP(UINT32_C(0x80004b50)); /* 50400006 beql v0,zero,80004b6c */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x80004b54));READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004b6c));}else target=sx(UINT32_C(0x80004b58));goto dispatch;
L_80004b54:
 STEP(UINT32_C(0x80004b54)); /* 8e420014 lw v0,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004b58));goto dispatch;
L_80004b58:
 STEP(UINT32_C(0x80004b58)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004b5c));goto dispatch;
L_80004b5c:
 STEP(UINT32_C(0x80004b5c)); /* ac3725f4 sw s7,0x25f4(at) */
 value32=(uint32_t)lo(m,23u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000025f4),&value32,4u);target=sx(UINT32_C(0x80004b60));goto dispatch;
L_80004b60:
 STEP(UINT32_C(0x80004b60)); /* 10000002 beq zero,zero,80004b6c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004b64));READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x80004b6c):UINT32_C(0x80004b68));goto dispatch;}
L_80004b64:
 STEP(UINT32_C(0x80004b64)); /* 8e420014 lw v0,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004b68));goto dispatch;
L_80004b68:
 STEP(UINT32_C(0x80004b68)); /* 8e420014 lw v0,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004b6c));goto dispatch;
L_80004b6c:
 STEP(UINT32_C(0x80004b6c)); /* 1c40ffda bgtz v0,zero,80004ad8 */
 {int taken=((int64_t)lo(m,2u)>0);STEP(UINT32_C(0x80004b70));/* nop */target=sx(taken?UINT32_C(0x80004ad8):UINT32_C(0x80004b74));goto dispatch;}
L_80004b70:
 STEP(UINT32_C(0x80004b70)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80004b74));goto dispatch;
L_80004b74:
 STEP(UINT32_C(0x80004b74)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004b78));goto dispatch;
L_80004b78:
 STEP(UINT32_C(0x80004b78)); /* 8c6373fc lw v1,0x73fc(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x000073fc),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004b7c));goto dispatch;
L_80004b7c:
 STEP(UINT32_C(0x80004b7c)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004b80));goto dispatch;
L_80004b80:
 STEP(UINT32_C(0x80004b80)); /* ae420004 sw v0,0x4(s2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80004b84));goto dispatch;
L_80004b84:
 STEP(UINT32_C(0x80004b84)); /* ae430000 sw v1,0x0(s2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004b88));goto dispatch;
L_80004b88:
 STEP(UINT32_C(0x80004b88)); /* 02a0102d daddu v0,s5,zero */
 set(m,2u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x80004b8c));goto dispatch;
L_80004b8c:
 STEP(UINT32_C(0x80004b8c)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004b90));goto dispatch;
L_80004b90:
 STEP(UINT32_C(0x80004b90)); /* ac3273fc sw s2,0x73fc(at) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000073fc),&value32,4u);target=sx(UINT32_C(0x80004b94));goto dispatch;
L_80004b94:
 STEP(UINT32_C(0x80004b94)); /* dfbf0090 ld ra,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80004b98));goto dispatch;
L_80004b98:
 STEP(UINT32_C(0x80004b98)); /* dfbe0080 ld s8,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,30u,value64);target=sx(UINT32_C(0x80004b9c));goto dispatch;
L_80004b9c:
 STEP(UINT32_C(0x80004b9c)); /* dfb70070 ld s7,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x80004ba0));goto dispatch;
L_80004ba0:
 STEP(UINT32_C(0x80004ba0)); /* dfb60060 ld s6,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x80004ba4));goto dispatch;
L_80004ba4:
 STEP(UINT32_C(0x80004ba4)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x80004ba8));goto dispatch;
L_80004ba8:
 STEP(UINT32_C(0x80004ba8)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x80004bac));goto dispatch;
L_80004bac:
 STEP(UINT32_C(0x80004bac)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x80004bb0));goto dispatch;
L_80004bb0:
 STEP(UINT32_C(0x80004bb0)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x80004bb4));goto dispatch;
L_80004bb4:
 STEP(UINT32_C(0x80004bb4)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x80004bb8));goto dispatch;
L_80004bb8:
 STEP(UINT32_C(0x80004bb8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x80004bbc));goto dispatch;
L_80004bbc:
 STEP(UINT32_C(0x80004bbc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004bc0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));goto dispatch;
L_80004bc0:
 STEP(UINT32_C(0x80004bc0)); /* 27bd00a0 addiu sp,sp,160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));target=sx(UINT32_C(0x80004bc4));goto dispatch;
L_80004cf8:
 STEP(UINT32_C(0x80004cf8)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x80004cfc));goto dispatch;
L_80004cfc:
 STEP(UINT32_C(0x80004cfc)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x80004d00));goto dispatch;
L_80004d00:
 STEP(UINT32_C(0x80004d00)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80004d04));goto dispatch;
L_80004d04:
 STEP(UINT32_C(0x80004d04)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x80004d08));goto dispatch;
L_80004d08:
 STEP(UINT32_C(0x80004d08)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80004d0c));goto dispatch;
L_80004d0c:
 STEP(UINT32_C(0x80004d0c)); /* 2e620100 sltiu v0,s3,256 */
 set(m,2u,(lo(m,19u)<UINT64_C(0x100)));target=sx(UINT32_C(0x80004d10));goto dispatch;
L_80004d10:
 STEP(UINT32_C(0x80004d10)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80004d14));goto dispatch;
L_80004d14:
 STEP(UINT32_C(0x80004d14)); /* 10400008 beq v0,zero,80004d38 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80004d18));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x80004d38):UINT32_C(0x80004d1c));goto dispatch;}
L_80004d18:
 STEP(UINT32_C(0x80004d18)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80004d1c));goto dispatch;
L_80004d1c:
 STEP(UINT32_C(0x80004d1c)); /* 00131940 sll v1,s3,5 */
 set(m,3u,sx((uint32_t)lo(m,19u)<<5u));target=sx(UINT32_C(0x80004d20));goto dispatch;
L_80004d20:
 STEP(UINT32_C(0x80004d20)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80004d24));goto dispatch;
L_80004d24:
 STEP(UINT32_C(0x80004d24)); /* 2442c000 addiu v0,v0,-16384 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffc000)));target=sx(UINT32_C(0x80004d28));goto dispatch;
L_80004d28:
 STEP(UINT32_C(0x80004d28)); /* 00629021 addu s2,v1,v0 */
 set(m,18u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80004d2c));goto dispatch;
L_80004d2c:
 STEP(UINT32_C(0x80004d2c)); /* 8e430004 lw v1,0x4(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004d30));goto dispatch;
L_80004d30:
 STEP(UINT32_C(0x80004d30)); /* 04610003 regimm1 v1,80004d40 */
 {int taken=((int64_t)lo(m,3u)>=0);STEP(UINT32_C(0x80004d34));/* nop */target=sx(taken?UINT32_C(0x80004d40):UINT32_C(0x80004d38));goto dispatch;}
L_80004d34:
 STEP(UINT32_C(0x80004d34)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80004d38));goto dispatch;
L_80004d38:
 STEP(UINT32_C(0x80004d38)); /* 1000001b beq zero,zero,80004da8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004d3c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80004da8):UINT32_C(0x80004d40));goto dispatch;}
L_80004d3c:
 STEP(UINT32_C(0x80004d3c)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004d40));goto dispatch;
L_80004d40:
 STEP(UINT32_C(0x80004d40)); /* 18600004 blez v1,zero,80004d54 */
 {int taken=((int64_t)lo(m,3u)<=0);STEP(UINT32_C(0x80004d44));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80004d54):UINT32_C(0x80004d48));goto dispatch;}
L_80004d44:
 STEP(UINT32_C(0x80004d44)); /* 2463ffff addiu v1,v1,-1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004d48));goto dispatch;
L_80004d48:
 STEP(UINT32_C(0x80004d48)); /* 0260102d daddu v0,s3,zero */
 set(m,2u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x80004d4c));goto dispatch;
L_80004d4c:
 STEP(UINT32_C(0x80004d4c)); /* 10000016 beq zero,zero,80004da8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004d50));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x80004da8):UINT32_C(0x80004d54));goto dispatch;}
L_80004d50:
 STEP(UINT32_C(0x80004d50)); /* ae430004 sw v1,0x4(s2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80004d54));goto dispatch;
L_80004d54:
 STEP(UINT32_C(0x80004d54)); /* 8e420014 lw v0,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004d58));goto dispatch;
L_80004d58:
 STEP(UINT32_C(0x80004d58)); /* 2411004c addiu s1,zero,76 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x80004d5c));goto dispatch;
L_80004d5c:
 STEP(UINT32_C(0x80004d5c)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004d60));goto dispatch;
L_80004d60:
 STEP(UINT32_C(0x80004d60)); /* 8c8425ec lw a0,0x25ec(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x000025ec),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80004d64));goto dispatch;
L_80004d64:
 STEP(UINT32_C(0x80004d64)); /* 3c108001 lui s0,zero,0x8001 */
 set(m,16u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004d68));goto dispatch;
L_80004d68:
 STEP(UINT32_C(0x80004d68)); /* 26107400 addiu s0,s0,29696 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00007400)));target=sx(UINT32_C(0x80004d6c));goto dispatch;
L_80004d6c:
 STEP(UINT32_C(0x80004d6c)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80004d70));goto dispatch;
L_80004d70:
 STEP(UINT32_C(0x80004d70)); /* 0c00165e jal 80005978 */
 set(m,31u,UINT64_C(0x80004d78));STEP(UINT32_C(0x80004d74));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x80005978));goto dispatch;
L_80004d74:
 STEP(UINT32_C(0x80004d74)); /* ae420014 sw v0,0x14(s2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x80004d78));goto dispatch;
L_80004d78:
 STEP(UINT32_C(0x80004d78)); /* 3c058001 lui a1,zero,0x8001 */
 set(m,5u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004d7c));goto dispatch;
L_80004d7c:
 STEP(UINT32_C(0x80004d7c)); /* 8ca525ec lw a1,0x25ec(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x000025ec),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80004d80));goto dispatch;
L_80004d80:
 STEP(UINT32_C(0x80004d80)); /* 26440018 addiu a0,s2,24 */
 set(m,4u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000018)));target=sx(UINT32_C(0x80004d84));goto dispatch;
L_80004d84:
 STEP(UINT32_C(0x80004d84)); /* 00b12818 mult_rd a1,a1,s1 */
 {int64_t product;if(lo(m,5u)!=sx((uint32_t)lo(m,5u))||lo(m,17u)!=sx((uint32_t)lo(m,17u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,5u)*(int64_t)(int32_t)lo(m,17u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,5u,m->lo);}target=sx(UINT32_C(0x80004d88));goto dispatch;
L_80004d88:
 STEP(UINT32_C(0x80004d88)); /* 0c0016c2 jal 80005b08 */
 set(m,31u,UINT64_C(0x80004d90));STEP(UINT32_C(0x80004d8c));set(m,5u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x80005b08));goto dispatch;
L_80004d8c:
 STEP(UINT32_C(0x80004d8c)); /* 00b02821 addu a1,a1,s0 */
 set(m,5u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x80004d90));goto dispatch;
L_80004d90:
 STEP(UINT32_C(0x80004d90)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004d94));goto dispatch;
L_80004d94:
 STEP(UINT32_C(0x80004d94)); /* 8c6325ec lw v1,0x25ec(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x000025ec),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004d98));goto dispatch;
L_80004d98:
 STEP(UINT32_C(0x80004d98)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x80004d9c));goto dispatch;
L_80004d9c:
 STEP(UINT32_C(0x80004d9c)); /* 00712018 mult_rd a0,v1,s1 */
 {int64_t product;if(lo(m,3u)!=sx((uint32_t)lo(m,3u))||lo(m,17u)!=sx((uint32_t)lo(m,17u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,3u)*(int64_t)(int32_t)lo(m,17u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x80004da0));goto dispatch;
L_80004da0:
 STEP(UINT32_C(0x80004da0)); /* 00901821 addu v1,a0,s0 */
 set(m,3u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x80004da4));goto dispatch;
L_80004da4:
 STEP(UINT32_C(0x80004da4)); /* ac730020 sw s3,0x20(v1) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x80004da8));goto dispatch;
L_80004da8:
 STEP(UINT32_C(0x80004da8)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80004dac));goto dispatch;
L_80004dac:
 STEP(UINT32_C(0x80004dac)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x80004db0));goto dispatch;
L_80004db0:
 STEP(UINT32_C(0x80004db0)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x80004db4));goto dispatch;
L_80004db4:
 STEP(UINT32_C(0x80004db4)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x80004db8));goto dispatch;
L_80004db8:
 STEP(UINT32_C(0x80004db8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x80004dbc));goto dispatch;
L_80004dbc:
 STEP(UINT32_C(0x80004dbc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004dc0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_80004dc0:
 STEP(UINT32_C(0x80004dc0)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x80004dc4));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

#include "sound_rpc_queue_native.h"
#include <string.h>
/* Original Nocturne ELF source-bound fixed statements. RAM and all MMIO are delegated
 * to the initialized memory owner; no INTC acknowledgement is synthesized.
 * The caller owns actual interrupt/SYSCALL entry, Cause/EPC/Status and clocks. */
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
uint32_t nocturneSoundRpcQueueResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002dbd90):goto L_002dbd90;
 case UINT32_C(0x002dbd94):goto L_002dbd94;
 case UINT32_C(0x002dbd98):goto L_002dbd98;
 case UINT32_C(0x002dbd9c):goto L_002dbd9c;
 case UINT32_C(0x002def78):goto L_002def78;
 case UINT32_C(0x002def7c):goto L_002def7c;
 case UINT32_C(0x002def80):goto L_002def80;
 case UINT32_C(0x002def84):goto L_002def84;
 case UINT32_C(0x002def88):goto L_002def88;
 case UINT32_C(0x002def8c):goto L_002def8c;
 case UINT32_C(0x002def90):goto L_002def90;
 case UINT32_C(0x002def94):goto L_002def94;
 case UINT32_C(0x002def98):goto L_002def98;
 case UINT32_C(0x002def9c):goto L_002def9c;
 case UINT32_C(0x002defa0):goto L_002defa0;
 case UINT32_C(0x002defa4):goto L_002defa4;
 case UINT32_C(0x002defa8):goto L_002defa8;
 case UINT32_C(0x002defac):goto L_002defac;
 case UINT32_C(0x002defb0):goto L_002defb0;
 case UINT32_C(0x002defb4):goto L_002defb4;
 case UINT32_C(0x002defb8):goto L_002defb8;
 case UINT32_C(0x002defbc):goto L_002defbc;
 case UINT32_C(0x002defc0):goto L_002defc0;
 case UINT32_C(0x002defc4):goto L_002defc4;
 case UINT32_C(0x002defc8):goto L_002defc8;
 case UINT32_C(0x002defcc):goto L_002defcc;
 case UINT32_C(0x002defd0):goto L_002defd0;
 case UINT32_C(0x002defd4):goto L_002defd4;
 case UINT32_C(0x002defd8):goto L_002defd8;
 case UINT32_C(0x002defdc):goto L_002defdc;
 case UINT32_C(0x002defe0):goto L_002defe0;
 case UINT32_C(0x002defe4):goto L_002defe4;
 case UINT32_C(0x002defe8):goto L_002defe8;
 case UINT32_C(0x002defec):goto L_002defec;
 case UINT32_C(0x002deff0):goto L_002deff0;
 case UINT32_C(0x002deff4):goto L_002deff4;
 case UINT32_C(0x002deff8):goto L_002deff8;
 case UINT32_C(0x002deffc):goto L_002deffc;
 case UINT32_C(0x002df000):goto L_002df000;
 case UINT32_C(0x002df004):goto L_002df004;
 case UINT32_C(0x002df008):goto L_002df008;
 case UINT32_C(0x002df010):goto L_002df010;
 case UINT32_C(0x002df014):goto L_002df014;
 case UINT32_C(0x002df018):goto L_002df018;
 case UINT32_C(0x002df01c):goto L_002df01c;
 case UINT32_C(0x002df020):goto L_002df020;
 case UINT32_C(0x002df024):goto L_002df024;
 case UINT32_C(0x002df028):goto L_002df028;
 case UINT32_C(0x002df02c):goto L_002df02c;
 case UINT32_C(0x002df030):goto L_002df030;
 case UINT32_C(0x002df034):goto L_002df034;
 case UINT32_C(0x002df038):goto L_002df038;
 case UINT32_C(0x002df03c):goto L_002df03c;
 case UINT32_C(0x002df040):goto L_002df040;
 case UINT32_C(0x002df044):goto L_002df044;
 case UINT32_C(0x002df048):goto L_002df048;
 case UINT32_C(0x002df04c):goto L_002df04c;
 case UINT32_C(0x002df050):goto L_002df050;
 case UINT32_C(0x002df054):goto L_002df054;
 case UINT32_C(0x002df058):goto L_002df058;
 case UINT32_C(0x002df05c):goto L_002df05c;
 case UINT32_C(0x002df060):goto L_002df060;
 case UINT32_C(0x002df064):goto L_002df064;
 case UINT32_C(0x002df068):goto L_002df068;
 case UINT32_C(0x002df06c):goto L_002df06c;
 case UINT32_C(0x002df070):goto L_002df070;
 case UINT32_C(0x002df074):goto L_002df074;
 case UINT32_C(0x002df078):goto L_002df078;
 case UINT32_C(0x002df07c):goto L_002df07c;
 case UINT32_C(0x002df080):goto L_002df080;
 case UINT32_C(0x002df084):goto L_002df084;
 case UINT32_C(0x002df088):goto L_002df088;
 case UINT32_C(0x002df08c):goto L_002df08c;
 case UINT32_C(0x002df090):goto L_002df090;
 case UINT32_C(0x002df094):goto L_002df094;
 case UINT32_C(0x002df098):goto L_002df098;
 case UINT32_C(0x002df09c):goto L_002df09c;
 case UINT32_C(0x002df0a0):goto L_002df0a0;
 case UINT32_C(0x002df0a4):goto L_002df0a4;
 case UINT32_C(0x002df0a8):goto L_002df0a8;
 case UINT32_C(0x002df0ac):goto L_002df0ac;
 case UINT32_C(0x002df0b0):goto L_002df0b0;
 case UINT32_C(0x002df0b4):goto L_002df0b4;
 case UINT32_C(0x002df0b8):goto L_002df0b8;
 case UINT32_C(0x002df0bc):goto L_002df0bc;
 case UINT32_C(0x002df0c0):goto L_002df0c0;
 case UINT32_C(0x002df0c4):goto L_002df0c4;
 case UINT32_C(0x002df0c8):goto L_002df0c8;
 case UINT32_C(0x002df0cc):goto L_002df0cc;
 case UINT32_C(0x002df0d0):goto L_002df0d0;
 case UINT32_C(0x002df0d4):goto L_002df0d4;
 case UINT32_C(0x002df0d8):goto L_002df0d8;
 case UINT32_C(0x002df0dc):goto L_002df0dc;
 case UINT32_C(0x002df208):goto L_002df208;
 case UINT32_C(0x002df20c):goto L_002df20c;
 case UINT32_C(0x002df210):goto L_002df210;
 case UINT32_C(0x002df214):goto L_002df214;
 case UINT32_C(0x002df218):goto L_002df218;
 case UINT32_C(0x002df21c):goto L_002df21c;
 case UINT32_C(0x002df220):goto L_002df220;
 case UINT32_C(0x002df224):goto L_002df224;
 case UINT32_C(0x002df228):goto L_002df228;
 case UINT32_C(0x002df22c):goto L_002df22c;
 case UINT32_C(0x002df230):goto L_002df230;
 case UINT32_C(0x002df234):goto L_002df234;
 case UINT32_C(0x002df238):goto L_002df238;
 case UINT32_C(0x002df23c):goto L_002df23c;
 case UINT32_C(0x002df240):goto L_002df240;
 case UINT32_C(0x002df244):goto L_002df244;
 case UINT32_C(0x002df248):goto L_002df248;
 case UINT32_C(0x002df24c):goto L_002df24c;
 case UINT32_C(0x002df250):goto L_002df250;
 case UINT32_C(0x002df254):goto L_002df254;
 case UINT32_C(0x002df258):goto L_002df258;
 case UINT32_C(0x002df25c):goto L_002df25c;
 case UINT32_C(0x002df428):goto L_002df428;
 case UINT32_C(0x002df42c):goto L_002df42c;
 case UINT32_C(0x002df430):goto L_002df430;
 case UINT32_C(0x002df434):goto L_002df434;
 case UINT32_C(0x002df438):goto L_002df438;
 case UINT32_C(0x002df43c):goto L_002df43c;
 case UINT32_C(0x002df440):goto L_002df440;
 case UINT32_C(0x002df444):goto L_002df444;
 case UINT32_C(0x002df448):goto L_002df448;
 case UINT32_C(0x002df44c):goto L_002df44c;
 case UINT32_C(0x002df450):goto L_002df450;
 case UINT32_C(0x002df454):goto L_002df454;
 case UINT32_C(0x002df458):goto L_002df458;
 case UINT32_C(0x002df45c):goto L_002df45c;
 case UINT32_C(0x002df460):goto L_002df460;
 case UINT32_C(0x002df464):goto L_002df464;
 case UINT32_C(0x002e4070):goto L_002e4070;
 case UINT32_C(0x002e4074):goto L_002e4074;
 case UINT32_C(0x002e4078):goto L_002e4078;
 case UINT32_C(0x002e407c):goto L_002e407c;
 case UINT32_C(0x002e4080):goto L_002e4080;
 case UINT32_C(0x002e4084):goto L_002e4084;
 case UINT32_C(0x002e4088):goto L_002e4088;
 case UINT32_C(0x002e408c):goto L_002e408c;
 case UINT32_C(0x002e4090):goto L_002e4090;
 case UINT32_C(0x002e4094):goto L_002e4094;
 case UINT32_C(0x002e4098):goto L_002e4098;
 case UINT32_C(0x002e409c):goto L_002e409c;
 case UINT32_C(0x002e40a0):goto L_002e40a0;
 case UINT32_C(0x002e40a4):goto L_002e40a4;
 case UINT32_C(0x002e40a8):goto L_002e40a8;
 case UINT32_C(0x002e40ac):goto L_002e40ac;
 case UINT32_C(0x002e40b0):goto L_002e40b0;
 case UINT32_C(0x002e40b4):goto L_002e40b4;
 case UINT32_C(0x002e40b8):goto L_002e40b8;
 case UINT32_C(0x002e40bc):goto L_002e40bc;
 case UINT32_C(0x002e40c0):goto L_002e40c0;
 case UINT32_C(0x002e40c4):goto L_002e40c4;
 case UINT32_C(0x002e40c8):goto L_002e40c8;
 case UINT32_C(0x002e40cc):goto L_002e40cc;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002dbd90:
 STEP(UINT32_C(0x002dbd90)); /* 2403002f addiu v1,zero,47 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000002f)));target=sx(UINT32_C(0x002dbd94));goto dispatch;
L_002dbd94:
 m->pc=UINT32_C(0x002dbd94); /* Unexecuted SYS, counted only by router. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbd98:
 STEP(UINT32_C(0x002dbd98)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbd9c));/* nop */goto dispatch;
L_002dbd9c:
 STEP(UINT32_C(0x002dbd9c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbda0));goto dispatch;
L_002def78:
 STEP(UINT32_C(0x002def78)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002def7c));goto dispatch;
L_002def7c:
 STEP(UINT32_C(0x002def7c)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002def80));goto dispatch;
L_002def80:
 STEP(UINT32_C(0x002def80)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002def84));goto dispatch;
L_002def84:
 STEP(UINT32_C(0x002def84)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002def88));goto dispatch;
L_002def88:
 STEP(UINT32_C(0x002def88)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002def8c));goto dispatch;
L_002def8c:
 STEP(UINT32_C(0x002def8c)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002def94));STEP(UINT32_C(0x002def90));set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002def90:
 STEP(UINT32_C(0x002def90)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002def94));goto dispatch;
L_002def94:
 STEP(UINT32_C(0x002def94)); /* 3c03005a lui v1,zero,0x5a */
 set(m,3u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002def98));goto dispatch;
L_002def98:
 STEP(UINT32_C(0x002def98)); /* ae300000 sw s0,0x0(s1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002def9c));goto dispatch;
L_002def9c:
 STEP(UINT32_C(0x002def9c)); /* 2463d440 addiu v1,v1,-11200 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffd440)));target=sx(UINT32_C(0x002defa0));goto dispatch;
L_002defa0:
 STEP(UINT32_C(0x002defa0)); /* ae200004 sw zero,0x4(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002defa4));goto dispatch;
L_002defa4:
 STEP(UINT32_C(0x002defa4)); /* 8c620028 lw v0,0x28(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000028),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002defa8));goto dispatch;
L_002defa8:
 STEP(UINT32_C(0x002defa8)); /* ae200008 sw zero,0x8(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002defac));goto dispatch;
L_002defac:
 STEP(UINT32_C(0x002defac)); /* ae20000c sw zero,0xc(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002defb0));goto dispatch;
L_002defb0:
 STEP(UINT32_C(0x002defb0)); /* ae200010 sw zero,0x10(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002defb4));goto dispatch;
L_002defb4:
 STEP(UINT32_C(0x002defb4)); /* 14400003 bne v0,zero,002defc4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002defb8));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002defc4):UINT32_C(0x002defbc));goto dispatch;}
L_002defb8:
 STEP(UINT32_C(0x002defb8)); /* ae200014 sw zero,0x14(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002defbc));goto dispatch;
L_002defbc:
 STEP(UINT32_C(0x002defbc)); /* 1000000e beq zero,zero,002deff8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002defc0));value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000028),&value32,4u);target=sx(taken?UINT32_C(0x002deff8):UINT32_C(0x002defc4));goto dispatch;}
L_002defc0:
 STEP(UINT32_C(0x002defc0)); /* ac710028 sw s1,0x28(v1) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x002defc4));goto dispatch;
L_002defc4:
 STEP(UINT32_C(0x002defc4)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002defc8));goto dispatch;
L_002defc8:
 STEP(UINT32_C(0x002defc8)); /* 8c830014 lw v1,0x14(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002defcc));goto dispatch;
L_002defcc:
 STEP(UINT32_C(0x002defcc)); /* 5060000a beql v1,zero,002deff8 */
 if(lo(m,3u)==lo(m,0u)){STEP(UINT32_C(0x002defd0));value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002deff8));}else target=sx(UINT32_C(0x002defd4));goto dispatch;
L_002defd0:
 STEP(UINT32_C(0x002defd0)); /* ac910014 sw s1,0x14(a0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002defd4));goto dispatch;
L_002defd4:
 STEP(UINT32_C(0x002defd4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002defd8));goto dispatch;
L_002defd8:
 STEP(UINT32_C(0x002defd8)); /* 0060202d daddu a0,v1,zero */
 set(m,4u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002defdc));goto dispatch;
L_002defdc:
 STEP(UINT32_C(0x002defdc)); /* 8c820014 lw v0,0x14(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002defe0));goto dispatch;
L_002defe0:
 STEP(UINT32_C(0x002defe0)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002defe4));goto dispatch;
L_002defe4:
 STEP(UINT32_C(0x002defe4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002defe8));goto dispatch;
L_002defe8:
 STEP(UINT32_C(0x002defe8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002defec));goto dispatch;
L_002defec:
 STEP(UINT32_C(0x002defec)); /* 1440fffa bne v0,zero,002defd8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002deff0));/* nop */target=sx(taken?UINT32_C(0x002defd8):UINT32_C(0x002deff4));goto dispatch;}
L_002deff0:
 STEP(UINT32_C(0x002deff0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002deff4));goto dispatch;
L_002deff4:
 STEP(UINT32_C(0x002deff4)); /* ac910014 sw s1,0x14(a0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002deff8));goto dispatch;
L_002deff8:
 STEP(UINT32_C(0x002deff8)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002deffc));goto dispatch;
L_002deffc:
 STEP(UINT32_C(0x002deffc)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002df000));goto dispatch;
L_002df000:
 STEP(UINT32_C(0x002df000)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002df004));goto dispatch;
L_002df004:
 STEP(UINT32_C(0x002df004)); /* 080b902e j 002e40b8 */
 STEP(UINT32_C(0x002df008));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002df008:
 STEP(UINT32_C(0x002df008)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002df00c));goto dispatch;
L_002df010:
 STEP(UINT32_C(0x002df010)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x002df014));goto dispatch;
L_002df014:
 STEP(UINT32_C(0x002df014)); /* ffb60060 sd s6,0x60(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002df018));goto dispatch;
L_002df018:
 STEP(UINT32_C(0x002df018)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002df01c));goto dispatch;
L_002df01c:
 STEP(UINT32_C(0x002df01c)); /* 0140b02d daddu s6,t2,zero */
 set(m,22u,lo(m,10u)+lo(m,0u));target=sx(UINT32_C(0x002df020));goto dispatch;
L_002df020:
 STEP(UINT32_C(0x002df020)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002df024));goto dispatch;
L_002df024:
 STEP(UINT32_C(0x002df024)); /* 0080a82d daddu s5,a0,zero */
 set(m,21u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002df028));goto dispatch;
L_002df028:
 STEP(UINT32_C(0x002df028)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002df02c));goto dispatch;
L_002df02c:
 STEP(UINT32_C(0x002df02c)); /* 0120a02d daddu s4,t1,zero */
 set(m,20u,lo(m,9u)+lo(m,0u));target=sx(UINT32_C(0x002df030));goto dispatch;
L_002df030:
 STEP(UINT32_C(0x002df030)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002df034));goto dispatch;
L_002df034:
 STEP(UINT32_C(0x002df034)); /* 0100982d daddu s3,t0,zero */
 set(m,19u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002df038));goto dispatch;
L_002df038:
 STEP(UINT32_C(0x002df038)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002df03c));goto dispatch;
L_002df03c:
 STEP(UINT32_C(0x002df03c)); /* 00e0902d daddu s2,a3,zero */
 set(m,18u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002df040));goto dispatch;
L_002df040:
 STEP(UINT32_C(0x002df040)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002df044));goto dispatch;
L_002df044:
 STEP(UINT32_C(0x002df044)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002df048));goto dispatch;
L_002df048:
 STEP(UINT32_C(0x002df048)); /* ffbf0070 sd ra,0x70(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002df04c));goto dispatch;
L_002df04c:
 STEP(UINT32_C(0x002df04c)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002df054));STEP(UINT32_C(0x002df050));set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002df050:
 STEP(UINT32_C(0x002df050)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002df054));goto dispatch;
L_002df054:
 STEP(UINT32_C(0x002df054)); /* aea0003c sw zero,0x3c(s5) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x0000003c),&value32,4u);target=sx(UINT32_C(0x002df058));goto dispatch;
L_002df058:
 STEP(UINT32_C(0x002df058)); /* aea00038 sw zero,0x38(s5) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000038),&value32,4u);target=sx(UINT32_C(0x002df05c));goto dispatch;
L_002df05c:
 STEP(UINT32_C(0x002df05c)); /* aeb00000 sw s0,0x0(s5) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002df060));goto dispatch;
L_002df060:
 STEP(UINT32_C(0x002df060)); /* 8ec20008 lw v0,0x8(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002df064));goto dispatch;
L_002df064:
 STEP(UINT32_C(0x002df064)); /* aeb10004 sw s1,0x4(s5) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002df068));goto dispatch;
L_002df068:
 STEP(UINT32_C(0x002df068)); /* aeb20008 sw s2,0x8(s5) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002df06c));goto dispatch;
L_002df06c:
 STEP(UINT32_C(0x002df06c)); /* aeb30010 sw s3,0x10(s5) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002df070));goto dispatch;
L_002df070:
 STEP(UINT32_C(0x002df070)); /* aeb40014 sw s4,0x14(s5) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002df074));goto dispatch;
L_002df074:
 STEP(UINT32_C(0x002df074)); /* 14400003 bne v0,zero,002df084 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002df078));value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000040),&value32,4u);target=sx(taken?UINT32_C(0x002df084):UINT32_C(0x002df07c));goto dispatch;}
L_002df078:
 STEP(UINT32_C(0x002df078)); /* aeb60040 sw s6,0x40(s5) */
 value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000040),&value32,4u);target=sx(UINT32_C(0x002df07c));goto dispatch;
L_002df07c:
 STEP(UINT32_C(0x002df07c)); /* 1000000e beq zero,zero,002df0b8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002df080));value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002df0b8):UINT32_C(0x002df084));goto dispatch;}
L_002df080:
 STEP(UINT32_C(0x002df080)); /* aed50008 sw s5,0x8(s6) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002df084));goto dispatch;
L_002df084:
 STEP(UINT32_C(0x002df084)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002df088));goto dispatch;
L_002df088:
 STEP(UINT32_C(0x002df088)); /* 8c830038 lw v1,0x38(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000038),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002df08c));goto dispatch;
L_002df08c:
 STEP(UINT32_C(0x002df08c)); /* 5060000a beql v1,zero,002df0b8 */
 if(lo(m,3u)==lo(m,0u)){STEP(UINT32_C(0x002df090));value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000038),&value32,4u);target=sx(UINT32_C(0x002df0b8));}else target=sx(UINT32_C(0x002df094));goto dispatch;
L_002df090:
 STEP(UINT32_C(0x002df090)); /* ac950038 sw s5,0x38(a0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000038),&value32,4u);target=sx(UINT32_C(0x002df094));goto dispatch;
L_002df094:
 STEP(UINT32_C(0x002df094)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df098));goto dispatch;
L_002df098:
 STEP(UINT32_C(0x002df098)); /* 0060202d daddu a0,v1,zero */
 set(m,4u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002df09c));goto dispatch;
L_002df09c:
 STEP(UINT32_C(0x002df09c)); /* 8c820038 lw v0,0x38(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000038),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002df0a0));goto dispatch;
L_002df0a0:
 STEP(UINT32_C(0x002df0a0)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002df0a4));goto dispatch;
L_002df0a4:
 STEP(UINT32_C(0x002df0a4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df0a8));goto dispatch;
L_002df0a8:
 STEP(UINT32_C(0x002df0a8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df0ac));goto dispatch;
L_002df0ac:
 STEP(UINT32_C(0x002df0ac)); /* 1440fffa bne v0,zero,002df098 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002df0b0));/* nop */target=sx(taken?UINT32_C(0x002df098):UINT32_C(0x002df0b4));goto dispatch;}
L_002df0b0:
 STEP(UINT32_C(0x002df0b0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df0b4));goto dispatch;
L_002df0b4:
 STEP(UINT32_C(0x002df0b4)); /* ac950038 sw s5,0x38(a0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000038),&value32,4u);target=sx(UINT32_C(0x002df0b8));goto dispatch;
L_002df0b8:
 STEP(UINT32_C(0x002df0b8)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002df0bc));goto dispatch;
L_002df0bc:
 STEP(UINT32_C(0x002df0bc)); /* dfb60060 ld s6,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002df0c0));goto dispatch;
L_002df0c0:
 STEP(UINT32_C(0x002df0c0)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002df0c4));goto dispatch;
L_002df0c4:
 STEP(UINT32_C(0x002df0c4)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002df0c8));goto dispatch;
L_002df0c8:
 STEP(UINT32_C(0x002df0c8)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002df0cc));goto dispatch;
L_002df0cc:
 STEP(UINT32_C(0x002df0cc)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002df0d0));goto dispatch;
L_002df0d0:
 STEP(UINT32_C(0x002df0d0)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002df0d4));goto dispatch;
L_002df0d4:
 STEP(UINT32_C(0x002df0d4)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002df0d8));goto dispatch;
L_002df0d8:
 STEP(UINT32_C(0x002df0d8)); /* 080b902e j 002e40b8 */
 STEP(UINT32_C(0x002df0dc));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002df0dc:
 STEP(UINT32_C(0x002df0dc)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x002df0e0));goto dispatch;
L_002df208:
 STEP(UINT32_C(0x002df208)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002df20c));goto dispatch;
L_002df20c:
 STEP(UINT32_C(0x002df20c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002df210));goto dispatch;
L_002df210:
 STEP(UINT32_C(0x002df210)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002df214));goto dispatch;
L_002df214:
 STEP(UINT32_C(0x002df214)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002df218));goto dispatch;
L_002df218:
 STEP(UINT32_C(0x002df218)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002df220));STEP(UINT32_C(0x002df21c));set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002df21c:
 STEP(UINT32_C(0x002df21c)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002df220));goto dispatch;
L_002df220:
 STEP(UINT32_C(0x002df220)); /* 8e11000c lw s1,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,17u,sx(value32));target=sx(UINT32_C(0x002df224));goto dispatch;
L_002df224:
 STEP(UINT32_C(0x002df224)); /* 56200003 bnel s1,zero,002df234 */
 if(lo(m,17u)!=lo(m,0u)){STEP(UINT32_C(0x002df228));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000003c),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002df234));}else target=sx(UINT32_C(0x002df22c));goto dispatch;
L_002df228:
 STEP(UINT32_C(0x002df228)); /* 8e23003c lw v1,0x3c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000003c),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002df22c));goto dispatch;
L_002df22c:
 STEP(UINT32_C(0x002df22c)); /* 10000004 beq zero,zero,002df240 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002df230));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002df240):UINT32_C(0x002df234));goto dispatch;}
L_002df230:
 STEP(UINT32_C(0x002df230)); /* ae000004 sw zero,0x4(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002df234));goto dispatch;
L_002df234:
 STEP(UINT32_C(0x002df234)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002df238));goto dispatch;
L_002df238:
 STEP(UINT32_C(0x002df238)); /* ae020004 sw v0,0x4(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002df23c));goto dispatch;
L_002df23c:
 STEP(UINT32_C(0x002df23c)); /* ae03000c sw v1,0xc(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002df240));goto dispatch;
L_002df240:
 STEP(UINT32_C(0x002df240)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002df248));STEP(UINT32_C(0x002df244));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002df244:
 STEP(UINT32_C(0x002df244)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df248));goto dispatch;
L_002df248:
 STEP(UINT32_C(0x002df248)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002df24c));goto dispatch;
L_002df24c:
 STEP(UINT32_C(0x002df24c)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002df250));goto dispatch;
L_002df250:
 STEP(UINT32_C(0x002df250)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002df254));goto dispatch;
L_002df254:
 STEP(UINT32_C(0x002df254)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002df258));goto dispatch;
L_002df258:
 STEP(UINT32_C(0x002df258)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002df25c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002df25c:
 STEP(UINT32_C(0x002df25c)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002df260));goto dispatch;
L_002df428:
 STEP(UINT32_C(0x002df428)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002df42c));goto dispatch;
L_002df42c:
 STEP(UINT32_C(0x002df42c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002df430));goto dispatch;
L_002df430:
 STEP(UINT32_C(0x002df430)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002df434));goto dispatch;
L_002df434:
 STEP(UINT32_C(0x002df434)); /* 10000004 beq zero,zero,002df448 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002df438));set(m,16u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x002df448):UINT32_C(0x002df43c));goto dispatch;}
L_002df438:
 STEP(UINT32_C(0x002df438)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002df43c));goto dispatch;
L_002df43c:
 STEP(UINT32_C(0x002df43c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df440));goto dispatch;
L_002df440:
 STEP(UINT32_C(0x002df440)); /* 0c0b7c98 jal 002df260 */
 set(m,31u,UINT64_C(0x002df448));STEP(UINT32_C(0x002df444));/* nop */target=sx(UINT32_C(0x002df260));goto dispatch;
L_002df444:
 STEP(UINT32_C(0x002df444)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df448));goto dispatch;
L_002df448:
 STEP(UINT32_C(0x002df448)); /* 0c0b7c82 jal 002df208 */
 set(m,31u,UINT64_C(0x002df450));STEP(UINT32_C(0x002df44c));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002df208));goto dispatch;
L_002df44c:
 STEP(UINT32_C(0x002df44c)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002df450));goto dispatch;
L_002df450:
 STEP(UINT32_C(0x002df450)); /* 1440fffb bne v0,zero,002df440 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002df454));set(m,4u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002df440):UINT32_C(0x002df458));goto dispatch;}
L_002df454:
 STEP(UINT32_C(0x002df454)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002df458));goto dispatch;
L_002df458:
 STEP(UINT32_C(0x002df458)); /* 0c0b6f70 jal 002dbdc0 */
 set(m,31u,UINT64_C(0x002df460));STEP(UINT32_C(0x002df45c));/* nop */target=sx(UINT32_C(0x002dbdc0));goto dispatch;
L_002df45c:
 STEP(UINT32_C(0x002df45c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df460));goto dispatch;
L_002df460:
 STEP(UINT32_C(0x002df460)); /* 1000fff9 beq zero,zero,002df448 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002df464));/* nop */target=sx(taken?UINT32_C(0x002df448):UINT32_C(0x002df468));goto dispatch;}
L_002df464:
 STEP(UINT32_C(0x002df464)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002df468));goto dispatch;
L_002e4070:
 STEP(UINT32_C(0x002e4070)); /* 40036000 cop0 rs0 rtv1 rd12 fn0 */
 set(m,3u,sx(m->status));target=sx(UINT32_C(0x002e4074));goto dispatch;
L_002e4074:
 STEP(UINT32_C(0x002e4074)); /* 3c020001 lui v0,zero,0x1 */
 set(m,2u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x002e4078));goto dispatch;
L_002e4078:
 STEP(UINT32_C(0x002e4078)); /* 00621824 and v1,v1,v0 */
 set(m,3u,lo(m,3u)&lo(m,2u));target=sx(UINT32_C(0x002e407c));goto dispatch;
L_002e407c:
 STEP(UINT32_C(0x002e407c)); /* 1060000b beq v1,zero,002e40ac */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002e4080));set(m,4u,lo(m,0u)<lo(m,3u));target=sx(taken?UINT32_C(0x002e40ac):UINT32_C(0x002e4084));goto dispatch;}
L_002e4080:
 STEP(UINT32_C(0x002e4080)); /* 0003202b sltu a0,zero,v1 */
 set(m,4u,lo(m,0u)<lo(m,3u));target=sx(UINT32_C(0x002e4084));goto dispatch;
L_002e4084:
 STEP(UINT32_C(0x002e4084)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e4088));goto dispatch;
L_002e4088:
 STEP(UINT32_C(0x002e4088)); /* 42000039 cop0 rs16 rtzero rd0 fn57 */
 if((m->status&0x20006u)||(m->status&0x18u)==0u)m->status&=~UINT32_C(0x10000);target=sx(UINT32_C(0x002e408c));goto dispatch;
L_002e408c:
 STEP(UINT32_C(0x002e408c)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x002e4090));goto dispatch;
L_002e4090:
 STEP(UINT32_C(0x002e4090)); /* 40026000 cop0 rs0 rtv0 rd12 fn0 */
 set(m,2u,sx(m->status));target=sx(UINT32_C(0x002e4094));goto dispatch;
L_002e4094:
 STEP(UINT32_C(0x002e4094)); /* 3c030001 lui v1,zero,0x1 */
 set(m,3u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x002e4098));goto dispatch;
L_002e4098:
 STEP(UINT32_C(0x002e4098)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002e409c));goto dispatch;
L_002e409c:
 STEP(UINT32_C(0x002e409c)); /* 1440fffa bne v0,zero,002e4088 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002e40a0));/* nop */target=sx(taken?UINT32_C(0x002e4088):UINT32_C(0x002e40a4));goto dispatch;}
L_002e40a0:
 STEP(UINT32_C(0x002e40a0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e40a4));goto dispatch;
L_002e40a4:
 STEP(UINT32_C(0x002e40a4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e40a8));set(m,2u,lo(m,4u)+lo(m,0u));goto dispatch;
L_002e40a8:
 STEP(UINT32_C(0x002e40a8)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e40ac));goto dispatch;
L_002e40ac:
 STEP(UINT32_C(0x002e40ac)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e40b0));goto dispatch;
L_002e40b0:
 STEP(UINT32_C(0x002e40b0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e40b4));set(m,2u,lo(m,4u)+lo(m,0u));goto dispatch;
L_002e40b4:
 STEP(UINT32_C(0x002e40b4)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002e40b8:
 STEP(UINT32_C(0x002e40b8)); /* 40026000 cop0 rs0 rtv0 rd12 fn0 */
 set(m,2u,sx(m->status));target=sx(UINT32_C(0x002e40bc));goto dispatch;
L_002e40bc:
 STEP(UINT32_C(0x002e40bc)); /* 3c030001 lui v1,zero,0x1 */
 set(m,3u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x002e40c0));goto dispatch;
L_002e40c0:
 STEP(UINT32_C(0x002e40c0)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002e40c4));goto dispatch;
L_002e40c4:
 STEP(UINT32_C(0x002e40c4)); /* 42000038 cop0 rs16 rtzero rd0 fn56 */
 if((m->status&0x20006u)||(m->status&0x18u)==0u)m->status|=0x10000u;target=sx(UINT32_C(0x002e40c8));goto dispatch;
L_002e40c8:
 STEP(UINT32_C(0x002e40c8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e40cc));set(m,2u,lo(m,0u)<lo(m,2u));goto dispatch;
L_002e40cc:
 STEP(UINT32_C(0x002e40cc)); /* 0002102b sltu v0,zero,v0 */
 set(m,2u,lo(m,0u)<lo(m,2u));target=sx(UINT32_C(0x002e40d0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

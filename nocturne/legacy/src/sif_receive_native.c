#include "sif_receive_native.h"
#include <string.h>
/* Original ELF/installed-BIOS source-bound fixed statements. RAM and all MMIO are delegated
 * to the initialized memory owner; no INTC acknowledgement is synthesized.
 * The caller owns actual interrupt/SYSCALL entry, Cause/EPC/Status and clocks. */
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
uint32_t nocturneSifReceiveResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002de330):goto L_002de330;
 case UINT32_C(0x002de334):goto L_002de334;
 case UINT32_C(0x002de338):goto L_002de338;
 case UINT32_C(0x002de33c):goto L_002de33c;
 case UINT32_C(0x002de340):goto L_002de340;
 case UINT32_C(0x002de344):goto L_002de344;
 case UINT32_C(0x002de348):goto L_002de348;
 case UINT32_C(0x002de34c):goto L_002de34c;
 case UINT32_C(0x002de350):goto L_002de350;
 case UINT32_C(0x002de354):goto L_002de354;
 case UINT32_C(0x002de358):goto L_002de358;
 case UINT32_C(0x002de35c):goto L_002de35c;
 case UINT32_C(0x002de360):goto L_002de360;
 case UINT32_C(0x002de364):goto L_002de364;
 case UINT32_C(0x002de368):goto L_002de368;
 case UINT32_C(0x002de36c):goto L_002de36c;
 case UINT32_C(0x002de370):goto L_002de370;
 case UINT32_C(0x002de374):goto L_002de374;
 case UINT32_C(0x002de378):goto L_002de378;
 case UINT32_C(0x002de37c):goto L_002de37c;
 case UINT32_C(0x002de380):goto L_002de380;
 case UINT32_C(0x002de384):goto L_002de384;
 case UINT32_C(0x002de388):goto L_002de388;
 case UINT32_C(0x002de38c):goto L_002de38c;
 case UINT32_C(0x002de390):goto L_002de390;
 case UINT32_C(0x002de394):goto L_002de394;
 case UINT32_C(0x002de398):goto L_002de398;
 case UINT32_C(0x002de39c):goto L_002de39c;
 case UINT32_C(0x002de3a0):goto L_002de3a0;
 case UINT32_C(0x002de3a4):goto L_002de3a4;
 case UINT32_C(0x002de3a8):goto L_002de3a8;
 case UINT32_C(0x002de3ac):goto L_002de3ac;
 case UINT32_C(0x002de3b0):goto L_002de3b0;
 case UINT32_C(0x002de3b4):goto L_002de3b4;
 case UINT32_C(0x002de3b8):goto L_002de3b8;
 case UINT32_C(0x002de3bc):goto L_002de3bc;
 case UINT32_C(0x002de3c0):goto L_002de3c0;
 case UINT32_C(0x002de3c4):goto L_002de3c4;
 case UINT32_C(0x002de3c8):goto L_002de3c8;
 case UINT32_C(0x002de3cc):goto L_002de3cc;
 case UINT32_C(0x002de3d0):goto L_002de3d0;
 case UINT32_C(0x002de3d4):goto L_002de3d4;
 case UINT32_C(0x002de3d8):goto L_002de3d8;
 case UINT32_C(0x002de3dc):goto L_002de3dc;
 case UINT32_C(0x002de3e0):goto L_002de3e0;
 case UINT32_C(0x002de3e4):goto L_002de3e4;
 case UINT32_C(0x002de3e8):goto L_002de3e8;
 case UINT32_C(0x002de3ec):goto L_002de3ec;
 case UINT32_C(0x002de3f0):goto L_002de3f0;
 case UINT32_C(0x002de3f4):goto L_002de3f4;
 case UINT32_C(0x002de3f8):goto L_002de3f8;
 case UINT32_C(0x002de3fc):goto L_002de3fc;
 case UINT32_C(0x002de400):goto L_002de400;
 case UINT32_C(0x002de404):goto L_002de404;
 case UINT32_C(0x002de408):goto L_002de408;
 case UINT32_C(0x002de40c):goto L_002de40c;
 case UINT32_C(0x002de410):goto L_002de410;
 case UINT32_C(0x002de414):goto L_002de414;
 case UINT32_C(0x002de418):goto L_002de418;
 case UINT32_C(0x002de41c):goto L_002de41c;
 case UINT32_C(0x002de420):goto L_002de420;
 case UINT32_C(0x002de424):goto L_002de424;
 case UINT32_C(0x002de428):goto L_002de428;
 case UINT32_C(0x002de42c):goto L_002de42c;
 case UINT32_C(0x002de430):goto L_002de430;
 case UINT32_C(0x002de434):goto L_002de434;
 case UINT32_C(0x002de438):goto L_002de438;
 case UINT32_C(0x002de43c):goto L_002de43c;
 case UINT32_C(0x002de440):goto L_002de440;
 case UINT32_C(0x002de444):goto L_002de444;
 case UINT32_C(0x002de448):goto L_002de448;
 case UINT32_C(0x002de44c):goto L_002de44c;
 case UINT32_C(0x002de450):goto L_002de450;
 case UINT32_C(0x002de454):goto L_002de454;
 case UINT32_C(0x002dc290):goto L_002dc290;
 case UINT32_C(0x002dc294):goto L_002dc294;
 case UINT32_C(0x002dc298):goto L_002dc298;
 case UINT32_C(0x002dc29c):goto L_002dc29c;
 case UINT32_C(0x800062a0):goto L_800062a0;
 case UINT32_C(0x800062a4):goto L_800062a4;
 case UINT32_C(0x800062a8):goto L_800062a8;
 case UINT32_C(0x800062ac):goto L_800062ac;
 case UINT32_C(0x800062b0):goto L_800062b0;
 case UINT32_C(0x800062b4):goto L_800062b4;
 case UINT32_C(0x800062b8):goto L_800062b8;
 case UINT32_C(0x800062bc):goto L_800062bc;
 case UINT32_C(0x800062c0):goto L_800062c0;
 case UINT32_C(0x800062c4):goto L_800062c4;
 case UINT32_C(0x800062c8):goto L_800062c8;
 case UINT32_C(0x800062cc):goto L_800062cc;
 case UINT32_C(0x800062d0):goto L_800062d0;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002de330:
 STEP(UINT32_C(0x002de330)); /* 27bdff70 addiu sp,sp,-144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff70)));target=sx(UINT32_C(0x002de334));goto dispatch;
L_002de334:
 STEP(UINT32_C(0x002de334)); /* ffb00070 sd s0,0x70(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002de338));goto dispatch;
L_002de338:
 STEP(UINT32_C(0x002de338)); /* ffbf0080 sd ra,0x80(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002de33c));goto dispatch;
L_002de33c:
 STEP(UINT32_C(0x002de33c)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002de344));STEP(UINT32_C(0x002de340));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002de340:
 STEP(UINT32_C(0x002de340)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de344));goto dispatch;
L_002de344:
 STEP(UINT32_C(0x002de344)); /* 3c03005a lui v1,zero,0x5a */
 set(m,3u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002de348));goto dispatch;
L_002de348:
 STEP(UINT32_C(0x002de348)); /* 8c67ba98 lw a3,-0x4568(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffba98),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002de34c));goto dispatch;
L_002de34c:
 STEP(UINT32_C(0x002de34c)); /* 2470ba98 addiu s0,v1,-17768 */
 set(m,16u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffba98)));target=sx(UINT32_C(0x002de350));goto dispatch;
L_002de350:
 STEP(UINT32_C(0x002de350)); /* 90e20000 lbu v0,0x0(a3) */
 {uint8_t byte;READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002de354));goto dispatch;
L_002de354:
 STEP(UINT32_C(0x002de354)); /* 304500ff andi a1,v0,0xff */
 set(m,5u,lo(m,2u) & UINT64_C(0xff));target=sx(UINT32_C(0x002de358));goto dispatch;
L_002de358:
 STEP(UINT32_C(0x002de358)); /* 10a0003b beq a1,zero,002de448 */
 {int taken=(lo(m,5u)==lo(m,0u));STEP(UINT32_C(0x002de35c));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002de448):UINT32_C(0x002de360));goto dispatch;}
L_002de35c:
 STEP(UINT32_C(0x002de35c)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de360));goto dispatch;
L_002de360:
 STEP(UINT32_C(0x002de360)); /* 24a2000f addiu v0,a1,15 */
 set(m,2u,sx((uint32_t)lo(m,5u)+UINT32_C(0x0000000f)));target=sx(UINT32_C(0x002de364));goto dispatch;
L_002de364:
 STEP(UINT32_C(0x002de364)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002de368));goto dispatch;
L_002de368:
 STEP(UINT32_C(0x002de368)); /* 24a4001e addiu a0,a1,30 */
 set(m,4u,sx((uint32_t)lo(m,5u)+UINT32_C(0x0000001e)));target=sx(UINT32_C(0x002de36c));goto dispatch;
L_002de36c:
 STEP(UINT32_C(0x002de36c)); /* 0062182a slt v1,v1,v0 */
 set(m,3u,((int64_t)lo(m,3u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x002de370));goto dispatch;
L_002de370:
 STEP(UINT32_C(0x002de370)); /* 0043200b movn a0,v0,v1 */
 if(lo(m,3u)!=0u)set(m,4u,lo(m,2u));target=sx(UINT32_C(0x002de374));goto dispatch;
L_002de374:
 STEP(UINT32_C(0x002de374)); /* 00e0302d daddu a2,a3,zero */
 set(m,6u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002de378));goto dispatch;
L_002de378:
 STEP(UINT32_C(0x002de378)); /* 00042903 sra a1,a0,4 */
 set(m,5u,sx((uint32_t)((int32_t)lo(m,4u)>>4u)));target=sx(UINT32_C(0x002de37c));goto dispatch;
L_002de37c:
 STEP(UINT32_C(0x002de37c)); /* a0e00000 sb zero,0x0(a3) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002de380));goto dispatch;
L_002de380:
 STEP(UINT32_C(0x002de380)); /* 18a0000a blez a1,zero,002de3ac */
 {int taken=((int64_t)lo(m,5u)<=0);STEP(UINT32_C(0x002de384));set(m,4u,lo(m,5u)+lo(m,0u));target=sx(taken?UINT32_C(0x002de3ac):UINT32_C(0x002de388));goto dispatch;}
L_002de384:
 STEP(UINT32_C(0x002de384)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002de388));goto dispatch;
L_002de388:
 STEP(UINT32_C(0x002de388)); /* 03a0182d daddu v1,sp,zero */
 set(m,3u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002de38c));goto dispatch;
L_002de38c:
 STEP(UINT32_C(0x002de38c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de390));goto dispatch;
L_002de390:
 STEP(UINT32_C(0x002de390)); /* 78c20000 lq v0,0x0(a2) */
 {uint32_t q[4];READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x002de394));goto dispatch;
L_002de394:
 STEP(UINT32_C(0x002de394)); /* 2484ffff addiu a0,a0,-1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002de398));goto dispatch;
L_002de398:
 STEP(UINT32_C(0x002de398)); /* 24c60010 addiu a2,a2,16 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002de39c));goto dispatch;
L_002de39c:
 STEP(UINT32_C(0x002de39c)); /* 7c620000 sq v0,0x0(v1) */
 WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),m->gpr[2],16u);target=sx(UINT32_C(0x002de3a0));goto dispatch;
L_002de3a0:
 STEP(UINT32_C(0x002de3a0)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002de3a4));goto dispatch;
L_002de3a4:
 STEP(UINT32_C(0x002de3a4)); /* 1480fffa bne a0,zero,002de390 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002de3a8));/* nop */target=sx(taken?UINT32_C(0x002de390):UINT32_C(0x002de3ac));goto dispatch;}
L_002de3a8:
 STEP(UINT32_C(0x002de3a8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de3ac));goto dispatch;
L_002de3ac:
 STEP(UINT32_C(0x002de3ac)); /* 0c0b70a4 jal 002dc290 */
 set(m,31u,UINT64_C(0x002de3b4));STEP(UINT32_C(0x002de3b0));/* nop */target=sx(UINT32_C(0x002dc290));goto dispatch;
L_002de3b0:
 STEP(UINT32_C(0x002de3b0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de3b4));goto dispatch;
L_002de3b4:
 STEP(UINT32_C(0x002de3b4)); /* 8fa30008 lw v1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de3b8));goto dispatch;
L_002de3b8:
 STEP(UINT32_C(0x002de3b8)); /* 04610013 regimm1 v1,002de408 */
 {int taken=((int64_t)lo(m,3u)>=0);STEP(UINT32_C(0x002de3bc));/* nop */target=sx(taken?UINT32_C(0x002de408):UINT32_C(0x002de3c0));goto dispatch;}
L_002de3bc:
 STEP(UINT32_C(0x002de3bc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de3c0));goto dispatch;
L_002de3c0:
 STEP(UINT32_C(0x002de3c0)); /* 8fa20008 lw v0,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de3c4));goto dispatch;
L_002de3c4:
 STEP(UINT32_C(0x002de3c4)); /* 3c037fff lui v1,zero,0x7fff */
 set(m,3u,sx(UINT32_C(0x7fff0000)));target=sx(UINT32_C(0x002de3c8));goto dispatch;
L_002de3c8:
 STEP(UINT32_C(0x002de3c8)); /* 3463ffff ori v1,v1,0xffff */
 set(m,3u,lo(m,3u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002de3cc));goto dispatch;
L_002de3cc:
 STEP(UINT32_C(0x002de3cc)); /* 8e040010 lw a0,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de3d0));goto dispatch;
L_002de3d0:
 STEP(UINT32_C(0x002de3d0)); /* 00432824 and a1,v0,v1 */
 set(m,5u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002de3d4));goto dispatch;
L_002de3d4:
 STEP(UINT32_C(0x002de3d4)); /* 00a4202a slt a0,a1,a0 */
 set(m,4u,((int64_t)lo(m,5u)<(int64_t)lo(m,4u)));target=sx(UINT32_C(0x002de3d8));goto dispatch;
L_002de3d8:
 STEP(UINT32_C(0x002de3d8)); /* 10800018 beq a0,zero,002de43c */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x002de3dc));set(m,2u,sx((uint32_t)lo(m,5u)<<3u));target=sx(taken?UINT32_C(0x002de43c):UINT32_C(0x002de3e0));goto dispatch;}
L_002de3dc:
 STEP(UINT32_C(0x002de3dc)); /* 000510c0 sll v0,a1,3 */
 set(m,2u,sx((uint32_t)lo(m,5u)<<3u));target=sx(UINT32_C(0x002de3e0));goto dispatch;
L_002de3e0:
 STEP(UINT32_C(0x002de3e0)); /* 8e03000c lw v1,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de3e4));goto dispatch;
L_002de3e4:
 STEP(UINT32_C(0x002de3e4)); /* 00431021 addu v0,v0,v1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002de3e8));goto dispatch;
L_002de3e8:
 STEP(UINT32_C(0x002de3e8)); /* 8c460000 lw a2,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002de3ec));goto dispatch;
L_002de3ec:
 STEP(UINT32_C(0x002de3ec)); /* 10c00013 beq a2,zero,002de43c */
 {int taken=(lo(m,6u)==lo(m,0u));STEP(UINT32_C(0x002de3f0));/* nop */target=sx(taken?UINT32_C(0x002de43c):UINT32_C(0x002de3f4));goto dispatch;}
L_002de3f0:
 STEP(UINT32_C(0x002de3f0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de3f4));goto dispatch;
L_002de3f4:
 STEP(UINT32_C(0x002de3f4)); /* 8c450004 lw a1,0x4(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002de3f8));goto dispatch;
L_002de3f8:
 STEP(UINT32_C(0x002de3f8)); /* 00c0f809 jalr ra,a2 */
 target=sx((uint32_t)lo(m,6u));set(m,31u,UINT64_C(0x002de400));STEP(UINT32_C(0x002de3fc));set(m,4u,lo(m,29u)+lo(m,0u));goto dispatch;
L_002de3fc:
 STEP(UINT32_C(0x002de3fc)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002de400));goto dispatch;
L_002de400:
 STEP(UINT32_C(0x002de400)); /* 1000000e beq zero,zero,002de43c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de404));/* nop */target=sx(taken?UINT32_C(0x002de43c):UINT32_C(0x002de408));goto dispatch;}
L_002de404:
 STEP(UINT32_C(0x002de404)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de408));goto dispatch;
L_002de408:
 STEP(UINT32_C(0x002de408)); /* 8fa50008 lw a1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002de40c));goto dispatch;
L_002de40c:
 STEP(UINT32_C(0x002de40c)); /* 8e020018 lw v0,0x18(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de410));goto dispatch;
L_002de410:
 STEP(UINT32_C(0x002de410)); /* 00a2102a slt v0,a1,v0 */
 set(m,2u,((int64_t)lo(m,5u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x002de414));goto dispatch;
L_002de414:
 STEP(UINT32_C(0x002de414)); /* 10400009 beq v0,zero,002de43c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002de418));set(m,2u,sx((uint32_t)lo(m,5u)<<3u));target=sx(taken?UINT32_C(0x002de43c):UINT32_C(0x002de41c));goto dispatch;}
L_002de418:
 STEP(UINT32_C(0x002de418)); /* 000510c0 sll v0,a1,3 */
 set(m,2u,sx((uint32_t)lo(m,5u)<<3u));target=sx(UINT32_C(0x002de41c));goto dispatch;
L_002de41c:
 STEP(UINT32_C(0x002de41c)); /* 8e030014 lw v1,0x14(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de420));goto dispatch;
L_002de420:
 STEP(UINT32_C(0x002de420)); /* 00431021 addu v0,v0,v1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002de424));goto dispatch;
L_002de424:
 STEP(UINT32_C(0x002de424)); /* 8c460000 lw a2,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002de428));goto dispatch;
L_002de428:
 STEP(UINT32_C(0x002de428)); /* 10c00004 beq a2,zero,002de43c */
 {int taken=(lo(m,6u)==lo(m,0u));STEP(UINT32_C(0x002de42c));/* nop */target=sx(taken?UINT32_C(0x002de43c):UINT32_C(0x002de430));goto dispatch;}
L_002de42c:
 STEP(UINT32_C(0x002de42c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de430));goto dispatch;
L_002de430:
 STEP(UINT32_C(0x002de430)); /* 8c450004 lw a1,0x4(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002de434));goto dispatch;
L_002de434:
 STEP(UINT32_C(0x002de434)); /* 00c0f809 jalr ra,a2 */
 target=sx((uint32_t)lo(m,6u));set(m,31u,UINT64_C(0x002de43c));STEP(UINT32_C(0x002de438));set(m,4u,lo(m,29u)+lo(m,0u));goto dispatch;
L_002de438:
 STEP(UINT32_C(0x002de438)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002de43c));goto dispatch;
L_002de43c:
 STEP(UINT32_C(0x002de43c)); /* 0000000f sync 0 */
 ++m->sync_p; /* Shared barrier counter includes native SYNC0; no physical timing supplied. */target=sx(UINT32_C(0x002de440));goto dispatch;
L_002de440:
 STEP(UINT32_C(0x002de440)); /* 42000038 cop0 rs16 rtzero rd0 fn56 */
 if((m->status&0x20006u)!=0u||(m->status&0x18u)==0u)m->status|=0x10000u;target=sx(UINT32_C(0x002de444));goto dispatch;
L_002de444:
 STEP(UINT32_C(0x002de444)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de448));goto dispatch;
L_002de448:
 STEP(UINT32_C(0x002de448)); /* dfbf0080 ld ra,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de44c));goto dispatch;
L_002de44c:
 STEP(UINT32_C(0x002de44c)); /* dfb00070 ld s0,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de450));goto dispatch;
L_002de450:
 STEP(UINT32_C(0x002de450)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de454));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));goto dispatch;
L_002de454:
 STEP(UINT32_C(0x002de454)); /* 27bd0090 addiu sp,sp,144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002dc290:
 STEP(UINT32_C(0x002dc290)); /* 2403ff88 addiu v1,zero,-120 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff88)));target=sx(UINT32_C(0x002dc294));goto dispatch;
L_002dc294:
 m->pc=UINT32_C(0x002dc294); /* SYS unexecuted; router owns exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dc298:
 STEP(UINT32_C(0x002dc298)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc29c));/* nop */goto dispatch;
L_002dc29c:
 STEP(UINT32_C(0x002dc29c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc2a0));goto dispatch;
L_800062a0:
 STEP(UINT32_C(0x800062a0)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x800062a4));goto dispatch;
L_800062a4:
 STEP(UINT32_C(0x800062a4)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x800062a8));goto dispatch;
L_800062a8:
 STEP(UINT32_C(0x800062a8)); /* 3463c000 ori v1,v1,0xc000 */
 set(m,3u,lo(m,3u) | UINT64_C(0xc000));target=sx(UINT32_C(0x800062ac));goto dispatch;
L_800062ac:
 STEP(UINT32_C(0x800062ac)); /* 3442c020 ori v0,v0,0xc020 */
 set(m,2u,lo(m,2u) | UINT64_C(0xc020));target=sx(UINT32_C(0x800062b0));goto dispatch;
L_800062b0:
 STEP(UINT32_C(0x800062b0)); /* ac600000 sw zero,0x0(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800062b4));goto dispatch;
L_800062b4:
 STEP(UINT32_C(0x800062b4)); /* 24040184 addiu a0,zero,388 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000184)));target=sx(UINT32_C(0x800062b8));goto dispatch;
L_800062b8:
 STEP(UINT32_C(0x800062b8)); /* ac400000 sw zero,0x0(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800062bc));goto dispatch;
L_800062bc:
 STEP(UINT32_C(0x800062bc)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x800062c0));goto dispatch;
L_800062c0:
 STEP(UINT32_C(0x800062c0)); /* ac640000 sw a0,0x0(v1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800062c4));goto dispatch;
L_800062c4:
 STEP(UINT32_C(0x800062c4)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800062c8));goto dispatch;
L_800062c8:
 STEP(UINT32_C(0x800062c8)); /* afa20000 sw v0,0x0(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800062cc));goto dispatch;
L_800062cc:
 STEP(UINT32_C(0x800062cc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800062d0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_800062d0:
 STEP(UINT32_C(0x800062d0)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x800062d4));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

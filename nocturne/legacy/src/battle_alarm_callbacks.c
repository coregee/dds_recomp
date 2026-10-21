#include "battle_alarm_callbacks.h"
#include <string.h>
_Static_assert(sizeof(NocturneWakeupMachine)==720u,"one actual shared720B machine");
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint64_t unpack(const uint8_t *p,unsigned n)
{uint64_t v=0;unsigned i;for(i=0;i<n;++i)v|=(uint64_t)p[i]<<(8u*i);return v;}
static void pack(uint8_t *p,uint64_t v,unsigned n)
{unsigned i;for(i=0;i<n;++i)p[i]=(uint8_t)(v>>(8u*i));}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
uint32_t nocturneBattleAlarmCallbacks(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
{
 uint64_t started,value=0;uint32_t target,address=0;uint8_t bytes[8];
 if(!m||!ram||!ram->read||!ram->write||!s)return NOCTURNE_WAKEUP_INPUT_DOMAIN;
 memset(s,0,sizeof(*s));
 if(m->gpr[0][0]||m->gpr[0][1]||m->gpr[0][2]||m->gpr[0][3])return stop(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN,0,0,0);
 if(!limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);
 started=m->instructions;target=m->pc;
#define STEP(p) do{m->pc=(p);if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);++m->instructions;}while(0)
#define READ(a,n) do{address=(a);if((address&((n)-1u))||!ram->read(ram->owner,address,bytes,(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);value=unpack(bytes,(n));}while(0)
#define WRITE(a,n,v) do{address=(a);pack(bytes,(v),(n));if((address&((n)-1u))||!ram->write(ram->owner,address,bytes,(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);}while(0)
dispatch:
 switch(target){
 case UINT32_C(0x002a8508):goto L_002a8508;
 case UINT32_C(0x002a850c):goto L_002a850c;
 case UINT32_C(0x002a8510):goto L_002a8510;
 case UINT32_C(0x002a8514):goto L_002a8514;
 case UINT32_C(0x002a8518):goto L_002a8518;
 case UINT32_C(0x002a851c):goto L_002a851c;
 case UINT32_C(0x002dcd50):goto L_002dcd50;
 case UINT32_C(0x002dcd54):goto L_002dcd54;
 case UINT32_C(0x002dcd58):goto L_002dcd58;
 case UINT32_C(0x002dcd5c):goto L_002dcd5c;
 case UINT32_C(0x002dcd60):goto L_002dcd60;
 case UINT32_C(0x002dcd64):goto L_002dcd64;
 case UINT32_C(0x002dcd68):goto L_002dcd68;
 case UINT32_C(0x002dcd6c):goto L_002dcd6c;
 case UINT32_C(0x002dcd70):goto L_002dcd70;
 case UINT32_C(0x002dcd74):goto L_002dcd74;
 case UINT32_C(0x002dcd78):goto L_002dcd78;
 case UINT32_C(0x002dcd7c):goto L_002dcd7c;
 case UINT32_C(0x002dcd80):goto L_002dcd80;
 case UINT32_C(0x002dcd84):goto L_002dcd84;
 case UINT32_C(0x002dcd88):goto L_002dcd88;
 case UINT32_C(0x002dcd8c):goto L_002dcd8c;
 case UINT32_C(0x002dcd90):goto L_002dcd90;
 case UINT32_C(0x002dcd94):goto L_002dcd94;
 case UINT32_C(0x002dcd98):goto L_002dcd98;
 case UINT32_C(0x002dcd9c):goto L_002dcd9c;
 case UINT32_C(0x002dcda0):goto L_002dcda0;
 case UINT32_C(0x002dcda4):goto L_002dcda4;
 case UINT32_C(0x002dcda8):goto L_002dcda8;
 case UINT32_C(0x002dcdac):goto L_002dcdac;
 case UINT32_C(0x002dcdb0):goto L_002dcdb0;
 case UINT32_C(0x002dcdb4):goto L_002dcdb4;
 case UINT32_C(0x002dcdb8):goto L_002dcdb8;
 case UINT32_C(0x002dcdbc):goto L_002dcdbc;
 case UINT32_C(0x002dcdc0):goto L_002dcdc0;
 case UINT32_C(0x002dcdc4):goto L_002dcdc4;
 case UINT32_C(0x002dcdc8):goto L_002dcdc8;
 case UINT32_C(0x002dcdcc):goto L_002dcdcc;
 case UINT32_C(0x002dcdd0):goto L_002dcdd0;
 case UINT32_C(0x002dcdd4):goto L_002dcdd4;
 case UINT32_C(0x002dcdd8):goto L_002dcdd8;
 case UINT32_C(0x002dcddc):goto L_002dcddc;
 case UINT32_C(0x002dcde0):goto L_002dcde0;
 case UINT32_C(0x002dbde0):goto L_002dbde0;
 case UINT32_C(0x002dbde4):goto L_002dbde4;
 case UINT32_C(0x002dbde8):goto L_002dbde8;
 case UINT32_C(0x002dbdec):goto L_002dbdec;
 case UINT32_C(0x002dbed0):goto L_002dbed0;
 case UINT32_C(0x002dbed4):goto L_002dbed4;
 case UINT32_C(0x002dbed8):goto L_002dbed8;
 case UINT32_C(0x002dbedc):goto L_002dbedc;
 case UINT32_C(0x002cb328):goto L_002cb328;
 case UINT32_C(0x002cb32c):goto L_002cb32c;
 case UINT32_C(0x002cb330):goto L_002cb330;
 case UINT32_C(0x002cb334):goto L_002cb334;
 case UINT32_C(0x002cb338):goto L_002cb338;
 case UINT32_C(0x002cb33c):goto L_002cb33c;
 case UINT32_C(0x002cb340):goto L_002cb340;
 case UINT32_C(0x002cb344):goto L_002cb344;
 case UINT32_C(0x002cb348):goto L_002cb348;
 default:m->pc=target;return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(target));}
L_002a8508:
 STEP(UINT32_C(0x002a8508)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=UINT32_C(0x002a850c);goto dispatch;
L_002a850c:
 STEP(UINT32_C(0x002a850c)); /* 00c0202d daddu a0,a2,zero */
 set(m,4u,lo(m,6u)+lo(m,0u));target=UINT32_C(0x002a8510);goto dispatch;
L_002a8510:
 STEP(UINT32_C(0x002a8510)); /* ffbf0000 sd ra,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,31u));target=UINT32_C(0x002a8514);goto dispatch;
L_002a8514:
 STEP(UINT32_C(0x002a8514)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,31u,value);target=UINT32_C(0x002a8518);goto dispatch;
L_002a8518:
 STEP(UINT32_C(0x002a8518)); /* 080b7354 j 002dcd50 */
 STEP(UINT32_C(0x002a851c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=UINT32_C(0x002dcd50);goto dispatch;
L_002a851c:
 STEP(UINT32_C(0x002a851c)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=UINT32_C(0x002a8520);goto dispatch;
L_002dcd50:
 STEP(UINT32_C(0x002dcd50)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=UINT32_C(0x002dcd54);goto dispatch;
L_002dcd54:
 STEP(UINT32_C(0x002dcd54)); /* ffbf0010 sd ra,0x10(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u,lo(m,31u));target=UINT32_C(0x002dcd58);goto dispatch;
L_002dcd58:
 STEP(UINT32_C(0x002dcd58)); /* ffb00000 sd s0,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,16u));target=UINT32_C(0x002dcd5c);goto dispatch;
L_002dcd5c:
 STEP(UINT32_C(0x002dcd5c)); /* 2403ffd1 addiu v1,zero,-47 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffd1)));target=UINT32_C(0x002dcd60);goto dispatch;
L_002dcd60:
 m->pc=UINT32_C(0x002dcd60); /* 0000000c syscall: unexecuted transfer */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,sx(m->pc));
L_002dcd64:
 STEP(UINT32_C(0x002dcd64)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=UINT32_C(0x002dcd68);goto dispatch;
L_002dcd68:
 STEP(UINT32_C(0x002dcd68)); /* 12040005 beq s0,a0,002dcd80 */
 {int taken=(lo(m,16u)==lo(m,4u));STEP(UINT32_C(0x002dcd6c));set(m,2u,(lo(m,16u)<UINT64_C(0x100)));target=taken?UINT32_C(0x002dcd80):UINT32_C(0x002dcd70);goto dispatch;}
L_002dcd6c:
 STEP(UINT32_C(0x002dcd6c)); /* 2e020100 sltiu v0,s0,256 */
 set(m,2u,(lo(m,16u)<UINT64_C(0x100)));target=UINT32_C(0x002dcd70);goto dispatch;
L_002dcd70:
 STEP(UINT32_C(0x002dcd70)); /* 0c0b6f78 jal 002dbde0 */
 set(m,31u,UINT64_C(0x002dcd78));STEP(UINT32_C(0x002dcd74));/* nop */target=UINT32_C(0x002dbde0);goto dispatch;
L_002dcd74:
 STEP(UINT32_C(0x002dcd74)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x002dcd78);goto dispatch;
L_002dcd78:
 STEP(UINT32_C(0x002dcd78)); /* 10000017 beq zero,zero,002dcdd8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dcd7c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u);set(m,31u,value);target=taken?UINT32_C(0x002dcdd8):UINT32_C(0x002dcd80);goto dispatch;}
L_002dcd7c:
 STEP(UINT32_C(0x002dcd7c)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u);set(m,31u,value);target=UINT32_C(0x002dcd80);goto dispatch;
L_002dcd80:
 STEP(UINT32_C(0x002dcd80)); /* 10400004 beq v0,zero,002dcd94 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002dcd84));set(m,2u,sx(UINT32_C(0x00530000)));target=taken?UINT32_C(0x002dcd94):UINT32_C(0x002dcd88);goto dispatch;}
L_002dcd84:
 STEP(UINT32_C(0x002dcd84)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=UINT32_C(0x002dcd88);goto dispatch;
L_002dcd88:
 STEP(UINT32_C(0x002dcd88)); /* 8c43c2ac lw v1,-0x3d54(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc2ac),4u);set(m,3u,sx((uint32_t)value));target=UINT32_C(0x002dcd8c);goto dispatch;
L_002dcd8c:
 STEP(UINT32_C(0x002dcd8c)); /* 14600003 bne v1,zero,002dcd9c */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002dcd90));set(m,3u,sx(UINT32_C(0x005a0000)));target=taken?UINT32_C(0x002dcd9c):UINT32_C(0x002dcd94);goto dispatch;}
L_002dcd90:
 STEP(UINT32_C(0x002dcd90)); /* 3c03005a lui v1,zero,0x5a */
 set(m,3u,sx(UINT32_C(0x005a0000)));target=UINT32_C(0x002dcd94);goto dispatch;
L_002dcd94:
 STEP(UINT32_C(0x002dcd94)); /* 1000000f beq zero,zero,002dcdd4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dcd98));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=taken?UINT32_C(0x002dcdd4):UINT32_C(0x002dcd9c);goto dispatch;}
L_002dcd98:
 STEP(UINT32_C(0x002dcd98)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=UINT32_C(0x002dcd9c);goto dispatch;
L_002dcd9c:
 STEP(UINT32_C(0x002dcd9c)); /* 3c05005a lui a1,zero,0x5a */
 set(m,5u,sx(UINT32_C(0x005a0000)));target=UINT32_C(0x002dcda0);goto dispatch;
L_002dcda0:
 STEP(UINT32_C(0x002dcda0)); /* 2463b178 addiu v1,v1,-20104 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffb178)));target=UINT32_C(0x002dcda4);goto dispatch;
L_002dcda4:
 STEP(UINT32_C(0x002dcda4)); /* 8ca4b170 lw a0,-0x4e90(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0xffffb170),4u);set(m,4u,sx((uint32_t)value));target=UINT32_C(0x002dcda8);goto dispatch;
L_002dcda8:
 STEP(UINT32_C(0x002dcda8)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x002dcdac);goto dispatch;
L_002dcdac:
 STEP(UINT32_C(0x002dcdac)); /* 304201ff andi v0,v0,0x1ff */
 set(m,2u,lo(m,2u)&UINT64_C(0x1ff));target=UINT32_C(0x002dcdb0);goto dispatch;
L_002dcdb0:
 STEP(UINT32_C(0x002dcdb0)); /* 00023040 sll a2,v0,1 */
 set(m,6u,sx((uint32_t)lo(m,2u)<<1u));target=UINT32_C(0x002dcdb4);goto dispatch;
L_002dcdb4:
 STEP(UINT32_C(0x002dcdb4)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=UINT32_C(0x002dcdb8);goto dispatch;
L_002dcdb8:
 STEP(UINT32_C(0x002dcdb8)); /* 00662821 addu a1,v1,a2 */
 set(m,5u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,6u)));target=UINT32_C(0x002dcdbc);goto dispatch;
L_002dcdbc:
 STEP(UINT32_C(0x002dcdbc)); /* ac620004 sw v0,0x4(v1) */
 WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),4u,lo(m,2u));target=UINT32_C(0x002dcdc0);goto dispatch;
L_002dcdc0:
 STEP(UINT32_C(0x002dcdc0)); /* 00a0182d daddu v1,a1,zero */
 set(m,3u,lo(m,5u)+lo(m,0u));target=UINT32_C(0x002dcdc4);goto dispatch;
L_002dcdc4:
 STEP(UINT32_C(0x002dcdc4)); /* a0a00008 sb zero,0x8(a1) */
 WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000008),1u,lo(m,0u));target=UINT32_C(0x002dcdc8);goto dispatch;
L_002dcdc8:
 STEP(UINT32_C(0x002dcdc8)); /* 0c0b6fb4 jal 002dbed0 */
 set(m,31u,UINT64_C(0x002dcdd0));STEP(UINT32_C(0x002dcdcc));WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000009),1u,lo(m,16u));target=UINT32_C(0x002dbed0);goto dispatch;
L_002dcdcc:
 STEP(UINT32_C(0x002dcdcc)); /* a0700009 sb s0,0x9(v1) */
 WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000009),1u,lo(m,16u));target=UINT32_C(0x002dcdd0);goto dispatch;
L_002dcdd0:
 STEP(UINT32_C(0x002dcdd0)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=UINT32_C(0x002dcdd4);goto dispatch;
L_002dcdd4:
 STEP(UINT32_C(0x002dcdd4)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u);set(m,31u,value);target=UINT32_C(0x002dcdd8);goto dispatch;
L_002dcdd8:
 STEP(UINT32_C(0x002dcdd8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,16u,value);target=UINT32_C(0x002dcddc);goto dispatch;
L_002dcddc:
 STEP(UINT32_C(0x002dcddc)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x002dcde0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002dcde0:
 STEP(UINT32_C(0x002dcde0)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=UINT32_C(0x002dcde4);goto dispatch;
L_002dbde0:
 STEP(UINT32_C(0x002dbde0)); /* 2403ffcc addiu v1,zero,-52 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffcc)));target=UINT32_C(0x002dbde4);goto dispatch;
L_002dbde4:
 m->pc=UINT32_C(0x002dbde4); /* 0000000c syscall: unexecuted transfer */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,sx(m->pc));
L_002dbde8:
 STEP(UINT32_C(0x002dbde8)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x002dbdec));/* nop */goto dispatch;
L_002dbdec:
 STEP(UINT32_C(0x002dbdec)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x002dbdf0);goto dispatch;
L_002dbed0:
 STEP(UINT32_C(0x002dbed0)); /* 2403ffbd addiu v1,zero,-67 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffbd)));target=UINT32_C(0x002dbed4);goto dispatch;
L_002dbed4:
 m->pc=UINT32_C(0x002dbed4); /* 0000000c syscall: unexecuted transfer */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,sx(m->pc));
L_002dbed8:
 STEP(UINT32_C(0x002dbed8)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x002dbedc));/* nop */goto dispatch;
L_002dbedc:
 STEP(UINT32_C(0x002dbedc)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x002dbee0);goto dispatch;
L_002cb328:
 STEP(UINT32_C(0x002cb328)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=UINT32_C(0x002cb32c);goto dispatch;
L_002cb32c:
 STEP(UINT32_C(0x002cb32c)); /* ffbf0000 sd ra,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,31u));target=UINT32_C(0x002cb330);goto dispatch;
L_002cb330:
 STEP(UINT32_C(0x002cb330)); /* 0c0b6fb4 jal 002dbed0 */
 set(m,31u,UINT64_C(0x002cb338));STEP(UINT32_C(0x002cb334));set(m,4u,lo(m,6u)+lo(m,0u));target=UINT32_C(0x002dbed0);goto dispatch;
L_002cb334:
 STEP(UINT32_C(0x002cb334)); /* 00c0202d daddu a0,a2,zero */
 set(m,4u,lo(m,6u)+lo(m,0u));target=UINT32_C(0x002cb338);goto dispatch;
L_002cb338:
 STEP(UINT32_C(0x002cb338)); /* 0000000f sync 0 */
 ++m->sync_p; /* actual SYNC0 value barrier; no event supplied */target=UINT32_C(0x002cb33c);goto dispatch;
L_002cb33c:
 STEP(UINT32_C(0x002cb33c)); /* 42000038 ei */
 if((m->status&UINT32_C(0x00020006))||(m->status&UINT32_C(0x18))==0u)m->status|=UINT32_C(0x00010000); /* EI: exact permission, otherwise NOP; no IRQ synthesized */target=UINT32_C(0x002cb340);goto dispatch;
L_002cb340:
 STEP(UINT32_C(0x002cb340)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,31u,value);target=UINT32_C(0x002cb344);goto dispatch;
L_002cb344:
 STEP(UINT32_C(0x002cb344)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x002cb348));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002cb348:
 STEP(UINT32_C(0x002cb348)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=UINT32_C(0x002cb34c);goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

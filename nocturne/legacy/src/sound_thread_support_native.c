#include "sound_thread_support_native.h"
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
uint32_t nocturneSoundThreadSupportResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002a8080):goto L_002a8080;
 case UINT32_C(0x002a8084):goto L_002a8084;
 case UINT32_C(0x002a8088):goto L_002a8088;
 case UINT32_C(0x002a808c):goto L_002a808c;
 case UINT32_C(0x002a8090):goto L_002a8090;
 case UINT32_C(0x002a8094):goto L_002a8094;
 case UINT32_C(0x002a8098):goto L_002a8098;
 case UINT32_C(0x002a809c):goto L_002a809c;
 case UINT32_C(0x002a80a0):goto L_002a80a0;
 case UINT32_C(0x002a80a4):goto L_002a80a4;
 case UINT32_C(0x002a80a8):goto L_002a80a8;
 case UINT32_C(0x002a80ac):goto L_002a80ac;
 case UINT32_C(0x002a80b0):goto L_002a80b0;
 case UINT32_C(0x002a80b4):goto L_002a80b4;
 case UINT32_C(0x002a80b8):goto L_002a80b8;
 case UINT32_C(0x002a80bc):goto L_002a80bc;
 case UINT32_C(0x002a80c0):goto L_002a80c0;
 case UINT32_C(0x002a80c4):goto L_002a80c4;
 case UINT32_C(0x002a80c8):goto L_002a80c8;
 case UINT32_C(0x002a80cc):goto L_002a80cc;
 case UINT32_C(0x002a80d0):goto L_002a80d0;
 case UINT32_C(0x002a80d4):goto L_002a80d4;
 case UINT32_C(0x002a80d8):goto L_002a80d8;
 case UINT32_C(0x002a80dc):goto L_002a80dc;
 case UINT32_C(0x002a80e0):goto L_002a80e0;
 case UINT32_C(0x002a80e4):goto L_002a80e4;
 case UINT32_C(0x002a80e8):goto L_002a80e8;
 case UINT32_C(0x002a80ec):goto L_002a80ec;
 case UINT32_C(0x002a80f0):goto L_002a80f0;
 case UINT32_C(0x002a80f4):goto L_002a80f4;
 case UINT32_C(0x002a80f8):goto L_002a80f8;
 case UINT32_C(0x002a80fc):goto L_002a80fc;
 case UINT32_C(0x002a8100):goto L_002a8100;
 case UINT32_C(0x002a8104):goto L_002a8104;
 case UINT32_C(0x002a8108):goto L_002a8108;
 case UINT32_C(0x002a810c):goto L_002a810c;
 case UINT32_C(0x002a8110):goto L_002a8110;
 case UINT32_C(0x002a8114):goto L_002a8114;
 case UINT32_C(0x002a8118):goto L_002a8118;
 case UINT32_C(0x002a811c):goto L_002a811c;
 case UINT32_C(0x002c2580):goto L_002c2580;
 case UINT32_C(0x002c2584):goto L_002c2584;
 case UINT32_C(0x002c2588):goto L_002c2588;
 case UINT32_C(0x002c258c):goto L_002c258c;
 case UINT32_C(0x002c2590):goto L_002c2590;
 case UINT32_C(0x002c2594):goto L_002c2594;
 case UINT32_C(0x002c2598):goto L_002c2598;
 case UINT32_C(0x002c259c):goto L_002c259c;
 case UINT32_C(0x002c25a0):goto L_002c25a0;
 case UINT32_C(0x002c25a4):goto L_002c25a4;
 case UINT32_C(0x002c25a8):goto L_002c25a8;
 case UINT32_C(0x002c25ac):goto L_002c25ac;
 case UINT32_C(0x002c25b0):goto L_002c25b0;
 case UINT32_C(0x002c25b4):goto L_002c25b4;
 case UINT32_C(0x002c25b8):goto L_002c25b8;
 case UINT32_C(0x002c25bc):goto L_002c25bc;
 case UINT32_C(0x002c25c0):goto L_002c25c0;
 case UINT32_C(0x002c25c4):goto L_002c25c4;
 case UINT32_C(0x002c25c8):goto L_002c25c8;
 case UINT32_C(0x002c25cc):goto L_002c25cc;
 case UINT32_C(0x002c25d0):goto L_002c25d0;
 case UINT32_C(0x002c25d4):goto L_002c25d4;
 case UINT32_C(0x002c25d8):goto L_002c25d8;
 case UINT32_C(0x002c25dc):goto L_002c25dc;
 case UINT32_C(0x002c25e0):goto L_002c25e0;
 case UINT32_C(0x002c25e4):goto L_002c25e4;
 case UINT32_C(0x002c25e8):goto L_002c25e8;
 case UINT32_C(0x002c25ec):goto L_002c25ec;
 case UINT32_C(0x002c25f0):goto L_002c25f0;
 case UINT32_C(0x002c25f4):goto L_002c25f4;
 case UINT32_C(0x002c25f8):goto L_002c25f8;
 case UINT32_C(0x002c25fc):goto L_002c25fc;
 case UINT32_C(0x002c2600):goto L_002c2600;
 case UINT32_C(0x002c2604):goto L_002c2604;
 case UINT32_C(0x002c2608):goto L_002c2608;
 case UINT32_C(0x002c260c):goto L_002c260c;
 case UINT32_C(0x002c2610):goto L_002c2610;
 case UINT32_C(0x002d4558):goto L_002d4558;
 case UINT32_C(0x002d455c):goto L_002d455c;
 case UINT32_C(0x002d4560):goto L_002d4560;
 case UINT32_C(0x002d4564):goto L_002d4564;
 case UINT32_C(0x002d4568):goto L_002d4568;
 case UINT32_C(0x002d456c):goto L_002d456c;
 case UINT32_C(0x002d4570):goto L_002d4570;
 case UINT32_C(0x002d4574):goto L_002d4574;
 case UINT32_C(0x002d4578):goto L_002d4578;
 case UINT32_C(0x002d457c):goto L_002d457c;
 case UINT32_C(0x002d4580):goto L_002d4580;
 case UINT32_C(0x002d4584):goto L_002d4584;
 case UINT32_C(0x002d4588):goto L_002d4588;
 case UINT32_C(0x002d458c):goto L_002d458c;
 case UINT32_C(0x002d4590):goto L_002d4590;
 case UINT32_C(0x002d4594):goto L_002d4594;
 case UINT32_C(0x002d4598):goto L_002d4598;
 case UINT32_C(0x002d459c):goto L_002d459c;
 case UINT32_C(0x002d45a0):goto L_002d45a0;
 case UINT32_C(0x002d45a4):goto L_002d45a4;
 case UINT32_C(0x002d45a8):goto L_002d45a8;
 case UINT32_C(0x002d45ac):goto L_002d45ac;
 case UINT32_C(0x002d45b0):goto L_002d45b0;
 case UINT32_C(0x002d45b4):goto L_002d45b4;
 case UINT32_C(0x002d45b8):goto L_002d45b8;
 case UINT32_C(0x002d45bc):goto L_002d45bc;
 case UINT32_C(0x002d45c0):goto L_002d45c0;
 case UINT32_C(0x002d45c4):goto L_002d45c4;
 case UINT32_C(0x002d45c8):goto L_002d45c8;
 case UINT32_C(0x002d45cc):goto L_002d45cc;
 case UINT32_C(0x002d45d0):goto L_002d45d0;
 case UINT32_C(0x002d45d4):goto L_002d45d4;
 case UINT32_C(0x002d45d8):goto L_002d45d8;
 case UINT32_C(0x002d45dc):goto L_002d45dc;
 case UINT32_C(0x002d45e0):goto L_002d45e0;
 case UINT32_C(0x002d45e4):goto L_002d45e4;
 case UINT32_C(0x002d45e8):goto L_002d45e8;
 case UINT32_C(0x002d45ec):goto L_002d45ec;
 case UINT32_C(0x002d45f0):goto L_002d45f0;
 case UINT32_C(0x002d45f4):goto L_002d45f4;
 case UINT32_C(0x002d45f8):goto L_002d45f8;
 case UINT32_C(0x002d45fc):goto L_002d45fc;
 case UINT32_C(0x002d4600):goto L_002d4600;
 case UINT32_C(0x002d4604):goto L_002d4604;
 case UINT32_C(0x002d4608):goto L_002d4608;
 case UINT32_C(0x002d460c):goto L_002d460c;
 case UINT32_C(0x002d4610):goto L_002d4610;
 case UINT32_C(0x002d4614):goto L_002d4614;
 case UINT32_C(0x002dbea0):goto L_002dbea0;
 case UINT32_C(0x002dbea4):goto L_002dbea4;
 case UINT32_C(0x002dbea8):goto L_002dbea8;
 case UINT32_C(0x002dbeac):goto L_002dbeac;
 case UINT32_C(0x002dddf0):goto L_002dddf0;
 case UINT32_C(0x002dddf4):goto L_002dddf4;
 case UINT32_C(0x002dddf8):goto L_002dddf8;
 case UINT32_C(0x002dddfc):goto L_002dddfc;
 case UINT32_C(0x002dde00):goto L_002dde00;
 case UINT32_C(0x002dde04):goto L_002dde04;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002a8080:
 STEP(UINT32_C(0x002a8080)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002a8084));goto dispatch;
L_002a8084:
 STEP(UINT32_C(0x002a8084)); /* afa40008 sw a0,0x8(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002a8088));goto dispatch;
L_002a8088:
 STEP(UINT32_C(0x002a8088)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002a808c));goto dispatch;
L_002a808c:
 STEP(UINT32_C(0x002a808c)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002a8090));goto dispatch;
L_002a8090:
 STEP(UINT32_C(0x002a8090)); /* afa50004 sw a1,0x4(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002a8094));goto dispatch;
L_002a8094:
 STEP(UINT32_C(0x002a8094)); /* 0c0b6fa8 jal 002dbea0 */
 set(m,31u,UINT64_C(0x002a809c));STEP(UINT32_C(0x002a8098));value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002dbea0));goto dispatch;
L_002a8098:
 STEP(UINT32_C(0x002a8098)); /* afa60014 sw a2,0x14(sp) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002a809c));goto dispatch;
L_002a809c:
 STEP(UINT32_C(0x002a809c)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002a80a0));goto dispatch;
L_002a80a0:
 STEP(UINT32_C(0x002a80a0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a80a4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002a80a4:
 STEP(UINT32_C(0x002a80a4)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002a80a8));goto dispatch;
L_002a80a8:
 STEP(UINT32_C(0x002a80a8)); /* 27bdffa0 addiu sp,sp,-96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffa0)));target=sx(UINT32_C(0x002a80ac));goto dispatch;
L_002a80ac:
 STEP(UINT32_C(0x002a80ac)); /* ffb10038 sd s1,0x38(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000038),&value64,8u);target=sx(UINT32_C(0x002a80b0));goto dispatch;
L_002a80b0:
 STEP(UINT32_C(0x002a80b0)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002a80b4));goto dispatch;
L_002a80b4:
 STEP(UINT32_C(0x002a80b4)); /* ffb20040 sd s2,0x40(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002a80b8));goto dispatch;
L_002a80b8:
 STEP(UINT32_C(0x002a80b8)); /* 00a0902d daddu s2,a1,zero */
 set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002a80bc));goto dispatch;
L_002a80bc:
 STEP(UINT32_C(0x002a80bc)); /* ffb30048 sd s3,0x48(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000048),&value64,8u);target=sx(UINT32_C(0x002a80c0));goto dispatch;
L_002a80c0:
 STEP(UINT32_C(0x002a80c0)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002a80c4));goto dispatch;
L_002a80c4:
 STEP(UINT32_C(0x002a80c4)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002a80c8));goto dispatch;
L_002a80c8:
 STEP(UINT32_C(0x002a80c8)); /* 24060030 addiu a2,zero,48 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002a80cc));goto dispatch;
L_002a80cc:
 STEP(UINT32_C(0x002a80cc)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002a80d0));goto dispatch;
L_002a80d0:
 STEP(UINT32_C(0x002a80d0)); /* ffb00030 sd s0,0x30(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002a80d4));goto dispatch;
L_002a80d4:
 STEP(UINT32_C(0x002a80d4)); /* ffbf0050 sd ra,0x50(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002a80d8));goto dispatch;
L_002a80d8:
 STEP(UINT32_C(0x002a80d8)); /* 0c0b5156 jal 002d4558 */
 set(m,31u,UINT64_C(0x002a80e0));STEP(UINT32_C(0x002a80dc));set(m,16u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d4558));goto dispatch;
L_002a80dc:
 STEP(UINT32_C(0x002a80dc)); /* 00e0802d daddu s0,a3,zero */
 set(m,16u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002a80e0));goto dispatch;
L_002a80e0:
 STEP(UINT32_C(0x002a80e0)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002a80e4));goto dispatch;
L_002a80e4:
 STEP(UINT32_C(0x002a80e4)); /* 24424170 addiu v0,v0,16752 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00004170)));target=sx(UINT32_C(0x002a80e8));goto dispatch;
L_002a80e8:
 STEP(UINT32_C(0x002a80e8)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002a80ec));goto dispatch;
L_002a80ec:
 STEP(UINT32_C(0x002a80ec)); /* afb30004 sw s3,0x4(sp) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002a80f0));goto dispatch;
L_002a80f0:
 STEP(UINT32_C(0x002a80f0)); /* afb20008 sw s2,0x8(sp) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002a80f4));goto dispatch;
L_002a80f4:
 STEP(UINT32_C(0x002a80f4)); /* afb1000c sw s1,0xc(sp) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002a80f8));goto dispatch;
L_002a80f8:
 STEP(UINT32_C(0x002a80f8)); /* afb00014 sw s0,0x14(sp) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002a80fc));goto dispatch;
L_002a80fc:
 STEP(UINT32_C(0x002a80fc)); /* 0c0b6f28 jal 002dbca0 */
 set(m,31u,UINT64_C(0x002a8104));STEP(UINT32_C(0x002a8100));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002dbca0));goto dispatch;
L_002a8100:
 STEP(UINT32_C(0x002a8100)); /* afa20010 sw v0,0x10(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002a8104));goto dispatch;
L_002a8104:
 STEP(UINT32_C(0x002a8104)); /* dfb00030 ld s0,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002a8108));goto dispatch;
L_002a8108:
 STEP(UINT32_C(0x002a8108)); /* dfb10038 ld s1,0x38(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000038),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002a810c));goto dispatch;
L_002a810c:
 STEP(UINT32_C(0x002a810c)); /* dfb20040 ld s2,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002a8110));goto dispatch;
L_002a8110:
 STEP(UINT32_C(0x002a8110)); /* dfb30048 ld s3,0x48(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000048),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002a8114));goto dispatch;
L_002a8114:
 STEP(UINT32_C(0x002a8114)); /* dfbf0050 ld ra,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002a8118));goto dispatch;
L_002a8118:
 STEP(UINT32_C(0x002a8118)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a811c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));goto dispatch;
L_002a811c:
 STEP(UINT32_C(0x002a811c)); /* 27bd0060 addiu sp,sp,96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002a8120));goto dispatch;
L_002c2580:
 STEP(UINT32_C(0x002c2580)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x002c2584));goto dispatch;
L_002c2584:
 STEP(UINT32_C(0x002c2584)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c2588));goto dispatch;
L_002c2588:
 STEP(UINT32_C(0x002c2588)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c258c));goto dispatch;
L_002c258c:
 STEP(UINT32_C(0x002c258c)); /* ffbf0070 sd ra,0x70(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002c2590));goto dispatch;
L_002c2590:
 STEP(UINT32_C(0x002c2590)); /* 0c0aa020 jal 002a8080 */
 set(m,31u,UINT64_C(0x002c2598));STEP(UINT32_C(0x002c2594));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002a8080));goto dispatch;
L_002c2594:
 STEP(UINT32_C(0x002c2594)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c2598));goto dispatch;
L_002c2598:
 STEP(UINT32_C(0x002c2598)); /* 1c400009 bgtz v0,zero,002c25c0 */
 {int taken=((int64_t)lo(m,2u)>0);STEP(UINT32_C(0x002c259c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfd0),&value32,4u);target=sx(taken?UINT32_C(0x002c25c0):UINT32_C(0x002c25a0));goto dispatch;}
L_002c259c:
 STEP(UINT32_C(0x002c259c)); /* af82dfd0 sw v0,-0x2030(gp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfd0),&value32,4u);target=sx(UINT32_C(0x002c25a0));goto dispatch;
L_002c25a0:
 STEP(UINT32_C(0x002c25a0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c25a4));goto dispatch;
L_002c25a4:
 STEP(UINT32_C(0x002c25a4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c25a8));goto dispatch;
L_002c25a8:
 STEP(UINT32_C(0x002c25a8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c25ac));goto dispatch;
L_002c25ac:
 STEP(UINT32_C(0x002c25ac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c25b0));goto dispatch;
L_002c25b0:
 STEP(UINT32_C(0x002c25b0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c25b4));goto dispatch;
L_002c25b4:
 STEP(UINT32_C(0x002c25b4)); /* 1000fffa beq zero,zero,002c25a0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c25b8));/* nop */target=sx(taken?UINT32_C(0x002c25a0):UINT32_C(0x002c25bc));goto dispatch;}
L_002c25b8:
 STEP(UINT32_C(0x002c25b8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c25bc));goto dispatch;
L_002c25bc:
 STEP(UINT32_C(0x002c25bc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c25c0));goto dispatch;
L_002c25c0:
 STEP(UINT32_C(0x002c25c0)); /* 0c0b6f64 jal 002dbd90 */
 set(m,31u,UINT64_C(0x002c25c8));STEP(UINT32_C(0x002c25c4));/* nop */target=sx(UINT32_C(0x002dbd90));goto dispatch;
L_002c25c4:
 STEP(UINT32_C(0x002c25c4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c25c8));goto dispatch;
L_002c25c8:
 STEP(UINT32_C(0x002c25c8)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002c25cc));goto dispatch;
L_002c25cc:
 STEP(UINT32_C(0x002c25cc)); /* 0c0b7bde jal 002def78 */
 set(m,31u,UINT64_C(0x002c25d4));STEP(UINT32_C(0x002c25d0));set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002def78));goto dispatch;
L_002c25d0:
 STEP(UINT32_C(0x002c25d0)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c25d4));goto dispatch;
L_002c25d4:
 STEP(UINT32_C(0x002c25d4)); /* 3c06002c lui a2,zero,0x2c */
 set(m,6u,sx(UINT32_C(0x002c0000)));target=sx(UINT32_C(0x002c25d8));goto dispatch;
L_002c25d8:
 STEP(UINT32_C(0x002c25d8)); /* 3c070059 lui a3,zero,0x59 */
 set(m,7u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c25dc));goto dispatch;
L_002c25dc:
 STEP(UINT32_C(0x002c25dc)); /* 3c055452 lui a1,zero,0x5452 */
 set(m,5u,sx(UINT32_C(0x54520000)));target=sx(UINT32_C(0x002c25e0));goto dispatch;
L_002c25e0:
 STEP(UINT32_C(0x002c25e0)); /* 27a40020 addiu a0,sp,32 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002c25e4));goto dispatch;
L_002c25e4:
 STEP(UINT32_C(0x002c25e4)); /* 24c62338 addiu a2,a2,9016 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00002338)));target=sx(UINT32_C(0x002c25e8));goto dispatch;
L_002c25e8:
 STEP(UINT32_C(0x002c25e8)); /* 24e73f40 addiu a3,a3,16192 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00003f40)));target=sx(UINT32_C(0x002c25ec));goto dispatch;
L_002c25ec:
 STEP(UINT32_C(0x002c25ec)); /* 34a54e53 ori a1,a1,0x4e53 */
 set(m,5u,lo(m,5u) | UINT64_C(0x4e53));target=sx(UINT32_C(0x002c25f0));goto dispatch;
L_002c25f0:
 STEP(UINT32_C(0x002c25f0)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c25f4));goto dispatch;
L_002c25f4:
 STEP(UINT32_C(0x002c25f4)); /* 0000482d daddu t1,zero,zero */
 set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c25f8));goto dispatch;
L_002c25f8:
 STEP(UINT32_C(0x002c25f8)); /* 0c0b7c04 jal 002df010 */
 set(m,31u,UINT64_C(0x002c2600));STEP(UINT32_C(0x002c25fc));set(m,10u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002df010));goto dispatch;
L_002c25fc:
 STEP(UINT32_C(0x002c25fc)); /* 03a0502d daddu t2,sp,zero */
 set(m,10u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002c2600));goto dispatch;
L_002c2600:
 STEP(UINT32_C(0x002c2600)); /* 0c0b7d0a jal 002df428 */
 set(m,31u,UINT64_C(0x002c2608));STEP(UINT32_C(0x002c2604));set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002df428));goto dispatch;
L_002c2604:
 STEP(UINT32_C(0x002c2604)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002c2608));goto dispatch;
L_002c2608:
 STEP(UINT32_C(0x002c2608)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c260c));goto dispatch;
L_002c260c:
 STEP(UINT32_C(0x002c260c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c2610));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_002c2610:
 STEP(UINT32_C(0x002c2610)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x002c2614));goto dispatch;
L_002d4558:
 STEP(UINT32_C(0x002d4558)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d455c));goto dispatch;
L_002d455c:
 STEP(UINT32_C(0x002d455c)); /* 1440001e bne v0,zero,002d45d8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d4560));set(m,3u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d45d8):UINT32_C(0x002d4564));goto dispatch;}
L_002d4560:
 STEP(UINT32_C(0x002d4560)); /* 0080182d daddu v1,a0,zero */
 set(m,3u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d4564));goto dispatch;
L_002d4564:
 STEP(UINT32_C(0x002d4564)); /* 3082000f andi v0,a0,0xf */
 set(m,2u,lo(m,4u) & UINT64_C(0xf));target=sx(UINT32_C(0x002d4568));goto dispatch;
L_002d4568:
 STEP(UINT32_C(0x002d4568)); /* 1440001b bne v0,zero,002d45d8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d456c));set(m,7u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d45d8):UINT32_C(0x002d4570));goto dispatch;}
L_002d456c:
 STEP(UINT32_C(0x002d456c)); /* 0080382d daddu a3,a0,zero */
 set(m,7u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d4570));goto dispatch;
L_002d4570:
 STEP(UINT32_C(0x002d4570)); /* 30a900ff andi t1,a1,0xff */
 set(m,9u,lo(m,5u) & UINT64_C(0xff));target=sx(UINT32_C(0x002d4574));goto dispatch;
L_002d4574:
 STEP(UINT32_C(0x002d4574)); /* 2cca0020 sltiu t2,a2,32 */
 set(m,10u,(lo(m,6u)<UINT64_C(0x20)));target=sx(UINT32_C(0x002d4578));goto dispatch;
L_002d4578:
 STEP(UINT32_C(0x002d4578)); /* 0120402d daddu t0,t1,zero */
 set(m,8u,lo(m,9u)+lo(m,0u));target=sx(UINT32_C(0x002d457c));goto dispatch;
L_002d457c:
 STEP(UINT32_C(0x002d457c)); /* 00081a38 dsll v1,t0,8 */
 set(m,3u,lo(m,8u)<<8u);target=sx(UINT32_C(0x002d4580));goto dispatch;
L_002d4580:
 STEP(UINT32_C(0x002d4580)); /* 00694025 or t0,v1,t1 */
 set(m,8u,lo(m,3u)|lo(m,9u));target=sx(UINT32_C(0x002d4584));goto dispatch;
L_002d4584:
 STEP(UINT32_C(0x002d4584)); /* 70081ee9 mmi 70081ee9 */
 {uint32_t a=m->gpr[8][0]&0xffffu,b=m->gpr[8][2]&0xffffu;a|=a<<16;b|=b<<16;m->gpr[3][0]=a;m->gpr[3][1]=a;m->gpr[3][2]=b;m->gpr[3][3]=b;}target=sx(UINT32_C(0x002d4588));goto dispatch;
L_002d4588:
 STEP(UINT32_C(0x002d4588)); /* 1540000e bne t2,zero,002d45c4 */
 {int taken=(lo(m,10u)!=lo(m,0u));STEP(UINT32_C(0x002d458c));set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(taken?UINT32_C(0x002d45c4):UINT32_C(0x002d4590));goto dispatch;}
L_002d458c:
 STEP(UINT32_C(0x002d458c)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d4590));goto dispatch;
L_002d4590:
 STEP(UINT32_C(0x002d4590)); /* 70634389 mmi 70634389 */
 {uint32_t q[4]={m->gpr[3][0],m->gpr[3][1],m->gpr[3][0],m->gpr[3][1]};memcpy(m->gpr[8],q,16u);}target=sx(UINT32_C(0x002d4594));goto dispatch;
L_002d4594:
 STEP(UINT32_C(0x002d4594)); /* 7ce80000 sq t0,0x0(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),m->gpr[8],16u);target=sx(UINT32_C(0x002d4598));goto dispatch;
L_002d4598:
 STEP(UINT32_C(0x002d4598)); /* 24c6ffe0 addiu a2,a2,-32 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d459c));goto dispatch;
L_002d459c:
 STEP(UINT32_C(0x002d459c)); /* 24e70010 addiu a3,a3,16 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d45a0));goto dispatch;
L_002d45a0:
 STEP(UINT32_C(0x002d45a0)); /* 2cc20020 sltiu v0,a2,32 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x20)));target=sx(UINT32_C(0x002d45a4));goto dispatch;
L_002d45a4:
 STEP(UINT32_C(0x002d45a4)); /* 7ce80000 sq t0,0x0(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),m->gpr[8],16u);target=sx(UINT32_C(0x002d45a8));goto dispatch;
L_002d45a8:
 STEP(UINT32_C(0x002d45a8)); /* 1040fffa beq v0,zero,002d4594 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d45ac));set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x002d4594):UINT32_C(0x002d45b0));goto dispatch;}
L_002d45ac:
 STEP(UINT32_C(0x002d45ac)); /* 24e70010 addiu a3,a3,16 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d45b0));goto dispatch;
L_002d45b0:
 STEP(UINT32_C(0x002d45b0)); /* 10000004 beq zero,zero,002d45c4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d45b4));set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(taken?UINT32_C(0x002d45c4):UINT32_C(0x002d45b8));goto dispatch;}
L_002d45b4:
 STEP(UINT32_C(0x002d45b4)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d45b8));goto dispatch;
L_002d45b8:
 STEP(UINT32_C(0x002d45b8)); /* 24c6fff8 addiu a2,a2,-8 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d45bc));goto dispatch;
L_002d45bc:
 STEP(UINT32_C(0x002d45bc)); /* 24e70008 addiu a3,a3,8 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d45c0));goto dispatch;
L_002d45c0:
 STEP(UINT32_C(0x002d45c0)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d45c4));goto dispatch;
L_002d45c4:
 STEP(UINT32_C(0x002d45c4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d45c8));goto dispatch;
L_002d45c8:
 STEP(UINT32_C(0x002d45c8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d45cc));goto dispatch;
L_002d45cc:
 STEP(UINT32_C(0x002d45cc)); /* 5040fffa beql v0,zero,002d45b8 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d45d0));value64=lo(m,3u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d45b8));}else target=sx(UINT32_C(0x002d45d4));goto dispatch;
L_002d45d0:
 STEP(UINT32_C(0x002d45d0)); /* fce30000 sd v1,0x0(a3) */
 value64=lo(m,3u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d45d4));goto dispatch;
L_002d45d4:
 STEP(UINT32_C(0x002d45d4)); /* 00e0182d daddu v1,a3,zero */
 set(m,3u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d45d8));goto dispatch;
L_002d45d8:
 STEP(UINT32_C(0x002d45d8)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002d45dc));goto dispatch;
L_002d45dc:
 STEP(UINT32_C(0x002d45dc)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d45e0));goto dispatch;
L_002d45e0:
 STEP(UINT32_C(0x002d45e0)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002d45e4));goto dispatch;
L_002d45e4:
 STEP(UINT32_C(0x002d45e4)); /* 10c2000a beq a2,v0,002d4610 */
 {int taken=(lo(m,6u)==lo(m,2u));STEP(UINT32_C(0x002d45e8));/* nop */target=sx(taken?UINT32_C(0x002d4610):UINT32_C(0x002d45ec));goto dispatch;}
L_002d45e8:
 STEP(UINT32_C(0x002d45e8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d45ec));goto dispatch;
L_002d45ec:
 STEP(UINT32_C(0x002d45ec)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002d45f0));goto dispatch;
L_002d45f0:
 STEP(UINT32_C(0x002d45f0)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002d45f4));goto dispatch;
L_002d45f4:
 STEP(UINT32_C(0x002d45f4)); /* a0650000 sb a1,0x0(v1) */
 {uint8_t byte=(uint8_t)lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d45f8));goto dispatch;
L_002d45f8:
 STEP(UINT32_C(0x002d45f8)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d45fc));goto dispatch;
L_002d45fc:
 STEP(UINT32_C(0x002d45fc)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4600));goto dispatch;
L_002d4600:
 STEP(UINT32_C(0x002d4600)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4604));goto dispatch;
L_002d4604:
 STEP(UINT32_C(0x002d4604)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4608));goto dispatch;
L_002d4608:
 STEP(UINT32_C(0x002d4608)); /* 14c2fffa bne a2,v0,002d45f4 */
 {int taken=(lo(m,6u)!=lo(m,2u));STEP(UINT32_C(0x002d460c));/* nop */target=sx(taken?UINT32_C(0x002d45f4):UINT32_C(0x002d4610));goto dispatch;}
L_002d460c:
 STEP(UINT32_C(0x002d460c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4610));goto dispatch;
L_002d4610:
 STEP(UINT32_C(0x002d4610)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d4614));set(m,2u,lo(m,4u)+lo(m,0u));goto dispatch;
L_002d4614:
 STEP(UINT32_C(0x002d4614)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d4618));goto dispatch;
L_002dbea0:
 STEP(UINT32_C(0x002dbea0)); /* 24030040 addiu v1,zero,64 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dbea4));goto dispatch;
L_002dbea4:
 m->pc=UINT32_C(0x002dbea4); /* Router owns this unexecuted SYS. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbea8:
 STEP(UINT32_C(0x002dbea8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbeac));/* nop */goto dispatch;
L_002dbeac:
 STEP(UINT32_C(0x002dbeac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbeb0));goto dispatch;
L_002dddf0:
 STEP(UINT32_C(0x002dddf0)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dddf4));goto dispatch;
L_002dddf4:
 STEP(UINT32_C(0x002dddf4)); /* 00042080 sll a0,a0,2 */
 set(m,4u,sx((uint32_t)lo(m,4u)<<2u));target=sx(UINT32_C(0x002dddf8));goto dispatch;
L_002dddf8:
 STEP(UINT32_C(0x002dddf8)); /* 2442bbc0 addiu v0,v0,-17472 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffbbc0)));target=sx(UINT32_C(0x002dddfc));goto dispatch;
L_002dddfc:
 STEP(UINT32_C(0x002dddfc)); /* 00822021 addu a0,a0,v0 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002dde00));goto dispatch;
L_002dde00:
 STEP(UINT32_C(0x002dde00)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dde04));READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));goto dispatch;
L_002dde04:
 STEP(UINT32_C(0x002dde04)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dde08));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

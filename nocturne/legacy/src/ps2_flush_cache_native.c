#include "ps2_flush_cache_native.h"
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
uint32_t nocturneFlushCacheResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s,NocturneSoundCommandCache cache,void *cache_owner)
{
 uint64_t target,started;uint32_t value32=0,address=0;
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
 case UINT32_C(0x002dc120):goto L_002dc120;
 case UINT32_C(0x002dc124):goto L_002dc124;
 case UINT32_C(0x002dc128):goto L_002dc128;
 case UINT32_C(0x002dc12c):goto L_002dc12c;
 case UINT32_C(0x80002a40):goto L_80002a40;
 case UINT32_C(0x80002a44):goto L_80002a44;
 case UINT32_C(0x80002a48):goto L_80002a48;
 case UINT32_C(0x80002a4c):goto L_80002a4c;
 case UINT32_C(0x80002a50):goto L_80002a50;
 case UINT32_C(0x80002a54):goto L_80002a54;
 case UINT32_C(0x80002a58):goto L_80002a58;
 case UINT32_C(0x80002a5c):goto L_80002a5c;
 case UINT32_C(0x80002a60):goto L_80002a60;
 case UINT32_C(0x80002a64):goto L_80002a64;
 case UINT32_C(0x80002a68):goto L_80002a68;
 case UINT32_C(0x80002a6c):goto L_80002a6c;
 case UINT32_C(0x80002a70):goto L_80002a70;
 case UINT32_C(0x80002a74):goto L_80002a74;
 case UINT32_C(0x80002a78):goto L_80002a78;
 case UINT32_C(0x80002a7c):goto L_80002a7c;
 case UINT32_C(0x80002ac0):goto L_80002ac0;
 case UINT32_C(0x80002ac4):goto L_80002ac4;
 case UINT32_C(0x80002ac8):goto L_80002ac8;
 case UINT32_C(0x80002acc):goto L_80002acc;
 case UINT32_C(0x80002ad0):goto L_80002ad0;
 case UINT32_C(0x80002ad4):goto L_80002ad4;
 case UINT32_C(0x80002ad8):goto L_80002ad8;
 case UINT32_C(0x80002adc):goto L_80002adc;
 case UINT32_C(0x80002ae0):goto L_80002ae0;
 case UINT32_C(0x80002ae4):goto L_80002ae4;
 case UINT32_C(0x80002ae8):goto L_80002ae8;
 case UINT32_C(0x80002aec):goto L_80002aec;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002dc120:
 STEP(UINT32_C(0x002dc120)); /* 24030064 addiu v1,zero,100 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000064)));target=sx(UINT32_C(0x002dc124));goto dispatch;
L_002dc124:
 m->pc=UINT32_C(0x002dc124); /* Router executes actual SYS once. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dc128:
 STEP(UINT32_C(0x002dc128)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc12c));/* nop */goto dispatch;
L_002dc12c:
 STEP(UINT32_C(0x002dc12c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc130));goto dispatch;
L_80002a40:
 STEP(UINT32_C(0x80002a40)); /* 34010001 ori at,zero,0x1 */
 set(m,1u,lo(m,0u) | UINT64_C(0x1));target=sx(UINT32_C(0x80002a44));goto dispatch;
L_80002a44:
 STEP(UINT32_C(0x80002a44)); /* 1004001e beq zero,a0,80002ac0 */
 {int taken=(lo(m,0u)==lo(m,4u));STEP(UINT32_C(0x80002a48));set(m,2u,lo(m,0u) | UINT64_C(0x2));target=sx(taken?UINT32_C(0x80002ac0):UINT32_C(0x80002a4c));goto dispatch;}
L_80002a48:
 STEP(UINT32_C(0x80002a48)); /* 34020002 ori v0,zero,0x2 */
 set(m,2u,lo(m,0u) | UINT64_C(0x2));target=sx(UINT32_C(0x80002a4c));goto dispatch;
L_80002a4c:
 STEP(UINT32_C(0x80002a4c)); /* 1024002c beq at,a0,80002b00 */
 {int taken=(lo(m,1u)==lo(m,4u));STEP(UINT32_C(0x80002a50));/* nop */target=sx(taken?UINT32_C(0x80002b00):UINT32_C(0x80002a54));goto dispatch;}
L_80002a50:
 STEP(UINT32_C(0x80002a50)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80002a54));goto dispatch;
L_80002a54:
 STEP(UINT32_C(0x80002a54)); /* 1044000a beq v0,a0,80002a80 */
 {int taken=(lo(m,2u)==lo(m,4u));STEP(UINT32_C(0x80002a58));/* nop */target=sx(taken?UINT32_C(0x80002a80):UINT32_C(0x80002a5c));goto dispatch;}
L_80002a58:
 STEP(UINT32_C(0x80002a58)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80002a5c));goto dispatch;
L_80002a5c:
 STEP(UINT32_C(0x80002a5c)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80002a60));goto dispatch;
L_80002a60:
 STEP(UINT32_C(0x80002a60)); /* afbf0000 sw ra,0x0(sp) */
 value32=(uint32_t)lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80002a64));goto dispatch;
L_80002a64:
 STEP(UINT32_C(0x80002a64)); /* 0c000ac0 jal 80002b00 */
 set(m,31u,UINT64_C(0x80002a6c));STEP(UINT32_C(0x80002a68));/* nop */target=sx(UINT32_C(0x80002b00));goto dispatch;
L_80002a68:
 STEP(UINT32_C(0x80002a68)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80002a6c));goto dispatch;
L_80002a6c:
 STEP(UINT32_C(0x80002a6c)); /* 0c000aa0 jal 80002a80 */
 set(m,31u,UINT64_C(0x80002a74));STEP(UINT32_C(0x80002a70));/* nop */target=sx(UINT32_C(0x80002a80));goto dispatch;
L_80002a70:
 STEP(UINT32_C(0x80002a70)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80002a74));goto dispatch;
L_80002a74:
 STEP(UINT32_C(0x80002a74)); /* 8fbf0000 lw ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,31u,sx(value32));target=sx(UINT32_C(0x80002a78));goto dispatch;
L_80002a78:
 STEP(UINT32_C(0x80002a78)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80002a7c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_80002a7c:
 STEP(UINT32_C(0x80002a7c)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80002a80));goto dispatch;
L_80002ac0:
 STEP(UINT32_C(0x80002ac0)); /* 24080000 addiu t0,zero,0 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000000)));target=sx(UINT32_C(0x80002ac4));goto dispatch;
L_80002ac4:
 STEP(UINT32_C(0x80002ac4)); /* 0000000f sync 0 */
 ++m->sync_p;target=sx(UINT32_C(0x80002ac8));goto dispatch;
L_80002ac8:
 STEP(UINT32_C(0x80002ac8)); /* bd140000 UNKNOWN bd140000 */
 if(!cache||!cache(cache_owner,UINT32_C(0x80002ac8),20u,(uint32_t)lo(m,8u)+0u))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,0);target=sx(UINT32_C(0x80002acc));goto dispatch;
L_80002acc:
 STEP(UINT32_C(0x80002acc)); /* 0000000f sync 0 */
 ++m->sync_p;target=sx(UINT32_C(0x80002ad0));goto dispatch;
L_80002ad0:
 STEP(UINT32_C(0x80002ad0)); /* bd140001 UNKNOWN bd140001 */
 if(!cache||!cache(cache_owner,UINT32_C(0x80002ad0),20u,(uint32_t)lo(m,8u)+1u))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,0);target=sx(UINT32_C(0x80002ad4));goto dispatch;
L_80002ad4:
 STEP(UINT32_C(0x80002ad4)); /* 0000000f sync 0 */
 ++m->sync_p;target=sx(UINT32_C(0x80002ad8));goto dispatch;
L_80002ad8:
 STEP(UINT32_C(0x80002ad8)); /* 25080040 addiu t0,t0,64 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x80002adc));goto dispatch;
L_80002adc:
 STEP(UINT32_C(0x80002adc)); /* 29091000 slti t1,t0,4096 */
 set(m,9u,((int64_t)lo(m,8u)<INT64_C(4096)));target=sx(UINT32_C(0x80002ae0));goto dispatch;
L_80002ae0:
 STEP(UINT32_C(0x80002ae0)); /* 1520fff8 bne t1,zero,80002ac4 */
 {int taken=(lo(m,9u)!=lo(m,0u));STEP(UINT32_C(0x80002ae4));/* nop */target=sx(taken?UINT32_C(0x80002ac4):UINT32_C(0x80002ae8));goto dispatch;}
L_80002ae4:
 STEP(UINT32_C(0x80002ae4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80002ae8));goto dispatch;
L_80002ae8:
 STEP(UINT32_C(0x80002ae8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80002aec));/* nop */goto dispatch;
L_80002aec:
 STEP(UINT32_C(0x80002aec)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80002af0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

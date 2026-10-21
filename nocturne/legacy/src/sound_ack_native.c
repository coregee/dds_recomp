#include "sound_ack_native.h"
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
uint32_t nocturneSoundAckResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002dddc0):goto L_002dddc0;
 case UINT32_C(0x002dddc4):goto L_002dddc4;
 case UINT32_C(0x002dddc8):goto L_002dddc8;
 case UINT32_C(0x002dddcc):goto L_002dddcc;
 case UINT32_C(0x002dddd0):goto L_002dddd0;
 case UINT32_C(0x002dddd4):goto L_002dddd4;
 case UINT32_C(0x002dddd8):goto L_002dddd8;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002dddc0:
 STEP(UINT32_C(0x002dddc0)); /* 8c820010 lw v0,0x10(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dddc4));goto dispatch;
L_002dddc4:
 STEP(UINT32_C(0x002dddc4)); /* 8ca6001c lw a2,0x1c(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x0000001c),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002dddc8));goto dispatch;
L_002dddc8:
 STEP(UINT32_C(0x002dddc8)); /* 8c830014 lw v1,0x14(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dddcc));goto dispatch;
L_002dddcc:
 STEP(UINT32_C(0x002dddcc)); /* 00021080 sll v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<2u));target=sx(UINT32_C(0x002dddd0));goto dispatch;
L_002dddd0:
 STEP(UINT32_C(0x002dddd0)); /* 00461021 addu v0,v0,a2 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002dddd4));goto dispatch;
L_002dddd4:
 if(m->instructions-started>=limit||limit-(m->instructions-started)<2u)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0); /* JR and delay slot need a single source budget. */
 STEP(UINT32_C(0x002dddd4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dddd8));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_002dddd8:
 STEP(UINT32_C(0x002dddd8)); /* ac430000 sw v1,0x0(v0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ddddc));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

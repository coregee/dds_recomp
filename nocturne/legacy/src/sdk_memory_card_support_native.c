#include "sdk_memory_card_support_native.h"
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
uint32_t nocturneSdkMemoryCardSupportResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002dbef0):goto L_002dbef0;
 case UINT32_C(0x002dbef4):goto L_002dbef4;
 case UINT32_C(0x002dbef8):goto L_002dbef8;
 case UINT32_C(0x002dbefc):goto L_002dbefc;
 case UINT32_C(0x002def38):goto L_002def38;
 case UINT32_C(0x002def3c):goto L_002def3c;
 case UINT32_C(0x002def40):goto L_002def40;
 case UINT32_C(0x002def44):goto L_002def44;
 case UINT32_C(0x002def48):goto L_002def48;
 case UINT32_C(0x002def4c):goto L_002def4c;
 case UINT32_C(0x002def50):goto L_002def50;
 case UINT32_C(0x002def54):goto L_002def54;
 case UINT32_C(0x002def58):goto L_002def58;
 case UINT32_C(0x002def5c):goto L_002def5c;
 case UINT32_C(0x002def60):goto L_002def60;
 case UINT32_C(0x002def64):goto L_002def64;
 case UINT32_C(0x002def68):goto L_002def68;
 case UINT32_C(0x002def6c):goto L_002def6c;
 case UINT32_C(0x002def70):goto L_002def70;
 case UINT32_C(0x80004dc8):goto L_80004dc8;
 case UINT32_C(0x80004dcc):goto L_80004dcc;
 case UINT32_C(0x80004dd0):goto L_80004dd0;
 case UINT32_C(0x80004dd4):goto L_80004dd4;
 case UINT32_C(0x80004dd8):goto L_80004dd8;
 case UINT32_C(0x80004ddc):goto L_80004ddc;
 case UINT32_C(0x80004de0):goto L_80004de0;
 case UINT32_C(0x80004de4):goto L_80004de4;
 case UINT32_C(0x80004de8):goto L_80004de8;
 case UINT32_C(0x80004dec):goto L_80004dec;
 case UINT32_C(0x80004df0):goto L_80004df0;
 case UINT32_C(0x80004df4):goto L_80004df4;
 case UINT32_C(0x80004df8):goto L_80004df8;
 case UINT32_C(0x80004dfc):goto L_80004dfc;
 case UINT32_C(0x002dbc20):goto L_002dbc20;
 case UINT32_C(0x002dbc24):goto L_002dbc24;
 case UINT32_C(0x002dbc28):goto L_002dbc28;
 case UINT32_C(0x002dbc2c):goto L_002dbc2c;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002dbef0:
 STEP(UINT32_C(0x002dbef0)); /* 24030045 addiu v1,zero,69 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000045)));target=sx(UINT32_C(0x002dbef4));goto dispatch;
L_002dbef4:
 m->pc=UINT32_C(0x002dbef4); /* Unexecuted SYS; router counts actual exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbef8:
 STEP(UINT32_C(0x002dbef8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbefc));/* nop */goto dispatch;
L_002dbefc:
 STEP(UINT32_C(0x002dbefc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbf00));goto dispatch;
L_002def38:
 STEP(UINT32_C(0x002def38)); /* 8c850000 lw a1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002def3c));goto dispatch;
L_002def3c:
 STEP(UINT32_C(0x002def3c)); /* 10a00009 beq a1,zero,002def64 */
 {int taken=(lo(m,5u)==lo(m,0u));STEP(UINT32_C(0x002def40));/* nop */target=sx(taken?UINT32_C(0x002def64):UINT32_C(0x002def44));goto dispatch;}
L_002def40:
 STEP(UINT32_C(0x002def40)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002def44));goto dispatch;
L_002def44:
 STEP(UINT32_C(0x002def44)); /* 8c830004 lw v1,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002def48));goto dispatch;
L_002def48:
 STEP(UINT32_C(0x002def48)); /* 8ca20018 lw v0,0x18(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002def4c));goto dispatch;
L_002def4c:
 STEP(UINT32_C(0x002def4c)); /* 14620005 bne v1,v0,002def64 */
 {int taken=(lo(m,3u)!=lo(m,2u));STEP(UINT32_C(0x002def50));/* nop */target=sx(taken?UINT32_C(0x002def64):UINT32_C(0x002def54));goto dispatch;}
L_002def50:
 STEP(UINT32_C(0x002def50)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002def54));goto dispatch;
L_002def54:
 STEP(UINT32_C(0x002def54)); /* 8ca20010 lw v0,0x10(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002def58));goto dispatch;
L_002def58:
 STEP(UINT32_C(0x002def58)); /* 30420001 andi v0,v0,0x1 */
 set(m,2u,lo(m,2u) & UINT64_C(0x1));target=sx(UINT32_C(0x002def5c));goto dispatch;
L_002def5c:
 STEP(UINT32_C(0x002def5c)); /* 14400003 bne v0,zero,002def6c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002def60));/* nop */target=sx(taken?UINT32_C(0x002def6c):UINT32_C(0x002def64));goto dispatch;}
L_002def60:
 STEP(UINT32_C(0x002def60)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002def64));goto dispatch;
L_002def64:
 STEP(UINT32_C(0x002def64)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002def68));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_002def68:
 STEP(UINT32_C(0x002def68)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002def6c));goto dispatch;
L_002def6c:
 STEP(UINT32_C(0x002def6c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002def70));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));goto dispatch;
L_002def70:
 STEP(UINT32_C(0x002def70)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002def74));goto dispatch;
L_80004dc8:
 STEP(UINT32_C(0x80004dc8)); /* 2c820100 sltiu v0,a0,256 */
 set(m,2u,(lo(m,4u)<UINT64_C(0x100)));target=sx(UINT32_C(0x80004dcc));goto dispatch;
L_80004dcc:
 STEP(UINT32_C(0x80004dcc)); /* 14400003 bne v0,zero,80004ddc */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80004dd0));set(m,3u,sx((uint32_t)lo(m,4u)<<5u));target=sx(taken?UINT32_C(0x80004ddc):UINT32_C(0x80004dd4));goto dispatch;}
L_80004dd0:
 STEP(UINT32_C(0x80004dd0)); /* 00041940 sll v1,a0,5 */
 set(m,3u,sx((uint32_t)lo(m,4u)<<5u));target=sx(UINT32_C(0x80004dd4));goto dispatch;
L_80004dd4:
 STEP(UINT32_C(0x80004dd4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004dd8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));goto dispatch;
L_80004dd8:
 STEP(UINT32_C(0x80004dd8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004ddc));goto dispatch;
L_80004ddc:
 STEP(UINT32_C(0x80004ddc)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80004de0));goto dispatch;
L_80004de0:
 STEP(UINT32_C(0x80004de0)); /* 2442c000 addiu v0,v0,-16384 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffc000)));target=sx(UINT32_C(0x80004de4));goto dispatch;
L_80004de4:
 STEP(UINT32_C(0x80004de4)); /* 00622821 addu a1,v1,v0 */
 set(m,5u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80004de8));goto dispatch;
L_80004de8:
 STEP(UINT32_C(0x80004de8)); /* 8ca30004 lw v1,0x4(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004dec));goto dispatch;
L_80004dec:
 STEP(UINT32_C(0x80004dec)); /* 1860fff9 blez v1,zero,80004dd4 */
 {int taken=((int64_t)lo(m,3u)<=0);STEP(UINT32_C(0x80004df0));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80004dd4):UINT32_C(0x80004df4));goto dispatch;}
L_80004df0:
 STEP(UINT32_C(0x80004df0)); /* 2463ffff addiu v1,v1,-1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004df4));goto dispatch;
L_80004df4:
 STEP(UINT32_C(0x80004df4)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80004df8));goto dispatch;
L_80004df8:
 STEP(UINT32_C(0x80004df8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004dfc));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);goto dispatch;
L_80004dfc:
 STEP(UINT32_C(0x80004dfc)); /* aca30004 sw v1,0x4(a1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80004e00));goto dispatch;
L_002dbc20:
 STEP(UINT32_C(0x002dbc20)); /* 240300fc addiu v1,zero,252 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000fc)));target=sx(UINT32_C(0x002dbc24));goto dispatch;
L_002dbc24:
 m->pc=UINT32_C(0x002dbc24); /* Unexecuted SYS; router counts actual exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbc28:
 STEP(UINT32_C(0x002dbc28)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbc2c));/* nop */goto dispatch;
L_002dbc2c:
 STEP(UINT32_C(0x002dbc2c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbc30));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

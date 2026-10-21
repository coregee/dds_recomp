#include "sound_thread_bootstrap_native.h"
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
uint32_t nocturneSoundThreadBootstrapResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,uint32_t observation_pc,NocturneWakeupStop *s)
{
 uint64_t target,value64=0,started;uint32_t value32=0,address=0;uint16_t value16=0;
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
 if(m->pc==observation_pc)return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));
 switch(m->pc){
 case UINT32_C(0x002c0fc0):goto L_002c0fc0;
 case UINT32_C(0x002c0fc4):goto L_002c0fc4;
 case UINT32_C(0x002c0fc8):goto L_002c0fc8;
 case UINT32_C(0x002c0fcc):goto L_002c0fcc;
 case UINT32_C(0x002c0fd0):goto L_002c0fd0;
 case UINT32_C(0x002c0fd4):goto L_002c0fd4;
 case UINT32_C(0x002c0fd8):goto L_002c0fd8;
 case UINT32_C(0x002c0fdc):goto L_002c0fdc;
 case UINT32_C(0x002c0fe0):goto L_002c0fe0;
 case UINT32_C(0x002c0fe4):goto L_002c0fe4;
 case UINT32_C(0x002c0fe8):goto L_002c0fe8;
 case UINT32_C(0x002c0fec):goto L_002c0fec;
 case UINT32_C(0x002c0ff0):goto L_002c0ff0;
 case UINT32_C(0x002c0ff4):goto L_002c0ff4;
 case UINT32_C(0x002c0ff8):goto L_002c0ff8;
 case UINT32_C(0x002c0ffc):goto L_002c0ffc;
 case UINT32_C(0x002c1000):goto L_002c1000;
 case UINT32_C(0x002c1004):goto L_002c1004;
 case UINT32_C(0x002c1008):goto L_002c1008;
 case UINT32_C(0x002c100c):goto L_002c100c;
 case UINT32_C(0x002c1010):goto L_002c1010;
 case UINT32_C(0x002c1014):goto L_002c1014;
 case UINT32_C(0x002c1018):goto L_002c1018;
 case UINT32_C(0x002c101c):goto L_002c101c;
 case UINT32_C(0x002c1020):goto L_002c1020;
 case UINT32_C(0x002c1024):goto L_002c1024;
 case UINT32_C(0x002c1028):goto L_002c1028;
 case UINT32_C(0x002c102c):goto L_002c102c;
 case UINT32_C(0x002c1030):goto L_002c1030;
 case UINT32_C(0x002c1034):goto L_002c1034;
 case UINT32_C(0x002c1038):goto L_002c1038;
 case UINT32_C(0x002c103c):goto L_002c103c;
 case UINT32_C(0x002c1040):goto L_002c1040;
 case UINT32_C(0x002c1044):goto L_002c1044;
 case UINT32_C(0x002c1048):goto L_002c1048;
 case UINT32_C(0x002c104c):goto L_002c104c;
 case UINT32_C(0x002c1050):goto L_002c1050;
 case UINT32_C(0x002c1054):goto L_002c1054;
 case UINT32_C(0x002c1058):goto L_002c1058;
 case UINT32_C(0x002c105c):goto L_002c105c;
 case UINT32_C(0x002c1060):goto L_002c1060;
 case UINT32_C(0x002c1064):goto L_002c1064;
 case UINT32_C(0x002c1068):goto L_002c1068;
 case UINT32_C(0x002c106c):goto L_002c106c;
 case UINT32_C(0x002c1070):goto L_002c1070;
 case UINT32_C(0x002c1074):goto L_002c1074;
 case UINT32_C(0x002c1078):goto L_002c1078;
 case UINT32_C(0x002c107c):goto L_002c107c;
 case UINT32_C(0x002c1080):goto L_002c1080;
 case UINT32_C(0x002c1084):goto L_002c1084;
 case UINT32_C(0x002c1088):goto L_002c1088;
 case UINT32_C(0x002c108c):goto L_002c108c;
 case UINT32_C(0x002c1090):goto L_002c1090;
 case UINT32_C(0x002c1094):goto L_002c1094;
 case UINT32_C(0x002c1098):goto L_002c1098;
 case UINT32_C(0x002c109c):goto L_002c109c;
 case UINT32_C(0x002c10a0):goto L_002c10a0;
 case UINT32_C(0x002c10a4):goto L_002c10a4;
 case UINT32_C(0x002c10a8):goto L_002c10a8;
 case UINT32_C(0x002c10ac):goto L_002c10ac;
 case UINT32_C(0x002c10b0):goto L_002c10b0;
 case UINT32_C(0x002c10b4):goto L_002c10b4;
 case UINT32_C(0x002c10b8):goto L_002c10b8;
 case UINT32_C(0x002c10bc):goto L_002c10bc;
 case UINT32_C(0x002c10c0):goto L_002c10c0;
 case UINT32_C(0x002c10c4):goto L_002c10c4;
 case UINT32_C(0x002c10c8):goto L_002c10c8;
 case UINT32_C(0x002c10cc):goto L_002c10cc;
 case UINT32_C(0x002c10d0):goto L_002c10d0;
 case UINT32_C(0x002c10d4):goto L_002c10d4;
 case UINT32_C(0x002c10d8):goto L_002c10d8;
 case UINT32_C(0x002c10dc):goto L_002c10dc;
 case UINT32_C(0x002c10e0):goto L_002c10e0;
 case UINT32_C(0x002dbca0):goto L_002dbca0;
 case UINT32_C(0x002dbca4):goto L_002dbca4;
 case UINT32_C(0x002dbca8):goto L_002dbca8;
 case UINT32_C(0x002dbcac):goto L_002dbcac;
 case UINT32_C(0x002dbcc0):goto L_002dbcc0;
 case UINT32_C(0x002dbcc4):goto L_002dbcc4;
 case UINT32_C(0x002dbcc8):goto L_002dbcc8;
 case UINT32_C(0x002dbccc):goto L_002dbccc;
 case UINT32_C(0x002dbdc0):goto L_002dbdc0;
 case UINT32_C(0x002dbdc4):goto L_002dbdc4;
 case UINT32_C(0x002dbdc8):goto L_002dbdc8;
 case UINT32_C(0x002dbdcc):goto L_002dbdcc;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002c0fc0:
 STEP(UINT32_C(0x002c0fc0)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002c0fc4));goto dispatch;
L_002c0fc4:
 STEP(UINT32_C(0x002c0fc4)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c0fc8));goto dispatch;
L_002c0fc8:
 STEP(UINT32_C(0x002c0fc8)); /* 0c0b6f70 jal 002dbdc0 */
 set(m,31u,UINT64_C(0x002c0fd0));STEP(UINT32_C(0x002c0fcc));/* nop */target=sx(UINT32_C(0x002dbdc0));goto dispatch;
L_002c0fcc:
 STEP(UINT32_C(0x002c0fcc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0fd0));goto dispatch;
L_002c0fd0:
 STEP(UINT32_C(0x002c0fd0)); /* 8383dfc0 lb v1,-0x2040(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc0),&value32,1u);set(m,3u,sx((uint32_t)(int32_t)(int8_t)value32));target=sx(UINT32_C(0x002c0fd4));goto dispatch;
L_002c0fd4:
 STEP(UINT32_C(0x002c0fd4)); /* 1460fffc bne v1,zero,002c0fc8 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002c0fd8));/* nop */target=sx(taken?UINT32_C(0x002c0fc8):UINT32_C(0x002c0fdc));goto dispatch;}
L_002c0fd8:
 STEP(UINT32_C(0x002c0fd8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0fdc));goto dispatch;
L_002c0fdc:
 STEP(UINT32_C(0x002c0fdc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0fe0));goto dispatch;
L_002c0fe0:
 STEP(UINT32_C(0x002c0fe0)); /* 0c0b03ca jal 002c0f28 */
 set(m,31u,UINT64_C(0x002c0fe8));STEP(UINT32_C(0x002c0fe4));/* nop */target=sx(UINT32_C(0x002c0f28));goto dispatch;
L_002c0fe4:
 STEP(UINT32_C(0x002c0fe4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0fe8));goto dispatch;
L_002c0fe8:
 STEP(UINT32_C(0x002c0fe8)); /* 1040fffd beq v0,zero,002c0fe0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002c0fec));/* nop */target=sx(taken?UINT32_C(0x002c0fe0):UINT32_C(0x002c0ff0));goto dispatch;}
L_002c0fec:
 STEP(UINT32_C(0x002c0fec)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0ff0));goto dispatch;
L_002c0ff0:
 STEP(UINT32_C(0x002c0ff0)); /* 1000fff5 beq zero,zero,002c0fc8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c0ff4));/* nop */target=sx(taken?UINT32_C(0x002c0fc8):UINT32_C(0x002c0ff8));goto dispatch;}
L_002c0ff4:
 STEP(UINT32_C(0x002c0ff4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0ff8));goto dispatch;
L_002c0ff8:
 STEP(UINT32_C(0x002c0ff8)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002c0ffc));goto dispatch;
L_002c0ffc:
 STEP(UINT32_C(0x002c0ffc)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c1000));goto dispatch;
L_002c1000:
 STEP(UINT32_C(0x002c1000)); /* 3c1105f5 lui s1,zero,0x5f5 */
 set(m,17u,sx(UINT32_C(0x05f50000)));target=sx(UINT32_C(0x002c1004));goto dispatch;
L_002c1004:
 STEP(UINT32_C(0x002c1004)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c1008));goto dispatch;
L_002c1008:
 STEP(UINT32_C(0x002c1008)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c100c));goto dispatch;
L_002c100c:
 STEP(UINT32_C(0x002c100c)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002c1010));goto dispatch;
L_002c1010:
 STEP(UINT32_C(0x002c1010)); /* 3c120055 lui s2,zero,0x55 */
 set(m,18u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1014));goto dispatch;
L_002c1014:
 STEP(UINT32_C(0x002c1014)); /* 3631e100 ori s1,s1,0xe100 */
 set(m,17u,lo(m,17u) | UINT64_C(0xe100));target=sx(UINT32_C(0x002c1018));goto dispatch;
L_002c1018:
 STEP(UINT32_C(0x002c1018)); /* 10000006 beq zero,zero,002c1034 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c101c));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(taken?UINT32_C(0x002c1034):UINT32_C(0x002c1020));goto dispatch;}
L_002c101c:
 STEP(UINT32_C(0x002c101c)); /* ffbf0018 sd ra,0x18(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002c1020));goto dispatch;
L_002c1020:
 STEP(UINT32_C(0x002c1020)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1024));goto dispatch;
L_002c1024:
 STEP(UINT32_C(0x002c1024)); /* 16110003 bne s0,s1,002c1034 */
 {int taken=(lo(m,16u)!=lo(m,17u));STEP(UINT32_C(0x002c1028));/* nop */target=sx(taken?UINT32_C(0x002c1034):UINT32_C(0x002c102c));goto dispatch;}
L_002c1028:
 STEP(UINT32_C(0x002c1028)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c102c));goto dispatch;
L_002c102c:
 STEP(UINT32_C(0x002c102c)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c1034));STEP(UINT32_C(0x002c1030));set(m,16u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c1030:
 STEP(UINT32_C(0x002c1030)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1034));goto dispatch;
L_002c1034:
 STEP(UINT32_C(0x002c1034)); /* 0c0b777c jal 002dddf0 */
 set(m,31u,UINT64_C(0x002c103c));STEP(UINT32_C(0x002c1038));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x002dddf0));goto dispatch;
L_002c1038:
 STEP(UINT32_C(0x002c1038)); /* 2404001f addiu a0,zero,31 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x002c103c));goto dispatch;
L_002c103c:
 STEP(UINT32_C(0x002c103c)); /* 1040fff8 beq v0,zero,002c1020 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002c1040));set(m,4u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffff9968)));target=sx(taken?UINT32_C(0x002c1020):UINT32_C(0x002c1044));goto dispatch;}
L_002c1040:
 STEP(UINT32_C(0x002c1040)); /* 26449968 addiu a0,s2,-26264 */
 set(m,4u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffff9968)));target=sx(UINT32_C(0x002c1044));goto dispatch;
L_002c1044:
 STEP(UINT32_C(0x002c1044)); /* 3c020059 lui v0,zero,0x59 */
 set(m,2u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c1048));goto dispatch;
L_002c1048:
 STEP(UINT32_C(0x002c1048)); /* 3c05002c lui a1,zero,0x2c */
 set(m,5u,sx(UINT32_C(0x002c0000)));target=sx(UINT32_C(0x002c104c));goto dispatch;
L_002c104c:
 STEP(UINT32_C(0x002c104c)); /* 3c030059 lui v1,zero,0x59 */
 set(m,3u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c1050));goto dispatch;
L_002c1050:
 STEP(UINT32_C(0x002c1050)); /* 244207c0 addiu v0,v0,1984 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x000007c0)));target=sx(UINT32_C(0x002c1054));goto dispatch;
L_002c1054:
 STEP(UINT32_C(0x002c1054)); /* 24631840 addiu v1,v1,6208 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00001840)));target=sx(UINT32_C(0x002c1058));goto dispatch;
L_002c1058:
 STEP(UINT32_C(0x002c1058)); /* 3c080055 lui t0,zero,0x55 */
 set(m,8u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c105c));goto dispatch;
L_002c105c:
 STEP(UINT32_C(0x002c105c)); /* 25084170 addiu t0,t0,16752 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00004170)));target=sx(UINT32_C(0x002c1060));goto dispatch;
L_002c1060:
 STEP(UINT32_C(0x002c1060)); /* 24061000 addiu a2,zero,4096 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00001000)));target=sx(UINT32_C(0x002c1064));goto dispatch;
L_002c1064:
 STEP(UINT32_C(0x002c1064)); /* 24070042 addiu a3,zero,66 */
 set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000042)));target=sx(UINT32_C(0x002c1068));goto dispatch;
L_002c1068:
 STEP(UINT32_C(0x002c1068)); /* 24a50fc0 addiu a1,a1,4032 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000fc0)));target=sx(UINT32_C(0x002c106c));goto dispatch;
L_002c106c:
 STEP(UINT32_C(0x002c106c)); /* ac430008 sw v1,0x8(v0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002c1070));goto dispatch;
L_002c1070:
 STEP(UINT32_C(0x002c1070)); /* ac480010 sw t0,0x10(v0) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002c1074));goto dispatch;
L_002c1074:
 STEP(UINT32_C(0x002c1074)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c1078));goto dispatch;
L_002c1078:
 STEP(UINT32_C(0x002c1078)); /* ac46000c sw a2,0xc(v0) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002c107c));goto dispatch;
L_002c107c:
 STEP(UINT32_C(0x002c107c)); /* ac470014 sw a3,0x14(v0) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002c1080));goto dispatch;
L_002c1080:
 STEP(UINT32_C(0x002c1080)); /* ac450004 sw a1,0x4(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002c1084));goto dispatch;
L_002c1084:
 STEP(UINT32_C(0x002c1084)); /* a780dfc2 sh zero,-0x203e(gp) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc2),&value16,2u);target=sx(UINT32_C(0x002c1088));goto dispatch;
L_002c1088:
 STEP(UINT32_C(0x002c1088)); /* a780dfc4 sh zero,-0x203c(gp) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc4),&value16,2u);target=sx(UINT32_C(0x002c108c));goto dispatch;
L_002c108c:
 STEP(UINT32_C(0x002c108c)); /* 0c0b6f28 jal 002dbca0 */
 set(m,31u,UINT64_C(0x002c1094));STEP(UINT32_C(0x002c1090));/* nop */target=sx(UINT32_C(0x002dbca0));goto dispatch;
L_002c1090:
 STEP(UINT32_C(0x002c1090)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1094));goto dispatch;
L_002c1094:
 STEP(UINT32_C(0x002c1094)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c1098));goto dispatch;
L_002c1098:
 STEP(UINT32_C(0x002c1098)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c109c));goto dispatch;
L_002c109c:
 STEP(UINT32_C(0x002c109c)); /* 0c0b6f30 jal 002dbcc0 */
 set(m,31u,UINT64_C(0x002c10a4));STEP(UINT32_C(0x002c10a0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc8),&value32,4u);target=sx(UINT32_C(0x002dbcc0));goto dispatch;
L_002c10a0:
 STEP(UINT32_C(0x002c10a0)); /* af82dfc8 sw v0,-0x2038(gp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc8),&value32,4u);target=sx(UINT32_C(0x002c10a4));goto dispatch;
L_002c10a4:
 STEP(UINT32_C(0x002c10a4)); /* 3c04002c lui a0,zero,0x2c */
 set(m,4u,sx(UINT32_C(0x002c0000)));target=sx(UINT32_C(0x002c10a8));goto dispatch;
L_002c10a8:
 STEP(UINT32_C(0x002c10a8)); /* 3c050059 lui a1,zero,0x59 */
 set(m,5u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c10ac));goto dispatch;
L_002c10ac:
 STEP(UINT32_C(0x002c10ac)); /* 24842580 addiu a0,a0,9600 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00002580)));target=sx(UINT32_C(0x002c10b0));goto dispatch;
L_002c10b0:
 STEP(UINT32_C(0x002c10b0)); /* 24a52880 addiu a1,a1,10368 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00002880)));target=sx(UINT32_C(0x002c10b4));goto dispatch;
L_002c10b4:
 STEP(UINT32_C(0x002c10b4)); /* 24061000 addiu a2,zero,4096 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00001000)));target=sx(UINT32_C(0x002c10b8));goto dispatch;
L_002c10b8:
 STEP(UINT32_C(0x002c10b8)); /* 0c0aa02a jal 002a80a8 */
 set(m,31u,UINT64_C(0x002c10c0));STEP(UINT32_C(0x002c10bc));set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000043)));target=sx(UINT32_C(0x002a80a8));goto dispatch;
L_002c10bc:
 STEP(UINT32_C(0x002c10bc)); /* 24070043 addiu a3,zero,67 */
 set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000043)));target=sx(UINT32_C(0x002c10c0));goto dispatch;
L_002c10c0:
 STEP(UINT32_C(0x002c10c0)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c10c4));goto dispatch;
L_002c10c4:
 STEP(UINT32_C(0x002c10c4)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c10c8));goto dispatch;
L_002c10c8:
 STEP(UINT32_C(0x002c10c8)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c10cc));goto dispatch;
L_002c10cc:
 STEP(UINT32_C(0x002c10cc)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c10d0));goto dispatch;
L_002c10d0:
 STEP(UINT32_C(0x002c10d0)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002c10d4));goto dispatch;
L_002c10d4:
 STEP(UINT32_C(0x002c10d4)); /* dfbf0018 ld ra,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c10d8));goto dispatch;
L_002c10d8:
 STEP(UINT32_C(0x002c10d8)); /* af82d864 sw v0,-0x279c(gp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffd864),&value32,4u);target=sx(UINT32_C(0x002c10dc));goto dispatch;
L_002c10dc:
 STEP(UINT32_C(0x002c10dc)); /* 080b6f30 j 002dbcc0 */
 STEP(UINT32_C(0x002c10e0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002dbcc0));goto dispatch;
L_002c10e0:
 STEP(UINT32_C(0x002c10e0)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002c10e4));goto dispatch;
L_002dbca0:
 STEP(UINT32_C(0x002dbca0)); /* 24030020 addiu v1,zero,32 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002dbca4));goto dispatch;
L_002dbca4:
 m->pc=UINT32_C(0x002dbca4); /* Unexecuted source SYSCALL; router counts it once. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbca8:
 STEP(UINT32_C(0x002dbca8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbcac));/* nop */goto dispatch;
L_002dbcac:
 STEP(UINT32_C(0x002dbcac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbcb0));goto dispatch;
L_002dbcc0:
 STEP(UINT32_C(0x002dbcc0)); /* 24030022 addiu v1,zero,34 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000022)));target=sx(UINT32_C(0x002dbcc4));goto dispatch;
L_002dbcc4:
 m->pc=UINT32_C(0x002dbcc4); /* Unexecuted source SYSCALL; router counts it once. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbcc8:
 STEP(UINT32_C(0x002dbcc8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbccc));/* nop */goto dispatch;
L_002dbccc:
 STEP(UINT32_C(0x002dbccc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbcd0));goto dispatch;
L_002dbdc0:
 STEP(UINT32_C(0x002dbdc0)); /* 24030032 addiu v1,zero,50 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000032)));target=sx(UINT32_C(0x002dbdc4));goto dispatch;
L_002dbdc4:
 m->pc=UINT32_C(0x002dbdc4); /* Unexecuted source SYSCALL; router counts it once. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbdc8:
 STEP(UINT32_C(0x002dbdc8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbdcc));/* nop */goto dispatch;
L_002dbdcc:
 STEP(UINT32_C(0x002dbdcc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbdd0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

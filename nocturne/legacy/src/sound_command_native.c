#include "sound_command_native.h"
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
uint32_t nocturneSoundCommandResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s,NocturneSoundCommandCache cache,void *cache_owner)
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
 switch(m->pc){
 case UINT32_C(0x002c0f28):goto L_002c0f28;
 case UINT32_C(0x002c0f2c):goto L_002c0f2c;
 case UINT32_C(0x002c0f30):goto L_002c0f30;
 case UINT32_C(0x002c0f34):goto L_002c0f34;
 case UINT32_C(0x002c0f38):goto L_002c0f38;
 case UINT32_C(0x002c0f3c):goto L_002c0f3c;
 case UINT32_C(0x002c0f40):goto L_002c0f40;
 case UINT32_C(0x002c0f44):goto L_002c0f44;
 case UINT32_C(0x002c0f48):goto L_002c0f48;
 case UINT32_C(0x002c0f4c):goto L_002c0f4c;
 case UINT32_C(0x002c0f50):goto L_002c0f50;
 case UINT32_C(0x002c0f54):goto L_002c0f54;
 case UINT32_C(0x002c0f58):goto L_002c0f58;
 case UINT32_C(0x002c0f5c):goto L_002c0f5c;
 case UINT32_C(0x002c0f60):goto L_002c0f60;
 case UINT32_C(0x002c0f64):goto L_002c0f64;
 case UINT32_C(0x002c0f68):goto L_002c0f68;
 case UINT32_C(0x002c0f6c):goto L_002c0f6c;
 case UINT32_C(0x002c0f70):goto L_002c0f70;
 case UINT32_C(0x002c0f74):goto L_002c0f74;
 case UINT32_C(0x002c0f78):goto L_002c0f78;
 case UINT32_C(0x002c0f7c):goto L_002c0f7c;
 case UINT32_C(0x002c0f80):goto L_002c0f80;
 case UINT32_C(0x002c0f84):goto L_002c0f84;
 case UINT32_C(0x002c0f88):goto L_002c0f88;
 case UINT32_C(0x002c0f8c):goto L_002c0f8c;
 case UINT32_C(0x002c0f90):goto L_002c0f90;
 case UINT32_C(0x002c0f94):goto L_002c0f94;
 case UINT32_C(0x002c0f98):goto L_002c0f98;
 case UINT32_C(0x002c0f9c):goto L_002c0f9c;
 case UINT32_C(0x002c0fa0):goto L_002c0fa0;
 case UINT32_C(0x002c0fa4):goto L_002c0fa4;
 case UINT32_C(0x002c0fa8):goto L_002c0fa8;
 case UINT32_C(0x002c0fac):goto L_002c0fac;
 case UINT32_C(0x002c0fb0):goto L_002c0fb0;
 case UINT32_C(0x002c0fb4):goto L_002c0fb4;
 case UINT32_C(0x002c0fb8):goto L_002c0fb8;
 case UINT32_C(0x002c0fbc):goto L_002c0fbc;
 case UINT32_C(0x002de178):goto L_002de178;
 case UINT32_C(0x002de17c):goto L_002de17c;
 case UINT32_C(0x002de180):goto L_002de180;
 case UINT32_C(0x002de184):goto L_002de184;
 case UINT32_C(0x002de188):goto L_002de188;
 case UINT32_C(0x002de18c):goto L_002de18c;
 case UINT32_C(0x002de190):goto L_002de190;
 case UINT32_C(0x002de194):goto L_002de194;
 case UINT32_C(0x002de198):goto L_002de198;
 case UINT32_C(0x002de19c):goto L_002de19c;
 case UINT32_C(0x002de1a0):goto L_002de1a0;
 case UINT32_C(0x002de1a4):goto L_002de1a4;
 case UINT32_C(0x002de1a8):goto L_002de1a8;
 case UINT32_C(0x002de1ac):goto L_002de1ac;
 case UINT32_C(0x002de1b0):goto L_002de1b0;
 case UINT32_C(0x002de1b4):goto L_002de1b4;
 case UINT32_C(0x002de1b8):goto L_002de1b8;
 case UINT32_C(0x002de1bc):goto L_002de1bc;
 case UINT32_C(0x002de1c0):goto L_002de1c0;
 case UINT32_C(0x002de1c4):goto L_002de1c4;
 case UINT32_C(0x002de1c8):goto L_002de1c8;
 case UINT32_C(0x002de1cc):goto L_002de1cc;
 case UINT32_C(0x002de1d0):goto L_002de1d0;
 case UINT32_C(0x002de1d4):goto L_002de1d4;
 case UINT32_C(0x002de1d8):goto L_002de1d8;
 case UINT32_C(0x002de1dc):goto L_002de1dc;
 case UINT32_C(0x002de1e0):goto L_002de1e0;
 case UINT32_C(0x002de1e4):goto L_002de1e4;
 case UINT32_C(0x002de1e8):goto L_002de1e8;
 case UINT32_C(0x002de1ec):goto L_002de1ec;
 case UINT32_C(0x002de1f0):goto L_002de1f0;
 case UINT32_C(0x002de1f4):goto L_002de1f4;
 case UINT32_C(0x002de1f8):goto L_002de1f8;
 case UINT32_C(0x002de1fc):goto L_002de1fc;
 case UINT32_C(0x002de200):goto L_002de200;
 case UINT32_C(0x002de204):goto L_002de204;
 case UINT32_C(0x002de208):goto L_002de208;
 case UINT32_C(0x002de20c):goto L_002de20c;
 case UINT32_C(0x002de210):goto L_002de210;
 case UINT32_C(0x002de214):goto L_002de214;
 case UINT32_C(0x002de218):goto L_002de218;
 case UINT32_C(0x002de21c):goto L_002de21c;
 case UINT32_C(0x002de220):goto L_002de220;
 case UINT32_C(0x002de224):goto L_002de224;
 case UINT32_C(0x002de228):goto L_002de228;
 case UINT32_C(0x002de22c):goto L_002de22c;
 case UINT32_C(0x002de230):goto L_002de230;
 case UINT32_C(0x002de234):goto L_002de234;
 case UINT32_C(0x002de238):goto L_002de238;
 case UINT32_C(0x002de23c):goto L_002de23c;
 case UINT32_C(0x002de240):goto L_002de240;
 case UINT32_C(0x002de244):goto L_002de244;
 case UINT32_C(0x002de248):goto L_002de248;
 case UINT32_C(0x002de24c):goto L_002de24c;
 case UINT32_C(0x002de250):goto L_002de250;
 case UINT32_C(0x002de254):goto L_002de254;
 case UINT32_C(0x002de258):goto L_002de258;
 case UINT32_C(0x002de25c):goto L_002de25c;
 case UINT32_C(0x002de260):goto L_002de260;
 case UINT32_C(0x002de264):goto L_002de264;
 case UINT32_C(0x002de268):goto L_002de268;
 case UINT32_C(0x002de26c):goto L_002de26c;
 case UINT32_C(0x002de270):goto L_002de270;
 case UINT32_C(0x002de274):goto L_002de274;
 case UINT32_C(0x002de278):goto L_002de278;
 case UINT32_C(0x002de27c):goto L_002de27c;
 case UINT32_C(0x002de280):goto L_002de280;
 case UINT32_C(0x002de284):goto L_002de284;
 case UINT32_C(0x002de288):goto L_002de288;
 case UINT32_C(0x002de28c):goto L_002de28c;
 case UINT32_C(0x002de290):goto L_002de290;
 case UINT32_C(0x002de294):goto L_002de294;
 case UINT32_C(0x002de298):goto L_002de298;
 case UINT32_C(0x002de29c):goto L_002de29c;
 case UINT32_C(0x002de2a0):goto L_002de2a0;
 case UINT32_C(0x002de2a4):goto L_002de2a4;
 case UINT32_C(0x002de2a8):goto L_002de2a8;
 case UINT32_C(0x002de2b0):goto L_002de2b0;
 case UINT32_C(0x002de2b4):goto L_002de2b4;
 case UINT32_C(0x002de2b8):goto L_002de2b8;
 case UINT32_C(0x002de2bc):goto L_002de2bc;
 case UINT32_C(0x002de2c0):goto L_002de2c0;
 case UINT32_C(0x002de2c4):goto L_002de2c4;
 case UINT32_C(0x002de2c8):goto L_002de2c8;
 case UINT32_C(0x002de2cc):goto L_002de2cc;
 case UINT32_C(0x002de2d0):goto L_002de2d0;
 case UINT32_C(0x002de2d4):goto L_002de2d4;
 case UINT32_C(0x002de2d8):goto L_002de2d8;
 case UINT32_C(0x002de2dc):goto L_002de2dc;
 case UINT32_C(0x002de2e0):goto L_002de2e0;
 case UINT32_C(0x002de2e4):goto L_002de2e4;
 case UINT32_C(0x002de2e8):goto L_002de2e8;
 case UINT32_C(0x002de458):goto L_002de458;
 case UINT32_C(0x002de45c):goto L_002de45c;
 case UINT32_C(0x002de460):goto L_002de460;
 case UINT32_C(0x002de464):goto L_002de464;
 case UINT32_C(0x002de468):goto L_002de468;
 case UINT32_C(0x002de46c):goto L_002de46c;
 case UINT32_C(0x002de470):goto L_002de470;
 case UINT32_C(0x002de474):goto L_002de474;
 case UINT32_C(0x002de478):goto L_002de478;
 case UINT32_C(0x002de47c):goto L_002de47c;
 case UINT32_C(0x002de480):goto L_002de480;
 case UINT32_C(0x002de484):goto L_002de484;
 case UINT32_C(0x002de488):goto L_002de488;
 case UINT32_C(0x002de48c):goto L_002de48c;
 case UINT32_C(0x002de490):goto L_002de490;
 case UINT32_C(0x002de494):goto L_002de494;
 case UINT32_C(0x002de498):goto L_002de498;
 case UINT32_C(0x002de49c):goto L_002de49c;
 case UINT32_C(0x002de4a0):goto L_002de4a0;
 case UINT32_C(0x002de4a4):goto L_002de4a4;
 case UINT32_C(0x002de4a8):goto L_002de4a8;
 case UINT32_C(0x002de4ac):goto L_002de4ac;
 case UINT32_C(0x002de4b0):goto L_002de4b0;
 case UINT32_C(0x002de4b4):goto L_002de4b4;
 case UINT32_C(0x002de4b8):goto L_002de4b8;
 case UINT32_C(0x002de4bc):goto L_002de4bc;
 case UINT32_C(0x002de4c0):goto L_002de4c0;
 case UINT32_C(0x002de4c4):goto L_002de4c4;
 case UINT32_C(0x002de4c8):goto L_002de4c8;
 case UINT32_C(0x002de4cc):goto L_002de4cc;
 case UINT32_C(0x002de4d0):goto L_002de4d0;
 case UINT32_C(0x002de4d4):goto L_002de4d4;
 case UINT32_C(0x002de4d8):goto L_002de4d8;
 case UINT32_C(0x002de4dc):goto L_002de4dc;
 case UINT32_C(0x002de4e0):goto L_002de4e0;
 case UINT32_C(0x002de4e4):goto L_002de4e4;
 case UINT32_C(0x002de4e8):goto L_002de4e8;
 case UINT32_C(0x002de4ec):goto L_002de4ec;
 case UINT32_C(0x002de4f0):goto L_002de4f0;
 case UINT32_C(0x002de4f4):goto L_002de4f4;
 case UINT32_C(0x002de4f8):goto L_002de4f8;
 case UINT32_C(0x002de4fc):goto L_002de4fc;
 case UINT32_C(0x002de500):goto L_002de500;
 case UINT32_C(0x002dc260):goto L_002dc260;
 case UINT32_C(0x002dc264):goto L_002dc264;
 case UINT32_C(0x002dc268):goto L_002dc268;
 case UINT32_C(0x002dc26c):goto L_002dc26c;
 case UINT32_C(0x002dc270):goto L_002dc270;
 case UINT32_C(0x002dc274):goto L_002dc274;
 case UINT32_C(0x002dc278):goto L_002dc278;
 case UINT32_C(0x002dc27c):goto L_002dc27c;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002c0f28:
 STEP(UINT32_C(0x002c0f28)); /* 9784dfc2 lhu a0,-0x203e(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc2),&value16,2u);set(m,4u,value16);target=sx(UINT32_C(0x002c0f2c));goto dispatch;
L_002c0f2c:
 STEP(UINT32_C(0x002c0f2c)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002c0f30));goto dispatch;
L_002c0f30:
 STEP(UINT32_C(0x002c0f30)); /* 9783dfc4 lhu v1,-0x203c(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc4),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002c0f34));goto dispatch;
L_002c0f34:
 STEP(UINT32_C(0x002c0f34)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c0f38));goto dispatch;
L_002c0f38:
 STEP(UINT32_C(0x002c0f38)); /* 00042400 sll a0,a0,16 */
 set(m,4u,sx((uint32_t)lo(m,4u)<<16u));target=sx(UINT32_C(0x002c0f3c));goto dispatch;
L_002c0f3c:
 STEP(UINT32_C(0x002c0f3c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c0f40));goto dispatch;
L_002c0f40:
 STEP(UINT32_C(0x002c0f40)); /* 00031c00 sll v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<16u));target=sx(UINT32_C(0x002c0f44));goto dispatch;
L_002c0f44:
 STEP(UINT32_C(0x002c0f44)); /* 00048403 sra s0,a0,16 */
 set(m,16u,sx((uint32_t)((int32_t)lo(m,4u)>>16u)));target=sx(UINT32_C(0x002c0f48));goto dispatch;
L_002c0f48:
 STEP(UINT32_C(0x002c0f48)); /* ffbf0008 sd ra,0x8(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c0f4c));goto dispatch;
L_002c0f4c:
 STEP(UINT32_C(0x002c0f4c)); /* 10830018 beq a0,v1,002c0fb0 */
 {int taken=(lo(m,4u)==lo(m,3u));STEP(UINT32_C(0x002c0f50));set(m,5u,sx((uint32_t)lo(m,16u)<<7u));target=sx(taken?UINT32_C(0x002c0fb0):UINT32_C(0x002c0f54));goto dispatch;}
L_002c0f50:
 STEP(UINT32_C(0x002c0f50)); /* 001029c0 sll a1,s0,7 */
 set(m,5u,sx((uint32_t)lo(m,16u)<<7u));target=sx(UINT32_C(0x002c0f54));goto dispatch;
L_002c0f54:
 STEP(UINT32_C(0x002c0f54)); /* 3c020059 lui v0,zero,0x59 */
 set(m,2u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c0f58));goto dispatch;
L_002c0f58:
 STEP(UINT32_C(0x002c0f58)); /* 24420840 addiu v0,v0,2112 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000840)));target=sx(UINT32_C(0x002c0f5c));goto dispatch;
L_002c0f5c:
 STEP(UINT32_C(0x002c0f5c)); /* 00451021 addu v0,v0,a1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002c0f60));goto dispatch;
L_002c0f60:
 STEP(UINT32_C(0x002c0f60)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c0f64));goto dispatch;
L_002c0f64:
 STEP(UINT32_C(0x002c0f64)); /* 9046000f lbu a2,0xf(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0x0000000f),&byte,1u);set(m,6u,byte);}target=sx(UINT32_C(0x002c0f68));goto dispatch;
L_002c0f68:
 STEP(UINT32_C(0x002c0f68)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c0f6c));goto dispatch;
L_002c0f6c:
 STEP(UINT32_C(0x002c0f6c)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c0f70));goto dispatch;
L_002c0f70:
 STEP(UINT32_C(0x002c0f70)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c0f74));goto dispatch;
L_002c0f74:
 STEP(UINT32_C(0x002c0f74)); /* 0000482d daddu t1,zero,zero */
 set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c0f78));goto dispatch;
L_002c0f78:
 STEP(UINT32_C(0x002c0f78)); /* 0c0b78ac jal 002de2b0 */
 set(m,31u,UINT64_C(0x002c0f80));STEP(UINT32_C(0x002c0f7c));set(m,6u,lo(m,6u) & UINT64_C(0xf0));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002c0f7c:
 STEP(UINT32_C(0x002c0f7c)); /* 30c600f0 andi a2,a2,0xf0 */
 set(m,6u,lo(m,6u) & UINT64_C(0xf0));target=sx(UINT32_C(0x002c0f80));goto dispatch;
L_002c0f80:
 STEP(UINT32_C(0x002c0f80)); /* 26030001 addiu v1,s0,1 */
 set(m,3u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c0f84));goto dispatch;
L_002c0f84:
 STEP(UINT32_C(0x002c0f84)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c0f88));goto dispatch;
L_002c0f88:
 STEP(UINT32_C(0x002c0f88)); /* 3070001f andi s0,v1,0x1f */
 set(m,16u,lo(m,3u) & UINT64_C(0x1f));target=sx(UINT32_C(0x002c0f8c));goto dispatch;
L_002c0f8c:
 STEP(UINT32_C(0x002c0f8c)); /* 14400006 bne v0,zero,002c0fa8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002c0f90));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9950)));target=sx(taken?UINT32_C(0x002c0fa8):UINT32_C(0x002c0f94));goto dispatch;}
L_002c0f90:
 STEP(UINT32_C(0x002c0f90)); /* 24849950 addiu a0,a0,-26288 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9950)));target=sx(UINT32_C(0x002c0f94));goto dispatch;
L_002c0f94:
 STEP(UINT32_C(0x002c0f94)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c0f9c));STEP(UINT32_C(0x002c0f98));/* nop */target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c0f98:
 STEP(UINT32_C(0x002c0f98)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0f9c));goto dispatch;
L_002c0f9c:
 STEP(UINT32_C(0x002c0f9c)); /* 10000004 beq zero,zero,002c0fb0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c0fa0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002c0fb0):UINT32_C(0x002c0fa4));goto dispatch;}
L_002c0fa0:
 STEP(UINT32_C(0x002c0fa0)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c0fa4));goto dispatch;
L_002c0fa4:
 STEP(UINT32_C(0x002c0fa4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0fa8));goto dispatch;
L_002c0fa8:
 STEP(UINT32_C(0x002c0fa8)); /* a790dfc2 sh s0,-0x203e(gp) */
 value16=(uint16_t)lo(m,16u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc2),&value16,2u);target=sx(UINT32_C(0x002c0fac));goto dispatch;
L_002c0fac:
 STEP(UINT32_C(0x002c0fac)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c0fb0));goto dispatch;
L_002c0fb0:
 STEP(UINT32_C(0x002c0fb0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c0fb4));goto dispatch;
L_002c0fb4:
 STEP(UINT32_C(0x002c0fb4)); /* dfbf0008 ld ra,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c0fb8));goto dispatch;
L_002c0fb8:
 STEP(UINT32_C(0x002c0fb8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c0fbc));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002c0fbc:
 STEP(UINT32_C(0x002c0fbc)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002c0fc0));goto dispatch;
L_002de178:
 STEP(UINT32_C(0x002de178)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x002de17c));goto dispatch;
L_002de17c:
 STEP(UINT32_C(0x002de17c)); /* ffb10030 sd s1,0x30(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002de180));goto dispatch;
L_002de180:
 STEP(UINT32_C(0x002de180)); /* ffb40060 sd s4,0x60(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002de184));goto dispatch;
L_002de184:
 STEP(UINT32_C(0x002de184)); /* 00e0882d daddu s1,a3,zero */
 set(m,17u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002de188));goto dispatch;
L_002de188:
 STEP(UINT32_C(0x002de188)); /* ffb30050 sd s3,0x50(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002de18c));goto dispatch;
L_002de18c:
 STEP(UINT32_C(0x002de18c)); /* 0080a02d daddu s4,a0,zero */
 set(m,20u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002de190));goto dispatch;
L_002de190:
 STEP(UINT32_C(0x002de190)); /* ffb00020 sd s0,0x20(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002de194));goto dispatch;
L_002de194:
 STEP(UINT32_C(0x002de194)); /* 2622fff0 addiu v0,s1,-16 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002de198));goto dispatch;
L_002de198:
 STEP(UINT32_C(0x002de198)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002de19c));goto dispatch;
L_002de19c:
 STEP(UINT32_C(0x002de19c)); /* ffbf0070 sd ra,0x70(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002de1a0));goto dispatch;
L_002de1a0:
 STEP(UINT32_C(0x002de1a0)); /* ffb20040 sd s2,0x40(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002de1a4));goto dispatch;
L_002de1a4:
 STEP(UINT32_C(0x002de1a4)); /* 00c0802d daddu s0,a2,zero */
 set(m,16u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002de1a8));goto dispatch;
L_002de1a8:
 STEP(UINT32_C(0x002de1a8)); /* 0100202d daddu a0,t0,zero */
 set(m,4u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002de1ac));goto dispatch;
L_002de1ac:
 STEP(UINT32_C(0x002de1ac)); /* 2c420061 sltiu v0,v0,97 */
 set(m,2u,(lo(m,2u)<UINT64_C(0x61)));target=sx(UINT32_C(0x002de1b0));goto dispatch;
L_002de1b0:
 STEP(UINT32_C(0x002de1b0)); /* 14400003 bne v0,zero,002de1c0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002de1b4));set(m,5u,lo(m,10u)+lo(m,0u));target=sx(taken?UINT32_C(0x002de1c0):UINT32_C(0x002de1b8));goto dispatch;}
L_002de1b4:
 STEP(UINT32_C(0x002de1b4)); /* 0140282d daddu a1,t2,zero */
 set(m,5u,lo(m,10u)+lo(m,0u));target=sx(UINT32_C(0x002de1b8));goto dispatch;
L_002de1b8:
 STEP(UINT32_C(0x002de1b8)); /* 10000034 beq zero,zero,002de28c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de1bc));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002de28c):UINT32_C(0x002de1c0));goto dispatch;}
L_002de1bc:
 STEP(UINT32_C(0x002de1bc)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de1c0));goto dispatch;
L_002de1c0:
 STEP(UINT32_C(0x002de1c0)); /* 18a00011 blez a1,zero,002de208 */
 {int taken=((int64_t)lo(m,5u)<=0);STEP(UINT32_C(0x002de1c4));set(m,18u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002de208):UINT32_C(0x002de1c8));goto dispatch;}
L_002de1c4:
 STEP(UINT32_C(0x002de1c4)); /* 0000902d daddu s2,zero,zero */
 set(m,18u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de1c8));goto dispatch;
L_002de1c8:
 STEP(UINT32_C(0x002de1c8)); /* 92020000 lbu v0,0x0(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002de1cc));goto dispatch;
L_002de1cc:
 STEP(UINT32_C(0x002de1cc)); /* 00051a00 sll v1,a1,8 */
 set(m,3u,sx((uint32_t)lo(m,5u)<<8u));target=sx(UINT32_C(0x002de1d0));goto dispatch;
L_002de1d0:
 STEP(UINT32_C(0x002de1d0)); /* ae090004 sw t1,0x4(s0) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002de1d4));goto dispatch;
L_002de1d4:
 STEP(UINT32_C(0x002de1d4)); /* 24120001 addiu s2,zero,1 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de1d8));goto dispatch;
L_002de1d8:
 STEP(UINT32_C(0x002de1d8)); /* 00431025 or v0,v0,v1 */
 set(m,2u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x002de1dc));goto dispatch;
L_002de1dc:
 STEP(UINT32_C(0x002de1dc)); /* afa40000 sw a0,0x0(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de1e0));goto dispatch;
L_002de1e0:
 STEP(UINT32_C(0x002de1e0)); /* ae020000 sw v0,0x0(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de1e4));goto dispatch;
L_002de1e4:
 STEP(UINT32_C(0x002de1e4)); /* 32630004 andi v1,s3,0x4 */
 set(m,3u,lo(m,19u) & UINT64_C(0x4));target=sx(UINT32_C(0x002de1e8));goto dispatch;
L_002de1e8:
 STEP(UINT32_C(0x002de1e8)); /* afa90004 sw t1,0x4(sp) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002de1ec));goto dispatch;
L_002de1ec:
 STEP(UINT32_C(0x002de1ec)); /* afa50008 sw a1,0x8(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002de1f0));goto dispatch;
L_002de1f0:
 STEP(UINT32_C(0x002de1f0)); /* 10600008 beq v1,zero,002de214 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002de1f4));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000c),&value32,4u);target=sx(taken?UINT32_C(0x002de214):UINT32_C(0x002de1f8));goto dispatch;}
L_002de1f4:
 STEP(UINT32_C(0x002de1f4)); /* afa0000c sw zero,0xc(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002de1f8));goto dispatch;
L_002de1f8:
 STEP(UINT32_C(0x002de1f8)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002de200));STEP(UINT32_C(0x002de1fc));/* nop */target=sx(UINT32_C(0x002de458));goto dispatch;
L_002de1fc:
 STEP(UINT32_C(0x002de1fc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de200));goto dispatch;
L_002de200:
 STEP(UINT32_C(0x002de200)); /* 10000005 beq zero,zero,002de218 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de204));set(m,5u,sx((uint32_t)lo(m,18u)<<4u));target=sx(taken?UINT32_C(0x002de218):UINT32_C(0x002de208));goto dispatch;}
L_002de204:
 STEP(UINT32_C(0x002de204)); /* 00122900 sll a1,s2,4 */
 set(m,5u,sx((uint32_t)lo(m,18u)<<4u));target=sx(UINT32_C(0x002de208));goto dispatch;
L_002de208:
 STEP(UINT32_C(0x002de208)); /* 92020000 lbu v0,0x0(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002de20c));goto dispatch;
L_002de20c:
 STEP(UINT32_C(0x002de20c)); /* ae000004 sw zero,0x4(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002de210));goto dispatch;
L_002de210:
 STEP(UINT32_C(0x002de210)); /* ae020000 sw v0,0x0(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de214));goto dispatch;
L_002de214:
 STEP(UINT32_C(0x002de214)); /* 00122900 sll a1,s2,4 */
 set(m,5u,sx((uint32_t)lo(m,18u)<<4u));target=sx(UINT32_C(0x002de218));goto dispatch;
L_002de218:
 STEP(UINT32_C(0x002de218)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002de21c));goto dispatch;
L_002de21c:
 STEP(UINT32_C(0x002de21c)); /* 8c44baa0 lw a0,-0x4560(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbaa0),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de220));goto dispatch;
L_002de220:
 STEP(UINT32_C(0x002de220)); /* 03a51821 addu v1,sp,a1 */
 set(m,3u,sx((uint32_t)lo(m,29u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002de224));goto dispatch;
L_002de224:
 STEP(UINT32_C(0x002de224)); /* ac700000 sw s0,0x0(v1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de228));goto dispatch;
L_002de228:
 STEP(UINT32_C(0x002de228)); /* 27a20004 addiu v0,sp,4 */
 set(m,2u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002de22c));goto dispatch;
L_002de22c:
 STEP(UINT32_C(0x002de22c)); /* 00451021 addu v0,v0,a1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002de230));goto dispatch;
L_002de230:
 STEP(UINT32_C(0x002de230)); /* 27a30008 addiu v1,sp,8 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002de234));goto dispatch;
L_002de234:
 STEP(UINT32_C(0x002de234)); /* ac440000 sw a0,0x0(v0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de238));goto dispatch;
L_002de238:
 STEP(UINT32_C(0x002de238)); /* 00651821 addu v1,v1,a1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002de23c));goto dispatch;
L_002de23c:
 STEP(UINT32_C(0x002de23c)); /* ac710000 sw s1,0x0(v1) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de240));goto dispatch;
L_002de240:
 STEP(UINT32_C(0x002de240)); /* 27a4000c addiu a0,sp,12 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002de244));goto dispatch;
L_002de244:
 STEP(UINT32_C(0x002de244)); /* 00852021 addu a0,a0,a1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002de248));goto dispatch;
L_002de248:
 STEP(UINT32_C(0x002de248)); /* ae140008 sw s4,0x8(s0) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002de24c));goto dispatch;
L_002de24c:
 STEP(UINT32_C(0x002de24c)); /* a2110000 sb s1,0x0(s0) */
 {uint8_t byte=(uint8_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002de250));goto dispatch;
L_002de250:
 STEP(UINT32_C(0x002de250)); /* 24020044 addiu v0,zero,68 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000044)));target=sx(UINT32_C(0x002de254));goto dispatch;
L_002de254:
 STEP(UINT32_C(0x002de254)); /* ac820000 sw v0,0x0(a0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de258));goto dispatch;
L_002de258:
 STEP(UINT32_C(0x002de258)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002de25c));goto dispatch;
L_002de25c:
 STEP(UINT32_C(0x002de25c)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de260));goto dispatch;
L_002de260:
 STEP(UINT32_C(0x002de260)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002de268));STEP(UINT32_C(0x002de264));set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002de264:
 STEP(UINT32_C(0x002de264)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de268));goto dispatch;
L_002de268:
 STEP(UINT32_C(0x002de268)); /* 32620001 andi v0,s3,0x1 */
 set(m,2u,lo(m,19u) & UINT64_C(0x1));target=sx(UINT32_C(0x002de26c));goto dispatch;
L_002de26c:
 STEP(UINT32_C(0x002de26c)); /* 10400005 beq v0,zero,002de284 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002de270));set(m,5u,lo(m,18u)+lo(m,0u));target=sx(taken?UINT32_C(0x002de284):UINT32_C(0x002de274));goto dispatch;}
L_002de270:
 STEP(UINT32_C(0x002de270)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002de274));goto dispatch;
L_002de274:
 STEP(UINT32_C(0x002de274)); /* 0c0b709c jal 002dc270 */
 set(m,31u,UINT64_C(0x002de27c));STEP(UINT32_C(0x002de278));set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002dc270));goto dispatch;
L_002de278:
 STEP(UINT32_C(0x002de278)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002de27c));goto dispatch;
L_002de27c:
 STEP(UINT32_C(0x002de27c)); /* 10000004 beq zero,zero,002de290 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de280));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002de290):UINT32_C(0x002de284));goto dispatch;}
L_002de280:
 STEP(UINT32_C(0x002de280)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de284));goto dispatch;
L_002de284:
 STEP(UINT32_C(0x002de284)); /* 0c0b7098 jal 002dc260 */
 set(m,31u,UINT64_C(0x002de28c));STEP(UINT32_C(0x002de288));set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002dc260));goto dispatch;
L_002de288:
 STEP(UINT32_C(0x002de288)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002de28c));goto dispatch;
L_002de28c:
 STEP(UINT32_C(0x002de28c)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de290));goto dispatch;
L_002de290:
 STEP(UINT32_C(0x002de290)); /* dfb40060 ld s4,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002de294));goto dispatch;
L_002de294:
 STEP(UINT32_C(0x002de294)); /* dfb30050 ld s3,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002de298));goto dispatch;
L_002de298:
 STEP(UINT32_C(0x002de298)); /* dfb20040 ld s2,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002de29c));goto dispatch;
L_002de29c:
 STEP(UINT32_C(0x002de29c)); /* dfb10030 ld s1,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002de2a0));goto dispatch;
L_002de2a0:
 STEP(UINT32_C(0x002de2a0)); /* dfb00020 ld s0,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de2a4));goto dispatch;
L_002de2a4:
 STEP(UINT32_C(0x002de2a4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de2a8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_002de2a8:
 STEP(UINT32_C(0x002de2a8)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x002de2ac));goto dispatch;
L_002de2b0:
 STEP(UINT32_C(0x002de2b0)); /* 00c0102d daddu v0,a2,zero */
 set(m,2u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002de2b4));goto dispatch;
L_002de2b4:
 STEP(UINT32_C(0x002de2b4)); /* 00e0182d daddu v1,a3,zero */
 set(m,3u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002de2b8));goto dispatch;
L_002de2b8:
 STEP(UINT32_C(0x002de2b8)); /* 0100582d daddu t3,t0,zero */
 set(m,11u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002de2bc));goto dispatch;
L_002de2bc:
 STEP(UINT32_C(0x002de2bc)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002de2c0));goto dispatch;
L_002de2c0:
 STEP(UINT32_C(0x002de2c0)); /* 0120502d daddu t2,t1,zero */
 set(m,10u,lo(m,9u)+lo(m,0u));target=sx(UINT32_C(0x002de2c4));goto dispatch;
L_002de2c4:
 STEP(UINT32_C(0x002de2c4)); /* 00a0302d daddu a2,a1,zero */
 set(m,6u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002de2c8));goto dispatch;
L_002de2c8:
 STEP(UINT32_C(0x002de2c8)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002de2cc));goto dispatch;
L_002de2cc:
 STEP(UINT32_C(0x002de2cc)); /* 0040382d daddu a3,v0,zero */
 set(m,7u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002de2d0));goto dispatch;
L_002de2d0:
 STEP(UINT32_C(0x002de2d0)); /* 0060402d daddu t0,v1,zero */
 set(m,8u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002de2d4));goto dispatch;
L_002de2d4:
 STEP(UINT32_C(0x002de2d4)); /* 0160482d daddu t1,t3,zero */
 set(m,9u,lo(m,11u)+lo(m,0u));target=sx(UINT32_C(0x002de2d8));goto dispatch;
L_002de2d8:
 STEP(UINT32_C(0x002de2d8)); /* 0c0b785e jal 002de178 */
 set(m,31u,UINT64_C(0x002de2e0));STEP(UINT32_C(0x002de2dc));set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de178));goto dispatch;
L_002de2dc:
 STEP(UINT32_C(0x002de2dc)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de2e0));goto dispatch;
L_002de2e0:
 STEP(UINT32_C(0x002de2e0)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de2e4));goto dispatch;
L_002de2e4:
 STEP(UINT32_C(0x002de2e4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de2e8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002de2e8:
 STEP(UINT32_C(0x002de2e8)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002de2ec));goto dispatch;
L_002de458:
 STEP(UINT32_C(0x002de458)); /* 3c19ffff lui t9,zero,0xffff */
 set(m,25u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002de45c));goto dispatch;
L_002de45c:
 STEP(UINT32_C(0x002de45c)); /* 3739ffc0 ori t9,t9,0xffc0 */
 set(m,25u,lo(m,25u) | UINT64_C(0xffc0));target=sx(UINT32_C(0x002de460));goto dispatch;
L_002de460:
 STEP(UINT32_C(0x002de460)); /* 18a00026 blez a1,zero,002de4fc */
 {int taken=((int64_t)lo(m,5u)<=0);STEP(UINT32_C(0x002de464));set(m,10u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=sx(taken?UINT32_C(0x002de4fc):UINT32_C(0x002de468));goto dispatch;}
L_002de464:
 STEP(UINT32_C(0x002de464)); /* 00855021 addu t2,a0,a1 */
 set(m,10u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002de468));goto dispatch;
L_002de468:
 STEP(UINT32_C(0x002de468)); /* 00994024 and t0,a0,t9 */
 set(m,8u,lo(m,4u)&lo(m,25u));target=sx(UINT32_C(0x002de46c));goto dispatch;
L_002de46c:
 STEP(UINT32_C(0x002de46c)); /* 254affff addiu t2,t2,-1 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002de470));goto dispatch;
L_002de470:
 STEP(UINT32_C(0x002de470)); /* 01594824 and t1,t2,t9 */
 set(m,9u,lo(m,10u)&lo(m,25u));target=sx(UINT32_C(0x002de474));goto dispatch;
L_002de474:
 STEP(UINT32_C(0x002de474)); /* 01285023 subu t2,t1,t0 */
 set(m,10u,sx((uint32_t)lo(m,9u)-(uint32_t)lo(m,8u)));target=sx(UINT32_C(0x002de478));goto dispatch;
L_002de478:
 STEP(UINT32_C(0x002de478)); /* 000a5982 srl t3,t2,6 */
 set(m,11u,sx((uint32_t)lo(m,10u)>>6u));target=sx(UINT32_C(0x002de47c));goto dispatch;
L_002de47c:
 STEP(UINT32_C(0x002de47c)); /* 256b0001 addiu t3,t3,1 */
 set(m,11u,sx((uint32_t)lo(m,11u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de480));goto dispatch;
L_002de480:
 STEP(UINT32_C(0x002de480)); /* 31690007 andi t1,t3,0x7 */
 set(m,9u,lo(m,11u) & UINT64_C(0x7));target=sx(UINT32_C(0x002de484));goto dispatch;
L_002de484:
 STEP(UINT32_C(0x002de484)); /* 11200008 beq t1,zero,002de4a8 */
 {int taken=(lo(m,9u)==lo(m,0u));STEP(UINT32_C(0x002de488));set(m,10u,sx((uint32_t)lo(m,11u)>>3u));target=sx(taken?UINT32_C(0x002de4a8):UINT32_C(0x002de48c));goto dispatch;}
L_002de488:
 STEP(UINT32_C(0x002de488)); /* 000b50c2 srl t2,t3,3 */
 set(m,10u,sx((uint32_t)lo(m,11u)>>3u));target=sx(UINT32_C(0x002de48c));goto dispatch;
L_002de48c:
 STEP(UINT32_C(0x002de48c)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de490));goto dispatch;
L_002de490:
 m->pc=UINT32_C(0x002de490); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x00000000);if(!cache||!cache(cache_owner,UINT32_C(0x002de490),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de494));goto dispatch;
L_002de494:
 STEP(UINT32_C(0x002de494)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de498));goto dispatch;
L_002de498:
 STEP(UINT32_C(0x002de498)); /* 2529ffff addiu t1,t1,-1 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002de49c));goto dispatch;
L_002de49c:
 STEP(UINT32_C(0x002de49c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de4a0));goto dispatch;
L_002de4a0:
 STEP(UINT32_C(0x002de4a0)); /* 1d20fffa bgtz t1,zero,002de48c */
 {int taken=((int64_t)lo(m,9u)>0);STEP(UINT32_C(0x002de4a4));set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000040)));target=sx(taken?UINT32_C(0x002de48c):UINT32_C(0x002de4a8));goto dispatch;}
L_002de4a4:
 STEP(UINT32_C(0x002de4a4)); /* 25080040 addiu t0,t0,64 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de4a8));goto dispatch;
L_002de4a8:
 STEP(UINT32_C(0x002de4a8)); /* 11400014 beq t2,zero,002de4fc */
 {int taken=(lo(m,10u)==lo(m,0u));STEP(UINT32_C(0x002de4ac));set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002de4fc):UINT32_C(0x002de4b0));goto dispatch;}
L_002de4ac:
 STEP(UINT32_C(0x002de4ac)); /* 254affff addiu t2,t2,-1 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002de4b0));goto dispatch;
L_002de4b0:
 STEP(UINT32_C(0x002de4b0)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4b4));goto dispatch;
L_002de4b4:
 m->pc=UINT32_C(0x002de4b4); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x00000000);if(!cache||!cache(cache_owner,UINT32_C(0x002de4b4),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de4b8));goto dispatch;
L_002de4b8:
 STEP(UINT32_C(0x002de4b8)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4bc));goto dispatch;
L_002de4bc:
 m->pc=UINT32_C(0x002de4bc); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x00000040);if(!cache||!cache(cache_owner,UINT32_C(0x002de4bc),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de4c0));goto dispatch;
L_002de4c0:
 STEP(UINT32_C(0x002de4c0)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4c4));goto dispatch;
L_002de4c4:
 m->pc=UINT32_C(0x002de4c4); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x00000080);if(!cache||!cache(cache_owner,UINT32_C(0x002de4c4),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de4c8));goto dispatch;
L_002de4c8:
 STEP(UINT32_C(0x002de4c8)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4cc));goto dispatch;
L_002de4cc:
 m->pc=UINT32_C(0x002de4cc); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x000000c0);if(!cache||!cache(cache_owner,UINT32_C(0x002de4cc),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de4d0));goto dispatch;
L_002de4d0:
 STEP(UINT32_C(0x002de4d0)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4d4));goto dispatch;
L_002de4d4:
 m->pc=UINT32_C(0x002de4d4); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x00000100);if(!cache||!cache(cache_owner,UINT32_C(0x002de4d4),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de4d8));goto dispatch;
L_002de4d8:
 STEP(UINT32_C(0x002de4d8)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4dc));goto dispatch;
L_002de4dc:
 m->pc=UINT32_C(0x002de4dc); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x00000140);if(!cache||!cache(cache_owner,UINT32_C(0x002de4dc),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de4e0));goto dispatch;
L_002de4e0:
 STEP(UINT32_C(0x002de4e0)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4e4));goto dispatch;
L_002de4e4:
 m->pc=UINT32_C(0x002de4e4); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x00000180);if(!cache||!cache(cache_owner,UINT32_C(0x002de4e4),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de4e8));goto dispatch;
L_002de4e8:
 STEP(UINT32_C(0x002de4e8)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4ec));goto dispatch;
L_002de4ec:
 m->pc=UINT32_C(0x002de4ec); /* Unexecuted external primitive until its actual owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,8u)+UINT32_C(0x000001c0);if(!cache||!cache(cache_owner,UINT32_C(0x002de4ec),24u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002de4f0));goto dispatch;
L_002de4f0:
 STEP(UINT32_C(0x002de4f0)); /* 0000000f sync 0 */
 ++m->sync_p; /* Count actual SYNC0, no cache or DMA completion. */target=sx(UINT32_C(0x002de4f4));goto dispatch;
L_002de4f4:
 STEP(UINT32_C(0x002de4f4)); /* 1d40ffed bgtz t2,zero,002de4ac */
 {int taken=((int64_t)lo(m,10u)>0);STEP(UINT32_C(0x002de4f8));set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000200)));target=sx(taken?UINT32_C(0x002de4ac):UINT32_C(0x002de4fc));goto dispatch;}
L_002de4f8:
 STEP(UINT32_C(0x002de4f8)); /* 25080200 addiu t0,t0,512 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000200)));target=sx(UINT32_C(0x002de4fc));goto dispatch;
L_002de4fc:
 STEP(UINT32_C(0x002de4fc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de500));/* nop */goto dispatch;
L_002de500:
 STEP(UINT32_C(0x002de500)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de504));goto dispatch;
L_002dc260:
 STEP(UINT32_C(0x002dc260)); /* 24030077 addiu v1,zero,119 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000077)));target=sx(UINT32_C(0x002dc264));goto dispatch;
L_002dc264:
 m->pc=UINT32_C(0x002dc264); /* Unexecuted external primitive until its actual owner accepts. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dc268:
 STEP(UINT32_C(0x002dc268)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc26c));/* nop */goto dispatch;
L_002dc26c:
 STEP(UINT32_C(0x002dc26c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc270));goto dispatch;
L_002dc270:
 STEP(UINT32_C(0x002dc270)); /* 2403ff89 addiu v1,zero,-119 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff89)));target=sx(UINT32_C(0x002dc274));goto dispatch;
L_002dc274:
 m->pc=UINT32_C(0x002dc274); /* Unexecuted external primitive until its actual owner accepts. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dc278:
 STEP(UINT32_C(0x002dc278)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc27c));/* nop */goto dispatch;
L_002dc27c:
 STEP(UINT32_C(0x002dc27c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc280));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

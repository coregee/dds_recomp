#include "ps2_semaphore_kernel.h"
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
uint32_t nocturneSemaphoreKernelResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x800049c0):goto L_800049c0;
 case UINT32_C(0x800049c4):goto L_800049c4;
 case UINT32_C(0x800049c8):goto L_800049c8;
 case UINT32_C(0x800049cc):goto L_800049cc;
 case UINT32_C(0x800049d0):goto L_800049d0;
 case UINT32_C(0x800049d4):goto L_800049d4;
 case UINT32_C(0x800049d8):goto L_800049d8;
 case UINT32_C(0x800049dc):goto L_800049dc;
 case UINT32_C(0x800049e0):goto L_800049e0;
 case UINT32_C(0x800049e4):goto L_800049e4;
 case UINT32_C(0x800049e8):goto L_800049e8;
 case UINT32_C(0x800049ec):goto L_800049ec;
 case UINT32_C(0x800049f0):goto L_800049f0;
 case UINT32_C(0x800049f4):goto L_800049f4;
 case UINT32_C(0x800049f8):goto L_800049f8;
 case UINT32_C(0x800049fc):goto L_800049fc;
 case UINT32_C(0x80004a00):goto L_80004a00;
 case UINT32_C(0x80004a04):goto L_80004a04;
 case UINT32_C(0x80004a08):goto L_80004a08;
 case UINT32_C(0x80004a0c):goto L_80004a0c;
 case UINT32_C(0x80004a10):goto L_80004a10;
 case UINT32_C(0x80004a14):goto L_80004a14;
 case UINT32_C(0x80004a18):goto L_80004a18;
 case UINT32_C(0x80004a1c):goto L_80004a1c;
 case UINT32_C(0x80004a20):goto L_80004a20;
 case UINT32_C(0x80004a24):goto L_80004a24;
 case UINT32_C(0x80004a28):goto L_80004a28;
 case UINT32_C(0x80004a2c):goto L_80004a2c;
 case UINT32_C(0x80004a30):goto L_80004a30;
 case UINT32_C(0x80004a34):goto L_80004a34;
 case UINT32_C(0x80004a38):goto L_80004a38;
 case UINT32_C(0x80004a3c):goto L_80004a3c;
 case UINT32_C(0x80004a40):goto L_80004a40;
 case UINT32_C(0x80004e68):goto L_80004e68;
 case UINT32_C(0x80004e6c):goto L_80004e6c;
 case UINT32_C(0x80004e70):goto L_80004e70;
 case UINT32_C(0x80004e74):goto L_80004e74;
 case UINT32_C(0x80004e78):goto L_80004e78;
 case UINT32_C(0x80004e7c):goto L_80004e7c;
 case UINT32_C(0x80004e80):goto L_80004e80;
 case UINT32_C(0x80004e84):goto L_80004e84;
 case UINT32_C(0x80004e88):goto L_80004e88;
 case UINT32_C(0x80004e8c):goto L_80004e8c;
 case UINT32_C(0x80004e90):goto L_80004e90;
 case UINT32_C(0x80004e94):goto L_80004e94;
 case UINT32_C(0x80004e98):goto L_80004e98;
 case UINT32_C(0x80004e9c):goto L_80004e9c;
 case UINT32_C(0x80004ea0):goto L_80004ea0;
 case UINT32_C(0x80004ea4):goto L_80004ea4;
 case UINT32_C(0x80004ea8):goto L_80004ea8;
 case UINT32_C(0x80004eac):goto L_80004eac;
 case UINT32_C(0x80004eb0):goto L_80004eb0;
 case UINT32_C(0x80004eb4):goto L_80004eb4;
 case UINT32_C(0x80004eb8):goto L_80004eb8;
 case UINT32_C(0x80004ebc):goto L_80004ebc;
 case UINT32_C(0x80004ec0):goto L_80004ec0;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_800049c0:
 STEP(UINT32_C(0x800049c0)); /* 3c068001 lui a2,zero,0x8001 */
 set(m,6u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800049c4));goto dispatch;
L_800049c4:
 STEP(UINT32_C(0x800049c4)); /* 8cc673fc lw a2,0x73fc(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x000073fc),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x800049c8));goto dispatch;
L_800049c8:
 STEP(UINT32_C(0x800049c8)); /* 10c00004 beq a2,zero,800049dc */
 {int taken=(lo(m,6u)==lo(m,0u));STEP(UINT32_C(0x800049cc));set(m,7u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x800049dc):UINT32_C(0x800049d0));goto dispatch;}
L_800049cc:
 STEP(UINT32_C(0x800049cc)); /* 0080382d daddu a3,a0,zero */
 set(m,7u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x800049d0));goto dispatch;
L_800049d0:
 STEP(UINT32_C(0x800049d0)); /* 8ce80008 lw t0,0x8(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x800049d4));goto dispatch;
L_800049d4:
 STEP(UINT32_C(0x800049d4)); /* 05010003 regimm1 t0,800049e4 */
 {int taken=((int64_t)lo(m,8u)>=0);STEP(UINT32_C(0x800049d8));set(m,4u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000018)));target=sx(taken?UINT32_C(0x800049e4):UINT32_C(0x800049dc));goto dispatch;}
L_800049d8:
 STEP(UINT32_C(0x800049d8)); /* 24c40018 addiu a0,a2,24 */
 set(m,4u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000018)));target=sx(UINT32_C(0x800049dc));goto dispatch;
L_800049dc:
 STEP(UINT32_C(0x800049dc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800049e0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));goto dispatch;
L_800049e0:
 STEP(UINT32_C(0x800049e0)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x800049e4));goto dispatch;
L_800049e4:
 STEP(UINT32_C(0x800049e4)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800049e8));goto dispatch;
L_800049e8:
 STEP(UINT32_C(0x800049e8)); /* 8c6373f8 lw v1,0x73f8(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x000073f8),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x800049ec));goto dispatch;
L_800049ec:
 STEP(UINT32_C(0x800049ec)); /* ac840004 sw a0,0x4(a0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x800049f0));goto dispatch;
L_800049f0:
 STEP(UINT32_C(0x800049f0)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800049f4));goto dispatch;
L_800049f4:
 STEP(UINT32_C(0x800049f4)); /* 2442c000 addiu v0,v0,-16384 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffc000)));target=sx(UINT32_C(0x800049f8));goto dispatch;
L_800049f8:
 STEP(UINT32_C(0x800049f8)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800049fc));goto dispatch;
L_800049fc:
 STEP(UINT32_C(0x800049fc)); /* 8cc50000 lw a1,0x0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80004a00));goto dispatch;
L_80004a00:
 STEP(UINT32_C(0x80004a00)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004a04));goto dispatch;
L_80004a04:
 STEP(UINT32_C(0x80004a04)); /* ac2373f8 sw v1,0x73f8(at) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000073f8),&value32,4u);target=sx(UINT32_C(0x80004a08));goto dispatch;
L_80004a08:
 STEP(UINT32_C(0x80004a08)); /* 00c21023 subu v0,a2,v0 */
 set(m,2u,sx((uint32_t)lo(m,6u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80004a0c));goto dispatch;
L_80004a0c:
 STEP(UINT32_C(0x80004a0c)); /* acc80004 sw t0,0x4(a2) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80004a10));goto dispatch;
L_80004a10:
 STEP(UINT32_C(0x80004a10)); /* 00021143 sra v0,v0,5 */
 set(m,2u,sx((uint32_t)((int32_t)lo(m,2u)>>5u)));target=sx(UINT32_C(0x80004a14));goto dispatch;
L_80004a14:
 STEP(UINT32_C(0x80004a14)); /* acc40018 sw a0,0x18(a2) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x80004a18));goto dispatch;
L_80004a18:
 STEP(UINT32_C(0x80004a18)); /* 8ce30004 lw v1,0x4(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004a1c));goto dispatch;
L_80004a1c:
 STEP(UINT32_C(0x80004a1c)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004a20));goto dispatch;
L_80004a20:
 STEP(UINT32_C(0x80004a20)); /* ac2573fc sw a1,0x73fc(at) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000073fc),&value32,4u);target=sx(UINT32_C(0x80004a24));goto dispatch;
L_80004a24:
 STEP(UINT32_C(0x80004a24)); /* acc30008 sw v1,0x8(a2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x80004a28));goto dispatch;
L_80004a28:
 STEP(UINT32_C(0x80004a28)); /* acc00000 sw zero,0x0(a2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004a2c));goto dispatch;
L_80004a2c:
 STEP(UINT32_C(0x80004a2c)); /* 8ce30010 lw v1,0x10(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000010),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004a30));goto dispatch;
L_80004a30:
 STEP(UINT32_C(0x80004a30)); /* acc3000c sw v1,0xc(a2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x80004a34));goto dispatch;
L_80004a34:
 STEP(UINT32_C(0x80004a34)); /* 8ce40014 lw a0,0x14(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000014),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80004a38));goto dispatch;
L_80004a38:
 STEP(UINT32_C(0x80004a38)); /* acc00014 sw zero,0x14(a2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x80004a3c));goto dispatch;
L_80004a3c:
 STEP(UINT32_C(0x80004a3c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004a40));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000010),&value32,4u);goto dispatch;
L_80004a40:
 STEP(UINT32_C(0x80004a40)); /* acc40010 sw a0,0x10(a2) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x80004a44));goto dispatch;
L_80004e68:
 STEP(UINT32_C(0x80004e68)); /* 3c058002 lui a1,zero,0x8002 */
 set(m,5u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80004e6c));goto dispatch;
L_80004e6c:
 STEP(UINT32_C(0x80004e6c)); /* 24a5dfe0 addiu a1,a1,-8224 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffdfe0)));target=sx(UINT32_C(0x80004e70));goto dispatch;
L_80004e70:
 STEP(UINT32_C(0x80004e70)); /* 2406ffff addiu a2,zero,-1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004e74));goto dispatch;
L_80004e74:
 STEP(UINT32_C(0x80004e74)); /* 24a2e038 addiu v0,a1,-8136 */
 set(m,2u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffe038)));target=sx(UINT32_C(0x80004e78));goto dispatch;
L_80004e78:
 STEP(UINT32_C(0x80004e78)); /* 24a3e040 addiu v1,a1,-8128 */
 set(m,3u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffe040)));target=sx(UINT32_C(0x80004e7c));goto dispatch;
L_80004e7c:
 STEP(UINT32_C(0x80004e7c)); /* 240400ff addiu a0,zero,255 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000ff)));target=sx(UINT32_C(0x80004e80));goto dispatch;
L_80004e80:
 STEP(UINT32_C(0x80004e80)); /* ac43ffe8 sw v1,-0x18(v0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffffffe8),&value32,4u);target=sx(UINT32_C(0x80004e84));goto dispatch;
L_80004e84:
 STEP(UINT32_C(0x80004e84)); /* 2484ffff addiu a0,a0,-1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004e88));goto dispatch;
L_80004e88:
 STEP(UINT32_C(0x80004e88)); /* ac46ffec sw a2,-0x14(v0) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffffffec),&value32,4u);target=sx(UINT32_C(0x80004e8c));goto dispatch;
L_80004e8c:
 STEP(UINT32_C(0x80004e8c)); /* 24630020 addiu v1,v1,32 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x80004e90));goto dispatch;
L_80004e90:
 STEP(UINT32_C(0x80004e90)); /* ac40fffc sw zero,-0x4(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xfffffffc),&value32,4u);target=sx(UINT32_C(0x80004e94));goto dispatch;
L_80004e94:
 STEP(UINT32_C(0x80004e94)); /* ac420004 sw v0,0x4(v0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80004e98));goto dispatch;
L_80004e98:
 STEP(UINT32_C(0x80004e98)); /* ac420000 sw v0,0x0(v0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004e9c));goto dispatch;
L_80004e9c:
 STEP(UINT32_C(0x80004e9c)); /* 0481fff8 regimm1 a0,80004e80 */
 {int taken=((int64_t)lo(m,4u)>=0);STEP(UINT32_C(0x80004ea0));set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000020)));target=sx(taken?UINT32_C(0x80004e80):UINT32_C(0x80004ea4));goto dispatch;}
L_80004ea0:
 STEP(UINT32_C(0x80004ea0)); /* 24420020 addiu v0,v0,32 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x80004ea4));goto dispatch;
L_80004ea4:
 STEP(UINT32_C(0x80004ea4)); /* 24a2e020 addiu v0,a1,-8160 */
 set(m,2u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffe020)));target=sx(UINT32_C(0x80004ea8));goto dispatch;
L_80004ea8:
 STEP(UINT32_C(0x80004ea8)); /* aca00000 sw zero,0x0(a1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004eac));goto dispatch;
L_80004eac:
 STEP(UINT32_C(0x80004eac)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004eb0));goto dispatch;
L_80004eb0:
 STEP(UINT32_C(0x80004eb0)); /* ac2273fc sw v0,0x73fc(at) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000073fc),&value32,4u);target=sx(UINT32_C(0x80004eb4));goto dispatch;
L_80004eb4:
 STEP(UINT32_C(0x80004eb4)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004eb8));goto dispatch;
L_80004eb8:
 STEP(UINT32_C(0x80004eb8)); /* ac2073f8 sw zero,0x73f8(at) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000073f8),&value32,4u);target=sx(UINT32_C(0x80004ebc));goto dispatch;
L_80004ebc:
 STEP(UINT32_C(0x80004ebc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004ec0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000100)));goto dispatch;
L_80004ec0:
 STEP(UINT32_C(0x80004ec0)); /* 24020100 addiu v0,zero,256 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000100)));target=sx(UINT32_C(0x80004ec4));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

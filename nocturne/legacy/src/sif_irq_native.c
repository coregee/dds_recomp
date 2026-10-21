#include "sif_irq_native.h"
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
static uint32_t plzcw(uint32_t v)
{uint32_t n=0;if(v&0x80000000u)v=~v;while(n<31u&&!(v&0x40000000u)){++n;v<<=1;}return n;}
uint32_t nocturneSifIrqResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x800004c0):goto L_800004c0;
 case UINT32_C(0x800004c4):goto L_800004c4;
 case UINT32_C(0x800004c8):goto L_800004c8;
 case UINT32_C(0x800004cc):goto L_800004cc;
 case UINT32_C(0x800004d0):goto L_800004d0;
 case UINT32_C(0x800004d4):goto L_800004d4;
 case UINT32_C(0x800004d8):goto L_800004d8;
 case UINT32_C(0x800004dc):goto L_800004dc;
 case UINT32_C(0x800004e0):goto L_800004e0;
 case UINT32_C(0x800004e4):goto L_800004e4;
 case UINT32_C(0x800004e8):goto L_800004e8;
 case UINT32_C(0x800004ec):goto L_800004ec;
 case UINT32_C(0x800004f0):goto L_800004f0;
 case UINT32_C(0x800004f4):goto L_800004f4;
 case UINT32_C(0x800004f8):goto L_800004f8;
 case UINT32_C(0x800004fc):goto L_800004fc;
 case UINT32_C(0x80000500):goto L_80000500;
 case UINT32_C(0x80000504):goto L_80000504;
 case UINT32_C(0x80000508):goto L_80000508;
 case UINT32_C(0x8000050c):goto L_8000050c;
 case UINT32_C(0x80000510):goto L_80000510;
 case UINT32_C(0x80000514):goto L_80000514;
 case UINT32_C(0x80000518):goto L_80000518;
 case UINT32_C(0x8000051c):goto L_8000051c;
 case UINT32_C(0x80000520):goto L_80000520;
 case UINT32_C(0x80000524):goto L_80000524;
 case UINT32_C(0x80000528):goto L_80000528;
 case UINT32_C(0x8000052c):goto L_8000052c;
 case UINT32_C(0x80000530):goto L_80000530;
 case UINT32_C(0x80000534):goto L_80000534;
 case UINT32_C(0x80000538):goto L_80000538;
 case UINT32_C(0x8000053c):goto L_8000053c;
 case UINT32_C(0x80000540):goto L_80000540;
 case UINT32_C(0x80000544):goto L_80000544;
 case UINT32_C(0x80000548):goto L_80000548;
 case UINT32_C(0x8000054c):goto L_8000054c;
 case UINT32_C(0x80000550):goto L_80000550;
 case UINT32_C(0x80000554):goto L_80000554;
 case UINT32_C(0x80000558):goto L_80000558;
 case UINT32_C(0x8000055c):goto L_8000055c;
 case UINT32_C(0x80000560):goto L_80000560;
 case UINT32_C(0x80000564):goto L_80000564;
 case UINT32_C(0x80000568):goto L_80000568;
 case UINT32_C(0x8000056c):goto L_8000056c;
 case UINT32_C(0x80000570):goto L_80000570;
 case UINT32_C(0x80000574):goto L_80000574;
 case UINT32_C(0x80000578):goto L_80000578;
 case UINT32_C(0x8000057c):goto L_8000057c;
 case UINT32_C(0x80000580):goto L_80000580;
 case UINT32_C(0x80000584):goto L_80000584;
 case UINT32_C(0x80000588):goto L_80000588;
 case UINT32_C(0x8000058c):goto L_8000058c;
 case UINT32_C(0x80000590):goto L_80000590;
 case UINT32_C(0x80000594):goto L_80000594;
 case UINT32_C(0x80000598):goto L_80000598;
 case UINT32_C(0x8000059c):goto L_8000059c;
 case UINT32_C(0x800005a0):goto L_800005a0;
 case UINT32_C(0x800005a4):goto L_800005a4;
 case UINT32_C(0x800005a8):goto L_800005a8;
 case UINT32_C(0x800005ac):goto L_800005ac;
 case UINT32_C(0x800005b0):goto L_800005b0;
 case UINT32_C(0x800005b4):goto L_800005b4;
 case UINT32_C(0x800005b8):goto L_800005b8;
 case UINT32_C(0x800005bc):goto L_800005bc;
 case UINT32_C(0x800005c0):goto L_800005c0;
 case UINT32_C(0x800005c4):goto L_800005c4;
 case UINT32_C(0x800005c8):goto L_800005c8;
 case UINT32_C(0x800005cc):goto L_800005cc;
 case UINT32_C(0x80001798):goto L_80001798;
 case UINT32_C(0x8000179c):goto L_8000179c;
 case UINT32_C(0x800017a0):goto L_800017a0;
 case UINT32_C(0x800017a4):goto L_800017a4;
 case UINT32_C(0x800017a8):goto L_800017a8;
 case UINT32_C(0x800017ac):goto L_800017ac;
 case UINT32_C(0x800017b0):goto L_800017b0;
 case UINT32_C(0x800017b4):goto L_800017b4;
 case UINT32_C(0x800017b8):goto L_800017b8;
 case UINT32_C(0x800017bc):goto L_800017bc;
 case UINT32_C(0x800017c0):goto L_800017c0;
 case UINT32_C(0x800017c4):goto L_800017c4;
 case UINT32_C(0x800017c8):goto L_800017c8;
 case UINT32_C(0x800017cc):goto L_800017cc;
 case UINT32_C(0x800017d0):goto L_800017d0;
 case UINT32_C(0x800017d4):goto L_800017d4;
 case UINT32_C(0x800017d8):goto L_800017d8;
 case UINT32_C(0x800017dc):goto L_800017dc;
 case UINT32_C(0x800017e0):goto L_800017e0;
 case UINT32_C(0x800017e4):goto L_800017e4;
 case UINT32_C(0x800017e8):goto L_800017e8;
 case UINT32_C(0x800017ec):goto L_800017ec;
 case UINT32_C(0x800017f0):goto L_800017f0;
 case UINT32_C(0x800017f4):goto L_800017f4;
 case UINT32_C(0x800017f8):goto L_800017f8;
 case UINT32_C(0x800017fc):goto L_800017fc;
 case UINT32_C(0x80001800):goto L_80001800;
 case UINT32_C(0x80001804):goto L_80001804;
 case UINT32_C(0x80001808):goto L_80001808;
 case UINT32_C(0x8000180c):goto L_8000180c;
 case UINT32_C(0x80001810):goto L_80001810;
 case UINT32_C(0x80001814):goto L_80001814;
 case UINT32_C(0x80001818):goto L_80001818;
 case UINT32_C(0x8000181c):goto L_8000181c;
 case UINT32_C(0x80001820):goto L_80001820;
 case UINT32_C(0x80001824):goto L_80001824;
 case UINT32_C(0x80001828):goto L_80001828;
 case UINT32_C(0x8000182c):goto L_8000182c;
 case UINT32_C(0x80001830):goto L_80001830;
 case UINT32_C(0x80001834):goto L_80001834;
 case UINT32_C(0x80001838):goto L_80001838;
 case UINT32_C(0x8000183c):goto L_8000183c;
 case UINT32_C(0x80001840):goto L_80001840;
 case UINT32_C(0x80001844):goto L_80001844;
 case UINT32_C(0x80001848):goto L_80001848;
 case UINT32_C(0x8000184c):goto L_8000184c;
 case UINT32_C(0x80001850):goto L_80001850;
 case UINT32_C(0x80001854):goto L_80001854;
 case UINT32_C(0x80001858):goto L_80001858;
 case UINT32_C(0x8000185c):goto L_8000185c;
 case UINT32_C(0x80001860):goto L_80001860;
 case UINT32_C(0x80001864):goto L_80001864;
 case UINT32_C(0x80001868):goto L_80001868;
 case UINT32_C(0x8000186c):goto L_8000186c;
 case UINT32_C(0x80001870):goto L_80001870;
 case UINT32_C(0x80001874):goto L_80001874;
 case UINT32_C(0x80001878):goto L_80001878;
 case UINT32_C(0x8000187c):goto L_8000187c;
 case UINT32_C(0x80001880):goto L_80001880;
 case UINT32_C(0x80001884):goto L_80001884;
 case UINT32_C(0x80001888):goto L_80001888;
 case UINT32_C(0x8000188c):goto L_8000188c;
 case UINT32_C(0x80001890):goto L_80001890;
 case UINT32_C(0x80001894):goto L_80001894;
 case UINT32_C(0x80001898):goto L_80001898;
 case UINT32_C(0x8000189c):goto L_8000189c;
 case UINT32_C(0x800018a0):goto L_800018a0;
 case UINT32_C(0x800018a4):goto L_800018a4;
 case UINT32_C(0x800018a8):goto L_800018a8;
 case UINT32_C(0x800018ac):goto L_800018ac;
 case UINT32_C(0x80002840):goto L_80002840;
 case UINT32_C(0x80002844):goto L_80002844;
 case UINT32_C(0x80002848):goto L_80002848;
 case UINT32_C(0x8000284c):goto L_8000284c;
 case UINT32_C(0x80002850):goto L_80002850;
 case UINT32_C(0x80002854):goto L_80002854;
 case UINT32_C(0x80002858):goto L_80002858;
 case UINT32_C(0x8000285c):goto L_8000285c;
 case UINT32_C(0x80002860):goto L_80002860;
 case UINT32_C(0x80002864):goto L_80002864;
 case UINT32_C(0x80002868):goto L_80002868;
 case UINT32_C(0x8000286c):goto L_8000286c;
 case UINT32_C(0x80002870):goto L_80002870;
 case UINT32_C(0x80002874):goto L_80002874;
 case UINT32_C(0x80002878):goto L_80002878;
 case UINT32_C(0x8000287c):goto L_8000287c;
 case UINT32_C(0x80002880):goto L_80002880;
 case UINT32_C(0x80002884):goto L_80002884;
 case UINT32_C(0x80002888):goto L_80002888;
 case UINT32_C(0x8000288c):goto L_8000288c;
 case UINT32_C(0x80002890):goto L_80002890;
 case UINT32_C(0x80002894):goto L_80002894;
 case UINT32_C(0x80002898):goto L_80002898;
 case UINT32_C(0x8000289c):goto L_8000289c;
 case UINT32_C(0x800028a0):goto L_800028a0;
 case UINT32_C(0x800028a4):goto L_800028a4;
 case UINT32_C(0x002de2f0):goto L_002de2f0;
 case UINT32_C(0x002de2f4):goto L_002de2f4;
 case UINT32_C(0x002de2f8):goto L_002de2f8;
 case UINT32_C(0x002de2fc):goto L_002de2fc;
 case UINT32_C(0x002de300):goto L_002de300;
 case UINT32_C(0x002de304):goto L_002de304;
 case UINT32_C(0x002de308):goto L_002de308;
 case UINT32_C(0x002de30c):goto L_002de30c;
 case UINT32_C(0x002de310):goto L_002de310;
 case UINT32_C(0x002de314):goto L_002de314;
 case UINT32_C(0x002de318):goto L_002de318;
 case UINT32_C(0x002de31c):goto L_002de31c;
 case UINT32_C(0x002de320):goto L_002de320;
 case UINT32_C(0x002de324):goto L_002de324;
 case UINT32_C(0x002de328):goto L_002de328;
 case UINT32_C(0x002de32c):goto L_002de32c;
 case UINT32_C(0x002dea78):goto L_002dea78;
 case UINT32_C(0x002dea7c):goto L_002dea7c;
 case UINT32_C(0x002dea80):goto L_002dea80;
 case UINT32_C(0x002dea84):goto L_002dea84;
 case UINT32_C(0x002dea88):goto L_002dea88;
 case UINT32_C(0x002dea8c):goto L_002dea8c;
 case UINT32_C(0x002dea90):goto L_002dea90;
 case UINT32_C(0x002dea94):goto L_002dea94;
 case UINT32_C(0x002dea98):goto L_002dea98;
 case UINT32_C(0x002dea9c):goto L_002dea9c;
 case UINT32_C(0x002deaa0):goto L_002deaa0;
 case UINT32_C(0x002deaa4):goto L_002deaa4;
 case UINT32_C(0x002deaa8):goto L_002deaa8;
 case UINT32_C(0x002deaac):goto L_002deaac;
 case UINT32_C(0x002deab0):goto L_002deab0;
 case UINT32_C(0x002deab4):goto L_002deab4;
 case UINT32_C(0x002deab8):goto L_002deab8;
 case UINT32_C(0x002deabc):goto L_002deabc;
 case UINT32_C(0x002deac0):goto L_002deac0;
 case UINT32_C(0x002deac4):goto L_002deac4;
 case UINT32_C(0x002deac8):goto L_002deac8;
 case UINT32_C(0x002deacc):goto L_002deacc;
 case UINT32_C(0x002dead0):goto L_002dead0;
 case UINT32_C(0x002dead4):goto L_002dead4;
 case UINT32_C(0x002dead8):goto L_002dead8;
 case UINT32_C(0x002deadc):goto L_002deadc;
 case UINT32_C(0x002deae0):goto L_002deae0;
 case UINT32_C(0x002deae4):goto L_002deae4;
 case UINT32_C(0x002deae8):goto L_002deae8;
 case UINT32_C(0x002deaec):goto L_002deaec;
 case UINT32_C(0x002deaf0):goto L_002deaf0;
 case UINT32_C(0x002deaf4):goto L_002deaf4;
 case UINT32_C(0x002deaf8):goto L_002deaf8;
 case UINT32_C(0x002deafc):goto L_002deafc;
 case UINT32_C(0x002deb00):goto L_002deb00;
 case UINT32_C(0x002deb04):goto L_002deb04;
 case UINT32_C(0x002deb08):goto L_002deb08;
 case UINT32_C(0x002deb0c):goto L_002deb0c;
 case UINT32_C(0x002deb10):goto L_002deb10;
 case UINT32_C(0x002deb14):goto L_002deb14;
 case UINT32_C(0x002deb18):goto L_002deb18;
 case UINT32_C(0x002deb1c):goto L_002deb1c;
 case UINT32_C(0x002deb20):goto L_002deb20;
 case UINT32_C(0x002deb24):goto L_002deb24;
 case UINT32_C(0x002deb28):goto L_002deb28;
 case UINT32_C(0x002deb2c):goto L_002deb2c;
 case UINT32_C(0x002deb30):goto L_002deb30;
 case UINT32_C(0x002deb34):goto L_002deb34;
 case UINT32_C(0x002deb38):goto L_002deb38;
 case UINT32_C(0x002deb3c):goto L_002deb3c;
 case UINT32_C(0x002deb40):goto L_002deb40;
 case UINT32_C(0x002deb44):goto L_002deb44;
 case UINT32_C(0x002deb48):goto L_002deb48;
 case UINT32_C(0x002deb4c):goto L_002deb4c;
 case UINT32_C(0x002deb50):goto L_002deb50;
 case UINT32_C(0x002deb54):goto L_002deb54;
 case UINT32_C(0x002deb58):goto L_002deb58;
 case UINT32_C(0x002deb5c):goto L_002deb5c;
 case UINT32_C(0x002deb60):goto L_002deb60;
 case UINT32_C(0x002deb64):goto L_002deb64;
 case UINT32_C(0x002deb68):goto L_002deb68;
 case UINT32_C(0x002deb6c):goto L_002deb6c;
 case UINT32_C(0x002deb70):goto L_002deb70;
 case UINT32_C(0x002deb74):goto L_002deb74;
 case UINT32_C(0x00081fe0):goto L_00081fe0;
 case UINT32_C(0x00081fe4):goto L_00081fe4;
 case UINT32_C(0x00081fe8):goto L_00081fe8;
 case UINT32_C(0x00081fec):goto L_00081fec;
 case UINT32_C(0x00081ff0):goto L_00081ff0;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_800004c0:
 STEP(UINT32_C(0x800004c0)); /* 3c01b000 lui at,zero,0xb000 */
 set(m,1u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x800004c4));goto dispatch;
L_800004c4:
 STEP(UINT32_C(0x800004c4)); /* 3421e010 ori at,at,0xe010 */
 set(m,1u,lo(m,1u) | UINT64_C(0xe010));target=sx(UINT32_C(0x800004c8));goto dispatch;
L_800004c8:
 STEP(UINT32_C(0x800004c8)); /* 9c3a0000 lwu k0,0x0(at) */
 READ((uint32_t)lo(m,1u)+UINT32_C(0x00000000),&value32,4u);set(m,26u,(uint64_t)value32);target=sx(UINT32_C(0x800004cc));goto dispatch;
L_800004cc:
 STEP(UINT32_C(0x800004cc)); /* 0340082d daddu at,k0,zero */
 set(m,1u,lo(m,26u)+lo(m,0u));target=sx(UINT32_C(0x800004d0));goto dispatch;
L_800004d0:
 STEP(UINT32_C(0x800004d0)); /* 335affff andi k0,k0,0xffff */
 set(m,26u,lo(m,26u) & UINT64_C(0xffff));target=sx(UINT32_C(0x800004d4));goto dispatch;
L_800004d4:
 STEP(UINT32_C(0x800004d4)); /* 00010c02 srl at,at,16 */
 set(m,1u,sx((uint32_t)lo(m,1u)>>16u));target=sx(UINT32_C(0x800004d8));goto dispatch;
L_800004d8:
 STEP(UINT32_C(0x800004d8)); /* 34218000 ori at,at,0x8000 */
 set(m,1u,lo(m,1u) | UINT64_C(0x8000));target=sx(UINT32_C(0x800004dc));goto dispatch;
L_800004dc:
 STEP(UINT32_C(0x800004dc)); /* 0341d024 and k0,k0,at */
 set(m,26u,lo(m,26u)&lo(m,1u));target=sx(UINT32_C(0x800004e0));goto dispatch;
L_800004e0:
 STEP(UINT32_C(0x800004e0)); /* 33410080 andi at,k0,0x80 */
 set(m,1u,lo(m,26u) & UINT64_C(0x80));target=sx(UINT32_C(0x800004e4));goto dispatch;
L_800004e4:
 STEP(UINT32_C(0x800004e4)); /* 10200004 beq at,zero,800004f8 */
 {int taken=(lo(m,1u)==lo(m,0u));STEP(UINT32_C(0x800004e8));/* nop */target=sx(taken?UINT32_C(0x800004f8):UINT32_C(0x800004ec));goto dispatch;}
L_800004e8:
 STEP(UINT32_C(0x800004e8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800004ec));goto dispatch;
L_800004ec:
 STEP(UINT32_C(0x800004ec)); /* 3c018000 lui at,zero,0x8000 */
 set(m,1u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800004f0));goto dispatch;
L_800004f0:
 STEP(UINT32_C(0x800004f0)); /* 0800447c j 800111f0 */
 STEP(UINT32_C(0x800004f4));{uint32_t q[4];READ((uint32_t)lo(m,1u)+UINT32_C(0x000010e0),q,16u);memcpy(m->gpr[1],q,16u);}target=sx(UINT32_C(0x800111f0));goto dispatch;
L_800004f4:
 STEP(UINT32_C(0x800004f4)); /* 782110e0 lq at,0x10e0(at) */
 {uint32_t q[4];READ((uint32_t)lo(m,1u)+UINT32_C(0x000010e0),q,16u);memcpy(m->gpr[1],q,16u);}target=sx(UINT32_C(0x800004f8));goto dispatch;
L_800004f8:
 STEP(UINT32_C(0x800004f8)); /* 40016000 cop0 rs0 rtat rd12 fn0 */
 set(m,1u,sx(m->status));target=sx(UINT32_C(0x800004fc));goto dispatch;
L_800004fc:
 STEP(UINT32_C(0x800004fc)); /* 241dffe4 addiu sp,zero,-28 */
 set(m,29u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffe4)));target=sx(UINT32_C(0x80000500));goto dispatch;
L_80000500:
 STEP(UINT32_C(0x80000500)); /* 003d0824 and at,at,sp */
 set(m,1u,lo(m,1u)&lo(m,29u));target=sx(UINT32_C(0x80000504));goto dispatch;
L_80000504:
 STEP(UINT32_C(0x80000504)); /* 40816000 cop0 rs4 rtat rd12 fn0 */
 m->status=(uint32_t)lo(m,1u);target=sx(UINT32_C(0x80000508));goto dispatch;
L_80000508:
 STEP(UINT32_C(0x80000508)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x8000050c));goto dispatch;
L_8000050c:
 STEP(UINT32_C(0x8000050c)); /* 3c1d8001 lui sp,zero,0x8001 */
 set(m,29u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80000510));goto dispatch;
L_80000510:
 STEP(UINT32_C(0x80000510)); /* 27bd5c40 addiu sp,sp,23616 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00005c40)));target=sx(UINT32_C(0x80000514));goto dispatch;
L_80000514:
 STEP(UINT32_C(0x80000514)); /* 0340082d daddu at,k0,zero */
 set(m,1u,lo(m,26u)+lo(m,0u));target=sx(UINT32_C(0x80000518));goto dispatch;
L_80000518:
 STEP(UINT32_C(0x80000518)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x8000051c));goto dispatch;
L_8000051c:
 STEP(UINT32_C(0x8000051c)); /* 401a7000 cop0 rs0 rtk0 rd14 fn0 */
 set(m,26u,sx(m->epc));target=sx(UINT32_C(0x80000520));goto dispatch;
L_80000520:
 STEP(UINT32_C(0x80000520)); /* afba0000 sw k0,0x0(sp) */
 value32=(uint32_t)lo(m,26u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80000524));goto dispatch;
L_80000524:
 STEP(UINT32_C(0x80000524)); /* 0c0004c0 jal 80001300 */
 set(m,31u,UINT64_C(0x8000052c));STEP(UINT32_C(0x80000528));/* nop */target=sx(UINT32_C(0x80001300));goto dispatch;
L_80000528:
 STEP(UINT32_C(0x80000528)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000052c));goto dispatch;
L_8000052c:
 STEP(UINT32_C(0x8000052c)); /* 70201804 mmi 70201804 */
 {uint64_t input=lo(m,1u);uint32_t a=plzcw((uint32_t)input),b=plzcw((uint32_t)(input>>32));set(m,3u,(uint64_t)a|((uint64_t)b<<32));}target=sx(UINT32_C(0x80000530));goto dispatch;
L_80000530:
 STEP(UINT32_C(0x80000530)); /* 306300ff andi v1,v1,0xff */
 set(m,3u,lo(m,3u) & UINT64_C(0xff));target=sx(UINT32_C(0x80000534));goto dispatch;
L_80000534:
 STEP(UINT32_C(0x80000534)); /* 2402001e addiu v0,zero,30 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001e)));target=sx(UINT32_C(0x80000538));goto dispatch;
L_80000538:
 STEP(UINT32_C(0x80000538)); /* 00431023 subu v0,v0,v1 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x8000053c));goto dispatch;
L_8000053c:
 STEP(UINT32_C(0x8000053c)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80000540));goto dispatch;
L_80000540:
 STEP(UINT32_C(0x80000540)); /* 00431804 sllv v1,v0,v1 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<((uint32_t)lo(m,2u)&31u)));target=sx(UINT32_C(0x80000544));goto dispatch;
L_80000544:
 STEP(UINT32_C(0x80000544)); /* 3c01b000 lui at,zero,0xb000 */
 set(m,1u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80000548));goto dispatch;
L_80000548:
 STEP(UINT32_C(0x80000548)); /* 3421e010 ori at,at,0xe010 */
 set(m,1u,lo(m,1u) | UINT64_C(0xe010));target=sx(UINT32_C(0x8000054c));goto dispatch;
L_8000054c:
 STEP(UINT32_C(0x8000054c)); /* ac230000 sw v1,0x0(at) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80000550));goto dispatch;
L_80000550:
 STEP(UINT32_C(0x80000550)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80000554));goto dispatch;
L_80000554:
 STEP(UINT32_C(0x80000554)); /* af4025f4 sw zero,0x25f4(k0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000025f4),&value32,4u);target=sx(UINT32_C(0x80000558));goto dispatch;
L_80000558:
 STEP(UINT32_C(0x80000558)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000055c));goto dispatch;
L_8000055c:
 STEP(UINT32_C(0x8000055c)); /* 00021080 sll v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<2u));target=sx(UINT32_C(0x80000560));goto dispatch;
L_80000560:
 STEP(UINT32_C(0x80000560)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80000564));goto dispatch;
L_80000564:
 STEP(UINT32_C(0x80000564)); /* 00621821 addu v1,v1,v0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80000568));goto dispatch;
L_80000568:
 STEP(UINT32_C(0x80000568)); /* 8c632440 lw v1,0x2440(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00002440),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x8000056c));goto dispatch;
L_8000056c:
 STEP(UINT32_C(0x8000056c)); /* 0060f809 jalr ra,v1 */
 target=sx((uint32_t)lo(m,3u));set(m,31u,UINT64_C(0x80000574));STEP(UINT32_C(0x80000570));/* nop */goto dispatch;
L_80000570:
 STEP(UINT32_C(0x80000570)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80000574));goto dispatch;
L_80000574:
 STEP(UINT32_C(0x80000574)); /* 0c0004f0 jal 800013c0 */
 set(m,31u,UINT64_C(0x8000057c));STEP(UINT32_C(0x80000578));/* nop */target=sx(UINT32_C(0x800013c0));goto dispatch;
L_80000578:
 STEP(UINT32_C(0x80000578)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000057c));goto dispatch;
L_8000057c:
 STEP(UINT32_C(0x8000057c)); /* 8fba0000 lw k0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x80000580));goto dispatch;
L_80000580:
 STEP(UINT32_C(0x80000580)); /* 409a7000 cop0 rs4 rtk0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80000584));goto dispatch;
L_80000584:
 STEP(UINT32_C(0x80000584)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80000588));goto dispatch;
L_80000588:
 STEP(UINT32_C(0x80000588)); /* 3c1a8000 lui k0,zero,0x8000 */
 set(m,26u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x8000058c));goto dispatch;
L_8000058c:
 STEP(UINT32_C(0x8000058c)); /* 7b5d10c0 lq sp,0x10c0(k0) */
 {uint32_t q[4];READ((uint32_t)lo(m,26u)+UINT32_C(0x000010c0),q,16u);memcpy(m->gpr[29],q,16u);}target=sx(UINT32_C(0x80000590));goto dispatch;
L_80000590:
 STEP(UINT32_C(0x80000590)); /* 7b5f10d0 lq ra,0x10d0(k0) */
 {uint32_t q[4];READ((uint32_t)lo(m,26u)+UINT32_C(0x000010d0),q,16u);memcpy(m->gpr[31],q,16u);}target=sx(UINT32_C(0x80000594));goto dispatch;
L_80000594:
 STEP(UINT32_C(0x80000594)); /* 7b4110e0 lq at,0x10e0(k0) */
 {uint32_t q[4];READ((uint32_t)lo(m,26u)+UINT32_C(0x000010e0),q,16u);memcpy(m->gpr[1],q,16u);}target=sx(UINT32_C(0x80000598));goto dispatch;
L_80000598:
 STEP(UINT32_C(0x80000598)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000059c));goto dispatch;
L_8000059c:
 STEP(UINT32_C(0x8000059c)); /* 8f5a25f4 lw k0,0x25f4(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x000025f4),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x800005a0));goto dispatch;
L_800005a0:
 STEP(UINT32_C(0x800005a0)); /* 13400006 beq k0,zero,800005bc */
 {int taken=(lo(m,26u)==lo(m,0u));STEP(UINT32_C(0x800005a4));/* nop */target=sx(taken?UINT32_C(0x800005bc):UINT32_C(0x800005a8));goto dispatch;}
L_800005a4:
 STEP(UINT32_C(0x800005a4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800005a8));goto dispatch;
L_800005a8:
 STEP(UINT32_C(0x800005a8)); /* 3c1d8001 lui sp,zero,0x8001 */
 set(m,29u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800005ac));goto dispatch;
L_800005ac:
 STEP(UINT32_C(0x800005ac)); /* 27bd5c40 addiu sp,sp,23616 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00005c40)));target=sx(UINT32_C(0x800005b0));goto dispatch;
L_800005b0:
 STEP(UINT32_C(0x800005b0)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800005b4));goto dispatch;
L_800005b4:
 STEP(UINT32_C(0x800005b4)); /* 08000d8f j 8000363c */
 STEP(UINT32_C(0x800005b8));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000025f4),&value32,4u);target=sx(UINT32_C(0x8000363c));goto dispatch;
L_800005b8:
 STEP(UINT32_C(0x800005b8)); /* af4025f4 sw zero,0x25f4(k0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000025f4),&value32,4u);target=sx(UINT32_C(0x800005bc));goto dispatch;
L_800005bc:
 STEP(UINT32_C(0x800005bc)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x800005c0));goto dispatch;
L_800005c0:
 STEP(UINT32_C(0x800005c0)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x800005c4));goto dispatch;
L_800005c4:
 STEP(UINT32_C(0x800005c4)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x800005c8));goto dispatch;
L_800005c8:
 STEP(UINT32_C(0x800005c8)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x800005cc));goto dispatch;
L_800005cc:
 STEP(UINT32_C(0x800005cc)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80001798:
 STEP(UINT32_C(0x80001798)); /* 27bdff90 addiu sp,sp,-112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff90)));target=sx(UINT32_C(0x8000179c));goto dispatch;
L_8000179c:
 STEP(UINT32_C(0x8000179c)); /* 2402000c addiu v0,zero,12 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x800017a0));goto dispatch;
L_800017a0:
 STEP(UINT32_C(0x800017a0)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x800017a4));goto dispatch;
L_800017a4:
 STEP(UINT32_C(0x800017a4)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800017a8));goto dispatch;
L_800017a8:
 STEP(UINT32_C(0x800017a8)); /* 24635d18 addiu v1,v1,23832 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00005d18)));target=sx(UINT32_C(0x800017ac));goto dispatch;
L_800017ac:
 STEP(UINT32_C(0x800017ac)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x800017b0));goto dispatch;
L_800017b0:
 STEP(UINT32_C(0x800017b0)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x800017b4));goto dispatch;
L_800017b4:
 STEP(UINT32_C(0x800017b4)); /* 02621018 mult_rd v0,s3,v0 */
 {int64_t product;if(lo(m,19u)!=sx((uint32_t)lo(m,19u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,19u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=sx(UINT32_C(0x800017b8));goto dispatch;
L_800017b8:
 STEP(UINT32_C(0x800017b8)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x800017bc));goto dispatch;
L_800017bc:
 STEP(UINT32_C(0x800017bc)); /* ffbf0060 sd ra,0x60(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x800017c0));goto dispatch;
L_800017c0:
 STEP(UINT32_C(0x800017c0)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x800017c4));goto dispatch;
L_800017c4:
 STEP(UINT32_C(0x800017c4)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x800017c8));goto dispatch;
L_800017c8:
 STEP(UINT32_C(0x800017c8)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x800017cc));goto dispatch;
L_800017cc:
 STEP(UINT32_C(0x800017cc)); /* 00432021 addu a0,v0,v1 */
 set(m,4u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x800017d0));goto dispatch;
L_800017d0:
 STEP(UINT32_C(0x800017d0)); /* 3c108001 lui s0,zero,0x8001 */
 set(m,16u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800017d4));goto dispatch;
L_800017d4:
 STEP(UINT32_C(0x800017d4)); /* 02028021 addu s0,s0,v0 */
 set(m,16u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x800017d8));goto dispatch;
L_800017d8:
 STEP(UINT32_C(0x800017d8)); /* 8e105d14 lw s0,0x5d14(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00005d14),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x800017dc));goto dispatch;
L_800017dc:
 STEP(UINT32_C(0x800017dc)); /* 8c830000 lw v1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x800017e0));goto dispatch;
L_800017e0:
 STEP(UINT32_C(0x800017e0)); /* 18600022 blez v1,zero,8000186c */
 {int taken=((int64_t)lo(m,3u)<=0);STEP(UINT32_C(0x800017e4));set(m,18u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000186c):UINT32_C(0x800017e8));goto dispatch;}
L_800017e4:
 STEP(UINT32_C(0x800017e4)); /* 0000902d daddu s2,zero,zero */
 set(m,18u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x800017e8));goto dispatch;
L_800017e8:
 STEP(UINT32_C(0x800017e8)); /* 0080a02d daddu s4,a0,zero */
 set(m,20u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x800017ec));goto dispatch;
L_800017ec:
 STEP(UINT32_C(0x800017ec)); /* 24150002 addiu s5,zero,2 */
 set(m,21u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x800017f0));goto dispatch;
L_800017f0:
 STEP(UINT32_C(0x800017f0)); /* 8e020014 lw v0,0x14(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800017f4));goto dispatch;
L_800017f4:
 STEP(UINT32_C(0x800017f4)); /* 14550013 bne v0,s5,80001844 */
 {int taken=(lo(m,2u)!=lo(m,21u));STEP(UINT32_C(0x800017f8));/* nop */target=sx(taken?UINT32_C(0x80001844):UINT32_C(0x800017fc));goto dispatch;}
L_800017f8:
 STEP(UINT32_C(0x800017f8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800017fc));goto dispatch;
L_800017fc:
 STEP(UINT32_C(0x800017fc)); /* 0380882d daddu s1,gp,zero */
 set(m,17u,lo(m,28u)+lo(m,0u));target=sx(UINT32_C(0x80001800));goto dispatch;
L_80001800:
 STEP(UINT32_C(0x80001800)); /* 8e02000c lw v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80001804));goto dispatch;
L_80001804:
 STEP(UINT32_C(0x80001804)); /* 0040e02d daddu gp,v0,zero */
 set(m,28u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80001808));goto dispatch;
L_80001808:
 STEP(UINT32_C(0x80001808)); /* 40087000 cop0 rs0 rtt0 rd14 fn0 */
 set(m,8u,sx(m->epc));target=sx(UINT32_C(0x8000180c));goto dispatch;
L_8000180c:
 STEP(UINT32_C(0x8000180c)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80001810));goto dispatch;
L_80001810:
 STEP(UINT32_C(0x80001810)); /* 8c8424e4 lw a0,0x24e4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x000024e4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80001814));goto dispatch;
L_80001814:
 STEP(UINT32_C(0x80001814)); /* 0260302d daddu a2,s3,zero */
 set(m,6u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x80001818));goto dispatch;
L_80001818:
 STEP(UINT32_C(0x80001818)); /* 8e050008 lw a1,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000181c));goto dispatch;
L_8000181c:
 STEP(UINT32_C(0x8000181c)); /* 0c000a10 jal 80002840 */
 set(m,31u,UINT64_C(0x80001824));STEP(UINT32_C(0x80001820));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x80002840));goto dispatch;
L_80001820:
 STEP(UINT32_C(0x80001820)); /* 8e070010 lw a3,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x80001824));goto dispatch;
L_80001824:
 STEP(UINT32_C(0x80001824)); /* 04410004 regimm1 v0,80001838 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x80001828));/* nop */target=sx(taken?UINT32_C(0x80001838):UINT32_C(0x8000182c));goto dispatch;}
L_80001828:
 STEP(UINT32_C(0x80001828)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000182c));goto dispatch;
L_8000182c:
 STEP(UINT32_C(0x8000182c)); /* 0220e02d daddu gp,s1,zero */
 set(m,28u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x80001830));goto dispatch;
L_80001830:
 STEP(UINT32_C(0x80001830)); /* 10000017 beq zero,zero,80001890 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80001834));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80001890):UINT32_C(0x80001838));goto dispatch;}
L_80001834:
 STEP(UINT32_C(0x80001834)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80001838));goto dispatch;
L_80001838:
 STEP(UINT32_C(0x80001838)); /* 0220e02d daddu gp,s1,zero */
 set(m,28u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x8000183c));goto dispatch;
L_8000183c:
 STEP(UINT32_C(0x8000183c)); /* 10000007 beq zero,zero,8000185c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80001840));READ((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x8000185c):UINT32_C(0x80001844));goto dispatch;}
L_80001840:
 STEP(UINT32_C(0x80001840)); /* 8e820000 lw v0,0x0(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80001844));goto dispatch;
L_80001844:
 STEP(UINT32_C(0x80001844)); /* 54400005 bnel v0,zero,8000185c */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x80001848));READ((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000185c));}else target=sx(UINT32_C(0x8000184c));goto dispatch;
L_80001848:
 STEP(UINT32_C(0x80001848)); /* 8e820000 lw v0,0x0(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000184c));goto dispatch;
L_8000184c:
 STEP(UINT32_C(0x8000184c)); /* 8e020008 lw v0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80001850));goto dispatch;
L_80001850:
 STEP(UINT32_C(0x80001850)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x80001858));STEP(UINT32_C(0x80001854));set(m,4u,lo(m,19u)+lo(m,0u));goto dispatch;
L_80001854:
 STEP(UINT32_C(0x80001854)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x80001858));goto dispatch;
L_80001858:
 STEP(UINT32_C(0x80001858)); /* 8e820000 lw v0,0x0(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000185c));goto dispatch;
L_8000185c:
 STEP(UINT32_C(0x8000185c)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80001860));goto dispatch;
L_80001860:
 STEP(UINT32_C(0x80001860)); /* 0242102a slt v0,s2,v0 */
 set(m,2u,((int64_t)lo(m,18u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x80001864));goto dispatch;
L_80001864:
 STEP(UINT32_C(0x80001864)); /* 1440ffe2 bne v0,zero,800017f0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80001868));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x800017f0):UINT32_C(0x8000186c));goto dispatch;}
L_80001868:
 STEP(UINT32_C(0x80001868)); /* 8e100004 lw s0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x8000186c));goto dispatch;
L_8000186c:
 STEP(UINT32_C(0x8000186c)); /* 16400008 bne s2,zero,80001890 */
 {int taken=(lo(m,18u)!=lo(m,0u));STEP(UINT32_C(0x80001870));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80001890):UINT32_C(0x80001874));goto dispatch;}
L_80001870:
 STEP(UINT32_C(0x80001870)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80001874));goto dispatch;
L_80001874:
 STEP(UINT32_C(0x80001874)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80001878));goto dispatch;
L_80001878:
 STEP(UINT32_C(0x80001878)); /* 24842b28 addiu a0,a0,11048 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00002b28)));target=sx(UINT32_C(0x8000187c));goto dispatch;
L_8000187c:
 STEP(UINT32_C(0x8000187c)); /* 0c001cd0 jal 80007340 */
 set(m,31u,UINT64_C(0x80001884));STEP(UINT32_C(0x80001880));set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x80007340));goto dispatch;
L_80001880:
 STEP(UINT32_C(0x80001880)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x80001884));goto dispatch;
L_80001884:
 STEP(UINT32_C(0x80001884)); /* 0c000370 jal 80000dc0 */
 set(m,31u,UINT64_C(0x8000188c));STEP(UINT32_C(0x80001888));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80000dc0));goto dispatch;
L_80001888:
 STEP(UINT32_C(0x80001888)); /* 24040001 addiu a0,zero,1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000188c));goto dispatch;
L_8000188c:
 STEP(UINT32_C(0x8000188c)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80001890));goto dispatch;
L_80001890:
 STEP(UINT32_C(0x80001890)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x80001894));goto dispatch;
L_80001894:
 STEP(UINT32_C(0x80001894)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x80001898));goto dispatch;
L_80001898:
 STEP(UINT32_C(0x80001898)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x8000189c));goto dispatch;
L_8000189c:
 STEP(UINT32_C(0x8000189c)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x800018a0));goto dispatch;
L_800018a0:
 STEP(UINT32_C(0x800018a0)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x800018a4));goto dispatch;
L_800018a4:
 STEP(UINT32_C(0x800018a4)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x800018a8));goto dispatch;
L_800018a8:
 STEP(UINT32_C(0x800018a8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800018ac));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));goto dispatch;
L_800018ac:
 STEP(UINT32_C(0x800018ac)); /* 27bd0070 addiu sp,sp,112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x800018b0));goto dispatch;
L_80002840:
 STEP(UINT32_C(0x80002840)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80002844));goto dispatch;
L_80002844:
 STEP(UINT32_C(0x80002844)); /* af5f6fc0 sw ra,0x6fc0(k0) */
 value32=(uint32_t)lo(m,31u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00006fc0),&value32,4u);target=sx(UINT32_C(0x80002848));goto dispatch;
L_80002848:
 STEP(UINT32_C(0x80002848)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000284c));goto dispatch;
L_8000284c:
 STEP(UINT32_C(0x8000284c)); /* af5d6fd0 sw sp,0x6fd0(k0) */
 value32=(uint32_t)lo(m,29u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00006fd0),&value32,4u);target=sx(UINT32_C(0x80002850));goto dispatch;
L_80002850:
 STEP(UINT32_C(0x80002850)); /* 40847000 cop0 rs4 rta0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,4u);target=sx(UINT32_C(0x80002854));goto dispatch;
L_80002854:
 STEP(UINT32_C(0x80002854)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80002858));goto dispatch;
L_80002858:
 STEP(UINT32_C(0x80002858)); /* 00a0182d daddu v1,a1,zero */
 set(m,3u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x8000285c));goto dispatch;
L_8000285c:
 STEP(UINT32_C(0x8000285c)); /* 00c0202d daddu a0,a2,zero */
 set(m,4u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x80002860));goto dispatch;
L_80002860:
 STEP(UINT32_C(0x80002860)); /* 00e0282d daddu a1,a3,zero */
 set(m,5u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x80002864));goto dispatch;
L_80002864:
 STEP(UINT32_C(0x80002864)); /* 0100302d daddu a2,t0,zero */
 set(m,6u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x80002868));goto dispatch;
L_80002868:
 STEP(UINT32_C(0x80002868)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x8000286c));goto dispatch;
L_8000286c:
 STEP(UINT32_C(0x8000286c)); /* 375a0012 ori k0,k0,0x12 */
 set(m,26u,lo(m,26u) | UINT64_C(0x12));target=sx(UINT32_C(0x80002870));goto dispatch;
L_80002870:
 STEP(UINT32_C(0x80002870)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80002874));goto dispatch;
L_80002874:
 STEP(UINT32_C(0x80002874)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80002878));goto dispatch;
L_80002878:
 STEP(UINT32_C(0x80002878)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_8000287c:
 STEP(UINT32_C(0x8000287c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80002880));goto dispatch;
L_80002880:
 STEP(UINT32_C(0x80002880)); /* 40016000 cop0 rs0 rtat rd12 fn0 */
 set(m,1u,sx(m->status));target=sx(UINT32_C(0x80002884));goto dispatch;
L_80002884:
 STEP(UINT32_C(0x80002884)); /* 241affe4 addiu k0,zero,-28 */
 set(m,26u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffe4)));target=sx(UINT32_C(0x80002888));goto dispatch;
L_80002888:
 STEP(UINT32_C(0x80002888)); /* 003a0824 and at,at,k0 */
 set(m,1u,lo(m,1u)&lo(m,26u));target=sx(UINT32_C(0x8000288c));goto dispatch;
L_8000288c:
 STEP(UINT32_C(0x8000288c)); /* 40816000 cop0 rs4 rtat rd12 fn0 */
 m->status=(uint32_t)lo(m,1u);target=sx(UINT32_C(0x80002890));goto dispatch;
L_80002890:
 STEP(UINT32_C(0x80002890)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80002894));goto dispatch;
L_80002894:
 STEP(UINT32_C(0x80002894)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80002898));goto dispatch;
L_80002898:
 STEP(UINT32_C(0x80002898)); /* 8f5f6fc0 lw ra,0x6fc0(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x00006fc0),&value32,4u);set(m,31u,sx(value32));target=sx(UINT32_C(0x8000289c));goto dispatch;
L_8000289c:
 STEP(UINT32_C(0x8000289c)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800028a0));goto dispatch;
L_800028a0:
 STEP(UINT32_C(0x800028a0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800028a4));READ((uint32_t)lo(m,26u)+UINT32_C(0x00006fd0),&value32,4u);set(m,29u,sx(value32));goto dispatch;
L_800028a4:
 STEP(UINT32_C(0x800028a4)); /* 8f5d6fd0 lw sp,0x6fd0(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x00006fd0),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x800028a8));goto dispatch;
L_002de2f0:
 STEP(UINT32_C(0x002de2f0)); /* 00c0102d daddu v0,a2,zero */
 set(m,2u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002de2f4));goto dispatch;
L_002de2f4:
 STEP(UINT32_C(0x002de2f4)); /* 00e0182d daddu v1,a3,zero */
 set(m,3u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002de2f8));goto dispatch;
L_002de2f8:
 STEP(UINT32_C(0x002de2f8)); /* 0100582d daddu t3,t0,zero */
 set(m,11u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002de2fc));goto dispatch;
L_002de2fc:
 STEP(UINT32_C(0x002de2fc)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002de300));goto dispatch;
L_002de300:
 STEP(UINT32_C(0x002de300)); /* 0120502d daddu t2,t1,zero */
 set(m,10u,lo(m,9u)+lo(m,0u));target=sx(UINT32_C(0x002de304));goto dispatch;
L_002de304:
 STEP(UINT32_C(0x002de304)); /* 00a0302d daddu a2,a1,zero */
 set(m,6u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002de308));goto dispatch;
L_002de308:
 STEP(UINT32_C(0x002de308)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002de30c));goto dispatch;
L_002de30c:
 STEP(UINT32_C(0x002de30c)); /* 0040382d daddu a3,v0,zero */
 set(m,7u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002de310));goto dispatch;
L_002de310:
 STEP(UINT32_C(0x002de310)); /* 0060402d daddu t0,v1,zero */
 set(m,8u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002de314));goto dispatch;
L_002de314:
 STEP(UINT32_C(0x002de314)); /* 0160482d daddu t1,t3,zero */
 set(m,9u,lo(m,11u)+lo(m,0u));target=sx(UINT32_C(0x002de318));goto dispatch;
L_002de318:
 STEP(UINT32_C(0x002de318)); /* 0c0b785e jal 002de178 */
 set(m,31u,UINT64_C(0x002de320));STEP(UINT32_C(0x002de31c));set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de178));goto dispatch;
L_002de31c:
 STEP(UINT32_C(0x002de31c)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de320));goto dispatch;
L_002de320:
 STEP(UINT32_C(0x002de320)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de324));goto dispatch;
L_002de324:
 STEP(UINT32_C(0x002de324)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de328));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002de328:
 STEP(UINT32_C(0x002de328)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002de32c));goto dispatch;
L_002de32c:
 STEP(UINT32_C(0x002de32c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de330));goto dispatch;
L_002dea78:
 STEP(UINT32_C(0x002dea78)); /* 8ca50028 lw a1,0x28(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000028),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002dea7c));goto dispatch;
L_002dea7c:
 STEP(UINT32_C(0x002dea7c)); /* 10a0000f beq a1,zero,002deabc */
 {int taken=(lo(m,5u)==lo(m,0u));STEP(UINT32_C(0x002dea80));/* nop */target=sx(taken?UINT32_C(0x002deabc):UINT32_C(0x002dea84));goto dispatch;}
L_002dea80:
 STEP(UINT32_C(0x002dea80)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dea84));goto dispatch;
L_002dea84:
 STEP(UINT32_C(0x002dea84)); /* 8ca30008 lw v1,0x8(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dea88));goto dispatch;
L_002dea88:
 STEP(UINT32_C(0x002dea88)); /* 5060000a beql v1,zero,002deab4 */
 if(lo(m,3u)==lo(m,0u)){STEP(UINT32_C(0x002dea8c));READ((uint32_t)lo(m,5u)+UINT32_C(0x00000014),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002deab4));}else target=sx(UINT32_C(0x002dea90));goto dispatch;
L_002dea8c:
 STEP(UINT32_C(0x002dea8c)); /* 8ca50014 lw a1,0x14(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000014),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002dea90));goto dispatch;
L_002dea90:
 STEP(UINT32_C(0x002dea90)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dea94));goto dispatch;
L_002dea94:
 STEP(UINT32_C(0x002dea94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dea98));goto dispatch;
L_002dea98:
 STEP(UINT32_C(0x002dea98)); /* 54440003 bnel v0,a0,002deaa8 */
 if(lo(m,2u)!=lo(m,4u)){STEP(UINT32_C(0x002dea9c));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000038),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002deaa8));}else target=sx(UINT32_C(0x002deaa0));goto dispatch;
L_002dea9c:
 STEP(UINT32_C(0x002dea9c)); /* 8c630038 lw v1,0x38(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000038),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002deaa0));goto dispatch;
L_002deaa0:
 STEP(UINT32_C(0x002deaa0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002deaa4));set(m,2u,lo(m,3u)+lo(m,0u));goto dispatch;
L_002deaa4:
 STEP(UINT32_C(0x002deaa4)); /* 0060102d daddu v0,v1,zero */
 set(m,2u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002deaa8));goto dispatch;
L_002deaa8:
 STEP(UINT32_C(0x002deaa8)); /* 5460fffb bnel v1,zero,002dea98 */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x002deaac));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dea98));}else target=sx(UINT32_C(0x002deab0));goto dispatch;
L_002deaac:
 STEP(UINT32_C(0x002deaac)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002deab0));goto dispatch;
L_002deab0:
 STEP(UINT32_C(0x002deab0)); /* 8ca50014 lw a1,0x14(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000014),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002deab4));goto dispatch;
L_002deab4:
 STEP(UINT32_C(0x002deab4)); /* 54a0fff4 bnel a1,zero,002dea88 */
 if(lo(m,5u)!=lo(m,0u)){STEP(UINT32_C(0x002deab8));READ((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dea88));}else target=sx(UINT32_C(0x002deabc));goto dispatch;
L_002deab8:
 STEP(UINT32_C(0x002deab8)); /* 8ca30008 lw v1,0x8(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002deabc));goto dispatch;
L_002deabc:
 STEP(UINT32_C(0x002deabc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002deac0));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_002deac0:
 STEP(UINT32_C(0x002deac0)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002deac4));goto dispatch;
L_002deac4:
 STEP(UINT32_C(0x002deac4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002deac8));goto dispatch;
L_002deac8:
 STEP(UINT32_C(0x002deac8)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002deacc));goto dispatch;
L_002deacc:
 STEP(UINT32_C(0x002deacc)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dead0));goto dispatch;
L_002dead0:
 STEP(UINT32_C(0x002dead0)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dead4));goto dispatch;
L_002dead4:
 STEP(UINT32_C(0x002dead4)); /* 00a0882d daddu s1,a1,zero */
 set(m,17u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002dead8));goto dispatch;
L_002dead8:
 STEP(UINT32_C(0x002dead8)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002deadc));goto dispatch;
L_002deadc:
 STEP(UINT32_C(0x002deadc)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002deae0));goto dispatch;
L_002deae0:
 STEP(UINT32_C(0x002deae0)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002deae4));goto dispatch;
L_002deae4:
 STEP(UINT32_C(0x002deae4)); /* 0c0b79e6 jal 002de798 */
 set(m,31u,UINT64_C(0x002deaec));STEP(UINT32_C(0x002deae8));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002de798));goto dispatch;
L_002deae8:
 STEP(UINT32_C(0x002deae8)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002deaec));goto dispatch;
L_002deaec:
 STEP(UINT32_C(0x002deaec)); /* 0040902d daddu s2,v0,zero */
 set(m,18u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002deaf0));goto dispatch;
L_002deaf0:
 STEP(UINT32_C(0x002deaf0)); /* 8e04001c lw a0,0x1c(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002deaf4));goto dispatch;
L_002deaf4:
 STEP(UINT32_C(0x002deaf4)); /* 8e030014 lw v1,0x14(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002deaf8));goto dispatch;
L_002deaf8:
 STEP(UINT32_C(0x002deaf8)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002deafc));goto dispatch;
L_002deafc:
 STEP(UINT32_C(0x002deafc)); /* 34420009 ori v0,v0,0x9 */
 set(m,2u,lo(m,2u) | UINT64_C(0x9));target=sx(UINT32_C(0x002deb00));goto dispatch;
L_002deb00:
 STEP(UINT32_C(0x002deb00)); /* ae44001c sw a0,0x1c(s2) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002deb04));goto dispatch;
L_002deb04:
 STEP(UINT32_C(0x002deb04)); /* ae430014 sw v1,0x14(s2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002deb08));goto dispatch;
L_002deb08:
 STEP(UINT32_C(0x002deb08)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002deb0c));goto dispatch;
L_002deb0c:
 STEP(UINT32_C(0x002deb0c)); /* ae420020 sw v0,0x20(s2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002deb10));goto dispatch;
L_002deb10:
 STEP(UINT32_C(0x002deb10)); /* 0c0b7a9e jal 002dea78 */
 set(m,31u,UINT64_C(0x002deb18));STEP(UINT32_C(0x002deb14));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dea78));goto dispatch;
L_002deb14:
 STEP(UINT32_C(0x002deb14)); /* 8e040020 lw a0,0x20(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002deb18));goto dispatch;
L_002deb18:
 STEP(UINT32_C(0x002deb18)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002deb1c));goto dispatch;
L_002deb1c:
 STEP(UINT32_C(0x002deb1c)); /* 54600005 bnel v1,zero,002deb34 */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x002deb20));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002deb34));}else target=sx(UINT32_C(0x002deb24));goto dispatch;
L_002deb20:
 STEP(UINT32_C(0x002deb20)); /* ae430024 sw v1,0x24(s2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002deb24));goto dispatch;
L_002deb24:
 STEP(UINT32_C(0x002deb24)); /* ae400024 sw zero,0x24(s2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002deb28));goto dispatch;
L_002deb28:
 STEP(UINT32_C(0x002deb28)); /* ae400028 sw zero,0x28(s2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x002deb2c));goto dispatch;
L_002deb2c:
 STEP(UINT32_C(0x002deb2c)); /* 10000005 beq zero,zero,002deb44 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002deb30));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x0000002c),&value32,4u);target=sx(taken?UINT32_C(0x002deb44):UINT32_C(0x002deb34));goto dispatch;}
L_002deb30:
 STEP(UINT32_C(0x002deb30)); /* ae40002c sw zero,0x2c(s2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x002deb34));goto dispatch;
L_002deb34:
 STEP(UINT32_C(0x002deb34)); /* 8c620008 lw v0,0x8(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002deb38));goto dispatch;
L_002deb38:
 STEP(UINT32_C(0x002deb38)); /* ae420028 sw v0,0x28(s2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x002deb3c));goto dispatch;
L_002deb3c:
 STEP(UINT32_C(0x002deb3c)); /* 8c630014 lw v1,0x14(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002deb40));goto dispatch;
L_002deb40:
 STEP(UINT32_C(0x002deb40)); /* ae43002c sw v1,0x2c(s2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x002deb44));goto dispatch;
L_002deb44:
 STEP(UINT32_C(0x002deb44)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002deb48));goto dispatch;
L_002deb48:
 STEP(UINT32_C(0x002deb48)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002deb4c));goto dispatch;
L_002deb4c:
 STEP(UINT32_C(0x002deb4c)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002deb50));goto dispatch;
L_002deb50:
 STEP(UINT32_C(0x002deb50)); /* 34840008 ori a0,a0,0x8 */
 set(m,4u,lo(m,4u) | UINT64_C(0x8));target=sx(UINT32_C(0x002deb54));goto dispatch;
L_002deb54:
 STEP(UINT32_C(0x002deb54)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002deb58));goto dispatch;
L_002deb58:
 STEP(UINT32_C(0x002deb58)); /* 24060040 addiu a2,zero,64 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002deb5c));goto dispatch;
L_002deb5c:
 STEP(UINT32_C(0x002deb5c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002deb60));goto dispatch;
L_002deb60:
 STEP(UINT32_C(0x002deb60)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002deb64));goto dispatch;
L_002deb64:
 STEP(UINT32_C(0x002deb64)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002deb68));goto dispatch;
L_002deb68:
 STEP(UINT32_C(0x002deb68)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002deb6c));goto dispatch;
L_002deb6c:
 STEP(UINT32_C(0x002deb6c)); /* 0000482d daddu t1,zero,zero */
 set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002deb70));goto dispatch;
L_002deb70:
 STEP(UINT32_C(0x002deb70)); /* 080b78bc j 002de2f0 */
 STEP(UINT32_C(0x002deb74));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de2f0));goto dispatch;
L_002deb74:
 STEP(UINT32_C(0x002deb74)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002deb78));goto dispatch;
L_00081fe0:
 STEP(UINT32_C(0x00081fe0)); /* 3c1d0008 lui sp,zero,0x8 */
 set(m,29u,sx(UINT32_C(0x00080000)));target=sx(UINT32_C(0x00081fe4));goto dispatch;
L_00081fe4:
 STEP(UINT32_C(0x00081fe4)); /* 0060f809 jalr ra,v1 */
 target=sx((uint32_t)lo(m,3u));set(m,31u,UINT64_C(0x00081fec));STEP(UINT32_C(0x00081fe8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00001fc0)));goto dispatch;
L_00081fe8:
 STEP(UINT32_C(0x00081fe8)); /* 27bd1fc0 addiu sp,sp,8128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00001fc0)));target=sx(UINT32_C(0x00081fec));goto dispatch;
L_00081fec:
 STEP(UINT32_C(0x00081fec)); /* 2403fffb addiu v1,zero,-5 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffb)));target=sx(UINT32_C(0x00081ff0));goto dispatch;
L_00081ff0:
 m->pc=UINT32_C(0x00081ff0); /* Unexecuted SYS; router owns exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
#undef STEP
#undef READ
#undef WRITE
}

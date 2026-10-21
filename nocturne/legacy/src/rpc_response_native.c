#include "rpc_response_native.h"
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
uint32_t nocturneRpcResponseResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002de798):goto L_002de798;
 case UINT32_C(0x002de79c):goto L_002de79c;
 case UINT32_C(0x002de7a0):goto L_002de7a0;
 case UINT32_C(0x002de7a4):goto L_002de7a4;
 case UINT32_C(0x002de7a8):goto L_002de7a8;
 case UINT32_C(0x002de7ac):goto L_002de7ac;
 case UINT32_C(0x002de7b0):goto L_002de7b0;
 case UINT32_C(0x002de7b4):goto L_002de7b4;
 case UINT32_C(0x002de7b8):goto L_002de7b8;
 case UINT32_C(0x002de7bc):goto L_002de7bc;
 case UINT32_C(0x002de7c0):goto L_002de7c0;
 case UINT32_C(0x002de7c4):goto L_002de7c4;
 case UINT32_C(0x002de7c8):goto L_002de7c8;
 case UINT32_C(0x002de7cc):goto L_002de7cc;
 case UINT32_C(0x002de7d0):goto L_002de7d0;
 case UINT32_C(0x002de7d4):goto L_002de7d4;
 case UINT32_C(0x002de7d8):goto L_002de7d8;
 case UINT32_C(0x002de7dc):goto L_002de7dc;
 case UINT32_C(0x002de7e0):goto L_002de7e0;
 case UINT32_C(0x002de7e4):goto L_002de7e4;
 case UINT32_C(0x002de7e8):goto L_002de7e8;
 case UINT32_C(0x002de7ec):goto L_002de7ec;
 case UINT32_C(0x002de7f0):goto L_002de7f0;
 case UINT32_C(0x002de7f4):goto L_002de7f4;
 case UINT32_C(0x002de7f8):goto L_002de7f8;
 case UINT32_C(0x002de7fc):goto L_002de7fc;
 case UINT32_C(0x002de800):goto L_002de800;
 case UINT32_C(0x002de804):goto L_002de804;
 case UINT32_C(0x002de808):goto L_002de808;
 case UINT32_C(0x002de80c):goto L_002de80c;
 case UINT32_C(0x002de810):goto L_002de810;
 case UINT32_C(0x002de814):goto L_002de814;
 case UINT32_C(0x002de818):goto L_002de818;
 case UINT32_C(0x002de81c):goto L_002de81c;
 case UINT32_C(0x002de820):goto L_002de820;
 case UINT32_C(0x002de824):goto L_002de824;
 case UINT32_C(0x002de828):goto L_002de828;
 case UINT32_C(0x002de82c):goto L_002de82c;
 case UINT32_C(0x002de830):goto L_002de830;
 case UINT32_C(0x002de834):goto L_002de834;
 case UINT32_C(0x002de838):goto L_002de838;
 case UINT32_C(0x002de83c):goto L_002de83c;
 case UINT32_C(0x002de840):goto L_002de840;
 case UINT32_C(0x002de844):goto L_002de844;
 case UINT32_C(0x002de848):goto L_002de848;
 case UINT32_C(0x002de84c):goto L_002de84c;
 case UINT32_C(0x002de850):goto L_002de850;
 case UINT32_C(0x002de854):goto L_002de854;
 case UINT32_C(0x002de858):goto L_002de858;
 case UINT32_C(0x002de85c):goto L_002de85c;
 case UINT32_C(0x002de860):goto L_002de860;
 case UINT32_C(0x002de864):goto L_002de864;
 case UINT32_C(0x002de868):goto L_002de868;
 case UINT32_C(0x002de86c):goto L_002de86c;
 case UINT32_C(0x002de870):goto L_002de870;
 case UINT32_C(0x002de874):goto L_002de874;
 case UINT32_C(0x002de878):goto L_002de878;
 case UINT32_C(0x002de87c):goto L_002de87c;
 case UINT32_C(0x002de880):goto L_002de880;
 case UINT32_C(0x002de884):goto L_002de884;
 case UINT32_C(0x002de888):goto L_002de888;
 case UINT32_C(0x002de88c):goto L_002de88c;
 case UINT32_C(0x002de890):goto L_002de890;
 case UINT32_C(0x002de894):goto L_002de894;
 case UINT32_C(0x002de898):goto L_002de898;
 case UINT32_C(0x002de89c):goto L_002de89c;
 case UINT32_C(0x002de8a0):goto L_002de8a0;
 case UINT32_C(0x002de8a4):goto L_002de8a4;
 case UINT32_C(0x002de8a8):goto L_002de8a8;
 case UINT32_C(0x002de8ac):goto L_002de8ac;
 case UINT32_C(0x002de8b0):goto L_002de8b0;
 case UINT32_C(0x002de8b4):goto L_002de8b4;
 case UINT32_C(0x002de8b8):goto L_002de8b8;
 case UINT32_C(0x002dbed0):goto L_002dbed0;
 case UINT32_C(0x002dbed4):goto L_002dbed4;
 case UINT32_C(0x002dbed8):goto L_002dbed8;
 case UINT32_C(0x002dbedc):goto L_002dbedc;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002de798:
 STEP(UINT32_C(0x002de798)); /* 8c850024 lw a1,0x24(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002de79c));goto dispatch;
L_002de79c:
 STEP(UINT32_C(0x002de79c)); /* 8c830018 lw v1,0x18(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de7a0));goto dispatch;
L_002de7a0:
 STEP(UINT32_C(0x002de7a0)); /* 00a3001a UNKNOWN 00a3001a */
 {int32_t numerator=(int32_t)lo(m,5u),denominator=(int32_t)lo(m,3u);uint32_t q,r;if(!denominator){q=numerator<0?1u:UINT32_MAX;r=(uint32_t)numerator;}else if(numerator==INT32_MIN&&denominator==-1){q=0x80000000u;r=0;}else{q=(uint32_t)(numerator/denominator);r=(uint32_t)(numerator%denominator);}m->lo=sx(q);m->hi=sx(r);}target=sx(UINT32_C(0x002de7a4));goto dispatch;
L_002de7a4:
 STEP(UINT32_C(0x002de7a4)); /* 50600001 beql v1,zero,002de7ac */
 if(lo(m,3u)==lo(m,0u)){STEP(UINT32_C(0x002de7a8));return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc)); /* BREAK7 exception owner remains required. */}else target=sx(UINT32_C(0x002de7ac));goto dispatch;
L_002de7a8:
 STEP(UINT32_C(0x002de7a8)); /* 000001cd UNKNOWN 000001cd */
 return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc)); /* BREAK7 exception owner remains required. */goto dispatch;
L_002de7ac:
 STEP(UINT32_C(0x002de7ac)); /* 8c850014 lw a1,0x14(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002de7b0));goto dispatch;
L_002de7b0:
 STEP(UINT32_C(0x002de7b0)); /* 00001010 mfhi v0 */
 set(m,2u,m->hi);target=sx(UINT32_C(0x002de7b4));goto dispatch;
L_002de7b4:
 STEP(UINT32_C(0x002de7b4)); /* 24430001 addiu v1,v0,1 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de7b8));goto dispatch;
L_002de7b8:
 STEP(UINT32_C(0x002de7b8)); /* 00021180 sll v0,v0,6 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<6u));target=sx(UINT32_C(0x002de7bc));goto dispatch;
L_002de7bc:
 STEP(UINT32_C(0x002de7bc)); /* ac830024 sw v1,0x24(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002de7c0));goto dispatch;
L_002de7c0:
 STEP(UINT32_C(0x002de7c0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de7c4));set(m,2u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,2u)));goto dispatch;
L_002de7c4:
 STEP(UINT32_C(0x002de7c4)); /* 00a21021 addu v0,a1,v0 */
 set(m,2u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002de7c8));goto dispatch;
L_002de7c8:
 STEP(UINT32_C(0x002de7c8)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002de7cc));goto dispatch;
L_002de7cc:
 STEP(UINT32_C(0x002de7cc)); /* 04a00005 regimm0 a1,002de7e4 */
 {int taken=((int64_t)lo(m,5u)<0);STEP(UINT32_C(0x002de7d0));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x002de7e4):UINT32_C(0x002de7d4));goto dispatch;}
L_002de7d0:
 STEP(UINT32_C(0x002de7d0)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002de7d4));goto dispatch;
L_002de7d4:
 STEP(UINT32_C(0x002de7d4)); /* 8c820020 lw v0,0x20(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000020),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de7d8));goto dispatch;
L_002de7d8:
 STEP(UINT32_C(0x002de7d8)); /* 00a2102a slt v0,a1,v0 */
 set(m,2u,((int64_t)lo(m,5u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x002de7dc));goto dispatch;
L_002de7dc:
 STEP(UINT32_C(0x002de7dc)); /* 54400005 bnel v0,zero,002de7f4 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002de7e0));READ((uint32_t)lo(m,4u)+UINT32_C(0x0000001c),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de7f4));}else target=sx(UINT32_C(0x002de7e4));goto dispatch;
L_002de7e0:
 STEP(UINT32_C(0x002de7e0)); /* 8c83001c lw v1,0x1c(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x0000001c),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de7e4));goto dispatch;
L_002de7e4:
 STEP(UINT32_C(0x002de7e4)); /* 0c0b79e6 jal 002de798 */
 set(m,31u,UINT64_C(0x002de7ec));STEP(UINT32_C(0x002de7e8));/* nop */target=sx(UINT32_C(0x002de798));goto dispatch;
L_002de7e8:
 STEP(UINT32_C(0x002de7e8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de7ec));goto dispatch;
L_002de7ec:
 STEP(UINT32_C(0x002de7ec)); /* 10000004 beq zero,zero,002de800 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de7f0));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002de800):UINT32_C(0x002de7f4));goto dispatch;}
L_002de7f0:
 STEP(UINT32_C(0x002de7f0)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de7f4));goto dispatch;
L_002de7f4:
 STEP(UINT32_C(0x002de7f4)); /* 00051180 sll v0,a1,6 */
 set(m,2u,sx((uint32_t)lo(m,5u)<<6u));target=sx(UINT32_C(0x002de7f8));goto dispatch;
L_002de7f8:
 STEP(UINT32_C(0x002de7f8)); /* 00621021 addu v0,v1,v0 */
 set(m,2u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002de7fc));goto dispatch;
L_002de7fc:
 STEP(UINT32_C(0x002de7fc)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de800));goto dispatch;
L_002de800:
 STEP(UINT32_C(0x002de800)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de804));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002de804:
 STEP(UINT32_C(0x002de804)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002de808));goto dispatch;
L_002de808:
 STEP(UINT32_C(0x002de808)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002de80c));goto dispatch;
L_002de80c:
 STEP(UINT32_C(0x002de80c)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de810));goto dispatch;
L_002de810:
 STEP(UINT32_C(0x002de810)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002de814));goto dispatch;
L_002de814:
 STEP(UINT32_C(0x002de814)); /* 3442000a ori v0,v0,0xa */
 set(m,2u,lo(m,2u) | UINT64_C(0xa));target=sx(UINT32_C(0x002de818));goto dispatch;
L_002de818:
 STEP(UINT32_C(0x002de818)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002de81c));goto dispatch;
L_002de81c:
 STEP(UINT32_C(0x002de81c)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002de820));goto dispatch;
L_002de820:
 STEP(UINT32_C(0x002de820)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002de824));goto dispatch;
L_002de824:
 STEP(UINT32_C(0x002de824)); /* 8e230020 lw v1,0x20(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000020),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de828));goto dispatch;
L_002de828:
 STEP(UINT32_C(0x002de828)); /* 10620009 beq v1,v0,002de850 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002de82c));set(m,2u,lo(m,2u)<lo(m,3u));target=sx(taken?UINT32_C(0x002de850):UINT32_C(0x002de830));goto dispatch;}
L_002de82c:
 STEP(UINT32_C(0x002de82c)); /* 0043102b sltu v0,v0,v1 */
 set(m,2u,lo(m,2u)<lo(m,3u));target=sx(UINT32_C(0x002de830));goto dispatch;
L_002de830:
 STEP(UINT32_C(0x002de830)); /* 54400015 bnel v0,zero,002de888 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002de834));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002de888));}else target=sx(UINT32_C(0x002de838));goto dispatch;
L_002de834:
 STEP(UINT32_C(0x002de834)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002de838));goto dispatch;
L_002de838:
 STEP(UINT32_C(0x002de838)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de83c));goto dispatch;
L_002de83c:
 STEP(UINT32_C(0x002de83c)); /* 34420009 ori v0,v0,0x9 */
 set(m,2u,lo(m,2u) | UINT64_C(0x9));target=sx(UINT32_C(0x002de840));goto dispatch;
L_002de840:
 STEP(UINT32_C(0x002de840)); /* 5062000b beql v1,v0,002de870 */
 if(lo(m,3u)==lo(m,2u)){STEP(UINT32_C(0x002de844));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de870));}else target=sx(UINT32_C(0x002de848));goto dispatch;
L_002de844:
 STEP(UINT32_C(0x002de844)); /* 8e220024 lw v0,0x24(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de848));goto dispatch;
L_002de848:
 STEP(UINT32_C(0x002de848)); /* 1000000f beq zero,zero,002de888 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de84c));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002de888):UINT32_C(0x002de850));goto dispatch;}
L_002de84c:
 STEP(UINT32_C(0x002de84c)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002de850));goto dispatch;
L_002de850:
 STEP(UINT32_C(0x002de850)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002de854));goto dispatch;
L_002de854:
 STEP(UINT32_C(0x002de854)); /* 8e02001c lw v0,0x1c(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de858));goto dispatch;
L_002de858:
 STEP(UINT32_C(0x002de858)); /* 5040000c beql v0,zero,002de88c */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002de85c));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de88c));}else target=sx(UINT32_C(0x002de860));goto dispatch;
L_002de85c:
 STEP(UINT32_C(0x002de85c)); /* 8e040008 lw a0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de860));goto dispatch;
L_002de860:
 STEP(UINT32_C(0x002de860)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002de868));STEP(UINT32_C(0x002de864));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);set(m,4u,sx(value32));goto dispatch;
L_002de864:
 STEP(UINT32_C(0x002de864)); /* 8e040020 lw a0,0x20(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de868));goto dispatch;
L_002de868:
 STEP(UINT32_C(0x002de868)); /* 10000007 beq zero,zero,002de888 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de86c));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002de888):UINT32_C(0x002de870));goto dispatch;}
L_002de86c:
 STEP(UINT32_C(0x002de86c)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002de870));goto dispatch;
L_002de870:
 STEP(UINT32_C(0x002de870)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002de874));goto dispatch;
L_002de874:
 STEP(UINT32_C(0x002de874)); /* ae020024 sw v0,0x24(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002de878));goto dispatch;
L_002de878:
 STEP(UINT32_C(0x002de878)); /* 8e230028 lw v1,0x28(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000028),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de87c));goto dispatch;
L_002de87c:
 STEP(UINT32_C(0x002de87c)); /* ae030014 sw v1,0x14(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002de880));goto dispatch;
L_002de880:
 STEP(UINT32_C(0x002de880)); /* 8e22002c lw v0,0x2c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000002c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de884));goto dispatch;
L_002de884:
 STEP(UINT32_C(0x002de884)); /* ae020018 sw v0,0x18(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002de888));goto dispatch;
L_002de888:
 STEP(UINT32_C(0x002de888)); /* 8e040008 lw a0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de88c));goto dispatch;
L_002de88c:
 STEP(UINT32_C(0x002de88c)); /* 04800003 regimm0 a0,002de89c */
 {int taken=((int64_t)lo(m,4u)<0);STEP(UINT32_C(0x002de890));/* nop */target=sx(taken?UINT32_C(0x002de89c):UINT32_C(0x002de894));goto dispatch;}
L_002de890:
 STEP(UINT32_C(0x002de890)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de894));goto dispatch;
L_002de894:
 STEP(UINT32_C(0x002de894)); /* 0c0b6fb4 jal 002dbed0 */
 set(m,31u,UINT64_C(0x002de89c));STEP(UINT32_C(0x002de898));/* nop */target=sx(UINT32_C(0x002dbed0));goto dispatch;
L_002de898:
 STEP(UINT32_C(0x002de898)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de89c));goto dispatch;
L_002de89c:
 STEP(UINT32_C(0x002de89c)); /* 0c0b79de jal 002de778 */
 set(m,31u,UINT64_C(0x002de8a4));STEP(UINT32_C(0x002de8a0));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de778));goto dispatch;
L_002de8a0:
 STEP(UINT32_C(0x002de8a0)); /* 8e040000 lw a0,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de8a4));goto dispatch;
L_002de8a4:
 STEP(UINT32_C(0x002de8a4)); /* ae000000 sw zero,0x0(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de8a8));goto dispatch;
L_002de8a8:
 STEP(UINT32_C(0x002de8a8)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de8ac));goto dispatch;
L_002de8ac:
 STEP(UINT32_C(0x002de8ac)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002de8b0));goto dispatch;
L_002de8b0:
 STEP(UINT32_C(0x002de8b0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de8b4));goto dispatch;
L_002de8b4:
 STEP(UINT32_C(0x002de8b4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de8b8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002de8b8:
 STEP(UINT32_C(0x002de8b8)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002de8bc));goto dispatch;
L_002dbed0:
 STEP(UINT32_C(0x002dbed0)); /* 2403ffbd addiu v1,zero,-67 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffbd)));target=sx(UINT32_C(0x002dbed4));goto dispatch;
L_002dbed4:
 m->pc=UINT32_C(0x002dbed4); /* Unexecuted SYS; router owns exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbed8:
 STEP(UINT32_C(0x002dbed8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbedc));/* nop */goto dispatch;
L_002dbedc:
 STEP(UINT32_C(0x002dbedc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbee0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

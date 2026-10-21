#include "ps2_thread_kernel.h"
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
uint32_t nocturneThreadKernelResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x80003c50):goto L_80003c50;
 case UINT32_C(0x80003c54):goto L_80003c54;
 case UINT32_C(0x80003c58):goto L_80003c58;
 case UINT32_C(0x80003c5c):goto L_80003c5c;
 case UINT32_C(0x80003c60):goto L_80003c60;
 case UINT32_C(0x80003c64):goto L_80003c64;
 case UINT32_C(0x80003c68):goto L_80003c68;
 case UINT32_C(0x80003c6c):goto L_80003c6c;
 case UINT32_C(0x80003c70):goto L_80003c70;
 case UINT32_C(0x80003c74):goto L_80003c74;
 case UINT32_C(0x80003c78):goto L_80003c78;
 case UINT32_C(0x80003c7c):goto L_80003c7c;
 case UINT32_C(0x80003c80):goto L_80003c80;
 case UINT32_C(0x80003c84):goto L_80003c84;
 case UINT32_C(0x80003c88):goto L_80003c88;
 case UINT32_C(0x80003c8c):goto L_80003c8c;
 case UINT32_C(0x80003c90):goto L_80003c90;
 case UINT32_C(0x80003c94):goto L_80003c94;
 case UINT32_C(0x80003c98):goto L_80003c98;
 case UINT32_C(0x80003c9c):goto L_80003c9c;
 case UINT32_C(0x80003ca0):goto L_80003ca0;
 case UINT32_C(0x80003ca4):goto L_80003ca4;
 case UINT32_C(0x80003ca8):goto L_80003ca8;
 case UINT32_C(0x80003cac):goto L_80003cac;
 case UINT32_C(0x80003cb0):goto L_80003cb0;
 case UINT32_C(0x80003cb4):goto L_80003cb4;
 case UINT32_C(0x80003cb8):goto L_80003cb8;
 case UINT32_C(0x80003cbc):goto L_80003cbc;
 case UINT32_C(0x80003cc0):goto L_80003cc0;
 case UINT32_C(0x80003cc4):goto L_80003cc4;
 case UINT32_C(0x80003cc8):goto L_80003cc8;
 case UINT32_C(0x80003ccc):goto L_80003ccc;
 case UINT32_C(0x80003cd0):goto L_80003cd0;
 case UINT32_C(0x80003cd4):goto L_80003cd4;
 case UINT32_C(0x80003cd8):goto L_80003cd8;
 case UINT32_C(0x80003cdc):goto L_80003cdc;
 case UINT32_C(0x80003ce0):goto L_80003ce0;
 case UINT32_C(0x80003ce4):goto L_80003ce4;
 case UINT32_C(0x80003ce8):goto L_80003ce8;
 case UINT32_C(0x80003cec):goto L_80003cec;
 case UINT32_C(0x80003cf0):goto L_80003cf0;
 case UINT32_C(0x80003cf4):goto L_80003cf4;
 case UINT32_C(0x80003cf8):goto L_80003cf8;
 case UINT32_C(0x80003cfc):goto L_80003cfc;
 case UINT32_C(0x80003d00):goto L_80003d00;
 case UINT32_C(0x80003d04):goto L_80003d04;
 case UINT32_C(0x80003d08):goto L_80003d08;
 case UINT32_C(0x80003d0c):goto L_80003d0c;
 case UINT32_C(0x80003d10):goto L_80003d10;
 case UINT32_C(0x80003d14):goto L_80003d14;
 case UINT32_C(0x80003d18):goto L_80003d18;
 case UINT32_C(0x80003d1c):goto L_80003d1c;
 case UINT32_C(0x80003d20):goto L_80003d20;
 case UINT32_C(0x80003d24):goto L_80003d24;
 case UINT32_C(0x80003d28):goto L_80003d28;
 case UINT32_C(0x80003d2c):goto L_80003d2c;
 case UINT32_C(0x80003d30):goto L_80003d30;
 case UINT32_C(0x80003d34):goto L_80003d34;
 case UINT32_C(0x80003d38):goto L_80003d38;
 case UINT32_C(0x80003d3c):goto L_80003d3c;
 case UINT32_C(0x80003d40):goto L_80003d40;
 case UINT32_C(0x80003d44):goto L_80003d44;
 case UINT32_C(0x80003d48):goto L_80003d48;
 case UINT32_C(0x80003d4c):goto L_80003d4c;
 case UINT32_C(0x80003d50):goto L_80003d50;
 case UINT32_C(0x80003d54):goto L_80003d54;
 case UINT32_C(0x80003d58):goto L_80003d58;
 case UINT32_C(0x80003d5c):goto L_80003d5c;
 case UINT32_C(0x80003d60):goto L_80003d60;
 case UINT32_C(0x80003d64):goto L_80003d64;
 case UINT32_C(0x80003d68):goto L_80003d68;
 case UINT32_C(0x80003d6c):goto L_80003d6c;
 case UINT32_C(0x80003d70):goto L_80003d70;
 case UINT32_C(0x80003d74):goto L_80003d74;
 case UINT32_C(0x80003d78):goto L_80003d78;
 case UINT32_C(0x80003d7c):goto L_80003d7c;
 case UINT32_C(0x80003d80):goto L_80003d80;
 case UINT32_C(0x80003d84):goto L_80003d84;
 case UINT32_C(0x80003d88):goto L_80003d88;
 case UINT32_C(0x80003d8c):goto L_80003d8c;
 case UINT32_C(0x80003d90):goto L_80003d90;
 case UINT32_C(0x80003d94):goto L_80003d94;
 case UINT32_C(0x80003d98):goto L_80003d98;
 case UINT32_C(0x80003d9c):goto L_80003d9c;
 case UINT32_C(0x80003da0):goto L_80003da0;
 case UINT32_C(0x80003da4):goto L_80003da4;
 case UINT32_C(0x80003da8):goto L_80003da8;
 case UINT32_C(0x80003dac):goto L_80003dac;
 case UINT32_C(0x80003db0):goto L_80003db0;
 case UINT32_C(0x80003db4):goto L_80003db4;
 case UINT32_C(0x80003db8):goto L_80003db8;
 case UINT32_C(0x80003dbc):goto L_80003dbc;
 case UINT32_C(0x80003dc0):goto L_80003dc0;
 case UINT32_C(0x80003dc4):goto L_80003dc4;
 case UINT32_C(0x80003dc8):goto L_80003dc8;
 case UINT32_C(0x80003dcc):goto L_80003dcc;
 case UINT32_C(0x80003dd0):goto L_80003dd0;
 case UINT32_C(0x80003dd4):goto L_80003dd4;
 case UINT32_C(0x80003dd8):goto L_80003dd8;
 case UINT32_C(0x80003ddc):goto L_80003ddc;
 case UINT32_C(0x80003de0):goto L_80003de0;
 case UINT32_C(0x80003de4):goto L_80003de4;
 case UINT32_C(0x80003de8):goto L_80003de8;
 case UINT32_C(0x80003dec):goto L_80003dec;
 case UINT32_C(0x80003df0):goto L_80003df0;
 case UINT32_C(0x80003df4):goto L_80003df4;
 case UINT32_C(0x80003df8):goto L_80003df8;
 case UINT32_C(0x80003040):goto L_80003040;
 case UINT32_C(0x80003044):goto L_80003044;
 case UINT32_C(0x80003048):goto L_80003048;
 case UINT32_C(0x8000304c):goto L_8000304c;
 case UINT32_C(0x80003050):goto L_80003050;
 case UINT32_C(0x80003054):goto L_80003054;
 case UINT32_C(0x80003058):goto L_80003058;
 case UINT32_C(0x8000305c):goto L_8000305c;
 case UINT32_C(0x80003060):goto L_80003060;
 case UINT32_C(0x80003064):goto L_80003064;
 case UINT32_C(0x80003068):goto L_80003068;
 case UINT32_C(0x8000306c):goto L_8000306c;
 case UINT32_C(0x80003070):goto L_80003070;
 case UINT32_C(0x80003074):goto L_80003074;
 case UINT32_C(0x80003078):goto L_80003078;
 case UINT32_C(0x8000307c):goto L_8000307c;
 case UINT32_C(0x80003080):goto L_80003080;
 case UINT32_C(0x80003084):goto L_80003084;
 case UINT32_C(0x80003088):goto L_80003088;
 case UINT32_C(0x8000308c):goto L_8000308c;
 case UINT32_C(0x80003090):goto L_80003090;
 case UINT32_C(0x80003094):goto L_80003094;
 case UINT32_C(0x80003098):goto L_80003098;
 case UINT32_C(0x8000309c):goto L_8000309c;
 case UINT32_C(0x800030a0):goto L_800030a0;
 case UINT32_C(0x800030a4):goto L_800030a4;
 case UINT32_C(0x800030a8):goto L_800030a8;
 case UINT32_C(0x800030ac):goto L_800030ac;
 case UINT32_C(0x80003f70):goto L_80003f70;
 case UINT32_C(0x80003f74):goto L_80003f74;
 case UINT32_C(0x80003f78):goto L_80003f78;
 case UINT32_C(0x80003f7c):goto L_80003f7c;
 case UINT32_C(0x80003f80):goto L_80003f80;
 case UINT32_C(0x80003f84):goto L_80003f84;
 case UINT32_C(0x80003f88):goto L_80003f88;
 case UINT32_C(0x80003f8c):goto L_80003f8c;
 case UINT32_C(0x80003f90):goto L_80003f90;
 case UINT32_C(0x80003f94):goto L_80003f94;
 case UINT32_C(0x80003f98):goto L_80003f98;
 case UINT32_C(0x80003f9c):goto L_80003f9c;
 case UINT32_C(0x80003fa0):goto L_80003fa0;
 case UINT32_C(0x80003fa4):goto L_80003fa4;
 case UINT32_C(0x80003fa8):goto L_80003fa8;
 case UINT32_C(0x80003fac):goto L_80003fac;
 case UINT32_C(0x80003fb0):goto L_80003fb0;
 case UINT32_C(0x80003fb4):goto L_80003fb4;
 case UINT32_C(0x80003fb8):goto L_80003fb8;
 case UINT32_C(0x80003fbc):goto L_80003fbc;
 case UINT32_C(0x80003fc0):goto L_80003fc0;
 case UINT32_C(0x80003fc4):goto L_80003fc4;
 case UINT32_C(0x80003fc8):goto L_80003fc8;
 case UINT32_C(0x80003fcc):goto L_80003fcc;
 case UINT32_C(0x80003fd0):goto L_80003fd0;
 case UINT32_C(0x80003fd4):goto L_80003fd4;
 case UINT32_C(0x80003fd8):goto L_80003fd8;
 case UINT32_C(0x80003fdc):goto L_80003fdc;
 case UINT32_C(0x80003fe0):goto L_80003fe0;
 case UINT32_C(0x80003fe4):goto L_80003fe4;
 case UINT32_C(0x80003fe8):goto L_80003fe8;
 case UINT32_C(0x80003fec):goto L_80003fec;
 case UINT32_C(0x80003ff0):goto L_80003ff0;
 case UINT32_C(0x80005a58):goto L_80005a58;
 case UINT32_C(0x80005a5c):goto L_80005a5c;
 case UINT32_C(0x80005a60):goto L_80005a60;
 case UINT32_C(0x80005a64):goto L_80005a64;
 case UINT32_C(0x80005a68):goto L_80005a68;
 case UINT32_C(0x80005a6c):goto L_80005a6c;
 case UINT32_C(0x80005a70):goto L_80005a70;
 case UINT32_C(0x80005a74):goto L_80005a74;
 case UINT32_C(0x80005a78):goto L_80005a78;
 case UINT32_C(0x80005a7c):goto L_80005a7c;
 case UINT32_C(0x80005a80):goto L_80005a80;
 case UINT32_C(0x80005a84):goto L_80005a84;
 case UINT32_C(0x80005a88):goto L_80005a88;
 case UINT32_C(0x80005a8c):goto L_80005a8c;
 case UINT32_C(0x80005a90):goto L_80005a90;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_80003c50:
 STEP(UINT32_C(0x80003c50)); /* 27bdff90 addiu sp,sp,-112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff90)));target=sx(UINT32_C(0x80003c54));goto dispatch;
L_80003c54:
 STEP(UINT32_C(0x80003c54)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x80003c58));goto dispatch;
L_80003c58:
 STEP(UINT32_C(0x80003c58)); /* 0080a82d daddu s5,a0,zero */
 set(m,21u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003c5c));goto dispatch;
L_80003c5c:
 STEP(UINT32_C(0x80003c5c)); /* ffbf0060 sd ra,0x60(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x80003c60));goto dispatch;
L_80003c60:
 STEP(UINT32_C(0x80003c60)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003c64));goto dispatch;
L_80003c64:
 STEP(UINT32_C(0x80003c64)); /* 24846fe8 addiu a0,a0,28648 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00006fe8)));target=sx(UINT32_C(0x80003c68));goto dispatch;
L_80003c68:
 STEP(UINT32_C(0x80003c68)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x80003c6c));goto dispatch;
L_80003c6c:
 STEP(UINT32_C(0x80003c6c)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x80003c70));goto dispatch;
L_80003c70:
 STEP(UINT32_C(0x80003c70)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80003c74));goto dispatch;
L_80003c74:
 STEP(UINT32_C(0x80003c74)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80003c78));goto dispatch;
L_80003c78:
 STEP(UINT32_C(0x80003c78)); /* 0c001696 jal 80005a58 */
 set(m,31u,UINT64_C(0x80003c80));STEP(UINT32_C(0x80003c7c));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80005a58));goto dispatch;
L_80003c7c:
 STEP(UINT32_C(0x80003c7c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80003c80));goto dispatch;
L_80003c80:
 STEP(UINT32_C(0x80003c80)); /* 14400003 bne v0,zero,80003c90 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80003c84));set(m,3u,sx(UINT32_C(0x286b0000)));target=sx(taken?UINT32_C(0x80003c90):UINT32_C(0x80003c88));goto dispatch;}
L_80003c84:
 STEP(UINT32_C(0x80003c84)); /* 3c03286b lui v1,zero,0x286b */
 set(m,3u,sx(UINT32_C(0x286b0000)));target=sx(UINT32_C(0x80003c88));goto dispatch;
L_80003c88:
 STEP(UINT32_C(0x80003c88)); /* 1000000c beq zero,zero,80003cbc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80003c8c));set(m,24u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80003cbc):UINT32_C(0x80003c90));goto dispatch;}
L_80003c8c:
 STEP(UINT32_C(0x80003c8c)); /* 2418ffff addiu t8,zero,-1 */
 set(m,24u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80003c90));goto dispatch;
L_80003c90:
 STEP(UINT32_C(0x80003c90)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003c94));goto dispatch;
L_80003c94:
 STEP(UINT32_C(0x80003c94)); /* 24847400 addiu a0,a0,29696 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00007400)));target=sx(UINT32_C(0x80003c98));goto dispatch;
L_80003c98:
 STEP(UINT32_C(0x80003c98)); /* 00442023 subu a0,v0,a0 */
 set(m,4u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80003c9c));goto dispatch;
L_80003c9c:
 STEP(UINT32_C(0x80003c9c)); /* 3463ca1b ori v1,v1,0xca1b */
 set(m,3u,lo(m,3u) | UINT64_C(0xca1b));target=sx(UINT32_C(0x80003ca0));goto dispatch;
L_80003ca0:
 STEP(UINT32_C(0x80003ca0)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003ca4));goto dispatch;
L_80003ca4:
 STEP(UINT32_C(0x80003ca4)); /* 8c426fe0 lw v0,0x6fe0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00006fe0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80003ca8));goto dispatch;
L_80003ca8:
 STEP(UINT32_C(0x80003ca8)); /* 00832018 mult_rd a0,a0,v1 */
 {int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x80003cac));goto dispatch;
L_80003cac:
 STEP(UINT32_C(0x80003cac)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80003cb0));goto dispatch;
L_80003cb0:
 STEP(UINT32_C(0x80003cb0)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003cb4));goto dispatch;
L_80003cb4:
 STEP(UINT32_C(0x80003cb4)); /* ac226fe0 sw v0,0x6fe0(at) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x00006fe0),&value32,4u);target=sx(UINT32_C(0x80003cb8));goto dispatch;
L_80003cb8:
 STEP(UINT32_C(0x80003cb8)); /* 0004c083 sra t8,a0,2 */
 set(m,24u,sx((uint32_t)((int32_t)lo(m,4u)>>2u)));target=sx(UINT32_C(0x80003cbc));goto dispatch;
L_80003cbc:
 STEP(UINT32_C(0x80003cbc)); /* 07010003 regimm1 t8,80003ccc */
 {int taken=((int64_t)lo(m,24u)>=0);STEP(UINT32_C(0x80003cc0));set(m,9u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(taken?UINT32_C(0x80003ccc):UINT32_C(0x80003cc4));goto dispatch;}
L_80003cc0:
 STEP(UINT32_C(0x80003cc0)); /* 2409004c addiu t1,zero,76 */
 set(m,9u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x80003cc4));goto dispatch;
L_80003cc4:
 STEP(UINT32_C(0x80003cc4)); /* 10000044 beq zero,zero,80003dd8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80003cc8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80003dd8):UINT32_C(0x80003ccc));goto dispatch;}
L_80003cc8:
 STEP(UINT32_C(0x80003cc8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80003ccc));goto dispatch;
L_80003ccc:
 STEP(UINT32_C(0x80003ccc)); /* 8ea2000c lw v0,0xc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80003cd0));goto dispatch;
L_80003cd0:
 STEP(UINT32_C(0x80003cd0)); /* 03091818 mult_rd v1,t8,t1 */
 {int64_t product;if(lo(m,24u)!=sx((uint32_t)lo(m,24u))||lo(m,9u)!=sx((uint32_t)lo(m,9u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,24u)*(int64_t)(int32_t)lo(m,9u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x80003cd4));goto dispatch;
L_80003cd4:
 STEP(UINT32_C(0x80003cd4)); /* 8ea80008 lw t0,0x8(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x80003cd8));goto dispatch;
L_80003cd8:
 STEP(UINT32_C(0x80003cd8)); /* 8ea40004 lw a0,0x4(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00000004),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80003cdc));goto dispatch;
L_80003cdc:
 STEP(UINT32_C(0x80003cdc)); /* 24060010 addiu a2,zero,16 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80003ce0));goto dispatch;
L_80003ce0:
 STEP(UINT32_C(0x80003ce0)); /* 01024021 addu t0,t0,v0 */
 set(m,8u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80003ce4));goto dispatch;
L_80003ce4:
 STEP(UINT32_C(0x80003ce4)); /* 3c058001 lui a1,zero,0x8001 */
 set(m,5u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003ce8));goto dispatch;
L_80003ce8:
 STEP(UINT32_C(0x80003ce8)); /* 24a57408 addiu a1,a1,29704 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00007408)));target=sx(UINT32_C(0x80003cec));goto dispatch;
L_80003cec:
 STEP(UINT32_C(0x80003cec)); /* 250afd60 addiu t2,t0,-672 */
 set(m,10u,sx((uint32_t)lo(m,8u)+UINT32_C(0xfffffd60)));target=sx(UINT32_C(0x80003cf0));goto dispatch;
L_80003cf0:
 STEP(UINT32_C(0x80003cf0)); /* 24abfff8 addiu t3,a1,-8 */
 set(m,11u,sx((uint32_t)lo(m,5u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x80003cf4));goto dispatch;
L_80003cf4:
 STEP(UINT32_C(0x80003cf4)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003cf8));goto dispatch;
L_80003cf8:
 STEP(UINT32_C(0x80003cf8)); /* 00230821 addu at,at,v1 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003cfc));goto dispatch;
L_80003cfc:
 STEP(UINT32_C(0x80003cfc)); /* ac24740c sw a0,0x740c(at) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x0000740c),&value32,4u);target=sx(UINT32_C(0x80003d00));goto dispatch;
L_80003d00:
 STEP(UINT32_C(0x80003d00)); /* 006b5821 addu t3,v1,t3 */
 set(m,11u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,11u)));target=sx(UINT32_C(0x80003d04));goto dispatch;
L_80003d04:
 STEP(UINT32_C(0x80003d04)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003d08));goto dispatch;
L_80003d08:
 STEP(UINT32_C(0x80003d08)); /* 00230821 addu at,at,v1 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003d0c));goto dispatch;
L_80003d0c:
 STEP(UINT32_C(0x80003d0c)); /* ac2a7410 sw t2,0x7410(at) */
 value32=(uint32_t)lo(m,10u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x00007410),&value32,4u);target=sx(UINT32_C(0x80003d10));goto dispatch;
L_80003d10:
 STEP(UINT32_C(0x80003d10)); /* 00a39021 addu s2,a1,v1 */
 set(m,18u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003d14));goto dispatch;
L_80003d14:
 STEP(UINT32_C(0x80003d14)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003d18));goto dispatch;
L_80003d18:
 STEP(UINT32_C(0x80003d18)); /* 00230821 addu at,at,v1 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003d1c));goto dispatch;
L_80003d1c:
 STEP(UINT32_C(0x80003d1c)); /* ac267408 sw a2,0x7408(at) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x00007408),&value32,4u);target=sx(UINT32_C(0x80003d20));goto dispatch;
L_80003d20:
 STEP(UINT32_C(0x80003d20)); /* 0240202d daddu a0,s2,zero */
 set(m,4u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x80003d24));goto dispatch;
L_80003d24:
 STEP(UINT32_C(0x80003d24)); /* 8ea20010 lw v0,0x10(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80003d28));goto dispatch;
L_80003d28:
 STEP(UINT32_C(0x80003d28)); /* 24a60040 addiu a2,a1,64 */
 set(m,6u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x80003d2c));goto dispatch;
L_80003d2c:
 STEP(UINT32_C(0x80003d2c)); /* 3c078001 lui a3,zero,0x8001 */
 set(m,7u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003d30));goto dispatch;
L_80003d30:
 STEP(UINT32_C(0x80003d30)); /* 8ce725ec lw a3,0x25ec(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x000025ec),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x80003d34));goto dispatch;
L_80003d34:
 STEP(UINT32_C(0x80003d34)); /* 0080702d daddu t6,a0,zero */
 set(m,14u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003d38));goto dispatch;
L_80003d38:
 STEP(UINT32_C(0x80003d38)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003d3c));goto dispatch;
L_80003d3c:
 STEP(UINT32_C(0x80003d3c)); /* 00230821 addu at,at,v1 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003d40));goto dispatch;
L_80003d40:
 STEP(UINT32_C(0x80003d40)); /* ac227414 sw v0,0x7414(at) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x00007414),&value32,4u);target=sx(UINT32_C(0x80003d44));goto dispatch;
L_80003d44:
 STEP(UINT32_C(0x80003d44)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003d48));goto dispatch;
L_80003d48:
 STEP(UINT32_C(0x80003d48)); /* 00e93818 mult_rd a3,a3,t1 */
 {int64_t product;if(lo(m,7u)!=sx((uint32_t)lo(m,7u))||lo(m,9u)!=sx((uint32_t)lo(m,9u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,7u)*(int64_t)(int32_t)lo(m,9u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,7u,m->lo);}target=sx(UINT32_C(0x80003d4c));goto dispatch;
L_80003d4c:
 STEP(UINT32_C(0x80003d4c)); /* 0080682d daddu t5,a0,zero */
 set(m,13u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003d50));goto dispatch;
L_80003d50:
 STEP(UINT32_C(0x80003d50)); /* 96a20014 lhu v0,0x14(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00000014),&value16,2u);set(m,2u,(uint64_t)value16);target=sx(UINT32_C(0x80003d54));goto dispatch;
L_80003d54:
 STEP(UINT32_C(0x80003d54)); /* 24a9003c addiu t1,a1,60 */
 set(m,9u,sx((uint32_t)lo(m,5u)+UINT32_C(0x0000003c)));target=sx(UINT32_C(0x80003d58));goto dispatch;
L_80003d58:
 STEP(UINT32_C(0x80003d58)); /* 8eaf0004 lw t7,0x4(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00000004),&value32,4u);set(m,15u,sx(value32));target=sx(UINT32_C(0x80003d5c));goto dispatch;
L_80003d5c:
 STEP(UINT32_C(0x80003d5c)); /* 0080602d daddu t4,a0,zero */
 set(m,12u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003d60));goto dispatch;
L_80003d60:
 STEP(UINT32_C(0x80003d60)); /* a5620018 sh v0,0x18(t3) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000018),&value16,2u);target=sx(UINT32_C(0x80003d64));goto dispatch;
L_80003d64:
 STEP(UINT32_C(0x80003d64)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003d68));goto dispatch;
L_80003d68:
 STEP(UINT32_C(0x80003d68)); /* 0240a02d daddu s4,s2,zero */
 set(m,20u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x80003d6c));goto dispatch;
L_80003d6c:
 STEP(UINT32_C(0x80003d6c)); /* 00669821 addu s3,v1,a2 */
 set(m,19u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x80003d70));goto dispatch;
L_80003d70:
 STEP(UINT32_C(0x80003d70)); /* 96b00014 lhu s0,0x14(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00000014),&value16,2u);set(m,16u,(uint64_t)value16);target=sx(UINT32_C(0x80003d74));goto dispatch;
L_80003d74:
 STEP(UINT32_C(0x80003d74)); /* 00e63021 addu a2,a3,a2 */
 set(m,6u,sx((uint32_t)lo(m,7u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x80003d78));goto dispatch;
L_80003d78:
 STEP(UINT32_C(0x80003d78)); /* ae400030 sw zero,0x30(s2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x80003d7c));goto dispatch;
L_80003d7c:
 STEP(UINT32_C(0x80003d7c)); /* 00e93821 addu a3,a3,t1 */
 set(m,7u,sx((uint32_t)lo(m,7u)+(uint32_t)lo(m,9u)));target=sx(UINT32_C(0x80003d80));goto dispatch;
L_80003d80:
 STEP(UINT32_C(0x80003d80)); /* ac80001c sw zero,0x1c(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x80003d84));goto dispatch;
L_80003d84:
 STEP(UINT32_C(0x80003d84)); /* 00691821 addu v1,v1,t1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,9u)));target=sx(UINT32_C(0x80003d88));goto dispatch;
L_80003d88:
 STEP(UINT32_C(0x80003d88)); /* 8ea40008 lw a0,0x8(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80003d8c));goto dispatch;
L_80003d8c:
 STEP(UINT32_C(0x80003d8c)); /* 2508ffe0 addiu t0,t0,-32 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x80003d90));goto dispatch;
L_80003d90:
 STEP(UINT32_C(0x80003d90)); /* adc00018 sw zero,0x18(t6) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,14u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x80003d94));goto dispatch;
L_80003d94:
 STEP(UINT32_C(0x80003d94)); /* 0300102d daddu v0,t8,zero */
 set(m,2u,lo(m,24u)+lo(m,0u));target=sx(UINT32_C(0x80003d98));goto dispatch;
L_80003d98:
 STEP(UINT32_C(0x80003d98)); /* ae840034 sw a0,0x34(s4) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,20u)+UINT32_C(0x00000034),&value32,4u);target=sx(UINT32_C(0x80003d9c));goto dispatch;
L_80003d9c:
 STEP(UINT32_C(0x80003d9c)); /* ae20002c sw zero,0x2c(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x80003da0));goto dispatch;
L_80003da0:
 STEP(UINT32_C(0x80003da0)); /* 8cc40000 lw a0,0x0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80003da4));goto dispatch;
L_80003da4:
 STEP(UINT32_C(0x80003da4)); /* adaf0028 sw t7,0x28(t5) */
 value32=(uint32_t)lo(m,15u);WRITE((uint32_t)lo(m,13u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x80003da8));goto dispatch;
L_80003da8:
 STEP(UINT32_C(0x80003da8)); /* ae640000 sw a0,0x0(s3) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80003dac));goto dispatch;
L_80003dac:
 STEP(UINT32_C(0x80003dac)); /* 8ea6000c lw a2,0xc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x0000000c),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x80003db0));goto dispatch;
L_80003db0:
 STEP(UINT32_C(0x80003db0)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80003db4));goto dispatch;
L_80003db4:
 STEP(UINT32_C(0x80003db4)); /* 8ea90010 lw t1,0x10(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00000010),&value32,4u);set(m,9u,sx(value32));target=sx(UINT32_C(0x80003db8));goto dispatch;
L_80003db8:
 STEP(UINT32_C(0x80003db8)); /* ad860038 sw a2,0x38(t4) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,12u)+UINT32_C(0x00000038),&value32,4u);target=sx(UINT32_C(0x80003dbc));goto dispatch;
L_80003dbc:
 STEP(UINT32_C(0x80003dbc)); /* a570001a sh s0,0x1a(t3) */
 value16=(uint16_t)lo(m,16u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x0000001a),&value16,2u);target=sx(UINT32_C(0x80003dc0));goto dispatch;
L_80003dc0:
 STEP(UINT32_C(0x80003dc0)); /* ad4401f0 sw a0,0x1f0(t2) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,10u)+UINT32_C(0x000001f0),&value32,4u);target=sx(UINT32_C(0x80003dc4));goto dispatch;
L_80003dc4:
 STEP(UINT32_C(0x80003dc4)); /* aca00014 sw zero,0x14(a1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x80003dc8));goto dispatch;
L_80003dc8:
 STEP(UINT32_C(0x80003dc8)); /* ac640000 sw a0,0x0(v1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80003dcc));goto dispatch;
L_80003dcc:
 STEP(UINT32_C(0x80003dcc)); /* ad4901c0 sw t1,0x1c0(t2) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,10u)+UINT32_C(0x000001c0),&value32,4u);target=sx(UINT32_C(0x80003dd0));goto dispatch;
L_80003dd0:
 STEP(UINT32_C(0x80003dd0)); /* ad4801e0 sw t0,0x1e0(t2) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,10u)+UINT32_C(0x000001e0),&value32,4u);target=sx(UINT32_C(0x80003dd4));goto dispatch;
L_80003dd4:
 STEP(UINT32_C(0x80003dd4)); /* ad4801d0 sw t0,0x1d0(t2) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,10u)+UINT32_C(0x000001d0),&value32,4u);target=sx(UINT32_C(0x80003dd8));goto dispatch;
L_80003dd8:
 STEP(UINT32_C(0x80003dd8)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80003ddc));goto dispatch;
L_80003ddc:
 STEP(UINT32_C(0x80003ddc)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x80003de0));goto dispatch;
L_80003de0:
 STEP(UINT32_C(0x80003de0)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x80003de4));goto dispatch;
L_80003de4:
 STEP(UINT32_C(0x80003de4)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x80003de8));goto dispatch;
L_80003de8:
 STEP(UINT32_C(0x80003de8)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x80003dec));goto dispatch;
L_80003dec:
 STEP(UINT32_C(0x80003dec)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x80003df0));goto dispatch;
L_80003df0:
 STEP(UINT32_C(0x80003df0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x80003df4));goto dispatch;
L_80003df4:
 STEP(UINT32_C(0x80003df4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80003df8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));goto dispatch;
L_80003df8:
 STEP(UINT32_C(0x80003df8)); /* 27bd0070 addiu sp,sp,112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x80003dfc));goto dispatch;
L_80003040:
 STEP(UINT32_C(0x80003040)); /* 0c000da0 jal 80003680 */
 set(m,31u,UINT64_C(0x80003048));STEP(UINT32_C(0x80003044));set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003680));goto dispatch;
L_80003044:
 STEP(UINT32_C(0x80003044)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003048));goto dispatch;
L_80003048:
 STEP(UINT32_C(0x80003048)); /* 0c000fdc jal 80003f70 */
 set(m,31u,UINT64_C(0x80003050));STEP(UINT32_C(0x8000304c));/* nop */target=sx(UINT32_C(0x80003f70));goto dispatch;
L_8000304c:
 STEP(UINT32_C(0x8000304c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003050));goto dispatch;
L_80003050:
 STEP(UINT32_C(0x80003050)); /* 0440000e regimm0 v0,8000308c */
 {int taken=((int64_t)lo(m,2u)<0);STEP(UINT32_C(0x80003054));/* nop */target=sx(taken?UINT32_C(0x8000308c):UINT32_C(0x80003058));goto dispatch;}
L_80003054:
 STEP(UINT32_C(0x80003054)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003058));goto dispatch;
L_80003058:
 STEP(UINT32_C(0x80003058)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x8000305c));goto dispatch;
L_8000305c:
 STEP(UINT32_C(0x8000305c)); /* 40047000 cop0 rs0 rta0 rd14 fn0 */
 set(m,4u,sx(m->epc));target=sx(UINT32_C(0x80003060));goto dispatch;
L_80003060:
 STEP(UINT32_C(0x80003060)); /* 0c000e50 jal 80003940 */
 set(m,31u,UINT64_C(0x80003068));STEP(UINT32_C(0x80003064));READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003940));goto dispatch;
L_80003064:
 STEP(UINT32_C(0x80003064)); /* 8ca510c0 lw a1,0x10c0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003068));goto dispatch;
L_80003068:
 STEP(UINT32_C(0x80003068)); /* 40827000 cop0 rs4 rtv0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x8000306c));goto dispatch;
L_8000306c:
 STEP(UINT32_C(0x8000306c)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003070));goto dispatch;
L_80003070:
 STEP(UINT32_C(0x80003070)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x80003078));STEP(UINT32_C(0x80003074));set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003800));goto dispatch;
L_80003074:
 STEP(UINT32_C(0x80003074)); /* 0060e82d daddu sp,v1,zero */
 set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003078));goto dispatch;
L_80003078:
 STEP(UINT32_C(0x80003078)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x8000307c));goto dispatch;
L_8000307c:
 STEP(UINT32_C(0x8000307c)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x80003080));goto dispatch;
L_80003080:
 STEP(UINT32_C(0x80003080)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003084));goto dispatch;
L_80003084:
 STEP(UINT32_C(0x80003084)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003088));goto dispatch;
L_80003088:
 STEP(UINT32_C(0x80003088)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_8000308c:
 STEP(UINT32_C(0x8000308c)); /* 3c1d8000 lui sp,zero,0x8000 */
 set(m,29u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003090));goto dispatch;
L_80003090:
 STEP(UINT32_C(0x80003090)); /* 8fbd10c0 lw sp,0x10c0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000010c0),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x80003094));goto dispatch;
L_80003094:
 STEP(UINT32_C(0x80003094)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x8000309c));STEP(UINT32_C(0x80003098));value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80003800));goto dispatch;
L_80003098:
 STEP(UINT32_C(0x80003098)); /* ffa20020 sd v0,0x20(sp) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000309c));goto dispatch;
L_8000309c:
 STEP(UINT32_C(0x8000309c)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x800030a0));goto dispatch;
L_800030a0:
 STEP(UINT32_C(0x800030a0)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x800030a4));goto dispatch;
L_800030a4:
 STEP(UINT32_C(0x800030a4)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x800030a8));goto dispatch;
L_800030a8:
 STEP(UINT32_C(0x800030a8)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x800030ac));goto dispatch;
L_800030ac:
 STEP(UINT32_C(0x800030ac)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80003f70:
 STEP(UINT32_C(0x80003f70)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x80003f74));goto dispatch;
L_80003f74:
 STEP(UINT32_C(0x80003f74)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80003f78));goto dispatch;
L_80003f78:
 STEP(UINT32_C(0x80003f78)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003f7c));goto dispatch;
L_80003f7c:
 STEP(UINT32_C(0x80003f7c)); /* 2602ffff addiu v0,s0,-1 */
 set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80003f80));goto dispatch;
L_80003f80:
 STEP(UINT32_C(0x80003f80)); /* 2c4200ff sltiu v0,v0,255 */
 set(m,2u,(lo(m,2u)<UINT64_C(0xff)));target=sx(UINT32_C(0x80003f84));goto dispatch;
L_80003f84:
 STEP(UINT32_C(0x80003f84)); /* 1040000e beq v0,zero,80003fc0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80003f88));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x80003fc0):UINT32_C(0x80003f8c));goto dispatch;}
L_80003f88:
 STEP(UINT32_C(0x80003f88)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80003f8c));goto dispatch;
L_80003f8c:
 STEP(UINT32_C(0x80003f8c)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003f90));goto dispatch;
L_80003f90:
 STEP(UINT32_C(0x80003f90)); /* 8c4225ec lw v0,0x25ec(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x000025ec),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80003f94));goto dispatch;
L_80003f94:
 STEP(UINT32_C(0x80003f94)); /* 1202000a beq s0,v0,80003fc0 */
 {int taken=(lo(m,16u)==lo(m,2u));STEP(UINT32_C(0x80003f98));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(taken?UINT32_C(0x80003fc0):UINT32_C(0x80003f9c));goto dispatch;}
L_80003f98:
 STEP(UINT32_C(0x80003f98)); /* 2402004c addiu v0,zero,76 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x80003f9c));goto dispatch;
L_80003f9c:
 STEP(UINT32_C(0x80003f9c)); /* 3c068001 lui a2,zero,0x8001 */
 set(m,6u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003fa0));goto dispatch;
L_80003fa0:
 STEP(UINT32_C(0x80003fa0)); /* 24c67408 addiu a2,a2,29704 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00007408)));target=sx(UINT32_C(0x80003fa4));goto dispatch;
L_80003fa4:
 STEP(UINT32_C(0x80003fa4)); /* 02022018 mult_rd a0,s0,v0 */
 {int64_t product;if(lo(m,16u)!=sx((uint32_t)lo(m,16u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,16u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x80003fa8));goto dispatch;
L_80003fa8:
 STEP(UINT32_C(0x80003fa8)); /* 24030010 addiu v1,zero,16 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80003fac));goto dispatch;
L_80003fac:
 STEP(UINT32_C(0x80003fac)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003fb0));goto dispatch;
L_80003fb0:
 STEP(UINT32_C(0x80003fb0)); /* 00441021 addu v0,v0,a0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80003fb4));goto dispatch;
L_80003fb4:
 STEP(UINT32_C(0x80003fb4)); /* 8c427408 lw v0,0x7408(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00007408),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80003fb8));goto dispatch;
L_80003fb8:
 STEP(UINT32_C(0x80003fb8)); /* 10430003 beq v0,v1,80003fc8 */
 {int taken=(lo(m,2u)==lo(m,3u));STEP(UINT32_C(0x80003fbc));set(m,2u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,4u)));target=sx(taken?UINT32_C(0x80003fc8):UINT32_C(0x80003fc0));goto dispatch;}
L_80003fbc:
 STEP(UINT32_C(0x80003fbc)); /* 00c41021 addu v0,a2,a0 */
 set(m,2u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80003fc0));goto dispatch;
L_80003fc0:
 STEP(UINT32_C(0x80003fc0)); /* 10000008 beq zero,zero,80003fe4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80003fc4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80003fe4):UINT32_C(0x80003fc8));goto dispatch;}
L_80003fc4:
 STEP(UINT32_C(0x80003fc4)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80003fc8));goto dispatch;
L_80003fc8:
 STEP(UINT32_C(0x80003fc8)); /* ac450030 sw a1,0x30(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x80003fcc));goto dispatch;
L_80003fcc:
 STEP(UINT32_C(0x80003fcc)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80003fd0));goto dispatch;
L_80003fd0:
 STEP(UINT32_C(0x80003fd0)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80003fd4));goto dispatch;
L_80003fd4:
 STEP(UINT32_C(0x80003fd4)); /* 8c620008 lw v0,0x8(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80003fd8));goto dispatch;
L_80003fd8:
 STEP(UINT32_C(0x80003fd8)); /* 0c00166e jal 800059b8 */
 set(m,31u,UINT64_C(0x80003fe0));STEP(UINT32_C(0x80003fdc));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000040),&value32,4u);target=sx(UINT32_C(0x800059b8));goto dispatch;
L_80003fdc:
 STEP(UINT32_C(0x80003fdc)); /* ac450040 sw a1,0x40(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000040),&value32,4u);target=sx(UINT32_C(0x80003fe0));goto dispatch;
L_80003fe0:
 STEP(UINT32_C(0x80003fe0)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80003fe4));goto dispatch;
L_80003fe4:
 STEP(UINT32_C(0x80003fe4)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80003fe8));goto dispatch;
L_80003fe8:
 STEP(UINT32_C(0x80003fe8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x80003fec));goto dispatch;
L_80003fec:
 STEP(UINT32_C(0x80003fec)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80003ff0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_80003ff0:
 STEP(UINT32_C(0x80003ff0)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x80003ff4));goto dispatch;
L_80005a58:
 STEP(UINT32_C(0x80005a58)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005a5c));goto dispatch;
L_80005a5c:
 STEP(UINT32_C(0x80005a5c)); /* 14820005 bne a0,v0,80005a74 */
 {int taken=(lo(m,4u)!=lo(m,2u));STEP(UINT32_C(0x80005a60));READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));target=sx(taken?UINT32_C(0x80005a74):UINT32_C(0x80005a64));goto dispatch;}
L_80005a60:
 STEP(UINT32_C(0x80005a60)); /* 8c860004 lw a2,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x80005a64));goto dispatch;
L_80005a64:
 STEP(UINT32_C(0x80005a64)); /* 54860004 bnel a0,a2,80005a78 */
 if(lo(m,4u)!=lo(m,6u)){STEP(UINT32_C(0x80005a68));READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80005a78));}else target=sx(UINT32_C(0x80005a6c));goto dispatch;
L_80005a68:
 STEP(UINT32_C(0x80005a68)); /* 8cc30000 lw v1,0x0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80005a6c));goto dispatch;
L_80005a6c:
 STEP(UINT32_C(0x80005a6c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80005a70));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_80005a70:
 STEP(UINT32_C(0x80005a70)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80005a74));goto dispatch;
L_80005a74:
 STEP(UINT32_C(0x80005a74)); /* 8cc30000 lw v1,0x0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80005a78));goto dispatch;
L_80005a78:
 STEP(UINT32_C(0x80005a78)); /* 00c0102d daddu v0,a2,zero */
 set(m,2u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x80005a7c));goto dispatch;
L_80005a7c:
 STEP(UINT32_C(0x80005a7c)); /* 8cc50004 lw a1,0x4(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80005a80));goto dispatch;
L_80005a80:
 STEP(UINT32_C(0x80005a80)); /* aca30000 sw v1,0x0(a1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80005a84));goto dispatch;
L_80005a84:
 STEP(UINT32_C(0x80005a84)); /* 8cc40000 lw a0,0x0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80005a88));goto dispatch;
L_80005a88:
 STEP(UINT32_C(0x80005a88)); /* 8cc30004 lw v1,0x4(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80005a8c));goto dispatch;
L_80005a8c:
 STEP(UINT32_C(0x80005a8c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80005a90));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);goto dispatch;
L_80005a90:
 STEP(UINT32_C(0x80005a90)); /* ac830004 sw v1,0x4(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80005a94));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

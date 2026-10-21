#include "sound_play_bank_native.h"
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
uint32_t nocturneSoundPlayBankResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s,const NocturneSoundBankProcessor *processor)
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
 case UINT32_C(0x002c18d8):goto L_002c18d8;
 case UINT32_C(0x002c18dc):goto L_002c18dc;
 case UINT32_C(0x002c18e0):goto L_002c18e0;
 case UINT32_C(0x002c18e4):goto L_002c18e4;
 case UINT32_C(0x002c18e8):goto L_002c18e8;
 case UINT32_C(0x002c18ec):goto L_002c18ec;
 case UINT32_C(0x002c18f0):goto L_002c18f0;
 case UINT32_C(0x002c18f4):goto L_002c18f4;
 case UINT32_C(0x002c18f8):goto L_002c18f8;
 case UINT32_C(0x002c18fc):goto L_002c18fc;
 case UINT32_C(0x002c1900):goto L_002c1900;
 case UINT32_C(0x002c1904):goto L_002c1904;
 case UINT32_C(0x002c1908):goto L_002c1908;
 case UINT32_C(0x002c190c):goto L_002c190c;
 case UINT32_C(0x002c1910):goto L_002c1910;
 case UINT32_C(0x002c1914):goto L_002c1914;
 case UINT32_C(0x002c1918):goto L_002c1918;
 case UINT32_C(0x002c191c):goto L_002c191c;
 case UINT32_C(0x002c1920):goto L_002c1920;
 case UINT32_C(0x002c1924):goto L_002c1924;
 case UINT32_C(0x002c1928):goto L_002c1928;
 case UINT32_C(0x002c192c):goto L_002c192c;
 case UINT32_C(0x002c1930):goto L_002c1930;
 case UINT32_C(0x002c1934):goto L_002c1934;
 case UINT32_C(0x002c1c20):goto L_002c1c20;
 case UINT32_C(0x002c1c24):goto L_002c1c24;
 case UINT32_C(0x002c1c28):goto L_002c1c28;
 case UINT32_C(0x002c1c2c):goto L_002c1c2c;
 case UINT32_C(0x002c1c30):goto L_002c1c30;
 case UINT32_C(0x002c1c34):goto L_002c1c34;
 case UINT32_C(0x002c1c38):goto L_002c1c38;
 case UINT32_C(0x002c1c3c):goto L_002c1c3c;
 case UINT32_C(0x002c1c40):goto L_002c1c40;
 case UINT32_C(0x002c1c44):goto L_002c1c44;
 case UINT32_C(0x002c1c48):goto L_002c1c48;
 case UINT32_C(0x002c1c4c):goto L_002c1c4c;
 case UINT32_C(0x002c1c50):goto L_002c1c50;
 case UINT32_C(0x002c1c54):goto L_002c1c54;
 case UINT32_C(0x002c1c58):goto L_002c1c58;
 case UINT32_C(0x002c1c5c):goto L_002c1c5c;
 case UINT32_C(0x002c1c60):goto L_002c1c60;
 case UINT32_C(0x002c1c64):goto L_002c1c64;
 case UINT32_C(0x002c1c68):goto L_002c1c68;
 case UINT32_C(0x002c1c6c):goto L_002c1c6c;
 case UINT32_C(0x002c1c70):goto L_002c1c70;
 case UINT32_C(0x002c1c74):goto L_002c1c74;
 case UINT32_C(0x002c1c78):goto L_002c1c78;
 case UINT32_C(0x002c1c7c):goto L_002c1c7c;
 case UINT32_C(0x002c1c80):goto L_002c1c80;
 case UINT32_C(0x002c1c84):goto L_002c1c84;
 case UINT32_C(0x002c1c88):goto L_002c1c88;
 case UINT32_C(0x002c1c8c):goto L_002c1c8c;
 case UINT32_C(0x002c1c90):goto L_002c1c90;
 case UINT32_C(0x002c1c94):goto L_002c1c94;
 case UINT32_C(0x002c1c98):goto L_002c1c98;
 case UINT32_C(0x002c1c9c):goto L_002c1c9c;
 case UINT32_C(0x002c1ca0):goto L_002c1ca0;
 case UINT32_C(0x002c1ca4):goto L_002c1ca4;
 case UINT32_C(0x002c1ca8):goto L_002c1ca8;
 case UINT32_C(0x002c1cac):goto L_002c1cac;
 case UINT32_C(0x002c1cb0):goto L_002c1cb0;
 case UINT32_C(0x002c1cb4):goto L_002c1cb4;
 case UINT32_C(0x002c1cb8):goto L_002c1cb8;
 case UINT32_C(0x002c1cbc):goto L_002c1cbc;
 case UINT32_C(0x002c1cc0):goto L_002c1cc0;
 case UINT32_C(0x002c1cc4):goto L_002c1cc4;
 case UINT32_C(0x002c1cc8):goto L_002c1cc8;
 case UINT32_C(0x002c1ccc):goto L_002c1ccc;
 case UINT32_C(0x002c1cd0):goto L_002c1cd0;
 case UINT32_C(0x002c1cd4):goto L_002c1cd4;
 case UINT32_C(0x002c1cd8):goto L_002c1cd8;
 case UINT32_C(0x002c1cdc):goto L_002c1cdc;
 case UINT32_C(0x002c1ce0):goto L_002c1ce0;
 case UINT32_C(0x002c1ce4):goto L_002c1ce4;
 case UINT32_C(0x002c1ce8):goto L_002c1ce8;
 case UINT32_C(0x002c1cec):goto L_002c1cec;
 case UINT32_C(0x002c1cf0):goto L_002c1cf0;
 case UINT32_C(0x002c1cf4):goto L_002c1cf4;
 case UINT32_C(0x002c1cf8):goto L_002c1cf8;
 case UINT32_C(0x002c1cfc):goto L_002c1cfc;
 case UINT32_C(0x002c1d00):goto L_002c1d00;
 case UINT32_C(0x002c1d04):goto L_002c1d04;
 case UINT32_C(0x002c1d08):goto L_002c1d08;
 case UINT32_C(0x002c1d0c):goto L_002c1d0c;
 case UINT32_C(0x002c1d10):goto L_002c1d10;
 case UINT32_C(0x002c1d14):goto L_002c1d14;
 case UINT32_C(0x002c1d18):goto L_002c1d18;
 case UINT32_C(0x002c1d1c):goto L_002c1d1c;
 case UINT32_C(0x002c1d20):goto L_002c1d20;
 case UINT32_C(0x002c1d24):goto L_002c1d24;
 case UINT32_C(0x002c1d28):goto L_002c1d28;
 case UINT32_C(0x002c1d2c):goto L_002c1d2c;
 case UINT32_C(0x002c1d30):goto L_002c1d30;
 case UINT32_C(0x002c1d34):goto L_002c1d34;
 case UINT32_C(0x002c1d38):goto L_002c1d38;
 case UINT32_C(0x002c1d3c):goto L_002c1d3c;
 case UINT32_C(0x002c1d40):goto L_002c1d40;
 case UINT32_C(0x002c1d44):goto L_002c1d44;
 case UINT32_C(0x002c1d48):goto L_002c1d48;
 case UINT32_C(0x002c1d4c):goto L_002c1d4c;
 case UINT32_C(0x002c1d50):goto L_002c1d50;
 case UINT32_C(0x002c1d54):goto L_002c1d54;
 case UINT32_C(0x002c1d58):goto L_002c1d58;
 case UINT32_C(0x002c1d5c):goto L_002c1d5c;
 case UINT32_C(0x002c1d60):goto L_002c1d60;
 case UINT32_C(0x002c1d64):goto L_002c1d64;
 case UINT32_C(0x002c1d68):goto L_002c1d68;
 case UINT32_C(0x002c1d6c):goto L_002c1d6c;
 case UINT32_C(0x002c1d70):goto L_002c1d70;
 case UINT32_C(0x002c1d74):goto L_002c1d74;
 case UINT32_C(0x002dc830):goto L_002dc830;
 case UINT32_C(0x002dc834):goto L_002dc834;
 case UINT32_C(0x002dc838):goto L_002dc838;
 case UINT32_C(0x002dc83c):goto L_002dc83c;
 case UINT32_C(0x002dc840):goto L_002dc840;
 case UINT32_C(0x002dc844):goto L_002dc844;
 case UINT32_C(0x002dc848):goto L_002dc848;
 case UINT32_C(0x002dc84c):goto L_002dc84c;
 case UINT32_C(0x002dc850):goto L_002dc850;
 case UINT32_C(0x002dc854):goto L_002dc854;
 case UINT32_C(0x002dc858):goto L_002dc858;
 case UINT32_C(0x002dc85c):goto L_002dc85c;
 case UINT32_C(0x002dc860):goto L_002dc860;
 case UINT32_C(0x002dc864):goto L_002dc864;
 case UINT32_C(0x002dc868):goto L_002dc868;
 case UINT32_C(0x002dc86c):goto L_002dc86c;
 case UINT32_C(0x002dc870):goto L_002dc870;
 case UINT32_C(0x002dc874):goto L_002dc874;
 case UINT32_C(0x002dc878):goto L_002dc878;
 case UINT32_C(0x002dc87c):goto L_002dc87c;
 case UINT32_C(0x002dc880):goto L_002dc880;
 case UINT32_C(0x002dc884):goto L_002dc884;
 case UINT32_C(0x002dc888):goto L_002dc888;
 case UINT32_C(0x002dc88c):goto L_002dc88c;
 case UINT32_C(0x002dc890):goto L_002dc890;
 case UINT32_C(0x002dc894):goto L_002dc894;
 case UINT32_C(0x002dc898):goto L_002dc898;
 case UINT32_C(0x002dc89c):goto L_002dc89c;
 case UINT32_C(0x002dc8a0):goto L_002dc8a0;
 case UINT32_C(0x002dc8a4):goto L_002dc8a4;
 case UINT32_C(0x002dc8a8):goto L_002dc8a8;
 case UINT32_C(0x002dc8ac):goto L_002dc8ac;
 case UINT32_C(0x002dc8b0):goto L_002dc8b0;
 case UINT32_C(0x002dc8b4):goto L_002dc8b4;
 case UINT32_C(0x002dc8b8):goto L_002dc8b8;
 case UINT32_C(0x002dc8bc):goto L_002dc8bc;
 case UINT32_C(0x002dc8c0):goto L_002dc8c0;
 case UINT32_C(0x002dc8c4):goto L_002dc8c4;
 case UINT32_C(0x002dc8c8):goto L_002dc8c8;
 case UINT32_C(0x002dc8cc):goto L_002dc8cc;
 case UINT32_C(0x002dc8d0):goto L_002dc8d0;
 case UINT32_C(0x002dc8d8):goto L_002dc8d8;
 case UINT32_C(0x002dc8dc):goto L_002dc8dc;
 case UINT32_C(0x002dc8e0):goto L_002dc8e0;
 case UINT32_C(0x002dc8e4):goto L_002dc8e4;
 case UINT32_C(0x002dc8e8):goto L_002dc8e8;
 case UINT32_C(0x002dc8ec):goto L_002dc8ec;
 case UINT32_C(0x002dc8f0):goto L_002dc8f0;
 case UINT32_C(0x002dc8f4):goto L_002dc8f4;
 case UINT32_C(0x002dc8f8):goto L_002dc8f8;
 case UINT32_C(0x002dc8fc):goto L_002dc8fc;
 case UINT32_C(0x002dc900):goto L_002dc900;
 case UINT32_C(0x002dc904):goto L_002dc904;
 case UINT32_C(0x002dc908):goto L_002dc908;
 case UINT32_C(0x002dc90c):goto L_002dc90c;
 case UINT32_C(0x002dc910):goto L_002dc910;
 case UINT32_C(0x002dc914):goto L_002dc914;
 case UINT32_C(0x002dc918):goto L_002dc918;
 case UINT32_C(0x002dc91c):goto L_002dc91c;
 case UINT32_C(0x002dc920):goto L_002dc920;
 case UINT32_C(0x002dc924):goto L_002dc924;
 case UINT32_C(0x002dc928):goto L_002dc928;
 case UINT32_C(0x002dc92c):goto L_002dc92c;
 case UINT32_C(0x002dc930):goto L_002dc930;
 case UINT32_C(0x002dc934):goto L_002dc934;
 case UINT32_C(0x002dc938):goto L_002dc938;
 case UINT32_C(0x002dc93c):goto L_002dc93c;
 case UINT32_C(0x002dc940):goto L_002dc940;
 case UINT32_C(0x002dc944):goto L_002dc944;
 case UINT32_C(0x002dc948):goto L_002dc948;
 case UINT32_C(0x002dc94c):goto L_002dc94c;
 case UINT32_C(0x002dc950):goto L_002dc950;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002c18d8:
 STEP(UINT32_C(0x002c18d8)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002c18dc));goto dispatch;
L_002c18dc:
 STEP(UINT32_C(0x002c18dc)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002c18e0));goto dispatch;
L_002c18e0:
 STEP(UINT32_C(0x002c18e0)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002c18e4));goto dispatch;
L_002c18e4:
 STEP(UINT32_C(0x002c18e4)); /* ffb10018 sd s1,0x18(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002c18e8));goto dispatch;
L_002c18e8:
 STEP(UINT32_C(0x002c18e8)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002c18ec));goto dispatch;
L_002c18ec:
 STEP(UINT32_C(0x002c18ec)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002c18f0));goto dispatch;
L_002c18f0:
 STEP(UINT32_C(0x002c18f0)); /* ffbf0028 sd ra,0x28(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(UINT32_C(0x002c18f4));goto dispatch;
L_002c18f4:
 STEP(UINT32_C(0x002c18f4)); /* 0c0b0728 jal 002c1ca0 */
 set(m,31u,UINT64_C(0x002c18fc));STEP(UINT32_C(0x002c18f8));set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002c1ca0));goto dispatch;
L_002c18f8:
 STEP(UINT32_C(0x002c18f8)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002c18fc));goto dispatch;
L_002c18fc:
 STEP(UINT32_C(0x002c18fc)); /* 323100ff andi s1,s1,0xff */
 set(m,17u,lo(m,17u) & UINT64_C(0xff));target=sx(UINT32_C(0x002c1900));goto dispatch;
L_002c1900:
 STEP(UINT32_C(0x002c1900)); /* 03a0302d daddu a2,sp,zero */
 set(m,6u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002c1904));goto dispatch;
L_002c1904:
 STEP(UINT32_C(0x002c1904)); /* 24040090 addiu a0,zero,144 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000090)));target=sx(UINT32_C(0x002c1908));goto dispatch;
L_002c1908:
 STEP(UINT32_C(0x002c1908)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c190c));goto dispatch;
L_002c190c:
 STEP(UINT32_C(0x002c190c)); /* 2407000c addiu a3,zero,12 */
 set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002c1910));goto dispatch;
L_002c1910:
 STEP(UINT32_C(0x002c1910)); /* afb20000 sw s2,0x0(sp) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002c1914));goto dispatch;
L_002c1914:
 STEP(UINT32_C(0x002c1914)); /* a7b00008 sh s0,0x8(sp) */
 value16=(uint16_t)lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value16,2u);target=sx(UINT32_C(0x002c1918));goto dispatch;
L_002c1918:
 STEP(UINT32_C(0x002c1918)); /* 0c0b043a jal 002c10e8 */
 set(m,31u,UINT64_C(0x002c1920));STEP(UINT32_C(0x002c191c));value16=(uint16_t)lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000a),&value16,2u);target=sx(UINT32_C(0x002c10e8));goto dispatch;
L_002c191c:
 STEP(UINT32_C(0x002c191c)); /* a7b1000a sh s1,0xa(sp) */
 value16=(uint16_t)lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000a),&value16,2u);target=sx(UINT32_C(0x002c1920));goto dispatch;
L_002c1920:
 STEP(UINT32_C(0x002c1920)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1924));goto dispatch;
L_002c1924:
 STEP(UINT32_C(0x002c1924)); /* dfb10018 ld s1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c1928));goto dispatch;
L_002c1928:
 STEP(UINT32_C(0x002c1928)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002c192c));goto dispatch;
L_002c192c:
 STEP(UINT32_C(0x002c192c)); /* dfbf0028 ld ra,0x28(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c1930));goto dispatch;
L_002c1930:
 STEP(UINT32_C(0x002c1930)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c1934));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002c1934:
 STEP(UINT32_C(0x002c1934)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002c1938));goto dispatch;
L_002c1c20:
 STEP(UINT32_C(0x002c1c20)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002c1c24));goto dispatch;
L_002c1c24:
 STEP(UINT32_C(0x002c1c24)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c1c28));goto dispatch;
L_002c1c28:
 STEP(UINT32_C(0x002c1c28)); /* 3c100059 lui s0,zero,0x59 */
 set(m,16u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c1c2c));goto dispatch;
L_002c1c2c:
 STEP(UINT32_C(0x002c1c2c)); /* 26103880 addiu s0,s0,14464 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00003880)));target=sx(UINT32_C(0x002c1c30));goto dispatch;
L_002c1c30:
 STEP(UINT32_C(0x002c1c30)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c1c34));goto dispatch;
L_002c1c34:
 STEP(UINT32_C(0x002c1c34)); /* 260505a0 addiu a1,s0,1440 */
 set(m,5u,sx((uint32_t)lo(m,16u)+UINT32_C(0x000005a0)));target=sx(UINT32_C(0x002c1c38));goto dispatch;
L_002c1c38:
 STEP(UINT32_C(0x002c1c38)); /* 00048c03 sra s1,a0,16 */
 set(m,17u,sx((uint32_t)((int32_t)lo(m,4u)>>16u)));target=sx(UINT32_C(0x002c1c3c));goto dispatch;
L_002c1c3c:
 STEP(UINT32_C(0x002c1c3c)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c1c40));goto dispatch;
L_002c1c40:
 STEP(UINT32_C(0x002c1c40)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002c1c44));goto dispatch;
L_002c1c44:
 STEP(UINT32_C(0x002c1c44)); /* 0c0b7236 jal 002dc8d8 */
 set(m,31u,UINT64_C(0x002c1c4c));STEP(UINT32_C(0x002c1c48));set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000190)));target=sx(UINT32_C(0x002dc8d8));goto dispatch;
L_002c1c48:
 STEP(UINT32_C(0x002c1c48)); /* 26100190 addiu s0,s0,400 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000190)));target=sx(UINT32_C(0x002c1c4c));goto dispatch;
L_002c1c4c:
 STEP(UINT32_C(0x002c1c4c)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1c50));goto dispatch;
L_002c1c50:
 STEP(UINT32_C(0x002c1c50)); /* 8e030000 lw v1,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002c1c54));goto dispatch;
L_002c1c54:
 STEP(UINT32_C(0x002c1c54)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1c58));goto dispatch;
L_002c1c58:
 STEP(UINT32_C(0x002c1c58)); /* 26100008 addiu s0,s0,8 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002c1c5c));goto dispatch;
L_002c1c5c:
 STEP(UINT32_C(0x002c1c5c)); /* 1071000b beq v1,s1,002c1c8c */
 {int taken=(lo(m,3u)==lo(m,17u));STEP(UINT32_C(0x002c1c60));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002c1c8c):UINT32_C(0x002c1c64));goto dispatch;}
L_002c1c60:
 STEP(UINT32_C(0x002c1c60)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1c64));goto dispatch;
L_002c1c64:
 STEP(UINT32_C(0x002c1c64)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1c68));goto dispatch;
L_002c1c68:
 STEP(UINT32_C(0x002c1c68)); /* 28820007 slti v0,a0,7 */
 set(m,2u,((int64_t)lo(m,4u)<INT64_C(7)));target=sx(UINT32_C(0x002c1c6c));goto dispatch;
L_002c1c6c:
 STEP(UINT32_C(0x002c1c6c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1c70));goto dispatch;
L_002c1c70:
 STEP(UINT32_C(0x002c1c70)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1c74));goto dispatch;
L_002c1c74:
 STEP(UINT32_C(0x002c1c74)); /* 5440fff8 bnel v0,zero,002c1c58 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002c1c78));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002c1c58));}else target=sx(UINT32_C(0x002c1c7c));goto dispatch;
L_002c1c78:
 STEP(UINT32_C(0x002c1c78)); /* 8e030000 lw v1,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002c1c7c));goto dispatch;
L_002c1c7c:
 STEP(UINT32_C(0x002c1c7c)); /* 8f83d850 lw v1,-0x27b0(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd850),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002c1c80));goto dispatch;
L_002c1c80:
 STEP(UINT32_C(0x002c1c80)); /* 24020002 addiu v0,zero,2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002c1c84));goto dispatch;
L_002c1c84:
 STEP(UINT32_C(0x002c1c84)); /* 00711826 xor v1,v1,s1 */
 set(m,3u,lo(m,3u)^lo(m,17u));target=sx(UINT32_C(0x002c1c88));goto dispatch;
L_002c1c88:
 STEP(UINT32_C(0x002c1c88)); /* 0003100b movn v0,zero,v1 */
 if(lo(m,3u))set(m,2u,lo(m,0u));target=sx(UINT32_C(0x002c1c8c));goto dispatch;
L_002c1c8c:
 STEP(UINT32_C(0x002c1c8c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1c90));goto dispatch;
L_002c1c90:
 STEP(UINT32_C(0x002c1c90)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c1c94));goto dispatch;
L_002c1c94:
 STEP(UINT32_C(0x002c1c94)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c1c98));goto dispatch;
L_002c1c98:
 STEP(UINT32_C(0x002c1c98)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c1c9c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002c1c9c:
 STEP(UINT32_C(0x002c1c9c)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002c1ca0));goto dispatch;
L_002c1ca0:
 STEP(UINT32_C(0x002c1ca0)); /* 27bdfed0 addiu sp,sp,-304 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffed0)));target=sx(UINT32_C(0x002c1ca4));goto dispatch;
L_002c1ca4:
 STEP(UINT32_C(0x002c1ca4)); /* ffb00110 sd s0,0x110(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000110),&value64,8u);target=sx(UINT32_C(0x002c1ca8));goto dispatch;
L_002c1ca8:
 STEP(UINT32_C(0x002c1ca8)); /* ffb10118 sd s1,0x118(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000118),&value64,8u);target=sx(UINT32_C(0x002c1cac));goto dispatch;
L_002c1cac:
 STEP(UINT32_C(0x002c1cac)); /* ffbf0120 sd ra,0x120(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000120),&value64,8u);target=sx(UINT32_C(0x002c1cb0));goto dispatch;
L_002c1cb0:
 STEP(UINT32_C(0x002c1cb0)); /* 0c0b0708 jal 002c1c20 */
 set(m,31u,UINT64_C(0x002c1cb8));STEP(UINT32_C(0x002c1cb4));set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002c1c20));goto dispatch;
L_002c1cb4:
 STEP(UINT32_C(0x002c1cb4)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002c1cb8));goto dispatch;
L_002c1cb8:
 STEP(UINT32_C(0x002c1cb8)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c1cbc));goto dispatch;
L_002c1cbc:
 STEP(UINT32_C(0x002c1cbc)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1cc0));goto dispatch;
L_002c1cc0:
 STEP(UINT32_C(0x002c1cc0)); /* 10620028 beq v1,v0,002c1d64 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002c1cc4));set(m,2u,((int64_t)lo(m,3u)<INT64_C(2)));target=sx(taken?UINT32_C(0x002c1d64):UINT32_C(0x002c1cc8));goto dispatch;}
L_002c1cc4:
 STEP(UINT32_C(0x002c1cc4)); /* 28620002 slti v0,v1,2 */
 set(m,2u,((int64_t)lo(m,3u)<INT64_C(2)));target=sx(UINT32_C(0x002c1cc8));goto dispatch;
L_002c1cc8:
 STEP(UINT32_C(0x002c1cc8)); /* 50400005 beql v0,zero,002c1ce0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002c1ccc));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002c1ce0));}else target=sx(UINT32_C(0x002c1cd0));goto dispatch;
L_002c1ccc:
 STEP(UINT32_C(0x002c1ccc)); /* 24020002 addiu v0,zero,2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002c1cd0));goto dispatch;
L_002c1cd0:
 STEP(UINT32_C(0x002c1cd0)); /* 50600007 beql v1,zero,002c1cf0 */
 if(lo(m,3u)==lo(m,0u)){STEP(UINT32_C(0x002c1cd4));set(m,16u,sx((uint32_t)((int32_t)lo(m,16u)>>16u)));target=sx(UINT32_C(0x002c1cf0));}else target=sx(UINT32_C(0x002c1cd8));goto dispatch;
L_002c1cd4:
 STEP(UINT32_C(0x002c1cd4)); /* 00108403 sra s0,s0,16 */
 set(m,16u,sx((uint32_t)((int32_t)lo(m,16u)>>16u)));target=sx(UINT32_C(0x002c1cd8));goto dispatch;
L_002c1cd8:
 STEP(UINT32_C(0x002c1cd8)); /* 10000023 beq zero,zero,002c1d68 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c1cdc));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000110),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002c1d68):UINT32_C(0x002c1ce0));goto dispatch;}
L_002c1cdc:
 STEP(UINT32_C(0x002c1cdc)); /* dfb00110 ld s0,0x110(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000110),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1ce0));goto dispatch;
L_002c1ce0:
 STEP(UINT32_C(0x002c1ce0)); /* 10620015 beq v1,v0,002c1d38 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002c1ce4));set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002c1d38):UINT32_C(0x002c1ce8));goto dispatch;}
L_002c1ce4:
 STEP(UINT32_C(0x002c1ce4)); /* 24110001 addiu s1,zero,1 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1ce8));goto dispatch;
L_002c1ce8:
 STEP(UINT32_C(0x002c1ce8)); /* 1000001f beq zero,zero,002c1d68 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c1cec));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000110),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002c1d68):UINT32_C(0x002c1cf0));goto dispatch;}
L_002c1cec:
 STEP(UINT32_C(0x002c1cec)); /* dfb00110 ld s0,0x110(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000110),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1cf0));goto dispatch;
L_002c1cf0:
 STEP(UINT32_C(0x002c1cf0)); /* 3c050055 lui a1,zero,0x55 */
 set(m,5u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1cf4));goto dispatch;
L_002c1cf4:
 STEP(UINT32_C(0x002c1cf4)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002c1cf8));goto dispatch;
L_002c1cf8:
 STEP(UINT32_C(0x002c1cf8)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c1cfc));goto dispatch;
L_002c1cfc:
 STEP(UINT32_C(0x002c1cfc)); /* 0c0b55a4 jal 002d5690 */
 set(m,31u,UINT64_C(0x002c1d04));STEP(UINT32_C(0x002c1d00));set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffff9aa8)));target=sx(UINT32_C(0x002d5690));goto dispatch;
L_002c1d00:
 STEP(UINT32_C(0x002c1d00)); /* 24a59aa8 addiu a1,a1,-25944 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffff9aa8)));target=sx(UINT32_C(0x002c1d04));goto dispatch;
L_002c1d04:
 STEP(UINT32_C(0x002c1d04)); /* 27b10010 addiu s1,sp,16 */
 set(m,17u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002c1d08));goto dispatch;
L_002c1d08:
 STEP(UINT32_C(0x002c1d08)); /* 03a0282d daddu a1,sp,zero */
 set(m,5u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002c1d0c));goto dispatch;
L_002c1d0c:
 STEP(UINT32_C(0x002c1d0c)); /* 0c0898ba jal 002262e8 */
 set(m,31u,UINT64_C(0x002c1d14));STEP(UINT32_C(0x002c1d10));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002262e8));goto dispatch;
L_002c1d10:
 STEP(UINT32_C(0x002c1d10)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002c1d14));goto dispatch;
L_002c1d14:
 STEP(UINT32_C(0x002c1d14)); /* 0c0b5743 jal 002d5d0c */
 set(m,31u,UINT64_C(0x002c1d1c));STEP(UINT32_C(0x002c1d18));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d5d0c));goto dispatch;
L_002c1d18:
 STEP(UINT32_C(0x002c1d18)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002c1d1c));goto dispatch;
L_002c1d1c:
 STEP(UINT32_C(0x002c1d1c)); /* 240400a0 addiu a0,zero,160 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000a0)));target=sx(UINT32_C(0x002c1d20));goto dispatch;
L_002c1d20:
 STEP(UINT32_C(0x002c1d20)); /* 0220302d daddu a2,s1,zero */
 set(m,6u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002c1d24));goto dispatch;
L_002c1d24:
 STEP(UINT32_C(0x002c1d24)); /* 24470001 addiu a3,v0,1 */
 set(m,7u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1d28));goto dispatch;
L_002c1d28:
 STEP(UINT32_C(0x002c1d28)); /* 0c0b0490 jal 002c1240 */
 set(m,31u,UINT64_C(0x002c1d30));STEP(UINT32_C(0x002c1d2c));set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1240));goto dispatch;
L_002c1d2c:
 STEP(UINT32_C(0x002c1d2c)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1d30));goto dispatch;
L_002c1d30:
 STEP(UINT32_C(0x002c1d30)); /* 1000000c beq zero,zero,002c1d64 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002c1d34));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffd850),&value32,4u);target=sx(taken?UINT32_C(0x002c1d64):UINT32_C(0x002c1d38));goto dispatch;}
L_002c1d34:
 STEP(UINT32_C(0x002c1d34)); /* af90d850 sw s0,-0x27b0(gp) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffd850),&value32,4u);target=sx(UINT32_C(0x002c1d38));goto dispatch;
L_002c1d38:
 STEP(UINT32_C(0x002c1d38)); /* 0c0aa148 jal 002a8520 */
 set(m,31u,UINT64_C(0x002c1d40));STEP(UINT32_C(0x002c1d3c));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002a8520));goto dispatch;
L_002c1d3c:
 STEP(UINT32_C(0x002c1d3c)); /* 24040002 addiu a0,zero,2 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002c1d40));goto dispatch;
L_002c1d40:
 STEP(UINT32_C(0x002c1d40)); /* 8f82d868 lw v0,-0x2798(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd868),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002c1d44));goto dispatch;
L_002c1d44:
 STEP(UINT32_C(0x002c1d44)); /* 10400003 beq v0,zero,002c1d54 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002c1d48));/* nop */target=sx(taken?UINT32_C(0x002c1d54):UINT32_C(0x002c1d4c));goto dispatch;}
L_002c1d48:
 STEP(UINT32_C(0x002c1d48)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1d4c));goto dispatch;
L_002c1d4c:
 STEP(UINT32_C(0x002c1d4c)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002c1d54));STEP(UINT32_C(0x002c1d50));/* nop */goto dispatch;
L_002c1d50:
 STEP(UINT32_C(0x002c1d50)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1d54));goto dispatch;
L_002c1d54:
 STEP(UINT32_C(0x002c1d54)); /* 0c0b0708 jal 002c1c20 */
 set(m,31u,UINT64_C(0x002c1d5c));STEP(UINT32_C(0x002c1d58));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c1c20));goto dispatch;
L_002c1d58:
 STEP(UINT32_C(0x002c1d58)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c1d5c));goto dispatch;
L_002c1d5c:
 STEP(UINT32_C(0x002c1d5c)); /* 1451fff6 bne v0,s1,002c1d38 */
 {int taken=(lo(m,2u)!=lo(m,17u));STEP(UINT32_C(0x002c1d60));/* nop */target=sx(taken?UINT32_C(0x002c1d38):UINT32_C(0x002c1d64));goto dispatch;}
L_002c1d60:
 STEP(UINT32_C(0x002c1d60)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1d64));goto dispatch;
L_002c1d64:
 STEP(UINT32_C(0x002c1d64)); /* dfb00110 ld s0,0x110(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000110),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1d68));goto dispatch;
L_002c1d68:
 STEP(UINT32_C(0x002c1d68)); /* dfb10118 ld s1,0x118(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000118),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c1d6c));goto dispatch;
L_002c1d6c:
 STEP(UINT32_C(0x002c1d6c)); /* dfbf0120 ld ra,0x120(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000120),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c1d70));goto dispatch;
L_002c1d70:
 STEP(UINT32_C(0x002c1d70)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c1d74));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000130)));goto dispatch;
L_002c1d74:
 STEP(UINT32_C(0x002c1d74)); /* 27bd0130 addiu sp,sp,304 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000130)));target=sx(UINT32_C(0x002c1d78));goto dispatch;
L_002dc830:
 STEP(UINT32_C(0x002dc830)); /* 3c07ffff lui a3,zero,0xffff */
 set(m,7u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002dc834));goto dispatch;
L_002dc834:
 STEP(UINT32_C(0x002dc834)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dc838));goto dispatch;
L_002dc838:
 STEP(UINT32_C(0x002dc838)); /* 34e7f000 ori a3,a3,0xf000 */
 set(m,7u,lo(m,7u) | UINT64_C(0xf000));target=sx(UINT32_C(0x002dc83c));goto dispatch;
L_002dc83c:
 STEP(UINT32_C(0x002dc83c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc840));goto dispatch;
L_002dc840:
 STEP(UINT32_C(0x002dc840)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc844));goto dispatch;
L_002dc844:
 m->pc=UINT32_C(0x002dc844); /* Count only after explicit processor owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,6u)+UINT32_C(0x00000000);if(!processor||!processor->cache||!processor->cache(processor->owner,UINT32_C(0x002dc844),16u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002dc848));goto dispatch;
L_002dc848:
 STEP(UINT32_C(0x002dc848)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc84c));goto dispatch;
L_002dc84c:
 m->pc=UINT32_C(0x002dc84c); /* Count only after explicit processor owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);if(!processor||!processor->taglo||!processor->taglo(processor->owner,&value32))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));++m->instructions;set(m,2u,sx(value32));target=sx(UINT32_C(0x002dc850));goto dispatch;
L_002dc850:
 STEP(UINT32_C(0x002dc850)); /* 00471024 and v0,v0,a3 */
 set(m,2u,lo(m,2u)&lo(m,7u));target=sx(UINT32_C(0x002dc854));goto dispatch;
L_002dc854:
 STEP(UINT32_C(0x002dc854)); /* 00461021 addu v0,v0,a2 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002dc858));goto dispatch;
L_002dc858:
 STEP(UINT32_C(0x002dc858)); /* 00a2182b sltu v1,a1,v0 */
 set(m,3u,lo(m,5u)<lo(m,2u));target=sx(UINT32_C(0x002dc85c));goto dispatch;
L_002dc85c:
 STEP(UINT32_C(0x002dc85c)); /* 0044102b sltu v0,v0,a0 */
 set(m,2u,lo(m,2u)<lo(m,4u));target=sx(UINT32_C(0x002dc860));goto dispatch;
L_002dc860:
 STEP(UINT32_C(0x002dc860)); /* 14400006 bne v0,zero,002dc87c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dc864));/* nop */target=sx(taken?UINT32_C(0x002dc87c):UINT32_C(0x002dc868));goto dispatch;}
L_002dc864:
 STEP(UINT32_C(0x002dc864)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc868));goto dispatch;
L_002dc868:
 STEP(UINT32_C(0x002dc868)); /* 14600004 bne v1,zero,002dc87c */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002dc86c));/* nop */target=sx(taken?UINT32_C(0x002dc87c):UINT32_C(0x002dc870));goto dispatch;}
L_002dc86c:
 STEP(UINT32_C(0x002dc86c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc870));goto dispatch;
L_002dc870:
 STEP(UINT32_C(0x002dc870)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc874));goto dispatch;
L_002dc874:
 m->pc=UINT32_C(0x002dc874); /* Count only after explicit processor owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,6u)+UINT32_C(0x00000000);if(!processor||!processor->cache||!processor->cache(processor->owner,UINT32_C(0x002dc874),22u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002dc878));goto dispatch;
L_002dc878:
 STEP(UINT32_C(0x002dc878)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc87c));goto dispatch;
L_002dc87c:
 STEP(UINT32_C(0x002dc87c)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc880));goto dispatch;
L_002dc880:
 m->pc=UINT32_C(0x002dc880); /* Count only after explicit processor owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,6u)+UINT32_C(0x00000001);if(!processor||!processor->cache||!processor->cache(processor->owner,UINT32_C(0x002dc880),16u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002dc884));goto dispatch;
L_002dc884:
 STEP(UINT32_C(0x002dc884)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc888));goto dispatch;
L_002dc888:
 m->pc=UINT32_C(0x002dc888); /* Count only after explicit processor owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);if(!processor||!processor->taglo||!processor->taglo(processor->owner,&value32))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));++m->instructions;set(m,2u,sx(value32));target=sx(UINT32_C(0x002dc88c));goto dispatch;
L_002dc88c:
 STEP(UINT32_C(0x002dc88c)); /* 00471024 and v0,v0,a3 */
 set(m,2u,lo(m,2u)&lo(m,7u));target=sx(UINT32_C(0x002dc890));goto dispatch;
L_002dc890:
 STEP(UINT32_C(0x002dc890)); /* 00461021 addu v0,v0,a2 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002dc894));goto dispatch;
L_002dc894:
 STEP(UINT32_C(0x002dc894)); /* 00a2182b sltu v1,a1,v0 */
 set(m,3u,lo(m,5u)<lo(m,2u));target=sx(UINT32_C(0x002dc898));goto dispatch;
L_002dc898:
 STEP(UINT32_C(0x002dc898)); /* 0044102b sltu v0,v0,a0 */
 set(m,2u,lo(m,2u)<lo(m,4u));target=sx(UINT32_C(0x002dc89c));goto dispatch;
L_002dc89c:
 STEP(UINT32_C(0x002dc89c)); /* 14400006 bne v0,zero,002dc8b8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dc8a0));/* nop */target=sx(taken?UINT32_C(0x002dc8b8):UINT32_C(0x002dc8a4));goto dispatch;}
L_002dc8a0:
 STEP(UINT32_C(0x002dc8a0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc8a4));goto dispatch;
L_002dc8a4:
 STEP(UINT32_C(0x002dc8a4)); /* 14600004 bne v1,zero,002dc8b8 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002dc8a8));/* nop */target=sx(taken?UINT32_C(0x002dc8b8):UINT32_C(0x002dc8ac));goto dispatch;}
L_002dc8a8:
 STEP(UINT32_C(0x002dc8a8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc8ac));goto dispatch;
L_002dc8ac:
 STEP(UINT32_C(0x002dc8ac)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc8b0));goto dispatch;
L_002dc8b0:
 m->pc=UINT32_C(0x002dc8b0); /* Count only after explicit processor owner accepts. */
 if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);address=(uint32_t)lo(m,6u)+UINT32_C(0x00000001);if(!processor||!processor->cache||!processor->cache(processor->owner,UINT32_C(0x002dc8b0),22u,address))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,address,64u,sx(m->pc));++m->instructions;target=sx(UINT32_C(0x002dc8b4));goto dispatch;
L_002dc8b4:
 STEP(UINT32_C(0x002dc8b4)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc8b8));goto dispatch;
L_002dc8b8:
 STEP(UINT32_C(0x002dc8b8)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no completion supplied. */target=sx(UINT32_C(0x002dc8bc));goto dispatch;
L_002dc8bc:
 STEP(UINT32_C(0x002dc8bc)); /* 24c60040 addiu a2,a2,64 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dc8c0));goto dispatch;
L_002dc8c0:
 STEP(UINT32_C(0x002dc8c0)); /* 28c21000 slti v0,a2,4096 */
 set(m,2u,((int64_t)lo(m,6u)<INT64_C(4096)));target=sx(UINT32_C(0x002dc8c4));goto dispatch;
L_002dc8c4:
 STEP(UINT32_C(0x002dc8c4)); /* 1440ffde bne v0,zero,002dc840 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dc8c8));/* nop */target=sx(taken?UINT32_C(0x002dc840):UINT32_C(0x002dc8cc));goto dispatch;}
L_002dc8c8:
 STEP(UINT32_C(0x002dc8c8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc8cc));goto dispatch;
L_002dc8cc:
 STEP(UINT32_C(0x002dc8cc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc8d0));/* nop */goto dispatch;
L_002dc8d0:
 STEP(UINT32_C(0x002dc8d0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc8d4));goto dispatch;
L_002dc8d8:
 STEP(UINT32_C(0x002dc8d8)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002dc8dc));goto dispatch;
L_002dc8dc:
 STEP(UINT32_C(0x002dc8dc)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dc8e0));goto dispatch;
L_002dc8e0:
 STEP(UINT32_C(0x002dc8e0)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dc8e4));goto dispatch;
L_002dc8e4:
 STEP(UINT32_C(0x002dc8e4)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002dc8e8));goto dispatch;
L_002dc8e8:
 STEP(UINT32_C(0x002dc8e8)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002dc8ec));goto dispatch;
L_002dc8ec:
 STEP(UINT32_C(0x002dc8ec)); /* 00a0882d daddu s1,a1,zero */
 set(m,17u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002dc8f0));goto dispatch;
L_002dc8f0:
 STEP(UINT32_C(0x002dc8f0)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dc8f4));goto dispatch;
L_002dc8f4:
 STEP(UINT32_C(0x002dc8f4)); /* 40106000 cop0 rs0 rts0 rd12 fn0 */
 set(m,16u,sx(m->status));target=sx(UINT32_C(0x002dc8f8));goto dispatch;
L_002dc8f8:
 STEP(UINT32_C(0x002dc8f8)); /* 3c020001 lui v0,zero,0x1 */
 set(m,2u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x002dc8fc));goto dispatch;
L_002dc8fc:
 STEP(UINT32_C(0x002dc8fc)); /* 02028024 and s0,s0,v0 */
 set(m,16u,lo(m,16u)&lo(m,2u));target=sx(UINT32_C(0x002dc900));goto dispatch;
L_002dc900:
 STEP(UINT32_C(0x002dc900)); /* 12000003 beq s0,zero,002dc910 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002dc904));/* nop */target=sx(taken?UINT32_C(0x002dc910):UINT32_C(0x002dc908));goto dispatch;}
L_002dc904:
 STEP(UINT32_C(0x002dc904)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc908));goto dispatch;
L_002dc908:
 STEP(UINT32_C(0x002dc908)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002dc910));STEP(UINT32_C(0x002dc90c));/* nop */target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002dc90c:
 STEP(UINT32_C(0x002dc90c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc910));goto dispatch;
L_002dc910:
 STEP(UINT32_C(0x002dc910)); /* 3c04ffff lui a0,zero,0xffff */
 set(m,4u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002dc914));goto dispatch;
L_002dc914:
 STEP(UINT32_C(0x002dc914)); /* 3484ffc0 ori a0,a0,0xffc0 */
 set(m,4u,lo(m,4u) | UINT64_C(0xffc0));target=sx(UINT32_C(0x002dc918));goto dispatch;
L_002dc918:
 STEP(UINT32_C(0x002dc918)); /* 02242824 and a1,s1,a0 */
 set(m,5u,lo(m,17u)&lo(m,4u));target=sx(UINT32_C(0x002dc91c));goto dispatch;
L_002dc91c:
 STEP(UINT32_C(0x002dc91c)); /* 0c0b720c jal 002dc830 */
 set(m,31u,UINT64_C(0x002dc924));STEP(UINT32_C(0x002dc920));set(m,4u,lo(m,18u)&lo(m,4u));target=sx(UINT32_C(0x002dc830));goto dispatch;
L_002dc920:
 STEP(UINT32_C(0x002dc920)); /* 02442024 and a0,s2,a0 */
 set(m,4u,lo(m,18u)&lo(m,4u));target=sx(UINT32_C(0x002dc924));goto dispatch;
L_002dc924:
 STEP(UINT32_C(0x002dc924)); /* 12000006 beq s0,zero,002dc940 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002dc928));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002dc940):UINT32_C(0x002dc92c));goto dispatch;}
L_002dc928:
 STEP(UINT32_C(0x002dc928)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dc92c));goto dispatch;
L_002dc92c:
 STEP(UINT32_C(0x002dc92c)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002dc930));goto dispatch;
L_002dc930:
 STEP(UINT32_C(0x002dc930)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dc934));goto dispatch;
L_002dc934:
 STEP(UINT32_C(0x002dc934)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dc938));goto dispatch;
L_002dc938:
 STEP(UINT32_C(0x002dc938)); /* 080b902e j 002e40b8 */
 STEP(UINT32_C(0x002dc93c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002dc93c:
 STEP(UINT32_C(0x002dc93c)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dc940));goto dispatch;
L_002dc940:
 STEP(UINT32_C(0x002dc940)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002dc944));goto dispatch;
L_002dc944:
 STEP(UINT32_C(0x002dc944)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dc948));goto dispatch;
L_002dc948:
 STEP(UINT32_C(0x002dc948)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dc94c));goto dispatch;
L_002dc94c:
 STEP(UINT32_C(0x002dc94c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc950));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002dc950:
 STEP(UINT32_C(0x002dc950)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dc954));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

int nocturneSoundPlayBankOwns(uint32_t p){return (p>=UINT32_C(0x002c18d8)&&p<UINT32_C(0x002c1938))||(p>=UINT32_C(0x002c1c20)&&p<UINT32_C(0x002c1ca0))||(p>=UINT32_C(0x002c1ca0)&&p<UINT32_C(0x002c1d78))||(p>=UINT32_C(0x002dc830)&&p<UINT32_C(0x002dc8d4))||(p>=UINT32_C(0x002dc8d8)&&p<UINT32_C(0x002dc954));}

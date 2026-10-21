#include "ps2_deci2_send.h"
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
uint32_t nocturneDeci2SendResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x80010a08):goto L_80010a08;
 case UINT32_C(0x80010a0c):goto L_80010a0c;
 case UINT32_C(0x80010a10):goto L_80010a10;
 case UINT32_C(0x80010a14):goto L_80010a14;
 case UINT32_C(0x80010a18):goto L_80010a18;
 case UINT32_C(0x80010a1c):goto L_80010a1c;
 case UINT32_C(0x80010a20):goto L_80010a20;
 case UINT32_C(0x80010a24):goto L_80010a24;
 case UINT32_C(0x80010a28):goto L_80010a28;
 case UINT32_C(0x80010a2c):goto L_80010a2c;
 case UINT32_C(0x80010a30):goto L_80010a30;
 case UINT32_C(0x80010a34):goto L_80010a34;
 case UINT32_C(0x80010a38):goto L_80010a38;
 case UINT32_C(0x80010a3c):goto L_80010a3c;
 case UINT32_C(0x80010a40):goto L_80010a40;
 case UINT32_C(0x80010a44):goto L_80010a44;
 case UINT32_C(0x80010a48):goto L_80010a48;
 case UINT32_C(0x80010a4c):goto L_80010a4c;
 case UINT32_C(0x80010a50):goto L_80010a50;
 case UINT32_C(0x80010a54):goto L_80010a54;
 case UINT32_C(0x80010a58):goto L_80010a58;
 case UINT32_C(0x80010a5c):goto L_80010a5c;
 case UINT32_C(0x80010a60):goto L_80010a60;
 case UINT32_C(0x80010a64):goto L_80010a64;
 case UINT32_C(0x80010a68):goto L_80010a68;
 case UINT32_C(0x80010a6c):goto L_80010a6c;
 case UINT32_C(0x80010a70):goto L_80010a70;
 case UINT32_C(0x80010a74):goto L_80010a74;
 case UINT32_C(0x80010a78):goto L_80010a78;
 case UINT32_C(0x80010a7c):goto L_80010a7c;
 case UINT32_C(0x80010a80):goto L_80010a80;
 case UINT32_C(0x80010a84):goto L_80010a84;
 case UINT32_C(0x80010a88):goto L_80010a88;
 case UINT32_C(0x80010a8c):goto L_80010a8c;
 case UINT32_C(0x80010a90):goto L_80010a90;
 case UINT32_C(0x80010a94):goto L_80010a94;
 case UINT32_C(0x80010a98):goto L_80010a98;
 case UINT32_C(0x80010a9c):goto L_80010a9c;
 case UINT32_C(0x80010aa0):goto L_80010aa0;
 case UINT32_C(0x80010aa4):goto L_80010aa4;
 case UINT32_C(0x80010aa8):goto L_80010aa8;
 case UINT32_C(0x80010aac):goto L_80010aac;
 case UINT32_C(0x80010ab0):goto L_80010ab0;
 case UINT32_C(0x80010ab4):goto L_80010ab4;
 case UINT32_C(0x80010ab8):goto L_80010ab8;
 case UINT32_C(0x80010abc):goto L_80010abc;
 case UINT32_C(0x80010ac0):goto L_80010ac0;
 case UINT32_C(0x80010ac4):goto L_80010ac4;
 case UINT32_C(0x80010ac8):goto L_80010ac8;
 case UINT32_C(0x80010acc):goto L_80010acc;
 case UINT32_C(0x80010ad0):goto L_80010ad0;
 case UINT32_C(0x80010ad4):goto L_80010ad4;
 case UINT32_C(0x80010ad8):goto L_80010ad8;
 case UINT32_C(0x80010adc):goto L_80010adc;
 case UINT32_C(0x80010ae0):goto L_80010ae0;
 case UINT32_C(0x80010ae4):goto L_80010ae4;
 case UINT32_C(0x80010ae8):goto L_80010ae8;
 case UINT32_C(0x80010aec):goto L_80010aec;
 case UINT32_C(0x80010af0):goto L_80010af0;
 case UINT32_C(0x80010af4):goto L_80010af4;
 case UINT32_C(0x80010af8):goto L_80010af8;
 case UINT32_C(0x80010afc):goto L_80010afc;
 case UINT32_C(0x80010b00):goto L_80010b00;
 case UINT32_C(0x80010b04):goto L_80010b04;
 case UINT32_C(0x80010b08):goto L_80010b08;
 case UINT32_C(0x80010b0c):goto L_80010b0c;
 case UINT32_C(0x80010b10):goto L_80010b10;
 case UINT32_C(0x80010b14):goto L_80010b14;
 case UINT32_C(0x80010b18):goto L_80010b18;
 case UINT32_C(0x80010b1c):goto L_80010b1c;
 case UINT32_C(0x80010b20):goto L_80010b20;
 case UINT32_C(0x80010b24):goto L_80010b24;
 case UINT32_C(0x80010b28):goto L_80010b28;
 case UINT32_C(0x80010b2c):goto L_80010b2c;
 case UINT32_C(0x80010b30):goto L_80010b30;
 case UINT32_C(0x80010b34):goto L_80010b34;
 case UINT32_C(0x80010b38):goto L_80010b38;
 case UINT32_C(0x80010b3c):goto L_80010b3c;
 case UINT32_C(0x80010b40):goto L_80010b40;
 case UINT32_C(0x80010b44):goto L_80010b44;
 case UINT32_C(0x80010b48):goto L_80010b48;
 case UINT32_C(0x80010b4c):goto L_80010b4c;
 case UINT32_C(0x80010b50):goto L_80010b50;
 case UINT32_C(0x80010b54):goto L_80010b54;
 case UINT32_C(0x80010b58):goto L_80010b58;
 case UINT32_C(0x80010b5c):goto L_80010b5c;
 case UINT32_C(0x80010b60):goto L_80010b60;
 case UINT32_C(0x80010b64):goto L_80010b64;
 case UINT32_C(0x80010b68):goto L_80010b68;
 case UINT32_C(0x80010b6c):goto L_80010b6c;
 case UINT32_C(0x80010b70):goto L_80010b70;
 case UINT32_C(0x80010b74):goto L_80010b74;
 case UINT32_C(0x80010b78):goto L_80010b78;
 case UINT32_C(0x80010b7c):goto L_80010b7c;
 case UINT32_C(0x80010b80):goto L_80010b80;
 case UINT32_C(0x80010b84):goto L_80010b84;
 case UINT32_C(0x80010b88):goto L_80010b88;
 case UINT32_C(0x80010b8c):goto L_80010b8c;
 case UINT32_C(0x80010b90):goto L_80010b90;
 case UINT32_C(0x80010b94):goto L_80010b94;
 case UINT32_C(0x80010b98):goto L_80010b98;
 case UINT32_C(0x80010b9c):goto L_80010b9c;
 case UINT32_C(0x80010ba0):goto L_80010ba0;
 case UINT32_C(0x80010ba4):goto L_80010ba4;
 case UINT32_C(0x80010ba8):goto L_80010ba8;
 case UINT32_C(0x80010bac):goto L_80010bac;
 case UINT32_C(0x80010bb0):goto L_80010bb0;
 case UINT32_C(0x80010bb4):goto L_80010bb4;
 case UINT32_C(0x80010bb8):goto L_80010bb8;
 case UINT32_C(0x80010bbc):goto L_80010bbc;
 case UINT32_C(0x80010bc0):goto L_80010bc0;
 case UINT32_C(0x80010bc4):goto L_80010bc4;
 case UINT32_C(0x80010bc8):goto L_80010bc8;
 case UINT32_C(0x80010bcc):goto L_80010bcc;
 case UINT32_C(0x80010bd0):goto L_80010bd0;
 case UINT32_C(0x80010bd4):goto L_80010bd4;
 case UINT32_C(0x80010bd8):goto L_80010bd8;
 case UINT32_C(0x80010bdc):goto L_80010bdc;
 case UINT32_C(0x80010be0):goto L_80010be0;
 case UINT32_C(0x80010be4):goto L_80010be4;
 case UINT32_C(0x80010be8):goto L_80010be8;
 case UINT32_C(0x80010bec):goto L_80010bec;
 case UINT32_C(0x80010bf0):goto L_80010bf0;
 case UINT32_C(0x80010bf4):goto L_80010bf4;
 case UINT32_C(0x80010bf8):goto L_80010bf8;
 case UINT32_C(0x80010bfc):goto L_80010bfc;
 case UINT32_C(0x80010c00):goto L_80010c00;
 case UINT32_C(0x80010c04):goto L_80010c04;
 case UINT32_C(0x80010c08):goto L_80010c08;
 case UINT32_C(0x80010c0c):goto L_80010c0c;
 case UINT32_C(0x80010c10):goto L_80010c10;
 case UINT32_C(0x80010c14):goto L_80010c14;
 case UINT32_C(0x80010c18):goto L_80010c18;
 case UINT32_C(0x80010c1c):goto L_80010c1c;
 case UINT32_C(0x80010c20):goto L_80010c20;
 case UINT32_C(0x80010c24):goto L_80010c24;
 case UINT32_C(0x80010c28):goto L_80010c28;
 case UINT32_C(0x80010c2c):goto L_80010c2c;
 case UINT32_C(0x80010c30):goto L_80010c30;
 case UINT32_C(0x80010c34):goto L_80010c34;
 case UINT32_C(0x80010c38):goto L_80010c38;
 case UINT32_C(0x80010c3c):goto L_80010c3c;
 case UINT32_C(0x80010c40):goto L_80010c40;
 case UINT32_C(0x80010c44):goto L_80010c44;
 case UINT32_C(0x80010c48):goto L_80010c48;
 case UINT32_C(0x80010c4c):goto L_80010c4c;
 case UINT32_C(0x80010c50):goto L_80010c50;
 case UINT32_C(0x80010c54):goto L_80010c54;
 case UINT32_C(0x80010c58):goto L_80010c58;
 case UINT32_C(0x80010c5c):goto L_80010c5c;
 case UINT32_C(0x80010c60):goto L_80010c60;
 case UINT32_C(0x80010c64):goto L_80010c64;
 case UINT32_C(0x80010c68):goto L_80010c68;
 case UINT32_C(0x80010c6c):goto L_80010c6c;
 case UINT32_C(0x80010c70):goto L_80010c70;
 case UINT32_C(0x80010c74):goto L_80010c74;
 case UINT32_C(0x80010c78):goto L_80010c78;
 case UINT32_C(0x80010c7c):goto L_80010c7c;
 case UINT32_C(0x80010c80):goto L_80010c80;
 case UINT32_C(0x80010c84):goto L_80010c84;
 case UINT32_C(0x80010c88):goto L_80010c88;
 case UINT32_C(0x80010c8c):goto L_80010c8c;
 case UINT32_C(0x80010c90):goto L_80010c90;
 case UINT32_C(0x80010c94):goto L_80010c94;
 case UINT32_C(0x80010c98):goto L_80010c98;
 case UINT32_C(0x80010c9c):goto L_80010c9c;
 case UINT32_C(0x80010ca0):goto L_80010ca0;
 case UINT32_C(0x80010ca4):goto L_80010ca4;
 case UINT32_C(0x80010ca8):goto L_80010ca8;
 case UINT32_C(0x80010cac):goto L_80010cac;
 case UINT32_C(0x80010cb0):goto L_80010cb0;
 case UINT32_C(0x80010cb4):goto L_80010cb4;
 case UINT32_C(0x80010cb8):goto L_80010cb8;
 case UINT32_C(0x80010cbc):goto L_80010cbc;
 case UINT32_C(0x80010cc0):goto L_80010cc0;
 case UINT32_C(0x80010cc4):goto L_80010cc4;
 case UINT32_C(0x80010cc8):goto L_80010cc8;
 case UINT32_C(0x80010ccc):goto L_80010ccc;
 case UINT32_C(0x80010cd0):goto L_80010cd0;
 case UINT32_C(0x80010cd4):goto L_80010cd4;
 case UINT32_C(0x80010cd8):goto L_80010cd8;
 case UINT32_C(0x80010cdc):goto L_80010cdc;
 case UINT32_C(0x80010ce0):goto L_80010ce0;
 case UINT32_C(0x80010ce4):goto L_80010ce4;
 case UINT32_C(0x80010ce8):goto L_80010ce8;
 case UINT32_C(0x80010cec):goto L_80010cec;
 case UINT32_C(0x80010cf0):goto L_80010cf0;
 case UINT32_C(0x80010cf4):goto L_80010cf4;
 case UINT32_C(0x80010cf8):goto L_80010cf8;
 case UINT32_C(0x80010cfc):goto L_80010cfc;
 case UINT32_C(0x80010d00):goto L_80010d00;
 case UINT32_C(0x8000bb08):goto L_8000bb08;
 case UINT32_C(0x8000bb0c):goto L_8000bb0c;
 case UINT32_C(0x8000bb10):goto L_8000bb10;
 case UINT32_C(0x8000bb14):goto L_8000bb14;
 case UINT32_C(0x8000bb18):goto L_8000bb18;
 case UINT32_C(0x8000bb1c):goto L_8000bb1c;
 case UINT32_C(0x8000bb20):goto L_8000bb20;
 case UINT32_C(0x8000bb24):goto L_8000bb24;
 case UINT32_C(0x8000bb28):goto L_8000bb28;
 case UINT32_C(0x8000bb2c):goto L_8000bb2c;
 case UINT32_C(0x8000bb30):goto L_8000bb30;
 case UINT32_C(0x8000bb34):goto L_8000bb34;
 case UINT32_C(0x8000bb38):goto L_8000bb38;
 case UINT32_C(0x8000bb3c):goto L_8000bb3c;
 case UINT32_C(0x8000bb40):goto L_8000bb40;
 case UINT32_C(0x8000bb44):goto L_8000bb44;
 case UINT32_C(0x8000bb48):goto L_8000bb48;
 case UINT32_C(0x8000bb4c):goto L_8000bb4c;
 case UINT32_C(0x8000bb50):goto L_8000bb50;
 case UINT32_C(0x8000bb54):goto L_8000bb54;
 case UINT32_C(0x8000bb58):goto L_8000bb58;
 case UINT32_C(0x8000bb5c):goto L_8000bb5c;
 case UINT32_C(0x8000bb60):goto L_8000bb60;
 case UINT32_C(0x8000bb64):goto L_8000bb64;
 case UINT32_C(0x8000bb68):goto L_8000bb68;
 case UINT32_C(0x8000bb6c):goto L_8000bb6c;
 case UINT32_C(0x8000bb70):goto L_8000bb70;
 case UINT32_C(0x8000bb74):goto L_8000bb74;
 case UINT32_C(0x8000bb78):goto L_8000bb78;
 case UINT32_C(0x8000bb7c):goto L_8000bb7c;
 case UINT32_C(0x8000bb80):goto L_8000bb80;
 case UINT32_C(0x8000bb84):goto L_8000bb84;
 case UINT32_C(0x8000bb88):goto L_8000bb88;
 case UINT32_C(0x8000bb8c):goto L_8000bb8c;
 case UINT32_C(0x8000bb90):goto L_8000bb90;
 case UINT32_C(0x8000bb94):goto L_8000bb94;
 case UINT32_C(0x8000bb98):goto L_8000bb98;
 case UINT32_C(0x8000bb9c):goto L_8000bb9c;
 case UINT32_C(0x8000bba0):goto L_8000bba0;
 case UINT32_C(0x8000bba4):goto L_8000bba4;
 case UINT32_C(0x8000bba8):goto L_8000bba8;
 case UINT32_C(0x8000bbac):goto L_8000bbac;
 case UINT32_C(0x8000bbb0):goto L_8000bbb0;
 case UINT32_C(0x8000bbb4):goto L_8000bbb4;
 case UINT32_C(0x8000bbb8):goto L_8000bbb8;
 case UINT32_C(0x8000bbbc):goto L_8000bbbc;
 case UINT32_C(0x8000bbc0):goto L_8000bbc0;
 case UINT32_C(0x8000bab8):goto L_8000bab8;
 case UINT32_C(0x8000babc):goto L_8000babc;
 case UINT32_C(0x8000d518):goto L_8000d518;
 case UINT32_C(0x8000d51c):goto L_8000d51c;
 case UINT32_C(0x8000d520):goto L_8000d520;
 case UINT32_C(0x8000d524):goto L_8000d524;
 case UINT32_C(0x8000d528):goto L_8000d528;
 case UINT32_C(0x8000d52c):goto L_8000d52c;
 case UINT32_C(0x8000d530):goto L_8000d530;
 case UINT32_C(0x8000d534):goto L_8000d534;
 case UINT32_C(0x8000d538):goto L_8000d538;
 case UINT32_C(0x8000d53c):goto L_8000d53c;
 case UINT32_C(0x8000d540):goto L_8000d540;
 case UINT32_C(0x8000d544):goto L_8000d544;
 case UINT32_C(0x8000d548):goto L_8000d548;
 case UINT32_C(0x8000d54c):goto L_8000d54c;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_80010a08:
 STEP(UINT32_C(0x80010a08)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x80010a0c));goto dispatch;
L_80010a0c:
 STEP(UINT32_C(0x80010a0c)); /* 00052e00 sll a1,a1,24 */
 set(m,5u,sx((uint32_t)lo(m,5u)<<24u));target=sx(UINT32_C(0x80010a10));goto dispatch;
L_80010a10:
 STEP(UINT32_C(0x80010a10)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80010a14));goto dispatch;
L_80010a14:
 STEP(UINT32_C(0x80010a14)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80010a18));goto dispatch;
L_80010a18:
 STEP(UINT32_C(0x80010a18)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80010a1c));goto dispatch;
L_80010a1c:
 STEP(UINT32_C(0x80010a1c)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80010a20));goto dispatch;
L_80010a20:
 STEP(UINT32_C(0x80010a20)); /* 0c002ea0 jal 8000ba80 */
 set(m,31u,UINT64_C(0x80010a28));STEP(UINT32_C(0x80010a24));set(m,16u,sx((uint32_t)((int32_t)lo(m,5u)>>24u)));target=sx(UINT32_C(0x8000ba80));goto dispatch;
L_80010a24:
 STEP(UINT32_C(0x80010a24)); /* 00058603 sra s0,a1,24 */
 set(m,16u,sx((uint32_t)((int32_t)lo(m,5u)>>24u)));target=sx(UINT32_C(0x80010a28));goto dispatch;
L_80010a28:
 STEP(UINT32_C(0x80010a28)); /* 14400003 bne v0,zero,80010a38 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80010a2c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000048)));target=sx(taken?UINT32_C(0x80010a38):UINT32_C(0x80010a30));goto dispatch;}
L_80010a2c:
 STEP(UINT32_C(0x80010a2c)); /* 24020048 addiu v0,zero,72 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000048)));target=sx(UINT32_C(0x80010a30));goto dispatch;
L_80010a30:
 STEP(UINT32_C(0x80010a30)); /* 1000002c beq zero,zero,80010ae4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80010a34));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(taken?UINT32_C(0x80010ae4):UINT32_C(0x80010a38));goto dispatch;}
L_80010a34:
 STEP(UINT32_C(0x80010a34)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x80010a38));goto dispatch;
L_80010a38:
 STEP(UINT32_C(0x80010a38)); /* 16020005 bne s0,v0,80010a50 */
 {int taken=(lo(m,16u)!=lo(m,2u));STEP(UINT32_C(0x80010a3c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000049)));target=sx(taken?UINT32_C(0x80010a50):UINT32_C(0x80010a40));goto dispatch;}
L_80010a3c:
 STEP(UINT32_C(0x80010a3c)); /* 24020049 addiu v0,zero,73 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000049)));target=sx(UINT32_C(0x80010a40));goto dispatch;
L_80010a40:
 STEP(UINT32_C(0x80010a40)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010a44));goto dispatch;
L_80010a44:
 STEP(UINT32_C(0x80010a44)); /* 8c430b54 lw v1,0xb54(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000b54),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80010a48));goto dispatch;
L_80010a48:
 STEP(UINT32_C(0x80010a48)); /* 10600007 beq v1,zero,80010a68 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x80010a4c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000049)));target=sx(taken?UINT32_C(0x80010a68):UINT32_C(0x80010a50));goto dispatch;}
L_80010a4c:
 STEP(UINT32_C(0x80010a4c)); /* 24020049 addiu v0,zero,73 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000049)));target=sx(UINT32_C(0x80010a50));goto dispatch;
L_80010a50:
 STEP(UINT32_C(0x80010a50)); /* 16020009 bne s0,v0,80010a78 */
 {int taken=(lo(m,16u)!=lo(m,2u));STEP(UINT32_C(0x80010a54));set(m,2u,sx(UINT32_C(0x80020000)));target=sx(taken?UINT32_C(0x80010a78):UINT32_C(0x80010a58));goto dispatch;}
L_80010a54:
 STEP(UINT32_C(0x80010a54)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010a58));goto dispatch;
L_80010a58:
 STEP(UINT32_C(0x80010a58)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010a5c));goto dispatch;
L_80010a5c:
 STEP(UINT32_C(0x80010a5c)); /* 8c430b58 lw v1,0xb58(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000b58),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80010a60));goto dispatch;
L_80010a60:
 STEP(UINT32_C(0x80010a60)); /* 14600005 bne v1,zero,80010a78 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x80010a64));set(m,2u,sx(UINT32_C(0x80020000)));target=sx(taken?UINT32_C(0x80010a78):UINT32_C(0x80010a68));goto dispatch;}
L_80010a64:
 STEP(UINT32_C(0x80010a64)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010a68));goto dispatch;
L_80010a68:
 STEP(UINT32_C(0x80010a68)); /* 1000001e beq zero,zero,80010ae4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80010a6c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff6)));target=sx(taken?UINT32_C(0x80010ae4):UINT32_C(0x80010a70));goto dispatch;}
L_80010a6c:
 STEP(UINT32_C(0x80010a6c)); /* 2402fff6 addiu v0,zero,-10 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff6)));target=sx(UINT32_C(0x80010a70));goto dispatch;
L_80010a70:
 STEP(UINT32_C(0x80010a70)); /* 1000000d beq zero,zero,80010aa8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80010a74));set(m,5u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,6u)));target=sx(taken?UINT32_C(0x80010aa8):UINT32_C(0x80010a78));goto dispatch;}
L_80010a74:
 STEP(UINT32_C(0x80010a74)); /* 00a62821 addu a1,a1,a2 */
 set(m,5u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x80010a78));goto dispatch;
L_80010a78:
 STEP(UINT32_C(0x80010a78)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80010a7c));goto dispatch;
L_80010a7c:
 STEP(UINT32_C(0x80010a7c)); /* 24461040 addiu a2,v0,4160 */
 set(m,6u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00001040)));target=sx(UINT32_C(0x80010a80));goto dispatch;
L_80010a80:
 STEP(UINT32_C(0x80010a80)); /* 24c40008 addiu a0,a2,8 */
 set(m,4u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x80010a84));goto dispatch;
L_80010a84:
 STEP(UINT32_C(0x80010a84)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80010a88));goto dispatch;
L_80010a88:
 STEP(UINT32_C(0x80010a88)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010a8c));goto dispatch;
L_80010a8c:
 STEP(UINT32_C(0x80010a8c)); /* 1040fff8 beq v0,zero,80010a70 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80010a90));set(m,5u,sx((uint32_t)lo(m,3u)<<4u));target=sx(taken?UINT32_C(0x80010a70):UINT32_C(0x80010a94));goto dispatch;}
L_80010a90:
 STEP(UINT32_C(0x80010a90)); /* 00032900 sll a1,v1,4 */
 set(m,5u,sx((uint32_t)lo(m,3u)<<4u));target=sx(UINT32_C(0x80010a94));goto dispatch;
L_80010a94:
 STEP(UINT32_C(0x80010a94)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80010a98));goto dispatch;
L_80010a98:
 STEP(UINT32_C(0x80010a98)); /* 28620020 slti v0,v1,32 */
 set(m,2u,((int64_t)lo(m,3u)<INT64_C(32)));target=sx(UINT32_C(0x80010a9c));goto dispatch;
L_80010a9c:
 STEP(UINT32_C(0x80010a9c)); /* 1440fffa bne v0,zero,80010a88 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80010aa0));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x80010a88):UINT32_C(0x80010aa4));goto dispatch;}
L_80010aa0:
 STEP(UINT32_C(0x80010aa0)); /* 24840010 addiu a0,a0,16 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80010aa4));goto dispatch;
L_80010aa4:
 STEP(UINT32_C(0x80010aa4)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80010aa8));goto dispatch;
L_80010aa8:
 STEP(UINT32_C(0x80010aa8)); /* 54a00003 bnel a1,zero,80010ab8 */
 if(lo(m,5u)!=lo(m,0u)){STEP(UINT32_C(0x80010aac));{uint8_t byte=(uint8_t)lo(m,16u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&byte,1u);}target=sx(UINT32_C(0x80010ab8));}else target=sx(UINT32_C(0x80010ab0));goto dispatch;
L_80010aac:
 STEP(UINT32_C(0x80010aac)); /* a0b0000c sb s0,0xc(a1) */
 {uint8_t byte=(uint8_t)lo(m,16u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&byte,1u);}target=sx(UINT32_C(0x80010ab0));goto dispatch;
L_80010ab0:
 STEP(UINT32_C(0x80010ab0)); /* 1000000c beq zero,zero,80010ae4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80010ab4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff5)));target=sx(taken?UINT32_C(0x80010ae4):UINT32_C(0x80010ab8));goto dispatch;}
L_80010ab4:
 STEP(UINT32_C(0x80010ab4)); /* 2402fff5 addiu v0,zero,-11 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff5)));target=sx(UINT32_C(0x80010ab8));goto dispatch;
L_80010ab8:
 STEP(UINT32_C(0x80010ab8)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010abc));goto dispatch;
L_80010abc:
 STEP(UINT32_C(0x80010abc)); /* acb10008 sw s1,0x8(a1) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x80010ac0));goto dispatch;
L_80010ac0:
 STEP(UINT32_C(0x80010ac0)); /* 0c003546 jal 8000d518 */
 set(m,31u,UINT64_C(0x80010ac8));STEP(UINT32_C(0x80010ac4));READ((uint32_t)lo(m,2u)+UINT32_C(0x00001034),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000d518));goto dispatch;
L_80010ac4:
 STEP(UINT32_C(0x80010ac4)); /* 8c441034 lw a0,0x1034(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00001034),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010ac8));goto dispatch;
L_80010ac8:
 STEP(UINT32_C(0x80010ac8)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010acc));goto dispatch;
L_80010acc:
 STEP(UINT32_C(0x80010acc)); /* 8c430b50 lw v1,0xb50(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000b50),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80010ad0));goto dispatch;
L_80010ad0:
 STEP(UINT32_C(0x80010ad0)); /* 14600004 bne v1,zero,80010ae4 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x80010ad4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x80010ae4):UINT32_C(0x80010ad8));goto dispatch;}
L_80010ad4:
 STEP(UINT32_C(0x80010ad4)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80010ad8));goto dispatch;
L_80010ad8:
 STEP(UINT32_C(0x80010ad8)); /* 0c0042be jal 80010af8 */
 set(m,31u,UINT64_C(0x80010ae0));STEP(UINT32_C(0x80010adc));/* nop */target=sx(UINT32_C(0x80010af8));goto dispatch;
L_80010adc:
 STEP(UINT32_C(0x80010adc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80010ae0));goto dispatch;
L_80010ae0:
 STEP(UINT32_C(0x80010ae0)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80010ae4));goto dispatch;
L_80010ae4:
 STEP(UINT32_C(0x80010ae4)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80010ae8));goto dispatch;
L_80010ae8:
 STEP(UINT32_C(0x80010ae8)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x80010aec));goto dispatch;
L_80010aec:
 STEP(UINT32_C(0x80010aec)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x80010af0));goto dispatch;
L_80010af0:
 STEP(UINT32_C(0x80010af0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80010af4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_80010af4:
 STEP(UINT32_C(0x80010af4)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x80010af8));goto dispatch;
L_80010af8:
 STEP(UINT32_C(0x80010af8)); /* 27bdff60 addiu sp,sp,-160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff60)));target=sx(UINT32_C(0x80010afc));goto dispatch;
L_80010afc:
 STEP(UINT32_C(0x80010afc)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010b00));goto dispatch;
L_80010b00:
 STEP(UINT32_C(0x80010b00)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x80010b04));goto dispatch;
L_80010b04:
 STEP(UINT32_C(0x80010b04)); /* 24641240 addiu a0,v1,4672 */
 set(m,4u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00001240)));target=sx(UINT32_C(0x80010b08));goto dispatch;
L_80010b08:
 STEP(UINT32_C(0x80010b08)); /* ffbf0090 sd ra,0x90(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x80010b0c));goto dispatch;
L_80010b0c:
 STEP(UINT32_C(0x80010b0c)); /* ffbe0080 sd s8,0x80(sp) */
 value64=lo(m,30u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x80010b10));goto dispatch;
L_80010b10:
 STEP(UINT32_C(0x80010b10)); /* ffb70070 sd s7,0x70(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x80010b14));goto dispatch;
L_80010b14:
 STEP(UINT32_C(0x80010b14)); /* ffb60060 sd s6,0x60(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x80010b18));goto dispatch;
L_80010b18:
 STEP(UINT32_C(0x80010b18)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x80010b1c));goto dispatch;
L_80010b1c:
 STEP(UINT32_C(0x80010b1c)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x80010b20));goto dispatch;
L_80010b20:
 STEP(UINT32_C(0x80010b20)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80010b24));goto dispatch;
L_80010b24:
 STEP(UINT32_C(0x80010b24)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80010b28));goto dispatch;
L_80010b28:
 STEP(UINT32_C(0x80010b28)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80010b2c));goto dispatch;
L_80010b2c:
 STEP(UINT32_C(0x80010b2c)); /* 8c820010 lw v0,0x10(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010b30));goto dispatch;
L_80010b30:
 STEP(UINT32_C(0x80010b30)); /* 14400058 bne v0,zero,80010c94 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80010b34));set(m,21u,lo(m,3u)+lo(m,0u));target=sx(taken?UINT32_C(0x80010c94):UINT32_C(0x80010b38));goto dispatch;}
L_80010b34:
 STEP(UINT32_C(0x80010b34)); /* 0060a82d daddu s5,v1,zero */
 set(m,21u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80010b38));goto dispatch;
L_80010b38:
 STEP(UINT32_C(0x80010b38)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010b3c));goto dispatch;
L_80010b3c:
 STEP(UINT32_C(0x80010b3c)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010b40));goto dispatch;
L_80010b40:
 STEP(UINT32_C(0x80010b40)); /* 245e1030 addiu s8,v0,4144 */
 set(m,30u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00001030)));target=sx(UINT32_C(0x80010b44));goto dispatch;
L_80010b44:
 STEP(UINT32_C(0x80010b44)); /* 24771040 addiu s7,v1,4160 */
 set(m,23u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00001040)));target=sx(UINT32_C(0x80010b48));goto dispatch;
L_80010b48:
 STEP(UINT32_C(0x80010b48)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80010b4c));goto dispatch;
L_80010b4c:
 STEP(UINT32_C(0x80010b4c)); /* 02a0a02d daddu s4,s5,zero */
 set(m,20u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x80010b50));goto dispatch;
L_80010b50:
 STEP(UINT32_C(0x80010b50)); /* 02a0b02d daddu s6,s5,zero */
 set(m,22u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x80010b54));goto dispatch;
L_80010b54:
 STEP(UINT32_C(0x80010b54)); /* 8e831240 lw v1,0x1240(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00001240),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80010b58));goto dispatch;
L_80010b58:
 STEP(UINT32_C(0x80010b58)); /* 54600027 bnel v1,zero,80010bf8 */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x80010b5c));READ((uint32_t)lo(m,19u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010bf8));}else target=sx(UINT32_C(0x80010b60));goto dispatch;
L_80010b5c:
 STEP(UINT32_C(0x80010b5c)); /* 8e62000c lw v0,0xc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010b60));goto dispatch;
L_80010b60:
 STEP(UINT32_C(0x80010b60)); /* 8fc30004 lw v1,0x4(s8) */
 READ((uint32_t)lo(m,30u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80010b64));goto dispatch;
L_80010b64:
 STEP(UINT32_C(0x80010b64)); /* 147e0006 bne v1,s8,80010b80 */
 {int taken=(lo(m,3u)!=lo(m,30u));STEP(UINT32_C(0x80010b68));set(m,4u,sx(UINT32_C(0x80020000)));target=sx(taken?UINT32_C(0x80010b80):UINT32_C(0x80010b6c));goto dispatch;}
L_80010b68:
 STEP(UINT32_C(0x80010b68)); /* 3c048002 lui a0,zero,0x8002 */
 set(m,4u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010b6c));goto dispatch;
L_80010b6c:
 STEP(UINT32_C(0x80010b6c)); /* 8c821030 lw v0,0x1030(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00001030),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010b70));goto dispatch;
L_80010b70:
 STEP(UINT32_C(0x80010b70)); /* 14430004 bne v0,v1,80010b84 */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x80010b74));set(m,3u,sx(UINT32_C(0x80020000)));target=sx(taken?UINT32_C(0x80010b84):UINT32_C(0x80010b78));goto dispatch;}
L_80010b74:
 STEP(UINT32_C(0x80010b74)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010b78));goto dispatch;
L_80010b78:
 STEP(UINT32_C(0x80010b78)); /* 1000001b beq zero,zero,80010be8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80010b7c));set(m,3u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x80010be8):UINT32_C(0x80010b80));goto dispatch;}
L_80010b7c:
 STEP(UINT32_C(0x80010b7c)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80010b80));goto dispatch;
L_80010b80:
 STEP(UINT32_C(0x80010b80)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010b84));goto dispatch;
L_80010b84:
 STEP(UINT32_C(0x80010b84)); /* 94620b60 lhu v0,0xb60(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000b60),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x80010b88));goto dispatch;
L_80010b88:
 STEP(UINT32_C(0x80010b88)); /* 10400016 beq v0,zero,80010be4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80010b8c));READ((uint32_t)lo(m,4u)+UINT32_C(0x00001030),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x80010be4):UINT32_C(0x80010b90));goto dispatch;}
L_80010b8c:
 STEP(UINT32_C(0x80010b8c)); /* 8c901030 lw s0,0x1030(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00001030),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x80010b90));goto dispatch;
L_80010b90:
 STEP(UINT32_C(0x80010b90)); /* 0c002eb0 jal 8000bac0 */
 set(m,31u,UINT64_C(0x80010b98));STEP(UINT32_C(0x80010b94));set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000bac0));goto dispatch;
L_80010b94:
 STEP(UINT32_C(0x80010b94)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80010b98));goto dispatch;
L_80010b98:
 STEP(UINT32_C(0x80010b98)); /* 0040882d daddu s1,v0,zero */
 set(m,17u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80010b9c));goto dispatch;
L_80010b9c:
 STEP(UINT32_C(0x80010b9c)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80010ba0));goto dispatch;
L_80010ba0:
 STEP(UINT32_C(0x80010ba0)); /* 24521030 addiu s2,v0,4144 */
 set(m,18u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00001030)));target=sx(UINT32_C(0x80010ba4));goto dispatch;
L_80010ba4:
 STEP(UINT32_C(0x80010ba4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80010ba8));goto dispatch;
L_80010ba8:
 STEP(UINT32_C(0x80010ba8)); /* 12120008 beq s0,s2,80010bcc */
 {int taken=(lo(m,16u)==lo(m,18u));STEP(UINT32_C(0x80010bac));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x80010bcc):UINT32_C(0x80010bb0));goto dispatch;}
L_80010bac:
 STEP(UINT32_C(0x80010bac)); /* 8e040008 lw a0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010bb0));goto dispatch;
L_80010bb0:
 STEP(UINT32_C(0x80010bb0)); /* 1091000d beq a0,s1,80010be8 */
 {int taken=(lo(m,4u)==lo(m,17u));STEP(UINT32_C(0x80010bb4));set(m,3u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x80010be8):UINT32_C(0x80010bb8));goto dispatch;}
L_80010bb4:
 STEP(UINT32_C(0x80010bb4)); /* 0200182d daddu v1,s0,zero */
 set(m,3u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80010bb8));goto dispatch;
L_80010bb8:
 STEP(UINT32_C(0x80010bb8)); /* 0c002eae jal 8000bab8 */
 set(m,31u,UINT64_C(0x80010bc0));STEP(UINT32_C(0x80010bbc));/* nop */target=sx(UINT32_C(0x8000bab8));goto dispatch;
L_80010bbc:
 STEP(UINT32_C(0x80010bbc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80010bc0));goto dispatch;
L_80010bc0:
 STEP(UINT32_C(0x80010bc0)); /* 5040fff9 beql v0,zero,80010ba8 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x80010bc4));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x80010ba8));}else target=sx(UINT32_C(0x80010bc8));goto dispatch;
L_80010bc4:
 STEP(UINT32_C(0x80010bc4)); /* 8e100000 lw s0,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x80010bc8));goto dispatch;
L_80010bc8:
 STEP(UINT32_C(0x80010bc8)); /* 8e040008 lw a0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010bcc));goto dispatch;
L_80010bcc:
 STEP(UINT32_C(0x80010bcc)); /* 10910006 beq a0,s1,80010be8 */
 {int taken=(lo(m,4u)==lo(m,17u));STEP(UINT32_C(0x80010bd0));set(m,3u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x80010be8):UINT32_C(0x80010bd4));goto dispatch;}
L_80010bd0:
 STEP(UINT32_C(0x80010bd0)); /* 0200182d daddu v1,s0,zero */
 set(m,3u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80010bd4));goto dispatch;
L_80010bd4:
 STEP(UINT32_C(0x80010bd4)); /* 0c002eae jal 8000bab8 */
 set(m,31u,UINT64_C(0x80010bdc));STEP(UINT32_C(0x80010bd8));/* nop */target=sx(UINT32_C(0x8000bab8));goto dispatch;
L_80010bd8:
 STEP(UINT32_C(0x80010bd8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80010bdc));goto dispatch;
L_80010bdc:
 STEP(UINT32_C(0x80010bdc)); /* 10400002 beq v0,zero,80010be8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80010be0));set(m,3u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x80010be8):UINT32_C(0x80010be4));goto dispatch;}
L_80010be0:
 STEP(UINT32_C(0x80010be0)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80010be4));goto dispatch;
L_80010be4:
 STEP(UINT32_C(0x80010be4)); /* 0200182d daddu v1,s0,zero */
 set(m,3u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80010be8));goto dispatch;
L_80010be8:
 STEP(UINT32_C(0x80010be8)); /* 1060002a beq v1,zero,80010c94 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x80010bec));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00001240),&value32,4u);target=sx(taken?UINT32_C(0x80010c94):UINT32_C(0x80010bf0));goto dispatch;}
L_80010bec:
 STEP(UINT32_C(0x80010bec)); /* aea31240 sw v1,0x1240(s5) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00001240),&value32,4u);target=sx(UINT32_C(0x80010bf0));goto dispatch;
L_80010bf0:
 STEP(UINT32_C(0x80010bf0)); /* 1000001f beq zero,zero,80010c70 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80010bf4));READ((uint32_t)lo(m,22u)+UINT32_C(0x00001240),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x80010c70):UINT32_C(0x80010bf8));goto dispatch;}
L_80010bf4:
 STEP(UINT32_C(0x80010bf4)); /* 8ec21240 lw v0,0x1240(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00001240),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010bf8));goto dispatch;
L_80010bf8:
 STEP(UINT32_C(0x80010bf8)); /* 54400009 bnel v0,zero,80010c20 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x80010bfc));READ((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010c20));}else target=sx(UINT32_C(0x80010c00));goto dispatch;
L_80010bfc:
 STEP(UINT32_C(0x80010bfc)); /* 8e620004 lw v0,0x4(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010c00));goto dispatch;
L_80010c00:
 STEP(UINT32_C(0x80010c00)); /* 8c640008 lw a0,0x8(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010c04));goto dispatch;
L_80010c04:
 STEP(UINT32_C(0x80010c04)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80010c08));goto dispatch;
L_80010c08:
 STEP(UINT32_C(0x80010c08)); /* 0c002ec2 jal 8000bb08 */
 set(m,31u,UINT64_C(0x80010c10));STEP(UINT32_C(0x80010c0c));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x8000bb08));goto dispatch;
L_80010c0c:
 STEP(UINT32_C(0x80010c0c)); /* 24060004 addiu a2,zero,4 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x80010c10));goto dispatch;
L_80010c10:
 STEP(UINT32_C(0x80010c10)); /* 8e62000c lw v0,0xc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010c14));goto dispatch;
L_80010c14:
 STEP(UINT32_C(0x80010c14)); /* 10400004 beq v0,zero,80010c28 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80010c18));/* nop */target=sx(taken?UINT32_C(0x80010c28):UINT32_C(0x80010c1c));goto dispatch;}
L_80010c18:
 STEP(UINT32_C(0x80010c18)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80010c1c));goto dispatch;
L_80010c1c:
 STEP(UINT32_C(0x80010c1c)); /* 8e620004 lw v0,0x4(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010c20));goto dispatch;
L_80010c20:
 STEP(UINT32_C(0x80010c20)); /* 04410013 regimm1 v0,80010c70 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x80010c24));READ((uint32_t)lo(m,22u)+UINT32_C(0x00001240),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x80010c70):UINT32_C(0x80010c28));goto dispatch;}
L_80010c24:
 STEP(UINT32_C(0x80010c24)); /* 8ec21240 lw v0,0x1240(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00001240),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010c28));goto dispatch;
L_80010c28:
 STEP(UINT32_C(0x80010c28)); /* 0c00354c jal 8000d530 */
 set(m,31u,UINT64_C(0x80010c30));STEP(UINT32_C(0x80010c2c));READ((uint32_t)lo(m,20u)+UINT32_C(0x00001240),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000d530));goto dispatch;
L_80010c2c:
 STEP(UINT32_C(0x80010c2c)); /* 8e841240 lw a0,0x1240(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00001240),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010c30));goto dispatch;
L_80010c30:
 STEP(UINT32_C(0x80010c30)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80010c34));goto dispatch;
L_80010c34:
 STEP(UINT32_C(0x80010c34)); /* ae821240 sw v0,0x1240(s4) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,20u)+UINT32_C(0x00001240),&value32,4u);target=sx(UINT32_C(0x80010c38));goto dispatch;
L_80010c38:
 STEP(UINT32_C(0x80010c38)); /* 26e30008 addiu v1,s7,8 */
 set(m,3u,sx((uint32_t)lo(m,23u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x80010c3c));goto dispatch;
L_80010c3c:
 STEP(UINT32_C(0x80010c3c)); /* 02e0102d daddu v0,s7,zero */
 set(m,2u,lo(m,23u)+lo(m,0u));target=sx(UINT32_C(0x80010c40));goto dispatch;
L_80010c40:
 STEP(UINT32_C(0x80010c40)); /* 2404001f addiu a0,zero,31 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x80010c44));goto dispatch;
L_80010c44:
 STEP(UINT32_C(0x80010c44)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80010c48));goto dispatch;
L_80010c48:
 STEP(UINT32_C(0x80010c48)); /* 50a20001 beql a1,v0,80010c50 */
 if(lo(m,5u)==lo(m,2u)){STEP(UINT32_C(0x80010c4c));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80010c50));}else target=sx(UINT32_C(0x80010c50));goto dispatch;
L_80010c4c:
 STEP(UINT32_C(0x80010c4c)); /* ac600000 sw zero,0x0(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80010c50));goto dispatch;
L_80010c50:
 STEP(UINT32_C(0x80010c50)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80010c54));goto dispatch;
L_80010c54:
 STEP(UINT32_C(0x80010c54)); /* 2484ffff addiu a0,a0,-1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80010c58));goto dispatch;
L_80010c58:
 STEP(UINT32_C(0x80010c58)); /* 0481fffb regimm1 a0,80010c48 */
 {int taken=((int64_t)lo(m,4u)>=0);STEP(UINT32_C(0x80010c5c));set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x80010c48):UINT32_C(0x80010c60));goto dispatch;}
L_80010c5c:
 STEP(UINT32_C(0x80010c5c)); /* 24420010 addiu v0,v0,16 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80010c60));goto dispatch;
L_80010c60:
 STEP(UINT32_C(0x80010c60)); /* ae801240 sw zero,0x1240(s4) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,20u)+UINT32_C(0x00001240),&value32,4u);target=sx(UINT32_C(0x80010c64));goto dispatch;
L_80010c64:
 STEP(UINT32_C(0x80010c64)); /* ae60000c sw zero,0xc(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x80010c68));goto dispatch;
L_80010c68:
 STEP(UINT32_C(0x80010c68)); /* ae600004 sw zero,0x4(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80010c6c));goto dispatch;
L_80010c6c:
 STEP(UINT32_C(0x80010c6c)); /* 8ec21240 lw v0,0x1240(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00001240),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010c70));goto dispatch;
L_80010c70:
 STEP(UINT32_C(0x80010c70)); /* 10400005 beq v0,zero,80010c88 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80010c74));set(m,16u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00001240)));target=sx(taken?UINT32_C(0x80010c88):UINT32_C(0x80010c78));goto dispatch;}
L_80010c74:
 STEP(UINT32_C(0x80010c74)); /* 26d01240 addiu s0,s6,4672 */
 set(m,16u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00001240)));target=sx(UINT32_C(0x80010c78));goto dispatch;
L_80010c78:
 STEP(UINT32_C(0x80010c78)); /* 8c440008 lw a0,0x8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010c7c));goto dispatch;
L_80010c7c:
 STEP(UINT32_C(0x80010c7c)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80010c80));goto dispatch;
L_80010c80:
 STEP(UINT32_C(0x80010c80)); /* 0c002ec2 jal 8000bb08 */
 set(m,31u,UINT64_C(0x80010c88));STEP(UINT32_C(0x80010c84));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x8000bb08));goto dispatch;
L_80010c84:
 STEP(UINT32_C(0x80010c84)); /* 24060003 addiu a2,zero,3 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x80010c88));goto dispatch;
L_80010c88:
 STEP(UINT32_C(0x80010c88)); /* 8e020010 lw v0,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010c8c));goto dispatch;
L_80010c8c:
 STEP(UINT32_C(0x80010c8c)); /* 1040ffb2 beq v0,zero,80010b58 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80010c90));READ((uint32_t)lo(m,20u)+UINT32_C(0x00001240),&value32,4u);set(m,3u,sx(value32));target=sx(taken?UINT32_C(0x80010b58):UINT32_C(0x80010c94));goto dispatch;}
L_80010c90:
 STEP(UINT32_C(0x80010c90)); /* 8e831240 lw v1,0x1240(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00001240),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80010c94));goto dispatch;
L_80010c94:
 STEP(UINT32_C(0x80010c94)); /* 26b01240 addiu s0,s5,4672 */
 set(m,16u,sx((uint32_t)lo(m,21u)+UINT32_C(0x00001240)));target=sx(UINT32_C(0x80010c98));goto dispatch;
L_80010c98:
 STEP(UINT32_C(0x80010c98)); /* 8e050010 lw a1,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80010c9c));goto dispatch;
L_80010c9c:
 STEP(UINT32_C(0x80010c9c)); /* 10a0000e beq a1,zero,80010cd8 */
 {int taken=(lo(m,5u)==lo(m,0u));STEP(UINT32_C(0x80010ca0));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80010cd8):UINT32_C(0x80010ca4));goto dispatch;}
L_80010ca0:
 STEP(UINT32_C(0x80010ca0)); /* dfbf0090 ld ra,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80010ca4));goto dispatch;
L_80010ca4:
 STEP(UINT32_C(0x80010ca4)); /* 8e020018 lw v0,0x18(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010ca8));goto dispatch;
L_80010ca8:
 STEP(UINT32_C(0x80010ca8)); /* 1440000c bne v0,zero,80010cdc */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80010cac));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,30u,value64);target=sx(taken?UINT32_C(0x80010cdc):UINT32_C(0x80010cb0));goto dispatch;}
L_80010cac:
 STEP(UINT32_C(0x80010cac)); /* dfbe0080 ld s8,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,30u,value64);target=sx(UINT32_C(0x80010cb0));goto dispatch;
L_80010cb0:
 STEP(UINT32_C(0x80010cb0)); /* 8e020004 lw v0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80010cb4));goto dispatch;
L_80010cb4:
 STEP(UINT32_C(0x80010cb4)); /* 1440000a bne v0,zero,80010ce0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80010cb8));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,23u,value64);target=sx(taken?UINT32_C(0x80010ce0):UINT32_C(0x80010cbc));goto dispatch;}
L_80010cb8:
 STEP(UINT32_C(0x80010cb8)); /* dfb70070 ld s7,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x80010cbc));goto dispatch;
L_80010cbc:
 STEP(UINT32_C(0x80010cbc)); /* 8e040014 lw a0,0x14(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010cc0));goto dispatch;
L_80010cc0:
 STEP(UINT32_C(0x80010cc0)); /* 0c00341a jal 8000d068 */
 set(m,31u,UINT64_C(0x80010cc8));STEP(UINT32_C(0x80010cc4));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x8000d068));goto dispatch;
L_80010cc4:
 STEP(UINT32_C(0x80010cc4)); /* 8e060008 lw a2,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x80010cc8));goto dispatch;
L_80010cc8:
 STEP(UINT32_C(0x80010cc8)); /* 10400002 beq v0,zero,80010cd4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80010ccc));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x80010cd4):UINT32_C(0x80010cd0));goto dispatch;}
L_80010ccc:
 STEP(UINT32_C(0x80010ccc)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80010cd0));goto dispatch;
L_80010cd0:
 STEP(UINT32_C(0x80010cd0)); /* ae020018 sw v0,0x18(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x80010cd4));goto dispatch;
L_80010cd4:
 STEP(UINT32_C(0x80010cd4)); /* dfbf0090 ld ra,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80010cd8));goto dispatch;
L_80010cd8:
 STEP(UINT32_C(0x80010cd8)); /* dfbe0080 ld s8,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,30u,value64);target=sx(UINT32_C(0x80010cdc));goto dispatch;
L_80010cdc:
 STEP(UINT32_C(0x80010cdc)); /* dfb70070 ld s7,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x80010ce0));goto dispatch;
L_80010ce0:
 STEP(UINT32_C(0x80010ce0)); /* dfb60060 ld s6,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x80010ce4));goto dispatch;
L_80010ce4:
 STEP(UINT32_C(0x80010ce4)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x80010ce8));goto dispatch;
L_80010ce8:
 STEP(UINT32_C(0x80010ce8)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x80010cec));goto dispatch;
L_80010cec:
 STEP(UINT32_C(0x80010cec)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x80010cf0));goto dispatch;
L_80010cf0:
 STEP(UINT32_C(0x80010cf0)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x80010cf4));goto dispatch;
L_80010cf4:
 STEP(UINT32_C(0x80010cf4)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x80010cf8));goto dispatch;
L_80010cf8:
 STEP(UINT32_C(0x80010cf8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x80010cfc));goto dispatch;
L_80010cfc:
 STEP(UINT32_C(0x80010cfc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80010d00));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));goto dispatch;
L_80010d00:
 STEP(UINT32_C(0x80010d00)); /* 27bd00a0 addiu sp,sp,160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));target=sx(UINT32_C(0x80010d04));goto dispatch;
L_8000bb08:
 STEP(UINT32_C(0x8000bb08)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x8000bb0c));goto dispatch;
L_8000bb0c:
 STEP(UINT32_C(0x8000bb0c)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000bb10));goto dispatch;
L_8000bb10:
 STEP(UINT32_C(0x8000bb10)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x8000bb14));goto dispatch;
L_8000bb14:
 STEP(UINT32_C(0x8000bb14)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000bb18));goto dispatch;
L_8000bb18:
 STEP(UINT32_C(0x8000bb18)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x8000bb1c));goto dispatch;
L_8000bb1c:
 STEP(UINT32_C(0x8000bb1c)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000bb20));goto dispatch;
L_8000bb20:
 STEP(UINT32_C(0x8000bb20)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x8000bb24));goto dispatch;
L_8000bb24:
 STEP(UINT32_C(0x8000bb24)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000bb28));goto dispatch;
L_8000bb28:
 STEP(UINT32_C(0x8000bb28)); /* 0040982d daddu s3,v0,zero */
 set(m,19u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000bb2c));goto dispatch;
L_8000bb2c:
 STEP(UINT32_C(0x8000bb2c)); /* ac510b50 sw s1,0xb50(v0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000b50),&value32,4u);target=sx(UINT32_C(0x8000bb30));goto dispatch;
L_8000bb30:
 STEP(UINT32_C(0x8000bb30)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x8000bb34));goto dispatch;
L_8000bb34:
 STEP(UINT32_C(0x8000bb34)); /* 0c002eae jal 8000bab8 */
 set(m,31u,UINT64_C(0x8000bb3c));STEP(UINT32_C(0x8000bb38));set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x8000bab8));goto dispatch;
L_8000bb38:
 STEP(UINT32_C(0x8000bb38)); /* 00a0902d daddu s2,a1,zero */
 set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x8000bb3c));goto dispatch;
L_8000bb3c:
 STEP(UINT32_C(0x8000bb3c)); /* 1040000d beq v0,zero,8000bb74 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x8000bb40));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(taken?UINT32_C(0x8000bb74):UINT32_C(0x8000bb44));goto dispatch;}
L_8000bb40:
 STEP(UINT32_C(0x8000bb40)); /* 2403000c addiu v1,zero,12 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000bb44));goto dispatch;
L_8000bb44:
 STEP(UINT32_C(0x8000bb44)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000bb48));goto dispatch;
L_8000bb48:
 STEP(UINT32_C(0x8000bb48)); /* 02031818 mult_rd v1,s0,v1 */
 {int64_t product;if(lo(m,16u)!=sx((uint32_t)lo(m,16u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,16u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x8000bb4c));goto dispatch;
L_8000bb4c:
 STEP(UINT32_C(0x8000bb4c)); /* 24420b60 addiu v0,v0,2912 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000b60)));target=sx(UINT32_C(0x8000bb50));goto dispatch;
L_8000bb50:
 STEP(UINT32_C(0x8000bb50)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x8000bb54));goto dispatch;
L_8000bb54:
 STEP(UINT32_C(0x8000bb54)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x8000bb58));goto dispatch;
L_8000bb58:
 STEP(UINT32_C(0x8000bb58)); /* 00434021 addu t0,v0,v1 */
 set(m,8u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x8000bb5c));goto dispatch;
L_8000bb5c:
 STEP(UINT32_C(0x8000bb5c)); /* 0100102d daddu v0,t0,zero */
 set(m,2u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x8000bb60));goto dispatch;
L_8000bb60:
 STEP(UINT32_C(0x8000bb60)); /* 8c470008 lw a3,0x8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x8000bb64));goto dispatch;
L_8000bb64:
 STEP(UINT32_C(0x8000bb64)); /* 00e0f809 jalr ra,a3 */
 target=sx((uint32_t)lo(m,7u));set(m,31u,UINT64_C(0x8000bb6c));STEP(UINT32_C(0x8000bb68));READ((uint32_t)lo(m,8u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));goto dispatch;
L_8000bb68:
 STEP(UINT32_C(0x8000bb68)); /* 8d060004 lw a2,0x4(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x8000bb6c));goto dispatch;
L_8000bb6c:
 STEP(UINT32_C(0x8000bb6c)); /* 1000000e beq zero,zero,8000bba8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bb70));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000b50),&value32,4u);target=sx(taken?UINT32_C(0x8000bba8):UINT32_C(0x8000bb74));goto dispatch;}
L_8000bb70:
 STEP(UINT32_C(0x8000bb70)); /* ae600b50 sw zero,0xb50(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000b50),&value32,4u);target=sx(UINT32_C(0x8000bb74));goto dispatch;
L_8000bb74:
 STEP(UINT32_C(0x8000bb74)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000bb78));goto dispatch;
L_8000bb78:
 STEP(UINT32_C(0x8000bb78)); /* 02031818 mult_rd v1,s0,v1 */
 {int64_t product;if(lo(m,16u)!=sx((uint32_t)lo(m,16u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,16u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x8000bb7c));goto dispatch;
L_8000bb7c:
 STEP(UINT32_C(0x8000bb7c)); /* 24420b60 addiu v0,v0,2912 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000b60)));target=sx(UINT32_C(0x8000bb80));goto dispatch;
L_8000bb80:
 STEP(UINT32_C(0x8000bb80)); /* 3c058001 lui a1,zero,0x8001 */
 set(m,5u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000bb84));goto dispatch;
L_8000bb84:
 STEP(UINT32_C(0x8000bb84)); /* 0220302d daddu a2,s1,zero */
 set(m,6u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x8000bb88));goto dispatch;
L_8000bb88:
 STEP(UINT32_C(0x8000bb88)); /* 8ca424e4 lw a0,0x24e4(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x000024e4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bb8c));goto dispatch;
L_8000bb8c:
 STEP(UINT32_C(0x8000bb8c)); /* 0240382d daddu a3,s2,zero */
 set(m,7u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x8000bb90));goto dispatch;
L_8000bb90:
 STEP(UINT32_C(0x8000bb90)); /* 00434821 addu t1,v0,v1 */
 set(m,9u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x8000bb94));goto dispatch;
L_8000bb94:
 STEP(UINT32_C(0x8000bb94)); /* 0120102d daddu v0,t1,zero */
 set(m,2u,lo(m,9u)+lo(m,0u));target=sx(UINT32_C(0x8000bb98));goto dispatch;
L_8000bb98:
 STEP(UINT32_C(0x8000bb98)); /* 8d280004 lw t0,0x4(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x8000bb9c));goto dispatch;
L_8000bb9c:
 STEP(UINT32_C(0x8000bb9c)); /* 0c000a10 jal 80002840 */
 set(m,31u,UINT64_C(0x8000bba4));STEP(UINT32_C(0x8000bba0));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80002840));goto dispatch;
L_8000bba0:
 STEP(UINT32_C(0x8000bba0)); /* 8c450008 lw a1,0x8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000bba4));goto dispatch;
L_8000bba4:
 STEP(UINT32_C(0x8000bba4)); /* ae600b50 sw zero,0xb50(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000b50),&value32,4u);target=sx(UINT32_C(0x8000bba8));goto dispatch;
L_8000bba8:
 STEP(UINT32_C(0x8000bba8)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000bbac));goto dispatch;
L_8000bbac:
 STEP(UINT32_C(0x8000bbac)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x8000bbb0));goto dispatch;
L_8000bbb0:
 STEP(UINT32_C(0x8000bbb0)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x8000bbb4));goto dispatch;
L_8000bbb4:
 STEP(UINT32_C(0x8000bbb4)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x8000bbb8));goto dispatch;
L_8000bbb8:
 STEP(UINT32_C(0x8000bbb8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x8000bbbc));goto dispatch;
L_8000bbbc:
 STEP(UINT32_C(0x8000bbbc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000bbc0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_8000bbc0:
 STEP(UINT32_C(0x8000bbc0)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x8000bbc4));goto dispatch;
L_8000bab8:
 STEP(UINT32_C(0x8000bab8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000babc));set(m,2u,((int64_t)lo(m,4u)<INT64_C(5)));goto dispatch;
L_8000babc:
 STEP(UINT32_C(0x8000babc)); /* 28820005 slti v0,a0,5 */
 set(m,2u,((int64_t)lo(m,4u)<INT64_C(5)));target=sx(UINT32_C(0x8000bac0));goto dispatch;
L_8000d518:
 STEP(UINT32_C(0x8000d518)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000d51c));goto dispatch;
L_8000d51c:
 STEP(UINT32_C(0x8000d51c)); /* aca40004 sw a0,0x4(a1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x8000d520));goto dispatch;
L_8000d520:
 STEP(UINT32_C(0x8000d520)); /* aca20000 sw v0,0x0(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x8000d524));goto dispatch;
L_8000d524:
 STEP(UINT32_C(0x8000d524)); /* ac450004 sw a1,0x4(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x8000d528));goto dispatch;
L_8000d528:
 STEP(UINT32_C(0x8000d528)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000d52c));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_8000d52c:
 STEP(UINT32_C(0x8000d52c)); /* ac850000 sw a1,0x0(a0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x8000d530));goto dispatch;
L_8000d530:
 STEP(UINT32_C(0x8000d530)); /* 8c830000 lw v1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x8000d534));goto dispatch;
L_8000d534:
 STEP(UINT32_C(0x8000d534)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000d538));goto dispatch;
L_8000d538:
 STEP(UINT32_C(0x8000d538)); /* 8c860004 lw a2,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x8000d53c));goto dispatch;
L_8000d53c:
 STEP(UINT32_C(0x8000d53c)); /* acc30000 sw v1,0x0(a2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x8000d540));goto dispatch;
L_8000d540:
 STEP(UINT32_C(0x8000d540)); /* 8c850000 lw a1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000d544));goto dispatch;
L_8000d544:
 STEP(UINT32_C(0x8000d544)); /* 8c830004 lw v1,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x8000d548));goto dispatch;
L_8000d548:
 STEP(UINT32_C(0x8000d548)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000d54c));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);goto dispatch;
L_8000d54c:
 STEP(UINT32_C(0x8000d54c)); /* aca30004 sw v1,0x4(a1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x8000d550));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

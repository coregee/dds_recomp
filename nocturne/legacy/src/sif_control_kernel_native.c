#include "sif_control_kernel_native.h"
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
uint32_t nocturneSifControlKernelResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x80000940):goto L_80000940;
 case UINT32_C(0x80000944):goto L_80000944;
 case UINT32_C(0x80000948):goto L_80000948;
 case UINT32_C(0x8000094c):goto L_8000094c;
 case UINT32_C(0x80000950):goto L_80000950;
 case UINT32_C(0x80000954):goto L_80000954;
 case UINT32_C(0x80000958):goto L_80000958;
 case UINT32_C(0x8000095c):goto L_8000095c;
 case UINT32_C(0x80000960):goto L_80000960;
 case UINT32_C(0x80000964):goto L_80000964;
 case UINT32_C(0x80000968):goto L_80000968;
 case UINT32_C(0x8000096c):goto L_8000096c;
 case UINT32_C(0x80001c78):goto L_80001c78;
 case UINT32_C(0x80001c7c):goto L_80001c7c;
 case UINT32_C(0x80001c80):goto L_80001c80;
 case UINT32_C(0x80001c84):goto L_80001c84;
 case UINT32_C(0x80001c88):goto L_80001c88;
 case UINT32_C(0x80001c8c):goto L_80001c8c;
 case UINT32_C(0x80001c90):goto L_80001c90;
 case UINT32_C(0x80001b10):goto L_80001b10;
 case UINT32_C(0x80001b14):goto L_80001b14;
 case UINT32_C(0x80001b18):goto L_80001b18;
 case UINT32_C(0x80001b1c):goto L_80001b1c;
 case UINT32_C(0x80001b20):goto L_80001b20;
 case UINT32_C(0x80001b24):goto L_80001b24;
 case UINT32_C(0x80001b28):goto L_80001b28;
 case UINT32_C(0x80001b2c):goto L_80001b2c;
 case UINT32_C(0x80001b30):goto L_80001b30;
 case UINT32_C(0x80001b34):goto L_80001b34;
 case UINT32_C(0x80001b38):goto L_80001b38;
 case UINT32_C(0x80001b3c):goto L_80001b3c;
 case UINT32_C(0x80001b40):goto L_80001b40;
 case UINT32_C(0x80001b44):goto L_80001b44;
 case UINT32_C(0x80001b48):goto L_80001b48;
 case UINT32_C(0x80001b4c):goto L_80001b4c;
 case UINT32_C(0x80001b50):goto L_80001b50;
 case UINT32_C(0x80001b54):goto L_80001b54;
 case UINT32_C(0x80001b58):goto L_80001b58;
 case UINT32_C(0x80001b5c):goto L_80001b5c;
 case UINT32_C(0x80001b60):goto L_80001b60;
 case UINT32_C(0x80001b64):goto L_80001b64;
 case UINT32_C(0x80001b68):goto L_80001b68;
 case UINT32_C(0x80001b6c):goto L_80001b6c;
 case UINT32_C(0x80001b70):goto L_80001b70;
 case UINT32_C(0x80001b74):goto L_80001b74;
 case UINT32_C(0x80001b78):goto L_80001b78;
 case UINT32_C(0x80001b7c):goto L_80001b7c;
 case UINT32_C(0x80001b80):goto L_80001b80;
 case UINT32_C(0x80001b84):goto L_80001b84;
 case UINT32_C(0x80001b88):goto L_80001b88;
 case UINT32_C(0x80001b8c):goto L_80001b8c;
 case UINT32_C(0x80001b90):goto L_80001b90;
 case UINT32_C(0x80001b94):goto L_80001b94;
 case UINT32_C(0x80001b98):goto L_80001b98;
 case UINT32_C(0x80001b9c):goto L_80001b9c;
 case UINT32_C(0x80001ba0):goto L_80001ba0;
 case UINT32_C(0x80001ba4):goto L_80001ba4;
 case UINT32_C(0x80001ba8):goto L_80001ba8;
 case UINT32_C(0x80001bac):goto L_80001bac;
 case UINT32_C(0x80001bb0):goto L_80001bb0;
 case UINT32_C(0x80001bb4):goto L_80001bb4;
 case UINT32_C(0x80001bb8):goto L_80001bb8;
 case UINT32_C(0x80001bbc):goto L_80001bbc;
 case UINT32_C(0x80001bc0):goto L_80001bc0;
 case UINT32_C(0x80001bc4):goto L_80001bc4;
 case UINT32_C(0x80001bc8):goto L_80001bc8;
 case UINT32_C(0x80001bcc):goto L_80001bcc;
 case UINT32_C(0x80001bd0):goto L_80001bd0;
 case UINT32_C(0x80001bd4):goto L_80001bd4;
 case UINT32_C(0x80001bd8):goto L_80001bd8;
 case UINT32_C(0x80001bdc):goto L_80001bdc;
 case UINT32_C(0x80001be0):goto L_80001be0;
 case UINT32_C(0x80001be4):goto L_80001be4;
 case UINT32_C(0x80001be8):goto L_80001be8;
 case UINT32_C(0x80001bec):goto L_80001bec;
 case UINT32_C(0x80001bf0):goto L_80001bf0;
 case UINT32_C(0x80001bf4):goto L_80001bf4;
 case UINT32_C(0x80001bf8):goto L_80001bf8;
 case UINT32_C(0x80001bfc):goto L_80001bfc;
 case UINT32_C(0x80001c00):goto L_80001c00;
 case UINT32_C(0x80001c04):goto L_80001c04;
 case UINT32_C(0x80001c08):goto L_80001c08;
 case UINT32_C(0x80001c0c):goto L_80001c0c;
 case UINT32_C(0x80001c10):goto L_80001c10;
 case UINT32_C(0x80001c14):goto L_80001c14;
 case UINT32_C(0x80001c18):goto L_80001c18;
 case UINT32_C(0x80001c1c):goto L_80001c1c;
 case UINT32_C(0x80001c20):goto L_80001c20;
 case UINT32_C(0x80001c24):goto L_80001c24;
 case UINT32_C(0x80001c28):goto L_80001c28;
 case UINT32_C(0x80001c2c):goto L_80001c2c;
 case UINT32_C(0x80001c30):goto L_80001c30;
 case UINT32_C(0x80001c34):goto L_80001c34;
 case UINT32_C(0x80001c38):goto L_80001c38;
 case UINT32_C(0x80001c3c):goto L_80001c3c;
 case UINT32_C(0x80001c40):goto L_80001c40;
 case UINT32_C(0x80001c44):goto L_80001c44;
 case UINT32_C(0x80001c48):goto L_80001c48;
 case UINT32_C(0x80001c4c):goto L_80001c4c;
 case UINT32_C(0x80001c50):goto L_80001c50;
 case UINT32_C(0x80001c54):goto L_80001c54;
 case UINT32_C(0x80001c58):goto L_80001c58;
 case UINT32_C(0x80001c5c):goto L_80001c5c;
 case UINT32_C(0x80001c60):goto L_80001c60;
 case UINT32_C(0x80001c64):goto L_80001c64;
 case UINT32_C(0x80001c68):goto L_80001c68;
 case UINT32_C(0x80001c6c):goto L_80001c6c;
 case UINT32_C(0x80001c70):goto L_80001c70;
 case UINT32_C(0x80001c74):goto L_80001c74;
 case UINT32_C(0x800015a0):goto L_800015a0;
 case UINT32_C(0x800015a4):goto L_800015a4;
 case UINT32_C(0x800015a8):goto L_800015a8;
 case UINT32_C(0x800015ac):goto L_800015ac;
 case UINT32_C(0x800015b0):goto L_800015b0;
 case UINT32_C(0x800015b4):goto L_800015b4;
 case UINT32_C(0x800015b8):goto L_800015b8;
 case UINT32_C(0x800015bc):goto L_800015bc;
 case UINT32_C(0x800015c0):goto L_800015c0;
 case UINT32_C(0x800015c4):goto L_800015c4;
 case UINT32_C(0x800015c8):goto L_800015c8;
 case UINT32_C(0x800015cc):goto L_800015cc;
 case UINT32_C(0x800015d0):goto L_800015d0;
 case UINT32_C(0x800015d4):goto L_800015d4;
 case UINT32_C(0x800015d8):goto L_800015d8;
 case UINT32_C(0x800015dc):goto L_800015dc;
 case UINT32_C(0x800015e0):goto L_800015e0;
 case UINT32_C(0x800015e4):goto L_800015e4;
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
 case UINT32_C(0x80005b08):goto L_80005b08;
 case UINT32_C(0x80005b0c):goto L_80005b0c;
 case UINT32_C(0x80005b10):goto L_80005b10;
 case UINT32_C(0x80005b14):goto L_80005b14;
 case UINT32_C(0x80005b18):goto L_80005b18;
 case UINT32_C(0x80005b1c):goto L_80005b1c;
 case UINT32_C(0x80005b20):goto L_80005b20;
 case UINT32_C(0x800062a0):goto L_800062a0;
 case UINT32_C(0x800062a4):goto L_800062a4;
 case UINT32_C(0x800062a8):goto L_800062a8;
 case UINT32_C(0x800062ac):goto L_800062ac;
 case UINT32_C(0x800062b0):goto L_800062b0;
 case UINT32_C(0x800062b4):goto L_800062b4;
 case UINT32_C(0x800062b8):goto L_800062b8;
 case UINT32_C(0x800062bc):goto L_800062bc;
 case UINT32_C(0x800062c0):goto L_800062c0;
 case UINT32_C(0x800062c4):goto L_800062c4;
 case UINT32_C(0x800062c8):goto L_800062c8;
 case UINT32_C(0x800062cc):goto L_800062cc;
 case UINT32_C(0x800062d0):goto L_800062d0;
 case UINT32_C(0x80006b60):goto L_80006b60;
 case UINT32_C(0x80006b64):goto L_80006b64;
 case UINT32_C(0x80006b68):goto L_80006b68;
 case UINT32_C(0x80006b6c):goto L_80006b6c;
 case UINT32_C(0x80006b70):goto L_80006b70;
 case UINT32_C(0x80006b74):goto L_80006b74;
 case UINT32_C(0x80006b78):goto L_80006b78;
 case UINT32_C(0x80006b7c):goto L_80006b7c;
 case UINT32_C(0x80006b80):goto L_80006b80;
 case UINT32_C(0x80006b84):goto L_80006b84;
 case UINT32_C(0x80006b88):goto L_80006b88;
 case UINT32_C(0x80006b8c):goto L_80006b8c;
 case UINT32_C(0x80006b90):goto L_80006b90;
 case UINT32_C(0x80006b94):goto L_80006b94;
 case UINT32_C(0x80006b98):goto L_80006b98;
 case UINT32_C(0x80006b9c):goto L_80006b9c;
 case UINT32_C(0x80006ba0):goto L_80006ba0;
 case UINT32_C(0x80006ba4):goto L_80006ba4;
 case UINT32_C(0x80006ba8):goto L_80006ba8;
 case UINT32_C(0x80006bac):goto L_80006bac;
 case UINT32_C(0x80006bb0):goto L_80006bb0;
 case UINT32_C(0x80006bb4):goto L_80006bb4;
 case UINT32_C(0x80006bb8):goto L_80006bb8;
 case UINT32_C(0x80006bbc):goto L_80006bbc;
 case UINT32_C(0x80006bc0):goto L_80006bc0;
 case UINT32_C(0x80006bc4):goto L_80006bc4;
 case UINT32_C(0x80006bc8):goto L_80006bc8;
 case UINT32_C(0x80006bcc):goto L_80006bcc;
 case UINT32_C(0x80006bd0):goto L_80006bd0;
 case UINT32_C(0x80006bd4):goto L_80006bd4;
 case UINT32_C(0x80006bd8):goto L_80006bd8;
 case UINT32_C(0x80006bdc):goto L_80006bdc;
 case UINT32_C(0x80006be0):goto L_80006be0;
 case UINT32_C(0x80006be4):goto L_80006be4;
 case UINT32_C(0x80006be8):goto L_80006be8;
 case UINT32_C(0x80006bec):goto L_80006bec;
 case UINT32_C(0x80006bf0):goto L_80006bf0;
 case UINT32_C(0x80006bf4):goto L_80006bf4;
 case UINT32_C(0x80006bf8):goto L_80006bf8;
 case UINT32_C(0x80006bfc):goto L_80006bfc;
 case UINT32_C(0x80006c00):goto L_80006c00;
 case UINT32_C(0x80006c04):goto L_80006c04;
 case UINT32_C(0x80006c08):goto L_80006c08;
 case UINT32_C(0x80006c0c):goto L_80006c0c;
 case UINT32_C(0x80006c10):goto L_80006c10;
 case UINT32_C(0x80006c14):goto L_80006c14;
 case UINT32_C(0x80006c18):goto L_80006c18;
 case UINT32_C(0x80006c1c):goto L_80006c1c;
 case UINT32_C(0x80006c20):goto L_80006c20;
 case UINT32_C(0x80006c24):goto L_80006c24;
 case UINT32_C(0x80006c28):goto L_80006c28;
 case UINT32_C(0x80006c2c):goto L_80006c2c;
 case UINT32_C(0x80006c30):goto L_80006c30;
 case UINT32_C(0x80006c34):goto L_80006c34;
 case UINT32_C(0x80006c38):goto L_80006c38;
 case UINT32_C(0x80006c3c):goto L_80006c3c;
 case UINT32_C(0x80006c40):goto L_80006c40;
 case UINT32_C(0x80006c44):goto L_80006c44;
 case UINT32_C(0x80006c48):goto L_80006c48;
 case UINT32_C(0x80006c4c):goto L_80006c4c;
 case UINT32_C(0x80006c50):goto L_80006c50;
 case UINT32_C(0x80006c54):goto L_80006c54;
 case UINT32_C(0x80006c58):goto L_80006c58;
 case UINT32_C(0x80006c5c):goto L_80006c5c;
 case UINT32_C(0x80006c60):goto L_80006c60;
 case UINT32_C(0x80006c64):goto L_80006c64;
 case UINT32_C(0x80006c68):goto L_80006c68;
 case UINT32_C(0x80006c6c):goto L_80006c6c;
 case UINT32_C(0x80006c70):goto L_80006c70;
 case UINT32_C(0x80006c74):goto L_80006c74;
 case UINT32_C(0x80006c78):goto L_80006c78;
 case UINT32_C(0x80006c7c):goto L_80006c7c;
 case UINT32_C(0x80006c80):goto L_80006c80;
 case UINT32_C(0x80006c84):goto L_80006c84;
 case UINT32_C(0x80006c88):goto L_80006c88;
 case UINT32_C(0x80006c8c):goto L_80006c8c;
 case UINT32_C(0x80006c90):goto L_80006c90;
 case UINT32_C(0x80006c94):goto L_80006c94;
 case UINT32_C(0x80006c98):goto L_80006c98;
 case UINT32_C(0x80006c9c):goto L_80006c9c;
 case UINT32_C(0x80006ca0):goto L_80006ca0;
 case UINT32_C(0x80006ca4):goto L_80006ca4;
 case UINT32_C(0x80006ca8):goto L_80006ca8;
 case UINT32_C(0x80006cac):goto L_80006cac;
 case UINT32_C(0x80006cb0):goto L_80006cb0;
 case UINT32_C(0x80006cb4):goto L_80006cb4;
 case UINT32_C(0x80006cb8):goto L_80006cb8;
 case UINT32_C(0x80006cbc):goto L_80006cbc;
 case UINT32_C(0x80006cc0):goto L_80006cc0;
 case UINT32_C(0x80006cc4):goto L_80006cc4;
 case UINT32_C(0x80006cc8):goto L_80006cc8;
 case UINT32_C(0x80006ccc):goto L_80006ccc;
 case UINT32_C(0x80006cd0):goto L_80006cd0;
 case UINT32_C(0x80006cd4):goto L_80006cd4;
 case UINT32_C(0x80006cd8):goto L_80006cd8;
 case UINT32_C(0x80006cdc):goto L_80006cdc;
 case UINT32_C(0x80006ce0):goto L_80006ce0;
 case UINT32_C(0x80006ac8):goto L_80006ac8;
 case UINT32_C(0x80006acc):goto L_80006acc;
 case UINT32_C(0x80006ad0):goto L_80006ad0;
 case UINT32_C(0x80006ad4):goto L_80006ad4;
 case UINT32_C(0x80006ad8):goto L_80006ad8;
 case UINT32_C(0x80006adc):goto L_80006adc;
 case UINT32_C(0x80006ae0):goto L_80006ae0;
 case UINT32_C(0x80006ae4):goto L_80006ae4;
 case UINT32_C(0x80006a80):goto L_80006a80;
 case UINT32_C(0x80006a84):goto L_80006a84;
 case UINT32_C(0x80006a88):goto L_80006a88;
 case UINT32_C(0x80006a8c):goto L_80006a8c;
 case UINT32_C(0x80006a90):goto L_80006a90;
 case UINT32_C(0x80006a94):goto L_80006a94;
 case UINT32_C(0x80006a98):goto L_80006a98;
 case UINT32_C(0x80006a38):goto L_80006a38;
 case UINT32_C(0x80006a3c):goto L_80006a3c;
 case UINT32_C(0x80006a40):goto L_80006a40;
 case UINT32_C(0x80006a44):goto L_80006a44;
 case UINT32_C(0x80006a48):goto L_80006a48;
 case UINT32_C(0x80006a4c):goto L_80006a4c;
 case UINT32_C(0x80006a50):goto L_80006a50;
 case UINT32_C(0x80006aa0):goto L_80006aa0;
 case UINT32_C(0x80006aa4):goto L_80006aa4;
 case UINT32_C(0x80006aa8):goto L_80006aa8;
 case UINT32_C(0x80006aac):goto L_80006aac;
 case UINT32_C(0x80006ab0):goto L_80006ab0;
 case UINT32_C(0x80006ab4):goto L_80006ab4;
 case UINT32_C(0x80006ab8):goto L_80006ab8;
 case UINT32_C(0x80006abc):goto L_80006abc;
 case UINT32_C(0x80006ac0):goto L_80006ac0;
 case UINT32_C(0x80006ae8):goto L_80006ae8;
 case UINT32_C(0x80006aec):goto L_80006aec;
 case UINT32_C(0x80006af0):goto L_80006af0;
 case UINT32_C(0x80006af4):goto L_80006af4;
 case UINT32_C(0x80006af8):goto L_80006af8;
 case UINT32_C(0x80006a58):goto L_80006a58;
 case UINT32_C(0x80006a5c):goto L_80006a5c;
 case UINT32_C(0x80006a60):goto L_80006a60;
 case UINT32_C(0x80006a64):goto L_80006a64;
 case UINT32_C(0x80006a68):goto L_80006a68;
 case UINT32_C(0x80006a6c):goto L_80006a6c;
 case UINT32_C(0x80006a70):goto L_80006a70;
 case UINT32_C(0x80006a74):goto L_80006a74;
 case UINT32_C(0x80006a78):goto L_80006a78;
 case UINT32_C(0x80005e58):goto L_80005e58;
 case UINT32_C(0x80005e5c):goto L_80005e5c;
 case UINT32_C(0x80005e60):goto L_80005e60;
 case UINT32_C(0x80005e64):goto L_80005e64;
 case UINT32_C(0x80005e68):goto L_80005e68;
 case UINT32_C(0x80005e6c):goto L_80005e6c;
 case UINT32_C(0x80005e70):goto L_80005e70;
 case UINT32_C(0x80005e74):goto L_80005e74;
 case UINT32_C(0x80005e78):goto L_80005e78;
 case UINT32_C(0x80005e7c):goto L_80005e7c;
 case UINT32_C(0x80005e80):goto L_80005e80;
 case UINT32_C(0x80005e84):goto L_80005e84;
 case UINT32_C(0x80005e88):goto L_80005e88;
 case UINT32_C(0x80005e8c):goto L_80005e8c;
 case UINT32_C(0x80005e90):goto L_80005e90;
 case UINT32_C(0x80005e94):goto L_80005e94;
 case UINT32_C(0x80005e98):goto L_80005e98;
 case UINT32_C(0x80005e9c):goto L_80005e9c;
 case UINT32_C(0x80005ea0):goto L_80005ea0;
 case UINT32_C(0x80005ea4):goto L_80005ea4;
 case UINT32_C(0x80005ea8):goto L_80005ea8;
 case UINT32_C(0x80005eac):goto L_80005eac;
 case UINT32_C(0x80005eb0):goto L_80005eb0;
 case UINT32_C(0x80005eb4):goto L_80005eb4;
 case UINT32_C(0x80005eb8):goto L_80005eb8;
 case UINT32_C(0x80005ebc):goto L_80005ebc;
 case UINT32_C(0x80005ec0):goto L_80005ec0;
 case UINT32_C(0x80005ec4):goto L_80005ec4;
 case UINT32_C(0x80005ec8):goto L_80005ec8;
 case UINT32_C(0x80005ecc):goto L_80005ecc;
 case UINT32_C(0x80005ed0):goto L_80005ed0;
 case UINT32_C(0x80005ed4):goto L_80005ed4;
 case UINT32_C(0x80005ed8):goto L_80005ed8;
 case UINT32_C(0x80005edc):goto L_80005edc;
 case UINT32_C(0x80005ee0):goto L_80005ee0;
 case UINT32_C(0x80005ee4):goto L_80005ee4;
 case UINT32_C(0x80005ee8):goto L_80005ee8;
 case UINT32_C(0x80005eec):goto L_80005eec;
 case UINT32_C(0x80005ef0):goto L_80005ef0;
 case UINT32_C(0x80005ef4):goto L_80005ef4;
 case UINT32_C(0x80005ef8):goto L_80005ef8;
 case UINT32_C(0x80005efc):goto L_80005efc;
 case UINT32_C(0x80005f00):goto L_80005f00;
 case UINT32_C(0x80005f04):goto L_80005f04;
 case UINT32_C(0x80005f08):goto L_80005f08;
 case UINT32_C(0x80005f0c):goto L_80005f0c;
 case UINT32_C(0x80005f10):goto L_80005f10;
 case UINT32_C(0x80005f14):goto L_80005f14;
 case UINT32_C(0x80005f18):goto L_80005f18;
 case UINT32_C(0x80005f1c):goto L_80005f1c;
 case UINT32_C(0x80005f20):goto L_80005f20;
 case UINT32_C(0x80005f24):goto L_80005f24;
 case UINT32_C(0x80005f28):goto L_80005f28;
 case UINT32_C(0x80005f2c):goto L_80005f2c;
 case UINT32_C(0x80005f30):goto L_80005f30;
 case UINT32_C(0x80005d78):goto L_80005d78;
 case UINT32_C(0x80005d7c):goto L_80005d7c;
 case UINT32_C(0x80005d80):goto L_80005d80;
 case UINT32_C(0x80005d84):goto L_80005d84;
 case UINT32_C(0x80005d88):goto L_80005d88;
 case UINT32_C(0x80005d8c):goto L_80005d8c;
 case UINT32_C(0x80005d90):goto L_80005d90;
 case UINT32_C(0x80005d94):goto L_80005d94;
 case UINT32_C(0x80005d98):goto L_80005d98;
 case UINT32_C(0x80005d9c):goto L_80005d9c;
 case UINT32_C(0x80005da0):goto L_80005da0;
 case UINT32_C(0x80005da4):goto L_80005da4;
 case UINT32_C(0x80005da8):goto L_80005da8;
 case UINT32_C(0x80005dac):goto L_80005dac;
 case UINT32_C(0x80005db0):goto L_80005db0;
 case UINT32_C(0x80005db4):goto L_80005db4;
 case UINT32_C(0x80005db8):goto L_80005db8;
 case UINT32_C(0x80005dbc):goto L_80005dbc;
 case UINT32_C(0x80005dc0):goto L_80005dc0;
 case UINT32_C(0x80005dc4):goto L_80005dc4;
 case UINT32_C(0x80005dc8):goto L_80005dc8;
 case UINT32_C(0x80005dcc):goto L_80005dcc;
 case UINT32_C(0x80005dd0):goto L_80005dd0;
 case UINT32_C(0x80005dd4):goto L_80005dd4;
 case UINT32_C(0x80005dd8):goto L_80005dd8;
 case UINT32_C(0x80005ddc):goto L_80005ddc;
 case UINT32_C(0x80005de0):goto L_80005de0;
 case UINT32_C(0x80005de4):goto L_80005de4;
 case UINT32_C(0x80005de8):goto L_80005de8;
 case UINT32_C(0x80005dec):goto L_80005dec;
 case UINT32_C(0x80005df0):goto L_80005df0;
 case UINT32_C(0x80005df4):goto L_80005df4;
 case UINT32_C(0x80005df8):goto L_80005df8;
 case UINT32_C(0x80005dfc):goto L_80005dfc;
 case UINT32_C(0x80005e00):goto L_80005e00;
 case UINT32_C(0x80005e04):goto L_80005e04;
 case UINT32_C(0x80005e08):goto L_80005e08;
 case UINT32_C(0x80005e0c):goto L_80005e0c;
 case UINT32_C(0x80005e10):goto L_80005e10;
 case UINT32_C(0x80005e14):goto L_80005e14;
 case UINT32_C(0x80005e18):goto L_80005e18;
 case UINT32_C(0x80005e1c):goto L_80005e1c;
 case UINT32_C(0x80005e20):goto L_80005e20;
 case UINT32_C(0x80005e24):goto L_80005e24;
 case UINT32_C(0x80005e28):goto L_80005e28;
 case UINT32_C(0x80005e2c):goto L_80005e2c;
 case UINT32_C(0x80005e30):goto L_80005e30;
 case UINT32_C(0x80005e34):goto L_80005e34;
 case UINT32_C(0x80005e38):goto L_80005e38;
 case UINT32_C(0x80005e3c):goto L_80005e3c;
 case UINT32_C(0x80005e40):goto L_80005e40;
 case UINT32_C(0x80005e44):goto L_80005e44;
 case UINT32_C(0x80005e48):goto L_80005e48;
 case UINT32_C(0x80005e4c):goto L_80005e4c;
 case UINT32_C(0x80005e50):goto L_80005e50;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_80000940:
 STEP(UINT32_C(0x80000940)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80000944));goto dispatch;
L_80000944:
 STEP(UINT32_C(0x80000944)); /* 3463e010 ori v1,v1,0xe010 */
 set(m,3u,lo(m,3u) | UINT64_C(0xe010));target=sx(UINT32_C(0x80000948));goto dispatch;
L_80000948:
 STEP(UINT32_C(0x80000948)); /* 3c010001 lui at,zero,0x1 */
 set(m,1u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x8000094c));goto dispatch;
L_8000094c:
 STEP(UINT32_C(0x8000094c)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80000950));goto dispatch;
L_80000950:
 STEP(UINT32_C(0x80000950)); /* 00810804 sllv at,a0,at */
 set(m,1u,sx((uint32_t)lo(m,1u)<<((uint32_t)lo(m,4u)&31u)));target=sx(UINT32_C(0x80000954));goto dispatch;
L_80000954:
 STEP(UINT32_C(0x80000954)); /* 00411024 and v0,v0,at */
 set(m,2u,lo(m,2u)&lo(m,1u));target=sx(UINT32_C(0x80000958));goto dispatch;
L_80000958:
 STEP(UINT32_C(0x80000958)); /* 54400003 bnel v0,zero,80000968 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x8000095c));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80000968));}else target=sx(UINT32_C(0x80000960));goto dispatch;
L_8000095c:
 STEP(UINT32_C(0x8000095c)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80000960));goto dispatch;
L_80000960:
 STEP(UINT32_C(0x80000960)); /* ac610000 sw at,0x0(v1) */
 value32=(uint32_t)lo(m,1u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80000964));goto dispatch;
L_80000964:
 STEP(UINT32_C(0x80000964)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80000968));goto dispatch;
L_80000968:
 STEP(UINT32_C(0x80000968)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000096c));/* nop */goto dispatch;
L_8000096c:
 STEP(UINT32_C(0x8000096c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80000970));goto dispatch;
L_80001c78:
 STEP(UINT32_C(0x80001c78)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80001c7c));goto dispatch;
L_80001c7c:
 STEP(UINT32_C(0x80001c7c)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80001c80));goto dispatch;
L_80001c80:
 STEP(UINT32_C(0x80001c80)); /* 0c0006c4 jal 80001b10 */
 set(m,31u,UINT64_C(0x80001c88));STEP(UINT32_C(0x80001c84));set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x80001b10));goto dispatch;
L_80001c84:
 STEP(UINT32_C(0x80001c84)); /* 24080002 addiu t0,zero,2 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x80001c88));goto dispatch;
L_80001c88:
 STEP(UINT32_C(0x80001c88)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80001c8c));goto dispatch;
L_80001c8c:
 STEP(UINT32_C(0x80001c8c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80001c90));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_80001c90:
 STEP(UINT32_C(0x80001c90)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80001c94));goto dispatch;
L_80001b10:
 STEP(UINT32_C(0x80001b10)); /* 27bdff90 addiu sp,sp,-112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff90)));target=sx(UINT32_C(0x80001b14));goto dispatch;
L_80001b14:
 STEP(UINT32_C(0x80001b14)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80001b18));goto dispatch;
L_80001b18:
 STEP(UINT32_C(0x80001b18)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x80001b1c));goto dispatch;
L_80001b1c:
 STEP(UINT32_C(0x80001b1c)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80001b20));goto dispatch;
L_80001b20:
 STEP(UINT32_C(0x80001b20)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x80001b24));goto dispatch;
L_80001b24:
 STEP(UINT32_C(0x80001b24)); /* 0100a82d daddu s5,t0,zero */
 set(m,21u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x80001b28));goto dispatch;
L_80001b28:
 STEP(UINT32_C(0x80001b28)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x80001b2c));goto dispatch;
L_80001b2c:
 STEP(UINT32_C(0x80001b2c)); /* 00e0a02d daddu s4,a3,zero */
 set(m,20u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x80001b30));goto dispatch;
L_80001b30:
 STEP(UINT32_C(0x80001b30)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80001b34));goto dispatch;
L_80001b34:
 STEP(UINT32_C(0x80001b34)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80001b38));goto dispatch;
L_80001b38:
 STEP(UINT32_C(0x80001b38)); /* ffbf0060 sd ra,0x60(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x80001b3c));goto dispatch;
L_80001b3c:
 STEP(UINT32_C(0x80001b3c)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x80001b40));goto dispatch;
L_80001b40:
 STEP(UINT32_C(0x80001b40)); /* 2e420010 sltiu v0,s2,16 */
 set(m,2u,(lo(m,18u)<UINT64_C(0x10)));target=sx(UINT32_C(0x80001b44));goto dispatch;
L_80001b44:
 STEP(UINT32_C(0x80001b44)); /* 1040002f beq v0,zero,80001c04 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80001b48));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x80001c04):UINT32_C(0x80001b4c));goto dispatch;}
L_80001b48:
 STEP(UINT32_C(0x80001b48)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80001b4c));goto dispatch;
L_80001b4c:
 STEP(UINT32_C(0x80001b4c)); /* 0c000568 jal 800015a0 */
 set(m,31u,UINT64_C(0x80001b54));STEP(UINT32_C(0x80001b50));/* nop */target=sx(UINT32_C(0x800015a0));goto dispatch;
L_80001b50:
 STEP(UINT32_C(0x80001b50)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80001b54));goto dispatch;
L_80001b54:
 STEP(UINT32_C(0x80001b54)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80001b58));goto dispatch;
L_80001b58:
 STEP(UINT32_C(0x80001b58)); /* 1200003e beq s0,zero,80001c54 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x80001b5c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80001c54):UINT32_C(0x80001b60));goto dispatch;}
L_80001b5c:
 STEP(UINT32_C(0x80001b5c)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80001b60));goto dispatch;
L_80001b60:
 STEP(UINT32_C(0x80001b60)); /* 0380102d daddu v0,gp,zero */
 set(m,2u,lo(m,28u)+lo(m,0u));target=sx(UINT32_C(0x80001b64));goto dispatch;
L_80001b64:
 STEP(UINT32_C(0x80001b64)); /* ae130008 sw s3,0x8(s0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x80001b68));goto dispatch;
L_80001b68:
 STEP(UINT32_C(0x80001b68)); /* ae02000c sw v0,0xc(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x80001b6c));goto dispatch;
L_80001b6c:
 STEP(UINT32_C(0x80001b6c)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80001b70));goto dispatch;
L_80001b70:
 STEP(UINT32_C(0x80001b70)); /* ae140010 sw s4,0x10(s0) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x80001b74));goto dispatch;
L_80001b74:
 STEP(UINT32_C(0x80001b74)); /* 12230011 beq s1,v1,80001bbc */
 {int taken=(lo(m,17u)==lo(m,3u));STEP(UINT32_C(0x80001b78));value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x80001bbc):UINT32_C(0x80001b7c));goto dispatch;}
L_80001b78:
 STEP(UINT32_C(0x80001b78)); /* ae150014 sw s5,0x14(s0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x80001b7c));goto dispatch;
L_80001b7c:
 STEP(UINT32_C(0x80001b7c)); /* 12200018 beq s1,zero,80001be0 */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x80001b80));set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80001be0):UINT32_C(0x80001b84));goto dispatch;}
L_80001b80:
 STEP(UINT32_C(0x80001b80)); /* 2622ffff addiu v0,s1,-1 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80001b84));goto dispatch;
L_80001b84:
 STEP(UINT32_C(0x80001b84)); /* 2c420080 sltiu v0,v0,128 */
 set(m,2u,(lo(m,2u)<UINT64_C(0x80)));target=sx(UINT32_C(0x80001b88));goto dispatch;
L_80001b88:
 STEP(UINT32_C(0x80001b88)); /* 1040001e beq v0,zero,80001c04 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80001b8c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000018)));target=sx(taken?UINT32_C(0x80001c04):UINT32_C(0x80001b90));goto dispatch;}
L_80001b8c:
 STEP(UINT32_C(0x80001b8c)); /* 24020018 addiu v0,zero,24 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000018)));target=sx(UINT32_C(0x80001b90));goto dispatch;
L_80001b90:
 STEP(UINT32_C(0x80001b90)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80001b94));goto dispatch;
L_80001b94:
 STEP(UINT32_C(0x80001b94)); /* 24845de4 addiu a0,a0,24036 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00005de4)));target=sx(UINT32_C(0x80001b98));goto dispatch;
L_80001b98:
 STEP(UINT32_C(0x80001b98)); /* 02223018 mult_rd a2,s1,v0 */
 {int64_t product;if(lo(m,17u)!=sx((uint32_t)lo(m,17u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,17u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,6u,m->lo);}target=sx(UINT32_C(0x80001b9c));goto dispatch;
L_80001b9c:
 STEP(UINT32_C(0x80001b9c)); /* 24030003 addiu v1,zero,3 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x80001ba0));goto dispatch;
L_80001ba0:
 STEP(UINT32_C(0x80001ba0)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80001ba4));goto dispatch;
L_80001ba4:
 STEP(UINT32_C(0x80001ba4)); /* 00461021 addu v0,v0,a2 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x80001ba8));goto dispatch;
L_80001ba8:
 STEP(UINT32_C(0x80001ba8)); /* 8c425de4 lw v0,0x5de4(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00005de4),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80001bac));goto dispatch;
L_80001bac:
 STEP(UINT32_C(0x80001bac)); /* 14430017 bne v0,v1,80001c0c */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x80001bb0));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffec)));target=sx(taken?UINT32_C(0x80001c0c):UINT32_C(0x80001bb4));goto dispatch;}
L_80001bb0:
 STEP(UINT32_C(0x80001bb0)); /* 2484ffec addiu a0,a0,-20 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffec)));target=sx(UINT32_C(0x80001bb4));goto dispatch;
L_80001bb4:
 STEP(UINT32_C(0x80001bb4)); /* 10000027 beq zero,zero,80001c54 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80001bb8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80001c54):UINT32_C(0x80001bbc));goto dispatch;}
L_80001bb8:
 STEP(UINT32_C(0x80001bb8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80001bbc));goto dispatch;
L_80001bbc:
 STEP(UINT32_C(0x80001bbc)); /* 2404000c addiu a0,zero,12 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x80001bc0));goto dispatch;
L_80001bc0:
 STEP(UINT32_C(0x80001bc0)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80001bc4));goto dispatch;
L_80001bc4:
 STEP(UINT32_C(0x80001bc4)); /* 24425d10 addiu v0,v0,23824 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00005d10)));target=sx(UINT32_C(0x80001bc8));goto dispatch;
L_80001bc8:
 STEP(UINT32_C(0x80001bc8)); /* 02442018 mult_rd a0,s2,a0 */
 {int64_t product;if(lo(m,18u)!=sx((uint32_t)lo(m,18u))||lo(m,4u)!=sx((uint32_t)lo(m,4u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,18u)*(int64_t)(int32_t)lo(m,4u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x80001bcc));goto dispatch;
L_80001bcc:
 STEP(UINT32_C(0x80001bcc)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80001bd0));goto dispatch;
L_80001bd0:
 STEP(UINT32_C(0x80001bd0)); /* 0c0016c2 jal 80005b08 */
 set(m,31u,UINT64_C(0x80001bd8));STEP(UINT32_C(0x80001bd4));set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80005b08));goto dispatch;
L_80001bd4:
 STEP(UINT32_C(0x80001bd4)); /* 00822021 addu a0,a0,v0 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80001bd8));goto dispatch;
L_80001bd8:
 STEP(UINT32_C(0x80001bd8)); /* 10000010 beq zero,zero,80001c1c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80001bdc));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(taken?UINT32_C(0x80001c1c):UINT32_C(0x80001be0));goto dispatch;}
L_80001bdc:
 STEP(UINT32_C(0x80001bdc)); /* 2404000c addiu a0,zero,12 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x80001be0));goto dispatch;
L_80001be0:
 STEP(UINT32_C(0x80001be0)); /* 2402000c addiu v0,zero,12 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x80001be4));goto dispatch;
L_80001be4:
 STEP(UINT32_C(0x80001be4)); /* 02421018 mult_rd v0,s2,v0 */
 {int64_t product;if(lo(m,18u)!=sx((uint32_t)lo(m,18u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,18u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=sx(UINT32_C(0x80001be8));goto dispatch;
L_80001be8:
 STEP(UINT32_C(0x80001be8)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80001bec));goto dispatch;
L_80001bec:
 STEP(UINT32_C(0x80001bec)); /* 00822021 addu a0,a0,v0 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80001bf0));goto dispatch;
L_80001bf0:
 STEP(UINT32_C(0x80001bf0)); /* 8c845d14 lw a0,0x5d14(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00005d14),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80001bf4));goto dispatch;
L_80001bf4:
 STEP(UINT32_C(0x80001bf4)); /* 0c0016c2 jal 80005b08 */
 set(m,31u,UINT64_C(0x80001bfc));STEP(UINT32_C(0x80001bf8));set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80005b08));goto dispatch;
L_80001bf8:
 STEP(UINT32_C(0x80001bf8)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80001bfc));goto dispatch;
L_80001bfc:
 STEP(UINT32_C(0x80001bfc)); /* 10000007 beq zero,zero,80001c1c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80001c00));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(taken?UINT32_C(0x80001c1c):UINT32_C(0x80001c04));goto dispatch;}
L_80001c00:
 STEP(UINT32_C(0x80001c00)); /* 2404000c addiu a0,zero,12 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x80001c04));goto dispatch;
L_80001c04:
 STEP(UINT32_C(0x80001c04)); /* 10000013 beq zero,zero,80001c54 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80001c08));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80001c54):UINT32_C(0x80001c0c));goto dispatch;}
L_80001c08:
 STEP(UINT32_C(0x80001c08)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80001c0c));goto dispatch;
L_80001c0c:
 STEP(UINT32_C(0x80001c0c)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x80001c10));goto dispatch;
L_80001c10:
 STEP(UINT32_C(0x80001c10)); /* 0c0016c2 jal 80005b08 */
 set(m,31u,UINT64_C(0x80001c18));STEP(UINT32_C(0x80001c14));set(m,4u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80005b08));goto dispatch;
L_80001c14:
 STEP(UINT32_C(0x80001c14)); /* 00c42021 addu a0,a2,a0 */
 set(m,4u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80001c18));goto dispatch;
L_80001c18:
 STEP(UINT32_C(0x80001c18)); /* 2404000c addiu a0,zero,12 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x80001c1c));goto dispatch;
L_80001c1c:
 STEP(UINT32_C(0x80001c1c)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80001c20));goto dispatch;
L_80001c20:
 STEP(UINT32_C(0x80001c20)); /* 24425dd0 addiu v0,v0,24016 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00005dd0)));target=sx(UINT32_C(0x80001c24));goto dispatch;
L_80001c24:
 STEP(UINT32_C(0x80001c24)); /* 02442018 mult_rd a0,s2,a0 */
 {int64_t product;if(lo(m,18u)!=sx((uint32_t)lo(m,18u))||lo(m,4u)!=sx((uint32_t)lo(m,4u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,18u)*(int64_t)(int32_t)lo(m,4u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x80001c28));goto dispatch;
L_80001c28:
 STEP(UINT32_C(0x80001c28)); /* 3c03aaaa lui v1,zero,0xaaaa */
 set(m,3u,sx(UINT32_C(0xaaaa0000)));target=sx(UINT32_C(0x80001c2c));goto dispatch;
L_80001c2c:
 STEP(UINT32_C(0x80001c2c)); /* 3463aaab ori v1,v1,0xaaab */
 set(m,3u,lo(m,3u) | UINT64_C(0xaaab));target=sx(UINT32_C(0x80001c30));goto dispatch;
L_80001c30:
 STEP(UINT32_C(0x80001c30)); /* 3c058001 lui a1,zero,0x8001 */
 set(m,5u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80001c34));goto dispatch;
L_80001c34:
 STEP(UINT32_C(0x80001c34)); /* 24a55d18 addiu a1,a1,23832 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00005d18)));target=sx(UINT32_C(0x80001c38));goto dispatch;
L_80001c38:
 STEP(UINT32_C(0x80001c38)); /* 02021023 subu v0,s0,v0 */
 set(m,2u,sx((uint32_t)lo(m,16u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80001c3c));goto dispatch;
L_80001c3c:
 STEP(UINT32_C(0x80001c3c)); /* 00431018 mult_rd v0,v0,v1 */
 {int64_t product;if(lo(m,2u)!=sx((uint32_t)lo(m,2u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,2u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=sx(UINT32_C(0x80001c40));goto dispatch;
L_80001c40:
 STEP(UINT32_C(0x80001c40)); /* 00852021 addu a0,a0,a1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x80001c44));goto dispatch;
L_80001c44:
 STEP(UINT32_C(0x80001c44)); /* 8c830000 lw v1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80001c48));goto dispatch;
L_80001c48:
 STEP(UINT32_C(0x80001c48)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80001c4c));goto dispatch;
L_80001c4c:
 STEP(UINT32_C(0x80001c4c)); /* 000210c3 sra v0,v0,3 */
 set(m,2u,sx((uint32_t)((int32_t)lo(m,2u)>>3u)));target=sx(UINT32_C(0x80001c50));goto dispatch;
L_80001c50:
 STEP(UINT32_C(0x80001c50)); /* ac830000 sw v1,0x0(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80001c54));goto dispatch;
L_80001c54:
 STEP(UINT32_C(0x80001c54)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80001c58));goto dispatch;
L_80001c58:
 STEP(UINT32_C(0x80001c58)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x80001c5c));goto dispatch;
L_80001c5c:
 STEP(UINT32_C(0x80001c5c)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x80001c60));goto dispatch;
L_80001c60:
 STEP(UINT32_C(0x80001c60)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x80001c64));goto dispatch;
L_80001c64:
 STEP(UINT32_C(0x80001c64)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x80001c68));goto dispatch;
L_80001c68:
 STEP(UINT32_C(0x80001c68)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x80001c6c));goto dispatch;
L_80001c6c:
 STEP(UINT32_C(0x80001c6c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x80001c70));goto dispatch;
L_80001c70:
 STEP(UINT32_C(0x80001c70)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80001c74));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));goto dispatch;
L_80001c74:
 STEP(UINT32_C(0x80001c74)); /* 27bd0070 addiu sp,sp,112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x80001c78));goto dispatch;
L_800015a0:
 STEP(UINT32_C(0x800015a0)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x800015a4));goto dispatch;
L_800015a4:
 STEP(UINT32_C(0x800015a4)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800015a8));goto dispatch;
L_800015a8:
 STEP(UINT32_C(0x800015a8)); /* 24845c50 addiu a0,a0,23632 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00005c50)));target=sx(UINT32_C(0x800015ac));goto dispatch;
L_800015ac:
 STEP(UINT32_C(0x800015ac)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x800015b0));goto dispatch;
L_800015b0:
 STEP(UINT32_C(0x800015b0)); /* 0c001696 jal 80005a58 */
 set(m,31u,UINT64_C(0x800015b8));STEP(UINT32_C(0x800015b4));/* nop */target=sx(UINT32_C(0x80005a58));goto dispatch;
L_800015b4:
 STEP(UINT32_C(0x800015b4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800015b8));goto dispatch;
L_800015b8:
 STEP(UINT32_C(0x800015b8)); /* 14400003 bne v0,zero,800015c8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x800015bc));/* nop */target=sx(taken?UINT32_C(0x800015c8):UINT32_C(0x800015c0));goto dispatch;}
L_800015bc:
 STEP(UINT32_C(0x800015bc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800015c0));goto dispatch;
L_800015c0:
 STEP(UINT32_C(0x800015c0)); /* 10000006 beq zero,zero,800015dc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800015c4));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x800015dc):UINT32_C(0x800015c8));goto dispatch;}
L_800015c4:
 STEP(UINT32_C(0x800015c4)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x800015c8));goto dispatch;
L_800015c8:
 STEP(UINT32_C(0x800015c8)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800015cc));goto dispatch;
L_800015cc:
 STEP(UINT32_C(0x800015cc)); /* 8c635c40 lw v1,0x5c40(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00005c40),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x800015d0));goto dispatch;
L_800015d0:
 STEP(UINT32_C(0x800015d0)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800015d4));goto dispatch;
L_800015d4:
 STEP(UINT32_C(0x800015d4)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800015d8));goto dispatch;
L_800015d8:
 STEP(UINT32_C(0x800015d8)); /* ac235c40 sw v1,0x5c40(at) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x00005c40),&value32,4u);target=sx(UINT32_C(0x800015dc));goto dispatch;
L_800015dc:
 STEP(UINT32_C(0x800015dc)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x800015e0));goto dispatch;
L_800015e0:
 STEP(UINT32_C(0x800015e0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800015e4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_800015e4:
 STEP(UINT32_C(0x800015e4)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x800015e8));goto dispatch;
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
L_80005b08:
 STEP(UINT32_C(0x80005b08)); /* 8c830000 lw v1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80005b0c));goto dispatch;
L_80005b0c:
 STEP(UINT32_C(0x80005b0c)); /* aca40004 sw a0,0x4(a1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80005b10));goto dispatch;
L_80005b10:
 STEP(UINT32_C(0x80005b10)); /* aca30000 sw v1,0x0(a1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80005b14));goto dispatch;
L_80005b14:
 STEP(UINT32_C(0x80005b14)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005b18));goto dispatch;
L_80005b18:
 STEP(UINT32_C(0x80005b18)); /* ac450004 sw a1,0x4(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80005b1c));goto dispatch;
L_80005b1c:
 STEP(UINT32_C(0x80005b1c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80005b20));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_80005b20:
 STEP(UINT32_C(0x80005b20)); /* ac850000 sw a1,0x0(a0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80005b24));goto dispatch;
L_800062a0:
 STEP(UINT32_C(0x800062a0)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x800062a4));goto dispatch;
L_800062a4:
 STEP(UINT32_C(0x800062a4)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x800062a8));goto dispatch;
L_800062a8:
 STEP(UINT32_C(0x800062a8)); /* 3463c000 ori v1,v1,0xc000 */
 set(m,3u,lo(m,3u) | UINT64_C(0xc000));target=sx(UINT32_C(0x800062ac));goto dispatch;
L_800062ac:
 STEP(UINT32_C(0x800062ac)); /* 3442c020 ori v0,v0,0xc020 */
 set(m,2u,lo(m,2u) | UINT64_C(0xc020));target=sx(UINT32_C(0x800062b0));goto dispatch;
L_800062b0:
 STEP(UINT32_C(0x800062b0)); /* ac600000 sw zero,0x0(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800062b4));goto dispatch;
L_800062b4:
 STEP(UINT32_C(0x800062b4)); /* 24040184 addiu a0,zero,388 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000184)));target=sx(UINT32_C(0x800062b8));goto dispatch;
L_800062b8:
 STEP(UINT32_C(0x800062b8)); /* ac400000 sw zero,0x0(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800062bc));goto dispatch;
L_800062bc:
 STEP(UINT32_C(0x800062bc)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x800062c0));goto dispatch;
L_800062c0:
 STEP(UINT32_C(0x800062c0)); /* ac640000 sw a0,0x0(v1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800062c4));goto dispatch;
L_800062c4:
 STEP(UINT32_C(0x800062c4)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800062c8));goto dispatch;
L_800062c8:
 STEP(UINT32_C(0x800062c8)); /* afa20000 sw v0,0x0(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800062cc));goto dispatch;
L_800062cc:
 STEP(UINT32_C(0x800062cc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800062d0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_800062d0:
 STEP(UINT32_C(0x800062d0)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x800062d4));goto dispatch;
L_80006b60:
 STEP(UINT32_C(0x80006b60)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80006b64));goto dispatch;
L_80006b64:
 STEP(UINT32_C(0x80006b64)); /* 24020003 addiu v0,zero,3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x80006b68));goto dispatch;
L_80006b68:
 STEP(UINT32_C(0x80006b68)); /* 10820011 beq a0,v0,80006bb0 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80006b6c));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x80006bb0):UINT32_C(0x80006b70));goto dispatch;}
L_80006b6c:
 STEP(UINT32_C(0x80006b6c)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80006b70));goto dispatch;
L_80006b70:
 STEP(UINT32_C(0x80006b70)); /* 2c820004 sltiu v0,a0,4 */
 set(m,2u,(lo(m,4u)<UINT64_C(0x4)));target=sx(UINT32_C(0x80006b74));goto dispatch;
L_80006b74:
 STEP(UINT32_C(0x80006b74)); /* 10400005 beq v0,zero,80006b8c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80006b78));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x80006b8c):UINT32_C(0x80006b7c));goto dispatch;}
L_80006b78:
 STEP(UINT32_C(0x80006b78)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80006b7c));goto dispatch;
L_80006b7c:
 STEP(UINT32_C(0x80006b7c)); /* 10820008 beq a0,v0,80006ba0 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80006b80));/* nop */target=sx(taken?UINT32_C(0x80006ba0):UINT32_C(0x80006b84));goto dispatch;}
L_80006b80:
 STEP(UINT32_C(0x80006b80)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006b84));goto dispatch;
L_80006b84:
 STEP(UINT32_C(0x80006b84)); /* 10000012 beq zero,zero,80006bd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006b88));/* nop */target=sx(taken?UINT32_C(0x80006bd0):UINT32_C(0x80006b8c));goto dispatch;}
L_80006b88:
 STEP(UINT32_C(0x80006b88)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006b8c));goto dispatch;
L_80006b8c:
 STEP(UINT32_C(0x80006b8c)); /* 24020004 addiu v0,zero,4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x80006b90));goto dispatch;
L_80006b90:
 STEP(UINT32_C(0x80006b90)); /* 1082000b beq a0,v0,80006bc0 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80006b94));/* nop */target=sx(taken?UINT32_C(0x80006bc0):UINT32_C(0x80006b98));goto dispatch;}
L_80006b94:
 STEP(UINT32_C(0x80006b94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006b98));goto dispatch;
L_80006b98:
 STEP(UINT32_C(0x80006b98)); /* 1000000d beq zero,zero,80006bd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006b9c));/* nop */target=sx(taken?UINT32_C(0x80006bd0):UINT32_C(0x80006ba0));goto dispatch;}
L_80006b9c:
 STEP(UINT32_C(0x80006b9c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006ba0));goto dispatch;
L_80006ba0:
 STEP(UINT32_C(0x80006ba0)); /* 0c001aba jal 80006ae8 */
 set(m,31u,UINT64_C(0x80006ba8));STEP(UINT32_C(0x80006ba4));set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006ae8));goto dispatch;
L_80006ba4:
 STEP(UINT32_C(0x80006ba4)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006ba8));goto dispatch;
L_80006ba8:
 STEP(UINT32_C(0x80006ba8)); /* 10000017 beq zero,zero,80006c08 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006bac));set(m,6u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x80006c08):UINT32_C(0x80006bb0));goto dispatch;}
L_80006bac:
 STEP(UINT32_C(0x80006bac)); /* 0040302d daddu a2,v0,zero */
 set(m,6u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80006bb0));goto dispatch;
L_80006bb0:
 STEP(UINT32_C(0x80006bb0)); /* 0c001a96 jal 80006a58 */
 set(m,31u,UINT64_C(0x80006bb8));STEP(UINT32_C(0x80006bb4));set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006a58));goto dispatch;
L_80006bb4:
 STEP(UINT32_C(0x80006bb4)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006bb8));goto dispatch;
L_80006bb8:
 STEP(UINT32_C(0x80006bb8)); /* 10000013 beq zero,zero,80006c08 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006bbc));set(m,6u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x80006c08):UINT32_C(0x80006bc0));goto dispatch;}
L_80006bbc:
 STEP(UINT32_C(0x80006bbc)); /* 0040302d daddu a2,v0,zero */
 set(m,6u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80006bc0));goto dispatch;
L_80006bc0:
 STEP(UINT32_C(0x80006bc0)); /* 0c001aa8 jal 80006aa0 */
 set(m,31u,UINT64_C(0x80006bc8));STEP(UINT32_C(0x80006bc4));set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006aa0));goto dispatch;
L_80006bc4:
 STEP(UINT32_C(0x80006bc4)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006bc8));goto dispatch;
L_80006bc8:
 STEP(UINT32_C(0x80006bc8)); /* 1000000f beq zero,zero,80006c08 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006bcc));set(m,6u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x80006c08):UINT32_C(0x80006bd0));goto dispatch;}
L_80006bcc:
 STEP(UINT32_C(0x80006bcc)); /* 0040302d daddu a2,v0,zero */
 set(m,6u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80006bd0));goto dispatch;
L_80006bd0:
 STEP(UINT32_C(0x80006bd0)); /* 0483000d regimm3 a0,80006c08 */
 if((int64_t)lo(m,4u)>=0){STEP(UINT32_C(0x80006bd4));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80006c08));}else target=sx(UINT32_C(0x80006bd8));goto dispatch;
L_80006bd4:
 STEP(UINT32_C(0x80006bd4)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80006bd8));goto dispatch;
L_80006bd8:
 STEP(UINT32_C(0x80006bd8)); /* 3c027fff lui v0,zero,0x7fff */
 set(m,2u,sx(UINT32_C(0x7fff0000)));target=sx(UINT32_C(0x80006bdc));goto dispatch;
L_80006bdc:
 STEP(UINT32_C(0x80006bdc)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x80006be0));goto dispatch;
L_80006be0:
 STEP(UINT32_C(0x80006be0)); /* 00821024 and v0,a0,v0 */
 set(m,2u,lo(m,4u)&lo(m,2u));target=sx(UINT32_C(0x80006be4));goto dispatch;
L_80006be4:
 STEP(UINT32_C(0x80006be4)); /* 2c430020 sltiu v1,v0,32 */
 set(m,3u,(lo(m,2u)<UINT64_C(0x20)));target=sx(UINT32_C(0x80006be8));goto dispatch;
L_80006be8:
 STEP(UINT32_C(0x80006be8)); /* 10600006 beq v1,zero,80006c04 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x80006bec));set(m,2u,sx((uint32_t)lo(m,2u)<<2u));target=sx(taken?UINT32_C(0x80006c04):UINT32_C(0x80006bf0));goto dispatch;}
L_80006bec:
 STEP(UINT32_C(0x80006bec)); /* 00021080 sll v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<2u));target=sx(UINT32_C(0x80006bf0));goto dispatch;
L_80006bf0:
 STEP(UINT32_C(0x80006bf0)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006bf4));goto dispatch;
L_80006bf4:
 STEP(UINT32_C(0x80006bf4)); /* 00220821 addu at,at,v0 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80006bf8));goto dispatch;
L_80006bf8:
 STEP(UINT32_C(0x80006bf8)); /* ac25e080 sw a1,-0x1f80(at) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe080),&value32,4u);target=sx(UINT32_C(0x80006bfc));goto dispatch;
L_80006bfc:
 STEP(UINT32_C(0x80006bfc)); /* 10000003 beq zero,zero,80006c0c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006c00));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80006c0c):UINT32_C(0x80006c04));goto dispatch;}
L_80006c00:
 STEP(UINT32_C(0x80006c00)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006c04));goto dispatch;
L_80006c04:
 STEP(UINT32_C(0x80006c04)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80006c08));goto dispatch;
L_80006c08:
 STEP(UINT32_C(0x80006c08)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006c0c));goto dispatch;
L_80006c0c:
 STEP(UINT32_C(0x80006c0c)); /* 00c0102d daddu v0,a2,zero */
 set(m,2u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x80006c10));goto dispatch;
L_80006c10:
 STEP(UINT32_C(0x80006c10)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006c14));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_80006c14:
 STEP(UINT32_C(0x80006c14)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006c18));goto dispatch;
L_80006c18:
 STEP(UINT32_C(0x80006c18)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80006c1c));goto dispatch;
L_80006c1c:
 STEP(UINT32_C(0x80006c1c)); /* 24020002 addiu v0,zero,2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x80006c20));goto dispatch;
L_80006c20:
 STEP(UINT32_C(0x80006c20)); /* 10820013 beq a0,v0,80006c70 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80006c24));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x80006c70):UINT32_C(0x80006c28));goto dispatch;}
L_80006c24:
 STEP(UINT32_C(0x80006c24)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80006c28));goto dispatch;
L_80006c28:
 STEP(UINT32_C(0x80006c28)); /* 2c820003 sltiu v0,a0,3 */
 set(m,2u,(lo(m,4u)<UINT64_C(0x3)));target=sx(UINT32_C(0x80006c2c));goto dispatch;
L_80006c2c:
 STEP(UINT32_C(0x80006c2c)); /* 10400005 beq v0,zero,80006c44 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80006c30));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x80006c44):UINT32_C(0x80006c34));goto dispatch;}
L_80006c30:
 STEP(UINT32_C(0x80006c30)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80006c34));goto dispatch;
L_80006c34:
 STEP(UINT32_C(0x80006c34)); /* 1082000a beq a0,v0,80006c60 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80006c38));/* nop */target=sx(taken?UINT32_C(0x80006c60):UINT32_C(0x80006c3c));goto dispatch;}
L_80006c38:
 STEP(UINT32_C(0x80006c38)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006c3c));goto dispatch;
L_80006c3c:
 STEP(UINT32_C(0x80006c3c)); /* 10000018 beq zero,zero,80006ca0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006c40));/* nop */target=sx(taken?UINT32_C(0x80006ca0):UINT32_C(0x80006c44));goto dispatch;}
L_80006c40:
 STEP(UINT32_C(0x80006c40)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006c44));goto dispatch;
L_80006c44:
 STEP(UINT32_C(0x80006c44)); /* 24020003 addiu v0,zero,3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x80006c48));goto dispatch;
L_80006c48:
 STEP(UINT32_C(0x80006c48)); /* 1082000d beq a0,v0,80006c80 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80006c4c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(taken?UINT32_C(0x80006c80):UINT32_C(0x80006c50));goto dispatch;}
L_80006c4c:
 STEP(UINT32_C(0x80006c4c)); /* 24020004 addiu v0,zero,4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x80006c50));goto dispatch;
L_80006c50:
 STEP(UINT32_C(0x80006c50)); /* 1082000f beq a0,v0,80006c90 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80006c54));/* nop */target=sx(taken?UINT32_C(0x80006c90):UINT32_C(0x80006c58));goto dispatch;}
L_80006c54:
 STEP(UINT32_C(0x80006c54)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006c58));goto dispatch;
L_80006c58:
 STEP(UINT32_C(0x80006c58)); /* 10000011 beq zero,zero,80006ca0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006c5c));/* nop */target=sx(taken?UINT32_C(0x80006ca0):UINT32_C(0x80006c60));goto dispatch;}
L_80006c5c:
 STEP(UINT32_C(0x80006c5c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006c60));goto dispatch;
L_80006c60:
 STEP(UINT32_C(0x80006c60)); /* 0c001ab2 jal 80006ac8 */
 set(m,31u,UINT64_C(0x80006c68));STEP(UINT32_C(0x80006c64));/* nop */target=sx(UINT32_C(0x80006ac8));goto dispatch;
L_80006c64:
 STEP(UINT32_C(0x80006c64)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006c68));goto dispatch;
L_80006c68:
 STEP(UINT32_C(0x80006c68)); /* 1000001c beq zero,zero,80006cdc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006c6c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80006cdc):UINT32_C(0x80006c70));goto dispatch;}
L_80006c6c:
 STEP(UINT32_C(0x80006c6c)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006c70));goto dispatch;
L_80006c70:
 STEP(UINT32_C(0x80006c70)); /* 0c001ab6 jal 80006ad8 */
 set(m,31u,UINT64_C(0x80006c78));STEP(UINT32_C(0x80006c74));/* nop */target=sx(UINT32_C(0x80006ad8));goto dispatch;
L_80006c74:
 STEP(UINT32_C(0x80006c74)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006c78));goto dispatch;
L_80006c78:
 STEP(UINT32_C(0x80006c78)); /* 10000018 beq zero,zero,80006cdc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006c7c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80006cdc):UINT32_C(0x80006c80));goto dispatch;}
L_80006c7c:
 STEP(UINT32_C(0x80006c7c)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006c80));goto dispatch;
L_80006c80:
 STEP(UINT32_C(0x80006c80)); /* 0c001a8e jal 80006a38 */
 set(m,31u,UINT64_C(0x80006c88));STEP(UINT32_C(0x80006c84));/* nop */target=sx(UINT32_C(0x80006a38));goto dispatch;
L_80006c84:
 STEP(UINT32_C(0x80006c84)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006c88));goto dispatch;
L_80006c88:
 STEP(UINT32_C(0x80006c88)); /* 10000014 beq zero,zero,80006cdc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006c8c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80006cdc):UINT32_C(0x80006c90));goto dispatch;}
L_80006c8c:
 STEP(UINT32_C(0x80006c8c)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006c90));goto dispatch;
L_80006c90:
 STEP(UINT32_C(0x80006c90)); /* 0c001aa0 jal 80006a80 */
 set(m,31u,UINT64_C(0x80006c98));STEP(UINT32_C(0x80006c94));/* nop */target=sx(UINT32_C(0x80006a80));goto dispatch;
L_80006c94:
 STEP(UINT32_C(0x80006c94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006c98));goto dispatch;
L_80006c98:
 STEP(UINT32_C(0x80006c98)); /* 10000010 beq zero,zero,80006cdc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006c9c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80006cdc):UINT32_C(0x80006ca0));goto dispatch;}
L_80006c9c:
 STEP(UINT32_C(0x80006c9c)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006ca0));goto dispatch;
L_80006ca0:
 STEP(UINT32_C(0x80006ca0)); /* 0481000d regimm1 a0,80006cd8 */
 {int taken=((int64_t)lo(m,4u)>=0);STEP(UINT32_C(0x80006ca4));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x80006cd8):UINT32_C(0x80006ca8));goto dispatch;}
L_80006ca4:
 STEP(UINT32_C(0x80006ca4)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80006ca8));goto dispatch;
L_80006ca8:
 STEP(UINT32_C(0x80006ca8)); /* 3c027fff lui v0,zero,0x7fff */
 set(m,2u,sx(UINT32_C(0x7fff0000)));target=sx(UINT32_C(0x80006cac));goto dispatch;
L_80006cac:
 STEP(UINT32_C(0x80006cac)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x80006cb0));goto dispatch;
L_80006cb0:
 STEP(UINT32_C(0x80006cb0)); /* 00821024 and v0,a0,v0 */
 set(m,2u,lo(m,4u)&lo(m,2u));target=sx(UINT32_C(0x80006cb4));goto dispatch;
L_80006cb4:
 STEP(UINT32_C(0x80006cb4)); /* 2c430020 sltiu v1,v0,32 */
 set(m,3u,(lo(m,2u)<UINT64_C(0x20)));target=sx(UINT32_C(0x80006cb8));goto dispatch;
L_80006cb8:
 STEP(UINT32_C(0x80006cb8)); /* 10600006 beq v1,zero,80006cd4 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x80006cbc));set(m,2u,sx((uint32_t)lo(m,2u)<<2u));target=sx(taken?UINT32_C(0x80006cd4):UINT32_C(0x80006cc0));goto dispatch;}
L_80006cbc:
 STEP(UINT32_C(0x80006cbc)); /* 00021080 sll v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<2u));target=sx(UINT32_C(0x80006cc0));goto dispatch;
L_80006cc0:
 STEP(UINT32_C(0x80006cc0)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006cc4));goto dispatch;
L_80006cc4:
 STEP(UINT32_C(0x80006cc4)); /* 00220821 addu at,at,v0 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80006cc8));goto dispatch;
L_80006cc8:
 STEP(UINT32_C(0x80006cc8)); /* 8c22e080 lw v0,-0x1f80(at) */
 READ((uint32_t)lo(m,1u)+UINT32_C(0xffffe080),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006ccc));goto dispatch;
L_80006ccc:
 STEP(UINT32_C(0x80006ccc)); /* 10000003 beq zero,zero,80006cdc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006cd0));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x80006cdc):UINT32_C(0x80006cd4));goto dispatch;}
L_80006cd0:
 STEP(UINT32_C(0x80006cd0)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006cd4));goto dispatch;
L_80006cd4:
 STEP(UINT32_C(0x80006cd4)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80006cd8));goto dispatch;
L_80006cd8:
 STEP(UINT32_C(0x80006cd8)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006cdc));goto dispatch;
L_80006cdc:
 STEP(UINT32_C(0x80006cdc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006ce0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_80006ce0:
 STEP(UINT32_C(0x80006ce0)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006ce4));goto dispatch;
L_80006ac8:
 STEP(UINT32_C(0x80006ac8)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006acc));goto dispatch;
L_80006acc:
 STEP(UINT32_C(0x80006acc)); /* 3463f200 ori v1,v1,0xf200 */
 set(m,3u,lo(m,3u) | UINT64_C(0xf200));target=sx(UINT32_C(0x80006ad0));goto dispatch;
L_80006ad0:
 STEP(UINT32_C(0x80006ad0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006ad4));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));goto dispatch;
L_80006ad4:
 STEP(UINT32_C(0x80006ad4)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006ad8));goto dispatch;
L_80006ad8:
 STEP(UINT32_C(0x80006ad8)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006adc));goto dispatch;
L_80006adc:
 STEP(UINT32_C(0x80006adc)); /* 3463f210 ori v1,v1,0xf210 */
 set(m,3u,lo(m,3u) | UINT64_C(0xf210));target=sx(UINT32_C(0x80006ae0));goto dispatch;
L_80006ae0:
 STEP(UINT32_C(0x80006ae0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006ae4));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));goto dispatch;
L_80006ae4:
 STEP(UINT32_C(0x80006ae4)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006ae8));goto dispatch;
L_80006a80:
 STEP(UINT32_C(0x80006a80)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80006a84));goto dispatch;
L_80006a84:
 STEP(UINT32_C(0x80006a84)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80006a88));goto dispatch;
L_80006a88:
 STEP(UINT32_C(0x80006a88)); /* 0c001796 jal 80005e58 */
 set(m,31u,UINT64_C(0x80006a90));STEP(UINT32_C(0x80006a8c));/* nop */target=sx(UINT32_C(0x80005e58));goto dispatch;
L_80006a8c:
 STEP(UINT32_C(0x80006a8c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006a90));goto dispatch;
L_80006a90:
 STEP(UINT32_C(0x80006a90)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006a94));goto dispatch;
L_80006a94:
 STEP(UINT32_C(0x80006a94)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006a98));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_80006a98:
 STEP(UINT32_C(0x80006a98)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006a9c));goto dispatch;
L_80006a38:
 STEP(UINT32_C(0x80006a38)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80006a3c));goto dispatch;
L_80006a3c:
 STEP(UINT32_C(0x80006a3c)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80006a40));goto dispatch;
L_80006a40:
 STEP(UINT32_C(0x80006a40)); /* 0c00175e jal 80005d78 */
 set(m,31u,UINT64_C(0x80006a48));STEP(UINT32_C(0x80006a44));/* nop */target=sx(UINT32_C(0x80005d78));goto dispatch;
L_80006a44:
 STEP(UINT32_C(0x80006a44)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80006a48));goto dispatch;
L_80006a48:
 STEP(UINT32_C(0x80006a48)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006a4c));goto dispatch;
L_80006a4c:
 STEP(UINT32_C(0x80006a4c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006a50));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_80006a50:
 STEP(UINT32_C(0x80006a50)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006a54));goto dispatch;
L_80006aa0:
 STEP(UINT32_C(0x80006aa0)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80006aa4));goto dispatch;
L_80006aa4:
 STEP(UINT32_C(0x80006aa4)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006aa8));goto dispatch;
L_80006aa8:
 STEP(UINT32_C(0x80006aa8)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80006aac));goto dispatch;
L_80006aac:
 STEP(UINT32_C(0x80006aac)); /* 3442f230 ori v0,v0,0xf230 */
 set(m,2u,lo(m,2u) | UINT64_C(0xf230));target=sx(UINT32_C(0x80006ab0));goto dispatch;
L_80006ab0:
 STEP(UINT32_C(0x80006ab0)); /* 0c001796 jal 80005e58 */
 set(m,31u,UINT64_C(0x80006ab8));STEP(UINT32_C(0x80006ab4));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80005e58));goto dispatch;
L_80006ab4:
 STEP(UINT32_C(0x80006ab4)); /* ac440000 sw a0,0x0(v0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006ab8));goto dispatch;
L_80006ab8:
 STEP(UINT32_C(0x80006ab8)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006abc));goto dispatch;
L_80006abc:
 STEP(UINT32_C(0x80006abc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006ac0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_80006ac0:
 STEP(UINT32_C(0x80006ac0)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006ac4));goto dispatch;
L_80006ae8:
 STEP(UINT32_C(0x80006ae8)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006aec));goto dispatch;
L_80006aec:
 STEP(UINT32_C(0x80006aec)); /* 3463f200 ori v1,v1,0xf200 */
 set(m,3u,lo(m,3u) | UINT64_C(0xf200));target=sx(UINT32_C(0x80006af0));goto dispatch;
L_80006af0:
 STEP(UINT32_C(0x80006af0)); /* ac640000 sw a0,0x0(v1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006af4));goto dispatch;
L_80006af4:
 STEP(UINT32_C(0x80006af4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006af8));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));goto dispatch;
L_80006af8:
 STEP(UINT32_C(0x80006af8)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006afc));goto dispatch;
L_80006a58:
 STEP(UINT32_C(0x80006a58)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80006a5c));goto dispatch;
L_80006a5c:
 STEP(UINT32_C(0x80006a5c)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006a60));goto dispatch;
L_80006a60:
 STEP(UINT32_C(0x80006a60)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80006a64));goto dispatch;
L_80006a64:
 STEP(UINT32_C(0x80006a64)); /* 3442f220 ori v0,v0,0xf220 */
 set(m,2u,lo(m,2u) | UINT64_C(0xf220));target=sx(UINT32_C(0x80006a68));goto dispatch;
L_80006a68:
 STEP(UINT32_C(0x80006a68)); /* 0c00175e jal 80005d78 */
 set(m,31u,UINT64_C(0x80006a70));STEP(UINT32_C(0x80006a6c));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80005d78));goto dispatch;
L_80006a6c:
 STEP(UINT32_C(0x80006a6c)); /* ac440000 sw a0,0x0(v0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006a70));goto dispatch;
L_80006a70:
 STEP(UINT32_C(0x80006a70)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006a74));goto dispatch;
L_80006a74:
 STEP(UINT32_C(0x80006a74)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006a78));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_80006a78:
 STEP(UINT32_C(0x80006a78)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006a7c));goto dispatch;
L_80005e58:
 STEP(UINT32_C(0x80005e58)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80005e5c));goto dispatch;
L_80005e5c:
 STEP(UINT32_C(0x80005e5c)); /* 3442f230 ori v0,v0,0xf230 */
 set(m,2u,lo(m,2u) | UINT64_C(0xf230));target=sx(UINT32_C(0x80005e60));goto dispatch;
L_80005e60:
 STEP(UINT32_C(0x80005e60)); /* 8c440000 lw a0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80005e64));goto dispatch;
L_80005e64:
 STEP(UINT32_C(0x80005e64)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e68));goto dispatch;
L_80005e68:
 STEP(UINT32_C(0x80005e68)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e6c));goto dispatch;
L_80005e6c:
 STEP(UINT32_C(0x80005e6c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e70));goto dispatch;
L_80005e70:
 STEP(UINT32_C(0x80005e70)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e74));goto dispatch;
L_80005e74:
 STEP(UINT32_C(0x80005e74)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e78));goto dispatch;
L_80005e78:
 STEP(UINT32_C(0x80005e78)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e7c));goto dispatch;
L_80005e7c:
 STEP(UINT32_C(0x80005e7c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e80));goto dispatch;
L_80005e80:
 STEP(UINT32_C(0x80005e80)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e84));goto dispatch;
L_80005e84:
 STEP(UINT32_C(0x80005e84)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e88));goto dispatch;
L_80005e88:
 STEP(UINT32_C(0x80005e88)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e8c));goto dispatch;
L_80005e8c:
 STEP(UINT32_C(0x80005e8c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e90));goto dispatch;
L_80005e90:
 STEP(UINT32_C(0x80005e90)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e94));goto dispatch;
L_80005e94:
 STEP(UINT32_C(0x80005e94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e98));goto dispatch;
L_80005e98:
 STEP(UINT32_C(0x80005e98)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e9c));goto dispatch;
L_80005e9c:
 STEP(UINT32_C(0x80005e9c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ea0));goto dispatch;
L_80005ea0:
 STEP(UINT32_C(0x80005ea0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ea4));goto dispatch;
L_80005ea4:
 STEP(UINT32_C(0x80005ea4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ea8));goto dispatch;
L_80005ea8:
 STEP(UINT32_C(0x80005ea8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005eac));goto dispatch;
L_80005eac:
 STEP(UINT32_C(0x80005eac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005eb0));goto dispatch;
L_80005eb0:
 STEP(UINT32_C(0x80005eb0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005eb4));goto dispatch;
L_80005eb4:
 STEP(UINT32_C(0x80005eb4)); /* 8c420000 lw v0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005eb8));goto dispatch;
L_80005eb8:
 STEP(UINT32_C(0x80005eb8)); /* 1082001c beq a0,v0,80005f2c */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80005ebc));/* nop */target=sx(taken?UINT32_C(0x80005f2c):UINT32_C(0x80005ec0));goto dispatch;}
L_80005ebc:
 STEP(UINT32_C(0x80005ebc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ec0));goto dispatch;
L_80005ec0:
 STEP(UINT32_C(0x80005ec0)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80005ec4));goto dispatch;
L_80005ec4:
 STEP(UINT32_C(0x80005ec4)); /* 3463f230 ori v1,v1,0xf230 */
 set(m,3u,lo(m,3u) | UINT64_C(0xf230));target=sx(UINT32_C(0x80005ec8));goto dispatch;
L_80005ec8:
 STEP(UINT32_C(0x80005ec8)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80005ecc));goto dispatch;
L_80005ecc:
 STEP(UINT32_C(0x80005ecc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ed0));goto dispatch;
L_80005ed0:
 STEP(UINT32_C(0x80005ed0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ed4));goto dispatch;
L_80005ed4:
 STEP(UINT32_C(0x80005ed4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ed8));goto dispatch;
L_80005ed8:
 STEP(UINT32_C(0x80005ed8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005edc));goto dispatch;
L_80005edc:
 STEP(UINT32_C(0x80005edc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ee0));goto dispatch;
L_80005ee0:
 STEP(UINT32_C(0x80005ee0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ee4));goto dispatch;
L_80005ee4:
 STEP(UINT32_C(0x80005ee4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ee8));goto dispatch;
L_80005ee8:
 STEP(UINT32_C(0x80005ee8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005eec));goto dispatch;
L_80005eec:
 STEP(UINT32_C(0x80005eec)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ef0));goto dispatch;
L_80005ef0:
 STEP(UINT32_C(0x80005ef0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ef4));goto dispatch;
L_80005ef4:
 STEP(UINT32_C(0x80005ef4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005ef8));goto dispatch;
L_80005ef8:
 STEP(UINT32_C(0x80005ef8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005efc));goto dispatch;
L_80005efc:
 STEP(UINT32_C(0x80005efc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f00));goto dispatch;
L_80005f00:
 STEP(UINT32_C(0x80005f00)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f04));goto dispatch;
L_80005f04:
 STEP(UINT32_C(0x80005f04)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f08));goto dispatch;
L_80005f08:
 STEP(UINT32_C(0x80005f08)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f0c));goto dispatch;
L_80005f0c:
 STEP(UINT32_C(0x80005f0c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f10));goto dispatch;
L_80005f10:
 STEP(UINT32_C(0x80005f10)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f14));goto dispatch;
L_80005f14:
 STEP(UINT32_C(0x80005f14)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f18));goto dispatch;
L_80005f18:
 STEP(UINT32_C(0x80005f18)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f1c));goto dispatch;
L_80005f1c:
 STEP(UINT32_C(0x80005f1c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005f20));goto dispatch;
L_80005f20:
 STEP(UINT32_C(0x80005f20)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005f24));goto dispatch;
L_80005f24:
 STEP(UINT32_C(0x80005f24)); /* 5482ffea bnel a0,v0,80005ed0 */
 if(lo(m,4u)!=lo(m,2u)){STEP(UINT32_C(0x80005f28));set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80005ed0));}else target=sx(UINT32_C(0x80005f2c));goto dispatch;
L_80005f28:
 STEP(UINT32_C(0x80005f28)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80005f2c));goto dispatch;
L_80005f2c:
 STEP(UINT32_C(0x80005f2c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80005f30));set(m,2u,lo(m,4u)+lo(m,0u));goto dispatch;
L_80005f30:
 STEP(UINT32_C(0x80005f30)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80005f34));goto dispatch;
L_80005d78:
 STEP(UINT32_C(0x80005d78)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80005d7c));goto dispatch;
L_80005d7c:
 STEP(UINT32_C(0x80005d7c)); /* 3442f220 ori v0,v0,0xf220 */
 set(m,2u,lo(m,2u) | UINT64_C(0xf220));target=sx(UINT32_C(0x80005d80));goto dispatch;
L_80005d80:
 STEP(UINT32_C(0x80005d80)); /* 8c440000 lw a0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80005d84));goto dispatch;
L_80005d84:
 STEP(UINT32_C(0x80005d84)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005d88));goto dispatch;
L_80005d88:
 STEP(UINT32_C(0x80005d88)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005d8c));goto dispatch;
L_80005d8c:
 STEP(UINT32_C(0x80005d8c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005d90));goto dispatch;
L_80005d90:
 STEP(UINT32_C(0x80005d90)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005d94));goto dispatch;
L_80005d94:
 STEP(UINT32_C(0x80005d94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005d98));goto dispatch;
L_80005d98:
 STEP(UINT32_C(0x80005d98)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005d9c));goto dispatch;
L_80005d9c:
 STEP(UINT32_C(0x80005d9c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005da0));goto dispatch;
L_80005da0:
 STEP(UINT32_C(0x80005da0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005da4));goto dispatch;
L_80005da4:
 STEP(UINT32_C(0x80005da4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005da8));goto dispatch;
L_80005da8:
 STEP(UINT32_C(0x80005da8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dac));goto dispatch;
L_80005dac:
 STEP(UINT32_C(0x80005dac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005db0));goto dispatch;
L_80005db0:
 STEP(UINT32_C(0x80005db0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005db4));goto dispatch;
L_80005db4:
 STEP(UINT32_C(0x80005db4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005db8));goto dispatch;
L_80005db8:
 STEP(UINT32_C(0x80005db8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dbc));goto dispatch;
L_80005dbc:
 STEP(UINT32_C(0x80005dbc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dc0));goto dispatch;
L_80005dc0:
 STEP(UINT32_C(0x80005dc0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dc4));goto dispatch;
L_80005dc4:
 STEP(UINT32_C(0x80005dc4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dc8));goto dispatch;
L_80005dc8:
 STEP(UINT32_C(0x80005dc8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dcc));goto dispatch;
L_80005dcc:
 STEP(UINT32_C(0x80005dcc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dd0));goto dispatch;
L_80005dd0:
 STEP(UINT32_C(0x80005dd0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dd4));goto dispatch;
L_80005dd4:
 STEP(UINT32_C(0x80005dd4)); /* 8c420000 lw v0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005dd8));goto dispatch;
L_80005dd8:
 STEP(UINT32_C(0x80005dd8)); /* 1082001c beq a0,v0,80005e4c */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x80005ddc));/* nop */target=sx(taken?UINT32_C(0x80005e4c):UINT32_C(0x80005de0));goto dispatch;}
L_80005ddc:
 STEP(UINT32_C(0x80005ddc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005de0));goto dispatch;
L_80005de0:
 STEP(UINT32_C(0x80005de0)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80005de4));goto dispatch;
L_80005de4:
 STEP(UINT32_C(0x80005de4)); /* 3463f220 ori v1,v1,0xf220 */
 set(m,3u,lo(m,3u) | UINT64_C(0xf220));target=sx(UINT32_C(0x80005de8));goto dispatch;
L_80005de8:
 STEP(UINT32_C(0x80005de8)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80005dec));goto dispatch;
L_80005dec:
 STEP(UINT32_C(0x80005dec)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005df0));goto dispatch;
L_80005df0:
 STEP(UINT32_C(0x80005df0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005df4));goto dispatch;
L_80005df4:
 STEP(UINT32_C(0x80005df4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005df8));goto dispatch;
L_80005df8:
 STEP(UINT32_C(0x80005df8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005dfc));goto dispatch;
L_80005dfc:
 STEP(UINT32_C(0x80005dfc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e00));goto dispatch;
L_80005e00:
 STEP(UINT32_C(0x80005e00)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e04));goto dispatch;
L_80005e04:
 STEP(UINT32_C(0x80005e04)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e08));goto dispatch;
L_80005e08:
 STEP(UINT32_C(0x80005e08)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e0c));goto dispatch;
L_80005e0c:
 STEP(UINT32_C(0x80005e0c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e10));goto dispatch;
L_80005e10:
 STEP(UINT32_C(0x80005e10)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e14));goto dispatch;
L_80005e14:
 STEP(UINT32_C(0x80005e14)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e18));goto dispatch;
L_80005e18:
 STEP(UINT32_C(0x80005e18)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e1c));goto dispatch;
L_80005e1c:
 STEP(UINT32_C(0x80005e1c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e20));goto dispatch;
L_80005e20:
 STEP(UINT32_C(0x80005e20)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e24));goto dispatch;
L_80005e24:
 STEP(UINT32_C(0x80005e24)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e28));goto dispatch;
L_80005e28:
 STEP(UINT32_C(0x80005e28)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e2c));goto dispatch;
L_80005e2c:
 STEP(UINT32_C(0x80005e2c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e30));goto dispatch;
L_80005e30:
 STEP(UINT32_C(0x80005e30)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e34));goto dispatch;
L_80005e34:
 STEP(UINT32_C(0x80005e34)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e38));goto dispatch;
L_80005e38:
 STEP(UINT32_C(0x80005e38)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e3c));goto dispatch;
L_80005e3c:
 STEP(UINT32_C(0x80005e3c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80005e40));goto dispatch;
L_80005e40:
 STEP(UINT32_C(0x80005e40)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005e44));goto dispatch;
L_80005e44:
 STEP(UINT32_C(0x80005e44)); /* 5482ffea bnel a0,v0,80005df0 */
 if(lo(m,4u)!=lo(m,2u)){STEP(UINT32_C(0x80005e48));set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80005df0));}else target=sx(UINT32_C(0x80005e4c));goto dispatch;
L_80005e48:
 STEP(UINT32_C(0x80005e48)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80005e4c));goto dispatch;
L_80005e4c:
 STEP(UINT32_C(0x80005e4c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80005e50));set(m,2u,lo(m,4u)+lo(m,0u));goto dispatch;
L_80005e50:
 STEP(UINT32_C(0x80005e50)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80005e54));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

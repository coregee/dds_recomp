#include "iop_heap_native.h"
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
static uint32_t plzcw(uint32_t v)
{uint32_t n=0;if(v&0x80000000u)v=~v;while(n<31u&&!(v&0x40000000u)){++n;v<<=1;}return n;}
uint32_t nocturneIopHeapResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002e2b98):goto L_002e2b98;
 case UINT32_C(0x002e2b9c):goto L_002e2b9c;
 case UINT32_C(0x002e2ba0):goto L_002e2ba0;
 case UINT32_C(0x002e2ba4):goto L_002e2ba4;
 case UINT32_C(0x002e2ba8):goto L_002e2ba8;
 case UINT32_C(0x002e2bac):goto L_002e2bac;
 case UINT32_C(0x002e2bb0):goto L_002e2bb0;
 case UINT32_C(0x002e2bb4):goto L_002e2bb4;
 case UINT32_C(0x002e2bb8):goto L_002e2bb8;
 case UINT32_C(0x002e2bbc):goto L_002e2bbc;
 case UINT32_C(0x002e2bc0):goto L_002e2bc0;
 case UINT32_C(0x002e2bc4):goto L_002e2bc4;
 case UINT32_C(0x002e2bc8):goto L_002e2bc8;
 case UINT32_C(0x002e2bcc):goto L_002e2bcc;
 case UINT32_C(0x002e2bd0):goto L_002e2bd0;
 case UINT32_C(0x002e2bd4):goto L_002e2bd4;
 case UINT32_C(0x002e2bd8):goto L_002e2bd8;
 case UINT32_C(0x002e2bdc):goto L_002e2bdc;
 case UINT32_C(0x002e2be0):goto L_002e2be0;
 case UINT32_C(0x002e2be4):goto L_002e2be4;
 case UINT32_C(0x002e2be8):goto L_002e2be8;
 case UINT32_C(0x002e2bec):goto L_002e2bec;
 case UINT32_C(0x002e2bf0):goto L_002e2bf0;
 case UINT32_C(0x002e2bf4):goto L_002e2bf4;
 case UINT32_C(0x002e2bf8):goto L_002e2bf8;
 case UINT32_C(0x002e2bfc):goto L_002e2bfc;
 case UINT32_C(0x002e2c00):goto L_002e2c00;
 case UINT32_C(0x002e2c04):goto L_002e2c04;
 case UINT32_C(0x002e2c08):goto L_002e2c08;
 case UINT32_C(0x002e2c0c):goto L_002e2c0c;
 case UINT32_C(0x002e2c10):goto L_002e2c10;
 case UINT32_C(0x002e2c14):goto L_002e2c14;
 case UINT32_C(0x002e2c18):goto L_002e2c18;
 case UINT32_C(0x002e2c1c):goto L_002e2c1c;
 case UINT32_C(0x002e2c20):goto L_002e2c20;
 case UINT32_C(0x002e2c24):goto L_002e2c24;
 case UINT32_C(0x002e2c28):goto L_002e2c28;
 case UINT32_C(0x002e2c2c):goto L_002e2c2c;
 case UINT32_C(0x002e2c30):goto L_002e2c30;
 case UINT32_C(0x002e2c34):goto L_002e2c34;
 case UINT32_C(0x002e2c38):goto L_002e2c38;
 case UINT32_C(0x002e2c3c):goto L_002e2c3c;
 case UINT32_C(0x002e2c40):goto L_002e2c40;
 case UINT32_C(0x002e2c44):goto L_002e2c44;
 case UINT32_C(0x002e2c48):goto L_002e2c48;
 case UINT32_C(0x002e2c4c):goto L_002e2c4c;
 case UINT32_C(0x002e2c50):goto L_002e2c50;
 case UINT32_C(0x002e2c54):goto L_002e2c54;
 case UINT32_C(0x002e2c58):goto L_002e2c58;
 case UINT32_C(0x002e2c5c):goto L_002e2c5c;
 case UINT32_C(0x002e2c60):goto L_002e2c60;
 case UINT32_C(0x002e2c64):goto L_002e2c64;
 case UINT32_C(0x002e2c68):goto L_002e2c68;
 case UINT32_C(0x002e2c6c):goto L_002e2c6c;
 case UINT32_C(0x002e2c70):goto L_002e2c70;
 case UINT32_C(0x002e2c74):goto L_002e2c74;
 case UINT32_C(0x002e2c78):goto L_002e2c78;
 case UINT32_C(0x002e2c7c):goto L_002e2c7c;
 case UINT32_C(0x002e2c80):goto L_002e2c80;
 case UINT32_C(0x002e2c84):goto L_002e2c84;
 case UINT32_C(0x002e2c88):goto L_002e2c88;
 case UINT32_C(0x002e2c8c):goto L_002e2c8c;
 case UINT32_C(0x002e2c90):goto L_002e2c90;
 case UINT32_C(0x002e2c94):goto L_002e2c94;
 case UINT32_C(0x002e2c98):goto L_002e2c98;
 case UINT32_C(0x002e2c9c):goto L_002e2c9c;
 case UINT32_C(0x002e2ca0):goto L_002e2ca0;
 case UINT32_C(0x002e2ca4):goto L_002e2ca4;
 case UINT32_C(0x002e2ca8):goto L_002e2ca8;
 case UINT32_C(0x002e2cac):goto L_002e2cac;
 case UINT32_C(0x002e2cb0):goto L_002e2cb0;
 case UINT32_C(0x002e2cb4):goto L_002e2cb4;
 case UINT32_C(0x002e2cb8):goto L_002e2cb8;
 case UINT32_C(0x002e2cbc):goto L_002e2cbc;
 case UINT32_C(0x002e2cc0):goto L_002e2cc0;
 case UINT32_C(0x002e2cc4):goto L_002e2cc4;
 case UINT32_C(0x002e2cc8):goto L_002e2cc8;
 case UINT32_C(0x002e2ccc):goto L_002e2ccc;
 case UINT32_C(0x002e2cd0):goto L_002e2cd0;
 case UINT32_C(0x002e2cd4):goto L_002e2cd4;
 case UINT32_C(0x002e2cd8):goto L_002e2cd8;
 case UINT32_C(0x002e2cdc):goto L_002e2cdc;
 case UINT32_C(0x002e2ce0):goto L_002e2ce0;
 case UINT32_C(0x002e2ce4):goto L_002e2ce4;
 case UINT32_C(0x002e2ce8):goto L_002e2ce8;
 case UINT32_C(0x002e2cec):goto L_002e2cec;
 case UINT32_C(0x002e2cf0):goto L_002e2cf0;
 case UINT32_C(0x002e2cf4):goto L_002e2cf4;
 case UINT32_C(0x002e2cf8):goto L_002e2cf8;
 case UINT32_C(0x002e2cfc):goto L_002e2cfc;
 case UINT32_C(0x002e2d00):goto L_002e2d00;
 case UINT32_C(0x002e2d04):goto L_002e2d04;
 case UINT32_C(0x002e2d08):goto L_002e2d08;
 case UINT32_C(0x002e2d0c):goto L_002e2d0c;
 case UINT32_C(0x002e2d10):goto L_002e2d10;
 case UINT32_C(0x002e2d14):goto L_002e2d14;
 case UINT32_C(0x002e2d18):goto L_002e2d18;
 case UINT32_C(0x002e2d20):goto L_002e2d20;
 case UINT32_C(0x002e2d24):goto L_002e2d24;
 case UINT32_C(0x002e2d28):goto L_002e2d28;
 case UINT32_C(0x002e2d2c):goto L_002e2d2c;
 case UINT32_C(0x002e2d30):goto L_002e2d30;
 case UINT32_C(0x002e2d34):goto L_002e2d34;
 case UINT32_C(0x002e2d38):goto L_002e2d38;
 case UINT32_C(0x002e2d3c):goto L_002e2d3c;
 case UINT32_C(0x002e2d40):goto L_002e2d40;
 case UINT32_C(0x002e2d44):goto L_002e2d44;
 case UINT32_C(0x002e2d48):goto L_002e2d48;
 case UINT32_C(0x002e2d4c):goto L_002e2d4c;
 case UINT32_C(0x002e2d50):goto L_002e2d50;
 case UINT32_C(0x002e2d54):goto L_002e2d54;
 case UINT32_C(0x002e2d58):goto L_002e2d58;
 case UINT32_C(0x002e2d5c):goto L_002e2d5c;
 case UINT32_C(0x002e2d60):goto L_002e2d60;
 case UINT32_C(0x002e2d64):goto L_002e2d64;
 case UINT32_C(0x002e2d68):goto L_002e2d68;
 case UINT32_C(0x002e2d6c):goto L_002e2d6c;
 case UINT32_C(0x002e2d70):goto L_002e2d70;
 case UINT32_C(0x002e2d74):goto L_002e2d74;
 case UINT32_C(0x002e2d78):goto L_002e2d78;
 case UINT32_C(0x002e2d7c):goto L_002e2d7c;
 case UINT32_C(0x002e2d80):goto L_002e2d80;
 case UINT32_C(0x002e2d84):goto L_002e2d84;
 case UINT32_C(0x002e2d88):goto L_002e2d88;
 case UINT32_C(0x002e2d8c):goto L_002e2d8c;
 case UINT32_C(0x002e2d90):goto L_002e2d90;
 case UINT32_C(0x002e2d94):goto L_002e2d94;
 case UINT32_C(0x002e2d98):goto L_002e2d98;
 case UINT32_C(0x002e2d9c):goto L_002e2d9c;
 case UINT32_C(0x002e2da0):goto L_002e2da0;
 case UINT32_C(0x002e2da4):goto L_002e2da4;
 case UINT32_C(0x002e2da8):goto L_002e2da8;
 case UINT32_C(0x002e2dac):goto L_002e2dac;
 case UINT32_C(0x002e2db0):goto L_002e2db0;
 case UINT32_C(0x002e2db4):goto L_002e2db4;
 case UINT32_C(0x002e2db8):goto L_002e2db8;
 case UINT32_C(0x002e2dbc):goto L_002e2dbc;
 case UINT32_C(0x002e2dc0):goto L_002e2dc0;
 case UINT32_C(0x002e2dc4):goto L_002e2dc4;
 case UINT32_C(0x002e2dc8):goto L_002e2dc8;
 case UINT32_C(0x002e2dcc):goto L_002e2dcc;
 case UINT32_C(0x002e2dd0):goto L_002e2dd0;
 case UINT32_C(0x002e2dd4):goto L_002e2dd4;
 case UINT32_C(0x002e2dd8):goto L_002e2dd8;
 case UINT32_C(0x002e2ddc):goto L_002e2ddc;
 case UINT32_C(0x002e2de0):goto L_002e2de0;
 case UINT32_C(0x002e2de4):goto L_002e2de4;
 case UINT32_C(0x002e2de8):goto L_002e2de8;
 case UINT32_C(0x002e2dec):goto L_002e2dec;
 case UINT32_C(0x002e2df0):goto L_002e2df0;
 case UINT32_C(0x002e2df4):goto L_002e2df4;
 case UINT32_C(0x002e2df8):goto L_002e2df8;
 case UINT32_C(0x002e2dfc):goto L_002e2dfc;
 case UINT32_C(0x002e2e00):goto L_002e2e00;
 case UINT32_C(0x002e2e04):goto L_002e2e04;
 case UINT32_C(0x002e2e08):goto L_002e2e08;
 case UINT32_C(0x002e2e0c):goto L_002e2e0c;
 case UINT32_C(0x002e2e10):goto L_002e2e10;
 case UINT32_C(0x002e2e14):goto L_002e2e14;
 case UINT32_C(0x002e2e18):goto L_002e2e18;
 case UINT32_C(0x002e2e1c):goto L_002e2e1c;
 case UINT32_C(0x002e2e20):goto L_002e2e20;
 case UINT32_C(0x002e2e24):goto L_002e2e24;
 case UINT32_C(0x002e2e28):goto L_002e2e28;
 case UINT32_C(0x002e2e2c):goto L_002e2e2c;
 case UINT32_C(0x002e2e30):goto L_002e2e30;
 case UINT32_C(0x002e2e34):goto L_002e2e34;
 case UINT32_C(0x002e2e38):goto L_002e2e38;
 case UINT32_C(0x002e2e3c):goto L_002e2e3c;
 case UINT32_C(0x002e2e40):goto L_002e2e40;
 case UINT32_C(0x002e2e44):goto L_002e2e44;
 case UINT32_C(0x002e2e48):goto L_002e2e48;
 case UINT32_C(0x002e2e4c):goto L_002e2e4c;
 case UINT32_C(0x002e2e50):goto L_002e2e50;
 case UINT32_C(0x002e2e54):goto L_002e2e54;
 case UINT32_C(0x002e2e58):goto L_002e2e58;
 case UINT32_C(0x002e2e5c):goto L_002e2e5c;
 case UINT32_C(0x002e2e60):goto L_002e2e60;
 case UINT32_C(0x002e2e64):goto L_002e2e64;
 case UINT32_C(0x002e2e68):goto L_002e2e68;
 case UINT32_C(0x002e2e6c):goto L_002e2e6c;
 case UINT32_C(0x002e2e70):goto L_002e2e70;
 case UINT32_C(0x002e2e74):goto L_002e2e74;
 case UINT32_C(0x002e2e78):goto L_002e2e78;
 case UINT32_C(0x002e2e7c):goto L_002e2e7c;
 case UINT32_C(0x002e2e80):goto L_002e2e80;
 case UINT32_C(0x002e2e84):goto L_002e2e84;
 case UINT32_C(0x002e2e88):goto L_002e2e88;
 case UINT32_C(0x002e2e8c):goto L_002e2e8c;
 case UINT32_C(0x002e2e90):goto L_002e2e90;
 case UINT32_C(0x002e2e94):goto L_002e2e94;
 case UINT32_C(0x002e2e98):goto L_002e2e98;
 case UINT32_C(0x002e2e9c):goto L_002e2e9c;
 case UINT32_C(0x002e2ea0):goto L_002e2ea0;
 case UINT32_C(0x002e2ea4):goto L_002e2ea4;
 case UINT32_C(0x002e2ea8):goto L_002e2ea8;
 case UINT32_C(0x002e2eac):goto L_002e2eac;
 case UINT32_C(0x002e2eb0):goto L_002e2eb0;
 case UINT32_C(0x002e2eb4):goto L_002e2eb4;
 case UINT32_C(0x002e2eb8):goto L_002e2eb8;
 case UINT32_C(0x002e2ebc):goto L_002e2ebc;
 case UINT32_C(0x002e2ec0):goto L_002e2ec0;
 case UINT32_C(0x002e2ec4):goto L_002e2ec4;
 case UINT32_C(0x002e2ec8):goto L_002e2ec8;
 case UINT32_C(0x002e2ecc):goto L_002e2ecc;
 case UINT32_C(0x002e2ed0):goto L_002e2ed0;
 case UINT32_C(0x002e2ed4):goto L_002e2ed4;
 case UINT32_C(0x002e2ed8):goto L_002e2ed8;
 case UINT32_C(0x002e2edc):goto L_002e2edc;
 case UINT32_C(0x002e2ee0):goto L_002e2ee0;
 case UINT32_C(0x002e2ee4):goto L_002e2ee4;
 case UINT32_C(0x002e2ee8):goto L_002e2ee8;
 case UINT32_C(0x002e2eec):goto L_002e2eec;
 case UINT32_C(0x002e2ef0):goto L_002e2ef0;
 case UINT32_C(0x002e2ef4):goto L_002e2ef4;
 case UINT32_C(0x002e2ef8):goto L_002e2ef8;
 case UINT32_C(0x002e2efc):goto L_002e2efc;
 case UINT32_C(0x002e2f00):goto L_002e2f00;
 case UINT32_C(0x002e2f04):goto L_002e2f04;
 case UINT32_C(0x002e2f08):goto L_002e2f08;
 case UINT32_C(0x002e2f0c):goto L_002e2f0c;
 case UINT32_C(0x002e2f10):goto L_002e2f10;
 case UINT32_C(0x002e2f14):goto L_002e2f14;
 case UINT32_C(0x002e2f18):goto L_002e2f18;
 case UINT32_C(0x002e2f1c):goto L_002e2f1c;
 case UINT32_C(0x002e2f20):goto L_002e2f20;
 case UINT32_C(0x002e2f24):goto L_002e2f24;
 case UINT32_C(0x002e2f28):goto L_002e2f28;
 case UINT32_C(0x002e2f2c):goto L_002e2f2c;
 case UINT32_C(0x002e2f30):goto L_002e2f30;
 case UINT32_C(0x002e2f34):goto L_002e2f34;
 case UINT32_C(0x002e2f38):goto L_002e2f38;
 case UINT32_C(0x002e2f3c):goto L_002e2f3c;
 case UINT32_C(0x002e2f40):goto L_002e2f40;
 case UINT32_C(0x002e2f44):goto L_002e2f44;
 case UINT32_C(0x002e2f48):goto L_002e2f48;
 case UINT32_C(0x002e2f4c):goto L_002e2f4c;
 case UINT32_C(0x002e2f50):goto L_002e2f50;
 case UINT32_C(0x002e2f54):goto L_002e2f54;
 case UINT32_C(0x002e2f58):goto L_002e2f58;
 case UINT32_C(0x002e2f5c):goto L_002e2f5c;
 case UINT32_C(0x002e2f60):goto L_002e2f60;
 case UINT32_C(0x002e2f64):goto L_002e2f64;
 case UINT32_C(0x002e2f68):goto L_002e2f68;
 case UINT32_C(0x002e2f6c):goto L_002e2f6c;
 case UINT32_C(0x002e2f70):goto L_002e2f70;
 case UINT32_C(0x002e2f74):goto L_002e2f74;
 case UINT32_C(0x002e2f78):goto L_002e2f78;
 case UINT32_C(0x002e2f7c):goto L_002e2f7c;
 case UINT32_C(0x002e2f80):goto L_002e2f80;
 case UINT32_C(0x002e2f84):goto L_002e2f84;
 case UINT32_C(0x002e2f88):goto L_002e2f88;
 case UINT32_C(0x002e2f8c):goto L_002e2f8c;
 case UINT32_C(0x002e2f90):goto L_002e2f90;
 case UINT32_C(0x002e2f94):goto L_002e2f94;
 case UINT32_C(0x002e2f98):goto L_002e2f98;
 case UINT32_C(0x002e2f9c):goto L_002e2f9c;
 case UINT32_C(0x002e2fa0):goto L_002e2fa0;
 case UINT32_C(0x002e2fa4):goto L_002e2fa4;
 case UINT32_C(0x002e2fa8):goto L_002e2fa8;
 case UINT32_C(0x002e2fac):goto L_002e2fac;
 case UINT32_C(0x002e2fb0):goto L_002e2fb0;
 case UINT32_C(0x002e2fb4):goto L_002e2fb4;
 case UINT32_C(0x002e2fb8):goto L_002e2fb8;
 case UINT32_C(0x002e2fbc):goto L_002e2fbc;
 case UINT32_C(0x002e2fc0):goto L_002e2fc0;
 case UINT32_C(0x002e2fc4):goto L_002e2fc4;
 case UINT32_C(0x002e2fc8):goto L_002e2fc8;
 case UINT32_C(0x002e2fcc):goto L_002e2fcc;
 case UINT32_C(0x002e2fd0):goto L_002e2fd0;
 case UINT32_C(0x002e2fd4):goto L_002e2fd4;
 case UINT32_C(0x002e2fd8):goto L_002e2fd8;
 case UINT32_C(0x002e2fe0):goto L_002e2fe0;
 case UINT32_C(0x002e2fe4):goto L_002e2fe4;
 case UINT32_C(0x002e2fe8):goto L_002e2fe8;
 case UINT32_C(0x002e2fec):goto L_002e2fec;
 case UINT32_C(0x002e2ff0):goto L_002e2ff0;
 case UINT32_C(0x002e2ff4):goto L_002e2ff4;
 case UINT32_C(0x002e2ff8):goto L_002e2ff8;
 case UINT32_C(0x002e2ffc):goto L_002e2ffc;
 case UINT32_C(0x002e3000):goto L_002e3000;
 case UINT32_C(0x002e3004):goto L_002e3004;
 case UINT32_C(0x002e3008):goto L_002e3008;
 case UINT32_C(0x002e300c):goto L_002e300c;
 case UINT32_C(0x002e3010):goto L_002e3010;
 case UINT32_C(0x002e3014):goto L_002e3014;
 case UINT32_C(0x002e3018):goto L_002e3018;
 case UINT32_C(0x002e301c):goto L_002e301c;
 case UINT32_C(0x002e3020):goto L_002e3020;
 case UINT32_C(0x002e3024):goto L_002e3024;
 case UINT32_C(0x002e3028):goto L_002e3028;
 case UINT32_C(0x002e302c):goto L_002e302c;
 case UINT32_C(0x002e3030):goto L_002e3030;
 case UINT32_C(0x002e3034):goto L_002e3034;
 case UINT32_C(0x002e3038):goto L_002e3038;
 case UINT32_C(0x002e303c):goto L_002e303c;
 case UINT32_C(0x002e3040):goto L_002e3040;
 case UINT32_C(0x002e3044):goto L_002e3044;
 case UINT32_C(0x002e3048):goto L_002e3048;
 case UINT32_C(0x002e304c):goto L_002e304c;
 case UINT32_C(0x002e3050):goto L_002e3050;
 case UINT32_C(0x002e3054):goto L_002e3054;
 case UINT32_C(0x002e3058):goto L_002e3058;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002e2b98:
 STEP(UINT32_C(0x002e2b98)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2b9c));goto dispatch;
L_002e2b9c:
 STEP(UINT32_C(0x002e2b9c)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2ba0));goto dispatch;
L_002e2ba0:
 STEP(UINT32_C(0x002e2ba0)); /* 8c62c354 lw v0,-0x3cac(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffc354),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2ba4));goto dispatch;
L_002e2ba4:
 STEP(UINT32_C(0x002e2ba4)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e2ba8));goto dispatch;
L_002e2ba8:
 STEP(UINT32_C(0x002e2ba8)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2bac));goto dispatch;
L_002e2bac:
 STEP(UINT32_C(0x002e2bac)); /* 04400011 regimm0 v0,002e2bf4 */
 {int taken=((int64_t)lo(m,2u)<0);STEP(UINT32_C(0x002e2bb0));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e2bf4):UINT32_C(0x002e2bb4));goto dispatch;}
L_002e2bb0:
 STEP(UINT32_C(0x002e2bb0)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2bb4));goto dispatch;
L_002e2bb4:
 STEP(UINT32_C(0x002e2bb4)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2bb8));goto dispatch;
L_002e2bb8:
 STEP(UINT32_C(0x002e2bb8)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2bbc));goto dispatch;
L_002e2bbc:
 STEP(UINT32_C(0x002e2bbc)); /* ace5e8c0 sw a1,-0x1740(a3) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffffe8c0),&value32,4u);target=sx(UINT32_C(0x002e2bc0));goto dispatch;
L_002e2bc0:
 STEP(UINT32_C(0x002e2bc0)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2bc4));goto dispatch;
L_002e2bc4:
 STEP(UINT32_C(0x002e2bc4)); /* 2484e840 addiu a0,a0,-6080 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2bc8));goto dispatch;
L_002e2bc8:
 STEP(UINT32_C(0x002e2bc8)); /* 24e7e8c0 addiu a3,a3,-5952 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffe8c0)));target=sx(UINT32_C(0x002e2bcc));goto dispatch;
L_002e2bcc:
 STEP(UINT32_C(0x002e2bcc)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e2bd0));goto dispatch;
L_002e2bd0:
 STEP(UINT32_C(0x002e2bd0)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002e2bd4));goto dispatch;
L_002e2bd4:
 STEP(UINT32_C(0x002e2bd4)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2bd8));goto dispatch;
L_002e2bd8:
 STEP(UINT32_C(0x002e2bd8)); /* 24080004 addiu t0,zero,4 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2bdc));goto dispatch;
L_002e2bdc:
 STEP(UINT32_C(0x002e2bdc)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e2be0));goto dispatch;
L_002e2be0:
 STEP(UINT32_C(0x002e2be0)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2be4));goto dispatch;
L_002e2be4:
 STEP(UINT32_C(0x002e2be4)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e2bec));STEP(UINT32_C(0x002e2be8));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e2be8:
 STEP(UINT32_C(0x002e2be8)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2bec));goto dispatch;
L_002e2bec:
 STEP(UINT32_C(0x002e2bec)); /* 04410002 regimm1 v0,002e2bf8 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e2bf0));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002e2bf8):UINT32_C(0x002e2bf4));goto dispatch;}
L_002e2bf0:
 STEP(UINT32_C(0x002e2bf0)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2bf4));goto dispatch;
L_002e2bf4:
 STEP(UINT32_C(0x002e2bf4)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2bf8));goto dispatch;
L_002e2bf8:
 STEP(UINT32_C(0x002e2bf8)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2bfc));goto dispatch;
L_002e2bfc:
 STEP(UINT32_C(0x002e2bfc)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2c00));goto dispatch;
L_002e2c00:
 STEP(UINT32_C(0x002e2c00)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2c04));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2c04:
 STEP(UINT32_C(0x002e2c04)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2c08));goto dispatch;
L_002e2c08:
 STEP(UINT32_C(0x002e2c08)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2c0c));goto dispatch;
L_002e2c0c:
 STEP(UINT32_C(0x002e2c0c)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2c10));goto dispatch;
L_002e2c10:
 STEP(UINT32_C(0x002e2c10)); /* 8c43c354 lw v1,-0x3cac(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc354),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002e2c14));goto dispatch;
L_002e2c14:
 STEP(UINT32_C(0x002e2c14)); /* 0080382d daddu a3,a0,zero */
 set(m,7u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e2c18));goto dispatch;
L_002e2c18:
 STEP(UINT32_C(0x002e2c18)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2c1c));goto dispatch;
L_002e2c1c:
 STEP(UINT32_C(0x002e2c1c)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2c20));goto dispatch;
L_002e2c20:
 STEP(UINT32_C(0x002e2c20)); /* 04600015 regimm0 v1,002e2c78 */
 {int taken=((int64_t)lo(m,3u)<0);STEP(UINT32_C(0x002e2c24));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e2c78):UINT32_C(0x002e2c28));goto dispatch;}
L_002e2c24:
 STEP(UINT32_C(0x002e2c24)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2c28));goto dispatch;
L_002e2c28:
 STEP(UINT32_C(0x002e2c28)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2c2c));goto dispatch;
L_002e2c2c:
 STEP(UINT32_C(0x002e2c2c)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2c30));goto dispatch;
L_002e2c30:
 STEP(UINT32_C(0x002e2c30)); /* 2443e8c0 addiu v1,v0,-5952 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffe8c0)));target=sx(UINT32_C(0x002e2c34));goto dispatch;
L_002e2c34:
 STEP(UINT32_C(0x002e2c34)); /* ac45e8c0 sw a1,-0x1740(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffffe8c0),&value32,4u);target=sx(UINT32_C(0x002e2c38));goto dispatch;
L_002e2c38:
 STEP(UINT32_C(0x002e2c38)); /* ac670004 sw a3,0x4(v1) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002e2c3c));goto dispatch;
L_002e2c3c:
 STEP(UINT32_C(0x002e2c3c)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2c40));goto dispatch;
L_002e2c40:
 STEP(UINT32_C(0x002e2c40)); /* ac660008 sw a2,0x8(v1) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002e2c44));goto dispatch;
L_002e2c44:
 STEP(UINT32_C(0x002e2c44)); /* 2484e840 addiu a0,a0,-6080 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2c48));goto dispatch;
L_002e2c48:
 STEP(UINT32_C(0x002e2c48)); /* 0060382d daddu a3,v1,zero */
 set(m,7u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002e2c4c));goto dispatch;
L_002e2c4c:
 STEP(UINT32_C(0x002e2c4c)); /* 24050004 addiu a1,zero,4 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2c50));goto dispatch;
L_002e2c50:
 STEP(UINT32_C(0x002e2c50)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e2c54));goto dispatch;
L_002e2c54:
 STEP(UINT32_C(0x002e2c54)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2c58));goto dispatch;
L_002e2c58:
 STEP(UINT32_C(0x002e2c58)); /* 2408000c addiu t0,zero,12 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002e2c5c));goto dispatch;
L_002e2c5c:
 STEP(UINT32_C(0x002e2c5c)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e2c60));goto dispatch;
L_002e2c60:
 STEP(UINT32_C(0x002e2c60)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2c64));goto dispatch;
L_002e2c64:
 STEP(UINT32_C(0x002e2c64)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e2c6c));STEP(UINT32_C(0x002e2c68));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e2c68:
 STEP(UINT32_C(0x002e2c68)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2c6c));goto dispatch;
L_002e2c6c:
 STEP(UINT32_C(0x002e2c6c)); /* 04410002 regimm1 v0,002e2c78 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e2c70));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002e2c78):UINT32_C(0x002e2c74));goto dispatch;}
L_002e2c70:
 STEP(UINT32_C(0x002e2c70)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2c74));goto dispatch;
L_002e2c74:
 STEP(UINT32_C(0x002e2c74)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2c78));goto dispatch;
L_002e2c78:
 STEP(UINT32_C(0x002e2c78)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2c7c));goto dispatch;
L_002e2c7c:
 STEP(UINT32_C(0x002e2c7c)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2c80));goto dispatch;
L_002e2c80:
 STEP(UINT32_C(0x002e2c80)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2c84));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2c84:
 STEP(UINT32_C(0x002e2c84)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2c88));goto dispatch;
L_002e2c88:
 STEP(UINT32_C(0x002e2c88)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2c8c));goto dispatch;
L_002e2c8c:
 STEP(UINT32_C(0x002e2c8c)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2c90));goto dispatch;
L_002e2c90:
 STEP(UINT32_C(0x002e2c90)); /* 8c62c354 lw v0,-0x3cac(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffc354),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2c94));goto dispatch;
L_002e2c94:
 STEP(UINT32_C(0x002e2c94)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e2c98));goto dispatch;
L_002e2c98:
 STEP(UINT32_C(0x002e2c98)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2c9c));goto dispatch;
L_002e2c9c:
 STEP(UINT32_C(0x002e2c9c)); /* 04410003 regimm1 v0,002e2cac */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e2ca0));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e2cac):UINT32_C(0x002e2ca4));goto dispatch;}
L_002e2ca0:
 STEP(UINT32_C(0x002e2ca0)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2ca4));goto dispatch;
L_002e2ca4:
 STEP(UINT32_C(0x002e2ca4)); /* 10000012 beq zero,zero,002e2cf0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2ca8));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e2cf0):UINT32_C(0x002e2cac));goto dispatch;}
L_002e2ca8:
 STEP(UINT32_C(0x002e2ca8)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2cac));goto dispatch;
L_002e2cac:
 STEP(UINT32_C(0x002e2cac)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2cb0));goto dispatch;
L_002e2cb0:
 STEP(UINT32_C(0x002e2cb0)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2cb4));goto dispatch;
L_002e2cb4:
 STEP(UINT32_C(0x002e2cb4)); /* ace5e8c0 sw a1,-0x1740(a3) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffffe8c0),&value32,4u);target=sx(UINT32_C(0x002e2cb8));goto dispatch;
L_002e2cb8:
 STEP(UINT32_C(0x002e2cb8)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2cbc));goto dispatch;
L_002e2cbc:
 STEP(UINT32_C(0x002e2cbc)); /* 2484e840 addiu a0,a0,-6080 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2cc0));goto dispatch;
L_002e2cc0:
 STEP(UINT32_C(0x002e2cc0)); /* 24e7e8c0 addiu a3,a3,-5952 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffe8c0)));target=sx(UINT32_C(0x002e2cc4));goto dispatch;
L_002e2cc4:
 STEP(UINT32_C(0x002e2cc4)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e2cc8));goto dispatch;
L_002e2cc8:
 STEP(UINT32_C(0x002e2cc8)); /* 24050002 addiu a1,zero,2 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002e2ccc));goto dispatch;
L_002e2ccc:
 STEP(UINT32_C(0x002e2ccc)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2cd0));goto dispatch;
L_002e2cd0:
 STEP(UINT32_C(0x002e2cd0)); /* 24080004 addiu t0,zero,4 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2cd4));goto dispatch;
L_002e2cd4:
 STEP(UINT32_C(0x002e2cd4)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e2cd8));goto dispatch;
L_002e2cd8:
 STEP(UINT32_C(0x002e2cd8)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2cdc));goto dispatch;
L_002e2cdc:
 STEP(UINT32_C(0x002e2cdc)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e2ce4));STEP(UINT32_C(0x002e2ce0));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e2ce0:
 STEP(UINT32_C(0x002e2ce0)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2ce4));goto dispatch;
L_002e2ce4:
 STEP(UINT32_C(0x002e2ce4)); /* 04410002 regimm1 v0,002e2cf0 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e2ce8));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002e2cf0):UINT32_C(0x002e2cec));goto dispatch;}
L_002e2ce8:
 STEP(UINT32_C(0x002e2ce8)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2cec));goto dispatch;
L_002e2cec:
 STEP(UINT32_C(0x002e2cec)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002e2cf0));goto dispatch;
L_002e2cf0:
 STEP(UINT32_C(0x002e2cf0)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2cf4));goto dispatch;
L_002e2cf4:
 STEP(UINT32_C(0x002e2cf4)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2cf8));goto dispatch;
L_002e2cf8:
 STEP(UINT32_C(0x002e2cf8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2cfc));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2cfc:
 STEP(UINT32_C(0x002e2cfc)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2d00));goto dispatch;
L_002e2d00:
 STEP(UINT32_C(0x002e2d00)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002e2d04));goto dispatch;
L_002e2d04:
 STEP(UINT32_C(0x002e2d04)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002e2d08));goto dispatch;
L_002e2d08:
 STEP(UINT32_C(0x002e2d08)); /* 0c0b8b22 jal 002e2c88 */
 set(m,31u,UINT64_C(0x002e2d10));STEP(UINT32_C(0x002e2d0c));/* nop */target=sx(UINT32_C(0x002e2c88));goto dispatch;
L_002e2d0c:
 STEP(UINT32_C(0x002e2d0c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e2d10));goto dispatch;
L_002e2d10:
 STEP(UINT32_C(0x002e2d10)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2d14));goto dispatch;
L_002e2d14:
 STEP(UINT32_C(0x002e2d14)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2d18));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002e2d18:
 STEP(UINT32_C(0x002e2d18)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002e2d1c));goto dispatch;
L_002e2d20:
 STEP(UINT32_C(0x002e2d20)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2d24));goto dispatch;
L_002e2d24:
 STEP(UINT32_C(0x002e2d24)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2d28));goto dispatch;
L_002e2d28:
 STEP(UINT32_C(0x002e2d28)); /* 8c43c354 lw v1,-0x3cac(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc354),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002e2d2c));goto dispatch;
L_002e2d2c:
 STEP(UINT32_C(0x002e2d2c)); /* 0080302d daddu a2,a0,zero */
 set(m,6u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e2d30));goto dispatch;
L_002e2d30:
 STEP(UINT32_C(0x002e2d30)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2d34));goto dispatch;
L_002e2d34:
 STEP(UINT32_C(0x002e2d34)); /* 04610003 regimm1 v1,002e2d44 */
 {int taken=((int64_t)lo(m,3u)>=0);STEP(UINT32_C(0x002e2d38));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e2d44):UINT32_C(0x002e2d3c));goto dispatch;}
L_002e2d38:
 STEP(UINT32_C(0x002e2d38)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2d3c));goto dispatch;
L_002e2d3c:
 STEP(UINT32_C(0x002e2d3c)); /* 10000030 beq zero,zero,002e2e00 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2d40));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e2e00):UINT32_C(0x002e2d44));goto dispatch;}
L_002e2d40:
 STEP(UINT32_C(0x002e2d40)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2d44));goto dispatch;
L_002e2d44:
 STEP(UINT32_C(0x002e2d44)); /* 90c20000 lbu v0,0x0(a2) */
 {uint8_t byte;READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002e2d48));goto dispatch;
L_002e2d48:
 STEP(UINT32_C(0x002e2d48)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2d4c));goto dispatch;
L_002e2d4c:
 STEP(UINT32_C(0x002e2d4c)); /* 24e3e900 addiu v1,a3,-5888 */
 set(m,3u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffe900)));target=sx(UINT32_C(0x002e2d50));goto dispatch;
L_002e2d50:
 STEP(UINT32_C(0x002e2d50)); /* a0620004 sb v0,0x4(v1) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&byte,1u);}target=sx(UINT32_C(0x002e2d54));goto dispatch;
L_002e2d54:
 STEP(UINT32_C(0x002e2d54)); /* 00021600 sll v0,v0,24 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<24u));target=sx(UINT32_C(0x002e2d58));goto dispatch;
L_002e2d58:
 STEP(UINT32_C(0x002e2d58)); /* 10400011 beq v0,zero,002e2da0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002e2d5c));set(m,8u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e2da0):UINT32_C(0x002e2d60));goto dispatch;}
L_002e2d5c:
 STEP(UINT32_C(0x002e2d5c)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2d60));goto dispatch;
L_002e2d60:
 STEP(UINT32_C(0x002e2d60)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2d64));goto dispatch;
L_002e2d64:
 STEP(UINT32_C(0x002e2d64)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2d68));goto dispatch;
L_002e2d68:
 STEP(UINT32_C(0x002e2d68)); /* 25080001 addiu t0,t0,1 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002e2d6c));goto dispatch;
L_002e2d6c:
 STEP(UINT32_C(0x002e2d6c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e2d70));goto dispatch;
L_002e2d70:
 STEP(UINT32_C(0x002e2d70)); /* 290200fc slti v0,t0,252 */
 set(m,2u,((int64_t)lo(m,8u)<INT64_C(252)));target=sx(UINT32_C(0x002e2d74));goto dispatch;
L_002e2d74:
 STEP(UINT32_C(0x002e2d74)); /* 1040000c beq v0,zero,002e2da8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002e2d78));set(m,2u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,8u)));target=sx(taken?UINT32_C(0x002e2da8):UINT32_C(0x002e2d7c));goto dispatch;}
L_002e2d78:
 STEP(UINT32_C(0x002e2d78)); /* 00c81021 addu v0,a2,t0 */
 set(m,2u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,8u)));target=sx(UINT32_C(0x002e2d7c));goto dispatch;
L_002e2d7c:
 STEP(UINT32_C(0x002e2d7c)); /* 24e3e900 addiu v1,a3,-5888 */
 set(m,3u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffe900)));target=sx(UINT32_C(0x002e2d80));goto dispatch;
L_002e2d80:
 STEP(UINT32_C(0x002e2d80)); /* 90440000 lbu a0,0x0(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&byte,1u);set(m,4u,byte);}target=sx(UINT32_C(0x002e2d84));goto dispatch;
L_002e2d84:
 STEP(UINT32_C(0x002e2d84)); /* 00681821 addu v1,v1,t0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,8u)));target=sx(UINT32_C(0x002e2d88));goto dispatch;
L_002e2d88:
 STEP(UINT32_C(0x002e2d88)); /* a0640004 sb a0,0x4(v1) */
 {uint8_t byte=(uint8_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&byte,1u);}target=sx(UINT32_C(0x002e2d8c));goto dispatch;
L_002e2d8c:
 STEP(UINT32_C(0x002e2d8c)); /* 00042600 sll a0,a0,24 */
 set(m,4u,sx((uint32_t)lo(m,4u)<<24u));target=sx(UINT32_C(0x002e2d90));goto dispatch;
L_002e2d90:
 STEP(UINT32_C(0x002e2d90)); /* 5480fff7 bnel a0,zero,002e2d70 */
 if(lo(m,4u)!=lo(m,0u)){STEP(UINT32_C(0x002e2d94));set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002e2d70));}else target=sx(UINT32_C(0x002e2d98));goto dispatch;
L_002e2d94:
 STEP(UINT32_C(0x002e2d94)); /* 25080001 addiu t0,t0,1 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002e2d98));goto dispatch;
L_002e2d98:
 STEP(UINT32_C(0x002e2d98)); /* 10000004 beq zero,zero,002e2dac */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2d9c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000fc)));target=sx(taken?UINT32_C(0x002e2dac):UINT32_C(0x002e2da0));goto dispatch;}
L_002e2d9c:
 STEP(UINT32_C(0x002e2d9c)); /* 240200fc addiu v0,zero,252 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000fc)));target=sx(UINT32_C(0x002e2da0));goto dispatch;
L_002e2da0:
 STEP(UINT32_C(0x002e2da0)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2da4));goto dispatch;
L_002e2da4:
 STEP(UINT32_C(0x002e2da4)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2da8));goto dispatch;
L_002e2da8:
 STEP(UINT32_C(0x002e2da8)); /* 240200fc addiu v0,zero,252 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000fc)));target=sx(UINT32_C(0x002e2dac));goto dispatch;
L_002e2dac:
 STEP(UINT32_C(0x002e2dac)); /* 55020005 bnel t0,v0,002e2dc4 */
 if(lo(m,8u)!=lo(m,2u)){STEP(UINT32_C(0x002e2db0));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffffe900),&value32,4u);target=sx(UINT32_C(0x002e2dc4));}else target=sx(UINT32_C(0x002e2db4));goto dispatch;
L_002e2db0:
 STEP(UINT32_C(0x002e2db0)); /* ace5e900 sw a1,-0x1700(a3) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffffe900),&value32,4u);target=sx(UINT32_C(0x002e2db4));goto dispatch;
L_002e2db4:
 STEP(UINT32_C(0x002e2db4)); /* 24e2e900 addiu v0,a3,-5888 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffe900)));target=sx(UINT32_C(0x002e2db8));goto dispatch;
L_002e2db8:
 STEP(UINT32_C(0x002e2db8)); /* 240800fb addiu t0,zero,251 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000fb)));target=sx(UINT32_C(0x002e2dbc));goto dispatch;
L_002e2dbc:
 STEP(UINT32_C(0x002e2dbc)); /* a04000ff sb zero,0xff(v0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x000000ff),&byte,1u);}target=sx(UINT32_C(0x002e2dc0));goto dispatch;
L_002e2dc0:
 STEP(UINT32_C(0x002e2dc0)); /* ace5e900 sw a1,-0x1700(a3) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffffe900),&value32,4u);target=sx(UINT32_C(0x002e2dc4));goto dispatch;
L_002e2dc4:
 STEP(UINT32_C(0x002e2dc4)); /* 24e2e900 addiu v0,a3,-5888 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffe900)));target=sx(UINT32_C(0x002e2dc8));goto dispatch;
L_002e2dc8:
 STEP(UINT32_C(0x002e2dc8)); /* 2524e840 addiu a0,t1,-6080 */
 set(m,4u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2dcc));goto dispatch;
L_002e2dcc:
 STEP(UINT32_C(0x002e2dcc)); /* a04000ff sb zero,0xff(v0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x000000ff),&byte,1u);}target=sx(UINT32_C(0x002e2dd0));goto dispatch;
L_002e2dd0:
 STEP(UINT32_C(0x002e2dd0)); /* 0040382d daddu a3,v0,zero */
 set(m,7u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002e2dd4));goto dispatch;
L_002e2dd4:
 STEP(UINT32_C(0x002e2dd4)); /* 25080005 addiu t0,t0,5 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000005)));target=sx(UINT32_C(0x002e2dd8));goto dispatch;
L_002e2dd8:
 STEP(UINT32_C(0x002e2dd8)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e2ddc));goto dispatch;
L_002e2ddc:
 STEP(UINT32_C(0x002e2ddc)); /* 24050003 addiu a1,zero,3 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002e2de0));goto dispatch;
L_002e2de0:
 STEP(UINT32_C(0x002e2de0)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2de4));goto dispatch;
L_002e2de4:
 STEP(UINT32_C(0x002e2de4)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e2de8));goto dispatch;
L_002e2de8:
 STEP(UINT32_C(0x002e2de8)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2dec));goto dispatch;
L_002e2dec:
 STEP(UINT32_C(0x002e2dec)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e2df4));STEP(UINT32_C(0x002e2df0));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e2df0:
 STEP(UINT32_C(0x002e2df0)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2df4));goto dispatch;
L_002e2df4:
 STEP(UINT32_C(0x002e2df4)); /* 04410002 regimm1 v0,002e2e00 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e2df8));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002e2e00):UINT32_C(0x002e2dfc));goto dispatch;}
L_002e2df8:
 STEP(UINT32_C(0x002e2df8)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2dfc));goto dispatch;
L_002e2dfc:
 STEP(UINT32_C(0x002e2dfc)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002e2e00));goto dispatch;
L_002e2e00:
 STEP(UINT32_C(0x002e2e00)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2e04));goto dispatch;
L_002e2e04:
 STEP(UINT32_C(0x002e2e04)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2e08));goto dispatch;
L_002e2e08:
 STEP(UINT32_C(0x002e2e08)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2e0c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2e0c:
 STEP(UINT32_C(0x002e2e0c)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2e10));goto dispatch;
L_002e2e10:
 STEP(UINT32_C(0x002e2e10)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2e14));goto dispatch;
L_002e2e14:
 STEP(UINT32_C(0x002e2e14)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2e18));goto dispatch;
L_002e2e18:
 STEP(UINT32_C(0x002e2e18)); /* 8c43c354 lw v1,-0x3cac(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc354),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002e2e1c));goto dispatch;
L_002e2e1c:
 STEP(UINT32_C(0x002e2e1c)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2e20));goto dispatch;
L_002e2e20:
 STEP(UINT32_C(0x002e2e20)); /* 04610003 regimm1 v1,002e2e30 */
 {int taken=((int64_t)lo(m,3u)>=0);STEP(UINT32_C(0x002e2e24));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e2e30):UINT32_C(0x002e2e28));goto dispatch;}
L_002e2e24:
 STEP(UINT32_C(0x002e2e24)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2e28));goto dispatch;
L_002e2e28:
 STEP(UINT32_C(0x002e2e28)); /* 10000011 beq zero,zero,002e2e70 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2e2c));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e2e70):UINT32_C(0x002e2e30));goto dispatch;}
L_002e2e2c:
 STEP(UINT32_C(0x002e2e2c)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2e30));goto dispatch;
L_002e2e30:
 STEP(UINT32_C(0x002e2e30)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2e34));goto dispatch;
L_002e2e34:
 STEP(UINT32_C(0x002e2e34)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2e38));goto dispatch;
L_002e2e38:
 STEP(UINT32_C(0x002e2e38)); /* 2484e840 addiu a0,a0,-6080 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2e3c));goto dispatch;
L_002e2e3c:
 STEP(UINT32_C(0x002e2e3c)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e2e40));goto dispatch;
L_002e2e40:
 STEP(UINT32_C(0x002e2e40)); /* 24050005 addiu a1,zero,5 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000005)));target=sx(UINT32_C(0x002e2e44));goto dispatch;
L_002e2e44:
 STEP(UINT32_C(0x002e2e44)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2e48));goto dispatch;
L_002e2e48:
 STEP(UINT32_C(0x002e2e48)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2e4c));goto dispatch;
L_002e2e4c:
 STEP(UINT32_C(0x002e2e4c)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2e50));goto dispatch;
L_002e2e50:
 STEP(UINT32_C(0x002e2e50)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e2e54));goto dispatch;
L_002e2e54:
 STEP(UINT32_C(0x002e2e54)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2e58));goto dispatch;
L_002e2e58:
 STEP(UINT32_C(0x002e2e58)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e2e60));STEP(UINT32_C(0x002e2e5c));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e2e5c:
 STEP(UINT32_C(0x002e2e5c)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2e60));goto dispatch;
L_002e2e60:
 STEP(UINT32_C(0x002e2e60)); /* 04430003 regimm3 v0,002e2e70 */
 if((int64_t)lo(m,2u)>=0){STEP(UINT32_C(0x002e2e64));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2e70));}else target=sx(UINT32_C(0x002e2e68));goto dispatch;
L_002e2e64:
 STEP(UINT32_C(0x002e2e64)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2e68));goto dispatch;
L_002e2e68:
 STEP(UINT32_C(0x002e2e68)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002e2e6c));goto dispatch;
L_002e2e6c:
 STEP(UINT32_C(0x002e2e6c)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002e2e70));goto dispatch;
L_002e2e70:
 STEP(UINT32_C(0x002e2e70)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2e74));goto dispatch;
L_002e2e74:
 STEP(UINT32_C(0x002e2e74)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2e78));goto dispatch;
L_002e2e78:
 STEP(UINT32_C(0x002e2e78)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2e7c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2e7c:
 STEP(UINT32_C(0x002e2e7c)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2e80));goto dispatch;
L_002e2e80:
 STEP(UINT32_C(0x002e2e80)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2e84));goto dispatch;
L_002e2e84:
 STEP(UINT32_C(0x002e2e84)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2e88));goto dispatch;
L_002e2e88:
 STEP(UINT32_C(0x002e2e88)); /* 8c43c354 lw v1,-0x3cac(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc354),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002e2e8c));goto dispatch;
L_002e2e8c:
 STEP(UINT32_C(0x002e2e8c)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2e90));goto dispatch;
L_002e2e90:
 STEP(UINT32_C(0x002e2e90)); /* 04610003 regimm1 v1,002e2ea0 */
 {int taken=((int64_t)lo(m,3u)>=0);STEP(UINT32_C(0x002e2e94));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e2ea0):UINT32_C(0x002e2e98));goto dispatch;}
L_002e2e94:
 STEP(UINT32_C(0x002e2e94)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2e98));goto dispatch;
L_002e2e98:
 STEP(UINT32_C(0x002e2e98)); /* 10000011 beq zero,zero,002e2ee0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2e9c));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e2ee0):UINT32_C(0x002e2ea0));goto dispatch;}
L_002e2e9c:
 STEP(UINT32_C(0x002e2e9c)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2ea0));goto dispatch;
L_002e2ea0:
 STEP(UINT32_C(0x002e2ea0)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2ea4));goto dispatch;
L_002e2ea4:
 STEP(UINT32_C(0x002e2ea4)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2ea8));goto dispatch;
L_002e2ea8:
 STEP(UINT32_C(0x002e2ea8)); /* 2484e840 addiu a0,a0,-6080 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2eac));goto dispatch;
L_002e2eac:
 STEP(UINT32_C(0x002e2eac)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e2eb0));goto dispatch;
L_002e2eb0:
 STEP(UINT32_C(0x002e2eb0)); /* 24050006 addiu a1,zero,6 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000006)));target=sx(UINT32_C(0x002e2eb4));goto dispatch;
L_002e2eb4:
 STEP(UINT32_C(0x002e2eb4)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2eb8));goto dispatch;
L_002e2eb8:
 STEP(UINT32_C(0x002e2eb8)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2ebc));goto dispatch;
L_002e2ebc:
 STEP(UINT32_C(0x002e2ebc)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2ec0));goto dispatch;
L_002e2ec0:
 STEP(UINT32_C(0x002e2ec0)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e2ec4));goto dispatch;
L_002e2ec4:
 STEP(UINT32_C(0x002e2ec4)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2ec8));goto dispatch;
L_002e2ec8:
 STEP(UINT32_C(0x002e2ec8)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e2ed0));STEP(UINT32_C(0x002e2ecc));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e2ecc:
 STEP(UINT32_C(0x002e2ecc)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2ed0));goto dispatch;
L_002e2ed0:
 STEP(UINT32_C(0x002e2ed0)); /* 04430003 regimm3 v0,002e2ee0 */
 if((int64_t)lo(m,2u)>=0){STEP(UINT32_C(0x002e2ed4));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2ee0));}else target=sx(UINT32_C(0x002e2ed8));goto dispatch;
L_002e2ed4:
 STEP(UINT32_C(0x002e2ed4)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2ed8));goto dispatch;
L_002e2ed8:
 STEP(UINT32_C(0x002e2ed8)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002e2edc));goto dispatch;
L_002e2edc:
 STEP(UINT32_C(0x002e2edc)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002e2ee0));goto dispatch;
L_002e2ee0:
 STEP(UINT32_C(0x002e2ee0)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2ee4));goto dispatch;
L_002e2ee4:
 STEP(UINT32_C(0x002e2ee4)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2ee8));goto dispatch;
L_002e2ee8:
 STEP(UINT32_C(0x002e2ee8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2eec));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2eec:
 STEP(UINT32_C(0x002e2eec)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2ef0));goto dispatch;
L_002e2ef0:
 STEP(UINT32_C(0x002e2ef0)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2ef4));goto dispatch;
L_002e2ef4:
 STEP(UINT32_C(0x002e2ef4)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2ef8));goto dispatch;
L_002e2ef8:
 STEP(UINT32_C(0x002e2ef8)); /* 8c43c354 lw v1,-0x3cac(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc354),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002e2efc));goto dispatch;
L_002e2efc:
 STEP(UINT32_C(0x002e2efc)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2f00));goto dispatch;
L_002e2f00:
 STEP(UINT32_C(0x002e2f00)); /* 04610003 regimm1 v1,002e2f10 */
 {int taken=((int64_t)lo(m,3u)>=0);STEP(UINT32_C(0x002e2f04));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e2f10):UINT32_C(0x002e2f08));goto dispatch;}
L_002e2f04:
 STEP(UINT32_C(0x002e2f04)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2f08));goto dispatch;
L_002e2f08:
 STEP(UINT32_C(0x002e2f08)); /* 10000011 beq zero,zero,002e2f50 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2f0c));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e2f50):UINT32_C(0x002e2f10));goto dispatch;}
L_002e2f0c:
 STEP(UINT32_C(0x002e2f0c)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2f10));goto dispatch;
L_002e2f10:
 STEP(UINT32_C(0x002e2f10)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2f14));goto dispatch;
L_002e2f14:
 STEP(UINT32_C(0x002e2f14)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2f18));goto dispatch;
L_002e2f18:
 STEP(UINT32_C(0x002e2f18)); /* 2484e840 addiu a0,a0,-6080 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2f1c));goto dispatch;
L_002e2f1c:
 STEP(UINT32_C(0x002e2f1c)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e2f20));goto dispatch;
L_002e2f20:
 STEP(UINT32_C(0x002e2f20)); /* 24050007 addiu a1,zero,7 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000007)));target=sx(UINT32_C(0x002e2f24));goto dispatch;
L_002e2f24:
 STEP(UINT32_C(0x002e2f24)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2f28));goto dispatch;
L_002e2f28:
 STEP(UINT32_C(0x002e2f28)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2f2c));goto dispatch;
L_002e2f2c:
 STEP(UINT32_C(0x002e2f2c)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2f30));goto dispatch;
L_002e2f30:
 STEP(UINT32_C(0x002e2f30)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e2f34));goto dispatch;
L_002e2f34:
 STEP(UINT32_C(0x002e2f34)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2f38));goto dispatch;
L_002e2f38:
 STEP(UINT32_C(0x002e2f38)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e2f40));STEP(UINT32_C(0x002e2f3c));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e2f3c:
 STEP(UINT32_C(0x002e2f3c)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2f40));goto dispatch;
L_002e2f40:
 STEP(UINT32_C(0x002e2f40)); /* 04430003 regimm3 v0,002e2f50 */
 if((int64_t)lo(m,2u)>=0){STEP(UINT32_C(0x002e2f44));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2f50));}else target=sx(UINT32_C(0x002e2f48));goto dispatch;
L_002e2f44:
 STEP(UINT32_C(0x002e2f44)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2f48));goto dispatch;
L_002e2f48:
 STEP(UINT32_C(0x002e2f48)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002e2f4c));goto dispatch;
L_002e2f4c:
 STEP(UINT32_C(0x002e2f4c)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002e2f50));goto dispatch;
L_002e2f50:
 STEP(UINT32_C(0x002e2f50)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2f54));goto dispatch;
L_002e2f54:
 STEP(UINT32_C(0x002e2f54)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2f58));goto dispatch;
L_002e2f58:
 STEP(UINT32_C(0x002e2f58)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2f5c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2f5c:
 STEP(UINT32_C(0x002e2f5c)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2f60));goto dispatch;
L_002e2f60:
 STEP(UINT32_C(0x002e2f60)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2f64));goto dispatch;
L_002e2f64:
 STEP(UINT32_C(0x002e2f64)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2f68));goto dispatch;
L_002e2f68:
 STEP(UINT32_C(0x002e2f68)); /* 8c62c354 lw v0,-0x3cac(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffc354),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2f6c));goto dispatch;
L_002e2f6c:
 STEP(UINT32_C(0x002e2f6c)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e2f70));goto dispatch;
L_002e2f70:
 STEP(UINT32_C(0x002e2f70)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2f74));goto dispatch;
L_002e2f74:
 STEP(UINT32_C(0x002e2f74)); /* 04410003 regimm1 v0,002e2f84 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e2f78));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e2f84):UINT32_C(0x002e2f7c));goto dispatch;}
L_002e2f78:
 STEP(UINT32_C(0x002e2f78)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2f7c));goto dispatch;
L_002e2f7c:
 STEP(UINT32_C(0x002e2f7c)); /* 10000013 beq zero,zero,002e2fcc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2f80));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e2fcc):UINT32_C(0x002e2f84));goto dispatch;}
L_002e2f80:
 STEP(UINT32_C(0x002e2f80)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2f84));goto dispatch;
L_002e2f84:
 STEP(UINT32_C(0x002e2f84)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2f88));goto dispatch;
L_002e2f88:
 STEP(UINT32_C(0x002e2f88)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2f8c));goto dispatch;
L_002e2f8c:
 STEP(UINT32_C(0x002e2f8c)); /* ace5e8c0 sw a1,-0x1740(a3) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffffe8c0),&value32,4u);target=sx(UINT32_C(0x002e2f90));goto dispatch;
L_002e2f90:
 STEP(UINT32_C(0x002e2f90)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2f94));goto dispatch;
L_002e2f94:
 STEP(UINT32_C(0x002e2f94)); /* 2484e840 addiu a0,a0,-6080 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2f98));goto dispatch;
L_002e2f98:
 STEP(UINT32_C(0x002e2f98)); /* 24e7e8c0 addiu a3,a3,-5952 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffe8c0)));target=sx(UINT32_C(0x002e2f9c));goto dispatch;
L_002e2f9c:
 STEP(UINT32_C(0x002e2f9c)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e2fa0));goto dispatch;
L_002e2fa0:
 STEP(UINT32_C(0x002e2fa0)); /* 24050008 addiu a1,zero,8 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002e2fa4));goto dispatch;
L_002e2fa4:
 STEP(UINT32_C(0x002e2fa4)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2fa8));goto dispatch;
L_002e2fa8:
 STEP(UINT32_C(0x002e2fa8)); /* 24080004 addiu t0,zero,4 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2fac));goto dispatch;
L_002e2fac:
 STEP(UINT32_C(0x002e2fac)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e2fb0));goto dispatch;
L_002e2fb0:
 STEP(UINT32_C(0x002e2fb0)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e2fb4));goto dispatch;
L_002e2fb4:
 STEP(UINT32_C(0x002e2fb4)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e2fbc));STEP(UINT32_C(0x002e2fb8));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e2fb8:
 STEP(UINT32_C(0x002e2fb8)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2fbc));goto dispatch;
L_002e2fbc:
 STEP(UINT32_C(0x002e2fbc)); /* 04430003 regimm3 v0,002e2fcc */
 if((int64_t)lo(m,2u)>=0){STEP(UINT32_C(0x002e2fc0));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2fcc));}else target=sx(UINT32_C(0x002e2fc4));goto dispatch;
L_002e2fc0:
 STEP(UINT32_C(0x002e2fc0)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2fc4));goto dispatch;
L_002e2fc4:
 STEP(UINT32_C(0x002e2fc4)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002e2fc8));goto dispatch;
L_002e2fc8:
 STEP(UINT32_C(0x002e2fc8)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002e2fcc));goto dispatch;
L_002e2fcc:
 STEP(UINT32_C(0x002e2fcc)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2fd0));goto dispatch;
L_002e2fd0:
 STEP(UINT32_C(0x002e2fd0)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2fd4));goto dispatch;
L_002e2fd4:
 STEP(UINT32_C(0x002e2fd4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2fd8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2fd8:
 STEP(UINT32_C(0x002e2fd8)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2fdc));goto dispatch;
L_002e2fe0:
 STEP(UINT32_C(0x002e2fe0)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2fe4));goto dispatch;
L_002e2fe4:
 STEP(UINT32_C(0x002e2fe4)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2fe8));goto dispatch;
L_002e2fe8:
 STEP(UINT32_C(0x002e2fe8)); /* 8c62c354 lw v0,-0x3cac(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffc354),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2fec));goto dispatch;
L_002e2fec:
 STEP(UINT32_C(0x002e2fec)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e2ff0));goto dispatch;
L_002e2ff0:
 STEP(UINT32_C(0x002e2ff0)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2ff4));goto dispatch;
L_002e2ff4:
 STEP(UINT32_C(0x002e2ff4)); /* 04410003 regimm1 v0,002e3004 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e2ff8));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e3004):UINT32_C(0x002e2ffc));goto dispatch;}
L_002e2ff8:
 STEP(UINT32_C(0x002e2ff8)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2ffc));goto dispatch;
L_002e2ffc:
 STEP(UINT32_C(0x002e2ffc)); /* 10000013 beq zero,zero,002e304c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e3000));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e304c):UINT32_C(0x002e3004));goto dispatch;}
L_002e3000:
 STEP(UINT32_C(0x002e3000)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3004));goto dispatch;
L_002e3004:
 STEP(UINT32_C(0x002e3004)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e3008));goto dispatch;
L_002e3008:
 STEP(UINT32_C(0x002e3008)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e300c));goto dispatch;
L_002e300c:
 STEP(UINT32_C(0x002e300c)); /* ace5e8c0 sw a1,-0x1740(a3) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffffe8c0),&value32,4u);target=sx(UINT32_C(0x002e3010));goto dispatch;
L_002e3010:
 STEP(UINT32_C(0x002e3010)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e3014));goto dispatch;
L_002e3014:
 STEP(UINT32_C(0x002e3014)); /* 2484e840 addiu a0,a0,-6080 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e3018));goto dispatch;
L_002e3018:
 STEP(UINT32_C(0x002e3018)); /* 24e7e8c0 addiu a3,a3,-5952 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffe8c0)));target=sx(UINT32_C(0x002e301c));goto dispatch;
L_002e301c:
 STEP(UINT32_C(0x002e301c)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e3020));goto dispatch;
L_002e3020:
 STEP(UINT32_C(0x002e3020)); /* 24050009 addiu a1,zero,9 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000009)));target=sx(UINT32_C(0x002e3024));goto dispatch;
L_002e3024:
 STEP(UINT32_C(0x002e3024)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3028));goto dispatch;
L_002e3028:
 STEP(UINT32_C(0x002e3028)); /* 24080004 addiu t0,zero,4 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e302c));goto dispatch;
L_002e302c:
 STEP(UINT32_C(0x002e302c)); /* 2609e880 addiu t1,s0,-6016 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe880)));target=sx(UINT32_C(0x002e3030));goto dispatch;
L_002e3030:
 STEP(UINT32_C(0x002e3030)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e3034));goto dispatch;
L_002e3034:
 STEP(UINT32_C(0x002e3034)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e303c));STEP(UINT32_C(0x002e3038));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e3038:
 STEP(UINT32_C(0x002e3038)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e303c));goto dispatch;
L_002e303c:
 STEP(UINT32_C(0x002e303c)); /* 04430003 regimm3 v0,002e304c */
 if((int64_t)lo(m,2u)>=0){STEP(UINT32_C(0x002e3040));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e304c));}else target=sx(UINT32_C(0x002e3044));goto dispatch;
L_002e3040:
 STEP(UINT32_C(0x002e3040)); /* 8e02e880 lw v0,-0x1780(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe880),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e3044));goto dispatch;
L_002e3044:
 STEP(UINT32_C(0x002e3044)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002e3048));goto dispatch;
L_002e3048:
 STEP(UINT32_C(0x002e3048)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002e304c));goto dispatch;
L_002e304c:
 STEP(UINT32_C(0x002e304c)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e3050));goto dispatch;
L_002e3050:
 STEP(UINT32_C(0x002e3050)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e3054));goto dispatch;
L_002e3054:
 STEP(UINT32_C(0x002e3054)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e3058));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e3058:
 STEP(UINT32_C(0x002e3058)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e305c));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

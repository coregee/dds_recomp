#include "libc_heap_native.h"
#include <string.h>
/* Original Nocturne/installed BIOS source-bound fixed statements. RAM and all MMIO are delegated
 * to the initialized memory owner; no INTC acknowledgement is synthesized.
 * The caller owns actual interrupt/SYSCALL entry, Cause/EPC/Status and clocks. */
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
uint32_t nocturneLibcHeapResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002d3be8):goto L_002d3be8;
 case UINT32_C(0x002d3bec):goto L_002d3bec;
 case UINT32_C(0x002d3bf0):goto L_002d3bf0;
 case UINT32_C(0x002d3bf4):goto L_002d3bf4;
 case UINT32_C(0x002d3bf8):goto L_002d3bf8;
 case UINT32_C(0x002d3bfc):goto L_002d3bfc;
 case UINT32_C(0x002d3c00):goto L_002d3c00;
 case UINT32_C(0x002d3c04):goto L_002d3c04;
 case UINT32_C(0x002d3c08):goto L_002d3c08;
 case UINT32_C(0x002d3c0c):goto L_002d3c0c;
 case UINT32_C(0x002d3c10):goto L_002d3c10;
 case UINT32_C(0x002d3c14):goto L_002d3c14;
 case UINT32_C(0x002d3c18):goto L_002d3c18;
 case UINT32_C(0x002d3c1c):goto L_002d3c1c;
 case UINT32_C(0x002d3c20):goto L_002d3c20;
 case UINT32_C(0x002d3c24):goto L_002d3c24;
 case UINT32_C(0x002d3c28):goto L_002d3c28;
 case UINT32_C(0x002d3c2c):goto L_002d3c2c;
 case UINT32_C(0x002d3c30):goto L_002d3c30;
 case UINT32_C(0x002d3c34):goto L_002d3c34;
 case UINT32_C(0x002d3c38):goto L_002d3c38;
 case UINT32_C(0x002d3c3c):goto L_002d3c3c;
 case UINT32_C(0x002d3c40):goto L_002d3c40;
 case UINT32_C(0x002d3c44):goto L_002d3c44;
 case UINT32_C(0x002d3c48):goto L_002d3c48;
 case UINT32_C(0x002d3c4c):goto L_002d3c4c;
 case UINT32_C(0x002d3c50):goto L_002d3c50;
 case UINT32_C(0x002d3c54):goto L_002d3c54;
 case UINT32_C(0x002d3c58):goto L_002d3c58;
 case UINT32_C(0x002d3c5c):goto L_002d3c5c;
 case UINT32_C(0x002d3c60):goto L_002d3c60;
 case UINT32_C(0x002d3c64):goto L_002d3c64;
 case UINT32_C(0x002d3c68):goto L_002d3c68;
 case UINT32_C(0x002d3c6c):goto L_002d3c6c;
 case UINT32_C(0x002d3c70):goto L_002d3c70;
 case UINT32_C(0x002d3c74):goto L_002d3c74;
 case UINT32_C(0x002d3c78):goto L_002d3c78;
 case UINT32_C(0x002d3c7c):goto L_002d3c7c;
 case UINT32_C(0x002d3c80):goto L_002d3c80;
 case UINT32_C(0x002d3c84):goto L_002d3c84;
 case UINT32_C(0x002d3c88):goto L_002d3c88;
 case UINT32_C(0x002d3c8c):goto L_002d3c8c;
 case UINT32_C(0x002d3c90):goto L_002d3c90;
 case UINT32_C(0x002d3c94):goto L_002d3c94;
 case UINT32_C(0x002d3c98):goto L_002d3c98;
 case UINT32_C(0x002d3c9c):goto L_002d3c9c;
 case UINT32_C(0x002d3ca0):goto L_002d3ca0;
 case UINT32_C(0x002d3ca4):goto L_002d3ca4;
 case UINT32_C(0x002d3ca8):goto L_002d3ca8;
 case UINT32_C(0x002d3cac):goto L_002d3cac;
 case UINT32_C(0x002d3cb0):goto L_002d3cb0;
 case UINT32_C(0x002d3cb4):goto L_002d3cb4;
 case UINT32_C(0x002d3cb8):goto L_002d3cb8;
 case UINT32_C(0x002d3cbc):goto L_002d3cbc;
 case UINT32_C(0x002d3cc0):goto L_002d3cc0;
 case UINT32_C(0x002d3cc4):goto L_002d3cc4;
 case UINT32_C(0x002d3cc8):goto L_002d3cc8;
 case UINT32_C(0x002d3ccc):goto L_002d3ccc;
 case UINT32_C(0x002d3cd0):goto L_002d3cd0;
 case UINT32_C(0x002d3cd4):goto L_002d3cd4;
 case UINT32_C(0x002d3cd8):goto L_002d3cd8;
 case UINT32_C(0x002d3cdc):goto L_002d3cdc;
 case UINT32_C(0x002d3ce0):goto L_002d3ce0;
 case UINT32_C(0x002d3ce4):goto L_002d3ce4;
 case UINT32_C(0x002d3ce8):goto L_002d3ce8;
 case UINT32_C(0x002d3cec):goto L_002d3cec;
 case UINT32_C(0x002d3cf0):goto L_002d3cf0;
 case UINT32_C(0x002d3cf4):goto L_002d3cf4;
 case UINT32_C(0x002d3cf8):goto L_002d3cf8;
 case UINT32_C(0x002d3cfc):goto L_002d3cfc;
 case UINT32_C(0x002d3d00):goto L_002d3d00;
 case UINT32_C(0x002d3d04):goto L_002d3d04;
 case UINT32_C(0x002d3d08):goto L_002d3d08;
 case UINT32_C(0x002d3d0c):goto L_002d3d0c;
 case UINT32_C(0x002d3d10):goto L_002d3d10;
 case UINT32_C(0x002d3d14):goto L_002d3d14;
 case UINT32_C(0x002d3d18):goto L_002d3d18;
 case UINT32_C(0x002d3d1c):goto L_002d3d1c;
 case UINT32_C(0x002d3d20):goto L_002d3d20;
 case UINT32_C(0x002d3d24):goto L_002d3d24;
 case UINT32_C(0x002d3d28):goto L_002d3d28;
 case UINT32_C(0x002d3d2c):goto L_002d3d2c;
 case UINT32_C(0x002d3d30):goto L_002d3d30;
 case UINT32_C(0x002d3d34):goto L_002d3d34;
 case UINT32_C(0x002d3d38):goto L_002d3d38;
 case UINT32_C(0x002d3d3c):goto L_002d3d3c;
 case UINT32_C(0x002d3d40):goto L_002d3d40;
 case UINT32_C(0x002d3d44):goto L_002d3d44;
 case UINT32_C(0x002d3d48):goto L_002d3d48;
 case UINT32_C(0x002d3d4c):goto L_002d3d4c;
 case UINT32_C(0x002d3d50):goto L_002d3d50;
 case UINT32_C(0x002d3d54):goto L_002d3d54;
 case UINT32_C(0x002d3d58):goto L_002d3d58;
 case UINT32_C(0x002d3d5c):goto L_002d3d5c;
 case UINT32_C(0x002d3d60):goto L_002d3d60;
 case UINT32_C(0x002d3d64):goto L_002d3d64;
 case UINT32_C(0x002d3d68):goto L_002d3d68;
 case UINT32_C(0x002d3d6c):goto L_002d3d6c;
 case UINT32_C(0x002d3d70):goto L_002d3d70;
 case UINT32_C(0x002d3d74):goto L_002d3d74;
 case UINT32_C(0x002d3d78):goto L_002d3d78;
 case UINT32_C(0x002d3d7c):goto L_002d3d7c;
 case UINT32_C(0x002d3d80):goto L_002d3d80;
 case UINT32_C(0x002d3d84):goto L_002d3d84;
 case UINT32_C(0x002d3d88):goto L_002d3d88;
 case UINT32_C(0x002d3d8c):goto L_002d3d8c;
 case UINT32_C(0x002d3d90):goto L_002d3d90;
 case UINT32_C(0x002d3d94):goto L_002d3d94;
 case UINT32_C(0x002d3d98):goto L_002d3d98;
 case UINT32_C(0x002d3d9c):goto L_002d3d9c;
 case UINT32_C(0x002d3da0):goto L_002d3da0;
 case UINT32_C(0x002d3da4):goto L_002d3da4;
 case UINT32_C(0x002d3da8):goto L_002d3da8;
 case UINT32_C(0x002d3dac):goto L_002d3dac;
 case UINT32_C(0x002d3db0):goto L_002d3db0;
 case UINT32_C(0x002d3db4):goto L_002d3db4;
 case UINT32_C(0x002d3db8):goto L_002d3db8;
 case UINT32_C(0x002d3dbc):goto L_002d3dbc;
 case UINT32_C(0x002d3dc0):goto L_002d3dc0;
 case UINT32_C(0x002d3dc4):goto L_002d3dc4;
 case UINT32_C(0x002d3dc8):goto L_002d3dc8;
 case UINT32_C(0x002d3dcc):goto L_002d3dcc;
 case UINT32_C(0x002d3dd0):goto L_002d3dd0;
 case UINT32_C(0x002d3dd4):goto L_002d3dd4;
 case UINT32_C(0x002d3dd8):goto L_002d3dd8;
 case UINT32_C(0x002d3ddc):goto L_002d3ddc;
 case UINT32_C(0x002d3de0):goto L_002d3de0;
 case UINT32_C(0x002d3de4):goto L_002d3de4;
 case UINT32_C(0x002d3de8):goto L_002d3de8;
 case UINT32_C(0x002d3dec):goto L_002d3dec;
 case UINT32_C(0x002d3df0):goto L_002d3df0;
 case UINT32_C(0x002d3df4):goto L_002d3df4;
 case UINT32_C(0x002d3df8):goto L_002d3df8;
 case UINT32_C(0x002d3dfc):goto L_002d3dfc;
 case UINT32_C(0x002d3e00):goto L_002d3e00;
 case UINT32_C(0x002d3e04):goto L_002d3e04;
 case UINT32_C(0x002d3e08):goto L_002d3e08;
 case UINT32_C(0x002d3e0c):goto L_002d3e0c;
 case UINT32_C(0x002d3e10):goto L_002d3e10;
 case UINT32_C(0x002d3e14):goto L_002d3e14;
 case UINT32_C(0x002d3e18):goto L_002d3e18;
 case UINT32_C(0x002d3e1c):goto L_002d3e1c;
 case UINT32_C(0x002d3e20):goto L_002d3e20;
 case UINT32_C(0x002d3e24):goto L_002d3e24;
 case UINT32_C(0x002d3e28):goto L_002d3e28;
 case UINT32_C(0x002d3e2c):goto L_002d3e2c;
 case UINT32_C(0x002d3e30):goto L_002d3e30;
 case UINT32_C(0x002d3e34):goto L_002d3e34;
 case UINT32_C(0x002d3e38):goto L_002d3e38;
 case UINT32_C(0x002d3e3c):goto L_002d3e3c;
 case UINT32_C(0x002d3e40):goto L_002d3e40;
 case UINT32_C(0x002d3e44):goto L_002d3e44;
 case UINT32_C(0x002d3e48):goto L_002d3e48;
 case UINT32_C(0x002d3e4c):goto L_002d3e4c;
 case UINT32_C(0x002d3e50):goto L_002d3e50;
 case UINT32_C(0x002d3e54):goto L_002d3e54;
 case UINT32_C(0x002d3e58):goto L_002d3e58;
 case UINT32_C(0x002d3e5c):goto L_002d3e5c;
 case UINT32_C(0x002d3e60):goto L_002d3e60;
 case UINT32_C(0x002d3e64):goto L_002d3e64;
 case UINT32_C(0x002d3e68):goto L_002d3e68;
 case UINT32_C(0x002d3e6c):goto L_002d3e6c;
 case UINT32_C(0x002d3e70):goto L_002d3e70;
 case UINT32_C(0x002d3e74):goto L_002d3e74;
 case UINT32_C(0x002d3e78):goto L_002d3e78;
 case UINT32_C(0x002d3e7c):goto L_002d3e7c;
 case UINT32_C(0x002d3e80):goto L_002d3e80;
 case UINT32_C(0x002d3e84):goto L_002d3e84;
 case UINT32_C(0x002d3e88):goto L_002d3e88;
 case UINT32_C(0x002d3e8c):goto L_002d3e8c;
 case UINT32_C(0x002d3e90):goto L_002d3e90;
 case UINT32_C(0x002d3e94):goto L_002d3e94;
 case UINT32_C(0x002d3e98):goto L_002d3e98;
 case UINT32_C(0x002d3e9c):goto L_002d3e9c;
 case UINT32_C(0x002d3ea0):goto L_002d3ea0;
 case UINT32_C(0x002d3ea4):goto L_002d3ea4;
 case UINT32_C(0x002d3ea8):goto L_002d3ea8;
 case UINT32_C(0x002d3eac):goto L_002d3eac;
 case UINT32_C(0x002d3eb0):goto L_002d3eb0;
 case UINT32_C(0x002d3eb4):goto L_002d3eb4;
 case UINT32_C(0x002d3eb8):goto L_002d3eb8;
 case UINT32_C(0x002d3ebc):goto L_002d3ebc;
 case UINT32_C(0x002d3ec0):goto L_002d3ec0;
 case UINT32_C(0x002d3ec4):goto L_002d3ec4;
 case UINT32_C(0x002d3ec8):goto L_002d3ec8;
 case UINT32_C(0x002d3ecc):goto L_002d3ecc;
 case UINT32_C(0x002d3ed0):goto L_002d3ed0;
 case UINT32_C(0x002d3ed4):goto L_002d3ed4;
 case UINT32_C(0x002d3ed8):goto L_002d3ed8;
 case UINT32_C(0x002d3edc):goto L_002d3edc;
 case UINT32_C(0x002d3ee0):goto L_002d3ee0;
 case UINT32_C(0x002d3ee4):goto L_002d3ee4;
 case UINT32_C(0x002d3ee8):goto L_002d3ee8;
 case UINT32_C(0x002d3eec):goto L_002d3eec;
 case UINT32_C(0x002d3ef0):goto L_002d3ef0;
 case UINT32_C(0x002d3ef4):goto L_002d3ef4;
 case UINT32_C(0x002d3ef8):goto L_002d3ef8;
 case UINT32_C(0x002d3efc):goto L_002d3efc;
 case UINT32_C(0x002d3f00):goto L_002d3f00;
 case UINT32_C(0x002d3f04):goto L_002d3f04;
 case UINT32_C(0x002d3f08):goto L_002d3f08;
 case UINT32_C(0x002d3f0c):goto L_002d3f0c;
 case UINT32_C(0x002d3f10):goto L_002d3f10;
 case UINT32_C(0x002d3f14):goto L_002d3f14;
 case UINT32_C(0x002d3f18):goto L_002d3f18;
 case UINT32_C(0x002d3f1c):goto L_002d3f1c;
 case UINT32_C(0x002d3f20):goto L_002d3f20;
 case UINT32_C(0x002d3f24):goto L_002d3f24;
 case UINT32_C(0x002d3f28):goto L_002d3f28;
 case UINT32_C(0x002d3f2c):goto L_002d3f2c;
 case UINT32_C(0x002d3f30):goto L_002d3f30;
 case UINT32_C(0x002d3f34):goto L_002d3f34;
 case UINT32_C(0x002d3f38):goto L_002d3f38;
 case UINT32_C(0x002d3f3c):goto L_002d3f3c;
 case UINT32_C(0x002d3f40):goto L_002d3f40;
 case UINT32_C(0x002d3f44):goto L_002d3f44;
 case UINT32_C(0x002d3f48):goto L_002d3f48;
 case UINT32_C(0x002d3f4c):goto L_002d3f4c;
 case UINT32_C(0x002d3f50):goto L_002d3f50;
 case UINT32_C(0x002d3f54):goto L_002d3f54;
 case UINT32_C(0x002d3f58):goto L_002d3f58;
 case UINT32_C(0x002d3f5c):goto L_002d3f5c;
 case UINT32_C(0x002d3f60):goto L_002d3f60;
 case UINT32_C(0x002d3f64):goto L_002d3f64;
 case UINT32_C(0x002d3f68):goto L_002d3f68;
 case UINT32_C(0x002d3f6c):goto L_002d3f6c;
 case UINT32_C(0x002d3f70):goto L_002d3f70;
 case UINT32_C(0x002d3f74):goto L_002d3f74;
 case UINT32_C(0x002d3f78):goto L_002d3f78;
 case UINT32_C(0x002d3f7c):goto L_002d3f7c;
 case UINT32_C(0x002d3f80):goto L_002d3f80;
 case UINT32_C(0x002d3f84):goto L_002d3f84;
 case UINT32_C(0x002d3f88):goto L_002d3f88;
 case UINT32_C(0x002d3f8c):goto L_002d3f8c;
 case UINT32_C(0x002d3f90):goto L_002d3f90;
 case UINT32_C(0x002d3f94):goto L_002d3f94;
 case UINT32_C(0x002d3f98):goto L_002d3f98;
 case UINT32_C(0x002d3f9c):goto L_002d3f9c;
 case UINT32_C(0x002d3fa0):goto L_002d3fa0;
 case UINT32_C(0x002d3fa4):goto L_002d3fa4;
 case UINT32_C(0x002d3fa8):goto L_002d3fa8;
 case UINT32_C(0x002d3fac):goto L_002d3fac;
 case UINT32_C(0x002d3fb0):goto L_002d3fb0;
 case UINT32_C(0x002d3fb4):goto L_002d3fb4;
 case UINT32_C(0x002d3fb8):goto L_002d3fb8;
 case UINT32_C(0x002d3fbc):goto L_002d3fbc;
 case UINT32_C(0x002d3fc0):goto L_002d3fc0;
 case UINT32_C(0x002d3fc4):goto L_002d3fc4;
 case UINT32_C(0x002d3fc8):goto L_002d3fc8;
 case UINT32_C(0x002d3fcc):goto L_002d3fcc;
 case UINT32_C(0x002d3fd0):goto L_002d3fd0;
 case UINT32_C(0x002d3fd4):goto L_002d3fd4;
 case UINT32_C(0x002d3fd8):goto L_002d3fd8;
 case UINT32_C(0x002d3fdc):goto L_002d3fdc;
 case UINT32_C(0x002d3fe0):goto L_002d3fe0;
 case UINT32_C(0x002d3fe4):goto L_002d3fe4;
 case UINT32_C(0x002d3fe8):goto L_002d3fe8;
 case UINT32_C(0x002d3fec):goto L_002d3fec;
 case UINT32_C(0x002d3ff0):goto L_002d3ff0;
 case UINT32_C(0x002d3ff4):goto L_002d3ff4;
 case UINT32_C(0x002d3ff8):goto L_002d3ff8;
 case UINT32_C(0x002d3ffc):goto L_002d3ffc;
 case UINT32_C(0x002d4000):goto L_002d4000;
 case UINT32_C(0x002d4004):goto L_002d4004;
 case UINT32_C(0x002d4008):goto L_002d4008;
 case UINT32_C(0x002d400c):goto L_002d400c;
 case UINT32_C(0x002d4010):goto L_002d4010;
 case UINT32_C(0x002d4014):goto L_002d4014;
 case UINT32_C(0x002d4018):goto L_002d4018;
 case UINT32_C(0x002d401c):goto L_002d401c;
 case UINT32_C(0x002d4020):goto L_002d4020;
 case UINT32_C(0x002d4024):goto L_002d4024;
 case UINT32_C(0x002d4028):goto L_002d4028;
 case UINT32_C(0x002d402c):goto L_002d402c;
 case UINT32_C(0x002d4030):goto L_002d4030;
 case UINT32_C(0x002d4034):goto L_002d4034;
 case UINT32_C(0x002d4038):goto L_002d4038;
 case UINT32_C(0x002d403c):goto L_002d403c;
 case UINT32_C(0x002d4040):goto L_002d4040;
 case UINT32_C(0x002d4044):goto L_002d4044;
 case UINT32_C(0x002d4048):goto L_002d4048;
 case UINT32_C(0x002d404c):goto L_002d404c;
 case UINT32_C(0x002d4050):goto L_002d4050;
 case UINT32_C(0x002d4054):goto L_002d4054;
 case UINT32_C(0x002d4058):goto L_002d4058;
 case UINT32_C(0x002d405c):goto L_002d405c;
 case UINT32_C(0x002d4060):goto L_002d4060;
 case UINT32_C(0x002d4064):goto L_002d4064;
 case UINT32_C(0x002d4068):goto L_002d4068;
 case UINT32_C(0x002d406c):goto L_002d406c;
 case UINT32_C(0x002d4070):goto L_002d4070;
 case UINT32_C(0x002d4074):goto L_002d4074;
 case UINT32_C(0x002d4078):goto L_002d4078;
 case UINT32_C(0x002d407c):goto L_002d407c;
 case UINT32_C(0x002d4080):goto L_002d4080;
 case UINT32_C(0x002d4084):goto L_002d4084;
 case UINT32_C(0x002d4088):goto L_002d4088;
 case UINT32_C(0x002d408c):goto L_002d408c;
 case UINT32_C(0x002d4090):goto L_002d4090;
 case UINT32_C(0x002d4094):goto L_002d4094;
 case UINT32_C(0x002d4098):goto L_002d4098;
 case UINT32_C(0x002d409c):goto L_002d409c;
 case UINT32_C(0x002d40a0):goto L_002d40a0;
 case UINT32_C(0x002d40a4):goto L_002d40a4;
 case UINT32_C(0x002d40a8):goto L_002d40a8;
 case UINT32_C(0x002d40ac):goto L_002d40ac;
 case UINT32_C(0x002d40b0):goto L_002d40b0;
 case UINT32_C(0x002d40b4):goto L_002d40b4;
 case UINT32_C(0x002d40b8):goto L_002d40b8;
 case UINT32_C(0x002d40bc):goto L_002d40bc;
 case UINT32_C(0x002d40c0):goto L_002d40c0;
 case UINT32_C(0x002d40c4):goto L_002d40c4;
 case UINT32_C(0x002d40c8):goto L_002d40c8;
 case UINT32_C(0x002d40cc):goto L_002d40cc;
 case UINT32_C(0x002d40d0):goto L_002d40d0;
 case UINT32_C(0x002d40d4):goto L_002d40d4;
 case UINT32_C(0x002d40d8):goto L_002d40d8;
 case UINT32_C(0x002d40dc):goto L_002d40dc;
 case UINT32_C(0x002d40e0):goto L_002d40e0;
 case UINT32_C(0x002d40e4):goto L_002d40e4;
 case UINT32_C(0x002d40e8):goto L_002d40e8;
 case UINT32_C(0x002d40ec):goto L_002d40ec;
 case UINT32_C(0x002d40f0):goto L_002d40f0;
 case UINT32_C(0x002d40f4):goto L_002d40f4;
 case UINT32_C(0x002d40f8):goto L_002d40f8;
 case UINT32_C(0x002d40fc):goto L_002d40fc;
 case UINT32_C(0x002d4100):goto L_002d4100;
 case UINT32_C(0x002d4104):goto L_002d4104;
 case UINT32_C(0x002d4108):goto L_002d4108;
 case UINT32_C(0x002d410c):goto L_002d410c;
 case UINT32_C(0x002d4110):goto L_002d4110;
 case UINT32_C(0x002d4114):goto L_002d4114;
 case UINT32_C(0x002d4118):goto L_002d4118;
 case UINT32_C(0x002d411c):goto L_002d411c;
 case UINT32_C(0x002d4120):goto L_002d4120;
 case UINT32_C(0x002d4124):goto L_002d4124;
 case UINT32_C(0x002d4128):goto L_002d4128;
 case UINT32_C(0x002d412c):goto L_002d412c;
 case UINT32_C(0x002d4130):goto L_002d4130;
 case UINT32_C(0x002d4134):goto L_002d4134;
 case UINT32_C(0x002d4138):goto L_002d4138;
 case UINT32_C(0x002d413c):goto L_002d413c;
 case UINT32_C(0x002d4140):goto L_002d4140;
 case UINT32_C(0x002d4144):goto L_002d4144;
 case UINT32_C(0x002d4148):goto L_002d4148;
 case UINT32_C(0x002d414c):goto L_002d414c;
 case UINT32_C(0x002d4150):goto L_002d4150;
 case UINT32_C(0x002d4154):goto L_002d4154;
 case UINT32_C(0x002d4158):goto L_002d4158;
 case UINT32_C(0x002d415c):goto L_002d415c;
 case UINT32_C(0x002d4160):goto L_002d4160;
 case UINT32_C(0x002d4164):goto L_002d4164;
 case UINT32_C(0x002d4168):goto L_002d4168;
 case UINT32_C(0x002d416c):goto L_002d416c;
 case UINT32_C(0x002d4170):goto L_002d4170;
 case UINT32_C(0x002d4174):goto L_002d4174;
 case UINT32_C(0x002d4178):goto L_002d4178;
 case UINT32_C(0x002d417c):goto L_002d417c;
 case UINT32_C(0x002d4180):goto L_002d4180;
 case UINT32_C(0x002d4184):goto L_002d4184;
 case UINT32_C(0x002d4188):goto L_002d4188;
 case UINT32_C(0x002d418c):goto L_002d418c;
 case UINT32_C(0x002d4190):goto L_002d4190;
 case UINT32_C(0x002d4194):goto L_002d4194;
 case UINT32_C(0x002d4198):goto L_002d4198;
 case UINT32_C(0x002d419c):goto L_002d419c;
 case UINT32_C(0x002d41a0):goto L_002d41a0;
 case UINT32_C(0x002d41a4):goto L_002d41a4;
 case UINT32_C(0x002d41a8):goto L_002d41a8;
 case UINT32_C(0x002d41ac):goto L_002d41ac;
 case UINT32_C(0x002d41b0):goto L_002d41b0;
 case UINT32_C(0x002d41b4):goto L_002d41b4;
 case UINT32_C(0x002d41b8):goto L_002d41b8;
 case UINT32_C(0x002d41bc):goto L_002d41bc;
 case UINT32_C(0x002d41c0):goto L_002d41c0;
 case UINT32_C(0x002d41c4):goto L_002d41c4;
 case UINT32_C(0x002d41c8):goto L_002d41c8;
 case UINT32_C(0x002d41cc):goto L_002d41cc;
 case UINT32_C(0x002d41d0):goto L_002d41d0;
 case UINT32_C(0x002d41d4):goto L_002d41d4;
 case UINT32_C(0x002d41d8):goto L_002d41d8;
 case UINT32_C(0x002d41dc):goto L_002d41dc;
 case UINT32_C(0x002d41e0):goto L_002d41e0;
 case UINT32_C(0x002d41e4):goto L_002d41e4;
 case UINT32_C(0x002d41e8):goto L_002d41e8;
 case UINT32_C(0x002d41ec):goto L_002d41ec;
 case UINT32_C(0x002d41f0):goto L_002d41f0;
 case UINT32_C(0x002d41f4):goto L_002d41f4;
 case UINT32_C(0x002d41f8):goto L_002d41f8;
 case UINT32_C(0x002d41fc):goto L_002d41fc;
 case UINT32_C(0x002d4200):goto L_002d4200;
 case UINT32_C(0x002d4204):goto L_002d4204;
 case UINT32_C(0x002d4208):goto L_002d4208;
 case UINT32_C(0x002d420c):goto L_002d420c;
 case UINT32_C(0x002d4210):goto L_002d4210;
 case UINT32_C(0x002d4214):goto L_002d4214;
 case UINT32_C(0x002d4218):goto L_002d4218;
 case UINT32_C(0x002d421c):goto L_002d421c;
 case UINT32_C(0x002d4220):goto L_002d4220;
 case UINT32_C(0x002d4224):goto L_002d4224;
 case UINT32_C(0x002d4228):goto L_002d4228;
 case UINT32_C(0x002d422c):goto L_002d422c;
 case UINT32_C(0x002d4230):goto L_002d4230;
 case UINT32_C(0x002d4234):goto L_002d4234;
 case UINT32_C(0x002d4238):goto L_002d4238;
 case UINT32_C(0x002d423c):goto L_002d423c;
 case UINT32_C(0x002d4240):goto L_002d4240;
 case UINT32_C(0x002d4244):goto L_002d4244;
 case UINT32_C(0x002d4248):goto L_002d4248;
 case UINT32_C(0x002d424c):goto L_002d424c;
 case UINT32_C(0x002d4250):goto L_002d4250;
 case UINT32_C(0x002d4254):goto L_002d4254;
 case UINT32_C(0x002d4258):goto L_002d4258;
 case UINT32_C(0x002d425c):goto L_002d425c;
 case UINT32_C(0x002d4260):goto L_002d4260;
 case UINT32_C(0x002d4264):goto L_002d4264;
 case UINT32_C(0x002d4268):goto L_002d4268;
 case UINT32_C(0x002d426c):goto L_002d426c;
 case UINT32_C(0x002d4270):goto L_002d4270;
 case UINT32_C(0x002d4274):goto L_002d4274;
 case UINT32_C(0x002d4278):goto L_002d4278;
 case UINT32_C(0x002d427c):goto L_002d427c;
 case UINT32_C(0x002d4280):goto L_002d4280;
 case UINT32_C(0x002d4284):goto L_002d4284;
 case UINT32_C(0x002d4288):goto L_002d4288;
 case UINT32_C(0x002d428c):goto L_002d428c;
 case UINT32_C(0x002d4290):goto L_002d4290;
 case UINT32_C(0x002d4294):goto L_002d4294;
 case UINT32_C(0x002d4298):goto L_002d4298;
 case UINT32_C(0x002d429c):goto L_002d429c;
 case UINT32_C(0x002d42a0):goto L_002d42a0;
 case UINT32_C(0x002d42a4):goto L_002d42a4;
 case UINT32_C(0x002d42a8):goto L_002d42a8;
 case UINT32_C(0x002d42ac):goto L_002d42ac;
 case UINT32_C(0x002d42b0):goto L_002d42b0;
 case UINT32_C(0x002d42b4):goto L_002d42b4;
 case UINT32_C(0x002d42b8):goto L_002d42b8;
 case UINT32_C(0x002d42bc):goto L_002d42bc;
 case UINT32_C(0x002d42c0):goto L_002d42c0;
 case UINT32_C(0x002d42c4):goto L_002d42c4;
 case UINT32_C(0x002d42c8):goto L_002d42c8;
 case UINT32_C(0x002d42cc):goto L_002d42cc;
 case UINT32_C(0x002d42d0):goto L_002d42d0;
 case UINT32_C(0x002d42d4):goto L_002d42d4;
 case UINT32_C(0x002d42d8):goto L_002d42d8;
 case UINT32_C(0x002d42dc):goto L_002d42dc;
 case UINT32_C(0x002d42e0):goto L_002d42e0;
 case UINT32_C(0x002d42e4):goto L_002d42e4;
 case UINT32_C(0x002d42e8):goto L_002d42e8;
 case UINT32_C(0x002d42ec):goto L_002d42ec;
 case UINT32_C(0x002d42f0):goto L_002d42f0;
 case UINT32_C(0x002d42f4):goto L_002d42f4;
 case UINT32_C(0x002d42f8):goto L_002d42f8;
 case UINT32_C(0x002d42fc):goto L_002d42fc;
 case UINT32_C(0x002d4300):goto L_002d4300;
 case UINT32_C(0x002d4304):goto L_002d4304;
 case UINT32_C(0x002d4308):goto L_002d4308;
 case UINT32_C(0x002d430c):goto L_002d430c;
 case UINT32_C(0x002d3990):goto L_002d3990;
 case UINT32_C(0x002d3994):goto L_002d3994;
 case UINT32_C(0x002d3998):goto L_002d3998;
 case UINT32_C(0x002d399c):goto L_002d399c;
 case UINT32_C(0x002d39a0):goto L_002d39a0;
 case UINT32_C(0x002d39a4):goto L_002d39a4;
 case UINT32_C(0x002d39a8):goto L_002d39a8;
 case UINT32_C(0x002d39ac):goto L_002d39ac;
 case UINT32_C(0x002d39b0):goto L_002d39b0;
 case UINT32_C(0x002d39b4):goto L_002d39b4;
 case UINT32_C(0x002d39b8):goto L_002d39b8;
 case UINT32_C(0x002d39bc):goto L_002d39bc;
 case UINT32_C(0x002d39c0):goto L_002d39c0;
 case UINT32_C(0x002d39c4):goto L_002d39c4;
 case UINT32_C(0x002d39c8):goto L_002d39c8;
 case UINT32_C(0x002d39cc):goto L_002d39cc;
 case UINT32_C(0x002d39d0):goto L_002d39d0;
 case UINT32_C(0x002d39d4):goto L_002d39d4;
 case UINT32_C(0x002d39d8):goto L_002d39d8;
 case UINT32_C(0x002d39dc):goto L_002d39dc;
 case UINT32_C(0x002d39e0):goto L_002d39e0;
 case UINT32_C(0x002d39e4):goto L_002d39e4;
 case UINT32_C(0x002d39e8):goto L_002d39e8;
 case UINT32_C(0x002d39ec):goto L_002d39ec;
 case UINT32_C(0x002d39f0):goto L_002d39f0;
 case UINT32_C(0x002d39f4):goto L_002d39f4;
 case UINT32_C(0x002d39f8):goto L_002d39f8;
 case UINT32_C(0x002d39fc):goto L_002d39fc;
 case UINT32_C(0x002d3a00):goto L_002d3a00;
 case UINT32_C(0x002d3a04):goto L_002d3a04;
 case UINT32_C(0x002d3a08):goto L_002d3a08;
 case UINT32_C(0x002d3a0c):goto L_002d3a0c;
 case UINT32_C(0x002d3a10):goto L_002d3a10;
 case UINT32_C(0x002d3a14):goto L_002d3a14;
 case UINT32_C(0x002d3a18):goto L_002d3a18;
 case UINT32_C(0x002d3a1c):goto L_002d3a1c;
 case UINT32_C(0x002d3a20):goto L_002d3a20;
 case UINT32_C(0x002d3a24):goto L_002d3a24;
 case UINT32_C(0x002d3a28):goto L_002d3a28;
 case UINT32_C(0x002d3a2c):goto L_002d3a2c;
 case UINT32_C(0x002d3a30):goto L_002d3a30;
 case UINT32_C(0x002d3a34):goto L_002d3a34;
 case UINT32_C(0x002d3a38):goto L_002d3a38;
 case UINT32_C(0x002d3a3c):goto L_002d3a3c;
 case UINT32_C(0x002d3a40):goto L_002d3a40;
 case UINT32_C(0x002d3a44):goto L_002d3a44;
 case UINT32_C(0x002d3a48):goto L_002d3a48;
 case UINT32_C(0x002d3a4c):goto L_002d3a4c;
 case UINT32_C(0x002d3a50):goto L_002d3a50;
 case UINT32_C(0x002d3a54):goto L_002d3a54;
 case UINT32_C(0x002d3a58):goto L_002d3a58;
 case UINT32_C(0x002d3a5c):goto L_002d3a5c;
 case UINT32_C(0x002d3a60):goto L_002d3a60;
 case UINT32_C(0x002d3a64):goto L_002d3a64;
 case UINT32_C(0x002d3a68):goto L_002d3a68;
 case UINT32_C(0x002d3a6c):goto L_002d3a6c;
 case UINT32_C(0x002d3a70):goto L_002d3a70;
 case UINT32_C(0x002d3a74):goto L_002d3a74;
 case UINT32_C(0x002d3a78):goto L_002d3a78;
 case UINT32_C(0x002d3a7c):goto L_002d3a7c;
 case UINT32_C(0x002d3a80):goto L_002d3a80;
 case UINT32_C(0x002d3a84):goto L_002d3a84;
 case UINT32_C(0x002d3a88):goto L_002d3a88;
 case UINT32_C(0x002d3a8c):goto L_002d3a8c;
 case UINT32_C(0x002d3a90):goto L_002d3a90;
 case UINT32_C(0x002d3a94):goto L_002d3a94;
 case UINT32_C(0x002d3a98):goto L_002d3a98;
 case UINT32_C(0x002d3a9c):goto L_002d3a9c;
 case UINT32_C(0x002d3aa0):goto L_002d3aa0;
 case UINT32_C(0x002d3aa4):goto L_002d3aa4;
 case UINT32_C(0x002d3aa8):goto L_002d3aa8;
 case UINT32_C(0x002d3aac):goto L_002d3aac;
 case UINT32_C(0x002d3ab0):goto L_002d3ab0;
 case UINT32_C(0x002d3ab4):goto L_002d3ab4;
 case UINT32_C(0x002d3ab8):goto L_002d3ab8;
 case UINT32_C(0x002d3abc):goto L_002d3abc;
 case UINT32_C(0x002d3ac0):goto L_002d3ac0;
 case UINT32_C(0x002d3ac4):goto L_002d3ac4;
 case UINT32_C(0x002d3ac8):goto L_002d3ac8;
 case UINT32_C(0x002d3acc):goto L_002d3acc;
 case UINT32_C(0x002d3ad0):goto L_002d3ad0;
 case UINT32_C(0x002d3ad4):goto L_002d3ad4;
 case UINT32_C(0x002d3ad8):goto L_002d3ad8;
 case UINT32_C(0x002d3adc):goto L_002d3adc;
 case UINT32_C(0x002d3ae0):goto L_002d3ae0;
 case UINT32_C(0x002d3ae4):goto L_002d3ae4;
 case UINT32_C(0x002d3ae8):goto L_002d3ae8;
 case UINT32_C(0x002d3aec):goto L_002d3aec;
 case UINT32_C(0x002d3af0):goto L_002d3af0;
 case UINT32_C(0x002d3af4):goto L_002d3af4;
 case UINT32_C(0x002d3af8):goto L_002d3af8;
 case UINT32_C(0x002d3afc):goto L_002d3afc;
 case UINT32_C(0x002d3b00):goto L_002d3b00;
 case UINT32_C(0x002d3b04):goto L_002d3b04;
 case UINT32_C(0x002d3b08):goto L_002d3b08;
 case UINT32_C(0x002d3b0c):goto L_002d3b0c;
 case UINT32_C(0x002d3b10):goto L_002d3b10;
 case UINT32_C(0x002d3b14):goto L_002d3b14;
 case UINT32_C(0x002d3b18):goto L_002d3b18;
 case UINT32_C(0x002d3b1c):goto L_002d3b1c;
 case UINT32_C(0x002d3b20):goto L_002d3b20;
 case UINT32_C(0x002d3b24):goto L_002d3b24;
 case UINT32_C(0x002d3b28):goto L_002d3b28;
 case UINT32_C(0x002d3b2c):goto L_002d3b2c;
 case UINT32_C(0x002d3b30):goto L_002d3b30;
 case UINT32_C(0x002d3b34):goto L_002d3b34;
 case UINT32_C(0x002d3b38):goto L_002d3b38;
 case UINT32_C(0x002d3b3c):goto L_002d3b3c;
 case UINT32_C(0x002d3b40):goto L_002d3b40;
 case UINT32_C(0x002d3b44):goto L_002d3b44;
 case UINT32_C(0x002d3b48):goto L_002d3b48;
 case UINT32_C(0x002d3b4c):goto L_002d3b4c;
 case UINT32_C(0x002d3b50):goto L_002d3b50;
 case UINT32_C(0x002d3b54):goto L_002d3b54;
 case UINT32_C(0x002d3b58):goto L_002d3b58;
 case UINT32_C(0x002d3b5c):goto L_002d3b5c;
 case UINT32_C(0x002d3b60):goto L_002d3b60;
 case UINT32_C(0x002d3b64):goto L_002d3b64;
 case UINT32_C(0x002d3b68):goto L_002d3b68;
 case UINT32_C(0x002d3b6c):goto L_002d3b6c;
 case UINT32_C(0x002d3b70):goto L_002d3b70;
 case UINT32_C(0x002d3b74):goto L_002d3b74;
 case UINT32_C(0x002d3b78):goto L_002d3b78;
 case UINT32_C(0x002d3b7c):goto L_002d3b7c;
 case UINT32_C(0x002d3b80):goto L_002d3b80;
 case UINT32_C(0x002d3b84):goto L_002d3b84;
 case UINT32_C(0x002d3b88):goto L_002d3b88;
 case UINT32_C(0x002d3b8c):goto L_002d3b8c;
 case UINT32_C(0x002d3b90):goto L_002d3b90;
 case UINT32_C(0x002d3b94):goto L_002d3b94;
 case UINT32_C(0x002d3b98):goto L_002d3b98;
 case UINT32_C(0x002d3b9c):goto L_002d3b9c;
 case UINT32_C(0x002d3ba0):goto L_002d3ba0;
 case UINT32_C(0x002d3ba4):goto L_002d3ba4;
 case UINT32_C(0x002d3ba8):goto L_002d3ba8;
 case UINT32_C(0x002d3bac):goto L_002d3bac;
 case UINT32_C(0x002d3bb0):goto L_002d3bb0;
 case UINT32_C(0x002d3bb4):goto L_002d3bb4;
 case UINT32_C(0x002d3bb8):goto L_002d3bb8;
 case UINT32_C(0x002d3bbc):goto L_002d3bbc;
 case UINT32_C(0x002d3bc0):goto L_002d3bc0;
 case UINT32_C(0x002d3bc4):goto L_002d3bc4;
 case UINT32_C(0x002d3bc8):goto L_002d3bc8;
 case UINT32_C(0x002d3bcc):goto L_002d3bcc;
 case UINT32_C(0x002d3bd0):goto L_002d3bd0;
 case UINT32_C(0x002d3bd4):goto L_002d3bd4;
 case UINT32_C(0x002d3bd8):goto L_002d3bd8;
 case UINT32_C(0x002d3bdc):goto L_002d3bdc;
 case UINT32_C(0x002d3be0):goto L_002d3be0;
 case UINT32_C(0x002d3be4):goto L_002d3be4;
 case UINT32_C(0x002d9998):goto L_002d9998;
 case UINT32_C(0x002d999c):goto L_002d999c;
 case UINT32_C(0x002d99a0):goto L_002d99a0;
 case UINT32_C(0x002d99a4):goto L_002d99a4;
 case UINT32_C(0x002d99a8):goto L_002d99a8;
 case UINT32_C(0x002d99ac):goto L_002d99ac;
 case UINT32_C(0x002d99b0):goto L_002d99b0;
 case UINT32_C(0x002d99b4):goto L_002d99b4;
 case UINT32_C(0x002d99b8):goto L_002d99b8;
 case UINT32_C(0x002d99bc):goto L_002d99bc;
 case UINT32_C(0x002d99c0):goto L_002d99c0;
 case UINT32_C(0x002d99c4):goto L_002d99c4;
 case UINT32_C(0x002d99c8):goto L_002d99c8;
 case UINT32_C(0x002d99cc):goto L_002d99cc;
 case UINT32_C(0x002d99d0):goto L_002d99d0;
 case UINT32_C(0x002d99d4):goto L_002d99d4;
 case UINT32_C(0x002d99d8):goto L_002d99d8;
 case UINT32_C(0x002d99dc):goto L_002d99dc;
 case UINT32_C(0x002d99e0):goto L_002d99e0;
 case UINT32_C(0x002d99e4):goto L_002d99e4;
 case UINT32_C(0x002d99e8):goto L_002d99e8;
 case UINT32_C(0x002d99ec):goto L_002d99ec;
 case UINT32_C(0x002d99f0):goto L_002d99f0;
 case UINT32_C(0x002d99f4):goto L_002d99f4;
 case UINT32_C(0x002d99f8):goto L_002d99f8;
 case UINT32_C(0x002d99fc):goto L_002d99fc;
 case UINT32_C(0x002d9a00):goto L_002d9a00;
 case UINT32_C(0x002d9a04):goto L_002d9a04;
 case UINT32_C(0x002d9a08):goto L_002d9a08;
 case UINT32_C(0x002d9a0c):goto L_002d9a0c;
 case UINT32_C(0x002d9a10):goto L_002d9a10;
 case UINT32_C(0x002d9a14):goto L_002d9a14;
 case UINT32_C(0x002d9a18):goto L_002d9a18;
 case UINT32_C(0x002d9a1c):goto L_002d9a1c;
 case UINT32_C(0x002d9a20):goto L_002d9a20;
 case UINT32_C(0x002d9a24):goto L_002d9a24;
 case UINT32_C(0x002d9a28):goto L_002d9a28;
 case UINT32_C(0x002d9a2c):goto L_002d9a2c;
 case UINT32_C(0x002d9a30):goto L_002d9a30;
 case UINT32_C(0x002d9a34):goto L_002d9a34;
 case UINT32_C(0x002d9a38):goto L_002d9a38;
 case UINT32_C(0x002d9a3c):goto L_002d9a3c;
 case UINT32_C(0x002d9a40):goto L_002d9a40;
 case UINT32_C(0x002d9a44):goto L_002d9a44;
 case UINT32_C(0x002d9a48):goto L_002d9a48;
 case UINT32_C(0x002d9a4c):goto L_002d9a4c;
 case UINT32_C(0x002d9a50):goto L_002d9a50;
 case UINT32_C(0x002d9a54):goto L_002d9a54;
 case UINT32_C(0x002d9a58):goto L_002d9a58;
 case UINT32_C(0x002d9a5c):goto L_002d9a5c;
 case UINT32_C(0x002d9a60):goto L_002d9a60;
 case UINT32_C(0x002d9a64):goto L_002d9a64;
 case UINT32_C(0x002d9a68):goto L_002d9a68;
 case UINT32_C(0x002d9a6c):goto L_002d9a6c;
 case UINT32_C(0x002d9a70):goto L_002d9a70;
 case UINT32_C(0x002d9a74):goto L_002d9a74;
 case UINT32_C(0x002d9a78):goto L_002d9a78;
 case UINT32_C(0x002d9a7c):goto L_002d9a7c;
 case UINT32_C(0x002d9a80):goto L_002d9a80;
 case UINT32_C(0x002d9a84):goto L_002d9a84;
 case UINT32_C(0x002d9a88):goto L_002d9a88;
 case UINT32_C(0x002d9a8c):goto L_002d9a8c;
 case UINT32_C(0x002d9a90):goto L_002d9a90;
 case UINT32_C(0x002d9a94):goto L_002d9a94;
 case UINT32_C(0x002d9a98):goto L_002d9a98;
 case UINT32_C(0x002d9a9c):goto L_002d9a9c;
 case UINT32_C(0x002d9aa0):goto L_002d9aa0;
 case UINT32_C(0x002d9aa4):goto L_002d9aa4;
 case UINT32_C(0x002d9aa8):goto L_002d9aa8;
 case UINT32_C(0x002d9aac):goto L_002d9aac;
 case UINT32_C(0x002d9ab0):goto L_002d9ab0;
 case UINT32_C(0x002d9ab4):goto L_002d9ab4;
 case UINT32_C(0x002d9ab8):goto L_002d9ab8;
 case UINT32_C(0x002d9abc):goto L_002d9abc;
 case UINT32_C(0x002d9ac0):goto L_002d9ac0;
 case UINT32_C(0x002d9ac4):goto L_002d9ac4;
 case UINT32_C(0x002d9ac8):goto L_002d9ac8;
 case UINT32_C(0x002d9acc):goto L_002d9acc;
 case UINT32_C(0x002d9ad0):goto L_002d9ad0;
 case UINT32_C(0x002d9ad4):goto L_002d9ad4;
 case UINT32_C(0x002d9ad8):goto L_002d9ad8;
 case UINT32_C(0x002d9adc):goto L_002d9adc;
 case UINT32_C(0x002d9ae0):goto L_002d9ae0;
 case UINT32_C(0x002d9ae4):goto L_002d9ae4;
 case UINT32_C(0x002d9ae8):goto L_002d9ae8;
 case UINT32_C(0x002d9aec):goto L_002d9aec;
 case UINT32_C(0x002d9af0):goto L_002d9af0;
 case UINT32_C(0x002d9af4):goto L_002d9af4;
 case UINT32_C(0x002d9af8):goto L_002d9af8;
 case UINT32_C(0x002d9afc):goto L_002d9afc;
 case UINT32_C(0x002d9b00):goto L_002d9b00;
 case UINT32_C(0x002d9b04):goto L_002d9b04;
 case UINT32_C(0x002d9b08):goto L_002d9b08;
 case UINT32_C(0x002d9b0c):goto L_002d9b0c;
 case UINT32_C(0x002d9b10):goto L_002d9b10;
 case UINT32_C(0x002d9b14):goto L_002d9b14;
 case UINT32_C(0x002d9b18):goto L_002d9b18;
 case UINT32_C(0x002d9b1c):goto L_002d9b1c;
 case UINT32_C(0x002d9b20):goto L_002d9b20;
 case UINT32_C(0x002d9b24):goto L_002d9b24;
 case UINT32_C(0x002d9b28):goto L_002d9b28;
 case UINT32_C(0x002d9b2c):goto L_002d9b2c;
 case UINT32_C(0x002d9b30):goto L_002d9b30;
 case UINT32_C(0x002d9b34):goto L_002d9b34;
 case UINT32_C(0x002d9b38):goto L_002d9b38;
 case UINT32_C(0x002d9b3c):goto L_002d9b3c;
 case UINT32_C(0x002d9b40):goto L_002d9b40;
 case UINT32_C(0x002d9b44):goto L_002d9b44;
 case UINT32_C(0x002d9b48):goto L_002d9b48;
 case UINT32_C(0x002d9b4c):goto L_002d9b4c;
 case UINT32_C(0x002d9b50):goto L_002d9b50;
 case UINT32_C(0x002d9b54):goto L_002d9b54;
 case UINT32_C(0x002d9b58):goto L_002d9b58;
 case UINT32_C(0x002d9b5c):goto L_002d9b5c;
 case UINT32_C(0x002d9b60):goto L_002d9b60;
 case UINT32_C(0x002d9b64):goto L_002d9b64;
 case UINT32_C(0x002d9b68):goto L_002d9b68;
 case UINT32_C(0x002d9b6c):goto L_002d9b6c;
 case UINT32_C(0x002d9b70):goto L_002d9b70;
 case UINT32_C(0x002d9b74):goto L_002d9b74;
 case UINT32_C(0x002d9b78):goto L_002d9b78;
 case UINT32_C(0x002d9b7c):goto L_002d9b7c;
 case UINT32_C(0x002d9b80):goto L_002d9b80;
 case UINT32_C(0x002d9b84):goto L_002d9b84;
 case UINT32_C(0x002d9b88):goto L_002d9b88;
 case UINT32_C(0x002d9b8c):goto L_002d9b8c;
 case UINT32_C(0x002d9b90):goto L_002d9b90;
 case UINT32_C(0x002d9b94):goto L_002d9b94;
 case UINT32_C(0x002d9b98):goto L_002d9b98;
 case UINT32_C(0x002d9b9c):goto L_002d9b9c;
 case UINT32_C(0x002d9ba0):goto L_002d9ba0;
 case UINT32_C(0x002d9ba4):goto L_002d9ba4;
 case UINT32_C(0x002d9ba8):goto L_002d9ba8;
 case UINT32_C(0x002d9bac):goto L_002d9bac;
 case UINT32_C(0x002d9bb0):goto L_002d9bb0;
 case UINT32_C(0x002d9bb4):goto L_002d9bb4;
 case UINT32_C(0x002d9bb8):goto L_002d9bb8;
 case UINT32_C(0x002d9bbc):goto L_002d9bbc;
 case UINT32_C(0x002d9bc0):goto L_002d9bc0;
 case UINT32_C(0x002d9bc4):goto L_002d9bc4;
 case UINT32_C(0x002d9bc8):goto L_002d9bc8;
 case UINT32_C(0x002d9bcc):goto L_002d9bcc;
 case UINT32_C(0x002d9bd0):goto L_002d9bd0;
 case UINT32_C(0x002d9bd4):goto L_002d9bd4;
 case UINT32_C(0x002d9bd8):goto L_002d9bd8;
 case UINT32_C(0x002d9bdc):goto L_002d9bdc;
 case UINT32_C(0x002d9be0):goto L_002d9be0;
 case UINT32_C(0x002d9be4):goto L_002d9be4;
 case UINT32_C(0x002d9be8):goto L_002d9be8;
 case UINT32_C(0x002d9bec):goto L_002d9bec;
 case UINT32_C(0x002d9bf0):goto L_002d9bf0;
 case UINT32_C(0x002d9bf4):goto L_002d9bf4;
 case UINT32_C(0x002d9bf8):goto L_002d9bf8;
 case UINT32_C(0x002d9bfc):goto L_002d9bfc;
 case UINT32_C(0x002d9c00):goto L_002d9c00;
 case UINT32_C(0x002d9c04):goto L_002d9c04;
 case UINT32_C(0x002d9c08):goto L_002d9c08;
 case UINT32_C(0x002d9c0c):goto L_002d9c0c;
 case UINT32_C(0x002d9c10):goto L_002d9c10;
 case UINT32_C(0x002d9c14):goto L_002d9c14;
 case UINT32_C(0x002d9c18):goto L_002d9c18;
 case UINT32_C(0x002d9c1c):goto L_002d9c1c;
 case UINT32_C(0x002d9c20):goto L_002d9c20;
 case UINT32_C(0x002d9c24):goto L_002d9c24;
 case UINT32_C(0x002d9c28):goto L_002d9c28;
 case UINT32_C(0x002d9c2c):goto L_002d9c2c;
 case UINT32_C(0x002d9c30):goto L_002d9c30;
 case UINT32_C(0x002d9c34):goto L_002d9c34;
 case UINT32_C(0x002d9c38):goto L_002d9c38;
 case UINT32_C(0x002d9c3c):goto L_002d9c3c;
 case UINT32_C(0x002d9c40):goto L_002d9c40;
 case UINT32_C(0x002d9c44):goto L_002d9c44;
 case UINT32_C(0x002d9c48):goto L_002d9c48;
 case UINT32_C(0x002d9c4c):goto L_002d9c4c;
 case UINT32_C(0x002d9c50):goto L_002d9c50;
 case UINT32_C(0x002d9c54):goto L_002d9c54;
 case UINT32_C(0x002d9c58):goto L_002d9c58;
 case UINT32_C(0x002d9c5c):goto L_002d9c5c;
 case UINT32_C(0x002d9c60):goto L_002d9c60;
 case UINT32_C(0x002d9c64):goto L_002d9c64;
 case UINT32_C(0x002d9c68):goto L_002d9c68;
 case UINT32_C(0x002d9c6c):goto L_002d9c6c;
 case UINT32_C(0x002d9c70):goto L_002d9c70;
 case UINT32_C(0x002d9c74):goto L_002d9c74;
 case UINT32_C(0x002d9c78):goto L_002d9c78;
 case UINT32_C(0x002d9c7c):goto L_002d9c7c;
 case UINT32_C(0x002d9c80):goto L_002d9c80;
 case UINT32_C(0x002d9c84):goto L_002d9c84;
 case UINT32_C(0x002d9c88):goto L_002d9c88;
 case UINT32_C(0x002d9c90):goto L_002d9c90;
 case UINT32_C(0x002d9c94):goto L_002d9c94;
 case UINT32_C(0x002d9c98):goto L_002d9c98;
 case UINT32_C(0x002d9c9c):goto L_002d9c9c;
 case UINT32_C(0x002d9ca0):goto L_002d9ca0;
 case UINT32_C(0x002d9ca4):goto L_002d9ca4;
 case UINT32_C(0x002d9ca8):goto L_002d9ca8;
 case UINT32_C(0x002d9cac):goto L_002d9cac;
 case UINT32_C(0x002d9cb0):goto L_002d9cb0;
 case UINT32_C(0x002d9cb4):goto L_002d9cb4;
 case UINT32_C(0x002d9cb8):goto L_002d9cb8;
 case UINT32_C(0x002d9cbc):goto L_002d9cbc;
 case UINT32_C(0x002d9cc0):goto L_002d9cc0;
 case UINT32_C(0x002d9cc4):goto L_002d9cc4;
 case UINT32_C(0x002d9cc8):goto L_002d9cc8;
 case UINT32_C(0x002d9ccc):goto L_002d9ccc;
 case UINT32_C(0x002d9cd0):goto L_002d9cd0;
 case UINT32_C(0x002d9cd4):goto L_002d9cd4;
 case UINT32_C(0x002d9cd8):goto L_002d9cd8;
 case UINT32_C(0x002d9cdc):goto L_002d9cdc;
 case UINT32_C(0x002d9ce0):goto L_002d9ce0;
 case UINT32_C(0x002d9ce4):goto L_002d9ce4;
 case UINT32_C(0x002d9ce8):goto L_002d9ce8;
 case UINT32_C(0x002d9cec):goto L_002d9cec;
 case UINT32_C(0x002d9cf0):goto L_002d9cf0;
 case UINT32_C(0x002d9cf4):goto L_002d9cf4;
 case UINT32_C(0x002d9cf8):goto L_002d9cf8;
 case UINT32_C(0x002d9cfc):goto L_002d9cfc;
 case UINT32_C(0x002d9d00):goto L_002d9d00;
 case UINT32_C(0x002d9d04):goto L_002d9d04;
 case UINT32_C(0x002d9d08):goto L_002d9d08;
 case UINT32_C(0x002d9d0c):goto L_002d9d0c;
 case UINT32_C(0x002d9d10):goto L_002d9d10;
 case UINT32_C(0x002d9d14):goto L_002d9d14;
 case UINT32_C(0x002d9d18):goto L_002d9d18;
 case UINT32_C(0x002d9d1c):goto L_002d9d1c;
 case UINT32_C(0x002d9d20):goto L_002d9d20;
 case UINT32_C(0x002d9d24):goto L_002d9d24;
 case UINT32_C(0x002d9d28):goto L_002d9d28;
 case UINT32_C(0x002d9d2c):goto L_002d9d2c;
 case UINT32_C(0x002d9d30):goto L_002d9d30;
 case UINT32_C(0x002d9d34):goto L_002d9d34;
 case UINT32_C(0x002d9d38):goto L_002d9d38;
 case UINT32_C(0x002d9d3c):goto L_002d9d3c;
 case UINT32_C(0x002d9d40):goto L_002d9d40;
 case UINT32_C(0x002d9d44):goto L_002d9d44;
 case UINT32_C(0x002d9d48):goto L_002d9d48;
 case UINT32_C(0x002d9d4c):goto L_002d9d4c;
 case UINT32_C(0x002d9d50):goto L_002d9d50;
 case UINT32_C(0x002d9d54):goto L_002d9d54;
 case UINT32_C(0x002d9d58):goto L_002d9d58;
 case UINT32_C(0x002d9d5c):goto L_002d9d5c;
 case UINT32_C(0x002d9d60):goto L_002d9d60;
 case UINT32_C(0x002d9d64):goto L_002d9d64;
 case UINT32_C(0x002d9d68):goto L_002d9d68;
 case UINT32_C(0x002d9d6c):goto L_002d9d6c;
 case UINT32_C(0x002d9d70):goto L_002d9d70;
 case UINT32_C(0x002d9d74):goto L_002d9d74;
 case UINT32_C(0x002d9d78):goto L_002d9d78;
 case UINT32_C(0x002d9d7c):goto L_002d9d7c;
 case UINT32_C(0x002d9d80):goto L_002d9d80;
 case UINT32_C(0x002d9d84):goto L_002d9d84;
 case UINT32_C(0x002d9d88):goto L_002d9d88;
 case UINT32_C(0x002d9d8c):goto L_002d9d8c;
 case UINT32_C(0x002d9d90):goto L_002d9d90;
 case UINT32_C(0x002d9d94):goto L_002d9d94;
 case UINT32_C(0x002d9d98):goto L_002d9d98;
 case UINT32_C(0x002d9d9c):goto L_002d9d9c;
 case UINT32_C(0x002d9da0):goto L_002d9da0;
 case UINT32_C(0x002d9da4):goto L_002d9da4;
 case UINT32_C(0x002d9da8):goto L_002d9da8;
 case UINT32_C(0x002d9dac):goto L_002d9dac;
 case UINT32_C(0x002d9db0):goto L_002d9db0;
 case UINT32_C(0x002d9db4):goto L_002d9db4;
 case UINT32_C(0x002d9db8):goto L_002d9db8;
 case UINT32_C(0x002d9dbc):goto L_002d9dbc;
 case UINT32_C(0x002d9dc0):goto L_002d9dc0;
 case UINT32_C(0x002d9dc4):goto L_002d9dc4;
 case UINT32_C(0x002d9dc8):goto L_002d9dc8;
 case UINT32_C(0x002d9dcc):goto L_002d9dcc;
 case UINT32_C(0x002d9dd0):goto L_002d9dd0;
 case UINT32_C(0x002d9dd4):goto L_002d9dd4;
 case UINT32_C(0x002d9dd8):goto L_002d9dd8;
 case UINT32_C(0x002d9ddc):goto L_002d9ddc;
 case UINT32_C(0x002d9de0):goto L_002d9de0;
 case UINT32_C(0x002d9de4):goto L_002d9de4;
 case UINT32_C(0x002d9de8):goto L_002d9de8;
 case UINT32_C(0x002d9dec):goto L_002d9dec;
 case UINT32_C(0x002d9df0):goto L_002d9df0;
 case UINT32_C(0x002d9df4):goto L_002d9df4;
 case UINT32_C(0x002d9df8):goto L_002d9df8;
 case UINT32_C(0x002d4618):goto L_002d4618;
 case UINT32_C(0x002d461c):goto L_002d461c;
 case UINT32_C(0x002d4620):goto L_002d4620;
 case UINT32_C(0x002d4624):goto L_002d4624;
 case UINT32_C(0x002d4628):goto L_002d4628;
 case UINT32_C(0x002d462c):goto L_002d462c;
 case UINT32_C(0x002d4630):goto L_002d4630;
 case UINT32_C(0x002d4634):goto L_002d4634;
 case UINT32_C(0x002d4638):goto L_002d4638;
 case UINT32_C(0x002d463c):goto L_002d463c;
 case UINT32_C(0x002d4640):goto L_002d4640;
 case UINT32_C(0x002d4644):goto L_002d4644;
 case UINT32_C(0x002d4648):goto L_002d4648;
 case UINT32_C(0x002d464c):goto L_002d464c;
 case UINT32_C(0x002d4650):goto L_002d4650;
 case UINT32_C(0x002d4654):goto L_002d4654;
 case UINT32_C(0x002d4658):goto L_002d4658;
 case UINT32_C(0x002d465c):goto L_002d465c;
 case UINT32_C(0x002d4660):goto L_002d4660;
 case UINT32_C(0x002d4664):goto L_002d4664;
 case UINT32_C(0x002d4668):goto L_002d4668;
 case UINT32_C(0x002d466c):goto L_002d466c;
 case UINT32_C(0x002d4670):goto L_002d4670;
 case UINT32_C(0x002d4674):goto L_002d4674;
 case UINT32_C(0x002d4678):goto L_002d4678;
 case UINT32_C(0x002d467c):goto L_002d467c;
 case UINT32_C(0x002d4680):goto L_002d4680;
 case UINT32_C(0x002d4684):goto L_002d4684;
 case UINT32_C(0x002d4688):goto L_002d4688;
 case UINT32_C(0x002d468c):goto L_002d468c;
 case UINT32_C(0x002d4690):goto L_002d4690;
 case UINT32_C(0x002d4698):goto L_002d4698;
 case UINT32_C(0x002d469c):goto L_002d469c;
 case UINT32_C(0x002d46a0):goto L_002d46a0;
 case UINT32_C(0x002d46a4):goto L_002d46a4;
 case UINT32_C(0x002d46a8):goto L_002d46a8;
 case UINT32_C(0x002d46ac):goto L_002d46ac;
 case UINT32_C(0x002d46b0):goto L_002d46b0;
 case UINT32_C(0x002d46b4):goto L_002d46b4;
 case UINT32_C(0x002d46b8):goto L_002d46b8;
 case UINT32_C(0x002d46bc):goto L_002d46bc;
 case UINT32_C(0x002d46c0):goto L_002d46c0;
 case UINT32_C(0x002d46c4):goto L_002d46c4;
 case UINT32_C(0x002d46c8):goto L_002d46c8;
 case UINT32_C(0x002d46cc):goto L_002d46cc;
 case UINT32_C(0x002d46d0):goto L_002d46d0;
 case UINT32_C(0x002d46d4):goto L_002d46d4;
 case UINT32_C(0x002d46d8):goto L_002d46d8;
 case UINT32_C(0x002d46dc):goto L_002d46dc;
 case UINT32_C(0x002d46e0):goto L_002d46e0;
 case UINT32_C(0x002d5250):goto L_002d5250;
 case UINT32_C(0x002d5254):goto L_002d5254;
 case UINT32_C(0x002d5258):goto L_002d5258;
 case UINT32_C(0x002d525c):goto L_002d525c;
 case UINT32_C(0x002d5260):goto L_002d5260;
 case UINT32_C(0x002d5264):goto L_002d5264;
 case UINT32_C(0x002d5268):goto L_002d5268;
 case UINT32_C(0x002d526c):goto L_002d526c;
 case UINT32_C(0x002d5270):goto L_002d5270;
 case UINT32_C(0x002d5274):goto L_002d5274;
 case UINT32_C(0x002d5278):goto L_002d5278;
 case UINT32_C(0x002d527c):goto L_002d527c;
 case UINT32_C(0x002d5280):goto L_002d5280;
 case UINT32_C(0x002d5284):goto L_002d5284;
 case UINT32_C(0x002d5288):goto L_002d5288;
 case UINT32_C(0x002d528c):goto L_002d528c;
 case UINT32_C(0x002d5290):goto L_002d5290;
 case UINT32_C(0x002d5294):goto L_002d5294;
 case UINT32_C(0x002d5298):goto L_002d5298;
 case UINT32_C(0x002d529c):goto L_002d529c;
 case UINT32_C(0x002d52a0):goto L_002d52a0;
 case UINT32_C(0x002d52a4):goto L_002d52a4;
 case UINT32_C(0x002dc5a0):goto L_002dc5a0;
 case UINT32_C(0x002dc5a4):goto L_002dc5a4;
 case UINT32_C(0x002dc5a8):goto L_002dc5a8;
 case UINT32_C(0x002dc5ac):goto L_002dc5ac;
 case UINT32_C(0x002dc5b0):goto L_002dc5b0;
 case UINT32_C(0x002dc5b4):goto L_002dc5b4;
 case UINT32_C(0x002dc5b8):goto L_002dc5b8;
 case UINT32_C(0x002dc5bc):goto L_002dc5bc;
 case UINT32_C(0x002dc5c0):goto L_002dc5c0;
 case UINT32_C(0x002dc5c4):goto L_002dc5c4;
 case UINT32_C(0x002dc5c8):goto L_002dc5c8;
 case UINT32_C(0x002dc5cc):goto L_002dc5cc;
 case UINT32_C(0x002dc5d0):goto L_002dc5d0;
 case UINT32_C(0x002dc5d4):goto L_002dc5d4;
 case UINT32_C(0x002dc5d8):goto L_002dc5d8;
 case UINT32_C(0x002dc5dc):goto L_002dc5dc;
 case UINT32_C(0x002dc5e0):goto L_002dc5e0;
 case UINT32_C(0x002dc5e4):goto L_002dc5e4;
 case UINT32_C(0x002dc5e8):goto L_002dc5e8;
 case UINT32_C(0x002dc5ec):goto L_002dc5ec;
 case UINT32_C(0x002dc5f0):goto L_002dc5f0;
 case UINT32_C(0x002dc5f4):goto L_002dc5f4;
 case UINT32_C(0x002dc5f8):goto L_002dc5f8;
 case UINT32_C(0x002dc5fc):goto L_002dc5fc;
 case UINT32_C(0x002dc600):goto L_002dc600;
 case UINT32_C(0x002dc604):goto L_002dc604;
 case UINT32_C(0x002dc608):goto L_002dc608;
 case UINT32_C(0x002dc60c):goto L_002dc60c;
 case UINT32_C(0x002dc610):goto L_002dc610;
 case UINT32_C(0x002dc614):goto L_002dc614;
 case UINT32_C(0x002dc618):goto L_002dc618;
 case UINT32_C(0x002dc61c):goto L_002dc61c;
 case UINT32_C(0x002dc620):goto L_002dc620;
 case UINT32_C(0x002dc624):goto L_002dc624;
 case UINT32_C(0x002dc628):goto L_002dc628;
 case UINT32_C(0x002dc62c):goto L_002dc62c;
 case UINT32_C(0x002dc630):goto L_002dc630;
 case UINT32_C(0x002dc634):goto L_002dc634;
 case UINT32_C(0x002dc638):goto L_002dc638;
 case UINT32_C(0x002dc63c):goto L_002dc63c;
 case UINT32_C(0x002dc640):goto L_002dc640;
 case UINT32_C(0x002dc644):goto L_002dc644;
 case UINT32_C(0x002dc648):goto L_002dc648;
 case UINT32_C(0x002e40d0):goto L_002e40d0;
 case UINT32_C(0x002e40d4):goto L_002e40d4;
 case UINT32_C(0x002e40d8):goto L_002e40d8;
 case UINT32_C(0x002e40dc):goto L_002e40dc;
 case UINT32_C(0x002e40e0):goto L_002e40e0;
 case UINT32_C(0x002e40e4):goto L_002e40e4;
 case UINT32_C(0x002e40e8):goto L_002e40e8;
 case UINT32_C(0x002e40ec):goto L_002e40ec;
 case UINT32_C(0x002e40f0):goto L_002e40f0;
 case UINT32_C(0x002e40f4):goto L_002e40f4;
 case UINT32_C(0x002e40f8):goto L_002e40f8;
 case UINT32_C(0x002e40fc):goto L_002e40fc;
 case UINT32_C(0x002e4100):goto L_002e4100;
 case UINT32_C(0x002e4104):goto L_002e4104;
 case UINT32_C(0x002e4108):goto L_002e4108;
 case UINT32_C(0x002e410c):goto L_002e410c;
 case UINT32_C(0x002e4110):goto L_002e4110;
 case UINT32_C(0x002e4114):goto L_002e4114;
 case UINT32_C(0x002e6e30):goto L_002e6e30;
 case UINT32_C(0x002e6e34):goto L_002e6e34;
 case UINT32_C(0x002e6e38):goto L_002e6e38;
 case UINT32_C(0x002dbe80):goto L_002dbe80;
 case UINT32_C(0x002dbe84):goto L_002dbe84;
 case UINT32_C(0x002dbe88):goto L_002dbe88;
 case UINT32_C(0x002dbe8c):goto L_002dbe8c;
 case UINT32_C(0x002dbec0):goto L_002dbec0;
 case UINT32_C(0x002dbec4):goto L_002dbec4;
 case UINT32_C(0x002dbec8):goto L_002dbec8;
 case UINT32_C(0x002dbecc):goto L_002dbecc;
 case UINT32_C(0x800034c0):goto L_800034c0;
 case UINT32_C(0x800034c4):goto L_800034c4;
 case UINT32_C(0x800034c8):goto L_800034c8;
 case UINT32_C(0x800034cc):goto L_800034cc;
 case UINT32_C(0x800034d0):goto L_800034d0;
 case UINT32_C(0x800034d4):goto L_800034d4;
 case UINT32_C(0x800034d8):goto L_800034d8;
 case UINT32_C(0x800034dc):goto L_800034dc;
 case UINT32_C(0x800034e0):goto L_800034e0;
 case UINT32_C(0x800034e4):goto L_800034e4;
 case UINT32_C(0x800034e8):goto L_800034e8;
 case UINT32_C(0x800034ec):goto L_800034ec;
 case UINT32_C(0x800034f0):goto L_800034f0;
 case UINT32_C(0x800034f4):goto L_800034f4;
 case UINT32_C(0x800034f8):goto L_800034f8;
 case UINT32_C(0x800034fc):goto L_800034fc;
 case UINT32_C(0x80003500):goto L_80003500;
 case UINT32_C(0x80003504):goto L_80003504;
 case UINT32_C(0x80003508):goto L_80003508;
 case UINT32_C(0x8000350c):goto L_8000350c;
 case UINT32_C(0x80003510):goto L_80003510;
 case UINT32_C(0x80003514):goto L_80003514;
 case UINT32_C(0x80003518):goto L_80003518;
 case UINT32_C(0x8000351c):goto L_8000351c;
 case UINT32_C(0x80003520):goto L_80003520;
 case UINT32_C(0x80003524):goto L_80003524;
 case UINT32_C(0x80003528):goto L_80003528;
 case UINT32_C(0x8000352c):goto L_8000352c;
 case UINT32_C(0x80003530):goto L_80003530;
 case UINT32_C(0x80003534):goto L_80003534;
 case UINT32_C(0x80003538):goto L_80003538;
 case UINT32_C(0x8000353c):goto L_8000353c;
 case UINT32_C(0x800052d8):goto L_800052d8;
 case UINT32_C(0x800052dc):goto L_800052dc;
 case UINT32_C(0x800052e0):goto L_800052e0;
 case UINT32_C(0x800052e4):goto L_800052e4;
 case UINT32_C(0x800052e8):goto L_800052e8;
 case UINT32_C(0x800052ec):goto L_800052ec;
 case UINT32_C(0x800052f0):goto L_800052f0;
 case UINT32_C(0x800052f4):goto L_800052f4;
 case UINT32_C(0x800052f8):goto L_800052f8;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002d3be8:
 STEP(UINT32_C(0x002d3be8)); /* 24a30013 addiu v1,a1,19 */
 set(m,3u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000013)));target=sx(UINT32_C(0x002d3bec));goto dispatch;
L_002d3bec:
 STEP(UINT32_C(0x002d3bec)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002d3bf0));goto dispatch;
L_002d3bf0:
 STEP(UINT32_C(0x002d3bf0)); /* 2c62001f sltiu v0,v1,31 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x1f)));target=sx(UINT32_C(0x002d3bf4));goto dispatch;
L_002d3bf4:
 STEP(UINT32_C(0x002d3bf4)); /* ffb30018 sd s3,0x18(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002d3bf8));goto dispatch;
L_002d3bf8:
 STEP(UINT32_C(0x002d3bf8)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d3bfc));goto dispatch;
L_002d3bfc:
 STEP(UINT32_C(0x002d3bfc)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d3c00));goto dispatch;
L_002d3c00:
 STEP(UINT32_C(0x002d3c00)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d3c04));goto dispatch;
L_002d3c04:
 STEP(UINT32_C(0x002d3c04)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d3c08));goto dispatch;
L_002d3c08:
 STEP(UINT32_C(0x002d3c08)); /* ffb40020 sd s4,0x20(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002d3c0c));goto dispatch;
L_002d3c0c:
 STEP(UINT32_C(0x002d3c0c)); /* 14400004 bne v0,zero,002d3c20 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d3c10));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(taken?UINT32_C(0x002d3c20):UINT32_C(0x002d3c14));goto dispatch;}
L_002d3c10:
 STEP(UINT32_C(0x002d3c10)); /* ffbf0028 sd ra,0x28(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(UINT32_C(0x002d3c14));goto dispatch;
L_002d3c14:
 STEP(UINT32_C(0x002d3c14)); /* 2402fff0 addiu v0,zero,-16 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d3c18));goto dispatch;
L_002d3c18:
 STEP(UINT32_C(0x002d3c18)); /* 10000002 beq zero,zero,002d3c24 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3c1c));set(m,17u,lo(m,3u)&lo(m,2u));target=sx(taken?UINT32_C(0x002d3c24):UINT32_C(0x002d3c20));goto dispatch;}
L_002d3c1c:
 STEP(UINT32_C(0x002d3c1c)); /* 00628824 and s1,v1,v0 */
 set(m,17u,lo(m,3u)&lo(m,2u));target=sx(UINT32_C(0x002d3c20));goto dispatch;
L_002d3c20:
 STEP(UINT32_C(0x002d3c20)); /* 24110010 addiu s1,zero,16 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d3c24));goto dispatch;
L_002d3c24:
 STEP(UINT32_C(0x002d3c24)); /* 0c0b5186 jal 002d4618 */
 set(m,31u,UINT64_C(0x002d3c2c));STEP(UINT32_C(0x002d3c28));set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d4618));goto dispatch;
L_002d3c28:
 STEP(UINT32_C(0x002d3c28)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d3c2c));goto dispatch;
L_002d3c2c:
 STEP(UINT32_C(0x002d3c2c)); /* 2e2201f8 sltiu v0,s1,504 */
 set(m,2u,(lo(m,17u)<UINT64_C(0x1f8)));target=sx(UINT32_C(0x002d3c30));goto dispatch;
L_002d3c30:
 STEP(UINT32_C(0x002d3c30)); /* 10400017 beq v0,zero,002d3c90 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3c34));set(m,3u,sx((uint32_t)lo(m,17u)>>9u));target=sx(taken?UINT32_C(0x002d3c90):UINT32_C(0x002d3c38));goto dispatch;}
L_002d3c34:
 STEP(UINT32_C(0x002d3c34)); /* 00111a42 srl v1,s1,9 */
 set(m,3u,sx((uint32_t)lo(m,17u)>>9u));target=sx(UINT32_C(0x002d3c38));goto dispatch;
L_002d3c38:
 STEP(UINT32_C(0x002d3c38)); /* 3c0f0053 lui t7,zero,0x53 */
 set(m,15u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3c3c));goto dispatch;
L_002d3c3c:
 STEP(UINT32_C(0x002d3c3c)); /* 25e2be38 addiu v0,t7,-16840 */
 set(m,2u,sx((uint32_t)lo(m,15u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d3c40));goto dispatch;
L_002d3c40:
 STEP(UINT32_C(0x002d3c40)); /* 2442fff8 addiu v0,v0,-8 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d3c44));goto dispatch;
L_002d3c44:
 STEP(UINT32_C(0x002d3c44)); /* 02222021 addu a0,s1,v0 */
 set(m,4u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d3c48));goto dispatch;
L_002d3c48:
 STEP(UINT32_C(0x002d3c48)); /* 8c90000c lw s0,0xc(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x0000000c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d3c4c));goto dispatch;
L_002d3c4c:
 STEP(UINT32_C(0x002d3c4c)); /* 1204000e beq s0,a0,002d3c88 */
 {int taken=(lo(m,16u)==lo(m,4u));STEP(UINT32_C(0x002d3c50));set(m,10u,sx((uint32_t)lo(m,17u)>>3u));target=sx(taken?UINT32_C(0x002d3c88):UINT32_C(0x002d3c54));goto dispatch;}
L_002d3c50:
 STEP(UINT32_C(0x002d3c50)); /* 001150c2 srl t2,s1,3 */
 set(m,10u,sx((uint32_t)lo(m,17u)>>3u));target=sx(UINT32_C(0x002d3c54));goto dispatch;
L_002d3c54:
 STEP(UINT32_C(0x002d3c54)); /* 8e030004 lw v1,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d3c58));goto dispatch;
L_002d3c58:
 STEP(UINT32_C(0x002d3c58)); /* 2402fffc addiu v0,zero,-4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d3c5c));goto dispatch;
L_002d3c5c:
 STEP(UINT32_C(0x002d3c5c)); /* 8e0b000c lw t3,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,11u,sx(value32));target=sx(UINT32_C(0x002d3c60));goto dispatch;
L_002d3c60:
 STEP(UINT32_C(0x002d3c60)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d3c64));goto dispatch;
L_002d3c64:
 STEP(UINT32_C(0x002d3c64)); /* 00623024 and a2,v1,v0 */
 set(m,6u,lo(m,3u)&lo(m,2u));target=sx(UINT32_C(0x002d3c68));goto dispatch;
L_002d3c68:
 STEP(UINT32_C(0x002d3c68)); /* 8e080008 lw t0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d3c6c));goto dispatch;
L_002d3c6c:
 STEP(UINT32_C(0x002d3c6c)); /* 02061821 addu v1,s0,a2 */
 set(m,3u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d3c70));goto dispatch;
L_002d3c70:
 STEP(UINT32_C(0x002d3c70)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3c74));goto dispatch;
L_002d3c74:
 STEP(UINT32_C(0x002d3c74)); /* ad0b000c sw t3,0xc(t0) */
 value32=(uint32_t)lo(m,11u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d3c78));goto dispatch;
L_002d3c78:
 STEP(UINT32_C(0x002d3c78)); /* 34420001 ori v0,v0,0x1 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d3c7c));goto dispatch;
L_002d3c7c:
 STEP(UINT32_C(0x002d3c7c)); /* ad680008 sw t0,0x8(t3) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3c80));goto dispatch;
L_002d3c80:
 STEP(UINT32_C(0x002d3c80)); /* 10000198 beq zero,zero,002d42e4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3c84));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d42e4):UINT32_C(0x002d3c88));goto dispatch;}
L_002d3c84:
 STEP(UINT32_C(0x002d3c84)); /* ac620004 sw v0,0x4(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3c88));goto dispatch;
L_002d3c88:
 STEP(UINT32_C(0x002d3c88)); /* 10000038 beq zero,zero,002d3d6c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3c8c));set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000002)));target=sx(taken?UINT32_C(0x002d3d6c):UINT32_C(0x002d3c90));goto dispatch;}
L_002d3c8c:
 STEP(UINT32_C(0x002d3c8c)); /* 254a0002 addiu t2,t2,2 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d3c90));goto dispatch;
L_002d3c90:
 STEP(UINT32_C(0x002d3c90)); /* 10600019 beq v1,zero,002d3cf8 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002d3c94));set(m,10u,sx((uint32_t)lo(m,17u)>>3u));target=sx(taken?UINT32_C(0x002d3cf8):UINT32_C(0x002d3c98));goto dispatch;}
L_002d3c94:
 STEP(UINT32_C(0x002d3c94)); /* 001150c2 srl t2,s1,3 */
 set(m,10u,sx((uint32_t)lo(m,17u)>>3u));target=sx(UINT32_C(0x002d3c98));goto dispatch;
L_002d3c98:
 STEP(UINT32_C(0x002d3c98)); /* 2c620005 sltiu v0,v1,5 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x5)));target=sx(UINT32_C(0x002d3c9c));goto dispatch;
L_002d3c9c:
 STEP(UINT32_C(0x002d3c9c)); /* 10400004 beq v0,zero,002d3cb0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3ca0));set(m,2u,(lo(m,3u)<UINT64_C(0x15)));target=sx(taken?UINT32_C(0x002d3cb0):UINT32_C(0x002d3ca4));goto dispatch;}
L_002d3ca0:
 STEP(UINT32_C(0x002d3ca0)); /* 2c620015 sltiu v0,v1,21 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x15)));target=sx(UINT32_C(0x002d3ca4));goto dispatch;
L_002d3ca4:
 STEP(UINT32_C(0x002d3ca4)); /* 00111182 srl v0,s1,6 */
 set(m,2u,sx((uint32_t)lo(m,17u)>>6u));target=sx(UINT32_C(0x002d3ca8));goto dispatch;
L_002d3ca8:
 STEP(UINT32_C(0x002d3ca8)); /* 10000013 beq zero,zero,002d3cf8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3cac));set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000038)));target=sx(taken?UINT32_C(0x002d3cf8):UINT32_C(0x002d3cb0));goto dispatch;}
L_002d3cac:
 STEP(UINT32_C(0x002d3cac)); /* 244a0038 addiu t2,v0,56 */
 set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000038)));target=sx(UINT32_C(0x002d3cb0));goto dispatch;
L_002d3cb0:
 STEP(UINT32_C(0x002d3cb0)); /* 14400011 bne v0,zero,002d3cf8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d3cb4));set(m,10u,sx((uint32_t)lo(m,3u)+UINT32_C(0x0000005b)));target=sx(taken?UINT32_C(0x002d3cf8):UINT32_C(0x002d3cb8));goto dispatch;}
L_002d3cb4:
 STEP(UINT32_C(0x002d3cb4)); /* 246a005b addiu t2,v1,91 */
 set(m,10u,sx((uint32_t)lo(m,3u)+UINT32_C(0x0000005b)));target=sx(UINT32_C(0x002d3cb8));goto dispatch;
L_002d3cb8:
 STEP(UINT32_C(0x002d3cb8)); /* 2c620055 sltiu v0,v1,85 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x55)));target=sx(UINT32_C(0x002d3cbc));goto dispatch;
L_002d3cbc:
 STEP(UINT32_C(0x002d3cbc)); /* 10400004 beq v0,zero,002d3cd0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3cc0));set(m,2u,(lo(m,3u)<UINT64_C(0x155)));target=sx(taken?UINT32_C(0x002d3cd0):UINT32_C(0x002d3cc4));goto dispatch;}
L_002d3cc0:
 STEP(UINT32_C(0x002d3cc0)); /* 2c620155 sltiu v0,v1,341 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x155)));target=sx(UINT32_C(0x002d3cc4));goto dispatch;
L_002d3cc4:
 STEP(UINT32_C(0x002d3cc4)); /* 00111302 srl v0,s1,12 */
 set(m,2u,sx((uint32_t)lo(m,17u)>>12u));target=sx(UINT32_C(0x002d3cc8));goto dispatch;
L_002d3cc8:
 STEP(UINT32_C(0x002d3cc8)); /* 1000000b beq zero,zero,002d3cf8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3ccc));set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000006e)));target=sx(taken?UINT32_C(0x002d3cf8):UINT32_C(0x002d3cd0));goto dispatch;}
L_002d3ccc:
 STEP(UINT32_C(0x002d3ccc)); /* 244a006e addiu t2,v0,110 */
 set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000006e)));target=sx(UINT32_C(0x002d3cd0));goto dispatch;
L_002d3cd0:
 STEP(UINT32_C(0x002d3cd0)); /* 10400005 beq v0,zero,002d3ce8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3cd4));set(m,2u,(lo(m,3u)<UINT64_C(0x555)));target=sx(taken?UINT32_C(0x002d3ce8):UINT32_C(0x002d3cd8));goto dispatch;}
L_002d3cd4:
 STEP(UINT32_C(0x002d3cd4)); /* 2c620555 sltiu v0,v1,1365 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x555)));target=sx(UINT32_C(0x002d3cd8));goto dispatch;
L_002d3cd8:
 STEP(UINT32_C(0x002d3cd8)); /* 001113c2 srl v0,s1,15 */
 set(m,2u,sx((uint32_t)lo(m,17u)>>15u));target=sx(UINT32_C(0x002d3cdc));goto dispatch;
L_002d3cdc:
 STEP(UINT32_C(0x002d3cdc)); /* 10000006 beq zero,zero,002d3cf8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3ce0));set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000077)));target=sx(taken?UINT32_C(0x002d3cf8):UINT32_C(0x002d3ce4));goto dispatch;}
L_002d3ce0:
 STEP(UINT32_C(0x002d3ce0)); /* 244a0077 addiu t2,v0,119 */
 set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000077)));target=sx(UINT32_C(0x002d3ce4));goto dispatch;
L_002d3ce4:
 STEP(UINT32_C(0x002d3ce4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3ce8));goto dispatch;
L_002d3ce8:
 STEP(UINT32_C(0x002d3ce8)); /* 50400003 beql v0,zero,002d3cf8 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d3cec));set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007e)));target=sx(UINT32_C(0x002d3cf8));}else target=sx(UINT32_C(0x002d3cf0));goto dispatch;
L_002d3cec:
 STEP(UINT32_C(0x002d3cec)); /* 240a007e addiu t2,zero,126 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007e)));target=sx(UINT32_C(0x002d3cf0));goto dispatch;
L_002d3cf0:
 STEP(UINT32_C(0x002d3cf0)); /* 00111482 srl v0,s1,18 */
 set(m,2u,sx((uint32_t)lo(m,17u)>>18u));target=sx(UINT32_C(0x002d3cf4));goto dispatch;
L_002d3cf4:
 STEP(UINT32_C(0x002d3cf4)); /* 244a007c addiu t2,v0,124 */
 set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000007c)));target=sx(UINT32_C(0x002d3cf8));goto dispatch;
L_002d3cf8:
 STEP(UINT32_C(0x002d3cf8)); /* 3c0f0053 lui t7,zero,0x53 */
 set(m,15u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3cfc));goto dispatch;
L_002d3cfc:
 STEP(UINT32_C(0x002d3cfc)); /* 000a18c0 sll v1,t2,3 */
 set(m,3u,sx((uint32_t)lo(m,10u)<<3u));target=sx(UINT32_C(0x002d3d00));goto dispatch;
L_002d3d00:
 STEP(UINT32_C(0x002d3d00)); /* 25e2be38 addiu v0,t7,-16840 */
 set(m,2u,sx((uint32_t)lo(m,15u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d3d04));goto dispatch;
L_002d3d04:
 STEP(UINT32_C(0x002d3d04)); /* 2404fffc addiu a0,zero,-4 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d3d08));goto dispatch;
L_002d3d08:
 STEP(UINT32_C(0x002d3d08)); /* 2442fff8 addiu v0,v0,-8 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d3d0c));goto dispatch;
L_002d3d0c:
 STEP(UINT32_C(0x002d3d0c)); /* 00622821 addu a1,v1,v0 */
 set(m,5u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d3d10));goto dispatch;
L_002d3d10:
 STEP(UINT32_C(0x002d3d10)); /* 10000004 beq zero,zero,002d3d24 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3d14));READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002d3d24):UINT32_C(0x002d3d18));goto dispatch;}
L_002d3d14:
 STEP(UINT32_C(0x002d3d14)); /* 8cb0000c lw s0,0xc(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d3d18));goto dispatch;
L_002d3d18:
 STEP(UINT32_C(0x002d3d18)); /* 0501013d regimm1 t0,002d4210 */
 {int taken=((int64_t)lo(m,8u)>=0);STEP(UINT32_C(0x002d3d1c));set(m,3u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,6u)));target=sx(taken?UINT32_C(0x002d4210):UINT32_C(0x002d3d20));goto dispatch;}
L_002d3d1c:
 STEP(UINT32_C(0x002d3d1c)); /* 02061821 addu v1,s0,a2 */
 set(m,3u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d3d20));goto dispatch;
L_002d3d20:
 STEP(UINT32_C(0x002d3d20)); /* 8e10000c lw s0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d3d24));goto dispatch;
L_002d3d24:
 STEP(UINT32_C(0x002d3d24)); /* 52050011 beql s0,a1,002d3d6c */
 if(lo(m,16u)==lo(m,5u)){STEP(UINT32_C(0x002d3d28));set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d3d6c));}else target=sx(UINT32_C(0x002d3d2c));goto dispatch;
L_002d3d28:
 STEP(UINT32_C(0x002d3d28)); /* 254a0001 addiu t2,t2,1 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d3d2c));goto dispatch;
L_002d3d2c:
 STEP(UINT32_C(0x002d3d2c)); /* 8e020004 lw v0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3d30));goto dispatch;
L_002d3d30:
 STEP(UINT32_C(0x002d3d30)); /* 00443024 and a2,v0,a0 */
 set(m,6u,lo(m,2u)&lo(m,4u));target=sx(UINT32_C(0x002d3d34));goto dispatch;
L_002d3d34:
 STEP(UINT32_C(0x002d3d34)); /* 02261823 subu v1,s1,a2 */
 set(m,3u,sx((uint32_t)lo(m,17u)-(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d3d38));goto dispatch;
L_002d3d38:
 STEP(UINT32_C(0x002d3d38)); /* 00d11023 subu v0,a2,s1 */
 set(m,2u,sx((uint32_t)lo(m,6u)-(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d3d3c));goto dispatch;
L_002d3d3c:
 STEP(UINT32_C(0x002d3d3c)); /* 0003183c dsll32 v1,v1,0 */
 set(m,3u,lo(m,3u)<<32u);target=sx(UINT32_C(0x002d3d40));goto dispatch;
L_002d3d40:
 STEP(UINT32_C(0x002d3d40)); /* 0002383c dsll32 a3,v0,0 */
 set(m,7u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d3d44));goto dispatch;
L_002d3d44:
 STEP(UINT32_C(0x002d3d44)); /* 0003183e dsrl32 v1,v1,0 */
 set(m,3u,lo(m,3u)>>32u);target=sx(UINT32_C(0x002d3d48));goto dispatch;
L_002d3d48:
 STEP(UINT32_C(0x002d3d48)); /* 00d1102b sltu v0,a2,s1 */
 set(m,2u,lo(m,6u)<lo(m,17u));target=sx(UINT32_C(0x002d3d4c));goto dispatch;
L_002d3d4c:
 STEP(UINT32_C(0x002d3d4c)); /* 14400002 bne v0,zero,002d3d58 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d3d50));set(m,8u,lo(m,0u)-lo(m,3u));target=sx(taken?UINT32_C(0x002d3d58):UINT32_C(0x002d3d54));goto dispatch;}
L_002d3d50:
 STEP(UINT32_C(0x002d3d50)); /* 0003402f dsubu t0,zero,v1 */
 set(m,8u,lo(m,0u)-lo(m,3u));target=sx(UINT32_C(0x002d3d54));goto dispatch;
L_002d3d54:
 STEP(UINT32_C(0x002d3d54)); /* 0007403e dsrl32 t0,a3,0 */
 set(m,8u,lo(m,7u)>>32u);target=sx(UINT32_C(0x002d3d58));goto dispatch;
L_002d3d58:
 STEP(UINT32_C(0x002d3d58)); /* 29020010 slti v0,t0,16 */
 set(m,2u,((int64_t)lo(m,8u)<INT64_C(16)));target=sx(UINT32_C(0x002d3d5c));goto dispatch;
L_002d3d5c:
 STEP(UINT32_C(0x002d3d5c)); /* 1440ffee bne v0,zero,002d3d18 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d3d60));/* nop */target=sx(taken?UINT32_C(0x002d3d18):UINT32_C(0x002d3d64));goto dispatch;}
L_002d3d60:
 STEP(UINT32_C(0x002d3d60)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3d64));goto dispatch;
L_002d3d64:
 STEP(UINT32_C(0x002d3d64)); /* 254affff addiu t2,t2,-1 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d3d68));goto dispatch;
L_002d3d68:
 STEP(UINT32_C(0x002d3d68)); /* 254a0001 addiu t2,t2,1 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d3d6c));goto dispatch;
L_002d3d6c:
 STEP(UINT32_C(0x002d3d6c)); /* 25e2be38 addiu v0,t7,-16840 */
 set(m,2u,sx((uint32_t)lo(m,15u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d3d70));goto dispatch;
L_002d3d70:
 STEP(UINT32_C(0x002d3d70)); /* 8c500008 lw s0,0x8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d3d74));goto dispatch;
L_002d3d74:
 STEP(UINT32_C(0x002d3d74)); /* 12020080 beq s0,v0,002d3f78 */
 {int taken=(lo(m,16u)==lo(m,2u));STEP(UINT32_C(0x002d3d78));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(taken?UINT32_C(0x002d3f78):UINT32_C(0x002d3d7c));goto dispatch;}
L_002d3d78:
 STEP(UINT32_C(0x002d3d78)); /* 2403fffc addiu v1,zero,-4 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d3d7c));goto dispatch;
L_002d3d7c:
 STEP(UINT32_C(0x002d3d7c)); /* 8e020004 lw v0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3d80));goto dispatch;
L_002d3d80:
 STEP(UINT32_C(0x002d3d80)); /* 00433024 and a2,v0,v1 */
 set(m,6u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d3d84));goto dispatch;
L_002d3d84:
 STEP(UINT32_C(0x002d3d84)); /* 00d1202b sltu a0,a2,s1 */
 set(m,4u,lo(m,6u)<lo(m,17u));target=sx(UINT32_C(0x002d3d88));goto dispatch;
L_002d3d88:
 STEP(UINT32_C(0x002d3d88)); /* 10800007 beq a0,zero,002d3da8 */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x002d3d8c));set(m,2u,sx((uint32_t)lo(m,6u)-(uint32_t)lo(m,17u)));target=sx(taken?UINT32_C(0x002d3da8):UINT32_C(0x002d3d90));goto dispatch;}
L_002d3d8c:
 STEP(UINT32_C(0x002d3d8c)); /* 00d11023 subu v0,a2,s1 */
 set(m,2u,sx((uint32_t)lo(m,6u)-(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d3d90));goto dispatch;
L_002d3d90:
 STEP(UINT32_C(0x002d3d90)); /* 02261023 subu v0,s1,a2 */
 set(m,2u,sx((uint32_t)lo(m,17u)-(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d3d94));goto dispatch;
L_002d3d94:
 STEP(UINT32_C(0x002d3d94)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d3d98));goto dispatch;
L_002d3d98:
 STEP(UINT32_C(0x002d3d98)); /* 0002103e dsrl32 v0,v0,0 */
 set(m,2u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d3d9c));goto dispatch;
L_002d3d9c:
 STEP(UINT32_C(0x002d3d9c)); /* 10000004 beq zero,zero,002d3db0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3da0));set(m,8u,lo(m,0u)-lo(m,2u));target=sx(taken?UINT32_C(0x002d3db0):UINT32_C(0x002d3da4));goto dispatch;}
L_002d3da0:
 STEP(UINT32_C(0x002d3da0)); /* 0002402f dsubu t0,zero,v0 */
 set(m,8u,lo(m,0u)-lo(m,2u));target=sx(UINT32_C(0x002d3da4));goto dispatch;
L_002d3da4:
 STEP(UINT32_C(0x002d3da4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3da8));goto dispatch;
L_002d3da8:
 STEP(UINT32_C(0x002d3da8)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d3dac));goto dispatch;
L_002d3dac:
 STEP(UINT32_C(0x002d3dac)); /* 0002403e dsrl32 t0,v0,0 */
 set(m,8u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d3db0));goto dispatch;
L_002d3db0:
 STEP(UINT32_C(0x002d3db0)); /* 29020010 slti v0,t0,16 */
 set(m,2u,((int64_t)lo(m,8u)<INT64_C(16)));target=sx(UINT32_C(0x002d3db4));goto dispatch;
L_002d3db4:
 STEP(UINT32_C(0x002d3db4)); /* 54400014 bnel v0,zero,002d3e08 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d3db8));set(m,4u,sx((uint32_t)lo(m,15u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d3e08));}else target=sx(UINT32_C(0x002d3dbc));goto dispatch;
L_002d3db8:
 STEP(UINT32_C(0x002d3db8)); /* 25e4be38 addiu a0,t7,-16840 */
 set(m,4u,sx((uint32_t)lo(m,15u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d3dbc));goto dispatch;
L_002d3dbc:
 STEP(UINT32_C(0x002d3dbc)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d3dc0));goto dispatch;
L_002d3dc0:
 STEP(UINT32_C(0x002d3dc0)); /* 02114821 addu t1,s0,s1 */
 set(m,9u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d3dc4));goto dispatch;
L_002d3dc4:
 STEP(UINT32_C(0x002d3dc4)); /* 0008383c dsll32 a3,t0,0 */
 set(m,7u,lo(m,8u)<<32u);target=sx(UINT32_C(0x002d3dc8));goto dispatch;
L_002d3dc8:
 STEP(UINT32_C(0x002d3dc8)); /* 0007383f dsra32 a3,a3,0 */
 set(m,7u,(uint64_t)((int64_t)lo(m,7u)>>32u));target=sx(UINT32_C(0x002d3dcc));goto dispatch;
L_002d3dcc:
 STEP(UINT32_C(0x002d3dcc)); /* 01031825 or v1,t0,v1 */
 set(m,3u,lo(m,8u)|lo(m,3u));target=sx(UINT32_C(0x002d3dd0));goto dispatch;
L_002d3dd0:
 STEP(UINT32_C(0x002d3dd0)); /* 25e5be38 addiu a1,t7,-16840 */
 set(m,5u,sx((uint32_t)lo(m,15u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d3dd4));goto dispatch;
L_002d3dd4:
 STEP(UINT32_C(0x002d3dd4)); /* 36220001 ori v0,s1,0x1 */
 set(m,2u,lo(m,17u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d3dd8));goto dispatch;
L_002d3dd8:
 STEP(UINT32_C(0x002d3dd8)); /* 0003183c dsll32 v1,v1,0 */
 set(m,3u,lo(m,3u)<<32u);target=sx(UINT32_C(0x002d3ddc));goto dispatch;
L_002d3ddc:
 STEP(UINT32_C(0x002d3ddc)); /* 0003183f dsra32 v1,v1,0 */
 set(m,3u,(uint64_t)((int64_t)lo(m,3u)>>32u));target=sx(UINT32_C(0x002d3de0));goto dispatch;
L_002d3de0:
 STEP(UINT32_C(0x002d3de0)); /* 01273021 addu a2,t1,a3 */
 set(m,6u,sx((uint32_t)lo(m,9u)+(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x002d3de4));goto dispatch;
L_002d3de4:
 STEP(UINT32_C(0x002d3de4)); /* ae020004 sw v0,0x4(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3de8));goto dispatch;
L_002d3de8:
 STEP(UINT32_C(0x002d3de8)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d3dec));goto dispatch;
L_002d3dec:
 STEP(UINT32_C(0x002d3dec)); /* aca9000c sw t1,0xc(a1) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d3df0));goto dispatch;
L_002d3df0:
 STEP(UINT32_C(0x002d3df0)); /* aca90008 sw t1,0x8(a1) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3df4));goto dispatch;
L_002d3df4:
 STEP(UINT32_C(0x002d3df4)); /* ad230004 sw v1,0x4(t1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3df8));goto dispatch;
L_002d3df8:
 STEP(UINT32_C(0x002d3df8)); /* ad250008 sw a1,0x8(t1) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3dfc));goto dispatch;
L_002d3dfc:
 STEP(UINT32_C(0x002d3dfc)); /* acc70000 sw a3,0x0(a2) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d3e00));goto dispatch;
L_002d3e00:
 STEP(UINT32_C(0x002d3e00)); /* 10000138 beq zero,zero,002d42e4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3e04));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);target=sx(taken?UINT32_C(0x002d42e4):UINT32_C(0x002d3e08));goto dispatch;}
L_002d3e04:
 STEP(UINT32_C(0x002d3e04)); /* ad25000c sw a1,0xc(t1) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d3e08));goto dispatch;
L_002d3e08:
 STEP(UINT32_C(0x002d3e08)); /* ac84000c sw a0,0xc(a0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d3e0c));goto dispatch;
L_002d3e0c:
 STEP(UINT32_C(0x002d3e0c)); /* 05000008 regimm0 t0,002d3e30 */
 {int taken=((int64_t)lo(m,8u)<0);STEP(UINT32_C(0x002d3e10));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002d3e30):UINT32_C(0x002d3e14));goto dispatch;}
L_002d3e10:
 STEP(UINT32_C(0x002d3e10)); /* ac840008 sw a0,0x8(a0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3e14));goto dispatch;
L_002d3e14:
 STEP(UINT32_C(0x002d3e14)); /* 02061821 addu v1,s0,a2 */
 set(m,3u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d3e18));goto dispatch;
L_002d3e18:
 STEP(UINT32_C(0x002d3e18)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d3e1c));goto dispatch;
L_002d3e1c:
 STEP(UINT32_C(0x002d3e1c)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3e20));goto dispatch;
L_002d3e20:
 STEP(UINT32_C(0x002d3e20)); /* 34420001 ori v0,v0,0x1 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d3e24));goto dispatch;
L_002d3e24:
 STEP(UINT32_C(0x002d3e24)); /* 1000012f beq zero,zero,002d42e4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3e28));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d42e4):UINT32_C(0x002d3e2c));goto dispatch;}
L_002d3e28:
 STEP(UINT32_C(0x002d3e28)); /* ac620004 sw v0,0x4(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3e2c));goto dispatch;
L_002d3e2c:
 STEP(UINT32_C(0x002d3e2c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3e30));goto dispatch;
L_002d3e30:
 STEP(UINT32_C(0x002d3e30)); /* 2cc20200 sltiu v0,a2,512 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x200)));target=sx(UINT32_C(0x002d3e34));goto dispatch;
L_002d3e34:
 STEP(UINT32_C(0x002d3e34)); /* 10400012 beq v0,zero,002d3e80 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3e38));set(m,3u,sx((uint32_t)lo(m,6u)>>9u));target=sx(taken?UINT32_C(0x002d3e80):UINT32_C(0x002d3e3c));goto dispatch;}
L_002d3e38:
 STEP(UINT32_C(0x002d3e38)); /* 00061a42 srl v1,a2,9 */
 set(m,3u,sx((uint32_t)lo(m,6u)>>9u));target=sx(UINT32_C(0x002d3e3c));goto dispatch;
L_002d3e3c:
 STEP(UINT32_C(0x002d3e3c)); /* 000628c2 srl a1,a2,3 */
 set(m,5u,sx((uint32_t)lo(m,6u)>>3u));target=sx(UINT32_C(0x002d3e40));goto dispatch;
L_002d3e40:
 STEP(UINT32_C(0x002d3e40)); /* 2484fff8 addiu a0,a0,-8 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d3e44));goto dispatch;
L_002d3e44:
 STEP(UINT32_C(0x002d3e44)); /* 000518c0 sll v1,a1,3 */
 set(m,3u,sx((uint32_t)lo(m,5u)<<3u));target=sx(UINT32_C(0x002d3e48));goto dispatch;
L_002d3e48:
 STEP(UINT32_C(0x002d3e48)); /* 00052882 srl a1,a1,2 */
 set(m,5u,sx((uint32_t)lo(m,5u)>>2u));target=sx(UINT32_C(0x002d3e4c));goto dispatch;
L_002d3e4c:
 STEP(UINT32_C(0x002d3e4c)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d3e50));goto dispatch;
L_002d3e50:
 STEP(UINT32_C(0x002d3e50)); /* 00645821 addu t3,v1,a0 */
 set(m,11u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d3e54));goto dispatch;
L_002d3e54:
 STEP(UINT32_C(0x002d3e54)); /* 00a21014 UNKNOWN 00a21014 */
 set(m,2u,lo(m,2u)<<(lo(m,5u)&63u));target=sx(UINT32_C(0x002d3e58));goto dispatch;
L_002d3e58:
 STEP(UINT32_C(0x002d3e58)); /* 8c830004 lw v1,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d3e5c));goto dispatch;
L_002d3e5c:
 STEP(UINT32_C(0x002d3e5c)); /* 8d680008 lw t0,0x8(t3) */
 READ((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d3e60));goto dispatch;
L_002d3e60:
 STEP(UINT32_C(0x002d3e60)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d3e64));goto dispatch;
L_002d3e64:
 STEP(UINT32_C(0x002d3e64)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x002d3e68));goto dispatch;
L_002d3e68:
 STEP(UINT32_C(0x002d3e68)); /* 00621825 or v1,v1,v0 */
 set(m,3u,lo(m,3u)|lo(m,2u));target=sx(UINT32_C(0x002d3e6c));goto dispatch;
L_002d3e6c:
 STEP(UINT32_C(0x002d3e6c)); /* ae0b000c sw t3,0xc(s0) */
 value32=(uint32_t)lo(m,11u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d3e70));goto dispatch;
L_002d3e70:
 STEP(UINT32_C(0x002d3e70)); /* ae080008 sw t0,0x8(s0) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3e74));goto dispatch;
L_002d3e74:
 STEP(UINT32_C(0x002d3e74)); /* 1000003e beq zero,zero,002d3f70 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3e78));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d3f70):UINT32_C(0x002d3e7c));goto dispatch;}
L_002d3e78:
 STEP(UINT32_C(0x002d3e78)); /* ac830004 sw v1,0x4(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3e7c));goto dispatch;
L_002d3e7c:
 STEP(UINT32_C(0x002d3e7c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3e80));goto dispatch;
L_002d3e80:
 STEP(UINT32_C(0x002d3e80)); /* 10600019 beq v1,zero,002d3ee8 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002d3e84));set(m,5u,sx((uint32_t)lo(m,6u)>>3u));target=sx(taken?UINT32_C(0x002d3ee8):UINT32_C(0x002d3e88));goto dispatch;}
L_002d3e84:
 STEP(UINT32_C(0x002d3e84)); /* 000628c2 srl a1,a2,3 */
 set(m,5u,sx((uint32_t)lo(m,6u)>>3u));target=sx(UINT32_C(0x002d3e88));goto dispatch;
L_002d3e88:
 STEP(UINT32_C(0x002d3e88)); /* 2c620005 sltiu v0,v1,5 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x5)));target=sx(UINT32_C(0x002d3e8c));goto dispatch;
L_002d3e8c:
 STEP(UINT32_C(0x002d3e8c)); /* 10400004 beq v0,zero,002d3ea0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3e90));set(m,2u,(lo(m,3u)<UINT64_C(0x15)));target=sx(taken?UINT32_C(0x002d3ea0):UINT32_C(0x002d3e94));goto dispatch;}
L_002d3e90:
 STEP(UINT32_C(0x002d3e90)); /* 2c620015 sltiu v0,v1,21 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x15)));target=sx(UINT32_C(0x002d3e94));goto dispatch;
L_002d3e94:
 STEP(UINT32_C(0x002d3e94)); /* 00061182 srl v0,a2,6 */
 set(m,2u,sx((uint32_t)lo(m,6u)>>6u));target=sx(UINT32_C(0x002d3e98));goto dispatch;
L_002d3e98:
 STEP(UINT32_C(0x002d3e98)); /* 10000013 beq zero,zero,002d3ee8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3e9c));set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000038)));target=sx(taken?UINT32_C(0x002d3ee8):UINT32_C(0x002d3ea0));goto dispatch;}
L_002d3e9c:
 STEP(UINT32_C(0x002d3e9c)); /* 24450038 addiu a1,v0,56 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000038)));target=sx(UINT32_C(0x002d3ea0));goto dispatch;
L_002d3ea0:
 STEP(UINT32_C(0x002d3ea0)); /* 14400011 bne v0,zero,002d3ee8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d3ea4));set(m,5u,sx((uint32_t)lo(m,3u)+UINT32_C(0x0000005b)));target=sx(taken?UINT32_C(0x002d3ee8):UINT32_C(0x002d3ea8));goto dispatch;}
L_002d3ea4:
 STEP(UINT32_C(0x002d3ea4)); /* 2465005b addiu a1,v1,91 */
 set(m,5u,sx((uint32_t)lo(m,3u)+UINT32_C(0x0000005b)));target=sx(UINT32_C(0x002d3ea8));goto dispatch;
L_002d3ea8:
 STEP(UINT32_C(0x002d3ea8)); /* 2c620055 sltiu v0,v1,85 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x55)));target=sx(UINT32_C(0x002d3eac));goto dispatch;
L_002d3eac:
 STEP(UINT32_C(0x002d3eac)); /* 10400004 beq v0,zero,002d3ec0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3eb0));set(m,2u,(lo(m,3u)<UINT64_C(0x155)));target=sx(taken?UINT32_C(0x002d3ec0):UINT32_C(0x002d3eb4));goto dispatch;}
L_002d3eb0:
 STEP(UINT32_C(0x002d3eb0)); /* 2c620155 sltiu v0,v1,341 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x155)));target=sx(UINT32_C(0x002d3eb4));goto dispatch;
L_002d3eb4:
 STEP(UINT32_C(0x002d3eb4)); /* 00061302 srl v0,a2,12 */
 set(m,2u,sx((uint32_t)lo(m,6u)>>12u));target=sx(UINT32_C(0x002d3eb8));goto dispatch;
L_002d3eb8:
 STEP(UINT32_C(0x002d3eb8)); /* 1000000b beq zero,zero,002d3ee8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3ebc));set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000006e)));target=sx(taken?UINT32_C(0x002d3ee8):UINT32_C(0x002d3ec0));goto dispatch;}
L_002d3ebc:
 STEP(UINT32_C(0x002d3ebc)); /* 2445006e addiu a1,v0,110 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000006e)));target=sx(UINT32_C(0x002d3ec0));goto dispatch;
L_002d3ec0:
 STEP(UINT32_C(0x002d3ec0)); /* 10400005 beq v0,zero,002d3ed8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3ec4));set(m,2u,(lo(m,3u)<UINT64_C(0x555)));target=sx(taken?UINT32_C(0x002d3ed8):UINT32_C(0x002d3ec8));goto dispatch;}
L_002d3ec4:
 STEP(UINT32_C(0x002d3ec4)); /* 2c620555 sltiu v0,v1,1365 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x555)));target=sx(UINT32_C(0x002d3ec8));goto dispatch;
L_002d3ec8:
 STEP(UINT32_C(0x002d3ec8)); /* 000613c2 srl v0,a2,15 */
 set(m,2u,sx((uint32_t)lo(m,6u)>>15u));target=sx(UINT32_C(0x002d3ecc));goto dispatch;
L_002d3ecc:
 STEP(UINT32_C(0x002d3ecc)); /* 10000006 beq zero,zero,002d3ee8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3ed0));set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000077)));target=sx(taken?UINT32_C(0x002d3ee8):UINT32_C(0x002d3ed4));goto dispatch;}
L_002d3ed0:
 STEP(UINT32_C(0x002d3ed0)); /* 24450077 addiu a1,v0,119 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000077)));target=sx(UINT32_C(0x002d3ed4));goto dispatch;
L_002d3ed4:
 STEP(UINT32_C(0x002d3ed4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3ed8));goto dispatch;
L_002d3ed8:
 STEP(UINT32_C(0x002d3ed8)); /* 50400003 beql v0,zero,002d3ee8 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d3edc));set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007e)));target=sx(UINT32_C(0x002d3ee8));}else target=sx(UINT32_C(0x002d3ee0));goto dispatch;
L_002d3edc:
 STEP(UINT32_C(0x002d3edc)); /* 2405007e addiu a1,zero,126 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007e)));target=sx(UINT32_C(0x002d3ee0));goto dispatch;
L_002d3ee0:
 STEP(UINT32_C(0x002d3ee0)); /* 00061482 srl v0,a2,18 */
 set(m,2u,sx((uint32_t)lo(m,6u)>>18u));target=sx(UINT32_C(0x002d3ee4));goto dispatch;
L_002d3ee4:
 STEP(UINT32_C(0x002d3ee4)); /* 2445007c addiu a1,v0,124 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000007c)));target=sx(UINT32_C(0x002d3ee8));goto dispatch;
L_002d3ee8:
 STEP(UINT32_C(0x002d3ee8)); /* 25e2be38 addiu v0,t7,-16840 */
 set(m,2u,sx((uint32_t)lo(m,15u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d3eec));goto dispatch;
L_002d3eec:
 STEP(UINT32_C(0x002d3eec)); /* 000518c0 sll v1,a1,3 */
 set(m,3u,sx((uint32_t)lo(m,5u)<<3u));target=sx(UINT32_C(0x002d3ef0));goto dispatch;
L_002d3ef0:
 STEP(UINT32_C(0x002d3ef0)); /* 2447fff8 addiu a3,v0,-8 */
 set(m,7u,sx((uint32_t)lo(m,2u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d3ef4));goto dispatch;
L_002d3ef4:
 STEP(UINT32_C(0x002d3ef4)); /* 00675821 addu t3,v1,a3 */
 set(m,11u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x002d3ef8));goto dispatch;
L_002d3ef8:
 STEP(UINT32_C(0x002d3ef8)); /* 8d680008 lw t0,0x8(t3) */
 READ((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d3efc));goto dispatch;
L_002d3efc:
 STEP(UINT32_C(0x002d3efc)); /* 550b000e bnel t0,t3,002d3f38 */
 if(lo(m,8u)!=lo(m,11u)){STEP(UINT32_C(0x002d3f00));READ((uint32_t)lo(m,8u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3f38));}else target=sx(UINT32_C(0x002d3f04));goto dispatch;
L_002d3f00:
 STEP(UINT32_C(0x002d3f00)); /* 8d020004 lw v0,0x4(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3f04));goto dispatch;
L_002d3f04:
 STEP(UINT32_C(0x002d3f04)); /* 24a40003 addiu a0,a1,3 */
 set(m,4u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002d3f08));goto dispatch;
L_002d3f08:
 STEP(UINT32_C(0x002d3f08)); /* 28a30000 slti v1,a1,0 */
 set(m,3u,((int64_t)lo(m,5u)<INT64_C(0)));target=sx(UINT32_C(0x002d3f0c));goto dispatch;
L_002d3f0c:
 STEP(UINT32_C(0x002d3f0c)); /* 0083280b movn a1,a0,v1 */
 if(lo(m,3u)!=0u)set(m,5u,lo(m,4u));target=sx(UINT32_C(0x002d3f10));goto dispatch;
L_002d3f10:
 STEP(UINT32_C(0x002d3f10)); /* 8ce30004 lw v1,0x4(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d3f14));goto dispatch;
L_002d3f14:
 STEP(UINT32_C(0x002d3f14)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d3f18));goto dispatch;
L_002d3f18:
 STEP(UINT32_C(0x002d3f18)); /* 00052083 sra a0,a1,2 */
 set(m,4u,sx((uint32_t)((int32_t)lo(m,5u)>>2u)));target=sx(UINT32_C(0x002d3f1c));goto dispatch;
L_002d3f1c:
 STEP(UINT32_C(0x002d3f1c)); /* 00821014 UNKNOWN 00821014 */
 set(m,2u,lo(m,2u)<<(lo(m,4u)&63u));target=sx(UINT32_C(0x002d3f20));goto dispatch;
L_002d3f20:
 STEP(UINT32_C(0x002d3f20)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d3f24));goto dispatch;
L_002d3f24:
 STEP(UINT32_C(0x002d3f24)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x002d3f28));goto dispatch;
L_002d3f28:
 STEP(UINT32_C(0x002d3f28)); /* 00621825 or v1,v1,v0 */
 set(m,3u,lo(m,3u)|lo(m,2u));target=sx(UINT32_C(0x002d3f2c));goto dispatch;
L_002d3f2c:
 STEP(UINT32_C(0x002d3f2c)); /* 1000000e beq zero,zero,002d3f68 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3f30));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d3f68):UINT32_C(0x002d3f34));goto dispatch;}
L_002d3f30:
 STEP(UINT32_C(0x002d3f30)); /* ace30004 sw v1,0x4(a3) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3f34));goto dispatch;
L_002d3f34:
 STEP(UINT32_C(0x002d3f34)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3f38));goto dispatch;
L_002d3f38:
 STEP(UINT32_C(0x002d3f38)); /* 10000004 beq zero,zero,002d3f4c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3f3c));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(taken?UINT32_C(0x002d3f4c):UINT32_C(0x002d3f40));goto dispatch;}
L_002d3f3c:
 STEP(UINT32_C(0x002d3f3c)); /* 2403fffc addiu v1,zero,-4 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d3f40));goto dispatch;
L_002d3f40:
 STEP(UINT32_C(0x002d3f40)); /* 510b0009 beql t0,t3,002d3f68 */
 if(lo(m,8u)==lo(m,11u)){STEP(UINT32_C(0x002d3f44));READ((uint32_t)lo(m,8u)+UINT32_C(0x0000000c),&value32,4u);set(m,11u,sx(value32));target=sx(UINT32_C(0x002d3f68));}else target=sx(UINT32_C(0x002d3f48));goto dispatch;
L_002d3f44:
 STEP(UINT32_C(0x002d3f44)); /* 8d0b000c lw t3,0xc(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x0000000c),&value32,4u);set(m,11u,sx(value32));target=sx(UINT32_C(0x002d3f48));goto dispatch;
L_002d3f48:
 STEP(UINT32_C(0x002d3f48)); /* 8d020004 lw v0,0x4(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3f4c));goto dispatch;
L_002d3f4c:
 STEP(UINT32_C(0x002d3f4c)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d3f50));goto dispatch;
L_002d3f50:
 STEP(UINT32_C(0x002d3f50)); /* 00c2102b sltu v0,a2,v0 */
 set(m,2u,lo(m,6u)<lo(m,2u));target=sx(UINT32_C(0x002d3f54));goto dispatch;
L_002d3f54:
 STEP(UINT32_C(0x002d3f54)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3f58));goto dispatch;
L_002d3f58:
 STEP(UINT32_C(0x002d3f58)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3f5c));goto dispatch;
L_002d3f5c:
 STEP(UINT32_C(0x002d3f5c)); /* 5440fff8 bnel v0,zero,002d3f40 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d3f60));READ((uint32_t)lo(m,8u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d3f40));}else target=sx(UINT32_C(0x002d3f64));goto dispatch;
L_002d3f60:
 STEP(UINT32_C(0x002d3f60)); /* 8d080008 lw t0,0x8(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d3f64));goto dispatch;
L_002d3f64:
 STEP(UINT32_C(0x002d3f64)); /* 8d0b000c lw t3,0xc(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x0000000c),&value32,4u);set(m,11u,sx(value32));target=sx(UINT32_C(0x002d3f68));goto dispatch;
L_002d3f68:
 STEP(UINT32_C(0x002d3f68)); /* ae0b000c sw t3,0xc(s0) */
 value32=(uint32_t)lo(m,11u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d3f6c));goto dispatch;
L_002d3f6c:
 STEP(UINT32_C(0x002d3f6c)); /* ae080008 sw t0,0x8(s0) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3f70));goto dispatch;
L_002d3f70:
 STEP(UINT32_C(0x002d3f70)); /* ad700008 sw s0,0x8(t3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3f74));goto dispatch;
L_002d3f74:
 STEP(UINT32_C(0x002d3f74)); /* ad10000c sw s0,0xc(t0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d3f78));goto dispatch;
L_002d3f78:
 STEP(UINT32_C(0x002d3f78)); /* 29420000 slti v0,t2,0 */
 set(m,2u,((int64_t)lo(m,10u)<INT64_C(0)));target=sx(UINT32_C(0x002d3f7c));goto dispatch;
L_002d3f7c:
 STEP(UINT32_C(0x002d3f7c)); /* 25450003 addiu a1,t2,3 */
 set(m,5u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002d3f80));goto dispatch;
L_002d3f80:
 STEP(UINT32_C(0x002d3f80)); /* 0140202d daddu a0,t2,zero */
 set(m,4u,lo(m,10u)+lo(m,0u));target=sx(UINT32_C(0x002d3f84));goto dispatch;
L_002d3f84:
 STEP(UINT32_C(0x002d3f84)); /* 3c140053 lui s4,zero,0x53 */
 set(m,20u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3f88));goto dispatch;
L_002d3f88:
 STEP(UINT32_C(0x002d3f88)); /* 00a2200b movn a0,a1,v0 */
 if(lo(m,2u)!=0u)set(m,4u,lo(m,5u));target=sx(UINT32_C(0x002d3f8c));goto dispatch;
L_002d3f8c:
 STEP(UINT32_C(0x002d3f8c)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d3f90));goto dispatch;
L_002d3f90:
 STEP(UINT32_C(0x002d3f90)); /* 2683be30 addiu v1,s4,-16848 */
 set(m,3u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d3f94));goto dispatch;
L_002d3f94:
 STEP(UINT32_C(0x002d3f94)); /* 00042083 sra a0,a0,2 */
 set(m,4u,sx((uint32_t)((int32_t)lo(m,4u)>>2u)));target=sx(UINT32_C(0x002d3f98));goto dispatch;
L_002d3f98:
 STEP(UINT32_C(0x002d3f98)); /* 9c660004 lwu a2,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,(uint64_t)value32);target=sx(UINT32_C(0x002d3f9c));goto dispatch;
L_002d3f9c:
 STEP(UINT32_C(0x002d3f9c)); /* 00824814 UNKNOWN 00824814 */
 set(m,9u,lo(m,2u)<<(lo(m,4u)&63u));target=sx(UINT32_C(0x002d3fa0));goto dispatch;
L_002d3fa0:
 STEP(UINT32_C(0x002d3fa0)); /* 00c9182b sltu v1,a2,t1 */
 set(m,3u,lo(m,6u)<lo(m,9u));target=sx(UINT32_C(0x002d3fa4));goto dispatch;
L_002d3fa4:
 STEP(UINT32_C(0x002d3fa4)); /* 54600061 bnel v1,zero,002d412c */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x002d3fa8));set(m,4u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d412c));}else target=sx(UINT32_C(0x002d3fac));goto dispatch;
L_002d3fa8:
 STEP(UINT32_C(0x002d3fa8)); /* 2684be30 addiu a0,s4,-16848 */
 set(m,4u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d3fac));goto dispatch;
L_002d3fac:
 STEP(UINT32_C(0x002d3fac)); /* 01261024 and v0,t1,a2 */
 set(m,2u,lo(m,9u)&lo(m,6u));target=sx(UINT32_C(0x002d3fb0));goto dispatch;
L_002d3fb0:
 STEP(UINT32_C(0x002d3fb0)); /* 14400011 bne v0,zero,002d3ff8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d3fb4));set(m,2u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002d3ff8):UINT32_C(0x002d3fb8));goto dispatch;}
L_002d3fb4:
 STEP(UINT32_C(0x002d3fb4)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3fb8));goto dispatch;
L_002d3fb8:
 STEP(UINT32_C(0x002d3fb8)); /* 2402fffc addiu v0,zero,-4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d3fbc));goto dispatch;
L_002d3fbc:
 STEP(UINT32_C(0x002d3fbc)); /* 00094878 dsll t1,t1,1 */
 set(m,9u,lo(m,9u)<<1u);target=sx(UINT32_C(0x002d3fc0));goto dispatch;
L_002d3fc0:
 STEP(UINT32_C(0x002d3fc0)); /* 01421024 and v0,t2,v0 */
 set(m,2u,lo(m,10u)&lo(m,2u));target=sx(UINT32_C(0x002d3fc4));goto dispatch;
L_002d3fc4:
 STEP(UINT32_C(0x002d3fc4)); /* 01261824 and v1,t1,a2 */
 set(m,3u,lo(m,9u)&lo(m,6u));target=sx(UINT32_C(0x002d3fc8));goto dispatch;
L_002d3fc8:
 STEP(UINT32_C(0x002d3fc8)); /* 1460000a bne v1,zero,002d3ff4 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002d3fcc));set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000004)));target=sx(taken?UINT32_C(0x002d3ff4):UINT32_C(0x002d3fd0));goto dispatch;}
L_002d3fcc:
 STEP(UINT32_C(0x002d3fcc)); /* 244a0004 addiu t2,v0,4 */
 set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002d3fd0));goto dispatch;
L_002d3fd0:
 STEP(UINT32_C(0x002d3fd0)); /* 00c0182d daddu v1,a2,zero */
 set(m,3u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d3fd4));goto dispatch;
L_002d3fd4:
 STEP(UINT32_C(0x002d3fd4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3fd8));goto dispatch;
L_002d3fd8:
 STEP(UINT32_C(0x002d3fd8)); /* 00094878 dsll t1,t1,1 */
 set(m,9u,lo(m,9u)<<1u);target=sx(UINT32_C(0x002d3fdc));goto dispatch;
L_002d3fdc:
 STEP(UINT32_C(0x002d3fdc)); /* 01231024 and v0,t1,v1 */
 set(m,2u,lo(m,9u)&lo(m,3u));target=sx(UINT32_C(0x002d3fe0));goto dispatch;
L_002d3fe0:
 STEP(UINT32_C(0x002d3fe0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3fe4));goto dispatch;
L_002d3fe4:
 STEP(UINT32_C(0x002d3fe4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3fe8));goto dispatch;
L_002d3fe8:
 STEP(UINT32_C(0x002d3fe8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3fec));goto dispatch;
L_002d3fec:
 STEP(UINT32_C(0x002d3fec)); /* 1040fffa beq v0,zero,002d3fd8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3ff0));set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000004)));target=sx(taken?UINT32_C(0x002d3fd8):UINT32_C(0x002d3ff4));goto dispatch;}
L_002d3ff0:
 STEP(UINT32_C(0x002d3ff0)); /* 254a0004 addiu t2,t2,4 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002d3ff4));goto dispatch;
L_002d3ff4:
 STEP(UINT32_C(0x002d3ff4)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3ff8));goto dispatch;
L_002d3ff8:
 STEP(UINT32_C(0x002d3ff8)); /* 244dbe30 addiu t5,v0,-16848 */
 set(m,13u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d3ffc));goto dispatch;
L_002d3ffc:
 STEP(UINT32_C(0x002d3ffc)); /* 0040702d daddu t6,v0,zero */
 set(m,14u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d4000));goto dispatch;
L_002d4000:
 STEP(UINT32_C(0x002d4000)); /* 01a0902d daddu s2,t5,zero */
 set(m,18u,lo(m,13u)+lo(m,0u));target=sx(UINT32_C(0x002d4004));goto dispatch;
L_002d4004:
 STEP(UINT32_C(0x002d4004)); /* 000a10c0 sll v0,t2,3 */
 set(m,2u,sx((uint32_t)lo(m,10u)<<3u));target=sx(UINT32_C(0x002d4008));goto dispatch;
L_002d4008:
 STEP(UINT32_C(0x002d4008)); /* 0140582d daddu t3,t2,zero */
 set(m,11u,lo(m,10u)+lo(m,0u));target=sx(UINT32_C(0x002d400c));goto dispatch;
L_002d400c:
 STEP(UINT32_C(0x002d400c)); /* 004d2021 addu a0,v0,t5 */
 set(m,4u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,13u)));target=sx(UINT32_C(0x002d4010));goto dispatch;
L_002d4010:
 STEP(UINT32_C(0x002d4010)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d4014));goto dispatch;
L_002d4014:
 STEP(UINT32_C(0x002d4014)); /* 8cb0000c lw s0,0xc(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d4018));goto dispatch;
L_002d4018:
 STEP(UINT32_C(0x002d4018)); /* 12050016 beq s0,a1,002d4074 */
 {int taken=(lo(m,16u)==lo(m,5u));STEP(UINT32_C(0x002d401c));set(m,2u,((int64_t)lo(m,10u)<INT64_C(63)));target=sx(taken?UINT32_C(0x002d4074):UINT32_C(0x002d4020));goto dispatch;}
L_002d401c:
 STEP(UINT32_C(0x002d401c)); /* 2942003f slti v0,t2,63 */
 set(m,2u,((int64_t)lo(m,10u)<INT64_C(63)));target=sx(UINT32_C(0x002d4020));goto dispatch;
L_002d4020:
 STEP(UINT32_C(0x002d4020)); /* 240cfffc addiu t4,zero,-4 */
 set(m,12u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d4024));goto dispatch;
L_002d4024:
 STEP(UINT32_C(0x002d4024)); /* 8e020004 lw v0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4028));goto dispatch;
L_002d4028:
 STEP(UINT32_C(0x002d4028)); /* 004c3024 and a2,v0,t4 */
 set(m,6u,lo(m,2u)&lo(m,12u));target=sx(UINT32_C(0x002d402c));goto dispatch;
L_002d402c:
 STEP(UINT32_C(0x002d402c)); /* 02261823 subu v1,s1,a2 */
 set(m,3u,sx((uint32_t)lo(m,17u)-(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d4030));goto dispatch;
L_002d4030:
 STEP(UINT32_C(0x002d4030)); /* 00d11023 subu v0,a2,s1 */
 set(m,2u,sx((uint32_t)lo(m,6u)-(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d4034));goto dispatch;
L_002d4034:
 STEP(UINT32_C(0x002d4034)); /* 0003183c dsll32 v1,v1,0 */
 set(m,3u,lo(m,3u)<<32u);target=sx(UINT32_C(0x002d4038));goto dispatch;
L_002d4038:
 STEP(UINT32_C(0x002d4038)); /* 0002383c dsll32 a3,v0,0 */
 set(m,7u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d403c));goto dispatch;
L_002d403c:
 STEP(UINT32_C(0x002d403c)); /* 0003183e dsrl32 v1,v1,0 */
 set(m,3u,lo(m,3u)>>32u);target=sx(UINT32_C(0x002d4040));goto dispatch;
L_002d4040:
 STEP(UINT32_C(0x002d4040)); /* 00d1102b sltu v0,a2,s1 */
 set(m,2u,lo(m,6u)<lo(m,17u));target=sx(UINT32_C(0x002d4044));goto dispatch;
L_002d4044:
 STEP(UINT32_C(0x002d4044)); /* 14400002 bne v0,zero,002d4050 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d4048));set(m,8u,lo(m,0u)-lo(m,3u));target=sx(taken?UINT32_C(0x002d4050):UINT32_C(0x002d404c));goto dispatch;}
L_002d4048:
 STEP(UINT32_C(0x002d4048)); /* 0003402f dsubu t0,zero,v1 */
 set(m,8u,lo(m,0u)-lo(m,3u));target=sx(UINT32_C(0x002d404c));goto dispatch;
L_002d404c:
 STEP(UINT32_C(0x002d404c)); /* 0007403e dsrl32 t0,a3,0 */
 set(m,8u,lo(m,7u)>>32u);target=sx(UINT32_C(0x002d4050));goto dispatch;
L_002d4050:
 STEP(UINT32_C(0x002d4050)); /* 29020010 slti v0,t0,16 */
 set(m,2u,((int64_t)lo(m,8u)<INT64_C(16)));target=sx(UINT32_C(0x002d4054));goto dispatch;
L_002d4054:
 STEP(UINT32_C(0x002d4054)); /* 50400078 beql v0,zero,002d4238 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d4058));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4238));}else target=sx(UINT32_C(0x002d405c));goto dispatch;
L_002d4058:
 STEP(UINT32_C(0x002d4058)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d405c));goto dispatch;
L_002d405c:
 STEP(UINT32_C(0x002d405c)); /* 0503008c regimm3 t0,002d4290 */
 if((int64_t)lo(m,8u)>=0){STEP(UINT32_C(0x002d4060));set(m,3u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d4290));}else target=sx(UINT32_C(0x002d4064));goto dispatch;
L_002d4060:
 STEP(UINT32_C(0x002d4060)); /* 02061821 addu v1,s0,a2 */
 set(m,3u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d4064));goto dispatch;
L_002d4064:
 STEP(UINT32_C(0x002d4064)); /* 8e10000c lw s0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d4068));goto dispatch;
L_002d4068:
 STEP(UINT32_C(0x002d4068)); /* 5605ffef bnel s0,a1,002d4028 */
 if(lo(m,16u)!=lo(m,5u)){STEP(UINT32_C(0x002d406c));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4028));}else target=sx(UINT32_C(0x002d4070));goto dispatch;
L_002d406c:
 STEP(UINT32_C(0x002d406c)); /* 8e020004 lw v0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4070));goto dispatch;
L_002d4070:
 STEP(UINT32_C(0x002d4070)); /* 2942003f slti v0,t2,63 */
 set(m,2u,((int64_t)lo(m,10u)<INT64_C(63)));target=sx(UINT32_C(0x002d4074));goto dispatch;
L_002d4074:
 STEP(UINT32_C(0x002d4074)); /* 10400003 beq v0,zero,002d4084 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d4078));set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002d4084):UINT32_C(0x002d407c));goto dispatch;}
L_002d4078:
 STEP(UINT32_C(0x002d4078)); /* 24a50008 addiu a1,a1,8 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d407c));goto dispatch;
L_002d407c:
 STEP(UINT32_C(0x002d407c)); /* 24a50008 addiu a1,a1,8 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d4080));goto dispatch;
L_002d4080:
 STEP(UINT32_C(0x002d4080)); /* 254a0001 addiu t2,t2,1 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4084));goto dispatch;
L_002d4084:
 STEP(UINT32_C(0x002d4084)); /* 254a0001 addiu t2,t2,1 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4088));goto dispatch;
L_002d4088:
 STEP(UINT32_C(0x002d4088)); /* 31420003 andi v0,t2,0x3 */
 set(m,2u,lo(m,10u) & UINT64_C(0x3));target=sx(UINT32_C(0x002d408c));goto dispatch;
L_002d408c:
 STEP(UINT32_C(0x002d408c)); /* 5440ffe2 bnel v0,zero,002d4018 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d4090));READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d4018));}else target=sx(UINT32_C(0x002d4094));goto dispatch;
L_002d4090:
 STEP(UINT32_C(0x002d4090)); /* 8cb0000c lw s0,0xc(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d4094));goto dispatch;
L_002d4094:
 STEP(UINT32_C(0x002d4094)); /* 0009103c dsll32 v0,t1,0 */
 set(m,2u,lo(m,9u)<<32u);target=sx(UINT32_C(0x002d4098));goto dispatch;
L_002d4098:
 STEP(UINT32_C(0x002d4098)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x002d409c));goto dispatch;
L_002d409c:
 STEP(UINT32_C(0x002d409c)); /* 25c5be30 addiu a1,t6,-16848 */
 set(m,5u,sx((uint32_t)lo(m,14u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d40a0));goto dispatch;
L_002d40a0:
 STEP(UINT32_C(0x002d40a0)); /* 00021827 nor v1,zero,v0 */
 set(m,3u,~(lo(m,0u)|lo(m,2u)));target=sx(UINT32_C(0x002d40a4));goto dispatch;
L_002d40a4:
 STEP(UINT32_C(0x002d40a4)); /* 31620003 andi v0,t3,0x3 */
 set(m,2u,lo(m,11u) & UINT64_C(0x3));target=sx(UINT32_C(0x002d40a8));goto dispatch;
L_002d40a8:
 STEP(UINT32_C(0x002d40a8)); /* 14400005 bne v0,zero,002d40c0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d40ac));set(m,11u,sx((uint32_t)lo(m,11u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002d40c0):UINT32_C(0x002d40b0));goto dispatch;}
L_002d40ac:
 STEP(UINT32_C(0x002d40ac)); /* 256bffff addiu t3,t3,-1 */
 set(m,11u,sx((uint32_t)lo(m,11u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d40b0));goto dispatch;
L_002d40b0:
 STEP(UINT32_C(0x002d40b0)); /* 8ca20004 lw v0,0x4(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d40b4));goto dispatch;
L_002d40b4:
 STEP(UINT32_C(0x002d40b4)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d40b8));goto dispatch;
L_002d40b8:
 STEP(UINT32_C(0x002d40b8)); /* 10000006 beq zero,zero,002d40d4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d40bc));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d40d4):UINT32_C(0x002d40c0));goto dispatch;}
L_002d40bc:
 STEP(UINT32_C(0x002d40bc)); /* aca20004 sw v0,0x4(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d40c0));goto dispatch;
L_002d40c0:
 STEP(UINT32_C(0x002d40c0)); /* 2484fff8 addiu a0,a0,-8 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d40c4));goto dispatch;
L_002d40c4:
 STEP(UINT32_C(0x002d40c4)); /* 8c820008 lw v0,0x8(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d40c8));goto dispatch;
L_002d40c8:
 STEP(UINT32_C(0x002d40c8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d40cc));goto dispatch;
L_002d40cc:
 STEP(UINT32_C(0x002d40cc)); /* 1044fff6 beq v0,a0,002d40a8 */
 {int taken=(lo(m,2u)==lo(m,4u));STEP(UINT32_C(0x002d40d0));set(m,2u,lo(m,11u) & UINT64_C(0x3));target=sx(taken?UINT32_C(0x002d40a8):UINT32_C(0x002d40d4));goto dispatch;}
L_002d40d0:
 STEP(UINT32_C(0x002d40d0)); /* 31620003 andi v0,t3,0x3 */
 set(m,2u,lo(m,11u) & UINT64_C(0x3));target=sx(UINT32_C(0x002d40d4));goto dispatch;
L_002d40d4:
 STEP(UINT32_C(0x002d40d4)); /* 9da30004 lwu v1,0x4(t5) */
 READ((uint32_t)lo(m,13u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,(uint64_t)value32);target=sx(UINT32_C(0x002d40d8));goto dispatch;
L_002d40d8:
 STEP(UINT32_C(0x002d40d8)); /* 00094878 dsll t1,t1,1 */
 set(m,9u,lo(m,9u)<<1u);target=sx(UINT32_C(0x002d40dc));goto dispatch;
L_002d40dc:
 STEP(UINT32_C(0x002d40dc)); /* 0069102b sltu v0,v1,t1 */
 set(m,2u,lo(m,3u)<lo(m,9u));target=sx(UINT32_C(0x002d40e0));goto dispatch;
L_002d40e0:
 STEP(UINT32_C(0x002d40e0)); /* 54400012 bnel v0,zero,002d412c */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d40e4));set(m,4u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d412c));}else target=sx(UINT32_C(0x002d40e8));goto dispatch;
L_002d40e4:
 STEP(UINT32_C(0x002d40e4)); /* 2684be30 addiu a0,s4,-16848 */
 set(m,4u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d40e8));goto dispatch;
L_002d40e8:
 STEP(UINT32_C(0x002d40e8)); /* 1120000f beq t1,zero,002d4128 */
 {int taken=(lo(m,9u)==lo(m,0u));STEP(UINT32_C(0x002d40ec));set(m,2u,lo(m,9u)&lo(m,3u));target=sx(taken?UINT32_C(0x002d4128):UINT32_C(0x002d40f0));goto dispatch;}
L_002d40ec:
 STEP(UINT32_C(0x002d40ec)); /* 01231024 and v0,t1,v1 */
 set(m,2u,lo(m,9u)&lo(m,3u));target=sx(UINT32_C(0x002d40f0));goto dispatch;
L_002d40f0:
 STEP(UINT32_C(0x002d40f0)); /* 1440ffc5 bne v0,zero,002d4008 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d40f4));set(m,2u,sx((uint32_t)lo(m,10u)<<3u));target=sx(taken?UINT32_C(0x002d4008):UINT32_C(0x002d40f8));goto dispatch;}
L_002d40f4:
 STEP(UINT32_C(0x002d40f4)); /* 000a10c0 sll v0,t2,3 */
 set(m,2u,sx((uint32_t)lo(m,10u)<<3u));target=sx(UINT32_C(0x002d40f8));goto dispatch;
L_002d40f8:
 STEP(UINT32_C(0x002d40f8)); /* 9e430004 lwu v1,0x4(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,(uint64_t)value32);target=sx(UINT32_C(0x002d40fc));goto dispatch;
L_002d40fc:
 STEP(UINT32_C(0x002d40fc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4100));goto dispatch;
L_002d4100:
 STEP(UINT32_C(0x002d4100)); /* 00094878 dsll t1,t1,1 */
 set(m,9u,lo(m,9u)<<1u);target=sx(UINT32_C(0x002d4104));goto dispatch;
L_002d4104:
 STEP(UINT32_C(0x002d4104)); /* 01231024 and v0,t1,v1 */
 set(m,2u,lo(m,9u)&lo(m,3u));target=sx(UINT32_C(0x002d4108));goto dispatch;
L_002d4108:
 STEP(UINT32_C(0x002d4108)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d410c));goto dispatch;
L_002d410c:
 STEP(UINT32_C(0x002d410c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4110));goto dispatch;
L_002d4110:
 STEP(UINT32_C(0x002d4110)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4114));goto dispatch;
L_002d4114:
 STEP(UINT32_C(0x002d4114)); /* 1040fffa beq v0,zero,002d4100 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d4118));set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000004)));target=sx(taken?UINT32_C(0x002d4100):UINT32_C(0x002d411c));goto dispatch;}
L_002d4118:
 STEP(UINT32_C(0x002d4118)); /* 254a0004 addiu t2,t2,4 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002d411c));goto dispatch;
L_002d411c:
 STEP(UINT32_C(0x002d411c)); /* 1000ffba beq zero,zero,002d4008 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d4120));set(m,2u,sx((uint32_t)lo(m,10u)<<3u));target=sx(taken?UINT32_C(0x002d4008):UINT32_C(0x002d4124));goto dispatch;}
L_002d4120:
 STEP(UINT32_C(0x002d4120)); /* 000a10c0 sll v0,t2,3 */
 set(m,2u,sx((uint32_t)lo(m,10u)<<3u));target=sx(UINT32_C(0x002d4124));goto dispatch;
L_002d4124:
 STEP(UINT32_C(0x002d4124)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4128));goto dispatch;
L_002d4128:
 STEP(UINT32_C(0x002d4128)); /* 2684be30 addiu a0,s4,-16848 */
 set(m,4u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d412c));goto dispatch;
L_002d412c:
 STEP(UINT32_C(0x002d412c)); /* 2405fffc addiu a1,zero,-4 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d4130));goto dispatch;
L_002d4130:
 STEP(UINT32_C(0x002d4130)); /* 8c820008 lw v0,0x8(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4134));goto dispatch;
L_002d4134:
 STEP(UINT32_C(0x002d4134)); /* 8c430004 lw v1,0x4(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d4138));goto dispatch;
L_002d4138:
 STEP(UINT32_C(0x002d4138)); /* 00651824 and v1,v1,a1 */
 set(m,3u,lo(m,3u)&lo(m,5u));target=sx(UINT32_C(0x002d413c));goto dispatch;
L_002d413c:
 STEP(UINT32_C(0x002d413c)); /* 0071102b sltu v0,v1,s1 */
 set(m,2u,lo(m,3u)<lo(m,17u));target=sx(UINT32_C(0x002d4140));goto dispatch;
L_002d4140:
 STEP(UINT32_C(0x002d4140)); /* 10400007 beq v0,zero,002d4160 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d4144));set(m,2u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,17u)));target=sx(taken?UINT32_C(0x002d4160):UINT32_C(0x002d4148));goto dispatch;}
L_002d4144:
 STEP(UINT32_C(0x002d4144)); /* 00711023 subu v0,v1,s1 */
 set(m,2u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d4148));goto dispatch;
L_002d4148:
 STEP(UINT32_C(0x002d4148)); /* 02231023 subu v0,s1,v1 */
 set(m,2u,sx((uint32_t)lo(m,17u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d414c));goto dispatch;
L_002d414c:
 STEP(UINT32_C(0x002d414c)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d4150));goto dispatch;
L_002d4150:
 STEP(UINT32_C(0x002d4150)); /* 0002103e dsrl32 v0,v0,0 */
 set(m,2u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d4154));goto dispatch;
L_002d4154:
 STEP(UINT32_C(0x002d4154)); /* 10000004 beq zero,zero,002d4168 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d4158));set(m,8u,lo(m,0u)-lo(m,2u));target=sx(taken?UINT32_C(0x002d4168):UINT32_C(0x002d415c));goto dispatch;}
L_002d4158:
 STEP(UINT32_C(0x002d4158)); /* 0002402f dsubu t0,zero,v0 */
 set(m,8u,lo(m,0u)-lo(m,2u));target=sx(UINT32_C(0x002d415c));goto dispatch;
L_002d415c:
 STEP(UINT32_C(0x002d415c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4160));goto dispatch;
L_002d4160:
 STEP(UINT32_C(0x002d4160)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d4164));goto dispatch;
L_002d4164:
 STEP(UINT32_C(0x002d4164)); /* 0002403e dsrl32 t0,v0,0 */
 set(m,8u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d4168));goto dispatch;
L_002d4168:
 STEP(UINT32_C(0x002d4168)); /* 2690be30 addiu s0,s4,-16848 */
 set(m,16u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d416c));goto dispatch;
L_002d416c:
 STEP(UINT32_C(0x002d416c)); /* 2412fffc addiu s2,zero,-4 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d4170));goto dispatch;
L_002d4170:
 STEP(UINT32_C(0x002d4170)); /* 8e030008 lw v1,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d4174));goto dispatch;
L_002d4174:
 STEP(UINT32_C(0x002d4174)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4178));goto dispatch;
L_002d4178:
 STEP(UINT32_C(0x002d4178)); /* 00521024 and v0,v0,s2 */
 set(m,2u,lo(m,2u)&lo(m,18u));target=sx(UINT32_C(0x002d417c));goto dispatch;
L_002d417c:
 STEP(UINT32_C(0x002d417c)); /* 0051102b sltu v0,v0,s1 */
 set(m,2u,lo(m,2u)<lo(m,17u));target=sx(UINT32_C(0x002d4180));goto dispatch;
L_002d4180:
 STEP(UINT32_C(0x002d4180)); /* 14400005 bne v0,zero,002d4198 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d4184));set(m,4u,lo(m,19u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d4198):UINT32_C(0x002d4188));goto dispatch;}
L_002d4184:
 STEP(UINT32_C(0x002d4184)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d4188));goto dispatch;
L_002d4188:
 STEP(UINT32_C(0x002d4188)); /* 29020010 slti v0,t0,16 */
 set(m,2u,((int64_t)lo(m,8u)<INT64_C(16)));target=sx(UINT32_C(0x002d418c));goto dispatch;
L_002d418c:
 STEP(UINT32_C(0x002d418c)); /* 1040004a beq v0,zero,002d42b8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d4190));set(m,6u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(taken?UINT32_C(0x002d42b8):UINT32_C(0x002d4194));goto dispatch;}
L_002d4190:
 STEP(UINT32_C(0x002d4190)); /* 2686be30 addiu a2,s4,-16848 */
 set(m,6u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d4194));goto dispatch;
L_002d4194:
 STEP(UINT32_C(0x002d4194)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d4198));goto dispatch;
L_002d4198:
 STEP(UINT32_C(0x002d4198)); /* 0c0b4e64 jal 002d3990 */
 set(m,31u,UINT64_C(0x002d41a0));STEP(UINT32_C(0x002d419c));set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d3990));goto dispatch;
L_002d419c:
 STEP(UINT32_C(0x002d419c)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d41a0));goto dispatch;
L_002d41a0:
 STEP(UINT32_C(0x002d41a0)); /* 8e020008 lw v0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d41a4));goto dispatch;
L_002d41a4:
 STEP(UINT32_C(0x002d41a4)); /* 8c430004 lw v1,0x4(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d41a8));goto dispatch;
L_002d41a8:
 STEP(UINT32_C(0x002d41a8)); /* 00721824 and v1,v1,s2 */
 set(m,3u,lo(m,3u)&lo(m,18u));target=sx(UINT32_C(0x002d41ac));goto dispatch;
L_002d41ac:
 STEP(UINT32_C(0x002d41ac)); /* 0071102b sltu v0,v1,s1 */
 set(m,2u,lo(m,3u)<lo(m,17u));target=sx(UINT32_C(0x002d41b0));goto dispatch;
L_002d41b0:
 STEP(UINT32_C(0x002d41b0)); /* 10400007 beq v0,zero,002d41d0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d41b4));set(m,2u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,17u)));target=sx(taken?UINT32_C(0x002d41d0):UINT32_C(0x002d41b8));goto dispatch;}
L_002d41b4:
 STEP(UINT32_C(0x002d41b4)); /* 00711023 subu v0,v1,s1 */
 set(m,2u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d41b8));goto dispatch;
L_002d41b8:
 STEP(UINT32_C(0x002d41b8)); /* 02231023 subu v0,s1,v1 */
 set(m,2u,sx((uint32_t)lo(m,17u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d41bc));goto dispatch;
L_002d41bc:
 STEP(UINT32_C(0x002d41bc)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d41c0));goto dispatch;
L_002d41c0:
 STEP(UINT32_C(0x002d41c0)); /* 0002103e dsrl32 v0,v0,0 */
 set(m,2u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d41c4));goto dispatch;
L_002d41c4:
 STEP(UINT32_C(0x002d41c4)); /* 10000004 beq zero,zero,002d41d8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d41c8));set(m,8u,lo(m,0u)-lo(m,2u));target=sx(taken?UINT32_C(0x002d41d8):UINT32_C(0x002d41cc));goto dispatch;}
L_002d41c8:
 STEP(UINT32_C(0x002d41c8)); /* 0002402f dsubu t0,zero,v0 */
 set(m,8u,lo(m,0u)-lo(m,2u));target=sx(UINT32_C(0x002d41cc));goto dispatch;
L_002d41cc:
 STEP(UINT32_C(0x002d41cc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d41d0));goto dispatch;
L_002d41d0:
 STEP(UINT32_C(0x002d41d0)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d41d4));goto dispatch;
L_002d41d4:
 STEP(UINT32_C(0x002d41d4)); /* 0002403e dsrl32 t0,v0,0 */
 set(m,8u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d41d8));goto dispatch;
L_002d41d8:
 STEP(UINT32_C(0x002d41d8)); /* 2684be30 addiu a0,s4,-16848 */
 set(m,4u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d41dc));goto dispatch;
L_002d41dc:
 STEP(UINT32_C(0x002d41dc)); /* 2405fffc addiu a1,zero,-4 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d41e0));goto dispatch;
L_002d41e0:
 STEP(UINT32_C(0x002d41e0)); /* 8c830008 lw v1,0x8(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d41e4));goto dispatch;
L_002d41e4:
 STEP(UINT32_C(0x002d41e4)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d41e8));goto dispatch;
L_002d41e8:
 STEP(UINT32_C(0x002d41e8)); /* 00451024 and v0,v0,a1 */
 set(m,2u,lo(m,2u)&lo(m,5u));target=sx(UINT32_C(0x002d41ec));goto dispatch;
L_002d41ec:
 STEP(UINT32_C(0x002d41ec)); /* 0051102b sltu v0,v0,s1 */
 set(m,2u,lo(m,2u)<lo(m,17u));target=sx(UINT32_C(0x002d41f0));goto dispatch;
L_002d41f0:
 STEP(UINT32_C(0x002d41f0)); /* 14400003 bne v0,zero,002d4200 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d41f4));set(m,2u,((int64_t)lo(m,8u)<INT64_C(16)));target=sx(taken?UINT32_C(0x002d4200):UINT32_C(0x002d41f8));goto dispatch;}
L_002d41f4:
 STEP(UINT32_C(0x002d41f4)); /* 29020010 slti v0,t0,16 */
 set(m,2u,((int64_t)lo(m,8u)<INT64_C(16)));target=sx(UINT32_C(0x002d41f8));goto dispatch;
L_002d41f8:
 STEP(UINT32_C(0x002d41f8)); /* 1040002f beq v0,zero,002d42b8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d41fc));set(m,6u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(taken?UINT32_C(0x002d42b8):UINT32_C(0x002d4200));goto dispatch;}
L_002d41fc:
 STEP(UINT32_C(0x002d41fc)); /* 2686be30 addiu a2,s4,-16848 */
 set(m,6u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d4200));goto dispatch;
L_002d4200:
 STEP(UINT32_C(0x002d4200)); /* 0c0b51a6 jal 002d4698 */
 set(m,31u,UINT64_C(0x002d4208));STEP(UINT32_C(0x002d4204));set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d4698));goto dispatch;
L_002d4204:
 STEP(UINT32_C(0x002d4204)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d4208));goto dispatch;
L_002d4208:
 STEP(UINT32_C(0x002d4208)); /* 10000039 beq zero,zero,002d42f0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d420c));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d42f0):UINT32_C(0x002d4210));goto dispatch;}
L_002d420c:
 STEP(UINT32_C(0x002d420c)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d4210));goto dispatch;
L_002d4210:
 STEP(UINT32_C(0x002d4210)); /* 8e0b000c lw t3,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,11u,sx(value32));target=sx(UINT32_C(0x002d4214));goto dispatch;
L_002d4214:
 STEP(UINT32_C(0x002d4214)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4218));goto dispatch;
L_002d4218:
 STEP(UINT32_C(0x002d4218)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d421c));goto dispatch;
L_002d421c:
 STEP(UINT32_C(0x002d421c)); /* 8e080008 lw t0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d4220));goto dispatch;
L_002d4220:
 STEP(UINT32_C(0x002d4220)); /* 34420001 ori v0,v0,0x1 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d4224));goto dispatch;
L_002d4224:
 STEP(UINT32_C(0x002d4224)); /* ac620004 sw v0,0x4(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d4228));goto dispatch;
L_002d4228:
 STEP(UINT32_C(0x002d4228)); /* ad0b000c sw t3,0xc(t0) */
 value32=(uint32_t)lo(m,11u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d422c));goto dispatch;
L_002d422c:
 STEP(UINT32_C(0x002d422c)); /* 1000002d beq zero,zero,002d42e4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d4230));value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002d42e4):UINT32_C(0x002d4234));goto dispatch;}
L_002d4230:
 STEP(UINT32_C(0x002d4230)); /* ad680008 sw t0,0x8(t3) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d4234));goto dispatch;
L_002d4234:
 STEP(UINT32_C(0x002d4234)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4238));goto dispatch;
L_002d4238:
 STEP(UINT32_C(0x002d4238)); /* 8e0b000c lw t3,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,11u,sx(value32));target=sx(UINT32_C(0x002d423c));goto dispatch;
L_002d423c:
 STEP(UINT32_C(0x002d423c)); /* 02114821 addu t1,s0,s1 */
 set(m,9u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d4240));goto dispatch;
L_002d4240:
 STEP(UINT32_C(0x002d4240)); /* 0008383c dsll32 a3,t0,0 */
 set(m,7u,lo(m,8u)<<32u);target=sx(UINT32_C(0x002d4244));goto dispatch;
L_002d4244:
 STEP(UINT32_C(0x002d4244)); /* 0007383f dsra32 a3,a3,0 */
 set(m,7u,(uint64_t)((int64_t)lo(m,7u)>>32u));target=sx(UINT32_C(0x002d4248));goto dispatch;
L_002d4248:
 STEP(UINT32_C(0x002d4248)); /* 01031825 or v1,t0,v1 */
 set(m,3u,lo(m,8u)|lo(m,3u));target=sx(UINT32_C(0x002d424c));goto dispatch;
L_002d424c:
 STEP(UINT32_C(0x002d424c)); /* 8e080008 lw t0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d4250));goto dispatch;
L_002d4250:
 STEP(UINT32_C(0x002d4250)); /* 25e5be38 addiu a1,t7,-16840 */
 set(m,5u,sx((uint32_t)lo(m,15u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d4254));goto dispatch;
L_002d4254:
 STEP(UINT32_C(0x002d4254)); /* 36220001 ori v0,s1,0x1 */
 set(m,2u,lo(m,17u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d4258));goto dispatch;
L_002d4258:
 STEP(UINT32_C(0x002d4258)); /* 0003183c dsll32 v1,v1,0 */
 set(m,3u,lo(m,3u)<<32u);target=sx(UINT32_C(0x002d425c));goto dispatch;
L_002d425c:
 STEP(UINT32_C(0x002d425c)); /* 0003183f dsra32 v1,v1,0 */
 set(m,3u,(uint64_t)((int64_t)lo(m,3u)>>32u));target=sx(UINT32_C(0x002d4260));goto dispatch;
L_002d4260:
 STEP(UINT32_C(0x002d4260)); /* 01273021 addu a2,t1,a3 */
 set(m,6u,sx((uint32_t)lo(m,9u)+(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x002d4264));goto dispatch;
L_002d4264:
 STEP(UINT32_C(0x002d4264)); /* ad0b000c sw t3,0xc(t0) */
 value32=(uint32_t)lo(m,11u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d4268));goto dispatch;
L_002d4268:
 STEP(UINT32_C(0x002d4268)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d426c));goto dispatch;
L_002d426c:
 STEP(UINT32_C(0x002d426c)); /* ad680008 sw t0,0x8(t3) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d4270));goto dispatch;
L_002d4270:
 STEP(UINT32_C(0x002d4270)); /* ae020004 sw v0,0x4(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d4274));goto dispatch;
L_002d4274:
 STEP(UINT32_C(0x002d4274)); /* aca9000c sw t1,0xc(a1) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d4278));goto dispatch;
L_002d4278:
 STEP(UINT32_C(0x002d4278)); /* aca90008 sw t1,0x8(a1) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d427c));goto dispatch;
L_002d427c:
 STEP(UINT32_C(0x002d427c)); /* ad230004 sw v1,0x4(t1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d4280));goto dispatch;
L_002d4280:
 STEP(UINT32_C(0x002d4280)); /* ad250008 sw a1,0x8(t1) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d4284));goto dispatch;
L_002d4284:
 STEP(UINT32_C(0x002d4284)); /* acc70000 sw a3,0x0(a2) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d4288));goto dispatch;
L_002d4288:
 STEP(UINT32_C(0x002d4288)); /* 10000016 beq zero,zero,002d42e4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d428c));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);target=sx(taken?UINT32_C(0x002d42e4):UINT32_C(0x002d4290));goto dispatch;}
L_002d428c:
 STEP(UINT32_C(0x002d428c)); /* ad25000c sw a1,0xc(t1) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d4290));goto dispatch;
L_002d4290:
 STEP(UINT32_C(0x002d4290)); /* 8e0b000c lw t3,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,11u,sx(value32));target=sx(UINT32_C(0x002d4294));goto dispatch;
L_002d4294:
 STEP(UINT32_C(0x002d4294)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4298));goto dispatch;
L_002d4298:
 STEP(UINT32_C(0x002d4298)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d429c));goto dispatch;
L_002d429c:
 STEP(UINT32_C(0x002d429c)); /* 8e080008 lw t0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d42a0));goto dispatch;
L_002d42a0:
 STEP(UINT32_C(0x002d42a0)); /* 34420001 ori v0,v0,0x1 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d42a4));goto dispatch;
L_002d42a4:
 STEP(UINT32_C(0x002d42a4)); /* ac620004 sw v0,0x4(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d42a8));goto dispatch;
L_002d42a8:
 STEP(UINT32_C(0x002d42a8)); /* ad0b000c sw t3,0xc(t0) */
 value32=(uint32_t)lo(m,11u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d42ac));goto dispatch;
L_002d42ac:
 STEP(UINT32_C(0x002d42ac)); /* 1000000d beq zero,zero,002d42e4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d42b0));value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002d42e4):UINT32_C(0x002d42b4));goto dispatch;}
L_002d42b0:
 STEP(UINT32_C(0x002d42b0)); /* ad680008 sw t0,0x8(t3) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d42b4));goto dispatch;
L_002d42b4:
 STEP(UINT32_C(0x002d42b4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d42b8));goto dispatch;
L_002d42b8:
 STEP(UINT32_C(0x002d42b8)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d42bc));goto dispatch;
L_002d42bc:
 STEP(UINT32_C(0x002d42bc)); /* 8cd00008 lw s0,0x8(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000008),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d42c0));goto dispatch;
L_002d42c0:
 STEP(UINT32_C(0x002d42c0)); /* 01021025 or v0,t0,v0 */
 set(m,2u,lo(m,8u)|lo(m,2u));target=sx(UINT32_C(0x002d42c4));goto dispatch;
L_002d42c4:
 STEP(UINT32_C(0x002d42c4)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d42c8));goto dispatch;
L_002d42c8:
 STEP(UINT32_C(0x002d42c8)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x002d42cc));goto dispatch;
L_002d42cc:
 STEP(UINT32_C(0x002d42cc)); /* 36230001 ori v1,s1,0x1 */
 set(m,3u,lo(m,17u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d42d0));goto dispatch;
L_002d42d0:
 STEP(UINT32_C(0x002d42d0)); /* 02112821 addu a1,s0,s1 */
 set(m,5u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d42d4));goto dispatch;
L_002d42d4:
 STEP(UINT32_C(0x002d42d4)); /* ae030004 sw v1,0x4(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d42d8));goto dispatch;
L_002d42d8:
 STEP(UINT32_C(0x002d42d8)); /* acc50008 sw a1,0x8(a2) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d42dc));goto dispatch;
L_002d42dc:
 STEP(UINT32_C(0x002d42dc)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d42e0));goto dispatch;
L_002d42e0:
 STEP(UINT32_C(0x002d42e0)); /* aca20004 sw v0,0x4(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d42e4));goto dispatch;
L_002d42e4:
 STEP(UINT32_C(0x002d42e4)); /* 0c0b51a6 jal 002d4698 */
 set(m,31u,UINT64_C(0x002d42ec));STEP(UINT32_C(0x002d42e8));/* nop */target=sx(UINT32_C(0x002d4698));goto dispatch;
L_002d42e8:
 STEP(UINT32_C(0x002d42e8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d42ec));goto dispatch;
L_002d42ec:
 STEP(UINT32_C(0x002d42ec)); /* 26020008 addiu v0,s0,8 */
 set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d42f0));goto dispatch;
L_002d42f0:
 STEP(UINT32_C(0x002d42f0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d42f4));goto dispatch;
L_002d42f4:
 STEP(UINT32_C(0x002d42f4)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d42f8));goto dispatch;
L_002d42f8:
 STEP(UINT32_C(0x002d42f8)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002d42fc));goto dispatch;
L_002d42fc:
 STEP(UINT32_C(0x002d42fc)); /* dfb30018 ld s3,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002d4300));goto dispatch;
L_002d4300:
 STEP(UINT32_C(0x002d4300)); /* dfb40020 ld s4,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002d4304));goto dispatch;
L_002d4304:
 STEP(UINT32_C(0x002d4304)); /* dfbf0028 ld ra,0x28(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d4308));goto dispatch;
L_002d4308:
 STEP(UINT32_C(0x002d4308)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d430c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002d430c:
 STEP(UINT32_C(0x002d430c)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002d4310));goto dispatch;
L_002d3990:
 STEP(UINT32_C(0x002d3990)); /* 27bdffa0 addiu sp,sp,-96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffa0)));target=sx(UINT32_C(0x002d3994));goto dispatch;
L_002d3994:
 STEP(UINT32_C(0x002d3994)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3998));goto dispatch;
L_002d3998:
 STEP(UINT32_C(0x002d3998)); /* ffb70048 sd s7,0x48(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000048),&value64,8u);target=sx(UINT32_C(0x002d399c));goto dispatch;
L_002d399c:
 STEP(UINT32_C(0x002d399c)); /* 2457be30 addiu s7,v0,-16848 */
 set(m,23u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d39a0));goto dispatch;
L_002d39a0:
 STEP(UINT32_C(0x002d39a0)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d39a4));goto dispatch;
L_002d39a4:
 STEP(UINT32_C(0x002d39a4)); /* 3c060053 lui a2,zero,0x53 */
 set(m,6u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d39a8));goto dispatch;
L_002d39a8:
 STEP(UINT32_C(0x002d39a8)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002d39ac));goto dispatch;
L_002d39ac:
 STEP(UINT32_C(0x002d39ac)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d39b0));goto dispatch;
L_002d39b0:
 STEP(UINT32_C(0x002d39b0)); /* ffb30028 sd s3,0x28(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(UINT32_C(0x002d39b4));goto dispatch;
L_002d39b4:
 STEP(UINT32_C(0x002d39b4)); /* 0005283c dsll32 a1,a1,0 */
 set(m,5u,lo(m,5u)<<32u);target=sx(UINT32_C(0x002d39b8));goto dispatch;
L_002d39b8:
 STEP(UINT32_C(0x002d39b8)); /* ffb40030 sd s4,0x30(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002d39bc));goto dispatch;
L_002d39bc:
 STEP(UINT32_C(0x002d39bc)); /* 0005283e dsrl32 a1,a1,0 */
 set(m,5u,lo(m,5u)>>32u);target=sx(UINT32_C(0x002d39c0));goto dispatch;
L_002d39c0:
 STEP(UINT32_C(0x002d39c0)); /* ffb50038 sd s5,0x38(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000038),&value64,8u);target=sx(UINT32_C(0x002d39c4));goto dispatch;
L_002d39c4:
 STEP(UINT32_C(0x002d39c4)); /* 2415ffff addiu s5,zero,-1 */
 set(m,21u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d39c8));goto dispatch;
L_002d39c8:
 STEP(UINT32_C(0x002d39c8)); /* ffb60040 sd s6,0x40(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002d39cc));goto dispatch;
L_002d39cc:
 STEP(UINT32_C(0x002d39cc)); /* 2456c248 addiu s6,v0,-15800 */
 set(m,22u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffc248)));target=sx(UINT32_C(0x002d39d0));goto dispatch;
L_002d39d0:
 STEP(UINT32_C(0x002d39d0)); /* 8ef40008 lw s4,0x8(s7) */
 READ((uint32_t)lo(m,23u)+UINT32_C(0x00000008),&value32,4u);set(m,20u,sx(value32));target=sx(UINT32_C(0x002d39d4));goto dispatch;
L_002d39d4:
 STEP(UINT32_C(0x002d39d4)); /* 2402fffc addiu v0,zero,-4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d39d8));goto dispatch;
L_002d39d8:
 STEP(UINT32_C(0x002d39d8)); /* ffb10018 sd s1,0x18(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002d39dc));goto dispatch;
L_002d39dc:
 STEP(UINT32_C(0x002d39dc)); /* ffbe0050 sd s8,0x50(sp) */
 value64=lo(m,30u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002d39e0));goto dispatch;
L_002d39e0:
 STEP(UINT32_C(0x002d39e0)); /* ffbf0058 sd ra,0x58(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000058),&value64,8u);target=sx(UINT32_C(0x002d39e4));goto dispatch;
L_002d39e4:
 STEP(UINT32_C(0x002d39e4)); /* dcc3c240 ld v1,-0x3dc0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0xffffc240),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d39e8));goto dispatch;
L_002d39e8:
 STEP(UINT32_C(0x002d39e8)); /* 8e860004 lw a2,0x4(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d39ec));goto dispatch;
L_002d39ec:
 STEP(UINT32_C(0x002d39ec)); /* 00a3282d daddu a1,a1,v1 */
 set(m,5u,lo(m,5u)+lo(m,3u));target=sx(UINT32_C(0x002d39f0));goto dispatch;
L_002d39f0:
 STEP(UINT32_C(0x002d39f0)); /* 8ec30000 lw v1,0x0(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d39f4));goto dispatch;
L_002d39f4:
 STEP(UINT32_C(0x002d39f4)); /* 00c29824 and s3,a2,v0 */
 set(m,19u,lo(m,6u)&lo(m,2u));target=sx(UINT32_C(0x002d39f8));goto dispatch;
L_002d39f8:
 STEP(UINT32_C(0x002d39f8)); /* 64a50010 daddiu a1,a1,16 */
 set(m,5u,lo(m,5u)+UINT64_C(0x0000000000000010));target=sx(UINT32_C(0x002d39fc));goto dispatch;
L_002d39fc:
 STEP(UINT32_C(0x002d39fc)); /* 0005903c dsll32 s2,a1,0 */
 set(m,18u,lo(m,5u)<<32u);target=sx(UINT32_C(0x002d3a00));goto dispatch;
L_002d3a00:
 STEP(UINT32_C(0x002d3a00)); /* 0012903f dsra32 s2,s2,0 */
 set(m,18u,(uint64_t)((int64_t)lo(m,18u)>>32u));target=sx(UINT32_C(0x002d3a04));goto dispatch;
L_002d3a04:
 STEP(UINT32_C(0x002d3a04)); /* afa40000 sw a0,0x0(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d3a08));goto dispatch;
L_002d3a08:
 STEP(UINT32_C(0x002d3a08)); /* 10750008 beq v1,s5,002d3a2c */
 {int taken=(lo(m,3u)==lo(m,21u));STEP(UINT32_C(0x002d3a0c));set(m,16u,sx((uint32_t)lo(m,20u)+(uint32_t)lo(m,19u)));target=sx(taken?UINT32_C(0x002d3a2c):UINT32_C(0x002d3a10));goto dispatch;}
L_002d3a0c:
 STEP(UINT32_C(0x002d3a0c)); /* 02938021 addu s0,s4,s3 */
 set(m,16u,sx((uint32_t)lo(m,20u)+(uint32_t)lo(m,19u)));target=sx(UINT32_C(0x002d3a10));goto dispatch;
L_002d3a10:
 STEP(UINT32_C(0x002d3a10)); /* 0012103c dsll32 v0,s2,0 */
 set(m,2u,lo(m,18u)<<32u);target=sx(UINT32_C(0x002d3a14));goto dispatch;
L_002d3a14:
 STEP(UINT32_C(0x002d3a14)); /* 2403f000 addiu v1,zero,-4096 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffff000)));target=sx(UINT32_C(0x002d3a18));goto dispatch;
L_002d3a18:
 STEP(UINT32_C(0x002d3a18)); /* 0002103e dsrl32 v0,v0,0 */
 set(m,2u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d3a1c));goto dispatch;
L_002d3a1c:
 STEP(UINT32_C(0x002d3a1c)); /* 64420fff daddiu v0,v0,4095 */
 set(m,2u,lo(m,2u)+UINT64_C(0x0000000000000fff));target=sx(UINT32_C(0x002d3a20));goto dispatch;
L_002d3a20:
 STEP(UINT32_C(0x002d3a20)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d3a24));goto dispatch;
L_002d3a24:
 STEP(UINT32_C(0x002d3a24)); /* 0002903c dsll32 s2,v0,0 */
 set(m,18u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d3a28));goto dispatch;
L_002d3a28:
 STEP(UINT32_C(0x002d3a28)); /* 0012903f dsra32 s2,s2,0 */
 set(m,18u,(uint64_t)((int64_t)lo(m,18u)>>32u));target=sx(UINT32_C(0x002d3a2c));goto dispatch;
L_002d3a2c:
 STEP(UINT32_C(0x002d3a2c)); /* 0c0b5494 jal 002d5250 */
 set(m,31u,UINT64_C(0x002d3a34));STEP(UINT32_C(0x002d3a30));set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d5250));goto dispatch;
L_002d3a30:
 STEP(UINT32_C(0x002d3a30)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d3a34));goto dispatch;
L_002d3a34:
 STEP(UINT32_C(0x002d3a34)); /* 0040882d daddu s1,v0,zero */
 set(m,17u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d3a38));goto dispatch;
L_002d3a38:
 STEP(UINT32_C(0x002d3a38)); /* 1235005f beq s1,s5,002d3bb8 */
 {int taken=(lo(m,17u)==lo(m,21u));STEP(UINT32_C(0x002d3a3c));set(m,2u,lo(m,17u)<lo(m,16u));target=sx(taken?UINT32_C(0x002d3bb8):UINT32_C(0x002d3a40));goto dispatch;}
L_002d3a3c:
 STEP(UINT32_C(0x002d3a3c)); /* 0230102b sltu v0,s1,s0 */
 set(m,2u,lo(m,17u)<lo(m,16u));target=sx(UINT32_C(0x002d3a40));goto dispatch;
L_002d3a40:
 STEP(UINT32_C(0x002d3a40)); /* 10400004 beq v0,zero,002d3a54 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d3a44));set(m,30u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002d3a54):UINT32_C(0x002d3a48));goto dispatch;}
L_002d3a44:
 STEP(UINT32_C(0x002d3a44)); /* 3c1e0053 lui s8,zero,0x53 */
 set(m,30u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3a48));goto dispatch;
L_002d3a48:
 STEP(UINT32_C(0x002d3a48)); /* 5697005c bnel s4,s7,002d3bbc */
 if(lo(m,20u)!=lo(m,23u)){STEP(UINT32_C(0x002d3a4c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d3bbc));}else target=sx(UINT32_C(0x002d3a50));goto dispatch;
L_002d3a4c:
 STEP(UINT32_C(0x002d3a4c)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d3a50));goto dispatch;
L_002d3a50:
 STEP(UINT32_C(0x002d3a50)); /* 3c1e0053 lui s8,zero,0x53 */
 set(m,30u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3a54));goto dispatch;
L_002d3a54:
 STEP(UINT32_C(0x002d3a54)); /* 27c4c260 addiu a0,s8,-15776 */
 set(m,4u,sx((uint32_t)lo(m,30u)+UINT32_C(0xffffc260)));target=sx(UINT32_C(0x002d3a58));goto dispatch;
L_002d3a58:
 STEP(UINT32_C(0x002d3a58)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3a5c));goto dispatch;
L_002d3a5c:
 STEP(UINT32_C(0x002d3a5c)); /* 00521821 addu v1,v0,s2 */
 set(m,3u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,18u)));target=sx(UINT32_C(0x002d3a60));goto dispatch;
L_002d3a60:
 STEP(UINT32_C(0x002d3a60)); /* 16300007 bne s1,s0,002d3a80 */
 {int taken=(lo(m,17u)!=lo(m,16u));STEP(UINT32_C(0x002d3a64));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002d3a80):UINT32_C(0x002d3a68));goto dispatch;}
L_002d3a64:
 STEP(UINT32_C(0x002d3a64)); /* ac830000 sw v1,0x0(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d3a68));goto dispatch;
L_002d3a68:
 STEP(UINT32_C(0x002d3a68)); /* 02532021 addu a0,s2,s3 */
 set(m,4u,sx((uint32_t)lo(m,18u)+(uint32_t)lo(m,19u)));target=sx(UINT32_C(0x002d3a6c));goto dispatch;
L_002d3a6c:
 STEP(UINT32_C(0x002d3a6c)); /* 8ee30008 lw v1,0x8(s7) */
 READ((uint32_t)lo(m,23u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d3a70));goto dispatch;
L_002d3a70:
 STEP(UINT32_C(0x002d3a70)); /* 34820001 ori v0,a0,0x1 */
 set(m,2u,lo(m,4u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d3a74));goto dispatch;
L_002d3a74:
 STEP(UINT32_C(0x002d3a74)); /* 10000043 beq zero,zero,002d3b84 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3a78));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d3b84):UINT32_C(0x002d3a7c));goto dispatch;}
L_002d3a78:
 STEP(UINT32_C(0x002d3a78)); /* ac620004 sw v0,0x4(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3a7c));goto dispatch;
L_002d3a7c:
 STEP(UINT32_C(0x002d3a7c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3a80));goto dispatch;
L_002d3a80:
 STEP(UINT32_C(0x002d3a80)); /* 8ec20000 lw v0,0x0(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3a84));goto dispatch;
L_002d3a84:
 STEP(UINT32_C(0x002d3a84)); /* 14550004 bne v0,s5,002d3a98 */
 {int taken=(lo(m,2u)!=lo(m,21u));STEP(UINT32_C(0x002d3a88));set(m,2u,sx((uint32_t)lo(m,17u)-(uint32_t)lo(m,16u)));target=sx(taken?UINT32_C(0x002d3a98):UINT32_C(0x002d3a8c));goto dispatch;}
L_002d3a88:
 STEP(UINT32_C(0x002d3a88)); /* 02301023 subu v0,s1,s0 */
 set(m,2u,sx((uint32_t)lo(m,17u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d3a8c));goto dispatch;
L_002d3a8c:
 STEP(UINT32_C(0x002d3a8c)); /* 10000004 beq zero,zero,002d3aa0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3a90));value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002d3aa0):UINT32_C(0x002d3a94));goto dispatch;}
L_002d3a90:
 STEP(UINT32_C(0x002d3a90)); /* aed10000 sw s1,0x0(s6) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d3a94));goto dispatch;
L_002d3a94:
 STEP(UINT32_C(0x002d3a94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3a98));goto dispatch;
L_002d3a98:
 STEP(UINT32_C(0x002d3a98)); /* 00621021 addu v0,v1,v0 */
 set(m,2u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d3a9c));goto dispatch;
L_002d3a9c:
 STEP(UINT32_C(0x002d3a9c)); /* ac820000 sw v0,0x0(a0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d3aa0));goto dispatch;
L_002d3aa0:
 STEP(UINT32_C(0x002d3aa0)); /* 26220008 addiu v0,s1,8 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d3aa4));goto dispatch;
L_002d3aa4:
 STEP(UINT32_C(0x002d3aa4)); /* 3045000f andi a1,v0,0xf */
 set(m,5u,lo(m,2u) & UINT64_C(0xf));target=sx(UINT32_C(0x002d3aa8));goto dispatch;
L_002d3aa8:
 STEP(UINT32_C(0x002d3aa8)); /* 10a00005 beq a1,zero,002d3ac0 */
 {int taken=(lo(m,5u)==lo(m,0u));STEP(UINT32_C(0x002d3aac));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x002d3ac0):UINT32_C(0x002d3ab0));goto dispatch;}
L_002d3aac:
 STEP(UINT32_C(0x002d3aac)); /* 24020010 addiu v0,zero,16 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d3ab0));goto dispatch;
L_002d3ab0:
 STEP(UINT32_C(0x002d3ab0)); /* 00458023 subu s0,v0,a1 */
 set(m,16u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002d3ab4));goto dispatch;
L_002d3ab4:
 STEP(UINT32_C(0x002d3ab4)); /* 10000003 beq zero,zero,002d3ac4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3ab8));set(m,17u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,16u)));target=sx(taken?UINT32_C(0x002d3ac4):UINT32_C(0x002d3abc));goto dispatch;}
L_002d3ab8:
 STEP(UINT32_C(0x002d3ab8)); /* 02308821 addu s1,s1,s0 */
 set(m,17u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d3abc));goto dispatch;
L_002d3abc:
 STEP(UINT32_C(0x002d3abc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3ac0));goto dispatch;
L_002d3ac0:
 STEP(UINT32_C(0x002d3ac0)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d3ac4));goto dispatch;
L_002d3ac4:
 STEP(UINT32_C(0x002d3ac4)); /* 02321021 addu v0,s1,s2 */
 set(m,2u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,18u)));target=sx(UINT32_C(0x002d3ac8));goto dispatch;
L_002d3ac8:
 STEP(UINT32_C(0x002d3ac8)); /* 24031000 addiu v1,zero,4096 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00001000)));target=sx(UINT32_C(0x002d3acc));goto dispatch;
L_002d3acc:
 STEP(UINT32_C(0x002d3acc)); /* 30420fff andi v0,v0,0xfff */
 set(m,2u,lo(m,2u) & UINT64_C(0xfff));target=sx(UINT32_C(0x002d3ad0));goto dispatch;
L_002d3ad0:
 STEP(UINT32_C(0x002d3ad0)); /* 8fa40000 lw a0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d3ad4));goto dispatch;
L_002d3ad4:
 STEP(UINT32_C(0x002d3ad4)); /* 0062182f dsubu v1,v1,v0 */
 set(m,3u,lo(m,3u)-lo(m,2u));target=sx(UINT32_C(0x002d3ad8));goto dispatch;
L_002d3ad8:
 STEP(UINT32_C(0x002d3ad8)); /* 0003183c dsll32 v1,v1,0 */
 set(m,3u,lo(m,3u)<<32u);target=sx(UINT32_C(0x002d3adc));goto dispatch;
L_002d3adc:
 STEP(UINT32_C(0x002d3adc)); /* 0003183f dsra32 v1,v1,0 */
 set(m,3u,(uint64_t)((int64_t)lo(m,3u)>>32u));target=sx(UINT32_C(0x002d3ae0));goto dispatch;
L_002d3ae0:
 STEP(UINT32_C(0x002d3ae0)); /* 02038021 addu s0,s0,v1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d3ae4));goto dispatch;
L_002d3ae4:
 STEP(UINT32_C(0x002d3ae4)); /* 0c0b5494 jal 002d5250 */
 set(m,31u,UINT64_C(0x002d3aec));STEP(UINT32_C(0x002d3ae8));set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d5250));goto dispatch;
L_002d3ae8:
 STEP(UINT32_C(0x002d3ae8)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d3aec));goto dispatch;
L_002d3aec:
 STEP(UINT32_C(0x002d3aec)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d3af0));goto dispatch;
L_002d3af0:
 STEP(UINT32_C(0x002d3af0)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d3af4));goto dispatch;
L_002d3af4:
 STEP(UINT32_C(0x002d3af4)); /* 10820030 beq a0,v0,002d3bb8 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x002d3af8));set(m,4u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,17u)));target=sx(taken?UINT32_C(0x002d3bb8):UINT32_C(0x002d3afc));goto dispatch;}
L_002d3af8:
 STEP(UINT32_C(0x002d3af8)); /* 00912023 subu a0,a0,s1 */
 set(m,4u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d3afc));goto dispatch;
L_002d3afc:
 STEP(UINT32_C(0x002d3afc)); /* 27c5c260 addiu a1,s8,-15776 */
 set(m,5u,sx((uint32_t)lo(m,30u)+UINT32_C(0xffffc260)));target=sx(UINT32_C(0x002d3b00));goto dispatch;
L_002d3b00:
 STEP(UINT32_C(0x002d3b00)); /* 8ca20000 lw v0,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3b04));goto dispatch;
L_002d3b04:
 STEP(UINT32_C(0x002d3b04)); /* 00902021 addu a0,a0,s0 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d3b08));goto dispatch;
L_002d3b08:
 STEP(UINT32_C(0x002d3b08)); /* 3c060053 lui a2,zero,0x53 */
 set(m,6u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3b0c));goto dispatch;
L_002d3b0c:
 STEP(UINT32_C(0x002d3b0c)); /* 34840001 ori a0,a0,0x1 */
 set(m,4u,lo(m,4u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d3b10));goto dispatch;
L_002d3b10:
 STEP(UINT32_C(0x002d3b10)); /* 24c3be30 addiu v1,a2,-16848 */
 set(m,3u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d3b14));goto dispatch;
L_002d3b14:
 STEP(UINT32_C(0x002d3b14)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d3b18));goto dispatch;
L_002d3b18:
 STEP(UINT32_C(0x002d3b18)); /* aca20000 sw v0,0x0(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d3b1c));goto dispatch;
L_002d3b1c:
 STEP(UINT32_C(0x002d3b1c)); /* ac710008 sw s1,0x8(v1) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3b20));goto dispatch;
L_002d3b20:
 STEP(UINT32_C(0x002d3b20)); /* 12830018 beq s4,v1,002d3b84 */
 {int taken=(lo(m,20u)==lo(m,3u));STEP(UINT32_C(0x002d3b24));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d3b84):UINT32_C(0x002d3b28));goto dispatch;}
L_002d3b24:
 STEP(UINT32_C(0x002d3b24)); /* ae240004 sw a0,0x4(s1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3b28));goto dispatch;
L_002d3b28:
 STEP(UINT32_C(0x002d3b28)); /* 2e620010 sltiu v0,s3,16 */
 set(m,2u,(lo(m,19u)<UINT64_C(0x10)));target=sx(UINT32_C(0x002d3b2c));goto dispatch;
L_002d3b2c:
 STEP(UINT32_C(0x002d3b2c)); /* 50400006 beql v0,zero,002d3b48 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d3b30));READ((uint32_t)lo(m,20u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3b48));}else target=sx(UINT32_C(0x002d3b34));goto dispatch;
L_002d3b30:
 STEP(UINT32_C(0x002d3b30)); /* 8e820004 lw v0,0x4(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d3b34));goto dispatch;
L_002d3b34:
 STEP(UINT32_C(0x002d3b34)); /* 0220182d daddu v1,s1,zero */
 set(m,3u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d3b38));goto dispatch;
L_002d3b38:
 STEP(UINT32_C(0x002d3b38)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d3b3c));goto dispatch;
L_002d3b3c:
 STEP(UINT32_C(0x002d3b3c)); /* 1000001e beq zero,zero,002d3bb8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d3b40));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d3bb8):UINT32_C(0x002d3b44));goto dispatch;}
L_002d3b40:
 STEP(UINT32_C(0x002d3b40)); /* ac620004 sw v0,0x4(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3b44));goto dispatch;
L_002d3b44:
 STEP(UINT32_C(0x002d3b44)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d3b48));goto dispatch;
L_002d3b48:
 STEP(UINT32_C(0x002d3b48)); /* 2664fff4 addiu a0,s3,-12 */
 set(m,4u,sx((uint32_t)lo(m,19u)+UINT32_C(0xfffffff4)));target=sx(UINT32_C(0x002d3b4c));goto dispatch;
L_002d3b4c:
 STEP(UINT32_C(0x002d3b4c)); /* 2403fff0 addiu v1,zero,-16 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d3b50));goto dispatch;
L_002d3b50:
 STEP(UINT32_C(0x002d3b50)); /* 24050005 addiu a1,zero,5 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000005)));target=sx(UINT32_C(0x002d3b54));goto dispatch;
L_002d3b54:
 STEP(UINT32_C(0x002d3b54)); /* 00839824 and s3,a0,v1 */
 set(m,19u,lo(m,4u)&lo(m,3u));target=sx(UINT32_C(0x002d3b58));goto dispatch;
L_002d3b58:
 STEP(UINT32_C(0x002d3b58)); /* 30420001 andi v0,v0,0x1 */
 set(m,2u,lo(m,2u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d3b5c));goto dispatch;
L_002d3b5c:
 STEP(UINT32_C(0x002d3b5c)); /* 02931821 addu v1,s4,s3 */
 set(m,3u,sx((uint32_t)lo(m,20u)+(uint32_t)lo(m,19u)));target=sx(UINT32_C(0x002d3b60));goto dispatch;
L_002d3b60:
 STEP(UINT32_C(0x002d3b60)); /* 00531025 or v0,v0,s3 */
 set(m,2u,lo(m,2u)|lo(m,19u));target=sx(UINT32_C(0x002d3b64));goto dispatch;
L_002d3b64:
 STEP(UINT32_C(0x002d3b64)); /* 2e640010 sltiu a0,s3,16 */
 set(m,4u,(lo(m,19u)<UINT64_C(0x10)));target=sx(UINT32_C(0x002d3b68));goto dispatch;
L_002d3b68:
 STEP(UINT32_C(0x002d3b68)); /* ae820004 sw v0,0x4(s4) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,20u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3b6c));goto dispatch;
L_002d3b6c:
 STEP(UINT32_C(0x002d3b6c)); /* ac650008 sw a1,0x8(v1) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d3b70));goto dispatch;
L_002d3b70:
 STEP(UINT32_C(0x002d3b70)); /* 14800004 bne a0,zero,002d3b84 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d3b74));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d3b84):UINT32_C(0x002d3b78));goto dispatch;}
L_002d3b74:
 STEP(UINT32_C(0x002d3b74)); /* ac650004 sw a1,0x4(v1) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d3b78));goto dispatch;
L_002d3b78:
 STEP(UINT32_C(0x002d3b78)); /* 8fa40000 lw a0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d3b7c));goto dispatch;
L_002d3b7c:
 STEP(UINT32_C(0x002d3b7c)); /* 0c0b6666 jal 002d9998 */
 set(m,31u,UINT64_C(0x002d3b84));STEP(UINT32_C(0x002d3b80));set(m,5u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d9998));goto dispatch;
L_002d3b80:
 STEP(UINT32_C(0x002d3b80)); /* 26850008 addiu a1,s4,8 */
 set(m,5u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d3b84));goto dispatch;
L_002d3b84:
 STEP(UINT32_C(0x002d3b84)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3b88));goto dispatch;
L_002d3b88:
 STEP(UINT32_C(0x002d3b88)); /* 8fc5c260 lw a1,-0x3da0(s8) */
 READ((uint32_t)lo(m,30u)+UINT32_C(0xffffc260),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d3b8c));goto dispatch;
L_002d3b8c:
 STEP(UINT32_C(0x002d3b8c)); /* 2463c250 addiu v1,v1,-15792 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffc250)));target=sx(UINT32_C(0x002d3b90));goto dispatch;
L_002d3b90:
 STEP(UINT32_C(0x002d3b90)); /* dc620000 ld v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value64,8u);set(m,2u,value64);target=sx(UINT32_C(0x002d3b94));goto dispatch;
L_002d3b94:
 STEP(UINT32_C(0x002d3b94)); /* 0045102b sltu v0,v0,a1 */
 set(m,2u,lo(m,2u)<lo(m,5u));target=sx(UINT32_C(0x002d3b98));goto dispatch;
L_002d3b98:
 STEP(UINT32_C(0x002d3b98)); /* 54400001 bnel v0,zero,002d3ba0 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d3b9c));value64=lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d3ba0));}else target=sx(UINT32_C(0x002d3ba0));goto dispatch;
L_002d3b9c:
 STEP(UINT32_C(0x002d3b9c)); /* fc650000 sd a1,0x0(v1) */
 value64=lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d3ba0));goto dispatch;
L_002d3ba0:
 STEP(UINT32_C(0x002d3ba0)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d3ba4));goto dispatch;
L_002d3ba4:
 STEP(UINT32_C(0x002d3ba4)); /* 2463c258 addiu v1,v1,-15784 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffc258)));target=sx(UINT32_C(0x002d3ba8));goto dispatch;
L_002d3ba8:
 STEP(UINT32_C(0x002d3ba8)); /* dc620000 ld v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value64,8u);set(m,2u,value64);target=sx(UINT32_C(0x002d3bac));goto dispatch;
L_002d3bac:
 STEP(UINT32_C(0x002d3bac)); /* 0045102b sltu v0,v0,a1 */
 set(m,2u,lo(m,2u)<lo(m,5u));target=sx(UINT32_C(0x002d3bb0));goto dispatch;
L_002d3bb0:
 STEP(UINT32_C(0x002d3bb0)); /* 54400001 bnel v0,zero,002d3bb8 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d3bb4));value64=lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d3bb8));}else target=sx(UINT32_C(0x002d3bb8));goto dispatch;
L_002d3bb4:
 STEP(UINT32_C(0x002d3bb4)); /* fc650000 sd a1,0x0(v1) */
 value64=lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d3bb8));goto dispatch;
L_002d3bb8:
 STEP(UINT32_C(0x002d3bb8)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d3bbc));goto dispatch;
L_002d3bbc:
 STEP(UINT32_C(0x002d3bbc)); /* dfb10018 ld s1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d3bc0));goto dispatch;
L_002d3bc0:
 STEP(UINT32_C(0x002d3bc0)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002d3bc4));goto dispatch;
L_002d3bc4:
 STEP(UINT32_C(0x002d3bc4)); /* dfb30028 ld s3,0x28(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002d3bc8));goto dispatch;
L_002d3bc8:
 STEP(UINT32_C(0x002d3bc8)); /* dfb40030 ld s4,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002d3bcc));goto dispatch;
L_002d3bcc:
 STEP(UINT32_C(0x002d3bcc)); /* dfb50038 ld s5,0x38(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000038),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002d3bd0));goto dispatch;
L_002d3bd0:
 STEP(UINT32_C(0x002d3bd0)); /* dfb60040 ld s6,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002d3bd4));goto dispatch;
L_002d3bd4:
 STEP(UINT32_C(0x002d3bd4)); /* dfb70048 ld s7,0x48(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000048),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002d3bd8));goto dispatch;
L_002d3bd8:
 STEP(UINT32_C(0x002d3bd8)); /* dfbe0050 ld s8,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,30u,value64);target=sx(UINT32_C(0x002d3bdc));goto dispatch;
L_002d3bdc:
 STEP(UINT32_C(0x002d3bdc)); /* dfbf0058 ld ra,0x58(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000058),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d3be0));goto dispatch;
L_002d3be0:
 STEP(UINT32_C(0x002d3be0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d3be4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));goto dispatch;
L_002d3be4:
 STEP(UINT32_C(0x002d3be4)); /* 27bd0060 addiu sp,sp,96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002d3be8));goto dispatch;
L_002d9998:
 STEP(UINT32_C(0x002d9998)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d999c));goto dispatch;
L_002d999c:
 STEP(UINT32_C(0x002d999c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d99a0));goto dispatch;
L_002d99a0:
 STEP(UINT32_C(0x002d99a0)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d99a4));goto dispatch;
L_002d99a4:
 STEP(UINT32_C(0x002d99a4)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d99a8));goto dispatch;
L_002d99a8:
 STEP(UINT32_C(0x002d99a8)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d99ac));goto dispatch;
L_002d99ac:
 STEP(UINT32_C(0x002d99ac)); /* 120000b2 beq s0,zero,002d9c78 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002d99b0));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002d9c78):UINT32_C(0x002d99b4));goto dispatch;}
L_002d99b0:
 STEP(UINT32_C(0x002d99b0)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d99b4));goto dispatch;
L_002d99b4:
 STEP(UINT32_C(0x002d99b4)); /* 0c0b5186 jal 002d4618 */
 set(m,31u,UINT64_C(0x002d99bc));STEP(UINT32_C(0x002d99b8));/* nop */target=sx(UINT32_C(0x002d4618));goto dispatch;
L_002d99b8:
 STEP(UINT32_C(0x002d99b8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d99bc));goto dispatch;
L_002d99bc:
 STEP(UINT32_C(0x002d99bc)); /* 2609fff8 addiu t1,s0,-8 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d99c0));goto dispatch;
L_002d99c0:
 STEP(UINT32_C(0x002d99c0)); /* 8d260004 lw a2,0x4(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d99c4));goto dispatch;
L_002d99c4:
 STEP(UINT32_C(0x002d99c4)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x002d99c8));goto dispatch;
L_002d99c8:
 STEP(UINT32_C(0x002d99c8)); /* 3c0c0053 lui t4,zero,0x53 */
 set(m,12u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d99cc));goto dispatch;
L_002d99cc:
 STEP(UINT32_C(0x002d99cc)); /* 2404fffc addiu a0,zero,-4 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d99d0));goto dispatch;
L_002d99d0:
 STEP(UINT32_C(0x002d99d0)); /* 00c24024 and t0,a2,v0 */
 set(m,8u,lo(m,6u)&lo(m,2u));target=sx(UINT32_C(0x002d99d4));goto dispatch;
L_002d99d4:
 STEP(UINT32_C(0x002d99d4)); /* 258abe30 addiu t2,t4,-16848 */
 set(m,10u,sx((uint32_t)lo(m,12u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d99d8));goto dispatch;
L_002d99d8:
 STEP(UINT32_C(0x002d99d8)); /* 01282821 addu a1,t1,t0 */
 set(m,5u,sx((uint32_t)lo(m,9u)+(uint32_t)lo(m,8u)));target=sx(UINT32_C(0x002d99dc));goto dispatch;
L_002d99dc:
 STEP(UINT32_C(0x002d99dc)); /* 8d430008 lw v1,0x8(t2) */
 READ((uint32_t)lo(m,10u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d99e0));goto dispatch;
L_002d99e0:
 STEP(UINT32_C(0x002d99e0)); /* 8ca20004 lw v0,0x4(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d99e4));goto dispatch;
L_002d99e4:
 STEP(UINT32_C(0x002d99e4)); /* 14a3001e bne a1,v1,002d9a60 */
 {int taken=(lo(m,5u)!=lo(m,3u));STEP(UINT32_C(0x002d99e8));set(m,4u,lo(m,2u)&lo(m,4u));target=sx(taken?UINT32_C(0x002d9a60):UINT32_C(0x002d99ec));goto dispatch;}
L_002d99e8:
 STEP(UINT32_C(0x002d99e8)); /* 00442024 and a0,v0,a0 */
 set(m,4u,lo(m,2u)&lo(m,4u));target=sx(UINT32_C(0x002d99ec));goto dispatch;
L_002d99ec:
 STEP(UINT32_C(0x002d99ec)); /* 30c20001 andi v0,a2,0x1 */
 set(m,2u,lo(m,6u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d99f0));goto dispatch;
L_002d99f0:
 STEP(UINT32_C(0x002d99f0)); /* 14400008 bne v0,zero,002d9a14 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d99f4));set(m,8u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,4u)));target=sx(taken?UINT32_C(0x002d9a14):UINT32_C(0x002d99f8));goto dispatch;}
L_002d99f4:
 STEP(UINT32_C(0x002d99f4)); /* 01044021 addu t0,t0,a0 */
 set(m,8u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d99f8));goto dispatch;
L_002d99f8:
 STEP(UINT32_C(0x002d99f8)); /* 8d230000 lw v1,0x0(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d99fc));goto dispatch;
L_002d99fc:
 STEP(UINT32_C(0x002d99fc)); /* 01234823 subu t1,t1,v1 */
 set(m,9u,sx((uint32_t)lo(m,9u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d9a00));goto dispatch;
L_002d9a00:
 STEP(UINT32_C(0x002d9a00)); /* 01034021 addu t0,t0,v1 */
 set(m,8u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d9a04));goto dispatch;
L_002d9a04:
 STEP(UINT32_C(0x002d9a04)); /* 8d27000c lw a3,0xc(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9a08));goto dispatch;
L_002d9a08:
 STEP(UINT32_C(0x002d9a08)); /* 8d260008 lw a2,0x8(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d9a0c));goto dispatch;
L_002d9a0c:
 STEP(UINT32_C(0x002d9a0c)); /* acc7000c sw a3,0xc(a2) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d9a10));goto dispatch;
L_002d9a10:
 STEP(UINT32_C(0x002d9a10)); /* ace60008 sw a2,0x8(a3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9a14));goto dispatch;
L_002d9a14:
 STEP(UINT32_C(0x002d9a14)); /* 35030001 ori v1,t0,0x1 */
 set(m,3u,lo(m,8u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d9a18));goto dispatch;
L_002d9a18:
 STEP(UINT32_C(0x002d9a18)); /* ad490008 sw t1,0x8(t2) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,10u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9a1c));goto dispatch;
L_002d9a1c:
 STEP(UINT32_C(0x002d9a1c)); /* ad230004 sw v1,0x4(t1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d9a20));goto dispatch;
L_002d9a20:
 STEP(UINT32_C(0x002d9a20)); /* 3c040053 lui a0,zero,0x53 */
 set(m,4u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9a24));goto dispatch;
L_002d9a24:
 STEP(UINT32_C(0x002d9a24)); /* 0008103c dsll32 v0,t0,0 */
 set(m,2u,lo(m,8u)<<32u);target=sx(UINT32_C(0x002d9a28));goto dispatch;
L_002d9a28:
 STEP(UINT32_C(0x002d9a28)); /* dc83c238 ld v1,-0x3dc8(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0xffffc238),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d9a2c));goto dispatch;
L_002d9a2c:
 STEP(UINT32_C(0x002d9a2c)); /* 0002103e dsrl32 v0,v0,0 */
 set(m,2u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d9a30));goto dispatch;
L_002d9a30:
 STEP(UINT32_C(0x002d9a30)); /* 0043102b sltu v0,v0,v1 */
 set(m,2u,lo(m,2u)<lo(m,3u));target=sx(UINT32_C(0x002d9a34));goto dispatch;
L_002d9a34:
 STEP(UINT32_C(0x002d9a34)); /* 14400005 bne v0,zero,002d9a4c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9a38));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d9a4c):UINT32_C(0x002d9a3c));goto dispatch;}
L_002d9a38:
 STEP(UINT32_C(0x002d9a38)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9a3c));goto dispatch;
L_002d9a3c:
 STEP(UINT32_C(0x002d9a3c)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9a40));goto dispatch;
L_002d9a40:
 STEP(UINT32_C(0x002d9a40)); /* 0c0b6724 jal 002d9c90 */
 set(m,31u,UINT64_C(0x002d9a48));STEP(UINT32_C(0x002d9a44));READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc240),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d9c90));goto dispatch;
L_002d9a44:
 STEP(UINT32_C(0x002d9a44)); /* 8c45c240 lw a1,-0x3dc0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc240),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d9a48));goto dispatch;
L_002d9a48:
 STEP(UINT32_C(0x002d9a48)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9a4c));goto dispatch;
L_002d9a4c:
 STEP(UINT32_C(0x002d9a4c)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d9a50));goto dispatch;
L_002d9a50:
 STEP(UINT32_C(0x002d9a50)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d9a54));goto dispatch;
L_002d9a54:
 STEP(UINT32_C(0x002d9a54)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d9a58));goto dispatch;
L_002d9a58:
 STEP(UINT32_C(0x002d9a58)); /* 080b51a6 j 002d4698 */
 STEP(UINT32_C(0x002d9a5c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d4698));goto dispatch;
L_002d9a5c:
 STEP(UINT32_C(0x002d9a5c)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d9a60));goto dispatch;
L_002d9a60:
 STEP(UINT32_C(0x002d9a60)); /* 30c20001 andi v0,a2,0x1 */
 set(m,2u,lo(m,6u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d9a64));goto dispatch;
L_002d9a64:
 STEP(UINT32_C(0x002d9a64)); /* aca40004 sw a0,0x4(a1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d9a68));goto dispatch;
L_002d9a68:
 STEP(UINT32_C(0x002d9a68)); /* 1440000e bne v0,zero,002d9aa4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9a6c));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d9aa4):UINT32_C(0x002d9a70));goto dispatch;}
L_002d9a6c:
 STEP(UINT32_C(0x002d9a6c)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9a70));goto dispatch;
L_002d9a70:
 STEP(UINT32_C(0x002d9a70)); /* 8d230000 lw v1,0x0(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9a74));goto dispatch;
L_002d9a74:
 STEP(UINT32_C(0x002d9a74)); /* 25420008 addiu v0,t2,8 */
 set(m,2u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d9a78));goto dispatch;
L_002d9a78:
 STEP(UINT32_C(0x002d9a78)); /* 01234823 subu t1,t1,v1 */
 set(m,9u,sx((uint32_t)lo(m,9u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d9a7c));goto dispatch;
L_002d9a7c:
 STEP(UINT32_C(0x002d9a7c)); /* 01034021 addu t0,t0,v1 */
 set(m,8u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d9a80));goto dispatch;
L_002d9a80:
 STEP(UINT32_C(0x002d9a80)); /* 8d230008 lw v1,0x8(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9a84));goto dispatch;
L_002d9a84:
 STEP(UINT32_C(0x002d9a84)); /* 54620004 bnel v1,v0,002d9a98 */
 if(lo(m,3u)!=lo(m,2u)){STEP(UINT32_C(0x002d9a88));READ((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9a98));}else target=sx(UINT32_C(0x002d9a8c));goto dispatch;
L_002d9a88:
 STEP(UINT32_C(0x002d9a88)); /* 8d27000c lw a3,0xc(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9a8c));goto dispatch;
L_002d9a8c:
 STEP(UINT32_C(0x002d9a8c)); /* 10000005 beq zero,zero,002d9aa4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9a90));set(m,11u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d9aa4):UINT32_C(0x002d9a94));goto dispatch;}
L_002d9a90:
 STEP(UINT32_C(0x002d9a90)); /* 240b0001 addiu t3,zero,1 */
 set(m,11u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d9a94));goto dispatch;
L_002d9a94:
 STEP(UINT32_C(0x002d9a94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9a98));goto dispatch;
L_002d9a98:
 STEP(UINT32_C(0x002d9a98)); /* 0060302d daddu a2,v1,zero */
 set(m,6u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d9a9c));goto dispatch;
L_002d9a9c:
 STEP(UINT32_C(0x002d9a9c)); /* acc7000c sw a3,0xc(a2) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d9aa0));goto dispatch;
L_002d9aa0:
 STEP(UINT32_C(0x002d9aa0)); /* ace60008 sw a2,0x8(a3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9aa4));goto dispatch;
L_002d9aa4:
 STEP(UINT32_C(0x002d9aa4)); /* 00a41821 addu v1,a1,a0 */
 set(m,3u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d9aa8));goto dispatch;
L_002d9aa8:
 STEP(UINT32_C(0x002d9aa8)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9aac));goto dispatch;
L_002d9aac:
 STEP(UINT32_C(0x002d9aac)); /* 30420001 andi v0,v0,0x1 */
 set(m,2u,lo(m,2u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d9ab0));goto dispatch;
L_002d9ab0:
 STEP(UINT32_C(0x002d9ab0)); /* 14400015 bne v0,zero,002d9b08 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9ab4));set(m,2u,lo(m,8u) | UINT64_C(0x1));target=sx(taken?UINT32_C(0x002d9b08):UINT32_C(0x002d9ab8));goto dispatch;}
L_002d9ab4:
 STEP(UINT32_C(0x002d9ab4)); /* 35020001 ori v0,t0,0x1 */
 set(m,2u,lo(m,8u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d9ab8));goto dispatch;
L_002d9ab8:
 STEP(UINT32_C(0x002d9ab8)); /* 1560000d bne t3,zero,002d9af0 */
 {int taken=(lo(m,11u)!=lo(m,0u));STEP(UINT32_C(0x002d9abc));set(m,8u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,4u)));target=sx(taken?UINT32_C(0x002d9af0):UINT32_C(0x002d9ac0));goto dispatch;}
L_002d9abc:
 STEP(UINT32_C(0x002d9abc)); /* 01044021 addu t0,t0,a0 */
 set(m,8u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d9ac0));goto dispatch;
L_002d9ac0:
 STEP(UINT32_C(0x002d9ac0)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9ac4));goto dispatch;
L_002d9ac4:
 STEP(UINT32_C(0x002d9ac4)); /* 8ca30008 lw v1,0x8(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9ac8));goto dispatch;
L_002d9ac8:
 STEP(UINT32_C(0x002d9ac8)); /* 2442be40 addiu v0,v0,-16832 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffbe40)));target=sx(UINT32_C(0x002d9acc));goto dispatch;
L_002d9acc:
 STEP(UINT32_C(0x002d9acc)); /* 2442fff8 addiu v0,v0,-8 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d9ad0));goto dispatch;
L_002d9ad0:
 STEP(UINT32_C(0x002d9ad0)); /* 54620009 bnel v1,v0,002d9af8 */
 if(lo(m,3u)!=lo(m,2u)){STEP(UINT32_C(0x002d9ad4));READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9af8));}else target=sx(UINT32_C(0x002d9ad8));goto dispatch;
L_002d9ad4:
 STEP(UINT32_C(0x002d9ad4)); /* 8ca7000c lw a3,0xc(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9ad8));goto dispatch;
L_002d9ad8:
 STEP(UINT32_C(0x002d9ad8)); /* ac69000c sw t1,0xc(v1) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d9adc));goto dispatch;
L_002d9adc:
 STEP(UINT32_C(0x002d9adc)); /* 240b0001 addiu t3,zero,1 */
 set(m,11u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d9ae0));goto dispatch;
L_002d9ae0:
 STEP(UINT32_C(0x002d9ae0)); /* ac690008 sw t1,0x8(v1) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9ae4));goto dispatch;
L_002d9ae4:
 STEP(UINT32_C(0x002d9ae4)); /* ad230008 sw v1,0x8(t1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9ae8));goto dispatch;
L_002d9ae8:
 STEP(UINT32_C(0x002d9ae8)); /* 10000006 beq zero,zero,002d9b04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9aec));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);target=sx(taken?UINT32_C(0x002d9b04):UINT32_C(0x002d9af0));goto dispatch;}
L_002d9aec:
 STEP(UINT32_C(0x002d9aec)); /* ad23000c sw v1,0xc(t1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d9af0));goto dispatch;
L_002d9af0:
 STEP(UINT32_C(0x002d9af0)); /* 8ca30008 lw v1,0x8(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9af4));goto dispatch;
L_002d9af4:
 STEP(UINT32_C(0x002d9af4)); /* 8ca7000c lw a3,0xc(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9af8));goto dispatch;
L_002d9af8:
 STEP(UINT32_C(0x002d9af8)); /* 0060302d daddu a2,v1,zero */
 set(m,6u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d9afc));goto dispatch;
L_002d9afc:
 STEP(UINT32_C(0x002d9afc)); /* acc7000c sw a3,0xc(a2) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d9b00));goto dispatch;
L_002d9b00:
 STEP(UINT32_C(0x002d9b00)); /* ace60008 sw a2,0x8(a3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9b04));goto dispatch;
L_002d9b04:
 STEP(UINT32_C(0x002d9b04)); /* 35020001 ori v0,t0,0x1 */
 set(m,2u,lo(m,8u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d9b08));goto dispatch;
L_002d9b08:
 STEP(UINT32_C(0x002d9b08)); /* 01281821 addu v1,t1,t0 */
 set(m,3u,sx((uint32_t)lo(m,9u)+(uint32_t)lo(m,8u)));target=sx(UINT32_C(0x002d9b0c));goto dispatch;
L_002d9b0c:
 STEP(UINT32_C(0x002d9b0c)); /* ad220004 sw v0,0x4(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d9b10));goto dispatch;
L_002d9b10:
 STEP(UINT32_C(0x002d9b10)); /* 15600053 bne t3,zero,002d9c60 */
 {int taken=(lo(m,11u)!=lo(m,0u));STEP(UINT32_C(0x002d9b14));value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002d9c60):UINT32_C(0x002d9b18));goto dispatch;}
L_002d9b14:
 STEP(UINT32_C(0x002d9b14)); /* ac680000 sw t0,0x0(v1) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d9b18));goto dispatch;
L_002d9b18:
 STEP(UINT32_C(0x002d9b18)); /* 2d020200 sltiu v0,t0,512 */
 set(m,2u,(lo(m,8u)<UINT64_C(0x200)));target=sx(UINT32_C(0x002d9b1c));goto dispatch;
L_002d9b1c:
 STEP(UINT32_C(0x002d9b1c)); /* 50400012 beql v0,zero,002d9b68 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d9b20));set(m,3u,sx((uint32_t)lo(m,8u)>>9u));target=sx(UINT32_C(0x002d9b68));}else target=sx(UINT32_C(0x002d9b24));goto dispatch;
L_002d9b20:
 STEP(UINT32_C(0x002d9b20)); /* 00081a42 srl v1,t0,9 */
 set(m,3u,sx((uint32_t)lo(m,8u)>>9u));target=sx(UINT32_C(0x002d9b24));goto dispatch;
L_002d9b24:
 STEP(UINT32_C(0x002d9b24)); /* 000828c2 srl a1,t0,3 */
 set(m,5u,sx((uint32_t)lo(m,8u)>>3u));target=sx(UINT32_C(0x002d9b28));goto dispatch;
L_002d9b28:
 STEP(UINT32_C(0x002d9b28)); /* 2584be30 addiu a0,t4,-16848 */
 set(m,4u,sx((uint32_t)lo(m,12u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d9b2c));goto dispatch;
L_002d9b2c:
 STEP(UINT32_C(0x002d9b2c)); /* 000518c0 sll v1,a1,3 */
 set(m,3u,sx((uint32_t)lo(m,5u)<<3u));target=sx(UINT32_C(0x002d9b30));goto dispatch;
L_002d9b30:
 STEP(UINT32_C(0x002d9b30)); /* 00052882 srl a1,a1,2 */
 set(m,5u,sx((uint32_t)lo(m,5u)>>2u));target=sx(UINT32_C(0x002d9b34));goto dispatch;
L_002d9b34:
 STEP(UINT32_C(0x002d9b34)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d9b38));goto dispatch;
L_002d9b38:
 STEP(UINT32_C(0x002d9b38)); /* 00643821 addu a3,v1,a0 */
 set(m,7u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d9b3c));goto dispatch;
L_002d9b3c:
 STEP(UINT32_C(0x002d9b3c)); /* 00a21014 UNKNOWN 00a21014 */
 set(m,2u,lo(m,2u)<<(lo(m,5u)&63u));target=sx(UINT32_C(0x002d9b40));goto dispatch;
L_002d9b40:
 STEP(UINT32_C(0x002d9b40)); /* 8c830004 lw v1,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9b44));goto dispatch;
L_002d9b44:
 STEP(UINT32_C(0x002d9b44)); /* 8ce60008 lw a2,0x8(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d9b48));goto dispatch;
L_002d9b48:
 STEP(UINT32_C(0x002d9b48)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d9b4c));goto dispatch;
L_002d9b4c:
 STEP(UINT32_C(0x002d9b4c)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x002d9b50));goto dispatch;
L_002d9b50:
 STEP(UINT32_C(0x002d9b50)); /* 00621825 or v1,v1,v0 */
 set(m,3u,lo(m,3u)|lo(m,2u));target=sx(UINT32_C(0x002d9b54));goto dispatch;
L_002d9b54:
 STEP(UINT32_C(0x002d9b54)); /* ad27000c sw a3,0xc(t1) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d9b58));goto dispatch;
L_002d9b58:
 STEP(UINT32_C(0x002d9b58)); /* ad260008 sw a2,0x8(t1) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9b5c));goto dispatch;
L_002d9b5c:
 STEP(UINT32_C(0x002d9b5c)); /* 1000003e beq zero,zero,002d9c58 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9b60));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d9c58):UINT32_C(0x002d9b64));goto dispatch;}
L_002d9b60:
 STEP(UINT32_C(0x002d9b60)); /* ac830004 sw v1,0x4(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d9b64));goto dispatch;
L_002d9b64:
 STEP(UINT32_C(0x002d9b64)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9b68));goto dispatch;
L_002d9b68:
 STEP(UINT32_C(0x002d9b68)); /* 10600019 beq v1,zero,002d9bd0 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002d9b6c));set(m,5u,sx((uint32_t)lo(m,8u)>>3u));target=sx(taken?UINT32_C(0x002d9bd0):UINT32_C(0x002d9b70));goto dispatch;}
L_002d9b6c:
 STEP(UINT32_C(0x002d9b6c)); /* 000828c2 srl a1,t0,3 */
 set(m,5u,sx((uint32_t)lo(m,8u)>>3u));target=sx(UINT32_C(0x002d9b70));goto dispatch;
L_002d9b70:
 STEP(UINT32_C(0x002d9b70)); /* 2c620005 sltiu v0,v1,5 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x5)));target=sx(UINT32_C(0x002d9b74));goto dispatch;
L_002d9b74:
 STEP(UINT32_C(0x002d9b74)); /* 10400004 beq v0,zero,002d9b88 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d9b78));set(m,2u,(lo(m,3u)<UINT64_C(0x15)));target=sx(taken?UINT32_C(0x002d9b88):UINT32_C(0x002d9b7c));goto dispatch;}
L_002d9b78:
 STEP(UINT32_C(0x002d9b78)); /* 2c620015 sltiu v0,v1,21 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x15)));target=sx(UINT32_C(0x002d9b7c));goto dispatch;
L_002d9b7c:
 STEP(UINT32_C(0x002d9b7c)); /* 00081182 srl v0,t0,6 */
 set(m,2u,sx((uint32_t)lo(m,8u)>>6u));target=sx(UINT32_C(0x002d9b80));goto dispatch;
L_002d9b80:
 STEP(UINT32_C(0x002d9b80)); /* 10000013 beq zero,zero,002d9bd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9b84));set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000038)));target=sx(taken?UINT32_C(0x002d9bd0):UINT32_C(0x002d9b88));goto dispatch;}
L_002d9b84:
 STEP(UINT32_C(0x002d9b84)); /* 24450038 addiu a1,v0,56 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000038)));target=sx(UINT32_C(0x002d9b88));goto dispatch;
L_002d9b88:
 STEP(UINT32_C(0x002d9b88)); /* 14400011 bne v0,zero,002d9bd0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9b8c));set(m,5u,sx((uint32_t)lo(m,3u)+UINT32_C(0x0000005b)));target=sx(taken?UINT32_C(0x002d9bd0):UINT32_C(0x002d9b90));goto dispatch;}
L_002d9b8c:
 STEP(UINT32_C(0x002d9b8c)); /* 2465005b addiu a1,v1,91 */
 set(m,5u,sx((uint32_t)lo(m,3u)+UINT32_C(0x0000005b)));target=sx(UINT32_C(0x002d9b90));goto dispatch;
L_002d9b90:
 STEP(UINT32_C(0x002d9b90)); /* 2c620055 sltiu v0,v1,85 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x55)));target=sx(UINT32_C(0x002d9b94));goto dispatch;
L_002d9b94:
 STEP(UINT32_C(0x002d9b94)); /* 10400004 beq v0,zero,002d9ba8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d9b98));set(m,2u,(lo(m,3u)<UINT64_C(0x155)));target=sx(taken?UINT32_C(0x002d9ba8):UINT32_C(0x002d9b9c));goto dispatch;}
L_002d9b98:
 STEP(UINT32_C(0x002d9b98)); /* 2c620155 sltiu v0,v1,341 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x155)));target=sx(UINT32_C(0x002d9b9c));goto dispatch;
L_002d9b9c:
 STEP(UINT32_C(0x002d9b9c)); /* 00081302 srl v0,t0,12 */
 set(m,2u,sx((uint32_t)lo(m,8u)>>12u));target=sx(UINT32_C(0x002d9ba0));goto dispatch;
L_002d9ba0:
 STEP(UINT32_C(0x002d9ba0)); /* 1000000b beq zero,zero,002d9bd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9ba4));set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000006e)));target=sx(taken?UINT32_C(0x002d9bd0):UINT32_C(0x002d9ba8));goto dispatch;}
L_002d9ba4:
 STEP(UINT32_C(0x002d9ba4)); /* 2445006e addiu a1,v0,110 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000006e)));target=sx(UINT32_C(0x002d9ba8));goto dispatch;
L_002d9ba8:
 STEP(UINT32_C(0x002d9ba8)); /* 10400005 beq v0,zero,002d9bc0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d9bac));set(m,2u,(lo(m,3u)<UINT64_C(0x555)));target=sx(taken?UINT32_C(0x002d9bc0):UINT32_C(0x002d9bb0));goto dispatch;}
L_002d9bac:
 STEP(UINT32_C(0x002d9bac)); /* 2c620555 sltiu v0,v1,1365 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x555)));target=sx(UINT32_C(0x002d9bb0));goto dispatch;
L_002d9bb0:
 STEP(UINT32_C(0x002d9bb0)); /* 000813c2 srl v0,t0,15 */
 set(m,2u,sx((uint32_t)lo(m,8u)>>15u));target=sx(UINT32_C(0x002d9bb4));goto dispatch;
L_002d9bb4:
 STEP(UINT32_C(0x002d9bb4)); /* 10000006 beq zero,zero,002d9bd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9bb8));set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000077)));target=sx(taken?UINT32_C(0x002d9bd0):UINT32_C(0x002d9bbc));goto dispatch;}
L_002d9bb8:
 STEP(UINT32_C(0x002d9bb8)); /* 24450077 addiu a1,v0,119 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000077)));target=sx(UINT32_C(0x002d9bbc));goto dispatch;
L_002d9bbc:
 STEP(UINT32_C(0x002d9bbc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9bc0));goto dispatch;
L_002d9bc0:
 STEP(UINT32_C(0x002d9bc0)); /* 50400003 beql v0,zero,002d9bd0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d9bc4));set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007e)));target=sx(UINT32_C(0x002d9bd0));}else target=sx(UINT32_C(0x002d9bc8));goto dispatch;
L_002d9bc4:
 STEP(UINT32_C(0x002d9bc4)); /* 2405007e addiu a1,zero,126 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007e)));target=sx(UINT32_C(0x002d9bc8));goto dispatch;
L_002d9bc8:
 STEP(UINT32_C(0x002d9bc8)); /* 00081482 srl v0,t0,18 */
 set(m,2u,sx((uint32_t)lo(m,8u)>>18u));target=sx(UINT32_C(0x002d9bcc));goto dispatch;
L_002d9bcc:
 STEP(UINT32_C(0x002d9bcc)); /* 2445007c addiu a1,v0,124 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000007c)));target=sx(UINT32_C(0x002d9bd0));goto dispatch;
L_002d9bd0:
 STEP(UINT32_C(0x002d9bd0)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9bd4));goto dispatch;
L_002d9bd4:
 STEP(UINT32_C(0x002d9bd4)); /* 000518c0 sll v1,a1,3 */
 set(m,3u,sx((uint32_t)lo(m,5u)<<3u));target=sx(UINT32_C(0x002d9bd8));goto dispatch;
L_002d9bd8:
 STEP(UINT32_C(0x002d9bd8)); /* 2442be38 addiu v0,v0,-16840 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffbe38)));target=sx(UINT32_C(0x002d9bdc));goto dispatch;
L_002d9bdc:
 STEP(UINT32_C(0x002d9bdc)); /* 244afff8 addiu t2,v0,-8 */
 set(m,10u,sx((uint32_t)lo(m,2u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d9be0));goto dispatch;
L_002d9be0:
 STEP(UINT32_C(0x002d9be0)); /* 006a3821 addu a3,v1,t2 */
 set(m,7u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,10u)));target=sx(UINT32_C(0x002d9be4));goto dispatch;
L_002d9be4:
 STEP(UINT32_C(0x002d9be4)); /* 8ce60008 lw a2,0x8(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d9be8));goto dispatch;
L_002d9be8:
 STEP(UINT32_C(0x002d9be8)); /* 54c7000d bnel a2,a3,002d9c20 */
 if(lo(m,6u)!=lo(m,7u)){STEP(UINT32_C(0x002d9bec));READ((uint32_t)lo(m,6u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9c20));}else target=sx(UINT32_C(0x002d9bf0));goto dispatch;
L_002d9bec:
 STEP(UINT32_C(0x002d9bec)); /* 8cc20004 lw v0,0x4(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9bf0));goto dispatch;
L_002d9bf0:
 STEP(UINT32_C(0x002d9bf0)); /* 24a40003 addiu a0,a1,3 */
 set(m,4u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002d9bf4));goto dispatch;
L_002d9bf4:
 STEP(UINT32_C(0x002d9bf4)); /* 28a30000 slti v1,a1,0 */
 set(m,3u,((int64_t)lo(m,5u)<INT64_C(0)));target=sx(UINT32_C(0x002d9bf8));goto dispatch;
L_002d9bf8:
 STEP(UINT32_C(0x002d9bf8)); /* 0083280b movn a1,a0,v1 */
 if(lo(m,3u)!=0u)set(m,5u,lo(m,4u));target=sx(UINT32_C(0x002d9bfc));goto dispatch;
L_002d9bfc:
 STEP(UINT32_C(0x002d9bfc)); /* 8d430004 lw v1,0x4(t2) */
 READ((uint32_t)lo(m,10u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9c00));goto dispatch;
L_002d9c00:
 STEP(UINT32_C(0x002d9c00)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d9c04));goto dispatch;
L_002d9c04:
 STEP(UINT32_C(0x002d9c04)); /* 00052083 sra a0,a1,2 */
 set(m,4u,sx((uint32_t)((int32_t)lo(m,5u)>>2u)));target=sx(UINT32_C(0x002d9c08));goto dispatch;
L_002d9c08:
 STEP(UINT32_C(0x002d9c08)); /* 00821014 UNKNOWN 00821014 */
 set(m,2u,lo(m,2u)<<(lo(m,4u)&63u));target=sx(UINT32_C(0x002d9c0c));goto dispatch;
L_002d9c0c:
 STEP(UINT32_C(0x002d9c0c)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d9c10));goto dispatch;
L_002d9c10:
 STEP(UINT32_C(0x002d9c10)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x002d9c14));goto dispatch;
L_002d9c14:
 STEP(UINT32_C(0x002d9c14)); /* 00621825 or v1,v1,v0 */
 set(m,3u,lo(m,3u)|lo(m,2u));target=sx(UINT32_C(0x002d9c18));goto dispatch;
L_002d9c18:
 STEP(UINT32_C(0x002d9c18)); /* 1000000d beq zero,zero,002d9c50 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9c1c));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,10u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d9c50):UINT32_C(0x002d9c20));goto dispatch;}
L_002d9c1c:
 STEP(UINT32_C(0x002d9c1c)); /* ad430004 sw v1,0x4(t2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,10u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d9c20));goto dispatch;
L_002d9c20:
 STEP(UINT32_C(0x002d9c20)); /* 10000004 beq zero,zero,002d9c34 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9c24));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(taken?UINT32_C(0x002d9c34):UINT32_C(0x002d9c28));goto dispatch;}
L_002d9c24:
 STEP(UINT32_C(0x002d9c24)); /* 2403fffc addiu v1,zero,-4 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d9c28));goto dispatch;
L_002d9c28:
 STEP(UINT32_C(0x002d9c28)); /* 50c70009 beql a2,a3,002d9c50 */
 if(lo(m,6u)==lo(m,7u)){STEP(UINT32_C(0x002d9c2c));READ((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9c50));}else target=sx(UINT32_C(0x002d9c30));goto dispatch;
L_002d9c2c:
 STEP(UINT32_C(0x002d9c2c)); /* 8cc7000c lw a3,0xc(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9c30));goto dispatch;
L_002d9c30:
 STEP(UINT32_C(0x002d9c30)); /* 8cc20004 lw v0,0x4(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9c34));goto dispatch;
L_002d9c34:
 STEP(UINT32_C(0x002d9c34)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d9c38));goto dispatch;
L_002d9c38:
 STEP(UINT32_C(0x002d9c38)); /* 0102102b sltu v0,t0,v0 */
 set(m,2u,lo(m,8u)<lo(m,2u));target=sx(UINT32_C(0x002d9c3c));goto dispatch;
L_002d9c3c:
 STEP(UINT32_C(0x002d9c3c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9c40));goto dispatch;
L_002d9c40:
 STEP(UINT32_C(0x002d9c40)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9c44));goto dispatch;
L_002d9c44:
 STEP(UINT32_C(0x002d9c44)); /* 5440fff8 bnel v0,zero,002d9c28 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d9c48));READ((uint32_t)lo(m,6u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d9c28));}else target=sx(UINT32_C(0x002d9c4c));goto dispatch;
L_002d9c48:
 STEP(UINT32_C(0x002d9c48)); /* 8cc60008 lw a2,0x8(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d9c4c));goto dispatch;
L_002d9c4c:
 STEP(UINT32_C(0x002d9c4c)); /* 8cc7000c lw a3,0xc(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d9c50));goto dispatch;
L_002d9c50:
 STEP(UINT32_C(0x002d9c50)); /* ad27000c sw a3,0xc(t1) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d9c54));goto dispatch;
L_002d9c54:
 STEP(UINT32_C(0x002d9c54)); /* ad260008 sw a2,0x8(t1) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9c58));goto dispatch;
L_002d9c58:
 STEP(UINT32_C(0x002d9c58)); /* ace90008 sw t1,0x8(a3) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9c5c));goto dispatch;
L_002d9c5c:
 STEP(UINT32_C(0x002d9c5c)); /* acc9000c sw t1,0xc(a2) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002d9c60));goto dispatch;
L_002d9c60:
 STEP(UINT32_C(0x002d9c60)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9c64));goto dispatch;
L_002d9c64:
 STEP(UINT32_C(0x002d9c64)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d9c68));goto dispatch;
L_002d9c68:
 STEP(UINT32_C(0x002d9c68)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d9c6c));goto dispatch;
L_002d9c6c:
 STEP(UINT32_C(0x002d9c6c)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d9c70));goto dispatch;
L_002d9c70:
 STEP(UINT32_C(0x002d9c70)); /* 080b51a6 j 002d4698 */
 STEP(UINT32_C(0x002d9c74));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d4698));goto dispatch;
L_002d9c74:
 STEP(UINT32_C(0x002d9c74)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d9c78));goto dispatch;
L_002d9c78:
 STEP(UINT32_C(0x002d9c78)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d9c7c));goto dispatch;
L_002d9c7c:
 STEP(UINT32_C(0x002d9c7c)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d9c80));goto dispatch;
L_002d9c80:
 STEP(UINT32_C(0x002d9c80)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d9c84));goto dispatch;
L_002d9c84:
 STEP(UINT32_C(0x002d9c84)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d9c88));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002d9c88:
 STEP(UINT32_C(0x002d9c88)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d9c8c));goto dispatch;
L_002d9c90:
 STEP(UINT32_C(0x002d9c90)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002d9c94));goto dispatch;
L_002d9c94:
 STEP(UINT32_C(0x002d9c94)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d9c98));goto dispatch;
L_002d9c98:
 STEP(UINT32_C(0x002d9c98)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d9c9c));goto dispatch;
L_002d9c9c:
 STEP(UINT32_C(0x002d9c9c)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d9ca0));goto dispatch;
L_002d9ca0:
 STEP(UINT32_C(0x002d9ca0)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d9ca4));goto dispatch;
L_002d9ca4:
 STEP(UINT32_C(0x002d9ca4)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d9ca8));goto dispatch;
L_002d9ca8:
 STEP(UINT32_C(0x002d9ca8)); /* 0010803c dsll32 s0,s0,0 */
 set(m,16u,lo(m,16u)<<32u);target=sx(UINT32_C(0x002d9cac));goto dispatch;
L_002d9cac:
 STEP(UINT32_C(0x002d9cac)); /* ffb40020 sd s4,0x20(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002d9cb0));goto dispatch;
L_002d9cb0:
 STEP(UINT32_C(0x002d9cb0)); /* ffb30018 sd s3,0x18(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002d9cb4));goto dispatch;
L_002d9cb4:
 STEP(UINT32_C(0x002d9cb4)); /* ffbf0028 sd ra,0x28(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(UINT32_C(0x002d9cb8));goto dispatch;
L_002d9cb8:
 STEP(UINT32_C(0x002d9cb8)); /* 0c0b5186 jal 002d4618 */
 set(m,31u,UINT64_C(0x002d9cc0));STEP(UINT32_C(0x002d9cbc));set(m,16u,lo(m,16u)>>32u);target=sx(UINT32_C(0x002d4618));goto dispatch;
L_002d9cbc:
 STEP(UINT32_C(0x002d9cbc)); /* 0010803e dsrl32 s0,s0,0 */
 set(m,16u,lo(m,16u)>>32u);target=sx(UINT32_C(0x002d9cc0));goto dispatch;
L_002d9cc0:
 STEP(UINT32_C(0x002d9cc0)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9cc4));goto dispatch;
L_002d9cc4:
 STEP(UINT32_C(0x002d9cc4)); /* 2406fffc addiu a2,zero,-4 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002d9cc8));goto dispatch;
L_002d9cc8:
 STEP(UINT32_C(0x002d9cc8)); /* 2454be30 addiu s4,v0,-16848 */
 set(m,20u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffbe30)));target=sx(UINT32_C(0x002d9ccc));goto dispatch;
L_002d9ccc:
 STEP(UINT32_C(0x002d9ccc)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9cd0));goto dispatch;
L_002d9cd0:
 STEP(UINT32_C(0x002d9cd0)); /* 8e830008 lw v1,0x8(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9cd4));goto dispatch;
L_002d9cd4:
 STEP(UINT32_C(0x002d9cd4)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9cd8));goto dispatch;
L_002d9cd8:
 STEP(UINT32_C(0x002d9cd8)); /* 00461024 and v0,v0,a2 */
 set(m,2u,lo(m,2u)&lo(m,6u));target=sx(UINT32_C(0x002d9cdc));goto dispatch;
L_002d9cdc:
 STEP(UINT32_C(0x002d9cdc)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d9ce0));goto dispatch;
L_002d9ce0:
 STEP(UINT32_C(0x002d9ce0)); /* 0002903e dsrl32 s2,v0,0 */
 set(m,18u,lo(m,2u)>>32u);target=sx(UINT32_C(0x002d9ce4));goto dispatch;
L_002d9ce4:
 STEP(UINT32_C(0x002d9ce4)); /* 0250802f dsubu s0,s2,s0 */
 set(m,16u,lo(m,18u)-lo(m,16u));target=sx(UINT32_C(0x002d9ce8));goto dispatch;
L_002d9ce8:
 STEP(UINT32_C(0x002d9ce8)); /* 66100fef daddiu s0,s0,4079 */
 set(m,16u,lo(m,16u)+UINT64_C(0x0000000000000fef));target=sx(UINT32_C(0x002d9cec));goto dispatch;
L_002d9cec:
 STEP(UINT32_C(0x002d9cec)); /* 0010833a dsrl s0,s0,12 */
 set(m,16u,lo(m,16u)>>12u);target=sx(UINT32_C(0x002d9cf0));goto dispatch;
L_002d9cf0:
 STEP(UINT32_C(0x002d9cf0)); /* 6610ffff daddiu s0,s0,-1 */
 set(m,16u,lo(m,16u)+UINT64_C(0xffffffffffffffff));target=sx(UINT32_C(0x002d9cf4));goto dispatch;
L_002d9cf4:
 STEP(UINT32_C(0x002d9cf4)); /* 00108338 dsll s0,s0,12 */
 set(m,16u,lo(m,16u)<<12u);target=sx(UINT32_C(0x002d9cf8));goto dispatch;
L_002d9cf8:
 STEP(UINT32_C(0x002d9cf8)); /* 2a021000 slti v0,s0,4096 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(4096)));target=sx(UINT32_C(0x002d9cfc));goto dispatch;
L_002d9cfc:
 STEP(UINT32_C(0x002d9cfc)); /* 14400026 bne v0,zero,002d9d98 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9d00));set(m,5u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d9d98):UINT32_C(0x002d9d04));goto dispatch;}
L_002d9d00:
 STEP(UINT32_C(0x002d9d00)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9d04));goto dispatch;
L_002d9d04:
 STEP(UINT32_C(0x002d9d04)); /* 0c0b5494 jal 002d5250 */
 set(m,31u,UINT64_C(0x002d9d0c));STEP(UINT32_C(0x002d9d08));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d5250));goto dispatch;
L_002d9d08:
 STEP(UINT32_C(0x002d9d08)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9d0c));goto dispatch;
L_002d9d0c:
 STEP(UINT32_C(0x002d9d0c)); /* 8e830008 lw v1,0x8(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9d10));goto dispatch;
L_002d9d10:
 STEP(UINT32_C(0x002d9d10)); /* 0012283c dsll32 a1,s2,0 */
 set(m,5u,lo(m,18u)<<32u);target=sx(UINT32_C(0x002d9d14));goto dispatch;
L_002d9d14:
 STEP(UINT32_C(0x002d9d14)); /* 0005283f dsra32 a1,a1,0 */
 set(m,5u,(uint64_t)((int64_t)lo(m,5u)>>32u));target=sx(UINT32_C(0x002d9d18));goto dispatch;
L_002d9d18:
 STEP(UINT32_C(0x002d9d18)); /* 00651821 addu v1,v1,a1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002d9d1c));goto dispatch;
L_002d9d1c:
 STEP(UINT32_C(0x002d9d1c)); /* 1443001e bne v0,v1,002d9d98 */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x002d9d20));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d9d98):UINT32_C(0x002d9d24));goto dispatch;}
L_002d9d20:
 STEP(UINT32_C(0x002d9d20)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9d24));goto dispatch;
L_002d9d24:
 STEP(UINT32_C(0x002d9d24)); /* 0010983c dsll32 s3,s0,0 */
 set(m,19u,lo(m,16u)<<32u);target=sx(UINT32_C(0x002d9d28));goto dispatch;
L_002d9d28:
 STEP(UINT32_C(0x002d9d28)); /* 0013983f dsra32 s3,s3,0 */
 set(m,19u,(uint64_t)((int64_t)lo(m,19u)>>32u));target=sx(UINT32_C(0x002d9d2c));goto dispatch;
L_002d9d2c:
 STEP(UINT32_C(0x002d9d2c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9d30));goto dispatch;
L_002d9d30:
 STEP(UINT32_C(0x002d9d30)); /* 0c0b5494 jal 002d5250 */
 set(m,31u,UINT64_C(0x002d9d38));STEP(UINT32_C(0x002d9d34));set(m,5u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,19u)));target=sx(UINT32_C(0x002d5250));goto dispatch;
L_002d9d34:
 STEP(UINT32_C(0x002d9d34)); /* 00132823 subu a1,zero,s3 */
 set(m,5u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,19u)));target=sx(UINT32_C(0x002d9d38));goto dispatch;
L_002d9d38:
 STEP(UINT32_C(0x002d9d38)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9d3c));goto dispatch;
L_002d9d3c:
 STEP(UINT32_C(0x002d9d3c)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9d40));goto dispatch;
L_002d9d40:
 STEP(UINT32_C(0x002d9d40)); /* 2406ffff addiu a2,zero,-1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d9d44));goto dispatch;
L_002d9d44:
 STEP(UINT32_C(0x002d9d44)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9d48));goto dispatch;
L_002d9d48:
 STEP(UINT32_C(0x002d9d48)); /* 14460017 bne v0,a2,002d9da8 */
 {int taken=(lo(m,2u)!=lo(m,6u));STEP(UINT32_C(0x002d9d4c));set(m,7u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffc260)));target=sx(taken?UINT32_C(0x002d9da8):UINT32_C(0x002d9d50));goto dispatch;}
L_002d9d4c:
 STEP(UINT32_C(0x002d9d4c)); /* 2467c260 addiu a3,v1,-15776 */
 set(m,7u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffc260)));target=sx(UINT32_C(0x002d9d50));goto dispatch;
L_002d9d50:
 STEP(UINT32_C(0x002d9d50)); /* 0c0b5494 jal 002d5250 */
 set(m,31u,UINT64_C(0x002d9d58));STEP(UINT32_C(0x002d9d54));/* nop */target=sx(UINT32_C(0x002d5250));goto dispatch;
L_002d9d54:
 STEP(UINT32_C(0x002d9d54)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9d58));goto dispatch;
L_002d9d58:
 STEP(UINT32_C(0x002d9d58)); /* 8e860008 lw a2,0x8(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d9d5c));goto dispatch;
L_002d9d5c:
 STEP(UINT32_C(0x002d9d5c)); /* 0040382d daddu a3,v0,zero */
 set(m,7u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d9d60));goto dispatch;
L_002d9d60:
 STEP(UINT32_C(0x002d9d60)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d9d64));goto dispatch;
L_002d9d64:
 STEP(UINT32_C(0x002d9d64)); /* 00e69023 subu s2,a3,a2 */
 set(m,18u,sx((uint32_t)lo(m,7u)-(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d9d68));goto dispatch;
L_002d9d68:
 STEP(UINT32_C(0x002d9d68)); /* 02421025 or v0,s2,v0 */
 set(m,2u,lo(m,18u)|lo(m,2u));target=sx(UINT32_C(0x002d9d6c));goto dispatch;
L_002d9d6c:
 STEP(UINT32_C(0x002d9d6c)); /* 2a430010 slti v1,s2,16 */
 set(m,3u,((int64_t)lo(m,18u)<INT64_C(16)));target=sx(UINT32_C(0x002d9d70));goto dispatch;
L_002d9d70:
 STEP(UINT32_C(0x002d9d70)); /* 0002283c dsll32 a1,v0,0 */
 set(m,5u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d9d74));goto dispatch;
L_002d9d74:
 STEP(UINT32_C(0x002d9d74)); /* 0005283f dsra32 a1,a1,0 */
 set(m,5u,(uint64_t)((int64_t)lo(m,5u)>>32u));target=sx(UINT32_C(0x002d9d78));goto dispatch;
L_002d9d78:
 STEP(UINT32_C(0x002d9d78)); /* 14600007 bne v1,zero,002d9d98 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002d9d7c));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d9d98):UINT32_C(0x002d9d80));goto dispatch;}
L_002d9d7c:
 STEP(UINT32_C(0x002d9d7c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9d80));goto dispatch;
L_002d9d80:
 STEP(UINT32_C(0x002d9d80)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9d84));goto dispatch;
L_002d9d84:
 STEP(UINT32_C(0x002d9d84)); /* 8c43c248 lw v1,-0x3db8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc248),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9d88));goto dispatch;
L_002d9d88:
 STEP(UINT32_C(0x002d9d88)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9d8c));goto dispatch;
L_002d9d8c:
 STEP(UINT32_C(0x002d9d8c)); /* 00e31823 subu v1,a3,v1 */
 set(m,3u,sx((uint32_t)lo(m,7u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d9d90));goto dispatch;
L_002d9d90:
 STEP(UINT32_C(0x002d9d90)); /* ac43c260 sw v1,-0x3da0(v0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffffc260),&value32,4u);target=sx(UINT32_C(0x002d9d94));goto dispatch;
L_002d9d94:
 STEP(UINT32_C(0x002d9d94)); /* acc50004 sw a1,0x4(a2) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d9d98));goto dispatch;
L_002d9d98:
 STEP(UINT32_C(0x002d9d98)); /* 0c0b51a6 jal 002d4698 */
 set(m,31u,UINT64_C(0x002d9da0));STEP(UINT32_C(0x002d9d9c));/* nop */target=sx(UINT32_C(0x002d4698));goto dispatch;
L_002d9d9c:
 STEP(UINT32_C(0x002d9d9c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9da0));goto dispatch;
L_002d9da0:
 STEP(UINT32_C(0x002d9da0)); /* 1000000e beq zero,zero,002d9ddc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9da4));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d9ddc):UINT32_C(0x002d9da8));goto dispatch;}
L_002d9da4:
 STEP(UINT32_C(0x002d9da4)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9da8));goto dispatch;
L_002d9da8:
 STEP(UINT32_C(0x002d9da8)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d9dac));goto dispatch;
L_002d9dac:
 STEP(UINT32_C(0x002d9dac)); /* 0250182f dsubu v1,s2,s0 */
 set(m,3u,lo(m,18u)-lo(m,16u));target=sx(UINT32_C(0x002d9db0));goto dispatch;
L_002d9db0:
 STEP(UINT32_C(0x002d9db0)); /* 8e850008 lw a1,0x8(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000008),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d9db4));goto dispatch;
L_002d9db4:
 STEP(UINT32_C(0x002d9db4)); /* 00621825 or v1,v1,v0 */
 set(m,3u,lo(m,3u)|lo(m,2u));target=sx(UINT32_C(0x002d9db8));goto dispatch;
L_002d9db8:
 STEP(UINT32_C(0x002d9db8)); /* 0003183c dsll32 v1,v1,0 */
 set(m,3u,lo(m,3u)<<32u);target=sx(UINT32_C(0x002d9dbc));goto dispatch;
L_002d9dbc:
 STEP(UINT32_C(0x002d9dbc)); /* 0003183f dsra32 v1,v1,0 */
 set(m,3u,(uint64_t)((int64_t)lo(m,3u)>>32u));target=sx(UINT32_C(0x002d9dc0));goto dispatch;
L_002d9dc0:
 STEP(UINT32_C(0x002d9dc0)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9dc4));goto dispatch;
L_002d9dc4:
 STEP(UINT32_C(0x002d9dc4)); /* aca30004 sw v1,0x4(a1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d9dc8));goto dispatch;
L_002d9dc8:
 STEP(UINT32_C(0x002d9dc8)); /* 8ce20000 lw v0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9dcc));goto dispatch;
L_002d9dcc:
 STEP(UINT32_C(0x002d9dcc)); /* 00531023 subu v0,v0,s3 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,19u)));target=sx(UINT32_C(0x002d9dd0));goto dispatch;
L_002d9dd0:
 STEP(UINT32_C(0x002d9dd0)); /* 0c0b51a6 jal 002d4698 */
 set(m,31u,UINT64_C(0x002d9dd8));STEP(UINT32_C(0x002d9dd4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d4698));goto dispatch;
L_002d9dd4:
 STEP(UINT32_C(0x002d9dd4)); /* ace20000 sw v0,0x0(a3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d9dd8));goto dispatch;
L_002d9dd8:
 STEP(UINT32_C(0x002d9dd8)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d9ddc));goto dispatch;
L_002d9ddc:
 STEP(UINT32_C(0x002d9ddc)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d9de0));goto dispatch;
L_002d9de0:
 STEP(UINT32_C(0x002d9de0)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d9de4));goto dispatch;
L_002d9de4:
 STEP(UINT32_C(0x002d9de4)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002d9de8));goto dispatch;
L_002d9de8:
 STEP(UINT32_C(0x002d9de8)); /* dfb30018 ld s3,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002d9dec));goto dispatch;
L_002d9dec:
 STEP(UINT32_C(0x002d9dec)); /* dfb40020 ld s4,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002d9df0));goto dispatch;
L_002d9df0:
 STEP(UINT32_C(0x002d9df0)); /* dfbf0028 ld ra,0x28(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d9df4));goto dispatch;
L_002d9df4:
 STEP(UINT32_C(0x002d9df4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d9df8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002d9df8:
 STEP(UINT32_C(0x002d9df8)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002d9dfc));goto dispatch;
L_002d4618:
 STEP(UINT32_C(0x002d4618)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d461c));goto dispatch;
L_002d461c:
 STEP(UINT32_C(0x002d461c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d4620));goto dispatch;
L_002d4620:
 STEP(UINT32_C(0x002d4620)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d4624));goto dispatch;
L_002d4624:
 STEP(UINT32_C(0x002d4624)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d4628));goto dispatch;
L_002d4628:
 STEP(UINT32_C(0x002d4628)); /* 0c0b6f64 jal 002dbd90 */
 set(m,31u,UINT64_C(0x002d4630));STEP(UINT32_C(0x002d462c));/* nop */target=sx(UINT32_C(0x002dbd90));goto dispatch;
L_002d462c:
 STEP(UINT32_C(0x002d462c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4630));goto dispatch;
L_002d4630:
 STEP(UINT32_C(0x002d4630)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d4634));goto dispatch;
L_002d4634:
 STEP(UINT32_C(0x002d4634)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d4638));goto dispatch;
L_002d4638:
 STEP(UINT32_C(0x002d4638)); /* 2471c288 addiu s1,v1,-15736 */
 set(m,17u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffc288)));target=sx(UINT32_C(0x002d463c));goto dispatch;
L_002d463c:
 STEP(UINT32_C(0x002d463c)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d4640));goto dispatch;
L_002d4640:
 STEP(UINT32_C(0x002d4640)); /* 2444c28c addiu a0,v0,-15732 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffc28c)));target=sx(UINT32_C(0x002d4644));goto dispatch;
L_002d4644:
 STEP(UINT32_C(0x002d4644)); /* 8e220000 lw v0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4648));goto dispatch;
L_002d4648:
 STEP(UINT32_C(0x002d4648)); /* 14500005 bne v0,s0,002d4660 */
 {int taken=(lo(m,2u)!=lo(m,16u));STEP(UINT32_C(0x002d464c));set(m,2u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002d4660):UINT32_C(0x002d4650));goto dispatch;}
L_002d464c:
 STEP(UINT32_C(0x002d464c)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d4650));goto dispatch;
L_002d4650:
 STEP(UINT32_C(0x002d4650)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4654));goto dispatch;
L_002d4654:
 STEP(UINT32_C(0x002d4654)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4658));goto dispatch;
L_002d4658:
 STEP(UINT32_C(0x002d4658)); /* 10000009 beq zero,zero,002d4680 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d465c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002d4680):UINT32_C(0x002d4660));goto dispatch;}
L_002d465c:
 STEP(UINT32_C(0x002d465c)); /* ac820000 sw v0,0x0(a0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d4660));goto dispatch;
L_002d4660:
 STEP(UINT32_C(0x002d4660)); /* 0c0b6fb8 jal 002dbee0 */
 set(m,31u,UINT64_C(0x002d4668));STEP(UINT32_C(0x002d4664));READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc378),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbee0));goto dispatch;
L_002d4664:
 STEP(UINT32_C(0x002d4664)); /* 8c44c378 lw a0,-0x3c88(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc378),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d4668));goto dispatch;
L_002d4668:
 STEP(UINT32_C(0x002d4668)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d466c));goto dispatch;
L_002d466c:
 STEP(UINT32_C(0x002d466c)); /* ae300000 sw s0,0x0(s1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d4670));goto dispatch;
L_002d4670:
 STEP(UINT32_C(0x002d4670)); /* 2463c28c addiu v1,v1,-15732 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffc28c)));target=sx(UINT32_C(0x002d4674));goto dispatch;
L_002d4674:
 STEP(UINT32_C(0x002d4674)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d4678));goto dispatch;
L_002d4678:
 STEP(UINT32_C(0x002d4678)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d467c));goto dispatch;
L_002d467c:
 STEP(UINT32_C(0x002d467c)); /* ac620000 sw v0,0x0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d4680));goto dispatch;
L_002d4680:
 STEP(UINT32_C(0x002d4680)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d4684));goto dispatch;
L_002d4684:
 STEP(UINT32_C(0x002d4684)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d4688));goto dispatch;
L_002d4688:
 STEP(UINT32_C(0x002d4688)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d468c));goto dispatch;
L_002d468c:
 STEP(UINT32_C(0x002d468c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d4690));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002d4690:
 STEP(UINT32_C(0x002d4690)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d4694));goto dispatch;
L_002d4698:
 STEP(UINT32_C(0x002d4698)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d469c));goto dispatch;
L_002d469c:
 STEP(UINT32_C(0x002d469c)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d46a0));goto dispatch;
L_002d46a0:
 STEP(UINT32_C(0x002d46a0)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d46a4));goto dispatch;
L_002d46a4:
 STEP(UINT32_C(0x002d46a4)); /* 2463c28c addiu v1,v1,-15732 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffc28c)));target=sx(UINT32_C(0x002d46a8));goto dispatch;
L_002d46a8:
 STEP(UINT32_C(0x002d46a8)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d46ac));goto dispatch;
L_002d46ac:
 STEP(UINT32_C(0x002d46ac)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d46b0));goto dispatch;
L_002d46b0:
 STEP(UINT32_C(0x002d46b0)); /* 14400009 bne v0,zero,002d46d8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d46b4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002d46d8):UINT32_C(0x002d46b8));goto dispatch;}
L_002d46b4:
 STEP(UINT32_C(0x002d46b4)); /* ac620000 sw v0,0x0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d46b8));goto dispatch;
L_002d46b8:
 STEP(UINT32_C(0x002d46b8)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d46bc));goto dispatch;
L_002d46bc:
 STEP(UINT32_C(0x002d46bc)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d46c0));goto dispatch;
L_002d46c0:
 STEP(UINT32_C(0x002d46c0)); /* 8c44c378 lw a0,-0x3c88(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffc378),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d46c4));goto dispatch;
L_002d46c4:
 STEP(UINT32_C(0x002d46c4)); /* 3c050053 lui a1,zero,0x53 */
 set(m,5u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d46c8));goto dispatch;
L_002d46c8:
 STEP(UINT32_C(0x002d46c8)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d46cc));goto dispatch;
L_002d46cc:
 STEP(UINT32_C(0x002d46cc)); /* aca3c288 sw v1,-0x3d78(a1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0xffffc288),&value32,4u);target=sx(UINT32_C(0x002d46d0));goto dispatch;
L_002d46d0:
 STEP(UINT32_C(0x002d46d0)); /* 080b6fb0 j 002dbec0 */
 STEP(UINT32_C(0x002d46d4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002d46d4:
 STEP(UINT32_C(0x002d46d4)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d46d8));goto dispatch;
L_002d46d8:
 STEP(UINT32_C(0x002d46d8)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d46dc));goto dispatch;
L_002d46dc:
 STEP(UINT32_C(0x002d46dc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d46e0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002d46e0:
 STEP(UINT32_C(0x002d46e0)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d46e4));goto dispatch;
L_002d5250:
 STEP(UINT32_C(0x002d5250)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d5254));goto dispatch;
L_002d5254:
 STEP(UINT32_C(0x002d5254)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d5258));goto dispatch;
L_002d5258:
 STEP(UINT32_C(0x002d5258)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d525c));goto dispatch;
L_002d525c:
 STEP(UINT32_C(0x002d525c)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d5260));goto dispatch;
L_002d5260:
 STEP(UINT32_C(0x002d5260)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d5264));goto dispatch;
L_002d5264:
 STEP(UINT32_C(0x002d5264)); /* 24512178 addiu s1,v0,8568 */
 set(m,17u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00002178)));target=sx(UINT32_C(0x002d5268));goto dispatch;
L_002d5268:
 STEP(UINT32_C(0x002d5268)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d526c));goto dispatch;
L_002d526c:
 STEP(UINT32_C(0x002d526c)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d5270));goto dispatch;
L_002d5270:
 STEP(UINT32_C(0x002d5270)); /* 0c0b7168 jal 002dc5a0 */
 set(m,31u,UINT64_C(0x002d5278));STEP(UINT32_C(0x002d5274));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002dc5a0));goto dispatch;
L_002d5274:
 STEP(UINT32_C(0x002d5274)); /* ae200000 sw zero,0x0(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d5278));goto dispatch;
L_002d5278:
 STEP(UINT32_C(0x002d5278)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d527c));goto dispatch;
L_002d527c:
 STEP(UINT32_C(0x002d527c)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d5280));goto dispatch;
L_002d5280:
 STEP(UINT32_C(0x002d5280)); /* 54830005 bnel a0,v1,002d5298 */
 if(lo(m,4u)!=lo(m,3u)){STEP(UINT32_C(0x002d5284));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d5298));}else target=sx(UINT32_C(0x002d5288));goto dispatch;
L_002d5284:
 STEP(UINT32_C(0x002d5284)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d5288));goto dispatch;
L_002d5288:
 STEP(UINT32_C(0x002d5288)); /* 8e230000 lw v1,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d528c));goto dispatch;
L_002d528c:
 STEP(UINT32_C(0x002d528c)); /* 54600001 bnel v1,zero,002d5294 */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x002d5290));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d5294));}else target=sx(UINT32_C(0x002d5294));goto dispatch;
L_002d5290:
 STEP(UINT32_C(0x002d5290)); /* ae030000 sw v1,0x0(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d5294));goto dispatch;
L_002d5294:
 STEP(UINT32_C(0x002d5294)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d5298));goto dispatch;
L_002d5298:
 STEP(UINT32_C(0x002d5298)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d529c));goto dispatch;
L_002d529c:
 STEP(UINT32_C(0x002d529c)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d52a0));goto dispatch;
L_002d52a0:
 STEP(UINT32_C(0x002d52a0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d52a4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002d52a4:
 STEP(UINT32_C(0x002d52a4)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d52a8));goto dispatch;
L_002dc5a0:
 STEP(UINT32_C(0x002dc5a0)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002dc5a4));goto dispatch;
L_002dc5a4:
 STEP(UINT32_C(0x002dc5a4)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002dc5a8));goto dispatch;
L_002dc5a8:
 STEP(UINT32_C(0x002dc5a8)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dc5ac));goto dispatch;
L_002dc5ac:
 STEP(UINT32_C(0x002dc5ac)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dc5b0));goto dispatch;
L_002dc5b0:
 STEP(UINT32_C(0x002dc5b0)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dc5b4));goto dispatch;
L_002dc5b4:
 STEP(UINT32_C(0x002dc5b4)); /* 40116000 cop0 rs0 rts1 rd12 fn0 */
 set(m,17u,sx(m->status));target=sx(UINT32_C(0x002dc5b8));goto dispatch;
L_002dc5b8:
 STEP(UINT32_C(0x002dc5b8)); /* 3c020001 lui v0,zero,0x1 */
 set(m,2u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x002dc5bc));goto dispatch;
L_002dc5bc:
 STEP(UINT32_C(0x002dc5bc)); /* 02228824 and s1,s1,v0 */
 set(m,17u,lo(m,17u)&lo(m,2u));target=sx(UINT32_C(0x002dc5c0));goto dispatch;
L_002dc5c0:
 STEP(UINT32_C(0x002dc5c0)); /* 1220000a beq s1,zero,002dc5ec */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002dc5c4));set(m,18u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002dc5ec):UINT32_C(0x002dc5c8));goto dispatch;}
L_002dc5c4:
 STEP(UINT32_C(0x002dc5c4)); /* 3c120053 lui s2,zero,0x53 */
 set(m,18u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002dc5c8));goto dispatch;
L_002dc5c8:
 STEP(UINT32_C(0x002dc5c8)); /* 42000039 cop0 rs16 rtzero rd0 fn57 */
 if((m->status&UINT32_C(0x20006))||(m->status&UINT32_C(0x18))==0u)m->status&=~UINT32_C(0x10000); /* Original EDI/EXL/ERL/KSU permission. */target=sx(UINT32_C(0x002dc5cc));goto dispatch;
L_002dc5cc:
 STEP(UINT32_C(0x002dc5cc)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x002dc5d0));goto dispatch;
L_002dc5d0:
 STEP(UINT32_C(0x002dc5d0)); /* 40026000 cop0 rs0 rtv0 rd12 fn0 */
 set(m,2u,sx(m->status));target=sx(UINT32_C(0x002dc5d4));goto dispatch;
L_002dc5d4:
 STEP(UINT32_C(0x002dc5d4)); /* 3c030001 lui v1,zero,0x1 */
 set(m,3u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x002dc5d8));goto dispatch;
L_002dc5d8:
 STEP(UINT32_C(0x002dc5d8)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002dc5dc));goto dispatch;
L_002dc5dc:
 STEP(UINT32_C(0x002dc5dc)); /* 1440fffa bne v0,zero,002dc5c8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dc5e0));/* nop */target=sx(taken?UINT32_C(0x002dc5c8):UINT32_C(0x002dc5e4));goto dispatch;}
L_002dc5e0:
 STEP(UINT32_C(0x002dc5e0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc5e4));goto dispatch;
L_002dc5e4:
 STEP(UINT32_C(0x002dc5e4)); /* 10000002 beq zero,zero,002dc5f0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dc5e8));READ((uint32_t)lo(m,18u)+UINT32_C(0xffffc2a8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002dc5f0):UINT32_C(0x002dc5ec));goto dispatch;}
L_002dc5e8:
 STEP(UINT32_C(0x002dc5e8)); /* 8e42c2a8 lw v0,-0x3d58(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffc2a8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dc5ec));goto dispatch;
L_002dc5ec:
 STEP(UINT32_C(0x002dc5ec)); /* 8e42c2a8 lw v0,-0x3d58(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffc2a8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dc5f0));goto dispatch;
L_002dc5f0:
 STEP(UINT32_C(0x002dc5f0)); /* 0c0b6fa0 jal 002dbe80 */
 set(m,31u,UINT64_C(0x002dc5f8));STEP(UINT32_C(0x002dc5f4));set(m,16u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002dbe80));goto dispatch;
L_002dc5f4:
 STEP(UINT32_C(0x002dc5f4)); /* 00448021 addu s0,v0,a0 */
 set(m,16u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002dc5f8));goto dispatch;
L_002dc5f8:
 STEP(UINT32_C(0x002dc5f8)); /* 0050102b sltu v0,v0,s0 */
 set(m,2u,lo(m,2u)<lo(m,16u));target=sx(UINT32_C(0x002dc5fc));goto dispatch;
L_002dc5fc:
 STEP(UINT32_C(0x002dc5fc)); /* 1040000a beq v0,zero,002dc628 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002dc600));READ((uint32_t)lo(m,18u)+UINT32_C(0xffffc2a8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002dc628):UINT32_C(0x002dc604));goto dispatch;}
L_002dc600:
 STEP(UINT32_C(0x002dc600)); /* 8e42c2a8 lw v0,-0x3d58(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffc2a8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dc604));goto dispatch;
L_002dc604:
 STEP(UINT32_C(0x002dc604)); /* 0c0b9b8c jal 002e6e30 */
 set(m,31u,UINT64_C(0x002dc60c));STEP(UINT32_C(0x002dc608));/* nop */target=sx(UINT32_C(0x002e6e30));goto dispatch;
L_002dc608:
 STEP(UINT32_C(0x002dc608)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc60c));goto dispatch;
L_002dc60c:
 STEP(UINT32_C(0x002dc60c)); /* 2403000c addiu v1,zero,12 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002dc610));goto dispatch;
L_002dc610:
 STEP(UINT32_C(0x002dc610)); /* 12200002 beq s1,zero,002dc61c */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002dc614));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002dc61c):UINT32_C(0x002dc618));goto dispatch;}
L_002dc614:
 STEP(UINT32_C(0x002dc614)); /* ac430000 sw v1,0x0(v0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002dc618));goto dispatch;
L_002dc618:
 STEP(UINT32_C(0x002dc618)); /* 42000038 cop0 rs16 rtzero rd0 fn56 */
 if((m->status&UINT32_C(0x20006))||(m->status&UINT32_C(0x18))==0u)m->status|=UINT32_C(0x10000); /* Original EDI/EXL/ERL/KSU permission. */target=sx(UINT32_C(0x002dc61c));goto dispatch;
L_002dc61c:
 STEP(UINT32_C(0x002dc61c)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002dc620));goto dispatch;
L_002dc620:
 STEP(UINT32_C(0x002dc620)); /* 10000004 beq zero,zero,002dc634 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dc624));set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(taken?UINT32_C(0x002dc634):UINT32_C(0x002dc628));goto dispatch;}
L_002dc624:
 STEP(UINT32_C(0x002dc624)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002dc628));goto dispatch;
L_002dc628:
 STEP(UINT32_C(0x002dc628)); /* 12200002 beq s1,zero,002dc634 */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002dc62c));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0xffffc2a8),&value32,4u);target=sx(taken?UINT32_C(0x002dc634):UINT32_C(0x002dc630));goto dispatch;}
L_002dc62c:
 STEP(UINT32_C(0x002dc62c)); /* ae50c2a8 sw s0,-0x3d58(s2) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0xffffc2a8),&value32,4u);target=sx(UINT32_C(0x002dc630));goto dispatch;
L_002dc630:
 STEP(UINT32_C(0x002dc630)); /* 42000038 cop0 rs16 rtzero rd0 fn56 */
 if((m->status&UINT32_C(0x20006))||(m->status&UINT32_C(0x18))==0u)m->status|=UINT32_C(0x10000); /* Original EDI/EXL/ERL/KSU permission. */target=sx(UINT32_C(0x002dc634));goto dispatch;
L_002dc634:
 STEP(UINT32_C(0x002dc634)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dc638));goto dispatch;
L_002dc638:
 STEP(UINT32_C(0x002dc638)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002dc63c));goto dispatch;
L_002dc63c:
 STEP(UINT32_C(0x002dc63c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dc640));goto dispatch;
L_002dc640:
 STEP(UINT32_C(0x002dc640)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dc644));goto dispatch;
L_002dc644:
 STEP(UINT32_C(0x002dc644)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc648));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002dc648:
 STEP(UINT32_C(0x002dc648)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dc64c));goto dispatch;
L_002e40d0:
 STEP(UINT32_C(0x002e40d0)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x002e40d4));goto dispatch;
L_002e40d4:
 STEP(UINT32_C(0x002e40d4)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002e40d8));goto dispatch;
L_002e40d8:
 STEP(UINT32_C(0x002e40d8)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002e40dc));goto dispatch;
L_002e40dc:
 STEP(UINT32_C(0x002e40dc)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002e40e0));goto dispatch;
L_002e40e0:
 STEP(UINT32_C(0x002e40e0)); /* afa20028 sw v0,0x28(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x002e40e4));goto dispatch;
L_002e40e4:
 STEP(UINT32_C(0x002e40e4)); /* afa20004 sw v0,0x4(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002e40e8));goto dispatch;
L_002e40e8:
 STEP(UINT32_C(0x002e40e8)); /* afa20008 sw v0,0x8(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002e40ec));goto dispatch;
L_002e40ec:
 STEP(UINT32_C(0x002e40ec)); /* 0c0b6fa8 jal 002dbea0 */
 set(m,31u,UINT64_C(0x002e40f4));STEP(UINT32_C(0x002e40f0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002dbea0));goto dispatch;
L_002e40f0:
 STEP(UINT32_C(0x002e40f0)); /* afa20024 sw v0,0x24(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002e40f4));goto dispatch;
L_002e40f4:
 STEP(UINT32_C(0x002e40f4)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e40f8));goto dispatch;
L_002e40f8:
 STEP(UINT32_C(0x002e40f8)); /* 27a40020 addiu a0,sp,32 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e40fc));goto dispatch;
L_002e40fc:
 STEP(UINT32_C(0x002e40fc)); /* 0c0b6fa8 jal 002dbea0 */
 set(m,31u,UINT64_C(0x002e4104));STEP(UINT32_C(0x002e4100));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffc378),&value32,4u);target=sx(UINT32_C(0x002dbea0));goto dispatch;
L_002e4100:
 STEP(UINT32_C(0x002e4100)); /* ac62c378 sw v0,-0x3c88(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffc378),&value32,4u);target=sx(UINT32_C(0x002e4104));goto dispatch;
L_002e4104:
 STEP(UINT32_C(0x002e4104)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e4108));goto dispatch;
L_002e4108:
 STEP(UINT32_C(0x002e4108)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e410c));goto dispatch;
L_002e410c:
 STEP(UINT32_C(0x002e410c)); /* ac62c37c sw v0,-0x3c84(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffc37c),&value32,4u);target=sx(UINT32_C(0x002e4110));goto dispatch;
L_002e4110:
 STEP(UINT32_C(0x002e4110)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e4114));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_002e4114:
 STEP(UINT32_C(0x002e4114)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x002e4118));goto dispatch;
L_002e6e30:
 STEP(UINT32_C(0x002e6e30)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e6e34));goto dispatch;
L_002e6e34:
 STEP(UINT32_C(0x002e6e34)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e6e38));READ((uint32_t)lo(m,3u)+UINT32_C(0xffffbe28),&value32,4u);set(m,2u,sx(value32));goto dispatch;
L_002e6e38:
 STEP(UINT32_C(0x002e6e38)); /* 8c62be28 lw v0,-0x41d8(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffbe28),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e6e3c));goto dispatch;
L_002dbe80:
 STEP(UINT32_C(0x002dbe80)); /* 2403003e addiu v1,zero,62 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000003e)));target=sx(UINT32_C(0x002dbe84));goto dispatch;
L_002dbe84:
 m->pc=UINT32_C(0x002dbe84); /* Router executes actual SYS once. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbe88:
 STEP(UINT32_C(0x002dbe88)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbe8c));/* nop */goto dispatch;
L_002dbe8c:
 STEP(UINT32_C(0x002dbe8c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbe90));goto dispatch;
L_002dbec0:
 STEP(UINT32_C(0x002dbec0)); /* 24030042 addiu v1,zero,66 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000042)));target=sx(UINT32_C(0x002dbec4));goto dispatch;
L_002dbec4:
 m->pc=UINT32_C(0x002dbec4); /* Router executes actual SYS once. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbec8:
 STEP(UINT32_C(0x002dbec8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbecc));/* nop */goto dispatch;
L_002dbecc:
 STEP(UINT32_C(0x002dbecc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbed0));goto dispatch;
L_800034c0:
 STEP(UINT32_C(0x800034c0)); /* 0c000da0 jal 80003680 */
 set(m,31u,UINT64_C(0x800034c8));STEP(UINT32_C(0x800034c4));set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003680));goto dispatch;
L_800034c4:
 STEP(UINT32_C(0x800034c4)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x800034c8));goto dispatch;
L_800034c8:
 STEP(UINT32_C(0x800034c8)); /* 0c0012f2 jal 80004bc8 */
 set(m,31u,UINT64_C(0x800034d0));STEP(UINT32_C(0x800034cc));/* nop */target=sx(UINT32_C(0x80004bc8));goto dispatch;
L_800034cc:
 STEP(UINT32_C(0x800034cc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800034d0));goto dispatch;
L_800034d0:
 STEP(UINT32_C(0x800034d0)); /* 0440000e regimm0 v0,8000350c */
 {int taken=((int64_t)lo(m,2u)<0);STEP(UINT32_C(0x800034d4));/* nop */target=sx(taken?UINT32_C(0x8000350c):UINT32_C(0x800034d8));goto dispatch;}
L_800034d4:
 STEP(UINT32_C(0x800034d4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800034d8));goto dispatch;
L_800034d8:
 STEP(UINT32_C(0x800034d8)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800034dc));goto dispatch;
L_800034dc:
 STEP(UINT32_C(0x800034dc)); /* 40047000 cop0 rs0 rta0 rd14 fn0 */
 set(m,4u,sx(m->epc));target=sx(UINT32_C(0x800034e0));goto dispatch;
L_800034e0:
 STEP(UINT32_C(0x800034e0)); /* 0c000e50 jal 80003940 */
 set(m,31u,UINT64_C(0x800034e8));STEP(UINT32_C(0x800034e4));READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003940));goto dispatch;
L_800034e4:
 STEP(UINT32_C(0x800034e4)); /* 8ca510c0 lw a1,0x10c0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x800034e8));goto dispatch;
L_800034e8:
 STEP(UINT32_C(0x800034e8)); /* 40827000 cop0 rs4 rtv0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x800034ec));goto dispatch;
L_800034ec:
 STEP(UINT32_C(0x800034ec)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x800034f0));goto dispatch;
L_800034f0:
 STEP(UINT32_C(0x800034f0)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x800034f8));STEP(UINT32_C(0x800034f4));set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003800));goto dispatch;
L_800034f4:
 STEP(UINT32_C(0x800034f4)); /* 0060e82d daddu sp,v1,zero */
 set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x800034f8));goto dispatch;
L_800034f8:
 STEP(UINT32_C(0x800034f8)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x800034fc));goto dispatch;
L_800034fc:
 STEP(UINT32_C(0x800034fc)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x80003500));goto dispatch;
L_80003500:
 STEP(UINT32_C(0x80003500)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003504));goto dispatch;
L_80003504:
 STEP(UINT32_C(0x80003504)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003508));goto dispatch;
L_80003508:
 STEP(UINT32_C(0x80003508)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_8000350c:
 STEP(UINT32_C(0x8000350c)); /* 3c1d8000 lui sp,zero,0x8000 */
 set(m,29u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003510));goto dispatch;
L_80003510:
 STEP(UINT32_C(0x80003510)); /* 8fbd10c0 lw sp,0x10c0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000010c0),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x80003514));goto dispatch;
L_80003514:
 STEP(UINT32_C(0x80003514)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x8000351c));STEP(UINT32_C(0x80003518));value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80003800));goto dispatch;
L_80003518:
 STEP(UINT32_C(0x80003518)); /* ffa20020 sd v0,0x20(sp) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000351c));goto dispatch;
L_8000351c:
 STEP(UINT32_C(0x8000351c)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x80003520));goto dispatch;
L_80003520:
 STEP(UINT32_C(0x80003520)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x80003524));goto dispatch;
L_80003524:
 STEP(UINT32_C(0x80003524)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003528));goto dispatch;
L_80003528:
 STEP(UINT32_C(0x80003528)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x8000352c));goto dispatch;
L_8000352c:
 STEP(UINT32_C(0x8000352c)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80003530:
 STEP(UINT32_C(0x80003530)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003534));goto dispatch;
L_80003534:
 STEP(UINT32_C(0x80003534)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003538));goto dispatch;
L_80003538:
 STEP(UINT32_C(0x80003538)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000353c));goto dispatch;
L_8000353c:
 STEP(UINT32_C(0x8000353c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003540));goto dispatch;
L_800052d8:
 STEP(UINT32_C(0x800052d8)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800052dc));goto dispatch;
L_800052dc:
 STEP(UINT32_C(0x800052dc)); /* 8c6325ec lw v1,0x25ec(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x000025ec),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x800052e0));goto dispatch;
L_800052e0:
 STEP(UINT32_C(0x800052e0)); /* 2402004c addiu v0,zero,76 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x800052e4));goto dispatch;
L_800052e4:
 STEP(UINT32_C(0x800052e4)); /* 00621818 mult_rd v1,v1,v0 */
 {int64_t product;if(lo(m,3u)!=sx((uint32_t)lo(m,3u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,3u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x800052e8));goto dispatch;
L_800052e8:
 STEP(UINT32_C(0x800052e8)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800052ec));goto dispatch;
L_800052ec:
 STEP(UINT32_C(0x800052ec)); /* 00431021 addu v0,v0,v1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x800052f0));goto dispatch;
L_800052f0:
 STEP(UINT32_C(0x800052f0)); /* 8c427448 lw v0,0x7448(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00007448),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800052f4));goto dispatch;
L_800052f4:
 STEP(UINT32_C(0x800052f4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800052f8));/* nop */goto dispatch;
L_800052f8:
 STEP(UINT32_C(0x800052f8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800052fc));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

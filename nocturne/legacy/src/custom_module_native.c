#include "custom_module_native.h"
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
uint32_t nocturneCustomModuleResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002a98a8):goto L_002a98a8;
 case UINT32_C(0x002a98ac):goto L_002a98ac;
 case UINT32_C(0x002a98b0):goto L_002a98b0;
 case UINT32_C(0x002a98b4):goto L_002a98b4;
 case UINT32_C(0x002a98b8):goto L_002a98b8;
 case UINT32_C(0x002a98bc):goto L_002a98bc;
 case UINT32_C(0x002a98c0):goto L_002a98c0;
 case UINT32_C(0x002a98c4):goto L_002a98c4;
 case UINT32_C(0x002a98c8):goto L_002a98c8;
 case UINT32_C(0x002a98cc):goto L_002a98cc;
 case UINT32_C(0x002a98d0):goto L_002a98d0;
 case UINT32_C(0x002a98d4):goto L_002a98d4;
 case UINT32_C(0x002a98d8):goto L_002a98d8;
 case UINT32_C(0x002a98dc):goto L_002a98dc;
 case UINT32_C(0x002a98e0):goto L_002a98e0;
 case UINT32_C(0x002a98e4):goto L_002a98e4;
 case UINT32_C(0x002a98e8):goto L_002a98e8;
 case UINT32_C(0x002a98ec):goto L_002a98ec;
 case UINT32_C(0x002a98f0):goto L_002a98f0;
 case UINT32_C(0x002a98f4):goto L_002a98f4;
 case UINT32_C(0x002a98f8):goto L_002a98f8;
 case UINT32_C(0x002a98fc):goto L_002a98fc;
 case UINT32_C(0x002a9900):goto L_002a9900;
 case UINT32_C(0x002a9904):goto L_002a9904;
 case UINT32_C(0x002a9908):goto L_002a9908;
 case UINT32_C(0x002a990c):goto L_002a990c;
 case UINT32_C(0x002a9910):goto L_002a9910;
 case UINT32_C(0x002a9914):goto L_002a9914;
 case UINT32_C(0x002a9918):goto L_002a9918;
 case UINT32_C(0x002a991c):goto L_002a991c;
 case UINT32_C(0x002a9920):goto L_002a9920;
 case UINT32_C(0x002a9924):goto L_002a9924;
 case UINT32_C(0x002a9928):goto L_002a9928;
 case UINT32_C(0x002a992c):goto L_002a992c;
 case UINT32_C(0x002a9930):goto L_002a9930;
 case UINT32_C(0x002a9934):goto L_002a9934;
 case UINT32_C(0x002a9938):goto L_002a9938;
 case UINT32_C(0x002a993c):goto L_002a993c;
 case UINT32_C(0x002a9940):goto L_002a9940;
 case UINT32_C(0x002a9944):goto L_002a9944;
 case UINT32_C(0x002a9948):goto L_002a9948;
 case UINT32_C(0x002a994c):goto L_002a994c;
 case UINT32_C(0x002a9950):goto L_002a9950;
 case UINT32_C(0x002a9954):goto L_002a9954;
 case UINT32_C(0x002a9958):goto L_002a9958;
 case UINT32_C(0x002a995c):goto L_002a995c;
 case UINT32_C(0x002a9960):goto L_002a9960;
 case UINT32_C(0x002a9964):goto L_002a9964;
 case UINT32_C(0x002a9968):goto L_002a9968;
 case UINT32_C(0x002a996c):goto L_002a996c;
 case UINT32_C(0x002a9970):goto L_002a9970;
 case UINT32_C(0x002a9974):goto L_002a9974;
 case UINT32_C(0x002a9978):goto L_002a9978;
 case UINT32_C(0x002a997c):goto L_002a997c;
 case UINT32_C(0x002a9980):goto L_002a9980;
 case UINT32_C(0x002a9984):goto L_002a9984;
 case UINT32_C(0x002a9988):goto L_002a9988;
 case UINT32_C(0x002a998c):goto L_002a998c;
 case UINT32_C(0x002a9990):goto L_002a9990;
 case UINT32_C(0x002a9994):goto L_002a9994;
 case UINT32_C(0x002a9998):goto L_002a9998;
 case UINT32_C(0x002a999c):goto L_002a999c;
 case UINT32_C(0x002a99a0):goto L_002a99a0;
 case UINT32_C(0x002a99a4):goto L_002a99a4;
 case UINT32_C(0x002a99a8):goto L_002a99a8;
 case UINT32_C(0x002a99ac):goto L_002a99ac;
 case UINT32_C(0x002a9038):goto L_002a9038;
 case UINT32_C(0x002a903c):goto L_002a903c;
 case UINT32_C(0x002a9040):goto L_002a9040;
 case UINT32_C(0x002a9044):goto L_002a9044;
 case UINT32_C(0x002a9048):goto L_002a9048;
 case UINT32_C(0x002a904c):goto L_002a904c;
 case UINT32_C(0x002a9050):goto L_002a9050;
 case UINT32_C(0x002a9054):goto L_002a9054;
 case UINT32_C(0x002a9058):goto L_002a9058;
 case UINT32_C(0x002a905c):goto L_002a905c;
 case UINT32_C(0x002a9060):goto L_002a9060;
 case UINT32_C(0x002a9064):goto L_002a9064;
 case UINT32_C(0x002a9068):goto L_002a9068;
 case UINT32_C(0x002a906c):goto L_002a906c;
 case UINT32_C(0x002a9070):goto L_002a9070;
 case UINT32_C(0x002a9074):goto L_002a9074;
 case UINT32_C(0x002a9078):goto L_002a9078;
 case UINT32_C(0x002a907c):goto L_002a907c;
 case UINT32_C(0x002a9080):goto L_002a9080;
 case UINT32_C(0x002a9084):goto L_002a9084;
 case UINT32_C(0x002a9088):goto L_002a9088;
 case UINT32_C(0x002a908c):goto L_002a908c;
 case UINT32_C(0x002a9090):goto L_002a9090;
 case UINT32_C(0x002a9094):goto L_002a9094;
 case UINT32_C(0x002a9098):goto L_002a9098;
 case UINT32_C(0x002a909c):goto L_002a909c;
 case UINT32_C(0x002a90a0):goto L_002a90a0;
 case UINT32_C(0x002a90a4):goto L_002a90a4;
 case UINT32_C(0x002a90a8):goto L_002a90a8;
 case UINT32_C(0x002a90ac):goto L_002a90ac;
 case UINT32_C(0x002a90b0):goto L_002a90b0;
 case UINT32_C(0x002a90b4):goto L_002a90b4;
 case UINT32_C(0x002a90b8):goto L_002a90b8;
 case UINT32_C(0x002a90bc):goto L_002a90bc;
 case UINT32_C(0x002a90c0):goto L_002a90c0;
 case UINT32_C(0x002a90c4):goto L_002a90c4;
 case UINT32_C(0x002a90c8):goto L_002a90c8;
 case UINT32_C(0x002a90cc):goto L_002a90cc;
 case UINT32_C(0x002a90d0):goto L_002a90d0;
 case UINT32_C(0x002a90d4):goto L_002a90d4;
 case UINT32_C(0x002a90d8):goto L_002a90d8;
 case UINT32_C(0x002a90dc):goto L_002a90dc;
 case UINT32_C(0x002a90e0):goto L_002a90e0;
 case UINT32_C(0x002a90e4):goto L_002a90e4;
 case UINT32_C(0x002a90e8):goto L_002a90e8;
 case UINT32_C(0x002a90ec):goto L_002a90ec;
 case UINT32_C(0x002a90f0):goto L_002a90f0;
 case UINT32_C(0x002a90f4):goto L_002a90f4;
 case UINT32_C(0x002a90f8):goto L_002a90f8;
 case UINT32_C(0x002a90fc):goto L_002a90fc;
 case UINT32_C(0x002a9100):goto L_002a9100;
 case UINT32_C(0x002a9104):goto L_002a9104;
 case UINT32_C(0x002a9108):goto L_002a9108;
 case UINT32_C(0x002a910c):goto L_002a910c;
 case UINT32_C(0x002a9110):goto L_002a9110;
 case UINT32_C(0x002a9114):goto L_002a9114;
 case UINT32_C(0x002a9118):goto L_002a9118;
 case UINT32_C(0x002a911c):goto L_002a911c;
 case UINT32_C(0x002a9120):goto L_002a9120;
 case UINT32_C(0x002a9124):goto L_002a9124;
 case UINT32_C(0x002a9128):goto L_002a9128;
 case UINT32_C(0x002a912c):goto L_002a912c;
 case UINT32_C(0x002a9130):goto L_002a9130;
 case UINT32_C(0x002a9134):goto L_002a9134;
 case UINT32_C(0x002a9138):goto L_002a9138;
 case UINT32_C(0x002a913c):goto L_002a913c;
 case UINT32_C(0x002a9140):goto L_002a9140;
 case UINT32_C(0x002a9144):goto L_002a9144;
 case UINT32_C(0x002a9148):goto L_002a9148;
 case UINT32_C(0x002a914c):goto L_002a914c;
 case UINT32_C(0x002a9150):goto L_002a9150;
 case UINT32_C(0x002a9154):goto L_002a9154;
 case UINT32_C(0x002a9688):goto L_002a9688;
 case UINT32_C(0x002a968c):goto L_002a968c;
 case UINT32_C(0x002a9690):goto L_002a9690;
 case UINT32_C(0x002a9694):goto L_002a9694;
 case UINT32_C(0x002a9698):goto L_002a9698;
 case UINT32_C(0x002d5d0c):goto L_002d5d0c;
 case UINT32_C(0x002d5d10):goto L_002d5d10;
 case UINT32_C(0x002d5d14):goto L_002d5d14;
 case UINT32_C(0x002d5d18):goto L_002d5d18;
 case UINT32_C(0x002d5d1c):goto L_002d5d1c;
 case UINT32_C(0x002d5d20):goto L_002d5d20;
 case UINT32_C(0x002d5d24):goto L_002d5d24;
 case UINT32_C(0x002d5d28):goto L_002d5d28;
 case UINT32_C(0x002d5d2c):goto L_002d5d2c;
 case UINT32_C(0x002d5d30):goto L_002d5d30;
 case UINT32_C(0x002d5d34):goto L_002d5d34;
 case UINT32_C(0x002d5d38):goto L_002d5d38;
 case UINT32_C(0x002d5d3c):goto L_002d5d3c;
 case UINT32_C(0x002d5d40):goto L_002d5d40;
 case UINT32_C(0x002d5d44):goto L_002d5d44;
 case UINT32_C(0x002d5d48):goto L_002d5d48;
 case UINT32_C(0x002d5d4c):goto L_002d5d4c;
 case UINT32_C(0x002d5d50):goto L_002d5d50;
 case UINT32_C(0x002d5d54):goto L_002d5d54;
 case UINT32_C(0x002d5d58):goto L_002d5d58;
 case UINT32_C(0x002d5d5c):goto L_002d5d5c;
 case UINT32_C(0x002d5d60):goto L_002d5d60;
 case UINT32_C(0x002d5d64):goto L_002d5d64;
 case UINT32_C(0x002d5d68):goto L_002d5d68;
 case UINT32_C(0x002d5d6c):goto L_002d5d6c;
 case UINT32_C(0x002d5d70):goto L_002d5d70;
 case UINT32_C(0x002d5d74):goto L_002d5d74;
 case UINT32_C(0x002d5d78):goto L_002d5d78;
 case UINT32_C(0x002d5d7c):goto L_002d5d7c;
 case UINT32_C(0x002d5d80):goto L_002d5d80;
 case UINT32_C(0x002d5d84):goto L_002d5d84;
 case UINT32_C(0x002d5d88):goto L_002d5d88;
 case UINT32_C(0x002d5d8c):goto L_002d5d8c;
 case UINT32_C(0x002d5d90):goto L_002d5d90;
 case UINT32_C(0x002d5d94):goto L_002d5d94;
 case UINT32_C(0x002d5d98):goto L_002d5d98;
 case UINT32_C(0x002d5d9c):goto L_002d5d9c;
 case UINT32_C(0x002d5da0):goto L_002d5da0;
 case UINT32_C(0x002d5da4):goto L_002d5da4;
 case UINT32_C(0x002d5da8):goto L_002d5da8;
 case UINT32_C(0x002d5dac):goto L_002d5dac;
 case UINT32_C(0x002d5db0):goto L_002d5db0;
 case UINT32_C(0x002d5db4):goto L_002d5db4;
 case UINT32_C(0x002d5db8):goto L_002d5db8;
 case UINT32_C(0x002d5dbc):goto L_002d5dbc;
 case UINT32_C(0x002d5dc0):goto L_002d5dc0;
 case UINT32_C(0x002d5dc4):goto L_002d5dc4;
 case UINT32_C(0x002d5dc8):goto L_002d5dc8;
 case UINT32_C(0x002d5dcc):goto L_002d5dcc;
 case UINT32_C(0x002d5dd0):goto L_002d5dd0;
 case UINT32_C(0x002d5dd4):goto L_002d5dd4;
 case UINT32_C(0x002d5dd8):goto L_002d5dd8;
 case UINT32_C(0x002d5ddc):goto L_002d5ddc;
 case UINT32_C(0x002d5de0):goto L_002d5de0;
 case UINT32_C(0x002d5de4):goto L_002d5de4;
 case UINT32_C(0x002d5de8):goto L_002d5de8;
 case UINT32_C(0x002d5dec):goto L_002d5dec;
 case UINT32_C(0x002d5df0):goto L_002d5df0;
 case UINT32_C(0x002d5df4):goto L_002d5df4;
 case UINT32_C(0x002d5df8):goto L_002d5df8;
 case UINT32_C(0x002d5dfc):goto L_002d5dfc;
 case UINT32_C(0x002d5e00):goto L_002d5e00;
 case UINT32_C(0x002d5e04):goto L_002d5e04;
 case UINT32_C(0x002d5e08):goto L_002d5e08;
 case UINT32_C(0x002d5e0c):goto L_002d5e0c;
 case UINT32_C(0x002d5e10):goto L_002d5e10;
 case UINT32_C(0x002d5e14):goto L_002d5e14;
 case UINT32_C(0x002d5e18):goto L_002d5e18;
 case UINT32_C(0x002d5e1c):goto L_002d5e1c;
 case UINT32_C(0x002d5e20):goto L_002d5e20;
 case UINT32_C(0x002d5e24):goto L_002d5e24;
 case UINT32_C(0x002d5e28):goto L_002d5e28;
 case UINT32_C(0x002d5e2c):goto L_002d5e2c;
 case UINT32_C(0x002d5e30):goto L_002d5e30;
 case UINT32_C(0x002d5e34):goto L_002d5e34;
 case UINT32_C(0x002d5e38):goto L_002d5e38;
 case UINT32_C(0x002d5e3c):goto L_002d5e3c;
 case UINT32_C(0x002d5e40):goto L_002d5e40;
 case UINT32_C(0x002a8af8):goto L_002a8af8;
 case UINT32_C(0x002a8afc):goto L_002a8afc;
 case UINT32_C(0x002a8b00):goto L_002a8b00;
 case UINT32_C(0x002a8b04):goto L_002a8b04;
 case UINT32_C(0x002a8b08):goto L_002a8b08;
 case UINT32_C(0x002a8b0c):goto L_002a8b0c;
 case UINT32_C(0x002a8b10):goto L_002a8b10;
 case UINT32_C(0x002a8b14):goto L_002a8b14;
 case UINT32_C(0x002a8b18):goto L_002a8b18;
 case UINT32_C(0x002a8b1c):goto L_002a8b1c;
 case UINT32_C(0x002a8b20):goto L_002a8b20;
 case UINT32_C(0x002a8b24):goto L_002a8b24;
 case UINT32_C(0x002a8b28):goto L_002a8b28;
 case UINT32_C(0x002a8b2c):goto L_002a8b2c;
 case UINT32_C(0x002a8b30):goto L_002a8b30;
 case UINT32_C(0x002a8b34):goto L_002a8b34;
 case UINT32_C(0x002a8b38):goto L_002a8b38;
 case UINT32_C(0x002a8b3c):goto L_002a8b3c;
 case UINT32_C(0x002a8b40):goto L_002a8b40;
 case UINT32_C(0x002a8b44):goto L_002a8b44;
 case UINT32_C(0x002a8b48):goto L_002a8b48;
 case UINT32_C(0x002a8b4c):goto L_002a8b4c;
 case UINT32_C(0x002a8b50):goto L_002a8b50;
 case UINT32_C(0x002a8b54):goto L_002a8b54;
 case UINT32_C(0x002a8b58):goto L_002a8b58;
 case UINT32_C(0x002a8b5c):goto L_002a8b5c;
 case UINT32_C(0x002a8b60):goto L_002a8b60;
 case UINT32_C(0x002a8b64):goto L_002a8b64;
 case UINT32_C(0x002a8b68):goto L_002a8b68;
 case UINT32_C(0x002a8b6c):goto L_002a8b6c;
 case UINT32_C(0x002a8b70):goto L_002a8b70;
 case UINT32_C(0x002a8b74):goto L_002a8b74;
 case UINT32_C(0x002a8b78):goto L_002a8b78;
 case UINT32_C(0x002a8b7c):goto L_002a8b7c;
 case UINT32_C(0x002a8b80):goto L_002a8b80;
 case UINT32_C(0x002a8b84):goto L_002a8b84;
 case UINT32_C(0x002a8b88):goto L_002a8b88;
 case UINT32_C(0x002a8b8c):goto L_002a8b8c;
 case UINT32_C(0x002a8b90):goto L_002a8b90;
 case UINT32_C(0x002a8b94):goto L_002a8b94;
 case UINT32_C(0x002a8b98):goto L_002a8b98;
 case UINT32_C(0x002a8b9c):goto L_002a8b9c;
 case UINT32_C(0x002a8ba0):goto L_002a8ba0;
 case UINT32_C(0x002a8ba4):goto L_002a8ba4;
 case UINT32_C(0x002a8ab0):goto L_002a8ab0;
 case UINT32_C(0x002a8ab4):goto L_002a8ab4;
 case UINT32_C(0x002a8ab8):goto L_002a8ab8;
 case UINT32_C(0x002a8abc):goto L_002a8abc;
 case UINT32_C(0x002a8ac0):goto L_002a8ac0;
 case UINT32_C(0x002a8ac4):goto L_002a8ac4;
 case UINT32_C(0x002a8ac8):goto L_002a8ac8;
 case UINT32_C(0x002a8acc):goto L_002a8acc;
 case UINT32_C(0x002a8ad0):goto L_002a8ad0;
 case UINT32_C(0x002a8ad4):goto L_002a8ad4;
 case UINT32_C(0x002a8ad8):goto L_002a8ad8;
 case UINT32_C(0x002a8adc):goto L_002a8adc;
 case UINT32_C(0x002a8ae0):goto L_002a8ae0;
 case UINT32_C(0x002a8ae4):goto L_002a8ae4;
 case UINT32_C(0x002a8ae8):goto L_002a8ae8;
 case UINT32_C(0x002a8aec):goto L_002a8aec;
 case UINT32_C(0x002a8af0):goto L_002a8af0;
 case UINT32_C(0x002a8af4):goto L_002a8af4;
 case UINT32_C(0x002a8a30):goto L_002a8a30;
 case UINT32_C(0x002a8a34):goto L_002a8a34;
 case UINT32_C(0x002a8a38):goto L_002a8a38;
 case UINT32_C(0x002a8a3c):goto L_002a8a3c;
 case UINT32_C(0x002a8a40):goto L_002a8a40;
 case UINT32_C(0x002a8a44):goto L_002a8a44;
 case UINT32_C(0x002a8a48):goto L_002a8a48;
 case UINT32_C(0x002a8a4c):goto L_002a8a4c;
 case UINT32_C(0x002a8a50):goto L_002a8a50;
 case UINT32_C(0x002a8a54):goto L_002a8a54;
 case UINT32_C(0x002a8a58):goto L_002a8a58;
 case UINT32_C(0x002a8a5c):goto L_002a8a5c;
 case UINT32_C(0x002a8a60):goto L_002a8a60;
 case UINT32_C(0x002a8a64):goto L_002a8a64;
 case UINT32_C(0x002a8a68):goto L_002a8a68;
 case UINT32_C(0x002a8a6c):goto L_002a8a6c;
 case UINT32_C(0x002a8a70):goto L_002a8a70;
 case UINT32_C(0x002a8a74):goto L_002a8a74;
 case UINT32_C(0x002a8a78):goto L_002a8a78;
 case UINT32_C(0x002a8a7c):goto L_002a8a7c;
 case UINT32_C(0x002a8a80):goto L_002a8a80;
 case UINT32_C(0x002a8a84):goto L_002a8a84;
 case UINT32_C(0x002a8a88):goto L_002a8a88;
 case UINT32_C(0x002a8a8c):goto L_002a8a8c;
 case UINT32_C(0x002a8a90):goto L_002a8a90;
 case UINT32_C(0x002a8a94):goto L_002a8a94;
 case UINT32_C(0x002a8a98):goto L_002a8a98;
 case UINT32_C(0x002a8a9c):goto L_002a8a9c;
 case UINT32_C(0x002a8aa0):goto L_002a8aa0;
 case UINT32_C(0x002a8aa4):goto L_002a8aa4;
 case UINT32_C(0x002a8aa8):goto L_002a8aa8;
 case UINT32_C(0x002a8aac):goto L_002a8aac;
 case UINT32_C(0x002a89e0):goto L_002a89e0;
 case UINT32_C(0x002a89e4):goto L_002a89e4;
 case UINT32_C(0x002a89e8):goto L_002a89e8;
 case UINT32_C(0x002a89ec):goto L_002a89ec;
 case UINT32_C(0x002a89f0):goto L_002a89f0;
 case UINT32_C(0x002a89f4):goto L_002a89f4;
 case UINT32_C(0x002a89f8):goto L_002a89f8;
 case UINT32_C(0x002a89fc):goto L_002a89fc;
 case UINT32_C(0x002a8a00):goto L_002a8a00;
 case UINT32_C(0x002a8a04):goto L_002a8a04;
 case UINT32_C(0x002a8a08):goto L_002a8a08;
 case UINT32_C(0x002a8a0c):goto L_002a8a0c;
 case UINT32_C(0x002a8a10):goto L_002a8a10;
 case UINT32_C(0x002a8a14):goto L_002a8a14;
 case UINT32_C(0x002a8a18):goto L_002a8a18;
 case UINT32_C(0x002a8a1c):goto L_002a8a1c;
 case UINT32_C(0x002a8a20):goto L_002a8a20;
 case UINT32_C(0x002a8a24):goto L_002a8a24;
 case UINT32_C(0x002a8a28):goto L_002a8a28;
 case UINT32_C(0x002a8a2c):goto L_002a8a2c;
 case UINT32_C(0x002a89c0):goto L_002a89c0;
 case UINT32_C(0x002a89c4):goto L_002a89c4;
 case UINT32_C(0x002a89c8):goto L_002a89c8;
 case UINT32_C(0x002a89cc):goto L_002a89cc;
 case UINT32_C(0x002a89d0):goto L_002a89d0;
 case UINT32_C(0x002a89d4):goto L_002a89d4;
 case UINT32_C(0x002a89d8):goto L_002a89d8;
 case UINT32_C(0x002cd418):goto L_002cd418;
 case UINT32_C(0x002cd41c):goto L_002cd41c;
 case UINT32_C(0x002cd420):goto L_002cd420;
 case UINT32_C(0x002cd424):goto L_002cd424;
 case UINT32_C(0x002cd428):goto L_002cd428;
 case UINT32_C(0x002cd42c):goto L_002cd42c;
 case UINT32_C(0x002cd430):goto L_002cd430;
 case UINT32_C(0x002cd434):goto L_002cd434;
 case UINT32_C(0x002cd438):goto L_002cd438;
 case UINT32_C(0x002cd43c):goto L_002cd43c;
 case UINT32_C(0x002cd440):goto L_002cd440;
 case UINT32_C(0x002cd444):goto L_002cd444;
 case UINT32_C(0x002cd448):goto L_002cd448;
 case UINT32_C(0x002cd44c):goto L_002cd44c;
 case UINT32_C(0x002cd450):goto L_002cd450;
 case UINT32_C(0x002cd454):goto L_002cd454;
 case UINT32_C(0x002cd458):goto L_002cd458;
 case UINT32_C(0x002cd45c):goto L_002cd45c;
 case UINT32_C(0x002cd460):goto L_002cd460;
 case UINT32_C(0x002cd464):goto L_002cd464;
 case UINT32_C(0x002cd468):goto L_002cd468;
 case UINT32_C(0x002cd46c):goto L_002cd46c;
 case UINT32_C(0x002cd470):goto L_002cd470;
 case UINT32_C(0x002cd474):goto L_002cd474;
 case UINT32_C(0x002cd478):goto L_002cd478;
 case UINT32_C(0x002cd47c):goto L_002cd47c;
 case UINT32_C(0x002cd480):goto L_002cd480;
 case UINT32_C(0x002cd484):goto L_002cd484;
 case UINT32_C(0x002cd488):goto L_002cd488;
 case UINT32_C(0x002cd48c):goto L_002cd48c;
 case UINT32_C(0x002cd490):goto L_002cd490;
 case UINT32_C(0x002cd494):goto L_002cd494;
 case UINT32_C(0x002cd498):goto L_002cd498;
 case UINT32_C(0x002cd49c):goto L_002cd49c;
 case UINT32_C(0x002cd4a0):goto L_002cd4a0;
 case UINT32_C(0x002cd4a4):goto L_002cd4a4;
 case UINT32_C(0x002cd4a8):goto L_002cd4a8;
 case UINT32_C(0x002cd4ac):goto L_002cd4ac;
 case UINT32_C(0x002cd4b0):goto L_002cd4b0;
 case UINT32_C(0x002cd4b4):goto L_002cd4b4;
 case UINT32_C(0x002cd4b8):goto L_002cd4b8;
 case UINT32_C(0x002cd4bc):goto L_002cd4bc;
 case UINT32_C(0x002cd4c0):goto L_002cd4c0;
 case UINT32_C(0x002cd4c4):goto L_002cd4c4;
 case UINT32_C(0x002cd4c8):goto L_002cd4c8;
 case UINT32_C(0x002cd4cc):goto L_002cd4cc;
 case UINT32_C(0x002cd4d0):goto L_002cd4d0;
 case UINT32_C(0x002cd4d4):goto L_002cd4d4;
 case UINT32_C(0x002cd4d8):goto L_002cd4d8;
 case UINT32_C(0x002cd4dc):goto L_002cd4dc;
 case UINT32_C(0x002cd4e0):goto L_002cd4e0;
 case UINT32_C(0x002cd4e4):goto L_002cd4e4;
 case UINT32_C(0x002cd4e8):goto L_002cd4e8;
 case UINT32_C(0x002cd4ec):goto L_002cd4ec;
 case UINT32_C(0x002cd4f0):goto L_002cd4f0;
 case UINT32_C(0x002cd4f4):goto L_002cd4f4;
 case UINT32_C(0x002cd4f8):goto L_002cd4f8;
 case UINT32_C(0x002cd4fc):goto L_002cd4fc;
 case UINT32_C(0x002cd500):goto L_002cd500;
 case UINT32_C(0x002cd504):goto L_002cd504;
 case UINT32_C(0x002cd508):goto L_002cd508;
 case UINT32_C(0x002cd50c):goto L_002cd50c;
 case UINT32_C(0x002cd510):goto L_002cd510;
 case UINT32_C(0x002cd514):goto L_002cd514;
 case UINT32_C(0x002cd518):goto L_002cd518;
 case UINT32_C(0x002cd51c):goto L_002cd51c;
 case UINT32_C(0x002cd520):goto L_002cd520;
 case UINT32_C(0x002cd524):goto L_002cd524;
 case UINT32_C(0x002cd528):goto L_002cd528;
 case UINT32_C(0x002cd52c):goto L_002cd52c;
 case UINT32_C(0x002cd530):goto L_002cd530;
 case UINT32_C(0x002cd534):goto L_002cd534;
 case UINT32_C(0x002cd538):goto L_002cd538;
 case UINT32_C(0x002cd53c):goto L_002cd53c;
 case UINT32_C(0x002cd540):goto L_002cd540;
 case UINT32_C(0x002cd544):goto L_002cd544;
 case UINT32_C(0x002cd548):goto L_002cd548;
 case UINT32_C(0x002cd54c):goto L_002cd54c;
 case UINT32_C(0x002cd550):goto L_002cd550;
 case UINT32_C(0x002cd554):goto L_002cd554;
 case UINT32_C(0x002cd558):goto L_002cd558;
 case UINT32_C(0x002cd55c):goto L_002cd55c;
 case UINT32_C(0x002cd560):goto L_002cd560;
 case UINT32_C(0x002cd564):goto L_002cd564;
 case UINT32_C(0x002cd568):goto L_002cd568;
 case UINT32_C(0x002cd56c):goto L_002cd56c;
 case UINT32_C(0x002cd570):goto L_002cd570;
 case UINT32_C(0x002cd574):goto L_002cd574;
 case UINT32_C(0x002cd578):goto L_002cd578;
 case UINT32_C(0x002cd57c):goto L_002cd57c;
 case UINT32_C(0x002cd580):goto L_002cd580;
 case UINT32_C(0x002cd584):goto L_002cd584;
 case UINT32_C(0x002cd588):goto L_002cd588;
 case UINT32_C(0x002cd58c):goto L_002cd58c;
 case UINT32_C(0x002cd590):goto L_002cd590;
 case UINT32_C(0x002cd594):goto L_002cd594;
 case UINT32_C(0x002cd598):goto L_002cd598;
 case UINT32_C(0x002cd59c):goto L_002cd59c;
 case UINT32_C(0x002cd5a0):goto L_002cd5a0;
 case UINT32_C(0x002cd5a4):goto L_002cd5a4;
 case UINT32_C(0x002cd5a8):goto L_002cd5a8;
 case UINT32_C(0x002cd5ac):goto L_002cd5ac;
 case UINT32_C(0x002cd5b0):goto L_002cd5b0;
 case UINT32_C(0x002cd5b4):goto L_002cd5b4;
 case UINT32_C(0x002cd5b8):goto L_002cd5b8;
 case UINT32_C(0x002cd5bc):goto L_002cd5bc;
 case UINT32_C(0x002cd5c0):goto L_002cd5c0;
 case UINT32_C(0x002cd5c4):goto L_002cd5c4;
 case UINT32_C(0x002cd5c8):goto L_002cd5c8;
 case UINT32_C(0x002cd5cc):goto L_002cd5cc;
 case UINT32_C(0x002cd5d0):goto L_002cd5d0;
 case UINT32_C(0x002cd5d4):goto L_002cd5d4;
 case UINT32_C(0x002cd5d8):goto L_002cd5d8;
 case UINT32_C(0x002cd5dc):goto L_002cd5dc;
 case UINT32_C(0x002cd5e0):goto L_002cd5e0;
 case UINT32_C(0x002cd5e4):goto L_002cd5e4;
 case UINT32_C(0x002cd5e8):goto L_002cd5e8;
 case UINT32_C(0x002cd5ec):goto L_002cd5ec;
 case UINT32_C(0x002cd5f0):goto L_002cd5f0;
 case UINT32_C(0x002cd5f4):goto L_002cd5f4;
 case UINT32_C(0x002cd5f8):goto L_002cd5f8;
 case UINT32_C(0x002cd5fc):goto L_002cd5fc;
 case UINT32_C(0x002cd600):goto L_002cd600;
 case UINT32_C(0x002cd604):goto L_002cd604;
 case UINT32_C(0x002cd608):goto L_002cd608;
 case UINT32_C(0x002cd60c):goto L_002cd60c;
 case UINT32_C(0x002cd610):goto L_002cd610;
 case UINT32_C(0x002cd614):goto L_002cd614;
 case UINT32_C(0x002cd618):goto L_002cd618;
 case UINT32_C(0x002cd61c):goto L_002cd61c;
 case UINT32_C(0x002cd620):goto L_002cd620;
 case UINT32_C(0x002cd624):goto L_002cd624;
 case UINT32_C(0x002cd628):goto L_002cd628;
 case UINT32_C(0x002cd62c):goto L_002cd62c;
 case UINT32_C(0x002cd630):goto L_002cd630;
 case UINT32_C(0x002cd634):goto L_002cd634;
 case UINT32_C(0x002cd638):goto L_002cd638;
 case UINT32_C(0x002cd63c):goto L_002cd63c;
 case UINT32_C(0x002cd640):goto L_002cd640;
 case UINT32_C(0x002cd644):goto L_002cd644;
 case UINT32_C(0x002cd648):goto L_002cd648;
 case UINT32_C(0x002cd64c):goto L_002cd64c;
 case UINT32_C(0x002cd650):goto L_002cd650;
 case UINT32_C(0x002cd654):goto L_002cd654;
 case UINT32_C(0x002cd658):goto L_002cd658;
 case UINT32_C(0x002cd65c):goto L_002cd65c;
 case UINT32_C(0x002cd660):goto L_002cd660;
 case UINT32_C(0x002cd664):goto L_002cd664;
 case UINT32_C(0x002cd668):goto L_002cd668;
 case UINT32_C(0x002cd66c):goto L_002cd66c;
 case UINT32_C(0x002cd670):goto L_002cd670;
 case UINT32_C(0x002cd674):goto L_002cd674;
 case UINT32_C(0x002cd678):goto L_002cd678;
 case UINT32_C(0x002ccf68):goto L_002ccf68;
 case UINT32_C(0x002ccf6c):goto L_002ccf6c;
 case UINT32_C(0x002ccf70):goto L_002ccf70;
 case UINT32_C(0x002ccf74):goto L_002ccf74;
 case UINT32_C(0x002ccf78):goto L_002ccf78;
 case UINT32_C(0x002ccf7c):goto L_002ccf7c;
 case UINT32_C(0x002ccf80):goto L_002ccf80;
 case UINT32_C(0x002ccf84):goto L_002ccf84;
 case UINT32_C(0x002ccf88):goto L_002ccf88;
 case UINT32_C(0x002ccf8c):goto L_002ccf8c;
 case UINT32_C(0x002ccf90):goto L_002ccf90;
 case UINT32_C(0x002ccf94):goto L_002ccf94;
 case UINT32_C(0x002ccf98):goto L_002ccf98;
 case UINT32_C(0x002ccf9c):goto L_002ccf9c;
 case UINT32_C(0x002ccfa0):goto L_002ccfa0;
 case UINT32_C(0x002ccfa4):goto L_002ccfa4;
 case UINT32_C(0x002ccfa8):goto L_002ccfa8;
 case UINT32_C(0x002ccfac):goto L_002ccfac;
 case UINT32_C(0x002ccfb0):goto L_002ccfb0;
 case UINT32_C(0x002ccfb4):goto L_002ccfb4;
 case UINT32_C(0x002ccfb8):goto L_002ccfb8;
 case UINT32_C(0x002ccfbc):goto L_002ccfbc;
 case UINT32_C(0x002ccfc0):goto L_002ccfc0;
 case UINT32_C(0x002ccfc4):goto L_002ccfc4;
 case UINT32_C(0x002ccfc8):goto L_002ccfc8;
 case UINT32_C(0x002ccfcc):goto L_002ccfcc;
 case UINT32_C(0x002ccfd0):goto L_002ccfd0;
 case UINT32_C(0x002ccfd4):goto L_002ccfd4;
 case UINT32_C(0x002ccfd8):goto L_002ccfd8;
 case UINT32_C(0x002ccfdc):goto L_002ccfdc;
 case UINT32_C(0x002ccfe0):goto L_002ccfe0;
 case UINT32_C(0x002ccfe4):goto L_002ccfe4;
 case UINT32_C(0x002ccfe8):goto L_002ccfe8;
 case UINT32_C(0x002ccfec):goto L_002ccfec;
 case UINT32_C(0x002ccff0):goto L_002ccff0;
 case UINT32_C(0x002ccff4):goto L_002ccff4;
 case UINT32_C(0x002ccff8):goto L_002ccff8;
 case UINT32_C(0x002ccffc):goto L_002ccffc;
 case UINT32_C(0x002cd000):goto L_002cd000;
 case UINT32_C(0x002cd004):goto L_002cd004;
 case UINT32_C(0x002cd008):goto L_002cd008;
 case UINT32_C(0x002cd00c):goto L_002cd00c;
 case UINT32_C(0x002cd010):goto L_002cd010;
 case UINT32_C(0x002cd014):goto L_002cd014;
 case UINT32_C(0x002cd018):goto L_002cd018;
 case UINT32_C(0x002cd01c):goto L_002cd01c;
 case UINT32_C(0x002cd020):goto L_002cd020;
 case UINT32_C(0x002cd024):goto L_002cd024;
 case UINT32_C(0x002cd028):goto L_002cd028;
 case UINT32_C(0x002cd030):goto L_002cd030;
 case UINT32_C(0x002cd034):goto L_002cd034;
 case UINT32_C(0x002cd038):goto L_002cd038;
 case UINT32_C(0x002cd03c):goto L_002cd03c;
 case UINT32_C(0x002cd040):goto L_002cd040;
 case UINT32_C(0x002cd044):goto L_002cd044;
 case UINT32_C(0x002cd048):goto L_002cd048;
 case UINT32_C(0x002cd04c):goto L_002cd04c;
 case UINT32_C(0x002cd050):goto L_002cd050;
 case UINT32_C(0x002cd054):goto L_002cd054;
 case UINT32_C(0x002cd058):goto L_002cd058;
 case UINT32_C(0x002cd05c):goto L_002cd05c;
 case UINT32_C(0x002cd060):goto L_002cd060;
 case UINT32_C(0x002cd064):goto L_002cd064;
 case UINT32_C(0x002cd068):goto L_002cd068;
 case UINT32_C(0x002cd06c):goto L_002cd06c;
 case UINT32_C(0x002cd070):goto L_002cd070;
 case UINT32_C(0x002cd074):goto L_002cd074;
 case UINT32_C(0x002cd078):goto L_002cd078;
 case UINT32_C(0x002cd07c):goto L_002cd07c;
 case UINT32_C(0x002cd080):goto L_002cd080;
 case UINT32_C(0x002cd084):goto L_002cd084;
 case UINT32_C(0x002cd088):goto L_002cd088;
 case UINT32_C(0x002cd08c):goto L_002cd08c;
 case UINT32_C(0x002cd090):goto L_002cd090;
 case UINT32_C(0x002cd094):goto L_002cd094;
 case UINT32_C(0x002cd098):goto L_002cd098;
 case UINT32_C(0x002cd09c):goto L_002cd09c;
 case UINT32_C(0x002cd0a0):goto L_002cd0a0;
 case UINT32_C(0x002cd0a4):goto L_002cd0a4;
 case UINT32_C(0x002cd0a8):goto L_002cd0a8;
 case UINT32_C(0x002cd0ac):goto L_002cd0ac;
 case UINT32_C(0x002cd0b0):goto L_002cd0b0;
 case UINT32_C(0x002cd0b4):goto L_002cd0b4;
 case UINT32_C(0x002cd0b8):goto L_002cd0b8;
 case UINT32_C(0x002cd0bc):goto L_002cd0bc;
 case UINT32_C(0x002cd0c0):goto L_002cd0c0;
 case UINT32_C(0x002cd0c4):goto L_002cd0c4;
 case UINT32_C(0x002cd0c8):goto L_002cd0c8;
 case UINT32_C(0x002cd0cc):goto L_002cd0cc;
 case UINT32_C(0x002cd0d0):goto L_002cd0d0;
 case UINT32_C(0x002cd0d4):goto L_002cd0d4;
 case UINT32_C(0x002cd0d8):goto L_002cd0d8;
 case UINT32_C(0x002cd0dc):goto L_002cd0dc;
 case UINT32_C(0x002cd0e0):goto L_002cd0e0;
 case UINT32_C(0x002cd0e4):goto L_002cd0e4;
 case UINT32_C(0x002cd0e8):goto L_002cd0e8;
 case UINT32_C(0x002cd0ec):goto L_002cd0ec;
 case UINT32_C(0x002cd0f0):goto L_002cd0f0;
 case UINT32_C(0x002cd0f4):goto L_002cd0f4;
 case UINT32_C(0x002cd0f8):goto L_002cd0f8;
 case UINT32_C(0x002cd0fc):goto L_002cd0fc;
 case UINT32_C(0x002cd100):goto L_002cd100;
 case UINT32_C(0x002cd104):goto L_002cd104;
 case UINT32_C(0x002cd108):goto L_002cd108;
 case UINT32_C(0x002cd10c):goto L_002cd10c;
 case UINT32_C(0x002cd110):goto L_002cd110;
 case UINT32_C(0x002cd114):goto L_002cd114;
 case UINT32_C(0x002cd118):goto L_002cd118;
 case UINT32_C(0x002cd11c):goto L_002cd11c;
 case UINT32_C(0x002cd120):goto L_002cd120;
 case UINT32_C(0x002cd124):goto L_002cd124;
 case UINT32_C(0x002cd128):goto L_002cd128;
 case UINT32_C(0x002cd12c):goto L_002cd12c;
 case UINT32_C(0x002cd130):goto L_002cd130;
 case UINT32_C(0x002cd134):goto L_002cd134;
 case UINT32_C(0x002b58b8):goto L_002b58b8;
 case UINT32_C(0x002b58bc):goto L_002b58bc;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002a98a8:
 STEP(UINT32_C(0x002a98a8)); /* 27bdff60 addiu sp,sp,-160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff60)));target=sx(UINT32_C(0x002a98ac));goto dispatch;
L_002a98ac:
 STEP(UINT32_C(0x002a98ac)); /* ffb00060 sd s0,0x60(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002a98b0));goto dispatch;
L_002a98b0:
 STEP(UINT32_C(0x002a98b0)); /* ffb10068 sd s1,0x68(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000068),&value64,8u);target=sx(UINT32_C(0x002a98b4));goto dispatch;
L_002a98b4:
 STEP(UINT32_C(0x002a98b4)); /* 00a0882d daddu s1,a1,zero */
 set(m,17u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002a98b8));goto dispatch;
L_002a98b8:
 STEP(UINT32_C(0x002a98b8)); /* ffb20070 sd s2,0x70(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002a98bc));goto dispatch;
L_002a98bc:
 STEP(UINT32_C(0x002a98bc)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002a98c0));goto dispatch;
L_002a98c0:
 STEP(UINT32_C(0x002a98c0)); /* ffb30078 sd s3,0x78(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000078),&value64,8u);target=sx(UINT32_C(0x002a98c4));goto dispatch;
L_002a98c4:
 STEP(UINT32_C(0x002a98c4)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002a98c8));goto dispatch;
L_002a98c8:
 STEP(UINT32_C(0x002a98c8)); /* ffb40080 sd s4,0x80(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002a98cc));goto dispatch;
L_002a98cc:
 STEP(UINT32_C(0x002a98cc)); /* ffb50088 sd s5,0x88(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000088),&value64,8u);target=sx(UINT32_C(0x002a98d0));goto dispatch;
L_002a98d0:
 STEP(UINT32_C(0x002a98d0)); /* ffb60090 sd s6,0x90(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x002a98d4));goto dispatch;
L_002a98d4:
 STEP(UINT32_C(0x002a98d4)); /* ffbf0098 sd ra,0x98(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000098),&value64,8u);target=sx(UINT32_C(0x002a98d8));goto dispatch;
L_002a98d8:
 STEP(UINT32_C(0x002a98d8)); /* 0c0b5743 jal 002d5d0c */
 set(m,31u,UINT64_C(0x002a98e0));STEP(UINT32_C(0x002a98dc));set(m,22u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d5d0c));goto dispatch;
L_002a98dc:
 STEP(UINT32_C(0x002a98dc)); /* 00e0b02d daddu s6,a3,zero */
 set(m,22u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002a98e0));goto dispatch;
L_002a98e0:
 STEP(UINT32_C(0x002a98e0)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a98e4));goto dispatch;
L_002a98e4:
 STEP(UINT32_C(0x002a98e4)); /* 02111021 addu v0,s0,s1 */
 set(m,2u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002a98e8));goto dispatch;
L_002a98e8:
 STEP(UINT32_C(0x002a98e8)); /* 2455000c addiu s5,v0,12 */
 set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002a98ec));goto dispatch;
L_002a98ec:
 STEP(UINT32_C(0x002a98ec)); /* 0c0aa40e jal 002a9038 */
 set(m,31u,UINT64_C(0x002a98f4));STEP(UINT32_C(0x002a98f0));set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002a9038));goto dispatch;
L_002a98f0:
 STEP(UINT32_C(0x002a98f0)); /* 02a0202d daddu a0,s5,zero */
 set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002a98f4));goto dispatch;
L_002a98f4:
 STEP(UINT32_C(0x002a98f4)); /* 0c0aa5a2 jal 002a9688 */
 set(m,31u,UINT64_C(0x002a98fc));STEP(UINT32_C(0x002a98f8));set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a9688));goto dispatch;
L_002a98f8:
 STEP(UINT32_C(0x002a98f8)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a98fc));goto dispatch;
L_002a98fc:
 STEP(UINT32_C(0x002a98fc)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002a9900));goto dispatch;
L_002a9900:
 STEP(UINT32_C(0x002a9900)); /* 0040a02d daddu s4,v0,zero */
 set(m,20u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a9904));goto dispatch;
L_002a9904:
 STEP(UINT32_C(0x002a9904)); /* 26060001 addiu a2,s0,1 */
 set(m,6u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002a9908));goto dispatch;
L_002a9908:
 STEP(UINT32_C(0x002a9908)); /* ae900000 sw s0,0x0(s4) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002a990c));goto dispatch;
L_002a990c:
 STEP(UINT32_C(0x002a990c)); /* 02908021 addu s0,s4,s0 */
 set(m,16u,sx((uint32_t)lo(m,20u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002a9910));goto dispatch;
L_002a9910:
 STEP(UINT32_C(0x002a9910)); /* ae910004 sw s1,0x4(s4) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,20u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002a9914));goto dispatch;
L_002a9914:
 STEP(UINT32_C(0x002a9914)); /* 0c0b50e9 jal 002d43a4 */
 set(m,31u,UINT64_C(0x002a991c));STEP(UINT32_C(0x002a9918));set(m,4u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d43a4));goto dispatch;
L_002a9918:
 STEP(UINT32_C(0x002a9918)); /* 26840008 addiu a0,s4,8 */
 set(m,4u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002a991c));goto dispatch;
L_002a991c:
 STEP(UINT32_C(0x002a991c)); /* 26040009 addiu a0,s0,9 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000009)));target=sx(UINT32_C(0x002a9920));goto dispatch;
L_002a9920:
 STEP(UINT32_C(0x002a9920)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002a9924));goto dispatch;
L_002a9924:
 STEP(UINT32_C(0x002a9924)); /* 12200003 beq s1,zero,002a9934 */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002a9928));set(m,6u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x002a9934):UINT32_C(0x002a992c));goto dispatch;}
L_002a9928:
 STEP(UINT32_C(0x002a9928)); /* 0220302d daddu a2,s1,zero */
 set(m,6u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002a992c));goto dispatch;
L_002a992c:
 STEP(UINT32_C(0x002a992c)); /* 0c0b50e9 jal 002d43a4 */
 set(m,31u,UINT64_C(0x002a9934));STEP(UINT32_C(0x002a9930));/* nop */target=sx(UINT32_C(0x002d43a4));goto dispatch;
L_002a9930:
 STEP(UINT32_C(0x002a9930)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a9934));goto dispatch;
L_002a9934:
 STEP(UINT32_C(0x002a9934)); /* 27a2004f addiu v0,sp,79 */
 set(m,2u,sx((uint32_t)lo(m,29u)+UINT32_C(0x0000004f)));target=sx(UINT32_C(0x002a9938));goto dispatch;
L_002a9938:
 STEP(UINT32_C(0x002a9938)); /* 2403ffc0 addiu v1,zero,-64 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002a993c));goto dispatch;
L_002a993c:
 STEP(UINT32_C(0x002a993c)); /* 00438024 and s0,v0,v1 */
 set(m,16u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002a9940));goto dispatch;
L_002a9940:
 STEP(UINT32_C(0x002a9940)); /* 3c040057 lui a0,zero,0x57 */
 set(m,4u,sx(UINT32_C(0x00570000)));target=sx(UINT32_C(0x002a9944));goto dispatch;
L_002a9944:
 STEP(UINT32_C(0x002a9944)); /* 0280382d daddu a3,s4,zero */
 set(m,7u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002a9948));goto dispatch;
L_002a9948:
 STEP(UINT32_C(0x002a9948)); /* 02a0402d daddu t0,s5,zero */
 set(m,8u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002a994c));goto dispatch;
L_002a994c:
 STEP(UINT32_C(0x002a994c)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002a9950));goto dispatch;
L_002a9950:
 STEP(UINT32_C(0x002a9950)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002a9954));goto dispatch;
L_002a9954:
 STEP(UINT32_C(0x002a9954)); /* 240a0008 addiu t2,zero,8 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002a9958));goto dispatch;
L_002a9958:
 STEP(UINT32_C(0x002a9958)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002a995c));goto dispatch;
L_002a995c:
 STEP(UINT32_C(0x002a995c)); /* 0200482d daddu t1,s0,zero */
 set(m,9u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002a9960));goto dispatch;
L_002a9960:
 STEP(UINT32_C(0x002a9960)); /* 24847f40 addiu a0,a0,32576 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00007f40)));target=sx(UINT32_C(0x002a9964));goto dispatch;
L_002a9964:
 STEP(UINT32_C(0x002a9964)); /* 0c0b3506 jal 002cd418 */
 set(m,31u,UINT64_C(0x002a996c));STEP(UINT32_C(0x002a9968));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cd418));goto dispatch;
L_002a9968:
 STEP(UINT32_C(0x002a9968)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002a996c));goto dispatch;
L_002a996c:
 STEP(UINT32_C(0x002a996c)); /* 04420007 regimm2 v0,002a998c */
 if((int64_t)lo(m,2u)<0){STEP(UINT32_C(0x002a9970));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002a998c));}else target=sx(UINT32_C(0x002a9974));goto dispatch;
L_002a9970:
 STEP(UINT32_C(0x002a9970)); /* dfb00060 ld s0,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002a9974));goto dispatch;
L_002a9974:
 STEP(UINT32_C(0x002a9974)); /* 52c00004 beql s6,zero,002a9988 */
 if(lo(m,22u)==lo(m,0u)){STEP(UINT32_C(0x002a9978));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a9988));}else target=sx(UINT32_C(0x002a997c));goto dispatch;
L_002a9978:
 STEP(UINT32_C(0x002a9978)); /* 8e020000 lw v0,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a997c));goto dispatch;
L_002a997c:
 STEP(UINT32_C(0x002a997c)); /* 8e020004 lw v0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a9980));goto dispatch;
L_002a9980:
 STEP(UINT32_C(0x002a9980)); /* aec20000 sw v0,0x0(s6) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002a9984));goto dispatch;
L_002a9984:
 STEP(UINT32_C(0x002a9984)); /* 8e020000 lw v0,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a9988));goto dispatch;
L_002a9988:
 STEP(UINT32_C(0x002a9988)); /* dfb00060 ld s0,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002a998c));goto dispatch;
L_002a998c:
 STEP(UINT32_C(0x002a998c)); /* dfb10068 ld s1,0x68(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000068),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002a9990));goto dispatch;
L_002a9990:
 STEP(UINT32_C(0x002a9990)); /* dfb20070 ld s2,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002a9994));goto dispatch;
L_002a9994:
 STEP(UINT32_C(0x002a9994)); /* dfb30078 ld s3,0x78(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000078),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002a9998));goto dispatch;
L_002a9998:
 STEP(UINT32_C(0x002a9998)); /* dfb40080 ld s4,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002a999c));goto dispatch;
L_002a999c:
 STEP(UINT32_C(0x002a999c)); /* dfb50088 ld s5,0x88(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000088),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002a99a0));goto dispatch;
L_002a99a0:
 STEP(UINT32_C(0x002a99a0)); /* dfb60090 ld s6,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002a99a4));goto dispatch;
L_002a99a4:
 STEP(UINT32_C(0x002a99a4)); /* dfbf0098 ld ra,0x98(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000098),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002a99a8));goto dispatch;
L_002a99a8:
 STEP(UINT32_C(0x002a99a8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a99ac));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));goto dispatch;
L_002a99ac:
 STEP(UINT32_C(0x002a99ac)); /* 27bd00a0 addiu sp,sp,160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));target=sx(UINT32_C(0x002a99b0));goto dispatch;
L_002a9038:
 STEP(UINT32_C(0x002a9038)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002a903c));goto dispatch;
L_002a903c:
 STEP(UINT32_C(0x002a903c)); /* 2484007f addiu a0,a0,127 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x0000007f)));target=sx(UINT32_C(0x002a9040));goto dispatch;
L_002a9040:
 STEP(UINT32_C(0x002a9040)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002a9044));goto dispatch;
L_002a9044:
 STEP(UINT32_C(0x002a9044)); /* 3c100057 lui s0,zero,0x57 */
 set(m,16u,sx(UINT32_C(0x00570000)));target=sx(UINT32_C(0x002a9048));goto dispatch;
L_002a9048:
 STEP(UINT32_C(0x002a9048)); /* 2402ff80 addiu v0,zero,-128 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x002a904c));goto dispatch;
L_002a904c:
 STEP(UINT32_C(0x002a904c)); /* 26107f18 addiu s0,s0,32536 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00007f18)));target=sx(UINT32_C(0x002a9050));goto dispatch;
L_002a9050:
 STEP(UINT32_C(0x002a9050)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002a9054));goto dispatch;
L_002a9054:
 STEP(UINT32_C(0x002a9054)); /* 00828824 and s1,a0,v0 */
 set(m,17u,lo(m,4u)&lo(m,2u));target=sx(UINT32_C(0x002a9058));goto dispatch;
L_002a9058:
 STEP(UINT32_C(0x002a9058)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002a905c));goto dispatch;
L_002a905c:
 STEP(UINT32_C(0x002a905c)); /* ffb30018 sd s3,0x18(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002a9060));goto dispatch;
L_002a9060:
 STEP(UINT32_C(0x002a9060)); /* 24130002 addiu s3,zero,2 */
 set(m,19u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002a9064));goto dispatch;
L_002a9064:
 STEP(UINT32_C(0x002a9064)); /* ffb40020 sd s4,0x20(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002a9068));goto dispatch;
L_002a9068:
 STEP(UINT32_C(0x002a9068)); /* ffbf0028 sd ra,0x28(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(UINT32_C(0x002a906c));goto dispatch;
L_002a906c:
 STEP(UINT32_C(0x002a906c)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002a9074));STEP(UINT32_C(0x002a9070));set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002a9070:
 STEP(UINT32_C(0x002a9070)); /* 24140001 addiu s4,zero,1 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002a9074));goto dispatch;
L_002a9074:
 STEP(UINT32_C(0x002a9074)); /* 8e100004 lw s0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002a9078));goto dispatch;
L_002a9078:
 STEP(UINT32_C(0x002a9078)); /* 0040902d daddu s2,v0,zero */
 set(m,18u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a907c));goto dispatch;
L_002a907c:
 STEP(UINT32_C(0x002a907c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a9080));goto dispatch;
L_002a9080:
 STEP(UINT32_C(0x002a9080)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002a9084));goto dispatch;
L_002a9084:
 STEP(UINT32_C(0x002a9084)); /* 5040000e beql v0,zero,002a90c0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002a9088));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002a90c0));}else target=sx(UINT32_C(0x002a908c));goto dispatch;
L_002a9088:
 STEP(UINT32_C(0x002a9088)); /* 8e050004 lw a1,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002a908c));goto dispatch;
L_002a908c:
 STEP(UINT32_C(0x002a908c)); /* 54530030 bnel v0,s3,002a9150 */
 if(lo(m,2u)!=lo(m,19u)){STEP(UINT32_C(0x002a9090));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002a9150));}else target=sx(UINT32_C(0x002a9094));goto dispatch;
L_002a9090:
 STEP(UINT32_C(0x002a9090)); /* 8e050004 lw a1,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002a9094));goto dispatch;
L_002a9094:
 STEP(UINT32_C(0x002a9094)); /* 52400004 beql s2,zero,002a90a8 */
 if(lo(m,18u)==lo(m,0u)){STEP(UINT32_C(0x002a9098));READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd6c0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a90a8));}else target=sx(UINT32_C(0x002a909c));goto dispatch;
L_002a9098:
 STEP(UINT32_C(0x002a9098)); /* 8f82d6c0 lw v0,-0x2940(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd6c0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a909c));goto dispatch;
L_002a909c:
 STEP(UINT32_C(0x002a909c)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002a90a4));STEP(UINT32_C(0x002a90a0));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002a90a0:
 STEP(UINT32_C(0x002a90a0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a90a4));goto dispatch;
L_002a90a4:
 STEP(UINT32_C(0x002a90a4)); /* 8f82d6c0 lw v0,-0x2940(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd6c0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a90a8));goto dispatch;
L_002a90a8:
 STEP(UINT32_C(0x002a90a8)); /* 50400029 beql v0,zero,002a9150 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002a90ac));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002a9150));}else target=sx(UINT32_C(0x002a90b0));goto dispatch;
L_002a90ac:
 STEP(UINT32_C(0x002a90ac)); /* 8e050004 lw a1,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002a90b0));goto dispatch;
L_002a90b0:
 STEP(UINT32_C(0x002a90b0)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002a90b8));STEP(UINT32_C(0x002a90b4));set(m,4u,lo(m,17u)+lo(m,0u));goto dispatch;
L_002a90b4:
 STEP(UINT32_C(0x002a90b4)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002a90b8));goto dispatch;
L_002a90b8:
 STEP(UINT32_C(0x002a90b8)); /* 10000025 beq zero,zero,002a9150 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002a90bc));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(taken?UINT32_C(0x002a9150):UINT32_C(0x002a90c0));goto dispatch;}
L_002a90bc:
 STEP(UINT32_C(0x002a90bc)); /* 8e050004 lw a1,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002a90c0));goto dispatch;
L_002a90c0:
 STEP(UINT32_C(0x002a90c0)); /* 8e020008 lw v0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a90c4));goto dispatch;
L_002a90c4:
 STEP(UINT32_C(0x002a90c4)); /* 8ca30008 lw v1,0x8(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002a90c8));goto dispatch;
L_002a90c8:
 STEP(UINT32_C(0x002a90c8)); /* 00621823 subu v1,v1,v0 */
 set(m,3u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002a90cc));goto dispatch;
L_002a90cc:
 STEP(UINT32_C(0x002a90cc)); /* 0071202a slt a0,v1,s1 */
 set(m,4u,((int64_t)lo(m,3u)<(int64_t)lo(m,17u)));target=sx(UINT32_C(0x002a90d0));goto dispatch;
L_002a90d0:
 STEP(UINT32_C(0x002a90d0)); /* 5480ffeb bnel a0,zero,002a9080 */
 if(lo(m,4u)!=lo(m,0u)){STEP(UINT32_C(0x002a90d4));set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002a9080));}else target=sx(UINT32_C(0x002a90d8));goto dispatch;
L_002a90d4:
 STEP(UINT32_C(0x002a90d4)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002a90d8));goto dispatch;
L_002a90d8:
 STEP(UINT32_C(0x002a90d8)); /* 0223102a slt v0,s1,v1 */
 set(m,2u,((int64_t)lo(m,17u)<(int64_t)lo(m,3u)));target=sx(UINT32_C(0x002a90dc));goto dispatch;
L_002a90dc:
 STEP(UINT32_C(0x002a90dc)); /* 1040000e beq v0,zero,002a9118 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002a90e0));/* nop */target=sx(taken?UINT32_C(0x002a9118):UINT32_C(0x002a90e4));goto dispatch;}
L_002a90e0:
 STEP(UINT32_C(0x002a90e0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a90e4));goto dispatch;
L_002a90e4:
 STEP(UINT32_C(0x002a90e4)); /* 0c0aa2be jal 002a8af8 */
 set(m,31u,UINT64_C(0x002a90ec));STEP(UINT32_C(0x002a90e8));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002a8af8));goto dispatch;
L_002a90e8:
 STEP(UINT32_C(0x002a90e8)); /* 24040010 addiu a0,zero,16 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002a90ec));goto dispatch;
L_002a90ec:
 STEP(UINT32_C(0x002a90ec)); /* 8e030008 lw v1,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002a90f0));goto dispatch;
L_002a90f0:
 STEP(UINT32_C(0x002a90f0)); /* ac500000 sw s0,0x0(v0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002a90f4));goto dispatch;
L_002a90f4:
 STEP(UINT32_C(0x002a90f4)); /* 00711821 addu v1,v1,s1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002a90f8));goto dispatch;
L_002a90f8:
 STEP(UINT32_C(0x002a90f8)); /* a440000c sh zero,0xc(v0) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002a90fc));goto dispatch;
L_002a90fc:
 STEP(UINT32_C(0x002a90fc)); /* 8e040004 lw a0,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002a9100));goto dispatch;
L_002a9100:
 STEP(UINT32_C(0x002a9100)); /* ac430008 sw v1,0x8(v0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002a9104));goto dispatch;
L_002a9104:
 STEP(UINT32_C(0x002a9104)); /* ac440004 sw a0,0x4(v0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002a9108));goto dispatch;
L_002a9108:
 STEP(UINT32_C(0x002a9108)); /* a440000e sh zero,0xe(v0) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000e),&value16,2u);target=sx(UINT32_C(0x002a910c));goto dispatch;
L_002a910c:
 STEP(UINT32_C(0x002a910c)); /* 8e030004 lw v1,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002a9110));goto dispatch;
L_002a9110:
 STEP(UINT32_C(0x002a9110)); /* ac620000 sw v0,0x0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002a9114));goto dispatch;
L_002a9114:
 STEP(UINT32_C(0x002a9114)); /* ae020004 sw v0,0x4(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002a9118));goto dispatch;
L_002a9118:
 STEP(UINT32_C(0x002a9118)); /* 12400003 beq s2,zero,002a9128 */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002a911c));value16=(uint16_t)lo(m,20u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(taken?UINT32_C(0x002a9128):UINT32_C(0x002a9120));goto dispatch;}
L_002a911c:
 STEP(UINT32_C(0x002a911c)); /* a614000c sh s4,0xc(s0) */
 value16=(uint16_t)lo(m,20u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002a9120));goto dispatch;
L_002a9120:
 STEP(UINT32_C(0x002a9120)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002a9128));STEP(UINT32_C(0x002a9124));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002a9124:
 STEP(UINT32_C(0x002a9124)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a9128));goto dispatch;
L_002a9128:
 STEP(UINT32_C(0x002a9128)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002a912c));goto dispatch;
L_002a912c:
 STEP(UINT32_C(0x002a912c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002a9130));goto dispatch;
L_002a9130:
 STEP(UINT32_C(0x002a9130)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002a9134));goto dispatch;
L_002a9134:
 STEP(UINT32_C(0x002a9134)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002a9138));goto dispatch;
L_002a9138:
 STEP(UINT32_C(0x002a9138)); /* dfb30018 ld s3,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002a913c));goto dispatch;
L_002a913c:
 STEP(UINT32_C(0x002a913c)); /* dfb40020 ld s4,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002a9140));goto dispatch;
L_002a9140:
 STEP(UINT32_C(0x002a9140)); /* dfbf0028 ld ra,0x28(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002a9144));goto dispatch;
L_002a9144:
 STEP(UINT32_C(0x002a9144)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a9148));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002a9148:
 STEP(UINT32_C(0x002a9148)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002a914c));goto dispatch;
L_002a914c:
 STEP(UINT32_C(0x002a914c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a9150));goto dispatch;
L_002a9150:
 STEP(UINT32_C(0x002a9150)); /* 1000ffcb beq zero,zero,002a9080 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002a9154));set(m,16u,lo(m,5u)+lo(m,0u));target=sx(taken?UINT32_C(0x002a9080):UINT32_C(0x002a9158));goto dispatch;}
L_002a9154:
 STEP(UINT32_C(0x002a9154)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002a9158));goto dispatch;
L_002a9688:
 STEP(UINT32_C(0x002a9688)); /* 9483000e lhu v1,0xe(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x0000000e),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002a968c));goto dispatch;
L_002a968c:
 STEP(UINT32_C(0x002a968c)); /* 8c820008 lw v0,0x8(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a9690));goto dispatch;
L_002a9690:
 STEP(UINT32_C(0x002a9690)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002a9694));goto dispatch;
L_002a9694:
 STEP(UINT32_C(0x002a9694)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a9698));value16=(uint16_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000000e),&value16,2u);goto dispatch;
L_002a9698:
 STEP(UINT32_C(0x002a9698)); /* a483000e sh v1,0xe(a0) */
 value16=(uint16_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000000e),&value16,2u);target=sx(UINT32_C(0x002a969c));goto dispatch;
L_002d5d0c:
 STEP(UINT32_C(0x002d5d0c)); /* 30820007 andi v0,a0,0x7 */
 set(m,2u,lo(m,4u) & UINT64_C(0x7));target=sx(UINT32_C(0x002d5d10));goto dispatch;
L_002d5d10:
 STEP(UINT32_C(0x002d5d10)); /* 14400043 bne v0,zero,002d5e20 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d5d14));set(m,7u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d5e20):UINT32_C(0x002d5d18));goto dispatch;}
L_002d5d14:
 STEP(UINT32_C(0x002d5d14)); /* 0080382d daddu a3,a0,zero */
 set(m,7u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d5d18));goto dispatch;
L_002d5d18:
 STEP(UINT32_C(0x002d5d18)); /* 3083000f andi v1,a0,0xf */
 set(m,3u,lo(m,4u) & UINT64_C(0xf));target=sx(UINT32_C(0x002d5d1c));goto dispatch;
L_002d5d1c:
 STEP(UINT32_C(0x002d5d1c)); /* 3c020101 lui v0,zero,0x101 */
 set(m,2u,sx(UINT32_C(0x01010000)));target=sx(UINT32_C(0x002d5d20));goto dispatch;
L_002d5d20:
 STEP(UINT32_C(0x002d5d20)); /* 34420101 ori v0,v0,0x101 */
 set(m,2u,lo(m,2u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d5d24));goto dispatch;
L_002d5d24:
 STEP(UINT32_C(0x002d5d24)); /* 00021438 dsll v0,v0,16 */
 set(m,2u,lo(m,2u)<<16u);target=sx(UINT32_C(0x002d5d28));goto dispatch;
L_002d5d28:
 STEP(UINT32_C(0x002d5d28)); /* 34420101 ori v0,v0,0x101 */
 set(m,2u,lo(m,2u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d5d2c));goto dispatch;
L_002d5d2c:
 STEP(UINT32_C(0x002d5d2c)); /* 00021438 dsll v0,v0,16 */
 set(m,2u,lo(m,2u)<<16u);target=sx(UINT32_C(0x002d5d30));goto dispatch;
L_002d5d30:
 STEP(UINT32_C(0x002d5d30)); /* 34420101 ori v0,v0,0x101 */
 set(m,2u,lo(m,2u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d5d34));goto dispatch;
L_002d5d34:
 STEP(UINT32_C(0x002d5d34)); /* 1460001e bne v1,zero,002d5db0 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002d5d38));set(m,5u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d5db0):UINT32_C(0x002d5d3c));goto dispatch;}
L_002d5d38:
 STEP(UINT32_C(0x002d5d38)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d5d3c));goto dispatch;
L_002d5d3c:
 STEP(UINT32_C(0x002d5d3c)); /* 78a30000 lq v1,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x002d5d40));goto dispatch;
L_002d5d40:
 STEP(UINT32_C(0x002d5d40)); /* 70424389 mmi 70424389 */
 {uint32_t out[4]={m->gpr[2][0],m->gpr[2][1],m->gpr[2][0],m->gpr[2][1]};memcpy(m->gpr[8],out,16);}target=sx(UINT32_C(0x002d5d44));goto dispatch;
L_002d5d44:
 STEP(UINT32_C(0x002d5d44)); /* 3c048080 lui a0,zero,0x8080 */
 set(m,4u,sx(UINT32_C(0x80800000)));target=sx(UINT32_C(0x002d5d48));goto dispatch;
L_002d5d48:
 STEP(UINT32_C(0x002d5d48)); /* 34848080 ori a0,a0,0x8080 */
 set(m,4u,lo(m,4u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d5d4c));goto dispatch;
L_002d5d4c:
 STEP(UINT32_C(0x002d5d4c)); /* 00042438 dsll a0,a0,16 */
 set(m,4u,lo(m,4u)<<16u);target=sx(UINT32_C(0x002d5d50));goto dispatch;
L_002d5d50:
 STEP(UINT32_C(0x002d5d50)); /* 34848080 ori a0,a0,0x8080 */
 set(m,4u,lo(m,4u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d5d54));goto dispatch;
L_002d5d54:
 STEP(UINT32_C(0x002d5d54)); /* 00042438 dsll a0,a0,16 */
 set(m,4u,lo(m,4u)<<16u);target=sx(UINT32_C(0x002d5d58));goto dispatch;
L_002d5d58:
 STEP(UINT32_C(0x002d5d58)); /* 34848080 ori a0,a0,0x8080 */
 set(m,4u,lo(m,4u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d5d5c));goto dispatch;
L_002d5d5c:
 STEP(UINT32_C(0x002d5d5c)); /* 70681248 mmi 70681248 */
 {uint8_t a[16],b[16],out[16];memcpy(a,m->gpr[3],16);memcpy(b,m->gpr[8],16);for(unsigned j=0;j<16;++j)out[j]=(uint8_t)(a[j]-b[j]);memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d5d60));goto dispatch;
L_002d5d60:
 STEP(UINT32_C(0x002d5d60)); /* 70031ce9 mmi 70031ce9 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=~(m->gpr[0][j]|m->gpr[3][j]);memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002d5d64));goto dispatch;
L_002d5d64:
 STEP(UINT32_C(0x002d5d64)); /* 70844b89 mmi 70844b89 */
 {uint32_t out[4]={m->gpr[4][0],m->gpr[4][1],m->gpr[4][0],m->gpr[4][1]};memcpy(m->gpr[9],out,16);}target=sx(UINT32_C(0x002d5d68));goto dispatch;
L_002d5d68:
 STEP(UINT32_C(0x002d5d68)); /* 70431489 mmi 70431489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[3][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d5d6c));goto dispatch;
L_002d5d6c:
 STEP(UINT32_C(0x002d5d6c)); /* 70491489 mmi 70491489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[9][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d5d70));goto dispatch;
L_002d5d70:
 STEP(UINT32_C(0x002d5d70)); /* 70481ba9 mmi 70481ba9 */
 {uint32_t out[4]={m->gpr[2][2],m->gpr[2][3],m->gpr[8][2],m->gpr[8][3]};memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002d5d74));goto dispatch;
L_002d5d74:
 STEP(UINT32_C(0x002d5d74)); /* 00623025 or a2,v1,v0 */
 set(m,6u,lo(m,3u)|lo(m,2u));target=sx(UINT32_C(0x002d5d78));goto dispatch;
L_002d5d78:
 STEP(UINT32_C(0x002d5d78)); /* 54c00029 bnel a2,zero,002d5e20 */
 if(lo(m,6u)!=lo(m,0u)){STEP(UINT32_C(0x002d5d7c));set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d5e20));}else target=sx(UINT32_C(0x002d5d80));goto dispatch;
L_002d5d7c:
 STEP(UINT32_C(0x002d5d7c)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d5d80));goto dispatch;
L_002d5d80:
 STEP(UINT32_C(0x002d5d80)); /* 24a50010 addiu a1,a1,16 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d5d84));goto dispatch;
L_002d5d84:
 STEP(UINT32_C(0x002d5d84)); /* 78a20000 lq v0,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x002d5d88));goto dispatch;
L_002d5d88:
 STEP(UINT32_C(0x002d5d88)); /* 70021ce9 mmi 70021ce9 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=~(m->gpr[0][j]|m->gpr[2][j]);memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002d5d8c));goto dispatch;
L_002d5d8c:
 STEP(UINT32_C(0x002d5d8c)); /* 70481248 mmi 70481248 */
 {uint8_t a[16],b[16],out[16];memcpy(a,m->gpr[2],16);memcpy(b,m->gpr[8],16);for(unsigned j=0;j<16;++j)out[j]=(uint8_t)(a[j]-b[j]);memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d5d90));goto dispatch;
L_002d5d90:
 STEP(UINT32_C(0x002d5d90)); /* 70431489 mmi 70431489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[3][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d5d94));goto dispatch;
L_002d5d94:
 STEP(UINT32_C(0x002d5d94)); /* 70492489 mmi 70492489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[9][j];memcpy(m->gpr[4],out,16);}target=sx(UINT32_C(0x002d5d98));goto dispatch;
L_002d5d98:
 STEP(UINT32_C(0x002d5d98)); /* 70861ba9 mmi 70861ba9 */
 {uint32_t out[4]={m->gpr[4][2],m->gpr[4][3],m->gpr[6][2],m->gpr[6][3]};memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002d5d9c));goto dispatch;
L_002d5d9c:
 STEP(UINT32_C(0x002d5d9c)); /* 00641825 or v1,v1,a0 */
 set(m,3u,lo(m,3u)|lo(m,4u));target=sx(UINT32_C(0x002d5da0));goto dispatch;
L_002d5da0:
 STEP(UINT32_C(0x002d5da0)); /* 5060fff8 beql v1,zero,002d5d84 */
 if(lo(m,3u)==lo(m,0u)){STEP(UINT32_C(0x002d5da4));set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d5d84));}else target=sx(UINT32_C(0x002d5da8));goto dispatch;
L_002d5da4:
 STEP(UINT32_C(0x002d5da4)); /* 24a50010 addiu a1,a1,16 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d5da8));goto dispatch;
L_002d5da8:
 STEP(UINT32_C(0x002d5da8)); /* 1000001d beq zero,zero,002d5e20 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d5dac));set(m,4u,lo(m,5u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d5e20):UINT32_C(0x002d5db0));goto dispatch;}
L_002d5dac:
 STEP(UINT32_C(0x002d5dac)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d5db0));goto dispatch;
L_002d5db0:
 STEP(UINT32_C(0x002d5db0)); /* dca30000 ld v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d5db4));goto dispatch;
L_002d5db4:
 STEP(UINT32_C(0x002d5db4)); /* 3c048080 lui a0,zero,0x8080 */
 set(m,4u,sx(UINT32_C(0x80800000)));target=sx(UINT32_C(0x002d5db8));goto dispatch;
L_002d5db8:
 STEP(UINT32_C(0x002d5db8)); /* 34848080 ori a0,a0,0x8080 */
 set(m,4u,lo(m,4u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d5dbc));goto dispatch;
L_002d5dbc:
 STEP(UINT32_C(0x002d5dbc)); /* 00042438 dsll a0,a0,16 */
 set(m,4u,lo(m,4u)<<16u);target=sx(UINT32_C(0x002d5dc0));goto dispatch;
L_002d5dc0:
 STEP(UINT32_C(0x002d5dc0)); /* 34848080 ori a0,a0,0x8080 */
 set(m,4u,lo(m,4u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d5dc4));goto dispatch;
L_002d5dc4:
 STEP(UINT32_C(0x002d5dc4)); /* 00042438 dsll a0,a0,16 */
 set(m,4u,lo(m,4u)<<16u);target=sx(UINT32_C(0x002d5dc8));goto dispatch;
L_002d5dc8:
 STEP(UINT32_C(0x002d5dc8)); /* 34848080 ori a0,a0,0x8080 */
 set(m,4u,lo(m,4u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d5dcc));goto dispatch;
L_002d5dcc:
 STEP(UINT32_C(0x002d5dcc)); /* 0062102f dsubu v0,v1,v0 */
 set(m,2u,lo(m,3u)-lo(m,2u));target=sx(UINT32_C(0x002d5dd0));goto dispatch;
L_002d5dd0:
 STEP(UINT32_C(0x002d5dd0)); /* 00031827 nor v1,zero,v1 */
 set(m,3u,~(lo(m,0u)|lo(m,3u)));target=sx(UINT32_C(0x002d5dd4));goto dispatch;
L_002d5dd4:
 STEP(UINT32_C(0x002d5dd4)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d5dd8));goto dispatch;
L_002d5dd8:
 STEP(UINT32_C(0x002d5dd8)); /* 00441024 and v0,v0,a0 */
 set(m,2u,lo(m,2u)&lo(m,4u));target=sx(UINT32_C(0x002d5ddc));goto dispatch;
L_002d5ddc:
 STEP(UINT32_C(0x002d5ddc)); /* 54400010 bnel v0,zero,002d5e20 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d5de0));set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d5e20));}else target=sx(UINT32_C(0x002d5de4));goto dispatch;
L_002d5de0:
 STEP(UINT32_C(0x002d5de0)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d5de4));goto dispatch;
L_002d5de4:
 STEP(UINT32_C(0x002d5de4)); /* 3c060101 lui a2,zero,0x101 */
 set(m,6u,sx(UINT32_C(0x01010000)));target=sx(UINT32_C(0x002d5de8));goto dispatch;
L_002d5de8:
 STEP(UINT32_C(0x002d5de8)); /* 34c60101 ori a2,a2,0x101 */
 set(m,6u,lo(m,6u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d5dec));goto dispatch;
L_002d5dec:
 STEP(UINT32_C(0x002d5dec)); /* 00063438 dsll a2,a2,16 */
 set(m,6u,lo(m,6u)<<16u);target=sx(UINT32_C(0x002d5df0));goto dispatch;
L_002d5df0:
 STEP(UINT32_C(0x002d5df0)); /* 34c60101 ori a2,a2,0x101 */
 set(m,6u,lo(m,6u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d5df4));goto dispatch;
L_002d5df4:
 STEP(UINT32_C(0x002d5df4)); /* 00063438 dsll a2,a2,16 */
 set(m,6u,lo(m,6u)<<16u);target=sx(UINT32_C(0x002d5df8));goto dispatch;
L_002d5df8:
 STEP(UINT32_C(0x002d5df8)); /* 34c60101 ori a2,a2,0x101 */
 set(m,6u,lo(m,6u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d5dfc));goto dispatch;
L_002d5dfc:
 STEP(UINT32_C(0x002d5dfc)); /* 24a50008 addiu a1,a1,8 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d5e00));goto dispatch;
L_002d5e00:
 STEP(UINT32_C(0x002d5e00)); /* dca20000 ld v0,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,2u,value64);target=sx(UINT32_C(0x002d5e04));goto dispatch;
L_002d5e04:
 STEP(UINT32_C(0x002d5e04)); /* 00021827 nor v1,zero,v0 */
 set(m,3u,~(lo(m,0u)|lo(m,2u)));target=sx(UINT32_C(0x002d5e08));goto dispatch;
L_002d5e08:
 STEP(UINT32_C(0x002d5e08)); /* 0046102f dsubu v0,v0,a2 */
 set(m,2u,lo(m,2u)-lo(m,6u));target=sx(UINT32_C(0x002d5e0c));goto dispatch;
L_002d5e0c:
 STEP(UINT32_C(0x002d5e0c)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d5e10));goto dispatch;
L_002d5e10:
 STEP(UINT32_C(0x002d5e10)); /* 00441024 and v0,v0,a0 */
 set(m,2u,lo(m,2u)&lo(m,4u));target=sx(UINT32_C(0x002d5e14));goto dispatch;
L_002d5e14:
 STEP(UINT32_C(0x002d5e14)); /* 5040fffa beql v0,zero,002d5e00 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d5e18));set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d5e00));}else target=sx(UINT32_C(0x002d5e1c));goto dispatch;
L_002d5e18:
 STEP(UINT32_C(0x002d5e18)); /* 24a50008 addiu a1,a1,8 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d5e1c));goto dispatch;
L_002d5e1c:
 STEP(UINT32_C(0x002d5e1c)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d5e20));goto dispatch;
L_002d5e20:
 STEP(UINT32_C(0x002d5e20)); /* 80820000 lb v0,0x0(a0) */
 {uint8_t byte;READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002d5e24));goto dispatch;
L_002d5e24:
 STEP(UINT32_C(0x002d5e24)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d5e28));goto dispatch;
L_002d5e28:
 STEP(UINT32_C(0x002d5e28)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d5e2c));goto dispatch;
L_002d5e2c:
 STEP(UINT32_C(0x002d5e2c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d5e30));goto dispatch;
L_002d5e30:
 STEP(UINT32_C(0x002d5e30)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d5e34));goto dispatch;
L_002d5e34:
 STEP(UINT32_C(0x002d5e34)); /* 5440fffa bnel v0,zero,002d5e20 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d5e38));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d5e20));}else target=sx(UINT32_C(0x002d5e3c));goto dispatch;
L_002d5e38:
 STEP(UINT32_C(0x002d5e38)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d5e3c));goto dispatch;
L_002d5e3c:
 STEP(UINT32_C(0x002d5e3c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d5e40));set(m,2u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,7u)));goto dispatch;
L_002d5e40:
 STEP(UINT32_C(0x002d5e40)); /* 00871023 subu v0,a0,a3 */
 set(m,2u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x002d5e44));goto dispatch;
L_002a8af8:
 STEP(UINT32_C(0x002a8af8)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002a8afc));goto dispatch;
L_002a8afc:
 STEP(UINT32_C(0x002a8afc)); /* 2482ffff addiu v0,a0,-1 */
 set(m,2u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002a8b00));goto dispatch;
L_002a8b00:
 STEP(UINT32_C(0x002a8b00)); /* 28840011 slti a0,a0,17 */
 set(m,4u,((int64_t)lo(m,4u)<INT64_C(17)));target=sx(UINT32_C(0x002a8b04));goto dispatch;
L_002a8b04:
 STEP(UINT32_C(0x002a8b04)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002a8b08));goto dispatch;
L_002a8b08:
 STEP(UINT32_C(0x002a8b08)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002a8b0c));goto dispatch;
L_002a8b0c:
 STEP(UINT32_C(0x002a8b0c)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002a8b10));goto dispatch;
L_002a8b10:
 STEP(UINT32_C(0x002a8b10)); /* 14800005 bne a0,zero,002a8b28 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002a8b14));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002a8b28):UINT32_C(0x002a8b18));goto dispatch;}
L_002a8b14:
 STEP(UINT32_C(0x002a8b14)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002a8b18));goto dispatch;
L_002a8b18:
 STEP(UINT32_C(0x002a8b18)); /* 70402804 mmi 70402804 */
 {uint64_t input=lo(m,2u);uint32_t a=plzcw((uint32_t)input),b=plzcw((uint32_t)(input>>32));set(m,5u,(uint64_t)a|((uint64_t)b<<32));}target=sx(UINT32_C(0x002a8b1c));goto dispatch;
L_002a8b1c:
 STEP(UINT32_C(0x002a8b1c)); /* 2403001b addiu v1,zero,27 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001b)));target=sx(UINT32_C(0x002a8b20));goto dispatch;
L_002a8b20:
 STEP(UINT32_C(0x002a8b20)); /* 30a200ff andi v0,a1,0xff */
 set(m,2u,lo(m,5u) & UINT64_C(0xff));target=sx(UINT32_C(0x002a8b24));goto dispatch;
L_002a8b24:
 STEP(UINT32_C(0x002a8b24)); /* 00622823 subu a1,v1,v0 */
 set(m,5u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002a8b28));goto dispatch;
L_002a8b28:
 STEP(UINT32_C(0x002a8b28)); /* 00051040 sll v0,a1,1 */
 set(m,2u,sx((uint32_t)lo(m,5u)<<1u));target=sx(UINT32_C(0x002a8b2c));goto dispatch;
L_002a8b2c:
 STEP(UINT32_C(0x002a8b2c)); /* 00451021 addu v0,v0,a1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002a8b30));goto dispatch;
L_002a8b30:
 STEP(UINT32_C(0x002a8b30)); /* 00021080 sll v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<2u));target=sx(UINT32_C(0x002a8b34));goto dispatch;
L_002a8b34:
 STEP(UINT32_C(0x002a8b34)); /* 3c100057 lui s0,zero,0x57 */
 set(m,16u,sx(UINT32_C(0x00570000)));target=sx(UINT32_C(0x002a8b38));goto dispatch;
L_002a8b38:
 STEP(UINT32_C(0x002a8b38)); /* 26107ec0 addiu s0,s0,32448 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00007ec0)));target=sx(UINT32_C(0x002a8b3c));goto dispatch;
L_002a8b3c:
 STEP(UINT32_C(0x002a8b3c)); /* 02028021 addu s0,s0,v0 */
 set(m,16u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002a8b40));goto dispatch;
L_002a8b40:
 STEP(UINT32_C(0x002a8b40)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002a8b48));STEP(UINT32_C(0x002a8b44));/* nop */target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002a8b44:
 STEP(UINT32_C(0x002a8b44)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a8b48));goto dispatch;
L_002a8b48:
 STEP(UINT32_C(0x002a8b48)); /* 0040882d daddu s1,v0,zero */
 set(m,17u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a8b4c));goto dispatch;
L_002a8b4c:
 STEP(UINT32_C(0x002a8b4c)); /* 8e020000 lw v0,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a8b50));goto dispatch;
L_002a8b50:
 STEP(UINT32_C(0x002a8b50)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002a8b54));goto dispatch;
L_002a8b54:
 STEP(UINT32_C(0x002a8b54)); /* 14400006 bne v0,zero,002a8b70 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002a8b58));set(m,5u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002a8b70):UINT32_C(0x002a8b5c));goto dispatch;}
L_002a8b58:
 STEP(UINT32_C(0x002a8b58)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a8b5c));goto dispatch;
L_002a8b5c:
 STEP(UINT32_C(0x002a8b5c)); /* 0c0aa2ac jal 002a8ab0 */
 set(m,31u,UINT64_C(0x002a8b64));STEP(UINT32_C(0x002a8b60));/* nop */target=sx(UINT32_C(0x002a8ab0));goto dispatch;
L_002a8b60:
 STEP(UINT32_C(0x002a8b60)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a8b64));goto dispatch;
L_002a8b64:
 STEP(UINT32_C(0x002a8b64)); /* 10000006 beq zero,zero,002a8b80 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002a8b68));set(m,16u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002a8b80):UINT32_C(0x002a8b6c));goto dispatch;}
L_002a8b68:
 STEP(UINT32_C(0x002a8b68)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a8b6c));goto dispatch;
L_002a8b6c:
 STEP(UINT32_C(0x002a8b6c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a8b70));goto dispatch;
L_002a8b70:
 STEP(UINT32_C(0x002a8b70)); /* 8c420008 lw v0,0x8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a8b74));goto dispatch;
L_002a8b74:
 STEP(UINT32_C(0x002a8b74)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002a8b7c));STEP(UINT32_C(0x002a8b78));set(m,4u,lo(m,16u)+lo(m,0u));goto dispatch;
L_002a8b78:
 STEP(UINT32_C(0x002a8b78)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002a8b7c));goto dispatch;
L_002a8b7c:
 STEP(UINT32_C(0x002a8b7c)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a8b80));goto dispatch;
L_002a8b80:
 STEP(UINT32_C(0x002a8b80)); /* 12200004 beq s1,zero,002a8b94 */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002a8b84));set(m,2u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002a8b94):UINT32_C(0x002a8b88));goto dispatch;}
L_002a8b84:
 STEP(UINT32_C(0x002a8b84)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002a8b88));goto dispatch;
L_002a8b88:
 STEP(UINT32_C(0x002a8b88)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002a8b90));STEP(UINT32_C(0x002a8b8c));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002a8b8c:
 STEP(UINT32_C(0x002a8b8c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a8b90));goto dispatch;
L_002a8b90:
 STEP(UINT32_C(0x002a8b90)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002a8b94));goto dispatch;
L_002a8b94:
 STEP(UINT32_C(0x002a8b94)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002a8b98));goto dispatch;
L_002a8b98:
 STEP(UINT32_C(0x002a8b98)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002a8b9c));goto dispatch;
L_002a8b9c:
 STEP(UINT32_C(0x002a8b9c)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002a8ba0));goto dispatch;
L_002a8ba0:
 STEP(UINT32_C(0x002a8ba0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a8ba4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002a8ba4:
 STEP(UINT32_C(0x002a8ba4)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002a8ba8));goto dispatch;
L_002a8ab0:
 STEP(UINT32_C(0x002a8ab0)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002a8ab4));goto dispatch;
L_002a8ab4:
 STEP(UINT32_C(0x002a8ab4)); /* 8f82deec lw v0,-0x2114(gp) */
 READ((uint32_t)lo(m,28u)+UINT32_C(0xffffdeec),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a8ab8));goto dispatch;
L_002a8ab8:
 STEP(UINT32_C(0x002a8ab8)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002a8abc));goto dispatch;
L_002a8abc:
 STEP(UINT32_C(0x002a8abc)); /* 0080382d daddu a3,a0,zero */
 set(m,7u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002a8ac0));goto dispatch;
L_002a8ac0:
 STEP(UINT32_C(0x002a8ac0)); /* 3c03002b lui v1,zero,0x2b */
 set(m,3u,sx(UINT32_C(0x002b0000)));target=sx(UINT32_C(0x002a8ac4));goto dispatch;
L_002a8ac4:
 STEP(UINT32_C(0x002a8ac4)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002a8ac8));goto dispatch;
L_002a8ac8:
 STEP(UINT32_C(0x002a8ac8)); /* 8c460000 lw a2,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002a8acc));goto dispatch;
L_002a8acc:
 STEP(UINT32_C(0x002a8acc)); /* 24638a30 addiu v1,v1,-30160 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffff8a30)));target=sx(UINT32_C(0x002a8ad0));goto dispatch;
L_002a8ad0:
 STEP(UINT32_C(0x002a8ad0)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002a8ad4));goto dispatch;
L_002a8ad4:
 STEP(UINT32_C(0x002a8ad4)); /* af86deec sw a2,-0x2114(gp) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdeec),&value32,4u);target=sx(UINT32_C(0x002a8ad8));goto dispatch;
L_002a8ad8:
 STEP(UINT32_C(0x002a8ad8)); /* a4400014 sh zero,0x14(v0) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000014),&value16,2u);target=sx(UINT32_C(0x002a8adc));goto dispatch;
L_002a8adc:
 STEP(UINT32_C(0x002a8adc)); /* ac430008 sw v1,0x8(v0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002a8ae0));goto dispatch;
L_002a8ae0:
 STEP(UINT32_C(0x002a8ae0)); /* 94e6000a lhu a2,0xa(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x0000000a),&value16,2u);set(m,6u,value16);target=sx(UINT32_C(0x002a8ae4));goto dispatch;
L_002a8ae4:
 STEP(UINT32_C(0x002a8ae4)); /* ace20000 sw v0,0x0(a3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002a8ae8));goto dispatch;
L_002a8ae8:
 STEP(UINT32_C(0x002a8ae8)); /* a4460016 sh a2,0x16(v0) */
 value16=(uint16_t)lo(m,6u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000016),&value16,2u);target=sx(UINT32_C(0x002a8aec));goto dispatch;
L_002a8aec:
 STEP(UINT32_C(0x002a8aec)); /* ac47000c sw a3,0xc(v0) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002a8af0));goto dispatch;
L_002a8af0:
 STEP(UINT32_C(0x002a8af0)); /* 080aa28c j 002a8a30 */
 STEP(UINT32_C(0x002a8af4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002a8a30));goto dispatch;
L_002a8af4:
 STEP(UINT32_C(0x002a8af4)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002a8af8));goto dispatch;
L_002a8a30:
 STEP(UINT32_C(0x002a8a30)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002a8a34));goto dispatch;
L_002a8a34:
 STEP(UINT32_C(0x002a8a34)); /* 00a0402d daddu t0,a1,zero */
 set(m,8u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002a8a38));goto dispatch;
L_002a8a38:
 STEP(UINT32_C(0x002a8a38)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002a8a3c));goto dispatch;
L_002a8a3c:
 STEP(UINT32_C(0x002a8a3c)); /* 0080382d daddu a3,a0,zero */
 set(m,7u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002a8a40));goto dispatch;
L_002a8a40:
 STEP(UINT32_C(0x002a8a40)); /* ffbf0008 sd ra,0x8(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002a8a44));goto dispatch;
L_002a8a44:
 STEP(UINT32_C(0x002a8a44)); /* 95020014 lhu v0,0x14(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000014),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002a8a48));goto dispatch;
L_002a8a48:
 STEP(UINT32_C(0x002a8a48)); /* 84ea000a lh t2,0xa(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x0000000a),&value16,2u);set(m,10u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002a8a4c));goto dispatch;
L_002a8a4c:
 STEP(UINT32_C(0x002a8a4c)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002a8a50));goto dispatch;
L_002a8a50:
 STEP(UINT32_C(0x002a8a50)); /* 85030016 lh v1,0x16(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000016),&value16,2u);set(m,3u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002a8a54));goto dispatch;
L_002a8a54:
 STEP(UINT32_C(0x002a8a54)); /* a5020014 sh v0,0x14(t0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000014),&value16,2u);target=sx(UINT32_C(0x002a8a58));goto dispatch;
L_002a8a58:
 STEP(UINT32_C(0x002a8a58)); /* 00021400 sll v0,v0,16 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<16u));target=sx(UINT32_C(0x002a8a5c));goto dispatch;
L_002a8a5c:
 STEP(UINT32_C(0x002a8a5c)); /* 01432823 subu a1,t2,v1 */
 set(m,5u,sx((uint32_t)lo(m,10u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002a8a60));goto dispatch;
L_002a8a60:
 STEP(UINT32_C(0x002a8a60)); /* 2463ffff addiu v1,v1,-1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002a8a64));goto dispatch;
L_002a8a64:
 STEP(UINT32_C(0x002a8a64)); /* 84e60008 lh a2,0x8(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value16,2u);set(m,6u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002a8a68));goto dispatch;
L_002a8a68:
 STEP(UINT32_C(0x002a8a68)); /* 00024c03 sra t1,v0,16 */
 set(m,9u,sx((uint32_t)((int32_t)lo(m,2u)>>16u)));target=sx(UINT32_C(0x002a8a6c));goto dispatch;
L_002a8a6c:
 STEP(UINT32_C(0x002a8a6c)); /* 8d070004 lw a3,0x4(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000004),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002a8a70));goto dispatch;
L_002a8a70:
 STEP(UINT32_C(0x002a8a70)); /* 00031400 sll v0,v1,16 */
 set(m,2u,sx((uint32_t)lo(m,3u)<<16u));target=sx(UINT32_C(0x002a8a74));goto dispatch;
L_002a8a74:
 STEP(UINT32_C(0x002a8a74)); /* 00a62818 mult_rd a1,a1,a2 */
 {int64_t product;if(lo(m,5u)!=sx((uint32_t)lo(m,5u))||lo(m,6u)!=sx((uint32_t)lo(m,6u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,5u)*(int64_t)(int32_t)lo(m,6u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,5u,m->lo);}target=sx(UINT32_C(0x002a8a78));goto dispatch;
L_002a8a78:
 STEP(UINT32_C(0x002a8a78)); /* a5030016 sh v1,0x16(t0) */
 value16=(uint16_t)lo(m,3u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000016),&value16,2u);target=sx(UINT32_C(0x002a8a7c));goto dispatch;
L_002a8a7c:
 STEP(UINT32_C(0x002a8a7c)); /* 14400007 bne v0,zero,002a8a9c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002a8a80));set(m,16u,sx((uint32_t)lo(m,7u)+(uint32_t)lo(m,5u)));target=sx(taken?UINT32_C(0x002a8a9c):UINT32_C(0x002a8a84));goto dispatch;}
L_002a8a80:
 STEP(UINT32_C(0x002a8a80)); /* 00e58021 addu s0,a3,a1 */
 set(m,16u,sx((uint32_t)lo(m,7u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002a8a84));goto dispatch;
L_002a8a84:
 STEP(UINT32_C(0x002a8a84)); /* 3c02002b lui v0,zero,0x2b */
 set(m,2u,sx(UINT32_C(0x002b0000)));target=sx(UINT32_C(0x002a8a88));goto dispatch;
L_002a8a88:
 STEP(UINT32_C(0x002a8a88)); /* 244289e0 addiu v0,v0,-30240 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff89e0)));target=sx(UINT32_C(0x002a8a8c));goto dispatch;
L_002a8a8c:
 STEP(UINT32_C(0x002a8a8c)); /* 152a0003 bne t1,t2,002a8a9c */
 {int taken=(lo(m,9u)!=lo(m,10u));STEP(UINT32_C(0x002a8a90));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002a8a9c):UINT32_C(0x002a8a94));goto dispatch;}
L_002a8a90:
 STEP(UINT32_C(0x002a8a90)); /* ad020008 sw v0,0x8(t0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002a8a94));goto dispatch;
L_002a8a94:
 STEP(UINT32_C(0x002a8a94)); /* 0c0aa270 jal 002a89c0 */
 set(m,31u,UINT64_C(0x002a8a9c));STEP(UINT32_C(0x002a8a98));/* nop */target=sx(UINT32_C(0x002a89c0));goto dispatch;
L_002a8a98:
 STEP(UINT32_C(0x002a8a98)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a8a9c));goto dispatch;
L_002a8a9c:
 STEP(UINT32_C(0x002a8a9c)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002a8aa0));goto dispatch;
L_002a8aa0:
 STEP(UINT32_C(0x002a8aa0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002a8aa4));goto dispatch;
L_002a8aa4:
 STEP(UINT32_C(0x002a8aa4)); /* dfbf0008 ld ra,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002a8aa8));goto dispatch;
L_002a8aa8:
 STEP(UINT32_C(0x002a8aa8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a8aac));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002a8aac:
 STEP(UINT32_C(0x002a8aac)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002a8ab0));goto dispatch;
L_002a89e0:
 STEP(UINT32_C(0x002a89e0)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002a89e4));goto dispatch;
L_002a89e4:
 STEP(UINT32_C(0x002a89e4)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002a89e8));goto dispatch;
L_002a89e8:
 STEP(UINT32_C(0x002a89e8)); /* ffbf0008 sd ra,0x8(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002a89ec));goto dispatch;
L_002a89ec:
 STEP(UINT32_C(0x002a89ec)); /* 94a20014 lhu v0,0x14(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000014),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002a89f0));goto dispatch;
L_002a89f0:
 STEP(UINT32_C(0x002a89f0)); /* 8cb00010 lw s0,0x10(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000010),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002a89f4));goto dispatch;
L_002a89f4:
 STEP(UINT32_C(0x002a89f4)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002a89f8));goto dispatch;
L_002a89f8:
 STEP(UINT32_C(0x002a89f8)); /* a4a20014 sh v0,0x14(a1) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000014),&value16,2u);target=sx(UINT32_C(0x002a89fc));goto dispatch;
L_002a89fc:
 STEP(UINT32_C(0x002a89fc)); /* 00021400 sll v0,v0,16 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<16u));target=sx(UINT32_C(0x002a8a00));goto dispatch;
L_002a8a00:
 STEP(UINT32_C(0x002a8a00)); /* 8e060008 lw a2,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002a8a04));goto dispatch;
L_002a8a04:
 STEP(UINT32_C(0x002a8a04)); /* 00021403 sra v0,v0,16 */
 set(m,2u,sx((uint32_t)((int32_t)lo(m,2u)>>16u)));target=sx(UINT32_C(0x002a8a08));goto dispatch;
L_002a8a08:
 STEP(UINT32_C(0x002a8a08)); /* 8483000a lh v1,0xa(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x0000000a),&value16,2u);set(m,3u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002a8a0c));goto dispatch;
L_002a8a0c:
 STEP(UINT32_C(0x002a8a0c)); /* 14430003 bne v0,v1,002a8a1c */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x002a8a10));value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000010),&value32,4u);target=sx(taken?UINT32_C(0x002a8a1c):UINT32_C(0x002a8a14));goto dispatch;}
L_002a8a10:
 STEP(UINT32_C(0x002a8a10)); /* aca60010 sw a2,0x10(a1) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002a8a14));goto dispatch;
L_002a8a14:
 STEP(UINT32_C(0x002a8a14)); /* 0c0aa270 jal 002a89c0 */
 set(m,31u,UINT64_C(0x002a8a1c));STEP(UINT32_C(0x002a8a18));/* nop */target=sx(UINT32_C(0x002a89c0));goto dispatch;
L_002a8a18:
 STEP(UINT32_C(0x002a8a18)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a8a1c));goto dispatch;
L_002a8a1c:
 STEP(UINT32_C(0x002a8a1c)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002a8a20));goto dispatch;
L_002a8a20:
 STEP(UINT32_C(0x002a8a20)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002a8a24));goto dispatch;
L_002a8a24:
 STEP(UINT32_C(0x002a8a24)); /* dfbf0008 ld ra,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002a8a28));goto dispatch;
L_002a8a28:
 STEP(UINT32_C(0x002a8a28)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a8a2c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002a8a2c:
 STEP(UINT32_C(0x002a8a2c)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002a8a30));goto dispatch;
L_002a89c0:
 STEP(UINT32_C(0x002a89c0)); /* 8c830004 lw v1,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002a89c4));goto dispatch;
L_002a89c4:
 STEP(UINT32_C(0x002a89c4)); /* 10600003 beq v1,zero,002a89d4 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002a89c8));/* nop */target=sx(taken?UINT32_C(0x002a89d4):UINT32_C(0x002a89cc));goto dispatch;}
L_002a89c8:
 STEP(UINT32_C(0x002a89c8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002a89cc));goto dispatch;
L_002a89cc:
 STEP(UINT32_C(0x002a89cc)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002a89d0));goto dispatch;
L_002a89d0:
 STEP(UINT32_C(0x002a89d0)); /* ac820004 sw v0,0x4(a0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002a89d4));goto dispatch;
L_002a89d4:
 STEP(UINT32_C(0x002a89d4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002a89d8));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_002a89d8:
 STEP(UINT32_C(0x002a89d8)); /* ac830000 sw v1,0x0(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002a89dc));goto dispatch;
L_002cd418:
 STEP(UINT32_C(0x002cd418)); /* 27bdff40 addiu sp,sp,-192 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff40)));target=sx(UINT32_C(0x002cd41c));goto dispatch;
L_002cd41c:
 STEP(UINT32_C(0x002cd41c)); /* ffbe00a0 sd s8,0xa0(sp) */
 value64=lo(m,30u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),&value64,8u);target=sx(UINT32_C(0x002cd420));goto dispatch;
L_002cd420:
 STEP(UINT32_C(0x002cd420)); /* ffb70090 sd s7,0x90(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x002cd424));goto dispatch;
L_002cd424:
 STEP(UINT32_C(0x002cd424)); /* 00c0f02d daddu s8,a2,zero */
 set(m,30u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002cd428));goto dispatch;
L_002cd428:
 STEP(UINT32_C(0x002cd428)); /* ffb60080 sd s6,0x80(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002cd42c));goto dispatch;
L_002cd42c:
 STEP(UINT32_C(0x002cd42c)); /* 0160b82d daddu s7,t3,zero */
 set(m,23u,lo(m,11u)+lo(m,0u));target=sx(UINT32_C(0x002cd430));goto dispatch;
L_002cd430:
 STEP(UINT32_C(0x002cd430)); /* ffb50070 sd s5,0x70(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002cd434));goto dispatch;
L_002cd434:
 STEP(UINT32_C(0x002cd434)); /* 00a0b02d daddu s6,a1,zero */
 set(m,22u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002cd438));goto dispatch;
L_002cd438:
 STEP(UINT32_C(0x002cd438)); /* ffb40060 sd s4,0x60(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002cd43c));goto dispatch;
L_002cd43c:
 STEP(UINT32_C(0x002cd43c)); /* 0120a82d daddu s5,t1,zero */
 set(m,21u,lo(m,9u)+lo(m,0u));target=sx(UINT32_C(0x002cd440));goto dispatch;
L_002cd440:
 STEP(UINT32_C(0x002cd440)); /* ffb30050 sd s3,0x50(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002cd444));goto dispatch;
L_002cd444:
 STEP(UINT32_C(0x002cd444)); /* 00e0a02d daddu s4,a3,zero */
 set(m,20u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002cd448));goto dispatch;
L_002cd448:
 STEP(UINT32_C(0x002cd448)); /* ffb20040 sd s2,0x40(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cd44c));goto dispatch;
L_002cd44c:
 STEP(UINT32_C(0x002cd44c)); /* 0100982d daddu s3,t0,zero */
 set(m,19u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002cd450));goto dispatch;
L_002cd450:
 STEP(UINT32_C(0x002cd450)); /* ffb10030 sd s1,0x30(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cd454));goto dispatch;
L_002cd454:
 STEP(UINT32_C(0x002cd454)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cd458));goto dispatch;
L_002cd458:
 STEP(UINT32_C(0x002cd458)); /* ffbf00b0 sd ra,0xb0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000000b0),&value64,8u);target=sx(UINT32_C(0x002cd45c));goto dispatch;
L_002cd45c:
 STEP(UINT32_C(0x002cd45c)); /* 0140882d daddu s1,t2,zero */
 set(m,17u,lo(m,10u)+lo(m,0u));target=sx(UINT32_C(0x002cd460));goto dispatch;
L_002cd460:
 STEP(UINT32_C(0x002cd460)); /* 13c00006 beq s8,zero,002cd47c */
 {int taken=(lo(m,30u)==lo(m,0u));STEP(UINT32_C(0x002cd464));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(taken?UINT32_C(0x002cd47c):UINT32_C(0x002cd468));goto dispatch;}
L_002cd464:
 STEP(UINT32_C(0x002cd464)); /* ffb00020 sd s0,0x20(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cd468));goto dispatch;
L_002cd468:
 STEP(UINT32_C(0x002cd468)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002cd46c));goto dispatch;
L_002cd46c:
 STEP(UINT32_C(0x002cd46c)); /* 0c0b7758 jal 002ddd60 */
 set(m,31u,UINT64_C(0x002cd474));STEP(UINT32_C(0x002cd470));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffadd8)));target=sx(UINT32_C(0x002ddd60));goto dispatch;
L_002cd470:
 STEP(UINT32_C(0x002cd470)); /* 2484add8 addiu a0,a0,-21032 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffadd8)));target=sx(UINT32_C(0x002cd474));goto dispatch;
L_002cd474:
 STEP(UINT32_C(0x002cd474)); /* 10000075 beq zero,zero,002cd64c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd478));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002cd64c):UINT32_C(0x002cd47c));goto dispatch;}
L_002cd478:
 STEP(UINT32_C(0x002cd478)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002cd47c));goto dispatch;
L_002cd47c:
 STEP(UINT32_C(0x002cd47c)); /* 0c0b6fb8 jal 002dbee0 */
 set(m,31u,UINT64_C(0x002cd484));STEP(UINT32_C(0x002cd480));READ((uint32_t)lo(m,18u)+UINT32_C(0x00000028),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbee0));goto dispatch;
L_002cd480:
 STEP(UINT32_C(0x002cd480)); /* 8e440028 lw a0,0x28(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000028),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd484));goto dispatch;
L_002cd484:
 STEP(UINT32_C(0x002cd484)); /* 3283003f andi v1,s4,0x3f */
 set(m,3u,lo(m,20u) & UINT64_C(0x3f));target=sx(UINT32_C(0x002cd488));goto dispatch;
L_002cd488:
 STEP(UINT32_C(0x002cd488)); /* 10600006 beq v1,zero,002cd4a4 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002cd48c));set(m,4u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002cd4a4):UINT32_C(0x002cd490));goto dispatch;}
L_002cd48c:
 STEP(UINT32_C(0x002cd48c)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002cd490));goto dispatch;
L_002cd490:
 STEP(UINT32_C(0x002cd490)); /* 3c050055 lui a1,zero,0x55 */
 set(m,5u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002cd494));goto dispatch;
L_002cd494:
 STEP(UINT32_C(0x002cd494)); /* 2484ae00 addiu a0,a0,-20992 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffae00)));target=sx(UINT32_C(0x002cd498));goto dispatch;
L_002cd498:
 STEP(UINT32_C(0x002cd498)); /* 24a5ae38 addiu a1,a1,-20936 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffae38)));target=sx(UINT32_C(0x002cd49c));goto dispatch;
L_002cd49c:
 STEP(UINT32_C(0x002cd49c)); /* 10000008 beq zero,zero,002cd4c0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd4a0));set(m,6u,lo(m,20u)+lo(m,0u));target=sx(taken?UINT32_C(0x002cd4c0):UINT32_C(0x002cd4a4));goto dispatch;}
L_002cd4a0:
 STEP(UINT32_C(0x002cd4a0)); /* 0280302d daddu a2,s4,zero */
 set(m,6u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002cd4a4));goto dispatch;
L_002cd4a4:
 STEP(UINT32_C(0x002cd4a4)); /* 32a2003f andi v0,s5,0x3f */
 set(m,2u,lo(m,21u) & UINT64_C(0x3f));target=sx(UINT32_C(0x002cd4a8));goto dispatch;
L_002cd4a8:
 STEP(UINT32_C(0x002cd4a8)); /* 10400009 beq v0,zero,002cd4d0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002cd4ac));set(m,5u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002cd4d0):UINT32_C(0x002cd4b0));goto dispatch;}
L_002cd4ac:
 STEP(UINT32_C(0x002cd4ac)); /* 3c050055 lui a1,zero,0x55 */
 set(m,5u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002cd4b0));goto dispatch;
L_002cd4b0:
 STEP(UINT32_C(0x002cd4b0)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002cd4b4));goto dispatch;
L_002cd4b4:
 STEP(UINT32_C(0x002cd4b4)); /* 2484ae48 addiu a0,a0,-20920 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffae48)));target=sx(UINT32_C(0x002cd4b8));goto dispatch;
L_002cd4b8:
 STEP(UINT32_C(0x002cd4b8)); /* 24a5ae38 addiu a1,a1,-20936 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffae38)));target=sx(UINT32_C(0x002cd4bc));goto dispatch;
L_002cd4bc:
 STEP(UINT32_C(0x002cd4bc)); /* 02a0302d daddu a2,s5,zero */
 set(m,6u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002cd4c0));goto dispatch;
L_002cd4c0:
 STEP(UINT32_C(0x002cd4c0)); /* 0c0b7758 jal 002ddd60 */
 set(m,31u,UINT64_C(0x002cd4c8));STEP(UINT32_C(0x002cd4c4));/* nop */target=sx(UINT32_C(0x002ddd60));goto dispatch;
L_002cd4c4:
 STEP(UINT32_C(0x002cd4c4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cd4c8));goto dispatch;
L_002cd4c8:
 STEP(UINT32_C(0x002cd4c8)); /* 10000060 beq zero,zero,002cd64c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd4cc));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002cd64c):UINT32_C(0x002cd4d0));goto dispatch;}
L_002cd4cc:
 STEP(UINT32_C(0x002cd4cc)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002cd4d0));goto dispatch;
L_002cd4d0:
 STEP(UINT32_C(0x002cd4d0)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cd4d4));goto dispatch;
L_002cd4d4:
 STEP(UINT32_C(0x002cd4d4)); /* 0c0b33da jal 002ccf68 */
 set(m,31u,UINT64_C(0x002cd4dc));STEP(UINT32_C(0x002cd4d8));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9700)));target=sx(UINT32_C(0x002ccf68));goto dispatch;
L_002cd4d8:
 STEP(UINT32_C(0x002cd4d8)); /* 24849700 addiu a0,a0,-26880 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9700)));target=sx(UINT32_C(0x002cd4dc));goto dispatch;
L_002cd4dc:
 STEP(UINT32_C(0x002cd4dc)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cd4e0));goto dispatch;
L_002cd4e0:
 STEP(UINT32_C(0x002cd4e0)); /* 16000003 bne s0,zero,002cd4f0 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cd4e4));READ((uint32_t)lo(m,29u)+UINT32_C(0x000000c0),&value32,4u);set(m,3u,sx(value32));target=sx(taken?UINT32_C(0x002cd4f0):UINT32_C(0x002cd4e8));goto dispatch;}
L_002cd4e4:
 STEP(UINT32_C(0x002cd4e4)); /* 8fa300c0 lw v1,0xc0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000000c0),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cd4e8));goto dispatch;
L_002cd4e8:
 STEP(UINT32_C(0x002cd4e8)); /* 10000058 beq zero,zero,002cd64c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd4ec));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002cd64c):UINT32_C(0x002cd4f0));goto dispatch;}
L_002cd4ec:
 STEP(UINT32_C(0x002cd4ec)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002cd4f0));goto dispatch;
L_002cd4f0:
 STEP(UINT32_C(0x002cd4f0)); /* 8e020018 lw v0,0x18(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cd4f4));goto dispatch;
L_002cd4f4:
 STEP(UINT32_C(0x002cd4f4)); /* ae430020 sw v1,0x20(s2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002cd4f8));goto dispatch;
L_002cd4f8:
 STEP(UINT32_C(0x002cd4f8)); /* ae420004 sw v0,0x4(s2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002cd4fc));goto dispatch;
L_002cd4fc:
 STEP(UINT32_C(0x002cd4fc)); /* ae500000 sw s0,0x0(s2) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cd500));goto dispatch;
L_002cd500:
 STEP(UINT32_C(0x002cd500)); /* ae57001c sw s7,0x1c(s2) */
 value32=(uint32_t)lo(m,23u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002cd504));goto dispatch;
L_002cd504:
 STEP(UINT32_C(0x002cd504)); /* ae160020 sw s6,0x20(s0) */
 value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002cd508));goto dispatch;
L_002cd508:
 STEP(UINT32_C(0x002cd508)); /* ae100014 sw s0,0x14(s0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002cd50c));goto dispatch;
L_002cd50c:
 STEP(UINT32_C(0x002cd50c)); /* ae130024 sw s3,0x24(s0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002cd510));goto dispatch;
L_002cd510:
 STEP(UINT32_C(0x002cd510)); /* ae150028 sw s5,0x28(s0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x002cd514));goto dispatch;
L_002cd514:
 STEP(UINT32_C(0x002cd514)); /* ae11002c sw s1,0x2c(s0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x002cd518));goto dispatch;
L_002cd518:
 STEP(UINT32_C(0x002cd518)); /* ae12001c sw s2,0x1c(s0) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002cd51c));goto dispatch;
L_002cd51c:
 STEP(UINT32_C(0x002cd51c)); /* 8e420024 lw v0,0x24(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cd520));goto dispatch;
L_002cd520:
 STEP(UINT32_C(0x002cd520)); /* 16950008 bne s4,s5,002cd544 */
 {int taken=(lo(m,20u)!=lo(m,21u));STEP(UINT32_C(0x002cd524));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000034),&value32,4u);target=sx(taken?UINT32_C(0x002cd544):UINT32_C(0x002cd528));goto dispatch;}
L_002cd524:
 STEP(UINT32_C(0x002cd524)); /* ae020034 sw v0,0x34(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000034),&value32,4u);target=sx(UINT32_C(0x002cd528));goto dispatch;
L_002cd528:
 STEP(UINT32_C(0x002cd528)); /* 0271102a slt v0,s3,s1 */
 set(m,2u,((int64_t)lo(m,19u)<(int64_t)lo(m,17u)));target=sx(UINT32_C(0x002cd52c));goto dispatch;
L_002cd52c:
 STEP(UINT32_C(0x002cd52c)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cd530));goto dispatch;
L_002cd530:
 STEP(UINT32_C(0x002cd530)); /* 0280202d daddu a0,s4,zero */
 set(m,4u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002cd534));goto dispatch;
L_002cd534:
 STEP(UINT32_C(0x002cd534)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002cd53c));STEP(UINT32_C(0x002cd538));if(lo(m,2u)==0u)set(m,5u,lo(m,19u));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002cd538:
 STEP(UINT32_C(0x002cd538)); /* 0262280a movz a1,s3,v0 */
 if(lo(m,2u)==0u)set(m,5u,lo(m,19u));target=sx(UINT32_C(0x002cd53c));goto dispatch;
L_002cd53c:
 STEP(UINT32_C(0x002cd53c)); /* 1000000a beq zero,zero,002cd568 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd540));set(m,2u,lo(m,30u) & UINT64_C(0x1));target=sx(taken?UINT32_C(0x002cd568):UINT32_C(0x002cd544));goto dispatch;}
L_002cd540:
 STEP(UINT32_C(0x002cd540)); /* 33c20001 andi v0,s8,0x1 */
 set(m,2u,lo(m,30u) & UINT64_C(0x1));target=sx(UINT32_C(0x002cd544));goto dispatch;
L_002cd544:
 STEP(UINT32_C(0x002cd544)); /* 1a600003 blez s3,zero,002cd554 */
 {int taken=((int64_t)lo(m,19u)<=0);STEP(UINT32_C(0x002cd548));set(m,4u,lo(m,20u)+lo(m,0u));target=sx(taken?UINT32_C(0x002cd554):UINT32_C(0x002cd54c));goto dispatch;}
L_002cd548:
 STEP(UINT32_C(0x002cd548)); /* 0280202d daddu a0,s4,zero */
 set(m,4u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002cd54c));goto dispatch;
L_002cd54c:
 STEP(UINT32_C(0x002cd54c)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002cd554));STEP(UINT32_C(0x002cd550));set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002cd550:
 STEP(UINT32_C(0x002cd550)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002cd554));goto dispatch;
L_002cd554:
 STEP(UINT32_C(0x002cd554)); /* 1a200003 blez s1,zero,002cd564 */
 {int taken=((int64_t)lo(m,17u)<=0);STEP(UINT32_C(0x002cd558));set(m,4u,lo(m,21u)+lo(m,0u));target=sx(taken?UINT32_C(0x002cd564):UINT32_C(0x002cd55c));goto dispatch;}
L_002cd558:
 STEP(UINT32_C(0x002cd558)); /* 02a0202d daddu a0,s5,zero */
 set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002cd55c));goto dispatch;
L_002cd55c:
 STEP(UINT32_C(0x002cd55c)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002cd564));STEP(UINT32_C(0x002cd560));set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002cd560:
 STEP(UINT32_C(0x002cd560)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cd564));goto dispatch;
L_002cd564:
 STEP(UINT32_C(0x002cd564)); /* 33c20001 andi v0,s8,0x1 */
 set(m,2u,lo(m,30u) & UINT64_C(0x1));target=sx(UINT32_C(0x002cd568));goto dispatch;
L_002cd568:
 STEP(UINT32_C(0x002cd568)); /* 50400016 beql v0,zero,002cd5c4 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002cd56c));set(m,21u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cd5c4));}else target=sx(UINT32_C(0x002cd570));goto dispatch;
L_002cd56c:
 STEP(UINT32_C(0x002cd56c)); /* 24150001 addiu s5,zero,1 */
 set(m,21u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cd570));goto dispatch;
L_002cd570:
 STEP(UINT32_C(0x002cd570)); /* 16e00003 bne s7,zero,002cd580 */
 {int taken=(lo(m,23u)!=lo(m,0u));STEP(UINT32_C(0x002cd574));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002cd580):UINT32_C(0x002cd578));goto dispatch;}
L_002cd574:
 STEP(UINT32_C(0x002cd574)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cd578));goto dispatch;
L_002cd578:
 STEP(UINT32_C(0x002cd578)); /* 10000002 beq zero,zero,002cd584 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd57c));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(taken?UINT32_C(0x002cd584):UINT32_C(0x002cd580));goto dispatch;}
L_002cd57c:
 STEP(UINT32_C(0x002cd57c)); /* ae000030 sw zero,0x30(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002cd580));goto dispatch;
L_002cd580:
 STEP(UINT32_C(0x002cd580)); /* ae020030 sw v0,0x30(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002cd584));goto dispatch;
L_002cd584:
 STEP(UINT32_C(0x002cd584)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002cd588));goto dispatch;
L_002cd588:
 STEP(UINT32_C(0x002cd588)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002cd58c));goto dispatch;
L_002cd58c:
 STEP(UINT32_C(0x002cd58c)); /* 8e480014 lw t0,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002cd590));goto dispatch;
L_002cd590:
 STEP(UINT32_C(0x002cd590)); /* 0280382d daddu a3,s4,zero */
 set(m,7u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002cd594));goto dispatch;
L_002cd594:
 STEP(UINT32_C(0x002cd594)); /* ae420008 sw v0,0x8(s2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002cd598));goto dispatch;
L_002cd598:
 STEP(UINT32_C(0x002cd598)); /* 0260482d daddu t1,s3,zero */
 set(m,9u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002cd59c));goto dispatch;
L_002cd59c:
 STEP(UINT32_C(0x002cd59c)); /* 3484001a ori a0,a0,0x1a */
 set(m,4u,lo(m,4u) | UINT64_C(0x1a));target=sx(UINT32_C(0x002cd5a0));goto dispatch;
L_002cd5a0:
 STEP(UINT32_C(0x002cd5a0)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cd5a4));goto dispatch;
L_002cd5a4:
 STEP(UINT32_C(0x002cd5a4)); /* 0c0b78ac jal 002de2b0 */
 set(m,31u,UINT64_C(0x002cd5ac));STEP(UINT32_C(0x002cd5a8));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002cd5a8:
 STEP(UINT32_C(0x002cd5a8)); /* 24060040 addiu a2,zero,64 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002cd5ac));goto dispatch;
L_002cd5ac:
 STEP(UINT32_C(0x002cd5ac)); /* 14400027 bne v0,zero,002cd64c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cd5b0));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002cd64c):UINT32_C(0x002cd5b4));goto dispatch;}
L_002cd5b0:
 STEP(UINT32_C(0x002cd5b0)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cd5b4));goto dispatch;
L_002cd5b4:
 STEP(UINT32_C(0x002cd5b4)); /* 0c0b3404 jal 002cd010 */
 set(m,31u,UINT64_C(0x002cd5bc));STEP(UINT32_C(0x002cd5b8));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cd010));goto dispatch;
L_002cd5b8:
 STEP(UINT32_C(0x002cd5b8)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cd5bc));goto dispatch;
L_002cd5bc:
 STEP(UINT32_C(0x002cd5bc)); /* 10000023 beq zero,zero,002cd64c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd5c0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(taken?UINT32_C(0x002cd64c):UINT32_C(0x002cd5c4));goto dispatch;}
L_002cd5c0:
 STEP(UINT32_C(0x002cd5c0)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x002cd5c4));goto dispatch;
L_002cd5c4:
 STEP(UINT32_C(0x002cd5c4)); /* afa00008 sw zero,0x8(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002cd5c8));goto dispatch;
L_002cd5c8:
 STEP(UINT32_C(0x002cd5c8)); /* afb50004 sw s5,0x4(sp) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002cd5cc));goto dispatch;
L_002cd5cc:
 STEP(UINT32_C(0x002cd5cc)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002cd5d0));goto dispatch;
L_002cd5d0:
 STEP(UINT32_C(0x002cd5d0)); /* 0c0b6fa8 jal 002dbea0 */
 set(m,31u,UINT64_C(0x002cd5d8));STEP(UINT32_C(0x002cd5d4));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002dbea0));goto dispatch;
L_002cd5d4:
 STEP(UINT32_C(0x002cd5d4)); /* afa00014 sw zero,0x14(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002cd5d8));goto dispatch;
L_002cd5d8:
 STEP(UINT32_C(0x002cd5d8)); /* 0040882d daddu s1,v0,zero */
 set(m,17u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cd5dc));goto dispatch;
L_002cd5dc:
 STEP(UINT32_C(0x002cd5dc)); /* 06210005 regimm1 s1,002cd5f4 */
 {int taken=((int64_t)lo(m,17u)>=0);STEP(UINT32_C(0x002cd5e0));value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002cd5f4):UINT32_C(0x002cd5e4));goto dispatch;}
L_002cd5e0:
 STEP(UINT32_C(0x002cd5e0)); /* ae510008 sw s1,0x8(s2) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002cd5e4));goto dispatch;
L_002cd5e4:
 STEP(UINT32_C(0x002cd5e4)); /* 0c0b3404 jal 002cd010 */
 set(m,31u,UINT64_C(0x002cd5ec));STEP(UINT32_C(0x002cd5e8));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cd010));goto dispatch;
L_002cd5e8:
 STEP(UINT32_C(0x002cd5e8)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cd5ec));goto dispatch;
L_002cd5ec:
 STEP(UINT32_C(0x002cd5ec)); /* 10000017 beq zero,zero,002cd64c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd5f0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffd)));target=sx(taken?UINT32_C(0x002cd64c):UINT32_C(0x002cd5f4));goto dispatch;}
L_002cd5f0:
 STEP(UINT32_C(0x002cd5f0)); /* 2402fffd addiu v0,zero,-3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffd)));target=sx(UINT32_C(0x002cd5f4));goto dispatch;
L_002cd5f4:
 STEP(UINT32_C(0x002cd5f4)); /* ae150030 sw s5,0x30(s0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002cd5f8));goto dispatch;
L_002cd5f8:
 STEP(UINT32_C(0x002cd5f8)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002cd5fc));goto dispatch;
L_002cd5fc:
 STEP(UINT32_C(0x002cd5fc)); /* 0280382d daddu a3,s4,zero */
 set(m,7u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002cd600));goto dispatch;
L_002cd600:
 STEP(UINT32_C(0x002cd600)); /* 0260482d daddu t1,s3,zero */
 set(m,9u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002cd604));goto dispatch;
L_002cd604:
 STEP(UINT32_C(0x002cd604)); /* 8e480014 lw t0,0x14(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000014),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002cd608));goto dispatch;
L_002cd608:
 STEP(UINT32_C(0x002cd608)); /* 3484001a ori a0,a0,0x1a */
 set(m,4u,lo(m,4u) | UINT64_C(0x1a));target=sx(UINT32_C(0x002cd60c));goto dispatch;
L_002cd60c:
 STEP(UINT32_C(0x002cd60c)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cd610));goto dispatch;
L_002cd610:
 STEP(UINT32_C(0x002cd610)); /* 0c0b78ac jal 002de2b0 */
 set(m,31u,UINT64_C(0x002cd618));STEP(UINT32_C(0x002cd614));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002cd614:
 STEP(UINT32_C(0x002cd614)); /* 24060040 addiu a2,zero,64 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002cd618));goto dispatch;
L_002cd618:
 STEP(UINT32_C(0x002cd618)); /* 14400007 bne v0,zero,002cd638 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cd61c));/* nop */target=sx(taken?UINT32_C(0x002cd638):UINT32_C(0x002cd620));goto dispatch;}
L_002cd61c:
 STEP(UINT32_C(0x002cd61c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cd620));goto dispatch;
L_002cd620:
 STEP(UINT32_C(0x002cd620)); /* 0c0b3404 jal 002cd010 */
 set(m,31u,UINT64_C(0x002cd628));STEP(UINT32_C(0x002cd624));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cd010));goto dispatch;
L_002cd624:
 STEP(UINT32_C(0x002cd624)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cd628));goto dispatch;
L_002cd628:
 STEP(UINT32_C(0x002cd628)); /* 0c0b6fac jal 002dbeb0 */
 set(m,31u,UINT64_C(0x002cd630));STEP(UINT32_C(0x002cd62c));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dbeb0));goto dispatch;
L_002cd62c:
 STEP(UINT32_C(0x002cd62c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cd630));goto dispatch;
L_002cd630:
 STEP(UINT32_C(0x002cd630)); /* 10000006 beq zero,zero,002cd64c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd634));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(taken?UINT32_C(0x002cd64c):UINT32_C(0x002cd638));goto dispatch;}
L_002cd634:
 STEP(UINT32_C(0x002cd634)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x002cd638));goto dispatch;
L_002cd638:
 STEP(UINT32_C(0x002cd638)); /* 0c0b6fb8 jal 002dbee0 */
 set(m,31u,UINT64_C(0x002cd640));STEP(UINT32_C(0x002cd63c));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dbee0));goto dispatch;
L_002cd63c:
 STEP(UINT32_C(0x002cd63c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cd640));goto dispatch;
L_002cd640:
 STEP(UINT32_C(0x002cd640)); /* 0c0b6fac jal 002dbeb0 */
 set(m,31u,UINT64_C(0x002cd648));STEP(UINT32_C(0x002cd644));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dbeb0));goto dispatch;
L_002cd644:
 STEP(UINT32_C(0x002cd644)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cd648));goto dispatch;
L_002cd648:
 STEP(UINT32_C(0x002cd648)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cd64c));goto dispatch;
L_002cd64c:
 STEP(UINT32_C(0x002cd64c)); /* dfbf00b0 ld ra,0xb0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000000b0),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cd650));goto dispatch;
L_002cd650:
 STEP(UINT32_C(0x002cd650)); /* dfbe00a0 ld s8,0xa0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),&value64,8u);set(m,30u,value64);target=sx(UINT32_C(0x002cd654));goto dispatch;
L_002cd654:
 STEP(UINT32_C(0x002cd654)); /* dfb70090 ld s7,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002cd658));goto dispatch;
L_002cd658:
 STEP(UINT32_C(0x002cd658)); /* dfb60080 ld s6,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002cd65c));goto dispatch;
L_002cd65c:
 STEP(UINT32_C(0x002cd65c)); /* dfb50070 ld s5,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002cd660));goto dispatch;
L_002cd660:
 STEP(UINT32_C(0x002cd660)); /* dfb40060 ld s4,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002cd664));goto dispatch;
L_002cd664:
 STEP(UINT32_C(0x002cd664)); /* dfb30050 ld s3,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002cd668));goto dispatch;
L_002cd668:
 STEP(UINT32_C(0x002cd668)); /* dfb20040 ld s2,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cd66c));goto dispatch;
L_002cd66c:
 STEP(UINT32_C(0x002cd66c)); /* dfb10030 ld s1,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cd670));goto dispatch;
L_002cd670:
 STEP(UINT32_C(0x002cd670)); /* dfb00020 ld s0,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cd674));goto dispatch;
L_002cd674:
 STEP(UINT32_C(0x002cd674)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cd678));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000c0)));goto dispatch;
L_002cd678:
 STEP(UINT32_C(0x002cd678)); /* 27bd00c0 addiu sp,sp,192 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000c0)));target=sx(UINT32_C(0x002cd67c));goto dispatch;
L_002ccf68:
 STEP(UINT32_C(0x002ccf68)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002ccf6c));goto dispatch;
L_002ccf6c:
 STEP(UINT32_C(0x002ccf6c)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ccf70));goto dispatch;
L_002ccf70:
 STEP(UINT32_C(0x002ccf70)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002ccf74));goto dispatch;
L_002ccf74:
 STEP(UINT32_C(0x002ccf74)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ccf78));goto dispatch;
L_002ccf78:
 STEP(UINT32_C(0x002ccf78)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002ccf80));STEP(UINT32_C(0x002ccf7c));set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002ccf7c:
 STEP(UINT32_C(0x002ccf7c)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ccf80));goto dispatch;
L_002ccf80:
 STEP(UINT32_C(0x002ccf80)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ccf84));goto dispatch;
L_002ccf84:
 STEP(UINT32_C(0x002ccf84)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ccf88));goto dispatch;
L_002ccf88:
 STEP(UINT32_C(0x002ccf88)); /* 18800019 blez a0,zero,002ccff0 */
 {int taken=((int64_t)lo(m,4u)<=0);STEP(UINT32_C(0x002ccf8c));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002ccff0):UINT32_C(0x002ccf90));goto dispatch;}
L_002ccf8c:
 STEP(UINT32_C(0x002ccf8c)); /* 8e300004 lw s0,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002ccf90));goto dispatch;
L_002ccf90:
 STEP(UINT32_C(0x002ccf90)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ccf94));goto dispatch;
L_002ccf94:
 STEP(UINT32_C(0x002ccf94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ccf98));goto dispatch;
L_002ccf98:
 STEP(UINT32_C(0x002ccf98)); /* 8e020010 lw v0,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ccf9c));goto dispatch;
L_002ccf9c:
 STEP(UINT32_C(0x002ccf9c)); /* 30420001 andi v0,v0,0x1 */
 set(m,2u,lo(m,2u) & UINT64_C(0x1));target=sx(UINT32_C(0x002ccfa0));goto dispatch;
L_002ccfa0:
 STEP(UINT32_C(0x002ccfa0)); /* 54400010 bnel v0,zero,002ccfe4 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002ccfa4));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ccfe4));}else target=sx(UINT32_C(0x002ccfa8));goto dispatch;
L_002ccfa4:
 STEP(UINT32_C(0x002ccfa4)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ccfa8));goto dispatch;
L_002ccfa8:
 STEP(UINT32_C(0x002ccfa8)); /* 00031400 sll v0,v1,16 */
 set(m,2u,sx((uint32_t)lo(m,3u)<<16u));target=sx(UINT32_C(0x002ccfac));goto dispatch;
L_002ccfac:
 STEP(UINT32_C(0x002ccfac)); /* 34420005 ori v0,v0,0x5 */
 set(m,2u,lo(m,2u) | UINT64_C(0x5));target=sx(UINT32_C(0x002ccfb0));goto dispatch;
L_002ccfb0:
 STEP(UINT32_C(0x002ccfb0)); /* ae020010 sw v0,0x10(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002ccfb4));goto dispatch;
L_002ccfb4:
 STEP(UINT32_C(0x002ccfb4)); /* 8e220000 lw v0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ccfb8));goto dispatch;
L_002ccfb8:
 STEP(UINT32_C(0x002ccfb8)); /* 24430001 addiu v1,v0,1 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ccfbc));goto dispatch;
L_002ccfbc:
 STEP(UINT32_C(0x002ccfbc)); /* 14650004 bne v1,a1,002ccfd0 */
 {int taken=(lo(m,3u)!=lo(m,5u));STEP(UINT32_C(0x002ccfc0));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002ccfd0):UINT32_C(0x002ccfc4));goto dispatch;}
L_002ccfc0:
 STEP(UINT32_C(0x002ccfc0)); /* ae230000 sw v1,0x0(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ccfc4));goto dispatch;
L_002ccfc4:
 STEP(UINT32_C(0x002ccfc4)); /* 24420002 addiu v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002ccfc8));goto dispatch;
L_002ccfc8:
 STEP(UINT32_C(0x002ccfc8)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ccfcc));goto dispatch;
L_002ccfcc:
 STEP(UINT32_C(0x002ccfcc)); /* ae220000 sw v0,0x0(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ccfd0));goto dispatch;
L_002ccfd0:
 STEP(UINT32_C(0x002ccfd0)); /* ae100014 sw s0,0x14(s0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002ccfd4));goto dispatch;
L_002ccfd4:
 STEP(UINT32_C(0x002ccfd4)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002ccfdc));STEP(UINT32_C(0x002ccfd8));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002ccfd8:
 STEP(UINT32_C(0x002ccfd8)); /* ae030018 sw v1,0x18(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002ccfdc));goto dispatch;
L_002ccfdc:
 STEP(UINT32_C(0x002ccfdc)); /* 10000007 beq zero,zero,002ccffc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ccfe0));set(m,2u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002ccffc):UINT32_C(0x002ccfe4));goto dispatch;}
L_002ccfe0:
 STEP(UINT32_C(0x002ccfe0)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ccfe4));goto dispatch;
L_002ccfe4:
 STEP(UINT32_C(0x002ccfe4)); /* 0064102a slt v0,v1,a0 */
 set(m,2u,((int64_t)lo(m,3u)<(int64_t)lo(m,4u)));target=sx(UINT32_C(0x002ccfe8));goto dispatch;
L_002ccfe8:
 STEP(UINT32_C(0x002ccfe8)); /* 1440ffeb bne v0,zero,002ccf98 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002ccfec));set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000040)));target=sx(taken?UINT32_C(0x002ccf98):UINT32_C(0x002ccff0));goto dispatch;}
L_002ccfec:
 STEP(UINT32_C(0x002ccfec)); /* 26100040 addiu s0,s0,64 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002ccff0));goto dispatch;
L_002ccff0:
 STEP(UINT32_C(0x002ccff0)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002ccff8));STEP(UINT32_C(0x002ccff4));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002ccff4:
 STEP(UINT32_C(0x002ccff4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ccff8));goto dispatch;
L_002ccff8:
 STEP(UINT32_C(0x002ccff8)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ccffc));goto dispatch;
L_002ccffc:
 STEP(UINT32_C(0x002ccffc)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cd000));goto dispatch;
L_002cd000:
 STEP(UINT32_C(0x002cd000)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cd004));goto dispatch;
L_002cd004:
 STEP(UINT32_C(0x002cd004)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cd008));goto dispatch;
L_002cd008:
 STEP(UINT32_C(0x002cd008)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cd00c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002cd00c:
 STEP(UINT32_C(0x002cd00c)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002cd010));goto dispatch;
L_002cd010:
 STEP(UINT32_C(0x002cd010)); /* 8c830010 lw v1,0x10(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cd014));goto dispatch;
L_002cd014:
 STEP(UINT32_C(0x002cd014)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002cd018));goto dispatch;
L_002cd018:
 STEP(UINT32_C(0x002cd018)); /* 3442fffe ori v0,v0,0xfffe */
 set(m,2u,lo(m,2u) | UINT64_C(0xfffe));target=sx(UINT32_C(0x002cd01c));goto dispatch;
L_002cd01c:
 STEP(UINT32_C(0x002cd01c)); /* ac800018 sw zero,0x18(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002cd020));goto dispatch;
L_002cd020:
 STEP(UINT32_C(0x002cd020)); /* 00621824 and v1,v1,v0 */
 set(m,3u,lo(m,3u)&lo(m,2u));target=sx(UINT32_C(0x002cd024));goto dispatch;
L_002cd024:
 STEP(UINT32_C(0x002cd024)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cd028));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);goto dispatch;
L_002cd028:
 STEP(UINT32_C(0x002cd028)); /* ac830010 sw v1,0x10(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002cd02c));goto dispatch;
L_002cd030:
 STEP(UINT32_C(0x002cd030)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002cd034));goto dispatch;
L_002cd034:
 STEP(UINT32_C(0x002cd034)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002cd038));goto dispatch;
L_002cd038:
 STEP(UINT32_C(0x002cd038)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cd03c));goto dispatch;
L_002cd03c:
 STEP(UINT32_C(0x002cd03c)); /* 3442001a ori v0,v0,0x1a */
 set(m,2u,lo(m,2u) | UINT64_C(0x1a));target=sx(UINT32_C(0x002cd040));goto dispatch;
L_002cd040:
 STEP(UINT32_C(0x002cd040)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cd044));goto dispatch;
L_002cd044:
 STEP(UINT32_C(0x002cd044)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cd048));goto dispatch;
L_002cd048:
 STEP(UINT32_C(0x002cd048)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002cd04c));goto dispatch;
L_002cd04c:
 STEP(UINT32_C(0x002cd04c)); /* 8e230020 lw v1,0x20(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000020),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cd050));goto dispatch;
L_002cd050:
 STEP(UINT32_C(0x002cd050)); /* 10620013 beq v1,v0,002cd0a0 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002cd054));set(m,2u,lo(m,2u)<lo(m,3u));target=sx(taken?UINT32_C(0x002cd0a0):UINT32_C(0x002cd058));goto dispatch;}
L_002cd054:
 STEP(UINT32_C(0x002cd054)); /* 0043102b sltu v0,v0,v1 */
 set(m,2u,lo(m,2u)<lo(m,3u));target=sx(UINT32_C(0x002cd058));goto dispatch;
L_002cd058:
 STEP(UINT32_C(0x002cd058)); /* 14400007 bne v0,zero,002cd078 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cd05c));/* nop */target=sx(taken?UINT32_C(0x002cd078):UINT32_C(0x002cd060));goto dispatch;}
L_002cd05c:
 STEP(UINT32_C(0x002cd05c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cd060));goto dispatch;
L_002cd060:
 STEP(UINT32_C(0x002cd060)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002cd064));goto dispatch;
L_002cd064:
 STEP(UINT32_C(0x002cd064)); /* 34420019 ori v0,v0,0x19 */
 set(m,2u,lo(m,2u) | UINT64_C(0x19));target=sx(UINT32_C(0x002cd068));goto dispatch;
L_002cd068:
 STEP(UINT32_C(0x002cd068)); /* 10620017 beq v1,v0,002cd0c8 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002cd06c));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002cd0c8):UINT32_C(0x002cd070));goto dispatch;}
L_002cd06c:
 STEP(UINT32_C(0x002cd06c)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002cd070));goto dispatch;
L_002cd070:
 STEP(UINT32_C(0x002cd070)); /* 10000025 beq zero,zero,002cd108 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd074));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x002cd108):UINT32_C(0x002cd078));goto dispatch;}
L_002cd074:
 STEP(UINT32_C(0x002cd074)); /* 8e040008 lw a0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd078));goto dispatch;
L_002cd078:
 STEP(UINT32_C(0x002cd078)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002cd07c));goto dispatch;
L_002cd07c:
 STEP(UINT32_C(0x002cd07c)); /* 3442001c ori v0,v0,0x1c */
 set(m,2u,lo(m,2u) | UINT64_C(0x1c));target=sx(UINT32_C(0x002cd080));goto dispatch;
L_002cd080:
 STEP(UINT32_C(0x002cd080)); /* 10620020 beq v1,v0,002cd104 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002cd084));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002cd104):UINT32_C(0x002cd088));goto dispatch;}
L_002cd084:
 STEP(UINT32_C(0x002cd084)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002cd088));goto dispatch;
L_002cd088:
 STEP(UINT32_C(0x002cd088)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002cd08c));goto dispatch;
L_002cd08c:
 STEP(UINT32_C(0x002cd08c)); /* 3442001d ori v0,v0,0x1d */
 set(m,2u,lo(m,2u) | UINT64_C(0x1d));target=sx(UINT32_C(0x002cd090));goto dispatch;
L_002cd090:
 STEP(UINT32_C(0x002cd090)); /* 10620017 beq v1,v0,002cd0f0 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002cd094));/* nop */target=sx(taken?UINT32_C(0x002cd0f0):UINT32_C(0x002cd098));goto dispatch;}
L_002cd094:
 STEP(UINT32_C(0x002cd094)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cd098));goto dispatch;
L_002cd098:
 STEP(UINT32_C(0x002cd098)); /* 1000001b beq zero,zero,002cd108 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd09c));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x002cd108):UINT32_C(0x002cd0a0));goto dispatch;}
L_002cd09c:
 STEP(UINT32_C(0x002cd09c)); /* 8e040008 lw a0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd0a0));goto dispatch;
L_002cd0a0:
 STEP(UINT32_C(0x002cd0a0)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002cd0a4));goto dispatch;
L_002cd0a4:
 STEP(UINT32_C(0x002cd0a4)); /* 8e02001c lw v0,0x1c(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cd0a8));goto dispatch;
L_002cd0a8:
 STEP(UINT32_C(0x002cd0a8)); /* 10400003 beq v0,zero,002cd0b8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002cd0ac));/* nop */target=sx(taken?UINT32_C(0x002cd0b8):UINT32_C(0x002cd0b0));goto dispatch;}
L_002cd0ac:
 STEP(UINT32_C(0x002cd0ac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cd0b0));goto dispatch;
L_002cd0b0:
 STEP(UINT32_C(0x002cd0b0)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002cd0b8));STEP(UINT32_C(0x002cd0b4));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);set(m,4u,sx(value32));goto dispatch;
L_002cd0b4:
 STEP(UINT32_C(0x002cd0b4)); /* 8e040020 lw a0,0x20(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd0b8));goto dispatch;
L_002cd0b8:
 STEP(UINT32_C(0x002cd0b8)); /* 0c0b6fb4 jal 002dbed0 */
 set(m,31u,UINT64_C(0x002cd0c0));STEP(UINT32_C(0x002cd0bc));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000028),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbed0));goto dispatch;
L_002cd0bc:
 STEP(UINT32_C(0x002cd0bc)); /* 8e040028 lw a0,0x28(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000028),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd0c0));goto dispatch;
L_002cd0c0:
 STEP(UINT32_C(0x002cd0c0)); /* 10000010 beq zero,zero,002cd104 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd0c4));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002cd104):UINT32_C(0x002cd0c8));goto dispatch;}
L_002cd0c4:
 STEP(UINT32_C(0x002cd0c4)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002cd0c8));goto dispatch;
L_002cd0c8:
 STEP(UINT32_C(0x002cd0c8)); /* 8e220024 lw v0,0x24(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cd0cc));goto dispatch;
L_002cd0cc:
 STEP(UINT32_C(0x002cd0cc)); /* 8e040028 lw a0,0x28(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000028),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd0d0));goto dispatch;
L_002cd0d0:
 STEP(UINT32_C(0x002cd0d0)); /* ae020024 sw v0,0x24(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002cd0d4));goto dispatch;
L_002cd0d4:
 STEP(UINT32_C(0x002cd0d4)); /* 8e230028 lw v1,0x28(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000028),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cd0d8));goto dispatch;
L_002cd0d8:
 STEP(UINT32_C(0x002cd0d8)); /* ae030014 sw v1,0x14(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002cd0dc));goto dispatch;
L_002cd0dc:
 STEP(UINT32_C(0x002cd0dc)); /* 8e22002c lw v0,0x2c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000002c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cd0e0));goto dispatch;
L_002cd0e0:
 STEP(UINT32_C(0x002cd0e0)); /* 0c0b6fb4 jal 002dbed0 */
 set(m,31u,UINT64_C(0x002cd0e8));STEP(UINT32_C(0x002cd0e4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002dbed0));goto dispatch;
L_002cd0e4:
 STEP(UINT32_C(0x002cd0e4)); /* ae020018 sw v0,0x18(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002cd0e8));goto dispatch;
L_002cd0e8:
 STEP(UINT32_C(0x002cd0e8)); /* 10000006 beq zero,zero,002cd104 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cd0ec));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002cd104):UINT32_C(0x002cd0f0));goto dispatch;}
L_002cd0ec:
 STEP(UINT32_C(0x002cd0ec)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002cd0f0));goto dispatch;
L_002cd0f0:
 STEP(UINT32_C(0x002cd0f0)); /* 8e220024 lw v0,0x24(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cd0f4));goto dispatch;
L_002cd0f4:
 STEP(UINT32_C(0x002cd0f4)); /* 8e040028 lw a0,0x28(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000028),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd0f8));goto dispatch;
L_002cd0f8:
 STEP(UINT32_C(0x002cd0f8)); /* 0c0b6fb4 jal 002dbed0 */
 set(m,31u,UINT64_C(0x002cd100));STEP(UINT32_C(0x002cd0fc));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x002dbed0));goto dispatch;
L_002cd0fc:
 STEP(UINT32_C(0x002cd0fc)); /* ae02002c sw v0,0x2c(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x002cd100));goto dispatch;
L_002cd100:
 STEP(UINT32_C(0x002cd100)); /* 8e30001c lw s0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002cd104));goto dispatch;
L_002cd104:
 STEP(UINT32_C(0x002cd104)); /* 8e040008 lw a0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd108));goto dispatch;
L_002cd108:
 STEP(UINT32_C(0x002cd108)); /* 04800003 regimm0 a0,002cd118 */
 {int taken=((int64_t)lo(m,4u)<0);STEP(UINT32_C(0x002cd10c));/* nop */target=sx(taken?UINT32_C(0x002cd118):UINT32_C(0x002cd110));goto dispatch;}
L_002cd10c:
 STEP(UINT32_C(0x002cd10c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cd110));goto dispatch;
L_002cd110:
 STEP(UINT32_C(0x002cd110)); /* 0c0b6fb4 jal 002dbed0 */
 set(m,31u,UINT64_C(0x002cd118));STEP(UINT32_C(0x002cd114));/* nop */target=sx(UINT32_C(0x002dbed0));goto dispatch;
L_002cd114:
 STEP(UINT32_C(0x002cd114)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cd118));goto dispatch;
L_002cd118:
 STEP(UINT32_C(0x002cd118)); /* 0c0b3404 jal 002cd010 */
 set(m,31u,UINT64_C(0x002cd120));STEP(UINT32_C(0x002cd11c));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd010));goto dispatch;
L_002cd11c:
 STEP(UINT32_C(0x002cd11c)); /* 8e040000 lw a0,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cd120));goto dispatch;
L_002cd120:
 STEP(UINT32_C(0x002cd120)); /* ae000000 sw zero,0x0(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cd124));goto dispatch;
L_002cd124:
 STEP(UINT32_C(0x002cd124)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cd128));goto dispatch;
L_002cd128:
 STEP(UINT32_C(0x002cd128)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cd12c));goto dispatch;
L_002cd12c:
 STEP(UINT32_C(0x002cd12c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cd130));goto dispatch;
L_002cd130:
 STEP(UINT32_C(0x002cd130)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cd134));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002cd134:
 STEP(UINT32_C(0x002cd134)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002cd138));goto dispatch;
L_002b58b8:
 STEP(UINT32_C(0x002b58b8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002b58bc));/* nop */goto dispatch;
L_002b58bc:
 STEP(UINT32_C(0x002b58bc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002b58c0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

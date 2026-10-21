#include "printf_runtime_native.h"
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
uint32_t nocturnePrintfRuntimeResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002d6678):goto L_002d6678;
 case UINT32_C(0x002d667c):goto L_002d667c;
 case UINT32_C(0x002d6680):goto L_002d6680;
 case UINT32_C(0x002d6684):goto L_002d6684;
 case UINT32_C(0x002d6688):goto L_002d6688;
 case UINT32_C(0x002d668c):goto L_002d668c;
 case UINT32_C(0x002d6690):goto L_002d6690;
 case UINT32_C(0x002d6694):goto L_002d6694;
 case UINT32_C(0x002d6698):goto L_002d6698;
 case UINT32_C(0x002d669c):goto L_002d669c;
 case UINT32_C(0x002d66a0):goto L_002d66a0;
 case UINT32_C(0x002d66a4):goto L_002d66a4;
 case UINT32_C(0x002d66a8):goto L_002d66a8;
 case UINT32_C(0x002d66ac):goto L_002d66ac;
 case UINT32_C(0x002d66b0):goto L_002d66b0;
 case UINT32_C(0x002d66b4):goto L_002d66b4;
 case UINT32_C(0x002d66b8):goto L_002d66b8;
 case UINT32_C(0x002d66bc):goto L_002d66bc;
 case UINT32_C(0x002d66c0):goto L_002d66c0;
 case UINT32_C(0x002d66c4):goto L_002d66c4;
 case UINT32_C(0x002d66c8):goto L_002d66c8;
 case UINT32_C(0x002d66cc):goto L_002d66cc;
 case UINT32_C(0x002d66d0):goto L_002d66d0;
 case UINT32_C(0x002d66d4):goto L_002d66d4;
 case UINT32_C(0x002d66d8):goto L_002d66d8;
 case UINT32_C(0x002d66dc):goto L_002d66dc;
 case UINT32_C(0x002d66e0):goto L_002d66e0;
 case UINT32_C(0x002d66e4):goto L_002d66e4;
 case UINT32_C(0x002d66e8):goto L_002d66e8;
 case UINT32_C(0x002d66ec):goto L_002d66ec;
 case UINT32_C(0x002d66f0):goto L_002d66f0;
 case UINT32_C(0x002d66f4):goto L_002d66f4;
 case UINT32_C(0x002d66f8):goto L_002d66f8;
 case UINT32_C(0x002d66fc):goto L_002d66fc;
 case UINT32_C(0x002d6700):goto L_002d6700;
 case UINT32_C(0x002d6704):goto L_002d6704;
 case UINT32_C(0x002d6708):goto L_002d6708;
 case UINT32_C(0x002d670c):goto L_002d670c;
 case UINT32_C(0x002d6710):goto L_002d6710;
 case UINT32_C(0x002d6714):goto L_002d6714;
 case UINT32_C(0x002d6718):goto L_002d6718;
 case UINT32_C(0x002d671c):goto L_002d671c;
 case UINT32_C(0x002d6720):goto L_002d6720;
 case UINT32_C(0x002d6724):goto L_002d6724;
 case UINT32_C(0x002d6728):goto L_002d6728;
 case UINT32_C(0x002d672c):goto L_002d672c;
 case UINT32_C(0x002d6730):goto L_002d6730;
 case UINT32_C(0x002d6734):goto L_002d6734;
 case UINT32_C(0x002d6738):goto L_002d6738;
 case UINT32_C(0x002d673c):goto L_002d673c;
 case UINT32_C(0x002d6740):goto L_002d6740;
 case UINT32_C(0x002d6744):goto L_002d6744;
 case UINT32_C(0x002d6748):goto L_002d6748;
 case UINT32_C(0x002d674c):goto L_002d674c;
 case UINT32_C(0x002d6750):goto L_002d6750;
 case UINT32_C(0x002d6754):goto L_002d6754;
 case UINT32_C(0x002d6758):goto L_002d6758;
 case UINT32_C(0x002d675c):goto L_002d675c;
 case UINT32_C(0x002d6760):goto L_002d6760;
 case UINT32_C(0x002d6764):goto L_002d6764;
 case UINT32_C(0x002d6768):goto L_002d6768;
 case UINT32_C(0x002d676c):goto L_002d676c;
 case UINT32_C(0x002d6770):goto L_002d6770;
 case UINT32_C(0x002d6774):goto L_002d6774;
 case UINT32_C(0x002d6778):goto L_002d6778;
 case UINT32_C(0x002d677c):goto L_002d677c;
 case UINT32_C(0x002d6780):goto L_002d6780;
 case UINT32_C(0x002d6784):goto L_002d6784;
 case UINT32_C(0x002d6788):goto L_002d6788;
 case UINT32_C(0x002d678c):goto L_002d678c;
 case UINT32_C(0x002d6790):goto L_002d6790;
 case UINT32_C(0x002d6794):goto L_002d6794;
 case UINT32_C(0x002d6798):goto L_002d6798;
 case UINT32_C(0x002d679c):goto L_002d679c;
 case UINT32_C(0x002d67a0):goto L_002d67a0;
 case UINT32_C(0x002d67a4):goto L_002d67a4;
 case UINT32_C(0x002d67a8):goto L_002d67a8;
 case UINT32_C(0x002d67ac):goto L_002d67ac;
 case UINT32_C(0x002d67b0):goto L_002d67b0;
 case UINT32_C(0x002d67b4):goto L_002d67b4;
 case UINT32_C(0x002d67b8):goto L_002d67b8;
 case UINT32_C(0x002d67bc):goto L_002d67bc;
 case UINT32_C(0x002d67c0):goto L_002d67c0;
 case UINT32_C(0x002d67c4):goto L_002d67c4;
 case UINT32_C(0x002d67c8):goto L_002d67c8;
 case UINT32_C(0x002d67cc):goto L_002d67cc;
 case UINT32_C(0x002d67d0):goto L_002d67d0;
 case UINT32_C(0x002d67d4):goto L_002d67d4;
 case UINT32_C(0x002d67d8):goto L_002d67d8;
 case UINT32_C(0x002d67dc):goto L_002d67dc;
 case UINT32_C(0x002d67e0):goto L_002d67e0;
 case UINT32_C(0x002d67e4):goto L_002d67e4;
 case UINT32_C(0x002d67e8):goto L_002d67e8;
 case UINT32_C(0x002d67ec):goto L_002d67ec;
 case UINT32_C(0x002d67f0):goto L_002d67f0;
 case UINT32_C(0x002d67f4):goto L_002d67f4;
 case UINT32_C(0x002d67f8):goto L_002d67f8;
 case UINT32_C(0x002d67fc):goto L_002d67fc;
 case UINT32_C(0x002d6800):goto L_002d6800;
 case UINT32_C(0x002d6804):goto L_002d6804;
 case UINT32_C(0x002d6808):goto L_002d6808;
 case UINT32_C(0x002d680c):goto L_002d680c;
 case UINT32_C(0x002d6810):goto L_002d6810;
 case UINT32_C(0x002d6814):goto L_002d6814;
 case UINT32_C(0x002d6818):goto L_002d6818;
 case UINT32_C(0x002d681c):goto L_002d681c;
 case UINT32_C(0x002d6820):goto L_002d6820;
 case UINT32_C(0x002d6824):goto L_002d6824;
 case UINT32_C(0x002d6828):goto L_002d6828;
 case UINT32_C(0x002d682c):goto L_002d682c;
 case UINT32_C(0x002d6830):goto L_002d6830;
 case UINT32_C(0x002d6834):goto L_002d6834;
 case UINT32_C(0x002d6838):goto L_002d6838;
 case UINT32_C(0x002d683c):goto L_002d683c;
 case UINT32_C(0x002d6840):goto L_002d6840;
 case UINT32_C(0x002d6844):goto L_002d6844;
 case UINT32_C(0x002d6848):goto L_002d6848;
 case UINT32_C(0x002d684c):goto L_002d684c;
 case UINT32_C(0x002d6850):goto L_002d6850;
 case UINT32_C(0x002d6854):goto L_002d6854;
 case UINT32_C(0x002d6858):goto L_002d6858;
 case UINT32_C(0x002d685c):goto L_002d685c;
 case UINT32_C(0x002d6860):goto L_002d6860;
 case UINT32_C(0x002d6864):goto L_002d6864;
 case UINT32_C(0x002d6868):goto L_002d6868;
 case UINT32_C(0x002d686c):goto L_002d686c;
 case UINT32_C(0x002d6870):goto L_002d6870;
 case UINT32_C(0x002d6874):goto L_002d6874;
 case UINT32_C(0x002d6878):goto L_002d6878;
 case UINT32_C(0x002d687c):goto L_002d687c;
 case UINT32_C(0x002d6880):goto L_002d6880;
 case UINT32_C(0x002d6884):goto L_002d6884;
 case UINT32_C(0x002d6888):goto L_002d6888;
 case UINT32_C(0x002d688c):goto L_002d688c;
 case UINT32_C(0x002d6890):goto L_002d6890;
 case UINT32_C(0x002d6894):goto L_002d6894;
 case UINT32_C(0x002d6898):goto L_002d6898;
 case UINT32_C(0x002d689c):goto L_002d689c;
 case UINT32_C(0x002d68a0):goto L_002d68a0;
 case UINT32_C(0x002d68a4):goto L_002d68a4;
 case UINT32_C(0x002d68a8):goto L_002d68a8;
 case UINT32_C(0x002d68ac):goto L_002d68ac;
 case UINT32_C(0x002d68b0):goto L_002d68b0;
 case UINT32_C(0x002d68b4):goto L_002d68b4;
 case UINT32_C(0x002d68b8):goto L_002d68b8;
 case UINT32_C(0x002d68bc):goto L_002d68bc;
 case UINT32_C(0x002d68c0):goto L_002d68c0;
 case UINT32_C(0x002d68c4):goto L_002d68c4;
 case UINT32_C(0x002d68c8):goto L_002d68c8;
 case UINT32_C(0x002d68cc):goto L_002d68cc;
 case UINT32_C(0x002d68d0):goto L_002d68d0;
 case UINT32_C(0x002d68d4):goto L_002d68d4;
 case UINT32_C(0x002d68d8):goto L_002d68d8;
 case UINT32_C(0x002d68dc):goto L_002d68dc;
 case UINT32_C(0x002d68e0):goto L_002d68e0;
 case UINT32_C(0x002d68e4):goto L_002d68e4;
 case UINT32_C(0x002d68e8):goto L_002d68e8;
 case UINT32_C(0x002d68ec):goto L_002d68ec;
 case UINT32_C(0x002d68f0):goto L_002d68f0;
 case UINT32_C(0x002d68f4):goto L_002d68f4;
 case UINT32_C(0x002d68f8):goto L_002d68f8;
 case UINT32_C(0x002d68fc):goto L_002d68fc;
 case UINT32_C(0x002d6900):goto L_002d6900;
 case UINT32_C(0x002d6904):goto L_002d6904;
 case UINT32_C(0x002d6908):goto L_002d6908;
 case UINT32_C(0x002d690c):goto L_002d690c;
 case UINT32_C(0x002d6910):goto L_002d6910;
 case UINT32_C(0x002d6914):goto L_002d6914;
 case UINT32_C(0x002d6918):goto L_002d6918;
 case UINT32_C(0x002d691c):goto L_002d691c;
 case UINT32_C(0x002d6920):goto L_002d6920;
 case UINT32_C(0x002d6924):goto L_002d6924;
 case UINT32_C(0x002d6928):goto L_002d6928;
 case UINT32_C(0x002d692c):goto L_002d692c;
 case UINT32_C(0x002d6930):goto L_002d6930;
 case UINT32_C(0x002d6934):goto L_002d6934;
 case UINT32_C(0x002d6938):goto L_002d6938;
 case UINT32_C(0x002d693c):goto L_002d693c;
 case UINT32_C(0x002d6940):goto L_002d6940;
 case UINT32_C(0x002d6944):goto L_002d6944;
 case UINT32_C(0x002d6948):goto L_002d6948;
 case UINT32_C(0x002d694c):goto L_002d694c;
 case UINT32_C(0x002d6950):goto L_002d6950;
 case UINT32_C(0x002d6954):goto L_002d6954;
 case UINT32_C(0x002d6958):goto L_002d6958;
 case UINT32_C(0x002d695c):goto L_002d695c;
 case UINT32_C(0x002d6960):goto L_002d6960;
 case UINT32_C(0x002d6964):goto L_002d6964;
 case UINT32_C(0x002d6968):goto L_002d6968;
 case UINT32_C(0x002d696c):goto L_002d696c;
 case UINT32_C(0x002d6970):goto L_002d6970;
 case UINT32_C(0x002d6974):goto L_002d6974;
 case UINT32_C(0x002d6978):goto L_002d6978;
 case UINT32_C(0x002d697c):goto L_002d697c;
 case UINT32_C(0x002d6980):goto L_002d6980;
 case UINT32_C(0x002d6984):goto L_002d6984;
 case UINT32_C(0x002d6988):goto L_002d6988;
 case UINT32_C(0x002d698c):goto L_002d698c;
 case UINT32_C(0x002d6990):goto L_002d6990;
 case UINT32_C(0x002d6994):goto L_002d6994;
 case UINT32_C(0x002d6998):goto L_002d6998;
 case UINT32_C(0x002d699c):goto L_002d699c;
 case UINT32_C(0x002d69a0):goto L_002d69a0;
 case UINT32_C(0x002d69a4):goto L_002d69a4;
 case UINT32_C(0x002d69a8):goto L_002d69a8;
 case UINT32_C(0x002d69ac):goto L_002d69ac;
 case UINT32_C(0x002d69b0):goto L_002d69b0;
 case UINT32_C(0x002d69b4):goto L_002d69b4;
 case UINT32_C(0x002d69b8):goto L_002d69b8;
 case UINT32_C(0x002d69bc):goto L_002d69bc;
 case UINT32_C(0x002d69c0):goto L_002d69c0;
 case UINT32_C(0x002d69c4):goto L_002d69c4;
 case UINT32_C(0x002d69c8):goto L_002d69c8;
 case UINT32_C(0x002d69cc):goto L_002d69cc;
 case UINT32_C(0x002d69d0):goto L_002d69d0;
 case UINT32_C(0x002d69d4):goto L_002d69d4;
 case UINT32_C(0x002d69d8):goto L_002d69d8;
 case UINT32_C(0x002d69dc):goto L_002d69dc;
 case UINT32_C(0x002d69e0):goto L_002d69e0;
 case UINT32_C(0x002d69e4):goto L_002d69e4;
 case UINT32_C(0x002d69e8):goto L_002d69e8;
 case UINT32_C(0x002d69ec):goto L_002d69ec;
 case UINT32_C(0x002d69f0):goto L_002d69f0;
 case UINT32_C(0x002d69f4):goto L_002d69f4;
 case UINT32_C(0x002d69f8):goto L_002d69f8;
 case UINT32_C(0x002d69fc):goto L_002d69fc;
 case UINT32_C(0x002d6a00):goto L_002d6a00;
 case UINT32_C(0x002d6a04):goto L_002d6a04;
 case UINT32_C(0x002d6a08):goto L_002d6a08;
 case UINT32_C(0x002d6a0c):goto L_002d6a0c;
 case UINT32_C(0x002d6a10):goto L_002d6a10;
 case UINT32_C(0x002d6a14):goto L_002d6a14;
 case UINT32_C(0x002d6a18):goto L_002d6a18;
 case UINT32_C(0x002d6a1c):goto L_002d6a1c;
 case UINT32_C(0x002d6a20):goto L_002d6a20;
 case UINT32_C(0x002d6a24):goto L_002d6a24;
 case UINT32_C(0x002d6a28):goto L_002d6a28;
 case UINT32_C(0x002d6a2c):goto L_002d6a2c;
 case UINT32_C(0x002d6a30):goto L_002d6a30;
 case UINT32_C(0x002d6a34):goto L_002d6a34;
 case UINT32_C(0x002d6a38):goto L_002d6a38;
 case UINT32_C(0x002d6a3c):goto L_002d6a3c;
 case UINT32_C(0x002d6a40):goto L_002d6a40;
 case UINT32_C(0x002d6a44):goto L_002d6a44;
 case UINT32_C(0x002d6a48):goto L_002d6a48;
 case UINT32_C(0x002d6a4c):goto L_002d6a4c;
 case UINT32_C(0x002d6a50):goto L_002d6a50;
 case UINT32_C(0x002d6a54):goto L_002d6a54;
 case UINT32_C(0x002d6a58):goto L_002d6a58;
 case UINT32_C(0x002d6a5c):goto L_002d6a5c;
 case UINT32_C(0x002d6a60):goto L_002d6a60;
 case UINT32_C(0x002d6a64):goto L_002d6a64;
 case UINT32_C(0x002d6a68):goto L_002d6a68;
 case UINT32_C(0x002d6a6c):goto L_002d6a6c;
 case UINT32_C(0x002d6a70):goto L_002d6a70;
 case UINT32_C(0x002d6a74):goto L_002d6a74;
 case UINT32_C(0x002d6a78):goto L_002d6a78;
 case UINT32_C(0x002d6a7c):goto L_002d6a7c;
 case UINT32_C(0x002d6a80):goto L_002d6a80;
 case UINT32_C(0x002d6a84):goto L_002d6a84;
 case UINT32_C(0x002d6a88):goto L_002d6a88;
 case UINT32_C(0x002d6a8c):goto L_002d6a8c;
 case UINT32_C(0x002d6a90):goto L_002d6a90;
 case UINT32_C(0x002d6a94):goto L_002d6a94;
 case UINT32_C(0x002d6a98):goto L_002d6a98;
 case UINT32_C(0x002d6a9c):goto L_002d6a9c;
 case UINT32_C(0x002d6aa0):goto L_002d6aa0;
 case UINT32_C(0x002d6aa4):goto L_002d6aa4;
 case UINT32_C(0x002d6aa8):goto L_002d6aa8;
 case UINT32_C(0x002d6aac):goto L_002d6aac;
 case UINT32_C(0x002d6ab0):goto L_002d6ab0;
 case UINT32_C(0x002d6ab4):goto L_002d6ab4;
 case UINT32_C(0x002d6ab8):goto L_002d6ab8;
 case UINT32_C(0x002d6abc):goto L_002d6abc;
 case UINT32_C(0x002d6ac0):goto L_002d6ac0;
 case UINT32_C(0x002d6ac4):goto L_002d6ac4;
 case UINT32_C(0x002d6ac8):goto L_002d6ac8;
 case UINT32_C(0x002d6acc):goto L_002d6acc;
 case UINT32_C(0x002d6ad0):goto L_002d6ad0;
 case UINT32_C(0x002d6ad4):goto L_002d6ad4;
 case UINT32_C(0x002d6ad8):goto L_002d6ad8;
 case UINT32_C(0x002d6adc):goto L_002d6adc;
 case UINT32_C(0x002d6ae0):goto L_002d6ae0;
 case UINT32_C(0x002d6ae4):goto L_002d6ae4;
 case UINT32_C(0x002d6ae8):goto L_002d6ae8;
 case UINT32_C(0x002d6aec):goto L_002d6aec;
 case UINT32_C(0x002d6af0):goto L_002d6af0;
 case UINT32_C(0x002d6af4):goto L_002d6af4;
 case UINT32_C(0x002d6af8):goto L_002d6af8;
 case UINT32_C(0x002d6afc):goto L_002d6afc;
 case UINT32_C(0x002d6b00):goto L_002d6b00;
 case UINT32_C(0x002d6b04):goto L_002d6b04;
 case UINT32_C(0x002d6b08):goto L_002d6b08;
 case UINT32_C(0x002d6b0c):goto L_002d6b0c;
 case UINT32_C(0x002d6b10):goto L_002d6b10;
 case UINT32_C(0x002d6b14):goto L_002d6b14;
 case UINT32_C(0x002d6b18):goto L_002d6b18;
 case UINT32_C(0x002d6b1c):goto L_002d6b1c;
 case UINT32_C(0x002d6b20):goto L_002d6b20;
 case UINT32_C(0x002d6b24):goto L_002d6b24;
 case UINT32_C(0x002d6b28):goto L_002d6b28;
 case UINT32_C(0x002d6b2c):goto L_002d6b2c;
 case UINT32_C(0x002d6b30):goto L_002d6b30;
 case UINT32_C(0x002d6b34):goto L_002d6b34;
 case UINT32_C(0x002d6b38):goto L_002d6b38;
 case UINT32_C(0x002d6b3c):goto L_002d6b3c;
 case UINT32_C(0x002d6b40):goto L_002d6b40;
 case UINT32_C(0x002d6b44):goto L_002d6b44;
 case UINT32_C(0x002d6b48):goto L_002d6b48;
 case UINT32_C(0x002d6b4c):goto L_002d6b4c;
 case UINT32_C(0x002d6b50):goto L_002d6b50;
 case UINT32_C(0x002d6b54):goto L_002d6b54;
 case UINT32_C(0x002d6b58):goto L_002d6b58;
 case UINT32_C(0x002d6b5c):goto L_002d6b5c;
 case UINT32_C(0x002d6b60):goto L_002d6b60;
 case UINT32_C(0x002d6b64):goto L_002d6b64;
 case UINT32_C(0x002d6b68):goto L_002d6b68;
 case UINT32_C(0x002d6b6c):goto L_002d6b6c;
 case UINT32_C(0x002d6b70):goto L_002d6b70;
 case UINT32_C(0x002d6b74):goto L_002d6b74;
 case UINT32_C(0x002d6b78):goto L_002d6b78;
 case UINT32_C(0x002d6b7c):goto L_002d6b7c;
 case UINT32_C(0x002d6b80):goto L_002d6b80;
 case UINT32_C(0x002d6b84):goto L_002d6b84;
 case UINT32_C(0x002d6b88):goto L_002d6b88;
 case UINT32_C(0x002d6b8c):goto L_002d6b8c;
 case UINT32_C(0x002d6b90):goto L_002d6b90;
 case UINT32_C(0x002d6b94):goto L_002d6b94;
 case UINT32_C(0x002d6b98):goto L_002d6b98;
 case UINT32_C(0x002d6b9c):goto L_002d6b9c;
 case UINT32_C(0x002d6ba0):goto L_002d6ba0;
 case UINT32_C(0x002d6ba4):goto L_002d6ba4;
 case UINT32_C(0x002d6ba8):goto L_002d6ba8;
 case UINT32_C(0x002d6bac):goto L_002d6bac;
 case UINT32_C(0x002d6bb0):goto L_002d6bb0;
 case UINT32_C(0x002d6bb4):goto L_002d6bb4;
 case UINT32_C(0x002d6bb8):goto L_002d6bb8;
 case UINT32_C(0x002d6bbc):goto L_002d6bbc;
 case UINT32_C(0x002d6bc0):goto L_002d6bc0;
 case UINT32_C(0x002d6bc4):goto L_002d6bc4;
 case UINT32_C(0x002d6bc8):goto L_002d6bc8;
 case UINT32_C(0x002d6bcc):goto L_002d6bcc;
 case UINT32_C(0x002d6bd0):goto L_002d6bd0;
 case UINT32_C(0x002d6bd4):goto L_002d6bd4;
 case UINT32_C(0x002d6bd8):goto L_002d6bd8;
 case UINT32_C(0x002d6bdc):goto L_002d6bdc;
 case UINT32_C(0x002d6be0):goto L_002d6be0;
 case UINT32_C(0x002d6be4):goto L_002d6be4;
 case UINT32_C(0x002d6be8):goto L_002d6be8;
 case UINT32_C(0x002d6bec):goto L_002d6bec;
 case UINT32_C(0x002d6bf0):goto L_002d6bf0;
 case UINT32_C(0x002d6bf4):goto L_002d6bf4;
 case UINT32_C(0x002d6bf8):goto L_002d6bf8;
 case UINT32_C(0x002d6bfc):goto L_002d6bfc;
 case UINT32_C(0x002d6c00):goto L_002d6c00;
 case UINT32_C(0x002d6c04):goto L_002d6c04;
 case UINT32_C(0x002d6c08):goto L_002d6c08;
 case UINT32_C(0x002d6c0c):goto L_002d6c0c;
 case UINT32_C(0x002d6c10):goto L_002d6c10;
 case UINT32_C(0x002d6c14):goto L_002d6c14;
 case UINT32_C(0x002d6c18):goto L_002d6c18;
 case UINT32_C(0x002d6c1c):goto L_002d6c1c;
 case UINT32_C(0x002d6c20):goto L_002d6c20;
 case UINT32_C(0x002d6c24):goto L_002d6c24;
 case UINT32_C(0x002d6c28):goto L_002d6c28;
 case UINT32_C(0x002d6c2c):goto L_002d6c2c;
 case UINT32_C(0x002d6c30):goto L_002d6c30;
 case UINT32_C(0x002d6c34):goto L_002d6c34;
 case UINT32_C(0x002d6c38):goto L_002d6c38;
 case UINT32_C(0x002d6c3c):goto L_002d6c3c;
 case UINT32_C(0x002d6c40):goto L_002d6c40;
 case UINT32_C(0x002d6c44):goto L_002d6c44;
 case UINT32_C(0x002d6c48):goto L_002d6c48;
 case UINT32_C(0x002d6c4c):goto L_002d6c4c;
 case UINT32_C(0x002d6c50):goto L_002d6c50;
 case UINT32_C(0x002d6c54):goto L_002d6c54;
 case UINT32_C(0x002d6c58):goto L_002d6c58;
 case UINT32_C(0x002d6c5c):goto L_002d6c5c;
 case UINT32_C(0x002d6c60):goto L_002d6c60;
 case UINT32_C(0x002d6c64):goto L_002d6c64;
 case UINT32_C(0x002d6c68):goto L_002d6c68;
 case UINT32_C(0x002d6c6c):goto L_002d6c6c;
 case UINT32_C(0x002d6c70):goto L_002d6c70;
 case UINT32_C(0x002d6c74):goto L_002d6c74;
 case UINT32_C(0x002d6c78):goto L_002d6c78;
 case UINT32_C(0x002d6c7c):goto L_002d6c7c;
 case UINT32_C(0x002d6c80):goto L_002d6c80;
 case UINT32_C(0x002d6c84):goto L_002d6c84;
 case UINT32_C(0x002d6c88):goto L_002d6c88;
 case UINT32_C(0x002d6c8c):goto L_002d6c8c;
 case UINT32_C(0x002d6c90):goto L_002d6c90;
 case UINT32_C(0x002d6c94):goto L_002d6c94;
 case UINT32_C(0x002d6c98):goto L_002d6c98;
 case UINT32_C(0x002d6c9c):goto L_002d6c9c;
 case UINT32_C(0x002d6ca0):goto L_002d6ca0;
 case UINT32_C(0x002d6ca4):goto L_002d6ca4;
 case UINT32_C(0x002d6ca8):goto L_002d6ca8;
 case UINT32_C(0x002d6cac):goto L_002d6cac;
 case UINT32_C(0x002d6cb0):goto L_002d6cb0;
 case UINT32_C(0x002d6cb4):goto L_002d6cb4;
 case UINT32_C(0x002d6cb8):goto L_002d6cb8;
 case UINT32_C(0x002d6cbc):goto L_002d6cbc;
 case UINT32_C(0x002d6cc0):goto L_002d6cc0;
 case UINT32_C(0x002d6cc4):goto L_002d6cc4;
 case UINT32_C(0x002d6cc8):goto L_002d6cc8;
 case UINT32_C(0x002d6ccc):goto L_002d6ccc;
 case UINT32_C(0x002d6cd0):goto L_002d6cd0;
 case UINT32_C(0x002d6cd4):goto L_002d6cd4;
 case UINT32_C(0x002d6cd8):goto L_002d6cd8;
 case UINT32_C(0x002d6cdc):goto L_002d6cdc;
 case UINT32_C(0x002d6ce0):goto L_002d6ce0;
 case UINT32_C(0x002d6ce4):goto L_002d6ce4;
 case UINT32_C(0x002d6ce8):goto L_002d6ce8;
 case UINT32_C(0x002d6cec):goto L_002d6cec;
 case UINT32_C(0x002d6cf0):goto L_002d6cf0;
 case UINT32_C(0x002d6cf4):goto L_002d6cf4;
 case UINT32_C(0x002d6cf8):goto L_002d6cf8;
 case UINT32_C(0x002d6cfc):goto L_002d6cfc;
 case UINT32_C(0x002d6d00):goto L_002d6d00;
 case UINT32_C(0x002d6d04):goto L_002d6d04;
 case UINT32_C(0x002d6d08):goto L_002d6d08;
 case UINT32_C(0x002d6d0c):goto L_002d6d0c;
 case UINT32_C(0x002d6d10):goto L_002d6d10;
 case UINT32_C(0x002d6d14):goto L_002d6d14;
 case UINT32_C(0x002d6d18):goto L_002d6d18;
 case UINT32_C(0x002d6d1c):goto L_002d6d1c;
 case UINT32_C(0x002d6d20):goto L_002d6d20;
 case UINT32_C(0x002d6d24):goto L_002d6d24;
 case UINT32_C(0x002d6d28):goto L_002d6d28;
 case UINT32_C(0x002d6d2c):goto L_002d6d2c;
 case UINT32_C(0x002d6d30):goto L_002d6d30;
 case UINT32_C(0x002d6d34):goto L_002d6d34;
 case UINT32_C(0x002d6d38):goto L_002d6d38;
 case UINT32_C(0x002d6d3c):goto L_002d6d3c;
 case UINT32_C(0x002d6d40):goto L_002d6d40;
 case UINT32_C(0x002d6d44):goto L_002d6d44;
 case UINT32_C(0x002d6d48):goto L_002d6d48;
 case UINT32_C(0x002d6d4c):goto L_002d6d4c;
 case UINT32_C(0x002d6d50):goto L_002d6d50;
 case UINT32_C(0x002d6d54):goto L_002d6d54;
 case UINT32_C(0x002d6d58):goto L_002d6d58;
 case UINT32_C(0x002d6d5c):goto L_002d6d5c;
 case UINT32_C(0x002d6d60):goto L_002d6d60;
 case UINT32_C(0x002d6d64):goto L_002d6d64;
 case UINT32_C(0x002d6d68):goto L_002d6d68;
 case UINT32_C(0x002d6d6c):goto L_002d6d6c;
 case UINT32_C(0x002d6d70):goto L_002d6d70;
 case UINT32_C(0x002d6d74):goto L_002d6d74;
 case UINT32_C(0x002d6d78):goto L_002d6d78;
 case UINT32_C(0x002d6d7c):goto L_002d6d7c;
 case UINT32_C(0x002d6d80):goto L_002d6d80;
 case UINT32_C(0x002d6d84):goto L_002d6d84;
 case UINT32_C(0x002d6d88):goto L_002d6d88;
 case UINT32_C(0x002d6d8c):goto L_002d6d8c;
 case UINT32_C(0x002d6d90):goto L_002d6d90;
 case UINT32_C(0x002d6d94):goto L_002d6d94;
 case UINT32_C(0x002d6d98):goto L_002d6d98;
 case UINT32_C(0x002d6d9c):goto L_002d6d9c;
 case UINT32_C(0x002d6da0):goto L_002d6da0;
 case UINT32_C(0x002d6da4):goto L_002d6da4;
 case UINT32_C(0x002d6da8):goto L_002d6da8;
 case UINT32_C(0x002d6dac):goto L_002d6dac;
 case UINT32_C(0x002d6db0):goto L_002d6db0;
 case UINT32_C(0x002d6db4):goto L_002d6db4;
 case UINT32_C(0x002d6db8):goto L_002d6db8;
 case UINT32_C(0x002d6dbc):goto L_002d6dbc;
 case UINT32_C(0x002d6dc0):goto L_002d6dc0;
 case UINT32_C(0x002d6dc4):goto L_002d6dc4;
 case UINT32_C(0x002d6dc8):goto L_002d6dc8;
 case UINT32_C(0x002d6dcc):goto L_002d6dcc;
 case UINT32_C(0x002d6dd0):goto L_002d6dd0;
 case UINT32_C(0x002d6dd4):goto L_002d6dd4;
 case UINT32_C(0x002d6dd8):goto L_002d6dd8;
 case UINT32_C(0x002d6ddc):goto L_002d6ddc;
 case UINT32_C(0x002d6de0):goto L_002d6de0;
 case UINT32_C(0x002d6de4):goto L_002d6de4;
 case UINT32_C(0x002d6de8):goto L_002d6de8;
 case UINT32_C(0x002d6dec):goto L_002d6dec;
 case UINT32_C(0x002d6df0):goto L_002d6df0;
 case UINT32_C(0x002d6df4):goto L_002d6df4;
 case UINT32_C(0x002d6df8):goto L_002d6df8;
 case UINT32_C(0x002d6dfc):goto L_002d6dfc;
 case UINT32_C(0x002d6e00):goto L_002d6e00;
 case UINT32_C(0x002d6e04):goto L_002d6e04;
 case UINT32_C(0x002d6e08):goto L_002d6e08;
 case UINT32_C(0x002d6e0c):goto L_002d6e0c;
 case UINT32_C(0x002d6e10):goto L_002d6e10;
 case UINT32_C(0x002d6e14):goto L_002d6e14;
 case UINT32_C(0x002d6e18):goto L_002d6e18;
 case UINT32_C(0x002d6e1c):goto L_002d6e1c;
 case UINT32_C(0x002d6e20):goto L_002d6e20;
 case UINT32_C(0x002d6e24):goto L_002d6e24;
 case UINT32_C(0x002d6e28):goto L_002d6e28;
 case UINT32_C(0x002d6e2c):goto L_002d6e2c;
 case UINT32_C(0x002d6e30):goto L_002d6e30;
 case UINT32_C(0x002d6e34):goto L_002d6e34;
 case UINT32_C(0x002d6e38):goto L_002d6e38;
 case UINT32_C(0x002d6e3c):goto L_002d6e3c;
 case UINT32_C(0x002d6e40):goto L_002d6e40;
 case UINT32_C(0x002d6e44):goto L_002d6e44;
 case UINT32_C(0x002d6e48):goto L_002d6e48;
 case UINT32_C(0x002d6e4c):goto L_002d6e4c;
 case UINT32_C(0x002d6e50):goto L_002d6e50;
 case UINT32_C(0x002d6e54):goto L_002d6e54;
 case UINT32_C(0x002d6e58):goto L_002d6e58;
 case UINT32_C(0x002d6e5c):goto L_002d6e5c;
 case UINT32_C(0x002d6e60):goto L_002d6e60;
 case UINT32_C(0x002d6e64):goto L_002d6e64;
 case UINT32_C(0x002d6e68):goto L_002d6e68;
 case UINT32_C(0x002d6e6c):goto L_002d6e6c;
 case UINT32_C(0x002d6e70):goto L_002d6e70;
 case UINT32_C(0x002d6e74):goto L_002d6e74;
 case UINT32_C(0x002d6e78):goto L_002d6e78;
 case UINT32_C(0x002d6e7c):goto L_002d6e7c;
 case UINT32_C(0x002d6e80):goto L_002d6e80;
 case UINT32_C(0x002d6e84):goto L_002d6e84;
 case UINT32_C(0x002d6e88):goto L_002d6e88;
 case UINT32_C(0x002d6e8c):goto L_002d6e8c;
 case UINT32_C(0x002d6e90):goto L_002d6e90;
 case UINT32_C(0x002d6e94):goto L_002d6e94;
 case UINT32_C(0x002d6e98):goto L_002d6e98;
 case UINT32_C(0x002d6e9c):goto L_002d6e9c;
 case UINT32_C(0x002d6ea0):goto L_002d6ea0;
 case UINT32_C(0x002d6ea4):goto L_002d6ea4;
 case UINT32_C(0x002d6ea8):goto L_002d6ea8;
 case UINT32_C(0x002d6eac):goto L_002d6eac;
 case UINT32_C(0x002d6eb0):goto L_002d6eb0;
 case UINT32_C(0x002d6eb4):goto L_002d6eb4;
 case UINT32_C(0x002d6eb8):goto L_002d6eb8;
 case UINT32_C(0x002d6ebc):goto L_002d6ebc;
 case UINT32_C(0x002d6ec0):goto L_002d6ec0;
 case UINT32_C(0x002d6ec4):goto L_002d6ec4;
 case UINT32_C(0x002d6ec8):goto L_002d6ec8;
 case UINT32_C(0x002d6ecc):goto L_002d6ecc;
 case UINT32_C(0x002d6ed0):goto L_002d6ed0;
 case UINT32_C(0x002d6ed4):goto L_002d6ed4;
 case UINT32_C(0x002d6ed8):goto L_002d6ed8;
 case UINT32_C(0x002d6edc):goto L_002d6edc;
 case UINT32_C(0x002d6ee0):goto L_002d6ee0;
 case UINT32_C(0x002d6ee4):goto L_002d6ee4;
 case UINT32_C(0x002d6ee8):goto L_002d6ee8;
 case UINT32_C(0x002d6eec):goto L_002d6eec;
 case UINT32_C(0x002d6ef0):goto L_002d6ef0;
 case UINT32_C(0x002d6ef4):goto L_002d6ef4;
 case UINT32_C(0x002d6ef8):goto L_002d6ef8;
 case UINT32_C(0x002d6efc):goto L_002d6efc;
 case UINT32_C(0x002d6f00):goto L_002d6f00;
 case UINT32_C(0x002d6f04):goto L_002d6f04;
 case UINT32_C(0x002d6f08):goto L_002d6f08;
 case UINT32_C(0x002d6f0c):goto L_002d6f0c;
 case UINT32_C(0x002d6f10):goto L_002d6f10;
 case UINT32_C(0x002d6f14):goto L_002d6f14;
 case UINT32_C(0x002d6f18):goto L_002d6f18;
 case UINT32_C(0x002d6f1c):goto L_002d6f1c;
 case UINT32_C(0x002d6f20):goto L_002d6f20;
 case UINT32_C(0x002d6f24):goto L_002d6f24;
 case UINT32_C(0x002d6f28):goto L_002d6f28;
 case UINT32_C(0x002d6f2c):goto L_002d6f2c;
 case UINT32_C(0x002d6f30):goto L_002d6f30;
 case UINT32_C(0x002d6f34):goto L_002d6f34;
 case UINT32_C(0x002d6f38):goto L_002d6f38;
 case UINT32_C(0x002d6f3c):goto L_002d6f3c;
 case UINT32_C(0x002d6f40):goto L_002d6f40;
 case UINT32_C(0x002d6f44):goto L_002d6f44;
 case UINT32_C(0x002d6f48):goto L_002d6f48;
 case UINT32_C(0x002d6f4c):goto L_002d6f4c;
 case UINT32_C(0x002d6f50):goto L_002d6f50;
 case UINT32_C(0x002d6f54):goto L_002d6f54;
 case UINT32_C(0x002d6f58):goto L_002d6f58;
 case UINT32_C(0x002d6f5c):goto L_002d6f5c;
 case UINT32_C(0x002d6f60):goto L_002d6f60;
 case UINT32_C(0x002d6f64):goto L_002d6f64;
 case UINT32_C(0x002d6f68):goto L_002d6f68;
 case UINT32_C(0x002d6f6c):goto L_002d6f6c;
 case UINT32_C(0x002d6f70):goto L_002d6f70;
 case UINT32_C(0x002d6f74):goto L_002d6f74;
 case UINT32_C(0x002d6f78):goto L_002d6f78;
 case UINT32_C(0x002d6f7c):goto L_002d6f7c;
 case UINT32_C(0x002d6f80):goto L_002d6f80;
 case UINT32_C(0x002d6f84):goto L_002d6f84;
 case UINT32_C(0x002d6f88):goto L_002d6f88;
 case UINT32_C(0x002d6f8c):goto L_002d6f8c;
 case UINT32_C(0x002d6f90):goto L_002d6f90;
 case UINT32_C(0x002d6f94):goto L_002d6f94;
 case UINT32_C(0x002d6f98):goto L_002d6f98;
 case UINT32_C(0x002d6f9c):goto L_002d6f9c;
 case UINT32_C(0x002d6fa0):goto L_002d6fa0;
 case UINT32_C(0x002d6fa4):goto L_002d6fa4;
 case UINT32_C(0x002d6fa8):goto L_002d6fa8;
 case UINT32_C(0x002d6fac):goto L_002d6fac;
 case UINT32_C(0x002d6fb0):goto L_002d6fb0;
 case UINT32_C(0x002d6fb4):goto L_002d6fb4;
 case UINT32_C(0x002d6fb8):goto L_002d6fb8;
 case UINT32_C(0x002d6fbc):goto L_002d6fbc;
 case UINT32_C(0x002d6fc0):goto L_002d6fc0;
 case UINT32_C(0x002d6fc4):goto L_002d6fc4;
 case UINT32_C(0x002d6fc8):goto L_002d6fc8;
 case UINT32_C(0x002d6fcc):goto L_002d6fcc;
 case UINT32_C(0x002d6fd0):goto L_002d6fd0;
 case UINT32_C(0x002d6fd4):goto L_002d6fd4;
 case UINT32_C(0x002d6fd8):goto L_002d6fd8;
 case UINT32_C(0x002d6fdc):goto L_002d6fdc;
 case UINT32_C(0x002d6fe0):goto L_002d6fe0;
 case UINT32_C(0x002d6fe4):goto L_002d6fe4;
 case UINT32_C(0x002d6fe8):goto L_002d6fe8;
 case UINT32_C(0x002d6fec):goto L_002d6fec;
 case UINT32_C(0x002d6ff0):goto L_002d6ff0;
 case UINT32_C(0x002d6ff4):goto L_002d6ff4;
 case UINT32_C(0x002d6ff8):goto L_002d6ff8;
 case UINT32_C(0x002d6ffc):goto L_002d6ffc;
 case UINT32_C(0x002d7000):goto L_002d7000;
 case UINT32_C(0x002d7004):goto L_002d7004;
 case UINT32_C(0x002d7008):goto L_002d7008;
 case UINT32_C(0x002d700c):goto L_002d700c;
 case UINT32_C(0x002d7010):goto L_002d7010;
 case UINT32_C(0x002d7014):goto L_002d7014;
 case UINT32_C(0x002d7018):goto L_002d7018;
 case UINT32_C(0x002d701c):goto L_002d701c;
 case UINT32_C(0x002d7020):goto L_002d7020;
 case UINT32_C(0x002d7024):goto L_002d7024;
 case UINT32_C(0x002d7028):goto L_002d7028;
 case UINT32_C(0x002d702c):goto L_002d702c;
 case UINT32_C(0x002d7030):goto L_002d7030;
 case UINT32_C(0x002d7034):goto L_002d7034;
 case UINT32_C(0x002d7038):goto L_002d7038;
 case UINT32_C(0x002d703c):goto L_002d703c;
 case UINT32_C(0x002d7040):goto L_002d7040;
 case UINT32_C(0x002d7044):goto L_002d7044;
 case UINT32_C(0x002d7048):goto L_002d7048;
 case UINT32_C(0x002d704c):goto L_002d704c;
 case UINT32_C(0x002d7050):goto L_002d7050;
 case UINT32_C(0x002d7054):goto L_002d7054;
 case UINT32_C(0x002d7058):goto L_002d7058;
 case UINT32_C(0x002d705c):goto L_002d705c;
 case UINT32_C(0x002d7060):goto L_002d7060;
 case UINT32_C(0x002d7064):goto L_002d7064;
 case UINT32_C(0x002d7068):goto L_002d7068;
 case UINT32_C(0x002d706c):goto L_002d706c;
 case UINT32_C(0x002d7070):goto L_002d7070;
 case UINT32_C(0x002d7074):goto L_002d7074;
 case UINT32_C(0x002d7078):goto L_002d7078;
 case UINT32_C(0x002d707c):goto L_002d707c;
 case UINT32_C(0x002d7080):goto L_002d7080;
 case UINT32_C(0x002d7084):goto L_002d7084;
 case UINT32_C(0x002d7088):goto L_002d7088;
 case UINT32_C(0x002d708c):goto L_002d708c;
 case UINT32_C(0x002d7090):goto L_002d7090;
 case UINT32_C(0x002d7094):goto L_002d7094;
 case UINT32_C(0x002d7098):goto L_002d7098;
 case UINT32_C(0x002d709c):goto L_002d709c;
 case UINT32_C(0x002d70a0):goto L_002d70a0;
 case UINT32_C(0x002d70a4):goto L_002d70a4;
 case UINT32_C(0x002d70a8):goto L_002d70a8;
 case UINT32_C(0x002d70ac):goto L_002d70ac;
 case UINT32_C(0x002d70b0):goto L_002d70b0;
 case UINT32_C(0x002d70b4):goto L_002d70b4;
 case UINT32_C(0x002d70b8):goto L_002d70b8;
 case UINT32_C(0x002d70bc):goto L_002d70bc;
 case UINT32_C(0x002d70c0):goto L_002d70c0;
 case UINT32_C(0x002d70c4):goto L_002d70c4;
 case UINT32_C(0x002d70c8):goto L_002d70c8;
 case UINT32_C(0x002d70cc):goto L_002d70cc;
 case UINT32_C(0x002d70d0):goto L_002d70d0;
 case UINT32_C(0x002d70d4):goto L_002d70d4;
 case UINT32_C(0x002d70d8):goto L_002d70d8;
 case UINT32_C(0x002d70dc):goto L_002d70dc;
 case UINT32_C(0x002d70e0):goto L_002d70e0;
 case UINT32_C(0x002d70e4):goto L_002d70e4;
 case UINT32_C(0x002d70e8):goto L_002d70e8;
 case UINT32_C(0x002d70ec):goto L_002d70ec;
 case UINT32_C(0x002d70f0):goto L_002d70f0;
 case UINT32_C(0x002d70f4):goto L_002d70f4;
 case UINT32_C(0x002d70f8):goto L_002d70f8;
 case UINT32_C(0x002d70fc):goto L_002d70fc;
 case UINT32_C(0x002d7100):goto L_002d7100;
 case UINT32_C(0x002d7104):goto L_002d7104;
 case UINT32_C(0x002d7108):goto L_002d7108;
 case UINT32_C(0x002d710c):goto L_002d710c;
 case UINT32_C(0x002d7110):goto L_002d7110;
 case UINT32_C(0x002d7114):goto L_002d7114;
 case UINT32_C(0x002d7118):goto L_002d7118;
 case UINT32_C(0x002d711c):goto L_002d711c;
 case UINT32_C(0x002d7120):goto L_002d7120;
 case UINT32_C(0x002d7124):goto L_002d7124;
 case UINT32_C(0x002d7128):goto L_002d7128;
 case UINT32_C(0x002d712c):goto L_002d712c;
 case UINT32_C(0x002d7130):goto L_002d7130;
 case UINT32_C(0x002d7134):goto L_002d7134;
 case UINT32_C(0x002d7138):goto L_002d7138;
 case UINT32_C(0x002d713c):goto L_002d713c;
 case UINT32_C(0x002d7140):goto L_002d7140;
 case UINT32_C(0x002d7144):goto L_002d7144;
 case UINT32_C(0x002d7148):goto L_002d7148;
 case UINT32_C(0x002d714c):goto L_002d714c;
 case UINT32_C(0x002d7150):goto L_002d7150;
 case UINT32_C(0x002d7154):goto L_002d7154;
 case UINT32_C(0x002d7158):goto L_002d7158;
 case UINT32_C(0x002d715c):goto L_002d715c;
 case UINT32_C(0x002d7160):goto L_002d7160;
 case UINT32_C(0x002d7164):goto L_002d7164;
 case UINT32_C(0x002d7168):goto L_002d7168;
 case UINT32_C(0x002d716c):goto L_002d716c;
 case UINT32_C(0x002d7170):goto L_002d7170;
 case UINT32_C(0x002d7174):goto L_002d7174;
 case UINT32_C(0x002d7178):goto L_002d7178;
 case UINT32_C(0x002d717c):goto L_002d717c;
 case UINT32_C(0x002d7180):goto L_002d7180;
 case UINT32_C(0x002d7184):goto L_002d7184;
 case UINT32_C(0x002d7188):goto L_002d7188;
 case UINT32_C(0x002d718c):goto L_002d718c;
 case UINT32_C(0x002d7190):goto L_002d7190;
 case UINT32_C(0x002d7194):goto L_002d7194;
 case UINT32_C(0x002d7198):goto L_002d7198;
 case UINT32_C(0x002d719c):goto L_002d719c;
 case UINT32_C(0x002d71a0):goto L_002d71a0;
 case UINT32_C(0x002d71a4):goto L_002d71a4;
 case UINT32_C(0x002d71a8):goto L_002d71a8;
 case UINT32_C(0x002d71ac):goto L_002d71ac;
 case UINT32_C(0x002d71b0):goto L_002d71b0;
 case UINT32_C(0x002d71b4):goto L_002d71b4;
 case UINT32_C(0x002d71b8):goto L_002d71b8;
 case UINT32_C(0x002d71bc):goto L_002d71bc;
 case UINT32_C(0x002d71c0):goto L_002d71c0;
 case UINT32_C(0x002d71c4):goto L_002d71c4;
 case UINT32_C(0x002d71c8):goto L_002d71c8;
 case UINT32_C(0x002d71cc):goto L_002d71cc;
 case UINT32_C(0x002d71d0):goto L_002d71d0;
 case UINT32_C(0x002d71d4):goto L_002d71d4;
 case UINT32_C(0x002d71d8):goto L_002d71d8;
 case UINT32_C(0x002d71dc):goto L_002d71dc;
 case UINT32_C(0x002d71e0):goto L_002d71e0;
 case UINT32_C(0x002d71e4):goto L_002d71e4;
 case UINT32_C(0x002d71e8):goto L_002d71e8;
 case UINT32_C(0x002d71ec):goto L_002d71ec;
 case UINT32_C(0x002d71f0):goto L_002d71f0;
 case UINT32_C(0x002d71f4):goto L_002d71f4;
 case UINT32_C(0x002d71f8):goto L_002d71f8;
 case UINT32_C(0x002d71fc):goto L_002d71fc;
 case UINT32_C(0x002d7200):goto L_002d7200;
 case UINT32_C(0x002d7204):goto L_002d7204;
 case UINT32_C(0x002d7208):goto L_002d7208;
 case UINT32_C(0x002d720c):goto L_002d720c;
 case UINT32_C(0x002d7210):goto L_002d7210;
 case UINT32_C(0x002d7214):goto L_002d7214;
 case UINT32_C(0x002d7218):goto L_002d7218;
 case UINT32_C(0x002d721c):goto L_002d721c;
 case UINT32_C(0x002d7220):goto L_002d7220;
 case UINT32_C(0x002d7224):goto L_002d7224;
 case UINT32_C(0x002d7228):goto L_002d7228;
 case UINT32_C(0x002d722c):goto L_002d722c;
 case UINT32_C(0x002d7230):goto L_002d7230;
 case UINT32_C(0x002d7234):goto L_002d7234;
 case UINT32_C(0x002d7238):goto L_002d7238;
 case UINT32_C(0x002d723c):goto L_002d723c;
 case UINT32_C(0x002d7240):goto L_002d7240;
 case UINT32_C(0x002d7244):goto L_002d7244;
 case UINT32_C(0x002d7248):goto L_002d7248;
 case UINT32_C(0x002d724c):goto L_002d724c;
 case UINT32_C(0x002d7250):goto L_002d7250;
 case UINT32_C(0x002d7254):goto L_002d7254;
 case UINT32_C(0x002d7258):goto L_002d7258;
 case UINT32_C(0x002d725c):goto L_002d725c;
 case UINT32_C(0x002d7260):goto L_002d7260;
 case UINT32_C(0x002d7264):goto L_002d7264;
 case UINT32_C(0x002d7268):goto L_002d7268;
 case UINT32_C(0x002d726c):goto L_002d726c;
 case UINT32_C(0x002d7270):goto L_002d7270;
 case UINT32_C(0x002d7274):goto L_002d7274;
 case UINT32_C(0x002d7278):goto L_002d7278;
 case UINT32_C(0x002d727c):goto L_002d727c;
 case UINT32_C(0x002d7280):goto L_002d7280;
 case UINT32_C(0x002d7284):goto L_002d7284;
 case UINT32_C(0x002d7288):goto L_002d7288;
 case UINT32_C(0x002d728c):goto L_002d728c;
 case UINT32_C(0x002d7290):goto L_002d7290;
 case UINT32_C(0x002d7294):goto L_002d7294;
 case UINT32_C(0x002d7298):goto L_002d7298;
 case UINT32_C(0x002d729c):goto L_002d729c;
 case UINT32_C(0x002d72a0):goto L_002d72a0;
 case UINT32_C(0x002d72a4):goto L_002d72a4;
 case UINT32_C(0x002d72a8):goto L_002d72a8;
 case UINT32_C(0x002d72ac):goto L_002d72ac;
 case UINT32_C(0x002d72b0):goto L_002d72b0;
 case UINT32_C(0x002d72b4):goto L_002d72b4;
 case UINT32_C(0x002d72b8):goto L_002d72b8;
 case UINT32_C(0x002d72bc):goto L_002d72bc;
 case UINT32_C(0x002d72c0):goto L_002d72c0;
 case UINT32_C(0x002d72c4):goto L_002d72c4;
 case UINT32_C(0x002d72c8):goto L_002d72c8;
 case UINT32_C(0x002d72cc):goto L_002d72cc;
 case UINT32_C(0x002d72d0):goto L_002d72d0;
 case UINT32_C(0x002d72d4):goto L_002d72d4;
 case UINT32_C(0x002d72d8):goto L_002d72d8;
 case UINT32_C(0x002d72dc):goto L_002d72dc;
 case UINT32_C(0x002d72e0):goto L_002d72e0;
 case UINT32_C(0x002d72e4):goto L_002d72e4;
 case UINT32_C(0x002d72e8):goto L_002d72e8;
 case UINT32_C(0x002d72ec):goto L_002d72ec;
 case UINT32_C(0x002d72f0):goto L_002d72f0;
 case UINT32_C(0x002d72f4):goto L_002d72f4;
 case UINT32_C(0x002d72f8):goto L_002d72f8;
 case UINT32_C(0x002d72fc):goto L_002d72fc;
 case UINT32_C(0x002d7300):goto L_002d7300;
 case UINT32_C(0x002d7304):goto L_002d7304;
 case UINT32_C(0x002d7308):goto L_002d7308;
 case UINT32_C(0x002d730c):goto L_002d730c;
 case UINT32_C(0x002d7310):goto L_002d7310;
 case UINT32_C(0x002d7314):goto L_002d7314;
 case UINT32_C(0x002d7318):goto L_002d7318;
 case UINT32_C(0x002d731c):goto L_002d731c;
 case UINT32_C(0x002d7320):goto L_002d7320;
 case UINT32_C(0x002d7324):goto L_002d7324;
 case UINT32_C(0x002d7328):goto L_002d7328;
 case UINT32_C(0x002d732c):goto L_002d732c;
 case UINT32_C(0x002d7330):goto L_002d7330;
 case UINT32_C(0x002d7334):goto L_002d7334;
 case UINT32_C(0x002d7338):goto L_002d7338;
 case UINT32_C(0x002d733c):goto L_002d733c;
 case UINT32_C(0x002d7340):goto L_002d7340;
 case UINT32_C(0x002d7344):goto L_002d7344;
 case UINT32_C(0x002d7348):goto L_002d7348;
 case UINT32_C(0x002d734c):goto L_002d734c;
 case UINT32_C(0x002d7350):goto L_002d7350;
 case UINT32_C(0x002d7354):goto L_002d7354;
 case UINT32_C(0x002d7358):goto L_002d7358;
 case UINT32_C(0x002d735c):goto L_002d735c;
 case UINT32_C(0x002d7360):goto L_002d7360;
 case UINT32_C(0x002d7364):goto L_002d7364;
 case UINT32_C(0x002d7368):goto L_002d7368;
 case UINT32_C(0x002d736c):goto L_002d736c;
 case UINT32_C(0x002d7370):goto L_002d7370;
 case UINT32_C(0x002d7374):goto L_002d7374;
 case UINT32_C(0x002d7378):goto L_002d7378;
 case UINT32_C(0x002d737c):goto L_002d737c;
 case UINT32_C(0x002d7380):goto L_002d7380;
 case UINT32_C(0x002d7384):goto L_002d7384;
 case UINT32_C(0x002d7388):goto L_002d7388;
 case UINT32_C(0x002d738c):goto L_002d738c;
 case UINT32_C(0x002d7390):goto L_002d7390;
 case UINT32_C(0x002d7394):goto L_002d7394;
 case UINT32_C(0x002d7398):goto L_002d7398;
 case UINT32_C(0x002d739c):goto L_002d739c;
 case UINT32_C(0x002d73a0):goto L_002d73a0;
 case UINT32_C(0x002d73a4):goto L_002d73a4;
 case UINT32_C(0x002d73a8):goto L_002d73a8;
 case UINT32_C(0x002d73ac):goto L_002d73ac;
 case UINT32_C(0x002d73b0):goto L_002d73b0;
 case UINT32_C(0x002d73b4):goto L_002d73b4;
 case UINT32_C(0x002d73b8):goto L_002d73b8;
 case UINT32_C(0x002d73bc):goto L_002d73bc;
 case UINT32_C(0x002d73c0):goto L_002d73c0;
 case UINT32_C(0x002d73c4):goto L_002d73c4;
 case UINT32_C(0x002d73c8):goto L_002d73c8;
 case UINT32_C(0x002d73cc):goto L_002d73cc;
 case UINT32_C(0x002d73d0):goto L_002d73d0;
 case UINT32_C(0x002d73d4):goto L_002d73d4;
 case UINT32_C(0x002d73d8):goto L_002d73d8;
 case UINT32_C(0x002d73dc):goto L_002d73dc;
 case UINT32_C(0x002d73e0):goto L_002d73e0;
 case UINT32_C(0x002d73e4):goto L_002d73e4;
 case UINT32_C(0x002d73e8):goto L_002d73e8;
 case UINT32_C(0x002d73ec):goto L_002d73ec;
 case UINT32_C(0x002d73f0):goto L_002d73f0;
 case UINT32_C(0x002d73f4):goto L_002d73f4;
 case UINT32_C(0x002d73f8):goto L_002d73f8;
 case UINT32_C(0x002d73fc):goto L_002d73fc;
 case UINT32_C(0x002d7400):goto L_002d7400;
 case UINT32_C(0x002d7404):goto L_002d7404;
 case UINT32_C(0x002d7408):goto L_002d7408;
 case UINT32_C(0x002d740c):goto L_002d740c;
 case UINT32_C(0x002d7410):goto L_002d7410;
 case UINT32_C(0x002d7414):goto L_002d7414;
 case UINT32_C(0x002d7418):goto L_002d7418;
 case UINT32_C(0x002d741c):goto L_002d741c;
 case UINT32_C(0x002d7420):goto L_002d7420;
 case UINT32_C(0x002d7424):goto L_002d7424;
 case UINT32_C(0x002d7428):goto L_002d7428;
 case UINT32_C(0x002d742c):goto L_002d742c;
 case UINT32_C(0x002d7430):goto L_002d7430;
 case UINT32_C(0x002d7434):goto L_002d7434;
 case UINT32_C(0x002d7438):goto L_002d7438;
 case UINT32_C(0x002d743c):goto L_002d743c;
 case UINT32_C(0x002d7440):goto L_002d7440;
 case UINT32_C(0x002d7444):goto L_002d7444;
 case UINT32_C(0x002d7448):goto L_002d7448;
 case UINT32_C(0x002d744c):goto L_002d744c;
 case UINT32_C(0x002d7450):goto L_002d7450;
 case UINT32_C(0x002d7454):goto L_002d7454;
 case UINT32_C(0x002d7458):goto L_002d7458;
 case UINT32_C(0x002d745c):goto L_002d745c;
 case UINT32_C(0x002d7460):goto L_002d7460;
 case UINT32_C(0x002d7464):goto L_002d7464;
 case UINT32_C(0x002d7468):goto L_002d7468;
 case UINT32_C(0x002d746c):goto L_002d746c;
 case UINT32_C(0x002d7470):goto L_002d7470;
 case UINT32_C(0x002d7474):goto L_002d7474;
 case UINT32_C(0x002d7478):goto L_002d7478;
 case UINT32_C(0x002d747c):goto L_002d747c;
 case UINT32_C(0x002d7480):goto L_002d7480;
 case UINT32_C(0x002d7484):goto L_002d7484;
 case UINT32_C(0x002d7488):goto L_002d7488;
 case UINT32_C(0x002d748c):goto L_002d748c;
 case UINT32_C(0x002d7490):goto L_002d7490;
 case UINT32_C(0x002d7494):goto L_002d7494;
 case UINT32_C(0x002d7498):goto L_002d7498;
 case UINT32_C(0x002d749c):goto L_002d749c;
 case UINT32_C(0x002d74a0):goto L_002d74a0;
 case UINT32_C(0x002d74a4):goto L_002d74a4;
 case UINT32_C(0x002d74a8):goto L_002d74a8;
 case UINT32_C(0x002d74ac):goto L_002d74ac;
 case UINT32_C(0x002d74b0):goto L_002d74b0;
 case UINT32_C(0x002d74b4):goto L_002d74b4;
 case UINT32_C(0x002d74b8):goto L_002d74b8;
 case UINT32_C(0x002d74bc):goto L_002d74bc;
 case UINT32_C(0x002d74c0):goto L_002d74c0;
 case UINT32_C(0x002d74c4):goto L_002d74c4;
 case UINT32_C(0x002d74c8):goto L_002d74c8;
 case UINT32_C(0x002d74cc):goto L_002d74cc;
 case UINT32_C(0x002d74d0):goto L_002d74d0;
 case UINT32_C(0x002d74d4):goto L_002d74d4;
 case UINT32_C(0x002d74d8):goto L_002d74d8;
 case UINT32_C(0x002d74dc):goto L_002d74dc;
 case UINT32_C(0x002d74e0):goto L_002d74e0;
 case UINT32_C(0x002d74e4):goto L_002d74e4;
 case UINT32_C(0x002d74e8):goto L_002d74e8;
 case UINT32_C(0x002d74ec):goto L_002d74ec;
 case UINT32_C(0x002d74f0):goto L_002d74f0;
 case UINT32_C(0x002d74f4):goto L_002d74f4;
 case UINT32_C(0x002d74f8):goto L_002d74f8;
 case UINT32_C(0x002d74fc):goto L_002d74fc;
 case UINT32_C(0x002d7500):goto L_002d7500;
 case UINT32_C(0x002d7504):goto L_002d7504;
 case UINT32_C(0x002d7508):goto L_002d7508;
 case UINT32_C(0x002d750c):goto L_002d750c;
 case UINT32_C(0x002d7510):goto L_002d7510;
 case UINT32_C(0x002d7514):goto L_002d7514;
 case UINT32_C(0x002d7518):goto L_002d7518;
 case UINT32_C(0x002d751c):goto L_002d751c;
 case UINT32_C(0x002d7520):goto L_002d7520;
 case UINT32_C(0x002d7524):goto L_002d7524;
 case UINT32_C(0x002d7528):goto L_002d7528;
 case UINT32_C(0x002d752c):goto L_002d752c;
 case UINT32_C(0x002d7530):goto L_002d7530;
 case UINT32_C(0x002d7534):goto L_002d7534;
 case UINT32_C(0x002d7538):goto L_002d7538;
 case UINT32_C(0x002d753c):goto L_002d753c;
 case UINT32_C(0x002d7540):goto L_002d7540;
 case UINT32_C(0x002d7544):goto L_002d7544;
 case UINT32_C(0x002d7548):goto L_002d7548;
 case UINT32_C(0x002d754c):goto L_002d754c;
 case UINT32_C(0x002d7550):goto L_002d7550;
 case UINT32_C(0x002d7554):goto L_002d7554;
 case UINT32_C(0x002d7558):goto L_002d7558;
 case UINT32_C(0x002d755c):goto L_002d755c;
 case UINT32_C(0x002d7560):goto L_002d7560;
 case UINT32_C(0x002d7564):goto L_002d7564;
 case UINT32_C(0x002d7568):goto L_002d7568;
 case UINT32_C(0x002d756c):goto L_002d756c;
 case UINT32_C(0x002d7570):goto L_002d7570;
 case UINT32_C(0x002d7574):goto L_002d7574;
 case UINT32_C(0x002d7578):goto L_002d7578;
 case UINT32_C(0x002d757c):goto L_002d757c;
 case UINT32_C(0x002d7580):goto L_002d7580;
 case UINT32_C(0x002d7584):goto L_002d7584;
 case UINT32_C(0x002d7588):goto L_002d7588;
 case UINT32_C(0x002d758c):goto L_002d758c;
 case UINT32_C(0x002d7590):goto L_002d7590;
 case UINT32_C(0x002d7594):goto L_002d7594;
 case UINT32_C(0x002d7598):goto L_002d7598;
 case UINT32_C(0x002d759c):goto L_002d759c;
 case UINT32_C(0x002d75a0):goto L_002d75a0;
 case UINT32_C(0x002d75a4):goto L_002d75a4;
 case UINT32_C(0x002d75a8):goto L_002d75a8;
 case UINT32_C(0x002d75ac):goto L_002d75ac;
 case UINT32_C(0x002d75b0):goto L_002d75b0;
 case UINT32_C(0x002d75b4):goto L_002d75b4;
 case UINT32_C(0x002d75b8):goto L_002d75b8;
 case UINT32_C(0x002d75bc):goto L_002d75bc;
 case UINT32_C(0x002d75c0):goto L_002d75c0;
 case UINT32_C(0x002d75c4):goto L_002d75c4;
 case UINT32_C(0x002d75c8):goto L_002d75c8;
 case UINT32_C(0x002d75cc):goto L_002d75cc;
 case UINT32_C(0x002d75d0):goto L_002d75d0;
 case UINT32_C(0x002d75d4):goto L_002d75d4;
 case UINT32_C(0x002d75d8):goto L_002d75d8;
 case UINT32_C(0x002d75dc):goto L_002d75dc;
 case UINT32_C(0x002d75e0):goto L_002d75e0;
 case UINT32_C(0x002d75e4):goto L_002d75e4;
 case UINT32_C(0x002d75e8):goto L_002d75e8;
 case UINT32_C(0x002d75ec):goto L_002d75ec;
 case UINT32_C(0x002d75f0):goto L_002d75f0;
 case UINT32_C(0x002d75f4):goto L_002d75f4;
 case UINT32_C(0x002d75f8):goto L_002d75f8;
 case UINT32_C(0x002d75fc):goto L_002d75fc;
 case UINT32_C(0x002d7600):goto L_002d7600;
 case UINT32_C(0x002d7604):goto L_002d7604;
 case UINT32_C(0x002d7608):goto L_002d7608;
 case UINT32_C(0x002d760c):goto L_002d760c;
 case UINT32_C(0x002d7610):goto L_002d7610;
 case UINT32_C(0x002d7614):goto L_002d7614;
 case UINT32_C(0x002d7618):goto L_002d7618;
 case UINT32_C(0x002d761c):goto L_002d761c;
 case UINT32_C(0x002d7620):goto L_002d7620;
 case UINT32_C(0x002d7624):goto L_002d7624;
 case UINT32_C(0x002d7628):goto L_002d7628;
 case UINT32_C(0x002d762c):goto L_002d762c;
 case UINT32_C(0x002d7630):goto L_002d7630;
 case UINT32_C(0x002d7634):goto L_002d7634;
 case UINT32_C(0x002d7638):goto L_002d7638;
 case UINT32_C(0x002d763c):goto L_002d763c;
 case UINT32_C(0x002d7640):goto L_002d7640;
 case UINT32_C(0x002d7644):goto L_002d7644;
 case UINT32_C(0x002d7648):goto L_002d7648;
 case UINT32_C(0x002d764c):goto L_002d764c;
 case UINT32_C(0x002d7650):goto L_002d7650;
 case UINT32_C(0x002d7654):goto L_002d7654;
 case UINT32_C(0x002d7658):goto L_002d7658;
 case UINT32_C(0x002d765c):goto L_002d765c;
 case UINT32_C(0x002d7660):goto L_002d7660;
 case UINT32_C(0x002d7664):goto L_002d7664;
 case UINT32_C(0x002d7668):goto L_002d7668;
 case UINT32_C(0x002d766c):goto L_002d766c;
 case UINT32_C(0x002d7670):goto L_002d7670;
 case UINT32_C(0x002d7674):goto L_002d7674;
 case UINT32_C(0x002d7678):goto L_002d7678;
 case UINT32_C(0x002d767c):goto L_002d767c;
 case UINT32_C(0x002d7680):goto L_002d7680;
 case UINT32_C(0x002d7684):goto L_002d7684;
 case UINT32_C(0x002d7688):goto L_002d7688;
 case UINT32_C(0x002d768c):goto L_002d768c;
 case UINT32_C(0x002d7690):goto L_002d7690;
 case UINT32_C(0x002d7694):goto L_002d7694;
 case UINT32_C(0x002d7698):goto L_002d7698;
 case UINT32_C(0x002d769c):goto L_002d769c;
 case UINT32_C(0x002d76a0):goto L_002d76a0;
 case UINT32_C(0x002d76a4):goto L_002d76a4;
 case UINT32_C(0x002d76a8):goto L_002d76a8;
 case UINT32_C(0x002d76ac):goto L_002d76ac;
 case UINT32_C(0x002d76b0):goto L_002d76b0;
 case UINT32_C(0x002d76b4):goto L_002d76b4;
 case UINT32_C(0x002d76b8):goto L_002d76b8;
 case UINT32_C(0x002d76bc):goto L_002d76bc;
 case UINT32_C(0x002d76c0):goto L_002d76c0;
 case UINT32_C(0x002d76c4):goto L_002d76c4;
 case UINT32_C(0x002d76c8):goto L_002d76c8;
 case UINT32_C(0x002d76cc):goto L_002d76cc;
 case UINT32_C(0x002d76d0):goto L_002d76d0;
 case UINT32_C(0x002d76d4):goto L_002d76d4;
 case UINT32_C(0x002d76d8):goto L_002d76d8;
 case UINT32_C(0x002d76dc):goto L_002d76dc;
 case UINT32_C(0x002d76e0):goto L_002d76e0;
 case UINT32_C(0x002d76e4):goto L_002d76e4;
 case UINT32_C(0x002d76e8):goto L_002d76e8;
 case UINT32_C(0x002d76ec):goto L_002d76ec;
 case UINT32_C(0x002d76f0):goto L_002d76f0;
 case UINT32_C(0x002d76f4):goto L_002d76f4;
 case UINT32_C(0x002d76f8):goto L_002d76f8;
 case UINT32_C(0x002d76fc):goto L_002d76fc;
 case UINT32_C(0x002d7700):goto L_002d7700;
 case UINT32_C(0x002d7704):goto L_002d7704;
 case UINT32_C(0x002d7708):goto L_002d7708;
 case UINT32_C(0x002d770c):goto L_002d770c;
 case UINT32_C(0x002d7710):goto L_002d7710;
 case UINT32_C(0x002d7714):goto L_002d7714;
 case UINT32_C(0x002d7718):goto L_002d7718;
 case UINT32_C(0x002d771c):goto L_002d771c;
 case UINT32_C(0x002d7720):goto L_002d7720;
 case UINT32_C(0x002d7724):goto L_002d7724;
 case UINT32_C(0x002d7728):goto L_002d7728;
 case UINT32_C(0x002d772c):goto L_002d772c;
 case UINT32_C(0x002d7730):goto L_002d7730;
 case UINT32_C(0x002d7734):goto L_002d7734;
 case UINT32_C(0x002d7738):goto L_002d7738;
 case UINT32_C(0x002d773c):goto L_002d773c;
 case UINT32_C(0x002d7740):goto L_002d7740;
 case UINT32_C(0x002d7744):goto L_002d7744;
 case UINT32_C(0x002d7748):goto L_002d7748;
 case UINT32_C(0x002d774c):goto L_002d774c;
 case UINT32_C(0x002d7750):goto L_002d7750;
 case UINT32_C(0x002d7754):goto L_002d7754;
 case UINT32_C(0x002d7758):goto L_002d7758;
 case UINT32_C(0x002d775c):goto L_002d775c;
 case UINT32_C(0x002d7760):goto L_002d7760;
 case UINT32_C(0x002d7764):goto L_002d7764;
 case UINT32_C(0x002d7768):goto L_002d7768;
 case UINT32_C(0x002d776c):goto L_002d776c;
 case UINT32_C(0x002d7770):goto L_002d7770;
 case UINT32_C(0x002d7774):goto L_002d7774;
 case UINT32_C(0x002d7778):goto L_002d7778;
 case UINT32_C(0x002d777c):goto L_002d777c;
 case UINT32_C(0x002d7780):goto L_002d7780;
 case UINT32_C(0x002d7784):goto L_002d7784;
 case UINT32_C(0x002d7788):goto L_002d7788;
 case UINT32_C(0x002d778c):goto L_002d778c;
 case UINT32_C(0x002d7790):goto L_002d7790;
 case UINT32_C(0x002d7794):goto L_002d7794;
 case UINT32_C(0x002d7798):goto L_002d7798;
 case UINT32_C(0x002d779c):goto L_002d779c;
 case UINT32_C(0x002d77a0):goto L_002d77a0;
 case UINT32_C(0x002d77a4):goto L_002d77a4;
 case UINT32_C(0x002d77a8):goto L_002d77a8;
 case UINT32_C(0x002d77ac):goto L_002d77ac;
 case UINT32_C(0x002d77b0):goto L_002d77b0;
 case UINT32_C(0x002d77b4):goto L_002d77b4;
 case UINT32_C(0x002d77b8):goto L_002d77b8;
 case UINT32_C(0x002d77bc):goto L_002d77bc;
 case UINT32_C(0x002d77c0):goto L_002d77c0;
 case UINT32_C(0x002d77c4):goto L_002d77c4;
 case UINT32_C(0x002d77c8):goto L_002d77c8;
 case UINT32_C(0x002d77cc):goto L_002d77cc;
 case UINT32_C(0x002d77d0):goto L_002d77d0;
 case UINT32_C(0x002d77d4):goto L_002d77d4;
 case UINT32_C(0x002d77d8):goto L_002d77d8;
 case UINT32_C(0x002d77dc):goto L_002d77dc;
 case UINT32_C(0x002d77e0):goto L_002d77e0;
 case UINT32_C(0x002d77e4):goto L_002d77e4;
 case UINT32_C(0x002d77e8):goto L_002d77e8;
 case UINT32_C(0x002d77ec):goto L_002d77ec;
 case UINT32_C(0x002d77f0):goto L_002d77f0;
 case UINT32_C(0x002d77f4):goto L_002d77f4;
 case UINT32_C(0x002d77f8):goto L_002d77f8;
 case UINT32_C(0x002d77fc):goto L_002d77fc;
 case UINT32_C(0x002d7800):goto L_002d7800;
 case UINT32_C(0x002d7804):goto L_002d7804;
 case UINT32_C(0x002d7808):goto L_002d7808;
 case UINT32_C(0x002d780c):goto L_002d780c;
 case UINT32_C(0x002d7810):goto L_002d7810;
 case UINT32_C(0x002d7814):goto L_002d7814;
 case UINT32_C(0x002d7818):goto L_002d7818;
 case UINT32_C(0x002d781c):goto L_002d781c;
 case UINT32_C(0x002d7820):goto L_002d7820;
 case UINT32_C(0x002d7824):goto L_002d7824;
 case UINT32_C(0x002d7828):goto L_002d7828;
 case UINT32_C(0x002d782c):goto L_002d782c;
 case UINT32_C(0x002d7830):goto L_002d7830;
 case UINT32_C(0x002d7834):goto L_002d7834;
 case UINT32_C(0x002d7838):goto L_002d7838;
 case UINT32_C(0x002d783c):goto L_002d783c;
 case UINT32_C(0x002d7840):goto L_002d7840;
 case UINT32_C(0x002d7844):goto L_002d7844;
 case UINT32_C(0x002d7848):goto L_002d7848;
 case UINT32_C(0x002d784c):goto L_002d784c;
 case UINT32_C(0x002d7850):goto L_002d7850;
 case UINT32_C(0x002d7854):goto L_002d7854;
 case UINT32_C(0x002d7858):goto L_002d7858;
 case UINT32_C(0x002d785c):goto L_002d785c;
 case UINT32_C(0x002d7860):goto L_002d7860;
 case UINT32_C(0x002d7864):goto L_002d7864;
 case UINT32_C(0x002d7868):goto L_002d7868;
 case UINT32_C(0x002d786c):goto L_002d786c;
 case UINT32_C(0x002d7870):goto L_002d7870;
 case UINT32_C(0x002d7874):goto L_002d7874;
 case UINT32_C(0x002d7878):goto L_002d7878;
 case UINT32_C(0x002d787c):goto L_002d787c;
 case UINT32_C(0x002d7880):goto L_002d7880;
 case UINT32_C(0x002d7884):goto L_002d7884;
 case UINT32_C(0x002d7888):goto L_002d7888;
 case UINT32_C(0x002d788c):goto L_002d788c;
 case UINT32_C(0x002d7890):goto L_002d7890;
 case UINT32_C(0x002d7894):goto L_002d7894;
 case UINT32_C(0x002d7898):goto L_002d7898;
 case UINT32_C(0x002d789c):goto L_002d789c;
 case UINT32_C(0x002d78a0):goto L_002d78a0;
 case UINT32_C(0x002d78a4):goto L_002d78a4;
 case UINT32_C(0x002d78a8):goto L_002d78a8;
 case UINT32_C(0x002d78ac):goto L_002d78ac;
 case UINT32_C(0x002d78b0):goto L_002d78b0;
 case UINT32_C(0x002d78b4):goto L_002d78b4;
 case UINT32_C(0x002d78b8):goto L_002d78b8;
 case UINT32_C(0x002d78bc):goto L_002d78bc;
 case UINT32_C(0x002d78c0):goto L_002d78c0;
 case UINT32_C(0x002d78c4):goto L_002d78c4;
 case UINT32_C(0x002d78c8):goto L_002d78c8;
 case UINT32_C(0x002d78cc):goto L_002d78cc;
 case UINT32_C(0x002d78d0):goto L_002d78d0;
 case UINT32_C(0x002d78d4):goto L_002d78d4;
 case UINT32_C(0x002d78d8):goto L_002d78d8;
 case UINT32_C(0x002d78dc):goto L_002d78dc;
 case UINT32_C(0x002d78e0):goto L_002d78e0;
 case UINT32_C(0x002d78e4):goto L_002d78e4;
 case UINT32_C(0x002d78e8):goto L_002d78e8;
 case UINT32_C(0x002d78ec):goto L_002d78ec;
 case UINT32_C(0x002d78f0):goto L_002d78f0;
 case UINT32_C(0x002d78f4):goto L_002d78f4;
 case UINT32_C(0x002d78f8):goto L_002d78f8;
 case UINT32_C(0x002d78fc):goto L_002d78fc;
 case UINT32_C(0x002d7900):goto L_002d7900;
 case UINT32_C(0x002d7904):goto L_002d7904;
 case UINT32_C(0x002d7908):goto L_002d7908;
 case UINT32_C(0x002d790c):goto L_002d790c;
 case UINT32_C(0x002d7910):goto L_002d7910;
 case UINT32_C(0x002d7914):goto L_002d7914;
 case UINT32_C(0x002d7918):goto L_002d7918;
 case UINT32_C(0x002d791c):goto L_002d791c;
 case UINT32_C(0x002d7920):goto L_002d7920;
 case UINT32_C(0x002d7924):goto L_002d7924;
 case UINT32_C(0x002d7928):goto L_002d7928;
 case UINT32_C(0x002d792c):goto L_002d792c;
 case UINT32_C(0x002d7930):goto L_002d7930;
 case UINT32_C(0x002d7934):goto L_002d7934;
 case UINT32_C(0x002d7938):goto L_002d7938;
 case UINT32_C(0x002d793c):goto L_002d793c;
 case UINT32_C(0x002d7940):goto L_002d7940;
 case UINT32_C(0x002d7944):goto L_002d7944;
 case UINT32_C(0x002d7948):goto L_002d7948;
 case UINT32_C(0x002d794c):goto L_002d794c;
 case UINT32_C(0x002d7950):goto L_002d7950;
 case UINT32_C(0x002d7954):goto L_002d7954;
 case UINT32_C(0x002d7958):goto L_002d7958;
 case UINT32_C(0x002d795c):goto L_002d795c;
 case UINT32_C(0x002d7960):goto L_002d7960;
 case UINT32_C(0x002d7964):goto L_002d7964;
 case UINT32_C(0x002d7968):goto L_002d7968;
 case UINT32_C(0x002d796c):goto L_002d796c;
 case UINT32_C(0x002d7970):goto L_002d7970;
 case UINT32_C(0x002d7974):goto L_002d7974;
 case UINT32_C(0x002d7978):goto L_002d7978;
 case UINT32_C(0x002d797c):goto L_002d797c;
 case UINT32_C(0x002d7980):goto L_002d7980;
 case UINT32_C(0x002d7984):goto L_002d7984;
 case UINT32_C(0x002d7988):goto L_002d7988;
 case UINT32_C(0x002d798c):goto L_002d798c;
 case UINT32_C(0x002d7990):goto L_002d7990;
 case UINT32_C(0x002d7994):goto L_002d7994;
 case UINT32_C(0x002d7998):goto L_002d7998;
 case UINT32_C(0x002d799c):goto L_002d799c;
 case UINT32_C(0x002d79a0):goto L_002d79a0;
 case UINT32_C(0x002d79a4):goto L_002d79a4;
 case UINT32_C(0x002d79a8):goto L_002d79a8;
 case UINT32_C(0x002d79ac):goto L_002d79ac;
 case UINT32_C(0x002d79b0):goto L_002d79b0;
 case UINT32_C(0x002d79b4):goto L_002d79b4;
 case UINT32_C(0x002d79b8):goto L_002d79b8;
 case UINT32_C(0x002d79bc):goto L_002d79bc;
 case UINT32_C(0x002d79c0):goto L_002d79c0;
 case UINT32_C(0x002d79c4):goto L_002d79c4;
 case UINT32_C(0x002d79c8):goto L_002d79c8;
 case UINT32_C(0x002d79cc):goto L_002d79cc;
 case UINT32_C(0x002d79d0):goto L_002d79d0;
 case UINT32_C(0x002d79d4):goto L_002d79d4;
 case UINT32_C(0x002d79d8):goto L_002d79d8;
 case UINT32_C(0x002d79dc):goto L_002d79dc;
 case UINT32_C(0x002d79e0):goto L_002d79e0;
 case UINT32_C(0x002d79e4):goto L_002d79e4;
 case UINT32_C(0x002d79e8):goto L_002d79e8;
 case UINT32_C(0x002d79ec):goto L_002d79ec;
 case UINT32_C(0x002d79f0):goto L_002d79f0;
 case UINT32_C(0x002d79f4):goto L_002d79f4;
 case UINT32_C(0x002d79f8):goto L_002d79f8;
 case UINT32_C(0x002d79fc):goto L_002d79fc;
 case UINT32_C(0x002d7a00):goto L_002d7a00;
 case UINT32_C(0x002d7a04):goto L_002d7a04;
 case UINT32_C(0x002d7a08):goto L_002d7a08;
 case UINT32_C(0x002d7a0c):goto L_002d7a0c;
 case UINT32_C(0x002d7a10):goto L_002d7a10;
 case UINT32_C(0x002d7a14):goto L_002d7a14;
 case UINT32_C(0x002d7a18):goto L_002d7a18;
 case UINT32_C(0x002d7a1c):goto L_002d7a1c;
 case UINT32_C(0x002d7a20):goto L_002d7a20;
 case UINT32_C(0x002d7a24):goto L_002d7a24;
 case UINT32_C(0x002d7a28):goto L_002d7a28;
 case UINT32_C(0x002d7a2c):goto L_002d7a2c;
 case UINT32_C(0x002d7a30):goto L_002d7a30;
 case UINT32_C(0x002d7a34):goto L_002d7a34;
 case UINT32_C(0x002d7a38):goto L_002d7a38;
 case UINT32_C(0x002d7a3c):goto L_002d7a3c;
 case UINT32_C(0x002d7a40):goto L_002d7a40;
 case UINT32_C(0x002d7a44):goto L_002d7a44;
 case UINT32_C(0x002d7a48):goto L_002d7a48;
 case UINT32_C(0x002d7a4c):goto L_002d7a4c;
 case UINT32_C(0x002d7a50):goto L_002d7a50;
 case UINT32_C(0x002d7a54):goto L_002d7a54;
 case UINT32_C(0x002d7a58):goto L_002d7a58;
 case UINT32_C(0x002d7a5c):goto L_002d7a5c;
 case UINT32_C(0x002d7a60):goto L_002d7a60;
 case UINT32_C(0x002d7a64):goto L_002d7a64;
 case UINT32_C(0x002d7a68):goto L_002d7a68;
 case UINT32_C(0x002d7a6c):goto L_002d7a6c;
 case UINT32_C(0x002d7a70):goto L_002d7a70;
 case UINT32_C(0x002d7a74):goto L_002d7a74;
 case UINT32_C(0x002d7a78):goto L_002d7a78;
 case UINT32_C(0x002d7a7c):goto L_002d7a7c;
 case UINT32_C(0x002d7a80):goto L_002d7a80;
 case UINT32_C(0x002d7a84):goto L_002d7a84;
 case UINT32_C(0x002d7a88):goto L_002d7a88;
 case UINT32_C(0x002d7a8c):goto L_002d7a8c;
 case UINT32_C(0x002d7a90):goto L_002d7a90;
 case UINT32_C(0x002d7a94):goto L_002d7a94;
 case UINT32_C(0x002d7a98):goto L_002d7a98;
 case UINT32_C(0x002d7a9c):goto L_002d7a9c;
 case UINT32_C(0x002d7aa0):goto L_002d7aa0;
 case UINT32_C(0x002d7aa4):goto L_002d7aa4;
 case UINT32_C(0x002d7aa8):goto L_002d7aa8;
 case UINT32_C(0x002d7aac):goto L_002d7aac;
 case UINT32_C(0x002d7ab0):goto L_002d7ab0;
 case UINT32_C(0x002d7ab4):goto L_002d7ab4;
 case UINT32_C(0x002d7ab8):goto L_002d7ab8;
 case UINT32_C(0x002d7abc):goto L_002d7abc;
 case UINT32_C(0x002d7ac0):goto L_002d7ac0;
 case UINT32_C(0x002d7ac4):goto L_002d7ac4;
 case UINT32_C(0x002d7ac8):goto L_002d7ac8;
 case UINT32_C(0x002d7acc):goto L_002d7acc;
 case UINT32_C(0x002d7ad0):goto L_002d7ad0;
 case UINT32_C(0x002d7ad4):goto L_002d7ad4;
 case UINT32_C(0x002d7ad8):goto L_002d7ad8;
 case UINT32_C(0x002d7adc):goto L_002d7adc;
 case UINT32_C(0x002d7ae0):goto L_002d7ae0;
 case UINT32_C(0x002d7ae4):goto L_002d7ae4;
 case UINT32_C(0x002d7ae8):goto L_002d7ae8;
 case UINT32_C(0x002d7aec):goto L_002d7aec;
 case UINT32_C(0x002d7af0):goto L_002d7af0;
 case UINT32_C(0x002d7af4):goto L_002d7af4;
 case UINT32_C(0x002d7af8):goto L_002d7af8;
 case UINT32_C(0x002d7afc):goto L_002d7afc;
 case UINT32_C(0x002d7b00):goto L_002d7b00;
 case UINT32_C(0x002d7b04):goto L_002d7b04;
 case UINT32_C(0x002d7b08):goto L_002d7b08;
 case UINT32_C(0x002d7b0c):goto L_002d7b0c;
 case UINT32_C(0x002d7b10):goto L_002d7b10;
 case UINT32_C(0x002d7b14):goto L_002d7b14;
 case UINT32_C(0x002d7b18):goto L_002d7b18;
 case UINT32_C(0x002d7b1c):goto L_002d7b1c;
 case UINT32_C(0x002d7b20):goto L_002d7b20;
 case UINT32_C(0x002d7b24):goto L_002d7b24;
 case UINT32_C(0x002d7b28):goto L_002d7b28;
 case UINT32_C(0x002d7b2c):goto L_002d7b2c;
 case UINT32_C(0x002d7b30):goto L_002d7b30;
 case UINT32_C(0x002d7b34):goto L_002d7b34;
 case UINT32_C(0x002d7b38):goto L_002d7b38;
 case UINT32_C(0x002d7b3c):goto L_002d7b3c;
 case UINT32_C(0x002d7b40):goto L_002d7b40;
 case UINT32_C(0x002d7b44):goto L_002d7b44;
 case UINT32_C(0x002d7b48):goto L_002d7b48;
 case UINT32_C(0x002d7b4c):goto L_002d7b4c;
 case UINT32_C(0x002d7b50):goto L_002d7b50;
 case UINT32_C(0x002d7b54):goto L_002d7b54;
 case UINT32_C(0x002d7b58):goto L_002d7b58;
 case UINT32_C(0x002d7b5c):goto L_002d7b5c;
 case UINT32_C(0x002d7b60):goto L_002d7b60;
 case UINT32_C(0x002d7b64):goto L_002d7b64;
 case UINT32_C(0x002d7b68):goto L_002d7b68;
 case UINT32_C(0x002d7b6c):goto L_002d7b6c;
 case UINT32_C(0x002d7b70):goto L_002d7b70;
 case UINT32_C(0x002d7b74):goto L_002d7b74;
 case UINT32_C(0x002d7b78):goto L_002d7b78;
 case UINT32_C(0x002d7b7c):goto L_002d7b7c;
 case UINT32_C(0x002d7b80):goto L_002d7b80;
 case UINT32_C(0x002d7b84):goto L_002d7b84;
 case UINT32_C(0x002d7b88):goto L_002d7b88;
 case UINT32_C(0x002d7b8c):goto L_002d7b8c;
 case UINT32_C(0x002d7b90):goto L_002d7b90;
 case UINT32_C(0x002d7b94):goto L_002d7b94;
 case UINT32_C(0x002d7b98):goto L_002d7b98;
 case UINT32_C(0x002d7b9c):goto L_002d7b9c;
 case UINT32_C(0x002d7ba0):goto L_002d7ba0;
 case UINT32_C(0x002d7ba4):goto L_002d7ba4;
 case UINT32_C(0x002d7ba8):goto L_002d7ba8;
 case UINT32_C(0x002d7bac):goto L_002d7bac;
 case UINT32_C(0x002d7bb0):goto L_002d7bb0;
 case UINT32_C(0x002d7bb4):goto L_002d7bb4;
 case UINT32_C(0x002d7bb8):goto L_002d7bb8;
 case UINT32_C(0x002d7bbc):goto L_002d7bbc;
 case UINT32_C(0x002d7bc0):goto L_002d7bc0;
 case UINT32_C(0x002d7bc4):goto L_002d7bc4;
 case UINT32_C(0x002d7bc8):goto L_002d7bc8;
 case UINT32_C(0x002d7bcc):goto L_002d7bcc;
 case UINT32_C(0x002d7bd0):goto L_002d7bd0;
 case UINT32_C(0x002d7bd4):goto L_002d7bd4;
 case UINT32_C(0x002d7bd8):goto L_002d7bd8;
 case UINT32_C(0x002d7bdc):goto L_002d7bdc;
 case UINT32_C(0x002d7be0):goto L_002d7be0;
 case UINT32_C(0x002d7be4):goto L_002d7be4;
 case UINT32_C(0x002d7be8):goto L_002d7be8;
 case UINT32_C(0x002d7bec):goto L_002d7bec;
 case UINT32_C(0x002d7bf0):goto L_002d7bf0;
 case UINT32_C(0x002d7bf4):goto L_002d7bf4;
 case UINT32_C(0x002d7bf8):goto L_002d7bf8;
 case UINT32_C(0x002d7bfc):goto L_002d7bfc;
 case UINT32_C(0x002d7c00):goto L_002d7c00;
 case UINT32_C(0x002d7c04):goto L_002d7c04;
 case UINT32_C(0x002d7c08):goto L_002d7c08;
 case UINT32_C(0x002d7c0c):goto L_002d7c0c;
 case UINT32_C(0x002d7c10):goto L_002d7c10;
 case UINT32_C(0x002d7c14):goto L_002d7c14;
 case UINT32_C(0x002d7c18):goto L_002d7c18;
 case UINT32_C(0x002d7c1c):goto L_002d7c1c;
 case UINT32_C(0x002d7c20):goto L_002d7c20;
 case UINT32_C(0x002d7c24):goto L_002d7c24;
 case UINT32_C(0x002d7c28):goto L_002d7c28;
 case UINT32_C(0x002d7c2c):goto L_002d7c2c;
 case UINT32_C(0x002d7c30):goto L_002d7c30;
 case UINT32_C(0x002d7c34):goto L_002d7c34;
 case UINT32_C(0x002d7c38):goto L_002d7c38;
 case UINT32_C(0x002d7c3c):goto L_002d7c3c;
 case UINT32_C(0x002d7c40):goto L_002d7c40;
 case UINT32_C(0x002d7c44):goto L_002d7c44;
 case UINT32_C(0x002d7c48):goto L_002d7c48;
 case UINT32_C(0x002d7c4c):goto L_002d7c4c;
 case UINT32_C(0x002d7c50):goto L_002d7c50;
 case UINT32_C(0x002d7c54):goto L_002d7c54;
 case UINT32_C(0x002d7c58):goto L_002d7c58;
 case UINT32_C(0x002d7c5c):goto L_002d7c5c;
 case UINT32_C(0x002d7c60):goto L_002d7c60;
 case UINT32_C(0x002d7c64):goto L_002d7c64;
 case UINT32_C(0x002d7c68):goto L_002d7c68;
 case UINT32_C(0x002d7c6c):goto L_002d7c6c;
 case UINT32_C(0x002d7c70):goto L_002d7c70;
 case UINT32_C(0x002d7c74):goto L_002d7c74;
 case UINT32_C(0x002d7c78):goto L_002d7c78;
 case UINT32_C(0x002d7c7c):goto L_002d7c7c;
 case UINT32_C(0x002d7c80):goto L_002d7c80;
 case UINT32_C(0x002d7c84):goto L_002d7c84;
 case UINT32_C(0x002d7c88):goto L_002d7c88;
 case UINT32_C(0x002d7c8c):goto L_002d7c8c;
 case UINT32_C(0x002d7c90):goto L_002d7c90;
 case UINT32_C(0x002d7c94):goto L_002d7c94;
 case UINT32_C(0x002d7c98):goto L_002d7c98;
 case UINT32_C(0x002d7c9c):goto L_002d7c9c;
 case UINT32_C(0x002d7ca0):goto L_002d7ca0;
 case UINT32_C(0x002d7ca4):goto L_002d7ca4;
 case UINT32_C(0x002d7ca8):goto L_002d7ca8;
 case UINT32_C(0x002d7cac):goto L_002d7cac;
 case UINT32_C(0x002d7cb0):goto L_002d7cb0;
 case UINT32_C(0x002d7cb4):goto L_002d7cb4;
 case UINT32_C(0x002d7cb8):goto L_002d7cb8;
 case UINT32_C(0x002d7cbc):goto L_002d7cbc;
 case UINT32_C(0x002d7cc0):goto L_002d7cc0;
 case UINT32_C(0x002d7cc4):goto L_002d7cc4;
 case UINT32_C(0x002d7cc8):goto L_002d7cc8;
 case UINT32_C(0x002d7ccc):goto L_002d7ccc;
 case UINT32_C(0x002d7cd0):goto L_002d7cd0;
 case UINT32_C(0x002d7cd4):goto L_002d7cd4;
 case UINT32_C(0x002d7cd8):goto L_002d7cd8;
 case UINT32_C(0x002d7cdc):goto L_002d7cdc;
 case UINT32_C(0x002d7ce0):goto L_002d7ce0;
 case UINT32_C(0x002d7ce4):goto L_002d7ce4;
 case UINT32_C(0x002da340):goto L_002da340;
 case UINT32_C(0x002da344):goto L_002da344;
 case UINT32_C(0x002da348):goto L_002da348;
 case UINT32_C(0x002da34c):goto L_002da34c;
 case UINT32_C(0x002da350):goto L_002da350;
 case UINT32_C(0x002da354):goto L_002da354;
 case UINT32_C(0x002da358):goto L_002da358;
 case UINT32_C(0x002da308):goto L_002da308;
 case UINT32_C(0x002da30c):goto L_002da30c;
 case UINT32_C(0x002da310):goto L_002da310;
 case UINT32_C(0x002da4b8):goto L_002da4b8;
 case UINT32_C(0x002da4bc):goto L_002da4bc;
 case UINT32_C(0x002da4c0):goto L_002da4c0;
 case UINT32_C(0x002da4c4):goto L_002da4c4;
 case UINT32_C(0x002da4c8):goto L_002da4c8;
 case UINT32_C(0x002da4cc):goto L_002da4cc;
 case UINT32_C(0x002da4d0):goto L_002da4d0;
 case UINT32_C(0x002da4d4):goto L_002da4d4;
 case UINT32_C(0x002da4d8):goto L_002da4d8;
 case UINT32_C(0x002da4dc):goto L_002da4dc;
 case UINT32_C(0x002da4e0):goto L_002da4e0;
 case UINT32_C(0x002da4e4):goto L_002da4e4;
 case UINT32_C(0x002da4e8):goto L_002da4e8;
 case UINT32_C(0x002d6500):goto L_002d6500;
 case UINT32_C(0x002d6504):goto L_002d6504;
 case UINT32_C(0x002d6508):goto L_002d6508;
 case UINT32_C(0x002d650c):goto L_002d650c;
 case UINT32_C(0x002d6510):goto L_002d6510;
 case UINT32_C(0x002d6514):goto L_002d6514;
 case UINT32_C(0x002d6518):goto L_002d6518;
 case UINT32_C(0x002d651c):goto L_002d651c;
 case UINT32_C(0x002d6520):goto L_002d6520;
 case UINT32_C(0x002d6524):goto L_002d6524;
 case UINT32_C(0x002d6528):goto L_002d6528;
 case UINT32_C(0x002d652c):goto L_002d652c;
 case UINT32_C(0x002d6530):goto L_002d6530;
 case UINT32_C(0x002d6534):goto L_002d6534;
 case UINT32_C(0x002d6538):goto L_002d6538;
 case UINT32_C(0x002d653c):goto L_002d653c;
 case UINT32_C(0x002d6540):goto L_002d6540;
 case UINT32_C(0x002d6544):goto L_002d6544;
 case UINT32_C(0x002d9e00):goto L_002d9e00;
 case UINT32_C(0x002d9e04):goto L_002d9e04;
 case UINT32_C(0x002d9e08):goto L_002d9e08;
 case UINT32_C(0x002d9e0c):goto L_002d9e0c;
 case UINT32_C(0x002d9e10):goto L_002d9e10;
 case UINT32_C(0x002d9e14):goto L_002d9e14;
 case UINT32_C(0x002d9e18):goto L_002d9e18;
 case UINT32_C(0x002d9e1c):goto L_002d9e1c;
 case UINT32_C(0x002d9e20):goto L_002d9e20;
 case UINT32_C(0x002d9e24):goto L_002d9e24;
 case UINT32_C(0x002d9e28):goto L_002d9e28;
 case UINT32_C(0x002d9e2c):goto L_002d9e2c;
 case UINT32_C(0x002d9e30):goto L_002d9e30;
 case UINT32_C(0x002d9e34):goto L_002d9e34;
 case UINT32_C(0x002d9e38):goto L_002d9e38;
 case UINT32_C(0x002d9e3c):goto L_002d9e3c;
 case UINT32_C(0x002d9e40):goto L_002d9e40;
 case UINT32_C(0x002d9e44):goto L_002d9e44;
 case UINT32_C(0x002d9e48):goto L_002d9e48;
 case UINT32_C(0x002d9e4c):goto L_002d9e4c;
 case UINT32_C(0x002d9e50):goto L_002d9e50;
 case UINT32_C(0x002d9e54):goto L_002d9e54;
 case UINT32_C(0x002d9e58):goto L_002d9e58;
 case UINT32_C(0x002d9e5c):goto L_002d9e5c;
 case UINT32_C(0x002d9e60):goto L_002d9e60;
 case UINT32_C(0x002d9e64):goto L_002d9e64;
 case UINT32_C(0x002d9e68):goto L_002d9e68;
 case UINT32_C(0x002d9e6c):goto L_002d9e6c;
 case UINT32_C(0x002d9e70):goto L_002d9e70;
 case UINT32_C(0x002d9e74):goto L_002d9e74;
 case UINT32_C(0x002d9e78):goto L_002d9e78;
 case UINT32_C(0x002d9e7c):goto L_002d9e7c;
 case UINT32_C(0x002d9e80):goto L_002d9e80;
 case UINT32_C(0x002d9e84):goto L_002d9e84;
 case UINT32_C(0x002d9e88):goto L_002d9e88;
 case UINT32_C(0x002d9e8c):goto L_002d9e8c;
 case UINT32_C(0x002d9e90):goto L_002d9e90;
 case UINT32_C(0x002d9e94):goto L_002d9e94;
 case UINT32_C(0x002d9e98):goto L_002d9e98;
 case UINT32_C(0x002d9e9c):goto L_002d9e9c;
 case UINT32_C(0x002d9ea0):goto L_002d9ea0;
 case UINT32_C(0x002d9ea4):goto L_002d9ea4;
 case UINT32_C(0x002d9ea8):goto L_002d9ea8;
 case UINT32_C(0x002d9eac):goto L_002d9eac;
 case UINT32_C(0x002d9eb0):goto L_002d9eb0;
 case UINT32_C(0x002d9eb4):goto L_002d9eb4;
 case UINT32_C(0x002d9eb8):goto L_002d9eb8;
 case UINT32_C(0x002d9ebc):goto L_002d9ebc;
 case UINT32_C(0x002d9ec0):goto L_002d9ec0;
 case UINT32_C(0x002d9ec4):goto L_002d9ec4;
 case UINT32_C(0x002d9ec8):goto L_002d9ec8;
 case UINT32_C(0x002d9ecc):goto L_002d9ecc;
 case UINT32_C(0x002d9ed0):goto L_002d9ed0;
 case UINT32_C(0x002d9ed4):goto L_002d9ed4;
 case UINT32_C(0x002d9ed8):goto L_002d9ed8;
 case UINT32_C(0x002d9edc):goto L_002d9edc;
 case UINT32_C(0x002d9ee0):goto L_002d9ee0;
 case UINT32_C(0x002d9ee4):goto L_002d9ee4;
 case UINT32_C(0x002d9ee8):goto L_002d9ee8;
 case UINT32_C(0x002d9eec):goto L_002d9eec;
 case UINT32_C(0x002d9ef0):goto L_002d9ef0;
 case UINT32_C(0x002d9ef4):goto L_002d9ef4;
 case UINT32_C(0x002d9ef8):goto L_002d9ef8;
 case UINT32_C(0x002d9efc):goto L_002d9efc;
 case UINT32_C(0x002d9f00):goto L_002d9f00;
 case UINT32_C(0x002d9f04):goto L_002d9f04;
 case UINT32_C(0x002d9f08):goto L_002d9f08;
 case UINT32_C(0x002d9f0c):goto L_002d9f0c;
 case UINT32_C(0x002d9f10):goto L_002d9f10;
 case UINT32_C(0x002d9f14):goto L_002d9f14;
 case UINT32_C(0x002d9f18):goto L_002d9f18;
 case UINT32_C(0x002d9f1c):goto L_002d9f1c;
 case UINT32_C(0x002d9f20):goto L_002d9f20;
 case UINT32_C(0x002d9f24):goto L_002d9f24;
 case UINT32_C(0x002d9f28):goto L_002d9f28;
 case UINT32_C(0x002d9f2c):goto L_002d9f2c;
 case UINT32_C(0x002d9f30):goto L_002d9f30;
 case UINT32_C(0x002d9f34):goto L_002d9f34;
 case UINT32_C(0x002d9f38):goto L_002d9f38;
 case UINT32_C(0x002d9f3c):goto L_002d9f3c;
 case UINT32_C(0x002d9f40):goto L_002d9f40;
 case UINT32_C(0x002d9f44):goto L_002d9f44;
 case UINT32_C(0x002d9f48):goto L_002d9f48;
 case UINT32_C(0x002d9f4c):goto L_002d9f4c;
 case UINT32_C(0x002d9f50):goto L_002d9f50;
 case UINT32_C(0x002d9f54):goto L_002d9f54;
 case UINT32_C(0x002d9f58):goto L_002d9f58;
 case UINT32_C(0x002d9f5c):goto L_002d9f5c;
 case UINT32_C(0x002d9f60):goto L_002d9f60;
 case UINT32_C(0x002d9f64):goto L_002d9f64;
 case UINT32_C(0x002d9f68):goto L_002d9f68;
 case UINT32_C(0x002d9f6c):goto L_002d9f6c;
 case UINT32_C(0x002d9f70):goto L_002d9f70;
 case UINT32_C(0x002d9f74):goto L_002d9f74;
 case UINT32_C(0x002d9f78):goto L_002d9f78;
 case UINT32_C(0x002d9f7c):goto L_002d9f7c;
 case UINT32_C(0x002d9f80):goto L_002d9f80;
 case UINT32_C(0x002d9f84):goto L_002d9f84;
 case UINT32_C(0x002d9f88):goto L_002d9f88;
 case UINT32_C(0x002d9f8c):goto L_002d9f8c;
 case UINT32_C(0x002d9f90):goto L_002d9f90;
 case UINT32_C(0x002d9f94):goto L_002d9f94;
 case UINT32_C(0x002d9f98):goto L_002d9f98;
 case UINT32_C(0x002d9f9c):goto L_002d9f9c;
 case UINT32_C(0x002d9fa0):goto L_002d9fa0;
 case UINT32_C(0x002d9fa4):goto L_002d9fa4;
 case UINT32_C(0x002d9fa8):goto L_002d9fa8;
 case UINT32_C(0x002d9fac):goto L_002d9fac;
 case UINT32_C(0x002d9fb0):goto L_002d9fb0;
 case UINT32_C(0x002d9fb4):goto L_002d9fb4;
 case UINT32_C(0x002d9fb8):goto L_002d9fb8;
 case UINT32_C(0x002d9fbc):goto L_002d9fbc;
 case UINT32_C(0x002d9fc0):goto L_002d9fc0;
 case UINT32_C(0x002d9fc4):goto L_002d9fc4;
 case UINT32_C(0x002d9fc8):goto L_002d9fc8;
 case UINT32_C(0x002d9fcc):goto L_002d9fcc;
 case UINT32_C(0x002d9fd0):goto L_002d9fd0;
 case UINT32_C(0x002d9fd4):goto L_002d9fd4;
 case UINT32_C(0x002d9fd8):goto L_002d9fd8;
 case UINT32_C(0x002d9fdc):goto L_002d9fdc;
 case UINT32_C(0x002d9fe0):goto L_002d9fe0;
 case UINT32_C(0x002d9fe4):goto L_002d9fe4;
 case UINT32_C(0x002d9fe8):goto L_002d9fe8;
 case UINT32_C(0x002d9fec):goto L_002d9fec;
 case UINT32_C(0x002d9ff0):goto L_002d9ff0;
 case UINT32_C(0x002d9ff4):goto L_002d9ff4;
 case UINT32_C(0x002d9ff8):goto L_002d9ff8;
 case UINT32_C(0x002d9ffc):goto L_002d9ffc;
 case UINT32_C(0x002da000):goto L_002da000;
 case UINT32_C(0x002da004):goto L_002da004;
 case UINT32_C(0x002da008):goto L_002da008;
 case UINT32_C(0x002da00c):goto L_002da00c;
 case UINT32_C(0x002da010):goto L_002da010;
 case UINT32_C(0x002da014):goto L_002da014;
 case UINT32_C(0x002da018):goto L_002da018;
 case UINT32_C(0x002da01c):goto L_002da01c;
 case UINT32_C(0x002da020):goto L_002da020;
 case UINT32_C(0x002da024):goto L_002da024;
 case UINT32_C(0x002da028):goto L_002da028;
 case UINT32_C(0x002da02c):goto L_002da02c;
 case UINT32_C(0x002da030):goto L_002da030;
 case UINT32_C(0x002da034):goto L_002da034;
 case UINT32_C(0x002da038):goto L_002da038;
 case UINT32_C(0x002da03c):goto L_002da03c;
 case UINT32_C(0x002da040):goto L_002da040;
 case UINT32_C(0x002da044):goto L_002da044;
 case UINT32_C(0x002da048):goto L_002da048;
 case UINT32_C(0x002da04c):goto L_002da04c;
 case UINT32_C(0x002da050):goto L_002da050;
 case UINT32_C(0x002da054):goto L_002da054;
 case UINT32_C(0x002da058):goto L_002da058;
 case UINT32_C(0x002da05c):goto L_002da05c;
 case UINT32_C(0x002da060):goto L_002da060;
 case UINT32_C(0x002da064):goto L_002da064;
 case UINT32_C(0x002da068):goto L_002da068;
 case UINT32_C(0x002da06c):goto L_002da06c;
 case UINT32_C(0x002da070):goto L_002da070;
 case UINT32_C(0x002da074):goto L_002da074;
 case UINT32_C(0x002da078):goto L_002da078;
 case UINT32_C(0x002da07c):goto L_002da07c;
 case UINT32_C(0x002da080):goto L_002da080;
 case UINT32_C(0x002da084):goto L_002da084;
 case UINT32_C(0x002da088):goto L_002da088;
 case UINT32_C(0x002da08c):goto L_002da08c;
 case UINT32_C(0x002da090):goto L_002da090;
 case UINT32_C(0x002da094):goto L_002da094;
 case UINT32_C(0x002da098):goto L_002da098;
 case UINT32_C(0x002da09c):goto L_002da09c;
 case UINT32_C(0x002da0a0):goto L_002da0a0;
 case UINT32_C(0x002da0a4):goto L_002da0a4;
 case UINT32_C(0x002da0a8):goto L_002da0a8;
 case UINT32_C(0x002da0ac):goto L_002da0ac;
 case UINT32_C(0x002da0b0):goto L_002da0b0;
 case UINT32_C(0x002da0b4):goto L_002da0b4;
 case UINT32_C(0x002da0b8):goto L_002da0b8;
 case UINT32_C(0x002da0bc):goto L_002da0bc;
 case UINT32_C(0x002da0c0):goto L_002da0c0;
 case UINT32_C(0x002da0c4):goto L_002da0c4;
 case UINT32_C(0x002da0c8):goto L_002da0c8;
 case UINT32_C(0x002da0cc):goto L_002da0cc;
 case UINT32_C(0x002da0d0):goto L_002da0d0;
 case UINT32_C(0x002da0d4):goto L_002da0d4;
 case UINT32_C(0x002da0d8):goto L_002da0d8;
 case UINT32_C(0x002da0dc):goto L_002da0dc;
 case UINT32_C(0x002da0e0):goto L_002da0e0;
 case UINT32_C(0x002da0e4):goto L_002da0e4;
 case UINT32_C(0x002da0e8):goto L_002da0e8;
 case UINT32_C(0x002da0ec):goto L_002da0ec;
 case UINT32_C(0x002da0f0):goto L_002da0f0;
 case UINT32_C(0x002da0f4):goto L_002da0f4;
 case UINT32_C(0x002da0f8):goto L_002da0f8;
 case UINT32_C(0x002da0fc):goto L_002da0fc;
 case UINT32_C(0x002da100):goto L_002da100;
 case UINT32_C(0x002da104):goto L_002da104;
 case UINT32_C(0x002da108):goto L_002da108;
 case UINT32_C(0x002da10c):goto L_002da10c;
 case UINT32_C(0x002da110):goto L_002da110;
 case UINT32_C(0x002da114):goto L_002da114;
 case UINT32_C(0x002da118):goto L_002da118;
 case UINT32_C(0x002da11c):goto L_002da11c;
 case UINT32_C(0x002da120):goto L_002da120;
 case UINT32_C(0x002da124):goto L_002da124;
 case UINT32_C(0x002da128):goto L_002da128;
 case UINT32_C(0x002da12c):goto L_002da12c;
 case UINT32_C(0x002da130):goto L_002da130;
 case UINT32_C(0x002da134):goto L_002da134;
 case UINT32_C(0x002da138):goto L_002da138;
 case UINT32_C(0x002da13c):goto L_002da13c;
 case UINT32_C(0x002da140):goto L_002da140;
 case UINT32_C(0x002da144):goto L_002da144;
 case UINT32_C(0x002da148):goto L_002da148;
 case UINT32_C(0x002da14c):goto L_002da14c;
 case UINT32_C(0x002da150):goto L_002da150;
 case UINT32_C(0x002da154):goto L_002da154;
 case UINT32_C(0x002da158):goto L_002da158;
 case UINT32_C(0x002da15c):goto L_002da15c;
 case UINT32_C(0x002da160):goto L_002da160;
 case UINT32_C(0x002da164):goto L_002da164;
 case UINT32_C(0x002da168):goto L_002da168;
 case UINT32_C(0x002da16c):goto L_002da16c;
 case UINT32_C(0x002da170):goto L_002da170;
 case UINT32_C(0x002da174):goto L_002da174;
 case UINT32_C(0x002da178):goto L_002da178;
 case UINT32_C(0x002da17c):goto L_002da17c;
 case UINT32_C(0x002da180):goto L_002da180;
 case UINT32_C(0x002da184):goto L_002da184;
 case UINT32_C(0x002da188):goto L_002da188;
 case UINT32_C(0x002da18c):goto L_002da18c;
 case UINT32_C(0x002da190):goto L_002da190;
 case UINT32_C(0x002da194):goto L_002da194;
 case UINT32_C(0x002da198):goto L_002da198;
 case UINT32_C(0x002da19c):goto L_002da19c;
 case UINT32_C(0x002da1a0):goto L_002da1a0;
 case UINT32_C(0x002da1a4):goto L_002da1a4;
 case UINT32_C(0x002da1a8):goto L_002da1a8;
 case UINT32_C(0x002da1ac):goto L_002da1ac;
 case UINT32_C(0x002da1b0):goto L_002da1b0;
 case UINT32_C(0x002da1b4):goto L_002da1b4;
 case UINT32_C(0x002da1b8):goto L_002da1b8;
 case UINT32_C(0x002da1bc):goto L_002da1bc;
 case UINT32_C(0x002da1c0):goto L_002da1c0;
 case UINT32_C(0x002da1c4):goto L_002da1c4;
 case UINT32_C(0x002da1c8):goto L_002da1c8;
 case UINT32_C(0x002da1cc):goto L_002da1cc;
 case UINT32_C(0x002da1d0):goto L_002da1d0;
 case UINT32_C(0x002da1d4):goto L_002da1d4;
 case UINT32_C(0x002da1d8):goto L_002da1d8;
 case UINT32_C(0x002da1dc):goto L_002da1dc;
 case UINT32_C(0x002d4454):goto L_002d4454;
 case UINT32_C(0x002d4458):goto L_002d4458;
 case UINT32_C(0x002d445c):goto L_002d445c;
 case UINT32_C(0x002d4460):goto L_002d4460;
 case UINT32_C(0x002d4464):goto L_002d4464;
 case UINT32_C(0x002d4468):goto L_002d4468;
 case UINT32_C(0x002d446c):goto L_002d446c;
 case UINT32_C(0x002d4470):goto L_002d4470;
 case UINT32_C(0x002d4474):goto L_002d4474;
 case UINT32_C(0x002d4478):goto L_002d4478;
 case UINT32_C(0x002d447c):goto L_002d447c;
 case UINT32_C(0x002d4480):goto L_002d4480;
 case UINT32_C(0x002d4484):goto L_002d4484;
 case UINT32_C(0x002d4488):goto L_002d4488;
 case UINT32_C(0x002d448c):goto L_002d448c;
 case UINT32_C(0x002d4490):goto L_002d4490;
 case UINT32_C(0x002d4494):goto L_002d4494;
 case UINT32_C(0x002d4498):goto L_002d4498;
 case UINT32_C(0x002d449c):goto L_002d449c;
 case UINT32_C(0x002d44a0):goto L_002d44a0;
 case UINT32_C(0x002d44a4):goto L_002d44a4;
 case UINT32_C(0x002d44a8):goto L_002d44a8;
 case UINT32_C(0x002d44ac):goto L_002d44ac;
 case UINT32_C(0x002d44b0):goto L_002d44b0;
 case UINT32_C(0x002d44b4):goto L_002d44b4;
 case UINT32_C(0x002d44b8):goto L_002d44b8;
 case UINT32_C(0x002d44bc):goto L_002d44bc;
 case UINT32_C(0x002d44c0):goto L_002d44c0;
 case UINT32_C(0x002d44c4):goto L_002d44c4;
 case UINT32_C(0x002d44c8):goto L_002d44c8;
 case UINT32_C(0x002d44cc):goto L_002d44cc;
 case UINT32_C(0x002d44d0):goto L_002d44d0;
 case UINT32_C(0x002d44d4):goto L_002d44d4;
 case UINT32_C(0x002d44d8):goto L_002d44d8;
 case UINT32_C(0x002d44dc):goto L_002d44dc;
 case UINT32_C(0x002d44e0):goto L_002d44e0;
 case UINT32_C(0x002d44e4):goto L_002d44e4;
 case UINT32_C(0x002d44e8):goto L_002d44e8;
 case UINT32_C(0x002d44ec):goto L_002d44ec;
 case UINT32_C(0x002d44f0):goto L_002d44f0;
 case UINT32_C(0x002d44f4):goto L_002d44f4;
 case UINT32_C(0x002d44f8):goto L_002d44f8;
 case UINT32_C(0x002d44fc):goto L_002d44fc;
 case UINT32_C(0x002d4500):goto L_002d4500;
 case UINT32_C(0x002d4504):goto L_002d4504;
 case UINT32_C(0x002d4508):goto L_002d4508;
 case UINT32_C(0x002d450c):goto L_002d450c;
 case UINT32_C(0x002d4510):goto L_002d4510;
 case UINT32_C(0x002d4514):goto L_002d4514;
 case UINT32_C(0x002d4518):goto L_002d4518;
 case UINT32_C(0x002d451c):goto L_002d451c;
 case UINT32_C(0x002d4520):goto L_002d4520;
 case UINT32_C(0x002d4524):goto L_002d4524;
 case UINT32_C(0x002d4528):goto L_002d4528;
 case UINT32_C(0x002d452c):goto L_002d452c;
 case UINT32_C(0x002d4530):goto L_002d4530;
 case UINT32_C(0x002d4534):goto L_002d4534;
 case UINT32_C(0x002d4538):goto L_002d4538;
 case UINT32_C(0x002d453c):goto L_002d453c;
 case UINT32_C(0x002d4540):goto L_002d4540;
 case UINT32_C(0x002d4544):goto L_002d4544;
 case UINT32_C(0x002d4548):goto L_002d4548;
 case UINT32_C(0x002d454c):goto L_002d454c;
 case UINT32_C(0x002d4550):goto L_002d4550;
 case UINT32_C(0x002d4554):goto L_002d4554;
 case UINT32_C(0x002d8038):goto L_002d8038;
 case UINT32_C(0x002d803c):goto L_002d803c;
 case UINT32_C(0x002d8040):goto L_002d8040;
 case UINT32_C(0x002d8044):goto L_002d8044;
 case UINT32_C(0x002d8048):goto L_002d8048;
 case UINT32_C(0x002d804c):goto L_002d804c;
 case UINT32_C(0x002d8050):goto L_002d8050;
 case UINT32_C(0x002d8054):goto L_002d8054;
 case UINT32_C(0x002d8058):goto L_002d8058;
 case UINT32_C(0x002d805c):goto L_002d805c;
 case UINT32_C(0x002d8060):goto L_002d8060;
 case UINT32_C(0x002d8064):goto L_002d8064;
 case UINT32_C(0x002d8068):goto L_002d8068;
 case UINT32_C(0x002d806c):goto L_002d806c;
 case UINT32_C(0x002d8070):goto L_002d8070;
 case UINT32_C(0x002d8074):goto L_002d8074;
 case UINT32_C(0x002d8078):goto L_002d8078;
 case UINT32_C(0x002d807c):goto L_002d807c;
 case UINT32_C(0x002d8080):goto L_002d8080;
 case UINT32_C(0x002d8084):goto L_002d8084;
 case UINT32_C(0x002d8088):goto L_002d8088;
 case UINT32_C(0x002d808c):goto L_002d808c;
 case UINT32_C(0x002d8090):goto L_002d8090;
 case UINT32_C(0x002d8094):goto L_002d8094;
 case UINT32_C(0x002d8098):goto L_002d8098;
 case UINT32_C(0x002d809c):goto L_002d809c;
 case UINT32_C(0x002d80a0):goto L_002d80a0;
 case UINT32_C(0x002d80a4):goto L_002d80a4;
 case UINT32_C(0x002d80a8):goto L_002d80a8;
 case UINT32_C(0x002d80ac):goto L_002d80ac;
 case UINT32_C(0x002d80b0):goto L_002d80b0;
 case UINT32_C(0x002d80b4):goto L_002d80b4;
 case UINT32_C(0x002d80b8):goto L_002d80b8;
 case UINT32_C(0x002d80bc):goto L_002d80bc;
 case UINT32_C(0x002d80c0):goto L_002d80c0;
 case UINT32_C(0x002d80c4):goto L_002d80c4;
 case UINT32_C(0x002d80c8):goto L_002d80c8;
 case UINT32_C(0x002d80cc):goto L_002d80cc;
 case UINT32_C(0x002d80d0):goto L_002d80d0;
 case UINT32_C(0x002d80d4):goto L_002d80d4;
 case UINT32_C(0x002d80d8):goto L_002d80d8;
 case UINT32_C(0x002d80dc):goto L_002d80dc;
 case UINT32_C(0x002d80e0):goto L_002d80e0;
 case UINT32_C(0x002d80e4):goto L_002d80e4;
 case UINT32_C(0x002d80e8):goto L_002d80e8;
 case UINT32_C(0x002d80ec):goto L_002d80ec;
 case UINT32_C(0x002d80f0):goto L_002d80f0;
 case UINT32_C(0x002d80f4):goto L_002d80f4;
 case UINT32_C(0x002d80f8):goto L_002d80f8;
 case UINT32_C(0x002d80fc):goto L_002d80fc;
 case UINT32_C(0x002d8100):goto L_002d8100;
 case UINT32_C(0x002d8104):goto L_002d8104;
 case UINT32_C(0x002d8108):goto L_002d8108;
 case UINT32_C(0x002d810c):goto L_002d810c;
 case UINT32_C(0x002d8110):goto L_002d8110;
 case UINT32_C(0x002d8114):goto L_002d8114;
 case UINT32_C(0x002d8118):goto L_002d8118;
 case UINT32_C(0x002d811c):goto L_002d811c;
 case UINT32_C(0x002d8120):goto L_002d8120;
 case UINT32_C(0x002d8124):goto L_002d8124;
 case UINT32_C(0x002d8128):goto L_002d8128;
 case UINT32_C(0x002d812c):goto L_002d812c;
 case UINT32_C(0x002d8130):goto L_002d8130;
 case UINT32_C(0x002d8134):goto L_002d8134;
 case UINT32_C(0x002d8138):goto L_002d8138;
 case UINT32_C(0x002d813c):goto L_002d813c;
 case UINT32_C(0x002d8140):goto L_002d8140;
 case UINT32_C(0x002d6548):goto L_002d6548;
 case UINT32_C(0x002d654c):goto L_002d654c;
 case UINT32_C(0x002d6550):goto L_002d6550;
 case UINT32_C(0x002d6554):goto L_002d6554;
 case UINT32_C(0x002d6558):goto L_002d6558;
 case UINT32_C(0x002d655c):goto L_002d655c;
 case UINT32_C(0x002d6560):goto L_002d6560;
 case UINT32_C(0x002d6564):goto L_002d6564;
 case UINT32_C(0x002d6568):goto L_002d6568;
 case UINT32_C(0x002d656c):goto L_002d656c;
 case UINT32_C(0x002d6570):goto L_002d6570;
 case UINT32_C(0x002d6574):goto L_002d6574;
 case UINT32_C(0x002d6578):goto L_002d6578;
 case UINT32_C(0x002d657c):goto L_002d657c;
 case UINT32_C(0x002d6580):goto L_002d6580;
 case UINT32_C(0x002d6584):goto L_002d6584;
 case UINT32_C(0x002d6588):goto L_002d6588;
 case UINT32_C(0x002d658c):goto L_002d658c;
 case UINT32_C(0x002d6590):goto L_002d6590;
 case UINT32_C(0x002d6594):goto L_002d6594;
 case UINT32_C(0x002d6598):goto L_002d6598;
 case UINT32_C(0x002d659c):goto L_002d659c;
 case UINT32_C(0x002d65a0):goto L_002d65a0;
 case UINT32_C(0x002d65a4):goto L_002d65a4;
 case UINT32_C(0x002d65a8):goto L_002d65a8;
 case UINT32_C(0x002d65ac):goto L_002d65ac;
 case UINT32_C(0x002d65b0):goto L_002d65b0;
 case UINT32_C(0x002d65b4):goto L_002d65b4;
 case UINT32_C(0x002d65b8):goto L_002d65b8;
 case UINT32_C(0x002d65bc):goto L_002d65bc;
 case UINT32_C(0x002d65c0):goto L_002d65c0;
 case UINT32_C(0x002d65c4):goto L_002d65c4;
 case UINT32_C(0x002d65c8):goto L_002d65c8;
 case UINT32_C(0x002d65cc):goto L_002d65cc;
 case UINT32_C(0x002d65d0):goto L_002d65d0;
 case UINT32_C(0x002d65d4):goto L_002d65d4;
 case UINT32_C(0x002d65d8):goto L_002d65d8;
 case UINT32_C(0x002d65dc):goto L_002d65dc;
 case UINT32_C(0x002d65e0):goto L_002d65e0;
 case UINT32_C(0x002d65e4):goto L_002d65e4;
 case UINT32_C(0x002d65e8):goto L_002d65e8;
 case UINT32_C(0x002d65ec):goto L_002d65ec;
 case UINT32_C(0x002d65f0):goto L_002d65f0;
 case UINT32_C(0x002d65f4):goto L_002d65f4;
 case UINT32_C(0x002d65f8):goto L_002d65f8;
 case UINT32_C(0x002d95e0):goto L_002d95e0;
 case UINT32_C(0x002d95e4):goto L_002d95e4;
 case UINT32_C(0x002d95e8):goto L_002d95e8;
 case UINT32_C(0x002d95ec):goto L_002d95ec;
 case UINT32_C(0x002d95f0):goto L_002d95f0;
 case UINT32_C(0x002d95f4):goto L_002d95f4;
 case UINT32_C(0x002d95f8):goto L_002d95f8;
 case UINT32_C(0x002d95fc):goto L_002d95fc;
 case UINT32_C(0x002d9600):goto L_002d9600;
 case UINT32_C(0x002d9604):goto L_002d9604;
 case UINT32_C(0x002d9608):goto L_002d9608;
 case UINT32_C(0x002d960c):goto L_002d960c;
 case UINT32_C(0x002d9610):goto L_002d9610;
 case UINT32_C(0x002d9614):goto L_002d9614;
 case UINT32_C(0x002d9618):goto L_002d9618;
 case UINT32_C(0x002d961c):goto L_002d961c;
 case UINT32_C(0x002d9620):goto L_002d9620;
 case UINT32_C(0x002d9624):goto L_002d9624;
 case UINT32_C(0x002d9628):goto L_002d9628;
 case UINT32_C(0x002d962c):goto L_002d962c;
 case UINT32_C(0x002d9630):goto L_002d9630;
 case UINT32_C(0x002d9634):goto L_002d9634;
 case UINT32_C(0x002d9638):goto L_002d9638;
 case UINT32_C(0x002d963c):goto L_002d963c;
 case UINT32_C(0x002d9640):goto L_002d9640;
 case UINT32_C(0x002d9644):goto L_002d9644;
 case UINT32_C(0x002d9648):goto L_002d9648;
 case UINT32_C(0x002d964c):goto L_002d964c;
 case UINT32_C(0x002d9650):goto L_002d9650;
 case UINT32_C(0x002d9654):goto L_002d9654;
 case UINT32_C(0x002d9658):goto L_002d9658;
 case UINT32_C(0x002d965c):goto L_002d965c;
 case UINT32_C(0x002d9660):goto L_002d9660;
 case UINT32_C(0x002d9664):goto L_002d9664;
 case UINT32_C(0x002d9668):goto L_002d9668;
 case UINT32_C(0x002d966c):goto L_002d966c;
 case UINT32_C(0x002d9670):goto L_002d9670;
 case UINT32_C(0x002d9674):goto L_002d9674;
 case UINT32_C(0x002d9678):goto L_002d9678;
 case UINT32_C(0x002d967c):goto L_002d967c;
 case UINT32_C(0x002d9680):goto L_002d9680;
 case UINT32_C(0x002d9684):goto L_002d9684;
 case UINT32_C(0x002d9688):goto L_002d9688;
 case UINT32_C(0x002d968c):goto L_002d968c;
 case UINT32_C(0x002d9690):goto L_002d9690;
 case UINT32_C(0x002d9694):goto L_002d9694;
 case UINT32_C(0x002d9698):goto L_002d9698;
 case UINT32_C(0x002d969c):goto L_002d969c;
 case UINT32_C(0x002d96a0):goto L_002d96a0;
 case UINT32_C(0x002d96a4):goto L_002d96a4;
 case UINT32_C(0x002d96a8):goto L_002d96a8;
 case UINT32_C(0x002d96ac):goto L_002d96ac;
 case UINT32_C(0x002d96b0):goto L_002d96b0;
 case UINT32_C(0x002d96b4):goto L_002d96b4;
 case UINT32_C(0x002d96b8):goto L_002d96b8;
 case UINT32_C(0x002d96bc):goto L_002d96bc;
 case UINT32_C(0x002d96c0):goto L_002d96c0;
 case UINT32_C(0x002d96c4):goto L_002d96c4;
 case UINT32_C(0x002d96c8):goto L_002d96c8;
 case UINT32_C(0x002d96cc):goto L_002d96cc;
 case UINT32_C(0x002d96d0):goto L_002d96d0;
 case UINT32_C(0x002d96d4):goto L_002d96d4;
 case UINT32_C(0x002d96d8):goto L_002d96d8;
 case UINT32_C(0x002d96dc):goto L_002d96dc;
 case UINT32_C(0x002d96e0):goto L_002d96e0;
 case UINT32_C(0x002d96e4):goto L_002d96e4;
 case UINT32_C(0x002d96e8):goto L_002d96e8;
 case UINT32_C(0x002d96ec):goto L_002d96ec;
 case UINT32_C(0x002d96f0):goto L_002d96f0;
 case UINT32_C(0x002da360):goto L_002da360;
 case UINT32_C(0x002da364):goto L_002da364;
 case UINT32_C(0x002da368):goto L_002da368;
 case UINT32_C(0x002da36c):goto L_002da36c;
 case UINT32_C(0x002da370):goto L_002da370;
 case UINT32_C(0x002da374):goto L_002da374;
 case UINT32_C(0x002da378):goto L_002da378;
 case UINT32_C(0x002da37c):goto L_002da37c;
 case UINT32_C(0x002da380):goto L_002da380;
 case UINT32_C(0x002da384):goto L_002da384;
 case UINT32_C(0x002da388):goto L_002da388;
 case UINT32_C(0x002da38c):goto L_002da38c;
 case UINT32_C(0x002da390):goto L_002da390;
 case UINT32_C(0x002da394):goto L_002da394;
 case UINT32_C(0x002da398):goto L_002da398;
 case UINT32_C(0x002da39c):goto L_002da39c;
 case UINT32_C(0x002da3a0):goto L_002da3a0;
 case UINT32_C(0x002da3a4):goto L_002da3a4;
 case UINT32_C(0x002da3a8):goto L_002da3a8;
 case UINT32_C(0x002da3ac):goto L_002da3ac;
 case UINT32_C(0x002da3b0):goto L_002da3b0;
 case UINT32_C(0x002da3b4):goto L_002da3b4;
 case UINT32_C(0x002da3b8):goto L_002da3b8;
 case UINT32_C(0x002da3bc):goto L_002da3bc;
 case UINT32_C(0x002da3c0):goto L_002da3c0;
 case UINT32_C(0x002da3c4):goto L_002da3c4;
 case UINT32_C(0x002da3c8):goto L_002da3c8;
 case UINT32_C(0x002da3cc):goto L_002da3cc;
 case UINT32_C(0x002da3d0):goto L_002da3d0;
 case UINT32_C(0x002da3d4):goto L_002da3d4;
 case UINT32_C(0x002da3d8):goto L_002da3d8;
 case UINT32_C(0x002da3dc):goto L_002da3dc;
 case UINT32_C(0x002da3e0):goto L_002da3e0;
 case UINT32_C(0x002da3e4):goto L_002da3e4;
 case UINT32_C(0x002da3e8):goto L_002da3e8;
 case UINT32_C(0x002da3ec):goto L_002da3ec;
 case UINT32_C(0x002da3f0):goto L_002da3f0;
 case UINT32_C(0x002da3f4):goto L_002da3f4;
 case UINT32_C(0x002da3f8):goto L_002da3f8;
 case UINT32_C(0x002da3fc):goto L_002da3fc;
 case UINT32_C(0x002da400):goto L_002da400;
 case UINT32_C(0x002da404):goto L_002da404;
 case UINT32_C(0x002da408):goto L_002da408;
 case UINT32_C(0x002da40c):goto L_002da40c;
 case UINT32_C(0x002da410):goto L_002da410;
 case UINT32_C(0x002da414):goto L_002da414;
 case UINT32_C(0x002da418):goto L_002da418;
 case UINT32_C(0x002da41c):goto L_002da41c;
 case UINT32_C(0x002da420):goto L_002da420;
 case UINT32_C(0x002da424):goto L_002da424;
 case UINT32_C(0x002da428):goto L_002da428;
 case UINT32_C(0x002da42c):goto L_002da42c;
 case UINT32_C(0x002da430):goto L_002da430;
 case UINT32_C(0x002da434):goto L_002da434;
 case UINT32_C(0x002da438):goto L_002da438;
 case UINT32_C(0x002da43c):goto L_002da43c;
 case UINT32_C(0x002da440):goto L_002da440;
 case UINT32_C(0x002da444):goto L_002da444;
 case UINT32_C(0x002da448):goto L_002da448;
 case UINT32_C(0x002da44c):goto L_002da44c;
 case UINT32_C(0x002da450):goto L_002da450;
 case UINT32_C(0x002da454):goto L_002da454;
 case UINT32_C(0x002da458):goto L_002da458;
 case UINT32_C(0x002da45c):goto L_002da45c;
 case UINT32_C(0x002da460):goto L_002da460;
 case UINT32_C(0x002da464):goto L_002da464;
 case UINT32_C(0x002da468):goto L_002da468;
 case UINT32_C(0x002da46c):goto L_002da46c;
 case UINT32_C(0x002da470):goto L_002da470;
 case UINT32_C(0x002da474):goto L_002da474;
 case UINT32_C(0x002da478):goto L_002da478;
 case UINT32_C(0x002da47c):goto L_002da47c;
 case UINT32_C(0x002da480):goto L_002da480;
 case UINT32_C(0x002da484):goto L_002da484;
 case UINT32_C(0x002da488):goto L_002da488;
 case UINT32_C(0x002da48c):goto L_002da48c;
 case UINT32_C(0x002da490):goto L_002da490;
 case UINT32_C(0x002da494):goto L_002da494;
 case UINT32_C(0x002da498):goto L_002da498;
 case UINT32_C(0x002da49c):goto L_002da49c;
 case UINT32_C(0x002da4a0):goto L_002da4a0;
 case UINT32_C(0x002da4a4):goto L_002da4a4;
 case UINT32_C(0x002da4a8):goto L_002da4a8;
 case UINT32_C(0x002da4ac):goto L_002da4ac;
 case UINT32_C(0x002da4b0):goto L_002da4b0;
 case UINT32_C(0x002db6d8):goto L_002db6d8;
 case UINT32_C(0x002db6dc):goto L_002db6dc;
 case UINT32_C(0x002db6e0):goto L_002db6e0;
 case UINT32_C(0x002db6e4):goto L_002db6e4;
 case UINT32_C(0x002db6e8):goto L_002db6e8;
 case UINT32_C(0x002db6ec):goto L_002db6ec;
 case UINT32_C(0x002db6f0):goto L_002db6f0;
 case UINT32_C(0x002db6f4):goto L_002db6f4;
 case UINT32_C(0x002db6f8):goto L_002db6f8;
 case UINT32_C(0x002db6fc):goto L_002db6fc;
 case UINT32_C(0x002db700):goto L_002db700;
 case UINT32_C(0x002db704):goto L_002db704;
 case UINT32_C(0x002db708):goto L_002db708;
 case UINT32_C(0x002db70c):goto L_002db70c;
 case UINT32_C(0x002db710):goto L_002db710;
 case UINT32_C(0x002db714):goto L_002db714;
 case UINT32_C(0x002db718):goto L_002db718;
 case UINT32_C(0x002db71c):goto L_002db71c;
 case UINT32_C(0x002db720):goto L_002db720;
 case UINT32_C(0x002db724):goto L_002db724;
 case UINT32_C(0x002db728):goto L_002db728;
 case UINT32_C(0x002db72c):goto L_002db72c;
 case UINT32_C(0x002db730):goto L_002db730;
 case UINT32_C(0x002db734):goto L_002db734;
 case UINT32_C(0x002db738):goto L_002db738;
 case UINT32_C(0x002db73c):goto L_002db73c;
 case UINT32_C(0x002db740):goto L_002db740;
 case UINT32_C(0x002db744):goto L_002db744;
 case UINT32_C(0x002db748):goto L_002db748;
 case UINT32_C(0x002db74c):goto L_002db74c;
 case UINT32_C(0x002db750):goto L_002db750;
 case UINT32_C(0x002db754):goto L_002db754;
 case UINT32_C(0x002db7e0):goto L_002db7e0;
 case UINT32_C(0x002db7e4):goto L_002db7e4;
 case UINT32_C(0x002db7e8):goto L_002db7e8;
 case UINT32_C(0x002db7ec):goto L_002db7ec;
 case UINT32_C(0x002db7f0):goto L_002db7f0;
 case UINT32_C(0x002db7f4):goto L_002db7f4;
 case UINT32_C(0x002db7f8):goto L_002db7f8;
 case UINT32_C(0x002db7fc):goto L_002db7fc;
 case UINT32_C(0x002db800):goto L_002db800;
 case UINT32_C(0x002db804):goto L_002db804;
 case UINT32_C(0x002db808):goto L_002db808;
 case UINT32_C(0x002db80c):goto L_002db80c;
 case UINT32_C(0x002db810):goto L_002db810;
 case UINT32_C(0x002db814):goto L_002db814;
 case UINT32_C(0x002db818):goto L_002db818;
 case UINT32_C(0x002db81c):goto L_002db81c;
 case UINT32_C(0x002db820):goto L_002db820;
 case UINT32_C(0x002db824):goto L_002db824;
 case UINT32_C(0x002db828):goto L_002db828;
 case UINT32_C(0x002db82c):goto L_002db82c;
 case UINT32_C(0x002db830):goto L_002db830;
 case UINT32_C(0x002db834):goto L_002db834;
 case UINT32_C(0x002db838):goto L_002db838;
 case UINT32_C(0x002db83c):goto L_002db83c;
 case UINT32_C(0x002dc468):goto L_002dc468;
 case UINT32_C(0x002dc46c):goto L_002dc46c;
 case UINT32_C(0x002dc470):goto L_002dc470;
 case UINT32_C(0x002dc474):goto L_002dc474;
 case UINT32_C(0x002dc478):goto L_002dc478;
 case UINT32_C(0x002dc47c):goto L_002dc47c;
 case UINT32_C(0x002dc480):goto L_002dc480;
 case UINT32_C(0x002dc484):goto L_002dc484;
 case UINT32_C(0x002dc488):goto L_002dc488;
 case UINT32_C(0x002dc48c):goto L_002dc48c;
 case UINT32_C(0x002dc490):goto L_002dc490;
 case UINT32_C(0x002dc494):goto L_002dc494;
 case UINT32_C(0x002dc498):goto L_002dc498;
 case UINT32_C(0x002dc49c):goto L_002dc49c;
 case UINT32_C(0x002dc4a0):goto L_002dc4a0;
 case UINT32_C(0x002dc4a4):goto L_002dc4a4;
 case UINT32_C(0x002dc4a8):goto L_002dc4a8;
 case UINT32_C(0x002dc4ac):goto L_002dc4ac;
 case UINT32_C(0x002dc4b0):goto L_002dc4b0;
 case UINT32_C(0x002dc4b4):goto L_002dc4b4;
 case UINT32_C(0x002dc4b8):goto L_002dc4b8;
 case UINT32_C(0x002dc4bc):goto L_002dc4bc;
 case UINT32_C(0x002dc4c0):goto L_002dc4c0;
 case UINT32_C(0x002dc4c4):goto L_002dc4c4;
 case UINT32_C(0x002dc4c8):goto L_002dc4c8;
 case UINT32_C(0x002dc4cc):goto L_002dc4cc;
 case UINT32_C(0x002dc4d0):goto L_002dc4d0;
 case UINT32_C(0x002dc4d4):goto L_002dc4d4;
 case UINT32_C(0x002dc4d8):goto L_002dc4d8;
 case UINT32_C(0x002dc4dc):goto L_002dc4dc;
 case UINT32_C(0x002dc4e0):goto L_002dc4e0;
 case UINT32_C(0x002db950):goto L_002db950;
 case UINT32_C(0x002db954):goto L_002db954;
 case UINT32_C(0x002db958):goto L_002db958;
 case UINT32_C(0x002db95c):goto L_002db95c;
 case UINT32_C(0x002db960):goto L_002db960;
 case UINT32_C(0x002db964):goto L_002db964;
 case UINT32_C(0x002db968):goto L_002db968;
 case UINT32_C(0x002db96c):goto L_002db96c;
 case UINT32_C(0x002db970):goto L_002db970;
 case UINT32_C(0x002db974):goto L_002db974;
 case UINT32_C(0x002db978):goto L_002db978;
 case UINT32_C(0x002db97c):goto L_002db97c;
 case UINT32_C(0x002db980):goto L_002db980;
 case UINT32_C(0x002db984):goto L_002db984;
 case UINT32_C(0x002db988):goto L_002db988;
 case UINT32_C(0x002db98c):goto L_002db98c;
 case UINT32_C(0x002db990):goto L_002db990;
 case UINT32_C(0x002db994):goto L_002db994;
 case UINT32_C(0x002db998):goto L_002db998;
 case UINT32_C(0x002db99c):goto L_002db99c;
 case UINT32_C(0x002db9a0):goto L_002db9a0;
 case UINT32_C(0x002db9a4):goto L_002db9a4;
 case UINT32_C(0x002db9a8):goto L_002db9a8;
 case UINT32_C(0x002dc658):goto L_002dc658;
 case UINT32_C(0x002dc65c):goto L_002dc65c;
 case UINT32_C(0x002dc660):goto L_002dc660;
 case UINT32_C(0x002dc664):goto L_002dc664;
 case UINT32_C(0x002dc668):goto L_002dc668;
 case UINT32_C(0x002dc650):goto L_002dc650;
 case UINT32_C(0x002dc654):goto L_002dc654;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002d6678:
 STEP(UINT32_C(0x002d6678)); /* 27bdfd70 addiu sp,sp,-656 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffd70)));target=sx(UINT32_C(0x002d667c));goto dispatch;
L_002d667c:
 STEP(UINT32_C(0x002d667c)); /* ffb00240 sd s0,0x240(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000240),&value64,8u);target=sx(UINT32_C(0x002d6680));goto dispatch;
L_002d6680:
 STEP(UINT32_C(0x002d6680)); /* 00c0802d daddu s0,a2,zero */
 set(m,16u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d6684));goto dispatch;
L_002d6684:
 STEP(UINT32_C(0x002d6684)); /* ffb60270 sd s6,0x270(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000270),&value64,8u);target=sx(UINT32_C(0x002d6688));goto dispatch;
L_002d6688:
 STEP(UINT32_C(0x002d6688)); /* 00e0b02d daddu s6,a3,zero */
 set(m,22u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d668c));goto dispatch;
L_002d668c:
 STEP(UINT32_C(0x002d668c)); /* afa401e4 sw a0,0x1e4(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001e4),&value32,4u);target=sx(UINT32_C(0x002d6690));goto dispatch;
L_002d6690:
 STEP(UINT32_C(0x002d6690)); /* ffb10248 sd s1,0x248(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000248),&value64,8u);target=sx(UINT32_C(0x002d6694));goto dispatch;
L_002d6694:
 STEP(UINT32_C(0x002d6694)); /* ffb20250 sd s2,0x250(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000250),&value64,8u);target=sx(UINT32_C(0x002d6698));goto dispatch;
L_002d6698:
 STEP(UINT32_C(0x002d6698)); /* ffb30258 sd s3,0x258(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000258),&value64,8u);target=sx(UINT32_C(0x002d669c));goto dispatch;
L_002d669c:
 STEP(UINT32_C(0x002d669c)); /* ffb40260 sd s4,0x260(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000260),&value64,8u);target=sx(UINT32_C(0x002d66a0));goto dispatch;
L_002d66a0:
 STEP(UINT32_C(0x002d66a0)); /* ffb50268 sd s5,0x268(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000268),&value64,8u);target=sx(UINT32_C(0x002d66a4));goto dispatch;
L_002d66a4:
 STEP(UINT32_C(0x002d66a4)); /* ffb70278 sd s7,0x278(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000278),&value64,8u);target=sx(UINT32_C(0x002d66a8));goto dispatch;
L_002d66a8:
 STEP(UINT32_C(0x002d66a8)); /* ffbe0280 sd s8,0x280(sp) */
 value64=lo(m,30u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000280),&value64,8u);target=sx(UINT32_C(0x002d66ac));goto dispatch;
L_002d66ac:
 STEP(UINT32_C(0x002d66ac)); /* ffbf0288 sd ra,0x288(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000288),&value64,8u);target=sx(UINT32_C(0x002d66b0));goto dispatch;
L_002d66b0:
 STEP(UINT32_C(0x002d66b0)); /* 0c0b68d0 jal 002da340 */
 set(m,31u,UINT64_C(0x002d66b8));STEP(UINT32_C(0x002d66b4));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);target=sx(UINT32_C(0x002da340));goto dispatch;
L_002d66b4:
 STEP(UINT32_C(0x002d66b4)); /* afa501e8 sw a1,0x1e8(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);target=sx(UINT32_C(0x002d66b8));goto dispatch;
L_002d66b8:
 STEP(UINT32_C(0x002d66b8)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d66bc));goto dispatch;
L_002d66bc:
 STEP(UINT32_C(0x002d66bc)); /* 8c420000 lw v0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d66c0));goto dispatch;
L_002d66c0:
 STEP(UINT32_C(0x002d66c0)); /* 9483000c lhu v1,0xc(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d66c4));goto dispatch;
L_002d66c4:
 STEP(UINT32_C(0x002d66c4)); /* afa201f4 sw v0,0x1f4(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001f4),&value32,4u);target=sx(UINT32_C(0x002d66c8));goto dispatch;
L_002d66c8:
 STEP(UINT32_C(0x002d66c8)); /* 30620008 andi v0,v1,0x8 */
 set(m,2u,lo(m,3u) & UINT64_C(0x8));target=sx(UINT32_C(0x002d66cc));goto dispatch;
L_002d66cc:
 STEP(UINT32_C(0x002d66cc)); /* 10400004 beq v0,zero,002d66e0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d66d0));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d8),&value32,4u);target=sx(taken?UINT32_C(0x002d66e0):UINT32_C(0x002d66d4));goto dispatch;}
L_002d66d0:
 STEP(UINT32_C(0x002d66d0)); /* afa001d8 sw zero,0x1d8(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d8),&value32,4u);target=sx(UINT32_C(0x002d66d4));goto dispatch;
L_002d66d4:
 STEP(UINT32_C(0x002d66d4)); /* 8c820010 lw v0,0x10(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d66d8));goto dispatch;
L_002d66d8:
 STEP(UINT32_C(0x002d66d8)); /* 54400008 bnel v0,zero,002d66fc */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d66dc));set(m,3u,lo(m,3u) & UINT64_C(0x1a));target=sx(UINT32_C(0x002d66fc));}else target=sx(UINT32_C(0x002d66e0));goto dispatch;
L_002d66dc:
 STEP(UINT32_C(0x002d66dc)); /* 3063001a andi v1,v1,0x1a */
 set(m,3u,lo(m,3u) & UINT64_C(0x1a));target=sx(UINT32_C(0x002d66e0));goto dispatch;
L_002d66e0:
 STEP(UINT32_C(0x002d66e0)); /* 0c0b600e jal 002d8038 */
 set(m,31u,UINT64_C(0x002d66e8));STEP(UINT32_C(0x002d66e4));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d8038));goto dispatch;
L_002d66e4:
 STEP(UINT32_C(0x002d66e4)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d66e8));goto dispatch;
L_002d66e8:
 STEP(UINT32_C(0x002d66e8)); /* 14400573 bne v0,zero,002d7cb8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d66ec));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002d7cb8):UINT32_C(0x002d66f0));goto dispatch;}
L_002d66ec:
 STEP(UINT32_C(0x002d66ec)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d66f0));goto dispatch;
L_002d66f0:
 STEP(UINT32_C(0x002d66f0)); /* 8fa501e8 lw a1,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d66f4));goto dispatch;
L_002d66f4:
 STEP(UINT32_C(0x002d66f4)); /* 94a3000c lhu v1,0xc(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d66f8));goto dispatch;
L_002d66f8:
 STEP(UINT32_C(0x002d66f8)); /* 3063001a andi v1,v1,0x1a */
 set(m,3u,lo(m,3u) & UINT64_C(0x1a));target=sx(UINT32_C(0x002d66fc));goto dispatch;
L_002d66fc:
 STEP(UINT32_C(0x002d66fc)); /* 2402000a addiu v0,zero,10 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002d6700));goto dispatch;
L_002d6700:
 STEP(UINT32_C(0x002d6700)); /* 1462000b bne v1,v0,002d6730 */
 {int taken=(lo(m,3u)!=lo(m,2u));STEP(UINT32_C(0x002d6704));set(m,19u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(taken?UINT32_C(0x002d6730):UINT32_C(0x002d6708));goto dispatch;}
L_002d6704:
 STEP(UINT32_C(0x002d6704)); /* 27b30020 addiu s3,sp,32 */
 set(m,19u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d6708));goto dispatch;
L_002d6708:
 STEP(UINT32_C(0x002d6708)); /* 8fa601e8 lw a2,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d670c));goto dispatch;
L_002d670c:
 STEP(UINT32_C(0x002d670c)); /* 84c2000e lh v0,0xe(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x0000000e),&value16,2u);set(m,2u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002d6710));goto dispatch;
L_002d6710:
 STEP(UINT32_C(0x002d6710)); /* 04400007 regimm0 v0,002d6730 */
 {int taken=((int64_t)lo(m,2u)<0);STEP(UINT32_C(0x002d6714));set(m,4u,lo(m,6u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6730):UINT32_C(0x002d6718));goto dispatch;}
L_002d6714:
 STEP(UINT32_C(0x002d6714)); /* 00c0202d daddu a0,a2,zero */
 set(m,4u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d6718));goto dispatch;
L_002d6718:
 STEP(UINT32_C(0x002d6718)); /* 02c0302d daddu a2,s6,zero */
 set(m,6u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d671c));goto dispatch;
L_002d671c:
 STEP(UINT32_C(0x002d671c)); /* 0c0b5952 jal 002d6548 */
 set(m,31u,UINT64_C(0x002d6724));STEP(UINT32_C(0x002d6720));set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6548));goto dispatch;
L_002d6720:
 STEP(UINT32_C(0x002d6720)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6724));goto dispatch;
L_002d6724:
 STEP(UINT32_C(0x002d6724)); /* 10000565 beq zero,zero,002d7cbc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6728));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000240),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002d7cbc):UINT32_C(0x002d672c));goto dispatch;}
L_002d6728:
 STEP(UINT32_C(0x002d6728)); /* dfb00240 ld s0,0x240(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000240),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d672c));goto dispatch;
L_002d672c:
 STEP(UINT32_C(0x002d672c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6730));goto dispatch;
L_002d6730:
 STEP(UINT32_C(0x002d6730)); /* afa00018 sw zero,0x18(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d6734));goto dispatch;
L_002d6734:
 STEP(UINT32_C(0x002d6734)); /* afb30010 sw s3,0x10(sp) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002d6738));goto dispatch;
L_002d6738:
 STEP(UINT32_C(0x002d6738)); /* 0200902d daddu s2,s0,zero */
 set(m,18u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d673c));goto dispatch;
L_002d673c:
 STEP(UINT32_C(0x002d673c)); /* afa00014 sw zero,0x14(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d6740));goto dispatch;
L_002d6740:
 STEP(UINT32_C(0x002d6740)); /* afa001ec sw zero,0x1ec(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);target=sx(UINT32_C(0x002d6744));goto dispatch;
L_002d6744:
 STEP(UINT32_C(0x002d6744)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6748));goto dispatch;
L_002d6748:
 STEP(UINT32_C(0x002d6748)); /* 0240a82d daddu s5,s2,zero */
 set(m,21u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d674c));goto dispatch;
L_002d674c:
 STEP(UINT32_C(0x002d674c)); /* 24110025 addiu s1,zero,37 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000025)));target=sx(UINT32_C(0x002d6750));goto dispatch;
L_002d6750:
 STEP(UINT32_C(0x002d6750)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d6754));goto dispatch;
L_002d6754:
 STEP(UINT32_C(0x002d6754)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d6758));goto dispatch;
L_002d6758:
 STEP(UINT32_C(0x002d6758)); /* 8c44be28 lw a0,-0x41d8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbe28),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d675c));goto dispatch;
L_002d675c:
 STEP(UINT32_C(0x002d675c)); /* 27a501d4 addiu a1,sp,468 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001d4)));target=sx(UINT32_C(0x002d6760));goto dispatch;
L_002d6760:
 STEP(UINT32_C(0x002d6760)); /* 8c67c290 lw a3,-0x3d70(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffc290),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d6764));goto dispatch;
L_002d6764:
 STEP(UINT32_C(0x002d6764)); /* 0240302d daddu a2,s2,zero */
 set(m,6u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d6768));goto dispatch;
L_002d6768:
 STEP(UINT32_C(0x002d6768)); /* 0c0b692e jal 002da4b8 */
 set(m,31u,UINT64_C(0x002d6770));STEP(UINT32_C(0x002d676c));set(m,8u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001d8)));target=sx(UINT32_C(0x002da4b8));goto dispatch;
L_002d676c:
 STEP(UINT32_C(0x002d676c)); /* 27a801d8 addiu t0,sp,472 */
 set(m,8u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001d8)));target=sx(UINT32_C(0x002d6770));goto dispatch;
L_002d6770:
 STEP(UINT32_C(0x002d6770)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d6774));goto dispatch;
L_002d6774:
 STEP(UINT32_C(0x002d6774)); /* 5a000006 blezl s0,zero,002d6790 */
 if((int64_t)lo(m,16u)<=0){STEP(UINT32_C(0x002d6778));set(m,17u,sx((uint32_t)lo(m,18u)-(uint32_t)lo(m,21u)));target=sx(UINT32_C(0x002d6790));}else target=sx(UINT32_C(0x002d677c));goto dispatch;
L_002d6778:
 STEP(UINT32_C(0x002d6778)); /* 02558823 subu s1,s2,s5 */
 set(m,17u,sx((uint32_t)lo(m,18u)-(uint32_t)lo(m,21u)));target=sx(UINT32_C(0x002d677c));goto dispatch;
L_002d677c:
 STEP(UINT32_C(0x002d677c)); /* 8fa201d4 lw v0,0x1d4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d4),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6780));goto dispatch;
L_002d6780:
 STEP(UINT32_C(0x002d6780)); /* 1451fff3 bne v0,s1,002d6750 */
 {int taken=(lo(m,2u)!=lo(m,17u));STEP(UINT32_C(0x002d6784));set(m,18u,sx((uint32_t)lo(m,18u)+(uint32_t)lo(m,16u)));target=sx(taken?UINT32_C(0x002d6750):UINT32_C(0x002d6788));goto dispatch;}
L_002d6784:
 STEP(UINT32_C(0x002d6784)); /* 02509021 addu s2,s2,s0 */
 set(m,18u,sx((uint32_t)lo(m,18u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d6788));goto dispatch;
L_002d6788:
 STEP(UINT32_C(0x002d6788)); /* 2652ffff addiu s2,s2,-1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d678c));goto dispatch;
L_002d678c:
 STEP(UINT32_C(0x002d678c)); /* 02558823 subu s1,s2,s5 */
 set(m,17u,sx((uint32_t)lo(m,18u)-(uint32_t)lo(m,21u)));target=sx(UINT32_C(0x002d6790));goto dispatch;
L_002d6790:
 STEP(UINT32_C(0x002d6790)); /* 12200016 beq s1,zero,002d67ec */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002d6794));/* nop */target=sx(taken?UINT32_C(0x002d67ec):UINT32_C(0x002d6798));goto dispatch;}
L_002d6794:
 STEP(UINT32_C(0x002d6794)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6798));goto dispatch;
L_002d6798:
 STEP(UINT32_C(0x002d6798)); /* ae710004 sw s1,0x4(s3) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d679c));goto dispatch;
L_002d679c:
 STEP(UINT32_C(0x002d679c)); /* ae750000 sw s5,0x0(s3) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d67a0));goto dispatch;
L_002d67a0:
 STEP(UINT32_C(0x002d67a0)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d67a4));goto dispatch;
L_002d67a4:
 STEP(UINT32_C(0x002d67a4)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d67a8));goto dispatch;
L_002d67a8:
 STEP(UINT32_C(0x002d67a8)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d67ac));goto dispatch;
L_002d67ac:
 STEP(UINT32_C(0x002d67ac)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d67b0));goto dispatch;
L_002d67b0:
 STEP(UINT32_C(0x002d67b0)); /* 00711821 addu v1,v1,s1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d67b4));goto dispatch;
L_002d67b4:
 STEP(UINT32_C(0x002d67b4)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d67b8));goto dispatch;
L_002d67b8:
 STEP(UINT32_C(0x002d67b8)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d67bc));goto dispatch;
L_002d67bc:
 STEP(UINT32_C(0x002d67bc)); /* 14800008 bne a0,zero,002d67e0 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d67c0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d67e0):UINT32_C(0x002d67c4));goto dispatch;}
L_002d67c0:
 STEP(UINT32_C(0x002d67c0)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d67c4));goto dispatch;
L_002d67c4:
 STEP(UINT32_C(0x002d67c4)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d67c8));goto dispatch;
L_002d67c8:
 STEP(UINT32_C(0x002d67c8)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d67d0));STEP(UINT32_C(0x002d67cc));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d67cc:
 STEP(UINT32_C(0x002d67cc)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d67d0));goto dispatch;
L_002d67d0:
 STEP(UINT32_C(0x002d67d0)); /* 14400534 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d67d4));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d67d8));goto dispatch;}
L_002d67d4:
 STEP(UINT32_C(0x002d67d4)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d67d8));goto dispatch;
L_002d67d8:
 STEP(UINT32_C(0x002d67d8)); /* 27a40020 addiu a0,sp,32 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d67dc));goto dispatch;
L_002d67dc:
 STEP(UINT32_C(0x002d67dc)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d67e0));goto dispatch;
L_002d67e0:
 STEP(UINT32_C(0x002d67e0)); /* 8fa501ec lw a1,0x1ec(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d67e4));goto dispatch;
L_002d67e4:
 STEP(UINT32_C(0x002d67e4)); /* 00b12821 addu a1,a1,s1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d67e8));goto dispatch;
L_002d67e8:
 STEP(UINT32_C(0x002d67e8)); /* afa501ec sw a1,0x1ec(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);target=sx(UINT32_C(0x002d67ec));goto dispatch;
L_002d67ec:
 STEP(UINT32_C(0x002d67ec)); /* 1a000525 blez s0,zero,002d7c84 */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d67f0));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7c84):UINT32_C(0x002d67f4));goto dispatch;}
L_002d67f0:
 STEP(UINT32_C(0x002d67f0)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d67f4));goto dispatch;
L_002d67f4:
 STEP(UINT32_C(0x002d67f4)); /* a3a001d1 sb zero,0x1d1(sp) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d67f8));goto dispatch;
L_002d67f8:
 STEP(UINT32_C(0x002d67f8)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d67fc));goto dispatch;
L_002d67fc:
 STEP(UINT32_C(0x002d67fc)); /* afa00204 sw zero,0x204(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);target=sx(UINT32_C(0x002d6800));goto dispatch;
L_002d6800:
 STEP(UINT32_C(0x002d6800)); /* 0000b82d daddu s7,zero,zero */
 set(m,23u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d6804));goto dispatch;
L_002d6804:
 STEP(UINT32_C(0x002d6804)); /* afa001f0 sw zero,0x1f0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);target=sx(UINT32_C(0x002d6808));goto dispatch;
L_002d6808:
 STEP(UINT32_C(0x002d6808)); /* 2414ffff addiu s4,zero,-1 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d680c));goto dispatch;
L_002d680c:
 STEP(UINT32_C(0x002d680c)); /* 92440000 lbu a0,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,4u,byte);}target=sx(UINT32_C(0x002d6810));goto dispatch;
L_002d6810:
 STEP(UINT32_C(0x002d6810)); /* 00041600 sll v0,a0,24 */
 set(m,2u,sx((uint32_t)lo(m,4u)<<24u));target=sx(UINT32_C(0x002d6814));goto dispatch;
L_002d6814:
 STEP(UINT32_C(0x002d6814)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6818));goto dispatch;
L_002d6818:
 STEP(UINT32_C(0x002d6818)); /* 00028e03 sra s1,v0,24 */
 set(m,17u,sx((uint32_t)((int32_t)lo(m,2u)>>24u)));target=sx(UINT32_C(0x002d681c));goto dispatch;
L_002d681c:
 STEP(UINT32_C(0x002d681c)); /* 2623ffe0 addiu v1,s1,-32 */
 set(m,3u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d6820));goto dispatch;
L_002d6820:
 STEP(UINT32_C(0x002d6820)); /* 2c620059 sltiu v0,v1,89 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x59)));target=sx(UINT32_C(0x002d6824));goto dispatch;
L_002d6824:
 STEP(UINT32_C(0x002d6824)); /* 104001b2 beq v0,zero,002d6ef0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6828));set(m,2u,sx((uint32_t)lo(m,3u)<<2u));target=sx(taken?UINT32_C(0x002d6ef0):UINT32_C(0x002d682c));goto dispatch;}
L_002d6828:
 STEP(UINT32_C(0x002d6828)); /* 00031080 sll v0,v1,2 */
 set(m,2u,sx((uint32_t)lo(m,3u)<<2u));target=sx(UINT32_C(0x002d682c));goto dispatch;
L_002d682c:
 STEP(UINT32_C(0x002d682c)); /* 3c030055 lui v1,zero,0x55 */
 set(m,3u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6830));goto dispatch;
L_002d6830:
 STEP(UINT32_C(0x002d6830)); /* 00621821 addu v1,v1,v0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d6834));goto dispatch;
L_002d6834:
 STEP(UINT32_C(0x002d6834)); /* 8c63b710 lw v1,-0x48f0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffb710),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d6838));goto dispatch;
L_002d6838:
 STEP(UINT32_C(0x002d6838)); /* 00600008 jr v1 */
 target=sx((uint32_t)lo(m,3u));STEP(UINT32_C(0x002d683c));/* nop */goto dispatch;
L_002d683c:
 STEP(UINT32_C(0x002d683c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6840));goto dispatch;
L_002d6840:
 STEP(UINT32_C(0x002d6840)); /* 83a201d1 lb v0,0x1d1(sp) */
 {uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);set(m,2u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d6844));goto dispatch;
L_002d6844:
 STEP(UINT32_C(0x002d6844)); /* 5440fff2 bnel v0,zero,002d6810 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d6848));{uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,4u,byte);}target=sx(UINT32_C(0x002d6810));}else target=sx(UINT32_C(0x002d684c));goto dispatch;
L_002d6848:
 STEP(UINT32_C(0x002d6848)); /* 92440000 lbu a0,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,4u,byte);}target=sx(UINT32_C(0x002d684c));goto dispatch;
L_002d684c:
 STEP(UINT32_C(0x002d684c)); /* 1000000f beq zero,zero,002d688c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6850));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(taken?UINT32_C(0x002d688c):UINT32_C(0x002d6854));goto dispatch;}
L_002d6850:
 STEP(UINT32_C(0x002d6850)); /* 24020020 addiu v0,zero,32 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d6854));goto dispatch;
L_002d6854:
 STEP(UINT32_C(0x002d6854)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6858));goto dispatch;
L_002d6858:
 STEP(UINT32_C(0x002d6858)); /* 1000ffec beq zero,zero,002d680c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d685c));set(m,23u,lo(m,23u) | UINT64_C(0x1));target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d6860));goto dispatch;}
L_002d685c:
 STEP(UINT32_C(0x002d685c)); /* 36f70001 ori s7,s7,0x1 */
 set(m,23u,lo(m,23u) | UINT64_C(0x1));target=sx(UINT32_C(0x002d6860));goto dispatch;
L_002d6860:
 STEP(UINT32_C(0x002d6860)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6864));goto dispatch;
L_002d6864:
 STEP(UINT32_C(0x002d6864)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6868));goto dispatch;
L_002d6868:
 STEP(UINT32_C(0x002d6868)); /* 8c420000 lw v0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d686c));goto dispatch;
L_002d686c:
 STEP(UINT32_C(0x002d686c)); /* 0441ffe7 regimm1 v0,002d680c */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002d6870));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d6874));goto dispatch;}
L_002d6870:
 STEP(UINT32_C(0x002d6870)); /* afa201f0 sw v0,0x1f0(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);target=sx(UINT32_C(0x002d6874));goto dispatch;
L_002d6874:
 STEP(UINT32_C(0x002d6874)); /* 00021023 subu v0,zero,v0 */
 set(m,2u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d6878));goto dispatch;
L_002d6878:
 STEP(UINT32_C(0x002d6878)); /* afa201f0 sw v0,0x1f0(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);target=sx(UINT32_C(0x002d687c));goto dispatch;
L_002d687c:
 STEP(UINT32_C(0x002d687c)); /* 1000ffe3 beq zero,zero,002d680c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6880));set(m,23u,lo(m,23u) | UINT64_C(0x4));target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d6884));goto dispatch;}
L_002d6880:
 STEP(UINT32_C(0x002d6880)); /* 36f70004 ori s7,s7,0x4 */
 set(m,23u,lo(m,23u) | UINT64_C(0x4));target=sx(UINT32_C(0x002d6884));goto dispatch;
L_002d6884:
 STEP(UINT32_C(0x002d6884)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6888));goto dispatch;
L_002d6888:
 STEP(UINT32_C(0x002d6888)); /* 2402002b addiu v0,zero,43 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000002b)));target=sx(UINT32_C(0x002d688c));goto dispatch;
L_002d688c:
 STEP(UINT32_C(0x002d688c)); /* 92440000 lbu a0,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,4u,byte);}target=sx(UINT32_C(0x002d6890));goto dispatch;
L_002d6890:
 STEP(UINT32_C(0x002d6890)); /* 1000ffdf beq zero,zero,002d6810 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6894));{uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(taken?UINT32_C(0x002d6810):UINT32_C(0x002d6898));goto dispatch;}
L_002d6894:
 STEP(UINT32_C(0x002d6894)); /* a3a201d1 sb v0,0x1d1(sp) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d6898));goto dispatch;
L_002d6898:
 STEP(UINT32_C(0x002d6898)); /* 82510000 lb s1,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,17u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d689c));goto dispatch;
L_002d689c:
 STEP(UINT32_C(0x002d689c)); /* 2402002a addiu v0,zero,42 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000002a)));target=sx(UINT32_C(0x002d68a0));goto dispatch;
L_002d68a0:
 STEP(UINT32_C(0x002d68a0)); /* 16220009 bne s1,v0,002d68c8 */
 {int taken=(lo(m,17u)!=lo(m,2u));STEP(UINT32_C(0x002d68a4));set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d68c8):UINT32_C(0x002d68a8));goto dispatch;}
L_002d68a4:
 STEP(UINT32_C(0x002d68a4)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d68a8));goto dispatch;
L_002d68a8:
 STEP(UINT32_C(0x002d68a8)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d68ac));goto dispatch;
L_002d68ac:
 STEP(UINT32_C(0x002d68ac)); /* 8c500000 lw s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d68b0));goto dispatch;
L_002d68b0:
 STEP(UINT32_C(0x002d68b0)); /* 0200a02d daddu s4,s0,zero */
 set(m,20u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d68b4));goto dispatch;
L_002d68b4:
 STEP(UINT32_C(0x002d68b4)); /* 2a82ffff slti v0,s4,-1 */
 set(m,2u,((int64_t)lo(m,20u)<INT64_C(-1)));target=sx(UINT32_C(0x002d68b8));goto dispatch;
L_002d68b8:
 STEP(UINT32_C(0x002d68b8)); /* 1040ffd4 beq v0,zero,002d680c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d68bc));set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d68c0));goto dispatch;}
L_002d68bc:
 STEP(UINT32_C(0x002d68bc)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d68c0));goto dispatch;
L_002d68c0:
 STEP(UINT32_C(0x002d68c0)); /* 1000ffd2 beq zero,zero,002d680c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d68c4));set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d68c8));goto dispatch;}
L_002d68c4:
 STEP(UINT32_C(0x002d68c4)); /* 2414ffff addiu s4,zero,-1 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d68c8));goto dispatch;
L_002d68c8:
 STEP(UINT32_C(0x002d68c8)); /* 2622ffd0 addiu v0,s1,-48 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002d68cc));goto dispatch;
L_002d68cc:
 STEP(UINT32_C(0x002d68cc)); /* 2c42000a sltiu v0,v0,10 */
 set(m,2u,(lo(m,2u)<UINT64_C(0xa)));target=sx(UINT32_C(0x002d68d0));goto dispatch;
L_002d68d0:
 STEP(UINT32_C(0x002d68d0)); /* 1040000b beq v0,zero,002d6900 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d68d4));set(m,16u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6900):UINT32_C(0x002d68d8));goto dispatch;}
L_002d68d4:
 STEP(UINT32_C(0x002d68d4)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d68d8));goto dispatch;
L_002d68d8:
 STEP(UINT32_C(0x002d68d8)); /* 00101080 sll v0,s0,2 */
 set(m,2u,sx((uint32_t)lo(m,16u)<<2u));target=sx(UINT32_C(0x002d68dc));goto dispatch;
L_002d68dc:
 STEP(UINT32_C(0x002d68dc)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d68e0));goto dispatch;
L_002d68e0:
 STEP(UINT32_C(0x002d68e0)); /* 00021040 sll v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<1u));target=sx(UINT32_C(0x002d68e4));goto dispatch;
L_002d68e4:
 STEP(UINT32_C(0x002d68e4)); /* 00511021 addu v0,v0,s1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d68e8));goto dispatch;
L_002d68e8:
 STEP(UINT32_C(0x002d68e8)); /* 82510000 lb s1,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,17u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d68ec));goto dispatch;
L_002d68ec:
 STEP(UINT32_C(0x002d68ec)); /* 2450ffd0 addiu s0,v0,-48 */
 set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002d68f0));goto dispatch;
L_002d68f0:
 STEP(UINT32_C(0x002d68f0)); /* 2622ffd0 addiu v0,s1,-48 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002d68f4));goto dispatch;
L_002d68f4:
 STEP(UINT32_C(0x002d68f4)); /* 2c42000a sltiu v0,v0,10 */
 set(m,2u,(lo(m,2u)<UINT64_C(0xa)));target=sx(UINT32_C(0x002d68f8));goto dispatch;
L_002d68f8:
 STEP(UINT32_C(0x002d68f8)); /* 1440fff7 bne v0,zero,002d68d8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d68fc));set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d68d8):UINT32_C(0x002d6900));goto dispatch;}
L_002d68fc:
 STEP(UINT32_C(0x002d68fc)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6900));goto dispatch;
L_002d6900:
 STEP(UINT32_C(0x002d6900)); /* 0200a02d daddu s4,s0,zero */
 set(m,20u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6904));goto dispatch;
L_002d6904:
 STEP(UINT32_C(0x002d6904)); /* 2a82ffff slti v0,s4,-1 */
 set(m,2u,((int64_t)lo(m,20u)<INT64_C(-1)));target=sx(UINT32_C(0x002d6908));goto dispatch;
L_002d6908:
 STEP(UINT32_C(0x002d6908)); /* 5440ffc4 bnel v0,zero,002d681c */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d690c));set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d681c));}else target=sx(UINT32_C(0x002d6910));goto dispatch;
L_002d690c:
 STEP(UINT32_C(0x002d690c)); /* 2414ffff addiu s4,zero,-1 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6910));goto dispatch;
L_002d6910:
 STEP(UINT32_C(0x002d6910)); /* 1000ffc3 beq zero,zero,002d6820 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6914));set(m,3u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffe0)));target=sx(taken?UINT32_C(0x002d6820):UINT32_C(0x002d6918));goto dispatch;}
L_002d6914:
 STEP(UINT32_C(0x002d6914)); /* 2623ffe0 addiu v1,s1,-32 */
 set(m,3u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d6918));goto dispatch;
L_002d6918:
 STEP(UINT32_C(0x002d6918)); /* 1000ffbc beq zero,zero,002d680c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d691c));set(m,23u,lo(m,23u) | UINT64_C(0x80));target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d6920));goto dispatch;}
L_002d691c:
 STEP(UINT32_C(0x002d691c)); /* 36f70080 ori s7,s7,0x80 */
 set(m,23u,lo(m,23u) | UINT64_C(0x80));target=sx(UINT32_C(0x002d6920));goto dispatch;
L_002d6920:
 STEP(UINT32_C(0x002d6920)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d6924));goto dispatch;
L_002d6924:
 STEP(UINT32_C(0x002d6924)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6928));goto dispatch;
L_002d6928:
 STEP(UINT32_C(0x002d6928)); /* 00101080 sll v0,s0,2 */
 set(m,2u,sx((uint32_t)lo(m,16u)<<2u));target=sx(UINT32_C(0x002d692c));goto dispatch;
L_002d692c:
 STEP(UINT32_C(0x002d692c)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d6930));goto dispatch;
L_002d6930:
 STEP(UINT32_C(0x002d6930)); /* 00021040 sll v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<1u));target=sx(UINT32_C(0x002d6934));goto dispatch;
L_002d6934:
 STEP(UINT32_C(0x002d6934)); /* 00511021 addu v0,v0,s1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,17u)));target=sx(UINT32_C(0x002d6938));goto dispatch;
L_002d6938:
 STEP(UINT32_C(0x002d6938)); /* 82510000 lb s1,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,17u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d693c));goto dispatch;
L_002d693c:
 STEP(UINT32_C(0x002d693c)); /* 2450ffd0 addiu s0,v0,-48 */
 set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002d6940));goto dispatch;
L_002d6940:
 STEP(UINT32_C(0x002d6940)); /* 2622ffd0 addiu v0,s1,-48 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002d6944));goto dispatch;
L_002d6944:
 STEP(UINT32_C(0x002d6944)); /* 2c42000a sltiu v0,v0,10 */
 set(m,2u,(lo(m,2u)<UINT64_C(0xa)));target=sx(UINT32_C(0x002d6948));goto dispatch;
L_002d6948:
 STEP(UINT32_C(0x002d6948)); /* 1440fff7 bne v0,zero,002d6928 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d694c));set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d6928):UINT32_C(0x002d6950));goto dispatch;}
L_002d694c:
 STEP(UINT32_C(0x002d694c)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6950));goto dispatch;
L_002d6950:
 STEP(UINT32_C(0x002d6950)); /* 1000ffb2 beq zero,zero,002d681c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6954));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);target=sx(taken?UINT32_C(0x002d681c):UINT32_C(0x002d6958));goto dispatch;}
L_002d6954:
 STEP(UINT32_C(0x002d6954)); /* afb001f0 sw s0,0x1f0(sp) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);target=sx(UINT32_C(0x002d6958));goto dispatch;
L_002d6958:
 STEP(UINT32_C(0x002d6958)); /* 1000ffac beq zero,zero,002d680c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d695c));set(m,23u,lo(m,23u) | UINT64_C(0x8));target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d6960));goto dispatch;}
L_002d695c:
 STEP(UINT32_C(0x002d695c)); /* 36f70008 ori s7,s7,0x8 */
 set(m,23u,lo(m,23u) | UINT64_C(0x8));target=sx(UINT32_C(0x002d6960));goto dispatch;
L_002d6960:
 STEP(UINT32_C(0x002d6960)); /* 1000ffaa beq zero,zero,002d680c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6964));set(m,23u,lo(m,23u) | UINT64_C(0x40));target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d6968));goto dispatch;}
L_002d6964:
 STEP(UINT32_C(0x002d6964)); /* 36f70040 ori s7,s7,0x40 */
 set(m,23u,lo(m,23u) | UINT64_C(0x40));target=sx(UINT32_C(0x002d6968));goto dispatch;
L_002d6968:
 STEP(UINT32_C(0x002d6968)); /* 82430000 lb v1,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d696c));goto dispatch;
L_002d696c:
 STEP(UINT32_C(0x002d696c)); /* 2402006c addiu v0,zero,108 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000006c)));target=sx(UINT32_C(0x002d6970));goto dispatch;
L_002d6970:
 STEP(UINT32_C(0x002d6970)); /* 14620005 bne v1,v0,002d6988 */
 {int taken=(lo(m,3u)!=lo(m,2u));STEP(UINT32_C(0x002d6974));{uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,4u,byte);}target=sx(taken?UINT32_C(0x002d6988):UINT32_C(0x002d6978));goto dispatch;}
L_002d6974:
 STEP(UINT32_C(0x002d6974)); /* 92440000 lbu a0,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,4u,byte);}target=sx(UINT32_C(0x002d6978));goto dispatch;
L_002d6978:
 STEP(UINT32_C(0x002d6978)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d697c));goto dispatch;
L_002d697c:
 STEP(UINT32_C(0x002d697c)); /* 1000ffa3 beq zero,zero,002d680c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6980));set(m,23u,lo(m,23u) | UINT64_C(0x20));target=sx(taken?UINT32_C(0x002d680c):UINT32_C(0x002d6984));goto dispatch;}
L_002d6980:
 STEP(UINT32_C(0x002d6980)); /* 36f70020 ori s7,s7,0x20 */
 set(m,23u,lo(m,23u) | UINT64_C(0x20));target=sx(UINT32_C(0x002d6984));goto dispatch;
L_002d6984:
 STEP(UINT32_C(0x002d6984)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6988));goto dispatch;
L_002d6988:
 STEP(UINT32_C(0x002d6988)); /* 1000ffa1 beq zero,zero,002d6810 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d698c));set(m,23u,lo(m,23u) | UINT64_C(0x10));target=sx(taken?UINT32_C(0x002d6810):UINT32_C(0x002d6990));goto dispatch;}
L_002d698c:
 STEP(UINT32_C(0x002d698c)); /* 36f70010 ori s7,s7,0x10 */
 set(m,23u,lo(m,23u) | UINT64_C(0x10));target=sx(UINT32_C(0x002d6990));goto dispatch;
L_002d6990:
 STEP(UINT32_C(0x002d6990)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6994));goto dispatch;
L_002d6994:
 STEP(UINT32_C(0x002d6994)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6998));goto dispatch;
L_002d6998:
 STEP(UINT32_C(0x002d6998)); /* 90430000 lbu v1,0x0(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002d699c));goto dispatch;
L_002d699c:
 STEP(UINT32_C(0x002d699c)); /* 27b50060 addiu s5,sp,96 */
 set(m,21u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002d69a0));goto dispatch;
L_002d69a0:
 STEP(UINT32_C(0x002d69a0)); /* 241e0001 addiu s8,zero,1 */
 set(m,30u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d69a4));goto dispatch;
L_002d69a4:
 STEP(UINT32_C(0x002d69a4)); /* 10000156 beq zero,zero,002d6f00 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d69a8));{uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(taken?UINT32_C(0x002d6f00):UINT32_C(0x002d69ac));goto dispatch;}
L_002d69a8:
 STEP(UINT32_C(0x002d69a8)); /* a2a30000 sb v1,0x0(s5) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d69ac));goto dispatch;
L_002d69ac:
 STEP(UINT32_C(0x002d69ac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d69b0));goto dispatch;
L_002d69b0:
 STEP(UINT32_C(0x002d69b0)); /* 36f70010 ori s7,s7,0x10 */
 set(m,23u,lo(m,23u) | UINT64_C(0x10));target=sx(UINT32_C(0x002d69b4));goto dispatch;
L_002d69b4:
 STEP(UINT32_C(0x002d69b4)); /* 32e20010 andi v0,s7,0x10 */
 set(m,2u,lo(m,23u) & UINT64_C(0x10));target=sx(UINT32_C(0x002d69b8));goto dispatch;
L_002d69b8:
 STEP(UINT32_C(0x002d69b8)); /* 10400005 beq v0,zero,002d69d0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d69bc));set(m,2u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d69d0):UINT32_C(0x002d69c0));goto dispatch;}
L_002d69bc:
 STEP(UINT32_C(0x002d69bc)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d69c0));goto dispatch;
L_002d69c0:
 STEP(UINT32_C(0x002d69c0)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d69c4));goto dispatch;
L_002d69c4:
 STEP(UINT32_C(0x002d69c4)); /* 1000000a beq zero,zero,002d69f0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d69c8));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002d69f0):UINT32_C(0x002d69cc));goto dispatch;}
L_002d69c8:
 STEP(UINT32_C(0x002d69c8)); /* dc500000 ld s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d69cc));goto dispatch;
L_002d69cc:
 STEP(UINT32_C(0x002d69cc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d69d0));goto dispatch;
L_002d69d0:
 STEP(UINT32_C(0x002d69d0)); /* 32e20040 andi v0,s7,0x40 */
 set(m,2u,lo(m,23u) & UINT64_C(0x40));target=sx(UINT32_C(0x002d69d4));goto dispatch;
L_002d69d4:
 STEP(UINT32_C(0x002d69d4)); /* 10400004 beq v0,zero,002d69e8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d69d8));set(m,2u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d69e8):UINT32_C(0x002d69dc));goto dispatch;}
L_002d69d8:
 STEP(UINT32_C(0x002d69d8)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d69dc));goto dispatch;
L_002d69dc:
 STEP(UINT32_C(0x002d69dc)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d69e0));goto dispatch;
L_002d69e0:
 STEP(UINT32_C(0x002d69e0)); /* 10000003 beq zero,zero,002d69f0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d69e4));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);set(m,16u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(taken?UINT32_C(0x002d69f0):UINT32_C(0x002d69e8));goto dispatch;}
L_002d69e4:
 STEP(UINT32_C(0x002d69e4)); /* 84500000 lh s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);set(m,16u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002d69e8));goto dispatch;
L_002d69e8:
 STEP(UINT32_C(0x002d69e8)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d69ec));goto dispatch;
L_002d69ec:
 STEP(UINT32_C(0x002d69ec)); /* 8c500000 lw s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d69f0));goto dispatch;
L_002d69f0:
 STEP(UINT32_C(0x002d69f0)); /* 060100f7 regimm1 s0,002d6dd0 */
 {int taken=((int64_t)lo(m,16u)>=0);STEP(UINT32_C(0x002d69f4));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d6dd0):UINT32_C(0x002d69f8));goto dispatch;}
L_002d69f4:
 STEP(UINT32_C(0x002d69f4)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d69f8));goto dispatch;
L_002d69f8:
 STEP(UINT32_C(0x002d69f8)); /* 2402002d addiu v0,zero,45 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000002d)));target=sx(UINT32_C(0x002d69fc));goto dispatch;
L_002d69fc:
 STEP(UINT32_C(0x002d69fc)); /* 0010802f dsubu s0,zero,s0 */
 set(m,16u,lo(m,0u)-lo(m,16u));target=sx(UINT32_C(0x002d6a00));goto dispatch;
L_002d6a00:
 STEP(UINT32_C(0x002d6a00)); /* 100000f3 beq zero,zero,002d6dd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6a04));{uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(taken?UINT32_C(0x002d6dd0):UINT32_C(0x002d6a08));goto dispatch;}
L_002d6a04:
 STEP(UINT32_C(0x002d6a04)); /* a3a201d1 sb v0,0x1d1(sp) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d6a08));goto dispatch;
L_002d6a08:
 STEP(UINT32_C(0x002d6a08)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6a0c));goto dispatch;
L_002d6a0c:
 STEP(UINT32_C(0x002d6a0c)); /* 16820004 bne s4,v0,002d6a20 */
 {int taken=(lo(m,20u)!=lo(m,2u));STEP(UINT32_C(0x002d6a10));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000067)));target=sx(taken?UINT32_C(0x002d6a20):UINT32_C(0x002d6a14));goto dispatch;}
L_002d6a10:
 STEP(UINT32_C(0x002d6a10)); /* 24020067 addiu v0,zero,103 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000067)));target=sx(UINT32_C(0x002d6a14));goto dispatch;
L_002d6a14:
 STEP(UINT32_C(0x002d6a14)); /* 10000008 beq zero,zero,002d6a38 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6a18));set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000006)));target=sx(taken?UINT32_C(0x002d6a38):UINT32_C(0x002d6a1c));goto dispatch;}
L_002d6a18:
 STEP(UINT32_C(0x002d6a18)); /* 24140006 addiu s4,zero,6 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000006)));target=sx(UINT32_C(0x002d6a1c));goto dispatch;
L_002d6a1c:
 STEP(UINT32_C(0x002d6a1c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6a20));goto dispatch;
L_002d6a20:
 STEP(UINT32_C(0x002d6a20)); /* 12220003 beq s1,v0,002d6a30 */
 {int taken=(lo(m,17u)==lo(m,2u));STEP(UINT32_C(0x002d6a24));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000047)));target=sx(taken?UINT32_C(0x002d6a30):UINT32_C(0x002d6a28));goto dispatch;}
L_002d6a24:
 STEP(UINT32_C(0x002d6a24)); /* 24020047 addiu v0,zero,71 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000047)));target=sx(UINT32_C(0x002d6a28));goto dispatch;
L_002d6a28:
 STEP(UINT32_C(0x002d6a28)); /* 16220004 bne s1,v0,002d6a3c */
 {int taken=(lo(m,17u)!=lo(m,2u));STEP(UINT32_C(0x002d6a2c));set(m,2u,lo(m,23u) & UINT64_C(0x8));target=sx(taken?UINT32_C(0x002d6a3c):UINT32_C(0x002d6a30));goto dispatch;}
L_002d6a2c:
 STEP(UINT32_C(0x002d6a2c)); /* 32e20008 andi v0,s7,0x8 */
 set(m,2u,lo(m,23u) & UINT64_C(0x8));target=sx(UINT32_C(0x002d6a30));goto dispatch;
L_002d6a30:
 STEP(UINT32_C(0x002d6a30)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6a34));goto dispatch;
L_002d6a34:
 STEP(UINT32_C(0x002d6a34)); /* 0054a00a movz s4,v0,s4 */
 if(lo(m,20u)==0u)set(m,20u,lo(m,2u));target=sx(UINT32_C(0x002d6a38));goto dispatch;
L_002d6a38:
 STEP(UINT32_C(0x002d6a38)); /* 32e20008 andi v0,s7,0x8 */
 set(m,2u,lo(m,23u) & UINT64_C(0x8));target=sx(UINT32_C(0x002d6a3c));goto dispatch;
L_002d6a3c:
 STEP(UINT32_C(0x002d6a3c)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6a40));goto dispatch;
L_002d6a40:
 STEP(UINT32_C(0x002d6a40)); /* dc420000 ld v0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,2u,value64);target=sx(UINT32_C(0x002d6a44));goto dispatch;
L_002d6a44:
 STEP(UINT32_C(0x002d6a44)); /* ffa201f8 sd v0,0x1f8(sp) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001f8),&value64,8u);target=sx(UINT32_C(0x002d6a48));goto dispatch;
L_002d6a48:
 STEP(UINT32_C(0x002d6a48)); /* dfa401f8 ld a0,0x1f8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f8),&value64,8u);set(m,4u,value64);target=sx(UINT32_C(0x002d6a4c));goto dispatch;
L_002d6a4c:
 STEP(UINT32_C(0x002d6a4c)); /* 0c0b6d7a jal 002db5e8 */
 set(m,31u,UINT64_C(0x002d6a54));STEP(UINT32_C(0x002d6a50));set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002db5e8));goto dispatch;
L_002d6a50:
 STEP(UINT32_C(0x002d6a50)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6a54));goto dispatch;
L_002d6a54:
 STEP(UINT32_C(0x002d6a54)); /* 1040000e beq v0,zero,002d6a90 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6a58));/* nop */target=sx(taken?UINT32_C(0x002d6a90):UINT32_C(0x002d6a5c));goto dispatch;}
L_002d6a58:
 STEP(UINT32_C(0x002d6a58)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6a5c));goto dispatch;
L_002d6a5c:
 STEP(UINT32_C(0x002d6a5c)); /* dfa401f8 ld a0,0x1f8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f8),&value64,8u);set(m,4u,value64);target=sx(UINT32_C(0x002d6a60));goto dispatch;
L_002d6a60:
 STEP(UINT32_C(0x002d6a60)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d6a64));goto dispatch;
L_002d6a64:
 STEP(UINT32_C(0x002d6a64)); /* 0c0b46ce jal 002d1b38 */
 set(m,31u,UINT64_C(0x002d6a6c));STEP(UINT32_C(0x002d6a68));/* nop */target=sx(UINT32_C(0x002d1b38));goto dispatch;
L_002d6a68:
 STEP(UINT32_C(0x002d6a68)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6a6c));goto dispatch;
L_002d6a6c:
 STEP(UINT32_C(0x002d6a6c)); /* 04410004 regimm1 v0,002d6a80 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002d6a70));set(m,2u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d6a80):UINT32_C(0x002d6a74));goto dispatch;}
L_002d6a70:
 STEP(UINT32_C(0x002d6a70)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6a74));goto dispatch;
L_002d6a74:
 STEP(UINT32_C(0x002d6a74)); /* 2402002d addiu v0,zero,45 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000002d)));target=sx(UINT32_C(0x002d6a78));goto dispatch;
L_002d6a78:
 STEP(UINT32_C(0x002d6a78)); /* a3a201d1 sb v0,0x1d1(sp) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d6a7c));goto dispatch;
L_002d6a7c:
 STEP(UINT32_C(0x002d6a7c)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6a80));goto dispatch;
L_002d6a80:
 STEP(UINT32_C(0x002d6a80)); /* 241e0003 addiu s8,zero,3 */
 set(m,30u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002d6a84));goto dispatch;
L_002d6a84:
 STEP(UINT32_C(0x002d6a84)); /* 1000011f beq zero,zero,002d6f04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6a88));set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb690)));target=sx(taken?UINT32_C(0x002d6f04):UINT32_C(0x002d6a8c));goto dispatch;}
L_002d6a88:
 STEP(UINT32_C(0x002d6a88)); /* 2455b690 addiu s5,v0,-18800 */
 set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb690)));target=sx(UINT32_C(0x002d6a8c));goto dispatch;
L_002d6a8c:
 STEP(UINT32_C(0x002d6a8c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6a90));goto dispatch;
L_002d6a90:
 STEP(UINT32_C(0x002d6a90)); /* dfa401f8 ld a0,0x1f8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f8),&value64,8u);set(m,4u,value64);target=sx(UINT32_C(0x002d6a94));goto dispatch;
L_002d6a94:
 STEP(UINT32_C(0x002d6a94)); /* 0c0b6d8c jal 002db630 */
 set(m,31u,UINT64_C(0x002d6a9c));STEP(UINT32_C(0x002d6a98));/* nop */target=sx(UINT32_C(0x002db630));goto dispatch;
L_002d6a98:
 STEP(UINT32_C(0x002d6a98)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6a9c));goto dispatch;
L_002d6a9c:
 STEP(UINT32_C(0x002d6a9c)); /* 10400004 beq v0,zero,002d6ab0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6aa0));set(m,2u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d6ab0):UINT32_C(0x002d6aa4));goto dispatch;}
L_002d6aa0:
 STEP(UINT32_C(0x002d6aa0)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6aa4));goto dispatch;
L_002d6aa4:
 STEP(UINT32_C(0x002d6aa4)); /* 241e0003 addiu s8,zero,3 */
 set(m,30u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002d6aa8));goto dispatch;
L_002d6aa8:
 STEP(UINT32_C(0x002d6aa8)); /* 10000116 beq zero,zero,002d6f04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6aac));set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb698)));target=sx(taken?UINT32_C(0x002d6f04):UINT32_C(0x002d6ab0));goto dispatch;}
L_002d6aac:
 STEP(UINT32_C(0x002d6aac)); /* 2455b698 addiu s5,v0,-18792 */
 set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb698)));target=sx(UINT32_C(0x002d6ab0));goto dispatch;
L_002d6ab0:
 STEP(UINT32_C(0x002d6ab0)); /* 36f70100 ori s7,s7,0x100 */
 set(m,23u,lo(m,23u) | UINT64_C(0x100));target=sx(UINT32_C(0x002d6ab4));goto dispatch;
L_002d6ab4:
 STEP(UINT32_C(0x002d6ab4)); /* 8fa401e4 lw a0,0x1e4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d6ab8));goto dispatch;
L_002d6ab8:
 STEP(UINT32_C(0x002d6ab8)); /* dfa501f8 ld a1,0x1f8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f8),&value64,8u);set(m,5u,value64);target=sx(UINT32_C(0x002d6abc));goto dispatch;
L_002d6abc:
 STEP(UINT32_C(0x002d6abc)); /* 0280302d daddu a2,s4,zero */
 set(m,6u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002d6ac0));goto dispatch;
L_002d6ac0:
 STEP(UINT32_C(0x002d6ac0)); /* 02e0382d daddu a3,s7,zero */
 set(m,7u,lo(m,23u)+lo(m,0u));target=sx(UINT32_C(0x002d6ac4));goto dispatch;
L_002d6ac4:
 STEP(UINT32_C(0x002d6ac4)); /* 27a801d0 addiu t0,sp,464 */
 set(m,8u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001d0)));target=sx(UINT32_C(0x002d6ac8));goto dispatch;
L_002d6ac8:
 STEP(UINT32_C(0x002d6ac8)); /* 27a901dc addiu t1,sp,476 */
 set(m,9u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001dc)));target=sx(UINT32_C(0x002d6acc));goto dispatch;
L_002d6acc:
 STEP(UINT32_C(0x002d6acc)); /* 0220502d daddu t2,s1,zero */
 set(m,10u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d6ad0));goto dispatch;
L_002d6ad0:
 STEP(UINT32_C(0x002d6ad0)); /* 0c0b5f3a jal 002d7ce8 */
 set(m,31u,UINT64_C(0x002d6ad8));STEP(UINT32_C(0x002d6ad4));set(m,11u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001e0)));target=sx(UINT32_C(0x002d7ce8));goto dispatch;
L_002d6ad4:
 STEP(UINT32_C(0x002d6ad4)); /* 27ab01e0 addiu t3,sp,480 */
 set(m,11u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001e0)));target=sx(UINT32_C(0x002d6ad8));goto dispatch;
L_002d6ad8:
 STEP(UINT32_C(0x002d6ad8)); /* 0040a82d daddu s5,v0,zero */
 set(m,21u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d6adc));goto dispatch;
L_002d6adc:
 STEP(UINT32_C(0x002d6adc)); /* 24020067 addiu v0,zero,103 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000067)));target=sx(UINT32_C(0x002d6ae0));goto dispatch;
L_002d6ae0:
 STEP(UINT32_C(0x002d6ae0)); /* 12220003 beq s1,v0,002d6af0 */
 {int taken=(lo(m,17u)==lo(m,2u));STEP(UINT32_C(0x002d6ae4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000047)));target=sx(taken?UINT32_C(0x002d6af0):UINT32_C(0x002d6ae8));goto dispatch;}
L_002d6ae4:
 STEP(UINT32_C(0x002d6ae4)); /* 24020047 addiu v0,zero,71 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000047)));target=sx(UINT32_C(0x002d6ae8));goto dispatch;
L_002d6ae8:
 STEP(UINT32_C(0x002d6ae8)); /* 1622000d bne s1,v0,002d6b20 */
 {int taken=(lo(m,17u)!=lo(m,2u));STEP(UINT32_C(0x002d6aec));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,7u,sx(value32));target=sx(taken?UINT32_C(0x002d6b20):UINT32_C(0x002d6af0));goto dispatch;}
L_002d6aec:
 STEP(UINT32_C(0x002d6aec)); /* 8fa701dc lw a3,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d6af0));goto dispatch;
L_002d6af0:
 STEP(UINT32_C(0x002d6af0)); /* 8fa701dc lw a3,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d6af4));goto dispatch;
L_002d6af4:
 STEP(UINT32_C(0x002d6af4)); /* 28e2fffd slti v0,a3,-3 */
 set(m,2u,((int64_t)lo(m,7u)<INT64_C(-3)));target=sx(UINT32_C(0x002d6af8));goto dispatch;
L_002d6af8:
 STEP(UINT32_C(0x002d6af8)); /* 14400005 bne v0,zero,002d6b10 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6afc));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000065)));target=sx(taken?UINT32_C(0x002d6b10):UINT32_C(0x002d6b00));goto dispatch;}
L_002d6afc:
 STEP(UINT32_C(0x002d6afc)); /* 24020065 addiu v0,zero,101 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000065)));target=sx(UINT32_C(0x002d6b00));goto dispatch;
L_002d6b00:
 STEP(UINT32_C(0x002d6b00)); /* 0287102a slt v0,s4,a3 */
 set(m,2u,((int64_t)lo(m,20u)<(int64_t)lo(m,7u)));target=sx(UINT32_C(0x002d6b04));goto dispatch;
L_002d6b04:
 STEP(UINT32_C(0x002d6b04)); /* 50400006 beql v0,zero,002d6b20 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d6b08));set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000067)));target=sx(UINT32_C(0x002d6b20));}else target=sx(UINT32_C(0x002d6b0c));goto dispatch;
L_002d6b08:
 STEP(UINT32_C(0x002d6b08)); /* 24110067 addiu s1,zero,103 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000067)));target=sx(UINT32_C(0x002d6b0c));goto dispatch;
L_002d6b0c:
 STEP(UINT32_C(0x002d6b0c)); /* 24020065 addiu v0,zero,101 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000065)));target=sx(UINT32_C(0x002d6b10));goto dispatch;
L_002d6b10:
 STEP(UINT32_C(0x002d6b10)); /* 3a240067 xori a0,s1,0x67 */
 set(m,4u,lo(m,17u)^UINT64_C(0x67));target=sx(UINT32_C(0x002d6b14));goto dispatch;
L_002d6b14:
 STEP(UINT32_C(0x002d6b14)); /* 24030045 addiu v1,zero,69 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000045)));target=sx(UINT32_C(0x002d6b18));goto dispatch;
L_002d6b18:
 STEP(UINT32_C(0x002d6b18)); /* 0040882d daddu s1,v0,zero */
 set(m,17u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d6b1c));goto dispatch;
L_002d6b1c:
 STEP(UINT32_C(0x002d6b1c)); /* 0064880b movn s1,v1,a0 */
 if(lo(m,4u)!=0u)set(m,17u,lo(m,3u));target=sx(UINT32_C(0x002d6b20));goto dispatch;
L_002d6b20:
 STEP(UINT32_C(0x002d6b20)); /* 2a220066 slti v0,s1,102 */
 set(m,2u,((int64_t)lo(m,17u)<INT64_C(102)));target=sx(UINT32_C(0x002d6b24));goto dispatch;
L_002d6b24:
 STEP(UINT32_C(0x002d6b24)); /* 50400012 beql v0,zero,002d6b70 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d6b28));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000066)));target=sx(UINT32_C(0x002d6b70));}else target=sx(UINT32_C(0x002d6b2c));goto dispatch;
L_002d6b28:
 STEP(UINT32_C(0x002d6b28)); /* 24020066 addiu v0,zero,102 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000066)));target=sx(UINT32_C(0x002d6b2c));goto dispatch;
L_002d6b2c:
 STEP(UINT32_C(0x002d6b2c)); /* 24e7ffff addiu a3,a3,-1 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6b30));goto dispatch;
L_002d6b30:
 STEP(UINT32_C(0x002d6b30)); /* 0220302d daddu a2,s1,zero */
 set(m,6u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d6b34));goto dispatch;
L_002d6b34:
 STEP(UINT32_C(0x002d6b34)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002d6b38));goto dispatch;
L_002d6b38:
 STEP(UINT32_C(0x002d6b38)); /* 00e0282d daddu a1,a3,zero */
 set(m,5u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d6b3c));goto dispatch;
L_002d6b3c:
 STEP(UINT32_C(0x002d6b3c)); /* 0c0b5faa jal 002d7ea8 */
 set(m,31u,UINT64_C(0x002d6b44));STEP(UINT32_C(0x002d6b40));value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);target=sx(UINT32_C(0x002d7ea8));goto dispatch;
L_002d6b40:
 STEP(UINT32_C(0x002d6b40)); /* afa701dc sw a3,0x1dc(sp) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);target=sx(UINT32_C(0x002d6b44));goto dispatch;
L_002d6b44:
 STEP(UINT32_C(0x002d6b44)); /* afa20200 sw v0,0x200(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000200),&value32,4u);target=sx(UINT32_C(0x002d6b48));goto dispatch;
L_002d6b48:
 STEP(UINT32_C(0x002d6b48)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6b4c));goto dispatch;
L_002d6b4c:
 STEP(UINT32_C(0x002d6b4c)); /* 8fa60200 lw a2,0x200(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000200),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d6b50));goto dispatch;
L_002d6b50:
 STEP(UINT32_C(0x002d6b50)); /* 28430002 slti v1,v0,2 */
 set(m,3u,((int64_t)lo(m,2u)<INT64_C(2)));target=sx(UINT32_C(0x002d6b54));goto dispatch;
L_002d6b54:
 STEP(UINT32_C(0x002d6b54)); /* 10600004 beq v1,zero,002d6b68 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002d6b58));set(m,30u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,2u)));target=sx(taken?UINT32_C(0x002d6b68):UINT32_C(0x002d6b5c));goto dispatch;}
L_002d6b58:
 STEP(UINT32_C(0x002d6b58)); /* 00c2f021 addu s8,a2,v0 */
 set(m,30u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d6b5c));goto dispatch;
L_002d6b5c:
 STEP(UINT32_C(0x002d6b5c)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d6b60));goto dispatch;
L_002d6b60:
 STEP(UINT32_C(0x002d6b60)); /* 1040001c beq v0,zero,002d6bd4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6b64));{uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d0),&byte,1u);set(m,2u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(taken?UINT32_C(0x002d6bd4):UINT32_C(0x002d6b68));goto dispatch;}
L_002d6b64:
 STEP(UINT32_C(0x002d6b64)); /* 83a201d0 lb v0,0x1d0(sp) */
 {uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d0),&byte,1u);set(m,2u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d6b68));goto dispatch;
L_002d6b68:
 STEP(UINT32_C(0x002d6b68)); /* 10000019 beq zero,zero,002d6bd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6b6c));set(m,30u,sx((uint32_t)lo(m,30u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d6bd0):UINT32_C(0x002d6b70));goto dispatch;}
L_002d6b6c:
 STEP(UINT32_C(0x002d6b6c)); /* 27de0001 addiu s8,s8,1 */
 set(m,30u,sx((uint32_t)lo(m,30u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6b70));goto dispatch;
L_002d6b70:
 STEP(UINT32_C(0x002d6b70)); /* 1622000b bne s1,v0,002d6ba0 */
 {int taken=(lo(m,17u)!=lo(m,2u));STEP(UINT32_C(0x002d6b74));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,5u,sx(value32));target=sx(taken?UINT32_C(0x002d6ba0):UINT32_C(0x002d6b78));goto dispatch;}
L_002d6b74:
 STEP(UINT32_C(0x002d6b74)); /* 8fa501e0 lw a1,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d6b78));goto dispatch;
L_002d6b78:
 STEP(UINT32_C(0x002d6b78)); /* 18e00015 blez a3,zero,002d6bd0 */
 {int taken=((int64_t)lo(m,7u)<=0);STEP(UINT32_C(0x002d6b7c));set(m,30u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000002)));target=sx(taken?UINT32_C(0x002d6bd0):UINT32_C(0x002d6b80));goto dispatch;}
L_002d6b7c:
 STEP(UINT32_C(0x002d6b7c)); /* 269e0002 addiu s8,s4,2 */
 set(m,30u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d6b80));goto dispatch;
L_002d6b80:
 STEP(UINT32_C(0x002d6b80)); /* 16800004 bne s4,zero,002d6b94 */
 {int taken=(lo(m,20u)!=lo(m,0u));STEP(UINT32_C(0x002d6b84));set(m,30u,lo(m,7u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6b94):UINT32_C(0x002d6b88));goto dispatch;}
L_002d6b84:
 STEP(UINT32_C(0x002d6b84)); /* 00e0f02d daddu s8,a3,zero */
 set(m,30u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d6b88));goto dispatch;
L_002d6b88:
 STEP(UINT32_C(0x002d6b88)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d6b8c));goto dispatch;
L_002d6b8c:
 STEP(UINT32_C(0x002d6b8c)); /* 10400011 beq v0,zero,002d6bd4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6b90));{uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d0),&byte,1u);set(m,2u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(taken?UINT32_C(0x002d6bd4):UINT32_C(0x002d6b94));goto dispatch;}
L_002d6b90:
 STEP(UINT32_C(0x002d6b90)); /* 83a201d0 lb v0,0x1d0(sp) */
 {uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d0),&byte,1u);set(m,2u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d6b94));goto dispatch;
L_002d6b94:
 STEP(UINT32_C(0x002d6b94)); /* 00f41021 addu v0,a3,s4 */
 set(m,2u,sx((uint32_t)lo(m,7u)+(uint32_t)lo(m,20u)));target=sx(UINT32_C(0x002d6b98));goto dispatch;
L_002d6b98:
 STEP(UINT32_C(0x002d6b98)); /* 1000000d beq zero,zero,002d6bd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6b9c));set(m,30u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d6bd0):UINT32_C(0x002d6ba0));goto dispatch;}
L_002d6b9c:
 STEP(UINT32_C(0x002d6b9c)); /* 245e0001 addiu s8,v0,1 */
 set(m,30u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6ba0));goto dispatch;
L_002d6ba0:
 STEP(UINT32_C(0x002d6ba0)); /* 00e5102a slt v0,a3,a1 */
 set(m,2u,((int64_t)lo(m,7u)<(int64_t)lo(m,5u)));target=sx(UINT32_C(0x002d6ba4));goto dispatch;
L_002d6ba4:
 STEP(UINT32_C(0x002d6ba4)); /* 14400006 bne v0,zero,002d6bc0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6ba8));set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(taken?UINT32_C(0x002d6bc0):UINT32_C(0x002d6bac));goto dispatch;}
L_002d6ba8:
 STEP(UINT32_C(0x002d6ba8)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d6bac));goto dispatch;
L_002d6bac:
 STEP(UINT32_C(0x002d6bac)); /* 10400008 beq v0,zero,002d6bd0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6bb0));set(m,30u,lo(m,7u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6bd0):UINT32_C(0x002d6bb4));goto dispatch;}
L_002d6bb0:
 STEP(UINT32_C(0x002d6bb0)); /* 00e0f02d daddu s8,a3,zero */
 set(m,30u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d6bb4));goto dispatch;
L_002d6bb4:
 STEP(UINT32_C(0x002d6bb4)); /* 10000006 beq zero,zero,002d6bd0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6bb8));set(m,30u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d6bd0):UINT32_C(0x002d6bbc));goto dispatch;}
L_002d6bb8:
 STEP(UINT32_C(0x002d6bb8)); /* 24fe0001 addiu s8,a3,1 */
 set(m,30u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6bbc));goto dispatch;
L_002d6bbc:
 STEP(UINT32_C(0x002d6bbc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6bc0));goto dispatch;
L_002d6bc0:
 STEP(UINT32_C(0x002d6bc0)); /* 5ce00003 bgtzl a3,zero,002d6bd0 */
 if((int64_t)lo(m,7u)>0){STEP(UINT32_C(0x002d6bc4));set(m,30u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6bd0));}else target=sx(UINT32_C(0x002d6bc8));goto dispatch;
L_002d6bc4:
 STEP(UINT32_C(0x002d6bc4)); /* 24be0001 addiu s8,a1,1 */
 set(m,30u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6bc8));goto dispatch;
L_002d6bc8:
 STEP(UINT32_C(0x002d6bc8)); /* 00a71023 subu v0,a1,a3 */
 set(m,2u,sx((uint32_t)lo(m,5u)-(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x002d6bcc));goto dispatch;
L_002d6bcc:
 STEP(UINT32_C(0x002d6bcc)); /* 245e0002 addiu s8,v0,2 */
 set(m,30u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d6bd0));goto dispatch;
L_002d6bd0:
 STEP(UINT32_C(0x002d6bd0)); /* 83a201d0 lb v0,0x1d0(sp) */
 {uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d0),&byte,1u);set(m,2u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d6bd4));goto dispatch;
L_002d6bd4:
 STEP(UINT32_C(0x002d6bd4)); /* 104000cb beq v0,zero,002d6f04 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6bd8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000002d)));target=sx(taken?UINT32_C(0x002d6f04):UINT32_C(0x002d6bdc));goto dispatch;}
L_002d6bd8:
 STEP(UINT32_C(0x002d6bd8)); /* 2402002d addiu v0,zero,45 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000002d)));target=sx(UINT32_C(0x002d6bdc));goto dispatch;
L_002d6bdc:
 STEP(UINT32_C(0x002d6bdc)); /* 100000c9 beq zero,zero,002d6f04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6be0));{uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(taken?UINT32_C(0x002d6f04):UINT32_C(0x002d6be4));goto dispatch;}
L_002d6be0:
 STEP(UINT32_C(0x002d6be0)); /* a3a201d1 sb v0,0x1d1(sp) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d6be4));goto dispatch;
L_002d6be4:
 STEP(UINT32_C(0x002d6be4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6be8));goto dispatch;
L_002d6be8:
 STEP(UINT32_C(0x002d6be8)); /* 32e20010 andi v0,s7,0x10 */
 set(m,2u,lo(m,23u) & UINT64_C(0x10));target=sx(UINT32_C(0x002d6bec));goto dispatch;
L_002d6bec:
 STEP(UINT32_C(0x002d6bec)); /* 10400008 beq v0,zero,002d6c10 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6bf0));set(m,2u,lo(m,23u) & UINT64_C(0x40));target=sx(taken?UINT32_C(0x002d6c10):UINT32_C(0x002d6bf4));goto dispatch;}
L_002d6bf0:
 STEP(UINT32_C(0x002d6bf0)); /* 32e20040 andi v0,s7,0x40 */
 set(m,2u,lo(m,23u) & UINT64_C(0x40));target=sx(UINT32_C(0x002d6bf4));goto dispatch;
L_002d6bf4:
 STEP(UINT32_C(0x002d6bf4)); /* 02c0182d daddu v1,s6,zero */
 set(m,3u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6bf8));goto dispatch;
L_002d6bf8:
 STEP(UINT32_C(0x002d6bf8)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6bfc));goto dispatch;
L_002d6bfc:
 STEP(UINT32_C(0x002d6bfc)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6c00));goto dispatch;
L_002d6c00:
 STEP(UINT32_C(0x002d6c00)); /* 8fa301ec lw v1,0x1ec(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d6c04));goto dispatch;
L_002d6c04:
 STEP(UINT32_C(0x002d6c04)); /* 1000fed0 beq zero,zero,002d6748 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6c08));value64=lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x002d6748):UINT32_C(0x002d6c0c));goto dispatch;}
L_002d6c08:
 STEP(UINT32_C(0x002d6c08)); /* fc430000 sd v1,0x0(v0) */
 value64=lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d6c0c));goto dispatch;
L_002d6c0c:
 STEP(UINT32_C(0x002d6c0c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6c10));goto dispatch;
L_002d6c10:
 STEP(UINT32_C(0x002d6c10)); /* 10400007 beq v0,zero,002d6c30 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6c14));set(m,3u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6c30):UINT32_C(0x002d6c18));goto dispatch;}
L_002d6c14:
 STEP(UINT32_C(0x002d6c14)); /* 02c0182d daddu v1,s6,zero */
 set(m,3u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6c18));goto dispatch;
L_002d6c18:
 STEP(UINT32_C(0x002d6c18)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6c1c));goto dispatch;
L_002d6c1c:
 STEP(UINT32_C(0x002d6c1c)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6c20));goto dispatch;
L_002d6c20:
 STEP(UINT32_C(0x002d6c20)); /* 8fa401ec lw a0,0x1ec(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d6c24));goto dispatch;
L_002d6c24:
 STEP(UINT32_C(0x002d6c24)); /* 1000fec8 beq zero,zero,002d6748 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6c28));value16=(uint16_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);target=sx(taken?UINT32_C(0x002d6748):UINT32_C(0x002d6c2c));goto dispatch;}
L_002d6c28:
 STEP(UINT32_C(0x002d6c28)); /* a4440000 sh a0,0x0(v0) */
 value16=(uint16_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);target=sx(UINT32_C(0x002d6c2c));goto dispatch;
L_002d6c2c:
 STEP(UINT32_C(0x002d6c2c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6c30));goto dispatch;
L_002d6c30:
 STEP(UINT32_C(0x002d6c30)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6c34));goto dispatch;
L_002d6c34:
 STEP(UINT32_C(0x002d6c34)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6c38));goto dispatch;
L_002d6c38:
 STEP(UINT32_C(0x002d6c38)); /* 8fa501ec lw a1,0x1ec(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d6c3c));goto dispatch;
L_002d6c3c:
 STEP(UINT32_C(0x002d6c3c)); /* 1000fec2 beq zero,zero,002d6748 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6c40));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002d6748):UINT32_C(0x002d6c44));goto dispatch;}
L_002d6c40:
 STEP(UINT32_C(0x002d6c40)); /* ac450000 sw a1,0x0(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d6c44));goto dispatch;
L_002d6c44:
 STEP(UINT32_C(0x002d6c44)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6c48));goto dispatch;
L_002d6c48:
 STEP(UINT32_C(0x002d6c48)); /* 36f70010 ori s7,s7,0x10 */
 set(m,23u,lo(m,23u) | UINT64_C(0x10));target=sx(UINT32_C(0x002d6c4c));goto dispatch;
L_002d6c4c:
 STEP(UINT32_C(0x002d6c4c)); /* 32e20010 andi v0,s7,0x10 */
 set(m,2u,lo(m,23u) & UINT64_C(0x10));target=sx(UINT32_C(0x002d6c50));goto dispatch;
L_002d6c50:
 STEP(UINT32_C(0x002d6c50)); /* 10400005 beq v0,zero,002d6c68 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6c54));set(m,2u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6c68):UINT32_C(0x002d6c58));goto dispatch;}
L_002d6c54:
 STEP(UINT32_C(0x002d6c54)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6c58));goto dispatch;
L_002d6c58:
 STEP(UINT32_C(0x002d6c58)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6c5c));goto dispatch;
L_002d6c5c:
 STEP(UINT32_C(0x002d6c5c)); /* 1000000a beq zero,zero,002d6c88 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6c60));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002d6c88):UINT32_C(0x002d6c64));goto dispatch;}
L_002d6c60:
 STEP(UINT32_C(0x002d6c60)); /* dc500000 ld s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d6c64));goto dispatch;
L_002d6c64:
 STEP(UINT32_C(0x002d6c64)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6c68));goto dispatch;
L_002d6c68:
 STEP(UINT32_C(0x002d6c68)); /* 32e20040 andi v0,s7,0x40 */
 set(m,2u,lo(m,23u) & UINT64_C(0x40));target=sx(UINT32_C(0x002d6c6c));goto dispatch;
L_002d6c6c:
 STEP(UINT32_C(0x002d6c6c)); /* 10400004 beq v0,zero,002d6c80 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6c70));set(m,2u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6c80):UINT32_C(0x002d6c74));goto dispatch;}
L_002d6c70:
 STEP(UINT32_C(0x002d6c70)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6c74));goto dispatch;
L_002d6c74:
 STEP(UINT32_C(0x002d6c74)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6c78));goto dispatch;
L_002d6c78:
 STEP(UINT32_C(0x002d6c78)); /* 10000003 beq zero,zero,002d6c88 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6c7c));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);set(m,16u,value16);target=sx(taken?UINT32_C(0x002d6c88):UINT32_C(0x002d6c80));goto dispatch;}
L_002d6c7c:
 STEP(UINT32_C(0x002d6c7c)); /* 94500000 lhu s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);set(m,16u,value16);target=sx(UINT32_C(0x002d6c80));goto dispatch;
L_002d6c80:
 STEP(UINT32_C(0x002d6c80)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6c84));goto dispatch;
L_002d6c84:
 STEP(UINT32_C(0x002d6c84)); /* 9c500000 lwu s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,16u,(uint64_t)value32);target=sx(UINT32_C(0x002d6c88));goto dispatch;
L_002d6c88:
 STEP(UINT32_C(0x002d6c88)); /* 10000050 beq zero,zero,002d6dcc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6c8c));set(m,3u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6dcc):UINT32_C(0x002d6c90));goto dispatch;}
L_002d6c8c:
 STEP(UINT32_C(0x002d6c8c)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d6c90));goto dispatch;
L_002d6c90:
 STEP(UINT32_C(0x002d6c90)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6c94));goto dispatch;
L_002d6c94:
 STEP(UINT32_C(0x002d6c94)); /* 02c0182d daddu v1,s6,zero */
 set(m,3u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6c98));goto dispatch;
L_002d6c98:
 STEP(UINT32_C(0x002d6c98)); /* 2442b6a0 addiu v0,v0,-18784 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6a0)));target=sx(UINT32_C(0x002d6c9c));goto dispatch;
L_002d6c9c:
 STEP(UINT32_C(0x002d6c9c)); /* 8c700000 lw s0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d6ca0));goto dispatch;
L_002d6ca0:
 STEP(UINT32_C(0x002d6ca0)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6ca4));goto dispatch;
L_002d6ca4:
 STEP(UINT32_C(0x002d6ca4)); /* 36f70002 ori s7,s7,0x2 */
 set(m,23u,lo(m,23u) | UINT64_C(0x2));target=sx(UINT32_C(0x002d6ca8));goto dispatch;
L_002d6ca8:
 STEP(UINT32_C(0x002d6ca8)); /* afa2020c sw v0,0x20c(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000020c),&value32,4u);target=sx(UINT32_C(0x002d6cac));goto dispatch;
L_002d6cac:
 STEP(UINT32_C(0x002d6cac)); /* 24030002 addiu v1,zero,2 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d6cb0));goto dispatch;
L_002d6cb0:
 STEP(UINT32_C(0x002d6cb0)); /* 10000046 beq zero,zero,002d6dcc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6cb4));set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000078)));target=sx(taken?UINT32_C(0x002d6dcc):UINT32_C(0x002d6cb8));goto dispatch;}
L_002d6cb4:
 STEP(UINT32_C(0x002d6cb4)); /* 24110078 addiu s1,zero,120 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000078)));target=sx(UINT32_C(0x002d6cb8));goto dispatch;
L_002d6cb8:
 STEP(UINT32_C(0x002d6cb8)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6cbc));goto dispatch;
L_002d6cbc:
 STEP(UINT32_C(0x002d6cbc)); /* 8c550000 lw s5,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,21u,sx(value32));target=sx(UINT32_C(0x002d6cc0));goto dispatch;
L_002d6cc0:
 STEP(UINT32_C(0x002d6cc0)); /* 16a00003 bne s5,zero,002d6cd0 */
 {int taken=(lo(m,21u)!=lo(m,0u));STEP(UINT32_C(0x002d6cc4));set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002d6cd0):UINT32_C(0x002d6cc8));goto dispatch;}
L_002d6cc4:
 STEP(UINT32_C(0x002d6cc4)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6cc8));goto dispatch;
L_002d6cc8:
 STEP(UINT32_C(0x002d6cc8)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6ccc));goto dispatch;
L_002d6ccc:
 STEP(UINT32_C(0x002d6ccc)); /* 2455b6b8 addiu s5,v0,-18760 */
 set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6b8)));target=sx(UINT32_C(0x002d6cd0));goto dispatch;
L_002d6cd0:
 STEP(UINT32_C(0x002d6cd0)); /* 0680000d regimm0 s4,002d6d08 */
 {int taken=((int64_t)lo(m,20u)<0);STEP(UINT32_C(0x002d6cd4));set(m,5u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6d08):UINT32_C(0x002d6cd8));goto dispatch;}
L_002d6cd4:
 STEP(UINT32_C(0x002d6cd4)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d6cd8));goto dispatch;
L_002d6cd8:
 STEP(UINT32_C(0x002d6cd8)); /* 02a0202d daddu a0,s5,zero */
 set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002d6cdc));goto dispatch;
L_002d6cdc:
 STEP(UINT32_C(0x002d6cdc)); /* 0c0b693b jal 002da4ec */
 set(m,31u,UINT64_C(0x002d6ce4));STEP(UINT32_C(0x002d6ce0));set(m,6u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002da4ec));goto dispatch;
L_002d6ce0:
 STEP(UINT32_C(0x002d6ce0)); /* 0280302d daddu a2,s4,zero */
 set(m,6u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002d6ce4));goto dispatch;
L_002d6ce4:
 STEP(UINT32_C(0x002d6ce4)); /* 10400086 beq v0,zero,002d6f00 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6ce8));set(m,30u,lo(m,20u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6f00):UINT32_C(0x002d6cec));goto dispatch;}
L_002d6ce8:
 STEP(UINT32_C(0x002d6ce8)); /* 0280f02d daddu s8,s4,zero */
 set(m,30u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002d6cec));goto dispatch;
L_002d6cec:
 STEP(UINT32_C(0x002d6cec)); /* 0055f023 subu s8,v0,s5 */
 set(m,30u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,21u)));target=sx(UINT32_C(0x002d6cf0));goto dispatch;
L_002d6cf0:
 STEP(UINT32_C(0x002d6cf0)); /* 029e102a slt v0,s4,s8 */
 set(m,2u,((int64_t)lo(m,20u)<(int64_t)lo(m,30u)));target=sx(UINT32_C(0x002d6cf4));goto dispatch;
L_002d6cf4:
 STEP(UINT32_C(0x002d6cf4)); /* 50400083 beql v0,zero,002d6f04 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d6cf8));{uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d6f04));}else target=sx(UINT32_C(0x002d6cfc));goto dispatch;
L_002d6cf8:
 STEP(UINT32_C(0x002d6cf8)); /* a3a001d1 sb zero,0x1d1(sp) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d6cfc));goto dispatch;
L_002d6cfc:
 STEP(UINT32_C(0x002d6cfc)); /* 10000080 beq zero,zero,002d6f00 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6d00));set(m,30u,lo(m,20u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6f00):UINT32_C(0x002d6d04));goto dispatch;}
L_002d6d00:
 STEP(UINT32_C(0x002d6d00)); /* 0280f02d daddu s8,s4,zero */
 set(m,30u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002d6d04));goto dispatch;
L_002d6d04:
 STEP(UINT32_C(0x002d6d04)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6d08));goto dispatch;
L_002d6d08:
 STEP(UINT32_C(0x002d6d08)); /* 0c0b5743 jal 002d5d0c */
 set(m,31u,UINT64_C(0x002d6d10));STEP(UINT32_C(0x002d6d0c));set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002d5d0c));goto dispatch;
L_002d6d0c:
 STEP(UINT32_C(0x002d6d0c)); /* 02a0202d daddu a0,s5,zero */
 set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002d6d10));goto dispatch;
L_002d6d10:
 STEP(UINT32_C(0x002d6d10)); /* 1000007b beq zero,zero,002d6f00 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6d14));set(m,30u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6f00):UINT32_C(0x002d6d18));goto dispatch;}
L_002d6d14:
 STEP(UINT32_C(0x002d6d14)); /* 0040f02d daddu s8,v0,zero */
 set(m,30u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d6d18));goto dispatch;
L_002d6d18:
 STEP(UINT32_C(0x002d6d18)); /* 36f70010 ori s7,s7,0x10 */
 set(m,23u,lo(m,23u) | UINT64_C(0x10));target=sx(UINT32_C(0x002d6d1c));goto dispatch;
L_002d6d1c:
 STEP(UINT32_C(0x002d6d1c)); /* 32e20010 andi v0,s7,0x10 */
 set(m,2u,lo(m,23u) & UINT64_C(0x10));target=sx(UINT32_C(0x002d6d20));goto dispatch;
L_002d6d20:
 STEP(UINT32_C(0x002d6d20)); /* 10400005 beq v0,zero,002d6d38 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6d24));set(m,2u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6d38):UINT32_C(0x002d6d28));goto dispatch;}
L_002d6d24:
 STEP(UINT32_C(0x002d6d24)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6d28));goto dispatch;
L_002d6d28:
 STEP(UINT32_C(0x002d6d28)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6d2c));goto dispatch;
L_002d6d2c:
 STEP(UINT32_C(0x002d6d2c)); /* 1000000a beq zero,zero,002d6d58 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6d30));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002d6d58):UINT32_C(0x002d6d34));goto dispatch;}
L_002d6d30:
 STEP(UINT32_C(0x002d6d30)); /* dc500000 ld s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d6d34));goto dispatch;
L_002d6d34:
 STEP(UINT32_C(0x002d6d34)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6d38));goto dispatch;
L_002d6d38:
 STEP(UINT32_C(0x002d6d38)); /* 32e20040 andi v0,s7,0x40 */
 set(m,2u,lo(m,23u) & UINT64_C(0x40));target=sx(UINT32_C(0x002d6d3c));goto dispatch;
L_002d6d3c:
 STEP(UINT32_C(0x002d6d3c)); /* 10400004 beq v0,zero,002d6d50 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6d40));set(m,2u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6d50):UINT32_C(0x002d6d44));goto dispatch;}
L_002d6d40:
 STEP(UINT32_C(0x002d6d40)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6d44));goto dispatch;
L_002d6d44:
 STEP(UINT32_C(0x002d6d44)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6d48));goto dispatch;
L_002d6d48:
 STEP(UINT32_C(0x002d6d48)); /* 10000003 beq zero,zero,002d6d58 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6d4c));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);set(m,16u,value16);target=sx(taken?UINT32_C(0x002d6d58):UINT32_C(0x002d6d50));goto dispatch;}
L_002d6d4c:
 STEP(UINT32_C(0x002d6d4c)); /* 94500000 lhu s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);set(m,16u,value16);target=sx(UINT32_C(0x002d6d50));goto dispatch;
L_002d6d50:
 STEP(UINT32_C(0x002d6d50)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6d54));goto dispatch;
L_002d6d54:
 STEP(UINT32_C(0x002d6d54)); /* 9c500000 lwu s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,16u,(uint64_t)value32);target=sx(UINT32_C(0x002d6d58));goto dispatch;
L_002d6d58:
 STEP(UINT32_C(0x002d6d58)); /* 1000001c beq zero,zero,002d6dcc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6d5c));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d6dcc):UINT32_C(0x002d6d60));goto dispatch;}
L_002d6d5c:
 STEP(UINT32_C(0x002d6d5c)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6d60));goto dispatch;
L_002d6d60:
 STEP(UINT32_C(0x002d6d60)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6d64));goto dispatch;
L_002d6d64:
 STEP(UINT32_C(0x002d6d64)); /* 10000004 beq zero,zero,002d6d78 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6d68));set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6c0)));target=sx(taken?UINT32_C(0x002d6d78):UINT32_C(0x002d6d6c));goto dispatch;}
L_002d6d68:
 STEP(UINT32_C(0x002d6d68)); /* 2442b6c0 addiu v0,v0,-18752 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6c0)));target=sx(UINT32_C(0x002d6d6c));goto dispatch;
L_002d6d6c:
 STEP(UINT32_C(0x002d6d6c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6d70));goto dispatch;
L_002d6d70:
 STEP(UINT32_C(0x002d6d70)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6d74));goto dispatch;
L_002d6d74:
 STEP(UINT32_C(0x002d6d74)); /* 2442b6a0 addiu v0,v0,-18784 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6a0)));target=sx(UINT32_C(0x002d6d78));goto dispatch;
L_002d6d78:
 STEP(UINT32_C(0x002d6d78)); /* afa2020c sw v0,0x20c(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000020c),&value32,4u);target=sx(UINT32_C(0x002d6d7c));goto dispatch;
L_002d6d7c:
 STEP(UINT32_C(0x002d6d7c)); /* 32e20010 andi v0,s7,0x10 */
 set(m,2u,lo(m,23u) & UINT64_C(0x10));target=sx(UINT32_C(0x002d6d80));goto dispatch;
L_002d6d80:
 STEP(UINT32_C(0x002d6d80)); /* 10400005 beq v0,zero,002d6d98 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6d84));set(m,2u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6d98):UINT32_C(0x002d6d88));goto dispatch;}
L_002d6d84:
 STEP(UINT32_C(0x002d6d84)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6d88));goto dispatch;
L_002d6d88:
 STEP(UINT32_C(0x002d6d88)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6d8c));goto dispatch;
L_002d6d8c:
 STEP(UINT32_C(0x002d6d8c)); /* 1000000a beq zero,zero,002d6db8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6d90));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(taken?UINT32_C(0x002d6db8):UINT32_C(0x002d6d94));goto dispatch;}
L_002d6d90:
 STEP(UINT32_C(0x002d6d90)); /* dc500000 ld s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d6d94));goto dispatch;
L_002d6d94:
 STEP(UINT32_C(0x002d6d94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6d98));goto dispatch;
L_002d6d98:
 STEP(UINT32_C(0x002d6d98)); /* 32e20040 andi v0,s7,0x40 */
 set(m,2u,lo(m,23u) & UINT64_C(0x40));target=sx(UINT32_C(0x002d6d9c));goto dispatch;
L_002d6d9c:
 STEP(UINT32_C(0x002d6d9c)); /* 10400004 beq v0,zero,002d6db0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6da0));set(m,2u,lo(m,22u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6db0):UINT32_C(0x002d6da4));goto dispatch;}
L_002d6da0:
 STEP(UINT32_C(0x002d6da0)); /* 02c0102d daddu v0,s6,zero */
 set(m,2u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002d6da4));goto dispatch;
L_002d6da4:
 STEP(UINT32_C(0x002d6da4)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6da8));goto dispatch;
L_002d6da8:
 STEP(UINT32_C(0x002d6da8)); /* 10000003 beq zero,zero,002d6db8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6dac));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);set(m,16u,value16);target=sx(taken?UINT32_C(0x002d6db8):UINT32_C(0x002d6db0));goto dispatch;}
L_002d6dac:
 STEP(UINT32_C(0x002d6dac)); /* 94500000 lhu s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value16,2u);set(m,16u,value16);target=sx(UINT32_C(0x002d6db0));goto dispatch;
L_002d6db0:
 STEP(UINT32_C(0x002d6db0)); /* 26d60008 addiu s6,s6,8 */
 set(m,22u,sx((uint32_t)lo(m,22u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6db4));goto dispatch;
L_002d6db4:
 STEP(UINT32_C(0x002d6db4)); /* 9c500000 lwu s0,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,16u,(uint64_t)value32);target=sx(UINT32_C(0x002d6db8));goto dispatch;
L_002d6db8:
 STEP(UINT32_C(0x002d6db8)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d6dbc));goto dispatch;
L_002d6dbc:
 STEP(UINT32_C(0x002d6dbc)); /* 10400003 beq v0,zero,002d6dcc */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6dc0));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(taken?UINT32_C(0x002d6dcc):UINT32_C(0x002d6dc4));goto dispatch;}
L_002d6dc0:
 STEP(UINT32_C(0x002d6dc0)); /* 24030002 addiu v1,zero,2 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d6dc4));goto dispatch;
L_002d6dc4:
 STEP(UINT32_C(0x002d6dc4)); /* 36e20002 ori v0,s7,0x2 */
 set(m,2u,lo(m,23u) | UINT64_C(0x2));target=sx(UINT32_C(0x002d6dc8));goto dispatch;
L_002d6dc8:
 STEP(UINT32_C(0x002d6dc8)); /* 0050b80b movn s7,v0,s0 */
 if(lo(m,16u)!=0u)set(m,23u,lo(m,2u));target=sx(UINT32_C(0x002d6dcc));goto dispatch;
L_002d6dcc:
 STEP(UINT32_C(0x002d6dcc)); /* a3a001d1 sb zero,0x1d1(sp) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d6dd0));goto dispatch;
L_002d6dd0:
 STEP(UINT32_C(0x002d6dd0)); /* 06800003 regimm0 s4,002d6de0 */
 {int taken=((int64_t)lo(m,20u)<0);STEP(UINT32_C(0x002d6dd4));value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);target=sx(taken?UINT32_C(0x002d6de0):UINT32_C(0x002d6dd8));goto dispatch;}
L_002d6dd4:
 STEP(UINT32_C(0x002d6dd4)); /* afb40204 sw s4,0x204(sp) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);target=sx(UINT32_C(0x002d6dd8));goto dispatch;
L_002d6dd8:
 STEP(UINT32_C(0x002d6dd8)); /* 2402ff7f addiu v0,zero,-129 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff7f)));target=sx(UINT32_C(0x002d6ddc));goto dispatch;
L_002d6ddc:
 STEP(UINT32_C(0x002d6ddc)); /* 02e2b824 and s7,s7,v0 */
 set(m,23u,lo(m,23u)&lo(m,2u));target=sx(UINT32_C(0x002d6de0));goto dispatch;
L_002d6de0:
 STEP(UINT32_C(0x002d6de0)); /* 16000004 bne s0,zero,002d6df4 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002d6de4));set(m,21u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001bc)));target=sx(taken?UINT32_C(0x002d6df4):UINT32_C(0x002d6de8));goto dispatch;}
L_002d6de4:
 STEP(UINT32_C(0x002d6de4)); /* 27b501bc addiu s5,sp,444 */
 set(m,21u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001bc)));target=sx(UINT32_C(0x002d6de8));goto dispatch;
L_002d6de8:
 STEP(UINT32_C(0x002d6de8)); /* 8fa60204 lw a2,0x204(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d6dec));goto dispatch;
L_002d6dec:
 STEP(UINT32_C(0x002d6dec)); /* 10c0003d beq a2,zero,002d6ee4 */
 {int taken=(lo(m,6u)==lo(m,0u));STEP(UINT32_C(0x002d6df0));set(m,2u,sx((uint32_t)lo(m,29u)-(uint32_t)lo(m,21u)));target=sx(taken?UINT32_C(0x002d6ee4):UINT32_C(0x002d6df4));goto dispatch;}
L_002d6df0:
 STEP(UINT32_C(0x002d6df0)); /* 03b51023 subu v0,sp,s5 */
 set(m,2u,sx((uint32_t)lo(m,29u)-(uint32_t)lo(m,21u)));target=sx(UINT32_C(0x002d6df4));goto dispatch;
L_002d6df4:
 STEP(UINT32_C(0x002d6df4)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6df8));goto dispatch;
L_002d6df8:
 STEP(UINT32_C(0x002d6df8)); /* 10620026 beq v1,v0,002d6e94 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002d6dfc));set(m,2u,(lo(m,16u)<UINT64_C(0xa)));target=sx(taken?UINT32_C(0x002d6e94):UINT32_C(0x002d6e00));goto dispatch;}
L_002d6dfc:
 STEP(UINT32_C(0x002d6dfc)); /* 2e02000a sltiu v0,s0,10 */
 set(m,2u,(lo(m,16u)<UINT64_C(0xa)));target=sx(UINT32_C(0x002d6e00));goto dispatch;
L_002d6e00:
 STEP(UINT32_C(0x002d6e00)); /* 10600009 beq v1,zero,002d6e28 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002d6e04));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000007)));target=sx(taken?UINT32_C(0x002d6e28):UINT32_C(0x002d6e08));goto dispatch;}
L_002d6e04:
 STEP(UINT32_C(0x002d6e04)); /* 24040007 addiu a0,zero,7 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000007)));target=sx(UINT32_C(0x002d6e08));goto dispatch;
L_002d6e08:
 STEP(UINT32_C(0x002d6e08)); /* 24020002 addiu v0,zero,2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d6e0c));goto dispatch;
L_002d6e0c:
 STEP(UINT32_C(0x002d6e0c)); /* 10620028 beq v1,v0,002d6eb0 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002d6e10));set(m,2u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d6eb0):UINT32_C(0x002d6e14));goto dispatch;}
L_002d6e10:
 STEP(UINT32_C(0x002d6e10)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6e14));goto dispatch;
L_002d6e14:
 STEP(UINT32_C(0x002d6e14)); /* 2455b6d8 addiu s5,v0,-18728 */
 set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6d8)));target=sx(UINT32_C(0x002d6e18));goto dispatch;
L_002d6e18:
 STEP(UINT32_C(0x002d6e18)); /* 0c0b5743 jal 002d5d0c */
 set(m,31u,UINT64_C(0x002d6e20));STEP(UINT32_C(0x002d6e1c));set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002d5d0c));goto dispatch;
L_002d6e1c:
 STEP(UINT32_C(0x002d6e1c)); /* 02a0202d daddu a0,s5,zero */
 set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002d6e20));goto dispatch;
L_002d6e20:
 STEP(UINT32_C(0x002d6e20)); /* 10000038 beq zero,zero,002d6f04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6e24));set(m,30u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6f04):UINT32_C(0x002d6e28));goto dispatch;}
L_002d6e24:
 STEP(UINT32_C(0x002d6e24)); /* 0040f02d daddu s8,v0,zero */
 set(m,30u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d6e28));goto dispatch;
L_002d6e28:
 STEP(UINT32_C(0x002d6e28)); /* 02041024 and v0,s0,a0 */
 set(m,2u,lo(m,16u)&lo(m,4u));target=sx(UINT32_C(0x002d6e2c));goto dispatch;
L_002d6e2c:
 STEP(UINT32_C(0x002d6e2c)); /* 001080fa dsrl s0,s0,3 */
 set(m,16u,lo(m,16u)>>3u);target=sx(UINT32_C(0x002d6e30));goto dispatch;
L_002d6e30:
 STEP(UINT32_C(0x002d6e30)); /* 64420030 daddiu v0,v0,48 */
 set(m,2u,lo(m,2u)+UINT64_C(0x0000000000000030));target=sx(UINT32_C(0x002d6e34));goto dispatch;
L_002d6e34:
 STEP(UINT32_C(0x002d6e34)); /* 26b5ffff addiu s5,s5,-1 */
 set(m,21u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6e38));goto dispatch;
L_002d6e38:
 STEP(UINT32_C(0x002d6e38)); /* 304300ff andi v1,v0,0xff */
 set(m,3u,lo(m,2u) & UINT64_C(0xff));target=sx(UINT32_C(0x002d6e3c));goto dispatch;
L_002d6e3c:
 STEP(UINT32_C(0x002d6e3c)); /* 1600fffa bne s0,zero,002d6e28 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002d6e40));{uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(taken?UINT32_C(0x002d6e28):UINT32_C(0x002d6e44));goto dispatch;}
L_002d6e40:
 STEP(UINT32_C(0x002d6e40)); /* a2a30000 sb v1,0x0(s5) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d6e44));goto dispatch;
L_002d6e44:
 STEP(UINT32_C(0x002d6e44)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d6e48));goto dispatch;
L_002d6e48:
 STEP(UINT32_C(0x002d6e48)); /* 10400025 beq v0,zero,002d6ee0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6e4c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(taken?UINT32_C(0x002d6ee0):UINT32_C(0x002d6e50));goto dispatch;}
L_002d6e4c:
 STEP(UINT32_C(0x002d6e4c)); /* 24020030 addiu v0,zero,48 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002d6e50));goto dispatch;
L_002d6e50:
 STEP(UINT32_C(0x002d6e50)); /* 50620024 beql v1,v0,002d6ee4 */
 if(lo(m,3u)==lo(m,2u)){STEP(UINT32_C(0x002d6e54));set(m,2u,sx((uint32_t)lo(m,29u)-(uint32_t)lo(m,21u)));target=sx(UINT32_C(0x002d6ee4));}else target=sx(UINT32_C(0x002d6e58));goto dispatch;
L_002d6e54:
 STEP(UINT32_C(0x002d6e54)); /* 03b51023 subu v0,sp,s5 */
 set(m,2u,sx((uint32_t)lo(m,29u)-(uint32_t)lo(m,21u)));target=sx(UINT32_C(0x002d6e58));goto dispatch;
L_002d6e58:
 STEP(UINT32_C(0x002d6e58)); /* 26b5ffff addiu s5,s5,-1 */
 set(m,21u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6e5c));goto dispatch;
L_002d6e5c:
 STEP(UINT32_C(0x002d6e5c)); /* 10000020 beq zero,zero,002d6ee0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6e60));{uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(taken?UINT32_C(0x002d6ee0):UINT32_C(0x002d6e64));goto dispatch;}
L_002d6e60:
 STEP(UINT32_C(0x002d6e60)); /* a2a20000 sb v0,0x0(s5) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d6e64));goto dispatch;
L_002d6e64:
 STEP(UINT32_C(0x002d6e64)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6e68));goto dispatch;
L_002d6e68:
 STEP(UINT32_C(0x002d6e68)); /* 0c0b9972 jal 002e65c8 */
 set(m,31u,UINT64_C(0x002d6e70));STEP(UINT32_C(0x002d6e6c));set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002e65c8));goto dispatch;
L_002d6e6c:
 STEP(UINT32_C(0x002d6e6c)); /* 2405000a addiu a1,zero,10 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002d6e70));goto dispatch;
L_002d6e70:
 STEP(UINT32_C(0x002d6e70)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6e74));goto dispatch;
L_002d6e74:
 STEP(UINT32_C(0x002d6e74)); /* 64420030 daddiu v0,v0,48 */
 set(m,2u,lo(m,2u)+UINT64_C(0x0000000000000030));target=sx(UINT32_C(0x002d6e78));goto dispatch;
L_002d6e78:
 STEP(UINT32_C(0x002d6e78)); /* 26b5ffff addiu s5,s5,-1 */
 set(m,21u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6e7c));goto dispatch;
L_002d6e7c:
 STEP(UINT32_C(0x002d6e7c)); /* 304200ff andi v0,v0,0xff */
 set(m,2u,lo(m,2u) & UINT64_C(0xff));target=sx(UINT32_C(0x002d6e80));goto dispatch;
L_002d6e80:
 STEP(UINT32_C(0x002d6e80)); /* 2405000a addiu a1,zero,10 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002d6e84));goto dispatch;
L_002d6e84:
 STEP(UINT32_C(0x002d6e84)); /* 0c0b9812 jal 002e6048 */
 set(m,31u,UINT64_C(0x002d6e8c));STEP(UINT32_C(0x002d6e88));{uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002e6048));goto dispatch;
L_002d6e88:
 STEP(UINT32_C(0x002d6e88)); /* a2a20000 sb v0,0x0(s5) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d6e8c));goto dispatch;
L_002d6e8c:
 STEP(UINT32_C(0x002d6e8c)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d6e90));goto dispatch;
L_002d6e90:
 STEP(UINT32_C(0x002d6e90)); /* 2e02000a sltiu v0,s0,10 */
 set(m,2u,(lo(m,16u)<UINT64_C(0xa)));target=sx(UINT32_C(0x002d6e94));goto dispatch;
L_002d6e94:
 STEP(UINT32_C(0x002d6e94)); /* 1040fff4 beq v0,zero,002d6e68 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6e98));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6e68):UINT32_C(0x002d6e9c));goto dispatch;}
L_002d6e98:
 STEP(UINT32_C(0x002d6e98)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6e9c));goto dispatch;
L_002d6e9c:
 STEP(UINT32_C(0x002d6e9c)); /* 66020030 daddiu v0,s0,48 */
 set(m,2u,lo(m,16u)+UINT64_C(0x0000000000000030));target=sx(UINT32_C(0x002d6ea0));goto dispatch;
L_002d6ea0:
 STEP(UINT32_C(0x002d6ea0)); /* 26b5ffff addiu s5,s5,-1 */
 set(m,21u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6ea4));goto dispatch;
L_002d6ea4:
 STEP(UINT32_C(0x002d6ea4)); /* 304200ff andi v0,v0,0xff */
 set(m,2u,lo(m,2u) & UINT64_C(0xff));target=sx(UINT32_C(0x002d6ea8));goto dispatch;
L_002d6ea8:
 STEP(UINT32_C(0x002d6ea8)); /* 1000000d beq zero,zero,002d6ee0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6eac));{uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(taken?UINT32_C(0x002d6ee0):UINT32_C(0x002d6eb0));goto dispatch;}
L_002d6eac:
 STEP(UINT32_C(0x002d6eac)); /* a2a20000 sb v0,0x0(s5) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d6eb0));goto dispatch;
L_002d6eb0:
 STEP(UINT32_C(0x002d6eb0)); /* 2404000f addiu a0,zero,15 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000f)));target=sx(UINT32_C(0x002d6eb4));goto dispatch;
L_002d6eb4:
 STEP(UINT32_C(0x002d6eb4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6eb8));goto dispatch;
L_002d6eb8:
 STEP(UINT32_C(0x002d6eb8)); /* 8fa3020c lw v1,0x20c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000020c),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d6ebc));goto dispatch;
L_002d6ebc:
 STEP(UINT32_C(0x002d6ebc)); /* 02041024 and v0,s0,a0 */
 set(m,2u,lo(m,16u)&lo(m,4u));target=sx(UINT32_C(0x002d6ec0));goto dispatch;
L_002d6ec0:
 STEP(UINT32_C(0x002d6ec0)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002d6ec4));goto dispatch;
L_002d6ec4:
 STEP(UINT32_C(0x002d6ec4)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x002d6ec8));goto dispatch;
L_002d6ec8:
 STEP(UINT32_C(0x002d6ec8)); /* 26b5ffff addiu s5,s5,-1 */
 set(m,21u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6ecc));goto dispatch;
L_002d6ecc:
 STEP(UINT32_C(0x002d6ecc)); /* 00621021 addu v0,v1,v0 */
 set(m,2u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d6ed0));goto dispatch;
L_002d6ed0:
 STEP(UINT32_C(0x002d6ed0)); /* 0010813a dsrl s0,s0,4 */
 set(m,16u,lo(m,16u)>>4u);target=sx(UINT32_C(0x002d6ed4));goto dispatch;
L_002d6ed4:
 STEP(UINT32_C(0x002d6ed4)); /* 90430000 lbu v1,0x0(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002d6ed8));goto dispatch;
L_002d6ed8:
 STEP(UINT32_C(0x002d6ed8)); /* 1600fff7 bne s0,zero,002d6eb8 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002d6edc));{uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(taken?UINT32_C(0x002d6eb8):UINT32_C(0x002d6ee0));goto dispatch;}
L_002d6edc:
 STEP(UINT32_C(0x002d6edc)); /* a2a30000 sb v1,0x0(s5) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d6ee0));goto dispatch;
L_002d6ee0:
 STEP(UINT32_C(0x002d6ee0)); /* 03b51023 subu v0,sp,s5 */
 set(m,2u,sx((uint32_t)lo(m,29u)-(uint32_t)lo(m,21u)));target=sx(UINT32_C(0x002d6ee4));goto dispatch;
L_002d6ee4:
 STEP(UINT32_C(0x002d6ee4)); /* 10000007 beq zero,zero,002d6f04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6ee8));set(m,30u,sx((uint32_t)lo(m,2u)+UINT32_C(0x000001bc)));target=sx(taken?UINT32_C(0x002d6f04):UINT32_C(0x002d6eec));goto dispatch;}
L_002d6ee8:
 STEP(UINT32_C(0x002d6ee8)); /* 245e01bc addiu s8,v0,444 */
 set(m,30u,sx((uint32_t)lo(m,2u)+UINT32_C(0x000001bc)));target=sx(UINT32_C(0x002d6eec));goto dispatch;
L_002d6eec:
 STEP(UINT32_C(0x002d6eec)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6ef0));goto dispatch;
L_002d6ef0:
 STEP(UINT32_C(0x002d6ef0)); /* 12200363 beq s1,zero,002d7c80 */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002d6ef4));set(m,21u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(taken?UINT32_C(0x002d7c80):UINT32_C(0x002d6ef8));goto dispatch;}
L_002d6ef4:
 STEP(UINT32_C(0x002d6ef4)); /* 27b50060 addiu s5,sp,96 */
 set(m,21u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002d6ef8));goto dispatch;
L_002d6ef8:
 STEP(UINT32_C(0x002d6ef8)); /* 241e0001 addiu s8,zero,1 */
 set(m,30u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6efc));goto dispatch;
L_002d6efc:
 STEP(UINT32_C(0x002d6efc)); /* a2b10000 sb s1,0x0(s5) */
 {uint8_t byte=(uint8_t)lo(m,17u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d6f00));goto dispatch;
L_002d6f00:
 STEP(UINT32_C(0x002d6f00)); /* a3a001d1 sb zero,0x1d1(sp) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);}target=sx(UINT32_C(0x002d6f04));goto dispatch;
L_002d6f04:
 STEP(UINT32_C(0x002d6f04)); /* 8fa50204 lw a1,0x204(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d6f08));goto dispatch;
L_002d6f08:
 STEP(UINT32_C(0x002d6f08)); /* 03c0202d daddu a0,s8,zero */
 set(m,4u,lo(m,30u)+lo(m,0u));target=sx(UINT32_C(0x002d6f0c));goto dispatch;
L_002d6f0c:
 STEP(UINT32_C(0x002d6f0c)); /* 03c0302d daddu a2,s8,zero */
 set(m,6u,lo(m,30u)+lo(m,0u));target=sx(UINT32_C(0x002d6f10));goto dispatch;
L_002d6f10:
 STEP(UINT32_C(0x002d6f10)); /* 83a301d1 lb v1,0x1d1(sp) */
 {uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);set(m,3u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002d6f14));goto dispatch;
L_002d6f14:
 STEP(UINT32_C(0x002d6f14)); /* 0085102a slt v0,a0,a1 */
 set(m,2u,((int64_t)lo(m,4u)<(int64_t)lo(m,5u)));target=sx(UINT32_C(0x002d6f18));goto dispatch;
L_002d6f18:
 STEP(UINT32_C(0x002d6f18)); /* 93a401d1 lbu a0,0x1d1(sp) */
 {uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);set(m,4u,byte);}target=sx(UINT32_C(0x002d6f1c));goto dispatch;
L_002d6f1c:
 STEP(UINT32_C(0x002d6f1c)); /* 00c2280a movz a1,a2,v0 */
 if(lo(m,2u)==0u)set(m,5u,lo(m,6u));target=sx(UINT32_C(0x002d6f20));goto dispatch;
L_002d6f20:
 STEP(UINT32_C(0x002d6f20)); /* afbe0208 sw s8,0x208(sp) */
 value32=(uint32_t)lo(m,30u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);target=sx(UINT32_C(0x002d6f24));goto dispatch;
L_002d6f24:
 STEP(UINT32_C(0x002d6f24)); /* 10600004 beq v1,zero,002d6f38 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002d6f28));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);target=sx(taken?UINT32_C(0x002d6f38):UINT32_C(0x002d6f2c));goto dispatch;}
L_002d6f28:
 STEP(UINT32_C(0x002d6f28)); /* afa50208 sw a1,0x208(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);target=sx(UINT32_C(0x002d6f2c));goto dispatch;
L_002d6f2c:
 STEP(UINT32_C(0x002d6f2c)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6f30));goto dispatch;
L_002d6f30:
 STEP(UINT32_C(0x002d6f30)); /* 10000005 beq zero,zero,002d6f48 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6f34));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);target=sx(taken?UINT32_C(0x002d6f48):UINT32_C(0x002d6f38));goto dispatch;}
L_002d6f34:
 STEP(UINT32_C(0x002d6f34)); /* afa50208 sw a1,0x208(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);target=sx(UINT32_C(0x002d6f38));goto dispatch;
L_002d6f38:
 STEP(UINT32_C(0x002d6f38)); /* 8fa30208 lw v1,0x208(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d6f3c));goto dispatch;
L_002d6f3c:
 STEP(UINT32_C(0x002d6f3c)); /* 32e20002 andi v0,s7,0x2 */
 set(m,2u,lo(m,23u) & UINT64_C(0x2));target=sx(UINT32_C(0x002d6f40));goto dispatch;
L_002d6f40:
 STEP(UINT32_C(0x002d6f40)); /* 00431821 addu v1,v0,v1 */
 set(m,3u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d6f44));goto dispatch;
L_002d6f44:
 STEP(UINT32_C(0x002d6f44)); /* afa30208 sw v1,0x208(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);target=sx(UINT32_C(0x002d6f48));goto dispatch;
L_002d6f48:
 STEP(UINT32_C(0x002d6f48)); /* 32e50084 andi a1,s7,0x84 */
 set(m,5u,lo(m,23u) & UINT64_C(0x84));target=sx(UINT32_C(0x002d6f4c));goto dispatch;
L_002d6f4c:
 STEP(UINT32_C(0x002d6f4c)); /* 14a0003a bne a1,zero,002d7038 */
 {int taken=(lo(m,5u)!=lo(m,0u));STEP(UINT32_C(0x002d6f50));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000210),&value32,4u);target=sx(taken?UINT32_C(0x002d7038):UINT32_C(0x002d6f54));goto dispatch;}
L_002d6f50:
 STEP(UINT32_C(0x002d6f50)); /* afa50210 sw a1,0x210(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000210),&value32,4u);target=sx(UINT32_C(0x002d6f54));goto dispatch;
L_002d6f54:
 STEP(UINT32_C(0x002d6f54)); /* 8fa601f0 lw a2,0x1f0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d6f58));goto dispatch;
L_002d6f58:
 STEP(UINT32_C(0x002d6f58)); /* 8fa20208 lw v0,0x208(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6f5c));goto dispatch;
L_002d6f5c:
 STEP(UINT32_C(0x002d6f5c)); /* 00c28023 subu s0,a2,v0 */
 set(m,16u,sx((uint32_t)lo(m,6u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d6f60));goto dispatch;
L_002d6f60:
 STEP(UINT32_C(0x002d6f60)); /* 1a000035 blez s0,zero,002d7038 */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d6f64));set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(taken?UINT32_C(0x002d7038):UINT32_C(0x002d6f68));goto dispatch;}
L_002d6f64:
 STEP(UINT32_C(0x002d6f64)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d6f68));goto dispatch;
L_002d6f68:
 STEP(UINT32_C(0x002d6f68)); /* 1440001f bne v0,zero,002d6fe8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6f6c));set(m,7u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d6fe8):UINT32_C(0x002d6f70));goto dispatch;}
L_002d6f6c:
 STEP(UINT32_C(0x002d6f6c)); /* 3c070055 lui a3,zero,0x55 */
 set(m,7u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d6f70));goto dispatch;
L_002d6f70:
 STEP(UINT32_C(0x002d6f70)); /* 24060010 addiu a2,zero,16 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6f74));goto dispatch;
L_002d6f74:
 STEP(UINT32_C(0x002d6f74)); /* 24f4b670 addiu s4,a3,-18832 */
 set(m,20u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb670)));target=sx(UINT32_C(0x002d6f78));goto dispatch;
L_002d6f78:
 STEP(UINT32_C(0x002d6f78)); /* ae660004 sw a2,0x4(s3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d6f7c));goto dispatch;
L_002d6f7c:
 STEP(UINT32_C(0x002d6f7c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6f80));goto dispatch;
L_002d6f80:
 STEP(UINT32_C(0x002d6f80)); /* ae740000 sw s4,0x0(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d6f84));goto dispatch;
L_002d6f84:
 STEP(UINT32_C(0x002d6f84)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6f88));goto dispatch;
L_002d6f88:
 STEP(UINT32_C(0x002d6f88)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6f8c));goto dispatch;
L_002d6f8c:
 STEP(UINT32_C(0x002d6f8c)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d6f90));goto dispatch;
L_002d6f90:
 STEP(UINT32_C(0x002d6f90)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d6f94));goto dispatch;
L_002d6f94:
 STEP(UINT32_C(0x002d6f94)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6f98));goto dispatch;
L_002d6f98:
 STEP(UINT32_C(0x002d6f98)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d6f9c));goto dispatch;
L_002d6f9c:
 STEP(UINT32_C(0x002d6f9c)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d6fa0));goto dispatch;
L_002d6fa0:
 STEP(UINT32_C(0x002d6fa0)); /* 1480000b bne a0,zero,002d6fd0 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d6fa4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d6fd0):UINT32_C(0x002d6fa8));goto dispatch;}
L_002d6fa4:
 STEP(UINT32_C(0x002d6fa4)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d6fa8));goto dispatch;
L_002d6fa8:
 STEP(UINT32_C(0x002d6fa8)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d6fac));goto dispatch;
L_002d6fac:
 STEP(UINT32_C(0x002d6fac)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6fb0));goto dispatch;
L_002d6fb0:
 STEP(UINT32_C(0x002d6fb0)); /* 7fa60220 sq a2,0x220(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000220),m->gpr[6],16u);target=sx(UINT32_C(0x002d6fb4));goto dispatch;
L_002d6fb4:
 STEP(UINT32_C(0x002d6fb4)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d6fbc));STEP(UINT32_C(0x002d6fb8));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d6fb8:
 STEP(UINT32_C(0x002d6fb8)); /* 7fa70230 sq a3,0x230(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6fbc));goto dispatch;
L_002d6fbc:
 STEP(UINT32_C(0x002d6fbc)); /* 7ba60220 lq a2,0x220(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000220),q,16u);memcpy(m->gpr[6],q,16u);}target=sx(UINT32_C(0x002d6fc0));goto dispatch;
L_002d6fc0:
 STEP(UINT32_C(0x002d6fc0)); /* 14400337 bne v0,zero,002d7ca0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6fc4));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(taken?UINT32_C(0x002d7ca0):UINT32_C(0x002d6fc8));goto dispatch;}
L_002d6fc4:
 STEP(UINT32_C(0x002d6fc4)); /* 7ba70230 lq a3,0x230(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x002d6fc8));goto dispatch;
L_002d6fc8:
 STEP(UINT32_C(0x002d6fc8)); /* 27a30020 addiu v1,sp,32 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d6fcc));goto dispatch;
L_002d6fcc:
 STEP(UINT32_C(0x002d6fcc)); /* 0060982d daddu s3,v1,zero */
 set(m,19u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d6fd0));goto dispatch;
L_002d6fd0:
 STEP(UINT32_C(0x002d6fd0)); /* 2610fff0 addiu s0,s0,-16 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d6fd4));goto dispatch;
L_002d6fd4:
 STEP(UINT32_C(0x002d6fd4)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d6fd8));goto dispatch;
L_002d6fd8:
 STEP(UINT32_C(0x002d6fd8)); /* 5040ffe9 beql v0,zero,002d6f80 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d6fdc));value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d6f80));}else target=sx(UINT32_C(0x002d6fe0));goto dispatch;
L_002d6fdc:
 STEP(UINT32_C(0x002d6fdc)); /* ae660004 sw a2,0x4(s3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d6fe0));goto dispatch;
L_002d6fe0:
 STEP(UINT32_C(0x002d6fe0)); /* 10000002 beq zero,zero,002d6fec */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6fe4));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d6fec):UINT32_C(0x002d6fe8));goto dispatch;}
L_002d6fe4:
 STEP(UINT32_C(0x002d6fe4)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d6fe8));goto dispatch;
L_002d6fe8:
 STEP(UINT32_C(0x002d6fe8)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d6fec));goto dispatch;
L_002d6fec:
 STEP(UINT32_C(0x002d6fec)); /* 24e2b670 addiu v0,a3,-18832 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb670)));target=sx(UINT32_C(0x002d6ff0));goto dispatch;
L_002d6ff0:
 STEP(UINT32_C(0x002d6ff0)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d6ff4));goto dispatch;
L_002d6ff4:
 STEP(UINT32_C(0x002d6ff4)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6ff8));goto dispatch;
L_002d6ff8:
 STEP(UINT32_C(0x002d6ff8)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d6ffc));goto dispatch;
L_002d6ffc:
 STEP(UINT32_C(0x002d6ffc)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7000));goto dispatch;
L_002d7000:
 STEP(UINT32_C(0x002d7000)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7004));goto dispatch;
L_002d7004:
 STEP(UINT32_C(0x002d7004)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d7008));goto dispatch;
L_002d7008:
 STEP(UINT32_C(0x002d7008)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d700c));goto dispatch;
L_002d700c:
 STEP(UINT32_C(0x002d700c)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7010));goto dispatch;
L_002d7010:
 STEP(UINT32_C(0x002d7010)); /* 14800008 bne a0,zero,002d7034 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7014));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7034):UINT32_C(0x002d7018));goto dispatch;}
L_002d7014:
 STEP(UINT32_C(0x002d7014)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7018));goto dispatch;
L_002d7018:
 STEP(UINT32_C(0x002d7018)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d701c));goto dispatch;
L_002d701c:
 STEP(UINT32_C(0x002d701c)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7024));STEP(UINT32_C(0x002d7020));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7020:
 STEP(UINT32_C(0x002d7020)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7024));goto dispatch;
L_002d7024:
 STEP(UINT32_C(0x002d7024)); /* 1440031f bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7028));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d702c));goto dispatch;}
L_002d7028:
 STEP(UINT32_C(0x002d7028)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d702c));goto dispatch;
L_002d702c:
 STEP(UINT32_C(0x002d702c)); /* 27a40020 addiu a0,sp,32 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7030));goto dispatch;
L_002d7030:
 STEP(UINT32_C(0x002d7030)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d7034));goto dispatch;
L_002d7034:
 STEP(UINT32_C(0x002d7034)); /* 93a401d1 lbu a0,0x1d1(sp) */
 {uint8_t byte;READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d1),&byte,1u);set(m,4u,byte);}target=sx(UINT32_C(0x002d7038));goto dispatch;
L_002d7038:
 STEP(UINT32_C(0x002d7038)); /* 10800015 beq a0,zero,002d7090 */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x002d703c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d7090):UINT32_C(0x002d7040));goto dispatch;}
L_002d703c:
 STEP(UINT32_C(0x002d703c)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7040));goto dispatch;
L_002d7040:
 STEP(UINT32_C(0x002d7040)); /* 27a301d1 addiu v1,sp,465 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001d1)));target=sx(UINT32_C(0x002d7044));goto dispatch;
L_002d7044:
 STEP(UINT32_C(0x002d7044)); /* ae620004 sw v0,0x4(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7048));goto dispatch;
L_002d7048:
 STEP(UINT32_C(0x002d7048)); /* ae630000 sw v1,0x0(s3) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d704c));goto dispatch;
L_002d704c:
 STEP(UINT32_C(0x002d704c)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7050));goto dispatch;
L_002d7050:
 STEP(UINT32_C(0x002d7050)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7054));goto dispatch;
L_002d7054:
 STEP(UINT32_C(0x002d7054)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7058));goto dispatch;
L_002d7058:
 STEP(UINT32_C(0x002d7058)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d705c));goto dispatch;
L_002d705c:
 STEP(UINT32_C(0x002d705c)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7060));goto dispatch;
L_002d7060:
 STEP(UINT32_C(0x002d7060)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d7064));goto dispatch;
L_002d7064:
 STEP(UINT32_C(0x002d7064)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7068));goto dispatch;
L_002d7068:
 STEP(UINT32_C(0x002d7068)); /* 14800022 bne a0,zero,002d70f4 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d706c));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d70f4):UINT32_C(0x002d7070));goto dispatch;}
L_002d706c:
 STEP(UINT32_C(0x002d706c)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7070));goto dispatch;
L_002d7070:
 STEP(UINT32_C(0x002d7070)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7074));goto dispatch;
L_002d7074:
 STEP(UINT32_C(0x002d7074)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d707c));STEP(UINT32_C(0x002d7078));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7078:
 STEP(UINT32_C(0x002d7078)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d707c));goto dispatch;
L_002d707c:
 STEP(UINT32_C(0x002d707c)); /* 14400309 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7080));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7084));goto dispatch;}
L_002d7080:
 STEP(UINT32_C(0x002d7080)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7084));goto dispatch;
L_002d7084:
 STEP(UINT32_C(0x002d7084)); /* 27a50020 addiu a1,sp,32 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7088));goto dispatch;
L_002d7088:
 STEP(UINT32_C(0x002d7088)); /* 1000001a beq zero,zero,002d70f4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d708c));set(m,19u,lo(m,5u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d70f4):UINT32_C(0x002d7090));goto dispatch;}
L_002d708c:
 STEP(UINT32_C(0x002d708c)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d7090));goto dispatch;
L_002d7090:
 STEP(UINT32_C(0x002d7090)); /* 32e20002 andi v0,s7,0x2 */
 set(m,2u,lo(m,23u) & UINT64_C(0x2));target=sx(UINT32_C(0x002d7094));goto dispatch;
L_002d7094:
 STEP(UINT32_C(0x002d7094)); /* 10400017 beq v0,zero,002d70f4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d7098));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(taken?UINT32_C(0x002d70f4):UINT32_C(0x002d709c));goto dispatch;}
L_002d7098:
 STEP(UINT32_C(0x002d7098)); /* 24020030 addiu v0,zero,48 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002d709c));goto dispatch;
L_002d709c:
 STEP(UINT32_C(0x002d709c)); /* 24040002 addiu a0,zero,2 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d70a0));goto dispatch;
L_002d70a0:
 STEP(UINT32_C(0x002d70a0)); /* a3a201c0 sb v0,0x1c0(sp) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001c0),&byte,1u);}target=sx(UINT32_C(0x002d70a4));goto dispatch;
L_002d70a4:
 STEP(UINT32_C(0x002d70a4)); /* 27a301c0 addiu v1,sp,448 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001c0)));target=sx(UINT32_C(0x002d70a8));goto dispatch;
L_002d70a8:
 STEP(UINT32_C(0x002d70a8)); /* a3b101c1 sb s1,0x1c1(sp) */
 {uint8_t byte=(uint8_t)lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001c1),&byte,1u);}target=sx(UINT32_C(0x002d70ac));goto dispatch;
L_002d70ac:
 STEP(UINT32_C(0x002d70ac)); /* ae640004 sw a0,0x4(s3) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d70b0));goto dispatch;
L_002d70b0:
 STEP(UINT32_C(0x002d70b0)); /* ae630000 sw v1,0x0(s3) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d70b4));goto dispatch;
L_002d70b4:
 STEP(UINT32_C(0x002d70b4)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d70b8));goto dispatch;
L_002d70b8:
 STEP(UINT32_C(0x002d70b8)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d70bc));goto dispatch;
L_002d70bc:
 STEP(UINT32_C(0x002d70bc)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d70c0));goto dispatch;
L_002d70c0:
 STEP(UINT32_C(0x002d70c0)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d70c4));goto dispatch;
L_002d70c4:
 STEP(UINT32_C(0x002d70c4)); /* 24420002 addiu v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d70c8));goto dispatch;
L_002d70c8:
 STEP(UINT32_C(0x002d70c8)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d70cc));goto dispatch;
L_002d70cc:
 STEP(UINT32_C(0x002d70cc)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d70d0));goto dispatch;
L_002d70d0:
 STEP(UINT32_C(0x002d70d0)); /* 14800008 bne a0,zero,002d70f4 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d70d4));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d70f4):UINT32_C(0x002d70d8));goto dispatch;}
L_002d70d4:
 STEP(UINT32_C(0x002d70d4)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d70d8));goto dispatch;
L_002d70d8:
 STEP(UINT32_C(0x002d70d8)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d70dc));goto dispatch;
L_002d70dc:
 STEP(UINT32_C(0x002d70dc)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d70e4));STEP(UINT32_C(0x002d70e0));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d70e0:
 STEP(UINT32_C(0x002d70e0)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d70e4));goto dispatch;
L_002d70e4:
 STEP(UINT32_C(0x002d70e4)); /* 144002ef bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d70e8));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d70ec));goto dispatch;}
L_002d70e8:
 STEP(UINT32_C(0x002d70e8)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d70ec));goto dispatch;
L_002d70ec:
 STEP(UINT32_C(0x002d70ec)); /* 27a60020 addiu a2,sp,32 */
 set(m,6u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d70f0));goto dispatch;
L_002d70f0:
 STEP(UINT32_C(0x002d70f0)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d70f4));goto dispatch;
L_002d70f4:
 STEP(UINT32_C(0x002d70f4)); /* 8fa30210 lw v1,0x210(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000210),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d70f8));goto dispatch;
L_002d70f8:
 STEP(UINT32_C(0x002d70f8)); /* 24020080 addiu v0,zero,128 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x002d70fc));goto dispatch;
L_002d70fc:
 STEP(UINT32_C(0x002d70fc)); /* 1462003a bne v1,v0,002d71e8 */
 {int taken=(lo(m,3u)!=lo(m,2u));STEP(UINT32_C(0x002d7100));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x002d71e8):UINT32_C(0x002d7104));goto dispatch;}
L_002d7100:
 STEP(UINT32_C(0x002d7100)); /* 8fa40204 lw a0,0x204(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7104));goto dispatch;
L_002d7104:
 STEP(UINT32_C(0x002d7104)); /* 8fa401f0 lw a0,0x1f0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7108));goto dispatch;
L_002d7108:
 STEP(UINT32_C(0x002d7108)); /* 8fa50208 lw a1,0x208(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d710c));goto dispatch;
L_002d710c:
 STEP(UINT32_C(0x002d710c)); /* 00858023 subu s0,a0,a1 */
 set(m,16u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002d7110));goto dispatch;
L_002d7110:
 STEP(UINT32_C(0x002d7110)); /* 1a000035 blez s0,zero,002d71e8 */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d7114));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x002d71e8):UINT32_C(0x002d7118));goto dispatch;}
L_002d7114:
 STEP(UINT32_C(0x002d7114)); /* 8fa40204 lw a0,0x204(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7118));goto dispatch;
L_002d7118:
 STEP(UINT32_C(0x002d7118)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d711c));goto dispatch;
L_002d711c:
 STEP(UINT32_C(0x002d711c)); /* 1440001e bne v0,zero,002d7198 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7120));set(m,7u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d7198):UINT32_C(0x002d7124));goto dispatch;}
L_002d7120:
 STEP(UINT32_C(0x002d7120)); /* 3c070055 lui a3,zero,0x55 */
 set(m,7u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d7124));goto dispatch;
L_002d7124:
 STEP(UINT32_C(0x002d7124)); /* 24060010 addiu a2,zero,16 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7128));goto dispatch;
L_002d7128:
 STEP(UINT32_C(0x002d7128)); /* 24f4b680 addiu s4,a3,-18816 */
 set(m,20u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d712c));goto dispatch;
L_002d712c:
 STEP(UINT32_C(0x002d712c)); /* ae660004 sw a2,0x4(s3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7130));goto dispatch;
L_002d7130:
 STEP(UINT32_C(0x002d7130)); /* ae740000 sw s4,0x0(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7134));goto dispatch;
L_002d7134:
 STEP(UINT32_C(0x002d7134)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7138));goto dispatch;
L_002d7138:
 STEP(UINT32_C(0x002d7138)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d713c));goto dispatch;
L_002d713c:
 STEP(UINT32_C(0x002d713c)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7140));goto dispatch;
L_002d7140:
 STEP(UINT32_C(0x002d7140)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7144));goto dispatch;
L_002d7144:
 STEP(UINT32_C(0x002d7144)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7148));goto dispatch;
L_002d7148:
 STEP(UINT32_C(0x002d7148)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d714c));goto dispatch;
L_002d714c:
 STEP(UINT32_C(0x002d714c)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7150));goto dispatch;
L_002d7150:
 STEP(UINT32_C(0x002d7150)); /* 1480000b bne a0,zero,002d7180 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7154));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7180):UINT32_C(0x002d7158));goto dispatch;}
L_002d7154:
 STEP(UINT32_C(0x002d7154)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7158));goto dispatch;
L_002d7158:
 STEP(UINT32_C(0x002d7158)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d715c));goto dispatch;
L_002d715c:
 STEP(UINT32_C(0x002d715c)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7160));goto dispatch;
L_002d7160:
 STEP(UINT32_C(0x002d7160)); /* 7fa60220 sq a2,0x220(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000220),m->gpr[6],16u);target=sx(UINT32_C(0x002d7164));goto dispatch;
L_002d7164:
 STEP(UINT32_C(0x002d7164)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d716c));STEP(UINT32_C(0x002d7168));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7168:
 STEP(UINT32_C(0x002d7168)); /* 7fa70230 sq a3,0x230(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d716c));goto dispatch;
L_002d716c:
 STEP(UINT32_C(0x002d716c)); /* 7ba60220 lq a2,0x220(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000220),q,16u);memcpy(m->gpr[6],q,16u);}target=sx(UINT32_C(0x002d7170));goto dispatch;
L_002d7170:
 STEP(UINT32_C(0x002d7170)); /* 144002cb bne v0,zero,002d7ca0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7174));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(taken?UINT32_C(0x002d7ca0):UINT32_C(0x002d7178));goto dispatch;}
L_002d7174:
 STEP(UINT32_C(0x002d7174)); /* 7ba70230 lq a3,0x230(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x002d7178));goto dispatch;
L_002d7178:
 STEP(UINT32_C(0x002d7178)); /* 27a20020 addiu v0,sp,32 */
 set(m,2u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d717c));goto dispatch;
L_002d717c:
 STEP(UINT32_C(0x002d717c)); /* 0040982d daddu s3,v0,zero */
 set(m,19u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d7180));goto dispatch;
L_002d7180:
 STEP(UINT32_C(0x002d7180)); /* 2610fff0 addiu s0,s0,-16 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d7184));goto dispatch;
L_002d7184:
 STEP(UINT32_C(0x002d7184)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d7188));goto dispatch;
L_002d7188:
 STEP(UINT32_C(0x002d7188)); /* 5040ffe9 beql v0,zero,002d7130 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d718c));value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7130));}else target=sx(UINT32_C(0x002d7190));goto dispatch;
L_002d718c:
 STEP(UINT32_C(0x002d718c)); /* ae660004 sw a2,0x4(s3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7190));goto dispatch;
L_002d7190:
 STEP(UINT32_C(0x002d7190)); /* 10000002 beq zero,zero,002d719c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7194));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d719c):UINT32_C(0x002d7198));goto dispatch;}
L_002d7194:
 STEP(UINT32_C(0x002d7194)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7198));goto dispatch;
L_002d7198:
 STEP(UINT32_C(0x002d7198)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d719c));goto dispatch;
L_002d719c:
 STEP(UINT32_C(0x002d719c)); /* 24e2b680 addiu v0,a3,-18816 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d71a0));goto dispatch;
L_002d71a0:
 STEP(UINT32_C(0x002d71a0)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d71a4));goto dispatch;
L_002d71a4:
 STEP(UINT32_C(0x002d71a4)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d71a8));goto dispatch;
L_002d71a8:
 STEP(UINT32_C(0x002d71a8)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d71ac));goto dispatch;
L_002d71ac:
 STEP(UINT32_C(0x002d71ac)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d71b0));goto dispatch;
L_002d71b0:
 STEP(UINT32_C(0x002d71b0)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d71b4));goto dispatch;
L_002d71b4:
 STEP(UINT32_C(0x002d71b4)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d71b8));goto dispatch;
L_002d71b8:
 STEP(UINT32_C(0x002d71b8)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d71bc));goto dispatch;
L_002d71bc:
 STEP(UINT32_C(0x002d71bc)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d71c0));goto dispatch;
L_002d71c0:
 STEP(UINT32_C(0x002d71c0)); /* 14800008 bne a0,zero,002d71e4 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d71c4));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d71e4):UINT32_C(0x002d71c8));goto dispatch;}
L_002d71c4:
 STEP(UINT32_C(0x002d71c4)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d71c8));goto dispatch;
L_002d71c8:
 STEP(UINT32_C(0x002d71c8)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d71cc));goto dispatch;
L_002d71cc:
 STEP(UINT32_C(0x002d71cc)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d71d4));STEP(UINT32_C(0x002d71d0));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d71d0:
 STEP(UINT32_C(0x002d71d0)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d71d4));goto dispatch;
L_002d71d4:
 STEP(UINT32_C(0x002d71d4)); /* 144002b3 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d71d8));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d71dc));goto dispatch;}
L_002d71d8:
 STEP(UINT32_C(0x002d71d8)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d71dc));goto dispatch;
L_002d71dc:
 STEP(UINT32_C(0x002d71dc)); /* 27a30020 addiu v1,sp,32 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d71e0));goto dispatch;
L_002d71e0:
 STEP(UINT32_C(0x002d71e0)); /* 0060982d daddu s3,v1,zero */
 set(m,19u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d71e4));goto dispatch;
L_002d71e4:
 STEP(UINT32_C(0x002d71e4)); /* 8fa40204 lw a0,0x204(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d71e8));goto dispatch;
L_002d71e8:
 STEP(UINT32_C(0x002d71e8)); /* 009e8023 subu s0,a0,s8 */
 set(m,16u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,30u)));target=sx(UINT32_C(0x002d71ec));goto dispatch;
L_002d71ec:
 STEP(UINT32_C(0x002d71ec)); /* 1a000036 blez s0,zero,002d72c8 */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d71f0));set(m,2u,lo(m,23u) & UINT64_C(0x100));target=sx(taken?UINT32_C(0x002d72c8):UINT32_C(0x002d71f4));goto dispatch;}
L_002d71f0:
 STEP(UINT32_C(0x002d71f0)); /* 32e20100 andi v0,s7,0x100 */
 set(m,2u,lo(m,23u) & UINT64_C(0x100));target=sx(UINT32_C(0x002d71f4));goto dispatch;
L_002d71f4:
 STEP(UINT32_C(0x002d71f4)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d71f8));goto dispatch;
L_002d71f8:
 STEP(UINT32_C(0x002d71f8)); /* 1440001f bne v0,zero,002d7278 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d71fc));set(m,7u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d7278):UINT32_C(0x002d7200));goto dispatch;}
L_002d71fc:
 STEP(UINT32_C(0x002d71fc)); /* 3c070055 lui a3,zero,0x55 */
 set(m,7u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d7200));goto dispatch;
L_002d7200:
 STEP(UINT32_C(0x002d7200)); /* 24060010 addiu a2,zero,16 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7204));goto dispatch;
L_002d7204:
 STEP(UINT32_C(0x002d7204)); /* 24f4b680 addiu s4,a3,-18816 */
 set(m,20u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d7208));goto dispatch;
L_002d7208:
 STEP(UINT32_C(0x002d7208)); /* ae660004 sw a2,0x4(s3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d720c));goto dispatch;
L_002d720c:
 STEP(UINT32_C(0x002d720c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d7210));goto dispatch;
L_002d7210:
 STEP(UINT32_C(0x002d7210)); /* ae740000 sw s4,0x0(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7214));goto dispatch;
L_002d7214:
 STEP(UINT32_C(0x002d7214)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7218));goto dispatch;
L_002d7218:
 STEP(UINT32_C(0x002d7218)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d721c));goto dispatch;
L_002d721c:
 STEP(UINT32_C(0x002d721c)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7220));goto dispatch;
L_002d7220:
 STEP(UINT32_C(0x002d7220)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7224));goto dispatch;
L_002d7224:
 STEP(UINT32_C(0x002d7224)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7228));goto dispatch;
L_002d7228:
 STEP(UINT32_C(0x002d7228)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d722c));goto dispatch;
L_002d722c:
 STEP(UINT32_C(0x002d722c)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7230));goto dispatch;
L_002d7230:
 STEP(UINT32_C(0x002d7230)); /* 1480000b bne a0,zero,002d7260 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7234));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7260):UINT32_C(0x002d7238));goto dispatch;}
L_002d7234:
 STEP(UINT32_C(0x002d7234)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7238));goto dispatch;
L_002d7238:
 STEP(UINT32_C(0x002d7238)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d723c));goto dispatch;
L_002d723c:
 STEP(UINT32_C(0x002d723c)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7240));goto dispatch;
L_002d7240:
 STEP(UINT32_C(0x002d7240)); /* 7fa60220 sq a2,0x220(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000220),m->gpr[6],16u);target=sx(UINT32_C(0x002d7244));goto dispatch;
L_002d7244:
 STEP(UINT32_C(0x002d7244)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d724c));STEP(UINT32_C(0x002d7248));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7248:
 STEP(UINT32_C(0x002d7248)); /* 7fa70230 sq a3,0x230(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d724c));goto dispatch;
L_002d724c:
 STEP(UINT32_C(0x002d724c)); /* 7ba60220 lq a2,0x220(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000220),q,16u);memcpy(m->gpr[6],q,16u);}target=sx(UINT32_C(0x002d7250));goto dispatch;
L_002d7250:
 STEP(UINT32_C(0x002d7250)); /* 14400293 bne v0,zero,002d7ca0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7254));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(taken?UINT32_C(0x002d7ca0):UINT32_C(0x002d7258));goto dispatch;}
L_002d7254:
 STEP(UINT32_C(0x002d7254)); /* 7ba70230 lq a3,0x230(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x002d7258));goto dispatch;
L_002d7258:
 STEP(UINT32_C(0x002d7258)); /* 27a50020 addiu a1,sp,32 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d725c));goto dispatch;
L_002d725c:
 STEP(UINT32_C(0x002d725c)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d7260));goto dispatch;
L_002d7260:
 STEP(UINT32_C(0x002d7260)); /* 2610fff0 addiu s0,s0,-16 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d7264));goto dispatch;
L_002d7264:
 STEP(UINT32_C(0x002d7264)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d7268));goto dispatch;
L_002d7268:
 STEP(UINT32_C(0x002d7268)); /* 5040ffe9 beql v0,zero,002d7210 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d726c));value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7210));}else target=sx(UINT32_C(0x002d7270));goto dispatch;
L_002d726c:
 STEP(UINT32_C(0x002d726c)); /* ae660004 sw a2,0x4(s3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7270));goto dispatch;
L_002d7270:
 STEP(UINT32_C(0x002d7270)); /* 10000002 beq zero,zero,002d727c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7274));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d727c):UINT32_C(0x002d7278));goto dispatch;}
L_002d7274:
 STEP(UINT32_C(0x002d7274)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7278));goto dispatch;
L_002d7278:
 STEP(UINT32_C(0x002d7278)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d727c));goto dispatch;
L_002d727c:
 STEP(UINT32_C(0x002d727c)); /* 24e2b680 addiu v0,a3,-18816 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d7280));goto dispatch;
L_002d7280:
 STEP(UINT32_C(0x002d7280)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7284));goto dispatch;
L_002d7284:
 STEP(UINT32_C(0x002d7284)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7288));goto dispatch;
L_002d7288:
 STEP(UINT32_C(0x002d7288)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d728c));goto dispatch;
L_002d728c:
 STEP(UINT32_C(0x002d728c)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7290));goto dispatch;
L_002d7290:
 STEP(UINT32_C(0x002d7290)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7294));goto dispatch;
L_002d7294:
 STEP(UINT32_C(0x002d7294)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d7298));goto dispatch;
L_002d7298:
 STEP(UINT32_C(0x002d7298)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d729c));goto dispatch;
L_002d729c:
 STEP(UINT32_C(0x002d729c)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d72a0));goto dispatch;
L_002d72a0:
 STEP(UINT32_C(0x002d72a0)); /* 14800008 bne a0,zero,002d72c4 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d72a4));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d72c4):UINT32_C(0x002d72a8));goto dispatch;}
L_002d72a4:
 STEP(UINT32_C(0x002d72a4)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d72a8));goto dispatch;
L_002d72a8:
 STEP(UINT32_C(0x002d72a8)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d72ac));goto dispatch;
L_002d72ac:
 STEP(UINT32_C(0x002d72ac)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d72b4));STEP(UINT32_C(0x002d72b0));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d72b0:
 STEP(UINT32_C(0x002d72b0)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d72b4));goto dispatch;
L_002d72b4:
 STEP(UINT32_C(0x002d72b4)); /* 1440027b bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d72b8));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d72bc));goto dispatch;}
L_002d72b8:
 STEP(UINT32_C(0x002d72b8)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d72bc));goto dispatch;
L_002d72bc:
 STEP(UINT32_C(0x002d72bc)); /* 27a60020 addiu a2,sp,32 */
 set(m,6u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d72c0));goto dispatch;
L_002d72c0:
 STEP(UINT32_C(0x002d72c0)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d72c4));goto dispatch;
L_002d72c4:
 STEP(UINT32_C(0x002d72c4)); /* 32e20100 andi v0,s7,0x100 */
 set(m,2u,lo(m,23u) & UINT64_C(0x100));target=sx(UINT32_C(0x002d72c8));goto dispatch;
L_002d72c8:
 STEP(UINT32_C(0x002d72c8)); /* 54400009 bnel v0,zero,002d72f0 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d72cc));set(m,2u,((int64_t)lo(m,17u)<INT64_C(102)));target=sx(UINT32_C(0x002d72f0));}else target=sx(UINT32_C(0x002d72d0));goto dispatch;
L_002d72cc:
 STEP(UINT32_C(0x002d72cc)); /* 2a220066 slti v0,s1,102 */
 set(m,2u,((int64_t)lo(m,17u)<INT64_C(102)));target=sx(UINT32_C(0x002d72d0));goto dispatch;
L_002d72d0:
 STEP(UINT32_C(0x002d72d0)); /* ae7e0004 sw s8,0x4(s3) */
 value32=(uint32_t)lo(m,30u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d72d4));goto dispatch;
L_002d72d4:
 STEP(UINT32_C(0x002d72d4)); /* ae750000 sw s5,0x0(s3) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d72d8));goto dispatch;
L_002d72d8:
 STEP(UINT32_C(0x002d72d8)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d72dc));goto dispatch;
L_002d72dc:
 STEP(UINT32_C(0x002d72dc)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d72e0));goto dispatch;
L_002d72e0:
 STEP(UINT32_C(0x002d72e0)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d72e4));goto dispatch;
L_002d72e4:
 STEP(UINT32_C(0x002d72e4)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d72e8));goto dispatch;
L_002d72e8:
 STEP(UINT32_C(0x002d72e8)); /* 1000020f beq zero,zero,002d7b28 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d72ec));set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,30u)));target=sx(taken?UINT32_C(0x002d7b28):UINT32_C(0x002d72f0));goto dispatch;}
L_002d72ec:
 STEP(UINT32_C(0x002d72ec)); /* 007e1821 addu v1,v1,s8 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,30u)));target=sx(UINT32_C(0x002d72f0));goto dispatch;
L_002d72f0:
 STEP(UINT32_C(0x002d72f0)); /* 14400181 bne v0,zero,002d78f8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d72f4));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d78f8):UINT32_C(0x002d72f8));goto dispatch;}
L_002d72f4:
 STEP(UINT32_C(0x002d72f4)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d72f8));goto dispatch;
L_002d72f8:
 STEP(UINT32_C(0x002d72f8)); /* dfa401f8 ld a0,0x1f8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f8),&value64,8u);set(m,4u,value64);target=sx(UINT32_C(0x002d72fc));goto dispatch;
L_002d72fc:
 STEP(UINT32_C(0x002d72fc)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d7300));goto dispatch;
L_002d7300:
 STEP(UINT32_C(0x002d7300)); /* 0c0b46ce jal 002d1b38 */
 set(m,31u,UINT64_C(0x002d7308));STEP(UINT32_C(0x002d7304));/* nop */target=sx(UINT32_C(0x002d1b38));goto dispatch;
L_002d7304:
 STEP(UINT32_C(0x002d7304)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d7308));goto dispatch;
L_002d7308:
 STEP(UINT32_C(0x002d7308)); /* 1440005f bne v0,zero,002d7488 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d730c));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,3u,sx(value32));target=sx(taken?UINT32_C(0x002d7488):UINT32_C(0x002d7310));goto dispatch;}
L_002d730c:
 STEP(UINT32_C(0x002d730c)); /* 8fa301dc lw v1,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7310));goto dispatch;
L_002d7310:
 STEP(UINT32_C(0x002d7310)); /* 24100001 addiu s0,zero,1 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7314));goto dispatch;
L_002d7314:
 STEP(UINT32_C(0x002d7314)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d7318));goto dispatch;
L_002d7318:
 STEP(UINT32_C(0x002d7318)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d731c));goto dispatch;
L_002d731c:
 STEP(UINT32_C(0x002d731c)); /* 2442b6f8 addiu v0,v0,-18696 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6f8)));target=sx(UINT32_C(0x002d7320));goto dispatch;
L_002d7320:
 STEP(UINT32_C(0x002d7320)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7324));goto dispatch;
L_002d7324:
 STEP(UINT32_C(0x002d7324)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7328));goto dispatch;
L_002d7328:
 STEP(UINT32_C(0x002d7328)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d732c));goto dispatch;
L_002d732c:
 STEP(UINT32_C(0x002d732c)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7330));goto dispatch;
L_002d7330:
 STEP(UINT32_C(0x002d7330)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7334));goto dispatch;
L_002d7334:
 STEP(UINT32_C(0x002d7334)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7338));goto dispatch;
L_002d7338:
 STEP(UINT32_C(0x002d7338)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d733c));goto dispatch;
L_002d733c:
 STEP(UINT32_C(0x002d733c)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7340));goto dispatch;
L_002d7340:
 STEP(UINT32_C(0x002d7340)); /* 14800008 bne a0,zero,002d7364 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7344));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7364):UINT32_C(0x002d7348));goto dispatch;}
L_002d7344:
 STEP(UINT32_C(0x002d7344)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7348));goto dispatch;
L_002d7348:
 STEP(UINT32_C(0x002d7348)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d734c));goto dispatch;
L_002d734c:
 STEP(UINT32_C(0x002d734c)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7354));STEP(UINT32_C(0x002d7350));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7350:
 STEP(UINT32_C(0x002d7350)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7354));goto dispatch;
L_002d7354:
 STEP(UINT32_C(0x002d7354)); /* 14400253 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7358));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d735c));goto dispatch;}
L_002d7358:
 STEP(UINT32_C(0x002d7358)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d735c));goto dispatch;
L_002d735c:
 STEP(UINT32_C(0x002d735c)); /* 27a30020 addiu v1,sp,32 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7360));goto dispatch;
L_002d7360:
 STEP(UINT32_C(0x002d7360)); /* 0060982d daddu s3,v1,zero */
 set(m,19u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d7364));goto dispatch;
L_002d7364:
 STEP(UINT32_C(0x002d7364)); /* 8fa201dc lw v0,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7368));goto dispatch;
L_002d7368:
 STEP(UINT32_C(0x002d7368)); /* 8fa301e0 lw v1,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d736c));goto dispatch;
L_002d736c:
 STEP(UINT32_C(0x002d736c)); /* 0043102a slt v0,v0,v1 */
 set(m,2u,((int64_t)lo(m,2u)<(int64_t)lo(m,3u)));target=sx(UINT32_C(0x002d7370));goto dispatch;
L_002d7370:
 STEP(UINT32_C(0x002d7370)); /* 54400005 bnel v0,zero,002d7388 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d7374));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7388));}else target=sx(UINT32_C(0x002d7378));goto dispatch;
L_002d7374:
 STEP(UINT32_C(0x002d7374)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7378));goto dispatch;
L_002d7378:
 STEP(UINT32_C(0x002d7378)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d737c));goto dispatch;
L_002d737c:
 STEP(UINT32_C(0x002d737c)); /* 104001f7 beq v0,zero,002d7b5c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d7380));set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(taken?UINT32_C(0x002d7b5c):UINT32_C(0x002d7384));goto dispatch;}
L_002d7380:
 STEP(UINT32_C(0x002d7380)); /* 32e20004 andi v0,s7,0x4 */
 set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(UINT32_C(0x002d7384));goto dispatch;
L_002d7384:
 STEP(UINT32_C(0x002d7384)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7388));goto dispatch;
L_002d7388:
 STEP(UINT32_C(0x002d7388)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d738c));goto dispatch;
L_002d738c:
 STEP(UINT32_C(0x002d738c)); /* 8fa401f4 lw a0,0x1f4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7390));goto dispatch;
L_002d7390:
 STEP(UINT32_C(0x002d7390)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7394));goto dispatch;
L_002d7394:
 STEP(UINT32_C(0x002d7394)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7398));goto dispatch;
L_002d7398:
 STEP(UINT32_C(0x002d7398)); /* ae640000 sw a0,0x0(s3) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d739c));goto dispatch;
L_002d739c:
 STEP(UINT32_C(0x002d739c)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d73a0));goto dispatch;
L_002d73a0:
 STEP(UINT32_C(0x002d73a0)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d73a4));goto dispatch;
L_002d73a4:
 STEP(UINT32_C(0x002d73a4)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d73a8));goto dispatch;
L_002d73a8:
 STEP(UINT32_C(0x002d73a8)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d73ac));goto dispatch;
L_002d73ac:
 STEP(UINT32_C(0x002d73ac)); /* 14800008 bne a0,zero,002d73d0 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d73b0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d73d0):UINT32_C(0x002d73b4));goto dispatch;}
L_002d73b0:
 STEP(UINT32_C(0x002d73b0)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d73b4));goto dispatch;
L_002d73b4:
 STEP(UINT32_C(0x002d73b4)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d73b8));goto dispatch;
L_002d73b8:
 STEP(UINT32_C(0x002d73b8)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d73c0));STEP(UINT32_C(0x002d73bc));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d73bc:
 STEP(UINT32_C(0x002d73bc)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d73c0));goto dispatch;
L_002d73c0:
 STEP(UINT32_C(0x002d73c0)); /* 14400238 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d73c4));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d73c8));goto dispatch;}
L_002d73c4:
 STEP(UINT32_C(0x002d73c4)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d73c8));goto dispatch;
L_002d73c8:
 STEP(UINT32_C(0x002d73c8)); /* 27a50020 addiu a1,sp,32 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d73cc));goto dispatch;
L_002d73cc:
 STEP(UINT32_C(0x002d73cc)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d73d0));goto dispatch;
L_002d73d0:
 STEP(UINT32_C(0x002d73d0)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d73d4));goto dispatch;
L_002d73d4:
 STEP(UINT32_C(0x002d73d4)); /* 2450ffff addiu s0,v0,-1 */
 set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d73d8));goto dispatch;
L_002d73d8:
 STEP(UINT32_C(0x002d73d8)); /* 1a0001e0 blez s0,zero,002d7b5c */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d73dc));set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(taken?UINT32_C(0x002d7b5c):UINT32_C(0x002d73e0));goto dispatch;}
L_002d73dc:
 STEP(UINT32_C(0x002d73dc)); /* 32e20004 andi v0,s7,0x4 */
 set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(UINT32_C(0x002d73e0));goto dispatch;
L_002d73e0:
 STEP(UINT32_C(0x002d73e0)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d73e4));goto dispatch;
L_002d73e4:
 STEP(UINT32_C(0x002d73e4)); /* 1440001c bne v0,zero,002d7458 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d73e8));set(m,7u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d7458):UINT32_C(0x002d73ec));goto dispatch;}
L_002d73e8:
 STEP(UINT32_C(0x002d73e8)); /* 3c070055 lui a3,zero,0x55 */
 set(m,7u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d73ec));goto dispatch;
L_002d73ec:
 STEP(UINT32_C(0x002d73ec)); /* 24140010 addiu s4,zero,16 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d73f0));goto dispatch;
L_002d73f0:
 STEP(UINT32_C(0x002d73f0)); /* 24f1b680 addiu s1,a3,-18816 */
 set(m,17u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d73f4));goto dispatch;
L_002d73f4:
 STEP(UINT32_C(0x002d73f4)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d73f8));goto dispatch;
L_002d73f8:
 STEP(UINT32_C(0x002d73f8)); /* ae710000 sw s1,0x0(s3) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d73fc));goto dispatch;
L_002d73fc:
 STEP(UINT32_C(0x002d73fc)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7400));goto dispatch;
L_002d7400:
 STEP(UINT32_C(0x002d7400)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7404));goto dispatch;
L_002d7404:
 STEP(UINT32_C(0x002d7404)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7408));goto dispatch;
L_002d7408:
 STEP(UINT32_C(0x002d7408)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d740c));goto dispatch;
L_002d740c:
 STEP(UINT32_C(0x002d740c)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7410));goto dispatch;
L_002d7410:
 STEP(UINT32_C(0x002d7410)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d7414));goto dispatch;
L_002d7414:
 STEP(UINT32_C(0x002d7414)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7418));goto dispatch;
L_002d7418:
 STEP(UINT32_C(0x002d7418)); /* 14800009 bne a0,zero,002d7440 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d741c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7440):UINT32_C(0x002d7420));goto dispatch;}
L_002d741c:
 STEP(UINT32_C(0x002d741c)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7420));goto dispatch;
L_002d7420:
 STEP(UINT32_C(0x002d7420)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7424));goto dispatch;
L_002d7424:
 STEP(UINT32_C(0x002d7424)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7428));goto dispatch;
L_002d7428:
 STEP(UINT32_C(0x002d7428)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7430));STEP(UINT32_C(0x002d742c));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d742c:
 STEP(UINT32_C(0x002d742c)); /* 7fa70230 sq a3,0x230(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d7430));goto dispatch;
L_002d7430:
 STEP(UINT32_C(0x002d7430)); /* 1440021b bne v0,zero,002d7ca0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7434));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(taken?UINT32_C(0x002d7ca0):UINT32_C(0x002d7438));goto dispatch;}
L_002d7434:
 STEP(UINT32_C(0x002d7434)); /* 7ba70230 lq a3,0x230(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x002d7438));goto dispatch;
L_002d7438:
 STEP(UINT32_C(0x002d7438)); /* 27a60020 addiu a2,sp,32 */
 set(m,6u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d743c));goto dispatch;
L_002d743c:
 STEP(UINT32_C(0x002d743c)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d7440));goto dispatch;
L_002d7440:
 STEP(UINT32_C(0x002d7440)); /* 2610fff0 addiu s0,s0,-16 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d7444));goto dispatch;
L_002d7444:
 STEP(UINT32_C(0x002d7444)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d7448));goto dispatch;
L_002d7448:
 STEP(UINT32_C(0x002d7448)); /* 5040ffeb beql v0,zero,002d73f8 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d744c));value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d73f8));}else target=sx(UINT32_C(0x002d7450));goto dispatch;
L_002d744c:
 STEP(UINT32_C(0x002d744c)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7450));goto dispatch;
L_002d7450:
 STEP(UINT32_C(0x002d7450)); /* 10000002 beq zero,zero,002d745c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7454));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d745c):UINT32_C(0x002d7458));goto dispatch;}
L_002d7454:
 STEP(UINT32_C(0x002d7454)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7458));goto dispatch;
L_002d7458:
 STEP(UINT32_C(0x002d7458)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d745c));goto dispatch;
L_002d745c:
 STEP(UINT32_C(0x002d745c)); /* 24e2b680 addiu v0,a3,-18816 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d7460));goto dispatch;
L_002d7460:
 STEP(UINT32_C(0x002d7460)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7464));goto dispatch;
L_002d7464:
 STEP(UINT32_C(0x002d7464)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7468));goto dispatch;
L_002d7468:
 STEP(UINT32_C(0x002d7468)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d746c));goto dispatch;
L_002d746c:
 STEP(UINT32_C(0x002d746c)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7470));goto dispatch;
L_002d7470:
 STEP(UINT32_C(0x002d7470)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7474));goto dispatch;
L_002d7474:
 STEP(UINT32_C(0x002d7474)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d7478));goto dispatch;
L_002d7478:
 STEP(UINT32_C(0x002d7478)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d747c));goto dispatch;
L_002d747c:
 STEP(UINT32_C(0x002d747c)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7480));goto dispatch;
L_002d7480:
 STEP(UINT32_C(0x002d7480)); /* 100001ac beq zero,zero,002d7b34 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7484));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7b34):UINT32_C(0x002d7488));goto dispatch;}
L_002d7484:
 STEP(UINT32_C(0x002d7484)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7488));goto dispatch;
L_002d7488:
 STEP(UINT32_C(0x002d7488)); /* 1c600079 bgtz v1,zero,002d7670 */
 {int taken=((int64_t)lo(m,3u)>0);STEP(UINT32_C(0x002d748c));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7670):UINT32_C(0x002d7490));goto dispatch;}
L_002d748c:
 STEP(UINT32_C(0x002d748c)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7490));goto dispatch;
L_002d7490:
 STEP(UINT32_C(0x002d7490)); /* 24100001 addiu s0,zero,1 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7494));goto dispatch;
L_002d7494:
 STEP(UINT32_C(0x002d7494)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d7498));goto dispatch;
L_002d7498:
 STEP(UINT32_C(0x002d7498)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d749c));goto dispatch;
L_002d749c:
 STEP(UINT32_C(0x002d749c)); /* 2442b6f8 addiu v0,v0,-18696 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6f8)));target=sx(UINT32_C(0x002d74a0));goto dispatch;
L_002d74a0:
 STEP(UINT32_C(0x002d74a0)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d74a4));goto dispatch;
L_002d74a4:
 STEP(UINT32_C(0x002d74a4)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d74a8));goto dispatch;
L_002d74a8:
 STEP(UINT32_C(0x002d74a8)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d74ac));goto dispatch;
L_002d74ac:
 STEP(UINT32_C(0x002d74ac)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d74b0));goto dispatch;
L_002d74b0:
 STEP(UINT32_C(0x002d74b0)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d74b4));goto dispatch;
L_002d74b4:
 STEP(UINT32_C(0x002d74b4)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d74b8));goto dispatch;
L_002d74b8:
 STEP(UINT32_C(0x002d74b8)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d74bc));goto dispatch;
L_002d74bc:
 STEP(UINT32_C(0x002d74bc)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d74c0));goto dispatch;
L_002d74c0:
 STEP(UINT32_C(0x002d74c0)); /* 14800008 bne a0,zero,002d74e4 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d74c4));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d74e4):UINT32_C(0x002d74c8));goto dispatch;}
L_002d74c4:
 STEP(UINT32_C(0x002d74c4)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d74c8));goto dispatch;
L_002d74c8:
 STEP(UINT32_C(0x002d74c8)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d74cc));goto dispatch;
L_002d74cc:
 STEP(UINT32_C(0x002d74cc)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d74d4));STEP(UINT32_C(0x002d74d0));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d74d0:
 STEP(UINT32_C(0x002d74d0)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d74d4));goto dispatch;
L_002d74d4:
 STEP(UINT32_C(0x002d74d4)); /* 144001f3 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d74d8));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d74dc));goto dispatch;}
L_002d74d8:
 STEP(UINT32_C(0x002d74d8)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d74dc));goto dispatch;
L_002d74dc:
 STEP(UINT32_C(0x002d74dc)); /* 27a30020 addiu v1,sp,32 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d74e0));goto dispatch;
L_002d74e0:
 STEP(UINT32_C(0x002d74e0)); /* 0060982d daddu s3,v1,zero */
 set(m,19u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d74e4));goto dispatch;
L_002d74e4:
 STEP(UINT32_C(0x002d74e4)); /* 8fa201dc lw v0,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d74e8));goto dispatch;
L_002d74e8:
 STEP(UINT32_C(0x002d74e8)); /* 54400005 bnel v0,zero,002d7500 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d74ec));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7500));}else target=sx(UINT32_C(0x002d74f0));goto dispatch;
L_002d74ec:
 STEP(UINT32_C(0x002d74ec)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d74f0));goto dispatch;
L_002d74f0:
 STEP(UINT32_C(0x002d74f0)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d74f4));goto dispatch;
L_002d74f4:
 STEP(UINT32_C(0x002d74f4)); /* 10400199 beq v0,zero,002d7b5c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d74f8));set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(taken?UINT32_C(0x002d7b5c):UINT32_C(0x002d74fc));goto dispatch;}
L_002d74f8:
 STEP(UINT32_C(0x002d74f8)); /* 32e20004 andi v0,s7,0x4 */
 set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(UINT32_C(0x002d74fc));goto dispatch;
L_002d74fc:
 STEP(UINT32_C(0x002d74fc)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7500));goto dispatch;
L_002d7500:
 STEP(UINT32_C(0x002d7500)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7504));goto dispatch;
L_002d7504:
 STEP(UINT32_C(0x002d7504)); /* 8fa401f4 lw a0,0x1f4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7508));goto dispatch;
L_002d7508:
 STEP(UINT32_C(0x002d7508)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d750c));goto dispatch;
L_002d750c:
 STEP(UINT32_C(0x002d750c)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7510));goto dispatch;
L_002d7510:
 STEP(UINT32_C(0x002d7510)); /* ae640000 sw a0,0x0(s3) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7514));goto dispatch;
L_002d7514:
 STEP(UINT32_C(0x002d7514)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7518));goto dispatch;
L_002d7518:
 STEP(UINT32_C(0x002d7518)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d751c));goto dispatch;
L_002d751c:
 STEP(UINT32_C(0x002d751c)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d7520));goto dispatch;
L_002d7520:
 STEP(UINT32_C(0x002d7520)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7524));goto dispatch;
L_002d7524:
 STEP(UINT32_C(0x002d7524)); /* 14800008 bne a0,zero,002d7548 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7528));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7548):UINT32_C(0x002d752c));goto dispatch;}
L_002d7528:
 STEP(UINT32_C(0x002d7528)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d752c));goto dispatch;
L_002d752c:
 STEP(UINT32_C(0x002d752c)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7530));goto dispatch;
L_002d7530:
 STEP(UINT32_C(0x002d7530)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7538));STEP(UINT32_C(0x002d7534));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7534:
 STEP(UINT32_C(0x002d7534)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7538));goto dispatch;
L_002d7538:
 STEP(UINT32_C(0x002d7538)); /* 144001da bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d753c));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7540));goto dispatch;}
L_002d753c:
 STEP(UINT32_C(0x002d753c)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7540));goto dispatch;
L_002d7540:
 STEP(UINT32_C(0x002d7540)); /* 27a50020 addiu a1,sp,32 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7544));goto dispatch;
L_002d7544:
 STEP(UINT32_C(0x002d7544)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d7548));goto dispatch;
L_002d7548:
 STEP(UINT32_C(0x002d7548)); /* 8fa201dc lw v0,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d754c));goto dispatch;
L_002d754c:
 STEP(UINT32_C(0x002d754c)); /* 00028023 subu s0,zero,v0 */
 set(m,16u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d7550));goto dispatch;
L_002d7550:
 STEP(UINT32_C(0x002d7550)); /* 5a000033 blezl s0,zero,002d7620 */
 if((int64_t)lo(m,16u)<=0){STEP(UINT32_C(0x002d7554));value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7620));}else target=sx(UINT32_C(0x002d7558));goto dispatch;
L_002d7554:
 STEP(UINT32_C(0x002d7554)); /* ae750000 sw s5,0x0(s3) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7558));goto dispatch;
L_002d7558:
 STEP(UINT32_C(0x002d7558)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d755c));goto dispatch;
L_002d755c:
 STEP(UINT32_C(0x002d755c)); /* 1440001c bne v0,zero,002d75d0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7560));set(m,7u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d75d0):UINT32_C(0x002d7564));goto dispatch;}
L_002d7560:
 STEP(UINT32_C(0x002d7560)); /* 3c070055 lui a3,zero,0x55 */
 set(m,7u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d7564));goto dispatch;
L_002d7564:
 STEP(UINT32_C(0x002d7564)); /* 24140010 addiu s4,zero,16 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7568));goto dispatch;
L_002d7568:
 STEP(UINT32_C(0x002d7568)); /* 24f1b680 addiu s1,a3,-18816 */
 set(m,17u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d756c));goto dispatch;
L_002d756c:
 STEP(UINT32_C(0x002d756c)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7570));goto dispatch;
L_002d7570:
 STEP(UINT32_C(0x002d7570)); /* ae710000 sw s1,0x0(s3) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7574));goto dispatch;
L_002d7574:
 STEP(UINT32_C(0x002d7574)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7578));goto dispatch;
L_002d7578:
 STEP(UINT32_C(0x002d7578)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d757c));goto dispatch;
L_002d757c:
 STEP(UINT32_C(0x002d757c)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7580));goto dispatch;
L_002d7580:
 STEP(UINT32_C(0x002d7580)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7584));goto dispatch;
L_002d7584:
 STEP(UINT32_C(0x002d7584)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7588));goto dispatch;
L_002d7588:
 STEP(UINT32_C(0x002d7588)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d758c));goto dispatch;
L_002d758c:
 STEP(UINT32_C(0x002d758c)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7590));goto dispatch;
L_002d7590:
 STEP(UINT32_C(0x002d7590)); /* 14800009 bne a0,zero,002d75b8 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7594));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d75b8):UINT32_C(0x002d7598));goto dispatch;}
L_002d7594:
 STEP(UINT32_C(0x002d7594)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7598));goto dispatch;
L_002d7598:
 STEP(UINT32_C(0x002d7598)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d759c));goto dispatch;
L_002d759c:
 STEP(UINT32_C(0x002d759c)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d75a0));goto dispatch;
L_002d75a0:
 STEP(UINT32_C(0x002d75a0)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d75a8));STEP(UINT32_C(0x002d75a4));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d75a4:
 STEP(UINT32_C(0x002d75a4)); /* 7fa70230 sq a3,0x230(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d75a8));goto dispatch;
L_002d75a8:
 STEP(UINT32_C(0x002d75a8)); /* 144001bd bne v0,zero,002d7ca0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d75ac));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(taken?UINT32_C(0x002d7ca0):UINT32_C(0x002d75b0));goto dispatch;}
L_002d75ac:
 STEP(UINT32_C(0x002d75ac)); /* 7ba70230 lq a3,0x230(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x002d75b0));goto dispatch;
L_002d75b0:
 STEP(UINT32_C(0x002d75b0)); /* 27a60020 addiu a2,sp,32 */
 set(m,6u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d75b4));goto dispatch;
L_002d75b4:
 STEP(UINT32_C(0x002d75b4)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d75b8));goto dispatch;
L_002d75b8:
 STEP(UINT32_C(0x002d75b8)); /* 2610fff0 addiu s0,s0,-16 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d75bc));goto dispatch;
L_002d75bc:
 STEP(UINT32_C(0x002d75bc)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d75c0));goto dispatch;
L_002d75c0:
 STEP(UINT32_C(0x002d75c0)); /* 5040ffeb beql v0,zero,002d7570 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d75c4));value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7570));}else target=sx(UINT32_C(0x002d75c8));goto dispatch;
L_002d75c4:
 STEP(UINT32_C(0x002d75c4)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d75c8));goto dispatch;
L_002d75c8:
 STEP(UINT32_C(0x002d75c8)); /* 10000002 beq zero,zero,002d75d4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d75cc));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d75d4):UINT32_C(0x002d75d0));goto dispatch;}
L_002d75cc:
 STEP(UINT32_C(0x002d75cc)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d75d0));goto dispatch;
L_002d75d0:
 STEP(UINT32_C(0x002d75d0)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d75d4));goto dispatch;
L_002d75d4:
 STEP(UINT32_C(0x002d75d4)); /* 24e2b680 addiu v0,a3,-18816 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d75d8));goto dispatch;
L_002d75d8:
 STEP(UINT32_C(0x002d75d8)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d75dc));goto dispatch;
L_002d75dc:
 STEP(UINT32_C(0x002d75dc)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d75e0));goto dispatch;
L_002d75e0:
 STEP(UINT32_C(0x002d75e0)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d75e4));goto dispatch;
L_002d75e4:
 STEP(UINT32_C(0x002d75e4)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d75e8));goto dispatch;
L_002d75e8:
 STEP(UINT32_C(0x002d75e8)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d75ec));goto dispatch;
L_002d75ec:
 STEP(UINT32_C(0x002d75ec)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d75f0));goto dispatch;
L_002d75f0:
 STEP(UINT32_C(0x002d75f0)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d75f4));goto dispatch;
L_002d75f4:
 STEP(UINT32_C(0x002d75f4)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d75f8));goto dispatch;
L_002d75f8:
 STEP(UINT32_C(0x002d75f8)); /* 14800008 bne a0,zero,002d761c */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d75fc));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d761c):UINT32_C(0x002d7600));goto dispatch;}
L_002d75fc:
 STEP(UINT32_C(0x002d75fc)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7600));goto dispatch;
L_002d7600:
 STEP(UINT32_C(0x002d7600)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7604));goto dispatch;
L_002d7604:
 STEP(UINT32_C(0x002d7604)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d760c));STEP(UINT32_C(0x002d7608));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7608:
 STEP(UINT32_C(0x002d7608)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d760c));goto dispatch;
L_002d760c:
 STEP(UINT32_C(0x002d760c)); /* 144001a5 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7610));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7614));goto dispatch;}
L_002d7610:
 STEP(UINT32_C(0x002d7610)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7614));goto dispatch;
L_002d7614:
 STEP(UINT32_C(0x002d7614)); /* 27a20020 addiu v0,sp,32 */
 set(m,2u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7618));goto dispatch;
L_002d7618:
 STEP(UINT32_C(0x002d7618)); /* 0040982d daddu s3,v0,zero */
 set(m,19u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d761c));goto dispatch;
L_002d761c:
 STEP(UINT32_C(0x002d761c)); /* ae750000 sw s5,0x0(s3) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7620));goto dispatch;
L_002d7620:
 STEP(UINT32_C(0x002d7620)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7624));goto dispatch;
L_002d7624:
 STEP(UINT32_C(0x002d7624)); /* ae620004 sw v0,0x4(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7628));goto dispatch;
L_002d7628:
 STEP(UINT32_C(0x002d7628)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d762c));goto dispatch;
L_002d762c:
 STEP(UINT32_C(0x002d762c)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7630));goto dispatch;
L_002d7630:
 STEP(UINT32_C(0x002d7630)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7634));goto dispatch;
L_002d7634:
 STEP(UINT32_C(0x002d7634)); /* 8fa401e0 lw a0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7638));goto dispatch;
L_002d7638:
 STEP(UINT32_C(0x002d7638)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d763c));goto dispatch;
L_002d763c:
 STEP(UINT32_C(0x002d763c)); /* 28450008 slti a1,v0,8 */
 set(m,5u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d7640));goto dispatch;
L_002d7640:
 STEP(UINT32_C(0x002d7640)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7644));goto dispatch;
L_002d7644:
 STEP(UINT32_C(0x002d7644)); /* 00641821 addu v1,v1,a0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d7648));goto dispatch;
L_002d7648:
 STEP(UINT32_C(0x002d7648)); /* 14a00143 bne a1,zero,002d7b58 */
 {int taken=(lo(m,5u)!=lo(m,0u));STEP(UINT32_C(0x002d764c));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(taken?UINT32_C(0x002d7b58):UINT32_C(0x002d7650));goto dispatch;}
L_002d764c:
 STEP(UINT32_C(0x002d764c)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7650));goto dispatch;
L_002d7650:
 STEP(UINT32_C(0x002d7650)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7654));goto dispatch;
L_002d7654:
 STEP(UINT32_C(0x002d7654)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d765c));STEP(UINT32_C(0x002d7658));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7658:
 STEP(UINT32_C(0x002d7658)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d765c));goto dispatch;
L_002d765c:
 STEP(UINT32_C(0x002d765c)); /* 14400191 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7660));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7664));goto dispatch;}
L_002d7660:
 STEP(UINT32_C(0x002d7660)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7664));goto dispatch;
L_002d7664:
 STEP(UINT32_C(0x002d7664)); /* 27a30020 addiu v1,sp,32 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7668));goto dispatch;
L_002d7668:
 STEP(UINT32_C(0x002d7668)); /* 1000013b beq zero,zero,002d7b58 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d766c));set(m,19u,lo(m,3u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d7b58):UINT32_C(0x002d7670));goto dispatch;}
L_002d766c:
 STEP(UINT32_C(0x002d766c)); /* 0060982d daddu s3,v1,zero */
 set(m,19u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d7670));goto dispatch;
L_002d7670:
 STEP(UINT32_C(0x002d7670)); /* 0062102a slt v0,v1,v0 */
 set(m,2u,((int64_t)lo(m,3u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x002d7674));goto dispatch;
L_002d7674:
 STEP(UINT32_C(0x002d7674)); /* 1440005c bne v0,zero,002d77e8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7678));value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002d77e8):UINT32_C(0x002d767c));goto dispatch;}
L_002d7678:
 STEP(UINT32_C(0x002d7678)); /* ae750000 sw s5,0x0(s3) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d767c));goto dispatch;
L_002d767c:
 STEP(UINT32_C(0x002d767c)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7680));goto dispatch;
L_002d7680:
 STEP(UINT32_C(0x002d7680)); /* ae620004 sw v0,0x4(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7684));goto dispatch;
L_002d7684:
 STEP(UINT32_C(0x002d7684)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7688));goto dispatch;
L_002d7688:
 STEP(UINT32_C(0x002d7688)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d768c));goto dispatch;
L_002d768c:
 STEP(UINT32_C(0x002d768c)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7690));goto dispatch;
L_002d7690:
 STEP(UINT32_C(0x002d7690)); /* 8fa501e0 lw a1,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d7694));goto dispatch;
L_002d7694:
 STEP(UINT32_C(0x002d7694)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7698));goto dispatch;
L_002d7698:
 STEP(UINT32_C(0x002d7698)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d769c));goto dispatch;
L_002d769c:
 STEP(UINT32_C(0x002d769c)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d76a0));goto dispatch;
L_002d76a0:
 STEP(UINT32_C(0x002d76a0)); /* 00651821 addu v1,v1,a1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002d76a4));goto dispatch;
L_002d76a4:
 STEP(UINT32_C(0x002d76a4)); /* 14800009 bne a0,zero,002d76cc */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d76a8));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(taken?UINT32_C(0x002d76cc):UINT32_C(0x002d76ac));goto dispatch;}
L_002d76a8:
 STEP(UINT32_C(0x002d76a8)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d76ac));goto dispatch;
L_002d76ac:
 STEP(UINT32_C(0x002d76ac)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d76b0));goto dispatch;
L_002d76b0:
 STEP(UINT32_C(0x002d76b0)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d76b8));STEP(UINT32_C(0x002d76b4));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d76b4:
 STEP(UINT32_C(0x002d76b4)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d76b8));goto dispatch;
L_002d76b8:
 STEP(UINT32_C(0x002d76b8)); /* 1440017a bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d76bc));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d76c0));goto dispatch;}
L_002d76bc:
 STEP(UINT32_C(0x002d76bc)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d76c0));goto dispatch;
L_002d76c0:
 STEP(UINT32_C(0x002d76c0)); /* 27a40020 addiu a0,sp,32 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d76c4));goto dispatch;
L_002d76c4:
 STEP(UINT32_C(0x002d76c4)); /* 8fa501e0 lw a1,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d76c8));goto dispatch;
L_002d76c8:
 STEP(UINT32_C(0x002d76c8)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d76cc));goto dispatch;
L_002d76cc:
 STEP(UINT32_C(0x002d76cc)); /* 8fa201dc lw v0,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d76d0));goto dispatch;
L_002d76d0:
 STEP(UINT32_C(0x002d76d0)); /* 00458023 subu s0,v0,a1 */
 set(m,16u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002d76d4));goto dispatch;
L_002d76d4:
 STEP(UINT32_C(0x002d76d4)); /* 1a000034 blez s0,zero,002d77a8 */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d76d8));set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(taken?UINT32_C(0x002d77a8):UINT32_C(0x002d76dc));goto dispatch;}
L_002d76d8:
 STEP(UINT32_C(0x002d76d8)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d76dc));goto dispatch;
L_002d76dc:
 STEP(UINT32_C(0x002d76dc)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d76e0));goto dispatch;
L_002d76e0:
 STEP(UINT32_C(0x002d76e0)); /* 1440001d bne v0,zero,002d7758 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d76e4));set(m,7u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d7758):UINT32_C(0x002d76e8));goto dispatch;}
L_002d76e4:
 STEP(UINT32_C(0x002d76e4)); /* 3c070055 lui a3,zero,0x55 */
 set(m,7u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d76e8));goto dispatch;
L_002d76e8:
 STEP(UINT32_C(0x002d76e8)); /* 24140010 addiu s4,zero,16 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d76ec));goto dispatch;
L_002d76ec:
 STEP(UINT32_C(0x002d76ec)); /* 24f1b680 addiu s1,a3,-18816 */
 set(m,17u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d76f0));goto dispatch;
L_002d76f0:
 STEP(UINT32_C(0x002d76f0)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d76f4));goto dispatch;
L_002d76f4:
 STEP(UINT32_C(0x002d76f4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d76f8));goto dispatch;
L_002d76f8:
 STEP(UINT32_C(0x002d76f8)); /* ae710000 sw s1,0x0(s3) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d76fc));goto dispatch;
L_002d76fc:
 STEP(UINT32_C(0x002d76fc)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7700));goto dispatch;
L_002d7700:
 STEP(UINT32_C(0x002d7700)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7704));goto dispatch;
L_002d7704:
 STEP(UINT32_C(0x002d7704)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7708));goto dispatch;
L_002d7708:
 STEP(UINT32_C(0x002d7708)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d770c));goto dispatch;
L_002d770c:
 STEP(UINT32_C(0x002d770c)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7710));goto dispatch;
L_002d7710:
 STEP(UINT32_C(0x002d7710)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d7714));goto dispatch;
L_002d7714:
 STEP(UINT32_C(0x002d7714)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7718));goto dispatch;
L_002d7718:
 STEP(UINT32_C(0x002d7718)); /* 14800009 bne a0,zero,002d7740 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d771c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7740):UINT32_C(0x002d7720));goto dispatch;}
L_002d771c:
 STEP(UINT32_C(0x002d771c)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7720));goto dispatch;
L_002d7720:
 STEP(UINT32_C(0x002d7720)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7724));goto dispatch;
L_002d7724:
 STEP(UINT32_C(0x002d7724)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7728));goto dispatch;
L_002d7728:
 STEP(UINT32_C(0x002d7728)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7730));STEP(UINT32_C(0x002d772c));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d772c:
 STEP(UINT32_C(0x002d772c)); /* 7fa70230 sq a3,0x230(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d7730));goto dispatch;
L_002d7730:
 STEP(UINT32_C(0x002d7730)); /* 1440015b bne v0,zero,002d7ca0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7734));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(taken?UINT32_C(0x002d7ca0):UINT32_C(0x002d7738));goto dispatch;}
L_002d7734:
 STEP(UINT32_C(0x002d7734)); /* 7ba70230 lq a3,0x230(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x002d7738));goto dispatch;
L_002d7738:
 STEP(UINT32_C(0x002d7738)); /* 27a50020 addiu a1,sp,32 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d773c));goto dispatch;
L_002d773c:
 STEP(UINT32_C(0x002d773c)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d7740));goto dispatch;
L_002d7740:
 STEP(UINT32_C(0x002d7740)); /* 2610fff0 addiu s0,s0,-16 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d7744));goto dispatch;
L_002d7744:
 STEP(UINT32_C(0x002d7744)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d7748));goto dispatch;
L_002d7748:
 STEP(UINT32_C(0x002d7748)); /* 5040ffeb beql v0,zero,002d76f8 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d774c));value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d76f8));}else target=sx(UINT32_C(0x002d7750));goto dispatch;
L_002d774c:
 STEP(UINT32_C(0x002d774c)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7750));goto dispatch;
L_002d7750:
 STEP(UINT32_C(0x002d7750)); /* 10000002 beq zero,zero,002d775c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7754));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d775c):UINT32_C(0x002d7758));goto dispatch;}
L_002d7754:
 STEP(UINT32_C(0x002d7754)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7758));goto dispatch;
L_002d7758:
 STEP(UINT32_C(0x002d7758)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d775c));goto dispatch;
L_002d775c:
 STEP(UINT32_C(0x002d775c)); /* 24e2b680 addiu v0,a3,-18816 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d7760));goto dispatch;
L_002d7760:
 STEP(UINT32_C(0x002d7760)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7764));goto dispatch;
L_002d7764:
 STEP(UINT32_C(0x002d7764)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7768));goto dispatch;
L_002d7768:
 STEP(UINT32_C(0x002d7768)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d776c));goto dispatch;
L_002d776c:
 STEP(UINT32_C(0x002d776c)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7770));goto dispatch;
L_002d7770:
 STEP(UINT32_C(0x002d7770)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7774));goto dispatch;
L_002d7774:
 STEP(UINT32_C(0x002d7774)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d7778));goto dispatch;
L_002d7778:
 STEP(UINT32_C(0x002d7778)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d777c));goto dispatch;
L_002d777c:
 STEP(UINT32_C(0x002d777c)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7780));goto dispatch;
L_002d7780:
 STEP(UINT32_C(0x002d7780)); /* 14800008 bne a0,zero,002d77a4 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7784));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d77a4):UINT32_C(0x002d7788));goto dispatch;}
L_002d7784:
 STEP(UINT32_C(0x002d7784)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7788));goto dispatch;
L_002d7788:
 STEP(UINT32_C(0x002d7788)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d778c));goto dispatch;
L_002d778c:
 STEP(UINT32_C(0x002d778c)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7794));STEP(UINT32_C(0x002d7790));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7790:
 STEP(UINT32_C(0x002d7790)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7794));goto dispatch;
L_002d7794:
 STEP(UINT32_C(0x002d7794)); /* 14400143 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7798));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d779c));goto dispatch;}
L_002d7798:
 STEP(UINT32_C(0x002d7798)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d779c));goto dispatch;
L_002d779c:
 STEP(UINT32_C(0x002d779c)); /* 27a60020 addiu a2,sp,32 */
 set(m,6u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d77a0));goto dispatch;
L_002d77a0:
 STEP(UINT32_C(0x002d77a0)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d77a4));goto dispatch;
L_002d77a4:
 STEP(UINT32_C(0x002d77a4)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d77a8));goto dispatch;
L_002d77a8:
 STEP(UINT32_C(0x002d77a8)); /* 104000eb beq v0,zero,002d7b58 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d77ac));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d7b58):UINT32_C(0x002d77b0));goto dispatch;}
L_002d77ac:
 STEP(UINT32_C(0x002d77ac)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d77b0));goto dispatch;
L_002d77b0:
 STEP(UINT32_C(0x002d77b0)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d77b4));goto dispatch;
L_002d77b4:
 STEP(UINT32_C(0x002d77b4)); /* ae630004 sw v1,0x4(s3) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d77b8));goto dispatch;
L_002d77b8:
 STEP(UINT32_C(0x002d77b8)); /* 2442b700 addiu v0,v0,-18688 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb700)));target=sx(UINT32_C(0x002d77bc));goto dispatch;
L_002d77bc:
 STEP(UINT32_C(0x002d77bc)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d77c0));goto dispatch;
L_002d77c0:
 STEP(UINT32_C(0x002d77c0)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d77c4));goto dispatch;
L_002d77c4:
 STEP(UINT32_C(0x002d77c4)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d77c8));goto dispatch;
L_002d77c8:
 STEP(UINT32_C(0x002d77c8)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d77cc));goto dispatch;
L_002d77cc:
 STEP(UINT32_C(0x002d77cc)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d77d0));goto dispatch;
L_002d77d0:
 STEP(UINT32_C(0x002d77d0)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d77d4));goto dispatch;
L_002d77d4:
 STEP(UINT32_C(0x002d77d4)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d77d8));goto dispatch;
L_002d77d8:
 STEP(UINT32_C(0x002d77d8)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d77dc));goto dispatch;
L_002d77dc:
 STEP(UINT32_C(0x002d77dc)); /* 100000d5 beq zero,zero,002d7b34 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d77e0));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7b34):UINT32_C(0x002d77e4));goto dispatch;}
L_002d77e0:
 STEP(UINT32_C(0x002d77e0)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d77e4));goto dispatch;
L_002d77e4:
 STEP(UINT32_C(0x002d77e4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d77e8));goto dispatch;
L_002d77e8:
 STEP(UINT32_C(0x002d77e8)); /* 8fa201dc lw v0,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d77ec));goto dispatch;
L_002d77ec:
 STEP(UINT32_C(0x002d77ec)); /* ae620004 sw v0,0x4(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d77f0));goto dispatch;
L_002d77f0:
 STEP(UINT32_C(0x002d77f0)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d77f4));goto dispatch;
L_002d77f4:
 STEP(UINT32_C(0x002d77f4)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d77f8));goto dispatch;
L_002d77f8:
 STEP(UINT32_C(0x002d77f8)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d77fc));goto dispatch;
L_002d77fc:
 STEP(UINT32_C(0x002d77fc)); /* 8fa701dc lw a3,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d7800));goto dispatch;
L_002d7800:
 STEP(UINT32_C(0x002d7800)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7804));goto dispatch;
L_002d7804:
 STEP(UINT32_C(0x002d7804)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d7808));goto dispatch;
L_002d7808:
 STEP(UINT32_C(0x002d7808)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d780c));goto dispatch;
L_002d780c:
 STEP(UINT32_C(0x002d780c)); /* 00671821 addu v1,v1,a3 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x002d7810));goto dispatch;
L_002d7810:
 STEP(UINT32_C(0x002d7810)); /* 14800009 bne a0,zero,002d7838 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7814));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(taken?UINT32_C(0x002d7838):UINT32_C(0x002d7818));goto dispatch;}
L_002d7814:
 STEP(UINT32_C(0x002d7814)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7818));goto dispatch;
L_002d7818:
 STEP(UINT32_C(0x002d7818)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d781c));goto dispatch;
L_002d781c:
 STEP(UINT32_C(0x002d781c)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7824));STEP(UINT32_C(0x002d7820));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7820:
 STEP(UINT32_C(0x002d7820)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7824));goto dispatch;
L_002d7824:
 STEP(UINT32_C(0x002d7824)); /* 1440011f bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7828));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d782c));goto dispatch;}
L_002d7828:
 STEP(UINT32_C(0x002d7828)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d782c));goto dispatch;
L_002d782c:
 STEP(UINT32_C(0x002d782c)); /* 27a30020 addiu v1,sp,32 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7830));goto dispatch;
L_002d7830:
 STEP(UINT32_C(0x002d7830)); /* 8fa701dc lw a3,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d7834));goto dispatch;
L_002d7834:
 STEP(UINT32_C(0x002d7834)); /* 0060982d daddu s3,v1,zero */
 set(m,19u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d7838));goto dispatch;
L_002d7838:
 STEP(UINT32_C(0x002d7838)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d783c));goto dispatch;
L_002d783c:
 STEP(UINT32_C(0x002d783c)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d7840));goto dispatch;
L_002d7840:
 STEP(UINT32_C(0x002d7840)); /* ae630004 sw v1,0x4(s3) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7844));goto dispatch;
L_002d7844:
 STEP(UINT32_C(0x002d7844)); /* 2442b700 addiu v0,v0,-18688 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb700)));target=sx(UINT32_C(0x002d7848));goto dispatch;
L_002d7848:
 STEP(UINT32_C(0x002d7848)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d784c));goto dispatch;
L_002d784c:
 STEP(UINT32_C(0x002d784c)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7850));goto dispatch;
L_002d7850:
 STEP(UINT32_C(0x002d7850)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7854));goto dispatch;
L_002d7854:
 STEP(UINT32_C(0x002d7854)); /* 02a7a821 addu s5,s5,a3 */
 set(m,21u,sx((uint32_t)lo(m,21u)+(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x002d7858));goto dispatch;
L_002d7858:
 STEP(UINT32_C(0x002d7858)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d785c));goto dispatch;
L_002d785c:
 STEP(UINT32_C(0x002d785c)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7860));goto dispatch;
L_002d7860:
 STEP(UINT32_C(0x002d7860)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7864));goto dispatch;
L_002d7864:
 STEP(UINT32_C(0x002d7864)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d7868));goto dispatch;
L_002d7868:
 STEP(UINT32_C(0x002d7868)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d786c));goto dispatch;
L_002d786c:
 STEP(UINT32_C(0x002d786c)); /* 14800008 bne a0,zero,002d7890 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7870));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7890):UINT32_C(0x002d7874));goto dispatch;}
L_002d7870:
 STEP(UINT32_C(0x002d7870)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7874));goto dispatch;
L_002d7874:
 STEP(UINT32_C(0x002d7874)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7878));goto dispatch;
L_002d7878:
 STEP(UINT32_C(0x002d7878)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7880));STEP(UINT32_C(0x002d787c));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d787c:
 STEP(UINT32_C(0x002d787c)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7880));goto dispatch;
L_002d7880:
 STEP(UINT32_C(0x002d7880)); /* 14400108 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7884));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7888));goto dispatch;}
L_002d7884:
 STEP(UINT32_C(0x002d7884)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7888));goto dispatch;
L_002d7888:
 STEP(UINT32_C(0x002d7888)); /* 27a40020 addiu a0,sp,32 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d788c));goto dispatch;
L_002d788c:
 STEP(UINT32_C(0x002d788c)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d7890));goto dispatch;
L_002d7890:
 STEP(UINT32_C(0x002d7890)); /* ae750000 sw s5,0x0(s3) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7894));goto dispatch;
L_002d7894:
 STEP(UINT32_C(0x002d7894)); /* 8fa301dc lw v1,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7898));goto dispatch;
L_002d7898:
 STEP(UINT32_C(0x002d7898)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d789c));goto dispatch;
L_002d789c:
 STEP(UINT32_C(0x002d789c)); /* 00431023 subu v0,v0,v1 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d78a0));goto dispatch;
L_002d78a0:
 STEP(UINT32_C(0x002d78a0)); /* ae620004 sw v0,0x4(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d78a4));goto dispatch;
L_002d78a4:
 STEP(UINT32_C(0x002d78a4)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d78a8));goto dispatch;
L_002d78a8:
 STEP(UINT32_C(0x002d78a8)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d78ac));goto dispatch;
L_002d78ac:
 STEP(UINT32_C(0x002d78ac)); /* 8fa401e0 lw a0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d78b0));goto dispatch;
L_002d78b0:
 STEP(UINT32_C(0x002d78b0)); /* 8fa501dc lw a1,0x1dc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001dc),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d78b4));goto dispatch;
L_002d78b4:
 STEP(UINT32_C(0x002d78b4)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d78b8));goto dispatch;
L_002d78b8:
 STEP(UINT32_C(0x002d78b8)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d78bc));goto dispatch;
L_002d78bc:
 STEP(UINT32_C(0x002d78bc)); /* 28660008 slti a2,v1,8 */
 set(m,6u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d78c0));goto dispatch;
L_002d78c0:
 STEP(UINT32_C(0x002d78c0)); /* 00852023 subu a0,a0,a1 */
 set(m,4u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002d78c4));goto dispatch;
L_002d78c4:
 STEP(UINT32_C(0x002d78c4)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d78c8));goto dispatch;
L_002d78c8:
 STEP(UINT32_C(0x002d78c8)); /* 00441021 addu v0,v0,a0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d78cc));goto dispatch;
L_002d78cc:
 STEP(UINT32_C(0x002d78cc)); /* 14c000a2 bne a2,zero,002d7b58 */
 {int taken=(lo(m,6u)!=lo(m,0u));STEP(UINT32_C(0x002d78d0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(taken?UINT32_C(0x002d7b58):UINT32_C(0x002d78d4));goto dispatch;}
L_002d78d0:
 STEP(UINT32_C(0x002d78d0)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d78d4));goto dispatch;
L_002d78d4:
 STEP(UINT32_C(0x002d78d4)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d78d8));goto dispatch;
L_002d78d8:
 STEP(UINT32_C(0x002d78d8)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d78e0));STEP(UINT32_C(0x002d78dc));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d78dc:
 STEP(UINT32_C(0x002d78dc)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d78e0));goto dispatch;
L_002d78e0:
 STEP(UINT32_C(0x002d78e0)); /* 144000f0 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d78e4));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d78e8));goto dispatch;}
L_002d78e4:
 STEP(UINT32_C(0x002d78e4)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d78e8));goto dispatch;
L_002d78e8:
 STEP(UINT32_C(0x002d78e8)); /* 27a50020 addiu a1,sp,32 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d78ec));goto dispatch;
L_002d78ec:
 STEP(UINT32_C(0x002d78ec)); /* 1000009a beq zero,zero,002d7b58 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d78f0));set(m,19u,lo(m,5u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d7b58):UINT32_C(0x002d78f4));goto dispatch;}
L_002d78f0:
 STEP(UINT32_C(0x002d78f0)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d78f4));goto dispatch;
L_002d78f4:
 STEP(UINT32_C(0x002d78f4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d78f8));goto dispatch;
L_002d78f8:
 STEP(UINT32_C(0x002d78f8)); /* 28420002 slti v0,v0,2 */
 set(m,2u,((int64_t)lo(m,2u)<INT64_C(2)));target=sx(UINT32_C(0x002d78fc));goto dispatch;
L_002d78fc:
 STEP(UINT32_C(0x002d78fc)); /* 50400005 beql v0,zero,002d7914 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d7900));{uint8_t byte;READ((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002d7914));}else target=sx(UINT32_C(0x002d7904));goto dispatch;
L_002d7900:
 STEP(UINT32_C(0x002d7900)); /* 92a30000 lbu v1,0x0(s5) */
 {uint8_t byte;READ((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002d7904));goto dispatch;
L_002d7904:
 STEP(UINT32_C(0x002d7904)); /* 32e20001 andi v0,s7,0x1 */
 set(m,2u,lo(m,23u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d7908));goto dispatch;
L_002d7908:
 STEP(UINT32_C(0x002d7908)); /* 1040006d beq v0,zero,002d7ac0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d790c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d7ac0):UINT32_C(0x002d7910));goto dispatch;}
L_002d790c:
 STEP(UINT32_C(0x002d790c)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7910));goto dispatch;
L_002d7910:
 STEP(UINT32_C(0x002d7910)); /* 92a30000 lbu v1,0x0(s5) */
 {uint8_t byte;READ((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002d7914));goto dispatch;
L_002d7914:
 STEP(UINT32_C(0x002d7914)); /* 26b50001 addiu s5,s5,1 */
 set(m,21u,sx((uint32_t)lo(m,21u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7918));goto dispatch;
L_002d7918:
 STEP(UINT32_C(0x002d7918)); /* 2404002e addiu a0,zero,46 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000002e)));target=sx(UINT32_C(0x002d791c));goto dispatch;
L_002d791c:
 STEP(UINT32_C(0x002d791c)); /* 24050002 addiu a1,zero,2 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d7920));goto dispatch;
L_002d7920:
 STEP(UINT32_C(0x002d7920)); /* a3a301c0 sb v1,0x1c0(sp) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001c0),&byte,1u);}target=sx(UINT32_C(0x002d7924));goto dispatch;
L_002d7924:
 STEP(UINT32_C(0x002d7924)); /* 27a201c0 addiu v0,sp,448 */
 set(m,2u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000001c0)));target=sx(UINT32_C(0x002d7928));goto dispatch;
L_002d7928:
 STEP(UINT32_C(0x002d7928)); /* a3a401c1 sb a0,0x1c1(sp) */
 {uint8_t byte=(uint8_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001c1),&byte,1u);}target=sx(UINT32_C(0x002d792c));goto dispatch;
L_002d792c:
 STEP(UINT32_C(0x002d792c)); /* ae650004 sw a1,0x4(s3) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7930));goto dispatch;
L_002d7930:
 STEP(UINT32_C(0x002d7930)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7934));goto dispatch;
L_002d7934:
 STEP(UINT32_C(0x002d7934)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7938));goto dispatch;
L_002d7938:
 STEP(UINT32_C(0x002d7938)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d793c));goto dispatch;
L_002d793c:
 STEP(UINT32_C(0x002d793c)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7940));goto dispatch;
L_002d7940:
 STEP(UINT32_C(0x002d7940)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7944));goto dispatch;
L_002d7944:
 STEP(UINT32_C(0x002d7944)); /* 24420002 addiu v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d7948));goto dispatch;
L_002d7948:
 STEP(UINT32_C(0x002d7948)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d794c));goto dispatch;
L_002d794c:
 STEP(UINT32_C(0x002d794c)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7950));goto dispatch;
L_002d7950:
 STEP(UINT32_C(0x002d7950)); /* 14800008 bne a0,zero,002d7974 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7954));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7974):UINT32_C(0x002d7958));goto dispatch;}
L_002d7954:
 STEP(UINT32_C(0x002d7954)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7958));goto dispatch;
L_002d7958:
 STEP(UINT32_C(0x002d7958)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d795c));goto dispatch;
L_002d795c:
 STEP(UINT32_C(0x002d795c)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7964));STEP(UINT32_C(0x002d7960));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7960:
 STEP(UINT32_C(0x002d7960)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7964));goto dispatch;
L_002d7964:
 STEP(UINT32_C(0x002d7964)); /* 144000cf bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7968));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d796c));goto dispatch;}
L_002d7968:
 STEP(UINT32_C(0x002d7968)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d796c));goto dispatch;
L_002d796c:
 STEP(UINT32_C(0x002d796c)); /* 27a60020 addiu a2,sp,32 */
 set(m,6u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7970));goto dispatch;
L_002d7970:
 STEP(UINT32_C(0x002d7970)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d7974));goto dispatch;
L_002d7974:
 STEP(UINT32_C(0x002d7974)); /* dfa401f8 ld a0,0x1f8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f8),&value64,8u);set(m,4u,value64);target=sx(UINT32_C(0x002d7978));goto dispatch;
L_002d7978:
 STEP(UINT32_C(0x002d7978)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d797c));goto dispatch;
L_002d797c:
 STEP(UINT32_C(0x002d797c)); /* 0c0b46ce jal 002d1b38 */
 set(m,31u,UINT64_C(0x002d7984));STEP(UINT32_C(0x002d7980));/* nop */target=sx(UINT32_C(0x002d1b38));goto dispatch;
L_002d7980:
 STEP(UINT32_C(0x002d7980)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d7984));goto dispatch;
L_002d7984:
 STEP(UINT32_C(0x002d7984)); /* 10400018 beq v0,zero,002d79e8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d7988));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d79e8):UINT32_C(0x002d798c));goto dispatch;}
L_002d7988:
 STEP(UINT32_C(0x002d7988)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d798c));goto dispatch;
L_002d798c:
 STEP(UINT32_C(0x002d798c)); /* ae750000 sw s5,0x0(s3) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7990));goto dispatch;
L_002d7990:
 STEP(UINT32_C(0x002d7990)); /* 8fa201e0 lw v0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7994));goto dispatch;
L_002d7994:
 STEP(UINT32_C(0x002d7994)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d7998));goto dispatch;
L_002d7998:
 STEP(UINT32_C(0x002d7998)); /* ae620004 sw v0,0x4(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d799c));goto dispatch;
L_002d799c:
 STEP(UINT32_C(0x002d799c)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d79a0));goto dispatch;
L_002d79a0:
 STEP(UINT32_C(0x002d79a0)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d79a4));goto dispatch;
L_002d79a4:
 STEP(UINT32_C(0x002d79a4)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d79a8));goto dispatch;
L_002d79a8:
 STEP(UINT32_C(0x002d79a8)); /* 8fa401e0 lw a0,0x1e0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d79ac));goto dispatch;
L_002d79ac:
 STEP(UINT32_C(0x002d79ac)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d79b0));goto dispatch;
L_002d79b0:
 STEP(UINT32_C(0x002d79b0)); /* 00641821 addu v1,v1,a0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d79b4));goto dispatch;
L_002d79b4:
 STEP(UINT32_C(0x002d79b4)); /* 28450008 slti a1,v0,8 */
 set(m,5u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d79b8));goto dispatch;
L_002d79b8:
 STEP(UINT32_C(0x002d79b8)); /* 2463ffff addiu v1,v1,-1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d79bc));goto dispatch;
L_002d79bc:
 STEP(UINT32_C(0x002d79bc)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d79c0));goto dispatch;
L_002d79c0:
 STEP(UINT32_C(0x002d79c0)); /* 14a00051 bne a1,zero,002d7b08 */
 {int taken=(lo(m,5u)!=lo(m,0u));STEP(UINT32_C(0x002d79c4));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(taken?UINT32_C(0x002d7b08):UINT32_C(0x002d79c8));goto dispatch;}
L_002d79c4:
 STEP(UINT32_C(0x002d79c4)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d79c8));goto dispatch;
L_002d79c8:
 STEP(UINT32_C(0x002d79c8)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d79cc));goto dispatch;
L_002d79cc:
 STEP(UINT32_C(0x002d79cc)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d79d4));STEP(UINT32_C(0x002d79d0));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d79d0:
 STEP(UINT32_C(0x002d79d0)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d79d4));goto dispatch;
L_002d79d4:
 STEP(UINT32_C(0x002d79d4)); /* 144000b3 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d79d8));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d79dc));goto dispatch;}
L_002d79d8:
 STEP(UINT32_C(0x002d79d8)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d79dc));goto dispatch;
L_002d79dc:
 STEP(UINT32_C(0x002d79dc)); /* 27a20020 addiu v0,sp,32 */
 set(m,2u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d79e0));goto dispatch;
L_002d79e0:
 STEP(UINT32_C(0x002d79e0)); /* 10000049 beq zero,zero,002d7b08 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d79e4));set(m,19u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d7b08):UINT32_C(0x002d79e8));goto dispatch;}
L_002d79e4:
 STEP(UINT32_C(0x002d79e4)); /* 0040982d daddu s3,v0,zero */
 set(m,19u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d79e8));goto dispatch;
L_002d79e8:
 STEP(UINT32_C(0x002d79e8)); /* 2450ffff addiu s0,v0,-1 */
 set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d79ec));goto dispatch;
L_002d79ec:
 STEP(UINT32_C(0x002d79ec)); /* 1a000047 blez s0,zero,002d7b0c */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d79f0));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000200),&value32,4u);set(m,6u,sx(value32));target=sx(taken?UINT32_C(0x002d7b0c):UINT32_C(0x002d79f4));goto dispatch;}
L_002d79f0:
 STEP(UINT32_C(0x002d79f0)); /* 8fa60200 lw a2,0x200(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000200),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d79f4));goto dispatch;
L_002d79f4:
 STEP(UINT32_C(0x002d79f4)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d79f8));goto dispatch;
L_002d79f8:
 STEP(UINT32_C(0x002d79f8)); /* 1440001d bne v0,zero,002d7a70 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d79fc));set(m,7u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d7a70):UINT32_C(0x002d7a00));goto dispatch;}
L_002d79fc:
 STEP(UINT32_C(0x002d79fc)); /* 3c070055 lui a3,zero,0x55 */
 set(m,7u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d7a00));goto dispatch;
L_002d7a00:
 STEP(UINT32_C(0x002d7a00)); /* 24140010 addiu s4,zero,16 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7a04));goto dispatch;
L_002d7a04:
 STEP(UINT32_C(0x002d7a04)); /* 24f1b680 addiu s1,a3,-18816 */
 set(m,17u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d7a08));goto dispatch;
L_002d7a08:
 STEP(UINT32_C(0x002d7a08)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7a0c));goto dispatch;
L_002d7a0c:
 STEP(UINT32_C(0x002d7a0c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d7a10));goto dispatch;
L_002d7a10:
 STEP(UINT32_C(0x002d7a10)); /* ae710000 sw s1,0x0(s3) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7a14));goto dispatch;
L_002d7a14:
 STEP(UINT32_C(0x002d7a14)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7a18));goto dispatch;
L_002d7a18:
 STEP(UINT32_C(0x002d7a18)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7a1c));goto dispatch;
L_002d7a1c:
 STEP(UINT32_C(0x002d7a1c)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7a20));goto dispatch;
L_002d7a20:
 STEP(UINT32_C(0x002d7a20)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7a24));goto dispatch;
L_002d7a24:
 STEP(UINT32_C(0x002d7a24)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7a28));goto dispatch;
L_002d7a28:
 STEP(UINT32_C(0x002d7a28)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d7a2c));goto dispatch;
L_002d7a2c:
 STEP(UINT32_C(0x002d7a2c)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7a30));goto dispatch;
L_002d7a30:
 STEP(UINT32_C(0x002d7a30)); /* 14800009 bne a0,zero,002d7a58 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7a34));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7a58):UINT32_C(0x002d7a38));goto dispatch;}
L_002d7a34:
 STEP(UINT32_C(0x002d7a34)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7a38));goto dispatch;
L_002d7a38:
 STEP(UINT32_C(0x002d7a38)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7a3c));goto dispatch;
L_002d7a3c:
 STEP(UINT32_C(0x002d7a3c)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7a40));goto dispatch;
L_002d7a40:
 STEP(UINT32_C(0x002d7a40)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7a48));STEP(UINT32_C(0x002d7a44));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7a44:
 STEP(UINT32_C(0x002d7a44)); /* 7fa70230 sq a3,0x230(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d7a48));goto dispatch;
L_002d7a48:
 STEP(UINT32_C(0x002d7a48)); /* 14400095 bne v0,zero,002d7ca0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7a4c));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(taken?UINT32_C(0x002d7ca0):UINT32_C(0x002d7a50));goto dispatch;}
L_002d7a4c:
 STEP(UINT32_C(0x002d7a4c)); /* 7ba70230 lq a3,0x230(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x002d7a50));goto dispatch;
L_002d7a50:
 STEP(UINT32_C(0x002d7a50)); /* 27a30020 addiu v1,sp,32 */
 set(m,3u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7a54));goto dispatch;
L_002d7a54:
 STEP(UINT32_C(0x002d7a54)); /* 0060982d daddu s3,v1,zero */
 set(m,19u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d7a58));goto dispatch;
L_002d7a58:
 STEP(UINT32_C(0x002d7a58)); /* 2610fff0 addiu s0,s0,-16 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d7a5c));goto dispatch;
L_002d7a5c:
 STEP(UINT32_C(0x002d7a5c)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d7a60));goto dispatch;
L_002d7a60:
 STEP(UINT32_C(0x002d7a60)); /* 5040ffeb beql v0,zero,002d7a10 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d7a64));value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7a10));}else target=sx(UINT32_C(0x002d7a68));goto dispatch;
L_002d7a64:
 STEP(UINT32_C(0x002d7a64)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7a68));goto dispatch;
L_002d7a68:
 STEP(UINT32_C(0x002d7a68)); /* 10000002 beq zero,zero,002d7a74 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7a6c));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d7a74):UINT32_C(0x002d7a70));goto dispatch;}
L_002d7a6c:
 STEP(UINT32_C(0x002d7a6c)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7a70));goto dispatch;
L_002d7a70:
 STEP(UINT32_C(0x002d7a70)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7a74));goto dispatch;
L_002d7a74:
 STEP(UINT32_C(0x002d7a74)); /* 24e2b680 addiu v0,a3,-18816 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb680)));target=sx(UINT32_C(0x002d7a78));goto dispatch;
L_002d7a78:
 STEP(UINT32_C(0x002d7a78)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7a7c));goto dispatch;
L_002d7a7c:
 STEP(UINT32_C(0x002d7a7c)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7a80));goto dispatch;
L_002d7a80:
 STEP(UINT32_C(0x002d7a80)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7a84));goto dispatch;
L_002d7a84:
 STEP(UINT32_C(0x002d7a84)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7a88));goto dispatch;
L_002d7a88:
 STEP(UINT32_C(0x002d7a88)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7a8c));goto dispatch;
L_002d7a8c:
 STEP(UINT32_C(0x002d7a8c)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d7a90));goto dispatch;
L_002d7a90:
 STEP(UINT32_C(0x002d7a90)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d7a94));goto dispatch;
L_002d7a94:
 STEP(UINT32_C(0x002d7a94)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7a98));goto dispatch;
L_002d7a98:
 STEP(UINT32_C(0x002d7a98)); /* 1480001b bne a0,zero,002d7b08 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7a9c));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7b08):UINT32_C(0x002d7aa0));goto dispatch;}
L_002d7a9c:
 STEP(UINT32_C(0x002d7a9c)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7aa0));goto dispatch;
L_002d7aa0:
 STEP(UINT32_C(0x002d7aa0)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7aa4));goto dispatch;
L_002d7aa4:
 STEP(UINT32_C(0x002d7aa4)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7aac));STEP(UINT32_C(0x002d7aa8));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7aa8:
 STEP(UINT32_C(0x002d7aa8)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7aac));goto dispatch;
L_002d7aac:
 STEP(UINT32_C(0x002d7aac)); /* 1440007d bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7ab0));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7ab4));goto dispatch;}
L_002d7ab0:
 STEP(UINT32_C(0x002d7ab0)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7ab4));goto dispatch;
L_002d7ab4:
 STEP(UINT32_C(0x002d7ab4)); /* 27a40020 addiu a0,sp,32 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7ab8));goto dispatch;
L_002d7ab8:
 STEP(UINT32_C(0x002d7ab8)); /* 10000013 beq zero,zero,002d7b08 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7abc));set(m,19u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d7b08):UINT32_C(0x002d7ac0));goto dispatch;}
L_002d7abc:
 STEP(UINT32_C(0x002d7abc)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d7ac0));goto dispatch;
L_002d7ac0:
 STEP(UINT32_C(0x002d7ac0)); /* ae750000 sw s5,0x0(s3) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7ac4));goto dispatch;
L_002d7ac4:
 STEP(UINT32_C(0x002d7ac4)); /* ae620004 sw v0,0x4(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7ac8));goto dispatch;
L_002d7ac8:
 STEP(UINT32_C(0x002d7ac8)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7acc));goto dispatch;
L_002d7acc:
 STEP(UINT32_C(0x002d7acc)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7ad0));goto dispatch;
L_002d7ad0:
 STEP(UINT32_C(0x002d7ad0)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7ad4));goto dispatch;
L_002d7ad4:
 STEP(UINT32_C(0x002d7ad4)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7ad8));goto dispatch;
L_002d7ad8:
 STEP(UINT32_C(0x002d7ad8)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7adc));goto dispatch;
L_002d7adc:
 STEP(UINT32_C(0x002d7adc)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d7ae0));goto dispatch;
L_002d7ae0:
 STEP(UINT32_C(0x002d7ae0)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7ae4));goto dispatch;
L_002d7ae4:
 STEP(UINT32_C(0x002d7ae4)); /* 14800008 bne a0,zero,002d7b08 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7ae8));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7b08):UINT32_C(0x002d7aec));goto dispatch;}
L_002d7ae8:
 STEP(UINT32_C(0x002d7ae8)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7aec));goto dispatch;
L_002d7aec:
 STEP(UINT32_C(0x002d7aec)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7af0));goto dispatch;
L_002d7af0:
 STEP(UINT32_C(0x002d7af0)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7af8));STEP(UINT32_C(0x002d7af4));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7af4:
 STEP(UINT32_C(0x002d7af4)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7af8));goto dispatch;
L_002d7af8:
 STEP(UINT32_C(0x002d7af8)); /* 1440006a bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7afc));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7b00));goto dispatch;}
L_002d7afc:
 STEP(UINT32_C(0x002d7afc)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7b00));goto dispatch;
L_002d7b00:
 STEP(UINT32_C(0x002d7b00)); /* 27a50020 addiu a1,sp,32 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7b04));goto dispatch;
L_002d7b04:
 STEP(UINT32_C(0x002d7b04)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d7b08));goto dispatch;
L_002d7b08:
 STEP(UINT32_C(0x002d7b08)); /* 8fa60200 lw a2,0x200(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000200),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d7b0c));goto dispatch;
L_002d7b0c:
 STEP(UINT32_C(0x002d7b0c)); /* ae7d0000 sw sp,0x0(s3) */
 value32=(uint32_t)lo(m,29u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7b10));goto dispatch;
L_002d7b10:
 STEP(UINT32_C(0x002d7b10)); /* ae660004 sw a2,0x4(s3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7b14));goto dispatch;
L_002d7b14:
 STEP(UINT32_C(0x002d7b14)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7b18));goto dispatch;
L_002d7b18:
 STEP(UINT32_C(0x002d7b18)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7b1c));goto dispatch;
L_002d7b1c:
 STEP(UINT32_C(0x002d7b1c)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7b20));goto dispatch;
L_002d7b20:
 STEP(UINT32_C(0x002d7b20)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7b24));goto dispatch;
L_002d7b24:
 STEP(UINT32_C(0x002d7b24)); /* 00661821 addu v1,v1,a2 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d7b28));goto dispatch;
L_002d7b28:
 STEP(UINT32_C(0x002d7b28)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d7b2c));goto dispatch;
L_002d7b2c:
 STEP(UINT32_C(0x002d7b2c)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7b30));goto dispatch;
L_002d7b30:
 STEP(UINT32_C(0x002d7b30)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7b34));goto dispatch;
L_002d7b34:
 STEP(UINT32_C(0x002d7b34)); /* 14800009 bne a0,zero,002d7b5c */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7b38));set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(taken?UINT32_C(0x002d7b5c):UINT32_C(0x002d7b3c));goto dispatch;}
L_002d7b38:
 STEP(UINT32_C(0x002d7b38)); /* 32e20004 andi v0,s7,0x4 */
 set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(UINT32_C(0x002d7b3c));goto dispatch;
L_002d7b3c:
 STEP(UINT32_C(0x002d7b3c)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7b40));goto dispatch;
L_002d7b40:
 STEP(UINT32_C(0x002d7b40)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7b48));STEP(UINT32_C(0x002d7b44));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7b44:
 STEP(UINT32_C(0x002d7b44)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7b48));goto dispatch;
L_002d7b48:
 STEP(UINT32_C(0x002d7b48)); /* 14400056 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7b4c));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7b50));goto dispatch;}
L_002d7b4c:
 STEP(UINT32_C(0x002d7b4c)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7b50));goto dispatch;
L_002d7b50:
 STEP(UINT32_C(0x002d7b50)); /* 27a20020 addiu v0,sp,32 */
 set(m,2u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7b54));goto dispatch;
L_002d7b54:
 STEP(UINT32_C(0x002d7b54)); /* 0040982d daddu s3,v0,zero */
 set(m,19u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d7b58));goto dispatch;
L_002d7b58:
 STEP(UINT32_C(0x002d7b58)); /* 32e20004 andi v0,s7,0x4 */
 set(m,2u,lo(m,23u) & UINT64_C(0x4));target=sx(UINT32_C(0x002d7b5c));goto dispatch;
L_002d7b5c:
 STEP(UINT32_C(0x002d7b5c)); /* 10400034 beq v0,zero,002d7c30 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d7b60));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);set(m,3u,sx(value32));target=sx(taken?UINT32_C(0x002d7c30):UINT32_C(0x002d7b64));goto dispatch;}
L_002d7b60:
 STEP(UINT32_C(0x002d7b60)); /* 8fa301f0 lw v1,0x1f0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7b64));goto dispatch;
L_002d7b64:
 STEP(UINT32_C(0x002d7b64)); /* 8fa40208 lw a0,0x208(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7b68));goto dispatch;
L_002d7b68:
 STEP(UINT32_C(0x002d7b68)); /* 00648023 subu s0,v1,a0 */
 set(m,16u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d7b6c));goto dispatch;
L_002d7b6c:
 STEP(UINT32_C(0x002d7b6c)); /* 1a000032 blez s0,zero,002d7c38 */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d7b70));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);set(m,6u,sx(value32));target=sx(taken?UINT32_C(0x002d7c38):UINT32_C(0x002d7b74));goto dispatch;}
L_002d7b70:
 STEP(UINT32_C(0x002d7b70)); /* 8fa60208 lw a2,0x208(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d7b74));goto dispatch;
L_002d7b74:
 STEP(UINT32_C(0x002d7b74)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d7b78));goto dispatch;
L_002d7b78:
 STEP(UINT32_C(0x002d7b78)); /* 1440001d bne v0,zero,002d7bf0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7b7c));set(m,7u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002d7bf0):UINT32_C(0x002d7b80));goto dispatch;}
L_002d7b7c:
 STEP(UINT32_C(0x002d7b7c)); /* 3c070055 lui a3,zero,0x55 */
 set(m,7u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002d7b80));goto dispatch;
L_002d7b80:
 STEP(UINT32_C(0x002d7b80)); /* 24140010 addiu s4,zero,16 */
 set(m,20u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7b84));goto dispatch;
L_002d7b84:
 STEP(UINT32_C(0x002d7b84)); /* 24f1b670 addiu s1,a3,-18832 */
 set(m,17u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb670)));target=sx(UINT32_C(0x002d7b88));goto dispatch;
L_002d7b88:
 STEP(UINT32_C(0x002d7b88)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7b8c));goto dispatch;
L_002d7b8c:
 STEP(UINT32_C(0x002d7b8c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d7b90));goto dispatch;
L_002d7b90:
 STEP(UINT32_C(0x002d7b90)); /* ae710000 sw s1,0x0(s3) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7b94));goto dispatch;
L_002d7b94:
 STEP(UINT32_C(0x002d7b94)); /* 26730008 addiu s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d7b98));goto dispatch;
L_002d7b98:
 STEP(UINT32_C(0x002d7b98)); /* 8fa20014 lw v0,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7b9c));goto dispatch;
L_002d7b9c:
 STEP(UINT32_C(0x002d7b9c)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7ba0));goto dispatch;
L_002d7ba0:
 STEP(UINT32_C(0x002d7ba0)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7ba4));goto dispatch;
L_002d7ba4:
 STEP(UINT32_C(0x002d7ba4)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7ba8));goto dispatch;
L_002d7ba8:
 STEP(UINT32_C(0x002d7ba8)); /* 28440008 slti a0,v0,8 */
 set(m,4u,((int64_t)lo(m,2u)<INT64_C(8)));target=sx(UINT32_C(0x002d7bac));goto dispatch;
L_002d7bac:
 STEP(UINT32_C(0x002d7bac)); /* afa30018 sw v1,0x18(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7bb0));goto dispatch;
L_002d7bb0:
 STEP(UINT32_C(0x002d7bb0)); /* 14800009 bne a0,zero,002d7bd8 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7bb4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7bd8):UINT32_C(0x002d7bb8));goto dispatch;}
L_002d7bb4:
 STEP(UINT32_C(0x002d7bb4)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7bb8));goto dispatch;
L_002d7bb8:
 STEP(UINT32_C(0x002d7bb8)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7bbc));goto dispatch;
L_002d7bbc:
 STEP(UINT32_C(0x002d7bbc)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7bc0));goto dispatch;
L_002d7bc0:
 STEP(UINT32_C(0x002d7bc0)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7bc8));STEP(UINT32_C(0x002d7bc4));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7bc4:
 STEP(UINT32_C(0x002d7bc4)); /* 7fa70230 sq a3,0x230(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000230),m->gpr[7],16u);target=sx(UINT32_C(0x002d7bc8));goto dispatch;
L_002d7bc8:
 STEP(UINT32_C(0x002d7bc8)); /* 14400035 bne v0,zero,002d7ca0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7bcc));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(taken?UINT32_C(0x002d7ca0):UINT32_C(0x002d7bd0));goto dispatch;}
L_002d7bcc:
 STEP(UINT32_C(0x002d7bcc)); /* 7ba70230 lq a3,0x230(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x002d7bd0));goto dispatch;
L_002d7bd0:
 STEP(UINT32_C(0x002d7bd0)); /* 27a50020 addiu a1,sp,32 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7bd4));goto dispatch;
L_002d7bd4:
 STEP(UINT32_C(0x002d7bd4)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d7bd8));goto dispatch;
L_002d7bd8:
 STEP(UINT32_C(0x002d7bd8)); /* 2610fff0 addiu s0,s0,-16 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d7bdc));goto dispatch;
L_002d7bdc:
 STEP(UINT32_C(0x002d7bdc)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002d7be0));goto dispatch;
L_002d7be0:
 STEP(UINT32_C(0x002d7be0)); /* 5040ffeb beql v0,zero,002d7b90 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d7be4));value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7b90));}else target=sx(UINT32_C(0x002d7be8));goto dispatch;
L_002d7be4:
 STEP(UINT32_C(0x002d7be4)); /* ae740004 sw s4,0x4(s3) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7be8));goto dispatch;
L_002d7be8:
 STEP(UINT32_C(0x002d7be8)); /* 10000002 beq zero,zero,002d7bf4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7bec));value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d7bf4):UINT32_C(0x002d7bf0));goto dispatch;}
L_002d7bec:
 STEP(UINT32_C(0x002d7bec)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7bf0));goto dispatch;
L_002d7bf0:
 STEP(UINT32_C(0x002d7bf0)); /* ae700004 sw s0,0x4(s3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d7bf4));goto dispatch;
L_002d7bf4:
 STEP(UINT32_C(0x002d7bf4)); /* 24e2b670 addiu v0,a3,-18832 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffb670)));target=sx(UINT32_C(0x002d7bf8));goto dispatch;
L_002d7bf8:
 STEP(UINT32_C(0x002d7bf8)); /* ae620000 sw v0,0x0(s3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d7bfc));goto dispatch;
L_002d7bfc:
 STEP(UINT32_C(0x002d7bfc)); /* 8fa30014 lw v1,0x14(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7c00));goto dispatch;
L_002d7c00:
 STEP(UINT32_C(0x002d7c00)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7c04));goto dispatch;
L_002d7c04:
 STEP(UINT32_C(0x002d7c04)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d7c08));goto dispatch;
L_002d7c08:
 STEP(UINT32_C(0x002d7c08)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d7c0c));goto dispatch;
L_002d7c0c:
 STEP(UINT32_C(0x002d7c0c)); /* 28640008 slti a0,v1,8 */
 set(m,4u,((int64_t)lo(m,3u)<INT64_C(8)));target=sx(UINT32_C(0x002d7c10));goto dispatch;
L_002d7c10:
 STEP(UINT32_C(0x002d7c10)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d7c14));goto dispatch;
L_002d7c14:
 STEP(UINT32_C(0x002d7c14)); /* 14800006 bne a0,zero,002d7c30 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d7c18));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002d7c30):UINT32_C(0x002d7c1c));goto dispatch;}
L_002d7c18:
 STEP(UINT32_C(0x002d7c18)); /* afa30014 sw v1,0x14(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7c1c));goto dispatch;
L_002d7c1c:
 STEP(UINT32_C(0x002d7c1c)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7c20));goto dispatch;
L_002d7c20:
 STEP(UINT32_C(0x002d7c20)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7c28));STEP(UINT32_C(0x002d7c24));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7c24:
 STEP(UINT32_C(0x002d7c24)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7c28));goto dispatch;
L_002d7c28:
 STEP(UINT32_C(0x002d7c28)); /* 1440001e bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7c2c));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7c30));goto dispatch;}
L_002d7c2c:
 STEP(UINT32_C(0x002d7c2c)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7c30));goto dispatch;
L_002d7c30:
 STEP(UINT32_C(0x002d7c30)); /* 8fa60208 lw a2,0x208(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002d7c34));goto dispatch;
L_002d7c34:
 STEP(UINT32_C(0x002d7c34)); /* 8fa301f0 lw v1,0x1f0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7c38));goto dispatch;
L_002d7c38:
 STEP(UINT32_C(0x002d7c38)); /* 8fa401f0 lw a0,0x1f0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7c3c));goto dispatch;
L_002d7c3c:
 STEP(UINT32_C(0x002d7c3c)); /* 00c3102a slt v0,a2,v1 */
 set(m,2u,((int64_t)lo(m,6u)<(int64_t)lo(m,3u)));target=sx(UINT32_C(0x002d7c40));goto dispatch;
L_002d7c40:
 STEP(UINT32_C(0x002d7c40)); /* 8fa30018 lw v1,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d7c44));goto dispatch;
L_002d7c44:
 STEP(UINT32_C(0x002d7c44)); /* 8fa501ec lw a1,0x1ec(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d7c48));goto dispatch;
L_002d7c48:
 STEP(UINT32_C(0x002d7c48)); /* 00c2200a movz a0,a2,v0 */
 if(lo(m,2u)==0u)set(m,4u,lo(m,6u));target=sx(UINT32_C(0x002d7c4c));goto dispatch;
L_002d7c4c:
 STEP(UINT32_C(0x002d7c4c)); /* 00a42821 addu a1,a1,a0 */
 set(m,5u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002d7c50));goto dispatch;
L_002d7c50:
 STEP(UINT32_C(0x002d7c50)); /* 10600006 beq v1,zero,002d7c6c */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002d7c54));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);target=sx(taken?UINT32_C(0x002d7c6c):UINT32_C(0x002d7c58));goto dispatch;}
L_002d7c54:
 STEP(UINT32_C(0x002d7c54)); /* afa501ec sw a1,0x1ec(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);target=sx(UINT32_C(0x002d7c58));goto dispatch;
L_002d7c58:
 STEP(UINT32_C(0x002d7c58)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7c5c));goto dispatch;
L_002d7c5c:
 STEP(UINT32_C(0x002d7c5c)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7c64));STEP(UINT32_C(0x002d7c60));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7c60:
 STEP(UINT32_C(0x002d7c60)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7c64));goto dispatch;
L_002d7c64:
 STEP(UINT32_C(0x002d7c64)); /* 1440000f bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7c68));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7c6c));goto dispatch;}
L_002d7c68:
 STEP(UINT32_C(0x002d7c68)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7c6c));goto dispatch;
L_002d7c6c:
 STEP(UINT32_C(0x002d7c6c)); /* 27a60020 addiu a2,sp,32 */
 set(m,6u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d7c70));goto dispatch;
L_002d7c70:
 STEP(UINT32_C(0x002d7c70)); /* afa00014 sw zero,0x14(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7c74));goto dispatch;
L_002d7c74:
 STEP(UINT32_C(0x002d7c74)); /* 1000fab4 beq zero,zero,002d6748 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d7c78));set(m,19u,lo(m,6u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6748):UINT32_C(0x002d7c7c));goto dispatch;}
L_002d7c78:
 STEP(UINT32_C(0x002d7c78)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d7c7c));goto dispatch;
L_002d7c7c:
 STEP(UINT32_C(0x002d7c7c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d7c80));goto dispatch;
L_002d7c80:
 STEP(UINT32_C(0x002d7c80)); /* 8fa20018 lw v0,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7c84));goto dispatch;
L_002d7c84:
 STEP(UINT32_C(0x002d7c84)); /* 10400005 beq v0,zero,002d7c9c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d7c88));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x002d7c9c):UINT32_C(0x002d7c8c));goto dispatch;}
L_002d7c88:
 STEP(UINT32_C(0x002d7c88)); /* 8fa401e8 lw a0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7c8c));goto dispatch;
L_002d7c8c:
 STEP(UINT32_C(0x002d7c8c)); /* 0c0b5940 jal 002d6500 */
 set(m,31u,UINT64_C(0x002d7c94));STEP(UINT32_C(0x002d7c90));set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6500));goto dispatch;
L_002d7c90:
 STEP(UINT32_C(0x002d7c90)); /* 27a50010 addiu a1,sp,16 */
 set(m,5u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d7c94));goto dispatch;
L_002d7c94:
 STEP(UINT32_C(0x002d7c94)); /* 14400003 bne v0,zero,002d7ca4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d7c98));READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002d7ca4):UINT32_C(0x002d7c9c));goto dispatch;}
L_002d7c98:
 STEP(UINT32_C(0x002d7c98)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7c9c));goto dispatch;
L_002d7c9c:
 STEP(UINT32_C(0x002d7c9c)); /* afa00014 sw zero,0x14(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d7ca0));goto dispatch;
L_002d7ca0:
 STEP(UINT32_C(0x002d7ca0)); /* 8fa201e8 lw v0,0x1e8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d7ca4));goto dispatch;
L_002d7ca4:
 STEP(UINT32_C(0x002d7ca4)); /* 8fa401ec lw a0,0x1ec(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001ec),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d7ca8));goto dispatch;
L_002d7ca8:
 STEP(UINT32_C(0x002d7ca8)); /* 9443000c lhu v1,0xc(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d7cac));goto dispatch;
L_002d7cac:
 STEP(UINT32_C(0x002d7cac)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d7cb0));goto dispatch;
L_002d7cb0:
 STEP(UINT32_C(0x002d7cb0)); /* 30630040 andi v1,v1,0x40 */
 set(m,3u,lo(m,3u) & UINT64_C(0x40));target=sx(UINT32_C(0x002d7cb4));goto dispatch;
L_002d7cb4:
 STEP(UINT32_C(0x002d7cb4)); /* 0083100a movz v0,a0,v1 */
 if(lo(m,3u)==0u)set(m,2u,lo(m,4u));target=sx(UINT32_C(0x002d7cb8));goto dispatch;
L_002d7cb8:
 STEP(UINT32_C(0x002d7cb8)); /* dfb00240 ld s0,0x240(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000240),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d7cbc));goto dispatch;
L_002d7cbc:
 STEP(UINT32_C(0x002d7cbc)); /* dfb10248 ld s1,0x248(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000248),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d7cc0));goto dispatch;
L_002d7cc0:
 STEP(UINT32_C(0x002d7cc0)); /* dfb20250 ld s2,0x250(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000250),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002d7cc4));goto dispatch;
L_002d7cc4:
 STEP(UINT32_C(0x002d7cc4)); /* dfb30258 ld s3,0x258(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000258),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002d7cc8));goto dispatch;
L_002d7cc8:
 STEP(UINT32_C(0x002d7cc8)); /* dfb40260 ld s4,0x260(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000260),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002d7ccc));goto dispatch;
L_002d7ccc:
 STEP(UINT32_C(0x002d7ccc)); /* dfb50268 ld s5,0x268(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000268),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002d7cd0));goto dispatch;
L_002d7cd0:
 STEP(UINT32_C(0x002d7cd0)); /* dfb60270 ld s6,0x270(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000270),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002d7cd4));goto dispatch;
L_002d7cd4:
 STEP(UINT32_C(0x002d7cd4)); /* dfb70278 ld s7,0x278(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000278),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002d7cd8));goto dispatch;
L_002d7cd8:
 STEP(UINT32_C(0x002d7cd8)); /* dfbe0280 ld s8,0x280(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000280),&value64,8u);set(m,30u,value64);target=sx(UINT32_C(0x002d7cdc));goto dispatch;
L_002d7cdc:
 STEP(UINT32_C(0x002d7cdc)); /* dfbf0288 ld ra,0x288(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000288),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d7ce0));goto dispatch;
L_002d7ce0:
 STEP(UINT32_C(0x002d7ce0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d7ce4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000290)));goto dispatch;
L_002d7ce4:
 STEP(UINT32_C(0x002d7ce4)); /* 27bd0290 addiu sp,sp,656 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000290)));target=sx(UINT32_C(0x002d7ce8));goto dispatch;
L_002da340:
 STEP(UINT32_C(0x002da340)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002da344));goto dispatch;
L_002da344:
 STEP(UINT32_C(0x002da344)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002da348));goto dispatch;
L_002da348:
 STEP(UINT32_C(0x002da348)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002da34c));goto dispatch;
L_002da34c:
 STEP(UINT32_C(0x002da34c)); /* 8c44be28 lw a0,-0x41d8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbe28),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002da350));goto dispatch;
L_002da350:
 STEP(UINT32_C(0x002da350)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002da354));goto dispatch;
L_002da354:
 STEP(UINT32_C(0x002da354)); /* 080b68c2 j 002da308 */
 STEP(UINT32_C(0x002da358));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002da308));goto dispatch;
L_002da358:
 STEP(UINT32_C(0x002da358)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002da35c));goto dispatch;
L_002da308:
 STEP(UINT32_C(0x002da308)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002da30c));goto dispatch;
L_002da30c:
 STEP(UINT32_C(0x002da30c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002da310));set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb8d8)));goto dispatch;
L_002da310:
 STEP(UINT32_C(0x002da310)); /* 2442b8d8 addiu v0,v0,-18216 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb8d8)));target=sx(UINT32_C(0x002da314));goto dispatch;
L_002da4b8:
 STEP(UINT32_C(0x002da4b8)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002da4bc));goto dispatch;
L_002da4bc:
 STEP(UINT32_C(0x002da4bc)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002da4c0));goto dispatch;
L_002da4c0:
 STEP(UINT32_C(0x002da4c0)); /* 03a0182d daddu v1,sp,zero */
 set(m,3u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002da4c4));goto dispatch;
L_002da4c4:
 STEP(UINT32_C(0x002da4c4)); /* 10c00007 beq a2,zero,002da4e4 */
 {int taken=(lo(m,6u)==lo(m,0u));STEP(UINT32_C(0x002da4c8));if(lo(m,5u)!=0u)set(m,3u,lo(m,5u));target=sx(taken?UINT32_C(0x002da4e4):UINT32_C(0x002da4cc));goto dispatch;}
L_002da4c8:
 STEP(UINT32_C(0x002da4c8)); /* 00a5180b movn v1,a1,a1 */
 if(lo(m,5u)!=0u)set(m,3u,lo(m,5u));target=sx(UINT32_C(0x002da4cc));goto dispatch;
L_002da4cc:
 STEP(UINT32_C(0x002da4cc)); /* 10e00005 beq a3,zero,002da4e4 */
 {int taken=(lo(m,7u)==lo(m,0u));STEP(UINT32_C(0x002da4d0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002da4e4):UINT32_C(0x002da4d4));goto dispatch;}
L_002da4d0:
 STEP(UINT32_C(0x002da4d0)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002da4d4));goto dispatch;
L_002da4d4:
 STEP(UINT32_C(0x002da4d4)); /* 90c20000 lbu v0,0x0(a2) */
 {uint8_t byte;READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002da4d8));goto dispatch;
L_002da4d8:
 STEP(UINT32_C(0x002da4d8)); /* ac620000 sw v0,0x0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002da4dc));goto dispatch;
L_002da4dc:
 STEP(UINT32_C(0x002da4dc)); /* 90c20000 lbu v0,0x0(a2) */
 {uint8_t byte;READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002da4e0));goto dispatch;
L_002da4e0:
 STEP(UINT32_C(0x002da4e0)); /* 0002102b sltu v0,zero,v0 */
 set(m,2u,lo(m,0u)<lo(m,2u));target=sx(UINT32_C(0x002da4e4));goto dispatch;
L_002da4e4:
 STEP(UINT32_C(0x002da4e4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002da4e8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002da4e8:
 STEP(UINT32_C(0x002da4e8)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002da4ec));goto dispatch;
L_002d6500:
 STEP(UINT32_C(0x002d6500)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d6504));goto dispatch;
L_002d6504:
 STEP(UINT32_C(0x002d6504)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d6508));goto dispatch;
L_002d6508:
 STEP(UINT32_C(0x002d6508)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d650c));goto dispatch;
L_002d650c:
 STEP(UINT32_C(0x002d650c)); /* ffbf0008 sd ra,0x8(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d6510));goto dispatch;
L_002d6510:
 STEP(UINT32_C(0x002d6510)); /* 8e020008 lw v0,0x8(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6514));goto dispatch;
L_002d6514:
 STEP(UINT32_C(0x002d6514)); /* 14400004 bne v0,zero,002d6528 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6518));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6528):UINT32_C(0x002d651c));goto dispatch;}
L_002d6518:
 STEP(UINT32_C(0x002d6518)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d651c));goto dispatch;
L_002d651c:
 STEP(UINT32_C(0x002d651c)); /* 10000006 beq zero,zero,002d6538 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d6520));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x002d6538):UINT32_C(0x002d6524));goto dispatch;}
L_002d6520:
 STEP(UINT32_C(0x002d6520)); /* ae000004 sw zero,0x4(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d6524));goto dispatch;
L_002d6524:
 STEP(UINT32_C(0x002d6524)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6528));goto dispatch;
L_002d6528:
 STEP(UINT32_C(0x002d6528)); /* 0c0b6780 jal 002d9e00 */
 set(m,31u,UINT64_C(0x002d6530));STEP(UINT32_C(0x002d652c));/* nop */target=sx(UINT32_C(0x002d9e00));goto dispatch;
L_002d652c:
 STEP(UINT32_C(0x002d652c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6530));goto dispatch;
L_002d6530:
 STEP(UINT32_C(0x002d6530)); /* ae000004 sw zero,0x4(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d6534));goto dispatch;
L_002d6534:
 STEP(UINT32_C(0x002d6534)); /* ae000008 sw zero,0x8(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d6538));goto dispatch;
L_002d6538:
 STEP(UINT32_C(0x002d6538)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d653c));goto dispatch;
L_002d653c:
 STEP(UINT32_C(0x002d653c)); /* dfbf0008 ld ra,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d6540));goto dispatch;
L_002d6540:
 STEP(UINT32_C(0x002d6540)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d6544));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002d6544:
 STEP(UINT32_C(0x002d6544)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6548));goto dispatch;
L_002d9e00:
 STEP(UINT32_C(0x002d9e00)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x002d9e04));goto dispatch;
L_002d9e04:
 STEP(UINT32_C(0x002d9e04)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9e08));goto dispatch;
L_002d9e08:
 STEP(UINT32_C(0x002d9e08)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d9e0c));goto dispatch;
L_002d9e0c:
 STEP(UINT32_C(0x002d9e0c)); /* ffb60030 sd s6,0x30(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002d9e10));goto dispatch;
L_002d9e10:
 STEP(UINT32_C(0x002d9e10)); /* 00a0b02d daddu s6,a1,zero */
 set(m,22u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d9e14));goto dispatch;
L_002d9e14:
 STEP(UINT32_C(0x002d9e14)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d9e18));goto dispatch;
L_002d9e18:
 STEP(UINT32_C(0x002d9e18)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d9e1c));goto dispatch;
L_002d9e1c:
 STEP(UINT32_C(0x002d9e1c)); /* ffb30018 sd s3,0x18(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002d9e20));goto dispatch;
L_002d9e20:
 STEP(UINT32_C(0x002d9e20)); /* ffb40020 sd s4,0x20(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002d9e24));goto dispatch;
L_002d9e24:
 STEP(UINT32_C(0x002d9e24)); /* ffb50028 sd s5,0x28(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(UINT32_C(0x002d9e28));goto dispatch;
L_002d9e28:
 STEP(UINT32_C(0x002d9e28)); /* ffb70038 sd s7,0x38(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000038),&value64,8u);target=sx(UINT32_C(0x002d9e2c));goto dispatch;
L_002d9e2c:
 STEP(UINT32_C(0x002d9e2c)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002d9e30));goto dispatch;
L_002d9e30:
 STEP(UINT32_C(0x002d9e30)); /* 8ed20008 lw s2,0x8(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,18u,sx(value32));target=sx(UINT32_C(0x002d9e34));goto dispatch;
L_002d9e34:
 STEP(UINT32_C(0x002d9e34)); /* 124000df beq s2,zero,002da1b4 */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002d9e38));set(m,17u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x002da1b4):UINT32_C(0x002d9e3c));goto dispatch;}
L_002d9e38:
 STEP(UINT32_C(0x002d9e38)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d9e3c));goto dispatch;
L_002d9e3c:
 STEP(UINT32_C(0x002d9e3c)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d9e40));goto dispatch;
L_002d9e40:
 STEP(UINT32_C(0x002d9e40)); /* 30620008 andi v0,v1,0x8 */
 set(m,2u,lo(m,3u) & UINT64_C(0x8));target=sx(UINT32_C(0x002d9e44));goto dispatch;
L_002d9e44:
 STEP(UINT32_C(0x002d9e44)); /* 10400004 beq v0,zero,002d9e58 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d9e48));/* nop */target=sx(taken?UINT32_C(0x002d9e58):UINT32_C(0x002d9e4c));goto dispatch;}
L_002d9e48:
 STEP(UINT32_C(0x002d9e48)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9e4c));goto dispatch;
L_002d9e4c:
 STEP(UINT32_C(0x002d9e4c)); /* 8e220010 lw v0,0x10(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9e50));goto dispatch;
L_002d9e50:
 STEP(UINT32_C(0x002d9e50)); /* 14400007 bne v0,zero,002d9e70 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9e54));set(m,2u,lo(m,3u) & UINT64_C(0x2));target=sx(taken?UINT32_C(0x002d9e70):UINT32_C(0x002d9e58));goto dispatch;}
L_002d9e54:
 STEP(UINT32_C(0x002d9e54)); /* 30620002 andi v0,v1,0x2 */
 set(m,2u,lo(m,3u) & UINT64_C(0x2));target=sx(UINT32_C(0x002d9e58));goto dispatch;
L_002d9e58:
 STEP(UINT32_C(0x002d9e58)); /* 0c0b600e jal 002d8038 */
 set(m,31u,UINT64_C(0x002d9e60));STEP(UINT32_C(0x002d9e5c));/* nop */target=sx(UINT32_C(0x002d8038));goto dispatch;
L_002d9e5c:
 STEP(UINT32_C(0x002d9e5c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9e60));goto dispatch;
L_002d9e60:
 STEP(UINT32_C(0x002d9e60)); /* 144000d4 bne v0,zero,002da1b4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9e64));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002da1b4):UINT32_C(0x002d9e68));goto dispatch;}
L_002d9e64:
 STEP(UINT32_C(0x002d9e64)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d9e68));goto dispatch;
L_002d9e68:
 STEP(UINT32_C(0x002d9e68)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d9e6c));goto dispatch;
L_002d9e6c:
 STEP(UINT32_C(0x002d9e6c)); /* 30620002 andi v0,v1,0x2 */
 set(m,2u,lo(m,3u) & UINT64_C(0x2));target=sx(UINT32_C(0x002d9e70));goto dispatch;
L_002d9e70:
 STEP(UINT32_C(0x002d9e70)); /* 8ed40000 lw s4,0x0(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000000),&value32,4u);set(m,20u,sx(value32));target=sx(UINT32_C(0x002d9e74));goto dispatch;
L_002d9e74:
 STEP(UINT32_C(0x002d9e74)); /* 1040001e beq v0,zero,002d9ef0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d9e78));set(m,18u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d9ef0):UINT32_C(0x002d9e7c));goto dispatch;}
L_002d9e78:
 STEP(UINT32_C(0x002d9e78)); /* 0000902d daddu s2,zero,zero */
 set(m,18u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9e7c));goto dispatch;
L_002d9e7c:
 STEP(UINT32_C(0x002d9e7c)); /* 24150400 addiu s5,zero,1024 */
 set(m,21u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(UINT32_C(0x002d9e80));goto dispatch;
L_002d9e80:
 STEP(UINT32_C(0x002d9e80)); /* 56400009 bnel s2,zero,002d9ea8 */
 if(lo(m,18u)!=lo(m,0u)){STEP(UINT32_C(0x002d9e84));set(m,3u,(lo(m,18u)<UINT64_C(0x401)));target=sx(UINT32_C(0x002d9ea8));}else target=sx(UINT32_C(0x002d9e88));goto dispatch;
L_002d9e84:
 STEP(UINT32_C(0x002d9e84)); /* 2e430401 sltiu v1,s2,1025 */
 set(m,3u,(lo(m,18u)<UINT64_C(0x401)));target=sx(UINT32_C(0x002d9e88));goto dispatch;
L_002d9e88:
 STEP(UINT32_C(0x002d9e88)); /* 8e920004 lw s2,0x4(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000004),&value32,4u);set(m,18u,sx(value32));target=sx(UINT32_C(0x002d9e8c));goto dispatch;
L_002d9e8c:
 STEP(UINT32_C(0x002d9e8c)); /* 8e930000 lw s3,0x0(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);set(m,19u,sx(value32));target=sx(UINT32_C(0x002d9e90));goto dispatch;
L_002d9e90:
 STEP(UINT32_C(0x002d9e90)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9e94));goto dispatch;
L_002d9e94:
 STEP(UINT32_C(0x002d9e94)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9e98));goto dispatch;
L_002d9e98:
 STEP(UINT32_C(0x002d9e98)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9e9c));goto dispatch;
L_002d9e9c:
 STEP(UINT32_C(0x002d9e9c)); /* 1240fffa beq s2,zero,002d9e88 */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002d9ea0));set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002d9e88):UINT32_C(0x002d9ea4));goto dispatch;}
L_002d9ea0:
 STEP(UINT32_C(0x002d9ea0)); /* 26940008 addiu s4,s4,8 */
 set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d9ea4));goto dispatch;
L_002d9ea4:
 STEP(UINT32_C(0x002d9ea4)); /* 2e430401 sltiu v1,s2,1025 */
 set(m,3u,(lo(m,18u)<UINT64_C(0x401)));target=sx(UINT32_C(0x002d9ea8));goto dispatch;
L_002d9ea8:
 STEP(UINT32_C(0x002d9ea8)); /* 8e220024 lw v0,0x24(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9eac));goto dispatch;
L_002d9eac:
 STEP(UINT32_C(0x002d9eac)); /* 8e24001c lw a0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d9eb0));goto dispatch;
L_002d9eb0:
 STEP(UINT32_C(0x002d9eb0)); /* 02a0302d daddu a2,s5,zero */
 set(m,6u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002d9eb4));goto dispatch;
L_002d9eb4:
 STEP(UINT32_C(0x002d9eb4)); /* 0243300b movn a2,s2,v1 */
 if(lo(m,3u)!=0u)set(m,6u,lo(m,18u));target=sx(UINT32_C(0x002d9eb8));goto dispatch;
L_002d9eb8:
 STEP(UINT32_C(0x002d9eb8)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002d9ec0));STEP(UINT32_C(0x002d9ebc));set(m,5u,lo(m,19u)+lo(m,0u));goto dispatch;
L_002d9ebc:
 STEP(UINT32_C(0x002d9ebc)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d9ec0));goto dispatch;
L_002d9ec0:
 STEP(UINT32_C(0x002d9ec0)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d9ec4));goto dispatch;
L_002d9ec4:
 STEP(UINT32_C(0x002d9ec4)); /* 5a0000b8 blezl s0,zero,002da1a8 */
 if((int64_t)lo(m,16u)<=0){STEP(UINT32_C(0x002d9ec8));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002da1a8));}else target=sx(UINT32_C(0x002d9ecc));goto dispatch;
L_002d9ec8:
 STEP(UINT32_C(0x002d9ec8)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d9ecc));goto dispatch;
L_002d9ecc:
 STEP(UINT32_C(0x002d9ecc)); /* 8ec20008 lw v0,0x8(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9ed0));goto dispatch;
L_002d9ed0:
 STEP(UINT32_C(0x002d9ed0)); /* 02709821 addu s3,s3,s0 */
 set(m,19u,sx((uint32_t)lo(m,19u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d9ed4));goto dispatch;
L_002d9ed4:
 STEP(UINT32_C(0x002d9ed4)); /* 02509023 subu s2,s2,s0 */
 set(m,18u,sx((uint32_t)lo(m,18u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d9ed8));goto dispatch;
L_002d9ed8:
 STEP(UINT32_C(0x002d9ed8)); /* 00501023 subu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d9edc));goto dispatch;
L_002d9edc:
 STEP(UINT32_C(0x002d9edc)); /* 1440ffe8 bne v0,zero,002d9e80 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9ee0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002d9e80):UINT32_C(0x002d9ee4));goto dispatch;}
L_002d9ee0:
 STEP(UINT32_C(0x002d9ee0)); /* aec20008 sw v0,0x8(s6) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9ee4));goto dispatch;
L_002d9ee4:
 STEP(UINT32_C(0x002d9ee4)); /* 100000b3 beq zero,zero,002da1b4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9ee8));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002da1b4):UINT32_C(0x002d9eec));goto dispatch;}
L_002d9ee8:
 STEP(UINT32_C(0x002d9ee8)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9eec));goto dispatch;
L_002d9eec:
 STEP(UINT32_C(0x002d9eec)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9ef0));goto dispatch;
L_002d9ef0:
 STEP(UINT32_C(0x002d9ef0)); /* 30620001 andi v0,v1,0x1 */
 set(m,2u,lo(m,3u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d9ef4));goto dispatch;
L_002d9ef4:
 STEP(UINT32_C(0x002d9ef4)); /* 14400052 bne v0,zero,002da040 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d9ef8));set(m,23u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002da040):UINT32_C(0x002d9efc));goto dispatch;}
L_002d9ef8:
 STEP(UINT32_C(0x002d9ef8)); /* 0000b82d daddu s7,zero,zero */
 set(m,23u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9efc));goto dispatch;
L_002d9efc:
 STEP(UINT32_C(0x002d9efc)); /* 10000004 beq zero,zero,002d9f10 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9f00));/* nop */target=sx(taken?UINT32_C(0x002d9f10):UINT32_C(0x002d9f04));goto dispatch;}
L_002d9f00:
 STEP(UINT32_C(0x002d9f00)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9f04));goto dispatch;
L_002d9f04:
 STEP(UINT32_C(0x002d9f04)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9f08));goto dispatch;
L_002d9f08:
 STEP(UINT32_C(0x002d9f08)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d9f0c));goto dispatch;
L_002d9f0c:
 STEP(UINT32_C(0x002d9f0c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9f10));goto dispatch;
L_002d9f10:
 STEP(UINT32_C(0x002d9f10)); /* 16400009 bne s2,zero,002d9f38 */
 {int taken=(lo(m,18u)!=lo(m,0u));STEP(UINT32_C(0x002d9f14));set(m,2u,lo(m,3u) & UINT64_C(0x200));target=sx(taken?UINT32_C(0x002d9f38):UINT32_C(0x002d9f18));goto dispatch;}
L_002d9f14:
 STEP(UINT32_C(0x002d9f14)); /* 30620200 andi v0,v1,0x200 */
 set(m,2u,lo(m,3u) & UINT64_C(0x200));target=sx(UINT32_C(0x002d9f18));goto dispatch;
L_002d9f18:
 STEP(UINT32_C(0x002d9f18)); /* 8e920004 lw s2,0x4(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000004),&value32,4u);set(m,18u,sx(value32));target=sx(UINT32_C(0x002d9f1c));goto dispatch;
L_002d9f1c:
 STEP(UINT32_C(0x002d9f1c)); /* 8e930000 lw s3,0x0(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);set(m,19u,sx(value32));target=sx(UINT32_C(0x002d9f20));goto dispatch;
L_002d9f20:
 STEP(UINT32_C(0x002d9f20)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9f24));goto dispatch;
L_002d9f24:
 STEP(UINT32_C(0x002d9f24)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9f28));goto dispatch;
L_002d9f28:
 STEP(UINT32_C(0x002d9f28)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9f2c));goto dispatch;
L_002d9f2c:
 STEP(UINT32_C(0x002d9f2c)); /* 1240fffa beq s2,zero,002d9f18 */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002d9f30));set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002d9f18):UINT32_C(0x002d9f34));goto dispatch;}
L_002d9f30:
 STEP(UINT32_C(0x002d9f30)); /* 26940008 addiu s4,s4,8 */
 set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d9f34));goto dispatch;
L_002d9f34:
 STEP(UINT32_C(0x002d9f34)); /* 30620200 andi v0,v1,0x200 */
 set(m,2u,lo(m,3u) & UINT64_C(0x200));target=sx(UINT32_C(0x002d9f38));goto dispatch;
L_002d9f38:
 STEP(UINT32_C(0x002d9f38)); /* 1040000d beq v0,zero,002d9f70 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d9f3c));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002d9f70):UINT32_C(0x002d9f40));goto dispatch;}
L_002d9f3c:
 STEP(UINT32_C(0x002d9f3c)); /* 8e300008 lw s0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d9f40));goto dispatch;
L_002d9f40:
 STEP(UINT32_C(0x002d9f40)); /* 0250102b sltu v0,s2,s0 */
 set(m,2u,lo(m,18u)<lo(m,16u));target=sx(UINT32_C(0x002d9f44));goto dispatch;
L_002d9f44:
 STEP(UINT32_C(0x002d9f44)); /* 8e240000 lw a0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d9f48));goto dispatch;
L_002d9f48:
 STEP(UINT32_C(0x002d9f48)); /* 0242800b movn s0,s2,v0 */
 if(lo(m,2u)!=0u)set(m,16u,lo(m,18u));target=sx(UINT32_C(0x002d9f4c));goto dispatch;
L_002d9f4c:
 STEP(UINT32_C(0x002d9f4c)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d9f50));goto dispatch;
L_002d9f50:
 STEP(UINT32_C(0x002d9f50)); /* 0c0b5115 jal 002d4454 */
 set(m,31u,UINT64_C(0x002d9f58));STEP(UINT32_C(0x002d9f54));set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d4454));goto dispatch;
L_002d9f54:
 STEP(UINT32_C(0x002d9f54)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d9f58));goto dispatch;
L_002d9f58:
 STEP(UINT32_C(0x002d9f58)); /* 8e230008 lw v1,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9f5c));goto dispatch;
L_002d9f5c:
 STEP(UINT32_C(0x002d9f5c)); /* 8e220000 lw v0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9f60));goto dispatch;
L_002d9f60:
 STEP(UINT32_C(0x002d9f60)); /* 00701823 subu v1,v1,s0 */
 set(m,3u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d9f64));goto dispatch;
L_002d9f64:
 STEP(UINT32_C(0x002d9f64)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d9f68));goto dispatch;
L_002d9f68:
 STEP(UINT32_C(0x002d9f68)); /* 1000002a beq zero,zero,002da014 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9f6c));set(m,16u,lo(m,18u)+lo(m,0u));target=sx(taken?UINT32_C(0x002da014):UINT32_C(0x002d9f70));goto dispatch;}
L_002d9f6c:
 STEP(UINT32_C(0x002d9f6c)); /* 0240802d daddu s0,s2,zero */
 set(m,16u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d9f70));goto dispatch;
L_002d9f70:
 STEP(UINT32_C(0x002d9f70)); /* 8e240000 lw a0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d9f74));goto dispatch;
L_002d9f74:
 STEP(UINT32_C(0x002d9f74)); /* 8e220010 lw v0,0x10(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9f78));goto dispatch;
L_002d9f78:
 STEP(UINT32_C(0x002d9f78)); /* 0044102b sltu v0,v0,a0 */
 set(m,2u,lo(m,2u)<lo(m,4u));target=sx(UINT32_C(0x002d9f7c));goto dispatch;
L_002d9f7c:
 STEP(UINT32_C(0x002d9f7c)); /* 50400010 beql v0,zero,002d9fc0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d9f80));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d9fc0));}else target=sx(UINT32_C(0x002d9f84));goto dispatch;
L_002d9f80:
 STEP(UINT32_C(0x002d9f80)); /* 8e300014 lw s0,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d9f84));goto dispatch;
L_002d9f84:
 STEP(UINT32_C(0x002d9f84)); /* 0212102b sltu v0,s0,s2 */
 set(m,2u,lo(m,16u)<lo(m,18u));target=sx(UINT32_C(0x002d9f88));goto dispatch;
L_002d9f88:
 STEP(UINT32_C(0x002d9f88)); /* 5040000d beql v0,zero,002d9fc0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d9f8c));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d9fc0));}else target=sx(UINT32_C(0x002d9f90));goto dispatch;
L_002d9f8c:
 STEP(UINT32_C(0x002d9f8c)); /* 8e300014 lw s0,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002d9f90));goto dispatch;
L_002d9f90:
 STEP(UINT32_C(0x002d9f90)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d9f94));goto dispatch;
L_002d9f94:
 STEP(UINT32_C(0x002d9f94)); /* 0c0b5115 jal 002d4454 */
 set(m,31u,UINT64_C(0x002d9f9c));STEP(UINT32_C(0x002d9f98));set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d4454));goto dispatch;
L_002d9f98:
 STEP(UINT32_C(0x002d9f98)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d9f9c));goto dispatch;
L_002d9f9c:
 STEP(UINT32_C(0x002d9f9c)); /* 8e230000 lw v1,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d9fa0));goto dispatch;
L_002d9fa0:
 STEP(UINT32_C(0x002d9fa0)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9fa4));goto dispatch;
L_002d9fa4:
 STEP(UINT32_C(0x002d9fa4)); /* 00701821 addu v1,v1,s0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002d9fa8));goto dispatch;
L_002d9fa8:
 STEP(UINT32_C(0x002d9fa8)); /* 0c0b6578 jal 002d95e0 */
 set(m,31u,UINT64_C(0x002d9fb0));STEP(UINT32_C(0x002d9fac));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d95e0));goto dispatch;
L_002d9fac:
 STEP(UINT32_C(0x002d9fac)); /* ae230000 sw v1,0x0(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d9fb0));goto dispatch;
L_002d9fb0:
 STEP(UINT32_C(0x002d9fb0)); /* 5040001b beql v0,zero,002da020 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d9fb4));READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da020));}else target=sx(UINT32_C(0x002d9fb8));goto dispatch;
L_002d9fb4:
 STEP(UINT32_C(0x002d9fb4)); /* 8ec20008 lw v0,0x8(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9fb8));goto dispatch;
L_002d9fb8:
 STEP(UINT32_C(0x002d9fb8)); /* 1000007b beq zero,zero,002da1a8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9fbc));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(taken?UINT32_C(0x002da1a8):UINT32_C(0x002d9fc0));goto dispatch;}
L_002d9fbc:
 STEP(UINT32_C(0x002d9fbc)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d9fc0));goto dispatch;
L_002d9fc0:
 STEP(UINT32_C(0x002d9fc0)); /* 0250102b sltu v0,s2,s0 */
 set(m,2u,lo(m,18u)<lo(m,16u));target=sx(UINT32_C(0x002d9fc4));goto dispatch;
L_002d9fc4:
 STEP(UINT32_C(0x002d9fc4)); /* 5440000c bnel v0,zero,002d9ff8 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d9fc8));set(m,16u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d9ff8));}else target=sx(UINT32_C(0x002d9fcc));goto dispatch;
L_002d9fc8:
 STEP(UINT32_C(0x002d9fc8)); /* 0240802d daddu s0,s2,zero */
 set(m,16u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d9fcc));goto dispatch;
L_002d9fcc:
 STEP(UINT32_C(0x002d9fcc)); /* 8e220024 lw v0,0x24(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9fd0));goto dispatch;
L_002d9fd0:
 STEP(UINT32_C(0x002d9fd0)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d9fd4));goto dispatch;
L_002d9fd4:
 STEP(UINT32_C(0x002d9fd4)); /* 8e24001c lw a0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d9fd8));goto dispatch;
L_002d9fd8:
 STEP(UINT32_C(0x002d9fd8)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002d9fe0));STEP(UINT32_C(0x002d9fdc));set(m,5u,lo(m,19u)+lo(m,0u));goto dispatch;
L_002d9fdc:
 STEP(UINT32_C(0x002d9fdc)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d9fe0));goto dispatch;
L_002d9fe0:
 STEP(UINT32_C(0x002d9fe0)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d9fe4));goto dispatch;
L_002d9fe4:
 STEP(UINT32_C(0x002d9fe4)); /* 5e00000e bgtzl s0,zero,002da020 */
 if((int64_t)lo(m,16u)>0){STEP(UINT32_C(0x002d9fe8));READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da020));}else target=sx(UINT32_C(0x002d9fec));goto dispatch;
L_002d9fe8:
 STEP(UINT32_C(0x002d9fe8)); /* 8ec20008 lw v0,0x8(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9fec));goto dispatch;
L_002d9fec:
 STEP(UINT32_C(0x002d9fec)); /* 1000006e beq zero,zero,002da1a8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d9ff0));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(taken?UINT32_C(0x002da1a8):UINT32_C(0x002d9ff4));goto dispatch;}
L_002d9ff0:
 STEP(UINT32_C(0x002d9ff0)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d9ff4));goto dispatch;
L_002d9ff4:
 STEP(UINT32_C(0x002d9ff4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9ff8));goto dispatch;
L_002d9ff8:
 STEP(UINT32_C(0x002d9ff8)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002d9ffc));goto dispatch;
L_002d9ffc:
 STEP(UINT32_C(0x002d9ffc)); /* 0c0b5115 jal 002d4454 */
 set(m,31u,UINT64_C(0x002da004));STEP(UINT32_C(0x002da000));set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d4454));goto dispatch;
L_002da000:
 STEP(UINT32_C(0x002da000)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002da004));goto dispatch;
L_002da004:
 STEP(UINT32_C(0x002da004)); /* 8e230008 lw v1,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002da008));goto dispatch;
L_002da008:
 STEP(UINT32_C(0x002da008)); /* 8e220000 lw v0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da00c));goto dispatch;
L_002da00c:
 STEP(UINT32_C(0x002da00c)); /* 00701823 subu v1,v1,s0 */
 set(m,3u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da010));goto dispatch;
L_002da010:
 STEP(UINT32_C(0x002da010)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da014));goto dispatch;
L_002da014:
 STEP(UINT32_C(0x002da014)); /* ae230008 sw v1,0x8(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002da018));goto dispatch;
L_002da018:
 STEP(UINT32_C(0x002da018)); /* ae220000 sw v0,0x0(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002da01c));goto dispatch;
L_002da01c:
 STEP(UINT32_C(0x002da01c)); /* 8ec20008 lw v0,0x8(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da020));goto dispatch;
L_002da020:
 STEP(UINT32_C(0x002da020)); /* 02709821 addu s3,s3,s0 */
 set(m,19u,sx((uint32_t)lo(m,19u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da024));goto dispatch;
L_002da024:
 STEP(UINT32_C(0x002da024)); /* 02509023 subu s2,s2,s0 */
 set(m,18u,sx((uint32_t)lo(m,18u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da028));goto dispatch;
L_002da028:
 STEP(UINT32_C(0x002da028)); /* 00501023 subu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da02c));goto dispatch;
L_002da02c:
 STEP(UINT32_C(0x002da02c)); /* 1440ffb6 bne v0,zero,002d9f08 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002da030));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002d9f08):UINT32_C(0x002da034));goto dispatch;}
L_002da030:
 STEP(UINT32_C(0x002da030)); /* aec20008 sw v0,0x8(s6) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002da034));goto dispatch;
L_002da034:
 STEP(UINT32_C(0x002da034)); /* 1000005f beq zero,zero,002da1b4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da038));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002da1b4):UINT32_C(0x002da03c));goto dispatch;}
L_002da038:
 STEP(UINT32_C(0x002da038)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002da03c));goto dispatch;
L_002da03c:
 STEP(UINT32_C(0x002da03c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da040));goto dispatch;
L_002da040:
 STEP(UINT32_C(0x002da040)); /* 1640000a bne s2,zero,002da06c */
 {int taken=(lo(m,18u)!=lo(m,0u));STEP(UINT32_C(0x002da044));/* nop */target=sx(taken?UINT32_C(0x002da06c):UINT32_C(0x002da048));goto dispatch;}
L_002da044:
 STEP(UINT32_C(0x002da044)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da048));goto dispatch;
L_002da048:
 STEP(UINT32_C(0x002da048)); /* 0000b82d daddu s7,zero,zero */
 set(m,23u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002da04c));goto dispatch;
L_002da04c:
 STEP(UINT32_C(0x002da04c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da050));goto dispatch;
L_002da050:
 STEP(UINT32_C(0x002da050)); /* 8e920004 lw s2,0x4(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000004),&value32,4u);set(m,18u,sx(value32));target=sx(UINT32_C(0x002da054));goto dispatch;
L_002da054:
 STEP(UINT32_C(0x002da054)); /* 8e930000 lw s3,0x0(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);set(m,19u,sx(value32));target=sx(UINT32_C(0x002da058));goto dispatch;
L_002da058:
 STEP(UINT32_C(0x002da058)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da05c));goto dispatch;
L_002da05c:
 STEP(UINT32_C(0x002da05c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da060));goto dispatch;
L_002da060:
 STEP(UINT32_C(0x002da060)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da064));goto dispatch;
L_002da064:
 STEP(UINT32_C(0x002da064)); /* 1240fffa beq s2,zero,002da050 */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002da068));set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002da050):UINT32_C(0x002da06c));goto dispatch;}
L_002da068:
 STEP(UINT32_C(0x002da068)); /* 26940008 addiu s4,s4,8 */
 set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002da06c));goto dispatch;
L_002da06c:
 STEP(UINT32_C(0x002da06c)); /* 56e0000d bnel s7,zero,002da0a4 */
 if(lo(m,23u)!=lo(m,0u)){STEP(UINT32_C(0x002da070));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002da0a4));}else target=sx(UINT32_C(0x002da074));goto dispatch;
L_002da070:
 STEP(UINT32_C(0x002da070)); /* 8e280000 lw t0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002da074));goto dispatch;
L_002da074:
 STEP(UINT32_C(0x002da074)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002da078));goto dispatch;
L_002da078:
 STEP(UINT32_C(0x002da078)); /* 2405000a addiu a1,zero,10 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002da07c));goto dispatch;
L_002da07c:
 STEP(UINT32_C(0x002da07c)); /* 0c0b693b jal 002da4ec */
 set(m,31u,UINT64_C(0x002da084));STEP(UINT32_C(0x002da080));set(m,6u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002da4ec));goto dispatch;
L_002da080:
 STEP(UINT32_C(0x002da080)); /* 0240302d daddu a2,s2,zero */
 set(m,6u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002da084));goto dispatch;
L_002da084:
 STEP(UINT32_C(0x002da084)); /* 10400004 beq v0,zero,002da098 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002da088));set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,19u)));target=sx(taken?UINT32_C(0x002da098):UINT32_C(0x002da08c));goto dispatch;}
L_002da088:
 STEP(UINT32_C(0x002da088)); /* 00531023 subu v0,v0,s3 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,19u)));target=sx(UINT32_C(0x002da08c));goto dispatch;
L_002da08c:
 STEP(UINT32_C(0x002da08c)); /* 10000003 beq zero,zero,002da09c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da090));set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002da09c):UINT32_C(0x002da094));goto dispatch;}
L_002da090:
 STEP(UINT32_C(0x002da090)); /* 24550001 addiu s5,v0,1 */
 set(m,21u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002da094));goto dispatch;
L_002da094:
 STEP(UINT32_C(0x002da094)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da098));goto dispatch;
L_002da098:
 STEP(UINT32_C(0x002da098)); /* 26550001 addiu s5,s2,1 */
 set(m,21u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002da09c));goto dispatch;
L_002da09c:
 STEP(UINT32_C(0x002da09c)); /* 24170001 addiu s7,zero,1 */
 set(m,23u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002da0a0));goto dispatch;
L_002da0a0:
 STEP(UINT32_C(0x002da0a0)); /* 8e280000 lw t0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002da0a4));goto dispatch;
L_002da0a4:
 STEP(UINT32_C(0x002da0a4)); /* 0255102b sltu v0,s2,s5 */
 set(m,2u,lo(m,18u)<lo(m,21u));target=sx(UINT32_C(0x002da0a8));goto dispatch;
L_002da0a8:
 STEP(UINT32_C(0x002da0a8)); /* 8e230010 lw v1,0x10(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002da0ac));goto dispatch;
L_002da0ac:
 STEP(UINT32_C(0x002da0ac)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002da0b0));goto dispatch;
L_002da0b0:
 STEP(UINT32_C(0x002da0b0)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002da0b4));goto dispatch;
L_002da0b4:
 STEP(UINT32_C(0x002da0b4)); /* 02a2280a movz a1,s5,v0 */
 if(lo(m,2u)==0u)set(m,5u,lo(m,21u));target=sx(UINT32_C(0x002da0b8));goto dispatch;
L_002da0b8:
 STEP(UINT32_C(0x002da0b8)); /* 8e270014 lw a3,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002da0bc));goto dispatch;
L_002da0bc:
 STEP(UINT32_C(0x002da0bc)); /* 0068182b sltu v1,v1,t0 */
 set(m,3u,lo(m,3u)<lo(m,8u));target=sx(UINT32_C(0x002da0c0));goto dispatch;
L_002da0c0:
 STEP(UINT32_C(0x002da0c0)); /* 10600011 beq v1,zero,002da108 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002da0c4));set(m,16u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,7u)));target=sx(taken?UINT32_C(0x002da108):UINT32_C(0x002da0c8));goto dispatch;}
L_002da0c4:
 STEP(UINT32_C(0x002da0c4)); /* 00878021 addu s0,a0,a3 */
 set(m,16u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x002da0c8));goto dispatch;
L_002da0c8:
 STEP(UINT32_C(0x002da0c8)); /* 0205102a slt v0,s0,a1 */
 set(m,2u,((int64_t)lo(m,16u)<(int64_t)lo(m,5u)));target=sx(UINT32_C(0x002da0cc));goto dispatch;
L_002da0cc:
 STEP(UINT32_C(0x002da0cc)); /* 5040000f beql v0,zero,002da10c */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002da0d0));set(m,16u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002da10c));}else target=sx(UINT32_C(0x002da0d4));goto dispatch;
L_002da0d0:
 STEP(UINT32_C(0x002da0d0)); /* 00e0802d daddu s0,a3,zero */
 set(m,16u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002da0d4));goto dispatch;
L_002da0d4:
 STEP(UINT32_C(0x002da0d4)); /* 0100202d daddu a0,t0,zero */
 set(m,4u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002da0d8));goto dispatch;
L_002da0d8:
 STEP(UINT32_C(0x002da0d8)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002da0dc));goto dispatch;
L_002da0dc:
 STEP(UINT32_C(0x002da0dc)); /* 0c0b5115 jal 002d4454 */
 set(m,31u,UINT64_C(0x002da0e4));STEP(UINT32_C(0x002da0e0));set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d4454));goto dispatch;
L_002da0e0:
 STEP(UINT32_C(0x002da0e0)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002da0e4));goto dispatch;
L_002da0e4:
 STEP(UINT32_C(0x002da0e4)); /* 8e230000 lw v1,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002da0e8));goto dispatch;
L_002da0e8:
 STEP(UINT32_C(0x002da0e8)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002da0ec));goto dispatch;
L_002da0ec:
 STEP(UINT32_C(0x002da0ec)); /* 00701821 addu v1,v1,s0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da0f0));goto dispatch;
L_002da0f0:
 STEP(UINT32_C(0x002da0f0)); /* 0c0b6578 jal 002d95e0 */
 set(m,31u,UINT64_C(0x002da0f8));STEP(UINT32_C(0x002da0f4));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d95e0));goto dispatch;
L_002da0f4:
 STEP(UINT32_C(0x002da0f4)); /* ae230000 sw v1,0x0(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002da0f8));goto dispatch;
L_002da0f8:
 STEP(UINT32_C(0x002da0f8)); /* 1040001c beq v0,zero,002da16c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002da0fc));set(m,21u,sx((uint32_t)lo(m,21u)-(uint32_t)lo(m,16u)));target=sx(taken?UINT32_C(0x002da16c):UINT32_C(0x002da100));goto dispatch;}
L_002da0fc:
 STEP(UINT32_C(0x002da0fc)); /* 02b0a823 subu s5,s5,s0 */
 set(m,21u,sx((uint32_t)lo(m,21u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da100));goto dispatch;
L_002da100:
 STEP(UINT32_C(0x002da100)); /* 10000029 beq zero,zero,002da1a8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da104));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(taken?UINT32_C(0x002da1a8):UINT32_C(0x002da108));goto dispatch;}
L_002da104:
 STEP(UINT32_C(0x002da104)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002da108));goto dispatch;
L_002da108:
 STEP(UINT32_C(0x002da108)); /* 00e0802d daddu s0,a3,zero */
 set(m,16u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002da10c));goto dispatch;
L_002da10c:
 STEP(UINT32_C(0x002da10c)); /* 00b0102a slt v0,a1,s0 */
 set(m,2u,((int64_t)lo(m,5u)<(int64_t)lo(m,16u)));target=sx(UINT32_C(0x002da110));goto dispatch;
L_002da110:
 STEP(UINT32_C(0x002da110)); /* 5440000b bnel v0,zero,002da140 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002da114));set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002da140));}else target=sx(UINT32_C(0x002da118));goto dispatch;
L_002da114:
 STEP(UINT32_C(0x002da114)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002da118));goto dispatch;
L_002da118:
 STEP(UINT32_C(0x002da118)); /* 8e220024 lw v0,0x24(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da11c));goto dispatch;
L_002da11c:
 STEP(UINT32_C(0x002da11c)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002da120));goto dispatch;
L_002da120:
 STEP(UINT32_C(0x002da120)); /* 8e24001c lw a0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002da124));goto dispatch;
L_002da124:
 STEP(UINT32_C(0x002da124)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002da12c));STEP(UINT32_C(0x002da128));set(m,5u,lo(m,19u)+lo(m,0u));goto dispatch;
L_002da128:
 STEP(UINT32_C(0x002da128)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002da12c));goto dispatch;
L_002da12c:
 STEP(UINT32_C(0x002da12c)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002da130));goto dispatch;
L_002da130:
 STEP(UINT32_C(0x002da130)); /* 1e00000e bgtz s0,zero,002da16c */
 {int taken=((int64_t)lo(m,16u)>0);STEP(UINT32_C(0x002da134));set(m,21u,sx((uint32_t)lo(m,21u)-(uint32_t)lo(m,16u)));target=sx(taken?UINT32_C(0x002da16c):UINT32_C(0x002da138));goto dispatch;}
L_002da134:
 STEP(UINT32_C(0x002da134)); /* 02b0a823 subu s5,s5,s0 */
 set(m,21u,sx((uint32_t)lo(m,21u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da138));goto dispatch;
L_002da138:
 STEP(UINT32_C(0x002da138)); /* 1000001b beq zero,zero,002da1a8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da13c));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(taken?UINT32_C(0x002da1a8):UINT32_C(0x002da140));goto dispatch;}
L_002da13c:
 STEP(UINT32_C(0x002da13c)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002da140));goto dispatch;
L_002da140:
 STEP(UINT32_C(0x002da140)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002da144));goto dispatch;
L_002da144:
 STEP(UINT32_C(0x002da144)); /* 0100202d daddu a0,t0,zero */
 set(m,4u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002da148));goto dispatch;
L_002da148:
 STEP(UINT32_C(0x002da148)); /* 0c0b5115 jal 002d4454 */
 set(m,31u,UINT64_C(0x002da150));STEP(UINT32_C(0x002da14c));set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d4454));goto dispatch;
L_002da14c:
 STEP(UINT32_C(0x002da14c)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002da150));goto dispatch;
L_002da150:
 STEP(UINT32_C(0x002da150)); /* 8e230008 lw v1,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002da154));goto dispatch;
L_002da154:
 STEP(UINT32_C(0x002da154)); /* 8e220000 lw v0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da158));goto dispatch;
L_002da158:
 STEP(UINT32_C(0x002da158)); /* 00701823 subu v1,v1,s0 */
 set(m,3u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da15c));goto dispatch;
L_002da15c:
 STEP(UINT32_C(0x002da15c)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da160));goto dispatch;
L_002da160:
 STEP(UINT32_C(0x002da160)); /* ae230008 sw v1,0x8(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002da164));goto dispatch;
L_002da164:
 STEP(UINT32_C(0x002da164)); /* ae220000 sw v0,0x0(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002da168));goto dispatch;
L_002da168:
 STEP(UINT32_C(0x002da168)); /* 02b0a823 subu s5,s5,s0 */
 set(m,21u,sx((uint32_t)lo(m,21u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da16c));goto dispatch;
L_002da16c:
 STEP(UINT32_C(0x002da16c)); /* 56a00007 bnel s5,zero,002da18c */
 if(lo(m,21u)!=lo(m,0u)){STEP(UINT32_C(0x002da170));READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da18c));}else target=sx(UINT32_C(0x002da174));goto dispatch;
L_002da170:
 STEP(UINT32_C(0x002da170)); /* 8ec20008 lw v0,0x8(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da174));goto dispatch;
L_002da174:
 STEP(UINT32_C(0x002da174)); /* 0c0b6578 jal 002d95e0 */
 set(m,31u,UINT64_C(0x002da17c));STEP(UINT32_C(0x002da178));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d95e0));goto dispatch;
L_002da178:
 STEP(UINT32_C(0x002da178)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002da17c));goto dispatch;
L_002da17c:
 STEP(UINT32_C(0x002da17c)); /* 5440000a bnel v0,zero,002da1a8 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002da180));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002da1a8));}else target=sx(UINT32_C(0x002da184));goto dispatch;
L_002da180:
 STEP(UINT32_C(0x002da180)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002da184));goto dispatch;
L_002da184:
 STEP(UINT32_C(0x002da184)); /* 0000b82d daddu s7,zero,zero */
 set(m,23u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002da188));goto dispatch;
L_002da188:
 STEP(UINT32_C(0x002da188)); /* 8ec20008 lw v0,0x8(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da18c));goto dispatch;
L_002da18c:
 STEP(UINT32_C(0x002da18c)); /* 02709821 addu s3,s3,s0 */
 set(m,19u,sx((uint32_t)lo(m,19u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da190));goto dispatch;
L_002da190:
 STEP(UINT32_C(0x002da190)); /* 02509023 subu s2,s2,s0 */
 set(m,18u,sx((uint32_t)lo(m,18u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da194));goto dispatch;
L_002da194:
 STEP(UINT32_C(0x002da194)); /* 00501023 subu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002da198));goto dispatch;
L_002da198:
 STEP(UINT32_C(0x002da198)); /* 1440ffa9 bne v0,zero,002da040 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002da19c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002da040):UINT32_C(0x002da1a0));goto dispatch;}
L_002da19c:
 STEP(UINT32_C(0x002da19c)); /* aec20008 sw v0,0x8(s6) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002da1a0));goto dispatch;
L_002da1a0:
 STEP(UINT32_C(0x002da1a0)); /* 10000004 beq zero,zero,002da1b4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da1a4));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002da1b4):UINT32_C(0x002da1a8));goto dispatch;}
L_002da1a4:
 STEP(UINT32_C(0x002da1a4)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002da1a8));goto dispatch;
L_002da1a8:
 STEP(UINT32_C(0x002da1a8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002da1ac));goto dispatch;
L_002da1ac:
 STEP(UINT32_C(0x002da1ac)); /* 34630040 ori v1,v1,0x40 */
 set(m,3u,lo(m,3u) | UINT64_C(0x40));target=sx(UINT32_C(0x002da1b0));goto dispatch;
L_002da1b0:
 STEP(UINT32_C(0x002da1b0)); /* a623000c sh v1,0xc(s1) */
 value16=(uint16_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002da1b4));goto dispatch;
L_002da1b4:
 STEP(UINT32_C(0x002da1b4)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002da1b8));goto dispatch;
L_002da1b8:
 STEP(UINT32_C(0x002da1b8)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002da1bc));goto dispatch;
L_002da1bc:
 STEP(UINT32_C(0x002da1bc)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002da1c0));goto dispatch;
L_002da1c0:
 STEP(UINT32_C(0x002da1c0)); /* dfb30018 ld s3,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002da1c4));goto dispatch;
L_002da1c4:
 STEP(UINT32_C(0x002da1c4)); /* dfb40020 ld s4,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002da1c8));goto dispatch;
L_002da1c8:
 STEP(UINT32_C(0x002da1c8)); /* dfb50028 ld s5,0x28(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002da1cc));goto dispatch;
L_002da1cc:
 STEP(UINT32_C(0x002da1cc)); /* dfb60030 ld s6,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002da1d0));goto dispatch;
L_002da1d0:
 STEP(UINT32_C(0x002da1d0)); /* dfb70038 ld s7,0x38(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000038),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002da1d4));goto dispatch;
L_002da1d4:
 STEP(UINT32_C(0x002da1d4)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002da1d8));goto dispatch;
L_002da1d8:
 STEP(UINT32_C(0x002da1d8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002da1dc));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_002da1dc:
 STEP(UINT32_C(0x002da1dc)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x002da1e0));goto dispatch;
L_002d4454:
 STEP(UINT32_C(0x002d4454)); /* 0080402d daddu t0,a0,zero */
 set(m,8u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d4458));goto dispatch;
L_002d4458:
 STEP(UINT32_C(0x002d4458)); /* 00a8102b sltu v0,a1,t0 */
 set(m,2u,lo(m,5u)<lo(m,8u));target=sx(UINT32_C(0x002d445c));goto dispatch;
L_002d445c:
 STEP(UINT32_C(0x002d445c)); /* 10400013 beq v0,zero,002d44ac */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d4460));set(m,3u,lo(m,8u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d44ac):UINT32_C(0x002d4464));goto dispatch;}
L_002d4460:
 STEP(UINT32_C(0x002d4460)); /* 0100182d daddu v1,t0,zero */
 set(m,3u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d4464));goto dispatch;
L_002d4464:
 STEP(UINT32_C(0x002d4464)); /* 00a63821 addu a3,a1,a2 */
 set(m,7u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d4468));goto dispatch;
L_002d4468:
 STEP(UINT32_C(0x002d4468)); /* 0107102b sltu v0,t0,a3 */
 set(m,2u,lo(m,8u)<lo(m,7u));target=sx(UINT32_C(0x002d446c));goto dispatch;
L_002d446c:
 STEP(UINT32_C(0x002d446c)); /* 1040000f beq v0,zero,002d44ac */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d4470));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002d44ac):UINT32_C(0x002d4474));goto dispatch;}
L_002d4470:
 STEP(UINT32_C(0x002d4470)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4474));goto dispatch;
L_002d4474:
 STEP(UINT32_C(0x002d4474)); /* 01061821 addu v1,t0,a2 */
 set(m,3u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002d4478));goto dispatch;
L_002d4478:
 STEP(UINT32_C(0x002d4478)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d447c));goto dispatch;
L_002d447c:
 STEP(UINT32_C(0x002d447c)); /* 10c20034 beq a2,v0,002d4550 */
 {int taken=(lo(m,6u)==lo(m,2u));STEP(UINT32_C(0x002d4480));set(m,5u,lo(m,7u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d4550):UINT32_C(0x002d4484));goto dispatch;}
L_002d4480:
 STEP(UINT32_C(0x002d4480)); /* 00e0282d daddu a1,a3,zero */
 set(m,5u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d4484));goto dispatch;
L_002d4484:
 STEP(UINT32_C(0x002d4484)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d4488));goto dispatch;
L_002d4488:
 STEP(UINT32_C(0x002d4488)); /* 24a5ffff addiu a1,a1,-1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d448c));goto dispatch;
L_002d448c:
 STEP(UINT32_C(0x002d448c)); /* 2463ffff addiu v1,v1,-1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4490));goto dispatch;
L_002d4490:
 STEP(UINT32_C(0x002d4490)); /* 90a20000 lbu v0,0x0(a1) */
 {uint8_t byte;READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002d4494));goto dispatch;
L_002d4494:
 STEP(UINT32_C(0x002d4494)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4498));goto dispatch;
L_002d4498:
 STEP(UINT32_C(0x002d4498)); /* a0620000 sb v0,0x0(v1) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d449c));goto dispatch;
L_002d449c:
 STEP(UINT32_C(0x002d449c)); /* 14c4fffa bne a2,a0,002d4488 */
 {int taken=(lo(m,6u)!=lo(m,4u));STEP(UINT32_C(0x002d44a0));/* nop */target=sx(taken?UINT32_C(0x002d4488):UINT32_C(0x002d44a4));goto dispatch;}
L_002d44a0:
 STEP(UINT32_C(0x002d44a0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d44a4));goto dispatch;
L_002d44a4:
 STEP(UINT32_C(0x002d44a4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d44a8));set(m,2u,lo(m,8u)+lo(m,0u));goto dispatch;
L_002d44a8:
 STEP(UINT32_C(0x002d44a8)); /* 0100102d daddu v0,t0,zero */
 set(m,2u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d44ac));goto dispatch;
L_002d44ac:
 STEP(UINT32_C(0x002d44ac)); /* 2cc20020 sltiu v0,a2,32 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x20)));target=sx(UINT32_C(0x002d44b0));goto dispatch;
L_002d44b0:
 STEP(UINT32_C(0x002d44b0)); /* 5440001d bnel v0,zero,002d4528 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d44b4));set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4528));}else target=sx(UINT32_C(0x002d44b8));goto dispatch;
L_002d44b4:
 STEP(UINT32_C(0x002d44b4)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d44b8));goto dispatch;
L_002d44b8:
 STEP(UINT32_C(0x002d44b8)); /* 00a31025 or v0,a1,v1 */
 set(m,2u,lo(m,5u)|lo(m,3u));target=sx(UINT32_C(0x002d44bc));goto dispatch;
L_002d44bc:
 STEP(UINT32_C(0x002d44bc)); /* 3042000f andi v0,v0,0xf */
 set(m,2u,lo(m,2u) & UINT64_C(0xf));target=sx(UINT32_C(0x002d44c0));goto dispatch;
L_002d44c0:
 STEP(UINT32_C(0x002d44c0)); /* 54400019 bnel v0,zero,002d4528 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d44c4));set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4528));}else target=sx(UINT32_C(0x002d44c8));goto dispatch;
L_002d44c4:
 STEP(UINT32_C(0x002d44c4)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d44c8));goto dispatch;
L_002d44c8:
 STEP(UINT32_C(0x002d44c8)); /* 0060382d daddu a3,v1,zero */
 set(m,7u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d44cc));goto dispatch;
L_002d44cc:
 STEP(UINT32_C(0x002d44cc)); /* 78a30000 lq v1,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x002d44d0));goto dispatch;
L_002d44d0:
 STEP(UINT32_C(0x002d44d0)); /* 24c6ffe0 addiu a2,a2,-32 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d44d4));goto dispatch;
L_002d44d4:
 STEP(UINT32_C(0x002d44d4)); /* 24a50010 addiu a1,a1,16 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d44d8));goto dispatch;
L_002d44d8:
 STEP(UINT32_C(0x002d44d8)); /* 2cc40020 sltiu a0,a2,32 */
 set(m,4u,(lo(m,6u)<UINT64_C(0x20)));target=sx(UINT32_C(0x002d44dc));goto dispatch;
L_002d44dc:
 STEP(UINT32_C(0x002d44dc)); /* 7ce30000 sq v1,0x0(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),m->gpr[3],16u);target=sx(UINT32_C(0x002d44e0));goto dispatch;
L_002d44e0:
 STEP(UINT32_C(0x002d44e0)); /* 24e70010 addiu a3,a3,16 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d44e4));goto dispatch;
L_002d44e4:
 STEP(UINT32_C(0x002d44e4)); /* 78a20000 lq v0,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x002d44e8));goto dispatch;
L_002d44e8:
 STEP(UINT32_C(0x002d44e8)); /* 24a50010 addiu a1,a1,16 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d44ec));goto dispatch;
L_002d44ec:
 STEP(UINT32_C(0x002d44ec)); /* 7ce20000 sq v0,0x0(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),m->gpr[2],16u);target=sx(UINT32_C(0x002d44f0));goto dispatch;
L_002d44f0:
 STEP(UINT32_C(0x002d44f0)); /* 1080fff6 beq a0,zero,002d44cc */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x002d44f4));set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x002d44cc):UINT32_C(0x002d44f8));goto dispatch;}
L_002d44f4:
 STEP(UINT32_C(0x002d44f4)); /* 24e70010 addiu a3,a3,16 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d44f8));goto dispatch;
L_002d44f8:
 STEP(UINT32_C(0x002d44f8)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d44fc));goto dispatch;
L_002d44fc:
 STEP(UINT32_C(0x002d44fc)); /* 14400009 bne v0,zero,002d4524 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d4500));set(m,3u,lo(m,7u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d4524):UINT32_C(0x002d4504));goto dispatch;}
L_002d4500:
 STEP(UINT32_C(0x002d4500)); /* 00e0182d daddu v1,a3,zero */
 set(m,3u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d4504));goto dispatch;
L_002d4504:
 STEP(UINT32_C(0x002d4504)); /* dca30000 ld v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d4508));goto dispatch;
L_002d4508:
 STEP(UINT32_C(0x002d4508)); /* 24c6fff8 addiu a2,a2,-8 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d450c));goto dispatch;
L_002d450c:
 STEP(UINT32_C(0x002d450c)); /* 24a50008 addiu a1,a1,8 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d4510));goto dispatch;
L_002d4510:
 STEP(UINT32_C(0x002d4510)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d4514));goto dispatch;
L_002d4514:
 STEP(UINT32_C(0x002d4514)); /* fce30000 sd v1,0x0(a3) */
 value64=lo(m,3u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d4518));goto dispatch;
L_002d4518:
 STEP(UINT32_C(0x002d4518)); /* 1040fffa beq v0,zero,002d4504 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d451c));set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002d4504):UINT32_C(0x002d4520));goto dispatch;}
L_002d451c:
 STEP(UINT32_C(0x002d451c)); /* 24e70008 addiu a3,a3,8 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d4520));goto dispatch;
L_002d4520:
 STEP(UINT32_C(0x002d4520)); /* 00e0182d daddu v1,a3,zero */
 set(m,3u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d4524));goto dispatch;
L_002d4524:
 STEP(UINT32_C(0x002d4524)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4528));goto dispatch;
L_002d4528:
 STEP(UINT32_C(0x002d4528)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d452c));goto dispatch;
L_002d452c:
 STEP(UINT32_C(0x002d452c)); /* 10c20008 beq a2,v0,002d4550 */
 {int taken=(lo(m,6u)==lo(m,2u));STEP(UINT32_C(0x002d4530));set(m,4u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d4550):UINT32_C(0x002d4534));goto dispatch;}
L_002d4530:
 STEP(UINT32_C(0x002d4530)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d4534));goto dispatch;
L_002d4534:
 STEP(UINT32_C(0x002d4534)); /* 90a20000 lbu v0,0x0(a1) */
 {uint8_t byte;READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002d4538));goto dispatch;
L_002d4538:
 STEP(UINT32_C(0x002d4538)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d453c));goto dispatch;
L_002d453c:
 STEP(UINT32_C(0x002d453c)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4540));goto dispatch;
L_002d4540:
 STEP(UINT32_C(0x002d4540)); /* a0620000 sb v0,0x0(v1) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d4544));goto dispatch;
L_002d4544:
 STEP(UINT32_C(0x002d4544)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4548));goto dispatch;
L_002d4548:
 STEP(UINT32_C(0x002d4548)); /* 14c4fffa bne a2,a0,002d4534 */
 {int taken=(lo(m,6u)!=lo(m,4u));STEP(UINT32_C(0x002d454c));/* nop */target=sx(taken?UINT32_C(0x002d4534):UINT32_C(0x002d4550));goto dispatch;}
L_002d454c:
 STEP(UINT32_C(0x002d454c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4550));goto dispatch;
L_002d4550:
 STEP(UINT32_C(0x002d4550)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d4554));set(m,2u,lo(m,8u)+lo(m,0u));goto dispatch;
L_002d4554:
 STEP(UINT32_C(0x002d4554)); /* 0100102d daddu v0,t0,zero */
 set(m,2u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d4558));goto dispatch;
L_002d8038:
 STEP(UINT32_C(0x002d8038)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d803c));goto dispatch;
L_002d803c:
 STEP(UINT32_C(0x002d803c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d8040));goto dispatch;
L_002d8040:
 STEP(UINT32_C(0x002d8040)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d8044));goto dispatch;
L_002d8044:
 STEP(UINT32_C(0x002d8044)); /* ffbf0008 sd ra,0x8(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d8048));goto dispatch;
L_002d8048:
 STEP(UINT32_C(0x002d8048)); /* 8e030054 lw v1,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d804c));goto dispatch;
L_002d804c:
 STEP(UINT32_C(0x002d804c)); /* 54600006 bnel v1,zero,002d8068 */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x002d8050));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000038),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d8068));}else target=sx(UINT32_C(0x002d8054));goto dispatch;
L_002d8050:
 STEP(UINT32_C(0x002d8050)); /* 8c620038 lw v0,0x38(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000038),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d8054));goto dispatch;
L_002d8054:
 STEP(UINT32_C(0x002d8054)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d8058));goto dispatch;
L_002d8058:
 STEP(UINT32_C(0x002d8058)); /* 8c43be28 lw v1,-0x41d8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbe28),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d805c));goto dispatch;
L_002d805c:
 STEP(UINT32_C(0x002d805c)); /* ae030054 sw v1,0x54(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);target=sx(UINT32_C(0x002d8060));goto dispatch;
L_002d8060:
 STEP(UINT32_C(0x002d8060)); /* 8c620038 lw v0,0x38(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000038),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d8064));goto dispatch;
L_002d8064:
 STEP(UINT32_C(0x002d8064)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d8068));goto dispatch;
L_002d8068:
 STEP(UINT32_C(0x002d8068)); /* 54400004 bnel v0,zero,002d807c */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d806c));READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,4u,value16);target=sx(UINT32_C(0x002d807c));}else target=sx(UINT32_C(0x002d8070));goto dispatch;
L_002d806c:
 STEP(UINT32_C(0x002d806c)); /* 9604000c lhu a0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,4u,value16);target=sx(UINT32_C(0x002d8070));goto dispatch;
L_002d8070:
 STEP(UINT32_C(0x002d8070)); /* 0c0b6642 jal 002d9908 */
 set(m,31u,UINT64_C(0x002d8078));STEP(UINT32_C(0x002d8074));set(m,4u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d9908));goto dispatch;
L_002d8074:
 STEP(UINT32_C(0x002d8074)); /* 0060202d daddu a0,v1,zero */
 set(m,4u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d8078));goto dispatch;
L_002d8078:
 STEP(UINT32_C(0x002d8078)); /* 9604000c lhu a0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,4u,value16);target=sx(UINT32_C(0x002d807c));goto dispatch;
L_002d807c:
 STEP(UINT32_C(0x002d807c)); /* 30820008 andi v0,a0,0x8 */
 set(m,2u,lo(m,4u) & UINT64_C(0x8));target=sx(UINT32_C(0x002d8080));goto dispatch;
L_002d8080:
 STEP(UINT32_C(0x002d8080)); /* 54400019 bnel v0,zero,002d80e8 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d8084));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d80e8));}else target=sx(UINT32_C(0x002d8088));goto dispatch;
L_002d8084:
 STEP(UINT32_C(0x002d8084)); /* 8e050010 lw a1,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d8088));goto dispatch;
L_002d8088:
 STEP(UINT32_C(0x002d8088)); /* 30830010 andi v1,a0,0x10 */
 set(m,3u,lo(m,4u) & UINT64_C(0x10));target=sx(UINT32_C(0x002d808c));goto dispatch;
L_002d808c:
 STEP(UINT32_C(0x002d808c)); /* 10600029 beq v1,zero,002d8134 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002d8090));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002d8134):UINT32_C(0x002d8094));goto dispatch;}
L_002d8090:
 STEP(UINT32_C(0x002d8090)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d8094));goto dispatch;
L_002d8094:
 STEP(UINT32_C(0x002d8094)); /* 30820004 andi v0,a0,0x4 */
 set(m,2u,lo(m,4u) & UINT64_C(0x4));target=sx(UINT32_C(0x002d8098));goto dispatch;
L_002d8098:
 STEP(UINT32_C(0x002d8098)); /* 50400011 beql v0,zero,002d80e0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d809c));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d80e0));}else target=sx(UINT32_C(0x002d80a0));goto dispatch;
L_002d809c:
 STEP(UINT32_C(0x002d809c)); /* 8e050010 lw a1,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d80a0));goto dispatch;
L_002d80a0:
 STEP(UINT32_C(0x002d80a0)); /* 8e050030 lw a1,0x30(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d80a4));goto dispatch;
L_002d80a4:
 STEP(UINT32_C(0x002d80a4)); /* 10a00007 beq a1,zero,002d80c4 */
 {int taken=(lo(m,5u)==lo(m,0u));STEP(UINT32_C(0x002d80a8));set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000040)));target=sx(taken?UINT32_C(0x002d80c4):UINT32_C(0x002d80ac));goto dispatch;}
L_002d80a8:
 STEP(UINT32_C(0x002d80a8)); /* 26020040 addiu v0,s0,64 */
 set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002d80ac));goto dispatch;
L_002d80ac:
 STEP(UINT32_C(0x002d80ac)); /* 50a20005 beql a1,v0,002d80c4 */
 if(lo(m,5u)==lo(m,2u)){STEP(UINT32_C(0x002d80b0));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002d80c4));}else target=sx(UINT32_C(0x002d80b4));goto dispatch;
L_002d80b0:
 STEP(UINT32_C(0x002d80b0)); /* ae000030 sw zero,0x30(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002d80b4));goto dispatch;
L_002d80b4:
 STEP(UINT32_C(0x002d80b4)); /* 0c0b6666 jal 002d9998 */
 set(m,31u,UINT64_C(0x002d80bc));STEP(UINT32_C(0x002d80b8));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d9998));goto dispatch;
L_002d80b8:
 STEP(UINT32_C(0x002d80b8)); /* 8e040054 lw a0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d80bc));goto dispatch;
L_002d80bc:
 STEP(UINT32_C(0x002d80bc)); /* 9604000c lhu a0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,4u,value16);target=sx(UINT32_C(0x002d80c0));goto dispatch;
L_002d80c0:
 STEP(UINT32_C(0x002d80c0)); /* ae000030 sw zero,0x30(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002d80c4));goto dispatch;
L_002d80c4:
 STEP(UINT32_C(0x002d80c4)); /* 2402ffdb addiu v0,zero,-37 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffdb)));target=sx(UINT32_C(0x002d80c8));goto dispatch;
L_002d80c8:
 STEP(UINT32_C(0x002d80c8)); /* 8e050010 lw a1,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002d80cc));goto dispatch;
L_002d80cc:
 STEP(UINT32_C(0x002d80cc)); /* 00821024 and v0,a0,v0 */
 set(m,2u,lo(m,4u)&lo(m,2u));target=sx(UINT32_C(0x002d80d0));goto dispatch;
L_002d80d0:
 STEP(UINT32_C(0x002d80d0)); /* ae000004 sw zero,0x4(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d80d4));goto dispatch;
L_002d80d4:
 STEP(UINT32_C(0x002d80d4)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002d80d8));goto dispatch;
L_002d80d8:
 STEP(UINT32_C(0x002d80d8)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d80dc));goto dispatch;
L_002d80dc:
 STEP(UINT32_C(0x002d80dc)); /* ae050000 sw a1,0x0(s0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d80e0));goto dispatch;
L_002d80e0:
 STEP(UINT32_C(0x002d80e0)); /* 34820008 ori v0,a0,0x8 */
 set(m,2u,lo(m,4u) | UINT64_C(0x8));target=sx(UINT32_C(0x002d80e4));goto dispatch;
L_002d80e4:
 STEP(UINT32_C(0x002d80e4)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002d80e8));goto dispatch;
L_002d80e8:
 STEP(UINT32_C(0x002d80e8)); /* 54a00004 bnel a1,zero,002d80fc */
 if(lo(m,5u)!=lo(m,0u)){STEP(UINT32_C(0x002d80ec));READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d80fc));}else target=sx(UINT32_C(0x002d80f0));goto dispatch;
L_002d80ec:
 STEP(UINT32_C(0x002d80ec)); /* 9603000c lhu v1,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d80f0));goto dispatch;
L_002d80f0:
 STEP(UINT32_C(0x002d80f0)); /* 0c0b68d8 jal 002da360 */
 set(m,31u,UINT64_C(0x002d80f8));STEP(UINT32_C(0x002d80f4));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002da360));goto dispatch;
L_002d80f4:
 STEP(UINT32_C(0x002d80f4)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d80f8));goto dispatch;
L_002d80f8:
 STEP(UINT32_C(0x002d80f8)); /* 9603000c lhu v1,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d80fc));goto dispatch;
L_002d80fc:
 STEP(UINT32_C(0x002d80fc)); /* 30620001 andi v0,v1,0x1 */
 set(m,2u,lo(m,3u) & UINT64_C(0x1));target=sx(UINT32_C(0x002d8100));goto dispatch;
L_002d8100:
 STEP(UINT32_C(0x002d8100)); /* 10400007 beq v0,zero,002d8120 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d8104));set(m,2u,lo(m,3u) & UINT64_C(0x2));target=sx(taken?UINT32_C(0x002d8120):UINT32_C(0x002d8108));goto dispatch;}
L_002d8104:
 STEP(UINT32_C(0x002d8104)); /* 30620002 andi v0,v1,0x2 */
 set(m,2u,lo(m,3u) & UINT64_C(0x2));target=sx(UINT32_C(0x002d8108));goto dispatch;
L_002d8108:
 STEP(UINT32_C(0x002d8108)); /* 8e020014 lw v0,0x14(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d810c));goto dispatch;
L_002d810c:
 STEP(UINT32_C(0x002d810c)); /* ae000008 sw zero,0x8(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d8110));goto dispatch;
L_002d8110:
 STEP(UINT32_C(0x002d8110)); /* 00021023 subu v0,zero,v0 */
 set(m,2u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d8114));goto dispatch;
L_002d8114:
 STEP(UINT32_C(0x002d8114)); /* 10000006 beq zero,zero,002d8130 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d8118));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(taken?UINT32_C(0x002d8130):UINT32_C(0x002d811c));goto dispatch;}
L_002d8118:
 STEP(UINT32_C(0x002d8118)); /* ae020018 sw v0,0x18(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d811c));goto dispatch;
L_002d811c:
 STEP(UINT32_C(0x002d811c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d8120));goto dispatch;
L_002d8120:
 STEP(UINT32_C(0x002d8120)); /* 14400002 bne v0,zero,002d812c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d8124));set(m,3u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d812c):UINT32_C(0x002d8128));goto dispatch;}
L_002d8124:
 STEP(UINT32_C(0x002d8124)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d8128));goto dispatch;
L_002d8128:
 STEP(UINT32_C(0x002d8128)); /* 8e030014 lw v1,0x14(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d812c));goto dispatch;
L_002d812c:
 STEP(UINT32_C(0x002d812c)); /* ae030008 sw v1,0x8(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d8130));goto dispatch;
L_002d8130:
 STEP(UINT32_C(0x002d8130)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d8134));goto dispatch;
L_002d8134:
 STEP(UINT32_C(0x002d8134)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d8138));goto dispatch;
L_002d8138:
 STEP(UINT32_C(0x002d8138)); /* dfbf0008 ld ra,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d813c));goto dispatch;
L_002d813c:
 STEP(UINT32_C(0x002d813c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d8140));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002d8140:
 STEP(UINT32_C(0x002d8140)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d8144));goto dispatch;
L_002d6548:
 STEP(UINT32_C(0x002d6548)); /* 27bdfb80 addiu sp,sp,-1152 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffb80)));target=sx(UINT32_C(0x002d654c));goto dispatch;
L_002d654c:
 STEP(UINT32_C(0x002d654c)); /* 240a0400 addiu t2,zero,1024 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(UINT32_C(0x002d6550));goto dispatch;
L_002d6550:
 STEP(UINT32_C(0x002d6550)); /* ffb00460 sd s0,0x460(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000460),&value64,8u);target=sx(UINT32_C(0x002d6554));goto dispatch;
L_002d6554:
 STEP(UINT32_C(0x002d6554)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d6558));goto dispatch;
L_002d6558:
 STEP(UINT32_C(0x002d6558)); /* ffb10468 sd s1,0x468(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000468),&value64,8u);target=sx(UINT32_C(0x002d655c));goto dispatch;
L_002d655c:
 STEP(UINT32_C(0x002d655c)); /* 27ab0060 addiu t3,sp,96 */
 set(m,11u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002d6560));goto dispatch;
L_002d6560:
 STEP(UINT32_C(0x002d6560)); /* ffbf0470 sd ra,0x470(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000470),&value64,8u);target=sx(UINT32_C(0x002d6564));goto dispatch;
L_002d6564:
 STEP(UINT32_C(0x002d6564)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002d6568));goto dispatch;
L_002d6568:
 STEP(UINT32_C(0x002d6568)); /* afab0010 sw t3,0x10(sp) */
 value32=(uint32_t)lo(m,11u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002d656c));goto dispatch;
L_002d656c:
 STEP(UINT32_C(0x002d656c)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002d6570));goto dispatch;
L_002d6570:
 STEP(UINT32_C(0x002d6570)); /* 9609000e lhu t1,0xe(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000e),&value16,2u);set(m,9u,value16);target=sx(UINT32_C(0x002d6574));goto dispatch;
L_002d6574:
 STEP(UINT32_C(0x002d6574)); /* 8e080054 lw t0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002d6578));goto dispatch;
L_002d6578:
 STEP(UINT32_C(0x002d6578)); /* 3042fffd andi v0,v0,0xfffd */
 set(m,2u,lo(m,2u) & UINT64_C(0xfffd));target=sx(UINT32_C(0x002d657c));goto dispatch;
L_002d657c:
 STEP(UINT32_C(0x002d657c)); /* 8e03001c lw v1,0x1c(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d6580));goto dispatch;
L_002d6580:
 STEP(UINT32_C(0x002d6580)); /* 8e070024 lw a3,0x24(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x002d6584));goto dispatch;
L_002d6584:
 STEP(UINT32_C(0x002d6584)); /* afa80054 sw t0,0x54(sp) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000054),&value32,4u);target=sx(UINT32_C(0x002d6588));goto dispatch;
L_002d6588:
 STEP(UINT32_C(0x002d6588)); /* a7a2000c sh v0,0xc(sp) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002d658c));goto dispatch;
L_002d658c:
 STEP(UINT32_C(0x002d658c)); /* a7a9000e sh t1,0xe(sp) */
 value16=(uint16_t)lo(m,9u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000e),&value16,2u);target=sx(UINT32_C(0x002d6590));goto dispatch;
L_002d6590:
 STEP(UINT32_C(0x002d6590)); /* afa3001c sw v1,0x1c(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002d6594));goto dispatch;
L_002d6594:
 STEP(UINT32_C(0x002d6594)); /* afa70024 sw a3,0x24(sp) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002d6598));goto dispatch;
L_002d6598:
 STEP(UINT32_C(0x002d6598)); /* afaa0014 sw t2,0x14(sp) */
 value32=(uint32_t)lo(m,10u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d659c));goto dispatch;
L_002d659c:
 STEP(UINT32_C(0x002d659c)); /* afab0000 sw t3,0x0(sp) */
 value32=(uint32_t)lo(m,11u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d65a0));goto dispatch;
L_002d65a0:
 STEP(UINT32_C(0x002d65a0)); /* afaa0008 sw t2,0x8(sp) */
 value32=(uint32_t)lo(m,10u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d65a4));goto dispatch;
L_002d65a4:
 STEP(UINT32_C(0x002d65a4)); /* 0c0b5980 jal 002d6600 */
 set(m,31u,UINT64_C(0x002d65ac));STEP(UINT32_C(0x002d65a8));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d6600));goto dispatch;
L_002d65a8:
 STEP(UINT32_C(0x002d65a8)); /* afa00018 sw zero,0x18(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d65ac));goto dispatch;
L_002d65ac:
 STEP(UINT32_C(0x002d65ac)); /* 0040882d daddu s1,v0,zero */
 set(m,17u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d65b0));goto dispatch;
L_002d65b0:
 STEP(UINT32_C(0x002d65b0)); /* 06200005 regimm0 s1,002d65c8 */
 {int taken=((int64_t)lo(m,17u)<0);STEP(UINT32_C(0x002d65b4));set(m,4u,lo(m,29u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d65c8):UINT32_C(0x002d65b8));goto dispatch;}
L_002d65b4:
 STEP(UINT32_C(0x002d65b4)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002d65b8));goto dispatch;
L_002d65b8:
 STEP(UINT32_C(0x002d65b8)); /* 0c0b6578 jal 002d95e0 */
 set(m,31u,UINT64_C(0x002d65c0));STEP(UINT32_C(0x002d65bc));/* nop */target=sx(UINT32_C(0x002d95e0));goto dispatch;
L_002d65bc:
 STEP(UINT32_C(0x002d65bc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d65c0));goto dispatch;
L_002d65c0:
 STEP(UINT32_C(0x002d65c0)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d65c4));goto dispatch;
L_002d65c4:
 STEP(UINT32_C(0x002d65c4)); /* 0062880b movn s1,v1,v0 */
 if(lo(m,2u)!=0u)set(m,17u,lo(m,3u));target=sx(UINT32_C(0x002d65c8));goto dispatch;
L_002d65c8:
 STEP(UINT32_C(0x002d65c8)); /* 97a2000c lhu v0,0xc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002d65cc));goto dispatch;
L_002d65cc:
 STEP(UINT32_C(0x002d65cc)); /* 30420040 andi v0,v0,0x40 */
 set(m,2u,lo(m,2u) & UINT64_C(0x40));target=sx(UINT32_C(0x002d65d0));goto dispatch;
L_002d65d0:
 STEP(UINT32_C(0x002d65d0)); /* 10400005 beq v0,zero,002d65e8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d65d4));set(m,2u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d65e8):UINT32_C(0x002d65d8));goto dispatch;}
L_002d65d4:
 STEP(UINT32_C(0x002d65d4)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d65d8));goto dispatch;
L_002d65d8:
 STEP(UINT32_C(0x002d65d8)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002d65dc));goto dispatch;
L_002d65dc:
 STEP(UINT32_C(0x002d65dc)); /* 34420040 ori v0,v0,0x40 */
 set(m,2u,lo(m,2u) | UINT64_C(0x40));target=sx(UINT32_C(0x002d65e0));goto dispatch;
L_002d65e0:
 STEP(UINT32_C(0x002d65e0)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002d65e4));goto dispatch;
L_002d65e4:
 STEP(UINT32_C(0x002d65e4)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d65e8));goto dispatch;
L_002d65e8:
 STEP(UINT32_C(0x002d65e8)); /* dfb00460 ld s0,0x460(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000460),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d65ec));goto dispatch;
L_002d65ec:
 STEP(UINT32_C(0x002d65ec)); /* dfb10468 ld s1,0x468(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000468),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d65f0));goto dispatch;
L_002d65f0:
 STEP(UINT32_C(0x002d65f0)); /* dfbf0470 ld ra,0x470(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000470),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d65f4));goto dispatch;
L_002d65f4:
 STEP(UINT32_C(0x002d65f4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d65f8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000480)));goto dispatch;
L_002d65f8:
 STEP(UINT32_C(0x002d65f8)); /* 27bd0480 addiu sp,sp,1152 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000480)));target=sx(UINT32_C(0x002d65fc));goto dispatch;
L_002d95e0:
 STEP(UINT32_C(0x002d95e0)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d95e4));goto dispatch;
L_002d95e4:
 STEP(UINT32_C(0x002d95e4)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d95e8));goto dispatch;
L_002d95e8:
 STEP(UINT32_C(0x002d95e8)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d95ec));goto dispatch;
L_002d95ec:
 STEP(UINT32_C(0x002d95ec)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d95f0));goto dispatch;
L_002d95f0:
 STEP(UINT32_C(0x002d95f0)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d95f4));goto dispatch;
L_002d95f4:
 STEP(UINT32_C(0x002d95f4)); /* 1620000c bne s1,zero,002d9628 */
 {int taken=(lo(m,17u)!=lo(m,0u));STEP(UINT32_C(0x002d95f8));value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(taken?UINT32_C(0x002d9628):UINT32_C(0x002d95fc));goto dispatch;}
L_002d95f8:
 STEP(UINT32_C(0x002d95f8)); /* ffbf0018 sd ra,0x18(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002d95fc));goto dispatch;
L_002d95fc:
 STEP(UINT32_C(0x002d95fc)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9600));goto dispatch;
L_002d9600:
 STEP(UINT32_C(0x002d9600)); /* 3c05002e lui a1,zero,0x2e */
 set(m,5u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002d9604));goto dispatch;
L_002d9604:
 STEP(UINT32_C(0x002d9604)); /* 8c44be28 lw a0,-0x41d8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbe28),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d9608));goto dispatch;
L_002d9608:
 STEP(UINT32_C(0x002d9608)); /* 24a595e0 addiu a1,a1,-27168 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffff95e0)));target=sx(UINT32_C(0x002d960c));goto dispatch;
L_002d960c:
 STEP(UINT32_C(0x002d960c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d9610));goto dispatch;
L_002d9610:
 STEP(UINT32_C(0x002d9610)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d9614));goto dispatch;
L_002d9614:
 STEP(UINT32_C(0x002d9614)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002d9618));goto dispatch;
L_002d9618:
 STEP(UINT32_C(0x002d9618)); /* dfbf0018 ld ra,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d961c));goto dispatch;
L_002d961c:
 STEP(UINT32_C(0x002d961c)); /* 080b6878 j 002da1e0 */
 STEP(UINT32_C(0x002d9620));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002da1e0));goto dispatch;
L_002d9620:
 STEP(UINT32_C(0x002d9620)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d9624));goto dispatch;
L_002d9624:
 STEP(UINT32_C(0x002d9624)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9628));goto dispatch;
L_002d9628:
 STEP(UINT32_C(0x002d9628)); /* 8e230054 lw v1,0x54(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000054),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d962c));goto dispatch;
L_002d962c:
 STEP(UINT32_C(0x002d962c)); /* 54600006 bnel v1,zero,002d9648 */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x002d9630));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000038),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9648));}else target=sx(UINT32_C(0x002d9634));goto dispatch;
L_002d9630:
 STEP(UINT32_C(0x002d9630)); /* 8c620038 lw v0,0x38(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000038),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9634));goto dispatch;
L_002d9634:
 STEP(UINT32_C(0x002d9634)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d9638));goto dispatch;
L_002d9638:
 STEP(UINT32_C(0x002d9638)); /* 8c43be28 lw v1,-0x41d8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbe28),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d963c));goto dispatch;
L_002d963c:
 STEP(UINT32_C(0x002d963c)); /* ae230054 sw v1,0x54(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000054),&value32,4u);target=sx(UINT32_C(0x002d9640));goto dispatch;
L_002d9640:
 STEP(UINT32_C(0x002d9640)); /* 8c620038 lw v0,0x38(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000038),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9644));goto dispatch;
L_002d9644:
 STEP(UINT32_C(0x002d9644)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d9648));goto dispatch;
L_002d9648:
 STEP(UINT32_C(0x002d9648)); /* 54400004 bnel v0,zero,002d965c */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002d964c));READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002d965c));}else target=sx(UINT32_C(0x002d9650));goto dispatch;
L_002d964c:
 STEP(UINT32_C(0x002d964c)); /* 8623000c lh v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002d9650));goto dispatch;
L_002d9650:
 STEP(UINT32_C(0x002d9650)); /* 0c0b6642 jal 002d9908 */
 set(m,31u,UINT64_C(0x002d9658));STEP(UINT32_C(0x002d9654));set(m,4u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d9908));goto dispatch;
L_002d9654:
 STEP(UINT32_C(0x002d9654)); /* 0060202d daddu a0,v1,zero */
 set(m,4u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002d9658));goto dispatch;
L_002d9658:
 STEP(UINT32_C(0x002d9658)); /* 8623000c lh v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002d965c));goto dispatch;
L_002d965c:
 STEP(UINT32_C(0x002d965c)); /* 30620008 andi v0,v1,0x8 */
 set(m,2u,lo(m,3u) & UINT64_C(0x8));target=sx(UINT32_C(0x002d9660));goto dispatch;
L_002d9660:
 STEP(UINT32_C(0x002d9660)); /* 1040001e beq v0,zero,002d96dc */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d9664));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d96dc):UINT32_C(0x002d9668));goto dispatch;}
L_002d9664:
 STEP(UINT32_C(0x002d9664)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9668));goto dispatch;
L_002d9668:
 STEP(UINT32_C(0x002d9668)); /* 8e320010 lw s2,0x10(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);set(m,18u,sx(value32));target=sx(UINT32_C(0x002d966c));goto dispatch;
L_002d966c:
 STEP(UINT32_C(0x002d966c)); /* 1240001b beq s2,zero,002d96dc */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002d9670));set(m,4u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d96dc):UINT32_C(0x002d9674));goto dispatch;}
L_002d9670:
 STEP(UINT32_C(0x002d9670)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9674));goto dispatch;
L_002d9674:
 STEP(UINT32_C(0x002d9674)); /* 8e220000 lw v0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d9678));goto dispatch;
L_002d9678:
 STEP(UINT32_C(0x002d9678)); /* 30630003 andi v1,v1,0x3 */
 set(m,3u,lo(m,3u) & UINT64_C(0x3));target=sx(UINT32_C(0x002d967c));goto dispatch;
L_002d967c:
 STEP(UINT32_C(0x002d967c)); /* ae320000 sw s2,0x0(s1) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d9680));goto dispatch;
L_002d9680:
 STEP(UINT32_C(0x002d9680)); /* 14600009 bne v1,zero,002d96a8 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002d9684));set(m,16u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,18u)));target=sx(taken?UINT32_C(0x002d96a8):UINT32_C(0x002d9688));goto dispatch;}
L_002d9684:
 STEP(UINT32_C(0x002d9684)); /* 00528023 subu s0,v0,s2 */
 set(m,16u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,18u)));target=sx(UINT32_C(0x002d9688));goto dispatch;
L_002d9688:
 STEP(UINT32_C(0x002d9688)); /* 10000007 beq zero,zero,002d96a8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d968c));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x002d96a8):UINT32_C(0x002d9690));goto dispatch;}
L_002d968c:
 STEP(UINT32_C(0x002d968c)); /* 8e240014 lw a0,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d9690));goto dispatch;
L_002d9690:
 STEP(UINT32_C(0x002d9690)); /* 9623000c lhu v1,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002d9694));goto dispatch;
L_002d9694:
 STEP(UINT32_C(0x002d9694)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d9698));goto dispatch;
L_002d9698:
 STEP(UINT32_C(0x002d9698)); /* 34630040 ori v1,v1,0x40 */
 set(m,3u,lo(m,3u) | UINT64_C(0x40));target=sx(UINT32_C(0x002d969c));goto dispatch;
L_002d969c:
 STEP(UINT32_C(0x002d969c)); /* 1000000f beq zero,zero,002d96dc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d96a0));value16=(uint16_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);target=sx(taken?UINT32_C(0x002d96dc):UINT32_C(0x002d96a4));goto dispatch;}
L_002d96a0:
 STEP(UINT32_C(0x002d96a0)); /* a623000c sh v1,0xc(s1) */
 value16=(uint16_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002d96a4));goto dispatch;
L_002d96a4:
 STEP(UINT32_C(0x002d96a4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d96a8));goto dispatch;
L_002d96a8:
 STEP(UINT32_C(0x002d96a8)); /* 1a00000b blez s0,zero,002d96d8 */
 {int taken=((int64_t)lo(m,16u)<=0);STEP(UINT32_C(0x002d96ac));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002d96d8):UINT32_C(0x002d96b0));goto dispatch;}
L_002d96ac:
 STEP(UINT32_C(0x002d96ac)); /* ae240008 sw a0,0x8(s1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d96b0));goto dispatch;
L_002d96b0:
 STEP(UINT32_C(0x002d96b0)); /* 8e220024 lw v0,0x24(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d96b4));goto dispatch;
L_002d96b4:
 STEP(UINT32_C(0x002d96b4)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d96b8));goto dispatch;
L_002d96b8:
 STEP(UINT32_C(0x002d96b8)); /* 8e24001c lw a0,0x1c(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d96bc));goto dispatch;
L_002d96bc:
 STEP(UINT32_C(0x002d96bc)); /* 0040f809 jalr ra,v0 */
 target=sx((uint32_t)lo(m,2u));set(m,31u,UINT64_C(0x002d96c4));STEP(UINT32_C(0x002d96c0));set(m,5u,lo(m,18u)+lo(m,0u));goto dispatch;
L_002d96c0:
 STEP(UINT32_C(0x002d96c0)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d96c4));goto dispatch;
L_002d96c4:
 STEP(UINT32_C(0x002d96c4)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d96c8));goto dispatch;
L_002d96c8:
 STEP(UINT32_C(0x002d96c8)); /* 1860fff1 blez v1,zero,002d9690 */
 {int taken=((int64_t)lo(m,3u)<=0);STEP(UINT32_C(0x002d96cc));set(m,16u,sx((uint32_t)lo(m,16u)-(uint32_t)lo(m,3u)));target=sx(taken?UINT32_C(0x002d9690):UINT32_C(0x002d96d0));goto dispatch;}
L_002d96cc:
 STEP(UINT32_C(0x002d96cc)); /* 02038023 subu s0,s0,v1 */
 set(m,16u,sx((uint32_t)lo(m,16u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d96d0));goto dispatch;
L_002d96d0:
 STEP(UINT32_C(0x002d96d0)); /* 1e00fff7 bgtz s0,zero,002d96b0 */
 {int taken=((int64_t)lo(m,16u)>0);STEP(UINT32_C(0x002d96d4));set(m,18u,sx((uint32_t)lo(m,18u)+(uint32_t)lo(m,3u)));target=sx(taken?UINT32_C(0x002d96b0):UINT32_C(0x002d96d8));goto dispatch;}
L_002d96d4:
 STEP(UINT32_C(0x002d96d4)); /* 02439021 addu s2,s2,v1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002d96d8));goto dispatch;
L_002d96d8:
 STEP(UINT32_C(0x002d96d8)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d96dc));goto dispatch;
L_002d96dc:
 STEP(UINT32_C(0x002d96dc)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d96e0));goto dispatch;
L_002d96e0:
 STEP(UINT32_C(0x002d96e0)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d96e4));goto dispatch;
L_002d96e4:
 STEP(UINT32_C(0x002d96e4)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002d96e8));goto dispatch;
L_002d96e8:
 STEP(UINT32_C(0x002d96e8)); /* dfbf0018 ld ra,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d96ec));goto dispatch;
L_002d96ec:
 STEP(UINT32_C(0x002d96ec)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d96f0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002d96f0:
 STEP(UINT32_C(0x002d96f0)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d96f4));goto dispatch;
L_002da360:
 STEP(UINT32_C(0x002da360)); /* 27bdff70 addiu sp,sp,-144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff70)));target=sx(UINT32_C(0x002da364));goto dispatch;
L_002da364:
 STEP(UINT32_C(0x002da364)); /* ffb00070 sd s0,0x70(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002da368));goto dispatch;
L_002da368:
 STEP(UINT32_C(0x002da368)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002da36c));goto dispatch;
L_002da36c:
 STEP(UINT32_C(0x002da36c)); /* ffb10078 sd s1,0x78(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000078),&value64,8u);target=sx(UINT32_C(0x002da370));goto dispatch;
L_002da370:
 STEP(UINT32_C(0x002da370)); /* ffb20080 sd s2,0x80(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002da374));goto dispatch;
L_002da374:
 STEP(UINT32_C(0x002da374)); /* ffbf0088 sd ra,0x88(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000088),&value64,8u);target=sx(UINT32_C(0x002da378));goto dispatch;
L_002da378:
 STEP(UINT32_C(0x002da378)); /* 9603000c lhu v1,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002da37c));goto dispatch;
L_002da37c:
 STEP(UINT32_C(0x002da37c)); /* 30620002 andi v0,v1,0x2 */
 set(m,2u,lo(m,3u) & UINT64_C(0x2));target=sx(UINT32_C(0x002da380));goto dispatch;
L_002da380:
 STEP(UINT32_C(0x002da380)); /* 10400007 beq v0,zero,002da3a0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002da384));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002da3a0):UINT32_C(0x002da388));goto dispatch;}
L_002da384:
 STEP(UINT32_C(0x002da384)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002da388));goto dispatch;
L_002da388:
 STEP(UINT32_C(0x002da388)); /* 26030043 addiu v1,s0,67 */
 set(m,3u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000043)));target=sx(UINT32_C(0x002da38c));goto dispatch;
L_002da38c:
 STEP(UINT32_C(0x002da38c)); /* ae020014 sw v0,0x14(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002da390));goto dispatch;
L_002da390:
 STEP(UINT32_C(0x002da390)); /* ae030010 sw v1,0x10(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002da394));goto dispatch;
L_002da394:
 STEP(UINT32_C(0x002da394)); /* 10000041 beq zero,zero,002da49c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da398));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002da49c):UINT32_C(0x002da39c));goto dispatch;}
L_002da398:
 STEP(UINT32_C(0x002da398)); /* ae030000 sw v1,0x0(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002da39c));goto dispatch;
L_002da39c:
 STEP(UINT32_C(0x002da39c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da3a0));goto dispatch;
L_002da3a0:
 STEP(UINT32_C(0x002da3a0)); /* 8605000e lh a1,0xe(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000e),&value16,2u);set(m,5u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002da3a4));goto dispatch;
L_002da3a4:
 STEP(UINT32_C(0x002da3a4)); /* 04a00008 regimm0 a1,002da3c8 */
 {int taken=((int64_t)lo(m,5u)<0);STEP(UINT32_C(0x002da3a8));set(m,2u,lo(m,3u) | UINT64_C(0x800));target=sx(taken?UINT32_C(0x002da3c8):UINT32_C(0x002da3ac));goto dispatch;}
L_002da3a8:
 STEP(UINT32_C(0x002da3a8)); /* 34620800 ori v0,v1,0x800 */
 set(m,2u,lo(m,3u) | UINT64_C(0x800));target=sx(UINT32_C(0x002da3ac));goto dispatch;
L_002da3ac:
 STEP(UINT32_C(0x002da3ac)); /* 8e040054 lw a0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002da3b0));goto dispatch;
L_002da3b0:
 STEP(UINT32_C(0x002da3b0)); /* 0c0b6e54 jal 002db950 */
 set(m,31u,UINT64_C(0x002da3b8));STEP(UINT32_C(0x002da3b4));set(m,6u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002db950));goto dispatch;
L_002da3b4:
 STEP(UINT32_C(0x002da3b4)); /* 03a0302d daddu a2,sp,zero */
 set(m,6u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002da3b8));goto dispatch;
L_002da3b8:
 STEP(UINT32_C(0x002da3b8)); /* 04410007 regimm1 v0,002da3d8 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002da3bc));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x002da3d8):UINT32_C(0x002da3c0));goto dispatch;}
L_002da3bc:
 STEP(UINT32_C(0x002da3bc)); /* 8fa20004 lw v0,0x4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002da3c0));goto dispatch;
L_002da3c0:
 STEP(UINT32_C(0x002da3c0)); /* 9603000c lhu v1,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,3u,value16);target=sx(UINT32_C(0x002da3c4));goto dispatch;
L_002da3c4:
 STEP(UINT32_C(0x002da3c4)); /* 34620800 ori v0,v1,0x800 */
 set(m,2u,lo(m,3u) | UINT64_C(0x800));target=sx(UINT32_C(0x002da3c8));goto dispatch;
L_002da3c8:
 STEP(UINT32_C(0x002da3c8)); /* 0000902d daddu s2,zero,zero */
 set(m,18u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002da3cc));goto dispatch;
L_002da3cc:
 STEP(UINT32_C(0x002da3cc)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002da3d0));goto dispatch;
L_002da3d0:
 STEP(UINT32_C(0x002da3d0)); /* 10000012 beq zero,zero,002da41c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da3d4));set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(taken?UINT32_C(0x002da41c):UINT32_C(0x002da3d8));goto dispatch;}
L_002da3d4:
 STEP(UINT32_C(0x002da3d4)); /* 24110400 addiu s1,zero,1024 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(UINT32_C(0x002da3d8));goto dispatch;
L_002da3d8:
 STEP(UINT32_C(0x002da3d8)); /* 34048000 ori a0,zero,0x8000 */
 set(m,4u,lo(m,0u) | UINT64_C(0x8000));target=sx(UINT32_C(0x002da3dc));goto dispatch;
L_002da3dc:
 STEP(UINT32_C(0x002da3dc)); /* 24110400 addiu s1,zero,1024 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(UINT32_C(0x002da3e0));goto dispatch;
L_002da3e0:
 STEP(UINT32_C(0x002da3e0)); /* 3042f000 andi v0,v0,0xf000 */
 set(m,2u,lo(m,2u) & UINT64_C(0xf000));target=sx(UINT32_C(0x002da3e4));goto dispatch;
L_002da3e4:
 STEP(UINT32_C(0x002da3e4)); /* 38432000 xori v1,v0,0x2000 */
 set(m,3u,lo(m,2u)^UINT64_C(0x2000));target=sx(UINT32_C(0x002da3e8));goto dispatch;
L_002da3e8:
 STEP(UINT32_C(0x002da3e8)); /* 14440009 bne v0,a0,002da410 */
 {int taken=(lo(m,2u)!=lo(m,4u));STEP(UINT32_C(0x002da3ec));set(m,18u,(lo(m,3u)<UINT64_C(0x1)));target=sx(taken?UINT32_C(0x002da410):UINT32_C(0x002da3f0));goto dispatch;}
L_002da3ec:
 STEP(UINT32_C(0x002da3ec)); /* 2c720001 sltiu s2,v1,1 */
 set(m,18u,(lo(m,3u)<UINT64_C(0x1)));target=sx(UINT32_C(0x002da3f0));goto dispatch;
L_002da3f0:
 STEP(UINT32_C(0x002da3f0)); /* 3c02002e lui v0,zero,0x2e */
 set(m,2u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002da3f4));goto dispatch;
L_002da3f4:
 STEP(UINT32_C(0x002da3f4)); /* 8e030028 lw v1,0x28(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000028),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002da3f8));goto dispatch;
L_002da3f8:
 STEP(UINT32_C(0x002da3f8)); /* 2442b758 addiu v0,v0,-18600 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb758)));target=sx(UINT32_C(0x002da3fc));goto dispatch;
L_002da3fc:
 STEP(UINT32_C(0x002da3fc)); /* 14620005 bne v1,v0,002da414 */
 {int taken=(lo(m,3u)!=lo(m,2u));STEP(UINT32_C(0x002da400));READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(taken?UINT32_C(0x002da414):UINT32_C(0x002da404));goto dispatch;}
L_002da400:
 STEP(UINT32_C(0x002da400)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002da404));goto dispatch;
L_002da404:
 STEP(UINT32_C(0x002da404)); /* ae11004c sw s1,0x4c(s0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000004c),&value32,4u);target=sx(UINT32_C(0x002da408));goto dispatch;
L_002da408:
 STEP(UINT32_C(0x002da408)); /* 10000003 beq zero,zero,002da418 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da40c));set(m,2u,lo(m,2u) | UINT64_C(0x400));target=sx(taken?UINT32_C(0x002da418):UINT32_C(0x002da410));goto dispatch;}
L_002da40c:
 STEP(UINT32_C(0x002da40c)); /* 34420400 ori v0,v0,0x400 */
 set(m,2u,lo(m,2u) | UINT64_C(0x400));target=sx(UINT32_C(0x002da410));goto dispatch;
L_002da410:
 STEP(UINT32_C(0x002da410)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002da414));goto dispatch;
L_002da414:
 STEP(UINT32_C(0x002da414)); /* 34420800 ori v0,v0,0x800 */
 set(m,2u,lo(m,2u) | UINT64_C(0x800));target=sx(UINT32_C(0x002da418));goto dispatch;
L_002da418:
 STEP(UINT32_C(0x002da418)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002da41c));goto dispatch;
L_002da41c:
 STEP(UINT32_C(0x002da41c)); /* 8e040054 lw a0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002da420));goto dispatch;
L_002da420:
 STEP(UINT32_C(0x002da420)); /* 0c0b4efa jal 002d3be8 */
 set(m,31u,UINT64_C(0x002da428));STEP(UINT32_C(0x002da424));set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(UINT32_C(0x002d3be8));goto dispatch;
L_002da424:
 STEP(UINT32_C(0x002da424)); /* 24050400 addiu a1,zero,1024 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(UINT32_C(0x002da428));goto dispatch;
L_002da428:
 STEP(UINT32_C(0x002da428)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002da42c));goto dispatch;
L_002da42c:
 STEP(UINT32_C(0x002da42c)); /* 14a0000a bne a1,zero,002da458 */
 {int taken=(lo(m,5u)!=lo(m,0u));STEP(UINT32_C(0x002da430));READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(taken?UINT32_C(0x002da458):UINT32_C(0x002da434));goto dispatch;}
L_002da430:
 STEP(UINT32_C(0x002da430)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002da434));goto dispatch;
L_002da434:
 STEP(UINT32_C(0x002da434)); /* 26040043 addiu a0,s0,67 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000043)));target=sx(UINT32_C(0x002da438));goto dispatch;
L_002da438:
 STEP(UINT32_C(0x002da438)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002da43c));goto dispatch;
L_002da43c:
 STEP(UINT32_C(0x002da43c)); /* ae040010 sw a0,0x10(s0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002da440));goto dispatch;
L_002da440:
 STEP(UINT32_C(0x002da440)); /* 34420002 ori v0,v0,0x2 */
 set(m,2u,lo(m,2u) | UINT64_C(0x2));target=sx(UINT32_C(0x002da444));goto dispatch;
L_002da444:
 STEP(UINT32_C(0x002da444)); /* ae030014 sw v1,0x14(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002da448));goto dispatch;
L_002da448:
 STEP(UINT32_C(0x002da448)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002da44c));goto dispatch;
L_002da44c:
 STEP(UINT32_C(0x002da44c)); /* 10000013 beq zero,zero,002da49c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002da450));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002da49c):UINT32_C(0x002da454));goto dispatch;}
L_002da450:
 STEP(UINT32_C(0x002da450)); /* ae040000 sw a0,0x0(s0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002da454));goto dispatch;
L_002da454:
 STEP(UINT32_C(0x002da454)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da458));goto dispatch;
L_002da458:
 STEP(UINT32_C(0x002da458)); /* 3c03002e lui v1,zero,0x2e */
 set(m,3u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002da45c));goto dispatch;
L_002da45c:
 STEP(UINT32_C(0x002da45c)); /* 8e040054 lw a0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002da460));goto dispatch;
L_002da460:
 STEP(UINT32_C(0x002da460)); /* 246398c8 addiu v1,v1,-26424 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffff98c8)));target=sx(UINT32_C(0x002da464));goto dispatch;
L_002da464:
 STEP(UINT32_C(0x002da464)); /* 34420080 ori v0,v0,0x80 */
 set(m,2u,lo(m,2u) | UINT64_C(0x80));target=sx(UINT32_C(0x002da468));goto dispatch;
L_002da468:
 STEP(UINT32_C(0x002da468)); /* ae050010 sw a1,0x10(s0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002da46c));goto dispatch;
L_002da46c:
 STEP(UINT32_C(0x002da46c)); /* ac83003c sw v1,0x3c(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000003c),&value32,4u);target=sx(UINT32_C(0x002da470));goto dispatch;
L_002da470:
 STEP(UINT32_C(0x002da470)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002da474));goto dispatch;
L_002da474:
 STEP(UINT32_C(0x002da474)); /* ae110014 sw s1,0x14(s0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002da478));goto dispatch;
L_002da478:
 STEP(UINT32_C(0x002da478)); /* 12400008 beq s2,zero,002da49c */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002da47c));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002da49c):UINT32_C(0x002da480));goto dispatch;}
L_002da47c:
 STEP(UINT32_C(0x002da47c)); /* ae050000 sw a1,0x0(s0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002da480));goto dispatch;
L_002da480:
 STEP(UINT32_C(0x002da480)); /* 0c0b7194 jal 002dc650 */
 set(m,31u,UINT64_C(0x002da488));STEP(UINT32_C(0x002da484));READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000e),&value16,2u);set(m,4u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002dc650));goto dispatch;
L_002da484:
 STEP(UINT32_C(0x002da484)); /* 8604000e lh a0,0xe(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000e),&value16,2u);set(m,4u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002da488));goto dispatch;
L_002da488:
 STEP(UINT32_C(0x002da488)); /* 50400005 beql v0,zero,002da4a0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002da48c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002da4a0));}else target=sx(UINT32_C(0x002da490));goto dispatch;
L_002da48c:
 STEP(UINT32_C(0x002da48c)); /* dfb00070 ld s0,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002da490));goto dispatch;
L_002da490:
 STEP(UINT32_C(0x002da490)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002da494));goto dispatch;
L_002da494:
 STEP(UINT32_C(0x002da494)); /* 34420001 ori v0,v0,0x1 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1));target=sx(UINT32_C(0x002da498));goto dispatch;
L_002da498:
 STEP(UINT32_C(0x002da498)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002da49c));goto dispatch;
L_002da49c:
 STEP(UINT32_C(0x002da49c)); /* dfb00070 ld s0,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002da4a0));goto dispatch;
L_002da4a0:
 STEP(UINT32_C(0x002da4a0)); /* dfb10078 ld s1,0x78(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000078),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002da4a4));goto dispatch;
L_002da4a4:
 STEP(UINT32_C(0x002da4a4)); /* dfb20080 ld s2,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002da4a8));goto dispatch;
L_002da4a8:
 STEP(UINT32_C(0x002da4a8)); /* dfbf0088 ld ra,0x88(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000088),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002da4ac));goto dispatch;
L_002da4ac:
 STEP(UINT32_C(0x002da4ac)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002da4b0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));goto dispatch;
L_002da4b0:
 STEP(UINT32_C(0x002da4b0)); /* 27bd0090 addiu sp,sp,144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));target=sx(UINT32_C(0x002da4b4));goto dispatch;
L_002db6d8:
 STEP(UINT32_C(0x002db6d8)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002db6dc));goto dispatch;
L_002db6dc:
 STEP(UINT32_C(0x002db6dc)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002db6e0));goto dispatch;
L_002db6e0:
 STEP(UINT32_C(0x002db6e0)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002db6e4));goto dispatch;
L_002db6e4:
 STEP(UINT32_C(0x002db6e4)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002db6e8));goto dispatch;
L_002db6e8:
 STEP(UINT32_C(0x002db6e8)); /* 00a0882d daddu s1,a1,zero */
 set(m,17u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002db6ec));goto dispatch;
L_002db6ec:
 STEP(UINT32_C(0x002db6ec)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002db6f0));goto dispatch;
L_002db6f0:
 STEP(UINT32_C(0x002db6f0)); /* 00c0902d daddu s2,a2,zero */
 set(m,18u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002db6f4));goto dispatch;
L_002db6f4:
 STEP(UINT32_C(0x002db6f4)); /* ffbf0018 sd ra,0x18(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002db6f8));goto dispatch;
L_002db6f8:
 STEP(UINT32_C(0x002db6f8)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002db6fc));goto dispatch;
L_002db6fc:
 STEP(UINT32_C(0x002db6fc)); /* 30420100 andi v0,v0,0x100 */
 set(m,2u,lo(m,2u) & UINT64_C(0x100));target=sx(UINT32_C(0x002db700));goto dispatch;
L_002db700:
 STEP(UINT32_C(0x002db700)); /* 10400005 beq v0,zero,002db718 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002db704));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002db718):UINT32_C(0x002db708));goto dispatch;}
L_002db704:
 STEP(UINT32_C(0x002db704)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002db708));goto dispatch;
L_002db708:
 STEP(UINT32_C(0x002db708)); /* 8e040054 lw a0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002db70c));goto dispatch;
L_002db70c:
 STEP(UINT32_C(0x002db70c)); /* 24070002 addiu a3,zero,2 */
 set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002db710));goto dispatch;
L_002db710:
 STEP(UINT32_C(0x002db710)); /* 0c0b6e6c jal 002db9b0 */
 set(m,31u,UINT64_C(0x002db718));STEP(UINT32_C(0x002db714));READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000e),&value16,2u);set(m,5u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002db9b0));goto dispatch;
L_002db714:
 STEP(UINT32_C(0x002db714)); /* 8605000e lh a1,0xe(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000e),&value16,2u);set(m,5u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002db718));goto dispatch;
L_002db718:
 STEP(UINT32_C(0x002db718)); /* 9602000c lhu v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002db71c));goto dispatch;
L_002db71c:
 STEP(UINT32_C(0x002db71c)); /* 0220302d daddu a2,s1,zero */
 set(m,6u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002db720));goto dispatch;
L_002db720:
 STEP(UINT32_C(0x002db720)); /* 8605000e lh a1,0xe(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000e),&value16,2u);set(m,5u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x002db724));goto dispatch;
L_002db724:
 STEP(UINT32_C(0x002db724)); /* 0240382d daddu a3,s2,zero */
 set(m,7u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002db728));goto dispatch;
L_002db728:
 STEP(UINT32_C(0x002db728)); /* 3042efff andi v0,v0,0xefff */
 set(m,2u,lo(m,2u) & UINT64_C(0xefff));target=sx(UINT32_C(0x002db72c));goto dispatch;
L_002db72c:
 STEP(UINT32_C(0x002db72c)); /* 8e040054 lw a0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002db730));goto dispatch;
L_002db730:
 STEP(UINT32_C(0x002db730)); /* 0c0b6df8 jal 002db7e0 */
 set(m,31u,UINT64_C(0x002db738));STEP(UINT32_C(0x002db734));value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002db7e0));goto dispatch;
L_002db734:
 STEP(UINT32_C(0x002db734)); /* a602000c sh v0,0xc(s0) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002db738));goto dispatch;
L_002db738:
 STEP(UINT32_C(0x002db738)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002db73c));goto dispatch;
L_002db73c:
 STEP(UINT32_C(0x002db73c)); /* 0002103c dsll32 v0,v0,0 */
 set(m,2u,lo(m,2u)<<32u);target=sx(UINT32_C(0x002db740));goto dispatch;
L_002db740:
 STEP(UINT32_C(0x002db740)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x002db744));goto dispatch;
L_002db744:
 STEP(UINT32_C(0x002db744)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002db748));goto dispatch;
L_002db748:
 STEP(UINT32_C(0x002db748)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002db74c));goto dispatch;
L_002db74c:
 STEP(UINT32_C(0x002db74c)); /* dfbf0018 ld ra,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002db750));goto dispatch;
L_002db750:
 STEP(UINT32_C(0x002db750)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002db754));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002db754:
 STEP(UINT32_C(0x002db754)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002db758));goto dispatch;
L_002db7e0:
 STEP(UINT32_C(0x002db7e0)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002db7e4));goto dispatch;
L_002db7e4:
 STEP(UINT32_C(0x002db7e4)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002db7e8));goto dispatch;
L_002db7e8:
 STEP(UINT32_C(0x002db7e8)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002db7ec));goto dispatch;
L_002db7ec:
 STEP(UINT32_C(0x002db7ec)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002db7f0));goto dispatch;
L_002db7f0:
 STEP(UINT32_C(0x002db7f0)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002db7f4));goto dispatch;
L_002db7f4:
 STEP(UINT32_C(0x002db7f4)); /* 24512178 addiu s1,v0,8568 */
 set(m,17u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00002178)));target=sx(UINT32_C(0x002db7f8));goto dispatch;
L_002db7f8:
 STEP(UINT32_C(0x002db7f8)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002db7fc));goto dispatch;
L_002db7fc:
 STEP(UINT32_C(0x002db7fc)); /* 00c0282d daddu a1,a2,zero */
 set(m,5u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002db800));goto dispatch;
L_002db800:
 STEP(UINT32_C(0x002db800)); /* 00e0302d daddu a2,a3,zero */
 set(m,6u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002db804));goto dispatch;
L_002db804:
 STEP(UINT32_C(0x002db804)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002db808));goto dispatch;
L_002db808:
 STEP(UINT32_C(0x002db808)); /* 0c0b711a jal 002dc468 */
 set(m,31u,UINT64_C(0x002db810));STEP(UINT32_C(0x002db80c));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002dc468));goto dispatch;
L_002db80c:
 STEP(UINT32_C(0x002db80c)); /* ae200000 sw zero,0x0(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002db810));goto dispatch;
L_002db810:
 STEP(UINT32_C(0x002db810)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002db814));goto dispatch;
L_002db814:
 STEP(UINT32_C(0x002db814)); /* 2404ffff addiu a0,zero,-1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002db818));goto dispatch;
L_002db818:
 STEP(UINT32_C(0x002db818)); /* 14640004 bne v1,a0,002db82c */
 {int taken=(lo(m,3u)!=lo(m,4u));STEP(UINT32_C(0x002db81c));set(m,2u,lo(m,3u)+lo(m,0u));target=sx(taken?UINT32_C(0x002db82c):UINT32_C(0x002db820));goto dispatch;}
L_002db81c:
 STEP(UINT32_C(0x002db81c)); /* 0060102d daddu v0,v1,zero */
 set(m,2u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002db820));goto dispatch;
L_002db820:
 STEP(UINT32_C(0x002db820)); /* 8e230000 lw v1,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002db824));goto dispatch;
L_002db824:
 STEP(UINT32_C(0x002db824)); /* 54600001 bnel v1,zero,002db82c */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x002db828));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002db82c));}else target=sx(UINT32_C(0x002db82c));goto dispatch;
L_002db828:
 STEP(UINT32_C(0x002db828)); /* ae030000 sw v1,0x0(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002db82c));goto dispatch;
L_002db82c:
 STEP(UINT32_C(0x002db82c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002db830));goto dispatch;
L_002db830:
 STEP(UINT32_C(0x002db830)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002db834));goto dispatch;
L_002db834:
 STEP(UINT32_C(0x002db834)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002db838));goto dispatch;
L_002db838:
 STEP(UINT32_C(0x002db838)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002db83c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002db83c:
 STEP(UINT32_C(0x002db83c)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002db840));goto dispatch;
L_002dc468:
 STEP(UINT32_C(0x002dc468)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002dc46c));goto dispatch;
L_002dc46c:
 STEP(UINT32_C(0x002dc46c)); /* 2484ffff addiu a0,a0,-1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dc470));goto dispatch;
L_002dc470:
 STEP(UINT32_C(0x002dc470)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dc474));goto dispatch;
L_002dc474:
 STEP(UINT32_C(0x002dc474)); /* 2c840002 sltiu a0,a0,2 */
 set(m,4u,(lo(m,4u)<UINT64_C(0x2)));target=sx(UINT32_C(0x002dc478));goto dispatch;
L_002dc478:
 STEP(UINT32_C(0x002dc478)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dc47c));goto dispatch;
L_002dc47c:
 STEP(UINT32_C(0x002dc47c)); /* 00c0902d daddu s2,a2,zero */
 set(m,18u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002dc480));goto dispatch;
L_002dc480:
 STEP(UINT32_C(0x002dc480)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002dc484));goto dispatch;
L_002dc484:
 STEP(UINT32_C(0x002dc484)); /* 00a0882d daddu s1,a1,zero */
 set(m,17u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002dc488));goto dispatch;
L_002dc488:
 STEP(UINT32_C(0x002dc488)); /* 1080000f beq a0,zero,002dc4c8 */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x002dc48c));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x002dc4c8):UINT32_C(0x002dc490));goto dispatch;}
L_002dc48c:
 STEP(UINT32_C(0x002dc48c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dc490));goto dispatch;
L_002dc490:
 STEP(UINT32_C(0x002dc490)); /* 3c100053 lui s0,zero,0x53 */
 set(m,16u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002dc494));goto dispatch;
L_002dc494:
 STEP(UINT32_C(0x002dc494)); /* 8e02c2a4 lw v0,-0x3d5c(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffc2a4),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dc498));goto dispatch;
L_002dc498:
 STEP(UINT32_C(0x002dc498)); /* 14400007 bne v0,zero,002dc4b8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dc49c));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dc4b8):UINT32_C(0x002dc4a0));goto dispatch;}
L_002dc49c:
 STEP(UINT32_C(0x002dc49c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dc4a0));goto dispatch;
L_002dc4a0:
 STEP(UINT32_C(0x002dc4a0)); /* 0c0b74d8 jal 002dd360 */
 set(m,31u,UINT64_C(0x002dc4a8));STEP(UINT32_C(0x002dc4a4));/* nop */target=sx(UINT32_C(0x002dd360));goto dispatch;
L_002dc4a4:
 STEP(UINT32_C(0x002dc4a4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc4a8));goto dispatch;
L_002dc4a8:
 STEP(UINT32_C(0x002dc4a8)); /* 10400007 beq v0,zero,002dc4c8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002dc4ac));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002dc4c8):UINT32_C(0x002dc4b0));goto dispatch;}
L_002dc4ac:
 STEP(UINT32_C(0x002dc4ac)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dc4b0));goto dispatch;
L_002dc4b0:
 STEP(UINT32_C(0x002dc4b0)); /* ae02c2a4 sw v0,-0x3d5c(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0xffffc2a4),&value32,4u);target=sx(UINT32_C(0x002dc4b4));goto dispatch;
L_002dc4b4:
 STEP(UINT32_C(0x002dc4b4)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dc4b8));goto dispatch;
L_002dc4b8:
 STEP(UINT32_C(0x002dc4b8)); /* 0c0b7450 jal 002dd140 */
 set(m,31u,UINT64_C(0x002dc4c0));STEP(UINT32_C(0x002dc4bc));set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002dd140));goto dispatch;
L_002dc4bc:
 STEP(UINT32_C(0x002dc4bc)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002dc4c0));goto dispatch;
L_002dc4c0:
 STEP(UINT32_C(0x002dc4c0)); /* 10000003 beq zero,zero,002dc4d0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dc4c4));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002dc4d0):UINT32_C(0x002dc4c8));goto dispatch;}
L_002dc4c4:
 STEP(UINT32_C(0x002dc4c4)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dc4c8));goto dispatch;
L_002dc4c8:
 STEP(UINT32_C(0x002dc4c8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dc4cc));goto dispatch;
L_002dc4cc:
 STEP(UINT32_C(0x002dc4cc)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dc4d0));goto dispatch;
L_002dc4d0:
 STEP(UINT32_C(0x002dc4d0)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002dc4d4));goto dispatch;
L_002dc4d4:
 STEP(UINT32_C(0x002dc4d4)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dc4d8));goto dispatch;
L_002dc4d8:
 STEP(UINT32_C(0x002dc4d8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dc4dc));goto dispatch;
L_002dc4dc:
 STEP(UINT32_C(0x002dc4dc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc4e0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002dc4e0:
 STEP(UINT32_C(0x002dc4e0)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dc4e4));goto dispatch;
L_002db950:
 STEP(UINT32_C(0x002db950)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002db954));goto dispatch;
L_002db954:
 STEP(UINT32_C(0x002db954)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002db958));goto dispatch;
L_002db958:
 STEP(UINT32_C(0x002db958)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002db95c));goto dispatch;
L_002db95c:
 STEP(UINT32_C(0x002db95c)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002db960));goto dispatch;
L_002db960:
 STEP(UINT32_C(0x002db960)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002db964));goto dispatch;
L_002db964:
 STEP(UINT32_C(0x002db964)); /* 24512178 addiu s1,v0,8568 */
 set(m,17u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00002178)));target=sx(UINT32_C(0x002db968));goto dispatch;
L_002db968:
 STEP(UINT32_C(0x002db968)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002db96c));goto dispatch;
L_002db96c:
 STEP(UINT32_C(0x002db96c)); /* 00c0282d daddu a1,a2,zero */
 set(m,5u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002db970));goto dispatch;
L_002db970:
 STEP(UINT32_C(0x002db970)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002db974));goto dispatch;
L_002db974:
 STEP(UINT32_C(0x002db974)); /* 0c0b7196 jal 002dc658 */
 set(m,31u,UINT64_C(0x002db97c));STEP(UINT32_C(0x002db978));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002dc658));goto dispatch;
L_002db978:
 STEP(UINT32_C(0x002db978)); /* ae200000 sw zero,0x0(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002db97c));goto dispatch;
L_002db97c:
 STEP(UINT32_C(0x002db97c)); /* 0040182d daddu v1,v0,zero */
 set(m,3u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002db980));goto dispatch;
L_002db980:
 STEP(UINT32_C(0x002db980)); /* 2404ffff addiu a0,zero,-1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002db984));goto dispatch;
L_002db984:
 STEP(UINT32_C(0x002db984)); /* 54640005 bnel v1,a0,002db99c */
 if(lo(m,3u)!=lo(m,4u)){STEP(UINT32_C(0x002db988));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002db99c));}else target=sx(UINT32_C(0x002db98c));goto dispatch;
L_002db988:
 STEP(UINT32_C(0x002db988)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002db98c));goto dispatch;
L_002db98c:
 STEP(UINT32_C(0x002db98c)); /* 8e230000 lw v1,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002db990));goto dispatch;
L_002db990:
 STEP(UINT32_C(0x002db990)); /* 54600001 bnel v1,zero,002db998 */
 if(lo(m,3u)!=lo(m,0u)){STEP(UINT32_C(0x002db994));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002db998));}else target=sx(UINT32_C(0x002db998));goto dispatch;
L_002db994:
 STEP(UINT32_C(0x002db994)); /* ae030000 sw v1,0x0(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002db998));goto dispatch;
L_002db998:
 STEP(UINT32_C(0x002db998)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002db99c));goto dispatch;
L_002db99c:
 STEP(UINT32_C(0x002db99c)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002db9a0));goto dispatch;
L_002db9a0:
 STEP(UINT32_C(0x002db9a0)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002db9a4));goto dispatch;
L_002db9a4:
 STEP(UINT32_C(0x002db9a4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002db9a8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002db9a8:
 STEP(UINT32_C(0x002db9a8)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002db9ac));goto dispatch;
L_002dc658:
 STEP(UINT32_C(0x002dc658)); /* 24022000 addiu v0,zero,8192 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00002000)));target=sx(UINT32_C(0x002dc65c));goto dispatch;
L_002dc65c:
 STEP(UINT32_C(0x002dc65c)); /* fca00048 sd zero,0x48(a1) */
 value64=lo(m,0u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000048),&value64,8u);target=sx(UINT32_C(0x002dc660));goto dispatch;
L_002dc660:
 STEP(UINT32_C(0x002dc660)); /* aca20004 sw v0,0x4(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dc664));goto dispatch;
L_002dc664:
 STEP(UINT32_C(0x002dc664)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc668));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_002dc668:
 STEP(UINT32_C(0x002dc668)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dc66c));goto dispatch;
L_002dc650:
 STEP(UINT32_C(0x002dc650)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc654));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));goto dispatch;
L_002dc654:
 STEP(UINT32_C(0x002dc654)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dc658));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

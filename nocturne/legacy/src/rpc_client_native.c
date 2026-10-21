#include "rpc_client_native.h"
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
uint32_t nocturneRpcClientResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002de6d0):goto L_002de6d0;
 case UINT32_C(0x002de6d4):goto L_002de6d4;
 case UINT32_C(0x002de6d8):goto L_002de6d8;
 case UINT32_C(0x002de6dc):goto L_002de6dc;
 case UINT32_C(0x002de6e0):goto L_002de6e0;
 case UINT32_C(0x002de6e4):goto L_002de6e4;
 case UINT32_C(0x002de6e8):goto L_002de6e8;
 case UINT32_C(0x002de6ec):goto L_002de6ec;
 case UINT32_C(0x002de6f0):goto L_002de6f0;
 case UINT32_C(0x002de6f4):goto L_002de6f4;
 case UINT32_C(0x002de6f8):goto L_002de6f8;
 case UINT32_C(0x002de6fc):goto L_002de6fc;
 case UINT32_C(0x002de700):goto L_002de700;
 case UINT32_C(0x002de704):goto L_002de704;
 case UINT32_C(0x002de708):goto L_002de708;
 case UINT32_C(0x002de70c):goto L_002de70c;
 case UINT32_C(0x002de710):goto L_002de710;
 case UINT32_C(0x002de714):goto L_002de714;
 case UINT32_C(0x002de718):goto L_002de718;
 case UINT32_C(0x002de71c):goto L_002de71c;
 case UINT32_C(0x002de720):goto L_002de720;
 case UINT32_C(0x002de724):goto L_002de724;
 case UINT32_C(0x002de728):goto L_002de728;
 case UINT32_C(0x002de72c):goto L_002de72c;
 case UINT32_C(0x002de730):goto L_002de730;
 case UINT32_C(0x002de734):goto L_002de734;
 case UINT32_C(0x002de738):goto L_002de738;
 case UINT32_C(0x002de73c):goto L_002de73c;
 case UINT32_C(0x002de740):goto L_002de740;
 case UINT32_C(0x002de744):goto L_002de744;
 case UINT32_C(0x002de748):goto L_002de748;
 case UINT32_C(0x002de74c):goto L_002de74c;
 case UINT32_C(0x002de750):goto L_002de750;
 case UINT32_C(0x002de754):goto L_002de754;
 case UINT32_C(0x002de758):goto L_002de758;
 case UINT32_C(0x002de75c):goto L_002de75c;
 case UINT32_C(0x002de760):goto L_002de760;
 case UINT32_C(0x002de764):goto L_002de764;
 case UINT32_C(0x002de768):goto L_002de768;
 case UINT32_C(0x002de76c):goto L_002de76c;
 case UINT32_C(0x002de770):goto L_002de770;
 case UINT32_C(0x002de774):goto L_002de774;
 case UINT32_C(0x002de778):goto L_002de778;
 case UINT32_C(0x002de77c):goto L_002de77c;
 case UINT32_C(0x002de780):goto L_002de780;
 case UINT32_C(0x002de784):goto L_002de784;
 case UINT32_C(0x002de788):goto L_002de788;
 case UINT32_C(0x002de78c):goto L_002de78c;
 case UINT32_C(0x002de790):goto L_002de790;
 case UINT32_C(0x002deb78):goto L_002deb78;
 case UINT32_C(0x002deb7c):goto L_002deb7c;
 case UINT32_C(0x002deb80):goto L_002deb80;
 case UINT32_C(0x002deb84):goto L_002deb84;
 case UINT32_C(0x002deb88):goto L_002deb88;
 case UINT32_C(0x002deb8c):goto L_002deb8c;
 case UINT32_C(0x002deb90):goto L_002deb90;
 case UINT32_C(0x002deb94):goto L_002deb94;
 case UINT32_C(0x002deb98):goto L_002deb98;
 case UINT32_C(0x002deb9c):goto L_002deb9c;
 case UINT32_C(0x002deba0):goto L_002deba0;
 case UINT32_C(0x002deba4):goto L_002deba4;
 case UINT32_C(0x002deba8):goto L_002deba8;
 case UINT32_C(0x002debac):goto L_002debac;
 case UINT32_C(0x002debb0):goto L_002debb0;
 case UINT32_C(0x002debb4):goto L_002debb4;
 case UINT32_C(0x002debb8):goto L_002debb8;
 case UINT32_C(0x002debbc):goto L_002debbc;
 case UINT32_C(0x002debc0):goto L_002debc0;
 case UINT32_C(0x002debc4):goto L_002debc4;
 case UINT32_C(0x002debc8):goto L_002debc8;
 case UINT32_C(0x002debcc):goto L_002debcc;
 case UINT32_C(0x002debd0):goto L_002debd0;
 case UINT32_C(0x002debd4):goto L_002debd4;
 case UINT32_C(0x002debd8):goto L_002debd8;
 case UINT32_C(0x002debdc):goto L_002debdc;
 case UINT32_C(0x002debe0):goto L_002debe0;
 case UINT32_C(0x002debe4):goto L_002debe4;
 case UINT32_C(0x002debe8):goto L_002debe8;
 case UINT32_C(0x002debec):goto L_002debec;
 case UINT32_C(0x002debf0):goto L_002debf0;
 case UINT32_C(0x002debf4):goto L_002debf4;
 case UINT32_C(0x002debf8):goto L_002debf8;
 case UINT32_C(0x002debfc):goto L_002debfc;
 case UINT32_C(0x002dec00):goto L_002dec00;
 case UINT32_C(0x002dec04):goto L_002dec04;
 case UINT32_C(0x002dec08):goto L_002dec08;
 case UINT32_C(0x002dec0c):goto L_002dec0c;
 case UINT32_C(0x002dec10):goto L_002dec10;
 case UINT32_C(0x002dec14):goto L_002dec14;
 case UINT32_C(0x002dec18):goto L_002dec18;
 case UINT32_C(0x002dec1c):goto L_002dec1c;
 case UINT32_C(0x002dec20):goto L_002dec20;
 case UINT32_C(0x002dec24):goto L_002dec24;
 case UINT32_C(0x002dec28):goto L_002dec28;
 case UINT32_C(0x002dec2c):goto L_002dec2c;
 case UINT32_C(0x002dec30):goto L_002dec30;
 case UINT32_C(0x002dec34):goto L_002dec34;
 case UINT32_C(0x002dec38):goto L_002dec38;
 case UINT32_C(0x002dec3c):goto L_002dec3c;
 case UINT32_C(0x002dec40):goto L_002dec40;
 case UINT32_C(0x002dec44):goto L_002dec44;
 case UINT32_C(0x002dec48):goto L_002dec48;
 case UINT32_C(0x002dec4c):goto L_002dec4c;
 case UINT32_C(0x002dec50):goto L_002dec50;
 case UINT32_C(0x002dec54):goto L_002dec54;
 case UINT32_C(0x002dec58):goto L_002dec58;
 case UINT32_C(0x002dec5c):goto L_002dec5c;
 case UINT32_C(0x002dec60):goto L_002dec60;
 case UINT32_C(0x002dec64):goto L_002dec64;
 case UINT32_C(0x002dec68):goto L_002dec68;
 case UINT32_C(0x002dec6c):goto L_002dec6c;
 case UINT32_C(0x002dec70):goto L_002dec70;
 case UINT32_C(0x002dec74):goto L_002dec74;
 case UINT32_C(0x002dec78):goto L_002dec78;
 case UINT32_C(0x002dec7c):goto L_002dec7c;
 case UINT32_C(0x002dec80):goto L_002dec80;
 case UINT32_C(0x002dec84):goto L_002dec84;
 case UINT32_C(0x002dec88):goto L_002dec88;
 case UINT32_C(0x002dec8c):goto L_002dec8c;
 case UINT32_C(0x002dec90):goto L_002dec90;
 case UINT32_C(0x002dec94):goto L_002dec94;
 case UINT32_C(0x002dec98):goto L_002dec98;
 case UINT32_C(0x002dec9c):goto L_002dec9c;
 case UINT32_C(0x002deca0):goto L_002deca0;
 case UINT32_C(0x002deca4):goto L_002deca4;
 case UINT32_C(0x002deca8):goto L_002deca8;
 case UINT32_C(0x002decac):goto L_002decac;
 case UINT32_C(0x002decb0):goto L_002decb0;
 case UINT32_C(0x002decb4):goto L_002decb4;
 case UINT32_C(0x002ded48):goto L_002ded48;
 case UINT32_C(0x002ded4c):goto L_002ded4c;
 case UINT32_C(0x002ded50):goto L_002ded50;
 case UINT32_C(0x002ded54):goto L_002ded54;
 case UINT32_C(0x002ded58):goto L_002ded58;
 case UINT32_C(0x002ded5c):goto L_002ded5c;
 case UINT32_C(0x002ded60):goto L_002ded60;
 case UINT32_C(0x002ded64):goto L_002ded64;
 case UINT32_C(0x002ded68):goto L_002ded68;
 case UINT32_C(0x002ded6c):goto L_002ded6c;
 case UINT32_C(0x002ded70):goto L_002ded70;
 case UINT32_C(0x002ded74):goto L_002ded74;
 case UINT32_C(0x002ded78):goto L_002ded78;
 case UINT32_C(0x002ded7c):goto L_002ded7c;
 case UINT32_C(0x002ded80):goto L_002ded80;
 case UINT32_C(0x002ded84):goto L_002ded84;
 case UINT32_C(0x002ded88):goto L_002ded88;
 case UINT32_C(0x002ded8c):goto L_002ded8c;
 case UINT32_C(0x002ded90):goto L_002ded90;
 case UINT32_C(0x002ded94):goto L_002ded94;
 case UINT32_C(0x002ded98):goto L_002ded98;
 case UINT32_C(0x002ded9c):goto L_002ded9c;
 case UINT32_C(0x002deda0):goto L_002deda0;
 case UINT32_C(0x002deda4):goto L_002deda4;
 case UINT32_C(0x002deda8):goto L_002deda8;
 case UINT32_C(0x002dedac):goto L_002dedac;
 case UINT32_C(0x002dedb0):goto L_002dedb0;
 case UINT32_C(0x002dedb4):goto L_002dedb4;
 case UINT32_C(0x002dedb8):goto L_002dedb8;
 case UINT32_C(0x002dedbc):goto L_002dedbc;
 case UINT32_C(0x002dedc0):goto L_002dedc0;
 case UINT32_C(0x002dedc4):goto L_002dedc4;
 case UINT32_C(0x002dedc8):goto L_002dedc8;
 case UINT32_C(0x002dedcc):goto L_002dedcc;
 case UINT32_C(0x002dedd0):goto L_002dedd0;
 case UINT32_C(0x002dedd4):goto L_002dedd4;
 case UINT32_C(0x002dedd8):goto L_002dedd8;
 case UINT32_C(0x002deddc):goto L_002deddc;
 case UINT32_C(0x002dede0):goto L_002dede0;
 case UINT32_C(0x002dede4):goto L_002dede4;
 case UINT32_C(0x002dede8):goto L_002dede8;
 case UINT32_C(0x002dedec):goto L_002dedec;
 case UINT32_C(0x002dedf0):goto L_002dedf0;
 case UINT32_C(0x002dedf4):goto L_002dedf4;
 case UINT32_C(0x002dedf8):goto L_002dedf8;
 case UINT32_C(0x002dedfc):goto L_002dedfc;
 case UINT32_C(0x002dee00):goto L_002dee00;
 case UINT32_C(0x002dee04):goto L_002dee04;
 case UINT32_C(0x002dee08):goto L_002dee08;
 case UINT32_C(0x002dee0c):goto L_002dee0c;
 case UINT32_C(0x002dee10):goto L_002dee10;
 case UINT32_C(0x002dee14):goto L_002dee14;
 case UINT32_C(0x002dee18):goto L_002dee18;
 case UINT32_C(0x002dee1c):goto L_002dee1c;
 case UINT32_C(0x002dee20):goto L_002dee20;
 case UINT32_C(0x002dee24):goto L_002dee24;
 case UINT32_C(0x002dee28):goto L_002dee28;
 case UINT32_C(0x002dee2c):goto L_002dee2c;
 case UINT32_C(0x002dee30):goto L_002dee30;
 case UINT32_C(0x002dee34):goto L_002dee34;
 case UINT32_C(0x002dee38):goto L_002dee38;
 case UINT32_C(0x002dee3c):goto L_002dee3c;
 case UINT32_C(0x002dee40):goto L_002dee40;
 case UINT32_C(0x002dee44):goto L_002dee44;
 case UINT32_C(0x002dee48):goto L_002dee48;
 case UINT32_C(0x002dee4c):goto L_002dee4c;
 case UINT32_C(0x002dee50):goto L_002dee50;
 case UINT32_C(0x002dee54):goto L_002dee54;
 case UINT32_C(0x002dee58):goto L_002dee58;
 case UINT32_C(0x002dee5c):goto L_002dee5c;
 case UINT32_C(0x002dee60):goto L_002dee60;
 case UINT32_C(0x002dee64):goto L_002dee64;
 case UINT32_C(0x002dee68):goto L_002dee68;
 case UINT32_C(0x002dee6c):goto L_002dee6c;
 case UINT32_C(0x002dee70):goto L_002dee70;
 case UINT32_C(0x002dee74):goto L_002dee74;
 case UINT32_C(0x002dee78):goto L_002dee78;
 case UINT32_C(0x002dee7c):goto L_002dee7c;
 case UINT32_C(0x002dee80):goto L_002dee80;
 case UINT32_C(0x002dee84):goto L_002dee84;
 case UINT32_C(0x002dee88):goto L_002dee88;
 case UINT32_C(0x002dee8c):goto L_002dee8c;
 case UINT32_C(0x002dee90):goto L_002dee90;
 case UINT32_C(0x002dee94):goto L_002dee94;
 case UINT32_C(0x002dee98):goto L_002dee98;
 case UINT32_C(0x002dee9c):goto L_002dee9c;
 case UINT32_C(0x002deea0):goto L_002deea0;
 case UINT32_C(0x002deea4):goto L_002deea4;
 case UINT32_C(0x002deea8):goto L_002deea8;
 case UINT32_C(0x002deeac):goto L_002deeac;
 case UINT32_C(0x002deeb0):goto L_002deeb0;
 case UINT32_C(0x002deeb4):goto L_002deeb4;
 case UINT32_C(0x002deeb8):goto L_002deeb8;
 case UINT32_C(0x002deebc):goto L_002deebc;
 case UINT32_C(0x002deec0):goto L_002deec0;
 case UINT32_C(0x002deec4):goto L_002deec4;
 case UINT32_C(0x002deec8):goto L_002deec8;
 case UINT32_C(0x002deecc):goto L_002deecc;
 case UINT32_C(0x002deed0):goto L_002deed0;
 case UINT32_C(0x002deed4):goto L_002deed4;
 case UINT32_C(0x002deed8):goto L_002deed8;
 case UINT32_C(0x002deedc):goto L_002deedc;
 case UINT32_C(0x002deee0):goto L_002deee0;
 case UINT32_C(0x002deee4):goto L_002deee4;
 case UINT32_C(0x002deee8):goto L_002deee8;
 case UINT32_C(0x002deeec):goto L_002deeec;
 case UINT32_C(0x002deef0):goto L_002deef0;
 case UINT32_C(0x002deef4):goto L_002deef4;
 case UINT32_C(0x002deef8):goto L_002deef8;
 case UINT32_C(0x002deefc):goto L_002deefc;
 case UINT32_C(0x002def00):goto L_002def00;
 case UINT32_C(0x002def04):goto L_002def04;
 case UINT32_C(0x002def08):goto L_002def08;
 case UINT32_C(0x002def0c):goto L_002def0c;
 case UINT32_C(0x002def10):goto L_002def10;
 case UINT32_C(0x002def14):goto L_002def14;
 case UINT32_C(0x002def18):goto L_002def18;
 case UINT32_C(0x002def1c):goto L_002def1c;
 case UINT32_C(0x002def20):goto L_002def20;
 case UINT32_C(0x002def24):goto L_002def24;
 case UINT32_C(0x002def28):goto L_002def28;
 case UINT32_C(0x002def2c):goto L_002def2c;
 case UINT32_C(0x002def30):goto L_002def30;
 case UINT32_C(0x002e2b10):goto L_002e2b10;
 case UINT32_C(0x002e2b14):goto L_002e2b14;
 case UINT32_C(0x002e2b18):goto L_002e2b18;
 case UINT32_C(0x002e2b1c):goto L_002e2b1c;
 case UINT32_C(0x002e2b20):goto L_002e2b20;
 case UINT32_C(0x002e2b24):goto L_002e2b24;
 case UINT32_C(0x002e2b28):goto L_002e2b28;
 case UINT32_C(0x002e2b2c):goto L_002e2b2c;
 case UINT32_C(0x002e2b30):goto L_002e2b30;
 case UINT32_C(0x002e2b34):goto L_002e2b34;
 case UINT32_C(0x002e2b38):goto L_002e2b38;
 case UINT32_C(0x002e2b3c):goto L_002e2b3c;
 case UINT32_C(0x002e2b40):goto L_002e2b40;
 case UINT32_C(0x002e2b44):goto L_002e2b44;
 case UINT32_C(0x002e2b48):goto L_002e2b48;
 case UINT32_C(0x002e2b4c):goto L_002e2b4c;
 case UINT32_C(0x002e2b50):goto L_002e2b50;
 case UINT32_C(0x002e2b54):goto L_002e2b54;
 case UINT32_C(0x002e2b58):goto L_002e2b58;
 case UINT32_C(0x002e2b5c):goto L_002e2b5c;
 case UINT32_C(0x002e2b60):goto L_002e2b60;
 case UINT32_C(0x002e2b64):goto L_002e2b64;
 case UINT32_C(0x002e2b68):goto L_002e2b68;
 case UINT32_C(0x002e2b6c):goto L_002e2b6c;
 case UINT32_C(0x002e2b70):goto L_002e2b70;
 case UINT32_C(0x002e2b74):goto L_002e2b74;
 case UINT32_C(0x002e2b78):goto L_002e2b78;
 case UINT32_C(0x002e2b7c):goto L_002e2b7c;
 case UINT32_C(0x002e2b80):goto L_002e2b80;
 case UINT32_C(0x002e2b84):goto L_002e2b84;
 case UINT32_C(0x002e2b88):goto L_002e2b88;
 case UINT32_C(0x002e2b8c):goto L_002e2b8c;
 case UINT32_C(0x002e2b90):goto L_002e2b90;
 case UINT32_C(0x002e2b94):goto L_002e2b94;
 case UINT32_C(0x002e3060):goto L_002e3060;
 case UINT32_C(0x002e3064):goto L_002e3064;
 case UINT32_C(0x002e3068):goto L_002e3068;
 case UINT32_C(0x002e306c):goto L_002e306c;
 case UINT32_C(0x002e3070):goto L_002e3070;
 case UINT32_C(0x002e3074):goto L_002e3074;
 case UINT32_C(0x002e3078):goto L_002e3078;
 case UINT32_C(0x002e307c):goto L_002e307c;
 case UINT32_C(0x002e3080):goto L_002e3080;
 case UINT32_C(0x002e3084):goto L_002e3084;
 case UINT32_C(0x002e3088):goto L_002e3088;
 case UINT32_C(0x002e308c):goto L_002e308c;
 case UINT32_C(0x002e3090):goto L_002e3090;
 case UINT32_C(0x002e3094):goto L_002e3094;
 case UINT32_C(0x002e3098):goto L_002e3098;
 case UINT32_C(0x002e309c):goto L_002e309c;
 case UINT32_C(0x002e30a0):goto L_002e30a0;
 case UINT32_C(0x002e30a4):goto L_002e30a4;
 case UINT32_C(0x002e30a8):goto L_002e30a8;
 case UINT32_C(0x002e30ac):goto L_002e30ac;
 case UINT32_C(0x002e30b0):goto L_002e30b0;
 case UINT32_C(0x002e30b4):goto L_002e30b4;
 case UINT32_C(0x002e30b8):goto L_002e30b8;
 case UINT32_C(0x002e30bc):goto L_002e30bc;
 case UINT32_C(0x002e30c0):goto L_002e30c0;
 case UINT32_C(0x002e30c4):goto L_002e30c4;
 case UINT32_C(0x002e30c8):goto L_002e30c8;
 case UINT32_C(0x002e30cc):goto L_002e30cc;
 case UINT32_C(0x002e30d0):goto L_002e30d0;
 case UINT32_C(0x002e30d4):goto L_002e30d4;
 case UINT32_C(0x002e30d8):goto L_002e30d8;
 case UINT32_C(0x002e30dc):goto L_002e30dc;
 case UINT32_C(0x002e30e0):goto L_002e30e0;
 case UINT32_C(0x002e30e4):goto L_002e30e4;
 case UINT32_C(0x002e30e8):goto L_002e30e8;
 case UINT32_C(0x002e30ec):goto L_002e30ec;
 case UINT32_C(0x002e30f0):goto L_002e30f0;
 case UINT32_C(0x002e30f4):goto L_002e30f4;
 case UINT32_C(0x002e30f8):goto L_002e30f8;
 case UINT32_C(0x002e30fc):goto L_002e30fc;
 case UINT32_C(0x002e3100):goto L_002e3100;
 case UINT32_C(0x002e3104):goto L_002e3104;
 case UINT32_C(0x002e3108):goto L_002e3108;
 case UINT32_C(0x002e310c):goto L_002e310c;
 case UINT32_C(0x002e3110):goto L_002e3110;
 case UINT32_C(0x002e3114):goto L_002e3114;
 case UINT32_C(0x002e3118):goto L_002e3118;
 case UINT32_C(0x002e311c):goto L_002e311c;
 case UINT32_C(0x002e3120):goto L_002e3120;
 case UINT32_C(0x002e3124):goto L_002e3124;
 case UINT32_C(0x002e3128):goto L_002e3128;
 case UINT32_C(0x002e312c):goto L_002e312c;
 case UINT32_C(0x002e3130):goto L_002e3130;
 case UINT32_C(0x002e3134):goto L_002e3134;
 case UINT32_C(0x002e3138):goto L_002e3138;
 case UINT32_C(0x002e313c):goto L_002e313c;
 case UINT32_C(0x002e3140):goto L_002e3140;
 case UINT32_C(0x002e3144):goto L_002e3144;
 case UINT32_C(0x002e3148):goto L_002e3148;
 case UINT32_C(0x002e314c):goto L_002e314c;
 case UINT32_C(0x002e3150):goto L_002e3150;
 case UINT32_C(0x002e3154):goto L_002e3154;
 case UINT32_C(0x002e3158):goto L_002e3158;
 case UINT32_C(0x002e315c):goto L_002e315c;
 case UINT32_C(0x002dbeb0):goto L_002dbeb0;
 case UINT32_C(0x002dbeb4):goto L_002dbeb4;
 case UINT32_C(0x002dbeb8):goto L_002dbeb8;
 case UINT32_C(0x002dbebc):goto L_002dbebc;
 case UINT32_C(0x002dbee0):goto L_002dbee0;
 case UINT32_C(0x002dbee4):goto L_002dbee4;
 case UINT32_C(0x002dbee8):goto L_002dbee8;
 case UINT32_C(0x002dbeec):goto L_002dbeec;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002de6d0:
 STEP(UINT32_C(0x002de6d0)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002de6d4));goto dispatch;
L_002de6d4:
 STEP(UINT32_C(0x002de6d4)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002de6d8));goto dispatch;
L_002de6d8:
 STEP(UINT32_C(0x002de6d8)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002de6dc));goto dispatch;
L_002de6dc:
 STEP(UINT32_C(0x002de6dc)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002de6e0));goto dispatch;
L_002de6e0:
 STEP(UINT32_C(0x002de6e0)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002de6e8));STEP(UINT32_C(0x002de6e4));set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002de6e4:
 STEP(UINT32_C(0x002de6e4)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002de6e8));goto dispatch;
L_002de6e8:
 STEP(UINT32_C(0x002de6e8)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de6ec));goto dispatch;
L_002de6ec:
 STEP(UINT32_C(0x002de6ec)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de6f0));goto dispatch;
L_002de6f0:
 STEP(UINT32_C(0x002de6f0)); /* 18800019 blez a0,zero,002de758 */
 {int taken=((int64_t)lo(m,4u)<=0);STEP(UINT32_C(0x002de6f4));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,16u,sx(value32));target=sx(taken?UINT32_C(0x002de758):UINT32_C(0x002de6f8));goto dispatch;}
L_002de6f4:
 STEP(UINT32_C(0x002de6f4)); /* 8e300004 lw s0,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x002de6f8));goto dispatch;
L_002de6f8:
 STEP(UINT32_C(0x002de6f8)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de6fc));goto dispatch;
L_002de6fc:
 STEP(UINT32_C(0x002de6fc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de700));goto dispatch;
L_002de700:
 STEP(UINT32_C(0x002de700)); /* 8e020010 lw v0,0x10(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de704));goto dispatch;
L_002de704:
 STEP(UINT32_C(0x002de704)); /* 30420001 andi v0,v0,0x1 */
 set(m,2u,lo(m,2u) & UINT64_C(0x1));target=sx(UINT32_C(0x002de708));goto dispatch;
L_002de708:
 STEP(UINT32_C(0x002de708)); /* 54400010 bnel v0,zero,002de74c */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002de70c));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de74c));}else target=sx(UINT32_C(0x002de710));goto dispatch;
L_002de70c:
 STEP(UINT32_C(0x002de70c)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de710));goto dispatch;
L_002de710:
 STEP(UINT32_C(0x002de710)); /* 00031400 sll v0,v1,16 */
 set(m,2u,sx((uint32_t)lo(m,3u)<<16u));target=sx(UINT32_C(0x002de714));goto dispatch;
L_002de714:
 STEP(UINT32_C(0x002de714)); /* 34420005 ori v0,v0,0x5 */
 set(m,2u,lo(m,2u) | UINT64_C(0x5));target=sx(UINT32_C(0x002de718));goto dispatch;
L_002de718:
 STEP(UINT32_C(0x002de718)); /* ae020010 sw v0,0x10(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002de71c));goto dispatch;
L_002de71c:
 STEP(UINT32_C(0x002de71c)); /* 8e220000 lw v0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de720));goto dispatch;
L_002de720:
 STEP(UINT32_C(0x002de720)); /* 24430001 addiu v1,v0,1 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de724));goto dispatch;
L_002de724:
 STEP(UINT32_C(0x002de724)); /* 14650004 bne v1,a1,002de738 */
 {int taken=(lo(m,3u)!=lo(m,5u));STEP(UINT32_C(0x002de728));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x002de738):UINT32_C(0x002de72c));goto dispatch;}
L_002de728:
 STEP(UINT32_C(0x002de728)); /* ae230000 sw v1,0x0(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de72c));goto dispatch;
L_002de72c:
 STEP(UINT32_C(0x002de72c)); /* 24420002 addiu v0,v0,2 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002de730));goto dispatch;
L_002de730:
 STEP(UINT32_C(0x002de730)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de734));goto dispatch;
L_002de734:
 STEP(UINT32_C(0x002de734)); /* ae220000 sw v0,0x0(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de738));goto dispatch;
L_002de738:
 STEP(UINT32_C(0x002de738)); /* ae100014 sw s0,0x14(s0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002de73c));goto dispatch;
L_002de73c:
 STEP(UINT32_C(0x002de73c)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002de744));STEP(UINT32_C(0x002de740));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002de740:
 STEP(UINT32_C(0x002de740)); /* ae030018 sw v1,0x18(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002de744));goto dispatch;
L_002de744:
 STEP(UINT32_C(0x002de744)); /* 10000007 beq zero,zero,002de764 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de748));set(m,2u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002de764):UINT32_C(0x002de74c));goto dispatch;}
L_002de748:
 STEP(UINT32_C(0x002de748)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de74c));goto dispatch;
L_002de74c:
 STEP(UINT32_C(0x002de74c)); /* 0064102a slt v0,v1,a0 */
 set(m,2u,((int64_t)lo(m,3u)<(int64_t)lo(m,4u)));target=sx(UINT32_C(0x002de750));goto dispatch;
L_002de750:
 STEP(UINT32_C(0x002de750)); /* 1440ffeb bne v0,zero,002de700 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002de754));set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000040)));target=sx(taken?UINT32_C(0x002de700):UINT32_C(0x002de758));goto dispatch;}
L_002de754:
 STEP(UINT32_C(0x002de754)); /* 26100040 addiu s0,s0,64 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de758));goto dispatch;
L_002de758:
 STEP(UINT32_C(0x002de758)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002de760));STEP(UINT32_C(0x002de75c));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002de75c:
 STEP(UINT32_C(0x002de75c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de760));goto dispatch;
L_002de760:
 STEP(UINT32_C(0x002de760)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de764));goto dispatch;
L_002de764:
 STEP(UINT32_C(0x002de764)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de768));goto dispatch;
L_002de768:
 STEP(UINT32_C(0x002de768)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002de76c));goto dispatch;
L_002de76c:
 STEP(UINT32_C(0x002de76c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de770));goto dispatch;
L_002de770:
 STEP(UINT32_C(0x002de770)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de774));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002de774:
 STEP(UINT32_C(0x002de774)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002de778));goto dispatch;
L_002de778:
 STEP(UINT32_C(0x002de778)); /* 8c830010 lw v1,0x10(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002de77c));goto dispatch;
L_002de77c:
 STEP(UINT32_C(0x002de77c)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002de780));goto dispatch;
L_002de780:
 STEP(UINT32_C(0x002de780)); /* 3442fffe ori v0,v0,0xfffe */
 set(m,2u,lo(m,2u) | UINT64_C(0xfffe));target=sx(UINT32_C(0x002de784));goto dispatch;
L_002de784:
 STEP(UINT32_C(0x002de784)); /* ac800018 sw zero,0x18(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002de788));goto dispatch;
L_002de788:
 STEP(UINT32_C(0x002de788)); /* 00621824 and v1,v1,v0 */
 set(m,3u,lo(m,3u)&lo(m,2u));target=sx(UINT32_C(0x002de78c));goto dispatch;
L_002de78c:
 STEP(UINT32_C(0x002de78c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de790));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);goto dispatch;
L_002de790:
 STEP(UINT32_C(0x002de790)); /* ac830010 sw v1,0x10(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002de794));goto dispatch;
L_002deb78:
 STEP(UINT32_C(0x002deb78)); /* 27bdff90 addiu sp,sp,-112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff90)));target=sx(UINT32_C(0x002deb7c));goto dispatch;
L_002deb7c:
 STEP(UINT32_C(0x002deb7c)); /* ffb10030 sd s1,0x30(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002deb80));goto dispatch;
L_002deb80:
 STEP(UINT32_C(0x002deb80)); /* ffb30050 sd s3,0x50(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002deb84));goto dispatch;
L_002deb84:
 STEP(UINT32_C(0x002deb84)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002deb88));goto dispatch;
L_002deb88:
 STEP(UINT32_C(0x002deb88)); /* ffb20040 sd s2,0x40(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002deb8c));goto dispatch;
L_002deb8c:
 STEP(UINT32_C(0x002deb8c)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002deb90));goto dispatch;
L_002deb90:
 STEP(UINT32_C(0x002deb90)); /* ffb00020 sd s0,0x20(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002deb94));goto dispatch;
L_002deb94:
 STEP(UINT32_C(0x002deb94)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002deb98));goto dispatch;
L_002deb98:
 STEP(UINT32_C(0x002deb98)); /* ffbf0060 sd ra,0x60(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002deb9c));goto dispatch;
L_002deb9c:
 STEP(UINT32_C(0x002deb9c)); /* 00c0902d daddu s2,a2,zero */
 set(m,18u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002deba0));goto dispatch;
L_002deba0:
 STEP(UINT32_C(0x002deba0)); /* ae200010 sw zero,0x10(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002deba4));goto dispatch;
L_002deba4:
 STEP(UINT32_C(0x002deba4)); /* 2484d440 addiu a0,a0,-11200 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffd440)));target=sx(UINT32_C(0x002deba8));goto dispatch;
L_002deba8:
 STEP(UINT32_C(0x002deba8)); /* 0c0b79b4 jal 002de6d0 */
 set(m,31u,UINT64_C(0x002debb0));STEP(UINT32_C(0x002debac));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002de6d0));goto dispatch;
L_002debac:
 STEP(UINT32_C(0x002debac)); /* ae200024 sw zero,0x24(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002debb0));goto dispatch;
L_002debb0:
 STEP(UINT32_C(0x002debb0)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002debb4));goto dispatch;
L_002debb4:
 STEP(UINT32_C(0x002debb4)); /* 12000039 beq s0,zero,002dec9c */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002debb8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002dec9c):UINT32_C(0x002debbc));goto dispatch;}
L_002debb8:
 STEP(UINT32_C(0x002debb8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002debbc));goto dispatch;
L_002debbc:
 STEP(UINT32_C(0x002debbc)); /* 8e020018 lw v0,0x18(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002debc0));goto dispatch;
L_002debc0:
 STEP(UINT32_C(0x002debc0)); /* 32430001 andi v1,s2,0x1 */
 set(m,3u,lo(m,18u) & UINT64_C(0x1));target=sx(UINT32_C(0x002debc4));goto dispatch;
L_002debc4:
 STEP(UINT32_C(0x002debc4)); /* ae300000 sw s0,0x0(s1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002debc8));goto dispatch;
L_002debc8:
 STEP(UINT32_C(0x002debc8)); /* ae220004 sw v0,0x4(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002debcc));goto dispatch;
L_002debcc:
 STEP(UINT32_C(0x002debcc)); /* ae130020 sw s3,0x20(s0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002debd0));goto dispatch;
L_002debd0:
 STEP(UINT32_C(0x002debd0)); /* ae100014 sw s0,0x14(s0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002debd4));goto dispatch;
L_002debd4:
 STEP(UINT32_C(0x002debd4)); /* 14600022 bne v1,zero,002dec60 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002debd8));value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);target=sx(taken?UINT32_C(0x002dec60):UINT32_C(0x002debdc));goto dispatch;}
L_002debd8:
 STEP(UINT32_C(0x002debd8)); /* ae11001c sw s1,0x1c(s0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002debdc));goto dispatch;
L_002debdc:
 STEP(UINT32_C(0x002debdc)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002debe0));goto dispatch;
L_002debe0:
 STEP(UINT32_C(0x002debe0)); /* afa00008 sw zero,0x8(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002debe4));goto dispatch;
L_002debe4:
 STEP(UINT32_C(0x002debe4)); /* afa20004 sw v0,0x4(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002debe8));goto dispatch;
L_002debe8:
 STEP(UINT32_C(0x002debe8)); /* 0c0b6fa8 jal 002dbea0 */
 set(m,31u,UINT64_C(0x002debf0));STEP(UINT32_C(0x002debec));set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002dbea0));goto dispatch;
L_002debec:
 STEP(UINT32_C(0x002debec)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002debf0));goto dispatch;
L_002debf0:
 STEP(UINT32_C(0x002debf0)); /* 04410005 regimm1 v0,002dec08 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002debf4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002dec08):UINT32_C(0x002debf8));goto dispatch;}
L_002debf4:
 STEP(UINT32_C(0x002debf4)); /* ae220008 sw v0,0x8(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002debf8));goto dispatch;
L_002debf8:
 STEP(UINT32_C(0x002debf8)); /* 0c0b79de jal 002de778 */
 set(m,31u,UINT64_C(0x002dec00));STEP(UINT32_C(0x002debfc));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de778));goto dispatch;
L_002debfc:
 STEP(UINT32_C(0x002debfc)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002dec00));goto dispatch;
L_002dec00:
 STEP(UINT32_C(0x002dec00)); /* 10000026 beq zero,zero,002dec9c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dec04));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffd)));target=sx(taken?UINT32_C(0x002dec9c):UINT32_C(0x002dec08));goto dispatch;}
L_002dec04:
 STEP(UINT32_C(0x002dec04)); /* 2402fffd addiu v0,zero,-3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffd)));target=sx(UINT32_C(0x002dec08));goto dispatch;
L_002dec08:
 STEP(UINT32_C(0x002dec08)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002dec0c));goto dispatch;
L_002dec0c:
 STEP(UINT32_C(0x002dec0c)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002dec10));goto dispatch;
L_002dec10:
 STEP(UINT32_C(0x002dec10)); /* 34840009 ori a0,a0,0x9 */
 set(m,4u,lo(m,4u) | UINT64_C(0x9));target=sx(UINT32_C(0x002dec14));goto dispatch;
L_002dec14:
 STEP(UINT32_C(0x002dec14)); /* 24060040 addiu a2,zero,64 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dec18));goto dispatch;
L_002dec18:
 STEP(UINT32_C(0x002dec18)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dec1c));goto dispatch;
L_002dec1c:
 STEP(UINT32_C(0x002dec1c)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dec20));goto dispatch;
L_002dec20:
 STEP(UINT32_C(0x002dec20)); /* 0c0b78ac jal 002de2b0 */
 set(m,31u,UINT64_C(0x002dec28));STEP(UINT32_C(0x002dec24));set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002dec24:
 STEP(UINT32_C(0x002dec24)); /* 0000482d daddu t1,zero,zero */
 set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dec28));goto dispatch;
L_002dec28:
 STEP(UINT32_C(0x002dec28)); /* 14400007 bne v0,zero,002dec48 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dec2c));/* nop */target=sx(taken?UINT32_C(0x002dec48):UINT32_C(0x002dec30));goto dispatch;}
L_002dec2c:
 STEP(UINT32_C(0x002dec2c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dec30));goto dispatch;
L_002dec30:
 STEP(UINT32_C(0x002dec30)); /* 0c0b79de jal 002de778 */
 set(m,31u,UINT64_C(0x002dec38));STEP(UINT32_C(0x002dec34));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de778));goto dispatch;
L_002dec34:
 STEP(UINT32_C(0x002dec34)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002dec38));goto dispatch;
L_002dec38:
 STEP(UINT32_C(0x002dec38)); /* 0c0b6fac jal 002dbeb0 */
 set(m,31u,UINT64_C(0x002dec40));STEP(UINT32_C(0x002dec3c));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbeb0));goto dispatch;
L_002dec3c:
 STEP(UINT32_C(0x002dec3c)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dec40));goto dispatch;
L_002dec40:
 STEP(UINT32_C(0x002dec40)); /* 10000016 beq zero,zero,002dec9c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dec44));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(taken?UINT32_C(0x002dec9c):UINT32_C(0x002dec48));goto dispatch;}
L_002dec44:
 STEP(UINT32_C(0x002dec44)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x002dec48));goto dispatch;
L_002dec48:
 STEP(UINT32_C(0x002dec48)); /* 0c0b6fb8 jal 002dbee0 */
 set(m,31u,UINT64_C(0x002dec50));STEP(UINT32_C(0x002dec4c));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbee0));goto dispatch;
L_002dec4c:
 STEP(UINT32_C(0x002dec4c)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dec50));goto dispatch;
L_002dec50:
 STEP(UINT32_C(0x002dec50)); /* 0c0b6fac jal 002dbeb0 */
 set(m,31u,UINT64_C(0x002dec58));STEP(UINT32_C(0x002dec54));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbeb0));goto dispatch;
L_002dec54:
 STEP(UINT32_C(0x002dec54)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dec58));goto dispatch;
L_002dec58:
 STEP(UINT32_C(0x002dec58)); /* 10000010 beq zero,zero,002dec9c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dec5c));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dec9c):UINT32_C(0x002dec60));goto dispatch;}
L_002dec5c:
 STEP(UINT32_C(0x002dec5c)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dec60));goto dispatch;
L_002dec60:
 STEP(UINT32_C(0x002dec60)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dec64));goto dispatch;
L_002dec64:
 STEP(UINT32_C(0x002dec64)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002dec68));goto dispatch;
L_002dec68:
 STEP(UINT32_C(0x002dec68)); /* ae220008 sw v0,0x8(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dec6c));goto dispatch;
L_002dec6c:
 STEP(UINT32_C(0x002dec6c)); /* 34840009 ori a0,a0,0x9 */
 set(m,4u,lo(m,4u) | UINT64_C(0x9));target=sx(UINT32_C(0x002dec70));goto dispatch;
L_002dec70:
 STEP(UINT32_C(0x002dec70)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002dec74));goto dispatch;
L_002dec74:
 STEP(UINT32_C(0x002dec74)); /* 24060040 addiu a2,zero,64 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dec78));goto dispatch;
L_002dec78:
 STEP(UINT32_C(0x002dec78)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dec7c));goto dispatch;
L_002dec7c:
 STEP(UINT32_C(0x002dec7c)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dec80));goto dispatch;
L_002dec80:
 STEP(UINT32_C(0x002dec80)); /* 0c0b78ac jal 002de2b0 */
 set(m,31u,UINT64_C(0x002dec88));STEP(UINT32_C(0x002dec84));set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002dec84:
 STEP(UINT32_C(0x002dec84)); /* 0000482d daddu t1,zero,zero */
 set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dec88));goto dispatch;
L_002dec88:
 STEP(UINT32_C(0x002dec88)); /* 14400004 bne v0,zero,002dec9c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dec8c));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dec9c):UINT32_C(0x002dec90));goto dispatch;}
L_002dec8c:
 STEP(UINT32_C(0x002dec8c)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dec90));goto dispatch;
L_002dec90:
 STEP(UINT32_C(0x002dec90)); /* 0c0b79de jal 002de778 */
 set(m,31u,UINT64_C(0x002dec98));STEP(UINT32_C(0x002dec94));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de778));goto dispatch;
L_002dec94:
 STEP(UINT32_C(0x002dec94)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002dec98));goto dispatch;
L_002dec98:
 STEP(UINT32_C(0x002dec98)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x002dec9c));goto dispatch;
L_002dec9c:
 STEP(UINT32_C(0x002dec9c)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002deca0));goto dispatch;
L_002deca0:
 STEP(UINT32_C(0x002deca0)); /* dfb30050 ld s3,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002deca4));goto dispatch;
L_002deca4:
 STEP(UINT32_C(0x002deca4)); /* dfb20040 ld s2,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002deca8));goto dispatch;
L_002deca8:
 STEP(UINT32_C(0x002deca8)); /* dfb10030 ld s1,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002decac));goto dispatch;
L_002decac:
 STEP(UINT32_C(0x002decac)); /* dfb00020 ld s0,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002decb0));goto dispatch;
L_002decb0:
 STEP(UINT32_C(0x002decb0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002decb4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));goto dispatch;
L_002decb4:
 STEP(UINT32_C(0x002decb4)); /* 27bd0070 addiu sp,sp,112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x002decb8));goto dispatch;
L_002ded48:
 STEP(UINT32_C(0x002ded48)); /* 27bdff40 addiu sp,sp,-192 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff40)));target=sx(UINT32_C(0x002ded4c));goto dispatch;
L_002ded4c:
 STEP(UINT32_C(0x002ded4c)); /* ffb10030 sd s1,0x30(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ded50));goto dispatch;
L_002ded50:
 STEP(UINT32_C(0x002ded50)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ded54));goto dispatch;
L_002ded54:
 STEP(UINT32_C(0x002ded54)); /* ffbe00a0 sd s8,0xa0(sp) */
 value64=lo(m,30u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),&value64,8u);target=sx(UINT32_C(0x002ded58));goto dispatch;
L_002ded58:
 STEP(UINT32_C(0x002ded58)); /* ffb70090 sd s7,0x90(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x002ded5c));goto dispatch;
L_002ded5c:
 STEP(UINT32_C(0x002ded5c)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ded60));goto dispatch;
L_002ded60:
 STEP(UINT32_C(0x002ded60)); /* ffb60080 sd s6,0x80(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002ded64));goto dispatch;
L_002ded64:
 STEP(UINT32_C(0x002ded64)); /* 00c0f02d daddu s8,a2,zero */
 set(m,30u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002ded68));goto dispatch;
L_002ded68:
 STEP(UINT32_C(0x002ded68)); /* ffb50070 sd s5,0x70(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002ded6c));goto dispatch;
L_002ded6c:
 STEP(UINT32_C(0x002ded6c)); /* 00a0b02d daddu s6,a1,zero */
 set(m,22u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002ded70));goto dispatch;
L_002ded70:
 STEP(UINT32_C(0x002ded70)); /* ffb40060 sd s4,0x60(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002ded74));goto dispatch;
L_002ded74:
 STEP(UINT32_C(0x002ded74)); /* 00e0a82d daddu s5,a3,zero */
 set(m,21u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002ded78));goto dispatch;
L_002ded78:
 STEP(UINT32_C(0x002ded78)); /* ffb30050 sd s3,0x50(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002ded7c));goto dispatch;
L_002ded7c:
 STEP(UINT32_C(0x002ded7c)); /* 0120a02d daddu s4,t1,zero */
 set(m,20u,lo(m,9u)+lo(m,0u));target=sx(UINT32_C(0x002ded80));goto dispatch;
L_002ded80:
 STEP(UINT32_C(0x002ded80)); /* ffb20040 sd s2,0x40(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ded84));goto dispatch;
L_002ded84:
 STEP(UINT32_C(0x002ded84)); /* 0140982d daddu s3,t2,zero */
 set(m,19u,lo(m,10u)+lo(m,0u));target=sx(UINT32_C(0x002ded88));goto dispatch;
L_002ded88:
 STEP(UINT32_C(0x002ded88)); /* ffb00020 sd s0,0x20(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ded8c));goto dispatch;
L_002ded8c:
 STEP(UINT32_C(0x002ded8c)); /* 0100902d daddu s2,t0,zero */
 set(m,18u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002ded90));goto dispatch;
L_002ded90:
 STEP(UINT32_C(0x002ded90)); /* ffbf00b0 sd ra,0xb0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000000b0),&value64,8u);target=sx(UINT32_C(0x002ded94));goto dispatch;
L_002ded94:
 STEP(UINT32_C(0x002ded94)); /* 0160b82d daddu s7,t3,zero */
 set(m,23u,lo(m,11u)+lo(m,0u));target=sx(UINT32_C(0x002ded98));goto dispatch;
L_002ded98:
 STEP(UINT32_C(0x002ded98)); /* 0c0b79b4 jal 002de6d0 */
 set(m,31u,UINT64_C(0x002deda0));STEP(UINT32_C(0x002ded9c));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffd440)));target=sx(UINT32_C(0x002de6d0));goto dispatch;
L_002ded9c:
 STEP(UINT32_C(0x002ded9c)); /* 2484d440 addiu a0,a0,-11200 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffd440)));target=sx(UINT32_C(0x002deda0));goto dispatch;
L_002deda0:
 STEP(UINT32_C(0x002deda0)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002deda4));goto dispatch;
L_002deda4:
 STEP(UINT32_C(0x002deda4)); /* 12000057 beq s0,zero,002def04 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002deda8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002def04):UINT32_C(0x002dedac));goto dispatch;}
L_002deda8:
 STEP(UINT32_C(0x002deda8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dedac));goto dispatch;
L_002dedac:
 STEP(UINT32_C(0x002dedac)); /* 8fa200c0 lw v0,0xc0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000000c0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dedb0));goto dispatch;
L_002dedb0:
 STEP(UINT32_C(0x002dedb0)); /* 33c40002 andi a0,s8,0x2 */
 set(m,4u,lo(m,30u) & UINT64_C(0x2));target=sx(UINT32_C(0x002dedb4));goto dispatch;
L_002dedb4:
 STEP(UINT32_C(0x002dedb4)); /* 8e030018 lw v1,0x18(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dedb8));goto dispatch;
L_002dedb8:
 STEP(UINT32_C(0x002dedb8)); /* ae220020 sw v0,0x20(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002dedbc));goto dispatch;
L_002dedbc:
 STEP(UINT32_C(0x002dedbc)); /* ae300000 sw s0,0x0(s1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002dedc0));goto dispatch;
L_002dedc0:
 STEP(UINT32_C(0x002dedc0)); /* ae230004 sw v1,0x4(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dedc4));goto dispatch;
L_002dedc4:
 STEP(UINT32_C(0x002dedc4)); /* ae37001c sw s7,0x1c(s1) */
 value32=(uint32_t)lo(m,23u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002dedc8));goto dispatch;
L_002dedc8:
 STEP(UINT32_C(0x002dedc8)); /* ae160020 sw s6,0x20(s0) */
 value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002dedcc));goto dispatch;
L_002dedcc:
 STEP(UINT32_C(0x002dedcc)); /* ae120024 sw s2,0x24(s0) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002dedd0));goto dispatch;
L_002dedd0:
 STEP(UINT32_C(0x002dedd0)); /* ae140028 sw s4,0x28(s0) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x002dedd4));goto dispatch;
L_002dedd4:
 STEP(UINT32_C(0x002dedd4)); /* ae13002c sw s3,0x2c(s0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x002dedd8));goto dispatch;
L_002dedd8:
 STEP(UINT32_C(0x002dedd8)); /* ae100014 sw s0,0x14(s0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002deddc));goto dispatch;
L_002deddc:
 STEP(UINT32_C(0x002deddc)); /* 8e220024 lw v0,0x24(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dede0));goto dispatch;
L_002dede0:
 STEP(UINT32_C(0x002dede0)); /* ae11001c sw s1,0x1c(s0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002dede4));goto dispatch;
L_002dede4:
 STEP(UINT32_C(0x002dede4)); /* 14800011 bne a0,zero,002dee2c */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002dede8));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000034),&value32,4u);target=sx(taken?UINT32_C(0x002dee2c):UINT32_C(0x002dedec));goto dispatch;}
L_002dede8:
 STEP(UINT32_C(0x002dede8)); /* ae020034 sw v0,0x34(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000034),&value32,4u);target=sx(UINT32_C(0x002dedec));goto dispatch;
L_002dedec:
 STEP(UINT32_C(0x002dedec)); /* 16b40007 bne s5,s4,002dee0c */
 {int taken=(lo(m,21u)!=lo(m,20u));STEP(UINT32_C(0x002dedf0));set(m,2u,((int64_t)lo(m,18u)<(int64_t)lo(m,19u)));target=sx(taken?UINT32_C(0x002dee0c):UINT32_C(0x002dedf4));goto dispatch;}
L_002dedf0:
 STEP(UINT32_C(0x002dedf0)); /* 0253102a slt v0,s2,s3 */
 set(m,2u,((int64_t)lo(m,18u)<(int64_t)lo(m,19u)));target=sx(UINT32_C(0x002dedf4));goto dispatch;
L_002dedf4:
 STEP(UINT32_C(0x002dedf4)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002dedf8));goto dispatch;
L_002dedf8:
 STEP(UINT32_C(0x002dedf8)); /* 02a0202d daddu a0,s5,zero */
 set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002dedfc));goto dispatch;
L_002dedfc:
 STEP(UINT32_C(0x002dedfc)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002dee04));STEP(UINT32_C(0x002dee00));if(lo(m,2u)==0u)set(m,5u,lo(m,18u));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002dee00:
 STEP(UINT32_C(0x002dee00)); /* 0242280a movz a1,s2,v0 */
 if(lo(m,2u)==0u)set(m,5u,lo(m,18u));target=sx(UINT32_C(0x002dee04));goto dispatch;
L_002dee04:
 STEP(UINT32_C(0x002dee04)); /* 1000000a beq zero,zero,002dee30 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dee08));set(m,2u,lo(m,30u) & UINT64_C(0x1));target=sx(taken?UINT32_C(0x002dee30):UINT32_C(0x002dee0c));goto dispatch;}
L_002dee08:
 STEP(UINT32_C(0x002dee08)); /* 33c20001 andi v0,s8,0x1 */
 set(m,2u,lo(m,30u) & UINT64_C(0x1));target=sx(UINT32_C(0x002dee0c));goto dispatch;
L_002dee0c:
 STEP(UINT32_C(0x002dee0c)); /* 1a400003 blez s2,zero,002dee1c */
 {int taken=((int64_t)lo(m,18u)<=0);STEP(UINT32_C(0x002dee10));set(m,4u,lo(m,21u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dee1c):UINT32_C(0x002dee14));goto dispatch;}
L_002dee10:
 STEP(UINT32_C(0x002dee10)); /* 02a0202d daddu a0,s5,zero */
 set(m,4u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002dee14));goto dispatch;
L_002dee14:
 STEP(UINT32_C(0x002dee14)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002dee1c));STEP(UINT32_C(0x002dee18));set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002dee18:
 STEP(UINT32_C(0x002dee18)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002dee1c));goto dispatch;
L_002dee1c:
 STEP(UINT32_C(0x002dee1c)); /* 1a600003 blez s3,zero,002dee2c */
 {int taken=((int64_t)lo(m,19u)<=0);STEP(UINT32_C(0x002dee20));set(m,4u,lo(m,20u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dee2c):UINT32_C(0x002dee24));goto dispatch;}
L_002dee20:
 STEP(UINT32_C(0x002dee20)); /* 0280202d daddu a0,s4,zero */
 set(m,4u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002dee24));goto dispatch;
L_002dee24:
 STEP(UINT32_C(0x002dee24)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002dee2c));STEP(UINT32_C(0x002dee28));set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002dee28:
 STEP(UINT32_C(0x002dee28)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002dee2c));goto dispatch;
L_002dee2c:
 STEP(UINT32_C(0x002dee2c)); /* 33c20001 andi v0,s8,0x1 */
 set(m,2u,lo(m,30u) & UINT64_C(0x1));target=sx(UINT32_C(0x002dee30));goto dispatch;
L_002dee30:
 STEP(UINT32_C(0x002dee30)); /* 50400014 beql v0,zero,002dee84 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002dee34));set(m,19u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dee84));}else target=sx(UINT32_C(0x002dee38));goto dispatch;
L_002dee34:
 STEP(UINT32_C(0x002dee34)); /* 24130001 addiu s3,zero,1 */
 set(m,19u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dee38));goto dispatch;
L_002dee38:
 STEP(UINT32_C(0x002dee38)); /* 16e00003 bne s7,zero,002dee48 */
 {int taken=(lo(m,23u)!=lo(m,0u));STEP(UINT32_C(0x002dee3c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002dee48):UINT32_C(0x002dee40));goto dispatch;}
L_002dee3c:
 STEP(UINT32_C(0x002dee3c)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dee40));goto dispatch;
L_002dee40:
 STEP(UINT32_C(0x002dee40)); /* 10000002 beq zero,zero,002dee4c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dee44));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(taken?UINT32_C(0x002dee4c):UINT32_C(0x002dee48));goto dispatch;}
L_002dee44:
 STEP(UINT32_C(0x002dee44)); /* ae000030 sw zero,0x30(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002dee48));goto dispatch;
L_002dee48:
 STEP(UINT32_C(0x002dee48)); /* ae020030 sw v0,0x30(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002dee4c));goto dispatch;
L_002dee4c:
 STEP(UINT32_C(0x002dee4c)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dee50));goto dispatch;
L_002dee50:
 STEP(UINT32_C(0x002dee50)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002dee54));goto dispatch;
L_002dee54:
 STEP(UINT32_C(0x002dee54)); /* 8e280014 lw t0,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002dee58));goto dispatch;
L_002dee58:
 STEP(UINT32_C(0x002dee58)); /* 02a0382d daddu a3,s5,zero */
 set(m,7u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002dee5c));goto dispatch;
L_002dee5c:
 STEP(UINT32_C(0x002dee5c)); /* ae220008 sw v0,0x8(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dee60));goto dispatch;
L_002dee60:
 STEP(UINT32_C(0x002dee60)); /* 0240482d daddu t1,s2,zero */
 set(m,9u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002dee64));goto dispatch;
L_002dee64:
 STEP(UINT32_C(0x002dee64)); /* 3484000a ori a0,a0,0xa */
 set(m,4u,lo(m,4u) | UINT64_C(0xa));target=sx(UINT32_C(0x002dee68));goto dispatch;
L_002dee68:
 STEP(UINT32_C(0x002dee68)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002dee6c));goto dispatch;
L_002dee6c:
 STEP(UINT32_C(0x002dee6c)); /* 0c0b78ac jal 002de2b0 */
 set(m,31u,UINT64_C(0x002dee74));STEP(UINT32_C(0x002dee70));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002dee70:
 STEP(UINT32_C(0x002dee70)); /* 24060040 addiu a2,zero,64 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dee74));goto dispatch;
L_002dee74:
 STEP(UINT32_C(0x002dee74)); /* 14400023 bne v0,zero,002def04 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dee78));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002def04):UINT32_C(0x002dee7c));goto dispatch;}
L_002dee78:
 STEP(UINT32_C(0x002dee78)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dee7c));goto dispatch;
L_002dee7c:
 STEP(UINT32_C(0x002dee7c)); /* 10000018 beq zero,zero,002deee0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dee80));/* nop */target=sx(taken?UINT32_C(0x002deee0):UINT32_C(0x002dee84));goto dispatch;}
L_002dee80:
 STEP(UINT32_C(0x002dee80)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dee84));goto dispatch;
L_002dee84:
 STEP(UINT32_C(0x002dee84)); /* afa00008 sw zero,0x8(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dee88));goto dispatch;
L_002dee88:
 STEP(UINT32_C(0x002dee88)); /* afb30004 sw s3,0x4(sp) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dee8c));goto dispatch;
L_002dee8c:
 STEP(UINT32_C(0x002dee8c)); /* 0c0b6fa8 jal 002dbea0 */
 set(m,31u,UINT64_C(0x002dee94));STEP(UINT32_C(0x002dee90));set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002dbea0));goto dispatch;
L_002dee90:
 STEP(UINT32_C(0x002dee90)); /* 03a0202d daddu a0,sp,zero */
 set(m,4u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002dee94));goto dispatch;
L_002dee94:
 STEP(UINT32_C(0x002dee94)); /* 04410005 regimm1 v0,002deeac */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002dee98));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002deeac):UINT32_C(0x002dee9c));goto dispatch;}
L_002dee98:
 STEP(UINT32_C(0x002dee98)); /* ae220008 sw v0,0x8(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dee9c));goto dispatch;
L_002dee9c:
 STEP(UINT32_C(0x002dee9c)); /* 0c0b79de jal 002de778 */
 set(m,31u,UINT64_C(0x002deea4));STEP(UINT32_C(0x002deea0));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de778));goto dispatch;
L_002deea0:
 STEP(UINT32_C(0x002deea0)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002deea4));goto dispatch;
L_002deea4:
 STEP(UINT32_C(0x002deea4)); /* 10000017 beq zero,zero,002def04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002deea8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffd)));target=sx(taken?UINT32_C(0x002def04):UINT32_C(0x002deeac));goto dispatch;}
L_002deea8:
 STEP(UINT32_C(0x002deea8)); /* 2402fffd addiu v0,zero,-3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffd)));target=sx(UINT32_C(0x002deeac));goto dispatch;
L_002deeac:
 STEP(UINT32_C(0x002deeac)); /* ae130030 sw s3,0x30(s0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002deeb0));goto dispatch;
L_002deeb0:
 STEP(UINT32_C(0x002deeb0)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002deeb4));goto dispatch;
L_002deeb4:
 STEP(UINT32_C(0x002deeb4)); /* 02a0382d daddu a3,s5,zero */
 set(m,7u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002deeb8));goto dispatch;
L_002deeb8:
 STEP(UINT32_C(0x002deeb8)); /* 0240482d daddu t1,s2,zero */
 set(m,9u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002deebc));goto dispatch;
L_002deebc:
 STEP(UINT32_C(0x002deebc)); /* 8e280014 lw t0,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x002deec0));goto dispatch;
L_002deec0:
 STEP(UINT32_C(0x002deec0)); /* 3484000a ori a0,a0,0xa */
 set(m,4u,lo(m,4u) | UINT64_C(0xa));target=sx(UINT32_C(0x002deec4));goto dispatch;
L_002deec4:
 STEP(UINT32_C(0x002deec4)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002deec8));goto dispatch;
L_002deec8:
 STEP(UINT32_C(0x002deec8)); /* 0c0b78ac jal 002de2b0 */
 set(m,31u,UINT64_C(0x002deed0));STEP(UINT32_C(0x002deecc));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002deecc:
 STEP(UINT32_C(0x002deecc)); /* 24060040 addiu a2,zero,64 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002deed0));goto dispatch;
L_002deed0:
 STEP(UINT32_C(0x002deed0)); /* 14400007 bne v0,zero,002deef0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002deed4));/* nop */target=sx(taken?UINT32_C(0x002deef0):UINT32_C(0x002deed8));goto dispatch;}
L_002deed4:
 STEP(UINT32_C(0x002deed4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002deed8));goto dispatch;
L_002deed8:
 STEP(UINT32_C(0x002deed8)); /* 0c0b6fac jal 002dbeb0 */
 set(m,31u,UINT64_C(0x002deee0));STEP(UINT32_C(0x002deedc));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbeb0));goto dispatch;
L_002deedc:
 STEP(UINT32_C(0x002deedc)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002deee0));goto dispatch;
L_002deee0:
 STEP(UINT32_C(0x002deee0)); /* 0c0b79de jal 002de778 */
 set(m,31u,UINT64_C(0x002deee8));STEP(UINT32_C(0x002deee4));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de778));goto dispatch;
L_002deee4:
 STEP(UINT32_C(0x002deee4)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002deee8));goto dispatch;
L_002deee8:
 STEP(UINT32_C(0x002deee8)); /* 10000006 beq zero,zero,002def04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002deeec));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(taken?UINT32_C(0x002def04):UINT32_C(0x002deef0));goto dispatch;}
L_002deeec:
 STEP(UINT32_C(0x002deeec)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x002deef0));goto dispatch;
L_002deef0:
 STEP(UINT32_C(0x002deef0)); /* 0c0b6fb8 jal 002dbee0 */
 set(m,31u,UINT64_C(0x002deef8));STEP(UINT32_C(0x002deef4));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbee0));goto dispatch;
L_002deef4:
 STEP(UINT32_C(0x002deef4)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002deef8));goto dispatch;
L_002deef8:
 STEP(UINT32_C(0x002deef8)); /* 0c0b6fac jal 002dbeb0 */
 set(m,31u,UINT64_C(0x002def00));STEP(UINT32_C(0x002deefc));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbeb0));goto dispatch;
L_002deefc:
 STEP(UINT32_C(0x002deefc)); /* 8e240008 lw a0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002def00));goto dispatch;
L_002def00:
 STEP(UINT32_C(0x002def00)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002def04));goto dispatch;
L_002def04:
 STEP(UINT32_C(0x002def04)); /* dfbf00b0 ld ra,0xb0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000000b0),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002def08));goto dispatch;
L_002def08:
 STEP(UINT32_C(0x002def08)); /* dfbe00a0 ld s8,0xa0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),&value64,8u);set(m,30u,value64);target=sx(UINT32_C(0x002def0c));goto dispatch;
L_002def0c:
 STEP(UINT32_C(0x002def0c)); /* dfb70090 ld s7,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002def10));goto dispatch;
L_002def10:
 STEP(UINT32_C(0x002def10)); /* dfb60080 ld s6,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002def14));goto dispatch;
L_002def14:
 STEP(UINT32_C(0x002def14)); /* dfb50070 ld s5,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002def18));goto dispatch;
L_002def18:
 STEP(UINT32_C(0x002def18)); /* dfb40060 ld s4,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002def1c));goto dispatch;
L_002def1c:
 STEP(UINT32_C(0x002def1c)); /* dfb30050 ld s3,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002def20));goto dispatch;
L_002def20:
 STEP(UINT32_C(0x002def20)); /* dfb20040 ld s2,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002def24));goto dispatch;
L_002def24:
 STEP(UINT32_C(0x002def24)); /* dfb10030 ld s1,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002def28));goto dispatch;
L_002def28:
 STEP(UINT32_C(0x002def28)); /* dfb00020 ld s0,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002def2c));goto dispatch;
L_002def2c:
 STEP(UINT32_C(0x002def2c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002def30));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000c0)));goto dispatch;
L_002def30:
 STEP(UINT32_C(0x002def30)); /* 27bd00c0 addiu sp,sp,192 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000c0)));target=sx(UINT32_C(0x002def34));goto dispatch;
L_002e2b10:
 STEP(UINT32_C(0x002e2b10)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002e2b14));goto dispatch;
L_002e2b14:
 STEP(UINT32_C(0x002e2b14)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e2b18));goto dispatch;
L_002e2b18:
 STEP(UINT32_C(0x002e2b18)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e2b1c));goto dispatch;
L_002e2b1c:
 STEP(UINT32_C(0x002e2b1c)); /* 3c11005a lui s1,zero,0x5a */
 set(m,17u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e2b20));goto dispatch;
L_002e2b20:
 STEP(UINT32_C(0x002e2b20)); /* 1000000a beq zero,zero,002e2b4c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2b24));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x002e2b4c):UINT32_C(0x002e2b28));goto dispatch;}
L_002e2b24:
 STEP(UINT32_C(0x002e2b24)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002e2b28));goto dispatch;
L_002e2b28:
 STEP(UINT32_C(0x002e2b28)); /* 3c020010 lui v0,zero,0x10 */
 set(m,2u,sx(UINT32_C(0x00100000)));target=sx(UINT32_C(0x002e2b2c));goto dispatch;
L_002e2b2c:
 STEP(UINT32_C(0x002e2b2c)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002e2b30));goto dispatch;
L_002e2b30:
 STEP(UINT32_C(0x002e2b30)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002e2b34));goto dispatch;
L_002e2b34:
 STEP(UINT32_C(0x002e2b34)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e2b38));goto dispatch;
L_002e2b38:
 STEP(UINT32_C(0x002e2b38)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e2b3c));goto dispatch;
L_002e2b3c:
 STEP(UINT32_C(0x002e2b3c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e2b40));goto dispatch;
L_002e2b40:
 STEP(UINT32_C(0x002e2b40)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e2b44));goto dispatch;
L_002e2b44:
 STEP(UINT32_C(0x002e2b44)); /* 1443fffa bne v0,v1,002e2b30 */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x002e2b48));/* nop */target=sx(taken?UINT32_C(0x002e2b30):UINT32_C(0x002e2b4c));goto dispatch;}
L_002e2b48:
 STEP(UINT32_C(0x002e2b48)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e2b4c));goto dispatch;
L_002e2b4c:
 STEP(UINT32_C(0x002e2b4c)); /* 2630e840 addiu s0,s1,-6080 */
 set(m,16u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffe840)));target=sx(UINT32_C(0x002e2b50));goto dispatch;
L_002e2b50:
 STEP(UINT32_C(0x002e2b50)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002e2b54));goto dispatch;
L_002e2b54:
 STEP(UINT32_C(0x002e2b54)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002e2b58));goto dispatch;
L_002e2b58:
 STEP(UINT32_C(0x002e2b58)); /* 34a50003 ori a1,a1,0x3 */
 set(m,5u,lo(m,5u) | UINT64_C(0x3));target=sx(UINT32_C(0x002e2b5c));goto dispatch;
L_002e2b5c:
 STEP(UINT32_C(0x002e2b5c)); /* 0c0b7ade jal 002deb78 */
 set(m,31u,UINT64_C(0x002e2b64));STEP(UINT32_C(0x002e2b60));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002deb78));goto dispatch;
L_002e2b60:
 STEP(UINT32_C(0x002e2b60)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2b64));goto dispatch;
L_002e2b64:
 STEP(UINT32_C(0x002e2b64)); /* 04430003 regimm3 v0,002e2b74 */
 if((int64_t)lo(m,2u)>=0){STEP(UINT32_C(0x002e2b68));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2b74));}else target=sx(UINT32_C(0x002e2b6c));goto dispatch;
L_002e2b68:
 STEP(UINT32_C(0x002e2b68)); /* 8e020024 lw v0,0x24(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e2b6c));goto dispatch;
L_002e2b6c:
 STEP(UINT32_C(0x002e2b6c)); /* 10000005 beq zero,zero,002e2b84 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e2b70));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002e2b84):UINT32_C(0x002e2b74));goto dispatch;}
L_002e2b70:
 STEP(UINT32_C(0x002e2b70)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002e2b74));goto dispatch;
L_002e2b74:
 STEP(UINT32_C(0x002e2b74)); /* 1040ffec beq v0,zero,002e2b28 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002e2b78));set(m,2u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002e2b28):UINT32_C(0x002e2b7c));goto dispatch;}
L_002e2b78:
 STEP(UINT32_C(0x002e2b78)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e2b7c));goto dispatch;
L_002e2b7c:
 STEP(UINT32_C(0x002e2b7c)); /* ac40c354 sw zero,-0x3cac(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffffc354),&value32,4u);target=sx(UINT32_C(0x002e2b80));goto dispatch;
L_002e2b80:
 STEP(UINT32_C(0x002e2b80)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e2b84));goto dispatch;
L_002e2b84:
 STEP(UINT32_C(0x002e2b84)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e2b88));goto dispatch;
L_002e2b88:
 STEP(UINT32_C(0x002e2b88)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002e2b8c));goto dispatch;
L_002e2b8c:
 STEP(UINT32_C(0x002e2b8c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e2b90));goto dispatch;
L_002e2b90:
 STEP(UINT32_C(0x002e2b90)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e2b94));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002e2b94:
 STEP(UINT32_C(0x002e2b94)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002e2b98));goto dispatch;
L_002e3060:
 STEP(UINT32_C(0x002e3060)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x002e3064));goto dispatch;
L_002e3064:
 STEP(UINT32_C(0x002e3064)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002e3068));goto dispatch;
L_002e3068:
 STEP(UINT32_C(0x002e3068)); /* 3c120053 lui s2,zero,0x53 */
 set(m,18u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e306c));goto dispatch;
L_002e306c:
 STEP(UINT32_C(0x002e306c)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002e3070));goto dispatch;
L_002e3070:
 STEP(UINT32_C(0x002e3070)); /* 8e42c358 lw v0,-0x3ca8(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffc358),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e3074));goto dispatch;
L_002e3074:
 STEP(UINT32_C(0x002e3074)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e3078));goto dispatch;
L_002e3078:
 STEP(UINT32_C(0x002e3078)); /* 04410032 regimm1 v0,002e3144 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e307c));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(taken?UINT32_C(0x002e3144):UINT32_C(0x002e3080));goto dispatch;}
L_002e307c:
 STEP(UINT32_C(0x002e307c)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e3080));goto dispatch;
L_002e3080:
 STEP(UINT32_C(0x002e3080)); /* 3c11005a lui s1,zero,0x5a */
 set(m,17u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e3084));goto dispatch;
L_002e3084:
 STEP(UINT32_C(0x002e3084)); /* 2630ec00 addiu s0,s1,-5120 */
 set(m,16u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffec00)));target=sx(UINT32_C(0x002e3088));goto dispatch;
L_002e3088:
 STEP(UINT32_C(0x002e3088)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002e308c));goto dispatch;
L_002e308c:
 STEP(UINT32_C(0x002e308c)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002e3090));goto dispatch;
L_002e3090:
 STEP(UINT32_C(0x002e3090)); /* 34a50006 ori a1,a1,0x6 */
 set(m,5u,lo(m,5u) | UINT64_C(0x6));target=sx(UINT32_C(0x002e3094));goto dispatch;
L_002e3094:
 STEP(UINT32_C(0x002e3094)); /* 0c0b7ade jal 002deb78 */
 set(m,31u,UINT64_C(0x002e309c));STEP(UINT32_C(0x002e3098));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002deb78));goto dispatch;
L_002e3098:
 STEP(UINT32_C(0x002e3098)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e309c));goto dispatch;
L_002e309c:
 STEP(UINT32_C(0x002e309c)); /* 04430003 regimm3 v0,002e30ac */
 if((int64_t)lo(m,2u)>=0){STEP(UINT32_C(0x002e30a0));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e30ac));}else target=sx(UINT32_C(0x002e30a4));goto dispatch;
L_002e30a0:
 STEP(UINT32_C(0x002e30a0)); /* 8e020024 lw v0,0x24(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e30a4));goto dispatch;
L_002e30a4:
 STEP(UINT32_C(0x002e30a4)); /* 10000028 beq zero,zero,002e3148 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e30a8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002e3148):UINT32_C(0x002e30ac));goto dispatch;}
L_002e30a8:
 STEP(UINT32_C(0x002e30a8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002e30ac));goto dispatch;
L_002e30ac:
 STEP(UINT32_C(0x002e30ac)); /* 10400019 beq v0,zero,002e3114 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002e30b0));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e3114):UINT32_C(0x002e30b4));goto dispatch;}
L_002e30b0:
 STEP(UINT32_C(0x002e30b0)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002e30b4));goto dispatch;
L_002e30b4:
 STEP(UINT32_C(0x002e30b4)); /* 3c11005a lui s1,zero,0x5a */
 set(m,17u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e30b8));goto dispatch;
L_002e30b8:
 STEP(UINT32_C(0x002e30b8)); /* ae40c358 sw zero,-0x3ca8(s2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0xffffc358),&value32,4u);target=sx(UINT32_C(0x002e30bc));goto dispatch;
L_002e30bc:
 STEP(UINT32_C(0x002e30bc)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e30c0));goto dispatch;
L_002e30c0:
 STEP(UINT32_C(0x002e30c0)); /* 240500ff addiu a1,zero,255 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000ff)));target=sx(UINT32_C(0x002e30c4));goto dispatch;
L_002e30c4:
 STEP(UINT32_C(0x002e30c4)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e30c8));goto dispatch;
L_002e30c8:
 STEP(UINT32_C(0x002e30c8)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e30cc));goto dispatch;
L_002e30cc:
 STEP(UINT32_C(0x002e30cc)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e30d0));goto dispatch;
L_002e30d0:
 STEP(UINT32_C(0x002e30d0)); /* 2629ea00 addiu t1,s1,-5632 */
 set(m,9u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffea00)));target=sx(UINT32_C(0x002e30d4));goto dispatch;
L_002e30d4:
 STEP(UINT32_C(0x002e30d4)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e30d8));goto dispatch;
L_002e30d8:
 STEP(UINT32_C(0x002e30d8)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e30e0));STEP(UINT32_C(0x002e30dc));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e30dc:
 STEP(UINT32_C(0x002e30dc)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e30e0));goto dispatch;
L_002e30e0:
 STEP(UINT32_C(0x002e30e0)); /* 04410004 regimm1 v0,002e30f4 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002e30e4));set(m,3u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002e30f4):UINT32_C(0x002e30e8));goto dispatch;}
L_002e30e4:
 STEP(UINT32_C(0x002e30e4)); /* 3c03005a lui v1,zero,0x5a */
 set(m,3u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e30e8));goto dispatch;
L_002e30e8:
 STEP(UINT32_C(0x002e30e8)); /* 3c02fffe lui v0,zero,0xfffe */
 set(m,2u,sx(UINT32_C(0xfffe0000)));target=sx(UINT32_C(0x002e30ec));goto dispatch;
L_002e30ec:
 STEP(UINT32_C(0x002e30ec)); /* 10000016 beq zero,zero,002e3148 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e30f0));set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(taken?UINT32_C(0x002e3148):UINT32_C(0x002e30f4));goto dispatch;}
L_002e30f0:
 STEP(UINT32_C(0x002e30f0)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002e30f4));goto dispatch;
L_002e30f4:
 STEP(UINT32_C(0x002e30f4)); /* 2627ea00 addiu a3,s1,-5632 */
 set(m,7u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffea00)));target=sx(UINT32_C(0x002e30f8));goto dispatch;
L_002e30f8:
 STEP(UINT32_C(0x002e30f8)); /* 2466ec28 addiu a2,v1,-5080 */
 set(m,6u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffec28)));target=sx(UINT32_C(0x002e30fc));goto dispatch;
L_002e30fc:
 STEP(UINT32_C(0x002e30fc)); /* 88e40003 lwl a0,0x3(a3) */
 {uint32_t effective=(uint32_t)lo(m,7u)+UINT32_C(0x00000003);unsigned shift=effective&3u;READ(effective&~3u,&value32,4u);value32=((uint32_t)lo(m,4u)&(UINT32_C(0x00ffffff)>>(8u*shift)))|(value32<<(8u*(3u-shift)));set(m,4u,sx(value32));}target=sx(UINT32_C(0x002e3100));goto dispatch;
L_002e3100:
 STEP(UINT32_C(0x002e3100)); /* 98e40000 lwr a0,0x0(a3) */
 {uint32_t effective=(uint32_t)lo(m,7u)+UINT32_C(0x00000000);unsigned shift=effective&3u;READ(effective&~3u,&value32,4u);value32=((uint32_t)lo(m,4u)&(shift?UINT32_MAX<<(8u*(4u-shift)):0u))|(value32>>(8u*shift));set(m,4u,shift?(lo(m,4u)&UINT64_C(0xffffffff00000000))|value32:sx(value32));}target=sx(UINT32_C(0x002e3104));goto dispatch;
L_002e3104:
 STEP(UINT32_C(0x002e3104)); /* a8c40003 swl a0,0x3(a2) */
 {uint32_t effective=(uint32_t)lo(m,6u)+UINT32_C(0x00000003);unsigned shift=effective&3u;READ(effective&~3u,&value32,4u);value32=(value32&(shift==3u?0u:UINT32_MAX<<(8u*(shift+1u))))|((uint32_t)lo(m,4u)>>(8u*(3u-shift)));WRITE(effective&~3u,&value32,4u);}target=sx(UINT32_C(0x002e3108));goto dispatch;
L_002e3108:
 STEP(UINT32_C(0x002e3108)); /* b8c40000 swr a0,0x0(a2) */
 {uint32_t effective=(uint32_t)lo(m,6u)+UINT32_C(0x00000000);unsigned shift=effective&3u;READ(effective&~3u,&value32,4u);value32=(value32&(shift?(UINT32_C(1)<<(8u*shift))-1u:0u))|((uint32_t)lo(m,4u)<<(8u*shift));WRITE(effective&~3u,&value32,4u);}target=sx(UINT32_C(0x002e310c));goto dispatch;
L_002e310c:
 STEP(UINT32_C(0x002e310c)); /* 1000000e beq zero,zero,002e3148 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e3110));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e3148):UINT32_C(0x002e3114));goto dispatch;}
L_002e3110:
 STEP(UINT32_C(0x002e3110)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3114));goto dispatch;
L_002e3114:
 STEP(UINT32_C(0x002e3114)); /* 3c020010 lui v0,zero,0x10 */
 set(m,2u,sx(UINT32_C(0x00100000)));target=sx(UINT32_C(0x002e3118));goto dispatch;
L_002e3118:
 STEP(UINT32_C(0x002e3118)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002e311c));goto dispatch;
L_002e311c:
 STEP(UINT32_C(0x002e311c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e3120));goto dispatch;
L_002e3120:
 STEP(UINT32_C(0x002e3120)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002e3124));goto dispatch;
L_002e3124:
 STEP(UINT32_C(0x002e3124)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e3128));goto dispatch;
L_002e3128:
 STEP(UINT32_C(0x002e3128)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e312c));goto dispatch;
L_002e312c:
 STEP(UINT32_C(0x002e312c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e3130));goto dispatch;
L_002e3130:
 STEP(UINT32_C(0x002e3130)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e3134));goto dispatch;
L_002e3134:
 STEP(UINT32_C(0x002e3134)); /* 1443fffa bne v0,v1,002e3120 */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x002e3138));/* nop */target=sx(taken?UINT32_C(0x002e3120):UINT32_C(0x002e313c));goto dispatch;}
L_002e3138:
 STEP(UINT32_C(0x002e3138)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e313c));goto dispatch;
L_002e313c:
 STEP(UINT32_C(0x002e313c)); /* 1000ffd2 beq zero,zero,002e3088 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e3140));set(m,16u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffec00)));target=sx(taken?UINT32_C(0x002e3088):UINT32_C(0x002e3144));goto dispatch;}
L_002e3140:
 STEP(UINT32_C(0x002e3140)); /* 2630ec00 addiu s0,s1,-5120 */
 set(m,16u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffec00)));target=sx(UINT32_C(0x002e3144));goto dispatch;
L_002e3144:
 STEP(UINT32_C(0x002e3144)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3148));goto dispatch;
L_002e3148:
 STEP(UINT32_C(0x002e3148)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e314c));goto dispatch;
L_002e314c:
 STEP(UINT32_C(0x002e314c)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002e3150));goto dispatch;
L_002e3150:
 STEP(UINT32_C(0x002e3150)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002e3154));goto dispatch;
L_002e3154:
 STEP(UINT32_C(0x002e3154)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e3158));goto dispatch;
L_002e3158:
 STEP(UINT32_C(0x002e3158)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e315c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_002e315c:
 STEP(UINT32_C(0x002e315c)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x002e3160));goto dispatch;
L_002dbeb0:
 STEP(UINT32_C(0x002dbeb0)); /* 24030041 addiu v1,zero,65 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000041)));target=sx(UINT32_C(0x002dbeb4));goto dispatch;
L_002dbeb4:
 m->pc=UINT32_C(0x002dbeb4); /* Unexecuted SYS; router counts exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbeb8:
 STEP(UINT32_C(0x002dbeb8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbebc));/* nop */goto dispatch;
L_002dbebc:
 STEP(UINT32_C(0x002dbebc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002dbee0:
 STEP(UINT32_C(0x002dbee0)); /* 24030044 addiu v1,zero,68 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000044)));target=sx(UINT32_C(0x002dbee4));goto dispatch;
L_002dbee4:
 m->pc=UINT32_C(0x002dbee4); /* Unexecuted SYS; router counts exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbee8:
 STEP(UINT32_C(0x002dbee8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbeec));/* nop */goto dispatch;
L_002dbeec:
 STEP(UINT32_C(0x002dbeec)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbef0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

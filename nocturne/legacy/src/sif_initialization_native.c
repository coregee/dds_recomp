#include "sif_initialization_native.h"
#include <string.h>
/* Complete original retail SIF initialization fixed statements. RAM and all MMIO are delegated
 * to the initialized memory owner; no INTC acknowledgement is synthesized.
 * The caller owns actual interrupt/SYSCALL entry, Cause/EPC/Status and clocks. */
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
uint32_t nocturneSifInitializationResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002de508):goto L_002de508;
 case UINT32_C(0x002de50c):goto L_002de50c;
 case UINT32_C(0x002de510):goto L_002de510;
 case UINT32_C(0x002de514):goto L_002de514;
 case UINT32_C(0x002de518):goto L_002de518;
 case UINT32_C(0x002de51c):goto L_002de51c;
 case UINT32_C(0x002de520):goto L_002de520;
 case UINT32_C(0x002de524):goto L_002de524;
 case UINT32_C(0x002de528):goto L_002de528;
 case UINT32_C(0x002de52c):goto L_002de52c;
 case UINT32_C(0x002de530):goto L_002de530;
 case UINT32_C(0x002de534):goto L_002de534;
 case UINT32_C(0x002de538):goto L_002de538;
 case UINT32_C(0x002de53c):goto L_002de53c;
 case UINT32_C(0x002de540):goto L_002de540;
 case UINT32_C(0x002de544):goto L_002de544;
 case UINT32_C(0x002de548):goto L_002de548;
 case UINT32_C(0x002de54c):goto L_002de54c;
 case UINT32_C(0x002de550):goto L_002de550;
 case UINT32_C(0x002de554):goto L_002de554;
 case UINT32_C(0x002de558):goto L_002de558;
 case UINT32_C(0x002de55c):goto L_002de55c;
 case UINT32_C(0x002de560):goto L_002de560;
 case UINT32_C(0x002de564):goto L_002de564;
 case UINT32_C(0x002de568):goto L_002de568;
 case UINT32_C(0x002de56c):goto L_002de56c;
 case UINT32_C(0x002de570):goto L_002de570;
 case UINT32_C(0x002de574):goto L_002de574;
 case UINT32_C(0x002de578):goto L_002de578;
 case UINT32_C(0x002de57c):goto L_002de57c;
 case UINT32_C(0x002de580):goto L_002de580;
 case UINT32_C(0x002de584):goto L_002de584;
 case UINT32_C(0x002de588):goto L_002de588;
 case UINT32_C(0x002de58c):goto L_002de58c;
 case UINT32_C(0x002de590):goto L_002de590;
 case UINT32_C(0x002de594):goto L_002de594;
 case UINT32_C(0x002de598):goto L_002de598;
 case UINT32_C(0x002de59c):goto L_002de59c;
 case UINT32_C(0x002de5a0):goto L_002de5a0;
 case UINT32_C(0x002de5a4):goto L_002de5a4;
 case UINT32_C(0x002de5a8):goto L_002de5a8;
 case UINT32_C(0x002de5ac):goto L_002de5ac;
 case UINT32_C(0x002de5b0):goto L_002de5b0;
 case UINT32_C(0x002de5b4):goto L_002de5b4;
 case UINT32_C(0x002de5b8):goto L_002de5b8;
 case UINT32_C(0x002de5bc):goto L_002de5bc;
 case UINT32_C(0x002de5c0):goto L_002de5c0;
 case UINT32_C(0x002de5c4):goto L_002de5c4;
 case UINT32_C(0x002de5c8):goto L_002de5c8;
 case UINT32_C(0x002de5cc):goto L_002de5cc;
 case UINT32_C(0x002de5d0):goto L_002de5d0;
 case UINT32_C(0x002de5d4):goto L_002de5d4;
 case UINT32_C(0x002de5d8):goto L_002de5d8;
 case UINT32_C(0x002de5dc):goto L_002de5dc;
 case UINT32_C(0x002de5e0):goto L_002de5e0;
 case UINT32_C(0x002de5e4):goto L_002de5e4;
 case UINT32_C(0x002de5e8):goto L_002de5e8;
 case UINT32_C(0x002de5ec):goto L_002de5ec;
 case UINT32_C(0x002de5f0):goto L_002de5f0;
 case UINT32_C(0x002de5f4):goto L_002de5f4;
 case UINT32_C(0x002de5f8):goto L_002de5f8;
 case UINT32_C(0x002de5fc):goto L_002de5fc;
 case UINT32_C(0x002de600):goto L_002de600;
 case UINT32_C(0x002de604):goto L_002de604;
 case UINT32_C(0x002de608):goto L_002de608;
 case UINT32_C(0x002de60c):goto L_002de60c;
 case UINT32_C(0x002de610):goto L_002de610;
 case UINT32_C(0x002de614):goto L_002de614;
 case UINT32_C(0x002de618):goto L_002de618;
 case UINT32_C(0x002de61c):goto L_002de61c;
 case UINT32_C(0x002de620):goto L_002de620;
 case UINT32_C(0x002de624):goto L_002de624;
 case UINT32_C(0x002de628):goto L_002de628;
 case UINT32_C(0x002de62c):goto L_002de62c;
 case UINT32_C(0x002de630):goto L_002de630;
 case UINT32_C(0x002de634):goto L_002de634;
 case UINT32_C(0x002de638):goto L_002de638;
 case UINT32_C(0x002de63c):goto L_002de63c;
 case UINT32_C(0x002de640):goto L_002de640;
 case UINT32_C(0x002de644):goto L_002de644;
 case UINT32_C(0x002de648):goto L_002de648;
 case UINT32_C(0x002de64c):goto L_002de64c;
 case UINT32_C(0x002de650):goto L_002de650;
 case UINT32_C(0x002de654):goto L_002de654;
 case UINT32_C(0x002de658):goto L_002de658;
 case UINT32_C(0x002de65c):goto L_002de65c;
 case UINT32_C(0x002de660):goto L_002de660;
 case UINT32_C(0x002de664):goto L_002de664;
 case UINT32_C(0x002de668):goto L_002de668;
 case UINT32_C(0x002de66c):goto L_002de66c;
 case UINT32_C(0x002de670):goto L_002de670;
 case UINT32_C(0x002de674):goto L_002de674;
 case UINT32_C(0x002de678):goto L_002de678;
 case UINT32_C(0x002de67c):goto L_002de67c;
 case UINT32_C(0x002de680):goto L_002de680;
 case UINT32_C(0x002de684):goto L_002de684;
 case UINT32_C(0x002de688):goto L_002de688;
 case UINT32_C(0x002de68c):goto L_002de68c;
 case UINT32_C(0x002de690):goto L_002de690;
 case UINT32_C(0x002de694):goto L_002de694;
 case UINT32_C(0x002de698):goto L_002de698;
 case UINT32_C(0x002de69c):goto L_002de69c;
 case UINT32_C(0x002de6a0):goto L_002de6a0;
 case UINT32_C(0x002dde38):goto L_002dde38;
 case UINT32_C(0x002dde3c):goto L_002dde3c;
 case UINT32_C(0x002dde40):goto L_002dde40;
 case UINT32_C(0x002dde44):goto L_002dde44;
 case UINT32_C(0x002dde48):goto L_002dde48;
 case UINT32_C(0x002dde4c):goto L_002dde4c;
 case UINT32_C(0x002dde50):goto L_002dde50;
 case UINT32_C(0x002dde54):goto L_002dde54;
 case UINT32_C(0x002dde58):goto L_002dde58;
 case UINT32_C(0x002dde5c):goto L_002dde5c;
 case UINT32_C(0x002dde60):goto L_002dde60;
 case UINT32_C(0x002dde64):goto L_002dde64;
 case UINT32_C(0x002dde68):goto L_002dde68;
 case UINT32_C(0x002dde6c):goto L_002dde6c;
 case UINT32_C(0x002dde70):goto L_002dde70;
 case UINT32_C(0x002dde74):goto L_002dde74;
 case UINT32_C(0x002dde78):goto L_002dde78;
 case UINT32_C(0x002dde7c):goto L_002dde7c;
 case UINT32_C(0x002dde80):goto L_002dde80;
 case UINT32_C(0x002dde84):goto L_002dde84;
 case UINT32_C(0x002dde88):goto L_002dde88;
 case UINT32_C(0x002dde8c):goto L_002dde8c;
 case UINT32_C(0x002dde90):goto L_002dde90;
 case UINT32_C(0x002dde94):goto L_002dde94;
 case UINT32_C(0x002dde98):goto L_002dde98;
 case UINT32_C(0x002dde9c):goto L_002dde9c;
 case UINT32_C(0x002ddea0):goto L_002ddea0;
 case UINT32_C(0x002ddea4):goto L_002ddea4;
 case UINT32_C(0x002ddea8):goto L_002ddea8;
 case UINT32_C(0x002ddeac):goto L_002ddeac;
 case UINT32_C(0x002ddeb0):goto L_002ddeb0;
 case UINT32_C(0x002ddeb4):goto L_002ddeb4;
 case UINT32_C(0x002ddeb8):goto L_002ddeb8;
 case UINT32_C(0x002ddebc):goto L_002ddebc;
 case UINT32_C(0x002ddec0):goto L_002ddec0;
 case UINT32_C(0x002ddec4):goto L_002ddec4;
 case UINT32_C(0x002ddec8):goto L_002ddec8;
 case UINT32_C(0x002ddecc):goto L_002ddecc;
 case UINT32_C(0x002dded0):goto L_002dded0;
 case UINT32_C(0x002dded4):goto L_002dded4;
 case UINT32_C(0x002dded8):goto L_002dded8;
 case UINT32_C(0x002ddedc):goto L_002ddedc;
 case UINT32_C(0x002ddee0):goto L_002ddee0;
 case UINT32_C(0x002ddee4):goto L_002ddee4;
 case UINT32_C(0x002ddee8):goto L_002ddee8;
 case UINT32_C(0x002ddeec):goto L_002ddeec;
 case UINT32_C(0x002ddef0):goto L_002ddef0;
 case UINT32_C(0x002ddef4):goto L_002ddef4;
 case UINT32_C(0x002ddef8):goto L_002ddef8;
 case UINT32_C(0x002ddefc):goto L_002ddefc;
 case UINT32_C(0x002ddf00):goto L_002ddf00;
 case UINT32_C(0x002ddf04):goto L_002ddf04;
 case UINT32_C(0x002ddf08):goto L_002ddf08;
 case UINT32_C(0x002ddf0c):goto L_002ddf0c;
 case UINT32_C(0x002ddf10):goto L_002ddf10;
 case UINT32_C(0x002ddf14):goto L_002ddf14;
 case UINT32_C(0x002ddf18):goto L_002ddf18;
 case UINT32_C(0x002ddf1c):goto L_002ddf1c;
 case UINT32_C(0x002ddf20):goto L_002ddf20;
 case UINT32_C(0x002ddf24):goto L_002ddf24;
 case UINT32_C(0x002ddf28):goto L_002ddf28;
 case UINT32_C(0x002ddf2c):goto L_002ddf2c;
 case UINT32_C(0x002ddf30):goto L_002ddf30;
 case UINT32_C(0x002ddf34):goto L_002ddf34;
 case UINT32_C(0x002ddf38):goto L_002ddf38;
 case UINT32_C(0x002ddf3c):goto L_002ddf3c;
 case UINT32_C(0x002ddf40):goto L_002ddf40;
 case UINT32_C(0x002ddf44):goto L_002ddf44;
 case UINT32_C(0x002ddf48):goto L_002ddf48;
 case UINT32_C(0x002ddf4c):goto L_002ddf4c;
 case UINT32_C(0x002ddf50):goto L_002ddf50;
 case UINT32_C(0x002ddf54):goto L_002ddf54;
 case UINT32_C(0x002ddf58):goto L_002ddf58;
 case UINT32_C(0x002ddf5c):goto L_002ddf5c;
 case UINT32_C(0x002ddf60):goto L_002ddf60;
 case UINT32_C(0x002ddf64):goto L_002ddf64;
 case UINT32_C(0x002ddf68):goto L_002ddf68;
 case UINT32_C(0x002ddf6c):goto L_002ddf6c;
 case UINT32_C(0x002ddf70):goto L_002ddf70;
 case UINT32_C(0x002ddf74):goto L_002ddf74;
 case UINT32_C(0x002ddf78):goto L_002ddf78;
 case UINT32_C(0x002ddf7c):goto L_002ddf7c;
 case UINT32_C(0x002ddf80):goto L_002ddf80;
 case UINT32_C(0x002ddf84):goto L_002ddf84;
 case UINT32_C(0x002ddf88):goto L_002ddf88;
 case UINT32_C(0x002ddf8c):goto L_002ddf8c;
 case UINT32_C(0x002ddf90):goto L_002ddf90;
 case UINT32_C(0x002ddf94):goto L_002ddf94;
 case UINT32_C(0x002ddf98):goto L_002ddf98;
 case UINT32_C(0x002ddf9c):goto L_002ddf9c;
 case UINT32_C(0x002ddfa0):goto L_002ddfa0;
 case UINT32_C(0x002ddfa4):goto L_002ddfa4;
 case UINT32_C(0x002ddfa8):goto L_002ddfa8;
 case UINT32_C(0x002ddfac):goto L_002ddfac;
 case UINT32_C(0x002ddfb0):goto L_002ddfb0;
 case UINT32_C(0x002ddfb4):goto L_002ddfb4;
 case UINT32_C(0x002ddfb8):goto L_002ddfb8;
 case UINT32_C(0x002ddfbc):goto L_002ddfbc;
 case UINT32_C(0x002ddfc0):goto L_002ddfc0;
 case UINT32_C(0x002ddfc4):goto L_002ddfc4;
 case UINT32_C(0x002ddfc8):goto L_002ddfc8;
 case UINT32_C(0x002ddfcc):goto L_002ddfcc;
 case UINT32_C(0x002ddfd0):goto L_002ddfd0;
 case UINT32_C(0x002ddfd4):goto L_002ddfd4;
 case UINT32_C(0x002ddfd8):goto L_002ddfd8;
 case UINT32_C(0x002ddfdc):goto L_002ddfdc;
 case UINT32_C(0x002ddfe0):goto L_002ddfe0;
 case UINT32_C(0x002ddfe4):goto L_002ddfe4;
 case UINT32_C(0x002ddfe8):goto L_002ddfe8;
 case UINT32_C(0x002ddfec):goto L_002ddfec;
 case UINT32_C(0x002ddff0):goto L_002ddff0;
 case UINT32_C(0x002ddff4):goto L_002ddff4;
 case UINT32_C(0x002ddff8):goto L_002ddff8;
 case UINT32_C(0x002ddffc):goto L_002ddffc;
 case UINT32_C(0x002de000):goto L_002de000;
 case UINT32_C(0x002de004):goto L_002de004;
 case UINT32_C(0x002de008):goto L_002de008;
 case UINT32_C(0x002de00c):goto L_002de00c;
 case UINT32_C(0x002de010):goto L_002de010;
 case UINT32_C(0x002de014):goto L_002de014;
 case UINT32_C(0x002de018):goto L_002de018;
 case UINT32_C(0x002de01c):goto L_002de01c;
 case UINT32_C(0x002de020):goto L_002de020;
 case UINT32_C(0x002de024):goto L_002de024;
 case UINT32_C(0x002de028):goto L_002de028;
 case UINT32_C(0x002de02c):goto L_002de02c;
 case UINT32_C(0x002de030):goto L_002de030;
 case UINT32_C(0x002de034):goto L_002de034;
 case UINT32_C(0x002de038):goto L_002de038;
 case UINT32_C(0x002de03c):goto L_002de03c;
 case UINT32_C(0x002de040):goto L_002de040;
 case UINT32_C(0x002de044):goto L_002de044;
 case UINT32_C(0x002de048):goto L_002de048;
 case UINT32_C(0x002de04c):goto L_002de04c;
 case UINT32_C(0x002de050):goto L_002de050;
 case UINT32_C(0x002de054):goto L_002de054;
 case UINT32_C(0x002de058):goto L_002de058;
 case UINT32_C(0x002de05c):goto L_002de05c;
 case UINT32_C(0x002de060):goto L_002de060;
 case UINT32_C(0x002de064):goto L_002de064;
 case UINT32_C(0x002de068):goto L_002de068;
 case UINT32_C(0x002de06c):goto L_002de06c;
 case UINT32_C(0x002de070):goto L_002de070;
 case UINT32_C(0x002de074):goto L_002de074;
 case UINT32_C(0x002de078):goto L_002de078;
 case UINT32_C(0x002de07c):goto L_002de07c;
 case UINT32_C(0x002de080):goto L_002de080;
 case UINT32_C(0x002de084):goto L_002de084;
 case UINT32_C(0x002de088):goto L_002de088;
 case UINT32_C(0x002de08c):goto L_002de08c;
 case UINT32_C(0x002de090):goto L_002de090;
 case UINT32_C(0x002de094):goto L_002de094;
 case UINT32_C(0x002de098):goto L_002de098;
 case UINT32_C(0x002de09c):goto L_002de09c;
 case UINT32_C(0x002de0a0):goto L_002de0a0;
 case UINT32_C(0x002de0a4):goto L_002de0a4;
 case UINT32_C(0x002de0a8):goto L_002de0a8;
 case UINT32_C(0x002de0ac):goto L_002de0ac;
 case UINT32_C(0x002de0b0):goto L_002de0b0;
 case UINT32_C(0x002de0b4):goto L_002de0b4;
 case UINT32_C(0x002de120):goto L_002de120;
 case UINT32_C(0x002de124):goto L_002de124;
 case UINT32_C(0x002de128):goto L_002de128;
 case UINT32_C(0x002de12c):goto L_002de12c;
 case UINT32_C(0x002de130):goto L_002de130;
 case UINT32_C(0x002de134):goto L_002de134;
 case UINT32_C(0x002de138):goto L_002de138;
 case UINT32_C(0x002de13c):goto L_002de13c;
 case UINT32_C(0x002de140):goto L_002de140;
 case UINT32_C(0x002de144):goto L_002de144;
 case UINT32_C(0x002de148):goto L_002de148;
 case UINT32_C(0x002dcab8):goto L_002dcab8;
 case UINT32_C(0x002dcabc):goto L_002dcabc;
 case UINT32_C(0x002dcac0):goto L_002dcac0;
 case UINT32_C(0x002dcac4):goto L_002dcac4;
 case UINT32_C(0x002dcac8):goto L_002dcac8;
 case UINT32_C(0x002dcacc):goto L_002dcacc;
 case UINT32_C(0x002dcad0):goto L_002dcad0;
 case UINT32_C(0x002dcad4):goto L_002dcad4;
 case UINT32_C(0x002dcad8):goto L_002dcad8;
 case UINT32_C(0x002dcadc):goto L_002dcadc;
 case UINT32_C(0x002dcae0):goto L_002dcae0;
 case UINT32_C(0x002dcae4):goto L_002dcae4;
 case UINT32_C(0x002dcae8):goto L_002dcae8;
 case UINT32_C(0x002dcaec):goto L_002dcaec;
 case UINT32_C(0x002dcaf0):goto L_002dcaf0;
 case UINT32_C(0x002dcaf4):goto L_002dcaf4;
 case UINT32_C(0x002dcaf8):goto L_002dcaf8;
 case UINT32_C(0x002dcafc):goto L_002dcafc;
 case UINT32_C(0x002dcb00):goto L_002dcb00;
 case UINT32_C(0x002dcb04):goto L_002dcb04;
 case UINT32_C(0x002dcb08):goto L_002dcb08;
 case UINT32_C(0x002dcb0c):goto L_002dcb0c;
 case UINT32_C(0x002dcb10):goto L_002dcb10;
 case UINT32_C(0x002dcb14):goto L_002dcb14;
 case UINT32_C(0x002dcb18):goto L_002dcb18;
 case UINT32_C(0x002dcb1c):goto L_002dcb1c;
 case UINT32_C(0x002dbbb0):goto L_002dbbb0;
 case UINT32_C(0x002dbbb4):goto L_002dbbb4;
 case UINT32_C(0x002dbbb8):goto L_002dbbb8;
 case UINT32_C(0x002dbbbc):goto L_002dbbbc;
 case UINT32_C(0x002dbc00):goto L_002dbc00;
 case UINT32_C(0x002dbc04):goto L_002dbc04;
 case UINT32_C(0x002dbc08):goto L_002dbc08;
 case UINT32_C(0x002dbc0c):goto L_002dbc0c;
 case UINT32_C(0x002dc280):goto L_002dc280;
 case UINT32_C(0x002dc284):goto L_002dc284;
 case UINT32_C(0x002dc288):goto L_002dc288;
 case UINT32_C(0x002dc28c):goto L_002dc28c;
 case UINT32_C(0x002dc2a0):goto L_002dc2a0;
 case UINT32_C(0x002dc2a4):goto L_002dc2a4;
 case UINT32_C(0x002dc2a8):goto L_002dc2a8;
 case UINT32_C(0x002dc2ac):goto L_002dc2ac;
 case UINT32_C(0x002dc2b0):goto L_002dc2b0;
 case UINT32_C(0x002dc2b4):goto L_002dc2b4;
 case UINT32_C(0x002dc2b8):goto L_002dc2b8;
 case UINT32_C(0x002dc2bc):goto L_002dc2bc;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002de508:
 STEP(UINT32_C(0x002de508)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002de50c));goto dispatch;
L_002de50c:
 STEP(UINT32_C(0x002de50c)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002de510));goto dispatch;
L_002de510:
 STEP(UINT32_C(0x002de510)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002de514));goto dispatch;
L_002de514:
 STEP(UINT32_C(0x002de514)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002de518));goto dispatch;
L_002de518:
 STEP(UINT32_C(0x002de518)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002de520));STEP(UINT32_C(0x002de51c));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002de51c:
 STEP(UINT32_C(0x002de51c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002de520));goto dispatch;
L_002de520:
 STEP(UINT32_C(0x002de520)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002de524));goto dispatch;
L_002de524:
 STEP(UINT32_C(0x002de524)); /* 8c62c2bc lw v0,-0x3d44(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0xffffc2bc),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002de528));goto dispatch;
L_002de528:
 STEP(UINT32_C(0x002de528)); /* 10400007 beq v0,zero,002de548 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002de52c));set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002de548):UINT32_C(0x002de530));goto dispatch;}
L_002de52c:
 STEP(UINT32_C(0x002de52c)); /* 24110001 addiu s1,zero,1 */
 set(m,17u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de530));goto dispatch;
L_002de530:
 STEP(UINT32_C(0x002de530)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de534));goto dispatch;
L_002de534:
 STEP(UINT32_C(0x002de534)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002de538));goto dispatch;
L_002de538:
 STEP(UINT32_C(0x002de538)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002de53c));goto dispatch;
L_002de53c:
 STEP(UINT32_C(0x002de53c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de540));goto dispatch;
L_002de540:
 STEP(UINT32_C(0x002de540)); /* 080b902e j 002e40b8 */
 STEP(UINT32_C(0x002de544));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002de544:
 STEP(UINT32_C(0x002de544)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de548));goto dispatch;
L_002de548:
 STEP(UINT32_C(0x002de548)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002de550));STEP(UINT32_C(0x002de54c));value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffc2bc),&value32,4u);target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002de54c:
 STEP(UINT32_C(0x002de54c)); /* ac71c2bc sw s1,-0x3d44(v1) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffc2bc),&value32,4u);target=sx(UINT32_C(0x002de550));goto dispatch;
L_002de550:
 STEP(UINT32_C(0x002de550)); /* 0c0b778e jal 002dde38 */
 set(m,31u,UINT64_C(0x002de558));STEP(UINT32_C(0x002de554));/* nop */target=sx(UINT32_C(0x002dde38));goto dispatch;
L_002de554:
 STEP(UINT32_C(0x002de554)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de558));goto dispatch;
L_002de558:
 STEP(UINT32_C(0x002de558)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002de560));STEP(UINT32_C(0x002de55c));/* nop */target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002de55c:
 STEP(UINT32_C(0x002de55c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de560));goto dispatch;
L_002de560:
 STEP(UINT32_C(0x002de560)); /* 3c03005a lui v1,zero,0x5a */
 set(m,3u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002de564));goto dispatch;
L_002de564:
 STEP(UINT32_C(0x002de564)); /* 3c08005a lui t0,zero,0x5a */
 set(m,8u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002de568));goto dispatch;
L_002de568:
 STEP(UINT32_C(0x002de568)); /* 2472bc40 addiu s2,v1,-17344 */
 set(m,18u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffbc40)));target=sx(UINT32_C(0x002de56c));goto dispatch;
L_002de56c:
 STEP(UINT32_C(0x002de56c)); /* 3c06005a lui a2,zero,0x5a */
 set(m,6u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002de570));goto dispatch;
L_002de570:
 STEP(UINT32_C(0x002de570)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002de574));goto dispatch;
L_002de574:
 STEP(UINT32_C(0x002de574)); /* 2510d440 addiu s0,t0,-11200 */
 set(m,16u,sx((uint32_t)lo(m,8u)+UINT32_C(0xffffd440)));target=sx(UINT32_C(0x002de578));goto dispatch;
L_002de578:
 STEP(UINT32_C(0x002de578)); /* 24030020 addiu v1,zero,32 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002de57c));goto dispatch;
L_002de57c:
 STEP(UINT32_C(0x002de57c)); /* 3c022000 lui v0,zero,0x2000 */
 set(m,2u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002de580));goto dispatch;
L_002de580:
 STEP(UINT32_C(0x002de580)); /* 24c6c440 addiu a2,a2,-15296 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffc440)));target=sx(UINT32_C(0x002de584));goto dispatch;
L_002de584:
 STEP(UINT32_C(0x002de584)); /* 24e7cc40 addiu a3,a3,-13248 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffffcc40)));target=sx(UINT32_C(0x002de588));goto dispatch;
L_002de588:
 STEP(UINT32_C(0x002de588)); /* 00c23025 or a2,a2,v0 */
 set(m,6u,lo(m,6u)|lo(m,2u));target=sx(UINT32_C(0x002de58c));goto dispatch;
L_002de58c:
 STEP(UINT32_C(0x002de58c)); /* 00e23825 or a3,a3,v0 */
 set(m,7u,lo(m,7u)|lo(m,2u));target=sx(UINT32_C(0x002de590));goto dispatch;
L_002de590:
 STEP(UINT32_C(0x002de590)); /* ae030020 sw v1,0x20(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002de594));goto dispatch;
L_002de594:
 STEP(UINT32_C(0x002de594)); /* 02421025 or v0,s2,v0 */
 set(m,2u,lo(m,18u)|lo(m,2u));target=sx(UINT32_C(0x002de598));goto dispatch;
L_002de598:
 STEP(UINT32_C(0x002de598)); /* ad11d440 sw s1,-0x2bc0(t0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0xffffd440),&value32,4u);target=sx(UINT32_C(0x002de59c));goto dispatch;
L_002de59c:
 STEP(UINT32_C(0x002de59c)); /* 3c05002e lui a1,zero,0x2e */
 set(m,5u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002de5a0));goto dispatch;
L_002de5a0:
 STEP(UINT32_C(0x002de5a0)); /* ae060014 sw a2,0x14(s0) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002de5a4));goto dispatch;
L_002de5a4:
 STEP(UINT32_C(0x002de5a4)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de5a8));goto dispatch;
L_002de5a8:
 STEP(UINT32_C(0x002de5a8)); /* ae020004 sw v0,0x4(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002de5ac));goto dispatch;
L_002de5ac:
 STEP(UINT32_C(0x002de5ac)); /* 24a5e808 addiu a1,a1,-6136 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffe808)));target=sx(UINT32_C(0x002de5b0));goto dispatch;
L_002de5b0:
 STEP(UINT32_C(0x002de5b0)); /* ae07001c sw a3,0x1c(s0) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002de5b4));goto dispatch;
L_002de5b4:
 STEP(UINT32_C(0x002de5b4)); /* 34840008 ori a0,a0,0x8 */
 set(m,4u,lo(m,4u) | UINT64_C(0x8));target=sx(UINT32_C(0x002de5b8));goto dispatch;
L_002de5b8:
 STEP(UINT32_C(0x002de5b8)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de5bc));goto dispatch;
L_002de5bc:
 STEP(UINT32_C(0x002de5bc)); /* ae030008 sw v1,0x8(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002de5c0));goto dispatch;
L_002de5c0:
 STEP(UINT32_C(0x002de5c0)); /* ae00000c sw zero,0xc(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002de5c4));goto dispatch;
L_002de5c4:
 STEP(UINT32_C(0x002de5c4)); /* ae000010 sw zero,0x10(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002de5c8));goto dispatch;
L_002de5c8:
 STEP(UINT32_C(0x002de5c8)); /* ae030018 sw v1,0x18(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002de5cc));goto dispatch;
L_002de5cc:
 STEP(UINT32_C(0x002de5cc)); /* 0c0b7848 jal 002de120 */
 set(m,31u,UINT64_C(0x002de5d4));STEP(UINT32_C(0x002de5d0));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002de120));goto dispatch;
L_002de5d0:
 STEP(UINT32_C(0x002de5d0)); /* ae000024 sw zero,0x24(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002de5d4));goto dispatch;
L_002de5d4:
 STEP(UINT32_C(0x002de5d4)); /* 3c05002e lui a1,zero,0x2e */
 set(m,5u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002de5d8));goto dispatch;
L_002de5d8:
 STEP(UINT32_C(0x002de5d8)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de5dc));goto dispatch;
L_002de5dc:
 STEP(UINT32_C(0x002de5dc)); /* 24a5eac8 addiu a1,a1,-5432 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffeac8)));target=sx(UINT32_C(0x002de5e0));goto dispatch;
L_002de5e0:
 STEP(UINT32_C(0x002de5e0)); /* 34840009 ori a0,a0,0x9 */
 set(m,4u,lo(m,4u) | UINT64_C(0x9));target=sx(UINT32_C(0x002de5e4));goto dispatch;
L_002de5e4:
 STEP(UINT32_C(0x002de5e4)); /* 0c0b7848 jal 002de120 */
 set(m,31u,UINT64_C(0x002de5ec));STEP(UINT32_C(0x002de5e8));set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de120));goto dispatch;
L_002de5e8:
 STEP(UINT32_C(0x002de5e8)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de5ec));goto dispatch;
L_002de5ec:
 STEP(UINT32_C(0x002de5ec)); /* 3c05002e lui a1,zero,0x2e */
 set(m,5u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002de5f0));goto dispatch;
L_002de5f0:
 STEP(UINT32_C(0x002de5f0)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de5f4));goto dispatch;
L_002de5f4:
 STEP(UINT32_C(0x002de5f4)); /* 24a5ecb8 addiu a1,a1,-4936 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffecb8)));target=sx(UINT32_C(0x002de5f8));goto dispatch;
L_002de5f8:
 STEP(UINT32_C(0x002de5f8)); /* 3484000a ori a0,a0,0xa */
 set(m,4u,lo(m,4u) | UINT64_C(0xa));target=sx(UINT32_C(0x002de5fc));goto dispatch;
L_002de5fc:
 STEP(UINT32_C(0x002de5fc)); /* 0c0b7848 jal 002de120 */
 set(m,31u,UINT64_C(0x002de604));STEP(UINT32_C(0x002de600));set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de120));goto dispatch;
L_002de600:
 STEP(UINT32_C(0x002de600)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de604));goto dispatch;
L_002de604:
 STEP(UINT32_C(0x002de604)); /* 3c05002e lui a1,zero,0x2e */
 set(m,5u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002de608));goto dispatch;
L_002de608:
 STEP(UINT32_C(0x002de608)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de60c));goto dispatch;
L_002de60c:
 STEP(UINT32_C(0x002de60c)); /* 24a5e8c0 addiu a1,a1,-5952 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffe8c0)));target=sx(UINT32_C(0x002de610));goto dispatch;
L_002de610:
 STEP(UINT32_C(0x002de610)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de614));goto dispatch;
L_002de614:
 STEP(UINT32_C(0x002de614)); /* 0c0b7848 jal 002de120 */
 set(m,31u,UINT64_C(0x002de61c));STEP(UINT32_C(0x002de618));set(m,4u,lo(m,4u) | UINT64_C(0xc));target=sx(UINT32_C(0x002de120));goto dispatch;
L_002de618:
 STEP(UINT32_C(0x002de618)); /* 3484000c ori a0,a0,0xc */
 set(m,4u,lo(m,4u) | UINT64_C(0xc));target=sx(UINT32_C(0x002de61c));goto dispatch;
L_002de61c:
 STEP(UINT32_C(0x002de61c)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002de624));STEP(UINT32_C(0x002de620));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002de620:
 STEP(UINT32_C(0x002de620)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de624));goto dispatch;
L_002de624:
 STEP(UINT32_C(0x002de624)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de628));goto dispatch;
L_002de628:
 STEP(UINT32_C(0x002de628)); /* 0c0b70ac jal 002dc2b0 */
 set(m,31u,UINT64_C(0x002de630));STEP(UINT32_C(0x002de62c));set(m,4u,lo(m,4u) | UINT64_C(0x2));target=sx(UINT32_C(0x002dc2b0));goto dispatch;
L_002de62c:
 STEP(UINT32_C(0x002de62c)); /* 34840002 ori a0,a0,0x2 */
 set(m,4u,lo(m,4u) | UINT64_C(0x2));target=sx(UINT32_C(0x002de630));goto dispatch;
L_002de630:
 STEP(UINT32_C(0x002de630)); /* 14400017 bne v0,zero,002de690 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002de634));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002de690):UINT32_C(0x002de638));goto dispatch;}
L_002de634:
 STEP(UINT32_C(0x002de634)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de638));goto dispatch;
L_002de638:
 STEP(UINT32_C(0x002de638)); /* 26450040 addiu a1,s2,64 */
 set(m,5u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de63c));goto dispatch;
L_002de63c:
 STEP(UINT32_C(0x002de63c)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de640));goto dispatch;
L_002de640:
 STEP(UINT32_C(0x002de640)); /* acb1000c sw s1,0xc(a1) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002de644));goto dispatch;
L_002de644:
 STEP(UINT32_C(0x002de644)); /* 34840002 ori a0,a0,0x2 */
 set(m,4u,lo(m,4u) | UINT64_C(0x2));target=sx(UINT32_C(0x002de648));goto dispatch;
L_002de648:
 STEP(UINT32_C(0x002de648)); /* 24060010 addiu a2,zero,16 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002de64c));goto dispatch;
L_002de64c:
 STEP(UINT32_C(0x002de64c)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de650));goto dispatch;
L_002de650:
 STEP(UINT32_C(0x002de650)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de654));goto dispatch;
L_002de654:
 STEP(UINT32_C(0x002de654)); /* 0c0b78ac jal 002de2b0 */
 set(m,31u,UINT64_C(0x002de65c));STEP(UINT32_C(0x002de658));set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002de658:
 STEP(UINT32_C(0x002de658)); /* 0000482d daddu t1,zero,zero */
 set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de65c));goto dispatch;
L_002de65c:
 STEP(UINT32_C(0x002de65c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002de660));goto dispatch;
L_002de660:
 STEP(UINT32_C(0x002de660)); /* 0c0b777c jal 002dddf0 */
 set(m,31u,UINT64_C(0x002de668));STEP(UINT32_C(0x002de664));set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dddf0));goto dispatch;
L_002de664:
 STEP(UINT32_C(0x002de664)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de668));goto dispatch;
L_002de668:
 STEP(UINT32_C(0x002de668)); /* 1040fffd beq v0,zero,002de660 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002de66c));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002de660):UINT32_C(0x002de670));goto dispatch;}
L_002de66c:
 STEP(UINT32_C(0x002de66c)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de670));goto dispatch;
L_002de670:
 STEP(UINT32_C(0x002de670)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de674));goto dispatch;
L_002de674:
 STEP(UINT32_C(0x002de674)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002de678));goto dispatch;
L_002de678:
 STEP(UINT32_C(0x002de678)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002de67c));goto dispatch;
L_002de67c:
 STEP(UINT32_C(0x002de67c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002de680));goto dispatch;
L_002de680:
 STEP(UINT32_C(0x002de680)); /* 34840002 ori a0,a0,0x2 */
 set(m,4u,lo(m,4u) | UINT64_C(0x2));target=sx(UINT32_C(0x002de684));goto dispatch;
L_002de684:
 STEP(UINT32_C(0x002de684)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de688));goto dispatch;
L_002de688:
 STEP(UINT32_C(0x002de688)); /* 080b70a8 j 002dc2a0 */
 STEP(UINT32_C(0x002de68c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dc2a0));goto dispatch;
L_002de68c:
 STEP(UINT32_C(0x002de68c)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de690));goto dispatch;
L_002de690:
 STEP(UINT32_C(0x002de690)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002de694));goto dispatch;
L_002de694:
 STEP(UINT32_C(0x002de694)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002de698));goto dispatch;
L_002de698:
 STEP(UINT32_C(0x002de698)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de69c));goto dispatch;
L_002de69c:
 STEP(UINT32_C(0x002de69c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de6a0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002de6a0:
 STEP(UINT32_C(0x002de6a0)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002de6a4));goto dispatch;
L_002dde38:
 STEP(UINT32_C(0x002dde38)); /* 27bdffa0 addiu sp,sp,-96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffa0)));target=sx(UINT32_C(0x002dde3c));goto dispatch;
L_002dde3c:
 STEP(UINT32_C(0x002dde3c)); /* ffbf0050 sd ra,0x50(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002dde40));goto dispatch;
L_002dde40:
 STEP(UINT32_C(0x002dde40)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002dde44));goto dispatch;
L_002dde44:
 STEP(UINT32_C(0x002dde44)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002dde48));goto dispatch;
L_002dde48:
 STEP(UINT32_C(0x002dde48)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dde4c));goto dispatch;
L_002dde4c:
 STEP(UINT32_C(0x002dde4c)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dde50));goto dispatch;
L_002dde50:
 STEP(UINT32_C(0x002dde50)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002dde58));STEP(UINT32_C(0x002dde54));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002dde54:
 STEP(UINT32_C(0x002dde54)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dde58));goto dispatch;
L_002dde58:
 STEP(UINT32_C(0x002dde58)); /* 3c0a0053 lui t2,zero,0x53 */
 set(m,10u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002dde5c));goto dispatch;
L_002dde5c:
 STEP(UINT32_C(0x002dde5c)); /* 8d42c2b8 lw v0,-0x3d48(t2) */
 READ((uint32_t)lo(m,10u)+UINT32_C(0xffffc2b8),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dde60));goto dispatch;
L_002dde60:
 STEP(UINT32_C(0x002dde60)); /* 10400009 beq v0,zero,002dde88 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002dde64));set(m,19u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002dde88):UINT32_C(0x002dde68));goto dispatch;}
L_002dde64:
 STEP(UINT32_C(0x002dde64)); /* 3c13005a lui s3,zero,0x5a */
 set(m,19u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dde68));goto dispatch;
L_002dde68:
 STEP(UINT32_C(0x002dde68)); /* dfbf0050 ld ra,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dde6c));goto dispatch;
L_002dde6c:
 STEP(UINT32_C(0x002dde6c)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002dde70));goto dispatch;
L_002dde70:
 STEP(UINT32_C(0x002dde70)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002dde74));goto dispatch;
L_002dde74:
 STEP(UINT32_C(0x002dde74)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002dde78));goto dispatch;
L_002dde78:
 STEP(UINT32_C(0x002dde78)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dde7c));goto dispatch;
L_002dde7c:
 STEP(UINT32_C(0x002dde7c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dde80));goto dispatch;
L_002dde80:
 STEP(UINT32_C(0x002dde80)); /* 080b902e j 002e40b8 */
 STEP(UINT32_C(0x002dde84));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002dde84:
 STEP(UINT32_C(0x002dde84)); /* 27bd0060 addiu sp,sp,96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002dde88));goto dispatch;
L_002dde88:
 STEP(UINT32_C(0x002dde88)); /* 3c05005a lui a1,zero,0x5a */
 set(m,5u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dde8c));goto dispatch;
L_002dde8c:
 STEP(UINT32_C(0x002dde8c)); /* 3c022000 lui v0,zero,0x2000 */
 set(m,2u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002dde90));goto dispatch;
L_002dde90:
 STEP(UINT32_C(0x002dde90)); /* 24a5ba40 addiu a1,a1,-17856 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffba40)));target=sx(UINT32_C(0x002dde94));goto dispatch;
L_002dde94:
 STEP(UINT32_C(0x002dde94)); /* 2666b9c0 addiu a2,s3,-17984 */
 set(m,6u,sx((uint32_t)lo(m,19u)+UINT32_C(0xffffb9c0)));target=sx(UINT32_C(0x002dde98));goto dispatch;
L_002dde98:
 STEP(UINT32_C(0x002dde98)); /* 3c12005a lui s2,zero,0x5a */
 set(m,18u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dde9c));goto dispatch;
L_002dde9c:
 STEP(UINT32_C(0x002dde9c)); /* 00a22825 or a1,a1,v0 */
 set(m,5u,lo(m,5u)|lo(m,2u));target=sx(UINT32_C(0x002ddea0));goto dispatch;
L_002ddea0:
 STEP(UINT32_C(0x002ddea0)); /* 00c23025 or a2,a2,v0 */
 set(m,6u,lo(m,6u)|lo(m,2u));target=sx(UINT32_C(0x002ddea4));goto dispatch;
L_002ddea4:
 STEP(UINT32_C(0x002ddea4)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ddea8));goto dispatch;
L_002ddea8:
 STEP(UINT32_C(0x002ddea8)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ddeac));goto dispatch;
L_002ddeac:
 STEP(UINT32_C(0x002ddeac)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ddeb0));goto dispatch;
L_002ddeb0:
 STEP(UINT32_C(0x002ddeb0)); /* 2642ba98 addiu v0,s2,-17768 */
 set(m,2u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffffba98)));target=sx(UINT32_C(0x002ddeb4));goto dispatch;
L_002ddeb4:
 STEP(UINT32_C(0x002ddeb4)); /* ad43c2b8 sw v1,-0x3d48(t2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,10u)+UINT32_C(0xffffc2b8),&value32,4u);target=sx(UINT32_C(0x002ddeb8));goto dispatch;
L_002ddeb8:
 STEP(UINT32_C(0x002ddeb8)); /* 2528bac0 addiu t0,t1,-17728 */
 set(m,8u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffbac0)));target=sx(UINT32_C(0x002ddebc));goto dispatch;
L_002ddebc:
 STEP(UINT32_C(0x002ddebc)); /* ae46ba98 sw a2,-0x4568(s2) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0xffffba98),&value32,4u);target=sx(UINT32_C(0x002ddec0));goto dispatch;
L_002ddec0:
 STEP(UINT32_C(0x002ddec0)); /* 2484bbc0 addiu a0,a0,-17472 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffbbc0)));target=sx(UINT32_C(0x002ddec4));goto dispatch;
L_002ddec4:
 STEP(UINT32_C(0x002ddec4)); /* 24070020 addiu a3,zero,32 */
 set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002ddec8));goto dispatch;
L_002ddec8:
 STEP(UINT32_C(0x002ddec8)); /* ac44001c sw a0,0x1c(v0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002ddecc));goto dispatch;
L_002ddecc:
 STEP(UINT32_C(0x002ddecc)); /* ac450004 sw a1,0x4(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dded0));goto dispatch;
L_002dded0:
 STEP(UINT32_C(0x002dded0)); /* 0100182d daddu v1,t0,zero */
 set(m,3u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002dded4));goto dispatch;
L_002dded4:
 STEP(UINT32_C(0x002dded4)); /* ac470010 sw a3,0x10(v0) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002dded8));goto dispatch;
L_002dded8:
 STEP(UINT32_C(0x002dded8)); /* 3c14005a lui s4,zero,0x5a */
 set(m,20u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ddedc));goto dispatch;
L_002ddedc:
 STEP(UINT32_C(0x002ddedc)); /* ac400008 sw zero,0x8(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002ddee0));goto dispatch;
L_002ddee0:
 STEP(UINT32_C(0x002ddee0)); /* 2410001f addiu s0,zero,31 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x002ddee4));goto dispatch;
L_002ddee4:
 STEP(UINT32_C(0x002ddee4)); /* ac48000c sw t0,0xc(v0) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002ddee8));goto dispatch;
L_002ddee8:
 STEP(UINT32_C(0x002ddee8)); /* ac400014 sw zero,0x14(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002ddeec));goto dispatch;
L_002ddeec:
 STEP(UINT32_C(0x002ddeec)); /* ac400018 sw zero,0x18(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002ddef0));goto dispatch;
L_002ddef0:
 STEP(UINT32_C(0x002ddef0)); /* ac600000 sw zero,0x0(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ddef4));goto dispatch;
L_002ddef4:
 STEP(UINT32_C(0x002ddef4)); /* 2610ffff addiu s0,s0,-1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002ddef8));goto dispatch;
L_002ddef8:
 STEP(UINT32_C(0x002ddef8)); /* ac600004 sw zero,0x4(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002ddefc));goto dispatch;
L_002ddefc:
 STEP(UINT32_C(0x002ddefc)); /* 24630008 addiu v1,v1,8 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002ddf00));goto dispatch;
L_002ddf00:
 STEP(UINT32_C(0x002ddf00)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ddf04));goto dispatch;
L_002ddf04:
 STEP(UINT32_C(0x002ddf04)); /* 0601fffa regimm1 s0,002ddef0 */
 {int taken=((int64_t)lo(m,16u)>=0);STEP(UINT32_C(0x002ddf08));/* nop */target=sx(taken?UINT32_C(0x002ddef0):UINT32_C(0x002ddf0c));goto dispatch;}
L_002ddf08:
 STEP(UINT32_C(0x002ddf08)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ddf0c));goto dispatch;
L_002ddf0c:
 STEP(UINT32_C(0x002ddf0c)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ddf10));goto dispatch;
L_002ddf10:
 STEP(UINT32_C(0x002ddf10)); /* 2410001f addiu s0,zero,31 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x002ddf14));goto dispatch;
L_002ddf14:
 STEP(UINT32_C(0x002ddf14)); /* 2442bbc0 addiu v0,v0,-17472 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffbbc0)));target=sx(UINT32_C(0x002ddf18));goto dispatch;
L_002ddf18:
 STEP(UINT32_C(0x002ddf18)); /* 2442007c addiu v0,v0,124 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000007c)));target=sx(UINT32_C(0x002ddf1c));goto dispatch;
L_002ddf1c:
 STEP(UINT32_C(0x002ddf1c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ddf20));goto dispatch;
L_002ddf20:
 STEP(UINT32_C(0x002ddf20)); /* ac400000 sw zero,0x0(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ddf24));goto dispatch;
L_002ddf24:
 STEP(UINT32_C(0x002ddf24)); /* 2610ffff addiu s0,s0,-1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002ddf28));goto dispatch;
L_002ddf28:
 STEP(UINT32_C(0x002ddf28)); /* 2442fffc addiu v0,v0,-4 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x002ddf2c));goto dispatch;
L_002ddf2c:
 STEP(UINT32_C(0x002ddf2c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ddf30));goto dispatch;
L_002ddf30:
 STEP(UINT32_C(0x002ddf30)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ddf34));goto dispatch;
L_002ddf34:
 STEP(UINT32_C(0x002ddf34)); /* 0601fffa regimm1 s0,002ddf20 */
 {int taken=((int64_t)lo(m,16u)>=0);STEP(UINT32_C(0x002ddf38));/* nop */target=sx(taken?UINT32_C(0x002ddf20):UINT32_C(0x002ddf3c));goto dispatch;}
L_002ddf38:
 STEP(UINT32_C(0x002ddf38)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ddf3c));goto dispatch;
L_002ddf3c:
 STEP(UINT32_C(0x002ddf3c)); /* 3c02002e lui v0,zero,0x2e */
 set(m,2u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002ddf40));goto dispatch;
L_002ddf40:
 STEP(UINT32_C(0x002ddf40)); /* 3c03002e lui v1,zero,0x2e */
 set(m,3u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002ddf44));goto dispatch;
L_002ddf44:
 STEP(UINT32_C(0x002ddf44)); /* 2442dde0 addiu v0,v0,-8736 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffdde0)));target=sx(UINT32_C(0x002ddf48));goto dispatch;
L_002ddf48:
 STEP(UINT32_C(0x002ddf48)); /* 2524bac0 addiu a0,t1,-17728 */
 set(m,4u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffbac0)));target=sx(UINT32_C(0x002ddf4c));goto dispatch;
L_002ddf4c:
 STEP(UINT32_C(0x002ddf4c)); /* 2463ddc0 addiu v1,v1,-8768 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffddc0)));target=sx(UINT32_C(0x002ddf50));goto dispatch;
L_002ddf50:
 STEP(UINT32_C(0x002ddf50)); /* 2651ba98 addiu s1,s2,-17768 */
 set(m,17u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffffba98)));target=sx(UINT32_C(0x002ddf54));goto dispatch;
L_002ddf54:
 STEP(UINT32_C(0x002ddf54)); /* ad22bac0 sw v0,-0x4540(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0xffffbac0),&value32,4u);target=sx(UINT32_C(0x002ddf58));goto dispatch;
L_002ddf58:
 STEP(UINT32_C(0x002ddf58)); /* 24100020 addiu s0,zero,32 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002ddf5c));goto dispatch;
L_002ddf5c:
 STEP(UINT32_C(0x002ddf5c)); /* ac830008 sw v1,0x8(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002ddf60));goto dispatch;
L_002ddf60:
 STEP(UINT32_C(0x002ddf60)); /* ac91000c sw s1,0xc(a0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002ddf64));goto dispatch;
L_002ddf64:
 STEP(UINT32_C(0x002ddf64)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002ddf6c));STEP(UINT32_C(0x002ddf68));value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002ddf68:
 STEP(UINT32_C(0x002ddf68)); /* ac910004 sw s1,0x4(a0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002ddf6c));goto dispatch;
L_002ddf6c:
 STEP(UINT32_C(0x002ddf6c)); /* 0c0b7048 jal 002dc120 */
 set(m,31u,UINT64_C(0x002ddf74));STEP(UINT32_C(0x002ddf70));set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dc120));goto dispatch;
L_002ddf70:
 STEP(UINT32_C(0x002ddf70)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ddf74));goto dispatch;
L_002ddf74:
 STEP(UINT32_C(0x002ddf74)); /* 3c021000 lui v0,zero,0x1000 */
 set(m,2u,sx(UINT32_C(0x10000000)));target=sx(UINT32_C(0x002ddf78));goto dispatch;
L_002ddf78:
 STEP(UINT32_C(0x002ddf78)); /* 3442e010 ori v0,v0,0xe010 */
 set(m,2u,lo(m,2u) | UINT64_C(0xe010));target=sx(UINT32_C(0x002ddf7c));goto dispatch;
L_002ddf7c:
 STEP(UINT32_C(0x002ddf7c)); /* 8c430000 lw v1,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ddf80));goto dispatch;
L_002ddf80:
 STEP(UINT32_C(0x002ddf80)); /* 30630020 andi v1,v1,0x20 */
 set(m,3u,lo(m,3u) & UINT64_C(0x20));target=sx(UINT32_C(0x002ddf84));goto dispatch;
L_002ddf84:
 STEP(UINT32_C(0x002ddf84)); /* 10600004 beq v1,zero,002ddf98 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002ddf88));set(m,2u,sx(UINT32_C(0x10000000)));target=sx(taken?UINT32_C(0x002ddf98):UINT32_C(0x002ddf8c));goto dispatch;}
L_002ddf88:
 STEP(UINT32_C(0x002ddf88)); /* 3c021000 lui v0,zero,0x1000 */
 set(m,2u,sx(UINT32_C(0x10000000)));target=sx(UINT32_C(0x002ddf8c));goto dispatch;
L_002ddf8c:
 STEP(UINT32_C(0x002ddf8c)); /* 3c011001 lui at,zero,0x1001 */
 set(m,1u,sx(UINT32_C(0x10010000)));target=sx(UINT32_C(0x002ddf90));goto dispatch;
L_002ddf90:
 STEP(UINT32_C(0x002ddf90)); /* ac30e010 sw s0,-0x1ff0(at) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe010),&value32,4u);target=sx(UINT32_C(0x002ddf94));goto dispatch;
L_002ddf94:
 STEP(UINT32_C(0x002ddf94)); /* 3c021000 lui v0,zero,0x1000 */
 set(m,2u,sx(UINT32_C(0x10000000)));target=sx(UINT32_C(0x002ddf98));goto dispatch;
L_002ddf98:
 STEP(UINT32_C(0x002ddf98)); /* 3442c000 ori v0,v0,0xc000 */
 set(m,2u,lo(m,2u) | UINT64_C(0xc000));target=sx(UINT32_C(0x002ddf9c));goto dispatch;
L_002ddf9c:
 STEP(UINT32_C(0x002ddf9c)); /* 8c430000 lw v1,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ddfa0));goto dispatch;
L_002ddfa0:
 STEP(UINT32_C(0x002ddfa0)); /* 30630100 andi v1,v1,0x100 */
 set(m,3u,lo(m,3u) & UINT64_C(0x100));target=sx(UINT32_C(0x002ddfa4));goto dispatch;
L_002ddfa4:
 STEP(UINT32_C(0x002ddfa4)); /* 14600004 bne v1,zero,002ddfb8 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002ddfa8));set(m,5u,sx(UINT32_C(0x002e0000)));target=sx(taken?UINT32_C(0x002ddfb8):UINT32_C(0x002ddfac));goto dispatch;}
L_002ddfa8:
 STEP(UINT32_C(0x002ddfa8)); /* 3c05002e lui a1,zero,0x2e */
 set(m,5u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002ddfac));goto dispatch;
L_002ddfac:
 STEP(UINT32_C(0x002ddfac)); /* 0c0b70a0 jal 002dc280 */
 set(m,31u,UINT64_C(0x002ddfb4));STEP(UINT32_C(0x002ddfb0));/* nop */target=sx(UINT32_C(0x002dc280));goto dispatch;
L_002ddfb0:
 STEP(UINT32_C(0x002ddfb0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ddfb4));goto dispatch;
L_002ddfb4:
 STEP(UINT32_C(0x002ddfb4)); /* 3c05002e lui a1,zero,0x2e */
 set(m,5u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002ddfb8));goto dispatch;
L_002ddfb8:
 STEP(UINT32_C(0x002ddfb8)); /* 24040005 addiu a0,zero,5 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000005)));target=sx(UINT32_C(0x002ddfbc));goto dispatch;
L_002ddfbc:
 STEP(UINT32_C(0x002ddfbc)); /* 24a5e330 addiu a1,a1,-7376 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffe330)));target=sx(UINT32_C(0x002ddfc0));goto dispatch;
L_002ddfc0:
 STEP(UINT32_C(0x002ddfc0)); /* 0c0b6eec jal 002dbbb0 */
 set(m,31u,UINT64_C(0x002ddfc8));STEP(UINT32_C(0x002ddfc4));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dbbb0));goto dispatch;
L_002ddfc4:
 STEP(UINT32_C(0x002ddfc4)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ddfc8));goto dispatch;
L_002ddfc8:
 STEP(UINT32_C(0x002ddfc8)); /* 3c03005a lui v1,zero,0x5a */
 set(m,3u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ddfcc));goto dispatch;
L_002ddfcc:
 STEP(UINT32_C(0x002ddfcc)); /* 24040005 addiu a0,zero,5 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000005)));target=sx(UINT32_C(0x002ddfd0));goto dispatch;
L_002ddfd0:
 STEP(UINT32_C(0x002ddfd0)); /* 0c0b72ae jal 002dcab8 */
 set(m,31u,UINT64_C(0x002ddfd8));STEP(UINT32_C(0x002ddfd4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffba94),&value32,4u);target=sx(UINT32_C(0x002dcab8));goto dispatch;
L_002ddfd4:
 STEP(UINT32_C(0x002ddfd4)); /* ac62ba94 sw v0,-0x456c(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffba94),&value32,4u);target=sx(UINT32_C(0x002ddfd8));goto dispatch;
L_002ddfd8:
 STEP(UINT32_C(0x002ddfd8)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002ddfdc));goto dispatch;
L_002ddfdc:
 STEP(UINT32_C(0x002ddfdc)); /* 0c0b70ac jal 002dc2b0 */
 set(m,31u,UINT64_C(0x002ddfe4));STEP(UINT32_C(0x002ddfe0));/* nop */target=sx(UINT32_C(0x002dc2b0));goto dispatch;
L_002ddfe0:
 STEP(UINT32_C(0x002ddfe0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ddfe4));goto dispatch;
L_002ddfe4:
 STEP(UINT32_C(0x002ddfe4)); /* 10400011 beq v0,zero,002de02c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002ddfe8));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(taken?UINT32_C(0x002de02c):UINT32_C(0x002ddfec));goto dispatch;}
L_002ddfe8:
 STEP(UINT32_C(0x002ddfe8)); /* ae220008 sw v0,0x8(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002ddfec));goto dispatch;
L_002ddfec:
 STEP(UINT32_C(0x002ddfec)); /* 2685ba80 addiu a1,s4,-17792 */
 set(m,5u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffba80)));target=sx(UINT32_C(0x002ddff0));goto dispatch;
L_002ddff0:
 STEP(UINT32_C(0x002ddff0)); /* 2662b9c0 addiu v0,s3,-17984 */
 set(m,2u,sx((uint32_t)lo(m,19u)+UINT32_C(0xffffb9c0)));target=sx(UINT32_C(0x002ddff4));goto dispatch;
L_002ddff4:
 STEP(UINT32_C(0x002ddff4)); /* dfbf0050 ld ra,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ddff8));goto dispatch;
L_002ddff8:
 STEP(UINT32_C(0x002ddff8)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002ddffc));goto dispatch;
L_002ddffc:
 STEP(UINT32_C(0x002ddffc)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002de000));goto dispatch;
L_002de000:
 STEP(UINT32_C(0x002de000)); /* 24060014 addiu a2,zero,20 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002de004));goto dispatch;
L_002de004:
 STEP(UINT32_C(0x002de004)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002de008));goto dispatch;
L_002de008:
 STEP(UINT32_C(0x002de008)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de00c));goto dispatch;
L_002de00c:
 STEP(UINT32_C(0x002de00c)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002de010));goto dispatch;
L_002de010:
 STEP(UINT32_C(0x002de010)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de014));goto dispatch;
L_002de014:
 STEP(UINT32_C(0x002de014)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002de018));goto dispatch;
L_002de018:
 STEP(UINT32_C(0x002de018)); /* 0000482d daddu t1,zero,zero */
 set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de01c));goto dispatch;
L_002de01c:
 STEP(UINT32_C(0x002de01c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de020));goto dispatch;
L_002de020:
 STEP(UINT32_C(0x002de020)); /* aca20010 sw v0,0x10(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002de024));goto dispatch;
L_002de024:
 STEP(UINT32_C(0x002de024)); /* 080b78ac j 002de2b0 */
 STEP(UINT32_C(0x002de028));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002de028:
 STEP(UINT32_C(0x002de028)); /* 27bd0060 addiu sp,sp,96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002de02c));goto dispatch;
L_002de02c:
 STEP(UINT32_C(0x002de02c)); /* 3c100002 lui s0,zero,0x2 */
 set(m,16u,sx(UINT32_C(0x00020000)));target=sx(UINT32_C(0x002de030));goto dispatch;
L_002de030:
 STEP(UINT32_C(0x002de030)); /* 0c0b70ac jal 002dc2b0 */
 set(m,31u,UINT64_C(0x002de038));STEP(UINT32_C(0x002de034));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002dc2b0));goto dispatch;
L_002de034:
 STEP(UINT32_C(0x002de034)); /* 24040004 addiu a0,zero,4 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002de038));goto dispatch;
L_002de038:
 STEP(UINT32_C(0x002de038)); /* 00501024 and v0,v0,s0 */
 set(m,2u,lo(m,2u)&lo(m,16u));target=sx(UINT32_C(0x002de03c));goto dispatch;
L_002de03c:
 STEP(UINT32_C(0x002de03c)); /* 1040fffc beq v0,zero,002de030 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002de040));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(taken?UINT32_C(0x002de030):UINT32_C(0x002de044));goto dispatch;}
L_002de040:
 STEP(UINT32_C(0x002de040)); /* 24040002 addiu a0,zero,2 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002de044));goto dispatch;
L_002de044:
 STEP(UINT32_C(0x002de044)); /* 0c0b70ac jal 002dc2b0 */
 set(m,31u,UINT64_C(0x002de04c));STEP(UINT32_C(0x002de048));set(m,16u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffffba98)));target=sx(UINT32_C(0x002dc2b0));goto dispatch;
L_002de048:
 STEP(UINT32_C(0x002de048)); /* 2650ba98 addiu s0,s2,-17768 */
 set(m,16u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffffba98)));target=sx(UINT32_C(0x002de04c));goto dispatch;
L_002de04c:
 STEP(UINT32_C(0x002de04c)); /* ae020008 sw v0,0x8(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002de050));goto dispatch;
L_002de050:
 STEP(UINT32_C(0x002de050)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de054));goto dispatch;
L_002de054:
 STEP(UINT32_C(0x002de054)); /* 0c0b70a8 jal 002dc2a0 */
 set(m,31u,UINT64_C(0x002de05c));STEP(UINT32_C(0x002de058));set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002dc2a0));goto dispatch;
L_002de058:
 STEP(UINT32_C(0x002de058)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002de05c));goto dispatch;
L_002de05c:
 STEP(UINT32_C(0x002de05c)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de060));goto dispatch;
L_002de060:
 STEP(UINT32_C(0x002de060)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002de064));goto dispatch;
L_002de064:
 STEP(UINT32_C(0x002de064)); /* 0c0b70a8 jal 002dc2a0 */
 set(m,31u,UINT64_C(0x002de06c));STEP(UINT32_C(0x002de068));set(m,4u,lo(m,4u) | UINT64_C(0x1));target=sx(UINT32_C(0x002dc2a0));goto dispatch;
L_002de068:
 STEP(UINT32_C(0x002de068)); /* 34840001 ori a0,a0,0x1 */
 set(m,4u,lo(m,4u) | UINT64_C(0x1));target=sx(UINT32_C(0x002de06c));goto dispatch;
L_002de06c:
 STEP(UINT32_C(0x002de06c)); /* 2683ba80 addiu v1,s4,-17792 */
 set(m,3u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffba80)));target=sx(UINT32_C(0x002de070));goto dispatch;
L_002de070:
 STEP(UINT32_C(0x002de070)); /* 2662b9c0 addiu v0,s3,-17984 */
 set(m,2u,sx((uint32_t)lo(m,19u)+UINT32_C(0xffffb9c0)));target=sx(UINT32_C(0x002de074));goto dispatch;
L_002de074:
 STEP(UINT32_C(0x002de074)); /* 3c048000 lui a0,zero,0x8000 */
 set(m,4u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002de078));goto dispatch;
L_002de078:
 STEP(UINT32_C(0x002de078)); /* dfbf0050 ld ra,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002de07c));goto dispatch;
L_002de07c:
 STEP(UINT32_C(0x002de07c)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002de080));goto dispatch;
L_002de080:
 STEP(UINT32_C(0x002de080)); /* 0060282d daddu a1,v1,zero */
 set(m,5u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002de084));goto dispatch;
L_002de084:
 STEP(UINT32_C(0x002de084)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002de088));goto dispatch;
L_002de088:
 STEP(UINT32_C(0x002de088)); /* 34840002 ori a0,a0,0x2 */
 set(m,4u,lo(m,4u) | UINT64_C(0x2));target=sx(UINT32_C(0x002de08c));goto dispatch;
L_002de08c:
 STEP(UINT32_C(0x002de08c)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002de090));goto dispatch;
L_002de090:
 STEP(UINT32_C(0x002de090)); /* 24060014 addiu a2,zero,20 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002de094));goto dispatch;
L_002de094:
 STEP(UINT32_C(0x002de094)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002de098));goto dispatch;
L_002de098:
 STEP(UINT32_C(0x002de098)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de09c));goto dispatch;
L_002de09c:
 STEP(UINT32_C(0x002de09c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002de0a0));goto dispatch;
L_002de0a0:
 STEP(UINT32_C(0x002de0a0)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de0a4));goto dispatch;
L_002de0a4:
 STEP(UINT32_C(0x002de0a4)); /* ac620010 sw v0,0x10(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002de0a8));goto dispatch;
L_002de0a8:
 STEP(UINT32_C(0x002de0a8)); /* 0000482d daddu t1,zero,zero */
 set(m,9u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de0ac));goto dispatch;
L_002de0ac:
 STEP(UINT32_C(0x002de0ac)); /* ac60000c sw zero,0xc(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002de0b0));goto dispatch;
L_002de0b0:
 STEP(UINT32_C(0x002de0b0)); /* 080b78ac j 002de2b0 */
 STEP(UINT32_C(0x002de0b4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002de2b0));goto dispatch;
L_002de0b4:
 STEP(UINT32_C(0x002de0b4)); /* 27bd0060 addiu sp,sp,96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002de0b8));goto dispatch;
L_002de120:
 STEP(UINT32_C(0x002de120)); /* 04810004 regimm1 a0,002de134 */
 {int taken=((int64_t)lo(m,4u)>=0);STEP(UINT32_C(0x002de124));set(m,3u,sx((uint32_t)lo(m,4u)<<3u));target=sx(taken?UINT32_C(0x002de134):UINT32_C(0x002de128));goto dispatch;}
L_002de124:
 STEP(UINT32_C(0x002de124)); /* 000418c0 sll v1,a0,3 */
 set(m,3u,sx((uint32_t)lo(m,4u)<<3u));target=sx(UINT32_C(0x002de128));goto dispatch;
L_002de128:
 STEP(UINT32_C(0x002de128)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002de12c));goto dispatch;
L_002de12c:
 STEP(UINT32_C(0x002de12c)); /* 10000003 beq zero,zero,002de13c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002de130));READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbaa4),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x002de13c):UINT32_C(0x002de134));goto dispatch;}
L_002de130:
 STEP(UINT32_C(0x002de130)); /* 8c44baa4 lw a0,-0x455c(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbaa4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de134));goto dispatch;
L_002de134:
 STEP(UINT32_C(0x002de134)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002de138));goto dispatch;
L_002de138:
 STEP(UINT32_C(0x002de138)); /* 8c44baac lw a0,-0x4554(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbaac),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002de13c));goto dispatch;
L_002de13c:
 STEP(UINT32_C(0x002de13c)); /* 00641821 addu v1,v1,a0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002de140));goto dispatch;
L_002de140:
 STEP(UINT32_C(0x002de140)); /* ac660004 sw a2,0x4(v1) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002de144));goto dispatch;
L_002de144:
 STEP(UINT32_C(0x002de144)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002de148));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_002de148:
 STEP(UINT32_C(0x002de148)); /* ac650000 sw a1,0x0(v1) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002de14c));goto dispatch;
L_002dcab8:
 STEP(UINT32_C(0x002dcab8)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002dcabc));goto dispatch;
L_002dcabc:
 STEP(UINT32_C(0x002dcabc)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dcac0));goto dispatch;
L_002dcac0:
 STEP(UINT32_C(0x002dcac0)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dcac4));goto dispatch;
L_002dcac4:
 STEP(UINT32_C(0x002dcac4)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002dcac8));goto dispatch;
L_002dcac8:
 STEP(UINT32_C(0x002dcac8)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dcacc));goto dispatch;
L_002dcacc:
 STEP(UINT32_C(0x002dcacc)); /* 40106000 cop0 rs0 rts0 rd12 fn0 */
 set(m,16u,sx(m->status));target=sx(UINT32_C(0x002dcad0));goto dispatch;
L_002dcad0:
 STEP(UINT32_C(0x002dcad0)); /* 3c020001 lui v0,zero,0x1 */
 set(m,2u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x002dcad4));goto dispatch;
L_002dcad4:
 STEP(UINT32_C(0x002dcad4)); /* 02028024 and s0,s0,v0 */
 set(m,16u,lo(m,16u)&lo(m,2u));target=sx(UINT32_C(0x002dcad8));goto dispatch;
L_002dcad8:
 STEP(UINT32_C(0x002dcad8)); /* 12000003 beq s0,zero,002dcae8 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002dcadc));/* nop */target=sx(taken?UINT32_C(0x002dcae8):UINT32_C(0x002dcae0));goto dispatch;}
L_002dcadc:
 STEP(UINT32_C(0x002dcadc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dcae0));goto dispatch;
L_002dcae0:
 STEP(UINT32_C(0x002dcae0)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002dcae8));STEP(UINT32_C(0x002dcae4));/* nop */target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002dcae4:
 STEP(UINT32_C(0x002dcae4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dcae8));goto dispatch;
L_002dcae8:
 STEP(UINT32_C(0x002dcae8)); /* 0c0b6f00 jal 002dbc00 */
 set(m,31u,UINT64_C(0x002dcaf0));STEP(UINT32_C(0x002dcaec));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dbc00));goto dispatch;
L_002dcaec:
 STEP(UINT32_C(0x002dcaec)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dcaf0));goto dispatch;
L_002dcaf0:
 STEP(UINT32_C(0x002dcaf0)); /* 0040882d daddu s1,v0,zero */
 set(m,17u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002dcaf4));goto dispatch;
L_002dcaf4:
 STEP(UINT32_C(0x002dcaf4)); /* 0000000f sync 0 */
 ++m->sync_p; /* Actual SYNC0, no external completion. */target=sx(UINT32_C(0x002dcaf8));goto dispatch;
L_002dcaf8:
 STEP(UINT32_C(0x002dcaf8)); /* 12000004 beq s0,zero,002dcb0c */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002dcafc));set(m,2u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dcb0c):UINT32_C(0x002dcb00));goto dispatch;}
L_002dcafc:
 STEP(UINT32_C(0x002dcafc)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dcb00));goto dispatch;
L_002dcb00:
 STEP(UINT32_C(0x002dcb00)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002dcb08));STEP(UINT32_C(0x002dcb04));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002dcb04:
 STEP(UINT32_C(0x002dcb04)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dcb08));goto dispatch;
L_002dcb08:
 STEP(UINT32_C(0x002dcb08)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dcb0c));goto dispatch;
L_002dcb0c:
 STEP(UINT32_C(0x002dcb0c)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dcb10));goto dispatch;
L_002dcb10:
 STEP(UINT32_C(0x002dcb10)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dcb14));goto dispatch;
L_002dcb14:
 STEP(UINT32_C(0x002dcb14)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dcb18));goto dispatch;
L_002dcb18:
 STEP(UINT32_C(0x002dcb18)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dcb1c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002dcb1c:
 STEP(UINT32_C(0x002dcb1c)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002dcb20));goto dispatch;
L_002dbbb0:
 STEP(UINT32_C(0x002dbbb0)); /* 24030012 addiu v1,zero,18 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000012)));target=sx(UINT32_C(0x002dbbb4));goto dispatch;
L_002dbbb4:
 m->pc=UINT32_C(0x002dbbb4); /* Unexecuted SYS; router owns exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbbb8:
 STEP(UINT32_C(0x002dbbb8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbbbc));/* nop */goto dispatch;
L_002dbbbc:
 STEP(UINT32_C(0x002dbbbc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbbc0));goto dispatch;
L_002dbc00:
 STEP(UINT32_C(0x002dbc00)); /* 24030016 addiu v1,zero,22 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000016)));target=sx(UINT32_C(0x002dbc04));goto dispatch;
L_002dbc04:
 m->pc=UINT32_C(0x002dbc04); /* Unexecuted SYS; router owns exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dbc08:
 STEP(UINT32_C(0x002dbc08)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dbc0c));/* nop */goto dispatch;
L_002dbc0c:
 STEP(UINT32_C(0x002dbc0c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dbc10));goto dispatch;
L_002dc280:
 STEP(UINT32_C(0x002dc280)); /* 24030078 addiu v1,zero,120 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000078)));target=sx(UINT32_C(0x002dc284));goto dispatch;
L_002dc284:
 m->pc=UINT32_C(0x002dc284); /* Unexecuted SYS; router owns exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dc288:
 STEP(UINT32_C(0x002dc288)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc28c));/* nop */goto dispatch;
L_002dc28c:
 STEP(UINT32_C(0x002dc28c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc290));goto dispatch;
L_002dc2a0:
 STEP(UINT32_C(0x002dc2a0)); /* 24030079 addiu v1,zero,121 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000079)));target=sx(UINT32_C(0x002dc2a4));goto dispatch;
L_002dc2a4:
 m->pc=UINT32_C(0x002dc2a4); /* Unexecuted SYS; router owns exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dc2a8:
 STEP(UINT32_C(0x002dc2a8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc2ac));/* nop */goto dispatch;
L_002dc2ac:
 STEP(UINT32_C(0x002dc2ac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc2b0));goto dispatch;
L_002dc2b0:
 STEP(UINT32_C(0x002dc2b0)); /* 2403007a addiu v1,zero,122 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007a)));target=sx(UINT32_C(0x002dc2b4));goto dispatch;
L_002dc2b4:
 m->pc=UINT32_C(0x002dc2b4); /* Unexecuted SYS; router owns exception entry. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dc2b8:
 STEP(UINT32_C(0x002dc2b8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc2bc));/* nop */goto dispatch;
L_002dc2bc:
 STEP(UINT32_C(0x002dc2bc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc2c0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

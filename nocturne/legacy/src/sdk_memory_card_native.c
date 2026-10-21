#include "sdk_memory_card_native.h"
#include <string.h>
/* Complete original retail memory-card client fixed statements. RAM and all MMIO are delegated
 * to the initialized memory owner; no INTC acknowledgement is synthesized.
 * The caller owns actual interrupt/SYSCALL entry, Cause/EPC/Status and clocks. */
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
uint32_t nocturneSdkMemoryCardResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002cdc90):goto L_002cdc90;
 case UINT32_C(0x002cdc94):goto L_002cdc94;
 case UINT32_C(0x002cdc98):goto L_002cdc98;
 case UINT32_C(0x002cdc9c):goto L_002cdc9c;
 case UINT32_C(0x002cdca0):goto L_002cdca0;
 case UINT32_C(0x002cdca4):goto L_002cdca4;
 case UINT32_C(0x002cdca8):goto L_002cdca8;
 case UINT32_C(0x002cdcac):goto L_002cdcac;
 case UINT32_C(0x002cdcb0):goto L_002cdcb0;
 case UINT32_C(0x002cdcb4):goto L_002cdcb4;
 case UINT32_C(0x002cdcb8):goto L_002cdcb8;
 case UINT32_C(0x002cdcbc):goto L_002cdcbc;
 case UINT32_C(0x002cdcc0):goto L_002cdcc0;
 case UINT32_C(0x002cdcc4):goto L_002cdcc4;
 case UINT32_C(0x002cdcc8):goto L_002cdcc8;
 case UINT32_C(0x002cdccc):goto L_002cdccc;
 case UINT32_C(0x002cdcd0):goto L_002cdcd0;
 case UINT32_C(0x002cdcd4):goto L_002cdcd4;
 case UINT32_C(0x002cdcd8):goto L_002cdcd8;
 case UINT32_C(0x002cdcdc):goto L_002cdcdc;
 case UINT32_C(0x002cdce0):goto L_002cdce0;
 case UINT32_C(0x002cdce4):goto L_002cdce4;
 case UINT32_C(0x002cdce8):goto L_002cdce8;
 case UINT32_C(0x002cdcec):goto L_002cdcec;
 case UINT32_C(0x002cdcf0):goto L_002cdcf0;
 case UINT32_C(0x002cdcf4):goto L_002cdcf4;
 case UINT32_C(0x002cdcf8):goto L_002cdcf8;
 case UINT32_C(0x002cdcfc):goto L_002cdcfc;
 case UINT32_C(0x002cdd00):goto L_002cdd00;
 case UINT32_C(0x002cdd04):goto L_002cdd04;
 case UINT32_C(0x002cdd08):goto L_002cdd08;
 case UINT32_C(0x002cdd0c):goto L_002cdd0c;
 case UINT32_C(0x002cdd10):goto L_002cdd10;
 case UINT32_C(0x002cdd14):goto L_002cdd14;
 case UINT32_C(0x002cdd18):goto L_002cdd18;
 case UINT32_C(0x002cdd1c):goto L_002cdd1c;
 case UINT32_C(0x002cdd20):goto L_002cdd20;
 case UINT32_C(0x002cdd24):goto L_002cdd24;
 case UINT32_C(0x002cdd28):goto L_002cdd28;
 case UINT32_C(0x002cdd2c):goto L_002cdd2c;
 case UINT32_C(0x002cdd30):goto L_002cdd30;
 case UINT32_C(0x002cdd34):goto L_002cdd34;
 case UINT32_C(0x002cdd38):goto L_002cdd38;
 case UINT32_C(0x002cdd3c):goto L_002cdd3c;
 case UINT32_C(0x002cdd40):goto L_002cdd40;
 case UINT32_C(0x002cdd44):goto L_002cdd44;
 case UINT32_C(0x002cdd48):goto L_002cdd48;
 case UINT32_C(0x002cdd4c):goto L_002cdd4c;
 case UINT32_C(0x002cdd50):goto L_002cdd50;
 case UINT32_C(0x002cdd54):goto L_002cdd54;
 case UINT32_C(0x002cdd58):goto L_002cdd58;
 case UINT32_C(0x002cdd5c):goto L_002cdd5c;
 case UINT32_C(0x002cdd60):goto L_002cdd60;
 case UINT32_C(0x002cdd64):goto L_002cdd64;
 case UINT32_C(0x002cdd68):goto L_002cdd68;
 case UINT32_C(0x002cdd6c):goto L_002cdd6c;
 case UINT32_C(0x002cdd70):goto L_002cdd70;
 case UINT32_C(0x002cdd74):goto L_002cdd74;
 case UINT32_C(0x002cdd78):goto L_002cdd78;
 case UINT32_C(0x002cdd7c):goto L_002cdd7c;
 case UINT32_C(0x002cdd80):goto L_002cdd80;
 case UINT32_C(0x002cdd84):goto L_002cdd84;
 case UINT32_C(0x002cdd88):goto L_002cdd88;
 case UINT32_C(0x002cdd8c):goto L_002cdd8c;
 case UINT32_C(0x002cdd90):goto L_002cdd90;
 case UINT32_C(0x002cdd94):goto L_002cdd94;
 case UINT32_C(0x002cdd98):goto L_002cdd98;
 case UINT32_C(0x002cdd9c):goto L_002cdd9c;
 case UINT32_C(0x002cdda0):goto L_002cdda0;
 case UINT32_C(0x002cdda4):goto L_002cdda4;
 case UINT32_C(0x002cdda8):goto L_002cdda8;
 case UINT32_C(0x002cddac):goto L_002cddac;
 case UINT32_C(0x002cddb0):goto L_002cddb0;
 case UINT32_C(0x002cddb4):goto L_002cddb4;
 case UINT32_C(0x002cddb8):goto L_002cddb8;
 case UINT32_C(0x002cddbc):goto L_002cddbc;
 case UINT32_C(0x002cddc0):goto L_002cddc0;
 case UINT32_C(0x002cddc4):goto L_002cddc4;
 case UINT32_C(0x002cddc8):goto L_002cddc8;
 case UINT32_C(0x002cddcc):goto L_002cddcc;
 case UINT32_C(0x002cddd0):goto L_002cddd0;
 case UINT32_C(0x002cddd4):goto L_002cddd4;
 case UINT32_C(0x002cddd8):goto L_002cddd8;
 case UINT32_C(0x002cdddc):goto L_002cdddc;
 case UINT32_C(0x002cdde0):goto L_002cdde0;
 case UINT32_C(0x002cdde4):goto L_002cdde4;
 case UINT32_C(0x002cdde8):goto L_002cdde8;
 case UINT32_C(0x002cddec):goto L_002cddec;
 case UINT32_C(0x002cddf0):goto L_002cddf0;
 case UINT32_C(0x002cddf4):goto L_002cddf4;
 case UINT32_C(0x002cddf8):goto L_002cddf8;
 case UINT32_C(0x002cddfc):goto L_002cddfc;
 case UINT32_C(0x002cde00):goto L_002cde00;
 case UINT32_C(0x002cde04):goto L_002cde04;
 case UINT32_C(0x002cde08):goto L_002cde08;
 case UINT32_C(0x002cde0c):goto L_002cde0c;
 case UINT32_C(0x002cde10):goto L_002cde10;
 case UINT32_C(0x002cde14):goto L_002cde14;
 case UINT32_C(0x002cde18):goto L_002cde18;
 case UINT32_C(0x002cde1c):goto L_002cde1c;
 case UINT32_C(0x002cde20):goto L_002cde20;
 case UINT32_C(0x002cde24):goto L_002cde24;
 case UINT32_C(0x002cde28):goto L_002cde28;
 case UINT32_C(0x002cde2c):goto L_002cde2c;
 case UINT32_C(0x002cde30):goto L_002cde30;
 case UINT32_C(0x002cde34):goto L_002cde34;
 case UINT32_C(0x002cde38):goto L_002cde38;
 case UINT32_C(0x002cde3c):goto L_002cde3c;
 case UINT32_C(0x002cde40):goto L_002cde40;
 case UINT32_C(0x002cde48):goto L_002cde48;
 case UINT32_C(0x002cde4c):goto L_002cde4c;
 case UINT32_C(0x002cde50):goto L_002cde50;
 case UINT32_C(0x002cde54):goto L_002cde54;
 case UINT32_C(0x002cde58):goto L_002cde58;
 case UINT32_C(0x002cde5c):goto L_002cde5c;
 case UINT32_C(0x002cde60):goto L_002cde60;
 case UINT32_C(0x002cde64):goto L_002cde64;
 case UINT32_C(0x002cde68):goto L_002cde68;
 case UINT32_C(0x002cde6c):goto L_002cde6c;
 case UINT32_C(0x002cde70):goto L_002cde70;
 case UINT32_C(0x002cde74):goto L_002cde74;
 case UINT32_C(0x002cde78):goto L_002cde78;
 case UINT32_C(0x002cde7c):goto L_002cde7c;
 case UINT32_C(0x002cde80):goto L_002cde80;
 case UINT32_C(0x002cde84):goto L_002cde84;
 case UINT32_C(0x002cde88):goto L_002cde88;
 case UINT32_C(0x002cde8c):goto L_002cde8c;
 case UINT32_C(0x002cde90):goto L_002cde90;
 case UINT32_C(0x002cde94):goto L_002cde94;
 case UINT32_C(0x002cde98):goto L_002cde98;
 case UINT32_C(0x002cde9c):goto L_002cde9c;
 case UINT32_C(0x002cdea0):goto L_002cdea0;
 case UINT32_C(0x002cdea4):goto L_002cdea4;
 case UINT32_C(0x002cdea8):goto L_002cdea8;
 case UINT32_C(0x002cdeac):goto L_002cdeac;
 case UINT32_C(0x002cdeb0):goto L_002cdeb0;
 case UINT32_C(0x002cdeb4):goto L_002cdeb4;
 case UINT32_C(0x002cdeb8):goto L_002cdeb8;
 case UINT32_C(0x002cdebc):goto L_002cdebc;
 case UINT32_C(0x002cdec0):goto L_002cdec0;
 case UINT32_C(0x002cdec4):goto L_002cdec4;
 case UINT32_C(0x002cdec8):goto L_002cdec8;
 case UINT32_C(0x002cdecc):goto L_002cdecc;
 case UINT32_C(0x002cded0):goto L_002cded0;
 case UINT32_C(0x002cded4):goto L_002cded4;
 case UINT32_C(0x002cded8):goto L_002cded8;
 case UINT32_C(0x002cdedc):goto L_002cdedc;
 case UINT32_C(0x002cdee0):goto L_002cdee0;
 case UINT32_C(0x002cdee4):goto L_002cdee4;
 case UINT32_C(0x002cdee8):goto L_002cdee8;
 case UINT32_C(0x002cdeec):goto L_002cdeec;
 case UINT32_C(0x002cdef0):goto L_002cdef0;
 case UINT32_C(0x002cdef4):goto L_002cdef4;
 case UINT32_C(0x002cdef8):goto L_002cdef8;
 case UINT32_C(0x002cdefc):goto L_002cdefc;
 case UINT32_C(0x002cdf00):goto L_002cdf00;
 case UINT32_C(0x002cdf04):goto L_002cdf04;
 case UINT32_C(0x002cdf08):goto L_002cdf08;
 case UINT32_C(0x002cdf0c):goto L_002cdf0c;
 case UINT32_C(0x002cdf10):goto L_002cdf10;
 case UINT32_C(0x002cdf14):goto L_002cdf14;
 case UINT32_C(0x002cdf18):goto L_002cdf18;
 case UINT32_C(0x002cdf1c):goto L_002cdf1c;
 case UINT32_C(0x002cdf20):goto L_002cdf20;
 case UINT32_C(0x002cdf24):goto L_002cdf24;
 case UINT32_C(0x002cdf28):goto L_002cdf28;
 case UINT32_C(0x002cdf2c):goto L_002cdf2c;
 case UINT32_C(0x002cdf30):goto L_002cdf30;
 case UINT32_C(0x002cdf34):goto L_002cdf34;
 case UINT32_C(0x002cdf38):goto L_002cdf38;
 case UINT32_C(0x002cdf3c):goto L_002cdf3c;
 case UINT32_C(0x002cdf40):goto L_002cdf40;
 case UINT32_C(0x002cdf44):goto L_002cdf44;
 case UINT32_C(0x002cdf48):goto L_002cdf48;
 case UINT32_C(0x002cdf4c):goto L_002cdf4c;
 case UINT32_C(0x002cdf50):goto L_002cdf50;
 case UINT32_C(0x002cdf54):goto L_002cdf54;
 case UINT32_C(0x002cdf58):goto L_002cdf58;
 case UINT32_C(0x002cdf5c):goto L_002cdf5c;
 case UINT32_C(0x002cdf60):goto L_002cdf60;
 case UINT32_C(0x002cdf64):goto L_002cdf64;
 case UINT32_C(0x002cdf68):goto L_002cdf68;
 case UINT32_C(0x002cdf70):goto L_002cdf70;
 case UINT32_C(0x002cdf74):goto L_002cdf74;
 case UINT32_C(0x002cdf78):goto L_002cdf78;
 case UINT32_C(0x002cdf7c):goto L_002cdf7c;
 case UINT32_C(0x002cdf80):goto L_002cdf80;
 case UINT32_C(0x002cdf84):goto L_002cdf84;
 case UINT32_C(0x002cdf88):goto L_002cdf88;
 case UINT32_C(0x002cdf8c):goto L_002cdf8c;
 case UINT32_C(0x002cdf90):goto L_002cdf90;
 case UINT32_C(0x002cdf94):goto L_002cdf94;
 case UINT32_C(0x002cdf98):goto L_002cdf98;
 case UINT32_C(0x002cdf9c):goto L_002cdf9c;
 case UINT32_C(0x002cdfa0):goto L_002cdfa0;
 case UINT32_C(0x002cdfa4):goto L_002cdfa4;
 case UINT32_C(0x002cdfa8):goto L_002cdfa8;
 case UINT32_C(0x002cdfac):goto L_002cdfac;
 case UINT32_C(0x002cdfb0):goto L_002cdfb0;
 case UINT32_C(0x002cdfb4):goto L_002cdfb4;
 case UINT32_C(0x002cdfb8):goto L_002cdfb8;
 case UINT32_C(0x002cdfbc):goto L_002cdfbc;
 case UINT32_C(0x002cdfc0):goto L_002cdfc0;
 case UINT32_C(0x002cdfc4):goto L_002cdfc4;
 case UINT32_C(0x002cdfc8):goto L_002cdfc8;
 case UINT32_C(0x002cdfcc):goto L_002cdfcc;
 case UINT32_C(0x002cdfd0):goto L_002cdfd0;
 case UINT32_C(0x002cdfd4):goto L_002cdfd4;
 case UINT32_C(0x002cdfd8):goto L_002cdfd8;
 case UINT32_C(0x002cdfdc):goto L_002cdfdc;
 case UINT32_C(0x002cdfe0):goto L_002cdfe0;
 case UINT32_C(0x002cdfe4):goto L_002cdfe4;
 case UINT32_C(0x002cdfe8):goto L_002cdfe8;
 case UINT32_C(0x002cdfec):goto L_002cdfec;
 case UINT32_C(0x002cdff0):goto L_002cdff0;
 case UINT32_C(0x002cdff4):goto L_002cdff4;
 case UINT32_C(0x002cdff8):goto L_002cdff8;
 case UINT32_C(0x002cdffc):goto L_002cdffc;
 case UINT32_C(0x002ce000):goto L_002ce000;
 case UINT32_C(0x002ce004):goto L_002ce004;
 case UINT32_C(0x002ce008):goto L_002ce008;
 case UINT32_C(0x002ce00c):goto L_002ce00c;
 case UINT32_C(0x002ce010):goto L_002ce010;
 case UINT32_C(0x002ce014):goto L_002ce014;
 case UINT32_C(0x002ce018):goto L_002ce018;
 case UINT32_C(0x002ce01c):goto L_002ce01c;
 case UINT32_C(0x002ce020):goto L_002ce020;
 case UINT32_C(0x002ce024):goto L_002ce024;
 case UINT32_C(0x002ce028):goto L_002ce028;
 case UINT32_C(0x002ce02c):goto L_002ce02c;
 case UINT32_C(0x002ce030):goto L_002ce030;
 case UINT32_C(0x002ce034):goto L_002ce034;
 case UINT32_C(0x002ce038):goto L_002ce038;
 case UINT32_C(0x002ce03c):goto L_002ce03c;
 case UINT32_C(0x002ce040):goto L_002ce040;
 case UINT32_C(0x002ce044):goto L_002ce044;
 case UINT32_C(0x002ce048):goto L_002ce048;
 case UINT32_C(0x002ce04c):goto L_002ce04c;
 case UINT32_C(0x002ce050):goto L_002ce050;
 case UINT32_C(0x002ce054):goto L_002ce054;
 case UINT32_C(0x002ce058):goto L_002ce058;
 case UINT32_C(0x002ce05c):goto L_002ce05c;
 case UINT32_C(0x002ce060):goto L_002ce060;
 case UINT32_C(0x002ce064):goto L_002ce064;
 case UINT32_C(0x002ce068):goto L_002ce068;
 case UINT32_C(0x002ce06c):goto L_002ce06c;
 case UINT32_C(0x002ce070):goto L_002ce070;
 case UINT32_C(0x002ce074):goto L_002ce074;
 case UINT32_C(0x002ce078):goto L_002ce078;
 case UINT32_C(0x002ce07c):goto L_002ce07c;
 case UINT32_C(0x002ce080):goto L_002ce080;
 case UINT32_C(0x002ce084):goto L_002ce084;
 case UINT32_C(0x002ce088):goto L_002ce088;
 case UINT32_C(0x002ce08c):goto L_002ce08c;
 case UINT32_C(0x002ce090):goto L_002ce090;
 case UINT32_C(0x002ce094):goto L_002ce094;
 case UINT32_C(0x002ce098):goto L_002ce098;
 case UINT32_C(0x002ce09c):goto L_002ce09c;
 case UINT32_C(0x002ce0a0):goto L_002ce0a0;
 case UINT32_C(0x002ce0a4):goto L_002ce0a4;
 case UINT32_C(0x002ce0a8):goto L_002ce0a8;
 case UINT32_C(0x002ce0ac):goto L_002ce0ac;
 case UINT32_C(0x002ce0b0):goto L_002ce0b0;
 case UINT32_C(0x002ce0b4):goto L_002ce0b4;
 case UINT32_C(0x002ce0b8):goto L_002ce0b8;
 case UINT32_C(0x002ce0bc):goto L_002ce0bc;
 case UINT32_C(0x002ce0c0):goto L_002ce0c0;
 case UINT32_C(0x002ce0c4):goto L_002ce0c4;
 case UINT32_C(0x002ce0c8):goto L_002ce0c8;
 case UINT32_C(0x002ce0cc):goto L_002ce0cc;
 case UINT32_C(0x002ce0d0):goto L_002ce0d0;
 case UINT32_C(0x002ce0d4):goto L_002ce0d4;
 case UINT32_C(0x002ce0d8):goto L_002ce0d8;
 case UINT32_C(0x002ce0dc):goto L_002ce0dc;
 case UINT32_C(0x002ce0e0):goto L_002ce0e0;
 case UINT32_C(0x002ce0e4):goto L_002ce0e4;
 case UINT32_C(0x002ce0e8):goto L_002ce0e8;
 case UINT32_C(0x002ce0ec):goto L_002ce0ec;
 case UINT32_C(0x002ce0f0):goto L_002ce0f0;
 case UINT32_C(0x002ce0f4):goto L_002ce0f4;
 case UINT32_C(0x002ce0f8):goto L_002ce0f8;
 case UINT32_C(0x002ce0fc):goto L_002ce0fc;
 case UINT32_C(0x002ce100):goto L_002ce100;
 case UINT32_C(0x002ce104):goto L_002ce104;
 case UINT32_C(0x002ce108):goto L_002ce108;
 case UINT32_C(0x002ce10c):goto L_002ce10c;
 case UINT32_C(0x002ce110):goto L_002ce110;
 case UINT32_C(0x002ce114):goto L_002ce114;
 case UINT32_C(0x002ce118):goto L_002ce118;
 case UINT32_C(0x002ce11c):goto L_002ce11c;
 case UINT32_C(0x002ce120):goto L_002ce120;
 case UINT32_C(0x002ce124):goto L_002ce124;
 case UINT32_C(0x002ce128):goto L_002ce128;
 case UINT32_C(0x002ce12c):goto L_002ce12c;
 case UINT32_C(0x002ce130):goto L_002ce130;
 case UINT32_C(0x002ce134):goto L_002ce134;
 case UINT32_C(0x002ce138):goto L_002ce138;
 case UINT32_C(0x002ce13c):goto L_002ce13c;
 case UINT32_C(0x002ce140):goto L_002ce140;
 case UINT32_C(0x002ce144):goto L_002ce144;
 case UINT32_C(0x002ce148):goto L_002ce148;
 case UINT32_C(0x002ce14c):goto L_002ce14c;
 case UINT32_C(0x002ce150):goto L_002ce150;
 case UINT32_C(0x002ce154):goto L_002ce154;
 case UINT32_C(0x002ce158):goto L_002ce158;
 case UINT32_C(0x002ce15c):goto L_002ce15c;
 case UINT32_C(0x002ce160):goto L_002ce160;
 case UINT32_C(0x002ce168):goto L_002ce168;
 case UINT32_C(0x002ce16c):goto L_002ce16c;
 case UINT32_C(0x002ce170):goto L_002ce170;
 case UINT32_C(0x002ce174):goto L_002ce174;
 case UINT32_C(0x002ce178):goto L_002ce178;
 case UINT32_C(0x002ce17c):goto L_002ce17c;
 case UINT32_C(0x002ce180):goto L_002ce180;
 case UINT32_C(0x002ce184):goto L_002ce184;
 case UINT32_C(0x002ce188):goto L_002ce188;
 case UINT32_C(0x002ce18c):goto L_002ce18c;
 case UINT32_C(0x002ce190):goto L_002ce190;
 case UINT32_C(0x002ce194):goto L_002ce194;
 case UINT32_C(0x002ce198):goto L_002ce198;
 case UINT32_C(0x002ce1a0):goto L_002ce1a0;
 case UINT32_C(0x002ce1a4):goto L_002ce1a4;
 case UINT32_C(0x002ce1a8):goto L_002ce1a8;
 case UINT32_C(0x002ce1ac):goto L_002ce1ac;
 case UINT32_C(0x002ce1b0):goto L_002ce1b0;
 case UINT32_C(0x002ce1b4):goto L_002ce1b4;
 case UINT32_C(0x002ce1b8):goto L_002ce1b8;
 case UINT32_C(0x002ce1bc):goto L_002ce1bc;
 case UINT32_C(0x002ce1c0):goto L_002ce1c0;
 case UINT32_C(0x002ce1c4):goto L_002ce1c4;
 case UINT32_C(0x002ce1c8):goto L_002ce1c8;
 case UINT32_C(0x002ce1cc):goto L_002ce1cc;
 case UINT32_C(0x002ce1d0):goto L_002ce1d0;
 case UINT32_C(0x002ce1d4):goto L_002ce1d4;
 case UINT32_C(0x002ce1d8):goto L_002ce1d8;
 case UINT32_C(0x002ce1dc):goto L_002ce1dc;
 case UINT32_C(0x002ce1e0):goto L_002ce1e0;
 case UINT32_C(0x002ce1e4):goto L_002ce1e4;
 case UINT32_C(0x002ce1e8):goto L_002ce1e8;
 case UINT32_C(0x002ce1ec):goto L_002ce1ec;
 case UINT32_C(0x002ce1f0):goto L_002ce1f0;
 case UINT32_C(0x002ce1f4):goto L_002ce1f4;
 case UINT32_C(0x002ce1f8):goto L_002ce1f8;
 case UINT32_C(0x002ce1fc):goto L_002ce1fc;
 case UINT32_C(0x002ce200):goto L_002ce200;
 case UINT32_C(0x002ce204):goto L_002ce204;
 case UINT32_C(0x002ce208):goto L_002ce208;
 case UINT32_C(0x002ce20c):goto L_002ce20c;
 case UINT32_C(0x002ce210):goto L_002ce210;
 case UINT32_C(0x002ce214):goto L_002ce214;
 case UINT32_C(0x002ce218):goto L_002ce218;
 case UINT32_C(0x002ce21c):goto L_002ce21c;
 case UINT32_C(0x002ce220):goto L_002ce220;
 case UINT32_C(0x002ce224):goto L_002ce224;
 case UINT32_C(0x002ce228):goto L_002ce228;
 case UINT32_C(0x002ce22c):goto L_002ce22c;
 case UINT32_C(0x002ce230):goto L_002ce230;
 case UINT32_C(0x002ce234):goto L_002ce234;
 case UINT32_C(0x002ce238):goto L_002ce238;
 case UINT32_C(0x002ce23c):goto L_002ce23c;
 case UINT32_C(0x002ce240):goto L_002ce240;
 case UINT32_C(0x002ce244):goto L_002ce244;
 case UINT32_C(0x002ce248):goto L_002ce248;
 case UINT32_C(0x002ce24c):goto L_002ce24c;
 case UINT32_C(0x002ce250):goto L_002ce250;
 case UINT32_C(0x002ce258):goto L_002ce258;
 case UINT32_C(0x002ce25c):goto L_002ce25c;
 case UINT32_C(0x002ce260):goto L_002ce260;
 case UINT32_C(0x002ce264):goto L_002ce264;
 case UINT32_C(0x002ce268):goto L_002ce268;
 case UINT32_C(0x002ce26c):goto L_002ce26c;
 case UINT32_C(0x002ce270):goto L_002ce270;
 case UINT32_C(0x002ce274):goto L_002ce274;
 case UINT32_C(0x002ce278):goto L_002ce278;
 case UINT32_C(0x002ce27c):goto L_002ce27c;
 case UINT32_C(0x002ce280):goto L_002ce280;
 case UINT32_C(0x002ce284):goto L_002ce284;
 case UINT32_C(0x002ce288):goto L_002ce288;
 case UINT32_C(0x002ce28c):goto L_002ce28c;
 case UINT32_C(0x002ce290):goto L_002ce290;
 case UINT32_C(0x002ce294):goto L_002ce294;
 case UINT32_C(0x002ce298):goto L_002ce298;
 case UINT32_C(0x002ce29c):goto L_002ce29c;
 case UINT32_C(0x002ce2a0):goto L_002ce2a0;
 case UINT32_C(0x002ce2a4):goto L_002ce2a4;
 case UINT32_C(0x002ce2a8):goto L_002ce2a8;
 case UINT32_C(0x002ce2ac):goto L_002ce2ac;
 case UINT32_C(0x002ce2b0):goto L_002ce2b0;
 case UINT32_C(0x002ce2b4):goto L_002ce2b4;
 case UINT32_C(0x002ce2b8):goto L_002ce2b8;
 case UINT32_C(0x002ce2bc):goto L_002ce2bc;
 case UINT32_C(0x002ce2c0):goto L_002ce2c0;
 case UINT32_C(0x002ce2c4):goto L_002ce2c4;
 case UINT32_C(0x002ce2c8):goto L_002ce2c8;
 case UINT32_C(0x002ce2cc):goto L_002ce2cc;
 case UINT32_C(0x002ce2d0):goto L_002ce2d0;
 case UINT32_C(0x002ce2d4):goto L_002ce2d4;
 case UINT32_C(0x002ce2d8):goto L_002ce2d8;
 case UINT32_C(0x002ce2dc):goto L_002ce2dc;
 case UINT32_C(0x002ce2e0):goto L_002ce2e0;
 case UINT32_C(0x002ce2e4):goto L_002ce2e4;
 case UINT32_C(0x002ce2e8):goto L_002ce2e8;
 case UINT32_C(0x002ce2ec):goto L_002ce2ec;
 case UINT32_C(0x002ce2f0):goto L_002ce2f0;
 case UINT32_C(0x002ce2f4):goto L_002ce2f4;
 case UINT32_C(0x002ce2f8):goto L_002ce2f8;
 case UINT32_C(0x002ce2fc):goto L_002ce2fc;
 case UINT32_C(0x002ce300):goto L_002ce300;
 case UINT32_C(0x002ce304):goto L_002ce304;
 case UINT32_C(0x002ce308):goto L_002ce308;
 case UINT32_C(0x002ce30c):goto L_002ce30c;
 case UINT32_C(0x002ce310):goto L_002ce310;
 case UINT32_C(0x002ce314):goto L_002ce314;
 case UINT32_C(0x002ce318):goto L_002ce318;
 case UINT32_C(0x002ce31c):goto L_002ce31c;
 case UINT32_C(0x002ce320):goto L_002ce320;
 case UINT32_C(0x002ce324):goto L_002ce324;
 case UINT32_C(0x002ce328):goto L_002ce328;
 case UINT32_C(0x002ce330):goto L_002ce330;
 case UINT32_C(0x002ce334):goto L_002ce334;
 case UINT32_C(0x002ce338):goto L_002ce338;
 case UINT32_C(0x002ce33c):goto L_002ce33c;
 case UINT32_C(0x002ce340):goto L_002ce340;
 case UINT32_C(0x002ce344):goto L_002ce344;
 case UINT32_C(0x002ce348):goto L_002ce348;
 case UINT32_C(0x002ce34c):goto L_002ce34c;
 case UINT32_C(0x002ce350):goto L_002ce350;
 case UINT32_C(0x002ce354):goto L_002ce354;
 case UINT32_C(0x002ce358):goto L_002ce358;
 case UINT32_C(0x002ce35c):goto L_002ce35c;
 case UINT32_C(0x002ce360):goto L_002ce360;
 case UINT32_C(0x002ce364):goto L_002ce364;
 case UINT32_C(0x002ce368):goto L_002ce368;
 case UINT32_C(0x002ce36c):goto L_002ce36c;
 case UINT32_C(0x002ce370):goto L_002ce370;
 case UINT32_C(0x002ce374):goto L_002ce374;
 case UINT32_C(0x002ce378):goto L_002ce378;
 case UINT32_C(0x002ce37c):goto L_002ce37c;
 case UINT32_C(0x002ce380):goto L_002ce380;
 case UINT32_C(0x002ce384):goto L_002ce384;
 case UINT32_C(0x002ce388):goto L_002ce388;
 case UINT32_C(0x002ce38c):goto L_002ce38c;
 case UINT32_C(0x002ce390):goto L_002ce390;
 case UINT32_C(0x002ce394):goto L_002ce394;
 case UINT32_C(0x002ce398):goto L_002ce398;
 case UINT32_C(0x002ce39c):goto L_002ce39c;
 case UINT32_C(0x002ce3a0):goto L_002ce3a0;
 case UINT32_C(0x002ce3a4):goto L_002ce3a4;
 case UINT32_C(0x002ce3a8):goto L_002ce3a8;
 case UINT32_C(0x002ce3ac):goto L_002ce3ac;
 case UINT32_C(0x002ce3b0):goto L_002ce3b0;
 case UINT32_C(0x002ce3b4):goto L_002ce3b4;
 case UINT32_C(0x002ce3b8):goto L_002ce3b8;
 case UINT32_C(0x002ce3bc):goto L_002ce3bc;
 case UINT32_C(0x002ce3c0):goto L_002ce3c0;
 case UINT32_C(0x002ce3c4):goto L_002ce3c4;
 case UINT32_C(0x002ce3c8):goto L_002ce3c8;
 case UINT32_C(0x002ce3cc):goto L_002ce3cc;
 case UINT32_C(0x002ce3d0):goto L_002ce3d0;
 case UINT32_C(0x002ce3d4):goto L_002ce3d4;
 case UINT32_C(0x002ce3d8):goto L_002ce3d8;
 case UINT32_C(0x002ce3dc):goto L_002ce3dc;
 case UINT32_C(0x002ce3e0):goto L_002ce3e0;
 case UINT32_C(0x002ce3e4):goto L_002ce3e4;
 case UINT32_C(0x002ce3e8):goto L_002ce3e8;
 case UINT32_C(0x002ce3ec):goto L_002ce3ec;
 case UINT32_C(0x002ce3f0):goto L_002ce3f0;
 case UINT32_C(0x002ce3f4):goto L_002ce3f4;
 case UINT32_C(0x002ce3f8):goto L_002ce3f8;
 case UINT32_C(0x002ce3fc):goto L_002ce3fc;
 case UINT32_C(0x002ce400):goto L_002ce400;
 case UINT32_C(0x002ce404):goto L_002ce404;
 case UINT32_C(0x002ce408):goto L_002ce408;
 case UINT32_C(0x002ce40c):goto L_002ce40c;
 case UINT32_C(0x002ce410):goto L_002ce410;
 case UINT32_C(0x002ce414):goto L_002ce414;
 case UINT32_C(0x002ce418):goto L_002ce418;
 case UINT32_C(0x002ce41c):goto L_002ce41c;
 case UINT32_C(0x002ce420):goto L_002ce420;
 case UINT32_C(0x002ce424):goto L_002ce424;
 case UINT32_C(0x002ce428):goto L_002ce428;
 case UINT32_C(0x002ce42c):goto L_002ce42c;
 case UINT32_C(0x002ce430):goto L_002ce430;
 case UINT32_C(0x002ce434):goto L_002ce434;
 case UINT32_C(0x002ce438):goto L_002ce438;
 case UINT32_C(0x002ce43c):goto L_002ce43c;
 case UINT32_C(0x002ce440):goto L_002ce440;
 case UINT32_C(0x002ce444):goto L_002ce444;
 case UINT32_C(0x002ce448):goto L_002ce448;
 case UINT32_C(0x002ce44c):goto L_002ce44c;
 case UINT32_C(0x002ce450):goto L_002ce450;
 case UINT32_C(0x002ce454):goto L_002ce454;
 case UINT32_C(0x002ce458):goto L_002ce458;
 case UINT32_C(0x002ce45c):goto L_002ce45c;
 case UINT32_C(0x002ce460):goto L_002ce460;
 case UINT32_C(0x002ce464):goto L_002ce464;
 case UINT32_C(0x002ce468):goto L_002ce468;
 case UINT32_C(0x002ce46c):goto L_002ce46c;
 case UINT32_C(0x002ce470):goto L_002ce470;
 case UINT32_C(0x002ce474):goto L_002ce474;
 case UINT32_C(0x002ce478):goto L_002ce478;
 case UINT32_C(0x002ce47c):goto L_002ce47c;
 case UINT32_C(0x002ce480):goto L_002ce480;
 case UINT32_C(0x002ce484):goto L_002ce484;
 case UINT32_C(0x002ce488):goto L_002ce488;
 case UINT32_C(0x002ce48c):goto L_002ce48c;
 case UINT32_C(0x002ce490):goto L_002ce490;
 case UINT32_C(0x002ce494):goto L_002ce494;
 case UINT32_C(0x002ce498):goto L_002ce498;
 case UINT32_C(0x002ce49c):goto L_002ce49c;
 case UINT32_C(0x002ce4a0):goto L_002ce4a0;
 case UINT32_C(0x002ce4a4):goto L_002ce4a4;
 case UINT32_C(0x002ce4a8):goto L_002ce4a8;
 case UINT32_C(0x002ce4ac):goto L_002ce4ac;
 case UINT32_C(0x002ce4b0):goto L_002ce4b0;
 case UINT32_C(0x002ce4b4):goto L_002ce4b4;
 case UINT32_C(0x002ce4b8):goto L_002ce4b8;
 case UINT32_C(0x002ce4bc):goto L_002ce4bc;
 case UINT32_C(0x002ce4c0):goto L_002ce4c0;
 case UINT32_C(0x002ce4c4):goto L_002ce4c4;
 case UINT32_C(0x002ce4c8):goto L_002ce4c8;
 case UINT32_C(0x002ce4cc):goto L_002ce4cc;
 case UINT32_C(0x002ce4d0):goto L_002ce4d0;
 case UINT32_C(0x002ce4d4):goto L_002ce4d4;
 case UINT32_C(0x002ce4d8):goto L_002ce4d8;
 case UINT32_C(0x002ce4e0):goto L_002ce4e0;
 case UINT32_C(0x002ce4e4):goto L_002ce4e4;
 case UINT32_C(0x002ce4e8):goto L_002ce4e8;
 case UINT32_C(0x002ce4ec):goto L_002ce4ec;
 case UINT32_C(0x002ce4f0):goto L_002ce4f0;
 case UINT32_C(0x002ce4f4):goto L_002ce4f4;
 case UINT32_C(0x002ce4f8):goto L_002ce4f8;
 case UINT32_C(0x002ce4fc):goto L_002ce4fc;
 case UINT32_C(0x002ce500):goto L_002ce500;
 case UINT32_C(0x002ce504):goto L_002ce504;
 case UINT32_C(0x002ce508):goto L_002ce508;
 case UINT32_C(0x002ce50c):goto L_002ce50c;
 case UINT32_C(0x002ce510):goto L_002ce510;
 case UINT32_C(0x002ce514):goto L_002ce514;
 case UINT32_C(0x002ce518):goto L_002ce518;
 case UINT32_C(0x002ce51c):goto L_002ce51c;
 case UINT32_C(0x002ce520):goto L_002ce520;
 case UINT32_C(0x002ce524):goto L_002ce524;
 case UINT32_C(0x002ce528):goto L_002ce528;
 case UINT32_C(0x002ce52c):goto L_002ce52c;
 case UINT32_C(0x002ce530):goto L_002ce530;
 case UINT32_C(0x002ce534):goto L_002ce534;
 case UINT32_C(0x002ce538):goto L_002ce538;
 case UINT32_C(0x002ce53c):goto L_002ce53c;
 case UINT32_C(0x002ce540):goto L_002ce540;
 case UINT32_C(0x002ce544):goto L_002ce544;
 case UINT32_C(0x002ce548):goto L_002ce548;
 case UINT32_C(0x002ce54c):goto L_002ce54c;
 case UINT32_C(0x002ce550):goto L_002ce550;
 case UINT32_C(0x002ce554):goto L_002ce554;
 case UINT32_C(0x002ce558):goto L_002ce558;
 case UINT32_C(0x002ce55c):goto L_002ce55c;
 case UINT32_C(0x002ce560):goto L_002ce560;
 case UINT32_C(0x002ce564):goto L_002ce564;
 case UINT32_C(0x002ce568):goto L_002ce568;
 case UINT32_C(0x002ce56c):goto L_002ce56c;
 case UINT32_C(0x002ce570):goto L_002ce570;
 case UINT32_C(0x002ce574):goto L_002ce574;
 case UINT32_C(0x002ce578):goto L_002ce578;
 case UINT32_C(0x002ce57c):goto L_002ce57c;
 case UINT32_C(0x002ce580):goto L_002ce580;
 case UINT32_C(0x002ce584):goto L_002ce584;
 case UINT32_C(0x002ce588):goto L_002ce588;
 case UINT32_C(0x002ce58c):goto L_002ce58c;
 case UINT32_C(0x002ce590):goto L_002ce590;
 case UINT32_C(0x002ce594):goto L_002ce594;
 case UINT32_C(0x002ce598):goto L_002ce598;
 case UINT32_C(0x002ce59c):goto L_002ce59c;
 case UINT32_C(0x002ce5a0):goto L_002ce5a0;
 case UINT32_C(0x002ce5a4):goto L_002ce5a4;
 case UINT32_C(0x002ce5a8):goto L_002ce5a8;
 case UINT32_C(0x002ce5ac):goto L_002ce5ac;
 case UINT32_C(0x002ce5b0):goto L_002ce5b0;
 case UINT32_C(0x002ce5b4):goto L_002ce5b4;
 case UINT32_C(0x002ce5b8):goto L_002ce5b8;
 case UINT32_C(0x002ce5bc):goto L_002ce5bc;
 case UINT32_C(0x002ce5c0):goto L_002ce5c0;
 case UINT32_C(0x002ce5c4):goto L_002ce5c4;
 case UINT32_C(0x002ce5c8):goto L_002ce5c8;
 case UINT32_C(0x002ce5cc):goto L_002ce5cc;
 case UINT32_C(0x002ce5d0):goto L_002ce5d0;
 case UINT32_C(0x002ce5d4):goto L_002ce5d4;
 case UINT32_C(0x002ce5d8):goto L_002ce5d8;
 case UINT32_C(0x002ce5dc):goto L_002ce5dc;
 case UINT32_C(0x002ce5e0):goto L_002ce5e0;
 case UINT32_C(0x002ce5e4):goto L_002ce5e4;
 case UINT32_C(0x002ce5e8):goto L_002ce5e8;
 case UINT32_C(0x002ce5ec):goto L_002ce5ec;
 case UINT32_C(0x002ce5f0):goto L_002ce5f0;
 case UINT32_C(0x002ce5f4):goto L_002ce5f4;
 case UINT32_C(0x002ce5f8):goto L_002ce5f8;
 case UINT32_C(0x002ce5fc):goto L_002ce5fc;
 case UINT32_C(0x002ce600):goto L_002ce600;
 case UINT32_C(0x002ce604):goto L_002ce604;
 case UINT32_C(0x002ce608):goto L_002ce608;
 case UINT32_C(0x002ce60c):goto L_002ce60c;
 case UINT32_C(0x002ce610):goto L_002ce610;
 case UINT32_C(0x002ce614):goto L_002ce614;
 case UINT32_C(0x002ce618):goto L_002ce618;
 case UINT32_C(0x002ce61c):goto L_002ce61c;
 case UINT32_C(0x002ce620):goto L_002ce620;
 case UINT32_C(0x002ce624):goto L_002ce624;
 case UINT32_C(0x002ce628):goto L_002ce628;
 case UINT32_C(0x002ce62c):goto L_002ce62c;
 case UINT32_C(0x002ce630):goto L_002ce630;
 case UINT32_C(0x002ce634):goto L_002ce634;
 case UINT32_C(0x002ce638):goto L_002ce638;
 case UINT32_C(0x002ce63c):goto L_002ce63c;
 case UINT32_C(0x002ce640):goto L_002ce640;
 case UINT32_C(0x002ce644):goto L_002ce644;
 case UINT32_C(0x002ce648):goto L_002ce648;
 case UINT32_C(0x002ce64c):goto L_002ce64c;
 case UINT32_C(0x002ce650):goto L_002ce650;
 case UINT32_C(0x002ce654):goto L_002ce654;
 case UINT32_C(0x002ce658):goto L_002ce658;
 case UINT32_C(0x002ce660):goto L_002ce660;
 case UINT32_C(0x002ce664):goto L_002ce664;
 case UINT32_C(0x002ce668):goto L_002ce668;
 case UINT32_C(0x002ce66c):goto L_002ce66c;
 case UINT32_C(0x002ce670):goto L_002ce670;
 case UINT32_C(0x002ce674):goto L_002ce674;
 case UINT32_C(0x002ce678):goto L_002ce678;
 case UINT32_C(0x002ce67c):goto L_002ce67c;
 case UINT32_C(0x002ce680):goto L_002ce680;
 case UINT32_C(0x002ce688):goto L_002ce688;
 case UINT32_C(0x002ce68c):goto L_002ce68c;
 case UINT32_C(0x002ce690):goto L_002ce690;
 case UINT32_C(0x002ce694):goto L_002ce694;
 case UINT32_C(0x002ce698):goto L_002ce698;
 case UINT32_C(0x002ce69c):goto L_002ce69c;
 case UINT32_C(0x002ce6a0):goto L_002ce6a0;
 case UINT32_C(0x002ce6a4):goto L_002ce6a4;
 case UINT32_C(0x002ce6a8):goto L_002ce6a8;
 case UINT32_C(0x002ce6ac):goto L_002ce6ac;
 case UINT32_C(0x002ce6b0):goto L_002ce6b0;
 case UINT32_C(0x002ce6b4):goto L_002ce6b4;
 case UINT32_C(0x002ce6b8):goto L_002ce6b8;
 case UINT32_C(0x002ce6bc):goto L_002ce6bc;
 case UINT32_C(0x002ce6c0):goto L_002ce6c0;
 case UINT32_C(0x002ce6c4):goto L_002ce6c4;
 case UINT32_C(0x002ce6c8):goto L_002ce6c8;
 case UINT32_C(0x002ce6d0):goto L_002ce6d0;
 case UINT32_C(0x002ce6d4):goto L_002ce6d4;
 case UINT32_C(0x002ce6d8):goto L_002ce6d8;
 case UINT32_C(0x002ce6dc):goto L_002ce6dc;
 case UINT32_C(0x002ce6e0):goto L_002ce6e0;
 case UINT32_C(0x002ce6e4):goto L_002ce6e4;
 case UINT32_C(0x002ce6e8):goto L_002ce6e8;
 case UINT32_C(0x002ce6ec):goto L_002ce6ec;
 case UINT32_C(0x002ce6f0):goto L_002ce6f0;
 case UINT32_C(0x002ce6f4):goto L_002ce6f4;
 case UINT32_C(0x002ce6f8):goto L_002ce6f8;
 case UINT32_C(0x002ce6fc):goto L_002ce6fc;
 case UINT32_C(0x002ce700):goto L_002ce700;
 case UINT32_C(0x002ce704):goto L_002ce704;
 case UINT32_C(0x002ce708):goto L_002ce708;
 case UINT32_C(0x002ce70c):goto L_002ce70c;
 case UINT32_C(0x002ce710):goto L_002ce710;
 case UINT32_C(0x002ce714):goto L_002ce714;
 case UINT32_C(0x002ce718):goto L_002ce718;
 case UINT32_C(0x002ce71c):goto L_002ce71c;
 case UINT32_C(0x002ce720):goto L_002ce720;
 case UINT32_C(0x002ce724):goto L_002ce724;
 case UINT32_C(0x002ce728):goto L_002ce728;
 case UINT32_C(0x002ce72c):goto L_002ce72c;
 case UINT32_C(0x002ce730):goto L_002ce730;
 case UINT32_C(0x002ce734):goto L_002ce734;
 case UINT32_C(0x002ce738):goto L_002ce738;
 case UINT32_C(0x002ce73c):goto L_002ce73c;
 case UINT32_C(0x002ce740):goto L_002ce740;
 case UINT32_C(0x002ce744):goto L_002ce744;
 case UINT32_C(0x002ce748):goto L_002ce748;
 case UINT32_C(0x002ce74c):goto L_002ce74c;
 case UINT32_C(0x002ce750):goto L_002ce750;
 case UINT32_C(0x002ce754):goto L_002ce754;
 case UINT32_C(0x002ce758):goto L_002ce758;
 case UINT32_C(0x002ce75c):goto L_002ce75c;
 case UINT32_C(0x002ce760):goto L_002ce760;
 case UINT32_C(0x002ce764):goto L_002ce764;
 case UINT32_C(0x002ce768):goto L_002ce768;
 case UINT32_C(0x002ce76c):goto L_002ce76c;
 case UINT32_C(0x002ce770):goto L_002ce770;
 case UINT32_C(0x002ce774):goto L_002ce774;
 case UINT32_C(0x002ce778):goto L_002ce778;
 case UINT32_C(0x002ce77c):goto L_002ce77c;
 case UINT32_C(0x002ce780):goto L_002ce780;
 case UINT32_C(0x002ce784):goto L_002ce784;
 case UINT32_C(0x002ce788):goto L_002ce788;
 case UINT32_C(0x002ce78c):goto L_002ce78c;
 case UINT32_C(0x002ce790):goto L_002ce790;
 case UINT32_C(0x002ce794):goto L_002ce794;
 case UINT32_C(0x002ce798):goto L_002ce798;
 case UINT32_C(0x002ce79c):goto L_002ce79c;
 case UINT32_C(0x002ce7a0):goto L_002ce7a0;
 case UINT32_C(0x002ce7a4):goto L_002ce7a4;
 case UINT32_C(0x002ce7a8):goto L_002ce7a8;
 case UINT32_C(0x002ce7ac):goto L_002ce7ac;
 case UINT32_C(0x002ce7b0):goto L_002ce7b0;
 case UINT32_C(0x002ce7b4):goto L_002ce7b4;
 case UINT32_C(0x002ce7b8):goto L_002ce7b8;
 case UINT32_C(0x002ce7bc):goto L_002ce7bc;
 case UINT32_C(0x002ce7c0):goto L_002ce7c0;
 case UINT32_C(0x002ce7c4):goto L_002ce7c4;
 case UINT32_C(0x002ce7c8):goto L_002ce7c8;
 case UINT32_C(0x002ce7cc):goto L_002ce7cc;
 case UINT32_C(0x002ce7d0):goto L_002ce7d0;
 case UINT32_C(0x002ce7d4):goto L_002ce7d4;
 case UINT32_C(0x002ce7d8):goto L_002ce7d8;
 case UINT32_C(0x002ce7dc):goto L_002ce7dc;
 case UINT32_C(0x002ce7e0):goto L_002ce7e0;
 case UINT32_C(0x002ce7e4):goto L_002ce7e4;
 case UINT32_C(0x002ce7e8):goto L_002ce7e8;
 case UINT32_C(0x002ce7ec):goto L_002ce7ec;
 case UINT32_C(0x002ce7f0):goto L_002ce7f0;
 case UINT32_C(0x002ce7f4):goto L_002ce7f4;
 case UINT32_C(0x002ce7f8):goto L_002ce7f8;
 case UINT32_C(0x002ce7fc):goto L_002ce7fc;
 case UINT32_C(0x002ce800):goto L_002ce800;
 case UINT32_C(0x002ce808):goto L_002ce808;
 case UINT32_C(0x002ce80c):goto L_002ce80c;
 case UINT32_C(0x002ce810):goto L_002ce810;
 case UINT32_C(0x002ce814):goto L_002ce814;
 case UINT32_C(0x002ce818):goto L_002ce818;
 case UINT32_C(0x002ce81c):goto L_002ce81c;
 case UINT32_C(0x002ce820):goto L_002ce820;
 case UINT32_C(0x002ce824):goto L_002ce824;
 case UINT32_C(0x002ce828):goto L_002ce828;
 case UINT32_C(0x002ce82c):goto L_002ce82c;
 case UINT32_C(0x002ce830):goto L_002ce830;
 case UINT32_C(0x002ce834):goto L_002ce834;
 case UINT32_C(0x002ce838):goto L_002ce838;
 case UINT32_C(0x002ce83c):goto L_002ce83c;
 case UINT32_C(0x002ce840):goto L_002ce840;
 case UINT32_C(0x002ce844):goto L_002ce844;
 case UINT32_C(0x002ce848):goto L_002ce848;
 case UINT32_C(0x002ce84c):goto L_002ce84c;
 case UINT32_C(0x002ce850):goto L_002ce850;
 case UINT32_C(0x002ce854):goto L_002ce854;
 case UINT32_C(0x002ce858):goto L_002ce858;
 case UINT32_C(0x002ce85c):goto L_002ce85c;
 case UINT32_C(0x002ce860):goto L_002ce860;
 case UINT32_C(0x002ce864):goto L_002ce864;
 case UINT32_C(0x002ce868):goto L_002ce868;
 case UINT32_C(0x002ce86c):goto L_002ce86c;
 case UINT32_C(0x002ce870):goto L_002ce870;
 case UINT32_C(0x002ce874):goto L_002ce874;
 case UINT32_C(0x002ce878):goto L_002ce878;
 case UINT32_C(0x002ce87c):goto L_002ce87c;
 case UINT32_C(0x002ce880):goto L_002ce880;
 case UINT32_C(0x002ce884):goto L_002ce884;
 case UINT32_C(0x002ce888):goto L_002ce888;
 case UINT32_C(0x002ce88c):goto L_002ce88c;
 case UINT32_C(0x002ce890):goto L_002ce890;
 case UINT32_C(0x002ce894):goto L_002ce894;
 case UINT32_C(0x002ce898):goto L_002ce898;
 case UINT32_C(0x002ce89c):goto L_002ce89c;
 case UINT32_C(0x002ce8a0):goto L_002ce8a0;
 case UINT32_C(0x002ce8a4):goto L_002ce8a4;
 case UINT32_C(0x002ce8a8):goto L_002ce8a8;
 case UINT32_C(0x002ce8ac):goto L_002ce8ac;
 case UINT32_C(0x002ce8b0):goto L_002ce8b0;
 case UINT32_C(0x002ce8b4):goto L_002ce8b4;
 case UINT32_C(0x002ce8b8):goto L_002ce8b8;
 case UINT32_C(0x002ce8bc):goto L_002ce8bc;
 case UINT32_C(0x002ce8c0):goto L_002ce8c0;
 case UINT32_C(0x002ce8c4):goto L_002ce8c4;
 case UINT32_C(0x002ce8c8):goto L_002ce8c8;
 case UINT32_C(0x002ce8cc):goto L_002ce8cc;
 case UINT32_C(0x002ce8d0):goto L_002ce8d0;
 case UINT32_C(0x002ce8d4):goto L_002ce8d4;
 case UINT32_C(0x002ce8d8):goto L_002ce8d8;
 case UINT32_C(0x002ce8dc):goto L_002ce8dc;
 case UINT32_C(0x002ce8e0):goto L_002ce8e0;
 case UINT32_C(0x002ce8e4):goto L_002ce8e4;
 case UINT32_C(0x002ce8e8):goto L_002ce8e8;
 case UINT32_C(0x002ce8ec):goto L_002ce8ec;
 case UINT32_C(0x002ce8f0):goto L_002ce8f0;
 case UINT32_C(0x002ce8f4):goto L_002ce8f4;
 case UINT32_C(0x002ce8f8):goto L_002ce8f8;
 case UINT32_C(0x002ce8fc):goto L_002ce8fc;
 case UINT32_C(0x002ce900):goto L_002ce900;
 case UINT32_C(0x002ce904):goto L_002ce904;
 case UINT32_C(0x002ce908):goto L_002ce908;
 case UINT32_C(0x002ce90c):goto L_002ce90c;
 case UINT32_C(0x002ce910):goto L_002ce910;
 case UINT32_C(0x002ce914):goto L_002ce914;
 case UINT32_C(0x002ce918):goto L_002ce918;
 case UINT32_C(0x002ce91c):goto L_002ce91c;
 case UINT32_C(0x002ce920):goto L_002ce920;
 case UINT32_C(0x002ce924):goto L_002ce924;
 case UINT32_C(0x002ce928):goto L_002ce928;
 case UINT32_C(0x002ce92c):goto L_002ce92c;
 case UINT32_C(0x002ce930):goto L_002ce930;
 case UINT32_C(0x002ce934):goto L_002ce934;
 case UINT32_C(0x002ce938):goto L_002ce938;
 case UINT32_C(0x002ce93c):goto L_002ce93c;
 case UINT32_C(0x002ce940):goto L_002ce940;
 case UINT32_C(0x002ce944):goto L_002ce944;
 case UINT32_C(0x002ce948):goto L_002ce948;
 case UINT32_C(0x002ce94c):goto L_002ce94c;
 case UINT32_C(0x002ce950):goto L_002ce950;
 case UINT32_C(0x002ce954):goto L_002ce954;
 case UINT32_C(0x002ce958):goto L_002ce958;
 case UINT32_C(0x002ce95c):goto L_002ce95c;
 case UINT32_C(0x002ce960):goto L_002ce960;
 case UINT32_C(0x002ce964):goto L_002ce964;
 case UINT32_C(0x002ce968):goto L_002ce968;
 case UINT32_C(0x002ce96c):goto L_002ce96c;
 case UINT32_C(0x002ce970):goto L_002ce970;
 case UINT32_C(0x002ce974):goto L_002ce974;
 case UINT32_C(0x002ce978):goto L_002ce978;
 case UINT32_C(0x002ce97c):goto L_002ce97c;
 case UINT32_C(0x002ce980):goto L_002ce980;
 case UINT32_C(0x002ce984):goto L_002ce984;
 case UINT32_C(0x002ce988):goto L_002ce988;
 case UINT32_C(0x002ce990):goto L_002ce990;
 case UINT32_C(0x002ce994):goto L_002ce994;
 case UINT32_C(0x002ce998):goto L_002ce998;
 case UINT32_C(0x002ce99c):goto L_002ce99c;
 case UINT32_C(0x002ce9a0):goto L_002ce9a0;
 case UINT32_C(0x002ce9a4):goto L_002ce9a4;
 case UINT32_C(0x002ce9a8):goto L_002ce9a8;
 case UINT32_C(0x002ce9ac):goto L_002ce9ac;
 case UINT32_C(0x002ce9b0):goto L_002ce9b0;
 case UINT32_C(0x002ce9b4):goto L_002ce9b4;
 case UINT32_C(0x002ce9b8):goto L_002ce9b8;
 case UINT32_C(0x002ce9bc):goto L_002ce9bc;
 case UINT32_C(0x002ce9c0):goto L_002ce9c0;
 case UINT32_C(0x002ce9c4):goto L_002ce9c4;
 case UINT32_C(0x002ce9c8):goto L_002ce9c8;
 case UINT32_C(0x002ce9cc):goto L_002ce9cc;
 case UINT32_C(0x002ce9d0):goto L_002ce9d0;
 case UINT32_C(0x002ce9d4):goto L_002ce9d4;
 case UINT32_C(0x002ce9d8):goto L_002ce9d8;
 case UINT32_C(0x002ce9dc):goto L_002ce9dc;
 case UINT32_C(0x002ce9e0):goto L_002ce9e0;
 case UINT32_C(0x002ce9e4):goto L_002ce9e4;
 case UINT32_C(0x002ce9e8):goto L_002ce9e8;
 case UINT32_C(0x002ce9ec):goto L_002ce9ec;
 case UINT32_C(0x002ce9f0):goto L_002ce9f0;
 case UINT32_C(0x002ce9f4):goto L_002ce9f4;
 case UINT32_C(0x002ce9f8):goto L_002ce9f8;
 case UINT32_C(0x002cea00):goto L_002cea00;
 case UINT32_C(0x002cea04):goto L_002cea04;
 case UINT32_C(0x002cea08):goto L_002cea08;
 case UINT32_C(0x002cea0c):goto L_002cea0c;
 case UINT32_C(0x002cea10):goto L_002cea10;
 case UINT32_C(0x002cea14):goto L_002cea14;
 case UINT32_C(0x002cea18):goto L_002cea18;
 case UINT32_C(0x002cea1c):goto L_002cea1c;
 case UINT32_C(0x002cea20):goto L_002cea20;
 case UINT32_C(0x002cea24):goto L_002cea24;
 case UINT32_C(0x002cea28):goto L_002cea28;
 case UINT32_C(0x002cea2c):goto L_002cea2c;
 case UINT32_C(0x002cea30):goto L_002cea30;
 case UINT32_C(0x002cea34):goto L_002cea34;
 case UINT32_C(0x002cea38):goto L_002cea38;
 case UINT32_C(0x002cea3c):goto L_002cea3c;
 case UINT32_C(0x002cea40):goto L_002cea40;
 case UINT32_C(0x002cea44):goto L_002cea44;
 case UINT32_C(0x002cea48):goto L_002cea48;
 case UINT32_C(0x002cea4c):goto L_002cea4c;
 case UINT32_C(0x002cea50):goto L_002cea50;
 case UINT32_C(0x002cea54):goto L_002cea54;
 case UINT32_C(0x002cea58):goto L_002cea58;
 case UINT32_C(0x002cea5c):goto L_002cea5c;
 case UINT32_C(0x002cea60):goto L_002cea60;
 case UINT32_C(0x002cea64):goto L_002cea64;
 case UINT32_C(0x002cea68):goto L_002cea68;
 case UINT32_C(0x002cea6c):goto L_002cea6c;
 case UINT32_C(0x002cea70):goto L_002cea70;
 case UINT32_C(0x002cea74):goto L_002cea74;
 case UINT32_C(0x002cea78):goto L_002cea78;
 case UINT32_C(0x002cea7c):goto L_002cea7c;
 case UINT32_C(0x002cea80):goto L_002cea80;
 case UINT32_C(0x002cea84):goto L_002cea84;
 case UINT32_C(0x002cea88):goto L_002cea88;
 case UINT32_C(0x002cea8c):goto L_002cea8c;
 case UINT32_C(0x002cea90):goto L_002cea90;
 case UINT32_C(0x002cea94):goto L_002cea94;
 case UINT32_C(0x002cea98):goto L_002cea98;
 case UINT32_C(0x002cea9c):goto L_002cea9c;
 case UINT32_C(0x002ceaa0):goto L_002ceaa0;
 case UINT32_C(0x002ceaa4):goto L_002ceaa4;
 case UINT32_C(0x002ceaa8):goto L_002ceaa8;
 case UINT32_C(0x002ceaac):goto L_002ceaac;
 case UINT32_C(0x002ceab0):goto L_002ceab0;
 case UINT32_C(0x002ceab4):goto L_002ceab4;
 case UINT32_C(0x002ceab8):goto L_002ceab8;
 case UINT32_C(0x002ceabc):goto L_002ceabc;
 case UINT32_C(0x002ceac0):goto L_002ceac0;
 case UINT32_C(0x002ceac4):goto L_002ceac4;
 case UINT32_C(0x002ceac8):goto L_002ceac8;
 case UINT32_C(0x002ceacc):goto L_002ceacc;
 case UINT32_C(0x002cead0):goto L_002cead0;
 case UINT32_C(0x002cead4):goto L_002cead4;
 case UINT32_C(0x002cead8):goto L_002cead8;
 case UINT32_C(0x002ceadc):goto L_002ceadc;
 case UINT32_C(0x002ceae0):goto L_002ceae0;
 case UINT32_C(0x002ceae4):goto L_002ceae4;
 case UINT32_C(0x002ceae8):goto L_002ceae8;
 case UINT32_C(0x002ceaec):goto L_002ceaec;
 case UINT32_C(0x002ceaf0):goto L_002ceaf0;
 case UINT32_C(0x002ceaf4):goto L_002ceaf4;
 case UINT32_C(0x002ceaf8):goto L_002ceaf8;
 case UINT32_C(0x002ceafc):goto L_002ceafc;
 case UINT32_C(0x002ceb00):goto L_002ceb00;
 case UINT32_C(0x002ceb04):goto L_002ceb04;
 case UINT32_C(0x002ceb08):goto L_002ceb08;
 case UINT32_C(0x002ceb0c):goto L_002ceb0c;
 case UINT32_C(0x002ceb10):goto L_002ceb10;
 case UINT32_C(0x002ceb14):goto L_002ceb14;
 case UINT32_C(0x002ceb18):goto L_002ceb18;
 case UINT32_C(0x002ceb1c):goto L_002ceb1c;
 case UINT32_C(0x002ceb20):goto L_002ceb20;
 case UINT32_C(0x002ceb24):goto L_002ceb24;
 case UINT32_C(0x002ceb28):goto L_002ceb28;
 case UINT32_C(0x002ceb2c):goto L_002ceb2c;
 case UINT32_C(0x002ceb30):goto L_002ceb30;
 case UINT32_C(0x002ceb34):goto L_002ceb34;
 case UINT32_C(0x002ceb38):goto L_002ceb38;
 case UINT32_C(0x002ceb3c):goto L_002ceb3c;
 case UINT32_C(0x002ceb40):goto L_002ceb40;
 case UINT32_C(0x002ceb44):goto L_002ceb44;
 case UINT32_C(0x002ceb48):goto L_002ceb48;
 case UINT32_C(0x002ceb4c):goto L_002ceb4c;
 case UINT32_C(0x002ceb50):goto L_002ceb50;
 case UINT32_C(0x002ceb54):goto L_002ceb54;
 case UINT32_C(0x002ceb58):goto L_002ceb58;
 case UINT32_C(0x002ceb5c):goto L_002ceb5c;
 case UINT32_C(0x002ceb60):goto L_002ceb60;
 case UINT32_C(0x002ceb64):goto L_002ceb64;
 case UINT32_C(0x002ceb68):goto L_002ceb68;
 case UINT32_C(0x002ceb6c):goto L_002ceb6c;
 case UINT32_C(0x002ceb70):goto L_002ceb70;
 case UINT32_C(0x002ceb74):goto L_002ceb74;
 case UINT32_C(0x002ceb78):goto L_002ceb78;
 case UINT32_C(0x002ceb7c):goto L_002ceb7c;
 case UINT32_C(0x002ceb80):goto L_002ceb80;
 case UINT32_C(0x002ceb84):goto L_002ceb84;
 case UINT32_C(0x002ceb88):goto L_002ceb88;
 case UINT32_C(0x002ceb8c):goto L_002ceb8c;
 case UINT32_C(0x002ceb90):goto L_002ceb90;
 case UINT32_C(0x002ceb94):goto L_002ceb94;
 case UINT32_C(0x002ceb98):goto L_002ceb98;
 case UINT32_C(0x002ceb9c):goto L_002ceb9c;
 case UINT32_C(0x002ceba0):goto L_002ceba0;
 case UINT32_C(0x002ceba4):goto L_002ceba4;
 case UINT32_C(0x002ceba8):goto L_002ceba8;
 case UINT32_C(0x002cebac):goto L_002cebac;
 case UINT32_C(0x002cebb0):goto L_002cebb0;
 case UINT32_C(0x002cebb4):goto L_002cebb4;
 case UINT32_C(0x002cebb8):goto L_002cebb8;
 case UINT32_C(0x002cebbc):goto L_002cebbc;
 case UINT32_C(0x002cebc0):goto L_002cebc0;
 case UINT32_C(0x002cebc4):goto L_002cebc4;
 case UINT32_C(0x002cebc8):goto L_002cebc8;
 case UINT32_C(0x002cebcc):goto L_002cebcc;
 case UINT32_C(0x002cebd0):goto L_002cebd0;
 case UINT32_C(0x002cebd4):goto L_002cebd4;
 case UINT32_C(0x002cebd8):goto L_002cebd8;
 case UINT32_C(0x002cebe0):goto L_002cebe0;
 case UINT32_C(0x002cebe4):goto L_002cebe4;
 case UINT32_C(0x002cebe8):goto L_002cebe8;
 case UINT32_C(0x002cebec):goto L_002cebec;
 case UINT32_C(0x002cebf0):goto L_002cebf0;
 case UINT32_C(0x002cebf4):goto L_002cebf4;
 case UINT32_C(0x002cebf8):goto L_002cebf8;
 case UINT32_C(0x002cebfc):goto L_002cebfc;
 case UINT32_C(0x002cec00):goto L_002cec00;
 case UINT32_C(0x002cec04):goto L_002cec04;
 case UINT32_C(0x002cec08):goto L_002cec08;
 case UINT32_C(0x002cec0c):goto L_002cec0c;
 case UINT32_C(0x002cec10):goto L_002cec10;
 case UINT32_C(0x002cec14):goto L_002cec14;
 case UINT32_C(0x002cec18):goto L_002cec18;
 case UINT32_C(0x002cec1c):goto L_002cec1c;
 case UINT32_C(0x002cec20):goto L_002cec20;
 case UINT32_C(0x002cec24):goto L_002cec24;
 case UINT32_C(0x002cec28):goto L_002cec28;
 case UINT32_C(0x002cec2c):goto L_002cec2c;
 case UINT32_C(0x002cec30):goto L_002cec30;
 case UINT32_C(0x002cec34):goto L_002cec34;
 case UINT32_C(0x002cec38):goto L_002cec38;
 case UINT32_C(0x002cec3c):goto L_002cec3c;
 case UINT32_C(0x002cec40):goto L_002cec40;
 case UINT32_C(0x002cec44):goto L_002cec44;
 case UINT32_C(0x002cec48):goto L_002cec48;
 case UINT32_C(0x002cec4c):goto L_002cec4c;
 case UINT32_C(0x002cec50):goto L_002cec50;
 case UINT32_C(0x002cec54):goto L_002cec54;
 case UINT32_C(0x002cec58):goto L_002cec58;
 case UINT32_C(0x002cec5c):goto L_002cec5c;
 case UINT32_C(0x002cec60):goto L_002cec60;
 case UINT32_C(0x002cec64):goto L_002cec64;
 case UINT32_C(0x002cec68):goto L_002cec68;
 case UINT32_C(0x002cec6c):goto L_002cec6c;
 case UINT32_C(0x002cec70):goto L_002cec70;
 case UINT32_C(0x002cec74):goto L_002cec74;
 case UINT32_C(0x002cec78):goto L_002cec78;
 case UINT32_C(0x002cec7c):goto L_002cec7c;
 case UINT32_C(0x002cec80):goto L_002cec80;
 case UINT32_C(0x002cec84):goto L_002cec84;
 case UINT32_C(0x002cec88):goto L_002cec88;
 case UINT32_C(0x002cec8c):goto L_002cec8c;
 case UINT32_C(0x002cec90):goto L_002cec90;
 case UINT32_C(0x002cec94):goto L_002cec94;
 case UINT32_C(0x002cec98):goto L_002cec98;
 case UINT32_C(0x002cec9c):goto L_002cec9c;
 case UINT32_C(0x002ceca0):goto L_002ceca0;
 case UINT32_C(0x002ceca4):goto L_002ceca4;
 case UINT32_C(0x002ceca8):goto L_002ceca8;
 case UINT32_C(0x002cecac):goto L_002cecac;
 case UINT32_C(0x002cecb0):goto L_002cecb0;
 case UINT32_C(0x002cecb4):goto L_002cecb4;
 case UINT32_C(0x002cecb8):goto L_002cecb8;
 case UINT32_C(0x002cecbc):goto L_002cecbc;
 case UINT32_C(0x002cecc0):goto L_002cecc0;
 case UINT32_C(0x002cecc4):goto L_002cecc4;
 case UINT32_C(0x002cecc8):goto L_002cecc8;
 case UINT32_C(0x002ceccc):goto L_002ceccc;
 case UINT32_C(0x002cecd0):goto L_002cecd0;
 case UINT32_C(0x002cecd4):goto L_002cecd4;
 case UINT32_C(0x002cecd8):goto L_002cecd8;
 case UINT32_C(0x002cecdc):goto L_002cecdc;
 case UINT32_C(0x002cece0):goto L_002cece0;
 case UINT32_C(0x002cece4):goto L_002cece4;
 case UINT32_C(0x002cece8):goto L_002cece8;
 case UINT32_C(0x002cecec):goto L_002cecec;
 case UINT32_C(0x002cecf0):goto L_002cecf0;
 case UINT32_C(0x002cecf4):goto L_002cecf4;
 case UINT32_C(0x002cecf8):goto L_002cecf8;
 case UINT32_C(0x002cecfc):goto L_002cecfc;
 case UINT32_C(0x002ced00):goto L_002ced00;
 case UINT32_C(0x002ced04):goto L_002ced04;
 case UINT32_C(0x002ced08):goto L_002ced08;
 case UINT32_C(0x002ced0c):goto L_002ced0c;
 case UINT32_C(0x002ced10):goto L_002ced10;
 case UINT32_C(0x002ced14):goto L_002ced14;
 case UINT32_C(0x002ced18):goto L_002ced18;
 case UINT32_C(0x002ced1c):goto L_002ced1c;
 case UINT32_C(0x002ced20):goto L_002ced20;
 case UINT32_C(0x002ced24):goto L_002ced24;
 case UINT32_C(0x002ced28):goto L_002ced28;
 case UINT32_C(0x002ced2c):goto L_002ced2c;
 case UINT32_C(0x002ced30):goto L_002ced30;
 case UINT32_C(0x002ced34):goto L_002ced34;
 case UINT32_C(0x002ced38):goto L_002ced38;
 case UINT32_C(0x002ced3c):goto L_002ced3c;
 case UINT32_C(0x002ced40):goto L_002ced40;
 case UINT32_C(0x002ced44):goto L_002ced44;
 case UINT32_C(0x002ced48):goto L_002ced48;
 case UINT32_C(0x002ced4c):goto L_002ced4c;
 case UINT32_C(0x002ced50):goto L_002ced50;
 case UINT32_C(0x002ced54):goto L_002ced54;
 case UINT32_C(0x002ced58):goto L_002ced58;
 case UINT32_C(0x002ced5c):goto L_002ced5c;
 case UINT32_C(0x002ced60):goto L_002ced60;
 case UINT32_C(0x002ced64):goto L_002ced64;
 case UINT32_C(0x002ced68):goto L_002ced68;
 case UINT32_C(0x002ced6c):goto L_002ced6c;
 case UINT32_C(0x002ced70):goto L_002ced70;
 case UINT32_C(0x002ced74):goto L_002ced74;
 case UINT32_C(0x002ced78):goto L_002ced78;
 case UINT32_C(0x002ced7c):goto L_002ced7c;
 case UINT32_C(0x002ced80):goto L_002ced80;
 case UINT32_C(0x002ced84):goto L_002ced84;
 case UINT32_C(0x002ced88):goto L_002ced88;
 case UINT32_C(0x002ced8c):goto L_002ced8c;
 case UINT32_C(0x002ced90):goto L_002ced90;
 case UINT32_C(0x002ced94):goto L_002ced94;
 case UINT32_C(0x002ced98):goto L_002ced98;
 case UINT32_C(0x002ced9c):goto L_002ced9c;
 case UINT32_C(0x002ceda0):goto L_002ceda0;
 case UINT32_C(0x002ceda4):goto L_002ceda4;
 case UINT32_C(0x002ceda8):goto L_002ceda8;
 case UINT32_C(0x002cedac):goto L_002cedac;
 case UINT32_C(0x002cedb0):goto L_002cedb0;
 case UINT32_C(0x002cedb4):goto L_002cedb4;
 case UINT32_C(0x002cedb8):goto L_002cedb8;
 case UINT32_C(0x002cedbc):goto L_002cedbc;
 case UINT32_C(0x002cedc0):goto L_002cedc0;
 case UINT32_C(0x002cedc4):goto L_002cedc4;
 case UINT32_C(0x002cedc8):goto L_002cedc8;
 case UINT32_C(0x002cedcc):goto L_002cedcc;
 case UINT32_C(0x002cedd0):goto L_002cedd0;
 case UINT32_C(0x002cedd4):goto L_002cedd4;
 case UINT32_C(0x002cedd8):goto L_002cedd8;
 case UINT32_C(0x002ceddc):goto L_002ceddc;
 case UINT32_C(0x002cede0):goto L_002cede0;
 case UINT32_C(0x002cede4):goto L_002cede4;
 case UINT32_C(0x002cede8):goto L_002cede8;
 case UINT32_C(0x002cedec):goto L_002cedec;
 case UINT32_C(0x002cedf0):goto L_002cedf0;
 case UINT32_C(0x002cedf4):goto L_002cedf4;
 case UINT32_C(0x002cedf8):goto L_002cedf8;
 case UINT32_C(0x002cedfc):goto L_002cedfc;
 case UINT32_C(0x002cee00):goto L_002cee00;
 case UINT32_C(0x002cee04):goto L_002cee04;
 case UINT32_C(0x002cee08):goto L_002cee08;
 case UINT32_C(0x002cee0c):goto L_002cee0c;
 case UINT32_C(0x002cee10):goto L_002cee10;
 case UINT32_C(0x002cee14):goto L_002cee14;
 case UINT32_C(0x002cee18):goto L_002cee18;
 case UINT32_C(0x002cee1c):goto L_002cee1c;
 case UINT32_C(0x002cee20):goto L_002cee20;
 case UINT32_C(0x002cee24):goto L_002cee24;
 case UINT32_C(0x002cee28):goto L_002cee28;
 case UINT32_C(0x002cee2c):goto L_002cee2c;
 case UINT32_C(0x002cee30):goto L_002cee30;
 case UINT32_C(0x002cee34):goto L_002cee34;
 case UINT32_C(0x002cee38):goto L_002cee38;
 case UINT32_C(0x002cee3c):goto L_002cee3c;
 case UINT32_C(0x002cee40):goto L_002cee40;
 case UINT32_C(0x002cee44):goto L_002cee44;
 case UINT32_C(0x002cee48):goto L_002cee48;
 case UINT32_C(0x002cee4c):goto L_002cee4c;
 case UINT32_C(0x002cee50):goto L_002cee50;
 case UINT32_C(0x002cee54):goto L_002cee54;
 case UINT32_C(0x002cee58):goto L_002cee58;
 case UINT32_C(0x002cee5c):goto L_002cee5c;
 case UINT32_C(0x002cee60):goto L_002cee60;
 case UINT32_C(0x002cee64):goto L_002cee64;
 case UINT32_C(0x002cee68):goto L_002cee68;
 case UINT32_C(0x002cee6c):goto L_002cee6c;
 case UINT32_C(0x002cee70):goto L_002cee70;
 case UINT32_C(0x002cee74):goto L_002cee74;
 case UINT32_C(0x002cee78):goto L_002cee78;
 case UINT32_C(0x002cee7c):goto L_002cee7c;
 case UINT32_C(0x002cee80):goto L_002cee80;
 case UINT32_C(0x002cee84):goto L_002cee84;
 case UINT32_C(0x002cee88):goto L_002cee88;
 case UINT32_C(0x002cee8c):goto L_002cee8c;
 case UINT32_C(0x002cee90):goto L_002cee90;
 case UINT32_C(0x002cee94):goto L_002cee94;
 case UINT32_C(0x002cee98):goto L_002cee98;
 case UINT32_C(0x002cee9c):goto L_002cee9c;
 case UINT32_C(0x002ceea0):goto L_002ceea0;
 case UINT32_C(0x002ceea4):goto L_002ceea4;
 case UINT32_C(0x002ceea8):goto L_002ceea8;
 case UINT32_C(0x002ceeac):goto L_002ceeac;
 case UINT32_C(0x002ceeb0):goto L_002ceeb0;
 case UINT32_C(0x002ceeb4):goto L_002ceeb4;
 case UINT32_C(0x002ceeb8):goto L_002ceeb8;
 case UINT32_C(0x002ceebc):goto L_002ceebc;
 case UINT32_C(0x002ceec0):goto L_002ceec0;
 case UINT32_C(0x002ceec4):goto L_002ceec4;
 case UINT32_C(0x002ceec8):goto L_002ceec8;
 case UINT32_C(0x002ceecc):goto L_002ceecc;
 case UINT32_C(0x002ceed0):goto L_002ceed0;
 case UINT32_C(0x002ceed4):goto L_002ceed4;
 case UINT32_C(0x002ceed8):goto L_002ceed8;
 case UINT32_C(0x002ceedc):goto L_002ceedc;
 case UINT32_C(0x002ceee0):goto L_002ceee0;
 case UINT32_C(0x002ceee4):goto L_002ceee4;
 case UINT32_C(0x002ceee8):goto L_002ceee8;
 case UINT32_C(0x002ceeec):goto L_002ceeec;
 case UINT32_C(0x002ceef0):goto L_002ceef0;
 case UINT32_C(0x002ceef4):goto L_002ceef4;
 case UINT32_C(0x002ceef8):goto L_002ceef8;
 case UINT32_C(0x002ceefc):goto L_002ceefc;
 case UINT32_C(0x002cef00):goto L_002cef00;
 case UINT32_C(0x002cef04):goto L_002cef04;
 case UINT32_C(0x002cef08):goto L_002cef08;
 case UINT32_C(0x002cef0c):goto L_002cef0c;
 case UINT32_C(0x002cef10):goto L_002cef10;
 case UINT32_C(0x002cef14):goto L_002cef14;
 case UINT32_C(0x002cef18):goto L_002cef18;
 case UINT32_C(0x002cef1c):goto L_002cef1c;
 case UINT32_C(0x002cef20):goto L_002cef20;
 case UINT32_C(0x002cef24):goto L_002cef24;
 case UINT32_C(0x002cef28):goto L_002cef28;
 case UINT32_C(0x002cef2c):goto L_002cef2c;
 case UINT32_C(0x002cef30):goto L_002cef30;
 case UINT32_C(0x002cef34):goto L_002cef34;
 case UINT32_C(0x002cef38):goto L_002cef38;
 case UINT32_C(0x002cef3c):goto L_002cef3c;
 case UINT32_C(0x002cef40):goto L_002cef40;
 case UINT32_C(0x002cef44):goto L_002cef44;
 case UINT32_C(0x002cef48):goto L_002cef48;
 case UINT32_C(0x002cef4c):goto L_002cef4c;
 case UINT32_C(0x002cef50):goto L_002cef50;
 case UINT32_C(0x002cef54):goto L_002cef54;
 case UINT32_C(0x002cef58):goto L_002cef58;
 case UINT32_C(0x002cef5c):goto L_002cef5c;
 case UINT32_C(0x002cef60):goto L_002cef60;
 case UINT32_C(0x002cef64):goto L_002cef64;
 case UINT32_C(0x002cef68):goto L_002cef68;
 case UINT32_C(0x002cef6c):goto L_002cef6c;
 case UINT32_C(0x002cef70):goto L_002cef70;
 case UINT32_C(0x002cef74):goto L_002cef74;
 case UINT32_C(0x002cef78):goto L_002cef78;
 case UINT32_C(0x002cef7c):goto L_002cef7c;
 case UINT32_C(0x002cef80):goto L_002cef80;
 case UINT32_C(0x002cef84):goto L_002cef84;
 case UINT32_C(0x002cef88):goto L_002cef88;
 case UINT32_C(0x002cef8c):goto L_002cef8c;
 case UINT32_C(0x002cef90):goto L_002cef90;
 case UINT32_C(0x002cef94):goto L_002cef94;
 case UINT32_C(0x002cef98):goto L_002cef98;
 case UINT32_C(0x002cef9c):goto L_002cef9c;
 case UINT32_C(0x002cefa0):goto L_002cefa0;
 case UINT32_C(0x002cefa4):goto L_002cefa4;
 case UINT32_C(0x002cefa8):goto L_002cefa8;
 case UINT32_C(0x002cefac):goto L_002cefac;
 case UINT32_C(0x002cefb0):goto L_002cefb0;
 case UINT32_C(0x002cefb4):goto L_002cefb4;
 case UINT32_C(0x002cefb8):goto L_002cefb8;
 case UINT32_C(0x002cefbc):goto L_002cefbc;
 case UINT32_C(0x002cefc0):goto L_002cefc0;
 case UINT32_C(0x002cefc4):goto L_002cefc4;
 case UINT32_C(0x002cefc8):goto L_002cefc8;
 case UINT32_C(0x002cefcc):goto L_002cefcc;
 case UINT32_C(0x002cefd0):goto L_002cefd0;
 case UINT32_C(0x002cefd8):goto L_002cefd8;
 case UINT32_C(0x002cefdc):goto L_002cefdc;
 case UINT32_C(0x002cefe0):goto L_002cefe0;
 case UINT32_C(0x002cefe4):goto L_002cefe4;
 case UINT32_C(0x002cefe8):goto L_002cefe8;
 case UINT32_C(0x002cefec):goto L_002cefec;
 case UINT32_C(0x002ceff0):goto L_002ceff0;
 case UINT32_C(0x002ceff4):goto L_002ceff4;
 case UINT32_C(0x002ceff8):goto L_002ceff8;
 case UINT32_C(0x002ceffc):goto L_002ceffc;
 case UINT32_C(0x002cf000):goto L_002cf000;
 case UINT32_C(0x002cf004):goto L_002cf004;
 case UINT32_C(0x002cf008):goto L_002cf008;
 case UINT32_C(0x002cf00c):goto L_002cf00c;
 case UINT32_C(0x002cf010):goto L_002cf010;
 case UINT32_C(0x002cf014):goto L_002cf014;
 case UINT32_C(0x002cf018):goto L_002cf018;
 case UINT32_C(0x002cf01c):goto L_002cf01c;
 case UINT32_C(0x002cf020):goto L_002cf020;
 case UINT32_C(0x002cf024):goto L_002cf024;
 case UINT32_C(0x002cf028):goto L_002cf028;
 case UINT32_C(0x002cf02c):goto L_002cf02c;
 case UINT32_C(0x002cf030):goto L_002cf030;
 case UINT32_C(0x002cf034):goto L_002cf034;
 case UINT32_C(0x002cf038):goto L_002cf038;
 case UINT32_C(0x002cf03c):goto L_002cf03c;
 case UINT32_C(0x002cf040):goto L_002cf040;
 case UINT32_C(0x002cf044):goto L_002cf044;
 case UINT32_C(0x002cf048):goto L_002cf048;
 case UINT32_C(0x002cf04c):goto L_002cf04c;
 case UINT32_C(0x002cf050):goto L_002cf050;
 case UINT32_C(0x002cf054):goto L_002cf054;
 case UINT32_C(0x002cf058):goto L_002cf058;
 case UINT32_C(0x002cf05c):goto L_002cf05c;
 case UINT32_C(0x002cf060):goto L_002cf060;
 case UINT32_C(0x002cf064):goto L_002cf064;
 case UINT32_C(0x002cf068):goto L_002cf068;
 case UINT32_C(0x002cf06c):goto L_002cf06c;
 case UINT32_C(0x002cf070):goto L_002cf070;
 case UINT32_C(0x002cf074):goto L_002cf074;
 case UINT32_C(0x002cf078):goto L_002cf078;
 case UINT32_C(0x002cf07c):goto L_002cf07c;
 case UINT32_C(0x002cf080):goto L_002cf080;
 case UINT32_C(0x002cf084):goto L_002cf084;
 case UINT32_C(0x002cf088):goto L_002cf088;
 case UINT32_C(0x002cf08c):goto L_002cf08c;
 case UINT32_C(0x002cf090):goto L_002cf090;
 case UINT32_C(0x002cf094):goto L_002cf094;
 case UINT32_C(0x002cf098):goto L_002cf098;
 case UINT32_C(0x002cf09c):goto L_002cf09c;
 case UINT32_C(0x002cf0a0):goto L_002cf0a0;
 case UINT32_C(0x002cf0a4):goto L_002cf0a4;
 case UINT32_C(0x002cf0a8):goto L_002cf0a8;
 case UINT32_C(0x002cf0ac):goto L_002cf0ac;
 case UINT32_C(0x002cf0b0):goto L_002cf0b0;
 case UINT32_C(0x002cf0b4):goto L_002cf0b4;
 case UINT32_C(0x002cf0b8):goto L_002cf0b8;
 case UINT32_C(0x002cf0bc):goto L_002cf0bc;
 case UINT32_C(0x002cf0c0):goto L_002cf0c0;
 case UINT32_C(0x002cf0c4):goto L_002cf0c4;
 case UINT32_C(0x002cf0c8):goto L_002cf0c8;
 case UINT32_C(0x002cf0cc):goto L_002cf0cc;
 case UINT32_C(0x002cf0d0):goto L_002cf0d0;
 case UINT32_C(0x002cf0d4):goto L_002cf0d4;
 case UINT32_C(0x002cf0d8):goto L_002cf0d8;
 case UINT32_C(0x002cf0dc):goto L_002cf0dc;
 case UINT32_C(0x002cf0e0):goto L_002cf0e0;
 case UINT32_C(0x002cf0e4):goto L_002cf0e4;
 case UINT32_C(0x002cf0e8):goto L_002cf0e8;
 case UINT32_C(0x002cf0ec):goto L_002cf0ec;
 case UINT32_C(0x002cf0f0):goto L_002cf0f0;
 case UINT32_C(0x002cf0f4):goto L_002cf0f4;
 case UINT32_C(0x002cf0f8):goto L_002cf0f8;
 case UINT32_C(0x002cf0fc):goto L_002cf0fc;
 case UINT32_C(0x002cf100):goto L_002cf100;
 case UINT32_C(0x002cf104):goto L_002cf104;
 case UINT32_C(0x002cf108):goto L_002cf108;
 case UINT32_C(0x002cf10c):goto L_002cf10c;
 case UINT32_C(0x002cf110):goto L_002cf110;
 case UINT32_C(0x002cf114):goto L_002cf114;
 case UINT32_C(0x002cf118):goto L_002cf118;
 case UINT32_C(0x002cf11c):goto L_002cf11c;
 case UINT32_C(0x002cf120):goto L_002cf120;
 case UINT32_C(0x002cf124):goto L_002cf124;
 case UINT32_C(0x002cf128):goto L_002cf128;
 case UINT32_C(0x002cf12c):goto L_002cf12c;
 case UINT32_C(0x002cf130):goto L_002cf130;
 case UINT32_C(0x002cf134):goto L_002cf134;
 case UINT32_C(0x002cf138):goto L_002cf138;
 case UINT32_C(0x002cf13c):goto L_002cf13c;
 case UINT32_C(0x002cf140):goto L_002cf140;
 case UINT32_C(0x002cf144):goto L_002cf144;
 case UINT32_C(0x002cf148):goto L_002cf148;
 case UINT32_C(0x002cf14c):goto L_002cf14c;
 case UINT32_C(0x002cf150):goto L_002cf150;
 case UINT32_C(0x002cf154):goto L_002cf154;
 case UINT32_C(0x002cf158):goto L_002cf158;
 case UINT32_C(0x002cf15c):goto L_002cf15c;
 case UINT32_C(0x002cf160):goto L_002cf160;
 case UINT32_C(0x002cf164):goto L_002cf164;
 case UINT32_C(0x002cf168):goto L_002cf168;
 case UINT32_C(0x002cf16c):goto L_002cf16c;
 case UINT32_C(0x002cf170):goto L_002cf170;
 case UINT32_C(0x002cf174):goto L_002cf174;
 case UINT32_C(0x002cf178):goto L_002cf178;
 case UINT32_C(0x002cf17c):goto L_002cf17c;
 case UINT32_C(0x002cf180):goto L_002cf180;
 case UINT32_C(0x002cf184):goto L_002cf184;
 case UINT32_C(0x002cf188):goto L_002cf188;
 case UINT32_C(0x002cf18c):goto L_002cf18c;
 case UINT32_C(0x002cf190):goto L_002cf190;
 case UINT32_C(0x002cf194):goto L_002cf194;
 case UINT32_C(0x002cf198):goto L_002cf198;
 case UINT32_C(0x002cf19c):goto L_002cf19c;
 case UINT32_C(0x002cf1a0):goto L_002cf1a0;
 case UINT32_C(0x002cf1a4):goto L_002cf1a4;
 case UINT32_C(0x002cf1a8):goto L_002cf1a8;
 case UINT32_C(0x002cf1ac):goto L_002cf1ac;
 case UINT32_C(0x002cf1b0):goto L_002cf1b0;
 case UINT32_C(0x002cf1b4):goto L_002cf1b4;
 case UINT32_C(0x002cf1b8):goto L_002cf1b8;
 case UINT32_C(0x002cf1bc):goto L_002cf1bc;
 case UINT32_C(0x002cf1c0):goto L_002cf1c0;
 case UINT32_C(0x002cf1c4):goto L_002cf1c4;
 case UINT32_C(0x002cf1c8):goto L_002cf1c8;
 case UINT32_C(0x002cf1cc):goto L_002cf1cc;
 case UINT32_C(0x002cf1d0):goto L_002cf1d0;
 case UINT32_C(0x002cf1d4):goto L_002cf1d4;
 case UINT32_C(0x002cf1d8):goto L_002cf1d8;
 case UINT32_C(0x002cf1dc):goto L_002cf1dc;
 case UINT32_C(0x002cf1e0):goto L_002cf1e0;
 case UINT32_C(0x002cf1e4):goto L_002cf1e4;
 case UINT32_C(0x002cf1e8):goto L_002cf1e8;
 case UINT32_C(0x002cf1ec):goto L_002cf1ec;
 case UINT32_C(0x002cf1f0):goto L_002cf1f0;
 case UINT32_C(0x002cf1f4):goto L_002cf1f4;
 case UINT32_C(0x002cf1f8):goto L_002cf1f8;
 case UINT32_C(0x002cf1fc):goto L_002cf1fc;
 case UINT32_C(0x002cf200):goto L_002cf200;
 case UINT32_C(0x002cf204):goto L_002cf204;
 case UINT32_C(0x002cf208):goto L_002cf208;
 case UINT32_C(0x002cf20c):goto L_002cf20c;
 case UINT32_C(0x002cf210):goto L_002cf210;
 case UINT32_C(0x002cf214):goto L_002cf214;
 case UINT32_C(0x002cf218):goto L_002cf218;
 case UINT32_C(0x002cf21c):goto L_002cf21c;
 case UINT32_C(0x002cf220):goto L_002cf220;
 case UINT32_C(0x002cf224):goto L_002cf224;
 case UINT32_C(0x002cf228):goto L_002cf228;
 case UINT32_C(0x002cf22c):goto L_002cf22c;
 case UINT32_C(0x002cf230):goto L_002cf230;
 case UINT32_C(0x002cf234):goto L_002cf234;
 case UINT32_C(0x002cf238):goto L_002cf238;
 case UINT32_C(0x002cf23c):goto L_002cf23c;
 case UINT32_C(0x002cf240):goto L_002cf240;
 case UINT32_C(0x002cf244):goto L_002cf244;
 case UINT32_C(0x002cf248):goto L_002cf248;
 case UINT32_C(0x002cf24c):goto L_002cf24c;
 case UINT32_C(0x002cf250):goto L_002cf250;
 case UINT32_C(0x002cf254):goto L_002cf254;
 case UINT32_C(0x002cf258):goto L_002cf258;
 case UINT32_C(0x002cf25c):goto L_002cf25c;
 case UINT32_C(0x002cf260):goto L_002cf260;
 case UINT32_C(0x002cf264):goto L_002cf264;
 case UINT32_C(0x002cf268):goto L_002cf268;
 case UINT32_C(0x002cf26c):goto L_002cf26c;
 case UINT32_C(0x002cf270):goto L_002cf270;
 case UINT32_C(0x002cf274):goto L_002cf274;
 case UINT32_C(0x002cf278):goto L_002cf278;
 case UINT32_C(0x002cf27c):goto L_002cf27c;
 case UINT32_C(0x002cf280):goto L_002cf280;
 case UINT32_C(0x002cf284):goto L_002cf284;
 case UINT32_C(0x002cf288):goto L_002cf288;
 case UINT32_C(0x002cf28c):goto L_002cf28c;
 case UINT32_C(0x002cf290):goto L_002cf290;
 case UINT32_C(0x002cf294):goto L_002cf294;
 case UINT32_C(0x002cf298):goto L_002cf298;
 case UINT32_C(0x002cf29c):goto L_002cf29c;
 case UINT32_C(0x002cf2a0):goto L_002cf2a0;
 case UINT32_C(0x002cf2a4):goto L_002cf2a4;
 case UINT32_C(0x002cf2a8):goto L_002cf2a8;
 case UINT32_C(0x002cf2ac):goto L_002cf2ac;
 case UINT32_C(0x002cf2b0):goto L_002cf2b0;
 case UINT32_C(0x002cf2b4):goto L_002cf2b4;
 case UINT32_C(0x002cf2b8):goto L_002cf2b8;
 case UINT32_C(0x002cf2bc):goto L_002cf2bc;
 case UINT32_C(0x002cf2c0):goto L_002cf2c0;
 case UINT32_C(0x002cf2c4):goto L_002cf2c4;
 case UINT32_C(0x002cf2c8):goto L_002cf2c8;
 case UINT32_C(0x002cf2cc):goto L_002cf2cc;
 case UINT32_C(0x002cf2d0):goto L_002cf2d0;
 case UINT32_C(0x002cf2d4):goto L_002cf2d4;
 case UINT32_C(0x002cf2d8):goto L_002cf2d8;
 case UINT32_C(0x002cf2dc):goto L_002cf2dc;
 case UINT32_C(0x002cf2e0):goto L_002cf2e0;
 case UINT32_C(0x002cf2e4):goto L_002cf2e4;
 case UINT32_C(0x002cf2e8):goto L_002cf2e8;
 case UINT32_C(0x002cf2ec):goto L_002cf2ec;
 case UINT32_C(0x002cf2f0):goto L_002cf2f0;
 case UINT32_C(0x002cf2f4):goto L_002cf2f4;
 case UINT32_C(0x002cf2f8):goto L_002cf2f8;
 case UINT32_C(0x002cf2fc):goto L_002cf2fc;
 case UINT32_C(0x002cf300):goto L_002cf300;
 case UINT32_C(0x002cf304):goto L_002cf304;
 case UINT32_C(0x002cf308):goto L_002cf308;
 case UINT32_C(0x002cf30c):goto L_002cf30c;
 case UINT32_C(0x002cf310):goto L_002cf310;
 case UINT32_C(0x002cf314):goto L_002cf314;
 case UINT32_C(0x002cf318):goto L_002cf318;
 case UINT32_C(0x002cf31c):goto L_002cf31c;
 case UINT32_C(0x002cf320):goto L_002cf320;
 case UINT32_C(0x002cf324):goto L_002cf324;
 case UINT32_C(0x002cf328):goto L_002cf328;
 case UINT32_C(0x002cf32c):goto L_002cf32c;
 case UINT32_C(0x002cf330):goto L_002cf330;
 case UINT32_C(0x002cf334):goto L_002cf334;
 case UINT32_C(0x002cf338):goto L_002cf338;
 case UINT32_C(0x002cf33c):goto L_002cf33c;
 case UINT32_C(0x002cf340):goto L_002cf340;
 case UINT32_C(0x002cf344):goto L_002cf344;
 case UINT32_C(0x002cf348):goto L_002cf348;
 case UINT32_C(0x002cf34c):goto L_002cf34c;
 case UINT32_C(0x002cf350):goto L_002cf350;
 case UINT32_C(0x002cf354):goto L_002cf354;
 case UINT32_C(0x002cf358):goto L_002cf358;
 case UINT32_C(0x002cf35c):goto L_002cf35c;
 case UINT32_C(0x002cf360):goto L_002cf360;
 case UINT32_C(0x002cf364):goto L_002cf364;
 case UINT32_C(0x002cf368):goto L_002cf368;
 case UINT32_C(0x002cf36c):goto L_002cf36c;
 case UINT32_C(0x002cf370):goto L_002cf370;
 case UINT32_C(0x002cf374):goto L_002cf374;
 case UINT32_C(0x002cf378):goto L_002cf378;
 case UINT32_C(0x002cf37c):goto L_002cf37c;
 case UINT32_C(0x002cf380):goto L_002cf380;
 case UINT32_C(0x002cf384):goto L_002cf384;
 case UINT32_C(0x002cf388):goto L_002cf388;
 case UINT32_C(0x002cf38c):goto L_002cf38c;
 case UINT32_C(0x002cf390):goto L_002cf390;
 case UINT32_C(0x002cf394):goto L_002cf394;
 case UINT32_C(0x002cf398):goto L_002cf398;
 case UINT32_C(0x002cf39c):goto L_002cf39c;
 case UINT32_C(0x002cf3a0):goto L_002cf3a0;
 case UINT32_C(0x002cf3a4):goto L_002cf3a4;
 case UINT32_C(0x002cf3a8):goto L_002cf3a8;
 case UINT32_C(0x002cf3ac):goto L_002cf3ac;
 case UINT32_C(0x002cf3b0):goto L_002cf3b0;
 case UINT32_C(0x002cf3b4):goto L_002cf3b4;
 case UINT32_C(0x002cf3b8):goto L_002cf3b8;
 case UINT32_C(0x002cf3bc):goto L_002cf3bc;
 case UINT32_C(0x002cf3c0):goto L_002cf3c0;
 case UINT32_C(0x002cf3c4):goto L_002cf3c4;
 case UINT32_C(0x002cf3c8):goto L_002cf3c8;
 case UINT32_C(0x002cf3cc):goto L_002cf3cc;
 case UINT32_C(0x002cf3d0):goto L_002cf3d0;
 case UINT32_C(0x002cf3d4):goto L_002cf3d4;
 case UINT32_C(0x002cf3d8):goto L_002cf3d8;
 case UINT32_C(0x002cf3dc):goto L_002cf3dc;
 case UINT32_C(0x002cf3e0):goto L_002cf3e0;
 case UINT32_C(0x002cf3e4):goto L_002cf3e4;
 case UINT32_C(0x002cf3e8):goto L_002cf3e8;
 case UINT32_C(0x002cf3ec):goto L_002cf3ec;
 case UINT32_C(0x002cf3f0):goto L_002cf3f0;
 case UINT32_C(0x002cf3f4):goto L_002cf3f4;
 case UINT32_C(0x002cf3f8):goto L_002cf3f8;
 case UINT32_C(0x002cf3fc):goto L_002cf3fc;
 case UINT32_C(0x002cf400):goto L_002cf400;
 case UINT32_C(0x002cf404):goto L_002cf404;
 case UINT32_C(0x002cf408):goto L_002cf408;
 case UINT32_C(0x002cf40c):goto L_002cf40c;
 case UINT32_C(0x002cf410):goto L_002cf410;
 case UINT32_C(0x002cf414):goto L_002cf414;
 case UINT32_C(0x002cf418):goto L_002cf418;
 case UINT32_C(0x002cf41c):goto L_002cf41c;
 case UINT32_C(0x002cf420):goto L_002cf420;
 case UINT32_C(0x002cf424):goto L_002cf424;
 case UINT32_C(0x002cf428):goto L_002cf428;
 case UINT32_C(0x002cf42c):goto L_002cf42c;
 case UINT32_C(0x002cf430):goto L_002cf430;
 case UINT32_C(0x002cf434):goto L_002cf434;
 case UINT32_C(0x002cf438):goto L_002cf438;
 case UINT32_C(0x002cf43c):goto L_002cf43c;
 case UINT32_C(0x002cf440):goto L_002cf440;
 case UINT32_C(0x002cf444):goto L_002cf444;
 case UINT32_C(0x002cf448):goto L_002cf448;
 case UINT32_C(0x002cf44c):goto L_002cf44c;
 case UINT32_C(0x002cf450):goto L_002cf450;
 case UINT32_C(0x002cf454):goto L_002cf454;
 case UINT32_C(0x002cf458):goto L_002cf458;
 case UINT32_C(0x002cf45c):goto L_002cf45c;
 case UINT32_C(0x002cf460):goto L_002cf460;
 case UINT32_C(0x002cf464):goto L_002cf464;
 case UINT32_C(0x002cf468):goto L_002cf468;
 case UINT32_C(0x002cf46c):goto L_002cf46c;
 case UINT32_C(0x002cf470):goto L_002cf470;
 case UINT32_C(0x002cf474):goto L_002cf474;
 case UINT32_C(0x002cf478):goto L_002cf478;
 case UINT32_C(0x002cf47c):goto L_002cf47c;
 case UINT32_C(0x002cf480):goto L_002cf480;
 case UINT32_C(0x002cf484):goto L_002cf484;
 case UINT32_C(0x002cf488):goto L_002cf488;
 case UINT32_C(0x002cf48c):goto L_002cf48c;
 case UINT32_C(0x002cf490):goto L_002cf490;
 case UINT32_C(0x002cf494):goto L_002cf494;
 case UINT32_C(0x002cf498):goto L_002cf498;
 case UINT32_C(0x002cf49c):goto L_002cf49c;
 case UINT32_C(0x002cf4a0):goto L_002cf4a0;
 case UINT32_C(0x002cf4a4):goto L_002cf4a4;
 case UINT32_C(0x002cf4a8):goto L_002cf4a8;
 case UINT32_C(0x002cf4ac):goto L_002cf4ac;
 case UINT32_C(0x002cf4b0):goto L_002cf4b0;
 case UINT32_C(0x002cf4b4):goto L_002cf4b4;
 case UINT32_C(0x002cf4b8):goto L_002cf4b8;
 case UINT32_C(0x002cf4bc):goto L_002cf4bc;
 case UINT32_C(0x002cf4c0):goto L_002cf4c0;
 case UINT32_C(0x002cf4c4):goto L_002cf4c4;
 case UINT32_C(0x002cf4c8):goto L_002cf4c8;
 case UINT32_C(0x002cf4cc):goto L_002cf4cc;
 case UINT32_C(0x002cf4d0):goto L_002cf4d0;
 case UINT32_C(0x002cf4d4):goto L_002cf4d4;
 case UINT32_C(0x002cf4d8):goto L_002cf4d8;
 case UINT32_C(0x002cf4dc):goto L_002cf4dc;
 case UINT32_C(0x002cf4e0):goto L_002cf4e0;
 case UINT32_C(0x002cf4e4):goto L_002cf4e4;
 case UINT32_C(0x002cf4e8):goto L_002cf4e8;
 case UINT32_C(0x002cf4ec):goto L_002cf4ec;
 case UINT32_C(0x002cf4f0):goto L_002cf4f0;
 case UINT32_C(0x002cf4f4):goto L_002cf4f4;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002cdc90:
 STEP(UINT32_C(0x002cdc90)); /* 27bdff50 addiu sp,sp,-176 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff50)));target=sx(UINT32_C(0x002cdc94));goto dispatch;
L_002cdc94:
 STEP(UINT32_C(0x002cdc94)); /* ffb50080 sd s5,0x80(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002cdc98));goto dispatch;
L_002cdc98:
 STEP(UINT32_C(0x002cdc98)); /* 3c150053 lui s5,zero,0x53 */
 set(m,21u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cdc9c));goto dispatch;
L_002cdc9c:
 STEP(UINT32_C(0x002cdc9c)); /* ffbf00a0 sd ra,0xa0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),&value64,8u);target=sx(UINT32_C(0x002cdca0));goto dispatch;
L_002cdca0:
 STEP(UINT32_C(0x002cdca0)); /* 8ea2bb24 lw v0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cdca4));goto dispatch;
L_002cdca4:
 STEP(UINT32_C(0x002cdca4)); /* ffb60090 sd s6,0x90(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x002cdca8));goto dispatch;
L_002cdca8:
 STEP(UINT32_C(0x002cdca8)); /* ffb40070 sd s4,0x70(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002cdcac));goto dispatch;
L_002cdcac:
 STEP(UINT32_C(0x002cdcac)); /* ffb30060 sd s3,0x60(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002cdcb0));goto dispatch;
L_002cdcb0:
 STEP(UINT32_C(0x002cdcb0)); /* ffb20050 sd s2,0x50(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002cdcb4));goto dispatch;
L_002cdcb4:
 STEP(UINT32_C(0x002cdcb4)); /* ffb10040 sd s1,0x40(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cdcb8));goto dispatch;
L_002cdcb8:
 STEP(UINT32_C(0x002cdcb8)); /* 04410008 regimm1 v0,002cdcdc */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cdcbc));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(taken?UINT32_C(0x002cdcdc):UINT32_C(0x002cdcc0));goto dispatch;}
L_002cdcbc:
 STEP(UINT32_C(0x002cdcbc)); /* ffb00030 sd s0,0x30(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cdcc0));goto dispatch;
L_002cdcc0:
 STEP(UINT32_C(0x002cdcc0)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cdcc4));goto dispatch;
L_002cdcc4:
 STEP(UINT32_C(0x002cdcc4)); /* afa00024 sw zero,0x24(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002cdcc8));goto dispatch;
L_002cdcc8:
 STEP(UINT32_C(0x002cdcc8)); /* afa20014 sw v0,0x14(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002cdccc));goto dispatch;
L_002cdccc:
 STEP(UINT32_C(0x002cdccc)); /* 27a40010 addiu a0,sp,16 */
 set(m,4u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002cdcd0));goto dispatch;
L_002cdcd0:
 STEP(UINT32_C(0x002cdcd0)); /* 0c0b6fa8 jal 002dbea0 */
 set(m,31u,UINT64_C(0x002cdcd8));STEP(UINT32_C(0x002cdcd4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002dbea0));goto dispatch;
L_002cdcd4:
 STEP(UINT32_C(0x002cdcd4)); /* afa20018 sw v0,0x18(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002cdcd8));goto dispatch;
L_002cdcd8:
 STEP(UINT32_C(0x002cdcd8)); /* aea2bb24 sw v0,-0x44dc(s5) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);target=sx(UINT32_C(0x002cdcdc));goto dispatch;
L_002cdcdc:
 STEP(UINT32_C(0x002cdcdc)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdce0));goto dispatch;
L_002cdce0:
 STEP(UINT32_C(0x002cdce0)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdce4));goto dispatch;
L_002cdce4:
 STEP(UINT32_C(0x002cdce4)); /* 0c0b39b4 jal 002ce6d0 */
 set(m,31u,UINT64_C(0x002cdcec));STEP(UINT32_C(0x002cdce8));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce6d0));goto dispatch;
L_002cdce8:
 STEP(UINT32_C(0x002cdce8)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdcec));goto dispatch;
L_002cdcec:
 STEP(UINT32_C(0x002cdcec)); /* 0c0b6fb8 jal 002dbee0 */
 set(m,31u,UINT64_C(0x002cdcf4));STEP(UINT32_C(0x002cdcf0));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbee0));goto dispatch;
L_002cdcf0:
 STEP(UINT32_C(0x002cdcf0)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cdcf4));goto dispatch;
L_002cdcf4:
 STEP(UINT32_C(0x002cdcf4)); /* 0c0b7942 jal 002de508 */
 set(m,31u,UINT64_C(0x002cdcfc));STEP(UINT32_C(0x002cdcf8));set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002de508));goto dispatch;
L_002cdcf8:
 STEP(UINT32_C(0x002cdcf8)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdcfc));goto dispatch;
L_002cdcfc:
 STEP(UINT32_C(0x002cdcfc)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdd00));goto dispatch;
L_002cdd00:
 STEP(UINT32_C(0x002cdd00)); /* 3c16005a lui s6,zero,0x5a */
 set(m,22u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdd04));goto dispatch;
L_002cdd04:
 STEP(UINT32_C(0x002cdd04)); /* 1000000b beq zero,zero,002cdd34 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cdd08));set(m,20u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cdd34):UINT32_C(0x002cdd0c));goto dispatch;}
L_002cdd08:
 STEP(UINT32_C(0x002cdd08)); /* 3c14005a lui s4,zero,0x5a */
 set(m,20u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdd0c));goto dispatch;
L_002cdd0c:
 STEP(UINT32_C(0x002cdd0c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd10));goto dispatch;
L_002cdd10:
 STEP(UINT32_C(0x002cdd10)); /* 3c020010 lui v0,zero,0x10 */
 set(m,2u,sx(UINT32_C(0x00100000)));target=sx(UINT32_C(0x002cdd14));goto dispatch;
L_002cdd14:
 STEP(UINT32_C(0x002cdd14)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd18));goto dispatch;
L_002cdd18:
 STEP(UINT32_C(0x002cdd18)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002cdd1c));goto dispatch;
L_002cdd1c:
 STEP(UINT32_C(0x002cdd1c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd20));goto dispatch;
L_002cdd20:
 STEP(UINT32_C(0x002cdd20)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd24));goto dispatch;
L_002cdd24:
 STEP(UINT32_C(0x002cdd24)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd28));goto dispatch;
L_002cdd28:
 STEP(UINT32_C(0x002cdd28)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd2c));goto dispatch;
L_002cdd2c:
 STEP(UINT32_C(0x002cdd2c)); /* 1440fffa bne v0,zero,002cdd18 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cdd30));/* nop */target=sx(taken?UINT32_C(0x002cdd18):UINT32_C(0x002cdd34));goto dispatch;}
L_002cdd30:
 STEP(UINT32_C(0x002cdd30)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd34));goto dispatch;
L_002cdd34:
 STEP(UINT32_C(0x002cdd34)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x002cdd38));goto dispatch;
L_002cdd38:
 STEP(UINT32_C(0x002cdd38)); /* 26049740 addiu a0,s0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cdd3c));goto dispatch;
L_002cdd3c:
 STEP(UINT32_C(0x002cdd3c)); /* 34a50400 ori a1,a1,0x400 */
 set(m,5u,lo(m,5u) | UINT64_C(0x400));target=sx(UINT32_C(0x002cdd40));goto dispatch;
L_002cdd40:
 STEP(UINT32_C(0x002cdd40)); /* 0c0b7ade jal 002deb78 */
 set(m,31u,UINT64_C(0x002cdd48));STEP(UINT32_C(0x002cdd44));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002deb78));goto dispatch;
L_002cdd44:
 STEP(UINT32_C(0x002cdd44)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdd48));goto dispatch;
L_002cdd48:
 STEP(UINT32_C(0x002cdd48)); /* 0441000c regimm1 v0,002cdd7c */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cdd4c));set(m,18u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffff9740)));target=sx(taken?UINT32_C(0x002cdd7c):UINT32_C(0x002cdd50));goto dispatch;}
L_002cdd4c:
 STEP(UINT32_C(0x002cdd4c)); /* 26129740 addiu s2,s0,-26816 */
 set(m,18u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cdd50));goto dispatch;
L_002cdd50:
 STEP(UINT32_C(0x002cdd50)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002cdd54));goto dispatch;
L_002cdd54:
 STEP(UINT32_C(0x002cdd54)); /* 0c0b7758 jal 002ddd60 */
 set(m,31u,UINT64_C(0x002cdd5c));STEP(UINT32_C(0x002cdd58));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffae80)));target=sx(UINT32_C(0x002ddd60));goto dispatch;
L_002cdd58:
 STEP(UINT32_C(0x002cdd58)); /* 2484ae80 addiu a0,a0,-20864 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffae80)));target=sx(UINT32_C(0x002cdd5c));goto dispatch;
L_002cdd5c:
 STEP(UINT32_C(0x002cdd5c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd60));goto dispatch;
L_002cdd60:
 STEP(UINT32_C(0x002cdd60)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd64));goto dispatch;
L_002cdd64:
 STEP(UINT32_C(0x002cdd64)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd68));goto dispatch;
L_002cdd68:
 STEP(UINT32_C(0x002cdd68)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd6c));goto dispatch;
L_002cdd6c:
 STEP(UINT32_C(0x002cdd6c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd70));goto dispatch;
L_002cdd70:
 STEP(UINT32_C(0x002cdd70)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd74));goto dispatch;
L_002cdd74:
 STEP(UINT32_C(0x002cdd74)); /* 1000fffa beq zero,zero,002cdd60 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cdd78));/* nop */target=sx(taken?UINT32_C(0x002cdd60):UINT32_C(0x002cdd7c));goto dispatch;}
L_002cdd78:
 STEP(UINT32_C(0x002cdd78)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdd7c));goto dispatch;
L_002cdd7c:
 STEP(UINT32_C(0x002cdd7c)); /* 8e420024 lw v0,0x24(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000024),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cdd80));goto dispatch;
L_002cdd80:
 STEP(UINT32_C(0x002cdd80)); /* 1040ffe3 beq v0,zero,002cdd10 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002cdd84));set(m,19u,lo(m,18u)+lo(m,0u));target=sx(taken?UINT32_C(0x002cdd10):UINT32_C(0x002cdd88));goto dispatch;}
L_002cdd84:
 STEP(UINT32_C(0x002cdd84)); /* 0240982d daddu s3,s2,zero */
 set(m,19u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002cdd88));goto dispatch;
L_002cdd88:
 STEP(UINT32_C(0x002cdd88)); /* 2691ad00 addiu s1,s4,-21248 */
 set(m,17u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cdd8c));goto dispatch;
L_002cdd8c:
 STEP(UINT32_C(0x002cdd8c)); /* 0220482d daddu t1,s1,zero */
 set(m,9u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cdd90));goto dispatch;
L_002cdd90:
 STEP(UINT32_C(0x002cdd90)); /* 26c797c0 addiu a3,s6,-26688 */
 set(m,7u,sx((uint32_t)lo(m,22u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002cdd94));goto dispatch;
L_002cdd94:
 STEP(UINT32_C(0x002cdd94)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cdd98));goto dispatch;
L_002cdd98:
 STEP(UINT32_C(0x002cdd98)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002cdd9c));goto dispatch;
L_002cdd9c:
 STEP(UINT32_C(0x002cdd9c)); /* 240500fe addiu a1,zero,254 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000fe)));target=sx(UINT32_C(0x002cdda0));goto dispatch;
L_002cdda0:
 STEP(UINT32_C(0x002cdda0)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdda4));goto dispatch;
L_002cdda4:
 STEP(UINT32_C(0x002cdda4)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002cdda8));goto dispatch;
L_002cdda8:
 STEP(UINT32_C(0x002cdda8)); /* 240a000c addiu t2,zero,12 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002cddac));goto dispatch;
L_002cddac:
 STEP(UINT32_C(0x002cddac)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cddb4));STEP(UINT32_C(0x002cddb0));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cddb0:
 STEP(UINT32_C(0x002cddb0)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cddb4));goto dispatch;
L_002cddb4:
 STEP(UINT32_C(0x002cddb4)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cddb8));goto dispatch;
L_002cddb8:
 STEP(UINT32_C(0x002cddb8)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cddc0));STEP(UINT32_C(0x002cddbc));set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cddbc:
 STEP(UINT32_C(0x002cddbc)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cddc0));goto dispatch;
L_002cddc0:
 STEP(UINT32_C(0x002cddc0)); /* 06030004 regimm3 s0,002cddd4 */
 if((int64_t)lo(m,16u)>=0){STEP(UINT32_C(0x002cddc4));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cddd4));}else target=sx(UINT32_C(0x002cddc8));goto dispatch;
L_002cddc4:
 STEP(UINT32_C(0x002cddc4)); /* 8e220004 lw v0,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cddc8));goto dispatch;
L_002cddc8:
 STEP(UINT32_C(0x002cddc8)); /* ae600024 sw zero,0x24(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002cddcc));goto dispatch;
L_002cddcc:
 STEP(UINT32_C(0x002cddcc)); /* 10000013 beq zero,zero,002cde1c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cddd0));set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002cde1c):UINT32_C(0x002cddd4));goto dispatch;}
L_002cddd0:
 STEP(UINT32_C(0x002cddd0)); /* 2602ff9c addiu v0,s0,-100 */
 set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cddd4));goto dispatch;
L_002cddd4:
 STEP(UINT32_C(0x002cddd4)); /* 2842020a slti v0,v0,522 */
 set(m,2u,((int64_t)lo(m,2u)<INT64_C(522)));target=sx(UINT32_C(0x002cddd8));goto dispatch;
L_002cddd8:
 STEP(UINT32_C(0x002cddd8)); /* 10400006 beq v0,zero,002cddf4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002cdddc));set(m,4u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002cddf4):UINT32_C(0x002cdde0));goto dispatch;}
L_002cdddc:
 STEP(UINT32_C(0x002cdddc)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002cdde0));goto dispatch;
L_002cdde0:
 STEP(UINT32_C(0x002cdde0)); /* 0c0b7758 jal 002ddd60 */
 set(m,31u,UINT64_C(0x002cdde8));STEP(UINT32_C(0x002cdde4));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffae98)));target=sx(UINT32_C(0x002ddd60));goto dispatch;
L_002cdde4:
 STEP(UINT32_C(0x002cdde4)); /* 2484ae98 addiu a0,a0,-20840 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffae98)));target=sx(UINT32_C(0x002cdde8));goto dispatch;
L_002cdde8:
 STEP(UINT32_C(0x002cdde8)); /* ae600024 sw zero,0x24(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002cddec));goto dispatch;
L_002cddec:
 STEP(UINT32_C(0x002cddec)); /* 1000000b beq zero,zero,002cde1c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cddf0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff88)));target=sx(taken?UINT32_C(0x002cde1c):UINT32_C(0x002cddf4));goto dispatch;}
L_002cddf0:
 STEP(UINT32_C(0x002cddf0)); /* 2402ff88 addiu v0,zero,-120 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff88)));target=sx(UINT32_C(0x002cddf4));goto dispatch;
L_002cddf4:
 STEP(UINT32_C(0x002cddf4)); /* 8e220008 lw v0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cddf8));goto dispatch;
L_002cddf8:
 STEP(UINT32_C(0x002cddf8)); /* 2842020e slti v0,v0,526 */
 set(m,2u,((int64_t)lo(m,2u)<INT64_C(526)));target=sx(UINT32_C(0x002cddfc));goto dispatch;
L_002cddfc:
 STEP(UINT32_C(0x002cddfc)); /* 10400006 beq v0,zero,002cde18 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002cde00));set(m,4u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002cde18):UINT32_C(0x002cde04));goto dispatch;}
L_002cde00:
 STEP(UINT32_C(0x002cde00)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002cde04));goto dispatch;
L_002cde04:
 STEP(UINT32_C(0x002cde04)); /* 0c0b7758 jal 002ddd60 */
 set(m,31u,UINT64_C(0x002cde0c));STEP(UINT32_C(0x002cde08));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffaec0)));target=sx(UINT32_C(0x002ddd60));goto dispatch;
L_002cde08:
 STEP(UINT32_C(0x002cde08)); /* 2484aec0 addiu a0,a0,-20800 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffaec0)));target=sx(UINT32_C(0x002cde0c));goto dispatch;
L_002cde0c:
 STEP(UINT32_C(0x002cde0c)); /* ae400024 sw zero,0x24(s2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002cde10));goto dispatch;
L_002cde10:
 STEP(UINT32_C(0x002cde10)); /* 10000002 beq zero,zero,002cde1c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cde14));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff87)));target=sx(taken?UINT32_C(0x002cde1c):UINT32_C(0x002cde18));goto dispatch;}
L_002cde14:
 STEP(UINT32_C(0x002cde14)); /* 2402ff87 addiu v0,zero,-121 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff87)));target=sx(UINT32_C(0x002cde18));goto dispatch;
L_002cde18:
 STEP(UINT32_C(0x002cde18)); /* 8e82ad00 lw v0,-0x5300(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0xffffad00),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002cde1c));goto dispatch;
L_002cde1c:
 STEP(UINT32_C(0x002cde1c)); /* dfbf00a0 ld ra,0xa0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cde20));goto dispatch;
L_002cde20:
 STEP(UINT32_C(0x002cde20)); /* dfb60090 ld s6,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002cde24));goto dispatch;
L_002cde24:
 STEP(UINT32_C(0x002cde24)); /* dfb50080 ld s5,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002cde28));goto dispatch;
L_002cde28:
 STEP(UINT32_C(0x002cde28)); /* dfb40070 ld s4,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002cde2c));goto dispatch;
L_002cde2c:
 STEP(UINT32_C(0x002cde2c)); /* dfb30060 ld s3,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002cde30));goto dispatch;
L_002cde30:
 STEP(UINT32_C(0x002cde30)); /* dfb20050 ld s2,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cde34));goto dispatch;
L_002cde34:
 STEP(UINT32_C(0x002cde34)); /* dfb10040 ld s1,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cde38));goto dispatch;
L_002cde38:
 STEP(UINT32_C(0x002cde38)); /* dfb00030 ld s0,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cde3c));goto dispatch;
L_002cde3c:
 STEP(UINT32_C(0x002cde3c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cde40));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000b0)));goto dispatch;
L_002cde40:
 STEP(UINT32_C(0x002cde40)); /* 27bd00b0 addiu sp,sp,176 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000b0)));target=sx(UINT32_C(0x002cde44));goto dispatch;
L_002cde48:
 STEP(UINT32_C(0x002cde48)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002cde4c));goto dispatch;
L_002cde4c:
 STEP(UINT32_C(0x002cde4c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002cde50));goto dispatch;
L_002cde50:
 STEP(UINT32_C(0x002cde50)); /* 3c100053 lui s0,zero,0x53 */
 set(m,16u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cde54));goto dispatch;
L_002cde54:
 STEP(UINT32_C(0x002cde54)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cde58));goto dispatch;
L_002cde58:
 STEP(UINT32_C(0x002cde58)); /* 8e04bb24 lw a0,-0x44dc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cde5c));goto dispatch;
L_002cde5c:
 STEP(UINT32_C(0x002cde5c)); /* 04800006 regimm0 a0,002cde78 */
 {int taken=((int64_t)lo(m,4u)<0);STEP(UINT32_C(0x002cde60));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002cde78):UINT32_C(0x002cde64));goto dispatch;}
L_002cde60:
 STEP(UINT32_C(0x002cde60)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cde64));goto dispatch;
L_002cde64:
 STEP(UINT32_C(0x002cde64)); /* 0c0b6fac jal 002dbeb0 */
 set(m,31u,UINT64_C(0x002cde6c));STEP(UINT32_C(0x002cde68));/* nop */target=sx(UINT32_C(0x002dbeb0));goto dispatch;
L_002cde68:
 STEP(UINT32_C(0x002cde68)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cde6c));goto dispatch;
L_002cde6c:
 STEP(UINT32_C(0x002cde6c)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002cde70));goto dispatch;
L_002cde70:
 STEP(UINT32_C(0x002cde70)); /* ae03bb24 sw v1,-0x44dc(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0xffffbb24),&value32,4u);target=sx(UINT32_C(0x002cde74));goto dispatch;
L_002cde74:
 STEP(UINT32_C(0x002cde74)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cde78));goto dispatch;
L_002cde78:
 STEP(UINT32_C(0x002cde78)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cde7c));goto dispatch;
L_002cde7c:
 STEP(UINT32_C(0x002cde7c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cde80));goto dispatch;
L_002cde80:
 STEP(UINT32_C(0x002cde80)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cde84));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002cde84:
 STEP(UINT32_C(0x002cde84)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002cde88));goto dispatch;
L_002cde88:
 STEP(UINT32_C(0x002cde88)); /* 3c06005a lui a2,zero,0x5a */
 set(m,6u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cde8c));goto dispatch;
L_002cde8c:
 STEP(UINT32_C(0x002cde8c)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cde90));goto dispatch;
L_002cde90:
 STEP(UINT32_C(0x002cde90)); /* 24c6ad00 addiu a2,a2,-21248 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cde94));goto dispatch;
L_002cde94:
 STEP(UINT32_C(0x002cde94)); /* 2442bb20 addiu v0,v0,-17632 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffbb20)));target=sx(UINT32_C(0x002cde98));goto dispatch;
L_002cde98:
 STEP(UINT32_C(0x002cde98)); /* ac860000 sw a2,0x0(a0) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cde9c));goto dispatch;
L_002cde9c:
 STEP(UINT32_C(0x002cde9c)); /* aca20000 sw v0,0x0(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cdea0));goto dispatch;
L_002cdea0:
 STEP(UINT32_C(0x002cdea0)); /* 3c040053 lui a0,zero,0x53 */
 set(m,4u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cdea4));goto dispatch;
L_002cdea4:
 STEP(UINT32_C(0x002cdea4)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdea8));goto dispatch;
L_002cdea8:
 STEP(UINT32_C(0x002cdea8)); /* 8c83bb24 lw v1,-0x44dc(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0xffffbb24),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cdeac));goto dispatch;
L_002cdeac:
 STEP(UINT32_C(0x002cdeac)); /* 24429740 addiu v0,v0,-26816 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cdeb0));goto dispatch;
L_002cdeb0:
 STEP(UINT32_C(0x002cdeb0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cdeb4));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000003c),&value32,4u);goto dispatch;
L_002cdeb4:
 STEP(UINT32_C(0x002cdeb4)); /* acc3003c sw v1,0x3c(a2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000003c),&value32,4u);target=sx(UINT32_C(0x002cdeb8));goto dispatch;
L_002cdeb8:
 STEP(UINT32_C(0x002cdeb8)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002cdebc));goto dispatch;
L_002cdebc:
 STEP(UINT32_C(0x002cdebc)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cdec0));goto dispatch;
L_002cdec0:
 STEP(UINT32_C(0x002cdec0)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cdec4));goto dispatch;
L_002cdec4:
 STEP(UINT32_C(0x002cdec4)); /* 3c110053 lui s1,zero,0x53 */
 set(m,17u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cdec8));goto dispatch;
L_002cdec8:
 STEP(UINT32_C(0x002cdec8)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cdecc));goto dispatch;
L_002cdecc:
 STEP(UINT32_C(0x002cdecc)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cded0));goto dispatch;
L_002cded0:
 STEP(UINT32_C(0x002cded0)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cded8));STEP(UINT32_C(0x002cded4));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cded4:
 STEP(UINT32_C(0x002cded4)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cded8));goto dispatch;
L_002cded8:
 STEP(UINT32_C(0x002cded8)); /* 04410003 regimm1 v0,002cdee8 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cdedc));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cdee8):UINT32_C(0x002cdee0));goto dispatch;}
L_002cdedc:
 STEP(UINT32_C(0x002cdedc)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdee0));goto dispatch;
L_002cdee0:
 STEP(UINT32_C(0x002cdee0)); /* 1000001d beq zero,zero,002cdf58 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cdee4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002cdf58):UINT32_C(0x002cdee8));goto dispatch;}
L_002cdee4:
 STEP(UINT32_C(0x002cdee4)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cdee8));goto dispatch;
L_002cdee8:
 STEP(UINT32_C(0x002cdee8)); /* 24449740 addiu a0,v0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cdeec));goto dispatch;
L_002cdeec:
 STEP(UINT32_C(0x002cdeec)); /* 8c830024 lw v1,0x24(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cdef0));goto dispatch;
L_002cdef0:
 STEP(UINT32_C(0x002cdef0)); /* 14600005 bne v1,zero,002cdf08 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cdef4));set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cdf08):UINT32_C(0x002cdef8));goto dispatch;}
L_002cdef4:
 STEP(UINT32_C(0x002cdef4)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdef8));goto dispatch;
L_002cdef8:
 STEP(UINT32_C(0x002cdef8)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cdf00));STEP(UINT32_C(0x002cdefc));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cdefc:
 STEP(UINT32_C(0x002cdefc)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cdf00));goto dispatch;
L_002cdf00:
 STEP(UINT32_C(0x002cdf00)); /* 10000015 beq zero,zero,002cdf58 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cdf04));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002cdf58):UINT32_C(0x002cdf08));goto dispatch;}
L_002cdf04:
 STEP(UINT32_C(0x002cdf04)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cdf08));goto dispatch;
L_002cdf08:
 STEP(UINT32_C(0x002cdf08)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdf0c));goto dispatch;
L_002cdf0c:
 STEP(UINT32_C(0x002cdf0c)); /* 24e797c0 addiu a3,a3,-26688 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002cdf10));goto dispatch;
L_002cdf10:
 STEP(UINT32_C(0x002cdf10)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cdf14));goto dispatch;
L_002cdf14:
 STEP(UINT32_C(0x002cdf14)); /* acf00014 sw s0,0x14(a3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002cdf18));goto dispatch;
L_002cdf18:
 STEP(UINT32_C(0x002cdf18)); /* 24050014 addiu a1,zero,20 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002cdf1c));goto dispatch;
L_002cdf1c:
 STEP(UINT32_C(0x002cdf1c)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cdf20));goto dispatch;
L_002cdf20:
 STEP(UINT32_C(0x002cdf20)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cdf24));goto dispatch;
L_002cdf24:
 STEP(UINT32_C(0x002cdf24)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002cdf28));goto dispatch;
L_002cdf28:
 STEP(UINT32_C(0x002cdf28)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cdf2c));goto dispatch;
L_002cdf2c:
 STEP(UINT32_C(0x002cdf2c)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cdf34));STEP(UINT32_C(0x002cdf30));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cdf30:
 STEP(UINT32_C(0x002cdf30)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdf34));goto dispatch;
L_002cdf34:
 STEP(UINT32_C(0x002cdf34)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cdf38));goto dispatch;
L_002cdf38:
 STEP(UINT32_C(0x002cdf38)); /* 16000004 bne s0,zero,002cdf4c */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cdf3c));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002cdf4c):UINT32_C(0x002cdf40));goto dispatch;}
L_002cdf3c:
 STEP(UINT32_C(0x002cdf3c)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cdf40));goto dispatch;
L_002cdf40:
 STEP(UINT32_C(0x002cdf40)); /* 24020014 addiu v0,zero,20 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002cdf44));goto dispatch;
L_002cdf44:
 STEP(UINT32_C(0x002cdf44)); /* 10000003 beq zero,zero,002cdf54 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cdf48));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002cdf54):UINT32_C(0x002cdf4c));goto dispatch;}
L_002cdf48:
 STEP(UINT32_C(0x002cdf48)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002cdf4c));goto dispatch;
L_002cdf4c:
 STEP(UINT32_C(0x002cdf4c)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cdf54));STEP(UINT32_C(0x002cdf50));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cdf50:
 STEP(UINT32_C(0x002cdf50)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cdf54));goto dispatch;
L_002cdf54:
 STEP(UINT32_C(0x002cdf54)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cdf58));goto dispatch;
L_002cdf58:
 STEP(UINT32_C(0x002cdf58)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cdf5c));goto dispatch;
L_002cdf5c:
 STEP(UINT32_C(0x002cdf5c)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cdf60));goto dispatch;
L_002cdf60:
 STEP(UINT32_C(0x002cdf60)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cdf64));goto dispatch;
L_002cdf64:
 STEP(UINT32_C(0x002cdf64)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cdf68));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002cdf68:
 STEP(UINT32_C(0x002cdf68)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002cdf6c));goto dispatch;
L_002cdf70:
 STEP(UINT32_C(0x002cdf70)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x002cdf74));goto dispatch;
L_002cdf74:
 STEP(UINT32_C(0x002cdf74)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cdf78));goto dispatch;
L_002cdf78:
 STEP(UINT32_C(0x002cdf78)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cdf7c));goto dispatch;
L_002cdf7c:
 STEP(UINT32_C(0x002cdf7c)); /* 3c110053 lui s1,zero,0x53 */
 set(m,17u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cdf80));goto dispatch;
L_002cdf80:
 STEP(UINT32_C(0x002cdf80)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cdf84));goto dispatch;
L_002cdf84:
 STEP(UINT32_C(0x002cdf84)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cdf88));goto dispatch;
L_002cdf88:
 STEP(UINT32_C(0x002cdf88)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cdf8c));goto dispatch;
L_002cdf8c:
 STEP(UINT32_C(0x002cdf8c)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cdf94));STEP(UINT32_C(0x002cdf90));value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cdf90:
 STEP(UINT32_C(0x002cdf90)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cdf94));goto dispatch;
L_002cdf94:
 STEP(UINT32_C(0x002cdf94)); /* 04410003 regimm1 v0,002cdfa4 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cdf98));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cdfa4):UINT32_C(0x002cdf9c));goto dispatch;}
L_002cdf98:
 STEP(UINT32_C(0x002cdf98)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdf9c));goto dispatch;
L_002cdf9c:
 STEP(UINT32_C(0x002cdf9c)); /* 1000001e beq zero,zero,002ce018 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cdfa0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ce018):UINT32_C(0x002cdfa4));goto dispatch;}
L_002cdfa0:
 STEP(UINT32_C(0x002cdfa0)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cdfa4));goto dispatch;
L_002cdfa4:
 STEP(UINT32_C(0x002cdfa4)); /* 24449740 addiu a0,v0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cdfa8));goto dispatch;
L_002cdfa8:
 STEP(UINT32_C(0x002cdfa8)); /* 8c830024 lw v1,0x24(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cdfac));goto dispatch;
L_002cdfac:
 STEP(UINT32_C(0x002cdfac)); /* 14600005 bne v1,zero,002cdfc4 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cdfb0));set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cdfc4):UINT32_C(0x002cdfb4));goto dispatch;}
L_002cdfb0:
 STEP(UINT32_C(0x002cdfb0)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdfb4));goto dispatch;
L_002cdfb4:
 STEP(UINT32_C(0x002cdfb4)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cdfbc));STEP(UINT32_C(0x002cdfb8));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cdfb8:
 STEP(UINT32_C(0x002cdfb8)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cdfbc));goto dispatch;
L_002cdfbc:
 STEP(UINT32_C(0x002cdfbc)); /* 10000016 beq zero,zero,002ce018 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cdfc0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ce018):UINT32_C(0x002cdfc4));goto dispatch;}
L_002cdfc0:
 STEP(UINT32_C(0x002cdfc0)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cdfc4));goto dispatch;
L_002cdfc4:
 STEP(UINT32_C(0x002cdfc4)); /* 3c12005a lui s2,zero,0x5a */
 set(m,18u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cdfc8));goto dispatch;
L_002cdfc8:
 STEP(UINT32_C(0x002cdfc8)); /* 24e797c0 addiu a3,a3,-26688 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002cdfcc));goto dispatch;
L_002cdfcc:
 STEP(UINT32_C(0x002cdfcc)); /* 24050015 addiu a1,zero,21 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000015)));target=sx(UINT32_C(0x002cdfd0));goto dispatch;
L_002cdfd0:
 STEP(UINT32_C(0x002cdfd0)); /* acf00004 sw s0,0x4(a3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002cdfd4));goto dispatch;
L_002cdfd4:
 STEP(UINT32_C(0x002cdfd4)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdfd8));goto dispatch;
L_002cdfd8:
 STEP(UINT32_C(0x002cdfd8)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cdfdc));goto dispatch;
L_002cdfdc:
 STEP(UINT32_C(0x002cdfdc)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002cdfe0));goto dispatch;
L_002cdfe0:
 STEP(UINT32_C(0x002cdfe0)); /* 2649ad00 addiu t1,s2,-21248 */
 set(m,9u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cdfe4));goto dispatch;
L_002cdfe4:
 STEP(UINT32_C(0x002cdfe4)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cdfe8));goto dispatch;
L_002cdfe8:
 STEP(UINT32_C(0x002cdfe8)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cdff0));STEP(UINT32_C(0x002cdfec));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cdfec:
 STEP(UINT32_C(0x002cdfec)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cdff0));goto dispatch;
L_002cdff0:
 STEP(UINT32_C(0x002cdff0)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cdff4));goto dispatch;
L_002cdff4:
 STEP(UINT32_C(0x002cdff4)); /* 12000005 beq s0,zero,002ce00c */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002cdff8));/* nop */target=sx(taken?UINT32_C(0x002ce00c):UINT32_C(0x002cdffc));goto dispatch;}
L_002cdff8:
 STEP(UINT32_C(0x002cdff8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cdffc));goto dispatch;
L_002cdffc:
 STEP(UINT32_C(0x002cdffc)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce004));STEP(UINT32_C(0x002ce000));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce000:
 STEP(UINT32_C(0x002ce000)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce004));goto dispatch;
L_002ce004:
 STEP(UINT32_C(0x002ce004)); /* 10000004 beq zero,zero,002ce018 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce008));set(m,2u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002ce018):UINT32_C(0x002ce00c));goto dispatch;}
L_002ce008:
 STEP(UINT32_C(0x002ce008)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce00c));goto dispatch;
L_002ce00c:
 STEP(UINT32_C(0x002ce00c)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce014));STEP(UINT32_C(0x002ce010));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce010:
 STEP(UINT32_C(0x002ce010)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce014));goto dispatch;
L_002ce014:
 STEP(UINT32_C(0x002ce014)); /* 8e42ad00 lw v0,-0x5300(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffad00),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce018));goto dispatch;
L_002ce018:
 STEP(UINT32_C(0x002ce018)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce01c));goto dispatch;
L_002ce01c:
 STEP(UINT32_C(0x002ce01c)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ce020));goto dispatch;
L_002ce020:
 STEP(UINT32_C(0x002ce020)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce024));goto dispatch;
L_002ce024:
 STEP(UINT32_C(0x002ce024)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce028));goto dispatch;
L_002ce028:
 STEP(UINT32_C(0x002ce028)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce02c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_002ce02c:
 STEP(UINT32_C(0x002ce02c)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x002ce030));goto dispatch;
L_002ce030:
 STEP(UINT32_C(0x002ce030)); /* 27bdff70 addiu sp,sp,-144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff70)));target=sx(UINT32_C(0x002ce034));goto dispatch;
L_002ce034:
 STEP(UINT32_C(0x002ce034)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002ce038));goto dispatch;
L_002ce038:
 STEP(UINT32_C(0x002ce038)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ce03c));goto dispatch;
L_002ce03c:
 STEP(UINT32_C(0x002ce03c)); /* 0080a82d daddu s5,a0,zero */
 set(m,21u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ce040));goto dispatch;
L_002ce040:
 STEP(UINT32_C(0x002ce040)); /* 3c120053 lui s2,zero,0x53 */
 set(m,18u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce044));goto dispatch;
L_002ce044:
 STEP(UINT32_C(0x002ce044)); /* ffb60070 sd s6,0x70(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002ce048));goto dispatch;
L_002ce048:
 STEP(UINT32_C(0x002ce048)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ce04c));goto dispatch;
L_002ce04c:
 STEP(UINT32_C(0x002ce04c)); /* 00a0b02d daddu s6,a1,zero */
 set(m,22u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002ce050));goto dispatch;
L_002ce050:
 STEP(UINT32_C(0x002ce050)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce054));goto dispatch;
L_002ce054:
 STEP(UINT32_C(0x002ce054)); /* 00e0982d daddu s3,a3,zero */
 set(m,19u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002ce058));goto dispatch;
L_002ce058:
 STEP(UINT32_C(0x002ce058)); /* 8e44bb24 lw a0,-0x44dc(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce05c));goto dispatch;
L_002ce05c:
 STEP(UINT32_C(0x002ce05c)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002ce060));goto dispatch;
L_002ce060:
 STEP(UINT32_C(0x002ce060)); /* ffbf0080 sd ra,0x80(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002ce064));goto dispatch;
L_002ce064:
 STEP(UINT32_C(0x002ce064)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002ce068));goto dispatch;
L_002ce068:
 STEP(UINT32_C(0x002ce068)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002ce070));STEP(UINT32_C(0x002ce06c));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002ce06c:
 STEP(UINT32_C(0x002ce06c)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce070));goto dispatch;
L_002ce070:
 STEP(UINT32_C(0x002ce070)); /* 04410003 regimm1 v0,002ce080 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002ce074));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce080):UINT32_C(0x002ce078));goto dispatch;}
L_002ce074:
 STEP(UINT32_C(0x002ce074)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce078));goto dispatch;
L_002ce078:
 STEP(UINT32_C(0x002ce078)); /* 10000030 beq zero,zero,002ce13c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce07c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ce13c):UINT32_C(0x002ce080));goto dispatch;}
L_002ce07c:
 STEP(UINT32_C(0x002ce07c)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002ce080));goto dispatch;
L_002ce080:
 STEP(UINT32_C(0x002ce080)); /* 24549740 addiu s4,v0,-26816 */
 set(m,20u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce084));goto dispatch;
L_002ce084:
 STEP(UINT32_C(0x002ce084)); /* 8e830024 lw v1,0x24(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce088));goto dispatch;
L_002ce088:
 STEP(UINT32_C(0x002ce088)); /* 14600005 bne v1,zero,002ce0a0 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002ce08c));/* nop */target=sx(taken?UINT32_C(0x002ce0a0):UINT32_C(0x002ce090));goto dispatch;}
L_002ce08c:
 STEP(UINT32_C(0x002ce08c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce090));goto dispatch;
L_002ce090:
 STEP(UINT32_C(0x002ce090)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce098));STEP(UINT32_C(0x002ce094));READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce094:
 STEP(UINT32_C(0x002ce094)); /* 8e44bb24 lw a0,-0x44dc(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce098));goto dispatch;
L_002ce098:
 STEP(UINT32_C(0x002ce098)); /* 10000028 beq zero,zero,002ce13c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce09c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ce13c):UINT32_C(0x002ce0a0));goto dispatch;}
L_002ce09c:
 STEP(UINT32_C(0x002ce09c)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002ce0a0));goto dispatch;
L_002ce0a0:
 STEP(UINT32_C(0x002ce0a0)); /* 12200004 beq s1,zero,002ce0b4 */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002ce0a4));/* nop */target=sx(taken?UINT32_C(0x002ce0b4):UINT32_C(0x002ce0a8));goto dispatch;}
L_002ce0a4:
 STEP(UINT32_C(0x002ce0a4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce0a8));goto dispatch;
L_002ce0a8:
 STEP(UINT32_C(0x002ce0a8)); /* 82220000 lb v0,0x0(s1) */
 {uint8_t byte;READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002ce0ac));goto dispatch;
L_002ce0ac:
 STEP(UINT32_C(0x002ce0ac)); /* 14400005 bne v0,zero,002ce0c4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002ce0b0));set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce0c4):UINT32_C(0x002ce0b4));goto dispatch;}
L_002ce0b0:
 STEP(UINT32_C(0x002ce0b0)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce0b4));goto dispatch;
L_002ce0b4:
 STEP(UINT32_C(0x002ce0b4)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce0bc));STEP(UINT32_C(0x002ce0b8));READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce0b8:
 STEP(UINT32_C(0x002ce0b8)); /* 8e44bb24 lw a0,-0x44dc(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce0bc));goto dispatch;
L_002ce0bc:
 STEP(UINT32_C(0x002ce0bc)); /* 1000001f beq zero,zero,002ce13c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce0c0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(taken?UINT32_C(0x002ce13c):UINT32_C(0x002ce0c4));goto dispatch;}
L_002ce0c0:
 STEP(UINT32_C(0x002ce0c0)); /* 2402ff2e addiu v0,zero,-210 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(UINT32_C(0x002ce0c4));goto dispatch;
L_002ce0c4:
 STEP(UINT32_C(0x002ce0c4)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002ce0c8));goto dispatch;
L_002ce0c8:
 STEP(UINT32_C(0x002ce0c8)); /* 26109804 addiu s0,s0,-26620 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffff9804)));target=sx(UINT32_C(0x002ce0cc));goto dispatch;
L_002ce0cc:
 STEP(UINT32_C(0x002ce0cc)); /* 240603ff addiu a2,zero,1023 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002ce0d0));goto dispatch;
L_002ce0d0:
 STEP(UINT32_C(0x002ce0d0)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002ce0d8));STEP(UINT32_C(0x002ce0d4));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002ce0d4:
 STEP(UINT32_C(0x002ce0d4)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce0d8));goto dispatch;
L_002ce0d8:
 STEP(UINT32_C(0x002ce0d8)); /* 2603ffec addiu v1,s0,-20 */
 set(m,3u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffec)));target=sx(UINT32_C(0x002ce0dc));goto dispatch;
L_002ce0dc:
 STEP(UINT32_C(0x002ce0dc)); /* ae15ffec sw s5,-0x14(s0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0xffffffec),&value32,4u);target=sx(UINT32_C(0x002ce0e0));goto dispatch;
L_002ce0e0:
 STEP(UINT32_C(0x002ce0e0)); /* ac730008 sw s3,0x8(v1) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002ce0e4));goto dispatch;
L_002ce0e4:
 STEP(UINT32_C(0x002ce0e4)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce0e8));goto dispatch;
L_002ce0e8:
 STEP(UINT32_C(0x002ce0e8)); /* ac760004 sw s6,0x4(v1) */
 value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002ce0ec));goto dispatch;
L_002ce0ec:
 STEP(UINT32_C(0x002ce0ec)); /* 0280202d daddu a0,s4,zero */
 set(m,4u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002ce0f0));goto dispatch;
L_002ce0f0:
 STEP(UINT32_C(0x002ce0f0)); /* a0600413 sb zero,0x413(v1) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000413),&byte,1u);}target=sx(UINT32_C(0x002ce0f4));goto dispatch;
L_002ce0f4:
 STEP(UINT32_C(0x002ce0f4)); /* 0060382d daddu a3,v1,zero */
 set(m,7u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002ce0f8));goto dispatch;
L_002ce0f8:
 STEP(UINT32_C(0x002ce0f8)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ce0fc));goto dispatch;
L_002ce0fc:
 STEP(UINT32_C(0x002ce0fc)); /* 24050002 addiu a1,zero,2 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002ce100));goto dispatch;
L_002ce100:
 STEP(UINT32_C(0x002ce100)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce104));goto dispatch;
L_002ce104:
 STEP(UINT32_C(0x002ce104)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce108));goto dispatch;
L_002ce108:
 STEP(UINT32_C(0x002ce108)); /* 24080414 addiu t0,zero,1044 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000414)));target=sx(UINT32_C(0x002ce10c));goto dispatch;
L_002ce10c:
 STEP(UINT32_C(0x002ce10c)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce110));goto dispatch;
L_002ce110:
 STEP(UINT32_C(0x002ce110)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ce118));STEP(UINT32_C(0x002ce114));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ce114:
 STEP(UINT32_C(0x002ce114)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce118));goto dispatch;
L_002ce118:
 STEP(UINT32_C(0x002ce118)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce11c));goto dispatch;
L_002ce11c:
 STEP(UINT32_C(0x002ce11c)); /* 16000004 bne s0,zero,002ce130 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002ce120));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002ce130):UINT32_C(0x002ce124));goto dispatch;}
L_002ce120:
 STEP(UINT32_C(0x002ce120)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce124));goto dispatch;
L_002ce124:
 STEP(UINT32_C(0x002ce124)); /* 24020002 addiu v0,zero,2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002ce128));goto dispatch;
L_002ce128:
 STEP(UINT32_C(0x002ce128)); /* 10000003 beq zero,zero,002ce138 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce12c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ce138):UINT32_C(0x002ce130));goto dispatch;}
L_002ce12c:
 STEP(UINT32_C(0x002ce12c)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ce130));goto dispatch;
L_002ce130:
 STEP(UINT32_C(0x002ce130)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce138));STEP(UINT32_C(0x002ce134));READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce134:
 STEP(UINT32_C(0x002ce134)); /* 8e44bb24 lw a0,-0x44dc(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce138));goto dispatch;
L_002ce138:
 STEP(UINT32_C(0x002ce138)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce13c));goto dispatch;
L_002ce13c:
 STEP(UINT32_C(0x002ce13c)); /* dfbf0080 ld ra,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce140));goto dispatch;
L_002ce140:
 STEP(UINT32_C(0x002ce140)); /* dfb60070 ld s6,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002ce144));goto dispatch;
L_002ce144:
 STEP(UINT32_C(0x002ce144)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002ce148));goto dispatch;
L_002ce148:
 STEP(UINT32_C(0x002ce148)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002ce14c));goto dispatch;
L_002ce14c:
 STEP(UINT32_C(0x002ce14c)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002ce150));goto dispatch;
L_002ce150:
 STEP(UINT32_C(0x002ce150)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ce154));goto dispatch;
L_002ce154:
 STEP(UINT32_C(0x002ce154)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce158));goto dispatch;
L_002ce158:
 STEP(UINT32_C(0x002ce158)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce15c));goto dispatch;
L_002ce15c:
 STEP(UINT32_C(0x002ce15c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce160));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));goto dispatch;
L_002ce160:
 STEP(UINT32_C(0x002ce160)); /* 27bd0090 addiu sp,sp,144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));target=sx(UINT32_C(0x002ce164));goto dispatch;
L_002ce168:
 STEP(UINT32_C(0x002ce168)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002ce16c));goto dispatch;
L_002ce16c:
 STEP(UINT32_C(0x002ce16c)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002ce170));goto dispatch;
L_002ce170:
 STEP(UINT32_C(0x002ce170)); /* 0c0b380c jal 002ce030 */
 set(m,31u,UINT64_C(0x002ce178));STEP(UINT32_C(0x002ce174));set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002ce030));goto dispatch;
L_002ce174:
 STEP(UINT32_C(0x002ce174)); /* 24070040 addiu a3,zero,64 */
 set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002ce178));goto dispatch;
L_002ce178:
 STEP(UINT32_C(0x002ce178)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce17c));goto dispatch;
L_002ce17c:
 STEP(UINT32_C(0x002ce17c)); /* 14800004 bne a0,zero,002ce190 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002ce180));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002ce190):UINT32_C(0x002ce184));goto dispatch;}
L_002ce180:
 STEP(UINT32_C(0x002ce180)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce184));goto dispatch;
L_002ce184:
 STEP(UINT32_C(0x002ce184)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce188));goto dispatch;
L_002ce188:
 STEP(UINT32_C(0x002ce188)); /* 2402000b addiu v0,zero,11 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000b)));target=sx(UINT32_C(0x002ce18c));goto dispatch;
L_002ce18c:
 STEP(UINT32_C(0x002ce18c)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ce190));goto dispatch;
L_002ce190:
 STEP(UINT32_C(0x002ce190)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ce194));goto dispatch;
L_002ce194:
 STEP(UINT32_C(0x002ce194)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce198));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002ce198:
 STEP(UINT32_C(0x002ce198)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002ce19c));goto dispatch;
L_002ce1a0:
 STEP(UINT32_C(0x002ce1a0)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002ce1a4));goto dispatch;
L_002ce1a4:
 STEP(UINT32_C(0x002ce1a4)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce1a8));goto dispatch;
L_002ce1a8:
 STEP(UINT32_C(0x002ce1a8)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce1ac));goto dispatch;
L_002ce1ac:
 STEP(UINT32_C(0x002ce1ac)); /* 3c110053 lui s1,zero,0x53 */
 set(m,17u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce1b0));goto dispatch;
L_002ce1b0:
 STEP(UINT32_C(0x002ce1b0)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ce1b4));goto dispatch;
L_002ce1b4:
 STEP(UINT32_C(0x002ce1b4)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ce1b8));goto dispatch;
L_002ce1b8:
 STEP(UINT32_C(0x002ce1b8)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002ce1c0));STEP(UINT32_C(0x002ce1bc));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002ce1bc:
 STEP(UINT32_C(0x002ce1bc)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce1c0));goto dispatch;
L_002ce1c0:
 STEP(UINT32_C(0x002ce1c0)); /* 04410003 regimm1 v0,002ce1d0 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002ce1c4));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce1d0):UINT32_C(0x002ce1c8));goto dispatch;}
L_002ce1c4:
 STEP(UINT32_C(0x002ce1c4)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce1c8));goto dispatch;
L_002ce1c8:
 STEP(UINT32_C(0x002ce1c8)); /* 1000001d beq zero,zero,002ce240 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce1cc));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ce240):UINT32_C(0x002ce1d0));goto dispatch;}
L_002ce1cc:
 STEP(UINT32_C(0x002ce1cc)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002ce1d0));goto dispatch;
L_002ce1d0:
 STEP(UINT32_C(0x002ce1d0)); /* 24449740 addiu a0,v0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce1d4));goto dispatch;
L_002ce1d4:
 STEP(UINT32_C(0x002ce1d4)); /* 8c830024 lw v1,0x24(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce1d8));goto dispatch;
L_002ce1d8:
 STEP(UINT32_C(0x002ce1d8)); /* 14600005 bne v1,zero,002ce1f0 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002ce1dc));set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce1f0):UINT32_C(0x002ce1e0));goto dispatch;}
L_002ce1dc:
 STEP(UINT32_C(0x002ce1dc)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce1e0));goto dispatch;
L_002ce1e0:
 STEP(UINT32_C(0x002ce1e0)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce1e8));STEP(UINT32_C(0x002ce1e4));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce1e4:
 STEP(UINT32_C(0x002ce1e4)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce1e8));goto dispatch;
L_002ce1e8:
 STEP(UINT32_C(0x002ce1e8)); /* 10000015 beq zero,zero,002ce240 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce1ec));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ce240):UINT32_C(0x002ce1f0));goto dispatch;}
L_002ce1ec:
 STEP(UINT32_C(0x002ce1ec)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002ce1f0));goto dispatch;
L_002ce1f0:
 STEP(UINT32_C(0x002ce1f0)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce1f4));goto dispatch;
L_002ce1f4:
 STEP(UINT32_C(0x002ce1f4)); /* acf097c0 sw s0,-0x6840(a3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffff97c0),&value32,4u);target=sx(UINT32_C(0x002ce1f8));goto dispatch;
L_002ce1f8:
 STEP(UINT32_C(0x002ce1f8)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ce1fc));goto dispatch;
L_002ce1fc:
 STEP(UINT32_C(0x002ce1fc)); /* 24e797c0 addiu a3,a3,-26688 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce200));goto dispatch;
L_002ce200:
 STEP(UINT32_C(0x002ce200)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce204));goto dispatch;
L_002ce204:
 STEP(UINT32_C(0x002ce204)); /* 24050003 addiu a1,zero,3 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002ce208));goto dispatch;
L_002ce208:
 STEP(UINT32_C(0x002ce208)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce20c));goto dispatch;
L_002ce20c:
 STEP(UINT32_C(0x002ce20c)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002ce210));goto dispatch;
L_002ce210:
 STEP(UINT32_C(0x002ce210)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce214));goto dispatch;
L_002ce214:
 STEP(UINT32_C(0x002ce214)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ce21c));STEP(UINT32_C(0x002ce218));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ce218:
 STEP(UINT32_C(0x002ce218)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce21c));goto dispatch;
L_002ce21c:
 STEP(UINT32_C(0x002ce21c)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce220));goto dispatch;
L_002ce220:
 STEP(UINT32_C(0x002ce220)); /* 16000004 bne s0,zero,002ce234 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002ce224));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002ce234):UINT32_C(0x002ce228));goto dispatch;}
L_002ce224:
 STEP(UINT32_C(0x002ce224)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce228));goto dispatch;
L_002ce228:
 STEP(UINT32_C(0x002ce228)); /* 24020003 addiu v0,zero,3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002ce22c));goto dispatch;
L_002ce22c:
 STEP(UINT32_C(0x002ce22c)); /* 10000003 beq zero,zero,002ce23c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce230));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ce23c):UINT32_C(0x002ce234));goto dispatch;}
L_002ce230:
 STEP(UINT32_C(0x002ce230)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ce234));goto dispatch;
L_002ce234:
 STEP(UINT32_C(0x002ce234)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce23c));STEP(UINT32_C(0x002ce238));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce238:
 STEP(UINT32_C(0x002ce238)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce23c));goto dispatch;
L_002ce23c:
 STEP(UINT32_C(0x002ce23c)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce240));goto dispatch;
L_002ce240:
 STEP(UINT32_C(0x002ce240)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce244));goto dispatch;
L_002ce244:
 STEP(UINT32_C(0x002ce244)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce248));goto dispatch;
L_002ce248:
 STEP(UINT32_C(0x002ce248)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce24c));goto dispatch;
L_002ce24c:
 STEP(UINT32_C(0x002ce24c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce250));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002ce250:
 STEP(UINT32_C(0x002ce250)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002ce254));goto dispatch;
L_002ce258:
 STEP(UINT32_C(0x002ce258)); /* 27bdffa0 addiu sp,sp,-96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffa0)));target=sx(UINT32_C(0x002ce25c));goto dispatch;
L_002ce25c:
 STEP(UINT32_C(0x002ce25c)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ce260));goto dispatch;
L_002ce260:
 STEP(UINT32_C(0x002ce260)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ce264));goto dispatch;
L_002ce264:
 STEP(UINT32_C(0x002ce264)); /* 3c130053 lui s3,zero,0x53 */
 set(m,19u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce268));goto dispatch;
L_002ce268:
 STEP(UINT32_C(0x002ce268)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ce26c));goto dispatch;
L_002ce26c:
 STEP(UINT32_C(0x002ce26c)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce270));goto dispatch;
L_002ce270:
 STEP(UINT32_C(0x002ce270)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce274));goto dispatch;
L_002ce274:
 STEP(UINT32_C(0x002ce274)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002ce278));goto dispatch;
L_002ce278:
 STEP(UINT32_C(0x002ce278)); /* 8e64bb24 lw a0,-0x44dc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce27c));goto dispatch;
L_002ce27c:
 STEP(UINT32_C(0x002ce27c)); /* ffbf0050 sd ra,0x50(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002ce280));goto dispatch;
L_002ce280:
 STEP(UINT32_C(0x002ce280)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002ce288));STEP(UINT32_C(0x002ce284));set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002ce284:
 STEP(UINT32_C(0x002ce284)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002ce288));goto dispatch;
L_002ce288:
 STEP(UINT32_C(0x002ce288)); /* 04410003 regimm1 v0,002ce298 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002ce28c));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce298):UINT32_C(0x002ce290));goto dispatch;}
L_002ce28c:
 STEP(UINT32_C(0x002ce28c)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce290));goto dispatch;
L_002ce290:
 STEP(UINT32_C(0x002ce290)); /* 1000001f beq zero,zero,002ce310 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce294));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ce310):UINT32_C(0x002ce298));goto dispatch;}
L_002ce294:
 STEP(UINT32_C(0x002ce294)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002ce298));goto dispatch;
L_002ce298:
 STEP(UINT32_C(0x002ce298)); /* 24449740 addiu a0,v0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce29c));goto dispatch;
L_002ce29c:
 STEP(UINT32_C(0x002ce29c)); /* 8c830024 lw v1,0x24(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce2a0));goto dispatch;
L_002ce2a0:
 STEP(UINT32_C(0x002ce2a0)); /* 14600005 bne v1,zero,002ce2b8 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002ce2a4));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce2b8):UINT32_C(0x002ce2a8));goto dispatch;}
L_002ce2a4:
 STEP(UINT32_C(0x002ce2a4)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce2a8));goto dispatch;
L_002ce2a8:
 STEP(UINT32_C(0x002ce2a8)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce2b0));STEP(UINT32_C(0x002ce2ac));READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce2ac:
 STEP(UINT32_C(0x002ce2ac)); /* 8e64bb24 lw a0,-0x44dc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce2b0));goto dispatch;
L_002ce2b0:
 STEP(UINT32_C(0x002ce2b0)); /* 10000017 beq zero,zero,002ce310 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce2b4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ce310):UINT32_C(0x002ce2b8));goto dispatch;}
L_002ce2b4:
 STEP(UINT32_C(0x002ce2b4)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002ce2b8));goto dispatch;
L_002ce2b8:
 STEP(UINT32_C(0x002ce2b8)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce2bc));goto dispatch;
L_002ce2bc:
 STEP(UINT32_C(0x002ce2bc)); /* 244797c0 addiu a3,v0,-26688 */
 set(m,7u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce2c0));goto dispatch;
L_002ce2c0:
 STEP(UINT32_C(0x002ce2c0)); /* ac5297c0 sw s2,-0x6840(v0) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffff97c0),&value32,4u);target=sx(UINT32_C(0x002ce2c4));goto dispatch;
L_002ce2c4:
 STEP(UINT32_C(0x002ce2c4)); /* acf00010 sw s0,0x10(a3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002ce2c8));goto dispatch;
L_002ce2c8:
 STEP(UINT32_C(0x002ce2c8)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ce2cc));goto dispatch;
L_002ce2cc:
 STEP(UINT32_C(0x002ce2cc)); /* acf10014 sw s1,0x14(a3) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002ce2d0));goto dispatch;
L_002ce2d0:
 STEP(UINT32_C(0x002ce2d0)); /* 24050004 addiu a1,zero,4 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce2d4));goto dispatch;
L_002ce2d4:
 STEP(UINT32_C(0x002ce2d4)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce2d8));goto dispatch;
L_002ce2d8:
 STEP(UINT32_C(0x002ce2d8)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce2dc));goto dispatch;
L_002ce2dc:
 STEP(UINT32_C(0x002ce2dc)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002ce2e0));goto dispatch;
L_002ce2e0:
 STEP(UINT32_C(0x002ce2e0)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce2e4));goto dispatch;
L_002ce2e4:
 STEP(UINT32_C(0x002ce2e4)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ce2ec));STEP(UINT32_C(0x002ce2e8));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ce2e8:
 STEP(UINT32_C(0x002ce2e8)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce2ec));goto dispatch;
L_002ce2ec:
 STEP(UINT32_C(0x002ce2ec)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce2f0));goto dispatch;
L_002ce2f0:
 STEP(UINT32_C(0x002ce2f0)); /* 16000004 bne s0,zero,002ce304 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002ce2f4));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002ce304):UINT32_C(0x002ce2f8));goto dispatch;}
L_002ce2f4:
 STEP(UINT32_C(0x002ce2f4)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce2f8));goto dispatch;
L_002ce2f8:
 STEP(UINT32_C(0x002ce2f8)); /* 24020004 addiu v0,zero,4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce2fc));goto dispatch;
L_002ce2fc:
 STEP(UINT32_C(0x002ce2fc)); /* 10000003 beq zero,zero,002ce30c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce300));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ce30c):UINT32_C(0x002ce304));goto dispatch;}
L_002ce300:
 STEP(UINT32_C(0x002ce300)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ce304));goto dispatch;
L_002ce304:
 STEP(UINT32_C(0x002ce304)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce30c));STEP(UINT32_C(0x002ce308));READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce308:
 STEP(UINT32_C(0x002ce308)); /* 8e64bb24 lw a0,-0x44dc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce30c));goto dispatch;
L_002ce30c:
 STEP(UINT32_C(0x002ce30c)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce310));goto dispatch;
L_002ce310:
 STEP(UINT32_C(0x002ce310)); /* dfbf0050 ld ra,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce314));goto dispatch;
L_002ce314:
 STEP(UINT32_C(0x002ce314)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002ce318));goto dispatch;
L_002ce318:
 STEP(UINT32_C(0x002ce318)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ce31c));goto dispatch;
L_002ce31c:
 STEP(UINT32_C(0x002ce31c)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce320));goto dispatch;
L_002ce320:
 STEP(UINT32_C(0x002ce320)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce324));goto dispatch;
L_002ce324:
 STEP(UINT32_C(0x002ce324)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce328));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));goto dispatch;
L_002ce328:
 STEP(UINT32_C(0x002ce328)); /* 27bd0060 addiu sp,sp,96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002ce32c));goto dispatch;
L_002ce330:
 STEP(UINT32_C(0x002ce330)); /* 3c022000 lui v0,zero,0x2000 */
 set(m,2u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002ce334));goto dispatch;
L_002ce334:
 STEP(UINT32_C(0x002ce334)); /* 00822025 or a0,a0,v0 */
 set(m,4u,lo(m,4u)|lo(m,2u));target=sx(UINT32_C(0x002ce338));goto dispatch;
L_002ce338:
 STEP(UINT32_C(0x002ce338)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce33c));goto dispatch;
L_002ce33c:
 STEP(UINT32_C(0x002ce33c)); /* 5040000f beql v0,zero,002ce37c */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002ce340));READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce37c));}else target=sx(UINT32_C(0x002ce344));goto dispatch;
L_002ce340:
 STEP(UINT32_C(0x002ce340)); /* 8c820004 lw v0,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce344));goto dispatch;
L_002ce344:
 STEP(UINT32_C(0x002ce344)); /* 8c860008 lw a2,0x8(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002ce348));goto dispatch;
L_002ce348:
 STEP(UINT32_C(0x002ce348)); /* 1840000b blez v0,zero,002ce378 */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x002ce34c));set(m,5u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002ce378):UINT32_C(0x002ce350));goto dispatch;}
L_002ce34c:
 STEP(UINT32_C(0x002ce34c)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce350));goto dispatch;
L_002ce350:
 STEP(UINT32_C(0x002ce350)); /* 24870010 addiu a3,a0,16 */
 set(m,7u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002ce354));goto dispatch;
L_002ce354:
 STEP(UINT32_C(0x002ce354)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce358));goto dispatch;
L_002ce358:
 STEP(UINT32_C(0x002ce358)); /* 00e51021 addu v0,a3,a1 */
 set(m,2u,sx((uint32_t)lo(m,7u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002ce35c));goto dispatch;
L_002ce35c:
 STEP(UINT32_C(0x002ce35c)); /* 90430000 lbu v1,0x0(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002ce360));goto dispatch;
L_002ce360:
 STEP(UINT32_C(0x002ce360)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce364));goto dispatch;
L_002ce364:
 STEP(UINT32_C(0x002ce364)); /* a0c30000 sb v1,0x0(a2) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002ce368));goto dispatch;
L_002ce368:
 STEP(UINT32_C(0x002ce368)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce36c));goto dispatch;
L_002ce36c:
 STEP(UINT32_C(0x002ce36c)); /* 00a2102a slt v0,a1,v0 */
 set(m,2u,((int64_t)lo(m,5u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x002ce370));goto dispatch;
L_002ce370:
 STEP(UINT32_C(0x002ce370)); /* 1440fff9 bne v0,zero,002ce358 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002ce374));set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002ce358):UINT32_C(0x002ce378));goto dispatch;}
L_002ce374:
 STEP(UINT32_C(0x002ce374)); /* 24c60001 addiu a2,a2,1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce378));goto dispatch;
L_002ce378:
 STEP(UINT32_C(0x002ce378)); /* 8c820004 lw v0,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce37c));goto dispatch;
L_002ce37c:
 STEP(UINT32_C(0x002ce37c)); /* 1040000e beq v0,zero,002ce3b8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002ce380));/* nop */target=sx(taken?UINT32_C(0x002ce3b8):UINT32_C(0x002ce384));goto dispatch;}
L_002ce380:
 STEP(UINT32_C(0x002ce380)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce384));goto dispatch;
L_002ce384:
 STEP(UINT32_C(0x002ce384)); /* 8c86000c lw a2,0xc(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x0000000c),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002ce388));goto dispatch;
L_002ce388:
 STEP(UINT32_C(0x002ce388)); /* 1840000b blez v0,zero,002ce3b8 */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x002ce38c));set(m,5u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002ce3b8):UINT32_C(0x002ce390));goto dispatch;}
L_002ce38c:
 STEP(UINT32_C(0x002ce38c)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce390));goto dispatch;
L_002ce390:
 STEP(UINT32_C(0x002ce390)); /* 24870050 addiu a3,a0,80 */
 set(m,7u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x002ce394));goto dispatch;
L_002ce394:
 STEP(UINT32_C(0x002ce394)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce398));goto dispatch;
L_002ce398:
 STEP(UINT32_C(0x002ce398)); /* 00e51021 addu v0,a3,a1 */
 set(m,2u,sx((uint32_t)lo(m,7u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002ce39c));goto dispatch;
L_002ce39c:
 STEP(UINT32_C(0x002ce39c)); /* 90430000 lbu v1,0x0(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002ce3a0));goto dispatch;
L_002ce3a0:
 STEP(UINT32_C(0x002ce3a0)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce3a4));goto dispatch;
L_002ce3a4:
 STEP(UINT32_C(0x002ce3a4)); /* a0c30000 sb v1,0x0(a2) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002ce3a8));goto dispatch;
L_002ce3a8:
 STEP(UINT32_C(0x002ce3a8)); /* 8c820004 lw v0,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce3ac));goto dispatch;
L_002ce3ac:
 STEP(UINT32_C(0x002ce3ac)); /* 00a2102a slt v0,a1,v0 */
 set(m,2u,((int64_t)lo(m,5u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x002ce3b0));goto dispatch;
L_002ce3b0:
 STEP(UINT32_C(0x002ce3b0)); /* 1440fff9 bne v0,zero,002ce398 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002ce3b4));set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002ce398):UINT32_C(0x002ce3b8));goto dispatch;}
L_002ce3b4:
 STEP(UINT32_C(0x002ce3b4)); /* 24c60001 addiu a2,a2,1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce3b8));goto dispatch;
L_002ce3b8:
 STEP(UINT32_C(0x002ce3b8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce3bc));/* nop */goto dispatch;
L_002ce3bc:
 STEP(UINT32_C(0x002ce3bc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce3c0));goto dispatch;
L_002ce3c0:
 STEP(UINT32_C(0x002ce3c0)); /* 27bdff70 addiu sp,sp,-144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff70)));target=sx(UINT32_C(0x002ce3c4));goto dispatch;
L_002ce3c4:
 STEP(UINT32_C(0x002ce3c4)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002ce3c8));goto dispatch;
L_002ce3c8:
 STEP(UINT32_C(0x002ce3c8)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002ce3cc));goto dispatch;
L_002ce3cc:
 STEP(UINT32_C(0x002ce3cc)); /* 3c150053 lui s5,zero,0x53 */
 set(m,21u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce3d0));goto dispatch;
L_002ce3d0:
 STEP(UINT32_C(0x002ce3d0)); /* 0080a02d daddu s4,a0,zero */
 set(m,20u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ce3d4));goto dispatch;
L_002ce3d4:
 STEP(UINT32_C(0x002ce3d4)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ce3d8));goto dispatch;
L_002ce3d8:
 STEP(UINT32_C(0x002ce3d8)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ce3dc));goto dispatch;
L_002ce3dc:
 STEP(UINT32_C(0x002ce3dc)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002ce3e0));goto dispatch;
L_002ce3e0:
 STEP(UINT32_C(0x002ce3e0)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce3e4));goto dispatch;
L_002ce3e4:
 STEP(UINT32_C(0x002ce3e4)); /* 00a0902d daddu s2,a1,zero */
 set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002ce3e8));goto dispatch;
L_002ce3e8:
 STEP(UINT32_C(0x002ce3e8)); /* ffbf0080 sd ra,0x80(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002ce3ec));goto dispatch;
L_002ce3ec:
 STEP(UINT32_C(0x002ce3ec)); /* ffb60070 sd s6,0x70(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002ce3f0));goto dispatch;
L_002ce3f0:
 STEP(UINT32_C(0x002ce3f0)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce3f4));goto dispatch;
L_002ce3f4:
 STEP(UINT32_C(0x002ce3f4)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002ce3fc));STEP(UINT32_C(0x002ce3f8));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002ce3f8:
 STEP(UINT32_C(0x002ce3f8)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce3fc));goto dispatch;
L_002ce3fc:
 STEP(UINT32_C(0x002ce3fc)); /* 04410003 regimm1 v0,002ce40c */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002ce400));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce40c):UINT32_C(0x002ce404));goto dispatch;}
L_002ce400:
 STEP(UINT32_C(0x002ce400)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce404));goto dispatch;
L_002ce404:
 STEP(UINT32_C(0x002ce404)); /* 1000002b beq zero,zero,002ce4b4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce408));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ce4b4):UINT32_C(0x002ce40c));goto dispatch;}
L_002ce408:
 STEP(UINT32_C(0x002ce408)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002ce40c));goto dispatch;
L_002ce40c:
 STEP(UINT32_C(0x002ce40c)); /* 24569740 addiu s6,v0,-26816 */
 set(m,22u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce410));goto dispatch;
L_002ce410:
 STEP(UINT32_C(0x002ce410)); /* 8ec30024 lw v1,0x24(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce414));goto dispatch;
L_002ce414:
 STEP(UINT32_C(0x002ce414)); /* 14600005 bne v1,zero,002ce42c */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002ce418));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce42c):UINT32_C(0x002ce41c));goto dispatch;}
L_002ce418:
 STEP(UINT32_C(0x002ce418)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce41c));goto dispatch;
L_002ce41c:
 STEP(UINT32_C(0x002ce41c)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce424));STEP(UINT32_C(0x002ce420));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce420:
 STEP(UINT32_C(0x002ce420)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce424));goto dispatch;
L_002ce424:
 STEP(UINT32_C(0x002ce424)); /* 10000023 beq zero,zero,002ce4b4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce428));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ce4b4):UINT32_C(0x002ce42c));goto dispatch;}
L_002ce428:
 STEP(UINT32_C(0x002ce428)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002ce42c));goto dispatch;
L_002ce42c:
 STEP(UINT32_C(0x002ce42c)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce430));goto dispatch;
L_002ce430:
 STEP(UINT32_C(0x002ce430)); /* 26109c40 addiu s0,s0,-25536 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffff9c40)));target=sx(UINT32_C(0x002ce434));goto dispatch;
L_002ce434:
 STEP(UINT32_C(0x002ce434)); /* 245197c0 addiu s1,v0,-26688 */
 set(m,17u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce438));goto dispatch;
L_002ce438:
 STEP(UINT32_C(0x002ce438)); /* ac5497c0 sw s4,-0x6840(v0) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffff97c0),&value32,4u);target=sx(UINT32_C(0x002ce43c));goto dispatch;
L_002ce43c:
 STEP(UINT32_C(0x002ce43c)); /* 0240202d daddu a0,s2,zero */
 set(m,4u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002ce440));goto dispatch;
L_002ce440:
 STEP(UINT32_C(0x002ce440)); /* ae30001c sw s0,0x1c(s1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002ce444));goto dispatch;
L_002ce444:
 STEP(UINT32_C(0x002ce444)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002ce448));goto dispatch;
L_002ce448:
 STEP(UINT32_C(0x002ce448)); /* ae320018 sw s2,0x18(s1) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002ce44c));goto dispatch;
L_002ce44c:
 STEP(UINT32_C(0x002ce44c)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002ce454));STEP(UINT32_C(0x002ce450));value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002de458));goto dispatch;
L_002ce450:
 STEP(UINT32_C(0x002ce450)); /* ae33000c sw s3,0xc(s1) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002ce454));goto dispatch;
L_002ce454:
 STEP(UINT32_C(0x002ce454)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce458));goto dispatch;
L_002ce458:
 STEP(UINT32_C(0x002ce458)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002ce460));STEP(UINT32_C(0x002ce45c));set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000c0)));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002ce45c:
 STEP(UINT32_C(0x002ce45c)); /* 240500c0 addiu a1,zero,192 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000c0)));target=sx(UINT32_C(0x002ce460));goto dispatch;
L_002ce460:
 STEP(UINT32_C(0x002ce460)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce464));goto dispatch;
L_002ce464:
 STEP(UINT32_C(0x002ce464)); /* 3c0b002d lui t3,zero,0x2d */
 set(m,11u,sx(UINT32_C(0x002d0000)));target=sx(UINT32_C(0x002ce468));goto dispatch;
L_002ce468:
 STEP(UINT32_C(0x002ce468)); /* afb00000 sw s0,0x0(sp) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce46c));goto dispatch;
L_002ce46c:
 STEP(UINT32_C(0x002ce46c)); /* 02c0202d daddu a0,s6,zero */
 set(m,4u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002ce470));goto dispatch;
L_002ce470:
 STEP(UINT32_C(0x002ce470)); /* 0220382d daddu a3,s1,zero */
 set(m,7u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002ce474));goto dispatch;
L_002ce474:
 STEP(UINT32_C(0x002ce474)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ce478));goto dispatch;
L_002ce478:
 STEP(UINT32_C(0x002ce478)); /* 256be330 addiu t3,t3,-7376 */
 set(m,11u,sx((uint32_t)lo(m,11u)+UINT32_C(0xffffe330)));target=sx(UINT32_C(0x002ce47c));goto dispatch;
L_002ce47c:
 STEP(UINT32_C(0x002ce47c)); /* 24050005 addiu a1,zero,5 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000005)));target=sx(UINT32_C(0x002ce480));goto dispatch;
L_002ce480:
 STEP(UINT32_C(0x002ce480)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce484));goto dispatch;
L_002ce484:
 STEP(UINT32_C(0x002ce484)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002ce488));goto dispatch;
L_002ce488:
 STEP(UINT32_C(0x002ce488)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ce490));STEP(UINT32_C(0x002ce48c));set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ce48c:
 STEP(UINT32_C(0x002ce48c)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce490));goto dispatch;
L_002ce490:
 STEP(UINT32_C(0x002ce490)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce494));goto dispatch;
L_002ce494:
 STEP(UINT32_C(0x002ce494)); /* 16000004 bne s0,zero,002ce4a8 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002ce498));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002ce4a8):UINT32_C(0x002ce49c));goto dispatch;}
L_002ce498:
 STEP(UINT32_C(0x002ce498)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce49c));goto dispatch;
L_002ce49c:
 STEP(UINT32_C(0x002ce49c)); /* 24020005 addiu v0,zero,5 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000005)));target=sx(UINT32_C(0x002ce4a0));goto dispatch;
L_002ce4a0:
 STEP(UINT32_C(0x002ce4a0)); /* 10000003 beq zero,zero,002ce4b0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce4a4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ce4b0):UINT32_C(0x002ce4a8));goto dispatch;}
L_002ce4a4:
 STEP(UINT32_C(0x002ce4a4)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ce4a8));goto dispatch;
L_002ce4a8:
 STEP(UINT32_C(0x002ce4a8)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce4b0));STEP(UINT32_C(0x002ce4ac));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce4ac:
 STEP(UINT32_C(0x002ce4ac)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce4b0));goto dispatch;
L_002ce4b0:
 STEP(UINT32_C(0x002ce4b0)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce4b4));goto dispatch;
L_002ce4b4:
 STEP(UINT32_C(0x002ce4b4)); /* dfbf0080 ld ra,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce4b8));goto dispatch;
L_002ce4b8:
 STEP(UINT32_C(0x002ce4b8)); /* dfb60070 ld s6,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002ce4bc));goto dispatch;
L_002ce4bc:
 STEP(UINT32_C(0x002ce4bc)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002ce4c0));goto dispatch;
L_002ce4c0:
 STEP(UINT32_C(0x002ce4c0)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002ce4c4));goto dispatch;
L_002ce4c4:
 STEP(UINT32_C(0x002ce4c4)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002ce4c8));goto dispatch;
L_002ce4c8:
 STEP(UINT32_C(0x002ce4c8)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ce4cc));goto dispatch;
L_002ce4cc:
 STEP(UINT32_C(0x002ce4cc)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce4d0));goto dispatch;
L_002ce4d0:
 STEP(UINT32_C(0x002ce4d0)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce4d4));goto dispatch;
L_002ce4d4:
 STEP(UINT32_C(0x002ce4d4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce4d8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));goto dispatch;
L_002ce4d8:
 STEP(UINT32_C(0x002ce4d8)); /* 27bd0090 addiu sp,sp,144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));target=sx(UINT32_C(0x002ce4dc));goto dispatch;
L_002ce4e0:
 STEP(UINT32_C(0x002ce4e0)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x002ce4e4));goto dispatch;
L_002ce4e4:
 STEP(UINT32_C(0x002ce4e4)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002ce4e8));goto dispatch;
L_002ce4e8:
 STEP(UINT32_C(0x002ce4e8)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ce4ec));goto dispatch;
L_002ce4ec:
 STEP(UINT32_C(0x002ce4ec)); /* 3c140053 lui s4,zero,0x53 */
 set(m,20u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce4f0));goto dispatch;
L_002ce4f0:
 STEP(UINT32_C(0x002ce4f0)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ce4f4));goto dispatch;
L_002ce4f4:
 STEP(UINT32_C(0x002ce4f4)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce4f8));goto dispatch;
L_002ce4f8:
 STEP(UINT32_C(0x002ce4f8)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce4fc));goto dispatch;
L_002ce4fc:
 STEP(UINT32_C(0x002ce4fc)); /* 00a0882d daddu s1,a1,zero */
 set(m,17u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002ce500));goto dispatch;
L_002ce500:
 STEP(UINT32_C(0x002ce500)); /* 8e84bb24 lw a0,-0x44dc(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce504));goto dispatch;
L_002ce504:
 STEP(UINT32_C(0x002ce504)); /* 00c0802d daddu s0,a2,zero */
 set(m,16u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002ce508));goto dispatch;
L_002ce508:
 STEP(UINT32_C(0x002ce508)); /* ffbf0070 sd ra,0x70(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002ce50c));goto dispatch;
L_002ce50c:
 STEP(UINT32_C(0x002ce50c)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002ce510));goto dispatch;
L_002ce510:
 STEP(UINT32_C(0x002ce510)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002ce518));STEP(UINT32_C(0x002ce514));value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002ce514:
 STEP(UINT32_C(0x002ce514)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ce518));goto dispatch;
L_002ce518:
 STEP(UINT32_C(0x002ce518)); /* 04410003 regimm1 v0,002ce528 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002ce51c));set(m,21u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce528):UINT32_C(0x002ce520));goto dispatch;}
L_002ce51c:
 STEP(UINT32_C(0x002ce51c)); /* 3c15005a lui s5,zero,0x5a */
 set(m,21u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce520));goto dispatch;
L_002ce520:
 STEP(UINT32_C(0x002ce520)); /* 10000045 beq zero,zero,002ce638 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce524));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ce638):UINT32_C(0x002ce528));goto dispatch;}
L_002ce524:
 STEP(UINT32_C(0x002ce524)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002ce528));goto dispatch;
L_002ce528:
 STEP(UINT32_C(0x002ce528)); /* 26a29740 addiu v0,s5,-26816 */
 set(m,2u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce52c));goto dispatch;
L_002ce52c:
 STEP(UINT32_C(0x002ce52c)); /* 8c430024 lw v1,0x24(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce530));goto dispatch;
L_002ce530:
 STEP(UINT32_C(0x002ce530)); /* 14600005 bne v1,zero,002ce548 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002ce534));set(m,18u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce548):UINT32_C(0x002ce538));goto dispatch;}
L_002ce534:
 STEP(UINT32_C(0x002ce534)); /* 3c12005a lui s2,zero,0x5a */
 set(m,18u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce538));goto dispatch;
L_002ce538:
 STEP(UINT32_C(0x002ce538)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce540));STEP(UINT32_C(0x002ce53c));READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce53c:
 STEP(UINT32_C(0x002ce53c)); /* 8e84bb24 lw a0,-0x44dc(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce540));goto dispatch;
L_002ce540:
 STEP(UINT32_C(0x002ce540)); /* 1000003d beq zero,zero,002ce638 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce544));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ce638):UINT32_C(0x002ce548));goto dispatch;}
L_002ce544:
 STEP(UINT32_C(0x002ce544)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002ce548));goto dispatch;
L_002ce548:
 STEP(UINT32_C(0x002ce548)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x002ce54c));goto dispatch;
L_002ce54c:
 STEP(UINT32_C(0x002ce54c)); /* 264697c0 addiu a2,s2,-26688 */
 set(m,6u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce550));goto dispatch;
L_002ce550:
 STEP(UINT32_C(0x002ce550)); /* 10400005 beq v0,zero,002ce568 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002ce554));value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0xffff97c0),&value32,4u);target=sx(taken?UINT32_C(0x002ce568):UINT32_C(0x002ce558));goto dispatch;}
L_002ce554:
 STEP(UINT32_C(0x002ce554)); /* ae5397c0 sw s3,-0x6840(s2) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,18u)+UINT32_C(0xffff97c0),&value32,4u);target=sx(UINT32_C(0x002ce558));goto dispatch;
L_002ce558:
 STEP(UINT32_C(0x002ce558)); /* acd00014 sw s0,0x14(a2) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002ce55c));goto dispatch;
L_002ce55c:
 STEP(UINT32_C(0x002ce55c)); /* acc00018 sw zero,0x18(a2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002ce560));goto dispatch;
L_002ce560:
 STEP(UINT32_C(0x002ce560)); /* 1000000c beq zero,zero,002ce594 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce564));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);target=sx(taken?UINT32_C(0x002ce594):UINT32_C(0x002ce568));goto dispatch;}
L_002ce564:
 STEP(UINT32_C(0x002ce564)); /* acc0000c sw zero,0xc(a2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002ce568));goto dispatch;
L_002ce568:
 STEP(UINT32_C(0x002ce568)); /* 3c03ffff lui v1,zero,0xffff */
 set(m,3u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002ce56c));goto dispatch;
L_002ce56c:
 STEP(UINT32_C(0x002ce56c)); /* 2622ffff addiu v0,s1,-1 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002ce570));goto dispatch;
L_002ce570:
 STEP(UINT32_C(0x002ce570)); /* 3463fff0 ori v1,v1,0xfff0 */
 set(m,3u,lo(m,3u) | UINT64_C(0xfff0));target=sx(UINT32_C(0x002ce574));goto dispatch;
L_002ce574:
 STEP(UINT32_C(0x002ce574)); /* 2624fff0 addiu a0,s1,-16 */
 set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002ce578));goto dispatch;
L_002ce578:
 STEP(UINT32_C(0x002ce578)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002ce57c));goto dispatch;
L_002ce57c:
 STEP(UINT32_C(0x002ce57c)); /* 00441023 subu v0,v0,a0 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x002ce580));goto dispatch;
L_002ce580:
 STEP(UINT32_C(0x002ce580)); /* 02022823 subu a1,s0,v0 */
 set(m,5u,sx((uint32_t)lo(m,16u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002ce584));goto dispatch;
L_002ce584:
 STEP(UINT32_C(0x002ce584)); /* 02221821 addu v1,s1,v0 */
 set(m,3u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002ce588));goto dispatch;
L_002ce588:
 STEP(UINT32_C(0x002ce588)); /* acc30018 sw v1,0x18(a2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002ce58c));goto dispatch;
L_002ce58c:
 STEP(UINT32_C(0x002ce58c)); /* acc5000c sw a1,0xc(a2) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002ce590));goto dispatch;
L_002ce590:
 STEP(UINT32_C(0x002ce590)); /* acc20014 sw v0,0x14(a2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002ce594));goto dispatch;
L_002ce594:
 STEP(UINT32_C(0x002ce594)); /* 264297c0 addiu v0,s2,-26688 */
 set(m,2u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce598));goto dispatch;
L_002ce598:
 STEP(UINT32_C(0x002ce598)); /* 0240382d daddu a3,s2,zero */
 set(m,7u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002ce59c));goto dispatch;
L_002ce59c:
 STEP(UINT32_C(0x002ce59c)); /* 8c430014 lw v1,0x14(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce5a0));goto dispatch;
L_002ce5a0:
 STEP(UINT32_C(0x002ce5a0)); /* 1060000f beq v1,zero,002ce5e0 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002ce5a4));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002ce5e0):UINT32_C(0x002ce5a8));goto dispatch;}
L_002ce5a4:
 STEP(UINT32_C(0x002ce5a4)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce5a8));goto dispatch;
L_002ce5a8:
 STEP(UINT32_C(0x002ce5a8)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce5ac));goto dispatch;
L_002ce5ac:
 STEP(UINT32_C(0x002ce5ac)); /* 02261021 addu v0,s1,a2 */
 set(m,2u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002ce5b0));goto dispatch;
L_002ce5b0:
 STEP(UINT32_C(0x002ce5b0)); /* 24e497c0 addiu a0,a3,-26688 */
 set(m,4u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce5b4));goto dispatch;
L_002ce5b4:
 STEP(UINT32_C(0x002ce5b4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce5b8));goto dispatch;
L_002ce5b8:
 STEP(UINT32_C(0x002ce5b8)); /* 90450000 lbu a1,0x0(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&byte,1u);set(m,5u,byte);}target=sx(UINT32_C(0x002ce5bc));goto dispatch;
L_002ce5bc:
 STEP(UINT32_C(0x002ce5bc)); /* 00861821 addu v1,a0,a2 */
 set(m,3u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002ce5c0));goto dispatch;
L_002ce5c0:
 STEP(UINT32_C(0x002ce5c0)); /* 24c60001 addiu a2,a2,1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce5c4));goto dispatch;
L_002ce5c4:
 STEP(UINT32_C(0x002ce5c4)); /* a0650020 sb a1,0x20(v1) */
 {uint8_t byte=(uint8_t)lo(m,5u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000020),&byte,1u);}target=sx(UINT32_C(0x002ce5c8));goto dispatch;
L_002ce5c8:
 STEP(UINT32_C(0x002ce5c8)); /* 8c820014 lw v0,0x14(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce5cc));goto dispatch;
L_002ce5cc:
 STEP(UINT32_C(0x002ce5cc)); /* 00c2102b sltu v0,a2,v0 */
 set(m,2u,lo(m,6u)<lo(m,2u));target=sx(UINT32_C(0x002ce5d0));goto dispatch;
L_002ce5d0:
 STEP(UINT32_C(0x002ce5d0)); /* 1440fff9 bne v0,zero,002ce5b8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002ce5d4));set(m,2u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,6u)));target=sx(taken?UINT32_C(0x002ce5b8):UINT32_C(0x002ce5d8));goto dispatch;}
L_002ce5d4:
 STEP(UINT32_C(0x002ce5d4)); /* 02261021 addu v0,s1,a2 */
 set(m,2u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,6u)));target=sx(UINT32_C(0x002ce5d8));goto dispatch;
L_002ce5d8:
 STEP(UINT32_C(0x002ce5d8)); /* 10000002 beq zero,zero,002ce5e4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce5dc));/* nop */target=sx(taken?UINT32_C(0x002ce5e4):UINT32_C(0x002ce5e0));goto dispatch;}
L_002ce5dc:
 STEP(UINT32_C(0x002ce5dc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce5e0));goto dispatch;
L_002ce5e0:
 STEP(UINT32_C(0x002ce5e0)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce5e4));goto dispatch;
L_002ce5e4:
 STEP(UINT32_C(0x002ce5e4)); /* 0c0b7048 jal 002dc120 */
 set(m,31u,UINT64_C(0x002ce5ec));STEP(UINT32_C(0x002ce5e8));set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dc120));goto dispatch;
L_002ce5e8:
 STEP(UINT32_C(0x002ce5e8)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce5ec));goto dispatch;
L_002ce5ec:
 STEP(UINT32_C(0x002ce5ec)); /* 2609ad00 addiu t1,s0,-21248 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ce5f0));goto dispatch;
L_002ce5f0:
 STEP(UINT32_C(0x002ce5f0)); /* 26a49740 addiu a0,s5,-26816 */
 set(m,4u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce5f4));goto dispatch;
L_002ce5f4:
 STEP(UINT32_C(0x002ce5f4)); /* 264797c0 addiu a3,s2,-26688 */
 set(m,7u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce5f8));goto dispatch;
L_002ce5f8:
 STEP(UINT32_C(0x002ce5f8)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce5fc));goto dispatch;
L_002ce5fc:
 STEP(UINT32_C(0x002ce5fc)); /* 24050006 addiu a1,zero,6 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000006)));target=sx(UINT32_C(0x002ce600));goto dispatch;
L_002ce600:
 STEP(UINT32_C(0x002ce600)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce604));goto dispatch;
L_002ce604:
 STEP(UINT32_C(0x002ce604)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002ce608));goto dispatch;
L_002ce608:
 STEP(UINT32_C(0x002ce608)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce60c));goto dispatch;
L_002ce60c:
 STEP(UINT32_C(0x002ce60c)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ce614));STEP(UINT32_C(0x002ce610));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ce610:
 STEP(UINT32_C(0x002ce610)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce614));goto dispatch;
L_002ce614:
 STEP(UINT32_C(0x002ce614)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce618));goto dispatch;
L_002ce618:
 STEP(UINT32_C(0x002ce618)); /* 16000004 bne s0,zero,002ce62c */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002ce61c));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002ce62c):UINT32_C(0x002ce620));goto dispatch;}
L_002ce61c:
 STEP(UINT32_C(0x002ce61c)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce620));goto dispatch;
L_002ce620:
 STEP(UINT32_C(0x002ce620)); /* 24020006 addiu v0,zero,6 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000006)));target=sx(UINT32_C(0x002ce624));goto dispatch;
L_002ce624:
 STEP(UINT32_C(0x002ce624)); /* 10000003 beq zero,zero,002ce634 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce628));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ce634):UINT32_C(0x002ce62c));goto dispatch;}
L_002ce628:
 STEP(UINT32_C(0x002ce628)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ce62c));goto dispatch;
L_002ce62c:
 STEP(UINT32_C(0x002ce62c)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce634));STEP(UINT32_C(0x002ce630));READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce630:
 STEP(UINT32_C(0x002ce630)); /* 8e84bb24 lw a0,-0x44dc(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce634));goto dispatch;
L_002ce634:
 STEP(UINT32_C(0x002ce634)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce638));goto dispatch;
L_002ce638:
 STEP(UINT32_C(0x002ce638)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce63c));goto dispatch;
L_002ce63c:
 STEP(UINT32_C(0x002ce63c)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002ce640));goto dispatch;
L_002ce640:
 STEP(UINT32_C(0x002ce640)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002ce644));goto dispatch;
L_002ce644:
 STEP(UINT32_C(0x002ce644)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002ce648));goto dispatch;
L_002ce648:
 STEP(UINT32_C(0x002ce648)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ce64c));goto dispatch;
L_002ce64c:
 STEP(UINT32_C(0x002ce64c)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce650));goto dispatch;
L_002ce650:
 STEP(UINT32_C(0x002ce650)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce654));goto dispatch;
L_002ce654:
 STEP(UINT32_C(0x002ce654)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce658));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_002ce658:
 STEP(UINT32_C(0x002ce658)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x002ce65c));goto dispatch;
L_002ce660:
 STEP(UINT32_C(0x002ce660)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002ce664));goto dispatch;
L_002ce664:
 STEP(UINT32_C(0x002ce664)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002ce668));goto dispatch;
L_002ce668:
 STEP(UINT32_C(0x002ce668)); /* 0c0b7354 jal 002dcd50 */
 set(m,31u,UINT64_C(0x002ce670));STEP(UINT32_C(0x002ce66c));set(m,4u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002dcd50));goto dispatch;
L_002ce66c:
 STEP(UINT32_C(0x002ce66c)); /* 00c0202d daddu a0,a2,zero */
 set(m,4u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002ce670));goto dispatch;
L_002ce670:
 STEP(UINT32_C(0x002ce670)); /* 0000000f sync 0 */
 ++m->sync_p; /* Native SYNC0 count; no cache/device completion. */target=sx(UINT32_C(0x002ce674));goto dispatch;
L_002ce674:
 STEP(UINT32_C(0x002ce674)); /* 42000038 cop0 rs16 rtzero rd0 fn56 */
 if((m->status&0x20006u)!=0u||(m->status&0x18u)==0u)m->status|=0x10000u;target=sx(UINT32_C(0x002ce678));goto dispatch;
L_002ce678:
 STEP(UINT32_C(0x002ce678)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce67c));goto dispatch;
L_002ce67c:
 STEP(UINT32_C(0x002ce67c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce680));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002ce680:
 STEP(UINT32_C(0x002ce680)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002ce684));goto dispatch;
L_002ce688:
 STEP(UINT32_C(0x002ce688)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002ce68c));goto dispatch;
L_002ce68c:
 STEP(UINT32_C(0x002ce68c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002ce690));goto dispatch;
L_002ce690:
 STEP(UINT32_C(0x002ce690)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce694));goto dispatch;
L_002ce694:
 STEP(UINT32_C(0x002ce694)); /* 3c10002d lui s0,zero,0x2d */
 set(m,16u,sx(UINT32_C(0x002d0000)));target=sx(UINT32_C(0x002ce698));goto dispatch;
L_002ce698:
 STEP(UINT32_C(0x002ce698)); /* 3091ffff andi s1,a0,0xffff */
 set(m,17u,lo(m,4u) & UINT64_C(0xffff));target=sx(UINT32_C(0x002ce69c));goto dispatch;
L_002ce69c:
 STEP(UINT32_C(0x002ce69c)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce6a0));goto dispatch;
L_002ce6a0:
 STEP(UINT32_C(0x002ce6a0)); /* 0c0b6f64 jal 002dbd90 */
 set(m,31u,UINT64_C(0x002ce6a8));STEP(UINT32_C(0x002ce6a4));set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe660)));target=sx(UINT32_C(0x002dbd90));goto dispatch;
L_002ce6a4:
 STEP(UINT32_C(0x002ce6a4)); /* 2610e660 addiu s0,s0,-6560 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffe660)));target=sx(UINT32_C(0x002ce6a8));goto dispatch;
L_002ce6a8:
 STEP(UINT32_C(0x002ce6a8)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002ce6ac));goto dispatch;
L_002ce6ac:
 STEP(UINT32_C(0x002ce6ac)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce6b0));goto dispatch;
L_002ce6b0:
 STEP(UINT32_C(0x002ce6b0)); /* 0c0b6f08 jal 002dbc20 */
 set(m,31u,UINT64_C(0x002ce6b8));STEP(UINT32_C(0x002ce6b4));set(m,6u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002dbc20));goto dispatch;
L_002ce6b4:
 STEP(UINT32_C(0x002ce6b4)); /* 0040302d daddu a2,v0,zero */
 set(m,6u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce6b8));goto dispatch;
L_002ce6b8:
 STEP(UINT32_C(0x002ce6b8)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce6bc));goto dispatch;
L_002ce6bc:
 STEP(UINT32_C(0x002ce6bc)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce6c0));goto dispatch;
L_002ce6c0:
 STEP(UINT32_C(0x002ce6c0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce6c4));goto dispatch;
L_002ce6c4:
 STEP(UINT32_C(0x002ce6c4)); /* 080b6f70 j 002dbdc0 */
 STEP(UINT32_C(0x002ce6c8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002dbdc0));goto dispatch;
L_002ce6c8:
 STEP(UINT32_C(0x002ce6c8)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002ce6cc));goto dispatch;
L_002ce6d0:
 STEP(UINT32_C(0x002ce6d0)); /* 27bdff90 addiu sp,sp,-112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff90)));target=sx(UINT32_C(0x002ce6d4));goto dispatch;
L_002ce6d4:
 STEP(UINT32_C(0x002ce6d4)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ce6d8));goto dispatch;
L_002ce6d8:
 STEP(UINT32_C(0x002ce6d8)); /* 3c130053 lui s3,zero,0x53 */
 set(m,19u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce6dc));goto dispatch;
L_002ce6dc:
 STEP(UINT32_C(0x002ce6dc)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002ce6e0));goto dispatch;
L_002ce6e0:
 STEP(UINT32_C(0x002ce6e0)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ce6e4));goto dispatch;
L_002ce6e4:
 STEP(UINT32_C(0x002ce6e4)); /* 00c0a82d daddu s5,a2,zero */
 set(m,21u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002ce6e8));goto dispatch;
L_002ce6e8:
 STEP(UINT32_C(0x002ce6e8)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce6ec));goto dispatch;
L_002ce6ec:
 STEP(UINT32_C(0x002ce6ec)); /* 00a0a02d daddu s4,a1,zero */
 set(m,20u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002ce6f0));goto dispatch;
L_002ce6f0:
 STEP(UINT32_C(0x002ce6f0)); /* 8e62bb20 lw v0,-0x44e0(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb20),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce6f4));goto dispatch;
L_002ce6f4:
 STEP(UINT32_C(0x002ce6f4)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ce6f8));goto dispatch;
L_002ce6f8:
 STEP(UINT32_C(0x002ce6f8)); /* ffbf0060 sd ra,0x60(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002ce6fc));goto dispatch;
L_002ce6fc:
 STEP(UINT32_C(0x002ce6fc)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce700));goto dispatch;
L_002ce700:
 STEP(UINT32_C(0x002ce700)); /* 14400003 bne v0,zero,002ce710 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002ce704));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x002ce710):UINT32_C(0x002ce708));goto dispatch;}
L_002ce704:
 STEP(UINT32_C(0x002ce704)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002ce708));goto dispatch;
L_002ce708:
 STEP(UINT32_C(0x002ce708)); /* 10000020 beq zero,zero,002ce78c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce70c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002ce78c):UINT32_C(0x002ce710));goto dispatch;}
L_002ce70c:
 STEP(UINT32_C(0x002ce70c)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002ce710));goto dispatch;
L_002ce710:
 STEP(UINT32_C(0x002ce710)); /* 3c11005a lui s1,zero,0x5a */
 set(m,17u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce714));goto dispatch;
L_002ce714:
 STEP(UINT32_C(0x002ce714)); /* 0c0b7bce jal 002def38 */
 set(m,31u,UINT64_C(0x002ce71c));STEP(UINT32_C(0x002ce718));set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002def38));goto dispatch;
L_002ce718:
 STEP(UINT32_C(0x002ce718)); /* 26249740 addiu a0,s1,-26816 */
 set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce71c));goto dispatch;
L_002ce71c:
 STEP(UINT32_C(0x002ce71c)); /* 1640000c bne s2,zero,002ce750 */
 {int taken=(lo(m,18u)!=lo(m,0u));STEP(UINT32_C(0x002ce720));set(m,16u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x002ce750):UINT32_C(0x002ce724));goto dispatch;}
L_002ce720:
 STEP(UINT32_C(0x002ce720)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce724));goto dispatch;
L_002ce724:
 STEP(UINT32_C(0x002ce724)); /* 1200000a beq s0,zero,002ce750 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002ce728));/* nop */target=sx(taken?UINT32_C(0x002ce750):UINT32_C(0x002ce72c));goto dispatch;}
L_002ce728:
 STEP(UINT32_C(0x002ce728)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce72c));goto dispatch;
L_002ce72c:
 STEP(UINT32_C(0x002ce72c)); /* 10000004 beq zero,zero,002ce740 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce730));/* nop */target=sx(taken?UINT32_C(0x002ce740):UINT32_C(0x002ce734));goto dispatch;}
L_002ce730:
 STEP(UINT32_C(0x002ce730)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce734));goto dispatch;
L_002ce734:
 STEP(UINT32_C(0x002ce734)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce738));goto dispatch;
L_002ce738:
 STEP(UINT32_C(0x002ce738)); /* 0c0b39a2 jal 002ce688 */
 set(m,31u,UINT64_C(0x002ce740));STEP(UINT32_C(0x002ce73c));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000003c)));target=sx(UINT32_C(0x002ce688));goto dispatch;
L_002ce73c:
 STEP(UINT32_C(0x002ce73c)); /* 2404003c addiu a0,zero,60 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000003c)));target=sx(UINT32_C(0x002ce740));goto dispatch;
L_002ce740:
 STEP(UINT32_C(0x002ce740)); /* 0c0b7bce jal 002def38 */
 set(m,31u,UINT64_C(0x002ce748));STEP(UINT32_C(0x002ce744));set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002def38));goto dispatch;
L_002ce744:
 STEP(UINT32_C(0x002ce744)); /* 26249740 addiu a0,s1,-26816 */
 set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce748));goto dispatch;
L_002ce748:
 STEP(UINT32_C(0x002ce748)); /* 1440fffb bne v0,zero,002ce738 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002ce74c));set(m,16u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002ce738):UINT32_C(0x002ce750));goto dispatch;}
L_002ce74c:
 STEP(UINT32_C(0x002ce74c)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce750));goto dispatch;
L_002ce750:
 STEP(UINT32_C(0x002ce750)); /* 12800003 beq s4,zero,002ce760 */
 {int taken=(lo(m,20u)==lo(m,0u));STEP(UINT32_C(0x002ce754));set(m,16u,(lo(m,16u)<UINT64_C(0x1)));target=sx(taken?UINT32_C(0x002ce760):UINT32_C(0x002ce758));goto dispatch;}
L_002ce754:
 STEP(UINT32_C(0x002ce754)); /* 2e100001 sltiu s0,s0,1 */
 set(m,16u,(lo(m,16u)<UINT64_C(0x1)));target=sx(UINT32_C(0x002ce758));goto dispatch;
L_002ce758:
 STEP(UINT32_C(0x002ce758)); /* 8e62bb20 lw v0,-0x44e0(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb20),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce75c));goto dispatch;
L_002ce75c:
 STEP(UINT32_C(0x002ce75c)); /* ae820000 sw v0,0x0(s4) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce760));goto dispatch;
L_002ce760:
 STEP(UINT32_C(0x002ce760)); /* 1200000a beq s0,zero,002ce78c */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002ce764));set(m,2u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002ce78c):UINT32_C(0x002ce768));goto dispatch;}
L_002ce764:
 STEP(UINT32_C(0x002ce764)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce768));goto dispatch;
L_002ce768:
 STEP(UINT32_C(0x002ce768)); /* 12a00004 beq s5,zero,002ce77c */
 {int taken=(lo(m,21u)==lo(m,0u));STEP(UINT32_C(0x002ce76c));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ce77c):UINT32_C(0x002ce770));goto dispatch;}
L_002ce76c:
 STEP(UINT32_C(0x002ce76c)); /* ae60bb20 sw zero,-0x44e0(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ce770));goto dispatch;
L_002ce770:
 STEP(UINT32_C(0x002ce770)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce774));goto dispatch;
L_002ce774:
 STEP(UINT32_C(0x002ce774)); /* 8c43ad00 lw v1,-0x5300(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffad00),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce778));goto dispatch;
L_002ce778:
 STEP(UINT32_C(0x002ce778)); /* aea30000 sw v1,0x0(s5) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce77c));goto dispatch;
L_002ce77c:
 STEP(UINT32_C(0x002ce77c)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce780));goto dispatch;
L_002ce780:
 STEP(UINT32_C(0x002ce780)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce788));STEP(UINT32_C(0x002ce784));READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce784:
 STEP(UINT32_C(0x002ce784)); /* 8c44bb24 lw a0,-0x44dc(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce788));goto dispatch;
L_002ce788:
 STEP(UINT32_C(0x002ce788)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce78c));goto dispatch;
L_002ce78c:
 STEP(UINT32_C(0x002ce78c)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce790));goto dispatch;
L_002ce790:
 STEP(UINT32_C(0x002ce790)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002ce794));goto dispatch;
L_002ce794:
 STEP(UINT32_C(0x002ce794)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002ce798));goto dispatch;
L_002ce798:
 STEP(UINT32_C(0x002ce798)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002ce79c));goto dispatch;
L_002ce79c:
 STEP(UINT32_C(0x002ce79c)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ce7a0));goto dispatch;
L_002ce7a0:
 STEP(UINT32_C(0x002ce7a0)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce7a4));goto dispatch;
L_002ce7a4:
 STEP(UINT32_C(0x002ce7a4)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce7a8));goto dispatch;
L_002ce7a8:
 STEP(UINT32_C(0x002ce7a8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce7ac));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));goto dispatch;
L_002ce7ac:
 STEP(UINT32_C(0x002ce7ac)); /* 27bd0070 addiu sp,sp,112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x002ce7b0));goto dispatch;
L_002ce7b0:
 STEP(UINT32_C(0x002ce7b0)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce7b4));goto dispatch;
L_002ce7b4:
 STEP(UINT32_C(0x002ce7b4)); /* 3c032000 lui v1,zero,0x2000 */
 set(m,3u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002ce7b8));goto dispatch;
L_002ce7b8:
 STEP(UINT32_C(0x002ce7b8)); /* 8c459768 lw a1,-0x6898(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffff9768),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002ce7bc));goto dispatch;
L_002ce7bc:
 STEP(UINT32_C(0x002ce7bc)); /* 10a00003 beq a1,zero,002ce7cc */
 {int taken=(lo(m,5u)==lo(m,0u));STEP(UINT32_C(0x002ce7c0));set(m,4u,lo(m,4u)|lo(m,3u));target=sx(taken?UINT32_C(0x002ce7cc):UINT32_C(0x002ce7c4));goto dispatch;}
L_002ce7c0:
 STEP(UINT32_C(0x002ce7c0)); /* 00832025 or a0,a0,v1 */
 set(m,4u,lo(m,4u)|lo(m,3u));target=sx(UINT32_C(0x002ce7c4));goto dispatch;
L_002ce7c4:
 STEP(UINT32_C(0x002ce7c4)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce7c8));goto dispatch;
L_002ce7c8:
 STEP(UINT32_C(0x002ce7c8)); /* aca20000 sw v0,0x0(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce7cc));goto dispatch;
L_002ce7cc:
 STEP(UINT32_C(0x002ce7cc)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce7d0));goto dispatch;
L_002ce7d0:
 STEP(UINT32_C(0x002ce7d0)); /* 8c43976c lw v1,-0x6894(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffff976c),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce7d4));goto dispatch;
L_002ce7d4:
 STEP(UINT32_C(0x002ce7d4)); /* 10600004 beq v1,zero,002ce7e8 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002ce7d8));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce7e8):UINT32_C(0x002ce7dc));goto dispatch;}
L_002ce7d8:
 STEP(UINT32_C(0x002ce7d8)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce7dc));goto dispatch;
L_002ce7dc:
 STEP(UINT32_C(0x002ce7dc)); /* 8c820004 lw v0,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce7e0));goto dispatch;
L_002ce7e0:
 STEP(UINT32_C(0x002ce7e0)); /* ac620000 sw v0,0x0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce7e4));goto dispatch;
L_002ce7e4:
 STEP(UINT32_C(0x002ce7e4)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce7e8));goto dispatch;
L_002ce7e8:
 STEP(UINT32_C(0x002ce7e8)); /* 8c439770 lw v1,-0x6890(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffff9770),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce7ec));goto dispatch;
L_002ce7ec:
 STEP(UINT32_C(0x002ce7ec)); /* 10600003 beq v1,zero,002ce7fc */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x002ce7f0));/* nop */target=sx(taken?UINT32_C(0x002ce7fc):UINT32_C(0x002ce7f4));goto dispatch;}
L_002ce7f0:
 STEP(UINT32_C(0x002ce7f0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce7f4));goto dispatch;
L_002ce7f4:
 STEP(UINT32_C(0x002ce7f4)); /* 8c820090 lw v0,0x90(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000090),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce7f8));goto dispatch;
L_002ce7f8:
 STEP(UINT32_C(0x002ce7f8)); /* ac620000 sw v0,0x0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce7fc));goto dispatch;
L_002ce7fc:
 STEP(UINT32_C(0x002ce7fc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce800));/* nop */goto dispatch;
L_002ce800:
 STEP(UINT32_C(0x002ce800)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002ce804));goto dispatch;
L_002ce808:
 STEP(UINT32_C(0x002ce808)); /* 27bdff60 addiu sp,sp,-160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff60)));target=sx(UINT32_C(0x002ce80c));goto dispatch;
L_002ce80c:
 STEP(UINT32_C(0x002ce80c)); /* ffb60070 sd s6,0x70(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002ce810));goto dispatch;
L_002ce810:
 STEP(UINT32_C(0x002ce810)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ce814));goto dispatch;
L_002ce814:
 STEP(UINT32_C(0x002ce814)); /* 3c160053 lui s6,zero,0x53 */
 set(m,22u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce818));goto dispatch;
L_002ce818:
 STEP(UINT32_C(0x002ce818)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ce81c));goto dispatch;
L_002ce81c:
 STEP(UINT32_C(0x002ce81c)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002ce820));goto dispatch;
L_002ce820:
 STEP(UINT32_C(0x002ce820)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002ce824));goto dispatch;
L_002ce824:
 STEP(UINT32_C(0x002ce824)); /* 0100a82d daddu s5,t0,zero */
 set(m,21u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002ce828));goto dispatch;
L_002ce828:
 STEP(UINT32_C(0x002ce828)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ce82c));goto dispatch;
L_002ce82c:
 STEP(UINT32_C(0x002ce82c)); /* 00e0a02d daddu s4,a3,zero */
 set(m,20u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002ce830));goto dispatch;
L_002ce830:
 STEP(UINT32_C(0x002ce830)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce834));goto dispatch;
L_002ce834:
 STEP(UINT32_C(0x002ce834)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002ce838));goto dispatch;
L_002ce838:
 STEP(UINT32_C(0x002ce838)); /* 8ec4bb24 lw a0,-0x44dc(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce83c));goto dispatch;
L_002ce83c:
 STEP(UINT32_C(0x002ce83c)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002ce840));goto dispatch;
L_002ce840:
 STEP(UINT32_C(0x002ce840)); /* ffbf0090 sd ra,0x90(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x002ce844));goto dispatch;
L_002ce844:
 STEP(UINT32_C(0x002ce844)); /* ffb70080 sd s7,0x80(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002ce848));goto dispatch;
L_002ce848:
 STEP(UINT32_C(0x002ce848)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002ce850));STEP(UINT32_C(0x002ce84c));value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002ce84c:
 STEP(UINT32_C(0x002ce84c)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce850));goto dispatch;
L_002ce850:
 STEP(UINT32_C(0x002ce850)); /* 04410003 regimm1 v0,002ce860 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002ce854));set(m,23u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce860):UINT32_C(0x002ce858));goto dispatch;}
L_002ce854:
 STEP(UINT32_C(0x002ce854)); /* 3c17005a lui s7,zero,0x5a */
 set(m,23u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce858));goto dispatch;
L_002ce858:
 STEP(UINT32_C(0x002ce858)); /* 10000041 beq zero,zero,002ce960 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce85c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ce960):UINT32_C(0x002ce860));goto dispatch;}
L_002ce85c:
 STEP(UINT32_C(0x002ce85c)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002ce860));goto dispatch;
L_002ce860:
 STEP(UINT32_C(0x002ce860)); /* 26e29740 addiu v0,s7,-26816 */
 set(m,2u,sx((uint32_t)lo(m,23u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce864));goto dispatch;
L_002ce864:
 STEP(UINT32_C(0x002ce864)); /* 8c430024 lw v1,0x24(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ce868));goto dispatch;
L_002ce868:
 STEP(UINT32_C(0x002ce868)); /* 14600005 bne v1,zero,002ce880 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002ce86c));set(m,17u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ce880):UINT32_C(0x002ce870));goto dispatch;}
L_002ce86c:
 STEP(UINT32_C(0x002ce86c)); /* 3c11005a lui s1,zero,0x5a */
 set(m,17u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce870));goto dispatch;
L_002ce870:
 STEP(UINT32_C(0x002ce870)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce878));STEP(UINT32_C(0x002ce874));READ((uint32_t)lo(m,22u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce874:
 STEP(UINT32_C(0x002ce874)); /* 8ec4bb24 lw a0,-0x44dc(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce878));goto dispatch;
L_002ce878:
 STEP(UINT32_C(0x002ce878)); /* 10000039 beq zero,zero,002ce960 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce87c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ce960):UINT32_C(0x002ce880));goto dispatch;}
L_002ce87c:
 STEP(UINT32_C(0x002ce87c)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002ce880));goto dispatch;
L_002ce880:
 STEP(UINT32_C(0x002ce880)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce884));goto dispatch;
L_002ce884:
 STEP(UINT32_C(0x002ce884)); /* 262397c0 addiu v1,s1,-26688 */
 set(m,3u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce888));goto dispatch;
L_002ce888:
 STEP(UINT32_C(0x002ce888)); /* 24829c40 addiu v0,a0,-25536 */
 set(m,2u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9c40)));target=sx(UINT32_C(0x002ce88c));goto dispatch;
L_002ce88c:
 STEP(UINT32_C(0x002ce88c)); /* ac720004 sw s2,0x4(v1) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002ce890));goto dispatch;
L_002ce890:
 STEP(UINT32_C(0x002ce890)); /* ac700008 sw s0,0x8(v1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002ce894));goto dispatch;
L_002ce894:
 STEP(UINT32_C(0x002ce894)); /* 12600004 beq s3,zero,002ce8a8 */
 {int taken=(lo(m,19u)==lo(m,0u));STEP(UINT32_C(0x002ce898));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000001c),&value32,4u);target=sx(taken?UINT32_C(0x002ce8a8):UINT32_C(0x002ce89c));goto dispatch;}
L_002ce898:
 STEP(UINT32_C(0x002ce898)); /* ac62001c sw v0,0x1c(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002ce89c));goto dispatch;
L_002ce89c:
 STEP(UINT32_C(0x002ce89c)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce8a0));goto dispatch;
L_002ce8a0:
 STEP(UINT32_C(0x002ce8a0)); /* 10000002 beq zero,zero,002ce8ac */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce8a4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000014),&value32,4u);target=sx(taken?UINT32_C(0x002ce8ac):UINT32_C(0x002ce8a8));goto dispatch;}
L_002ce8a4:
 STEP(UINT32_C(0x002ce8a4)); /* ac620014 sw v0,0x14(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002ce8a8));goto dispatch;
L_002ce8a8:
 STEP(UINT32_C(0x002ce8a8)); /* ac600014 sw zero,0x14(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002ce8ac));goto dispatch;
L_002ce8ac:
 STEP(UINT32_C(0x002ce8ac)); /* 12800004 beq s4,zero,002ce8c0 */
 {int taken=(lo(m,20u)==lo(m,0u));STEP(UINT32_C(0x002ce8b0));set(m,3u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff97c0)));target=sx(taken?UINT32_C(0x002ce8c0):UINT32_C(0x002ce8b4));goto dispatch;}
L_002ce8b0:
 STEP(UINT32_C(0x002ce8b0)); /* 262397c0 addiu v1,s1,-26688 */
 set(m,3u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce8b4));goto dispatch;
L_002ce8b4:
 STEP(UINT32_C(0x002ce8b4)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce8b8));goto dispatch;
L_002ce8b8:
 STEP(UINT32_C(0x002ce8b8)); /* 10000003 beq zero,zero,002ce8c8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce8bc));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000010),&value32,4u);target=sx(taken?UINT32_C(0x002ce8c8):UINT32_C(0x002ce8c0));goto dispatch;}
L_002ce8bc:
 STEP(UINT32_C(0x002ce8bc)); /* ac620010 sw v0,0x10(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002ce8c0));goto dispatch;
L_002ce8c0:
 STEP(UINT32_C(0x002ce8c0)); /* 262297c0 addiu v0,s1,-26688 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce8c4));goto dispatch;
L_002ce8c4:
 STEP(UINT32_C(0x002ce8c4)); /* ac400010 sw zero,0x10(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002ce8c8));goto dispatch;
L_002ce8c8:
 STEP(UINT32_C(0x002ce8c8)); /* 12a00004 beq s5,zero,002ce8dc */
 {int taken=(lo(m,21u)==lo(m,0u));STEP(UINT32_C(0x002ce8cc));set(m,3u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff97c0)));target=sx(taken?UINT32_C(0x002ce8dc):UINT32_C(0x002ce8d0));goto dispatch;}
L_002ce8cc:
 STEP(UINT32_C(0x002ce8cc)); /* 262397c0 addiu v1,s1,-26688 */
 set(m,3u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce8d0));goto dispatch;
L_002ce8d0:
 STEP(UINT32_C(0x002ce8d0)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce8d4));goto dispatch;
L_002ce8d4:
 STEP(UINT32_C(0x002ce8d4)); /* 10000003 beq zero,zero,002ce8e4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce8d8));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),&value32,4u);target=sx(taken?UINT32_C(0x002ce8e4):UINT32_C(0x002ce8dc));goto dispatch;}
L_002ce8d8:
 STEP(UINT32_C(0x002ce8d8)); /* ac62000c sw v0,0xc(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002ce8dc));goto dispatch;
L_002ce8dc:
 STEP(UINT32_C(0x002ce8dc)); /* 262297c0 addiu v0,s1,-26688 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce8e0));goto dispatch;
L_002ce8e0:
 STEP(UINT32_C(0x002ce8e0)); /* ac40000c sw zero,0xc(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002ce8e4));goto dispatch;
L_002ce8e4:
 STEP(UINT32_C(0x002ce8e4)); /* 24909c40 addiu s0,a0,-25536 */
 set(m,16u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9c40)));target=sx(UINT32_C(0x002ce8e8));goto dispatch;
L_002ce8e8:
 STEP(UINT32_C(0x002ce8e8)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce8ec));goto dispatch;
L_002ce8ec:
 STEP(UINT32_C(0x002ce8ec)); /* 3c03005a lui v1,zero,0x5a */
 set(m,3u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce8f0));goto dispatch;
L_002ce8f0:
 STEP(UINT32_C(0x002ce8f0)); /* 3c06005a lui a2,zero,0x5a */
 set(m,6u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce8f4));goto dispatch;
L_002ce8f4:
 STEP(UINT32_C(0x002ce8f4)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce8f8));goto dispatch;
L_002ce8f8:
 STEP(UINT32_C(0x002ce8f8)); /* ac539768 sw s3,-0x6898(v0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffff9768),&value32,4u);target=sx(UINT32_C(0x002ce8fc));goto dispatch;
L_002ce8fc:
 STEP(UINT32_C(0x002ce8fc)); /* ac74976c sw s4,-0x6894(v1) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffff976c),&value32,4u);target=sx(UINT32_C(0x002ce900));goto dispatch;
L_002ce900:
 STEP(UINT32_C(0x002ce900)); /* 240500c0 addiu a1,zero,192 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000c0)));target=sx(UINT32_C(0x002ce904));goto dispatch;
L_002ce904:
 STEP(UINT32_C(0x002ce904)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002ce90c));STEP(UINT32_C(0x002ce908));value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0xffff9770),&value32,4u);target=sx(UINT32_C(0x002de458));goto dispatch;
L_002ce908:
 STEP(UINT32_C(0x002ce908)); /* acd59770 sw s5,-0x6890(a2) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0xffff9770),&value32,4u);target=sx(UINT32_C(0x002ce90c));goto dispatch;
L_002ce90c:
 STEP(UINT32_C(0x002ce90c)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce910));goto dispatch;
L_002ce910:
 STEP(UINT32_C(0x002ce910)); /* 3c0b002d lui t3,zero,0x2d */
 set(m,11u,sx(UINT32_C(0x002d0000)));target=sx(UINT32_C(0x002ce914));goto dispatch;
L_002ce914:
 STEP(UINT32_C(0x002ce914)); /* afb00000 sw s0,0x0(sp) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce918));goto dispatch;
L_002ce918:
 STEP(UINT32_C(0x002ce918)); /* 26e49740 addiu a0,s7,-26816 */
 set(m,4u,sx((uint32_t)lo(m,23u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce91c));goto dispatch;
L_002ce91c:
 STEP(UINT32_C(0x002ce91c)); /* 262797c0 addiu a3,s1,-26688 */
 set(m,7u,sx((uint32_t)lo(m,17u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce920));goto dispatch;
L_002ce920:
 STEP(UINT32_C(0x002ce920)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ce924));goto dispatch;
L_002ce924:
 STEP(UINT32_C(0x002ce924)); /* 256be7b0 addiu t3,t3,-6224 */
 set(m,11u,sx((uint32_t)lo(m,11u)+UINT32_C(0xffffe7b0)));target=sx(UINT32_C(0x002ce928));goto dispatch;
L_002ce928:
 STEP(UINT32_C(0x002ce928)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce92c));goto dispatch;
L_002ce92c:
 STEP(UINT32_C(0x002ce92c)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce930));goto dispatch;
L_002ce930:
 STEP(UINT32_C(0x002ce930)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002ce934));goto dispatch;
L_002ce934:
 STEP(UINT32_C(0x002ce934)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ce93c));STEP(UINT32_C(0x002ce938));set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ce938:
 STEP(UINT32_C(0x002ce938)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce93c));goto dispatch;
L_002ce93c:
 STEP(UINT32_C(0x002ce93c)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ce940));goto dispatch;
L_002ce940:
 STEP(UINT32_C(0x002ce940)); /* 16000004 bne s0,zero,002ce954 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002ce944));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002ce954):UINT32_C(0x002ce948));goto dispatch;}
L_002ce944:
 STEP(UINT32_C(0x002ce944)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ce948));goto dispatch;
L_002ce948:
 STEP(UINT32_C(0x002ce948)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ce94c));goto dispatch;
L_002ce94c:
 STEP(UINT32_C(0x002ce94c)); /* 10000003 beq zero,zero,002ce95c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce950));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ce95c):UINT32_C(0x002ce954));goto dispatch;}
L_002ce950:
 STEP(UINT32_C(0x002ce950)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ce954));goto dispatch;
L_002ce954:
 STEP(UINT32_C(0x002ce954)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ce95c));STEP(UINT32_C(0x002ce958));READ((uint32_t)lo(m,22u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ce958:
 STEP(UINT32_C(0x002ce958)); /* 8ec4bb24 lw a0,-0x44dc(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ce95c));goto dispatch;
L_002ce95c:
 STEP(UINT32_C(0x002ce95c)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ce960));goto dispatch;
L_002ce960:
 STEP(UINT32_C(0x002ce960)); /* dfbf0090 ld ra,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce964));goto dispatch;
L_002ce964:
 STEP(UINT32_C(0x002ce964)); /* dfb70080 ld s7,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002ce968));goto dispatch;
L_002ce968:
 STEP(UINT32_C(0x002ce968)); /* dfb60070 ld s6,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002ce96c));goto dispatch;
L_002ce96c:
 STEP(UINT32_C(0x002ce96c)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002ce970));goto dispatch;
L_002ce970:
 STEP(UINT32_C(0x002ce970)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002ce974));goto dispatch;
L_002ce974:
 STEP(UINT32_C(0x002ce974)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002ce978));goto dispatch;
L_002ce978:
 STEP(UINT32_C(0x002ce978)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ce97c));goto dispatch;
L_002ce97c:
 STEP(UINT32_C(0x002ce97c)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ce980));goto dispatch;
L_002ce980:
 STEP(UINT32_C(0x002ce980)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce984));goto dispatch;
L_002ce984:
 STEP(UINT32_C(0x002ce984)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce988));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));goto dispatch;
L_002ce988:
 STEP(UINT32_C(0x002ce988)); /* 27bd00a0 addiu sp,sp,160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));target=sx(UINT32_C(0x002ce98c));goto dispatch;
L_002ce990:
 STEP(UINT32_C(0x002ce990)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002ce994));goto dispatch;
L_002ce994:
 STEP(UINT32_C(0x002ce994)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce998));goto dispatch;
L_002ce998:
 STEP(UINT32_C(0x002ce998)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ce99c));goto dispatch;
L_002ce99c:
 STEP(UINT32_C(0x002ce99c)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce9a0));goto dispatch;
L_002ce9a0:
 STEP(UINT32_C(0x002ce9a0)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ce9a4));goto dispatch;
L_002ce9a4:
 STEP(UINT32_C(0x002ce9a4)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ce9a8));goto dispatch;
L_002ce9a8:
 STEP(UINT32_C(0x002ce9a8)); /* 24849740 addiu a0,a0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ce9ac));goto dispatch;
L_002ce9ac:
 STEP(UINT32_C(0x002ce9ac)); /* 24e797c0 addiu a3,a3,-26688 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ce9b0));goto dispatch;
L_002ce9b0:
 STEP(UINT32_C(0x002ce9b0)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ce9b4));goto dispatch;
L_002ce9b4:
 STEP(UINT32_C(0x002ce9b4)); /* 24050035 addiu a1,zero,53 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000035)));target=sx(UINT32_C(0x002ce9b8));goto dispatch;
L_002ce9b8:
 STEP(UINT32_C(0x002ce9b8)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce9bc));goto dispatch;
L_002ce9bc:
 STEP(UINT32_C(0x002ce9bc)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002ce9c0));goto dispatch;
L_002ce9c0:
 STEP(UINT32_C(0x002ce9c0)); /* 2609ad00 addiu t1,s0,-21248 */
 set(m,9u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ce9c4));goto dispatch;
L_002ce9c4:
 STEP(UINT32_C(0x002ce9c4)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ce9c8));goto dispatch;
L_002ce9c8:
 STEP(UINT32_C(0x002ce9c8)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ce9d0));STEP(UINT32_C(0x002ce9cc));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ce9cc:
 STEP(UINT32_C(0x002ce9cc)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ce9d0));goto dispatch;
L_002ce9d0:
 STEP(UINT32_C(0x002ce9d0)); /* 10400005 beq v0,zero,002ce9e8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002ce9d4));set(m,4u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002ce9e8):UINT32_C(0x002ce9d8));goto dispatch;}
L_002ce9d4:
 STEP(UINT32_C(0x002ce9d4)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002ce9d8));goto dispatch;
L_002ce9d8:
 STEP(UINT32_C(0x002ce9d8)); /* 0c0b7758 jal 002ddd60 */
 set(m,31u,UINT64_C(0x002ce9e0));STEP(UINT32_C(0x002ce9dc));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffaee8)));target=sx(UINT32_C(0x002ddd60));goto dispatch;
L_002ce9dc:
 STEP(UINT32_C(0x002ce9dc)); /* 2484aee8 addiu a0,a0,-20760 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffaee8)));target=sx(UINT32_C(0x002ce9e0));goto dispatch;
L_002ce9e0:
 STEP(UINT32_C(0x002ce9e0)); /* 10000002 beq zero,zero,002ce9ec */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ce9e4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002ce9ec):UINT32_C(0x002ce9e8));goto dispatch;}
L_002ce9e4:
 STEP(UINT32_C(0x002ce9e4)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002ce9e8));goto dispatch;
L_002ce9e8:
 STEP(UINT32_C(0x002ce9e8)); /* 8e02ad00 lw v0,-0x5300(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffad00),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002ce9ec));goto dispatch;
L_002ce9ec:
 STEP(UINT32_C(0x002ce9ec)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ce9f0));goto dispatch;
L_002ce9f0:
 STEP(UINT32_C(0x002ce9f0)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ce9f4));goto dispatch;
L_002ce9f4:
 STEP(UINT32_C(0x002ce9f4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ce9f8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002ce9f8:
 STEP(UINT32_C(0x002ce9f8)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002ce9fc));goto dispatch;
L_002cea00:
 STEP(UINT32_C(0x002cea00)); /* 27bdff60 addiu sp,sp,-160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff60)));target=sx(UINT32_C(0x002cea04));goto dispatch;
L_002cea04:
 STEP(UINT32_C(0x002cea04)); /* ffb60070 sd s6,0x70(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002cea08));goto dispatch;
L_002cea08:
 STEP(UINT32_C(0x002cea08)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002cea0c));goto dispatch;
L_002cea0c:
 STEP(UINT32_C(0x002cea0c)); /* 0080b02d daddu s6,a0,zero */
 set(m,22u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cea10));goto dispatch;
L_002cea10:
 STEP(UINT32_C(0x002cea10)); /* 3c150053 lui s5,zero,0x53 */
 set(m,21u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cea14));goto dispatch;
L_002cea14:
 STEP(UINT32_C(0x002cea14)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002cea18));goto dispatch;
L_002cea18:
 STEP(UINT32_C(0x002cea18)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cea1c));goto dispatch;
L_002cea1c:
 STEP(UINT32_C(0x002cea1c)); /* 00e0a02d daddu s4,a3,zero */
 set(m,20u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002cea20));goto dispatch;
L_002cea20:
 STEP(UINT32_C(0x002cea20)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cea24));goto dispatch;
L_002cea24:
 STEP(UINT32_C(0x002cea24)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002cea28));goto dispatch;
L_002cea28:
 STEP(UINT32_C(0x002cea28)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cea2c));goto dispatch;
L_002cea2c:
 STEP(UINT32_C(0x002cea2c)); /* 0120902d daddu s2,t1,zero */
 set(m,18u,lo(m,9u)+lo(m,0u));target=sx(UINT32_C(0x002cea30));goto dispatch;
L_002cea30:
 STEP(UINT32_C(0x002cea30)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cea34));goto dispatch;
L_002cea34:
 STEP(UINT32_C(0x002cea34)); /* 0100882d daddu s1,t0,zero */
 set(m,17u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002cea38));goto dispatch;
L_002cea38:
 STEP(UINT32_C(0x002cea38)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cea3c));goto dispatch;
L_002cea3c:
 STEP(UINT32_C(0x002cea3c)); /* 00c0802d daddu s0,a2,zero */
 set(m,16u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002cea40));goto dispatch;
L_002cea40:
 STEP(UINT32_C(0x002cea40)); /* ffbf0090 sd ra,0x90(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x002cea44));goto dispatch;
L_002cea44:
 STEP(UINT32_C(0x002cea44)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cea4c));STEP(UINT32_C(0x002cea48));value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cea48:
 STEP(UINT32_C(0x002cea48)); /* ffb70080 sd s7,0x80(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002cea4c));goto dispatch;
L_002cea4c:
 STEP(UINT32_C(0x002cea4c)); /* 04410003 regimm1 v0,002cea5c */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cea50));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cea5c):UINT32_C(0x002cea54));goto dispatch;}
L_002cea50:
 STEP(UINT32_C(0x002cea50)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cea54));goto dispatch;
L_002cea54:
 STEP(UINT32_C(0x002cea54)); /* 10000035 beq zero,zero,002ceb2c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cea58));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ceb2c):UINT32_C(0x002cea5c));goto dispatch;}
L_002cea58:
 STEP(UINT32_C(0x002cea58)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cea5c));goto dispatch;
L_002cea5c:
 STEP(UINT32_C(0x002cea5c)); /* 24579740 addiu s7,v0,-26816 */
 set(m,23u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cea60));goto dispatch;
L_002cea60:
 STEP(UINT32_C(0x002cea60)); /* 8ee30024 lw v1,0x24(s7) */
 READ((uint32_t)lo(m,23u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cea64));goto dispatch;
L_002cea64:
 STEP(UINT32_C(0x002cea64)); /* 14600005 bne v1,zero,002cea7c */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cea68));/* nop */target=sx(taken?UINT32_C(0x002cea7c):UINT32_C(0x002cea6c));goto dispatch;}
L_002cea68:
 STEP(UINT32_C(0x002cea68)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cea6c));goto dispatch;
L_002cea6c:
 STEP(UINT32_C(0x002cea6c)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cea74));STEP(UINT32_C(0x002cea70));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cea70:
 STEP(UINT32_C(0x002cea70)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cea74));goto dispatch;
L_002cea74:
 STEP(UINT32_C(0x002cea74)); /* 1000002d beq zero,zero,002ceb2c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cea78));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ceb2c):UINT32_C(0x002cea7c));goto dispatch;}
L_002cea78:
 STEP(UINT32_C(0x002cea78)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cea7c));goto dispatch;
L_002cea7c:
 STEP(UINT32_C(0x002cea7c)); /* 12000004 beq s0,zero,002cea90 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002cea80));/* nop */target=sx(taken?UINT32_C(0x002cea90):UINT32_C(0x002cea84));goto dispatch;}
L_002cea80:
 STEP(UINT32_C(0x002cea80)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cea84));goto dispatch;
L_002cea84:
 STEP(UINT32_C(0x002cea84)); /* 82020000 lb v0,0x0(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002cea88));goto dispatch;
L_002cea88:
 STEP(UINT32_C(0x002cea88)); /* 14400005 bne v0,zero,002ceaa0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cea8c));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ceaa0):UINT32_C(0x002cea90));goto dispatch;}
L_002cea8c:
 STEP(UINT32_C(0x002cea8c)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cea90));goto dispatch;
L_002cea90:
 STEP(UINT32_C(0x002cea90)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cea98));STEP(UINT32_C(0x002cea94));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cea94:
 STEP(UINT32_C(0x002cea94)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cea98));goto dispatch;
L_002cea98:
 STEP(UINT32_C(0x002cea98)); /* 10000024 beq zero,zero,002ceb2c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cea9c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(taken?UINT32_C(0x002ceb2c):UINT32_C(0x002ceaa0));goto dispatch;}
L_002cea9c:
 STEP(UINT32_C(0x002cea9c)); /* 2402ff2e addiu v0,zero,-210 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(UINT32_C(0x002ceaa0));goto dispatch;
L_002ceaa0:
 STEP(UINT32_C(0x002ceaa0)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ceaa4));goto dispatch;
L_002ceaa4:
 STEP(UINT32_C(0x002ceaa4)); /* 245097f0 addiu s0,v0,-26640 */
 set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0)));target=sx(UINT32_C(0x002ceaa8));goto dispatch;
L_002ceaa8:
 STEP(UINT32_C(0x002ceaa8)); /* ac5697f0 sw s6,-0x6810(v0) */
 value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0),&value32,4u);target=sx(UINT32_C(0x002ceaac));goto dispatch;
L_002ceaac:
 STEP(UINT32_C(0x002ceaac)); /* ae130004 sw s3,0x4(s0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002ceab0));goto dispatch;
L_002ceab0:
 STEP(UINT32_C(0x002ceab0)); /* 26040014 addiu a0,s0,20 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002ceab4));goto dispatch;
L_002ceab4:
 STEP(UINT32_C(0x002ceab4)); /* ae140008 sw s4,0x8(s0) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002ceab8));goto dispatch;
L_002ceab8:
 STEP(UINT32_C(0x002ceab8)); /* 240603ff addiu a2,zero,1023 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002ceabc));goto dispatch;
L_002ceabc:
 STEP(UINT32_C(0x002ceabc)); /* ae11000c sw s1,0xc(s0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002ceac0));goto dispatch;
L_002ceac0:
 STEP(UINT32_C(0x002ceac0)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002ceac8));STEP(UINT32_C(0x002ceac4));value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002ceac4:
 STEP(UINT32_C(0x002ceac4)); /* ae120010 sw s2,0x10(s0) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002ceac8));goto dispatch;
L_002ceac8:
 STEP(UINT32_C(0x002ceac8)); /* 06200004 regimm0 s1,002ceadc */
 {int taken=((int64_t)lo(m,17u)<0);STEP(UINT32_C(0x002ceacc));{uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000413),&byte,1u);}target=sx(taken?UINT32_C(0x002ceadc):UINT32_C(0x002cead0));goto dispatch;}
L_002ceacc:
 STEP(UINT32_C(0x002ceacc)); /* a2000413 sb zero,0x413(s0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000413),&byte,1u);}target=sx(UINT32_C(0x002cead0));goto dispatch;
L_002cead0:
 STEP(UINT32_C(0x002cead0)); /* 0240202d daddu a0,s2,zero */
 set(m,4u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002cead4));goto dispatch;
L_002cead4:
 STEP(UINT32_C(0x002cead4)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002ceadc));STEP(UINT32_C(0x002cead8));set(m,5u,sx((uint32_t)lo(m,17u)<<6u));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002cead8:
 STEP(UINT32_C(0x002cead8)); /* 00112980 sll a1,s1,6 */
 set(m,5u,sx((uint32_t)lo(m,17u)<<6u));target=sx(UINT32_C(0x002ceadc));goto dispatch;
L_002ceadc:
 STEP(UINT32_C(0x002ceadc)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ceae0));goto dispatch;
L_002ceae0:
 STEP(UINT32_C(0x002ceae0)); /* 0200382d daddu a3,s0,zero */
 set(m,7u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ceae4));goto dispatch;
L_002ceae4:
 STEP(UINT32_C(0x002ceae4)); /* 02e0202d daddu a0,s7,zero */
 set(m,4u,lo(m,23u)+lo(m,0u));target=sx(UINT32_C(0x002ceae8));goto dispatch;
L_002ceae8:
 STEP(UINT32_C(0x002ceae8)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ceaec));goto dispatch;
L_002ceaec:
 STEP(UINT32_C(0x002ceaec)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ceaf0));goto dispatch;
L_002ceaf0:
 STEP(UINT32_C(0x002ceaf0)); /* 2405000d addiu a1,zero,13 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000d)));target=sx(UINT32_C(0x002ceaf4));goto dispatch;
L_002ceaf4:
 STEP(UINT32_C(0x002ceaf4)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ceaf8));goto dispatch;
L_002ceaf8:
 STEP(UINT32_C(0x002ceaf8)); /* 24080414 addiu t0,zero,1044 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000414)));target=sx(UINT32_C(0x002ceafc));goto dispatch;
L_002ceafc:
 STEP(UINT32_C(0x002ceafc)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ceb00));goto dispatch;
L_002ceb00:
 STEP(UINT32_C(0x002ceb00)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ceb08));STEP(UINT32_C(0x002ceb04));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ceb04:
 STEP(UINT32_C(0x002ceb04)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ceb08));goto dispatch;
L_002ceb08:
 STEP(UINT32_C(0x002ceb08)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ceb0c));goto dispatch;
L_002ceb0c:
 STEP(UINT32_C(0x002ceb0c)); /* 16000004 bne s0,zero,002ceb20 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002ceb10));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002ceb20):UINT32_C(0x002ceb14));goto dispatch;}
L_002ceb10:
 STEP(UINT32_C(0x002ceb10)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ceb14));goto dispatch;
L_002ceb14:
 STEP(UINT32_C(0x002ceb14)); /* 2402000d addiu v0,zero,13 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000d)));target=sx(UINT32_C(0x002ceb18));goto dispatch;
L_002ceb18:
 STEP(UINT32_C(0x002ceb18)); /* 10000003 beq zero,zero,002ceb28 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ceb1c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ceb28):UINT32_C(0x002ceb20));goto dispatch;}
L_002ceb1c:
 STEP(UINT32_C(0x002ceb1c)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ceb20));goto dispatch;
L_002ceb20:
 STEP(UINT32_C(0x002ceb20)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ceb28));STEP(UINT32_C(0x002ceb24));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ceb24:
 STEP(UINT32_C(0x002ceb24)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ceb28));goto dispatch;
L_002ceb28:
 STEP(UINT32_C(0x002ceb28)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ceb2c));goto dispatch;
L_002ceb2c:
 STEP(UINT32_C(0x002ceb2c)); /* dfbf0090 ld ra,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ceb30));goto dispatch;
L_002ceb30:
 STEP(UINT32_C(0x002ceb30)); /* dfb70080 ld s7,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002ceb34));goto dispatch;
L_002ceb34:
 STEP(UINT32_C(0x002ceb34)); /* dfb60070 ld s6,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002ceb38));goto dispatch;
L_002ceb38:
 STEP(UINT32_C(0x002ceb38)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002ceb3c));goto dispatch;
L_002ceb3c:
 STEP(UINT32_C(0x002ceb3c)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002ceb40));goto dispatch;
L_002ceb40:
 STEP(UINT32_C(0x002ceb40)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002ceb44));goto dispatch;
L_002ceb44:
 STEP(UINT32_C(0x002ceb44)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ceb48));goto dispatch;
L_002ceb48:
 STEP(UINT32_C(0x002ceb48)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ceb4c));goto dispatch;
L_002ceb4c:
 STEP(UINT32_C(0x002ceb4c)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ceb50));goto dispatch;
L_002ceb50:
 STEP(UINT32_C(0x002ceb50)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ceb54));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));goto dispatch;
L_002ceb54:
 STEP(UINT32_C(0x002ceb54)); /* 27bd00a0 addiu sp,sp,160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));target=sx(UINT32_C(0x002ceb58));goto dispatch;
L_002ceb58:
 STEP(UINT32_C(0x002ceb58)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002ceb5c));goto dispatch;
L_002ceb5c:
 STEP(UINT32_C(0x002ceb5c)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ceb60));goto dispatch;
L_002ceb60:
 STEP(UINT32_C(0x002ceb60)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ceb64));goto dispatch;
L_002ceb64:
 STEP(UINT32_C(0x002ceb64)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ceb68));goto dispatch;
L_002ceb68:
 STEP(UINT32_C(0x002ceb68)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ceb6c));goto dispatch;
L_002ceb6c:
 STEP(UINT32_C(0x002ceb6c)); /* 12200015 beq s1,zero,002cebc4 */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002ceb70));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x002cebc4):UINT32_C(0x002ceb74));goto dispatch;}
L_002ceb70:
 STEP(UINT32_C(0x002ceb70)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002ceb74));goto dispatch;
L_002ceb74:
 STEP(UINT32_C(0x002ceb74)); /* 3c12005a lui s2,zero,0x5a */
 set(m,18u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ceb78));goto dispatch;
L_002ceb78:
 STEP(UINT32_C(0x002ceb78)); /* 3c022000 lui v0,zero,0x2000 */
 set(m,2u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002ceb7c));goto dispatch;
L_002ceb7c:
 STEP(UINT32_C(0x002ceb7c)); /* 26439d00 addiu v1,s2,-25344 */
 set(m,3u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffff9d00)));target=sx(UINT32_C(0x002ceb80));goto dispatch;
L_002ceb80:
 STEP(UINT32_C(0x002ceb80)); /* 00628025 or s0,v1,v0 */
 set(m,16u,lo(m,3u)|lo(m,2u));target=sx(UINT32_C(0x002ceb84));goto dispatch;
L_002ceb84:
 STEP(UINT32_C(0x002ceb84)); /* 0c0b5743 jal 002d5d0c */
 set(m,31u,UINT64_C(0x002ceb8c));STEP(UINT32_C(0x002ceb88));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d5d0c));goto dispatch;
L_002ceb88:
 STEP(UINT32_C(0x002ceb88)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ceb8c));goto dispatch;
L_002ceb8c:
 STEP(UINT32_C(0x002ceb8c)); /* 2c420400 sltiu v0,v0,1024 */
 set(m,2u,(lo(m,2u)<UINT64_C(0x400)));target=sx(UINT32_C(0x002ceb90));goto dispatch;
L_002ceb90:
 STEP(UINT32_C(0x002ceb90)); /* 50400004 beql v0,zero,002ceba4 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002ceb94));set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002ceba4));}else target=sx(UINT32_C(0x002ceb98));goto dispatch;
L_002ceb94:
 STEP(UINT32_C(0x002ceb94)); /* 241003ff addiu s0,zero,1023 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002ceb98));goto dispatch;
L_002ceb98:
 STEP(UINT32_C(0x002ceb98)); /* 0c0b5743 jal 002d5d0c */
 set(m,31u,UINT64_C(0x002ceba0));STEP(UINT32_C(0x002ceb9c));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d5d0c));goto dispatch;
L_002ceb9c:
 STEP(UINT32_C(0x002ceb9c)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ceba0));goto dispatch;
L_002ceba0:
 STEP(UINT32_C(0x002ceba0)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ceba4));goto dispatch;
L_002ceba4:
 STEP(UINT32_C(0x002ceba4)); /* 26429d00 addiu v0,s2,-25344 */
 set(m,2u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffff9d00)));target=sx(UINT32_C(0x002ceba8));goto dispatch;
L_002ceba8:
 STEP(UINT32_C(0x002ceba8)); /* 3c052000 lui a1,zero,0x2000 */
 set(m,5u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002cebac));goto dispatch;
L_002cebac:
 STEP(UINT32_C(0x002cebac)); /* 00452825 or a1,v0,a1 */
 set(m,5u,lo(m,2u)|lo(m,5u));target=sx(UINT32_C(0x002cebb0));goto dispatch;
L_002cebb0:
 STEP(UINT32_C(0x002cebb0)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cebb4));goto dispatch;
L_002cebb4:
 STEP(UINT32_C(0x002cebb4)); /* 0c0b50e9 jal 002d43a4 */
 set(m,31u,UINT64_C(0x002cebbc));STEP(UINT32_C(0x002cebb8));set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d43a4));goto dispatch;
L_002cebb8:
 STEP(UINT32_C(0x002cebb8)); /* 0200302d daddu a2,s0,zero */
 set(m,6u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cebbc));goto dispatch;
L_002cebbc:
 STEP(UINT32_C(0x002cebbc)); /* 02301821 addu v1,s1,s0 */
 set(m,3u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002cebc0));goto dispatch;
L_002cebc0:
 STEP(UINT32_C(0x002cebc0)); /* a0600000 sb zero,0x0(v1) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002cebc4));goto dispatch;
L_002cebc4:
 STEP(UINT32_C(0x002cebc4)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cebc8));goto dispatch;
L_002cebc8:
 STEP(UINT32_C(0x002cebc8)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cebcc));goto dispatch;
L_002cebcc:
 STEP(UINT32_C(0x002cebcc)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cebd0));goto dispatch;
L_002cebd0:
 STEP(UINT32_C(0x002cebd0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cebd4));goto dispatch;
L_002cebd4:
 STEP(UINT32_C(0x002cebd4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cebd8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002cebd8:
 STEP(UINT32_C(0x002cebd8)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002cebdc));goto dispatch;
L_002cebe0:
 STEP(UINT32_C(0x002cebe0)); /* 27bdff60 addiu sp,sp,-160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff60)));target=sx(UINT32_C(0x002cebe4));goto dispatch;
L_002cebe4:
 STEP(UINT32_C(0x002cebe4)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002cebe8));goto dispatch;
L_002cebe8:
 STEP(UINT32_C(0x002cebe8)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cebec));goto dispatch;
L_002cebec:
 STEP(UINT32_C(0x002cebec)); /* 0080a82d daddu s5,a0,zero */
 set(m,21u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cebf0));goto dispatch;
L_002cebf0:
 STEP(UINT32_C(0x002cebf0)); /* 3c130053 lui s3,zero,0x53 */
 set(m,19u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cebf4));goto dispatch;
L_002cebf4:
 STEP(UINT32_C(0x002cebf4)); /* ffb60070 sd s6,0x70(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002cebf8));goto dispatch;
L_002cebf8:
 STEP(UINT32_C(0x002cebf8)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002cebfc));goto dispatch;
L_002cebfc:
 STEP(UINT32_C(0x002cebfc)); /* 00e0b02d daddu s6,a3,zero */
 set(m,22u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002cec00));goto dispatch;
L_002cec00:
 STEP(UINT32_C(0x002cec00)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cec04));goto dispatch;
L_002cec04:
 STEP(UINT32_C(0x002cec04)); /* 00a0a02d daddu s4,a1,zero */
 set(m,20u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002cec08));goto dispatch;
L_002cec08:
 STEP(UINT32_C(0x002cec08)); /* 8e64bb24 lw a0,-0x44dc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cec0c));goto dispatch;
L_002cec0c:
 STEP(UINT32_C(0x002cec0c)); /* 00c0902d daddu s2,a2,zero */
 set(m,18u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002cec10));goto dispatch;
L_002cec10:
 STEP(UINT32_C(0x002cec10)); /* ffbf0090 sd ra,0x90(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x002cec14));goto dispatch;
L_002cec14:
 STEP(UINT32_C(0x002cec14)); /* ffb70080 sd s7,0x80(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002cec18));goto dispatch;
L_002cec18:
 STEP(UINT32_C(0x002cec18)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cec1c));goto dispatch;
L_002cec1c:
 STEP(UINT32_C(0x002cec1c)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cec24));STEP(UINT32_C(0x002cec20));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cec20:
 STEP(UINT32_C(0x002cec20)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cec24));goto dispatch;
L_002cec24:
 STEP(UINT32_C(0x002cec24)); /* 04410003 regimm1 v0,002cec34 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cec28));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cec34):UINT32_C(0x002cec2c));goto dispatch;}
L_002cec28:
 STEP(UINT32_C(0x002cec28)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cec2c));goto dispatch;
L_002cec2c:
 STEP(UINT32_C(0x002cec2c)); /* 10000035 beq zero,zero,002ced04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cec30));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ced04):UINT32_C(0x002cec34));goto dispatch;}
L_002cec30:
 STEP(UINT32_C(0x002cec30)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cec34));goto dispatch;
L_002cec34:
 STEP(UINT32_C(0x002cec34)); /* 24579740 addiu s7,v0,-26816 */
 set(m,23u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cec38));goto dispatch;
L_002cec38:
 STEP(UINT32_C(0x002cec38)); /* 8ee30024 lw v1,0x24(s7) */
 READ((uint32_t)lo(m,23u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cec3c));goto dispatch;
L_002cec3c:
 STEP(UINT32_C(0x002cec3c)); /* 14600005 bne v1,zero,002cec54 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cec40));/* nop */target=sx(taken?UINT32_C(0x002cec54):UINT32_C(0x002cec44));goto dispatch;}
L_002cec40:
 STEP(UINT32_C(0x002cec40)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cec44));goto dispatch;
L_002cec44:
 STEP(UINT32_C(0x002cec44)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cec4c));STEP(UINT32_C(0x002cec48));READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cec48:
 STEP(UINT32_C(0x002cec48)); /* 8e64bb24 lw a0,-0x44dc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cec4c));goto dispatch;
L_002cec4c:
 STEP(UINT32_C(0x002cec4c)); /* 1000002d beq zero,zero,002ced04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cec50));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ced04):UINT32_C(0x002cec54));goto dispatch;}
L_002cec50:
 STEP(UINT32_C(0x002cec50)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cec54));goto dispatch;
L_002cec54:
 STEP(UINT32_C(0x002cec54)); /* 12400004 beq s2,zero,002cec68 */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002cec58));/* nop */target=sx(taken?UINT32_C(0x002cec68):UINT32_C(0x002cec5c));goto dispatch;}
L_002cec58:
 STEP(UINT32_C(0x002cec58)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cec5c));goto dispatch;
L_002cec5c:
 STEP(UINT32_C(0x002cec5c)); /* 82420000 lb v0,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002cec60));goto dispatch;
L_002cec60:
 STEP(UINT32_C(0x002cec60)); /* 14400005 bne v0,zero,002cec78 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cec64));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cec78):UINT32_C(0x002cec68));goto dispatch;}
L_002cec64:
 STEP(UINT32_C(0x002cec64)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cec68));goto dispatch;
L_002cec68:
 STEP(UINT32_C(0x002cec68)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cec70));STEP(UINT32_C(0x002cec6c));READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cec6c:
 STEP(UINT32_C(0x002cec6c)); /* 8e64bb24 lw a0,-0x44dc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cec70));goto dispatch;
L_002cec70:
 STEP(UINT32_C(0x002cec70)); /* 10000024 beq zero,zero,002ced04 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cec74));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(taken?UINT32_C(0x002ced04):UINT32_C(0x002cec78));goto dispatch;}
L_002cec74:
 STEP(UINT32_C(0x002cec74)); /* 2402ff2e addiu v0,zero,-210 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(UINT32_C(0x002cec78));goto dispatch;
L_002cec78:
 STEP(UINT32_C(0x002cec78)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cec7c));goto dispatch;
L_002cec7c:
 STEP(UINT32_C(0x002cec7c)); /* 245197f0 addiu s1,v0,-26640 */
 set(m,17u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0)));target=sx(UINT32_C(0x002cec80));goto dispatch;
L_002cec80:
 STEP(UINT32_C(0x002cec80)); /* 26109d00 addiu s0,s0,-25344 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffff9d00)));target=sx(UINT32_C(0x002cec84));goto dispatch;
L_002cec84:
 STEP(UINT32_C(0x002cec84)); /* ac5597f0 sw s5,-0x6810(v0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0),&value32,4u);target=sx(UINT32_C(0x002cec88));goto dispatch;
L_002cec88:
 STEP(UINT32_C(0x002cec88)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002cec8c));goto dispatch;
L_002cec8c:
 STEP(UINT32_C(0x002cec8c)); /* ae300010 sw s0,0x10(s1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002cec90));goto dispatch;
L_002cec90:
 STEP(UINT32_C(0x002cec90)); /* 26240014 addiu a0,s1,20 */
 set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002cec94));goto dispatch;
L_002cec94:
 STEP(UINT32_C(0x002cec94)); /* ae340004 sw s4,0x4(s1) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002cec98));goto dispatch;
L_002cec98:
 STEP(UINT32_C(0x002cec98)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002ceca0));STEP(UINT32_C(0x002cec9c));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002cec9c:
 STEP(UINT32_C(0x002cec9c)); /* 240603ff addiu a2,zero,1023 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002ceca0));goto dispatch;
L_002ceca0:
 STEP(UINT32_C(0x002ceca0)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ceca4));goto dispatch;
L_002ceca4:
 STEP(UINT32_C(0x002ceca4)); /* a2200413 sb zero,0x413(s1) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000413),&byte,1u);}target=sx(UINT32_C(0x002ceca8));goto dispatch;
L_002ceca8:
 STEP(UINT32_C(0x002ceca8)); /* 0c0b7916 jal 002de458 */
 set(m,31u,UINT64_C(0x002cecb0));STEP(UINT32_C(0x002cecac));set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(UINT32_C(0x002de458));goto dispatch;
L_002cecac:
 STEP(UINT32_C(0x002cecac)); /* 24050400 addiu a1,zero,1024 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000400)));target=sx(UINT32_C(0x002cecb0));goto dispatch;
L_002cecb0:
 STEP(UINT32_C(0x002cecb0)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cecb4));goto dispatch;
L_002cecb4:
 STEP(UINT32_C(0x002cecb4)); /* 3c0b002d lui t3,zero,0x2d */
 set(m,11u,sx(UINT32_C(0x002d0000)));target=sx(UINT32_C(0x002cecb8));goto dispatch;
L_002cecb8:
 STEP(UINT32_C(0x002cecb8)); /* afb60000 sw s6,0x0(sp) */
 value32=(uint32_t)lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cecbc));goto dispatch;
L_002cecbc:
 STEP(UINT32_C(0x002cecbc)); /* 02e0202d daddu a0,s7,zero */
 set(m,4u,lo(m,23u)+lo(m,0u));target=sx(UINT32_C(0x002cecc0));goto dispatch;
L_002cecc0:
 STEP(UINT32_C(0x002cecc0)); /* 0220382d daddu a3,s1,zero */
 set(m,7u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cecc4));goto dispatch;
L_002cecc4:
 STEP(UINT32_C(0x002cecc4)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cecc8));goto dispatch;
L_002cecc8:
 STEP(UINT32_C(0x002cecc8)); /* 256beb58 addiu t3,t3,-5288 */
 set(m,11u,sx((uint32_t)lo(m,11u)+UINT32_C(0xffffeb58)));target=sx(UINT32_C(0x002ceccc));goto dispatch;
L_002ceccc:
 STEP(UINT32_C(0x002ceccc)); /* 2405000c addiu a1,zero,12 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002cecd0));goto dispatch;
L_002cecd0:
 STEP(UINT32_C(0x002cecd0)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cecd4));goto dispatch;
L_002cecd4:
 STEP(UINT32_C(0x002cecd4)); /* 24080414 addiu t0,zero,1044 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000414)));target=sx(UINT32_C(0x002cecd8));goto dispatch;
L_002cecd8:
 STEP(UINT32_C(0x002cecd8)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cece0));STEP(UINT32_C(0x002cecdc));set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cecdc:
 STEP(UINT32_C(0x002cecdc)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cece0));goto dispatch;
L_002cece0:
 STEP(UINT32_C(0x002cece0)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cece4));goto dispatch;
L_002cece4:
 STEP(UINT32_C(0x002cece4)); /* 16000004 bne s0,zero,002cecf8 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cece8));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002cecf8):UINT32_C(0x002cecec));goto dispatch;}
L_002cece8:
 STEP(UINT32_C(0x002cece8)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cecec));goto dispatch;
L_002cecec:
 STEP(UINT32_C(0x002cecec)); /* 2402000c addiu v0,zero,12 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002cecf0));goto dispatch;
L_002cecf0:
 STEP(UINT32_C(0x002cecf0)); /* 10000003 beq zero,zero,002ced00 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cecf4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ced00):UINT32_C(0x002cecf8));goto dispatch;}
L_002cecf4:
 STEP(UINT32_C(0x002cecf4)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002cecf8));goto dispatch;
L_002cecf8:
 STEP(UINT32_C(0x002cecf8)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ced00));STEP(UINT32_C(0x002cecfc));READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cecfc:
 STEP(UINT32_C(0x002cecfc)); /* 8e64bb24 lw a0,-0x44dc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ced00));goto dispatch;
L_002ced00:
 STEP(UINT32_C(0x002ced00)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ced04));goto dispatch;
L_002ced04:
 STEP(UINT32_C(0x002ced04)); /* dfbf0090 ld ra,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002ced08));goto dispatch;
L_002ced08:
 STEP(UINT32_C(0x002ced08)); /* dfb70080 ld s7,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002ced0c));goto dispatch;
L_002ced0c:
 STEP(UINT32_C(0x002ced0c)); /* dfb60070 ld s6,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002ced10));goto dispatch;
L_002ced10:
 STEP(UINT32_C(0x002ced10)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002ced14));goto dispatch;
L_002ced14:
 STEP(UINT32_C(0x002ced14)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002ced18));goto dispatch;
L_002ced18:
 STEP(UINT32_C(0x002ced18)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002ced1c));goto dispatch;
L_002ced1c:
 STEP(UINT32_C(0x002ced1c)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002ced20));goto dispatch;
L_002ced20:
 STEP(UINT32_C(0x002ced20)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002ced24));goto dispatch;
L_002ced24:
 STEP(UINT32_C(0x002ced24)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002ced28));goto dispatch;
L_002ced28:
 STEP(UINT32_C(0x002ced28)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002ced2c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));goto dispatch;
L_002ced2c:
 STEP(UINT32_C(0x002ced2c)); /* 27bd00a0 addiu sp,sp,160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));target=sx(UINT32_C(0x002ced30));goto dispatch;
L_002ced30:
 STEP(UINT32_C(0x002ced30)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x002ced34));goto dispatch;
L_002ced34:
 STEP(UINT32_C(0x002ced34)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ced38));goto dispatch;
L_002ced38:
 STEP(UINT32_C(0x002ced38)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002ced3c));goto dispatch;
L_002ced3c:
 STEP(UINT32_C(0x002ced3c)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002ced40));goto dispatch;
L_002ced40:
 STEP(UINT32_C(0x002ced40)); /* 3c110053 lui s1,zero,0x53 */
 set(m,17u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ced44));goto dispatch;
L_002ced44:
 STEP(UINT32_C(0x002ced44)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002ced48));goto dispatch;
L_002ced48:
 STEP(UINT32_C(0x002ced48)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ced4c));goto dispatch;
L_002ced4c:
 STEP(UINT32_C(0x002ced4c)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ced50));goto dispatch;
L_002ced50:
 STEP(UINT32_C(0x002ced50)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002ced58));STEP(UINT32_C(0x002ced54));set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002ced54:
 STEP(UINT32_C(0x002ced54)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002ced58));goto dispatch;
L_002ced58:
 STEP(UINT32_C(0x002ced58)); /* 04410003 regimm1 v0,002ced68 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002ced5c));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ced68):UINT32_C(0x002ced60));goto dispatch;}
L_002ced5c:
 STEP(UINT32_C(0x002ced5c)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ced60));goto dispatch;
L_002ced60:
 STEP(UINT32_C(0x002ced60)); /* 1000001f beq zero,zero,002cede0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ced64));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002cede0):UINT32_C(0x002ced68));goto dispatch;}
L_002ced64:
 STEP(UINT32_C(0x002ced64)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002ced68));goto dispatch;
L_002ced68:
 STEP(UINT32_C(0x002ced68)); /* 24449740 addiu a0,v0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002ced6c));goto dispatch;
L_002ced6c:
 STEP(UINT32_C(0x002ced6c)); /* 8c830024 lw v1,0x24(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002ced70));goto dispatch;
L_002ced70:
 STEP(UINT32_C(0x002ced70)); /* 14600005 bne v1,zero,002ced88 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002ced74));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002ced88):UINT32_C(0x002ced78));goto dispatch;}
L_002ced74:
 STEP(UINT32_C(0x002ced74)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ced78));goto dispatch;
L_002ced78:
 STEP(UINT32_C(0x002ced78)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ced80));STEP(UINT32_C(0x002ced7c));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ced7c:
 STEP(UINT32_C(0x002ced7c)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ced80));goto dispatch;
L_002ced80:
 STEP(UINT32_C(0x002ced80)); /* 10000017 beq zero,zero,002cede0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ced84));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002cede0):UINT32_C(0x002ced88));goto dispatch;}
L_002ced84:
 STEP(UINT32_C(0x002ced84)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002ced88));goto dispatch;
L_002ced88:
 STEP(UINT32_C(0x002ced88)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ced8c));goto dispatch;
L_002ced8c:
 STEP(UINT32_C(0x002ced8c)); /* 244297c0 addiu v0,v0,-26688 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002ced90));goto dispatch;
L_002ced90:
 STEP(UINT32_C(0x002ced90)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ced94));goto dispatch;
L_002ced94:
 STEP(UINT32_C(0x002ced94)); /* ac500008 sw s0,0x8(v0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002ced98));goto dispatch;
L_002ced98:
 STEP(UINT32_C(0x002ced98)); /* 0040382d daddu a3,v0,zero */
 set(m,7u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ced9c));goto dispatch;
L_002ced9c:
 STEP(UINT32_C(0x002ced9c)); /* ac520004 sw s2,0x4(v0) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002ceda0));goto dispatch;
L_002ceda0:
 STEP(UINT32_C(0x002ceda0)); /* 24050010 addiu a1,zero,16 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002ceda4));goto dispatch;
L_002ceda4:
 STEP(UINT32_C(0x002ceda4)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ceda8));goto dispatch;
L_002ceda8:
 STEP(UINT32_C(0x002ceda8)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cedac));goto dispatch;
L_002cedac:
 STEP(UINT32_C(0x002cedac)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002cedb0));goto dispatch;
L_002cedb0:
 STEP(UINT32_C(0x002cedb0)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cedb4));goto dispatch;
L_002cedb4:
 STEP(UINT32_C(0x002cedb4)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cedbc));STEP(UINT32_C(0x002cedb8));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cedb8:
 STEP(UINT32_C(0x002cedb8)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cedbc));goto dispatch;
L_002cedbc:
 STEP(UINT32_C(0x002cedbc)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cedc0));goto dispatch;
L_002cedc0:
 STEP(UINT32_C(0x002cedc0)); /* 16000004 bne s0,zero,002cedd4 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cedc4));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002cedd4):UINT32_C(0x002cedc8));goto dispatch;}
L_002cedc4:
 STEP(UINT32_C(0x002cedc4)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cedc8));goto dispatch;
L_002cedc8:
 STEP(UINT32_C(0x002cedc8)); /* 24020010 addiu v0,zero,16 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002cedcc));goto dispatch;
L_002cedcc:
 STEP(UINT32_C(0x002cedcc)); /* 10000003 beq zero,zero,002ceddc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cedd0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ceddc):UINT32_C(0x002cedd4));goto dispatch;}
L_002cedd0:
 STEP(UINT32_C(0x002cedd0)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002cedd4));goto dispatch;
L_002cedd4:
 STEP(UINT32_C(0x002cedd4)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ceddc));STEP(UINT32_C(0x002cedd8));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cedd8:
 STEP(UINT32_C(0x002cedd8)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ceddc));goto dispatch;
L_002ceddc:
 STEP(UINT32_C(0x002ceddc)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cede0));goto dispatch;
L_002cede0:
 STEP(UINT32_C(0x002cede0)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cede4));goto dispatch;
L_002cede4:
 STEP(UINT32_C(0x002cede4)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cede8));goto dispatch;
L_002cede8:
 STEP(UINT32_C(0x002cede8)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cedec));goto dispatch;
L_002cedec:
 STEP(UINT32_C(0x002cedec)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cedf0));goto dispatch;
L_002cedf0:
 STEP(UINT32_C(0x002cedf0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cedf4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_002cedf4:
 STEP(UINT32_C(0x002cedf4)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x002cedf8));goto dispatch;
L_002cedf8:
 STEP(UINT32_C(0x002cedf8)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x002cedfc));goto dispatch;
L_002cedfc:
 STEP(UINT32_C(0x002cedfc)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002cee00));goto dispatch;
L_002cee00:
 STEP(UINT32_C(0x002cee00)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cee04));goto dispatch;
L_002cee04:
 STEP(UINT32_C(0x002cee04)); /* 0080a82d daddu s5,a0,zero */
 set(m,21u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cee08));goto dispatch;
L_002cee08:
 STEP(UINT32_C(0x002cee08)); /* 3c120053 lui s2,zero,0x53 */
 set(m,18u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cee0c));goto dispatch;
L_002cee0c:
 STEP(UINT32_C(0x002cee0c)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002cee10));goto dispatch;
L_002cee10:
 STEP(UINT32_C(0x002cee10)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cee14));goto dispatch;
L_002cee14:
 STEP(UINT32_C(0x002cee14)); /* 00a0a02d daddu s4,a1,zero */
 set(m,20u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002cee18));goto dispatch;
L_002cee18:
 STEP(UINT32_C(0x002cee18)); /* 8e44bb24 lw a0,-0x44dc(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cee1c));goto dispatch;
L_002cee1c:
 STEP(UINT32_C(0x002cee1c)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002cee20));goto dispatch;
L_002cee20:
 STEP(UINT32_C(0x002cee20)); /* ffbf0070 sd ra,0x70(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002cee24));goto dispatch;
L_002cee24:
 STEP(UINT32_C(0x002cee24)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cee28));goto dispatch;
L_002cee28:
 STEP(UINT32_C(0x002cee28)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cee30));STEP(UINT32_C(0x002cee2c));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cee2c:
 STEP(UINT32_C(0x002cee2c)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cee30));goto dispatch;
L_002cee30:
 STEP(UINT32_C(0x002cee30)); /* 04410003 regimm1 v0,002cee40 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cee34));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cee40):UINT32_C(0x002cee38));goto dispatch;}
L_002cee34:
 STEP(UINT32_C(0x002cee34)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cee38));goto dispatch;
L_002cee38:
 STEP(UINT32_C(0x002cee38)); /* 10000030 beq zero,zero,002ceefc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cee3c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002ceefc):UINT32_C(0x002cee40));goto dispatch;}
L_002cee3c:
 STEP(UINT32_C(0x002cee3c)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cee40));goto dispatch;
L_002cee40:
 STEP(UINT32_C(0x002cee40)); /* 24539740 addiu s3,v0,-26816 */
 set(m,19u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cee44));goto dispatch;
L_002cee44:
 STEP(UINT32_C(0x002cee44)); /* 8e630024 lw v1,0x24(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cee48));goto dispatch;
L_002cee48:
 STEP(UINT32_C(0x002cee48)); /* 14600005 bne v1,zero,002cee60 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cee4c));/* nop */target=sx(taken?UINT32_C(0x002cee60):UINT32_C(0x002cee50));goto dispatch;}
L_002cee4c:
 STEP(UINT32_C(0x002cee4c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cee50));goto dispatch;
L_002cee50:
 STEP(UINT32_C(0x002cee50)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cee58));STEP(UINT32_C(0x002cee54));READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cee54:
 STEP(UINT32_C(0x002cee54)); /* 8e44bb24 lw a0,-0x44dc(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cee58));goto dispatch;
L_002cee58:
 STEP(UINT32_C(0x002cee58)); /* 10000028 beq zero,zero,002ceefc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cee5c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002ceefc):UINT32_C(0x002cee60));goto dispatch;}
L_002cee5c:
 STEP(UINT32_C(0x002cee5c)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cee60));goto dispatch;
L_002cee60:
 STEP(UINT32_C(0x002cee60)); /* 12200004 beq s1,zero,002cee74 */
 {int taken=(lo(m,17u)==lo(m,0u));STEP(UINT32_C(0x002cee64));/* nop */target=sx(taken?UINT32_C(0x002cee74):UINT32_C(0x002cee68));goto dispatch;}
L_002cee64:
 STEP(UINT32_C(0x002cee64)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cee68));goto dispatch;
L_002cee68:
 STEP(UINT32_C(0x002cee68)); /* 82220000 lb v0,0x0(s1) */
 {uint8_t byte;READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002cee6c));goto dispatch;
L_002cee6c:
 STEP(UINT32_C(0x002cee6c)); /* 14400005 bne v0,zero,002cee84 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cee70));set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cee84):UINT32_C(0x002cee74));goto dispatch;}
L_002cee70:
 STEP(UINT32_C(0x002cee70)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cee74));goto dispatch;
L_002cee74:
 STEP(UINT32_C(0x002cee74)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cee7c));STEP(UINT32_C(0x002cee78));READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cee78:
 STEP(UINT32_C(0x002cee78)); /* 8e44bb24 lw a0,-0x44dc(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cee7c));goto dispatch;
L_002cee7c:
 STEP(UINT32_C(0x002cee7c)); /* 1000001f beq zero,zero,002ceefc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cee80));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(taken?UINT32_C(0x002ceefc):UINT32_C(0x002cee84));goto dispatch;}
L_002cee80:
 STEP(UINT32_C(0x002cee80)); /* 2402ff2e addiu v0,zero,-210 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(UINT32_C(0x002cee84));goto dispatch;
L_002cee84:
 STEP(UINT32_C(0x002cee84)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cee88));goto dispatch;
L_002cee88:
 STEP(UINT32_C(0x002cee88)); /* 26109804 addiu s0,s0,-26620 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffff9804)));target=sx(UINT32_C(0x002cee8c));goto dispatch;
L_002cee8c:
 STEP(UINT32_C(0x002cee8c)); /* 240603ff addiu a2,zero,1023 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002cee90));goto dispatch;
L_002cee90:
 STEP(UINT32_C(0x002cee90)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002cee98));STEP(UINT32_C(0x002cee94));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002cee94:
 STEP(UINT32_C(0x002cee94)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cee98));goto dispatch;
L_002cee98:
 STEP(UINT32_C(0x002cee98)); /* 2603ffec addiu v1,s0,-20 */
 set(m,3u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffec)));target=sx(UINT32_C(0x002cee9c));goto dispatch;
L_002cee9c:
 STEP(UINT32_C(0x002cee9c)); /* ae15ffec sw s5,-0x14(s0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0xffffffec),&value32,4u);target=sx(UINT32_C(0x002ceea0));goto dispatch;
L_002ceea0:
 STEP(UINT32_C(0x002ceea0)); /* ac740004 sw s4,0x4(v1) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002ceea4));goto dispatch;
L_002ceea4:
 STEP(UINT32_C(0x002ceea4)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002ceea8));goto dispatch;
L_002ceea8:
 STEP(UINT32_C(0x002ceea8)); /* a0600413 sb zero,0x413(v1) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000413),&byte,1u);}target=sx(UINT32_C(0x002ceeac));goto dispatch;
L_002ceeac:
 STEP(UINT32_C(0x002ceeac)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002ceeb0));goto dispatch;
L_002ceeb0:
 STEP(UINT32_C(0x002ceeb0)); /* ac600008 sw zero,0x8(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002ceeb4));goto dispatch;
L_002ceeb4:
 STEP(UINT32_C(0x002ceeb4)); /* 0060382d daddu a3,v1,zero */
 set(m,7u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002ceeb8));goto dispatch;
L_002ceeb8:
 STEP(UINT32_C(0x002ceeb8)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002ceebc));goto dispatch;
L_002ceebc:
 STEP(UINT32_C(0x002ceebc)); /* 2405000f addiu a1,zero,15 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000f)));target=sx(UINT32_C(0x002ceec0));goto dispatch;
L_002ceec0:
 STEP(UINT32_C(0x002ceec0)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002ceec4));goto dispatch;
L_002ceec4:
 STEP(UINT32_C(0x002ceec4)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002ceec8));goto dispatch;
L_002ceec8:
 STEP(UINT32_C(0x002ceec8)); /* 24080414 addiu t0,zero,1044 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000414)));target=sx(UINT32_C(0x002ceecc));goto dispatch;
L_002ceecc:
 STEP(UINT32_C(0x002ceecc)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002ceed0));goto dispatch;
L_002ceed0:
 STEP(UINT32_C(0x002ceed0)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002ceed8));STEP(UINT32_C(0x002ceed4));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002ceed4:
 STEP(UINT32_C(0x002ceed4)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ceed8));goto dispatch;
L_002ceed8:
 STEP(UINT32_C(0x002ceed8)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002ceedc));goto dispatch;
L_002ceedc:
 STEP(UINT32_C(0x002ceedc)); /* 16000004 bne s0,zero,002ceef0 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002ceee0));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002ceef0):UINT32_C(0x002ceee4));goto dispatch;}
L_002ceee0:
 STEP(UINT32_C(0x002ceee0)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002ceee4));goto dispatch;
L_002ceee4:
 STEP(UINT32_C(0x002ceee4)); /* 2402000f addiu v0,zero,15 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000f)));target=sx(UINT32_C(0x002ceee8));goto dispatch;
L_002ceee8:
 STEP(UINT32_C(0x002ceee8)); /* 10000003 beq zero,zero,002ceef8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002ceeec));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002ceef8):UINT32_C(0x002ceef0));goto dispatch;}
L_002ceeec:
 STEP(UINT32_C(0x002ceeec)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002ceef0));goto dispatch;
L_002ceef0:
 STEP(UINT32_C(0x002ceef0)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002ceef8));STEP(UINT32_C(0x002ceef4));READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002ceef4:
 STEP(UINT32_C(0x002ceef4)); /* 8e44bb24 lw a0,-0x44dc(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002ceef8));goto dispatch;
L_002ceef8:
 STEP(UINT32_C(0x002ceef8)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002ceefc));goto dispatch;
L_002ceefc:
 STEP(UINT32_C(0x002ceefc)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cef00));goto dispatch;
L_002cef00:
 STEP(UINT32_C(0x002cef00)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002cef04));goto dispatch;
L_002cef04:
 STEP(UINT32_C(0x002cef04)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002cef08));goto dispatch;
L_002cef08:
 STEP(UINT32_C(0x002cef08)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002cef0c));goto dispatch;
L_002cef0c:
 STEP(UINT32_C(0x002cef0c)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cef10));goto dispatch;
L_002cef10:
 STEP(UINT32_C(0x002cef10)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cef14));goto dispatch;
L_002cef14:
 STEP(UINT32_C(0x002cef14)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cef18));goto dispatch;
L_002cef18:
 STEP(UINT32_C(0x002cef18)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cef1c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_002cef1c:
 STEP(UINT32_C(0x002cef1c)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x002cef20));goto dispatch;
L_002cef20:
 STEP(UINT32_C(0x002cef20)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002cef24));goto dispatch;
L_002cef24:
 STEP(UINT32_C(0x002cef24)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cef28));goto dispatch;
L_002cef28:
 STEP(UINT32_C(0x002cef28)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cef2c));goto dispatch;
L_002cef2c:
 STEP(UINT32_C(0x002cef2c)); /* 3c110053 lui s1,zero,0x53 */
 set(m,17u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cef30));goto dispatch;
L_002cef30:
 STEP(UINT32_C(0x002cef30)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cef34));goto dispatch;
L_002cef34:
 STEP(UINT32_C(0x002cef34)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cef38));goto dispatch;
L_002cef38:
 STEP(UINT32_C(0x002cef38)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cef40));STEP(UINT32_C(0x002cef3c));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cef3c:
 STEP(UINT32_C(0x002cef3c)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cef40));goto dispatch;
L_002cef40:
 STEP(UINT32_C(0x002cef40)); /* 04410003 regimm1 v0,002cef50 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cef44));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cef50):UINT32_C(0x002cef48));goto dispatch;}
L_002cef44:
 STEP(UINT32_C(0x002cef44)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cef48));goto dispatch;
L_002cef48:
 STEP(UINT32_C(0x002cef48)); /* 1000001d beq zero,zero,002cefc0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cef4c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002cefc0):UINT32_C(0x002cef50));goto dispatch;}
L_002cef4c:
 STEP(UINT32_C(0x002cef4c)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cef50));goto dispatch;
L_002cef50:
 STEP(UINT32_C(0x002cef50)); /* 24449740 addiu a0,v0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cef54));goto dispatch;
L_002cef54:
 STEP(UINT32_C(0x002cef54)); /* 8c830024 lw v1,0x24(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cef58));goto dispatch;
L_002cef58:
 STEP(UINT32_C(0x002cef58)); /* 14600005 bne v1,zero,002cef70 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cef5c));set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cef70):UINT32_C(0x002cef60));goto dispatch;}
L_002cef5c:
 STEP(UINT32_C(0x002cef5c)); /* 3c07005a lui a3,zero,0x5a */
 set(m,7u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cef60));goto dispatch;
L_002cef60:
 STEP(UINT32_C(0x002cef60)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cef68));STEP(UINT32_C(0x002cef64));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cef64:
 STEP(UINT32_C(0x002cef64)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cef68));goto dispatch;
L_002cef68:
 STEP(UINT32_C(0x002cef68)); /* 10000015 beq zero,zero,002cefc0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cef6c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002cefc0):UINT32_C(0x002cef70));goto dispatch;}
L_002cef6c:
 STEP(UINT32_C(0x002cef6c)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cef70));goto dispatch;
L_002cef70:
 STEP(UINT32_C(0x002cef70)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cef74));goto dispatch;
L_002cef74:
 STEP(UINT32_C(0x002cef74)); /* acf097c0 sw s0,-0x6840(a3) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0xffff97c0),&value32,4u);target=sx(UINT32_C(0x002cef78));goto dispatch;
L_002cef78:
 STEP(UINT32_C(0x002cef78)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cef7c));goto dispatch;
L_002cef7c:
 STEP(UINT32_C(0x002cef7c)); /* 24e797c0 addiu a3,a3,-26688 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002cef80));goto dispatch;
L_002cef80:
 STEP(UINT32_C(0x002cef80)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cef84));goto dispatch;
L_002cef84:
 STEP(UINT32_C(0x002cef84)); /* 2405000a addiu a1,zero,10 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002cef88));goto dispatch;
L_002cef88:
 STEP(UINT32_C(0x002cef88)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cef8c));goto dispatch;
L_002cef8c:
 STEP(UINT32_C(0x002cef8c)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002cef90));goto dispatch;
L_002cef90:
 STEP(UINT32_C(0x002cef90)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cef94));goto dispatch;
L_002cef94:
 STEP(UINT32_C(0x002cef94)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cef9c));STEP(UINT32_C(0x002cef98));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cef98:
 STEP(UINT32_C(0x002cef98)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cef9c));goto dispatch;
L_002cef9c:
 STEP(UINT32_C(0x002cef9c)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cefa0));goto dispatch;
L_002cefa0:
 STEP(UINT32_C(0x002cefa0)); /* 16000004 bne s0,zero,002cefb4 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cefa4));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002cefb4):UINT32_C(0x002cefa8));goto dispatch;}
L_002cefa4:
 STEP(UINT32_C(0x002cefa4)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cefa8));goto dispatch;
L_002cefa8:
 STEP(UINT32_C(0x002cefa8)); /* 2402000a addiu v0,zero,10 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002cefac));goto dispatch;
L_002cefac:
 STEP(UINT32_C(0x002cefac)); /* 10000003 beq zero,zero,002cefbc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cefb0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002cefbc):UINT32_C(0x002cefb4));goto dispatch;}
L_002cefb0:
 STEP(UINT32_C(0x002cefb0)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002cefb4));goto dispatch;
L_002cefb4:
 STEP(UINT32_C(0x002cefb4)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cefbc));STEP(UINT32_C(0x002cefb8));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cefb8:
 STEP(UINT32_C(0x002cefb8)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cefbc));goto dispatch;
L_002cefbc:
 STEP(UINT32_C(0x002cefbc)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cefc0));goto dispatch;
L_002cefc0:
 STEP(UINT32_C(0x002cefc0)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cefc4));goto dispatch;
L_002cefc4:
 STEP(UINT32_C(0x002cefc4)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cefc8));goto dispatch;
L_002cefc8:
 STEP(UINT32_C(0x002cefc8)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cefcc));goto dispatch;
L_002cefcc:
 STEP(UINT32_C(0x002cefcc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cefd0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002cefd0:
 STEP(UINT32_C(0x002cefd0)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002cefd4));goto dispatch;
L_002cefd8:
 STEP(UINT32_C(0x002cefd8)); /* 27bdff60 addiu sp,sp,-160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff60)));target=sx(UINT32_C(0x002cefdc));goto dispatch;
L_002cefdc:
 STEP(UINT32_C(0x002cefdc)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002cefe0));goto dispatch;
L_002cefe0:
 STEP(UINT32_C(0x002cefe0)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002cefe4));goto dispatch;
L_002cefe4:
 STEP(UINT32_C(0x002cefe4)); /* 0080a82d daddu s5,a0,zero */
 set(m,21u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cefe8));goto dispatch;
L_002cefe8:
 STEP(UINT32_C(0x002cefe8)); /* 3c140053 lui s4,zero,0x53 */
 set(m,20u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cefec));goto dispatch;
L_002cefec:
 STEP(UINT32_C(0x002cefec)); /* ffb60070 sd s6,0x70(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002ceff0));goto dispatch;
L_002ceff0:
 STEP(UINT32_C(0x002ceff0)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002ceff4));goto dispatch;
L_002ceff4:
 STEP(UINT32_C(0x002ceff4)); /* 00e0b02d daddu s6,a3,zero */
 set(m,22u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002ceff8));goto dispatch;
L_002ceff8:
 STEP(UINT32_C(0x002ceff8)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002ceffc));goto dispatch;
L_002ceffc:
 STEP(UINT32_C(0x002ceffc)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002cf000));goto dispatch;
L_002cf000:
 STEP(UINT32_C(0x002cf000)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cf004));goto dispatch;
L_002cf004:
 STEP(UINT32_C(0x002cf004)); /* 00c0902d daddu s2,a2,zero */
 set(m,18u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002cf008));goto dispatch;
L_002cf008:
 STEP(UINT32_C(0x002cf008)); /* 8e84bb24 lw a0,-0x44dc(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf00c));goto dispatch;
L_002cf00c:
 STEP(UINT32_C(0x002cf00c)); /* 0100882d daddu s1,t0,zero */
 set(m,17u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002cf010));goto dispatch;
L_002cf010:
 STEP(UINT32_C(0x002cf010)); /* ffbf0090 sd ra,0x90(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);target=sx(UINT32_C(0x002cf014));goto dispatch;
L_002cf014:
 STEP(UINT32_C(0x002cf014)); /* ffb70080 sd s7,0x80(sp) */
 value64=lo(m,23u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002cf018));goto dispatch;
L_002cf018:
 STEP(UINT32_C(0x002cf018)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cf020));STEP(UINT32_C(0x002cf01c));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cf01c:
 STEP(UINT32_C(0x002cf01c)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cf020));goto dispatch;
L_002cf020:
 STEP(UINT32_C(0x002cf020)); /* 04410003 regimm1 v0,002cf030 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cf024));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cf030):UINT32_C(0x002cf028));goto dispatch;}
L_002cf024:
 STEP(UINT32_C(0x002cf024)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf028));goto dispatch;
L_002cf028:
 STEP(UINT32_C(0x002cf028)); /* 10000056 beq zero,zero,002cf184 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf02c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002cf184):UINT32_C(0x002cf030));goto dispatch;}
L_002cf02c:
 STEP(UINT32_C(0x002cf02c)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cf030));goto dispatch;
L_002cf030:
 STEP(UINT32_C(0x002cf030)); /* 24579740 addiu s7,v0,-26816 */
 set(m,23u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cf034));goto dispatch;
L_002cf034:
 STEP(UINT32_C(0x002cf034)); /* 8ee30024 lw v1,0x24(s7) */
 READ((uint32_t)lo(m,23u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cf038));goto dispatch;
L_002cf038:
 STEP(UINT32_C(0x002cf038)); /* 14600005 bne v1,zero,002cf050 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cf03c));/* nop */target=sx(taken?UINT32_C(0x002cf050):UINT32_C(0x002cf040));goto dispatch;}
L_002cf03c:
 STEP(UINT32_C(0x002cf03c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cf040));goto dispatch;
L_002cf040:
 STEP(UINT32_C(0x002cf040)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf048));STEP(UINT32_C(0x002cf044));READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf044:
 STEP(UINT32_C(0x002cf044)); /* 8e84bb24 lw a0,-0x44dc(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf048));goto dispatch;
L_002cf048:
 STEP(UINT32_C(0x002cf048)); /* 1000004e beq zero,zero,002cf184 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf04c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002cf184):UINT32_C(0x002cf050));goto dispatch;}
L_002cf04c:
 STEP(UINT32_C(0x002cf04c)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cf050));goto dispatch;
L_002cf050:
 STEP(UINT32_C(0x002cf050)); /* 12400004 beq s2,zero,002cf064 */
 {int taken=(lo(m,18u)==lo(m,0u));STEP(UINT32_C(0x002cf054));/* nop */target=sx(taken?UINT32_C(0x002cf064):UINT32_C(0x002cf058));goto dispatch;}
L_002cf054:
 STEP(UINT32_C(0x002cf054)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cf058));goto dispatch;
L_002cf058:
 STEP(UINT32_C(0x002cf058)); /* 82420000 lb v0,0x0(s2) */
 {uint8_t byte;READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002cf05c));goto dispatch;
L_002cf05c:
 STEP(UINT32_C(0x002cf05c)); /* 14400005 bne v0,zero,002cf074 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cf060));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cf074):UINT32_C(0x002cf064));goto dispatch;}
L_002cf060:
 STEP(UINT32_C(0x002cf060)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf064));goto dispatch;
L_002cf064:
 STEP(UINT32_C(0x002cf064)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf06c));STEP(UINT32_C(0x002cf068));READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf068:
 STEP(UINT32_C(0x002cf068)); /* 8e84bb24 lw a0,-0x44dc(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf06c));goto dispatch;
L_002cf06c:
 STEP(UINT32_C(0x002cf06c)); /* 10000045 beq zero,zero,002cf184 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf070));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(taken?UINT32_C(0x002cf184):UINT32_C(0x002cf074));goto dispatch;}
L_002cf070:
 STEP(UINT32_C(0x002cf070)); /* 2402ff2e addiu v0,zero,-210 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(UINT32_C(0x002cf074));goto dispatch;
L_002cf074:
 STEP(UINT32_C(0x002cf074)); /* 32310007 andi s1,s1,0x7 */
 set(m,17u,lo(m,17u) & UINT64_C(0x7));target=sx(UINT32_C(0x002cf078));goto dispatch;
L_002cf078:
 STEP(UINT32_C(0x002cf078)); /* 245097f0 addiu s0,v0,-26640 */
 set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0)));target=sx(UINT32_C(0x002cf07c));goto dispatch;
L_002cf07c:
 STEP(UINT32_C(0x002cf07c)); /* ac5597f0 sw s5,-0x6810(v0) */
 value32=(uint32_t)lo(m,21u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0),&value32,4u);target=sx(UINT32_C(0x002cf080));goto dispatch;
L_002cf080:
 STEP(UINT32_C(0x002cf080)); /* ae130004 sw s3,0x4(s0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002cf084));goto dispatch;
L_002cf084:
 STEP(UINT32_C(0x002cf084)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf088));goto dispatch;
L_002cf088:
 STEP(UINT32_C(0x002cf088)); /* ae110008 sw s1,0x8(s0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002cf08c));goto dispatch;
L_002cf08c:
 STEP(UINT32_C(0x002cf08c)); /* 24439780 addiu v1,v0,-26752 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9780)));target=sx(UINT32_C(0x002cf090));goto dispatch;
L_002cf090:
 STEP(UINT32_C(0x002cf090)); /* 26040014 addiu a0,s0,20 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002cf094));goto dispatch;
L_002cf094:
 STEP(UINT32_C(0x002cf094)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002cf098));goto dispatch;
L_002cf098:
 STEP(UINT32_C(0x002cf098)); /* 24499780 addiu t1,v0,-26752 */
 set(m,9u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9780)));target=sx(UINT32_C(0x002cf09c));goto dispatch;
L_002cf09c:
 STEP(UINT32_C(0x002cf09c)); /* 6ac60007 ldl a2,0x7(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000007);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002cf0a0));goto dispatch;
L_002cf0a0:
 STEP(UINT32_C(0x002cf0a0)); /* 6ec60000 ldr a2,0x0(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000000);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002cf0a4));goto dispatch;
L_002cf0a4:
 STEP(UINT32_C(0x002cf0a4)); /* 6ac7000f ldl a3,0xf(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x0000000f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002cf0a8));goto dispatch;
L_002cf0a8:
 STEP(UINT32_C(0x002cf0a8)); /* 6ec70008 ldr a3,0x8(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000008);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002cf0ac));goto dispatch;
L_002cf0ac:
 STEP(UINT32_C(0x002cf0ac)); /* 6ac80017 ldl t0,0x17(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000017);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,8u,(lo(m,8u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002cf0b0));goto dispatch;
L_002cf0b0:
 STEP(UINT32_C(0x002cf0b0)); /* 6ec80010 ldr t0,0x10(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000010);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,8u,(lo(m,8u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002cf0b4));goto dispatch;
L_002cf0b4:
 STEP(UINT32_C(0x002cf0b4)); /* b1260007 sdl a2,0x7(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000007);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,6u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0b8));goto dispatch;
L_002cf0b8:
 STEP(UINT32_C(0x002cf0b8)); /* b5260000 sdr a2,0x0(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000000);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,6u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0bc));goto dispatch;
L_002cf0bc:
 STEP(UINT32_C(0x002cf0bc)); /* b127000f sdl a3,0xf(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x0000000f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,7u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0c0));goto dispatch;
L_002cf0c0:
 STEP(UINT32_C(0x002cf0c0)); /* b5270008 sdr a3,0x8(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000008);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,7u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0c4));goto dispatch;
L_002cf0c4:
 STEP(UINT32_C(0x002cf0c4)); /* b1280017 sdl t0,0x17(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000017);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,8u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0c8));goto dispatch;
L_002cf0c8:
 STEP(UINT32_C(0x002cf0c8)); /* b5280010 sdr t0,0x10(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000010);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,8u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0cc));goto dispatch;
L_002cf0cc:
 STEP(UINT32_C(0x002cf0cc)); /* 6ac6001f ldl a2,0x1f(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x0000001f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002cf0d0));goto dispatch;
L_002cf0d0:
 STEP(UINT32_C(0x002cf0d0)); /* 6ec60018 ldr a2,0x18(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000018);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002cf0d4));goto dispatch;
L_002cf0d4:
 STEP(UINT32_C(0x002cf0d4)); /* 6ac70027 ldl a3,0x27(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000027);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002cf0d8));goto dispatch;
L_002cf0d8:
 STEP(UINT32_C(0x002cf0d8)); /* 6ec70020 ldr a3,0x20(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000020);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002cf0dc));goto dispatch;
L_002cf0dc:
 STEP(UINT32_C(0x002cf0dc)); /* 6ac8002f ldl t0,0x2f(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x0000002f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,8u,(lo(m,8u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002cf0e0));goto dispatch;
L_002cf0e0:
 STEP(UINT32_C(0x002cf0e0)); /* 6ec80028 ldr t0,0x28(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000028);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,8u,(lo(m,8u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002cf0e4));goto dispatch;
L_002cf0e4:
 STEP(UINT32_C(0x002cf0e4)); /* b126001f sdl a2,0x1f(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x0000001f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,6u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0e8));goto dispatch;
L_002cf0e8:
 STEP(UINT32_C(0x002cf0e8)); /* b5260018 sdr a2,0x18(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000018);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,6u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0ec));goto dispatch;
L_002cf0ec:
 STEP(UINT32_C(0x002cf0ec)); /* b1270027 sdl a3,0x27(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000027);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,7u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0f0));goto dispatch;
L_002cf0f0:
 STEP(UINT32_C(0x002cf0f0)); /* b5270020 sdr a3,0x20(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000020);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,7u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0f4));goto dispatch;
L_002cf0f4:
 STEP(UINT32_C(0x002cf0f4)); /* b128002f sdl t0,0x2f(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x0000002f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,8u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0f8));goto dispatch;
L_002cf0f8:
 STEP(UINT32_C(0x002cf0f8)); /* b5280028 sdr t0,0x28(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000028);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,8u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf0fc));goto dispatch;
L_002cf0fc:
 STEP(UINT32_C(0x002cf0fc)); /* 6ac60037 ldl a2,0x37(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000037);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002cf100));goto dispatch;
L_002cf100:
 STEP(UINT32_C(0x002cf100)); /* 6ec60030 ldr a2,0x30(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000030);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002cf104));goto dispatch;
L_002cf104:
 STEP(UINT32_C(0x002cf104)); /* 6ac7003f ldl a3,0x3f(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x0000003f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002cf108));goto dispatch;
L_002cf108:
 STEP(UINT32_C(0x002cf108)); /* 6ec70038 ldr a3,0x38(s6) */
 {uint32_t effective=(uint32_t)lo(m,22u)+UINT32_C(0x00000038);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002cf10c));goto dispatch;
L_002cf10c:
 STEP(UINT32_C(0x002cf10c)); /* b1260037 sdl a2,0x37(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000037);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,6u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf110));goto dispatch;
L_002cf110:
 STEP(UINT32_C(0x002cf110)); /* b5260030 sdr a2,0x30(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000030);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,6u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf114));goto dispatch;
L_002cf114:
 STEP(UINT32_C(0x002cf114)); /* b127003f sdl a3,0x3f(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x0000003f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,7u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf118));goto dispatch;
L_002cf118:
 STEP(UINT32_C(0x002cf118)); /* b5270038 sdr a3,0x38(t1) */
 {uint32_t effective=(uint32_t)lo(m,9u)+UINT32_C(0x00000038);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,7u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002cf11c));goto dispatch;
L_002cf11c:
 STEP(UINT32_C(0x002cf11c)); /* ae030010 sw v1,0x10(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002cf120));goto dispatch;
L_002cf120:
 STEP(UINT32_C(0x002cf120)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002cf128));STEP(UINT32_C(0x002cf124));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002cf124:
 STEP(UINT32_C(0x002cf124)); /* 240603ff addiu a2,zero,1023 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002cf128));goto dispatch;
L_002cf128:
 STEP(UINT32_C(0x002cf128)); /* a2000413 sb zero,0x413(s0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000413),&byte,1u);}target=sx(UINT32_C(0x002cf12c));goto dispatch;
L_002cf12c:
 STEP(UINT32_C(0x002cf12c)); /* 0c0b7048 jal 002dc120 */
 set(m,31u,UINT64_C(0x002cf134));STEP(UINT32_C(0x002cf130));set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dc120));goto dispatch;
L_002cf130:
 STEP(UINT32_C(0x002cf130)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cf134));goto dispatch;
L_002cf134:
 STEP(UINT32_C(0x002cf134)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf138));goto dispatch;
L_002cf138:
 STEP(UINT32_C(0x002cf138)); /* 0200382d daddu a3,s0,zero */
 set(m,7u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf13c));goto dispatch;
L_002cf13c:
 STEP(UINT32_C(0x002cf13c)); /* 02e0202d daddu a0,s7,zero */
 set(m,4u,lo(m,23u)+lo(m,0u));target=sx(UINT32_C(0x002cf140));goto dispatch;
L_002cf140:
 STEP(UINT32_C(0x002cf140)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cf144));goto dispatch;
L_002cf144:
 STEP(UINT32_C(0x002cf144)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cf148));goto dispatch;
L_002cf148:
 STEP(UINT32_C(0x002cf148)); /* 2405000e addiu a1,zero,14 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000e)));target=sx(UINT32_C(0x002cf14c));goto dispatch;
L_002cf14c:
 STEP(UINT32_C(0x002cf14c)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cf150));goto dispatch;
L_002cf150:
 STEP(UINT32_C(0x002cf150)); /* 24080414 addiu t0,zero,1044 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000414)));target=sx(UINT32_C(0x002cf154));goto dispatch;
L_002cf154:
 STEP(UINT32_C(0x002cf154)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cf158));goto dispatch;
L_002cf158:
 STEP(UINT32_C(0x002cf158)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cf160));STEP(UINT32_C(0x002cf15c));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cf15c:
 STEP(UINT32_C(0x002cf15c)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cf160));goto dispatch;
L_002cf160:
 STEP(UINT32_C(0x002cf160)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cf164));goto dispatch;
L_002cf164:
 STEP(UINT32_C(0x002cf164)); /* 16000004 bne s0,zero,002cf178 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cf168));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002cf178):UINT32_C(0x002cf16c));goto dispatch;}
L_002cf168:
 STEP(UINT32_C(0x002cf168)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cf16c));goto dispatch;
L_002cf16c:
 STEP(UINT32_C(0x002cf16c)); /* 2402000e addiu v0,zero,14 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000e)));target=sx(UINT32_C(0x002cf170));goto dispatch;
L_002cf170:
 STEP(UINT32_C(0x002cf170)); /* 10000003 beq zero,zero,002cf180 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf174));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002cf180):UINT32_C(0x002cf178));goto dispatch;}
L_002cf174:
 STEP(UINT32_C(0x002cf174)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002cf178));goto dispatch;
L_002cf178:
 STEP(UINT32_C(0x002cf178)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf180));STEP(UINT32_C(0x002cf17c));READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf17c:
 STEP(UINT32_C(0x002cf17c)); /* 8e84bb24 lw a0,-0x44dc(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf180));goto dispatch;
L_002cf180:
 STEP(UINT32_C(0x002cf180)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf184));goto dispatch;
L_002cf184:
 STEP(UINT32_C(0x002cf184)); /* dfbf0090 ld ra,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cf188));goto dispatch;
L_002cf188:
 STEP(UINT32_C(0x002cf188)); /* dfb70080 ld s7,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,23u,value64);target=sx(UINT32_C(0x002cf18c));goto dispatch;
L_002cf18c:
 STEP(UINT32_C(0x002cf18c)); /* dfb60070 ld s6,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002cf190));goto dispatch;
L_002cf190:
 STEP(UINT32_C(0x002cf190)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002cf194));goto dispatch;
L_002cf194:
 STEP(UINT32_C(0x002cf194)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002cf198));goto dispatch;
L_002cf198:
 STEP(UINT32_C(0x002cf198)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002cf19c));goto dispatch;
L_002cf19c:
 STEP(UINT32_C(0x002cf19c)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cf1a0));goto dispatch;
L_002cf1a0:
 STEP(UINT32_C(0x002cf1a0)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cf1a4));goto dispatch;
L_002cf1a4:
 STEP(UINT32_C(0x002cf1a4)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cf1a8));goto dispatch;
L_002cf1a8:
 STEP(UINT32_C(0x002cf1a8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cf1ac));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));goto dispatch;
L_002cf1ac:
 STEP(UINT32_C(0x002cf1ac)); /* 27bd00a0 addiu sp,sp,160 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000a0)));target=sx(UINT32_C(0x002cf1b0));goto dispatch;
L_002cf1b0:
 STEP(UINT32_C(0x002cf1b0)); /* 27bdff70 addiu sp,sp,-144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff70)));target=sx(UINT32_C(0x002cf1b4));goto dispatch;
L_002cf1b4:
 STEP(UINT32_C(0x002cf1b4)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002cf1b8));goto dispatch;
L_002cf1b8:
 STEP(UINT32_C(0x002cf1b8)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002cf1bc));goto dispatch;
L_002cf1bc:
 STEP(UINT32_C(0x002cf1bc)); /* 3c150053 lui s5,zero,0x53 */
 set(m,21u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cf1c0));goto dispatch;
L_002cf1c0:
 STEP(UINT32_C(0x002cf1c0)); /* 0080a02d daddu s4,a0,zero */
 set(m,20u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cf1c4));goto dispatch;
L_002cf1c4:
 STEP(UINT32_C(0x002cf1c4)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cf1c8));goto dispatch;
L_002cf1c8:
 STEP(UINT32_C(0x002cf1c8)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cf1cc));goto dispatch;
L_002cf1cc:
 STEP(UINT32_C(0x002cf1cc)); /* 00a0982d daddu s3,a1,zero */
 set(m,19u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002cf1d0));goto dispatch;
L_002cf1d0:
 STEP(UINT32_C(0x002cf1d0)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cf1d4));goto dispatch;
L_002cf1d4:
 STEP(UINT32_C(0x002cf1d4)); /* 00e0902d daddu s2,a3,zero */
 set(m,18u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002cf1d8));goto dispatch;
L_002cf1d8:
 STEP(UINT32_C(0x002cf1d8)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf1dc));goto dispatch;
L_002cf1dc:
 STEP(UINT32_C(0x002cf1dc)); /* 00c0802d daddu s0,a2,zero */
 set(m,16u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002cf1e0));goto dispatch;
L_002cf1e0:
 STEP(UINT32_C(0x002cf1e0)); /* ffbf0080 sd ra,0x80(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);target=sx(UINT32_C(0x002cf1e4));goto dispatch;
L_002cf1e4:
 STEP(UINT32_C(0x002cf1e4)); /* ffb60070 sd s6,0x70(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002cf1e8));goto dispatch;
L_002cf1e8:
 STEP(UINT32_C(0x002cf1e8)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cf1f0));STEP(UINT32_C(0x002cf1ec));value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cf1ec:
 STEP(UINT32_C(0x002cf1ec)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cf1f0));goto dispatch;
L_002cf1f0:
 STEP(UINT32_C(0x002cf1f0)); /* 04410003 regimm1 v0,002cf200 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cf1f4));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cf200):UINT32_C(0x002cf1f8));goto dispatch;}
L_002cf1f4:
 STEP(UINT32_C(0x002cf1f4)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf1f8));goto dispatch;
L_002cf1f8:
 STEP(UINT32_C(0x002cf1f8)); /* 1000003d beq zero,zero,002cf2f0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf1fc));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002cf2f0):UINT32_C(0x002cf200));goto dispatch;}
L_002cf1fc:
 STEP(UINT32_C(0x002cf1fc)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cf200));goto dispatch;
L_002cf200:
 STEP(UINT32_C(0x002cf200)); /* 24569740 addiu s6,v0,-26816 */
 set(m,22u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cf204));goto dispatch;
L_002cf204:
 STEP(UINT32_C(0x002cf204)); /* 8ec30024 lw v1,0x24(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cf208));goto dispatch;
L_002cf208:
 STEP(UINT32_C(0x002cf208)); /* 14600005 bne v1,zero,002cf220 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cf20c));/* nop */target=sx(taken?UINT32_C(0x002cf220):UINT32_C(0x002cf210));goto dispatch;}
L_002cf20c:
 STEP(UINT32_C(0x002cf20c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cf210));goto dispatch;
L_002cf210:
 STEP(UINT32_C(0x002cf210)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf218));STEP(UINT32_C(0x002cf214));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf214:
 STEP(UINT32_C(0x002cf214)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf218));goto dispatch;
L_002cf218:
 STEP(UINT32_C(0x002cf218)); /* 10000035 beq zero,zero,002cf2f0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf21c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002cf2f0):UINT32_C(0x002cf220));goto dispatch;}
L_002cf21c:
 STEP(UINT32_C(0x002cf21c)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cf220));goto dispatch;
L_002cf220:
 STEP(UINT32_C(0x002cf220)); /* 12000006 beq s0,zero,002cf23c */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002cf224));/* nop */target=sx(taken?UINT32_C(0x002cf23c):UINT32_C(0x002cf228));goto dispatch;}
L_002cf224:
 STEP(UINT32_C(0x002cf224)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cf228));goto dispatch;
L_002cf228:
 STEP(UINT32_C(0x002cf228)); /* 82020000 lb v0,0x0(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002cf22c));goto dispatch;
L_002cf22c:
 STEP(UINT32_C(0x002cf22c)); /* 10400003 beq v0,zero,002cf23c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002cf230));/* nop */target=sx(taken?UINT32_C(0x002cf23c):UINT32_C(0x002cf234));goto dispatch;}
L_002cf230:
 STEP(UINT32_C(0x002cf230)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cf234));goto dispatch;
L_002cf234:
 STEP(UINT32_C(0x002cf234)); /* 16400005 bne s2,zero,002cf24c */
 {int taken=(lo(m,18u)!=lo(m,0u));STEP(UINT32_C(0x002cf238));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cf24c):UINT32_C(0x002cf23c));goto dispatch;}
L_002cf238:
 STEP(UINT32_C(0x002cf238)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf23c));goto dispatch;
L_002cf23c:
 STEP(UINT32_C(0x002cf23c)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf244));STEP(UINT32_C(0x002cf240));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf240:
 STEP(UINT32_C(0x002cf240)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf244));goto dispatch;
L_002cf244:
 STEP(UINT32_C(0x002cf244)); /* 1000002a beq zero,zero,002cf2f0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf248));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(taken?UINT32_C(0x002cf2f0):UINT32_C(0x002cf24c));goto dispatch;}
L_002cf248:
 STEP(UINT32_C(0x002cf248)); /* 2402ff2e addiu v0,zero,-210 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(UINT32_C(0x002cf24c));goto dispatch;
L_002cf24c:
 STEP(UINT32_C(0x002cf24c)); /* 24030010 addiu v1,zero,16 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002cf250));goto dispatch;
L_002cf250:
 STEP(UINT32_C(0x002cf250)); /* 245197f0 addiu s1,v0,-26640 */
 set(m,17u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0)));target=sx(UINT32_C(0x002cf254));goto dispatch;
L_002cf254:
 STEP(UINT32_C(0x002cf254)); /* ac5497f0 sw s4,-0x6810(v0) */
 value32=(uint32_t)lo(m,20u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0),&value32,4u);target=sx(UINT32_C(0x002cf258));goto dispatch;
L_002cf258:
 STEP(UINT32_C(0x002cf258)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf25c));goto dispatch;
L_002cf25c:
 STEP(UINT32_C(0x002cf25c)); /* ae330004 sw s3,0x4(s1) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002cf260));goto dispatch;
L_002cf260:
 STEP(UINT32_C(0x002cf260)); /* ae230008 sw v1,0x8(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002cf264));goto dispatch;
L_002cf264:
 STEP(UINT32_C(0x002cf264)); /* 26240014 addiu a0,s1,20 */
 set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002cf268));goto dispatch;
L_002cf268:
 STEP(UINT32_C(0x002cf268)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002cf270));STEP(UINT32_C(0x002cf26c));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002cf26c:
 STEP(UINT32_C(0x002cf26c)); /* 240603ff addiu a2,zero,1023 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002cf270));goto dispatch;
L_002cf270:
 STEP(UINT32_C(0x002cf270)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf274));goto dispatch;
L_002cf274:
 STEP(UINT32_C(0x002cf274)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002cf278));goto dispatch;
L_002cf278:
 STEP(UINT32_C(0x002cf278)); /* 261097a0 addiu s0,s0,-26720 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffff97a0)));target=sx(UINT32_C(0x002cf27c));goto dispatch;
L_002cf27c:
 STEP(UINT32_C(0x002cf27c)); /* a2200413 sb zero,0x413(s1) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000413),&byte,1u);}target=sx(UINT32_C(0x002cf280));goto dispatch;
L_002cf280:
 STEP(UINT32_C(0x002cf280)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf284));goto dispatch;
L_002cf284:
 STEP(UINT32_C(0x002cf284)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002cf28c));STEP(UINT32_C(0x002cf288));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002cf288:
 STEP(UINT32_C(0x002cf288)); /* 24060020 addiu a2,zero,32 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002cf28c));goto dispatch;
L_002cf28c:
 STEP(UINT32_C(0x002cf28c)); /* 2610ffe0 addiu s0,s0,-32 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002cf290));goto dispatch;
L_002cf290:
 STEP(UINT32_C(0x002cf290)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cf294));goto dispatch;
L_002cf294:
 STEP(UINT32_C(0x002cf294)); /* ae300010 sw s0,0x10(s1) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002cf298));goto dispatch;
L_002cf298:
 STEP(UINT32_C(0x002cf298)); /* 0c0b7048 jal 002dc120 */
 set(m,31u,UINT64_C(0x002cf2a0));STEP(UINT32_C(0x002cf29c));{uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000003f),&byte,1u);}target=sx(UINT32_C(0x002dc120));goto dispatch;
L_002cf29c:
 STEP(UINT32_C(0x002cf29c)); /* a200003f sb zero,0x3f(s0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000003f),&byte,1u);}target=sx(UINT32_C(0x002cf2a0));goto dispatch;
L_002cf2a0:
 STEP(UINT32_C(0x002cf2a0)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf2a4));goto dispatch;
L_002cf2a4:
 STEP(UINT32_C(0x002cf2a4)); /* 02c0202d daddu a0,s6,zero */
 set(m,4u,lo(m,22u)+lo(m,0u));target=sx(UINT32_C(0x002cf2a8));goto dispatch;
L_002cf2a8:
 STEP(UINT32_C(0x002cf2a8)); /* 0220382d daddu a3,s1,zero */
 set(m,7u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002cf2ac));goto dispatch;
L_002cf2ac:
 STEP(UINT32_C(0x002cf2ac)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cf2b0));goto dispatch;
L_002cf2b0:
 STEP(UINT32_C(0x002cf2b0)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cf2b4));goto dispatch;
L_002cf2b4:
 STEP(UINT32_C(0x002cf2b4)); /* 2405000e addiu a1,zero,14 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000e)));target=sx(UINT32_C(0x002cf2b8));goto dispatch;
L_002cf2b8:
 STEP(UINT32_C(0x002cf2b8)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cf2bc));goto dispatch;
L_002cf2bc:
 STEP(UINT32_C(0x002cf2bc)); /* 24080414 addiu t0,zero,1044 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000414)));target=sx(UINT32_C(0x002cf2c0));goto dispatch;
L_002cf2c0:
 STEP(UINT32_C(0x002cf2c0)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cf2c4));goto dispatch;
L_002cf2c4:
 STEP(UINT32_C(0x002cf2c4)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cf2cc));STEP(UINT32_C(0x002cf2c8));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cf2c8:
 STEP(UINT32_C(0x002cf2c8)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cf2cc));goto dispatch;
L_002cf2cc:
 STEP(UINT32_C(0x002cf2cc)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cf2d0));goto dispatch;
L_002cf2d0:
 STEP(UINT32_C(0x002cf2d0)); /* 16000004 bne s0,zero,002cf2e4 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cf2d4));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002cf2e4):UINT32_C(0x002cf2d8));goto dispatch;}
L_002cf2d4:
 STEP(UINT32_C(0x002cf2d4)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cf2d8));goto dispatch;
L_002cf2d8:
 STEP(UINT32_C(0x002cf2d8)); /* 24020013 addiu v0,zero,19 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000013)));target=sx(UINT32_C(0x002cf2dc));goto dispatch;
L_002cf2dc:
 STEP(UINT32_C(0x002cf2dc)); /* 10000003 beq zero,zero,002cf2ec */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf2e0));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002cf2ec):UINT32_C(0x002cf2e4));goto dispatch;}
L_002cf2e0:
 STEP(UINT32_C(0x002cf2e0)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002cf2e4));goto dispatch;
L_002cf2e4:
 STEP(UINT32_C(0x002cf2e4)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf2ec));STEP(UINT32_C(0x002cf2e8));READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf2e8:
 STEP(UINT32_C(0x002cf2e8)); /* 8ea4bb24 lw a0,-0x44dc(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf2ec));goto dispatch;
L_002cf2ec:
 STEP(UINT32_C(0x002cf2ec)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf2f0));goto dispatch;
L_002cf2f0:
 STEP(UINT32_C(0x002cf2f0)); /* dfbf0080 ld ra,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cf2f4));goto dispatch;
L_002cf2f4:
 STEP(UINT32_C(0x002cf2f4)); /* dfb60070 ld s6,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x002cf2f8));goto dispatch;
L_002cf2f8:
 STEP(UINT32_C(0x002cf2f8)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002cf2fc));goto dispatch;
L_002cf2fc:
 STEP(UINT32_C(0x002cf2fc)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002cf300));goto dispatch;
L_002cf300:
 STEP(UINT32_C(0x002cf300)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002cf304));goto dispatch;
L_002cf304:
 STEP(UINT32_C(0x002cf304)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cf308));goto dispatch;
L_002cf308:
 STEP(UINT32_C(0x002cf308)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cf30c));goto dispatch;
L_002cf30c:
 STEP(UINT32_C(0x002cf30c)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cf310));goto dispatch;
L_002cf310:
 STEP(UINT32_C(0x002cf310)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cf314));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));goto dispatch;
L_002cf314:
 STEP(UINT32_C(0x002cf314)); /* 27bd0090 addiu sp,sp,144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));target=sx(UINT32_C(0x002cf318));goto dispatch;
L_002cf318:
 STEP(UINT32_C(0x002cf318)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x002cf31c));goto dispatch;
L_002cf31c:
 STEP(UINT32_C(0x002cf31c)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cf320));goto dispatch;
L_002cf320:
 STEP(UINT32_C(0x002cf320)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cf324));goto dispatch;
L_002cf324:
 STEP(UINT32_C(0x002cf324)); /* 0080902d daddu s2,a0,zero */
 set(m,18u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cf328));goto dispatch;
L_002cf328:
 STEP(UINT32_C(0x002cf328)); /* 3c110053 lui s1,zero,0x53 */
 set(m,17u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cf32c));goto dispatch;
L_002cf32c:
 STEP(UINT32_C(0x002cf32c)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cf330));goto dispatch;
L_002cf330:
 STEP(UINT32_C(0x002cf330)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf334));goto dispatch;
L_002cf334:
 STEP(UINT32_C(0x002cf334)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cf338));goto dispatch;
L_002cf338:
 STEP(UINT32_C(0x002cf338)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cf340));STEP(UINT32_C(0x002cf33c));set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cf33c:
 STEP(UINT32_C(0x002cf33c)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002cf340));goto dispatch;
L_002cf340:
 STEP(UINT32_C(0x002cf340)); /* 04410003 regimm1 v0,002cf350 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cf344));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cf350):UINT32_C(0x002cf348));goto dispatch;}
L_002cf344:
 STEP(UINT32_C(0x002cf344)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf348));goto dispatch;
L_002cf348:
 STEP(UINT32_C(0x002cf348)); /* 1000001f beq zero,zero,002cf3c8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf34c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002cf3c8):UINT32_C(0x002cf350));goto dispatch;}
L_002cf34c:
 STEP(UINT32_C(0x002cf34c)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cf350));goto dispatch;
L_002cf350:
 STEP(UINT32_C(0x002cf350)); /* 24449740 addiu a0,v0,-26816 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cf354));goto dispatch;
L_002cf354:
 STEP(UINT32_C(0x002cf354)); /* 8c830024 lw v1,0x24(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cf358));goto dispatch;
L_002cf358:
 STEP(UINT32_C(0x002cf358)); /* 14600005 bne v1,zero,002cf370 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cf35c));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cf370):UINT32_C(0x002cf360));goto dispatch;}
L_002cf35c:
 STEP(UINT32_C(0x002cf35c)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf360));goto dispatch;
L_002cf360:
 STEP(UINT32_C(0x002cf360)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf368));STEP(UINT32_C(0x002cf364));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf364:
 STEP(UINT32_C(0x002cf364)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf368));goto dispatch;
L_002cf368:
 STEP(UINT32_C(0x002cf368)); /* 10000017 beq zero,zero,002cf3c8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf36c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002cf3c8):UINT32_C(0x002cf370));goto dispatch;}
L_002cf36c:
 STEP(UINT32_C(0x002cf36c)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cf370));goto dispatch;
L_002cf370:
 STEP(UINT32_C(0x002cf370)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf374));goto dispatch;
L_002cf374:
 STEP(UINT32_C(0x002cf374)); /* 244297c0 addiu v0,v0,-26688 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97c0)));target=sx(UINT32_C(0x002cf378));goto dispatch;
L_002cf378:
 STEP(UINT32_C(0x002cf378)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cf37c));goto dispatch;
L_002cf37c:
 STEP(UINT32_C(0x002cf37c)); /* ac500008 sw s0,0x8(v0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002cf380));goto dispatch;
L_002cf380:
 STEP(UINT32_C(0x002cf380)); /* 0040382d daddu a3,v0,zero */
 set(m,7u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cf384));goto dispatch;
L_002cf384:
 STEP(UINT32_C(0x002cf384)); /* ac520004 sw s2,0x4(v0) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002cf388));goto dispatch;
L_002cf388:
 STEP(UINT32_C(0x002cf388)); /* 24050011 addiu a1,zero,17 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000011)));target=sx(UINT32_C(0x002cf38c));goto dispatch;
L_002cf38c:
 STEP(UINT32_C(0x002cf38c)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cf390));goto dispatch;
L_002cf390:
 STEP(UINT32_C(0x002cf390)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cf394));goto dispatch;
L_002cf394:
 STEP(UINT32_C(0x002cf394)); /* 24080030 addiu t0,zero,48 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002cf398));goto dispatch;
L_002cf398:
 STEP(UINT32_C(0x002cf398)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cf39c));goto dispatch;
L_002cf39c:
 STEP(UINT32_C(0x002cf39c)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cf3a4));STEP(UINT32_C(0x002cf3a0));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cf3a0:
 STEP(UINT32_C(0x002cf3a0)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cf3a4));goto dispatch;
L_002cf3a4:
 STEP(UINT32_C(0x002cf3a4)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cf3a8));goto dispatch;
L_002cf3a8:
 STEP(UINT32_C(0x002cf3a8)); /* 16000004 bne s0,zero,002cf3bc */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cf3ac));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002cf3bc):UINT32_C(0x002cf3b0));goto dispatch;}
L_002cf3ac:
 STEP(UINT32_C(0x002cf3ac)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cf3b0));goto dispatch;
L_002cf3b0:
 STEP(UINT32_C(0x002cf3b0)); /* 24020011 addiu v0,zero,17 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000011)));target=sx(UINT32_C(0x002cf3b4));goto dispatch;
L_002cf3b4:
 STEP(UINT32_C(0x002cf3b4)); /* 10000003 beq zero,zero,002cf3c4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf3b8));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002cf3c4):UINT32_C(0x002cf3bc));goto dispatch;}
L_002cf3b8:
 STEP(UINT32_C(0x002cf3b8)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002cf3bc));goto dispatch;
L_002cf3bc:
 STEP(UINT32_C(0x002cf3bc)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf3c4));STEP(UINT32_C(0x002cf3c0));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf3c0:
 STEP(UINT32_C(0x002cf3c0)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf3c4));goto dispatch;
L_002cf3c4:
 STEP(UINT32_C(0x002cf3c4)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf3c8));goto dispatch;
L_002cf3c8:
 STEP(UINT32_C(0x002cf3c8)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cf3cc));goto dispatch;
L_002cf3cc:
 STEP(UINT32_C(0x002cf3cc)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cf3d0));goto dispatch;
L_002cf3d0:
 STEP(UINT32_C(0x002cf3d0)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cf3d4));goto dispatch;
L_002cf3d4:
 STEP(UINT32_C(0x002cf3d4)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cf3d8));goto dispatch;
L_002cf3d8:
 STEP(UINT32_C(0x002cf3d8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cf3dc));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_002cf3dc:
 STEP(UINT32_C(0x002cf3dc)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x002cf3e0));goto dispatch;
L_002cf3e0:
 STEP(UINT32_C(0x002cf3e0)); /* 27bdff90 addiu sp,sp,-112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff90)));target=sx(UINT32_C(0x002cf3e4));goto dispatch;
L_002cf3e4:
 STEP(UINT32_C(0x002cf3e4)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002cf3e8));goto dispatch;
L_002cf3e8:
 STEP(UINT32_C(0x002cf3e8)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002cf3ec));goto dispatch;
L_002cf3ec:
 STEP(UINT32_C(0x002cf3ec)); /* 0080982d daddu s3,a0,zero */
 set(m,19u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002cf3f0));goto dispatch;
L_002cf3f0:
 STEP(UINT32_C(0x002cf3f0)); /* 3c110053 lui s1,zero,0x53 */
 set(m,17u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cf3f4));goto dispatch;
L_002cf3f4:
 STEP(UINT32_C(0x002cf3f4)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002cf3f8));goto dispatch;
L_002cf3f8:
 STEP(UINT32_C(0x002cf3f8)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002cf3fc));goto dispatch;
L_002cf3fc:
 STEP(UINT32_C(0x002cf3fc)); /* 00a0902d daddu s2,a1,zero */
 set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002cf400));goto dispatch;
L_002cf400:
 STEP(UINT32_C(0x002cf400)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf404));goto dispatch;
L_002cf404:
 STEP(UINT32_C(0x002cf404)); /* 00c0802d daddu s0,a2,zero */
 set(m,16u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002cf408));goto dispatch;
L_002cf408:
 STEP(UINT32_C(0x002cf408)); /* ffbf0060 sd ra,0x60(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002cf40c));goto dispatch;
L_002cf40c:
 STEP(UINT32_C(0x002cf40c)); /* 0c0b6fbc jal 002dbef0 */
 set(m,31u,UINT64_C(0x002cf414));STEP(UINT32_C(0x002cf410));value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002dbef0));goto dispatch;
L_002cf410:
 STEP(UINT32_C(0x002cf410)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002cf414));goto dispatch;
L_002cf414:
 STEP(UINT32_C(0x002cf414)); /* 04410003 regimm1 v0,002cf424 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002cf418));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cf424):UINT32_C(0x002cf41c));goto dispatch;}
L_002cf418:
 STEP(UINT32_C(0x002cf418)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf41c));goto dispatch;
L_002cf41c:
 STEP(UINT32_C(0x002cf41c)); /* 1000002e beq zero,zero,002cf4d8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf420));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(taken?UINT32_C(0x002cf4d8):UINT32_C(0x002cf424));goto dispatch;}
L_002cf420:
 STEP(UINT32_C(0x002cf420)); /* 2402ff38 addiu v0,zero,-200 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff38)));target=sx(UINT32_C(0x002cf424));goto dispatch;
L_002cf424:
 STEP(UINT32_C(0x002cf424)); /* 24549740 addiu s4,v0,-26816 */
 set(m,20u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9740)));target=sx(UINT32_C(0x002cf428));goto dispatch;
L_002cf428:
 STEP(UINT32_C(0x002cf428)); /* 8e830024 lw v1,0x24(s4) */
 READ((uint32_t)lo(m,20u)+UINT32_C(0x00000024),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002cf42c));goto dispatch;
L_002cf42c:
 STEP(UINT32_C(0x002cf42c)); /* 14600005 bne v1,zero,002cf444 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002cf430));/* nop */target=sx(taken?UINT32_C(0x002cf444):UINT32_C(0x002cf434));goto dispatch;}
L_002cf430:
 STEP(UINT32_C(0x002cf430)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cf434));goto dispatch;
L_002cf434:
 STEP(UINT32_C(0x002cf434)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf43c));STEP(UINT32_C(0x002cf438));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf438:
 STEP(UINT32_C(0x002cf438)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf43c));goto dispatch;
L_002cf43c:
 STEP(UINT32_C(0x002cf43c)); /* 10000026 beq zero,zero,002cf4d8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf440));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(taken?UINT32_C(0x002cf4d8):UINT32_C(0x002cf444));goto dispatch;}
L_002cf440:
 STEP(UINT32_C(0x002cf440)); /* 2402ff9c addiu v0,zero,-100 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff9c)));target=sx(UINT32_C(0x002cf444));goto dispatch;
L_002cf444:
 STEP(UINT32_C(0x002cf444)); /* 12000004 beq s0,zero,002cf458 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002cf448));/* nop */target=sx(taken?UINT32_C(0x002cf458):UINT32_C(0x002cf44c));goto dispatch;}
L_002cf448:
 STEP(UINT32_C(0x002cf448)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002cf44c));goto dispatch;
L_002cf44c:
 STEP(UINT32_C(0x002cf44c)); /* 82020000 lb v0,0x0(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,sx((uint32_t)(int32_t)(int8_t)byte));}target=sx(UINT32_C(0x002cf450));goto dispatch;
L_002cf450:
 STEP(UINT32_C(0x002cf450)); /* 14400005 bne v0,zero,002cf468 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002cf454));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002cf468):UINT32_C(0x002cf458));goto dispatch;}
L_002cf454:
 STEP(UINT32_C(0x002cf454)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf458));goto dispatch;
L_002cf458:
 STEP(UINT32_C(0x002cf458)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf460));STEP(UINT32_C(0x002cf45c));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf45c:
 STEP(UINT32_C(0x002cf45c)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf460));goto dispatch;
L_002cf460:
 STEP(UINT32_C(0x002cf460)); /* 1000001d beq zero,zero,002cf4d8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf464));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(taken?UINT32_C(0x002cf4d8):UINT32_C(0x002cf468));goto dispatch;}
L_002cf464:
 STEP(UINT32_C(0x002cf464)); /* 2402ff2e addiu v0,zero,-210 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffff2e)));target=sx(UINT32_C(0x002cf468));goto dispatch;
L_002cf468:
 STEP(UINT32_C(0x002cf468)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf46c));goto dispatch;
L_002cf46c:
 STEP(UINT32_C(0x002cf46c)); /* 245097f0 addiu s0,v0,-26640 */
 set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0)));target=sx(UINT32_C(0x002cf470));goto dispatch;
L_002cf470:
 STEP(UINT32_C(0x002cf470)); /* ac5397f0 sw s3,-0x6810(v0) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffff97f0),&value32,4u);target=sx(UINT32_C(0x002cf474));goto dispatch;
L_002cf474:
 STEP(UINT32_C(0x002cf474)); /* ae120004 sw s2,0x4(s0) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002cf478));goto dispatch;
L_002cf478:
 STEP(UINT32_C(0x002cf478)); /* 26040014 addiu a0,s0,20 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x002cf47c));goto dispatch;
L_002cf47c:
 STEP(UINT32_C(0x002cf47c)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002cf484));STEP(UINT32_C(0x002cf480));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002cf480:
 STEP(UINT32_C(0x002cf480)); /* 240603ff addiu a2,zero,1023 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000003ff)));target=sx(UINT32_C(0x002cf484));goto dispatch;
L_002cf484:
 STEP(UINT32_C(0x002cf484)); /* a2000413 sb zero,0x413(s0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000413),&byte,1u);}target=sx(UINT32_C(0x002cf488));goto dispatch;
L_002cf488:
 STEP(UINT32_C(0x002cf488)); /* 3c09005a lui t1,zero,0x5a */
 set(m,9u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002cf48c));goto dispatch;
L_002cf48c:
 STEP(UINT32_C(0x002cf48c)); /* 0200382d daddu a3,s0,zero */
 set(m,7u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf490));goto dispatch;
L_002cf490:
 STEP(UINT32_C(0x002cf490)); /* 0280202d daddu a0,s4,zero */
 set(m,4u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002cf494));goto dispatch;
L_002cf494:
 STEP(UINT32_C(0x002cf494)); /* 2529ad00 addiu t1,t1,-21248 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffad00)));target=sx(UINT32_C(0x002cf498));goto dispatch;
L_002cf498:
 STEP(UINT32_C(0x002cf498)); /* 24050012 addiu a1,zero,18 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000012)));target=sx(UINT32_C(0x002cf49c));goto dispatch;
L_002cf49c:
 STEP(UINT32_C(0x002cf49c)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002cf4a0));goto dispatch;
L_002cf4a0:
 STEP(UINT32_C(0x002cf4a0)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002cf4a4));goto dispatch;
L_002cf4a4:
 STEP(UINT32_C(0x002cf4a4)); /* 24080414 addiu t0,zero,1044 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000414)));target=sx(UINT32_C(0x002cf4a8));goto dispatch;
L_002cf4a8:
 STEP(UINT32_C(0x002cf4a8)); /* 240a0004 addiu t2,zero,4 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002cf4ac));goto dispatch;
L_002cf4ac:
 STEP(UINT32_C(0x002cf4ac)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002cf4b4));STEP(UINT32_C(0x002cf4b0));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002cf4b0:
 STEP(UINT32_C(0x002cf4b0)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002cf4b4));goto dispatch;
L_002cf4b4:
 STEP(UINT32_C(0x002cf4b4)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002cf4b8));goto dispatch;
L_002cf4b8:
 STEP(UINT32_C(0x002cf4b8)); /* 16000004 bne s0,zero,002cf4cc */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x002cf4bc));set(m,3u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002cf4cc):UINT32_C(0x002cf4c0));goto dispatch;}
L_002cf4bc:
 STEP(UINT32_C(0x002cf4bc)); /* 3c030053 lui v1,zero,0x53 */
 set(m,3u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002cf4c0));goto dispatch;
L_002cf4c0:
 STEP(UINT32_C(0x002cf4c0)); /* 24020012 addiu v0,zero,18 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000012)));target=sx(UINT32_C(0x002cf4c4));goto dispatch;
L_002cf4c4:
 STEP(UINT32_C(0x002cf4c4)); /* 10000003 beq zero,zero,002cf4d4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002cf4c8));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(taken?UINT32_C(0x002cf4d4):UINT32_C(0x002cf4cc));goto dispatch;}
L_002cf4c8:
 STEP(UINT32_C(0x002cf4c8)); /* ac62bb20 sw v0,-0x44e0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffffbb20),&value32,4u);target=sx(UINT32_C(0x002cf4cc));goto dispatch;
L_002cf4cc:
 STEP(UINT32_C(0x002cf4cc)); /* 0c0b6fb0 jal 002dbec0 */
 set(m,31u,UINT64_C(0x002cf4d4));STEP(UINT32_C(0x002cf4d0));READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dbec0));goto dispatch;
L_002cf4d0:
 STEP(UINT32_C(0x002cf4d0)); /* 8e24bb24 lw a0,-0x44dc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffbb24),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002cf4d4));goto dispatch;
L_002cf4d4:
 STEP(UINT32_C(0x002cf4d4)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002cf4d8));goto dispatch;
L_002cf4d8:
 STEP(UINT32_C(0x002cf4d8)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002cf4dc));goto dispatch;
L_002cf4dc:
 STEP(UINT32_C(0x002cf4dc)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002cf4e0));goto dispatch;
L_002cf4e0:
 STEP(UINT32_C(0x002cf4e0)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002cf4e4));goto dispatch;
L_002cf4e4:
 STEP(UINT32_C(0x002cf4e4)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002cf4e8));goto dispatch;
L_002cf4e8:
 STEP(UINT32_C(0x002cf4e8)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002cf4ec));goto dispatch;
L_002cf4ec:
 STEP(UINT32_C(0x002cf4ec)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002cf4f0));goto dispatch;
L_002cf4f0:
 STEP(UINT32_C(0x002cf4f0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002cf4f4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));goto dispatch;
L_002cf4f4:
 STEP(UINT32_C(0x002cf4f4)); /* 27bd0070 addiu sp,sp,112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x002cf4f8));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

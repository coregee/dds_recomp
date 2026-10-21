#include "console_native.h"
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
uint32_t nocturneConsoleResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002da4ec):goto L_002da4ec;
 case UINT32_C(0x002da4f0):goto L_002da4f0;
 case UINT32_C(0x002da4f4):goto L_002da4f4;
 case UINT32_C(0x002da4f8):goto L_002da4f8;
 case UINT32_C(0x002da4fc):goto L_002da4fc;
 case UINT32_C(0x002da500):goto L_002da500;
 case UINT32_C(0x002da504):goto L_002da504;
 case UINT32_C(0x002da508):goto L_002da508;
 case UINT32_C(0x002da50c):goto L_002da50c;
 case UINT32_C(0x002da510):goto L_002da510;
 case UINT32_C(0x002da514):goto L_002da514;
 case UINT32_C(0x002da518):goto L_002da518;
 case UINT32_C(0x002da51c):goto L_002da51c;
 case UINT32_C(0x002da520):goto L_002da520;
 case UINT32_C(0x002da524):goto L_002da524;
 case UINT32_C(0x002da528):goto L_002da528;
 case UINT32_C(0x002da52c):goto L_002da52c;
 case UINT32_C(0x002da530):goto L_002da530;
 case UINT32_C(0x002da534):goto L_002da534;
 case UINT32_C(0x002da538):goto L_002da538;
 case UINT32_C(0x002da53c):goto L_002da53c;
 case UINT32_C(0x002da540):goto L_002da540;
 case UINT32_C(0x002da544):goto L_002da544;
 case UINT32_C(0x002da548):goto L_002da548;
 case UINT32_C(0x002da54c):goto L_002da54c;
 case UINT32_C(0x002da550):goto L_002da550;
 case UINT32_C(0x002da554):goto L_002da554;
 case UINT32_C(0x002da558):goto L_002da558;
 case UINT32_C(0x002da55c):goto L_002da55c;
 case UINT32_C(0x002da560):goto L_002da560;
 case UINT32_C(0x002da564):goto L_002da564;
 case UINT32_C(0x002da568):goto L_002da568;
 case UINT32_C(0x002da56c):goto L_002da56c;
 case UINT32_C(0x002da570):goto L_002da570;
 case UINT32_C(0x002da574):goto L_002da574;
 case UINT32_C(0x002da578):goto L_002da578;
 case UINT32_C(0x002da57c):goto L_002da57c;
 case UINT32_C(0x002da580):goto L_002da580;
 case UINT32_C(0x002da584):goto L_002da584;
 case UINT32_C(0x002da588):goto L_002da588;
 case UINT32_C(0x002da58c):goto L_002da58c;
 case UINT32_C(0x002da590):goto L_002da590;
 case UINT32_C(0x002da594):goto L_002da594;
 case UINT32_C(0x002da598):goto L_002da598;
 case UINT32_C(0x002da59c):goto L_002da59c;
 case UINT32_C(0x002da5a0):goto L_002da5a0;
 case UINT32_C(0x002da5a4):goto L_002da5a4;
 case UINT32_C(0x002da5a8):goto L_002da5a8;
 case UINT32_C(0x002da5ac):goto L_002da5ac;
 case UINT32_C(0x002da5b0):goto L_002da5b0;
 case UINT32_C(0x002da5b4):goto L_002da5b4;
 case UINT32_C(0x002da5b8):goto L_002da5b8;
 case UINT32_C(0x002da5bc):goto L_002da5bc;
 case UINT32_C(0x002da5c0):goto L_002da5c0;
 case UINT32_C(0x002da5c4):goto L_002da5c4;
 case UINT32_C(0x002da5c8):goto L_002da5c8;
 case UINT32_C(0x002dd360):goto L_002dd360;
 case UINT32_C(0x002dd364):goto L_002dd364;
 case UINT32_C(0x002dd368):goto L_002dd368;
 case UINT32_C(0x002dd36c):goto L_002dd36c;
 case UINT32_C(0x002dd370):goto L_002dd370;
 case UINT32_C(0x002dd374):goto L_002dd374;
 case UINT32_C(0x002dd378):goto L_002dd378;
 case UINT32_C(0x002dd37c):goto L_002dd37c;
 case UINT32_C(0x002dd380):goto L_002dd380;
 case UINT32_C(0x002dd384):goto L_002dd384;
 case UINT32_C(0x002dd388):goto L_002dd388;
 case UINT32_C(0x002dd38c):goto L_002dd38c;
 case UINT32_C(0x002dd390):goto L_002dd390;
 case UINT32_C(0x002dd394):goto L_002dd394;
 case UINT32_C(0x002dd398):goto L_002dd398;
 case UINT32_C(0x002dd39c):goto L_002dd39c;
 case UINT32_C(0x002dd3a0):goto L_002dd3a0;
 case UINT32_C(0x002dd3a4):goto L_002dd3a4;
 case UINT32_C(0x002dd3a8):goto L_002dd3a8;
 case UINT32_C(0x002dd3ac):goto L_002dd3ac;
 case UINT32_C(0x002dd3b0):goto L_002dd3b0;
 case UINT32_C(0x002dd3b4):goto L_002dd3b4;
 case UINT32_C(0x002dd3b8):goto L_002dd3b8;
 case UINT32_C(0x002dd3bc):goto L_002dd3bc;
 case UINT32_C(0x002dd3c0):goto L_002dd3c0;
 case UINT32_C(0x002dd3c4):goto L_002dd3c4;
 case UINT32_C(0x002dd3c8):goto L_002dd3c8;
 case UINT32_C(0x002dd3cc):goto L_002dd3cc;
 case UINT32_C(0x002dd3d0):goto L_002dd3d0;
 case UINT32_C(0x002dd3d4):goto L_002dd3d4;
 case UINT32_C(0x002dd3d8):goto L_002dd3d8;
 case UINT32_C(0x002dd3dc):goto L_002dd3dc;
 case UINT32_C(0x002dd3e0):goto L_002dd3e0;
 case UINT32_C(0x002dd3e4):goto L_002dd3e4;
 case UINT32_C(0x002dd3e8):goto L_002dd3e8;
 case UINT32_C(0x002dd3ec):goto L_002dd3ec;
 case UINT32_C(0x002dd3f0):goto L_002dd3f0;
 case UINT32_C(0x002dd3f4):goto L_002dd3f4;
 case UINT32_C(0x002dd3f8):goto L_002dd3f8;
 case UINT32_C(0x002dd3fc):goto L_002dd3fc;
 case UINT32_C(0x002dd400):goto L_002dd400;
 case UINT32_C(0x002dd404):goto L_002dd404;
 case UINT32_C(0x002dd408):goto L_002dd408;
 case UINT32_C(0x002dd40c):goto L_002dd40c;
 case UINT32_C(0x002dd410):goto L_002dd410;
 case UINT32_C(0x002dd414):goto L_002dd414;
 case UINT32_C(0x002dd418):goto L_002dd418;
 case UINT32_C(0x002dd140):goto L_002dd140;
 case UINT32_C(0x002dd144):goto L_002dd144;
 case UINT32_C(0x002dd148):goto L_002dd148;
 case UINT32_C(0x002dd14c):goto L_002dd14c;
 case UINT32_C(0x002dd150):goto L_002dd150;
 case UINT32_C(0x002dd154):goto L_002dd154;
 case UINT32_C(0x002dd158):goto L_002dd158;
 case UINT32_C(0x002dd15c):goto L_002dd15c;
 case UINT32_C(0x002dd160):goto L_002dd160;
 case UINT32_C(0x002dd164):goto L_002dd164;
 case UINT32_C(0x002dd168):goto L_002dd168;
 case UINT32_C(0x002dd16c):goto L_002dd16c;
 case UINT32_C(0x002dd170):goto L_002dd170;
 case UINT32_C(0x002dd174):goto L_002dd174;
 case UINT32_C(0x002dd178):goto L_002dd178;
 case UINT32_C(0x002dd17c):goto L_002dd17c;
 case UINT32_C(0x002dd180):goto L_002dd180;
 case UINT32_C(0x002dd184):goto L_002dd184;
 case UINT32_C(0x002dd188):goto L_002dd188;
 case UINT32_C(0x002dd18c):goto L_002dd18c;
 case UINT32_C(0x002dd190):goto L_002dd190;
 case UINT32_C(0x002dd194):goto L_002dd194;
 case UINT32_C(0x002dd198):goto L_002dd198;
 case UINT32_C(0x002dd19c):goto L_002dd19c;
 case UINT32_C(0x002dd1a0):goto L_002dd1a0;
 case UINT32_C(0x002dd1a4):goto L_002dd1a4;
 case UINT32_C(0x002dd1a8):goto L_002dd1a8;
 case UINT32_C(0x002dd1ac):goto L_002dd1ac;
 case UINT32_C(0x002dd1b0):goto L_002dd1b0;
 case UINT32_C(0x002dd1b4):goto L_002dd1b4;
 case UINT32_C(0x002dd1b8):goto L_002dd1b8;
 case UINT32_C(0x002dd1bc):goto L_002dd1bc;
 case UINT32_C(0x002dd1c0):goto L_002dd1c0;
 case UINT32_C(0x002dd1c4):goto L_002dd1c4;
 case UINT32_C(0x002dd1c8):goto L_002dd1c8;
 case UINT32_C(0x002dd1cc):goto L_002dd1cc;
 case UINT32_C(0x002dd1d0):goto L_002dd1d0;
 case UINT32_C(0x002dd1d4):goto L_002dd1d4;
 case UINT32_C(0x002dd1d8):goto L_002dd1d8;
 case UINT32_C(0x002dd1dc):goto L_002dd1dc;
 case UINT32_C(0x002dd1e0):goto L_002dd1e0;
 case UINT32_C(0x002dd1e4):goto L_002dd1e4;
 case UINT32_C(0x002dd1e8):goto L_002dd1e8;
 case UINT32_C(0x002dd1ec):goto L_002dd1ec;
 case UINT32_C(0x002dd1f0):goto L_002dd1f0;
 case UINT32_C(0x002dd1f4):goto L_002dd1f4;
 case UINT32_C(0x002dd1f8):goto L_002dd1f8;
 case UINT32_C(0x002dd1fc):goto L_002dd1fc;
 case UINT32_C(0x002dd200):goto L_002dd200;
 case UINT32_C(0x002dd204):goto L_002dd204;
 case UINT32_C(0x002dd208):goto L_002dd208;
 case UINT32_C(0x002dd20c):goto L_002dd20c;
 case UINT32_C(0x002dd210):goto L_002dd210;
 case UINT32_C(0x002dd214):goto L_002dd214;
 case UINT32_C(0x002dd218):goto L_002dd218;
 case UINT32_C(0x002dd21c):goto L_002dd21c;
 case UINT32_C(0x002dd220):goto L_002dd220;
 case UINT32_C(0x002dd224):goto L_002dd224;
 case UINT32_C(0x002dd228):goto L_002dd228;
 case UINT32_C(0x002dd22c):goto L_002dd22c;
 case UINT32_C(0x002dd230):goto L_002dd230;
 case UINT32_C(0x002dd234):goto L_002dd234;
 case UINT32_C(0x002dd238):goto L_002dd238;
 case UINT32_C(0x002dd23c):goto L_002dd23c;
 case UINT32_C(0x002dd240):goto L_002dd240;
 case UINT32_C(0x002dd244):goto L_002dd244;
 case UINT32_C(0x002dd248):goto L_002dd248;
 case UINT32_C(0x002dd24c):goto L_002dd24c;
 case UINT32_C(0x002dd250):goto L_002dd250;
 case UINT32_C(0x002dd254):goto L_002dd254;
 case UINT32_C(0x002dd258):goto L_002dd258;
 case UINT32_C(0x002dd25c):goto L_002dd25c;
 case UINT32_C(0x002dd260):goto L_002dd260;
 case UINT32_C(0x002dd264):goto L_002dd264;
 case UINT32_C(0x002dd268):goto L_002dd268;
 case UINT32_C(0x002dd26c):goto L_002dd26c;
 case UINT32_C(0x002dd270):goto L_002dd270;
 case UINT32_C(0x002dd274):goto L_002dd274;
 case UINT32_C(0x002dd278):goto L_002dd278;
 case UINT32_C(0x002dd27c):goto L_002dd27c;
 case UINT32_C(0x002dd280):goto L_002dd280;
 case UINT32_C(0x002dd284):goto L_002dd284;
 case UINT32_C(0x002dd288):goto L_002dd288;
 case UINT32_C(0x002dd28c):goto L_002dd28c;
 case UINT32_C(0x002dcfa8):goto L_002dcfa8;
 case UINT32_C(0x002dcfac):goto L_002dcfac;
 case UINT32_C(0x002dcfb0):goto L_002dcfb0;
 case UINT32_C(0x002dcfb4):goto L_002dcfb4;
 case UINT32_C(0x002dcfb8):goto L_002dcfb8;
 case UINT32_C(0x002dcfbc):goto L_002dcfbc;
 case UINT32_C(0x002dcfc0):goto L_002dcfc0;
 case UINT32_C(0x002dcfc4):goto L_002dcfc4;
 case UINT32_C(0x002dcfc8):goto L_002dcfc8;
 case UINT32_C(0x002dcfcc):goto L_002dcfcc;
 case UINT32_C(0x002dcfd0):goto L_002dcfd0;
 case UINT32_C(0x002dcfd4):goto L_002dcfd4;
 case UINT32_C(0x002dcfd8):goto L_002dcfd8;
 case UINT32_C(0x002dcfdc):goto L_002dcfdc;
 case UINT32_C(0x002dcfe0):goto L_002dcfe0;
 case UINT32_C(0x002dcfe4):goto L_002dcfe4;
 case UINT32_C(0x002dcfe8):goto L_002dcfe8;
 case UINT32_C(0x002dcfec):goto L_002dcfec;
 case UINT32_C(0x002dcff0):goto L_002dcff0;
 case UINT32_C(0x002dcff4):goto L_002dcff4;
 case UINT32_C(0x002dcff8):goto L_002dcff8;
 case UINT32_C(0x002dcffc):goto L_002dcffc;
 case UINT32_C(0x002dd000):goto L_002dd000;
 case UINT32_C(0x002dd004):goto L_002dd004;
 case UINT32_C(0x002dd008):goto L_002dd008;
 case UINT32_C(0x002dd00c):goto L_002dd00c;
 case UINT32_C(0x002dd010):goto L_002dd010;
 case UINT32_C(0x002dd014):goto L_002dd014;
 case UINT32_C(0x002dd018):goto L_002dd018;
 case UINT32_C(0x002dd01c):goto L_002dd01c;
 case UINT32_C(0x002dd020):goto L_002dd020;
 case UINT32_C(0x002dd024):goto L_002dd024;
 case UINT32_C(0x002dd028):goto L_002dd028;
 case UINT32_C(0x002dd02c):goto L_002dd02c;
 case UINT32_C(0x002dd030):goto L_002dd030;
 case UINT32_C(0x002dd034):goto L_002dd034;
 case UINT32_C(0x002dd038):goto L_002dd038;
 case UINT32_C(0x002dd03c):goto L_002dd03c;
 case UINT32_C(0x002dd040):goto L_002dd040;
 case UINT32_C(0x002dd044):goto L_002dd044;
 case UINT32_C(0x002dd048):goto L_002dd048;
 case UINT32_C(0x002dd04c):goto L_002dd04c;
 case UINT32_C(0x002dd050):goto L_002dd050;
 case UINT32_C(0x002dd054):goto L_002dd054;
 case UINT32_C(0x002dd058):goto L_002dd058;
 case UINT32_C(0x002dd05c):goto L_002dd05c;
 case UINT32_C(0x002dd060):goto L_002dd060;
 case UINT32_C(0x002dd064):goto L_002dd064;
 case UINT32_C(0x002dd068):goto L_002dd068;
 case UINT32_C(0x002dd06c):goto L_002dd06c;
 case UINT32_C(0x002dd070):goto L_002dd070;
 case UINT32_C(0x002dd074):goto L_002dd074;
 case UINT32_C(0x002dd078):goto L_002dd078;
 case UINT32_C(0x002dd07c):goto L_002dd07c;
 case UINT32_C(0x002dd080):goto L_002dd080;
 case UINT32_C(0x002dd084):goto L_002dd084;
 case UINT32_C(0x002dd088):goto L_002dd088;
 case UINT32_C(0x002dd08c):goto L_002dd08c;
 case UINT32_C(0x002dd090):goto L_002dd090;
 case UINT32_C(0x002dd094):goto L_002dd094;
 case UINT32_C(0x002dd098):goto L_002dd098;
 case UINT32_C(0x002dd09c):goto L_002dd09c;
 case UINT32_C(0x002dd0a0):goto L_002dd0a0;
 case UINT32_C(0x002dd0a4):goto L_002dd0a4;
 case UINT32_C(0x002dd0a8):goto L_002dd0a8;
 case UINT32_C(0x002dd0ac):goto L_002dd0ac;
 case UINT32_C(0x002dd0b0):goto L_002dd0b0;
 case UINT32_C(0x002dd0b4):goto L_002dd0b4;
 case UINT32_C(0x002dd0b8):goto L_002dd0b8;
 case UINT32_C(0x002dd0bc):goto L_002dd0bc;
 case UINT32_C(0x002dd0c0):goto L_002dd0c0;
 case UINT32_C(0x002dd0c4):goto L_002dd0c4;
 case UINT32_C(0x002dd0c8):goto L_002dd0c8;
 case UINT32_C(0x002dd0cc):goto L_002dd0cc;
 case UINT32_C(0x002dd0d0):goto L_002dd0d0;
 case UINT32_C(0x002dd0d4):goto L_002dd0d4;
 case UINT32_C(0x002dd0d8):goto L_002dd0d8;
 case UINT32_C(0x002dd0dc):goto L_002dd0dc;
 case UINT32_C(0x002dd0e0):goto L_002dd0e0;
 case UINT32_C(0x002dd0e4):goto L_002dd0e4;
 case UINT32_C(0x002dd0e8):goto L_002dd0e8;
 case UINT32_C(0x002dd0ec):goto L_002dd0ec;
 case UINT32_C(0x002dd0f0):goto L_002dd0f0;
 case UINT32_C(0x002dd0f4):goto L_002dd0f4;
 case UINT32_C(0x002dd0f8):goto L_002dd0f8;
 case UINT32_C(0x002dd0fc):goto L_002dd0fc;
 case UINT32_C(0x002dd100):goto L_002dd100;
 case UINT32_C(0x002dd104):goto L_002dd104;
 case UINT32_C(0x002dd108):goto L_002dd108;
 case UINT32_C(0x002dd10c):goto L_002dd10c;
 case UINT32_C(0x002dd110):goto L_002dd110;
 case UINT32_C(0x002dd114):goto L_002dd114;
 case UINT32_C(0x002dd118):goto L_002dd118;
 case UINT32_C(0x002dd11c):goto L_002dd11c;
 case UINT32_C(0x002dd120):goto L_002dd120;
 case UINT32_C(0x002dd124):goto L_002dd124;
 case UINT32_C(0x002dd128):goto L_002dd128;
 case UINT32_C(0x002dd12c):goto L_002dd12c;
 case UINT32_C(0x002dd130):goto L_002dd130;
 case UINT32_C(0x002dd134):goto L_002dd134;
 case UINT32_C(0x002dd138):goto L_002dd138;
 case UINT32_C(0x002dcf00):goto L_002dcf00;
 case UINT32_C(0x002dcf04):goto L_002dcf04;
 case UINT32_C(0x002dcf08):goto L_002dcf08;
 case UINT32_C(0x002dcf0c):goto L_002dcf0c;
 case UINT32_C(0x002dcf10):goto L_002dcf10;
 case UINT32_C(0x002dcf14):goto L_002dcf14;
 case UINT32_C(0x002dcf18):goto L_002dcf18;
 case UINT32_C(0x002dcf1c):goto L_002dcf1c;
 case UINT32_C(0x002dcf20):goto L_002dcf20;
 case UINT32_C(0x002dcf28):goto L_002dcf28;
 case UINT32_C(0x002dcf2c):goto L_002dcf2c;
 case UINT32_C(0x002dcf30):goto L_002dcf30;
 case UINT32_C(0x002dcf34):goto L_002dcf34;
 case UINT32_C(0x002dcf38):goto L_002dcf38;
 case UINT32_C(0x002dcf3c):goto L_002dcf3c;
 case UINT32_C(0x002dcf40):goto L_002dcf40;
 case UINT32_C(0x002dcf44):goto L_002dcf44;
 case UINT32_C(0x002dcf48):goto L_002dcf48;
 case UINT32_C(0x002dcf4c):goto L_002dcf4c;
 case UINT32_C(0x002dcf50):goto L_002dcf50;
 case UINT32_C(0x002dcf54):goto L_002dcf54;
 case UINT32_C(0x002dcf58):goto L_002dcf58;
 case UINT32_C(0x002dcf5c):goto L_002dcf5c;
 case UINT32_C(0x002dcf60):goto L_002dcf60;
 case UINT32_C(0x002e4898):goto L_002e4898;
 case UINT32_C(0x002e489c):goto L_002e489c;
 case UINT32_C(0x002e48a0):goto L_002e48a0;
 case UINT32_C(0x002e48a4):goto L_002e48a4;
 case UINT32_C(0x002e48a8):goto L_002e48a8;
 case UINT32_C(0x002e48ac):goto L_002e48ac;
 case UINT32_C(0x002e48b0):goto L_002e48b0;
 case UINT32_C(0x002e48b4):goto L_002e48b4;
 case UINT32_C(0x002e48b8):goto L_002e48b8;
 case UINT32_C(0x002e48bc):goto L_002e48bc;
 case UINT32_C(0x002e48c0):goto L_002e48c0;
 case UINT32_C(0x002e48c4):goto L_002e48c4;
 case UINT32_C(0x002e48c8):goto L_002e48c8;
 case UINT32_C(0x002e48cc):goto L_002e48cc;
 case UINT32_C(0x002e48d0):goto L_002e48d0;
 case UINT32_C(0x002e48d4):goto L_002e48d4;
 case UINT32_C(0x002e48d8):goto L_002e48d8;
 case UINT32_C(0x002e4908):goto L_002e4908;
 case UINT32_C(0x002e490c):goto L_002e490c;
 case UINT32_C(0x002e4910):goto L_002e4910;
 case UINT32_C(0x002e4914):goto L_002e4914;
 case UINT32_C(0x002e4918):goto L_002e4918;
 case UINT32_C(0x002e491c):goto L_002e491c;
 case UINT32_C(0x002e4920):goto L_002e4920;
 case UINT32_C(0x002e4924):goto L_002e4924;
 case UINT32_C(0x002e4928):goto L_002e4928;
 case UINT32_C(0x002e492c):goto L_002e492c;
 case UINT32_C(0x002e4930):goto L_002e4930;
 case UINT32_C(0x002e4934):goto L_002e4934;
 case UINT32_C(0x002e4938):goto L_002e4938;
 case UINT32_C(0x002e493c):goto L_002e493c;
 case UINT32_C(0x002e4940):goto L_002e4940;
 case UINT32_C(0x002e4944):goto L_002e4944;
 case UINT32_C(0x002e4948):goto L_002e4948;
 case UINT32_C(0x002e494c):goto L_002e494c;
 case UINT32_C(0x002e4950):goto L_002e4950;
 case UINT32_C(0x002e4954):goto L_002e4954;
 case UINT32_C(0x002e4958):goto L_002e4958;
 case UINT32_C(0x002e4960):goto L_002e4960;
 case UINT32_C(0x002e4964):goto L_002e4964;
 case UINT32_C(0x002e4968):goto L_002e4968;
 case UINT32_C(0x002e496c):goto L_002e496c;
 case UINT32_C(0x002e4970):goto L_002e4970;
 case UINT32_C(0x002e4974):goto L_002e4974;
 case UINT32_C(0x002e4978):goto L_002e4978;
 case UINT32_C(0x002e497c):goto L_002e497c;
 case UINT32_C(0x002e4980):goto L_002e4980;
 case UINT32_C(0x002e4984):goto L_002e4984;
 case UINT32_C(0x002e4988):goto L_002e4988;
 case UINT32_C(0x002e498c):goto L_002e498c;
 case UINT32_C(0x002e4990):goto L_002e4990;
 case UINT32_C(0x002e4998):goto L_002e4998;
 case UINT32_C(0x002e499c):goto L_002e499c;
 case UINT32_C(0x002e49a0):goto L_002e49a0;
 case UINT32_C(0x002e49a4):goto L_002e49a4;
 case UINT32_C(0x002e49a8):goto L_002e49a8;
 case UINT32_C(0x002e49ac):goto L_002e49ac;
 case UINT32_C(0x002e49b0):goto L_002e49b0;
 case UINT32_C(0x002e49b4):goto L_002e49b4;
 case UINT32_C(0x002e49b8):goto L_002e49b8;
 case UINT32_C(0x002e49bc):goto L_002e49bc;
 case UINT32_C(0x002e49c0):goto L_002e49c0;
 case UINT32_C(0x002e49c4):goto L_002e49c4;
 case UINT32_C(0x002e49c8):goto L_002e49c8;
 case UINT32_C(0x002dc2d0):goto L_002dc2d0;
 case UINT32_C(0x002dc2d4):goto L_002dc2d4;
 case UINT32_C(0x002dc2d8):goto L_002dc2d8;
 case UINT32_C(0x002dc2dc):goto L_002dc2dc;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002da4ec:
 STEP(UINT32_C(0x002da4ec)); /* 2cc20010 sltiu v0,a2,16 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x10)));target=sx(UINT32_C(0x002da4f0));goto dispatch;
L_002da4f0:
 STEP(UINT32_C(0x002da4f0)); /* 14400026 bne v0,zero,002da58c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002da4f4));set(m,5u,lo(m,5u) & UINT64_C(0xff));target=sx(taken?UINT32_C(0x002da58c):UINT32_C(0x002da4f8));goto dispatch;}
L_002da4f4:
 STEP(UINT32_C(0x002da4f4)); /* 30a500ff andi a1,a1,0xff */
 set(m,5u,lo(m,5u) & UINT64_C(0xff));target=sx(UINT32_C(0x002da4f8));goto dispatch;
L_002da4f8:
 STEP(UINT32_C(0x002da4f8)); /* 3082000f andi v0,a0,0xf */
 set(m,2u,lo(m,4u) & UINT64_C(0xf));target=sx(UINT32_C(0x002da4fc));goto dispatch;
L_002da4fc:
 STEP(UINT32_C(0x002da4fc)); /* 14400023 bne v0,zero,002da58c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002da500));set(m,7u,lo(m,4u)+lo(m,0u));target=sx(taken?UINT32_C(0x002da58c):UINT32_C(0x002da504));goto dispatch;}
L_002da500:
 STEP(UINT32_C(0x002da500)); /* 0080382d daddu a3,a0,zero */
 set(m,7u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002da504));goto dispatch;
L_002da504:
 STEP(UINT32_C(0x002da504)); /* 00051a38 dsll v1,a1,8 */
 set(m,3u,lo(m,5u)<<8u);target=sx(UINT32_C(0x002da508));goto dispatch;
L_002da508:
 STEP(UINT32_C(0x002da508)); /* 3c020101 lui v0,zero,0x101 */
 set(m,2u,sx(UINT32_C(0x01010000)));target=sx(UINT32_C(0x002da50c));goto dispatch;
L_002da50c:
 STEP(UINT32_C(0x002da50c)); /* 34420101 ori v0,v0,0x101 */
 set(m,2u,lo(m,2u) | UINT64_C(0x101));target=sx(UINT32_C(0x002da510));goto dispatch;
L_002da510:
 STEP(UINT32_C(0x002da510)); /* 00021438 dsll v0,v0,16 */
 set(m,2u,lo(m,2u)<<16u);target=sx(UINT32_C(0x002da514));goto dispatch;
L_002da514:
 STEP(UINT32_C(0x002da514)); /* 34420101 ori v0,v0,0x101 */
 set(m,2u,lo(m,2u) | UINT64_C(0x101));target=sx(UINT32_C(0x002da518));goto dispatch;
L_002da518:
 STEP(UINT32_C(0x002da518)); /* 00021438 dsll v0,v0,16 */
 set(m,2u,lo(m,2u)<<16u);target=sx(UINT32_C(0x002da51c));goto dispatch;
L_002da51c:
 STEP(UINT32_C(0x002da51c)); /* 34420101 ori v0,v0,0x101 */
 set(m,2u,lo(m,2u) | UINT64_C(0x101));target=sx(UINT32_C(0x002da520));goto dispatch;
L_002da520:
 STEP(UINT32_C(0x002da520)); /* 0065502d daddu t2,v1,a1 */
 set(m,10u,lo(m,3u)+lo(m,5u));target=sx(UINT32_C(0x002da524));goto dispatch;
L_002da524:
 STEP(UINT32_C(0x002da524)); /* 3c038080 lui v1,zero,0x8080 */
 set(m,3u,sx(UINT32_C(0x80800000)));target=sx(UINT32_C(0x002da528));goto dispatch;
L_002da528:
 STEP(UINT32_C(0x002da528)); /* 34638080 ori v1,v1,0x8080 */
 set(m,3u,lo(m,3u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002da52c));goto dispatch;
L_002da52c:
 STEP(UINT32_C(0x002da52c)); /* 00031c38 dsll v1,v1,16 */
 set(m,3u,lo(m,3u)<<16u);target=sx(UINT32_C(0x002da530));goto dispatch;
L_002da530:
 STEP(UINT32_C(0x002da530)); /* 34638080 ori v1,v1,0x8080 */
 set(m,3u,lo(m,3u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002da534));goto dispatch;
L_002da534:
 STEP(UINT32_C(0x002da534)); /* 00031c38 dsll v1,v1,16 */
 set(m,3u,lo(m,3u)<<16u);target=sx(UINT32_C(0x002da538));goto dispatch;
L_002da538:
 STEP(UINT32_C(0x002da538)); /* 34638080 ori v1,v1,0x8080 */
 set(m,3u,lo(m,3u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002da53c));goto dispatch;
L_002da53c:
 STEP(UINT32_C(0x002da53c)); /* 700a46e9 mmi 700a46e9 */
 {uint32_t a=m->gpr[10][0]&0xffffu,b=m->gpr[10][2]&0xffffu;a|=a<<16;b|=b<<16;m->gpr[8][0]=a;m->gpr[8][1]=a;m->gpr[8][2]=b;m->gpr[8][3]=b;}target=sx(UINT32_C(0x002da540));goto dispatch;
L_002da540:
 STEP(UINT32_C(0x002da540)); /* 71084b89 mmi 71084b89 */
 {uint32_t out[4]={m->gpr[8][0],m->gpr[8][1],m->gpr[8][0],m->gpr[8][1]};memcpy(m->gpr[9],out,16);}target=sx(UINT32_C(0x002da544));goto dispatch;
L_002da544:
 STEP(UINT32_C(0x002da544)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002da548));goto dispatch;
L_002da548:
 STEP(UINT32_C(0x002da548)); /* 70634389 mmi 70634389 */
 {uint32_t out[4]={m->gpr[3][0],m->gpr[3][1],m->gpr[3][0],m->gpr[3][1]};memcpy(m->gpr[8],out,16);}target=sx(UINT32_C(0x002da54c));goto dispatch;
L_002da54c:
 STEP(UINT32_C(0x002da54c)); /* 78e20000 lq v0,0x0(a3) */
 {uint32_t q[4];READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x002da550));goto dispatch;
L_002da550:
 STEP(UINT32_C(0x002da550)); /* 704914c9 mmi 704914c9 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]^m->gpr[9][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002da554));goto dispatch;
L_002da554:
 STEP(UINT32_C(0x002da554)); /* 70845389 mmi 70845389 */
 {uint32_t out[4]={m->gpr[4][0],m->gpr[4][1],m->gpr[4][0],m->gpr[4][1]};memcpy(m->gpr[10],out,16);}target=sx(UINT32_C(0x002da558));goto dispatch;
L_002da558:
 STEP(UINT32_C(0x002da558)); /* 70021ce9 mmi 70021ce9 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=~(m->gpr[0][j]|m->gpr[2][j]);memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002da55c));goto dispatch;
L_002da55c:
 STEP(UINT32_C(0x002da55c)); /* 704a1248 mmi 704a1248 */
 {uint8_t a[16],b[16],out[16];memcpy(a,m->gpr[2],16);memcpy(b,m->gpr[10],16);for(unsigned j=0;j<16;++j)out[j]=(uint8_t)(a[j]-b[j]);memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002da560));goto dispatch;
L_002da560:
 STEP(UINT32_C(0x002da560)); /* 70431489 mmi 70431489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[3][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002da564));goto dispatch;
L_002da564:
 STEP(UINT32_C(0x002da564)); /* 70481489 mmi 70481489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[8][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002da568));goto dispatch;
L_002da568:
 STEP(UINT32_C(0x002da568)); /* 70491ba9 mmi 70491ba9 */
 {uint32_t out[4]={m->gpr[2][2],m->gpr[2][3],m->gpr[9][2],m->gpr[9][3]};memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002da56c));goto dispatch;
L_002da56c:
 STEP(UINT32_C(0x002da56c)); /* 00431025 or v0,v0,v1 */
 set(m,2u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x002da570));goto dispatch;
L_002da570:
 STEP(UINT32_C(0x002da570)); /* 54400006 bnel v0,zero,002da58c */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002da574));set(m,4u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002da58c));}else target=sx(UINT32_C(0x002da578));goto dispatch;
L_002da574:
 STEP(UINT32_C(0x002da574)); /* 00e0202d daddu a0,a3,zero */
 set(m,4u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002da578));goto dispatch;
L_002da578:
 STEP(UINT32_C(0x002da578)); /* 24c6fff0 addiu a2,a2,-16 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002da57c));goto dispatch;
L_002da57c:
 STEP(UINT32_C(0x002da57c)); /* 2cc20010 sltiu v0,a2,16 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x10)));target=sx(UINT32_C(0x002da580));goto dispatch;
L_002da580:
 STEP(UINT32_C(0x002da580)); /* 1040fff2 beq v0,zero,002da54c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002da584));set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x002da54c):UINT32_C(0x002da588));goto dispatch;}
L_002da584:
 STEP(UINT32_C(0x002da584)); /* 24e70010 addiu a3,a3,16 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002da588));goto dispatch;
L_002da588:
 STEP(UINT32_C(0x002da588)); /* 00e0202d daddu a0,a3,zero */
 set(m,4u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002da58c));goto dispatch;
L_002da58c:
 STEP(UINT32_C(0x002da58c)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002da590));goto dispatch;
L_002da590:
 STEP(UINT32_C(0x002da590)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002da594));goto dispatch;
L_002da594:
 STEP(UINT32_C(0x002da594)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002da598));goto dispatch;
L_002da598:
 STEP(UINT32_C(0x002da598)); /* 10c20008 beq a2,v0,002da5bc */
 {int taken=(lo(m,6u)==lo(m,2u));STEP(UINT32_C(0x002da59c));/* nop */target=sx(taken?UINT32_C(0x002da5bc):UINT32_C(0x002da5a0));goto dispatch;}
L_002da59c:
 STEP(UINT32_C(0x002da59c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002da5a0));goto dispatch;
L_002da5a0:
 STEP(UINT32_C(0x002da5a0)); /* 3c03ffff lui v1,zero,0xffff */
 set(m,3u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002da5a4));goto dispatch;
L_002da5a4:
 STEP(UINT32_C(0x002da5a4)); /* 3463ffff ori v1,v1,0xffff */
 set(m,3u,lo(m,3u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002da5a8));goto dispatch;
L_002da5a8:
 STEP(UINT32_C(0x002da5a8)); /* 90820000 lbu v0,0x0(a0) */
 {uint8_t byte;READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002da5ac));goto dispatch;
L_002da5ac:
 STEP(UINT32_C(0x002da5ac)); /* 10450005 beq v0,a1,002da5c4 */
 {int taken=(lo(m,2u)==lo(m,5u));STEP(UINT32_C(0x002da5b0));set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002da5c4):UINT32_C(0x002da5b4));goto dispatch;}
L_002da5b0:
 STEP(UINT32_C(0x002da5b0)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002da5b4));goto dispatch;
L_002da5b4:
 STEP(UINT32_C(0x002da5b4)); /* 14c3fffc bne a2,v1,002da5a8 */
 {int taken=(lo(m,6u)!=lo(m,3u));STEP(UINT32_C(0x002da5b8));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002da5a8):UINT32_C(0x002da5bc));goto dispatch;}
L_002da5b8:
 STEP(UINT32_C(0x002da5b8)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002da5bc));goto dispatch;
L_002da5bc:
 STEP(UINT32_C(0x002da5bc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002da5c0));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_002da5c0:
 STEP(UINT32_C(0x002da5c0)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002da5c4));goto dispatch;
L_002da5c4:
 STEP(UINT32_C(0x002da5c4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002da5c8));set(m,2u,lo(m,4u)+lo(m,0u));goto dispatch;
L_002da5c8:
 STEP(UINT32_C(0x002da5c8)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002da5cc));goto dispatch;
L_002dd360:
 STEP(UINT32_C(0x002dd360)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002dd364));goto dispatch;
L_002dd364:
 STEP(UINT32_C(0x002dd364)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dd368));goto dispatch;
L_002dd368:
 STEP(UINT32_C(0x002dd368)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dd36c));goto dispatch;
L_002dd36c:
 STEP(UINT32_C(0x002dd36c)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dd370));goto dispatch;
L_002dd370:
 STEP(UINT32_C(0x002dd370)); /* ffbf0020 sd ra,0x20(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dd374));goto dispatch;
L_002dd374:
 STEP(UINT32_C(0x002dd374)); /* 0c0b7048 jal 002dc120 */
 set(m,31u,UINT64_C(0x002dd37c));STEP(UINT32_C(0x002dd378));set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dc120));goto dispatch;
L_002dd378:
 STEP(UINT32_C(0x002dd378)); /* 3c10005a lui s0,zero,0x5a */
 set(m,16u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dd37c));goto dispatch;
L_002dd37c:
 STEP(UINT32_C(0x002dd37c)); /* 2611b690 addiu s1,s0,-18800 */
 set(m,17u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffb690)));target=sx(UINT32_C(0x002dd380));goto dispatch;
L_002dd380:
 STEP(UINT32_C(0x002dd380)); /* 3c06002e lui a2,zero,0x2e */
 set(m,6u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002dd384));goto dispatch;
L_002dd384:
 STEP(UINT32_C(0x002dd384)); /* 24040210 addiu a0,zero,528 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000210)));target=sx(UINT32_C(0x002dd388));goto dispatch;
L_002dd388:
 STEP(UINT32_C(0x002dd388)); /* 24c6cfa8 addiu a2,a2,-12376 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffcfa8)));target=sx(UINT32_C(0x002dd38c));goto dispatch;
L_002dd38c:
 STEP(UINT32_C(0x002dd38c)); /* 0c0b9226 jal 002e4898 */
 set(m,31u,UINT64_C(0x002dd394));STEP(UINT32_C(0x002dd390));set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002e4898));goto dispatch;
L_002dd390:
 STEP(UINT32_C(0x002dd390)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002dd394));goto dispatch;
L_002dd394:
 STEP(UINT32_C(0x002dd394)); /* ae02b690 sw v0,-0x4970(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0xffffb690),&value32,4u);target=sx(UINT32_C(0x002dd398));goto dispatch;
L_002dd398:
 STEP(UINT32_C(0x002dd398)); /* 8e02b690 lw v0,-0x4970(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffb690),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd39c));goto dispatch;
L_002dd39c:
 STEP(UINT32_C(0x002dd39c)); /* 04410003 regimm1 v0,002dd3ac */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002dd3a0));set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(taken?UINT32_C(0x002dd3ac):UINT32_C(0x002dd3a4));goto dispatch;}
L_002dd3a0:
 STEP(UINT32_C(0x002dd3a0)); /* 3c04005a lui a0,zero,0x5a */
 set(m,4u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dd3a4));goto dispatch;
L_002dd3a4:
 STEP(UINT32_C(0x002dd3a4)); /* 10000018 beq zero,zero,002dd408 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dd3a8));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dd408):UINT32_C(0x002dd3ac));goto dispatch;}
L_002dd3a8:
 STEP(UINT32_C(0x002dd3a8)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dd3ac));goto dispatch;
L_002dd3ac:
 STEP(UINT32_C(0x002dd3ac)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dd3b0));goto dispatch;
L_002dd3b0:
 STEP(UINT32_C(0x002dd3b0)); /* ae20000c sw zero,0xc(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002dd3b4));goto dispatch;
L_002dd3b4:
 STEP(UINT32_C(0x002dd3b4)); /* 3c032000 lui v1,zero,0x2000 */
 set(m,3u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002dd3b8));goto dispatch;
L_002dd3b8:
 STEP(UINT32_C(0x002dd3b8)); /* 2484b800 addiu a0,a0,-18432 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffb800)));target=sx(UINT32_C(0x002dd3bc));goto dispatch;
L_002dd3bc:
 STEP(UINT32_C(0x002dd3bc)); /* 2442b6c0 addiu v0,v0,-18752 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6c0)));target=sx(UINT32_C(0x002dd3c0));goto dispatch;
L_002dd3c0:
 STEP(UINT32_C(0x002dd3c0)); /* 00431025 or v0,v0,v1 */
 set(m,2u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x002dd3c4));goto dispatch;
L_002dd3c4:
 STEP(UINT32_C(0x002dd3c4)); /* ae200004 sw zero,0x4(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dd3c8));goto dispatch;
L_002dd3c8:
 STEP(UINT32_C(0x002dd3c8)); /* 00832025 or a0,a0,v1 */
 set(m,4u,lo(m,4u)|lo(m,3u));target=sx(UINT32_C(0x002dd3cc));goto dispatch;
L_002dd3cc:
 STEP(UINT32_C(0x002dd3cc)); /* ae200008 sw zero,0x8(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dd3d0));goto dispatch;
L_002dd3d0:
 STEP(UINT32_C(0x002dd3d0)); /* ae240014 sw a0,0x14(s1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002dd3d4));goto dispatch;
L_002dd3d4:
 STEP(UINT32_C(0x002dd3d4)); /* 24060210 addiu a2,zero,528 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000210)));target=sx(UINT32_C(0x002dd3d8));goto dispatch;
L_002dd3d8:
 STEP(UINT32_C(0x002dd3d8)); /* ae220010 sw v0,0x10(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002dd3dc));goto dispatch;
L_002dd3dc:
 STEP(UINT32_C(0x002dd3dc)); /* 24050045 addiu a1,zero,69 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000045)));target=sx(UINT32_C(0x002dd3e0));goto dispatch;
L_002dd3e0:
 STEP(UINT32_C(0x002dd3e0)); /* 24030048 addiu v1,zero,72 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000048)));target=sx(UINT32_C(0x002dd3e4));goto dispatch;
L_002dd3e4:
 STEP(UINT32_C(0x002dd3e4)); /* 24040100 addiu a0,zero,256 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000100)));target=sx(UINT32_C(0x002dd3e8));goto dispatch;
L_002dd3e8:
 STEP(UINT32_C(0x002dd3e8)); /* a4460004 sh a2,0x4(v0) */
 value16=(uint16_t)lo(m,6u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value16,2u);target=sx(UINT32_C(0x002dd3ec));goto dispatch;
L_002dd3ec:
 STEP(UINT32_C(0x002dd3ec)); /* a0450006 sb a1,0x6(v0) */
 {uint8_t byte=(uint8_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000006),&byte,1u);}target=sx(UINT32_C(0x002dd3f0));goto dispatch;
L_002dd3f0:
 STEP(UINT32_C(0x002dd3f0)); /* a0430007 sb v1,0x7(v0) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000007),&byte,1u);}target=sx(UINT32_C(0x002dd3f4));goto dispatch;
L_002dd3f4:
 STEP(UINT32_C(0x002dd3f4)); /* ac400008 sw zero,0x8(v0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dd3f8));goto dispatch;
L_002dd3f8:
 STEP(UINT32_C(0x002dd3f8)); /* 0c0b73c0 jal 002dcf00 */
 set(m,31u,UINT64_C(0x002dd400));STEP(UINT32_C(0x002dd3fc));value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000002),&value16,2u);target=sx(UINT32_C(0x002dcf00));goto dispatch;
L_002dd3fc:
 STEP(UINT32_C(0x002dd3fc)); /* a4400002 sh zero,0x2(v0) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000002),&value16,2u);target=sx(UINT32_C(0x002dd400));goto dispatch;
L_002dd400:
 STEP(UINT32_C(0x002dd400)); /* ae220018 sw v0,0x18(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002dd404));goto dispatch;
L_002dd404:
 STEP(UINT32_C(0x002dd404)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd408));goto dispatch;
L_002dd408:
 STEP(UINT32_C(0x002dd408)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dd40c));goto dispatch;
L_002dd40c:
 STEP(UINT32_C(0x002dd40c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dd410));goto dispatch;
L_002dd410:
 STEP(UINT32_C(0x002dd410)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dd414));goto dispatch;
L_002dd414:
 STEP(UINT32_C(0x002dd414)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dd418));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002dd418:
 STEP(UINT32_C(0x002dd418)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002dd41c));goto dispatch;
L_002dd140:
 STEP(UINT32_C(0x002dd140)); /* 27bdff90 addiu sp,sp,-112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff90)));target=sx(UINT32_C(0x002dd144));goto dispatch;
L_002dd144:
 STEP(UINT32_C(0x002dd144)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002dd148));goto dispatch;
L_002dd148:
 STEP(UINT32_C(0x002dd148)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002dd14c));goto dispatch;
L_002dd14c:
 STEP(UINT32_C(0x002dd14c)); /* 3c15005a lui s5,zero,0x5a */
 set(m,21u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dd150));goto dispatch;
L_002dd150:
 STEP(UINT32_C(0x002dd150)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002dd154));goto dispatch;
L_002dd154:
 STEP(UINT32_C(0x002dd154)); /* 0000a02d daddu s4,zero,zero */
 set(m,20u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dd158));goto dispatch;
L_002dd158:
 STEP(UINT32_C(0x002dd158)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dd15c));goto dispatch;
L_002dd15c:
 STEP(UINT32_C(0x002dd15c)); /* 26b3b690 addiu s3,s5,-18800 */
 set(m,19u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffb690)));target=sx(UINT32_C(0x002dd160));goto dispatch;
L_002dd160:
 STEP(UINT32_C(0x002dd160)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dd164));goto dispatch;
L_002dd164:
 STEP(UINT32_C(0x002dd164)); /* 00a0902d daddu s2,a1,zero */
 set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002dd168));goto dispatch;
L_002dd168:
 STEP(UINT32_C(0x002dd168)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dd16c));goto dispatch;
L_002dd16c:
 STEP(UINT32_C(0x002dd16c)); /* 0000882d daddu s1,zero,zero */
 set(m,17u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002dd170));goto dispatch;
L_002dd170:
 STEP(UINT32_C(0x002dd170)); /* ffbf0060 sd ra,0x60(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002dd174));goto dispatch;
L_002dd174:
 STEP(UINT32_C(0x002dd174)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002dd178));goto dispatch;
L_002dd178:
 STEP(UINT32_C(0x002dd178)); /* 8e62000c lw v0,0xc(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd17c));goto dispatch;
L_002dd17c:
 STEP(UINT32_C(0x002dd17c)); /* 1440003b bne v0,zero,002dd26c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dd180));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002dd26c):UINT32_C(0x002dd184));goto dispatch;}
L_002dd180:
 STEP(UINT32_C(0x002dd180)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dd184));goto dispatch;
L_002dd184:
 STEP(UINT32_C(0x002dd184)); /* 0c0b901c jal 002e4070 */
 set(m,31u,UINT64_C(0x002dd18c));STEP(UINT32_C(0x002dd188));/* nop */target=sx(UINT32_C(0x002e4070));goto dispatch;
L_002dd188:
 STEP(UINT32_C(0x002dd188)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd18c));goto dispatch;
L_002dd18c:
 STEP(UINT32_C(0x002dd18c)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dd190));goto dispatch;
L_002dd190:
 STEP(UINT32_C(0x002dd190)); /* 3c032000 lui v1,zero,0x2000 */
 set(m,3u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002dd194));goto dispatch;
L_002dd194:
 STEP(UINT32_C(0x002dd194)); /* 2442b6c0 addiu v0,v0,-18752 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb6c0)));target=sx(UINT32_C(0x002dd198));goto dispatch;
L_002dd198:
 STEP(UINT32_C(0x002dd198)); /* 24040001 addiu a0,zero,1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd19c));goto dispatch;
L_002dd19c:
 STEP(UINT32_C(0x002dd19c)); /* 00433025 or a2,v0,v1 */
 set(m,6u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x002dd1a0));goto dispatch;
L_002dd1a0:
 STEP(UINT32_C(0x002dd1a0)); /* ae64000c sw a0,0xc(s3) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002dd1a4));goto dispatch;
L_002dd1a4:
 STEP(UINT32_C(0x002dd1a4)); /* ae660010 sw a2,0x10(s3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002dd1a8));goto dispatch;
L_002dd1a8:
 STEP(UINT32_C(0x002dd1a8)); /* 2408ffff addiu t0,zero,-1 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dd1ac));goto dispatch;
L_002dd1ac:
 STEP(UINT32_C(0x002dd1ac)); /* 2407000a addiu a3,zero,10 */
 set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002dd1b0));goto dispatch;
L_002dd1b0:
 STEP(UINT32_C(0x002dd1b0)); /* 2405000d addiu a1,zero,13 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000d)));target=sx(UINT32_C(0x002dd1b4));goto dispatch;
L_002dd1b4:
 STEP(UINT32_C(0x002dd1b4)); /* 24c4000c addiu a0,a2,12 */
 set(m,4u,sx((uint32_t)lo(m,6u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002dd1b8));goto dispatch;
L_002dd1b8:
 STEP(UINT32_C(0x002dd1b8)); /* 2652ffff addiu s2,s2,-1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dd1bc));goto dispatch;
L_002dd1bc:
 STEP(UINT32_C(0x002dd1bc)); /* 52480012 beql s2,t0,002dd208 */
 if(lo(m,18u)==lo(m,8u)){STEP(UINT32_C(0x002dd1c0));set(m,16u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffb690)));target=sx(UINT32_C(0x002dd208));}else target=sx(UINT32_C(0x002dd1c4));goto dispatch;
L_002dd1c0:
 STEP(UINT32_C(0x002dd1c0)); /* 26b0b690 addiu s0,s5,-18800 */
 set(m,16u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffb690)));target=sx(UINT32_C(0x002dd1c4));goto dispatch;
L_002dd1c4:
 STEP(UINT32_C(0x002dd1c4)); /* 82020000 lb v0,0x0(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002dd1c8));goto dispatch;
L_002dd1c8:
 STEP(UINT32_C(0x002dd1c8)); /* 14470007 bne v0,a3,002dd1e8 */
 {int taken=(lo(m,2u)!=lo(m,7u));STEP(UINT32_C(0x002dd1cc));{uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(taken?UINT32_C(0x002dd1e8):UINT32_C(0x002dd1d0));goto dispatch;}
L_002dd1cc:
 STEP(UINT32_C(0x002dd1cc)); /* 92030000 lbu v1,0x0(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002dd1d0));goto dispatch;
L_002dd1d0:
 STEP(UINT32_C(0x002dd1d0)); /* a0850000 sb a1,0x0(a0) */
 {uint8_t byte=(uint8_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002dd1d4));goto dispatch;
L_002dd1d4:
 STEP(UINT32_C(0x002dd1d4)); /* 26310001 addiu s1,s1,1 */
 set(m,17u,sx((uint32_t)lo(m,17u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd1d8));goto dispatch;
L_002dd1d8:
 STEP(UINT32_C(0x002dd1d8)); /* 2a220100 slti v0,s1,256 */
 set(m,2u,((int64_t)lo(m,17u)<INT64_C(256)));target=sx(UINT32_C(0x002dd1dc));goto dispatch;
L_002dd1dc:
 STEP(UINT32_C(0x002dd1dc)); /* 10400009 beq v0,zero,002dd204 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002dd1e0));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002dd204):UINT32_C(0x002dd1e4));goto dispatch;}
L_002dd1e0:
 STEP(UINT32_C(0x002dd1e0)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd1e4));goto dispatch;
L_002dd1e4:
 STEP(UINT32_C(0x002dd1e4)); /* 92030000 lbu v1,0x0(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002dd1e8));goto dispatch;
L_002dd1e8:
 STEP(UINT32_C(0x002dd1e8)); /* a0830000 sb v1,0x0(a0) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002dd1ec));goto dispatch;
L_002dd1ec:
 STEP(UINT32_C(0x002dd1ec)); /* 26310001 addiu s1,s1,1 */
 set(m,17u,sx((uint32_t)lo(m,17u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd1f0));goto dispatch;
L_002dd1f0:
 STEP(UINT32_C(0x002dd1f0)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd1f4));goto dispatch;
L_002dd1f4:
 STEP(UINT32_C(0x002dd1f4)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd1f8));goto dispatch;
L_002dd1f8:
 STEP(UINT32_C(0x002dd1f8)); /* 2a220100 slti v0,s1,256 */
 set(m,2u,((int64_t)lo(m,17u)<INT64_C(256)));target=sx(UINT32_C(0x002dd1fc));goto dispatch;
L_002dd1fc:
 STEP(UINT32_C(0x002dd1fc)); /* 1440ffee bne v0,zero,002dd1b8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dd200));set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002dd1b8):UINT32_C(0x002dd204));goto dispatch;}
L_002dd200:
 STEP(UINT32_C(0x002dd200)); /* 26940001 addiu s4,s4,1 */
 set(m,20u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd204));goto dispatch;
L_002dd204:
 STEP(UINT32_C(0x002dd204)); /* 26b0b690 addiu s0,s5,-18800 */
 set(m,16u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffb690)));target=sx(UINT32_C(0x002dd208));goto dispatch;
L_002dd208:
 STEP(UINT32_C(0x002dd208)); /* 2622000c addiu v0,s1,12 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002dd20c));goto dispatch;
L_002dd20c:
 STEP(UINT32_C(0x002dd20c)); /* ae020004 sw v0,0x4(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dd210));goto dispatch;
L_002dd210:
 STEP(UINT32_C(0x002dd210)); /* 8e030004 lw v1,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dd214));goto dispatch;
L_002dd214:
 STEP(UINT32_C(0x002dd214)); /* 80c50007 lb a1,0x7(a2) */
 {uint8_t byte;READ((uint32_t)lo(m,6u)+UINT32_C(0x00000007),&byte,1u);set(m,5u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x002dd218));goto dispatch;
L_002dd218:
 STEP(UINT32_C(0x002dd218)); /* 8ea4b690 lw a0,-0x4970(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffb690),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dd21c));goto dispatch;
L_002dd21c:
 STEP(UINT32_C(0x002dd21c)); /* 0c0b9242 jal 002e4908 */
 set(m,31u,UINT64_C(0x002dd224));STEP(UINT32_C(0x002dd220));value16=(uint16_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value16,2u);target=sx(UINT32_C(0x002e4908));goto dispatch;
L_002dd220:
 STEP(UINT32_C(0x002dd220)); /* a4c30000 sh v1,0x0(a2) */
 value16=(uint16_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value16,2u);target=sx(UINT32_C(0x002dd224));goto dispatch;
L_002dd224:
 STEP(UINT32_C(0x002dd224)); /* 04410005 regimm1 v0,002dd23c */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x002dd228));/* nop */target=sx(taken?UINT32_C(0x002dd23c):UINT32_C(0x002dd22c));goto dispatch;}
L_002dd228:
 STEP(UINT32_C(0x002dd228)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd22c));goto dispatch;
L_002dd22c:
 STEP(UINT32_C(0x002dd22c)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002dd234));STEP(UINT32_C(0x002dd230));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002dd230:
 STEP(UINT32_C(0x002dd230)); /* ae00000c sw zero,0xc(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002dd234));goto dispatch;
L_002dd234:
 STEP(UINT32_C(0x002dd234)); /* 1000000d beq zero,zero,002dd26c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dd238));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002dd26c):UINT32_C(0x002dd23c));goto dispatch;}
L_002dd238:
 STEP(UINT32_C(0x002dd238)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002dd23c));goto dispatch;
L_002dd23c:
 STEP(UINT32_C(0x002dd23c)); /* 8e02000c lw v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd240));goto dispatch;
L_002dd240:
 STEP(UINT32_C(0x002dd240)); /* 10400007 beq v0,zero,002dd260 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002dd244));set(m,17u,lo(m,21u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dd260):UINT32_C(0x002dd248));goto dispatch;}
L_002dd244:
 STEP(UINT32_C(0x002dd244)); /* 02a0882d daddu s1,s5,zero */
 set(m,17u,lo(m,21u)+lo(m,0u));target=sx(UINT32_C(0x002dd248));goto dispatch;
L_002dd248:
 STEP(UINT32_C(0x002dd248)); /* 8e24b690 lw a0,-0x4970(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0xffffb690),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dd24c));goto dispatch;
L_002dd24c:
 STEP(UINT32_C(0x002dd24c)); /* 0c0b924e jal 002e4938 */
 set(m,31u,UINT64_C(0x002dd254));STEP(UINT32_C(0x002dd250));/* nop */target=sx(UINT32_C(0x002e4938));goto dispatch;
L_002dd250:
 STEP(UINT32_C(0x002dd250)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd254));goto dispatch;
L_002dd254:
 STEP(UINT32_C(0x002dd254)); /* 8e02000c lw v0,0xc(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd258));goto dispatch;
L_002dd258:
 STEP(UINT32_C(0x002dd258)); /* 1440fffb bne v0,zero,002dd248 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dd25c));/* nop */target=sx(taken?UINT32_C(0x002dd248):UINT32_C(0x002dd260));goto dispatch;}
L_002dd25c:
 STEP(UINT32_C(0x002dd25c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd260));goto dispatch;
L_002dd260:
 STEP(UINT32_C(0x002dd260)); /* 0c0b902e jal 002e40b8 */
 set(m,31u,UINT64_C(0x002dd268));STEP(UINT32_C(0x002dd264));/* nop */target=sx(UINT32_C(0x002e40b8));goto dispatch;
L_002dd264:
 STEP(UINT32_C(0x002dd264)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd268));goto dispatch;
L_002dd268:
 STEP(UINT32_C(0x002dd268)); /* 0280102d daddu v0,s4,zero */
 set(m,2u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002dd26c));goto dispatch;
L_002dd26c:
 STEP(UINT32_C(0x002dd26c)); /* dfbf0060 ld ra,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dd270));goto dispatch;
L_002dd270:
 STEP(UINT32_C(0x002dd270)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002dd274));goto dispatch;
L_002dd274:
 STEP(UINT32_C(0x002dd274)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002dd278));goto dispatch;
L_002dd278:
 STEP(UINT32_C(0x002dd278)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002dd27c));goto dispatch;
L_002dd27c:
 STEP(UINT32_C(0x002dd27c)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002dd280));goto dispatch;
L_002dd280:
 STEP(UINT32_C(0x002dd280)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dd284));goto dispatch;
L_002dd284:
 STEP(UINT32_C(0x002dd284)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dd288));goto dispatch;
L_002dd288:
 STEP(UINT32_C(0x002dd288)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dd28c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));goto dispatch;
L_002dd28c:
 STEP(UINT32_C(0x002dd28c)); /* 27bd0070 addiu sp,sp,112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x002dd290));goto dispatch;
L_002dcfa8:
 STEP(UINT32_C(0x002dcfa8)); /* 27bdffc0 addiu sp,sp,-64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffc0)));target=sx(UINT32_C(0x002dcfac));goto dispatch;
L_002dcfac:
 STEP(UINT32_C(0x002dcfac)); /* 24020003 addiu v0,zero,3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002dcfb0));goto dispatch;
L_002dcfb0:
 STEP(UINT32_C(0x002dcfb0)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002dcfb4));goto dispatch;
L_002dcfb4:
 STEP(UINT32_C(0x002dcfb4)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002dcfb8));goto dispatch;
L_002dcfb8:
 STEP(UINT32_C(0x002dcfb8)); /* 00c0882d daddu s1,a2,zero */
 set(m,17u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002dcfbc));goto dispatch;
L_002dcfbc:
 STEP(UINT32_C(0x002dcfbc)); /* ffbf0030 sd ra,0x30(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002dcfc0));goto dispatch;
L_002dcfc0:
 STEP(UINT32_C(0x002dcfc0)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002dcfc4));goto dispatch;
L_002dcfc4:
 STEP(UINT32_C(0x002dcfc4)); /* 1082003b beq a0,v0,002dd0b4 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x002dcfc8));value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(taken?UINT32_C(0x002dd0b4):UINT32_C(0x002dcfcc));goto dispatch;}
L_002dcfc8:
 STEP(UINT32_C(0x002dcfc8)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002dcfcc));goto dispatch;
L_002dcfcc:
 STEP(UINT32_C(0x002dcfcc)); /* 28820004 slti v0,a0,4 */
 set(m,2u,((int64_t)lo(m,4u)<INT64_C(4)));target=sx(UINT32_C(0x002dcfd0));goto dispatch;
L_002dcfd0:
 STEP(UINT32_C(0x002dcfd0)); /* 14400005 bne v0,zero,002dcfe8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dcfd4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(taken?UINT32_C(0x002dcfe8):UINT32_C(0x002dcfd8));goto dispatch;}
L_002dcfd4:
 STEP(UINT32_C(0x002dcfd4)); /* 24020004 addiu v0,zero,4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002dcfd8));goto dispatch;
L_002dcfd8:
 STEP(UINT32_C(0x002dcfd8)); /* 1082004a beq a0,v0,002dd104 */
 {int taken=(lo(m,4u)==lo(m,2u));STEP(UINT32_C(0x002dcfdc));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002dd104):UINT32_C(0x002dcfe0));goto dispatch;}
L_002dcfdc:
 STEP(UINT32_C(0x002dcfdc)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dcfe0));goto dispatch;
L_002dcfe0:
 STEP(UINT32_C(0x002dcfe0)); /* 10000052 beq zero,zero,002dd12c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dcfe4));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(taken?UINT32_C(0x002dd12c):UINT32_C(0x002dcfe8));goto dispatch;}
L_002dcfe4:
 STEP(UINT32_C(0x002dcfe4)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002dcfe8));goto dispatch;
L_002dcfe8:
 STEP(UINT32_C(0x002dcfe8)); /* 1880004f blez a0,zero,002dd128 */
 {int taken=((int64_t)lo(m,4u)<=0);STEP(UINT32_C(0x002dcfec));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002dd128):UINT32_C(0x002dcff0));goto dispatch;}
L_002dcfec:
 STEP(UINT32_C(0x002dcfec)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dcff0));goto dispatch;
L_002dcff0:
 STEP(UINT32_C(0x002dcff0)); /* 52000019 beql s0,zero,002dd058 */
 if(lo(m,16u)==lo(m,0u)){STEP(UINT32_C(0x002dcff4));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,18u,sx(value32));target=sx(UINT32_C(0x002dd058));}else target=sx(UINT32_C(0x002dcff8));goto dispatch;
L_002dcff4:
 STEP(UINT32_C(0x002dcff4)); /* 8e320014 lw s2,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,18u,sx(value32));target=sx(UINT32_C(0x002dcff8));goto dispatch;
L_002dcff8:
 STEP(UINT32_C(0x002dcff8)); /* 8e220008 lw v0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dcffc));goto dispatch;
L_002dcffc:
 STEP(UINT32_C(0x002dcffc)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002dd000));goto dispatch;
L_002dd000:
 STEP(UINT32_C(0x002dd000)); /* 2c420141 sltiu v0,v0,321 */
 set(m,2u,(lo(m,2u)<UINT64_C(0x141)));target=sx(UINT32_C(0x002dd004));goto dispatch;
L_002dd004:
 STEP(UINT32_C(0x002dd004)); /* 14400003 bne v0,zero,002dd014 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002dd008));set(m,4u,sx(UINT32_C(0x00550000)));target=sx(taken?UINT32_C(0x002dd014):UINT32_C(0x002dd00c));goto dispatch;}
L_002dd008:
 STEP(UINT32_C(0x002dd008)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002dd00c));goto dispatch;
L_002dd00c:
 STEP(UINT32_C(0x002dd00c)); /* 0c0b774a jal 002ddd28 */
 set(m,31u,UINT64_C(0x002dd014));STEP(UINT32_C(0x002dd010));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffba70)));target=sx(UINT32_C(0x002ddd28));goto dispatch;
L_002dd010:
 STEP(UINT32_C(0x002dd010)); /* 2484ba70 addiu a0,a0,-17808 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffba70)));target=sx(UINT32_C(0x002dd014));goto dispatch;
L_002dd014:
 STEP(UINT32_C(0x002dd014)); /* 8e220008 lw v0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd018));goto dispatch;
L_002dd018:
 STEP(UINT32_C(0x002dd018)); /* 3206ffff andi a2,s0,0xffff */
 set(m,6u,lo(m,16u) & UINT64_C(0xffff));target=sx(UINT32_C(0x002dd01c));goto dispatch;
L_002dd01c:
 STEP(UINT32_C(0x002dd01c)); /* 8e250014 lw a1,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002dd020));goto dispatch;
L_002dd020:
 STEP(UINT32_C(0x002dd020)); /* 8e240000 lw a0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dd024));goto dispatch;
L_002dd024:
 STEP(UINT32_C(0x002dd024)); /* 0c0b9258 jal 002e4960 */
 set(m,31u,UINT64_C(0x002dd02c));STEP(UINT32_C(0x002dd028));set(m,5u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002e4960));goto dispatch;
L_002dd028:
 STEP(UINT32_C(0x002dd028)); /* 00a22821 addu a1,a1,v0 */
 set(m,5u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002dd02c));goto dispatch;
L_002dd02c:
 STEP(UINT32_C(0x002dd02c)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002dd030));goto dispatch;
L_002dd030:
 STEP(UINT32_C(0x002dd030)); /* 06010004 regimm1 s0,002dd044 */
 {int taken=((int64_t)lo(m,16u)>=0);STEP(UINT32_C(0x002dd034));/* nop */target=sx(taken?UINT32_C(0x002dd044):UINT32_C(0x002dd038));goto dispatch;}
L_002dd034:
 STEP(UINT32_C(0x002dd034)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd038));goto dispatch;
L_002dd038:
 STEP(UINT32_C(0x002dd038)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002dd03c));goto dispatch;
L_002dd03c:
 STEP(UINT32_C(0x002dd03c)); /* 0c0b774a jal 002ddd28 */
 set(m,31u,UINT64_C(0x002dd044));STEP(UINT32_C(0x002dd040));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffba98)));target=sx(UINT32_C(0x002ddd28));goto dispatch;
L_002dd040:
 STEP(UINT32_C(0x002dd040)); /* 2484ba98 addiu a0,a0,-17768 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffba98)));target=sx(UINT32_C(0x002dd044));goto dispatch;
L_002dd044:
 STEP(UINT32_C(0x002dd044)); /* 8e220008 lw v0,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd048));goto dispatch;
L_002dd048:
 STEP(UINT32_C(0x002dd048)); /* 00501021 addu v0,v0,s0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002dd04c));goto dispatch;
L_002dd04c:
 STEP(UINT32_C(0x002dd04c)); /* ae220008 sw v0,0x8(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dd050));goto dispatch;
L_002dd050:
 STEP(UINT32_C(0x002dd050)); /* 10000035 beq zero,zero,002dd128 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dd054));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002dd128):UINT32_C(0x002dd058));goto dispatch;}
L_002dd054:
 STEP(UINT32_C(0x002dd054)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dd058));goto dispatch;
L_002dd058:
 STEP(UINT32_C(0x002dd058)); /* 2410000c addiu s0,zero,12 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x002dd05c));goto dispatch;
L_002dd05c:
 STEP(UINT32_C(0x002dd05c)); /* 96420000 lhu v0,0x0(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002dd060));goto dispatch;
L_002dd060:
 STEP(UINT32_C(0x002dd060)); /* 0202102a slt v0,s0,v0 */
 set(m,2u,((int64_t)lo(m,16u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x002dd064));goto dispatch;
L_002dd064:
 STEP(UINT32_C(0x002dd064)); /* 10400010 beq v0,zero,002dd0a8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002dd068));set(m,3u,lo(m,18u)+lo(m,0u));target=sx(taken?UINT32_C(0x002dd0a8):UINT32_C(0x002dd06c));goto dispatch;}
L_002dd068:
 STEP(UINT32_C(0x002dd068)); /* 0240182d daddu v1,s2,zero */
 set(m,3u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002dd06c));goto dispatch;
L_002dd06c:
 STEP(UINT32_C(0x002dd06c)); /* 10000003 beq zero,zero,002dd07c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dd070));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000018),&value32,4u);set(m,4u,sx(value32));target=sx(taken?UINT32_C(0x002dd07c):UINT32_C(0x002dd074));goto dispatch;}
L_002dd070:
 STEP(UINT32_C(0x002dd070)); /* 8e240018 lw a0,0x18(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000018),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dd074));goto dispatch;
L_002dd074:
 STEP(UINT32_C(0x002dd074)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd078));goto dispatch;
L_002dd078:
 STEP(UINT32_C(0x002dd078)); /* 8e240018 lw a0,0x18(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000018),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dd07c));goto dispatch;
L_002dd07c:
 STEP(UINT32_C(0x002dd07c)); /* 00701021 addu v0,v1,s0 */
 set(m,2u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x002dd080));goto dispatch;
L_002dd080:
 STEP(UINT32_C(0x002dd080)); /* 90430000 lbu v1,0x0(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002dd084));goto dispatch;
L_002dd084:
 STEP(UINT32_C(0x002dd084)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dd088));goto dispatch;
L_002dd088:
 STEP(UINT32_C(0x002dd088)); /* 8c82000c lw v0,0xc(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd08c));goto dispatch;
L_002dd08c:
 STEP(UINT32_C(0x002dd08c)); /* a0430000 sb v1,0x0(v0) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002dd090));goto dispatch;
L_002dd090:
 STEP(UINT32_C(0x002dd090)); /* 0c0b73ca jal 002dcf28 */
 set(m,31u,UINT64_C(0x002dd098));STEP(UINT32_C(0x002dd094));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000018),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dcf28));goto dispatch;
L_002dd094:
 STEP(UINT32_C(0x002dd094)); /* 8e240018 lw a0,0x18(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000018),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dd098));goto dispatch;
L_002dd098:
 STEP(UINT32_C(0x002dd098)); /* 96420000 lhu v0,0x0(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00000000),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x002dd09c));goto dispatch;
L_002dd09c:
 STEP(UINT32_C(0x002dd09c)); /* 0202102a slt v0,s0,v0 */
 set(m,2u,((int64_t)lo(m,16u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x002dd0a0));goto dispatch;
L_002dd0a0:
 STEP(UINT32_C(0x002dd0a0)); /* 5440fff5 bnel v0,zero,002dd078 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x002dd0a4));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dd078));}else target=sx(UINT32_C(0x002dd0a8));goto dispatch;
L_002dd0a4:
 STEP(UINT32_C(0x002dd0a4)); /* 8e230014 lw v1,0x14(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000014),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dd0a8));goto dispatch;
L_002dd0a8:
 STEP(UINT32_C(0x002dd0a8)); /* ae200008 sw zero,0x8(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dd0ac));goto dispatch;
L_002dd0ac:
 STEP(UINT32_C(0x002dd0ac)); /* 1000001e beq zero,zero,002dd128 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dd0b0));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002dd128):UINT32_C(0x002dd0b4));goto dispatch;}
L_002dd0b0:
 STEP(UINT32_C(0x002dd0b0)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dd0b4));goto dispatch;
L_002dd0b4:
 STEP(UINT32_C(0x002dd0b4)); /* 8e260004 lw a2,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x002dd0b8));goto dispatch;
L_002dd0b8:
 STEP(UINT32_C(0x002dd0b8)); /* 8e240000 lw a0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dd0bc));goto dispatch;
L_002dd0bc:
 STEP(UINT32_C(0x002dd0bc)); /* 8e250010 lw a1,0x10(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002dd0c0));goto dispatch;
L_002dd0c0:
 STEP(UINT32_C(0x002dd0c0)); /* 0c0b9266 jal 002e4998 */
 set(m,31u,UINT64_C(0x002dd0c8));STEP(UINT32_C(0x002dd0c4));set(m,6u,lo(m,6u) & UINT64_C(0xffff));target=sx(UINT32_C(0x002e4998));goto dispatch;
L_002dd0c4:
 STEP(UINT32_C(0x002dd0c4)); /* 30c6ffff andi a2,a2,0xffff */
 set(m,6u,lo(m,6u) & UINT64_C(0xffff));target=sx(UINT32_C(0x002dd0c8));goto dispatch;
L_002dd0c8:
 STEP(UINT32_C(0x002dd0c8)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002dd0cc));goto dispatch;
L_002dd0cc:
 STEP(UINT32_C(0x002dd0cc)); /* 04a30006 regimm3 a1,002dd0e8 */
 if((int64_t)lo(m,5u)>=0){STEP(UINT32_C(0x002dd0d0));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd0e8));}else target=sx(UINT32_C(0x002dd0d4));goto dispatch;
L_002dd0d0:
 STEP(UINT32_C(0x002dd0d0)); /* 8e220010 lw v0,0x10(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd0d4));goto dispatch;
L_002dd0d4:
 STEP(UINT32_C(0x002dd0d4)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002dd0d8));goto dispatch;
L_002dd0d8:
 STEP(UINT32_C(0x002dd0d8)); /* 0c0b774a jal 002ddd28 */
 set(m,31u,UINT64_C(0x002dd0e0));STEP(UINT32_C(0x002dd0dc));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffbab0)));target=sx(UINT32_C(0x002ddd28));goto dispatch;
L_002dd0dc:
 STEP(UINT32_C(0x002dd0dc)); /* 2484bab0 addiu a0,a0,-17744 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffbab0)));target=sx(UINT32_C(0x002dd0e0));goto dispatch;
L_002dd0e0:
 STEP(UINT32_C(0x002dd0e0)); /* 1000000f beq zero,zero,002dd120 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dd0e4));/* nop */target=sx(taken?UINT32_C(0x002dd120):UINT32_C(0x002dd0e8));goto dispatch;}
L_002dd0e4:
 STEP(UINT32_C(0x002dd0e4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd0e8));goto dispatch;
L_002dd0e8:
 STEP(UINT32_C(0x002dd0e8)); /* 8e230004 lw v1,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dd0ec));goto dispatch;
L_002dd0ec:
 STEP(UINT32_C(0x002dd0ec)); /* 00451021 addu v0,v0,a1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002dd0f0));goto dispatch;
L_002dd0f0:
 STEP(UINT32_C(0x002dd0f0)); /* 00651823 subu v1,v1,a1 */
 set(m,3u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x002dd0f4));goto dispatch;
L_002dd0f4:
 STEP(UINT32_C(0x002dd0f4)); /* ae220010 sw v0,0x10(s1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002dd0f8));goto dispatch;
L_002dd0f8:
 STEP(UINT32_C(0x002dd0f8)); /* ae230004 sw v1,0x4(s1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dd0fc));goto dispatch;
L_002dd0fc:
 STEP(UINT32_C(0x002dd0fc)); /* 1000000a beq zero,zero,002dd128 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002dd100));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x002dd128):UINT32_C(0x002dd104));goto dispatch;}
L_002dd100:
 STEP(UINT32_C(0x002dd100)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dd104));goto dispatch;
L_002dd104:
 STEP(UINT32_C(0x002dd104)); /* 8e220004 lw v0,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dd108));goto dispatch;
L_002dd108:
 STEP(UINT32_C(0x002dd108)); /* 10400005 beq v0,zero,002dd120 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002dd10c));/* nop */target=sx(taken?UINT32_C(0x002dd120):UINT32_C(0x002dd110));goto dispatch;}
L_002dd10c:
 STEP(UINT32_C(0x002dd10c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dd110));goto dispatch;
L_002dd110:
 STEP(UINT32_C(0x002dd110)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002dd114));goto dispatch;
L_002dd114:
 STEP(UINT32_C(0x002dd114)); /* 8e250004 lw a1,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002dd118));goto dispatch;
L_002dd118:
 STEP(UINT32_C(0x002dd118)); /* 0c0b774a jal 002ddd28 */
 set(m,31u,UINT64_C(0x002dd120));STEP(UINT32_C(0x002dd11c));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffbac8)));target=sx(UINT32_C(0x002ddd28));goto dispatch;
L_002dd11c:
 STEP(UINT32_C(0x002dd11c)); /* 2484bac8 addiu a0,a0,-17720 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffbac8)));target=sx(UINT32_C(0x002dd120));goto dispatch;
L_002dd120:
 STEP(UINT32_C(0x002dd120)); /* ae20000c sw zero,0xc(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002dd124));goto dispatch;
L_002dd124:
 STEP(UINT32_C(0x002dd124)); /* dfbf0030 ld ra,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002dd128));goto dispatch;
L_002dd128:
 STEP(UINT32_C(0x002dd128)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002dd12c));goto dispatch;
L_002dd12c:
 STEP(UINT32_C(0x002dd12c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002dd130));goto dispatch;
L_002dd130:
 STEP(UINT32_C(0x002dd130)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002dd134));goto dispatch;
L_002dd134:
 STEP(UINT32_C(0x002dd134)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dd138));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));goto dispatch;
L_002dd138:
 STEP(UINT32_C(0x002dd138)); /* 27bd0040 addiu sp,sp,64 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000040)));target=sx(UINT32_C(0x002dd13c));goto dispatch;
L_002dcf00:
 STEP(UINT32_C(0x002dcf00)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002dcf04));goto dispatch;
L_002dcf04:
 STEP(UINT32_C(0x002dcf04)); /* 2443b580 addiu v1,v0,-19072 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb580)));target=sx(UINT32_C(0x002dcf08));goto dispatch;
L_002dcf08:
 STEP(UINT32_C(0x002dcf08)); /* ac44b580 sw a0,-0x4a80(v0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0xffffb580),&value32,4u);target=sx(UINT32_C(0x002dcf0c));goto dispatch;
L_002dcf0c:
 STEP(UINT32_C(0x002dcf0c)); /* 24640010 addiu a0,v1,16 */
 set(m,4u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002dcf10));goto dispatch;
L_002dcf10:
 STEP(UINT32_C(0x002dcf10)); /* 0060102d daddu v0,v1,zero */
 set(m,2u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x002dcf14));goto dispatch;
L_002dcf14:
 STEP(UINT32_C(0x002dcf14)); /* ac640008 sw a0,0x8(v1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dcf18));goto dispatch;
L_002dcf18:
 STEP(UINT32_C(0x002dcf18)); /* ac600004 sw zero,0x4(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dcf1c));goto dispatch;
L_002dcf1c:
 STEP(UINT32_C(0x002dcf1c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dcf20));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),&value32,4u);goto dispatch;
L_002dcf20:
 STEP(UINT32_C(0x002dcf20)); /* ac64000c sw a0,0xc(v1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002dcf24));goto dispatch;
L_002dcf28:
 STEP(UINT32_C(0x002dcf28)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002dcf2c));goto dispatch;
L_002dcf2c:
 STEP(UINT32_C(0x002dcf2c)); /* 8ca20004 lw v0,0x4(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002dcf30));goto dispatch;
L_002dcf30:
 STEP(UINT32_C(0x002dcf30)); /* 8ca4000c lw a0,0xc(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002dcf34));goto dispatch;
L_002dcf34:
 STEP(UINT32_C(0x002dcf34)); /* 8ca30000 lw v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002dcf38));goto dispatch;
L_002dcf38:
 STEP(UINT32_C(0x002dcf38)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dcf3c));goto dispatch;
L_002dcf3c:
 STEP(UINT32_C(0x002dcf3c)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002dcf40));goto dispatch;
L_002dcf40:
 STEP(UINT32_C(0x002dcf40)); /* aca20004 sw v0,0x4(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002dcf44));goto dispatch;
L_002dcf44:
 STEP(UINT32_C(0x002dcf44)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002dcf48));goto dispatch;
L_002dcf48:
 STEP(UINT32_C(0x002dcf48)); /* 00a31821 addu v1,a1,v1 */
 set(m,3u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x002dcf4c));goto dispatch;
L_002dcf4c:
 STEP(UINT32_C(0x002dcf4c)); /* 14830003 bne a0,v1,002dcf5c */
 {int taken=(lo(m,4u)!=lo(m,3u));STEP(UINT32_C(0x002dcf50));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);target=sx(taken?UINT32_C(0x002dcf5c):UINT32_C(0x002dcf54));goto dispatch;}
L_002dcf50:
 STEP(UINT32_C(0x002dcf50)); /* aca4000c sw a0,0xc(a1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002dcf54));goto dispatch;
L_002dcf54:
 STEP(UINT32_C(0x002dcf54)); /* 24a20010 addiu v0,a1,16 */
 set(m,2u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002dcf58));goto dispatch;
L_002dcf58:
 STEP(UINT32_C(0x002dcf58)); /* aca2000c sw v0,0xc(a1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002dcf5c));goto dispatch;
L_002dcf5c:
 STEP(UINT32_C(0x002dcf5c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dcf60));/* nop */goto dispatch;
L_002dcf60:
 STEP(UINT32_C(0x002dcf60)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dcf64));goto dispatch;
L_002e4898:
 STEP(UINT32_C(0x002e4898)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e489c));goto dispatch;
L_002e489c:
 STEP(UINT32_C(0x002e489c)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002e48a0));goto dispatch;
L_002e48a0:
 STEP(UINT32_C(0x002e48a0)); /* 3c032000 lui v1,zero,0x2000 */
 set(m,3u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x002e48a4));goto dispatch;
L_002e48a4:
 STEP(UINT32_C(0x002e48a4)); /* 2442eca8 addiu v0,v0,-4952 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffeca8)));target=sx(UINT32_C(0x002e48a8));goto dispatch;
L_002e48a8:
 STEP(UINT32_C(0x002e48a8)); /* 3084ffff andi a0,a0,0xffff */
 set(m,4u,lo(m,4u) & UINT64_C(0xffff));target=sx(UINT32_C(0x002e48ac));goto dispatch;
L_002e48ac:
 STEP(UINT32_C(0x002e48ac)); /* 00431025 or v0,v0,v1 */
 set(m,2u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x002e48b0));goto dispatch;
L_002e48b0:
 STEP(UINT32_C(0x002e48b0)); /* afa50004 sw a1,0x4(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002e48b4));goto dispatch;
L_002e48b4:
 STEP(UINT32_C(0x002e48b4)); /* afa40000 sw a0,0x0(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e48b8));goto dispatch;
L_002e48b8:
 STEP(UINT32_C(0x002e48b8)); /* 03a0282d daddu a1,sp,zero */
 set(m,5u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002e48bc));goto dispatch;
L_002e48bc:
 STEP(UINT32_C(0x002e48bc)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e48c0));goto dispatch;
L_002e48c0:
 STEP(UINT32_C(0x002e48c0)); /* 24040001 addiu a0,zero,1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002e48c4));goto dispatch;
L_002e48c4:
 STEP(UINT32_C(0x002e48c4)); /* afa60008 sw a2,0x8(sp) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002e48c8));goto dispatch;
L_002e48c8:
 STEP(UINT32_C(0x002e48c8)); /* 0c0b70b4 jal 002dc2d0 */
 set(m,31u,UINT64_C(0x002e48d0));STEP(UINT32_C(0x002e48cc));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002dc2d0));goto dispatch;
L_002e48cc:
 STEP(UINT32_C(0x002e48cc)); /* afa2000c sw v0,0xc(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002e48d0));goto dispatch;
L_002e48d0:
 STEP(UINT32_C(0x002e48d0)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e48d4));goto dispatch;
L_002e48d4:
 STEP(UINT32_C(0x002e48d4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e48d8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002e48d8:
 STEP(UINT32_C(0x002e48d8)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e48dc));goto dispatch;
L_002e4908:
 STEP(UINT32_C(0x002e4908)); /* 00052e00 sll a1,a1,24 */
 set(m,5u,sx((uint32_t)lo(m,5u)<<24u));target=sx(UINT32_C(0x002e490c));goto dispatch;
L_002e490c:
 STEP(UINT32_C(0x002e490c)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002e4910));goto dispatch;
L_002e4910:
 STEP(UINT32_C(0x002e4910)); /* 00052e03 sra a1,a1,24 */
 set(m,5u,sx((uint32_t)((int32_t)lo(m,5u)>>24u)));target=sx(UINT32_C(0x002e4914));goto dispatch;
L_002e4914:
 STEP(UINT32_C(0x002e4914)); /* afa40000 sw a0,0x0(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e4918));goto dispatch;
L_002e4918:
 STEP(UINT32_C(0x002e4918)); /* afa50004 sw a1,0x4(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002e491c));goto dispatch;
L_002e491c:
 STEP(UINT32_C(0x002e491c)); /* 24040003 addiu a0,zero,3 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002e4920));goto dispatch;
L_002e4920:
 STEP(UINT32_C(0x002e4920)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e4924));goto dispatch;
L_002e4924:
 STEP(UINT32_C(0x002e4924)); /* 0c0b70b4 jal 002dc2d0 */
 set(m,31u,UINT64_C(0x002e492c));STEP(UINT32_C(0x002e4928));set(m,5u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002dc2d0));goto dispatch;
L_002e4928:
 STEP(UINT32_C(0x002e4928)); /* 03a0282d daddu a1,sp,zero */
 set(m,5u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002e492c));goto dispatch;
L_002e492c:
 STEP(UINT32_C(0x002e492c)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e4930));goto dispatch;
L_002e4930:
 STEP(UINT32_C(0x002e4930)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e4934));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002e4934:
 STEP(UINT32_C(0x002e4934)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e4938));goto dispatch;
L_002e4938:
 STEP(UINT32_C(0x002e4938)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002e493c));goto dispatch;
L_002e493c:
 STEP(UINT32_C(0x002e493c)); /* afa40000 sw a0,0x0(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e4940));goto dispatch;
L_002e4940:
 STEP(UINT32_C(0x002e4940)); /* 03a0282d daddu a1,sp,zero */
 set(m,5u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002e4944));goto dispatch;
L_002e4944:
 STEP(UINT32_C(0x002e4944)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e4948));goto dispatch;
L_002e4948:
 STEP(UINT32_C(0x002e4948)); /* 0c0b70b4 jal 002dc2d0 */
 set(m,31u,UINT64_C(0x002e4950));STEP(UINT32_C(0x002e494c));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002dc2d0));goto dispatch;
L_002e494c:
 STEP(UINT32_C(0x002e494c)); /* 24040004 addiu a0,zero,4 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e4950));goto dispatch;
L_002e4950:
 STEP(UINT32_C(0x002e4950)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e4954));goto dispatch;
L_002e4954:
 STEP(UINT32_C(0x002e4954)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e4958));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002e4958:
 STEP(UINT32_C(0x002e4958)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e495c));goto dispatch;
L_002e4960:
 STEP(UINT32_C(0x002e4960)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002e4964));goto dispatch;
L_002e4964:
 STEP(UINT32_C(0x002e4964)); /* 00a0102d daddu v0,a1,zero */
 set(m,2u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002e4968));goto dispatch;
L_002e4968:
 STEP(UINT32_C(0x002e4968)); /* 30c6ffff andi a2,a2,0xffff */
 set(m,6u,lo(m,6u) & UINT64_C(0xffff));target=sx(UINT32_C(0x002e496c));goto dispatch;
L_002e496c:
 STEP(UINT32_C(0x002e496c)); /* afa40000 sw a0,0x0(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e4970));goto dispatch;
L_002e4970:
 STEP(UINT32_C(0x002e4970)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e4974));goto dispatch;
L_002e4974:
 STEP(UINT32_C(0x002e4974)); /* 03a0282d daddu a1,sp,zero */
 set(m,5u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002e4978));goto dispatch;
L_002e4978:
 STEP(UINT32_C(0x002e4978)); /* afa20004 sw v0,0x4(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002e497c));goto dispatch;
L_002e497c:
 STEP(UINT32_C(0x002e497c)); /* 2404fffb addiu a0,zero,-5 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffb)));target=sx(UINT32_C(0x002e4980));goto dispatch;
L_002e4980:
 STEP(UINT32_C(0x002e4980)); /* 0c0b70b4 jal 002dc2d0 */
 set(m,31u,UINT64_C(0x002e4988));STEP(UINT32_C(0x002e4984));value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dc2d0));goto dispatch;
L_002e4984:
 STEP(UINT32_C(0x002e4984)); /* afa60008 sw a2,0x8(sp) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002e4988));goto dispatch;
L_002e4988:
 STEP(UINT32_C(0x002e4988)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e498c));goto dispatch;
L_002e498c:
 STEP(UINT32_C(0x002e498c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e4990));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002e4990:
 STEP(UINT32_C(0x002e4990)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e4994));goto dispatch;
L_002e4998:
 STEP(UINT32_C(0x002e4998)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002e499c));goto dispatch;
L_002e499c:
 STEP(UINT32_C(0x002e499c)); /* 00a0102d daddu v0,a1,zero */
 set(m,2u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002e49a0));goto dispatch;
L_002e49a0:
 STEP(UINT32_C(0x002e49a0)); /* 30c6ffff andi a2,a2,0xffff */
 set(m,6u,lo(m,6u) & UINT64_C(0xffff));target=sx(UINT32_C(0x002e49a4));goto dispatch;
L_002e49a4:
 STEP(UINT32_C(0x002e49a4)); /* afa40000 sw a0,0x0(sp) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e49a8));goto dispatch;
L_002e49a8:
 STEP(UINT32_C(0x002e49a8)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e49ac));goto dispatch;
L_002e49ac:
 STEP(UINT32_C(0x002e49ac)); /* 03a0282d daddu a1,sp,zero */
 set(m,5u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002e49b0));goto dispatch;
L_002e49b0:
 STEP(UINT32_C(0x002e49b0)); /* afa20004 sw v0,0x4(sp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002e49b4));goto dispatch;
L_002e49b4:
 STEP(UINT32_C(0x002e49b4)); /* 2404fffa addiu a0,zero,-6 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffa)));target=sx(UINT32_C(0x002e49b8));goto dispatch;
L_002e49b8:
 STEP(UINT32_C(0x002e49b8)); /* 0c0b70b4 jal 002dc2d0 */
 set(m,31u,UINT64_C(0x002e49c0));STEP(UINT32_C(0x002e49bc));value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002dc2d0));goto dispatch;
L_002e49bc:
 STEP(UINT32_C(0x002e49bc)); /* afa60008 sw a2,0x8(sp) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002e49c0));goto dispatch;
L_002e49c0:
 STEP(UINT32_C(0x002e49c0)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e49c4));goto dispatch;
L_002e49c4:
 STEP(UINT32_C(0x002e49c4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e49c8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002e49c8:
 STEP(UINT32_C(0x002e49c8)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e49cc));goto dispatch;
L_002dc2d0:
 STEP(UINT32_C(0x002dc2d0)); /* 2403007c addiu v1,zero,124 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007c)));target=sx(UINT32_C(0x002dc2d4));goto dispatch;
L_002dc2d4:
 m->pc=UINT32_C(0x002dc2d4); /* Router executes actual SYS once. */
 return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,lo(m,3u));
L_002dc2d8:
 STEP(UINT32_C(0x002dc2d8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002dc2dc));/* nop */goto dispatch;
L_002dc2dc:
 STEP(UINT32_C(0x002dc2dc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002dc2e0));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

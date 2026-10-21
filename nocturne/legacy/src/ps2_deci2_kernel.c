#include "ps2_deci2_kernel.h"
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
uint32_t nocturneDeci2KernelResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s,NocturneDeci2PlatformState *platform)
{
 uint64_t target,value64=0,started;uint32_t value32=0,address=0;uint16_t value16=0;
 if(!platform||platform->version!=1u||platform->profile!=1u||!m||!ram||!ram->read||!ram->write||!s)return NOCTURNE_WAKEUP_INPUT_DOMAIN;
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
 case UINT32_C(0x8001123c):goto L_8001123c;
 case UINT32_C(0x80011240):goto L_80011240;
 case UINT32_C(0x80011244):goto L_80011244;
 case UINT32_C(0x80011248):goto L_80011248;
 case UINT32_C(0x8001124c):goto L_8001124c;
 case UINT32_C(0x80011250):goto L_80011250;
 case UINT32_C(0x80011254):goto L_80011254;
 case UINT32_C(0x80011258):goto L_80011258;
 case UINT32_C(0x8001125c):goto L_8001125c;
 case UINT32_C(0x80011260):goto L_80011260;
 case UINT32_C(0x80011264):goto L_80011264;
 case UINT32_C(0x80011268):goto L_80011268;
 case UINT32_C(0x8001126c):goto L_8001126c;
 case UINT32_C(0x80011270):goto L_80011270;
 case UINT32_C(0x80011274):goto L_80011274;
 case UINT32_C(0x80011278):goto L_80011278;
 case UINT32_C(0x8001127c):goto L_8001127c;
 case UINT32_C(0x80011280):goto L_80011280;
 case UINT32_C(0x80011284):goto L_80011284;
 case UINT32_C(0x80011288):goto L_80011288;
 case UINT32_C(0x8001128c):goto L_8001128c;
 case UINT32_C(0x80011290):goto L_80011290;
 case UINT32_C(0x80011294):goto L_80011294;
 case UINT32_C(0x80011298):goto L_80011298;
 case UINT32_C(0x8001129c):goto L_8001129c;
 case UINT32_C(0x800112a0):goto L_800112a0;
 case UINT32_C(0x800112a4):goto L_800112a4;
 case UINT32_C(0x800112a8):goto L_800112a8;
 case UINT32_C(0x800112ac):goto L_800112ac;
 case UINT32_C(0x800112b0):goto L_800112b0;
 case UINT32_C(0x800112b4):goto L_800112b4;
 case UINT32_C(0x800112b8):goto L_800112b8;
 case UINT32_C(0x800112bc):goto L_800112bc;
 case UINT32_C(0x80010f34):goto L_80010f34;
 case UINT32_C(0x80010f38):goto L_80010f38;
 case UINT32_C(0x80010f3c):goto L_80010f3c;
 case UINT32_C(0x80010f40):goto L_80010f40;
 case UINT32_C(0x80010f44):goto L_80010f44;
 case UINT32_C(0x80010f48):goto L_80010f48;
 case UINT32_C(0x80010f4c):goto L_80010f4c;
 case UINT32_C(0x80010f50):goto L_80010f50;
 case UINT32_C(0x80010f54):goto L_80010f54;
 case UINT32_C(0x80010f58):goto L_80010f58;
 case UINT32_C(0x80010f5c):goto L_80010f5c;
 case UINT32_C(0x80010f60):goto L_80010f60;
 case UINT32_C(0x80010f64):goto L_80010f64;
 case UINT32_C(0x80010f68):goto L_80010f68;
 case UINT32_C(0x80010f6c):goto L_80010f6c;
 case UINT32_C(0x80010f70):goto L_80010f70;
 case UINT32_C(0x80010f74):goto L_80010f74;
 case UINT32_C(0x80010f78):goto L_80010f78;
 case UINT32_C(0x80010f7c):goto L_80010f7c;
 case UINT32_C(0x80010f80):goto L_80010f80;
 case UINT32_C(0x80010f84):goto L_80010f84;
 case UINT32_C(0x80010f88):goto L_80010f88;
 case UINT32_C(0x80010f8c):goto L_80010f8c;
 case UINT32_C(0x80010f90):goto L_80010f90;
 case UINT32_C(0x80010f94):goto L_80010f94;
 case UINT32_C(0x80010f98):goto L_80010f98;
 case UINT32_C(0x80010f9c):goto L_80010f9c;
 case UINT32_C(0x80010fa0):goto L_80010fa0;
 case UINT32_C(0x80010fa4):goto L_80010fa4;
 case UINT32_C(0x80010fa8):goto L_80010fa8;
 case UINT32_C(0x80010fac):goto L_80010fac;
 case UINT32_C(0x80010fb0):goto L_80010fb0;
 case UINT32_C(0x80010fb4):goto L_80010fb4;
 case UINT32_C(0x80010fb8):goto L_80010fb8;
 case UINT32_C(0x80010fbc):goto L_80010fbc;
 case UINT32_C(0x80010fc0):goto L_80010fc0;
 case UINT32_C(0x80010fc4):goto L_80010fc4;
 case UINT32_C(0x80010fc8):goto L_80010fc8;
 case UINT32_C(0x80010fcc):goto L_80010fcc;
 case UINT32_C(0x80010fd0):goto L_80010fd0;
 case UINT32_C(0x80010fd4):goto L_80010fd4;
 case UINT32_C(0x80010fd8):goto L_80010fd8;
 case UINT32_C(0x80010fdc):goto L_80010fdc;
 case UINT32_C(0x80010fe0):goto L_80010fe0;
 case UINT32_C(0x80010fe4):goto L_80010fe4;
 case UINT32_C(0x80010fe8):goto L_80010fe8;
 case UINT32_C(0x80010fec):goto L_80010fec;
 case UINT32_C(0x80010ff0):goto L_80010ff0;
 case UINT32_C(0x80010ff4):goto L_80010ff4;
 case UINT32_C(0x80010ff8):goto L_80010ff8;
 case UINT32_C(0x80010ffc):goto L_80010ffc;
 case UINT32_C(0x80011000):goto L_80011000;
 case UINT32_C(0x80011004):goto L_80011004;
 case UINT32_C(0x80011008):goto L_80011008;
 case UINT32_C(0x8001100c):goto L_8001100c;
 case UINT32_C(0x80011010):goto L_80011010;
 case UINT32_C(0x80011014):goto L_80011014;
 case UINT32_C(0x80011018):goto L_80011018;
 case UINT32_C(0x8001101c):goto L_8001101c;
 case UINT32_C(0x80011020):goto L_80011020;
 case UINT32_C(0x80011024):goto L_80011024;
 case UINT32_C(0x80011028):goto L_80011028;
 case UINT32_C(0x8001102c):goto L_8001102c;
 case UINT32_C(0x80011030):goto L_80011030;
 case UINT32_C(0x80011034):goto L_80011034;
 case UINT32_C(0x80011038):goto L_80011038;
 case UINT32_C(0x8001103c):goto L_8001103c;
 case UINT32_C(0x80011040):goto L_80011040;
 case UINT32_C(0x80011044):goto L_80011044;
 case UINT32_C(0x80011048):goto L_80011048;
 case UINT32_C(0x8001104c):goto L_8001104c;
 case UINT32_C(0x80011050):goto L_80011050;
 case UINT32_C(0x80011054):goto L_80011054;
 case UINT32_C(0x80011058):goto L_80011058;
 case UINT32_C(0x8001105c):goto L_8001105c;
 case UINT32_C(0x80011060):goto L_80011060;
 case UINT32_C(0x80011064):goto L_80011064;
 case UINT32_C(0x80011068):goto L_80011068;
 case UINT32_C(0x8001106c):goto L_8001106c;
 case UINT32_C(0x80011070):goto L_80011070;
 case UINT32_C(0x80011074):goto L_80011074;
 case UINT32_C(0x80011078):goto L_80011078;
 case UINT32_C(0x8001107c):goto L_8001107c;
 case UINT32_C(0x80011080):goto L_80011080;
 case UINT32_C(0x80011084):goto L_80011084;
 case UINT32_C(0x80011088):goto L_80011088;
 case UINT32_C(0x8001108c):goto L_8001108c;
 case UINT32_C(0x80011090):goto L_80011090;
 case UINT32_C(0x80011094):goto L_80011094;
 case UINT32_C(0x80011098):goto L_80011098;
 case UINT32_C(0x8001109c):goto L_8001109c;
 case UINT32_C(0x800110a0):goto L_800110a0;
 case UINT32_C(0x800110a4):goto L_800110a4;
 case UINT32_C(0x800110a8):goto L_800110a8;
 case UINT32_C(0x800110ac):goto L_800110ac;
 case UINT32_C(0x800110b0):goto L_800110b0;
 case UINT32_C(0x800110b4):goto L_800110b4;
 case UINT32_C(0x800110b8):goto L_800110b8;
 case UINT32_C(0x800110bc):goto L_800110bc;
 case UINT32_C(0x800110c0):goto L_800110c0;
 case UINT32_C(0x800110c4):goto L_800110c4;
 case UINT32_C(0x800110c8):goto L_800110c8;
 case UINT32_C(0x800110cc):goto L_800110cc;
 case UINT32_C(0x800110d0):goto L_800110d0;
 case UINT32_C(0x800110d4):goto L_800110d4;
 case UINT32_C(0x800110d8):goto L_800110d8;
 case UINT32_C(0x800110dc):goto L_800110dc;
 case UINT32_C(0x800110e0):goto L_800110e0;
 case UINT32_C(0x800110e4):goto L_800110e4;
 case UINT32_C(0x800110e8):goto L_800110e8;
 case UINT32_C(0x800110ec):goto L_800110ec;
 case UINT32_C(0x800110f0):goto L_800110f0;
 case UINT32_C(0x8000be78):goto L_8000be78;
 case UINT32_C(0x8000be7c):goto L_8000be7c;
 case UINT32_C(0x8000be80):goto L_8000be80;
 case UINT32_C(0x8000be84):goto L_8000be84;
 case UINT32_C(0x8000be88):goto L_8000be88;
 case UINT32_C(0x8000be8c):goto L_8000be8c;
 case UINT32_C(0x8000be90):goto L_8000be90;
 case UINT32_C(0x8000be94):goto L_8000be94;
 case UINT32_C(0x8000be98):goto L_8000be98;
 case UINT32_C(0x8000be9c):goto L_8000be9c;
 case UINT32_C(0x8000bea0):goto L_8000bea0;
 case UINT32_C(0x8000bea4):goto L_8000bea4;
 case UINT32_C(0x8000bea8):goto L_8000bea8;
 case UINT32_C(0x8000beac):goto L_8000beac;
 case UINT32_C(0x8000beb0):goto L_8000beb0;
 case UINT32_C(0x8000beb4):goto L_8000beb4;
 case UINT32_C(0x8000beb8):goto L_8000beb8;
 case UINT32_C(0x8000bebc):goto L_8000bebc;
 case UINT32_C(0x8000bec0):goto L_8000bec0;
 case UINT32_C(0x8000bec4):goto L_8000bec4;
 case UINT32_C(0x8000bec8):goto L_8000bec8;
 case UINT32_C(0x8000becc):goto L_8000becc;
 case UINT32_C(0x8000bed0):goto L_8000bed0;
 case UINT32_C(0x8000bed4):goto L_8000bed4;
 case UINT32_C(0x8000bed8):goto L_8000bed8;
 case UINT32_C(0x8000bedc):goto L_8000bedc;
 case UINT32_C(0x8000bee0):goto L_8000bee0;
 case UINT32_C(0x8000bee4):goto L_8000bee4;
 case UINT32_C(0x8000bee8):goto L_8000bee8;
 case UINT32_C(0x8000beec):goto L_8000beec;
 case UINT32_C(0x8000bef0):goto L_8000bef0;
 case UINT32_C(0x8000bef4):goto L_8000bef4;
 case UINT32_C(0x8000bef8):goto L_8000bef8;
 case UINT32_C(0x8000befc):goto L_8000befc;
 case UINT32_C(0x8000bf00):goto L_8000bf00;
 case UINT32_C(0x8000bf04):goto L_8000bf04;
 case UINT32_C(0x8000bf08):goto L_8000bf08;
 case UINT32_C(0x8000bf0c):goto L_8000bf0c;
 case UINT32_C(0x8000bf10):goto L_8000bf10;
 case UINT32_C(0x8000bf14):goto L_8000bf14;
 case UINT32_C(0x8000bf18):goto L_8000bf18;
 case UINT32_C(0x8000bf1c):goto L_8000bf1c;
 case UINT32_C(0x8000bf20):goto L_8000bf20;
 case UINT32_C(0x8000bf24):goto L_8000bf24;
 case UINT32_C(0x8000bf28):goto L_8000bf28;
 case UINT32_C(0x8000bf2c):goto L_8000bf2c;
 case UINT32_C(0x8000bf30):goto L_8000bf30;
 case UINT32_C(0x8000bf34):goto L_8000bf34;
 case UINT32_C(0x8000bf38):goto L_8000bf38;
 case UINT32_C(0x8000bf3c):goto L_8000bf3c;
 case UINT32_C(0x8000bf40):goto L_8000bf40;
 case UINT32_C(0x8000bf44):goto L_8000bf44;
 case UINT32_C(0x8000bf48):goto L_8000bf48;
 case UINT32_C(0x8000bf4c):goto L_8000bf4c;
 case UINT32_C(0x8000bf50):goto L_8000bf50;
 case UINT32_C(0x8000bf54):goto L_8000bf54;
 case UINT32_C(0x8000bf58):goto L_8000bf58;
 case UINT32_C(0x8000bf5c):goto L_8000bf5c;
 case UINT32_C(0x8000bf60):goto L_8000bf60;
 case UINT32_C(0x8000bf64):goto L_8000bf64;
 case UINT32_C(0x8000bf68):goto L_8000bf68;
 case UINT32_C(0x8000bf6c):goto L_8000bf6c;
 case UINT32_C(0x8000bf70):goto L_8000bf70;
 case UINT32_C(0x8000bf74):goto L_8000bf74;
 case UINT32_C(0x8000bf78):goto L_8000bf78;
 case UINT32_C(0x8000bf7c):goto L_8000bf7c;
 case UINT32_C(0x8000bf80):goto L_8000bf80;
 case UINT32_C(0x8000bf84):goto L_8000bf84;
 case UINT32_C(0x8000bf88):goto L_8000bf88;
 case UINT32_C(0x8000bf8c):goto L_8000bf8c;
 case UINT32_C(0x8000bf90):goto L_8000bf90;
 case UINT32_C(0x8000bf94):goto L_8000bf94;
 case UINT32_C(0x8000bf98):goto L_8000bf98;
 case UINT32_C(0x8000bf9c):goto L_8000bf9c;
 case UINT32_C(0x8000bfa0):goto L_8000bfa0;
 case UINT32_C(0x8000bfa4):goto L_8000bfa4;
 case UINT32_C(0x8000bfa8):goto L_8000bfa8;
 case UINT32_C(0x8000bfac):goto L_8000bfac;
 case UINT32_C(0x8000bac0):goto L_8000bac0;
 case UINT32_C(0x8000bac4):goto L_8000bac4;
 case UINT32_C(0x8000bac8):goto L_8000bac8;
 case UINT32_C(0x8000bacc):goto L_8000bacc;
 case UINT32_C(0x8000bad0):goto L_8000bad0;
 case UINT32_C(0x8000bad4):goto L_8000bad4;
 case UINT32_C(0x8000bad8):goto L_8000bad8;
 case UINT32_C(0x8000badc):goto L_8000badc;
 case UINT32_C(0x8000bae0):goto L_8000bae0;
 case UINT32_C(0x8000bae4):goto L_8000bae4;
 case UINT32_C(0x8000bae8):goto L_8000bae8;
 case UINT32_C(0x8000baec):goto L_8000baec;
 case UINT32_C(0x8000baf0):goto L_8000baf0;
 case UINT32_C(0x8000baf4):goto L_8000baf4;
 case UINT32_C(0x8000baf8):goto L_8000baf8;
 case UINT32_C(0x8000bafc):goto L_8000bafc;
 case UINT32_C(0x8000bb00):goto L_8000bb00;
 case UINT32_C(0x8000bb04):goto L_8000bb04;
 case UINT32_C(0x8000bca8):goto L_8000bca8;
 case UINT32_C(0x8000bcac):goto L_8000bcac;
 case UINT32_C(0x8000bcb0):goto L_8000bcb0;
 case UINT32_C(0x8000bcb4):goto L_8000bcb4;
 case UINT32_C(0x8000bcb8):goto L_8000bcb8;
 case UINT32_C(0x8000bcbc):goto L_8000bcbc;
 case UINT32_C(0x8000bcc0):goto L_8000bcc0;
 case UINT32_C(0x8000bcc4):goto L_8000bcc4;
 case UINT32_C(0x8000bcc8):goto L_8000bcc8;
 case UINT32_C(0x8000bccc):goto L_8000bccc;
 case UINT32_C(0x8000bcd0):goto L_8000bcd0;
 case UINT32_C(0x8000bcd4):goto L_8000bcd4;
 case UINT32_C(0x8000bcd8):goto L_8000bcd8;
 case UINT32_C(0x8000bcdc):goto L_8000bcdc;
 case UINT32_C(0x8000bce0):goto L_8000bce0;
 case UINT32_C(0x8000bce4):goto L_8000bce4;
 case UINT32_C(0x8000bce8):goto L_8000bce8;
 case UINT32_C(0x8000bcec):goto L_8000bcec;
 case UINT32_C(0x8000bcf0):goto L_8000bcf0;
 case UINT32_C(0x8000bcf4):goto L_8000bcf4;
 case UINT32_C(0x8000bcf8):goto L_8000bcf8;
 case UINT32_C(0x8000bcfc):goto L_8000bcfc;
 case UINT32_C(0x8000bd00):goto L_8000bd00;
 case UINT32_C(0x8000bd04):goto L_8000bd04;
 case UINT32_C(0x8000bd08):goto L_8000bd08;
 case UINT32_C(0x8000bd0c):goto L_8000bd0c;
 case UINT32_C(0x8000bd10):goto L_8000bd10;
 case UINT32_C(0x8000bd14):goto L_8000bd14;
 case UINT32_C(0x8000bd18):goto L_8000bd18;
 case UINT32_C(0x8000bd1c):goto L_8000bd1c;
 case UINT32_C(0x8000bd20):goto L_8000bd20;
 case UINT32_C(0x8000bd24):goto L_8000bd24;
 case UINT32_C(0x8000bd28):goto L_8000bd28;
 case UINT32_C(0x8000bd2c):goto L_8000bd2c;
 case UINT32_C(0x8000bd30):goto L_8000bd30;
 case UINT32_C(0x8000bd34):goto L_8000bd34;
 case UINT32_C(0x8000bd38):goto L_8000bd38;
 case UINT32_C(0x8000bd3c):goto L_8000bd3c;
 case UINT32_C(0x8000bd40):goto L_8000bd40;
 case UINT32_C(0x8000bd44):goto L_8000bd44;
 case UINT32_C(0x8000bd48):goto L_8000bd48;
 case UINT32_C(0x8000bd4c):goto L_8000bd4c;
 case UINT32_C(0x8000bd50):goto L_8000bd50;
 case UINT32_C(0x8000bd54):goto L_8000bd54;
 case UINT32_C(0x8000bd58):goto L_8000bd58;
 case UINT32_C(0x8000bd5c):goto L_8000bd5c;
 case UINT32_C(0x8000bd60):goto L_8000bd60;
 case UINT32_C(0x8000bd64):goto L_8000bd64;
 case UINT32_C(0x8000bd68):goto L_8000bd68;
 case UINT32_C(0x8000bd6c):goto L_8000bd6c;
 case UINT32_C(0x8000bd70):goto L_8000bd70;
 case UINT32_C(0x8000bd74):goto L_8000bd74;
 case UINT32_C(0x8000bd78):goto L_8000bd78;
 case UINT32_C(0x8000bd7c):goto L_8000bd7c;
 case UINT32_C(0x8000bd80):goto L_8000bd80;
 case UINT32_C(0x8000bd84):goto L_8000bd84;
 case UINT32_C(0x8000bd88):goto L_8000bd88;
 case UINT32_C(0x8000bd8c):goto L_8000bd8c;
 case UINT32_C(0x8000bd90):goto L_8000bd90;
 case UINT32_C(0x8000bd94):goto L_8000bd94;
 case UINT32_C(0x8000bd98):goto L_8000bd98;
 case UINT32_C(0x8000bd9c):goto L_8000bd9c;
 case UINT32_C(0x8000bda0):goto L_8000bda0;
 case UINT32_C(0x8000bda4):goto L_8000bda4;
 case UINT32_C(0x8000bda8):goto L_8000bda8;
 case UINT32_C(0x8000bdac):goto L_8000bdac;
 case UINT32_C(0x8000bdb0):goto L_8000bdb0;
 case UINT32_C(0x8000bdb4):goto L_8000bdb4;
 case UINT32_C(0x8000bdb8):goto L_8000bdb8;
 case UINT32_C(0x8000bdbc):goto L_8000bdbc;
 case UINT32_C(0x8000bdc0):goto L_8000bdc0;
 case UINT32_C(0x8000bdc4):goto L_8000bdc4;
 case UINT32_C(0x8000bdc8):goto L_8000bdc8;
 case UINT32_C(0x8000bdcc):goto L_8000bdcc;
 case UINT32_C(0x8000bdd0):goto L_8000bdd0;
 case UINT32_C(0x8000bdd4):goto L_8000bdd4;
 case UINT32_C(0x8000bdd8):goto L_8000bdd8;
 case UINT32_C(0x8000bddc):goto L_8000bddc;
 case UINT32_C(0x8000bde0):goto L_8000bde0;
 case UINT32_C(0x8000bde4):goto L_8000bde4;
 case UINT32_C(0x8000bde8):goto L_8000bde8;
 case UINT32_C(0x8000bdec):goto L_8000bdec;
 case UINT32_C(0x8000bdf0):goto L_8000bdf0;
 case UINT32_C(0x8000bdf4):goto L_8000bdf4;
 case UINT32_C(0x8000bdf8):goto L_8000bdf8;
 case UINT32_C(0x8000bdfc):goto L_8000bdfc;
 case UINT32_C(0x8000be00):goto L_8000be00;
 case UINT32_C(0x8000be04):goto L_8000be04;
 case UINT32_C(0x8000be08):goto L_8000be08;
 case UINT32_C(0x8000be0c):goto L_8000be0c;
 case UINT32_C(0x8000be10):goto L_8000be10;
 case UINT32_C(0x8000be14):goto L_8000be14;
 case UINT32_C(0x8000be18):goto L_8000be18;
 case UINT32_C(0x8000be1c):goto L_8000be1c;
 case UINT32_C(0x8000be20):goto L_8000be20;
 case UINT32_C(0x8000be24):goto L_8000be24;
 case UINT32_C(0x8000be28):goto L_8000be28;
 case UINT32_C(0x8000be2c):goto L_8000be2c;
 case UINT32_C(0x8000be30):goto L_8000be30;
 case UINT32_C(0x8000be34):goto L_8000be34;
 case UINT32_C(0x8000be38):goto L_8000be38;
 case UINT32_C(0x8000be3c):goto L_8000be3c;
 case UINT32_C(0x8000be40):goto L_8000be40;
 case UINT32_C(0x8000be44):goto L_8000be44;
 case UINT32_C(0x8000be48):goto L_8000be48;
 case UINT32_C(0x8000be4c):goto L_8000be4c;
 case UINT32_C(0x8000be50):goto L_8000be50;
 case UINT32_C(0x8000be54):goto L_8000be54;
 case UINT32_C(0x8000be58):goto L_8000be58;
 case UINT32_C(0x8000be5c):goto L_8000be5c;
 case UINT32_C(0x8000be60):goto L_8000be60;
 case UINT32_C(0x8000be64):goto L_8000be64;
 case UINT32_C(0x8000be68):goto L_8000be68;
 case UINT32_C(0x8000be6c):goto L_8000be6c;
 case UINT32_C(0x8000be70):goto L_8000be70;
 case UINT32_C(0x8000be74):goto L_8000be74;
 case UINT32_C(0x8000c308):goto L_8000c308;
 case UINT32_C(0x8000c30c):goto L_8000c30c;
 case UINT32_C(0x8000c310):goto L_8000c310;
 case UINT32_C(0x8000c314):goto L_8000c314;
 case UINT32_C(0x8000c318):goto L_8000c318;
 case UINT32_C(0x8000c31c):goto L_8000c31c;
 case UINT32_C(0x8000c320):goto L_8000c320;
 case UINT32_C(0x8000c324):goto L_8000c324;
 case UINT32_C(0x8000c328):goto L_8000c328;
 case UINT32_C(0x8000c32c):goto L_8000c32c;
 case UINT32_C(0x8000c330):goto L_8000c330;
 case UINT32_C(0x8000c334):goto L_8000c334;
 case UINT32_C(0x8000c338):goto L_8000c338;
 case UINT32_C(0x8000c33c):goto L_8000c33c;
 case UINT32_C(0x8000c340):goto L_8000c340;
 case UINT32_C(0x8000c344):goto L_8000c344;
 case UINT32_C(0x8000c348):goto L_8000c348;
 case UINT32_C(0x8000c34c):goto L_8000c34c;
 case UINT32_C(0x8000c350):goto L_8000c350;
 case UINT32_C(0x8000c354):goto L_8000c354;
 case UINT32_C(0x8000c358):goto L_8000c358;
 case UINT32_C(0x8000c35c):goto L_8000c35c;
 case UINT32_C(0x8000c360):goto L_8000c360;
 case UINT32_C(0x8000c364):goto L_8000c364;
 case UINT32_C(0x8000c368):goto L_8000c368;
 case UINT32_C(0x8000c36c):goto L_8000c36c;
 case UINT32_C(0x8000c370):goto L_8000c370;
 case UINT32_C(0x8000c374):goto L_8000c374;
 case UINT32_C(0x8000c378):goto L_8000c378;
 case UINT32_C(0x8000c37c):goto L_8000c37c;
 case UINT32_C(0x8000c380):goto L_8000c380;
 case UINT32_C(0x8000c384):goto L_8000c384;
 case UINT32_C(0x8000c388):goto L_8000c388;
 case UINT32_C(0x8000c38c):goto L_8000c38c;
 case UINT32_C(0x8000c390):goto L_8000c390;
 case UINT32_C(0x8000c394):goto L_8000c394;
 case UINT32_C(0x8000c398):goto L_8000c398;
 case UINT32_C(0x8000c39c):goto L_8000c39c;
 case UINT32_C(0x8000c3a0):goto L_8000c3a0;
 case UINT32_C(0x8000c3a4):goto L_8000c3a4;
 case UINT32_C(0x8000c3a8):goto L_8000c3a8;
 case UINT32_C(0x8000c3ac):goto L_8000c3ac;
 case UINT32_C(0x8000c3b0):goto L_8000c3b0;
 case UINT32_C(0x8000c3b4):goto L_8000c3b4;
 case UINT32_C(0x8000c3b8):goto L_8000c3b8;
 case UINT32_C(0x8000c3bc):goto L_8000c3bc;
 case UINT32_C(0x8000c3c0):goto L_8000c3c0;
 case UINT32_C(0x8000c3c4):goto L_8000c3c4;
 case UINT32_C(0x8000c3c8):goto L_8000c3c8;
 case UINT32_C(0x8000c3cc):goto L_8000c3cc;
 case UINT32_C(0x8000c3d0):goto L_8000c3d0;
 case UINT32_C(0x8000c3d4):goto L_8000c3d4;
 case UINT32_C(0x8000c3d8):goto L_8000c3d8;
 case UINT32_C(0x8000c3dc):goto L_8000c3dc;
 case UINT32_C(0x8000c3e0):goto L_8000c3e0;
 case UINT32_C(0x8000c3e4):goto L_8000c3e4;
 case UINT32_C(0x8000c3e8):goto L_8000c3e8;
 case UINT32_C(0x8000c3ec):goto L_8000c3ec;
 case UINT32_C(0x8000c3f0):goto L_8000c3f0;
 case UINT32_C(0x8000c260):goto L_8000c260;
 case UINT32_C(0x8000c264):goto L_8000c264;
 case UINT32_C(0x8000c268):goto L_8000c268;
 case UINT32_C(0x8000c26c):goto L_8000c26c;
 case UINT32_C(0x8000c270):goto L_8000c270;
 case UINT32_C(0x8000c274):goto L_8000c274;
 case UINT32_C(0x8000c278):goto L_8000c278;
 case UINT32_C(0x8000c27c):goto L_8000c27c;
 case UINT32_C(0x8000c280):goto L_8000c280;
 case UINT32_C(0x8000c284):goto L_8000c284;
 case UINT32_C(0x8000c288):goto L_8000c288;
 case UINT32_C(0x8000c28c):goto L_8000c28c;
 case UINT32_C(0x8000c290):goto L_8000c290;
 case UINT32_C(0x8000c294):goto L_8000c294;
 case UINT32_C(0x8000c298):goto L_8000c298;
 case UINT32_C(0x8000c29c):goto L_8000c29c;
 case UINT32_C(0x8000c2a0):goto L_8000c2a0;
 case UINT32_C(0x8000c2a4):goto L_8000c2a4;
 case UINT32_C(0x8000c2a8):goto L_8000c2a8;
 case UINT32_C(0x8000c2ac):goto L_8000c2ac;
 case UINT32_C(0x8000c2b0):goto L_8000c2b0;
 case UINT32_C(0x8000c2b4):goto L_8000c2b4;
 case UINT32_C(0x8000c2b8):goto L_8000c2b8;
 case UINT32_C(0x8000c2bc):goto L_8000c2bc;
 case UINT32_C(0x8000c2c0):goto L_8000c2c0;
 case UINT32_C(0x8000c2c4):goto L_8000c2c4;
 case UINT32_C(0x8000c2c8):goto L_8000c2c8;
 case UINT32_C(0x8000c2cc):goto L_8000c2cc;
 case UINT32_C(0x8000c2d0):goto L_8000c2d0;
 case UINT32_C(0x8000c2d4):goto L_8000c2d4;
 case UINT32_C(0x8000c2d8):goto L_8000c2d8;
 case UINT32_C(0x8000c2dc):goto L_8000c2dc;
 case UINT32_C(0x8000c2e0):goto L_8000c2e0;
 case UINT32_C(0x8000c2e4):goto L_8000c2e4;
 case UINT32_C(0x8000c2e8):goto L_8000c2e8;
 case UINT32_C(0x8000c2ec):goto L_8000c2ec;
 case UINT32_C(0x8000c2f0):goto L_8000c2f0;
 case UINT32_C(0x8000c2f4):goto L_8000c2f4;
 case UINT32_C(0x8000c2f8):goto L_8000c2f8;
 case UINT32_C(0x8000c2fc):goto L_8000c2fc;
 case UINT32_C(0x8000c300):goto L_8000c300;
 case UINT32_C(0x8000c304):goto L_8000c304;
 case UINT32_C(0x8000c208):goto L_8000c208;
 case UINT32_C(0x8000c20c):goto L_8000c20c;
 case UINT32_C(0x8000c210):goto L_8000c210;
 case UINT32_C(0x8000c214):goto L_8000c214;
 case UINT32_C(0x8000c218):goto L_8000c218;
 case UINT32_C(0x8000c21c):goto L_8000c21c;
 case UINT32_C(0x8000c220):goto L_8000c220;
 case UINT32_C(0x8000c224):goto L_8000c224;
 case UINT32_C(0x8000c228):goto L_8000c228;
 case UINT32_C(0x8000c22c):goto L_8000c22c;
 case UINT32_C(0x8000c230):goto L_8000c230;
 case UINT32_C(0x8000c234):goto L_8000c234;
 case UINT32_C(0x8000c238):goto L_8000c238;
 case UINT32_C(0x8000c23c):goto L_8000c23c;
 case UINT32_C(0x8000c240):goto L_8000c240;
 case UINT32_C(0x8000c244):goto L_8000c244;
 case UINT32_C(0x8000c248):goto L_8000c248;
 case UINT32_C(0x8000c24c):goto L_8000c24c;
 case UINT32_C(0x8000c250):goto L_8000c250;
 case UINT32_C(0x8000c254):goto L_8000c254;
 case UINT32_C(0x8000c258):goto L_8000c258;
 case UINT32_C(0x8000ba80):goto L_8000ba80;
 case UINT32_C(0x8000ba84):goto L_8000ba84;
 case UINT32_C(0x8000ba88):goto L_8000ba88;
 case UINT32_C(0x8000ba8c):goto L_8000ba8c;
 case UINT32_C(0x8000ba90):goto L_8000ba90;
 case UINT32_C(0x8000ba94):goto L_8000ba94;
 case UINT32_C(0x8000ba98):goto L_8000ba98;
 case UINT32_C(0x8000ba9c):goto L_8000ba9c;
 case UINT32_C(0x8000baa0):goto L_8000baa0;
 case UINT32_C(0x8000baa4):goto L_8000baa4;
 case UINT32_C(0x8000baa8):goto L_8000baa8;
 case UINT32_C(0x8000baac):goto L_8000baac;
 case UINT32_C(0x8000bab0):goto L_8000bab0;
 case UINT32_C(0x8000d478):goto L_8000d478;
 case UINT32_C(0x8000d47c):goto L_8000d47c;
 case UINT32_C(0x8000d480):goto L_8000d480;
 case UINT32_C(0x8000d484):goto L_8000d484;
 case UINT32_C(0x8000d488):goto L_8000d488;
 case UINT32_C(0x8000d48c):goto L_8000d48c;
 case UINT32_C(0x8000d490):goto L_8000d490;
 case UINT32_C(0x8000d494):goto L_8000d494;
 case UINT32_C(0x8000d498):goto L_8000d498;
 case UINT32_C(0x8000d49c):goto L_8000d49c;
 case UINT32_C(0x8000d4a0):goto L_8000d4a0;
 case UINT32_C(0x8000d4a4):goto L_8000d4a4;
 case UINT32_C(0x8000d4a8):goto L_8000d4a8;
 case UINT32_C(0x8000d4ac):goto L_8000d4ac;
 case UINT32_C(0x8000d4b0):goto L_8000d4b0;
 case UINT32_C(0x8000d4b4):goto L_8000d4b4;
 case UINT32_C(0x8000d4b8):goto L_8000d4b8;
 case UINT32_C(0x8000d4bc):goto L_8000d4bc;
 case UINT32_C(0x8000d4c0):goto L_8000d4c0;
 case UINT32_C(0x8000d4c4):goto L_8000d4c4;
 case UINT32_C(0x8000d4c8):goto L_8000d4c8;
 case UINT32_C(0x8000d4cc):goto L_8000d4cc;
 case UINT32_C(0x8000d4d0):goto L_8000d4d0;
 case UINT32_C(0x8000d4d4):goto L_8000d4d4;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_8001123c:
 STEP(UINT32_C(0x8001123c)); /* 04820016 regimm2 a0,80011298 */
 if((int64_t)lo(m,4u)<0){STEP(UINT32_C(0x80011240));set(m,4u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80011298));}else target=sx(UINT32_C(0x80011244));goto dispatch;
L_80011240:
 STEP(UINT32_C(0x80011240)); /* 00042023 subu a0,zero,a0 */
 set(m,4u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80011244));goto dispatch;
L_80011244:
 STEP(UINT32_C(0x80011244)); /* 7c1bfff0 sq k1,-0x10(zero) */
 WRITE((uint32_t)lo(m,0u)+UINT32_C(0xfffffff0),m->gpr[27],16u);target=sx(UINT32_C(0x80011248));goto dispatch;
L_80011248:
 STEP(UINT32_C(0x80011248)); /* 3c1b0000 lui k1,zero,0x0 */
 set(m,27u,sx(UINT32_C(0x00000000)));target=sx(UINT32_C(0x8001124c));goto dispatch;
L_8001124c:
 STEP(UINT32_C(0x8001124c)); /* 277b8000 addiu k1,k1,-32768 */
 set(m,27u,sx((uint32_t)lo(m,27u)+UINT32_C(0xffff8000)));target=sx(UINT32_C(0x80011250));goto dispatch;
L_80011250:
 STEP(UINT32_C(0x80011250)); /* 7f7f01f0 sq ra,0x1f0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000001f0),m->gpr[31],16u);target=sx(UINT32_C(0x80011254));goto dispatch;
L_80011254:
 STEP(UINT32_C(0x80011254)); /* 7f620020 sq v0,0x20(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000020),m->gpr[2],16u);target=sx(UINT32_C(0x80011258));goto dispatch;
L_80011258:
 STEP(UINT32_C(0x80011258)); /* 7802fff0 lq v0,-0x10(zero) */
 {uint32_t q[4];READ((uint32_t)lo(m,0u)+UINT32_C(0xfffffff0),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x8001125c));goto dispatch;
L_8001125c:
 STEP(UINT32_C(0x8001125c)); /* 0c0043d6 jal 80010f58 */
 set(m,31u,UINT64_C(0x80011264));STEP(UINT32_C(0x80011260));WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000001b0),m->gpr[2],16u);target=sx(UINT32_C(0x80010f58));goto dispatch;
L_80011260:
 STEP(UINT32_C(0x80011260)); /* 7f6201b0 sq v0,0x1b0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000001b0),m->gpr[2],16u);target=sx(UINT32_C(0x80011264));goto dispatch;
L_80011264:
 STEP(UINT32_C(0x80011264)); /* 40027000 cop0 rs0 rtv0 rd14 fn0 */
 set(m,2u,sx(m->epc));target=sx(UINT32_C(0x80011268));goto dispatch;
L_80011268:
 STEP(UINT32_C(0x80011268)); /* 24420004 addiu v0,v0,4 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x8001126c));goto dispatch;
L_8001126c:
 STEP(UINT32_C(0x8001126c)); /* 0c0043cd jal 80010f34 */
 set(m,31u,UINT64_C(0x80011274));STEP(UINT32_C(0x80011270));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000230),&value32,4u);target=sx(UINT32_C(0x80010f34));goto dispatch;
L_80011270:
 STEP(UINT32_C(0x80011270)); /* af620230 sw v0,0x230(k1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000230),&value32,4u);target=sx(UINT32_C(0x80011274));goto dispatch;
L_80011274:
 STEP(UINT32_C(0x80011274)); /* 3c1d8002 lui sp,zero,0x8002 */
 set(m,29u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80011278));goto dispatch;
L_80011278:
 STEP(UINT32_C(0x80011278)); /* 27bdff50 addiu sp,sp,-176 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff50)));target=sx(UINT32_C(0x8001127c));goto dispatch;
L_8001127c:
 STEP(UINT32_C(0x8001127c)); /* 0c002f9e jal 8000be78 */
 set(m,31u,UINT64_C(0x80011284));STEP(UINT32_C(0x80011280));/* nop */target=sx(UINT32_C(0x8000be78));goto dispatch;
L_80011280:
 STEP(UINT32_C(0x80011280)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80011284));goto dispatch;
L_80011284:
 STEP(UINT32_C(0x80011284)); /* 0c00440c jal 80011030 */
 set(m,31u,UINT64_C(0x8001128c));STEP(UINT32_C(0x80011288));/* nop */target=sx(UINT32_C(0x80011030));goto dispatch;
L_80011288:
 STEP(UINT32_C(0x80011288)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8001128c));goto dispatch;
L_8001128c:
 STEP(UINT32_C(0x8001128c)); /* 7b7f01f0 lq ra,0x1f0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000001f0),q,16u);memcpy(m->gpr[31],q,16u);}target=sx(UINT32_C(0x80011290));goto dispatch;
L_80011290:
 STEP(UINT32_C(0x80011290)); /* 7b7b01b0 lq k1,0x1b0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000001b0),q,16u);memcpy(m->gpr[27],q,16u);}target=sx(UINT32_C(0x80011294));goto dispatch;
L_80011294:
 STEP(UINT32_C(0x80011294)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u){m->status&=~4u;m->pc=platform->error_epc;}else{m->status&=~2u;m->pc=m->epc;}return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80011298:
 STEP(UINT32_C(0x80011298)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x8001129c));goto dispatch;
L_8001129c:
 STEP(UINT32_C(0x8001129c)); /* 401a7000 cop0 rs0 rtk0 rd14 fn0 */
 set(m,26u,sx(m->epc));target=sx(UINT32_C(0x800112a0));goto dispatch;
L_800112a0:
 STEP(UINT32_C(0x800112a0)); /* afbf0000 sw ra,0x0(sp) */
 value32=(uint32_t)lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800112a4));goto dispatch;
L_800112a4:
 STEP(UINT32_C(0x800112a4)); /* 275a0004 addiu k0,k0,4 */
 set(m,26u,sx((uint32_t)lo(m,26u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x800112a8));goto dispatch;
L_800112a8:
 STEP(UINT32_C(0x800112a8)); /* 409a7000 cop0 rs4 rtk0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x800112ac));goto dispatch;
L_800112ac:
 STEP(UINT32_C(0x800112ac)); /* 0c002f9e jal 8000be78 */
 set(m,31u,UINT64_C(0x800112b4));STEP(UINT32_C(0x800112b0));/* nop */target=sx(UINT32_C(0x8000be78));goto dispatch;
L_800112b0:
 STEP(UINT32_C(0x800112b0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800112b4));goto dispatch;
L_800112b4:
 STEP(UINT32_C(0x800112b4)); /* 8fbf0000 lw ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,31u,sx(value32));target=sx(UINT32_C(0x800112b8));goto dispatch;
L_800112b8:
 STEP(UINT32_C(0x800112b8)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x800112bc));goto dispatch;
L_800112bc:
 STEP(UINT32_C(0x800112bc)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u){m->status&=~4u;m->pc=platform->error_epc;}else{m->status&=~2u;m->pc=m->epc;}return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80010f34:
 STEP(UINT32_C(0x80010f34)); /* 4080c800 cop0 rs4 rtzero rd25 fn0 */
 if((platform->pccr|((uint32_t)lo(m,0u)))&UINT32_C(0x80000000))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,0);platform->pccr=(uint32_t)lo(m,0u);target=sx(UINT32_C(0x80010f38));goto dispatch;
L_80010f38:
 STEP(UINT32_C(0x80010f38)); /* 4080c000 cop0 rs4 rtzero rd24 fn0 */
 /* Installed PCS profile: debug-register operation preserves all banks. */target=sx(UINT32_C(0x80010f3c));goto dispatch;
L_80010f3c:
 STEP(UINT32_C(0x80010f3c)); /* 2403ffe0 addiu v1,zero,-32 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x80010f40));goto dispatch;
L_80010f40:
 STEP(UINT32_C(0x80010f40)); /* 40026000 cop0 rs0 rtv0 rd12 fn0 */
 set(m,2u,sx(m->status&UINT32_C(0xf0c79c1f)));target=sx(UINT32_C(0x80010f44));goto dispatch;
L_80010f44:
 STEP(UINT32_C(0x80010f44)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x80010f48));goto dispatch;
L_80010f48:
 STEP(UINT32_C(0x80010f48)); /* 40826000 cop0 rs4 rtv0 rd12 fn0 */
 if(platform->pccr&UINT32_C(0x80000000))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,0);m->status=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x80010f4c));goto dispatch;
L_80010f4c:
 STEP(UINT32_C(0x80010f4c)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80010f50));goto dispatch;
L_80010f50:
 STEP(UINT32_C(0x80010f50)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80010f54));/* nop */goto dispatch;
L_80010f54:
 STEP(UINT32_C(0x80010f54)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80010f58));goto dispatch;
L_80010f58:
 STEP(UINT32_C(0x80010f58)); /* 7f600000 sq zero,0x0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000000),m->gpr[0],16u);target=sx(UINT32_C(0x80010f5c));goto dispatch;
L_80010f5c:
 STEP(UINT32_C(0x80010f5c)); /* 7f610010 sq at,0x10(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000010),m->gpr[1],16u);target=sx(UINT32_C(0x80010f60));goto dispatch;
L_80010f60:
 STEP(UINT32_C(0x80010f60)); /* 7f630030 sq v1,0x30(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000030),m->gpr[3],16u);target=sx(UINT32_C(0x80010f64));goto dispatch;
L_80010f64:
 STEP(UINT32_C(0x80010f64)); /* 7f640040 sq a0,0x40(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000040),m->gpr[4],16u);target=sx(UINT32_C(0x80010f68));goto dispatch;
L_80010f68:
 STEP(UINT32_C(0x80010f68)); /* 7f650050 sq a1,0x50(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000050),m->gpr[5],16u);target=sx(UINT32_C(0x80010f6c));goto dispatch;
L_80010f6c:
 STEP(UINT32_C(0x80010f6c)); /* 7f660060 sq a2,0x60(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000060),m->gpr[6],16u);target=sx(UINT32_C(0x80010f70));goto dispatch;
L_80010f70:
 STEP(UINT32_C(0x80010f70)); /* 7f670070 sq a3,0x70(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000070),m->gpr[7],16u);target=sx(UINT32_C(0x80010f74));goto dispatch;
L_80010f74:
 STEP(UINT32_C(0x80010f74)); /* 7f680080 sq t0,0x80(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000080),m->gpr[8],16u);target=sx(UINT32_C(0x80010f78));goto dispatch;
L_80010f78:
 STEP(UINT32_C(0x80010f78)); /* 7f690090 sq t1,0x90(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000090),m->gpr[9],16u);target=sx(UINT32_C(0x80010f7c));goto dispatch;
L_80010f7c:
 STEP(UINT32_C(0x80010f7c)); /* 7f6a00a0 sq t2,0xa0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000000a0),m->gpr[10],16u);target=sx(UINT32_C(0x80010f80));goto dispatch;
L_80010f80:
 STEP(UINT32_C(0x80010f80)); /* 7f6b00b0 sq t3,0xb0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000000b0),m->gpr[11],16u);target=sx(UINT32_C(0x80010f84));goto dispatch;
L_80010f84:
 STEP(UINT32_C(0x80010f84)); /* 7f6c00c0 sq t4,0xc0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000000c0),m->gpr[12],16u);target=sx(UINT32_C(0x80010f88));goto dispatch;
L_80010f88:
 STEP(UINT32_C(0x80010f88)); /* 7f6d00d0 sq t5,0xd0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000000d0),m->gpr[13],16u);target=sx(UINT32_C(0x80010f8c));goto dispatch;
L_80010f8c:
 STEP(UINT32_C(0x80010f8c)); /* 7f6e00e0 sq t6,0xe0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000000e0),m->gpr[14],16u);target=sx(UINT32_C(0x80010f90));goto dispatch;
L_80010f90:
 STEP(UINT32_C(0x80010f90)); /* 7f6f00f0 sq t7,0xf0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000000f0),m->gpr[15],16u);target=sx(UINT32_C(0x80010f94));goto dispatch;
L_80010f94:
 STEP(UINT32_C(0x80010f94)); /* 7f700100 sq s0,0x100(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000100),m->gpr[16],16u);target=sx(UINT32_C(0x80010f98));goto dispatch;
L_80010f98:
 STEP(UINT32_C(0x80010f98)); /* 7f710110 sq s1,0x110(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000110),m->gpr[17],16u);target=sx(UINT32_C(0x80010f9c));goto dispatch;
L_80010f9c:
 STEP(UINT32_C(0x80010f9c)); /* 7f720120 sq s2,0x120(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000120),m->gpr[18],16u);target=sx(UINT32_C(0x80010fa0));goto dispatch;
L_80010fa0:
 STEP(UINT32_C(0x80010fa0)); /* 7f730130 sq s3,0x130(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000130),m->gpr[19],16u);target=sx(UINT32_C(0x80010fa4));goto dispatch;
L_80010fa4:
 STEP(UINT32_C(0x80010fa4)); /* 7f740140 sq s4,0x140(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000140),m->gpr[20],16u);target=sx(UINT32_C(0x80010fa8));goto dispatch;
L_80010fa8:
 STEP(UINT32_C(0x80010fa8)); /* 7f750150 sq s5,0x150(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000150),m->gpr[21],16u);target=sx(UINT32_C(0x80010fac));goto dispatch;
L_80010fac:
 STEP(UINT32_C(0x80010fac)); /* 7f760160 sq s6,0x160(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000160),m->gpr[22],16u);target=sx(UINT32_C(0x80010fb0));goto dispatch;
L_80010fb0:
 STEP(UINT32_C(0x80010fb0)); /* 7f770170 sq s7,0x170(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000170),m->gpr[23],16u);target=sx(UINT32_C(0x80010fb4));goto dispatch;
L_80010fb4:
 STEP(UINT32_C(0x80010fb4)); /* 7f780180 sq t8,0x180(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000180),m->gpr[24],16u);target=sx(UINT32_C(0x80010fb8));goto dispatch;
L_80010fb8:
 STEP(UINT32_C(0x80010fb8)); /* 7f790190 sq t9,0x190(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000190),m->gpr[25],16u);target=sx(UINT32_C(0x80010fbc));goto dispatch;
L_80010fbc:
 STEP(UINT32_C(0x80010fbc)); /* 7f7a01a0 sq k0,0x1a0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000001a0),m->gpr[26],16u);target=sx(UINT32_C(0x80010fc0));goto dispatch;
L_80010fc0:
 STEP(UINT32_C(0x80010fc0)); /* 7f7c01c0 sq gp,0x1c0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000001c0),m->gpr[28],16u);target=sx(UINT32_C(0x80010fc4));goto dispatch;
L_80010fc4:
 STEP(UINT32_C(0x80010fc4)); /* 7f7d01d0 sq sp,0x1d0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000001d0),m->gpr[29],16u);target=sx(UINT32_C(0x80010fc8));goto dispatch;
L_80010fc8:
 STEP(UINT32_C(0x80010fc8)); /* 7f7e01e0 sq s8,0x1e0(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x000001e0),m->gpr[30],16u);target=sx(UINT32_C(0x80010fcc));goto dispatch;
L_80010fcc:
 STEP(UINT32_C(0x80010fcc)); /* 70001209 mmi 70001209 */
 {uint32_t q[4]={(uint32_t)m->hi,(uint32_t)(m->hi>>32),(uint32_t)m->hi1,(uint32_t)(m->hi1>>32)};memcpy(m->gpr[2],q,16);}target=sx(UINT32_C(0x80010fd0));goto dispatch;
L_80010fd0:
 STEP(UINT32_C(0x80010fd0)); /* 70001a49 mmi 70001a49 */
 {uint32_t q[4]={(uint32_t)m->lo,(uint32_t)(m->lo>>32),(uint32_t)m->lo1,(uint32_t)(m->lo1>>32)};memcpy(m->gpr[3],q,16);}target=sx(UINT32_C(0x80010fd4));goto dispatch;
L_80010fd4:
 STEP(UINT32_C(0x80010fd4)); /* 7062c389 mmi 7062c389 */
 {uint32_t out[4]={m->gpr[2][0],m->gpr[2][1],m->gpr[3][0],m->gpr[3][1]};memcpy(m->gpr[24],out,16);}target=sx(UINT32_C(0x80010fd8));goto dispatch;
L_80010fd8:
 STEP(UINT32_C(0x80010fd8)); /* 7043cba9 mmi 7043cba9 */
 {uint32_t out[4]={m->gpr[2][2],m->gpr[2][3],m->gpr[3][2],m->gpr[3][3]};memcpy(m->gpr[25],out,16);}target=sx(UINT32_C(0x80010fdc));goto dispatch;
L_80010fdc:
 STEP(UINT32_C(0x80010fdc)); /* 7f780200 sq t8,0x200(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000200),m->gpr[24],16u);target=sx(UINT32_C(0x80010fe0));goto dispatch;
L_80010fe0:
 STEP(UINT32_C(0x80010fe0)); /* 7f790210 sq t9,0x210(k1) */
 WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000210),m->gpr[25],16u);target=sx(UINT32_C(0x80010fe4));goto dispatch;
L_80010fe4:
 STEP(UINT32_C(0x80010fe4)); /* 00001028 mfsa v0 */
 set(m,2u,(uint64_t)m->sa);target=sx(UINT32_C(0x80010fe8));goto dispatch;
L_80010fe8:
 STEP(UINT32_C(0x80010fe8)); /* 40034000 cop0 rs0 rtv1 rd8 fn0 */
 set(m,3u,sx(platform->bad_vaddr));target=sx(UINT32_C(0x80010fec));goto dispatch;
L_80010fec:
 STEP(UINT32_C(0x80010fec)); /* 40186000 cop0 rs0 rtt8 rd12 fn0 */
 set(m,24u,sx(m->status&UINT32_C(0xf0c79c1f)));target=sx(UINT32_C(0x80010ff0));goto dispatch;
L_80010ff0:
 STEP(UINT32_C(0x80010ff0)); /* 40196800 cop0 rs0 rtt9 rd13 fn0 */
 set(m,25u,sx(m->cause));target=sx(UINT32_C(0x80010ff4));goto dispatch;
L_80010ff4:
 STEP(UINT32_C(0x80010ff4)); /* 70621488 mmi 70621488 */
 {uint32_t q[4]={m->gpr[2][0],m->gpr[3][0],m->gpr[2][1],m->gpr[3][1]};memcpy(m->gpr[2],q,16);}target=sx(UINT32_C(0x80010ff8));goto dispatch;
L_80010ff8:
 STEP(UINT32_C(0x80010ff8)); /* 7338c488 mmi 7338c488 */
 {uint32_t q[4]={m->gpr[24][0],m->gpr[25][0],m->gpr[24][1],m->gpr[25][1]};memcpy(m->gpr[24],q,16);}target=sx(UINT32_C(0x80010ffc));goto dispatch;
L_80010ffc:
 STEP(UINT32_C(0x80010ffc)); /* ff620220 sd v0,0x220(k1) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000220),&value64,8u);target=sx(UINT32_C(0x80011000));goto dispatch;
L_80011000:
 STEP(UINT32_C(0x80011000)); /* ff780228 sd t8,0x228(k1) */
 value64=lo(m,24u);WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000228),&value64,8u);target=sx(UINT32_C(0x80011004));goto dispatch;
L_80011004:
 STEP(UINT32_C(0x80011004)); /* 40027000 cop0 rs0 rtv0 rd14 fn0 */
 set(m,2u,sx(m->epc));target=sx(UINT32_C(0x80011008));goto dispatch;
L_80011008:
 STEP(UINT32_C(0x80011008)); /* 4003b800 cop0 rs0 rtv1 rd23 fn0 */
 set(m,3u,sx(platform->rd23));target=sx(UINT32_C(0x8001100c));goto dispatch;
L_8001100c:
 STEP(UINT32_C(0x8001100c)); /* 4018c000 cop0 rs0 rtt8 rd24 fn0 */
 /* Installed PCS profile: debug-register operation preserves all banks. */target=sx(UINT32_C(0x80011010));goto dispatch;
L_80011010:
 STEP(UINT32_C(0x80011010)); /* 4019c800 cop0 rs0 rtt9 rd25 fn0 */
 set(m,25u,sx(platform->pccr));target=sx(UINT32_C(0x80011014));goto dispatch;
L_80011014:
 STEP(UINT32_C(0x80011014)); /* 70621488 mmi 70621488 */
 {uint32_t q[4]={m->gpr[2][0],m->gpr[3][0],m->gpr[2][1],m->gpr[3][1]};memcpy(m->gpr[2],q,16);}target=sx(UINT32_C(0x80011018));goto dispatch;
L_80011018:
 STEP(UINT32_C(0x80011018)); /* 7338c488 mmi 7338c488 */
 {uint32_t q[4]={m->gpr[24][0],m->gpr[25][0],m->gpr[24][1],m->gpr[25][1]};memcpy(m->gpr[24],q,16);}target=sx(UINT32_C(0x8001101c));goto dispatch;
L_8001101c:
 STEP(UINT32_C(0x8001101c)); /* ff620230 sd v0,0x230(k1) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000230),&value64,8u);target=sx(UINT32_C(0x80011020));goto dispatch;
L_80011020:
 STEP(UINT32_C(0x80011020)); /* ff780238 sd t8,0x238(k1) */
 value64=lo(m,24u);WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000238),&value64,8u);target=sx(UINT32_C(0x80011024));goto dispatch;
L_80011024:
 STEP(UINT32_C(0x80011024)); /* 4002f000 cop0 rs0 rtv0 rd30 fn0 */
 set(m,2u,sx(platform->error_epc));target=sx(UINT32_C(0x80011028));goto dispatch;
L_80011028:
 STEP(UINT32_C(0x80011028)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8001102c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000240),&value32,4u);goto dispatch;
L_8001102c:
 STEP(UINT32_C(0x8001102c)); /* af620240 sw v0,0x240(k1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,27u)+UINT32_C(0x00000240),&value32,4u);target=sx(UINT32_C(0x80011030));goto dispatch;
L_80011030:
 STEP(UINT32_C(0x80011030)); /* 8f620228 lw v0,0x228(k1) */
 READ((uint32_t)lo(m,27u)+UINT32_C(0x00000228),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80011034));goto dispatch;
L_80011034:
 STEP(UINT32_C(0x80011034)); /* 8f630240 lw v1,0x240(k1) */
 READ((uint32_t)lo(m,27u)+UINT32_C(0x00000240),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80011038));goto dispatch;
L_80011038:
 STEP(UINT32_C(0x80011038)); /* 40826000 cop0 rs4 rtv0 rd12 fn0 */
 if(platform->pccr&UINT32_C(0x80000000))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,0);m->status=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x8001103c));goto dispatch;
L_8001103c:
 STEP(UINT32_C(0x8001103c)); /* 4083f000 cop0 rs4 rtv1 rd30 fn0 */
 platform->error_epc=(uint32_t)lo(m,3u);target=sx(UINT32_C(0x80011040));goto dispatch;
L_80011040:
 STEP(UINT32_C(0x80011040)); /* df620238 ld v0,0x238(k1) */
 READ((uint32_t)lo(m,27u)+UINT32_C(0x00000238),&value64,8u);set(m,2u,value64);target=sx(UINT32_C(0x80011044));goto dispatch;
L_80011044:
 STEP(UINT32_C(0x80011044)); /* 4082c000 cop0 rs4 rtv0 rd24 fn0 */
 /* Installed PCS profile: debug-register operation preserves all banks. */target=sx(UINT32_C(0x80011048));goto dispatch;
L_80011048:
 STEP(UINT32_C(0x80011048)); /* 0002103f dsra32 v0,v0,0 */
 set(m,2u,(uint64_t)((int64_t)lo(m,2u)>>32u));target=sx(UINT32_C(0x8001104c));goto dispatch;
L_8001104c:
 STEP(UINT32_C(0x8001104c)); /* 4082c800 cop0 rs4 rtv0 rd25 fn0 */
 if((platform->pccr|((uint32_t)lo(m,2u)))&UINT32_C(0x80000000))return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,0);platform->pccr=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x80011050));goto dispatch;
L_80011050:
 STEP(UINT32_C(0x80011050)); /* 8f620230 lw v0,0x230(k1) */
 READ((uint32_t)lo(m,27u)+UINT32_C(0x00000230),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80011054));goto dispatch;
L_80011054:
 STEP(UINT32_C(0x80011054)); /* 8f630220 lw v1,0x220(k1) */
 READ((uint32_t)lo(m,27u)+UINT32_C(0x00000220),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80011058));goto dispatch;
L_80011058:
 STEP(UINT32_C(0x80011058)); /* 40827000 cop0 rs4 rtv0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x8001105c));goto dispatch;
L_8001105c:
 STEP(UINT32_C(0x8001105c)); /* 00600029 mtsa v1 */
 m->sa=(uint32_t)lo(m,3u);target=sx(UINT32_C(0x80011060));goto dispatch;
L_80011060:
 STEP(UINT32_C(0x80011060)); /* 7b620200 lq v0,0x200(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000200),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x80011064));goto dispatch;
L_80011064:
 STEP(UINT32_C(0x80011064)); /* 7b630210 lq v1,0x210(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000210),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x80011068));goto dispatch;
L_80011068:
 STEP(UINT32_C(0x80011068)); /* 70622389 mmi 70622389 */
 {uint32_t out[4]={m->gpr[2][0],m->gpr[2][1],m->gpr[3][0],m->gpr[3][1]};memcpy(m->gpr[4],out,16);}target=sx(UINT32_C(0x8001106c));goto dispatch;
L_8001106c:
 STEP(UINT32_C(0x8001106c)); /* 70432ba9 mmi 70432ba9 */
 {uint32_t out[4]={m->gpr[2][2],m->gpr[2][3],m->gpr[3][2],m->gpr[3][3]};memcpy(m->gpr[5],out,16);}target=sx(UINT32_C(0x80011070));goto dispatch;
L_80011070:
 STEP(UINT32_C(0x80011070)); /* 70800229 mmi 70800229 */
 m->hi=lo(m,4u);m->hi1=(uint64_t)m->gpr[4][2]|((uint64_t)m->gpr[4][3]<<32);target=sx(UINT32_C(0x80011074));goto dispatch;
L_80011074:
 STEP(UINT32_C(0x80011074)); /* 70a00269 mmi 70a00269 */
 m->lo=lo(m,5u);m->lo1=(uint64_t)m->gpr[5][2]|((uint64_t)m->gpr[5][3]<<32);target=sx(UINT32_C(0x80011078));goto dispatch;
L_80011078:
 STEP(UINT32_C(0x80011078)); /* 7b610010 lq at,0x10(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000010),q,16u);memcpy(m->gpr[1],q,16u);}target=sx(UINT32_C(0x8001107c));goto dispatch;
L_8001107c:
 STEP(UINT32_C(0x8001107c)); /* 7b620020 lq v0,0x20(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000020),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x80011080));goto dispatch;
L_80011080:
 STEP(UINT32_C(0x80011080)); /* 7b630030 lq v1,0x30(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000030),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x80011084));goto dispatch;
L_80011084:
 STEP(UINT32_C(0x80011084)); /* 7b640040 lq a0,0x40(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000040),q,16u);memcpy(m->gpr[4],q,16u);}target=sx(UINT32_C(0x80011088));goto dispatch;
L_80011088:
 STEP(UINT32_C(0x80011088)); /* 7b650050 lq a1,0x50(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000050),q,16u);memcpy(m->gpr[5],q,16u);}target=sx(UINT32_C(0x8001108c));goto dispatch;
L_8001108c:
 STEP(UINT32_C(0x8001108c)); /* 7b660060 lq a2,0x60(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000060),q,16u);memcpy(m->gpr[6],q,16u);}target=sx(UINT32_C(0x80011090));goto dispatch;
L_80011090:
 STEP(UINT32_C(0x80011090)); /* 7b670070 lq a3,0x70(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000070),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x80011094));goto dispatch;
L_80011094:
 STEP(UINT32_C(0x80011094)); /* 7b680080 lq t0,0x80(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000080),q,16u);memcpy(m->gpr[8],q,16u);}target=sx(UINT32_C(0x80011098));goto dispatch;
L_80011098:
 STEP(UINT32_C(0x80011098)); /* 7b690090 lq t1,0x90(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000090),q,16u);memcpy(m->gpr[9],q,16u);}target=sx(UINT32_C(0x8001109c));goto dispatch;
L_8001109c:
 STEP(UINT32_C(0x8001109c)); /* 7b6a00a0 lq t2,0xa0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000000a0),q,16u);memcpy(m->gpr[10],q,16u);}target=sx(UINT32_C(0x800110a0));goto dispatch;
L_800110a0:
 STEP(UINT32_C(0x800110a0)); /* 7b6b00b0 lq t3,0xb0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000000b0),q,16u);memcpy(m->gpr[11],q,16u);}target=sx(UINT32_C(0x800110a4));goto dispatch;
L_800110a4:
 STEP(UINT32_C(0x800110a4)); /* 7b6c00c0 lq t4,0xc0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000000c0),q,16u);memcpy(m->gpr[12],q,16u);}target=sx(UINT32_C(0x800110a8));goto dispatch;
L_800110a8:
 STEP(UINT32_C(0x800110a8)); /* 7b6d00d0 lq t5,0xd0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000000d0),q,16u);memcpy(m->gpr[13],q,16u);}target=sx(UINT32_C(0x800110ac));goto dispatch;
L_800110ac:
 STEP(UINT32_C(0x800110ac)); /* 7b6e00e0 lq t6,0xe0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000000e0),q,16u);memcpy(m->gpr[14],q,16u);}target=sx(UINT32_C(0x800110b0));goto dispatch;
L_800110b0:
 STEP(UINT32_C(0x800110b0)); /* 7b6f00f0 lq t7,0xf0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000000f0),q,16u);memcpy(m->gpr[15],q,16u);}target=sx(UINT32_C(0x800110b4));goto dispatch;
L_800110b4:
 STEP(UINT32_C(0x800110b4)); /* 7b700100 lq s0,0x100(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000100),q,16u);memcpy(m->gpr[16],q,16u);}target=sx(UINT32_C(0x800110b8));goto dispatch;
L_800110b8:
 STEP(UINT32_C(0x800110b8)); /* 7b710110 lq s1,0x110(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000110),q,16u);memcpy(m->gpr[17],q,16u);}target=sx(UINT32_C(0x800110bc));goto dispatch;
L_800110bc:
 STEP(UINT32_C(0x800110bc)); /* 7b720120 lq s2,0x120(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000120),q,16u);memcpy(m->gpr[18],q,16u);}target=sx(UINT32_C(0x800110c0));goto dispatch;
L_800110c0:
 STEP(UINT32_C(0x800110c0)); /* 7b730130 lq s3,0x130(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000130),q,16u);memcpy(m->gpr[19],q,16u);}target=sx(UINT32_C(0x800110c4));goto dispatch;
L_800110c4:
 STEP(UINT32_C(0x800110c4)); /* 7b740140 lq s4,0x140(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000140),q,16u);memcpy(m->gpr[20],q,16u);}target=sx(UINT32_C(0x800110c8));goto dispatch;
L_800110c8:
 STEP(UINT32_C(0x800110c8)); /* 7b750150 lq s5,0x150(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000150),q,16u);memcpy(m->gpr[21],q,16u);}target=sx(UINT32_C(0x800110cc));goto dispatch;
L_800110cc:
 STEP(UINT32_C(0x800110cc)); /* 7b760160 lq s6,0x160(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000160),q,16u);memcpy(m->gpr[22],q,16u);}target=sx(UINT32_C(0x800110d0));goto dispatch;
L_800110d0:
 STEP(UINT32_C(0x800110d0)); /* 7b770170 lq s7,0x170(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000170),q,16u);memcpy(m->gpr[23],q,16u);}target=sx(UINT32_C(0x800110d4));goto dispatch;
L_800110d4:
 STEP(UINT32_C(0x800110d4)); /* 7b780180 lq t8,0x180(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000180),q,16u);memcpy(m->gpr[24],q,16u);}target=sx(UINT32_C(0x800110d8));goto dispatch;
L_800110d8:
 STEP(UINT32_C(0x800110d8)); /* 7b790190 lq t9,0x190(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x00000190),q,16u);memcpy(m->gpr[25],q,16u);}target=sx(UINT32_C(0x800110dc));goto dispatch;
L_800110dc:
 STEP(UINT32_C(0x800110dc)); /* 7b7a01a0 lq k0,0x1a0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000001a0),q,16u);memcpy(m->gpr[26],q,16u);}target=sx(UINT32_C(0x800110e0));goto dispatch;
L_800110e0:
 STEP(UINT32_C(0x800110e0)); /* 7b7c01c0 lq gp,0x1c0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000001c0),q,16u);memcpy(m->gpr[28],q,16u);}target=sx(UINT32_C(0x800110e4));goto dispatch;
L_800110e4:
 STEP(UINT32_C(0x800110e4)); /* 7b7d01d0 lq sp,0x1d0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000001d0),q,16u);memcpy(m->gpr[29],q,16u);}target=sx(UINT32_C(0x800110e8));goto dispatch;
L_800110e8:
 STEP(UINT32_C(0x800110e8)); /* 7b7e01e0 lq s8,0x1e0(k1) */
 {uint32_t q[4];READ((uint32_t)lo(m,27u)+UINT32_C(0x000001e0),q,16u);memcpy(m->gpr[30],q,16u);}target=sx(UINT32_C(0x800110ec));goto dispatch;
L_800110ec:
 STEP(UINT32_C(0x800110ec)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800110f0));/* nop */goto dispatch;
L_800110f0:
 STEP(UINT32_C(0x800110f0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800110f4));goto dispatch;
L_8000be78:
 STEP(UINT32_C(0x8000be78)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x8000be7c));goto dispatch;
L_8000be7c:
 STEP(UINT32_C(0x8000be7c)); /* 2483ffff addiu v1,a0,-1 */
 set(m,3u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x8000be80));goto dispatch;
L_8000be80:
 STEP(UINT32_C(0x8000be80)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000be84));goto dispatch;
L_8000be84:
 STEP(UINT32_C(0x8000be84)); /* 2c620010 sltiu v0,v1,16 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x10)));target=sx(UINT32_C(0x8000be88));goto dispatch;
L_8000be88:
 STEP(UINT32_C(0x8000be88)); /* 1040003f beq v0,zero,8000bf88 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x8000be8c));set(m,7u,lo(m,5u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000bf88):UINT32_C(0x8000be90));goto dispatch;}
L_8000be8c:
 STEP(UINT32_C(0x8000be8c)); /* 00a0382d daddu a3,a1,zero */
 set(m,7u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x8000be90));goto dispatch;
L_8000be90:
 STEP(UINT32_C(0x8000be90)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000be94));goto dispatch;
L_8000be94:
 STEP(UINT32_C(0x8000be94)); /* 00031880 sll v1,v1,2 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<2u));target=sx(UINT32_C(0x8000be98));goto dispatch;
L_8000be98:
 STEP(UINT32_C(0x8000be98)); /* 24423280 addiu v0,v0,12928 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00003280)));target=sx(UINT32_C(0x8000be9c));goto dispatch;
L_8000be9c:
 STEP(UINT32_C(0x8000be9c)); /* 00621821 addu v1,v1,v0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x8000bea0));goto dispatch;
L_8000bea0:
 STEP(UINT32_C(0x8000bea0)); /* 8c640000 lw a0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bea4));goto dispatch;
L_8000bea4:
 STEP(UINT32_C(0x8000bea4)); /* 00800008 jr a0 */
 target=sx((uint32_t)lo(m,4u));STEP(UINT32_C(0x8000bea8));/* nop */goto dispatch;
L_8000bea8:
 STEP(UINT32_C(0x8000bea8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000beac));goto dispatch;
L_8000beac:
 STEP(UINT32_C(0x8000beac)); /* 8ce60008 lw a2,0x8(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x8000beb0));goto dispatch;
L_8000beb0:
 STEP(UINT32_C(0x8000beb0)); /* 94e40000 lhu a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value16,2u);set(m,4u,value16);target=sx(UINT32_C(0x8000beb4));goto dispatch;
L_8000beb4:
 STEP(UINT32_C(0x8000beb4)); /* 0c002f2a jal 8000bca8 */
 set(m,31u,UINT64_C(0x8000bebc));STEP(UINT32_C(0x8000beb8));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000bca8));goto dispatch;
L_8000beb8:
 STEP(UINT32_C(0x8000beb8)); /* 8ce50004 lw a1,0x4(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000bebc));goto dispatch;
L_8000bebc:
 STEP(UINT32_C(0x8000bebc)); /* 10000009 beq zero,zero,8000bee4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bec0));set(m,3u,sx(UINT32_C(0x00000000)));target=sx(taken?UINT32_C(0x8000bee4):UINT32_C(0x8000bec4));goto dispatch;}
L_8000bec0:
 STEP(UINT32_C(0x8000bec0)); /* 3c030000 lui v1,zero,0x0 */
 set(m,3u,sx(UINT32_C(0x00000000)));target=sx(UINT32_C(0x8000bec4));goto dispatch;
L_8000bec4:
 STEP(UINT32_C(0x8000bec4)); /* 0c002f58 jal 8000bd60 */
 set(m,31u,UINT64_C(0x8000becc));STEP(UINT32_C(0x8000bec8));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bd60));goto dispatch;
L_8000bec8:
 STEP(UINT32_C(0x8000bec8)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000becc));goto dispatch;
L_8000becc:
 STEP(UINT32_C(0x8000becc)); /* 10000005 beq zero,zero,8000bee4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bed0));set(m,3u,sx(UINT32_C(0x00000000)));target=sx(taken?UINT32_C(0x8000bee4):UINT32_C(0x8000bed4));goto dispatch;}
L_8000bed0:
 STEP(UINT32_C(0x8000bed0)); /* 3c030000 lui v1,zero,0x0 */
 set(m,3u,sx(UINT32_C(0x00000000)));target=sx(UINT32_C(0x8000bed4));goto dispatch;
L_8000bed4:
 STEP(UINT32_C(0x8000bed4)); /* 80e50004 lb a1,0x4(a3) */
 {uint8_t byte;READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&byte,1u);set(m,5u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x8000bed8));goto dispatch;
L_8000bed8:
 STEP(UINT32_C(0x8000bed8)); /* 0c004282 jal 80010a08 */
 set(m,31u,UINT64_C(0x8000bee0));STEP(UINT32_C(0x8000bedc));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010a08));goto dispatch;
L_8000bedc:
 STEP(UINT32_C(0x8000bedc)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bee0));goto dispatch;
L_8000bee0:
 STEP(UINT32_C(0x8000bee0)); /* 3c030000 lui v1,zero,0x0 */
 set(m,3u,sx(UINT32_C(0x00000000)));target=sx(UINT32_C(0x8000bee4));goto dispatch;
L_8000bee4:
 STEP(UINT32_C(0x8000bee4)); /* 24648000 addiu a0,v1,-32768 */
 set(m,4u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffff8000)));target=sx(UINT32_C(0x8000bee8));goto dispatch;
L_8000bee8:
 STEP(UINT32_C(0x8000bee8)); /* 0060282d daddu a1,v1,zero */
 set(m,5u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x8000beec));goto dispatch;
L_8000beec:
 STEP(UINT32_C(0x8000beec)); /* 1000002b beq zero,zero,8000bf9c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bef0));value64=lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000020),&value64,8u);target=sx(taken?UINT32_C(0x8000bf9c):UINT32_C(0x8000bef4));goto dispatch;}
L_8000bef0:
 STEP(UINT32_C(0x8000bef0)); /* fc820020 sd v0,0x20(a0) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000bef4));goto dispatch;
L_8000bef4:
 STEP(UINT32_C(0x8000bef4)); /* 0c0033e2 jal 8000cf88 */
 set(m,31u,UINT64_C(0x8000befc));STEP(UINT32_C(0x8000bef8));/* nop */target=sx(UINT32_C(0x8000cf88));goto dispatch;
L_8000bef8:
 STEP(UINT32_C(0x8000bef8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000befc));goto dispatch;
L_8000befc:
 STEP(UINT32_C(0x8000befc)); /* 0c003db8 jal 8000f6e0 */
 set(m,31u,UINT64_C(0x8000bf04));STEP(UINT32_C(0x8000bf00));set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000f6e0));goto dispatch;
L_8000bf00:
 STEP(UINT32_C(0x8000bf00)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000bf04));goto dispatch;
L_8000bf04:
 STEP(UINT32_C(0x8000bf04)); /* 10000025 beq zero,zero,8000bf9c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bf08));set(m,5u,sx(UINT32_C(0x00000000)));target=sx(taken?UINT32_C(0x8000bf9c):UINT32_C(0x8000bf0c));goto dispatch;}
L_8000bf08:
 STEP(UINT32_C(0x8000bf08)); /* 3c050000 lui a1,zero,0x0 */
 set(m,5u,sx(UINT32_C(0x00000000)));target=sx(UINT32_C(0x8000bf0c));goto dispatch;
L_8000bf0c:
 STEP(UINT32_C(0x8000bf0c)); /* 94e60008 lhu a2,0x8(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value16,2u);set(m,6u,value16);target=sx(UINT32_C(0x8000bf10));goto dispatch;
L_8000bf10:
 STEP(UINT32_C(0x8000bf10)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bf14));goto dispatch;
L_8000bf14:
 STEP(UINT32_C(0x8000bf14)); /* 0c0032ac jal 8000cab0 */
 set(m,31u,UINT64_C(0x8000bf1c));STEP(UINT32_C(0x8000bf18));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000cab0));goto dispatch;
L_8000bf18:
 STEP(UINT32_C(0x8000bf18)); /* 8ce50004 lw a1,0x4(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000bf1c));goto dispatch;
L_8000bf1c:
 STEP(UINT32_C(0x8000bf1c)); /* 10000021 beq zero,zero,8000bfa4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bf20));set(m,2u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000bfa4):UINT32_C(0x8000bf24));goto dispatch;}
L_8000bf20:
 STEP(UINT32_C(0x8000bf20)); /* 0040102d daddu v0,v0,zero */
 set(m,2u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000bf24));goto dispatch;
L_8000bf24:
 STEP(UINT32_C(0x8000bf24)); /* 94e60008 lhu a2,0x8(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value16,2u);set(m,6u,value16);target=sx(UINT32_C(0x8000bf28));goto dispatch;
L_8000bf28:
 STEP(UINT32_C(0x8000bf28)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bf2c));goto dispatch;
L_8000bf2c:
 STEP(UINT32_C(0x8000bf2c)); /* 0c004342 jal 80010d08 */
 set(m,31u,UINT64_C(0x8000bf34));STEP(UINT32_C(0x8000bf30));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80010d08));goto dispatch;
L_8000bf30:
 STEP(UINT32_C(0x8000bf30)); /* 8ce50004 lw a1,0x4(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000bf34));goto dispatch;
L_8000bf34:
 STEP(UINT32_C(0x8000bf34)); /* 1000001b beq zero,zero,8000bfa4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bf38));set(m,2u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000bfa4):UINT32_C(0x8000bf3c));goto dispatch;}
L_8000bf38:
 STEP(UINT32_C(0x8000bf38)); /* 0040102d daddu v0,v0,zero */
 set(m,2u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000bf3c));goto dispatch;
L_8000bf3c:
 STEP(UINT32_C(0x8000bf3c)); /* 80e50004 lb a1,0x4(a3) */
 {uint8_t byte;READ((uint32_t)lo(m,7u)+UINT32_C(0x00000004),&byte,1u);set(m,5u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x8000bf40));goto dispatch;
L_8000bf40:
 STEP(UINT32_C(0x8000bf40)); /* 0c004282 jal 80010a08 */
 set(m,31u,UINT64_C(0x8000bf48));STEP(UINT32_C(0x8000bf44));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80010a08));goto dispatch;
L_8000bf44:
 STEP(UINT32_C(0x8000bf44)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bf48));goto dispatch;
L_8000bf48:
 STEP(UINT32_C(0x8000bf48)); /* 10000016 beq zero,zero,8000bfa4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bf4c));set(m,2u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000bfa4):UINT32_C(0x8000bf50));goto dispatch;}
L_8000bf4c:
 STEP(UINT32_C(0x8000bf4c)); /* 0040102d daddu v0,v0,zero */
 set(m,2u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000bf50));goto dispatch;
L_8000bf50:
 STEP(UINT32_C(0x8000bf50)); /* 0c002f6c jal 8000bdb0 */
 set(m,31u,UINT64_C(0x8000bf58));STEP(UINT32_C(0x8000bf54));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bdb0));goto dispatch;
L_8000bf54:
 STEP(UINT32_C(0x8000bf54)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bf58));goto dispatch;
L_8000bf58:
 STEP(UINT32_C(0x8000bf58)); /* 10000012 beq zero,zero,8000bfa4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bf5c));set(m,2u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000bfa4):UINT32_C(0x8000bf60));goto dispatch;}
L_8000bf5c:
 STEP(UINT32_C(0x8000bf5c)); /* 0040102d daddu v0,v0,zero */
 set(m,2u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000bf60));goto dispatch;
L_8000bf60:
 STEP(UINT32_C(0x8000bf60)); /* 0c002f8a jal 8000be28 */
 set(m,31u,UINT64_C(0x8000bf68));STEP(UINT32_C(0x8000bf64));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000be28));goto dispatch;
L_8000bf64:
 STEP(UINT32_C(0x8000bf64)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bf68));goto dispatch;
L_8000bf68:
 STEP(UINT32_C(0x8000bf68)); /* 1000000e beq zero,zero,8000bfa4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bf6c));set(m,2u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000bfa4):UINT32_C(0x8000bf70));goto dispatch;}
L_8000bf6c:
 STEP(UINT32_C(0x8000bf6c)); /* 0040102d daddu v0,v0,zero */
 set(m,2u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000bf70));goto dispatch;
L_8000bf70:
 STEP(UINT32_C(0x8000bf70)); /* 0c0034ea jal 8000d3a8 */
 set(m,31u,UINT64_C(0x8000bf78));STEP(UINT32_C(0x8000bf74));READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000d3a8));goto dispatch;
L_8000bf74:
 STEP(UINT32_C(0x8000bf74)); /* 8ce40000 lw a0,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000bf78));goto dispatch;
L_8000bf78:
 STEP(UINT32_C(0x8000bf78)); /* 3c030000 lui v1,zero,0x0 */
 set(m,3u,sx(UINT32_C(0x00000000)));target=sx(UINT32_C(0x8000bf7c));goto dispatch;
L_8000bf7c:
 STEP(UINT32_C(0x8000bf7c)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000bf80));goto dispatch;
L_8000bf80:
 STEP(UINT32_C(0x8000bf80)); /* 0c003db8 jal 8000f6e0 */
 set(m,31u,UINT64_C(0x8000bf88));STEP(UINT32_C(0x8000bf84));value64=lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffff8020),&value64,8u);target=sx(UINT32_C(0x8000f6e0));goto dispatch;
L_8000bf84:
 STEP(UINT32_C(0x8000bf84)); /* fc628020 sd v0,-0x7fe0(v1) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xffff8020),&value64,8u);target=sx(UINT32_C(0x8000bf88));goto dispatch;
L_8000bf88:
 STEP(UINT32_C(0x8000bf88)); /* 3c020000 lui v0,zero,0x0 */
 set(m,2u,sx(UINT32_C(0x00000000)));target=sx(UINT32_C(0x8000bf8c));goto dispatch;
L_8000bf8c:
 STEP(UINT32_C(0x8000bf8c)); /* 2404ffff addiu a0,zero,-1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x8000bf90));goto dispatch;
L_8000bf90:
 STEP(UINT32_C(0x8000bf90)); /* 24438000 addiu v1,v0,-32768 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff8000)));target=sx(UINT32_C(0x8000bf94));goto dispatch;
L_8000bf94:
 STEP(UINT32_C(0x8000bf94)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000bf98));goto dispatch;
L_8000bf98:
 STEP(UINT32_C(0x8000bf98)); /* fc640020 sd a0,0x20(v1) */
 value64=lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000bf9c));goto dispatch;
L_8000bf9c:
 STEP(UINT32_C(0x8000bf9c)); /* 24a38000 addiu v1,a1,-32768 */
 set(m,3u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffff8000)));target=sx(UINT32_C(0x8000bfa0));goto dispatch;
L_8000bfa0:
 STEP(UINT32_C(0x8000bfa0)); /* dc620020 ld v0,0x20(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000020),&value64,8u);set(m,2u,value64);target=sx(UINT32_C(0x8000bfa4));goto dispatch;
L_8000bfa4:
 STEP(UINT32_C(0x8000bfa4)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000bfa8));goto dispatch;
L_8000bfa8:
 STEP(UINT32_C(0x8000bfa8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000bfac));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_8000bfac:
 STEP(UINT32_C(0x8000bfac)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x8000bfb0));goto dispatch;
L_8000bac0:
 STEP(UINT32_C(0x8000bac0)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000bac4));goto dispatch;
L_8000bac4:
 STEP(UINT32_C(0x8000bac4)); /* 3084ffff andi a0,a0,0xffff */
 set(m,4u,lo(m,4u) & UINT64_C(0xffff));target=sx(UINT32_C(0x8000bac8));goto dispatch;
L_8000bac8:
 STEP(UINT32_C(0x8000bac8)); /* 24420b60 addiu v0,v0,2912 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000b60)));target=sx(UINT32_C(0x8000bacc));goto dispatch;
L_8000bacc:
 STEP(UINT32_C(0x8000bacc)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000bad0));goto dispatch;
L_8000bad0:
 STEP(UINT32_C(0x8000bad0)); /* 2445000c addiu a1,v0,12 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000bad4));goto dispatch;
L_8000bad4:
 STEP(UINT32_C(0x8000bad4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000bad8));goto dispatch;
L_8000bad8:
 STEP(UINT32_C(0x8000bad8)); /* 94a20000 lhu v0,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x8000badc));goto dispatch;
L_8000badc:
 STEP(UINT32_C(0x8000badc)); /* 50400005 beql v0,zero,8000baf4 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x8000bae0));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000baf4));}else target=sx(UINT32_C(0x8000bae4));goto dispatch;
L_8000bae0:
 STEP(UINT32_C(0x8000bae0)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000bae4));goto dispatch;
L_8000bae4:
 STEP(UINT32_C(0x8000bae4)); /* 54440003 bnel v0,a0,8000baf4 */
 if(lo(m,2u)!=lo(m,4u)){STEP(UINT32_C(0x8000bae8));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000baf4));}else target=sx(UINT32_C(0x8000baec));goto dispatch;
L_8000bae8:
 STEP(UINT32_C(0x8000bae8)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000baec));goto dispatch;
L_8000baec:
 STEP(UINT32_C(0x8000baec)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000baf0));set(m,2u,lo(m,3u)+lo(m,0u));goto dispatch;
L_8000baf0:
 STEP(UINT32_C(0x8000baf0)); /* 0060102d daddu v0,v1,zero */
 set(m,2u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x8000baf4));goto dispatch;
L_8000baf4:
 STEP(UINT32_C(0x8000baf4)); /* 28620011 slti v0,v1,17 */
 set(m,2u,((int64_t)lo(m,3u)<INT64_C(17)));target=sx(UINT32_C(0x8000baf8));goto dispatch;
L_8000baf8:
 STEP(UINT32_C(0x8000baf8)); /* 1440fff7 bne v0,zero,8000bad8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8000bafc));set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x0000000c)));target=sx(taken?UINT32_C(0x8000bad8):UINT32_C(0x8000bb00));goto dispatch;}
L_8000bafc:
 STEP(UINT32_C(0x8000bafc)); /* 24a5000c addiu a1,a1,12 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000bb00));goto dispatch;
L_8000bb00:
 STEP(UINT32_C(0x8000bb00)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000bb04));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_8000bb04:
 STEP(UINT32_C(0x8000bb04)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000bb08));goto dispatch;
L_8000bca8:
 STEP(UINT32_C(0x8000bca8)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x8000bcac));goto dispatch;
L_8000bcac:
 STEP(UINT32_C(0x8000bcac)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x8000bcb0));goto dispatch;
L_8000bcb0:
 STEP(UINT32_C(0x8000bcb0)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x8000bcb4));goto dispatch;
L_8000bcb4:
 STEP(UINT32_C(0x8000bcb4)); /* 3091ffff andi s1,a0,0xffff */
 set(m,17u,lo(m,4u) & UINT64_C(0xffff));target=sx(UINT32_C(0x8000bcb8));goto dispatch;
L_8000bcb8:
 STEP(UINT32_C(0x8000bcb8)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000bcbc));goto dispatch;
L_8000bcbc:
 STEP(UINT32_C(0x8000bcbc)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x8000bcc0));goto dispatch;
L_8000bcc0:
 STEP(UINT32_C(0x8000bcc0)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x8000bcc4));goto dispatch;
L_8000bcc4:
 STEP(UINT32_C(0x8000bcc4)); /* 00a0902d daddu s2,a1,zero */
 set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x8000bcc8));goto dispatch;
L_8000bcc8:
 STEP(UINT32_C(0x8000bcc8)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000bccc));goto dispatch;
L_8000bccc:
 STEP(UINT32_C(0x8000bccc)); /* 0c002eb0 jal 8000bac0 */
 set(m,31u,UINT64_C(0x8000bcd4));STEP(UINT32_C(0x8000bcd0));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x8000bac0));goto dispatch;
L_8000bcd0:
 STEP(UINT32_C(0x8000bcd0)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x8000bcd4));goto dispatch;
L_8000bcd4:
 STEP(UINT32_C(0x8000bcd4)); /* 1840000d blez v0,zero,8000bd0c */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x8000bcd8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffd)));target=sx(taken?UINT32_C(0x8000bd0c):UINT32_C(0x8000bcdc));goto dispatch;}
L_8000bcd8:
 STEP(UINT32_C(0x8000bcd8)); /* 2402fffd addiu v0,zero,-3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffd)));target=sx(UINT32_C(0x8000bcdc));goto dispatch;
L_8000bcdc:
 STEP(UINT32_C(0x8000bcdc)); /* 1000001a beq zero,zero,8000bd48 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bce0));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x8000bd48):UINT32_C(0x8000bce4));goto dispatch;}
L_8000bce0:
 STEP(UINT32_C(0x8000bce0)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000bce4));goto dispatch;
L_8000bce4:
 STEP(UINT32_C(0x8000bce4)); /* 00a41821 addu v1,a1,a0 */
 set(m,3u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x8000bce8));goto dispatch;
L_8000bce8:
 STEP(UINT32_C(0x8000bce8)); /* a4d10000 sh s1,0x0(a2) */
 value16=(uint16_t)lo(m,17u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value16,2u);target=sx(UINT32_C(0x8000bcec));goto dispatch;
L_8000bcec:
 STEP(UINT32_C(0x8000bcec)); /* 0060102d daddu v0,v1,zero */
 set(m,2u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x8000bcf0));goto dispatch;
L_8000bcf0:
 STEP(UINT32_C(0x8000bcf0)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x8000bcf4));goto dispatch;
L_8000bcf4:
 STEP(UINT32_C(0x8000bcf4)); /* ac520004 sw s2,0x4(v0) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x8000bcf8));goto dispatch;
L_8000bcf8:
 STEP(UINT32_C(0x8000bcf8)); /* 24040001 addiu a0,zero,1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000bcfc));goto dispatch;
L_8000bcfc:
 STEP(UINT32_C(0x8000bcfc)); /* 0c0030c2 jal 8000c308 */
 set(m,31u,UINT64_C(0x8000bd04));STEP(UINT32_C(0x8000bd00));value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x8000c308));goto dispatch;
L_8000bd00:
 STEP(UINT32_C(0x8000bd00)); /* ac730008 sw s3,0x8(v1) */
 value32=(uint32_t)lo(m,19u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x8000bd04));goto dispatch;
L_8000bd04:
 STEP(UINT32_C(0x8000bd04)); /* 1000000f beq zero,zero,8000bd44 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bd08));set(m,2u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000bd44):UINT32_C(0x8000bd0c));goto dispatch;}
L_8000bd08:
 STEP(UINT32_C(0x8000bd08)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x8000bd0c));goto dispatch;
L_8000bd0c:
 STEP(UINT32_C(0x8000bd0c)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000bd10));goto dispatch;
L_8000bd10:
 STEP(UINT32_C(0x8000bd10)); /* 24100002 addiu s0,zero,2 */
 set(m,16u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x8000bd14));goto dispatch;
L_8000bd14:
 STEP(UINT32_C(0x8000bd14)); /* 24450b60 addiu a1,v0,2912 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000b60)));target=sx(UINT32_C(0x8000bd18));goto dispatch;
L_8000bd18:
 STEP(UINT32_C(0x8000bd18)); /* 24040018 addiu a0,zero,24 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000018)));target=sx(UINT32_C(0x8000bd1c));goto dispatch;
L_8000bd1c:
 STEP(UINT32_C(0x8000bd1c)); /* 24a30018 addiu v1,a1,24 */
 set(m,3u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000018)));target=sx(UINT32_C(0x8000bd20));goto dispatch;
L_8000bd20:
 STEP(UINT32_C(0x8000bd20)); /* 94620000 lhu v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x8000bd24));goto dispatch;
L_8000bd24:
 STEP(UINT32_C(0x8000bd24)); /* 1040ffef beq v0,zero,8000bce4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x8000bd28));set(m,6u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=sx(taken?UINT32_C(0x8000bce4):UINT32_C(0x8000bd2c));goto dispatch;}
L_8000bd28:
 STEP(UINT32_C(0x8000bd28)); /* 00853021 addu a2,a0,a1 */
 set(m,6u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x8000bd2c));goto dispatch;
L_8000bd2c:
 STEP(UINT32_C(0x8000bd2c)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000bd30));goto dispatch;
L_8000bd30:
 STEP(UINT32_C(0x8000bd30)); /* 2463000c addiu v1,v1,12 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000bd34));goto dispatch;
L_8000bd34:
 STEP(UINT32_C(0x8000bd34)); /* 2a020011 slti v0,s0,17 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(17)));target=sx(UINT32_C(0x8000bd38));goto dispatch;
L_8000bd38:
 STEP(UINT32_C(0x8000bd38)); /* 1440fff9 bne v0,zero,8000bd20 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8000bd3c));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x0000000c)));target=sx(taken?UINT32_C(0x8000bd20):UINT32_C(0x8000bd40));goto dispatch;}
L_8000bd3c:
 STEP(UINT32_C(0x8000bd3c)); /* 2484000c addiu a0,a0,12 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000bd40));goto dispatch;
L_8000bd40:
 STEP(UINT32_C(0x8000bd40)); /* 2402fffc addiu v0,zero,-4 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x8000bd44));goto dispatch;
L_8000bd44:
 STEP(UINT32_C(0x8000bd44)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000bd48));goto dispatch;
L_8000bd48:
 STEP(UINT32_C(0x8000bd48)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x8000bd4c));goto dispatch;
L_8000bd4c:
 STEP(UINT32_C(0x8000bd4c)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x8000bd50));goto dispatch;
L_8000bd50:
 STEP(UINT32_C(0x8000bd50)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x8000bd54));goto dispatch;
L_8000bd54:
 STEP(UINT32_C(0x8000bd54)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x8000bd58));goto dispatch;
L_8000bd58:
 STEP(UINT32_C(0x8000bd58)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000bd5c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_8000bd5c:
 STEP(UINT32_C(0x8000bd5c)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x8000bd60));goto dispatch;
L_8000bd60:
 STEP(UINT32_C(0x8000bd60)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x8000bd64));goto dispatch;
L_8000bd64:
 STEP(UINT32_C(0x8000bd64)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000bd68));goto dispatch;
L_8000bd68:
 STEP(UINT32_C(0x8000bd68)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x8000bd6c));goto dispatch;
L_8000bd6c:
 STEP(UINT32_C(0x8000bd6c)); /* 0c002ea0 jal 8000ba80 */
 set(m,31u,UINT64_C(0x8000bd74));STEP(UINT32_C(0x8000bd70));set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000ba80));goto dispatch;
L_8000bd70:
 STEP(UINT32_C(0x8000bd70)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000bd74));goto dispatch;
L_8000bd74:
 STEP(UINT32_C(0x8000bd74)); /* 14400003 bne v0,zero,8000bd84 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8000bd78));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(taken?UINT32_C(0x8000bd84):UINT32_C(0x8000bd7c));goto dispatch;}
L_8000bd78:
 STEP(UINT32_C(0x8000bd78)); /* 2403000c addiu v1,zero,12 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000bd7c));goto dispatch;
L_8000bd7c:
 STEP(UINT32_C(0x8000bd7c)); /* 10000007 beq zero,zero,8000bd9c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bd80));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(taken?UINT32_C(0x8000bd9c):UINT32_C(0x8000bd84));goto dispatch;}
L_8000bd80:
 STEP(UINT32_C(0x8000bd80)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x8000bd84));goto dispatch;
L_8000bd84:
 STEP(UINT32_C(0x8000bd84)); /* 3c048002 lui a0,zero,0x8002 */
 set(m,4u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000bd88));goto dispatch;
L_8000bd88:
 STEP(UINT32_C(0x8000bd88)); /* 02031818 mult_rd v1,s0,v1 */
 {int64_t product;if(lo(m,16u)!=sx((uint32_t)lo(m,16u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,16u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x8000bd8c));goto dispatch;
L_8000bd8c:
 STEP(UINT32_C(0x8000bd8c)); /* 24840b60 addiu a0,a0,2912 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000b60)));target=sx(UINT32_C(0x8000bd90));goto dispatch;
L_8000bd90:
 STEP(UINT32_C(0x8000bd90)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000bd94));goto dispatch;
L_8000bd94:
 STEP(UINT32_C(0x8000bd94)); /* 00641821 addu v1,v1,a0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x8000bd98));goto dispatch;
L_8000bd98:
 STEP(UINT32_C(0x8000bd98)); /* a4600000 sh zero,0x0(v1) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value16,2u);target=sx(UINT32_C(0x8000bd9c));goto dispatch;
L_8000bd9c:
 STEP(UINT32_C(0x8000bd9c)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000bda0));goto dispatch;
L_8000bda0:
 STEP(UINT32_C(0x8000bda0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x8000bda4));goto dispatch;
L_8000bda4:
 STEP(UINT32_C(0x8000bda4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000bda8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_8000bda8:
 STEP(UINT32_C(0x8000bda8)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x8000bdac));goto dispatch;
L_8000bdac:
 STEP(UINT32_C(0x8000bdac)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000bdb0));goto dispatch;
L_8000bdb0:
 STEP(UINT32_C(0x8000bdb0)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x8000bdb4));goto dispatch;
L_8000bdb4:
 STEP(UINT32_C(0x8000bdb4)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000bdb8));goto dispatch;
L_8000bdb8:
 STEP(UINT32_C(0x8000bdb8)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x8000bdbc));goto dispatch;
L_8000bdbc:
 STEP(UINT32_C(0x8000bdbc)); /* 0c002ea0 jal 8000ba80 */
 set(m,31u,UINT64_C(0x8000bdc4));STEP(UINT32_C(0x8000bdc0));set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000ba80));goto dispatch;
L_8000bdc0:
 STEP(UINT32_C(0x8000bdc0)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000bdc4));goto dispatch;
L_8000bdc4:
 STEP(UINT32_C(0x8000bdc4)); /* 14400003 bne v0,zero,8000bdd4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8000bdc8));set(m,9u,sx(UINT32_C(0x80020000)));target=sx(taken?UINT32_C(0x8000bdd4):UINT32_C(0x8000bdcc));goto dispatch;}
L_8000bdc8:
 STEP(UINT32_C(0x8000bdc8)); /* 3c098002 lui t1,zero,0x8002 */
 set(m,9u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000bdcc));goto dispatch;
L_8000bdcc:
 STEP(UINT32_C(0x8000bdcc)); /* 10000012 beq zero,zero,8000be18 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bdd0));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(taken?UINT32_C(0x8000be18):UINT32_C(0x8000bdd4));goto dispatch;}
L_8000bdd0:
 STEP(UINT32_C(0x8000bdd0)); /* 2402fffe addiu v0,zero,-2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffffe)));target=sx(UINT32_C(0x8000bdd4));goto dispatch;
L_8000bdd4:
 STEP(UINT32_C(0x8000bdd4)); /* 95220b60 lhu v0,0xb60(t1) */
 READ((uint32_t)lo(m,9u)+UINT32_C(0x00000b60),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x8000bdd8));goto dispatch;
L_8000bdd8:
 STEP(UINT32_C(0x8000bdd8)); /* 10400003 beq v0,zero,8000bde8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x8000bddc));set(m,8u,sx((uint32_t)lo(m,9u)+UINT32_C(0x00000b60)));target=sx(taken?UINT32_C(0x8000bde8):UINT32_C(0x8000bde0));goto dispatch;}
L_8000bddc:
 STEP(UINT32_C(0x8000bddc)); /* 25280b60 addiu t0,t1,2912 */
 set(m,8u,sx((uint32_t)lo(m,9u)+UINT32_C(0x00000b60)));target=sx(UINT32_C(0x8000bde0));goto dispatch;
L_8000bde0:
 STEP(UINT32_C(0x8000bde0)); /* 1000000d beq zero,zero,8000be18 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000bde4));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff8)));target=sx(taken?UINT32_C(0x8000be18):UINT32_C(0x8000bde8));goto dispatch;}
L_8000bde4:
 STEP(UINT32_C(0x8000bde4)); /* 2402fff8 addiu v0,zero,-8 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x8000bde8));goto dispatch;
L_8000bde8:
 STEP(UINT32_C(0x8000bde8)); /* 2403000c addiu v1,zero,12 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000bdec));goto dispatch;
L_8000bdec:
 STEP(UINT32_C(0x8000bdec)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000bdf0));goto dispatch;
L_8000bdf0:
 STEP(UINT32_C(0x8000bdf0)); /* 02031818 mult_rd v1,s0,v1 */
 {int64_t product;if(lo(m,16u)!=sx((uint32_t)lo(m,16u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,16u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x8000bdf4));goto dispatch;
L_8000bdf4:
 STEP(UINT32_C(0x8000bdf4)); /* 00682021 addu a0,v1,t0 */
 set(m,4u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,8u)));target=sx(UINT32_C(0x8000bdf8));goto dispatch;
L_8000bdf8:
 STEP(UINT32_C(0x8000bdf8)); /* 01033821 addu a3,t0,v1 */
 set(m,7u,sx((uint32_t)lo(m,8u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x8000bdfc));goto dispatch;
L_8000bdfc:
 STEP(UINT32_C(0x8000bdfc)); /* 94850000 lhu a1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value16,2u);set(m,5u,value16);target=sx(UINT32_C(0x8000be00));goto dispatch;
L_8000be00:
 STEP(UINT32_C(0x8000be00)); /* 00e0182d daddu v1,a3,zero */
 set(m,3u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x8000be04));goto dispatch;
L_8000be04:
 STEP(UINT32_C(0x8000be04)); /* 8c660004 lw a2,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x8000be08));goto dispatch;
L_8000be08:
 STEP(UINT32_C(0x8000be08)); /* 8ce40008 lw a0,0x8(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000be0c));goto dispatch;
L_8000be0c:
 STEP(UINT32_C(0x8000be0c)); /* a5250b60 sh a1,0xb60(t1) */
 value16=(uint16_t)lo(m,5u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000b60),&value16,2u);target=sx(UINT32_C(0x8000be10));goto dispatch;
L_8000be10:
 STEP(UINT32_C(0x8000be10)); /* ad040008 sw a0,0x8(t0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x8000be14));goto dispatch;
L_8000be14:
 STEP(UINT32_C(0x8000be14)); /* ad060004 sw a2,0x4(t0) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x8000be18));goto dispatch;
L_8000be18:
 STEP(UINT32_C(0x8000be18)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000be1c));goto dispatch;
L_8000be1c:
 STEP(UINT32_C(0x8000be1c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x8000be20));goto dispatch;
L_8000be20:
 STEP(UINT32_C(0x8000be20)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000be24));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_8000be24:
 STEP(UINT32_C(0x8000be24)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x8000be28));goto dispatch;
L_8000be28:
 STEP(UINT32_C(0x8000be28)); /* 2402000c addiu v0,zero,12 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000be2c));goto dispatch;
L_8000be2c:
 STEP(UINT32_C(0x8000be2c)); /* 3c068002 lui a2,zero,0x8002 */
 set(m,6u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000be30));goto dispatch;
L_8000be30:
 STEP(UINT32_C(0x8000be30)); /* 00822018 mult_rd a0,a0,v0 */
 {int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x8000be34));goto dispatch;
L_8000be34:
 STEP(UINT32_C(0x8000be34)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x8000be38));goto dispatch;
L_8000be38:
 STEP(UINT32_C(0x8000be38)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000be3c));goto dispatch;
L_8000be3c:
 STEP(UINT32_C(0x8000be3c)); /* 24c30b60 addiu v1,a2,2912 */
 set(m,3u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000b60)));target=sx(UINT32_C(0x8000be40));goto dispatch;
L_8000be40:
 STEP(UINT32_C(0x8000be40)); /* 94c50b60 lhu a1,0xb60(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000b60),&value16,2u);set(m,5u,value16);target=sx(UINT32_C(0x8000be44));goto dispatch;
L_8000be44:
 STEP(UINT32_C(0x8000be44)); /* 00832021 addu a0,a0,v1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x8000be48));goto dispatch;
L_8000be48:
 STEP(UINT32_C(0x8000be48)); /* 94820000 lhu v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x8000be4c));goto dispatch;
L_8000be4c:
 STEP(UINT32_C(0x8000be4c)); /* 14a20006 bne a1,v0,8000be68 */
 {int taken=(lo(m,5u)!=lo(m,2u));STEP(UINT32_C(0x8000be50));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff7)));target=sx(taken?UINT32_C(0x8000be68):UINT32_C(0x8000be54));goto dispatch;}
L_8000be50:
 STEP(UINT32_C(0x8000be50)); /* 2402fff7 addiu v0,zero,-9 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff7)));target=sx(UINT32_C(0x8000be54));goto dispatch;
L_8000be54:
 STEP(UINT32_C(0x8000be54)); /* a4c00b60 sh zero,0xb60(a2) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000b60),&value16,2u);target=sx(UINT32_C(0x8000be58));goto dispatch;
L_8000be58:
 STEP(UINT32_C(0x8000be58)); /* 24040002 addiu a0,zero,2 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x8000be5c));goto dispatch;
L_8000be5c:
 STEP(UINT32_C(0x8000be5c)); /* 0c0030c2 jal 8000c308 */
 set(m,31u,UINT64_C(0x8000be64));STEP(UINT32_C(0x8000be60));set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000c308));goto dispatch;
L_8000be60:
 STEP(UINT32_C(0x8000be60)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000be64));goto dispatch;
L_8000be64:
 STEP(UINT32_C(0x8000be64)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000be68));goto dispatch;
L_8000be68:
 STEP(UINT32_C(0x8000be68)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000be6c));goto dispatch;
L_8000be6c:
 STEP(UINT32_C(0x8000be6c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000be70));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_8000be70:
 STEP(UINT32_C(0x8000be70)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x8000be74));goto dispatch;
L_8000be74:
 STEP(UINT32_C(0x8000be74)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000be78));goto dispatch;
L_8000c308:
 STEP(UINT32_C(0x8000c308)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x8000c30c));goto dispatch;
L_8000c30c:
 STEP(UINT32_C(0x8000c30c)); /* 24020002 addiu v0,zero,2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x8000c310));goto dispatch;
L_8000c310:
 STEP(UINT32_C(0x8000c310)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x8000c314));goto dispatch;
L_8000c314:
 STEP(UINT32_C(0x8000c314)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x8000c318));goto dispatch;
L_8000c318:
 STEP(UINT32_C(0x8000c318)); /* 30b4ffff andi s4,a1,0xffff */
 set(m,20u,lo(m,5u) & UINT64_C(0xffff));target=sx(UINT32_C(0x8000c31c));goto dispatch;
L_8000c31c:
 STEP(UINT32_C(0x8000c31c)); /* ffbf0070 sd ra,0x70(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x8000c320));goto dispatch;
L_8000c320:
 STEP(UINT32_C(0x8000c320)); /* 3091ffff andi s1,a0,0xffff */
 set(m,17u,lo(m,4u) & UINT64_C(0xffff));target=sx(UINT32_C(0x8000c324));goto dispatch;
L_8000c324:
 STEP(UINT32_C(0x8000c324)); /* ffb60060 sd s6,0x60(sp) */
 value64=lo(m,22u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x8000c328));goto dispatch;
L_8000c328:
 STEP(UINT32_C(0x8000c328)); /* ffb50050 sd s5,0x50(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x8000c32c));goto dispatch;
L_8000c32c:
 STEP(UINT32_C(0x8000c32c)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x8000c330));goto dispatch;
L_8000c330:
 STEP(UINT32_C(0x8000c330)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000c334));goto dispatch;
L_8000c334:
 STEP(UINT32_C(0x8000c334)); /* 16220006 bne s1,v0,8000c350 */
 {int taken=(lo(m,17u)!=lo(m,2u));STEP(UINT32_C(0x8000c338));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x8000c350):UINT32_C(0x8000c33c));goto dispatch;}
L_8000c338:
 STEP(UINT32_C(0x8000c338)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000c33c));goto dispatch;
L_8000c33c:
 STEP(UINT32_C(0x8000c33c)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000c340));goto dispatch;
L_8000c340:
 STEP(UINT32_C(0x8000c340)); /* 8c620cdc lw v0,0xcdc(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000cdc),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000c344));goto dispatch;
L_8000c344:
 STEP(UINT32_C(0x8000c344)); /* 10400022 beq v0,zero,8000c3d0 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x8000c348));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x8000c3d0):UINT32_C(0x8000c34c));goto dispatch;}
L_8000c348:
 STEP(UINT32_C(0x8000c348)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000c34c));goto dispatch;
L_8000c34c:
 STEP(UINT32_C(0x8000c34c)); /* ac600cdc sw zero,0xcdc(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000cdc),&value32,4u);target=sx(UINT32_C(0x8000c350));goto dispatch;
L_8000c350:
 STEP(UINT32_C(0x8000c350)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000c354));goto dispatch;
L_8000c354:
 STEP(UINT32_C(0x8000c354)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000c358));goto dispatch;
L_8000c358:
 STEP(UINT32_C(0x8000c358)); /* 24530b50 addiu s3,v0,2896 */
 set(m,19u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000b50)));target=sx(UINT32_C(0x8000c35c));goto dispatch;
L_8000c35c:
 STEP(UINT32_C(0x8000c35c)); /* 24160048 addiu s6,zero,72 */
 set(m,22u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000048)));target=sx(UINT32_C(0x8000c360));goto dispatch;
L_8000c360:
 STEP(UINT32_C(0x8000c360)); /* 24120049 addiu s2,zero,73 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000049)));target=sx(UINT32_C(0x8000c364));goto dispatch;
L_8000c364:
 STEP(UINT32_C(0x8000c364)); /* 24150001 addiu s5,zero,1 */
 set(m,21u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000c368));goto dispatch;
L_8000c368:
 STEP(UINT32_C(0x8000c368)); /* 24030048 addiu v1,zero,72 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000048)));target=sx(UINT32_C(0x8000c36c));goto dispatch;
L_8000c36c:
 STEP(UINT32_C(0x8000c36c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000c370));goto dispatch;
L_8000c370:
 STEP(UINT32_C(0x8000c370)); /* 0250180b movn v1,s2,s0 */
 if(lo(m,16u)!=0u)set(m,3u,lo(m,18u));target=sx(UINT32_C(0x8000c374));goto dispatch;
L_8000c374:
 STEP(UINT32_C(0x8000c374)); /* 14720004 bne v1,s2,8000c388 */
 {int taken=(lo(m,3u)!=lo(m,18u));STEP(UINT32_C(0x8000c378));set(m,5u,lo(m,3u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000c388):UINT32_C(0x8000c37c));goto dispatch;}
L_8000c378:
 STEP(UINT32_C(0x8000c378)); /* 0060282d daddu a1,v1,zero */
 set(m,5u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x8000c37c));goto dispatch;
L_8000c37c:
 STEP(UINT32_C(0x8000c37c)); /* 8e620008 lw v0,0x8(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000c380));goto dispatch;
L_8000c380:
 STEP(UINT32_C(0x8000c380)); /* 5040000f beql v0,zero,8000c3c0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x8000c384));set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000c3c0));}else target=sx(UINT32_C(0x8000c388));goto dispatch;
L_8000c384:
 STEP(UINT32_C(0x8000c384)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000c388));goto dispatch;
L_8000c388:
 STEP(UINT32_C(0x8000c388)); /* 14760004 bne v1,s6,8000c39c */
 {int taken=(lo(m,3u)!=lo(m,22u));STEP(UINT32_C(0x8000c38c));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000e)));target=sx(taken?UINT32_C(0x8000c39c):UINT32_C(0x8000c390));goto dispatch;}
L_8000c38c:
 STEP(UINT32_C(0x8000c38c)); /* 2404000e addiu a0,zero,14 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000e)));target=sx(UINT32_C(0x8000c390));goto dispatch;
L_8000c390:
 STEP(UINT32_C(0x8000c390)); /* 8e620004 lw v0,0x4(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000c394));goto dispatch;
L_8000c394:
 STEP(UINT32_C(0x8000c394)); /* 5040000a beql v0,zero,8000c3c0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x8000c398));set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000c3c0));}else target=sx(UINT32_C(0x8000c39c));goto dispatch;
L_8000c398:
 STEP(UINT32_C(0x8000c398)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000c39c));goto dispatch;
L_8000c39c:
 STEP(UINT32_C(0x8000c39c)); /* 24060002 addiu a2,zero,2 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x8000c3a0));goto dispatch;
L_8000c3a0:
 STEP(UINT32_C(0x8000c3a0)); /* 0c003098 jal 8000c260 */
 set(m,31u,UINT64_C(0x8000c3a8));STEP(UINT32_C(0x8000c3a4));set(m,7u,lo(m,17u) & UINT64_C(0xff));target=sx(UINT32_C(0x8000c260));goto dispatch;
L_8000c3a4:
 STEP(UINT32_C(0x8000c3a4)); /* 322700ff andi a3,s1,0xff */
 set(m,7u,lo(m,17u) & UINT64_C(0xff));target=sx(UINT32_C(0x8000c3a8));goto dispatch;
L_8000c3a8:
 STEP(UINT32_C(0x8000c3a8)); /* 16350002 bne s1,s5,8000c3b4 */
 {int taken=(lo(m,17u)!=lo(m,21u));STEP(UINT32_C(0x8000c3ac));value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value16,2u);target=sx(taken?UINT32_C(0x8000c3b4):UINT32_C(0x8000c3b0));goto dispatch;}
L_8000c3ac:
 STEP(UINT32_C(0x8000c3ac)); /* a440000c sh zero,0xc(v0) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x8000c3b0));goto dispatch;
L_8000c3b0:
 STEP(UINT32_C(0x8000c3b0)); /* a454000c sh s4,0xc(v0) */
 value16=(uint16_t)lo(m,20u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x8000c3b4));goto dispatch;
L_8000c3b4:
 STEP(UINT32_C(0x8000c3b4)); /* 0c003082 jal 8000c208 */
 set(m,31u,UINT64_C(0x8000c3bc));STEP(UINT32_C(0x8000c3b8));set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000c208));goto dispatch;
L_8000c3b8:
 STEP(UINT32_C(0x8000c3b8)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x8000c3bc));goto dispatch;
L_8000c3bc:
 STEP(UINT32_C(0x8000c3bc)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000c3c0));goto dispatch;
L_8000c3c0:
 STEP(UINT32_C(0x8000c3c0)); /* 2a020002 slti v0,s0,2 */
 set(m,2u,((int64_t)lo(m,16u)<INT64_C(2)));target=sx(UINT32_C(0x8000c3c4));goto dispatch;
L_8000c3c4:
 STEP(UINT32_C(0x8000c3c4)); /* 1440ffea bne v0,zero,8000c370 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8000c3c8));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000048)));target=sx(taken?UINT32_C(0x8000c370):UINT32_C(0x8000c3cc));goto dispatch;}
L_8000c3c8:
 STEP(UINT32_C(0x8000c3c8)); /* 24030048 addiu v1,zero,72 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000048)));target=sx(UINT32_C(0x8000c3cc));goto dispatch;
L_8000c3cc:
 STEP(UINT32_C(0x8000c3cc)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000c3d0));goto dispatch;
L_8000c3d0:
 STEP(UINT32_C(0x8000c3d0)); /* dfb60060 ld s6,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,22u,value64);target=sx(UINT32_C(0x8000c3d4));goto dispatch;
L_8000c3d4:
 STEP(UINT32_C(0x8000c3d4)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x8000c3d8));goto dispatch;
L_8000c3d8:
 STEP(UINT32_C(0x8000c3d8)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x8000c3dc));goto dispatch;
L_8000c3dc:
 STEP(UINT32_C(0x8000c3dc)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x8000c3e0));goto dispatch;
L_8000c3e0:
 STEP(UINT32_C(0x8000c3e0)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x8000c3e4));goto dispatch;
L_8000c3e4:
 STEP(UINT32_C(0x8000c3e4)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x8000c3e8));goto dispatch;
L_8000c3e8:
 STEP(UINT32_C(0x8000c3e8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x8000c3ec));goto dispatch;
L_8000c3ec:
 STEP(UINT32_C(0x8000c3ec)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000c3f0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_8000c3f0:
 STEP(UINT32_C(0x8000c3f0)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x8000c3f4));goto dispatch;
L_8000c260:
 STEP(UINT32_C(0x8000c260)); /* 27bdffa0 addiu sp,sp,-96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffa0)));target=sx(UINT32_C(0x8000c264));goto dispatch;
L_8000c264:
 STEP(UINT32_C(0x8000c264)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x8000c268));goto dispatch;
L_8000c268:
 STEP(UINT32_C(0x8000c268)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000c26c));goto dispatch;
L_8000c26c:
 STEP(UINT32_C(0x8000c26c)); /* 3c118002 lui s1,zero,0x8002 */
 set(m,17u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000c270));goto dispatch;
L_8000c270:
 STEP(UINT32_C(0x8000c270)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000c274));goto dispatch;
L_8000c274:
 STEP(UINT32_C(0x8000c274)); /* ffb40040 sd s4,0x40(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x8000c278));goto dispatch;
L_8000c278:
 STEP(UINT32_C(0x8000c278)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x8000c27c));goto dispatch;
L_8000c27c:
 STEP(UINT32_C(0x8000c27c)); /* 30f400ff andi s4,a3,0xff */
 set(m,20u,lo(m,7u) & UINT64_C(0xff));target=sx(UINT32_C(0x8000c280));goto dispatch;
L_8000c280:
 STEP(UINT32_C(0x8000c280)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000c284));goto dispatch;
L_8000c284:
 STEP(UINT32_C(0x8000c284)); /* 30d300ff andi s3,a2,0xff */
 set(m,19u,lo(m,6u) & UINT64_C(0xff));target=sx(UINT32_C(0x8000c288));goto dispatch;
L_8000c288:
 STEP(UINT32_C(0x8000c288)); /* ffbf0050 sd ra,0x50(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x8000c28c));goto dispatch;
L_8000c28c:
 STEP(UINT32_C(0x8000c28c)); /* 8e240cd4 lw a0,0xcd4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000cd4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000c290));goto dispatch;
L_8000c290:
 STEP(UINT32_C(0x8000c290)); /* 8c830004 lw v1,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x8000c294));goto dispatch;
L_8000c294:
 STEP(UINT32_C(0x8000c294)); /* 8c820008 lw v0,0x8(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000c298));goto dispatch;
L_8000c298:
 STEP(UINT32_C(0x8000c298)); /* 14430005 bne v0,v1,8000c2b0 */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x8000c29c));set(m,18u,lo(m,5u) & UINT64_C(0xff));target=sx(taken?UINT32_C(0x8000c2b0):UINT32_C(0x8000c2a0));goto dispatch;}
L_8000c29c:
 STEP(UINT32_C(0x8000c29c)); /* 30b200ff andi s2,a1,0xff */
 set(m,18u,lo(m,5u) & UINT64_C(0xff));target=sx(UINT32_C(0x8000c2a0));goto dispatch;
L_8000c2a0:
 STEP(UINT32_C(0x8000c2a0)); /* 3c058001 lui a1,zero,0x8001 */
 set(m,5u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000c2a4));goto dispatch;
L_8000c2a4:
 STEP(UINT32_C(0x8000c2a4)); /* 24040003 addiu a0,zero,3 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x8000c2a8));goto dispatch;
L_8000c2a8:
 STEP(UINT32_C(0x8000c2a8)); /* 0c002e74 jal 8000b9d0 */
 set(m,31u,UINT64_C(0x8000c2b0));STEP(UINT32_C(0x8000c2ac));set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00003360)));target=sx(UINT32_C(0x8000b9d0));goto dispatch;
L_8000c2ac:
 STEP(UINT32_C(0x8000c2ac)); /* 24a53360 addiu a1,a1,13152 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00003360)));target=sx(UINT32_C(0x8000c2b0));goto dispatch;
L_8000c2b0:
 STEP(UINT32_C(0x8000c2b0)); /* 8e220cd4 lw v0,0xcd4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000cd4),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000c2b4));goto dispatch;
L_8000c2b4:
 STEP(UINT32_C(0x8000c2b4)); /* 24040001 addiu a0,zero,1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000c2b8));goto dispatch;
L_8000c2b8:
 STEP(UINT32_C(0x8000c2b8)); /* 24060045 addiu a2,zero,69 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000045)));target=sx(UINT32_C(0x8000c2bc));goto dispatch;
L_8000c2bc:
 STEP(UINT32_C(0x8000c2bc)); /* dfbf0050 ld ra,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000c2c0));goto dispatch;
L_8000c2c0:
 STEP(UINT32_C(0x8000c2c0)); /* 8c430010 lw v1,0x10(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000010),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x8000c2c4));goto dispatch;
L_8000c2c4:
 STEP(UINT32_C(0x8000c2c4)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x8000c2c8));goto dispatch;
L_8000c2c8:
 STEP(UINT32_C(0x8000c2c8)); /* a4700000 sh s0,0x0(v1) */
 value16=(uint16_t)lo(m,16u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value16,2u);target=sx(UINT32_C(0x8000c2cc));goto dispatch;
L_8000c2cc:
 STEP(UINT32_C(0x8000c2cc)); /* 24650008 addiu a1,v1,8 */
 set(m,5u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x8000c2d0));goto dispatch;
L_8000c2d0:
 STEP(UINT32_C(0x8000c2d0)); /* a0720007 sb s2,0x7(v1) */
 {uint8_t byte=(uint8_t)lo(m,18u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000007),&byte,1u);}target=sx(UINT32_C(0x8000c2d4));goto dispatch;
L_8000c2d4:
 STEP(UINT32_C(0x8000c2d4)); /* 0060102d daddu v0,v1,zero */
 set(m,2u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x8000c2d8));goto dispatch;
L_8000c2d8:
 STEP(UINT32_C(0x8000c2d8)); /* a0730008 sb s3,0x8(v1) */
 {uint8_t byte=(uint8_t)lo(m,19u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&byte,1u);}target=sx(UINT32_C(0x8000c2dc));goto dispatch;
L_8000c2dc:
 STEP(UINT32_C(0x8000c2dc)); /* a4640004 sh a0,0x4(v1) */
 value16=(uint16_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value16,2u);target=sx(UINT32_C(0x8000c2e0));goto dispatch;
L_8000c2e0:
 STEP(UINT32_C(0x8000c2e0)); /* a0660006 sb a2,0x6(v1) */
 {uint8_t byte=(uint8_t)lo(m,6u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000006),&byte,1u);}target=sx(UINT32_C(0x8000c2e4));goto dispatch;
L_8000c2e4:
 STEP(UINT32_C(0x8000c2e4)); /* a4600002 sh zero,0x2(v1) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000002),&value16,2u);target=sx(UINT32_C(0x8000c2e8));goto dispatch;
L_8000c2e8:
 STEP(UINT32_C(0x8000c2e8)); /* a0b40001 sb s4,0x1(a1) */
 {uint8_t byte=(uint8_t)lo(m,20u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000001),&byte,1u);}target=sx(UINT32_C(0x8000c2ec));goto dispatch;
L_8000c2ec:
 STEP(UINT32_C(0x8000c2ec)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x8000c2f0));goto dispatch;
L_8000c2f0:
 STEP(UINT32_C(0x8000c2f0)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x8000c2f4));goto dispatch;
L_8000c2f4:
 STEP(UINT32_C(0x8000c2f4)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x8000c2f8));goto dispatch;
L_8000c2f8:
 STEP(UINT32_C(0x8000c2f8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x8000c2fc));goto dispatch;
L_8000c2fc:
 STEP(UINT32_C(0x8000c2fc)); /* a4a00002 sh zero,0x2(a1) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000002),&value16,2u);target=sx(UINT32_C(0x8000c300));goto dispatch;
L_8000c300:
 STEP(UINT32_C(0x8000c300)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000c304));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));goto dispatch;
L_8000c304:
 STEP(UINT32_C(0x8000c304)); /* 27bd0060 addiu sp,sp,96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x8000c308));goto dispatch;
L_8000c208:
 STEP(UINT32_C(0x8000c208)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x8000c20c));goto dispatch;
L_8000c20c:
 STEP(UINT32_C(0x8000c20c)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000c210));goto dispatch;
L_8000c210:
 STEP(UINT32_C(0x8000c210)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x8000c214));goto dispatch;
L_8000c214:
 STEP(UINT32_C(0x8000c214)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000c218));goto dispatch;
L_8000c218:
 STEP(UINT32_C(0x8000c218)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x8000c21c));goto dispatch;
L_8000c21c:
 STEP(UINT32_C(0x8000c21c)); /* 0c003526 jal 8000d498 */
 set(m,31u,UINT64_C(0x8000c224));STEP(UINT32_C(0x8000c220));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000cd4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000d498));goto dispatch;
L_8000c220:
 STEP(UINT32_C(0x8000c220)); /* 8c440cd4 lw a0,0xcd4(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000cd4),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000c224));goto dispatch;
L_8000c224:
 STEP(UINT32_C(0x8000c224)); /* 82050007 lb a1,0x7(s0) */
 {uint8_t byte;READ((uint32_t)lo(m,16u)+UINT32_C(0x00000007),&byte,1u);set(m,5u,(uint64_t)(int64_t)(int8_t)byte);}target=sx(UINT32_C(0x8000c228));goto dispatch;
L_8000c228:
 STEP(UINT32_C(0x8000c228)); /* 0c004282 jal 80010a08 */
 set(m,31u,UINT64_C(0x8000c230));STEP(UINT32_C(0x8000c22c));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80010a08));goto dispatch;
L_8000c22c:
 STEP(UINT32_C(0x8000c22c)); /* 24040001 addiu a0,zero,1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000c230));goto dispatch;
L_8000c230:
 STEP(UINT32_C(0x8000c230)); /* 04410007 regimm1 v0,8000c250 */
 {int taken=((int64_t)lo(m,2u)>=0);STEP(UINT32_C(0x8000c234));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x8000c250):UINT32_C(0x8000c238));goto dispatch;}
L_8000c234:
 STEP(UINT32_C(0x8000c234)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000c238));goto dispatch;
L_8000c238:
 STEP(UINT32_C(0x8000c238)); /* 3c058001 lui a1,zero,0x8001 */
 set(m,5u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000c23c));goto dispatch;
L_8000c23c:
 STEP(UINT32_C(0x8000c23c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x8000c240));goto dispatch;
L_8000c240:
 STEP(UINT32_C(0x8000c240)); /* 24040003 addiu a0,zero,3 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x8000c244));goto dispatch;
L_8000c244:
 STEP(UINT32_C(0x8000c244)); /* 24a53350 addiu a1,a1,13136 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00003350)));target=sx(UINT32_C(0x8000c248));goto dispatch;
L_8000c248:
 STEP(UINT32_C(0x8000c248)); /* 08002e74 j 8000b9d0 */
 STEP(UINT32_C(0x8000c24c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x8000b9d0));goto dispatch;
L_8000c24c:
 STEP(UINT32_C(0x8000c24c)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x8000c250));goto dispatch;
L_8000c250:
 STEP(UINT32_C(0x8000c250)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x8000c254));goto dispatch;
L_8000c254:
 STEP(UINT32_C(0x8000c254)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000c258));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_8000c258:
 STEP(UINT32_C(0x8000c258)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x8000c25c));goto dispatch;
L_8000ba80:
 STEP(UINT32_C(0x8000ba80)); /* 2482ffff addiu v0,a0,-1 */
 set(m,2u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x8000ba84));goto dispatch;
L_8000ba84:
 STEP(UINT32_C(0x8000ba84)); /* 2c420010 sltiu v0,v0,16 */
 set(m,2u,(lo(m,2u)<UINT64_C(0x10)));target=sx(UINT32_C(0x8000ba88));goto dispatch;
L_8000ba88:
 STEP(UINT32_C(0x8000ba88)); /* 14400003 bne v0,zero,8000ba98 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8000ba8c));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(taken?UINT32_C(0x8000ba98):UINT32_C(0x8000ba90));goto dispatch;}
L_8000ba8c:
 STEP(UINT32_C(0x8000ba8c)); /* 2403000c addiu v1,zero,12 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x8000ba90));goto dispatch;
L_8000ba90:
 STEP(UINT32_C(0x8000ba90)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000ba94));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_8000ba94:
 STEP(UINT32_C(0x8000ba94)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000ba98));goto dispatch;
L_8000ba98:
 STEP(UINT32_C(0x8000ba98)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000ba9c));goto dispatch;
L_8000ba9c:
 STEP(UINT32_C(0x8000ba9c)); /* 00831818 mult_rd v1,a0,v1 */
 {int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x8000baa0));goto dispatch;
L_8000baa0:
 STEP(UINT32_C(0x8000baa0)); /* 24420b60 addiu v0,v0,2912 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000b60)));target=sx(UINT32_C(0x8000baa4));goto dispatch;
L_8000baa4:
 STEP(UINT32_C(0x8000baa4)); /* 00621821 addu v1,v1,v0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x8000baa8));goto dispatch;
L_8000baa8:
 STEP(UINT32_C(0x8000baa8)); /* 94620000 lhu v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x8000baac));goto dispatch;
L_8000baac:
 STEP(UINT32_C(0x8000baac)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000bab0));set(m,2u,lo(m,0u)<lo(m,2u));goto dispatch;
L_8000bab0:
 STEP(UINT32_C(0x8000bab0)); /* 0002102b sltu v0,zero,v0 */
 set(m,2u,lo(m,0u)<lo(m,2u));target=sx(UINT32_C(0x8000bab4));goto dispatch;
L_8000d478:
 STEP(UINT32_C(0x8000d478)); /* ac850000 sw a1,0x0(a0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x8000d47c));goto dispatch;
L_8000d47c:
 STEP(UINT32_C(0x8000d47c)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000d480));goto dispatch;
L_8000d480:
 STEP(UINT32_C(0x8000d480)); /* ac860004 sw a2,0x4(a0) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x8000d484));goto dispatch;
L_8000d484:
 STEP(UINT32_C(0x8000d484)); /* ac87000c sw a3,0xc(a0) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x8000d488));goto dispatch;
L_8000d488:
 STEP(UINT32_C(0x8000d488)); /* ac800008 sw zero,0x8(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x8000d48c));goto dispatch;
L_8000d48c:
 STEP(UINT32_C(0x8000d48c)); /* ac870014 sw a3,0x14(a0) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x8000d490));goto dispatch;
L_8000d490:
 STEP(UINT32_C(0x8000d490)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000d494));value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);goto dispatch;
L_8000d494:
 STEP(UINT32_C(0x8000d494)); /* ac870010 sw a3,0x10(a0) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x8000d498));goto dispatch;
L_8000d498:
 STEP(UINT32_C(0x8000d498)); /* 0080302d daddu a2,a0,zero */
 set(m,6u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000d49c));goto dispatch;
L_8000d49c:
 STEP(UINT32_C(0x8000d49c)); /* 8cc50000 lw a1,0x0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000d4a0));goto dispatch;
L_8000d4a0:
 STEP(UINT32_C(0x8000d4a0)); /* 8cc40004 lw a0,0x4(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000004),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000d4a4));goto dispatch;
L_8000d4a4:
 STEP(UINT32_C(0x8000d4a4)); /* 8cc30008 lw v1,0x8(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x8000d4a8));goto dispatch;
L_8000d4a8:
 STEP(UINT32_C(0x8000d4a8)); /* 00a42018 mult_rd a0,a1,a0 */
 {int64_t product;if(lo(m,5u)!=sx((uint32_t)lo(m,5u))||lo(m,4u)!=sx((uint32_t)lo(m,4u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,5u)*(int64_t)(int32_t)lo(m,4u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x8000d4ac));goto dispatch;
L_8000d4ac:
 STEP(UINT32_C(0x8000d4ac)); /* 8cc20010 lw v0,0x10(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000010),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x8000d4b0));goto dispatch;
L_8000d4b0:
 STEP(UINT32_C(0x8000d4b0)); /* 8cc70014 lw a3,0x14(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000014),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x8000d4b4));goto dispatch;
L_8000d4b4:
 STEP(UINT32_C(0x8000d4b4)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000d4b8));goto dispatch;
L_8000d4b8:
 STEP(UINT32_C(0x8000d4b8)); /* 00451021 addu v0,v0,a1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x8000d4bc));goto dispatch;
L_8000d4bc:
 STEP(UINT32_C(0x8000d4bc)); /* acc30008 sw v1,0x8(a2) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x8000d4c0));goto dispatch;
L_8000d4c0:
 STEP(UINT32_C(0x8000d4c0)); /* 00e42021 addu a0,a3,a0 */
 set(m,4u,sx((uint32_t)lo(m,7u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x8000d4c4));goto dispatch;
L_8000d4c4:
 STEP(UINT32_C(0x8000d4c4)); /* 14440002 bne v0,a0,8000d4d0 */
 {int taken=(lo(m,2u)!=lo(m,4u));STEP(UINT32_C(0x8000d4c8));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000010),&value32,4u);target=sx(taken?UINT32_C(0x8000d4d0):UINT32_C(0x8000d4cc));goto dispatch;}
L_8000d4c8:
 STEP(UINT32_C(0x8000d4c8)); /* acc20010 sw v0,0x10(a2) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x8000d4cc));goto dispatch;
L_8000d4cc:
 STEP(UINT32_C(0x8000d4cc)); /* acc70010 sw a3,0x10(a2) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x8000d4d0));goto dispatch;
L_8000d4d0:
 STEP(UINT32_C(0x8000d4d0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000d4d4));/* nop */goto dispatch;
L_8000d4d4:
 STEP(UINT32_C(0x8000d4d4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000d4d8));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

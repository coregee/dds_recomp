#include "ps2_sif_dma_kernel.h"
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
uint32_t nocturneSifDmaKernelResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x80006308):goto L_80006308;
 case UINT32_C(0x8000630c):goto L_8000630c;
 case UINT32_C(0x80006310):goto L_80006310;
 case UINT32_C(0x80006314):goto L_80006314;
 case UINT32_C(0x80006318):goto L_80006318;
 case UINT32_C(0x8000631c):goto L_8000631c;
 case UINT32_C(0x80006320):goto L_80006320;
 case UINT32_C(0x80006324):goto L_80006324;
 case UINT32_C(0x80006328):goto L_80006328;
 case UINT32_C(0x8000632c):goto L_8000632c;
 case UINT32_C(0x80006330):goto L_80006330;
 case UINT32_C(0x80006334):goto L_80006334;
 case UINT32_C(0x80006338):goto L_80006338;
 case UINT32_C(0x8000633c):goto L_8000633c;
 case UINT32_C(0x80006340):goto L_80006340;
 case UINT32_C(0x80006344):goto L_80006344;
 case UINT32_C(0x80006348):goto L_80006348;
 case UINT32_C(0x8000634c):goto L_8000634c;
 case UINT32_C(0x80006350):goto L_80006350;
 case UINT32_C(0x80006354):goto L_80006354;
 case UINT32_C(0x80006358):goto L_80006358;
 case UINT32_C(0x8000635c):goto L_8000635c;
 case UINT32_C(0x80006360):goto L_80006360;
 case UINT32_C(0x80006364):goto L_80006364;
 case UINT32_C(0x80006368):goto L_80006368;
 case UINT32_C(0x80006370):goto L_80006370;
 case UINT32_C(0x80006374):goto L_80006374;
 case UINT32_C(0x80006378):goto L_80006378;
 case UINT32_C(0x8000637c):goto L_8000637c;
 case UINT32_C(0x80006380):goto L_80006380;
 case UINT32_C(0x80006384):goto L_80006384;
 case UINT32_C(0x80006388):goto L_80006388;
 case UINT32_C(0x8000638c):goto L_8000638c;
 case UINT32_C(0x80006390):goto L_80006390;
 case UINT32_C(0x80006394):goto L_80006394;
 case UINT32_C(0x80006398):goto L_80006398;
 case UINT32_C(0x8000639c):goto L_8000639c;
 case UINT32_C(0x800063a0):goto L_800063a0;
 case UINT32_C(0x800063a4):goto L_800063a4;
 case UINT32_C(0x800063a8):goto L_800063a8;
 case UINT32_C(0x800063ac):goto L_800063ac;
 case UINT32_C(0x800063b0):goto L_800063b0;
 case UINT32_C(0x800063b4):goto L_800063b4;
 case UINT32_C(0x800063b8):goto L_800063b8;
 case UINT32_C(0x800063bc):goto L_800063bc;
 case UINT32_C(0x800063c0):goto L_800063c0;
 case UINT32_C(0x800063c4):goto L_800063c4;
 case UINT32_C(0x800063c8):goto L_800063c8;
 case UINT32_C(0x800063cc):goto L_800063cc;
 case UINT32_C(0x800063d0):goto L_800063d0;
 case UINT32_C(0x800063d4):goto L_800063d4;
 case UINT32_C(0x800063d8):goto L_800063d8;
 case UINT32_C(0x800063dc):goto L_800063dc;
 case UINT32_C(0x800063e0):goto L_800063e0;
 case UINT32_C(0x800063e4):goto L_800063e4;
 case UINT32_C(0x800063e8):goto L_800063e8;
 case UINT32_C(0x800063ec):goto L_800063ec;
 case UINT32_C(0x800063f0):goto L_800063f0;
 case UINT32_C(0x800063f4):goto L_800063f4;
 case UINT32_C(0x800063f8):goto L_800063f8;
 case UINT32_C(0x800063fc):goto L_800063fc;
 case UINT32_C(0x80006400):goto L_80006400;
 case UINT32_C(0x80006404):goto L_80006404;
 case UINT32_C(0x80006408):goto L_80006408;
 case UINT32_C(0x8000640c):goto L_8000640c;
 case UINT32_C(0x80006410):goto L_80006410;
 case UINT32_C(0x80006414):goto L_80006414;
 case UINT32_C(0x80006418):goto L_80006418;
 case UINT32_C(0x8000641c):goto L_8000641c;
 case UINT32_C(0x80006420):goto L_80006420;
 case UINT32_C(0x80006424):goto L_80006424;
 case UINT32_C(0x80006428):goto L_80006428;
 case UINT32_C(0x8000642c):goto L_8000642c;
 case UINT32_C(0x80006430):goto L_80006430;
 case UINT32_C(0x80006434):goto L_80006434;
 case UINT32_C(0x80006438):goto L_80006438;
 case UINT32_C(0x8000643c):goto L_8000643c;
 case UINT32_C(0x80006440):goto L_80006440;
 case UINT32_C(0x80006444):goto L_80006444;
 case UINT32_C(0x80006448):goto L_80006448;
 case UINT32_C(0x8000644c):goto L_8000644c;
 case UINT32_C(0x80006450):goto L_80006450;
 case UINT32_C(0x80006454):goto L_80006454;
 case UINT32_C(0x80006458):goto L_80006458;
 case UINT32_C(0x8000645c):goto L_8000645c;
 case UINT32_C(0x80006460):goto L_80006460;
 case UINT32_C(0x80006464):goto L_80006464;
 case UINT32_C(0x80006468):goto L_80006468;
 case UINT32_C(0x8000646c):goto L_8000646c;
 case UINT32_C(0x80006470):goto L_80006470;
 case UINT32_C(0x80006474):goto L_80006474;
 case UINT32_C(0x80006478):goto L_80006478;
 case UINT32_C(0x8000647c):goto L_8000647c;
 case UINT32_C(0x80006480):goto L_80006480;
 case UINT32_C(0x80006484):goto L_80006484;
 case UINT32_C(0x80006488):goto L_80006488;
 case UINT32_C(0x8000648c):goto L_8000648c;
 case UINT32_C(0x80006490):goto L_80006490;
 case UINT32_C(0x80006494):goto L_80006494;
 case UINT32_C(0x80006498):goto L_80006498;
 case UINT32_C(0x8000649c):goto L_8000649c;
 case UINT32_C(0x800064a0):goto L_800064a0;
 case UINT32_C(0x800064a4):goto L_800064a4;
 case UINT32_C(0x800064a8):goto L_800064a8;
 case UINT32_C(0x800064ac):goto L_800064ac;
 case UINT32_C(0x800064b0):goto L_800064b0;
 case UINT32_C(0x800064b4):goto L_800064b4;
 case UINT32_C(0x800064b8):goto L_800064b8;
 case UINT32_C(0x800064bc):goto L_800064bc;
 case UINT32_C(0x800064c0):goto L_800064c0;
 case UINT32_C(0x800064c4):goto L_800064c4;
 case UINT32_C(0x800064c8):goto L_800064c8;
 case UINT32_C(0x800064cc):goto L_800064cc;
 case UINT32_C(0x800064d0):goto L_800064d0;
 case UINT32_C(0x800064d4):goto L_800064d4;
 case UINT32_C(0x800064d8):goto L_800064d8;
 case UINT32_C(0x800064dc):goto L_800064dc;
 case UINT32_C(0x800064e0):goto L_800064e0;
 case UINT32_C(0x800064e4):goto L_800064e4;
 case UINT32_C(0x800064e8):goto L_800064e8;
 case UINT32_C(0x800064ec):goto L_800064ec;
 case UINT32_C(0x800064f0):goto L_800064f0;
 case UINT32_C(0x800064f4):goto L_800064f4;
 case UINT32_C(0x800064f8):goto L_800064f8;
 case UINT32_C(0x800064fc):goto L_800064fc;
 case UINT32_C(0x80006500):goto L_80006500;
 case UINT32_C(0x80006504):goto L_80006504;
 case UINT32_C(0x80006508):goto L_80006508;
 case UINT32_C(0x8000650c):goto L_8000650c;
 case UINT32_C(0x80006510):goto L_80006510;
 case UINT32_C(0x80006514):goto L_80006514;
 case UINT32_C(0x80006518):goto L_80006518;
 case UINT32_C(0x8000651c):goto L_8000651c;
 case UINT32_C(0x80006520):goto L_80006520;
 case UINT32_C(0x80006524):goto L_80006524;
 case UINT32_C(0x80006528):goto L_80006528;
 case UINT32_C(0x8000652c):goto L_8000652c;
 case UINT32_C(0x80006530):goto L_80006530;
 case UINT32_C(0x80006534):goto L_80006534;
 case UINT32_C(0x80006538):goto L_80006538;
 case UINT32_C(0x8000653c):goto L_8000653c;
 case UINT32_C(0x80006540):goto L_80006540;
 case UINT32_C(0x80006544):goto L_80006544;
 case UINT32_C(0x80006548):goto L_80006548;
 case UINT32_C(0x8000654c):goto L_8000654c;
 case UINT32_C(0x80006550):goto L_80006550;
 case UINT32_C(0x80006554):goto L_80006554;
 case UINT32_C(0x80006558):goto L_80006558;
 case UINT32_C(0x8000655c):goto L_8000655c;
 case UINT32_C(0x80006560):goto L_80006560;
 case UINT32_C(0x80006564):goto L_80006564;
 case UINT32_C(0x80006568):goto L_80006568;
 case UINT32_C(0x8000656c):goto L_8000656c;
 case UINT32_C(0x80006570):goto L_80006570;
 case UINT32_C(0x80006574):goto L_80006574;
 case UINT32_C(0x80006578):goto L_80006578;
 case UINT32_C(0x8000657c):goto L_8000657c;
 case UINT32_C(0x80006580):goto L_80006580;
 case UINT32_C(0x80006584):goto L_80006584;
 case UINT32_C(0x80006588):goto L_80006588;
 case UINT32_C(0x8000658c):goto L_8000658c;
 case UINT32_C(0x80006590):goto L_80006590;
 case UINT32_C(0x80006594):goto L_80006594;
 case UINT32_C(0x80006598):goto L_80006598;
 case UINT32_C(0x8000659c):goto L_8000659c;
 case UINT32_C(0x800065a0):goto L_800065a0;
 case UINT32_C(0x800065a4):goto L_800065a4;
 case UINT32_C(0x800065a8):goto L_800065a8;
 case UINT32_C(0x800065ac):goto L_800065ac;
 case UINT32_C(0x800065b0):goto L_800065b0;
 case UINT32_C(0x800065b4):goto L_800065b4;
 case UINT32_C(0x800065b8):goto L_800065b8;
 case UINT32_C(0x800065bc):goto L_800065bc;
 case UINT32_C(0x800065c0):goto L_800065c0;
 case UINT32_C(0x800065c4):goto L_800065c4;
 case UINT32_C(0x800065c8):goto L_800065c8;
 case UINT32_C(0x800065cc):goto L_800065cc;
 case UINT32_C(0x800065d0):goto L_800065d0;
 case UINT32_C(0x800065d4):goto L_800065d4;
 case UINT32_C(0x800065d8):goto L_800065d8;
 case UINT32_C(0x800065dc):goto L_800065dc;
 case UINT32_C(0x800065e0):goto L_800065e0;
 case UINT32_C(0x800065e4):goto L_800065e4;
 case UINT32_C(0x800065e8):goto L_800065e8;
 case UINT32_C(0x800065ec):goto L_800065ec;
 case UINT32_C(0x800065f0):goto L_800065f0;
 case UINT32_C(0x800065f4):goto L_800065f4;
 case UINT32_C(0x800065f8):goto L_800065f8;
 case UINT32_C(0x800065fc):goto L_800065fc;
 case UINT32_C(0x80006600):goto L_80006600;
 case UINT32_C(0x80006604):goto L_80006604;
 case UINT32_C(0x80006608):goto L_80006608;
 case UINT32_C(0x8000660c):goto L_8000660c;
 case UINT32_C(0x80006610):goto L_80006610;
 case UINT32_C(0x80006614):goto L_80006614;
 case UINT32_C(0x80006618):goto L_80006618;
 case UINT32_C(0x8000661c):goto L_8000661c;
 case UINT32_C(0x80006620):goto L_80006620;
 case UINT32_C(0x80006624):goto L_80006624;
 case UINT32_C(0x80006628):goto L_80006628;
 case UINT32_C(0x8000662c):goto L_8000662c;
 case UINT32_C(0x80006630):goto L_80006630;
 case UINT32_C(0x80006634):goto L_80006634;
 case UINT32_C(0x80006638):goto L_80006638;
 case UINT32_C(0x8000663c):goto L_8000663c;
 case UINT32_C(0x80006640):goto L_80006640;
 case UINT32_C(0x80006644):goto L_80006644;
 case UINT32_C(0x80006648):goto L_80006648;
 case UINT32_C(0x8000664c):goto L_8000664c;
 case UINT32_C(0x80006650):goto L_80006650;
 case UINT32_C(0x80006654):goto L_80006654;
 case UINT32_C(0x80006658):goto L_80006658;
 case UINT32_C(0x8000665c):goto L_8000665c;
 case UINT32_C(0x80006660):goto L_80006660;
 case UINT32_C(0x80006664):goto L_80006664;
 case UINT32_C(0x80006668):goto L_80006668;
 case UINT32_C(0x8000666c):goto L_8000666c;
 case UINT32_C(0x80006670):goto L_80006670;
 case UINT32_C(0x80006674):goto L_80006674;
 case UINT32_C(0x80006678):goto L_80006678;
 case UINT32_C(0x8000667c):goto L_8000667c;
 case UINT32_C(0x80006680):goto L_80006680;
 case UINT32_C(0x80006684):goto L_80006684;
 case UINT32_C(0x80006688):goto L_80006688;
 case UINT32_C(0x8000668c):goto L_8000668c;
 case UINT32_C(0x80006690):goto L_80006690;
 case UINT32_C(0x80006694):goto L_80006694;
 case UINT32_C(0x80006698):goto L_80006698;
 case UINT32_C(0x8000669c):goto L_8000669c;
 case UINT32_C(0x800066a0):goto L_800066a0;
 case UINT32_C(0x800066a4):goto L_800066a4;
 case UINT32_C(0x800066a8):goto L_800066a8;
 case UINT32_C(0x800066ac):goto L_800066ac;
 case UINT32_C(0x800066b0):goto L_800066b0;
 case UINT32_C(0x800066b4):goto L_800066b4;
 case UINT32_C(0x800066b8):goto L_800066b8;
 case UINT32_C(0x800066bc):goto L_800066bc;
 case UINT32_C(0x800066c0):goto L_800066c0;
 case UINT32_C(0x800066c4):goto L_800066c4;
 case UINT32_C(0x800066c8):goto L_800066c8;
 case UINT32_C(0x800066cc):goto L_800066cc;
 case UINT32_C(0x800066d0):goto L_800066d0;
 case UINT32_C(0x800066d4):goto L_800066d4;
 case UINT32_C(0x800066d8):goto L_800066d8;
 case UINT32_C(0x800066dc):goto L_800066dc;
 case UINT32_C(0x800066e0):goto L_800066e0;
 case UINT32_C(0x800066e4):goto L_800066e4;
 case UINT32_C(0x800066e8):goto L_800066e8;
 case UINT32_C(0x800066ec):goto L_800066ec;
 case UINT32_C(0x800066f0):goto L_800066f0;
 case UINT32_C(0x800066f4):goto L_800066f4;
 case UINT32_C(0x800066f8):goto L_800066f8;
 case UINT32_C(0x800066fc):goto L_800066fc;
 case UINT32_C(0x80006700):goto L_80006700;
 case UINT32_C(0x80006704):goto L_80006704;
 case UINT32_C(0x80006708):goto L_80006708;
 case UINT32_C(0x8000670c):goto L_8000670c;
 case UINT32_C(0x80006710):goto L_80006710;
 case UINT32_C(0x80006714):goto L_80006714;
 case UINT32_C(0x80006718):goto L_80006718;
 case UINT32_C(0x8000671c):goto L_8000671c;
 case UINT32_C(0x80006720):goto L_80006720;
 case UINT32_C(0x80006724):goto L_80006724;
 case UINT32_C(0x80006728):goto L_80006728;
 case UINT32_C(0x8000672c):goto L_8000672c;
 case UINT32_C(0x80006730):goto L_80006730;
 case UINT32_C(0x80006734):goto L_80006734;
 case UINT32_C(0x80006738):goto L_80006738;
 case UINT32_C(0x8000673c):goto L_8000673c;
 case UINT32_C(0x80006740):goto L_80006740;
 case UINT32_C(0x80006744):goto L_80006744;
 case UINT32_C(0x80006748):goto L_80006748;
 case UINT32_C(0x8000674c):goto L_8000674c;
 case UINT32_C(0x80006750):goto L_80006750;
 case UINT32_C(0x80006754):goto L_80006754;
 case UINT32_C(0x80006758):goto L_80006758;
 case UINT32_C(0x8000675c):goto L_8000675c;
 case UINT32_C(0x80006760):goto L_80006760;
 case UINT32_C(0x80006764):goto L_80006764;
 case UINT32_C(0x80006768):goto L_80006768;
 case UINT32_C(0x8000676c):goto L_8000676c;
 case UINT32_C(0x80006770):goto L_80006770;
 case UINT32_C(0x80006774):goto L_80006774;
 case UINT32_C(0x80006778):goto L_80006778;
 case UINT32_C(0x8000677c):goto L_8000677c;
 case UINT32_C(0x80006780):goto L_80006780;
 case UINT32_C(0x80006784):goto L_80006784;
 case UINT32_C(0x80006788):goto L_80006788;
 case UINT32_C(0x8000678c):goto L_8000678c;
 case UINT32_C(0x80006790):goto L_80006790;
 case UINT32_C(0x80006794):goto L_80006794;
 case UINT32_C(0x80006798):goto L_80006798;
 case UINT32_C(0x8000679c):goto L_8000679c;
 case UINT32_C(0x800067a0):goto L_800067a0;
 case UINT32_C(0x800067a4):goto L_800067a4;
 case UINT32_C(0x800067a8):goto L_800067a8;
 case UINT32_C(0x800067ac):goto L_800067ac;
 case UINT32_C(0x800067b0):goto L_800067b0;
 case UINT32_C(0x800067b4):goto L_800067b4;
 case UINT32_C(0x800067b8):goto L_800067b8;
 case UINT32_C(0x800067bc):goto L_800067bc;
 case UINT32_C(0x800067c0):goto L_800067c0;
 case UINT32_C(0x800067c4):goto L_800067c4;
 case UINT32_C(0x800067c8):goto L_800067c8;
 case UINT32_C(0x800067cc):goto L_800067cc;
 case UINT32_C(0x800067d0):goto L_800067d0;
 case UINT32_C(0x800067d4):goto L_800067d4;
 case UINT32_C(0x800067d8):goto L_800067d8;
 case UINT32_C(0x800067dc):goto L_800067dc;
 case UINT32_C(0x800067e0):goto L_800067e0;
 case UINT32_C(0x800067e4):goto L_800067e4;
 case UINT32_C(0x800067e8):goto L_800067e8;
 case UINT32_C(0x800067ec):goto L_800067ec;
 case UINT32_C(0x800067f0):goto L_800067f0;
 case UINT32_C(0x800067f4):goto L_800067f4;
 case UINT32_C(0x800067f8):goto L_800067f8;
 case UINT32_C(0x800067fc):goto L_800067fc;
 case UINT32_C(0x80006800):goto L_80006800;
 case UINT32_C(0x80006804):goto L_80006804;
 case UINT32_C(0x80006808):goto L_80006808;
 case UINT32_C(0x8000680c):goto L_8000680c;
 case UINT32_C(0x80006810):goto L_80006810;
 case UINT32_C(0x80006814):goto L_80006814;
 case UINT32_C(0x80006818):goto L_80006818;
 case UINT32_C(0x8000681c):goto L_8000681c;
 case UINT32_C(0x80006820):goto L_80006820;
 case UINT32_C(0x80006824):goto L_80006824;
 case UINT32_C(0x80006828):goto L_80006828;
 case UINT32_C(0x8000682c):goto L_8000682c;
 case UINT32_C(0x80006830):goto L_80006830;
 case UINT32_C(0x80006834):goto L_80006834;
 case UINT32_C(0x80006838):goto L_80006838;
 case UINT32_C(0x8000683c):goto L_8000683c;
 case UINT32_C(0x80006840):goto L_80006840;
 case UINT32_C(0x80006844):goto L_80006844;
 case UINT32_C(0x80006848):goto L_80006848;
 case UINT32_C(0x8000684c):goto L_8000684c;
 case UINT32_C(0x80006850):goto L_80006850;
 case UINT32_C(0x80006854):goto L_80006854;
 case UINT32_C(0x80006858):goto L_80006858;
 case UINT32_C(0x8000685c):goto L_8000685c;
 case UINT32_C(0x80006860):goto L_80006860;
 case UINT32_C(0x80006864):goto L_80006864;
 case UINT32_C(0x80006868):goto L_80006868;
 case UINT32_C(0x8000686c):goto L_8000686c;
 case UINT32_C(0x80006870):goto L_80006870;
 case UINT32_C(0x80006874):goto L_80006874;
 case UINT32_C(0x80006878):goto L_80006878;
 case UINT32_C(0x8000687c):goto L_8000687c;
 case UINT32_C(0x80006880):goto L_80006880;
 case UINT32_C(0x80006884):goto L_80006884;
 case UINT32_C(0x80006888):goto L_80006888;
 case UINT32_C(0x8000688c):goto L_8000688c;
 case UINT32_C(0x80006890):goto L_80006890;
 case UINT32_C(0x80006894):goto L_80006894;
 case UINT32_C(0x80006898):goto L_80006898;
 case UINT32_C(0x8000689c):goto L_8000689c;
 case UINT32_C(0x800068a0):goto L_800068a0;
 case UINT32_C(0x800068a4):goto L_800068a4;
 case UINT32_C(0x800068a8):goto L_800068a8;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_80006308:
 STEP(UINT32_C(0x80006308)); /* 3c048002 lui a0,zero,0x8002 */
 set(m,4u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000630c));goto dispatch;
L_8000630c:
 STEP(UINT32_C(0x8000630c)); /* 2484e330 addiu a0,a0,-7376 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe330)));target=sx(UINT32_C(0x80006310));goto dispatch;
L_80006310:
 STEP(UINT32_C(0x80006310)); /* 3c020fff lui v0,zero,0xfff */
 set(m,2u,sx(UINT32_C(0x0fff0000)));target=sx(UINT32_C(0x80006314));goto dispatch;
L_80006314:
 STEP(UINT32_C(0x80006314)); /* 2485fe10 addiu a1,a0,-496 */
 set(m,5u,sx((uint32_t)lo(m,4u)+UINT32_C(0xfffffe10)));target=sx(UINT32_C(0x80006318));goto dispatch;
L_80006318:
 STEP(UINT32_C(0x80006318)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x8000631c));goto dispatch;
L_8000631c:
 STEP(UINT32_C(0x8000631c)); /* 00a22824 and a1,a1,v0 */
 set(m,5u,lo(m,5u)&lo(m,2u));target=sx(UINT32_C(0x80006320));goto dispatch;
L_80006320:
 STEP(UINT32_C(0x80006320)); /* 2403001e addiu v1,zero,30 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001e)));target=sx(UINT32_C(0x80006324));goto dispatch;
L_80006324:
 STEP(UINT32_C(0x80006324)); /* 3c06a000 lui a2,zero,0xa000 */
 set(m,6u,sx(UINT32_C(0xa0000000)));target=sx(UINT32_C(0x80006328));goto dispatch;
L_80006328:
 STEP(UINT32_C(0x80006328)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000632c));goto dispatch;
L_8000632c:
 STEP(UINT32_C(0x8000632c)); /* a023e104 sb v1,-0x1efc(at) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe104),&byte,1u);}target=sx(UINT32_C(0x80006330));goto dispatch;
L_80006330:
 STEP(UINT32_C(0x80006330)); /* 00862025 or a0,a0,a2 */
 set(m,4u,lo(m,4u)|lo(m,6u));target=sx(UINT32_C(0x80006334));goto dispatch;
L_80006334:
 STEP(UINT32_C(0x80006334)); /* 3c022000 lui v0,zero,0x2000 */
 set(m,2u,sx(UINT32_C(0x20000000)));target=sx(UINT32_C(0x80006338));goto dispatch;
L_80006338:
 STEP(UINT32_C(0x80006338)); /* ac820000 sw v0,0x0(a0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x8000633c));goto dispatch;
L_8000633c:
 STEP(UINT32_C(0x8000633c)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006340));goto dispatch;
L_80006340:
 STEP(UINT32_C(0x80006340)); /* ac850004 sw a1,0x4(a0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80006344));goto dispatch;
L_80006344:
 STEP(UINT32_C(0x80006344)); /* 3463c420 ori v1,v1,0xc420 */
 set(m,3u,lo(m,3u) | UINT64_C(0xc420));target=sx(UINT32_C(0x80006348));goto dispatch;
L_80006348:
 STEP(UINT32_C(0x80006348)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x8000634c));goto dispatch;
L_8000634c:
 STEP(UINT32_C(0x8000634c)); /* ac600000 sw zero,0x0(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006350));goto dispatch;
L_80006350:
 STEP(UINT32_C(0x80006350)); /* 3404ffff ori a0,zero,0xffff */
 set(m,4u,lo(m,0u) | UINT64_C(0xffff));target=sx(UINT32_C(0x80006354));goto dispatch;
L_80006354:
 STEP(UINT32_C(0x80006354)); /* 3442c430 ori v0,v0,0xc430 */
 set(m,2u,lo(m,2u) | UINT64_C(0xc430));target=sx(UINT32_C(0x80006358));goto dispatch;
L_80006358:
 STEP(UINT32_C(0x80006358)); /* ac450000 sw a1,0x0(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x8000635c));goto dispatch;
L_8000635c:
 STEP(UINT32_C(0x8000635c)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006360));goto dispatch;
L_80006360:
 STEP(UINT32_C(0x80006360)); /* a424e106 sh a0,-0x1efa(at) */
 value16=(uint16_t)lo(m,4u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe106),&value16,2u);target=sx(UINT32_C(0x80006364));goto dispatch;
L_80006364:
 STEP(UINT32_C(0x80006364)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80006368));/* nop */goto dispatch;
L_80006368:
 STEP(UINT32_C(0x80006368)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000636c));goto dispatch;
L_80006370:
 STEP(UINT32_C(0x80006370)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006374));goto dispatch;
L_80006374:
 STEP(UINT32_C(0x80006374)); /* 9042e104 lbu v0,-0x1efc(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe104),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x80006378));goto dispatch;
L_80006378:
 STEP(UINT32_C(0x80006378)); /* 0080602d daddu t4,a0,zero */
 set(m,12u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000637c));goto dispatch;
L_8000637c:
 STEP(UINT32_C(0x8000637c)); /* 240f001f addiu t7,zero,31 */
 set(m,15u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x80006380));goto dispatch;
L_80006380:
 STEP(UINT32_C(0x80006380)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80006384));goto dispatch;
L_80006384:
 STEP(UINT32_C(0x80006384)); /* 304300ff andi v1,v0,0xff */
 set(m,3u,lo(m,2u) & UINT64_C(0xff));target=sx(UINT32_C(0x80006388));goto dispatch;
L_80006388:
 STEP(UINT32_C(0x80006388)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000638c));goto dispatch;
L_8000638c:
 STEP(UINT32_C(0x8000638c)); /* a022e104 sb v0,-0x1efc(at) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe104),&byte,1u);}target=sx(UINT32_C(0x80006390));goto dispatch;
L_80006390:
 STEP(UINT32_C(0x80006390)); /* 146f0008 bne v1,t7,800063b4 */
 {int taken=(lo(m,3u)!=lo(m,15u));STEP(UINT32_C(0x80006394));set(m,25u,lo(m,5u)+lo(m,0u));target=sx(taken?UINT32_C(0x800063b4):UINT32_C(0x80006398));goto dispatch;}
L_80006394:
 STEP(UINT32_C(0x80006394)); /* 00a0c82d daddu t9,a1,zero */
 set(m,25u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006398));goto dispatch;
L_80006398:
 STEP(UINT32_C(0x80006398)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000639c));goto dispatch;
L_8000639c:
 STEP(UINT32_C(0x8000639c)); /* 9442e106 lhu v0,-0x1efa(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe106),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x800063a0));goto dispatch;
L_800063a0:
 STEP(UINT32_C(0x800063a0)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800063a4));goto dispatch;
L_800063a4:
 STEP(UINT32_C(0x800063a4)); /* a020e104 sb zero,-0x1efc(at) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe104),&byte,1u);}target=sx(UINT32_C(0x800063a8));goto dispatch;
L_800063a8:
 STEP(UINT32_C(0x800063a8)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800063ac));goto dispatch;
L_800063ac:
 STEP(UINT32_C(0x800063ac)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800063b0));goto dispatch;
L_800063b0:
 STEP(UINT32_C(0x800063b0)); /* a422e106 sh v0,-0x1efa(at) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe106),&value16,2u);target=sx(UINT32_C(0x800063b4));goto dispatch;
L_800063b4:
 STEP(UINT32_C(0x800063b4)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800063b8));goto dispatch;
L_800063b8:
 STEP(UINT32_C(0x800063b8)); /* 9042e104 lbu v0,-0x1efc(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe104),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x800063bc));goto dispatch;
L_800063bc:
 STEP(UINT32_C(0x800063bc)); /* 24c3000f addiu v1,a2,15 */
 set(m,3u,sx((uint32_t)lo(m,6u)+UINT32_C(0x0000000f)));target=sx(UINT32_C(0x800063c0));goto dispatch;
L_800063c0:
 STEP(UINT32_C(0x800063c0)); /* 3c188002 lui t8,zero,0x8002 */
 set(m,24u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800063c4));goto dispatch;
L_800063c4:
 STEP(UINT32_C(0x800063c4)); /* 2718e140 addiu t8,t8,-7872 */
 set(m,24u,sx((uint32_t)lo(m,24u)+UINT32_C(0xffffe140)));target=sx(UINT32_C(0x800063c8));goto dispatch;
L_800063c8:
 STEP(UINT32_C(0x800063c8)); /* 3c0da000 lui t5,zero,0xa000 */
 set(m,13u,sx(UINT32_C(0xa0000000)));target=sx(UINT32_C(0x800063cc));goto dispatch;
L_800063cc:
 STEP(UINT32_C(0x800063cc)); /* 00021100 sll v0,v0,4 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<4u));target=sx(UINT32_C(0x800063d0));goto dispatch;
L_800063d0:
 STEP(UINT32_C(0x800063d0)); /* 00033102 srl a2,v1,4 */
 set(m,6u,sx((uint32_t)lo(m,3u)>>4u));target=sx(UINT32_C(0x800063d4));goto dispatch;
L_800063d4:
 STEP(UINT32_C(0x800063d4)); /* 00581021 addu v0,v0,t8 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,24u)));target=sx(UINT32_C(0x800063d8));goto dispatch;
L_800063d8:
 STEP(UINT32_C(0x800063d8)); /* 30e30020 andi v1,a3,0x20 */
 set(m,3u,lo(m,7u) & UINT64_C(0x20));target=sx(UINT32_C(0x800063dc));goto dispatch;
L_800063dc:
 STEP(UINT32_C(0x800063dc)); /* 10600012 beq v1,zero,80006428 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x800063e0));set(m,9u,lo(m,2u)|lo(m,13u));target=sx(taken?UINT32_C(0x80006428):UINT32_C(0x800063e4));goto dispatch;}
L_800063e0:
 STEP(UINT32_C(0x800063e0)); /* 004d4825 or t1,v0,t5 */
 set(m,9u,lo(m,2u)|lo(m,13u));target=sx(UINT32_C(0x800063e4));goto dispatch;
L_800063e4:
 STEP(UINT32_C(0x800063e4)); /* 00081400 sll v0,t0,16 */
 set(m,2u,sx((uint32_t)lo(m,8u)<<16u));target=sx(UINT32_C(0x800063e8));goto dispatch;
L_800063e8:
 STEP(UINT32_C(0x800063e8)); /* 30e30002 andi v1,a3,0x2 */
 set(m,3u,lo(m,7u) & UINT64_C(0x2));target=sx(UINT32_C(0x800063ec));goto dispatch;
L_800063ec:
 STEP(UINT32_C(0x800063ec)); /* 00462025 or a0,v0,a2 */
 set(m,4u,lo(m,2u)|lo(m,6u));target=sx(UINT32_C(0x800063f0));goto dispatch;
L_800063f0:
 STEP(UINT32_C(0x800063f0)); /* 10600004 beq v1,zero,80006404 */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x800063f4));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x80006404):UINT32_C(0x800063f8));goto dispatch;}
L_800063f4:
 STEP(UINT32_C(0x800063f4)); /* ad240000 sw a0,0x0(t1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800063f8));goto dispatch;
L_800063f8:
 STEP(UINT32_C(0x800063f8)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800063fc));goto dispatch;
L_800063fc:
 STEP(UINT32_C(0x800063fc)); /* 00821025 or v0,a0,v0 */
 set(m,2u,lo(m,4u)|lo(m,2u));target=sx(UINT32_C(0x80006400));goto dispatch;
L_80006400:
 STEP(UINT32_C(0x80006400)); /* ad220000 sw v0,0x0(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006404));goto dispatch;
L_80006404:
 STEP(UINT32_C(0x80006404)); /* 3c021fff lui v0,zero,0x1fff */
 set(m,2u,sx(UINT32_C(0x1fff0000)));target=sx(UINT32_C(0x80006408));goto dispatch;
L_80006408:
 STEP(UINT32_C(0x80006408)); /* 018d5825 or t3,t4,t5 */
 set(m,11u,lo(m,12u)|lo(m,13u));target=sx(UINT32_C(0x8000640c));goto dispatch;
L_8000640c:
 STEP(UINT32_C(0x8000640c)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x80006410));goto dispatch;
L_80006410:
 STEP(UINT32_C(0x80006410)); /* 30ea0040 andi t2,a3,0x40 */
 set(m,10u,lo(m,7u) & UINT64_C(0x40));target=sx(UINT32_C(0x80006414));goto dispatch;
L_80006414:
 STEP(UINT32_C(0x80006414)); /* 01821024 and v0,t4,v0 */
 set(m,2u,lo(m,12u)&lo(m,2u));target=sx(UINT32_C(0x80006418));goto dispatch;
L_80006418:
 STEP(UINT32_C(0x80006418)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x8000641c));goto dispatch;
L_8000641c:
 STEP(UINT32_C(0x8000641c)); /* ad220004 sw v0,0x4(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80006420));goto dispatch;
L_80006420:
 STEP(UINT32_C(0x80006420)); /* 1000005c beq zero,zero,80006594 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006424));set(m,3u,lo(m,7u) & UINT64_C(0x4));target=sx(taken?UINT32_C(0x80006594):UINT32_C(0x80006428));goto dispatch;}
L_80006424:
 STEP(UINT32_C(0x80006424)); /* 30e30004 andi v1,a3,0x4 */
 set(m,3u,lo(m,7u) & UINT64_C(0x4));target=sx(UINT32_C(0x80006428));goto dispatch;
L_80006428:
 STEP(UINT32_C(0x80006428)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x8000642c));goto dispatch;
L_8000642c:
 STEP(UINT32_C(0x8000642c)); /* 14400032 bne v0,zero,800064f8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80006430));set(m,2u,sx((uint32_t)lo(m,8u)<<16u));target=sx(taken?UINT32_C(0x800064f8):UINT32_C(0x80006434));goto dispatch;}
L_80006430:
 STEP(UINT32_C(0x80006430)); /* 00081400 sll v0,t0,16 */
 set(m,2u,sx((uint32_t)lo(m,8u)<<16u));target=sx(UINT32_C(0x80006434));goto dispatch;
L_80006434:
 STEP(UINT32_C(0x80006434)); /* 3c023000 lui v0,zero,0x3000 */
 set(m,2u,sx(UINT32_C(0x30000000)));target=sx(UINT32_C(0x80006438));goto dispatch;
L_80006438:
 STEP(UINT32_C(0x80006438)); /* 3c058002 lui a1,zero,0x8002 */
 set(m,5u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000643c));goto dispatch;
L_8000643c:
 STEP(UINT32_C(0x8000643c)); /* 24a5e340 addiu a1,a1,-7360 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffe340)));target=sx(UINT32_C(0x80006440));goto dispatch;
L_80006440:
 STEP(UINT32_C(0x80006440)); /* 34420008 ori v0,v0,0x8 */
 set(m,2u,lo(m,2u) | UINT64_C(0x8));target=sx(UINT32_C(0x80006444));goto dispatch;
L_80006444:
 STEP(UINT32_C(0x80006444)); /* 3c0a1fff lui t2,zero,0x1fff */
 set(m,10u,sx(UINT32_C(0x1fff0000)));target=sx(UINT32_C(0x80006448));goto dispatch;
L_80006448:
 STEP(UINT32_C(0x80006448)); /* ad220000 sw v0,0x0(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x8000644c));goto dispatch;
L_8000644c:
 STEP(UINT32_C(0x8000644c)); /* 354affff ori t2,t2,0xffff */
 set(m,10u,lo(m,10u) | UINT64_C(0xffff));target=sx(UINT32_C(0x80006450));goto dispatch;
L_80006450:
 STEP(UINT32_C(0x80006450)); /* 240e0007 addiu t6,zero,7 */
 set(m,14u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000007)));target=sx(UINT32_C(0x80006454));goto dispatch;
L_80006454:
 STEP(UINT32_C(0x80006454)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006458));goto dispatch;
L_80006458:
 STEP(UINT32_C(0x80006458)); /* 9042e104 lbu v0,-0x1efc(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe104),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x8000645c));goto dispatch;
L_8000645c:
 STEP(UINT32_C(0x8000645c)); /* 000211c0 sll v0,v0,7 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<7u));target=sx(UINT32_C(0x80006460));goto dispatch;
L_80006460:
 STEP(UINT32_C(0x80006460)); /* 00451021 addu v0,v0,a1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x80006464));goto dispatch;
L_80006464:
 STEP(UINT32_C(0x80006464)); /* 004a1024 and v0,v0,t2 */
 set(m,2u,lo(m,2u)&lo(m,10u));target=sx(UINT32_C(0x80006468));goto dispatch;
L_80006468:
 STEP(UINT32_C(0x80006468)); /* ad220004 sw v0,0x4(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x8000646c));goto dispatch;
L_8000646c:
 STEP(UINT32_C(0x8000646c)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006470));goto dispatch;
L_80006470:
 STEP(UINT32_C(0x80006470)); /* 9063e104 lbu v1,-0x1efc(v1) */
 {uint8_t byte;READ((uint32_t)lo(m,3u)+UINT32_C(0xffffe104),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x80006474));goto dispatch;
L_80006474:
 STEP(UINT32_C(0x80006474)); /* 000311c0 sll v0,v1,7 */
 set(m,2u,sx((uint32_t)lo(m,3u)<<7u));target=sx(UINT32_C(0x80006478));goto dispatch;
L_80006478:
 STEP(UINT32_C(0x80006478)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x8000647c));goto dispatch;
L_8000647c:
 STEP(UINT32_C(0x8000647c)); /* 00451021 addu v0,v0,a1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x80006480));goto dispatch;
L_80006480:
 STEP(UINT32_C(0x80006480)); /* 306400ff andi a0,v1,0xff */
 set(m,4u,lo(m,3u) & UINT64_C(0xff));target=sx(UINT32_C(0x80006484));goto dispatch;
L_80006484:
 STEP(UINT32_C(0x80006484)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006488));goto dispatch;
L_80006488:
 STEP(UINT32_C(0x80006488)); /* a023e104 sb v1,-0x1efc(at) */
 {uint8_t byte=(uint8_t)lo(m,3u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe104),&byte,1u);}target=sx(UINT32_C(0x8000648c));goto dispatch;
L_8000648c:
 STEP(UINT32_C(0x8000648c)); /* 148f0008 bne a0,t7,800064b0 */
 {int taken=(lo(m,4u)!=lo(m,15u));STEP(UINT32_C(0x80006490));set(m,11u,lo(m,2u)|lo(m,13u));target=sx(taken?UINT32_C(0x800064b0):UINT32_C(0x80006494));goto dispatch;}
L_80006490:
 STEP(UINT32_C(0x80006490)); /* 004d5825 or t3,v0,t5 */
 set(m,11u,lo(m,2u)|lo(m,13u));target=sx(UINT32_C(0x80006494));goto dispatch;
L_80006494:
 STEP(UINT32_C(0x80006494)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006498));goto dispatch;
L_80006498:
 STEP(UINT32_C(0x80006498)); /* 9442e106 lhu v0,-0x1efa(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe106),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x8000649c));goto dispatch;
L_8000649c:
 STEP(UINT32_C(0x8000649c)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800064a0));goto dispatch;
L_800064a0:
 STEP(UINT32_C(0x800064a0)); /* a020e104 sb zero,-0x1efc(at) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe104),&byte,1u);}target=sx(UINT32_C(0x800064a4));goto dispatch;
L_800064a4:
 STEP(UINT32_C(0x800064a4)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800064a8));goto dispatch;
L_800064a8:
 STEP(UINT32_C(0x800064a8)); /* 3c018002 lui at,zero,0x8002 */
 set(m,1u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800064ac));goto dispatch;
L_800064ac:
 STEP(UINT32_C(0x800064ac)); /* a422e106 sh v0,-0x1efa(at) */
 value16=(uint16_t)lo(m,2u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0xffffe106),&value16,2u);target=sx(UINT32_C(0x800064b0));goto dispatch;
L_800064b0:
 STEP(UINT32_C(0x800064b0)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800064b4));goto dispatch;
L_800064b4:
 STEP(UINT32_C(0x800064b4)); /* 9042e104 lbu v0,-0x1efc(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe104),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x800064b8));goto dispatch;
L_800064b8:
 STEP(UINT32_C(0x800064b8)); /* 00082400 sll a0,t0,16 */
 set(m,4u,sx((uint32_t)lo(m,8u)<<16u));target=sx(UINT32_C(0x800064bc));goto dispatch;
L_800064bc:
 STEP(UINT32_C(0x800064bc)); /* 24c3fff9 addiu v1,a2,-7 */
 set(m,3u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff9)));target=sx(UINT32_C(0x800064c0));goto dispatch;
L_800064c0:
 STEP(UINT32_C(0x800064c0)); /* 30e50002 andi a1,a3,0x2 */
 set(m,5u,lo(m,7u) & UINT64_C(0x2));target=sx(UINT32_C(0x800064c4));goto dispatch;
L_800064c4:
 STEP(UINT32_C(0x800064c4)); /* 00021100 sll v0,v0,4 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<4u));target=sx(UINT32_C(0x800064c8));goto dispatch;
L_800064c8:
 STEP(UINT32_C(0x800064c8)); /* 00832025 or a0,a0,v1 */
 set(m,4u,lo(m,4u)|lo(m,3u));target=sx(UINT32_C(0x800064cc));goto dispatch;
L_800064cc:
 STEP(UINT32_C(0x800064cc)); /* 00581021 addu v0,v0,t8 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,24u)));target=sx(UINT32_C(0x800064d0));goto dispatch;
L_800064d0:
 STEP(UINT32_C(0x800064d0)); /* 004d4825 or t1,v0,t5 */
 set(m,9u,lo(m,2u)|lo(m,13u));target=sx(UINT32_C(0x800064d4));goto dispatch;
L_800064d4:
 STEP(UINT32_C(0x800064d4)); /* 10a00004 beq a1,zero,800064e8 */
 {int taken=(lo(m,5u)==lo(m,0u));STEP(UINT32_C(0x800064d8));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x800064e8):UINT32_C(0x800064dc));goto dispatch;}
L_800064d8:
 STEP(UINT32_C(0x800064d8)); /* ad240000 sw a0,0x0(t1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800064dc));goto dispatch;
L_800064dc:
 STEP(UINT32_C(0x800064dc)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800064e0));goto dispatch;
L_800064e0:
 STEP(UINT32_C(0x800064e0)); /* 00821025 or v0,a0,v0 */
 set(m,2u,lo(m,4u)|lo(m,2u));target=sx(UINT32_C(0x800064e4));goto dispatch;
L_800064e4:
 STEP(UINT32_C(0x800064e4)); /* ad220000 sw v0,0x0(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800064e8));goto dispatch;
L_800064e8:
 STEP(UINT32_C(0x800064e8)); /* 25820070 addiu v0,t4,112 */
 set(m,2u,sx((uint32_t)lo(m,12u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x800064ec));goto dispatch;
L_800064ec:
 STEP(UINT32_C(0x800064ec)); /* 004a1024 and v0,v0,t2 */
 set(m,2u,lo(m,2u)&lo(m,10u));target=sx(UINT32_C(0x800064f0));goto dispatch;
L_800064f0:
 STEP(UINT32_C(0x800064f0)); /* 10000019 beq zero,zero,80006558 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800064f4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(taken?UINT32_C(0x80006558):UINT32_C(0x800064f8));goto dispatch;}
L_800064f4:
 STEP(UINT32_C(0x800064f4)); /* ad220004 sw v0,0x4(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x800064f8));goto dispatch;
L_800064f8:
 STEP(UINT32_C(0x800064f8)); /* 24c30001 addiu v1,a2,1 */
 set(m,3u,sx((uint32_t)lo(m,6u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800064fc));goto dispatch;
L_800064fc:
 STEP(UINT32_C(0x800064fc)); /* 00434025 or t0,v0,v1 */
 set(m,8u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x80006500));goto dispatch;
L_80006500:
 STEP(UINT32_C(0x80006500)); /* 30e40002 andi a0,a3,0x2 */
 set(m,4u,lo(m,7u) & UINT64_C(0x2));target=sx(UINT32_C(0x80006504));goto dispatch;
L_80006504:
 STEP(UINT32_C(0x80006504)); /* 10800004 beq a0,zero,80006518 */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x80006508));value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x80006518):UINT32_C(0x8000650c));goto dispatch;}
L_80006508:
 STEP(UINT32_C(0x80006508)); /* ad280000 sw t0,0x0(t1) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x8000650c));goto dispatch;
L_8000650c:
 STEP(UINT32_C(0x8000650c)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80006510));goto dispatch;
L_80006510:
 STEP(UINT32_C(0x80006510)); /* 01021025 or v0,t0,v0 */
 set(m,2u,lo(m,8u)|lo(m,2u));target=sx(UINT32_C(0x80006514));goto dispatch;
L_80006514:
 STEP(UINT32_C(0x80006514)); /* ad220000 sw v0,0x0(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006518));goto dispatch;
L_80006518:
 STEP(UINT32_C(0x80006518)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000651c));goto dispatch;
L_8000651c:
 STEP(UINT32_C(0x8000651c)); /* 9063e104 lbu v1,-0x1efc(v1) */
 {uint8_t byte;READ((uint32_t)lo(m,3u)+UINT32_C(0xffffe104),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x80006520));goto dispatch;
L_80006520:
 STEP(UINT32_C(0x80006520)); /* 3c048002 lui a0,zero,0x8002 */
 set(m,4u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006524));goto dispatch;
L_80006524:
 STEP(UINT32_C(0x80006524)); /* 2484e340 addiu a0,a0,-7360 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffe340)));target=sx(UINT32_C(0x80006528));goto dispatch;
L_80006528:
 STEP(UINT32_C(0x80006528)); /* 3c021fff lui v0,zero,0x1fff */
 set(m,2u,sx(UINT32_C(0x1fff0000)));target=sx(UINT32_C(0x8000652c));goto dispatch;
L_8000652c:
 STEP(UINT32_C(0x8000652c)); /* 00c0702d daddu t6,a2,zero */
 set(m,14u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x80006530));goto dispatch;
L_80006530:
 STEP(UINT32_C(0x80006530)); /* 000319c0 sll v1,v1,7 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<7u));target=sx(UINT32_C(0x80006534));goto dispatch;
L_80006534:
 STEP(UINT32_C(0x80006534)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x80006538));goto dispatch;
L_80006538:
 STEP(UINT32_C(0x80006538)); /* 00641821 addu v1,v1,a0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x8000653c));goto dispatch;
L_8000653c:
 STEP(UINT32_C(0x8000653c)); /* 00621824 and v1,v1,v0 */
 set(m,3u,lo(m,3u)&lo(m,2u));target=sx(UINT32_C(0x80006540));goto dispatch;
L_80006540:
 STEP(UINT32_C(0x80006540)); /* ad230004 sw v1,0x4(t1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80006544));goto dispatch;
L_80006544:
 STEP(UINT32_C(0x80006544)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006548));goto dispatch;
L_80006548:
 STEP(UINT32_C(0x80006548)); /* 9042e104 lbu v0,-0x1efc(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe104),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x8000654c));goto dispatch;
L_8000654c:
 STEP(UINT32_C(0x8000654c)); /* 000211c0 sll v0,v0,7 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<7u));target=sx(UINT32_C(0x80006550));goto dispatch;
L_80006550:
 STEP(UINT32_C(0x80006550)); /* 00441021 addu v0,v0,a0 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80006554));goto dispatch;
L_80006554:
 STEP(UINT32_C(0x80006554)); /* 004d5825 or t3,v0,t5 */
 set(m,11u,lo(m,2u)|lo(m,13u));target=sx(UINT32_C(0x80006558));goto dispatch;
L_80006558:
 STEP(UINT32_C(0x80006558)); /* 30ea0040 andi t2,a3,0x40 */
 set(m,10u,lo(m,7u) & UINT64_C(0x40));target=sx(UINT32_C(0x8000655c));goto dispatch;
L_8000655c:
 STEP(UINT32_C(0x8000655c)); /* 25680010 addiu t0,t3,16 */
 set(m,8u,sx((uint32_t)lo(m,11u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006560));goto dispatch;
L_80006560:
 STEP(UINT32_C(0x80006560)); /* 19c0000c blez t6,zero,80006594 */
 {int taken=((int64_t)lo(m,14u)<=0);STEP(UINT32_C(0x80006564));set(m,3u,lo(m,7u) & UINT64_C(0x4));target=sx(taken?UINT32_C(0x80006594):UINT32_C(0x80006568));goto dispatch;}
L_80006564:
 STEP(UINT32_C(0x80006564)); /* 30e30004 andi v1,a3,0x4 */
 set(m,3u,lo(m,7u) & UINT64_C(0x4));target=sx(UINT32_C(0x80006568));goto dispatch;
L_80006568:
 STEP(UINT32_C(0x80006568)); /* 3c02a000 lui v0,zero,0xa000 */
 set(m,2u,sx(UINT32_C(0xa0000000)));target=sx(UINT32_C(0x8000656c));goto dispatch;
L_8000656c:
 STEP(UINT32_C(0x8000656c)); /* 0100482d daddu t1,t0,zero */
 set(m,9u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x80006570));goto dispatch;
L_80006570:
 STEP(UINT32_C(0x80006570)); /* 01822025 or a0,t4,v0 */
 set(m,4u,lo(m,12u)|lo(m,2u));target=sx(UINT32_C(0x80006574));goto dispatch;
L_80006574:
 STEP(UINT32_C(0x80006574)); /* 01c0402d daddu t0,t6,zero */
 set(m,8u,lo(m,14u)+lo(m,0u));target=sx(UINT32_C(0x80006578));goto dispatch;
L_80006578:
 STEP(UINT32_C(0x80006578)); /* 78820000 lq v0,0x0(a0) */
 {uint32_t q[4];READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x8000657c));goto dispatch;
L_8000657c:
 STEP(UINT32_C(0x8000657c)); /* 2508ffff addiu t0,t0,-1 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80006580));goto dispatch;
L_80006580:
 STEP(UINT32_C(0x80006580)); /* 24840010 addiu a0,a0,16 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006584));goto dispatch;
L_80006584:
 STEP(UINT32_C(0x80006584)); /* 7d220000 sq v0,0x0(t1) */
 WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),m->gpr[2],16u);target=sx(UINT32_C(0x80006588));goto dispatch;
L_80006588:
 STEP(UINT32_C(0x80006588)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000658c));goto dispatch;
L_8000658c:
 STEP(UINT32_C(0x8000658c)); /* 1500fffa bne t0,zero,80006578 */
 {int taken=(lo(m,8u)!=lo(m,0u));STEP(UINT32_C(0x80006590));set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x80006578):UINT32_C(0x80006594));goto dispatch;}
L_80006590:
 STEP(UINT32_C(0x80006590)); /* 25290010 addiu t1,t1,16 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006594));goto dispatch;
L_80006594:
 STEP(UINT32_C(0x80006594)); /* 3c054000 lui a1,zero,0x4000 */
 set(m,5u,sx(UINT32_C(0x40000000)));target=sx(UINT32_C(0x80006598));goto dispatch;
L_80006598:
 STEP(UINT32_C(0x80006598)); /* 11400003 beq t2,zero,800065a8 */
 {int taken=(lo(m,10u)==lo(m,0u));STEP(UINT32_C(0x8000659c));if(lo(m,3u)==0u)set(m,5u,lo(m,0u));target=sx(taken?UINT32_C(0x800065a8):UINT32_C(0x800065a0));goto dispatch;}
L_8000659c:
 STEP(UINT32_C(0x8000659c)); /* 0003280a movz a1,zero,v1 */
 if(lo(m,3u)==0u)set(m,5u,lo(m,0u));target=sx(UINT32_C(0x800065a0));goto dispatch;
L_800065a0:
 STEP(UINT32_C(0x800065a0)); /* 3c028000 lui v0,zero,0x8000 */
 set(m,2u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800065a4));goto dispatch;
L_800065a4:
 STEP(UINT32_C(0x800065a4)); /* 00a22825 or a1,a1,v0 */
 set(m,5u,lo(m,5u)|lo(m,2u));target=sx(UINT32_C(0x800065a8));goto dispatch;
L_800065a8:
 STEP(UINT32_C(0x800065a8)); /* 3c0200ff lui v0,zero,0xff */
 set(m,2u,sx(UINT32_C(0x00ff0000)));target=sx(UINT32_C(0x800065ac));goto dispatch;
L_800065ac:
 STEP(UINT32_C(0x800065ac)); /* 00061880 sll v1,a2,2 */
 set(m,3u,sx((uint32_t)lo(m,6u)<<2u));target=sx(UINT32_C(0x800065b0));goto dispatch;
L_800065b0:
 STEP(UINT32_C(0x800065b0)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x800065b4));goto dispatch;
L_800065b4:
 STEP(UINT32_C(0x800065b4)); /* ad630004 sw v1,0x4(t3) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x800065b8));goto dispatch;
L_800065b8:
 STEP(UINT32_C(0x800065b8)); /* 03221024 and v0,t9,v0 */
 set(m,2u,lo(m,25u)&lo(m,2u));target=sx(UINT32_C(0x800065bc));goto dispatch;
L_800065bc:
 STEP(UINT32_C(0x800065bc)); /* 00451025 or v0,v0,a1 */
 set(m,2u,lo(m,2u)|lo(m,5u));target=sx(UINT32_C(0x800065c0));goto dispatch;
L_800065c0:
 STEP(UINT32_C(0x800065c0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800065c4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_800065c4:
 STEP(UINT32_C(0x800065c4)); /* ad620000 sw v0,0x0(t3) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,11u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800065c8));goto dispatch;
L_800065c8:
 STEP(UINT32_C(0x800065c8)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x800065cc));goto dispatch;
L_800065cc:
 STEP(UINT32_C(0x800065cc)); /* 3c058002 lui a1,zero,0x8002 */
 set(m,5u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800065d0));goto dispatch;
L_800065d0:
 STEP(UINT32_C(0x800065d0)); /* 24a5e140 addiu a1,a1,-7872 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffe140)));target=sx(UINT32_C(0x800065d4));goto dispatch;
L_800065d4:
 STEP(UINT32_C(0x800065d4)); /* 3463c430 ori v1,v1,0xc430 */
 set(m,3u,lo(m,3u) | UINT64_C(0xc430));target=sx(UINT32_C(0x800065d8));goto dispatch;
L_800065d8:
 STEP(UINT32_C(0x800065d8)); /* 3c041fff lui a0,zero,0x1fff */
 set(m,4u,sx(UINT32_C(0x1fff0000)));target=sx(UINT32_C(0x800065dc));goto dispatch;
L_800065dc:
 STEP(UINT32_C(0x800065dc)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800065e0));goto dispatch;
L_800065e0:
 STEP(UINT32_C(0x800065e0)); /* 3484ffff ori a0,a0,0xffff */
 set(m,4u,lo(m,4u) | UINT64_C(0xffff));target=sx(UINT32_C(0x800065e4));goto dispatch;
L_800065e4:
 STEP(UINT32_C(0x800065e4)); /* 2403ffff addiu v1,zero,-1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x800065e8));goto dispatch;
L_800065e8:
 STEP(UINT32_C(0x800065e8)); /* 2406001e addiu a2,zero,30 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001e)));target=sx(UINT32_C(0x800065ec));goto dispatch;
L_800065ec:
 STEP(UINT32_C(0x800065ec)); /* 00451023 subu v0,v0,a1 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x800065f0));goto dispatch;
L_800065f0:
 STEP(UINT32_C(0x800065f0)); /* 00441024 and v0,v0,a0 */
 set(m,2u,lo(m,2u)&lo(m,4u));target=sx(UINT32_C(0x800065f4));goto dispatch;
L_800065f4:
 STEP(UINT32_C(0x800065f4)); /* 3c058002 lui a1,zero,0x8002 */
 set(m,5u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800065f8));goto dispatch;
L_800065f8:
 STEP(UINT32_C(0x800065f8)); /* 90a5e104 lbu a1,-0x1efc(a1) */
 {uint8_t byte;READ((uint32_t)lo(m,5u)+UINT32_C(0xffffe104),&byte,1u);set(m,5u,byte);}target=sx(UINT32_C(0x800065fc));goto dispatch;
L_800065fc:
 STEP(UINT32_C(0x800065fc)); /* 00021102 srl v0,v0,4 */
 set(m,2u,sx((uint32_t)lo(m,2u)>>4u));target=sx(UINT32_C(0x80006600));goto dispatch;
L_80006600:
 STEP(UINT32_C(0x80006600)); /* 2444ffff addiu a0,v0,-1 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80006604));goto dispatch;
L_80006604:
 STEP(UINT32_C(0x80006604)); /* 0064182a slt v1,v1,a0 */
 set(m,3u,((int64_t)lo(m,3u)<(int64_t)lo(m,4u)));target=sx(UINT32_C(0x80006608));goto dispatch;
L_80006608:
 STEP(UINT32_C(0x80006608)); /* 00c3200a movz a0,a2,v1 */
 if(lo(m,3u)==0u)set(m,4u,lo(m,6u));target=sx(UINT32_C(0x8000660c));goto dispatch;
L_8000660c:
 STEP(UINT32_C(0x8000660c)); /* 14850008 bne a0,a1,80006630 */
 {int taken=(lo(m,4u)!=lo(m,5u));STEP(UINT32_C(0x80006610));set(m,2u,((int64_t)lo(m,4u)<(int64_t)lo(m,5u)));target=sx(taken?UINT32_C(0x80006630):UINT32_C(0x80006614));goto dispatch;}
L_80006610:
 STEP(UINT32_C(0x80006610)); /* 0085102a slt v0,a0,a1 */
 set(m,2u,((int64_t)lo(m,4u)<(int64_t)lo(m,5u)));target=sx(UINT32_C(0x80006614));goto dispatch;
L_80006614:
 STEP(UINT32_C(0x80006614)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006618));goto dispatch;
L_80006618:
 STEP(UINT32_C(0x80006618)); /* 2405001e addiu a1,zero,30 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001e)));target=sx(UINT32_C(0x8000661c));goto dispatch;
L_8000661c:
 STEP(UINT32_C(0x8000661c)); /* 3442c420 ori v0,v0,0xc420 */
 set(m,2u,lo(m,2u) | UINT64_C(0xc420));target=sx(UINT32_C(0x80006620));goto dispatch;
L_80006620:
 STEP(UINT32_C(0x80006620)); /* 2404001f addiu a0,zero,31 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x80006624));goto dispatch;
L_80006624:
 STEP(UINT32_C(0x80006624)); /* 8c430000 lw v1,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80006628));goto dispatch;
L_80006628:
 STEP(UINT32_C(0x80006628)); /* 10000007 beq zero,zero,80006648 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8000662c));if(lo(m,3u)==0u)set(m,5u,lo(m,4u));target=sx(taken?UINT32_C(0x80006648):UINT32_C(0x80006630));goto dispatch;}
L_8000662c:
 STEP(UINT32_C(0x8000662c)); /* 0083280a movz a1,a0,v1 */
 if(lo(m,3u)==0u)set(m,5u,lo(m,4u));target=sx(UINT32_C(0x80006630));goto dispatch;
L_80006630:
 STEP(UINT32_C(0x80006630)); /* 10400004 beq v0,zero,80006644 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80006634));set(m,2u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,5u)));target=sx(taken?UINT32_C(0x80006644):UINT32_C(0x80006638));goto dispatch;}
L_80006634:
 STEP(UINT32_C(0x80006634)); /* 00851023 subu v0,a0,a1 */
 set(m,2u,sx((uint32_t)lo(m,4u)-(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x80006638));goto dispatch;
L_80006638:
 STEP(UINT32_C(0x80006638)); /* 2482001e addiu v0,a0,30 */
 set(m,2u,sx((uint32_t)lo(m,4u)+UINT32_C(0x0000001e)));target=sx(UINT32_C(0x8000663c));goto dispatch;
L_8000663c:
 STEP(UINT32_C(0x8000663c)); /* 10000002 beq zero,zero,80006648 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80006640));set(m,5u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,5u)));target=sx(taken?UINT32_C(0x80006648):UINT32_C(0x80006644));goto dispatch;}
L_80006640:
 STEP(UINT32_C(0x80006640)); /* 00452823 subu a1,v0,a1 */
 set(m,5u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x80006644));goto dispatch;
L_80006644:
 STEP(UINT32_C(0x80006644)); /* 2445ffff addiu a1,v0,-1 */
 set(m,5u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80006648));goto dispatch;
L_80006648:
 STEP(UINT32_C(0x80006648)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x8000664c));set(m,2u,lo(m,5u)+lo(m,0u));goto dispatch;
L_8000664c:
 STEP(UINT32_C(0x8000664c)); /* 00a0102d daddu v0,a1,zero */
 set(m,2u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006650));goto dispatch;
L_80006650:
 STEP(UINT32_C(0x80006650)); /* 0080302d daddu a2,a0,zero */
 set(m,6u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80006654));goto dispatch;
L_80006654:
 STEP(UINT32_C(0x80006654)); /* 2402001f addiu v0,zero,31 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x80006658));goto dispatch;
L_80006658:
 STEP(UINT32_C(0x80006658)); /* 10c20020 beq a2,v0,800066dc */
 {int taken=(lo(m,6u)==lo(m,2u));STEP(UINT32_C(0x8000665c));set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001e)));target=sx(taken?UINT32_C(0x800066dc):UINT32_C(0x80006660));goto dispatch;}
L_8000665c:
 STEP(UINT32_C(0x8000665c)); /* 2405001e addiu a1,zero,30 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001e)));target=sx(UINT32_C(0x80006660));goto dispatch;
L_80006660:
 STEP(UINT32_C(0x80006660)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006664));goto dispatch;
L_80006664:
 STEP(UINT32_C(0x80006664)); /* 9042e104 lbu v0,-0x1efc(v0) */
 {uint8_t byte;READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe104),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x80006668));goto dispatch;
L_80006668:
 STEP(UINT32_C(0x80006668)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x8000666c));goto dispatch;
L_8000666c:
 STEP(UINT32_C(0x8000666c)); /* 2463e140 addiu v1,v1,-7872 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffe140)));target=sx(UINT32_C(0x80006670));goto dispatch;
L_80006670:
 STEP(UINT32_C(0x80006670)); /* 3c04a000 lui a0,zero,0xa000 */
 set(m,4u,sx(UINT32_C(0xa0000000)));target=sx(UINT32_C(0x80006674));goto dispatch;
L_80006674:
 STEP(UINT32_C(0x80006674)); /* 00021100 sll v0,v0,4 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<4u));target=sx(UINT32_C(0x80006678));goto dispatch;
L_80006678:
 STEP(UINT32_C(0x80006678)); /* 00431021 addu v0,v0,v1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x8000667c));goto dispatch;
L_8000667c:
 STEP(UINT32_C(0x8000667c)); /* 14c50019 bne a2,a1,800066e4 */
 {int taken=(lo(m,6u)!=lo(m,5u));STEP(UINT32_C(0x80006680));set(m,8u,lo(m,2u)|lo(m,4u));target=sx(taken?UINT32_C(0x800066e4):UINT32_C(0x80006684));goto dispatch;}
L_80006680:
 STEP(UINT32_C(0x80006680)); /* 00444025 or t0,v0,a0 */
 set(m,8u,lo(m,2u)|lo(m,4u));target=sx(UINT32_C(0x80006684));goto dispatch;
L_80006684:
 STEP(UINT32_C(0x80006684)); /* 8d020000 lw v0,0x0(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006688));goto dispatch;
L_80006688:
 STEP(UINT32_C(0x80006688)); /* 3c038c00 lui v1,zero,0x8c00 */
 set(m,3u,sx(UINT32_C(0x8c000000)));target=sx(UINT32_C(0x8000668c));goto dispatch;
L_8000668c:
 STEP(UINT32_C(0x8000668c)); /* 3c06b000 lui a2,zero,0xb000 */
 set(m,6u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006690));goto dispatch;
L_80006690:
 STEP(UINT32_C(0x80006690)); /* 3c043000 lui a0,zero,0x3000 */
 set(m,4u,sx(UINT32_C(0x30000000)));target=sx(UINT32_C(0x80006694));goto dispatch;
L_80006694:
 STEP(UINT32_C(0x80006694)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x80006698));goto dispatch;
L_80006698:
 STEP(UINT32_C(0x80006698)); /* 34c6c420 ori a2,a2,0xc420 */
 set(m,6u,lo(m,6u) | UINT64_C(0xc420));target=sx(UINT32_C(0x8000669c));goto dispatch;
L_8000669c:
 STEP(UINT32_C(0x8000669c)); /* ad020000 sw v0,0x0(t0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800066a0));goto dispatch;
L_800066a0:
 STEP(UINT32_C(0x800066a0)); /* 3c05b000 lui a1,zero,0xb000 */
 set(m,5u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x800066a4));goto dispatch;
L_800066a4:
 STEP(UINT32_C(0x800066a4)); /* 00441025 or v0,v0,a0 */
 set(m,2u,lo(m,2u)|lo(m,4u));target=sx(UINT32_C(0x800066a8));goto dispatch;
L_800066a8:
 STEP(UINT32_C(0x800066a8)); /* 34a5c410 ori a1,a1,0xc410 */
 set(m,5u,lo(m,5u) | UINT64_C(0xc410));target=sx(UINT32_C(0x800066ac));goto dispatch;
L_800066ac:
 STEP(UINT32_C(0x800066ac)); /* 8cc70000 lw a3,0x0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x800066b0));goto dispatch;
L_800066b0:
 STEP(UINT32_C(0x800066b0)); /* 3c031fff lui v1,zero,0x1fff */
 set(m,3u,sx(UINT32_C(0x1fff0000)));target=sx(UINT32_C(0x800066b4));goto dispatch;
L_800066b4:
 STEP(UINT32_C(0x800066b4)); /* 3c04b000 lui a0,zero,0xb000 */
 set(m,4u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x800066b8));goto dispatch;
L_800066b8:
 STEP(UINT32_C(0x800066b8)); /* 3463ffff ori v1,v1,0xffff */
 set(m,3u,lo(m,3u) | UINT64_C(0xffff));target=sx(UINT32_C(0x800066bc));goto dispatch;
L_800066bc:
 STEP(UINT32_C(0x800066bc)); /* 00471025 or v0,v0,a3 */
 set(m,2u,lo(m,2u)|lo(m,7u));target=sx(UINT32_C(0x800066c0));goto dispatch;
L_800066c0:
 STEP(UINT32_C(0x800066c0)); /* 01031824 and v1,t0,v1 */
 set(m,3u,lo(m,8u)&lo(m,3u));target=sx(UINT32_C(0x800066c4));goto dispatch;
L_800066c4:
 STEP(UINT32_C(0x800066c4)); /* ad020000 sw v0,0x0(t0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800066c8));goto dispatch;
L_800066c8:
 STEP(UINT32_C(0x800066c8)); /* 3484c430 ori a0,a0,0xc430 */
 set(m,4u,lo(m,4u) | UINT64_C(0xc430));target=sx(UINT32_C(0x800066cc));goto dispatch;
L_800066cc:
 STEP(UINT32_C(0x800066cc)); /* 8ca20000 lw v0,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800066d0));goto dispatch;
L_800066d0:
 STEP(UINT32_C(0x800066d0)); /* ad020004 sw v0,0x4(t0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x800066d4));goto dispatch;
L_800066d4:
 STEP(UINT32_C(0x800066d4)); /* acc00000 sw zero,0x0(a2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800066d8));goto dispatch;
L_800066d8:
 STEP(UINT32_C(0x800066d8)); /* ac830000 sw v1,0x0(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800066dc));goto dispatch;
L_800066dc:
 STEP(UINT32_C(0x800066dc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800066e0));/* nop */goto dispatch;
L_800066e0:
 STEP(UINT32_C(0x800066e0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800066e4));goto dispatch;
L_800066e4:
 STEP(UINT32_C(0x800066e4)); /* 8d020000 lw v0,0x0(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800066e8));goto dispatch;
L_800066e8:
 STEP(UINT32_C(0x800066e8)); /* 3c033000 lui v1,zero,0x3000 */
 set(m,3u,sx(UINT32_C(0x30000000)));target=sx(UINT32_C(0x800066ec));goto dispatch;
L_800066ec:
 STEP(UINT32_C(0x800066ec)); /* 00431025 or v0,v0,v1 */
 set(m,2u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x800066f0));goto dispatch;
L_800066f0:
 STEP(UINT32_C(0x800066f0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800066f4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_800066f4:
 STEP(UINT32_C(0x800066f4)); /* ad020000 sw v0,0x0(t0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800066f8));goto dispatch;
L_800066f8:
 STEP(UINT32_C(0x800066f8)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x800066fc));goto dispatch;
L_800066fc:
 STEP(UINT32_C(0x800066fc)); /* 3c08b000 lui t0,zero,0xb000 */
 set(m,8u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006700));goto dispatch;
L_80006700:
 STEP(UINT32_C(0x80006700)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x80006704));goto dispatch;
L_80006704:
 STEP(UINT32_C(0x80006704)); /* 3508f520 ori t0,t0,0xf520 */
 set(m,8u,lo(m,8u) | UINT64_C(0xf520));target=sx(UINT32_C(0x80006708));goto dispatch;
L_80006708:
 STEP(UINT32_C(0x80006708)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x8000670c));goto dispatch;
L_8000670c:
 STEP(UINT32_C(0x8000670c)); /* 3c030001 lui v1,zero,0x1 */
 set(m,3u,sx(UINT32_C(0x00010000)));target=sx(UINT32_C(0x80006710));goto dispatch;
L_80006710:
 STEP(UINT32_C(0x80006710)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80006714));goto dispatch;
L_80006714:
 STEP(UINT32_C(0x80006714)); /* 3c091000 lui t1,zero,0x1000 */
 set(m,9u,sx(UINT32_C(0x10000000)));target=sx(UINT32_C(0x80006718));goto dispatch;
L_80006718:
 STEP(UINT32_C(0x80006718)); /* ffbf0070 sd ra,0x70(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x8000671c));goto dispatch;
L_8000671c:
 STEP(UINT32_C(0x8000671c)); /* 3529f590 ori t1,t1,0xf590 */
 set(m,9u,lo(m,9u) | UINT64_C(0xf590));target=sx(UINT32_C(0x80006720));goto dispatch;
L_80006720:
 STEP(UINT32_C(0x80006720)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x80006724));goto dispatch;
L_80006724:
 STEP(UINT32_C(0x80006724)); /* 3c06b000 lui a2,zero,0xb000 */
 set(m,6u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006728));goto dispatch;
L_80006728:
 STEP(UINT32_C(0x80006728)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x8000672c));goto dispatch;
L_8000672c:
 STEP(UINT32_C(0x8000672c)); /* 34c6c400 ori a2,a2,0xc400 */
 set(m,6u,lo(m,6u) | UINT64_C(0xc400));target=sx(UINT32_C(0x80006730));goto dispatch;
L_80006730:
 STEP(UINT32_C(0x80006730)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80006734));goto dispatch;
L_80006734:
 STEP(UINT32_C(0x80006734)); /* 3c07fffe lui a3,zero,0xfffe */
 set(m,7u,sx(UINT32_C(0xfffe0000)));target=sx(UINT32_C(0x80006738));goto dispatch;
L_80006738:
 STEP(UINT32_C(0x80006738)); /* 34e7ffff ori a3,a3,0xffff */
 set(m,7u,lo(m,7u) | UINT64_C(0xffff));target=sx(UINT32_C(0x8000673c));goto dispatch;
L_8000673c:
 STEP(UINT32_C(0x8000673c)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80006740));goto dispatch;
L_80006740:
 STEP(UINT32_C(0x80006740)); /* 8d020000 lw v0,0x0(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006744));goto dispatch;
L_80006744:
 STEP(UINT32_C(0x80006744)); /* 00a0a02d daddu s4,a1,zero */
 set(m,20u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006748));goto dispatch;
L_80006748:
 STEP(UINT32_C(0x80006748)); /* 0000902d daddu s2,zero,zero */
 set(m,18u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x8000674c));goto dispatch;
L_8000674c:
 STEP(UINT32_C(0x8000674c)); /* 00431025 or v0,v0,v1 */
 set(m,2u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x80006750));goto dispatch;
L_80006750:
 STEP(UINT32_C(0x80006750)); /* ad220000 sw v0,0x0(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006754));goto dispatch;
L_80006754:
 STEP(UINT32_C(0x80006754)); /* acc00000 sw zero,0x0(a2) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006758));goto dispatch;
L_80006758:
 STEP(UINT32_C(0x80006758)); /* 8cc30000 lw v1,0x0(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x8000675c));goto dispatch;
L_8000675c:
 STEP(UINT32_C(0x8000675c)); /* afa30000 sw v1,0x0(sp) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006760));goto dispatch;
L_80006760:
 STEP(UINT32_C(0x80006760)); /* 8d020000 lw v0,0x0(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006764));goto dispatch;
L_80006764:
 STEP(UINT32_C(0x80006764)); /* 00471024 and v0,v0,a3 */
 set(m,2u,lo(m,2u)&lo(m,7u));target=sx(UINT32_C(0x80006768));goto dispatch;
L_80006768:
 STEP(UINT32_C(0x80006768)); /* 0c001972 jal 800065c8 */
 set(m,31u,UINT64_C(0x80006770));STEP(UINT32_C(0x8000676c));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800065c8));goto dispatch;
L_8000676c:
 STEP(UINT32_C(0x8000676c)); /* ad220000 sw v0,0x0(t1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,9u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006770));goto dispatch;
L_80006770:
 STEP(UINT32_C(0x80006770)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80006774));goto dispatch;
L_80006774:
 STEP(UINT32_C(0x80006774)); /* 1a80000e blez s4,zero,800067b0 */
 {int taken=((int64_t)lo(m,20u)<=0);STEP(UINT32_C(0x80006778));set(m,3u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x800067b0):UINT32_C(0x8000677c));goto dispatch;}
L_80006778:
 STEP(UINT32_C(0x80006778)); /* 0220182d daddu v1,s1,zero */
 set(m,3u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x8000677c));goto dispatch;
L_8000677c:
 STEP(UINT32_C(0x8000677c)); /* 0280802d daddu s0,s4,zero */
 set(m,16u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x80006780));goto dispatch;
L_80006780:
 STEP(UINT32_C(0x80006780)); /* 8c62000c lw v0,0xc(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006784));goto dispatch;
L_80006784:
 STEP(UINT32_C(0x80006784)); /* 30420020 andi v0,v0,0x20 */
 set(m,2u,lo(m,2u) & UINT64_C(0x20));target=sx(UINT32_C(0x80006788));goto dispatch;
L_80006788:
 STEP(UINT32_C(0x80006788)); /* 54400006 bnel v0,zero,800067a4 */
 if(lo(m,2u)!=lo(m,0u)){STEP(UINT32_C(0x8000678c));set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800067a4));}else target=sx(UINT32_C(0x80006790));goto dispatch;
L_8000678c:
 STEP(UINT32_C(0x8000678c)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80006790));goto dispatch;
L_80006790:
 STEP(UINT32_C(0x80006790)); /* 8c620008 lw v0,0x8(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80006794));goto dispatch;
L_80006794:
 STEP(UINT32_C(0x80006794)); /* 2c420071 sltiu v0,v0,113 */
 set(m,2u,(lo(m,2u)<UINT64_C(0x71)));target=sx(UINT32_C(0x80006798));goto dispatch;
L_80006798:
 STEP(UINT32_C(0x80006798)); /* 50400002 beql v0,zero,800067a4 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x8000679c));set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x800067a4));}else target=sx(UINT32_C(0x800067a0));goto dispatch;
L_8000679c:
 STEP(UINT32_C(0x8000679c)); /* 26520002 addiu s2,s2,2 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x800067a0));goto dispatch;
L_800067a0:
 STEP(UINT32_C(0x800067a0)); /* 26520001 addiu s2,s2,1 */
 set(m,18u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800067a4));goto dispatch;
L_800067a4:
 STEP(UINT32_C(0x800067a4)); /* 2610ffff addiu s0,s0,-1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x800067a8));goto dispatch;
L_800067a8:
 STEP(UINT32_C(0x800067a8)); /* 1600fff5 bne s0,zero,80006780 */
 {int taken=(lo(m,16u)!=lo(m,0u));STEP(UINT32_C(0x800067ac));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x80006780):UINT32_C(0x800067b0));goto dispatch;}
L_800067ac:
 STEP(UINT32_C(0x800067ac)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x800067b0));goto dispatch;
L_800067b0:
 STEP(UINT32_C(0x800067b0)); /* 00b2102a slt v0,a1,s2 */
 set(m,2u,((int64_t)lo(m,5u)<(int64_t)lo(m,18u)));target=sx(UINT32_C(0x800067b4));goto dispatch;
L_800067b4:
 STEP(UINT32_C(0x800067b4)); /* 1440002d bne v0,zero,8000686c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x800067b8));set(m,2u,lo(m,0u)+lo(m,0u));target=sx(taken?UINT32_C(0x8000686c):UINT32_C(0x800067bc));goto dispatch;}
L_800067b8:
 STEP(UINT32_C(0x800067b8)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x800067bc));goto dispatch;
L_800067bc:
 STEP(UINT32_C(0x800067bc)); /* 3c038002 lui v1,zero,0x8002 */
 set(m,3u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800067c0));goto dispatch;
L_800067c0:
 STEP(UINT32_C(0x800067c0)); /* 9063e104 lbu v1,-0x1efc(v1) */
 {uint8_t byte;READ((uint32_t)lo(m,3u)+UINT32_C(0xffffe104),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x800067c4));goto dispatch;
L_800067c4:
 STEP(UINT32_C(0x800067c4)); /* 2402001f addiu v0,zero,31 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000001f)));target=sx(UINT32_C(0x800067c8));goto dispatch;
L_800067c8:
 STEP(UINT32_C(0x800067c8)); /* 50400001 beql v0,zero,800067d0 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x800067cc));return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc)); /* BREAK7 is annulled by native nonzero LI31/BEQL. No invented exception handler. */}else target=sx(UINT32_C(0x800067d0));goto dispatch;
L_800067cc:
 STEP(UINT32_C(0x800067cc)); /* 000001cd UNKNOWN 000001cd */
 return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc)); /* BREAK7 is annulled by native nonzero LI31/BEQL. No invented exception handler. */
L_800067d0:
 STEP(UINT32_C(0x800067d0)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800067d4));goto dispatch;
L_800067d4:
 STEP(UINT32_C(0x800067d4)); /* 0062001a UNKNOWN 0062001a */
 if(lo(m,3u)>256u||lo(m,2u)!=31u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->lo=sx((uint32_t)lo(m,3u)/31u);m->hi=sx((uint32_t)lo(m,3u)%31u); /* Native DIV with actual bounded ring index and LI31 divisor. */target=sx(UINT32_C(0x800067d8));goto dispatch;
L_800067d8:
 STEP(UINT32_C(0x800067d8)); /* 00002010 mfhi a0 */
 set(m,4u,m->hi);target=sx(UINT32_C(0x800067dc));goto dispatch;
L_800067dc:
 STEP(UINT32_C(0x800067dc)); /* 309300ff andi s3,a0,0xff */
 set(m,19u,lo(m,4u) & UINT64_C(0xff));target=sx(UINT32_C(0x800067e0));goto dispatch;
L_800067e0:
 STEP(UINT32_C(0x800067e0)); /* 16600006 bne s3,zero,800067fc */
 {int taken=(lo(m,19u)!=lo(m,0u));STEP(UINT32_C(0x800067e4));/* nop */target=sx(taken?UINT32_C(0x800067fc):UINT32_C(0x800067e8));goto dispatch;}
L_800067e4:
 STEP(UINT32_C(0x800067e4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800067e8));goto dispatch;
L_800067e8:
 STEP(UINT32_C(0x800067e8)); /* 3c028002 lui v0,zero,0x8002 */
 set(m,2u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x800067ec));goto dispatch;
L_800067ec:
 STEP(UINT32_C(0x800067ec)); /* 9442e106 lhu v0,-0x1efa(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffe106),&value16,2u);set(m,2u,value16);target=sx(UINT32_C(0x800067f0));goto dispatch;
L_800067f0:
 STEP(UINT32_C(0x800067f0)); /* 24420001 addiu v0,v0,1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800067f4));goto dispatch;
L_800067f4:
 STEP(UINT32_C(0x800067f4)); /* 10000003 beq zero,zero,80006804 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800067f8));set(m,16u,lo(m,2u) & UINT64_C(0xffff));target=sx(taken?UINT32_C(0x80006804):UINT32_C(0x800067fc));goto dispatch;}
L_800067f8:
 STEP(UINT32_C(0x800067f8)); /* 3050ffff andi s0,v0,0xffff */
 set(m,16u,lo(m,2u) & UINT64_C(0xffff));target=sx(UINT32_C(0x800067fc));goto dispatch;
L_800067fc:
 STEP(UINT32_C(0x800067fc)); /* 3c108002 lui s0,zero,0x8002 */
 set(m,16u,sx(UINT32_C(0x80020000)));target=sx(UINT32_C(0x80006800));goto dispatch;
L_80006800:
 STEP(UINT32_C(0x80006800)); /* 9610e106 lhu s0,-0x1efa(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffe106),&value16,2u);set(m,16u,value16);target=sx(UINT32_C(0x80006804));goto dispatch;
L_80006804:
 STEP(UINT32_C(0x80006804)); /* 00a0202d daddu a0,a1,zero */
 set(m,4u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x80006808));goto dispatch;
L_80006808:
 STEP(UINT32_C(0x80006808)); /* 0c001994 jal 80006650 */
 set(m,31u,UINT64_C(0x80006810));STEP(UINT32_C(0x8000680c));set(m,21u,sx((uint32_t)lo(m,16u)<<16u));target=sx(UINT32_C(0x80006650));goto dispatch;
L_8000680c:
 STEP(UINT32_C(0x8000680c)); /* 0010ac00 sll s5,s0,16 */
 set(m,21u,sx((uint32_t)lo(m,16u)<<16u));target=sx(UINT32_C(0x80006810));goto dispatch;
L_80006810:
 STEP(UINT32_C(0x80006810)); /* 00139a00 sll s3,s3,8 */
 set(m,19u,sx((uint32_t)lo(m,19u)<<8u));target=sx(UINT32_C(0x80006814));goto dispatch;
L_80006814:
 STEP(UINT32_C(0x80006814)); /* 2682ffff addiu v0,s4,-1 */
 set(m,2u,sx((uint32_t)lo(m,20u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80006818));goto dispatch;
L_80006818:
 STEP(UINT32_C(0x80006818)); /* 1840000c blez v0,zero,8000684c */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x8000681c));set(m,18u,lo(m,18u) & UINT64_C(0xff));target=sx(taken?UINT32_C(0x8000684c):UINT32_C(0x80006820));goto dispatch;}
L_8000681c:
 STEP(UINT32_C(0x8000681c)); /* 325200ff andi s2,s2,0xff */
 set(m,18u,lo(m,18u) & UINT64_C(0xff));target=sx(UINT32_C(0x80006820));goto dispatch;
L_80006820:
 STEP(UINT32_C(0x80006820)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80006824));goto dispatch;
L_80006824:
 STEP(UINT32_C(0x80006824)); /* 8e240000 lw a0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80006828));goto dispatch;
L_80006828:
 STEP(UINT32_C(0x80006828)); /* 24083000 addiu t0,zero,12288 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00003000)));target=sx(UINT32_C(0x8000682c));goto dispatch;
L_8000682c:
 STEP(UINT32_C(0x8000682c)); /* 8e250004 lw a1,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80006830));goto dispatch;
L_80006830:
 STEP(UINT32_C(0x80006830)); /* 2610ffff addiu s0,s0,-1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80006834));goto dispatch;
L_80006834:
 STEP(UINT32_C(0x80006834)); /* 8e260008 lw a2,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x80006838));goto dispatch;
L_80006838:
 STEP(UINT32_C(0x80006838)); /* 8e27000c lw a3,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x8000683c));goto dispatch;
L_8000683c:
 STEP(UINT32_C(0x8000683c)); /* 0c0018dc jal 80006370 */
 set(m,31u,UINT64_C(0x80006844));STEP(UINT32_C(0x80006840));set(m,17u,sx((uint32_t)lo(m,17u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006370));goto dispatch;
L_80006840:
 STEP(UINT32_C(0x80006840)); /* 26310010 addiu s1,s1,16 */
 set(m,17u,sx((uint32_t)lo(m,17u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x80006844));goto dispatch;
L_80006844:
 STEP(UINT32_C(0x80006844)); /* 5600fff8 bnel s0,zero,80006828 */
 if(lo(m,16u)!=lo(m,0u)){STEP(UINT32_C(0x80006848));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80006828));}else target=sx(UINT32_C(0x8000684c));goto dispatch;
L_80006848:
 STEP(UINT32_C(0x80006848)); /* 8e240000 lw a0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x8000684c));goto dispatch;
L_8000684c:
 STEP(UINT32_C(0x8000684c)); /* 8e27000c lw a3,0xc(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x0000000c),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x80006850));goto dispatch;
L_80006850:
 STEP(UINT32_C(0x80006850)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80006854));goto dispatch;
L_80006854:
 STEP(UINT32_C(0x80006854)); /* 8e240000 lw a0,0x0(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80006858));goto dispatch;
L_80006858:
 STEP(UINT32_C(0x80006858)); /* 8e250004 lw a1,0x4(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x8000685c));goto dispatch;
L_8000685c:
 STEP(UINT32_C(0x8000685c)); /* 0c0018dc jal 80006370 */
 set(m,31u,UINT64_C(0x80006864));STEP(UINT32_C(0x80006860));READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x80006370));goto dispatch;
L_80006860:
 STEP(UINT32_C(0x80006860)); /* 8e260008 lw a2,0x8(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x80006864));goto dispatch;
L_80006864:
 STEP(UINT32_C(0x80006864)); /* 02b31025 or v0,s5,s3 */
 set(m,2u,lo(m,21u)|lo(m,19u));target=sx(UINT32_C(0x80006868));goto dispatch;
L_80006868:
 STEP(UINT32_C(0x80006868)); /* 00521025 or v0,v0,s2 */
 set(m,2u,lo(m,2u)|lo(m,18u));target=sx(UINT32_C(0x8000686c));goto dispatch;
L_8000686c:
 STEP(UINT32_C(0x8000686c)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=sx(UINT32_C(0x80006870));goto dispatch;
L_80006870:
 STEP(UINT32_C(0x80006870)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80006874));goto dispatch;
L_80006874:
 STEP(UINT32_C(0x80006874)); /* 3463c400 ori v1,v1,0xc400 */
 set(m,3u,lo(m,3u) | UINT64_C(0xc400));target=sx(UINT32_C(0x80006878));goto dispatch;
L_80006878:
 STEP(UINT32_C(0x80006878)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x8000687c));goto dispatch;
L_8000687c:
 STEP(UINT32_C(0x8000687c)); /* 8c640000 lw a0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80006880));goto dispatch;
L_80006880:
 STEP(UINT32_C(0x80006880)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x80006884));goto dispatch;
L_80006884:
 STEP(UINT32_C(0x80006884)); /* 34840184 ori a0,a0,0x184 */
 set(m,4u,lo(m,4u) | UINT64_C(0x184));target=sx(UINT32_C(0x80006888));goto dispatch;
L_80006888:
 STEP(UINT32_C(0x80006888)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x8000688c));goto dispatch;
L_8000688c:
 STEP(UINT32_C(0x8000688c)); /* ac640000 sw a0,0x0(v1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80006890));goto dispatch;
L_80006890:
 STEP(UINT32_C(0x80006890)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x80006894));goto dispatch;
L_80006894:
 STEP(UINT32_C(0x80006894)); /* 8c650000 lw a1,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80006898));goto dispatch;
L_80006898:
 STEP(UINT32_C(0x80006898)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x8000689c));goto dispatch;
L_8000689c:
 STEP(UINT32_C(0x8000689c)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x800068a0));goto dispatch;
L_800068a0:
 STEP(UINT32_C(0x800068a0)); /* afa50000 sw a1,0x0(sp) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800068a4));goto dispatch;
L_800068a4:
 STEP(UINT32_C(0x800068a4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800068a8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_800068a8:
 STEP(UINT32_C(0x800068a8)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x800068ac));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

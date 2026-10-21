#include "battle_syscall_kernel_resume.h"
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
static int normal_or_zero(uint32_t v){uint32_t e=v&0x7f800000u;return e!=0x7f800000u&&(e!=0u||(v&0x7fffffffu)==0u);}
uint32_t nocturneBattleSyscallKernelResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x80000180):goto L_80000180;
 case UINT32_C(0x80000184):goto L_80000184;
 case UINT32_C(0x80000188):goto L_80000188;
 case UINT32_C(0x8000018c):goto L_8000018c;
 case UINT32_C(0x80000190):goto L_80000190;
 case UINT32_C(0x80000194):goto L_80000194;
 case UINT32_C(0x80000198):goto L_80000198;
 case UINT32_C(0x8000019c):goto L_8000019c;
 case UINT32_C(0x800001a0):goto L_800001a0;
 case UINT32_C(0x800001a4):goto L_800001a4;
 case UINT32_C(0x80000280):goto L_80000280;
 case UINT32_C(0x80000284):goto L_80000284;
 case UINT32_C(0x80000288):goto L_80000288;
 case UINT32_C(0x8000028c):goto L_8000028c;
 case UINT32_C(0x80000290):goto L_80000290;
 case UINT32_C(0x80000294):goto L_80000294;
 case UINT32_C(0x80000298):goto L_80000298;
 case UINT32_C(0x8000029c):goto L_8000029c;
 case UINT32_C(0x800002a0):goto L_800002a0;
 case UINT32_C(0x800002a4):goto L_800002a4;
 case UINT32_C(0x800002a8):goto L_800002a8;
 case UINT32_C(0x800002ac):goto L_800002ac;
 case UINT32_C(0x800002b0):goto L_800002b0;
 case UINT32_C(0x800002b4):goto L_800002b4;
 case UINT32_C(0x800002b8):goto L_800002b8;
 case UINT32_C(0x800002bc):goto L_800002bc;
 case UINT32_C(0x800002c0):goto L_800002c0;
 case UINT32_C(0x800002c4):goto L_800002c4;
 case UINT32_C(0x800002c8):goto L_800002c8;
 case UINT32_C(0x800002cc):goto L_800002cc;
 case UINT32_C(0x800002d0):goto L_800002d0;
 case UINT32_C(0x800002d4):goto L_800002d4;
 case UINT32_C(0x800002d8):goto L_800002d8;
 case UINT32_C(0x800002dc):goto L_800002dc;
 case UINT32_C(0x800002e0):goto L_800002e0;
 case UINT32_C(0x800002e4):goto L_800002e4;
 case UINT32_C(0x800002e8):goto L_800002e8;
 case UINT32_C(0x800002ec):goto L_800002ec;
 case UINT32_C(0x800002f0):goto L_800002f0;
 case UINT32_C(0x800002f4):goto L_800002f4;
 case UINT32_C(0x800002f8):goto L_800002f8;
 case UINT32_C(0x800002fc):goto L_800002fc;
 case UINT32_C(0x80000300):goto L_80000300;
 case UINT32_C(0x80000304):goto L_80000304;
 case UINT32_C(0x80000308):goto L_80000308;
 case UINT32_C(0x8000030c):goto L_8000030c;
 case UINT32_C(0x80000310):goto L_80000310;
 case UINT32_C(0x80000314):goto L_80000314;
 case UINT32_C(0x80000318):goto L_80000318;
 case UINT32_C(0x8000031c):goto L_8000031c;
 case UINT32_C(0x80000320):goto L_80000320;
 case UINT32_C(0x80000324):goto L_80000324;
 case UINT32_C(0x80000328):goto L_80000328;
 case UINT32_C(0x8000032c):goto L_8000032c;
 case UINT32_C(0x80000330):goto L_80000330;
 case UINT32_C(0x80000334):goto L_80000334;
 case UINT32_C(0x80000338):goto L_80000338;
 case UINT32_C(0x8000033c):goto L_8000033c;
 case UINT32_C(0x80000340):goto L_80000340;
 case UINT32_C(0x80000344):goto L_80000344;
 case UINT32_C(0x80000348):goto L_80000348;
 case UINT32_C(0x8000034c):goto L_8000034c;
 case UINT32_C(0x80000350):goto L_80000350;
 case UINT32_C(0x80000354):goto L_80000354;
 case UINT32_C(0x80000358):goto L_80000358;
 case UINT32_C(0x8000035c):goto L_8000035c;
 case UINT32_C(0x80000360):goto L_80000360;
 case UINT32_C(0x80000364):goto L_80000364;
 case UINT32_C(0x80000368):goto L_80000368;
 case UINT32_C(0x8000036c):goto L_8000036c;
 case UINT32_C(0x80000370):goto L_80000370;
 case UINT32_C(0x80000374):goto L_80000374;
 case UINT32_C(0x80003340):goto L_80003340;
 case UINT32_C(0x80003344):goto L_80003344;
 case UINT32_C(0x80003348):goto L_80003348;
 case UINT32_C(0x8000334c):goto L_8000334c;
 case UINT32_C(0x80003350):goto L_80003350;
 case UINT32_C(0x80003354):goto L_80003354;
 case UINT32_C(0x80003358):goto L_80003358;
 case UINT32_C(0x8000335c):goto L_8000335c;
 case UINT32_C(0x80003360):goto L_80003360;
 case UINT32_C(0x80003364):goto L_80003364;
 case UINT32_C(0x80003368):goto L_80003368;
 case UINT32_C(0x8000336c):goto L_8000336c;
 case UINT32_C(0x80003370):goto L_80003370;
 case UINT32_C(0x80003374):goto L_80003374;
 case UINT32_C(0x80003378):goto L_80003378;
 case UINT32_C(0x8000337c):goto L_8000337c;
 case UINT32_C(0x80003380):goto L_80003380;
 case UINT32_C(0x80003384):goto L_80003384;
 case UINT32_C(0x80003388):goto L_80003388;
 case UINT32_C(0x8000338c):goto L_8000338c;
 case UINT32_C(0x80003390):goto L_80003390;
 case UINT32_C(0x80003394):goto L_80003394;
 case UINT32_C(0x80003398):goto L_80003398;
 case UINT32_C(0x8000339c):goto L_8000339c;
 case UINT32_C(0x800033a0):goto L_800033a0;
 case UINT32_C(0x800033a4):goto L_800033a4;
 case UINT32_C(0x800033a8):goto L_800033a8;
 case UINT32_C(0x800033ac):goto L_800033ac;
 case UINT32_C(0x80003680):goto L_80003680;
 case UINT32_C(0x80003684):goto L_80003684;
 case UINT32_C(0x80003688):goto L_80003688;
 case UINT32_C(0x8000368c):goto L_8000368c;
 case UINT32_C(0x80003690):goto L_80003690;
 case UINT32_C(0x80003694):goto L_80003694;
 case UINT32_C(0x80003698):goto L_80003698;
 case UINT32_C(0x8000369c):goto L_8000369c;
 case UINT32_C(0x800036a0):goto L_800036a0;
 case UINT32_C(0x800036a4):goto L_800036a4;
 case UINT32_C(0x800036a8):goto L_800036a8;
 case UINT32_C(0x800036ac):goto L_800036ac;
 case UINT32_C(0x800036b0):goto L_800036b0;
 case UINT32_C(0x800036b4):goto L_800036b4;
 case UINT32_C(0x800036b8):goto L_800036b8;
 case UINT32_C(0x800036bc):goto L_800036bc;
 case UINT32_C(0x800036c0):goto L_800036c0;
 case UINT32_C(0x800036c4):goto L_800036c4;
 case UINT32_C(0x800036c8):goto L_800036c8;
 case UINT32_C(0x800036cc):goto L_800036cc;
 case UINT32_C(0x800036d0):goto L_800036d0;
 case UINT32_C(0x800036d4):goto L_800036d4;
 case UINT32_C(0x800036d8):goto L_800036d8;
 case UINT32_C(0x800036dc):goto L_800036dc;
 case UINT32_C(0x800036e0):goto L_800036e0;
 case UINT32_C(0x800036e4):goto L_800036e4;
 case UINT32_C(0x800036e8):goto L_800036e8;
 case UINT32_C(0x800036ec):goto L_800036ec;
 case UINT32_C(0x800036f0):goto L_800036f0;
 case UINT32_C(0x800036f4):goto L_800036f4;
 case UINT32_C(0x800036f8):goto L_800036f8;
 case UINT32_C(0x800036fc):goto L_800036fc;
 case UINT32_C(0x80003700):goto L_80003700;
 case UINT32_C(0x80003704):goto L_80003704;
 case UINT32_C(0x80003708):goto L_80003708;
 case UINT32_C(0x8000370c):goto L_8000370c;
 case UINT32_C(0x80003710):goto L_80003710;
 case UINT32_C(0x80003714):goto L_80003714;
 case UINT32_C(0x80003718):goto L_80003718;
 case UINT32_C(0x8000371c):goto L_8000371c;
 case UINT32_C(0x80003720):goto L_80003720;
 case UINT32_C(0x80003724):goto L_80003724;
 case UINT32_C(0x80003728):goto L_80003728;
 case UINT32_C(0x8000372c):goto L_8000372c;
 case UINT32_C(0x80003730):goto L_80003730;
 case UINT32_C(0x80003734):goto L_80003734;
 case UINT32_C(0x80003738):goto L_80003738;
 case UINT32_C(0x8000373c):goto L_8000373c;
 case UINT32_C(0x80003740):goto L_80003740;
 case UINT32_C(0x80003744):goto L_80003744;
 case UINT32_C(0x80003748):goto L_80003748;
 case UINT32_C(0x8000374c):goto L_8000374c;
 case UINT32_C(0x80003750):goto L_80003750;
 case UINT32_C(0x80003754):goto L_80003754;
 case UINT32_C(0x80003758):goto L_80003758;
 case UINT32_C(0x8000375c):goto L_8000375c;
 case UINT32_C(0x80003760):goto L_80003760;
 case UINT32_C(0x80003764):goto L_80003764;
 case UINT32_C(0x80003768):goto L_80003768;
 case UINT32_C(0x8000376c):goto L_8000376c;
 case UINT32_C(0x80003770):goto L_80003770;
 case UINT32_C(0x80003774):goto L_80003774;
 case UINT32_C(0x80003778):goto L_80003778;
 case UINT32_C(0x8000377c):goto L_8000377c;
 case UINT32_C(0x80003780):goto L_80003780;
 case UINT32_C(0x80003784):goto L_80003784;
 case UINT32_C(0x80003788):goto L_80003788;
 case UINT32_C(0x8000378c):goto L_8000378c;
 case UINT32_C(0x80003790):goto L_80003790;
 case UINT32_C(0x80003794):goto L_80003794;
 case UINT32_C(0x80003798):goto L_80003798;
 case UINT32_C(0x8000379c):goto L_8000379c;
 case UINT32_C(0x800037a0):goto L_800037a0;
 case UINT32_C(0x800037a4):goto L_800037a4;
 case UINT32_C(0x800037a8):goto L_800037a8;
 case UINT32_C(0x800037ac):goto L_800037ac;
 case UINT32_C(0x800037b0):goto L_800037b0;
 case UINT32_C(0x800037b4):goto L_800037b4;
 case UINT32_C(0x800037b8):goto L_800037b8;
 case UINT32_C(0x800037bc):goto L_800037bc;
 case UINT32_C(0x800037c0):goto L_800037c0;
 case UINT32_C(0x800037c4):goto L_800037c4;
 case UINT32_C(0x800037c8):goto L_800037c8;
 case UINT32_C(0x800037cc):goto L_800037cc;
 case UINT32_C(0x800037d0):goto L_800037d0;
 case UINT32_C(0x800037d4):goto L_800037d4;
 case UINT32_C(0x800037d8):goto L_800037d8;
 case UINT32_C(0x800037dc):goto L_800037dc;
 case UINT32_C(0x800037e0):goto L_800037e0;
 case UINT32_C(0x800037e4):goto L_800037e4;
 case UINT32_C(0x80003800):goto L_80003800;
 case UINT32_C(0x80003804):goto L_80003804;
 case UINT32_C(0x80003808):goto L_80003808;
 case UINT32_C(0x8000380c):goto L_8000380c;
 case UINT32_C(0x80003810):goto L_80003810;
 case UINT32_C(0x80003814):goto L_80003814;
 case UINT32_C(0x80003818):goto L_80003818;
 case UINT32_C(0x8000381c):goto L_8000381c;
 case UINT32_C(0x80003820):goto L_80003820;
 case UINT32_C(0x80003824):goto L_80003824;
 case UINT32_C(0x80003828):goto L_80003828;
 case UINT32_C(0x8000382c):goto L_8000382c;
 case UINT32_C(0x80003830):goto L_80003830;
 case UINT32_C(0x80003834):goto L_80003834;
 case UINT32_C(0x80003838):goto L_80003838;
 case UINT32_C(0x8000383c):goto L_8000383c;
 case UINT32_C(0x80003840):goto L_80003840;
 case UINT32_C(0x80003844):goto L_80003844;
 case UINT32_C(0x80003848):goto L_80003848;
 case UINT32_C(0x8000384c):goto L_8000384c;
 case UINT32_C(0x80003850):goto L_80003850;
 case UINT32_C(0x80003854):goto L_80003854;
 case UINT32_C(0x80003858):goto L_80003858;
 case UINT32_C(0x8000385c):goto L_8000385c;
 case UINT32_C(0x80003860):goto L_80003860;
 case UINT32_C(0x80003864):goto L_80003864;
 case UINT32_C(0x80003868):goto L_80003868;
 case UINT32_C(0x8000386c):goto L_8000386c;
 case UINT32_C(0x80003870):goto L_80003870;
 case UINT32_C(0x80003874):goto L_80003874;
 case UINT32_C(0x80003878):goto L_80003878;
 case UINT32_C(0x8000387c):goto L_8000387c;
 case UINT32_C(0x80003880):goto L_80003880;
 case UINT32_C(0x80003884):goto L_80003884;
 case UINT32_C(0x80003888):goto L_80003888;
 case UINT32_C(0x8000388c):goto L_8000388c;
 case UINT32_C(0x80003890):goto L_80003890;
 case UINT32_C(0x80003894):goto L_80003894;
 case UINT32_C(0x80003898):goto L_80003898;
 case UINT32_C(0x8000389c):goto L_8000389c;
 case UINT32_C(0x800038a0):goto L_800038a0;
 case UINT32_C(0x800038a4):goto L_800038a4;
 case UINT32_C(0x800038a8):goto L_800038a8;
 case UINT32_C(0x800038ac):goto L_800038ac;
 case UINT32_C(0x800038b0):goto L_800038b0;
 case UINT32_C(0x800038b4):goto L_800038b4;
 case UINT32_C(0x800038b8):goto L_800038b8;
 case UINT32_C(0x800038bc):goto L_800038bc;
 case UINT32_C(0x800038c0):goto L_800038c0;
 case UINT32_C(0x800038c4):goto L_800038c4;
 case UINT32_C(0x800038c8):goto L_800038c8;
 case UINT32_C(0x800038cc):goto L_800038cc;
 case UINT32_C(0x800038d0):goto L_800038d0;
 case UINT32_C(0x800038d4):goto L_800038d4;
 case UINT32_C(0x800038d8):goto L_800038d8;
 case UINT32_C(0x800038dc):goto L_800038dc;
 case UINT32_C(0x800038e0):goto L_800038e0;
 case UINT32_C(0x800038e4):goto L_800038e4;
 case UINT32_C(0x800038e8):goto L_800038e8;
 case UINT32_C(0x800038ec):goto L_800038ec;
 case UINT32_C(0x800038f0):goto L_800038f0;
 case UINT32_C(0x800038f4):goto L_800038f4;
 case UINT32_C(0x800038f8):goto L_800038f8;
 case UINT32_C(0x800038fc):goto L_800038fc;
 case UINT32_C(0x80003900):goto L_80003900;
 case UINT32_C(0x80003904):goto L_80003904;
 case UINT32_C(0x80003908):goto L_80003908;
 case UINT32_C(0x8000390c):goto L_8000390c;
 case UINT32_C(0x80003910):goto L_80003910;
 case UINT32_C(0x80003914):goto L_80003914;
 case UINT32_C(0x80003918):goto L_80003918;
 case UINT32_C(0x8000391c):goto L_8000391c;
 case UINT32_C(0x80003920):goto L_80003920;
 case UINT32_C(0x80003924):goto L_80003924;
 case UINT32_C(0x80003928):goto L_80003928;
 case UINT32_C(0x8000392c):goto L_8000392c;
 case UINT32_C(0x80003930):goto L_80003930;
 case UINT32_C(0x80003934):goto L_80003934;
 case UINT32_C(0x80003938):goto L_80003938;
 case UINT32_C(0x800046b0):goto L_800046b0;
 case UINT32_C(0x800046b4):goto L_800046b4;
 case UINT32_C(0x800046b8):goto L_800046b8;
 case UINT32_C(0x800046bc):goto L_800046bc;
 case UINT32_C(0x800046c0):goto L_800046c0;
 case UINT32_C(0x800046c4):goto L_800046c4;
 case UINT32_C(0x800046c8):goto L_800046c8;
 case UINT32_C(0x800046cc):goto L_800046cc;
 case UINT32_C(0x800046d0):goto L_800046d0;
 case UINT32_C(0x800046d4):goto L_800046d4;
 case UINT32_C(0x800046d8):goto L_800046d8;
 case UINT32_C(0x800046dc):goto L_800046dc;
 case UINT32_C(0x800046e0):goto L_800046e0;
 case UINT32_C(0x800046e4):goto L_800046e4;
 case UINT32_C(0x800046e8):goto L_800046e8;
 case UINT32_C(0x800046ec):goto L_800046ec;
 case UINT32_C(0x800046f0):goto L_800046f0;
 case UINT32_C(0x800046f4):goto L_800046f4;
 case UINT32_C(0x800046f8):goto L_800046f8;
 case UINT32_C(0x800046fc):goto L_800046fc;
 case UINT32_C(0x80004700):goto L_80004700;
 case UINT32_C(0x80004704):goto L_80004704;
 case UINT32_C(0x80004708):goto L_80004708;
 case UINT32_C(0x8000470c):goto L_8000470c;
 case UINT32_C(0x80004710):goto L_80004710;
 case UINT32_C(0x80004714):goto L_80004714;
 case UINT32_C(0x80004718):goto L_80004718;
 case UINT32_C(0x8000471c):goto L_8000471c;
 case UINT32_C(0x80004720):goto L_80004720;
 case UINT32_C(0x80004724):goto L_80004724;
 case UINT32_C(0x80004728):goto L_80004728;
 case UINT32_C(0x8000472c):goto L_8000472c;
 case UINT32_C(0x80004730):goto L_80004730;
 case UINT32_C(0x80004734):goto L_80004734;
 case UINT32_C(0x80004738):goto L_80004738;
 case UINT32_C(0x8000473c):goto L_8000473c;
 case UINT32_C(0x80004740):goto L_80004740;
 case UINT32_C(0x80004744):goto L_80004744;
 case UINT32_C(0x80004748):goto L_80004748;
 case UINT32_C(0x8000474c):goto L_8000474c;
 case UINT32_C(0x80004750):goto L_80004750;
 case UINT32_C(0x80004754):goto L_80004754;
 case UINT32_C(0x80004758):goto L_80004758;
 case UINT32_C(0x8000475c):goto L_8000475c;
 case UINT32_C(0x80004760):goto L_80004760;
 case UINT32_C(0x80004764):goto L_80004764;
 case UINT32_C(0x80004768):goto L_80004768;
 case UINT32_C(0x8000476c):goto L_8000476c;
 case UINT32_C(0x80004770):goto L_80004770;
 case UINT32_C(0x80004774):goto L_80004774;
 case UINT32_C(0x80004778):goto L_80004778;
 case UINT32_C(0x8000477c):goto L_8000477c;
 case UINT32_C(0x80004780):goto L_80004780;
 case UINT32_C(0x80004784):goto L_80004784;
 case UINT32_C(0x80004788):goto L_80004788;
 case UINT32_C(0x8000478c):goto L_8000478c;
 case UINT32_C(0x80004790):goto L_80004790;
 case UINT32_C(0x80004794):goto L_80004794;
 case UINT32_C(0x80004798):goto L_80004798;
 case UINT32_C(0x8000479c):goto L_8000479c;
 case UINT32_C(0x800047a0):goto L_800047a0;
 case UINT32_C(0x800047a4):goto L_800047a4;
 case UINT32_C(0x800047a8):goto L_800047a8;
 case UINT32_C(0x800047ac):goto L_800047ac;
 case UINT32_C(0x800047b0):goto L_800047b0;
 case UINT32_C(0x800047b4):goto L_800047b4;
 case UINT32_C(0x800047b8):goto L_800047b8;
 case UINT32_C(0x800047bc):goto L_800047bc;
 case UINT32_C(0x800047c0):goto L_800047c0;
 case UINT32_C(0x800047c4):goto L_800047c4;
 case UINT32_C(0x800047c8):goto L_800047c8;
 case UINT32_C(0x800047cc):goto L_800047cc;
 case UINT32_C(0x800047d0):goto L_800047d0;
 case UINT32_C(0x800047d4):goto L_800047d4;
 case UINT32_C(0x800047d8):goto L_800047d8;
 case UINT32_C(0x800047dc):goto L_800047dc;
 case UINT32_C(0x800047e0):goto L_800047e0;
 case UINT32_C(0x800047e4):goto L_800047e4;
 case UINT32_C(0x800047e8):goto L_800047e8;
 case UINT32_C(0x800047ec):goto L_800047ec;
 case UINT32_C(0x800047f0):goto L_800047f0;
 case UINT32_C(0x800047f4):goto L_800047f4;
 case UINT32_C(0x800047f8):goto L_800047f8;
 case UINT32_C(0x800047fc):goto L_800047fc;
 case UINT32_C(0x80004800):goto L_80004800;
 case UINT32_C(0x800059b8):goto L_800059b8;
 case UINT32_C(0x800059bc):goto L_800059bc;
 case UINT32_C(0x800059c0):goto L_800059c0;
 case UINT32_C(0x800059c4):goto L_800059c4;
 case UINT32_C(0x800059c8):goto L_800059c8;
 case UINT32_C(0x800059cc):goto L_800059cc;
 case UINT32_C(0x800059d0):goto L_800059d0;
 case UINT32_C(0x800059d4):goto L_800059d4;
 case UINT32_C(0x800059d8):goto L_800059d8;
 case UINT32_C(0x800059dc):goto L_800059dc;
 case UINT32_C(0x800059e0):goto L_800059e0;
 case UINT32_C(0x800059e4):goto L_800059e4;
 case UINT32_C(0x800059e8):goto L_800059e8;
 case UINT32_C(0x800059ec):goto L_800059ec;
 case UINT32_C(0x800059f0):goto L_800059f0;
 case UINT32_C(0x800059f4):goto L_800059f4;
 case UINT32_C(0x800059f8):goto L_800059f8;
 case UINT32_C(0x800059fc):goto L_800059fc;
 case UINT32_C(0x80005a00):goto L_80005a00;
 case UINT32_C(0x80005a04):goto L_80005a04;
 case UINT32_C(0x80005a08):goto L_80005a08;
 case UINT32_C(0x80005a0c):goto L_80005a0c;
 case UINT32_C(0x80005b08):goto L_80005b08;
 case UINT32_C(0x80005b0c):goto L_80005b0c;
 case UINT32_C(0x80005b10):goto L_80005b10;
 case UINT32_C(0x80005b14):goto L_80005b14;
 case UINT32_C(0x80005b18):goto L_80005b18;
 case UINT32_C(0x80005b1c):goto L_80005b1c;
 case UINT32_C(0x80005b20):goto L_80005b20;
 case UINT32_C(0x80004548):goto L_80004548;
 case UINT32_C(0x8000454c):goto L_8000454c;
 case UINT32_C(0x80004550):goto L_80004550;
 case UINT32_C(0x80004554):goto L_80004554;
 case UINT32_C(0x80004970):goto L_80004970;
 case UINT32_C(0x80004974):goto L_80004974;
 case UINT32_C(0x80004978):goto L_80004978;
 case UINT32_C(0x8000497c):goto L_8000497c;
 case UINT32_C(0x80004980):goto L_80004980;
 case UINT32_C(0x80004984):goto L_80004984;
 case UINT32_C(0x80004988):goto L_80004988;
 case UINT32_C(0x8000498c):goto L_8000498c;
 case UINT32_C(0x80004990):goto L_80004990;
 case UINT32_C(0x80004994):goto L_80004994;
 case UINT32_C(0x80004998):goto L_80004998;
 case UINT32_C(0x8000499c):goto L_8000499c;
 case UINT32_C(0x800049a0):goto L_800049a0;
 case UINT32_C(0x800049a4):goto L_800049a4;
 case UINT32_C(0x800049a8):goto L_800049a8;
 case UINT32_C(0x800049ac):goto L_800049ac;
 case UINT32_C(0x800032c0):goto L_800032c0;
 case UINT32_C(0x800032c4):goto L_800032c4;
 case UINT32_C(0x800032c8):goto L_800032c8;
 case UINT32_C(0x800032cc):goto L_800032cc;
 case UINT32_C(0x800032d0):goto L_800032d0;
 case UINT32_C(0x800032d4):goto L_800032d4;
 case UINT32_C(0x800032d8):goto L_800032d8;
 case UINT32_C(0x800032dc):goto L_800032dc;
 case UINT32_C(0x800032e0):goto L_800032e0;
 case UINT32_C(0x800032e4):goto L_800032e4;
 case UINT32_C(0x800032e8):goto L_800032e8;
 case UINT32_C(0x800032ec):goto L_800032ec;
 case UINT32_C(0x800032f0):goto L_800032f0;
 case UINT32_C(0x800032f4):goto L_800032f4;
 case UINT32_C(0x800032f8):goto L_800032f8;
 case UINT32_C(0x800032fc):goto L_800032fc;
 case UINT32_C(0x80003300):goto L_80003300;
 case UINT32_C(0x80003304):goto L_80003304;
 case UINT32_C(0x80003308):goto L_80003308;
 case UINT32_C(0x8000330c):goto L_8000330c;
 case UINT32_C(0x80003310):goto L_80003310;
 case UINT32_C(0x80003314):goto L_80003314;
 case UINT32_C(0x80003318):goto L_80003318;
 case UINT32_C(0x8000331c):goto L_8000331c;
 case UINT32_C(0x80003320):goto L_80003320;
 case UINT32_C(0x80003324):goto L_80003324;
 case UINT32_C(0x80003328):goto L_80003328;
 case UINT32_C(0x8000332c):goto L_8000332c;
 case UINT32_C(0x80003330):goto L_80003330;
 case UINT32_C(0x80003334):goto L_80003334;
 case UINT32_C(0x80003338):goto L_80003338;
 case UINT32_C(0x80004658):goto L_80004658;
 case UINT32_C(0x8000465c):goto L_8000465c;
 case UINT32_C(0x80004660):goto L_80004660;
 case UINT32_C(0x80004664):goto L_80004664;
 case UINT32_C(0x80004668):goto L_80004668;
 case UINT32_C(0x8000466c):goto L_8000466c;
 case UINT32_C(0x80004670):goto L_80004670;
 case UINT32_C(0x80004674):goto L_80004674;
 case UINT32_C(0x80004678):goto L_80004678;
 case UINT32_C(0x8000467c):goto L_8000467c;
 case UINT32_C(0x80004680):goto L_80004680;
 case UINT32_C(0x80004684):goto L_80004684;
 case UINT32_C(0x80004688):goto L_80004688;
 case UINT32_C(0x8000468c):goto L_8000468c;
 case UINT32_C(0x80004690):goto L_80004690;
 case UINT32_C(0x80004694):goto L_80004694;
 case UINT32_C(0x80004698):goto L_80004698;
 case UINT32_C(0x8000469c):goto L_8000469c;
 case UINT32_C(0x800046a0):goto L_800046a0;
 case UINT32_C(0x800046a4):goto L_800046a4;
 case UINT32_C(0x800046a8):goto L_800046a8;
 case UINT32_C(0x80005978):goto L_80005978;
 case UINT32_C(0x8000597c):goto L_8000597c;
 case UINT32_C(0x80005980):goto L_80005980;
 case UINT32_C(0x80005984):goto L_80005984;
 case UINT32_C(0x80005988):goto L_80005988;
 case UINT32_C(0x8000598c):goto L_8000598c;
 case UINT32_C(0x80005990):goto L_80005990;
 case UINT32_C(0x80005994):goto L_80005994;
 case UINT32_C(0x80005998):goto L_80005998;
 case UINT32_C(0x8000599c):goto L_8000599c;
 case UINT32_C(0x800059a0):goto L_800059a0;
 case UINT32_C(0x800059a4):goto L_800059a4;
 case UINT32_C(0x800059a8):goto L_800059a8;
 case UINT32_C(0x800059ac):goto L_800059ac;
 case UINT32_C(0x800059b0):goto L_800059b0;
 case UINT32_C(0x80005ae8):goto L_80005ae8;
 case UINT32_C(0x80005aec):goto L_80005aec;
 case UINT32_C(0x80005af0):goto L_80005af0;
 case UINT32_C(0x80005af4):goto L_80005af4;
 case UINT32_C(0x80005af8):goto L_80005af8;
 case UINT32_C(0x80005afc):goto L_80005afc;
 case UINT32_C(0x80005b00):goto L_80005b00;
 case UINT32_C(0x80003a78):goto L_80003a78;
 case UINT32_C(0x80003a7c):goto L_80003a7c;
 case UINT32_C(0x80003a80):goto L_80003a80;
 case UINT32_C(0x80003a84):goto L_80003a84;
 case UINT32_C(0x80003a88):goto L_80003a88;
 case UINT32_C(0x80003a8c):goto L_80003a8c;
 case UINT32_C(0x80003a90):goto L_80003a90;
 case UINT32_C(0x80003a94):goto L_80003a94;
 case UINT32_C(0x80003a98):goto L_80003a98;
 case UINT32_C(0x80003a9c):goto L_80003a9c;
 case UINT32_C(0x80003aa0):goto L_80003aa0;
 case UINT32_C(0x80003aa4):goto L_80003aa4;
 case UINT32_C(0x80003aa8):goto L_80003aa8;
 case UINT32_C(0x80003aac):goto L_80003aac;
 case UINT32_C(0x80003ab0):goto L_80003ab0;
 case UINT32_C(0x80003ab4):goto L_80003ab4;
 case UINT32_C(0x80003ab8):goto L_80003ab8;
 case UINT32_C(0x80003abc):goto L_80003abc;
 case UINT32_C(0x80003ac0):goto L_80003ac0;
 case UINT32_C(0x80003ac4):goto L_80003ac4;
 case UINT32_C(0x80003ac8):goto L_80003ac8;
 case UINT32_C(0x80003acc):goto L_80003acc;
 case UINT32_C(0x80003ad0):goto L_80003ad0;
 case UINT32_C(0x80003ad4):goto L_80003ad4;
 case UINT32_C(0x80003ad8):goto L_80003ad8;
 case UINT32_C(0x80003adc):goto L_80003adc;
 case UINT32_C(0x80003ae0):goto L_80003ae0;
 case UINT32_C(0x80003ae4):goto L_80003ae4;
 case UINT32_C(0x80003ae8):goto L_80003ae8;
 case UINT32_C(0x80003aec):goto L_80003aec;
 case UINT32_C(0x80003af0):goto L_80003af0;
 case UINT32_C(0x80003af4):goto L_80003af4;
 case UINT32_C(0x80003af8):goto L_80003af8;
 case UINT32_C(0x80003afc):goto L_80003afc;
 case UINT32_C(0x80003b00):goto L_80003b00;
 case UINT32_C(0x80003b04):goto L_80003b04;
 case UINT32_C(0x80003b08):goto L_80003b08;
 case UINT32_C(0x80003b0c):goto L_80003b0c;
 case UINT32_C(0x80003b10):goto L_80003b10;
 case UINT32_C(0x80003b14):goto L_80003b14;
 case UINT32_C(0x80003b18):goto L_80003b18;
 case UINT32_C(0x80003b1c):goto L_80003b1c;
 case UINT32_C(0x80003b20):goto L_80003b20;
 case UINT32_C(0x80003b24):goto L_80003b24;
 case UINT32_C(0x80003b28):goto L_80003b28;
 case UINT32_C(0x80003b2c):goto L_80003b2c;
 case UINT32_C(0x80003b30):goto L_80003b30;
 case UINT32_C(0x80003b34):goto L_80003b34;
 case UINT32_C(0x80003b38):goto L_80003b38;
 case UINT32_C(0x80003b3c):goto L_80003b3c;
 case UINT32_C(0x80003b40):goto L_80003b40;
 case UINT32_C(0x80003b44):goto L_80003b44;
 case UINT32_C(0x80003b48):goto L_80003b48;
 case UINT32_C(0x80003b4c):goto L_80003b4c;
 case UINT32_C(0x80003b50):goto L_80003b50;
 case UINT32_C(0x80003b54):goto L_80003b54;
 case UINT32_C(0x80003b58):goto L_80003b58;
 case UINT32_C(0x80003b5c):goto L_80003b5c;
 case UINT32_C(0x80003b60):goto L_80003b60;
 case UINT32_C(0x80003b64):goto L_80003b64;
 case UINT32_C(0x80003b68):goto L_80003b68;
 case UINT32_C(0x80003b6c):goto L_80003b6c;
 case UINT32_C(0x80003b70):goto L_80003b70;
 case UINT32_C(0x80003b74):goto L_80003b74;
 case UINT32_C(0x80003b78):goto L_80003b78;
 case UINT32_C(0x80003b7c):goto L_80003b7c;
 case UINT32_C(0x80003b80):goto L_80003b80;
 case UINT32_C(0x80003b84):goto L_80003b84;
 case UINT32_C(0x80003b88):goto L_80003b88;
 case UINT32_C(0x80003b8c):goto L_80003b8c;
 case UINT32_C(0x80003b90):goto L_80003b90;
 case UINT32_C(0x80003b94):goto L_80003b94;
 case UINT32_C(0x80003b98):goto L_80003b98;
 case UINT32_C(0x80003b9c):goto L_80003b9c;
 case UINT32_C(0x80003ba0):goto L_80003ba0;
 case UINT32_C(0x80003ba4):goto L_80003ba4;
 case UINT32_C(0x80003ba8):goto L_80003ba8;
 case UINT32_C(0x80003bac):goto L_80003bac;
 case UINT32_C(0x80003bb0):goto L_80003bb0;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_80000180:
 STEP(UINT32_C(0x80000180)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80000184));goto dispatch;
L_80000184:
 STEP(UINT32_C(0x80000184)); /* ff5923b8 sd t9,0x23b8(k0) */
 value64=lo(m,25u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000023b8),&value64,8u);target=sx(UINT32_C(0x80000188));goto dispatch;
L_80000188:
 STEP(UINT32_C(0x80000188)); /* 40196800 cop0 rs0 rtt9 rd13 fn0 */
 set(m,25u,sx(m->cause));target=sx(UINT32_C(0x8000018c));goto dispatch;
L_8000018c:
 STEP(UINT32_C(0x8000018c)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80000190));goto dispatch;
L_80000190:
 STEP(UINT32_C(0x80000190)); /* 3339007c andi t9,t9,0x7c */
 set(m,25u,lo(m,25u) & UINT64_C(0x7c));target=sx(UINT32_C(0x80000194));goto dispatch;
L_80000194:
 STEP(UINT32_C(0x80000194)); /* 0359d021 addu k0,k0,t9 */
 set(m,26u,sx((uint32_t)lo(m,26u)+(uint32_t)lo(m,25u)));target=sx(UINT32_C(0x80000198));goto dispatch;
L_80000198:
 STEP(UINT32_C(0x80000198)); /* 8f5a2380 lw k0,0x2380(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x00002380),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x8000019c));goto dispatch;
L_8000019c:
 STEP(UINT32_C(0x8000019c)); /* 3c198001 lui t9,zero,0x8001 */
 set(m,25u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800001a0));goto dispatch;
L_800001a0:
 STEP(UINT32_C(0x800001a0)); /* 03400008 jr k0 */
 target=sx((uint32_t)lo(m,26u));STEP(UINT32_C(0x800001a4));READ((uint32_t)lo(m,25u)+UINT32_C(0x000023b8),&value64,8u);set(m,25u,value64);goto dispatch;
L_800001a4:
 STEP(UINT32_C(0x800001a4)); /* df3923b8 ld t9,0x23b8(t9) */
 READ((uint32_t)lo(m,25u)+UINT32_C(0x000023b8),&value64,8u);set(m,25u,value64);target=sx(UINT32_C(0x800001a8));goto dispatch;
L_80000280:
 STEP(UINT32_C(0x80000280)); /* 0462002a regimm2 v1,8000032c */
 if((int64_t)lo(m,3u)<0){STEP(UINT32_C(0x80000284));set(m,3u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x8000032c));}else target=sx(UINT32_C(0x80000288));goto dispatch;
L_80000284:
 STEP(UINT32_C(0x80000284)); /* 00031823 subu v1,zero,v1 */
 set(m,3u,sx((uint32_t)lo(m,0u)-(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80000288));goto dispatch;
L_80000288:
 STEP(UINT32_C(0x80000288)); /* 241a007c addiu k0,zero,124 */
 set(m,26u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000007c)));target=sx(UINT32_C(0x8000028c));goto dispatch;
L_8000028c:
 STEP(UINT32_C(0x8000028c)); /* 17430003 bne k0,v1,8000029c */
 {int taken=(lo(m,26u)!=lo(m,3u));STEP(UINT32_C(0x80000290));/* nop */target=sx(taken?UINT32_C(0x8000029c):UINT32_C(0x80000294));goto dispatch;}
L_80000290:
 STEP(UINT32_C(0x80000290)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80000294));goto dispatch;
L_80000294:
 STEP(UINT32_C(0x80000294)); /* 0800448f j 8001123c */
 STEP(UINT32_C(0x80000298));/* nop */target=sx(UINT32_C(0x8001123c));goto dispatch;
L_80000298:
 STEP(UINT32_C(0x80000298)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000029c));goto dispatch;
L_8000029c:
 STEP(UINT32_C(0x8000029c)); /* 3c1a8000 lui k0,zero,0x8000 */
 set(m,26u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800002a0));goto dispatch;
L_800002a0:
 STEP(UINT32_C(0x800002a0)); /* 7f5d10c0 sq sp,0x10c0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000010c0),m->gpr[29],16u);target=sx(UINT32_C(0x800002a4));goto dispatch;
L_800002a4:
 STEP(UINT32_C(0x800002a4)); /* 7f5f10d0 sq ra,0x10d0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000010d0),m->gpr[31],16u);target=sx(UINT32_C(0x800002a8));goto dispatch;
L_800002a8:
 STEP(UINT32_C(0x800002a8)); /* 7f4110e0 sq at,0x10e0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000010e0),m->gpr[1],16u);target=sx(UINT32_C(0x800002ac));goto dispatch;
L_800002ac:
 STEP(UINT32_C(0x800002ac)); /* 40016000 cop0 rs0 rtat rd12 fn0 */
 set(m,1u,sx(m->status));target=sx(UINT32_C(0x800002b0));goto dispatch;
L_800002b0:
 STEP(UINT32_C(0x800002b0)); /* 241affe4 addiu k0,zero,-28 */
 set(m,26u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffe4)));target=sx(UINT32_C(0x800002b4));goto dispatch;
L_800002b4:
 STEP(UINT32_C(0x800002b4)); /* 003a0824 and at,at,k0 */
 set(m,1u,lo(m,1u)&lo(m,26u));target=sx(UINT32_C(0x800002b8));goto dispatch;
L_800002b8:
 STEP(UINT32_C(0x800002b8)); /* 40816000 cop0 rs4 rtat rd12 fn0 */
 m->status=(uint32_t)lo(m,1u);target=sx(UINT32_C(0x800002bc));goto dispatch;
L_800002bc:
 STEP(UINT32_C(0x800002bc)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x800002c0));goto dispatch;
L_800002c0:
 STEP(UINT32_C(0x800002c0)); /* 03a0d02d daddu k0,sp,zero */
 set(m,26u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x800002c4));goto dispatch;
L_800002c4:
 STEP(UINT32_C(0x800002c4)); /* 3c1d8001 lui sp,zero,0x8001 */
 set(m,29u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800002c8));goto dispatch;
L_800002c8:
 STEP(UINT32_C(0x800002c8)); /* 27bd5c40 addiu sp,sp,23616 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00005c40)));target=sx(UINT32_C(0x800002cc));goto dispatch;
L_800002cc:
 STEP(UINT32_C(0x800002cc)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x800002d0));goto dispatch;
L_800002d0:
 STEP(UINT32_C(0x800002d0)); /* afbf0000 sw ra,0x0(sp) */
 value32=(uint32_t)lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800002d4));goto dispatch;
L_800002d4:
 STEP(UINT32_C(0x800002d4)); /* afba0004 sw k0,0x4(sp) */
 value32=(uint32_t)lo(m,26u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x800002d8));goto dispatch;
L_800002d8:
 STEP(UINT32_C(0x800002d8)); /* 401a7000 cop0 rs0 rtk0 rd14 fn0 */
 set(m,26u,sx(m->epc));target=sx(UINT32_C(0x800002dc));goto dispatch;
L_800002dc:
 STEP(UINT32_C(0x800002dc)); /* 275a0004 addiu k0,k0,4 */
 set(m,26u,sx((uint32_t)lo(m,26u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x800002e0));goto dispatch;
L_800002e0:
 STEP(UINT32_C(0x800002e0)); /* afba0008 sw k0,0x8(sp) */
 value32=(uint32_t)lo(m,26u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x800002e4));goto dispatch;
L_800002e4:
 STEP(UINT32_C(0x800002e4)); /* 409a7000 cop0 rs4 rtk0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x800002e8));goto dispatch;
L_800002e8:
 STEP(UINT32_C(0x800002e8)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x800002ec));goto dispatch;
L_800002ec:
 STEP(UINT32_C(0x800002ec)); /* 00031880 sll v1,v1,2 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<2u));target=sx(UINT32_C(0x800002f0));goto dispatch;
L_800002f0:
 STEP(UINT32_C(0x800002f0)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800002f4));goto dispatch;
L_800002f4:
 STEP(UINT32_C(0x800002f4)); /* 0343d021 addu k0,k0,v1 */
 set(m,26u,sx((uint32_t)lo(m,26u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x800002f8));goto dispatch;
L_800002f8:
 STEP(UINT32_C(0x800002f8)); /* 8f5a1f80 lw k0,0x1f80(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x00001f80),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x800002fc));goto dispatch;
L_800002fc:
 STEP(UINT32_C(0x800002fc)); /* 0340f809 jalr ra,k0 */
 target=sx((uint32_t)lo(m,26u));set(m,31u,UINT64_C(0x80000304));STEP(UINT32_C(0x80000300));/* nop */goto dispatch;
L_80000300:
 STEP(UINT32_C(0x80000300)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80000304));goto dispatch;
L_80000304:
 STEP(UINT32_C(0x80000304)); /* 8fba0008 lw k0,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x80000308));goto dispatch;
L_80000308:
 STEP(UINT32_C(0x80000308)); /* 8fbf0000 lw ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,31u,sx(value32));target=sx(UINT32_C(0x8000030c));goto dispatch;
L_8000030c:
 STEP(UINT32_C(0x8000030c)); /* 8fbd0004 lw sp,0x4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x80000310));goto dispatch;
L_80000310:
 STEP(UINT32_C(0x80000310)); /* 409a7000 cop0 rs4 rtk0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80000314));goto dispatch;
L_80000314:
 STEP(UINT32_C(0x80000314)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80000318));goto dispatch;
L_80000318:
 STEP(UINT32_C(0x80000318)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x8000031c));goto dispatch;
L_8000031c:
 STEP(UINT32_C(0x8000031c)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x80000320));goto dispatch;
L_80000320:
 STEP(UINT32_C(0x80000320)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80000324));goto dispatch;
L_80000324:
 STEP(UINT32_C(0x80000324)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80000328));goto dispatch;
L_80000328:
 STEP(UINT32_C(0x80000328)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_8000032c:
 STEP(UINT32_C(0x8000032c)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80000330));goto dispatch;
L_80000330:
 STEP(UINT32_C(0x80000330)); /* afbf0000 sw ra,0x0(sp) */
 value32=(uint32_t)lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80000334));goto dispatch;
L_80000334:
 STEP(UINT32_C(0x80000334)); /* 401a7000 cop0 rs0 rtk0 rd14 fn0 */
 set(m,26u,sx(m->epc));target=sx(UINT32_C(0x80000338));goto dispatch;
L_80000338:
 STEP(UINT32_C(0x80000338)); /* 275a0004 addiu k0,k0,4 */
 set(m,26u,sx((uint32_t)lo(m,26u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x8000033c));goto dispatch;
L_8000033c:
 STEP(UINT32_C(0x8000033c)); /* afba0004 sw k0,0x4(sp) */
 value32=(uint32_t)lo(m,26u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80000340));goto dispatch;
L_80000340:
 STEP(UINT32_C(0x80000340)); /* 409a7000 cop0 rs4 rtk0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80000344));goto dispatch;
L_80000344:
 STEP(UINT32_C(0x80000344)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80000348));goto dispatch;
L_80000348:
 STEP(UINT32_C(0x80000348)); /* 00031880 sll v1,v1,2 */
 set(m,3u,sx((uint32_t)lo(m,3u)<<2u));target=sx(UINT32_C(0x8000034c));goto dispatch;
L_8000034c:
 STEP(UINT32_C(0x8000034c)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80000350));goto dispatch;
L_80000350:
 STEP(UINT32_C(0x80000350)); /* 0343d021 addu k0,k0,v1 */
 set(m,26u,sx((uint32_t)lo(m,26u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80000354));goto dispatch;
L_80000354:
 STEP(UINT32_C(0x80000354)); /* 8f5a1f80 lw k0,0x1f80(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x00001f80),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x80000358));goto dispatch;
L_80000358:
 STEP(UINT32_C(0x80000358)); /* 0340f809 jalr ra,k0 */
 target=sx((uint32_t)lo(m,26u));set(m,31u,UINT64_C(0x80000360));STEP(UINT32_C(0x8000035c));/* nop */goto dispatch;
L_8000035c:
 STEP(UINT32_C(0x8000035c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80000360));goto dispatch;
L_80000360:
 STEP(UINT32_C(0x80000360)); /* 8fba0004 lw k0,0x4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x80000364));goto dispatch;
L_80000364:
 STEP(UINT32_C(0x80000364)); /* 8fbf0000 lw ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,31u,sx(value32));target=sx(UINT32_C(0x80000368));goto dispatch;
L_80000368:
 STEP(UINT32_C(0x80000368)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x8000036c));goto dispatch;
L_8000036c:
 STEP(UINT32_C(0x8000036c)); /* 409a7000 cop0 rs4 rtk0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80000370));goto dispatch;
L_80000370:
 STEP(UINT32_C(0x80000370)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80000374));goto dispatch;
L_80000374:
 STEP(UINT32_C(0x80000374)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80003340:
 STEP(UINT32_C(0x80003340)); /* 0c000da0 jal 80003680 */
 set(m,31u,UINT64_C(0x80003348));STEP(UINT32_C(0x80003344));set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003680));goto dispatch;
L_80003344:
 STEP(UINT32_C(0x80003344)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80003348));goto dispatch;
L_80003348:
 STEP(UINT32_C(0x80003348)); /* 0c0011ac jal 800046b0 */
 set(m,31u,UINT64_C(0x80003350));STEP(UINT32_C(0x8000334c));/* nop */target=sx(UINT32_C(0x800046b0));goto dispatch;
L_8000334c:
 STEP(UINT32_C(0x8000334c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003350));goto dispatch;
L_80003350:
 STEP(UINT32_C(0x80003350)); /* 0440000e regimm0 v0,8000338c */
 {int taken=((int64_t)lo(m,2u)<0);STEP(UINT32_C(0x80003354));/* nop */target=sx(taken?UINT32_C(0x8000338c):UINT32_C(0x80003358));goto dispatch;}
L_80003354:
 STEP(UINT32_C(0x80003354)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003358));goto dispatch;
L_80003358:
 STEP(UINT32_C(0x80003358)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x8000335c));goto dispatch;
L_8000335c:
 STEP(UINT32_C(0x8000335c)); /* 40047000 cop0 rs0 rta0 rd14 fn0 */
 set(m,4u,sx(m->epc));target=sx(UINT32_C(0x80003360));goto dispatch;
L_80003360:
 STEP(UINT32_C(0x80003360)); /* 0c000e50 jal 80003940 */
 set(m,31u,UINT64_C(0x80003368));STEP(UINT32_C(0x80003364));READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003940));goto dispatch;
L_80003364:
 STEP(UINT32_C(0x80003364)); /* 8ca510c0 lw a1,0x10c0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003368));goto dispatch;
L_80003368:
 STEP(UINT32_C(0x80003368)); /* 40827000 cop0 rs4 rtv0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x8000336c));goto dispatch;
L_8000336c:
 STEP(UINT32_C(0x8000336c)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003370));goto dispatch;
L_80003370:
 STEP(UINT32_C(0x80003370)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x80003378));STEP(UINT32_C(0x80003374));set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003800));goto dispatch;
L_80003374:
 STEP(UINT32_C(0x80003374)); /* 0060e82d daddu sp,v1,zero */
 set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003378));goto dispatch;
L_80003378:
 STEP(UINT32_C(0x80003378)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x8000337c));goto dispatch;
L_8000337c:
 STEP(UINT32_C(0x8000337c)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x80003380));goto dispatch;
L_80003380:
 STEP(UINT32_C(0x80003380)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003384));goto dispatch;
L_80003384:
 STEP(UINT32_C(0x80003384)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003388));goto dispatch;
L_80003388:
 STEP(UINT32_C(0x80003388)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_8000338c:
 STEP(UINT32_C(0x8000338c)); /* 3c1d8000 lui sp,zero,0x8000 */
 set(m,29u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003390));goto dispatch;
L_80003390:
 STEP(UINT32_C(0x80003390)); /* 8fbd10c0 lw sp,0x10c0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000010c0),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x80003394));goto dispatch;
L_80003394:
 STEP(UINT32_C(0x80003394)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x8000339c));STEP(UINT32_C(0x80003398));value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80003800));goto dispatch;
L_80003398:
 STEP(UINT32_C(0x80003398)); /* ffa20020 sd v0,0x20(sp) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x8000339c));goto dispatch;
L_8000339c:
 STEP(UINT32_C(0x8000339c)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x800033a0));goto dispatch;
L_800033a0:
 STEP(UINT32_C(0x800033a0)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x800033a4));goto dispatch;
L_800033a4:
 STEP(UINT32_C(0x800033a4)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x800033a8));goto dispatch;
L_800033a8:
 STEP(UINT32_C(0x800033a8)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x800033ac));goto dispatch;
L_800033ac:
 STEP(UINT32_C(0x800033ac)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80003680:
 STEP(UINT32_C(0x80003680)); /* 3c1a8000 lui k0,zero,0x8000 */
 set(m,26u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003684));goto dispatch;
L_80003684:
 STEP(UINT32_C(0x80003684)); /* 7b5a10c0 lq k0,0x10c0(k0) */
 {uint32_t q[4];READ((uint32_t)lo(m,26u)+UINT32_C(0x000010c0),q,16u);memcpy(m->gpr[26],q,16u);}target=sx(UINT32_C(0x80003688));goto dispatch;
L_80003688:
 STEP(UINT32_C(0x80003688)); /* 275afd80 addiu k0,k0,-640 */
 set(m,26u,sx((uint32_t)lo(m,26u)+UINT32_C(0xfffffd80)));target=sx(UINT32_C(0x8000368c));goto dispatch;
L_8000368c:
 STEP(UINT32_C(0x8000368c)); /* 3c018000 lui at,zero,0x8000 */
 set(m,1u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003690));goto dispatch;
L_80003690:
 STEP(UINT32_C(0x80003690)); /* 782110e0 lq at,0x10e0(at) */
 {uint32_t q[4];READ((uint32_t)lo(m,1u)+UINT32_C(0x000010e0),q,16u);memcpy(m->gpr[1],q,16u);}target=sx(UINT32_C(0x80003694));goto dispatch;
L_80003694:
 STEP(UINT32_C(0x80003694)); /* 7f410010 sq at,0x10(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000010),m->gpr[1],16u);target=sx(UINT32_C(0x80003698));goto dispatch;
L_80003698:
 STEP(UINT32_C(0x80003698)); /* 7f420020 sq v0,0x20(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000020),m->gpr[2],16u);target=sx(UINT32_C(0x8000369c));goto dispatch;
L_8000369c:
 STEP(UINT32_C(0x8000369c)); /* 7f430030 sq v1,0x30(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000030),m->gpr[3],16u);target=sx(UINT32_C(0x800036a0));goto dispatch;
L_800036a0:
 STEP(UINT32_C(0x800036a0)); /* 7f440040 sq a0,0x40(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000040),m->gpr[4],16u);target=sx(UINT32_C(0x800036a4));goto dispatch;
L_800036a4:
 STEP(UINT32_C(0x800036a4)); /* 7f450050 sq a1,0x50(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000050),m->gpr[5],16u);target=sx(UINT32_C(0x800036a8));goto dispatch;
L_800036a8:
 STEP(UINT32_C(0x800036a8)); /* 7f460060 sq a2,0x60(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000060),m->gpr[6],16u);target=sx(UINT32_C(0x800036ac));goto dispatch;
L_800036ac:
 STEP(UINT32_C(0x800036ac)); /* 7f470070 sq a3,0x70(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000070),m->gpr[7],16u);target=sx(UINT32_C(0x800036b0));goto dispatch;
L_800036b0:
 STEP(UINT32_C(0x800036b0)); /* 7f480080 sq t0,0x80(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000080),m->gpr[8],16u);target=sx(UINT32_C(0x800036b4));goto dispatch;
L_800036b4:
 STEP(UINT32_C(0x800036b4)); /* 7f490090 sq t1,0x90(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000090),m->gpr[9],16u);target=sx(UINT32_C(0x800036b8));goto dispatch;
L_800036b8:
 STEP(UINT32_C(0x800036b8)); /* 7f4a00a0 sq t2,0xa0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000000a0),m->gpr[10],16u);target=sx(UINT32_C(0x800036bc));goto dispatch;
L_800036bc:
 STEP(UINT32_C(0x800036bc)); /* 7f4b00b0 sq t3,0xb0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000000b0),m->gpr[11],16u);target=sx(UINT32_C(0x800036c0));goto dispatch;
L_800036c0:
 STEP(UINT32_C(0x800036c0)); /* 7f4c00c0 sq t4,0xc0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000000c0),m->gpr[12],16u);target=sx(UINT32_C(0x800036c4));goto dispatch;
L_800036c4:
 STEP(UINT32_C(0x800036c4)); /* 7f4d00d0 sq t5,0xd0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000000d0),m->gpr[13],16u);target=sx(UINT32_C(0x800036c8));goto dispatch;
L_800036c8:
 STEP(UINT32_C(0x800036c8)); /* 7f4e00e0 sq t6,0xe0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000000e0),m->gpr[14],16u);target=sx(UINT32_C(0x800036cc));goto dispatch;
L_800036cc:
 STEP(UINT32_C(0x800036cc)); /* 7f4f00f0 sq t7,0xf0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000000f0),m->gpr[15],16u);target=sx(UINT32_C(0x800036d0));goto dispatch;
L_800036d0:
 STEP(UINT32_C(0x800036d0)); /* 7f500100 sq s0,0x100(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000100),m->gpr[16],16u);target=sx(UINT32_C(0x800036d4));goto dispatch;
L_800036d4:
 STEP(UINT32_C(0x800036d4)); /* 7f510110 sq s1,0x110(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000110),m->gpr[17],16u);target=sx(UINT32_C(0x800036d8));goto dispatch;
L_800036d8:
 STEP(UINT32_C(0x800036d8)); /* 7f520120 sq s2,0x120(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000120),m->gpr[18],16u);target=sx(UINT32_C(0x800036dc));goto dispatch;
L_800036dc:
 STEP(UINT32_C(0x800036dc)); /* 7f530130 sq s3,0x130(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000130),m->gpr[19],16u);target=sx(UINT32_C(0x800036e0));goto dispatch;
L_800036e0:
 STEP(UINT32_C(0x800036e0)); /* 7f540140 sq s4,0x140(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000140),m->gpr[20],16u);target=sx(UINT32_C(0x800036e4));goto dispatch;
L_800036e4:
 STEP(UINT32_C(0x800036e4)); /* 7f550150 sq s5,0x150(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000150),m->gpr[21],16u);target=sx(UINT32_C(0x800036e8));goto dispatch;
L_800036e8:
 STEP(UINT32_C(0x800036e8)); /* 7f560160 sq s6,0x160(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000160),m->gpr[22],16u);target=sx(UINT32_C(0x800036ec));goto dispatch;
L_800036ec:
 STEP(UINT32_C(0x800036ec)); /* 7f570170 sq s7,0x170(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000170),m->gpr[23],16u);target=sx(UINT32_C(0x800036f0));goto dispatch;
L_800036f0:
 STEP(UINT32_C(0x800036f0)); /* 7f580180 sq t8,0x180(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000180),m->gpr[24],16u);target=sx(UINT32_C(0x800036f4));goto dispatch;
L_800036f4:
 STEP(UINT32_C(0x800036f4)); /* 7f590190 sq t9,0x190(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000190),m->gpr[25],16u);target=sx(UINT32_C(0x800036f8));goto dispatch;
L_800036f8:
 STEP(UINT32_C(0x800036f8)); /* 7f5c01c0 sq gp,0x1c0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000001c0),m->gpr[28],16u);target=sx(UINT32_C(0x800036fc));goto dispatch;
L_800036fc:
 STEP(UINT32_C(0x800036fc)); /* 3c018000 lui at,zero,0x8000 */
 set(m,1u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003700));goto dispatch;
L_80003700:
 STEP(UINT32_C(0x80003700)); /* 782110c0 lq at,0x10c0(at) */
 {uint32_t q[4];READ((uint32_t)lo(m,1u)+UINT32_C(0x000010c0),q,16u);memcpy(m->gpr[1],q,16u);}target=sx(UINT32_C(0x80003704));goto dispatch;
L_80003704:
 STEP(UINT32_C(0x80003704)); /* 7f4101d0 sq at,0x1d0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000001d0),m->gpr[1],16u);target=sx(UINT32_C(0x80003708));goto dispatch;
L_80003708:
 STEP(UINT32_C(0x80003708)); /* 7f5e01e0 sq s8,0x1e0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000001e0),m->gpr[30],16u);target=sx(UINT32_C(0x8000370c));goto dispatch;
L_8000370c:
 STEP(UINT32_C(0x8000370c)); /* 3c018000 lui at,zero,0x8000 */
 set(m,1u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003710));goto dispatch;
L_80003710:
 STEP(UINT32_C(0x80003710)); /* 782110d0 lq at,0x10d0(at) */
 {uint32_t q[4];READ((uint32_t)lo(m,1u)+UINT32_C(0x000010d0),q,16u);memcpy(m->gpr[1],q,16u);}target=sx(UINT32_C(0x80003714));goto dispatch;
L_80003714:
 STEP(UINT32_C(0x80003714)); /* 7f4101f0 sq at,0x1f0(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000001f0),m->gpr[1],16u);target=sx(UINT32_C(0x80003718));goto dispatch;
L_80003718:
 STEP(UINT32_C(0x80003718)); /* e7400200 swc1 f0,0x200(k0) */
 value32=m->fpr[0];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000200),&value32,4u);target=sx(UINT32_C(0x8000371c));goto dispatch;
L_8000371c:
 STEP(UINT32_C(0x8000371c)); /* e7410204 swc1 f1,0x204(k0) */
 value32=m->fpr[1];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000204),&value32,4u);target=sx(UINT32_C(0x80003720));goto dispatch;
L_80003720:
 STEP(UINT32_C(0x80003720)); /* e7420208 swc1 f2,0x208(k0) */
 value32=m->fpr[2];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000208),&value32,4u);target=sx(UINT32_C(0x80003724));goto dispatch;
L_80003724:
 STEP(UINT32_C(0x80003724)); /* e743020c swc1 f3,0x20c(k0) */
 value32=m->fpr[3];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x0000020c),&value32,4u);target=sx(UINT32_C(0x80003728));goto dispatch;
L_80003728:
 STEP(UINT32_C(0x80003728)); /* e7440210 swc1 f4,0x210(k0) */
 value32=m->fpr[4];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000210),&value32,4u);target=sx(UINT32_C(0x8000372c));goto dispatch;
L_8000372c:
 STEP(UINT32_C(0x8000372c)); /* e7450214 swc1 f5,0x214(k0) */
 value32=m->fpr[5];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000214),&value32,4u);target=sx(UINT32_C(0x80003730));goto dispatch;
L_80003730:
 STEP(UINT32_C(0x80003730)); /* e7460218 swc1 f6,0x218(k0) */
 value32=m->fpr[6];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000218),&value32,4u);target=sx(UINT32_C(0x80003734));goto dispatch;
L_80003734:
 STEP(UINT32_C(0x80003734)); /* e747021c swc1 f7,0x21c(k0) */
 value32=m->fpr[7];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x0000021c),&value32,4u);target=sx(UINT32_C(0x80003738));goto dispatch;
L_80003738:
 STEP(UINT32_C(0x80003738)); /* e7480220 swc1 f8,0x220(k0) */
 value32=m->fpr[8];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000220),&value32,4u);target=sx(UINT32_C(0x8000373c));goto dispatch;
L_8000373c:
 STEP(UINT32_C(0x8000373c)); /* e7490224 swc1 f9,0x224(k0) */
 value32=m->fpr[9];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000224),&value32,4u);target=sx(UINT32_C(0x80003740));goto dispatch;
L_80003740:
 STEP(UINT32_C(0x80003740)); /* e74a0228 swc1 f10,0x228(k0) */
 value32=m->fpr[10];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000228),&value32,4u);target=sx(UINT32_C(0x80003744));goto dispatch;
L_80003744:
 STEP(UINT32_C(0x80003744)); /* e74b022c swc1 f11,0x22c(k0) */
 value32=m->fpr[11];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x0000022c),&value32,4u);target=sx(UINT32_C(0x80003748));goto dispatch;
L_80003748:
 STEP(UINT32_C(0x80003748)); /* e74c0230 swc1 f12,0x230(k0) */
 value32=m->fpr[12];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000230),&value32,4u);target=sx(UINT32_C(0x8000374c));goto dispatch;
L_8000374c:
 STEP(UINT32_C(0x8000374c)); /* e74d0234 swc1 f13,0x234(k0) */
 value32=m->fpr[13];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000234),&value32,4u);target=sx(UINT32_C(0x80003750));goto dispatch;
L_80003750:
 STEP(UINT32_C(0x80003750)); /* e74e0238 swc1 f14,0x238(k0) */
 value32=m->fpr[14];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000238),&value32,4u);target=sx(UINT32_C(0x80003754));goto dispatch;
L_80003754:
 STEP(UINT32_C(0x80003754)); /* e74f023c swc1 f15,0x23c(k0) */
 value32=m->fpr[15];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x0000023c),&value32,4u);target=sx(UINT32_C(0x80003758));goto dispatch;
L_80003758:
 STEP(UINT32_C(0x80003758)); /* e7500240 swc1 f16,0x240(k0) */
 value32=m->fpr[16];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000240),&value32,4u);target=sx(UINT32_C(0x8000375c));goto dispatch;
L_8000375c:
 STEP(UINT32_C(0x8000375c)); /* e7510244 swc1 f17,0x244(k0) */
 value32=m->fpr[17];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000244),&value32,4u);target=sx(UINT32_C(0x80003760));goto dispatch;
L_80003760:
 STEP(UINT32_C(0x80003760)); /* e7520248 swc1 f18,0x248(k0) */
 value32=m->fpr[18];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000248),&value32,4u);target=sx(UINT32_C(0x80003764));goto dispatch;
L_80003764:
 STEP(UINT32_C(0x80003764)); /* e753024c swc1 f19,0x24c(k0) */
 value32=m->fpr[19];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x0000024c),&value32,4u);target=sx(UINT32_C(0x80003768));goto dispatch;
L_80003768:
 STEP(UINT32_C(0x80003768)); /* e7540250 swc1 f20,0x250(k0) */
 value32=m->fpr[20];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000250),&value32,4u);target=sx(UINT32_C(0x8000376c));goto dispatch;
L_8000376c:
 STEP(UINT32_C(0x8000376c)); /* e7550254 swc1 f21,0x254(k0) */
 value32=m->fpr[21];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000254),&value32,4u);target=sx(UINT32_C(0x80003770));goto dispatch;
L_80003770:
 STEP(UINT32_C(0x80003770)); /* e7560258 swc1 f22,0x258(k0) */
 value32=m->fpr[22];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000258),&value32,4u);target=sx(UINT32_C(0x80003774));goto dispatch;
L_80003774:
 STEP(UINT32_C(0x80003774)); /* e757025c swc1 f23,0x25c(k0) */
 value32=m->fpr[23];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x0000025c),&value32,4u);target=sx(UINT32_C(0x80003778));goto dispatch;
L_80003778:
 STEP(UINT32_C(0x80003778)); /* e7580260 swc1 f24,0x260(k0) */
 value32=m->fpr[24];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000260),&value32,4u);target=sx(UINT32_C(0x8000377c));goto dispatch;
L_8000377c:
 STEP(UINT32_C(0x8000377c)); /* e7590264 swc1 f25,0x264(k0) */
 value32=m->fpr[25];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000264),&value32,4u);target=sx(UINT32_C(0x80003780));goto dispatch;
L_80003780:
 STEP(UINT32_C(0x80003780)); /* e75a0268 swc1 f26,0x268(k0) */
 value32=m->fpr[26];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000268),&value32,4u);target=sx(UINT32_C(0x80003784));goto dispatch;
L_80003784:
 STEP(UINT32_C(0x80003784)); /* e75b026c swc1 f27,0x26c(k0) */
 value32=m->fpr[27];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x0000026c),&value32,4u);target=sx(UINT32_C(0x80003788));goto dispatch;
L_80003788:
 STEP(UINT32_C(0x80003788)); /* e75c0270 swc1 f28,0x270(k0) */
 value32=m->fpr[28];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000270),&value32,4u);target=sx(UINT32_C(0x8000378c));goto dispatch;
L_8000378c:
 STEP(UINT32_C(0x8000378c)); /* e75d0274 swc1 f29,0x274(k0) */
 value32=m->fpr[29];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000274),&value32,4u);target=sx(UINT32_C(0x80003790));goto dispatch;
L_80003790:
 STEP(UINT32_C(0x80003790)); /* e75e0278 swc1 f30,0x278(k0) */
 value32=m->fpr[30];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000278),&value32,4u);target=sx(UINT32_C(0x80003794));goto dispatch;
L_80003794:
 STEP(UINT32_C(0x80003794)); /* e75f027c swc1 f31,0x27c(k0) */
 value32=m->fpr[31];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x0000027c),&value32,4u);target=sx(UINT32_C(0x80003798));goto dispatch;
L_80003798:
 STEP(UINT32_C(0x80003798)); /* 00000828 mfsa at */
 set(m,1u,(uint64_t)m->sa);target=sx(UINT32_C(0x8000379c));goto dispatch;
L_8000379c:
 STEP(UINT32_C(0x8000379c)); /* af410000 sw at,0x0(k0) */
 value32=(uint32_t)lo(m,1u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800037a0));goto dispatch;
L_800037a0:
 STEP(UINT32_C(0x800037a0)); /* 4441f800 cop1 4441f800 */
 set(m,1u,sx(m->fcsr));target=sx(UINT32_C(0x800037a4));goto dispatch;
L_800037a4:
 STEP(UINT32_C(0x800037a4)); /* af410004 sw at,0x4(k0) */
 value32=(uint32_t)lo(m,1u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x800037a8));goto dispatch;
L_800037a8:
 STEP(UINT32_C(0x800037a8)); /* 3c018000 lui at,zero,0x8000 */
 set(m,1u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800037ac));goto dispatch;
L_800037ac:
 STEP(UINT32_C(0x800037ac)); /* 44810800 cop1 44810800 */
 m->fpr[1]=(uint32_t)lo(m,1u);target=sx(UINT32_C(0x800037b0));goto dispatch;
L_800037b0:
 STEP(UINT32_C(0x800037b0)); /* 44800000 cop1 44800000 */
 m->fpr[0]=(uint32_t)lo(m,0u);target=sx(UINT32_C(0x800037b4));goto dispatch;
L_800037b4:
 STEP(UINT32_C(0x800037b4)); /* 4601001c cop1 4601001c */
 if(m->fpr[0]!=0u||m->fpr[1]!=0x80000000u||!normal_or_zero(m->fpu_acc))return stop(m,s,NOCTURNE_WAKEUP_FPU_DOMAIN,0,0,0);m->fpr[0]=m->fpu_acc;m->fcsr&=~UINT32_C(0x0000c000); /* ACC + (+0 * -0), finite-normal/zero value profile */target=sx(UINT32_C(0x800037b8));goto dispatch;
L_800037b8:
 STEP(UINT32_C(0x800037b8)); /* e7400008 swc1 f0,0x8(k0) */
 value32=m->fpr[0];WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x800037bc));goto dispatch;
L_800037bc:
 STEP(UINT32_C(0x800037bc)); /* 00000810 mfhi at */
 set(m,1u,m->hi);target=sx(UINT32_C(0x800037c0));goto dispatch;
L_800037c0:
 STEP(UINT32_C(0x800037c0)); /* ff4101a0 sd at,0x1a0(k0) */
 value64=lo(m,1u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000001a0),&value64,8u);target=sx(UINT32_C(0x800037c4));goto dispatch;
L_800037c4:
 STEP(UINT32_C(0x800037c4)); /* 70000810 mmi 70000810 */
 set(m,1u,m->hi1);target=sx(UINT32_C(0x800037c8));goto dispatch;
L_800037c8:
 STEP(UINT32_C(0x800037c8)); /* ff4101a8 sd at,0x1a8(k0) */
 value64=lo(m,1u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000001a8),&value64,8u);target=sx(UINT32_C(0x800037cc));goto dispatch;
L_800037cc:
 STEP(UINT32_C(0x800037cc)); /* 00000812 mflo at */
 set(m,1u,m->lo);target=sx(UINT32_C(0x800037d0));goto dispatch;
L_800037d0:
 STEP(UINT32_C(0x800037d0)); /* ff4101b0 sd at,0x1b0(k0) */
 value64=lo(m,1u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000001b0),&value64,8u);target=sx(UINT32_C(0x800037d4));goto dispatch;
L_800037d4:
 STEP(UINT32_C(0x800037d4)); /* 70000812 mmi 70000812 */
 set(m,1u,m->lo1);target=sx(UINT32_C(0x800037d8));goto dispatch;
L_800037d8:
 STEP(UINT32_C(0x800037d8)); /* ff4101b8 sd at,0x1b8(k0) */
 value64=lo(m,1u);WRITE((uint32_t)lo(m,26u)+UINT32_C(0x000001b8),&value64,8u);target=sx(UINT32_C(0x800037dc));goto dispatch;
L_800037dc:
 STEP(UINT32_C(0x800037dc)); /* 3c018000 lui at,zero,0x8000 */
 set(m,1u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800037e0));goto dispatch;
L_800037e0:
 STEP(UINT32_C(0x800037e0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800037e4));value32=(uint32_t)lo(m,26u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000010c0),&value32,4u);goto dispatch;
L_800037e4:
 STEP(UINT32_C(0x800037e4)); /* ac3a10c0 sw k0,0x10c0(at) */
 value32=(uint32_t)lo(m,26u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000010c0),&value32,4u);target=sx(UINT32_C(0x800037e8));goto dispatch;
L_80003800:
 STEP(UINT32_C(0x80003800)); /* 3c1a8000 lui k0,zero,0x8000 */
 set(m,26u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x80003804));goto dispatch;
L_80003804:
 STEP(UINT32_C(0x80003804)); /* 449a0800 cop1 449a0800 */
 m->fpr[1]=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003808));goto dispatch;
L_80003808:
 STEP(UINT32_C(0x80003808)); /* c7a00008 lwc1 f0,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value32,4u);m->fpr[0]=value32;target=sx(UINT32_C(0x8000380c));goto dispatch;
L_8000380c:
 STEP(UINT32_C(0x8000380c)); /* 46010018 cop1 46010018 */
 if(m->fpr[1]!=0x80000000u||!normal_or_zero(m->fpr[0]))return stop(m,s,NOCTURNE_WAKEUP_FPU_DOMAIN,0,0,0);m->fpu_acc=m->fpr[0];m->fcsr&=~UINT32_C(0x0000c000); /* ADDA F0,-0 in same value profile; FCSR restored later */target=sx(UINT32_C(0x80003810));goto dispatch;
L_80003810:
 STEP(UINT32_C(0x80003810)); /* 8fba0000 lw k0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x80003814));goto dispatch;
L_80003814:
 STEP(UINT32_C(0x80003814)); /* 03400029 mtsa k0 */
 m->sa=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003818));goto dispatch;
L_80003818:
 STEP(UINT32_C(0x80003818)); /* 8fba0004 lw k0,0x4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000004),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x8000381c));goto dispatch;
L_8000381c:
 STEP(UINT32_C(0x8000381c)); /* 44daf800 cop1 44daf800 */
 m->fcsr=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003820));goto dispatch;
L_80003820:
 STEP(UINT32_C(0x80003820)); /* dfba01a0 ld k0,0x1a0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001a0),&value64,8u);set(m,26u,value64);target=sx(UINT32_C(0x80003824));goto dispatch;
L_80003824:
 STEP(UINT32_C(0x80003824)); /* 03400011 mthi k0 */
 m->hi=lo(m,26u);target=sx(UINT32_C(0x80003828));goto dispatch;
L_80003828:
 STEP(UINT32_C(0x80003828)); /* dfba01a8 ld k0,0x1a8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001a8),&value64,8u);set(m,26u,value64);target=sx(UINT32_C(0x8000382c));goto dispatch;
L_8000382c:
 STEP(UINT32_C(0x8000382c)); /* 73400011 mmi 73400011 */
 m->hi1=lo(m,26u);target=sx(UINT32_C(0x80003830));goto dispatch;
L_80003830:
 STEP(UINT32_C(0x80003830)); /* dfba01b0 ld k0,0x1b0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001b0),&value64,8u);set(m,26u,value64);target=sx(UINT32_C(0x80003834));goto dispatch;
L_80003834:
 STEP(UINT32_C(0x80003834)); /* 03400013 mtlo k0 */
 m->lo=lo(m,26u);target=sx(UINT32_C(0x80003838));goto dispatch;
L_80003838:
 STEP(UINT32_C(0x80003838)); /* dfba01b8 ld k0,0x1b8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000001b8),&value64,8u);set(m,26u,value64);target=sx(UINT32_C(0x8000383c));goto dispatch;
L_8000383c:
 STEP(UINT32_C(0x8000383c)); /* 73400013 mmi 73400013 */
 m->lo1=lo(m,26u);target=sx(UINT32_C(0x80003840));goto dispatch;
L_80003840:
 STEP(UINT32_C(0x80003840)); /* 7ba10010 lq at,0x10(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),q,16u);memcpy(m->gpr[1],q,16u);}target=sx(UINT32_C(0x80003844));goto dispatch;
L_80003844:
 STEP(UINT32_C(0x80003844)); /* 7ba20020 lq v0,0x20(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x80003848));goto dispatch;
L_80003848:
 STEP(UINT32_C(0x80003848)); /* 7ba30030 lq v1,0x30(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x8000384c));goto dispatch;
L_8000384c:
 STEP(UINT32_C(0x8000384c)); /* 7ba40040 lq a0,0x40(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),q,16u);memcpy(m->gpr[4],q,16u);}target=sx(UINT32_C(0x80003850));goto dispatch;
L_80003850:
 STEP(UINT32_C(0x80003850)); /* 7ba50050 lq a1,0x50(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),q,16u);memcpy(m->gpr[5],q,16u);}target=sx(UINT32_C(0x80003854));goto dispatch;
L_80003854:
 STEP(UINT32_C(0x80003854)); /* 7ba60060 lq a2,0x60(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),q,16u);memcpy(m->gpr[6],q,16u);}target=sx(UINT32_C(0x80003858));goto dispatch;
L_80003858:
 STEP(UINT32_C(0x80003858)); /* 7ba70070 lq a3,0x70(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),q,16u);memcpy(m->gpr[7],q,16u);}target=sx(UINT32_C(0x8000385c));goto dispatch;
L_8000385c:
 STEP(UINT32_C(0x8000385c)); /* 7ba80080 lq t0,0x80(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),q,16u);memcpy(m->gpr[8],q,16u);}target=sx(UINT32_C(0x80003860));goto dispatch;
L_80003860:
 STEP(UINT32_C(0x80003860)); /* 7ba90090 lq t1,0x90(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),q,16u);memcpy(m->gpr[9],q,16u);}target=sx(UINT32_C(0x80003864));goto dispatch;
L_80003864:
 STEP(UINT32_C(0x80003864)); /* 7baa00a0 lq t2,0xa0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),q,16u);memcpy(m->gpr[10],q,16u);}target=sx(UINT32_C(0x80003868));goto dispatch;
L_80003868:
 STEP(UINT32_C(0x80003868)); /* 7bab00b0 lq t3,0xb0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000000b0),q,16u);memcpy(m->gpr[11],q,16u);}target=sx(UINT32_C(0x8000386c));goto dispatch;
L_8000386c:
 STEP(UINT32_C(0x8000386c)); /* 7bac00c0 lq t4,0xc0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000000c0),q,16u);memcpy(m->gpr[12],q,16u);}target=sx(UINT32_C(0x80003870));goto dispatch;
L_80003870:
 STEP(UINT32_C(0x80003870)); /* 7bad00d0 lq t5,0xd0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000000d0),q,16u);memcpy(m->gpr[13],q,16u);}target=sx(UINT32_C(0x80003874));goto dispatch;
L_80003874:
 STEP(UINT32_C(0x80003874)); /* 7bae00e0 lq t6,0xe0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000000e0),q,16u);memcpy(m->gpr[14],q,16u);}target=sx(UINT32_C(0x80003878));goto dispatch;
L_80003878:
 STEP(UINT32_C(0x80003878)); /* 7baf00f0 lq t7,0xf0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000000f0),q,16u);memcpy(m->gpr[15],q,16u);}target=sx(UINT32_C(0x8000387c));goto dispatch;
L_8000387c:
 STEP(UINT32_C(0x8000387c)); /* 7bb00100 lq s0,0x100(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000100),q,16u);memcpy(m->gpr[16],q,16u);}target=sx(UINT32_C(0x80003880));goto dispatch;
L_80003880:
 STEP(UINT32_C(0x80003880)); /* 7bb10110 lq s1,0x110(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000110),q,16u);memcpy(m->gpr[17],q,16u);}target=sx(UINT32_C(0x80003884));goto dispatch;
L_80003884:
 STEP(UINT32_C(0x80003884)); /* 7bb20120 lq s2,0x120(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000120),q,16u);memcpy(m->gpr[18],q,16u);}target=sx(UINT32_C(0x80003888));goto dispatch;
L_80003888:
 STEP(UINT32_C(0x80003888)); /* 7bb30130 lq s3,0x130(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000130),q,16u);memcpy(m->gpr[19],q,16u);}target=sx(UINT32_C(0x8000388c));goto dispatch;
L_8000388c:
 STEP(UINT32_C(0x8000388c)); /* 7bb40140 lq s4,0x140(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000140),q,16u);memcpy(m->gpr[20],q,16u);}target=sx(UINT32_C(0x80003890));goto dispatch;
L_80003890:
 STEP(UINT32_C(0x80003890)); /* 7bb50150 lq s5,0x150(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000150),q,16u);memcpy(m->gpr[21],q,16u);}target=sx(UINT32_C(0x80003894));goto dispatch;
L_80003894:
 STEP(UINT32_C(0x80003894)); /* 7bb60160 lq s6,0x160(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000160),q,16u);memcpy(m->gpr[22],q,16u);}target=sx(UINT32_C(0x80003898));goto dispatch;
L_80003898:
 STEP(UINT32_C(0x80003898)); /* 7bb70170 lq s7,0x170(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000170),q,16u);memcpy(m->gpr[23],q,16u);}target=sx(UINT32_C(0x8000389c));goto dispatch;
L_8000389c:
 STEP(UINT32_C(0x8000389c)); /* 7bb80180 lq t8,0x180(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000180),q,16u);memcpy(m->gpr[24],q,16u);}target=sx(UINT32_C(0x800038a0));goto dispatch;
L_800038a0:
 STEP(UINT32_C(0x800038a0)); /* 7bb90190 lq t9,0x190(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x00000190),q,16u);memcpy(m->gpr[25],q,16u);}target=sx(UINT32_C(0x800038a4));goto dispatch;
L_800038a4:
 STEP(UINT32_C(0x800038a4)); /* 7bbc01c0 lq gp,0x1c0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000001c0),q,16u);memcpy(m->gpr[28],q,16u);}target=sx(UINT32_C(0x800038a8));goto dispatch;
L_800038a8:
 STEP(UINT32_C(0x800038a8)); /* 7bbe01e0 lq s8,0x1e0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000001e0),q,16u);memcpy(m->gpr[30],q,16u);}target=sx(UINT32_C(0x800038ac));goto dispatch;
L_800038ac:
 STEP(UINT32_C(0x800038ac)); /* c7a00200 lwc1 f0,0x200(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000200),&value32,4u);m->fpr[0]=value32;target=sx(UINT32_C(0x800038b0));goto dispatch;
L_800038b0:
 STEP(UINT32_C(0x800038b0)); /* c7a10204 lwc1 f1,0x204(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000204),&value32,4u);m->fpr[1]=value32;target=sx(UINT32_C(0x800038b4));goto dispatch;
L_800038b4:
 STEP(UINT32_C(0x800038b4)); /* c7a20208 lwc1 f2,0x208(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000208),&value32,4u);m->fpr[2]=value32;target=sx(UINT32_C(0x800038b8));goto dispatch;
L_800038b8:
 STEP(UINT32_C(0x800038b8)); /* c7a3020c lwc1 f3,0x20c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000020c),&value32,4u);m->fpr[3]=value32;target=sx(UINT32_C(0x800038bc));goto dispatch;
L_800038bc:
 STEP(UINT32_C(0x800038bc)); /* c7a40210 lwc1 f4,0x210(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000210),&value32,4u);m->fpr[4]=value32;target=sx(UINT32_C(0x800038c0));goto dispatch;
L_800038c0:
 STEP(UINT32_C(0x800038c0)); /* c7a50214 lwc1 f5,0x214(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000214),&value32,4u);m->fpr[5]=value32;target=sx(UINT32_C(0x800038c4));goto dispatch;
L_800038c4:
 STEP(UINT32_C(0x800038c4)); /* c7a60218 lwc1 f6,0x218(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000218),&value32,4u);m->fpr[6]=value32;target=sx(UINT32_C(0x800038c8));goto dispatch;
L_800038c8:
 STEP(UINT32_C(0x800038c8)); /* c7a7021c lwc1 f7,0x21c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000021c),&value32,4u);m->fpr[7]=value32;target=sx(UINT32_C(0x800038cc));goto dispatch;
L_800038cc:
 STEP(UINT32_C(0x800038cc)); /* c7a80220 lwc1 f8,0x220(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000220),&value32,4u);m->fpr[8]=value32;target=sx(UINT32_C(0x800038d0));goto dispatch;
L_800038d0:
 STEP(UINT32_C(0x800038d0)); /* c7a90224 lwc1 f9,0x224(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000224),&value32,4u);m->fpr[9]=value32;target=sx(UINT32_C(0x800038d4));goto dispatch;
L_800038d4:
 STEP(UINT32_C(0x800038d4)); /* c7aa0228 lwc1 f10,0x228(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000228),&value32,4u);m->fpr[10]=value32;target=sx(UINT32_C(0x800038d8));goto dispatch;
L_800038d8:
 STEP(UINT32_C(0x800038d8)); /* c7ab022c lwc1 f11,0x22c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000022c),&value32,4u);m->fpr[11]=value32;target=sx(UINT32_C(0x800038dc));goto dispatch;
L_800038dc:
 STEP(UINT32_C(0x800038dc)); /* c7ac0230 lwc1 f12,0x230(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000230),&value32,4u);m->fpr[12]=value32;target=sx(UINT32_C(0x800038e0));goto dispatch;
L_800038e0:
 STEP(UINT32_C(0x800038e0)); /* c7ad0234 lwc1 f13,0x234(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000234),&value32,4u);m->fpr[13]=value32;target=sx(UINT32_C(0x800038e4));goto dispatch;
L_800038e4:
 STEP(UINT32_C(0x800038e4)); /* c7ae0238 lwc1 f14,0x238(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000238),&value32,4u);m->fpr[14]=value32;target=sx(UINT32_C(0x800038e8));goto dispatch;
L_800038e8:
 STEP(UINT32_C(0x800038e8)); /* c7af023c lwc1 f15,0x23c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000023c),&value32,4u);m->fpr[15]=value32;target=sx(UINT32_C(0x800038ec));goto dispatch;
L_800038ec:
 STEP(UINT32_C(0x800038ec)); /* c7b00240 lwc1 f16,0x240(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000240),&value32,4u);m->fpr[16]=value32;target=sx(UINT32_C(0x800038f0));goto dispatch;
L_800038f0:
 STEP(UINT32_C(0x800038f0)); /* c7b10244 lwc1 f17,0x244(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000244),&value32,4u);m->fpr[17]=value32;target=sx(UINT32_C(0x800038f4));goto dispatch;
L_800038f4:
 STEP(UINT32_C(0x800038f4)); /* c7b20248 lwc1 f18,0x248(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000248),&value32,4u);m->fpr[18]=value32;target=sx(UINT32_C(0x800038f8));goto dispatch;
L_800038f8:
 STEP(UINT32_C(0x800038f8)); /* c7b3024c lwc1 f19,0x24c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000024c),&value32,4u);m->fpr[19]=value32;target=sx(UINT32_C(0x800038fc));goto dispatch;
L_800038fc:
 STEP(UINT32_C(0x800038fc)); /* c7b40250 lwc1 f20,0x250(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000250),&value32,4u);m->fpr[20]=value32;target=sx(UINT32_C(0x80003900));goto dispatch;
L_80003900:
 STEP(UINT32_C(0x80003900)); /* c7b50254 lwc1 f21,0x254(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000254),&value32,4u);m->fpr[21]=value32;target=sx(UINT32_C(0x80003904));goto dispatch;
L_80003904:
 STEP(UINT32_C(0x80003904)); /* c7b60258 lwc1 f22,0x258(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000258),&value32,4u);m->fpr[22]=value32;target=sx(UINT32_C(0x80003908));goto dispatch;
L_80003908:
 STEP(UINT32_C(0x80003908)); /* c7b7025c lwc1 f23,0x25c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000025c),&value32,4u);m->fpr[23]=value32;target=sx(UINT32_C(0x8000390c));goto dispatch;
L_8000390c:
 STEP(UINT32_C(0x8000390c)); /* c7b80260 lwc1 f24,0x260(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000260),&value32,4u);m->fpr[24]=value32;target=sx(UINT32_C(0x80003910));goto dispatch;
L_80003910:
 STEP(UINT32_C(0x80003910)); /* c7b90264 lwc1 f25,0x264(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000264),&value32,4u);m->fpr[25]=value32;target=sx(UINT32_C(0x80003914));goto dispatch;
L_80003914:
 STEP(UINT32_C(0x80003914)); /* c7ba0268 lwc1 f26,0x268(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000268),&value32,4u);m->fpr[26]=value32;target=sx(UINT32_C(0x80003918));goto dispatch;
L_80003918:
 STEP(UINT32_C(0x80003918)); /* c7bb026c lwc1 f27,0x26c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000026c),&value32,4u);m->fpr[27]=value32;target=sx(UINT32_C(0x8000391c));goto dispatch;
L_8000391c:
 STEP(UINT32_C(0x8000391c)); /* c7bc0270 lwc1 f28,0x270(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000270),&value32,4u);m->fpr[28]=value32;target=sx(UINT32_C(0x80003920));goto dispatch;
L_80003920:
 STEP(UINT32_C(0x80003920)); /* c7bd0274 lwc1 f29,0x274(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000274),&value32,4u);m->fpr[29]=value32;target=sx(UINT32_C(0x80003924));goto dispatch;
L_80003924:
 STEP(UINT32_C(0x80003924)); /* c7be0278 lwc1 f30,0x278(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000278),&value32,4u);m->fpr[30]=value32;target=sx(UINT32_C(0x80003928));goto dispatch;
L_80003928:
 STEP(UINT32_C(0x80003928)); /* c7bf027c lwc1 f31,0x27c(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000027c),&value32,4u);m->fpr[31]=value32;target=sx(UINT32_C(0x8000392c));goto dispatch;
L_8000392c:
 STEP(UINT32_C(0x8000392c)); /* 03e0d02d daddu k0,ra,zero */
 set(m,26u,lo(m,31u)+lo(m,0u));target=sx(UINT32_C(0x80003930));goto dispatch;
L_80003930:
 STEP(UINT32_C(0x80003930)); /* 7bbf01f0 lq ra,0x1f0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000001f0),q,16u);memcpy(m->gpr[31],q,16u);}target=sx(UINT32_C(0x80003934));goto dispatch;
L_80003934:
 STEP(UINT32_C(0x80003934)); /* 03400008 jr k0 */
 target=sx((uint32_t)lo(m,26u));STEP(UINT32_C(0x80003938));{uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d0),q,16u);memcpy(m->gpr[29],q,16u);}goto dispatch;
L_80003938:
 STEP(UINT32_C(0x80003938)); /* 7bbd01d0 lq sp,0x1d0(sp) */
 {uint32_t q[4];READ((uint32_t)lo(m,29u)+UINT32_C(0x000001d0),q,16u);memcpy(m->gpr[29],q,16u);}target=sx(UINT32_C(0x8000393c));goto dispatch;
L_800046b0:
 STEP(UINT32_C(0x800046b0)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x800046b4));goto dispatch;
L_800046b4:
 STEP(UINT32_C(0x800046b4)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x800046b8));goto dispatch;
L_800046b8:
 STEP(UINT32_C(0x800046b8)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x800046bc));goto dispatch;
L_800046bc:
 STEP(UINT32_C(0x800046bc)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x800046c0));goto dispatch;
L_800046c0:
 STEP(UINT32_C(0x800046c0)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x800046c4));goto dispatch;
L_800046c4:
 STEP(UINT32_C(0x800046c4)); /* 2e220100 sltiu v0,s1,256 */
 set(m,2u,(lo(m,17u)<UINT64_C(0x100)));target=sx(UINT32_C(0x800046c8));goto dispatch;
L_800046c8:
 STEP(UINT32_C(0x800046c8)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x800046cc));goto dispatch;
L_800046cc:
 STEP(UINT32_C(0x800046cc)); /* 10400045 beq v0,zero,800047e4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x800046d0));value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(taken?UINT32_C(0x800047e4):UINT32_C(0x800046d4));goto dispatch;}
L_800046d0:
 STEP(UINT32_C(0x800046d0)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x800046d4));goto dispatch;
L_800046d4:
 STEP(UINT32_C(0x800046d4)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800046d8));goto dispatch;
L_800046d8:
 STEP(UINT32_C(0x800046d8)); /* 8c4225ec lw v0,0x25ec(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x000025ec),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800046dc));goto dispatch;
L_800046dc:
 STEP(UINT32_C(0x800046dc)); /* 2403004c addiu v1,zero,76 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x800046e0));goto dispatch;
L_800046e0:
 STEP(UINT32_C(0x800046e0)); /* 3c078001 lui a3,zero,0x8001 */
 set(m,7u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800046e4));goto dispatch;
L_800046e4:
 STEP(UINT32_C(0x800046e4)); /* 24e77408 addiu a3,a3,29704 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00007408)));target=sx(UINT32_C(0x800046e8));goto dispatch;
L_800046e8:
 STEP(UINT32_C(0x800046e8)); /* 24040004 addiu a0,zero,4 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x800046ec));goto dispatch;
L_800046ec:
 STEP(UINT32_C(0x800046ec)); /* 0051880a movz s1,v0,s1 */
 if(lo(m,17u)==0u)set(m,17u,lo(m,2u));target=sx(UINT32_C(0x800046f0));goto dispatch;
L_800046f0:
 STEP(UINT32_C(0x800046f0)); /* 02233018 mult_rd a2,s1,v1 */
 {int64_t product;if(lo(m,17u)!=sx((uint32_t)lo(m,17u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,17u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,6u,m->lo);}target=sx(UINT32_C(0x800046f4));goto dispatch;
L_800046f4:
 STEP(UINT32_C(0x800046f4)); /* 00c74021 addu t0,a2,a3 */
 set(m,8u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,7u)));target=sx(UINT32_C(0x800046f8));goto dispatch;
L_800046f8:
 STEP(UINT32_C(0x800046f8)); /* 8d030000 lw v1,0x0(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x800046fc));goto dispatch;
L_800046fc:
 STEP(UINT32_C(0x800046fc)); /* 1064000e beq v1,a0,80004738 */
 {int taken=(lo(m,3u)==lo(m,4u));STEP(UINT32_C(0x80004700));set(m,2u,(lo(m,3u)<UINT64_C(0x5)));target=sx(taken?UINT32_C(0x80004738):UINT32_C(0x80004704));goto dispatch;}
L_80004700:
 STEP(UINT32_C(0x80004700)); /* 2c620005 sltiu v0,v1,5 */
 set(m,2u,(lo(m,3u)<UINT64_C(0x5)));target=sx(UINT32_C(0x80004704));goto dispatch;
L_80004704:
 STEP(UINT32_C(0x80004704)); /* 10400005 beq v0,zero,8000471c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80004708));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(taken?UINT32_C(0x8000471c):UINT32_C(0x8000470c));goto dispatch;}
L_80004708:
 STEP(UINT32_C(0x80004708)); /* 24020002 addiu v0,zero,2 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x8000470c));goto dispatch;
L_8000470c:
 STEP(UINT32_C(0x8000470c)); /* 1062001e beq v1,v0,80004788 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x80004710));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80004788):UINT32_C(0x80004714));goto dispatch;}
L_80004710:
 STEP(UINT32_C(0x80004710)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004714));goto dispatch;
L_80004714:
 STEP(UINT32_C(0x80004714)); /* 10000035 beq zero,zero,800047ec */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004718));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x800047ec):UINT32_C(0x8000471c));goto dispatch;}
L_80004718:
 STEP(UINT32_C(0x80004718)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x8000471c));goto dispatch;
L_8000471c:
 STEP(UINT32_C(0x8000471c)); /* 24090008 addiu t1,zero,8 */
 set(m,9u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x80004720));goto dispatch;
L_80004720:
 STEP(UINT32_C(0x80004720)); /* 10690019 beq v1,t1,80004788 */
 {int taken=(lo(m,3u)==lo(m,9u));STEP(UINT32_C(0x80004724));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(taken?UINT32_C(0x80004788):UINT32_C(0x80004728));goto dispatch;}
L_80004724:
 STEP(UINT32_C(0x80004724)); /* 2402000c addiu v0,zero,12 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000c)));target=sx(UINT32_C(0x80004728));goto dispatch;
L_80004728:
 STEP(UINT32_C(0x80004728)); /* 1062001e beq v1,v0,800047a4 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x8000472c));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x800047a4):UINT32_C(0x80004730));goto dispatch;}
L_8000472c:
 STEP(UINT32_C(0x8000472c)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004730));goto dispatch;
L_80004730:
 STEP(UINT32_C(0x80004730)); /* 1000002e beq zero,zero,800047ec */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004734));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(taken?UINT32_C(0x800047ec):UINT32_C(0x80004738));goto dispatch;}
L_80004734:
 STEP(UINT32_C(0x80004734)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80004738));goto dispatch;
L_80004738:
 STEP(UINT32_C(0x80004738)); /* 24e20014 addiu v0,a3,20 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x8000473c));goto dispatch;
L_8000473c:
 STEP(UINT32_C(0x8000473c)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80004740));goto dispatch;
L_80004740:
 STEP(UINT32_C(0x80004740)); /* 00c29821 addu s3,a2,v0 */
 set(m,19u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80004744));goto dispatch;
L_80004744:
 STEP(UINT32_C(0x80004744)); /* 8e720000 lw s2,0x0(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);set(m,18u,sx(value32));target=sx(UINT32_C(0x80004748));goto dispatch;
L_80004748:
 STEP(UINT32_C(0x80004748)); /* 16430020 bne s2,v1,800047cc */
 {int taken=(lo(m,18u)!=lo(m,3u));STEP(UINT32_C(0x8000474c));set(m,4u,sx((uint32_t)lo(m,7u)+UINT32_C(0x0000001c)));target=sx(taken?UINT32_C(0x800047cc):UINT32_C(0x80004750));goto dispatch;}
L_8000474c:
 STEP(UINT32_C(0x8000474c)); /* 24e4001c addiu a0,a3,28 */
 set(m,4u,sx((uint32_t)lo(m,7u)+UINT32_C(0x0000001c)));target=sx(UINT32_C(0x80004750));goto dispatch;
L_80004750:
 STEP(UINT32_C(0x80004750)); /* 3c108001 lui s0,zero,0x8001 */
 set(m,16u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004754));goto dispatch;
L_80004754:
 STEP(UINT32_C(0x80004754)); /* 8e1025f0 lw s0,0x25f0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x000025f0),&value32,4u);set(m,16u,sx(value32));target=sx(UINT32_C(0x80004758));goto dispatch;
L_80004758:
 STEP(UINT32_C(0x80004758)); /* 0c00166e jal 800059b8 */
 set(m,31u,UINT64_C(0x80004760));STEP(UINT32_C(0x8000475c));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x800059b8));goto dispatch;
L_8000475c:
 STEP(UINT32_C(0x8000475c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x80004760));goto dispatch;
L_80004760:
 STEP(UINT32_C(0x80004760)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004764));goto dispatch;
L_80004764:
 STEP(UINT32_C(0x80004764)); /* 8c4225f0 lw v0,0x25f0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x000025f0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004768));goto dispatch;
L_80004768:
 STEP(UINT32_C(0x80004768)); /* 0050102a slt v0,v0,s0 */
 set(m,2u,((int64_t)lo(m,2u)<(int64_t)lo(m,16u)));target=sx(UINT32_C(0x8000476c));goto dispatch;
L_8000476c:
 STEP(UINT32_C(0x8000476c)); /* 50400004 beql v0,zero,80004780 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x80004770));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004780));}else target=sx(UINT32_C(0x80004774));goto dispatch;
L_80004770:
 STEP(UINT32_C(0x80004770)); /* ae600000 sw zero,0x0(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004774));goto dispatch;
L_80004774:
 STEP(UINT32_C(0x80004774)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004778));goto dispatch;
L_80004778:
 STEP(UINT32_C(0x80004778)); /* ac3225f4 sw s2,0x25f4(at) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000025f4),&value32,4u);target=sx(UINT32_C(0x8000477c));goto dispatch;
L_8000477c:
 STEP(UINT32_C(0x8000477c)); /* ae600000 sw zero,0x0(s3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,19u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004780));goto dispatch;
L_80004780:
 STEP(UINT32_C(0x80004780)); /* 10000019 beq zero,zero,800047e8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004784));set(m,2u,lo(m,17u)+lo(m,0u));target=sx(taken?UINT32_C(0x800047e8):UINT32_C(0x80004788));goto dispatch;}
L_80004784:
 STEP(UINT32_C(0x80004784)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x80004788));goto dispatch;
L_80004788:
 STEP(UINT32_C(0x80004788)); /* 2404004c addiu a0,zero,76 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x8000478c));goto dispatch;
L_8000478c:
 STEP(UINT32_C(0x8000478c)); /* 3c058001 lui a1,zero,0x8001 */
 set(m,5u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004790));goto dispatch;
L_80004790:
 STEP(UINT32_C(0x80004790)); /* 24a57424 addiu a1,a1,29732 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00007424)));target=sx(UINT32_C(0x80004794));goto dispatch;
L_80004794:
 STEP(UINT32_C(0x80004794)); /* 02242018 mult_rd a0,s1,a0 */
 {int64_t product;if(lo(m,17u)!=sx((uint32_t)lo(m,17u))||lo(m,4u)!=sx((uint32_t)lo(m,4u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,17u)*(int64_t)(int32_t)lo(m,4u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x80004798));goto dispatch;
L_80004798:
 STEP(UINT32_C(0x80004798)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x8000479c));goto dispatch;
L_8000479c:
 STEP(UINT32_C(0x8000479c)); /* 1000000d beq zero,zero,800047d4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800047a0));set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=sx(taken?UINT32_C(0x800047d4):UINT32_C(0x800047a4));goto dispatch;}
L_800047a0:
 STEP(UINT32_C(0x800047a0)); /* 00852021 addu a0,a0,a1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=sx(UINT32_C(0x800047a4));goto dispatch;
L_800047a4:
 STEP(UINT32_C(0x800047a4)); /* 24e20014 addiu v0,a3,20 */
 set(m,2u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x800047a8));goto dispatch;
L_800047a8:
 STEP(UINT32_C(0x800047a8)); /* 24040001 addiu a0,zero,1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800047ac));goto dispatch;
L_800047ac:
 STEP(UINT32_C(0x800047ac)); /* 00c22821 addu a1,a2,v0 */
 set(m,5u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x800047b0));goto dispatch;
L_800047b0:
 STEP(UINT32_C(0x800047b0)); /* 8ca30000 lw v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x800047b4));goto dispatch;
L_800047b4:
 STEP(UINT32_C(0x800047b4)); /* 14640005 bne v1,a0,800047cc */
 {int taken=(lo(m,3u)!=lo(m,4u));STEP(UINT32_C(0x800047b8));set(m,4u,sx((uint32_t)lo(m,7u)+UINT32_C(0x0000001c)));target=sx(taken?UINT32_C(0x800047cc):UINT32_C(0x800047bc));goto dispatch;}
L_800047b8:
 STEP(UINT32_C(0x800047b8)); /* 24e4001c addiu a0,a3,28 */
 set(m,4u,sx((uint32_t)lo(m,7u)+UINT32_C(0x0000001c)));target=sx(UINT32_C(0x800047bc));goto dispatch;
L_800047bc:
 STEP(UINT32_C(0x800047bc)); /* ad090000 sw t1,0x0(t0) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,8u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800047c0));goto dispatch;
L_800047c0:
 STEP(UINT32_C(0x800047c0)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x800047c4));goto dispatch;
L_800047c4:
 STEP(UINT32_C(0x800047c4)); /* 10000008 beq zero,zero,800047e8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800047c8));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x800047e8):UINT32_C(0x800047cc));goto dispatch;}
L_800047c8:
 STEP(UINT32_C(0x800047c8)); /* aca00000 sw zero,0x0(a1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800047cc));goto dispatch;
L_800047cc:
 STEP(UINT32_C(0x800047cc)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x800047d0));goto dispatch;
L_800047d0:
 STEP(UINT32_C(0x800047d0)); /* 00c42021 addu a0,a2,a0 */
 set(m,4u,sx((uint32_t)lo(m,6u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x800047d4));goto dispatch;
L_800047d4:
 STEP(UINT32_C(0x800047d4)); /* 8c830000 lw v1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x800047d8));goto dispatch;
L_800047d8:
 STEP(UINT32_C(0x800047d8)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x800047dc));goto dispatch;
L_800047dc:
 STEP(UINT32_C(0x800047dc)); /* 10000002 beq zero,zero,800047e8 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800047e0));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x800047e8):UINT32_C(0x800047e4));goto dispatch;}
L_800047e0:
 STEP(UINT32_C(0x800047e0)); /* ac830000 sw v1,0x0(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800047e4));goto dispatch;
L_800047e4:
 STEP(UINT32_C(0x800047e4)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x800047e8));goto dispatch;
L_800047e8:
 STEP(UINT32_C(0x800047e8)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x800047ec));goto dispatch;
L_800047ec:
 STEP(UINT32_C(0x800047ec)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x800047f0));goto dispatch;
L_800047f0:
 STEP(UINT32_C(0x800047f0)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x800047f4));goto dispatch;
L_800047f4:
 STEP(UINT32_C(0x800047f4)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x800047f8));goto dispatch;
L_800047f8:
 STEP(UINT32_C(0x800047f8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x800047fc));goto dispatch;
L_800047fc:
 STEP(UINT32_C(0x800047fc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004800));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_80004800:
 STEP(UINT32_C(0x80004800)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x80004804));goto dispatch;
L_800059b8:
 STEP(UINT32_C(0x800059b8)); /* 2402004c addiu v0,zero,76 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x800059bc));goto dispatch;
L_800059bc:
 STEP(UINT32_C(0x800059bc)); /* 24050002 addiu a1,zero,2 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x800059c0));goto dispatch;
L_800059c0:
 STEP(UINT32_C(0x800059c0)); /* 00822018 mult_rd a0,a0,v0 */
 {int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=sx(UINT32_C(0x800059c4));goto dispatch;
L_800059c4:
 STEP(UINT32_C(0x800059c4)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800059c8));goto dispatch;
L_800059c8:
 STEP(UINT32_C(0x800059c8)); /* 24637400 addiu v1,v1,29696 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00007400)));target=sx(UINT32_C(0x800059cc));goto dispatch;
L_800059cc:
 STEP(UINT32_C(0x800059cc)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800059d0));goto dispatch;
L_800059d0:
 STEP(UINT32_C(0x800059d0)); /* 8c4225f0 lw v0,0x25f0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x000025f0),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800059d4));goto dispatch;
L_800059d4:
 STEP(UINT32_C(0x800059d4)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800059d8));goto dispatch;
L_800059d8:
 STEP(UINT32_C(0x800059d8)); /* 00240821 addu at,at,a0 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x800059dc));goto dispatch;
L_800059dc:
 STEP(UINT32_C(0x800059dc)); /* ac257408 sw a1,0x7408(at) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x00007408),&value32,4u);target=sx(UINT32_C(0x800059e0));goto dispatch;
L_800059e0:
 STEP(UINT32_C(0x800059e0)); /* 00833021 addu a2,a0,v1 */
 set(m,6u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x800059e4));goto dispatch;
L_800059e4:
 STEP(UINT32_C(0x800059e4)); /* 84c3001a lh v1,0x1a(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x0000001a),&value16,2u);set(m,3u,sx((uint32_t)(int32_t)(int16_t)value16));target=sx(UINT32_C(0x800059e8));goto dispatch;
L_800059e8:
 STEP(UINT32_C(0x800059e8)); /* 0062102a slt v0,v1,v0 */
 set(m,2u,((int64_t)lo(m,3u)<(int64_t)lo(m,2u)));target=sx(UINT32_C(0x800059ec));goto dispatch;
L_800059ec:
 STEP(UINT32_C(0x800059ec)); /* 10400003 beq v0,zero,800059fc */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x800059f0));set(m,2u,sx((uint32_t)lo(m,3u)<<3u));target=sx(taken?UINT32_C(0x800059fc):UINT32_C(0x800059f4));goto dispatch;}
L_800059f0:
 STEP(UINT32_C(0x800059f0)); /* 000310c0 sll v0,v1,3 */
 set(m,2u,sx((uint32_t)lo(m,3u)<<3u));target=sx(UINT32_C(0x800059f4));goto dispatch;
L_800059f4:
 STEP(UINT32_C(0x800059f4)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800059f8));goto dispatch;
L_800059f8:
 STEP(UINT32_C(0x800059f8)); /* ac2325f0 sw v1,0x25f0(at) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000025f0),&value32,4u);target=sx(UINT32_C(0x800059fc));goto dispatch;
L_800059fc:
 STEP(UINT32_C(0x800059fc)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80005a00));goto dispatch;
L_80005a00:
 STEP(UINT32_C(0x80005a00)); /* 24846ff0 addiu a0,a0,28656 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00006ff0)));target=sx(UINT32_C(0x80005a04));goto dispatch;
L_80005a04:
 STEP(UINT32_C(0x80005a04)); /* 00442021 addu a0,v0,a0 */
 set(m,4u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80005a08));goto dispatch;
L_80005a08:
 STEP(UINT32_C(0x80005a08)); /* 080016c2 j 80005b08 */
 STEP(UINT32_C(0x80005a0c));set(m,5u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x80005b08));goto dispatch;
L_80005a0c:
 STEP(UINT32_C(0x80005a0c)); /* 00c0282d daddu a1,a2,zero */
 set(m,5u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x80005a10));goto dispatch;
L_80005b08:
 STEP(UINT32_C(0x80005b08)); /* 8c830000 lw v1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80005b0c));goto dispatch;
L_80005b0c:
 STEP(UINT32_C(0x80005b0c)); /* aca40004 sw a0,0x4(a1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80005b10));goto dispatch;
L_80005b10:
 STEP(UINT32_C(0x80005b10)); /* aca30000 sw v1,0x0(a1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80005b14));goto dispatch;
L_80005b14:
 STEP(UINT32_C(0x80005b14)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005b18));goto dispatch;
L_80005b18:
 STEP(UINT32_C(0x80005b18)); /* ac450004 sw a1,0x4(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80005b1c));goto dispatch;
L_80005b1c:
 STEP(UINT32_C(0x80005b1c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80005b20));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_80005b20:
 STEP(UINT32_C(0x80005b20)); /* ac850000 sw a1,0x0(a0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80005b24));goto dispatch;
L_80004548:
 STEP(UINT32_C(0x80004548)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000454c));goto dispatch;
L_8000454c:
 STEP(UINT32_C(0x8000454c)); /* 8c4225ec lw v0,0x25ec(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x000025ec),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004550));goto dispatch;
L_80004550:
 STEP(UINT32_C(0x80004550)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004554));/* nop */goto dispatch;
L_80004554:
 STEP(UINT32_C(0x80004554)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80004558));goto dispatch;
L_80004970:
 STEP(UINT32_C(0x80004970)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x80004974));goto dispatch;
L_80004974:
 STEP(UINT32_C(0x80004974)); /* 2ca20100 sltiu v0,a1,256 */
 set(m,2u,(lo(m,5u)<UINT64_C(0x100)));target=sx(UINT32_C(0x80004978));goto dispatch;
L_80004978:
 STEP(UINT32_C(0x80004978)); /* 14400003 bne v0,zero,80004988 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8000497c));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(taken?UINT32_C(0x80004988):UINT32_C(0x80004980));goto dispatch;}
L_8000497c:
 STEP(UINT32_C(0x8000497c)); /* 2403004c addiu v1,zero,76 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x80004980));goto dispatch;
L_80004980:
 STEP(UINT32_C(0x80004980)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80004984));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));goto dispatch;
L_80004984:
 STEP(UINT32_C(0x80004984)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004988));goto dispatch;
L_80004988:
 STEP(UINT32_C(0x80004988)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000498c));goto dispatch;
L_8000498c:
 STEP(UINT32_C(0x8000498c)); /* 8c4225ec lw v0,0x25ec(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x000025ec),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80004990));goto dispatch;
L_80004990:
 STEP(UINT32_C(0x80004990)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80004994));goto dispatch;
L_80004994:
 STEP(UINT32_C(0x80004994)); /* 24847424 addiu a0,a0,29732 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00007424)));target=sx(UINT32_C(0x80004998));goto dispatch;
L_80004998:
 STEP(UINT32_C(0x80004998)); /* 0045280a movz a1,v0,a1 */
 if(lo(m,5u)==0u)set(m,5u,lo(m,2u));target=sx(UINT32_C(0x8000499c));goto dispatch;
L_8000499c:
 STEP(UINT32_C(0x8000499c)); /* 00a31818 mult_rd v1,a1,v1 */
 {int64_t product;if(lo(m,5u)!=sx((uint32_t)lo(m,5u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,5u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x800049a0));goto dispatch;
L_800049a0:
 STEP(UINT32_C(0x800049a0)); /* 00641821 addu v1,v1,a0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x800049a4));goto dispatch;
L_800049a4:
 STEP(UINT32_C(0x800049a4)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x800049a8));goto dispatch;
L_800049a8:
 STEP(UINT32_C(0x800049a8)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800049ac));value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);goto dispatch;
L_800049ac:
 STEP(UINT32_C(0x800049ac)); /* ac600000 sw zero,0x0(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x800049b0));goto dispatch;
L_800032c0:
 STEP(UINT32_C(0x800032c0)); /* 3c1a8001 lui k0,zero,0x8001 */
 set(m,26u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x800032c4));goto dispatch;
L_800032c4:
 STEP(UINT32_C(0x800032c4)); /* 8f5a25ec lw k0,0x25ec(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x000025ec),&value32,4u);set(m,26u,sx(value32));target=sx(UINT32_C(0x800032c8));goto dispatch;
L_800032c8:
 STEP(UINT32_C(0x800032c8)); /* 0c000da0 jal 80003680 */
 set(m,31u,UINT64_C(0x800032d0));STEP(UINT32_C(0x800032cc));set(m,2u,lo(m,26u)+lo(m,0u));target=sx(UINT32_C(0x80003680));goto dispatch;
L_800032cc:
 STEP(UINT32_C(0x800032cc)); /* 0340102d daddu v0,k0,zero */
 set(m,2u,lo(m,26u)+lo(m,0u));target=sx(UINT32_C(0x800032d0));goto dispatch;
L_800032d0:
 STEP(UINT32_C(0x800032d0)); /* 0c001196 jal 80004658 */
 set(m,31u,UINT64_C(0x800032d8));STEP(UINT32_C(0x800032d4));/* nop */target=sx(UINT32_C(0x80004658));goto dispatch;
L_800032d4:
 STEP(UINT32_C(0x800032d4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800032d8));goto dispatch;
L_800032d8:
 STEP(UINT32_C(0x800032d8)); /* 0440000a regimm0 v0,80003304 */
 {int taken=((int64_t)lo(m,2u)<0);STEP(UINT32_C(0x800032dc));/* nop */target=sx(taken?UINT32_C(0x80003304):UINT32_C(0x800032e0));goto dispatch;}
L_800032dc:
 STEP(UINT32_C(0x800032dc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800032e0));goto dispatch;
L_800032e0:
 STEP(UINT32_C(0x800032e0)); /* 3c1d8000 lui sp,zero,0x8000 */
 set(m,29u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x800032e4));goto dispatch;
L_800032e4:
 STEP(UINT32_C(0x800032e4)); /* 8fbd10c0 lw sp,0x10c0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000010c0),&value32,4u);set(m,29u,sx(value32));target=sx(UINT32_C(0x800032e8));goto dispatch;
L_800032e8:
 STEP(UINT32_C(0x800032e8)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x800032f0));STEP(UINT32_C(0x800032ec));value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80003800));goto dispatch;
L_800032ec:
 STEP(UINT32_C(0x800032ec)); /* ffa20020 sd v0,0x20(sp) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x800032f0));goto dispatch;
L_800032f0:
 STEP(UINT32_C(0x800032f0)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x800032f4));goto dispatch;
L_800032f4:
 STEP(UINT32_C(0x800032f4)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x800032f8));goto dispatch;
L_800032f8:
 STEP(UINT32_C(0x800032f8)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x800032fc));goto dispatch;
L_800032fc:
 STEP(UINT32_C(0x800032fc)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003300));goto dispatch;
L_80003300:
 STEP(UINT32_C(0x80003300)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80003304:
 STEP(UINT32_C(0x80003304)); /* 40047000 cop0 rs0 rta0 rd14 fn0 */
 set(m,4u,sx(m->epc));target=sx(UINT32_C(0x80003308));goto dispatch;
L_80003308:
 STEP(UINT32_C(0x80003308)); /* 3c058000 lui a1,zero,0x8000 */
 set(m,5u,sx(UINT32_C(0x80000000)));target=sx(UINT32_C(0x8000330c));goto dispatch;
L_8000330c:
 STEP(UINT32_C(0x8000330c)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80003310));goto dispatch;
L_80003310:
 STEP(UINT32_C(0x80003310)); /* 0c000e9e jal 80003a78 */
 set(m,31u,UINT64_C(0x80003318));STEP(UINT32_C(0x80003314));READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003a78));goto dispatch;
L_80003314:
 STEP(UINT32_C(0x80003314)); /* 8ca510c0 lw a1,0x10c0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x000010c0),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80003318));goto dispatch;
L_80003318:
 STEP(UINT32_C(0x80003318)); /* 40827000 cop0 rs4 rtv0 rd14 fn0 */
 m->epc=(uint32_t)lo(m,2u);target=sx(UINT32_C(0x8000331c));goto dispatch;
L_8000331c:
 STEP(UINT32_C(0x8000331c)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003320));goto dispatch;
L_80003320:
 STEP(UINT32_C(0x80003320)); /* 0c000e00 jal 80003800 */
 set(m,31u,UINT64_C(0x80003328));STEP(UINT32_C(0x80003324));set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003800));goto dispatch;
L_80003324:
 STEP(UINT32_C(0x80003324)); /* 0060e82d daddu sp,v1,zero */
 set(m,29u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003328));goto dispatch;
L_80003328:
 STEP(UINT32_C(0x80003328)); /* 401a6000 cop0 rs0 rtk0 rd12 fn0 */
 set(m,26u,sx(m->status));target=sx(UINT32_C(0x8000332c));goto dispatch;
L_8000332c:
 STEP(UINT32_C(0x8000332c)); /* 375a0013 ori k0,k0,0x13 */
 set(m,26u,lo(m,26u) | UINT64_C(0x13));target=sx(UINT32_C(0x80003330));goto dispatch;
L_80003330:
 STEP(UINT32_C(0x80003330)); /* 409a6000 cop0 rs4 rtk0 rd12 fn0 */
 m->status=(uint32_t)lo(m,26u);target=sx(UINT32_C(0x80003334));goto dispatch;
L_80003334:
 STEP(UINT32_C(0x80003334)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier, not a cache operation */target=sx(UINT32_C(0x80003338));goto dispatch;
L_80003338:
 STEP(UINT32_C(0x80003338)); /* 42000018 cop0 rs16 rtzero rd0 fn24 */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,sx(m->pc));m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_80004658:
 STEP(UINT32_C(0x80004658)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000465c));goto dispatch;
L_8000465c:
 STEP(UINT32_C(0x8000465c)); /* 8c8425ec lw a0,0x25ec(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x000025ec),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x80004660));goto dispatch;
L_80004660:
 STEP(UINT32_C(0x80004660)); /* 2402004c addiu v0,zero,76 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x80004664));goto dispatch;
L_80004664:
 STEP(UINT32_C(0x80004664)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x80004668));goto dispatch;
L_80004668:
 STEP(UINT32_C(0x80004668)); /* 3c038001 lui v1,zero,0x8001 */
 set(m,3u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000466c));goto dispatch;
L_8000466c:
 STEP(UINT32_C(0x8000466c)); /* 24637424 addiu v1,v1,29732 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00007424)));target=sx(UINT32_C(0x80004670));goto dispatch;
L_80004670:
 STEP(UINT32_C(0x80004670)); /* 00821018 mult_rd v0,a0,v0 */
 {int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=sx(UINT32_C(0x80004674));goto dispatch;
L_80004674:
 STEP(UINT32_C(0x80004674)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80004678));goto dispatch;
L_80004678:
 STEP(UINT32_C(0x80004678)); /* 00432821 addu a1,v0,v1 */
 set(m,5u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x8000467c));goto dispatch;
L_8000467c:
 STEP(UINT32_C(0x8000467c)); /* 8ca30000 lw v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80004680));goto dispatch;
L_80004680:
 STEP(UINT32_C(0x80004680)); /* 18600004 blez v1,zero,80004694 */
 {int taken=((int64_t)lo(m,3u)<=0);STEP(UINT32_C(0x80004684));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x80004694):UINT32_C(0x80004688));goto dispatch;}
L_80004684:
 STEP(UINT32_C(0x80004684)); /* 2463ffff addiu v1,v1,-1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80004688));goto dispatch;
L_80004688:
 STEP(UINT32_C(0x80004688)); /* 0080102d daddu v0,a0,zero */
 set(m,2u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x8000468c));goto dispatch;
L_8000468c:
 STEP(UINT32_C(0x8000468c)); /* 10000004 beq zero,zero,800046a0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80004690));value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(taken?UINT32_C(0x800046a0):UINT32_C(0x80004694));goto dispatch;}
L_80004690:
 STEP(UINT32_C(0x80004690)); /* aca30000 sw v1,0x0(a1) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80004694));goto dispatch;
L_80004694:
 STEP(UINT32_C(0x80004694)); /* 0c00165e jal 80005978 */
 set(m,31u,UINT64_C(0x8000469c));STEP(UINT32_C(0x80004698));/* nop */target=sx(UINT32_C(0x80005978));goto dispatch;
L_80004698:
 STEP(UINT32_C(0x80004698)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x8000469c));goto dispatch;
L_8000469c:
 STEP(UINT32_C(0x8000469c)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x800046a0));goto dispatch;
L_800046a0:
 STEP(UINT32_C(0x800046a0)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x800046a4));goto dispatch;
L_800046a4:
 STEP(UINT32_C(0x800046a4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800046a8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_800046a8:
 STEP(UINT32_C(0x800046a8)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x800046ac));goto dispatch;
L_80005978:
 STEP(UINT32_C(0x80005978)); /* 2403004c addiu v1,zero,76 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x8000597c));goto dispatch;
L_8000597c:
 STEP(UINT32_C(0x8000597c)); /* 3c058001 lui a1,zero,0x8001 */
 set(m,5u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80005980));goto dispatch;
L_80005980:
 STEP(UINT32_C(0x80005980)); /* 24a57408 addiu a1,a1,29704 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00007408)));target=sx(UINT32_C(0x80005984));goto dispatch;
L_80005984:
 STEP(UINT32_C(0x80005984)); /* 00831818 mult_rd v1,a0,v1 */
 {int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x80005988));goto dispatch;
L_80005988:
 STEP(UINT32_C(0x80005988)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x8000598c));goto dispatch;
L_8000598c:
 STEP(UINT32_C(0x8000598c)); /* 00431021 addu v0,v0,v1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80005990));goto dispatch;
L_80005990:
 STEP(UINT32_C(0x80005990)); /* 8c427408 lw v0,0x7408(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00007408),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005994));goto dispatch;
L_80005994:
 STEP(UINT32_C(0x80005994)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80005998));goto dispatch;
L_80005998:
 STEP(UINT32_C(0x80005998)); /* 2c420002 sltiu v0,v0,2 */
 set(m,2u,(lo(m,2u)<UINT64_C(0x2)));target=sx(UINT32_C(0x8000599c));goto dispatch;
L_8000599c:
 STEP(UINT32_C(0x8000599c)); /* 10400003 beq v0,zero,800059ac */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x800059a0));set(m,4u,sx((uint32_t)lo(m,5u)+UINT32_C(0xfffffff8)));target=sx(taken?UINT32_C(0x800059ac):UINT32_C(0x800059a4));goto dispatch;}
L_800059a0:
 STEP(UINT32_C(0x800059a0)); /* 24a4fff8 addiu a0,a1,-8 */
 set(m,4u,sx((uint32_t)lo(m,5u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x800059a4));goto dispatch;
L_800059a4:
 STEP(UINT32_C(0x800059a4)); /* 080016ba j 80005ae8 */
 STEP(UINT32_C(0x800059a8));set(m,4u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80005ae8));goto dispatch;
L_800059a8:
 STEP(UINT32_C(0x800059a8)); /* 00642021 addu a0,v1,a0 */
 set(m,4u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x800059ac));goto dispatch;
L_800059ac:
 STEP(UINT32_C(0x800059ac)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x800059b0));/* nop */goto dispatch;
L_800059b0:
 STEP(UINT32_C(0x800059b0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x800059b4));goto dispatch;
L_80005ae8:
 STEP(UINT32_C(0x80005ae8)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005aec));goto dispatch;
L_80005aec:
 STEP(UINT32_C(0x80005aec)); /* 8c830004 lw v1,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80005af0));goto dispatch;
L_80005af0:
 STEP(UINT32_C(0x80005af0)); /* ac620000 sw v0,0x0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80005af4));goto dispatch;
L_80005af4:
 STEP(UINT32_C(0x80005af4)); /* 8c850004 lw a1,0x4(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x80005af8));goto dispatch;
L_80005af8:
 STEP(UINT32_C(0x80005af8)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80005afc));goto dispatch;
L_80005afc:
 STEP(UINT32_C(0x80005afc)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80005b00));value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);goto dispatch;
L_80005b00:
 STEP(UINT32_C(0x80005b00)); /* ac450004 sw a1,0x4(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x80005b04));goto dispatch;
L_80003a78:
 STEP(UINT32_C(0x80003a78)); /* 3c078001 lui a3,zero,0x8001 */
 set(m,7u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003a7c));goto dispatch;
L_80003a7c:
 STEP(UINT32_C(0x80003a7c)); /* 8ce725ec lw a3,0x25ec(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x000025ec),&value32,4u);set(m,7u,sx(value32));target=sx(UINT32_C(0x80003a80));goto dispatch;
L_80003a80:
 STEP(UINT32_C(0x80003a80)); /* 2403004c addiu v1,zero,76 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x80003a84));goto dispatch;
L_80003a84:
 STEP(UINT32_C(0x80003a84)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x80003a88));goto dispatch;
L_80003a88:
 STEP(UINT32_C(0x80003a88)); /* 3c0b8001 lui t3,zero,0x8001 */
 set(m,11u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003a8c));goto dispatch;
L_80003a8c:
 STEP(UINT32_C(0x80003a8c)); /* 256b740c addiu t3,t3,29708 */
 set(m,11u,sx((uint32_t)lo(m,11u)+UINT32_C(0x0000740c)));target=sx(UINT32_C(0x80003a90));goto dispatch;
L_80003a90:
 STEP(UINT32_C(0x80003a90)); /* 00e31818 mult_rd v1,a3,v1 */
 {int64_t product;if(lo(m,7u)!=sx((uint32_t)lo(m,7u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,7u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=sx(UINT32_C(0x80003a94));goto dispatch;
L_80003a94:
 STEP(UINT32_C(0x80003a94)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x80003a98));goto dispatch;
L_80003a98:
 STEP(UINT32_C(0x80003a98)); /* 2562fffc addiu v0,t3,-4 */
 set(m,2u,sx((uint32_t)lo(m,11u)+UINT32_C(0xfffffffc)));target=sx(UINT32_C(0x80003a9c));goto dispatch;
L_80003a9c:
 STEP(UINT32_C(0x80003a9c)); /* 3c0a8001 lui t2,zero,0x8001 */
 set(m,10u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003aa0));goto dispatch;
L_80003aa0:
 STEP(UINT32_C(0x80003aa0)); /* 8d4a25f0 lw t2,0x25f0(t2) */
 READ((uint32_t)lo(m,10u)+UINT32_C(0x000025f0),&value32,4u);set(m,10u,sx(value32));target=sx(UINT32_C(0x80003aa4));goto dispatch;
L_80003aa4:
 STEP(UINT32_C(0x80003aa4)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80003aa8));goto dispatch;
L_80003aa8:
 STEP(UINT32_C(0x80003aa8)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x80003aac));goto dispatch;
L_80003aac:
 STEP(UINT32_C(0x80003aac)); /* 24080004 addiu t0,zero,4 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x80003ab0));goto dispatch;
L_80003ab0:
 STEP(UINT32_C(0x80003ab0)); /* 29490081 slti t1,t2,129 */
 set(m,9u,((int64_t)lo(m,10u)<INT64_C(129)));target=sx(UINT32_C(0x80003ab4));goto dispatch;
L_80003ab4:
 STEP(UINT32_C(0x80003ab4)); /* 01633821 addu a3,t3,v1 */
 set(m,7u,sx((uint32_t)lo(m,11u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003ab8));goto dispatch;
L_80003ab8:
 STEP(UINT32_C(0x80003ab8)); /* 00621021 addu v0,v1,v0 */
 set(m,2u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80003abc));goto dispatch;
L_80003abc:
 STEP(UINT32_C(0x80003abc)); /* ac480000 sw t0,0x0(v0) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80003ac0));goto dispatch;
L_80003ac0:
 STEP(UINT32_C(0x80003ac0)); /* ace60010 sw a2,0x10(a3) */
 value32=(uint32_t)lo(m,6u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x80003ac4));goto dispatch;
L_80003ac4:
 STEP(UINT32_C(0x80003ac4)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003ac8));goto dispatch;
L_80003ac8:
 STEP(UINT32_C(0x80003ac8)); /* 00230821 addu at,at,v1 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003acc));goto dispatch;
L_80003acc:
 STEP(UINT32_C(0x80003acc)); /* ac24740c sw a0,0x740c(at) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x0000740c),&value32,4u);target=sx(UINT32_C(0x80003ad0));goto dispatch;
L_80003ad0:
 STEP(UINT32_C(0x80003ad0)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003ad4));goto dispatch;
L_80003ad4:
 STEP(UINT32_C(0x80003ad4)); /* 00230821 addu at,at,v1 */
 set(m,1u,sx((uint32_t)lo(m,1u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003ad8));goto dispatch;
L_80003ad8:
 STEP(UINT32_C(0x80003ad8)); /* ac257410 sw a1,0x7410(at) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x00007410),&value32,4u);target=sx(UINT32_C(0x80003adc));goto dispatch;
L_80003adc:
 STEP(UINT32_C(0x80003adc)); /* 11200019 beq t1,zero,80003b44 */
 {int taken=(lo(m,9u)==lo(m,0u));STEP(UINT32_C(0x80003ae0));set(m,7u,sx(UINT32_C(0x286b0000)));target=sx(taken?UINT32_C(0x80003b44):UINT32_C(0x80003ae4));goto dispatch;}
L_80003ae0:
 STEP(UINT32_C(0x80003ae0)); /* 3c07286b lui a3,zero,0x286b */
 set(m,7u,sx(UINT32_C(0x286b0000)));target=sx(UINT32_C(0x80003ae4));goto dispatch;
L_80003ae4:
 STEP(UINT32_C(0x80003ae4)); /* 000a18c0 sll v1,t2,3 */
 set(m,3u,sx((uint32_t)lo(m,10u)<<3u));target=sx(UINT32_C(0x80003ae8));goto dispatch;
L_80003ae8:
 STEP(UINT32_C(0x80003ae8)); /* 3c028001 lui v0,zero,0x8001 */
 set(m,2u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003aec));goto dispatch;
L_80003aec:
 STEP(UINT32_C(0x80003aec)); /* 24426ff0 addiu v0,v0,28656 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00006ff0)));target=sx(UINT32_C(0x80003af0));goto dispatch;
L_80003af0:
 STEP(UINT32_C(0x80003af0)); /* 2564fff4 addiu a0,t3,-12 */
 set(m,4u,sx((uint32_t)lo(m,11u)+UINT32_C(0xfffffff4)));target=sx(UINT32_C(0x80003af4));goto dispatch;
L_80003af4:
 STEP(UINT32_C(0x80003af4)); /* 00621821 addu v1,v1,v0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80003af8));goto dispatch;
L_80003af8:
 STEP(UINT32_C(0x80003af8)); /* 34e7ca1b ori a3,a3,0xca1b */
 set(m,7u,lo(m,7u) | UINT64_C(0xca1b));target=sx(UINT32_C(0x80003afc));goto dispatch;
L_80003afc:
 STEP(UINT32_C(0x80003afc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x80003b00));goto dispatch;
L_80003b00:
 STEP(UINT32_C(0x80003b00)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80003b04));goto dispatch;
L_80003b04:
 STEP(UINT32_C(0x80003b04)); /* 14430003 bne v0,v1,80003b14 */
 {int taken=(lo(m,2u)!=lo(m,3u));STEP(UINT32_C(0x80003b08));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(taken?UINT32_C(0x80003b14):UINT32_C(0x80003b0c));goto dispatch;}
L_80003b08:
 STEP(UINT32_C(0x80003b08)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x80003b0c));goto dispatch;
L_80003b0c:
 STEP(UINT32_C(0x80003b0c)); /* 5043000a beql v0,v1,80003b38 */
 if(lo(m,2u)==lo(m,3u)){STEP(UINT32_C(0x80003b10));set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80003b38));}else target=sx(UINT32_C(0x80003b14));goto dispatch;
L_80003b10:
 STEP(UINT32_C(0x80003b10)); /* 254a0001 addiu t2,t2,1 */
 set(m,10u,sx((uint32_t)lo(m,10u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80003b14));goto dispatch;
L_80003b14:
 STEP(UINT32_C(0x80003b14)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003b18));goto dispatch;
L_80003b18:
 STEP(UINT32_C(0x80003b18)); /* ac2a25f0 sw t2,0x25f0(at) */
 value32=(uint32_t)lo(m,10u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000025f0),&value32,4u);target=sx(UINT32_C(0x80003b1c));goto dispatch;
L_80003b1c:
 STEP(UINT32_C(0x80003b1c)); /* 00441023 subu v0,v0,a0 */
 set(m,2u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,4u)));target=sx(UINT32_C(0x80003b20));goto dispatch;
L_80003b20:
 STEP(UINT32_C(0x80003b20)); /* 00471018 mult_rd v0,v0,a3 */
 {int64_t product;if(lo(m,2u)!=sx((uint32_t)lo(m,2u))||lo(m,7u)!=sx((uint32_t)lo(m,7u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,2u)*(int64_t)(int32_t)lo(m,7u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=sx(UINT32_C(0x80003b24));goto dispatch;
L_80003b24:
 STEP(UINT32_C(0x80003b24)); /* 00021083 sra v0,v0,2 */
 set(m,2u,sx((uint32_t)((int32_t)lo(m,2u)>>2u)));target=sx(UINT32_C(0x80003b28));goto dispatch;
L_80003b28:
 STEP(UINT32_C(0x80003b28)); /* 3c018001 lui at,zero,0x8001 */
 set(m,1u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003b2c));goto dispatch;
L_80003b2c:
 STEP(UINT32_C(0x80003b2c)); /* ac2225ec sw v0,0x25ec(at) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,1u)+UINT32_C(0x000025ec),&value32,4u);target=sx(UINT32_C(0x80003b30));goto dispatch;
L_80003b30:
 STEP(UINT32_C(0x80003b30)); /* 1000000a beq zero,zero,80003b5c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80003b34));set(m,7u,lo(m,2u)+lo(m,0u));target=sx(taken?UINT32_C(0x80003b5c):UINT32_C(0x80003b38));goto dispatch;}
L_80003b34:
 STEP(UINT32_C(0x80003b34)); /* 0040382d daddu a3,v0,zero */
 set(m,7u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x80003b38));goto dispatch;
L_80003b38:
 STEP(UINT32_C(0x80003b38)); /* 29420081 slti v0,t2,129 */
 set(m,2u,((int64_t)lo(m,10u)<INT64_C(129)));target=sx(UINT32_C(0x80003b3c));goto dispatch;
L_80003b3c:
 STEP(UINT32_C(0x80003b3c)); /* 1440fff0 bne v0,zero,80003b00 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80003b40));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x80003b00):UINT32_C(0x80003b44));goto dispatch;}
L_80003b40:
 STEP(UINT32_C(0x80003b40)); /* 24630008 addiu v1,v1,8 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x80003b44));goto dispatch;
L_80003b44:
 STEP(UINT32_C(0x80003b44)); /* 3c048001 lui a0,zero,0x8001 */
 set(m,4u,sx(UINT32_C(0x80010000)));target=sx(UINT32_C(0x80003b48));goto dispatch;
L_80003b48:
 STEP(UINT32_C(0x80003b48)); /* 0c001cd0 jal 80007340 */
 set(m,31u,UINT64_C(0x80003b50));STEP(UINT32_C(0x80003b4c));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00002b50)));target=sx(UINT32_C(0x80007340));goto dispatch;
L_80003b4c:
 STEP(UINT32_C(0x80003b4c)); /* 24842b50 addiu a0,a0,11088 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00002b50)));target=sx(UINT32_C(0x80003b50));goto dispatch;
L_80003b50:
 STEP(UINT32_C(0x80003b50)); /* 0c000360 jal 80000d80 */
 set(m,31u,UINT64_C(0x80003b58));STEP(UINT32_C(0x80003b54));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80000d80));goto dispatch;
L_80003b54:
 STEP(UINT32_C(0x80003b54)); /* 24040001 addiu a0,zero,1 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80003b58));goto dispatch;
L_80003b58:
 STEP(UINT32_C(0x80003b58)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x80003b5c));goto dispatch;
L_80003b5c:
 STEP(UINT32_C(0x80003b5c)); /* 2402004c addiu v0,zero,76 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000004c)));target=sx(UINT32_C(0x80003b60));goto dispatch;
L_80003b60:
 STEP(UINT32_C(0x80003b60)); /* 26030014 addiu v1,s0,20 */
 set(m,3u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000014)));target=sx(UINT32_C(0x80003b64));goto dispatch;
L_80003b64:
 STEP(UINT32_C(0x80003b64)); /* 00e21018 mult_rd v0,a3,v0 */
 {int64_t product;if(lo(m,7u)!=sx((uint32_t)lo(m,7u))||lo(m,2u)!=sx((uint32_t)lo(m,2u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,7u)*(int64_t)(int32_t)lo(m,2u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=sx(UINT32_C(0x80003b68));goto dispatch;
L_80003b68:
 STEP(UINT32_C(0x80003b68)); /* 24050001 addiu a1,zero,1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x80003b6c));goto dispatch;
L_80003b6c:
 STEP(UINT32_C(0x80003b6c)); /* 00433821 addu a3,v0,v1 */
 set(m,7u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=sx(UINT32_C(0x80003b70));goto dispatch;
L_80003b70:
 STEP(UINT32_C(0x80003b70)); /* 00502021 addu a0,v0,s0 */
 set(m,4u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=sx(UINT32_C(0x80003b74));goto dispatch;
L_80003b74:
 STEP(UINT32_C(0x80003b74)); /* 02021821 addu v1,s0,v0 */
 set(m,3u,sx((uint32_t)lo(m,16u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x80003b78));goto dispatch;
L_80003b78:
 STEP(UINT32_C(0x80003b78)); /* ac850000 sw a1,0x0(a0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80003b7c));goto dispatch;
L_80003b7c:
 STEP(UINT32_C(0x80003b7c)); /* 0060102d daddu v0,v1,zero */
 set(m,2u,lo(m,3u)+lo(m,0u));target=sx(UINT32_C(0x80003b80));goto dispatch;
L_80003b80:
 STEP(UINT32_C(0x80003b80)); /* 8c680004 lw t0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);set(m,8u,sx(value32));target=sx(UINT32_C(0x80003b84));goto dispatch;
L_80003b84:
 STEP(UINT32_C(0x80003b84)); /* 8ce30000 lw v1,0x0(a3) */
 READ((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x80003b88));goto dispatch;
L_80003b88:
 STEP(UINT32_C(0x80003b88)); /* 10600004 beq v1,zero,80003b9c */
 {int taken=(lo(m,3u)==lo(m,0u));STEP(UINT32_C(0x80003b8c));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(taken?UINT32_C(0x80003b9c):UINT32_C(0x80003b90));goto dispatch;}
L_80003b8c:
 STEP(UINT32_C(0x80003b8c)); /* 8c460008 lw a2,0x8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,6u,sx(value32));target=sx(UINT32_C(0x80003b90));goto dispatch;
L_80003b90:
 STEP(UINT32_C(0x80003b90)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x80003b94));goto dispatch;
L_80003b94:
 STEP(UINT32_C(0x80003b94)); /* ace00000 sw zero,0x0(a3) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x80003b98));goto dispatch;
L_80003b98:
 STEP(UINT32_C(0x80003b98)); /* fcc20020 sd v0,0x20(a2) */
 value64=lo(m,2u);WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x80003b9c));goto dispatch;
L_80003b9c:
 STEP(UINT32_C(0x80003b9c)); /* 0100102d daddu v0,t0,zero */
 set(m,2u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x80003ba0));goto dispatch;
L_80003ba0:
 STEP(UINT32_C(0x80003ba0)); /* 00c0182d daddu v1,a2,zero */
 set(m,3u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x80003ba4));goto dispatch;
L_80003ba4:
 STEP(UINT32_C(0x80003ba4)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x80003ba8));goto dispatch;
L_80003ba8:
 STEP(UINT32_C(0x80003ba8)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x80003bac));goto dispatch;
L_80003bac:
 STEP(UINT32_C(0x80003bac)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x80003bb0));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_80003bb0:
 STEP(UINT32_C(0x80003bb0)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x80003bb4));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

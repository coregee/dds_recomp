#include "sound_setup_native.h"
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
uint32_t nocturneSoundSetupResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002c1578):goto L_002c1578;
 case UINT32_C(0x002c157c):goto L_002c157c;
 case UINT32_C(0x002c1580):goto L_002c1580;
 case UINT32_C(0x002c1584):goto L_002c1584;
 case UINT32_C(0x002c1588):goto L_002c1588;
 case UINT32_C(0x002c158c):goto L_002c158c;
 case UINT32_C(0x002c1590):goto L_002c1590;
 case UINT32_C(0x002c1594):goto L_002c1594;
 case UINT32_C(0x002c1598):goto L_002c1598;
 case UINT32_C(0x002c159c):goto L_002c159c;
 case UINT32_C(0x002c15a0):goto L_002c15a0;
 case UINT32_C(0x002c15a4):goto L_002c15a4;
 case UINT32_C(0x002c15a8):goto L_002c15a8;
 case UINT32_C(0x002c15ac):goto L_002c15ac;
 case UINT32_C(0x002c15b0):goto L_002c15b0;
 case UINT32_C(0x002c15b4):goto L_002c15b4;
 case UINT32_C(0x002c15b8):goto L_002c15b8;
 case UINT32_C(0x002c15bc):goto L_002c15bc;
 case UINT32_C(0x002c15c0):goto L_002c15c0;
 case UINT32_C(0x002c15c4):goto L_002c15c4;
 case UINT32_C(0x002c15c8):goto L_002c15c8;
 case UINT32_C(0x002c15cc):goto L_002c15cc;
 case UINT32_C(0x002c15d0):goto L_002c15d0;
 case UINT32_C(0x002c15d4):goto L_002c15d4;
 case UINT32_C(0x002c15d8):goto L_002c15d8;
 case UINT32_C(0x002c15dc):goto L_002c15dc;
 case UINT32_C(0x002c15e0):goto L_002c15e0;
 case UINT32_C(0x002c15e4):goto L_002c15e4;
 case UINT32_C(0x002c15e8):goto L_002c15e8;
 case UINT32_C(0x002c15ec):goto L_002c15ec;
 case UINT32_C(0x002c15f0):goto L_002c15f0;
 case UINT32_C(0x002c15f4):goto L_002c15f4;
 case UINT32_C(0x002c15f8):goto L_002c15f8;
 case UINT32_C(0x002c15fc):goto L_002c15fc;
 case UINT32_C(0x002c1600):goto L_002c1600;
 case UINT32_C(0x002c1604):goto L_002c1604;
 case UINT32_C(0x002c1608):goto L_002c1608;
 case UINT32_C(0x002c160c):goto L_002c160c;
 case UINT32_C(0x002c1610):goto L_002c1610;
 case UINT32_C(0x002c1614):goto L_002c1614;
 case UINT32_C(0x002c1618):goto L_002c1618;
 case UINT32_C(0x002c161c):goto L_002c161c;
 case UINT32_C(0x002c1620):goto L_002c1620;
 case UINT32_C(0x002c1624):goto L_002c1624;
 case UINT32_C(0x002c1628):goto L_002c1628;
 case UINT32_C(0x002c162c):goto L_002c162c;
 case UINT32_C(0x002c1630):goto L_002c1630;
 case UINT32_C(0x002c1634):goto L_002c1634;
 case UINT32_C(0x002c1638):goto L_002c1638;
 case UINT32_C(0x002c163c):goto L_002c163c;
 case UINT32_C(0x002c1640):goto L_002c1640;
 case UINT32_C(0x002c1644):goto L_002c1644;
 case UINT32_C(0x002c1648):goto L_002c1648;
 case UINT32_C(0x002c164c):goto L_002c164c;
 case UINT32_C(0x002c1650):goto L_002c1650;
 case UINT32_C(0x002c1654):goto L_002c1654;
 case UINT32_C(0x002c1658):goto L_002c1658;
 case UINT32_C(0x002c165c):goto L_002c165c;
 case UINT32_C(0x002c1660):goto L_002c1660;
 case UINT32_C(0x002c1664):goto L_002c1664;
 case UINT32_C(0x002c1668):goto L_002c1668;
 case UINT32_C(0x002c1310):goto L_002c1310;
 case UINT32_C(0x002c1314):goto L_002c1314;
 case UINT32_C(0x002c1318):goto L_002c1318;
 case UINT32_C(0x002c131c):goto L_002c131c;
 case UINT32_C(0x002c1320):goto L_002c1320;
 case UINT32_C(0x002c1324):goto L_002c1324;
 case UINT32_C(0x002c1328):goto L_002c1328;
 case UINT32_C(0x002c132c):goto L_002c132c;
 case UINT32_C(0x002c1330):goto L_002c1330;
 case UINT32_C(0x002c1334):goto L_002c1334;
 case UINT32_C(0x002c1338):goto L_002c1338;
 case UINT32_C(0x002c133c):goto L_002c133c;
 case UINT32_C(0x002c1340):goto L_002c1340;
 case UINT32_C(0x002c1344):goto L_002c1344;
 case UINT32_C(0x002c1348):goto L_002c1348;
 case UINT32_C(0x002c134c):goto L_002c134c;
 case UINT32_C(0x002c1350):goto L_002c1350;
 case UINT32_C(0x002c1354):goto L_002c1354;
 case UINT32_C(0x002c1358):goto L_002c1358;
 case UINT32_C(0x002c135c):goto L_002c135c;
 case UINT32_C(0x002c1360):goto L_002c1360;
 case UINT32_C(0x002c1364):goto L_002c1364;
 case UINT32_C(0x002c1368):goto L_002c1368;
 case UINT32_C(0x002c136c):goto L_002c136c;
 case UINT32_C(0x002c1370):goto L_002c1370;
 case UINT32_C(0x002c1374):goto L_002c1374;
 case UINT32_C(0x002c1378):goto L_002c1378;
 case UINT32_C(0x002c137c):goto L_002c137c;
 case UINT32_C(0x002c1380):goto L_002c1380;
 case UINT32_C(0x002c1384):goto L_002c1384;
 case UINT32_C(0x002c1388):goto L_002c1388;
 case UINT32_C(0x002c138c):goto L_002c138c;
 case UINT32_C(0x002c1390):goto L_002c1390;
 case UINT32_C(0x002c1394):goto L_002c1394;
 case UINT32_C(0x002c1398):goto L_002c1398;
 case UINT32_C(0x002c139c):goto L_002c139c;
 case UINT32_C(0x002c13a0):goto L_002c13a0;
 case UINT32_C(0x002c13a4):goto L_002c13a4;
 case UINT32_C(0x002c13a8):goto L_002c13a8;
 case UINT32_C(0x002c13ac):goto L_002c13ac;
 case UINT32_C(0x002c13b0):goto L_002c13b0;
 case UINT32_C(0x002c13b4):goto L_002c13b4;
 case UINT32_C(0x002c13b8):goto L_002c13b8;
 case UINT32_C(0x002c13bc):goto L_002c13bc;
 case UINT32_C(0x002c13c0):goto L_002c13c0;
 case UINT32_C(0x002c13c4):goto L_002c13c4;
 case UINT32_C(0x002c13c8):goto L_002c13c8;
 case UINT32_C(0x002c13cc):goto L_002c13cc;
 case UINT32_C(0x002c13d0):goto L_002c13d0;
 case UINT32_C(0x002c13d4):goto L_002c13d4;
 case UINT32_C(0x002e3838):goto L_002e3838;
 case UINT32_C(0x002e383c):goto L_002e383c;
 case UINT32_C(0x002e3840):goto L_002e3840;
 case UINT32_C(0x002e3844):goto L_002e3844;
 case UINT32_C(0x002e3848):goto L_002e3848;
 case UINT32_C(0x002e384c):goto L_002e384c;
 case UINT32_C(0x002e3850):goto L_002e3850;
 case UINT32_C(0x002e3854):goto L_002e3854;
 case UINT32_C(0x002e3858):goto L_002e3858;
 case UINT32_C(0x002e385c):goto L_002e385c;
 case UINT32_C(0x002e3860):goto L_002e3860;
 case UINT32_C(0x002e3864):goto L_002e3864;
 case UINT32_C(0x002e3868):goto L_002e3868;
 case UINT32_C(0x002e386c):goto L_002e386c;
 case UINT32_C(0x002e3870):goto L_002e3870;
 case UINT32_C(0x002e3874):goto L_002e3874;
 case UINT32_C(0x002e3878):goto L_002e3878;
 case UINT32_C(0x002e387c):goto L_002e387c;
 case UINT32_C(0x002e3880):goto L_002e3880;
 case UINT32_C(0x002e3884):goto L_002e3884;
 case UINT32_C(0x002e3888):goto L_002e3888;
 case UINT32_C(0x002e388c):goto L_002e388c;
 case UINT32_C(0x002e3890):goto L_002e3890;
 case UINT32_C(0x002e3894):goto L_002e3894;
 case UINT32_C(0x002e3898):goto L_002e3898;
 case UINT32_C(0x002e389c):goto L_002e389c;
 case UINT32_C(0x002e38a0):goto L_002e38a0;
 case UINT32_C(0x002e38a4):goto L_002e38a4;
 case UINT32_C(0x002e38a8):goto L_002e38a8;
 case UINT32_C(0x002e38ac):goto L_002e38ac;
 case UINT32_C(0x002e38b0):goto L_002e38b0;
 case UINT32_C(0x002e38b4):goto L_002e38b4;
 case UINT32_C(0x002e38b8):goto L_002e38b8;
 case UINT32_C(0x002e38bc):goto L_002e38bc;
 case UINT32_C(0x002e38c0):goto L_002e38c0;
 case UINT32_C(0x002e38c4):goto L_002e38c4;
 case UINT32_C(0x002e38c8):goto L_002e38c8;
 case UINT32_C(0x002e38cc):goto L_002e38cc;
 case UINT32_C(0x002e38d0):goto L_002e38d0;
 case UINT32_C(0x002e38d4):goto L_002e38d4;
 case UINT32_C(0x002e38d8):goto L_002e38d8;
 case UINT32_C(0x002e38dc):goto L_002e38dc;
 case UINT32_C(0x002e38e0):goto L_002e38e0;
 case UINT32_C(0x002e38e4):goto L_002e38e4;
 case UINT32_C(0x002e38e8):goto L_002e38e8;
 case UINT32_C(0x002e38ec):goto L_002e38ec;
 case UINT32_C(0x002e38f0):goto L_002e38f0;
 case UINT32_C(0x002e38f4):goto L_002e38f4;
 case UINT32_C(0x002e38f8):goto L_002e38f8;
 case UINT32_C(0x002e38fc):goto L_002e38fc;
 case UINT32_C(0x002e3900):goto L_002e3900;
 case UINT32_C(0x002e3904):goto L_002e3904;
 case UINT32_C(0x002e3908):goto L_002e3908;
 case UINT32_C(0x002e390c):goto L_002e390c;
 case UINT32_C(0x002e3910):goto L_002e3910;
 case UINT32_C(0x002e3914):goto L_002e3914;
 case UINT32_C(0x002e3918):goto L_002e3918;
 case UINT32_C(0x002e391c):goto L_002e391c;
 case UINT32_C(0x002e3920):goto L_002e3920;
 case UINT32_C(0x002e3924):goto L_002e3924;
 case UINT32_C(0x002e3928):goto L_002e3928;
 case UINT32_C(0x002e392c):goto L_002e392c;
 case UINT32_C(0x002e3930):goto L_002e3930;
 case UINT32_C(0x002e3934):goto L_002e3934;
 case UINT32_C(0x002e3938):goto L_002e3938;
 case UINT32_C(0x002e393c):goto L_002e393c;
 case UINT32_C(0x002e3940):goto L_002e3940;
 case UINT32_C(0x002e3944):goto L_002e3944;
 case UINT32_C(0x002e3948):goto L_002e3948;
 case UINT32_C(0x002e394c):goto L_002e394c;
 case UINT32_C(0x002e3950):goto L_002e3950;
 case UINT32_C(0x002e3954):goto L_002e3954;
 case UINT32_C(0x002e3958):goto L_002e3958;
 case UINT32_C(0x002e395c):goto L_002e395c;
 case UINT32_C(0x002e3960):goto L_002e3960;
 case UINT32_C(0x002e3964):goto L_002e3964;
 case UINT32_C(0x002e3968):goto L_002e3968;
 case UINT32_C(0x002e396c):goto L_002e396c;
 case UINT32_C(0x002e3970):goto L_002e3970;
 case UINT32_C(0x002e3974):goto L_002e3974;
 case UINT32_C(0x002e3978):goto L_002e3978;
 case UINT32_C(0x002e397c):goto L_002e397c;
 case UINT32_C(0x002e3980):goto L_002e3980;
 case UINT32_C(0x002e3984):goto L_002e3984;
 case UINT32_C(0x002e3988):goto L_002e3988;
 case UINT32_C(0x002e398c):goto L_002e398c;
 case UINT32_C(0x002e3990):goto L_002e3990;
 case UINT32_C(0x002e3994):goto L_002e3994;
 case UINT32_C(0x002e3998):goto L_002e3998;
 case UINT32_C(0x002e399c):goto L_002e399c;
 case UINT32_C(0x002e39a0):goto L_002e39a0;
 case UINT32_C(0x002e39a4):goto L_002e39a4;
 case UINT32_C(0x002e39a8):goto L_002e39a8;
 case UINT32_C(0x002e39ac):goto L_002e39ac;
 case UINT32_C(0x002e39b0):goto L_002e39b0;
 case UINT32_C(0x002e39b4):goto L_002e39b4;
 case UINT32_C(0x002e39b8):goto L_002e39b8;
 case UINT32_C(0x002e39bc):goto L_002e39bc;
 case UINT32_C(0x002e39c0):goto L_002e39c0;
 case UINT32_C(0x002e39c4):goto L_002e39c4;
 case UINT32_C(0x002e39c8):goto L_002e39c8;
 case UINT32_C(0x002e39cc):goto L_002e39cc;
 case UINT32_C(0x002e39d0):goto L_002e39d0;
 case UINT32_C(0x002e39d4):goto L_002e39d4;
 case UINT32_C(0x002e39d8):goto L_002e39d8;
 case UINT32_C(0x002e39dc):goto L_002e39dc;
 case UINT32_C(0x002e39e0):goto L_002e39e0;
 case UINT32_C(0x002e39e4):goto L_002e39e4;
 case UINT32_C(0x002e39e8):goto L_002e39e8;
 case UINT32_C(0x002e39ec):goto L_002e39ec;
 case UINT32_C(0x002e39f0):goto L_002e39f0;
 case UINT32_C(0x002e39f4):goto L_002e39f4;
 case UINT32_C(0x002e39f8):goto L_002e39f8;
 case UINT32_C(0x002e39fc):goto L_002e39fc;
 case UINT32_C(0x002e3a00):goto L_002e3a00;
 case UINT32_C(0x002e3a04):goto L_002e3a04;
 case UINT32_C(0x002e3a08):goto L_002e3a08;
 case UINT32_C(0x002e3a0c):goto L_002e3a0c;
 case UINT32_C(0x002e3a10):goto L_002e3a10;
 case UINT32_C(0x002e3a14):goto L_002e3a14;
 case UINT32_C(0x002e3a18):goto L_002e3a18;
 case UINT32_C(0x002e3a1c):goto L_002e3a1c;
 case UINT32_C(0x002e3a20):goto L_002e3a20;
 case UINT32_C(0x002e3a24):goto L_002e3a24;
 case UINT32_C(0x002e3a28):goto L_002e3a28;
 case UINT32_C(0x002e3a2c):goto L_002e3a2c;
 case UINT32_C(0x002e3a30):goto L_002e3a30;
 case UINT32_C(0x002e3a34):goto L_002e3a34;
 case UINT32_C(0x002e3a38):goto L_002e3a38;
 case UINT32_C(0x002e3a3c):goto L_002e3a3c;
 case UINT32_C(0x002e3a40):goto L_002e3a40;
 case UINT32_C(0x002e3a44):goto L_002e3a44;
 case UINT32_C(0x002e3a48):goto L_002e3a48;
 case UINT32_C(0x002e3a4c):goto L_002e3a4c;
 case UINT32_C(0x002e3a50):goto L_002e3a50;
 case UINT32_C(0x002e3a54):goto L_002e3a54;
 case UINT32_C(0x002e3a58):goto L_002e3a58;
 case UINT32_C(0x002e3a60):goto L_002e3a60;
 case UINT32_C(0x002e3a64):goto L_002e3a64;
 case UINT32_C(0x002e3a68):goto L_002e3a68;
 case UINT32_C(0x002e3a6c):goto L_002e3a6c;
 case UINT32_C(0x002e3a70):goto L_002e3a70;
 case UINT32_C(0x002e3a74):goto L_002e3a74;
 case UINT32_C(0x002e3a78):goto L_002e3a78;
 case UINT32_C(0x002e3a7c):goto L_002e3a7c;
 case UINT32_C(0x002e3160):goto L_002e3160;
 case UINT32_C(0x002e3164):goto L_002e3164;
 case UINT32_C(0x002e3168):goto L_002e3168;
 case UINT32_C(0x002e316c):goto L_002e316c;
 case UINT32_C(0x002e3170):goto L_002e3170;
 case UINT32_C(0x002e3174):goto L_002e3174;
 case UINT32_C(0x002e3178):goto L_002e3178;
 case UINT32_C(0x002e317c):goto L_002e317c;
 case UINT32_C(0x002e3180):goto L_002e3180;
 case UINT32_C(0x002e3184):goto L_002e3184;
 case UINT32_C(0x002e3188):goto L_002e3188;
 case UINT32_C(0x002e318c):goto L_002e318c;
 case UINT32_C(0x002e3190):goto L_002e3190;
 case UINT32_C(0x002e3194):goto L_002e3194;
 case UINT32_C(0x002e3198):goto L_002e3198;
 case UINT32_C(0x002e319c):goto L_002e319c;
 case UINT32_C(0x002e31a0):goto L_002e31a0;
 case UINT32_C(0x002e31a4):goto L_002e31a4;
 case UINT32_C(0x002e31a8):goto L_002e31a8;
 case UINT32_C(0x002e31ac):goto L_002e31ac;
 case UINT32_C(0x002e31b0):goto L_002e31b0;
 case UINT32_C(0x002e31b4):goto L_002e31b4;
 case UINT32_C(0x002e31b8):goto L_002e31b8;
 case UINT32_C(0x002e31bc):goto L_002e31bc;
 case UINT32_C(0x002e31c0):goto L_002e31c0;
 case UINT32_C(0x002e31c4):goto L_002e31c4;
 case UINT32_C(0x002e31c8):goto L_002e31c8;
 case UINT32_C(0x002e31cc):goto L_002e31cc;
 case UINT32_C(0x002e31d0):goto L_002e31d0;
 case UINT32_C(0x002e31d4):goto L_002e31d4;
 case UINT32_C(0x002e31d8):goto L_002e31d8;
 case UINT32_C(0x002e31dc):goto L_002e31dc;
 case UINT32_C(0x002e31e0):goto L_002e31e0;
 case UINT32_C(0x002e31e4):goto L_002e31e4;
 case UINT32_C(0x002e31e8):goto L_002e31e8;
 case UINT32_C(0x002d6000):goto L_002d6000;
 case UINT32_C(0x002d6004):goto L_002d6004;
 case UINT32_C(0x002d6008):goto L_002d6008;
 case UINT32_C(0x002d600c):goto L_002d600c;
 case UINT32_C(0x002d6010):goto L_002d6010;
 case UINT32_C(0x002d6014):goto L_002d6014;
 case UINT32_C(0x002d6018):goto L_002d6018;
 case UINT32_C(0x002d601c):goto L_002d601c;
 case UINT32_C(0x002d6020):goto L_002d6020;
 case UINT32_C(0x002d6024):goto L_002d6024;
 case UINT32_C(0x002d6028):goto L_002d6028;
 case UINT32_C(0x002d602c):goto L_002d602c;
 case UINT32_C(0x002d6030):goto L_002d6030;
 case UINT32_C(0x002d6034):goto L_002d6034;
 case UINT32_C(0x002d6038):goto L_002d6038;
 case UINT32_C(0x002d603c):goto L_002d603c;
 case UINT32_C(0x002d6040):goto L_002d6040;
 case UINT32_C(0x002d6044):goto L_002d6044;
 case UINT32_C(0x002d6048):goto L_002d6048;
 case UINT32_C(0x002d604c):goto L_002d604c;
 case UINT32_C(0x002d6050):goto L_002d6050;
 case UINT32_C(0x002d6054):goto L_002d6054;
 case UINT32_C(0x002d6058):goto L_002d6058;
 case UINT32_C(0x002d605c):goto L_002d605c;
 case UINT32_C(0x002d6060):goto L_002d6060;
 case UINT32_C(0x002d6064):goto L_002d6064;
 case UINT32_C(0x002d6068):goto L_002d6068;
 case UINT32_C(0x002d606c):goto L_002d606c;
 case UINT32_C(0x002d6070):goto L_002d6070;
 case UINT32_C(0x002d6074):goto L_002d6074;
 case UINT32_C(0x002d6078):goto L_002d6078;
 case UINT32_C(0x002d607c):goto L_002d607c;
 case UINT32_C(0x002d6080):goto L_002d6080;
 case UINT32_C(0x002d6084):goto L_002d6084;
 case UINT32_C(0x002d6088):goto L_002d6088;
 case UINT32_C(0x002d608c):goto L_002d608c;
 case UINT32_C(0x002d6090):goto L_002d6090;
 case UINT32_C(0x002d6094):goto L_002d6094;
 case UINT32_C(0x002d6098):goto L_002d6098;
 case UINT32_C(0x002d609c):goto L_002d609c;
 case UINT32_C(0x002d60a0):goto L_002d60a0;
 case UINT32_C(0x002d60a4):goto L_002d60a4;
 case UINT32_C(0x002d60a8):goto L_002d60a8;
 case UINT32_C(0x002d60ac):goto L_002d60ac;
 case UINT32_C(0x002d60b0):goto L_002d60b0;
 case UINT32_C(0x002d60b4):goto L_002d60b4;
 case UINT32_C(0x002d60b8):goto L_002d60b8;
 case UINT32_C(0x002d60bc):goto L_002d60bc;
 case UINT32_C(0x002d60c0):goto L_002d60c0;
 case UINT32_C(0x002d60c4):goto L_002d60c4;
 case UINT32_C(0x002d60c8):goto L_002d60c8;
 case UINT32_C(0x002d60cc):goto L_002d60cc;
 case UINT32_C(0x002d60d0):goto L_002d60d0;
 case UINT32_C(0x002d60d4):goto L_002d60d4;
 case UINT32_C(0x002d60d8):goto L_002d60d8;
 case UINT32_C(0x002d60dc):goto L_002d60dc;
 case UINT32_C(0x002d60e0):goto L_002d60e0;
 case UINT32_C(0x002d60e4):goto L_002d60e4;
 case UINT32_C(0x002d60e8):goto L_002d60e8;
 case UINT32_C(0x002d60ec):goto L_002d60ec;
 case UINT32_C(0x002d60f0):goto L_002d60f0;
 case UINT32_C(0x002d60f4):goto L_002d60f4;
 case UINT32_C(0x002d60f8):goto L_002d60f8;
 case UINT32_C(0x002d60fc):goto L_002d60fc;
 case UINT32_C(0x002d6100):goto L_002d6100;
 case UINT32_C(0x002d6104):goto L_002d6104;
 case UINT32_C(0x002d6108):goto L_002d6108;
 case UINT32_C(0x002d610c):goto L_002d610c;
 case UINT32_C(0x002d6110):goto L_002d6110;
 case UINT32_C(0x002d6114):goto L_002d6114;
 case UINT32_C(0x002d6118):goto L_002d6118;
 case UINT32_C(0x002d611c):goto L_002d611c;
 case UINT32_C(0x002d6120):goto L_002d6120;
 case UINT32_C(0x002d6124):goto L_002d6124;
 case UINT32_C(0x002d6128):goto L_002d6128;
 case UINT32_C(0x002d612c):goto L_002d612c;
 case UINT32_C(0x002d6130):goto L_002d6130;
 case UINT32_C(0x002d6134):goto L_002d6134;
 case UINT32_C(0x002d6138):goto L_002d6138;
 case UINT32_C(0x002d613c):goto L_002d613c;
 case UINT32_C(0x002d6140):goto L_002d6140;
 case UINT32_C(0x002d6144):goto L_002d6144;
 case UINT32_C(0x002d6148):goto L_002d6148;
 case UINT32_C(0x002d614c):goto L_002d614c;
 case UINT32_C(0x002d6150):goto L_002d6150;
 case UINT32_C(0x002d6154):goto L_002d6154;
 case UINT32_C(0x002d6158):goto L_002d6158;
 case UINT32_C(0x002d615c):goto L_002d615c;
 case UINT32_C(0x002d6160):goto L_002d6160;
 case UINT32_C(0x002d6164):goto L_002d6164;
 case UINT32_C(0x002d6168):goto L_002d6168;
 case UINT32_C(0x002d616c):goto L_002d616c;
 case UINT32_C(0x002d6170):goto L_002d6170;
 case UINT32_C(0x002d6174):goto L_002d6174;
 case UINT32_C(0x002d6178):goto L_002d6178;
 case UINT32_C(0x002d617c):goto L_002d617c;
 case UINT32_C(0x002d6180):goto L_002d6180;
 case UINT32_C(0x002d6184):goto L_002d6184;
 case UINT32_C(0x002d6188):goto L_002d6188;
 case UINT32_C(0x002d618c):goto L_002d618c;
 case UINT32_C(0x002d6190):goto L_002d6190;
 case UINT32_C(0x002d6194):goto L_002d6194;
 case UINT32_C(0x002d6198):goto L_002d6198;
 case UINT32_C(0x002d619c):goto L_002d619c;
 case UINT32_C(0x002d61a0):goto L_002d61a0;
 case UINT32_C(0x002d61a4):goto L_002d61a4;
 case UINT32_C(0x002d61a8):goto L_002d61a8;
 case UINT32_C(0x002d61ac):goto L_002d61ac;
 case UINT32_C(0x002d61b0):goto L_002d61b0;
 case UINT32_C(0x002d61b4):goto L_002d61b4;
 case UINT32_C(0x002d61b8):goto L_002d61b8;
 case UINT32_C(0x002d4310):goto L_002d4310;
 case UINT32_C(0x002d4314):goto L_002d4314;
 case UINT32_C(0x002d4318):goto L_002d4318;
 case UINT32_C(0x002d431c):goto L_002d431c;
 case UINT32_C(0x002d4320):goto L_002d4320;
 case UINT32_C(0x002d4324):goto L_002d4324;
 case UINT32_C(0x002d4328):goto L_002d4328;
 case UINT32_C(0x002d432c):goto L_002d432c;
 case UINT32_C(0x002d4330):goto L_002d4330;
 case UINT32_C(0x002d4334):goto L_002d4334;
 case UINT32_C(0x002d4338):goto L_002d4338;
 case UINT32_C(0x002d433c):goto L_002d433c;
 case UINT32_C(0x002d4340):goto L_002d4340;
 case UINT32_C(0x002d4344):goto L_002d4344;
 case UINT32_C(0x002d4348):goto L_002d4348;
 case UINT32_C(0x002d434c):goto L_002d434c;
 case UINT32_C(0x002d4350):goto L_002d4350;
 case UINT32_C(0x002d4354):goto L_002d4354;
 case UINT32_C(0x002d4358):goto L_002d4358;
 case UINT32_C(0x002d435c):goto L_002d435c;
 case UINT32_C(0x002d4360):goto L_002d4360;
 case UINT32_C(0x002d4364):goto L_002d4364;
 case UINT32_C(0x002d4368):goto L_002d4368;
 case UINT32_C(0x002d436c):goto L_002d436c;
 case UINT32_C(0x002d4370):goto L_002d4370;
 case UINT32_C(0x002d4374):goto L_002d4374;
 case UINT32_C(0x002d4378):goto L_002d4378;
 case UINT32_C(0x002d437c):goto L_002d437c;
 case UINT32_C(0x002d4380):goto L_002d4380;
 case UINT32_C(0x002d4384):goto L_002d4384;
 case UINT32_C(0x002d4388):goto L_002d4388;
 case UINT32_C(0x002d438c):goto L_002d438c;
 case UINT32_C(0x002d4390):goto L_002d4390;
 case UINT32_C(0x002d4394):goto L_002d4394;
 case UINT32_C(0x002d4398):goto L_002d4398;
 case UINT32_C(0x002d439c):goto L_002d439c;
 case UINT32_C(0x002d43a0):goto L_002d43a0;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002c1578:
 STEP(UINT32_C(0x002c1578)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=sx(UINT32_C(0x002c157c));goto dispatch;
L_002c157c:
 STEP(UINT32_C(0x002c157c)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1580));goto dispatch;
L_002c1580:
 STEP(UINT32_C(0x002c1580)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c1584));goto dispatch;
L_002c1584:
 STEP(UINT32_C(0x002c1584)); /* 3c100059 lui s0,zero,0x59 */
 set(m,16u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c1588));goto dispatch;
L_002c1588:
 STEP(UINT32_C(0x002c1588)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c158c));goto dispatch;
L_002c158c:
 STEP(UINT32_C(0x002c158c)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002c1590));goto dispatch;
L_002c1590:
 STEP(UINT32_C(0x002c1590)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002c1594));goto dispatch;
L_002c1594:
 STEP(UINT32_C(0x002c1594)); /* 00a0902d daddu s2,a1,zero */
 set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002c1598));goto dispatch;
L_002c1598:
 STEP(UINT32_C(0x002c1598)); /* ffb30018 sd s3,0x18(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002c159c));goto dispatch;
L_002c159c:
 STEP(UINT32_C(0x002c159c)); /* 00c0982d daddu s3,a2,zero */
 set(m,19u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002c15a0));goto dispatch;
L_002c15a0:
 STEP(UINT32_C(0x002c15a0)); /* ffb40020 sd s4,0x20(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002c15a4));goto dispatch;
L_002c15a4:
 STEP(UINT32_C(0x002c15a4)); /* 00e0a02d daddu s4,a3,zero */
 set(m,20u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002c15a8));goto dispatch;
L_002c15a8:
 STEP(UINT32_C(0x002c15a8)); /* ffbf0028 sd ra,0x28(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);target=sx(UINT32_C(0x002c15ac));goto dispatch;
L_002c15ac:
 STEP(UINT32_C(0x002c15ac)); /* 26103880 addiu s0,s0,14464 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00003880)));target=sx(UINT32_C(0x002c15b0));goto dispatch;
L_002c15b0:
 STEP(UINT32_C(0x002c15b0)); /* 0c0b04c4 jal 002c1310 */
 set(m,31u,UINT64_C(0x002c15b8));STEP(UINT32_C(0x002c15b4));{uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc0),&byte,1u);}target=sx(UINT32_C(0x002c1310));goto dispatch;
L_002c15b4:
 STEP(UINT32_C(0x002c15b4)); /* a382dfc0 sb v0,-0x2040(gp) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc0),&byte,1u);}target=sx(UINT32_C(0x002c15b8));goto dispatch;
L_002c15b8:
 STEP(UINT32_C(0x002c15b8)); /* 0c0b8ac4 jal 002e2b10 */
 set(m,31u,UINT64_C(0x002c15c0));STEP(UINT32_C(0x002c15bc));/* nop */target=sx(UINT32_C(0x002e2b10));goto dispatch;
L_002c15bc:
 STEP(UINT32_C(0x002c15bc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c15c0));goto dispatch;
L_002c15c0:
 STEP(UINT32_C(0x002c15c0)); /* 0c0b03fe jal 002c0ff8 */
 set(m,31u,UINT64_C(0x002c15c8));STEP(UINT32_C(0x002c15c4));/* nop */target=sx(UINT32_C(0x002c0ff8));goto dispatch;
L_002c15c4:
 STEP(UINT32_C(0x002c15c4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c15c8));goto dispatch;
L_002c15c8:
 STEP(UINT32_C(0x002c15c8)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c15cc));goto dispatch;
L_002c15cc:
 STEP(UINT32_C(0x002c15cc)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c15d4));STEP(UINT32_C(0x002c15d0));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9a78)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c15d0:
 STEP(UINT32_C(0x002c15d0)); /* 24849a78 addiu a0,a0,-25992 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9a78)));target=sx(UINT32_C(0x002c15d4));goto dispatch;
L_002c15d4:
 STEP(UINT32_C(0x002c15d4)); /* 0c0b03a4 jal 002c0e90 */
 set(m,31u,UINT64_C(0x002c15dc));STEP(UINT32_C(0x002c15d8));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00004000)));target=sx(UINT32_C(0x002c0e90));goto dispatch;
L_002c15d8:
 STEP(UINT32_C(0x002c15d8)); /* 24044000 addiu a0,zero,16384 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00004000)));target=sx(UINT32_C(0x002c15dc));goto dispatch;
L_002c15dc:
 STEP(UINT32_C(0x002c15dc)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002c15e0));goto dispatch;
L_002c15e0:
 STEP(UINT32_C(0x002c15e0)); /* 24034000 addiu v1,zero,16384 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00004000)));target=sx(UINT32_C(0x002c15e4));goto dispatch;
L_002c15e4:
 STEP(UINT32_C(0x002c15e4)); /* ae020008 sw v0,0x8(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002c15e8));goto dispatch;
L_002c15e8:
 STEP(UINT32_C(0x002c15e8)); /* ae03000c sw v1,0xc(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002c15ec));goto dispatch;
L_002c15ec:
 STEP(UINT32_C(0x002c15ec)); /* 0c0b04f6 jal 002c13d8 */
 set(m,31u,UINT64_C(0x002c15f4));STEP(UINT32_C(0x002c15f0));set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002c13d8));goto dispatch;
L_002c15f0:
 STEP(UINT32_C(0x002c15f0)); /* 0240282d daddu a1,s2,zero */
 set(m,5u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002c15f4));goto dispatch;
L_002c15f4:
 STEP(UINT32_C(0x002c15f4)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002c15f8));goto dispatch;
L_002c15f8:
 STEP(UINT32_C(0x002c15f8)); /* 0c0b0524 jal 002c1490 */
 set(m,31u,UINT64_C(0x002c1600));STEP(UINT32_C(0x002c15fc));set(m,5u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002c1490));goto dispatch;
L_002c15fc:
 STEP(UINT32_C(0x002c15fc)); /* 0280282d daddu a1,s4,zero */
 set(m,5u,lo(m,20u)+lo(m,0u));target=sx(UINT32_C(0x002c1600));goto dispatch;
L_002c1600:
 STEP(UINT32_C(0x002c1600)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1604));goto dispatch;
L_002c1604:
 STEP(UINT32_C(0x002c1604)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c160c));STEP(UINT32_C(0x002c1608));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9a90)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c1608:
 STEP(UINT32_C(0x002c1608)); /* 24849a90 addiu a0,a0,-25968 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9a90)));target=sx(UINT32_C(0x002c160c));goto dispatch;
L_002c160c:
 STEP(UINT32_C(0x002c160c)); /* 0c0b03a4 jal 002c0e90 */
 set(m,31u,UINT64_C(0x002c1614));STEP(UINT32_C(0x002c1610));set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000005a0)));target=sx(UINT32_C(0x002c0e90));goto dispatch;
L_002c1610:
 STEP(UINT32_C(0x002c1610)); /* 240405a0 addiu a0,zero,1440 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000005a0)));target=sx(UINT32_C(0x002c1614));goto dispatch;
L_002c1614:
 STEP(UINT32_C(0x002c1614)); /* ae1001c8 sw s0,0x1c8(s0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x000001c8),&value32,4u);target=sx(UINT32_C(0x002c1618));goto dispatch;
L_002c1618:
 STEP(UINT32_C(0x002c1618)); /* 240305a0 addiu v1,zero,1440 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000005a0)));target=sx(UINT32_C(0x002c161c));goto dispatch;
L_002c161c:
 STEP(UINT32_C(0x002c161c)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c1620));goto dispatch;
L_002c1620:
 STEP(UINT32_C(0x002c1620)); /* ae0301cc sw v1,0x1cc(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x000001cc),&value32,4u);target=sx(UINT32_C(0x002c1624));goto dispatch;
L_002c1624:
 STEP(UINT32_C(0x002c1624)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c1628));goto dispatch;
L_002c1628:
 STEP(UINT32_C(0x002c1628)); /* 240605a0 addiu a2,zero,1440 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000005a0)));target=sx(UINT32_C(0x002c162c));goto dispatch;
L_002c162c:
 STEP(UINT32_C(0x002c162c)); /* 0c0b049e jal 002c1278 */
 set(m,31u,UINT64_C(0x002c1634));STEP(UINT32_C(0x002c1630));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfcc),&value32,4u);target=sx(UINT32_C(0x002c1278));goto dispatch;
L_002c1630:
 STEP(UINT32_C(0x002c1630)); /* af82dfcc sw v0,-0x2034(gp) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfcc),&value32,4u);target=sx(UINT32_C(0x002c1634));goto dispatch;
L_002c1634:
 STEP(UINT32_C(0x002c1634)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1638));goto dispatch;
L_002c1638:
 STEP(UINT32_C(0x002c1638)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c163c));goto dispatch;
L_002c163c:
 STEP(UINT32_C(0x002c163c)); /* 2786dfcc addiu a2,gp,-8244 */
 set(m,6u,sx((uint32_t)lo(m,28u)+UINT32_C(0xffffdfcc)));target=sx(UINT32_C(0x002c1640));goto dispatch;
L_002c1640:
 STEP(UINT32_C(0x002c1640)); /* 0c0b0490 jal 002c1240 */
 set(m,31u,UINT64_C(0x002c1648));STEP(UINT32_C(0x002c1644));set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002c1240));goto dispatch;
L_002c1644:
 STEP(UINT32_C(0x002c1644)); /* 24070004 addiu a3,zero,4 */
 set(m,7u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002c1648));goto dispatch;
L_002c1648:
 STEP(UINT32_C(0x002c1648)); /* a380dfc0 sb zero,-0x2040(gp) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,28u)+UINT32_C(0xffffdfc0),&byte,1u);}target=sx(UINT32_C(0x002c164c));goto dispatch;
L_002c164c:
 STEP(UINT32_C(0x002c164c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1650));goto dispatch;
L_002c1650:
 STEP(UINT32_C(0x002c1650)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c1654));goto dispatch;
L_002c1654:
 STEP(UINT32_C(0x002c1654)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002c1658));goto dispatch;
L_002c1658:
 STEP(UINT32_C(0x002c1658)); /* dfb30018 ld s3,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002c165c));goto dispatch;
L_002c165c:
 STEP(UINT32_C(0x002c165c)); /* dfb40020 ld s4,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002c1660));goto dispatch;
L_002c1660:
 STEP(UINT32_C(0x002c1660)); /* dfbf0028 ld ra,0x28(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c1664));goto dispatch;
L_002c1664:
 STEP(UINT32_C(0x002c1664)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c1668));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_002c1668:
 STEP(UINT32_C(0x002c1668)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=sx(UINT32_C(0x002c166c));goto dispatch;
L_002c1310:
 STEP(UINT32_C(0x002c1310)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1314));goto dispatch;
L_002c1314:
 STEP(UINT32_C(0x002c1314)); /* 27bdffa0 addiu sp,sp,-96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffa0)));target=sx(UINT32_C(0x002c1318));goto dispatch;
L_002c1318:
 STEP(UINT32_C(0x002c1318)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c131c));goto dispatch;
L_002c131c:
 STEP(UINT32_C(0x002c131c)); /* 24849988 addiu a0,a0,-26232 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9988)));target=sx(UINT32_C(0x002c1320));goto dispatch;
L_002c1320:
 STEP(UINT32_C(0x002c1320)); /* ffb00040 sd s0,0x40(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002c1324));goto dispatch;
L_002c1324:
 STEP(UINT32_C(0x002c1324)); /* ffb10048 sd s1,0x48(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000048),&value64,8u);target=sx(UINT32_C(0x002c1328));goto dispatch;
L_002c1328:
 STEP(UINT32_C(0x002c1328)); /* ffbf0050 sd ra,0x50(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002c132c));goto dispatch;
L_002c132c:
 STEP(UINT32_C(0x002c132c)); /* 0c0b8e98 jal 002e3a60 */
 set(m,31u,UINT64_C(0x002c1334));STEP(UINT32_C(0x002c1330));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3a60));goto dispatch;
L_002c1330:
 STEP(UINT32_C(0x002c1330)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1334));goto dispatch;
L_002c1334:
 STEP(UINT32_C(0x002c1334)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1338));goto dispatch;
L_002c1338:
 STEP(UINT32_C(0x002c1338)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c133c));goto dispatch;
L_002c133c:
 STEP(UINT32_C(0x002c133c)); /* 248499a8 addiu a0,a0,-26200 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff99a8)));target=sx(UINT32_C(0x002c1340));goto dispatch;
L_002c1340:
 STEP(UINT32_C(0x002c1340)); /* 0c0b8e98 jal 002e3a60 */
 set(m,31u,UINT64_C(0x002c1348));STEP(UINT32_C(0x002c1344));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3a60));goto dispatch;
L_002c1344:
 STEP(UINT32_C(0x002c1344)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1348));goto dispatch;
L_002c1348:
 STEP(UINT32_C(0x002c1348)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c134c));goto dispatch;
L_002c134c:
 STEP(UINT32_C(0x002c134c)); /* 248499c8 addiu a0,a0,-26168 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff99c8)));target=sx(UINT32_C(0x002c1350));goto dispatch;
L_002c1350:
 STEP(UINT32_C(0x002c1350)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1354));goto dispatch;
L_002c1354:
 STEP(UINT32_C(0x002c1354)); /* 0c0b8e98 jal 002e3a60 */
 set(m,31u,UINT64_C(0x002c135c));STEP(UINT32_C(0x002c1358));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3a60));goto dispatch;
L_002c1358:
 STEP(UINT32_C(0x002c1358)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c135c));goto dispatch;
L_002c135c:
 STEP(UINT32_C(0x002c135c)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1360));goto dispatch;
L_002c1360:
 STEP(UINT32_C(0x002c1360)); /* 248499e8 addiu a0,a0,-26136 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff99e8)));target=sx(UINT32_C(0x002c1364));goto dispatch;
L_002c1364:
 STEP(UINT32_C(0x002c1364)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1368));goto dispatch;
L_002c1368:
 STEP(UINT32_C(0x002c1368)); /* 0c0b8e98 jal 002e3a60 */
 set(m,31u,UINT64_C(0x002c1370));STEP(UINT32_C(0x002c136c));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3a60));goto dispatch;
L_002c136c:
 STEP(UINT32_C(0x002c136c)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1370));goto dispatch;
L_002c1370:
 STEP(UINT32_C(0x002c1370)); /* 3c030055 lui v1,zero,0x55 */
 set(m,3u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1374));goto dispatch;
L_002c1374:
 STEP(UINT32_C(0x002c1374)); /* 9386d836 lbu a2,-0x27ca(gp) */
 {uint8_t byte;READ((uint32_t)lo(m,28u)+UINT32_C(0xffffd836),&byte,1u);set(m,6u,byte);}target=sx(UINT32_C(0x002c1378));goto dispatch;
L_002c1378:
 STEP(UINT32_C(0x002c1378)); /* 24719a28 addiu s1,v1,-26072 */
 set(m,17u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffff9a28)));target=sx(UINT32_C(0x002c137c));goto dispatch;
L_002c137c:
 STEP(UINT32_C(0x002c137c)); /* 3c020055 lui v0,zero,0x55 */
 set(m,2u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1380));goto dispatch;
L_002c1380:
 STEP(UINT32_C(0x002c1380)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002c1384));goto dispatch;
L_002c1384:
 STEP(UINT32_C(0x002c1384)); /* 03a0282d daddu a1,sp,zero */
 set(m,5u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002c1388));goto dispatch;
L_002c1388:
 STEP(UINT32_C(0x002c1388)); /* 10c00009 beq a2,zero,002c13b0 */
 {int taken=(lo(m,6u)==lo(m,0u));STEP(UINT32_C(0x002c138c));set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9a08)));target=sx(taken?UINT32_C(0x002c13b0):UINT32_C(0x002c1390));goto dispatch;}
L_002c138c:
 STEP(UINT32_C(0x002c138c)); /* 24509a08 addiu s0,v0,-26104 */
 set(m,16u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff9a08)));target=sx(UINT32_C(0x002c1390));goto dispatch;
L_002c1390:
 STEP(UINT32_C(0x002c1390)); /* 0c0b8638 jal 002e18e0 */
 set(m,31u,UINT64_C(0x002c1398));STEP(UINT32_C(0x002c1394));/* nop */target=sx(UINT32_C(0x002e18e0));goto dispatch;
L_002c1394:
 STEP(UINT32_C(0x002c1394)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1398));goto dispatch;
L_002c1398:
 STEP(UINT32_C(0x002c1398)); /* 14400006 bne v0,zero,002c13b4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002c139c));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002c13b4):UINT32_C(0x002c13a0));goto dispatch;}
L_002c139c:
 STEP(UINT32_C(0x002c139c)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c13a0));goto dispatch;
L_002c13a0:
 STEP(UINT32_C(0x002c13a0)); /* 8fa20000 lw v0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002c13a4));goto dispatch;
L_002c13a4:
 STEP(UINT32_C(0x002c13a4)); /* 3042f000 andi v0,v0,0xf000 */
 set(m,2u,lo(m,2u) & UINT64_C(0xf000));target=sx(UINT32_C(0x002c13a8));goto dispatch;
L_002c13a8:
 STEP(UINT32_C(0x002c13a8)); /* 38422000 xori v0,v0,0x2000 */
 set(m,2u,lo(m,2u)^UINT64_C(0x2000));target=sx(UINT32_C(0x002c13ac));goto dispatch;
L_002c13ac:
 STEP(UINT32_C(0x002c13ac)); /* 0222800a movz s0,s1,v0 */
 if(lo(m,2u)==0u)set(m,16u,lo(m,17u));target=sx(UINT32_C(0x002c13b0));goto dispatch;
L_002c13b0:
 STEP(UINT32_C(0x002c13b0)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c13b4));goto dispatch;
L_002c13b4:
 STEP(UINT32_C(0x002c13b4)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c13b8));goto dispatch;
L_002c13b8:
 STEP(UINT32_C(0x002c13b8)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c13bc));goto dispatch;
L_002c13bc:
 STEP(UINT32_C(0x002c13bc)); /* 0c0aa62a jal 002a98a8 */
 set(m,31u,UINT64_C(0x002c13c4));STEP(UINT32_C(0x002c13c0));set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002a98a8));goto dispatch;
L_002c13c0:
 STEP(UINT32_C(0x002c13c0)); /* 0000382d daddu a3,zero,zero */
 set(m,7u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c13c4));goto dispatch;
L_002c13c4:
 STEP(UINT32_C(0x002c13c4)); /* dfb00040 ld s0,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c13c8));goto dispatch;
L_002c13c8:
 STEP(UINT32_C(0x002c13c8)); /* dfb10048 ld s1,0x48(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000048),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c13cc));goto dispatch;
L_002c13cc:
 STEP(UINT32_C(0x002c13cc)); /* dfbf0050 ld ra,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c13d0));goto dispatch;
L_002c13d0:
 STEP(UINT32_C(0x002c13d0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c13d4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));goto dispatch;
L_002c13d4:
 STEP(UINT32_C(0x002c13d4)); /* 27bd0060 addiu sp,sp,96 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000060)));target=sx(UINT32_C(0x002c13d8));goto dispatch;
L_002e3838:
 STEP(UINT32_C(0x002e3838)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=sx(UINT32_C(0x002e383c));goto dispatch;
L_002e383c:
 STEP(UINT32_C(0x002e383c)); /* ffb40050 sd s4,0x50(sp) */
 value64=lo(m,20u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002e3840));goto dispatch;
L_002e3840:
 STEP(UINT32_C(0x002e3840)); /* ffb30040 sd s3,0x40(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002e3844));goto dispatch;
L_002e3844:
 STEP(UINT32_C(0x002e3844)); /* 00e0a02d daddu s4,a3,zero */
 set(m,20u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002e3848));goto dispatch;
L_002e3848:
 STEP(UINT32_C(0x002e3848)); /* ffb20030 sd s2,0x30(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002e384c));goto dispatch;
L_002e384c:
 STEP(UINT32_C(0x002e384c)); /* 0100982d daddu s3,t0,zero */
 set(m,19u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002e3850));goto dispatch;
L_002e3850:
 STEP(UINT32_C(0x002e3850)); /* ffb10020 sd s1,0x20(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e3854));goto dispatch;
L_002e3854:
 STEP(UINT32_C(0x002e3854)); /* 00a0902d daddu s2,a1,zero */
 set(m,18u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002e3858));goto dispatch;
L_002e3858:
 STEP(UINT32_C(0x002e3858)); /* ffb00010 sd s0,0x10(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e385c));goto dispatch;
L_002e385c:
 STEP(UINT32_C(0x002e385c)); /* 0080882d daddu s1,a0,zero */
 set(m,17u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e3860));goto dispatch;
L_002e3860:
 STEP(UINT32_C(0x002e3860)); /* ffbf0070 sd ra,0x70(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);target=sx(UINT32_C(0x002e3864));goto dispatch;
L_002e3864:
 STEP(UINT32_C(0x002e3864)); /* 00c0802d daddu s0,a2,zero */
 set(m,16u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002e3868));goto dispatch;
L_002e3868:
 STEP(UINT32_C(0x002e3868)); /* 0c0b8c18 jal 002e3060 */
 set(m,31u,UINT64_C(0x002e3870));STEP(UINT32_C(0x002e386c));value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002e3060));goto dispatch;
L_002e386c:
 STEP(UINT32_C(0x002e386c)); /* ffb50060 sd s5,0x60(sp) */
 value64=lo(m,21u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002e3870));goto dispatch;
L_002e3870:
 STEP(UINT32_C(0x002e3870)); /* 04400071 regimm0 v0,002e3a38 */
 {int taken=((int64_t)lo(m,2u)<0);STEP(UINT32_C(0x002e3874));set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(taken?UINT32_C(0x002e3a38):UINT32_C(0x002e3878));goto dispatch;}
L_002e3874:
 STEP(UINT32_C(0x002e3874)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002e3878));goto dispatch;
L_002e3878:
 STEP(UINT32_C(0x002e3878)); /* 0c0b8c58 jal 002e3160 */
 set(m,31u,UINT64_C(0x002e3880));STEP(UINT32_C(0x002e387c));/* nop */target=sx(UINT32_C(0x002e3160));goto dispatch;
L_002e387c:
 STEP(UINT32_C(0x002e387c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e3880));goto dispatch;
L_002e3880:
 STEP(UINT32_C(0x002e3880)); /* 50400004 beql v0,zero,002e3894 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002e3884));set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e3894));}else target=sx(UINT32_C(0x002e3888));goto dispatch;
L_002e3884:
 STEP(UINT32_C(0x002e3884)); /* 3c02005a lui v0,zero,0x5a */
 set(m,2u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e3888));goto dispatch;
L_002e3888:
 STEP(UINT32_C(0x002e3888)); /* 3c02fffe lui v0,zero,0xfffe */
 set(m,2u,sx(UINT32_C(0xfffe0000)));target=sx(UINT32_C(0x002e388c));goto dispatch;
L_002e388c:
 STEP(UINT32_C(0x002e388c)); /* 1000006a beq zero,zero,002e3a38 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e3890));set(m,2u,lo(m,2u) | UINT64_C(0xfffc));target=sx(taken?UINT32_C(0x002e3a38):UINT32_C(0x002e3894));goto dispatch;}
L_002e3890:
 STEP(UINT32_C(0x002e3890)); /* 3442fffc ori v0,v0,0xfffc */
 set(m,2u,lo(m,2u) | UINT64_C(0xfffc));target=sx(UINT32_C(0x002e3894));goto dispatch;
L_002e3894:
 STEP(UINT32_C(0x002e3894)); /* 0220282d daddu a1,s1,zero */
 set(m,5u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002e3898));goto dispatch;
L_002e3898:
 STEP(UINT32_C(0x002e3898)); /* 2451ea08 addiu s1,v0,-5624 */
 set(m,17u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffea08)));target=sx(UINT32_C(0x002e389c));goto dispatch;
L_002e389c:
 STEP(UINT32_C(0x002e389c)); /* 240600fc addiu a2,zero,252 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000fc)));target=sx(UINT32_C(0x002e38a0));goto dispatch;
L_002e38a0:
 STEP(UINT32_C(0x002e38a0)); /* 0c0b5800 jal 002d6000 */
 set(m,31u,UINT64_C(0x002e38a8));STEP(UINT32_C(0x002e38a4));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d6000));goto dispatch;
L_002e38a4:
 STEP(UINT32_C(0x002e38a4)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002e38a8));goto dispatch;
L_002e38a8:
 STEP(UINT32_C(0x002e38a8)); /* 2622fff8 addiu v0,s1,-8 */
 set(m,2u,sx((uint32_t)lo(m,17u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002e38ac));goto dispatch;
L_002e38ac:
 STEP(UINT32_C(0x002e38ac)); /* 1200004c beq s0,zero,002e39e0 */
 {int taken=(lo(m,16u)==lo(m,0u));STEP(UINT32_C(0x002e38b0));{uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000103),&byte,1u);}target=sx(taken?UINT32_C(0x002e39e0):UINT32_C(0x002e38b4));goto dispatch;}
L_002e38b0:
 STEP(UINT32_C(0x002e38b0)); /* a0400103 sb zero,0x103(v0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000103),&byte,1u);}target=sx(UINT32_C(0x002e38b4));goto dispatch;
L_002e38b4:
 STEP(UINT32_C(0x002e38b4)); /* 2a4200fd slti v0,s2,253 */
 set(m,2u,((int64_t)lo(m,18u)<INT64_C(253)));target=sx(UINT32_C(0x002e38b8));goto dispatch;
L_002e38b8:
 STEP(UINT32_C(0x002e38b8)); /* 14400043 bne v0,zero,002e39c8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002e38bc));set(m,5u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e39c8):UINT32_C(0x002e38c0));goto dispatch;}
L_002e38bc:
 STEP(UINT32_C(0x002e38bc)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002e38c0));goto dispatch;
L_002e38c0:
 STEP(UINT32_C(0x002e38c0)); /* 262400fc addiu a0,s1,252 */
 set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0x000000fc)));target=sx(UINT32_C(0x002e38c4));goto dispatch;
L_002e38c4:
 STEP(UINT32_C(0x002e38c4)); /* 02041025 or v0,s0,a0 */
 set(m,2u,lo(m,16u)|lo(m,4u));target=sx(UINT32_C(0x002e38c8));goto dispatch;
L_002e38c8:
 STEP(UINT32_C(0x002e38c8)); /* 30420007 andi v0,v0,0x7 */
 set(m,2u,lo(m,2u) & UINT64_C(0x7));target=sx(UINT32_C(0x002e38cc));goto dispatch;
L_002e38cc:
 STEP(UINT32_C(0x002e38cc)); /* 1040001b beq v0,zero,002e393c */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002e38d0));set(m,3u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002e393c):UINT32_C(0x002e38d4));goto dispatch;}
L_002e38d0:
 STEP(UINT32_C(0x002e38d0)); /* 0200182d daddu v1,s0,zero */
 set(m,3u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002e38d4));goto dispatch;
L_002e38d4:
 STEP(UINT32_C(0x002e38d4)); /* 260200e0 addiu v0,s0,224 */
 set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0x000000e0)));target=sx(UINT32_C(0x002e38d8));goto dispatch;
L_002e38d8:
 STEP(UINT32_C(0x002e38d8)); /* 3c15005a lui s5,zero,0x5a */
 set(m,21u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e38dc));goto dispatch;
L_002e38dc:
 STEP(UINT32_C(0x002e38dc)); /* 3c05005a lui a1,zero,0x5a */
 set(m,5u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e38e0));goto dispatch;
L_002e38e0:
 STEP(UINT32_C(0x002e38e0)); /* 68660007 ldl a2,0x7(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000007);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002e38e4));goto dispatch;
L_002e38e4:
 STEP(UINT32_C(0x002e38e4)); /* 6c660000 ldr a2,0x0(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000000);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002e38e8));goto dispatch;
L_002e38e8:
 STEP(UINT32_C(0x002e38e8)); /* 6867000f ldl a3,0xf(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x0000000f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002e38ec));goto dispatch;
L_002e38ec:
 STEP(UINT32_C(0x002e38ec)); /* 6c670008 ldr a3,0x8(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000008);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002e38f0));goto dispatch;
L_002e38f0:
 STEP(UINT32_C(0x002e38f0)); /* 68680017 ldl t0,0x17(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000017);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,8u,(lo(m,8u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002e38f4));goto dispatch;
L_002e38f4:
 STEP(UINT32_C(0x002e38f4)); /* 6c680010 ldr t0,0x10(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000010);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,8u,(lo(m,8u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002e38f8));goto dispatch;
L_002e38f8:
 STEP(UINT32_C(0x002e38f8)); /* 6869001f ldl t1,0x1f(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x0000001f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,9u,(lo(m,9u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002e38fc));goto dispatch;
L_002e38fc:
 STEP(UINT32_C(0x002e38fc)); /* 6c690018 ldr t1,0x18(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000018);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,9u,(lo(m,9u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002e3900));goto dispatch;
L_002e3900:
 STEP(UINT32_C(0x002e3900)); /* b0860007 sdl a2,0x7(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000007);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,6u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e3904));goto dispatch;
L_002e3904:
 STEP(UINT32_C(0x002e3904)); /* b4860000 sdr a2,0x0(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000000);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,6u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e3908));goto dispatch;
L_002e3908:
 STEP(UINT32_C(0x002e3908)); /* b087000f sdl a3,0xf(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x0000000f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,7u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e390c));goto dispatch;
L_002e390c:
 STEP(UINT32_C(0x002e390c)); /* b4870008 sdr a3,0x8(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000008);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,7u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e3910));goto dispatch;
L_002e3910:
 STEP(UINT32_C(0x002e3910)); /* b0880017 sdl t0,0x17(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000017);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,8u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e3914));goto dispatch;
L_002e3914:
 STEP(UINT32_C(0x002e3914)); /* b4880010 sdr t0,0x10(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000010);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,8u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e3918));goto dispatch;
L_002e3918:
 STEP(UINT32_C(0x002e3918)); /* b089001f sdl t1,0x1f(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x0000001f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,9u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e391c));goto dispatch;
L_002e391c:
 STEP(UINT32_C(0x002e391c)); /* b4890018 sdr t1,0x18(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000018);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,9u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e3920));goto dispatch;
L_002e3920:
 STEP(UINT32_C(0x002e3920)); /* 24630020 addiu v1,v1,32 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e3924));goto dispatch;
L_002e3924:
 STEP(UINT32_C(0x002e3924)); /* 24840020 addiu a0,a0,32 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e3928));goto dispatch;
L_002e3928:
 STEP(UINT32_C(0x002e3928)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e392c));goto dispatch;
L_002e392c:
 STEP(UINT32_C(0x002e392c)); /* 1462ffec bne v1,v0,002e38e0 */
 {int taken=(lo(m,3u)!=lo(m,2u));STEP(UINT32_C(0x002e3930));/* nop */target=sx(taken?UINT32_C(0x002e38e0):UINT32_C(0x002e3934));goto dispatch;}
L_002e3930:
 STEP(UINT32_C(0x002e3930)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e3934));goto dispatch;
L_002e3934:
 STEP(UINT32_C(0x002e3934)); /* 10000011 beq zero,zero,002e397c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e3938));/* nop */target=sx(taken?UINT32_C(0x002e397c):UINT32_C(0x002e393c));goto dispatch;}
L_002e3938:
 STEP(UINT32_C(0x002e3938)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e393c));goto dispatch;
L_002e393c:
 STEP(UINT32_C(0x002e393c)); /* 260200e0 addiu v0,s0,224 */
 set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0x000000e0)));target=sx(UINT32_C(0x002e3940));goto dispatch;
L_002e3940:
 STEP(UINT32_C(0x002e3940)); /* 3c15005a lui s5,zero,0x5a */
 set(m,21u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e3944));goto dispatch;
L_002e3944:
 STEP(UINT32_C(0x002e3944)); /* 3c05005a lui a1,zero,0x5a */
 set(m,5u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e3948));goto dispatch;
L_002e3948:
 STEP(UINT32_C(0x002e3948)); /* dc660000 ld a2,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value64,8u);set(m,6u,value64);target=sx(UINT32_C(0x002e394c));goto dispatch;
L_002e394c:
 STEP(UINT32_C(0x002e394c)); /* dc670008 ld a3,0x8(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value64,8u);set(m,7u,value64);target=sx(UINT32_C(0x002e3950));goto dispatch;
L_002e3950:
 STEP(UINT32_C(0x002e3950)); /* dc680010 ld t0,0x10(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000010),&value64,8u);set(m,8u,value64);target=sx(UINT32_C(0x002e3954));goto dispatch;
L_002e3954:
 STEP(UINT32_C(0x002e3954)); /* dc690018 ld t1,0x18(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000018),&value64,8u);set(m,9u,value64);target=sx(UINT32_C(0x002e3958));goto dispatch;
L_002e3958:
 STEP(UINT32_C(0x002e3958)); /* fc860000 sd a2,0x0(a0) */
 value64=lo(m,6u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002e395c));goto dispatch;
L_002e395c:
 STEP(UINT32_C(0x002e395c)); /* fc870008 sd a3,0x8(a0) */
 value64=lo(m,7u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002e3960));goto dispatch;
L_002e3960:
 STEP(UINT32_C(0x002e3960)); /* fc880010 sd t0,0x10(a0) */
 value64=lo(m,8u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e3964));goto dispatch;
L_002e3964:
 STEP(UINT32_C(0x002e3964)); /* fc890018 sd t1,0x18(a0) */
 value64=lo(m,9u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002e3968));goto dispatch;
L_002e3968:
 STEP(UINT32_C(0x002e3968)); /* 24630020 addiu v1,v1,32 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e396c));goto dispatch;
L_002e396c:
 STEP(UINT32_C(0x002e396c)); /* 24840020 addiu a0,a0,32 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e3970));goto dispatch;
L_002e3970:
 STEP(UINT32_C(0x002e3970)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e3974));goto dispatch;
L_002e3974:
 STEP(UINT32_C(0x002e3974)); /* 1462fff4 bne v1,v0,002e3948 */
 {int taken=(lo(m,3u)!=lo(m,2u));STEP(UINT32_C(0x002e3978));/* nop */target=sx(taken?UINT32_C(0x002e3948):UINT32_C(0x002e397c));goto dispatch;}
L_002e3978:
 STEP(UINT32_C(0x002e3978)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002e397c));goto dispatch;
L_002e397c:
 STEP(UINT32_C(0x002e397c)); /* 68660007 ldl a2,0x7(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000007);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002e3980));goto dispatch;
L_002e3980:
 STEP(UINT32_C(0x002e3980)); /* 6c660000 ldr a2,0x0(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000000);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,6u,(lo(m,6u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002e3984));goto dispatch;
L_002e3984:
 STEP(UINT32_C(0x002e3984)); /* 6867000f ldl a3,0xf(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x0000000f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002e3988));goto dispatch;
L_002e3988:
 STEP(UINT32_C(0x002e3988)); /* 6c670008 ldr a3,0x8(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000008);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,7u,(lo(m,7u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002e398c));goto dispatch;
L_002e398c:
 STEP(UINT32_C(0x002e398c)); /* 68680017 ldl t0,0x17(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000017);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,8u,(lo(m,8u)&(shift==7u?0u:UINT64_MAX>>(8u*(shift+1u))))|(value64<<(8u*(7u-shift))));}target=sx(UINT32_C(0x002e3990));goto dispatch;
L_002e3990:
 STEP(UINT32_C(0x002e3990)); /* 6c680010 ldr t0,0x10(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000010);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);set(m,8u,(lo(m,8u)&(shift?UINT64_MAX<<(8u*(8u-shift)):0u))|(value64>>(8u*shift)));}target=sx(UINT32_C(0x002e3994));goto dispatch;
L_002e3994:
 STEP(UINT32_C(0x002e3994)); /* 8869001b lwl t1,0x1b(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x0000001b);unsigned shift=effective&3u;READ(effective&~3u,&value32,4u);value32=((uint32_t)lo(m,9u)&(UINT32_C(0x00ffffff)>>(8u*shift)))|(value32<<(8u*(3u-shift)));set(m,9u,sx(value32));}target=sx(UINT32_C(0x002e3998));goto dispatch;
L_002e3998:
 STEP(UINT32_C(0x002e3998)); /* 98690018 lwr t1,0x18(v1) */
 {uint32_t effective=(uint32_t)lo(m,3u)+UINT32_C(0x00000018);unsigned shift=effective&3u;READ(effective&~3u,&value32,4u);value32=((uint32_t)lo(m,9u)&(shift?UINT32_MAX<<(8u*(4u-shift)):0u))|(value32>>(8u*shift));set(m,9u,shift?(lo(m,9u)&UINT64_C(0xffffffff00000000))|value32:sx(value32));}target=sx(UINT32_C(0x002e399c));goto dispatch;
L_002e399c:
 STEP(UINT32_C(0x002e399c)); /* b0860007 sdl a2,0x7(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000007);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,6u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e39a0));goto dispatch;
L_002e39a0:
 STEP(UINT32_C(0x002e39a0)); /* b4860000 sdr a2,0x0(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000000);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,6u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e39a4));goto dispatch;
L_002e39a4:
 STEP(UINT32_C(0x002e39a4)); /* b087000f sdl a3,0xf(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x0000000f);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,7u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e39a8));goto dispatch;
L_002e39a8:
 STEP(UINT32_C(0x002e39a8)); /* b4870008 sdr a3,0x8(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000008);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,7u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e39ac));goto dispatch;
L_002e39ac:
 STEP(UINT32_C(0x002e39ac)); /* b0880017 sdl t0,0x17(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000017);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift==7u?0u:UINT64_MAX<<(8u*(shift+1u))))|(lo(m,8u)>>(8u*(7u-shift)));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e39b0));goto dispatch;
L_002e39b0:
 STEP(UINT32_C(0x002e39b0)); /* b4880010 sdr t0,0x10(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000010);unsigned shift=effective&7u;READ(effective&~7u,&value64,8u);value64=(value64&(shift?(UINT64_C(1)<<(8u*shift))-1u:0u))|(lo(m,8u)<<(8u*shift));WRITE(effective&~7u,&value64,8u);}target=sx(UINT32_C(0x002e39b4));goto dispatch;
L_002e39b4:
 STEP(UINT32_C(0x002e39b4)); /* a889001b swl t1,0x1b(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x0000001b);unsigned shift=effective&3u;READ(effective&~3u,&value32,4u);value32=(value32&(shift==3u?0u:UINT32_MAX<<(8u*(shift+1u))))|((uint32_t)lo(m,9u)>>(8u*(3u-shift)));WRITE(effective&~3u,&value32,4u);}target=sx(UINT32_C(0x002e39b8));goto dispatch;
L_002e39b8:
 STEP(UINT32_C(0x002e39b8)); /* 240200fc addiu v0,zero,252 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x000000fc)));target=sx(UINT32_C(0x002e39bc));goto dispatch;
L_002e39bc:
 STEP(UINT32_C(0x002e39bc)); /* b8890018 swr t1,0x18(a0) */
 {uint32_t effective=(uint32_t)lo(m,4u)+UINT32_C(0x00000018);unsigned shift=effective&3u;READ(effective&~3u,&value32,4u);value32=(value32&(shift?(UINT32_C(1)<<(8u*shift))-1u:0u))|((uint32_t)lo(m,9u)<<(8u*shift));WRITE(effective&~3u,&value32,4u);}target=sx(UINT32_C(0x002e39c0));goto dispatch;
L_002e39c0:
 STEP(UINT32_C(0x002e39c0)); /* 1000000b beq zero,zero,002e39f0 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e39c4));value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0xffffea00),&value32,4u);target=sx(taken?UINT32_C(0x002e39f0):UINT32_C(0x002e39c8));goto dispatch;}
L_002e39c4:
 STEP(UINT32_C(0x002e39c4)); /* aea2ea00 sw v0,-0x1600(s5) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,21u)+UINT32_C(0xffffea00),&value32,4u);target=sx(UINT32_C(0x002e39c8));goto dispatch;
L_002e39c8:
 STEP(UINT32_C(0x002e39c8)); /* 262400fc addiu a0,s1,252 */
 set(m,4u,sx((uint32_t)lo(m,17u)+UINT32_C(0x000000fc)));target=sx(UINT32_C(0x002e39cc));goto dispatch;
L_002e39cc:
 STEP(UINT32_C(0x002e39cc)); /* 0240302d daddu a2,s2,zero */
 set(m,6u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002e39d0));goto dispatch;
L_002e39d0:
 STEP(UINT32_C(0x002e39d0)); /* 0c0b50e9 jal 002d43a4 */
 set(m,31u,UINT64_C(0x002e39d8));STEP(UINT32_C(0x002e39d4));set(m,21u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002d43a4));goto dispatch;
L_002e39d4:
 STEP(UINT32_C(0x002e39d4)); /* 3c15005a lui s5,zero,0x5a */
 set(m,21u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e39d8));goto dispatch;
L_002e39d8:
 STEP(UINT32_C(0x002e39d8)); /* 10000004 beq zero,zero,002e39ec */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e39dc));value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0xfffffff8),&value32,4u);target=sx(taken?UINT32_C(0x002e39ec):UINT32_C(0x002e39e0));goto dispatch;}
L_002e39dc:
 STEP(UINT32_C(0x002e39dc)); /* ae32fff8 sw s2,-0x8(s1) */
 value32=(uint32_t)lo(m,18u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0xfffffff8),&value32,4u);target=sx(UINT32_C(0x002e39e0));goto dispatch;
L_002e39e0:
 STEP(UINT32_C(0x002e39e0)); /* a0400104 sb zero,0x104(v0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000104),&byte,1u);}target=sx(UINT32_C(0x002e39e4));goto dispatch;
L_002e39e4:
 STEP(UINT32_C(0x002e39e4)); /* 3c15005a lui s5,zero,0x5a */
 set(m,21u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e39e8));goto dispatch;
L_002e39e8:
 STEP(UINT32_C(0x002e39e8)); /* ae20fff8 sw zero,-0x8(s1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,17u)+UINT32_C(0xfffffff8),&value32,4u);target=sx(UINT32_C(0x002e39ec));goto dispatch;
L_002e39ec:
 STEP(UINT32_C(0x002e39ec)); /* 3c05005a lui a1,zero,0x5a */
 set(m,5u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e39f0));goto dispatch;
L_002e39f0:
 STEP(UINT32_C(0x002e39f0)); /* 26b0ea00 addiu s0,s5,-5632 */
 set(m,16u,sx((uint32_t)lo(m,21u)+UINT32_C(0xffffea00)));target=sx(UINT32_C(0x002e39f4));goto dispatch;
L_002e39f4:
 STEP(UINT32_C(0x002e39f4)); /* 24a4ec00 addiu a0,a1,-5120 */
 set(m,4u,sx((uint32_t)lo(m,5u)+UINT32_C(0xffffec00)));target=sx(UINT32_C(0x002e39f8));goto dispatch;
L_002e39f8:
 STEP(UINT32_C(0x002e39f8)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002e39fc));goto dispatch;
L_002e39fc:
 STEP(UINT32_C(0x002e39fc)); /* afa00000 sw zero,0x0(sp) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e3a00));goto dispatch;
L_002e3a00:
 STEP(UINT32_C(0x002e3a00)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3a04));goto dispatch;
L_002e3a04:
 STEP(UINT32_C(0x002e3a04)); /* 0200382d daddu a3,s0,zero */
 set(m,7u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002e3a08));goto dispatch;
L_002e3a08:
 STEP(UINT32_C(0x002e3a08)); /* 24080200 addiu t0,zero,512 */
 set(m,8u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000200)));target=sx(UINT32_C(0x002e3a0c));goto dispatch;
L_002e3a0c:
 STEP(UINT32_C(0x002e3a0c)); /* 0200482d daddu t1,s0,zero */
 set(m,9u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002e3a10));goto dispatch;
L_002e3a10:
 STEP(UINT32_C(0x002e3a10)); /* 240a0008 addiu t2,zero,8 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002e3a14));goto dispatch;
L_002e3a14:
 STEP(UINT32_C(0x002e3a14)); /* 0c0b7b52 jal 002ded48 */
 set(m,31u,UINT64_C(0x002e3a1c));STEP(UINT32_C(0x002e3a18));set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002ded48));goto dispatch;
L_002e3a18:
 STEP(UINT32_C(0x002e3a18)); /* 0000582d daddu t3,zero,zero */
 set(m,11u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3a1c));goto dispatch;
L_002e3a1c:
 STEP(UINT32_C(0x002e3a1c)); /* 04430004 regimm3 v0,002e3a30 */
 if((int64_t)lo(m,2u)>=0){STEP(UINT32_C(0x002e3a20));READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002e3a30));}else target=sx(UINT32_C(0x002e3a24));goto dispatch;
L_002e3a20:
 STEP(UINT32_C(0x002e3a20)); /* 8e030004 lw v1,0x4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000004),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002e3a24));goto dispatch;
L_002e3a24:
 STEP(UINT32_C(0x002e3a24)); /* 3c02fffe lui v0,zero,0xfffe */
 set(m,2u,sx(UINT32_C(0xfffe0000)));target=sx(UINT32_C(0x002e3a28));goto dispatch;
L_002e3a28:
 STEP(UINT32_C(0x002e3a28)); /* 10000003 beq zero,zero,002e3a38 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002e3a2c));set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(taken?UINT32_C(0x002e3a38):UINT32_C(0x002e3a30));goto dispatch;}
L_002e3a2c:
 STEP(UINT32_C(0x002e3a2c)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002e3a30));goto dispatch;
L_002e3a30:
 STEP(UINT32_C(0x002e3a30)); /* 8ea2ea00 lw v0,-0x1600(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0xffffea00),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002e3a34));goto dispatch;
L_002e3a34:
 STEP(UINT32_C(0x002e3a34)); /* ae830000 sw v1,0x0(s4) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,20u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002e3a38));goto dispatch;
L_002e3a38:
 STEP(UINT32_C(0x002e3a38)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e3a3c));goto dispatch;
L_002e3a3c:
 STEP(UINT32_C(0x002e3a3c)); /* dfb50060 ld s5,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);set(m,21u,value64);target=sx(UINT32_C(0x002e3a40));goto dispatch;
L_002e3a40:
 STEP(UINT32_C(0x002e3a40)); /* dfb40050 ld s4,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);set(m,20u,value64);target=sx(UINT32_C(0x002e3a44));goto dispatch;
L_002e3a44:
 STEP(UINT32_C(0x002e3a44)); /* dfb30040 ld s3,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002e3a48));goto dispatch;
L_002e3a48:
 STEP(UINT32_C(0x002e3a48)); /* dfb20030 ld s2,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002e3a4c));goto dispatch;
L_002e3a4c:
 STEP(UINT32_C(0x002e3a4c)); /* dfb10020 ld s1,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002e3a50));goto dispatch;
L_002e3a50:
 STEP(UINT32_C(0x002e3a50)); /* dfb00010 ld s0,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e3a54));goto dispatch;
L_002e3a54:
 STEP(UINT32_C(0x002e3a54)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e3a58));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_002e3a58:
 STEP(UINT32_C(0x002e3a58)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=sx(UINT32_C(0x002e3a5c));goto dispatch;
L_002e3a60:
 STEP(UINT32_C(0x002e3a60)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002e3a64));goto dispatch;
L_002e3a64:
 STEP(UINT32_C(0x002e3a64)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3a68));goto dispatch;
L_002e3a68:
 STEP(UINT32_C(0x002e3a68)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e3a6c));goto dispatch;
L_002e3a6c:
 STEP(UINT32_C(0x002e3a6c)); /* 0c0b8e0e jal 002e3838 */
 set(m,31u,UINT64_C(0x002e3a74));STEP(UINT32_C(0x002e3a70));set(m,7u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002e3838));goto dispatch;
L_002e3a70:
 STEP(UINT32_C(0x002e3a70)); /* 03a0382d daddu a3,sp,zero */
 set(m,7u,lo(m,29u)+lo(m,0u));target=sx(UINT32_C(0x002e3a74));goto dispatch;
L_002e3a74:
 STEP(UINT32_C(0x002e3a74)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e3a78));goto dispatch;
L_002e3a78:
 STEP(UINT32_C(0x002e3a78)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e3a7c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002e3a7c:
 STEP(UINT32_C(0x002e3a7c)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002e3a80));goto dispatch;
L_002e3160:
 STEP(UINT32_C(0x002e3160)); /* 27bdffb0 addiu sp,sp,-80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffb0)));target=sx(UINT32_C(0x002e3164));goto dispatch;
L_002e3164:
 STEP(UINT32_C(0x002e3164)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e3168));goto dispatch;
L_002e3168:
 STEP(UINT32_C(0x002e3168)); /* ffb30030 sd s3,0x30(sp) */
 value64=lo(m,19u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);target=sx(UINT32_C(0x002e316c));goto dispatch;
L_002e316c:
 STEP(UINT32_C(0x002e316c)); /* 3c03005a lui v1,zero,0x5a */
 set(m,3u,sx(UINT32_C(0x005a0000)));target=sx(UINT32_C(0x002e3170));goto dispatch;
L_002e3170:
 STEP(UINT32_C(0x002e3170)); /* ffb10010 sd s1,0x10(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002e3174));goto dispatch;
L_002e3174:
 STEP(UINT32_C(0x002e3174)); /* 2453c2a0 addiu s3,v0,-15712 */
 set(m,19u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffc2a0)));target=sx(UINT32_C(0x002e3178));goto dispatch;
L_002e3178:
 STEP(UINT32_C(0x002e3178)); /* ffb20020 sd s2,0x20(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);target=sx(UINT32_C(0x002e317c));goto dispatch;
L_002e317c:
 STEP(UINT32_C(0x002e317c)); /* 2471ec28 addiu s1,v1,-5080 */
 set(m,17u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffec28)));target=sx(UINT32_C(0x002e3180));goto dispatch;
L_002e3180:
 STEP(UINT32_C(0x002e3180)); /* ffbf0040 sd ra,0x40(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002e3184));goto dispatch;
L_002e3184:
 STEP(UINT32_C(0x002e3184)); /* 0000902d daddu s2,zero,zero */
 set(m,18u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002e3188));goto dispatch;
L_002e3188:
 STEP(UINT32_C(0x002e3188)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002e318c));goto dispatch;
L_002e318c:
 STEP(UINT32_C(0x002e318c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002e3190));goto dispatch;
L_002e3190:
 STEP(UINT32_C(0x002e3190)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002e3194));goto dispatch;
L_002e3194:
 STEP(UINT32_C(0x002e3194)); /* 0c0b50c4 jal 002d4310 */
 set(m,31u,UINT64_C(0x002e319c));STEP(UINT32_C(0x002e3198));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002d4310));goto dispatch;
L_002e3198:
 STEP(UINT32_C(0x002e3198)); /* 24060004 addiu a2,zero,4 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e319c));goto dispatch;
L_002e319c:
 STEP(UINT32_C(0x002e319c)); /* 1040000b beq v0,zero,002e31cc */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002e31a0));set(m,16u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002e31cc):UINT32_C(0x002e31a4));goto dispatch;}
L_002e31a0:
 STEP(UINT32_C(0x002e31a0)); /* 3c100053 lui s0,zero,0x53 */
 set(m,16u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002e31a4));goto dispatch;
L_002e31a4:
 STEP(UINT32_C(0x002e31a4)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002e31a8));goto dispatch;
L_002e31a8:
 STEP(UINT32_C(0x002e31a8)); /* 8e05c35c lw a1,-0x3ca4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffc35c),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002e31ac));goto dispatch;
L_002e31ac:
 STEP(UINT32_C(0x002e31ac)); /* 0c0b50c4 jal 002d4310 */
 set(m,31u,UINT64_C(0x002e31b4));STEP(UINT32_C(0x002e31b0));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002d4310));goto dispatch;
L_002e31b0:
 STEP(UINT32_C(0x002e31b0)); /* 24060004 addiu a2,zero,4 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e31b4));goto dispatch;
L_002e31b4:
 STEP(UINT32_C(0x002e31b4)); /* 10400005 beq v0,zero,002e31cc */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002e31b8));READ((uint32_t)lo(m,16u)+UINT32_C(0xffffc35c),&value32,4u);set(m,5u,sx(value32));target=sx(taken?UINT32_C(0x002e31cc):UINT32_C(0x002e31bc));goto dispatch;}
L_002e31b8:
 STEP(UINT32_C(0x002e31b8)); /* 8e05c35c lw a1,-0x3ca4(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0xffffc35c),&value32,4u);set(m,5u,sx(value32));target=sx(UINT32_C(0x002e31bc));goto dispatch;
L_002e31bc:
 STEP(UINT32_C(0x002e31bc)); /* 0260202d daddu a0,s3,zero */
 set(m,4u,lo(m,19u)+lo(m,0u));target=sx(UINT32_C(0x002e31c0));goto dispatch;
L_002e31c0:
 STEP(UINT32_C(0x002e31c0)); /* 0c0b50c4 jal 002d4310 */
 set(m,31u,UINT64_C(0x002e31c8));STEP(UINT32_C(0x002e31c4));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002d4310));goto dispatch;
L_002e31c4:
 STEP(UINT32_C(0x002e31c4)); /* 24060004 addiu a2,zero,4 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002e31c8));goto dispatch;
L_002e31c8:
 STEP(UINT32_C(0x002e31c8)); /* 0002902b sltu s2,zero,v0 */
 set(m,18u,lo(m,0u)<lo(m,2u));target=sx(UINT32_C(0x002e31cc));goto dispatch;
L_002e31cc:
 STEP(UINT32_C(0x002e31cc)); /* 0240102d daddu v0,s2,zero */
 set(m,2u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002e31d0));goto dispatch;
L_002e31d0:
 STEP(UINT32_C(0x002e31d0)); /* dfbf0040 ld ra,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002e31d4));goto dispatch;
L_002e31d4:
 STEP(UINT32_C(0x002e31d4)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value64,8u);set(m,19u,value64);target=sx(UINT32_C(0x002e31d8));goto dispatch;
L_002e31d8:
 STEP(UINT32_C(0x002e31d8)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002e31dc));goto dispatch;
L_002e31dc:
 STEP(UINT32_C(0x002e31dc)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002e31e0));goto dispatch;
L_002e31e0:
 STEP(UINT32_C(0x002e31e0)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002e31e4));goto dispatch;
L_002e31e4:
 STEP(UINT32_C(0x002e31e4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002e31e8));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));goto dispatch;
L_002e31e8:
 STEP(UINT32_C(0x002e31e8)); /* 27bd0050 addiu sp,sp,80 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000050)));target=sx(UINT32_C(0x002e31ec));goto dispatch;
L_002d6000:
 STEP(UINT32_C(0x002d6000)); /* 0080402d daddu t0,a0,zero */
 set(m,8u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d6004));goto dispatch;
L_002d6004:
 STEP(UINT32_C(0x002d6004)); /* 00a43825 or a3,a1,a0 */
 set(m,7u,lo(m,5u)|lo(m,4u));target=sx(UINT32_C(0x002d6008));goto dispatch;
L_002d6008:
 STEP(UINT32_C(0x002d6008)); /* 240a0010 addiu t2,zero,16 */
 set(m,10u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d600c));goto dispatch;
L_002d600c:
 STEP(UINT32_C(0x002d600c)); /* 30e20007 andi v0,a3,0x7 */
 set(m,2u,lo(m,7u) & UINT64_C(0x7));target=sx(UINT32_C(0x002d6010));goto dispatch;
L_002d6010:
 STEP(UINT32_C(0x002d6010)); /* 24090008 addiu t1,zero,8 */
 set(m,9u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6014));goto dispatch;
L_002d6014:
 STEP(UINT32_C(0x002d6014)); /* 14400054 bne v0,zero,002d6168 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6018));set(m,2u,lo(m,7u) & UINT64_C(0xf));target=sx(taken?UINT32_C(0x002d6168):UINT32_C(0x002d601c));goto dispatch;}
L_002d6018:
 STEP(UINT32_C(0x002d6018)); /* 30e2000f andi v0,a3,0xf */
 set(m,2u,lo(m,7u) & UINT64_C(0xf));target=sx(UINT32_C(0x002d601c));goto dispatch;
L_002d601c:
 STEP(UINT32_C(0x002d601c)); /* 0142480a movz t1,t2,v0 */
 if(lo(m,2u)==0u)set(m,9u,lo(m,10u));target=sx(UINT32_C(0x002d6020));goto dispatch;
L_002d6020:
 STEP(UINT32_C(0x002d6020)); /* 1440002c bne v0,zero,002d60d4 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6024));set(m,2u,lo(m,6u)<lo(m,9u));target=sx(taken?UINT32_C(0x002d60d4):UINT32_C(0x002d6028));goto dispatch;}
L_002d6024:
 STEP(UINT32_C(0x002d6024)); /* 00c9102b sltu v0,a2,t1 */
 set(m,2u,lo(m,6u)<lo(m,9u));target=sx(UINT32_C(0x002d6028));goto dispatch;
L_002d6028:
 STEP(UINT32_C(0x002d6028)); /* 1440004f bne v0,zero,002d6168 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d602c));/* nop */target=sx(taken?UINT32_C(0x002d6168):UINT32_C(0x002d6030));goto dispatch;}
L_002d602c:
 STEP(UINT32_C(0x002d602c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6030));goto dispatch;
L_002d6030:
 STEP(UINT32_C(0x002d6030)); /* 3c070101 lui a3,zero,0x101 */
 set(m,7u,sx(UINT32_C(0x01010000)));target=sx(UINT32_C(0x002d6034));goto dispatch;
L_002d6034:
 STEP(UINT32_C(0x002d6034)); /* 34e70101 ori a3,a3,0x101 */
 set(m,7u,lo(m,7u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d6038));goto dispatch;
L_002d6038:
 STEP(UINT32_C(0x002d6038)); /* 00073c38 dsll a3,a3,16 */
 set(m,7u,lo(m,7u)<<16u);target=sx(UINT32_C(0x002d603c));goto dispatch;
L_002d603c:
 STEP(UINT32_C(0x002d603c)); /* 34e70101 ori a3,a3,0x101 */
 set(m,7u,lo(m,7u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d6040));goto dispatch;
L_002d6040:
 STEP(UINT32_C(0x002d6040)); /* 00073c38 dsll a3,a3,16 */
 set(m,7u,lo(m,7u)<<16u);target=sx(UINT32_C(0x002d6044));goto dispatch;
L_002d6044:
 STEP(UINT32_C(0x002d6044)); /* 34e70101 ori a3,a3,0x101 */
 set(m,7u,lo(m,7u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d6048));goto dispatch;
L_002d6048:
 STEP(UINT32_C(0x002d6048)); /* 78a30000 lq v1,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x002d604c));goto dispatch;
L_002d604c:
 STEP(UINT32_C(0x002d604c)); /* 70e74b89 mmi 70e74b89 */
 {uint32_t out[4]={m->gpr[7][0],m->gpr[7][1],m->gpr[7][0],m->gpr[7][1]};memcpy(m->gpr[9],out,16);}target=sx(UINT32_C(0x002d6050));goto dispatch;
L_002d6050:
 STEP(UINT32_C(0x002d6050)); /* 70031ce9 mmi 70031ce9 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=~(m->gpr[0][j]|m->gpr[3][j]);memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002d6054));goto dispatch;
L_002d6054:
 STEP(UINT32_C(0x002d6054)); /* 3c078080 lui a3,zero,0x8080 */
 set(m,7u,sx(UINT32_C(0x80800000)));target=sx(UINT32_C(0x002d6058));goto dispatch;
L_002d6058:
 STEP(UINT32_C(0x002d6058)); /* 34e78080 ori a3,a3,0x8080 */
 set(m,7u,lo(m,7u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d605c));goto dispatch;
L_002d605c:
 STEP(UINT32_C(0x002d605c)); /* 00073c38 dsll a3,a3,16 */
 set(m,7u,lo(m,7u)<<16u);target=sx(UINT32_C(0x002d6060));goto dispatch;
L_002d6060:
 STEP(UINT32_C(0x002d6060)); /* 34e78080 ori a3,a3,0x8080 */
 set(m,7u,lo(m,7u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d6064));goto dispatch;
L_002d6064:
 STEP(UINT32_C(0x002d6064)); /* 00073c38 dsll a3,a3,16 */
 set(m,7u,lo(m,7u)<<16u);target=sx(UINT32_C(0x002d6068));goto dispatch;
L_002d6068:
 STEP(UINT32_C(0x002d6068)); /* 34e78080 ori a3,a3,0x8080 */
 set(m,7u,lo(m,7u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d606c));goto dispatch;
L_002d606c:
 STEP(UINT32_C(0x002d606c)); /* 70691248 mmi 70691248 */
 {uint8_t a[16],b[16],out[16];memcpy(a,m->gpr[3],16);memcpy(b,m->gpr[9],16);for(unsigned j=0;j<16;++j)out[j]=(uint8_t)(a[j]-b[j]);memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d6070));goto dispatch;
L_002d6070:
 STEP(UINT32_C(0x002d6070)); /* 70e75389 mmi 70e75389 */
 {uint32_t out[4]={m->gpr[7][0],m->gpr[7][1],m->gpr[7][0],m->gpr[7][1]};memcpy(m->gpr[10],out,16);}target=sx(UINT32_C(0x002d6074));goto dispatch;
L_002d6074:
 STEP(UINT32_C(0x002d6074)); /* 70431489 mmi 70431489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[3][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d6078));goto dispatch;
L_002d6078:
 STEP(UINT32_C(0x002d6078)); /* 704a1489 mmi 704a1489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[10][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d607c));goto dispatch;
L_002d607c:
 STEP(UINT32_C(0x002d607c)); /* 70441ba9 mmi 70441ba9 */
 {uint32_t out[4]={m->gpr[2][2],m->gpr[2][3],m->gpr[4][2],m->gpr[4][3]};memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002d6080));goto dispatch;
L_002d6080:
 STEP(UINT32_C(0x002d6080)); /* 00431825 or v1,v0,v1 */
 set(m,3u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x002d6084));goto dispatch;
L_002d6084:
 STEP(UINT32_C(0x002d6084)); /* 14600037 bne v1,zero,002d6164 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x002d6088));set(m,7u,lo(m,8u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6164):UINT32_C(0x002d608c));goto dispatch;}
L_002d6088:
 STEP(UINT32_C(0x002d6088)); /* 0100382d daddu a3,t0,zero */
 set(m,7u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d608c));goto dispatch;
L_002d608c:
 STEP(UINT32_C(0x002d608c)); /* 78a30000 lq v1,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x002d6090));goto dispatch;
L_002d6090:
 STEP(UINT32_C(0x002d6090)); /* 24c6fff0 addiu a2,a2,-16 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d6094));goto dispatch;
L_002d6094:
 STEP(UINT32_C(0x002d6094)); /* 24a50010 addiu a1,a1,16 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d6098));goto dispatch;
L_002d6098:
 STEP(UINT32_C(0x002d6098)); /* 2cc20010 sltiu v0,a2,16 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x10)));target=sx(UINT32_C(0x002d609c));goto dispatch;
L_002d609c:
 STEP(UINT32_C(0x002d609c)); /* 7ce30000 sq v1,0x0(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),m->gpr[3],16u);target=sx(UINT32_C(0x002d60a0));goto dispatch;
L_002d60a0:
 STEP(UINT32_C(0x002d60a0)); /* 14400030 bne v0,zero,002d6164 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d60a4));set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x002d6164):UINT32_C(0x002d60a8));goto dispatch;}
L_002d60a4:
 STEP(UINT32_C(0x002d60a4)); /* 24e70010 addiu a3,a3,16 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d60a8));goto dispatch;
L_002d60a8:
 STEP(UINT32_C(0x002d60a8)); /* 78a20000 lq v0,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x002d60ac));goto dispatch;
L_002d60ac:
 STEP(UINT32_C(0x002d60ac)); /* 70021ce9 mmi 70021ce9 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=~(m->gpr[0][j]|m->gpr[2][j]);memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002d60b0));goto dispatch;
L_002d60b0:
 STEP(UINT32_C(0x002d60b0)); /* 70491248 mmi 70491248 */
 {uint8_t a[16],b[16],out[16];memcpy(a,m->gpr[2],16);memcpy(b,m->gpr[9],16);for(unsigned j=0;j<16;++j)out[j]=(uint8_t)(a[j]-b[j]);memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d60b4));goto dispatch;
L_002d60b4:
 STEP(UINT32_C(0x002d60b4)); /* 70431489 mmi 70431489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[3][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d60b8));goto dispatch;
L_002d60b8:
 STEP(UINT32_C(0x002d60b8)); /* 704a1489 mmi 704a1489 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]&m->gpr[10][j];memcpy(m->gpr[2],out,16);}target=sx(UINT32_C(0x002d60bc));goto dispatch;
L_002d60bc:
 STEP(UINT32_C(0x002d60bc)); /* 70441ba9 mmi 70441ba9 */
 {uint32_t out[4]={m->gpr[2][2],m->gpr[2][3],m->gpr[4][2],m->gpr[4][3]};memcpy(m->gpr[3],out,16);}target=sx(UINT32_C(0x002d60c0));goto dispatch;
L_002d60c0:
 STEP(UINT32_C(0x002d60c0)); /* 00431025 or v0,v0,v1 */
 set(m,2u,lo(m,2u)|lo(m,3u));target=sx(UINT32_C(0x002d60c4));goto dispatch;
L_002d60c4:
 STEP(UINT32_C(0x002d60c4)); /* 5040001a beql v0,zero,002d6130 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d60c8));{uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x002d6130));}else target=sx(UINT32_C(0x002d60cc));goto dispatch;
L_002d60c8:
 STEP(UINT32_C(0x002d60c8)); /* 78a30000 lq v1,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x002d60cc));goto dispatch;
L_002d60cc:
 STEP(UINT32_C(0x002d60cc)); /* 10000026 beq zero,zero,002d6168 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x002d60d0));set(m,4u,lo(m,7u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6168):UINT32_C(0x002d60d4));goto dispatch;}
L_002d60d0:
 STEP(UINT32_C(0x002d60d0)); /* 00e0202d daddu a0,a3,zero */
 set(m,4u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d60d4));goto dispatch;
L_002d60d4:
 STEP(UINT32_C(0x002d60d4)); /* 14400024 bne v0,zero,002d6168 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d60d8));/* nop */target=sx(taken?UINT32_C(0x002d6168):UINT32_C(0x002d60dc));goto dispatch;}
L_002d60d8:
 STEP(UINT32_C(0x002d60d8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d60dc));goto dispatch;
L_002d60dc:
 STEP(UINT32_C(0x002d60dc)); /* dca30000 ld v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d60e0));goto dispatch;
L_002d60e0:
 STEP(UINT32_C(0x002d60e0)); /* 3c090101 lui t1,zero,0x101 */
 set(m,9u,sx(UINT32_C(0x01010000)));target=sx(UINT32_C(0x002d60e4));goto dispatch;
L_002d60e4:
 STEP(UINT32_C(0x002d60e4)); /* 35290101 ori t1,t1,0x101 */
 set(m,9u,lo(m,9u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d60e8));goto dispatch;
L_002d60e8:
 STEP(UINT32_C(0x002d60e8)); /* 00094c38 dsll t1,t1,16 */
 set(m,9u,lo(m,9u)<<16u);target=sx(UINT32_C(0x002d60ec));goto dispatch;
L_002d60ec:
 STEP(UINT32_C(0x002d60ec)); /* 35290101 ori t1,t1,0x101 */
 set(m,9u,lo(m,9u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d60f0));goto dispatch;
L_002d60f0:
 STEP(UINT32_C(0x002d60f0)); /* 00094c38 dsll t1,t1,16 */
 set(m,9u,lo(m,9u)<<16u);target=sx(UINT32_C(0x002d60f4));goto dispatch;
L_002d60f4:
 STEP(UINT32_C(0x002d60f4)); /* 35290101 ori t1,t1,0x101 */
 set(m,9u,lo(m,9u) | UINT64_C(0x101));target=sx(UINT32_C(0x002d60f8));goto dispatch;
L_002d60f8:
 STEP(UINT32_C(0x002d60f8)); /* 3c0a8080 lui t2,zero,0x8080 */
 set(m,10u,sx(UINT32_C(0x80800000)));target=sx(UINT32_C(0x002d60fc));goto dispatch;
L_002d60fc:
 STEP(UINT32_C(0x002d60fc)); /* 354a8080 ori t2,t2,0x8080 */
 set(m,10u,lo(m,10u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d6100));goto dispatch;
L_002d6100:
 STEP(UINT32_C(0x002d6100)); /* 000a5438 dsll t2,t2,16 */
 set(m,10u,lo(m,10u)<<16u);target=sx(UINT32_C(0x002d6104));goto dispatch;
L_002d6104:
 STEP(UINT32_C(0x002d6104)); /* 354a8080 ori t2,t2,0x8080 */
 set(m,10u,lo(m,10u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d6108));goto dispatch;
L_002d6108:
 STEP(UINT32_C(0x002d6108)); /* 000a5438 dsll t2,t2,16 */
 set(m,10u,lo(m,10u)<<16u);target=sx(UINT32_C(0x002d610c));goto dispatch;
L_002d610c:
 STEP(UINT32_C(0x002d610c)); /* 354a8080 ori t2,t2,0x8080 */
 set(m,10u,lo(m,10u) | UINT64_C(0x8080));target=sx(UINT32_C(0x002d6110));goto dispatch;
L_002d6110:
 STEP(UINT32_C(0x002d6110)); /* 0069102f dsubu v0,v1,t1 */
 set(m,2u,lo(m,3u)-lo(m,9u));target=sx(UINT32_C(0x002d6114));goto dispatch;
L_002d6114:
 STEP(UINT32_C(0x002d6114)); /* 00031827 nor v1,zero,v1 */
 set(m,3u,~(lo(m,0u)|lo(m,3u)));target=sx(UINT32_C(0x002d6118));goto dispatch;
L_002d6118:
 STEP(UINT32_C(0x002d6118)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d611c));goto dispatch;
L_002d611c:
 STEP(UINT32_C(0x002d611c)); /* 004a1024 and v0,v0,t2 */
 set(m,2u,lo(m,2u)&lo(m,10u));target=sx(UINT32_C(0x002d6120));goto dispatch;
L_002d6120:
 STEP(UINT32_C(0x002d6120)); /* 14400010 bne v0,zero,002d6164 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6124));set(m,7u,lo(m,8u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6164):UINT32_C(0x002d6128));goto dispatch;}
L_002d6124:
 STEP(UINT32_C(0x002d6124)); /* 0100382d daddu a3,t0,zero */
 set(m,7u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d6128));goto dispatch;
L_002d6128:
 STEP(UINT32_C(0x002d6128)); /* dca30000 ld v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d612c));goto dispatch;
L_002d612c:
 STEP(UINT32_C(0x002d612c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d6130));goto dispatch;
L_002d6130:
 STEP(UINT32_C(0x002d6130)); /* 24c6fff8 addiu a2,a2,-8 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff8)));target=sx(UINT32_C(0x002d6134));goto dispatch;
L_002d6134:
 STEP(UINT32_C(0x002d6134)); /* 24a50008 addiu a1,a1,8 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6138));goto dispatch;
L_002d6138:
 STEP(UINT32_C(0x002d6138)); /* 2cc20008 sltiu v0,a2,8 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x8)));target=sx(UINT32_C(0x002d613c));goto dispatch;
L_002d613c:
 STEP(UINT32_C(0x002d613c)); /* fce30000 sd v1,0x0(a3) */
 value64=lo(m,3u);WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d6140));goto dispatch;
L_002d6140:
 STEP(UINT32_C(0x002d6140)); /* 14400008 bne v0,zero,002d6164 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6144));set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002d6164):UINT32_C(0x002d6148));goto dispatch;}
L_002d6144:
 STEP(UINT32_C(0x002d6144)); /* 24e70008 addiu a3,a3,8 */
 set(m,7u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002d6148));goto dispatch;
L_002d6148:
 STEP(UINT32_C(0x002d6148)); /* dca20000 ld v0,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,2u,value64);target=sx(UINT32_C(0x002d614c));goto dispatch;
L_002d614c:
 STEP(UINT32_C(0x002d614c)); /* 00021827 nor v1,zero,v0 */
 set(m,3u,~(lo(m,0u)|lo(m,2u)));target=sx(UINT32_C(0x002d6150));goto dispatch;
L_002d6150:
 STEP(UINT32_C(0x002d6150)); /* 0049102f dsubu v0,v0,t1 */
 set(m,2u,lo(m,2u)-lo(m,9u));target=sx(UINT32_C(0x002d6154));goto dispatch;
L_002d6154:
 STEP(UINT32_C(0x002d6154)); /* 00431024 and v0,v0,v1 */
 set(m,2u,lo(m,2u)&lo(m,3u));target=sx(UINT32_C(0x002d6158));goto dispatch;
L_002d6158:
 STEP(UINT32_C(0x002d6158)); /* 004a1024 and v0,v0,t2 */
 set(m,2u,lo(m,2u)&lo(m,10u));target=sx(UINT32_C(0x002d615c));goto dispatch;
L_002d615c:
 STEP(UINT32_C(0x002d615c)); /* 5040fff4 beql v0,zero,002d6130 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002d6160));READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d6130));}else target=sx(UINT32_C(0x002d6164));goto dispatch;
L_002d6160:
 STEP(UINT32_C(0x002d6160)); /* dca30000 ld v1,0x0(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&value64,8u);set(m,3u,value64);target=sx(UINT32_C(0x002d6164));goto dispatch;
L_002d6164:
 STEP(UINT32_C(0x002d6164)); /* 00e0202d daddu a0,a3,zero */
 set(m,4u,lo(m,7u)+lo(m,0u));target=sx(UINT32_C(0x002d6168));goto dispatch;
L_002d6168:
 STEP(UINT32_C(0x002d6168)); /* 10c00012 beq a2,zero,002d61b4 */
 {int taken=(lo(m,6u)==lo(m,0u));STEP(UINT32_C(0x002d616c));set(m,2u,lo(m,6u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d61b4):UINT32_C(0x002d6170));goto dispatch;}
L_002d616c:
 STEP(UINT32_C(0x002d616c)); /* 00c0102d daddu v0,a2,zero */
 set(m,2u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d6170));goto dispatch;
L_002d6170:
 STEP(UINT32_C(0x002d6170)); /* 90a20000 lbu v0,0x0(a1) */
 {uint8_t byte;READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002d6174));goto dispatch;
L_002d6174:
 STEP(UINT32_C(0x002d6174)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6178));goto dispatch;
L_002d6178:
 STEP(UINT32_C(0x002d6178)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d617c));goto dispatch;
L_002d617c:
 STEP(UINT32_C(0x002d617c)); /* a0820000 sb v0,0x0(a0) */
 {uint8_t byte=(uint8_t)lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d6180));goto dispatch;
L_002d6180:
 STEP(UINT32_C(0x002d6180)); /* 00021600 sll v0,v0,24 */
 set(m,2u,sx((uint32_t)lo(m,2u)<<24u));target=sx(UINT32_C(0x002d6184));goto dispatch;
L_002d6184:
 STEP(UINT32_C(0x002d6184)); /* 1440fff8 bne v0,zero,002d6168 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6188));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d6168):UINT32_C(0x002d618c));goto dispatch;}
L_002d6188:
 STEP(UINT32_C(0x002d6188)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d618c));goto dispatch;
L_002d618c:
 STEP(UINT32_C(0x002d618c)); /* 00c0102d daddu v0,a2,zero */
 set(m,2u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d6190));goto dispatch;
L_002d6190:
 STEP(UINT32_C(0x002d6190)); /* 10400008 beq v0,zero,002d61b4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x002d6194));set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(taken?UINT32_C(0x002d61b4):UINT32_C(0x002d6198));goto dispatch;}
L_002d6194:
 STEP(UINT32_C(0x002d6194)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d6198));goto dispatch;
L_002d6198:
 STEP(UINT32_C(0x002d6198)); /* a0800000 sb zero,0x0(a0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002d619c));goto dispatch;
L_002d619c:
 STEP(UINT32_C(0x002d619c)); /* 00c0102d daddu v0,a2,zero */
 set(m,2u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d61a0));goto dispatch;
L_002d61a0:
 STEP(UINT32_C(0x002d61a0)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d61a4));goto dispatch;
L_002d61a4:
 STEP(UINT32_C(0x002d61a4)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d61a8));goto dispatch;
L_002d61a8:
 STEP(UINT32_C(0x002d61a8)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d61ac));goto dispatch;
L_002d61ac:
 STEP(UINT32_C(0x002d61ac)); /* 1440fffa bne v0,zero,002d6198 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d61b0));/* nop */target=sx(taken?UINT32_C(0x002d6198):UINT32_C(0x002d61b4));goto dispatch;}
L_002d61b0:
 STEP(UINT32_C(0x002d61b0)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d61b4));goto dispatch;
L_002d61b4:
 STEP(UINT32_C(0x002d61b4)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d61b8));set(m,2u,lo(m,8u)+lo(m,0u));goto dispatch;
L_002d61b8:
 STEP(UINT32_C(0x002d61b8)); /* 0100102d daddu v0,t0,zero */
 set(m,2u,lo(m,8u)+lo(m,0u));target=sx(UINT32_C(0x002d61bc));goto dispatch;
L_002d4310:
 STEP(UINT32_C(0x002d4310)); /* 2cc20010 sltiu v0,a2,16 */
 set(m,2u,(lo(m,6u)<UINT64_C(0x10)));target=sx(UINT32_C(0x002d4314));goto dispatch;
L_002d4314:
 STEP(UINT32_C(0x002d4314)); /* 14400011 bne v0,zero,002d435c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d4318));set(m,2u,lo(m,4u)|lo(m,5u));target=sx(taken?UINT32_C(0x002d435c):UINT32_C(0x002d431c));goto dispatch;}
L_002d4318:
 STEP(UINT32_C(0x002d4318)); /* 00851025 or v0,a0,a1 */
 set(m,2u,lo(m,4u)|lo(m,5u));target=sx(UINT32_C(0x002d431c));goto dispatch;
L_002d431c:
 STEP(UINT32_C(0x002d431c)); /* 3042000f andi v0,v0,0xf */
 set(m,2u,lo(m,2u) & UINT64_C(0xf));target=sx(UINT32_C(0x002d4320));goto dispatch;
L_002d4320:
 STEP(UINT32_C(0x002d4320)); /* 1440000e bne v0,zero,002d435c */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d4324));/* nop */target=sx(taken?UINT32_C(0x002d435c):UINT32_C(0x002d4328));goto dispatch;}
L_002d4324:
 STEP(UINT32_C(0x002d4324)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4328));goto dispatch;
L_002d4328:
 STEP(UINT32_C(0x002d4328)); /* 78830000 lq v1,0x0(a0) */
 {uint32_t q[4];READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[3],q,16u);}target=sx(UINT32_C(0x002d432c));goto dispatch;
L_002d432c:
 STEP(UINT32_C(0x002d432c)); /* 2cc70020 sltiu a3,a2,32 */
 set(m,7u,(lo(m,6u)<UINT64_C(0x20)));target=sx(UINT32_C(0x002d4330));goto dispatch;
L_002d4330:
 STEP(UINT32_C(0x002d4330)); /* 78a20000 lq v0,0x0(a1) */
 {uint32_t q[4];READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),q,16u);memcpy(m->gpr[2],q,16u);}target=sx(UINT32_C(0x002d4334));goto dispatch;
L_002d4334:
 STEP(UINT32_C(0x002d4334)); /* 24840010 addiu a0,a0,16 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d4338));goto dispatch;
L_002d4338:
 STEP(UINT32_C(0x002d4338)); /* 704344c9 mmi 704344c9 */
 {uint32_t out[4];for(unsigned j=0;j<4;++j)out[j]=m->gpr[2][j]^m->gpr[3][j];memcpy(m->gpr[8],out,16);}target=sx(UINT32_C(0x002d433c));goto dispatch;
L_002d433c:
 STEP(UINT32_C(0x002d433c)); /* 24a20010 addiu v0,a1,16 */
 set(m,2u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002d4340));goto dispatch;
L_002d4340:
 STEP(UINT32_C(0x002d4340)); /* 710753a9 mmi 710753a9 */
 {uint32_t out[4]={m->gpr[8][2],m->gpr[8][3],m->gpr[7][2],m->gpr[7][3]};memcpy(m->gpr[10],out,16);}target=sx(UINT32_C(0x002d4344));goto dispatch;
L_002d4344:
 STEP(UINT32_C(0x002d4344)); /* 01484825 or t1,t2,t0 */
 set(m,9u,lo(m,10u)|lo(m,8u));target=sx(UINT32_C(0x002d4348));goto dispatch;
L_002d4348:
 STEP(UINT32_C(0x002d4348)); /* 0049280a movz a1,v0,t1 */
 if(lo(m,9u)==0u)set(m,5u,lo(m,2u));target=sx(UINT32_C(0x002d434c));goto dispatch;
L_002d434c:
 STEP(UINT32_C(0x002d434c)); /* 55200003 bnel t1,zero,002d435c */
 if(lo(m,9u)!=lo(m,0u)){STEP(UINT32_C(0x002d4350));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d435c));}else target=sx(UINT32_C(0x002d4354));goto dispatch;
L_002d4350:
 STEP(UINT32_C(0x002d4350)); /* 2484fff0 addiu a0,a0,-16 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d4354));goto dispatch;
L_002d4354:
 STEP(UINT32_C(0x002d4354)); /* 10e0fff4 beq a3,zero,002d4328 */
 {int taken=(lo(m,7u)==lo(m,0u));STEP(UINT32_C(0x002d4358));set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff0)));target=sx(taken?UINT32_C(0x002d4328):UINT32_C(0x002d435c));goto dispatch;}
L_002d4358:
 STEP(UINT32_C(0x002d4358)); /* 24c6fff0 addiu a2,a2,-16 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002d435c));goto dispatch;
L_002d435c:
 STEP(UINT32_C(0x002d435c)); /* 3c02ffff lui v0,zero,0xffff */
 set(m,2u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002d4360));goto dispatch;
L_002d4360:
 STEP(UINT32_C(0x002d4360)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4364));goto dispatch;
L_002d4364:
 STEP(UINT32_C(0x002d4364)); /* 3442ffff ori v0,v0,0xffff */
 set(m,2u,lo(m,2u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002d4368));goto dispatch;
L_002d4368:
 STEP(UINT32_C(0x002d4368)); /* 10c2000c beq a2,v0,002d439c */
 {int taken=(lo(m,6u)==lo(m,2u));STEP(UINT32_C(0x002d436c));/* nop */target=sx(taken?UINT32_C(0x002d439c):UINT32_C(0x002d4370));goto dispatch;}
L_002d436c:
 STEP(UINT32_C(0x002d436c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d4370));goto dispatch;
L_002d4370:
 STEP(UINT32_C(0x002d4370)); /* 3c07ffff lui a3,zero,0xffff */
 set(m,7u,sx(UINT32_C(0xffff0000)));target=sx(UINT32_C(0x002d4374));goto dispatch;
L_002d4374:
 STEP(UINT32_C(0x002d4374)); /* 34e7ffff ori a3,a3,0xffff */
 set(m,7u,lo(m,7u) | UINT64_C(0xffff));target=sx(UINT32_C(0x002d4378));goto dispatch;
L_002d4378:
 STEP(UINT32_C(0x002d4378)); /* 90830000 lbu v1,0x0(a0) */
 {uint8_t byte;READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&byte,1u);set(m,3u,byte);}target=sx(UINT32_C(0x002d437c));goto dispatch;
L_002d437c:
 STEP(UINT32_C(0x002d437c)); /* 90a20000 lbu v0,0x0(a1) */
 {uint8_t byte;READ((uint32_t)lo(m,5u)+UINT32_C(0x00000000),&byte,1u);set(m,2u,byte);}target=sx(UINT32_C(0x002d4380));goto dispatch;
L_002d4380:
 STEP(UINT32_C(0x002d4380)); /* 10620003 beq v1,v0,002d4390 */
 {int taken=(lo(m,3u)==lo(m,2u));STEP(UINT32_C(0x002d4384));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d4390):UINT32_C(0x002d4388));goto dispatch;}
L_002d4384:
 STEP(UINT32_C(0x002d4384)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d4388));goto dispatch;
L_002d4388:
 STEP(UINT32_C(0x002d4388)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d438c));set(m,2u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,2u)));goto dispatch;
L_002d438c:
 STEP(UINT32_C(0x002d438c)); /* 00621023 subu v0,v1,v0 */
 set(m,2u,sx((uint32_t)lo(m,3u)-(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002d4390));goto dispatch;
L_002d4390:
 STEP(UINT32_C(0x002d4390)); /* 24c6ffff addiu a2,a2,-1 */
 set(m,6u,sx((uint32_t)lo(m,6u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002d4394));goto dispatch;
L_002d4394:
 STEP(UINT32_C(0x002d4394)); /* 14c7fff8 bne a2,a3,002d4378 */
 {int taken=(lo(m,6u)!=lo(m,7u));STEP(UINT32_C(0x002d4398));set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(taken?UINT32_C(0x002d4378):UINT32_C(0x002d439c));goto dispatch;}
L_002d4398:
 STEP(UINT32_C(0x002d4398)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d439c));goto dispatch;
L_002d439c:
 STEP(UINT32_C(0x002d439c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d43a0));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_002d43a0:
 STEP(UINT32_C(0x002d43a0)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d43a4));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

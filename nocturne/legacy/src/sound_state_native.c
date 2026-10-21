#include "sound_state_native.h"
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
uint32_t nocturneSoundStateResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
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
 case UINT32_C(0x002c0e90):goto L_002c0e90;
 case UINT32_C(0x002c0e94):goto L_002c0e94;
 case UINT32_C(0x002c0e98):goto L_002c0e98;
 case UINT32_C(0x002c0e9c):goto L_002c0e9c;
 case UINT32_C(0x002c0ea0):goto L_002c0ea0;
 case UINT32_C(0x002c0ea4):goto L_002c0ea4;
 case UINT32_C(0x002c0ea8):goto L_002c0ea8;
 case UINT32_C(0x002c0eac):goto L_002c0eac;
 case UINT32_C(0x002c0eb0):goto L_002c0eb0;
 case UINT32_C(0x002c0eb4):goto L_002c0eb4;
 case UINT32_C(0x002c0eb8):goto L_002c0eb8;
 case UINT32_C(0x002c0ebc):goto L_002c0ebc;
 case UINT32_C(0x002c0ec0):goto L_002c0ec0;
 case UINT32_C(0x002c0ec4):goto L_002c0ec4;
 case UINT32_C(0x002c0ec8):goto L_002c0ec8;
 case UINT32_C(0x002c0ecc):goto L_002c0ecc;
 case UINT32_C(0x002c0ed0):goto L_002c0ed0;
 case UINT32_C(0x002c0ed4):goto L_002c0ed4;
 case UINT32_C(0x002c0ed8):goto L_002c0ed8;
 case UINT32_C(0x002c0edc):goto L_002c0edc;
 case UINT32_C(0x002c0ee0):goto L_002c0ee0;
 case UINT32_C(0x002c0ee4):goto L_002c0ee4;
 case UINT32_C(0x002c0ee8):goto L_002c0ee8;
 case UINT32_C(0x002c0eec):goto L_002c0eec;
 case UINT32_C(0x002c0ef0):goto L_002c0ef0;
 case UINT32_C(0x002c0ef4):goto L_002c0ef4;
 case UINT32_C(0x002c0ef8):goto L_002c0ef8;
 case UINT32_C(0x002c0efc):goto L_002c0efc;
 case UINT32_C(0x002c0f00):goto L_002c0f00;
 case UINT32_C(0x002c0f04):goto L_002c0f04;
 case UINT32_C(0x002c0f08):goto L_002c0f08;
 case UINT32_C(0x002c0f0c):goto L_002c0f0c;
 case UINT32_C(0x002c0f10):goto L_002c0f10;
 case UINT32_C(0x002c0f14):goto L_002c0f14;
 case UINT32_C(0x002c0f18):goto L_002c0f18;
 case UINT32_C(0x002c0f1c):goto L_002c0f1c;
 case UINT32_C(0x002c0f20):goto L_002c0f20;
 case UINT32_C(0x002c0f24):goto L_002c0f24;
 case UINT32_C(0x002c13d8):goto L_002c13d8;
 case UINT32_C(0x002c13dc):goto L_002c13dc;
 case UINT32_C(0x002c13e0):goto L_002c13e0;
 case UINT32_C(0x002c13e4):goto L_002c13e4;
 case UINT32_C(0x002c13e8):goto L_002c13e8;
 case UINT32_C(0x002c13ec):goto L_002c13ec;
 case UINT32_C(0x002c13f0):goto L_002c13f0;
 case UINT32_C(0x002c13f4):goto L_002c13f4;
 case UINT32_C(0x002c13f8):goto L_002c13f8;
 case UINT32_C(0x002c13fc):goto L_002c13fc;
 case UINT32_C(0x002c1400):goto L_002c1400;
 case UINT32_C(0x002c1404):goto L_002c1404;
 case UINT32_C(0x002c1408):goto L_002c1408;
 case UINT32_C(0x002c140c):goto L_002c140c;
 case UINT32_C(0x002c1410):goto L_002c1410;
 case UINT32_C(0x002c1414):goto L_002c1414;
 case UINT32_C(0x002c1418):goto L_002c1418;
 case UINT32_C(0x002c141c):goto L_002c141c;
 case UINT32_C(0x002c1420):goto L_002c1420;
 case UINT32_C(0x002c1424):goto L_002c1424;
 case UINT32_C(0x002c1428):goto L_002c1428;
 case UINT32_C(0x002c142c):goto L_002c142c;
 case UINT32_C(0x002c1430):goto L_002c1430;
 case UINT32_C(0x002c1434):goto L_002c1434;
 case UINT32_C(0x002c1438):goto L_002c1438;
 case UINT32_C(0x002c143c):goto L_002c143c;
 case UINT32_C(0x002c1440):goto L_002c1440;
 case UINT32_C(0x002c1444):goto L_002c1444;
 case UINT32_C(0x002c1448):goto L_002c1448;
 case UINT32_C(0x002c144c):goto L_002c144c;
 case UINT32_C(0x002c1450):goto L_002c1450;
 case UINT32_C(0x002c1454):goto L_002c1454;
 case UINT32_C(0x002c1458):goto L_002c1458;
 case UINT32_C(0x002c145c):goto L_002c145c;
 case UINT32_C(0x002c1460):goto L_002c1460;
 case UINT32_C(0x002c1464):goto L_002c1464;
 case UINT32_C(0x002c1468):goto L_002c1468;
 case UINT32_C(0x002c146c):goto L_002c146c;
 case UINT32_C(0x002c1470):goto L_002c1470;
 case UINT32_C(0x002c1474):goto L_002c1474;
 case UINT32_C(0x002c1478):goto L_002c1478;
 case UINT32_C(0x002c147c):goto L_002c147c;
 case UINT32_C(0x002c1480):goto L_002c1480;
 case UINT32_C(0x002c1484):goto L_002c1484;
 case UINT32_C(0x002c1488):goto L_002c1488;
 case UINT32_C(0x002c1490):goto L_002c1490;
 case UINT32_C(0x002c1494):goto L_002c1494;
 case UINT32_C(0x002c1498):goto L_002c1498;
 case UINT32_C(0x002c149c):goto L_002c149c;
 case UINT32_C(0x002c14a0):goto L_002c14a0;
 case UINT32_C(0x002c14a4):goto L_002c14a4;
 case UINT32_C(0x002c14a8):goto L_002c14a8;
 case UINT32_C(0x002c14ac):goto L_002c14ac;
 case UINT32_C(0x002c14b0):goto L_002c14b0;
 case UINT32_C(0x002c14b4):goto L_002c14b4;
 case UINT32_C(0x002c14b8):goto L_002c14b8;
 case UINT32_C(0x002c14bc):goto L_002c14bc;
 case UINT32_C(0x002c14c0):goto L_002c14c0;
 case UINT32_C(0x002c14c4):goto L_002c14c4;
 case UINT32_C(0x002c14c8):goto L_002c14c8;
 case UINT32_C(0x002c14cc):goto L_002c14cc;
 case UINT32_C(0x002c14d0):goto L_002c14d0;
 case UINT32_C(0x002c14d4):goto L_002c14d4;
 case UINT32_C(0x002c14d8):goto L_002c14d8;
 case UINT32_C(0x002c14dc):goto L_002c14dc;
 case UINT32_C(0x002c14e0):goto L_002c14e0;
 case UINT32_C(0x002c14e4):goto L_002c14e4;
 case UINT32_C(0x002c14e8):goto L_002c14e8;
 case UINT32_C(0x002c14ec):goto L_002c14ec;
 case UINT32_C(0x002c14f0):goto L_002c14f0;
 case UINT32_C(0x002c14f4):goto L_002c14f4;
 case UINT32_C(0x002c14f8):goto L_002c14f8;
 case UINT32_C(0x002c14fc):goto L_002c14fc;
 case UINT32_C(0x002c1500):goto L_002c1500;
 case UINT32_C(0x002c1504):goto L_002c1504;
 case UINT32_C(0x002c1508):goto L_002c1508;
 case UINT32_C(0x002c150c):goto L_002c150c;
 case UINT32_C(0x002c1510):goto L_002c1510;
 case UINT32_C(0x002c1514):goto L_002c1514;
 case UINT32_C(0x002c1518):goto L_002c1518;
 case UINT32_C(0x002c151c):goto L_002c151c;
 case UINT32_C(0x002c1520):goto L_002c1520;
 case UINT32_C(0x002c1524):goto L_002c1524;
 case UINT32_C(0x002c1528):goto L_002c1528;
 case UINT32_C(0x002c152c):goto L_002c152c;
 case UINT32_C(0x002c1530):goto L_002c1530;
 case UINT32_C(0x002c1534):goto L_002c1534;
 case UINT32_C(0x002c1538):goto L_002c1538;
 case UINT32_C(0x002c153c):goto L_002c153c;
 case UINT32_C(0x002c1540):goto L_002c1540;
 case UINT32_C(0x002c1544):goto L_002c1544;
 case UINT32_C(0x002c1548):goto L_002c1548;
 case UINT32_C(0x002c154c):goto L_002c154c;
 case UINT32_C(0x002c1550):goto L_002c1550;
 case UINT32_C(0x002c1554):goto L_002c1554;
 case UINT32_C(0x002c1558):goto L_002c1558;
 case UINT32_C(0x002c155c):goto L_002c155c;
 case UINT32_C(0x002c1560):goto L_002c1560;
 case UINT32_C(0x002c1564):goto L_002c1564;
 case UINT32_C(0x002c1568):goto L_002c1568;
 case UINT32_C(0x002c156c):goto L_002c156c;
 case UINT32_C(0x002c1570):goto L_002c1570;
 case UINT32_C(0x002c1574):goto L_002c1574;
 case UINT32_C(0x002c1240):goto L_002c1240;
 case UINT32_C(0x002c1244):goto L_002c1244;
 case UINT32_C(0x002c1248):goto L_002c1248;
 case UINT32_C(0x002c124c):goto L_002c124c;
 case UINT32_C(0x002c1250):goto L_002c1250;
 case UINT32_C(0x002c1254):goto L_002c1254;
 case UINT32_C(0x002c1258):goto L_002c1258;
 case UINT32_C(0x002c125c):goto L_002c125c;
 case UINT32_C(0x002c1260):goto L_002c1260;
 case UINT32_C(0x002c1264):goto L_002c1264;
 case UINT32_C(0x002c1268):goto L_002c1268;
 case UINT32_C(0x002c126c):goto L_002c126c;
 case UINT32_C(0x002c1270):goto L_002c1270;
 case UINT32_C(0x002c1238):goto L_002c1238;
 case UINT32_C(0x002c123c):goto L_002c123c;
 case UINT32_C(0x002d4748):goto L_002d4748;
 case UINT32_C(0x002d474c):goto L_002d474c;
 case UINT32_C(0x002d4750):goto L_002d4750;
 case UINT32_C(0x002d4754):goto L_002d4754;
 case UINT32_C(0x002d4758):goto L_002d4758;
 case UINT32_C(0x002d475c):goto L_002d475c;
 case UINT32_C(0x002d4760):goto L_002d4760;
 case UINT32_C(0x002d4764):goto L_002d4764;
 case UINT32_C(0x002d4768):goto L_002d4768;
 case UINT32_C(0x002d476c):goto L_002d476c;
 case UINT32_C(0x002d4770):goto L_002d4770;
 case UINT32_C(0x002d4774):goto L_002d4774;
 case UINT32_C(0x002d4778):goto L_002d4778;
 case UINT32_C(0x002d477c):goto L_002d477c;
 case UINT32_C(0x002d4780):goto L_002d4780;
 case UINT32_C(0x002d4784):goto L_002d4784;
 case UINT32_C(0x002d4788):goto L_002d4788;
 case UINT32_C(0x002d478c):goto L_002d478c;
 case UINT32_C(0x002d4790):goto L_002d4790;
 case UINT32_C(0x002d4794):goto L_002d4794;
 case UINT32_C(0x002d4798):goto L_002d4798;
 case UINT32_C(0x002d479c):goto L_002d479c;
 case UINT32_C(0x002d47a0):goto L_002d47a0;
 case UINT32_C(0x002d47a4):goto L_002d47a4;
 case UINT32_C(0x002d47a8):goto L_002d47a8;
 case UINT32_C(0x002d47ac):goto L_002d47ac;
 case UINT32_C(0x002d47b0):goto L_002d47b0;
 case UINT32_C(0x002d47b4):goto L_002d47b4;
 case UINT32_C(0x002d6600):goto L_002d6600;
 case UINT32_C(0x002d6604):goto L_002d6604;
 case UINT32_C(0x002d6608):goto L_002d6608;
 case UINT32_C(0x002d660c):goto L_002d660c;
 case UINT32_C(0x002d6610):goto L_002d6610;
 case UINT32_C(0x002d6614):goto L_002d6614;
 case UINT32_C(0x002d6618):goto L_002d6618;
 case UINT32_C(0x002d661c):goto L_002d661c;
 case UINT32_C(0x002d6620):goto L_002d6620;
 case UINT32_C(0x002d6624):goto L_002d6624;
 case UINT32_C(0x002d6628):goto L_002d6628;
 case UINT32_C(0x002d662c):goto L_002d662c;
 case UINT32_C(0x002d6630):goto L_002d6630;
 case UINT32_C(0x002d6634):goto L_002d6634;
 case UINT32_C(0x002d6638):goto L_002d6638;
 case UINT32_C(0x002d663c):goto L_002d663c;
 case UINT32_C(0x002d6640):goto L_002d6640;
 case UINT32_C(0x002d6644):goto L_002d6644;
 case UINT32_C(0x002d6648):goto L_002d6648;
 case UINT32_C(0x002d664c):goto L_002d664c;
 case UINT32_C(0x002d6650):goto L_002d6650;
 case UINT32_C(0x002d6654):goto L_002d6654;
 case UINT32_C(0x002d6658):goto L_002d6658;
 case UINT32_C(0x002d665c):goto L_002d665c;
 case UINT32_C(0x002d6660):goto L_002d6660;
 case UINT32_C(0x002d6664):goto L_002d6664;
 case UINT32_C(0x002d6668):goto L_002d6668;
 case UINT32_C(0x002d666c):goto L_002d666c;
 case UINT32_C(0x002d6670):goto L_002d6670;
 case UINT32_C(0x002d9908):goto L_002d9908;
 case UINT32_C(0x002d990c):goto L_002d990c;
 case UINT32_C(0x002d9910):goto L_002d9910;
 case UINT32_C(0x002d9914):goto L_002d9914;
 case UINT32_C(0x002d9918):goto L_002d9918;
 case UINT32_C(0x002d991c):goto L_002d991c;
 case UINT32_C(0x002d9920):goto L_002d9920;
 case UINT32_C(0x002d9924):goto L_002d9924;
 case UINT32_C(0x002d9928):goto L_002d9928;
 case UINT32_C(0x002d992c):goto L_002d992c;
 case UINT32_C(0x002d9930):goto L_002d9930;
 case UINT32_C(0x002d9934):goto L_002d9934;
 case UINT32_C(0x002d9938):goto L_002d9938;
 case UINT32_C(0x002d993c):goto L_002d993c;
 case UINT32_C(0x002d9940):goto L_002d9940;
 case UINT32_C(0x002d9944):goto L_002d9944;
 case UINT32_C(0x002d9948):goto L_002d9948;
 case UINT32_C(0x002d994c):goto L_002d994c;
 case UINT32_C(0x002d9950):goto L_002d9950;
 case UINT32_C(0x002d9954):goto L_002d9954;
 case UINT32_C(0x002d9958):goto L_002d9958;
 case UINT32_C(0x002d995c):goto L_002d995c;
 case UINT32_C(0x002d9960):goto L_002d9960;
 case UINT32_C(0x002d9964):goto L_002d9964;
 case UINT32_C(0x002d9968):goto L_002d9968;
 case UINT32_C(0x002d996c):goto L_002d996c;
 case UINT32_C(0x002d9970):goto L_002d9970;
 case UINT32_C(0x002d9974):goto L_002d9974;
 case UINT32_C(0x002d9978):goto L_002d9978;
 case UINT32_C(0x002d997c):goto L_002d997c;
 case UINT32_C(0x002d9980):goto L_002d9980;
 case UINT32_C(0x002d9984):goto L_002d9984;
 case UINT32_C(0x002d9988):goto L_002d9988;
 case UINT32_C(0x002d998c):goto L_002d998c;
 case UINT32_C(0x002d9990):goto L_002d9990;
 case UINT32_C(0x002d96f8):goto L_002d96f8;
 case UINT32_C(0x002d96fc):goto L_002d96fc;
 case UINT32_C(0x002d9700):goto L_002d9700;
 case UINT32_C(0x002d9704):goto L_002d9704;
 case UINT32_C(0x002d9708):goto L_002d9708;
 case UINT32_C(0x002d970c):goto L_002d970c;
 case UINT32_C(0x002d9710):goto L_002d9710;
 case UINT32_C(0x002d9714):goto L_002d9714;
 case UINT32_C(0x002d9718):goto L_002d9718;
 case UINT32_C(0x002d971c):goto L_002d971c;
 case UINT32_C(0x002d9720):goto L_002d9720;
 case UINT32_C(0x002d9724):goto L_002d9724;
 case UINT32_C(0x002d9728):goto L_002d9728;
 case UINT32_C(0x002d972c):goto L_002d972c;
 case UINT32_C(0x002d9730):goto L_002d9730;
 case UINT32_C(0x002d9734):goto L_002d9734;
 case UINT32_C(0x002d9738):goto L_002d9738;
 case UINT32_C(0x002d973c):goto L_002d973c;
 case UINT32_C(0x002d9740):goto L_002d9740;
 case UINT32_C(0x002d9744):goto L_002d9744;
 case UINT32_C(0x002d9748):goto L_002d9748;
 case UINT32_C(0x002d974c):goto L_002d974c;
 case UINT32_C(0x002d9750):goto L_002d9750;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(m->pc));}
L_002c0e90:
 STEP(UINT32_C(0x002c0e90)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002c0e94));goto dispatch;
L_002c0e94:
 STEP(UINT32_C(0x002c0e94)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c0e98));goto dispatch;
L_002c0e98:
 STEP(UINT32_C(0x002c0e98)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c0e9c));goto dispatch;
L_002c0e9c:
 STEP(UINT32_C(0x002c0e9c)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002c0ea0));goto dispatch;
L_002c0ea0:
 STEP(UINT32_C(0x002c0ea0)); /* 0c0b8ae6 jal 002e2b98 */
 set(m,31u,UINT64_C(0x002c0ea8));STEP(UINT32_C(0x002c0ea4));set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002e2b98));goto dispatch;
L_002c0ea4:
 STEP(UINT32_C(0x002c0ea4)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002c0ea8));goto dispatch;
L_002c0ea8:
 STEP(UINT32_C(0x002c0ea8)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c0eac));goto dispatch;
L_002c0eac:
 STEP(UINT32_C(0x002c0eac)); /* 0040882d daddu s1,v0,zero */
 set(m,17u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c0eb0));goto dispatch;
L_002c0eb0:
 STEP(UINT32_C(0x002c0eb0)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c0eb8));STEP(UINT32_C(0x002c0eb4));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff98a0)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c0eb4:
 STEP(UINT32_C(0x002c0eb4)); /* 248498a0 addiu a0,a0,-26464 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff98a0)));target=sx(UINT32_C(0x002c0eb8));goto dispatch;
L_002c0eb8:
 STEP(UINT32_C(0x002c0eb8)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c0ebc));goto dispatch;
L_002c0ebc:
 STEP(UINT32_C(0x002c0ebc)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c0ec0));goto dispatch;
L_002c0ec0:
 STEP(UINT32_C(0x002c0ec0)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c0ec8));STEP(UINT32_C(0x002c0ec4));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff98b0)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c0ec4:
 STEP(UINT32_C(0x002c0ec4)); /* 248498b0 addiu a0,a0,-26448 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff98b0)));target=sx(UINT32_C(0x002c0ec8));goto dispatch;
L_002c0ec8:
 STEP(UINT32_C(0x002c0ec8)); /* 0c0b8ba0 jal 002e2e80 */
 set(m,31u,UINT64_C(0x002c0ed0));STEP(UINT32_C(0x002c0ecc));/* nop */target=sx(UINT32_C(0x002e2e80));goto dispatch;
L_002c0ecc:
 STEP(UINT32_C(0x002c0ecc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0ed0));goto dispatch;
L_002c0ed0:
 STEP(UINT32_C(0x002c0ed0)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c0ed4));goto dispatch;
L_002c0ed4:
 STEP(UINT32_C(0x002c0ed4)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c0ed8));goto dispatch;
L_002c0ed8:
 STEP(UINT32_C(0x002c0ed8)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c0ee0));STEP(UINT32_C(0x002c0edc));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff98d8)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c0edc:
 STEP(UINT32_C(0x002c0edc)); /* 248498d8 addiu a0,a0,-26408 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff98d8)));target=sx(UINT32_C(0x002c0ee0));goto dispatch;
L_002c0ee0:
 STEP(UINT32_C(0x002c0ee0)); /* 0c0b8b84 jal 002e2e10 */
 set(m,31u,UINT64_C(0x002c0ee8));STEP(UINT32_C(0x002c0ee4));/* nop */target=sx(UINT32_C(0x002e2e10));goto dispatch;
L_002c0ee4:
 STEP(UINT32_C(0x002c0ee4)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0ee8));goto dispatch;
L_002c0ee8:
 STEP(UINT32_C(0x002c0ee8)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c0eec));goto dispatch;
L_002c0eec:
 STEP(UINT32_C(0x002c0eec)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c0ef0));goto dispatch;
L_002c0ef0:
 STEP(UINT32_C(0x002c0ef0)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c0ef8));STEP(UINT32_C(0x002c0ef4));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9900)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c0ef4:
 STEP(UINT32_C(0x002c0ef4)); /* 24849900 addiu a0,a0,-26368 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9900)));target=sx(UINT32_C(0x002c0ef8));goto dispatch;
L_002c0ef8:
 STEP(UINT32_C(0x002c0ef8)); /* 0c0b8bbc jal 002e2ef0 */
 set(m,31u,UINT64_C(0x002c0f00));STEP(UINT32_C(0x002c0efc));/* nop */target=sx(UINT32_C(0x002e2ef0));goto dispatch;
L_002c0efc:
 STEP(UINT32_C(0x002c0efc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c0f00));goto dispatch;
L_002c0f00:
 STEP(UINT32_C(0x002c0f00)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c0f04));goto dispatch;
L_002c0f04:
 STEP(UINT32_C(0x002c0f04)); /* 0040282d daddu a1,v0,zero */
 set(m,5u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c0f08));goto dispatch;
L_002c0f08:
 STEP(UINT32_C(0x002c0f08)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c0f10));STEP(UINT32_C(0x002c0f0c));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9928)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c0f0c:
 STEP(UINT32_C(0x002c0f0c)); /* 24849928 addiu a0,a0,-26328 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9928)));target=sx(UINT32_C(0x002c0f10));goto dispatch;
L_002c0f10:
 STEP(UINT32_C(0x002c0f10)); /* 0220102d daddu v0,s1,zero */
 set(m,2u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002c0f14));goto dispatch;
L_002c0f14:
 STEP(UINT32_C(0x002c0f14)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c0f18));goto dispatch;
L_002c0f18:
 STEP(UINT32_C(0x002c0f18)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c0f1c));goto dispatch;
L_002c0f1c:
 STEP(UINT32_C(0x002c0f1c)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c0f20));goto dispatch;
L_002c0f20:
 STEP(UINT32_C(0x002c0f20)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c0f24));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002c0f24:
 STEP(UINT32_C(0x002c0f24)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002c0f28));goto dispatch;
L_002c13d8:
 STEP(UINT32_C(0x002c13d8)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002c13dc));goto dispatch;
L_002c13dc:
 STEP(UINT32_C(0x002c13dc)); /* 0000202d daddu a0,zero,zero */
 set(m,4u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c13e0));goto dispatch;
L_002c13e0:
 STEP(UINT32_C(0x002c13e0)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c13e4));goto dispatch;
L_002c13e4:
 STEP(UINT32_C(0x002c13e4)); /* 3c100059 lui s0,zero,0x59 */
 set(m,16u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c13e8));goto dispatch;
L_002c13e8:
 STEP(UINT32_C(0x002c13e8)); /* 26023880 addiu v0,s0,14464 */
 set(m,2u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00003880)));target=sx(UINT32_C(0x002c13ec));goto dispatch;
L_002c13ec:
 STEP(UINT32_C(0x002c13ec)); /* ffbf0008 sd ra,0x8(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c13f0));goto dispatch;
L_002c13f0:
 STEP(UINT32_C(0x002c13f0)); /* ac450000 sw a1,0x0(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002c13f4));goto dispatch;
L_002c13f4:
 STEP(UINT32_C(0x002c13f4)); /* 24060020 addiu a2,zero,32 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002c13f8));goto dispatch;
L_002c13f8:
 STEP(UINT32_C(0x002c13f8)); /* 24430010 addiu v1,v0,16 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002c13fc));goto dispatch;
L_002c13fc:
 STEP(UINT32_C(0x002c13fc)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1400));goto dispatch;
L_002c1400:
 STEP(UINT32_C(0x002c1400)); /* a0640000 sb a0,0x0(v1) */
 {uint8_t byte=(uint8_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&byte,1u);}target=sx(UINT32_C(0x002c1404));goto dispatch;
L_002c1404:
 STEP(UINT32_C(0x002c1404)); /* 24840001 addiu a0,a0,1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1408));goto dispatch;
L_002c1408:
 STEP(UINT32_C(0x002c1408)); /* 28820010 slti v0,a0,16 */
 set(m,2u,((int64_t)lo(m,4u)<INT64_C(16)));target=sx(UINT32_C(0x002c140c));goto dispatch;
L_002c140c:
 STEP(UINT32_C(0x002c140c)); /* a0660001 sb a2,0x1(v1) */
 {uint8_t byte=(uint8_t)lo(m,6u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000001),&byte,1u);}target=sx(UINT32_C(0x002c1410));goto dispatch;
L_002c1410:
 STEP(UINT32_C(0x002c1410)); /* a4600002 sh zero,0x2(v1) */
 value16=(uint16_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000002),&value16,2u);target=sx(UINT32_C(0x002c1414));goto dispatch;
L_002c1414:
 STEP(UINT32_C(0x002c1414)); /* ac600008 sw zero,0x8(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002c1418));goto dispatch;
L_002c1418:
 STEP(UINT32_C(0x002c1418)); /* ac600004 sw zero,0x4(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002c141c));goto dispatch;
L_002c141c:
 STEP(UINT32_C(0x002c141c)); /* ac60000c sw zero,0xc(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),&value32,4u);target=sx(UINT32_C(0x002c1420));goto dispatch;
L_002c1420:
 STEP(UINT32_C(0x002c1420)); /* 1440fff7 bne v0,zero,002c1400 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002c1424));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(taken?UINT32_C(0x002c1400):UINT32_C(0x002c1428));goto dispatch;}
L_002c1424:
 STEP(UINT32_C(0x002c1424)); /* 24630010 addiu v1,v1,16 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002c1428));goto dispatch;
L_002c1428:
 STEP(UINT32_C(0x002c1428)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c142c));goto dispatch;
L_002c142c:
 STEP(UINT32_C(0x002c142c)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c1434));STEP(UINT32_C(0x002c1430));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9a48)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c1430:
 STEP(UINT32_C(0x002c1430)); /* 24849a48 addiu a0,a0,-26040 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9a48)));target=sx(UINT32_C(0x002c1434));goto dispatch;
L_002c1434:
 STEP(UINT32_C(0x002c1434)); /* 3c040002 lui a0,zero,0x2 */
 set(m,4u,sx(UINT32_C(0x00020000)));target=sx(UINT32_C(0x002c1438));goto dispatch;
L_002c1438:
 STEP(UINT32_C(0x002c1438)); /* 0c0b03a4 jal 002c0e90 */
 set(m,31u,UINT64_C(0x002c1440));STEP(UINT32_C(0x002c143c));set(m,4u,lo(m,4u) | UINT64_C(0x4e00));target=sx(UINT32_C(0x002c0e90));goto dispatch;
L_002c143c:
 STEP(UINT32_C(0x002c143c)); /* 34844e00 ori a0,a0,0x4e00 */
 set(m,4u,lo(m,4u) | UINT64_C(0x4e00));target=sx(UINT32_C(0x002c1440));goto dispatch;
L_002c1440:
 STEP(UINT32_C(0x002c1440)); /* 26033880 addiu v1,s0,14464 */
 set(m,3u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00003880)));target=sx(UINT32_C(0x002c1444));goto dispatch;
L_002c1444:
 STEP(UINT32_C(0x002c1444)); /* ac6001d0 sw zero,0x1d0(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x000001d0),&value32,4u);target=sx(UINT32_C(0x002c1448));goto dispatch;
L_002c1448:
 STEP(UINT32_C(0x002c1448)); /* 2405ffff addiu a1,zero,-1 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002c144c));goto dispatch;
L_002c144c:
 STEP(UINT32_C(0x002c144c)); /* ac6001d4 sw zero,0x1d4(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x000001d4),&value32,4u);target=sx(UINT32_C(0x002c1450));goto dispatch;
L_002c1450:
 STEP(UINT32_C(0x002c1450)); /* 24040006 addiu a0,zero,6 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000006)));target=sx(UINT32_C(0x002c1454));goto dispatch;
L_002c1454:
 STEP(UINT32_C(0x002c1454)); /* ac620018 sw v0,0x18(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002c1458));goto dispatch;
L_002c1458:
 STEP(UINT32_C(0x002c1458)); /* 24620190 addiu v0,v1,400 */
 set(m,2u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000190)));target=sx(UINT32_C(0x002c145c));goto dispatch;
L_002c145c:
 STEP(UINT32_C(0x002c145c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1460));goto dispatch;
L_002c1460:
 STEP(UINT32_C(0x002c1460)); /* 2484ffff addiu a0,a0,-1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=sx(UINT32_C(0x002c1464));goto dispatch;
L_002c1464:
 STEP(UINT32_C(0x002c1464)); /* ac450000 sw a1,0x0(v0) */
 value32=(uint32_t)lo(m,5u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002c1468));goto dispatch;
L_002c1468:
 STEP(UINT32_C(0x002c1468)); /* a0400004 sb zero,0x4(v0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&byte,1u);}target=sx(UINT32_C(0x002c146c));goto dispatch;
L_002c146c:
 STEP(UINT32_C(0x002c146c)); /* a0400005 sb zero,0x5(v0) */
 {uint8_t byte=(uint8_t)lo(m,0u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000005),&byte,1u);}target=sx(UINT32_C(0x002c1470));goto dispatch;
L_002c1470:
 STEP(UINT32_C(0x002c1470)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1474));goto dispatch;
L_002c1474:
 STEP(UINT32_C(0x002c1474)); /* 0481fffa regimm1 a0,002c1460 */
 {int taken=((int64_t)lo(m,4u)>=0);STEP(UINT32_C(0x002c1478));set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002c1460):UINT32_C(0x002c147c));goto dispatch;}
L_002c1478:
 STEP(UINT32_C(0x002c1478)); /* 24420008 addiu v0,v0,8 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002c147c));goto dispatch;
L_002c147c:
 STEP(UINT32_C(0x002c147c)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1480));goto dispatch;
L_002c1480:
 STEP(UINT32_C(0x002c1480)); /* dfbf0008 ld ra,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c1484));goto dispatch;
L_002c1484:
 STEP(UINT32_C(0x002c1484)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c1488));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002c1488:
 STEP(UINT32_C(0x002c1488)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002c148c));goto dispatch;
L_002c1490:
 STEP(UINT32_C(0x002c1490)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002c1494));goto dispatch;
L_002c1494:
 STEP(UINT32_C(0x002c1494)); /* 3c020059 lui v0,zero,0x59 */
 set(m,2u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c1498));goto dispatch;
L_002c1498:
 STEP(UINT32_C(0x002c1498)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c149c));goto dispatch;
L_002c149c:
 STEP(UINT32_C(0x002c149c)); /* 00a0802d daddu s0,a1,zero */
 set(m,16u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002c14a0));goto dispatch;
L_002c14a0:
 STEP(UINT32_C(0x002c14a0)); /* 24423880 addiu v0,v0,14464 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00003880)));target=sx(UINT32_C(0x002c14a4));goto dispatch;
L_002c14a4:
 STEP(UINT32_C(0x002c14a4)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c14a8));goto dispatch;
L_002c14a8:
 STEP(UINT32_C(0x002c14a8)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002c14ac));goto dispatch;
L_002c14ac:
 STEP(UINT32_C(0x002c14ac)); /* 24430110 addiu v1,v0,272 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000110)));target=sx(UINT32_C(0x002c14b0));goto dispatch;
L_002c14b0:
 STEP(UINT32_C(0x002c14b0)); /* ac500004 sw s0,0x4(v0) */
 value32=(uint32_t)lo(m,16u);WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002c14b4));goto dispatch;
L_002c14b4:
 STEP(UINT32_C(0x002c14b4)); /* 0000882d daddu s1,zero,zero */
 set(m,17u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c14b8));goto dispatch;
L_002c14b8:
 STEP(UINT32_C(0x002c14b8)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c14bc));goto dispatch;
L_002c14bc:
 STEP(UINT32_C(0x002c14bc)); /* 2406fff0 addiu a2,zero,-16 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002c14c0));goto dispatch;
L_002c14c0:
 STEP(UINT32_C(0x002c14c0)); /* 8c820000 lw v0,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002c14c4));goto dispatch;
L_002c14c4:
 STEP(UINT32_C(0x002c14c4)); /* 24840004 addiu a0,a0,4 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002c14c8));goto dispatch;
L_002c14c8:
 STEP(UINT32_C(0x002c14c8)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c14cc));goto dispatch;
L_002c14cc:
 STEP(UINT32_C(0x002c14cc)); /* 2442000f addiu v0,v0,15 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x0000000f)));target=sx(UINT32_C(0x002c14d0));goto dispatch;
L_002c14d0:
 STEP(UINT32_C(0x002c14d0)); /* 00461024 and v0,v0,a2 */
 set(m,2u,lo(m,2u)&lo(m,6u));target=sx(UINT32_C(0x002c14d4));goto dispatch;
L_002c14d4:
 STEP(UINT32_C(0x002c14d4)); /* ac620000 sw v0,0x0(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002c14d8));goto dispatch;
L_002c14d8:
 STEP(UINT32_C(0x002c14d8)); /* 24630008 addiu v1,v1,8 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002c14dc));goto dispatch;
L_002c14dc:
 STEP(UINT32_C(0x002c14dc)); /* 14b0fff8 bne a1,s0,002c14c0 */
 {int taken=(lo(m,5u)!=lo(m,16u));STEP(UINT32_C(0x002c14e0));set(m,17u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,2u)));target=sx(taken?UINT32_C(0x002c14c0):UINT32_C(0x002c14e4));goto dispatch;}
L_002c14e0:
 STEP(UINT32_C(0x002c14e0)); /* 02228821 addu s1,s1,v0 */
 set(m,17u,sx((uint32_t)lo(m,17u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002c14e4));goto dispatch;
L_002c14e4:
 STEP(UINT32_C(0x002c14e4)); /* 28a20010 slti v0,a1,16 */
 set(m,2u,((int64_t)lo(m,5u)<INT64_C(16)));target=sx(UINT32_C(0x002c14e8));goto dispatch;
L_002c14e8:
 STEP(UINT32_C(0x002c14e8)); /* 5040000d beql v0,zero,002c1520 */
 if(lo(m,2u)==lo(m,0u)){STEP(UINT32_C(0x002c14ec));set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1520));}else target=sx(UINT32_C(0x002c14f0));goto dispatch;
L_002c14ec:
 STEP(UINT32_C(0x002c14ec)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c14f0));goto dispatch;
L_002c14f0:
 STEP(UINT32_C(0x002c14f0)); /* 000510c0 sll v0,a1,3 */
 set(m,2u,sx((uint32_t)lo(m,5u)<<3u));target=sx(UINT32_C(0x002c14f4));goto dispatch;
L_002c14f4:
 STEP(UINT32_C(0x002c14f4)); /* 3c030059 lui v1,zero,0x59 */
 set(m,3u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c14f8));goto dispatch;
L_002c14f8:
 STEP(UINT32_C(0x002c14f8)); /* 24633994 addiu v1,v1,14740 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00003994)));target=sx(UINT32_C(0x002c14fc));goto dispatch;
L_002c14fc:
 STEP(UINT32_C(0x002c14fc)); /* 00621821 addu v1,v1,v0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002c1500));goto dispatch;
L_002c1500:
 STEP(UINT32_C(0x002c1500)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1504));goto dispatch;
L_002c1504:
 STEP(UINT32_C(0x002c1504)); /* ac60fffc sw zero,-0x4(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0xfffffffc),&value32,4u);target=sx(UINT32_C(0x002c1508));goto dispatch;
L_002c1508:
 STEP(UINT32_C(0x002c1508)); /* 28a20010 slti v0,a1,16 */
 set(m,2u,((int64_t)lo(m,5u)<INT64_C(16)));target=sx(UINT32_C(0x002c150c));goto dispatch;
L_002c150c:
 STEP(UINT32_C(0x002c150c)); /* ac600000 sw zero,0x0(v1) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002c1510));goto dispatch;
L_002c1510:
 STEP(UINT32_C(0x002c1510)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1514));goto dispatch;
L_002c1514:
 STEP(UINT32_C(0x002c1514)); /* 1440fffa bne v0,zero,002c1500 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002c1518));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=sx(taken?UINT32_C(0x002c1500):UINT32_C(0x002c151c));goto dispatch;}
L_002c1518:
 STEP(UINT32_C(0x002c1518)); /* 24630008 addiu v1,v1,8 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002c151c));goto dispatch;
L_002c151c:
 STEP(UINT32_C(0x002c151c)); /* 3c040055 lui a0,zero,0x55 */
 set(m,4u,sx(UINT32_C(0x00550000)));target=sx(UINT32_C(0x002c1520));goto dispatch;
L_002c1520:
 STEP(UINT32_C(0x002c1520)); /* 0c0b51d2 jal 002d4748 */
 set(m,31u,UINT64_C(0x002c1528));STEP(UINT32_C(0x002c1524));set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9a60)));target=sx(UINT32_C(0x002d4748));goto dispatch;
L_002c1524:
 STEP(UINT32_C(0x002c1524)); /* 24849a60 addiu a0,a0,-26016 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffff9a60)));target=sx(UINT32_C(0x002c1528));goto dispatch;
L_002c1528:
 STEP(UINT32_C(0x002c1528)); /* 0c0b03a4 jal 002c0e90 */
 set(m,31u,UINT64_C(0x002c1530));STEP(UINT32_C(0x002c152c));set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002c0e90));goto dispatch;
L_002c152c:
 STEP(UINT32_C(0x002c152c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002c1530));goto dispatch;
L_002c1530:
 STEP(UINT32_C(0x002c1530)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002c1534));goto dispatch;
L_002c1534:
 STEP(UINT32_C(0x002c1534)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c1538));goto dispatch;
L_002c1538:
 STEP(UINT32_C(0x002c1538)); /* 3c020059 lui v0,zero,0x59 */
 set(m,2u,sx(UINT32_C(0x00590000)));target=sx(UINT32_C(0x002c153c));goto dispatch;
L_002c153c:
 STEP(UINT32_C(0x002c153c)); /* 24423880 addiu v0,v0,14464 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00003880)));target=sx(UINT32_C(0x002c1540));goto dispatch;
L_002c1540:
 STEP(UINT32_C(0x002c1540)); /* 24430110 addiu v1,v0,272 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00000110)));target=sx(UINT32_C(0x002c1544));goto dispatch;
L_002c1544:
 STEP(UINT32_C(0x002c1544)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1548));goto dispatch;
L_002c1548:
 STEP(UINT32_C(0x002c1548)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002c154c));goto dispatch;
L_002c154c:
 STEP(UINT32_C(0x002c154c)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002c1550));goto dispatch;
L_002c1550:
 STEP(UINT32_C(0x002c1550)); /* ac640004 sw a0,0x4(v1) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002c1554));goto dispatch;
L_002c1554:
 STEP(UINT32_C(0x002c1554)); /* 24630008 addiu v1,v1,8 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=sx(UINT32_C(0x002c1558));goto dispatch;
L_002c1558:
 STEP(UINT32_C(0x002c1558)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c155c));goto dispatch;
L_002c155c:
 STEP(UINT32_C(0x002c155c)); /* 14b0fffa bne a1,s0,002c1548 */
 {int taken=(lo(m,5u)!=lo(m,16u));STEP(UINT32_C(0x002c1560));set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,2u)));target=sx(taken?UINT32_C(0x002c1548):UINT32_C(0x002c1564));goto dispatch;}
L_002c1560:
 STEP(UINT32_C(0x002c1560)); /* 00822021 addu a0,a0,v0 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,2u)));target=sx(UINT32_C(0x002c1564));goto dispatch;
L_002c1564:
 STEP(UINT32_C(0x002c1564)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c1568));goto dispatch;
L_002c1568:
 STEP(UINT32_C(0x002c1568)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002c156c));goto dispatch;
L_002c156c:
 STEP(UINT32_C(0x002c156c)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c1570));goto dispatch;
L_002c1570:
 STEP(UINT32_C(0x002c1570)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c1574));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002c1574:
 STEP(UINT32_C(0x002c1574)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002c1578));goto dispatch;
L_002c1240:
 STEP(UINT32_C(0x002c1240)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=sx(UINT32_C(0x002c1244));goto dispatch;
L_002c1244:
 STEP(UINT32_C(0x002c1244)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002c1248));goto dispatch;
L_002c1248:
 STEP(UINT32_C(0x002c1248)); /* ffbf0008 sd ra,0x8(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002c124c));goto dispatch;
L_002c124c:
 STEP(UINT32_C(0x002c124c)); /* 0c0b043a jal 002c10e8 */
 set(m,31u,UINT64_C(0x002c1254));STEP(UINT32_C(0x002c1250));/* nop */target=sx(UINT32_C(0x002c10e8));goto dispatch;
L_002c1250:
 STEP(UINT32_C(0x002c1250)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1254));goto dispatch;
L_002c1254:
 STEP(UINT32_C(0x002c1254)); /* 0040802d daddu s0,v0,zero */
 set(m,16u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002c1258));goto dispatch;
L_002c1258:
 STEP(UINT32_C(0x002c1258)); /* 0c0b048e jal 002c1238 */
 set(m,31u,UINT64_C(0x002c1260));STEP(UINT32_C(0x002c125c));set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c1238));goto dispatch;
L_002c125c:
 STEP(UINT32_C(0x002c125c)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c1260));goto dispatch;
L_002c1260:
 STEP(UINT32_C(0x002c1260)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002c1264));goto dispatch;
L_002c1264:
 STEP(UINT32_C(0x002c1264)); /* dfbf0008 ld ra,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002c1268));goto dispatch;
L_002c1268:
 STEP(UINT32_C(0x002c1268)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002c126c));goto dispatch;
L_002c126c:
 STEP(UINT32_C(0x002c126c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c1270));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_002c1270:
 STEP(UINT32_C(0x002c1270)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=sx(UINT32_C(0x002c1274));goto dispatch;
L_002c1238:
 STEP(UINT32_C(0x002c1238)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002c123c));/* nop */goto dispatch;
L_002c123c:
 STEP(UINT32_C(0x002c123c)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002c1240));goto dispatch;
L_002d4748:
 STEP(UINT32_C(0x002d4748)); /* 27bdff90 addiu sp,sp,-112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff90)));target=sx(UINT32_C(0x002d474c));goto dispatch;
L_002d474c:
 STEP(UINT32_C(0x002d474c)); /* 3c0c0053 lui t4,zero,0x53 */
 set(m,12u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d4750));goto dispatch;
L_002d4750:
 STEP(UINT32_C(0x002d4750)); /* ffbf0000 sd ra,0x0(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d4754));goto dispatch;
L_002d4754:
 STEP(UINT32_C(0x002d4754)); /* ffa50038 sd a1,0x38(sp) */
 value64=lo(m,5u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000038),&value64,8u);target=sx(UINT32_C(0x002d4758));goto dispatch;
L_002d4758:
 STEP(UINT32_C(0x002d4758)); /* 0080282d daddu a1,a0,zero */
 set(m,5u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d475c));goto dispatch;
L_002d475c:
 STEP(UINT32_C(0x002d475c)); /* ffa60040 sd a2,0x40(sp) */
 value64=lo(m,6u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),&value64,8u);target=sx(UINT32_C(0x002d4760));goto dispatch;
L_002d4760:
 STEP(UINT32_C(0x002d4760)); /* 27a60038 addiu a2,sp,56 */
 set(m,6u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000038)));target=sx(UINT32_C(0x002d4764));goto dispatch;
L_002d4764:
 STEP(UINT32_C(0x002d4764)); /* ffa70048 sd a3,0x48(sp) */
 value64=lo(m,7u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000048),&value64,8u);target=sx(UINT32_C(0x002d4768));goto dispatch;
L_002d4768:
 STEP(UINT32_C(0x002d4768)); /* ffa80050 sd t0,0x50(sp) */
 value64=lo(m,8u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),&value64,8u);target=sx(UINT32_C(0x002d476c));goto dispatch;
L_002d476c:
 STEP(UINT32_C(0x002d476c)); /* ffa90058 sd t1,0x58(sp) */
 value64=lo(m,9u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000058),&value64,8u);target=sx(UINT32_C(0x002d4770));goto dispatch;
L_002d4770:
 STEP(UINT32_C(0x002d4770)); /* ffaa0060 sd t2,0x60(sp) */
 value64=lo(m,10u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),&value64,8u);target=sx(UINT32_C(0x002d4774));goto dispatch;
L_002d4774:
 STEP(UINT32_C(0x002d4774)); /* ffab0068 sd t3,0x68(sp) */
 value64=lo(m,11u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000068),&value64,8u);target=sx(UINT32_C(0x002d4778));goto dispatch;
L_002d4778:
 STEP(UINT32_C(0x002d4778)); /* e7ac0018 swc1 f12,0x18(sp) */
 value32=m->fpr[12];WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d477c));goto dispatch;
L_002d477c:
 STEP(UINT32_C(0x002d477c)); /* e7ad001c swc1 f13,0x1c(sp) */
 value32=m->fpr[13];WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002d4780));goto dispatch;
L_002d4780:
 STEP(UINT32_C(0x002d4780)); /* e7ae0020 swc1 f14,0x20(sp) */
 value32=m->fpr[14];WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002d4784));goto dispatch;
L_002d4784:
 STEP(UINT32_C(0x002d4784)); /* e7af0024 swc1 f15,0x24(sp) */
 value32=m->fpr[15];WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002d4788));goto dispatch;
L_002d4788:
 STEP(UINT32_C(0x002d4788)); /* e7b00028 swc1 f16,0x28(sp) */
 value32=m->fpr[16];WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x002d478c));goto dispatch;
L_002d478c:
 STEP(UINT32_C(0x002d478c)); /* e7b1002c swc1 f17,0x2c(sp) */
 value32=m->fpr[17];WRITE((uint32_t)lo(m,29u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x002d4790));goto dispatch;
L_002d4790:
 STEP(UINT32_C(0x002d4790)); /* e7b20030 swc1 f18,0x30(sp) */
 value32=m->fpr[18];WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),&value32,4u);target=sx(UINT32_C(0x002d4794));goto dispatch;
L_002d4794:
 STEP(UINT32_C(0x002d4794)); /* e7b30034 swc1 f19,0x34(sp) */
 value32=m->fpr[19];WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000034),&value32,4u);target=sx(UINT32_C(0x002d4798));goto dispatch;
L_002d4798:
 STEP(UINT32_C(0x002d4798)); /* 8d82be28 lw v0,-0x41d8(t4) */
 READ((uint32_t)lo(m,12u)+UINT32_C(0xffffbe28),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d479c));goto dispatch;
L_002d479c:
 STEP(UINT32_C(0x002d479c)); /* 8c430008 lw v1,0x8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,3u,sx(value32));target=sx(UINT32_C(0x002d47a0));goto dispatch;
L_002d47a0:
 STEP(UINT32_C(0x002d47a0)); /* ac620054 sw v0,0x54(v1) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000054),&value32,4u);target=sx(UINT32_C(0x002d47a4));goto dispatch;
L_002d47a4:
 STEP(UINT32_C(0x002d47a4)); /* 0c0b5980 jal 002d6600 */
 set(m,31u,UINT64_C(0x002d47ac));STEP(UINT32_C(0x002d47a8));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d6600));goto dispatch;
L_002d47a8:
 STEP(UINT32_C(0x002d47a8)); /* 8c440008 lw a0,0x8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000008),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d47ac));goto dispatch;
L_002d47ac:
 STEP(UINT32_C(0x002d47ac)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d47b0));goto dispatch;
L_002d47b0:
 STEP(UINT32_C(0x002d47b0)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d47b4));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));goto dispatch;
L_002d47b4:
 STEP(UINT32_C(0x002d47b4)); /* 27bd0070 addiu sp,sp,112 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000070)));target=sx(UINT32_C(0x002d47b8));goto dispatch;
L_002d6600:
 STEP(UINT32_C(0x002d6600)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d6604));goto dispatch;
L_002d6604:
 STEP(UINT32_C(0x002d6604)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d6608));goto dispatch;
L_002d6608:
 STEP(UINT32_C(0x002d6608)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d660c));goto dispatch;
L_002d660c:
 STEP(UINT32_C(0x002d660c)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d6610));goto dispatch;
L_002d6610:
 STEP(UINT32_C(0x002d6610)); /* 00a0882d daddu s1,a1,zero */
 set(m,17u,lo(m,5u)+lo(m,0u));target=sx(UINT32_C(0x002d6614));goto dispatch;
L_002d6614:
 STEP(UINT32_C(0x002d6614)); /* ffb20010 sd s2,0x10(sp) */
 value64=lo(m,18u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d6618));goto dispatch;
L_002d6618:
 STEP(UINT32_C(0x002d6618)); /* 00c0902d daddu s2,a2,zero */
 set(m,18u,lo(m,6u)+lo(m,0u));target=sx(UINT32_C(0x002d661c));goto dispatch;
L_002d661c:
 STEP(UINT32_C(0x002d661c)); /* ffbf0018 sd ra,0x18(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);target=sx(UINT32_C(0x002d6620));goto dispatch;
L_002d6620:
 STEP(UINT32_C(0x002d6620)); /* 8e040054 lw a0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d6624));goto dispatch;
L_002d6624:
 STEP(UINT32_C(0x002d6624)); /* 14800004 bne a0,zero,002d6638 */
 {int taken=(lo(m,4u)!=lo(m,0u));STEP(UINT32_C(0x002d6628));set(m,2u,sx(UINT32_C(0x00530000)));target=sx(taken?UINT32_C(0x002d6638):UINT32_C(0x002d662c));goto dispatch;}
L_002d6628:
 STEP(UINT32_C(0x002d6628)); /* 3c020053 lui v0,zero,0x53 */
 set(m,2u,sx(UINT32_C(0x00530000)));target=sx(UINT32_C(0x002d662c));goto dispatch;
L_002d662c:
 STEP(UINT32_C(0x002d662c)); /* 8c42be28 lw v0,-0x41d8(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0xffffbe28),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d6630));goto dispatch;
L_002d6630:
 STEP(UINT32_C(0x002d6630)); /* ae020054 sw v0,0x54(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);target=sx(UINT32_C(0x002d6634));goto dispatch;
L_002d6634:
 STEP(UINT32_C(0x002d6634)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=sx(UINT32_C(0x002d6638));goto dispatch;
L_002d6638:
 STEP(UINT32_C(0x002d6638)); /* 8c820038 lw v0,0x38(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000038),&value32,4u);set(m,2u,sx(value32));target=sx(UINT32_C(0x002d663c));goto dispatch;
L_002d663c:
 STEP(UINT32_C(0x002d663c)); /* 14400005 bne v0,zero,002d6654 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x002d6640));set(m,5u,lo(m,16u)+lo(m,0u));target=sx(taken?UINT32_C(0x002d6654):UINT32_C(0x002d6644));goto dispatch;}
L_002d6640:
 STEP(UINT32_C(0x002d6640)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6644));goto dispatch;
L_002d6644:
 STEP(UINT32_C(0x002d6644)); /* 0c0b6642 jal 002d9908 */
 set(m,31u,UINT64_C(0x002d664c));STEP(UINT32_C(0x002d6648));/* nop */target=sx(UINT32_C(0x002d9908));goto dispatch;
L_002d6648:
 STEP(UINT32_C(0x002d6648)); /* 00000000 nop */
 /* nop */target=sx(UINT32_C(0x002d664c));goto dispatch;
L_002d664c:
 STEP(UINT32_C(0x002d664c)); /* 8e040054 lw a0,0x54(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000054),&value32,4u);set(m,4u,sx(value32));target=sx(UINT32_C(0x002d6650));goto dispatch;
L_002d6650:
 STEP(UINT32_C(0x002d6650)); /* 0200282d daddu a1,s0,zero */
 set(m,5u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d6654));goto dispatch;
L_002d6654:
 STEP(UINT32_C(0x002d6654)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d6658));goto dispatch;
L_002d6658:
 STEP(UINT32_C(0x002d6658)); /* 0220302d daddu a2,s1,zero */
 set(m,6u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d665c));goto dispatch;
L_002d665c:
 STEP(UINT32_C(0x002d665c)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d6660));goto dispatch;
L_002d6660:
 STEP(UINT32_C(0x002d6660)); /* 0240382d daddu a3,s2,zero */
 set(m,7u,lo(m,18u)+lo(m,0u));target=sx(UINT32_C(0x002d6664));goto dispatch;
L_002d6664:
 STEP(UINT32_C(0x002d6664)); /* dfb20010 ld s2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,18u,value64);target=sx(UINT32_C(0x002d6668));goto dispatch;
L_002d6668:
 STEP(UINT32_C(0x002d6668)); /* dfbf0018 ld ra,0x18(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000018),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d666c));goto dispatch;
L_002d666c:
 STEP(UINT32_C(0x002d666c)); /* 080b599e j 002d6678 */
 STEP(UINT32_C(0x002d6670));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d6678));goto dispatch;
L_002d6670:
 STEP(UINT32_C(0x002d6670)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d6674));goto dispatch;
L_002d9908:
 STEP(UINT32_C(0x002d9908)); /* 27bdffe0 addiu sp,sp,-32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffe0)));target=sx(UINT32_C(0x002d990c));goto dispatch;
L_002d990c:
 STEP(UINT32_C(0x002d990c)); /* 3c02002e lui v0,zero,0x2e */
 set(m,2u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002d9910));goto dispatch;
L_002d9910:
 STEP(UINT32_C(0x002d9910)); /* ffb00000 sd s0,0x0(sp) */
 value64=lo(m,16u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);target=sx(UINT32_C(0x002d9914));goto dispatch;
L_002d9914:
 STEP(UINT32_C(0x002d9914)); /* 0080802d daddu s0,a0,zero */
 set(m,16u,lo(m,4u)+lo(m,0u));target=sx(UINT32_C(0x002d9918));goto dispatch;
L_002d9918:
 STEP(UINT32_C(0x002d9918)); /* 244298c8 addiu v0,v0,-26424 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffff98c8)));target=sx(UINT32_C(0x002d991c));goto dispatch;
L_002d991c:
 STEP(UINT32_C(0x002d991c)); /* 24030001 addiu v1,zero,1 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d9920));goto dispatch;
L_002d9920:
 STEP(UINT32_C(0x002d9920)); /* ffb10008 sd s1,0x8(sp) */
 value64=lo(m,17u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);target=sx(UINT32_C(0x002d9924));goto dispatch;
L_002d9924:
 STEP(UINT32_C(0x002d9924)); /* 261101e4 addiu s1,s0,484 */
 set(m,17u,sx((uint32_t)lo(m,16u)+UINT32_C(0x000001e4)));target=sx(UINT32_C(0x002d9928));goto dispatch;
L_002d9928:
 STEP(UINT32_C(0x002d9928)); /* ffbf0010 sd ra,0x10(sp) */
 value64=lo(m,31u);WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);target=sx(UINT32_C(0x002d992c));goto dispatch;
L_002d992c:
 STEP(UINT32_C(0x002d992c)); /* 0220202d daddu a0,s1,zero */
 set(m,4u,lo(m,17u)+lo(m,0u));target=sx(UINT32_C(0x002d9930));goto dispatch;
L_002d9930:
 STEP(UINT32_C(0x002d9930)); /* ae02003c sw v0,0x3c(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x0000003c),&value32,4u);target=sx(UINT32_C(0x002d9934));goto dispatch;
L_002d9934:
 STEP(UINT32_C(0x002d9934)); /* 0200382d daddu a3,s0,zero */
 set(m,7u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d9938));goto dispatch;
L_002d9938:
 STEP(UINT32_C(0x002d9938)); /* ae030038 sw v1,0x38(s0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000038),&value32,4u);target=sx(UINT32_C(0x002d993c));goto dispatch;
L_002d993c:
 STEP(UINT32_C(0x002d993c)); /* 24050004 addiu a1,zero,4 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000004)));target=sx(UINT32_C(0x002d9940));goto dispatch;
L_002d9940:
 STEP(UINT32_C(0x002d9940)); /* 0c0b65be jal 002d96f8 */
 set(m,31u,UINT64_C(0x002d9948));STEP(UINT32_C(0x002d9944));set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d96f8));goto dispatch;
L_002d9944:
 STEP(UINT32_C(0x002d9944)); /* 0000302d daddu a2,zero,zero */
 set(m,6u,lo(m,0u)+lo(m,0u));target=sx(UINT32_C(0x002d9948));goto dispatch;
L_002d9948:
 STEP(UINT32_C(0x002d9948)); /* 2604023c addiu a0,s0,572 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0x0000023c)));target=sx(UINT32_C(0x002d994c));goto dispatch;
L_002d994c:
 STEP(UINT32_C(0x002d994c)); /* 0200382d daddu a3,s0,zero */
 set(m,7u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d9950));goto dispatch;
L_002d9950:
 STEP(UINT32_C(0x002d9950)); /* 24050009 addiu a1,zero,9 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000009)));target=sx(UINT32_C(0x002d9954));goto dispatch;
L_002d9954:
 STEP(UINT32_C(0x002d9954)); /* 0c0b65be jal 002d96f8 */
 set(m,31u,UINT64_C(0x002d995c));STEP(UINT32_C(0x002d9958));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d96f8));goto dispatch;
L_002d9958:
 STEP(UINT32_C(0x002d9958)); /* 24060001 addiu a2,zero,1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=sx(UINT32_C(0x002d995c));goto dispatch;
L_002d995c:
 STEP(UINT32_C(0x002d995c)); /* 26040294 addiu a0,s0,660 */
 set(m,4u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000294)));target=sx(UINT32_C(0x002d9960));goto dispatch;
L_002d9960:
 STEP(UINT32_C(0x002d9960)); /* 0200382d daddu a3,s0,zero */
 set(m,7u,lo(m,16u)+lo(m,0u));target=sx(UINT32_C(0x002d9964));goto dispatch;
L_002d9964:
 STEP(UINT32_C(0x002d9964)); /* 2405000a addiu a1,zero,10 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x0000000a)));target=sx(UINT32_C(0x002d9968));goto dispatch;
L_002d9968:
 STEP(UINT32_C(0x002d9968)); /* 0c0b65be jal 002d96f8 */
 set(m,31u,UINT64_C(0x002d9970));STEP(UINT32_C(0x002d996c));set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d96f8));goto dispatch;
L_002d996c:
 STEP(UINT32_C(0x002d996c)); /* 24060002 addiu a2,zero,2 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000002)));target=sx(UINT32_C(0x002d9970));goto dispatch;
L_002d9970:
 STEP(UINT32_C(0x002d9970)); /* ae0001d8 sw zero,0x1d8(s0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x000001d8),&value32,4u);target=sx(UINT32_C(0x002d9974));goto dispatch;
L_002d9974:
 STEP(UINT32_C(0x002d9974)); /* 24020003 addiu v0,zero,3 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000003)));target=sx(UINT32_C(0x002d9978));goto dispatch;
L_002d9978:
 STEP(UINT32_C(0x002d9978)); /* ae1101e0 sw s1,0x1e0(s0) */
 value32=(uint32_t)lo(m,17u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x000001e0),&value32,4u);target=sx(UINT32_C(0x002d997c));goto dispatch;
L_002d997c:
 STEP(UINT32_C(0x002d997c)); /* ae0201dc sw v0,0x1dc(s0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,16u)+UINT32_C(0x000001dc),&value32,4u);target=sx(UINT32_C(0x002d9980));goto dispatch;
L_002d9980:
 STEP(UINT32_C(0x002d9980)); /* dfb10008 ld s1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),&value64,8u);set(m,17u,value64);target=sx(UINT32_C(0x002d9984));goto dispatch;
L_002d9984:
 STEP(UINT32_C(0x002d9984)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),&value64,8u);set(m,16u,value64);target=sx(UINT32_C(0x002d9988));goto dispatch;
L_002d9988:
 STEP(UINT32_C(0x002d9988)); /* dfbf0010 ld ra,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),&value64,8u);set(m,31u,value64);target=sx(UINT32_C(0x002d998c));goto dispatch;
L_002d998c:
 STEP(UINT32_C(0x002d998c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d9990));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));goto dispatch;
L_002d9990:
 STEP(UINT32_C(0x002d9990)); /* 27bd0020 addiu sp,sp,32 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000020)));target=sx(UINT32_C(0x002d9994));goto dispatch;
L_002d96f8:
 STEP(UINT32_C(0x002d96f8)); /* 3c02002e lui v0,zero,0x2e */
 set(m,2u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002d96fc));goto dispatch;
L_002d96fc:
 STEP(UINT32_C(0x002d96fc)); /* 3c03002e lui v1,zero,0x2e */
 set(m,3u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002d9700));goto dispatch;
L_002d9700:
 STEP(UINT32_C(0x002d9700)); /* 3c08002e lui t0,zero,0x2e */
 set(m,8u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002d9704));goto dispatch;
L_002d9704:
 STEP(UINT32_C(0x002d9704)); /* 3c09002e lui t1,zero,0x2e */
 set(m,9u,sx(UINT32_C(0x002e0000)));target=sx(UINT32_C(0x002d9708));goto dispatch;
L_002d9708:
 STEP(UINT32_C(0x002d9708)); /* 2442b670 addiu v0,v0,-18832 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffb670)));target=sx(UINT32_C(0x002d970c));goto dispatch;
L_002d970c:
 STEP(UINT32_C(0x002d970c)); /* 2463b6d8 addiu v1,v1,-18728 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffb6d8)));target=sx(UINT32_C(0x002d9710));goto dispatch;
L_002d9710:
 STEP(UINT32_C(0x002d9710)); /* 2508b758 addiu t0,t0,-18600 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0xffffb758)));target=sx(UINT32_C(0x002d9714));goto dispatch;
L_002d9714:
 STEP(UINT32_C(0x002d9714)); /* 2529b7c0 addiu t1,t1,-18496 */
 set(m,9u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffb7c0)));target=sx(UINT32_C(0x002d9718));goto dispatch;
L_002d9718:
 STEP(UINT32_C(0x002d9718)); /* ac870054 sw a3,0x54(a0) */
 value32=(uint32_t)lo(m,7u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000054),&value32,4u);target=sx(UINT32_C(0x002d971c));goto dispatch;
L_002d971c:
 STEP(UINT32_C(0x002d971c)); /* a485000c sh a1,0xc(a0) */
 value16=(uint16_t)lo(m,5u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000000c),&value16,2u);target=sx(UINT32_C(0x002d9720));goto dispatch;
L_002d9720:
 STEP(UINT32_C(0x002d9720)); /* a486000e sh a2,0xe(a0) */
 value16=(uint16_t)lo(m,6u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000000e),&value16,2u);target=sx(UINT32_C(0x002d9724));goto dispatch;
L_002d9724:
 STEP(UINT32_C(0x002d9724)); /* ac820020 sw v0,0x20(a0) */
 value32=(uint32_t)lo(m,2u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000020),&value32,4u);target=sx(UINT32_C(0x002d9728));goto dispatch;
L_002d9728:
 STEP(UINT32_C(0x002d9728)); /* ac830024 sw v1,0x24(a0) */
 value32=(uint32_t)lo(m,3u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000024),&value32,4u);target=sx(UINT32_C(0x002d972c));goto dispatch;
L_002d972c:
 STEP(UINT32_C(0x002d972c)); /* ac880028 sw t0,0x28(a0) */
 value32=(uint32_t)lo(m,8u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000028),&value32,4u);target=sx(UINT32_C(0x002d9730));goto dispatch;
L_002d9730:
 STEP(UINT32_C(0x002d9730)); /* ac89002c sw t1,0x2c(a0) */
 value32=(uint32_t)lo(m,9u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000002c),&value32,4u);target=sx(UINT32_C(0x002d9734));goto dispatch;
L_002d9734:
 STEP(UINT32_C(0x002d9734)); /* ac800000 sw zero,0x0(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),&value32,4u);target=sx(UINT32_C(0x002d9738));goto dispatch;
L_002d9738:
 STEP(UINT32_C(0x002d9738)); /* ac800004 sw zero,0x4(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000004),&value32,4u);target=sx(UINT32_C(0x002d973c));goto dispatch;
L_002d973c:
 STEP(UINT32_C(0x002d973c)); /* ac800008 sw zero,0x8(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000008),&value32,4u);target=sx(UINT32_C(0x002d9740));goto dispatch;
L_002d9740:
 STEP(UINT32_C(0x002d9740)); /* ac800010 sw zero,0x10(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),&value32,4u);target=sx(UINT32_C(0x002d9744));goto dispatch;
L_002d9744:
 STEP(UINT32_C(0x002d9744)); /* ac800014 sw zero,0x14(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000014),&value32,4u);target=sx(UINT32_C(0x002d9748));goto dispatch;
L_002d9748:
 STEP(UINT32_C(0x002d9748)); /* ac800018 sw zero,0x18(a0) */
 value32=(uint32_t)lo(m,0u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000018),&value32,4u);target=sx(UINT32_C(0x002d974c));goto dispatch;
L_002d974c:
 STEP(UINT32_C(0x002d974c)); /* 03e00008 jr ra */
 target=sx((uint32_t)lo(m,31u));STEP(UINT32_C(0x002d9750));value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000001c),&value32,4u);goto dispatch;
L_002d9750:
 STEP(UINT32_C(0x002d9750)); /* ac84001c sw a0,0x1c(a0) */
 value32=(uint32_t)lo(m,4u);WRITE((uint32_t)lo(m,4u)+UINT32_C(0x0000001c),&value32,4u);target=sx(UINT32_C(0x002d9754));goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

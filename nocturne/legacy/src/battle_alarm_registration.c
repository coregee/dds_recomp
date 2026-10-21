#include "battle_alarm_registration.h"
#include <string.h>
/* Fixed source-bound instruction statements. No runtime instruction decoder,
 * callback answers, private guest RAM, fake timer or post-call bank repair. */
static uint64_t lo(const NocturneWakeupMachine *m,unsigned r)
{return (uint64_t)m->gpr[r][0]|((uint64_t)m->gpr[r][1]<<32);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
static void set(NocturneWakeupMachine *m,unsigned r,uint64_t v)
{if(r){m->gpr[r][0]=(uint32_t)v;m->gpr[r][1]=(uint32_t)(v>>32);}}
static uint64_t unpack(const uint8_t *b,unsigned n)
{uint64_t v=0;unsigned i;for(i=0;i<n;++i)v|=(uint64_t)b[i]<<(8u*i);return v;}
static void pack(uint8_t *b,uint64_t v,unsigned n)
{unsigned i;for(i=0;i<n;++i)b[i]=(uint8_t)(v>>(8u*i));}
static uint32_t stop(NocturneWakeupMachine *m,NocturneWakeupStop *s,uint32_t why,uint32_t a,uint32_t n,uint64_t target)
{s->outcome=why;s->pc=m->pc;s->address=a;s->bytes=n;s->target=target;return why;}
static const uint64_t ldl_mask[8]={UINT64_C(0x00ffffffffffffff),UINT64_C(0x0000ffffffffffff),UINT64_C(0x000000ffffffffff),UINT64_C(0x00000000ffffffff),UINT64_C(0x0000000000ffffff),UINT64_C(0x000000000000ffff),UINT64_C(0x00000000000000ff),0};
static const uint64_t ldr_mask[8]={0,UINT64_C(0xff00000000000000),UINT64_C(0xffff000000000000),UINT64_C(0xffffff0000000000),UINT64_C(0xffffffff00000000),UINT64_C(0xffffffffff000000),UINT64_C(0xffffffffffff0000),UINT64_C(0xffffffffffffff00)};
static const uint64_t sdl_mask[8]={UINT64_C(0xffffffffffffff00),UINT64_C(0xffffffffffff0000),UINT64_C(0xffffffffff000000),UINT64_C(0xffffffff00000000),UINT64_C(0xffffff0000000000),UINT64_C(0xffff000000000000),UINT64_C(0xff00000000000000),0};
static const uint64_t sdr_mask[8]={0,UINT64_C(0x00000000000000ff),UINT64_C(0x000000000000ffff),UINT64_C(0x0000000000ffffff),UINT64_C(0x00000000ffffffff),UINT64_C(0x000000ffffffffff),UINT64_C(0x0000ffffffffffff),UINT64_C(0x00ffffffffffffff)};
uint32_t nocturneBattleAlarmRegistration(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
{
 uint64_t target=UINT64_C(0x80076440),started,return_pc,value;uint32_t address=0,ea=0,offset=0;uint8_t bytes[8];
 if(!m||!ram||!ram->read||!ram->write||!s)return NOCTURNE_WAKEUP_INPUT_DOMAIN;
 memset(s,0,sizeof(*s));m->pc=UINT32_C(0x80076440);
 if(!limit||m->gpr[0][0]||m->gpr[0][1]||m->gpr[0][2]||m->gpr[0][3])return stop(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN,0,0,0);
 started=m->instructions;return_pc=(uint32_t)lo(m,31u);
#define STEP(p) do{m->pc=(p);if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);++m->instructions;}while(0)
#define READ(a,n) do{address=(a);if((address&((n)-1u))||!ram->read(ram->owner,address,bytes,(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);value=unpack(bytes,(n));}while(0)
#define WRITE(a,n,v) do{address=(a);pack(bytes,(v),(n));if((address&((n)-1u))||!ram->write(ram->owner,address,bytes,(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);}while(0)
dispatch:
 if(target==return_pc){m->pc=(uint32_t)return_pc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,return_pc);}
 switch((uint32_t)target){
 case UINT32_C(0x80076038):goto L_80076038;
 case UINT32_C(0x8007603c):goto L_8007603c;
 case UINT32_C(0x80076040):goto L_80076040;
 case UINT32_C(0x80076044):goto L_80076044;
 case UINT32_C(0x80076048):goto L_80076048;
 case UINT32_C(0x8007604c):goto L_8007604c;
 case UINT32_C(0x80076050):goto L_80076050;
 case UINT32_C(0x80076058):goto L_80076058;
 case UINT32_C(0x8007605c):goto L_8007605c;
 case UINT32_C(0x80076060):goto L_80076060;
 case UINT32_C(0x80076064):goto L_80076064;
 case UINT32_C(0x80076068):goto L_80076068;
 case UINT32_C(0x8007606c):goto L_8007606c;
 case UINT32_C(0x80076070):goto L_80076070;
 case UINT32_C(0x80076074):goto L_80076074;
 case UINT32_C(0x80076078):goto L_80076078;
 case UINT32_C(0x8007607c):goto L_8007607c;
 case UINT32_C(0x80076080):goto L_80076080;
 case UINT32_C(0x80076084):goto L_80076084;
 case UINT32_C(0x80076088):goto L_80076088;
 case UINT32_C(0x8007608c):goto L_8007608c;
 case UINT32_C(0x80076090):goto L_80076090;
 case UINT32_C(0x80076094):goto L_80076094;
 case UINT32_C(0x80076098):goto L_80076098;
 case UINT32_C(0x8007609c):goto L_8007609c;
 case UINT32_C(0x800760a0):goto L_800760a0;
 case UINT32_C(0x800760a4):goto L_800760a4;
 case UINT32_C(0x800760a8):goto L_800760a8;
 case UINT32_C(0x800760ac):goto L_800760ac;
 case UINT32_C(0x800760b0):goto L_800760b0;
 case UINT32_C(0x800760b4):goto L_800760b4;
 case UINT32_C(0x800760b8):goto L_800760b8;
 case UINT32_C(0x800760bc):goto L_800760bc;
 case UINT32_C(0x800760c0):goto L_800760c0;
 case UINT32_C(0x800760c4):goto L_800760c4;
 case UINT32_C(0x800760c8):goto L_800760c8;
 case UINT32_C(0x800760cc):goto L_800760cc;
 case UINT32_C(0x800760d0):goto L_800760d0;
 case UINT32_C(0x800760d4):goto L_800760d4;
 case UINT32_C(0x800760d8):goto L_800760d8;
 case UINT32_C(0x800760dc):goto L_800760dc;
 case UINT32_C(0x800760e0):goto L_800760e0;
 case UINT32_C(0x800760e4):goto L_800760e4;
 case UINT32_C(0x800760e8):goto L_800760e8;
 case UINT32_C(0x800760ec):goto L_800760ec;
 case UINT32_C(0x800760f0):goto L_800760f0;
 case UINT32_C(0x800760f4):goto L_800760f4;
 case UINT32_C(0x800760f8):goto L_800760f8;
 case UINT32_C(0x800760fc):goto L_800760fc;
 case UINT32_C(0x80076100):goto L_80076100;
 case UINT32_C(0x80076104):goto L_80076104;
 case UINT32_C(0x80076108):goto L_80076108;
 case UINT32_C(0x8007610c):goto L_8007610c;
 case UINT32_C(0x80076110):goto L_80076110;
 case UINT32_C(0x80076114):goto L_80076114;
 case UINT32_C(0x80076118):goto L_80076118;
 case UINT32_C(0x8007611c):goto L_8007611c;
 case UINT32_C(0x80076120):goto L_80076120;
 case UINT32_C(0x80076124):goto L_80076124;
 case UINT32_C(0x80076128):goto L_80076128;
 case UINT32_C(0x8007612c):goto L_8007612c;
 case UINT32_C(0x80076130):goto L_80076130;
 case UINT32_C(0x80076134):goto L_80076134;
 case UINT32_C(0x80076138):goto L_80076138;
 case UINT32_C(0x8007613c):goto L_8007613c;
 case UINT32_C(0x80076140):goto L_80076140;
 case UINT32_C(0x80076144):goto L_80076144;
 case UINT32_C(0x80076148):goto L_80076148;
 case UINT32_C(0x8007614c):goto L_8007614c;
 case UINT32_C(0x80076150):goto L_80076150;
 case UINT32_C(0x80076154):goto L_80076154;
 case UINT32_C(0x80076158):goto L_80076158;
 case UINT32_C(0x80076160):goto L_80076160;
 case UINT32_C(0x80076164):goto L_80076164;
 case UINT32_C(0x80076168):goto L_80076168;
 case UINT32_C(0x8007616c):goto L_8007616c;
 case UINT32_C(0x80076170):goto L_80076170;
 case UINT32_C(0x80076174):goto L_80076174;
 case UINT32_C(0x80076178):goto L_80076178;
 case UINT32_C(0x8007617c):goto L_8007617c;
 case UINT32_C(0x80076180):goto L_80076180;
 case UINT32_C(0x80076184):goto L_80076184;
 case UINT32_C(0x80076188):goto L_80076188;
 case UINT32_C(0x8007618c):goto L_8007618c;
 case UINT32_C(0x80076190):goto L_80076190;
 case UINT32_C(0x80076194):goto L_80076194;
 case UINT32_C(0x80076198):goto L_80076198;
 case UINT32_C(0x8007619c):goto L_8007619c;
 case UINT32_C(0x800761a0):goto L_800761a0;
 case UINT32_C(0x800761a4):goto L_800761a4;
 case UINT32_C(0x800761a8):goto L_800761a8;
 case UINT32_C(0x800761ac):goto L_800761ac;
 case UINT32_C(0x800761b0):goto L_800761b0;
 case UINT32_C(0x800761b4):goto L_800761b4;
 case UINT32_C(0x800761b8):goto L_800761b8;
 case UINT32_C(0x800761bc):goto L_800761bc;
 case UINT32_C(0x800761c0):goto L_800761c0;
 case UINT32_C(0x800761c4):goto L_800761c4;
 case UINT32_C(0x800761c8):goto L_800761c8;
 case UINT32_C(0x800761cc):goto L_800761cc;
 case UINT32_C(0x800761d0):goto L_800761d0;
 case UINT32_C(0x800761d4):goto L_800761d4;
 case UINT32_C(0x800761d8):goto L_800761d8;
 case UINT32_C(0x800761dc):goto L_800761dc;
 case UINT32_C(0x800761e0):goto L_800761e0;
 case UINT32_C(0x800761e4):goto L_800761e4;
 case UINT32_C(0x800761e8):goto L_800761e8;
 case UINT32_C(0x800761ec):goto L_800761ec;
 case UINT32_C(0x800761f0):goto L_800761f0;
 case UINT32_C(0x800761f4):goto L_800761f4;
 case UINT32_C(0x800761f8):goto L_800761f8;
 case UINT32_C(0x800761fc):goto L_800761fc;
 case UINT32_C(0x80076200):goto L_80076200;
 case UINT32_C(0x80076204):goto L_80076204;
 case UINT32_C(0x80076208):goto L_80076208;
 case UINT32_C(0x8007620c):goto L_8007620c;
 case UINT32_C(0x80076210):goto L_80076210;
 case UINT32_C(0x80076214):goto L_80076214;
 case UINT32_C(0x80076218):goto L_80076218;
 case UINT32_C(0x8007621c):goto L_8007621c;
 case UINT32_C(0x80076220):goto L_80076220;
 case UINT32_C(0x80076224):goto L_80076224;
 case UINT32_C(0x80076228):goto L_80076228;
 case UINT32_C(0x8007622c):goto L_8007622c;
 case UINT32_C(0x80076230):goto L_80076230;
 case UINT32_C(0x80076234):goto L_80076234;
 case UINT32_C(0x80076238):goto L_80076238;
 case UINT32_C(0x8007623c):goto L_8007623c;
 case UINT32_C(0x80076240):goto L_80076240;
 case UINT32_C(0x80076244):goto L_80076244;
 case UINT32_C(0x80076248):goto L_80076248;
 case UINT32_C(0x8007624c):goto L_8007624c;
 case UINT32_C(0x80076250):goto L_80076250;
 case UINT32_C(0x80076254):goto L_80076254;
 case UINT32_C(0x80076258):goto L_80076258;
 case UINT32_C(0x8007625c):goto L_8007625c;
 case UINT32_C(0x80076260):goto L_80076260;
 case UINT32_C(0x80076264):goto L_80076264;
 case UINT32_C(0x80076268):goto L_80076268;
 case UINT32_C(0x8007626c):goto L_8007626c;
 case UINT32_C(0x80076270):goto L_80076270;
 case UINT32_C(0x80076274):goto L_80076274;
 case UINT32_C(0x80076278):goto L_80076278;
 case UINT32_C(0x8007627c):goto L_8007627c;
 case UINT32_C(0x80076280):goto L_80076280;
 case UINT32_C(0x80076284):goto L_80076284;
 case UINT32_C(0x80076288):goto L_80076288;
 case UINT32_C(0x8007628c):goto L_8007628c;
 case UINT32_C(0x80076290):goto L_80076290;
 case UINT32_C(0x80076294):goto L_80076294;
 case UINT32_C(0x80076298):goto L_80076298;
 case UINT32_C(0x80076440):goto L_80076440;
 case UINT32_C(0x80076444):goto L_80076444;
 case UINT32_C(0x80076448):goto L_80076448;
 case UINT32_C(0x8007644c):goto L_8007644c;
 case UINT32_C(0x80076450):goto L_80076450;
 case UINT32_C(0x80076454):goto L_80076454;
 case UINT32_C(0x80076458):goto L_80076458;
 case UINT32_C(0x8007645c):goto L_8007645c;
 case UINT32_C(0x80076460):goto L_80076460;
 case UINT32_C(0x80076464):goto L_80076464;
 case UINT32_C(0x80076468):goto L_80076468;
 case UINT32_C(0x8007646c):goto L_8007646c;
 case UINT32_C(0x80076470):goto L_80076470;
 case UINT32_C(0x80076474):goto L_80076474;
 case UINT32_C(0x80076478):goto L_80076478;
 case UINT32_C(0x8007647c):goto L_8007647c;
 case UINT32_C(0x80076480):goto L_80076480;
 default:m->pc=(uint32_t)target;return stop(m,s,NOCTURNE_WAKEUP_UNKNOWN_CODE,0,0,target);}
L_80076038:
 STEP(UINT32_C(0x80076038)); /* 00a4202a slt a0,a1,a0 */
 set(m,4u,((int64_t)lo(m,5u)<(int64_t)lo(m,4u)));target=UINT64_C(0x8007603c);goto dispatch;
L_8007603c:
 STEP(UINT32_C(0x8007603c)); /* 10800003 beq a0,zero,8007604c */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x80076040));set(m,2u,sx(UINT32_C(0x00010000)));target=taken?UINT64_C(0x8007604c):UINT64_C(0x80076044);goto dispatch;}
L_80076040:
 STEP(UINT32_C(0x80076040)); /* 3c020001 lui v0,zero,0x1 */
 set(m,2u,sx(UINT32_C(0x00010000)));target=UINT64_C(0x80076044);goto dispatch;
L_80076044:
 STEP(UINT32_C(0x80076044)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076048));set(m,2u,lo(m,5u)|lo(m,2u));goto dispatch;
L_80076048:
 STEP(UINT32_C(0x80076048)); /* 00a21025 or v0,a1,v0 */
 set(m,2u,lo(m,5u)|lo(m,2u));target=UINT64_C(0x8007604c);goto dispatch;
L_8007604c:
 STEP(UINT32_C(0x8007604c)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076050));set(m,2u,lo(m,5u)+lo(m,0u));goto dispatch;
L_80076050:
 STEP(UINT32_C(0x80076050)); /* 00a0102d daddu v0,a1,zero */
 set(m,2u,lo(m,5u)+lo(m,0u));target=UINT64_C(0x80076054);goto dispatch;
L_80076058:
 STEP(UINT32_C(0x80076058)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=UINT64_C(0x8007605c);goto dispatch;
L_8007605c:
 STEP(UINT32_C(0x8007605c)); /* ffb30030 sd s3,0x30(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u,lo(m,19u));target=UINT64_C(0x80076060);goto dispatch;
L_80076060:
 STEP(UINT32_C(0x80076060)); /* 3c138007 lui s3,zero,0x8007 */
 set(m,19u,sx(UINT32_C(0x80070000)));target=UINT64_C(0x80076064);goto dispatch;
L_80076064:
 STEP(UINT32_C(0x80076064)); /* ffb60060 sd s6,0x60(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u,lo(m,22u));target=UINT64_C(0x80076068);goto dispatch;
L_80076068:
 STEP(UINT32_C(0x80076068)); /* ffb50050 sd s5,0x50(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u,lo(m,21u));target=UINT64_C(0x8007606c);goto dispatch;
L_8007606c:
 STEP(UINT32_C(0x8007606c)); /* 0080b02d daddu s6,a0,zero */
 set(m,22u,lo(m,4u)+lo(m,0u));target=UINT64_C(0x80076070);goto dispatch;
L_80076070:
 STEP(UINT32_C(0x80076070)); /* ffb00000 sd s0,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,16u));target=UINT64_C(0x80076074);goto dispatch;
L_80076074:
 STEP(UINT32_C(0x80076074)); /* 00a0a82d daddu s5,a1,zero */
 set(m,21u,lo(m,5u)+lo(m,0u));target=UINT64_C(0x80076078);goto dispatch;
L_80076078:
 STEP(UINT32_C(0x80076078)); /* 8e626700 lw v0,0x6700(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT64_C(0x8007607c);goto dispatch;
L_8007607c:
 STEP(UINT32_C(0x8007607c)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=UINT64_C(0x80076080);goto dispatch;
L_80076080:
 STEP(UINT32_C(0x80076080)); /* ffbf0070 sd ra,0x70(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u,lo(m,31u));target=UINT64_C(0x80076084);goto dispatch;
L_80076084:
 STEP(UINT32_C(0x80076084)); /* ffb40040 sd s4,0x40(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u,lo(m,20u));target=UINT64_C(0x80076088);goto dispatch;
L_80076088:
 STEP(UINT32_C(0x80076088)); /* ffb20020 sd s2,0x20(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u,lo(m,18u));target=UINT64_C(0x8007608c);goto dispatch;
L_8007608c:
 STEP(UINT32_C(0x8007608c)); /* 18400028 blez v0,zero,80076130 */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x80076090));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u,lo(m,17u));target=taken?UINT64_C(0x80076130):UINT64_C(0x80076094);goto dispatch;}
L_80076090:
 STEP(UINT32_C(0x80076090)); /* ffb10010 sd s1,0x10(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u,lo(m,17u));target=UINT64_C(0x80076094);goto dispatch;
L_80076094:
 STEP(UINT32_C(0x80076094)); /* 3c148007 lui s4,zero,0x8007 */
 set(m,20u,sx(UINT32_C(0x80070000)));target=UINT64_C(0x80076098);goto dispatch;
L_80076098:
 STEP(UINT32_C(0x80076098)); /* 24120014 addiu s2,zero,20 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT64_C(0x8007609c);goto dispatch;
L_8007609c:
 STEP(UINT32_C(0x8007609c)); /* 00000000 nop */
 /* nop */target=UINT64_C(0x800760a0);goto dispatch;
L_800760a0:
 STEP(UINT32_C(0x800760a0)); /* 26916740 addiu s1,s4,26432 */
 set(m,17u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00006740)));target=UINT64_C(0x800760a4);goto dispatch;
L_800760a4:
 STEP(UINT32_C(0x800760a4)); /* 02121018 mult_rd v0,s0,s2 */
 {int64_t product;if(lo(m,16u)!=sx((uint32_t)lo(m,16u))||lo(m,18u)!=sx((uint32_t)lo(m,18u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,16u)*(int64_t)(int32_t)lo(m,18u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=UINT64_C(0x800760a8);goto dispatch;
L_800760a8:
 STEP(UINT32_C(0x800760a8)); /* 02c0202d daddu a0,s6,zero */
 set(m,4u,lo(m,22u)+lo(m,0u));target=UINT64_C(0x800760ac);goto dispatch;
L_800760ac:
 STEP(UINT32_C(0x800760ac)); /* 00511021 addu v0,v0,s1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,17u)));target=UINT64_C(0x800760b0);goto dispatch;
L_800760b0:
 STEP(UINT32_C(0x800760b0)); /* 0c01d80e jal 80076038 */
 set(m,31u,UINT64_C(0x800760b8));STEP(UINT32_C(0x800760b4));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),2u);set(m,5u,value);target=UINT64_C(0x80076038);goto dispatch;
L_800760b4:
 STEP(UINT32_C(0x800760b4)); /* 94450000 lhu a1,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),2u);set(m,5u,value);target=UINT64_C(0x800760b8);goto dispatch;
L_800760b8:
 STEP(UINT32_C(0x800760b8)); /* 02a2102a slt v0,s5,v0 */
 set(m,2u,((int64_t)lo(m,21u)<(int64_t)lo(m,2u)));target=UINT64_C(0x800760bc);goto dispatch;
L_800760bc:
 STEP(UINT32_C(0x800760bc)); /* 10400018 beq v0,zero,80076120 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x800760c0));READ((uint32_t)lo(m,19u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=taken?UINT64_C(0x80076120):UINT64_C(0x800760c4);goto dispatch;}
L_800760c0:
 STEP(UINT32_C(0x800760c0)); /* 8e626700 lw v0,0x6700(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT64_C(0x800760c4);goto dispatch;
L_800760c4:
 STEP(UINT32_C(0x800760c4)); /* 2444ffff addiu a0,v0,-1 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=UINT64_C(0x800760c8);goto dispatch;
L_800760c8:
 STEP(UINT32_C(0x800760c8)); /* 0090182a slt v1,a0,s0 */
 set(m,3u,((int64_t)lo(m,4u)<(int64_t)lo(m,16u)));target=UINT64_C(0x800760cc);goto dispatch;
L_800760cc:
 STEP(UINT32_C(0x800760cc)); /* 14600018 bne v1,zero,80076130 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x800760d0));{int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,18u)!=sx((uint32_t)lo(m,18u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,18u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=taken?UINT64_C(0x80076130):UINT64_C(0x800760d4);goto dispatch;}
L_800760d0:
 STEP(UINT32_C(0x800760d0)); /* 00921018 mult_rd v0,a0,s2 */
 {int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,18u)!=sx((uint32_t)lo(m,18u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,18u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=UINT64_C(0x800760d4);goto dispatch;
L_800760d4:
 STEP(UINT32_C(0x800760d4)); /* 00511821 addu v1,v0,s1 */
 set(m,3u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,17u)));target=UINT64_C(0x800760d8);goto dispatch;
L_800760d8:
 STEP(UINT32_C(0x800760d8)); /* 68650007 ldl a1,0x7(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000007);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,5u,(lo(m,5u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT64_C(0x800760dc);goto dispatch;
L_800760dc:
 STEP(UINT32_C(0x800760dc)); /* 6c650000 ldr a1,0x0(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000000);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,5u,(lo(m,5u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT64_C(0x800760e0);goto dispatch;
L_800760e0:
 STEP(UINT32_C(0x800760e0)); /* 6866000f ldl a2,0xf(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x0000000f);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,6u,(lo(m,6u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT64_C(0x800760e4);goto dispatch;
L_800760e4:
 STEP(UINT32_C(0x800760e4)); /* 6c660008 ldr a2,0x8(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000008);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,6u,(lo(m,6u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT64_C(0x800760e8);goto dispatch;
L_800760e8:
 STEP(UINT32_C(0x800760e8)); /* 8c670010 lw a3,0x10(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000010),4u);set(m,7u,sx((uint32_t)value));target=UINT64_C(0x800760ec);goto dispatch;
L_800760ec:
 STEP(UINT32_C(0x800760ec)); /* b065001b sdl a1,0x1b(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x0000001b);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,5u)>>((7u-offset)*8u)));target=UINT64_C(0x800760f0);goto dispatch;
L_800760f0:
 STEP(UINT32_C(0x800760f0)); /* b4650014 sdr a1,0x14(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000014);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,5u)<<(offset*8u)));target=UINT64_C(0x800760f4);goto dispatch;
L_800760f4:
 STEP(UINT32_C(0x800760f4)); /* b0660023 sdl a2,0x23(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000023);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,6u)>>((7u-offset)*8u)));target=UINT64_C(0x800760f8);goto dispatch;
L_800760f8:
 STEP(UINT32_C(0x800760f8)); /* b466001c sdr a2,0x1c(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x0000001c);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,6u)<<(offset*8u)));target=UINT64_C(0x800760fc);goto dispatch;
L_800760fc:
 STEP(UINT32_C(0x800760fc)); /* ac670024 sw a3,0x24(v1) */
 WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000024),4u,lo(m,7u));target=UINT64_C(0x80076100);goto dispatch;
L_80076100:
 STEP(UINT32_C(0x80076100)); /* 2484ffff addiu a0,a0,-1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=UINT64_C(0x80076104);goto dispatch;
L_80076104:
 STEP(UINT32_C(0x80076104)); /* 2463ffec addiu v1,v1,-20 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffec)));target=UINT64_C(0x80076108);goto dispatch;
L_80076108:
 STEP(UINT32_C(0x80076108)); /* 0090102a slt v0,a0,s0 */
 set(m,2u,((int64_t)lo(m,4u)<(int64_t)lo(m,16u)));target=UINT64_C(0x8007610c);goto dispatch;
L_8007610c:
 STEP(UINT32_C(0x8007610c)); /* 00000000 nop */
 /* nop */target=UINT64_C(0x80076110);goto dispatch;
L_80076110:
 STEP(UINT32_C(0x80076110)); /* 1040fff1 beq v0,zero,800760d8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80076114));/* nop */target=taken?UINT64_C(0x800760d8):UINT64_C(0x80076118);goto dispatch;}
L_80076114:
 STEP(UINT32_C(0x80076114)); /* 00000000 nop */
 /* nop */target=UINT64_C(0x80076118);goto dispatch;
L_80076118:
 STEP(UINT32_C(0x80076118)); /* 10000006 beq zero,zero,80076134 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8007611c));set(m,2u,lo(m,16u)+lo(m,0u));target=taken?UINT64_C(0x80076134):UINT64_C(0x80076120);goto dispatch;}
L_8007611c:
 STEP(UINT32_C(0x8007611c)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=UINT64_C(0x80076120);goto dispatch;
L_80076120:
 STEP(UINT32_C(0x80076120)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=UINT64_C(0x80076124);goto dispatch;
L_80076124:
 STEP(UINT32_C(0x80076124)); /* 0202102a slt v0,s0,v0 */
 set(m,2u,((int64_t)lo(m,16u)<(int64_t)lo(m,2u)));target=UINT64_C(0x80076128);goto dispatch;
L_80076128:
 STEP(UINT32_C(0x80076128)); /* 1440ffdd bne v0,zero,800760a0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8007612c));set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=taken?UINT64_C(0x800760a0):UINT64_C(0x80076130);goto dispatch;}
L_8007612c:
 STEP(UINT32_C(0x8007612c)); /* 24120014 addiu s2,zero,20 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT64_C(0x80076130);goto dispatch;
L_80076130:
 STEP(UINT32_C(0x80076130)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=UINT64_C(0x80076134);goto dispatch;
L_80076134:
 STEP(UINT32_C(0x80076134)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u);set(m,31u,value);target=UINT64_C(0x80076138);goto dispatch;
L_80076138:
 STEP(UINT32_C(0x80076138)); /* dfb60060 ld s6,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u);set(m,22u,value);target=UINT64_C(0x8007613c);goto dispatch;
L_8007613c:
 STEP(UINT32_C(0x8007613c)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u);set(m,21u,value);target=UINT64_C(0x80076140);goto dispatch;
L_80076140:
 STEP(UINT32_C(0x80076140)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u);set(m,20u,value);target=UINT64_C(0x80076144);goto dispatch;
L_80076144:
 STEP(UINT32_C(0x80076144)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u);set(m,19u,value);target=UINT64_C(0x80076148);goto dispatch;
L_80076148:
 STEP(UINT32_C(0x80076148)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u);set(m,18u,value);target=UINT64_C(0x8007614c);goto dispatch;
L_8007614c:
 STEP(UINT32_C(0x8007614c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u);set(m,17u,value);target=UINT64_C(0x80076150);goto dispatch;
L_80076150:
 STEP(UINT32_C(0x80076150)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,16u,value);target=UINT64_C(0x80076154);goto dispatch;
L_80076154:
 STEP(UINT32_C(0x80076154)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076158));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_80076158:
 STEP(UINT32_C(0x80076158)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=UINT64_C(0x8007615c);goto dispatch;
L_80076160:
 STEP(UINT32_C(0x80076160)); /* 27bdff70 addiu sp,sp,-144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff70)));target=UINT64_C(0x80076164);goto dispatch;
L_80076164:
 STEP(UINT32_C(0x80076164)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT64_C(0x80076168);goto dispatch;
L_80076168:
 STEP(UINT32_C(0x80076168)); /* ffb70070 sd s7,0x70(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u,lo(m,23u));target=UINT64_C(0x8007616c);goto dispatch;
L_8007616c:
 STEP(UINT32_C(0x8007616c)); /* 34421800 ori v0,v0,0x1800 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1800));target=UINT64_C(0x80076170);goto dispatch;
L_80076170:
 STEP(UINT32_C(0x80076170)); /* ffb60060 sd s6,0x60(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u,lo(m,22u));target=UINT64_C(0x80076174);goto dispatch;
L_80076174:
 STEP(UINT32_C(0x80076174)); /* 00c0b82d daddu s7,a2,zero */
 set(m,23u,lo(m,6u)+lo(m,0u));target=UINT64_C(0x80076178);goto dispatch;
L_80076178:
 STEP(UINT32_C(0x80076178)); /* ffb50050 sd s5,0x50(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u,lo(m,21u));target=UINT64_C(0x8007617c);goto dispatch;
L_8007617c:
 STEP(UINT32_C(0x8007617c)); /* 00a0b02d daddu s6,a1,zero */
 set(m,22u,lo(m,5u)+lo(m,0u));target=UINT64_C(0x80076180);goto dispatch;
L_80076180:
 STEP(UINT32_C(0x80076180)); /* ffb30030 sd s3,0x30(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u,lo(m,19u));target=UINT64_C(0x80076184);goto dispatch;
L_80076184:
 STEP(UINT32_C(0x80076184)); /* 3c158007 lui s5,zero,0x8007 */
 set(m,21u,sx(UINT32_C(0x80070000)));target=UINT64_C(0x80076188);goto dispatch;
L_80076188:
 STEP(UINT32_C(0x80076188)); /* ffbf0080 sd ra,0x80(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),8u,lo(m,31u));target=UINT64_C(0x8007618c);goto dispatch;
L_8007618c:
 STEP(UINT32_C(0x8007618c)); /* 3093ffff andi s3,a0,0xffff */
 set(m,19u,lo(m,4u) & UINT64_C(0xffff));target=UINT64_C(0x80076190);goto dispatch;
L_80076190:
 STEP(UINT32_C(0x80076190)); /* ffb20020 sd s2,0x20(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u,lo(m,18u));target=UINT64_C(0x80076194);goto dispatch;
L_80076194:
 STEP(UINT32_C(0x80076194)); /* ffb10010 sd s1,0x10(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u,lo(m,17u));target=UINT64_C(0x80076198);goto dispatch;
L_80076198:
 STEP(UINT32_C(0x80076198)); /* ffb00000 sd s0,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,16u));target=UINT64_C(0x8007619c);goto dispatch;
L_8007619c:
 STEP(UINT32_C(0x8007619c)); /* ffb40040 sd s4,0x40(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u,lo(m,20u));target=UINT64_C(0x800761a0);goto dispatch;
L_800761a0:
 STEP(UINT32_C(0x800761a0)); /* 8ea36700 lw v1,0x6700(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00006700),4u);set(m,3u,sx((uint32_t)value));target=UINT64_C(0x800761a4);goto dispatch;
L_800761a4:
 STEP(UINT32_C(0x800761a4)); /* 8c540000 lw s4,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u);set(m,20u,sx((uint32_t)value));target=UINT64_C(0x800761a8);goto dispatch;
L_800761a8:
 STEP(UINT32_C(0x800761a8)); /* 28630040 slti v1,v1,64 */
 set(m,3u,((int64_t)lo(m,3u)<INT64_C(64)));target=UINT64_C(0x800761ac);goto dispatch;
L_800761ac:
 STEP(UINT32_C(0x800761ac)); /* 14600008 bne v1,zero,800761d0 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x800761b0));set(m,19u,sx((uint32_t)lo(m,19u)+(uint32_t)lo(m,20u)));target=taken?UINT64_C(0x800761d0):UINT64_C(0x800761b4);goto dispatch;}
L_800761b0:
 STEP(UINT32_C(0x800761b0)); /* 02749821 addu s3,s3,s4 */
 set(m,19u,sx((uint32_t)lo(m,19u)+(uint32_t)lo(m,20u)));target=UINT64_C(0x800761b4);goto dispatch;
L_800761b4:
 STEP(UINT32_C(0x800761b4)); /* 1000002e beq zero,zero,80076270 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800761b8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=taken?UINT64_C(0x80076270):UINT64_C(0x800761bc);goto dispatch;}
L_800761b8:
 STEP(UINT32_C(0x800761b8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=UINT64_C(0x800761bc);goto dispatch;
L_800761bc:
 STEP(UINT32_C(0x800761bc)); /* 0060902d daddu s2,v1,zero */
 set(m,18u,lo(m,3u)+lo(m,0u));target=UINT64_C(0x800761c0);goto dispatch;
L_800761c0:
 STEP(UINT32_C(0x800761c0)); /* 00621014 dsllv v0,v0,v1 */
 set(m,2u,lo(m,2u)<<(lo(m,3u)&63u));target=UINT64_C(0x800761c4);goto dispatch;
L_800761c4:
 STEP(UINT32_C(0x800761c4)); /* 00821025 or v0,a0,v0 */
 set(m,2u,lo(m,4u)|lo(m,2u));target=UINT64_C(0x800761c8);goto dispatch;
L_800761c8:
 STEP(UINT32_C(0x800761c8)); /* 1000000d beq zero,zero,80076200 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800761cc));WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00006708),8u,lo(m,2u));target=taken?UINT64_C(0x80076200):UINT64_C(0x800761d0);goto dispatch;}
L_800761cc:
 STEP(UINT32_C(0x800761cc)); /* fca26708 sd v0,0x6708(a1) */
 WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00006708),8u,lo(m,2u));target=UINT64_C(0x800761d0);goto dispatch;
L_800761d0:
 STEP(UINT32_C(0x800761d0)); /* 3c058007 lui a1,zero,0x8007 */
 set(m,5u,sx(UINT32_C(0x80070000)));target=UINT64_C(0x800761d4);goto dispatch;
L_800761d4:
 STEP(UINT32_C(0x800761d4)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=UINT64_C(0x800761d8);goto dispatch;
L_800761d8:
 STEP(UINT32_C(0x800761d8)); /* dca46708 ld a0,0x6708(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00006708),8u);set(m,4u,value);target=UINT64_C(0x800761dc);goto dispatch;
L_800761dc:
 STEP(UINT32_C(0x800761dc)); /* 00641016 dsrlv v0,a0,v1 */
 set(m,2u,lo(m,4u)>>(lo(m,3u)&63u));target=UINT64_C(0x800761e0);goto dispatch;
L_800761e0:
 STEP(UINT32_C(0x800761e0)); /* 30420001 andi v0,v0,0x1 */
 set(m,2u,lo(m,2u) & UINT64_C(0x1));target=UINT64_C(0x800761e4);goto dispatch;
L_800761e4:
 STEP(UINT32_C(0x800761e4)); /* 1040fff5 beq v0,zero,800761bc */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x800761e8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=taken?UINT64_C(0x800761bc):UINT64_C(0x800761ec);goto dispatch;}
L_800761e8:
 STEP(UINT32_C(0x800761e8)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=UINT64_C(0x800761ec);goto dispatch;
L_800761ec:
 STEP(UINT32_C(0x800761ec)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=UINT64_C(0x800761f0);goto dispatch;
L_800761f0:
 STEP(UINT32_C(0x800761f0)); /* 28620040 slti v0,v1,64 */
 set(m,2u,((int64_t)lo(m,3u)<INT64_C(64)));target=UINT64_C(0x800761f4);goto dispatch;
L_800761f4:
 STEP(UINT32_C(0x800761f4)); /* 1440fffa bne v0,zero,800761e0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x800761f8));set(m,2u,lo(m,4u)>>(lo(m,3u)&63u));target=taken?UINT64_C(0x800761e0):UINT64_C(0x800761fc);goto dispatch;}
L_800761f8:
 STEP(UINT32_C(0x800761f8)); /* 00641016 dsrlv v0,a0,v1 */
 set(m,2u,lo(m,4u)>>(lo(m,3u)&63u));target=UINT64_C(0x800761fc);goto dispatch;
L_800761fc:
 STEP(UINT32_C(0x800761fc)); /* 2412ffff addiu s2,zero,-1 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=UINT64_C(0x80076200);goto dispatch;
L_80076200:
 STEP(UINT32_C(0x80076200)); /* 0640001b bltz s2,80076270 */
 {int taken=((int64_t)lo(m,18u)<0);STEP(UINT32_C(0x80076204));set(m,2u,lo(m,18u)+lo(m,0u));target=taken?UINT64_C(0x80076270):UINT64_C(0x80076208);goto dispatch;}
L_80076204:
 STEP(UINT32_C(0x80076204)); /* 0240102d daddu v0,s2,zero */
 set(m,2u,lo(m,18u)+lo(m,0u));target=UINT64_C(0x80076208);goto dispatch;
L_80076208:
 STEP(UINT32_C(0x80076208)); /* 0380882d daddu s1,gp,zero */
 set(m,17u,lo(m,28u)+lo(m,0u));target=UINT64_C(0x8007620c);goto dispatch;
L_8007620c:
 STEP(UINT32_C(0x8007620c)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=UINT64_C(0x80076210);goto dispatch;
L_80076210:
 STEP(UINT32_C(0x80076210)); /* 0c01d816 jal 80076058 */
 set(m,31u,UINT64_C(0x80076218));STEP(UINT32_C(0x80076214));set(m,4u,lo(m,20u)+lo(m,0u));target=UINT64_C(0x80076058);goto dispatch;
L_80076214:
 STEP(UINT32_C(0x80076214)); /* 0280202d daddu a0,s4,zero */
 set(m,4u,lo(m,20u)+lo(m,0u));target=UINT64_C(0x80076218);goto dispatch;
L_80076218:
 STEP(UINT32_C(0x80076218)); /* 24040014 addiu a0,zero,20 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT64_C(0x8007621c);goto dispatch;
L_8007621c:
 STEP(UINT32_C(0x8007621c)); /* 3c088007 lui t0,zero,0x8007 */
 set(m,8u,sx(UINT32_C(0x80070000)));target=UINT64_C(0x80076220);goto dispatch;
L_80076220:
 STEP(UINT32_C(0x80076220)); /* 00441018 mult_rd v0,v0,a0 */
 {int64_t product;if(lo(m,2u)!=sx((uint32_t)lo(m,2u))||lo(m,4u)!=sx((uint32_t)lo(m,4u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,2u)*(int64_t)(int32_t)lo(m,4u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=UINT64_C(0x80076224);goto dispatch;
L_80076224:
 STEP(UINT32_C(0x80076224)); /* 25036740 addiu v1,t0,26432 */
 set(m,3u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00006740)));target=UINT64_C(0x80076228);goto dispatch;
L_80076228:
 STEP(UINT32_C(0x80076228)); /* 8ea56700 lw a1,0x6700(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00006700),4u);set(m,5u,sx((uint32_t)value));target=UINT64_C(0x8007622c);goto dispatch;
L_8007622c:
 STEP(UINT32_C(0x8007622c)); /* 24700004 addiu s0,v1,4 */
 set(m,16u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000004)));target=UINT64_C(0x80076230);goto dispatch;
L_80076230:
 STEP(UINT32_C(0x80076230)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=UINT64_C(0x80076234);goto dispatch;
L_80076234:
 STEP(UINT32_C(0x80076234)); /* 00432021 addu a0,v0,v1 */
 set(m,4u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=UINT64_C(0x80076238);goto dispatch;
L_80076238:
 STEP(UINT32_C(0x80076238)); /* 00623821 addu a3,v1,v0 */
 set(m,7u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=UINT64_C(0x8007623c);goto dispatch;
L_8007623c:
 STEP(UINT32_C(0x8007623c)); /* 00508021 addu s0,v0,s0 */
 set(m,16u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=UINT64_C(0x80076240);goto dispatch;
L_80076240:
 STEP(UINT32_C(0x80076240)); /* a4940002 sh s4,0x2(a0) */
 WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000002),2u,lo(m,20u));target=UINT64_C(0x80076244);goto dispatch;
L_80076244:
 STEP(UINT32_C(0x80076244)); /* a4930000 sh s3,0x0(a0) */
 WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),2u,lo(m,19u));target=UINT64_C(0x80076248);goto dispatch;
L_80076248:
 STEP(UINT32_C(0x80076248)); /* 00e0302d daddu a2,a3,zero */
 set(m,6u,lo(m,7u)+lo(m,0u));target=UINT64_C(0x8007624c);goto dispatch;
L_8007624c:
 STEP(UINT32_C(0x8007624c)); /* ae120000 sw s2,0x0(s0) */
 WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),4u,lo(m,18u));target=UINT64_C(0x80076250);goto dispatch;
L_80076250:
 STEP(UINT32_C(0x80076250)); /* 00c0182d daddu v1,a2,zero */
 set(m,3u,lo(m,6u)+lo(m,0u));target=UINT64_C(0x80076254);goto dispatch;
L_80076254:
 STEP(UINT32_C(0x80076254)); /* acf10010 sw s1,0x10(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000010),4u,lo(m,17u));target=UINT64_C(0x80076258);goto dispatch;
L_80076258:
 STEP(UINT32_C(0x80076258)); /* 95046740 lhu a0,0x6740(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00006740),2u);set(m,4u,value);target=UINT64_C(0x8007625c);goto dispatch;
L_8007625c:
 STEP(UINT32_C(0x8007625c)); /* acd60008 sw s6,0x8(a2) */
 WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000008),4u,lo(m,22u));target=UINT64_C(0x80076260);goto dispatch;
L_80076260:
 STEP(UINT32_C(0x80076260)); /* ac77000c sw s7,0xc(v1) */
 WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),4u,lo(m,23u));target=UINT64_C(0x80076264);goto dispatch;
L_80076264:
 STEP(UINT32_C(0x80076264)); /* 0c01d918 jal 80076460 */
 set(m,31u,UINT64_C(0x8007626c));STEP(UINT32_C(0x80076268));WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00006700),4u,lo(m,5u));target=UINT64_C(0x80076460);goto dispatch;
L_80076268:
 STEP(UINT32_C(0x80076268)); /* aea56700 sw a1,0x6700(s5) */
 WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00006700),4u,lo(m,5u));target=UINT64_C(0x8007626c);goto dispatch;
L_8007626c:
 STEP(UINT32_C(0x8007626c)); /* 8e020000 lw v0,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),4u);set(m,2u,sx((uint32_t)value));target=UINT64_C(0x80076270);goto dispatch;
L_80076270:
 STEP(UINT32_C(0x80076270)); /* dfbf0080 ld ra,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),8u);set(m,31u,value);target=UINT64_C(0x80076274);goto dispatch;
L_80076274:
 STEP(UINT32_C(0x80076274)); /* dfb70070 ld s7,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u);set(m,23u,value);target=UINT64_C(0x80076278);goto dispatch;
L_80076278:
 STEP(UINT32_C(0x80076278)); /* dfb60060 ld s6,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u);set(m,22u,value);target=UINT64_C(0x8007627c);goto dispatch;
L_8007627c:
 STEP(UINT32_C(0x8007627c)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u);set(m,21u,value);target=UINT64_C(0x80076280);goto dispatch;
L_80076280:
 STEP(UINT32_C(0x80076280)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u);set(m,20u,value);target=UINT64_C(0x80076284);goto dispatch;
L_80076284:
 STEP(UINT32_C(0x80076284)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u);set(m,19u,value);target=UINT64_C(0x80076288);goto dispatch;
L_80076288:
 STEP(UINT32_C(0x80076288)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u);set(m,18u,value);target=UINT64_C(0x8007628c);goto dispatch;
L_8007628c:
 STEP(UINT32_C(0x8007628c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u);set(m,17u,value);target=UINT64_C(0x80076290);goto dispatch;
L_80076290:
 STEP(UINT32_C(0x80076290)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,16u,value);target=UINT64_C(0x80076294);goto dispatch;
L_80076294:
 STEP(UINT32_C(0x80076294)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076298));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));goto dispatch;
L_80076298:
 STEP(UINT32_C(0x80076298)); /* 27bd0090 addiu sp,sp,144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));target=UINT64_C(0x8007629c);goto dispatch;
L_80076440:
 STEP(UINT32_C(0x80076440)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=UINT64_C(0x80076444);goto dispatch;
L_80076444:
 STEP(UINT32_C(0x80076444)); /* ffbf0000 sd ra,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,31u));target=UINT64_C(0x80076448);goto dispatch;
L_80076448:
 STEP(UINT32_C(0x80076448)); /* 0c01d858 jal 80076160 */
 set(m,31u,UINT64_C(0x80076450));STEP(UINT32_C(0x8007644c));set(m,4u,lo(m,4u) & UINT64_C(0xffff));target=UINT64_C(0x80076160);goto dispatch;
L_8007644c:
 STEP(UINT32_C(0x8007644c)); /* 3084ffff andi a0,a0,0xffff */
 set(m,4u,lo(m,4u) & UINT64_C(0xffff));target=UINT64_C(0x80076450);goto dispatch;
L_80076450:
 STEP(UINT32_C(0x80076450)); /* 0000000f sync 0 */
 ++m->sync_p; /* actual SYNC0 value barrier, no timer/cache fabrication */target=UINT64_C(0x80076454);goto dispatch;
L_80076454:
 STEP(UINT32_C(0x80076454)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,31u,value);target=UINT64_C(0x80076458);goto dispatch;
L_80076458:
 STEP(UINT32_C(0x80076458)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x8007645c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_8007645c:
 STEP(UINT32_C(0x8007645c)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=UINT64_C(0x80076460);goto dispatch;
L_80076460:
 STEP(UINT32_C(0x80076460)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT64_C(0x80076464);goto dispatch;
L_80076464:
 STEP(UINT32_C(0x80076464)); /* 34421820 ori v0,v0,0x1820 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1820));target=UINT64_C(0x80076468);goto dispatch;
L_80076468:
 STEP(UINT32_C(0x80076468)); /* ac440000 sw a0,0x0(v0) */
 WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u,lo(m,4u));target=UINT64_C(0x8007646c);goto dispatch;
L_8007646c:
 STEP(UINT32_C(0x8007646c)); /* 0000000f sync 0 */
 ++m->sync_p; /* actual SYNC0 value barrier, no timer/cache fabrication */target=UINT64_C(0x80076470);goto dispatch;
L_80076470:
 STEP(UINT32_C(0x80076470)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT64_C(0x80076474);goto dispatch;
L_80076474:
 STEP(UINT32_C(0x80076474)); /* 24030583 addiu v1,zero,1411 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000583)));target=UINT64_C(0x80076478);goto dispatch;
L_80076478:
 STEP(UINT32_C(0x80076478)); /* 34421810 ori v0,v0,0x1810 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1810));target=UINT64_C(0x8007647c);goto dispatch;
L_8007647c:
 STEP(UINT32_C(0x8007647c)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076480));WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u,lo(m,3u));goto dispatch;
L_80076480:
 STEP(UINT32_C(0x80076480)); /* ac430000 sw v1,0x0(v0) */
 WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u,lo(m,3u));target=UINT64_C(0x80076484);goto dispatch;
#undef STEP
#undef READ
#undef WRITE
}

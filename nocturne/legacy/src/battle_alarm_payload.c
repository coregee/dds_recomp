#include "battle_alarm_payload.h"
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
uint32_t nocturneBattleAlarmPayloadResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t limit,NocturneWakeupStop *s)
{
 uint32_t target,address=0,ea=0,offset=0;uint64_t started,value;uint8_t bytes[8];
 if(!m||!ram||!ram->read||!ram->write||!s)return NOCTURNE_WAKEUP_INPUT_DOMAIN;
 memset(s,0,sizeof(*s));
 if(m->gpr[0][0]||m->gpr[0][1]||m->gpr[0][2]||m->gpr[0][3])return stop(m,s,NOCTURNE_WAKEUP_INPUT_DOMAIN,0,0,0);
 if(!limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);
 started=m->instructions;target=m->pc;
#define STEP(p) do{m->pc=(p);if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);++m->instructions;}while(0)
#define READ(a,n) do{address=(a);if((address&((n)-1u))||!ram->read(ram->owner,address,bytes,(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);value=unpack(bytes,(n));}while(0)
#define WRITE(a,n,v) do{address=(a);pack(bytes,(v),(n));if((address&((n)-1u))||!ram->write(ram->owner,address,bytes,(n)))return stop(m,s,NOCTURNE_WAKEUP_UNBACKED,address,(n),0);}while(0)
dispatch:
 m->pc=target;
 switch(target){
 case UINT32_C(0x80076000):goto L_80076000;
 case UINT32_C(0x80076004):goto L_80076004;
 case UINT32_C(0x80076008):goto L_80076008;
 case UINT32_C(0x8007600c):goto L_8007600c;
 case UINT32_C(0x80076010):goto L_80076010;
 case UINT32_C(0x80076014):goto L_80076014;
 case UINT32_C(0x80076018):goto L_80076018;
 case UINT32_C(0x8007601c):goto L_8007601c;
 case UINT32_C(0x80076020):goto L_80076020;
 case UINT32_C(0x80076024):goto L_80076024;
 case UINT32_C(0x80076028):goto L_80076028;
 case UINT32_C(0x8007602c):goto L_8007602c;
 case UINT32_C(0x80076030):goto L_80076030;
 case UINT32_C(0x80076034):goto L_80076034;
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
 case UINT32_C(0x800762a0):goto L_800762a0;
 case UINT32_C(0x800762a4):goto L_800762a4;
 case UINT32_C(0x800762a8):goto L_800762a8;
 case UINT32_C(0x800762ac):goto L_800762ac;
 case UINT32_C(0x800762b0):goto L_800762b0;
 case UINT32_C(0x800762b4):goto L_800762b4;
 case UINT32_C(0x800762b8):goto L_800762b8;
 case UINT32_C(0x800762bc):goto L_800762bc;
 case UINT32_C(0x800762c0):goto L_800762c0;
 case UINT32_C(0x800762c4):goto L_800762c4;
 case UINT32_C(0x800762c8):goto L_800762c8;
 case UINT32_C(0x800762cc):goto L_800762cc;
 case UINT32_C(0x800762d0):goto L_800762d0;
 case UINT32_C(0x800762d4):goto L_800762d4;
 case UINT32_C(0x800762d8):goto L_800762d8;
 case UINT32_C(0x800762dc):goto L_800762dc;
 case UINT32_C(0x800762e0):goto L_800762e0;
 case UINT32_C(0x800762e4):goto L_800762e4;
 case UINT32_C(0x800762e8):goto L_800762e8;
 case UINT32_C(0x800762ec):goto L_800762ec;
 case UINT32_C(0x800762f0):goto L_800762f0;
 case UINT32_C(0x800762f4):goto L_800762f4;
 case UINT32_C(0x800762f8):goto L_800762f8;
 case UINT32_C(0x800762fc):goto L_800762fc;
 case UINT32_C(0x80076300):goto L_80076300;
 case UINT32_C(0x80076304):goto L_80076304;
 case UINT32_C(0x80076308):goto L_80076308;
 case UINT32_C(0x8007630c):goto L_8007630c;
 case UINT32_C(0x80076310):goto L_80076310;
 case UINT32_C(0x80076314):goto L_80076314;
 case UINT32_C(0x80076318):goto L_80076318;
 case UINT32_C(0x8007631c):goto L_8007631c;
 case UINT32_C(0x80076320):goto L_80076320;
 case UINT32_C(0x80076324):goto L_80076324;
 case UINT32_C(0x80076328):goto L_80076328;
 case UINT32_C(0x8007632c):goto L_8007632c;
 case UINT32_C(0x80076330):goto L_80076330;
 case UINT32_C(0x80076334):goto L_80076334;
 case UINT32_C(0x80076338):goto L_80076338;
 case UINT32_C(0x8007633c):goto L_8007633c;
 case UINT32_C(0x80076340):goto L_80076340;
 case UINT32_C(0x80076344):goto L_80076344;
 case UINT32_C(0x80076348):goto L_80076348;
 case UINT32_C(0x8007634c):goto L_8007634c;
 case UINT32_C(0x80076350):goto L_80076350;
 case UINT32_C(0x80076354):goto L_80076354;
 case UINT32_C(0x80076358):goto L_80076358;
 case UINT32_C(0x8007635c):goto L_8007635c;
 case UINT32_C(0x80076360):goto L_80076360;
 case UINT32_C(0x80076364):goto L_80076364;
 case UINT32_C(0x80076368):goto L_80076368;
 case UINT32_C(0x8007636c):goto L_8007636c;
 case UINT32_C(0x80076370):goto L_80076370;
 case UINT32_C(0x80076374):goto L_80076374;
 case UINT32_C(0x80076378):goto L_80076378;
 case UINT32_C(0x8007637c):goto L_8007637c;
 case UINT32_C(0x80076380):goto L_80076380;
 case UINT32_C(0x80076384):goto L_80076384;
 case UINT32_C(0x80076388):goto L_80076388;
 case UINT32_C(0x8007638c):goto L_8007638c;
 case UINT32_C(0x80076390):goto L_80076390;
 case UINT32_C(0x80076394):goto L_80076394;
 case UINT32_C(0x80076398):goto L_80076398;
 case UINT32_C(0x8007639c):goto L_8007639c;
 case UINT32_C(0x800763a0):goto L_800763a0;
 case UINT32_C(0x800763a4):goto L_800763a4;
 case UINT32_C(0x800763a8):goto L_800763a8;
 case UINT32_C(0x800763ac):goto L_800763ac;
 case UINT32_C(0x800763b0):goto L_800763b0;
 case UINT32_C(0x800763b4):goto L_800763b4;
 case UINT32_C(0x800763b8):goto L_800763b8;
 case UINT32_C(0x800763bc):goto L_800763bc;
 case UINT32_C(0x800763c0):goto L_800763c0;
 case UINT32_C(0x800763c4):goto L_800763c4;
 case UINT32_C(0x800763c8):goto L_800763c8;
 case UINT32_C(0x800763cc):goto L_800763cc;
 case UINT32_C(0x800763d0):goto L_800763d0;
 case UINT32_C(0x800763d4):goto L_800763d4;
 case UINT32_C(0x800763d8):goto L_800763d8;
 case UINT32_C(0x800763dc):goto L_800763dc;
 case UINT32_C(0x800763e0):goto L_800763e0;
 case UINT32_C(0x800763e4):goto L_800763e4;
 case UINT32_C(0x800763e8):goto L_800763e8;
 case UINT32_C(0x800763ec):goto L_800763ec;
 case UINT32_C(0x800763f0):goto L_800763f0;
 case UINT32_C(0x800763f4):goto L_800763f4;
 case UINT32_C(0x800763f8):goto L_800763f8;
 case UINT32_C(0x800763fc):goto L_800763fc;
 case UINT32_C(0x80076400):goto L_80076400;
 case UINT32_C(0x80076404):goto L_80076404;
 case UINT32_C(0x80076408):goto L_80076408;
 case UINT32_C(0x8007640c):goto L_8007640c;
 case UINT32_C(0x80076410):goto L_80076410;
 case UINT32_C(0x80076414):goto L_80076414;
 case UINT32_C(0x80076418):goto L_80076418;
 case UINT32_C(0x8007641c):goto L_8007641c;
 case UINT32_C(0x80076420):goto L_80076420;
 case UINT32_C(0x80076424):goto L_80076424;
 case UINT32_C(0x80076428):goto L_80076428;
 case UINT32_C(0x8007642c):goto L_8007642c;
 case UINT32_C(0x80076430):goto L_80076430;
 case UINT32_C(0x80076434):goto L_80076434;
 case UINT32_C(0x80076438):goto L_80076438;
 case UINT32_C(0x8007643c):goto L_8007643c;
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
 case UINT32_C(0x80076488):goto L_80076488;
 case UINT32_C(0x8007648c):goto L_8007648c;
 case UINT32_C(0x80076490):goto L_80076490;
 case UINT32_C(0x80076494):goto L_80076494;
 case UINT32_C(0x80076498):goto L_80076498;
 case UINT32_C(0x8007649c):goto L_8007649c;
 case UINT32_C(0x800764a0):goto L_800764a0;
 case UINT32_C(0x800764a4):goto L_800764a4;
 case UINT32_C(0x800764a8):goto L_800764a8;
 case UINT32_C(0x800764ac):goto L_800764ac;
 case UINT32_C(0x800764b0):goto L_800764b0;
 case UINT32_C(0x800764b4):goto L_800764b4;
 case UINT32_C(0x800764b8):goto L_800764b8;
 case UINT32_C(0x800764bc):goto L_800764bc;
 case UINT32_C(0x800764c0):goto L_800764c0;
 case UINT32_C(0x800764c4):goto L_800764c4;
 case UINT32_C(0x800764c8):goto L_800764c8;
 case UINT32_C(0x800764cc):goto L_800764cc;
 case UINT32_C(0x800764d0):goto L_800764d0;
 case UINT32_C(0x800764d4):goto L_800764d4;
 case UINT32_C(0x800764d8):goto L_800764d8;
 case UINT32_C(0x800764dc):goto L_800764dc;
 case UINT32_C(0x800764e0):goto L_800764e0;
 case UINT32_C(0x800764e4):goto L_800764e4;
 case UINT32_C(0x800764e8):goto L_800764e8;
 case UINT32_C(0x800764ec):goto L_800764ec;
 case UINT32_C(0x800764f0):goto L_800764f0;
 case UINT32_C(0x800764f4):goto L_800764f4;
 case UINT32_C(0x800764f8):goto L_800764f8;
 case UINT32_C(0x800764fc):goto L_800764fc;
 case UINT32_C(0x80076500):goto L_80076500;
 case UINT32_C(0x80076504):goto L_80076504;
 case UINT32_C(0x80076508):goto L_80076508;
 case UINT32_C(0x8007650c):goto L_8007650c;
 case UINT32_C(0x80076510):goto L_80076510;
 case UINT32_C(0x80076514):goto L_80076514;
 case UINT32_C(0x80076518):goto L_80076518;
 case UINT32_C(0x8007651c):goto L_8007651c;
 case UINT32_C(0x80076520):goto L_80076520;
 case UINT32_C(0x80076524):goto L_80076524;
 case UINT32_C(0x80076528):goto L_80076528;
 case UINT32_C(0x8007652c):goto L_8007652c;
 case UINT32_C(0x80076530):goto L_80076530;
 case UINT32_C(0x80076534):goto L_80076534;
 case UINT32_C(0x80076538):goto L_80076538;
 case UINT32_C(0x8007653c):goto L_8007653c;
 case UINT32_C(0x80076540):goto L_80076540;
 case UINT32_C(0x80076544):goto L_80076544;
 case UINT32_C(0x80076548):goto L_80076548;
 case UINT32_C(0x8007654c):goto L_8007654c;
 case UINT32_C(0x80076550):goto L_80076550;
 case UINT32_C(0x80076554):goto L_80076554;
 case UINT32_C(0x80076558):goto L_80076558;
 case UINT32_C(0x8007655c):goto L_8007655c;
 case UINT32_C(0x80076560):goto L_80076560;
 case UINT32_C(0x80076564):goto L_80076564;
 case UINT32_C(0x80076568):goto L_80076568;
 case UINT32_C(0x8007656c):goto L_8007656c;
 case UINT32_C(0x80076570):goto L_80076570;
 case UINT32_C(0x80076574):goto L_80076574;
 case UINT32_C(0x80076578):goto L_80076578;
 case UINT32_C(0x8007657c):goto L_8007657c;
 case UINT32_C(0x80076580):goto L_80076580;
 case UINT32_C(0x80076584):goto L_80076584;
 case UINT32_C(0x80076588):goto L_80076588;
 case UINT32_C(0x8007658c):goto L_8007658c;
 case UINT32_C(0x80076590):goto L_80076590;
 case UINT32_C(0x80076594):goto L_80076594;
 case UINT32_C(0x80076598):goto L_80076598;
 case UINT32_C(0x8007659c):goto L_8007659c;
 case UINT32_C(0x800765a0):goto L_800765a0;
 case UINT32_C(0x800765a4):goto L_800765a4;
 case UINT32_C(0x800765a8):goto L_800765a8;
 case UINT32_C(0x800765ac):goto L_800765ac;
 case UINT32_C(0x800765b0):goto L_800765b0;
 case UINT32_C(0x800765b4):goto L_800765b4;
 case UINT32_C(0x800765b8):goto L_800765b8;
 case UINT32_C(0x800765bc):goto L_800765bc;
 case UINT32_C(0x800765c0):goto L_800765c0;
 case UINT32_C(0x800765c4):goto L_800765c4;
 case UINT32_C(0x800765c8):goto L_800765c8;
 case UINT32_C(0x800765cc):goto L_800765cc;
 case UINT32_C(0x800765d0):goto L_800765d0;
 case UINT32_C(0x800765d4):goto L_800765d4;
 case UINT32_C(0x800765d8):goto L_800765d8;
 case UINT32_C(0x800765dc):goto L_800765dc;
 case UINT32_C(0x800765e0):goto L_800765e0;
 case UINT32_C(0x800765e4):goto L_800765e4;
 case UINT32_C(0x800765e8):goto L_800765e8;
 case UINT32_C(0x800765ec):goto L_800765ec;
 case UINT32_C(0x800765f0):goto L_800765f0;
 case UINT32_C(0x800765f4):goto L_800765f4;
 case UINT32_C(0x800765f8):goto L_800765f8;
 case UINT32_C(0x800765fc):goto L_800765fc;
 case UINT32_C(0x80076600):goto L_80076600;
 case UINT32_C(0x80076604):goto L_80076604;
 case UINT32_C(0x80076608):goto L_80076608;
 case UINT32_C(0x8007660c):goto L_8007660c;
 case UINT32_C(0x80076610):goto L_80076610;
 case UINT32_C(0x80076614):goto L_80076614;
 case UINT32_C(0x80076618):goto L_80076618;
 case UINT32_C(0x8007661c):goto L_8007661c;
 case UINT32_C(0x80076620):goto L_80076620;
 case UINT32_C(0x80076624):goto L_80076624;
 case UINT32_C(0x80076628):goto L_80076628;
 case UINT32_C(0x8007662c):goto L_8007662c;
 case UINT32_C(0x80076630):goto L_80076630;
 case UINT32_C(0x80076634):goto L_80076634;
 case UINT32_C(0x80076638):goto L_80076638;
 case UINT32_C(0x8007663c):goto L_8007663c;
 case UINT32_C(0x80076640):goto L_80076640;
 case UINT32_C(0x80076644):goto L_80076644;
 case UINT32_C(0x80076648):goto L_80076648;
 case UINT32_C(0x8007664c):goto L_8007664c;
 case UINT32_C(0x80076650):goto L_80076650;
 case UINT32_C(0x80076654):goto L_80076654;
 case UINT32_C(0x80076658):goto L_80076658;
 case UINT32_C(0x8007665c):goto L_8007665c;
 case UINT32_C(0x80076660):goto L_80076660;
 case UINT32_C(0x80076664):goto L_80076664;
 case UINT32_C(0x80076680):goto L_80076680;
 case UINT32_C(0x80076684):goto L_80076684;
 case UINT32_C(0x80076688):goto L_80076688;
 case UINT32_C(0x8007668c):goto L_8007668c;
 case UINT32_C(0x80076690):goto L_80076690;
 case UINT32_C(0x80076694):goto L_80076694;
 case UINT32_C(0x80076698):goto L_80076698;
 case UINT32_C(0x8007669c):goto L_8007669c;
 case UINT32_C(0x800766a0):goto L_800766a0;
 case UINT32_C(0x800766a4):goto L_800766a4;
 case UINT32_C(0x800766a8):goto L_800766a8;
 case UINT32_C(0x800766ac):goto L_800766ac;
 case UINT32_C(0x800766b0):goto L_800766b0;
 case UINT32_C(0x800766b4):goto L_800766b4;
 case UINT32_C(0x800766b8):goto L_800766b8;
 case UINT32_C(0x800766c0):goto L_800766c0;
 case UINT32_C(0x800766c4):goto L_800766c4;
 case UINT32_C(0x800766c8):goto L_800766c8;
 case UINT32_C(0x800766cc):goto L_800766cc;
 case UINT32_C(0x800766d0):goto L_800766d0;
 case UINT32_C(0x800766d4):goto L_800766d4;
 case UINT32_C(0x800766d8):goto L_800766d8;
 case UINT32_C(0x800766dc):goto L_800766dc;
 case UINT32_C(0x800766e0):goto L_800766e0;
 case UINT32_C(0x800766e4):goto L_800766e4;
 case UINT32_C(0x00082000):goto L_00082000;
 case UINT32_C(0x00082004):goto L_00082004;
 case UINT32_C(0x00082008):goto L_00082008;
 case UINT32_C(0x0008200c):goto L_0008200c;
 case UINT32_C(0x00082010):goto L_00082010;
 default:return stop(m,s,NOCTURNE_NATIVE_TRANSFER,0,0,sx(target));}
L_80076000:
 STEP(UINT32_C(0x80076000)); /* 3c028007 lui v0,zero,0x8007 */
 set(m,2u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x80076004);goto dispatch;
L_80076004:
 STEP(UINT32_C(0x80076004)); /* 0000282d daddu a1,zero,zero */
 set(m,5u,lo(m,0u)+lo(m,0u));target=UINT32_C(0x80076008);goto dispatch;
L_80076008:
 STEP(UINT32_C(0x80076008)); /* 24436710 addiu v1,v0,26384 */
 set(m,3u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00006710)));target=UINT32_C(0x8007600c);goto dispatch;
L_8007600c:
 STEP(UINT32_C(0x8007600c)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x80076010);goto dispatch;
L_80076010:
 STEP(UINT32_C(0x80076010)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x80076014);goto dispatch;
L_80076014:
 STEP(UINT32_C(0x80076014)); /* 14820003 bne a0,v0,80076024 */
 {int taken=(lo(m,4u)!=lo(m,2u));STEP(UINT32_C(0x80076018));set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=taken?UINT32_C(0x80076024):UINT32_C(0x8007601c);goto dispatch;}
L_80076018:
 STEP(UINT32_C(0x80076018)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=UINT32_C(0x8007601c);goto dispatch;
L_8007601c:
 STEP(UINT32_C(0x8007601c)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076020));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),4u);set(m,2u,sx((uint32_t)value));goto dispatch;
L_80076020:
 STEP(UINT32_C(0x80076020)); /* 8c620004 lw v0,0x4(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000004),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x80076024);goto dispatch;
L_80076024:
 STEP(UINT32_C(0x80076024)); /* 2ca20006 sltiu v0,a1,6 */
 set(m,2u,(lo(m,5u)<UINT64_C(0x6)));target=UINT32_C(0x80076028);goto dispatch;
L_80076028:
 STEP(UINT32_C(0x80076028)); /* 1440fff9 bne v0,zero,80076010 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8007602c));set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=taken?UINT32_C(0x80076010):UINT32_C(0x80076030);goto dispatch;}
L_8007602c:
 STEP(UINT32_C(0x8007602c)); /* 24630008 addiu v1,v1,8 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000008)));target=UINT32_C(0x80076030);goto dispatch;
L_80076030:
 STEP(UINT32_C(0x80076030)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076034));set(m,2u,lo(m,0u)+lo(m,0u));goto dispatch;
L_80076034:
 STEP(UINT32_C(0x80076034)); /* 0000102d daddu v0,zero,zero */
 set(m,2u,lo(m,0u)+lo(m,0u));target=UINT32_C(0x80076038);goto dispatch;
L_80076038:
 STEP(UINT32_C(0x80076038)); /* 00a4202a slt a0,a1,a0 */
 set(m,4u,((int64_t)lo(m,5u)<(int64_t)lo(m,4u)));target=UINT32_C(0x8007603c);goto dispatch;
L_8007603c:
 STEP(UINT32_C(0x8007603c)); /* 10800003 beq a0,zero,8007604c */
 {int taken=(lo(m,4u)==lo(m,0u));STEP(UINT32_C(0x80076040));set(m,2u,sx(UINT32_C(0x00010000)));target=taken?UINT32_C(0x8007604c):UINT32_C(0x80076044);goto dispatch;}
L_80076040:
 STEP(UINT32_C(0x80076040)); /* 3c020001 lui v0,zero,0x1 */
 set(m,2u,sx(UINT32_C(0x00010000)));target=UINT32_C(0x80076044);goto dispatch;
L_80076044:
 STEP(UINT32_C(0x80076044)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076048));set(m,2u,(lo(m,5u)|lo(m,2u)));goto dispatch;
L_80076048:
 STEP(UINT32_C(0x80076048)); /* 00a21025 or v0,a1,v0 */
 set(m,2u,(lo(m,5u)|lo(m,2u)));target=UINT32_C(0x8007604c);goto dispatch;
L_8007604c:
 STEP(UINT32_C(0x8007604c)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076050));set(m,2u,lo(m,5u)+lo(m,0u));goto dispatch;
L_80076050:
 STEP(UINT32_C(0x80076050)); /* 00a0102d daddu v0,a1,zero */
 set(m,2u,lo(m,5u)+lo(m,0u));target=UINT32_C(0x80076054);goto dispatch;
L_80076058:
 STEP(UINT32_C(0x80076058)); /* 27bdff80 addiu sp,sp,-128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff80)));target=UINT32_C(0x8007605c);goto dispatch;
L_8007605c:
 STEP(UINT32_C(0x8007605c)); /* ffb30030 sd s3,0x30(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u,lo(m,19u));target=UINT32_C(0x80076060);goto dispatch;
L_80076060:
 STEP(UINT32_C(0x80076060)); /* 3c138007 lui s3,zero,0x8007 */
 set(m,19u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x80076064);goto dispatch;
L_80076064:
 STEP(UINT32_C(0x80076064)); /* ffb60060 sd s6,0x60(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u,lo(m,22u));target=UINT32_C(0x80076068);goto dispatch;
L_80076068:
 STEP(UINT32_C(0x80076068)); /* ffb50050 sd s5,0x50(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u,lo(m,21u));target=UINT32_C(0x8007606c);goto dispatch;
L_8007606c:
 STEP(UINT32_C(0x8007606c)); /* 0080b02d daddu s6,a0,zero */
 set(m,22u,lo(m,4u)+lo(m,0u));target=UINT32_C(0x80076070);goto dispatch;
L_80076070:
 STEP(UINT32_C(0x80076070)); /* ffb00000 sd s0,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,16u));target=UINT32_C(0x80076074);goto dispatch;
L_80076074:
 STEP(UINT32_C(0x80076074)); /* 00a0a82d daddu s5,a1,zero */
 set(m,21u,lo(m,5u)+lo(m,0u));target=UINT32_C(0x80076078);goto dispatch;
L_80076078:
 STEP(UINT32_C(0x80076078)); /* 8e626700 lw v0,0x6700(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x8007607c);goto dispatch;
L_8007607c:
 STEP(UINT32_C(0x8007607c)); /* 0000802d daddu s0,zero,zero */
 set(m,16u,lo(m,0u)+lo(m,0u));target=UINT32_C(0x80076080);goto dispatch;
L_80076080:
 STEP(UINT32_C(0x80076080)); /* ffbf0070 sd ra,0x70(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u,lo(m,31u));target=UINT32_C(0x80076084);goto dispatch;
L_80076084:
 STEP(UINT32_C(0x80076084)); /* ffb40040 sd s4,0x40(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u,lo(m,20u));target=UINT32_C(0x80076088);goto dispatch;
L_80076088:
 STEP(UINT32_C(0x80076088)); /* ffb20020 sd s2,0x20(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u,lo(m,18u));target=UINT32_C(0x8007608c);goto dispatch;
L_8007608c:
 STEP(UINT32_C(0x8007608c)); /* 18400028 blez v0,zero,80076130 */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x80076090));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u,lo(m,17u));target=taken?UINT32_C(0x80076130):UINT32_C(0x80076094);goto dispatch;}
L_80076090:
 STEP(UINT32_C(0x80076090)); /* ffb10010 sd s1,0x10(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u,lo(m,17u));target=UINT32_C(0x80076094);goto dispatch;
L_80076094:
 STEP(UINT32_C(0x80076094)); /* 3c148007 lui s4,zero,0x8007 */
 set(m,20u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x80076098);goto dispatch;
L_80076098:
 STEP(UINT32_C(0x80076098)); /* 24120014 addiu s2,zero,20 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x8007609c);goto dispatch;
L_8007609c:
 STEP(UINT32_C(0x8007609c)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x800760a0);goto dispatch;
L_800760a0:
 STEP(UINT32_C(0x800760a0)); /* 26916740 addiu s1,s4,26432 */
 set(m,17u,sx((uint32_t)lo(m,20u)+UINT32_C(0x00006740)));target=UINT32_C(0x800760a4);goto dispatch;
L_800760a4:
 STEP(UINT32_C(0x800760a4)); /* 02121018 mult_rd v0,s0,s2 */
 {int64_t product;if(lo(m,16u)!=sx((uint32_t)lo(m,16u))||lo(m,18u)!=sx((uint32_t)lo(m,18u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,16u)*(int64_t)(int32_t)lo(m,18u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=UINT32_C(0x800760a8);goto dispatch;
L_800760a8:
 STEP(UINT32_C(0x800760a8)); /* 02c0202d daddu a0,s6,zero */
 set(m,4u,lo(m,22u)+lo(m,0u));target=UINT32_C(0x800760ac);goto dispatch;
L_800760ac:
 STEP(UINT32_C(0x800760ac)); /* 00511021 addu v0,v0,s1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,17u)));target=UINT32_C(0x800760b0);goto dispatch;
L_800760b0:
 STEP(UINT32_C(0x800760b0)); /* 0c01d80e jal 80076038 */
 set(m,31u,UINT64_C(0x800760b8));STEP(UINT32_C(0x800760b4));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),2u);set(m,5u,value);target=UINT32_C(0x80076038);goto dispatch;
L_800760b4:
 STEP(UINT32_C(0x800760b4)); /* 94450000 lhu a1,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),2u);set(m,5u,value);target=UINT32_C(0x800760b8);goto dispatch;
L_800760b8:
 STEP(UINT32_C(0x800760b8)); /* 02a2102a slt v0,s5,v0 */
 set(m,2u,((int64_t)lo(m,21u)<(int64_t)lo(m,2u)));target=UINT32_C(0x800760bc);goto dispatch;
L_800760bc:
 STEP(UINT32_C(0x800760bc)); /* 10400018 beq v0,zero,80076120 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x800760c0));READ((uint32_t)lo(m,19u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=taken?UINT32_C(0x80076120):UINT32_C(0x800760c4);goto dispatch;}
L_800760c0:
 STEP(UINT32_C(0x800760c0)); /* 8e626700 lw v0,0x6700(s3) */
 READ((uint32_t)lo(m,19u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x800760c4);goto dispatch;
L_800760c4:
 STEP(UINT32_C(0x800760c4)); /* 2444ffff addiu a0,v0,-1 */
 set(m,4u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=UINT32_C(0x800760c8);goto dispatch;
L_800760c8:
 STEP(UINT32_C(0x800760c8)); /* 0090182a slt v1,a0,s0 */
 set(m,3u,((int64_t)lo(m,4u)<(int64_t)lo(m,16u)));target=UINT32_C(0x800760cc);goto dispatch;
L_800760cc:
 STEP(UINT32_C(0x800760cc)); /* 14600018 bne v1,zero,80076130 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x800760d0));{int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,18u)!=sx((uint32_t)lo(m,18u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,18u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=taken?UINT32_C(0x80076130):UINT32_C(0x800760d4);goto dispatch;}
L_800760d0:
 STEP(UINT32_C(0x800760d0)); /* 00921018 mult_rd v0,a0,s2 */
 {int64_t product;if(lo(m,4u)!=sx((uint32_t)lo(m,4u))||lo(m,18u)!=sx((uint32_t)lo(m,18u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,4u)*(int64_t)(int32_t)lo(m,18u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=UINT32_C(0x800760d4);goto dispatch;
L_800760d4:
 STEP(UINT32_C(0x800760d4)); /* 00511821 addu v1,v0,s1 */
 set(m,3u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,17u)));target=UINT32_C(0x800760d8);goto dispatch;
L_800760d8:
 STEP(UINT32_C(0x800760d8)); /* 68650007 ldl a1,0x7(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000007);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,5u,(lo(m,5u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT32_C(0x800760dc);goto dispatch;
L_800760dc:
 STEP(UINT32_C(0x800760dc)); /* 6c650000 ldr a1,0x0(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000000);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,5u,(lo(m,5u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT32_C(0x800760e0);goto dispatch;
L_800760e0:
 STEP(UINT32_C(0x800760e0)); /* 6866000f ldl a2,0xf(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x0000000f);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,6u,(lo(m,6u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT32_C(0x800760e4);goto dispatch;
L_800760e4:
 STEP(UINT32_C(0x800760e4)); /* 6c660008 ldr a2,0x8(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000008);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,6u,(lo(m,6u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT32_C(0x800760e8);goto dispatch;
L_800760e8:
 STEP(UINT32_C(0x800760e8)); /* 8c670010 lw a3,0x10(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000010),4u);set(m,7u,sx((uint32_t)value));target=UINT32_C(0x800760ec);goto dispatch;
L_800760ec:
 STEP(UINT32_C(0x800760ec)); /* b065001b sdl a1,0x1b(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x0000001b);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,5u)>>((7u-offset)*8u)));target=UINT32_C(0x800760f0);goto dispatch;
L_800760f0:
 STEP(UINT32_C(0x800760f0)); /* b4650014 sdr a1,0x14(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000014);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,5u)<<(offset*8u)));target=UINT32_C(0x800760f4);goto dispatch;
L_800760f4:
 STEP(UINT32_C(0x800760f4)); /* b0660023 sdl a2,0x23(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x00000023);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,6u)>>((7u-offset)*8u)));target=UINT32_C(0x800760f8);goto dispatch;
L_800760f8:
 STEP(UINT32_C(0x800760f8)); /* b466001c sdr a2,0x1c(v1) */
 ea=(uint32_t)lo(m,3u)+UINT32_C(0x0000001c);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,6u)<<(offset*8u)));target=UINT32_C(0x800760fc);goto dispatch;
L_800760fc:
 STEP(UINT32_C(0x800760fc)); /* ac670024 sw a3,0x24(v1) */
 WRITE((uint32_t)lo(m,3u)+UINT32_C(0x00000024),4u,lo(m,7u));target=UINT32_C(0x80076100);goto dispatch;
L_80076100:
 STEP(UINT32_C(0x80076100)); /* 2484ffff addiu a0,a0,-1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=UINT32_C(0x80076104);goto dispatch;
L_80076104:
 STEP(UINT32_C(0x80076104)); /* 2463ffec addiu v1,v1,-20 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0xffffffec)));target=UINT32_C(0x80076108);goto dispatch;
L_80076108:
 STEP(UINT32_C(0x80076108)); /* 0090102a slt v0,a0,s0 */
 set(m,2u,((int64_t)lo(m,4u)<(int64_t)lo(m,16u)));target=UINT32_C(0x8007610c);goto dispatch;
L_8007610c:
 STEP(UINT32_C(0x8007610c)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x80076110);goto dispatch;
L_80076110:
 STEP(UINT32_C(0x80076110)); /* 1040fff1 beq v0,zero,800760d8 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80076114));/* nop */target=taken?UINT32_C(0x800760d8):UINT32_C(0x80076118);goto dispatch;}
L_80076114:
 STEP(UINT32_C(0x80076114)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x80076118);goto dispatch;
L_80076118:
 STEP(UINT32_C(0x80076118)); /* 10000006 beq zero,zero,80076134 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8007611c));set(m,2u,lo(m,16u)+lo(m,0u));target=taken?UINT32_C(0x80076134):UINT32_C(0x80076120);goto dispatch;}
L_8007611c:
 STEP(UINT32_C(0x8007611c)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=UINT32_C(0x80076120);goto dispatch;
L_80076120:
 STEP(UINT32_C(0x80076120)); /* 26100001 addiu s0,s0,1 */
 set(m,16u,sx((uint32_t)lo(m,16u)+UINT32_C(0x00000001)));target=UINT32_C(0x80076124);goto dispatch;
L_80076124:
 STEP(UINT32_C(0x80076124)); /* 0202102a slt v0,s0,v0 */
 set(m,2u,((int64_t)lo(m,16u)<(int64_t)lo(m,2u)));target=UINT32_C(0x80076128);goto dispatch;
L_80076128:
 STEP(UINT32_C(0x80076128)); /* 1440ffdd bne v0,zero,800760a0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x8007612c));set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=taken?UINT32_C(0x800760a0):UINT32_C(0x80076130);goto dispatch;}
L_8007612c:
 STEP(UINT32_C(0x8007612c)); /* 24120014 addiu s2,zero,20 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x80076130);goto dispatch;
L_80076130:
 STEP(UINT32_C(0x80076130)); /* 0200102d daddu v0,s0,zero */
 set(m,2u,lo(m,16u)+lo(m,0u));target=UINT32_C(0x80076134);goto dispatch;
L_80076134:
 STEP(UINT32_C(0x80076134)); /* dfbf0070 ld ra,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u);set(m,31u,value);target=UINT32_C(0x80076138);goto dispatch;
L_80076138:
 STEP(UINT32_C(0x80076138)); /* dfb60060 ld s6,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u);set(m,22u,value);target=UINT32_C(0x8007613c);goto dispatch;
L_8007613c:
 STEP(UINT32_C(0x8007613c)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u);set(m,21u,value);target=UINT32_C(0x80076140);goto dispatch;
L_80076140:
 STEP(UINT32_C(0x80076140)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u);set(m,20u,value);target=UINT32_C(0x80076144);goto dispatch;
L_80076144:
 STEP(UINT32_C(0x80076144)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u);set(m,19u,value);target=UINT32_C(0x80076148);goto dispatch;
L_80076148:
 STEP(UINT32_C(0x80076148)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u);set(m,18u,value);target=UINT32_C(0x8007614c);goto dispatch;
L_8007614c:
 STEP(UINT32_C(0x8007614c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u);set(m,17u,value);target=UINT32_C(0x80076150);goto dispatch;
L_80076150:
 STEP(UINT32_C(0x80076150)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,16u,value);target=UINT32_C(0x80076154);goto dispatch;
L_80076154:
 STEP(UINT32_C(0x80076154)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076158));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));goto dispatch;
L_80076158:
 STEP(UINT32_C(0x80076158)); /* 27bd0080 addiu sp,sp,128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000080)));target=UINT32_C(0x8007615c);goto dispatch;
L_80076160:
 STEP(UINT32_C(0x80076160)); /* 27bdff70 addiu sp,sp,-144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff70)));target=UINT32_C(0x80076164);goto dispatch;
L_80076164:
 STEP(UINT32_C(0x80076164)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT32_C(0x80076168);goto dispatch;
L_80076168:
 STEP(UINT32_C(0x80076168)); /* ffb70070 sd s7,0x70(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u,lo(m,23u));target=UINT32_C(0x8007616c);goto dispatch;
L_8007616c:
 STEP(UINT32_C(0x8007616c)); /* 34421800 ori v0,v0,0x1800 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1800));target=UINT32_C(0x80076170);goto dispatch;
L_80076170:
 STEP(UINT32_C(0x80076170)); /* ffb60060 sd s6,0x60(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u,lo(m,22u));target=UINT32_C(0x80076174);goto dispatch;
L_80076174:
 STEP(UINT32_C(0x80076174)); /* 00c0b82d daddu s7,a2,zero */
 set(m,23u,lo(m,6u)+lo(m,0u));target=UINT32_C(0x80076178);goto dispatch;
L_80076178:
 STEP(UINT32_C(0x80076178)); /* ffb50050 sd s5,0x50(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u,lo(m,21u));target=UINT32_C(0x8007617c);goto dispatch;
L_8007617c:
 STEP(UINT32_C(0x8007617c)); /* 00a0b02d daddu s6,a1,zero */
 set(m,22u,lo(m,5u)+lo(m,0u));target=UINT32_C(0x80076180);goto dispatch;
L_80076180:
 STEP(UINT32_C(0x80076180)); /* ffb30030 sd s3,0x30(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u,lo(m,19u));target=UINT32_C(0x80076184);goto dispatch;
L_80076184:
 STEP(UINT32_C(0x80076184)); /* 3c158007 lui s5,zero,0x8007 */
 set(m,21u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x80076188);goto dispatch;
L_80076188:
 STEP(UINT32_C(0x80076188)); /* ffbf0080 sd ra,0x80(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),8u,lo(m,31u));target=UINT32_C(0x8007618c);goto dispatch;
L_8007618c:
 STEP(UINT32_C(0x8007618c)); /* 3093ffff andi s3,a0,0xffff */
 set(m,19u,lo(m,4u) & UINT64_C(0xffff));target=UINT32_C(0x80076190);goto dispatch;
L_80076190:
 STEP(UINT32_C(0x80076190)); /* ffb20020 sd s2,0x20(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u,lo(m,18u));target=UINT32_C(0x80076194);goto dispatch;
L_80076194:
 STEP(UINT32_C(0x80076194)); /* ffb10010 sd s1,0x10(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u,lo(m,17u));target=UINT32_C(0x80076198);goto dispatch;
L_80076198:
 STEP(UINT32_C(0x80076198)); /* ffb00000 sd s0,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,16u));target=UINT32_C(0x8007619c);goto dispatch;
L_8007619c:
 STEP(UINT32_C(0x8007619c)); /* ffb40040 sd s4,0x40(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u,lo(m,20u));target=UINT32_C(0x800761a0);goto dispatch;
L_800761a0:
 STEP(UINT32_C(0x800761a0)); /* 8ea36700 lw v1,0x6700(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00006700),4u);set(m,3u,sx((uint32_t)value));target=UINT32_C(0x800761a4);goto dispatch;
L_800761a4:
 STEP(UINT32_C(0x800761a4)); /* 8c540000 lw s4,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u);set(m,20u,sx((uint32_t)value));target=UINT32_C(0x800761a8);goto dispatch;
L_800761a8:
 STEP(UINT32_C(0x800761a8)); /* 28630040 slti v1,v1,64 */
 set(m,3u,((int64_t)lo(m,3u)<INT64_C(64)));target=UINT32_C(0x800761ac);goto dispatch;
L_800761ac:
 STEP(UINT32_C(0x800761ac)); /* 14600008 bne v1,zero,800761d0 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x800761b0));set(m,19u,sx((uint32_t)lo(m,19u)+(uint32_t)lo(m,20u)));target=taken?UINT32_C(0x800761d0):UINT32_C(0x800761b4);goto dispatch;}
L_800761b0:
 STEP(UINT32_C(0x800761b0)); /* 02749821 addu s3,s3,s4 */
 set(m,19u,sx((uint32_t)lo(m,19u)+(uint32_t)lo(m,20u)));target=UINT32_C(0x800761b4);goto dispatch;
L_800761b4:
 STEP(UINT32_C(0x800761b4)); /* 1000002e beq zero,zero,80076270 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800761b8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=taken?UINT32_C(0x80076270):UINT32_C(0x800761bc);goto dispatch;}
L_800761b8:
 STEP(UINT32_C(0x800761b8)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=UINT32_C(0x800761bc);goto dispatch;
L_800761bc:
 STEP(UINT32_C(0x800761bc)); /* 0060902d daddu s2,v1,zero */
 set(m,18u,lo(m,3u)+lo(m,0u));target=UINT32_C(0x800761c0);goto dispatch;
L_800761c0:
 STEP(UINT32_C(0x800761c0)); /* 00621014 dsllv v0,v0,v1 */
 set(m,2u,lo(m,2u)<<(lo(m,3u)&63u));target=UINT32_C(0x800761c4);goto dispatch;
L_800761c4:
 STEP(UINT32_C(0x800761c4)); /* 00821025 or v0,a0,v0 */
 set(m,2u,(lo(m,4u)|lo(m,2u)));target=UINT32_C(0x800761c8);goto dispatch;
L_800761c8:
 STEP(UINT32_C(0x800761c8)); /* 1000000d beq zero,zero,80076200 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800761cc));WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00006708),8u,lo(m,2u));target=taken?UINT32_C(0x80076200):UINT32_C(0x800761d0);goto dispatch;}
L_800761cc:
 STEP(UINT32_C(0x800761cc)); /* fca26708 sd v0,0x6708(a1) */
 WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00006708),8u,lo(m,2u));target=UINT32_C(0x800761d0);goto dispatch;
L_800761d0:
 STEP(UINT32_C(0x800761d0)); /* 3c058007 lui a1,zero,0x8007 */
 set(m,5u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800761d4);goto dispatch;
L_800761d4:
 STEP(UINT32_C(0x800761d4)); /* 0000182d daddu v1,zero,zero */
 set(m,3u,lo(m,0u)+lo(m,0u));target=UINT32_C(0x800761d8);goto dispatch;
L_800761d8:
 STEP(UINT32_C(0x800761d8)); /* dca46708 ld a0,0x6708(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00006708),8u);set(m,4u,value);target=UINT32_C(0x800761dc);goto dispatch;
L_800761dc:
 STEP(UINT32_C(0x800761dc)); /* 00641016 dsrlv v0,a0,v1 */
 set(m,2u,lo(m,4u)>>(lo(m,3u)&63u));target=UINT32_C(0x800761e0);goto dispatch;
L_800761e0:
 STEP(UINT32_C(0x800761e0)); /* 30420001 andi v0,v0,0x1 */
 set(m,2u,lo(m,2u) & UINT64_C(0x1));target=UINT32_C(0x800761e4);goto dispatch;
L_800761e4:
 STEP(UINT32_C(0x800761e4)); /* 1040fff5 beq v0,zero,800761bc */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x800761e8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=taken?UINT32_C(0x800761bc):UINT32_C(0x800761ec);goto dispatch;}
L_800761e8:
 STEP(UINT32_C(0x800761e8)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=UINT32_C(0x800761ec);goto dispatch;
L_800761ec:
 STEP(UINT32_C(0x800761ec)); /* 24630001 addiu v1,v1,1 */
 set(m,3u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000001)));target=UINT32_C(0x800761f0);goto dispatch;
L_800761f0:
 STEP(UINT32_C(0x800761f0)); /* 28620040 slti v0,v1,64 */
 set(m,2u,((int64_t)lo(m,3u)<INT64_C(64)));target=UINT32_C(0x800761f4);goto dispatch;
L_800761f4:
 STEP(UINT32_C(0x800761f4)); /* 1440fffa bne v0,zero,800761e0 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x800761f8));set(m,2u,lo(m,4u)>>(lo(m,3u)&63u));target=taken?UINT32_C(0x800761e0):UINT32_C(0x800761fc);goto dispatch;}
L_800761f8:
 STEP(UINT32_C(0x800761f8)); /* 00641016 dsrlv v0,a0,v1 */
 set(m,2u,lo(m,4u)>>(lo(m,3u)&63u));target=UINT32_C(0x800761fc);goto dispatch;
L_800761fc:
 STEP(UINT32_C(0x800761fc)); /* 2412ffff addiu s2,zero,-1 */
 set(m,18u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=UINT32_C(0x80076200);goto dispatch;
L_80076200:
 STEP(UINT32_C(0x80076200)); /* 0640001b bltz s2,80076270 */
 {int taken=((int64_t)lo(m,18u)<0);STEP(UINT32_C(0x80076204));set(m,2u,lo(m,18u)+lo(m,0u));target=taken?UINT32_C(0x80076270):UINT32_C(0x80076208);goto dispatch;}
L_80076204:
 STEP(UINT32_C(0x80076204)); /* 0240102d daddu v0,s2,zero */
 set(m,2u,lo(m,18u)+lo(m,0u));target=UINT32_C(0x80076208);goto dispatch;
L_80076208:
 STEP(UINT32_C(0x80076208)); /* 0380882d daddu s1,gp,zero */
 set(m,17u,lo(m,28u)+lo(m,0u));target=UINT32_C(0x8007620c);goto dispatch;
L_8007620c:
 STEP(UINT32_C(0x8007620c)); /* 0260282d daddu a1,s3,zero */
 set(m,5u,lo(m,19u)+lo(m,0u));target=UINT32_C(0x80076210);goto dispatch;
L_80076210:
 STEP(UINT32_C(0x80076210)); /* 0c01d816 jal 80076058 */
 set(m,31u,UINT64_C(0x80076218));STEP(UINT32_C(0x80076214));set(m,4u,lo(m,20u)+lo(m,0u));target=UINT32_C(0x80076058);goto dispatch;
L_80076214:
 STEP(UINT32_C(0x80076214)); /* 0280202d daddu a0,s4,zero */
 set(m,4u,lo(m,20u)+lo(m,0u));target=UINT32_C(0x80076218);goto dispatch;
L_80076218:
 STEP(UINT32_C(0x80076218)); /* 24040014 addiu a0,zero,20 */
 set(m,4u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x8007621c);goto dispatch;
L_8007621c:
 STEP(UINT32_C(0x8007621c)); /* 3c088007 lui t0,zero,0x8007 */
 set(m,8u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x80076220);goto dispatch;
L_80076220:
 STEP(UINT32_C(0x80076220)); /* 00441018 mult_rd v0,v0,a0 */
 {int64_t product;if(lo(m,2u)!=sx((uint32_t)lo(m,2u))||lo(m,4u)!=sx((uint32_t)lo(m,4u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,2u)*(int64_t)(int32_t)lo(m,4u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=UINT32_C(0x80076224);goto dispatch;
L_80076224:
 STEP(UINT32_C(0x80076224)); /* 25036740 addiu v1,t0,26432 */
 set(m,3u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00006740)));target=UINT32_C(0x80076228);goto dispatch;
L_80076228:
 STEP(UINT32_C(0x80076228)); /* 8ea56700 lw a1,0x6700(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00006700),4u);set(m,5u,sx((uint32_t)value));target=UINT32_C(0x8007622c);goto dispatch;
L_8007622c:
 STEP(UINT32_C(0x8007622c)); /* 24700004 addiu s0,v1,4 */
 set(m,16u,sx((uint32_t)lo(m,3u)+UINT32_C(0x00000004)));target=UINT32_C(0x80076230);goto dispatch;
L_80076230:
 STEP(UINT32_C(0x80076230)); /* 24a50001 addiu a1,a1,1 */
 set(m,5u,sx((uint32_t)lo(m,5u)+UINT32_C(0x00000001)));target=UINT32_C(0x80076234);goto dispatch;
L_80076234:
 STEP(UINT32_C(0x80076234)); /* 00432021 addu a0,v0,v1 */
 set(m,4u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,3u)));target=UINT32_C(0x80076238);goto dispatch;
L_80076238:
 STEP(UINT32_C(0x80076238)); /* 00623821 addu a3,v1,v0 */
 set(m,7u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,2u)));target=UINT32_C(0x8007623c);goto dispatch;
L_8007623c:
 STEP(UINT32_C(0x8007623c)); /* 00508021 addu s0,v0,s0 */
 set(m,16u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,16u)));target=UINT32_C(0x80076240);goto dispatch;
L_80076240:
 STEP(UINT32_C(0x80076240)); /* a4940002 sh s4,0x2(a0) */
 WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000002),2u,lo(m,20u));target=UINT32_C(0x80076244);goto dispatch;
L_80076244:
 STEP(UINT32_C(0x80076244)); /* a4930000 sh s3,0x0(a0) */
 WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000000),2u,lo(m,19u));target=UINT32_C(0x80076248);goto dispatch;
L_80076248:
 STEP(UINT32_C(0x80076248)); /* 00e0302d daddu a2,a3,zero */
 set(m,6u,lo(m,7u)+lo(m,0u));target=UINT32_C(0x8007624c);goto dispatch;
L_8007624c:
 STEP(UINT32_C(0x8007624c)); /* ae120000 sw s2,0x0(s0) */
 WRITE((uint32_t)lo(m,16u)+UINT32_C(0x00000000),4u,lo(m,18u));target=UINT32_C(0x80076250);goto dispatch;
L_80076250:
 STEP(UINT32_C(0x80076250)); /* 00c0182d daddu v1,a2,zero */
 set(m,3u,lo(m,6u)+lo(m,0u));target=UINT32_C(0x80076254);goto dispatch;
L_80076254:
 STEP(UINT32_C(0x80076254)); /* acf10010 sw s1,0x10(a3) */
 WRITE((uint32_t)lo(m,7u)+UINT32_C(0x00000010),4u,lo(m,17u));target=UINT32_C(0x80076258);goto dispatch;
L_80076258:
 STEP(UINT32_C(0x80076258)); /* 95046740 lhu a0,0x6740(t0) */
 READ((uint32_t)lo(m,8u)+UINT32_C(0x00006740),2u);set(m,4u,value);target=UINT32_C(0x8007625c);goto dispatch;
L_8007625c:
 STEP(UINT32_C(0x8007625c)); /* acd60008 sw s6,0x8(a2) */
 WRITE((uint32_t)lo(m,6u)+UINT32_C(0x00000008),4u,lo(m,22u));target=UINT32_C(0x80076260);goto dispatch;
L_80076260:
 STEP(UINT32_C(0x80076260)); /* ac77000c sw s7,0xc(v1) */
 WRITE((uint32_t)lo(m,3u)+UINT32_C(0x0000000c),4u,lo(m,23u));target=UINT32_C(0x80076264);goto dispatch;
L_80076264:
 STEP(UINT32_C(0x80076264)); /* 0c01d918 jal 80076460 */
 set(m,31u,UINT64_C(0x8007626c));STEP(UINT32_C(0x80076268));WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00006700),4u,lo(m,5u));target=UINT32_C(0x80076460);goto dispatch;
L_80076268:
 STEP(UINT32_C(0x80076268)); /* aea56700 sw a1,0x6700(s5) */
 WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00006700),4u,lo(m,5u));target=UINT32_C(0x8007626c);goto dispatch;
L_8007626c:
 STEP(UINT32_C(0x8007626c)); /* 8e020000 lw v0,0x0(s0) */
 READ((uint32_t)lo(m,16u)+UINT32_C(0x00000000),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x80076270);goto dispatch;
L_80076270:
 STEP(UINT32_C(0x80076270)); /* dfbf0080 ld ra,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),8u);set(m,31u,value);target=UINT32_C(0x80076274);goto dispatch;
L_80076274:
 STEP(UINT32_C(0x80076274)); /* dfb70070 ld s7,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u);set(m,23u,value);target=UINT32_C(0x80076278);goto dispatch;
L_80076278:
 STEP(UINT32_C(0x80076278)); /* dfb60060 ld s6,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u);set(m,22u,value);target=UINT32_C(0x8007627c);goto dispatch;
L_8007627c:
 STEP(UINT32_C(0x8007627c)); /* dfb50050 ld s5,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u);set(m,21u,value);target=UINT32_C(0x80076280);goto dispatch;
L_80076280:
 STEP(UINT32_C(0x80076280)); /* dfb40040 ld s4,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u);set(m,20u,value);target=UINT32_C(0x80076284);goto dispatch;
L_80076284:
 STEP(UINT32_C(0x80076284)); /* dfb30030 ld s3,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u);set(m,19u,value);target=UINT32_C(0x80076288);goto dispatch;
L_80076288:
 STEP(UINT32_C(0x80076288)); /* dfb20020 ld s2,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u);set(m,18u,value);target=UINT32_C(0x8007628c);goto dispatch;
L_8007628c:
 STEP(UINT32_C(0x8007628c)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u);set(m,17u,value);target=UINT32_C(0x80076290);goto dispatch;
L_80076290:
 STEP(UINT32_C(0x80076290)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,16u,value);target=UINT32_C(0x80076294);goto dispatch;
L_80076294:
 STEP(UINT32_C(0x80076294)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076298));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));goto dispatch;
L_80076298:
 STEP(UINT32_C(0x80076298)); /* 27bd0090 addiu sp,sp,144 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000090)));target=UINT32_C(0x8007629c);goto dispatch;
L_800762a0:
 STEP(UINT32_C(0x800762a0)); /* 27bdffd0 addiu sp,sp,-48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffffd0)));target=UINT32_C(0x800762a4);goto dispatch;
L_800762a4:
 STEP(UINT32_C(0x800762a4)); /* 3c0c8007 lui t4,zero,0x8007 */
 set(m,12u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800762a8);goto dispatch;
L_800762a8:
 STEP(UINT32_C(0x800762a8)); /* ffb10010 sd s1,0x10(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u,lo(m,17u));target=UINT32_C(0x800762ac);goto dispatch;
L_800762ac:
 STEP(UINT32_C(0x800762ac)); /* 0080682d daddu t5,a0,zero */
 set(m,13u,lo(m,4u)+lo(m,0u));target=UINT32_C(0x800762b0);goto dispatch;
L_800762b0:
 STEP(UINT32_C(0x800762b0)); /* 8d826700 lw v0,0x6700(t4) */
 READ((uint32_t)lo(m,12u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x800762b4);goto dispatch;
L_800762b4:
 STEP(UINT32_C(0x800762b4)); /* 0180882d daddu s1,t4,zero */
 set(m,17u,lo(m,12u)+lo(m,0u));target=UINT32_C(0x800762b8);goto dispatch;
L_800762b8:
 STEP(UINT32_C(0x800762b8)); /* ffbf0020 sd ra,0x20(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u,lo(m,31u));target=UINT32_C(0x800762bc);goto dispatch;
L_800762bc:
 STEP(UINT32_C(0x800762bc)); /* 2406ffff addiu a2,zero,-1 */
 set(m,6u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=UINT32_C(0x800762c0);goto dispatch;
L_800762c0:
 STEP(UINT32_C(0x800762c0)); /* 18400058 blez v0,zero,80076424 */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x800762c4));WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,16u));target=taken?UINT32_C(0x80076424):UINT32_C(0x800762c8);goto dispatch;}
L_800762c4:
 STEP(UINT32_C(0x800762c4)); /* ffb00000 sd s0,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,16u));target=UINT32_C(0x800762c8);goto dispatch;
L_800762c8:
 STEP(UINT32_C(0x800762c8)); /* 18400056 blez v0,zero,80076424 */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x800762cc));set(m,8u,lo(m,0u)+lo(m,0u));target=taken?UINT32_C(0x80076424):UINT32_C(0x800762d0);goto dispatch;}
L_800762cc:
 STEP(UINT32_C(0x800762cc)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=UINT32_C(0x800762d0);goto dispatch;
L_800762d0:
 STEP(UINT32_C(0x800762d0)); /* 3c0b8007 lui t3,zero,0x8007 */
 set(m,11u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800762d4);goto dispatch;
L_800762d4:
 STEP(UINT32_C(0x800762d4)); /* 24030014 addiu v1,zero,20 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x800762d8);goto dispatch;
L_800762d8:
 STEP(UINT32_C(0x800762d8)); /* 25656740 addiu a1,t3,26432 */
 set(m,5u,sx((uint32_t)lo(m,11u)+UINT32_C(0x00006740)));target=UINT32_C(0x800762dc);goto dispatch;
L_800762dc:
 STEP(UINT32_C(0x800762dc)); /* 01032018 mult_rd a0,t0,v1 */
 {int64_t product;if(lo(m,8u)!=sx((uint32_t)lo(m,8u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,8u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=UINT32_C(0x800762e0);goto dispatch;
L_800762e0:
 STEP(UINT32_C(0x800762e0)); /* 00a41021 addu v0,a1,a0 */
 set(m,2u,sx((uint32_t)lo(m,5u)+(uint32_t)lo(m,4u)));target=UINT32_C(0x800762e4);goto dispatch;
L_800762e4:
 STEP(UINT32_C(0x800762e4)); /* 8c430004 lw v1,0x4(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000004),4u);set(m,3u,sx((uint32_t)value));target=UINT32_C(0x800762e8);goto dispatch;
L_800762e8:
 STEP(UINT32_C(0x800762e8)); /* 15a3004a bne t5,v1,80076414 */
 {int taken=(lo(m,13u)!=lo(m,3u));STEP(UINT32_C(0x800762ec));READ((uint32_t)lo(m,12u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=taken?UINT32_C(0x80076414):UINT32_C(0x800762f0);goto dispatch;}
L_800762ec:
 STEP(UINT32_C(0x800762ec)); /* 8d826700 lw v0,0x6700(t4) */
 READ((uint32_t)lo(m,12u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x800762f0);goto dispatch;
L_800762f0:
 STEP(UINT32_C(0x800762f0)); /* 3c03b000 lui v1,zero,0xb000 */
 set(m,3u,sx(UINT32_C(0xb0000000)));target=UINT32_C(0x800762f4);goto dispatch;
L_800762f4:
 STEP(UINT32_C(0x800762f4)); /* 00852021 addu a0,a0,a1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,5u)));target=UINT32_C(0x800762f8);goto dispatch;
L_800762f8:
 STEP(UINT32_C(0x800762f8)); /* 34631820 ori v1,v1,0x1820 */
 set(m,3u,lo(m,3u) | UINT64_C(0x1820));target=UINT32_C(0x800762fc);goto dispatch;
L_800762fc:
 STEP(UINT32_C(0x800762fc)); /* 94850000 lhu a1,0x0(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000000),2u);set(m,5u,value);target=UINT32_C(0x80076300);goto dispatch;
L_80076300:
 STEP(UINT32_C(0x80076300)); /* 8c620000 lw v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x80076304);goto dispatch;
L_80076304:
 STEP(UINT32_C(0x80076304)); /* 14a20008 bne a1,v0,80076328 */
 {int taken=(lo(m,5u)!=lo(m,2u));STEP(UINT32_C(0x80076308));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=taken?UINT32_C(0x80076328):UINT32_C(0x8007630c);goto dispatch;}
L_80076308:
 STEP(UINT32_C(0x80076308)); /* 24030014 addiu v1,zero,20 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x8007630c);goto dispatch;
L_8007630c:
 STEP(UINT32_C(0x8007630c)); /* 3c021000 lui v0,zero,0x1000 */
 set(m,2u,sx(UINT32_C(0x10000000)));target=UINT32_C(0x80076310);goto dispatch;
L_80076310:
 STEP(UINT32_C(0x80076310)); /* 3442f000 ori v0,v0,0xf000 */
 set(m,2u,lo(m,2u) | UINT64_C(0xf000));target=UINT32_C(0x80076314);goto dispatch;
L_80076314:
 STEP(UINT32_C(0x80076314)); /* 8c430000 lw v1,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u);set(m,3u,sx((uint32_t)value));target=UINT32_C(0x80076318);goto dispatch;
L_80076318:
 STEP(UINT32_C(0x80076318)); /* 30631000 andi v1,v1,0x1000 */
 set(m,3u,lo(m,3u) & UINT64_C(0x1000));target=UINT32_C(0x8007631c);goto dispatch;
L_8007631c:
 STEP(UINT32_C(0x8007631c)); /* 14600043 bne v1,zero,8007642c */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x80076320));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=taken?UINT32_C(0x8007642c):UINT32_C(0x80076324);goto dispatch;}
L_80076320:
 STEP(UINT32_C(0x80076320)); /* 2402ffff addiu v0,zero,-1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffff)));target=UINT32_C(0x80076324);goto dispatch;
L_80076324:
 STEP(UINT32_C(0x80076324)); /* 24030014 addiu v1,zero,20 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x80076328);goto dispatch;
L_80076328:
 STEP(UINT32_C(0x80076328)); /* 8d896700 lw t1,0x6700(t4) */
 READ((uint32_t)lo(m,12u)+UINT32_C(0x00006700),4u);set(m,9u,sx((uint32_t)value));target=UINT32_C(0x8007632c);goto dispatch;
L_8007632c:
 STEP(UINT32_C(0x8007632c)); /* 01031818 mult_rd v1,t0,v1 */
 {int64_t product;if(lo(m,8u)!=sx((uint32_t)lo(m,8u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,8u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=UINT32_C(0x80076330);goto dispatch;
L_80076330:
 STEP(UINT32_C(0x80076330)); /* 25646740 addiu a0,t3,26432 */
 set(m,4u,sx((uint32_t)lo(m,11u)+UINT32_C(0x00006740)));target=UINT32_C(0x80076334);goto dispatch;
L_80076334:
 STEP(UINT32_C(0x80076334)); /* 2522ffff addiu v0,t1,-1 */
 set(m,2u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffffff)));target=UINT32_C(0x80076338);goto dispatch;
L_80076338:
 STEP(UINT32_C(0x80076338)); /* 0100382d daddu a3,t0,zero */
 set(m,7u,lo(m,8u)+lo(m,0u));target=UINT32_C(0x8007633c);goto dispatch;
L_8007633c:
 STEP(UINT32_C(0x8007633c)); /* 0102102a slt v0,t0,v0 */
 set(m,2u,((int64_t)lo(m,8u)<(int64_t)lo(m,2u)));target=UINT32_C(0x80076340);goto dispatch;
L_80076340:
 STEP(UINT32_C(0x80076340)); /* 00641821 addu v1,v1,a0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=UINT32_C(0x80076344);goto dispatch;
L_80076344:
 STEP(UINT32_C(0x80076344)); /* 10400019 beq v0,zero,800763ac */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x80076348));READ((uint32_t)lo(m,3u)+UINT32_C(0x00000002),2u);set(m,16u,value);target=taken?UINT32_C(0x800763ac):UINT32_C(0x8007634c);goto dispatch;}
L_80076348:
 STEP(UINT32_C(0x80076348)); /* 94700002 lhu s0,0x2(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000002),2u);set(m,16u,value);target=UINT32_C(0x8007634c);goto dispatch;
L_8007634c:
 STEP(UINT32_C(0x8007634c)); /* 3c0a8007 lui t2,zero,0x8007 */
 set(m,10u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x80076350);goto dispatch;
L_80076350:
 STEP(UINT32_C(0x80076350)); /* 24e30001 addiu v1,a3,1 */
 set(m,3u,sx((uint32_t)lo(m,7u)+UINT32_C(0x00000001)));target=UINT32_C(0x80076354);goto dispatch;
L_80076354:
 STEP(UINT32_C(0x80076354)); /* 24050014 addiu a1,zero,20 */
 set(m,5u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x80076358);goto dispatch;
L_80076358:
 STEP(UINT32_C(0x80076358)); /* 00651018 mult_rd v0,v1,a1 */
 {int64_t product;if(lo(m,3u)!=sx((uint32_t)lo(m,3u))||lo(m,5u)!=sx((uint32_t)lo(m,5u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,3u)*(int64_t)(int32_t)lo(m,5u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,2u,m->lo);}target=UINT32_C(0x8007635c);goto dispatch;
L_8007635c:
 STEP(UINT32_C(0x8007635c)); /* 00e52018 mult_rd a0,a3,a1 */
 {int64_t product;if(lo(m,7u)!=sx((uint32_t)lo(m,7u))||lo(m,5u)!=sx((uint32_t)lo(m,5u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,7u)*(int64_t)(int32_t)lo(m,5u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,4u,m->lo);}target=UINT32_C(0x80076360);goto dispatch;
L_80076360:
 STEP(UINT32_C(0x80076360)); /* 25666740 addiu a2,t3,26432 */
 set(m,6u,sx((uint32_t)lo(m,11u)+UINT32_C(0x00006740)));target=UINT32_C(0x80076364);goto dispatch;
L_80076364:
 STEP(UINT32_C(0x80076364)); /* 0060382d daddu a3,v1,zero */
 set(m,7u,lo(m,3u)+lo(m,0u));target=UINT32_C(0x80076368);goto dispatch;
L_80076368:
 STEP(UINT32_C(0x80076368)); /* 00462821 addu a1,v0,a2 */
 set(m,5u,sx((uint32_t)lo(m,2u)+(uint32_t)lo(m,6u)));target=UINT32_C(0x8007636c);goto dispatch;
L_8007636c:
 STEP(UINT32_C(0x8007636c)); /* 00862021 addu a0,a0,a2 */
 set(m,4u,sx((uint32_t)lo(m,4u)+(uint32_t)lo(m,6u)));target=UINT32_C(0x80076370);goto dispatch;
L_80076370:
 STEP(UINT32_C(0x80076370)); /* 2522ffff addiu v0,t1,-1 */
 set(m,2u,sx((uint32_t)lo(m,9u)+UINT32_C(0xffffffff)));target=UINT32_C(0x80076374);goto dispatch;
L_80076374:
 STEP(UINT32_C(0x80076374)); /* 68a30007 ldl v1,0x7(a1) */
 ea=(uint32_t)lo(m,5u)+UINT32_C(0x00000007);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,3u,(lo(m,3u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT32_C(0x80076378);goto dispatch;
L_80076378:
 STEP(UINT32_C(0x80076378)); /* 6ca30000 ldr v1,0x0(a1) */
 ea=(uint32_t)lo(m,5u)+UINT32_C(0x00000000);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,3u,(lo(m,3u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT32_C(0x8007637c);goto dispatch;
L_8007637c:
 STEP(UINT32_C(0x8007637c)); /* 68a6000f ldl a2,0xf(a1) */
 ea=(uint32_t)lo(m,5u)+UINT32_C(0x0000000f);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,6u,(lo(m,6u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT32_C(0x80076380);goto dispatch;
L_80076380:
 STEP(UINT32_C(0x80076380)); /* 6ca60008 ldr a2,0x8(a1) */
 ea=(uint32_t)lo(m,5u)+UINT32_C(0x00000008);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,6u,(lo(m,6u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT32_C(0x80076384);goto dispatch;
L_80076384:
 STEP(UINT32_C(0x80076384)); /* 8cae0010 lw t6,0x10(a1) */
 READ((uint32_t)lo(m,5u)+UINT32_C(0x00000010),4u);set(m,14u,sx((uint32_t)value));target=UINT32_C(0x80076388);goto dispatch;
L_80076388:
 STEP(UINT32_C(0x80076388)); /* b0830007 sdl v1,0x7(a0) */
 ea=(uint32_t)lo(m,4u)+UINT32_C(0x00000007);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,3u)>>((7u-offset)*8u)));target=UINT32_C(0x8007638c);goto dispatch;
L_8007638c:
 STEP(UINT32_C(0x8007638c)); /* b4830000 sdr v1,0x0(a0) */
 ea=(uint32_t)lo(m,4u)+UINT32_C(0x00000000);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,3u)<<(offset*8u)));target=UINT32_C(0x80076390);goto dispatch;
L_80076390:
 STEP(UINT32_C(0x80076390)); /* b086000f sdl a2,0xf(a0) */
 ea=(uint32_t)lo(m,4u)+UINT32_C(0x0000000f);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,6u)>>((7u-offset)*8u)));target=UINT32_C(0x80076394);goto dispatch;
L_80076394:
 STEP(UINT32_C(0x80076394)); /* b4860008 sdr a2,0x8(a0) */
 ea=(uint32_t)lo(m,4u)+UINT32_C(0x00000008);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,6u)<<(offset*8u)));target=UINT32_C(0x80076398);goto dispatch;
L_80076398:
 STEP(UINT32_C(0x80076398)); /* 00e2102a slt v0,a3,v0 */
 set(m,2u,((int64_t)lo(m,7u)<(int64_t)lo(m,2u)));target=UINT32_C(0x8007639c);goto dispatch;
L_8007639c:
 STEP(UINT32_C(0x8007639c)); /* 1440ffec bne v0,zero,80076350 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x800763a0));WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),4u,lo(m,14u));target=taken?UINT32_C(0x80076350):UINT32_C(0x800763a4);goto dispatch;}
L_800763a0:
 STEP(UINT32_C(0x800763a0)); /* ac8e0010 sw t6,0x10(a0) */
 WRITE((uint32_t)lo(m,4u)+UINT32_C(0x00000010),4u,lo(m,14u));target=UINT32_C(0x800763a4);goto dispatch;
L_800763a4:
 STEP(UINT32_C(0x800763a4)); /* 10000003 beq zero,zero,800763b4 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800763a8));set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=taken?UINT32_C(0x800763b4):UINT32_C(0x800763ac);goto dispatch;}
L_800763a8:
 STEP(UINT32_C(0x800763a8)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=UINT32_C(0x800763ac);goto dispatch;
L_800763ac:
 STEP(UINT32_C(0x800763ac)); /* 3c0a8007 lui t2,zero,0x8007 */
 set(m,10u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800763b0);goto dispatch;
L_800763b0:
 STEP(UINT32_C(0x800763b0)); /* 24020001 addiu v0,zero,1 */
 set(m,2u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=UINT32_C(0x800763b4);goto dispatch;
L_800763b4:
 STEP(UINT32_C(0x800763b4)); /* 8d846700 lw a0,0x6700(t4) */
 READ((uint32_t)lo(m,12u)+UINT32_C(0x00006700),4u);set(m,4u,sx((uint32_t)value));target=UINT32_C(0x800763b8);goto dispatch;
L_800763b8:
 STEP(UINT32_C(0x800763b8)); /* dd436708 ld v1,0x6708(t2) */
 READ((uint32_t)lo(m,10u)+UINT32_C(0x00006708),8u);set(m,3u,value);target=UINT32_C(0x800763bc);goto dispatch;
L_800763bc:
 STEP(UINT32_C(0x800763bc)); /* 01a21014 dsllv v0,v0,t5 */
 set(m,2u,lo(m,2u)<<(lo(m,13u)&63u));target=UINT32_C(0x800763c0);goto dispatch;
L_800763c0:
 STEP(UINT32_C(0x800763c0)); /* 00021027 nor v0,zero,v0 */
 set(m,2u,~(lo(m,0u)|lo(m,2u)));target=UINT32_C(0x800763c4);goto dispatch;
L_800763c4:
 STEP(UINT32_C(0x800763c4)); /* 2484ffff addiu a0,a0,-1 */
 set(m,4u,sx((uint32_t)lo(m,4u)+UINT32_C(0xffffffff)));target=UINT32_C(0x800763c8);goto dispatch;
L_800763c8:
 STEP(UINT32_C(0x800763c8)); /* 00621824 and v1,v1,v0 */
 set(m,3u,(lo(m,3u)&lo(m,2u)));target=UINT32_C(0x800763cc);goto dispatch;
L_800763cc:
 STEP(UINT32_C(0x800763cc)); /* ad846700 sw a0,0x6700(t4) */
 WRITE((uint32_t)lo(m,12u)+UINT32_C(0x00006700),4u,lo(m,4u));target=UINT32_C(0x800763d0);goto dispatch;
L_800763d0:
 STEP(UINT32_C(0x800763d0)); /* 15000003 bne t0,zero,800763e0 */
 {int taken=(lo(m,8u)!=lo(m,0u));STEP(UINT32_C(0x800763d4));WRITE((uint32_t)lo(m,10u)+UINT32_C(0x00006708),8u,lo(m,3u));target=taken?UINT32_C(0x800763e0):UINT32_C(0x800763d8);goto dispatch;}
L_800763d4:
 STEP(UINT32_C(0x800763d4)); /* fd436708 sd v1,0x6708(t2) */
 WRITE((uint32_t)lo(m,10u)+UINT32_C(0x00006708),8u,lo(m,3u));target=UINT32_C(0x800763d8);goto dispatch;
L_800763d8:
 STEP(UINT32_C(0x800763d8)); /* 0c01d918 jal 80076460 */
 set(m,31u,UINT64_C(0x800763e0));STEP(UINT32_C(0x800763dc));READ((uint32_t)lo(m,11u)+UINT32_C(0x00006740),2u);set(m,4u,value);target=UINT32_C(0x80076460);goto dispatch;
L_800763dc:
 STEP(UINT32_C(0x800763dc)); /* 95646740 lhu a0,0x6740(t3) */
 READ((uint32_t)lo(m,11u)+UINT32_C(0x00006740),2u);set(m,4u,value);target=UINT32_C(0x800763e0);goto dispatch;
L_800763e0:
 STEP(UINT32_C(0x800763e0)); /* 8e226700 lw v0,0x6700(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x800763e4);goto dispatch;
L_800763e4:
 STEP(UINT32_C(0x800763e4)); /* 14400004 bne v0,zero,800763f8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x800763e8));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000083)));target=taken?UINT32_C(0x800763f8):UINT32_C(0x800763ec);goto dispatch;}
L_800763e8:
 STEP(UINT32_C(0x800763e8)); /* 24030083 addiu v1,zero,131 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000083)));target=UINT32_C(0x800763ec);goto dispatch;
L_800763ec:
 STEP(UINT32_C(0x800763ec)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT32_C(0x800763f0);goto dispatch;
L_800763f0:
 STEP(UINT32_C(0x800763f0)); /* 34421810 ori v0,v0,0x1810 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1810));target=UINT32_C(0x800763f4);goto dispatch;
L_800763f4:
 STEP(UINT32_C(0x800763f4)); /* ac430000 sw v1,0x0(v0) */
 WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u,lo(m,3u));target=UINT32_C(0x800763f8);goto dispatch;
L_800763f8:
 STEP(UINT32_C(0x800763f8)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT32_C(0x800763fc);goto dispatch;
L_800763fc:
 STEP(UINT32_C(0x800763fc)); /* 0200202d daddu a0,s0,zero */
 set(m,4u,lo(m,16u)+lo(m,0u));target=UINT32_C(0x80076400);goto dispatch;
L_80076400:
 STEP(UINT32_C(0x80076400)); /* 34421800 ori v0,v0,0x1800 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1800));target=UINT32_C(0x80076404);goto dispatch;
L_80076404:
 STEP(UINT32_C(0x80076404)); /* 0c01d80e jal 80076038 */
 set(m,31u,UINT64_C(0x8007640c));STEP(UINT32_C(0x80076408));READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u);set(m,5u,sx((uint32_t)value));target=UINT32_C(0x80076038);goto dispatch;
L_80076408:
 STEP(UINT32_C(0x80076408)); /* 8c450000 lw a1,0x0(v0) */
 READ((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u);set(m,5u,sx((uint32_t)value));target=UINT32_C(0x8007640c);goto dispatch;
L_8007640c:
 STEP(UINT32_C(0x8007640c)); /* 10000005 beq zero,zero,80076424 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80076410));set(m,6u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,16u)));target=taken?UINT32_C(0x80076424):UINT32_C(0x80076414);goto dispatch;}
L_80076410:
 STEP(UINT32_C(0x80076410)); /* 00503023 subu a2,v0,s0 */
 set(m,6u,sx((uint32_t)lo(m,2u)-(uint32_t)lo(m,16u)));target=UINT32_C(0x80076414);goto dispatch;
L_80076414:
 STEP(UINT32_C(0x80076414)); /* 25080001 addiu t0,t0,1 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000001)));target=UINT32_C(0x80076418);goto dispatch;
L_80076418:
 STEP(UINT32_C(0x80076418)); /* 0102102a slt v0,t0,v0 */
 set(m,2u,((int64_t)lo(m,8u)<(int64_t)lo(m,2u)));target=UINT32_C(0x8007641c);goto dispatch;
L_8007641c:
 STEP(UINT32_C(0x8007641c)); /* 1440ffae bne v0,zero,800762d8 */
 {int taken=(lo(m,2u)!=lo(m,0u));STEP(UINT32_C(0x80076420));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=taken?UINT32_C(0x800762d8):UINT32_C(0x80076424);goto dispatch;}
L_80076420:
 STEP(UINT32_C(0x80076420)); /* 24030014 addiu v1,zero,20 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x80076424);goto dispatch;
L_80076424:
 STEP(UINT32_C(0x80076424)); /* 0000000f sync 0 */
 ++m->sync_p; /* native value barrier; no device/timing synthesis */target=UINT32_C(0x80076428);goto dispatch;
L_80076428:
 STEP(UINT32_C(0x80076428)); /* 00c0102d daddu v0,a2,zero */
 set(m,2u,lo(m,6u)+lo(m,0u));target=UINT32_C(0x8007642c);goto dispatch;
L_8007642c:
 STEP(UINT32_C(0x8007642c)); /* dfbf0020 ld ra,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u);set(m,31u,value);target=UINT32_C(0x80076430);goto dispatch;
L_80076430:
 STEP(UINT32_C(0x80076430)); /* dfb10010 ld s1,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),8u);set(m,17u,value);target=UINT32_C(0x80076434);goto dispatch;
L_80076434:
 STEP(UINT32_C(0x80076434)); /* dfb00000 ld s0,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,16u,value);target=UINT32_C(0x80076438);goto dispatch;
L_80076438:
 STEP(UINT32_C(0x80076438)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x8007643c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));goto dispatch;
L_8007643c:
 STEP(UINT32_C(0x8007643c)); /* 27bd0030 addiu sp,sp,48 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000030)));target=UINT32_C(0x80076440);goto dispatch;
L_80076440:
 STEP(UINT32_C(0x80076440)); /* 27bdfff0 addiu sp,sp,-16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xfffffff0)));target=UINT32_C(0x80076444);goto dispatch;
L_80076444:
 STEP(UINT32_C(0x80076444)); /* ffbf0000 sd ra,0x0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u,lo(m,31u));target=UINT32_C(0x80076448);goto dispatch;
L_80076448:
 STEP(UINT32_C(0x80076448)); /* 0c01d858 jal 80076160 */
 set(m,31u,UINT64_C(0x80076450));STEP(UINT32_C(0x8007644c));set(m,4u,lo(m,4u) & UINT64_C(0xffff));target=UINT32_C(0x80076160);goto dispatch;
L_8007644c:
 STEP(UINT32_C(0x8007644c)); /* 3084ffff andi a0,a0,0xffff */
 set(m,4u,lo(m,4u) & UINT64_C(0xffff));target=UINT32_C(0x80076450);goto dispatch;
L_80076450:
 STEP(UINT32_C(0x80076450)); /* 0000000f sync 0 */
 ++m->sync_p; /* native value barrier; no device/timing synthesis */target=UINT32_C(0x80076454);goto dispatch;
L_80076454:
 STEP(UINT32_C(0x80076454)); /* dfbf0000 ld ra,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),8u);set(m,31u,value);target=UINT32_C(0x80076458);goto dispatch;
L_80076458:
 STEP(UINT32_C(0x80076458)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x8007645c));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));goto dispatch;
L_8007645c:
 STEP(UINT32_C(0x8007645c)); /* 27bd0010 addiu sp,sp,16 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00000010)));target=UINT32_C(0x80076460);goto dispatch;
L_80076460:
 STEP(UINT32_C(0x80076460)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT32_C(0x80076464);goto dispatch;
L_80076464:
 STEP(UINT32_C(0x80076464)); /* 34421820 ori v0,v0,0x1820 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1820));target=UINT32_C(0x80076468);goto dispatch;
L_80076468:
 STEP(UINT32_C(0x80076468)); /* ac440000 sw a0,0x0(v0) */
 WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u,lo(m,4u));target=UINT32_C(0x8007646c);goto dispatch;
L_8007646c:
 STEP(UINT32_C(0x8007646c)); /* 0000000f sync 0 */
 ++m->sync_p; /* native value barrier; no device/timing synthesis */target=UINT32_C(0x80076470);goto dispatch;
L_80076470:
 STEP(UINT32_C(0x80076470)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT32_C(0x80076474);goto dispatch;
L_80076474:
 STEP(UINT32_C(0x80076474)); /* 24030583 addiu v1,zero,1411 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000583)));target=UINT32_C(0x80076478);goto dispatch;
L_80076478:
 STEP(UINT32_C(0x80076478)); /* 34421810 ori v0,v0,0x1810 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1810));target=UINT32_C(0x8007647c);goto dispatch;
L_8007647c:
 STEP(UINT32_C(0x8007647c)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076480));WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u,lo(m,3u));goto dispatch;
L_80076480:
 STEP(UINT32_C(0x80076480)); /* ac430000 sw v1,0x0(v0) */
 WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u,lo(m,3u));target=UINT32_C(0x80076484);goto dispatch;
L_80076488:
 STEP(UINT32_C(0x80076488)); /* 27bdff50 addiu sp,sp,-176 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0xffffff50)));target=UINT32_C(0x8007648c);goto dispatch;
L_8007648c:
 STEP(UINT32_C(0x8007648c)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=UINT32_C(0x80076490);goto dispatch;
L_80076490:
 STEP(UINT32_C(0x80076490)); /* ffbf00a0 sd ra,0xa0(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),8u,lo(m,31u));target=UINT32_C(0x80076494);goto dispatch;
L_80076494:
 STEP(UINT32_C(0x80076494)); /* ffb70090 sd s7,0x90(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000090),8u,lo(m,23u));target=UINT32_C(0x80076498);goto dispatch;
L_80076498:
 STEP(UINT32_C(0x80076498)); /* ffb60080 sd s6,0x80(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000080),8u,lo(m,22u));target=UINT32_C(0x8007649c);goto dispatch;
L_8007649c:
 STEP(UINT32_C(0x8007649c)); /* ffb50070 sd s5,0x70(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u,lo(m,21u));target=UINT32_C(0x800764a0);goto dispatch;
L_800764a0:
 STEP(UINT32_C(0x800764a0)); /* ffb40060 sd s4,0x60(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u,lo(m,20u));target=UINT32_C(0x800764a4);goto dispatch;
L_800764a4:
 STEP(UINT32_C(0x800764a4)); /* ffb30050 sd s3,0x50(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u,lo(m,19u));target=UINT32_C(0x800764a8);goto dispatch;
L_800764a8:
 STEP(UINT32_C(0x800764a8)); /* ffb20040 sd s2,0x40(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u,lo(m,18u));target=UINT32_C(0x800764ac);goto dispatch;
L_800764ac:
 STEP(UINT32_C(0x800764ac)); /* ffb10030 sd s1,0x30(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u,lo(m,17u));target=UINT32_C(0x800764b0);goto dispatch;
L_800764b0:
 STEP(UINT32_C(0x800764b0)); /* ffb00020 sd s0,0x20(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u,lo(m,16u));target=UINT32_C(0x800764b4);goto dispatch;
L_800764b4:
 STEP(UINT32_C(0x800764b4)); /* 3c118007 lui s1,zero,0x8007 */
 set(m,17u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800764b8);goto dispatch;
L_800764b8:
 STEP(UINT32_C(0x800764b8)); /* 3c128007 lui s2,zero,0x8007 */
 set(m,18u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800764bc);goto dispatch;
L_800764bc:
 STEP(UINT32_C(0x800764bc)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x800764c0);goto dispatch;
L_800764c0:
 STEP(UINT32_C(0x800764c0)); /* 8e226700 lw v0,0x6700(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x800764c4);goto dispatch;
L_800764c4:
 STEP(UINT32_C(0x800764c4)); /* 0102102a slt v0,t0,v0 */
 set(m,2u,((int64_t)lo(m,8u)<(int64_t)lo(m,2u)));target=UINT32_C(0x800764c8);goto dispatch;
L_800764c8:
 STEP(UINT32_C(0x800764c8)); /* 1040000a beq v0,zero,800764f4 */
 {int taken=(lo(m,2u)==lo(m,0u));STEP(UINT32_C(0x800764cc));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=taken?UINT32_C(0x800764f4):UINT32_C(0x800764d0);goto dispatch;}
L_800764cc:
 STEP(UINT32_C(0x800764cc)); /* 24030014 addiu v1,zero,20 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x800764d0);goto dispatch;
L_800764d0:
 STEP(UINT32_C(0x800764d0)); /* 26446740 addiu a0,s2,26432 */
 set(m,4u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00006740)));target=UINT32_C(0x800764d4);goto dispatch;
L_800764d4:
 STEP(UINT32_C(0x800764d4)); /* 01031818 mult_rd v1,t0,v1 */
 {int64_t product;if(lo(m,8u)!=sx((uint32_t)lo(m,8u))||lo(m,3u)!=sx((uint32_t)lo(m,3u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,8u)*(int64_t)(int32_t)lo(m,3u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=UINT32_C(0x800764d8);goto dispatch;
L_800764d8:
 STEP(UINT32_C(0x800764d8)); /* 96456740 lhu a1,0x6740(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00006740),2u);set(m,5u,value);target=UINT32_C(0x800764dc);goto dispatch;
L_800764dc:
 STEP(UINT32_C(0x800764dc)); /* 00641821 addu v1,v1,a0 */
 set(m,3u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,4u)));target=UINT32_C(0x800764e0);goto dispatch;
L_800764e0:
 STEP(UINT32_C(0x800764e0)); /* 94620000 lhu v0,0x0(v1) */
 READ((uint32_t)lo(m,3u)+UINT32_C(0x00000000),2u);set(m,2u,value);target=UINT32_C(0x800764e4);goto dispatch;
L_800764e4:
 STEP(UINT32_C(0x800764e4)); /* 10a2fff6 beq a1,v0,800764c0 */
 {int taken=(lo(m,5u)==lo(m,2u));STEP(UINT32_C(0x800764e8));set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000001)));target=taken?UINT32_C(0x800764c0):UINT32_C(0x800764ec);goto dispatch;}
L_800764e8:
 STEP(UINT32_C(0x800764e8)); /* 25080001 addiu t0,t0,1 */
 set(m,8u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000001)));target=UINT32_C(0x800764ec);goto dispatch;
L_800764ec:
 STEP(UINT32_C(0x800764ec)); /* 0c01d918 jal 80076460 */
 set(m,31u,UINT64_C(0x800764f4));STEP(UINT32_C(0x800764f0));set(m,4u,lo(m,2u)+lo(m,0u));target=UINT32_C(0x80076460);goto dispatch;
L_800764f0:
 STEP(UINT32_C(0x800764f0)); /* 0040202d daddu a0,v0,zero */
 set(m,4u,lo(m,2u)+lo(m,0u));target=UINT32_C(0x800764f4);goto dispatch;
L_800764f4:
 STEP(UINT32_C(0x800764f4)); /* 3c028007 lui v0,zero,0x8007 */
 set(m,2u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800764f8);goto dispatch;
L_800764f8:
 STEP(UINT32_C(0x800764f8)); /* 0220b02d daddu s6,s1,zero */
 set(m,22u,lo(m,17u)+lo(m,0u));target=UINT32_C(0x800764fc);goto dispatch;
L_800764fc:
 STEP(UINT32_C(0x800764fc)); /* 24546740 addiu s4,v0,26432 */
 set(m,20u,sx((uint32_t)lo(m,2u)+UINT32_C(0x00006740)));target=UINT32_C(0x80076500);goto dispatch;
L_80076500:
 STEP(UINT32_C(0x80076500)); /* 24130014 addiu s3,zero,20 */
 set(m,19u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000014)));target=UINT32_C(0x80076504);goto dispatch;
L_80076504:
 STEP(UINT32_C(0x80076504)); /* 3c158007 lui s5,zero,0x8007 */
 set(m,21u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x80076508);goto dispatch;
L_80076508:
 STEP(UINT32_C(0x80076508)); /* 10000004 beq zero,zero,8007651c */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x8007650c));set(m,23u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=taken?UINT32_C(0x8007651c):UINT32_C(0x80076510);goto dispatch;}
L_8007650c:
 STEP(UINT32_C(0x8007650c)); /* 24170001 addiu s7,zero,1 */
 set(m,23u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000001)));target=UINT32_C(0x80076510);goto dispatch;
L_80076510:
 STEP(UINT32_C(0x80076510)); /* 96426740 lhu v0,0x6740(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00006740),2u);set(m,2u,value);target=UINT32_C(0x80076514);goto dispatch;
L_80076514:
 STEP(UINT32_C(0x80076514)); /* 1462003e bne v1,v0,80076610 */
 {int taken=(lo(m,3u)!=lo(m,2u));STEP(UINT32_C(0x80076518));READ((uint32_t)lo(m,17u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=taken?UINT32_C(0x80076610):UINT32_C(0x8007651c);goto dispatch;}
L_80076518:
 STEP(UINT32_C(0x80076518)); /* 8e226700 lw v0,0x6700(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x8007651c);goto dispatch;
L_8007651c:
 STEP(UINT32_C(0x8007651c)); /* 8ec26700 lw v0,0x6700(s6) */
 READ((uint32_t)lo(m,22u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x80076520);goto dispatch;
L_80076520:
 STEP(UINT32_C(0x80076520)); /* 0000402d daddu t0,zero,zero */
 set(m,8u,lo(m,0u)+lo(m,0u));target=UINT32_C(0x80076524);goto dispatch;
L_80076524:
 STEP(UINT32_C(0x80076524)); /* 26466740 addiu a2,s2,26432 */
 set(m,6u,sx((uint32_t)lo(m,18u)+UINT32_C(0x00006740)));target=UINT32_C(0x80076528);goto dispatch;
L_80076528:
 STEP(UINT32_C(0x80076528)); /* 68c30007 ldl v1,0x7(a2) */
 ea=(uint32_t)lo(m,6u)+UINT32_C(0x00000007);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,3u,(lo(m,3u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT32_C(0x8007652c);goto dispatch;
L_8007652c:
 STEP(UINT32_C(0x8007652c)); /* 6cc30000 ldr v1,0x0(a2) */
 ea=(uint32_t)lo(m,6u)+UINT32_C(0x00000000);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,3u,(lo(m,3u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT32_C(0x80076530);goto dispatch;
L_80076530:
 STEP(UINT32_C(0x80076530)); /* 68c4000f ldl a0,0xf(a2) */
 ea=(uint32_t)lo(m,6u)+UINT32_C(0x0000000f);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,4u,(lo(m,4u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT32_C(0x80076534);goto dispatch;
L_80076534:
 STEP(UINT32_C(0x80076534)); /* 6cc40008 ldr a0,0x8(a2) */
 ea=(uint32_t)lo(m,6u)+UINT32_C(0x00000008);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,4u,(lo(m,4u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT32_C(0x80076538);goto dispatch;
L_80076538:
 STEP(UINT32_C(0x80076538)); /* 8cc50010 lw a1,0x10(a2) */
 READ((uint32_t)lo(m,6u)+UINT32_C(0x00000010),4u);set(m,5u,sx((uint32_t)value));target=UINT32_C(0x8007653c);goto dispatch;
L_8007653c:
 STEP(UINT32_C(0x8007653c)); /* b3a30007 sdl v1,0x7(sp) */
 ea=(uint32_t)lo(m,29u)+UINT32_C(0x00000007);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,3u)>>((7u-offset)*8u)));target=UINT32_C(0x80076540);goto dispatch;
L_80076540:
 STEP(UINT32_C(0x80076540)); /* b7a30000 sdr v1,0x0(sp) */
 ea=(uint32_t)lo(m,29u)+UINT32_C(0x00000000);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,3u)<<(offset*8u)));target=UINT32_C(0x80076544);goto dispatch;
L_80076544:
 STEP(UINT32_C(0x80076544)); /* b3a4000f sdl a0,0xf(sp) */
 ea=(uint32_t)lo(m,29u)+UINT32_C(0x0000000f);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,4u)>>((7u-offset)*8u)));target=UINT32_C(0x80076548);goto dispatch;
L_80076548:
 STEP(UINT32_C(0x80076548)); /* b7a40008 sdr a0,0x8(sp) */
 ea=(uint32_t)lo(m,29u)+UINT32_C(0x00000008);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,4u)<<(offset*8u)));target=UINT32_C(0x8007654c);goto dispatch;
L_8007654c:
 STEP(UINT32_C(0x8007654c)); /* afa50010 sw a1,0x10(sp) */
 WRITE((uint32_t)lo(m,29u)+UINT32_C(0x00000010),4u,lo(m,5u));target=UINT32_C(0x80076550);goto dispatch;
L_80076550:
 STEP(UINT32_C(0x80076550)); /* 2442ffff addiu v0,v0,-1 */
 set(m,2u,sx((uint32_t)lo(m,2u)+UINT32_C(0xffffffff)));target=UINT32_C(0x80076554);goto dispatch;
L_80076554:
 STEP(UINT32_C(0x80076554)); /* 1840001a blez v0,zero,800765c0 */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x80076558));WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00006700),4u,lo(m,2u));target=taken?UINT32_C(0x800765c0):UINT32_C(0x8007655c);goto dispatch;}
L_80076558:
 STEP(UINT32_C(0x80076558)); /* aec26700 sw v0,0x6700(s6) */
 WRITE((uint32_t)lo(m,22u)+UINT32_C(0x00006700),4u,lo(m,2u));target=UINT32_C(0x8007655c);goto dispatch;
L_8007655c:
 STEP(UINT32_C(0x8007655c)); /* 8e296700 lw t1,0x6700(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00006700),4u);set(m,9u,sx((uint32_t)value));target=UINT32_C(0x80076560);goto dispatch;
L_80076560:
 STEP(UINT32_C(0x80076560)); /* 8faa0010 lw t2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),4u);set(m,10u,sx((uint32_t)value));target=UINT32_C(0x80076564);goto dispatch;
L_80076564:
 STEP(UINT32_C(0x80076564)); /* 8fa60004 lw a2,0x4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000004),4u);set(m,6u,sx((uint32_t)value));target=UINT32_C(0x80076568);goto dispatch;
L_80076568:
 STEP(UINT32_C(0x80076568)); /* 97a70000 lhu a3,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),2u);set(m,7u,value);target=UINT32_C(0x8007656c);goto dispatch;
L_8007656c:
 STEP(UINT32_C(0x8007656c)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x80076570);goto dispatch;
L_80076570:
 STEP(UINT32_C(0x80076570)); /* 01131818 mult_rd v1,t0,s3 */
 {int64_t product;if(lo(m,8u)!=sx((uint32_t)lo(m,8u))||lo(m,19u)!=sx((uint32_t)lo(m,19u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,8u)*(int64_t)(int32_t)lo(m,19u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=UINT32_C(0x80076574);goto dispatch;
L_80076574:
 STEP(UINT32_C(0x80076574)); /* 25020001 addiu v0,t0,1 */
 set(m,2u,sx((uint32_t)lo(m,8u)+UINT32_C(0x00000001)));target=UINT32_C(0x80076578);goto dispatch;
L_80076578:
 STEP(UINT32_C(0x80076578)); /* 0040402d daddu t0,v0,zero */
 set(m,8u,lo(m,2u)+lo(m,0u));target=UINT32_C(0x8007657c);goto dispatch;
L_8007657c:
 STEP(UINT32_C(0x8007657c)); /* 00742821 addu a1,v1,s4 */
 set(m,5u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,20u)));target=UINT32_C(0x80076580);goto dispatch;
L_80076580:
 STEP(UINT32_C(0x80076580)); /* 00531818 mult_rd v1,v0,s3 */
 {int64_t product;if(lo(m,2u)!=sx((uint32_t)lo(m,2u))||lo(m,19u)!=sx((uint32_t)lo(m,19u)))return stop(m,s,NOCTURNE_WAKEUP_UNDEFINED_WORD_MULTIPLY,0,0,0);product=(int64_t)(int32_t)lo(m,2u)*(int64_t)(int32_t)lo(m,19u);m->lo=sx((uint32_t)product);m->hi=sx((uint32_t)((uint64_t)product>>32));set(m,3u,m->lo);}target=UINT32_C(0x80076584);goto dispatch;
L_80076584:
 STEP(UINT32_C(0x80076584)); /* 00742021 addu a0,v1,s4 */
 set(m,4u,sx((uint32_t)lo(m,3u)+(uint32_t)lo(m,20u)));target=UINT32_C(0x80076588);goto dispatch;
L_80076588:
 STEP(UINT32_C(0x80076588)); /* 688b0007 ldl t3,0x7(a0) */
 ea=(uint32_t)lo(m,4u)+UINT32_C(0x00000007);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,11u,(lo(m,11u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT32_C(0x8007658c);goto dispatch;
L_8007658c:
 STEP(UINT32_C(0x8007658c)); /* 6c8b0000 ldr t3,0x0(a0) */
 ea=(uint32_t)lo(m,4u)+UINT32_C(0x00000000);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,11u,(lo(m,11u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT32_C(0x80076590);goto dispatch;
L_80076590:
 STEP(UINT32_C(0x80076590)); /* 688c000f ldl t4,0xf(a0) */
 ea=(uint32_t)lo(m,4u)+UINT32_C(0x0000000f);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,12u,(lo(m,12u)&ldl_mask[offset])|(value<<((7u-offset)*8u)));target=UINT32_C(0x80076594);goto dispatch;
L_80076594:
 STEP(UINT32_C(0x80076594)); /* 6c8c0008 ldr t4,0x8(a0) */
 ea=(uint32_t)lo(m,4u)+UINT32_C(0x00000008);offset=ea&7u;READ(ea&~UINT32_C(7),8u);set(m,12u,(lo(m,12u)&ldr_mask[offset])|(value>>(offset*8u)));target=UINT32_C(0x80076598);goto dispatch;
L_80076598:
 STEP(UINT32_C(0x80076598)); /* 8c8d0010 lw t5,0x10(a0) */
 READ((uint32_t)lo(m,4u)+UINT32_C(0x00000010),4u);set(m,13u,sx((uint32_t)value));target=UINT32_C(0x8007659c);goto dispatch;
L_8007659c:
 STEP(UINT32_C(0x8007659c)); /* b0ab0007 sdl t3,0x7(a1) */
 ea=(uint32_t)lo(m,5u)+UINT32_C(0x00000007);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,11u)>>((7u-offset)*8u)));target=UINT32_C(0x800765a0);goto dispatch;
L_800765a0:
 STEP(UINT32_C(0x800765a0)); /* b4ab0000 sdr t3,0x0(a1) */
 ea=(uint32_t)lo(m,5u)+UINT32_C(0x00000000);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,11u)<<(offset*8u)));target=UINT32_C(0x800765a4);goto dispatch;
L_800765a4:
 STEP(UINT32_C(0x800765a4)); /* b0ac000f sdl t4,0xf(a1) */
 ea=(uint32_t)lo(m,5u)+UINT32_C(0x0000000f);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdl_mask[offset])|(lo(m,12u)>>((7u-offset)*8u)));target=UINT32_C(0x800765a8);goto dispatch;
L_800765a8:
 STEP(UINT32_C(0x800765a8)); /* b4ac0008 sdr t4,0x8(a1) */
 ea=(uint32_t)lo(m,5u)+UINT32_C(0x00000008);offset=ea&7u;READ(ea&~UINT32_C(7),8u);WRITE(ea&~UINT32_C(7),8u,(value&sdr_mask[offset])|(lo(m,12u)<<(offset*8u)));target=UINT32_C(0x800765ac);goto dispatch;
L_800765ac:
 STEP(UINT32_C(0x800765ac)); /* 0109182a slt v1,t0,t1 */
 set(m,3u,((int64_t)lo(m,8u)<(int64_t)lo(m,9u)));target=UINT32_C(0x800765b0);goto dispatch;
L_800765b0:
 STEP(UINT32_C(0x800765b0)); /* 1460ffef bne v1,zero,80076570 */
 {int taken=(lo(m,3u)!=lo(m,0u));STEP(UINT32_C(0x800765b4));WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000010),4u,lo(m,13u));target=taken?UINT32_C(0x80076570):UINT32_C(0x800765b8);goto dispatch;}
L_800765b4:
 STEP(UINT32_C(0x800765b4)); /* acad0010 sw t5,0x10(a1) */
 WRITE((uint32_t)lo(m,5u)+UINT32_C(0x00000010),4u,lo(m,13u));target=UINT32_C(0x800765b8);goto dispatch;
L_800765b8:
 STEP(UINT32_C(0x800765b8)); /* 10000004 beq zero,zero,800765cc */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x800765bc));/* nop */target=taken?UINT32_C(0x800765cc):UINT32_C(0x800765c0);goto dispatch;}
L_800765bc:
 STEP(UINT32_C(0x800765bc)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x800765c0);goto dispatch;
L_800765c0:
 STEP(UINT32_C(0x800765c0)); /* 8faa0010 lw t2,0x10(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000010),4u);set(m,10u,sx((uint32_t)value));target=UINT32_C(0x800765c4);goto dispatch;
L_800765c4:
 STEP(UINT32_C(0x800765c4)); /* 8fa60004 lw a2,0x4(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000004),4u);set(m,6u,sx((uint32_t)value));target=UINT32_C(0x800765c8);goto dispatch;
L_800765c8:
 STEP(UINT32_C(0x800765c8)); /* 97a70000 lhu a3,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),2u);set(m,7u,value);target=UINT32_C(0x800765cc);goto dispatch;
L_800765cc:
 STEP(UINT32_C(0x800765cc)); /* 0380802d daddu s0,gp,zero */
 set(m,16u,lo(m,28u)+lo(m,0u));target=UINT32_C(0x800765d0);goto dispatch;
L_800765d0:
 STEP(UINT32_C(0x800765d0)); /* 0140e02d daddu gp,t2,zero */
 set(m,28u,lo(m,10u)+lo(m,0u));target=UINT32_C(0x800765d4);goto dispatch;
L_800765d4:
 STEP(UINT32_C(0x800765d4)); /* dea36708 ld v1,0x6708(s5) */
 READ((uint32_t)lo(m,21u)+UINT32_C(0x00006708),8u);set(m,3u,value);target=UINT32_C(0x800765d8);goto dispatch;
L_800765d8:
 STEP(UINT32_C(0x800765d8)); /* 00d71014 dsllv v0,s7,a2 */
 set(m,2u,lo(m,23u)<<(lo(m,6u)&63u));target=UINT32_C(0x800765dc);goto dispatch;
L_800765dc:
 STEP(UINT32_C(0x800765dc)); /* 00021027 nor v0,zero,v0 */
 set(m,2u,~(lo(m,0u)|lo(m,2u)));target=UINT32_C(0x800765e0);goto dispatch;
L_800765e0:
 STEP(UINT32_C(0x800765e0)); /* 3c040008 lui a0,zero,0x8 */
 set(m,4u,sx(UINT32_C(0x00080000)));target=UINT32_C(0x800765e4);goto dispatch;
L_800765e4:
 STEP(UINT32_C(0x800765e4)); /* 00621824 and v1,v1,v0 */
 set(m,3u,(lo(m,3u)&lo(m,2u)));target=UINT32_C(0x800765e8);goto dispatch;
L_800765e8:
 STEP(UINT32_C(0x800765e8)); /* 8fa50008 lw a1,0x8(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000008),4u);set(m,5u,sx((uint32_t)value));target=UINT32_C(0x800765ec);goto dispatch;
L_800765ec:
 STEP(UINT32_C(0x800765ec)); /* 8fa8000c lw t0,0xc(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x0000000c),4u);set(m,8u,sx((uint32_t)value));target=UINT32_C(0x800765f0);goto dispatch;
L_800765f0:
 STEP(UINT32_C(0x800765f0)); /* 34842000 ori a0,a0,0x2000 */
 set(m,4u,lo(m,4u) | UINT64_C(0x2000));target=UINT32_C(0x800765f4);goto dispatch;
L_800765f4:
 STEP(UINT32_C(0x800765f4)); /* 0c01d9a0 jal 80076680 */
 set(m,31u,UINT64_C(0x800765fc));STEP(UINT32_C(0x800765f8));WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00006708),8u,lo(m,3u));target=UINT32_C(0x80076680);goto dispatch;
L_800765f8:
 STEP(UINT32_C(0x800765f8)); /* fea36708 sd v1,0x6708(s5) */
 WRITE((uint32_t)lo(m,21u)+UINT32_C(0x00006708),8u,lo(m,3u));target=UINT32_C(0x800765fc);goto dispatch;
L_800765fc:
 STEP(UINT32_C(0x800765fc)); /* 0200e02d daddu gp,s0,zero */
 set(m,28u,lo(m,16u)+lo(m,0u));target=UINT32_C(0x80076600);goto dispatch;
L_80076600:
 STEP(UINT32_C(0x80076600)); /* 8e226700 lw v0,0x6700(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x80076604);goto dispatch;
L_80076604:
 STEP(UINT32_C(0x80076604)); /* 1c40ffc2 bgtz v0,zero,80076510 */
 {int taken=((int64_t)lo(m,2u)>0);STEP(UINT32_C(0x80076608));READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),2u);set(m,3u,value);target=taken?UINT32_C(0x80076510):UINT32_C(0x8007660c);goto dispatch;}
L_80076608:
 STEP(UINT32_C(0x80076608)); /* 97a30000 lhu v1,0x0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000000),2u);set(m,3u,value);target=UINT32_C(0x8007660c);goto dispatch;
L_8007660c:
 STEP(UINT32_C(0x8007660c)); /* 8e226700 lw v0,0x6700(s1) */
 READ((uint32_t)lo(m,17u)+UINT32_C(0x00006700),4u);set(m,2u,sx((uint32_t)value));target=UINT32_C(0x80076610);goto dispatch;
L_80076610:
 STEP(UINT32_C(0x80076610)); /* 18400005 blez v0,zero,80076628 */
 {int taken=((int64_t)lo(m,2u)<=0);STEP(UINT32_C(0x80076614));set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000483)));target=taken?UINT32_C(0x80076628):UINT32_C(0x80076618);goto dispatch;}
L_80076614:
 STEP(UINT32_C(0x80076614)); /* 24030483 addiu v1,zero,1155 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0x00000483)));target=UINT32_C(0x80076618);goto dispatch;
L_80076618:
 STEP(UINT32_C(0x80076618)); /* 0c01d918 jal 80076460 */
 set(m,31u,UINT64_C(0x80076620));STEP(UINT32_C(0x8007661c));READ((uint32_t)lo(m,18u)+UINT32_C(0x00006740),2u);set(m,4u,value);target=UINT32_C(0x80076460);goto dispatch;
L_8007661c:
 STEP(UINT32_C(0x8007661c)); /* 96446740 lhu a0,0x6740(s2) */
 READ((uint32_t)lo(m,18u)+UINT32_C(0x00006740),2u);set(m,4u,value);target=UINT32_C(0x80076620);goto dispatch;
L_80076620:
 STEP(UINT32_C(0x80076620)); /* 10000004 beq zero,zero,80076634 */
 {int taken=(lo(m,0u)==lo(m,0u));STEP(UINT32_C(0x80076624));/* nop */target=taken?UINT32_C(0x80076634):UINT32_C(0x80076628);goto dispatch;}
L_80076624:
 STEP(UINT32_C(0x80076624)); /* 00000000 nop */
 /* nop */target=UINT32_C(0x80076628);goto dispatch;
L_80076628:
 STEP(UINT32_C(0x80076628)); /* 3c02b000 lui v0,zero,0xb000 */
 set(m,2u,sx(UINT32_C(0xb0000000)));target=UINT32_C(0x8007662c);goto dispatch;
L_8007662c:
 STEP(UINT32_C(0x8007662c)); /* 34421810 ori v0,v0,0x1810 */
 set(m,2u,lo(m,2u) | UINT64_C(0x1810));target=UINT32_C(0x80076630);goto dispatch;
L_80076630:
 STEP(UINT32_C(0x80076630)); /* ac430000 sw v1,0x0(v0) */
 WRITE((uint32_t)lo(m,2u)+UINT32_C(0x00000000),4u,lo(m,3u));target=UINT32_C(0x80076634);goto dispatch;
L_80076634:
 STEP(UINT32_C(0x80076634)); /* 0000000f sync 0 */
 ++m->sync_p; /* native value barrier; no device/timing synthesis */target=UINT32_C(0x80076638);goto dispatch;
L_80076638:
 STEP(UINT32_C(0x80076638)); /* 42000038 ei */
 if((m->status&UINT32_C(0x00020006))||(m->status&UINT32_C(0x18))==0u)m->status|=UINT32_C(0x10000); /* EI: EDI/EXL/ERL/kernel conditional EIE set */target=UINT32_C(0x8007663c);goto dispatch;
L_8007663c:
 STEP(UINT32_C(0x8007663c)); /* dfbf00a0 ld ra,0xa0(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x000000a0),8u);set(m,31u,value);target=UINT32_C(0x80076640);goto dispatch;
L_80076640:
 STEP(UINT32_C(0x80076640)); /* dfb70090 ld s7,0x90(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000090),8u);set(m,23u,value);target=UINT32_C(0x80076644);goto dispatch;
L_80076644:
 STEP(UINT32_C(0x80076644)); /* dfb60080 ld s6,0x80(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000080),8u);set(m,22u,value);target=UINT32_C(0x80076648);goto dispatch;
L_80076648:
 STEP(UINT32_C(0x80076648)); /* dfb50070 ld s5,0x70(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000070),8u);set(m,21u,value);target=UINT32_C(0x8007664c);goto dispatch;
L_8007664c:
 STEP(UINT32_C(0x8007664c)); /* dfb40060 ld s4,0x60(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000060),8u);set(m,20u,value);target=UINT32_C(0x80076650);goto dispatch;
L_80076650:
 STEP(UINT32_C(0x80076650)); /* dfb30050 ld s3,0x50(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000050),8u);set(m,19u,value);target=UINT32_C(0x80076654);goto dispatch;
L_80076654:
 STEP(UINT32_C(0x80076654)); /* dfb20040 ld s2,0x40(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000040),8u);set(m,18u,value);target=UINT32_C(0x80076658);goto dispatch;
L_80076658:
 STEP(UINT32_C(0x80076658)); /* dfb10030 ld s1,0x30(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000030),8u);set(m,17u,value);target=UINT32_C(0x8007665c);goto dispatch;
L_8007665c:
 STEP(UINT32_C(0x8007665c)); /* dfb00020 ld s0,0x20(sp) */
 READ((uint32_t)lo(m,29u)+UINT32_C(0x00000020),8u);set(m,16u,value);target=UINT32_C(0x80076660);goto dispatch;
L_80076660:
 STEP(UINT32_C(0x80076660)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x80076664));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000b0)));goto dispatch;
L_80076664:
 STEP(UINT32_C(0x80076664)); /* 27bd00b0 addiu sp,sp,176 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x000000b0)));target=UINT32_C(0x80076668);goto dispatch;
L_80076680:
 STEP(UINT32_C(0x80076680)); /* 3c1a8007 lui k0,zero,0x8007 */
 set(m,26u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x80076684);goto dispatch;
L_80076684:
 STEP(UINT32_C(0x80076684)); /* af5f6c40 sw ra,0x6c40(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00006c40),4u,lo(m,31u));target=UINT32_C(0x80076688);goto dispatch;
L_80076688:
 STEP(UINT32_C(0x80076688)); /* 3c1a8007 lui k0,zero,0x8007 */
 set(m,26u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x8007668c);goto dispatch;
L_8007668c:
 STEP(UINT32_C(0x8007668c)); /* af5d6c50 sw sp,0x6c50(k0) */
 WRITE((uint32_t)lo(m,26u)+UINT32_C(0x00006c50),4u,lo(m,29u));target=UINT32_C(0x80076690);goto dispatch;
L_80076690:
 STEP(UINT32_C(0x80076690)); /* 40847000 mtc0 a0,EPC */
 m->epc=(uint32_t)lo(m,4u);target=UINT32_C(0x80076694);goto dispatch;
L_80076694:
 STEP(UINT32_C(0x80076694)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier; no device/timing synthesis */target=UINT32_C(0x80076698);goto dispatch;
L_80076698:
 STEP(UINT32_C(0x80076698)); /* 00a0182d daddu v1,a1,zero */
 set(m,3u,lo(m,5u)+lo(m,0u));target=UINT32_C(0x8007669c);goto dispatch;
L_8007669c:
 STEP(UINT32_C(0x8007669c)); /* 00c0202d daddu a0,a2,zero */
 set(m,4u,lo(m,6u)+lo(m,0u));target=UINT32_C(0x800766a0);goto dispatch;
L_800766a0:
 STEP(UINT32_C(0x800766a0)); /* 00e0282d daddu a1,a3,zero */
 set(m,5u,lo(m,7u)+lo(m,0u));target=UINT32_C(0x800766a4);goto dispatch;
L_800766a4:
 STEP(UINT32_C(0x800766a4)); /* 0100302d daddu a2,t0,zero */
 set(m,6u,lo(m,8u)+lo(m,0u));target=UINT32_C(0x800766a8);goto dispatch;
L_800766a8:
 STEP(UINT32_C(0x800766a8)); /* 401a6000 mfc0 k0,Status */
 set(m,26u,sx(m->status));target=UINT32_C(0x800766ac);goto dispatch;
L_800766ac:
 STEP(UINT32_C(0x800766ac)); /* 375a0012 ori k0,k0,0x12 */
 set(m,26u,lo(m,26u) | UINT64_C(0x12));target=UINT32_C(0x800766b0);goto dispatch;
L_800766b0:
 STEP(UINT32_C(0x800766b0)); /* 409a6000 mtc0 k0,Status */
 m->status=(uint32_t)lo(m,26u);target=UINT32_C(0x800766b4);goto dispatch;
L_800766b4:
 STEP(UINT32_C(0x800766b4)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier; no device/timing synthesis */target=UINT32_C(0x800766b8);goto dispatch;
L_800766b8:
 STEP(UINT32_C(0x800766b8)); /* 42000018 eret */
 if(m->status&4u)return stop(m,s,NOCTURNE_NATIVE_PROCESSOR_DOMAIN,0,0,0);m->status&=~2u;m->pc=m->epc;return stop(m,s,NOCTURNE_WAKEUP_RETURNED,0,0,sx(m->pc));
L_800766c0:
 STEP(UINT32_C(0x800766c0)); /* 40016000 mfc0 at,Status */
 set(m,1u,sx(m->status));target=UINT32_C(0x800766c4);goto dispatch;
L_800766c4:
 STEP(UINT32_C(0x800766c4)); /* 241affe4 addiu k0,zero,-28 */
 set(m,26u,sx((uint32_t)lo(m,0u)+UINT32_C(0xffffffe4)));target=UINT32_C(0x800766c8);goto dispatch;
L_800766c8:
 STEP(UINT32_C(0x800766c8)); /* 003a0824 and at,at,k0 */
 set(m,1u,(lo(m,1u)&lo(m,26u)));target=UINT32_C(0x800766cc);goto dispatch;
L_800766cc:
 STEP(UINT32_C(0x800766cc)); /* 40816000 mtc0 at,Status */
 m->status=(uint32_t)lo(m,1u);target=UINT32_C(0x800766d0);goto dispatch;
L_800766d0:
 STEP(UINT32_C(0x800766d0)); /* 0000040f sync 16 */
 ++m->sync_p; /* native value barrier; no device/timing synthesis */target=UINT32_C(0x800766d4);goto dispatch;
L_800766d4:
 STEP(UINT32_C(0x800766d4)); /* 3c1a8007 lui k0,zero,0x8007 */
 set(m,26u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800766d8);goto dispatch;
L_800766d8:
 STEP(UINT32_C(0x800766d8)); /* 8f5f6c40 lw ra,0x6c40(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x00006c40),4u);set(m,31u,sx((uint32_t)value));target=UINT32_C(0x800766dc);goto dispatch;
L_800766dc:
 STEP(UINT32_C(0x800766dc)); /* 3c1a8007 lui k0,zero,0x8007 */
 set(m,26u,sx(UINT32_C(0x80070000)));target=UINT32_C(0x800766e0);goto dispatch;
L_800766e0:
 STEP(UINT32_C(0x800766e0)); /* 03e00008 jr ra */
 target=(uint32_t)lo(m,31u);STEP(UINT32_C(0x800766e4));READ((uint32_t)lo(m,26u)+UINT32_C(0x00006c50),4u);set(m,29u,sx((uint32_t)value));goto dispatch;
L_800766e4:
 STEP(UINT32_C(0x800766e4)); /* 8f5d6c50 lw sp,0x6c50(k0) */
 READ((uint32_t)lo(m,26u)+UINT32_C(0x00006c50),4u);set(m,29u,sx((uint32_t)value));target=UINT32_C(0x800766e8);goto dispatch;
L_00082000:
 STEP(UINT32_C(0x00082000)); /* 3c1d0008 lui sp,zero,0x8 */
 set(m,29u,sx(UINT32_C(0x00080000)));target=UINT32_C(0x00082004);goto dispatch;
L_00082004:
 STEP(UINT32_C(0x00082004)); /* 0060f809 jalr ra,v1 */
 target=(uint32_t)lo(m,3u);set(m,31u,UINT64_C(0x0008200c));STEP(UINT32_C(0x00082008));set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00001fc0)));goto dispatch;
L_00082008:
 STEP(UINT32_C(0x00082008)); /* 27bd1fc0 addiu sp,sp,8128 */
 set(m,29u,sx((uint32_t)lo(m,29u)+UINT32_C(0x00001fc0)));target=UINT32_C(0x0008200c);goto dispatch;
L_0008200c:
 STEP(UINT32_C(0x0008200c)); /* 2403fff8 addiu v1,zero,-8 */
 set(m,3u,sx((uint32_t)lo(m,0u)+UINT32_C(0xfffffff8)));target=UINT32_C(0x00082010);goto dispatch;
L_00082010:
 m->pc=UINT32_C(0x00082010);if(m->instructions-started>=limit)return stop(m,s,NOCTURNE_WAKEUP_INSTRUCTION_LIMIT,0,0,0);return stop(m,s,NOCTURNE_NATIVE_SYSCALL,0,0,sx(m->pc)); /* unexecuted SYS; router counts exactly once */
#undef STEP
#undef READ
#undef WRITE
}

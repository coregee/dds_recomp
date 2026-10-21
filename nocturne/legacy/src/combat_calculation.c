/* Complete native SLUS_209.11 combat-calculation algorithms. HD supplies role
 * names only; native word arithmetic, raw64 decisions and live RAM order win.
 * This layer does not materialize volatile CPU/FPR banks or guest save frames. */
#include "combat_calculation.h"
#include "nocturne.h"
#include "battle_work_access.h"
#include "battle_support_access.h"
#include "battle_action_status.h"
#include "battle_targeting.h"
#include "battle_affinity.h"
#include "unit_progression.h"
#include "libc_printf.h"
#include "compiler_numeric.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <string.h>
#include <stdlib.h>

static uint8_t *at(uint32_t a)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveCombatCalculationAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint8_t r8(uint32_t a) { return *at(a); }
static uint16_t r16(uint32_t a) { uint16_t v; memcpy(&v,at(a),2);return v; }
static uint32_t r32(uint32_t a) { uint32_t v; memcpy(&v,at(a),4);return v; }
static uint64_t r64(uint32_t a) { uint64_t v; memcpy(&v,at(a),8);return v; }
static void w8(uint32_t a,uint8_t v) { *at(a)=v; }
static void w16(uint32_t a,uint16_t v) { memcpy(at(a),&v,2); }
static void w32(uint32_t a,uint32_t v) { memcpy(at(a),&v,4); }
static int32_t i8(uint8_t v) { return v<128u?(int32_t)v:(int32_t)v-256; }
static int32_t i16(uint16_t v) { return v<32768u?(int32_t)v:(int32_t)v-65536; }
static int32_t i32(uint32_t v) { return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v); }
static uint64_t sx(uint32_t v) { return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v; }
static int lt(uint64_t a,uint64_t b) { return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000)); }
static uint32_t asr(uint32_t v,unsigned n) { return (v>>n)|((v&0x80000000u)?UINT32_MAX<<(32u-n):0); }
static uint32_t mul(uint32_t a,uint32_t b) { return (uint32_t)((int64_t)i32(a)*(int64_t)i32(b)); }
static uint32_t divs(uint32_t a,uint32_t b)
{
    int64_t n=i32(a),d=i32(b);
    if(!d) return n<0?1u:UINT32_MAX;
    return (uint32_t)(n/d);
}
static uint32_t fbits(float v) { uint32_t b; memcpy(&b,&v,4);return b; }
static float fvalue(uint32_t v) { float f;memcpy(&f,&v,4);return f; }
static uint32_t cv(uint32_t v) { return EE_FPU_CVT_S_W(v); }
static uint32_t truncw(uint32_t v) { return EE_FPU_CVT_W_S(v); }
static uint32_t fm(uint32_t a,uint32_t b) { return EE_FPU_MUL_S(a,b); }
static uint32_t fa(uint32_t a,uint32_t b) { return EE_FPU_ADD_S(a,b); }
static uint32_t fs(uint32_t a,uint32_t b) { return EE_FPU_SUB_S(a,b); }
static uint32_t fd(uint32_t a,uint32_t b) { return EE_FPU_DIV_S(a,b); }
static int flt(uint32_t a,uint32_t b) { return EE_FPU_COMPARE_S(a,b,1)!=0; }
static uint32_t global(void) { return r32(0x54ea20u); }
static datUnitWork_PS2 *unit(uint32_t a) { return (datUnitWork_PS2 *)at(a); }
static uint32_t descriptor(uint64_t skill) { return 0x3d7998u+(uint32_t)skill*60u; }
static uint32_t encounter(uint32_t id) { return 0x3aefe0u+id*38u; }
static uint32_t pack(uint32_t c) { return r32(c+0x30)*8u+r32(c+0x28)*420u+r32(c+0x2c)*100u; }
static uint64_t random100(void) { return sx(sdfGetRandInt(NULL,100)); }

/* Registered243EE0 raw-ABI extension: canonical arguments retain the real
 * registered call. High64 indexes still execute all native LB and status reads,
 * with word address wrap and the FULL64 XORI/move condition. */
static uint64_t parameter(uint32_t u,uint64_t p)
{
    if(p<=UINT32_MAX || p==sx((uint32_t)p)) return sx((uint32_t)datGetParam(unit(u),i32((uint32_t)p)));
    uint32_t t=u+(uint32_t)p+0x10u;
    uint32_t flags=r32(u);
    uint32_t a=(uint32_t)i8(*(const volatile uint8_t *)at(t+6));
    uint32_t b=(uint32_t)i8(*(const volatile uint8_t *)at(t+12));
    uint32_t sum=a+b;
    if(!(flags&4u)) sum+=(uint32_t)i8(*(const volatile uint8_t *)at(u+(uint32_t)p+0x7a));
    if(i32(sum)<=0) sum=1;
    if(i32(sum)>40) sum=40;
    uint32_t status=r16(u+14)&0xfffu;
    if(status==0x200u && (p^4u)!=0) sum=1;
    return sx(sum);
}
static void set_status(uint32_t u,uint64_t status)
{
    if(status<=UINT32_MAX) { datSetBadStat(unit(u),(uint32_t)status);return; }
    uint32_t old=r16(u+14); /* Native BNE delay LHU, before any branch result. */
    if(status==0x8000u) w16(u+14,(uint16_t)(old|0x8000u));
    else if((uint64_t)(old&0xfffu)<status) w16(u+14,(uint16_t)((old&0xf000u)|(status&0xfffu)));
}
static uint32_t scaled_agility(uint32_t u)
{
    uint32_t p=(uint32_t)parameter(u,4);
    uint32_t level=r16(u+0x14);
    uint32_t q=divs(p,level/5u+3u);
    return q*100u;
}
static uint32_t cap_hit(uint32_t f)
{
    if(flt(f,0x42480000u)) f=0x42480000u;
    if(flt(0x42c80000u,f)) f=0x42c80000u;
    return f;
}

uint64_t ps2CombatHitType_002654B8(uint64_t context,uint64_t skill,uint64_t source,uint64_t target)
{
    uint32_t c=(uint32_t)context;
    uint32_t su=(uint32_t)nbGetUnitWorkFromFormindex(source);
    uint32_t tu=(uint32_t)nbGetUnitWorkFromFormindex(target);
    uint64_t attr=nbGetNormalSkillAttr(skill);
    if(attr==UINT64_MAX || (!lt(attr,UINT64_MAX) && lt(attr,16) && !lt(attr,12))) return 0;
    uint64_t affinity=nbGetAisyo(skill,target,attr);
    if(skill==0) {
        if(nbHatudoCheckSkill(unit(su),0x12c)) { w32(c+0x58,0x12c);return 1; }
        if(nbHatudoCheckSkill(unit(su),0x12d)) { w32(c+0x58,0x12d);return 1; }
    }
    if(lt(affinity,0)) return 2;
    uint32_t party=(uint32_t)nbGetPartyFromFormindex(source);
    if(r16(party)&0x100u) return 1;
    uint32_t status=r16(tu+14)&0xfffu;
    uint32_t factor=cv(status==1||status==2?100u:(status==4||status==0x10?8u:1u));
    uint32_t forms=r32(r32(c));
    if(r32(forms+(uint32_t)target*240u+0x78)&0x2000u) {
        if(!evtBitCheck(0xaf2)) factor=0x42c80000u;
    }
    int marked=0;
    if(skill==0 && nbHatudoCheckSkill(unit(su),0x12b)) {
        marked=1;
        factor=fm(factor,fd(cv((uint32_t)i16(r16(0x3dc1f8))),0x42c80000u));
    }
    uint32_t d=descriptor(skill);
    if(r8(d+2)!=0) return 0;
    (void)*(const volatile uint32_t *)at(su);
    uint32_t source_scaled=scaled_agility(su);
    uint32_t target_scaled=scaled_agility(tu);
    uint32_t base=cv(100u-(uint32_t)i16(r16(d+0x36)));
    uint32_t f=fa(base,fm(fs(cv(source_scaled),cv(target_scaled)),0x3d800000u));
    if(flt(f,0x42480000u)) f=0x42480000u;
    uint32_t value=fd(f,base);
    value=fm(value,cv((uint32_t)i16(r16(d+0x34))));
    value=fm(value,factor);
    uint32_t threshold=truncw(value);
    int32_t critical=i16(r16(descriptor(skill)+0x34));
    uint32_t diagnostic=truncw(f);
    ps2LibcPrintf(0x5449c0u,sx((uint32_t)critical),sx(diagnostic),sx(threshold));
    uint64_t rand=random100();
    if(!lt(rand,sx(threshold))) return 0;
    if(marked) w32(c+0x58,0x12b);
    return 1;
}
uint64_t ps2CombatAlignment_00265868(uint64_t form)
{
    uint64_t u=nbGetUnitWorkFromFormindex(form);
    uint64_t a=datGet3Zokusei(u);
    return a==UINT64_MAX?0u:(a==1?2u:1u);
}
uint64_t ps2CombatEffectCondition_002658B8(uint64_t skill,uint64_t unused,uint64_t target)
{
    (void)unused;
    uint32_t mask=r8(descriptor(skill)+0x10);
    uint64_t alignment=ps2CombatAlignment_00265868(target);
    return (mask&1u)||((mask&2u)&&alignment==0)||((mask&4u)&&alignment==1)||((mask&8u)&&alignment==2);
}
uint64_t ps2CombatEffectType_00265948(uint64_t skill,uint64_t source,uint64_t target)
{
    source=sx((uint32_t)source); /* Original incoming A1 is SW/LW, not SD/LD. */
    uint32_t c=(uint32_t)nbGetMainProcessData(),d=descriptor(skill);
    uint32_t kind=r32(d+0x30);
    /* Exact544A10 native jump table; unlisted rows reach the common body. */
    switch(kind) {
    case 1:return 7;case 2:case 3:return 6;case 4:return 8;case 5:return 9;
    case 7:return 10;case 12:return 12;case 13:return 13;case 14:return 14;
    default:break;
    }
    uint32_t su=(uint32_t)nbGetUnitWorkFromFormindex(source);
    uint32_t tu=(uint32_t)nbGetUnitWorkFromFormindex(target);
    uint32_t format=(uint32_t)nbGetDevilFormatFlag(target);
    uint32_t flags=r32(c+0x60);
    if(flags&0x40000000u) return 1;
    if(flags&0x08000000u) return 0;
    if(skill==0x9e && (flags&1u) && r32(c+0x34)!=0x408u && (r32(tu)&0x20u)) return 5;
    if(skill==0x9f && (flags&1u) && (r32(tu)&0x20u)) return 5;
    uint64_t attr=nbGetNormalSkillAttr(skill),affinity=0;
    if(attr!=UINT64_MAX && (lt(attr,12)||lt(14,attr))) {
        affinity=nbGetAisyo(skill,target,attr);
        if((r16(tu+14)&0xfffu)==2 && r8(d+2)==0)
            affinity&=~UINT64_C(0x70000);
        if(affinity&0x20000u) return 1;
        int pierce=datCheckSyojiSkill(unit(su),0x165);
        if(pierce && r8(d+2)==0) {
            if(affinity&0x50000u) w32(c+0x14c,1);
        } else {
            if(affinity&0x40000u) return 2;
            if(affinity&0x10000u) return 3;
        }
    }
    flags=r32(c+0x60);
    if((flags&0x400u) && (r32(tu)&0x20u)) {
        if(r8(d+8)==0) {
            uint32_t forms=r32(c);
            if(r32(forms+(uint32_t)target*240u+0x78)&0x1000u) return 11;
        } else if(attr!=14 && i16(r16(c+0x1a))!=1) return 5;
    }
    kind=r32(d+0x30);
    uint32_t status=r16(tu+14)&0xfffu;
    if(kind==6) { if(status!=4) return 5; }
    else if(kind==15 && status!=0x40) return 5;
    if(status==4||status==0x100||status==0x10||status==0x400||status==1||status==2) return 0;
    if(!ps2CombatEffectCondition_002658B8(skill,source,target)) { ps2LibcPrintf(0x551140u);return 5; }
    if(r8(d+0x11)==0xffu) return 0;
    uint32_t rate=fm(cv(r8(d+0x11)),r32(0x54e528));
    if(evtBitCheck(0xaf2) && r16(d+0x16)==3 && i16(r16(d+0x18))==1 && !(r32(tu)&0x20u))
        rate=fm(rate,r32(0x54e52c));
    uint32_t source_hojo=fbits(nbGetHojoRitu(source,8));
    uint32_t target_hojo=fbits(nbGetHojoRitu(target,6));
    uint32_t classification=r8(d+2),hit;
    if(classification==0) {
        (void)*(const volatile uint32_t *)at(su);
        uint32_t source_scaled=scaled_agility(su),target_scaled=scaled_agility(tu);
        hit=fa(cv(100u-(uint32_t)i16(r16(d+0x36))),fm(fs(cv(source_scaled),cv(target_scaled)),0x3d800000u));
    } else if(classification==1) {
        uint32_t base=(r32(su)&0x20u)?0x42be0000u:0x42c80000u;
        uint32_t evasion=(uint32_t)ps2UnitEvasionPower_00242D50(tu);
        uint64_t magic=ps2UnitMagicHitPower_00242CB0(su);
        uint32_t times25=(evasion<<5)-(evasion<<3)+evasion;
        if(magic==0) nocturneCompilerArithmeticTrap(7);
        uint32_t quotient=divs(times25<<2,(uint32_t)magic);
        hit=fa(fm(cv(100u-quotient),0x3f000000u),base);
    } else return 0;
    hit=fm(hit,source_hojo);hit=fm(hit,target_hojo);hit=fm(hit,rate);
    hit=cap_hit(hit);
    if(nbGetBadStat(source)==0x100) hit=fm(hit,0x3e800000u);
    uint32_t threshold=truncw(hit);
    ps2LibcPrintf(classification==0?0x5449e0u:0x5449f8u,sx(threshold));
    uint64_t rand=random100();
    if(lt(rand,sx(threshold))) return 0;
    return format&0x800u?5u:4u;
}
void ps2CombatAddHpMp_002660C0(uint64_t form,uint64_t resource,uint64_t amount)
{
    uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(form);
    if(!u) return;
    if(resource==0) (void)datAddHp(unit(u),i32((uint32_t)amount));
    else if(resource==1) (void)datAddMp(unit(u),i32((uint32_t)amount));
}
float ps2CombatHpDrainRate_00266C90(uint64_t skill)
{
    uint32_t mode=r16(descriptor(skill)+0x16);
    return fvalue(mode==12||mode==13?0x3f800000u:0);
}
float ps2CombatMpDrainRate_00266CD8(uint64_t skill)
{
    uint32_t mode=r16(descriptor(skill)+0x1a);
    return fvalue(mode==12||mode==13?0x3f800000u:0);
}
float ps2CombatReductionRate_00266D20(uint64_t skill)
{
    return fvalue(fd(cv(r16(descriptor(skill)+0x22)),0x42c80000u));
}
uint64_t ps2CombatCheckHitEffect_00267370(uint64_t effect) { return r8(0x3dbd23u+(uint32_t)effect*4u)==0; }
uint64_t ps2CombatDeadType_00267388(void) { return 0; }
uint64_t ps2CombatCheckStoneDeath_00267390(uint64_t skill,uint64_t form)
{
    uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(form);
    if(!u || nbGetBadStat(form)!=0x400) return 0;
    uint64_t attr=nbGetNormalSkillAttr(skill);
    if(attr!=0 && attr!=4) return 0;
    uint32_t luck=(uint32_t)parameter(u,5),level=r16(u+0x14);
    uint32_t denominator=fd(fa(cv(level),0x41a00000u),0x40a00000u);
    uint32_t value=fm(fd(cv(luck),denominator),(r32(u)&4u)?0x42200000u:0x41a00000u);
    uint32_t threshold=truncw(fs(0x42c80000u,value));
    if(i32(threshold)<20) threshold=20;
    ps2LibcPrintf(0x544bf8u,sx(threshold));
    return lt(random100(),sx(threshold));
}
void ps2CombatSetStatus_002674D0(uint64_t form,uint64_t set,uint64_t status)
{
    uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(form);
    if(!u) return;
    if(set==0) datResetBadStat(unit(u),(uint32_t)status);
    else set_status(u,status);
}
uint64_t ps2CombatCheckStatusRecovery_00267530(uint64_t object,uint64_t mode)
{
    if(!object) return 0;
    uint32_t u=(uint32_t)object;
    if(!(r32(u)&1u)) return 0;
    uint32_t status=r16(u+14)&0xfffu;
    if(mode==1) return status==0x10;
    if(mode==2) return status==4;
    if(mode==3) return status==1||status==2||status==4||status==8||status==0x10||status==0x80||status==0x200||status==0x400;
    if(mode!=0) return 0;
    if(status==1||status==2) return 1;
    if(status!=4&&status!=8&&status!=0x10&&status!=0x80) return 0;
    uint32_t luck=(uint32_t)parameter(u,5);
    uint32_t denominator=divs(r16(u+0x14)+20u,5u);
    uint32_t ratio=fd(cv(luck),cv(denominator));
    uint32_t factor=status==4?0x41a00000u:(status==8||status==0x10?0x41f00000u:0x42200000u);
    uint32_t threshold=truncw(fm(factor,ratio));
    ps2LibcPrintf(0x544c10u,sx(threshold));
    return lt(random100(),sx(threshold));
}
uint64_t ps2CombatCheckCurse_002677B8(uint64_t form)
{
    uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(form);
    return u?(r16(u+14)&0x8000u)!=0:0;
}
void ps2CombatAddEncounterItems_00269318(uint64_t context)
{
    uint32_t c=(uint32_t)context;
    uint32_t id=r32(c+0x34);
    if(i32(id)<=0 || datBossRashChk(i32(id))) return;
    uint32_t e=encounter(r32(c+0x34));
    uint8_t item=r8(e+2),count=r8(e+3);
    if(!item||!count) return;
    for(uint32_t i=0;i<4;i++) {
        if(r8(c+0x98+i)==item) { uint8_t old=r8(c+0x9c+i);w8(c+0x9c+i,(uint8_t)(old+count));return; }
    }
    for(uint32_t i=0;i<4;i++) {
        if(!r8(c+0x98+i)) { w8(c+0x98+i,item);w8(c+0x9c+i,count);return; }
    }
    for(uint32_t i=3;i!=0;i--) {
        uint8_t previous=r8(c+0x97+i);w8(c+0x98+i,previous);
        previous=r8(c+0x9b+i);w8(c+0x9c+i,previous);
    }
    w8(c+0x9c,count);w8(c+0x98,item);
}
void ps2CombatAddRewards_00269448(uint64_t object)
{
    uint32_t u=(uint32_t)object;
    if(r32(u)&4u) return;
    uint32_t c=(uint32_t)nbGetMainProcessData();
    int boss=datBossRashChk(i32(r32(c+0x34)));
    uint32_t d=0x3497c0u+(uint32_t)r16(u+4)*60u;
    uint32_t exp=r16(d+0x2c);
    uint32_t player=(uint32_t)datGetPlayerLevel();
    uint32_t level=r16(u+0x14),difference=player-level;
    uint32_t divisor=0;int reduced=0;
    if(level<70) {
        if(difference-6u<6u) { divisor=r32(0x54e594);reduced=1; }
        else if(i32(difference)>11) { divisor=r32(0x54e590);reduced=1; }
    } else if(i32(difference)>5) { divisor=r32(0x54e594);reduced=1; }
    if(reduced) exp=truncw(fd(cv(exp),divisor));
    uint32_t money=r16(d+0x2a);
    if(boss) { exp=divs(exp,10);money=divs(money,10); }
    uint32_t old_exp=r32(c+0xa4),old_money=r32(c+0xa0);
    w32(c+0xa4,old_exp+exp);w32(c+0xa0,old_money+money);
    if(boss) return;
    uint8_t item=0;
    uint32_t event=r16(d+0x32);
    if(event==0 || evtBitCheck((int32_t)event)) {
        if(r8(d+0x34)!=0) {
            uint64_t draw=random100();uint32_t chance=r8(d+0x35);
            if(lt(draw,chance)) item=r8(d+0x34);
        }
    }
    if(!item) {
        for(uint32_t i=0;i<2;i++) {
            if(r8(d+0x2e+i)!=0) {
                uint64_t draw=random100();uint32_t chance=r8(d+0x30+i);
                if(lt(draw,chance)) item=r8(d+0x2e+i);
            }
            if(item) break;
        }
    }
    uint64_t draw=random100();uint32_t chance=r8(d+0x36);
    if(lt(draw,chance)&&!item) item=4;
    draw=random100();chance=r8(d+0x37);
    if(lt(draw,chance)&&!item) item=3;
    if(!item) return;
    for(uint32_t i=0;i<4;i++) {
        if(r8(c+0x98+i)==item) { uint8_t n=r8(c+0x9c+i);w8(c+0x9c+i,(uint8_t)(n+1u));return; }
    }
    for(uint32_t i=0;i<4;i++) {
        if(!r8(c+0x98+i)) { w8(c+0x98+i,item);w8(c+0x9c+i,1);return; }
    }
}
uint64_t ps2CombatLevelAverage_002697D8(uint64_t context,uint64_t enemy)
{
    uint32_t sum=0,count=0;
    if(enemy==0) {
        uint32_t base=global()+0xa54u;
        for(uint32_t i=0;i<16;i++,base+=0xec) {
            if((r32(base)&3u)==3u) { sum+=r16(base+0x14);count++; }
        }
    } else {
        uint32_t list=encounter(r32((uint32_t)context+0x34))+6;
        for(uint32_t i=0;i<11;i++,list+=2) {
            uint32_t id=r16(list);
            if(id) { sum+=r8(0x3497c5u+id*60u);count++; }
        }
    }
    return count?sx(divs(sum,count)):0;
}
uint64_t ps2CombatParameterAverage_002698C0(uint64_t context,uint64_t enemy,uint64_t index)
{
    uint32_t c=(uint32_t)context,sum=0,count=0;
    for(uint32_t i=0;i<14;i++) {
        uint32_t p=r32(c+0x10)+i*128u;
        uint32_t flags=r16(p);
        if(!(flags&1u)||(flags&4u)) continue;
        if(enemy==0?(flags&2u)!=0:(flags&2u)==0) continue;
        uint32_t u=(uint32_t)nbGetUnitWorkPointer(context,p);
        sum+=(uint32_t)parameter(u,index);count++;
    }
    return count?sx(divs(sum,count)):0;
}
uint64_t ps2CombatEncounterParameterAverage_002699B0(uint64_t context,uint64_t enemy,uint64_t index)
{
    uint32_t sum=0,count=0;
    if(enemy==0) {
        for(uint32_t i=0;i<16;i++) {
            uint32_t u=global()+0xa54u+i*0xecu;
            if((r32(u)&3u)==3u) { sum+=(uint32_t)parameter(u,index);count++; }
        }
    } else {
        uint32_t list=encounter(r32((uint32_t)context+0x34))+6;
        for(uint32_t i=0;i<11;i++,list+=2) {
            uint32_t id=r16(list);
            if(id) { sum+=(uint32_t)i8(r8(0x3497d0u+id*60u+(uint32_t)index));count++; }
        }
    }
    return count?sx(divs(sum,count)):0;
}
uint64_t ps2CombatCheckPlayerInitiative_00269AD8(uint64_t context)
{
    uint32_t c=(uint32_t)context,coeff[6];
    /* Three original LDL/LDR pairs cache all six coefficients before calls. */
    uint64_t a=r64(0x544d58),b=r64(0x544d60),d=r64(0x544d68);
    coeff[0]=(uint32_t)a;coeff[1]=(uint32_t)(a>>32);coeff[2]=(uint32_t)b;
    coeff[3]=(uint32_t)(b>>32);coeff[4]=(uint32_t)d;coeff[5]=(uint32_t)(d>>32);
    uint32_t flags=r16(encounter(r32(c+0x34))+0x20);
    if(flags&4u) return 0;
    if(flags&2u) return 1;
    uint32_t enemy_level=(uint32_t)ps2CombatLevelAverage_002697D8(context,1);
    uint32_t enemy_agility=(uint32_t)ps2CombatEncounterParameterAverage_002699B0(context,1,4);
    uint32_t enemy_luck=(uint32_t)ps2CombatEncounterParameterAverage_002699B0(context,1,5);
    uint32_t player=global()+0xa54u;
    uint32_t player_level=r16(player+0x14);
    uint32_t agility=(uint32_t)parameter(player,4),luck=(uint32_t)parameter(player,5);
    uint32_t player_score=player_level+asr(luck+(luck>>31),1)+agility;
    uint32_t enemy_score=enemy_level+asr(enemy_luck+(enemy_luck>>31),1)+enemy_agility;
    uint32_t score=player_score-enemy_score+72u;
    if(i32(score)<70) score=70;
    if(i32(score)>85) score=85;
    uint32_t index=r8(0x3badfcu+pack(c));
    if(i32(player_level)<i32(enemy_level+15u)) {
        /* Native other indexes read private/save RAM, outside this algorithm
         * layer's backed coefficient domain. Reject, never invent a factor. */
        if(index>=6) abort();
        score=truncw(fm(cv(score),coeff[index]));
    }
    uint64_t draw=sx(sdfGetRandInt(NULL,128));
    ps2LibcPrintf(0x544d70u,sx(player_level),sx(enemy_level),sx(index),sx(score),draw);
    if(lt(draw,sx(score))) return 0;
    if(evtBitCheck(0xaf2) && (sdfGetRandInt(NULL,128)&1u)) return 0;
    return 1;
}
uint64_t ps2CombatCheckEnemyInitiative_00269D20(uint64_t context)
{
    uint32_t c=(uint32_t)context;
    int32_t type=i8(r8(encounter(r32(c+0x34))));
    if(type==-1) return 0;
    if(type==1) return 1;
    uint32_t enemy_level=(uint32_t)ps2CombatLevelAverage_002697D8(context,1);
    uint32_t enemy_agility=(uint32_t)ps2CombatEncounterParameterAverage_002699B0(context,1,4);
    uint32_t enemy_luck=(uint32_t)ps2CombatEncounterParameterAverage_002699B0(context,1,5);
    uint32_t player=global()+0xa54u;
    uint32_t player_level=r16(player+0x14);
    uint32_t agility=(uint32_t)parameter(player,4),luck=(uint32_t)parameter(player,5);
    uint64_t draw=random100();
    uint32_t enemy_score=enemy_level+asr(enemy_luck+(enemy_luck>>31),1)+enemy_agility+10u;
    uint32_t player_score=player_level+asr(luck+(luck>>31),1)+agility+10u;
    uint32_t threshold=12;
    if(datCheckSkillInParty(0x12a)) {
        uint32_t divisor=(uint32_t)i16(r16(0x3dc1f0));
        threshold=divs(12,divisor); /* Native DIV precedes BEQL/BREAK7. */
        if(divisor==0) nocturneCompilerArithmeticTrap(7);
    }
    ps2LibcPrintf(0x544da8u,sx(player_score),sx(enemy_score),sx(threshold),draw);
    return lt(draw,sx(threshold));
}
uint64_t ps2CombatCheckEscape_00269E98(uint64_t context)
{
    uint32_t c=(uint32_t)context;
    if(r16(encounter(r32(c+0x34))+0x20)&0x20u) return 1;
    int active=0;
    for(uint32_t i=4;i<14;i++) {
        uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(i);
        if(!u) continue;
        uint32_t status=r16(u+14)&0xfffu;
        if(status!=1&&status!=2&&status!=4&&status!=0x10&&status!=0x100&&status!=0x400) active=1;
    }
    if(!active) return 1;
    uint32_t p4=(uint32_t)ps2CombatParameterAverage_002698C0(context,0,4);
    uint32_t p5=(uint32_t)ps2CombatParameterAverage_002698C0(context,0,5);
    uint32_t e4=(uint32_t)ps2CombatParameterAverage_002698C0(context,1,4);
    uint32_t e5=(uint32_t)ps2CombatParameterAverage_002698C0(context,1,5);
    uint32_t rate=fm(fd(cv(p4+p5),cv(e4+e5)),0x41a00000u);
    uint32_t score=truncw(fa(cv((uint32_t)r8(c+0x6b)*20u),rate));
    if(datCheckSkillInParty(0x128)) score=divs(mul(score,(uint32_t)i16(r16(0x3dc1e0))),100);
    uint32_t event=evtBitCheck(0xaf2);
    score<<=1;
    if(!event) return 0;
    ps2LibcPrintf(0x544de0u,sx(score));
    uint64_t draw=random100();
    if(lt(sx(score),draw)) return 0;
    if(evtGetAgeOfMoon()!=8) return 1;
    if(sdfGetRandInt(NULL,4)==1) return 1;
    if(evtBitCheck(0xaf2) && (sdfGetRandInt(NULL,2)&1u)) return 1;
    return 0;
}
uint64_t ps2CombatCheckConsecutiveEncounter_0026A158(uint64_t context)
{
    uint32_t c=(uint32_t)context;
    if(r16(encounter(r32(c+0x34))+0x20)&0x10u) {
        w32(c+0x34,0x149);w32(c+0x30,1);
        ps2CombatSetEncounter_00259658(sx(r32(c+0x34)));return 1;
    }
    if(i32(r32(c+0x28))<=0) return 0;
    uint32_t off=pack(c);
    uint32_t chance=r8(0x3badfdu+off),target=r16(0x3badfeu+off);
    if(r32(global()+0xa4c)&2u) chance*=5u;
    ps2LibcPrintf(0x544df0u,sx(chance),sx(target));
    if(!lt(random100(),sx(chance))) return 0;
    uint32_t area=r32(c+0x28),zone=r32(c+0x2c);
    w32(c+0x30,target);
    uint32_t id=r16(0x3badf8u+target*8u+area*420u+zone*100u);
    w32(c+0x34,id);ps2CombatSetEncounter_00259658(sx(r32(c+0x34)));return 1;
}
uint64_t ps2CombatSingleTargetSkill_0026A448(uint64_t skill) { return r8(descriptor(skill)+8)==0; }
uint64_t ps2CombatSameFormation_0026A470(uint64_t first,uint64_t second)
{
    uint64_t side=nbCheckFormationPlayerSide(first);
    return side==nbCheckFormationPlayerSide(second);
}
uint64_t ps2CombatScatteredMoney_0026A4B0(uint64_t object)
{
    uint32_t u=(uint32_t)object;
    uint32_t g=global();
    uint32_t cash=fd(cv(r32(g+0xa48)),0x41a00000u),base;
    if(r32(u)&0x20u) {
        uint32_t player=g+0xa54u,level=r16(player+0x14);
        uint32_t denominator=fa(fd(cv(level),0x40a00000u),0x40800000u);
        uint32_t luck=(uint32_t)parameter(player,5);
        uint32_t ratio=fd(cv(luck),denominator);
        uint32_t id=r16(u+4),money=r16(0x3497eau+id*60u);
        base=truncw(fm(cv(money),ratio));
    } else {
        uint32_t level=r16(u+0x14);
        uint32_t denominator=fa(fd(cv(level),0x40a00000u),0x40800000u);
        uint32_t luck=(uint32_t)parameter(u,5);
        uint32_t ratio=fd(cv(luck),denominator);
        uint32_t epsilon=r32(0x54e598);
        base=EE_FPU_COMPARE_S(epsilon,ratio&0x7fffffffu,2)?truncw(fd(cash,ratio)):0;
    }
    uint32_t draw=fbits(sdfGetRandFloat(NULL)),scale=r32(0x54e59c);
    uint32_t f=fs(draw,0x3f000000u);f=fa(f,f);f=fm(f,scale);
    uint32_t basef=cv(base);f=fm(basef,f);f=fa(basef,f);
    uint32_t value=truncw(f);
    uint32_t event=evtBitCheck(0xaf2);
    if(event && !(r32(u)&0x20u)) value=divs(value,10);
    return i32(value)>0?sx(value):1;
}
uint64_t ps2CombatCheckPanicAction_0026A688(uint64_t object)
{
    uint32_t flags=r32((uint32_t)object),threshold=30;
    if(!(flags&4u) && (flags&0x20u)) threshold=10;
    return !lt(random100(),threshold);
}
uint64_t ps2CombatCheckStatusGameOver_0026A6D8(void)
{
    for(uint32_t i=0;i<4;i++) {
        uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(i);
        if(u && (r16(u+14)&0xfffu)!=0x400u) return 0;
    }
    return 1;
}
void ps2CombatSetHpModelScale_0026A740(uint64_t object)
{
    uint32_t p=(uint32_t)object;
    uint32_t u=(uint32_t)nbGetUnitWorkFromFormindex(sx((uint32_t)i16(r16(p+0x92))));
    if(!u) return;
    uint32_t hp=r16(u+6);
    if(!hp) return;
    uint32_t ratio=fd(cv(hp),cv(r16(u+8)));
    uint32_t model=(uint32_t)ps2CombatModelScaleDescriptor_00259A60(u);
    uint32_t base=r32(model+0x18);
    uint32_t value=fa(fm(fs(base,0x3f000000u),ratio),0x3f000000u);
    w32(p+0x5c,value);
}
float ps2CombatCriticalPower_0026A828(uint64_t source,float power)
{
    (void)source; /* Native SLTI's scalar result is dead, no memory effects. */
    return fvalue(fm(fbits(power),0x3fc00000u));
}
uint64_t ps2CombatEarnedExperience_0026A840(uint64_t context)
{
    uint32_t c=(uint32_t)context,id=r32(c+0x34),v=r32(c+0xa4);
    if((id==0x10bu||id==0x11cu)&&i32(v)>20000) v=20000;
    return sx(v);
}
uint64_t ps2CombatEarnedMoney_0026A870(uint64_t context)
{
    uint32_t c=(uint32_t)context,id=r32(c+0x34),v=r32(c+0xa0);
    if((id==0x10bu||id==0x11cu)&&i32(v)>10000) v=10000;
    return sx(v);
}
void ps2CombatSetEncounter_00259658(uint64_t id)
{
    uint32_t c=(uint32_t)nbGetMainProcessData();
    w32(c+0x34,(uint32_t)id);
    uint32_t flags=r8(encounter((uint32_t)id)+4);
    w16(c+0x56,0xffff);w32(c+0x38,flags);w8(c+0x6b,0);w32(c+0x44,0);
    w16(c+0x1c,0xffff);w8(c+0x54,0xff);w16(c+0x58,0);w16(c+0x5a,0);w16(c+0x5c,0);
    w8(c+0x68,0);w8(c+0x6a,0);
}
uint64_t ps2CombatModelScaleDescriptor_00259A60(uint64_t object)
{
    uint64_t id=nbGetUnitID(object);
    return id?sx(0x34f1e0u+(uint32_t)id*0x310u):sx(0x3494b0u);
}

/* SLUS_209.11 unit/stock/progression algorithms, original26 complete bodies.
 * Native instructions decide fixed-width arithmetic, raw64 branches and live
 * read/store order. HD names and community table definitions supply context,
 * not substituted managed layouts or formulas. Like field_skill.c, this is a
 * readable algorithm unit: CPU/FPR/HI/LO bank and guest save-frame transport
 * are separate obligations, not inferred from ordinary C execution. */
#include "unit_progression.h"
#include "nocturne.h"
#include "battle_targeting.h"
#include "battle_action_status.h"
#include "rst_stats.h"
#include "exp.h"
#include "ps2_memory.h"
#include "script_construction.h"
#include "libc_printf.h"
#include "compiler_numeric.h"
#include <stdlib.h>
#include <string.h>

static uint8_t *address(uint32_t guest)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveUnitProgressionAddress(guest);
#else
    return (uint8_t *)(uintptr_t)guest;
#endif
}
static uint16_t read16(uint32_t a) { uint16_t v; memcpy(&v,address(a),2); return v; }
static uint32_t read32(uint32_t a) { uint32_t v; memcpy(&v,address(a),4); return v; }
static void write16(uint32_t a,uint16_t v) { memcpy(address(a),&v,2); }
static void write32(uint32_t a,uint32_t v) { memcpy(address(a),&v,4); }
static int32_t signed_byte(uint8_t v) { return v<128u?(int32_t)v:(int32_t)v-256; }
static int32_t signed_half(uint16_t v) { return v<32768u?(int32_t)v:(int32_t)v-65536; }
static int32_t signed_word(uint32_t v)
{
    return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);
}
static uint64_t sign_extend(uint32_t v)
{
    return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;
}
static int negative64(uint64_t v) { return (v>>63)!=0; }
static uint32_t shift_right_signed(uint32_t v,unsigned n)
{
    return (v>>n)|((v&0x80000000u)?UINT32_MAX<<(32u-n):0);
}
static uint32_t signed_quotient(uint32_t numerator,uint32_t denominator)
{
    int64_t n=signed_word(numerator),d=signed_word(denominator);
    /* Actual DIV/DIV1 quotient, including zero and INT_MIN/-1. No host
     * divide-by-zero or signed-overflow expression is evaluated. */
    if(d==0) return n<0?1u:UINT32_MAX;
    return (uint32_t)(n/d);
}
static uint32_t multiply_word(uint32_t a,uint32_t b)
{
    return (uint32_t)((int64_t)signed_word(a)*(int64_t)signed_word(b));
}
static uint32_t global_work(void) { return read32(0x0054ea20u); }
static datUnitWork_PS2 *unit_at(uint32_t a) { return (datUnitWork_PS2 *)address(a); }

/* Raw-ABI adapter for the already registered00243F40. Its existing typed
 * uint32 skill interface represents the entire canonical range, so use that
 * real callee there. A high64 argument cannot pass through that interface:
 * execute the actual native list traversal, including every failed LHU/full64
 * BEQ comparison, rather than truncating the skill or supplying a false result.
 * This is an existing-body ABI extension, not a new recovered identity. */
static int owns_skill_raw(uint32_t unit,uint64_t skill)
{
    if(skill<=UINT32_MAX) return datCheckSyojiSkill(unit_at(unit),(uint32_t)skill);
    uint32_t list,count;
    if(read32(unit)&0x20u) {
        uint32_t id=read16(unit+4);
        list=0x3497d6u+id*60u;
        count=8;
    } else {
        count=read16(unit+0x38);
        list=unit+0x3a;
    }
    for(uint32_t i=0;i<count;i++,list+=2) {
        /* The raw high argument can never equal an LHU value. Retain the
         * actual aligned RAM read, not only an optimizer-proved false test. */
        uint16_t current=*(const volatile uint16_t *)address(list);
        if((uint64_t)current==skill) return 1;
    }
    return 0;
}

/* 00240A98. HP's zero-max trap precedes the MP loads. The secondary DIV1
 * has no corresponding trap; preserve its real zero-divisor result. */
void ps2UnitRecalculateMaxHpMp_00240A98(uint64_t unit)
{
    uint32_t u=(uint32_t)unit;
    uint32_t old_max_hp=read16(u+8),old_hp=read16(u+6);
    if(old_max_hp==0) nocturneCompilerArithmeticTrap(7); /* Actual BREAK7. */
    uint32_t old_mp=read16(u+10),old_max_mp=read16(u+12);
    uint32_t hp_ratio=signed_quotient(old_hp<<10,old_max_hp);
    uint32_t mp_ratio=signed_quotient(old_mp<<10,old_max_mp);
    write16(u+8,(uint16_t)datGetMaxHp(unit_at(u)));
    uint32_t max_mp=datGetMaxMp(unit_at(u));
    uint32_t max_hp=read16(u+8);
    write16(u+12,(uint16_t)max_mp);
    uint32_t hp=multiply_word(max_hp,hp_ratio);
    uint32_t mp=multiply_word(max_mp&0xffffu,mp_ratio);
    if(hp&0x80000000u) hp+=0x3ffu;
    if(mp&0x80000000u) mp+=0x3ffu;
    write16(u+10,(uint16_t)shift_right_signed(mp,10));
    write16(u+6,(uint16_t)shift_right_signed(hp,10));
}

/* 00242CB0. ADDIU/ADDU/SLL are word operations; the signed divide-by2
 * bias uses the already wrapped (parameter5+5) value. */
uint64_t ps2UnitMagicHitPower_00242CB0(uint64_t unit)
{
    uint32_t u=(uint32_t)unit;
    uint32_t magic=(uint32_t)datGetParam(unit_at(u),2);
    uint32_t luck=(uint32_t)datGetParam(unit_at(u),5)+5u;
    uint32_t level=read16(u+0x14);
    luck=shift_right_signed(luck+(luck>>31),1);
    return sign_extend((magic<<1)+level+luck+15u);
}

/* 00242D50. Keep the original software-double conversion/multiply/add chain;
 * a managed rearrangement or host double expression is not equivalent. */
uint64_t ps2UnitEvasionPower_00242D50(uint64_t unit)
{
    uint32_t u=(uint32_t)unit;
    uint32_t agility=(uint32_t)datGetParam(unit_at(u),4);
    uint32_t luck=(uint32_t)datGetParam(unit_at(u),5);
    uint64_t value=ps2SoftDoubleFromInt(signed_word(agility+5u));
    value=ps2SoftDoubleMul(value,UINT64_C(0x3ff8000000000000));
    uint64_t other=ps2SoftDoubleFromInt(signed_word(luck+5u));
    value=ps2SoftDoubleAdd(value,other);
    other=ps2SoftDoubleFromInt((int32_t)read16(u+0x14)+5);
    value=ps2SoftDoubleAdd(value,other);
    return sign_extend((uint32_t)ps2SoftDoubleToInt(value));
}

uint64_t ps2UnitAffinityFlags_00244098(uint64_t unit,uint64_t attribute)
{
    /* LUI FFFF produces a sign-extended64 mask, not 00000000FFFF0000. */
    return datGetAisyo(unit,attribute)&UINT64_C(0xffffffffffff0000);
}

void ps2UnitAddMakaPercent_00244268(uint64_t percent)
{
    uint32_t g=global_work(),maka=read32(g+0xa48);
    int subtract=negative64(percent);
    uint32_t magnitude=subtract?0u-(uint32_t)percent:(uint32_t)percent;
    uint32_t change=signed_quotient(multiply_word(maka,magnitude),100);
    uint32_t result=subtract?maka-change:maka+change;
    if(result&0x80000000u) result=0;
    if(result>9999999u) result=9999999u;
    write32(g+0xa48,result);
}

uint64_t ps2UnitPlayerParameter_002445C0(uint64_t parameter)
{
    uint32_t g=global_work();
    uint8_t equipped=*address(g+0x1cfa);
    int32_t value=signed_byte(*address(g+(uint32_t)parameter+0xa6a));
    int32_t extra=0;
    if(equipped) extra=cmbGetHeartsParam((int8_t)signed_byte(equipped),
        (int8_t)signed_byte((uint8_t)parameter));
    return sign_extend((uint32_t)value-(uint32_t)extra);
}

void ps2UnitAddPlayerParameter_00244610(uint64_t parameter,uint64_t amount)
{
    uint32_t a=global_work()+(uint32_t)parameter+0xa6a;
    uint32_t value=(uint32_t)signed_byte(*address(a))+(uint32_t)amount;
    if(signed_word(value)>=41) value=40;
    *address(a)=(uint8_t)value;
    ps2UnitRecalculateMaxHpMp_00240A98(sign_extend(global_work()+0xa54));
    uint32_t g=global_work();
    uint16_t hp=read16(g+0xa5c),mp=read16(g+0xa60);
    write16(g+0xa5a,hp);
    write16(g+0xa5e,mp);
}

uint64_t ps2UnitCompanionParameter_00244668(uint64_t species,uint64_t parameter)
{
    uint32_t g=global_work(),id=g+0xb44,p=g+(uint32_t)parameter+0xb56;
    uint32_t value=0;
    /* Slots1..15, no occupied test and no early break: LAST duplicate wins. */
    for(unsigned i=0;i<15;i++,id+=0xec,p+=0xec)
        if((uint64_t)read16(id)==species) value=(uint32_t)signed_byte(*address(p));
    return sign_extend(value);
}

uint64_t ps2UnitPlayerAlignment_002446B0(void)
{
    uint32_t race=cmbGetPlayerRaceID(unit_at(global_work()+0xa54));
    return race?sign_extend((uint32_t)(signed_word(race-1u)%3)):1;
}

void ps2UnitKillCompanion_002446F8(uint64_t species)
{
    for(uint32_t offset=0xec;offset<=15u*0xec;offset+=0xec) {
        uint32_t g=global_work(),slot=offset+0xa50,a=g+slot;
        if(!(read32(a+4)&1u) || (uint64_t)read16(a+8)!=species) continue;
        if(read16(a+10)) {
            write16(a+10,0);
            datSetBadStat(unit_at(g+offset+0xa54),0x800);
            g=global_work();
        }
        uint32_t flags_at=g+slot+4,flags=read32(flags_at);
        if(flags&2u) write32(flags_at,flags&~2u);
    }
}

void ps2UnitInitializeCompanion_00244EF8(uint64_t species,uint64_t unit)
{
    uint32_t id=(uint32_t)species,u=(uint32_t)unit;
    (void)ps2Memset(address(u),0,0xec);
    uint32_t descriptor=0x3497c0u+id*60u;
    write32(u,1);
    write16(u+4,(uint16_t)species);
    uint8_t level=*address(descriptor+5);
    write32(u+0x10,0);
    write16(u+0x14,level);
    for(uint32_t i=0;i<6;i++) {
        uint8_t parameter=*address(descriptor+0x10+i);
        *address(u+0x16+i)=parameter;
    }
    uint32_t skill=0x333cf8u+id*102u,out=u+0x3a,count=0;
    for(unsigned i=0;i<24;i++,skill+=4) {
        if(*address(skill+6)!=0) continue;
        if(*address(skill+7)!=1) continue;
        uint16_t number=read16(skill+8);
        ++count;
        write16(out,number);
        out+=2;
    }
    uint32_t hp=datGetMaxHp(unit_at(u));
    write16(u+6,(uint16_t)hp);
    write16(u+8,(uint16_t)hp);
    uint32_t mp=datGetMaxMp(unit_at(u));
    write16(u+0x38,(uint16_t)count);
    write16(u+10,(uint16_t)mp);
    write16(u+12,(uint16_t)mp);
}

uint64_t ps2UnitAddCompanion_00245020(uint64_t species,uint64_t join_party)
{
    int register_compendium=!negative64(species);
    if(!register_compendium) species&=UINT64_C(0x7fffffff);
    uint32_t g=global_work(),party_count=0;
    for(uint32_t i=0;i<16;i++) {
        uint32_t flags=read32(g+0xa54+i*0xec);
        if((flags&3u)==3u) ++party_count;
    }
    uint32_t limit=read32(g+0xa50),slot=0;
    if(signed_word(limit)>0) {
        uint32_t a=g+0xe04;
        do {
            if(!(read32(a)&1u)) break;
            ++slot;
            a+=0xec;
        } while(signed_word(slot)<signed_word(limit));
    }
    if(sign_extend(slot)==sign_extend(read32(g+0xa50))) return UINT64_MAX;
    uint32_t offset=slot*0xecu;
    ps2UnitInitializeCompanion_00244EF8(species,sign_extend(g+offset+0xe04));
    if(register_compendium) (void)fclEncycRegist(unit_at(global_work()+offset+0xe04),0);
    if(join_party!=0 && party_count<4) {
        uint32_t a=global_work()+offset+0xe04;
        write32(a,read32(a)|2u);
    }
    g=global_work();
    uint32_t result=slot+4u,index=read32(g+0x1924);
    *address(g+index+0x1914)=(uint8_t)result;
    g=global_work();
    index=read32(g+0x1924);
    write32(g+0x1924,index+1u);
    return sign_extend(result);
}

void ps2UnitAddUniqueCompanion_00245180(uint64_t species,uint64_t join_party,uint64_t unique_id)
{
    uint32_t slot=(uint32_t)ps2UnitAddCompanion_00245020(species,join_party);
    uint32_t base=global_work()+slot*0xecu,flags_at=base+0xa54;
    uint32_t flags=read32(flags_at);
    /* No failure guard in the original. Result-1 writes global+968/+98A. */
    write16(base+0xa76,(uint16_t)unique_id);
    write32(flags_at,flags|0x400u);
    if(unique_id==1) write32(flags_at,flags|0x1400u);
}

uint64_t ps2UnitFindUniqueCompanion_002451F0(uint64_t unique_id)
{
    uint32_t g=global_work(),flags_at=g+0xa54,id_at=g+0xa76;
    for(uint32_t i=0;i<16;i++,flags_at+=0xec,id_at+=0xec) {
        uint32_t flags=read32(flags_at);
        if((flags&1u) && !(flags&4u) && (flags&0x400u)
            && (uint64_t)read16(id_at)==unique_id) return i;
    }
    return UINT64_MAX;
}

void ps2UnitAddExperience_002452B8(uint64_t unit,uint64_t experience)
{
    uint32_t a=(uint32_t)unit+0x10;
    write32(a,read32(a)+(uint32_t)experience);
}

void ps2UnitMagatamaEquipHook_00221550(void) { /* Native JR RA / NOP. */ }
void ps2UnitMagatamaUnequipHook_00221558(void) { /* Native JR RA / NOP. */ }

void ps2UnitRemoveMagatama_00245380(void)
{
    uint32_t g=global_work(),u=g+0xa54;
    if(!*address(g+0x1d7b)) return;
    cmbSubHeartsParam(*address(g+0x1cfa),unit_at(u));
    /* The following real empty call consumes no supplied register slots. */
    ps2UnitMagatamaUnequipHook_00221558();
    g=global_work();
    *address(g+0x1cfa)=0;
    ps2UnitRecalculateMaxHpMp_00240A98(sign_extend(u));
}

void ps2UnitEquipMagatama_002453E8(uint64_t id)
{
    uint32_t g=global_work(),u=g+0xa54;
    if(!*address(g+0x1d7b) || (uint64_t)*address(g+0x1cfa)==id) return;
    ps2UnitRemoveMagatama_00245380();
    g=global_work();
    *address(g+0x1cfa)=(uint8_t)id;
    g=global_work();
    ps2HeartsAddParam(*address(g+0x1cfa),unit_at(u));
    ps2UnitMagatamaEquipHook_00221550();
    ps2UnitRecalculateMaxHpMp_00240A98(sign_extend(u));
}

void ps2UnitApplyRecoverySkill_00245478(uint64_t unit,uint64_t skill)
{
    uint32_t u=(uint32_t)unit;
    if(!owns_skill_raw(u,skill)) return;
    uint32_t a=0x3db8a0u+(uint32_t)skill*8u;
    int32_t first=signed_half(read16(a)),second=signed_half(read16(a+2));
    uint32_t hp=0,mp=0,index=(uint32_t)skill-0x15au;
    if(index<5) {
        /* Original table543140: HP,MP,both,HP,MP. These are native cases,
         * not HD passive-record offsets. Divisors are signed LH values. */
        if(index==0 || index==2 || index==3)
            if(first>0) hp=signed_quotient(read16(u+8),(uint32_t)first);
        if(index==1 || index==4) {
            if(first>0) mp=signed_quotient(read16(u+12),(uint32_t)first);
        } else if(index==2 && second>0) mp=signed_quotient(read16(u+12),(uint32_t)second);
    }
    if(signed_word(hp)>0) (void)datAddHp(unit_at(u),signed_word(hp));
    if(signed_word(mp)>0) (void)datAddMp(unit_at(u),signed_word(mp));
}

void ps2UnitRecoverFieldParty_002455B8(void)
{
    for(uint32_t offset=0;offset<16u*0xec;offset+=0xec) {
        uint32_t u=global_work()+offset+0xa54,flags=read32(u);
        if((flags&3u)==3u) {
            ps2UnitApplyRecoverySkill_00245478(sign_extend(u),0x15d);
            ps2UnitApplyRecoverySkill_00245478(sign_extend(u),0x15e);
        }
    }
}

uint64_t ps2UnitFindTreasureSkillOwner_002456D0(void)
{
    uint32_t event=read32(0x3dc920);
    if(event && !evtBitCheck(signed_word(event))) return 0;
    for(uint32_t offset=0;offset<16u*0xec;offset+=0xec) {
        uint32_t u=global_work()+offset+0xa54,flags=read32(u);
        if((flags&3u)!=3u) continue;
        uint32_t luck=(uint32_t)signed_byte(*address(u+0x1b));
        uint32_t threshold=signed_quotient(luck<<7,100);
        if(!datCheckSyojiSkill(unit_at(u),0x161)) continue;
        uint32_t random=sdfGetRandInt(NULL,32);
        uint16_t id=read16(u+4);
        /* Actual disabled diagnostic call, including its native arguments. */
        ps2ScriptDiagnosticDisabled(0x543158,(uint64_t)id,sign_extend(threshold),sign_extend(random));
        if(signed_word(threshold)>=signed_word(random)) return read16(u+4);
    }
    return 0;
}

void ps2UnitClearPartyCommandMemory_00245808(void)
{
    for(uint32_t offset=0;offset<16u*0xec;offset+=0xec)
        datClearCommMemory(sign_extend(global_work()+offset+0xa54));
}

void ps2UnitAddReasonPoints_00245890(uint64_t reason,uint64_t amount)
{
    if(reason==0) return;
    uint32_t a=global_work()+(uint32_t)reason+0x1cec;
    uint32_t value=(uint32_t)*address(a)+(uint32_t)amount;
    if(value&0x80000000u) value=0;
    if(value>128u) value=128;
    *address(a)=(uint8_t)value;
}

uint64_t ps2UnitReasonRank_002458D0(uint64_t rank)
{
    uint32_t order[3]={1,2,3};
    for(unsigned i=0;i<2;i++) {
        for(unsigned j=i+1;j<3;j++) {
            uint32_t g=global_work(),right=order[j],left=order[i];
            uint8_t right_points=*address(g+right+0x1cec);
            uint8_t left_points=*address(g+left+0x1cec);
            if(right_points<left_points) continue;
            if(left_points==right_points) {
                if(signed_word(sdfGetRandInt(NULL,100))<50) continue;
                right=order[j];left=order[i];
            }
            order[i]=right;
            order[j]=left;
        }
    }
    /* Normal caller ranks0..2. Other word indexes address private/save-area
     * RAM in the native64-byte frame; no fabricated fourth rank is returned. */
    uint32_t index=(uint32_t)rank;
    if(index>=3) abort();
    return sign_extend(order[index]);
}

void ps2UnitRefreshCompanion_00245D30(uint64_t species,uint64_t unit)
{
    uint32_t id=(uint32_t)species,u=(uint32_t)unit,descriptor=0x3497c0u+id*60u;
    uint8_t level=*address(descriptor+5);
    write16(u+0x14,level);
    for(uint32_t i=0;i<6;i++) {
        uint8_t parameter=*address(descriptor+0x10+i);
        *address(u+0x16+i)=parameter;
    }
    uint32_t skill=0x333cf8u+id*102u,out=u+0x3a,count=0;
    for(unsigned i=0;i<24;i++,skill+=4) {
        if(*address(skill+6)!=0) continue;
        if(*address(skill+7)!=1) continue;
        uint16_t number=read16(skill+8);
        ++count;
        write16(out,number);
        out+=2;
    }
    uint32_t hp=datGetMaxHp(unit_at(u));
    write16(u+6,(uint16_t)hp);
    write16(u+8,(uint16_t)hp);
    uint32_t mp=datGetMaxMp(unit_at(u));
    write16(u+0x38,(uint16_t)count);
    uint16_t current_level=read16(u+0x14);
    write16(u+10,(uint16_t)mp);
    write16(u+12,(uint16_t)mp);
    (void)ps2LibcPrintf(0x543188,(uint64_t)current_level);
    uint32_t experience=cmbCalcLevelUpExp(unit_at(u),(int32_t)read16(u+0x14));
    write32(u+0x10,experience);
    (void)ps2LibcPrintf(0x543198,sign_extend(experience));
    (void)fclEncycRegist(unit_at(u),0);
}

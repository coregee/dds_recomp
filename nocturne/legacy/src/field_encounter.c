/* Original Nocturne field-encounter decisions. Unity nbEncount supplies role
 * leads; original instructions establish the table layout, widths and order. */
#include "field_encounter.h"
#include "nocturne.h"
#include "battle_work_access.h"
#include "libc_printf.h"
#include "ee_fpu.h"
#include "script_compare.h"
#include <string.h>

static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveFieldEncounterAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (v&0x80000000u)?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t i32(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t asr(uint32_t v,unsigned n){return(v>>n)|((v&0x80000000u)?UINT32_MAX<<(32u-n):0);}
static uint32_t work(void){return r32(0x54ea20u);}
static uint32_t pack_at(uint64_t p){return 0x3bade0u+(uint32_t)p*420u;}
static uint32_t encounter_at(uint64_t e){return 0x3aefe0u+(uint32_t)e*38u;}
static uint32_t random_int(uint32_t limit){return sdfGetRandInt(NULL,limit);}

uint64_t ps2FieldEncounterCondition_0028C9F0(uint64_t pack)
{
    uint32_t p=pack_at(pack),mask=r16(p+6u);
    if(mask&&((mask>>(evtGetAgeOfMoon()&31u))&1u))return r16(p+8u);
    uint32_t event=r16(p+10u),a=event?evtBitCheck((int)event):0u;
    event=r16(p+12u);
    uint32_t b=event?evtBitCheck((int)event):0u;
    return *at(p+14u+(a?1u:0u)+(b?2u:0u));
}

uint64_t ps2FieldEncounterThreshold_0028CB68(uint64_t pack)
{
    if(!pack)return 0;
    uint32_t c=(uint32_t)ps2FieldEncounterCondition_0028C9F0(pack);
    uint32_t p=pack_at(pack)+c*100u,total=0;
    for(uint32_t j=0;j<12u;j++)total+=r16(p+0x1au+j*8u);
    if(!total)return 0;
    uint32_t cached=r32(0x551520u);
    if(i32(cached)>0)return sx(cached);
    uint32_t product=r32(p+0x14u)*48u;
    uint32_t quotient=(uint32_t)((int64_t)i32(product)/100);
    uint32_t base=r32(0x54ff1cu)-quotient;
    cached=random_int(base*2u-32u)+16u;
    w32(0x551520u,cached);
    ps2LibcPrintf(0x545ba0u,sx(cached),sx(base));
    return sx(r32(0x551520u));
}

uint64_t ps2FieldEncounterCount_0028CC98(void)
{
    return r16(work()+0x1cf8u);
}

uint64_t ps2FieldEncounterCheckLevel_0028CEE0(uint64_t encounter)
{
    if(!encounter)return 0;
    uint32_t count=0,total=0,p=encounter_at(encounter)+6u;
    /* The original loop reads ELEVEN halfwords, including row+1A. This differs
     * from the ten physical formation slots and from the notes' nine-slot guess. */
    for(uint32_t j=0;j<11u;j++){
        uint32_t id=r16(p+j*2u);
        if(id){++count;total+=*at(0x3497c0u+id*60u+5u);}
    }
    if(!count)return 0;
    uint32_t average=(uint32_t)((int64_t)i32(total)/(int64_t)i32(count));
    uint32_t player=(uint32_t)datGetPlayerLevel();
    uint32_t adjusted=player+((player&0x80000000u)?3u:0u);
    return i32(player)<=i32(average+asr(adjusted,2u));
}

void ps2FieldEncounterReset_0028CFB0(void)
{
    uint32_t p=work();
    w16(p+0x1cf8u,0);w32(p+0x1cf4u,0);w32(0x551520u,0);
}

uint64_t ps2FieldEncounterAdvance_0028CCA8(uint64_t pack,float distance)
{
    uint32_t length;memcpy(&length,&distance,4);
    if(!pack)return 0;
    if(EE_FPU_COMPARE_S(length,0u,0u))return 0;
    uint32_t condition=(uint32_t)ps2FieldEncounterCondition_0028C9F0(pack);
    uint64_t threshold=ps2FieldEncounterThreshold_0028CB68(pack);
    if(!threshold)return 0;
    uint32_t p=work(),sum=EE_FPU_ADD_S(r32(p+0x1cf4u),length);
    int below=EE_FPU_COMPARE_S(sum,0x42c80000u,1u)!=0;
    w32(p+0x1cf4u,sum);
    if(below)return 0;
    uint32_t steps=EE_FPU_CVT_W_S(EE_FPU_DIV_S(sum,0x42c80000u));
    uint32_t remainder=EE_FPU_SUB_S(sum,EE_FPU_MUL_S(EE_FPU_CVT_S_W(steps),0x42c80000u));
    w32(p+0x1cf4u,remainder);
    for(int32_t j=0;j<i32(steps);j++){
        p=work();
        uint32_t fast=r32(p+0xa4cu)&2u;
        uint32_t draw=random_int(fast?7u:3u);
        p=work();
        w16(p+0x1cf8u,(uint16_t)(r16(p+0x1cf8u)+draw+(fast?6u:2u)));
    }
    p=work();
    if(r16(p+0x1cf8u)>65000u)w16(p+0x1cf8u,65000u);
    /* SLT compares two original64 values. Cached LW results are sign extended;
     * the counter is unsigned16. A negative threshold therefore permits a draw. */
    if(((uint64_t)r16(p+0x1cf8u)^UINT64_C(0x8000000000000000))
       <(threshold^UINT64_C(0x8000000000000000)))return 0;
    uint64_t draw=sx(random_int(1000u));
    uint32_t total=0,choices=pack_at(pack)+condition*100u+0x18u;
    for(uint32_t j=0;j<12u;j++){
        uint32_t id=r16(choices+j*8u);
        if(!id)continue;
        total+=r16(choices+j*8u+2u);
        if(i32((uint32_t)draw)>=i32(total))continue;
        if((r32(work()+0xa4cu)&1u)&&!ps2FieldEncounterCheckLevel_0028CEE0(id)){
            ps2FieldEncounterReset_0028CFB0();return 0;
        }
        w32(0x551520u,0);
        return sx((condition<<24)|(j<<16)|id);
    }
    return 0;
}

uint64_t ps2FieldEncounterMusic_0028CFC8(uint64_t pack,uint64_t encounter)
{
    uint32_t music=0;
    if(pack&&!(pack&UINT64_C(0x8000000000000000)))music=r16(pack_at(pack)+4u);
    uint32_t specific=r16(encounter_at(encounter)+0x24u);
    if(specific)music=specific;
    return music?music:1u;
}

uint64_t ps2FieldEncounterBattleMusic_0028D028(void)
{
    uint32_t context=(uint32_t)nbGetMainProcessData();
    return ps2FieldEncounterMusic_0028CFC8(sx(r32(context+0x28u)),sx(r32(context+0x34u)));
}

uint64_t ps2FieldEncounterFieldMusic_0028D050(uint64_t encoded)
{
    return ps2FieldEncounterMusic_0028CFC8((uint32_t)encoded>>24,(uint32_t)encoded&0xffffu);
}

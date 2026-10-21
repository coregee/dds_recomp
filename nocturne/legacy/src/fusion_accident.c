/* Whole native fusion-accident algorithms, SLUS_209.11.
 * Semantic/declared-RAM/callee-save profile: private guest frames and full
 * volatile banks are deliberately not claimed by these typed C functions. */
#include "fusion_accident.h"
#include "unit_neighbors.h"
#include <string.h>

static uint8_t *at(uint32_t address)
{
    return (uint8_t *)nocturneResolveFusionAccidentAddress(address);
}
static uint16_t read16(uint32_t address)
{
    uint16_t value;memcpy(&value,at(address),sizeof(value));return value;
}
static uint32_t read32(uint32_t address)
{
    uint32_t value;memcpy(&value,at(address),sizeof(value));return value;
}
static int32_t signed32(uint32_t value)
{
    return value<=INT32_MAX?(int32_t)value:(int32_t)((int64_t)value-INT64_C(4294967296));
}
static uint64_t sx(uint32_t value)
{
    return (uint64_t)(int64_t)signed32(value);
}
static uint32_t descriptor(uint16_t id)
{
    return UINT32_C(0x3497c0)+(uint32_t)id*60u;
}
static const datUnitWork_PS2 *stock(void)
{
    return (const datUnitWork_PS2 *)at(read32(UINT32_C(0x54ea20))+UINT32_C(0xa54));
}

/* 001FD3B0, whole29 instructions. Matching rows whose event is unset disable
 * the demon. Search all34 rows, including duplicate IDs. */
uint64_t ps2FusionAccidentEventDisabled_001FD3B0(uint64_t raw_id)
{
    uint16_t id=(uint16_t)raw_id;
    for(uint32_t i=0;i<34;i++){
        uint32_t row=UINT32_C(0x32dcc0)+i*8u;
        if(read16(row)==id&&evtBitCheck(signed32(read32(row+4u)))==0)return 1;
    }
    return 0;
}

/* 001FE2C8, whole9. Native return is mask2, not HD's normalized boolean1. */
uint64_t ps2FusionAccidentMetaOnly_001FE2C8(uint64_t raw_id)
{
    return (uint64_t)(*at(descriptor((uint16_t)raw_id))&2u);
}

/* 001FE2F0, whole28. Zero/full folded moon uses maskF; others useFF.
 * The real default RNG is advanced exactly once on either branch. */
uint64_t ps2FusionAccidentCheck_001FE2F0(void)
{
    uint32_t moon=evtGetAgeOfMoon();
    uint32_t value=sdfGetRand(NULL);
    return (value&((moon==0||moon==8)?15u:255u))==0?1u:0u;
}

/* 001FE368, whole8: the apparent constant result still consumes real RNG. */
uint64_t ps2FusionAccidentType_001FE368(void)
{
    (void)sdfGetRand(NULL);
    return 0;
}

/* 001FE388, whole33. Reverse14-entry scan; exhausted search returns the
 * final read entry0 even if it was occupied or equal to excluded_id. */
uint64_t ps2FusionAccidentFallback_001FE388(uint64_t raw_excluded_id)
{
    uint16_t excluded=(uint16_t)raw_excluded_id,id=0;
    for(int32_t i=13;i>=0;i--){
        id=read16(UINT32_C(0x32dca0)+(uint32_t)i*2u);
        if(cmbChkStockDevil(id,stock(),16)<0&&id!=excluded)return id;
    }
    return id;
}

/* 001FE410, whole86. All original retries/filters and fallback are retained.
 * The real registered initializer constructs its full236-byte scratch unit
 * from original descriptor/default skills and genuine maximum calculators. */
uint64_t ps2FusionAccidentSelect_001FE410(uint64_t raw_excluded_id)
{
    /* 001FE414/440 retain this player base across retries; the stock query
     * below separately reloads the actual pointer as at001FE4D8. */
    uint32_t player=read32(UINT32_C(0x54ea20))+UINT32_C(0xa54);
    uint16_t excluded=(uint16_t)raw_excluded_id;
    _Alignas(16) datUnitWork_PS2 scratch;
    for(uint32_t attempt=0;attempt<16;attempt++){
        uint16_t id=(uint16_t)(sdfGetRand(NULL)%168u+1u);
        cmbCopyDefaultDevilToStock(id,&scratch);
        if(*at(descriptor(id)+4u)==0x21u)continue;
        if(ps2FusionAccidentEventDisabled_001FD3B0(id)!=0)continue;
        int32_t level=(int32_t)read16(player+UINT32_C(0x14));
        int32_t candidate=(int32_t)scratch.level;
        if(level+3<candidate||candidate<level-15)continue;
        if(cmbChkStockDevil(id,stock(),16)>=0)continue;
        if(ps2FusionAccidentMetaOnly_001FE2C8(id)!=0)continue;
        if(id!=excluded)return id;
    }
    return ps2FusionAccidentFallback_001FE388(excluded);
}

/* 001FE570, whole31. Six signed LB/5 (truncate toward0) then LBU+quotient
 * and SB wrap. Store HP pair before invoking the real MP algorithm. */
uint64_t ps2FusionAccidentBoost_001FE570(uint64_t raw_unit)
{
    uint32_t address=(uint32_t)raw_unit;
    datUnitWork_PS2 *unit=(datUnitWork_PS2 *)at(address);
    for(uint32_t i=0;i<6;i++){
        uint8_t *p=at(address+0x16u+i);uint32_t old=*p;
        int32_t signed_old=old<128u?(int32_t)old:(int32_t)old-256;
        *p=(uint8_t)((int32_t)old+signed_old/5);
    }
    uint32_t hp=datGetMaxHp(unit);unit->maxhp=(uint16_t)hp;unit->hp=(uint16_t)hp;
    uint32_t mp=datGetMaxMp(unit);unit->maxmp=(uint16_t)mp;unit->mp=(uint16_t)mp;
    return sx(mp);
}

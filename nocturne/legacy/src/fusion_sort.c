/* SLUS_209.11: four complete sorter services70ops and two auxiliary leaves39ops.
 * Semantic VOID services/raw64 comparator V0; ordinary guest RAM/callee-save
 * profile. Private scratch96 is guest-backed so real qsort callbacks receive
 * original element addresses. No host qsort, supplied comparisons or padding
 * initialization. Effective addresses wrap to native32 bits.
 */
#include "fusion_sort.h"
#include "ps2_qsort.h"
#include <string.h>

static uint8_t *at(uint32_t address)
{
    return (uint8_t *)nocturneResolveFusionSortAddress(address);
}
static uint8_t r8(uint32_t address)
{
    return *at(address);
}
static uint16_t r16(uint32_t address)
{
    uint16_t value;memcpy(&value,at(address),2);return value;
}
static uint32_t r32(uint32_t address)
{
    uint32_t value;memcpy(&value,at(address),4);return value;
}
static void w8(uint32_t address,uint8_t value)
{
    *at(address)=value;
}
static void w16(uint32_t address,uint16_t value)
{
    memcpy(at(address),&value,2);
}
static void w32(uint32_t address,uint32_t value)
{
    memcpy(at(address),&value,4);
}

void ps2FusionSortPack_00213280(uint64_t raw_unit,uint64_t raw_output)
{
    uint32_t skills=(uint32_t)raw_unit+0x86u;
    uint32_t attributes=(uint32_t)raw_unit+0xb6u;
    uint32_t output=(uint32_t)raw_output;
    for(uint32_t i=0;i<24u;++i){
        uint16_t skill=r16(skills);skills+=2u;
        w16(output,skill);
        /* Original reads attribute AFTER the halfword store: overlap matters. */
        uint8_t attribute=r8(attributes);attributes+=1u;
        w8(output+2u,attribute);output+=4u;
    }
}

void ps2FusionSortUnpack_002132C0(uint64_t raw_unit,uint64_t raw_input)
{
    uint32_t skills=(uint32_t)raw_unit+0x86u;
    uint32_t attributes=(uint32_t)raw_unit+0xb6u;
    uint32_t input=(uint32_t)raw_input;
    for(uint32_t i=0;i<24u;++i){
        uint16_t skill=r16(input);
        w16(skills,skill);skills+=2u;
        uint8_t attribute=r8(input+2u);input+=4u;
        w8(attributes,attribute);attributes+=1u;
    }
}

void ps2FusionSortSkills_00213350(uint64_t unit)
{
    uint32_t scratch=nocturneFusionSortScratchPush(96u);
    ps2FusionSortPack_00213280(unit,scratch);
    ps2Qsort_002D4860(scratch,24u,4u,UINT64_C(0x002131e0));
    ps2FusionSortUnpack_002132C0(unit,scratch);
    nocturneFusionSortScratchPop(scratch,96u);
}

void ps2FusionSortDescriptors_002133A0(uint64_t raw_output,uint64_t raw_count)
{
    uint32_t count=(uint16_t)raw_count;
    uint32_t output=(uint32_t)raw_output;
    uint32_t descriptor=UINT32_C(0x003497c0);
    /* Native has no384 clamp. Bytes2..3 of every row are untouched. */
    for(uint32_t i=0;i<count;++i){
        w16(output,(uint16_t)i);
        w32(output+4u,descriptor);
        descriptor+=60u;output+=8u;
    }
    ps2Qsort_002D4860(raw_output,count,8u,UINT64_C(0x00213230));
}

uint64_t ps2FusionSortCompareSkill_002131E0(uint64_t raw_left,uint64_t raw_right)
{
    uint32_t left=(uint32_t)raw_left;
    uint16_t a=r16(left);
    uint16_t b=r16((uint32_t)raw_right); /* BNE delay: always read. */
    if(a==0u&&b!=0u)return UINT64_C(1);
    if(a!=0u&&b==0u)return UINT64_MAX;
    /* Original re-reads left after these branches, including the both-zero
     * path. Preserve this access rather than replace it with a cached key. */
    a=r16(left);
    if(b<a)return UINT64_C(1);
    if(a<b)return UINT64_MAX;
    return UINT64_C(0);
}

uint64_t ps2FusionSortCompareDescriptor_00213230(uint64_t raw_left,uint64_t raw_right)
{
    /* Native LW pointer loads occur RIGHT then LEFT, before descriptor reads. */
    uint32_t right_descriptor=r32((uint32_t)raw_right+4u);
    uint32_t left_descriptor=r32((uint32_t)raw_left+4u);
    uint8_t b_race=r8(right_descriptor+4u);
    uint8_t a_race=r8(left_descriptor+4u);
    if(b_race<a_race)return UINT64_C(1);
    if(a_race<b_race)return UINT64_MAX;
    uint8_t a_level=r8(left_descriptor+5u);
    uint8_t b_level=r8(right_descriptor+5u);
    if(b_level<a_level)return UINT64_MAX;
    return (uint64_t)(a_level<b_level);
}

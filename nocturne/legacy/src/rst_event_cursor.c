#include "rst_event_cursor.h"

static int8_t signed_byte(uint32_t value)
{
    uint8_t b=(uint8_t)value;
    return b<128u ? (int8_t)b : (int8_t)((int32_t)b-256);
}
static int32_t signed_word(uint32_t value)
{
    return value<=(uint32_t)INT32_MAX ? (int32_t)value : -1-(int32_t)(UINT32_MAX-value);
}
static datUnitWork_PS2 *current_unit(void)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveRstUnitAddress(g_rstCursorWork->unit_address);
#else
    return (datUnitWork_PS2 *)(uintptr_t)g_rstCursorWork->unit_address;
#endif
}
static uint32_t original_unit_address(datUnitWork_PS2 *unit)
{
#if UINTPTR_MAX > UINT32_MAX
    /* Host mapping only, not a substitute for any game calculation. */
    extern uint32_t g_nocturneRstWorkAddress;
    return g_nocturneRstWorkAddress+(uint32_t)((uintptr_t)unit-(uintptr_t)g_datGlobalWork);
#else
    return (uint32_t)(uintptr_t)unit;
#endif
}
static uint32_t original_event_address(const cmbDemonSkillEntry_PS2 *entry)
{
    if(entry==NULL) return 0;
#if UINTPTR_MAX > UINT32_MAX
    return UINT32_C(0x333cf8)+(uint32_t)((uintptr_t)entry-(uintptr_t)g_cmbDemonSkillRows);
#else
    return (uint32_t)(uintptr_t)entry;
#endif
}
static const cmbDemonSkillEntry_PS2 *event_at(uint32_t address,int8_t index)
{
    uint32_t effective=address+(uint32_t)((int32_t)index*4);
#if UINTPTR_MAX > UINT32_MAX
    uint32_t offset=effective-UINT32_C(0x333cf8);
    return (const cmbDemonSkillEntry_PS2 *)((const uint8_t *)g_cmbDemonSkillRows+offset);
#else
    return (const cmbDemonSkillEntry_PS2 *)(uintptr_t)effective;
#endif
}

/* 0021F788 ->1822840E0. Flag1 and absence of status800 precede the
 * complete real EXP-count dependency; exact Boolean positive count. */
int32_t rstChkLevelUpTarget(const datUnitWork_PS2 *unit)
{
    if((unit->flag&1u)==0 || (unit->badstat&0x800u)!=0) return 0;
    return cmbGetLevelUpCount(unit,0)>0 ? 1 : 0;
}
/* 0021F7D8 ->1822841D0. Scan all16 PHYSICAL EC-stride units, not list order;
 * stop after the first positive actual target query. */
int8_t rstChkResultEntry(void)
{
    for(uint32_t index=0;index<16;++index)
        if(rstChkLevelUpTarget(&g_datGlobalWork->units[index])!=0) return 1;
    return 0;
}
/* 0021F838 ->182283F90. Modular addedEXP replaces current EXP only in the
 * real count's private copy. Return old LOW BYTE level+count narrowedbyte. */
uint8_t rstCalcLevelFromExp(uint8_t index,uint32_t exp)
{
    datUnitWork_PS2 *unit=&g_datGlobalWork->units[index];
    int32_t added=signed_word(exp-(uint32_t)unit->exp);
    int32_t count=cmbGetLevelUpCount(unit,added);
    return (uint8_t)((uint32_t)(uint8_t)unit->level+(uint32_t)count);
}
/* 0021F898 ->182283EC0. Original full signed32 requested level passes to
 * the real EXP scaler; no byte/ushort truncation. */
uint32_t rstCalcExpFromLevel(uint8_t index,int32_t level)
{
    return cmbCalcLevelUpExp(&g_datGlobalWork->units[index],level);
}
/* 002203D0 ->1822812A0. Advance the signed result72 cursor before list
 * lookup; skip negative entries and no-level changes. Pointer16C changes only
 * after a qualifying real setup+limit query, including result2 success. */
int8_t rstSetCurrentDevil(void)
{
    int8_t outcome=0;
    datUnitWork_PS2 *unit=NULL;
    for(;;) {
        int8_t cursor=g_rstCursorWork->stock_cursor;
        if(cursor>=16) break;
        uint8_t increment=(uint8_t)g_rstCursorWork->stock_cursor+1u;
        g_rstCursorWork->stock_cursor=signed_byte(increment);
        int8_t index=signed_byte(g_datGlobalWork->stock_list[cursor]);
        if(index<0) continue;
        unit=&g_datGlobalWork->units[index];
        if(rstSetLevelUpCount(unit)==0) continue;
        outcome=rstChkParamLimitAll(unit)!=0 ? 2 : 1;
        break;
    }
    if(outcome!=0) g_rstCursorWork->unit_address=original_unit_address(unit);
    return outcome;
}
/* 00220860 ->18227C330. The actual dependency counts EVERY level match,
 * then original code walks contiguous entries from the FIRST pointer.
 * Keep that distinction, signed cursor indexing and all result reloads. */
int8_t rstCalcEventInfo(uint16_t *parameter)
{
    for(;;) {
        rstCursorWork_PS2 *result=g_rstCursorWork;
        if(current_unit()->level<result->preview.level) return -1;
        if(result->event_count==0) {
            result->event_index=0;
            result=g_rstCursorWork;
            const cmbDemonSkillEntry_PS2 *first=cmbChkLevelUpEvent(&result->preview,&result->event_count);
            g_rstCursorWork->event_address=original_event_address(first);
            result=g_rstCursorWork;
        }
        uint32_t address=result->event_address;
        if(address!=0 && result->event_count!=result->event_index) {
            if(parameter!=NULL) {
                *parameter=event_at(address,result->event_index)->skill;
                result=g_rstCursorWork;
            }
            int8_t index=result->event_index;
            address=result->event_address;
            result->event_index=signed_byte((uint32_t)(uint8_t)index+1u);
            return event_at(address,index)->type;
        }
        result->event_count=0;
        result=g_rstCursorWork;
        if(result->preview.level>=99u) return -1;
        rstAddLevel(1,&result->preview);
        if(g_rstCursorWork->event_count!=0) return -1;
    }
}
/* 00220BA8 ->182280820. Consume actual event iterator until type1
 * unevolved or type6 evolved; real skill-owner/count eligibility0/1/2.
 * Already-owned event subtracts one from result1B as a modular byte. */
int8_t rstGetDefaultSkill(void)
{
    for(;;) {
        int8_t type=rstCalcEventInfo(&g_rstCursorWork->proposed_skill);
        if(type<0) return 0;
        if(type!=1 && type!=6) continue;
        uint16_t old=current_unit()->hensinmae;
        if((type==6 && old==0) || (type==1 && old!=0)) continue;
        uint8_t outcome=rstChkAddSkill(g_rstCursorWork->proposed_skill);
        if(outcome!=0) return signed_byte(outcome);
        g_rstLevelWork->level_difference=(uint8_t)((uint32_t)g_rstLevelWork->level_difference-1u);
    }
}


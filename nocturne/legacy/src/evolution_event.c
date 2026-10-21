/* Complete SLUS_209.11 evolution-event consumer, original00223258/80ops.
 * Existing registered algorithms execute construction, stock queries, EXP,
 * weighted level growth and parameter limits. No supplied dependency results.
 */
#include "evolution_event.h"
#include "inheritance_queries.h"
#include "unit_neighbors.h"
#include "exp.h"
#include "rst_rng_frontier.h"
#include <string.h>

static uint8_t *at(uint32_t address)
{
    return (uint8_t *)nocturneResolveEvolutionEventAddress(address);
}
static uint16_t r16(uint32_t address)
{
    uint16_t value;memcpy(&value,at(address),2);return value;
}
static uint32_t r32(uint32_t address)
{
    uint32_t value;memcpy(&value,at(address),4);return value;
}
static void w16(uint32_t address,uint16_t value)
{
    memcpy(at(address),&value,2);
}
static void w32(uint32_t address,uint32_t value)
{
    memcpy(at(address),&value,4);
}

void ps2EvolutionEvent_00223258(uint64_t raw_source,uint64_t raw_event,
    uint64_t raw_mode,uint64_t raw_output)
{
    uint32_t source=(uint32_t)raw_source,event=(uint32_t)raw_event;
    uint16_t id;
    if((uint8_t)raw_mode!=0&&*at(event+5u)==5u){
        const datUnitWork_PS2 *stock=(const datUnitWork_PS2 *)at(source);
        int32_t occupied=cmbChkStockDevilNums(stock,16);
        int32_t dark=cmbChkStockDarkDevilNums(stock,16);
        id=r16(event+(occupied/2<dark?2u:6u));
    }else{
        id=r16(event+2u);
    }
    /* BEQ S1,zero tests the complete original raw64 slot, not low32. */
    if(raw_output==0)return;
    uint32_t output=(uint32_t)raw_output;
    datUnitWork_PS2 *unit=(datUnitWork_PS2 *)at(output);
    cmbCopyDefaultDevilToStock(id,unit);
    /* Original reloads source AFTER the constructor. Exact self-alias sees
     * the newly constructed source level, rather than its old input level. */
    uint32_t default_level=r16(output+0x14u),source_level=r16(source+0x14u);
    if(default_level>=source_level)return;
    uint32_t remaining=source_level-default_level;
    w16(output+0x14u,(uint16_t)source_level);
    uint32_t exp=cmbCalcLevelUpExp(unit,(int32_t)source_level);
    w32(output+0x10u,exp);
    do{
        int32_t lane=cmbAddLevelUpParamEx(unit,0);
        if(lane>=0&&datGetParam(unit,lane)<40){
            /* No invented lane<6 clamp. Original uses S1+6+lane+10. */
            uint8_t *parameter=at(output+0x16u+(uint32_t)lane);
            *parameter=(uint8_t)((uint32_t)*parameter+1u);
        }
        --remaining;
    }while(remaining!=0);
    w32(output,r32(output)|UINT32_C(0x200));
}

/* Complete twelve recovery-service bodies from SLUS_209.11.
 * Original instruction order/widths and COP1 boundaries determine behavior.
 * Semantic/callee-save/declared-RAM profile: guest private/save frames, full
 * volatile CPU/FPR banks, HI/LO and arithmetic FCSR flags are not transported.
 * No OS/device/game-result callbacks or precomputed maxima are used. */
#include "recovery_service.h"
#include "nocturne.h"
#include "ee_fpu.h"
#include <string.h>

static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveRecoveryServiceAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint16_t read16(uint32_t address){uint16_t v;memcpy(&v,at(address),2);return v;}
static void write16(uint32_t address,uint16_t value){memcpy(at(address),&value,2);}
static uint64_t result(uint32_t word)
{return word&UINT32_C(0x80000000)?UINT64_C(0xffffffff00000000)|word:word;}
static uint32_t maximum_hp(uint32_t unit)
{return datGetMaxHp((datUnitWork_PS2 *)at(unit));}
static uint32_t maximum_mp(uint32_t unit)
{return datGetMaxMp((datUnitWork_PS2 *)at(unit));}

/* 0020DBF0. Dead-unit tenth is subtracted before converting the HP delta.
 * The MP word's sign bit selects the actual unsigned32->binary32 sequence:
 * sticky-half CVT.S.W then ADD.S, rather than a host floating conversion.
 * Native DIVU's divisor is literal10; its BEQL annuls the BREAK7 delay. */
uint64_t ps2RecoveryServicePriceRecover_0020DBF0(uint64_t raw_unit)
{
    uint32_t unit=(uint32_t)raw_unit,revival_hp=0;
    if(read16(unit+0x0eu)&0x0800u)
        revival_hp=(maximum_hp(unit)+UINT32_C(9))/UINT32_C(10);
    uint32_t hp_max=maximum_hp(unit);
    uint32_t hp=read16(unit+0x06u);
    uint32_t hp_delta=hp_max-(hp+revival_hp);
    uint32_t mp_max=maximum_mp(unit);
    uint32_t mp=read16(unit+0x0au);
    uint32_t hp_float=EE_FPU_CVT_S_W(hp_delta);
    uint32_t mp_delta=mp_max-mp,mp_float;
    if(mp_delta&UINT32_C(0x80000000)){
        uint32_t sticky_half=(mp_delta>>1)|(mp_delta&1u);
        mp_float=EE_FPU_CVT_S_W(sticky_half);
        mp_float=EE_FPU_ADD_S(mp_float,mp_float);
    }else mp_float=EE_FPU_CVT_S_W(mp_delta);
    uint32_t scaled=EE_FPU_MUL_S(mp_float,UINT32_C(0x40200000));
    uint32_t total=EE_FPU_ADD_S(hp_float,scaled);
    return result(EE_FPU_CVT_W_S(total));
}

/* 0020DCC0. Each of the three status bits selects the same100, not a sum. */
uint64_t ps2RecoveryServicePriceStatusRecover_0020DCC0(uint64_t raw_unit)
{return (read16((uint32_t)raw_unit+0x0eu)&0x0160u)?100u:0u;}

/* 0020DCE8. MOVZ in the JR delay returns0 when the dead bit is absent. */
uint64_t ps2RecoveryServicePriceRevive_0020DCE8(uint64_t raw_unit)
{return (read16((uint32_t)raw_unit+0x0eu)&0x0800u)?400u:0u;}

/* 0020DD00. Real JR delay word24020190 defines400. Old pseudocode's0
 * omitted that delay effect and is deliberately not used as authority. */
uint64_t ps2RecoveryServicePriceDispel_0020DD00(void)
{return 400u;}

/* 0020DD08. Preserve call order and both wrapping32-bit ADDU boundaries. */
uint64_t ps2RecoveryServicePriceAllRecover_0020DD08(uint64_t unit)
{
    uint32_t recovery=(uint32_t)ps2RecoveryServicePriceRecover_0020DBF0(unit);
    uint32_t statuses=(uint32_t)ps2RecoveryServicePriceStatusRecover_0020DCC0(unit);
    uint32_t partial=recovery+statuses;
    uint32_t revival=(uint32_t)ps2RecoveryServicePriceRevive_0020DCE8(unit);
    return result(partial+revival);
}

/* 0020DD50. ANDI A1,FF precedes the signed comparisons and real tail calls.
 * Unsupported low8 values return sign-extended -1 without touching the unit. */
uint64_t ps2RecoveryServicePrice_0020DD50(uint64_t unit,uint64_t raw_flag)
{
    switch((uint8_t)raw_flag){
    case 1:return ps2RecoveryServicePriceRecover_0020DBF0(unit);
    case 2:return ps2RecoveryServicePriceStatusRecover_0020DCC0(unit);
    case 4:return ps2RecoveryServicePriceRevive_0020DCE8(unit);
    case 7:return ps2RecoveryServicePriceAllRecover_0020DD08(unit);
    default:return UINT64_MAX;
    }
}

/* 0020DDD8. The HP store occurs before the second actual calculator call. */
uint64_t ps2RecoveryServiceAppRecover_0020DDD8(uint64_t raw_unit)
{
    uint32_t unit=(uint32_t)raw_unit;
    uint32_t hp=maximum_hp(unit);write16(unit+0x06u,(uint16_t)hp);
    uint32_t mp=maximum_mp(unit);write16(unit+0x0au,(uint16_t)mp);
    return 1u;
}

/* 0020DE10. SH in the JR delay preserves all bits except20/40/100. */
uint64_t ps2RecoveryServiceAppStatusRecover_0020DE10(uint64_t raw_unit)
{
    uint32_t address=(uint32_t)raw_unit+0x0eu;
    uint16_t status=(uint16_t)(read16(address)&0xfe9fu);
    write16(address,status);return status;
}

/* 0020DE20. Dead bit is cleared in the maxHP JAL delay, before that call.
 * ADDIU wraps32, DIVU uses unsigned32 and SH retains the low16 result.
 * V0 remains the complete quotient, not the truncated stored HP. */
uint64_t ps2RecoveryServiceAppRevive_0020DE20(uint64_t raw_unit)
{
    uint32_t unit=(uint32_t)raw_unit;
    write16(unit+0x0eu,(uint16_t)(read16(unit+0x0eu)&0xf7ffu));
    uint32_t hp=(maximum_hp(unit)+UINT32_C(9))/UINT32_C(10);
    write16(unit+0x06u,(uint16_t)hp);return result(hp);
}

/* 0020DE70. Defined raw V0 is the mask result even though HD declares void. */
uint64_t ps2RecoveryServiceAppDispel_0020DE70(uint64_t raw_unit)
{
    uint32_t address=(uint32_t)raw_unit+0x0eu;
    uint16_t status=(uint16_t)(read16(address)&0x7fffu);
    write16(address,status);return status;
}

/* 0020DE80. Real ordered three-call composition. Final status-clear tail
 * retains8000; this routine does not silently call AppDispel as well. */
uint64_t ps2RecoveryServiceAppAllRecover_0020DE80(uint64_t unit)
{
    (void)ps2RecoveryServiceAppRevive_0020DE20(unit);
    (void)ps2RecoveryServiceAppRecover_0020DDD8(unit);
    return ps2RecoveryServiceAppStatusRecover_0020DE10(unit);
}

/* 0020DEB0. HP is read before maxHP, MP after maxHP but before maxMP,
 * then status is read after both actual calls. No cached maxima/flags. */
uint64_t ps2RecoveryServiceGetDevilAttr_0020DEB0(uint64_t raw_unit)
{
    uint32_t unit=(uint32_t)raw_unit;
    uint32_t hp=read16(unit+0x06u),hp_max=maximum_hp(unit);
    uint32_t mp=read16(unit+0x0au),mp_max=maximum_mp(unit);
    uint16_t status=read16(unit+0x0eu);
    uint32_t value=(hp<hp_max||mp<mp_max)?1u:0u;
    if(status&0x0020u)value|=2u;
    if(status&0x0040u)value|=2u;
    if(status&0x0100u)value|=2u;
    if(status&0x0800u)value|=4u;
    return value;
}

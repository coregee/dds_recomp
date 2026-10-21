/* Recovered EXP routines from SLUS_209.11. See next-exp-leads.md. */
#include "exp.h"

/* Defined low32 two's-complement interpretation without an out-of-range
 * unsigned-to-signed cast or signed-overflow expression. */
static int32_t signed_word(uint32_t bits)
{
    if (bits <= (uint32_t)INT32_MAX) return (int32_t)bits;
    return -1 - (int32_t)(UINT32_MAX - bits);
}

/* 00223628. MULT/MFLO twice wraps the cube before signed CVT.S.W.
 * Distinct MUL.S then ADD.S then CVT.W.S, with signed-negative rejection. */
uint32_t cmpCalcLevelUpBaseExp(int32_t level)
{
    uint32_t level_bits = (uint32_t)level;
    uint32_t square = level_bits * level_bits;
    uint32_t a_bits = g_cmbExpConstants->a_bits;
    uint32_t cube = square * level_bits;
    uint32_t f0 = EE_FPU_CVT_S_W(cube);
    f0 = EE_FPU_MUL_S(f0, a_bits);
    f0 = EE_FPU_ADD_S(f0, PS2_EXP_MINUS_FIVE_BITS);
    uint32_t converted = EE_FPU_CVT_W_S(f0);
    return (converted & UINT32_C(0x80000000)) != 0 ? 0 : converted;
}

/* 00223668. Both CVT.W boundaries and the intervening CVT.S are essential.
 * Do not collapse the products, substitute the HD integer percentage, or
 * introduce the HD D==1 shortcut. Each helper call follows COP1 opcode order. */
uint32_t cmbCalcLevelUpExp(const datUnitWork_PS2 *unit, int32_t level)
{
    uint32_t requested = cmpCalcLevelUpBaseExp(level);
    if ((unit->flag & UINT32_C(4)) != 0) return requested;

    uint16_t descriptor_id = unit->id;
    uint32_t requested_float = EE_FPU_CVT_S_W(requested);
    uint32_t c_bits = g_cmbExpConstants->c_bits;
    uint32_t b_bits = g_cmbExpConstants->b_bits;
    const uint8_t *descriptor =
        (const uint8_t *)&g_datDevilSkillTable[descriptor_id];
    uint8_t descriptor_level =
        descriptor[offsetof(cmbInheritanceDevilView_PS2, level)];
    uint32_t descriptor_float = EE_FPU_CVT_S_W(descriptor_level);
    uint32_t factor_product = EE_FPU_MUL_S(descriptor_float, c_bits);
    const uint32_t factor_f20 = EE_FPU_SUB_S(b_bits, factor_product);
    uint32_t first_product = EE_FPU_MUL_S(requested_float, factor_f20);
    uint32_t first_integer = EE_FPU_CVT_W_S(first_product);

    uint32_t descriptor_base = cmpCalcLevelUpBaseExp(descriptor_level);
    uint32_t descriptor_base_float = EE_FPU_CVT_S_W(descriptor_base);
    uint32_t ancestral_exp_bits = (uint32_t)unit->hensinmaeexp;
    uint32_t first_integer_float = EE_FPU_CVT_S_W(first_integer);
    uint32_t second_product =
        EE_FPU_MUL_S(descriptor_base_float, factor_f20);
    uint32_t difference = EE_FPU_SUB_S(first_integer_float, second_product);
    uint32_t second_integer = EE_FPU_CVT_W_S(difference);
    return second_integer + ancestral_exp_bits;
}

/* 00223728. LHU plus integer1, without narrowing back to ushort: stored
 * FFFF passes requested level10000 to the full signed32 scaler interface. */
uint32_t cmbChkLevelUpExp(const datUnitWork_PS2 *unit)
{
    int32_t next_level = (int32_t)unit->level + 1;
    return cmbCalcLevelUpExp(unit, next_level);
}

/* 00223928. Execute original recovered copy/resource dependency, then an
 * unsigned EXP query loop on scratch. Increment level before testing cap;
 * count only transitions whose previous stored level was below255. */
int32_t cmbGetLevelUpCount(const datUnitWork_PS2 *unit, int32_t added_exp)
{
    _Alignas(16) datUnitWork_PS2 scratch;
    cmbCopyCustomDevilToStock(&scratch, unit);
    scratch.exp = signed_word((uint32_t)scratch.exp + (uint32_t)added_exp);

    int32_t count = 0;
    for (;;) {
        uint32_t threshold = cmbChkLevelUpExp(&scratch);
        if ((uint32_t)scratch.exp < threshold) return count;
        uint16_t previous_level = scratch.level;
        scratch.level = (uint16_t)((uint32_t)previous_level + 1);
        if (previous_level >= 255) return count;
        ++count;
    }
}

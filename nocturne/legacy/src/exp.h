#ifndef NOCTURNE_EXP_H
#define NOCTURNE_EXP_H

/* Original COP1 operand and result boundaries are explicit. */
#include "rst_stats.h"
#include "stat_neighbors.h"
#include "ee_fpu.h"

/* Host binding, not a recovered original symbol. Three contiguous
 * LWC1 cells start0054e434. Keep their original A/C/B order and load timing;
 * read the binding on each original call instead of freezing the values in C.
 * Its established initialized bytes are listed below, including B's low bit.
 * The binding is read-only through these interfaces; alias writes elsewhere
 * in the complete executable have not been ruled out by this local review. */
typedef struct cmbExpConstants_PS2 {
    uint32_t a_bits, c_bits, b_bits;
} cmbExpConstants_PS2;

#define PS2_EXP_A_INITIAL_BITS UINT32_C(0x3fb5c28f)
#define PS2_EXP_C_INITIAL_BITS UINT32_C(0x3c8b4395)
#define PS2_EXP_B_INITIAL_BITS UINT32_C(0x402ccccc)
#define PS2_EXP_MINUS_FIVE_BITS UINT32_C(0xc0a00000)
extern const cmbExpConstants_PS2 *g_cmbExpConstants;

_Static_assert(sizeof(cmbExpConstants_PS2) == 12, "EXP coefficient span");
_Static_assert(offsetof(cmbExpConstants_PS2, a_bits) == 0, "A at0054e434");
_Static_assert(offsetof(cmbExpConstants_PS2, c_bits) == 4, "C at0054e438");
_Static_assert(offsetof(cmbExpConstants_PS2, b_bits) == 8, "B at0054e43c");
_Static_assert(offsetof(datUnitWork_PS2, flag) == 0, "EXP flags offset");
_Static_assert(offsetof(datUnitWork_PS2, id) == 4, "EXP descriptor ID offset");
_Static_assert(offsetof(datUnitWork_PS2, exp) == 0x10, "EXP offset");
_Static_assert(offsetof(datUnitWork_PS2, level) == 0x14, "stored level offset");
_Static_assert(offsetof(datUnitWork_PS2, hensinmaeexp) == 0xd8,
    "ancestral EXP offset");
_Static_assert(offsetof(cmbInheritanceDevilView_PS2, level) == 5,
    "unsigned descriptor level byte");

/* Contract: complete non-NULL unit objects and initialized coefficient/FPU
 * bindings. Level/added_exp are full signed32 inputs; negative values retain
 * their original modular integer behavior. The scaler reads descriptor byte5
 * from g_datDevilSkillTable at003497c0/stride3c unless flag4 bypasses it. The
 * ushort descriptor ID must select a backed row on that path. Count also
 * executes the real cmbCopyCustomDevilToStock dependency; satisfy its current
 * skill/resource/global table contracts and word-aligned source requirement.
 *
 * All four preserve caller unit, descriptor and coefficient bytes. Count
 * writes only an aligned private EC-byte scratch unit and counts cap255 after
 * its scratch level increment. Query wrappers do not update caller level or
 * subtract thresholds from EXP. FPU effects belong to the primitive provider;
 * a local raw factor retains the original saved F20 across the second base
 * call. It does not overwrite a shared F20 binding. Return low32 bits of the
 * first three are unsigned thresholds; count returns signed32, normally0..255.
 */
uint32_t cmpCalcLevelUpBaseExp(int32_t level);
uint32_t cmbCalcLevelUpExp(const datUnitWork_PS2 *unit, int32_t level);
uint32_t cmbChkLevelUpExp(const datUnitWork_PS2 *unit);
int32_t cmbGetLevelUpCount(const datUnitWork_PS2 *unit, int32_t added_exp);

#endif

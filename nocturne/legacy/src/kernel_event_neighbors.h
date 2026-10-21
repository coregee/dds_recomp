#ifndef NOCTURNE_KERNEL_EVENT_NEIGHBORS_H
#define NOCTURNE_KERNEL_EVENT_NEIGHBORS_H

#include "nocturne.h"

/* Partial PS2 views and host binding names, not recovered original symbols.
 * The original sequence word is 0054eb80 and process word is 0054eb88. */
typedef struct fldFlagState_PS2 {
    uint32_t sequence_flags;
    uint8_t unknown_04[4];
    uint32_t process_flags;
} fldFlagState_PS2;

/* Only the word at 002fbf80+14 is used by these leaves. The complete runtime
 * object is larger; neither its remaining fields nor its size is recovered. */
typedef struct fldRuntimeFlags_PS2_prefix {
    uint8_t unknown_00[0x14];
    uint32_t flags;
} fldRuntimeFlags_PS2_prefix;

_Static_assert(sizeof(fldFlagState_PS2) == 0x0c, "partial flag state extent");
_Static_assert(offsetof(fldFlagState_PS2, process_flags) == 8, "process flag offset");
_Static_assert(offsetof(fldRuntimeFlags_PS2_prefix, flags) == 0x14, "runtime flag offset");
_Static_assert(sizeof(fldRuntimeFlags_PS2_prefix) == 0x18, "partial runtime view extent");
_Static_assert(offsetof(datGlobalWork_PS2, unknown_0a4c) == 0xa4c, "effect flag backing offset");
_Static_assert(sizeof(((datGlobalWork_PS2 *)0)->unknown_0a4c) == 4, "effect flag backing extent");

extern fldFlagState_PS2 *g_fldFlagState;
extern fldRuntimeFlags_PS2_prefix *g_fldRuntimeFlags;
/* Signed word at 0054eafc, used only when the global LightMa bit is clear. */
extern const int32_t *g_fldLightMaEnabled;

/* Stable ordinary backed RAM; field bindings retain separate original storage.
 * Seeding requires a writable, four-byte-aligned sixteen-byte destination,
 * or NULL with the existing default state backed. Raw uint32 masks for generic
 * Check have zero extension or consistent sign extension in EE registers.
 * LightMa enabled may be NULL only when work+A4C bit8 skips its load.
 * Disjoint value comparisons do not establish MMIO or access-trace behavior. */
void sdfRandomize(uint32_t *state, uint32_t seed);
void fldSeqOnFlag(uint32_t flag);
void fldSeqOffFlag(uint32_t flag);
int8_t fldSeqCheckFlag(uint32_t flag);
void fldProcOnFlag(uint32_t flag);
void fldProcOffFlag(uint32_t flag);
int8_t fldProcCheckFlag(uint32_t flag);
void fldLightMaClear(void);
int32_t fldLightMaChk(void);
void fldRifutoMaClear(void);
void fldRifutoMaStart(void);
int32_t fldRifutoMaChk(void);
void fldRiberaMaClear(void);
void fldRiberaMaStart(void);
int32_t fldRiberaMaChk(void);
void fldEsutoMaClear(void);
void fldEsutoMaStart(void);
int32_t fldEsutoMaChk(void);

#endif

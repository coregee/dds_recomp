#ifndef NOCTURNE_FIELD_NEIGHBORS_H
#define NOCTURNE_FIELD_NEIGHBORS_H

#include "kernel_event_neighbors.h"

/* Host binding names and partial views, not original PS2 symbol names.
 * GP=00554170: index0054eb48, eligible_count0054eb4c. */
typedef struct fldAnahoriState_PS2 {
    int32_t index;
    int32_t eligible_count;
} fldAnahoriState_PS2;

/* Two distinct signed wait words:0054eb68 and0054eb6c. */
typedef struct fldProcWait_PS2 {
    int32_t camp_wait;
    int32_t am_wait;
} fldProcWait_PS2;

_Static_assert(sizeof(fldAnahoriState_PS2) == 8, "Anahori partial state extent");
_Static_assert(offsetof(fldAnahoriState_PS2, eligible_count) == 4, "Anahori count offset");
_Static_assert(sizeof(fldProcWait_PS2) == 8, "field wait partial state extent");
_Static_assert(offsetof(fldProcWait_PS2, am_wait) == 4, "automap wait offset");
_Static_assert(offsetof(datUnitWork_PS2, hp) == 6, "Anahori HP offset");
_Static_assert(offsetof(datGlobalWork_PS2, units) == 0xa54, "Anahori inline units offset");
_Static_assert(sizeof(((datGlobalWork_PS2 *)0)->units) / sizeof(datUnitWork_PS2) == 16,
               "Anahori fixed unit scan extent");

extern fldAnahoriState_PS2 *g_fldAnahoriState;
extern fldProcWait_PS2 *g_fldProcWait;
/* Original signed byte0054fdd4; only value2 is consumed/reset. */
extern int8_t *g_cmpCampProcessState;
/* Original signed word0054ee60; this batch only reads it. */
extern const int32_t *g_fldAutoMapMode;

/* Stable ordinary backed RAM and distinct original field bindings. Reuse the
 * existing work/runtime/flag views; runtime field and area are words+4/+8.
 * Init always scans all16 inline units. Get skips work when count==0; otherwise
 * it scans at most16, without deriving the scan bound from count or index.
 * Next preserves original signed32 comparison and wrapping32 increment.
 * ClearMsg calls the real corresponding Clear before setting the runtime bit;
 * when its global bit is absent, the runtime view is not used. Positive
 * Camp/Am waits skip camp/mode reads; Camp result1 also skips process flags.
 * No MMIO/concurrency/access-trace or overlapping-global-binding claim. */
int32_t fldLightMaIdxCalc(void);
void fldRifutoMaClearMsg(void);
void fldRiberaMaClearMsg(void);
void fldEsutoMaClearMsg(void);
void fldAnahoriSelectInit(void);
int32_t fldAnahoriSelectGet(void);
void fldAnahoriSelectNext(void);
int8_t cmpChkCampProcess(void);
int32_t fldProcCampChk(void);
int32_t fldAutoMapChkMode(void);
int32_t fldProcAmChk(void);

#endif

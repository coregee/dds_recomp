#ifndef NOCTURNE_RST_MOTION_LEAVES_H
#define NOCTURNE_RST_MOTION_LEAVES_H
#include "nocturne.h"

/* Partial view of the same551F88 result owner. Extent22F0 is access evidence,
 * not a recovered allocation size. These views require one stable RAM owner. */
typedef struct rstMotionWork_PS2 {
    uint8_t unknown_0000[0x16c];
    uint32_t unit_address;
    uint8_t unknown_0170[0x22e5-0x170];
    int8_t motion_number, motion_mode;
    uint8_t unknown_22e7;
    float before_frame, after_frame;
} rstMotionWork_PS2;
_Static_assert(offsetof(rstMotionWork_PS2,unit_address)==0x16c,"unit address32");
_Static_assert(offsetof(rstMotionWork_PS2,motion_number)==0x22e5,"motion byte");
_Static_assert(offsetof(rstMotionWork_PS2,motion_mode)==0x22e6,"mode byte");
_Static_assert(offsetof(rstMotionWork_PS2,before_frame)==0x22e8,"F12 word");
_Static_assert(offsetof(rstMotionWork_PS2,after_frame)==0x22ec,"F13 word");
_Static_assert(sizeof(rstMotionWork_PS2)==0x22f0,"partial accessed extent");
extern rstMotionWork_PS2 *g_rstMotionWork;
extern uint8_t g_ps2RstBusyState;
extern uint8_t *g_ps2RstFlagObject;
/* Original332458 table:21 bytes per unit ID, seven3-byte motion records.
 * Signed type values are allowed only when their complete effective record
 * stays within this backing. No clamp or unsigned-index repair. */
extern const uint8_t *g_rstMotionTable;

int32_t ps2RstConsumeBusyState(void);
void ps2RstMarkObjectFlag(void);
void rstSetMotionReq(int8_t number,float before_frame,float after_frame,int8_t mode);
void rstCancelMotionReq(void);
void rstSetMotionReqFromTbl(int8_t type);

/* Stable, complete aligned result/unit owners; NULL flag pointer or one backed
 * byte (including other writable owners). Motion table is complete and stable.
 * Flag may not alias a pointer slot. This is ordinary RAM, not MMIO/interrupt
 * mutation. F12/F13 are transported as raw words without arithmetic. */
#endif

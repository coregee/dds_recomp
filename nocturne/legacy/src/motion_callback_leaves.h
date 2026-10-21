#ifndef NOCTURNE_MOTION_CALLBACK_LEAVES_H
#define NOCTURNE_MOTION_CALLBACK_LEAVES_H
#include <stdint.h>
/* Raw PS2 address values are stored without host pointer widening.
 * Word-store nodes require four-byte alignment. Vector callbacks require a
 * readable raw model address at node+C and aligned, backed 16-byte transfers.
 * Stable ordinary RAM, without address wrap, MMIO or concurrent mutation. */
void sdfMotionNodeBaseInit(void *node,uint32_t controller_address,uint32_t vtable_address);
void sdfMotCLBK_SetCut(void *node,uint32_t cut_address);
/* Descriptive PS2 aliases; HD blend initialization copies in the reverse direction. */
void ps2MotionSaveValue60(void *node);
void ps2MotionSaveValue50(void *node);
void ps2MotionSaveValue70(void *node);
#if UINTPTR_MAX > UINT32_MAX
const void *nocturneResolveMotionAddress(uint32_t address);
#endif
#endif

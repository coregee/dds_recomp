#include "motion_callback_leaves.h"
#include <string.h>

/* 002B3B78: SW A1,+4 then return-delay-slot SW A2,+0. */
void sdfMotionNodeBaseInit(void *node,uint32_t controller_address,uint32_t vtable_address)
{
    memcpy((uint8_t *)node+4,&controller_address,4);
    memcpy(node,&vtable_address,4);
}
/* 002B4118: raw cut pointer store in JR RA delay slot. */
void sdfMotCLBK_SetCut(void *node,uint32_t cut_address)
{
    memcpy((uint8_t *)node+8,&cut_address,4);
}
static const uint8_t *resolve_original(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolveMotionAddress(address);
#else
    return (const uint8_t *)(uintptr_t)address;
#endif
}
static void save_model_value(void *node,uint32_t offset)
{
    uint32_t model_address;
    uint8_t value[16];
    memcpy(&model_address,(const uint8_t *)node+12,4);
    /* Original LQ completes before SQ, retaining all 128 bits under alias. */
    memcpy(value,resolve_original(model_address)+offset,sizeof value);
    memcpy((uint8_t *)node+16,value,sizeof value);
}
void ps2MotionSaveValue60(void *node) { save_model_value(node,0x60); }
void ps2MotionSaveValue50(void *node) { save_model_value(node,0x50); }
void ps2MotionSaveValue70(void *node) { save_model_value(node,0x70); }

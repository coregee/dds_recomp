#ifndef NOCTURNE_FUSION_CORE_TRANSPORT_H
#define NOCTURNE_FUSION_CORE_TRANSPORT_H
#include <stdint.h>
#define NOCTURNE_FUSION_CORE_STACK_LOW UINT32_C(0x00630000)
#define NOCTURNE_FUSION_CORE_STACK_HIGH UINT32_C(0x00650000)
typedef struct NocturneFusionCorePointerBinding {
    void *cell;
    uint32_t guest_address;
    uint32_t reserved;
} NocturneFusionCorePointerBinding;
/* Actual canonical host pointer cells supplied by the caller; no guest writes. */
void nocturneFusionCoreActivate(const NocturneFusionCorePointerBinding *bindings,uint32_t count);
void nocturneFusionCoreDeactivate(void);
/* The caller binds the actual canonical g_scriptCoreFcsr cell, never a mirror. */
void nocturneFusionCoreBindFcsr(uint32_t *actual_cell);
uint32_t nocturneFusionCoreStackPointer(void);
void nocturneFusionCoreSetStackPointer(uint32_t address);
void nocturneFusionCoreFpuCondition(uint32_t condition);
uint32_t nocturneFusionCoreObserveCall(void (*function)(void),uint32_t argc,const uint64_t *arguments,uint32_t return_width);
_Noreturn void nocturneFusionCoreArithmeticTrap(uint32_t code);
extern uint64_t g_fusionCoreResult;
extern uint32_t g_fusionCoreTrapCode;
extern uint32_t g_fusionCoreCompleted;
#endif

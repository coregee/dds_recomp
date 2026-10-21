#ifndef NOCTURNE_BATTLE_ACTION_SKILL_HEAP_WORLD_KERNEL_H
#define NOCTURNE_BATTLE_ACTION_SKILL_HEAP_WORLD_KERNEL_H
#include "battle_action_skill_kernel.h"

/* Explicit single-thread external test world, not retail BIOS behavior.
 * The old Begin API still selects exact finite-array transport only. */
enum { NOCTURNE_SKILL_HEAP_WORLD_LIMIT = 4096 };
typedef struct NocturneSkillHeapWorldState {
    uint32_t version, enabled, accepted_count, fixed_count, fixed_consumed;
    uint32_t created_heap_semaphores, request_limit, balanced;
    /* Slots are IDs7,21,22, in that order. Missing slots have count0/max1. */
    uint32_t semaphore_present[3], semaphore_count[3], semaphore_max[3];
} NocturneSkillHeapWorldState;

uint32_t nocturneBattleActionSkillKernelBeginHeapWorld(
    const NocturneSkillKernelInput *inputs, uint32_t count);
/* Adds only a pre-existing external model mutex ID10/count1/max127. */
uint32_t nocturneBattleActionSkillKernelBeginModelHeapWorld(
    const NocturneSkillKernelInput *inputs, uint32_t count);
uint32_t nocturneBattleActionSkillKernelHeapWorldState(NocturneSkillHeapWorldState *output);
uint32_t nocturneBattleActionSkillKernelHeapWorldSemaphoreCount(uint32_t id, uint32_t *output);
uint32_t nocturneBattleActionSkillKernelHeapWorldBalanced(void);
#endif

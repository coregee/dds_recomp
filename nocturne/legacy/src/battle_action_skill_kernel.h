#ifndef NOCTURNE_BATTLE_ACTION_SKILL_KERNEL_H
#define NOCTURNE_BATTLE_ACTION_SKILL_KERNEL_H
#include <stdint.h>

/* External system inputs only. Each record is consumed once, in exact order.
 * These records contain no game-function results or guest memory patches. */
typedef struct NocturneSkillKernelInput {
    uint64_t selector;
    uint32_t pc;
    uint32_t argc;
    uint64_t arguments[2];
    uint64_t result;
    /* Optional complete V1 register output, little-endian64 lanes.
     * flags==0 preserves V1; flags==1 publishes both lanes. No inferred reply. */
    uint64_t v1_result[2];
    uint32_t output_flags;
    uint32_t reserved;
} NocturneSkillKernelInput;

uint64_t nocturneBattleActionSkillKernelValue(uint64_t selector, uint32_t pc,
    uint32_t argc, const uint64_t *arguments);
uint32_t nocturneBattleActionSkillKernelBegin(const NocturneSkillKernelInput *inputs, uint32_t count);
uint32_t nocturneBattleActionSkillKernelTake(uint64_t selector, uint32_t pc,
    uint32_t argc, const uint64_t *arguments, uint64_t *result);
uint32_t nocturneBattleActionSkillKernelFinish(void);
uint32_t nocturneBattleActionSkillKernelFault(void);
uint32_t nocturneBattleActionSkillKernelPosition(void);
uint32_t nocturneBattleActionSkillKernelTrace(uint32_t index, NocturneSkillKernelInput *output);

/* Observation-frame coordination; neither call installs guest inputs. */
uint32_t nocturneBattleActionSkillKernelEnter(void);
uint32_t nocturneBattleActionSkillKernelComplete(void);
uint32_t nocturneBattleActionSkillObservationActive(void);
_Noreturn void nocturneBattleActionSkillKernelReject(void);
#endif

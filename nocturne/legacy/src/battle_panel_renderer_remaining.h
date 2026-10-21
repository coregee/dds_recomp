#ifndef NOCTURNE_BATTLE_PANEL_RENDERER_REMAINING_H
#define NOCTURNE_BATTLE_PANEL_RENDERER_REMAINING_H
#include <stdint.h>
/* Host handled1/0 only. All original registers/FP/HI-LO/SP/RA already live. */
uint32_t nocturneBattlePanelRendererRemainingBody(uint32_t entry);
/* Genuine integration-owned actual-bank routes, no supplied native result. */
void nocturneBattlePanelRendererRemainingCall(uint32_t target,uint32_t pc);
void nocturneBattlePanelRendererRemainingIndirect(uint64_t target,uint32_t pc);
uint32_t nocturneBattlePanelRendererRemainingFcsr(void);
/* Actual original processor boundaries; no cache tags, OS replies, cache
 * effects, timing or completion values are implemented by this source. The
 * syscall hook consumes the actual live bank; no argument count is guessed. */
uint32_t nocturneBattlePanelRendererRemainingCp0(uint32_t pc,uint32_t reg);
void nocturneBattlePanelRendererRemainingSync(uint32_t pc,uint32_t subtype);
void nocturneBattlePanelRendererRemainingCache(uint32_t pc,uint32_t operation,uint32_t address);
void nocturneBattlePanelRendererRemainingSyscall(uint32_t pc,uint64_t selector);
#endif

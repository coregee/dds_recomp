#ifndef NOCTURNE_BATTLE_PANEL_COLOR_PRIVILEGED_H
#define NOCTURNE_BATTLE_PANEL_COLOR_PRIVILEGED_H
#include <stdint.h>
/* Host handled1/0 only; native banks/actual Status are live inputs. */
uint32_t nocturneBattlePanelColorPrivilegedBody(uint32_t entry);
/* UNIMPLEMENTED privileged processor boundaries. Return actual Status at
 * the original instruction, not a fixture/reply. DI/EI and SYNC must perform
 * their real declared processor effects, or stop before unsupported work.
 * No policy, timing, privilege-domain or hardware admission is made here. */
uint32_t nocturneBattlePanelColorReadStatus(uint32_t pc);
void nocturneBattlePanelColorDisableInterrupts(uint32_t pc);
void nocturneBattlePanelColorEnableInterrupts(uint32_t pc);
void nocturneBattlePanelColorSync(uint32_t subtype,uint32_t pc);
#endif

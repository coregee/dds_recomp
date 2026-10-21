#ifndef NOCTURNE_BATTLE_CALLBACK_DISPATCH_H
#define NOCTURNE_BATTLE_CALLBACK_DISPATCH_H
#include <stdint.h>
/* Original public names. Actual Core+Effect activation selects the native
 * bank/frame path; old standalone memory profiles retain their exact bodies.
 * Neither dispatch mode invents callback results or tolerates unknown targets.
 */
void nbActionSetSeq(uint64_t context,uint64_t state);
uint64_t nbActionProcess1(uint64_t process);
/* Scoped compile aliases of the old complete semantic parent definitions. */
void nocturneLegacyNbActionSetSeq(uint64_t context,uint64_t state);
uint64_t nocturneLegacyNbActionProcess1(uint64_t process);
/* Read-only accessor implemented beside the actual static Core activation
 * cell. No mirrored activation flag or shadow CPU/RAM bank is introduced. */
uint32_t nocturneFusionCoreIsActive(void);
#endif

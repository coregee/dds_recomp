#ifndef NOCTURNE_COMPENDIUM_RESTORE_H
#define NOCTURNE_COMPENDIUM_RESTORE_H
#include <stdint.h>
void *nocturneResolveCompendiumRestoreAddress(uint32_t address);
/* Same actual guest RAM/SP as real typed prerequisites; no result callbacks. */
uint32_t nocturneCompendiumRestoreStackPointer(void);
void nocturneCompendiumRestoreSetStackPointer(uint32_t address);
uint64_t ps2CompendiumRestore_00216BF0(void);
uint64_t ps2CompendiumRestore_00219318(uint64_t p0);
void ps2CompendiumRestore_0021A0B8(uint64_t p0,uint64_t p1);
void ps2CompendiumRestore_0021A118(uint64_t p0,uint64_t p1);
uint64_t ps2CompendiumRestore_0021A308(uint64_t p0,uint64_t p1);
uint64_t ps2CompendiumRestore_00216B20(uint64_t p0);
/* Search preserves raw64ID equality. Restore wrappers have genuine VOID
 * roles; their incidental V0 is not a universal result. All dereferenced
 * effective addresses use original low32 word arithmetic. */
#endif

#ifndef NOCTURNE_MAGATAMA_MENU_ENTRY_H
#define NOCTURNE_MAGATAMA_MENU_ENTRY_H
#include <stdint.h>
void *nocturneResolveMagatamaMenuEntryAddress(uint32_t address);
void ps2MagatamaMessagePositionSet_00213FB8(uint64_t position);
uint64_t ps2MagatamaMessagePositionGet_00213FD8(void);
uint64_t ps2MagatamaRequestLoad_002144B8(uint64_t path,uint64_t slot);
void ps2MagatamaLoadResources_00232AE8(uint64_t data);
uint64_t ps2MagatamaInitialize_00232EC0(uint64_t parent);
void ps2MagatamaTerminate_002330D8(void);
void ps2MagatamaRootUpdate_00234FD0(void);
#endif

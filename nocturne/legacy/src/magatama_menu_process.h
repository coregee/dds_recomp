#ifndef NOCTURNE_MAGATAMA_MENU_PROCESS_H
#define NOCTURNE_MAGATAMA_MENU_PROCESS_H
#include <stdint.h>
void *nocturneResolveMagatamaMenuProcessAddress(uint32_t address);
void ps2CampMenuSuspend_00232550(uint64_t suspend);
uint64_t ps2MagatamaProcessStart_00233010(uint64_t parent);
void ps2MagatamaProcessShutdown_00232FC0(void);
void ps2MagatamaTexturesFree_00232B40(uint64_t data);
void ps2MagatamaResourcesFree_00232BB0(uint64_t data);
void ps2CampInfoHide_00230518(void);
void ps2CampInfoTerminate_0023B4E0(void);
uint64_t ps2VramBlockMergePrevious_002AA718(uint64_t block);
void ps2VramBlockFree_002AA7F0(uint64_t block);
void ps2TextureImmediateFree_002AB860(uint64_t texture);
/* Independently recovered20-byte callback,currently unindexed. This is an
 * external callback API,not a claim that a device read has completed. */
uint64_t ps2MagatamaResourceCompletion_002144A0(uint64_t job,uint64_t event,
    uint64_t data,uint64_t bytes,uint64_t payload);
#endif

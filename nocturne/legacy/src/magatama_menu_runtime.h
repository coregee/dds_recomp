#ifndef NOCTURNE_MAGATAMA_MENU_RUNTIME_H
#define NOCTURNE_MAGATAMA_MENU_RUNTIME_H
#include <stdint.h>
void *nocturneResolveMagatamaMenuRuntimeAddress(uint32_t address);
void ps2MagatamaPadActionHook_00232878(uint64_t type);
uint64_t ps2MagatamaTextureLoading_002329F8(void);
uint64_t ps2MagatamaTextureReady_00232A28(void);
void ps2MagatamaInfoInitialize_00232E90(uint64_t data);
void ps2MagatamaCursorMove_00234BF0(uint64_t mode);
uint64_t ps2MagatamaAttachStatus_00234DC8(void);
void ps2MagatamaRestoreParameters_00234E98(void);
void ps2MagatamaEquipSelection_00234F80(void);
void ps2MagatamaTimersUpdate_002356F8(void);
void ps2MagatamaCommandFadeUpdate_00235770(void);
void ps2MagatamaBlurTimersUpdate_002357C0(void);
void ps2MagatamaIconSetup_00235820(uint64_t icon);
void ps2MagatamaIconMove_00235A58(uint64_t icon);
void ps2MagatamaIconsUpdate_00235AB8(void);
void ps2MagatamaInfoUpdate_00235B50(void);
#endif

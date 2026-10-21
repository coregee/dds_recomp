#ifndef NOCTURNE_FIELD_INF_CONTROLLER_H
#define NOCTURNE_FIELD_INF_CONTROLLER_H
#include <stdint.h>
/* Draft controller interfaces. No staged/canonical build or validation claim. */
uint64_t ps2FieldInfNext_001405B0(uint64_t line,uint64_t selection);
void ps2FieldInfToWap_00140CF0(void);
uint64_t ps2SceneStartNamedScript_0010F4D8(uint64_t scene,uint64_t name);
void ps2FieldInteractionInit_0013C860(void);
void ps2FieldControllerProcNext_00125CB8(uint64_t field,uint64_t event);
uint64_t ps2FieldControllerEventCamera_0012EFD8(void);
/* Real native dependent owners to recover next. These are declarations,not
 * callbacks/stubs: a linked candidate is forbidden until complete bodies exist. */
void ps2FieldControllerResetNormal_0012CA30(void);
void ps2FieldControllerResetPlayer_0012DDF8(void);
void ps2FieldControllerPlayerOff_00134DF8(void);
void ps2FieldControllerPlayerOn_00134E48(void);
void ps2FieldControllerRecover_0013C6F0(void);
void ps2FieldControllerPositionPlayer_001E1688(uint64_t player,uint64_t matter);
void ps2FieldControllerBattle_001E7228(uint64_t encounter);
void *nocturneResolveFieldInfControllerAddress(uint32_t address);
#endif

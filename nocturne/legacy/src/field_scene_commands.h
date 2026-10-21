#ifndef NOCTURNE_FIELD_SCENE_COMMANDS_H
#define NOCTURNE_FIELD_SCENE_COMMANDS_H
#include <stdint.h>
uint64_t ps2FieldCallField2_001E7378(void);
uint64_t ps2FieldCallField3_001E73E0(void);
void *nocturneResolveFieldSceneCommandsAddress(uint32_t address);
uint32_t nocturneFieldSceneCommandsIncomingStack(void);
#endif

#ifndef NOCTURNE_FIELD_DOOR_MOTION_H
#define NOCTURNE_FIELD_DOOR_MOTION_H
#include <stdint.h>
void ps2FieldDoorInit_00142FB0(void);
void ps2FieldDoorImport_001430D0(uint64_t source);
void ps2FieldDoorAllSet_00143188(void);
void ps2FieldDoorStart_00143D50(uint64_t event_hit_id);
uint64_t ps2FieldDoorStep_00143E20(uint64_t matter_id,uint64_t x,uint64_t y,uint64_t z);
uint32_t ps2FieldDoorAtan2Bits_002C0258(uint32_t x,uint32_t z);
uint32_t ps2FieldDoorHeadingBits_002C0B60(void);
void *nocturneResolveFieldDoorMotionAddress(uint32_t address);
#endif

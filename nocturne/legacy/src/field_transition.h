#ifndef NOCTURNE_FIELD_TRANSITION_H
#define NOCTURNE_FIELD_TRANSITION_H
#include <stddef.h>
#include <stdint.h>

/* Native inline request copied as A0 bytes by the original scene callers.
 * Strings retain original unchecked strcpy behavior and store order. */
typedef struct NocturneFieldSceneRequest_PS2 {
    uint8_t unknown_00[0x30];
    uint32_t clear_30, unknown_34, clear_38, clear_3c;
    char point_resource[16];
    uint32_t field, area, enabled, mode;
    uint16_t bgm, clear_62;
    uint32_t camera_mode;
    uint8_t unknown_68[8];
    char camera[16], forced_script[16];
    uint32_t clear_90;
    uint8_t unknown_94[12];
} NocturneFieldSceneRequest_PS2;
_Static_assert(sizeof(NocturneFieldSceneRequest_PS2)==0xa0,"native scene request extent");
_Static_assert(offsetof(NocturneFieldSceneRequest_PS2,field)==0x50,"native destination field");
_Static_assert(offsetof(NocturneFieldSceneRequest_PS2,camera)==0x70,"native inline camera");
_Static_assert(offsetof(NocturneFieldSceneRequest_PS2,forced_script)==0x80,"native forced script");

/* Native low64 arguments occupy A0..A3,T0..T2. Request stores narrow to the
 * native word/halfword; same-field comparison retains the full field register.
 * Return values expose the original V0 observation, although HD declares void. */
uint64_t ps2FieldSetSceneParam2_00121758(uint64_t p,uint64_t field,uint64_t area,uint64_t point);
uint64_t ps2FieldSetSceneParam3_00121840(uint64_t p,uint64_t field,uint64_t area,uint64_t point);
uint64_t ps2FieldSetSceneParam4_00121920(uint64_t p,uint64_t field,uint64_t area,uint64_t point,uint64_t bgm,uint64_t camera_mode,uint64_t camera);
uint64_t ps2FieldSetSceneParam5_00121A20(uint64_t p,uint64_t field,uint64_t area,uint64_t point,uint64_t bgm,uint64_t forced_script);
uint64_t ps2FieldSetSceneParamLoad_00121B10(uint64_t p,uint64_t field,uint64_t area,uint64_t point,uint64_t bgm,uint64_t camera_mode,uint64_t camera);
void *nocturneResolveFieldTransitionAddress(uint32_t address);
uint32_t nocturneFieldTransitionOriginalAddress(const void *address);
#endif

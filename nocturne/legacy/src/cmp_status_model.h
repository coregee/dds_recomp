#ifndef NOCTURNE_CMP_STATUS_MODEL_H
#define NOCTURNE_CMP_STATUS_MODEL_H
#include "nocturne.h"
#include "ee_fpu.h"

/* Recovered original model fields, independently compared against PS2 instructions.
 * Original345F70 table stride44; no table capacity/allocation claim. */
typedef struct cmpModelRecord_PS2 {
    uint8_t motion_number;
    uint8_t unknown_01[7];
    float motion_speed;
    float position[3];
    uint8_t unknown_18[4];
    float rotation[3];
    uint8_t unknown_28[4];
} cmpModelRecord_PS2;
_Static_assert(sizeof(cmpModelRecord_PS2)==44,"original model stride");
_Static_assert(offsetof(cmpModelRecord_PS2,motion_speed)==8,"original speed");
_Static_assert(offsetof(cmpModelRecord_PS2,position)==12,"original position");
_Static_assert(offsetof(cmpModelRecord_PS2,rotation)==28,"original rotation");
extern cmpModelRecord_PS2 *g_cmpModelRows;
extern void *g_cmpStatusModelHandle;
extern uint16_t g_cmpModelMinorNo;
extern uint8_t g_cmpModelMoveMode;

void cmpSetModelMoveMode(int32_t mode);
void *cmpGetStatusModelHandle(void);
int32_t cmpGetModelMinorNo(void);
uint8_t cmpModelTblGetMotNo(uint16_t id);
float cmpModelTblGetMotSpd(uint16_t id);
void cmpModelTblGetPos(uint16_t id,float *output);
void cmpModelTblGetRot(uint16_t id,float *output);
void cmpModelTblSetPos(uint16_t id,int32_t x,int32_t y,int32_t z);
void cmpModelTblSetRot(uint16_t id,int32_t x,int32_t y,int32_t z);

/* Complete stable ordinary RAM rows and12 output bytes. Sequential getter
 * loads/stores retain word-aligned output/table overlaps; no memcpy-all repair.
 * Arithmetic uses ordered raw-word EE operations, not native host casts/add.
 * Synthetic high-index backing does not establish the shipped table capacity. */
#endif

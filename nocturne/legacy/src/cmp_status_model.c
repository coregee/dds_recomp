#include "cmp_status_model.h"
#include <string.h>

/* 0023F8C8 ->18223BA00. Full integer zero predicate; normalized byte0/1. */
void cmpSetModelMoveMode(int32_t mode)
{
    g_cmpModelMoveMode=mode!=0 ? 1u : 0u;
}
/* 0023F8E0 ->182237C10. Opaque original pointer-slot read only. */
void *cmpGetStatusModelHandle(void)
{
    return g_cmpStatusModelHandle;
}
/* 0023F8E8 ->182237BB0. Original LHU result zero extends toint32. */
int32_t cmpGetModelMinorNo(void)
{
    return g_cmpModelMinorNo;
}
/* 0023FB90 ->18223A7E0. Unsigned byte0 of44-byte record. */
uint8_t cmpModelTblGetMotNo(uint16_t id)
{
    return g_cmpModelRows[id].motion_number;
}
/* 0023FBC0 ->18223A870. Raw float word8 transported toF0. */
float cmpModelTblGetMotSpd(uint16_t id)
{
    float value;
    memcpy(&value,&g_cmpModelRows[id].motion_speed,sizeof value);
    return value;
}
static void copy_three_words(float *output,const float *input)
{
    /* Each source word is reread AFTER the preceding output store. Table/output
     * aliasing is observable, so memcpy/memmove of all12 bytes is incorrect. */
    for(uint32_t lane=0;lane<3;++lane) {
        uint32_t word;
        memcpy(&word,(const uint8_t *)input+4*lane,sizeof word);
        memcpy((uint8_t *)output+4*lane,&word,sizeof word);
    }
}
/* 0023FBF0 ->18223A900. Original direct12-byte output, not managed-array ref. */
void cmpModelTblGetPos(uint16_t id,float *output)
{
    copy_three_words(output,g_cmpModelRows[id].position);
}
/* 0023FC40 ->18223AAD0. Original offsets1C/20/24, same sequential stores. */
void cmpModelTblGetRot(uint16_t id,float *output)
{
    copy_three_words(output,g_cmpModelRows[id].rotation);
}
static void add_three_words(float *target,int32_t x,int32_t y,int32_t z)
{
    uint32_t add[3]={EE_FPU_CVT_S_W((uint32_t)x),EE_FPU_CVT_S_W((uint32_t)y),EE_FPU_CVT_S_W((uint32_t)z)};
    for(uint32_t lane=0;lane<3;++lane) {
        uint32_t original;
        memcpy(&original,(uint8_t *)target+4*lane,sizeof original);
        uint32_t result=EE_FPU_ADD_S(original,add[lane]);
        memcpy((uint8_t *)target+4*lane,&result,sizeof result);
    }
}
/* 0023FA98 ->18223B020. Complete original instruction span. All three fullsigned32 conversions precede ordered adds. */
void cmpModelTblSetPos(uint16_t id,int32_t x,int32_t y,int32_t z)
{
    add_three_words(g_cmpModelRows[id].position,x,y,z);
}
/* 0023FB10 ->18223B1E0. Same conversion/add order, rotation fields. */
void cmpModelTblSetRot(uint16_t id,int32_t x,int32_t y,int32_t z)
{
    add_three_words(g_cmpModelRows[id].rotation,x,y,z);
}

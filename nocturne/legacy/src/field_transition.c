/* Original field scene-request builders. Unity fldMain supplies role leads;
 * PS2 instructions establish inline offsets, raw argument widths and order. */
#include "field_transition.h"
#include "field_encounter.h"
#include "event_camera.h"
#include "ps2_memory.h"
#include <string.h>

static uint8_t *at(uint32_t a){return nocturneResolveFieldTransitionAddress(a);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void half(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t original_pointer(const void *p){return sx(nocturneFieldTransitionOriginalAddress(p));}
static uint64_t clear16(uint32_t a){return original_pointer(ps2Memset(at(a),0,16));}
static uint64_t copy(uint32_t a,uint64_t s){return original_pointer(ps2Strcpy((char *)at(a),(const char *)at((uint32_t)s)));}

static void reuse_or_reset(uint64_t field)
{
    if(dds3SearchProcessName(0x531690u)){
        if(sx(word(0x2fbf84u))==field)put(0x2fc028u,1);
        else ps2FieldEncounterReset_0028CFB0();
    }
}
static void head(uint32_t p,uint64_t point)
{
    put(p+0x30u,0);put(p+0x3cu,0);put(p+0x38u,0);(void)copy(p+0x40u,point);
}

uint64_t ps2FieldSetSceneParam2_00121758(uint64_t request,uint64_t field,uint64_t area,uint64_t point)
{
    uint32_t p=(uint32_t)request;reuse_or_reset(field);head(p,point);
    put(p+0x50u,(uint32_t)field);put(p+0x5cu,2);put(p+0x54u,(uint32_t)area);
    put(p+0x58u,1);half(p+0x60u,0);half(p+0x62u,0);put(p+0x64u,0);
    (void)clear16(p+0x70u);(void)clear16(p+0x80u);put(p+0x90u,0);
    *at(0x54ede4u)=0;*at(0x303040u)=0;
    return 0x300000u; /* Native epilogue LUI V0,0030 before the byte store. */
}
uint64_t ps2FieldSetSceneParam3_00121840(uint64_t request,uint64_t field,uint64_t area,uint64_t point)
{
    uint32_t p=(uint32_t)request;reuse_or_reset(field);head(p,point);
    put(p+0x50u,(uint32_t)field);put(p+0x5cu,3);put(p+0x54u,(uint32_t)area);
    put(p+0x58u,1);half(p+0x60u,0);half(p+0x62u,0);put(p+0x64u,0);
    (void)clear16(p+0x70u);uint64_t result=clear16(p+0x80u);put(p+0x90u,0);return result;
}
uint64_t ps2FieldSetSceneParam4_00121920(uint64_t request,uint64_t field,uint64_t area,uint64_t point,uint64_t bgm,uint64_t camera_mode,uint64_t camera)
{
    uint32_t p=(uint32_t)request;reuse_or_reset(field);head(p,point);
    put(p+0x50u,(uint32_t)field);put(p+0x5cu,2);put(p+0x54u,(uint32_t)area);
    half(p+0x60u,(uint16_t)bgm);put(p+0x64u,(uint32_t)camera_mode);put(p+0x58u,1);half(p+0x62u,0);
    (void)copy(p+0x70u,camera);uint64_t result=clear16(p+0x80u);put(p+0x90u,0);return result;
}
uint64_t ps2FieldSetSceneParam5_00121A20(uint64_t request,uint64_t field,uint64_t area,uint64_t point,uint64_t bgm,uint64_t forced_script)
{
    uint32_t p=(uint32_t)request;reuse_or_reset(field);head(p,point);
    put(p+0x50u,(uint32_t)field);put(p+0x5cu,2);put(p+0x54u,(uint32_t)area);
    half(p+0x60u,(uint16_t)bgm);put(p+0x58u,1);half(p+0x62u,0);put(p+0x64u,0);
    (void)clear16(p+0x70u);uint64_t result=copy(p+0x80u,forced_script);put(p+0x90u,0);return result;
}
uint64_t ps2FieldSetSceneParamLoad_00121B10(uint64_t request,uint64_t field,uint64_t area,uint64_t point,uint64_t bgm,uint64_t camera_mode,uint64_t camera)
{
    uint32_t p=(uint32_t)request;head(p,point);
    put(p+0x58u,1);put(p+0x50u,(uint32_t)field);put(p+0x54u,(uint32_t)area);
    half(p+0x60u,(uint16_t)bgm);put(p+0x64u,(uint32_t)camera_mode);put(p+0x5cu,2);half(p+0x62u,0);
    (void)copy(p+0x70u,camera);uint64_t result=clear16(p+0x80u);put(p+0x90u,0);return result;
}

/* Original field input-release closure. The movement distance/VU caller and
 * input registration/collision solver are separate unrecovered owners. */
#include "field_input_release.h"
#include "path_control.h"
#include "kernel_event_neighbors.h"
#include <string.h>
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveFieldInputReleaseAddress(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(nocturneResolveFieldInputReleaseAddress(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t ps2FieldGetUnitControl_001225E8(void){return 0x2fc350u;}
uint64_t ps2MoverSetPrimaryControl_0010FED0(uint64_t mover,uint64_t function)
{
    uint32_t data=word((uint32_t)mover+0x18u);
    put(data+8u,(uint32_t)function);
    return sx(data);
}
uint64_t ps2ObjectSetPrimaryControl_001121D8(uint64_t object,uint64_t function)
{
    uint64_t mover=dds3ObjectBaseGetControlBasic(object,1);
    if(!mover)return 0;
    (void)ps2MoverSetPrimaryControl_0010FED0(mover,function);
    return 1;
}
uint64_t ps2FieldReleaseUnitPad_00122718(void)
{
    uint32_t work=(uint32_t)ps2FieldGetUnitControl_001225E8();
    if(word(work)){
        fldProcOffFlag(0x40);
        (void)ps2ObjectSetPrimaryControl_001121D8(sx(word(work)),0);
    }
    put(0x2fbfdcu,4);
    return 4;
}

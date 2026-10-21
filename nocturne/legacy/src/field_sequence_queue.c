/* Native administrative request ownership consumed by field transitions.
 * The HD managed reference does not replace the original allocation/copy. */
#include "field_sequence_queue.h"
#include "event_camera.h"
#include "process_lists.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t a){return nocturneResolveFieldSequenceQueueAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t ps2FieldSequenceGetData_00102800(void)
{
    return dds3GetProcessData(dds3SearchProcessName(0x54e8c8u));
}
uint64_t ps2FieldSequenceQueue_00102848(uint64_t sequence,uint64_t data,uint64_t size,uint64_t restore)
{
    if(data&&size>=257u)return 0;
    uint32_t p=(uint32_t)ps2FieldSequenceGetData_00102800();
    uint32_t flags=word(p),previous=word(p+0x1cu);
    *at(p+9u)=(uint8_t)sequence;*at(p+0x21u)=2;
    put(p,(flags|1u)&0xfffefff7u);
    if(previous){ps2PoolRelease(previous);put(p+0x1cu,0);*at(p+0x20u)=0;}
    if(!data){put(p+0x1cu,0);*at(p+0x20u)=0;}
    else{
        uint32_t destination=ps2PoolAllocate((int32_t)(uint32_t)size);
        put(p+0x1cu,destination);
        (void)ps2Memcpy(at(destination),at((uint32_t)data),(uint32_t)size);
        *at(p+0x20u)=(uint8_t)size;
    }
    flags=word(p);flags=restore?flags|4u:flags&0xfffffffbu;put(p,flags);
    return sx(flags);
}

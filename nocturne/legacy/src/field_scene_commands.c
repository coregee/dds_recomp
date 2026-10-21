/* Actual CALL_FIELD2/3 consumers. The original A0-byte request retains its
 * incoming stack prefix/holes/tail; no managed/default-zero object is invented. */
#include "field_scene_commands.h"
#include "field_transition.h"
#include "field_sequence_queue.h"
#include "script_movie.h"
#include "script_core.h"
#include "script_lifetime.h"
#include <string.h>
static uint64_t field(void)
{
    uint32_t v;memcpy(&v,nocturneResolveFieldSceneCommandsAddress(0x2fbf84u),4);
    return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;
}
uint64_t ps2FieldCallField2_001E7378(void)
{
    uint32_t request=nocturneFieldSceneCommandsIncomingStack()-0xb0u;
    uint64_t area=scrGetIntPara(0),point=scrGetStrPara(1);
    (void)ps2FieldSetSceneParam2_00121758(request,field(),area,point);
    (void)ps2FieldSequenceQueue_00102848(6,request,0xa0,0);
    (void)scrAllReleaseScript();return 1;
}
uint64_t ps2FieldCallField3_001E73E0(void)
{
    uint32_t request=nocturneFieldSceneCommandsIncomingStack()-0xb0u;
    uint64_t area=scrGetIntPara(0),point=scrGetStrPara(1);
    (void)ps2FieldSetSceneParam3_00121840(request,field(),area,point);
    (void)ps2FieldSequenceQueue_00102848(6,request,0xa0,0);
    (void)scrAllReleaseScript();return 1;
}

/* Original CALL_FIELD and field BGM submission. Sound rendering/IOP execution
 * remains downstream of the real canonical ring and syscall boundary. */
#include "field_bgm_transition.h"
#include "field_transition.h"
#include "field_sequence_queue.h"
#include "script_movie.h"
#include "script_core.h"
#include "script_lifetime.h"
#include "movie_draw.h"
#include <string.h>
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveFieldBgmTransitionAddress(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(nocturneResolveFieldBgmTransitionAddress(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t ps2SoundFadeOut_002C2070(uint64_t midi)
{
    uint32_t packet=nocturneFieldBgmTransitionStack()-0x20u;
    put(packet,(uint32_t)midi);
    return ps2MovieCommandEnqueue(0xd0,0,packet,16);
}
uint64_t ps2FieldBgmFadeOut_001452F0(void)
{
    uint32_t sp=nocturneFieldBgmTransitionStack();
    uint64_t midi=sx(word(0x54ee24u));
    nocturneFieldBgmTransitionSetStack(sp-0x10u);
    (void)ps2SoundFadeOut_002C2070(midi);
    nocturneFieldBgmTransitionSetStack(sp);
    uint32_t state=word(0x2fc020u);
    if(state<0x80000000u&&state>=128u)put(0x2fc020u,1);
    put(0x54ee24u,0);
    return 1;
}
uint64_t ps2FieldCallField_001E72F8(void)
{
    uint32_t sp=nocturneFieldBgmTransitionStack(),request=sp-0xc0u;
    nocturneFieldBgmTransitionSetStack(request);
    (void)ps2FieldBgmFadeOut_001452F0();
    nocturneFieldBgmTransitionSetStack(sp);
    uint64_t field=scrGetIntPara(0),area=scrGetIntPara(1),point=scrGetStrPara(2);
    (void)ps2FieldSetSceneParam2_00121758(request,field,area,point);
    (void)ps2FieldSequenceQueue_00102848(6,request,0xa0,0);
    (void)scrAllReleaseScript();
    return 1;
}

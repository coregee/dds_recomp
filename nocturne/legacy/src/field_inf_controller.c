/* Draft original mutating INF/ToWAP controller. Original instructions own
 * offsets,narrowing,call order and side effects; no staged validation yet.
 * The remaining camera/player/battle owners are external declarations,not
 * synthesized outcomes. Do not link until their complete closure is recovered. */
#include "field_inf_controller.h"
#include "field_inf_graph.h"
#include "field_door_motion.h"
#include "scene_lookup.h"
#include "event_camera.h"
#include "event_kuti.h"
#include "script_process.h"
#include "script_construction.h"
#include "script_lifetime.h"
#include "libc_printf.h"
#include "nocturne.h"
#include <string.h>

static uint8_t *at(uint32_t p){return nocturneResolveFieldInfControllerAddress(p);}
static uint16_t r16(uint32_t p){uint16_t v;memcpy(&v,at(p),2);return v;}
static uint32_t r32(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void w16(uint32_t p,uint16_t v){memcpy(at(p),&v,2);}
static void w32(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t lb(uint32_t p){uint32_t v=*at(p);return v&0x80u?v|0xffffff00u:v;}
static uint32_t lh(uint32_t p){uint32_t v=r16(p);return v&0x8000u?v|0xffff0000u:v;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static int below(uint64_t v,uint64_t bound){return(v>>63)!=0||v<bound;}
static uint32_t message(uint32_t row,uint32_t line){return 0x2fff00u+row*312u+(line-10u)*14u;}
static void restore_camera(void)
{
    uint32_t mode=r32(0x2fbf98u);
    if(mode==0||mode==3)ps2FieldControllerResetNormal_0012CA30();
    else if(mode==1)ps2FieldControllerResetPlayer_0012DDF8();
}

/* Full native raw64 return; invalid-data/name diagnostics execute real printf.
 * PS2 priority1002 is literal. No HD managed copy/player-animation is inserted. */
uint64_t ps2SceneStartNamedScript_0010F4D8(uint64_t scene,uint64_t name)
{
    uint32_t data=r32(r32((uint32_t)scene+0x18u)+0x1cu);
    if(!data){(void)ps2LibcPrintf(0x52f770u);return 0;}
    if(!name){(void)ps2LibcPrintf(0x52f788u,name);return 0;}
    uint64_t procedure=scrSearchProcedureName(sx(data),name);
    if(procedure>>63){(void)ps2LibcPrintf(0x52f7a0u,name);return 0;}
    if(dds3SearchProcessName(name))return 0;
    return scrStartScript2(1002,sx(data),procedure);
}

void ps2FieldInfToWap_00140CF0(void)
{
    uint32_t slot=r32(0x54eddcu)*4u;
    w32(0x54ede0u,1);
    uint32_t hit=r32(0x2fcda0u+slot);
    uint64_t label=ps2FieldInfFindWarp_00140F48(sx(r32(hit+8u)));
    if(scrSearchScriptName(label))return;
    uint64_t scene=dds3GetActiveScene();
    uint64_t handle=ps2SceneStartNamedScript_0010F4D8(scene,label);
    w32(0x2fcea0u+slot,(uint32_t)handle);
}

uint64_t ps2FieldInfNext_001405B0(uint64_t line,uint64_t selection)
{
    uint32_t source_index,row=r32(0x54edd8u),next;
    if(below(line,10)){
        source_index=(uint32_t)line-1u;
        uint32_t p=0x2ffef0u+row*312u+source_index*4u,event=lh(p);
        if(!event)next=lb(p+2u);
        else{
            uint32_t yes=evtBitCheck(si(event));row=r32(0x54edd8u);
            next=lb(0x2ffef0u+row*312u+source_index*4u+(yes?3u:2u));
        }
    }else{
        source_index=(uint32_t)line-10u;
        next=lb(0x2fff04u+row*312u+source_index*14u+(uint32_t)selection);
    }
    /* Native signedbyte target100 has no HD exclusion here. */
    int target_message=si(next)>=10;
    if(target_message){
        uint32_t p=message(row,next),event=lh(p+8u);
        if(event){evtBitOff(si(event));row=r32(0x54edd8u);}
        event=lh(message(row,next)+10u);
        if(event)evtBitOn(si(event));
    }
    uint64_t scene=dds3GetActiveScene();
    if(target_message){
        row=r32(0x54edd8u);
        uint32_t extra=lb(message(row,next)+13u);
        if(extra){
            uint32_t p=0x2ffbc0u+extra*20u;
            switch(lh(p)){
            case 1:ps2FieldControllerRecover_0013C6F0();break;
            case 2:datAddItem(si(r32(p+4u)),si(r32(p+8u)));break;
            case 3:datAddMaka(si(r32(p+4u)));break;
            default:break;
            }
        }
    }
    uint32_t start=target_message?lb(message(r32(0x54edd8u),next)+12u):0;
    if(start){
        uint32_t offset=start*32u;
        uint32_t player=r32(0x54eae8u);
        if(r32(r32(player+0x18u)+8u)){
            if(r32(0x2ff6c0u+offset))ps2FieldControllerPlayerOn_00134E48();
            else ps2FieldControllerPlayerOff_00134DF8();
        }
        if(*at(0x2ff6c8u+offset)){
            uint64_t object=dds3SceneBasicSearchName(scene,0x2ff6c8u+offset);
            if(object)ps2FieldControllerPositionPlayer_001E1688(sx(r32(r32(0x54eae8u)+4u)),sx(r32((uint32_t)object+4u)));
        }
        if(*at(0x2ff6d4u+offset)){
            uint64_t object=dds3SceneBasicSearchName(scene,0x2ff6d4u+offset);
            if(object){
                uint64_t camera=dds3SearchSceneBasic(scene,sx(r32((uint32_t)object+4u)),4);
                if(camera)(void)dds3SetActiveCameraSceneBasic(scene,camera);
            }
        }else if(ps2FieldControllerEventCamera_0012EFD8()){
            uint64_t camera=fldGetUnitFollowCamera();
            (void)dds3SetActiveCameraSceneBasic(scene,camera);
            restore_camera();
        }
    }
    if(next)return sx(next);
    /* When incoming line<10,the native flag index is reused as a message
     * index for this terminal extra lookup; retain that unchecked layout. */
    row=r32(0x54edd8u);
    uint32_t extra=lb(0x2fff0du+source_index*14u+row*312u);
    if(extra&&lh(0x2ffbc0u+extra*20u)==4){
        (void)scrAllReleaseScript();
        extra=lb(0x2fff0du+source_index*14u+r32(0x54edd8u)*312u);
        uint32_t p=0x2ffbc0u+extra*20u,encounter=r32(p+4u),wait=r32(p+8u);
        ps2FieldControllerProcNext_00125CB8(sx(r32(0x2fbf84u)),sx(encounter));
        ps2FieldControllerBattle_001E7228(sx(encounter));
        if(sx(wait)==1)w32(0x2fc04cu,wait);
        return sx(encounter+200u);
    }
    uint32_t control=r32(r32(r32(0x54eae8u)+0x18u)+8u);
    if(control){uint32_t flags=r32(control+0x8cu);w32(flags,r32(flags)&0xfffffffeu);}
    if(ps2FieldControllerEventCamera_0012EFD8())restore_camera();
    return 0;
}

void ps2FieldControllerProcNext_00125CB8(uint64_t field,uint64_t event)
{
    w32(0x54eb78u,(uint32_t)field);w32(0x54eb7cu,(uint32_t)event);
    if(field==14&&event==603)w32(0x54eb50u,1);
}

uint64_t ps2FieldControllerEventCamera_0012EFD8(void)
{
    uint64_t scene=dds3GetActiveScene();
    uint64_t camera=dds3GetActiveCameraSceneBasic(scene);
    uint64_t follow=fldGetUnitFollowCamera();
    return camera==follow?0:camera;
}

void ps2FieldInteractionInit_0013C860(void)
{
    w32(0x54edb8u,0);w32(0x54edc8u,0);w32(0x54edccu,0);
    for(uint32_t row=0;row<64;row++){
        uint32_t p=0x55dc30u+row*0x130u;
        for(uint32_t v=0;v<8;v++){
            w32(p+v*16u,0);w32(p+v*16u+4u,0);w32(p+v*16u+8u,0);w32(p+v*16u+12u,0x3f800000u);
        }
        w32(p+0x80u,0);w32(p+0x84u,0);w32(p+0x88u,0);w32(p+0x8cu,0x3f800000u);
        for(uint32_t v=0;v<6;v++){
            uint32_t q=p+0x90u+v*16u;
            w32(q,0);w32(q+4u,0);w32(q+8u,0);w32(q+12u,0x3f800000u);w32(p+0xf0u+v*4u,0);
        }
        w32(0x2fcea0u+row*4u,0);
        for(uint32_t offset=0x108;offset<=0x11c;offset+=4)w32(p+offset,0);
        w16(p+0x120u,0);w16(p+0x122u,0xffff);w16(p+0x124u,0xffff);w16(p+0x126u,0);
        w16(p+0x128u,0xffff);w16(p+0x12au,0);w32(p+0x12cu,0);
    }
    w32(0x54edd4u,0);
    const uint32_t sentinels[]={0x54edc4u,0x54edb0u,0x54edb4u,0x54edbcu,0x54edc0u};
    for(unsigned i=0;i<sizeof(sentinels)/sizeof(sentinels[0]);i++)w32(sentinels[i],0xffffffffu);
    ps2FieldDoorInit_00142FB0();
}

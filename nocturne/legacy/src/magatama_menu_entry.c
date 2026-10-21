/* Seven complete original Magatama entry/resource/snapshot owners,1020B.
 * Actual allocation,queued file requests,icon initializer,equip and input
 * sound dependencies remain. Request completion is not fabricated here. */
#include "magatama_menu_entry.h"
#include "magatama_menu_runtime.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "file_worker_control.h"
#include "shop_payment_controller.h"
#include "shop_selection.h"
#include "hearts_menu.h"
#include "nocturne.h"
#include "ps2_memory.h"
#include "libc_printf.h"
#include <string.h>

static uint8_t *at(uint32_t a)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMagatamaMenuEntryAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r8(uint32_t a){return *at(a);}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint32_t v){*at(a)=(uint8_t)v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t sb(uint32_t v){return(v&128u)?(v&255u)|0xffffff00u:v&255u;}
static uint64_t sx(uint32_t v){return(v>>31)?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
static uint32_t work(void){return r32(0x551fb0);}

void ps2MagatamaMessagePositionSet_00213FB8(uint64_t position)
{
    if(si(r32(0x54fc50))>=0)w8(0x54fc5c,(uint32_t)position);
}
uint64_t ps2MagatamaMessagePositionGet_00213FD8(void)
{
    return sx(sb(r8(0x54fc5c)));
}
uint64_t ps2MagatamaRequestLoad_002144B8(uint64_t path,uint64_t slot)
{
    /* The genuine callback pointer2144A0 is queued,not called here. Its
     * asynchronous owner must be recovered/entered separately. */
    return ps2FileRequestLoad(path,0,UINT64_MAX,0x2144a0,slot);
}
void ps2MagatamaLoadResources_00232AE8(uint64_t data)
{
    uint32_t d=(uint32_t)data;
    (void)ps2MagatamaRequestLoad_002144B8(0x53fd00,sx(d+0x116c));
    (void)ps2MagatamaRequestLoad_002144B8(0x53fd18,sx(d+0x1170));
    (void)ps2MagatamaRequestLoad_002144B8(0x53fd30,sx(d+0x1174));
    (void)ps2LibcPrintf(0x53fd48);
}
uint64_t ps2MagatamaInitialize_00232EC0(uint64_t parent)
{
    uint32_t data=r32(0x54fe78);
    if(!data){
        uint32_t handle=ps2MemoryHandleAllocate(0x1f8c);
        data=ps2MemoryHandleAcquirePointer(handle);
        (void)ps2Memset(at(data),0,0x1f8c);
        w32(data+0x14,handle);w32(data+0x2c,256);
        ps2MagatamaLoadResources_00232AE8(sx(data));
        w32(data+0x1c,0);
    }else w32(data+0x1c,0);
    w32(data+0x20,0);w32(data+0x24,0);
    ps2ShopSequenceInitialize_002427D8(sx(data),parent);
    w8(data,r8(data)&0xfeu);
    cmpSetEquipHeartsSelectPos((cmpDataDH_PS2 *)at(data));
    cmpInitHeartsIcon((cmpDataDH_PS2 *)at(data));
    ps2MagatamaInfoInitialize_00232E90(sx(data));
    ps2MagatamaPadActionHook_00232878(sx(sb(r8(data+0x1280u+sb(r8(data+0x31))*52u))));
    w8(data+0x30,(uint32_t)ps2MagatamaMessagePositionGet_00213FD8());
    ps2MagatamaMessagePositionSet_00213FB8(0);w8(data+4,0);
    /* Original233010 publishes this return to the shared slot;the tested
     * initializer itself does not manufacture that caller's later store. */
    return sx(data);
}
void ps2MagatamaTerminate_002330D8(void)
{
    uint32_t data=r32(0x54fe78);if(data)w8(data,r8(data)|0x10u);
}
static void snapshotPlayer(void)
{
    uint32_t data=work(),game=r32(0x54ea20);
    w8(data+0x32,r8(game+0x1cfa));
    uint32_t src=game+0xa54,dst=work()+0x34,end=game+0xb34;
    do{uint8_t block[32];memcpy(block,at(src),32);memcpy(at(dst),block,32);src+=32;dst+=32;}while(src!=end);
    uint8_t tail[12];memcpy(tail,at(src),8);memcpy(tail+8,at(src+8),4);memcpy(at(dst),tail,8);memcpy(at(dst+8),tail+8,4);
}
void ps2MagatamaRootUpdate_00234FD0(void)
{
    uint32_t key=(uint16_t)ps2ShopCommonInput_002411B0(0xf3);
    if(!ps2MagatamaTextureReady_00232A28())return;
    w8(work(),r8(work())|1u);
    if(key==1){
        uint64_t state=ps2MagatamaAttachStatus_00234DC8();
        if(state==1)key=0x8000;
        else if(state==0||state==2||state==3||state==4){
            w8(work()+0x18,0);snapshotPlayer();
            ps2MagatamaEquipSelection_00234F80();
            w8(work()+1,1);w8(work()+4,1);
        }
    }else if(key==2)ps2MagatamaTerminate_002330D8();
    else if(key==0x10||key==0x20||key==0x40||key==0x80)ps2MagatamaCursorMove_00234BF0(key);
    /* Native root restores its S0/RA and tailcalls this real shared owner.
     * A host proof must transport the actual caller frame,not supply sound
     * success or reuse another API's packet padding assumptions. */
    ps2ShopInputSound_002413A0(key);
}

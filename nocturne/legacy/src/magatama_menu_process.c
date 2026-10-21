/* Ten complete indexed menu start/shutdown/resource owners,920B.
 * Indexed credit remains separate from prior raw frame variants and the
 * separate unindexed20B completion callback. No service return is supplied. */
#include "magatama_menu_process.h"
#include "magatama_menu_entry.h"
#include "process_creation.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "movie_decoder.h"
#include "libc_printf.h"
#include <string.h>
static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMagatamaMenuProcessAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r8(uint32_t a){return *at(a);}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint32_t v){*at(a)=(uint8_t)v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
void ps2CampMenuSuspend_00232550(uint64_t suspend)
{
    uint32_t p=r32(0x54fe74);
    if(p){uint32_t flags=r8(p);w8(p,(suspend&255u)?flags|2u:flags&0xfdu);}
}
uint64_t ps2MagatamaProcessStart_00233010(uint64_t parent)
{
    uint64_t data=ps2MagatamaInitialize_00232EC0(parent);
    /* The actual23302C delay store publishes the real constructor result.
     * This source never writes a guessed address after initialization. */
    w32(0x54fe78,(uint32_t)data);
    ps2CampMenuSuspend_00232550(0);
    uint64_t calc=dds3StartProcess(0x53fd90,0x3f0,1,1,0x233270,0,sx(r32(0x54fe78)));
    (void)dds3StartProcess(0x53fda0,0x2b05,1,1,0x234b58,0,sx(r32(0x54fe78)));
    (void)dds3StartProcess(0x53fdb0,0x5209,1,1,0x235c50,0x232fc0,sx(r32(0x54fe78)));
    return calc;
}
void ps2CampInfoTerminate_0023B4E0(void)
{
    uint32_t p=r32(0x54fec8);if(p)w8(p,r8(p)|0x10u);
}
void ps2CampInfoHide_00230518(void){ps2CampInfoTerminate_0023B4E0();}
uint64_t ps2VramBlockMergePrevious_002AA718(uint64_t raw)
{
    uint32_t p=(uint32_t)raw,previous=r32(p+4);
    if(!previous||r32(previous+8))return 0;
    uint32_t older=r32(previous+4);
    w32(p+0x10,r32(p+0x10)+r32(previous+0x10));
    w32(p+4,older);
    if(older)w32(r32(previous+4),p);else w32(0x552094,p);
    ps2PoolRelease(previous);return 1;
}
void ps2VramBlockFree_002AA7F0(uint64_t raw)
{
    if(!raw)return;
    uint32_t p=(uint32_t)raw,restore=ps2KernelDisableInterrupts();
    w32(p+8,0);(void)ps2VramBlockMergePrevious_002AA718(raw);
    uint32_t next=r32(p);
    if(next&&!r32(next+8))(void)ps2VramBlockMergePrevious_002AA718(sx(next));
    if(restore)(void)ps2KernelEnableInterrupts();
}
void ps2TextureImmediateFree_002AB860(uint64_t raw)
{
    if(!raw)return;
    uint32_t t=(uint32_t)raw;
    if(!r32(t+8))ps2VramBlockFree_002AA7F0(sx(r32(t+0x10)));
    ps2VramBlockFree_002AA7F0(sx(r32(t+0x14)));
    ps2PoolRelease(r32(t+0x28));ps2PoolRelease(r32(t+0x2c));
    uint32_t previous=r32(t+4),next=r32(t);
    if(previous)w32(previous,next);
    if(next)w32(next+4,previous);else w32(0x551860,previous);
    ps2PoolOrMemoryPointerFree(sx(r32(t+0x30)));
    ps2PoolOrMemoryPointerFree(sx(r32(t+0x3c)));
    ps2PoolRelease(t);
}
void ps2MagatamaTexturesFree_00232B40(uint64_t raw)
{
    uint32_t p=(uint32_t)raw;
    for(uint32_t offset=0x1160;offset<0x116c;offset+=4){
        uint32_t texture=r32(p+offset);
        if(texture){ps2TextureImmediateFree_002AB860(sx(texture));w32(p+offset,0);}
    }
    (void)ps2LibcPrintf(0x53fd60);
}
void ps2MagatamaResourcesFree_00232BB0(uint64_t raw)
{
    uint32_t p=(uint32_t)raw;ps2MagatamaTexturesFree_00232B40(raw);
    /* Native pointer-free doesnot accept a fabricatedNULLsuccess: its real
     * FindPointer traversal can stay pending when no allocatedowner matches.
     * Returnable shutdown worlds require three genuinely owned filebuffers. */
    for(uint32_t offset=0x116c;offset<0x1178;offset+=4){
        ps2MemoryPointerFree(sx(r32(p+offset)));w32(p+offset,0);
    }
    (void)ps2LibcPrintf(0x53fd78);
}
void ps2MagatamaProcessShutdown_00232FC0(void)
{
    uint32_t p=r32(0x54fe78);if(!p)return;
    ps2MagatamaMessagePositionSet_00213FB8(sx((r8(p+0x30)&128u)?r8(p+0x30)|0xffffff00u:r8(p+0x30)));
    ps2CampMenuSuspend_00232550(1);ps2CampInfoHide_00230518();
    ps2MagatamaResourcesFree_00232BB0(sx(r32(0x54fe78)));
    ps2MemoryHandleFree(r32(r32(0x54fe78)+0x14));w32(0x54fe78,0);
}

/* Reconstructed original PS2 draw-environment callers and global stores. */
#include "draw_environment.h"
#include <string.h>
#include "heap_queue.h"
#include "render_chain.h"
#include "ordering_flush.h"
#include "deferred_drain.h"
#include "packet_builders.h"
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveHeapAddress(a),4);return v;}
static uint32_t half_signed(uint32_t a){uint16_t v;memcpy(&v,nocturneResolveHeapAddress(a),2);return v|((v&UINT16_C(0x8000))?UINT32_C(0xffff0000):0);}
static uint32_t byte(uint32_t a){uint8_t v;memcpy(&v,nocturneResolveHeapAddress(a),1);return v;}
static void put32(uint32_t a,uint32_t v){memcpy(nocturneResolveDrawGlobalAddress(a),&v,4);}
static void put64(uint32_t a,uint64_t v){memcpy(nocturneResolveHeapAddress(a),&v,8);}
static void put8(uint32_t a,uint8_t v){memcpy(nocturneResolveHeapAddress(a),&v,1);}
void ps2DrawBuildSingleRegisterGroup(uint32_t dst,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6,uint64_t p7,uint32_t context)
{
    ps2DrawInitializeInlineRegisterPacket(dst,5);
    ps2DrawBuildRegisterGroupPacket(dst+32,p2,p3,p4,p5,p6,p7,0,context);
}
static void pair_tail(uint32_t dst,uint32_t base)
{
    put64(dst+base+8,UINT64_C(0x47));put64(dst+base+24,UINT64_C(0x42));
    put64(dst+base+32,UINT64_C(0x517fb));put64(dst+base+40,UINT64_C(0x48));
    put64(dst+base+48,UINT64_C(0x44));put64(dst+base+56,UINT64_C(0x43));
    put64(dst+base,UINT64_C(0x517fb));put64(dst+base+16,UINT64_C(0x44));
}
void ps2DrawBuildConfiguredEnvironment(uint32_t dst,uint32_t config,uint32_t index)
{
    uint32_t selected=config+(index<<2);
    ps2DrawInitializeInlineRegisterPacket(dst,21);
    uint32_t frame=word(word(selected+8)+12),depth=word(word(config+16)+12);
    uint32_t width=half_signed(config),format=byte(config+6),height=half_signed(config+4),depth_format=byte(config+7);
    uint32_t mode=byte(UINT32_C(0x55188a));
    ps2DrawBuildRegisterGroupPacket(dst+96,frame,width,height,format,depth,depth_format,mode,0);
    mode=byte(UINT32_C(0x55188a));
    ps2DrawBuildRegisterGroupPacket(dst+160,frame,width,height,format,depth,depth_format,mode,1);
    /* Original reloads config fields after both packet calls. */
    depth_format=byte(config+7);width=half_signed(config);height=half_signed(config+4);format=byte(config+6);
    (void)depth_format;(void)format;
    ps2DrawBuildOffsetRangePacket(dst+224,width,height);
    pair_tail(dst,304);
    ps2DrawBuildFixedStatePacket(dst+32);
}
void ps2DrawInitializeEnvironmentRecord(uint32_t dst,uint32_t config)
{
    ps2DrawInitializeInlineRegisterPacket(dst+16,21);
    put32(dst+8,config);
    uint32_t width=half_signed(config);
    put32(dst+4,UINT32_C(0x2ad568));
    uint32_t height=half_signed(config+4),depth_format=byte(config+7),format=byte(config+6);
    (void)depth_format;(void)format;
    ps2DrawBuildOffsetRangePacket(dst+240,width,height);
    pair_tail(dst,320);
    ps2DrawBuildFixedStatePacket(dst+48);
}
void ps2DrawLinkEnvironmentRecord(uint32_t chain,uint32_t list,uint32_t record)
{
    ps2DrawNodeListAppend(list,record);
    ps2DmaChainAppend(chain,record+16);
}
void ps2DrawBuildContextReference180(uint32_t src,uint32_t dst,uint64_t context)
{ps2DrawInitializeReferencedRegisterPacket(dst,(uint64_t)(src+(context?UINT32_C(0x190):UINT32_C(0x180))),1);}
void ps2DrawBuildContextReference70(uint32_t src,uint32_t dst,uint64_t context)
{ps2DrawInitializeReferencedRegisterPacket(dst,(uint64_t)(src+(context?UINT32_C(0xb0):UINT32_C(0x70))),1);}
static void reference_four(uint32_t chain,uint32_t src,uint32_t packet,uint32_t offset)
{
    uint64_t ref=UINT64_C(0x30000004)|((uint64_t)((src+offset)&UINT32_C(0x0fffffff))<<32);
    put64(packet+8,UINT64_C(0x5000000410000000));put64(packet,ref);
    put64(packet+16,0);put64(packet+24,0);
    ps2DrawTagAppendReference(chain,packet);
}
void ps2DrawAppendStateReference1a0(uint32_t chain,uint32_t src,uint32_t packet)
{reference_four(chain,src,packet,UINT32_C(0x1a0));}
void ps2DrawAppendStateReference1e0(uint32_t chain,uint32_t src,uint32_t packet)
{reference_four(chain,src,packet,UINT32_C(0x1e0));}
void ps2DrawInitializeAuxiliaryRecord(uint32_t dst,uint32_t p2,uint32_t p3,uint32_t p4,uint32_t p5)
{
    ps2DrawInitializeInlineRegisterPacket(dst+16,2);
    put32(dst+92,p5);put32(dst+80,p2);put32(dst+84,p3);put32(dst+88,p4);put32(dst+4,UINT32_C(0x2ad950));
}
void ps2DrawStoreNonnegativeModeByte(uint64_t value)
{put8(UINT32_C(0x55188b),(uint8_t)((value&UINT64_C(0x8000000000000000))?0:value));}
void ps2DrawResetGlobalState(void)
{put8(UINT32_C(0x55188b),0);put32(UINT32_C(0x5293f8),0);put32(UINT32_C(0x551890),0);}

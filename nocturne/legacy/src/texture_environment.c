/* Reconstructed original PS2 texture packets and installed environment callback. */
#include "texture_environment.h"
#include <string.h>
#include "heap_queue.h"
#include "packet_builders.h"
#include "material_fiveword_pool.h"
static uint64_t sx32(uint32_t v){return (uint64_t)v|((v&UINT32_C(0x80000000))?UINT64_C(0xffffffff00000000):0);}
static uint32_t asr32(uint32_t v,unsigned n){return(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32-n)):0);}
static void put64(uint32_t a,uint64_t v){memcpy(nocturneResolveHeapAddress(a),&v,8);}
static uint32_t get32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveHeapAddress(a),4);return v;}
static uint32_t get16(uint32_t a){uint16_t v;memcpy(&v,nocturneResolveHeapAddress(a),2);return v;}
static uint32_t signed16(uint32_t a){uint32_t v=get16(a);return v|((v&0x8000)?UINT32_C(0xffff0000):0);}
static uint32_t get8(uint32_t a){uint8_t v;memcpy(&v,nocturneResolveHeapAddress(a),1);return v;}
void ps2DrawBuildTextureRegisterGroup(uint32_t dst,uint32_t width,uint32_t height,uint32_t address,uint32_t format,uint64_t palette,uint64_t paletteMode,uint64_t functionMode,uint32_t filter,uint32_t filterValue,uint32_t clamp,uint32_t context)
{
    uint64_t pitch=sx32(asr32(width,6)<<14),tw=sx32((31-EE_MMI_LEADING_SIGN_WORD(width-1))<<26);
    uint64_t th=sx32(31-EE_MMI_LEADING_SIGN_WORD(height-1))<<30,fmt=sx32(format<<20);
    uint64_t paletteAddress=sx32(asr32((uint32_t)palette,6))<<37;
    uint64_t paletteBits=paletteMode<<51,mode=functionMode<<34;
    uint64_t value=paletteBits|pitch|mode|tw|sx32(asr32(address,6))|th|fmt|paletteAddress;
    put64(dst+8,14);put64(dst,UINT64_C(0x1000000000008003));
    uint64_t f=filter?(sx32(filter<<2)|((uint64_t)(filterValue&0xfff)<<32)|((uint64_t)(asr32(filterValue,12)&3)<<19)|UINT64_C(0x360)):UINT64_C(0x61);
    put64(dst+16,f);put64(dst+24,context?21:20);
    if(palette)value=paletteBits|pitch|mode|tw|paletteAddress|UINT64_C(0x8000000000000000)|th|fmt|sx32(asr32(address,6));
    put64(dst+32,value);put64(dst+40,context?7:6);
    put64(dst+48,(clamp&255)==255?0:(clamp&15));put64(dst+56,context?9:8);
}
void ps2DrawUpdateEnvironmentRecord(uint32_t record,uint32_t index)
{
    uint32_t firstMode=get8(UINT32_C(0x55188a));
    uint32_t cfg=get32(record+8),table=cfg+8;
    uint32_t framebuffer=get32(get32(table+(index<<2))+12),depth=get32(get32(cfg+16)+12);
    uint32_t width=signed16(cfg),height=signed16(cfg+4),format=get8(cfg+6),depthFormat=get8(cfg+7);
    ps2DrawBuildRegisterGroupPacket(record+112,sx32(framebuffer),sx32(width),sx32(height),format,sx32(depth),depthFormat,firstMode,0);
    uint32_t secondMode=get8(UINT32_C(0x55188a));
    ps2DrawBuildRegisterGroupPacket(record+176,sx32(framebuffer),sx32(width),sx32(height),format,sx32(depth),depthFormat,secondMode,1);
    uint64_t v=sx32(format<<24)|sx32(asr32(framebuffer,11))|sx32(asr32(width,6)<<16)|UINT64_C(0x00ffffff00000000);
    put64(record+392,76);put64(record+400,v);put64(record+408,77);put64(record+384,v);
    if(!format)format=1;
    ps2DrawBuildTextureRegisterGroup(record+480,width,height,framebuffer,format,0,0,1,0,0,5,0);
    uint32_t alternate=get32(get32(table+((index^1)<<2))+12);
    ps2DrawBuildTextureRegisterGroup(record+416,width,height,alternate,format,0,0,1,0,0,5,0);
}

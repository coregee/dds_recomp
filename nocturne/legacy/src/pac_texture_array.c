#include "pac_texture_array.h"
#include "pac_texture.h"
#include "pac_binary.h"
#include "pac_parser.h"
#include "array_lists.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include <string.h>
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolvePacAddress(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,nocturneResolvePacAddress(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(nocturneResolvePacAddress(a),&v,4);}
static void w16(uint32_t a,uint32_t v){uint16_t n=(uint16_t)v;memcpy(nocturneResolvePacAddress(a),&n,2);}
static int32_t sh(uint32_t a){return (int32_t)(a&32767)-(int32_t)(a&32768);}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t ps2PointerArrayCreate(int32_t capacity){return sx(ps2ArrayCreate(capacity,4,4));}
void ps2PointerArrayAppend(uint64_t array,uint64_t value)
{
    uint32_t a=(uint32_t)array,count=r16(a+4),capacity=r16(a+6);
    if(sh(count)>=sh(capacity))ps2ArrayGrow(a);
    count=r16(a+4);uint32_t data=r32(a+12),slot=data+(uint32_t)(sh(count)*4);
    w16(a+4,count+1);w32(slot,(uint32_t)value);
}
void ps2PacTextureArrayHeaderReady(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,w=r32(p+0x2c);ps2PacTexturePrepare(parser,sx(w+16),sx(w+32));w32(p+12,0x2c6d88);
}
void ps2PacTextureArrayReadHeader(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,w=r32(p+0x2c);w32(p+12,0x2c6d18);w32(p+0x1c,w+16);w32(p+0x20,16);w32(p+8,0x2c65b0);
}
void ps2PacTextureArrayCompleteItem(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,w=r32(p+0x2c),tail=r32(p+0x34),texture=r32(w+32);
    ps2PointerArrayAppend(sx(r32(tail+8)),sx(texture));uint32_t index=r32(w+4)+1,count=r32(w);w32(w+4,index);
    if(index==count){ps2PoolRelease(w);ps2PacFinishRecord(parser);}else ps2PacTextureArrayReadHeader(parser);
}
void ps2PacTextureArraySkipTable(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,left=r32(p+0x14),rest=r32(p+0x20),n=(left^0x80000000)<(rest^0x80000000)?left:rest;
    ps2PacAdvanceBuffer(parser,sx(n));rest=r32(p+0x20)-n;w32(p+0x20,rest);if(!rest)ps2PacTextureArrayReadHeader(parser);
}
void ps2PacTextureArrayReadCount(uint64_t parser)
{
    uint32_t p=(uint32_t)parser;if(!r32(p+0x14))return;
    uint32_t count=r32(r32(p+16));ps2PacAdvanceBuffer(parser,4);uint32_t w=r32(p+0x2c),tail=r32(p+0x34);
    w32(w,count);w32(w+4,0);uint32_t padded=(((count*4+0x53)&0xffffffc0)-0x14);
    uint64_t array=ps2PointerArrayCreate((int32_t)count);w32(tail+8,(uint32_t)array);w32(p+8,0x2c6e00);w32(p+0x20,padded);
}
void ps2PacTextureArrayRecordInitialize(uint64_t parser,uint64_t header)
{
    uint32_t p=(uint32_t)parser;(void)ps2PacAppendRecord(parser,header);uint32_t w=ps2PoolAllocate(48);w32(p+0x2c,w);w32(p+8,0x2c6e70);
}
uint64_t ps2PacDefaultHeaderCallback(uint64_t parser,uint64_t phase,uint64_t header)
{
    if(phase)return 0;uint32_t type=*(uint8_t *)nocturneResolvePacAddress((uint32_t)header);
    if(type==1)ps2PacBinaryRecordInitialize(parser,header);
    else if(type==2)ps2PacTextureRecordInitialize(parser,header);
    else if(type==6)ps2PacType6RecordInitialize(parser,header);
    else if(type==8)ps2PacType8RecordInitialize(parser,header);
    else if(type==9)ps2PacTextureArrayRecordInitialize(parser,header);
    else return type==255?1:3;
    return 0;
}

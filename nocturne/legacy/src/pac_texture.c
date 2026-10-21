#include "pac_texture.h"
#include "pac_parser.h"
#include "pac_compression.h"
#include "texture_upload.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "material_lists.h"
#include "memory_handle_allocation.h"
#include "ps2_memory.h"
#include <string.h>
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolvePacAddress(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(nocturneResolvePacAddress(a),&v,4);}
static uint32_t r8(uint32_t a){return *(uint8_t *)nocturneResolvePacAddress(a);}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t minimum(uint32_t a,uint32_t b){return (a^0x80000000)<(b^0x80000000)?a:b;}
void ps2PacTexturePrepare(uint64_t parser,uint64_t header,uint64_t work)
{
    uint32_t p=(uint32_t)parser,h=(uint32_t)header,w=(uint32_t)work;
    w32(p+0x28,w);w32(w+12,r32(h+4)-16);uint32_t flag=r8(p+1);
    if(flag&1){w32(p+8,0x2c6ad0);w32(w+8,r32(p+16)-16);return;}
    uint32_t handle=flag&2?(uint32_t)ps2MemoryHandleAllocateHigh(sx(r32(h+4))):ps2MemoryHandleAllocate((int32_t)r32(h+4));
    w32(w+4,handle);uint32_t dst=ps2MemoryHandleAcquirePointer(r32(w+4));w32(w+8,dst);
    /* Both original unaligned 64-bit header loads precede every store. */
    uint8_t bytes[16];memcpy(bytes,nocturneResolvePacAddress(h),16);memcpy(nocturneResolvePacAddress(dst),bytes,16);
    w32(w+8,r32(w+8)+16);uint32_t compression=r8(h+1);
    if(!compression)w32(p+8,0x2c6990);
    else if(compression==1){uint32_t decomp=ps2PoolAllocate(32);w32(p+0x24,decomp);ps2PacCompressionInitialize(sx(decomp),sx(r32(w+8)));w32(p+8,0x2c6a38);}
}
void ps2PacTextureRawStream(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,w=r32(p+0x28),n=minimum(r32(p+0x14),r32(w+12));
    if(!n)return;
    ps2Memcpy(nocturneResolvePacAddress(r32(w+8)),nocturneResolvePacAddress(r32(p+16)),n);
    ps2PacAdvanceBuffer(parser,sx(n));uint32_t dst=r32(w+8),remaining=r32(w+12)-n;
    w32(w+8,dst+n);w32(w+12,remaining);
    if(!remaining){uint32_t data=ps2MemoryHandleAcquirePointer(r32(w+4));uint64_t texture=ps2TextureTmxCopy(sx(data));w32(w,(uint32_t)texture);ps2MemoryHandleClearSlot(sx(w+4));nocturnePacDataCallback(r32(p+12),parser);}
}
void ps2PacTextureReferenceStream(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,w=r32(p+0x28),n=minimum(r32(p+0x14),r32(w+12));
    if(!n)return;
    ps2PacAdvanceBuffer(parser,sx(n));uint32_t remaining=r32(w+12)-n;w32(w+12,remaining);
    if(!remaining){uint64_t texture=ps2TextureTmxReference(sx(r32(w+8)));uint32_t callback=r32(p+12);w32(w,(uint32_t)texture);nocturnePacDataCallback(callback,parser);}
}
void ps2PacTextureCompressedStream(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,n=r32(p+0x20);
    uint64_t done=ps2PacCompressionDecode(sx(r32(p+0x24)),sx(r32(p+16)),sx(n));
    uint32_t decomp=r32(p+0x24);ps2PacAdvanceBuffer(parser,sx(n-r32(decomp+12)));
    if(done){uint32_t w=r32(p+0x28),data=ps2MemoryHandleAcquirePointer(r32(w+4));uint64_t texture=ps2TextureTmxCopy(sx(data));w32(w,(uint32_t)texture);ps2MemoryHandleClearSlot(sx(w+4));ps2PoolRelease(r32(p+0x24));nocturnePacDataCallback(r32(p+12),parser);}
}
void ps2PacTextureComplete(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,w=r32(p+0x2c),tail=r32(p+0x34),texture=r32(w);
    w32(tail+8,texture);ps2PoolRelease(r32(p+0x2c));ps2PacFinishRecord(parser);
}
void ps2PacTextureRecordInitialize(uint64_t parser,uint64_t header)
{
    uint32_t p=(uint32_t)parser;(void)ps2PacAppendRecord(parser,header);uint32_t w=ps2PoolAllocate(16);
    w32(p+0x2c,w);ps2PacTexturePrepare(parser,header,sx(w));w32(p+12,0x2c6c80);
}

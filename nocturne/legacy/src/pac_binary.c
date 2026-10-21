#include "pac_binary.h"
#include "pac_parser.h"
#include "pac_compression.h"
#include "material_lists.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "ps2_memory.h"
#include <string.h>
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolvePacAddress(a),4);return v;}
static uint32_t r8(uint32_t a){return *(uint8_t *)nocturneResolvePacAddress(a);}
static void w32(uint32_t a,uint32_t v){memcpy(nocturneResolvePacAddress(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t minimum(uint32_t a,uint32_t b){return (a^0x80000000)<(b^0x80000000)?a:b;}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
void ps2PacBinaryPrepare(uint64_t parser,uint64_t header)
{
    uint32_t p=(uint32_t)parser,h=(uint32_t)header,size=r32(h+12);
    if(!size)size=r32(h+4)+(r8(h+1)&240)-16;
    if(r8(p+1)&1){uint32_t node=(uint32_t)ps2PacAppendRecord(parser,header);w32(node+12,h+16);w32(p+8,0x2c66b0);return;}
    *(uint8_t *)nocturneResolvePacAddress(p)=2;uint32_t node=(uint32_t)ps2PacAppendRecord(parser,header);
    uint32_t handle=r8(p+1)&2?(uint32_t)ps2MemoryHandleAllocateHigh(sx(size)):ps2MemoryHandleAllocate((int32_t)size);
    w32(node+8,handle);uint32_t data=ps2MemoryHandleAcquirePointer(r32(node+8));w32(node+12,data);w32(p+0x1c,data);
    uint32_t compression=r8(h+1)&15;
    if(!compression)w32(p+8,0x2c65b0);
    else if(compression==1){uint32_t decomp=ps2PoolAllocate(32);uint32_t destination=r32(p+0x1c);w32(p+0x24,decomp);ps2PacCompressionInitialize(sx(decomp),sx(destination));w32(p+8,0x2c6638);}
}
void ps2PacBinaryRawStream(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,n=minimum(r32(p+0x14),r32(p+0x20));if(!n)return;
    ps2Memcpy(nocturneResolvePacAddress(r32(p+0x1c)),nocturneResolvePacAddress(r32(p+16)),n);ps2PacAdvanceBuffer(parser,sx(n));
    uint32_t dst=r32(p+0x1c),rest=r32(p+0x20)-n;w32(p+0x1c,dst+n);w32(p+0x20,rest);
    if(!rest)nocturnePacDataCallback(r32(p+12),parser);
}
void ps2PacBinaryCompressedStream(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,n=r32(p+0x14);uint64_t done=ps2PacCompressionDecode(sx(r32(p+0x24)),sx(r32(p+16)),sx(n));
    uint32_t decomp=r32(p+0x24);ps2PacAdvanceBuffer(parser,sx(n-r32(decomp+12)));
    if(done){ps2PoolRelease(r32(p+0x24));nocturnePacDataCallback(r32(p+12),parser);}
}
void ps2PacBinaryReferenceStream(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,n=minimum(r32(p+0x14),r32(p+0x20));if(!n)return;
    ps2PacAdvanceBuffer(parser,sx(n));uint32_t rest=r32(p+0x20)-n;w32(p+0x20,rest);if(!rest)nocturnePacDataCallback(r32(p+12),parser);
}
void ps2PacRelocatePointers(uint64_t destination,uint64_t base,uint64_t table,uint64_t bytes)
{
    if(!less(0,bytes))return;uint32_t dst=(uint32_t)destination,src=(uint32_t)table,start=src;
    do{
        uint32_t code=r8(src++),delta;
        if(!(code&1))delta=code>>1;
        else if(!(code&2)){uint32_t next=r8(src++);delta=(code|(next<<8))>>2;}
        else if(!(code&4)){uint32_t lo=r8(src),hi=r8(src+1);src+=2;delta=(code|(lo<<8)|(hi<<16))>>3;}
        else{
            uint32_t run=(code>>3)+2;do{dst+=4;w32(dst,r32(dst)+(uint32_t)base);}while(--run);
            continue;
        }
        dst+=delta*4;w32(dst,r32(dst)+(uint32_t)base);
    }while(less(sx(src-start),bytes));
}
static void complete(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,node=r32(p+0x34),data=r32(node+12),body=data+16,count=r32(data+4);
    w32(node+12,body);
    if(count){uint32_t table=body+r32(data);ps2PacRelocatePointers(sx(body),sx(body),sx(table),sx(count));w32(data+4,0);}
    ps2PacFinishRecord(parser);
}
void ps2PacType6Complete(uint64_t parser){complete(parser);}
void ps2PacType8Complete(uint64_t parser){complete(parser);}
void ps2PacBinaryRecordInitialize(uint64_t parser,uint64_t header){ps2PacBinaryPrepare(parser,header);w32((uint32_t)parser+12,0x2c61f0);}
void ps2PacType6RecordInitialize(uint64_t parser,uint64_t header){ps2PacBinaryPrepare(parser,header);w32((uint32_t)parser+12,0x2c6870);}
void ps2PacType8RecordInitialize(uint64_t parser,uint64_t header){ps2PacBinaryPrepare(parser,header);w32((uint32_t)parser+12,0x2c6900);}

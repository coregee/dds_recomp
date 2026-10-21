/* Reconstructed original PS2 packet memory values with exact instruction widths. */
#include "packet_builders.h"
#include <string.h>
#include "heap_queue.h"
static void packet64(uint32_t a,uint64_t v){memcpy(nocturneResolveHeapAddress(a),&v,8);}
static uint64_t sx32(uint32_t v){return (uint64_t)v|((v&UINT32_C(0x80000000))?UINT64_C(0xffffffff00000000):0);}
static uint32_t asr32(uint32_t v,unsigned n){return (v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32-n)):0);}

void ps2DrawInitializeInlineRegisterPacket(uint32_t dst,uint64_t count)
{
    uint64_t next=sx32((uint32_t)count+1);
    packet64(dst+24,14);
    packet64(dst+8,((next|UINT64_C(0x50000000))<<32)|UINT64_C(0x10000000));
    packet64(dst+16,count|UINT64_C(0x1000000000008000));
    packet64(dst,next);
}
void ps2DrawInitializeReferencedRegisterPacket(uint32_t dst,uint64_t source,uint64_t count)
{
    uint64_t ref=(count&UINT64_C(0xffff))|UINT64_C(0x30000000)|((source&UINT64_C(0x0fffffff))<<32);
    uint64_t gif=count|UINT64_C(0x1000000000008000);
    packet64(dst,UINT64_C(0x10000001));
    packet64(dst+8,UINT64_C(0x5000000110000000));
    packet64(dst+16,gif);
    packet64(dst+24,14);
    packet64(dst+32,ref);
    packet64(dst+40,UINT64_C(0x5000000100000000));
    packet64(dst+48,UINT64_C(0x20000000));
    packet64(dst+56,0);
}
void ps2DrawBuildRegisterGroupPacket(uint32_t dst,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6,uint64_t p7,uint64_t p8,uint32_t p9)
{
    uint64_t width=sx32((uint32_t)p3-1),height=sx32((uint32_t)p4-1);
    uint64_t value0=sx32((uint32_t)p5<<24)|sx32(asr32((uint32_t)p3+63,6)<<16)|sx32(asr32((uint32_t)p2,11));
    uint64_t value2=sx32((uint32_t)p7<<24)|sx32(asr32((uint32_t)p6,11));
    uint32_t y=(UINT32_C(4096)-(uint32_t)p4)<<3;
    uint32_t x=(UINT32_C(4096)-(uint32_t)p3)<<3;
    uint64_t scissor=(height<<48)|(width<<16);
    packet64(dst+56,p9?UINT64_C(0x41):UINT64_C(0x40));
    packet64(dst,value0);
    if(p8)y+=8;
    packet64(dst+8,p9?UINT64_C(0x4d):UINT64_C(0x4c));
    packet64(dst+16,value2);
    packet64(dst+24,p9?UINT64_C(0x4f):UINT64_C(0x4e));
    packet64(dst+40,p9?UINT64_C(0x19):UINT64_C(0x18));
    packet64(dst+48,scissor);
    packet64(dst+32,sx32(x)|(sx32(y)<<32));
}
void ps2DrawBuildOffsetRangePacket(uint32_t dst,uint32_t x,uint32_t y)
{
    uint32_t low=((UINT32_C(4096)-y)<<19)|((UINT32_C(4096)-x)<<3);
    uint32_t high=((y+UINT32_C(4096))<<19)|((x+UINT32_C(4096))<<3);
    packet64(dst+72,5);
    packet64(dst,UINT64_C(0x30003));
    packet64(dst+8,UINT64_C(0x47));
    packet64(dst+16,6);
    packet64(dst+32,UINT64_C(0x3f80000000000000));
    packet64(dst+40,1);
    packet64(dst+48,low);
    packet64(dst+64,high);
    packet64(dst+24,0);
    packet64(dst+56,5);
}
void ps2DrawBuildFixedStatePacket(uint32_t dst)
{
    packet64(dst+8,UINT64_C(0x1a));
    packet64(dst+56,UINT64_C(0x3b));
    packet64(dst+16,1);
    packet64(dst+24,UINT64_C(0x46));
    packet64(dst+40,UINT64_C(0x45));
    packet64(dst+48,UINT64_C(0x4000000080));
    packet64(dst,1);
    packet64(dst+32,0);
}

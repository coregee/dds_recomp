/* Composite PCP copies rebuild owned parts and reset native instance state. */
#include "pcp_copy.h"
#include "pcp_construction.h"
#include "battle_effect_copy.h"
#include "material_fiveword_pool.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t p){return nocturneResolvePcpConstructionAddress(p);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t p){return (void *)(uintptr_t)p;}
#endif
static uint32_t read32(uint32_t p){uint32_t v;memcpy(&v,at(p),4);return v;}
static void write32(uint32_t p,uint32_t v){memcpy(at(p),&v,4);}
static uint64_t sx(uint32_t p){return (uint64_t)(int64_t)(int32_t)p;}
static uint64_t copyPart(uint32_t p){
    /* Account for the original part-copy frame in the host guest-stack bridge. */
    ENTER(32);uint64_t result=dds3EffectPartCopy(sx(p));LEAVE(32);return result;
}
uint64_t ps2PcpType3Copy(uint64_t source){
    ENTER(64);uint32_t s=(uint32_t)source,p=ps2PoolAllocate(188);
    for(unsigned i=0;i<8;i++){
        uint32_t pair=(i&1)*8;
        write32(p+28+i*8,(uint32_t)copyPart(read32(s+28+pair)));
        write32(p+32+i*8,(uint32_t)copyPart(read32(s+32+pair)));
        uint32_t third=(uint32_t)copyPart(read32(s+92));
        write32(p+124+i*4,0);write32(p+92+i*4,third);
        ps2PcpType3InitializePair(sx(p),i);
    }
    write32(p,0);write32(p+16,0x80808080);write32(p+24,0x3f800000);
    write32(p+4,0);write32(p+8,0);write32(p+20,0);
    LEAVE(64);return sx(p);
}
uint64_t ps2PcpType4Copy(uint64_t source){
    ENTER(48);uint32_t s=(uint32_t)source,p=ps2PoolAllocate(152);
    for(unsigned i=0;i<8;i++){
        write32(p+56+i*8,(uint32_t)copyPart(read32(s+56)));
        write32(p+60+i*8,(uint32_t)copyPart(read32(s+60)));
        ps2PcpType4InitializePair(sx(p),i);
    }
    write32(p,0);write32(p+16,0x80808080);write32(p+20,0x3f800000);
    write32(p+4,0);write32(p+8,0);LEAVE(48);return sx(p);
}
uint64_t ps2PcpType5Copy(uint64_t source){
    ENTER(64);uint32_t s=(uint32_t)source,p=ps2PoolAllocate(220);
    uint64_t base=copyPart(read32(s+24));write32(p+24,(uint32_t)base);
    ps2ModelChangeMotionSingle(dds3EffectPartGetHandle(base),0,0);
    for(unsigned group=0;group<4;group++)for(unsigned i=0;i<3;i++){
        write32(p+28+(group*3+i)*4,(uint32_t)copyPart(read32(s+28+group*12)));
        ps2PcpType5InitializePart(sx(p),group,i);
    }
    write32(p,0);write32(p+16,0x80808080);write32(p+20,0x3f800000);
    write32(p+4,0);write32(p+8,0);LEAVE(64);return sx(p);
}
uint64_t ps2PcpType6Copy(uint64_t source){
    ENTER(32);uint32_t s=(uint32_t)source,h=ps2MemoryHandleAllocate(0x1354),p=ps2MemoryHandleAcquirePointer(h);
    uint32_t original=read32(s+0x134c);write32(p+0x1350,h);
    write32(p+0x134c,(uint32_t)copyPart(original));
    write32(p+0x1348,(uint32_t)copyPart(read32(s+0x1348)));
    ps2PcpType6Reset(sx(p));write32(p+0xaf0,0);write32(p+0xaf4,0);
    write32(p+0x1334,0x80808080);write32(p+0x1338,0x3f800000);write32(p+0xaf8,0);
    LEAVE(32);return sx(p);
}

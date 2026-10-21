#include "pac_parser.h"
#include "ps2_memory.h"
#include "material_construction_release.h"
#include <string.h>
static uint32_t r32(uint32_t a)
{ uint32_t v;memcpy(&v,nocturneResolvePacAddress(a),4);return v; }
static uint32_t r16(uint32_t a)
{ uint16_t v;memcpy(&v,nocturneResolvePacAddress(a),2);return v; }
static uint32_t r8(uint32_t a)
{ return *(uint8_t *)nocturneResolvePacAddress(a); }
static void w32(uint32_t a,uint32_t v)
{ memcpy(nocturneResolvePacAddress(a),&v,4); }
static void w16(uint32_t a,uint32_t v)
{ uint16_t h=(uint16_t)v;memcpy(nocturneResolvePacAddress(a),&h,2); }
static void w8(uint32_t a,uint32_t v)
{ *(uint8_t *)nocturneResolvePacAddress(a)=(uint8_t)v; }
static uint64_t sx32(uint32_t v)
{ return v&UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000)|v : v; }
static uint64_t state_result(uint32_t v)
{ return v&128 ? UINT64_C(0xffffffffffffff00)|v : v; }
/* 002c6030: callback choice compares the whole argument, then stores low32. */
void ps2PacInitialize(uint64_t parser,uint64_t callback)
{
    uint32_t p=(uint32_t)parser;
    (void)ps2Memset(nocturneResolvePacAddress(p),0,56);
    w16(p+2,65535);w32(p+4,callback ? (uint32_t)callback : UINT32_C(0x2c64b0));
}
void ps2PacSetFlag2(uint64_t parser)
{ uint32_t p=(uint32_t)parser;w8(p+1,r8(p+1)|2); }
/* 002c60a8: save next before actual pool release; leave parser links as-is. */
void ps2PacReleaseRecords(uint64_t parser)
{
    uint32_t node=r32((uint32_t)parser+0x30);
    while(node){uint32_t next=r32(node);ps2PoolRelease(node);node=next;}
}
void ps2PacStop(uint64_t parser)
{ w8((uint32_t)parser,255); }
/* 002c60f0: all three old words are loaded before any write. */
void ps2PacAdvanceBuffer(uint64_t parser,uint64_t count)
{
    uint32_t p=(uint32_t)parser,n=(uint32_t)count;
    uint32_t input=r32(p+0x10),left=r32(p+0x14),total=r32(p+0x18);
    w32(p+0x10,input+n);w32(p+0x14,left-n);w32(p+0x18,total+n);
}
/* 002c6118: the original reads a full header even with fewer bytes offered. */
void ps2PacReadHeader(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,misalignment=r32(p+0x18)&63;
    if(misalignment){w8(p,1);w32(p+0x20,64-misalignment);return;}
    uint32_t header=r32(p+0x10);ps2PacAdvanceBuffer(parser,16);
    uint32_t size=r32(header+4);w16(p+2,r16(p+2)+1);
    uint32_t callback=r32(p+4),extra=r8(header+1)&240;
    w32(p+0x20,size-extra-16);
    uint64_t result=nocturnePacHeaderCallback(callback,parser,0,sx32(header));
    if(result==1){ps2PacStop(parser);return;}
    if(result==2){w8(p,1);w32(p+0x20,(r32(p+0x20)+63)&UINT32_C(0xffffffc0));}
    else w8(p,2);
}
/* 002c61f0: callback may change links; reload after its return.
   Multi-node removal deliberately does not update the tail pointer. */
void ps2PacFinishRecord(uint64_t parser)
{
    uint32_t p=(uint32_t)parser,header=r32(p+0x34)+16;
    uint64_t result=nocturnePacHeaderCallback(r32(p+4),parser,1,sx32(header));
    if(result==1){ps2PacStop(parser);return;}
    if(result==4){
        uint32_t tail=r32(p+0x34),node=r32(p+0x30);
        if(node==tail){w32(p+0x34,0);w32(p+0x30,0);}
        else{
            uint32_t next=r32(node);
            while(next!=tail){node=next;next=r32(node);}
            w32(node,0);
        }
        ps2PoolRelease(tail);
    }
    w8(p,0);
}
/* 002c62a0: the initial BLEZ uses full64 count; loop/min use signed32 words. */
uint64_t ps2PacDecodeChunk(uint64_t parser,uint64_t input,uint64_t count)
{
    uint32_t p=(uint32_t)parser;
    w32(p+0x10,(uint32_t)input);w32(p+0x14,(uint32_t)count);
    if(count==0 || count>>63)return state_result(r8(p));
    uint32_t state=r8(p);
    do{
        if(state==255)return UINT64_MAX;
        if(state==0)ps2PacReadHeader(parser);
        else if(state==1){
            uint32_t rest=r32(p+0x20),left=r32(p+0x14);
            uint32_t n=(left^UINT32_C(0x80000000))<(rest^UINT32_C(0x80000000)) ? left : rest;
            ps2PacAdvanceBuffer(parser,sx32(n));
            rest=r32(p+0x20)-n;w32(p+0x20,rest);
            if(rest==0)w8(p,0);
        }else if(state==2)nocturnePacDataCallback(r32(p+8),parser);
        state=r8(p);
        uint32_t left=r32(p+0x14);
        if(left==0 || left&UINT32_C(0x80000000))break;
    }while(1);
    return state_result(state);
}
/* 002c63b8: copy retained header bytes into a real zeroed pool record. */
uint64_t ps2PacAppendRecord(uint64_t parser,uint64_t header)
{
    uint32_t p=(uint32_t)parser,h=(uint32_t)header,extra=r8(h+1)&240;
    uint32_t node=ps2PoolAllocateZeroed((int32_t)(extra+32));
    w32(node+4,p);
    (void)ps2Memcpy(nocturneResolvePacAddress(node+16),nocturneResolvePacAddress(h),extra+16);
    uint32_t tail=r32(p+0x34);
    if(tail)w32(tail,node);else w32(p+0x30,node);
    w32(p+0x34,node);return sx32(node);
}

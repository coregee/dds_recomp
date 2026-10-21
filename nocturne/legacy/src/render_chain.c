/* Reconstructed ordinary RAM behavior from original Nocturne EE instructions. */
#include "render_chain.h"
#include <string.h>
#include "heap_queue.h"
#include "deferred_drain.h"
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveHeapAddress(a),4);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,nocturneResolveHeapAddress(a),2);return v;}
static uint64_t r64(uint32_t a){uint64_t v;memcpy(&v,nocturneResolveHeapAddress(a),8);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(nocturneResolveHeapAddress(a),&v,4);}
static void w64(uint32_t a,uint64_t v){memcpy(nocturneResolveHeapAddress(a),&v,8);}
static void w8(uint32_t a,uint8_t v){memcpy(nocturneResolveHeapAddress(a),&v,1);}
void ps2DrawTagAppendReference(uint32_t chain,uint32_t tag)
{
    w8(tag+3,0x30);uint32_t previous=r32(chain+8),tail=tag+16;
    if(!previous)w32(chain+4,tag);
    else{w8(previous+3,0x20);w32(previous+4,tag&UINT32_C(0x0fffffff));}
    w32(chain+8,tail);
}
void ps2DrawTagAppendPacket48(uint32_t chain,uint32_t tag)
{
    uint32_t previous=r32(chain+8);
    if(!previous)w32(chain+4,tag);
    else{w8(previous+3,0x20);w32(previous+4,tag&UINT32_C(0x0fffffff));}
    w32(chain+8,tag+48);
}
void ps2DrawTagAppendCall(uint32_t chain,uint32_t tag)
{
    w8(tag+3,0x50);uint32_t previous=r32(chain+8),tail=tag+16;
    if(!previous)w32(chain+4,tag);
    else{w8(previous+3,0x20);w32(previous+4,tag&UINT32_C(0x0fffffff));}
    w32(chain+8,tail);
}
uint32_t ps2DrawBuildReferencePacket(uint32_t source)
{
    uint32_t packet=ps2WorkBufferTake(32);
    uint64_t tag=(uint64_t)(r16(source)|UINT32_C(0x30000000))|((uint64_t)((source+16)&UINT32_C(0x0fffffff))<<32);
    w64(packet,tag);w64(packet+16,0);w64(packet+24,0);
    uint64_t payload=r64(source+8);w64(packet+8,payload);
    return packet;
}
uint32_t ps2DrawLinkReferencePacket(uint32_t previous,uint32_t source)
{
    uint32_t packet=ps2DrawBuildReferencePacket(source);
    w8(previous+3,0x20);uint32_t tail=packet+16;
    w32(previous+4,packet&UINT32_C(0x0fffffff));return tail;
}
void ps2DrawTagLinkState(uint32_t previous,uint32_t next)
{
    uint32_t other=r32(next+16),current=r32(previous+16),tail=r32(previous+8);
    if(current!=other){if(!other)w32(next+16,current);else tail=ps2DrawLinkReferencePacket(tail,other);}
    current=r32(previous+20);other=r32(next+20);
    if(current!=other){if(!other)w32(next+20,current);else tail=ps2DrawLinkReferencePacket(tail,other);}
    w8(tail+3,0x20);uint32_t head=r32(next+4);
    w32(tail+4,head&UINT32_C(0x0fffffff));
}
void ps2DrawChainPrepend(uint32_t list,uint32_t tag)
{
    if(r32(tag+8)){
        uint32_t head=r32(list+4);
        if(!head)w32(list+8,tag);else ps2DrawTagLinkState(tag,head);
        w32(tag,head);w32(list+4,tag);
    }
}
void ps2DrawChainAppend(uint32_t list,uint32_t tag)
{
    if(r32(tag+4)){
        uint32_t previous=r32(list+8);
        if(!previous)w32(list+4,tag);
        else{w32(previous,tag);ps2DrawTagLinkState(previous,tag);}
        w32(list+8,tag);
    }
}
void ps2DrawChainPrependOnMode1(uint32_t list,uint32_t mode,uint32_t tag)
{if(mode==1)ps2DrawChainPrepend(list,tag);}
void ps2DrawOrderingInitialize(uint32_t record,uint32_t count)
{
    --count;
    w32(record+16,0x2acd40);w32(record+20,0x2acd98);w32(record+4,0);w32(record+8,0);w32(record+12,0);w32(record+24,0);
    if(!count){w32(record,0);return;}
    do{
        uint32_t next=record+32;--count;w32(record,next);record=next;
        w32(record+16,0x2acd40);w32(record+20,0x2acd98);w32(record+4,0);w32(record+8,0);w32(record+12,0);w32(record+24,0);
    }while(count);
    w32(record,0);
}

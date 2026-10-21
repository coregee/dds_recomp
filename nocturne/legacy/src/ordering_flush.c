/* Reconstructed ordinary RAM behavior from original Nocturne EE instructions. */
#include "ordering_flush.h"
#include <string.h>
#include "heap_queue.h"
#include "deferred_drain.h"
#include "render_chain.h"
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveHeapAddress(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(nocturneResolveHeapAddress(a),&v,4);}
static void w64(uint32_t a,uint64_t v){memcpy(nocturneResolveHeapAddress(a),&v,8);}
static void w8(uint32_t a,uint8_t v){memcpy(nocturneResolveHeapAddress(a),&v,1);}
void ps2DrawTagPrependStateReferences(uint32_t tag)
{
    uint32_t source=r32(tag+20);
    if(source){uint32_t packet=ps2DrawBuildReferencePacket(source),head=r32(tag+4);w32(tag+4,packet);w64(packet+16,((uint64_t)(head&UINT32_C(0x0fffffff))<<32)|UINT64_C(0x20000000));}
    source=r32(tag+16);
    if(source){uint32_t packet=ps2DrawBuildReferencePacket(source),head=r32(tag+4);w32(tag+4,packet);w64(packet+16,((uint64_t)(head&UINT32_C(0x0fffffff))<<32)|UINT64_C(0x20000000));}
}
uint32_t ps2DrawOrderingFlush(uint32_t record)
{
    uint32_t last=0,first=0;
    while(record){
        uint32_t callback=r32(record+20);nocturneCallDrawOrdering(callback,record,0,0);uint32_t head=r32(record+4);
        if(head){if(!first){first=head;ps2DrawTagPrependStateReferences(first);}else ps2DrawTagLinkState(last,head);last=r32(record+8);}
        record=r32(record);
    }
    if(last){uint32_t tail=r32(last+8);w8(tail+3,0x70);tail=r32(last+8);w32(tail+4,0);}
    return first;
}
void ps2DrawNodeListInitialize(uint32_t list)
{w32(list+12,0);w32(list,0);w32(list+4,0);w32(list+8,0);}
void ps2DrawNodeListAppend(uint32_t list,uint32_t node)
{
    uint32_t previous=r32(list+8);
    if(!previous)w32(list+4,node);else w32(previous,node);
    w32(list+8,node);w32(node,0);
}
void ps2DrawPacketListInitialize(uint32_t list)
{w32(list+4,0);w32(list,0);}
void ps2DrawPacketListAppend(uint32_t list,uint32_t tag)
{
    uint32_t previous=r32(list+4);
    if(!previous)w32(list,tag);
    else{uint32_t captured_tail=r32(previous+8),next_tail=r32(tag+8);w32(captured_tail,next_tail);}
    w32(list+4,tag);
}

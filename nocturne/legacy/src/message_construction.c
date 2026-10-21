#include "message_construction.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "pac_binary.h"
#include <string.h>
static uint32_t r32(uint32_t a)
{ uint32_t v;memcpy(&v,nocturneResolveMessageConstructionAddress(a),4);return v; }
static uint32_t r8(uint32_t a)
{ return *(uint8_t *)nocturneResolveMessageConstructionAddress(a); }
static void w32(uint32_t a,uint32_t v)
{ memcpy(nocturneResolveMessageConstructionAddress(a),&v,4); }
static void w16(uint32_t a,uint32_t v)
{ uint16_t h=(uint16_t)v;memcpy(nocturneResolveMessageConstructionAddress(a),&h,2); }
static void w8(uint32_t a,uint32_t v)
{ *(uint8_t *)nocturneResolveMessageConstructionAddress(a)=(uint8_t)v; }
static uint64_t sx(uint32_t v)
{ return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v; }
/* 001caeb8: append the first free node to the active list, retaining live reloads. */
uint64_t itfMiscLinkTake(uint64_t stack)
{
 uint32_t s=(uint32_t)stack,node=r32(s+8);if(!node)return 0;
 uint32_t head=r32(s),next=r32(node+4);
 if(head){uint32_t tail=r32(s+4);w32(node,tail);w32(r32(s+4)+4,node);}
 else{w32(node,0);w32(s,node);}
 w32(node+4,0);w32(s+4,node);
 if(next)w32(next,0);else w32(s+0xc,0);
 w32(s+8,next);return sx(node);
}
/* 001caf20: active unlink followed by free-tail insertion, with no guards. */
void itfMiscLinkGive(uint64_t rawnode,uint64_t stack)
{
 uint32_t node=(uint32_t)rawnode,s=(uint32_t)stack,prev=r32(node),next=r32(node+4);
 if(prev)w32(prev+4,next);else w32(s,next);
 if(next)w32(next,prev);else w32(s+4,prev);
 w32(node+4,0);uint32_t tail=r32(s+0xc);w32(node,tail);
 if(tail)w32(tail+4,node);
 uint32_t freehead=r32(s+8);w32(s+0xc,node);if(!freehead)w32(s+8,node);
}
/* 001cfc58 / 001cfc80: only reset positions when the full argument is nonzero. */
void itfMesInitializeSpeaker(uint64_t speaker,uint64_t defaultpos)
{
 uint32_t p=(uint32_t)speaker;
 if(defaultpos){w32(p,0x430);w32(p+4,0x9b0);}
 w32(p+8,0);w16(p+0xc,0xffff);
}
void itfMesInitializeMessage(uint64_t message,uint64_t defaultpos)
{
 uint32_t p=(uint32_t)message;
 if(defaultpos){w32(p,0x4b0);w32(p+4,0xa88);}
 w32(p+8,0);w8(p+0x15,0x80);w32(p+0xc,0);
 w8(p+0x10,0);w8(p+0x11,0);w16(p+0x16,0);w16(p+0x18,0);w16(p+0x1a,0);
 w8(p+0x12,0);w8(p+0x13,0);w8(p+0x14,0);
}
/* 001cfcc8 */
void itfMesInitializeSelect(uint64_t select)
{
 uint32_t p=(uint32_t)select;w32(p,0x560);w32(p+4,0xbc8);w16(p+0x14,0xffff);w16(p+0x1a,0);
 w32(p+8,0);w32(p+0xc,0);w16(p+0x10,0);w16(p+0x12,0xffff);w16(p+0x16,0);w16(p+0x18,0);
}
/* 001cfed0: type uses full-width equality; positive alpha uses signed64 SLT. */
void itfMesResetWindowPara(uint64_t window,uint64_t type,uint64_t alpha)
{
 uint32_t p=(uint32_t)window,value=alpha&&!(alpha>>63)?(uint32_t)alpha:type==1?0x57:type==2?0x87:0x66;
 if(type==1){
  w32(p+8,(uint32_t)-0x1db0);w32(p+0x24,value);w32(p+0xc,(uint32_t)-0x2f8);
  w32(p+0x10,0x2c30);w32(p+0x14,0x548);w32(p+0x20,0x7f);w32(p+0x18,0x7f);w32(p+0x1c,0x7f);
 }else{
  w32(p+0x24,value);w32(p+8,(uint32_t)-0x1390);w32(p+0xc,type==2?(uint32_t)-0x208:(uint32_t)-0x3d8);
  w32(p+0x10,0x2a30);w32(p+0x14,type==2?0x410:0x590);w32(p+0x20,0x7f);w32(p+0x18,0x7f);w32(p+0x1c,0x7f);
 }
}
/* 001cfd00: clear owned pointers before invoking the complete reset body. */
void itfMesInitializeWindow(uint64_t window)
{ uint32_t p=(uint32_t)window;w32(p+4,0);w32(p,0);itfMesResetWindowPara(window,0,0); }
/* 001cfd28: original descending stores do not clear the following handle array. */
void itfMesInitializeVariable(uint64_t variable)
{ uint32_t p=(uint32_t)variable+0x7c;for(unsigned i=0;i<32;i++,p-=4)w32(p,0); }
/* 001cfd58: nonzero isdisp preserves the existing display byte. */
void itfMesInitializeCurCtr(uint64_t cursor,uint64_t isdisp)
{
 uint32_t p=(uint32_t)cursor;if(!isdisp)w8(p,0);w32(p+8,0);w16(p+4,0x40);w16(p+2,0);w16(p+6,0);
}
/* 001cf100: the resource's single byte records completed relocation. */
void itfMesResolveResourceAddress(uint64_t data)
{
 uint32_t d=(uint32_t)data;if(r8(d+0x1c))return;
 uint32_t offset=r32(d+0x10),size=r32(d+0x14);
 ps2PacRelocatePointers(sx(d+0x20),sx(d+0x20),sx(d+offset),sx(size));w8(d+0x1c,1);
}
/* 001cf190: return the type header following the eight-byte record array. */
uint64_t ps2MessageGetTypeHeader2(uint64_t data)
{ uint32_t d=(uint32_t)data;return sx(d+0x20+(r32(d+0x18)<<3)); }
/* 001ce838: old resource returned; MSG1 additionally publishes the type word. */
uint64_t itfMesMngSetResourcePtr(uint64_t id,uint64_t data)
{
 uint32_t instance=r32(0x56be8c+(uint32_t)id*20),d=(uint32_t)data,old=r32(instance+4);
 w32(instance+4,d);itfMesResolveResourceAddress(data);uint32_t header=(uint32_t)ps2MessageGetTypeHeader2(data);
 uint32_t type=r32(d+8)==0x3147534d?r32(header+8):0;w32(instance+8,type);return sx(old);
}
/* 001cda40: all allocations, relocation and field initializer callees execute. */
uint64_t itfMesMngInitialize(uint64_t data)
{
 uint32_t node=(uint32_t)itfMiscLinkTake(0x56be70),id=r32(node+8),handle=ps2MemoryHandleAllocate(0x1d4);
 w32(node+0x10,handle);uint32_t p=ps2MemoryHandleAcquirePointer(handle);w32(node+0xc,p);w32(p+4,0);
 (void)itfMesMngSetResourcePtr(sx(id),data);w32(p,0);w16(p+0x10,0x47);w32(p+0xc,0xfffff0);w16(p+0x12,0);
 w32(p+0x1d0,0);itfMesInitializeSpeaker(sx(p+0x14),1);itfMesInitializeMessage(sx(p+0x24),1);
 itfMesInitializeSelect(sx(p+0x40));itfMesInitializeWindow(sx(p+0x9c));itfMesInitializeVariable(sx(p+0xc4));itfMesInitializeCurCtr(sx(p+0x1c4),0);
 w32(0x56be60,r32(0x56be60)+1);return sx(id);
}

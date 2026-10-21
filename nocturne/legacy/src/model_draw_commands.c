/* Original PS2 model command lists and DMA/VIF packet construction.
 * Community record roles: Megami-Decomps/dds-decomp, bec33411543cdc487bad9debdf758f0090a2242c.
 * Addresses, widths, partial writes and control flow are from SLUS_209.11. */
#include "model_draw_commands.h"
#include "model_pose_evaluation.h"
#include "model_root_creation.h"
#include "model_motion_creation.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "libc_stream.h"
#include <string.h>
static void *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveModelDrawCommandAddress(a);
#else
 return (void *)(uintptr_t)a;
#endif
}
static uint8_t r8(uint32_t a){uint8_t v;memcpy(&v,at(a),1);return v;}
static uint16_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w8(uint32_t a,uint8_t v){memcpy(at(a),&v,1);}
static void w16(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}

uint64_t ps2ModelEnsureWorkspace(uint64_t node){
 uint32_t n=(uint32_t)node,p=r32(n+0x30);
 if(!p){p=ps2PoolAllocate(256);w32(n+0x30,p);}return sx(p);
}
void ps2ModelFreeCommandLists(uint64_t node){
 uint32_t n=(uint32_t)node;
 for(unsigned pass=0;pass<2;pass++){
  uint32_t p=r32(n+0x28+pass*4);
  while(p){uint32_t h=r32(p+12),next=r32(p);if(h)ps2MemoryHandleFree(h);else ps2PoolRelease(p);p=next;}
 }
 /* The original does not clear the two heads. */
}
uint64_t ps2ModelWriteReturnPacket(uint64_t packet){
 uint32_t p=(uint32_t)packet;w32(p+8,0);w32(p+12,0);w32(p,0x60000000);w32(p+4,0);return sx(p+16);
}
uint64_t ps2ModelWriteIndexedAssetPacket(uint64_t root,uint64_t index,uint64_t packet,uint64_t frame){
 uint32_t r=(uint32_t)root,resources=r32(r+12),asset=r32(r32(resources+12)+((uint32_t)index<<2));
 return sx(ps2MatWritePacketHeader(asset,(uint32_t)packet,(uint32_t)frame));
}
uint64_t ps2ModelMeasureCommandList(uint64_t list,uint64_t count,uint64_t quadwords){
 uint32_t l=(uint32_t)list,c=(uint32_t)count,q=(uint32_t)quadwords;
#if UINTPTR_MAX > UINT32_MAX
 nocturneModelCommandObserveCount(r32(c));
#endif
 if(!list){w32(c,0);w32(q,0);return 0;}
 uint32_t remaining=r32(l)&0xffff,bytes=0,kind3=0,extra=0;l+=4;
 while(remaining--){uint32_t command=r32(l);l+=4;unsigned kind=r8(command);
  if(kind==1)bytes+=32;else if(kind==2)bytes+=((uint32_t)r16(command+12)<<4)+64;
  else if(kind==3)kind3++;else if(kind>=4&&kind<=8)extra+=16;
 }
 w32(c,r32(c)+kind3);w32(q,extra);return sx(bytes?bytes+32:0);
}
uint64_t ps2ModelBuildIndexedPayload(uint64_t node,uint64_t command,uint64_t packet,uint64_t frame){
 uint32_t n=(uint32_t)node,c=(uint32_t)command,packed=r32(c+4);
 uint32_t p=(uint32_t)ps2ModelWriteIndexedAssetPacket(sx(r32(n+16)),packed>>16,packet,frame);
 w8(p+3,0x30);w16(p,(uint16_t)packed);w32(p+8,0);w32(p+12,0);w32(p+4,r32(c+8)&0x0fffffff);return sx(p+16);
}
uint64_t ps2ModelBuildNodeRefsPayload(uint64_t node,uint64_t command,uint64_t packet,uint64_t frame){
 uint32_t n=(uint32_t)node,c=(uint32_t)command,packed=r32(c+4);
 uint32_t p=(uint32_t)ps2ModelWriteIndexedAssetPacket(sx(r32(n+16)),packed>>16,packet,frame);
 uint32_t count=r32(c+12),cursor=c+16,i=0,destination=1;
 do{
  uint32_t id=r16(cursor);cursor+=2;i++;
  uint64_t child=sdfModelSearchNode(sx(r32(n+16)),id);
  w16(p,7);w8(p+3,0x30);uint32_t workspace=(uint32_t)ps2ModelEnsureWorkspace(child);
  w32(p+8,0);w32(p+12,destination|0x6c07c000);destination+=7;
  w32(p+4,(workspace+((uint32_t)frame<<7))&0x0fffffff);p+=16;
 }while(i!=count);
 w8(p+3,0x10);w32(p+8,0);w32(p+12,0);w16(p,1);uint32_t payload=p+16;p+=32;
 w32(payload+12,0x14000000);w32(payload+4,count);w32(payload,0x6001c000);w32(payload+8,0x0400000e);
 w8(p+3,0x30);w16(p,(uint16_t)packed);w32(p+8,0);w32(p+12,0);w32(p+4,r32(c+8)&0x0fffffff);return sx(p+16);
}
uint64_t ps2ModelPrependCommandNode(uint64_t node,uint64_t selector,uint64_t pass){
 uint32_t p=ps2PoolAllocate(16),head=(uint32_t)node+0x28+((uint32_t)pass<<2),next=r32(head);
 w8(p+5,(uint8_t)selector);w32(head,p);w16(p+6,1);w32(p,next);w32(p+12,0);return sx(p);
}
void ps2ModelEnsureReferencedWorkspaces(uint64_t root,uint64_t command){
 uint32_t c=(uint32_t)command,cursor=c+24,array=r32((uint32_t)root),data=r32(array+12);
 if(r16(c+22)&0x800){uint32_t count=r16(cursor);cursor+=2;while(count--){uint32_t id=r16(cursor);cursor+=2;ps2ModelEnsureWorkspace(sx(r32(data+id*4u)));}}
}
void ps2ModelBuildCommandList(uint64_t node,uint64_t list,uint64_t selector,uint64_t alternate,uint64_t pass){
 uint32_t counts[2];
#if UINTPTR_MAX > UINT32_MAX
 /* Original +0 is an incoming private-frame word; measure adds to it. */
 counts[0]=nocturneModelCommandIncomingCount();counts[1]=0;
 uint32_t address=nocturneLibcStreamLocalAddress(counts,8);
#else
 uint32_t address=(uint32_t)(uintptr_t)counts;
#endif
 uint64_t measured=ps2ModelMeasureCommandList(list,sx(address),sx(address+4));
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();nocturneModelCommandStoreCount(counts[0]);
#endif
 if(!measured&&!counts[0]&&!counts[1])return;
 ps2ModelEnsureWorkspace(node);uint32_t l=(uint32_t)list,packed=r32(l),remaining=packed&0xffff,p=0;l+=4;
 if(alternate)selector=packed>>16;
 if(measured){uint32_t h=ps2MemoryHandleAllocate((int32_t)measured),header=ps2MemoryHandleAcquirePointer(h),head=(uint32_t)node+0x28+((uint32_t)pass<<2),next=r32(head);p=header+16;
  w8(header+4,1);w8(header+5,(uint8_t)selector);w32(header+8,p);w16(header+6,(uint16_t)(((int32_t)((uint32_t)measured+15))>>4));w32(header,next);w32(header+12,h);w32(head,header);
 }
 do{
  uint32_t command=r32(l);l+=4;unsigned kind=r8(command);
  if(kind==1)p=(uint32_t)ps2ModelBuildIndexedPayload(node,sx(command),sx(p),pass);
  else if(kind==2)p=(uint32_t)ps2ModelBuildNodeRefsPayload(node,sx(command),sx(p),pass);
  else if(kind>=3&&kind<=8){
   if(kind==5||kind==7)ps2ModelEnsureReferencedWorkspaces(sx(r32((uint32_t)node+16)),sx(command));
   uint32_t entry=(uint32_t)ps2ModelPrependCommandNode(node,selector,pass);w32(entry+8,command);w8(entry+4,kind==3?2:3);
  }
 }while(--remaining);
 if(measured)ps2ModelWriteReturnPacket(sx(p));
}
void ps2ModelNodeSetCommands(uint64_t node,uint64_t item){
 uint32_t d=(uint32_t)item;ps2ModelNodeBaseSet(node,item);
#if UINTPTR_MAX > UINT32_MAX
 nocturneModelCommandBeginItem();
#endif
 uint16_t mode=r16(d);
 if(mode==0){for(unsigned pass=0;pass<2;pass++)for(unsigned slot=0;slot<3;slot++)ps2ModelBuildCommandList(node,sx(r32(d+68+slot*4)),slot,0,pass);}
 else if(mode==1){uint32_t table=r32(d+68);if(table)for(unsigned pass=0;pass<2;pass++){uint32_t cursor=table,command;while((command=r32(cursor))!=0){cursor+=4;ps2ModelBuildCommandList(node,sx(command),0,1,pass);}if(pass==0)table=r32(d+68);}}
}
void ps2ModelResetCommands(uint64_t node,uint64_t list,uint64_t selector){
 w32((uint32_t)node+56,(uint32_t)list);ps2ModelFreeCommandLists(node);ps2ModelEnsureWorkspace(node);sdfModelMakeLocalTm(node);
#if UINTPTR_MAX > UINT32_MAX
 nocturneModelCommandBeginReset();
#endif
 for(unsigned pass=0;pass<2;pass++)ps2ModelBuildCommandList(node,list,selector,0,pass);
}
uint64_t ps2ModelMake(uint64_t textures,uint64_t definition){
 uint32_t d=(uint32_t)definition,r=(uint32_t)sdfModelMakeRoot(textures,definition),list=r32(d),count=r32(list),record=list+16,i=0;
 if(count)do{uint32_t array=r32(r),node=r32(r32(array+12)+i*4u);i++;ps2ModelNodeSetCommands(sx(node),sx(record));record+=80;}while(i!=count);
 return sx(r);
}

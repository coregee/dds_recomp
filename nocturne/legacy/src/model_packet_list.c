/* 002B0CB0: two weighted slots, material reference and nonempty mesh packets. */
#include "model_packet_list.h"
#include "model_draw_commands.h"
#include "deferred_drain.h"
#include "resource_loader_flow.h"
#include "script_compare.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolveModelPacketListAddress(a);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
void ps2ModelAppendWeightedMeshPackets(uint64_t node,uint64_t command,uint64_t chain,uint64_t frame){
 ENTER(80);uint32_t threshold=word(0x54e744),n=(uint32_t)node,c=(uint32_t)command,selected=0;
#if UINTPTR_MAX > UINT32_MAX
 uint32_t slots=nocturneModelPacketListFrameAddress();
#else
 uint64_t local[2];uint32_t slots=(uint32_t)(uintptr_t)local;
#endif
 uint32_t model=word(n+16),packed=word(c+4),list=word(model+16),data=word(list+12);
 uint32_t count=half(c+8),pairs=data+((packed&65535u)<<4);
 for(unsigned i=0;i<2;i++)if(EE_FPU_COMPARE_S(threshold,word(pairs+i*8+4),1)){
  uint64_t pair=quad(pairs+i*8);sd(slots+selected*8,pair);++selected;
 }
 uint32_t start=ps2WorkBufferTake(((selected<<4)+16)*count+64);
 /* Reload the model after allocation; the work cursor may alias node+10. */
 uint32_t p=(uint32_t)ps2ModelWriteIndexedAssetPacket(sx(word(n+16)),packed>>16,sx(start),frame);
 sd(p,UINT64_C(0x10000001));sd(p+8,UINT64_C(0x6002c00000000000));
 for(uint32_t i=0;i<selected;i++)sw(p+16+i*4,word(slots+4+i*8));
 for(uint32_t i=selected;i<2;i++)sw(p+16+i*4,0);
 sw(p+28,0x14000000);sw(p+24,0x0400000a);p+=32;
 uint32_t outer=0;
 /* The original enters this loop even for count zero. Keep its wrapping
  * equality exit; a zero descriptor count is not an empty-list fast path. */
 do{
  uint32_t descriptor=word(c+12+outer*4);
  for(uint32_t i=0;i<selected;i++){
   uint32_t index=word(slots+i*8);sd(p+8,0);
   uint32_t address=word(descriptor+8+(index<<3));uint32_t qwords=half(descriptor+12+(index<<3));
   sd(p,((uint64_t)(address&0x0fffffffu)<<32)|(qwords|0x30000000u));p+=16;
  }
  uint32_t address=word(descriptor),qwords=half(descriptor+4);sd(p+8,0);
  sd(p,((uint64_t)(address&0x0fffffffu)<<32)|(qwords|0x30000000u));p+=16;++outer;
 }while(outer!=count);
 memset(at(p),0,16);ps2DmaChainAppendWithTail((uint32_t)chain,start,p);LEAVE(80);
}

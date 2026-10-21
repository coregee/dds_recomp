/* Original EE movie frame allocation, GS upload packets and update bodies. */
#include "movie_frame.h"
#include "movie_archive.h"
#include "movie_decoder.h"
#include "movie_refill.h"
#include "movie_manager.h"
#include "texture_construction.h"
#include "material_fiveword_pool.h"
#include "libc_stream.h"
#include "heap_queue.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveMovieArchiveAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void w64(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int64_t s64(uint64_t v){return v>>63?-1-(int64_t)~v:(int64_t)v;}
static uint32_t sar(uint32_t v,unsigned n){return (v>>n)|((v&0x80000000u)?(~UINT32_C(0)<<(32-n)):0);}
static uint64_t consume(uint32_t entry,uint64_t d,uint64_t p,uint64_t event,uint64_t buffer,uint64_t bytes){
#if UINTPTR_MAX > UINT32_MAX
 uint64_t a[5]={d,p,event,buffer,bytes};return nocturneMovieDecoderConsume(entry,a);
#else
 typedef uint64_t (*Callback)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
 return ((Callback)(uintptr_t)entry)(d,p,event,buffer,bytes);
#endif
}
/* 002aa350: GS formats use this table, including zero for unsupported values. */
uint64_t ps2VramFormatBits(uint64_t format){
 if(format>=59)return 0;
 switch(format){
 case 0:case 1:case 27:case 36:case 44:case 48:case 49:return 32;
 case 2:case 10:case 50:case 58:return 16;
 case 19:return 8;case 20:return 4;default:return 0;
 }
}
/* 002aa438: scan backwards and split a free extent from its low end. */
uint64_t ps2VramAllocateFront(uint64_t size,uint64_t category){
 uint32_t restore=ps2KernelDisableInterrupts(),node=r32(0x552090);
 for(;;){
  if(!node){
   uint32_t callback=r32(0x55185c);
   if(restore){(void)ps2KernelEnableInterrupts();callback=r32(0x55185c);}
   if(callback)nocturneVramErrorCallback(callback,size,category);
  }
  if(!r32(node+8)&&s64(sx(r32(node+16)))>=s64(size))break;
  node=r32(node+4);
 }
 if(sx(r32(node+16))==size){w32(node+8,(uint32_t)category);if(restore)(void)ps2KernelEnableInterrupts();return sx(node);}
 uint32_t allocated=ps2PoolAllocate(28),next=r32(node);
 w32(allocated,next);if(next)w32(r32(node)+4,allocated);else w32(0x552090,allocated);
 w32(allocated+8,(uint32_t)category);w32(node,allocated);
 w32(allocated+16,(uint32_t)size);w32(allocated+12,r32(node+12));w32(allocated+4,node);
 w32(node+12,r32(node+12)+(uint32_t)size);w32(node+16,r32(node+16)-(uint32_t)size);
 if(restore)(void)ps2KernelEnableInterrupts();return sx(allocated);
}
uint64_t ps2VramSurfaceAllocate(uint64_t width,uint64_t height,uint64_t format,uint64_t category,uint64_t front){
 uint32_t product=(uint32_t)width*(uint32_t)height;product*=(uint32_t)ps2VramFormatBits(format);
 uint64_t size=sx(sar(product,5));
 uint64_t result=front?ps2VramAllocateFront(size,category):ps2VramAllocate(size,category);
 uint32_t p=(uint32_t)result;w16(p+20,(uint32_t)width);w16(p+22,(uint32_t)height);w32(p+24,(uint32_t)format);return result;
}
void ps2MovieDecoderAllocateFrames(uint64_t decoder){
 uint32_t d=(uint32_t)decoder,length=r16(d+60)*r16(d+62)*(*at(d+20)?2u:4u);
 w32(d+28,length);w32(d+32,(uint32_t)ps2TextureStagingAllocate(sx(length)));
 w32(d+36,(uint32_t)ps2TextureStagingAllocate(sx(length)));
}
/* Both packet passes share the original decrementing macroblock counter. */
void ps2MovieDecoderBuildUploadPackets(uint64_t decoder){
 uint32_t d=(uint32_t)decoder,width=r16(d+60),height=r16(d+62),qwc=*at(d+20)?32u:64u;
 uint32_t blocks=(width>>4)*(height>>4),stride=width>>6,bytes=blocks*96+80;
 uint64_t bitblt=((uint64_t)(*at(d+20)?2u:0u)<<56)|((uint64_t)(stride?stride:1u)<<48);
 w32(d+48,bytes);
 for(unsigned pass=0;pass<2;pass++){
  uint32_t output=(uint32_t)ps2TextureStagingAllocate(sx(bytes)),input=r32(d+32+pass*4)&0x0fffffffu,packet=output;
  w32(d+40+pass*4,output);
  w64(packet,0x10000003);w64(packet+8,UINT64_C(0x5000000300000000));
  w64(packet+16,UINT64_C(0x1000000000000002));w64(packet+24,14);
  w64(packet+32,bitblt|((uint64_t)(r32(d+52)>>6)<<32));w64(packet+40,0x50);
  w64(packet+48,UINT64_C(0x1000000010));w64(packet+56,0x52);packet+=64;
  uint32_t y=0,ended=0;
  do{
   uint32_t x=0;
   do{
    blocks--;if(!blocks)ended=1;
    w64(packet,0x10000004);w64(packet+8,UINT64_C(0x5000000400000000));
    w64(packet+16,UINT64_C(0x1000000000000002));w64(packet+24,14);
    w64(packet+32,((uint64_t)y<<48)|((uint64_t)x<<32));w64(packet+40,0x51);
    w64(packet+48,0);w64(packet+56,0x53);
    w64(packet+64,UINT64_C(0x0800000000000000)|(ended<<15)|qwc);
    w64(packet+72,0);w64(packet+80,((uint64_t)input<<32)|0x30000000u|qwc);
    w64(packet+88,(uint64_t)(0x50000000u|qwc)<<32);
    input+=qwc*16;packet+=96;x+=16;
   }while(x<width);
   y+=16;
  }while(y<height);
 }
}
void ps2MovieDecoderReadStreamHeader(uint64_t decoder){
 uint32_t d=(uint32_t)decoder;if(*at(d+80))return;
 uint8_t header[16]={0};uint32_t ended=0;
#if UINTPTR_MAX > UINT32_MAX
 uint32_t flag=nocturneLibcStreamLocalAddress(&ended,4);
#else
 uint32_t flag=(uint32_t)(uintptr_t)&ended;
#endif
 uint64_t available=consume(r32(d+92),decoder,sx(r32(d+96)),0,flag,0);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 if(available<16)return;
 *at(d+80)=1;
#if UINTPTR_MAX > UINT32_MAX
 uint32_t target=nocturneLibcStreamLocalAddress(header,16);
#else
 uint32_t target=(uint32_t)(uintptr_t)header;
#endif
 (void)consume(r32(d+92),decoder,sx(r32(d+96)),1,target,16);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 uint16_t width,height;uint32_t frames;memcpy(&width,header+8,2);memcpy(&height,header+10,2);memcpy(&frames,header+12,4);
 w16(d+60,width);w16(d+62,height);w32(d+64,frames);
 if(!r32(d+52)){
  uint32_t w=width,h=height;if(w>64)w=(w+63)&~63u;
  uint32_t format=*at(d+20)?2u:0u,alignment=format?64u:32u;if(h>alignment)h=(h+alignment-1)&~(alignment-1);
  uint32_t extent=(uint32_t)ps2VramSurfaceAllocate(w,h,format,2,0);w32(d+56,extent);w32(d+52,r32(extent+12));
 }
 ps2MovieDecoderAllocateFrames(decoder);uint32_t restore=ps2KernelDisableInterrupts();ps2MovieDecoderQueueAppend(decoder,0);
 if(restore)(void)ps2KernelEnableInterrupts();
}
void ps2MovieUploadQueueAppend(uint64_t packet,uint64_t end){
 (void)ps2KernelWaitSema(r32(0x581018));uint32_t tail=r32(0x581028);
 if(tail){w64(tail+8,0);w64(tail,((uint64_t)((uint32_t)packet&0x0fffffffu)<<32)|0x20000000u);}
 else w32(0x581024,(uint32_t)packet);
 w32(0x581028,(uint32_t)end);(void)ps2KernelSignalSema(r32(0x581018));
}
uint64_t ps2MovieDecoderDeliverFrame(uint64_t decoder){
 uint32_t d=(uint32_t)decoder;if(!*at(d+26))return 0;
 uint32_t slot=d+40+(uint32_t)*at(d+25)*4;
 if(!r32(slot))ps2MovieDecoderBuildUploadPackets(decoder);
 uint32_t packet=r32(slot),end=packet+r32(d+48)-16;
 ps2MovieUploadQueueAppend(sx(packet),sx(end));ps2MovieDecoderFrameConsumed(decoder);return 1;
}
void ps2MovieDecoderUpdate(uint64_t delta){
 uint32_t active=r32(0x552154);if(active&&*at(active+18))ps2MovieDecoderInputDma(sx(active));
 uint32_t d=r32(0x552148);
 while(d){
  if(*at(d+19))*at(d+19)=(uint8_t)(*at(d+19)-1);
  uint32_t accumulator=*at(d+23),state=*at(d+16);
  if(state==1){(void)ps2MovieDecoderDeliverFrame(sx(d));*at(d+16)=2;*at(d+23)=*at(d+22);}
  else if(state==2){
   accumulator+=*at(d+22);
   if(s64(sx(accumulator))>=s64(delta)&&ps2MovieDecoderDeliverFrame(sx(d)))accumulator-=(uint32_t)delta;
   *at(d+23)=(uint8_t)accumulator;
  }
  if(*at(d+12)==1){
   ps2MovieDecoderReadStreamHeader(sx(d));
   if(*at(d+82)<8){uint32_t restore=ps2KernelDisableInterrupts();ps2MovieDecoderRefill(sx(d));if(restore)(void)ps2KernelEnableInterrupts();}
   (void)consume(r32(d+92),sx(d),sx(r32(d+96)),2,0,0);
  }
  d=r32(d+8);
 }
 ps2MovieDecoderSchedule(0);
}

/* Complete original preloaded IPU setup and input DMA-chain bodies. */
#include "movie_preloaded.h"
#include "movie_archive.h"
#include "movie_initialize.h"
#include "movie_frame.h"
#include "movie_manager.h"
#include "movie_decoder.h"
#include "texture_construction.h"
#include "material_fiveword_pool.h"
#include "draw_consumer_support.h"
#include "libc_stream.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveMovieArchiveAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w16(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w64(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static int64_t s32(uint32_t v){return v&0x80000000u?(int64_t)v-INT64_C(0x100000000):v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
void ps2MovieDecoderBuildInputChain(uint64_t decoder,uint64_t payload,uint64_t bytes){
 uint32_t remaining=((uint32_t)bytes+15u)&~15u;
 uint32_t count=(uint32_t)(s32(remaining+0xffeffu)/0xfff00);
 uint32_t packet=(uint32_t)ps2TextureStagingAllocate(sx(count<<4));
 w32((uint32_t)decoder+76,packet);uint32_t input=(uint32_t)payload&0x0fffffffu;
 do{
  uint32_t chunk=s32(remaining)>0xfff00?0xfff00:remaining;
  remaining-=chunk;
  uint32_t qwc=(uint32_t)(s32(chunk)/16)&0xffffu;
  w64(packet+8,0);w64(packet,((uint64_t)input<<32)|(remaining?0x30000000u:0u)|qwc);
  input+=chunk;packet+=16;
 }while(s32(remaining)>0);
 (void)ps2KernelFlushCache(0);
}
void ps2MovieDecoderInitializePreloaded(uint64_t decoder,uint64_t configuration,uint64_t image,uint64_t bytes){
 uint32_t d=(uint32_t)decoder,h=(uint32_t)image;
 ps2MovieDecoderClear(decoder,configuration);
 uint32_t width=r16(h+8),frames=r32(h+12);w16(d+60,width);w32(d+64,frames);w16(d+62,r16(h+10));
 ps2MovieDecoderAllocateFrames(decoder);
 ps2MovieDecoderBuildInputChain(decoder,sx(h+16),sx((uint32_t)bytes-16));
 uint32_t restore=ps2KernelDisableInterrupts();ps2MovieDecoderQueueAppend(decoder,0);
 if(restore)(void)ps2KernelEnableInterrupts();ps2MovieDecoderSchedule(0);
}
void ps2MovieDecoderPreloadedCreate(uint64_t decoder,uint64_t configuration,uint64_t image,uint64_t bytes,uint64_t display){
 ps2MovieDecoderInitializePreloaded(decoder,configuration,image,bytes);
 w32((uint32_t)decoder+52,(uint32_t)display);ps2MovieDecoderListAppend(decoder);
}
void ps2MovieDecoderPreloadedFromTexture(uint64_t decoder,uint64_t configuration,uint64_t image,uint64_t bytes,uint64_t texture){
 uint8_t local[4];memcpy(local,at((uint32_t)configuration),4);
 uint8_t format=*at((uint32_t)texture+26);if(!format)local[0]=0;else if(format==2)local[0]=1;
 uint64_t display=ps2TextureBaseAddress(texture);
#if UINTPTR_MAX > UINT32_MAX
 uint32_t temporary=nocturneLibcStreamLocalAddress(local,4);
#else
 uint32_t temporary=(uint32_t)(uintptr_t)local;
#endif
 ps2MovieDecoderPreloadedCreate(decoder,temporary,image,bytes,display);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
}

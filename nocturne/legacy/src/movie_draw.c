/* Complete PS2 movie packet construction and command queue. */
#include "movie_draw.h"
#include "movie_archive.h"
#include "deferred_drain.h"
#include "file_rpc.h"
#include "libc_stream.h"
#include "libc_printf.h"
#include "ps2_memory.h"
#include "material_fiveword_pool.h"
#include "draw_consumer_support.h"
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
static void w16(uint32_t a,uint32_t v){uint16_t n=(uint16_t)v;memcpy(at(a),&n,2);}
static void w64(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
static int32_t s16(uint32_t v){return (int32_t)(v&32767)-(int32_t)(v&32768);}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
uint64_t ps2KernelWakeupThreadRaw(uint64_t thread){return nocturneDrawSupportKernelValue(0x33,1,thread);}
uint64_t ps2MovieCommandPump(void){
 uint32_t head=r16(0x552132),tail=r16(0x552134);if(head==tail)return 1;
 uint32_t packet=0x590840+(uint32_t)s16(head)*128;
 uint64_t result=ps2SifSendCommandDefault(0,sx(packet),*at(packet+15)&0xf0,0,0,0);
 uint32_t next=(head+1)&31;
 if(!result){(void)ps2LibcPrintf(0x549950,0,0,0,0,0,0);return 1;}
 w16(0x552132,next);return 0;
}
uint64_t ps2MovieCommandEnqueue(uint64_t command,uint64_t flags,uint64_t source,uint64_t bytes){
 uint32_t token=r32(0x5519d0)+1;if(!token)token=1;w32(0x5519d0,token);
 uint32_t next=(uint32_t)(s16(r16(0x552134))+1)&31;
 if((int32_t)next==s16(r16(0x552132))){
  for(unsigned k=0;k<8;k++)do{(void)ps2KernelWakeupThreadRaw(sx(r32(0x552138)));}while(s16(r16(0x552132))!=(int32_t)next);
  return 0;
 }
 uint32_t packet=0x590840+(uint32_t)s16(r16(0x552134))*128;
 w32(packet+16,r32(0x5519d0));
 if(bytes)ps2Memcpy(at(packet+20),at((uint32_t)source),(uint32_t)bytes);
 uint32_t length=(uint32_t)(s32((uint32_t)bytes+35)>>4)<<28;
 w32(packet+12,((uint32_t)command<<16)|((uint32_t)flags&65535)|length);w16(0x552134,next);
 if(*at(0x552130)){while(ps2MovieCommandPump()){};return sx(r32(0x5519d0));}
 (void)ps2KernelWakeupThreadRaw(sx(r32(0x552138)));return sx(r32(0x5519d0));
}
void ps2MovieCommandTokenIgnore(uint64_t token){(void)token;}
uint64_t ps2MovieCommandSubmit(uint64_t command,uint64_t flags,uint64_t source,uint64_t bytes){
 uint64_t result=ps2MovieCommandEnqueue(command,flags,source,bytes);ps2MovieCommandTokenIgnore(result);return result;
}
uint64_t ps2MovieRegisterCommandCallback(uint64_t callback){
 if(r32(0x5519cc))return 0;w32(0x5519c4,(uint32_t)callback);return callback;
}
uint64_t ps2MovieSetOutputMode(uint64_t mode){
 uint32_t bits=((uint32_t)mode>>3)&15;if(r32(0x5519cc))return 1;
 (void)ps2MovieCommandSubmit(bits|0x120,0,0,0);return 0;
}
uint64_t ps2DrawChainCreate(uint64_t allocator){
 uint64_t chain;
 if(!allocator)allocator=0x2acb50;
#if UINTPTR_MAX > UINT32_MAX
 chain=nocturneMovieDrawAllocate((uint32_t)allocator,32);
#else
 chain=((uint64_t (*)(uint64_t))(uintptr_t)(uint32_t)allocator)(32);
#endif
 ps2DmaChainInitialize((uint32_t)chain);return chain;
}
void ps2MovieBuildDrawPacket(uint64_t control_raw,uint64_t ordering_raw){
 uint32_t control=(uint32_t)control_raw,ordering=(uint32_t)ordering_raw;
 if(*at(control+0x34)<2)return;
 if(*at(control+0x20)&&!*at(control+0x21)&&s32(r32(r32(control+0x1c)+0x68))>=4096){
  *at(control+0x21)=1;w32(0x552168,control);(void)ps2MovieRegisterCommandCallback(0x2c5098);(void)ps2MovieSetOutputMode(*at(control+0x22));
 }
 uint32_t packet=ps2WorkBufferTake(176),height=r16(control+0x62),width=r16(control+0x60);
 w64(packet+8,UINT64_C(0x5000000a00000000));w64(packet,0x100000a);w64(packet+16,UINT64_C(0x108b400000008009));
 uint32_t heightLog=31-EE_MMI_LEADING_SIGN_WORD(height-1);w64(packet+24,14);w64(packet+32,33);w64(packet+40,20);
 uint32_t widthLog=31-EE_MMI_LEADING_SIGN_WORD(width-1);
 uint64_t tex=sx(widthLog<<26)|((uint64_t)heightLog<<30)|UINT64_C(0x400000000);
 uint32_t stride=width>>6;if(!stride)stride=1;uint32_t base=r32(control+0x58)>>6;
 if(*at(control+0x38)){tex|=base;base=0x200000;}
 tex|=(uint64_t)stride<<14;tex|=base;
 int32_t y=s16(r16(control+6)),dy=s16(r16(control+14)),x=s16(r16(control+4)),dx=s16(r16(control+12));uint32_t z=r32(control+8);
 uint64_t first=((uint64_t)z<<32)|((uint32_t)y<<16)|(uint32_t)x;
 uint64_t second=((uint64_t)z<<32)|((uint32_t)(y+dy)<<16)|(uint32_t)(x+dx);
 uint64_t uv=sx(height<<20)|sx(width<<4);
 w64(packet+48,tex);w64(packet+72,8);w64(packet+80,UINT64_C(0x4000000080));w64(packet+88,59);w64(packet+96,UINT64_C(0xffffffff80808080));w64(packet+104,1);
 w64(packet+128,first);w64(packet+144,uv);w64(packet+152,3);w64(packet+160,second);w64(packet+168,5);w64(packet+64,5);w64(packet+120,3);w64(packet+136,5);w64(packet+56,6);w64(packet+112,0);
 uint64_t chain=ps2DrawChainCreate(0);ps2DmaChainAppend((uint32_t)chain,packet);
#if UINTPTR_MAX > UINT32_MAX
 nocturneMovieDrawInvoke(r32(ordering+16),ordering_raw,chain);
#else
 ((void (*)(uint64_t,uint64_t))(uintptr_t)r32(ordering+16))(ordering_raw,chain);
#endif
}
uint64_t ps2MovieDrawProcess(void){ps2MovieBuildDrawPacket(0x343e40,0x2f6638);return 0;}
uint64_t ps2MovieControlCheckEnd(uint64_t control){uint32_t p=(uint32_t)control;return *at(p+0x33)!=0&&*at(p+0x3e)==0;}
uint64_t ps2MovieCheckEnd(void){return ps2MovieControlCheckEnd(0x343e40);}
uint64_t ps2MovieCheckDrawState(void){return *at(0x343e74);}

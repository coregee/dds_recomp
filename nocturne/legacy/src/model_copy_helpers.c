/* Original optional16-byte-list and material parameter copies. */
#include "model_copy_helpers.h"
#include "material_fiveword_pool.h"
#include "ps2_memory.h"
#include "resource_loader_flow.h"
#include <string.h>
#if UINTPTR_MAX > UINT32_MAX
#define ENTER(n) nocturneResourceFrameEnter(n)
#define LEAVE(n) nocturneResourceFrameLeave(n)
static void *at(uint32_t a){return nocturneResolveModelCopyAddress(a);}
#else
#define ENTER(n) ((void)0)
#define LEAVE(n) ((void)0)
static void *at(uint32_t a){return (void *)(uintptr_t)a;}
#endif
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static int32_t signedHalf(uint32_t a){uint32_t v=half(a);return v&0x8000u?(int32_t)v-65536:(int32_t)v;}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)(int32_t)v;}
void ps2ModelCopyOptionBuffer(uint64_t destination,uint64_t source){
 ENTER(16);
 if(destination){uint32_t d=(uint32_t)destination;int32_t count=signedHalf(d+4);
  if(count>0){uint32_t output=word(d+12),input=word((uint32_t)source+12);ps2Memcpy(at(output),at(input),(uint32_t)count<<4);}
 }LEAVE(16);
}
/* Native LDL/LDR loads all three qwords before any SDL/SDR store. */
static void copy24(uint32_t output,uint32_t input){
 uint64_t a,b,c;memcpy(&a,at(input),8);memcpy(&b,at(input+8),8);memcpy(&c,at(input+16),8);
 memcpy(at(output),&a,8);memcpy(at(output+8),&b,8);memcpy(at(output+16),&c,8);
}
void ps2MaterialCopyParameters(uint64_t destination,uint64_t source){
 ENTER(32);uint32_t d=(uint32_t)destination,s=(uint32_t)source;uint8_t flags=255;memcpy(at(d+6),&flags,1);
 uint32_t value=word(s+16),scalar=word(s+28);sw(d+16,value);uint16_t kind=half(s+4);value=word(s+20);uint32_t texture=word(s+44);sw(d+20,value);
 uint32_t block=word(s+56);value=word(s+24);sw(d+28,scalar);sw(d+24,value);sh(d+4,kind);value=word(s+32);sw(d+44,texture);sw(d+32,value);value=word(s+40);sw(d+40,value);
 if(block){uint32_t output=ps2MatGetFiveWords38(at(d));copy24(output,block);}
 block=word(s+60);if(block){uint32_t output=ps2MatGetFiveWords3C(at(d));copy24(output,block);}
 scalar=word(s+64);sw(d+64,scalar);scalar=word(s+68);sw(d+68,scalar);LEAVE(32);
}
void ps2MaterialCopyListParameters(uint64_t destination,uint64_t source){
 ENTER(48);uint32_t d=(uint32_t)destination,s=(uint32_t)source;int32_t count=signedHalf(d+4);uint32_t input=word(s+12),output=word(d+12);
 for(int32_t i=0;i<count;i++){uint32_t target=word(output+((uint32_t)i<<2)),origin=word(input+((uint32_t)i<<2));ps2MaterialCopyParameters(sx(target),sx(origin));}
 LEAVE(48);
}

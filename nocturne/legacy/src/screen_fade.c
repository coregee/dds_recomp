#include "screen_fade.h"
#include "script_construction.h"
#include "script_core.h"
#include "script_movie.h"
#include "script_lifetime.h"
#include "deferred_drain.h"
#include "message_frame_draw.h"
#include "compiler_numeric.h"
#include <string.h>
static void *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static uint32_t byte(uint32_t a){return *(uint8_t *)at(a);}
static void sw(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void sh(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static void sb(uint32_t a,uint32_t v){*(uint8_t *)at(a)=(uint8_t)v;}
static void sd(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 00104f78: clearing RGB/alpha and direction bits leaves both counters alone. */
void dds3FadeClear(void)
{uint32_t flags=word(0x54e95c)&~UINT32_C(3);sb(0x54e97b,0);sw(0x54e95c,flags);sb(0x54e978,0);sb(0x54e979,0);sb(0x54e97a,0);}
/* 00104fa0: native four-byte setter has no reviewed HD ColorGet identity. */
void ps2FadeSetRGBA(uint64_t r,uint64_t g,uint64_t b,uint64_t a)
{uint32_t flags=word(0x54e95c)&~UINT32_C(3);sb(0x54e97b,(uint32_t)a);sw(0x54e95c,flags);sb(0x54e978,(uint32_t)r);sb(0x54e979,(uint32_t)g);sb(0x54e97a,(uint32_t)b);}
/* 00104fc8 */
void dds3FadeColorSet(uint64_t r,uint64_t g,uint64_t b)
{sb(0x54e97a,(uint32_t)b);sb(0x54e978,(uint32_t)r);sb(0x54e979,(uint32_t)g);}
/* 00104fe0: the zero test uses all64 frame bits before narrowing to SH. */
void dds3FadeIn(uint64_t r,uint64_t g,uint64_t b,uint64_t frames)
{
 sb(0x54e97b,128);sb(0x54e978,(uint32_t)r);sb(0x54e979,(uint32_t)g);sb(0x54e97a,(uint32_t)b);
 if(!frames){sb(0x54e97b,0);sh(0x551bb8,0);sh(0x551bba,0);dds3FadeClear();return;}
 uint32_t flags=(word(0x54e95c)|1)&~UINT32_C(2);sh(0x551bb8,(uint32_t)frames);sh(0x551bba,(uint32_t)frames);sw(0x54e95c,flags);
}
/* 00105048: unlike colored FadeIn, zero frames preserves the existing RGB. */
void dds3FadeIn2(uint64_t frames)
{
 sb(0x54e97b,128);
 if(!frames){sb(0x54e97b,0);uint32_t flags=word(0x54e95c)&~UINT32_C(3);sh(0x551bb8,0);sw(0x54e95c,flags);sh(0x551bba,0);return;}
 uint32_t flags=(word(0x54e95c)|1)&~UINT32_C(2);sh(0x551bb8,(uint32_t)frames);sh(0x551bba,(uint32_t)frames);sw(0x54e95c,flags);
}
/* 00105098 / 001050f8 */
void dds3FadeOut(uint64_t r,uint64_t g,uint64_t b,uint64_t frames)
{
 sb(0x54e978,(uint32_t)r);sb(0x54e979,(uint32_t)g);sb(0x54e97a,(uint32_t)b);sb(0x54e97b,0);
 if(!frames){uint32_t flags=word(0x54e95c)&~UINT32_C(3);sh(0x551bb8,0);sh(0x551bba,0);sb(0x54e97b,128);sw(0x54e95c,flags);return;}
 uint32_t flags=(word(0x54e95c)&~UINT32_C(1))|2;sh(0x551bba,(uint32_t)frames);sh(0x551bb8,0);sw(0x54e95c,flags);
}
void dds3FadeOut2(uint64_t frames)
{
 sb(0x54e97b,0);
 if(!frames){uint32_t flags=word(0x54e95c)&~UINT32_C(3);sh(0x551bb8,0);sb(0x54e97b,128);sw(0x54e95c,flags);sh(0x551bba,0);return;}
 uint32_t flags=(word(0x54e95c)&~UINT32_C(1))|2;sh(0x551bba,(uint32_t)frames);sh(0x551bb8,0);sw(0x54e95c,flags);
}
/* 00105148 / 00105158: original update has no HD early-final-frame handling. */
uint64_t dds3FadeCheck(void){return (word(0x54e95c)&3)!=0;}
void dds3FadeUpdate(void)
{
 if(!dds3FadeCheck())return;
 uint32_t flags=word(0x54e95c),in=flags&1,out=flags&2;
 sh(0x551bb8,half(0x551bb8)+(in?65535:1));
 uint32_t count=half(0x551bb8),total=half(0x551bba);
 if(!total)nocturneCompilerArithmeticTrap(7);
 sb(0x54e97b,(count<<7)/total);
 if((in&&!count)||(out&&count==total)){
  sh(0x551bb8,0);sh(0x551bba,0);sw(0x54e95c,flags&~UINT32_C(3));
 }
}
/* 00117b08: actual work allocator and actual chain initialization. */
uint64_t ps2DrawCreateDmaChain(void)
{uint32_t chain=ps2WorkBufferTake(32);ps2DmaChainInitialize(chain);return sx(chain);}
/* 001052d8: build the full native176-byte overlay packet, then real OT append.
 * Alpha above128 remains unchecked; the shifted negative word sign extends. */
void dds3DrawFade(void)
{
 uint32_t context=(uint32_t)ps2KernelGetFontContextIndex(),alpha=byte(0x54e97b);
 if(!alpha)return;
 uint64_t rgba=sx((128-alpha)<<24)|byte(0x54e978)|((uint64_t)byte(0x54e979)<<8)|((uint64_t)byte(0x54e97a)<<16)|UINT64_C(0x3f80000000000000);
 uint32_t p=0x5570c0+context*176;
 sb(p+3,0x70);sb(p+2,0);sd(p+16,UINT64_C(0x1000000000000004));sd(p+24,14);sd(p+40,0x42);sd(p+32,1);sw(p+12,0x5000000a);sd(p+56,0x49);sh(p,10);sd(p+48,0);
 sd(p+72,0x4a);sd(p+64,0);sd(p+88,0x47);sd(p+80,0x31003);sd(p+96,UINT64_C(0x1023400000008004));sd(p+104,14);sd(p+136,5);sd(p+120,1);sd(p+112,rgba);sd(p+128,UINT64_C(0x00feffff79007000));sd(p+152,1);sd(p+144,rgba);sd(p+168,5);sw(p+4,0);sd(p+160,UINT64_C(0x00feffff87009000));sw(p+8,0);
 uint64_t chain=ps2DrawCreateDmaChain();ps2DmaChainAppend((uint32_t)chain,p);
 nocturneInvokeMessageDrawOrder(word(0x2f6908),0x2f68f8,chain);
}
/* 0010ba38 / 0010bad8: first command entry yields; any nonzero timer completes. */
uint64_t scrCommand_FADE_IN(void)
{
 if(scrGetCommandTimer())return 1;
 uint64_t mode=scrGetIntPara(0);if(mode!=0&&mode!=1)return 1;
 uint64_t frames=scrGetIntPara(1),color=mode?255:0;dds3FadeIn(color,color,color,frames);return 0;
}
uint64_t scrCommand_FADE_OUT(void)
{
 if(scrGetCommandTimer())return 1;
 uint64_t mode=scrGetIntPara(0);if(mode!=0&&mode!=1)return 1;
 uint64_t frames=scrGetIntPara(1),color=mode?255:0;dds3FadeOut(color,color,color,frames);return 0;
}

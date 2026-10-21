#include "message_request.h"
#include "message_commands.h"
#include "font_message.h"
#include "font_parser_support.h"
#include "script_lifetime.h"
#include "script_core.h"
#include "script_movie.h"
#include "panel_construction.h"
#include "libc_printf.h"
#include "compiler_numeric.h"
#include "script_construction.h"
#include <string.h>
static uint8_t *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static int32_t sh(uint32_t a){uint32_t v=half(a);return (int32_t)(v&32767)-(int32_t)(v&32768);}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void ph(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t asr3(uint32_t v){return (v>>3)|((v&0x80000000u)?UINT32_C(0xe0000000):0);}
/* 001cf778: native signed height; BREAK7 has no normal return. */
uint64_t CountLineMessage(uint64_t top,uint64_t font)
{
 uint32_t a=word((uint32_t)top+8),b=word((uint32_t)font+8);int32_t height=sh((uint32_t)font+18);
 uint32_t distance=asr3(b-a);if(!height)nocturneCompilerArithmeticTrap(7);
 int64_t signedDistance=(int64_t)distance-((distance&0x80000000u)?INT64_C(4294967296):0);
 return sx((uint32_t)(signedDistance/height)+1);
}
/* 001ceb38: raw callback word stored in the native twenty-byte slot. */
void itfMesMngSetKutiCallback(uint64_t id,uint64_t function)
{put(word(0x56be8c+(uint32_t)id*20)+0x1d0,(uint32_t)function);}
/* 001d1640: original callback installed by 001d1470. */
uint64_t ps2MessageKutiDiagnostic(void){return ps2LibcPrintf(0x535c18);}
/* 001cf1d8: native ReadytoMessage with real parser and stored callback. */
void ps2MessageReady(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,m=p+36;uint64_t old=sx(word(m+12));
 if(old){(void)frDestroyFontRequestAfter(old);put(m+12,0);}
 uint64_t text=GetMessagePagePtr(sx(word(m+8)),sx((uint32_t)sh(m+24)));
 uint64_t font=ps2FontMessageRequest(sx(word(m)),sx(word(m+4)),*at(m+18),*at(m+19),*at(m+20),*at(m+21),text,0);
 if(!(word(p)&0x400000)&&(half(0x56be6c)&1))RaiseMessageSpeedMax(font);
 GetLastMessagePara(font,sx(m));uint64_t bits=ps2FontTestGlobalFlags(3);*at(m+17)=(uint8_t)bits;
 if(bits&2)put(p,word(p)|0x10000);else put(p,word(p)&0xfffeffff);
 if(ps2FontTestGlobalFlags(4)){uint32_t fn=word(p+0x1d0);if(fn)nocturneInvokeMessageKutiCallback(fn);}
 ChangeZBuffer(font,sx(word(p+12)));uint64_t last=GetLastLinkFontHandle(font),lines=CountLineMessage(last,font);
 put(m+12,(uint32_t)font);ph(m+22,(uint32_t)lines);
}
/* 001cdb80: speaker ID is re-read from the resource after text preparation. */
uint64_t itfMesMngRequestMessage(uint64_t id,uint64_t message,uint64_t page)
{
 uint32_t p=word(0x56be8c+(uint32_t)id*20),m=p+36,s=p+20;
 uint32_t record=(uint32_t)ps2MessageGetResourceEntry(sx(p),message),resource=word(record+4);
 ph(m+24,(uint32_t)page);put(m+8,resource);ph(m+26,half(resource+24));
 if(!sh(resource+24)){(void)ps2LibcPrintf(0x535a80);return 0;}
 CommitVarTable(sx(p+196));uint64_t binding=sx(word(p+8));if(binding)ps2FontBindMessageStyle(binding);
 ps2MessageReady(sx(p));uint32_t speaker=half(resource+26);
 if(half(s+12)!=speaker){
  uint64_t old=sx(word(s+8));if(old){(void)frDestroyFontRequestAfter(old);put(s+8,0);}
  ph(s+12,speaker);
  if(speaker!=65535){
   uint64_t panel=sx(word(p+156));if(panel){itfPnlRelease(panel);put(p+156,0);}
   uint64_t text=(speaker&0x8000)?itfMesMngGetVarLocalize(id,speaker&32767):GetSpeakerName(sx(p));
   uint64_t font=ps2FontMessageRequest(sx(word(s)),sx(word(s+4)),0,3,0,8,text,0);put(s+8,(uint32_t)font);
   frSetDrawPosition(sx(word(s+8)),sx(word(s)),sx(word(s+4)));frSetDrawSpeed(sx(word(s+8)),10);ChangeZBuffer(sx(word(s+8)),sx(word(p+12)));
  }
 }
 ps2MessageOpenSpeakerPanel(sx(p));uint32_t flags=word(p),phase=flags&0x300;
 if((flags&0x200000)&&(phase==0||phase==0x300)){ps2MessageOpenPanel(sx(p));put(p,(word(p)&~UINT32_C(7))|2);}
 else put(p,(flags&~UINT32_C(7))|3);
 *at(m+16)=1;return 1;
}
/* 001cd2e0: sign of the live completion byte decides wait versus consume. */
uint64_t itfMesMngMessage(void)
{
 uint64_t id=scrGetMessageHandle();if(id>>63)return 1;
 uint32_t p=word(0x56be8c+(uint32_t)id*20);uint64_t message=scrGetIntPara(0);int8_t state=(int8_t)*at(p+52);
 if(!state)return itfMesMngRequestMessage(id,message,0)?0:1;
 if(state>=0)return 0;*at(p+52)=0;return 1;
}

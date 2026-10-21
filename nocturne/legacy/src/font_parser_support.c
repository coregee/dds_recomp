#include "font_parser_support.h"
#include "font_text.h"
#include "font_resource.h"
#include "message_commands.h"
#include "script_construction.h"
#include "libc_stream.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveScriptConstructionAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint32_t sb(uint32_t v){v&=255;return v&128?v|0xffffff00u:v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 001c7a88: spacing store precedes the actual linked-list measurement. */
void frSetFontSpace(uint64_t font,uint64_t spacing)
{uint32_t f=(uint32_t)font;*at(f+1)=(uint8_t)spacing;put(f+12,(uint32_t)ps2FontMeasureRequest(font));}
/* 001c7b40: native SRL uses only the lower argument word. */
void ps2FontSetDepth(uint64_t font,uint64_t depth){put((uint32_t)font+20,(uint32_t)depth>>4);}
/* Both mode routines return the old unsigned byte, including upper-lane inputs. */
uint64_t frEnableMode(uint64_t flag){uint32_t old=*at(0x54f41c);*at(0x54f41c)=(uint8_t)(old|flag);return old;}
uint64_t frDisableMode(uint64_t flag){uint32_t old=*at(0x54f41c);*at(0x54f41c)=(uint8_t)(old&~(uint32_t)flag);return old;}
/* 001c81b8: message font context is native slot eight. */
void ps2FontBindMessageStyle(uint64_t data){ps2FontBindContext(8,data,0);}
/* 001c86a0: pending newline and position flags are separate live fields. */
void frCreateNewHandle(uint64_t message)
{
 uint32_t m=(uint32_t)message,f=word(m+20);
 if(f&&!word(f+28))*at(m+28)=0;
 if(*at(m+28)){
  uint64_t created=ps2FontAppendStringCombined(0x54f430,0,sx(sb(*at(m+13))),sx(sb(*at(m+14))),sx(f));
  put(m+20,(uint32_t)created);frSetDrawSpeed(created,*at(m+15));*at(m+28)=0;
 }
 if(*at(m+29)){frSetDrawPosition(sx(word(m+20)),sx(word(m)),sx(word(m+4)));*at(m+29)=0;}
}
/* 001c8730: wrapping word arithmetic and both pending flags. */
void ps2FontAdvanceMessageLine(uint64_t message)
{uint32_t m=(uint32_t)message,increment=word(0x54f40c)<<3,y=word(m+4);*at(m+29)=1;*at(m+28)=1;put(m+4,y+increment);}
/* 001c8758: big-endian character bytes, actual newline/string/spacing/depth. */
void ps2FontAppendSpecialCode(uint64_t message,uint64_t code)
{
 uint32_t m=(uint32_t)message;uint8_t bytes[16]={0};bytes[0]=(uint8_t)(code>>8);bytes[1]=(uint8_t)code;
#if UINTPTR_MAX > UINT32_MAX
 uint32_t local=nocturneLibcStreamLocalAddress(bytes,sizeof(bytes));
#else
 uint32_t local=(uint32_t)(uintptr_t)bytes;
#endif
 frCreateNewHandle(message);
 uint64_t font=ps2FontAppendString(local,sx(sb(*at(m+12))),sx(sb(*at(m+13))),sx(sb(*at(m+14))),sx(word(m+20)),0);
 put(m+20,(uint32_t)font);frSetFontSpace(font,sx(sb(*at(0x54f408))));ps2FontSetDepth(sx(word(m+20)),sx(word(m+8)));
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
}
/* 001c8508: read each live style and request after the recovered callees. */
void ps2FontAppendVariable(uint64_t index,uint64_t message)
{
 uint32_t string=word(0x56bbd0+((uint32_t)index&255)*4),m=(uint32_t)message;uint8_t bytes[16]={0};(void)ps2Memset(bytes,0,3);
 if(!string)return;
 uint32_t length=ps2Strlen((const char *)at(string)),position=0,previous=sb(*at(m+12));if((int32_t)length<=0)return;
#if UINTPTR_MAX > UINT32_MAX
 uint32_t local=nocturneLibcStreamLocalAddress(bytes,sizeof(bytes));
#else
 uint32_t local=(uint32_t)(uintptr_t)bytes;
#endif
 while(position<length){
  uint32_t first=*at(string+position),code;bytes[0]=(uint8_t)first;
  if(first&128){position++;bytes[1]=*at(string+position);code=first<<8|bytes[1];}else{bytes[1]=0;code=first;}
  uint32_t style=sb(*at(m+12));
  if(style!=previous){uint64_t font=sx(word(m+20));if(!font||word((uint32_t)font+28)){font=ps2FontAppendStringCombined(0x54f430,0,sx(sb(*at(m+13))),sx(sb(*at(m+14))),font);put(m+20,(uint32_t)font);}
   frSetDrawSpeed(font,*at(m+15));previous=style;
  }
  uint64_t font=ps2FontAppendString(local,sx(style),sx(sb(*at(m+13))),sx(sb(*at(m+14))),sx(word(m+20)),position<1);position++;
  put(m+20,(uint32_t)font);frSetFontSpace(font,sx(sb(*at(0x54f408))));ps2FontRecordLastCode(code);
 }
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
}
/* 001c9d60: live native name pairs/counts, then real string construction. */
uint64_t ps2FontAppendResourceName(uint64_t index,uint64_t style,uint64_t font,uint64_t color)
{
 uint32_t id=sb((uint32_t)index),metric=sb((uint32_t)style),table=word(0x54ea20),countOffset=id+0x6654,offset=id*20,position=0,k=0;
 uint8_t bytes[528]={0};
 while(k<*at(table+countOffset)){
  uint32_t p=table+offset+0x6604,first=*at(p);
  if(first){bytes[position++]=(uint8_t)first;table=word(0x54ea20);bytes[position]=*at(table+offset+0x6605);}
  else bytes[position]=*at(p+1);
  table=word(0x54ea20);k++;position++;offset+=2;
 }
 bytes[position]=0;
#if UINTPTR_MAX > UINT32_MAX
 uint32_t local=nocturneLibcStreamLocalAddress(bytes,sizeof(bytes));
#else
 uint32_t local=(uint32_t)(uintptr_t)bytes;
#endif
 (void)frEnableMode(1);uint64_t result=ps2FontAppendStringCombined(local,sx(metric),sx(sb((uint32_t)color)),0,font);(void)frDisableMode(1);frSetFontSpace(result,4);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 return result;
}

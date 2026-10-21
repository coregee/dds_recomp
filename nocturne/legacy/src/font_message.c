#include "font_message.h"
#include "font_parser_support.h"
#include "font_text.h"
#include "font_resource.h"
#include "message_commands.h"
#include "material_fiveword_pool.h"
#include "script_construction.h"
#include "libc_printf.h"
#include "libc_stream.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneResolveScriptConstructionAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void ph(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static uint32_t sb(uint32_t v){v&=255;return v&128?v|0xffffff00u:v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t local(void *p,uint32_t n){
#if UINTPTR_MAX > UINT32_MAX
 return nocturneLibcStreamLocalAddress(p,n);
#else
 (void)n;return (uint32_t)(uintptr_t)p;
#endif
}
static void endLocal(void){
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
}
/* 001c96d8: original 32-byte load/store stages and actual allocation/upload. */
uint64_t ps2FontLoadNameBitmapBank(uint64_t bank,uint64_t second,uint64_t count,uint64_t pixels)
{
 uint32_t b=sb((uint32_t)bank),n=sb((uint32_t)count),work=word(0x54ea20),offset=b<<1;
 uint32_t start=((uint32_t)second&255)?sb(*at(work+offset+0x657c)):0;
 uint32_t clearCount=sb(*at(work+offset+0x657c+(((uint32_t)second&255)?1:0))),limit=start+clearCount;
 if((int32_t)start<(int32_t)limit){uint32_t out=0x56bc50+((b<<4)+start)*4,left=limit-start;do{left--;put(out,0);out+=4;}while(left);}
 if((int32_t)n>0){uint32_t out=0x56bc50+((b<<4)+start)*4,input=(uint32_t)pixels;
  do{uint32_t output=ps2PoolAllocate(0x120);for(uint32_t k=0;k<0x120;k+=32){uint8_t block[32];memcpy(block,at(input+k),32);memcpy(at(output+k),block,32);}
   uint64_t glyph=ps2FontCreateTextureGlyph(24,24,sx(output),1);n--;input+=0x120;put(out,(uint32_t)glyph);out+=4;ph((uint32_t)glyph,b);
  }while(n);
 }
 return ps2LibcPrintf(0x535998,sx(b));
}
/* 001c98c0: lazy two-part load, then increment by the selected unsigned count. */
void ps2FontReferenceNameBitmapBank(uint64_t bank,uint64_t second)
{
 uint32_t b=sb((uint32_t)bank),p=0x56bd50+b*4,refs=word(p),offset=b<<1;
 if(!refs){uint32_t work=word(0x54ea20),count=sb(*at(work+offset+0x657c)),pixels=work+b*0x1200+0x1d7c;
  (void)ps2FontLoadNameBitmapBank(sx(b),0,sx(count),sx(pixels));work=word(0x54ea20);pixels=work+b*0x1200+count*0x120+0x1d7c;
  (void)ps2FontLoadNameBitmapBank(sx(b),1,sx(sb(*at(work+offset+0x657d))),sx(pixels));refs=word(p);
 }
 uint32_t work=word(0x54ea20),count=*at(work+offset+0x657c+((((uint32_t)second&255)!=0)?1:0));put(p,refs+count);
}
/* 001c9a98: global-work big-endian code pair and native control-glyph append. */
uint64_t ps2FontAppendNameBitmapGlyph(uint64_t bank,uint64_t index,uint64_t font)
{
 uint32_t slot=(sb((uint32_t)bank)<<4)+sb((uint32_t)index),p=word(0x54ea20)+slot*2+0x6584,code=*at(p)<<8|*at(p+1),glyphIndex=code-32;
 ps2FontRecordLastCode(code);uint64_t result=ps2FontCreateControlGlyph(sx(word(0x56bc50+slot*4)),font);uint32_t text=word((uint32_t)result+32);ph(text,code);
 ps2FontLayoutGlyph(sx(text),sx(glyphIndex),0);put(word((uint32_t)result+32)+8,(uint32_t)ps2FontGetGlyphStorageSize());return result;
}
uint64_t ps2FontAppendNameFirst(uint64_t bank,uint64_t font,uint64_t color)
{
 uint32_t b=sb((uint32_t)bank),offset=(b<<1)+0x657c,k=0,index=0;ps2FontReferenceNameBitmapBank(sx(b),0);
 while(k<*at(word(0x54ea20)+offset)){font=ps2FontAppendNameBitmapGlyph(sx(b),sx(index),font);k++;index=sb(index+1);*at(word((uint32_t)font+32)+20)=(uint8_t)color;}return font;
}
uint64_t ps2FontAppendNameSecond(uint64_t bank,uint64_t font,uint64_t color)
{
 uint32_t b=sb((uint32_t)bank),offset=b<<1,index=sb(*at(word(0x54ea20)+offset+0x657c)),k=0;ps2FontReferenceNameBitmapBank(sx(b),1);
 while(k<*at(word(0x54ea20)+offset+0x657d)){font=ps2FontAppendNameBitmapGlyph(sx(b),sx(index),font);k++;index=sb(index+1);*at(word((uint32_t)font+32)+20)=(uint8_t)color;}return font;
}
uint64_t ps2FontAppendNameBoth(uint64_t bank,uint64_t font,uint64_t color)
{
 uint64_t second=ps2FontAppendNameSecond(sx(sb((uint32_t)bank)),font,color);uint32_t f=(uint32_t)second,total=word(f+12),tail=word(f+32);put(f+12,total+8);put(tail+12,word(tail+12)+8);
 return ps2FontAppendNameFirst(sx(sb((uint32_t)bank)),second,color);
}
/* 001c87c8: complete native tag dispatch,including unknown-tag cursor skipping. */
uint64_t ps2FontParseMessageTag(uint64_t prefix,uint64_t message)
{
 uint32_t m=(uint32_t)message,pos=word(m+24),string=word(m+16),color=sb(*at(m+13)),next=pos+1;
 uint32_t command=((uint32_t)prefix<<8)|*at(string+pos);put(m+24,next);
 switch(command){
 case 0xf104:put(0x54f404,word(0x54f404)|1);return 1;
 case 0xf110:put(0x54f404,word(0x54f404)|2);return 1;
 case 0xf111:if(*at(0x54f41c)&8){put(0x54f404,word(0x54f404)|1);return 1;}break;
 case 0xf112:put(0x54f404,word(0x54f404)|4);break;
 case 0xf10f:if(!(*at(0x54f41c)&4))ps2FontAdvanceMessageLine(message);break;
 case 0xf113:case 0xf114:case 0xf115:{uint32_t base=command==0xf113?0x80e2:command==0xf114?0x80e4:0x80e0;uint64_t found=ps2FontFindCode416(half(0x54ea00));ps2FontAppendSpecialCode(message,base+((found>>63)?0:1));break;}
 case 0xf116:if(ps2FontFindCode416(half(0x54ea00))>>63)ps2FontAppendSpecialCode(message,0x80e2);break;
 case 0xf117:ps2FontAppendSpecialCode(message,(ps2FontFindCode416(half(0x54ea00))>>63)?0x80e7:0x80e6);break;
 case 0xf118:if((ps2FontFindCode416(half(0x54ea00))>>63)&&(ps2FontFindCode264(half(0x54ea00))>>63))ps2FontAppendSpecialCode(message,0x80e9);ps2FontAppendSpecialCode(message,0x80e8);break;
 case 0xf202:case 0xf206:case 0xf207:case 0xf209:{uint32_t field=command==0xf202?13:command==0xf206?12:command==0xf207?15:14;*at(m+field)=(uint8_t)(*at(string+next)+255);put(m+24,next+2);break;}
 case 0xf203:if(word(0x56bbcc+*at(string+next)*4)){frCreateNewHandle(message);uint32_t index=(*at(word(m+16)+word(m+24))+255)&255;ps2FontAppendVariable(index,message);}put(m+24,word(m+24)+2);break;
 case 0xf20a:case 0xf20b:case 0xf20c:case 0xf20d:{uint32_t index=sb(*at(string+next)-1);put(m+24,next+2);frCreateNewHandle(message);uint64_t font=sx(word(m+20));
  if(command==0xf20a)font=ps2FontAppendNameBoth(sx(index),font,sx(color));
  else if(command==0xf20b)font=ps2FontAppendNameFirst(sx(index),font,sx(color));
  else if(command==0xf20c)font=ps2FontAppendNameSecond(sx(index),font,sx(color));
  else font=ps2FontAppendResourceName(sx(index),sx(sb(*at(m+12))),font,sx(color));
  put(m+20,(uint32_t)font);if(command==0xf20d)(void)frEnableMode(1);frSetFontSpace(font,sx(sb(*at(0x54f408))));if(command==0xf20d)frSetDrawSpeed(sx(word(m+20)),*at(m+15));break;}
 case 0xf20e:put(m+24,next+1);break;
 default:put(m+24,word(m+24)+((((uint32_t)prefix&15)-1)<<1));break;
 }
 if(!*at(m+28))*at(m+28)=1;return 0;
}
/* 001c8f08: full mixed-byte parser and native prefix/termination behavior. */
uint64_t ps2FontParseMessage(uint64_t message)
{
 uint32_t m=(uint32_t)message,string=word(m+16),first=1;uint8_t bytes[16]={0};uint32_t scratch=local(bytes,sizeof(bytes));
 if((*at(string)&0xf0)!=0xf0&&*at(string+1)==8)put(m+24,word(m+24)+4);
 put(0x54f404,word(0x54f404)&~7u);(void)frEnableMode(1);
 for(;;){uint32_t pos=word(m+24),code=*at(word(m+16)+pos);put(m+24,pos+1);if(!code)break;
  if((code&0xf0)==0xf0){if(ps2FontParseMessageTag(code,message))break;continue;}
  if(code==10){if(*at(0x54f41c)&4)ps2FontAdvanceMessageLine(message);first=1;continue;}
  frCreateNewHandle(message);uint32_t style=sb(*at(m+12));
  if(code<128){bytes[0]=(uint8_t)code;bytes[1]=0;uint64_t f=ps2FontAppendString(scratch,sx(style),sx(sb(*at(m+13))),sx(sb(*at(m+14))),sx(word(m+20)),first);put(m+20,(uint32_t)f);}
  else{pos=word(m+24);code=code<<8|*at(word(m+16)+pos);put(m+24,pos+1);if(code>0xc07f){code-=0x4000;style=8;}bytes[0]=(uint8_t)(code>>8);bytes[1]=(uint8_t)code;bytes[2]=0;
   uint64_t f=ps2FontAppendString(scratch,sx(style),sx(sb(*at(m+13))),sx(sb(*at(m+14))),sx(word(m+20)),first);put(m+20,(uint32_t)f);ps2FontRecordLastCode(code&65535);
  }
  first=0;frSetFontSpace(sx(word(m+20)),sx(sb(*at(0x54f408))));ps2FontSetDepth(sx(word(m+20)),sx(word(m+8)));
 }
 (void)frDisableMode(1);(void)frEnableMode(2);uint64_t result=sx(word(m+20));endLocal();return result;
}
/* 001c9188: argument nine comes from caller stack; private record is native32. */
uint64_t ps2FontMessageRequestEx(uint64_t x,uint64_t y,uint64_t z,uint64_t style,uint64_t color,uint64_t transparency,uint64_t speed,uint64_t text,uint64_t font)
{
 uint8_t record[32]={0};uint32_t p=local(record,sizeof(record));put(p,(uint32_t)x);put(p+4,(uint32_t)y);put(p+8,(uint32_t)z<<4);*at(p+12)=(uint8_t)style;*at(p+13)=(uint8_t)color;*at(p+14)=(uint8_t)transparency;*at(p+15)=(uint8_t)speed;put(p+16,(uint32_t)text);put(p+20,(uint32_t)font);put(p+24,0);*at(p+28)=1;*at(p+29)=1;
 uint64_t result=ps2FontParseMessage(p);endLocal();return result;
}
/* 001c9140: byte masking and actual zero-depth constructor. */
uint64_t ps2FontMessageRequest(uint64_t x,uint64_t y,uint64_t style,uint64_t color,uint64_t transparency,uint64_t speed,uint64_t text,uint64_t font)
{return ps2FontMessageRequestEx(x,y,0,style&255,color&255,transparency&255,speed&255,text,font);}

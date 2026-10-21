#include "font_text.h"
#include "font_resource.h"
#include "script_construction.h"
#include "script_lifetime.h"
#include "material_lists.h"
#include "texture_upload.h"
#include "libc_stream.h"
#include "ps2_memory.h"
#include "ee_fpu.h"
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
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint32_t sb(uint32_t v){v&=255;return v&128?v|0xffffff00u:v;}
static uint32_t sar(uint32_t v,unsigned n){return (v>>n)|((v&0x80000000u)?(~0u<<(32-n)):0);}
/* 001c6b68: live native FNT fields,including handle acquisition and alias reads. */
void ps2FontBindContext(uint64_t style,uint64_t data,uint64_t handle)
{
 if(!data&&handle)data=sx(ps2MemoryHandleAcquirePointer((uint32_t)handle));
 uint32_t p=(uint32_t)data,c=0x56ba30+((uint32_t)style&255)*36,offset=word(p);
 put(c,(uint32_t)handle);put(c+4,p);
 uint32_t palette=*at(p+10),metrics=*at(p+0x16);offset+=palette<<6;
 if(metrics){uint32_t m=p+offset,size=word(m);put(c+0x10,m+4);put(c+8,size);offset+=size+4;m=p+offset;size=word(m);put(c+0x14,m+4);put(c+0xc,size);offset+=size+4;}
 else{put(c+0x10,0);put(c+0x14,0);put(c+8,0);put(c+0xc,0);}
 uint32_t live=word(c+4);put(c+0x18,p+offset);
 uint32_t count=half(live+0xe),names=word(live+0x18);offset+=count<<2;
 put(c+0x1c,p+offset);put(c+0x20,names?p+names:0);
}
/* 001c7088: original raw COP1 value boundaries,not host float expressions. */
void ps2FontLayoutGlyph(uint64_t text,uint64_t index,uint64_t first)
{
 (void)first;uint32_t t=(uint32_t)text,style=*at(t+0x15),c=0x56ba30+style*36;
 uint32_t scaled=style<2,factor=0x3f800000;
 *at(t+0x18)=(uint8_t)frGetDefaultFontWidth(style);
 *at(t+0x19)=(uint8_t)frGetDefaultFontHeight(*at(t+0x15));
 style=*at(t+0x15);uint32_t metric=*at(0x326060+style),metric_signed=sb(metric);put(t+0xc,metric_signed);
 if(style<2){scaled=1;factor=EE_FPU_DIV_S(EE_FPU_CVT_S_W(*at(t+0x18)),0x41a00000);}
 uint32_t flags=*at(t+0x17),code=half(t);
 if(scaled&&code<128)put(t+0xc,sar(metric_signed,1));
 code=half(t);
 if(code==32&&(*at(t+0x15)==0||*at(t+0x15)==1)){put(t+0xc,word(0x54f414)+sar(word(t+0xc),1));return;}
 if(index==0x2c1)put(t+0xc,word(t+0xc)-7);
 if(!(flags&1))return;
 if(!*at(word(c+4)+0x16))return;
 uint32_t doubled=(uint32_t)index<<1;
 if((int64_t)(int32_t)doubled>=(int64_t)(int32_t)word(c+8))return;
 uint32_t m=word(c+0x10)+doubled,right=sb(*at(m+1));if(!right)return;
 uint32_t left=sb(*at(m)),advance=EE_FPU_CVT_S_W(right-left),position=EE_FPU_CVT_S_W(left);
 position=EE_FPU_MUL_S(position,0x41800000);advance=EE_FPU_MUL_S(advance,factor);position=EE_FPU_MUL_S(position,factor);
 uint32_t width=EE_FPU_CVT_W_S(advance),x=EE_FPU_CVT_W_S(position),glyph=sar(doubled,1)+32;
 if(glyph==33||glyph==49){x-=32;width+=4;}put(t+0xc,width);put(t+4,0-x);
}
/* 001c7408: native slot ownership and the real DMA upload builder. The otherwise
 * unassigned record+4 word is an explicit original ambient stack operand. */
uint64_t ps2FontCreateTextureGlyph(uint64_t width,uint64_t height,uint64_t pixels,uint64_t owned)
{
 uint32_t node=(uint32_t)ps2FontTakeTextureSlot(),slot=word(node+0x14),x=sar(word(node+4),4),y=sar(word(node+8),4);
 ph(slot+4,1);put(slot+8,node);uint8_t record[24];uint32_t address;
#if UINTPTR_MAX > UINT32_MAX
 address=nocturneLibcStreamLocalAddress(record,sizeof(record));
 put(address,(uint32_t)pixels);put(address+4,nocturneTextureImageScratchWord());
#else
 address=(uint32_t)(uintptr_t)record;put(address,(uint32_t)pixels);
#endif
 *at(address+8)=sb((uint32_t)owned)?2:0;*at(address+9)=20;
 ph(address+10,half(0x56bb90));put(address+12,word(0x56bba0)<<6);
 ph(address+16,x);ph(address+18,y);ph(address+20,(uint32_t)width);ph(address+22,(uint32_t)height);
 (void)ps2TextureQueueUpload(address);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 return sx(slot);
}
/* 001c7568: cache reads,reference increments and publication stay live. */
uint64_t ps2FontAcquireCachedGlyph(uint64_t text,uint64_t index)
{
 uint32_t t=(uint32_t)text,style=*at(t+0x15),c=0x56ba30+style*36,offset=(uint32_t)index<<2;
 uint32_t slot=word(word(c+0x18)+offset);if(slot){ph(slot+4,half(slot+4)+1);return sx(slot);}
 uint64_t pixels=ps2FontAllocateDecodedGlyph(style,index);
 uint64_t width=frGetFontWidth(*at(t+0x15));uint64_t height=frGetFontHeight(*at(t+0x15));
 uint64_t result=ps2FontCreateTextureGlyph(width,height,pixels,1);slot=(uint32_t)result;
 uint32_t array=word(c+0x18),count=word(0x56bb74);ph(slot,(uint32_t)index);put(array+offset,slot);put(0x56bb74,count+1);return result;
}
/* 001c76e0: native byte/Shift-JIS-like glyph indexing,including caret remap. */
uint64_t ps2FontCreateTextGlyph(uint64_t code,uint64_t style,uint64_t color,uint64_t transparency,uint64_t first)
{
 uint32_t glyph=(uint32_t)code&65535,s=(uint32_t)style&255;
 uint64_t text=ps2FontTakeGlyphSlot(sx(word(0x56bb80)));uint32_t t=(uint32_t)text,count=word(0x56bb78);put(0x56bb78,count+1);
 frInitTextHandle(text,glyph,s,(uint32_t)color&255,0xa09dc300,(uint32_t)transparency&255);
 uint32_t index=0;glyph=half(t);
 if(glyph>=32){if(glyph<128){if(glyph==94)ph(t,38);index=half(t)-32;}else{uint32_t value=half(t)+0xffff7f80u;index=((value&0xff00)>>1)+(value&127);}}
 put(t+0x1c,(uint32_t)ps2FontAcquireCachedGlyph(text,index));ps2FontLayoutGlyph(text,index,first);
 if(*at(t+0x17)&16)put(t+8,(uint32_t)ps2FontGetGlyphStorageSize());else put(t+8,0);
 return text;
}
/* 001c7288: append a zero-code control glyph to a new or supplied request. */
uint64_t ps2FontCreateControlGlyph(uint64_t data,uint64_t font)
{
 if(!font){font=ps2FontTakeGlyphSlot(sx(word(0x56bb84)));put(0x56bb7c,word(0x56bb7c)+1);frInitFontHandle(font);}
 uint64_t text=ps2FontTakeGlyphSlot(sx(word(0x56bb80)));uint32_t f=(uint32_t)font,t=(uint32_t)text,previous=word(f+0x20);
 put(0x56bb78,word(0x56bb78)+1);frInitTextHandle(text,0,0,0,0xa09dc300,0);
 if(previous)put(previous+0x28,t);else put(f+0x1c,t);
 put(t+0x20,(uint32_t)data);put(t+0xc,sb(*at(0x326060)));*at(t+0x18)=(uint8_t)frGetDefaultFontWidth(0);*at(t+0x19)=(uint8_t)frGetDefaultFontHeight(0);
 put(t+0x24,previous);put(f+0x20,t);uint32_t count=word(f+0x18),total=word(f+0xc);put(f+0x18,count+1);put(f+0xc,total+word(t+0xc));ph(f+0x10,*at(t+0x18));ph(f+0x12,*at(t+0x19));return font;
}
/* 001c7890: actual strlen,free-list allocation and native mixed-byte traversal. */
uint64_t ps2FontAppendString(uint64_t string,uint64_t style,uint64_t color,uint64_t transparency,uint64_t font,uint64_t first)
{
 uint32_t s=sb((uint32_t)style),col=sb((uint32_t)color),tp=sb((uint32_t)transparency);
 if(!(s&0x80000000u))*at(0x54f424)=(uint8_t)s;
 uint32_t selected=*at(0x54f424);if(!word(0x56ba30+selected*36+0x1c))return 0;
 uint32_t length=string?ps2Strlen((const char *)at((uint32_t)string)):0;
 if(!font){font=ps2FontTakeGlyphSlot(sx(word(0x56bb84)));put(0x56bb7c,word(0x56bb7c)+1);frInitFontHandle(font);}
 uint32_t f=(uint32_t)font,previous=word(f+0x20),pos=0,last=0;
 while(pos<length){uint32_t code=*at((uint32_t)string+pos);if(code>=128){pos++;code=(code<<8)|*at((uint32_t)string+pos);}
  uint64_t scale=(uint32_t)first!=0&&pos==0;pos++;
  last=(uint32_t)ps2FontCreateTextGlyph(code,*at(0x54f424),col&255,tp&255,scale);
  if(previous)put(previous+0x28,last);else put(f+0x1c,last);
  uint32_t width=word(last+0xc),total=word(f+0xc),count=word(f+0x18);put(last+0x24,previous);put(f+0xc,total+width);put(f+0x18,count+1);previous=last;ps2FontRecordLastCode(code);
 }
 if(last){put(f+0x20,last);ph(f+0x10,*at(last+0x18));ph(f+0x12,*at(last+0x19));}return font;
}
/* 001c8108: wrapper's actual mode is one. */
uint64_t ps2FontCombineRequest(uint64_t first,uint64_t second){return frCombineFontRequestEx(first,second,1);}
/* 001c7828: only the newly built request is combined;failure preserves input. */
uint64_t ps2FontAppendStringCombined(uint64_t string,uint64_t style,uint64_t color,uint64_t transparency,uint64_t font)
{uint64_t created=ps2FontAppendString(string,sx(sb((uint32_t)style)),sx(sb((uint32_t)color)),sx(sb((uint32_t)transparency)),0,0);return created?ps2FontCombineRequest(font,created):font;}

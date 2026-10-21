#include "font_resource.h"
#include "script_construction.h"
#include "material_fiveword_pool.h"
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
static void putHalf(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 001ca9c0 is a real identity helper,not a supplied decoder return. */
uint64_t ps2FontResourceIdentity(uint64_t resource){return resource;}
/* 001ca9c8 caches all header words before stores,including overlapping outputs. */
void ps2FontResolveCompressedSections(uint64_t resource,uint64_t sections)
{uint32_t p=(uint32_t)resource,s=(uint32_t)sections,a=word(p),b=word(p+4),c=word(p+0x18);put(s,p+a);put(s+4,p+a+b);put(s+8,p+a+b+c);}
/* 001caa18: native six-byte tree nodes and little-endian packed halfword bits.
 * The original consumes at least one bit even for a zero bit count; do not
 * add a zero-length guard or a guessed terminator. */
uint64_t ps2FontDecodeGlyph(uint64_t output,uint64_t index,uint64_t resource,uint64_t sections)
{
 uint32_t s=(uint32_t)sections,p=word(s+4)+((uint32_t)index<<2),tree=word(s);
 uint32_t start=word(p),end=word(p+4),count=0;
 (void)ps2FontResourceIdentity(resource);
 uint32_t bits=word(s+8)+((start>>4)<<1),remaining=end-start;
 uint32_t shift=start&15,packed=(half(bits)|0x10000u)>>shift,node=tree+2;
 do{
  uint32_t child=half(node+((packed&1)<<1));node=tree+child*6+2;
  uint32_t internal=half(node);packed>>=1;
  if(!internal){uint8_t value=*at(node+2);node=tree+2;*at((uint32_t)output+count)=value;count++;}
  remaining--;
  if(packed==1){bits+=2;packed=half(bits)|0x10000u;}
 }while(remaining);
 put(0x551ea0,count);return sx(count);
}
/* 001c74e8: real 0x120-byte pool allocation,private section words,full decoder. */
uint64_t ps2FontAllocateDecodedGlyph(uint64_t style,uint64_t index)
{
 uint32_t context=0x56ba30+((uint32_t)style&255)*36;
 uint32_t output=ps2PoolAllocate(0x120);uint8_t scratch[12];uint32_t sections;
#if UINTPTR_MAX > UINT32_MAX
 sections=nocturneLibcStreamLocalAddress(scratch,sizeof(scratch));
#else
 sections=(uint32_t)(uintptr_t)scratch;
#endif
 ps2FontResolveCompressedSections(sx(word(context+0x1c)),sections);
 (void)ps2FontDecodeGlyph(sx(output),index,sx(word(context+0x1c)),sections);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 return sx(output);
}
/* 001cabd8: sentinel word is loaded even when the returned allocation is null. */
uint64_t ps2FontTakeGlyphSlot(uint64_t list)
{uint32_t p=(uint32_t)list,node=word(p+4);if(!word(node))return 0;uint32_t next=word(node+4);put(p+4,next);put(node+4,0);return sx(node+8);}
/* 001c6018: linked texture slot removal uses live reloads after list stores. */
uint64_t ps2FontTakeTextureSlot(void)
{uint32_t list=0x56b668,tail=word(list+0x1c),node=word(tail+0x1c);if(!word(node))return 0;uint32_t next=word(node+0x1c),previous=word(node+0x18),count=word(list+0x18);put(previous+0x1c,next);put(list+0x18,count-1);next=word(node+0x1c);previous=word(node+0x18);put(next+0x18,previous);return sx(node);}
static uint64_t find(uint32_t table,uint32_t size,uint64_t code)
{uint32_t key=(uint32_t)code&65535;for(uint32_t i=0;i<size;i++)if(half(table+i*2)==key)return i;return UINT64_MAX;}
/* 001c6098,001c60e0: fixed original codebooks,first match,16-bit code masking. */
uint64_t ps2FontFindCode416(uint64_t code){return find(0x325b10,416,code);}
uint64_t ps2FontFindCode264(uint64_t code){return find(0x325e50,264,code);}
/* 001c6128: exclude low codes,85EC and the wrapped range003A..0040. */
void ps2FontRecordLastCode(uint64_t code)
{uint32_t v=(uint32_t)code&65535;if(v!=0x85ec&&v>=0x2f&&((v+0xffc6)&65535)>=7)putHalf(0x54ea00,v);}
/* 001c83b0,001c83f0,001c8418,001c8458: default styles use signed global LW. */
uint64_t frGetFontWidth(uint64_t style){return half(word(0x56ba34+((uint32_t)style&255)*36)+0x10);}
uint64_t frGetFontHeight(uint64_t style){return half(word(0x56ba34+((uint32_t)style&255)*36)+0x12);}
uint64_t frGetDefaultFontWidth(uint64_t style){return ((uint32_t)style&255)<2?sx(word(0x54f410)):frGetFontWidth(style);}
uint64_t frGetDefaultFontHeight(uint64_t style){return ((uint32_t)style&255)<2?sx(word(0x54f410)):frGetFontHeight(style);}
/* 001c7080 */
uint64_t ps2FontGetGlyphStorageSize(void){return 24;}
/* 001c7660: retain native store order and live global mode byte load. */
void frInitTextHandle(uint64_t text,uint64_t code,uint64_t style,uint64_t color_index,uint64_t color,uint64_t transparency)
{uint32_t p=(uint32_t)text;*at(p+0x15)=(uint8_t)style;*at(p+0x14)=(uint8_t)color_index;*at(p+0x16)=(uint8_t)transparency;putHalf(p,(uint32_t)code);uint8_t mode=*at(0x54f41c);put(p+0x10,(uint32_t)color&0xffffff00u);*at(p+0x17)=mode;put(p+0x28,0);put(p+4,0);put(p+8,0);put(p+0xc,0);putHalf(p+2,0);put(p+0x1c,0);put(p+0x20,0);put(p+0x24,0);}
/* 001c76a8 */
void frInitFontHandle(uint64_t font)
{uint32_t p=(uint32_t)font;put(p+0x18,0);*at(p)=128;put(p+4,0);put(p+8,0);*at(p+1)=0;put(p+0xc,0);put(p+0x14,0);put(p+0x24,0);put(p+0x28,0);put(p+0x2c,p);put(p+0x1c,0);put(p+0x20,0);}
/* 001c8230: signed spacing byte contributes once for each text node. */
uint64_t ps2FontMeasureRequest(uint64_t font)
{uint32_t p=(uint32_t)font,node=word(p+0x1c),sum=0;if(node){uint32_t b=*at(p+1),spacing=b&128?b|0xffffff00u:b;do{uint32_t width=word(node+0xc);node=word(node+0x28);sum+=width;sum+=spacing;}while(node);}return sx(sum);}

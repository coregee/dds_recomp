#include "script_construction.h"
#include "script_process.h"
#include "message_construction.h"
#include "material_fiveword_pool.h"
#include "libc_printf.h"
#include <string.h>
static uint32_t word(uint32_t a)
{ uint32_t v;memcpy(&v,nocturneResolveScriptConstructionAddress(a),4);return v; }
static int32_t half(uint32_t a)
{ uint16_t v;memcpy(&v,nocturneResolveScriptConstructionAddress(a),2);return (int32_t)(v&32767)-(int32_t)(v&32768); }
static uint32_t byte(uint32_t a)
{ return *(uint8_t *)nocturneResolveScriptConstructionAddress(a); }
static void put(uint32_t a,uint32_t v)
{ memcpy(nocturneResolveScriptConstructionAddress(a),&v,4); }
static void putByte(uint32_t a,uint32_t v)
{ *(uint8_t *)nocturneResolveScriptConstructionAddress(a)=(uint8_t)v; }
static uint64_t sx(uint32_t v)
{ return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v; }
static int less(uint64_t a,uint64_t b)
{ return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000)); }
/* 001098e0: raw64 guards precede actual pool construction; +F0 stays untouched. */
uint64_t scrAddScript(uint64_t header,uint64_t types,uint64_t procedures,uint64_t labels,
    uint64_t code,uint64_t messages,uint64_t strings,uint64_t start)
{
 if(!header||!types||!procedures||!code||(start>>63)||!less(start,sx(word((uint32_t)types+8))))return 0;
 uint32_t w=ps2PoolAllocate(0xf4);if(!w)return 0;
 uint32_t proc=(uint32_t)procedures+((uint32_t)start<<5),h=(uint32_t)header,index=0,value;
 do{value=byte(proc+index);putByte(w+index,value);index++;}while(value);
 uint32_t cp=word(proc+0x18);put(w+0x1c,0);put(w+0x18,cp);
 for(unsigned k=0;k<28;k++){putByte(w+0x20+k,0);put(w+0x3c+k*4,0);}
 put(w+0xb0,(uint32_t)types);int32_t count=half(h+0x14);
 put(w+0xbc,(uint32_t)code);put(w+0xb8,(uint32_t)labels);put(w+0xc4,(uint32_t)strings);
 put(w+0xc8,(uint32_t)start);put(w+0xcc,0xffffffff);put(w+0xac,h);put(w+0xb4,(uint32_t)procedures);put(w+0xc0,(uint32_t)messages);
 put(w+0xd0,0);put(w+0xd4,0);put(w+0xd8,0);put(w+0xdc,0);put(w+0xe0,0);put(w+0xe4,0);put(w+0xe8,0);put(w+0xec,0);
 if(count>0){uint32_t p=ps2PoolAllocate(count*4);count=half(h+0x14);put(w+0xdc,p);for(int32_t k=0;k<count;k++)put(p+(uint32_t)k*4,0);}
 else put(w+0xdc,0);
 count=half(h+0x16);
 if(count>0){uint32_t p=ps2PoolAllocate(count*4);count=half(h+0x16);put(w+0xe0,p);for(int32_t k=0;k<count;k++)put(p+(uint32_t)k*4,0);}
 else put(w+0xe0,0);
 if(messages)put(w+0xcc,(uint32_t)itfMesMngInitialize(messages));
 scrLinkScriptHandleList(sx(w));
 (void)ps2LibcPrintf(0x52e270,sx(proc));ps2ScriptDiagnosticDisabled(0x52e288,sx(proc));
 return sx(w);
}
/* 00109b48: later descriptors win; an empty message descriptor preserves the earlier pointer. */
uint64_t scrAddScript2(uint64_t data,uint64_t start)
{
 uint32_t d=(uint32_t)data,types=d+0x20,proc=0,labels=0,code=0,messages=0,strings=0;
 if(word(d+8)!=0x30574c46)return 0;
 uint32_t count=word(d+0x10);
 for(uint32_t k=0;less(sx(k),sx(count));k++){
  uint32_t p=types+(k<<4),kind=word(p);if(kind>=5)return 0;
  if(kind==3){if(word(p+8))messages=d+word(p+0xc);}
  else{uint32_t value=d+word(p+0xc);switch(kind){case 0:proc=value;break;case 1:labels=value;break;case 2:code=value;break;default:strings=value;break;}}
 }
 return scrAddScript(data,sx(types),sx(proc),sx(labels),sx(code),sx(messages),sx(strings),start);
}
/* 00109e38 */
uint64_t ps2ScriptAddFirst(uint64_t header,uint64_t types,uint64_t procedures,uint64_t labels,
    uint64_t code,uint64_t messages,uint64_t strings)
{ return scrAddScript(header,types,procedures,labels,code,messages,strings,0); }
/* 00109d98: original unconditionally starts the returned work. */
uint64_t scrStartScript2(uint64_t priority,uint64_t data,uint64_t start)
{ return scrStartScriptProcess(priority,scrAddScript2(data,start)); }
/* 00109de8: ninth entry argument is LW at caller SP+0, sign-extended into T3. */
uint64_t scrStartScript1a(uint64_t priority,uint64_t header,uint64_t types,uint64_t procedures,
    uint64_t labels,uint64_t code,uint64_t messages,uint64_t strings,uint32_t start)
{ return scrStartScriptProcess(priority,scrAddScript(header,types,procedures,labels,code,messages,strings,sx(start))); }
/* 001097e8: only private argument/FPR spills; no output call or defined return. */
void ps2ScriptDiagnosticDisabled(uint64_t format,...)
{ (void)format; }

#include "script_lifetime.h"
#include "script_construction.h"
#include "script_process.h"
#include "message_construction.h"
#include "memory_handle_allocation.h"
#include "material_construction_release.h"
#include "process_shutdown.h"
#include "process_lists.h"
#include "libc_printf.h"
#include <string.h>
static uint32_t word(uint32_t a)
{ uint32_t v;memcpy(&v,nocturneResolveScriptLifetimeAddress(a),4);return v; }
static uint32_t half(uint32_t a)
{ uint16_t v;memcpy(&v,nocturneResolveScriptLifetimeAddress(a),2);return v; }
static void put(uint32_t a,uint32_t v)
{ memcpy(nocturneResolveScriptLifetimeAddress(a),&v,4); }
static void putHalf(uint32_t a,uint32_t v)
{ uint16_t h=(uint16_t)v;memcpy(nocturneResolveScriptLifetimeAddress(a),&h,2); }
static uint64_t sx(uint32_t v)
{ return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v; }
/* 00100418: descriptive alias; consumer masks the original signed LW to eight bits. */
uint64_t ps2KernelGetFontContextIndex(void)
{ return sx(word(0x551b80)); }
/* 001c8120: splice reads stay live; the native Mode equality uses all 64 bits. */
uint64_t frCombineFontRequestEx(uint64_t first,uint64_t second,uint64_t mode)
{
 if(!first)return second;if(!second)return first;
 uint32_t a=(uint32_t)first,b=(uint32_t)second;
 put(a+0x28,word(b+0x2c));put(word(b+0x2c)+0x24,a);put(b+0x2c,word(a+0x2c));
 if(mode==1){
  uint32_t tag=word(b+0x1c);
  if(tag&&half(tag)==13){
   uint32_t x=word(a+4),height=half(a+0x12);put(b+4,x);
   int32_t h=(int32_t)(height&32767)-(int32_t)(height&32768);put(b+8,word(a+8)+(uint32_t)h);
  }else{uint32_t width=word(a+0xc),x=word(a+4);put(b+4,x+(width<<4));put(b+8,word(a+8));}
 }
 return second;
}
/* 001c6ff8: recycling into the context list does not free the request allocation. */
uint64_t frDestroyFontRequestAfter(uint64_t request)
{
 uint32_t slot=0x56bbc4+((uint32_t)ps2KernelGetFontContextIndex()&255)*4;
 put(slot,(uint32_t)frCombineFontRequestEx(sx(word(slot)),request,0));return 0;
}
/* 001cc150: reload primary handle after releasing the optional owned allocation. */
void itfPnlRelease(uint64_t panel)
{
 if(!panel)return;uint32_t p=(uint32_t)panel;
 if(word(p+8))ps2MemoryHandleFree(word(p+4));ps2MemoryHandleFree(word(p));
}
/* 001cdd78: only this request helper guards a signed64 negative ID. */
void itfMesMngRequestMessageRelease(uint64_t id,uint64_t speaker)
{
 if(id>>63)return;uint32_t p=word(0x56be8c+(uint32_t)id*20),m=p+0x24,s=p+0x14;
 uint32_t request=word(m+0xc);if(request){(void)frDestroyFontRequestAfter(sx(request));put(m+0xc,0);}
 itfMesInitializeMessage(sx(m),0);put(p,word(p)&0xfffdfff8);
 if(speaker){request=word(s+8);if(request){(void)frDestroyFontRequestAfter(sx(request));put(s+8,0);}itfMesInitializeSpeaker(sx(s),0);}
}
/* 001cdf80: unlike message release, selection has no negative-ID guard. */
void itfMesMngRequestSelectRelease(uint64_t id)
{
 uint32_t p=word(0x56be8c+(uint32_t)id*20),s=p+0x40,request=word(s+8);
 if(request){(void)frDestroyFontRequestAfter(sx(request));put(s+8,0);}
 put(s+0xc,0);uint32_t phase=word(p);putHalf(s+0x10,0);putHalf(s+0x16,0);putHalf(s+0x12,0xffff);put(p,phase&0xfffbffc7);
}
/* 001cfd88: the second panel and phase are read after the first release. */
void itfMesReleaseAllWindow(uint64_t instance)
{
 uint32_t p=(uint32_t)instance,w=p+0x9c,handle=word(w);
 if(handle){itfPnlRelease(sx(handle));put(w,0);}handle=word(w+4);
 if(handle){itfPnlRelease(sx(handle));put(w+4,0);}put(p,word(p)&0xfffff0ff);
}
/* 001cfdf8: ascending pointer slots; stale parallel handle words are preserved. */
void itfMesReleaseAllVariable(uint64_t variable)
{
 uint32_t p=(uint32_t)variable;
 for(unsigned i=0;i<32;i++,p+=4)if(word(p)){ps2MemoryHandleFree(word(p+0x80));put(p,0);}
}
/* 001cf058: release owned resources, return slot to free tail, decrement live count. */
void ps2MessageManagerReleaseInner(uint64_t id)
{
 uint32_t slot=0x56be80+(uint32_t)id*20,p=word(slot+0xc);if(!p)return;
 itfMesMngRequestMessageRelease(id,1);itfMesMngRequestSelectRelease(id);
 itfMesReleaseAllWindow(sx(p));itfMesReleaseAllVariable(sx(p+0xc4));put(p,0);
 ps2MemoryHandleFree(word(slot+0x10));put(slot+0xc,0);itfMiscLinkGive(sx(slot),0x56be70);put(0x56be60,word(0x56be60)-1);
}
/* 001cdb38: no upper-bound check in the original wrapper. */
void itfMesMngRelease(uint64_t id)
{ if(!(id>>63)&&word(0x56be8c+(uint32_t)id*20))ps2MessageManagerReleaseInner(id); }
/* 00109e50: release work ownership; process removal belongs to the caller. */
void scrReleaseScript(uint64_t work)
{
 uint32_t w=(uint32_t)work;
 (void)ps2LibcPrintf(0x52e2b8,sx(word(w+0xb4)+(word(w+0xc8)<<5)));
 ps2ScriptDiagnosticDisabled(0x52e2d0,sx(word(w+0xb4)+(word(w+0xc8)<<5)));
 uint32_t p=word(w+0xdc);if(p)ps2PoolRelease(p);p=word(w+0xe0);if(p)ps2PoolRelease(p);
 p=word(w+0xcc);if(!(p&0x80000000u))itfMesMngRelease(sx(p));p=word(w+0xd8);if(p)ps2MemoryHandleFree(p);
 scrUnlinkScriptHandleList(work);ps2PoolRelease(w);
}
/* 00109f08: cache next before callback-driven destruction; V0 is final printf result. */
uint64_t scrAllReleaseScript(void)
{
 (void)ps2LibcPrintf(0x52e2e0,sx(word(0x54e994)));uint32_t w=word(0x54e998);
 while(w){
  (void)ps2LibcPrintf(0x52e2f0,sx(w));uint32_t process=word(w+0xe4),next=word(w+0xec);
  if(process){(void)ps2LibcPrintf(0x52e310);(void)dds3KillProcess(sx(word(w+0xe4)),0);}
  else{(void)ps2LibcPrintf(0x52e328);scrReleaseScript(sx(w));}w=next;
 }
 return ps2LibcPrintf(0x52e340,sx(word(0x54e994)));
}
/* 0010a210: repeated shutdown sees null work after the original process-data store. */
void scrScriptShutdown(uint64_t process)
{ uint64_t w=dds3GetProcessData(process);if(w)scrReleaseScript(w);dds3SetProcessData(process,0); }

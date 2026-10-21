#include "diagnostic_transport.h"
#include "diagnostic_rpc.h"
#include "diagnostic_support.h"
#include "script_construction.h"
#include "libc_stream.h"
#include "ps2_memory.h"
#include "sdk_debug.h"
#include <stdarg.h>
static void *at(uint32_t address){return nocturneResolveScriptConstructionAddress(address);}
/* 002bd4a8: copy exactly strlen bytes into a private 64-byte aligned buffer,
 * then submit the original command2001. This body has no output-length guard. */
void ps2DiagnosticTextSend(uint64_t text)
{
 uint8_t frame[0x170];uint32_t guest;
#if UINTPTR_MAX > UINT32_MAX
 guest=nocturneDiagnosticFrameStart(frame,sizeof(frame));
#else
 guest=(uint32_t)(uintptr_t)frame;
#endif
 if(*(uint8_t *)at(0x551900)){
  uint32_t length=ps2Strlen(at((uint32_t)text)),buffer=(guest+0x4f)&~UINT32_C(63);
  if(length){
   (void)ps2Memcpy(at(buffer),at((uint32_t)text),length);
   (void)ps2DiagnosticRpcCall(0x58f310,2001,0,buffer,length,0,0,0,0);
  }
 }else ps2SdkPrintf(0x551908,text,0,0,0,0,0,0);
#if UINTPTR_MAX > UINT32_MAX
 nocturneDiagnosticFrameEnd();
#endif
}
/* 002bd550: seven saved GP arguments, followed by the caller-stack tail.
 * FPR spills are private saves; the actual formatter reads the GP cursor. */
uint64_t ps2DiagnosticPrintf(uint64_t format,...)
{
 uint8_t frame[0x170];uint32_t guest,cursor;
 va_list parameters;va_start(parameters,format);
#if UINTPTR_MAX > UINT32_MAX
 guest=nocturneDiagnosticFrameStart(frame,sizeof(frame));
 cursor=nocturneLibcStreamLocalAddress(parameters,0x10000);
#else
 guest=(uint32_t)(uintptr_t)frame;cursor=(uint32_t)(uintptr_t)parameters;
#endif
 uint64_t result=ps2LibcVsprintf(guest,format,cursor);
 ps2DiagnosticTextSend(guest);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();nocturneDiagnosticFrameEnd();
#endif
 va_end(parameters);return result;
}

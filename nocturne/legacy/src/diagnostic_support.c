/* Original diagnostic RPC pool and vsprintf prerequisites. */
#include "diagnostic_support.h"
#include "script_construction.h"
#include "material_fiveword_pool.h"
#include "libc_formatter.h"
#include "libc_stream.h"
#include <string.h>
static void *at(uint32_t address){return nocturneResolveScriptConstructionAddress(address);}
static uint32_t word(uint32_t address){uint32_t v;memcpy(&v,at(address),4);return v;}
static void put(uint32_t address,uint32_t v){memcpy(at(address),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 002ccf68: this independent pool uses the same serial-1 quirk as SIF RPC.
 * EI is unconditional; an initially disabled interrupt state is not restored. */
uint64_t ps2DiagnosticRpcPacketTake(uint64_t queue_raw)
{
 uint32_t queue=(uint32_t)queue_raw;
 (void)ps2KernelDisableInterrupts();
 uint32_t count=word(queue+8),packet=word(queue+4);
 if(count&&!(count&0x80000000u)){
  for(uint32_t index=0;index<count;index++,packet+=64){
   if(!(word(packet+16)&1)){
    put(packet+16,(index<<16)|5);
    uint32_t serial=word(queue)+1;put(queue,serial);
    if(serial==1){put(queue,serial+1);serial=1;}
    put(packet+20,packet);put(packet+24,serial);
    (void)ps2KernelEnableInterrupts();return sx(packet);
   }
  }
 }
 (void)ps2KernelEnableInterrupts();return 0;
}
/* 002cd010: serial cleared; only busy bit 0 is removed. */
void ps2DiagnosticRpcPacketRelease(uint64_t packet_raw)
{
 uint32_t packet=(uint32_t)packet_raw,value=word(packet+16);
 put(packet+24,0);put(packet+16,value&~UINT32_C(1));
}
/* 002d7f88: the actual stream formatter consumes a caller-supplied EE argv.
 * Only private FILE transport is relocated for the host build. */
uint64_t ps2LibcVsprintf(uint64_t output,uint64_t format,uint64_t arguments)
{
 uint8_t stream[96]={0};uint32_t guest;
#if UINTPTR_MAX > UINT32_MAX
 guest=nocturneLibcStreamLocalAddress(stream,sizeof(stream));
#else
 guest=(uint32_t)(uintptr_t)stream;
#endif
 uint32_t p=(uint32_t)output,value=0x7fffffff;uint16_t flags=0x208;
 memcpy(stream,&p,4);memcpy(stream+8,&value,4);memcpy(stream+12,&flags,2);
 memcpy(stream+16,&p,4);memcpy(stream+20,&value,4);
 value=word(0x52be28);memcpy(stream+84,&value,4);
 uint64_t result=ps2LibcVfprintfStream(sx(guest),format,arguments);
 memcpy(&p,stream,4);*(uint8_t *)at(p)=0;
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 return result;
}

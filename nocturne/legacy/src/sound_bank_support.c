#include "sound_bank_support.h"
#include "script_construction.h"
#include "material_fiveword_pool.h"
#include "libc_formatter.h"
#include "libc_stream.h"
#include "ps2_sdk_helpers.h"
#include <stdarg.h>
#include <string.h>
static void *at(uint32_t a){return nocturneResolveScriptConstructionAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 002dc830: two cache ways per index, inclusive full-width unsigned bounds. */
uint64_t ps2DataCacheScanRange(uint64_t first,uint64_t last)
{

 for(uint32_t index=0;index<4096;index+=64){
  for(uint32_t way=0;way<2;way++){
   nocturneSoundCacheSync();uint32_t tag=nocturneSoundCacheOperation(16,index+way);nocturneSoundCacheSync();
   uint64_t address=sx((tag&0xfffff000)+index);uint64_t below=address<first;
   if(!below&&last>=address){nocturneSoundCacheSync();(void)nocturneSoundCacheOperation(22,index+way);nocturneSoundCacheSync();}
  }
  nocturneSoundCacheSync();
 }
 return 0; /* Final SLTI at 002dc8c0, after index reaches 0x1000. */
}
/* 002dc8d8: align both arguments without discarding their high lanes. */
uint64_t ps2DataCacheInvalidateRange(uint64_t first,uint64_t last)
{
 uint32_t enabled=EE_SYSTEM_READ_STATUS()&0x10000;if(enabled)(void)ps2KernelDisableInterrupts();
 uint64_t result=ps2DataCacheScanRange(first&UINT64_C(0xffffffffffffffc0),last&UINT64_C(0xffffffffffffffc0));
 return enabled?ps2KernelEnableInterrupts():result;
}
/* 002c1c20: signed bank ID and seven live IOP-bank records. */
uint64_t ps2SoundBankStatus(uint64_t sound)
{
 uint32_t v=(uint32_t)sound;int32_t bank=(int32_t)v>>16;
 (void)ps2DataCacheInvalidateRange(0x593880,0x593e20);
 for(uint32_t i=0;i<7;i++)if((int32_t)word(0x593a10+i*8)==bank)return 1;
 return (int32_t)word(0x5519c0)==bank?2:0;
}
/* 002262e8: copy the original eight bytes before the actual strcat. */
uint64_t ps2SoundBuildPath(uint64_t output,uint64_t name)
{
 uint64_t prefix;memcpy(&prefix,at(0x54fd18),8);memcpy(at((uint32_t)output),&prefix,8);
 (void)ps2Strcat(at((uint32_t)output),at((uint32_t)name));return output;
}
/* 002d5690: real variadic cursor, six saved GP slots plus caller-stack tail. */
uint64_t ps2LibcSprintf(uint64_t output,uint64_t format,...)
{
 uint8_t stream[96]={0};uint32_t cursor,guest;
 va_list parameters;va_start(parameters,format);
#if UINTPTR_MAX > UINT32_MAX
 guest=nocturneLibcStreamLocalAddress(stream,sizeof(stream));cursor=nocturneLibcStreamLocalAddress(parameters,0x10000);
#else
 guest=(uint32_t)(uintptr_t)stream;cursor=(uint32_t)(uintptr_t)parameters;
#endif
 uint32_t p=(uint32_t)output,value=0x7fffffff;uint16_t flags=0x208;
 memcpy(stream,&p,4);memcpy(stream+8,&value,4);memcpy(stream+12,&flags,2);memcpy(stream+16,&p,4);memcpy(stream+20,&value,4);value=word(0x52be28);memcpy(stream+84,&value,4);
 uint64_t result=ps2LibcVfprintfStream(sx(guest),format,cursor);memcpy(&p,stream,4);*(uint8_t *)at(p)=0;
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();nocturneLibcStreamEndLocal();
#endif
 va_end(parameters);return result;
}

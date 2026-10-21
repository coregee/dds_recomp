/* Complete native SIF client/server response and file reply handlers. */
#include "file_completion.h"
#include "file_rpc.h"
#include "draw_interrupt.h"
#include "material_fiveword_pool.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveFileCompletionAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t r64(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void w64(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
void ps2SifRpcResponse(uint64_t packet_raw)
{
 uint32_t packet=(uint32_t)packet_raw,command=r(packet+32),client;
 if(command==0x8000000a){
  client=r(packet+28);uint32_t callback=r(client+28);
  if(callback)nocturneFileCompletionInvoke(callback,sx(r(client+32)));
  client=r(packet+28);
 }else if(command==0x80000009){
  uint32_t server=r(packet+36);client=r(packet+28);w(client+36,server);
  w(client+20,r(packet+40));w(client+24,r(packet+44));
 }else client=r(packet+28);
 uint32_t sem=r(client+8);if(s32(sem)>=0)(void)ps2KernelInterruptSignalSema(sx(sem));
 ps2SifRpcPacketRelease(sx(r(client)));w(client,0);
}
void ps2SifRpcServerRequest(uint64_t packet_raw)
{
 uint32_t packet=(uint32_t)packet_raw,server=r(packet+52),queue=r(server+64),tail=r(queue+12);
 if(tail){tail=r(queue+16);w(tail+60,server);}else w(queue+12,server);
 w(queue+16,server);uint32_t serial=r(packet+20),client=r(packet+28);w(server+32,serial);w(server+28,client);
 w(server+36,r(packet+32));w(server+12,r(packet+36));w(server+40,r(packet+40));w(server+44,r(packet+44));w(server+48,r(packet+48));w(server+52,r(packet+16));
 uint32_t thread=r(queue);if(s32(thread)>=0&&!r(queue+4))(void)ps2DrawWakeThread(sx(thread));
}
static void copy32(uint32_t destination,uint32_t source)
{
 uint64_t a=r64(source),b=r64(source+8),c=r64(source+16),d=r64(source+24);
 w64(destination,a);w64(destination+8,b);w64(destination+16,c);w64(destination+24,d);
}
void ps2FileRpcComplete(void)
{
 /* Original LWL/LWR loads preserve these four header words across memcpy. */
 uint32_t sem=r(0x2059e140),command=r(0x2059e144),destination=r(0x2059e148),bytes=r(0x2059e14c);
 if(s32(sem)>=0)(void)ps2Memcpy(at(destination),at(0x2059e150),bytes);
 if(command==2){
  uint32_t record=0x2059e154,count=r(record);
  if(s32(count)>0){
   uint32_t out=r(record+8),index=0;
   do{uint8_t value=*at(record+16+index);*at(out+index)=value;index++;count=r(record);}while(s32(index)<s32(count));
  }
  count=r(record+4);
  if(s32(count)>0){
   uint32_t out=r(record+12),index=0;
   do{uint8_t value=*at(record+80+index);*at(out+index)=value;index++;count=r(record+4);}while(s32(index)<s32(count));
  }
 }else if(command==11){
  uint32_t out=r(0x2059e154),source=0x2059e158;
  for(uint32_t k=0;k<320;k+=32)copy32(out+k,source+k);
  w(out+320,r(source+320));
 }else if(command==12){
  uint32_t out=r(0x2059e154);copy32(out,0x2059e158);copy32(out+32,0x2059e178);
 }else if(command==23||command==25||command==26){
  uint32_t out=r(0x2059e154),count=r(0x2059e158);if(count>1024)count=1024;
  (void)ps2Memcpy(at(out),at(0x2059e15c),count);
 }
 if(s32(sem)<0){
  uint32_t id=0-sem;
  for(uint32_t k=0;k<32;k++)if(r(0x52c2c0+k*4)==id){w(0x52c2c0+k*4,UINT32_MAX);break;}
 }else (void)ps2KernelInterruptSignalSema(sx(sem));
}
void ps2FileRpcNotification(uint64_t packet,uint64_t callback_record)
{
 (void)packet;uint32_t record=(uint32_t)callback_record,callback=r(record);
 if(callback)nocturneFileCompletionInvoke(callback,sx(r(record+4)));
 nocturneDrawInterruptSync();EE_SYSTEM_EI();
}

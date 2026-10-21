/* Complete original RPC packet/command/call/bind and descriptor/lock bodies.
 * Raw EE addresses and full-width comparisons are retained. Service boundaries
 * expose DMA packets and cache operations; they do not replace RPC functions. */
#include "file_rpc.h"
#include "heap_queue.h"
#include "material_fiveword_pool.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveFileRpcAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
static int negative(uint64_t v){return (int)(v>>63);}
static int signedLess(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
static uint32_t createSema(uint32_t initial,uint32_t maximum,uint32_t option){
 uint32_t packet[6];packet[1]=maximum;packet[2]=initial;packet[5]=option;
 return ps2KernelCreateSema(packet);
}
void ps2SifSyncDataCache(uint64_t address,uint64_t bytes)
{
 if(negative(bytes)||!bytes)return;
 uint32_t base=(uint32_t)address&~UINT32_C(63),last=((uint32_t)address+(uint32_t)bytes-1)&~UINT32_C(63);
 uint32_t count=((last-base)>>6)+1,remainder=count&7,groups=count>>3;
 for(uint32_t k=0;k<remainder;k++){
  nocturneRpcSyncValue(0);nocturneRpcCacheValue(24,base);nocturneRpcSyncValue(0);base+=64;
 }
 for(uint32_t k=0;k<groups;k++){
  nocturneRpcSyncValue(0);
  for(uint32_t j=0;j<8;j++){nocturneRpcCacheValue(24,base+j*64);nocturneRpcSyncValue(0);}
  base+=512;
 }
}
uint64_t ps2SifRpcPacketTake(uint64_t queue_raw)
{
 uint32_t queue=(uint32_t)queue_raw;(void)ps2KernelDisableInterrupts();
 uint32_t count=r(queue+8),packet=r(queue+4);
 if(s32(count)>0)for(uint32_t index=0;index<count;index++,packet+=64){
  if(!(r(packet+16)&1)){
   w(packet+16,(index<<16)|5);uint32_t serial=r(queue)+1;w(queue,serial);
   if(serial==1){w(queue,serial+1);serial=1;}
   w(packet+20,packet);w(packet+24,serial);(void)ps2KernelEnableInterrupts();return sx(packet);
  }
 }
 (void)ps2KernelEnableInterrupts();return 0;
}
void ps2SifRpcPacketRelease(uint64_t packet_raw){uint32_t packet=(uint32_t)packet_raw,value=r(packet+16);w(packet+24,0);w(packet+16,value&~UINT32_C(1));}
uint64_t ps2KernelSifSetDma(const void *packets,uint64_t count){return nocturneRpcDmaValue(0x77,packets,count);}
uint64_t ps2KernelSifSetDmaInterrupt(const void *packets,uint64_t count){return nocturneRpcDmaValue(0xffffff89,packets,count);}
uint64_t ps2KernelDeleteSema(uint64_t id){return nocturneRpcDeleteSemaValue(id);}
uint64_t ps2SifSendCommand(uint64_t command,uint64_t mode,uint64_t packet_raw,uint64_t packet_bytes,uint64_t source,uint64_t destination,uint64_t bytes)
{
 if(sx((uint32_t)packet_bytes-16)>=97)return 0;
 uint32_t packet=(uint32_t)packet_raw,descriptors[8],count=0;
 uint32_t first=*at(packet);
 if(!negative(bytes)&&bytes){
  w(packet+4,(uint32_t)destination);w(packet,first|((uint32_t)bytes<<8));
  descriptors[0]=(uint32_t)source;descriptors[1]=(uint32_t)destination;descriptors[2]=(uint32_t)bytes;descriptors[3]=0;count=1;
  if(mode&4)ps2SifSyncDataCache(source,bytes);
 }else{w(packet+4,0);w(packet,first);}
 descriptors[count*4]=packet;descriptors[count*4+1]=r(0x59baa0);descriptors[count*4+2]=(uint32_t)packet_bytes;
 w(packet+8,(uint32_t)command);*at(packet)=(uint8_t)packet_bytes;descriptors[count*4+3]=0x44;
 ps2SifSyncDataCache(packet_raw,packet_bytes);count++;
 return mode&1?ps2KernelSifSetDmaInterrupt(descriptors,count):ps2KernelSifSetDma(descriptors,count);
}
uint64_t ps2SifSendCommandDefault(uint64_t command,uint64_t packet,uint64_t packet_bytes,uint64_t source,uint64_t destination,uint64_t bytes)
{return ps2SifSendCommand(command,0,packet,packet_bytes,source,destination,bytes);}
uint64_t ps2SifRpcCall(uint64_t client_raw,uint64_t command,uint64_t mode,uint64_t send,uint64_t send_bytes,uint64_t receive,uint64_t receive_bytes,uint64_t callback,uint32_t callback_parameter)
{
 uint64_t packet_raw=ps2SifRpcPacketTake(0x59d440);if(!packet_raw)return UINT64_MAX;
 uint32_t client=(uint32_t)client_raw,packet=(uint32_t)packet_raw,serial=r(packet+24);
 w(client+32,callback_parameter);w(client,packet);w(client+4,serial);w(client+28,(uint32_t)callback);
 w(packet+32,(uint32_t)command);w(packet+36,(uint32_t)send_bytes);w(packet+40,(uint32_t)receive);w(packet+44,(uint32_t)receive_bytes);w(packet+20,packet);
 uint32_t server=r(client+36);w(packet+28,client);w(packet+52,server);
 if(!(mode&2)){
  if(send==receive)ps2SifSyncDataCache(send,signedLess(send_bytes,receive_bytes)?receive_bytes:send_bytes);
  else{if(!negative(send_bytes)&&send_bytes)ps2SifSyncDataCache(send,send_bytes);if(!negative(receive_bytes)&&receive_bytes)ps2SifSyncDataCache(receive,receive_bytes);}
 }
 if(mode&1){
  w(packet+48,callback?1:0);w(client+8,UINT32_MAX);
  if(ps2SifSendCommandDefault(UINT64_C(0xffffffff8000000a),packet_raw,64,send,sx(r(client+20)),send_bytes))return 0;
 }else{
  uint32_t sem=createSema(0,1,nocturneRpcSemaUnwrittenOption());w(client+8,sem);
  if(s32(sem)<0){ps2SifRpcPacketRelease(packet_raw);return UINT64_C(0xfffffffffffffffd);}
  w(packet+48,1);
  if(ps2SifSendCommandDefault(UINT64_C(0xffffffff8000000a),packet_raw,64,send,sx(r(client+20)),send_bytes)){
   (void)ps2KernelWaitSema(r(client+8));(void)ps2KernelDeleteSema(sx(r(client+8)));return 0;
  }
  (void)ps2KernelDeleteSema(sx(r(client+8)));
 }
 ps2SifRpcPacketRelease(packet_raw);return UINT64_C(0xfffffffffffffffe);
}
uint64_t ps2SifRpcBind(uint64_t client_raw,uint64_t server,uint64_t mode)
{
 uint32_t client=(uint32_t)client_raw;w(client+16,0);w(client+36,0);
 uint64_t packet_raw=ps2SifRpcPacketTake(0x59d440);if(!packet_raw)return UINT64_MAX;
 uint32_t packet=(uint32_t)packet_raw;w(client,packet);w(client+4,r(packet+24));w(packet+32,(uint32_t)server);w(packet+20,packet);w(packet+28,client);
 if(mode&1){
  w(client+8,UINT32_MAX);
  if(ps2SifSendCommandDefault(UINT64_C(0xffffffff80000009),packet_raw,64,0,0,0))return 0;
  ps2SifRpcPacketRelease(packet_raw);return UINT64_C(0xfffffffffffffffe);
 }
 uint32_t sem=createSema(0,1,nocturneRpcSemaUnwrittenOption());w(client+8,sem);
 if(s32(sem)<0){ps2SifRpcPacketRelease(packet_raw);return UINT64_C(0xfffffffffffffffd);}
 if(!ps2SifSendCommandDefault(UINT64_C(0xffffffff80000009),packet_raw,64,0,0,0)){
  ps2SifRpcPacketRelease(packet_raw);(void)ps2KernelDeleteSema(sx(r(client+8)));return UINT64_C(0xfffffffffffffffe);
 }
 (void)ps2KernelWaitSema(r(client+8));(void)ps2KernelDeleteSema(sx(r(client+8)));return 0;
}
void ps2FileRpcDescriptorInitialize(void)
{
 if(sx(r(0x52c348))!=UINT64_MAX)return;
 w(0x52c348,createSema(1,1,0));w(0x52c34c,createSema(1,1,0));
}
uint64_t ps2FileRpcDescriptorTake(void)
{
 ps2FileRpcDescriptorInitialize();(void)ps2KernelWaitSema(r(0x52c348));
 for(uint32_t address=0x59e580;address<0x59e780;address+=16)if(!r(address+4)){
  uint32_t sem=r(0x52c348);w(address+4,0x10000000);(void)ps2KernelSignalSema(sem);return sx(address);
 }
 (void)ps2KernelSignalSema(r(0x52c348));return 0;
}
uint64_t ps2FileRpcDescriptorLookup(uint64_t id)
{
 ps2FileRpcDescriptorInitialize();(void)ps2KernelWaitSema(r(0x52c348));
 if(id>=32){(void)ps2KernelSignalSema(r(0x52c348));return 0;}
 uint32_t address=0x59e580+((uint32_t)id<<4);(void)ps2KernelSignalSema(r(0x52c348));return sx(address);
}
void ps2FileRpcLockInitialize(void){if(sx(r(0x52c344))==UINT64_MAX)w(0x52c344,createSema(1,1,0));}
uint64_t ps2FileRpcLock(uint64_t command){(void)command;ps2FileRpcLockInitialize();(void)ps2KernelWaitSema(r(0x52c344));return 0;}
uint64_t ps2FileRpcUnlock(void){return sx(ps2KernelSignalSema(r(0x52c344)));}
uint64_t ps2FileRpcVersionMismatch(void)
{
 if(ps2Memcmp(at(0x59e7a8),at(0x52c2a0),4)==0)return 0;
 if(ps2Memcmp(at(0x59e7a8),at(r(0x52c350)),4)==0)return 0;
 return ps2Memcmp(at(0x52c2a0),at(r(0x52c350)),4)!=0;
}

/* 002cd418: independent, synchronous diagnostic SIF RPC implementation. */
#include "diagnostic_rpc.h"
#include "diagnostic_support.h"
#include "file_rpc.h"
#include "heap_queue.h"
#include "sdk_debug.h"
#include "script_construction.h"
#include <string.h>
static uint32_t word(uint32_t address){uint32_t v;memcpy(&v,nocturneResolveScriptConstructionAddress(address),4);return v;}
static void put(uint32_t address,uint32_t v){memcpy(nocturneResolveScriptConstructionAddress(address),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int positive(uint64_t v){return v&&!(v>>63);}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
uint64_t ps2DiagnosticRpcCall(uint64_t client_raw,uint64_t command,uint64_t mode,
 uint64_t send,uint64_t send_bytes,uint64_t receive,uint64_t receive_bytes,
 uint64_t callback,uint32_t parameter)
{
 if(mode){ps2SdkPrintf(0x54add8,0,0,0,0,0,0,0);return UINT64_MAX;}
 uint32_t client=(uint32_t)client_raw;
 (void)ps2KernelWaitSema(word(client+40));
 if(send&63){ps2SdkPrintf(0x54ae00,0x54ae38,send,0,0,0,0,0);return UINT64_MAX;}
 if(receive&63){ps2SdkPrintf(0x54ae48,0x54ae38,receive,0,0,0,0,0);return UINT64_MAX;}
 uint64_t packet_raw=ps2DiagnosticRpcPacketTake(0x599700);
 if(!packet_raw)return UINT64_MAX;
 uint32_t packet=(uint32_t)packet_raw,serial=word(packet+24);
 put(client+32,parameter);put(client+4,serial);put(client,packet);
 put(client+28,(uint32_t)callback);put(packet+32,(uint32_t)command);
 put(packet+20,packet);put(packet+36,(uint32_t)send_bytes);
 put(packet+40,(uint32_t)receive);put(packet+44,(uint32_t)receive_bytes);
 put(packet+28,client);put(packet+52,word(client+36));
 if(send==receive)ps2SifSyncDataCache(send,less(send_bytes,receive_bytes)?receive_bytes:send_bytes);
 else{
  if(positive(send_bytes))ps2SifSyncDataCache(send,send_bytes);
  if(positive(receive_bytes))ps2SifSyncDataCache(receive,receive_bytes);
 }
 /* Retained original asynchronous arm. The entry guard makes it unreachable:
  * mode is zero here and all actual callees preserve the saved mode register. */
 if(mode&1){
  put(packet+48,callback?1:0);put(client+8,UINT32_MAX);
  if(ps2SifSendCommandDefault(UINT64_C(0xffffffff8000001a),packet_raw,64,send,sx(word(client+20)),send_bytes))return 0;
  ps2DiagnosticRpcPacketRelease(packet_raw);return UINT64_C(0xfffffffffffffffe);
 }
 uint32_t parameters[6];parameters[1]=1;parameters[2]=0;parameters[5]=0;
 uint32_t sem=ps2KernelCreateSema(parameters);put(client+8,sem);
 if(sem&0x80000000u){ps2DiagnosticRpcPacketRelease(packet_raw);return UINT64_C(0xfffffffffffffffd);}
 put(packet+48,1);
 if(!ps2SifSendCommandDefault(UINT64_C(0xffffffff8000001a),packet_raw,64,send,sx(word(client+20)),send_bytes)){
  ps2DiagnosticRpcPacketRelease(packet_raw);(void)ps2KernelDeleteSema(sx(sem));return UINT64_C(0xfffffffffffffffe);
 }
 (void)ps2KernelWaitSema(sem);(void)ps2KernelDeleteSema(sx(sem));return 0;
}

/* Complete movie setup and decoder ownership/list bodies from original EE code. */
#include "movie_initialize.h"
#include "movie_archive.h"
#include "movie_draw.h"
#include "libc_stream.h"
#include "ps2_memory.h"
#include "ps2_sdk_helpers.h"
#include "ps2_sdk_neighbors.h"
#include "material_fiveword_pool.h"
#include "material_construction_release.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "texture_construction.h"
#include "file_device.h"
#include "heap_queue.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveMovieArchiveAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
void ps2MovieDecoderClear(uint64_t decoder,uint64_t configuration){
 uint32_t d=(uint32_t)decoder,c=(uint32_t)configuration;
 ps2Memset(at(d),0,140);
 *at(d+20)=!*at(c)?0:!*at(c+1)?1:2;
 *at(d+21)=*at(c+2);*at(d+22)=*at(c+3);
}
void ps2MovieDecoderCreate(uint64_t decoder,uint64_t configuration,uint64_t callback,uint64_t payload){
 uint32_t d=(uint32_t)decoder;ps2MovieDecoderClear(decoder,configuration);
 w32(d+92,(uint32_t)callback);w32(d+96,(uint32_t)payload);*at(d+12)=1;
 uint64_t data=ps2TextureStagingAllocate(0x10100);w32(d+84,(uint32_t)data+256);
}
void ps2MovieDecoderListAppend(uint64_t decoder){
 uint32_t d=(uint32_t)decoder,slot=0x552148,node=r32(slot);
 while(node){slot=node+8;node=r32(slot);}
 w32(slot,d);w32(d+8,0);
}
void ps2MovieDecoderListRemove(uint64_t decoder){
 uint32_t slot=0x552148,node=r32(slot);
 while(node){if(sx(node)==decoder){w32(slot,r32(node+8));return;}slot=node+8;node=r32(slot);}
}
uint64_t ps2MovieDecoderQueueRemove(uint64_t decoder,uint64_t interrupts_disabled){
 uint32_t d=(uint32_t)decoder,restore=interrupts_disabled?0:ps2KernelDisableInterrupts();
 uint64_t result=*at(d+13);
 if(result){
  uint32_t previous=r32(d),next=r32(d+4);result=sx(next);
  if(previous)w32(previous+4,next);else w32(0x55215c,next);
  if(next)w32(next,previous);else w32(0x552160,previous);
  *at(d+13)=0;
 }
 if(!interrupts_disabled&&restore)return ps2KernelEnableInterrupts();
 return result;
}
void ps2MovieDecoderInitialize(uint64_t decoder,uint64_t configuration,uint64_t callback,uint64_t payload,uint64_t field){
 ps2MovieDecoderCreate(decoder,configuration,callback,payload);w32((uint32_t)decoder+52,(uint32_t)field);ps2MovieDecoderListAppend(decoder);
}
void ps2MovieStopDecoderCommand(void){(void)ps2MovieCommandSubmit(0x100,0,0,0);}
void ps2MovieControlInitialize(uint64_t control,uint64_t parameters,uint64_t filename){
 uint32_t c=(uint32_t)control,p=(uint32_t)parameters;ps2Memset(at(c),0,176);*at(c)=1;
 const char *last=ps2Strrchr((const char *)at((uint32_t)filename),46);
 int ips=last&&ps2Strcasecmp(last,(const char *)at(0x551b50))==0;*at(c+3)=(uint8_t)ips;
 w32(c+24,0x7fffffff);w16(c+4,r16(p));w32(c+8,r32(p+4));w16(c+6,r16(p+2));w16(c+12,r16(p+8));w16(c+14,r16(p+10));
 uint8_t configuration[4]={*at(p+16),*at(p+17),0,*at(p+18)};
 uint32_t record,handle,data;uint64_t job;
 if(ips){
  if(r32(0x551b48)&0x80000000)w32(0x551b48,ps2CreateSemaphore(1,1,0));
  w32(0x55216c,UINT32_MAX);record=ps2PoolAllocateZeroed(120);w32(c+28,record);
  handle=ps2MemoryHandleAllocate(0x24000);w32(record+76,handle);data=ps2MemoryHandleAcquirePointer(handle);
  w32(record+84,data+0x4000);w32(record+116,record+32);w32(record+96,data+0x14000);w32(record+112,32);w32(record+80,data);
  *at(c+1)=0;job=ps2FileRequestRead(filename,0x2c5688,control);*at(c+32)=1;*at(c+34)=127;w32(c+16,(uint32_t)job);
 }else{
  record=ps2PoolAllocateZeroed(20);w32(c+28,record);handle=ps2MemoryHandleAllocate(0x20000);w32(record,handle);data=ps2MemoryHandleAcquirePointer(handle);
  w32(record+12,data);w32(record+4,data);w32(record+8,data);*at(c+1)=0;job=ps2FileRequestRead(filename,0x2c5460,control);w32(c+16,(uint32_t)job);
 }
#if UINTPTR_MAX > UINT32_MAX
 uint32_t temporary=nocturneLibcStreamLocalAddress(configuration,4);
#else
 uint32_t temporary=(uint32_t)(uintptr_t)configuration;
#endif
 ps2MovieDecoderInitialize(sx(c+36),temporary,ips?0x2c5bb8:0x2c5a18,control,sx(r32(p+12)));
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
}

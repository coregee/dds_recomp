/* Complete native command/RPC/file initialization; kernel/MMIO values external. */
#include "sif_initialization.h"
#include "file_rpc.h"
#include "heap_queue.h"
#include "display_control.h"
#include "draw_consumer_support.h"
#include "material_fiveword_pool.h"
#include <string.h>
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveSifInitializationAddress(address);
#else
 return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r(uint32_t address){uint32_t v;memcpy(&v,at(address),4);return v;}
static void w(uint32_t address,uint32_t v){memcpy(at(address),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t ps2KernelSifSetDChain(void){return nocturneSifInitializationKernel(0x78,0,0);}
uint64_t ps2KernelSifGetRegister(uint64_t id){return nocturneSifInitializationKernel(0x7a,1,&id);}
uint64_t ps2KernelSifSetRegister(uint64_t id,uint64_t value){uint64_t args[2]={id,value};return nocturneSifInitializationKernel(0x79,2,args);}
uint64_t ps2KernelAddDmacHandler(uint64_t channel,uint64_t handler,uint64_t next){uint64_t args[3]={channel,handler,next};return nocturneSifInitializationKernel(0x12,3,args);}
uint64_t ps2SifReadCommandRegister(uint64_t id){return sx(r(0x59bbc0+((uint32_t)id<<2)));}
void ps2SifAddCommandHandler(uint64_t command,uint64_t handler,uint64_t parameter){
 uint32_t base=r(command>>63?0x59baa4:0x59baac),slot=base+((uint32_t)command<<3);
 w(slot+4,(uint32_t)parameter);w(slot,(uint32_t)handler);
}
void ps2SifCommandInitialize(void){
 (void)ps2KernelDisableInterrupts();
 if(r(0x52c2b8)){(void)ps2KernelEnableInterrupts();return;}
 w(0x52c2b8,1);w(0x59ba98,0x2059b9c0);w(0x59ba9c,0x2059ba40);
 w(0x59bab4,0x59bbc0);w(0x59baa8,32);w(0x59baa0,0);w(0x59baa4,0x59bac0);w(0x59baac,0);w(0x59bab0,0);
 for(uint32_t k=0;k<32;k++){w(0x59bac0+k*8,0);w(0x59bac4+k*8,0);}
 for(uint32_t k=32;k>0;k--)w(0x59bbc0+(k-1)*4,0);
 w(0x59bac0,0x2ddde0);w(0x59bac8,0x2dddc0);w(0x59bacc,0x59ba98);w(0x59bac4,0x59ba98);
 (void)ps2KernelEnableInterrupts();(void)ps2KernelFlushCache(0);
 if(nocturneSifInitializationMmioRead(0x1000e010)&32)nocturneSifInitializationMmioWrite(0x1000e010,32);
 if(!(nocturneSifInitializationMmioRead(0x1000c000)&256))(void)ps2KernelSifSetDChain();
 w(0x59ba94,(uint32_t)ps2KernelAddDmacHandler(5,0x2de330,0));(void)ps2KernelEnableDmac(5);
 uint64_t value=ps2KernelSifGetRegister(UINT64_C(0xffffffff80000000));w(0x59baa0,(uint32_t)value);
 if(value){
  w(0x59ba90,0x59b9c0);
  (void)ps2SifSendCommandDefault(UINT64_C(0xffffffff80000000),0x59ba80,20,0,0,0);
 }else{
  while(!(ps2KernelSifGetRegister(4)&0x20000)){}
  value=ps2KernelSifGetRegister(2);w(0x59baa0,(uint32_t)value);
  (void)ps2KernelSifSetRegister(UINT64_C(0xffffffff80000000),value);
  (void)ps2KernelSifSetRegister(UINT64_C(0xffffffff80000001),0x59ba98);
  w(0x59ba90,0x59b9c0);w(0x59ba8c,0);
  (void)ps2SifSendCommandDefault(UINT64_C(0xffffffff80000002),0x59ba80,20,0,0,0);
 }
}
void ps2SifRpcInitialize(void){
 (void)ps2KernelDisableInterrupts();
 if(r(0x52c2bc)){(void)ps2KernelEnableInterrupts();return;}
 w(0x52c2bc,1);(void)ps2KernelEnableInterrupts();ps2SifCommandInitialize();(void)ps2KernelDisableInterrupts();
 w(0x59d460,32);w(0x59d440,1);w(0x59d454,0x2059c440);w(0x59d444,0x2059bc40);w(0x59d45c,0x2059cc40);
 w(0x59d448,32);w(0x59d44c,0);w(0x59d450,0);w(0x59d458,32);w(0x59d464,0);
 ps2SifAddCommandHandler(UINT64_C(0xffffffff80000008),0x2de808,0x59d440);
 ps2SifAddCommandHandler(UINT64_C(0xffffffff80000009),0x2deac8,0x59d440);
 ps2SifAddCommandHandler(UINT64_C(0xffffffff8000000a),0x2decb8,0x59d440);
 ps2SifAddCommandHandler(UINT64_C(0xffffffff8000000c),0x2de8c0,0x59d440);
 (void)ps2KernelEnableInterrupts();
 if(!ps2KernelSifGetRegister(UINT64_C(0xffffffff80000002))){
  w(0x59bc8c,1);(void)ps2SifSendCommandDefault(UINT64_C(0xffffffff80000002),0x59bc80,16,0,0,0);
  while(!ps2SifReadCommandRegister(0)){}
  (void)ps2KernelSifSetRegister(UINT64_C(0xffffffff80000002),1);
 }
}
uint64_t ps2FileRpcInitialize(void){
 ps2SifRpcInitialize();w(0x59e800,0);w(0x59e804,0);
 uint64_t enabled=ps2KernelDisableInterrupts();
 ps2SifAddCommandHandler(UINT64_C(0xffffffff80000011),0x2df5c0,0x59e7c0);
 ps2SifAddCommandHandler(UINT64_C(0xffffffff80000013),0x2dfaa8,0x59e800);
 if(enabled)(void)ps2KernelEnableInterrupts();
 for(;;){
  uint64_t result=ps2SifRpcBind(0x59e780,UINT64_C(0xffffffff80000001),0);
  if(result>>63)return UINT64_MAX;
  if(r(0x59e7a4))break;
  /* Original bounded delay: V0 starts0x100000 and decrements to-1. */
  for(volatile uint32_t delay=0x100000;delay!=UINT32_MAX;delay--){}
 }
 ps2FileRpcDescriptorInitialize();(void)ps2KernelWaitSema(r(0x52c348));
 for(uint32_t a=0x59e580;a<0x59e780;a+=16)w(a+4,0);
 (void)ps2KernelSignalSema(r(0x52c348));w(0x59d480,0x59e140);
 uint64_t result=ps2SifRpcCall(0x59e780,255,0,0x59d480,4,0x59e100,4,0,0);
 if(result>>63)return UINT64_C(0xfffffffffffeffff);
 w(0x59e7a8,r(0x2059e100));w(0x52c340,1);return 0;
}

/* Complete original IPU reset, interrupt registration and decoder startup. */
#include "movie_startup.h"
#include "movie_archive.h"
#include "movie_decoder.h"
#include "texture_construction.h"
#include "draw_interrupt.h"
#include "display_control.h"
#include "file_device.h"
#include "material_fiveword_pool.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveMovieArchiveAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){
 if(a>=0x10000000&&a<0x10010000){
#if UINTPTR_MAX > UINT32_MAX
  return nocturneMovieDecoderMmioRead(a);
#else
  return *(volatile uint32_t *)(uintptr_t)a;
#endif
 }
 uint32_t v;memcpy(&v,at(a),4);return v;
}
static void w32(uint32_t a,uint32_t v){
 if(a>=0x10000000&&a<0x10010000){
#if UINTPTR_MAX > UINT32_MAX
  nocturneMovieDecoderMmioWrite(a,v);
#else
  *(volatile uint32_t *)(uintptr_t)a=v;
#endif
 }else memcpy(at(a),&v,4);
}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static void waitIpu(void){while(r32(0x10002010)&0x80000000u){}}
static void fifo(uint32_t address){
 NocturneQuadword q;memcpy(&q,at(address),16);nocturneMovieIpuFifoWrite(q);
}
uint64_t ps2KernelAddIntcHandler2(uint64_t cause,uint64_t callback,uint64_t next,uint64_t argument){
 uint64_t args[4]={cause,callback,next,argument};return nocturneDrawInterruptKernelValue(0x10,4,args);
}
uint64_t ps2KernelAddSbusHandler(uint64_t cause,uint64_t callback){
 uint64_t args[2]={cause,callback};return nocturneDrawInterruptKernelValue(0x0a,2,args);
}
uint64_t ps2InterruptHandlerRegister(uint64_t kind,uint64_t cause,uint64_t callback,uint64_t next,uint64_t argument){
 uint64_t handler;
 if(kind==1)handler=ps2KernelAddDmaHandler(cause,callback,next,argument);
 else if(kind==0)handler=ps2KernelAddIntcHandler2(cause,callback,next,argument);
 else if(kind==2)handler=ps2KernelAddSbusHandler(cause,callback);
 else ps2FatalSpin(0x549018,kind);
 uint32_t node=(uint32_t)ps2TextureStagingAllocate(16),head=r32(0x551820);
 w32(node+4,(uint32_t)kind);w32(node+8,(uint32_t)cause);w32(node+12,(uint32_t)handler);
 w32(node,head);w32(0x551820,node);return sx(node);
}
/* This duplicate reset helper also unconditionally restores EI at its tail. */
uint64_t ps2MovieIpuResetInputDma(uint64_t control){
 (void)ps2KernelDisableInterrupts();w32(0x1000f590,r32(0x1000f520)|0x10000);
 w32(0x1000b400,(uint32_t)control);w32(0x1000f590,r32(0x1000f520)&0xfffeffffu);
 return ps2KernelEnableInterrupts();
}
void ps2MovieIpuInitialize(void){
 (void)ps2MovieIpuResetInputDma(1);w32(0x10002010,0x40000000);waitIpu();w32(0x10002000,0);waitIpu();
 fifo(0x52baa0);fifo(0x52bab0);fifo(0x52bac0);fifo(0x52bad0);
 fifo(0x52bae0);fifo(0x52bae0);fifo(0x52bae0);fifo(0x52bae0);
 w32(0x10002000,0x50000000);waitIpu();w32(0x10002000,0x58000000);waitIpu();
 fifo(0x52baf0);fifo(0x52bb00);w32(0x10002000,0x60000000);waitIpu();
 w32(0x10002000,0x90000000);waitIpu();w32(0x10002010,0x40000000);waitIpu();w32(0x10002000,0);waitIpu();
}
uint64_t ps2MovieDecoderStartup(void){
 ps2MovieIpuInitialize();w32(0x10002000,0x90000000);w32(0x552148,0);w32(0x552154,0);
 uint64_t output=ps2InterruptHandlerRegister(1,3,0x2c4b10,UINT64_MAX,0);w32(0x55214c,(uint32_t)output);(void)ps2KernelEnableDmac(3);
 uint64_t input=ps2InterruptHandlerRegister(1,4,0x2c4b40,UINT64_MAX,0);w32(0x552150,(uint32_t)input);(void)ps2KernelEnableDmac(4);
 uint64_t thread=ps2ThreadCreateWithStack(0x2c4a40,0x593f80,0x800,0x46);w32(0x552164,(uint32_t)thread);
 return ps2KernelStartThread(thread,0);
}

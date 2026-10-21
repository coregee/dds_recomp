/* Complete original tracked-handler removal and movie-system startup. */
#include "interrupt_lifecycle.h"
#include "movie_archive.h"
#include "movie_decoder.h"
#include "movie_startup.h"
#include "display_control.h"
#include "draw_interrupt.h"
#include "process_creation.h"
#include "movie_frame.h"
#include "compiler_numeric.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveMovieArchiveAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
/* Preserve repeated original LW/SW accesses in the unusual traversal loop. */
static uint32_t r32(uint32_t a){return *(volatile uint32_t *)at(a);}
static void w32(uint32_t a,uint32_t v){*(volatile uint32_t *)at(a)=v;}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
uint64_t ps2KernelRemoveSbusHandler(uint64_t cause){
 return nocturneDrawInterruptKernelValue(0x0b,1,&cause);
}
void ps2InterruptHandlerRemove(uint64_t handler){
 uint32_t slot=0x551820,node=r32(slot);
 while(node){
  if(sx(node)==handler){
   uint32_t next=r32(node),kind=r32(node+4);w32(slot,next);
   if(kind==1)(void)ps2KernelRemoveDmaHandler(sx(r32(node+8)),sx(r32(node+12)));
   else if(kind==0){(void)ps2KernelDisableIntc(sx(r32(node+8)));(void)ps2KernelRemoveIntcHandler(sx(r32(node+8)),sx(r32(node+12)));}
   else if(kind==2)(void)ps2KernelRemoveSbusHandler(sx(r32(node+8)));
   ps2PoolOrMemoryPointerFree(handler);return;
  }
  /* Original BNEL delay slot uses the requested node, not the current node. */
  slot=(uint32_t)handler;node=r32(slot);
 }
}
void ps2InterruptHandlersClear(void){
 uint32_t node=r32(0x551820);
 while(node){ps2InterruptHandlerRemove(sx(node));node=r32(0x551820);}
}
uint64_t ps2MovieSystemInitialize(void){
 (void)ps2MovieDecoderStartup();return dds3StartProcess(0x53f3d8,0x385,1,0,0x22b808,0,0);
}
uint64_t ps2MovieUpdateProcess(void){
 uint16_t rate=*(volatile uint16_t *)at(0x54e82c);
 if(!rate)nocturneCompilerArithmeticTrap(7);
 ps2MovieDecoderUpdate(60u/rate);return 0;
}

/* Original PS2 movie-manager wrappers and decoder FIFO insertion. */
#include "movie_manager.h"
#include "movie_archive.h"
#include "movie_initialize.h"
#include "movie_decoder.h"
#include "process_creation.h"
#include "process_shutdown.h"
#include "material_fiveword_pool.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
 return (uint8_t *)nocturneResolveMovieArchiveAddress(a);
#else
 return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
/* 0022b710: initialize the fixed control before allocating its process. */
void ps2MoviePlayFile(uint64_t filename,uint64_t parameters){
 if(r32(0x54fd94))return;
 ps2MovieControlInitialize(0x343e40,parameters,filename);
 uint64_t process=dds3StartProcess(0x53f3c8,0x2afb,1,1,0x22b6e0,0,0);
 w32(0x54fd94,(uint32_t)process);
}
/* 0022b768: word arithmetic wraps; the record is filename plus inline params. */
void ps2MoviePlayIndex(uint64_t index){
 uint32_t record=UINT32_C(0x343be8)+(uint32_t)index*24u;
 ps2MoviePlayFile(sx(r32(record)),sx(record+4));
}
/* 0022b7a0: close can run asynchronous arrivals; reload the process afterwards. */
void ps2MovieStop(void){
 if(!r32(0x54fd94))return;
 ps2MovieControlClose(0x343e40);
 (void)dds3KillProcess(sx(r32(0x54fd94)),0);
 w32(0x54fd94,0);
}
/* 002c3b40: move an existing queued decoder to the tail under the same lock. */
void ps2MovieDecoderQueueAppend(uint64_t decoder,uint64_t interrupts_disabled){
 uint32_t d=(uint32_t)decoder,restore=interrupts_disabled?0:ps2KernelDisableInterrupts();
 if(*at(d+13))(void)ps2MovieDecoderQueueRemove(decoder,1);
 *at(d+13)=1;
 uint32_t tail=r32(0x552160);
 if(tail)w32(tail+4,d);else w32(0x55215c,d);
 w32(d,tail);w32(d+4,0);w32(0x552160,d);
 if(!interrupts_disabled&&restore)(void)ps2KernelEnableInterrupts();
}

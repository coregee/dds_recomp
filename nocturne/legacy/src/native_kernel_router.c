#include "native_kernel_router.h"
#include "battle_syscall_kernel_resume.h"
#include "ps2_thread_kernel.h"
#include "battle_irq_kernel.h"
#include "ps2_semaphore_kernel.h"
#include "ps2_semaphore_wait_delete.h"
#include "libc_heap_native.h"
#include "sound_rpc_queue_native.h"
static int owner(uint32_t p){
 static const uint32_t ranges[][3]={
 {UINT32_C(0x80000180),UINT32_C(0x800001a8),1u},
 {UINT32_C(0x80000280),UINT32_C(0x80000378),1u},
 {UINT32_C(0x80003340),UINT32_C(0x800033b0),1u},
 {UINT32_C(0x80003680),UINT32_C(0x800037e8),1u},
 {UINT32_C(0x80003800),UINT32_C(0x8000393c),1u},
 {UINT32_C(0x800046b0),UINT32_C(0x80004804),1u},
 {UINT32_C(0x800059b8),UINT32_C(0x80005a10),1u},
 {UINT32_C(0x80005b08),UINT32_C(0x80005b24),1u},
 {UINT32_C(0x80004548),UINT32_C(0x80004558),1u},
 {UINT32_C(0x80004970),UINT32_C(0x800049b0),1u},
 {UINT32_C(0x800032c0),UINT32_C(0x8000333c),1u},
 {UINT32_C(0x80004658),UINT32_C(0x800046ac),1u},
 {UINT32_C(0x80005978),UINT32_C(0x800059b4),1u},
 {UINT32_C(0x80005ae8),UINT32_C(0x80005b04),1u},
 {UINT32_C(0x80003a78),UINT32_C(0x80003bb4),1u},
 {UINT32_C(0x80003c50),UINT32_C(0x80003dfc),2u},
 {UINT32_C(0x80003040),UINT32_C(0x800030b0),2u},
 {UINT32_C(0x80003f70),UINT32_C(0x80003ff4),2u},
 {UINT32_C(0x80005a58),UINT32_C(0x80005a94),2u},
 {UINT32_C(0x80000180),UINT32_C(0x800001a8),3u},
 {UINT32_C(0x80000200),UINT32_C(0x8000024c),3u},
 {UINT32_C(0x80000280),UINT32_C(0x80000378),3u},
 {UINT32_C(0x80000380),UINT32_C(0x8000048c),3u},
 {UINT32_C(0x80001300),UINT32_C(0x8000139c),3u},
 {UINT32_C(0x800013c0),UINT32_C(0x80001460),3u},
 {UINT32_C(0x8000363c),UINT32_C(0x80003678),3u},
 {UINT32_C(0x80003680),UINT32_C(0x800037e8),3u},
 {UINT32_C(0x80003800),UINT32_C(0x8000393c),3u},
 {UINT32_C(0x80003940),UINT32_C(0x80003a74),3u},
 {UINT32_C(0x80004548),UINT32_C(0x80004558),3u},
 {UINT32_C(0x800046b0),UINT32_C(0x80004804),3u},
 {UINT32_C(0x80004bc8),UINT32_C(0x80004cf8),3u},
 {UINT32_C(0x800059b8),UINT32_C(0x80005a10),3u},
 {UINT32_C(0x80005a58),UINT32_C(0x80005a94),3u},
 {UINT32_C(0x80005ae8),UINT32_C(0x80005b04),3u},
 {UINT32_C(0x80005b08),UINT32_C(0x80005b24),3u},
 {UINT32_C(0x800049c0),UINT32_C(0x80004a44),4u},
 {UINT32_C(0x80004e68),UINT32_C(0x80004ec4),4u},
 {UINT32_C(0x80003440),UINT32_C(0x800034b4),5u},
 {UINT32_C(0x80003540),UINT32_C(0x800035b0),5u},
 {UINT32_C(0x80004a48),UINT32_C(0x80004bc4),5u},
 {UINT32_C(0x80004cf8),UINT32_C(0x80004dc4),5u},
 {UINT32_C(0x002d3be8),UINT32_C(0x002d4310),6u},
 {UINT32_C(0x002d3990),UINT32_C(0x002d3be8),6u},
 {UINT32_C(0x002d9998),UINT32_C(0x002d9c8c),6u},
 {UINT32_C(0x002d9c90),UINT32_C(0x002d9dfc),6u},
 {UINT32_C(0x002d4618),UINT32_C(0x002d4694),6u},
 {UINT32_C(0x002d4698),UINT32_C(0x002d46e4),6u},
 {UINT32_C(0x002d5250),UINT32_C(0x002d52a8),6u},
 {UINT32_C(0x002dc5a0),UINT32_C(0x002dc64c),6u},
 {UINT32_C(0x002e40d0),UINT32_C(0x002e4118),6u},
 {UINT32_C(0x002e6e30),UINT32_C(0x002e6e3c),6u},
 {UINT32_C(0x002dbe80),UINT32_C(0x002dbe90),6u},
 {UINT32_C(0x002dbec0),UINT32_C(0x002dbed0),6u},
 {UINT32_C(0x800034c0),UINT32_C(0x80003540),6u},
 {UINT32_C(0x800052d8),UINT32_C(0x800052fc),6u},
 {UINT32_C(0x002dbd90),UINT32_C(0x002dbda0),7u},
 {UINT32_C(0x002e4070),UINT32_C(0x002e40b8),7u},
 {UINT32_C(0x002e40b8),UINT32_C(0x002e40d0),7u},
 };
 for(unsigned i=0;i<sizeof(ranges)/sizeof(ranges[0]);++i)if(p>=ranges[i][0]&&p<ranges[i][1])return(int)ranges[i][2];return 0;
}
int nocturneNativeKernelOwns(uint32_t pc){return owner(pc)!=0;}
uint32_t nocturneNativeKernelBody(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t budget,NocturneWakeupStop *s){
 switch(owner(m->pc)){
 case 1:return nocturneBattleSyscallKernelResume(m,ram,budget,s);
 case 2:return nocturneThreadKernelResume(m,ram,budget,s);
 case 3:return nocturneBattleIrqKernelResume(m,ram,budget,s);
 case 4:return nocturneSemaphoreKernelResume(m,ram,budget,s);
 case 5:return nocturneSemaphoreWaitDeleteResume(m,ram,budget,s);
 case 6:return nocturneLibcHeapResume(m,ram,budget,s);
 case 7:return nocturneSoundRpcQueueResume(m,ram,budget,s);
 default:s->outcome=8;s->pc=m->pc;s->address=s->bytes=0;s->target=(uint64_t)(int64_t)(int32_t)m->pc;return 8;
 }
}
static int contains(void *v,uint32_t p){(void)v;return nocturneNativeKernelOwns(p);}
static uint32_t resume(void *v,NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t n,NocturneWakeupStop *s){(void)v;return nocturneNativeKernelBody(m,ram,n,s);}
uint32_t nocturneNativeKernelResume(NocturneWakeupMachine *m,const NocturneWakeupMemory *ram,uint64_t n,uint32_t stop_pc,NocturneWakeupStop *s,NocturneNativeRouteCounts *counts){
 const NocturneNativeRouter router={0,contains,resume};return nocturneNativeRouteResume(m,ram,&router,n,stop_pc,s,counts);
}

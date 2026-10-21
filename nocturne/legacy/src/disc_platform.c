/* Disc/movie platform prerequisites, reconstructed from complete EE bodies.
 * Alarm duration is explicitly narrowed to sixteen bits. Units are unclaimed.
 * These routines do not replace either callback with a supplied game result. */
#include "disc_platform.h"
#include "heap_queue.h"
#include "file_rpc.h"
#include "draw_interrupt.h"
#include "draw_consumer_support.h"
#include "display_control.h"
#include "material_fiveword_pool.h"
#include <string.h>
static uint8_t *at(uint32_t address) {
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveDiscPlatformAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t word(uint32_t address) { uint32_t v; memcpy(&v,at(address),4); return v; }
static void put(uint32_t address,uint32_t v) { memcpy(at(address),&v,4); }
static uint64_t sx(uint32_t v) { return v&UINT32_C(0x80000000)?UINT64_C(0xffffffff00000000)|v:v; }
/* 002def38: serial mismatch makes a recycled packet inactive. */
uint64_t ps2SifRpcIsBusy(uint64_t client) {
    uint32_t p=(uint32_t)client,packet=word(p);
    if(!packet || word(p+4)!=word(packet+24)) return 0;
    return word(packet+16)&1;
}
/* 002cb6f0: if either semaphore is -1, recreate all three, in this order. */
void ps2CdInitializeSemaphores(void) {
    if(word(0x52a028)!=UINT32_MAX && word(0x52a02c)!=UINT32_MAX) return;
    uint32_t packet[6];packet[1]=1;packet[2]=1;packet[5]=0;
    put(0x52a028,ps2KernelCreateSema(packet));
    put(0x52a02c,ps2KernelCreateSema(packet));
    packet[2]=0;put(0x52a020,ps2KernelCreateSema(packet));
    put(0x52a030,0);
}
uint64_t ps2KernelPollSema(uint64_t semaphore) {
    return nocturneDiscPlatformKernel(0x45,1,&semaphore); /* 002dbef0 */
}
uint64_t ps2KernelReferThreadStatus(uint64_t thread,uint64_t status) {
    uint64_t args[2]={thread,status};return nocturneDiscPlatformKernel(0x30,2,args); /* 002dbda0 */
}
uint64_t ps2KernelSetAlarmRaw(uint64_t delay,uint64_t callback,uint64_t argument) {
    uint64_t args[3]={delay,callback,argument};return nocturneDiscPlatformKernel(0xfc,3,args); /* 002dbc20 */
}
/* 002cb328: SYNC0 then EI execute even when iSignalSema fails. */
void ps2CdAlarmSignal(uint64_t alarm,uint64_t time,uint64_t semaphore) {
    (void)alarm;(void)time;(void)ps2KernelInterruptSignalSema(semaphore);
    nocturneDrawInterruptSync();EE_SYSTEM_EI();
}
/* 002cb350: create, register, wait, delete even if a preceding call failed. */
uint64_t ps2CdDelay(uint64_t delay) {
    uint32_t packet[6];packet[1]=1;packet[2]=0;packet[5]=0;
    uint64_t semaphore=sx(ps2KernelCreateSema(packet));
    (void)ps2KernelSetAlarmRaw(delay&0xffff,0x2cb328,semaphore);
    (void)ps2KernelWaitSema((uint32_t)semaphore);
    return ps2KernelDeleteSema(semaphore);
}
/* 002a8508: third alarm argument is the thread; tail-call actual wake code. */
uint64_t ps2FileAlarmWakeThread(uint64_t alarm,uint64_t time,uint64_t thread) {
    (void)alarm;(void)time;return ps2DrawWakeThread(thread);
}
/* 002a8520: cancel prior wakeups, install an alarm, then sleep. */
uint64_t ps2FileDelay(uint64_t delay) {
    uint64_t thread=sx(ps2KernelGetThreadId());
    (void)ps2KernelCancelWakeupThread(thread);
    (void)ps2KernelSetAlarmRaw(delay&0xffff,0x2a8508,thread);
    return ps2KernelSleepThread();
}

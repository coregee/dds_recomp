/* Complete CD initialization/callback/thread/shutdown bodies, including two
 * originally unowned instruction spans discovered in the working executable. */
#include "cd_lifecycle.h"
#include "cd_stream.h"
#include "disc_platform.h"
#include "file_rpc.h"
#include "sif_initialization.h"
#include "heap_queue.h"
#include "file_device.h"
#include "file_worker_control.h"
#include "material_fiveword_pool.h"
#include "draw_interrupt.h"
#include "sdk_debug.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveCdStreamAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int positive(uint32_t v){return v!=0&&!(v&0x80000000u);}
static int less32(uint32_t a,uint32_t b){return (a^0x80000000u)<(b^0x80000000u);}
static void invoke(uint32_t callback,uint64_t parameter){
#if UINTPTR_MAX > UINT32_MAX
    nocturneCdLifecycleCallback(callback,parameter);
#else
    ((void (*)(uint64_t))(uintptr_t)callback)(parameter);
#endif
}
/* 002cb3b8: N activity blocks callback replacement. */
uint64_t ps2CdSetReadCallback(uint64_t callback){
    if(ps2CdNWait(1))return 0;
    uint32_t enabled=ps2KernelDisableInterrupts(),old=word(0x598c40);
    put(0x598c40,(uint32_t)callback);if(enabled)(void)ps2KernelEnableInterrupts();return sx(old);
}
/* 002cb418: command11 clears activity without signaling either semaphore. */
void ps2CdReplyNotify(uint64_t packet){
    put(0x52a054,word((uint32_t)packet));put(0x52a058,word(0x52a054));
    if(word(0x52a054)==11){put(0x52a054,0);put(0x52a030,0);return;}
    (void)ps2KernelInterruptSignalSema(sx(word(0x52a028)));
    if(word(0x52a014)&&word(0x598c40))(void)ps2KernelInterruptSignalSema(sx(word(0x52a020)));
    else put(0x52a030,0);
    put(0x52a054,0);
}
uint64_t ps2KernelExitThreadRaw(void){return nocturneDiscPlatformKernel(0x24,0,0);}
/* 002cb4b8: original infinite worker. A successful kernel ExitThread ends the
 * thread externally; its raw wrapper may return if the service fails. */
_Noreturn void ps2CdCallbackThreadMain(void){
    for(;;){
        (void)ps2KernelWaitSema(word(0x52a020));
        if(word(0x52a054)==UINT32_MAX){
            put(0x52a030,0);put(0x52a054,0);put(0x52a014,0);put(0x598c4c,0);
            (void)ps2KernelExitThreadRaw();
        }
        if(positive(word(0x52a010)))ps2SdkPrintf(0x54aab8,sx(word(0x598c40)),sx(word(0x52a058)),0,0,0,0,0);
        uint32_t callback=word(0x598c40);
        if(callback&&word(0x52a058))invoke(callback,sx(word(0x52a058)));
        put(0x52a030,0);
    }
}
/* 002cb578: first call creates/starts the worker; later calls only reprioritize.
 * Thread attributes at record+0 are left as the original live global word. */
uint64_t ps2CdEnsureCallbackThread(uint64_t priority,uint64_t stack,uint64_t stack_bytes){
    uint32_t handle=word(0x52a014);
    if(handle){(void)ps2KernelChangeThreadPriority(sx(handle),priority);return 0;}
    uint64_t thread=sx(ps2KernelGetThreadId());put(0x598c50,(uint32_t)thread);
    (void)ps2KernelReferThreadStatus(thread,0x598c58);
    put(0x598c94,(uint32_t)stack_bytes);put(0x598c98,0x554170);
    put(0x598c8c,0x2cb4b8);put(0x598c90,(uint32_t)stack);put(0x598c9c,(uint32_t)priority);
    thread=ps2KernelCreateThread(at(0x598c88));put(0x52a014,(uint32_t)thread);
    (void)ps2KernelStartThread(thread,0);return 1;
}
/* 002cb650: byte loops reload their signed count after every store, including
 * header/data/output aliases. Tail notification uses global command52a054. */
void ps2CdReadCopyReply(uint64_t packet){
    uint32_t base=(uint32_t)packet|0x20000000u,count=word(base);
    if(positive(count)){
        uint32_t out=word(base+8),index=0;
        do{uint8_t value=*at(base+16+index);*at(out+index)=value;index++;count=word(base);}while(less32(index,count));
    }
    count=word(base+4);
    if(positive(count)){
        uint32_t out=word(base+12),index=0;
        do{uint8_t value=*at(base+80+index);*at(out+index)=value;index++;count=word(base+4);}while(less32(index,count));
    }
    ps2CdReplyNotify(0x52a054);
}
/* 002de150: remove only the handler word; retain the parameter word. */
void ps2SifRemoveCommandHandler(uint64_t command){
    uint32_t table=word(command>>63?0x59baa4:0x59baac);put(table+((uint32_t)command<<3),0);
}
/* 002cb788: three DeleteSema calls even after earlier failures. */
void ps2CdExit(void){
    if(word(0x52a014)){put(0x52a054,UINT32_MAX);(void)ps2KernelSignalSema(word(0x52a020));}
    (void)ps2KernelDeleteSema(sx(word(0x52a028)));
    (void)ps2KernelDeleteSema(sx(word(0x52a02c)));
    (void)ps2KernelDeleteSema(sx(word(0x52a020)));
    uint32_t enabled=ps2KernelDisableInterrupts();ps2SifRemoveCommandHandler(UINT64_C(0xffffffff80000012));
    if(enabled)(void)ps2KernelEnableInterrupts();
}
/* 002cb820 / 002cb898 / 002cb8d8. */
uint64_t ps2CdSetCommandCallback(uint64_t callback,uint64_t parameter){
    if(word(0x52a03c)&0x80000000u)(void)ps2CdRegisterCommandCallback();
    uint32_t enabled=ps2KernelDisableInterrupts(),old=word(0x598c44);
    put(0x598c48,(uint32_t)parameter);put(0x598c44,(uint32_t)callback);
    if(enabled)(void)ps2KernelEnableInterrupts();return sx(old);
}
void ps2CdCommandCallback(void){
    uint32_t callback=word(0x598c44);
    if(callback&&!word(0x52a024))invoke(callback,sx(word(0x598c48)));
}
uint64_t ps2CdRegisterCommandCallback(void){
    put(0x52a024,1);uint32_t enabled=ps2KernelDisableInterrupts();
    ps2SifAddCommandHandler(UINT64_C(0xffffffff80000012),0x2cb898,0);
    if(enabled)(void)ps2KernelEnableInterrupts();put(0x52a024,0);put(0x52a03c,1);return 1;
}
/* 002cc110. Result1/2 derives from reply ABI/version words and special FF/FE.
 * The rounding expression operates as wrapped, sign-extended word arithmetic. */
static int versionBelowTwo(uint32_t value){
    uint32_t rounded=value+255;
    if(!(value&0x80000000u))rounded=value;
    uint32_t shifted=rounded>>8;if(rounded&0x80000000u)shifted|=0xff000000u;
    return less32(shifted,2);
}
uint64_t ps2CdInitialize(uint64_t mode){
    if(ps2CdSWait(1))return 0;ps2SifRpcInitialize();
    uint64_t thread=sx(ps2KernelGetThreadId());
    uint32_t serial=word(0x52a050)+1;put(0x52a024,1);put(0x598c50,(uint32_t)thread);
    put(0x52a03c,UINT32_MAX);put(0x52a040,UINT32_MAX);put(0x52a038,UINT32_MAX);
    put(0x52a048,UINT32_MAX);put(0x52a044,UINT32_MAX);put(0x52a034,0);
    put(0x52a050,serial);put(0x52a04c,UINT32_MAX);
    for(;;){
        uint64_t bound=ps2SifRpcBind(0x598e68,UINT64_C(0xffffffff80000592),0);
        if(bound>>63){
            if(positive(word(0x52a010)))ps2SdkPrintf(0x54abf0,bound,sx(word(0x52a050)),0,0,0,0,0);
        }else if(word(0x598e8c))break;
        for(volatile uint32_t v=0x100000;v!=UINT32_MAX;v--){}
    }
    put(0x598ec0,(uint32_t)mode);put(0x52a04c,0);ps2SifSyncDataCache(0x598ec0,4);
    uint64_t result=ps2SifRpcCall(0x598e68,0,0,0x598ec0,4,0x52b200,16,0,0);
    if(result>>63){put(0x52a024,0);return 0;}
    uint32_t marker=word(0x2052b20c),first=word(0x2052b204),second=word(0x2052b208);result=1;
    if(marker==0xfe)put(0x52a010,1);
    else if(marker!=0xff&&(versionBelowTwo(first)||versionBelowTwo(second)))result=2;
    put(0x52a024,0);
    if(!(mode>>63)&&mode>=2&&mode==5){
        if(positive(word(0x52a010)))ps2SdkPrintf(0x54ac10,0,0,0,0,0,0,0);
        ps2CdExit();put(0x52a028,UINT32_MAX);put(0x52a02c,UINT32_MAX);put(0x52a020,UINT32_MAX);
    }else{ps2CdInitializeSemaphores();(void)ps2CdRegisterCommandCallback();}
    return result;
}

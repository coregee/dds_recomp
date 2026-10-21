/* Complete EE CD preflight/wait/stream bodies. RPC and debug calls execute
 * recovered code. Cached/uncached addresses remain distinct memory operands. */
#include "cd_stream.h"
#include "disc_platform.h"
#include "file_rpc.h"
#include "sif_initialization.h"
#include "heap_queue.h"
#include "sdk_debug.h"
#include <string.h>
static uint8_t *at(uint32_t address) {
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveCdStreamAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int positive(uint32_t v){return v!=0&&!(v&0x80000000u);}
static void print(uint32_t f,uint64_t a,uint64_t b,uint64_t c,uint64_t d){ps2SdkPrintf(f,a,b,c,d,0,0,0);}
/* The native loop decrements 0x100000 through -1; no timing guarantee. */
static void bindDelay(void){for(volatile uint32_t v=0x100000;v!=UINT32_MAX;v--){} }
/* 002cbc88 / 002cbfa0. A successful preflight retains the polled semaphore. */
static uint64_t preflight(uint64_t command,int normal){
    uint32_t sem=normal?0x52a028:0x52a02c,cmd=normal?0x52a01c:0x52a018;
    uint32_t flag=normal?0x52a038:0x52a048,client=normal?0x52b1d0:0x52ba48;
    ps2CdInitializeSemaphores();
    uint64_t acquired=ps2KernelPollSema(sx(word(sem)));
    if(acquired!=sx(word(sem))){
        if(positive(word(0x52a010)))print(normal?0x54ab50:0x54abb0,command,sx(word(cmd)),0,0);
        return 0;
    }
    uint64_t thread=sx(word(0x598c50));put(cmd,(uint32_t)command);
    (void)ps2KernelReferThreadStatus(thread,0x598c58);
    if(normal?ps2CdNWait(1):ps2CdSWait(1)){
        (void)ps2KernelSignalSema(word(sem));return 0;
    }
    ps2SifRpcInitialize();
    if(!(word(flag)&0x80000000u))return 1;
    for(;;){
        uint64_t result=ps2SifRpcBind(client,normal?UINT64_C(0xffffffff80000595):UINT64_C(0xffffffff80000593),0);
        if(result>>63){
            if(positive(word(0x52a010)))print(normal?0x54ab78:0x54abd8,0,0,0,0);
        }else if(word(client+36)){put(flag,0);return 1;}
        bindDelay();
    }
}
uint64_t ps2CdNPreflight(uint64_t command){return preflight(command,1);}
uint64_t ps2CdSPreflight(uint64_t command){return preflight(command,0);}
/* 002cbe90. The N busy word short-circuits serial-aware RPC activity. */
uint64_t ps2CdNWait(uint64_t mode){
    if(mode)return word(0x52a030)?1:(ps2SifRpcIsBusy(0x52b1d0)!=0);
    if(positive(word(0x52a010)))print(0x54ab90,0,0,0,0);
    while(word(0x52a030)||ps2SifRpcIsBusy(0x52b1d0))(void)ps2CdDelay(60);
    return 0;
}
/* 002cbf30. */
uint64_t ps2CdSWait(uint64_t mode){
    if(mode)return ps2SifRpcIsBusy(0x52ba48);
    if(positive(word(0x52a010)))print(0x54aba0,0,0,0,0);
    while(ps2SifRpcIsBusy(0x52ba48))(void)ps2CdDelay(60);
    return 0;
}
/* 002ccd28. Mode byte loads/stores are interleaved for overlapping pointers. */
uint64_t ps2CdStreamCommand(uint64_t sector,uint64_t count,uint64_t buffer,uint64_t operation,uint64_t mode){
    if(!ps2CdNPreflight(15))return 0;
    uint32_t debug=word(0x52a010);
    if(positive(debug)){print(0x54ad98,0,0,0,0);debug=word(0x52a010);}
    put(0x52a100,(uint32_t)sector);put(0x52a104,(uint32_t)count);
    put(0x52a108,(uint32_t)buffer);put(0x52a10c,(uint32_t)operation);
    if(mode)for(uint32_t k=0;k<3;k++){uint8_t v=*at((uint32_t)mode+k);*at(0x52a110+k)=v;}
    if(positive(debug))print(0x54adb0,0,0,0,0);
    ps2SifSyncDataCache(0x52a100,20);
    uint64_t result=ps2SifRpcCall(0x52b1d0,9,0,0x52a100,20,0x52a080,4,0,0);
    if(result>>63){(void)ps2KernelSignalSema(word(0x52a028));return 0;}
    if(positive(word(0x52a010)))print(0x54adc8,0,0,0,0);
    result=sx(word(0x2052a080));(void)ps2KernelSignalSema(word(0x52a028));return result;
}
/* 002cc9e0 / 002cca78. Active state changes before the command, even on failure. */
uint64_t ps2CdStreamStart(uint64_t sector,uint64_t mode){put(0x52ba70,1);return ps2CdStreamCommand(sector,0,0,1,mode);}
uint64_t ps2CdStreamStop(void){put(0x52ba70,0);return ps2CdStreamCommand(0,0,0,3,0x598ed8);}
/* 002ccab0. Word arithmetic wraps; comparison with original count is full64. */
uint64_t ps2CdStreamRead(uint64_t count,uint64_t buffer,uint64_t mode,uint64_t error){
    if(positive(word(0x52a010)))print(0x54acb8,count,mode,0,0);
    if(!word(0x52ba70))return 0;
    ps2SifSyncDataCache(buffer,sx((uint32_t)count<<11));
    uint64_t total=0;uint32_t lastError=0;
    if(!mode){
        uint64_t result=ps2CdStreamCommand(0,count,buffer,2,0x598ed8);
        put((uint32_t)error,(uint32_t)result>>16);return result&0xffff;
    }
    for(;;){
        uint64_t result=ps2CdStreamCommand(0,sx((uint32_t)count-(uint32_t)total),sx((uint32_t)buffer+((uint32_t)total<<11)),2,0x598ed8);
        uint32_t chunk=(uint32_t)result&0xffff,currentError=(uint32_t)result>>16;
        total=sx((uint32_t)total+chunk);
        if(currentError){
            lastError=currentError;
            if(positive(word(0x52a010)))print(0x54ace8,total,chunk,count,currentError);
        }else if(!chunk)(void)ps2CdDelay(8);
        if(total==count||(currentError&&!chunk))break;
    }
    if(positive(word(0x52a010)))print(0x54ad30,0,0,0,0);
    put((uint32_t)error,lastError);return total;
}
/* 002cc748. Load the uncached reply before releasing S semaphore. */
uint64_t ps2CdGetError(void){
    if(!ps2CdSPreflight(2))return UINT64_MAX;
    uint64_t result=ps2SifRpcCall(0x52ba48,12,0,0,0,0x52b200,4,0,0);
    if(result>>63){(void)ps2KernelSignalSema(word(0x52a02c));return UINT64_MAX;}
    result=sx(word(0x2052b200));(void)ps2KernelSignalSema(word(0x52a02c));
    uint32_t debug=word(0x52a010);
    if(!(debug&0x80000000u)&&debug>=2)print(0x54ac68,0,0,0,0);
    return result;
}

/* Full native CD search/readiness/control bodies. Calls use real recovered
 * RPC, semaphore and formatter code; ordinary IOP replies remain external. */
#include "cd_services.h"
#include "cd_stream.h"
#include "disc_platform.h"
#include "file_rpc.h"
#include "sif_initialization.h"
#include "heap_queue.h"
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
static int debug(void){uint32_t v=word(0x52a010);return v!=0&&!(v&0x80000000u);}
static void print(uint32_t format,uint64_t value){ps2SdkPrintf(format,value,0,0,0,0,0,0);}
static void bindDelay(void){for(volatile uint32_t v=0x100000;v!=UINT32_MAX;v--){} }
static void bind(uint32_t flag,uint32_t client,uint64_t server,uint32_t message){
    if(!(word(flag)&0x80000000u))return;
    for(;;){
        uint64_t result=ps2SifRpcBind(client,server,0);
        if(result>>63){if(debug())print(message,0);}
        else if(word(client+36)){put(flag,0);return;}
        bindDelay();
    }
}
/* 002cb950: output is 36 bytes. Load four doublewords before any output store,
 * then load/store the final word, preserving overlapping record semantics. */
uint64_t ps2CdSearchFileExtended(uint64_t output,uint64_t path,uint64_t layer){
    ps2CdInitializeSemaphores();
    uint64_t polled=ps2KernelPollSema(sx(word(0x52a028)));
    if(polled!=sx(word(0x52a028)))return 0;
    uint64_t thread=sx(word(0x598c50));put(0x52a01c,1);
    (void)ps2KernelReferThreadStatus(thread,0x598c58);
    if(ps2CdNWait(1)){(void)ps2KernelSignalSema(word(0x52a028));return 0;}
    ps2SifRpcInitialize();bind(0x52a040,0x598e40,UINT64_C(0xffffffff80000597),0x54aae0);
    uint32_t index=0;uint8_t c=*at((uint32_t)path);*at(0x598ce4)=c;
    if(c){
        index=1;
        while(index<256){c=*at((uint32_t)path+index);*at(0x598ce4+index)=c;if(!c)break;index++;}
    }
    if(index==256)*at(0x598de3)=0;
    if(debug())print(0x54ab00,0x598ce4);
    put(0x598de8,(uint32_t)layer);put(0x598de4,0x598cc0);
    ps2SifSyncDataCache(0x598cc0,300);
    uint64_t result=ps2SifRpcCall(0x598e40,0,0,0x598cc0,300,0x598e00,4,0,0);
    if(result>>63){(void)ps2KernelSignalSema(word(0x52a028));return 0;}
    uint64_t values[4];for(unsigned k=0;k<4;k++)memcpy(&values[k],at(0x20598cc0+k*8),8);
    for(unsigned k=0;k<4;k++)memcpy(at((uint32_t)output+k*8),&values[k],8);
    put((uint32_t)output+32,word(0x20598ce0));
    if(debug()){
        print(0x54ab18,sx((uint32_t)output+8));
        if(debug()){
            print(0x54ab28,sx(word((uint32_t)output+4)));
            if(debug())print(0x54ab38,sx(word((uint32_t)output)));
        }
    }
    result=sx(word(0x20598e00));(void)ps2KernelSignalSema(word(0x52a028));return result;
}
/* 002cbc68. */
uint64_t ps2CdSearchFile(uint64_t output,uint64_t path){return ps2CdSearchFileExtended(output,path,0);}
/* 002cc3f0: a failed poll always returns 6; later failures return -1 only when
 * the complete raw input equals 8. Successful replies are loaded before unlock. */
uint64_t ps2CdDiskReady(uint64_t mode){
    if(debug())print(0x54ac20,0);ps2CdInitializeSemaphores();
    uint64_t polled=ps2KernelPollSema(sx(word(0x52a02c)));
    if(polled!=sx(word(0x52a02c)))return 6;
    if(ps2CdSWait(1)){
        (void)ps2KernelSignalSema(word(0x52a02c));return mode==8?UINT64_MAX:6;
    }
    ps2SifRpcInitialize();bind(0x52a044,0x598e90,UINT64_C(0xffffffff8000059a),0x54ac30);
    put(0x598ed0,(uint32_t)mode);ps2SifSyncDataCache(0x598ed0,4);
    uint64_t result=ps2SifRpcCall(0x598e90,0,0,0x598ed0,4,0x52b200,4,0,0);
    if(result>>63){(void)ps2KernelSignalSema(word(0x52a02c));return mode==8?UINT64_MAX:6;}
    if(debug())print(0x54ac50,0);
    result=sx(word(0x2052b200));(void)ps2KernelSignalSema(word(0x52a02c));return result;
}
/* 002cbdf8 / 002cc6b0. Distinct preflight and RPC command numbers. */
static uint64_t scalarCommand(int normal,uint64_t preflight,uint64_t command){
    if(normal?!ps2CdNPreflight(preflight):!ps2CdSPreflight(preflight))return 0;
    uint32_t client=normal?0x52b1d0:0x52ba48,receive=normal?0x52a080:0x52b200,sem=normal?0x52a028:0x52a02c;
    uint64_t result=ps2SifRpcCall(client,command,0,0,0,receive,4,0,0);
    if(result>>63){(void)ps2KernelSignalSema(word(sem));return 0;}
    result=sx(word(receive|0x20000000));(void)ps2KernelSignalSema(word(sem));return result;
}
uint64_t ps2CdNCommand14(void){return scalarCommand(1,2,14);}
uint64_t ps2CdGetDiskType(void){return scalarCommand(0,1,3);}
/* 002cc5e8. Preserve command22 identity without assuming the public SDK name. */
uint64_t ps2CdSCommand22(uint64_t mode){
    if(!ps2CdSPreflight(34))return 0;
    put(0x52b640,(uint32_t)mode);ps2SifSyncDataCache(0x52b640,4);
    uint64_t result=ps2SifRpcCall(0x52ba48,34,0,0x52b640,4,0x52b200,4,0,0);
    if(result>>63){(void)ps2KernelSignalSema(word(0x52a02c));return 0;}
    result=sx(word(0x2052b200));(void)ps2KernelSignalSema(word(0x52a02c));return result;
}
/* 002cc800. Output word store precedes reloading the return word. */
uint64_t ps2CdSCommand21OutputWord(uint64_t output){
    if(!ps2CdSPreflight(33))return 0;
    uint64_t result=ps2SifRpcCall(0x52ba48,33,0,0,0,0x52b200,8,0,0);
    if(result>>63){(void)ps2KernelSignalSema(word(0x52a02c));return 0;}
    put((uint32_t)output,word(0x2052b204));result=sx(word(0x2052b200));
    (void)ps2KernelSignalSema(word(0x52a02c));return result;
}
/* 002cc8b8. RPC receives16 bytes; caller receives exactly8 at reply+4. */
uint64_t ps2CdReadClock(uint64_t output){
    if(!ps2CdSPreflight(15))return 0;
    if(debug())print(0x54ac78,0);
    uint64_t result=ps2SifRpcCall(0x52ba48,1,0,0,0,0x52b200,16,0,0);
    if(result>>63){(void)ps2KernelSignalSema(word(0x52a02c));return 0;}
    uint64_t clock;memcpy(&clock,at(0x2052b204),8);memcpy(at((uint32_t)output),&clock,8);
    if(debug())print(0x54ac98,0);
    result=sx(word(0x2052b200));(void)ps2KernelSignalSema(word(0x52a02c));return result;
}
/* 002cc9b0: original incoming A0/A1/A2 remain live at operation5. */
uint64_t ps2CdStreamInitialize(uint64_t a0,uint64_t a1,uint64_t a2){put(0x52ba70,0);return ps2CdStreamCommand(a0,a1,a2,5,0x598ed8);}
uint64_t ps2CdStreamSeekFast(uint64_t sector){return ps2CdStreamCommand(sector,0,0,9,0x598ed8);}
uint64_t ps2CdStreamSeek(uint64_t sector){return ps2CdStreamCommand(sector,0,0,4,0x598ed8);}
uint64_t ps2CdStreamPause(void){put(0x52ba70,0);if(debug())print(0x54ad50,0);return ps2CdStreamCommand(0,0,0,7,0x598ed8);}
uint64_t ps2CdStreamResume(void){put(0x52ba70,1);if(debug())print(0x54ad68,0);return ps2CdStreamCommand(0,0,0,8,0x598ed8);}
uint64_t ps2CdStreamStatus(void){if(debug())print(0x54ad80,0);return ps2CdStreamCommand(0,0,0,6,0x598ed8);}

/* 002bed50: all nine native command-table routes. Connected comparisons:
 * analysis/movie-worker-validation.json. The original worker never returns. */
#include "movie_worker.h"
#include "movie_file.h"
#include "movie_archive.h"
#include "file_worker_execution.h"
#include "file_worker_control.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "heap_queue.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveMovieArchiveAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static void state(uint32_t job,uint8_t v){*at(job+22)=v;}
static void invoke(uint32_t callback,uint64_t job,uint64_t event,uint64_t data,uint64_t amount){
    nocturneFileWorkerInvoke(callback,job,event,data,amount,sx(word((uint32_t)job+60)));
}
_Noreturn void ps2MovieWorkerRun(uint64_t worker_raw)
{
    uint32_t worker=(uint32_t)worker_raw;
    for(;;){
        (void)ps2KernelWaitSema(word(worker+4));
        uint64_t job_raw=sx(word(worker+8));uint32_t job=(uint32_t)job_raw;
        if(!job_raw)continue;
        uint32_t command=*at(job+21);*at(job+21)=0;
        uint32_t callback;uint64_t result,amount;
        switch(command){
        case 1:
            state(job,2);result=ps2MovieFileOpen(sx(word(job+16)));
            if(result>>63){ps2FileWorkerError(job_raw,0);break;}
            state(job,7);callback=word(job+56);put(job+48,0);
            if(callback)invoke(callback,job_raw,2,0,0);
            break;
        case 4:
            callback=word(job+56);state(job,7);
            if(callback){result=ps2MovieFileSize();invoke(callback,job_raw,4,0,result);}
            break;
        case 5:
            state(job,4);result=ps2MovieFileRead(sx(word(job+32)),sx(word(job+28)));
            if(result>>63){ps2FileWorkerError(job_raw,result);break;}
            callback=word(job+56);uint32_t progress=word(job+48)+(uint32_t)result;
            state(job,7);put(job+48,progress);
            if(callback)invoke(callback,job_raw,5,sx(word(job+32)),result);
            break;
        case 7:
            state(job,6);(void)ps2MovieFileClose();(void)ps2FileJobComplete(job_raw);
            callback=word(job+56);state(job,8);
            if(callback)invoke(callback,job_raw,7,0,0);
            break;
        case 8:
            state(job,2);result=ps2MovieFileOpen(sx(word(job+16)));
            if(result>>63){ps2FileWorkerError(job_raw,0);break;}
            amount=sx(word(job+28));if(amount>>63)amount=ps2MovieFileSize();
            if(amount){
                uint32_t buffer=word(job+32);
                if(!buffer){
                    uint32_t handle=ps2MemoryHandleAllocate((int32_t)(uint32_t)amount);
                    buffer=ps2MemoryHandleAcquirePointer(handle);
                }
                put(job+32,buffer);state(job,4);amount=ps2MovieFileRead(sx(buffer),amount);
                if(amount>>63){ps2FileWorkerError(job_raw,amount);break;}
            }
            state(job,6);(void)ps2MovieFileClose();put(job+40,UINT32_MAX);
            (void)ps2FileJobComplete(job_raw);callback=word(job+56);state(job,8);
            if(callback)invoke(callback,job_raw,8,sx(word(job+32)),amount);
            break;
        case 2:case 3:case 6:case 9:
            ps2FileWorkerError(job_raw,0);break;
        default:
            break;
        }
    }
}

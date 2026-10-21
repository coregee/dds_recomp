/* Complete generic file worker and its close/error helpers, reconstructed from EE.
 * Connected original-instruction checks: analysis/file-worker-execution-validation.json.
 */
#include "file_worker_execution.h"
#include "file_worker_control.h"
#include "file_operations.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "heap_queue.h"
#include <string.h>
extern void *nocturneResolveFileDeviceAddress(uint32_t address);
static uint8_t *at(uint32_t address){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveFileDeviceAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void state(uint32_t job,uint32_t value){*at(job+22)=(uint8_t)value;}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v&0x80000000)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
static int negative(uint64_t v){return (v>>63)!=0;}
static void notify(uint64_t raw,uint64_t event,uint64_t buffer,uint64_t result){
    uint32_t job=(uint32_t)raw,callback=r(job+56);
    if(callback)nocturneFileWorkerInvoke(callback,raw,event,buffer,result,sx(r(job+60)));
}
uint64_t ps2FileWorkerCloseDetach(uint64_t job_raw)
{
    uint32_t job=(uint32_t)job_raw,handle=r(job+40);
    w(job+40,UINT32_MAX);
    if(!(handle&0x80000000))(void)ps2FileRpcClose(sx(handle));
    return ps2FileJobComplete(job_raw);
}
void ps2FileWorkerError(uint64_t job_raw,uint64_t error)
{
    uint32_t job=(uint32_t)job_raw;
    w(job+44,(uint32_t)error);state(job,9);
    (void)ps2FileWorkerCloseDetach(job_raw);
    notify(job_raw,0,0,0);
}
void ps2FileWorkerRun(uint64_t worker_raw)
{
    uint32_t worker=(uint32_t)worker_raw;
    for(;;){
        (void)ps2KernelWaitSema(r(worker+4));
        uint64_t job_raw=sx(r(worker+8));uint32_t job=(uint32_t)job_raw;
        if(!job_raw)continue;
        uint32_t command=*at(job+21);*at(job+21)=0;
        uint64_t result,amount;
        switch(command){
        case 1:case 2:
            state(job,2);
            result=ps2FileRpcOpen(sx(r(job+16)),command==1?1:0x202,command==1?0:sx(r(job+36)));
            if(negative(result)){ps2FileWorkerError(job_raw,result);break;}
            state(job,7);w(job+40,(uint32_t)result);w(job+48,0);
            notify(job_raw,2,0,0);break;
        case 3:
            state(job,3);
            result=ps2FileRpcSeek(sx(r(job+40)),sx(r(job+24)),sx(r(job+36)));
            if(negative(result)){ps2FileWorkerError(job_raw,result);break;}
            state(job,7);w(job+48,(uint32_t)result);notify(job_raw,3,0,result);break;
        case 4:{
            state(job,3);
            uint64_t position=ps2FileRpcSeek(sx(r(job+40)),0,1);
            if(negative(position)){ps2FileWorkerError(job_raw,position);break;}
            amount=ps2FileRpcSeek(sx(r(job+40)),0,2);
            if(negative(amount)){ps2FileWorkerError(job_raw,amount);break;}
            result=ps2FileRpcSeek(sx(r(job+40)),position,0);
            if(negative(result)){ps2FileWorkerError(job_raw,result);break;}
            state(job,7);w(job+48,(uint32_t)amount);notify(job_raw,4,0,amount);break;
        }
        case 5:case 6:
            state(job,command==5?4:5);
            result=command==5?ps2FileRpcRead(sx(r(job+40)),sx(r(job+32)),sx(r(job+28))):
                              ps2FileRpcWrite(sx(r(job+40)),sx(r(job+32)),sx(r(job+28)));
            if(negative(result)){ps2FileWorkerError(job_raw,result);break;}
            w(job+48,r(job+48)+(uint32_t)result);state(job,7);
            notify(job_raw,command,sx(r(job+32)),result);break;
        case 7:
            state(job,6);result=ps2FileRpcClose(sx(r(job+40)));w(job+40,UINT32_MAX);
            if(negative(result)){ps2FileWorkerError(job_raw,result);break;}
            (void)ps2FileJobComplete(job_raw);state(job,8);notify(job_raw,7,0,0);break;
        case 8:case 9:
            state(job,2);
            result=ps2FileRpcOpen(sx(r(job+16)),command==8?1:0x202,command==8?0:sx(r(job+36)));
            if(negative(result)){ps2FileWorkerError(job_raw,result);break;}
            w(job+40,(uint32_t)result);amount=sx(r(job+28));
            if(command==8&&negative(amount)){
                state(job,3);amount=ps2FileRpcSeek(result,0,2);
                if(negative(amount)){ps2FileWorkerError(job_raw,amount);break;}
                result=ps2FileRpcSeek(sx(r(job+40)),0,0);
                if(negative(result)){ps2FileWorkerError(job_raw,result);break;}
            }
            if(amount){
                uint64_t buffer=sx(r(job+32));
                if(command==8){
                    if(!buffer)buffer=sx(ps2MemoryHandleAcquirePointer(ps2MemoryHandleAllocate(s32((uint32_t)amount))));
                    w(job+32,(uint32_t)buffer);state(job,4);
                    amount=ps2FileRpcRead(sx(r(job+40)),buffer,amount);
                }else{
                    state(job,5);amount=ps2FileRpcWrite(sx(r(job+40)),buffer,amount);
                }
                if(negative(amount)){ps2FileWorkerError(job_raw,amount);break;}
            }
            state(job,6);(void)ps2FileRpcClose(sx(r(job+40)));w(job+40,UINT32_MAX);
            (void)ps2FileJobComplete(job_raw);state(job,8);
            notify(job_raw,8,sx(r(job+32)),amount);
            (void)ps2KernelSignalSema(r(worker+4));break;
        default:break;
        }
    }
}

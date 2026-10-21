#include "script_file.h"
#include "file_device.h"
#include "file_worker_control.h"
#include "file_loader_support.h"
#include "memory_handle_allocation.h"
#include "material_lists.h"
#include "heap_queue.h"
#include "disc_platform.h"
#include "script_construction.h"
#include "script_process.h"
#include "libc_stream.h"
#include <string.h>
static uint32_t word(uint32_t a)
{ uint32_t v;memcpy(&v,nocturneResolveScriptFileAddress(a),4);return v; }
static void put(uint32_t a,uint32_t v)
{ memcpy(nocturneResolveScriptFileAddress(a),&v,4); }
static uint64_t sx(uint32_t v)
{ return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v; }
/* The native WaitSema/SignalSema wrappers preserve the full syscall V0. */
static uint64_t wait(void)
{ uint64_t args[]={sx(word(0x551924))};return nocturneDiscPlatformKernel(0x44,1,args); }
/* 002be328: comparisons use all 64 event bits; the stored result is a word. */
uint64_t ps2BlockingFileCompletion(uint64_t job,uint64_t event,uint64_t buffer,uint64_t result,uint64_t payload)
{
 (void)job;(void)buffer;(void)payload;
 if(event==3)put(0x552118,(uint32_t)result);
 else if(event==4)put(0x552114,(uint32_t)result);
 uint64_t args[]={sx(word(0x551924))};return nocturneDiscPlatformKernel(0x42,1,args);
}
/* 002be368: the request and retry calls execute even for a null job. */
uint64_t ps2BlockingFileOpen(uint64_t path)
{
 if(word(0x551924)&0x80000000u)put(0x551924,ps2CreateSemaphore(0,128,0));
 uint64_t job=ps2FileRequestRead(path,0x2be328,0);
 (void)wait();(void)ps2FileCommandRetry(job);return job;
}
/* 002be450 */
uint64_t ps2BlockingFileClose(uint64_t job)
{ (void)ps2FileCommandClose(job);(void)wait();return ps2FileJobReleaseIfTerminal(job); }
/* 002be480: return is WaitSema's result, not the read byte count. */
uint64_t ps2BlockingFileRead(uint64_t job,uint64_t buffer,uint64_t bytes)
{ (void)ps2FileCommandRead(job,buffer,bytes);return wait(); }
/* 002be4a0 */
uint64_t ps2BlockingFileSize(uint64_t job)
{ (void)ps2FileCommandSize(job);(void)wait();return sx(word(0x552114)); }
/* 002c3660: ADDU wraps the allocation size. Output stores retain their order. */
uint64_t sdfDevLoadFileEx(uint64_t path,uint64_t data_out,uint64_t size_out,uint64_t margin)
{
 uint64_t job=ps2BlockingFileOpen(path),size=ps2BlockingFileSize(job);
 uint32_t handle=ps2MemoryHandleAllocate((int32_t)((uint32_t)size+(uint32_t)margin));
 uint32_t data=ps2MemoryHandleAcquirePointer(handle);
 (void)ps2BlockingFileRead(job,sx(data),size);(void)ps2BlockingFileClose(job);
 if(data_out)put((uint32_t)data_out,data);else (void)ps2MemoryHandleReleasePointer(handle);
 if(size_out)put((uint32_t)size_out,(uint32_t)size);
 return sx(handle);
}
/* 002c3718 */
uint64_t sdfDevLoadFile(uint64_t path,uint64_t data_out,uint64_t size_out)
{ return sdfDevLoadFileEx(path,data_out,size_out,0); }
/* 00109c58: a failed construction retains the allocated file handle. */
uint64_t scrAddScript3(uint64_t path,uint64_t start)
{
 uint32_t data;
#if UINTPTR_MAX > UINT32_MAX
 uint32_t local=nocturneLibcStreamLocalAddress(&data,4);
#else
 uint32_t local=(uint32_t)(uintptr_t)&data;
#endif
 uint64_t handle=sdfDevLoadFile(path,sx(local),0);
#if UINTPTR_MAX > UINT32_MAX
 nocturneLibcStreamEndLocal();
#endif
 uint64_t work=data?scrAddScript2(sx(data),start):0;
 if(work)put((uint32_t)work+0xd8,(uint32_t)handle);
 return work;
}
/* 00109d48: original startup does not guard a failed AddScript3. */
uint64_t scrStartScript3(uint64_t priority,uint64_t path,uint64_t start)
{ return scrStartScriptProcess(priority,scrAddScript3(path,start)); }

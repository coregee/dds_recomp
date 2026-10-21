#include "process_shutdown.h"
#include "process_lists.h"
#include "heap_queue.h"
#include "material_construction_release.h"
#include <string.h>
static uint32_t r32(uint32_t address)
{ uint32_t v;memcpy(&v,nocturneResolveProcessShutdownAddress(address),4);return v; }
static uint32_t r16(uint32_t address)
{ uint16_t v;memcpy(&v,nocturneResolveProcessShutdownAddress(address),2);return v; }
static void w32(uint32_t address,uint32_t value)
{ memcpy(nocturneResolveProcessShutdownAddress(address),&value,4); }
static void w16(uint32_t address,uint32_t value)
{ uint16_t v=(uint16_t)value;memcpy(nocturneResolveProcessShutdownAddress(address),&v,2); }
static uint64_t sx32(uint32_t value)
{ return value&UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000)|value : value; }
/* 00101b80: raw full-lane equality against sign-extended sibling pointers. */
void dds3UnlinkProcess(uint64_t process)
{
    uint32_t p=(uint32_t)process,parent=r32(p+0x44);
    if(!parent)return;
    uint32_t child=r32(parent+0x48);
    if(sx32(child)==process)w32(parent+0x48,r32(p+0x4c));
    else{
        uint32_t next=r32(child+0x4c);
        while(sx32(next)!=process){child=next;next=r32(child+0x4c);}
        w32(child+0x4c,r32(p+0x4c));
    }
    w32(p+0x4c,0);w32(p+0x44,0);
}
/* 00100d70: preserve the sibling before the actual recursive kill. */
void dds3KillProcessNow(uint64_t process)
{
    uint32_t p=(uint32_t)process,child=r32(p+0x48);
    while(child){
        uint32_t next=r32(child+0x4c);
        (void)dds3KillProcess(sx32(child),0);child=next;
    }
    dds3DeleteProcessList(process);
    nocturneProcessDiagnostic(UINT32_C(0x52dd18),process);
    uint32_t callback=r32(p+0x34);
    if(callback)nocturneProcessShutdownCallback(callback,process);
    w32(p+0x1c,r32(p+0x1c)&UINT32_C(0xfffffff0));
    dds3UnlinkProcess(process);ps2PoolRelease(p);
}
/* 00100e08: only states1/2 enter the ending list. */
void dds3EndProcess(uint64_t process)
{
    uint32_t p=(uint32_t)process,state=r32(p+0x1c)&15;
    if(state==0 || state>=3)return;
    dds3DeleteProcessList(process);
    w32(p+0x1c,(r32(p+0x1c)&UINT32_C(0xfffffff0))|3);
    dds3AddProcessList(process);
    if(r16(p+0x2e)==0)dds3KillProcessNow(process);
}
/* 00101738: sentinels use full64 equality, delay stores truncate16. */
uint64_t dds3KillProcess(uint64_t process,uint64_t delay)
{
    if(process==0 || process==UINT64_MAX)return 0;
    uint32_t p=(uint32_t)process,state=r32(p+0x1c)&15;
    if(state==1 || state==2){w16(p+0x2e,(uint32_t)delay);dds3EndProcess(process);return 1;}
    if(state==3){
        w16(p+0x2e,(uint32_t)delay);
        if(((uint32_t)delay&65535)==0)dds3KillProcessNow(process);
        return 1;
    }
    return 0;
}
/* 00100e80: next saved before release, negative halfword delays untouched. */
void dds3EndingProcesses(void)
{
    uint32_t p=r32(UINT32_C(0x54e85c));
    while(p){
        uint32_t delay=r16(p+0x2e);
        if(delay>0 && delay<32768)w16(p+0x2e,delay-1);
        uint32_t next=r32(p+0x3c);
        if(r16(p+0x2e)==0)dds3KillProcessNow(sx32(p));
        p=next;
    }
}
/* 002ab8f0: SDK deferred queue, not immediate texture destruction. */
void ps2TextureDeferredRelease(uint64_t texture)
{ ps2DeferredQueueAppend(UINT32_C(0x5520a0),(uint32_t)texture); }
/* 001eaf08: reload each next handle after the preceding actual append. */
void ps2MoonShutdown(uint64_t process)
{
    uint32_t data=(uint32_t)dds3GetProcessData(process);
    for(uint32_t k=0;k<6;k++){
        uint32_t handle=r32(data+k*4);
        if(handle)ps2TextureDeferredRelease(sx32(handle));
    }
    ps2PoolRelease(data);w32(UINT32_C(0x54f76c),0);
}

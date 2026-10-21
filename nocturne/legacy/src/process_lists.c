#include "process_lists.h"
#include <string.h>
static uint32_t r32(uint32_t address)
{ uint32_t value; memcpy(&value,nocturneResolveProcessAddress(address),4); return value; }
static uint32_t r16(uint32_t address)
{ uint16_t value; memcpy(&value,nocturneResolveProcessAddress(address),2); return value; }
static void w32(uint32_t address,uint32_t value)
{ memcpy(nocturneResolveProcessAddress(address),&value,4); }
static void w16(uint32_t address,uint32_t value)
{ uint16_t word=(uint16_t)value; memcpy(nocturneResolveProcessAddress(address),&word,2); }
static uint32_t root(uint32_t state)
{ return state==1 ? UINT32_C(0x54e850) : state==2 ? UINT32_C(0x54e868) : UINT32_C(0x54e85c); }
/* 001005e8: three lists, head/tail/count; unlink before clearing this node. */
void dds3DeleteProcessList(uint64_t process)
{
    uint32_t p=(uint32_t)process,flags=r32(p+0x1c),state=flags&15;
    if(state==0 || state>3)return;
    uint32_t list=root(state),previous=r32(p+0x40);
    if(previous)w32(previous+0x3c,r32(p+0x3c));
    else w32(list,r32(p+0x3c));
    uint32_t next=r32(p+0x3c);
    if(next)w32(next+0x40,r32(p+0x40));
    else { w32(list+4,r32(p+0x40)); flags=r32(p+0x1c); }
    w32(p+0x40,0); w32(p+0x3c,0);
    state=flags&15;
    if(state>=1 && state<=3){ list=root(state); w32(list+8,r32(list+8)-1); }
}
/* 00100760: ascending unsigned priority, insert after all equal priorities. */
void dds3AddProcessList(uint64_t process)
{
    uint32_t p=(uint32_t)process,flags=r32(p+0x1c),state=flags&15;
    if(state==0 || state>3)return;
    uint32_t list=root(state),current=r32(list);
    if(!current){
        w32(list,p); w32(list+4,p); flags=r32(p+0x1c);
        w32(p+0x3c,0); w32(p+0x40,0);
    }else{
        uint32_t priority=r32(p+0x20);
        while(priority>=r32(current+0x20)){
            current=r32(current+0x3c); if(!current)break;
        }
        if(current){
            uint32_t previous=r32(current+0x40);
            if(previous){
                w32(previous+0x3c,p);
                uint32_t reloaded=r32(current+0x40);
                w32(p+0x3c,current); w32(p+0x40,reloaded); w32(current+0x40,p);
            }else{
                w32(list,p); flags=r32(p+0x1c);
                w32(p+0x40,0); w32(p+0x3c,current); w32(current+0x40,p);
            }
        }else{
            uint32_t tail=r32(list+4); flags=r32(p+0x1c);
            w32(tail+0x3c,p); w32(p+0x40,tail); w32(list+4,p); w32(p+0x3c,0);
        }
    }
    state=flags&15;
    if(state>=1 && state<=3){ list=root(state); w32(list+8,r32(list+8)+1); }
}
/* 001009a0: actual unlink/reinsert; retain high flag bits, clear two clocks. */
void dds3StartReadyProcess(uint64_t process)
{
    uint32_t p=(uint32_t)process;
    dds3DeleteProcessList(process);
    w32(p+0x1c,(r32(p+0x1c)&UINT32_C(0xfffffff0))|2);
    dds3AddProcessList(process);
    w32(p+0x24,0); w32(p+0x28,0);
}
/* 001009e8: save next before moving zero-delay nodes out of the start list. */
void dds3StartingProcesses(void)
{
    uint32_t p=r32(UINT32_C(0x54e850));
    while(p){
        uint32_t delay=r16(p+0x2c);
        if(delay>0 && delay<UINT32_C(0x8000))w16(p+0x2c,delay-1);
        uint32_t next=r32(p+0x3c);
        if(r16(p+0x2c)==0){
            uint64_t argument=p&UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000)|p : p;
            dds3StartReadyProcess(argument);
        }
        p=next;
    }
}
/* 00101aa8 / 00101ab0: SW truncates; LW sign-extends into the full V0 lane. */
void dds3SetProcessData(uint64_t process,uint64_t data)
{ w32((uint32_t)process+0x38,(uint32_t)data); }
uint64_t dds3GetProcessData(uint64_t process)
{
    uint32_t value=r32((uint32_t)process+0x38);
    return value&UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000)|value : value;
}

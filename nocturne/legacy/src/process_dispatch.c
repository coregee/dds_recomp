#include "process_dispatch.h"
#include "process_shutdown.h"
#include <string.h>
static uint32_t r32(uint32_t address)
{ uint32_t v;memcpy(&v,nocturneResolveProcessDispatchAddress(address),4);return v; }
static uint32_t r8(uint32_t address)
{ return *(uint8_t *)nocturneResolveProcessDispatchAddress(address); }
static void w32(uint32_t address,uint32_t value)
{ memcpy(nocturneResolveProcessDispatchAddress(address),&value,4); }
static void w8(uint32_t address,uint32_t value)
{ *(uint8_t *)nocturneResolveProcessDispatchAddress(address)=(uint8_t)value; }
static uint64_t sx32(uint32_t value)
{ return value&UINT32_C(0x80000000) ? UINT64_C(0xffffffff00000000)|value : value; }
/* 00100a48: prepare controller state before invoking the raw callback. */
uint64_t dds3RunProcess(uint64_t process)
{
    uint32_t p=(uint32_t)process,flags=r32(p+0x1c);
    if(flags&0x20)return 1;
    w32(UINT32_C(0x54e874),p);
    for(uint32_t port=0;port<2;port++){
        for(uint32_t k=0;k<16;k++){
            uint32_t index=port*16+k,a=0,b=0;
            if(!(flags&0x10)){
                a=r8(UINT32_C(0x2f57d0)+index);
                b=r8(UINT32_C(0x2f57f0)+index);
            }
            w8(UINT32_C(0x2f5810)+index,a);
            w8(UINT32_C(0x2f5830)+index,b);
        }
        for(uint32_t k=0;k<2;k++){
            uint32_t index=port*4+k*2,a=0,b=0,c=0;
            if(!(flags&0x10)){
                a=r8(UINT32_C(0x54e8f8)+index);
                b=r8(UINT32_C(0x54e8f9)+index);
                c=r8(UINT32_C(0x54e900)+port*2+k);
                w8(UINT32_C(0x54e908)+index,a);
                w8(UINT32_C(0x54e909)+index,b);
                w8(UINT32_C(0x54e910)+port*2+k,c);
            }else{
                w8(UINT32_C(0x54e908)+index,0);
                w8(UINT32_C(0x54e910)+port*2+k,0);
                w8(UINT32_C(0x54e909)+index,0);
            }
        }
    }
    uint32_t callback=r32(p+0x30);
    if(callback && callback!=UINT32_MAX){
        uint64_t result=nocturneProcessRunCallback(callback,process);
        if(result)w32(p+0x30,(uint32_t)result);
        if(result==UINT64_MAX && (r32(p+0x1c)&15)==2){
            dds3EndProcess(process);w32(UINT32_C(0x54e874),0);return 0;
        }
    }
    w32(p+0x28,r32(p+0x28)+1);
    w32(UINT32_C(0x54e874),0);return 1;
}
static uint32_t advance(uint32_t current,uint32_t head)
{
    uint32_t previous=r32(current+0x40);
    if(dds3RunProcess(sx32(current)))return r32(current+0x3c);
    return previous ? r32(previous+0x3c) : r32(head);
}
/* 00100c48: merge active/ending priorities; active runs first on ties.
   Once one side is exhausted, the original drains only the other side. */
void dds3RunningProcess(void)
{
    uint32_t active=r32(UINT32_C(0x54e868)),ending=r32(UINT32_C(0x54e85c));
    while(active && ending){
        if(r32(ending+0x20)<r32(active+0x20))ending=advance(ending,UINT32_C(0x54e85c));
        else active=advance(active,UINT32_C(0x54e868));
    }
    if(active){
        do{active=advance(active,UINT32_C(0x54e868));}while(active);
    }else{
        while(ending)ending=advance(ending,UINT32_C(0x54e85c));
    }
}

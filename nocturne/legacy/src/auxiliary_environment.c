/* Reconstructed original auxiliary draw-environment callback. */
#include "auxiliary_environment.h"
#include <string.h>
#include "heap_queue.h"
static uint32_t get32(uint32_t a){uint32_t v;memcpy(&v,nocturneResolveHeapAddress(a),4);return v;}
static uint32_t get8(uint32_t a){uint8_t v;memcpy(&v,nocturneResolveHeapAddress(a),1);return v;}
static uint32_t signed16(uint32_t a){uint16_t v;memcpy(&v,nocturneResolveHeapAddress(a),2);return(uint32_t)v|((v&0x8000)?UINT32_C(0xffff0000):0);}
static uint64_t sx32(uint32_t v){return(uint64_t)v|((v&UINT32_C(0x80000000))?UINT64_C(0xffffffff00000000):0);}
static uint32_t asr32(uint32_t v,unsigned n){return(v>>n)|((v&UINT32_C(0x80000000))?(UINT32_MAX<<(32-n)):0);}
static void put64(uint32_t a,uint64_t v){memcpy(nocturneResolveHeapAddress(a),&v,8);}
void ps2DrawUpdateAuxiliaryEnvironmentRecord(uint32_t record,uint32_t index)
{
    uint32_t context=get32(record+92),cfg=get32(record+80),upper=get32(record+84);
    uint32_t fb=get32(get32(cfg+(index<<2)+8)+12);
    uint32_t width=signed16(cfg),format=get8(cfg+6);
    uint64_t first=((uint64_t)upper<<32)|(fb>>11)|(sx32(asr32(width+63,6))<<16)|sx32(format<<24);
    uint32_t depthSlice=get32(cfg+16);
    put64(record+56,context?77:76);
    uint32_t depth=get32(depthSlice+12);
    put64(record+48,first);
    uint32_t depthFormat=get8(cfg+7);
    put64(record+72,context?79:78);
    put64(record+64,(depth>>11)|sx32(depthFormat<<24));
}

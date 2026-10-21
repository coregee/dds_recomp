#include "pac_compression.h"
#include "material_fiveword_pool.h"
#include "memory_handle_allocation.h"
#include "ps2_memory.h"
#include <string.h>
static uint8_t *at(uint32_t address)
{
#if UINTPTR_MAX > UINT32_MAX
    return nocturneResolvePacCompressionAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint32_t r16(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void w16(uint32_t a,uint32_t v){uint16_t n=(uint16_t)v;memcpy(at(a),&n,2);}
static uint64_t sx(uint32_t v){return v&0x80000000?UINT64_C(0xffffffff00000000)|v:v;}
static int less(uint64_t a,uint64_t b){return (a^UINT64_C(0x8000000000000000))<(b^UINT64_C(0x8000000000000000));}
uint64_t ps2MemoryHandleAllocateHigh(uint64_t size)
{
    uint64_t rounded=sx(((uint32_t)size+127)&0xffffff80);
    uint32_t enabled=ps2KernelDisableInterrupts(),node=r32(0x577f28),gap;
    for(;;){
        uint32_t state=r16(node+12);
        if(!state){
            gap=r32(r32(node+4)+8)-r32(node+8);
            if(!less(sx(gap),rounded))break;
        }else if(state==2 && enabled)ps2KernelEnableInterrupts();
        node=r32(node);
    }
    if(less(rounded,sx(gap))){
        uint32_t allocated=ps2PoolAllocate(16),delta=gap-(uint32_t)rounded;
        w32(allocated,node);uint32_t data=r32(node+8),next=r32(node+4);
        w16(allocated+12,0);w32(allocated+4,next);w32(allocated+8,data+delta);
        next=r32(node+4);w16(allocated+14,0);w32(next,allocated);w32(node+4,allocated);node=allocated;
    }
    w16(node+12,1);if(enabled)ps2KernelEnableInterrupts();return sx(node);
}
void ps2MemoryHandleClearSlot(uint64_t slot)
{uint32_t address=(uint32_t)slot,handle=r32(address);if(handle){w32(address,0);ps2MemoryHandleFree(handle);}}
void ps2PacCompressionInitialize(uint64_t work,uint64_t destination)
{uint32_t p=(uint32_t)work;w32(p+4,(uint32_t)destination);*at(p)=1;}
static void copy(uint32_t dst,uint32_t src,uint32_t n)
{ps2Memcpy(n?at(dst):NULL,n?at(src):NULL,n);}
static void fill(uint32_t dst,uint32_t value,uint32_t n)
{ps2Memset(n?at(dst):NULL,(int32_t)value,n);}
/* All ten states, including the two-stage distance and interleaved-zero copy.
 * Original malformed zero-length do-loops/unknown-state loops remain unchecked. */
uint64_t ps2PacCompressionDecode(uint64_t work,uint64_t input,uint64_t count)
{
    uint32_t p=(uint32_t)work,src=(uint32_t)input;
    if(!*at(p))return 1;
    w32(0x552170,0);uint32_t dst=r32(p+4);uint64_t left=count;
    while(less(0,left)){
        uint32_t state=*at(p);
        switch(state){
        case 1:{
            uint32_t index=r32(0x552170);left=sx((uint32_t)left-1);
            w32(0x594780+index*4,src);w32(0x552170,(index+1)&15);
            uint32_t command=*at(src++);
            if(command>=0xe0){if(command==255){w32(p+4,dst);w32(p+8,src);w32(p+12,(uint32_t)left);*at(p)=0;return 1;}}
            else{*at(p+1)=(uint8_t)(command&0xe0);if(!(command&31))*at(p)=2;else{w16(p+2,command&31);*at(p)=4;}}
            break;}
        case 2:{uint32_t value=*at(src++);left=sx((uint32_t)left-1);w16(p+2,value);*at(p)=3;break;}
        case 3:{uint32_t high=*at(src++),length=r16(p+2);*at(p)=4;left=sx((uint32_t)left-1);w16(p+2,length|(high<<8));break;}
        case 4:{
            uint32_t kind=*at(p+1);
            if(kind==0)*at(p)=5;
            else if(kind==0x20){uint32_t n=r16(p+2),old=dst;dst+=n;fill(old,0,n);*at(p)=1;}
            else if(kind==0x40)*at(p)=6;
            else if(kind==0x60)*at(p)=7;
            else if(kind==0x80)*at(p)=8;
            else if(kind==0xa0)*at(p)=10;
            break;}
        case 5:{
            uint32_t n=r16(p+2);if(less(left,n))n=(uint32_t)left;
            uint32_t old=dst;dst+=n;copy(old,src,n);
            uint32_t remaining=r16(p+2)-n;src+=n;left=sx((uint32_t)left-n);w16(p+2,remaining);
            if(!(remaining&65535))*at(p)=1;break;}
        case 6:{
            uint32_t n=r16(p+2),old=dst,value=*at(src++);dst+=n;fill(old,value,n);
            left=sx((uint32_t)left-1);*at(p)=1;break;}
        case 7:{
            uint32_t offset=*at(src++),n=r16(p+2);left=sx((uint32_t)left-1);uint32_t previous=dst-offset;
            do{uint32_t value=*at(previous++);--n;*at(dst++)=(uint8_t)value;}while(n);
            *at(p)=1;break;}
        case 8:{
            uint32_t value=*at(src++);left=sx((uint32_t)left-1);*at(p+16)=(uint8_t)value;
            if(!left){*at(p)=9;break;}
            /* The original falls through even when a raw high lane makes the
             * first decrement negative; only exact64 zero waits for state9. */
            uint32_t high=*at(src++),low=*at(p+16);left=sx((uint32_t)left-1);
            uint32_t n=r16(p+2),previous=dst-(low|(high<<8));
            do{value=*at(previous++);--n;*at(dst++)=(uint8_t)value;}while(n);
            *at(p)=1;break;}
        case 9:{
            uint32_t high=*at(src++),low=*at(p+16);left=sx((uint32_t)left-1);
            uint32_t n=r16(p+2),previous=dst-(low|(high<<8));
            do{uint32_t value=*at(previous++);--n;*at(dst++)=(uint8_t)value;}while(n);
            *at(p)=1;break;}
        case 10:{
            uint32_t n=r16(p+2);
            if(less(left,n)){n=(uint32_t)left;left=0;w16(p+2,r16(p+2)-n);}
            else{w16(p+2,0);*at(p)=1;left=sx((uint32_t)left-n);}
            do{uint32_t value=*at(src++);--n;*at(dst++)=(uint8_t)value;*at(dst++)=0;}while(n);
            break;}
        default:break;
        }
    }
    w32(p+4,dst);w32(p+8,src);w32(p+12,(uint32_t)left);return 0;
}

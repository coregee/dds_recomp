/* Original retail libmc callbacks. Source count fields are reread after each
 * copied byte, preserving native overlap behavior rather than using memcpy. */
#include "sdk_memory_card_callbacks.h"
#include <string.h>
static uint8_t *at(uint32_t a){return nocturneResolveSdkMemoryCardAddress(a);}
static uint32_t r32(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void w32(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static int32_t si(uint32_t v){return v<=INT32_MAX?(int32_t)v:-1-(int32_t)(UINT32_MAX-v);}
void ps2McReadFixAlign_002CE330(uint64_t reply)
{
    uint32_t base=(uint32_t)reply|0x20000000u,n=r32(base);
    if(n){
        uint32_t dst=r32(base+8u);
        if(si(n)>0){
            uint32_t i=0;
            do{*at(dst)=*at(base+16u+i);++i;++dst;}while(si(i)<si(r32(base)));
        }
    }
    n=r32(base+4u);
    if(n){
        uint32_t dst=r32(base+12u);
        if(si(n)>0){
            uint32_t i=0;
            do{*at(dst)=*at(base+80u+i);++i;++dst;}while(si(i)<si(r32(base+4u)));
        }
    }
}
void ps2McGetInfoApdx_002CE7B0(uint64_t reply)
{
    uint32_t base=(uint32_t)reply|0x20000000u,dst=r32(0x599768u);
    if(dst)w32(dst,r32(base));
    dst=r32(0x59976cu);
    if(dst)w32(dst,r32(base+4u));
    dst=r32(0x599770u);
    if(dst)w32(dst,r32(base+144u));
}

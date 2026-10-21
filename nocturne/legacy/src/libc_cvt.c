/* 002d7ce8: original formatting wrapper, including raw64 character tests.
 * Padding writes exactly the counted bytes; it does not append a new NUL. */
#include "libc_cvt.h"
#include "libc_dtoa.h"
#include "libc_stream.h"
#include "heap_queue.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveHeapAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx(uint32_t v){return (uint64_t)((int64_t)v-((v>>31)?INT64_C(4294967296):0));}
uint64_t ps2LibcCvt(uint64_t context,uint64_t bits,uint64_t precision,
    uint64_t flags,uint64_t signByte,uint64_t decimalPoint,
    uint64_t format,uint64_t length)
{
    uint64_t mode=3;
    uint32_t scratch[2],guestScratch;
    if(format!='f'){
        mode=2;
        if(format=='e'||format=='E')precision=sx((uint32_t)precision+1);
    }
    if(bits>>63){bits=ps2SoftDoubleSub(0,bits);*at((uint32_t)signByte)='-';}
    else *at((uint32_t)signByte)=0;
#if UINTPTR_MAX > UINT32_MAX
    guestScratch=nocturneLibcStreamLocalAddress(scratch,sizeof(scratch));
#else
    guestScratch=(uint32_t)(uintptr_t)scratch;
#endif
    uint64_t result=ps2LibcDtoa(context,bits,mode,precision,decimalPoint,
        guestScratch,guestScratch+4);
#if UINTPTR_MAX > UINT32_MAX
    nocturneLibcStreamEndLocal();
#endif
    uint32_t digits=(uint32_t)result,end=scratch[1];
    if((format!='g'&&format!='G')||(flags&1)){
        uint32_t target=digits+(uint32_t)precision;
        if(format=='f'){
            if((int8_t)*at(digits)=='0'&&ps2SoftDoubleCompare(bits,0)!=0)
                put((uint32_t)decimalPoint,1-(uint32_t)precision);
            target+=word((uint32_t)decimalPoint);
        }
        if(ps2SoftDoubleCompare(bits,0)==0)end=target;
        while(end<target)*at(end++)='0';
    }
    put((uint32_t)length,end-digits);
    return result;
}

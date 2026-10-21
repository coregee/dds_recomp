/* Complete original __sfvwrite and __sprint bodies. Counts and pointers in
 * descriptors are guest words; callback results retain their raw EE width. */
#include "libc_vector.h"
#include "libc_stream.h"
#include "ps2_memory.h"
#include "ps2_sdk_frontier.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveLibcStreamAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void putHalf(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static int positive(uint64_t v){return v&&!(v>>63);}
static void copy(uint32_t out,uint32_t in,uint32_t n){
    if(n)(void)ps2Memmove(at(out),at(in),n);
    else (void)ps2Memmove((void *)(uintptr_t)out,(const void *)(uintptr_t)in,0);
}
static uint64_t search(uint32_t input,uint32_t n){
    if(!n){(void)ps2Memchr(NULL,10,0);return 0;}
    const uint8_t *p=at(input),*found=ps2Memchr(p,10,n);
    return found?sx(input+(uint32_t)(found-p)):0;
}
static uint64_t writeCallback(uint32_t p,uint64_t input,uint64_t count){
    uint32_t cb=word(p+36);uint64_t cookie=sx(word(p+28));
#if UINTPTR_MAX > UINT32_MAX
    uint64_t args[3]={cookie,input,count};return nocturneLibcStreamCallback(cb,3,args);
#else
    return ((uint64_t (*)(uint64_t,uint64_t,uint64_t))(uintptr_t)cb)(cookie,input,count);
#endif
}
static uint64_t failed(uint32_t p){putHalf(p+12,(uint16_t)(half(p+12)|0x40));return UINT64_MAX;}
static void nextVector(uint32_t *next,uint64_t *input,uint64_t *remaining){
    do{*remaining=sx(word(*next+4));*input=sx(word(*next));*next+=8;}while(!*remaining);
}
static int consume(uint32_t u,uint64_t count,uint64_t *input,uint64_t *remaining){
    uint32_t residual=word(u+8);*input=sx((uint32_t)*input+(uint32_t)count);*remaining=sx((uint32_t)*remaining-(uint32_t)count);
    residual-=(uint32_t)count;put(u+8,residual);return residual!=0;
}
uint64_t ps2LibcWriteVectors(uint64_t stream,uint64_t vectors){
    uint32_t p=(uint32_t)stream,u=(uint32_t)vectors;if(!word(u+8))return 0;
    uint16_t flags=half(p+12);
    if(!(flags&8)||!word(p+16)){if(ps2LibcPrepareWrite(stream))return UINT64_MAX;flags=half(p+12);}
    uint32_t next=word(u);uint64_t input=0,remaining=0;
    if(flags&2){
        for(;;){
            if(!remaining)nextVector(&next,&input,&remaining);
            uint64_t count=remaining<1025?remaining:1024;
            count=writeCallback(p,input,count);if(!positive(count))return failed(p);
            if(!consume(u,count,&input,&remaining))return 0;
        }
    }
    if(!(flags&1)){
        for(;;){
            if(!remaining)nextVector(&next,&input,&remaining);
            uint64_t count=sx(word(p+8));uint32_t output=word(p);
            if(flags&0x200){
                if(remaining<count)count=remaining;copy(output,(uint32_t)input,(uint32_t)count);
                uint32_t writable=word(p+8),cursor=word(p);writable-=(uint32_t)count;cursor+=(uint32_t)count;
                count=remaining;put(p+8,writable);put(p,cursor);
            }else{
                uint64_t base=sx(word(p+16));
                if(base<sx(output)&&count<remaining){
                    copy(output,(uint32_t)input,(uint32_t)count);put(p,word(p)+(uint32_t)count);
                    if(ps2LibcFlush(stream))return failed(p);
                }else{
                    count=sx(word(p+20));
                    if(remaining<count){
                        count=remaining;copy(output,(uint32_t)input,(uint32_t)count);
                        uint32_t writable=word(p+8),cursor=word(p);put(p+8,writable-(uint32_t)count);put(p,cursor+(uint32_t)count);
                    }else{count=writeCallback(p,input,count);if(!positive(count))return failed(p);}
                }
            }
            if(!consume(u,count,&input,&remaining))return 0;flags=half(p+12);
        }
    }
    uint64_t line=0;int cached=0;
    for(;;){
        if(!remaining){cached=0;nextVector(&next,&input,&remaining);}
        if(!cached){uint64_t hit=search((uint32_t)input,(uint32_t)remaining);line=hit?sx((uint32_t)hit-(uint32_t)input+1):sx((uint32_t)remaining+1);cached=1;}
        uint32_t output=word(p);uint64_t available=remaining<line?remaining:line;
        uint64_t base=sx(word(p+16)),writable=sx(word(p+8)),size=sx(word(p+20));uint64_t count=sx((uint32_t)writable+(uint32_t)size);
        if(base<sx(output)&&(int64_t)count<(int64_t)available){
            copy(output,(uint32_t)input,(uint32_t)count);put(p,word(p)+(uint32_t)count);
            uint64_t flush=ps2LibcFlush(stream);line=sx((uint32_t)line-(uint32_t)count);if(flush)return failed(p);
        }else{
            count=size;
            if((int64_t)available<(int64_t)count){
                count=available;copy(output,(uint32_t)input,(uint32_t)count);
                uint32_t w=word(p+8),cursor=word(p);put(p+8,w-(uint32_t)count);put(p,cursor+(uint32_t)count);
            }else{
                count=writeCallback(p,input,count);line=sx((uint32_t)line-(uint32_t)count);if(!positive(count))return failed(p);
                goto lineUpdated;
            }
            line=sx((uint32_t)line-(uint32_t)count);
        }
lineUpdated:
        if(!line){if(ps2LibcFlush(stream))return failed(p);cached=0;}
        if(!consume(u,count,&input,&remaining))return 0;
    }
}
uint64_t ps2LibcSprint(uint64_t stream,uint64_t vectors){
    uint32_t u=(uint32_t)vectors;uint64_t result=0;
    if(word(u+8)){result=ps2LibcWriteVectors(stream,vectors);put(u+4,0);put(u+8,0);}
    else put(u+4,0);return result;
}
uint64_t ps2LibcFormatExponent(uint64_t output,uint64_t exponent,uint64_t marker){
    uint32_t p=(uint32_t)output,cursor=p+2;*at(p)=(uint8_t)marker;
    if(exponent>>63){*at(p+1)=45;exponent=sx(0-(uint32_t)exponent);}else *at(p+1)=43;
    if((int64_t)exponent<10){*at(cursor++)=48;*at(cursor++)=(uint8_t)((uint32_t)exponent+48);}
    else{
        uint8_t digits[16];unsigned n=0;
        do{
            int32_t value=(int32_t)(uint32_t)exponent;int32_t quotient=value/10,remainder=value%10;
            digits[n++]=(uint8_t)((uint32_t)remainder+48);exponent=sx((uint32_t)quotient);
        }while((int64_t)exponent>=10);
        digits[n++]=(uint8_t)((uint32_t)exponent+48);
        while(n)*at(cursor++)=digits[--n];
    }
    return sx(cursor-p);
}

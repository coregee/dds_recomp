/* Complete original stream adapters, console transport, ring and kernel packets. */
#include "libc_console.h"
#include "libc_stream.h"
#include "sdk_debug.h"
#include "material_fiveword_pool.h"
#include "draw_consumer_support.h"
#include <string.h>
static uint8_t *at(uint32_t a){
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveLibcConsoleAddress(a);
#else
    return (uint8_t *)(uintptr_t)a;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void putHalf(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static uint64_t sx(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint64_t sxHalf(uint16_t v){return sx(v&0x8000u?0xffff0000u|v:v);}
static uint64_t sxByte(uint8_t v){return sx(v&128?0xffffff00u|v:v);}
static int negative(uint64_t v){return (int)(v>>63);}
uint64_t ps2ConsoleRegisterCommand(uint64_t service,uint64_t context,uint64_t callback){
    uint32_t packet[4]={(uint16_t)service,(uint32_t)context,(uint32_t)callback,0x2059eca8};
    return ps2KernelCommandRaw(1,packet);
}
uint64_t ps2ConsoleSendCommand(uint64_t channel,uint64_t command){
    uint32_t packet[2]={(uint32_t)channel,(uint32_t)sxByte((uint8_t)command)};
    return ps2KernelCommandRaw(3,packet);
}
uint64_t ps2ConsolePollCommand(uint64_t channel){uint32_t packet=(uint32_t)channel;return ps2KernelCommandRaw(4,&packet);}
uint64_t ps2ConsoleReceiveBytes(uint64_t channel,uint64_t buffer,uint64_t count){
    uint32_t packet[3]={(uint32_t)channel,(uint32_t)buffer,(uint16_t)count};return ps2KernelCommandRaw(UINT64_C(0xfffffffffffffffb),packet);
}
uint64_t ps2ConsoleSendBytes(uint64_t channel,uint64_t buffer,uint64_t count){
    uint32_t packet[3]={(uint32_t)channel,(uint32_t)buffer,(uint16_t)count};return ps2KernelCommandRaw(UINT64_C(0xfffffffffffffffa),packet);
}
uint64_t ps2ConsoleRingInitialize(uint64_t capacity){
    put(0x59b580,(uint32_t)capacity);put(0x59b588,0x59b590);put(0x59b584,0);put(0x59b58c,0x59b590);return 0x59b580;
}
void ps2ConsoleRingProduce(uint64_t ring){
    uint32_t p=(uint32_t)ring,n=word(p+4),cursor=word(p+12),capacity=word(p);n++;cursor++;
    put(p+4,n);uint32_t end=p+capacity+16;put(p+12,cursor);if(cursor==end)put(p+12,p+16);
}
void ps2ConsoleRingConsume(uint64_t ring){
    uint32_t p=(uint32_t)ring,n=word(p+4),cursor=word(p+8),capacity=word(p);n--;cursor++;
    put(p+4,n);uint32_t end=p+capacity+16;put(p+8,cursor);if(cursor==end)put(p+8,p+16);
}
uint64_t ps2ConsoleInitialize(void){
    (void)ps2KernelFlushCache(0);uint64_t value=ps2ConsoleRegisterCommand(0x210,0x59b690,0x2dcfa8);put(0x59b690,(uint32_t)value);
    if(word(0x59b690)&0x80000000u)return 0;
    put(0x59b69c,0);put(0x59b694,0);put(0x59b698,0);put(0x59b6a4,0x2059b800);put(0x59b6a0,0x2059b6c0);
    putHalf(0x2059b6c4,0x210);*at(0x2059b6c6)=0x45;*at(0x2059b6c7)=0x48;put(0x2059b6c8,0);putHalf(0x2059b6c2,0);
    value=ps2ConsoleRingInitialize(256);put(0x59b6a8,(uint32_t)value);return 1;
}
uint64_t ps2ConsoleWrite(uint64_t buffer,uint64_t count){
    if(word(0x59b69c))return UINT64_MAX;
    uint32_t p=(uint32_t)buffer,left=(uint32_t)count,output=0x2059b6cc,bytes=0,consumed=0;
    (void)ps2KernelDisableInterrupts();put(0x59b69c,1);put(0x59b6a0,0x2059b6c0);
    for(;;){
        left--;if(left==0xffffffffu)break;
        uint8_t c=*at(p);
        if(c==10){*at(output)=13;bytes++;output++;if(bytes==256)break;c=*at(p);}
        *at(output)=c;bytes++;p++;output++;consumed++;if(bytes==256)break;
    }
    put(0x59b694,bytes+12);uint32_t size=word(0x59b694);uint64_t command=sxByte(*at(0x2059b6c7)),channel=sx(word(0x59b690));
    putHalf(0x2059b6c0,(uint16_t)size);uint64_t result=ps2ConsoleSendCommand(channel,command);
    if(negative(result)){put(0x59b69c,0);(void)ps2KernelEnableInterrupts();return UINT64_MAX;}
    while(word(0x59b69c)) (void)ps2ConsolePollCommand(sx(word(0x59b690)));
    (void)ps2KernelEnableInterrupts();return sx(consumed);
}
uint64_t ps2ConsoleRead(uint64_t buffer,uint64_t count){
    uint32_t p=(uint32_t)buffer,n=0;if(!count||negative(count))return 0;
    for(;;){
        uint32_t next=n+1,ring=word(0x59b6a8),out=p+n;
        for(;;){
#if UINTPTR_MAX > UINT32_MAX
            uint32_t available=nocturneLibcConsoleReadAvailable(ring+4);
#else
            uint32_t available=*(volatile uint32_t *)(uintptr_t)(ring+4);
#endif
            if(available)break;
        }
        ring=word(0x59b6a8);uint32_t cursor=word(ring+8);*at(out)=*at(cursor);
        ps2ConsoleRingConsume(sx(word(0x59b6a8)));uint64_t c=sxByte(*at(out));
        if(c==10||c==13)return sx(next);
        n=next;if((int64_t)sx(n)>=(int64_t)count)return sx(n);
    }
}
static void diagnostic(uint32_t format,uint64_t a1){ps2SdkPrintfDefault(format,a1,0,0,0,0,0,0);}
void ps2ConsoleCommandCallback(uint64_t operation,uint64_t amount,uint64_t state){
    uint32_t p=(uint32_t)state;
    if(operation==3){
        uint64_t sent=ps2ConsoleSendBytes(sx(word(p)),sx(word(p+16)),(uint16_t)word(p+4));
        if(negative(sent)){diagnostic(0x54bab0,sent);put(p+12,0);}
        else{uint32_t buffer=word(p+16),remaining=word(p+4);buffer+=(uint32_t)sent;remaining-=(uint32_t)sent;put(p+16,buffer);put(p+4,remaining);}
        return;
    }
    if((int64_t)operation>=4){if(operation==4){if(word(p+4))diagnostic(0x54bac8,sx(word(p+4)));put(p+12,0);}return;}
    if(!operation||negative(operation))return;
    if(amount){
        uint32_t prior=word(p+8);if(sx(prior+(uint32_t)amount)>=321)diagnostic(0x54ba70,0);
        prior=word(p+8);uint32_t buffer=word(p+20);uint64_t received=ps2ConsoleReceiveBytes(sx(word(p)),sx(buffer+prior),(uint16_t)amount);
        if(negative(received))diagnostic(0x54ba98,0);
        put(p+8,word(p+8)+(uint32_t)received);return;
    }
    uint32_t header=word(p+20),packet=header,offset=12;
    while((int64_t)sx(offset)<(int64_t)(uint64_t)half(header)){
        uint8_t c=*at(packet+offset);offset++;uint32_t ring=word(p+24),cursor=word(ring+12);*at(cursor)=c;
        ps2ConsoleRingProduce(sx(word(p+24)));if((int64_t)sx(offset)<(int64_t)(uint64_t)half(header))packet=word(p+20);
    }
    put(p+8,0);
}
uint64_t ps2LibcConsoleWrite(uint64_t descriptor,uint64_t buffer,uint64_t count){
    if(sx((uint32_t)descriptor-1)>=2)return UINT64_MAX;
    if(!word(0x52c2a4)){if(!ps2ConsoleInitialize())return UINT64_MAX;put(0x52c2a4,1);}
    return ps2ConsoleWrite(buffer,count);
}
uint64_t ps2LibcConsoleRead(uint64_t descriptor,uint64_t buffer,uint64_t count){
    if(descriptor)return UINT64_MAX;
    if(!word(0x52c2a4)){if(!ps2ConsoleInitialize())return UINT64_MAX;put(0x52c2a4,1);}
    return ps2ConsoleRead(buffer,count);
}
uint64_t ps2LibcWriteReentrant(uint64_t context,uint64_t descriptor,uint64_t buffer,uint64_t count){
    put(0x552178,0);uint64_t result=ps2LibcConsoleWrite(descriptor,buffer,count);
    if(result==UINT64_MAX){uint32_t error=word(0x552178);if(error)put((uint32_t)context,error);}return result;
}
uint64_t ps2LibcReadReentrant(uint64_t context,uint64_t descriptor,uint64_t buffer,uint64_t count){
    put(0x552178,0);uint64_t result=ps2LibcConsoleRead(descriptor,buffer,count);
    if(result==UINT64_MAX){uint32_t error=word(0x552178);if(error)put((uint32_t)context,error);}return result;
}
uint64_t ps2LibcStreamRead(uint64_t cookie,uint64_t buffer,uint64_t count){
    uint32_t p=(uint32_t)cookie;uint64_t result=sx((uint32_t)ps2LibcReadReentrant(sx(word(p+84)),sxHalf(half(p+14)),buffer,count));
    if(negative(result))putHalf(p+12,(uint16_t)(half(p+12)&0xefff));else put(p+80,word(p+80)+(uint32_t)result);return result;
}
uint64_t ps2LibcStreamWrite(uint64_t cookie,uint64_t buffer,uint64_t count){
    uint32_t p=(uint32_t)cookie;if(half(p+12)&0x100)(void)ps2LibcSeekReentrant(sx(word(p+84)),sxHalf(half(p+14)),0,2);
    uint16_t flags=half(p+12);uint64_t descriptor=sxHalf(half(p+14)),context=sx(word(p+84));putHalf(p+12,(uint16_t)(flags&0xefff));
    return sx((uint32_t)ps2LibcWriteReentrant(context,descriptor,buffer,count));
}

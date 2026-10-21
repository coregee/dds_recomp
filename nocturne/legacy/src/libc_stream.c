/* Complete original stream/setup/flush/adapter bodies. Offsets are guest
 * offsets in 88-byte FILE records and the original reentrancy structure. */
#include "libc_stream.h"
#include "heap_queue.h"
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
static uint64_t sxHalf(uint16_t v){return sx(v&0x8000u?0xffff0000u|v:v);}
static int positive(uint32_t v){return v!=0&&!(v&0x80000000u);}
static uint64_t callback(uint32_t entry,uint32_t argc,const uint64_t *args){
#if UINTPTR_MAX > UINT32_MAX
    return nocturneLibcStreamCallback(entry,argc,args);
#else
    if(argc==1)return ((uint64_t (*)(uint64_t))(uintptr_t)entry)(args[0]);
    return ((uint64_t (*)(uint64_t,uint64_t,uint64_t))(uintptr_t)entry)(args[0],args[1],args[2]);
#endif
}
void ps2LibcStreamRecordInitialize(uint64_t stream,uint64_t flags,uint64_t descriptor,uint64_t context){
    uint32_t p=(uint32_t)stream;
    put(p+84,(uint32_t)context);putHalf(p+12,(uint16_t)flags);putHalf(p+14,(uint16_t)descriptor);
    put(p+32,0x2db670);put(p+36,0x2db6d8);put(p+40,0x2db758);put(p+44,0x2db7c0);
    put(p,0);put(p+4,0);put(p+8,0);put(p+16,0);put(p+20,0);put(p+24,0);put(p+28,p);
}
void ps2LibcStreamsInitialize(uint64_t context){
    uint32_t p=(uint32_t)context;put(p+60,0x2d98c8);put(p+56,1);
    ps2LibcStreamRecordInitialize(sx(p+484),4,0,context);
    ps2LibcStreamRecordInitialize(sx(p+572),9,1,context);
    ps2LibcStreamRecordInitialize(sx(p+660),10,2,context);
    put(p+472,0);put(p+480,p+484);put(p+476,3);
}
uint64_t ps2LibcLocaleRecord(uint64_t context){(void)context;return 0x54b8d8;}
uint64_t ps2LibcLocaleConvention(void){return ps2LibcLocaleRecord(sx(word(0x52be28)));}
uint64_t ps2LibcIsatty(uint64_t descriptor){(void)descriptor;return 1;}
uint64_t ps2LibcFstatStub(uint64_t descriptor,uint64_t output){
    (void)descriptor;uint32_t p=(uint32_t)output;uint64_t zero=0;memcpy(at(p+72),&zero,8);put(p+4,0x2000);return 0;
}
uint64_t ps2LibcFstatReentrant(uint64_t context,uint64_t descriptor,uint64_t output){
    put(0x552178,0);uint64_t value=ps2LibcFstatStub(descriptor,output);
    if(value==UINT64_MAX){uint32_t error=word(0x552178);if(error)put((uint32_t)context,error);}return value;
}
uint64_t ps2LibcCloseUnsupported(uint64_t descriptor){(void)descriptor;return UINT64_MAX;}
uint64_t ps2LibcSeekUnsupported(uint64_t descriptor,uint64_t offset,uint64_t origin){(void)descriptor;(void)offset;(void)origin;return UINT64_MAX;}
uint64_t ps2LibcCloseReentrant(uint64_t context,uint64_t descriptor){
    put(0x552178,0);uint64_t value=ps2LibcCloseUnsupported(descriptor);
    if(value==UINT64_MAX){uint32_t error=word(0x552178);if(error)put((uint32_t)context,error);}return value;
}
uint64_t ps2LibcSeekReentrant(uint64_t context,uint64_t descriptor,uint64_t offset,uint64_t origin){
    put(0x552178,0);uint64_t value=ps2LibcSeekUnsupported(descriptor,offset,origin);
    if(value==UINT64_MAX){uint32_t error=word(0x552178);if(error)put((uint32_t)context,error);}return value;
}
uint64_t ps2LibcStreamClose(uint64_t cookie){
    uint32_t p=(uint32_t)cookie;return ps2LibcCloseReentrant(sx(word(p+84)),sxHalf(half(p+14)));
}
uint64_t ps2LibcStreamSeek(uint64_t cookie,uint64_t offset,uint64_t origin){
    uint32_t p=(uint32_t)cookie;uint64_t value=ps2LibcSeekReentrant(sx(word(p+84)),sxHalf(half(p+14)),offset,origin);
    uint16_t flags=half(p+12);
    if(value==UINT64_MAX)flags&=0xefff;
    else{put(p+80,(uint32_t)value);flags|=0x1000;}
    putHalf(p+12,flags);return value;
}
uint64_t ps2LibcStreamWalk(uint64_t context,uint64_t cb){
    uint32_t node=(uint32_t)context+472;uint64_t result=0;
    while(node){
        uint32_t count=word(node+4),p=word(node+8);count--;
        while(!(count&0x80000000u)){
            if(half(p+12)){uint64_t args[1]={sx(p)};result|=callback((uint32_t)cb,1,args);}
            count--;p+=88;
        }
        node=word(node);
    }
    return result;
}
uint64_t ps2LibcStreamsCleanup(uint64_t context){return ps2LibcStreamWalk(context,0x2d95e0);}
uint64_t ps2LibcFlush(uint64_t stream){
    if(!stream)return ps2LibcStreamWalk(sx(word(0x52be28)),0x2d95e0);
    uint32_t p=(uint32_t)stream,context=word(p+84);
    if(!context){context=word(0x52be28);put(p+84,context);}
    if(!word(context+56))ps2LibcStreamsInitialize(sx(context));
    uint16_t flags=half(p+12);
    if((flags&8)&&word(p+16)){
        uint32_t output=word(p+16),remaining=word(p)-output,writable=flags&3?0:word(p+20);
        put(p,output);
        /* Original SW W happens even for an empty buffer. */
        put(p+8,writable);
        while(positive(remaining)){
            uint64_t args[3]={sx(word(p+28)),sx(output),sx(remaining)};
            uint64_t written=callback(word(p+36),3,args);remaining-=(uint32_t)written;
            if(!written||(written>>63)){putHalf(p+12,(uint16_t)(half(p+12)|0x40));return UINT64_MAX;}
            output+=(uint32_t)written;
        }
    }
    return 0;
}
void ps2LibcMakeBuffer(uint64_t stream){
    uint32_t p=(uint32_t)stream;uint16_t flags=half(p+12);int character=0;
    if(flags&2){put(p+20,1);put(p+16,p+67);put(p,p+67);return;}
    if(!(half(p+14)&0x8000u)){
        uint8_t status[80];uint32_t statusAddress;
#if UINTPTR_MAX > UINT32_MAX
        statusAddress=nocturneLibcStreamLocalAddress(status,sizeof(status));
#else
        statusAddress=(uint32_t)(uintptr_t)status;
#endif
        uint64_t result=ps2LibcFstatReentrant(sx(word(p+84)),sxHalf(half(p+14)),statusAddress);
#if UINTPTR_MAX > UINT32_MAX
        nocturneLibcStreamEndLocal();
#endif
        if(!(result>>63)){
            uint32_t mode;memcpy(&mode,status+4,4);mode&=0xf000;character=mode==0x2000;flags=half(p+12);
            if(mode==0x8000&&word(p+40)==0x2db758){put(p+76,1024);flags|=0x400;}else flags|=0x800;
        }else{flags=half(p+12);flags|=0x800;}
    }else flags|=0x800;
    putHalf(p+12,flags);uint32_t buffer=ps2HeapMallocReentrant(word(p+84),1024);flags=half(p+12);
    if(!buffer){put(p+16,p+67);put(p+20,1);putHalf(p+12,(uint16_t)(flags|2));put(p,p+67);return;}
    put(p+16,buffer);put(word(p+84)+60,0x2d98c8);putHalf(p+12,(uint16_t)(flags|0x80));put(p+20,1024);put(p,buffer);
    if(character&&ps2LibcIsatty(sxHalf(half(p+14))))putHalf(p+12,(uint16_t)(half(p+12)|1));
}
uint64_t ps2LibcPrepareWrite(uint64_t stream){
    uint32_t p=(uint32_t)stream,context=word(p+84);
    if(!context){context=word(0x52be28);put(p+84,context);}
    if(!word(context+56))ps2LibcStreamsInitialize(sx(context));
    uint16_t flags=half(p+12);uint32_t buffer;
    if(!(flags&8)){
        if(!(flags&16))return UINT64_MAX;
        if(flags&4){
            uint32_t unget=word(p+48);
            if(unget){if(unget==p+64)put(p+48,0);else{ps2HeapFree(word(p+84),unget);flags=half(p+12);put(p+48,0);}}
            buffer=word(p+16);flags&=0xffdb;put(p+4,0);putHalf(p+12,flags);put(p,buffer);
        }
        flags|=8;putHalf(p+12,flags);
    }
    buffer=word(p+16);
    if(!buffer)ps2LibcMakeBuffer(stream);
    flags=half(p+12);
    if(flags&1){put(p+8,0);put(p+24,0-word(p+20));}
    else put(p+8,flags&2?0:word(p+20));
    return 0;
}

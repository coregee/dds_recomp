/* Complete SDK formatter/output bodies. Integer arguments occupy eight bytes;
 * format-directed loads narrow to the original word/halfword/byte widths. */
#include "sdk_debug.h"
#include "compiler_numeric.h"
#include "nocturne.h"
#include "material_fiveword_pool.h"
#include <string.h>
static uint8_t *at(uint32_t address) {
#if UINTPTR_MAX > UINT32_MAX
    return (uint8_t *)nocturneResolveSdkDebugAddress(address);
#else
    return (uint8_t *)(uintptr_t)address;
#endif
}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static uint64_t sx32(uint32_t v){return v&0x80000000u?UINT64_C(0xffffffff00000000)|v:v;}
static uint64_t sx8(uint8_t v){return v&128?UINT64_C(0xffffffffffffff00)|v:v;}
static uint64_t sx16(uint16_t v){return v&32768?UINT64_C(0xffffffffffff0000)|v:v;}
static void emit(uint64_t character){
    uint32_t callback=word(0x52c2b4);
#if UINTPTR_MAX > UINT32_MAX
    nocturneSdkDebugCallback(callback,character);
#else
    (void)((uint64_t (*)(uint64_t))(uintptr_t)callback)(character);
#endif
}
uint64_t ps2SdkSerialPutchar(uint64_t character){ /* 002dd420 */
    while(nocturneSdkDebugSerialRead()&0x8000){}
    nocturneSdkDebugSerialWrite((uint8_t)character);return character;
}
uint64_t ps2SdkSerialPutcharNewline(uint64_t character){ /* 002dd508 */
    if(character==10){(void)ps2SdkSerialPutchar(13);return ps2SdkSerialPutchar(10);}
    return ps2SdkSerialPutchar(character);
}
uint64_t ps2KernelCommandRaw(uint64_t command,const void *parameters){return nocturneSdkDebugKernel(command,parameters);} /* 002dc2d0 */
uint64_t ps2SdkKernelDebugString(uint64_t string){ /* 002e4a50 */
    uint32_t packet=(uint32_t)string;return ps2KernelCommandRaw(16,&packet);
}
void ps2SdkBufferedPutchar(uint64_t character){ /* 002dd458 */
    uint32_t count=word(0x52c2b0);
    if(sx32(count)<UINT64_C(0x8000000000000000)&&count>=126){
        put(0x52c2b0,0);*at(0x59b940+127)=0;
        (void)ps2SdkKernelDebugString(0x59b940);count=word(0x52c2b0);
    }
    if(character==10){
        put(0x52c2b0,0);*at(0x59b940+count)=(uint8_t)character;*at(0x59b940+count+1)=0;
        (void)ps2SdkKernelDebugString(0x59b940);return;
    }
    put(0x52c2b0,count+1);*at(0x59b940+count)=(uint8_t)character;
}
void ps2SdkFormatFloat(uint64_t bits){ /* 002dd5d0 */
    uint64_t value=bits;uint32_t exponent=0;
    if(ps2SoftDoubleCompare(value,0)<0){value=ps2SoftDoubleSub(0,value);emit(45);}
    if(ps2SoftDoubleCompare(value,UINT64_C(0x3fb999999999999a))<0){
        while(ps2SoftDoubleCompare(value,UINT64_C(0x3fb999999999999a))<0){value=ps2SoftDoubleMul(value,UINT64_C(0x4024000000000000));exponent--;}
    }else if(ps2SoftDoubleCompare(value,UINT64_C(0x3ff0000000000000))>=0){
        while(ps2SoftDoubleCompare(value,UINT64_C(0x3ff0000000000000))>=0){value=ps2SoftDoubleDiv(value,UINT64_C(0x4024000000000000));exponent++;}
    }
    uint64_t integer=ps2SoftDoubleToUint64(ps2SoftDoubleMul(value,UINT64_C(0x412e848000000000)));
    ps2SdkPrintfDefault(0x54bae0,ps2SdkRoundDoubleWord(integer),0,0,0,0,0,0);
    ps2SdkPrintfDefault(exponent&0x80000000u?0x54baf0:0x54bae8,sx32(exponent),0,0,0,0,0,0);
}
static uint64_t argument(const uint8_t **p){uint64_t v;memcpy(&v,*p,8);*p+=8;return v;}
void ps2SdkVprintf(uint64_t format,const void *arguments){ /* 002dd738 */
    const uint8_t *args=arguments;uint32_t cursor=(uint32_t)format;
    uint32_t enabled=ps2KernelDisableInterrupts();
    while(*at(cursor)){
        uint8_t initial=*at(cursor);
        if(initial!='%'){emit(sx8(initial));cursor++;continue;}
        uint32_t spec=cursor+1;unsigned width=0,modifier=0;
        for(;;){
            uint8_t conversion=*at(spec);
            if(conversion=='0'){
                uint8_t next=*at(spec+1);unsigned first=(uint8_t)(next-'0');
                if(first>=10){spec++;continue;}
                uint8_t second=*at(spec+2);int digit=(int)(int8_t)second-'0';
                if(digit>=0&&digit<10){width=first*10+(unsigned)digit;if(width>31)width=31;spec+=3;}
                else{width=first;spec+=2;}
                continue;
            }
            if(conversion=='l'||conversion=='h'){modifier=conversion;spec++;continue;}
            if(conversion=='o'||conversion=='x'||conversion=='u'||conversion=='d'){
                uint64_t v=argument(&args);
                if(modifier=='h')v=conversion=='d'?sx16((uint16_t)v):(uint16_t)v;
                else if(modifier!='l')v=conversion=='d'?sx32((uint32_t)v):(uint32_t)v;
                uint8_t scratch[32];unsigned begin=31;scratch[31]=0;
                if(width)memset(scratch+31-width,'0',width);
                if(!v)scratch[--begin]='0';
                else{
                    if(conversion=='d'&&(v>>63)){v=UINT64_C(0)-v;emit(45);}
                    while(v){uint64_t digit;
                        if(conversion=='o'){digit=v&7;v>>=3;}
                        else if(conversion=='x'){digit=v&15;v>>=4;}
                        else if(conversion=='d'){digit=ps2Signed64Remainder(v,10);v=ps2Signed64Divide(v,10);}
                        else{digit=ps2Unsigned64Remainder(v,10);v=ps2Unsigned64Divide(v,10);}
                        scratch[--begin]=(uint8_t)(digit+(conversion=='x'&&digit>=10?87:48));
                    }
                }
                if(width&&31-width<begin)begin=31-width;
                while(scratch[begin])emit(sx8(scratch[begin++]));
                cursor=spec+1;break;
            }
            if(conversion=='c'){emit(sx8((uint8_t)argument(&args)));cursor=spec+1;break;}
            if(conversion=='s'){
                uint32_t string=(uint32_t)argument(&args);
                if(!*at(string)){const char *null_text="(null)";for(unsigned k=0;k<6;k++)emit((uint8_t)null_text[k]);}
                else{while(*at(string)){uint8_t v=*at(string);string++;emit(sx8(v));}}
                cursor=spec+1;break;
            }
            if(conversion=='e'||conversion=='f'){
                uint32_t bits=(uint32_t)argument(&args);
                if(nocturneSdkDebugFloatZero(bits))emit(48);
                else{float v;memcpy(&v,&bits,4);ps2SdkFormatFloat(ps2SoftDoubleFromFloat(v));}
                cursor=spec+1;break;
            }
            /* Unknown in-range jump-table entries and out-of-range bytes both
             * advance once. A malformed trailing format can read past NUL. */
            cursor=spec+1;break;
        }
    }
    if(enabled)(void)ps2KernelEnableInterrupts();
}
void ps2SdkPrintfDefault(uint64_t format,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7){ /* 002ddd28 */
    uint64_t args[7]={a1,a2,a3,a4,a5,a6,a7};ps2SdkVprintf(format,args);
}
void ps2SdkPrintf(uint64_t format,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7){ /* 002ddd60 */
    uint32_t previous=word(0x52c2b4);put(0x52c2b4,0x2dd458);
    uint64_t args[7]={a1,a2,a3,a4,a5,a6,a7};ps2SdkVprintf(format,args);put(0x52c2b4,previous);
}

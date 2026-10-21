/* Complete native formatter: explicit guest words and original eight-vector
 * batches. Integer and floating conversion call recovered library bodies. */
#include "libc_formatter.h"
#include "libc_cvt.h"
#include "libc_stream.h"
#include "libc_vector.h"
#include "heap_queue.h"
#include "compiler_numeric.h"
#include "ps2_memory.h"
#include "ps2_sdk_frontier.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveHeapAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t quad(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static uint16_t half(uint32_t a){uint16_t v;memcpy(&v,at(a),2);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void putQuad(uint32_t a,uint64_t v){memcpy(at(a),&v,8);}
static void putHalf(uint32_t a,uint16_t v){memcpy(at(a),&v,2);}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v>>31)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
static uint32_t local(void *p,uint32_t n){
#if UINTPTR_MAX > UINT32_MAX
    return nocturneLibcStreamLocalAddress(p,n);
#else
    (void)n;return (uint32_t)(uintptr_t)p;
#endif
}
static void endLocal(void){
#if UINTPTR_MAX > UINT32_MAX
    nocturneLibcStreamEndLocal();
#endif
}
typedef struct {uint64_t stream;uint32_t frame,next;} Output;
static int flush(Output *o){
    uint64_t r=ps2LibcSprint(o->stream,o->frame+0x10);
    o->next=o->frame+0x20;return r!=0;
}
static int emit(Output *o,uint32_t p,uint32_t n){
    put(o->next,p);put(o->next+4,n);o->next+=8;
    put(o->frame+0x14,word(o->frame+0x14)+1);
    put(o->frame+0x18,word(o->frame+0x18)+n);
    if(s32(word(o->frame+0x14))>7)return flush(o);
    return 0;
}
static int pad(Output *o,uint32_t p,int32_t n){
    while(n>16){if(emit(o,p,16))return 1;n-=16;}
    return n>0?emit(o,p,(uint32_t)n):0;
}
static uint32_t argument(uint32_t *args){uint32_t p=*args;*args+=8;return p;}
uint64_t ps2LibcVfprintfUnbuffered(uint64_t stream,uint64_t format,uint64_t arguments)
{
    uint8_t scratch[0x480];uint32_t p=local(scratch,sizeof(scratch)),s=(uint32_t)stream,b=p+0x60;
    put(p,b);put(p+8,1024);putHalf(p+12,(uint16_t)(half(s+12)&0xfffd));
    putHalf(p+14,half(s+14));put(p+16,b);put(p+20,1024);put(p+24,0);
    put(p+28,word(s+28));put(p+36,word(s+36));put(p+84,word(s+84));
    uint64_t result=ps2LibcVfprintfStream(p,format,arguments);
    if(!(result>>63)&&ps2LibcFlush(p))result=UINT64_MAX;
    if(half(p+12)&0x40)putHalf(s+12,(uint16_t)(half(s+12)|0x40));
    endLocal();return result;
}
uint64_t ps2LibcVfprintfStream(uint64_t stream,uint64_t format,uint64_t arguments)
{
    uint32_t p=(uint32_t)stream,c=word(p+84);
    if(!c){c=word(0x52be28);put(p+84,c);}
    if(!word(c+56)){ps2LibcStreamsInitialize(c);c=word(p+84);}
    return ps2LibcVfprintf(sx(c),stream,format,arguments);
}
uint64_t ps2LibcVfprintf(uint64_t context,uint64_t stream,uint64_t format,uint64_t arguments)
{
    uint8_t scratch[0x290];uint32_t frame=local(scratch,sizeof(scratch));
    uint32_t s=(uint32_t)stream,f=(uint32_t)format,args=(uint32_t)arguments,count=0;
    uint32_t decimal=word((uint32_t)ps2LibcLocaleConvention());
    Output output={stream,frame,frame+0x20};
    put(frame+0x10,frame+0x20);put(frame+0x14,0);put(frame+0x18,0);
    uint64_t result;
    if(!(half(s+12)&8)||!word(s+16)){
        if(ps2LibcPrepareWrite(stream)){result=UINT64_MAX;goto done;}
    }
    if((half(s+12)&0x1a)==10&&!(half(s+14)&0x8000)){
        result=ps2LibcVfprintfUnbuffered(stream,format,arguments);goto done;
    }
    for(;;){
        uint32_t start=f,widened=0;int32_t step;
        do{
            step=ps2WidenByte((void *)(uintptr_t)word(0x52be28),&widened,f?at(f):NULL,sx(word(0x52c290)));
            if(step>0){f+=(uint32_t)step;if(widened=='%'){f--;break;}}
        }while(step>0);
        uint32_t literal=f-start;
        if(literal){if(emit(&output,start,literal))goto failure;count+=literal;}
        if(step<=0)break;
        f++;
        uint32_t flags=0,width=0,precision=UINT32_MAX,numberPrecision=0;
        uint32_t source=frame+0x60,n=0,hex=0x54b6a0;
        uint8_t sign=0;int32_t conversion;
        uint64_t bits=0;
        for(;;){
            conversion=(int8_t)*at(f++);
            if(conversion==' '){if(!sign)sign=' ';continue;}
            if(conversion=='#'){flags|=1;continue;}
            if(conversion=='+'){sign='+';continue;}
            if(conversion=='-'){flags|=4;continue;}
            if(conversion=='0'){flags|=0x80;continue;}
            if(conversion=='*'){
                width=word(argument(&args));if(s32(width)<0){width=0-width;flags|=4;}continue;
            }
            if(conversion>='1'&&conversion<='9'){
                width=0;
                do{width=width*10+(uint32_t)conversion-'0';conversion=(int8_t)*at(f++);}
                while((uint32_t)(conversion-'0')<10);
            }
            if(conversion=='.'){
                conversion=(int8_t)*at(f++);
                if(conversion=='*'){
                    precision=word(argument(&args));if(s32(precision)<-1)precision=UINT32_MAX;continue;
                }
                precision=0;
                while((uint32_t)(conversion-'0')<10){
                    precision=precision*10+(uint32_t)conversion-'0';conversion=(int8_t)*at(f++);
                }
                if(s32(precision)<-1)precision=UINT32_MAX;
            }
            if(conversion=='h'){flags|=0x40;continue;}
            if(conversion=='l'){
                if(*at(f)=='l'){f++;flags|=0x20;}else flags|=0x10;
                continue;
            }
            if(conversion=='q'){flags|=0x20;continue;}
            if(conversion=='L'){flags|=8;continue;}
            break;
        }
        if(conversion=='n'){
            uint32_t out=word(argument(&args));
            if(flags&0x10)putQuad(out,sx(count));
            else if(flags&0x40)putHalf(out,(uint16_t)count);else put(out,count);
            continue;
        }
        if(conversion=='s'){
            source=word(argument(&args));if(!source)source=0x54b6b8;
            if(s32(precision)<0)n=ps2Strlen((const char *)at(source));
            else{
                n=precision;
                const uint8_t *p=at(source),*found=ps2Memchr(p,0,precision);
                if(found&&s32((uint32_t)(found-p))<=s32(precision))n=(uint32_t)(found-p);
            }
            sign=0;
        }else if(conversion=='c'){
            *at(source)=(uint8_t)quad(argument(&args));n=1;sign=0;
        }else if(conversion=='d'||conversion=='i'||conversion=='D'||conversion=='u'||conversion=='U'||
                 conversion=='o'||conversion=='O'||conversion=='x'||conversion=='X'||conversion=='p'){
            int radix=10,signedValue=conversion=='d'||conversion=='i'||conversion=='D';
            if(conversion=='D'||conversion=='U'||conversion=='O')flags|=0x10;
            uint32_t p=argument(&args);uint64_t value;
            if(conversion=='p')value=sx(word(p));
            else if(flags&0x10)value=quad(p);
            else if(flags&0x40)value=signedValue?(uint64_t)(int64_t)(int16_t)half(p):half(p);
            else value=signedValue?sx(word(p)):word(p);
            if(signedValue){if(value>>63){value=0-value;sign='-';}}
            else sign=0;
            if(conversion=='o'||conversion=='O')radix=8;
            if(conversion=='x'||conversion=='X'||conversion=='p'){
                radix=16;hex=conversion=='X'?0x54b6c0:0x54b6a0;
                if(conversion=='p'){flags|=2;conversion='x';}
                else if((flags&1)&&value)flags|=2;
            }
            numberPrecision=precision;if(s32(precision)>=0)flags&=~0x80u;
            source=frame+0x1bc;
            if(value||precision){
                if(radix==10){
                    while(value>9){*at(--source)=(uint8_t)(ps2Unsigned64Remainder(value,10)+'0');value=ps2Unsigned64Divide(value,10);}
                    *at(--source)=(uint8_t)(value+'0');
                }else if(radix==8){
                    do{*at(--source)=(uint8_t)((value&7)+'0');value>>=3;}while(value);
                    if((flags&1)&&*at(source)!='0')*at(--source)='0';
                }else{
                    do{*at(--source)=*at(hex+(uint32_t)(value&15));value>>=4;}while(value);
                }
            }
            n=frame+0x1bc-source;
        }else if(conversion=='e'||conversion=='E'||conversion=='f'||conversion=='g'||conversion=='G'){
            if(precision==UINT32_MAX)precision=6;
            else if((conversion=='g'||conversion=='G')&&!precision)precision=1;
            bits=quad(argument(&args));
            if(ps2IsDoubleInfBits(bits)){
                if(ps2SoftDoubleCompare(bits,0)<0)sign='-';source=0x54b690;n=3;
            }else if(ps2IsDoubleNaNBits(bits)){source=0x54b698;n=3;}
            else{
                flags|=0x100;
                source=(uint32_t)ps2LibcCvt(context,bits,sx(precision),flags,frame+0x1d0,frame+0x1dc,sx((uint32_t)conversion),frame+0x1e0);
                uint32_t dec=word(frame+0x1dc),digits=word(frame+0x1e0);
                if(conversion=='g'||conversion=='G'){
                    if(s32(dec)<-3||s32(precision)<s32(dec))conversion=conversion=='g'?'e':'E';
                    else conversion='g';
                }
                if(conversion<'f'){
                    dec--;put(frame+0x1dc,dec);
                    uint32_t exponent=(uint32_t)ps2LibcFormatExponent(frame,sx(dec),sx((uint32_t)conversion));
                    put(frame+0x200,exponent);n=exponent+digits+((s32(digits)>1||(flags&1))?1:0);
                }else if(conversion=='f'){
                    n=precision+2;
                    if(s32(dec)>0){n=dec;if(precision||(flags&1))n=dec+precision+1;}
                }else if(s32(dec)<s32(digits))n=s32(dec)<1?digits-dec+2:digits+1;
                else n=dec+((flags&1)?1:0);
                if(*at(frame+0x1d0))sign='-';
            }
        }else{
            if(!conversion)break;
            *at(source)=(uint8_t)conversion;n=1;sign=0;
        }
        uint32_t printed=s32(numberPrecision)>s32(n)?numberPrecision:n;
        printed+=sign?1:(flags&2);
        *at(frame+0x1d1)=sign;
        if(!(flags&0x84)&&pad(&output,0x54b670,s32(width-printed)))goto failure;
        if(sign){if(emit(&output,frame+0x1d1,1))goto failure;}
        else if(flags&2){*at(frame+0x1c0)='0';*at(frame+0x1c1)=(uint8_t)conversion;if(emit(&output,frame+0x1c0,2))goto failure;}
        if((flags&0x84)==0x80&&pad(&output,0x54b680,s32(width-printed)))goto failure;
        if(pad(&output,0x54b680,s32(numberPrecision-n)))goto failure;
        if(!(flags&0x100)){if(emit(&output,source,n))goto failure;}
        else{
            uint32_t digits=word(frame+0x1e0),dec=word(frame+0x1dc);
            if(conversion<'f'){
                if(s32(digits)>1||(flags&1)){
                    *at(frame+0x1c0)=*at(source);*at(frame+0x1c1)='.';
                    if(emit(&output,frame+0x1c0,2))goto failure;
                    if(ps2SoftDoubleCompare(bits,0)==0){if(pad(&output,0x54b680,s32(digits-1)))goto failure;}
                    else if(emit(&output,source+1,digits-1))goto failure;
                }else if(emit(&output,source,1))goto failure;
                if(emit(&output,frame,word(frame+0x200)))goto failure;
            }else if(ps2SoftDoubleCompare(bits,0)==0){
                if(emit(&output,0x54b6f8,1))goto failure;
                if(s32(dec)<s32(digits)||(flags&1)){
                    if(emit(&output,decimal,1)||pad(&output,0x54b680,s32(digits-1)))goto failure;
                }
            }else if(s32(dec)<1){
                if(emit(&output,0x54b6f8,1))goto failure;
                if(dec||digits){
                    if(emit(&output,decimal,1)||pad(&output,0x54b680,s32(0-dec))||emit(&output,source,digits))goto failure;
                }
            }else if(s32(dec)<s32(digits)){
                if(emit(&output,source,dec)||emit(&output,0x54b700,1)||emit(&output,source+dec,digits-dec))goto failure;
            }else{
                if(emit(&output,source,digits)||pad(&output,0x54b680,s32(dec-digits)))goto failure;
                if((flags&1)&&emit(&output,0x54b700,1))goto failure;
            }
        }
        if((flags&4)&&pad(&output,0x54b670,s32(width-printed)))goto failure;
        count+=s32(width)>s32(printed)?width:printed;
        if(word(frame+0x18)&&flush(&output))goto failure;
        output.next=frame+0x20;put(frame+0x14,0);
    }
    if(word(frame+0x18))(void)flush(&output);
failure:
    result=(half(s+12)&0x40)?UINT64_MAX:sx(count);
done:
    endLocal();return result;
}

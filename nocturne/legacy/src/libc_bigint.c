#include "libc_bigint.h"
#include "heap_queue.h"
#include "ps2_memory.h"
#include "ps2_sdk_frontier.h"
#include "compiler_numeric.h"
#include <string.h>
static uint8_t *at(uint32_t address){return (uint8_t *)nocturneResolveHeapAddress(address);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static void putHalf(uint32_t a,uint32_t v){uint16_t h=(uint16_t)v;memcpy(at(a),&h,2);}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v>>31)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
static uint32_t sar(uint32_t v,unsigned n){return (v>>n)|((v>>31)?(~UINT32_C(0)<<(32-n)):0);}
uint64_t ps2LibcCallocReentrant(uint64_t context,uint64_t count,uint64_t size){
    uint32_t p=ps2HeapMallocReentrant((uint32_t)context,(uint32_t)count*(uint32_t)size);
    if(p){
        uint32_t bytes=(word(p-4)&~UINT32_C(3))-4,cursor=p;
        if(bytes<37){
            if(bytes>=20){put(p,0);put(p+4,0);cursor=p+8;
                if(bytes>=28){put(cursor,0);cursor=p+16;put(p+12,0);
                    if(bytes>=36){put(cursor,0);cursor=p+24;put(p+20,0);}
                }
            }
            put(cursor,0);cursor+=4;put(cursor+4,0);put(cursor,0);
        }else ps2Memset(at(p),0,bytes);
    }
    return sx(p);
}
uint64_t ps2LibcBigintAllocate(uint64_t context,uint64_t k){
    uint32_t c=(uint32_t)context,heads=word(c+76),slot,p;
    if(!heads){heads=(uint32_t)ps2LibcCallocReentrant(context,4,16);put(c+76,heads);if(!heads)return 0;}
    slot=heads+((uint32_t)k<<2);p=word(slot);
    if(p)put(slot,word(p));
    else{
        uint32_t capacity=1u<<((uint32_t)k&31);
        p=(uint32_t)ps2LibcCallocReentrant(context,1,sx((capacity<<2)+20));if(!p)return 0;
        put(p+4,(uint32_t)k);put(p+8,capacity);
    }
    put(p+16,0);put(p+12,0);return sx(p);
}
void ps2LibcBigintFree(uint64_t context,uint64_t bigint){
    if(bigint){uint32_t p=(uint32_t)bigint,slot=word((uint32_t)context+76)+(word(p+4)<<2);uint32_t next=word(slot);put(p,next);put(slot,p);}
}
uint64_t ps2LibcBigintFromWord(uint64_t context,uint64_t value){
    uint64_t p=ps2LibcBigintAllocate(context,1);put((uint32_t)p+20,(uint32_t)value);put((uint32_t)p+16,1);return p;
}
uint64_t ps2LibcBigintMultiplyAdd(uint64_t context,uint64_t bigint,uint64_t multiplier,uint64_t addend){
    uint64_t result=bigint;
    uint32_t p=(uint32_t)bigint,n=word(p+16),cursor=p+20,i=0,carry=(uint32_t)addend,m=(uint32_t)multiplier;
    do{
        uint32_t v=word(cursor),lo=(v&65535)*m+carry,hi=(v>>16)*m+(lo>>16);
        ++i;carry=hi>>16;put(cursor,(hi<<16)+(lo&65535));cursor+=4;
    }while(s32(i)<s32(n));
    if(carry){
        if(!(s32(n)<s32(word(p+8)))){
            uint32_t fresh=(uint32_t)ps2LibcBigintAllocate(context,sx(word(p+4)+1));
            uint32_t bytes=(word(p+16)<<2)+8;ps2Memcpy(at(fresh+12),at(p+12),bytes);
            ps2LibcBigintFree(context,sx(p));p=fresh;result=sx(p);
        }
        put(p+(n<<2)+20,carry);put(p+16,n+1);
    }
    return result;
}
uint64_t ps2LibcBigintMultiply(uint64_t context,uint64_t left,uint64_t right){
    uint32_t a=(uint32_t)left,b=(uint32_t)right,na=word(a+16),nb=word(b+16);
    if(s32(na)<s32(nb)){uint32_t t=a;a=b;b=t;na=nb;nb=word(b+16);}
    uint32_t n=na+nb,k=word(a+4)+(s32(word(a+8))<s32(n));
    uint32_t out=(uint32_t)ps2LibcBigintAllocate(context,sx(k)),start=out+20,end=start+(n<<2);
    for(uint32_t p=start;p<end;p+=4)put(p,0);
    uint32_t bp=b+20,bend=bp+(nb<<2),abase=a+20,aend=abase+(na<<2),op=start;
    while(bp<bend){
        uint32_t m=word(bp)&65535,d=op;
        if(m){uint32_t ap=abase,carry=0;do{
            uint32_t v=word(ap),old=word(d),lo=(v&65535)*m+(old&65535)+carry;
            uint32_t hi=(v>>16)*m+(old>>16)+(lo>>16);
            putHalf(d,lo);putHalf(d+2,hi);carry=hi>>16;ap+=4;d+=4;
        }while(ap<aend);put(d,carry);}
        m=word(bp)>>16;d=op;
        if(m){uint32_t ap=abase,carry=0,old=word(d),v=old;do{
            uint32_t limb=word(ap);ap+=4;putHalf(d,v);
            uint32_t lo=(limb&65535)*m+(old>>16)+carry;
            putHalf(d+2,lo);d+=4;old=word(d);
            v=(limb>>16)*m+(old&65535)+(lo>>16);carry=v>>16;
        }while(ap<aend);put(d,v);}
        bp+=4;op+=4;
    }
    uint32_t tail=end;
    while(s32(n)>0){tail-=4;if(word(tail))break;--n;}
    put(out+16,n);return sx(out);
}
uint64_t ps2LibcBigintPowerOfFive(uint64_t context,uint64_t bigint,uint64_t exponent){
    uint64_t result=bigint;
    uint32_t c=(uint32_t)context,p=(uint32_t)bigint,e=(uint32_t)exponent,small=e&3;
    if(small){result=ps2LibcBigintMultiplyAdd(context,result,sx(word(0x54b91c+(small<<2))),0);p=(uint32_t)result;}
    e=sar(e,2);if(!e)return result;
    uint32_t power=word(c+72);
    if(!power){power=(uint32_t)ps2LibcBigintFromWord(context,625);put(c+72,power);put(power,0);}
    for(;;){
        uint32_t bit=e&1;e=sar(e,1);
        if(bit){uint32_t fresh=(uint32_t)ps2LibcBigintMultiply(context,result,sx(power));ps2LibcBigintFree(context,result);p=fresh;result=sx(p);}
        if(!e)break;
        uint32_t next=word(power);
        if(!next){next=(uint32_t)ps2LibcBigintMultiply(context,sx(power),sx(power));put(power,next);put(next,0);}
        power=next;
    }
    return result;
}
uint64_t ps2LibcBigintShiftLeft(uint64_t context,uint64_t bigint,uint64_t shift){
    uint32_t p=(uint32_t)bigint,s=(uint32_t)shift,whole=sar(s,5),n=whole+word(p+16)+1;
    uint32_t capacity=word(p+8),k=word(p+4);
    while(s32(capacity)<s32(n)){capacity<<=1;++k;}
    uint32_t out=(uint32_t)ps2LibcBigintAllocate(context,sx(k)),d=out+20;
    if(s32(whole)>0){uint32_t i=whole;do{--i;put(d,0);d+=4;}while(i);}
    uint32_t src=p+20,end=src+(word(p+16)<<2);s&=31;
    if(s){uint32_t carry=0;do{
        uint32_t v=word(src);put(d,(v<<s)|carry);d+=4;carry=word(src)>>(32-s);src+=4;
    }while(src<end);put(d,carry);if(carry)++n;
    }else do{uint32_t v=word(src);src+=4;put(d,v);d+=4;}while(src<end);
    put(out+16,n-1);ps2LibcBigintFree(context,bigint);return sx(out);
}
uint64_t ps2LibcBigintDifference(uint64_t context,uint64_t left,uint64_t right){
    uint32_t a=(uint32_t)left,b=(uint32_t)right;int32_t comparison=ps2CompareLimbArrays(at(a),at(b));
    if(!comparison){uint32_t p=(uint32_t)ps2LibcBigintAllocate(context,0);put(p+16,1);put(p+20,0);return sx(p);}
    uint32_t sign=0;if(comparison<0){uint32_t t=a;a=b;b=t;sign=1;}
    uint32_t out=(uint32_t)ps2LibcBigintAllocate(context,sx(word(a+4))),ap=a+20,bp=b+20,d=out+20,borrow=0,n=word(a+16);
    put(out+12,sign);uint32_t aend=ap+(n<<2),bend=bp+(word(b+16)<<2);
    do{
        uint32_t av=word(ap),bv=word(bp);ap+=4;bp+=4;
        uint32_t lo=(av&65535)-(bv&65535)+borrow,hi=(av>>16)-(bv>>16)+sar(lo,16);
        putHalf(d,lo);putHalf(d+2,hi);d+=4;borrow=sar(hi,16);
    }while(bp<bend);
    while(ap<aend){uint32_t av=word(ap);ap+=4;uint32_t lo=(av&65535)+borrow,hi=(av>>16)+sar(lo,16);putHalf(d,lo);putHalf(d+2,hi);d+=4;borrow=sar(hi,16);}
    d-=4;while(!word(d)){d-=4;--n;}put(out+16,n);return sx(out);
}
uint64_t ps2LibcBigintFromDoubleBits(uint64_t context,uint64_t bits,uint64_t exponent,uint64_t significantBits){
    uint32_t out=(uint32_t)ps2LibcBigintAllocate(context,1),hi=(uint32_t)(bits>>32)&0xfffff;
    uint32_t encoded=(uint32_t)(bits>>52)&2047,lo=(uint32_t)bits,removed,count;
    if(encoded)hi|=0x100000;
    if(lo){removed=ps2RemoveTrailingZeroBits(&lo);if(removed){lo|=hi<<((0-removed)&31);hi>>=removed;}
        put(out+20,lo);count=hi?2:1;put(out+24,hi);put(out+16,count);
    }else{removed=ps2RemoveTrailingZeroBits(&hi)+32;put(out+20,hi);count=1;put(out+16,1);}
    uint32_t significant;
    if(encoded){put((uint32_t)exponent,encoded+removed-1075);significant=53-removed;}
    else{put((uint32_t)exponent,removed-1074);significant=(count<<5)-ps2CountLeadingZeroBits(s32(word(out+16+(count<<2))));}
    put((uint32_t)significantBits,significant);return sx(out);
}
uint64_t ps2LibcBigintQuotientRemainder(uint64_t numerator,uint64_t denominator){
    uint32_t a=(uint32_t)numerator,b=(uint32_t)denominator,n=word(b+16);
    if(s32(word(a+16))<s32(n))return 0;
    --n;uint32_t abase=a+20,bbase=b+20,top=abase+(n<<2),btop=bbase+(n<<2);
    uint32_t cached=word(top),divisor=word(btop)+1;
    if(!divisor)nocturneCompilerArithmeticTrap(7);
    uint32_t q=cached/divisor;
    if(q){uint32_t ap=abase,bp=bbase,carry=0,borrow=0;do{
        uint32_t bv=word(bp),av=word(ap);bp+=4;
        uint32_t lo=(bv&65535)*q+carry,hi=(bv>>16)*q+(lo>>16);
        uint32_t lowdiff=(av&65535)-(lo&65535)+borrow,highdiff=(av>>16)-(hi&65535)+sar(lowdiff,16);
        putHalf(ap,lowdiff);putHalf(ap+2,highdiff);ap+=4;carry=hi>>16;borrow=sar(highdiff,16);
    }while(!(btop<bp));
        /* The original tests its cached pre-subtraction top, not a reload. */
        if(!cached){top-=4;while(abase<top){if(word(top))break;top-=4;--n;}put(a+16,n);}
    }
    if(ps2CompareLimbArrays(at(a),at(b))>=0){
        ++q;uint32_t ap=abase,bp=bbase,carry=0,borrow=0;do{
            uint32_t bv=word(bp),av=word(ap);bp+=4;
            uint32_t lo=(bv&65535)+carry,hi=(bv>>16)+(lo>>16);
            uint32_t lowdiff=(av&65535)-(lo&65535)+borrow,highdiff=(av>>16)-(hi&65535)+sar(lowdiff,16);
            putHalf(ap,lowdiff);putHalf(ap+2,highdiff);ap+=4;carry=hi>>16;borrow=sar(highdiff,16);
        }while(!(btop<bp));
        top=abase+(n<<2);if(!word(top)){top-=4;while(abase<top){if(word(top))break;top-=4;--n;}put(a+16,n);}
    }
    return sx(q);
}

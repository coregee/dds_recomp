/* Complete scalar compiler/SDK numeric behavior. No host floating arithmetic.
 * Integer magnitude operations avoid signed overflow at INT64_MIN/-1. */
#include "compiler_numeric.h"
#include "nocturne.h"
static int32_t s32(uint32_t v) { return (int32_t)((int64_t)v-(v&UINT32_C(0x80000000)?INT64_C(4294967296):0)); }
static uint64_t sx(uint32_t v) { return v&UINT32_C(0x80000000)?UINT64_C(0xffffffff00000000)|v:v; }
uint64_t ps2Unsigned64Divide(uint64_t dividend,uint64_t divisor) { /* 002e6048 */
    if(!divisor)nocturneCompilerArithmeticTrap(7);
    return dividend/divisor;
}
uint64_t ps2Unsigned64Remainder(uint64_t dividend,uint64_t divisor) { /* 002e65c8 */
    if(!divisor)nocturneCompilerArithmeticTrap(7);
    return dividend%divisor;
}
uint64_t ps2Signed64Divide(uint64_t dividend,uint64_t divisor) { /* 002e5320 */
    if(!divisor)nocturneCompilerArithmeticTrap(7);
    uint64_t a=dividend>>63?UINT64_C(0)-dividend:dividend;
    uint64_t b=divisor>>63?UINT64_C(0)-divisor:divisor;
    uint64_t quotient=a/b;
    return (dividend^divisor)>>63?UINT64_C(0)-quotient:quotient;
}
uint64_t ps2Signed64Remainder(uint64_t dividend,uint64_t divisor) { /* 002e59b8 */
    if(!divisor)nocturneCompilerArithmeticTrap(7);
    uint64_t a=dividend>>63?UINT64_C(0)-dividend:dividend;
    uint64_t b=divisor>>63?UINT64_C(0)-divisor:divisor;
    uint64_t remainder=a%b;
    return dividend>>63?UINT64_C(0)-remainder:remainder;
}
/* 002e6c48: 61 quotient bits, truncating pack and flushed subnormals. */
uint64_t ps2SoftDoubleDiv(uint64_t left,uint64_t right) {
    ps2SoftDoubleParts a={0},b={0};
    ps2SoftDoubleUnpack(&left,&a);ps2SoftDoubleUnpack(&right,&b);
    if(a.fpclass<2)return ps2SoftDoublePack(&a);
    if(b.fpclass<2)return ps2SoftDoublePack(&b);
    a.sign^=b.sign;
    if(a.fpclass==4||a.fpclass==2) {
        if(a.fpclass==b.fpclass)return UINT64_C(0x7ff8000000000000);
        return ps2SoftDoublePack(&a);
    }
    if(b.fpclass==4){a.fraction=0;a.exponent=0;return ps2SoftDoublePack(&a);}
    if(b.fpclass==2){a.fpclass=4;return ps2SoftDoublePack(&a);}
    a.exponent-=b.exponent;
    uint64_t remainder=a.fraction,denominator=b.fraction,quotient=0;
    if(remainder<denominator){a.exponent--;remainder<<=1;}
    for(uint64_t bit=UINT64_C(0x1000000000000000);bit;bit>>=1) {
        if(remainder>=denominator){remainder-=denominator;quotient|=bit;}
        remainder<<=1;
    }
    a.fraction=quotient;return ps2SoftDoublePack(&a);
}
/* 002e6d88: signed high word, two multiplications by65536, unsigned low word. */
uint64_t ps2SoftDoubleFromInt64(uint64_t value) {
    uint64_t high=ps2SoftDoubleFromInt(s32((uint32_t)(value>>32)));
    high=ps2SoftDoubleMul(high,UINT64_C(0x40f0000000000000));
    high=ps2SoftDoubleMul(high,UINT64_C(0x40f0000000000000));
    int32_t low=s32((uint32_t)value);uint64_t low_bits=ps2SoftDoubleFromInt(low);
    if(low<0)low_bits=ps2SoftDoubleAdd(low_bits,UINT64_C(0x41f0000000000000));
    return ps2SoftDoubleAdd(high,low_bits);
}
/* 002e6b30: separate high/low conversions; preserve subtraction correction. */
uint64_t ps2SoftDoubleToUint64(uint64_t bits) {
    if(ps2SoftDoubleCompare(bits,0)<0)return 0;
    uint64_t high=(uint64_t)ps2SoftDoubleToUint(ps2SoftDoubleMul(bits,UINT64_C(0x3df0000000000000)))<<32;
    uint64_t converted;
    if(high>>63){converted=ps2SoftDoubleFromInt64((high>>1)|(high&1));converted=ps2SoftDoubleAdd(converted,converted);}
    else converted=ps2SoftDoubleFromInt64(high);
    uint64_t residual=ps2SoftDoubleSub(bits,converted);
    if(ps2SoftDoubleCompare(residual,0)<0)return high-ps2SoftDoubleToUint(ps2SoftDoubleSub(0,residual));
    return high+ps2SoftDoubleToUint(residual);
}
/* 002dd540: sign ignored, two low guard bits round upward only when both set.
 * Variable shifts mask to63; the final word is sign-extended. */
uint64_t ps2SdkRoundDoubleWord(uint64_t bits) {
    int64_t exponent=(int64_t)((bits<<1)>>53)-1075;
    if(exponent < -53)return 0;
    if(exponent >= 13)return 9999;
    uint64_t mantissa=(bits&UINT64_C(0x000fffffffffffff))|UINT64_C(0x0010000000000000);
    if(exponent<0){mantissa>>=(uint32_t)(-exponent-2)&63;mantissa=(mantissa&3)==3?(mantissa>>2)+1:mantissa>>2;}
    else mantissa<<=(uint32_t)exponent&63;
    return sx((uint32_t)mantissa);
}

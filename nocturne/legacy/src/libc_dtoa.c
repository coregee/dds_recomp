/* Complete native dtoa control flow, backed guest records and raw bits.
 * Stack-derived names and original join labels make instruction review possible;
 * they are not a machine interpreter. All dependencies are recovered C. */
#include "libc_dtoa.h"
#include "libc_bigint.h"
#include "libc_stream.h"
#include "heap_queue.h"
#include "compiler_numeric.h"
#include "ps2_memory.h"
#include "ps2_sdk_frontier.h"
#include "nocturne.h"
#include <string.h>
static uint8_t *at(uint32_t a){return (uint8_t *)nocturneResolveHeapAddress(a);}
static uint32_t word(uint32_t a){uint32_t v;memcpy(&v,at(a),4);return v;}
static uint64_t qword(uint32_t a){uint64_t v;memcpy(&v,at(a),8);return v;}
static void put(uint32_t a,uint32_t v){memcpy(at(a),&v,4);}
static int8_t byte(uint32_t a){return (int8_t)*at(a);}
static void putByte(uint32_t a,int32_t v){*at(a)=(uint8_t)v;}
static int32_t s32(uint32_t v){return (int32_t)((int64_t)v-((v>>31)?INT64_C(4294967296):0));}
static uint64_t sx(uint32_t v){return (uint64_t)(int64_t)s32(v);}
static uint32_t fromDouble(uint64_t c,uint64_t bits,int32_t *exponent,int32_t *significant){
    uint32_t local[2],a;
#if UINTPTR_MAX > UINT32_MAX
    a=nocturneLibcStreamLocalAddress(local,8);
#else
    a=(uint32_t)(uintptr_t)local;
#endif
    uint32_t p=(uint32_t)ps2LibcBigintFromDoubleBits(c,bits,a,a+4);
#if UINTPTR_MAX > UINT32_MAX
    nocturneLibcStreamEndLocal();
#endif
    *exponent=s32(local[0]);*significant=s32(local[1]);return p;
}
uint64_t ps2LibcDtoa(uint64_t context,uint64_t valueBits,uint64_t mode,uint64_t precision,uint64_t decimalPoint,uint64_t sign,uint64_t endPointer)
{
  int32_t bVar1;
  int32_t bVar2;
  int32_t iVar3;
  int32_t iVar4;
  uint32_t pvVar5;
  uint64_t uVar6;
  uint64_t uVar7;
  uint64_t uVar8;
  int8_t cVar9;
  uint64_t uVar10;
  uint32_t uVar11;
  uint32_t powerPointer;
  int32_t iVar13;
  uint32_t uVar14;
  int32_t iVar15;
  uint32_t uVar16;
  uint32_t digits;
  uint32_t cursor;
  uint32_t carryCursor;
  uint64_t uVar20;
  int32_t binaryExponent;
  int32_t significantBits;
  uint32_t formatMode;
  uint32_t requestedDigits;
  uint32_t decimalPointOut;
  uint32_t endOut;
  int32_t numeratorTwos;
  int32_t numeratorFives;
  uint32_t digitLimit;
  uint32_t savedDigitLimit;
  uint32_t reducedDigitLimit;
  uint32_t savedDecimalExponent;
  int32_t estimateNeedsCheck;
  int32_t leftRight;
  int32_t denominatorTwos;
  uint32_t denominatorFives;
  int32_t subnormal;
  uint32_t numerator;
  uint32_t lowerMargin=0; /* Unread on quick paths with no margin record. */
  uint32_t upperMargin;
  uint32_t denominator;
  
  uint32_t param_3=(uint32_t)mode,param_4=(uint32_t)precision;
  uint32_t param_5=(uint32_t)decimalPoint,param_6=(uint32_t)sign,param_7=(uint32_t)endPointer;
  uint32_t reent=(uint32_t)context;
  iVar3 = s32(word(reent+64));
  formatMode = param_3;
  requestedDigits = param_4;
  decimalPointOut = param_5;
  endOut = param_7;
  if (iVar3 != 0) {
    put((uint32_t)iVar3+4,word(reent+68));
    put((uint32_t)iVar3+8,1u << (word(reent+68)&31));
    ps2LibcBigintFree(context,iVar3);
    put(reent+64,0);
  }
  uVar10 = sx((uint32_t)(valueBits>>32));
  if (uVar10>>63) {
    put(param_6,1);
    valueBits = valueBits & 0xffffffff | (uVar10 & 0x7fffffff) << 0x20;
  }
  else {
    put(param_6,0);
  }
  uVar11 = (uint32_t)(valueBits >> 0x20);
  if ((uVar11 & 0x7ff00000) == 0x7ff00000) {
    put(decimalPointOut,9999);
    if ((valueBits & 0xfffffffffffff) == 0) {
      digits = 0x54b880;
    }
    else {
      digits = 0x54b890;
    }
    if (endOut == 0) {
      return sx(digits);
    }
    cursor = digits + 8;
    if (byte(digits+3) == '\0') {
      cursor = digits + 3;
    }
    put(endOut,cursor);
    return sx(digits);
  }
  iVar3 = ps2SoftDoubleCompare(valueBits,0);
  if (iVar3 == 0) {
    put(decimalPointOut,1);
    if (endOut == 0) {
      return 0x54b898;
    }
    put(endOut,0x54b899);
    return 0x54b898;
  }
  numerator = fromDouble(context,valueBits,&binaryExponent,&significantBits);
  iVar3 = significantBits;
  uVar14 = uVar11 >> 0x14 & 0x7ff;
  if (uVar14 == 0) {
    iVar4 = significantBits + binaryExponent;
    iVar15 = iVar4 + 0x432;
    if (iVar15 < 0x21) {
      uVar11 = (uint32_t)valueBits << (-iVar15 & 0x1fU);
    }
    else {
      uVar11 = uVar11 << (-iVar15 & 0x1fU) | (uint32_t)valueBits >> (iVar4 + 0x412U & 0x1f);
    }
    uVar10 = ps2SoftDoubleFromInt(uVar11);
    if ((int32_t)uVar11 < 0) {
      uVar10 = ps2SoftDoubleAdd(uVar10,0x41f0000000000000);
    }
    subnormal = 1;
    uVar14 = iVar4 - 1;
    uVar20 = uVar10 & 0xffffffff | (uint64_t)((uint32_t)(uVar10>>32)-0x1f00000u)<<32;
  }
  else {
    uVar14 = uVar14 - 0x3ff;
    subnormal = 0;
    uVar20 = (valueBits&UINT64_C(0xffffffff)) |
       ((uint64_t)(((uint32_t)(valueBits>>32)&0xfffffu)|0x3ff00000u)<<32);
  }
  uVar20 = ps2SoftDoubleSub(uVar20,0x3ff8000000000000);
  uVar20 = ps2SoftDoubleMul(uVar20,qword(0x0054b8a0));
  uVar20 = ps2SoftDoubleAdd(uVar20,qword(0x0054b8a8));
  uVar6 = ps2SoftDoubleFromInt(uVar14);
  uVar6 = ps2SoftDoubleMul(uVar6,qword(0x0054b8b0));
  uVar20 = ps2SoftDoubleAdd(uVar20,uVar6);
  uVar11 = ps2SoftDoubleToInt(uVar20);
  iVar4 = ps2SoftDoubleCompare(uVar20,0);
  if (iVar4 < 0) {
    uVar6 = ps2SoftDoubleFromInt(uVar11);
    iVar4 = ps2SoftDoubleCompare(uVar20,uVar6);
    if (iVar4 != 0) {
      uVar11 = uVar11 - 1;
    }
  }
  estimateNeedsCheck = 1;
  if (uVar11 < 0x17) {
    estimateNeedsCheck = 0;
    iVar4 = ps2SoftDoubleCompare(valueBits,qword(0x54b930+(uVar11<<3)));
    if (iVar4 < 0) {
      uVar11 = uVar11 - 1;
    }
  }
  denominatorTwos = (iVar3 - uVar14) + -1;
  if (denominatorTwos < 0) {
    numeratorTwos = -denominatorTwos;
    denominatorTwos = 0;
  }
  else {
    numeratorTwos = 0;
  }
  if ((int32_t)uVar11 < 0) {
    numeratorFives = s32(0u-uVar11);
    numeratorTwos = numeratorTwos - uVar11;
    denominatorFives = 0;
  }
  else {
    numeratorFives = 0;
    denominatorTwos = denominatorTwos + uVar11;
    denominatorFives = uVar11;
  }
  if (9 < formatMode) {
    formatMode = 0;
  }
  bVar1 = 5 < (int32_t)formatMode;
  if (bVar1) {
    formatMode = formatMode - 4;
  }
  leftRight = 1;
  reducedDigitLimit = 0xffffffff;
  digitLimit = 0xffffffff;
  uVar16 = requestedDigits;
  switch(formatMode) {
  case 0:
  case 1:
    requestedDigits = 0;
    uVar14 = 0x12;
    uVar16 = requestedDigits;
    break;
  case 2:
    leftRight = 0;
  case 4:
    digitLimit = 1;
    uVar14 = digitLimit;
    uVar16 = digitLimit;
    reducedDigitLimit = digitLimit;
    if (0 < (int32_t)requestedDigits) {
      uVar14 = requestedDigits;
      uVar16 = requestedDigits;
      digitLimit = requestedDigits;
      reducedDigitLimit = requestedDigits;
    }
    break;
  case 3:
    leftRight = 0;
  case 5:
    reducedDigitLimit = requestedDigits + uVar11;
    digitLimit = reducedDigitLimit + 1;
    uVar14 = digitLimit;
    if ((int32_t)digitLimit < 1) {
      uVar14 = 1;
    }
  }
  requestedDigits = uVar16;
  put(reent+68,0);
  iVar3 = 4;
  if (0x17 < uVar14) {
    iVar4 = 0;
    do {
      iVar3 = iVar3 * 2;
      iVar4 = iVar4 + 1;
    } while (iVar3 + 0x14U <= uVar14);
    put(reent+68,(uint32_t)iVar4);
  }
  digits = (uint32_t)ps2LibcBigintAllocate(context,word(reent+68));
  put(reent+64,digits);
  uVar14 = uVar11;
  uVar16 = digitLimit;
  if ((0xe < digitLimit) || (bVar1)) {
LAB_002d8ca4:
    digitLimit = uVar16;
    if ((binaryExponent < 0) || (0xe < (int32_t)uVar14)) {
      bVar1 = (int32_t)formatMode < 2;
      lowerMargin = (uint32_t)0x0;
      upperMargin = (uint32_t)0x0;
      iVar3 = numeratorTwos;
      iVar13 = numeratorFives;
      if (leftRight != 0) {
        if (bVar1) {
          uVar11 = binaryExponent + 0x433;
          if (subnormal == 0) {
            uVar11 = 0x36 - significantBits;
          }
        }
        else {
          iVar4 = digitLimit - 1;
          iVar13 = numeratorFives - iVar4;
          if (numeratorFives < iVar4) {
            iVar13 = 0;
            iVar4 = iVar4 - numeratorFives;
            numeratorFives = numeratorFives + iVar4;
            denominatorFives = denominatorFives + iVar4;
          }
          uVar11 = digitLimit;
          if ((int32_t)digitLimit < 0) {
            uVar11 = 0;
            iVar3 = numeratorTwos - digitLimit;
          }
        }
        denominatorTwos = denominatorTwos + uVar11;
        upperMargin = (uint32_t)ps2LibcBigintFromWord(context,1);
        numeratorTwos = numeratorTwos + uVar11;
      }
      if ((0 < iVar3) && (0 < denominatorTwos)) {
        iVar4 = denominatorTwos;
        if (iVar3 < denominatorTwos) {
          iVar4 = iVar3;
        }
        denominatorTwos = denominatorTwos - iVar4;
        iVar3 = iVar3 - iVar4;
        numeratorTwos = numeratorTwos - iVar4;
      }
      if (0 < numeratorFives) {
        if (leftRight == 0) {
          numerator = (uint32_t)ps2LibcBigintPowerOfFive(context,numerator,numeratorFives);
        }
        else {
          if (0 < iVar13) {
            uVar8 = ps2LibcBigintPowerOfFive(context,upperMargin,iVar13);
            upperMargin = (uint32_t)uVar8;
            pvVar5 = (uint32_t)ps2LibcBigintMultiply(context,uVar8,numerator);
            ps2LibcBigintFree(context,numerator);
            numerator = pvVar5;
          }
          if (numeratorFives - iVar13 != 0) {
            numerator = (uint32_t)ps2LibcBigintPowerOfFive(context,numerator,numeratorFives - iVar13);
          }
        }
      }
      uVar8 = ps2LibcBigintFromWord(context,1);
      denominator = (uint32_t)uVar8;
      if (0 < (int32_t)denominatorFives) {
        denominator = (uint32_t)ps2LibcBigintPowerOfFive(context,uVar8,denominatorFives);
      }
      bVar2 = 0;
      if (((bVar1) && ((valueBits & 0xfffffffffffff) == 0)) &&
         (((int64_t)valueBits >> 0x20 & 0x7ff00000U) != 0)) {
        bVar2 = 1;
        numeratorTwos = numeratorTwos + 1;
        denominatorTwos = denominatorTwos + 1;
      }
      if (denominatorFives == 0) {
        uVar11 = denominatorTwos + 1;
      }
      else {
        uVar11 = ps2CountLeadingZeroBits(s32(word(denominator+(word(denominator+16)<<2)+16)));
        uVar11 = denominatorTwos - uVar11;
      }
      iVar13 = 0;
      if ((uVar11 & 0x1f) != 0) {
        iVar13 = 0x20 - (uVar11 & 0x1f);
      }
      if (iVar13 < 5) {
        if (iVar13 < 4) {
          iVar13 = iVar13 + 0x1c;
          goto LAB_002d90e0;
        }
      }
      else {
        iVar13 = iVar13 + -4;
LAB_002d90e0:
        denominatorTwos = denominatorTwos + iVar13;
        numeratorTwos = numeratorTwos + iVar13;
        iVar3 = iVar3 + iVar13;
      }
      if (0 < numeratorTwos) {
        numerator = (uint32_t)ps2LibcBigintShiftLeft(context,numerator,numeratorTwos);
      }
      if (0 < denominatorTwos) {
        denominator = (uint32_t)ps2LibcBigintShiftLeft(context,denominator,denominatorTwos);
      }
      if ((estimateNeedsCheck != 0) && (iVar13 = ps2CompareLimbArrays(at((uint32_t)numerator),at((uint32_t)denominator)), iVar13 < 0)) {
        numerator = (uint32_t)ps2LibcBigintMultiplyAdd(context,numerator,10,0);
        uVar14 = uVar14 - 1;
        if (leftRight != 0) {
          upperMargin = (uint32_t)ps2LibcBigintMultiplyAdd(context,upperMargin,10,0);
        }
        digitLimit = reducedDigitLimit;
      }
      if (((int32_t)digitLimit < 1) && (2 < (int32_t)formatMode)) {
        if ((int32_t)digitLimit < 0) goto LAB_002d91d4;
        denominator = (uint32_t)ps2LibcBigintMultiplyAdd(context,denominator,5,0);
        iVar3 = ps2CompareLimbArrays(at((uint32_t)numerator),at((uint32_t)denominator));
        uVar11 = uVar14;
        goto joined_r0x002d91c8;
      }
      iVar13 = 1;
      cursor = digits;
      if (leftRight != 0) {
        if (0 < iVar3) {
          upperMargin = (uint32_t)ps2LibcBigintShiftLeft(context,upperMargin,iVar3);
        }
        lowerMargin = upperMargin;
        if (bVar2) {
          upperMargin = (uint32_t)ps2LibcBigintAllocate(context,word(upperMargin+4));
          ps2Memcpy(at(upperMargin+12),at(lowerMargin+12),
                    s32(word(lowerMargin+16)) * 4 + 8);
          upperMargin = (uint32_t)ps2LibcBigintShiftLeft(context,upperMargin,1);
        }
        uVar11 = 1;
        do {
          iVar3 = (uint32_t)ps2LibcBigintQuotientRemainder(numerator,denominator);
          uVar16 = iVar3 + 0x30;
          iVar13 = ps2CompareLimbArrays(at((uint32_t)numerator),at((uint32_t)lowerMargin));
          uVar8 = ps2LibcBigintDifference(context,denominator,upperMargin);
          iVar4 = 1;
          if (s32(word((uint32_t)uVar8+12)) == 0) {
            iVar4 = ps2CompareLimbArrays(at(numerator),at((uint32_t)uVar8));
          }
          ps2LibcBigintFree(context,uVar8);
          cVar9 = (int8_t)uVar16;
          if (((iVar4 == 0) && (formatMode == 0)) && ((valueBits & 1) == 0)) {
            if (uVar16 != 0x39) {
              putByte(cursor,cVar9 + (0 < iVar13));
              goto LAB_002d9540;
            }
LAB_002d9418:
            putByte(cursor,'9');
            cursor = cursor + 1;
            goto LAB_002d94e8;
          }
          if ((iVar13 < 0) || (((iVar13 == 0 && (formatMode == 0)) && ((valueBits & 1) == 0)))) {
            if (iVar4 < 1) {
              putByte(cursor,cVar9);
              goto LAB_002d9540;
            }
            numerator = (uint32_t)ps2LibcBigintShiftLeft(context,numerator,1);
            iVar13 = ps2CompareLimbArrays(at((uint32_t)numerator),at((uint32_t)denominator));
            if (iVar13 < 1) {
              if (iVar13 != 0) {
                putByte(cursor,cVar9);
                goto LAB_002d9540;
              }
              if ((uVar16 & 1) == 0) {
                putByte(cursor,cVar9);
                goto LAB_002d9540;
              }
            }
            if (iVar3 + 0x31 == 0x3a) goto LAB_002d9418;
            putByte(cursor,(int8_t)(iVar3 + 0x31));
            goto LAB_002d9540;
          }
          if (0 < iVar4) {
            if (uVar16 == 0x39) goto LAB_002d9418;
            putByte(cursor,cVar9 + '\x01');
            goto LAB_002d9540;
          }
          putByte(cursor,cVar9);
          cursor = cursor + 1;
          if (uVar11 == digitLimit) goto LAB_002d948c;
          numerator = (uint32_t)ps2LibcBigintMultiplyAdd(context,numerator,10,0);
          if (lowerMargin == upperMargin) {
            lowerMargin = (uint32_t)ps2LibcBigintMultiplyAdd(context,upperMargin,10,0);
            upperMargin = lowerMargin;
          }
          else {
            lowerMargin = (uint32_t)ps2LibcBigintMultiplyAdd(context,lowerMargin,10,0);
            upperMargin = (uint32_t)ps2LibcBigintMultiplyAdd(context,upperMargin,10,0);
          }
          uVar11 = uVar11 + 1;
        } while( 1 );
      }
      while( 1 ) {
        iVar3 = (uint32_t)ps2LibcBigintQuotientRemainder(numerator,denominator);
        uVar16 = iVar3 + 0x30;
        putByte(cursor,(int8_t)uVar16);
        cursor = cursor + 1;
        if ((int32_t)digitLimit <= iVar13) break;
        numerator = (uint32_t)ps2LibcBigintMultiplyAdd(context,numerator,10,0);
        iVar13 = iVar13 + 1;
      }
LAB_002d948c:
      numerator = (uint32_t)ps2LibcBigintShiftLeft(context,numerator,1);
      iVar3 = ps2CompareLimbArrays(at((uint32_t)numerator),at((uint32_t)denominator));
      if (iVar3 < 1) {
        if (iVar3 == 0) {
          if ((uVar16 & 1) != 0) goto LAB_002d94e8;
          cursor = cursor + -1;
        }
        else {
          cursor = cursor + -1;
        }
        for (; byte(cursor) == '0'; cursor = cursor + -1) {
        }
LAB_002d9540:
        cursor = cursor + 1;
      }
      else {
LAB_002d94e8:
        do {
          cursor = cursor + -1;
          if (byte(cursor) != '9') {
            putByte(cursor,byte(cursor) + '\x01');
            goto LAB_002d9540;
          }
        } while (cursor != digits);
        uVar14 = uVar14 + 1;
        putByte(digits,'1');
        cursor = digits + 1;
      }
    }
    else {
      uVar20 = qword(0x54b930+(uVar14<<3));
      uVar16 = 1;
      cursor = digits;
      uVar11 = uVar14;
      if ((-1 < (int32_t)requestedDigits) || (0 < (int32_t)digitLimit)) {
        do {
          uVar6 = ps2SoftDoubleDiv(valueBits,uVar20);
          uVar14 = ps2SoftDoubleToInt(uVar6);
          uVar6 = ps2SoftDoubleFromInt(uVar14);
          uVar6 = ps2SoftDoubleMul(uVar6,uVar20);
          uVar6 = ps2SoftDoubleSub(valueBits,uVar6);
          putByte(cursor,(int8_t)uVar14 + '0');
          cursor = cursor + 1;
          if (uVar16 == digitLimit) {
            uVar6 = ps2SoftDoubleAdd(uVar6,uVar6);
            iVar3 = ps2SoftDoubleCompare(uVar6,uVar20);
            carryCursor = cursor;
            if ((0 < iVar3) ||
               ((iVar3 = ps2SoftDoubleCompare(uVar6,uVar20), iVar3 == 0 && ((uVar14 & 1) != 0))))
            goto LAB_002d8dd8;
            break;
          }
          valueBits = ps2SoftDoubleMul(0x4024000000000000,uVar6);
          iVar3 = ps2SoftDoubleCompare(valueBits,0);
          uVar16 = uVar16 + 1;
        } while (iVar3 != 0);
        goto LAB_002d9584;
      }
      upperMargin = (uint32_t)0x0;
      denominator = (uint32_t)0x0;
      if ((int32_t)digitLimit < 0) goto LAB_002d91d4;
      uVar20 = ps2SoftDoubleMul(uVar20,0x4014000000000000);
      iVar3 = ps2SoftDoubleCompare(valueBits,uVar20);
joined_r0x002d91c8:
      if (0 < iVar3) goto LAB_002d91e0;
LAB_002d91d4:
      uVar14 = ~requestedDigits;
      cursor = digits;
    }
  }
  else {
    savedDigitLimit = digitLimit;
    iVar3 = 2;
    savedDecimalExponent = uVar11;
    if ((int32_t)uVar11 < 1) {
      uVar14 = 0u-uVar11;
      uVar20 = valueBits;
      if (uVar14 != 0) {
        uVar16 = (int32_t)uVar14 >> 4;
        uVar20 = ps2SoftDoubleMul(qword(0x54b930+((uVar14&15)<<3)),valueBits);
        if (uVar16 != 0) {
          powerPointer = 0x54b9f8;
          do {
            uVar14 = uVar16 & 1;
            uVar16 = (int32_t)uVar16 >> 1;
            if (uVar14 != 0) {
              iVar3 = iVar3 + 1;
              uVar20 = ps2SoftDoubleMul(qword(powerPointer),uVar20);
            }
            powerPointer += 8;
          } while (uVar16 != 0);
        }
      }
    }
    else {
      uVar14 = (int32_t)uVar11 >> 4;
      uVar20 = qword(0x54b930+((uVar11&15)<<3));
      uVar10 = valueBits;
      if ((uVar14 & 0x10) != 0) {
        uVar14 = uVar14 & 0xf;
        iVar3 = 3;
        uVar10 = ps2SoftDoubleDiv(valueBits,qword(0x0054ba18));
      }
      if (uVar14 != 0) {
        powerPointer = 0x54b9f8;
        do {
          uVar16 = uVar14 & 1;
          uVar14 = (int32_t)uVar14 >> 1;
          if (uVar16 != 0) {
            iVar3 = iVar3 + 1;
            uVar20 = ps2SoftDoubleMul(uVar20,qword(powerPointer));
          }
          powerPointer += 8;
        } while (uVar14 != 0);
      }
      uVar20 = ps2SoftDoubleDiv(uVar10,uVar20);
    }
    if (((estimateNeedsCheck != 0) && (iVar13 = ps2SoftDoubleCompare(uVar20,0x3ff0000000000000), iVar13 < 0))
       && (0 < (int32_t)digitLimit)) {
      uVar14 = savedDecimalExponent;
      uVar16 = savedDigitLimit;
      if ((int32_t)reducedDigitLimit < 1) goto LAB_002d8ca4;
      uVar11 = uVar11 - 1;
      digitLimit = reducedDigitLimit;
      iVar3 = iVar3 + 1;
      uVar20 = ps2SoftDoubleMul(0x4024000000000000,uVar20);
    }
    uVar6 = ps2SoftDoubleFromInt(iVar3);
    uVar6 = ps2SoftDoubleMul(uVar6,uVar20);
    uVar6 = ps2SoftDoubleAdd(uVar6,0x401c000000000000);
    uVar10 = uVar6 & 0xffffffff | (uint64_t)((uint32_t)(uVar6>>32)-0x3400000u)<<32;
    if (digitLimit != 0) {
      if (leftRight != 0) {
        iVar3 = 0;
        uVar6 = ps2SoftDoubleDiv(0x3fe0000000000000,qword(0x54b928+(digitLimit<<3)));
        uVar6 = ps2SoftDoubleSub(uVar6,uVar10);
        cursor = digits;
        while( 1 ) {
          iVar13 = ps2SoftDoubleToInt(uVar20);
          uVar7 = ps2SoftDoubleFromInt(iVar13);
          uVar20 = ps2SoftDoubleSub(uVar20,uVar7);
          putByte(cursor,(int8_t)iVar13 + '0');
          cursor = cursor + 1;
          iVar13 = ps2SoftDoubleCompare(uVar20,uVar6);
          if (iVar13 < 0) break;
          uVar7 = ps2SoftDoubleSub(0x3ff0000000000000,uVar20);
          iVar13 = ps2SoftDoubleCompare(uVar7,uVar6);
          carryCursor = cursor;
          if (iVar13 < 0) goto LAB_002d8dd8;
          iVar3 = iVar3 + 1;
          uVar14 = savedDecimalExponent;
          uVar16 = savedDigitLimit;
          if ((int32_t)digitLimit <= iVar3) goto LAB_002d8ca4;
          uVar6 = ps2SoftDoubleMul(0x4024000000000000,uVar6);
          uVar20 = ps2SoftDoubleMul(0x4024000000000000,uVar20);
        }
        goto LAB_002d9584;
      }
      uVar14 = 1;
      uVar6 = ps2SoftDoubleMul(qword(0x54b928+(digitLimit<<3)),uVar10);
      cursor = digits;
      while( 1 ) {
        iVar3 = ps2SoftDoubleToInt(uVar20);
        uVar7 = ps2SoftDoubleFromInt(iVar3);
        uVar20 = ps2SoftDoubleSub(uVar20,uVar7);
        putByte(cursor,(int8_t)iVar3 + '0');
        if (uVar14 == digitLimit) break;
        uVar14 = uVar14 + 1;
        uVar20 = ps2SoftDoubleMul(0x4024000000000000,uVar20);
        cursor = cursor + 1;
      }
      uVar7 = ps2SoftDoubleAdd(0x3fe0000000000000,uVar6);
      iVar3 = ps2SoftDoubleCompare(uVar20,uVar7);
      carryCursor = cursor + 1;
      if (0 < iVar3) {
LAB_002d8dd8:
        do {
          cursor = carryCursor;
          carryCursor = cursor + -1;
          cVar9 = byte(carryCursor);
          if (byte(carryCursor) != '9') goto LAB_002d8e08;
        } while (carryCursor != digits);
        putByte(digits,'0');
        cVar9 = '0';
        uVar11 = uVar11 + 1;
LAB_002d8e08:
        putByte(carryCursor,cVar9 + '\x01');
        goto LAB_002d9584;
      }
      uVar6 = ps2SoftDoubleSub(0x3fe0000000000000,uVar6);
      iVar3 = ps2SoftDoubleCompare(uVar20,uVar6);
      uVar14 = savedDecimalExponent;
      uVar16 = savedDigitLimit;
      if (iVar3 < 0) {
        for (; byte(cursor) == '0'; cursor = cursor + -1) {
        }
        cursor = cursor + 1;
        goto LAB_002d9584;
      }
      goto LAB_002d8ca4;
    }
    upperMargin = (uint32_t)0x0;
    denominator = (uint32_t)0x0;
    uVar20 = ps2SoftDoubleSub(uVar20,0x4014000000000000);
    iVar3 = ps2SoftDoubleCompare(uVar20,uVar10);
    if (iVar3 < 1) {
      uVar6 = ps2SoftDoubleSub(0,uVar10);
      iVar3 = ps2SoftDoubleCompare(uVar20,uVar6);
      uVar14 = savedDecimalExponent;
      uVar16 = savedDigitLimit;
      if (-1 < iVar3) goto LAB_002d8ca4;
      goto LAB_002d91d4;
    }
LAB_002d91e0:
    uVar14 = uVar11 + 1;
    putByte(digits,'1');
    cursor = digits + 1;
  }
  ps2LibcBigintFree(context,denominator);
  uVar11 = uVar14;
  if (upperMargin != (uint32_t)0x0) {
    if ((lowerMargin != (uint32_t)0x0) && (lowerMargin != upperMargin)) {
      ps2LibcBigintFree(context,lowerMargin);
    }
    ps2LibcBigintFree(context,upperMargin);
  }
LAB_002d9584:
  ps2LibcBigintFree(context,numerator);
  putByte(cursor,'\0');
  put(decimalPointOut,uVar11 + 1);
  if (endOut != 0) {
    put(endOut,cursor);
  }
  return sx(digits);
}


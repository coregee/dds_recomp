#ifndef NOCTURNE_COMPILER_NUMERIC_H
#define NOCTURNE_COMPILER_NUMERIC_H
#include <stdint.h>
/* Signed arguments/results are represented by their original EE bit patterns. */
uint64_t ps2Signed64Divide(uint64_t dividend,uint64_t divisor);
uint64_t ps2Signed64Remainder(uint64_t dividend,uint64_t divisor);
uint64_t ps2Unsigned64Divide(uint64_t dividend,uint64_t divisor);
uint64_t ps2Unsigned64Remainder(uint64_t dividend,uint64_t divisor);
uint64_t ps2SoftDoubleDiv(uint64_t left,uint64_t right);
uint64_t ps2SoftDoubleFromInt64(uint64_t value);
uint64_t ps2SoftDoubleToUint64(uint64_t bits);
uint64_t ps2SdkRoundDoubleWord(uint64_t bits);
/* Original BREAK7 raises a CPU exception; no ordinary return is specified. */
_Noreturn void nocturneCompilerArithmeticTrap(uint32_t code);
#endif

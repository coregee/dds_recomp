#ifndef NOCTURNE_SCRIPT_OPS_H
#define NOCTURNE_SCRIPT_OPS_H
#include <stdint.h>
void scrCodeFunc_2Operation(uint64_t work,uint64_t operation);
uint64_t scrCodeFunc_Add(uint64_t work);
uint64_t scrCodeFunc_Sub(uint64_t work);
uint64_t scrCodeFunc_Mul(uint64_t work);
uint64_t scrCodeFunc_Div(uint64_t work);
uint64_t scrCodeFunc_Or(uint64_t work);
uint64_t scrCodeFunc_And(uint64_t work);
uint64_t scrCodeFunc_EQ(uint64_t work);
uint64_t scrCodeFunc_NEQ(uint64_t work);
uint64_t scrCodeFunc_S(uint64_t work);
uint64_t scrCodeFunc_L(uint64_t work);
uint64_t scrCodeFunc_SE(uint64_t work);
uint64_t scrCodeFunc_LE(uint64_t work);
uint64_t scrCodeFunc_Not(uint64_t work);
uint64_t scrCodeFunc_If(uint64_t work);
#endif

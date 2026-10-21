#ifndef NOCTURNE_SCRIPT_STACK_H
#define NOCTURNE_SCRIPT_STACK_H
#include <stdint.h>
void scrPushInt(uint64_t work,uint64_t value);
void scrPushFloatBits(uint64_t work,uint32_t bits);
void scrPushStr(uint64_t work,uint64_t value);
void scrPushRet(uint64_t work,uint64_t value);
uint32_t scrPopFloatBits(uint64_t work);
uint64_t scrCodeFunc_PushI(uint64_t work);
uint64_t scrCodeFunc_PushIS(uint64_t work);
uint64_t scrCodeFunc_PushF(uint64_t work);
uint64_t scrCodeFunc_PushIX(uint64_t work);
uint64_t scrCodeFunc_PushFX(uint64_t work);
uint64_t scrCodeFunc_PushLIX(uint64_t work);
uint64_t scrCodeFunc_PushLFX(uint64_t work);
uint64_t scrCodeFunc_PushSTR(uint64_t work);
uint64_t scrCodeFunc_PushReg(uint64_t work);
uint64_t scrCodeFunc_PopIX(uint64_t work);
uint64_t scrCodeFunc_PopFX(uint64_t work);
uint64_t scrCodeFunc_PopLIX(uint64_t work);
uint64_t scrCodeFunc_PopLFX(uint64_t work);
uint64_t scrCodeFunc_Proc(uint64_t work);
uint64_t scrCodeFunc_Jump(uint64_t work);
uint64_t scrCodeFunc_Call(uint64_t work);
uint64_t scrCodeFunc_Run(uint64_t work);
#endif

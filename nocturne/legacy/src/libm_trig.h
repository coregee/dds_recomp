#pragma once
#include <stdint.h>
float ps2LibmCosFloat(float x);
float ps2LibmSinFloat(float x);
int32_t ps2LibmRemPio2Float(float x,float *y);
float ps2LibmKernelCosFloat(float x,float y);
float ps2LibmKernelSinFloat(float x,float y,uint64_t tail);
int32_t ps2LibmKernelRemPio2Float(const float *x,float *y,int32_t exponent,int32_t count,int32_t precision,const int32_t *table);
float ps2LibmFloorFloat(float x);
float ps2LibmScalbnFloat(float x,uint64_t exponent);
void sdfRotationYFloat(float angle);
void sdfRotationZFloat(float angle);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolveLibmTrigAddress(uint32_t address);
#endif

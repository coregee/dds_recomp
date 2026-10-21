#ifndef NOCTURNE_EE_VU_ROTATION_H
#define NOCTURNE_EE_VU_ROTATION_H
#include <stdint.h>
/* Processor boundaries. Low32 result + bit32 ACC overflow; only the latter
 * status bit is retained because it changes subsequent MAC result values. */
uint64_t EE_ROT_VU_ADD(uint32_t a,uint32_t b);
uint64_t EE_ROT_VU_SUB(uint32_t a,uint32_t b);
uint64_t EE_ROT_VU_MUL(uint32_t a,uint32_t b);
uint64_t EE_ROT_VU_MAC(uint32_t acc,uint32_t a,uint32_t b,uint32_t overflow,uint32_t subtract);
uint32_t EE_ROT_VU_RSQRT(uint32_t a,uint32_t b);
void EE_ROT_VU_READ(unsigned reg,uint32_t words[4]);
void EE_ROT_VU_WRITE(unsigned reg,const uint32_t words[4]);
void EE_ROT_ACC_READ(uint32_t words[4],uint32_t overflow[4]);
void EE_ROT_ACC_WRITE(const uint32_t words[4],const uint32_t overflow[4]);
void EE_ROT_Q_WRITE(uint32_t bits);
#endif

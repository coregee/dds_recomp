#ifndef NOCTURNE_EE_VU_MINMAX_H
#define NOCTURNE_EE_VU_MINMAX_H
#include <stdint.h>
/* VU MINI/MAX choose an original raw word, including signed zero, denormals
 * and exponent255 encodings. COP1 comparison normalization is different. */
static inline uint32_t EE_VU_MINMAX_BITS(uint32_t a,uint32_t b,unsigned minimum){
 uint32_t ka=a&0x80000000u?~a:a^0x80000000u,kb=b&0x80000000u?~b:b^0x80000000u;
 return minimum?(ka<kb?a:b):(ka>kb?a:b);
}
#endif

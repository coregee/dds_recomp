#pragma once
#include <stdint.h>
/* Macro-mode clip history and CFC2 control18 boundary, separate from timing. */
void EE_VU_CLIP(unsigned source,unsigned threshold);
uint32_t EE_VU_CLIP_READ(void);

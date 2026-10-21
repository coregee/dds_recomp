#ifndef NOCTURNE_PATH_ROTATION_H
#define NOCTURNE_PATH_ROTATION_H
#include <stdint.h>
void dds3PathBasicControlGetRot(uint64_t control);
/* Native descriptive roles; live vector/ACC/Q interfaces are processor state. */
void ps2QuaternionBlendNormalized(float rate);
void ps2QuaternionNormalize(void);
#endif

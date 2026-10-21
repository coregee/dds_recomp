#ifndef NOCTURNE_MATERIAL_MOTION_SCALARS_H
#define NOCTURNE_MATERIAL_MOTION_SCALARS_H
#include <stdint.h>
/* Partial material/node views in stable ordinary, aligned backed RAM.
 * All floating arguments/results use raw EE words in the host C interface.
 * Target constant/scalar ABI uses F12/F0; blend callback uses F12/F13.
 * Node raw addresses retain their original 32-bit representation. */
void sdfMatSetAmbient(void *material,uint32_t value);
void sdfMatSetDiffuse(void *material,uint32_t value);
void sdfMatSetSpecular(void *material,uint32_t value);
void sdfMatSetConstant(void *material,uint32_t value_bits);
uint32_t ps2MotionInterpolateScalar(const void *key_pair);
void ps2MotionApplyMaterialConstant(void *node,uint32_t frame_bits);
void ps2MotionBlendMaterialConstant(void *node,uint32_t frame_bits,uint32_t blend_bits);
#endif

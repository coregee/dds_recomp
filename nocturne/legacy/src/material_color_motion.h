#ifndef NOCTURNE_MATERIAL_COLOR_MOTION_H
#define NOCTURNE_MATERIAL_COLOR_MOTION_H
#include <stdint.h>
/* Host float arguments retain raw PS2 encodings; target callbacks use F12/F13.
 * Key pairs contain two raw32 addresses and one raw32 interpolation value. */
uint32_t ps2MotionInterpolateColor(const void *key_pair);
#define NOCTURNE_COLOR_DECL(role) \
void ps2MotionApplyMaterial##role(void *node,uint32_t frame_bits); \
void ps2MotionBlendMaterial##role(void *node,uint32_t frame_bits,uint32_t blend_bits);
NOCTURNE_COLOR_DECL(Diffuse)
NOCTURNE_COLOR_DECL(Ambient)
NOCTURNE_COLOR_DECL(Specular)
NOCTURNE_COLOR_DECL(Word28)
NOCTURNE_COLOR_DECL(Word18)
#undef NOCTURNE_COLOR_DECL
#endif

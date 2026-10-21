/* Verified native EE interfaces; ambient processor/frame state is explicit. */
#ifndef NOCTURNE_MAGATUHI_RUNTIME_H
#define NOCTURNE_MAGATUHI_RUNTIME_H
#include <stdint.h>
void nocturneEffectHostActivate(void);
void nocturneEffectHostDeactivate(void);
void ps2EffectMagatuhiDraw_001A52B0(uint64_t owner);
void ps2EffectMagatuhiDrawHistory_001A54E0(uint64_t data);
void ps2EffectMagatuhiSetPosition_001A5920(uint64_t data,uint64_t index,uint64_t vector);
void ps2EffectMagatuhiSetColour_001A5C98(uint64_t data,uint64_t index,uint64_t colour);
void ps2EffectMagatuhiResetHistory_001A5D88(uint64_t data,uint64_t index);
void ps2EffectMagatuhiTriangleInitializeEntry_001A5FA0(uint64_t object,uint64_t index);
void ps2EffectMagatuhiTriangleUpdateAndDraw_001A61A0(uint64_t object);
void ps2EffectMagatuhiGeometryInitializeEntry_001A6940(uint64_t object,uint64_t index);
void ps2EffectMagatuhiGeometryUpdateAndDraw_001A6C48(uint64_t object);
void ps2EffectMagatuhiOrbitInitializeEntry_001A7308(uint64_t object,uint64_t index);
void ps2EffectMagatuhiOrbitUpdateAndDraw_001A7450(uint64_t object);
void ps2EffectMagatuhiExpandingOrbitInitializeEntry_001A7B38(uint64_t object,uint64_t index);
void ps2EffectMagatuhiExpandingOrbitUpdateAndDraw_001A7C90(uint64_t object);
void ps2EffectMagatuhiWobbleInitializeEntry_001A83E0(uint64_t object,uint64_t index);
void ps2EffectMagatuhiWobbleUpdateAndDraw_001A85D0(uint64_t object);
void ps2EffectMagatuhiUpdateAndDraw_001A8C40(uint64_t object);
uint64_t ps2EffectMagatuhiInterpolateTriangle_001ABE38(uint64_t triangles,uint64_t index,uint64_t output);
uint64_t ps2EffectMagatuhiTriangleAt_001AC090(uint64_t triangles,uint64_t index);
void ps2BillboardBuildUploadReference(uint64_t arg0,uint64_t arg1,uint64_t arg2);
void ps2BillboardBuildMatrixPacket(uint64_t arg0,uint64_t arg1);
uint64_t ps2BillboardBuildGeometryPacket(uint64_t arg0,uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4,uint64_t arg5);
#endif

#pragma once
#include <stdint.h>
void ps2MajorEffectSetPosition(uint64_t object,uint64_t vector);
void ps2BillboardSetPositionVector(uint64_t object,uint64_t vector);
void ps2MaterialBillboardSetPosition(uint64_t object,uint64_t vector);
void ps2PolygonSetPosition(uint64_t object,uint64_t vector);
void ps2PolygonAlternateSetPosition(uint64_t object,uint64_t vector);
void ps2SpecialPolygonSetPosition(uint64_t object,uint64_t vector);
void ps2MagatuhiWrapperSetPosition(uint64_t object,uint64_t vector);
void ps2MagatuhiType2SetPosition(uint64_t object,uint64_t vector);
void ps2MagatuhiType3SetPosition(uint64_t object,uint64_t vector);
void ps2MagatuhiType4SetPosition(uint64_t object,uint64_t vector);
void nocturneEffectPositionCall(uint32_t target,uint64_t object,uint64_t vector);

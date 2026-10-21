#pragma once
#include <stdint.h>
uint64_t ps2PolygonStateArrayCreate(uint64_t count);
uint64_t ps2PolygonHistoryCreate(uint64_t count,uint64_t width,uint64_t source);
void ps2PolygonColorSetup(uint64_t record,uint64_t time);
uint64_t ps2PolygonSampleLookup(uint64_t width);
uint64_t ps2PolygonVertexCreate(uint64_t count,uint64_t width,uint64_t step,uint64_t kind);
void ps2PolygonVertexReset(uint64_t work,uint64_t index);
void ps2PolygonVertexSetMode(uint64_t work,uint64_t mode);
void ps2PolygonVertexColors(uint64_t work,uint64_t operation,uint64_t first,uint64_t second);
void ps2PolygonPairColors(uint64_t work,uint64_t first,uint64_t second);
void ps2PolygonPairFade(uint64_t work,uint64_t first,uint64_t second);
void ps2PolygonPairRiseFall(uint64_t work,uint64_t first,uint64_t second);
void ps2PolygonTripleColors(uint64_t work,uint64_t first,uint64_t second);
void ps2PolygonTripleFade(uint64_t work,uint64_t first,uint64_t second);
void ps2PolygonTripleRiseFall(uint64_t work,uint64_t first,uint64_t second);
void ps2PolygonQuadColors(uint64_t work,uint64_t first,uint64_t second);
void ps2PolygonQuadFade(uint64_t work,uint64_t first,uint64_t second);
void ps2PolygonQuadRiseFall(uint64_t work,uint64_t first,uint64_t second);
#if UINTPTR_MAX > UINT32_MAX
void *nocturneResolvePolygonPrerequisiteAddress(uint32_t address);
void nocturneCallPolygonColor(uint32_t target,uint64_t work,uint64_t first,uint64_t second);
#endif

#ifndef NOCTURNE_FIELD_INF_GRAPH_H
#define NOCTURNE_FIELD_INF_GRAPH_H
#include <stdint.h>
void ps2FieldInfImport_00140C38(uint64_t source);
uint64_t ps2FieldInfFindEvent_0013FD28(uint64_t name);
uint64_t ps2FieldInfFindNpc_0013FF20(uint64_t name);
uint64_t ps2FieldInfFindAny_00140108(uint64_t name);
uint64_t ps2FieldInfFastPanel_001402D0(uint64_t line);
uint64_t ps2FieldInfGet_00140B10(uint64_t line,uint64_t column);
uint64_t ps2FieldInfFindWarp_00140F48(uint64_t name);
uint64_t ps2FieldInfLadderQuery_00142A88(uint64_t mode);
void *nocturneResolveFieldInfGraphAddress(uint32_t address);
#endif

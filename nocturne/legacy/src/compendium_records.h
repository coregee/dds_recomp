#ifndef NOCTURNE_COMPENDIUM_RECORDS_H
#define NOCTURNE_COMPENDIUM_RECORDS_H
#include <stdint.h>
void *nocturneResolveCompendiumRecordsAddress(uint32_t address);
/* Provider-owned guest SP: actual local236B object and typed qsort callbacks. */
uint32_t nocturneCompendiumRecordsStackPointer(void);
void nocturneCompendiumRecordsSetStackPointer(uint32_t address);
uint64_t ps2CompendiumRecords_00216910(uint64_t p0,uint64_t p1);
void ps2CompendiumRecords_00219FC0(uint64_t p0,uint64_t p1);
void ps2CompendiumRecords_00216C08(void);
uint64_t ps2CompendiumRecords_00219400(uint64_t p0);
void ps2CompendiumRecords_002197B0(uint64_t p0,uint64_t p1,uint64_t p2);
void ps2CompendiumRecords_00219BA0(uint64_t p0);
void ps2CompendiumRecords_00219BF0(uint64_t p0);
void ps2CompendiumRecords_00219DC0(uint64_t p0,uint64_t p1);
uint64_t ps2CompendiumRecords_00219C40(uint64_t p0,uint64_t p1);
uint64_t ps2CompendiumRecords_00219D00(uint64_t p0,uint64_t p1);
uint64_t ps2CompendiumRecords_00216A18(uint64_t p0,uint64_t p1);
#endif

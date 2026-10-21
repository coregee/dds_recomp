#ifndef NOCTURNE_COMPENDIUM_RECORDS_TRANSPORT_H
#define NOCTURNE_COMPENDIUM_RECORDS_TRANSPORT_H
#include "fusion_core_transport.h"
typedef NocturneFusionCorePointerBinding NocturneCompendiumRecordsPointerBinding;
void nocturneCompendiumRecordsActivate(const NocturneCompendiumRecordsPointerBinding *bindings,uint32_t count);
void nocturneCompendiumRecordsDeactivate(void);
void nocturneCompendiumRecordsBindFcsr(uint32_t *actual_cell);
uint32_t nocturneCompendiumRecordsStackPointer(void);
void nocturneCompendiumRecordsSetStackPointer(uint32_t address);
void nocturneCompendiumRecordsFpuCondition(uint32_t condition);
/* Real finite code dispatch only. The qsort caller records the actual result. */
uint64_t nocturneCompendiumRecordsCompare(uint64_t target,uint64_t left,uint64_t right);
uint32_t nocturneCompendiumRecordsObserveCall(void (*function)(void),uint32_t argc,const uint64_t *arguments,uint32_t return_width);
_Noreturn void nocturneCompendiumRecordsArithmeticTrap(uint32_t code);
extern uint64_t g_compendiumRecordsResult;
extern uint32_t g_compendiumRecordsTrapCode;
extern uint32_t g_compendiumRecordsCompleted;
#endif

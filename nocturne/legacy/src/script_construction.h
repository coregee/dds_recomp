#ifndef NOCTURNE_SCRIPT_CONSTRUCTION_H
#define NOCTURNE_SCRIPT_CONSTRUCTION_H
#include <stdint.h>
uint64_t scrAddScript(uint64_t header,uint64_t types,uint64_t procedures,uint64_t labels,
    uint64_t code,uint64_t messages,uint64_t strings,uint64_t start);
uint64_t scrAddScript2(uint64_t data,uint64_t start);
uint64_t ps2ScriptAddFirst(uint64_t header,uint64_t types,uint64_t procedures,uint64_t labels,
    uint64_t code,uint64_t messages,uint64_t strings);
uint64_t scrStartScript2(uint64_t priority,uint64_t data,uint64_t start);
uint64_t scrStartScript1a(uint64_t priority,uint64_t header,uint64_t types,uint64_t procedures,
    uint64_t labels,uint64_t code,uint64_t messages,uint64_t strings,uint32_t start);
void ps2ScriptDiagnosticDisabled(uint64_t format,...);
void *nocturneResolveScriptConstructionAddress(uint32_t address);
#endif

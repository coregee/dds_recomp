#ifndef NOCTURNE_EVOLUTION_EVENT_H
#define NOCTURNE_EVOLUTION_EVENT_H
#include <stdint.h>

/* Whole00223258. Raw positional PS2 argument slots; mode uses only low8.
 * source is a full unit and, on mode!=0/type5, sixteen inline EC-byte units.
 * event is a flat >=8-byte PS2 record, not the HD managed event array.
 * output may be raw NULL; otherwise it backs a complete writable EC-byte
 * unit. Source/output may alias, including exact self-alias. All effective
 * guest reads/writes go through the original low32 address representation.
 * No universal V0 is defined: this is intentionally a semantic void API.
 * Private guest frames, full volatile banks and arithmetic FCSR flags are
 * outside the current semantic/callee-save/declared-RAM comparison profile.
 */
void ps2EvolutionEvent_00223258(uint64_t source, uint64_t event,
    uint64_t mode, uint64_t output);
void *nocturneResolveEvolutionEventAddress(uint32_t address);
#endif

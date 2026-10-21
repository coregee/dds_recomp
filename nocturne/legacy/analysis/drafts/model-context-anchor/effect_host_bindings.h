#ifndef NOCTURNE_WORKING_EFFECT_HOST_BINDINGS_H
#define NOCTURNE_WORKING_EFFECT_HOST_BINDINGS_H
#include <stdint.h>
void *nocturneEffectHostAddress(uint32_t address);
uint32_t nocturneEffectHostOriginalAddress(const void *host);
/* One active comparison domain at a time. Repeated Activate resets the
 * active domain; Deactivate restores the caller's prior routing/bank view.
 * Compare final native state while active, before Deactivate. This is host
 * mode restoration, never a game-call epilogue or processor-state repair. */
extern uint32_t g_nocturneEffectHostActive;
void nocturneEffectHostActivate(void);
void nocturneEffectHostDeactivate(void);
uint32_t *nocturneEffectHostFpr(void);
void nocturneEffectAxisNoteEntry(uint32_t entry);
#define NOCTURNE_EFFECT_ENTRY_TRACE_CAPACITY 8192u
#define NOCTURNE_EFFECT_ENTRY_TRACE_FIELDS 11u
extern uint64_t g_effectAxisEntryTrace[NOCTURNE_EFFECT_ENTRY_TRACE_CAPACITY*NOCTURNE_EFFECT_ENTRY_TRACE_FIELDS];
extern uint32_t g_effectAxisEntryTraceSize;
extern uint32_t g_effectAxisEntryTraceOverflow;
void nocturneEffectHostCpuRead(unsigned reg,uint32_t words[4]);
void nocturneEffectHostCpuWrite(unsigned reg,const uint32_t words[4]);
#endif

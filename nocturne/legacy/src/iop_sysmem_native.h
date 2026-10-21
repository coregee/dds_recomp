#ifndef NOCTURNE_IOP_SYSMEM_NATIVE_H
#define NOCTURNE_IOP_SYSMEM_NATIVE_H
#include <stdint.h>
/* Independent R3000 integer machine. Module-relative PC and data; caller owns
 * relocation/load address, initialized RAM, callbacks and interrupt exclusion.
 * Outcome1 transfers to a real unowned target. No callback result is supplied.
 * This is not the EE's 720-byte machine, an RPC server, or an IOP scheduler. */
typedef struct {uint32_t gpr[32],hi,lo,pc,load_register,load_value,branch_pending,branch_target;uint64_t instructions;} NocturneIopMachine;
enum {NOCTURNE_IOP_TRANSFER=1,NOCTURNE_IOP_MEMORY=2,NOCTURNE_IOP_LIMIT=3,NOCTURNE_IOP_DOMAIN=4};
uint32_t nocturneIopSysmemResume(NocturneIopMachine *,uint8_t *ram,uint32_t ram_bytes,uint64_t limit);
#endif

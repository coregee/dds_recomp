/* A deterministic stand-in for the PS2 around the code under test.
 *
 * Guest RAM is a 32 MB host buffer with SLUS_209.11's segments loaded, so
 * static tables (skills, devils, encounters, affinities) are the real game
 * data. Every function the battle calculations call is replaced by a fake
 * with simple, seed-driven behaviour. Both the legacy C and the rewrite call
 * the *same* fakes, so any difference in results, RNG draws, debug prints or
 * RAM writes comes from the code under test. */
#ifndef READABLE_FAKE_WORLD_H
#define READABLE_FAKE_WORLD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Guest addresses of the fake dynamic state. */
enum {
    FW_RAM_SIZE   = 0x02000000,
    FW_GLOBAL     = 0x01000000, /* datGlobalWork */
    FW_MAIN       = 0x01100000, /* nbMainProcessData */
    FW_FORMS      = 0x01101000, /* nbFormation[14] */
    FW_PARTY      = 0x01102000, /* nbParty[14] */
    FW_ENEMIES    = 0x01103000, /* enemy datUnitWork[10] */
    FW_ACTION     = 0x01104000, /* nbActionProcessData */
    FW_FORM_UNITS = 0x01105000, /* uint32_t[16]: formindex -> unit address */
    FW_LOG        = 0x01105100, /* event bit writes: count, then bit | on << 31 */
    FW_SCRATCH    = 0x01105400, /* 0xC00 bytes for test buffers */
    FW_DYNAMIC_BEGIN = 0x01000000,
    FW_TARSEL     = 0x01106000, /* nbTarSelProcessData */
    FW_SCRIPT     = 0x01106100, /* the running command's script work (scr::ProcessWork, harness.hpp);
                                   at 0x60 the message handle */
    FW_MES_INSTANCE = 0x01107000, /* two message windows (instanceMes_tag, 0x200 apart) */
    FW_MES_TABLE  = 0x011a0000,   /* a message table (MSG1), up to 0x10000 bytes */
    FW_MES_STATE  = 0x0110a200,   /* the message fakes: pool cursor, log count, log {kind, a, b} */
    FW_MES_POOL   = 0x0110a800,   /* memory blocks, panels and pools the fakes hand out */
    FW_MES_POOL_END = 0x01160000,
    FW_FONTS      = 0x01160000,   /* the four .fnt files (game/dds3/font/EngFont) */
    FW_DYNAMIC_END   = 0x011b0000,
    /* Guest stack for legacy code that allocates on it (not compared). */
    FW_STACK_TOP     = 0x01300000,
};

enum { FW_MAX_TRACE = 64 };

typedef struct fw_trace {
    /* RNG draws: limit (0 for float) and the value returned. */
    uint32_t rng_count;
    uint32_t rng_limit[FW_MAX_TRACE];
    uint32_t rng_value[FW_MAX_TRACE];
    /* Debug prints: format address and up to five arguments. */
    uint32_t print_count;
    uint32_t print_format[FW_MAX_TRACE];
    int64_t print_args[FW_MAX_TRACE][5];
} fw_trace;

extern uint8_t *fw_ram;
extern fw_trace fw_current_trace;

int fw_load_elf(const char *path);
void *fw_resolve(uint32_t address);
uint32_t fw_address_of(const void *pointer);

/* Start a case: seeds the fakes and the RNG, clears the trace. */
void fw_begin_case(uint64_t seed, int normal_difficulty, uint32_t moon_age);

/* Record a debug print (rewrite side); the legacy side goes through
 * ps2LibcPrintf. */
void fw_record_print(uint32_t format, const int64_t *args);
int fw_print_arg_count(uint32_t format);

/* A BREAK 7 trap: longjmps to the harness. */
#ifdef __cplusplus
[[noreturn]]
#else
_Noreturn
#endif
void fw_trap(uint32_t code);
extern void *fw_trap_target; /* jmp_buf* set by the harness */

uint64_t fw_hash(uint64_t a, uint64_t b, uint64_t c);

/* Message-manager fakes: append to the log in FW_MES_STATE. */
void fw_mes_log(uint32_t kind, uint32_t a, uint32_t b);

#ifdef __cplusplus
}
#endif
#endif

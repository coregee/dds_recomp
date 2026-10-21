#ifndef NOCTURNE_SOUND_WORKER_PROTOCOL_H
#define NOCTURNE_SOUND_WORKER_PROTOCOL_H
#include <stddef.h>
#include <stdint.h>
/* Native little-endian wire layouts, never host pointers or supplied replies.
 * EE2C10E8/0F28 and IOP SDFSDMAN3C10/3FD4 use this same128-byte slot.
 * Bits0..7 of size_and_dma_bytes are SIF packet bytes, bits8..31 DMA bytes.
 * length_command_flags is SIF opt: native command<<16 | flags_low16 |
 * ((payload_bytes+35)>>4)<<28. Do not confuse its token with OS thread IDs. */
typedef struct NocturneSoundCommandSlot32 {
    uint32_t size_and_dma_bytes;
    uint32_t dma_destination;
    uint32_t sif_command_id;
    uint32_t length_command_flags;
    uint32_t token;
    uint8_t payload[108];
} NocturneSoundCommandSlot32;

/* EE2C13D8 initializes bank_id_word toFFFFFFFF and state bytes4/5 to0.
 * IOP2B80 reads actual SMG header ID/flags, stores them at3204..3248 and
 * calls35DC to DMA the whole status mirror back. Bytes6/7 are not initialized
 * by that EE constructor and must retain their real prior bytes. */
typedef struct NocturneSoundBankRecord32 {
    uint32_t bank_id_word;
    uint8_t state4, state5, retained6, retained7;
} NocturneSoundBankRecord32;

typedef struct NocturneSoundStatusMirror32 {
    uint8_t other_native_state[0x190];
    NocturneSoundBankRecord32 banks[7];
    uint32_t ee_mirror_address;
    uint32_t mirror_bytes;
    uint8_t other_native_state_after[0x5a0-0x1d0];
} NocturneSoundStatusMirror32;

/* SIF system command80000001: real IOP sends[31,1] at readiness and
 * [30,token] after command handling. These describe transported writes,
 * not a permission receipt or a substitute for SIF/worker execution. */
typedef struct NocturneSoundSregWrite32 {
    uint32_t size_and_dma_bytes, dma_destination, sif_command_id, option;
    uint32_t index, value;
} NocturneSoundSregWrite32;

_Static_assert(sizeof(NocturneSoundCommandSlot32)==128,"native sound command slot");
_Static_assert(offsetof(NocturneSoundCommandSlot32,token)==16,"native token offset");
_Static_assert(offsetof(NocturneSoundCommandSlot32,payload)==20,"native payload offset");
_Static_assert(sizeof(NocturneSoundBankRecord32)==8,"native bank stride");
_Static_assert(offsetof(NocturneSoundStatusMirror32,banks)==0x190,"native banks offset");
_Static_assert(offsetof(NocturneSoundStatusMirror32,ee_mirror_address)==0x1c8,"native EE mirror address");
_Static_assert(offsetof(NocturneSoundStatusMirror32,mirror_bytes)==0x1cc,"native DMA extent");
_Static_assert(sizeof(NocturneSoundStatusMirror32)==0x5a0,"native shared status extent");
_Static_assert(sizeof(NocturneSoundSregWrite32)==24,"native SREG command extent");
#endif

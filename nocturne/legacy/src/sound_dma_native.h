#ifndef NOCTURNE_SOUND_DMA_NATIVE_H
#define NOCTURNE_SOUND_DMA_NATIVE_H
#include <stdint.h>
#include "battle_panel_color_native.h"
/* Complete38-instruction2C1278 plus3 whole syscall veneers. All physical
 * GPR128/guest RAM/SP values use the existing actual-bank hooks above.
 * Body returns host handled1/0 only; native V0 is never a host result.
 * Typed VOID3 wrapper changes only A0/A1/A2 low64, preserving actual uppers.
 * Destination/source/length remain raw64 until original SW narrows them.
 * Actual frame stores S0/S1/RA and its unused8bytes are never prefilled. */
uint32_t nocturneSoundDmaNativeBody(uint32_t entry);
void ps2SoundDmaNative_002C1278(uint64_t destination,uint64_t source,uint64_t bytes);
/* UNIMPLEMENTED real processor boundary. The source already published V1,
 * native SP and caller RA in the actual bank. Execute original FlushCache100,
 * SetDma119 or DmaStat118 with their true BIOS/device/IOP effects and bank
 * clobbers, or stop without returning. Never consume supplied replies or
 * return a constant ID/completion. No bank snapshot/repair is authorized.
 * SetDma119 success only queues channel6; its return does NOT establish
 * completed transfer. Native118 polling remains live and unbounded. */
void nocturneSoundDmaNativeSyscall(uint32_t pc,uint64_t selector);
#endif

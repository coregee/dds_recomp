#ifndef NOCTURNE_SIF0_TRANSPORT_H
#define NOCTURNE_SIF0_TRANSPORT_H
#include <stdint.h>
/* Explicit device state, separate from original EE/IOP CPU banks. Linear RAM
 * profile only; no VTLB/SPR/cache side effects. SIF0 IOP->FIFO->EE, 128 words.
 * Cycles are request deltas in a declared emulator profile, not a live clock.
 * Completion delivery publishes IRQ requests; no guest handler or RPC reply
 * is supplied. The caller must route real native interrupt/scheduler code. */
typedef struct {
 uint32_t fifo[128],junk[4],read_pos,write_pos,size;
 uint32_t iop_busy,iop_end,iop_counter,iop_padding,iop_cycles,iop_tag[4];
 uint32_t ee_busy,ee_end,ee_cycles;
 uint32_t iop_madr,iop_bcr,iop_chcr,iop_tadr,ee_madr,ee_qwc,ee_chcr;
 uint32_t sbus_control,stall_source,stall_address,ee_cycle_scale;
 uint32_t pending_iop,pending_ee,iop_delay,ee_delay,iop_irq,ee_irq,stall_clears;
 uint32_t event_count,events[64][3];
} NocturneSif0Transport;
enum { NOCTURNE_SIF0_WAIT=0,NOCTURNE_SIF0_LIMIT=1,
 NOCTURNE_SIF0_MEMORY=2,NOCTURNE_SIF0_DOMAIN=3 };
/* action:0 drive,1 start IOP,2 start EE,3 deliver pending IOP completion,
 * 4 deliver pending EE completion. Delivery does not advance guest CPUs. */
uint32_t nocturneSif0Drive(NocturneSif0Transport *,uint8_t *,uint32_t,
 uint8_t *,uint32_t,uint32_t,uint32_t);
#endif

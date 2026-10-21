#ifndef NOCTURNE_MOVIE_STARTUP_H
#define NOCTURNE_MOVIE_STARTUP_H
#include <stdint.h>
#include "vif_reset.h"
uint64_t ps2KernelAddIntcHandler2(uint64_t cause,uint64_t callback,uint64_t next,uint64_t argument);
uint64_t ps2KernelAddSbusHandler(uint64_t cause,uint64_t callback);
uint64_t ps2InterruptHandlerRegister(uint64_t kind,uint64_t cause,uint64_t callback,uint64_t next,uint64_t argument);
uint64_t ps2MovieIpuResetInputDma(uint64_t control);
void ps2MovieIpuInitialize(void);
uint64_t ps2MovieDecoderStartup(void);
/* One original SQ transfer to the IPU input FIFO; timing belongs to the platform. */
void nocturneMovieIpuFifoWrite(NocturneQuadword value);
#endif

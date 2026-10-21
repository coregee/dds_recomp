#ifndef NOCTURNE_BATTLE_PANEL_COLOR_NATIVE_H
#define NOCTURNE_BATTLE_PANEL_COLOR_NATIVE_H
#include <stdint.h>
/* Complete existing registered 001ABC88, zero new identity credit.
 * The bank entry consumes actual A0/A1 and leaves native clobbers published.
 * The typed entry writes only A0/A1 low64, preserving their actual upper64. */
uint64_t nocturneBattlePanelColorBody_001ABC88(void);
uint64_t ps2BattlePanelColorNative_001ABC88(uint64_t first,uint64_t second);

/* Integration-owned, UNIMPLEMENTED here. Every access is to the actual live
 * shared architectural bank, never a shadow, fixture reply or upper-word FIFO.
 * GPR words are little-endian low32,high32,upper-low32,upper-high32. Register0
 * reads all zero; writes to0 are ignored. VU0 VF0 is architectural constant.
 * StackPointer must equal low32 actualGPR29 on entry; SetStackPointer joins
 * the actualCPU29 and Core/sorter guest SP, preserving GPR29 upper64.
 * Resolve must supply the actual declared RAM and never MMIO-as-RAM. */
void nocturneBattlePanelColorCpuRead(unsigned reg,uint32_t words[4]);
void nocturneBattlePanelColorCpuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattlePanelColorReadFpr(unsigned reg);
void nocturneBattlePanelColorWriteFpr(unsigned reg,uint32_t bits);
void nocturneBattlePanelColorVuRead(unsigned reg,uint32_t words[4]);
void nocturneBattlePanelColorVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneBattlePanelColorStackPointer(void);
void nocturneBattlePanelColorSetStackPointer(uint32_t address);
void *nocturneResolveBattlePanelColorAddress(uint32_t address);
#endif

#ifndef NOCTURNE_BATTLE_PANEL_OWNER_H
#define NOCTURNE_BATTLE_PANEL_OWNER_H
#include <stdint.h>
/* Complete8 new bodies and28 existing native variants. Actual full architectural
 * banks and guest RAM/SP/RA are already live. Return1/0 is host dispatch status,
 * never a supplied native V0 or an instruction execution result. */
uint32_t nocturneBattlePanelOwnerBody(uint32_t entry);
/* The only unimplemented integration-owned routes are genuine callback targets
 * outside the36-body closure and the SQRT.S processor primitive. Unknown native
 * callbacks must stop explicitly without publishing a synthetic return value. */
void nocturneBattlePanelOwnerIndirect(uint64_t target,uint32_t pc);
uint32_t nocturneBattlePanelOwnerSqrtS(uint32_t input_bits,uint32_t pc);
/* Actual architectural state/RAM providers; no private bank or result provider.
 * Scalar writes preserve upper64. Register0 is constant; VF0=[0,0,0,1.0].
 * Resolve supplies declared ordinary RAM only. SP setter joins native/core SP. */
void nocturneBattlePanelOwnerCpuRead(unsigned reg,uint32_t words[4]);
void nocturneBattlePanelOwnerCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneBattlePanelOwnerVuRead(unsigned reg,uint32_t words[4]);
void nocturneBattlePanelOwnerVuWrite(unsigned reg,const uint32_t words[4]);
void *nocturneResolveBattlePanelOwnerAddress(uint32_t address);
uint32_t nocturneBattlePanelOwnerStackPointer(void);
void nocturneBattlePanelOwnerSetStackPointer(uint32_t address);
/* Native COP1 condition bit23, shared across nested callees. */
uint32_t nocturneBattlePanelOwnerFcsr(void);
/* Typed bridges write only actual native formal registers/stack words.
 * All ambient lanes, private stack and volatile state remain source-owned. */
void ps2BattlePanelSetOrderingOffset_002797B0(uint64_t a0);
void ps2BattlePanelDrawScaledTexture_00279D30(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,float f12);
void ps2BattlePanelDrawScaledTextureXY_00279E20(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,float f12,float f13);
void ps2BattlePanelDrawCurveHighlight_0027A7C0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7);
uint64_t nbPanelPressTurnRun(void);
void nbPanelPressTurn(uint64_t a0);
void ps2DrawBuildColoredTrianglePacket_002AEF00(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7,uint32_t a8,uint32_t a9,uint32_t a10,uint32_t a11);
void ps2DrawAppendColoredTrianglePacket_002AEFD0(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,uint64_t a4,uint64_t a5,uint64_t a6,uint64_t a7,uint32_t a8,uint32_t a9,uint32_t a10,uint32_t a11,uint32_t a12);
#endif

#ifndef NOCTURNE_FIELD_MOVEMENT_ENCOUNTER_H
#define NOCTURNE_FIELD_MOVEMENT_ENCOUNTER_H
#include <stdint.h>
/* Whole native16 source. Host handled1/0 is only dispatch status. Every GPR128,
 * FPR,VU/ACC/Q/clip,HI/LO and RAM result belongs to original operations.
 * Unavailable real calls/callbacks/services must stop, never supply answers. */
uint32_t nocturneFieldMovementBody(uint32_t entry);
void nocturneFieldMovementCall(uint32_t target,uint32_t pc);
void nocturneFieldMovementIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneFieldMovementTrap(uint32_t code,uint32_t pc);
void *nocturneResolveFieldMovementAddress(uint32_t address);
void nocturneFieldMovementCpuRead(unsigned reg,uint32_t words[4]);
void nocturneFieldMovementCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneFieldMovementVuRead(unsigned reg,uint32_t words[4]);
void nocturneFieldMovementVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneFieldMovementStackPointer(void);
void nocturneFieldMovementSetStackPointer(uint32_t address);
uint32_t nocturneFieldMovementFcsr(void);
/* ActualQ read and existing pinned PS2Float VUSQRT value owner,not hostIEEE
 * math/results. Scheduling/fullVU flags and physical runtime remain separate. */
uint32_t nocturneFieldMovementQ(void);
uint32_t nocturneFieldMovementVuSqrt(uint32_t input_bits,uint32_t pc);
uint64_t ps2FieldProcessCount_001010D8(uint64_t a0);
uint64_t ps2FieldProcessAt_00101130(uint64_t a0,uint64_t a1);
void ps2FieldEndSceneScript_0010F598(uint64_t a0,uint64_t a1);
uint64_t ps2FieldBasicGetData_00116050(uint64_t a0);
void ps2FieldRunDistanceAngle_0011BE98(uint64_t a0,uint64_t a1);
uint64_t ps2FieldSpecialEncounterCheck_0011F510(void);
uint64_t ps2FieldMovementEncounterCheck_00123C10(void);
uint64_t ps2FieldNextLoadStatus_001275D0(void);
void ps2FieldPlayerShadowOn_00134FD8(void);
void ps2FieldPlayerPositionRotation_00135380(void);
void ps2FieldEventHitEnd_0013C9A0(void);
uint64_t ps2FieldEventHitProcessCheck_0013FCD8(void);
void ps2FieldBgmStop_00145410(void);
void ps2FieldKillScripts_001E1AB0(void);
void ps2FieldCallBattle_001E7188(uint64_t a0,uint64_t a1);
uint64_t ps2FieldPublishActiveUnit_0010F1C0(uint64_t a0,uint64_t a1);
#endif

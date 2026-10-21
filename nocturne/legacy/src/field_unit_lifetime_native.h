#ifndef NOCTURNE_FIELD_UNIT_LIFETIME_NATIVE_H
#define NOCTURNE_FIELD_UNIT_LIFETIME_NATIVE_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneFieldUnitLifetimeNativeBody(uint32_t entry);
void nocturneFieldUnitLifetimeNativeExternal(uint32_t target,uint32_t pc);
void nocturneFieldUnitLifetimeNativeIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneFieldUnitLifetimeNativeTrap(uint32_t code,uint32_t pc);
void nocturneFieldUnitLifetimeNativeCpuRead(unsigned reg,uint32_t words[4]);
void nocturneFieldUnitLifetimeNativeCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneFieldUnitLifetimeNativeVuRead(unsigned reg,uint32_t words[4]);
void nocturneFieldUnitLifetimeNativeVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneFieldUnitLifetimeNativeStackPointer(void);
void nocturneFieldUnitLifetimeNativeSetStackPointer(uint32_t address);
uint32_t nocturneFieldUnitLifetimeNativeFcsr(void);
void *nocturneResolveFieldUnitLifetimeNativeAddress(uint32_t address);
uint64_t ps2FieldUnitLifetimeNative_0010DBE0(uint64_t a0);
void ps2FieldUnitLifetimeNative_0010DCB8(uint64_t a0);
uint64_t ps2FieldUnitLifetimeNative_0010F040(uint64_t a0);
void ps2FieldUnitLifetimeNative_0010F0E8(uint64_t a0);
uint64_t ps2FieldUnitLifetimeNative_0010F9D8(uint64_t a0,uint64_t a1);
uint64_t ps2FieldUnitLifetimeNative_0010FB98(void);
void ps2FieldUnitLifetimeNative_00110070(uint64_t a0);
void ps2FieldUnitLifetimeNative_00110370(uint64_t a0);
uint64_t ps2FieldUnitLifetimeNative_00111B80(uint64_t a0);
uint64_t ps2FieldUnitLifetimeNative_00112A40(uint64_t a0,uint64_t a1,uint64_t a2);
void ps2FieldUnitLifetimeNative_00112AF0(uint64_t a0);
uint64_t ps2FieldUnitLifetimeNative_00112B38(uint64_t a0);
void ps2FieldUnitLifetimeNative_00112BB0(uint64_t a0);
void ps2FieldUnitLifetimeNative_001130D0(uint64_t a0);
void ps2FieldUnitLifetimeNative_00115BC8(uint64_t a0,uint64_t a1);
void ps2FieldUnitLifetimeNative_001E3548(uint64_t a0,uint64_t a1);
uint64_t ps2FieldUnitLifetimeNative_001E39E8(uint64_t a0,uint64_t a1);
#endif

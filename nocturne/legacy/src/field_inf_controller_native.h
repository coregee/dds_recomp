#ifndef NOCTURNE_FIELD_INF_CONTROLLER_NATIVE_H
#define NOCTURNE_FIELD_INF_CONTROLLER_NATIVE_H
#include <stdint.h>
/* Complete fixed native bodies. External routes must execute actual registered callees;no invented result or native clobber is permitted. */
uint32_t nocturneFieldInfControllerNativeBody(uint32_t entry);
void nocturneFieldInfControllerNativeExternal(uint32_t target,uint32_t pc);
void nocturneFieldInfControllerNativeIndirect(uint64_t target,uint32_t pc);
_Noreturn void nocturneFieldInfControllerNativeTrap(uint32_t code,uint32_t pc);
void nocturneFieldInfControllerNativeCpuRead(unsigned reg,uint32_t words[4]);
void nocturneFieldInfControllerNativeCpuWrite(unsigned reg,const uint32_t words[4]);
void nocturneFieldInfControllerNativeVuRead(unsigned reg,uint32_t words[4]);
void nocturneFieldInfControllerNativeVuWrite(unsigned reg,const uint32_t words[4]);
uint32_t nocturneFieldInfControllerNativeStackPointer(void);
void nocturneFieldInfControllerNativeSetStackPointer(uint32_t address);
uint32_t nocturneFieldInfControllerNativeFcsr(void);
void *nocturneResolveFieldInfControllerNativeAddress(uint32_t address);
uint64_t ps2FieldInfControllerNative_00109F08(void);
void ps2FieldInfControllerNative_0010F020(uint64_t a0,uint64_t a1);
uint64_t ps2FieldInfControllerNative_0010F1F8(uint64_t a0);
uint64_t ps2FieldInfControllerNative_0010F270(uint64_t a0,uint64_t a1);
uint64_t ps2FieldInfControllerNative_0010F4D8(uint64_t a0,uint64_t a1);
uint64_t ps2FieldInfControllerNative_00110350(uint64_t a0);
uint64_t ps2FieldInfControllerNative_00112410(uint64_t a0);
void ps2FieldInfControllerNative_001128A8(uint64_t a0,uint64_t a1);
void ps2FieldInfControllerNative_00113448(uint64_t a0,uint64_t a1);
uint64_t ps2FieldInfControllerNative_00113458(uint64_t a0);
uint64_t ps2FieldInfControllerNative_00120120(uint64_t a0);
uint64_t ps2FieldInfControllerNative_001201A8(uint64_t a0);
uint64_t ps2FieldInfControllerNative_001207C0(uint64_t a0,uint64_t a1,uint64_t a2);
uint64_t ps2FieldInfControllerNative_00123370(void);
void ps2FieldInfControllerNative_00125CB8(uint64_t a0,uint64_t a1);
uint64_t ps2FieldInfControllerNative_0012C148(void);
void ps2FieldInfControllerNative_0012C360(void);
float ps2FieldInfControllerNative_0012C458(float f12,float f13,float f14,float f15);
float ps2FieldInfControllerNative_0012C528(float f12,float f13,float f14,float f15);
void ps2FieldInfControllerNative_0012C730(void);
void ps2FieldInfControllerNative_0012CA30(void);
void ps2FieldInfControllerNative_0012DDF8(void);
uint64_t ps2FieldInfControllerNative_0012EFD8(void);
void ps2FieldInfControllerNative_001303A0(uint64_t a0,uint64_t a1,float f12);
void ps2FieldInfControllerNative_00134DF8(void);
void ps2FieldInfControllerNative_00134E48(void);
void ps2FieldInfControllerNative_00135318(void);
float ps2FieldInfControllerNative_00137B40(uint64_t a0,uint64_t a1);
float ps2FieldInfControllerNative_0013B928(uint64_t a0,uint64_t a1,uint64_t a2,uint64_t a3,float f12);
uint64_t ps2FieldInfControllerNative_0013BAD8(uint64_t a0,uint64_t a1,uint64_t a2);
void ps2FieldInfControllerNative_0013C6F0(void);
void ps2FieldInfControllerNative_0013C860(void);
uint64_t ps2FieldInfControllerNative_001405B0(uint64_t a0,uint64_t a1);
void ps2FieldInfControllerNative_00140CF0(void);
void ps2FieldInfControllerNative_001452C8(void);
void ps2FieldInfControllerNative_001DD578(uint64_t a0,uint64_t a1,uint64_t a2,float f12,float f13);
void ps2FieldInfControllerNative_001E1688(uint64_t a0,uint64_t a1);
void ps2FieldInfControllerNative_001E7228(uint64_t a0);
void ps2FieldInfControllerNative_002C0560(float f12);
uint64_t ps2FieldInfControllerNative_002C16B8(uint64_t a0);
uint64_t ps2FieldInfControllerNative_002C18D8(uint64_t a0,uint64_t a1,uint64_t a2);
#endif

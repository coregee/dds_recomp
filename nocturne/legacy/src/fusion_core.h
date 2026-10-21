#ifndef NOCTURNE_FUSION_CORE_H
#define NOCTURNE_FUSION_CORE_H
#include <stdint.h>
void *nocturneResolveFusionCoreAddress(uint32_t address);
/* Provider-owned guest SP, shared with sorter scratch. No RAM writes. */
uint32_t nocturneFusionCoreStackPointer(void);
void nocturneFusionCoreSetStackPointer(uint32_t address);
/* Publish the locally computed COP1 condition to bit23 only. */
void nocturneFusionCoreFpuCondition(uint32_t condition);
uint64_t ps2FusionCore_001FD498(uint64_t p0);
uint64_t ps2FusionCore_001FD4E0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3);
uint64_t ps2FusionCore_001FD538(uint64_t p0,uint64_t p1);
uint64_t ps2FusionCore_001FD610(uint64_t p0,uint64_t p1,uint64_t p2);
uint64_t ps2FusionCore_001FD708(uint64_t p0,uint64_t p1,uint64_t p2);
uint64_t ps2FusionCore_001FD730(uint64_t p0,uint64_t p1,uint64_t p2);
uint64_t ps2FusionCore_001FD878(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4);
uint64_t ps2FusionCore_001FDA08(uint64_t p0);
uint64_t ps2FusionCore_001FDAC0(uint64_t p0,uint64_t p1);
uint64_t ps2FusionCore_001FDCA0(uint64_t p0,uint64_t p1);
uint64_t ps2FusionCore_001FDD18(uint64_t p0,uint64_t p1);
uint64_t ps2FusionCore_001FDDE8(uint64_t p0,uint64_t p1,uint64_t p2);
uint64_t ps2FusionCore_001FDEC0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3);
uint64_t ps2FusionCore_001FDF78(uint64_t p0,uint64_t p1);
void ps2FusionCore_001FE170(uint64_t p0,uint64_t p1,uint64_t p2);
uint64_t ps2FusionCore_001FE1A0(uint64_t p0,uint64_t p1);
uint64_t ps2FusionCore_001FE280(uint64_t p0);
uint64_t ps2FusionCore_001FE5F0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3);
uint64_t ps2FusionCore_001FE690(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6);
void ps2FusionCore_001FE880(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3);
uint64_t ps2FusionCore_001FEA20(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6);
void ps2FusionCore_001FEB28(uint64_t p0,uint64_t p1);
void ps2FusionCore_001FEC40(uint64_t p0,uint64_t p1);
uint64_t ps2FusionCore_001FEC68(uint64_t p0,uint64_t p1);
uint64_t ps2FusionCore_001FF428(uint64_t p0);
void ps2FusionCore_001FF4D0(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4);
uint64_t ps2FusionCore_001FF648(uint64_t p0);
uint64_t ps2FusionCore_001FF758(uint64_t p0,uint64_t p1,uint64_t p2);
uint64_t ps2FusionCore_001FF790(uint64_t p0,uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,uint64_t p5,uint64_t p6,uint64_t p7);
#endif

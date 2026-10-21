#ifndef NOCTURNE_BASIC_POSE_H
#define NOCTURNE_BASIC_POSE_H
#include <stdint.h>
uint64_t dds3InitPoseSet(uint64_t basic);
void dds3FreePoseSet(uint64_t basic);
void dds3OnPoseSetFlag(uint64_t pose,uint64_t flags);
void dds3OffPoseSetFlag(uint64_t pose,uint64_t flags);
uint64_t dds3CheckPoseSetFlag(uint64_t pose,uint64_t flags);
void dds3InitPoseSetValue(uint64_t pose);
void dds3BackupPoseSet(uint64_t pose);
void dds3SetRadiusPoseSet(uint64_t basic,float radius);
void dds3SetPosPoseSet(uint64_t basic,uint64_t vector);
void dds3SetRotPoseSet(uint64_t basic,uint64_t vector);
void dds3SetSclPoseSet(uint64_t basic,uint64_t vector);
/* Vector getters/results use the original implicit VU register state. */
void dds3GetPosPoseSetMCR(uint64_t basic);
void dds3GetRotPoseSet(uint64_t basic);
void dds3AddPosPoseSet(uint64_t basic,uint64_t vector);
void dds3AddRotPoseSet(uint64_t basic,uint64_t vector);
void dds3AddSclPoseSet(uint64_t basic,uint64_t vector);
void ps2PoseBuildTransform(uint64_t scale,uint64_t rotation,uint64_t position);
void dds3GetTMPoseSet(uint64_t basic);
uint64_t dds3SerializeID(void);
void sdfQuatMult(void);
void sdfQuatToMatrix(void);
#endif

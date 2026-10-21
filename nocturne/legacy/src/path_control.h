#ifndef NOCTURNE_PATH_CONTROL_H
#define NOCTURNE_PATH_CONTROL_H
#include <stdint.h>
uint64_t dds3CameraObjectBasicGetControlWorkData(uint64_t object);
uint64_t dds3UnitObjectBasicGetControlWorkData(uint64_t object);
uint64_t dds3MatterObjectBasicGetControlWorkData(uint64_t object);
uint64_t dds3LightObjectBasicGetControlWorkData(uint64_t object);
uint64_t dds3EventObjectBasicGetControlWorkData(uint64_t object);
uint64_t dds3EffectObjectBasicGetControlWorkData(uint64_t object);
uint64_t dds3GetBaseControlWorkData(uint64_t object);
uint64_t dds3ObjectBaseGetControlBasic(uint64_t object,uint64_t type);
void dds3MoverBasicSetPath(uint64_t mover,uint64_t path);
void dds3MoverBasicMakePath(uint64_t mover);
uint64_t dds3MoverBasicGetPathControl(uint64_t mover);
uint64_t dds3PathBasicPathControlGetMode(uint64_t control);
float dds3PathBasicControlGetRatio(uint64_t control);
uint64_t dds3PathBasicMakeControl(uint64_t path);
void dds3PathBasicFreeControl(uint64_t control);
uint64_t effSplInitialize2(uint64_t points,uint64_t count,uint64_t bogus);
void ps2SplineRelease(uint64_t spline);
void effSplineMakeCoefficientTable(uint64_t spline,uint64_t bogus);
void effSplineMakeDifferential(uint64_t output,uint64_t points,uint64_t count);
void effSplineSolveTridiagonal(uint64_t output,uint64_t differential,uint64_t count);
void effSplineMakeCoefficient(uint64_t spline,uint64_t differential);
void effSplineMakeCoefficient2(uint64_t spline,uint64_t differential);
uint64_t evtPathLinkAndMake(uint64_t path,uint64_t object);
uint64_t evtCheckPathStat(uint64_t object);
uint64_t evtCommand_CAM_SEL_FOVY(void);
uint64_t evtCommand_CAM_PATH_MOVE(void);
uint64_t evtCommand_CAM_PATH_WAIT(void);
#endif

#pragma once
#include <stdint.h>
void ps2RigidInverseMatrix(void);
void sdfVu0LookAtMatrix(uint64_t target,uint64_t position,uint64_t up);
void dds3CameraObjectBasicMakeCamera(uint64_t basic);
uint64_t dds3AddCameraObjectBasicTypeFree(uint64_t serial,uint64_t position,uint64_t rotation);
uint64_t dds3AddCameraObjectBasicTypeLookAt(uint64_t serial,uint64_t position,uint64_t target,uint64_t up);
uint64_t evtCommand_CAM_CREATE(void);

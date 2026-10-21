#ifndef NOCTURNE_EVENT_CAMERA_H
#define NOCTURNE_EVENT_CAMERA_H
#include <stdint.h>
uint64_t dds3SearchProcessName(uint64_t name);
uint64_t dds3GetActiveCameraSceneBasic(uint64_t scene);
uint64_t dds3SetActiveCameraSceneBasic(uint64_t scene,uint64_t camera);
uint64_t fldGetFollowCameraControl(void);
uint64_t fldGetUnitFollowCamera(void);
uint64_t evtSearchBasic(uint64_t type,uint64_t serial);
void dds3SetScreenFovy(float fovy);
void fldCamSyukanSuriawase(void);
uint64_t evtCommand_CAM_SEL(void);
#endif

#pragma once
#include <stdint.h>
uint64_t dds3AddBasic(uint64_t type);
void dds3DeleteBasic(uint64_t basic);
uint64_t ps2WorldBasicConstructor(uint64_t basic);
void ps2WorldBasicDestructor(uint64_t basic);
void dds3DeleteScene(uint64_t scene);
uint64_t dds3AddSceneBasicData(uint64_t type);
void dds3DeleteSceneBasicData(uint64_t basic);
void dds3MoverBasicDestructor(uint64_t basic);
uint64_t dds3AddMoverBasic(uint64_t object);
uint64_t dds3ObjectBaseCreateMover(uint64_t object);
uint64_t dds3CameraObjectBasicConstructor(uint64_t basic);
uint64_t dds3AddCameraObjectBasicDef(uint64_t serial);
uint64_t dds3AddPathBasic(uint64_t serial,uint64_t data,uint64_t name);
/* Host adaptation; production resolves these original callback addresses. */
uint64_t nocturneCallBasicInitializer(uint32_t entry,uint64_t basic);
void nocturneCallBasicDestructor(uint32_t entry,uint64_t basic);

#pragma once
#include <stdint.h>
void sdfMotCLBK_modelLinerPosSeek(uint64_t node,float frame);
void ps2MotionPositionBlend(uint64_t node,float frame,float weight);
void ps2MotionEulerSeek(uint64_t node,float frame);
void ps2MotionEulerBlend(uint64_t node,float frame,float weight);
void sdfMotCLBK_modelLinerScaleSeek(uint64_t node,float frame);
void ps2MotionScaleBlend(uint64_t node,float frame,float weight);
void ps2MotionQuaternionSeek(uint64_t node,float frame);
void ps2MotionQuaternionBlend(uint64_t node,float frame,float weight);
void sdfMotCLBK_modelVisibleSeek(uint64_t node,float frame);
void sdfMotCLBK_modelVisibleBlendSeek(uint64_t node,float frame,float weight);
void sdfQuatFromEuler(float x,float y,float z);
uint32_t sdfCosBits(uint32_t angle);

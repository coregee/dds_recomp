#pragma once
#include <stdint.h>
uint64_t ps2MotionMaterialFactory(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t ps2MotionMorphFactory(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t ps2MotionCreateMaterialWord14(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t ps2MotionCreateMaterialWord10(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t ps2MotionCreateMaterialWord20(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t ps2MotionCreateMaterialWord28(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t ps2MotionCreateMaterialScalar1C(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t ps2MotionCreateMaterialDirect38(uint64_t controller,uint64_t command,uint64_t argument);
uint64_t ps2MotionCreateMaterialDirect3C(uint64_t controller,uint64_t command,uint64_t argument);
void ps2MotionMaterialDirect38Seek(uint64_t node,float frame);
void ps2MotionMaterialDirect38Blend(uint64_t node,float frame,float weight);
void ps2MotionMaterialDirect3CSeek(uint64_t node,float frame);
void ps2MotionMaterialDirect3CBlend(uint64_t node,float frame,float weight);
void ps2MotionMorphInit(uint64_t node,uint64_t controller,uint64_t vtable,uint64_t argument);
uint64_t ps2MotionCreateMorph(uint64_t controller,uint64_t command,uint64_t argument);
void ps2MotionMorphSeek(uint64_t node,float frame);
void ps2MotionMorphBlend(uint64_t node,float frame,float weight);

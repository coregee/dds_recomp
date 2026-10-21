#ifndef NOCTURNE_PATH_EVALUATION_H
#define NOCTURNE_PATH_EVALUATION_H
#include <stdint.h>
/* VU vector access is a processor boundary, not a recovered ELF function. */
void EE_PATH_VU_READ(unsigned reg,uint32_t words[4]);
void EE_PATH_VU_WRITE(unsigned reg,const uint32_t words[4]);
void dds3PathGetElement(uint64_t segment,uint64_t weight,uint64_t resource,float frame);
/* Host-independent boundary for the original caller's two private stack words. */
void nocturnePathElementPrivate(uint32_t result[2],uint32_t resource,uint32_t frame_bits);
void dds3PathBasicControlGetPos(uint64_t control);
void dds3PathBasicControlGetLight(uint64_t control,uint64_t output);
float dds3PathBasicControlGetFovy(uint64_t control);
uint64_t dds3PathBasicControlNextStep(uint64_t control);
void dds3PathBasicControlAlterMode(uint64_t control,uint64_t mode);
void dds3PathBasicControlSetRatio(uint64_t control,float ratio);
void dds3PathBasicPause(uint64_t control);
void dds3PathBasicPauseOff(uint64_t control);
void dds3PathBasicLoopOn(uint64_t control);
void dds3PathBasicLoopOff(uint64_t control);
void ps2SplineEvaluate(uint64_t output,uint64_t spline,uint64_t segment,float weight);
uint64_t ps2SplineAdvance(uint64_t output,uint64_t spline);
#endif

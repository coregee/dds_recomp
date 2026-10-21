#ifndef NOCTURNE_SCRIPT_DISTORTION_H
#define NOCTURNE_SCRIPT_DISTORTION_H
#include <stdint.h>
void *nocturneResolveScriptDistortionAddress(uint32_t address);
uint64_t scrCommand_DIST_BLUR_PARA(void);
uint64_t scrCommand_DIST_BLUR_RGBA(void);
uint64_t scrCommand_DIST_BLUR_AREA(void);
uint64_t scrCommand_DIST_BLUR_ON(void);
void ps2DistBlurSetPara_00105E78(uint64_t count, uint64_t width, uint64_t interval,
    uint64_t mode, float speed, float rotation, float distortion);
void ps2DistBlurSetRgba_00105EC0(uint64_t colour);
void ps2DistBlurSetArea_00105ED0(uint64_t area, uint64_t x, uint64_t y);
void ps2DistBlurOn_00105FC8(uint64_t frames);
void ps2DistBlurFlagSet_001AD370(void);
void ps2DistBlurFlagClear_001AD380(void);
void ps2DistBlurCopyConfig_001AD388(uint64_t source);
#endif

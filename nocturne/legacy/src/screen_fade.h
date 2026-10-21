#ifndef NOCTURNE_SCREEN_FADE_H
#define NOCTURNE_SCREEN_FADE_H
#include <stdint.h>
void dds3FadeClear(void);
void ps2FadeSetRGBA(uint64_t r,uint64_t g,uint64_t b,uint64_t a);
void dds3FadeColorSet(uint64_t r,uint64_t g,uint64_t b);
void dds3FadeIn(uint64_t r,uint64_t g,uint64_t b,uint64_t frames);
void dds3FadeIn2(uint64_t frames);
void dds3FadeOut(uint64_t r,uint64_t g,uint64_t b,uint64_t frames);
void dds3FadeOut2(uint64_t frames);
uint64_t dds3FadeCheck(void);
void dds3FadeUpdate(void);
uint64_t ps2DrawCreateDmaChain(void);
void dds3DrawFade(void);
uint64_t scrCommand_FADE_IN(void);
uint64_t scrCommand_FADE_OUT(void);
#endif

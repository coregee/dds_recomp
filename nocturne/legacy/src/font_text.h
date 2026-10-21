#ifndef NOCTURNE_FONT_TEXT_H
#define NOCTURNE_FONT_TEXT_H
#include <stdint.h>
void ps2FontBindContext(uint64_t style,uint64_t data,uint64_t handle);
void ps2FontLayoutGlyph(uint64_t text,uint64_t index,uint64_t first);
uint64_t ps2FontCreateTextureGlyph(uint64_t width,uint64_t height,uint64_t pixels,uint64_t owned);
uint64_t ps2FontAcquireCachedGlyph(uint64_t text,uint64_t index);
uint64_t ps2FontCreateTextGlyph(uint64_t code,uint64_t style,uint64_t color,uint64_t transparency,uint64_t first);
uint64_t ps2FontCreateControlGlyph(uint64_t data,uint64_t font);
uint64_t ps2FontAppendString(uint64_t string,uint64_t style,uint64_t color,uint64_t transparency,uint64_t font,uint64_t first);
uint64_t ps2FontCombineRequest(uint64_t first,uint64_t second);
uint64_t ps2FontAppendStringCombined(uint64_t string,uint64_t style,uint64_t color,uint64_t transparency,uint64_t font);
#endif

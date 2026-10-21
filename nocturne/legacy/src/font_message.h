#ifndef NOCTURNE_FONT_MESSAGE_H
#define NOCTURNE_FONT_MESSAGE_H
#include <stdint.h>
uint64_t ps2FontLoadNameBitmapBank(uint64_t bank,uint64_t second,uint64_t count,uint64_t pixels);
void ps2FontReferenceNameBitmapBank(uint64_t bank,uint64_t second);
uint64_t ps2FontAppendNameBitmapGlyph(uint64_t bank,uint64_t index,uint64_t font);
uint64_t ps2FontAppendNameFirst(uint64_t bank,uint64_t font,uint64_t color);
uint64_t ps2FontAppendNameSecond(uint64_t bank,uint64_t font,uint64_t color);
uint64_t ps2FontAppendNameBoth(uint64_t bank,uint64_t font,uint64_t color);
uint64_t ps2FontParseMessageTag(uint64_t prefix,uint64_t message);
uint64_t ps2FontParseMessage(uint64_t message);
uint64_t ps2FontMessageRequestEx(uint64_t x,uint64_t y,uint64_t z,uint64_t style,uint64_t color,uint64_t transparency,uint64_t speed,uint64_t text,uint64_t font);
uint64_t ps2FontMessageRequest(uint64_t x,uint64_t y,uint64_t style,uint64_t color,uint64_t transparency,uint64_t speed,uint64_t text,uint64_t font);
#endif

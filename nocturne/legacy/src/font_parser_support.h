#ifndef NOCTURNE_FONT_PARSER_SUPPORT_H
#define NOCTURNE_FONT_PARSER_SUPPORT_H
#include <stdint.h>
void frSetFontSpace(uint64_t font,uint64_t spacing);
void ps2FontSetDepth(uint64_t font,uint64_t depth);
uint64_t frEnableMode(uint64_t flag);
uint64_t frDisableMode(uint64_t flag);
void ps2FontBindMessageStyle(uint64_t data);
void ps2FontAppendVariable(uint64_t index,uint64_t message);
void frCreateNewHandle(uint64_t message);
void ps2FontAdvanceMessageLine(uint64_t message);
void ps2FontAppendSpecialCode(uint64_t message,uint64_t code);
uint64_t ps2FontAppendResourceName(uint64_t index,uint64_t style,uint64_t font,uint64_t color);
#endif

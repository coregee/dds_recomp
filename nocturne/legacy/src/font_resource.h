#ifndef NOCTURNE_FONT_RESOURCE_H
#define NOCTURNE_FONT_RESOURCE_H
#include <stdint.h>
uint64_t ps2FontResourceIdentity(uint64_t resource);
void ps2FontResolveCompressedSections(uint64_t resource,uint64_t sections);
uint64_t ps2FontDecodeGlyph(uint64_t output,uint64_t index,uint64_t resource,uint64_t sections);
uint64_t ps2FontAllocateDecodedGlyph(uint64_t style,uint64_t index);
uint64_t ps2FontTakeGlyphSlot(uint64_t list);
uint64_t ps2FontTakeTextureSlot(void);
uint64_t ps2FontFindCode416(uint64_t code);
uint64_t ps2FontFindCode264(uint64_t code);
void ps2FontRecordLastCode(uint64_t code);
uint64_t frGetDefaultFontWidth(uint64_t style);
uint64_t frGetFontWidth(uint64_t style);
uint64_t frGetDefaultFontHeight(uint64_t style);
uint64_t frGetFontHeight(uint64_t style);
uint64_t ps2FontGetGlyphStorageSize(void);
void frInitTextHandle(uint64_t text,uint64_t code,uint64_t style,uint64_t color_index,uint64_t color,uint64_t transparency);
void frInitFontHandle(uint64_t font);
uint64_t ps2FontMeasureRequest(uint64_t font);
#endif

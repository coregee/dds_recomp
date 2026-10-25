// The font engine (original unit: frFont): the JP builds' (font.cpp has
// the rest, font_layout_us.cpp the US release's). This engine has no size override for styles 0 and 1, no code
// lists or last code, and no name tables: every style draws at its font's
// size.

#include "nocturne/build.hpp"

#if NOCTURNE_JAPANESE

#include "nocturne/address.hpp"
#include "nocturne/interface/font.hpp"

#include <cstring>

#include "nocturne/external.hpp"

namespace nocturne::fr {

namespace {

uint32_t addressOf(const void* p) { return guest::addressOf(p); }
template <class T> T* at(uint32_t address) { return address ? guest::table<T>(address) : nullptr; }

// Mode bit 2 (kModeParsing) also halves the single-byte characters here.
constexpr uint8_t kModeHalfAscii = kModeParsing;

// The glyphs that get the shadow offset: in style 1, these; in style 0,
// those 0x154..0x1C5 marked in a byte table.
constexpr int32_t kStyle1Shadowed[] = {0x31, 0x47, 0x4a, 0x50, 0x51, 0x59};
constexpr uint32_t kStyle0Shadowed = jpAddr(0x003252b8);

} // namespace

// ps2FontBindContext @ 0x001C6B68
// Points a style at a font file: given by address, or by the memory handle
// holding it (kept, to free it with the style).
void BindStyle(uint8_t styleIndex, uint32_t data, uint32_t handle)
{
    if (!data && handle)
        data = mem::HandleAcquirePointer(handle);
    Style& s = style(styleIndex);
    const FontHeader& header = *guest::table<FontHeader>(data);
    uint32_t offset = header.header_size;
    s.handle = handle;
    s.data.address = data;
    offset += static_cast<uint32_t>(header.palettes) << 6;
    if (header.metrics) {
        for (int k = 0; k < 2; ++k) {
            const uint32_t table = data + offset;
            const int32_t size = *guest::table<int32_t>(table);
            s.metric[k] = table + 4;
            s.metric_size[k] = size;
            offset += static_cast<uint32_t>(size) + 4;
        }
    } else {
        s.metric[0] = s.metric[1] = 0;
        s.metric_size[0] = s.metric_size[1] = 0;
    }
    s.cache = data + offset;
    offset += static_cast<uint32_t>(s.data->glyphs) << 2;
    s.glyphs = data + offset;
}

// frLoadStyle @ 0x001C6858: loads a font file into a
// style, every time.
void frLoadStyle(uint8_t styleIndex, uint32_t name) { BindStyle(styleIndex, 0, file::Load(name)); }

// frDelFontStyle @ 0x001C6C70: unloads a style.
void frDelFontStyle(uint8_t styleIndex)
{
    Style& s = style(styleIndex);
    if (s.handle) {
        mem::HandleFree(s.handle);
        s.glyphs = 0;
    }
    s.cache = 0;
}

// ps2FontAcquireCachedGlyph @ 0x001C7568
// The glyph for a text: the cached one (one more reference), or a new one
// at the font's size.
Glyph* AcquireGlyph(Text& text, int32_t index)
{
    Style& s = style(text.style);
    uint32_t* cache = guest::table<uint32_t>(s.cache);
    if (Glyph* cached = at<Glyph>(cache[index])) {
        ++cached->refs;
        return cached;
    }
    uint32_t pixels = DecodeGlyphPixels(text.style, index);
    int32_t width = frGetDefaultFontWidth(text.style);
    int32_t height = frGetDefaultFontHeight(text.style);
    Glyph* glyph = CreateTextureGlyph(width, height, pixels, true);
    glyph->index = static_cast<uint16_t>(index);
    guest::table<uint32_t>(style(text.style).cache)[index] = addressOf(glyph);
    ++tables().glyphs;
    return glyph;
}

// frGetDefaultFontWidth @ 0x001C83B0: the font's size.
int32_t frGetDefaultFontWidth(uint8_t s) { return style(s).data->width; }
// frGetDefaultFontHeight @ 0x001C8418
int32_t frGetDefaultFontHeight(uint8_t s) { return style(s).data->height; }

// (The US release's ps2FontSetSize, 0x1C6160: the JP builds have no size
// override; READY's calls to set it do nothing here.)
void frSetBaseWidth(int64_t) {}

// frGetXShiftLev @ 0x001C7088
// A text's size and advance (the style's default). With kModeHalfAscii a
// single-byte character takes half of each; with kModeMetrics the font's
// per-glyph {left, right} gives the advance and the shift, for glyphs below
// 0x1C6 (halved likewise). '!' and '1' get 2 more pixels on each side.
void frGetXShiftLev(Text& pText, int32_t index, bool)
{
    const Style& s = style(pText.style);
    pText.width = static_cast<uint8_t>(frGetDefaultFontWidth(pText.style));
    pText.height = static_cast<uint8_t>(frGetDefaultFontHeight(pText.style));
    const int8_t advance = static_cast<int8_t>(defaultAdvance(pText.style));
    const uint8_t mode = pText.mode;
    pText.lw = advance;
    const bool half = (mode & kModeHalfAscii) && pText.code < 0x80;
    if (half) {
        pText.lw = advance >> 1;
        pText.width = static_cast<uint8_t>(pText.width >> 1);
    }
    if (!(mode & kModeMetrics) || !s.data->metrics || index >= 0x1c6)
        return;
    const int32_t doubled = index * 2;
    if (doubled >= s.metric_size[0])
        return;
    const int8_t* metric = guest::table<int8_t>(s.metric[0] + static_cast<uint32_t>(doubled));
    const int32_t right = metric[1];
    if (!right)
        return;
    int32_t w = right - metric[0];
    int32_t shift = metric[0] << 4;
    if ((mode & kModeHalfAscii) && pText.code < 0x80) {
        shift >>= 1;
        w >>= 1;
    }
    const int32_t glyph = (doubled >> 1) + 32;
    if (glyph == '!' || glyph == '1') {
        shift -= 32;
        w += 4;
    }
    pText.lw = w;
    pText.lx = -shift;
}

// ps2FontGetGlyphStorageSize @ 0x001C7080: the shadow
// offset of a glyph: 24 for the listed ones, else 0 (US Maniax: always 24).
int32_t shadowOffset(int8_t styleIndex, int32_t index)
{
    bool listed = false;
    if (styleIndex == 1)
        for (int32_t glyph : kStyle1Shadowed)
            listed = listed || index == glyph;
    if (styleIndex == 0 && static_cast<uint32_t>(index - 0x154) < 0x72)
        listed = guest::table<int8_t>(kStyle0Shadowed)[index - 0x154] != 0;
    return listed ? 24 : 0;
}

// frSetFont @ 0x001C76E0
// A text for one character, with its glyph: single-byte codes from 32 (a
// lower one reads before the glyphs), two-byte ones from 0x8080; glyph
// 0x147 for one the font doesn't have.
Text* frSetFont(uint16_t code, uint8_t styleIndex, uint8_t colno, uint8_t tp, bool)
{
    Text* text = static_cast<Text*>(PoolTake(*tables().text_pool));
    ++tables().texts;
    frInitTextHandle(*text, code, styleIndex, colno, 0xa09dc300, tp);
    int32_t index;
    if (text->code < 0x80) {
        index = text->code - 0x20;
    } else {
        const uint32_t value = static_cast<uint32_t>(text->code) - 0x8080;
        index = static_cast<int32_t>(((value & 0xff00) >> 1) + (value & 0x7f));
    }
    if (index >= style(styleIndex).data->glyphs)
        index = 0x147;
    text->glyph.address = addressOf(AcquireGlyph(*text, index));
    frGetXShiftLev(*text, index, false);
    text->ly = (text->mode & kModeShadow) ? shadowOffset(static_cast<int8_t>(styleIndex), index) : 0;
    return text;
}

// frSetFontString @ 0x001C7890
// Appends a string (single-byte characters and 2-byte codes from 0x80) to a
// request (a new one for null). A negative style keeps the last one; null
// if that font isn't loaded.
Request* frSetFontString(const uint8_t* pStr, int8_t styleIndex, int8_t colno, int8_t tp, Request* pFRQ, bool)
{
    Settings& set = settings();
    if (styleIndex >= 0)
        set.style = static_cast<uint8_t>(styleIndex);
    if (!style(set.style).glyphs)
        return nullptr;
    const uint32_t length = pStr ? static_cast<uint32_t>(std::strlen(reinterpret_cast<const char*>(pStr))) : 0;
    if (!pFRQ)
        pFRQ = newRequest();
    Text* previous = pFRQ->str_end.get();
    Text* last = nullptr;
    for (uint32_t pos = 0; pos < length; ++pos) {
        uint16_t code = pStr[pos];
        if (code >= 128)
            code = static_cast<uint16_t>(code << 8 | pStr[++pos]);
        last = frSetFont(code, settings().style, static_cast<uint8_t>(colno), static_cast<uint8_t>(tp), false);
        if (previous)
            previous->next.address = addressOf(last);
        else
            pFRQ->str.address = addressOf(last);
        last->prev.address = addressOf(previous);
        pFRQ->w_pxls += last->lw;
        ++pFRQ->strlen;
        previous = last;
    }
    if (last) {
        pFRQ->str_end.address = addressOf(last);
        pFRQ->x_size = last->width;
        pFRQ->y_size = last->height;
    }
    return pFRQ;
}

// frCombineFontRequestEx @ 0x001C8120
// Chains pFRQ2 (a chain, by its last request) after pFRQ1 (likewise) and
// returns the whole chain, by pFRQ2. With mode 1 pFRQ2 is also placed
// after pFRQ1 on the same line.
Request* frCombineFontRequestEx(Request* pFRQ1, Request* pFRQ2, uint64_t mode)
{
    if (!pFRQ1)
        return pFRQ2;
    if (!pFRQ2)
        return pFRQ1;
    pFRQ1->next = pFRQ2->head;
    pFRQ2->head->prev.address = addressOf(pFRQ1);
    pFRQ2->head = pFRQ1->head;
    if (mode == 1) {
        pFRQ2->x = pFRQ1->x + (pFRQ1->w_pxls << 4);
        pFRQ2->y = pFRQ1->y;
    }
    return pFRQ2;
}

} // namespace nocturne::fr

#endif // NOCTURNE_JAPANESE

// The font engine (original unit: frFont): the US release's own (Hardtype
// keeps it; font.cpp has the rest, font_layout_jp.cpp the JP builds').
// The JP engine has no size override, code lists or name
// tables.

#include "nocturne/build.hpp"

#if !NOCTURNE_JAPANESE

#include "nocturne/interface/font.hpp"

#include <cstring>

#include "nocturne/address.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"

namespace nocturne::fr {

namespace {

constexpr uint32_t kLastCode = addr(0x0054ea00);       // uint16: the last character laid out
constexpr uint32_t kCodes416 = addr(0x00325b10);       // uint16[416]
constexpr uint32_t kCodes264 = addr(0x00325e50);       // uint16[264]
constexpr uint32_t kStyleLoaded = addr(0x003261e8);    // int32 per style: 1 once loaded
constexpr uint32_t kStyleAdvance = addr(0x00326060);   // int8 per style: the default advance

int32_t& loaded(uint8_t s) { return guest::table<int32_t>(kStyleLoaded)[s]; }
uint32_t addressOf(const void* p) { return guest::addressOf(p); }
template <class T> T* at(uint32_t address) { return address ? guest::table<T>(address) : nullptr; }

} // namespace

// ps2FontBindContext @ 0x001C6B68 (no original name)
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
    s.names = s.data->names ? data + s.data->names : 0;
}

// frLoadStyle @ 0x001C6858 (no original name)
// Loads a font file into a style, once. Style 1 shares style 0's file.
void frLoadStyle(uint8_t styleIndex, uint32_t name)
{
    if (loaded(styleIndex) == 1)
        return;
    if (styleIndex == 1)
        BindStyle(1, 0, style(0).handle);
    else
        BindStyle(styleIndex, 0, file::Load(name));
    loaded(styleIndex) = 1;
}

// frDelFontStyle @ 0x001C6C70: unloads a style (0 and 1 stay).
void frDelFontStyle(uint8_t styleIndex)
{
    if (styleIndex <= 1)
        return;
    loaded(styleIndex) = 0;
    Style& s = style(styleIndex);
    if (s.handle) {
        mem::HandleFree(s.handle);
        s.glyphs = 0;
    }
    s.cache = 0;
}

// ps2FontAcquireCachedGlyph @ 0x001C7568
// The glyph for a text: the cached one (one more reference), or a new one.
Glyph* AcquireGlyph(Text& text, int32_t index)
{
    Style& s = style(text.style);
    uint32_t* cache = guest::table<uint32_t>(s.cache);
    if (Glyph* cached = at<Glyph>(cache[index])) {
        ++cached->refs;
        return cached;
    }
    uint32_t pixels = DecodeGlyphPixels(text.style, index);
    int32_t width = frGetFontWidth(text.style);
    int32_t height = frGetFontHeight(text.style);
    Glyph* glyph = CreateTextureGlyph(width, height, pixels, true);
    glyph->index = static_cast<uint16_t>(index);
    guest::table<uint32_t>(style(text.style).cache)[index] = addressOf(glyph);
    ++tables().glyphs;
    return glyph;
}

// frGetFontWidth @ 0x001C83F0: a font's character size.
int32_t frGetFontWidth(uint8_t s) { return style(s).data->width; }
// frGetFontHeight @ 0x001C8458
int32_t frGetFontHeight(uint8_t s) { return style(s).data->height; }

// frGetDefaultFontWidth @ 0x001C83B0: styles 0 and 1 are drawn at the base width.
int32_t frGetDefaultFontWidth(uint8_t s) { return s < 2 ? settings().base_width : frGetFontWidth(s); }
// frGetDefaultFontHeight @ 0x001C8418
int32_t frGetDefaultFontHeight(uint8_t s) { return s < 2 ? settings().base_width : frGetFontHeight(s); }

// ps2FontSetSize @ 0x001C6160 (no original name)
// Sets the base size of styles 0 and 1 (20 for none); style 1's default
// advance follows it.
void frSetBaseWidth(int64_t width)
{
    if (width < 1)
        width = 0x14;
    settings().base_width = static_cast<int32_t>(width);
    guest::table<int8_t>(kStyleAdvance)[1] = static_cast<int8_t>(width - 5);
}

// frGetXShiftLev @ 0x001C7088
// A text's size and advance. Styles 0 and 1 are scaled from 20-pixel
// glyphs to the base width and give ASCII half the default advance; with
// kModeMetrics, the font's per-glyph {left, right} gives the advance and
// the shift. ('!' and '1' get 2 more pixels on each side; glyph 0x2C1 is
// 7 narrower.)
void frGetXShiftLev(Text& pText, int32_t index, bool)
{
    const Style& s = style(pText.style);
    bool scaled = pText.style < 2;
    ee::Float factor = 1.0f;
    pText.width = static_cast<uint8_t>(frGetDefaultFontWidth(pText.style));
    pText.height = static_cast<uint8_t>(frGetDefaultFontHeight(pText.style));
    const int32_t advance = guest::table<int8_t>(kStyleAdvance)[pText.style];
    pText.lw = advance;
    if (pText.style < 2) {
        scaled = true;
        factor = ee::Float::fromInt(pText.width) / 20.0f;
    }
    const uint8_t mode = pText.mode;
    if (scaled && pText.code < 128)
        pText.lw = advance >> 1;
    if (pText.code == ' ' && (pText.style == 0 || pText.style == 1)) {
        pText.lw = settings().space_width + (pText.lw >> 1);
        return;
    }
    if (index == 0x2c1)
        pText.lw -= 7;
    if (!(mode & kModeMetrics) || !s.data->metrics)
        return;
    const int32_t doubled = index * 2;
    if (doubled >= s.metric_size[0])
        return;
    const int8_t* metric = guest::table<int8_t>(s.metric[0] + static_cast<uint32_t>(doubled));
    const int32_t left = metric[0], right = metric[1];
    if (!right)
        return;
    ee::Float width = ee::Float::fromInt(right - left) * factor;
    ee::Float x = ee::Float::fromInt(left) * 16.0f * factor;
    int32_t w = width.toInt(), shift = x.toInt();
    const int32_t glyph = (doubled >> 1) + 32;
    if (glyph == '!' || glyph == '1') {
        shift -= 32;
        w += 4;
    }
    pText.lw = w;
    pText.lx = -shift;
}

namespace {

int64_t findCode(uint32_t table, uint32_t size, uint16_t code)
{
    const uint16_t* codes = guest::table<uint16_t>(table);
    for (uint32_t i = 0; i < size; ++i)
        if (codes[i] == code)
            return i;
    return -1;
}

} // namespace

// ps2FontFindCode416 @ 0x001C6098
// Whether a character is in one of two code lists (used to pick particles,
// docs/messages.md); its position or -1.
int64_t FindCode416(uint16_t code) { return findCode(kCodes416, 416, code); }
// ps2FontFindCode264 @ 0x001C60E0
int64_t FindCode264(uint16_t code) { return findCode(kCodes264, 264, code); }

// ps2FontRecordLastCode @ 0x001C6128
// Remembers the last letter laid out: not punctuation below '/', not ':'..'@'
// and not 0x85EC.
void RecordLastCode(uint16_t code)
{
    if (code != 0x85ec && code >= 0x2f && static_cast<uint16_t>(code - 0x3a) >= 7)
        *guest::table<uint16_t>(kLastCode) = code;
}

// frSetFont @ 0x001C76E0
// A text for one character, with its glyph. ('^' is shown as '&'.)
Text* frSetFont(uint16_t code, uint8_t styleIndex, uint8_t colno, uint8_t tp, bool first)
{
    Text* text = static_cast<Text*>(PoolTake(*tables().text_pool));
    ++tables().texts;
    frInitTextHandle(*text, code, styleIndex, colno, 0xa09dc300, tp);
    if (text->code == '^')
        text->code = '&';
    const int32_t index = glyphIndex(text->code);
    text->glyph.address = addressOf(AcquireGlyph(*text, index));
    frGetXShiftLev(*text, index, first);
    text->ly = (text->mode & kModeShadow) ? 24 : 0;
    return text;
}

// frSetFontString @ 0x001C7890
// Appends a string (single-byte characters and 2-byte codes from 0x80) to a
// request (a new one for null). A negative style keeps the last one; null
// if that font isn't loaded.
Request* frSetFontString(const uint8_t* pStr, int8_t styleIndex, int8_t colno, int8_t tp, Request* pFRQ, bool first)
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
    for (uint32_t pos = 0; pos < length;) {
        uint16_t code = pStr[pos];
        if (code >= 128)
            code = static_cast<uint16_t>(code << 8 | pStr[++pos]);
        const bool scale = first && pos == 0;
        ++pos;
        last = frSetFont(code, settings().style, static_cast<uint8_t>(colno), static_cast<uint8_t>(tp), scale);
        if (previous)
            previous->next.address = addressOf(last);
        else
            pFRQ->str.address = addressOf(last);
        last->prev.address = addressOf(previous);
        pFRQ->w_pxls += last->lw;
        ++pFRQ->strlen;
        previous = last;
        RecordLastCode(code);
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
// returns the whole chain, by pFRQ2. With mode 1 pFRQ2 is also placed: below
// pFRQ1 when it starts with a line feed (code 13), otherwise after it on the
// same line.
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
        const Text* first = pFRQ2->str.get();
        if (first && first->code == 13) {
            pFRQ2->x = pFRQ1->x;
            pFRQ2->y = pFRQ1->y + pFRQ1->y_size;
        } else {
            pFRQ2->x = pFRQ1->x + (pFRQ1->w_pxls << 4);
            pFRQ2->y = pFRQ1->y;
        }
    }
    return pFRQ2;
}

} // namespace nocturne::fr

#endif // !NOCTURNE_JAPANESE

// The font engine (original unit: frFont): building font requests.
//
// A string becomes a font request: one text record per character, each
// pointing at a glyph in the texture cache. Glyphs are decoded on first use
// from the font's Huffman-compressed data into a 24x24 cell of the font
// texture, and shared until no text uses them. Requests chain into pages
// (frCombineFontRequestEx); a chain is destroyed at once or after the frame
// that still draws it.
#include "nocturne/interface/font.hpp"

#include <cstring>

#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"

namespace nocturne::fr {

namespace {

constexpr uint32_t kSettings = 0x0054f404;
constexpr uint32_t kStyles = 0x0056ba30;
constexpr uint32_t kTextureCells = 0x0056b668;
constexpr uint32_t kStyleAdvance = 0x00326060;   // int8 per style: the default advance
constexpr uint32_t kLastCode = 0x0054ea00;       // uint16: the last character laid out
constexpr uint32_t kDecodedBytes = 0x00551ea0;   // int32: bytes the last glyph decoded to
constexpr uint32_t kCodes416 = 0x00325b10;       // uint16[416]
constexpr uint32_t kCodes264 = 0x00325e50;       // uint16[264]
constexpr uint32_t kDrawOt = 0x0054f420;         // the ordering table texts are drawn into

// Counters and pools (0x56BB74).
struct Tables {
    int32_t glyphs;              // cached glyphs
    int32_t texts;
    int32_t requests;
    Ptr32<PoolNode> text_pool;
    Ptr32<PoolNode> request_pool;
    uint32_t unknown_88, unknown_8c;
    int32_t texture_width;       // in pixels
    int32_t unknown_94, unknown_98, unknown_9c;
    int32_t texture_base;        // in 64-word blocks (TBP)
};
constexpr uint32_t kTables = 0x0056bb74;

Tables& tables() { return *guest::table<Tables>(kTables); }
TextureCells& textureCells() { return *guest::table<TextureCells>(kTextureCells); }
uint32_t addressOf(const void* p) { return guest::addressOf(p); }
template <class T> T* at(uint32_t address) { return address ? guest::table<T>(address) : nullptr; }

// Every text of a chain, from its last request back.
template <class F> void forEachText(Request* pFRQ, F f)
{
    for (; pFRQ; pFRQ = pFRQ->prev.get())
        for (Text* t = pFRQ->str.get(); t; t = t->next.get())
            f(*t);
}

} // namespace

Settings& settings() { return *guest::table<Settings>(kSettings); }
Style& style(int32_t index) { return guest::table<Style>(kStyles)[index]; }

// ---- pools ---------------------------------------------------------------------------------

// ps2PoolCreate @ 0x001CAB38 (no original name)
// `count` nodes of `size` bytes, in one memory handle (its handle in the word
// before the head). The last node is a sentinel holding the count, leading
// back to the head.
PoolNode* PoolCreate(int32_t size, int32_t count)
{
    uint32_t handle = mem::HandleAllocate((size + 8) * (count + 1) + 4);
    uint32_t base = mem::HandleAcquirePointer(handle);
    std::memcpy(guest::table<uint8_t>(base), &handle, 4);   // stored unaligned-safe
    const uint32_t head = base + 4;
    uint32_t node = head;
    for (int32_t i = 0; i < count; ++i) {
        PoolNode& n = *guest::table<PoolNode>(node);
        n.index = i;
        node += static_cast<uint32_t>(size) + 8;
        n.next.address = node;
    }
    PoolNode& sentinel = *guest::table<PoolNode>(node);
    sentinel.index = count;
    sentinel.next.address = head;
    return guest::table<PoolNode>(head);
}

// ps2FontTakeGlyphSlot @ 0x001CABD8: takes a free node; null when none is left.
void* PoolTake(PoolNode& pool)
{
    PoolNode* node = pool.next.get();
    if (node->index == 0)
        return nullptr;
    pool.next = node->next;
    node->next.address = 0;
    return node + 1;
}

// ps2PoolGive @ 0x001CAC00 (no original name): returns a node taken from the pool.
bool PoolGive(void* element, PoolNode& pool)
{
    if (!element)
        return false;
    PoolNode& node = static_cast<PoolNode*>(element)[-1];
    if (node.next)
        return false;
    node.next = pool.next;
    pool.next.address = addressOf(&node);
    return true;
}

// ---- handles -------------------------------------------------------------------------------

// frInitTextHandle @ 0x001C7660
void frInitTextHandle(Text& pText, uint16_t code, uint8_t style, uint8_t colno, uint32_t color, uint8_t tp)
{
    pText.style = style;
    pText.col_no = colno;
    pText.tp = tp;
    pText.code = code;
    pText.color = color & 0xffffff00;
    pText.mode = settings().mode;
    pText.next.address = 0;
    pText.lx = 0;
    pText.ly = 0;
    pText.lw = 0;
    pText.draw_count = 0;
    pText.glyph.address = 0;
    pText.data = 0;
    pText.prev.address = 0;
}

// frInitFontHandle @ 0x001C76A8
void frInitFontHandle(Request& pFRQ)
{
    pFRQ.strlen = 0;
    pFRQ.draw_spd = 128;
    pFRQ.x = 0;
    pFRQ.y = 0;
    pFRQ.space = 0;
    pFRQ.w_pxls = 0;
    pFRQ.priority = 0;
    pFRQ.prev.address = 0;
    pFRQ.next.address = 0;
    pFRQ.head.address = addressOf(&pFRQ);
    pFRQ.str.address = 0;
    pFRQ.str_end.address = 0;
}

// ---- fonts ---------------------------------------------------------------------------------

namespace {
constexpr uint32_t kStyleLoaded = 0x003261e8;    // int32 per style: 1 once loaded
int32_t& loaded(uint8_t s) { return guest::table<int32_t>(kStyleLoaded)[s]; }
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

// frLoadStyleAll @ 0x001C6CE0: the four fonts every screen uses.
void frLoadStyleAll()
{
    frLoadStyle(0, 0x005358f0);
    frLoadStyle(1, 0x00535900);
    frLoadStyle(2, 0x00535910);
    frLoadStyle(3, 0x00535920);
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

// frDelStyleAll @ 0x001C6D30: unloads every style that has glyphs.
void frDelStyleAll()
{
    for (int i = 0; i <= 8; ++i)
        if (style(i).glyphs)
            frDelFontStyle(static_cast<uint8_t>(i));
}

// frSetExtDic @ 0x001C81B8: the message table's own font (style 8).
void frSetExtDic(uint32_t data) { BindStyle(8, data, 0); }

// frDelExtDic @ 0x001C81D8 (no original name)
void frDelExtDic() { frDelFontStyle(8); }

// 0x001C6300 (no original name)
// Sets the first metric (the space) of a style to {1, width + 1}.
void SetSpaceMetric(uint8_t styleIndex, int8_t width)
{
    uint8_t* metric = guest::table<uint8_t>(style(styleIndex).metric[0]);
    metric[0] = 1;
    metric[1] = static_cast<uint8_t>(width + 1);
}

// ---- the glyph cache -------------------------------------------------------------------------

// frConvertVal2N @ 0x001C6360: the index of the highest set bit (0 for 0 and 1).
uint8_t frConvertVal2N(uint32_t val)
{
    uint8_t n = 0, bits = 0;
    for (; val; val >>= 1) {
        n = bits;
        ++bits;
    }
    return n;
}

// ps2FontResourceIdentity @ 0x001CA9C0 (no original name)
// Returns its argument; the decoder calls it and ignores the result.
uint32_t ResourceIdentity(uint32_t resource) { return resource; }

// ps2FontResolveCompressedSections @ 0x001CA9C8
// A compressed glyph block: the Huffman tree, the bit offsets of each glyph,
// and the bits.
void ResolveGlyphSections(uint32_t resource, uint32_t sections[3])
{
    const uint32_t* header = guest::table<uint32_t>(resource);
    const uint32_t tree = header[0], offsets = header[1], bits = header[6];
    sections[0] = resource + tree;
    sections[1] = resource + tree + offsets;
    sections[2] = resource + tree + offsets + bits;
}

// ps2FontDecodeGlyph @ 0x001CAA18
// Decodes glyph `index`: a Huffman tree of 6-byte nodes {left, right, value}
// (a node whose first half is 0 is a leaf), walked by the glyph's bits, read
// from 16-bit words low bit first. Returns the bytes written (also kept at
// 0x551EA0). At least one bit is read even for an empty glyph.
int32_t DecodeGlyph(uint8_t* output, int32_t index, const uint32_t sections[3])
{
    const uint32_t tree = sections[0];
    const uint32_t* offsets = guest::table<uint32_t>(sections[1] + static_cast<uint32_t>(index) * 4);
    const uint32_t start = offsets[0], end = offsets[1];
    auto half = [](uint32_t address) { return static_cast<uint32_t>(*guest::table<uint16_t>(address)); };
    uint32_t word = sections[2] + (start >> 4) * 2;
    uint32_t remaining = end - start;
    uint32_t packed = (half(word) | 0x10000) >> (start & 15);   // a marker bit above the data
    uint32_t node = tree + 2;
    int32_t count = 0;
    do {
        uint32_t child = half(node + (packed & 1) * 2);
        node = tree + child * 6 + 2;
        packed >>= 1;
        if (half(node) == 0) {
            output[count++] = *guest::table<uint8_t>(node + 2);
            node = tree + 2;
        }
        --remaining;
        if (packed == 1) {
            word += 2;
            packed = half(word) | 0x10000;
        }
    } while (remaining);
    *guest::table<int32_t>(kDecodedBytes) = count;
    return count;
}

// ps2FontAllocateDecodedGlyph @ 0x001C74E8: a glyph's pixels, in a new block.
uint32_t DecodeGlyphPixels(uint8_t styleIndex, int32_t index)
{
    const Style& s = style(styleIndex);
    uint32_t output = mem::PoolAllocate(0x120);
    uint32_t sections[3];
    ResolveGlyphSections(s.glyphs, sections);
    DecodeGlyph(guest::table<uint8_t>(output), index, sections);
    return output;
}

// ps2FontTakeTextureSlot @ 0x001C6018: a free cell of the font texture, or null.
TextureCell* TakeTextureCell()
{
    TextureCells& cells = textureCells();
    TextureCell* cell = cells.ring->next.get();
    if (cell->index == 0)
        return nullptr;
    cell->prev->next = cell->next;
    --cells.free;
    cell->next->prev = cell->prev;
    return cell;
}

// ps2FontGiveTextureSlot @ 0x001C6068 (no original name): back to the ring.
void GiveTextureCell(TextureCell& cell)
{
    TextureCells& cells = textureCells();
    TextureCell& ring = *cells.ring;
    Ptr32<TextureCell> next = ring.next;
    cell.prev.address = addressOf(&ring);
    cell.next = next;
    ++cells.free;
    ring.next.address = addressOf(&cell);
    next->prev.address = addressOf(&cell);
}

// ps2FontCreateTextureGlyph @ 0x001C7408
// Puts pixels in a free texture cell and queues their upload; returns the
// cell's glyph record (one reference).
Glyph* CreateTextureGlyph(int32_t width, int32_t height, uint32_t pixels, bool owned)
{
    TextureCell* cell = TakeTextureCell();
    Glyph& glyph = *cell->glyph;
    glyph.refs = 1;
    glyph.cell.address = addressOf(cell);
    tex::UploadRecord record{};
    record.pixels = pixels;
    record.flags = owned ? 2 : 0;
    record.psm = 20;
    record.width = static_cast<uint16_t>(tables().texture_width);
    record.base = static_cast<uint32_t>(tables().texture_base) << 6;
    record.x = static_cast<uint16_t>(cell->x >> 4);
    record.y = static_cast<uint16_t>(cell->y >> 4);
    record.w = static_cast<uint16_t>(width);
    record.h = static_cast<uint16_t>(height);
    tex::QueueUpload(record);
    return &glyph;
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

// ps2FontReleaseGlyph @ 0x001C6E50 (no original name)
// Once no text uses a text's glyph, frees its cell.
void ReleaseGlyph(Text& text)
{
    Glyph* glyph = text.glyph.get();
    if (!glyph || glyph->refs != 0)
        return;
    TextureCell* cell = glyph->cell.get();
    guest::table<uint32_t>(style(text.style).cache)[glyph->index] = 0;
    GiveTextureCell(*cell);
    --tables().glyphs;
}

// The glyph number of a character code: ASCII from 32; two-byte codes from
// 0x8080, 128 per lead byte.
int32_t glyphIndex(uint16_t code)
{
    if (code < 32)
        return 0;
    if (code < 128)
        return code - 32;
    uint32_t value = static_cast<uint32_t>(code) - 0x8080;
    return static_cast<int32_t>(((value & 0xff00) >> 1) + (value & 127));
}

// ---- layout -----------------------------------------------------------------------------------

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

// frGetStrWidth @ 0x001C8230: the advances of a request's texts plus its spacing.
int32_t frGetStrWidth(const Request& pFRQ)
{
    int32_t sum = 0;
    for (const Text* t = pFRQ.str.get(); t; t = t->next.get())
        sum += t->lw + pFRQ.space;
    return sum;
}

// 0x001C8268 (no original name)
// The width of a whole chain, from its first request on.
int32_t frGetChainWidth(const Request& pFRQ)
{
    int32_t sum = 0;
    for (const Request* r = pFRQ.head.get(); r; r = r->next.get())
        for (const Text* t = r->str.get(); t; t = t->next.get())
            sum += t->lw + r->space;
    return sum;
}

// 0x001C6270 (no original name): lays out a request's texts again.
void RelayoutRequest(Request& pFRQ)
{
    for (Text* t = pFRQ.str.get(); t; t = t->next.get())
        frGetXShiftLev(*t, glyphIndex(t->code), false);
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

// ---- building requests -------------------------------------------------------------------------

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

namespace {

Request* newRequest()
{
    Request* r = static_cast<Request*>(PoolTake(*tables().request_pool));
    ++tables().requests;
    frInitFontHandle(*r);
    return r;
}


} // namespace

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

// frLinkFontString @ 0x001C7828
// A string as a new request chained after pFRQ (on the same line, or below
// for a line feed); pFRQ unchanged if the string can't be laid out.
Request* frLinkFontString(const uint8_t* pStr, int8_t styleIndex, int8_t colno, int8_t tp, Request* pFRQ)
{
    Request* created = frSetFontString(pStr, styleIndex, colno, tp, nullptr, false);
    return created ? frCombineFontRequest(pFRQ, created) : pFRQ;
}

// ps2FontCreateControlGlyph @ 0x001C7288
// Appends a text that draws `data` (a name glyph) instead of a font glyph.
Request* AppendControlText(uint32_t data, Request* pFRQ)
{
    if (!pFRQ)
        pFRQ = newRequest();
    Text* text = static_cast<Text*>(PoolTake(*tables().text_pool));
    Text* previous = pFRQ->str_end.get();
    ++tables().texts;
    frInitTextHandle(*text, 0, 0, 0, 0xa09dc300, 0);
    if (previous)
        previous->next.address = addressOf(text);
    else
        pFRQ->str.address = addressOf(text);
    text->data = data;
    text->lw = guest::table<int8_t>(kStyleAdvance)[0];
    text->width = static_cast<uint8_t>(frGetDefaultFontWidth(0));
    text->height = static_cast<uint8_t>(frGetDefaultFontHeight(0));
    text->prev.address = addressOf(previous);
    pFRQ->str_end.address = addressOf(text);
    ++pFRQ->strlen;
    pFRQ->w_pxls += text->lw;
    pFRQ->x_size = text->width;
    pFRQ->y_size = text->height;
    return pFRQ;
}

// 0x001C73B8 (no original name): a control text as a request chained after pFRQ.
Request* LinkControlText(uint32_t data, Request* pFRQ)
{
    Request* created = AppendControlText(data, nullptr);
    return created ? frCombineFontRequest(pFRQ, created) : nullptr;
}

// frCombineFontRequest @ 0x001C8108
Request* frCombineFontRequest(Request* pFRQ1, Request* pFRQ2) { return frCombineFontRequestEx(pFRQ1, pFRQ2, 1); }

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

// frDestroyFontRequestNow @ 0x001C6F08
// Frees a chain (from its last request back): its requests, their texts,
// and glyphs and name banks no longer used.
void frDestroyFontRequestNow(Request* pFRQ)
{
    Tables& tbl = tables();
    while (pFRQ) {
        for (Text* t = pFRQ->str.get(); t;) {
            Text* next = t->next.get();
            if (t->data == 0) {
                --t->glyph->refs;
                ReleaseGlyph(*t);
            } else {
                ReleaseNameBank(*guest::table<int8_t>(t->data));
            }
            PoolGive(t, *tbl.text_pool);
            --tbl.texts;
            t = next;
        }
        Request* prev = pFRQ->prev.get();
        PoolGive(pFRQ, *tbl.request_pool);
        --tbl.requests;
        pFRQ = prev;
    }
}

// frDestroyFontRequestAfter @ 0x001C6FF8
// Frees a chain once the frame being drawn is done with it: it joins the
// current frame's list, freed when that buffer comes round again.
void frDestroyFontRequestAfter(Request* pFRQ)
{
    uint32_t& pending = guest::table<uint32_t>(0x0056bbc4)[dds3::GetFrameIndex() & 0xff];
    pending = addressOf(frCombineFontRequestEx(at<Request>(pending), pFRQ, 0));
}

// 0x001C7C30 (no original name)
// One step of fading out the texts with tp 2: alpha down by 8, 2 units
// lower. True while any is still visible.
bool frFadeOutText(Request* pFRQ)
{
    bool fading = false;
    forEachText(pFRQ, [&](Text& t) {
        if (t.tp != 2)
            return;
        int32_t alpha = static_cast<int32_t>(t.color & 0xff);
        if (!alpha)
            return;
        alpha -= 8;
        fading = true;
        if (alpha < 0)
            alpha = 0;
        t.ly += 16;
        t.color = (t.color & 0xffffff00) | static_cast<uint32_t>(alpha);
    });
    return fading;
}

// 0x001C6EC8 (no original name)
// Fades a chain out, then frees it; returns it while it is still fading.
Request* frDestroyFontRequestFade(Request* pFRQ)
{
    if (frFadeOutText(pFRQ))
        return pFRQ;
    frDestroyFontRequestNow(pFRQ);
    return nullptr;
}

// ---- settings of a request ---------------------------------------------------------------------

// frSetDrawSpeed @ 0x001C7A60: characters appear at speed * 2 (128: at once).
void frSetDrawSpeed(Request& pFRQ, uint8_t speed)
{
    uint32_t v = static_cast<uint32_t>(speed) * 2;
    pFRQ.draw_spd = static_cast<uint8_t>(v > 128 ? 128 : v);
}

// frSetFontSpace @ 0x001C7A88
void frSetFontSpace(Request& pFRQ, int32_t space)
{
    pFRQ.space = static_cast<int8_t>(space);
    pFRQ.w_pxls = frGetStrWidth(pFRQ);
}

// frSetDrawPosition @ 0x001C7B30
void frSetDrawPosition(Request& pFRQ, int32_t x, int32_t y)
{
    pFRQ.y = y;
    pFRQ.x = x;
}

// frSetPriority @ 0x001C7B40: z, in 1/16 units.
void frSetPriority(Request& pFRQ, uint32_t pri) { pFRQ.priority = pri >> 4; }

// frSetFontSize @ 0x001C7AB8 (no original name)
// Sets the character size of a chain (each text's advance becomes the width).
void frSetFontSize(Request& pFRQ, int32_t width, int32_t height)
{
    pFRQ.x_size = static_cast<int16_t>(width);
    pFRQ.y_size = static_cast<int16_t>(height);
    forEachText(&pFRQ, [&](Text& t) {
        t.lw = width;
        t.width = static_cast<uint8_t>(width);
        t.height = static_cast<uint8_t>(height);
    });
    pFRQ.w_pxls = frGetStrWidth(pFRQ);
}

// frSetFontColNo @ 0x001C7B50 (no original name): every text's palette.
void frSetFontColNo(Request* pFRQ, uint8_t colno)
{
    forEachText(pFRQ, [&](Text& t) { t.col_no = colno; });
}

// frSetFontColor @ 0x001C7BA8: every text's color.
void frSetFontColor(Request* pFRQ, uint32_t color)
{
    for (; pFRQ; pFRQ = pFRQ->prev.get())
        for (Text* t = pFRQ->str.get(); t; t = t->next.get())
            t->color = color;
}

// frEnableMode @ 0x001C7C00: returns the old flags.
uint8_t frEnableMode(uint8_t flag)
{
    uint8_t old = settings().mode;
    settings().mode = old | flag;
    return old;
}

// frDisableMode @ 0x001C7C10
uint8_t frDisableMode(uint8_t flag)
{
    uint8_t old = settings().mode;
    settings().mode = static_cast<uint8_t>(old & ~flag);
    return old;
}

// frSetFontDrawOT @ 0x001C7C28
void frSetFontDrawOT(uint32_t ot) { *guest::table<uint32_t>(kDrawOt) = ot; }

// frSetStepY @ 0x001C8490 (no original name): the line height of messages.
void frSetStepY(int32_t step) { settings().step = step; }

// frResetStepY @ 0x001C8480 (no original name)
void frResetStepY() { settings().step = 0x14; }

} // namespace nocturne::fr

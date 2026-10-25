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

#include "nocturne/address.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/external.hpp"

namespace nocturne::fr {

namespace {

// What differs by version is in each version's font_layout.cpp
// (docs/versions.md).
constexpr uint32_t kSettings = addr(0x0054f404);
constexpr uint32_t kStyles = addr(0x0056ba30);
constexpr uint32_t kTextureCells = addr(0x0056b668);
constexpr uint32_t kStyleAdvance = addr(0x00326060);   // int8 per style: the default advance
constexpr uint32_t kDecodedBytes = addr(0x00551ea0);   // int32: bytes the last glyph decoded to
constexpr uint32_t kDrawOt = addr(0x0054f420);         // the ordering table texts are drawn into

// The counters follow the nine styles, as the original addresses them.
constexpr uint32_t kTables = kStyles + 9 * sizeof(Style);

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
Tables& tables() { return *guest::table<Tables>(kTables); }
int32_t defaultAdvance(uint8_t s) { return guest::table<int8_t>(kStyleAdvance)[s]; }

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

// frLoadStyleAll @ 0x001C6CE0: the four fonts every screen uses.
void frLoadStyleAll()
{
    frLoadStyle(0, addr(0x005358f0));
    frLoadStyle(1, addr(0x00535900));
    frLoadStyle(2, addr(0x00535910));
    frLoadStyle(3, addr(0x00535920));
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

#if NOCTURNE_US
// 0x001C6270 (no original name): lays out a request's texts again. Nothing
// calls it; the JP builds don't have it.
void RelayoutRequest(Request& pFRQ)
{
    for (Text* t = pFRQ.str.get(); t; t = t->next.get())
        frGetXShiftLev(*t, glyphIndex(t->code), false);
}
#endif

// newRequest: a request from the pool, counted (in frSetFontString and
// ps2FontCreateControlGlyph).
Request* newRequest()
{
    Request* r = static_cast<Request*>(PoolTake(*tables().request_pool));
    ++tables().requests;
    frInitFontHandle(*r);
    return r;
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
    text->lw = defaultAdvance(0);
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
    uint32_t& pending = guest::table<uint32_t>(addr(0x0056bbc4))[dds3::GetFrameIndex() & 0xff];
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
void frResetStepY() { settings().step = kDefaultLineStep; }

} // namespace nocturne::fr

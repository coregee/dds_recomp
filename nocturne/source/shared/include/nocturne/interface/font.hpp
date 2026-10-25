// The font engine (original unit: frFont): text laid out as chains of font
// requests, one text record per character, with glyphs decoded from the
// game's .fnt files into a texture cache.
//
// Records are in their PS2 layout; field names are the HD remaster's where it
// has them.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/build.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::fr {

struct Glyph;

// _TEXT: one character of a font request.
struct Text {
    uint16_t code;               // the character code (ASCII, or a 2-byte code)
    uint16_t draw_count;
    int32_t lx, ly;              // offset from the request's position
    int32_t lw;                  // advance
    uint32_t color;              // RGBA; the low byte is the alpha
    uint8_t col_no;              // palette
    uint8_t style;               // font (0..8)
    uint8_t tp;                  // 2: fades out (frFadeOutText)
    uint8_t mode;                // frEnableMode flags when created
    uint8_t width, height;       // character size
    uint8_t pad1a[2];
    Ptr32<Glyph> glyph;          // the cached glyph, or null for a control text
    uint32_t data;               // control text: its data (a name bitmap)
    Ptr32<Text> prev;
    Ptr32<Text> next;
};
static_assert(offsetof(Text, color) == 0x10 && offsetof(Text, col_no) == 0x14 && offsetof(Text, tp) == 0x16);
static_assert(offsetof(Text, width) == 0x18 && offsetof(Text, glyph) == 0x1c && offsetof(Text, prev) == 0x24);
static_assert(sizeof(Text) == 0x2c);

// _FRQ: a font request, one run of text on one line. A message page is a
// chain of them; a new line starts a request with a new `y`. A chain is
// handled by its last request: `prev` leads back to the first, which `head`
// points at.
struct Request {
    uint8_t draw_spd;            // drawing speed, 0..128 (128: all at once)
    int8_t space;                // extra advance per character
    uint8_t pad02[2];
    int32_t x, y;                // in 1/16 pixels horizontally, 1/8 vertically
    int32_t w_pxls;              // width: the characters' advances plus spacing
    int16_t x_size, y_size;      // character size; y_size is the line height
    uint32_t priority;           // z
    int32_t strlen;              // characters
    Ptr32<Text> str, str_end;
    Ptr32<Request> prev;         // the request before it in the chain
    Ptr32<Request> next;         // the request after it
    Ptr32<Request> head;         // the chain's first request (itself when alone)
};
static_assert(sizeof(Request) == 0x30);
static_assert(offsetof(Request, y_size) == 0x12 && offsetof(Request, priority) == 0x14 && offsetof(Request, prev) == 0x24);

// The header of a .fnt file (game/dds3/font/).
struct FontHeader {
    uint32_t header_size;        // 0x24
    uint32_t data_size;
    uint8_t unknown_08[2];
    uint8_t palettes;            // 16-color palettes (64 bytes each) after the header
    uint8_t unknown_0b[3];
    uint16_t glyphs;             // 0x2C3 in the fonts on disc
    uint16_t width, height;      // 24 x 24
    uint16_t glyph_bytes;        // 0x120: 4 bits per pixel
    uint8_t metrics;             // per-glyph advance tables follow the palettes
    uint8_t unknown_17;
    uint32_t names;              // offset of a name table, or 0
};
static_assert(offsetof(FontHeader, glyphs) == 0xe && offsetof(FontHeader, metrics) == 0x16 && offsetof(FontHeader, names) == 0x18);

// A loaded font (one of nine styles, US 0x56BA30): pointers into its file.
struct Style {
    uint32_t handle;             // the memory handle holding the file, or 0
    Ptr32<FontHeader> data;
    int32_t metric_size[2];      // bytes in each metric table
    uint32_t metric[2];          // the tables: {left, right} per glyph
    uint32_t cache;              // per glyph: its cached Glyph, or 0 (a zeroed array in the file)
    uint32_t glyphs;             // the compressed glyphs
#if !NOCTURNE_JAPANESE
    uint32_t names;              // the file's name table (the US engine's only)
#endif
};
static_assert(sizeof(Style) == (kBuild.japanese ? 0x20 : 0x24));

// Font engine globals (US 0x54F404). The JP engine has no size override,
// so no base and space widths.
struct Settings {
    uint32_t result;             // gMessageRequestResult: how the last page ended (frGetMessageResult)
    int8_t space;                // gMessageSpaceX
    uint8_t pad05[3];
    int32_t step;                // gMessageStepY: line height, in 1/8 units
#if !NOCTURNE_JAPANESE
    int32_t base_width;          // the advance of styles 0 and 1 (frSetBaseWidth)
    int32_t space_width;         // extra advance of a space in styles 0 and 1
    uint32_t unknown_14;
#endif
    uint8_t mode;                // gModeFlag (frEnableMode)
    uint8_t pad_mode[7];
    uint8_t style;               // the style of the last frSetFontString
};
static_assert(offsetof(Settings, mode) == (kBuild.japanese ? 0xc : 0x18) &&
              offsetof(Settings, style) == (kBuild.japanese ? 0x14 : 0x20));

inline constexpr int32_t kDefaultLineStep = kBuild.japanese ? 0x19 : 0x14;   // frResetStepY

#if NOCTURNE_JAPANESE
// The shadow offset a glyph gets with kModeShadow: 24 for some, else 0
// (the US engine: always 24; font_layout_jp.cpp).
int32_t shadowOffset(int8_t style, int32_t index);
#endif

// A cell of the font texture (0x20 bytes, a ring at 0x56B668).
struct TextureCell {
    int32_t index;
    int32_t x, y;                // in the texture, in 1/16 pixels
    int32_t x2;
    uint32_t unknown_10;
    Ptr32<Glyph> glyph;          // the glyph record that owns it
    Ptr32<TextureCell> prev, next;
};
static_assert(sizeof(TextureCell) == 0x20);

// The texture cells in use and free.
struct TextureCells {
    uint32_t handle;
    uint32_t pixel_handle;
    int32_t width, height;
    int32_t bytes;
    int32_t count;
    int32_t free;                // cells on the ring
    Ptr32<TextureCell> ring;     // the ring's anchor (cell 0)
};

// A glyph in the texture cache.
struct Glyph {
    uint16_t index;              // glyph number in its font (or the name bank)
    uint16_t pad02;
    uint16_t refs;               // texts using it
    uint16_t pad06;
    Ptr32<TextureCell> cell;
};

// A fixed-size pool: a free list threaded through the nodes. Node 0 is the
// head (its `next` is the first free node); a node in use has `next` 0; a
// node's payload follows its 8-byte header.
struct PoolNode {
    int32_t index;
    Ptr32<PoolNode> next;
};

// frMsgInfo_t: the state of laying out one message page.
struct MessageInfo {
    int32_t x, y;                // where the next request starts
    uint32_t z;                  // in 1/16 units
    int8_t style, colno, tp;
    uint8_t speed;
    uint32_t text;               // the page
    Ptr32<Request> font;         // the chain so far
    int32_t pos;                 // read position in the text
    uint8_t newline;             // start a new request before the next character
    uint8_t position;            // and move it to x, y
    uint8_t pad1e[2];
};
static_assert(sizeof(MessageInfo) == 0x20);

// Mode flags (Settings::mode, copied to each text).
enum : uint8_t {
    kModeMetrics = 1,            // use the font's per-glyph advances
    kModeParsing = 2,
    kModeCompact = 4,            // lines break by themselves; '\n' is ignored
    kModeShadow = 16,            // texts get a 24-unit shadow offset
};

// Counters and pools, after the nine styles (US Maniax 0x56BB74).
struct Tables {
    int32_t glyphs;              // cached glyphs
    int32_t texts;
    int32_t requests;
    Ptr32<PoolNode> text_pool;
    Ptr32<PoolNode> request_pool;
    uint32_t unknown_14, unknown_18;
    int32_t texture_width;       // in pixels
    int32_t unknown_20, unknown_24, unknown_28;
    int32_t texture_base;        // in 64-word blocks (TBP)
};

Settings& settings();
Style& style(int32_t index);
Tables& tables();
int32_t defaultAdvance(uint8_t style);   // a style's default advance (US Maniax 0x326060)
Request* newRequest();                   // a request from the pool, counted

// Pools
PoolNode* PoolCreate(int32_t size, int32_t count);
void* PoolTake(PoolNode& pool);
bool PoolGive(void* element, PoolNode& pool);

// Fonts. [version] marks what each version's font_layout.cpp defines.
void BindStyle(uint8_t style, uint32_t data, uint32_t handle);   // [version]
void frLoadStyle(uint8_t style, uint32_t name);                  // [version]
void frLoadStyleAll();
void frDelFontStyle(uint8_t style);   // [version]
void frDelStyleAll();
void frSetExtDic(uint32_t data);
void frDelExtDic();
void SetSpaceMetric(uint8_t style, int8_t width);

// Handles
void frInitTextHandle(Text& pText, uint16_t code, uint8_t style, uint8_t colno, uint32_t color, uint8_t tp);
void frInitFontHandle(Request& pFRQ);

// The glyph cache
uint8_t frConvertVal2N(uint32_t val);
uint32_t ResourceIdentity(uint32_t resource);
void ResolveGlyphSections(uint32_t resource, uint32_t sections[3]);
int32_t DecodeGlyph(uint8_t* output, int32_t index, const uint32_t sections[3]);
uint32_t DecodeGlyphPixels(uint8_t style, int32_t index);
TextureCell* TakeTextureCell();
Glyph* CreateTextureGlyph(int32_t width, int32_t height, uint32_t pixels, bool owned);
void GiveTextureCell(TextureCell& cell);
Glyph* AcquireGlyph(Text& text, int32_t index);   // [version]
void ReleaseGlyph(Text& text);
int32_t glyphIndex(uint16_t code);

// Layout
int32_t frGetDefaultFontWidth(uint8_t style);                    // [version]
int32_t frGetDefaultFontHeight(uint8_t style);                   // [version]
void frSetBaseWidth(int64_t width);                              // [version]
void frGetXShiftLev(Text& pText, int32_t index, bool first);     // [version]
int32_t frGetStrWidth(const Request& pFRQ);
int32_t frGetChainWidth(const Request& pFRQ);
#if !NOCTURNE_JAPANESE
void RelayoutRequest(Request& pFRQ);   // (the US release's only)
int32_t frGetFontWidth(uint8_t style);
int32_t frGetFontHeight(uint8_t style);
int64_t FindCode416(uint16_t code);
int64_t FindCode264(uint16_t code);
void RecordLastCode(uint16_t code);
#endif

// Building requests
Text* frSetFont(uint16_t code, uint8_t style, uint8_t colno, uint8_t tp, bool first);   // [version]
Request* frSetFontString(const uint8_t* pStr, int8_t style, int8_t colno, int8_t tp, Request* pFRQ,
                         bool first);                            // [version]
Request* frLinkFontString(const uint8_t* pStr, int8_t style, int8_t colno, int8_t tp, Request* pFRQ);
Request* AppendControlText(uint32_t data, Request* pFRQ);
Request* LinkControlText(uint32_t data, Request* pFRQ);
Request* frCombineFontRequest(Request* pFRQ1, Request* pFRQ2);
Request* frCombineFontRequestEx(Request* pFRQ1, Request* pFRQ2, uint64_t mode);   // [version]
void frDestroyFontRequestNow(Request* pFRQ);
void frDestroyFontRequestAfter(Request* pFRQ);
bool frFadeOutText(Request* pFRQ);
Request* frDestroyFontRequestFade(Request* pFRQ);

// Settings of a request
void frSetDrawSpeed(Request& pFRQ, uint8_t speed);
void frSetFontSpace(Request& pFRQ, int32_t space);
void frSetDrawPosition(Request& pFRQ, int32_t x, int32_t y);
void frSetPriority(Request& pFRQ, uint32_t pri);
void frSetFontSize(Request& pFRQ, int32_t width, int32_t height);
void frSetFontColNo(Request* pFRQ, uint8_t colno);
void frSetFontColor(Request* pFRQ, uint32_t color);
uint8_t frEnableMode(uint8_t flag);
uint8_t frDisableMode(uint8_t flag);
void frSetFontDrawOT(uint32_t ot);
void frSetStepY(int32_t step);
void frResetStepY();

// Entered names and pages: each version's font_message.cpp. (The JP
// builds' name functions leave colno to their callers.)
void LoadNameBank(int8_t bank, bool given, int8_t count, uint32_t pixels);
void ReferenceNameBank(int8_t bank, bool given);
void ReleaseNameBank(int8_t bank);
Request* AppendNameLetter(int8_t bank, int8_t index, Request* pFRQ);
Request* AppendFamilyName(int8_t bank, Request* pFRQ, int8_t colno);
Request* AppendGivenName(int8_t bank, Request* pFRQ, int8_t colno);
Request* AppendFullName(int8_t bank, Request* pFRQ, int8_t colno);
Request* AppendNameText(int8_t bank, int8_t style, Request* pFRQ, int8_t colno);
// A string one character per request, at (x, y) and depth z (the battle's
// help line and level-up rows).
Request* LinkLetters(int32_t x, int32_t y, uint32_t z, uint32_t color, const uint8_t* pStr, int8_t styleIndex,
                     int8_t keepMode, Request* chain);
Request* LinkSpacedLetters(int32_t x, int32_t y, uint32_t z, uint32_t color, const uint8_t* pStr, Request* chain);

// Laying out a page (font_message.cpp)
void frCreateNewHandle(MessageInfo& m);
void AdvanceMessageLine(MessageInfo& m);
void AppendVariable(uint8_t index, MessageInfo& m);
bool frAnalyzeTag(uint8_t prefix, MessageInfo& m);
Request* frAnalyzeMessage(MessageInfo& m);
Request* MessageRequestEx(int32_t x, int32_t y, uint32_t z, uint8_t style, uint8_t colno, uint8_t tp, uint8_t speed,
                          uint32_t text, Request* pFRQ);
Request* MessageRequest(int32_t x, int32_t y, uint8_t style, uint8_t colno, uint8_t tp, uint8_t speed, uint32_t text,
                        Request* pFRQ);
Request* MessageRequestPlain(int32_t x, int32_t y, uint32_t text, Request* pFRQ);
// (0x1CA508) a short string in style 3, placed at x, y (1/16 units), depth z, in a color.
Request* StringRequest(int32_t x, int32_t y, uint32_t z, uint32_t color, uint32_t text, Request* pFRQ);
Request* MessageRequestKeepSpace(int32_t x, int32_t y, uint32_t z, uint8_t style, uint8_t colno, uint8_t tp,
                                 uint8_t speed, uint32_t text);
int64_t frGetMessageResult(int64_t mask);
void frSetVariableRequest(int32_t index, uint32_t pstr);
#if !NOCTURNE_JAPANESE
void AppendSpecialCode(MessageInfo& m, uint16_t code);
int32_t ControlCodeLength(uint16_t code);
int32_t CountMessageLines(const uint8_t* text);
void CopyMessageLine(const uint8_t* text, uint8_t* out, int32_t line);
#endif

} // namespace nocturne::fr

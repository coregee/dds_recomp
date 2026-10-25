// Font engine (frFont): the rewrite against the original instructions, run
// by the EE interpreter in the same fake world, with the game's own fonts.
// They run on both engines (the JP builds' through their own
// font_layout.cpp and font_message.cpp); what only US Maniax's engine has
// is tested under NOCTURNE_US_FONT_ENGINE.
#include <cstring>
#include <iterator>

#include "harness.hpp"
#include "version_map.hpp"
#include "interface_world.hpp"
#include "nocturne/interface/font.hpp"

extern "C" {
uint32_t ps2PoolAllocate(int32_t);
}

namespace difftest {

namespace {

using namespace nocturne::fr;
using iface::A;
using iface::addr;
using iface::I;
using iface::orig;
using iface::origVoid;

constexpr uint32_t kInfo = FW_SCRATCH;            // a MessageInfo
constexpr uint32_t kBuffer = FW_SCRATCH + 0x40;   // scratch for strings and glyph pixels

template <class T> T* P(uint64_t a) { return a ? &at<T>(static_cast<uint32_t>(a)) : nullptr; }
const uint8_t* bytes(uint64_t a) { return &at<uint8_t>(static_cast<uint32_t>(a)); }
uint64_t R(const void* p) { return norm(static_cast<int32_t>(addr(p))); }

// A world with fonts; sometimes a message table loaded for real pages.
void world(Gen& g)
{
    std::memset(fw_ram + FW_MES_STATE, 0, FW_MES_POOL_END - FW_MES_STATE);
    iface::loadTable(g, true);
    iface::fontWorld(g);
}

uint32_t pool(Gen& g) { return g.chance(50) ? tables().text_pool.address : tables().request_pool.address; }

uint32_t guestString(const char* s)
{
    uint32_t length = static_cast<uint32_t>(std::strlen(s)) + 1;
    uint32_t p = ps2PoolAllocate(static_cast<int32_t>(length));
    std::memcpy(fw_ram + p, s, length);
    return p;
}

uint32_t someString(Gen& g)
{
    static const char* const strings[] = {"Pixie", "Hello, world!", "^caret^", "  spaced  ", "\x81\x40\x81\x41\x82\x60", "x",
                                          "", "Jack\x80\xe2\x80\xe3", "1!1!",
#if NOCTURNE_JAPANESE   // (kana and kanji: past the US fonts' glyphs)
                                          "\x82\xa0\x82\xa2\x82\xa4", "\x83\x73\x83\x4e\x83\x56\x81\x5b",
                                          "\x88\xa0\x89\x9f\x93\xfa", "\x8a\xbf\x8e\x9a",
#endif
    };
    return guestString(strings[g.below(static_cast<uint32_t>(std::size(strings)))]);
}

int8_t someStyle(Gen& g)
{
    return static_cast<int8_t>(g.chance(10) ? -1 : g.chance(10) && style(8).glyphs ? 8 : g.range(0, 3));
}

// A MessageInfo at kInfo, laying out `text`.
void info(Gen& g, uint32_t text, bool withFont)
{
    MessageInfo& m = at<MessageInfo>(kInfo);
    m.x = g.range(0, 0x2000);
    m.y = g.range(0, 0x1000);
    m.z = g.below(0x10000);
    m.style = static_cast<int8_t>(g.chance(10) && style(8).glyphs ? 8 : g.range(0, 3));   // 8 only when loaded
    m.colno = static_cast<int8_t>(g.range(0, 5));
    m.tp = static_cast<int8_t>(g.range(0, 2));
    m.speed = static_cast<uint8_t>(g.below(140));
    m.text = text;
    m.font.address = withFont && g.chance(60) ? addr(iface::chain(g, m.x, m.y)) : 0;
    m.pos = 0;
    m.newline = static_cast<uint8_t>(!m.font || g.chance(50));   // a page starts with a request pending
    m.position = static_cast<uint8_t>(g.below(2));
}

using Body = std::function<Pair(Gen&)>;

} // namespace

void addFontTests(std::vector<TestCase>& t)
{
    auto add = [&](const char* name, Body body) {
        t.push_back({name, [body](Gen& g) {
            world(g);
            return body(g);
        }});
    };

    // ---- pools ----
    add("ps2PoolCreate", [](Gen& g) {
        int32_t size = g.pick<int32_t>({0x2c, 0x30, 8, 12}), count = g.range(1, 20);
        return Pair{[=] { return orig(0x001cab38, {I(size), I(count)}); }, [=] { return R(PoolCreate(size, count)); }};
    });
    add("PoolTake", [](Gen& g) {
        uint32_t p = pool(g);
        if (g.chance(10)) {   // an exhausted pool
            for (int i = 0; i < 400 && PoolTake(at<PoolNode>(p)); ++i) {}
        }
        return Pair{[=] { return orig(0x001cabd8, {p}); }, [=] { return R(PoolTake(at<PoolNode>(p))); }};
    });
    add("PoolGive", [](Gen& g) {
        uint32_t p = pool(g);
        void* e = PoolTake(at<PoolNode>(p));
        uint64_t element = g.chance(10) ? 0 : g.chance(20) ? addr(e) + 0x30 : addr(e);
        return Pair{[=] { return orig(0x001cac00, {element, p}); }, [=] { return norm(PoolGive(P<uint8_t>(element), at<PoolNode>(p))); }};
    });

    // ---- handles ----
    add("frInitTextHandle", [](Gen& g) {
        uint32_t text = kBuffer;
        uint16_t code = static_cast<uint16_t>(g.below(0x10000));
        uint8_t style = static_cast<uint8_t>(g.below(9)), col = static_cast<uint8_t>(g.below(8)), tp = static_cast<uint8_t>(g.below(3));
        uint32_t color = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVoid(0x001c7660, {text, code, style, col, color, tp}); },
                    [=] { frInitTextHandle(at<Text>(text), code, style, col, color, tp); return uint64_t{0}; }};
    });
    add("frInitFontHandle", [](Gen&) {
        return Pair{[=] { return origVoid(0x001c76a8, {kBuffer}); }, [=] { frInitFontHandle(at<Request>(kBuffer)); return uint64_t{0}; }};
    });

    // ---- fonts ----
    add("ps2FontBindContext", [](Gen& g) {
        uint8_t style = static_cast<uint8_t>(g.below(9));
        uint32_t file = FW_FONTS + g.pick<uint32_t>({0x00000, 0x18000, 0x2e000, 0x33000});
        bool byHandle = g.chance(50);
        uint32_t data = byHandle ? 0 : file, handle = byHandle ? file + 1 : 0;
        return Pair{[=] { return origVoid(0x001c6b68, {style, data, handle}); }, [=] { BindStyle(style, data, handle); return uint64_t{0}; }};
    });
    add("frLoadStyle", [](Gen& g) {
        uint8_t style = static_cast<uint8_t>(g.below(4));
        uint32_t name = difftest::version::dataOrDie(0x005358f0) + 0x10 * g.below(4);
        return Pair{[=] { return origVoid(0x001c6858, {style, name}); }, [=] { frLoadStyle(style, name); return uint64_t{0}; }};
    });
    add("frLoadStyleAll", [](Gen&) { return Pair{[] { return origVoid(0x001c6ce0, {}); }, [] { frLoadStyleAll(); return uint64_t{0}; }}; });
    add("frDelFontStyle", [](Gen& g) {
        uint8_t style = static_cast<uint8_t>(g.below(9));
        return Pair{[=] { return origVoid(0x001c6c70, {style}); }, [=] { frDelFontStyle(style); return uint64_t{0}; }};
    });
    add("frDelStyleAll", [](Gen&) { return Pair{[] { return origVoid(0x001c6d30, {}); }, [] { frDelStyleAll(); return uint64_t{0}; }}; });
    add("frSetExtDic", [](Gen&) {
        return Pair{[] { return origVoid(0x001c81b8, {FW_FONTS + 0x2e000}); }, [] { frSetExtDic(FW_FONTS + 0x2e000); return uint64_t{0}; }};
    });
    add("frDelExtDic", [](Gen&) { return Pair{[] { return origVoid(0x001c81d8, {}); }, [] { frDelExtDic(); return uint64_t{0}; }}; });
    add("SetSpaceMetric", [](Gen& g) {
        uint8_t style = static_cast<uint8_t>(g.below(4));
        int8_t width = static_cast<int8_t>(g.range(-3, 30));
        return Pair{[=] { return origVoid(0x001c6300, {style, I(width)}); }, [=] { SetSpaceMetric(style, width); return uint64_t{0}; }};
    });

    // ---- the glyph cache ----
    add("frConvertVal2N", [](Gen& g) {
        uint32_t v = g.chance(30) ? g.below(4) : static_cast<uint32_t>(g.rng()) >> g.below(32);
        return Pair{[=] { return orig(0x001c6360, {v}); }, [=] { return norm(static_cast<int32_t>(static_cast<int8_t>(frConvertVal2N(v)))); }};
    });
    add("ps2FontResourceIdentity", [](Gen& g) {
        uint32_t r = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return orig(0x001ca9c0, {r}); }, [=] { return norm(static_cast<int32_t>(ResourceIdentity(r))); }};
    });
    add("ps2FontResolveCompressedSections", [](Gen& g) {
        uint32_t resource = style(static_cast<int32_t>(g.below(4))).glyphs;
        return Pair{[=] { return origVoid(0x001ca9c8, {resource, kBuffer}); },
                    [=] { ResolveGlyphSections(resource, &at<uint32_t>(kBuffer)); return uint64_t{0}; }};
    });
    add("ps2FontDecodeGlyph", [](Gen& g) {
        const Style& st = style(static_cast<int32_t>(g.below(4)));
        uint32_t resource = st.glyphs;
        ResolveGlyphSections(resource, &at<uint32_t>(kBuffer));
        int32_t index = g.range(0, st.data->glyphs - 1);
        uint32_t out = kBuffer + 0x20;
        return Pair{[=] { return orig(0x001caa18, {out, I(index), resource, kBuffer}); },
                    [=] { return norm(DecodeGlyph(&at<uint8_t>(out), index, &at<uint32_t>(kBuffer))); }};
    });
    add("ps2FontAllocateDecodedGlyph", [](Gen& g) {
        uint8_t style = static_cast<uint8_t>(g.below(4));
        int32_t index = g.range(0, nocturne::fr::style(style).data->glyphs - 1);
        return Pair{[=] { return orig(0x001c74e8, {style, I(index)}); }, [=] { return norm(static_cast<int32_t>(DecodeGlyphPixels(style, index))); }};
    });
    add("ps2FontTakeTextureSlot", [](Gen& g) {
        if (g.chance(10)) {
            while (TakeTextureCell()) {}
        }
        return Pair{[] { return orig(0x001c6018, {}); }, [] { return R(TakeTextureCell()); }};
    });
    add("ps2FontGiveTextureSlot", [](Gen&) {
        TextureCell* c = TakeTextureCell();
        uint32_t cell = addr(c);
        return Pair{[=] { return origVoid(0x001c6068, {cell}); }, [=] { GiveTextureCell(at<TextureCell>(cell)); return uint64_t{0}; }};
    });
    add("ps2FontCreateTextureGlyph", [](Gen& g) {
        int32_t w = g.range(1, 24), h = g.range(1, 24);
        uint32_t pixels = kBuffer;
        bool owned = g.chance(50);
        return Pair{[=] { return orig(0x001c7408, {I(w), I(h), pixels, owned}); },
                    [=] { return R(CreateTextureGlyph(w, h, pixels, owned)); }};
    });
    auto textArg = [](Gen& g) {
        Request* r = iface::chain(g, 0, 0);
        Text* t = r ? r->str.get() : nullptr;
        return addr(t);
    };
    add("ps2FontAcquireCachedGlyph", [=](Gen& g) {
        uint32_t text = textArg(g);
        if (!text)
            text = addr(frSetFont('A', 0, 0, 0, false));
        const int32_t glyphs = style(at<Text>(text).style).data->glyphs;   // (the text's own glyph when the font has it)
        int32_t index = glyphIndex(at<Text>(text).code);
        if (g.chance(50) || index >= glyphs)
            index = g.range(0, glyphs - 1);
        return Pair{[=] { return orig(0x001c7568, {text, I(index)}); }, [=] { return R(AcquireGlyph(at<Text>(text), index)); }};
    });
    add("ps2FontReleaseGlyph", [=](Gen& g) {
        Text* t = frSetFont(static_cast<uint16_t>('A' + g.below(26)), static_cast<uint8_t>(g.below(4)), 0, 0, false);
        if (g.chance(60))
            t->glyph->refs = 0;
        uint32_t text = addr(t);
        return Pair{[=] { return origVoid(0x001c6e50, {text}); }, [=] { ReleaseGlyph(at<Text>(text)); return uint64_t{0}; }};
    });
#if !NOCTURNE_JAPANESE
    add("ps2FontFindCode416", [](Gen& g) {
        uint16_t code = static_cast<uint16_t>(g.chance(50) ? at<uint16_t>(difftest::version::dataOrDie(0x00325b10) + 2 * g.below(416)) : g.below(0x10000));
        return Pair{[=] { return orig(0x001c6098, {code}); }, [=] { return static_cast<uint64_t>(FindCode416(code)); }};
    });
    add("ps2FontFindCode264", [](Gen& g) {
        uint16_t code = static_cast<uint16_t>(g.chance(50) ? at<uint16_t>(difftest::version::dataOrDie(0x00325e50) + 2 * g.below(264)) : g.below(0x10000));
        return Pair{[=] { return orig(0x001c60e0, {code}); }, [=] { return static_cast<uint64_t>(FindCode264(code)); }};
    });
    add("ps2FontRecordLastCode", [](Gen& g) {
        uint16_t code = static_cast<uint16_t>(g.chance(30) ? g.pick<uint32_t>({0x85ec, 0x2e, 0x2f, 0x39, 0x3a, 0x40, 0x41}) : g.below(0x10000));
        return Pair{[=] { return origVoid(0x001c6128, {code}); }, [=] { RecordLastCode(code); return uint64_t{0}; }};
    });
#endif

    // ---- layout ----
#if !NOCTURNE_JAPANESE
    add("frGetFontWidth", [](Gen& g) {
        uint8_t s = static_cast<uint8_t>(g.below(4));
        return Pair{[=] { return orig(0x001c83f0, {s}); }, [=] { return norm(frGetFontWidth(s)); }};
    });
    add("frGetFontHeight", [](Gen& g) {
        uint8_t s = static_cast<uint8_t>(g.below(4));
        return Pair{[=] { return orig(0x001c8458, {s}); }, [=] { return norm(frGetFontHeight(s)); }};
    });
#endif
    add("frGetDefaultFontWidth", [](Gen& g) {
        uint8_t s = static_cast<uint8_t>(g.below(4));
        return Pair{[=] { return orig(0x001c83b0, {s}); }, [=] { return norm(frGetDefaultFontWidth(s)); }};
    });
    add("frGetDefaultFontHeight", [](Gen& g) {
        uint8_t s = static_cast<uint8_t>(g.below(4));
        return Pair{[=] { return orig(0x001c8418, {s}); }, [=] { return norm(frGetDefaultFontHeight(s)); }};
    });
#if !NOCTURNE_JAPANESE
    add("ps2FontSetSize", [](Gen& g) {
        int32_t w = g.range(-2, 30);
        return Pair{[=] { return origVoid(0x001c6160, {I(w)}); }, [=] { frSetBaseWidth(w); return uint64_t{0}; }};
    });
#endif
    add("frGetXShiftLev", [=](Gen& g) {
        uint32_t text = textArg(g);
        if (!text)
            text = addr(frSetFont('W', 0, 0, 0, false));
        Text& t = at<Text>(text);
        t.style = static_cast<uint8_t>(g.below(4));
        if (g.chance(30))
            t.code = static_cast<uint16_t>(g.pick<uint32_t>({' ', '!', '1', 0x2c1 + 32}));
        t.mode = static_cast<uint8_t>(g.below(32));
        int32_t index = g.chance(10) ? 0x2c1 : glyphIndex(t.code);
        bool first = g.chance(50);
        return Pair{[=] { return origVoid(0x001c7088, {text, I(index), first}); },
                    [=] { frGetXShiftLev(at<Text>(text), index, first); return uint64_t{0}; }};
    });
    add("frGetStrWidth", [](Gen& g) {
        uint32_t r = addr(iface::chain(g, 0, 0));
        if (r)
            at<Request>(r).space = static_cast<int8_t>(g.range(-4, 6));
        return Pair{[=] { return orig(0x001c8230, {r}); }, [=] { return norm(frGetStrWidth(at<Request>(r))); }};
    });
    add("frGetChainWidth", [](Gen& g) {
        uint32_t r = addr(iface::chain(g, 0, 0));
        return Pair{[=] { return orig(0x001c8268, {r}); }, [=] { return norm(frGetChainWidth(at<Request>(r))); }};
    });
#if !NOCTURNE_JAPANESE   // (the JP builds have no RelayoutRequest)
    add("RelayoutRequest", [](Gen& g) {
        uint32_t r = addr(iface::chain(g, 0, 0));
        settings().mode = static_cast<uint8_t>(g.below(32));
        return Pair{[=] { return origVoid(0x001c6270, {r}); }, [=] { RelayoutRequest(at<Request>(r)); return uint64_t{0}; }};
    });
#endif

    // ---- building requests ----
    add("frSetFont", [](Gen& g) {
#if !NOCTURNE_JAPANESE
        uint16_t code = static_cast<uint16_t>(g.chance(70) ? 32 + g.below(95) : g.chance(50) ? 0x8080 + g.below(0x100) : g.below(32));
        uint8_t s = static_cast<uint8_t>(code >= 0x8080 ? g.below(2) : g.below(4));
#else   // (codes from 32: a lower one would decode a glyph before the font's)
        uint16_t code = static_cast<uint16_t>(g.chance(50) ? 32 + g.below(95) : 0x8080 + (g.below(0x14) << 8) + g.below(0x80));
        uint8_t s = static_cast<uint8_t>(g.below(4));
#endif
        uint8_t col = static_cast<uint8_t>(g.below(6)), tp = static_cast<uint8_t>(g.below(3));
        bool first = g.chance(50);
        return Pair{[=] { return orig(0x001c76e0, {code, s, col, tp, first}); }, [=] { return R(frSetFont(code, s, col, tp, first)); }};
    });
    add("frSetFontString", [=](Gen& g) {
        uint32_t str = g.chance(10) ? 0 : someString(g);
        int8_t s = someStyle(g);
        int8_t col = static_cast<int8_t>(g.range(0, 5)), tp = static_cast<int8_t>(g.range(0, 2));
        uint32_t font = g.chance(50) ? addr(iface::chain(g, 0, 0)) : 0;
        bool first = g.chance(50);
        return Pair{[=] { return orig(0x001c7890, {str, I(s), I(col), I(tp), font, first}); },
                    [=] { return R(frSetFontString(str ? bytes(str) : nullptr, s, col, tp, P<Request>(font), first)); }};
    });
    add("frLinkFontString", [=](Gen& g) {
        uint32_t str = someString(g);
        int8_t s = someStyle(g);
        int8_t col = static_cast<int8_t>(g.range(0, 5)), tp = static_cast<int8_t>(g.range(0, 2));
        uint32_t font = g.chance(70) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001c7828, {str, I(s), I(col), I(tp), font}); },
                    [=] { return R(frLinkFontString(bytes(str), s, col, tp, P<Request>(font))); }};
    });
    add("ps2FontCreateControlGlyph", [](Gen& g) {
        uint32_t data = 0x00456700 + g.below(0x100);
        uint32_t font = g.chance(60) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001c7288, {data, font}); }, [=] { return R(AppendControlText(data, P<Request>(font))); }};
    });
    add("LinkControlText", [](Gen& g) {
        uint32_t data = 0x00456700 + g.below(0x100);
        uint32_t font = g.chance(60) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001c73b8, {data, font}); }, [=] { return R(LinkControlText(data, P<Request>(font))); }};
    });
    add("frCombineFontRequest", [](Gen& g) {
        uint32_t a = g.chance(10) ? 0 : addr(iface::chain(g, g.range(0, 0x1000), g.range(0, 0x1000)));
        uint32_t b = g.chance(10) ? 0 : addr(iface::chain(g, 0, 0));
        return Pair{[=] { return orig(0x001c8108, {a, b}); }, [=] { return R(frCombineFontRequest(P<Request>(a), P<Request>(b))); }};
    });
    add("frCombineFontRequestEx", [](Gen& g) {
        uint32_t a = g.chance(10) ? 0 : addr(iface::chain(g, g.range(0, 0x1000), g.range(0, 0x1000)));
        uint32_t b = g.chance(10) ? 0 : addr(iface::chain(g, 0, 0));
        if (b && g.chance(30))   // starts with a line feed
            at<Request>(b).head->str->code = 13;
        uint64_t mode = g.pick<uint64_t>({0, 1, 2, 0x100000001ull});
        return Pair{[=] { return orig(0x001c8120, {a, b, mode}); }, [=] { return R(frCombineFontRequestEx(P<Request>(a), P<Request>(b), mode)); }};
    });
    add("frDestroyFontRequestNow", [](Gen& g) {
        uint32_t r = g.chance(10) ? 0 : addr(iface::chain(g, 0, 0));
        if (r && g.chance(30)) {   // a control text (an entered name's letter: its data starts with the bank)
            at<uint8_t>(kBuffer) = static_cast<uint8_t>(g.below(4));
            r = addr(LinkControlText(kBuffer, &at<Request>(r)));
        }
        return Pair{[=] { return origVoid(0x001c6f08, {r}); }, [=] { frDestroyFontRequestNow(P<Request>(r)); return uint64_t{0}; }};
    });
    add("frDestroyFontRequestAfter", [](Gen& g) {
        uint32_t r = g.chance(10) ? 0 : addr(iface::chain(g, 0, 0));
        if (g.chance(50))
            at<uint32_t>(difftest::version::dataOrDie(0x0056bbc4) + 4 * at<uint32_t>(difftest::version::dataOrDie(0x00551b80))) = addr(iface::chain(g, 0, 0));
        return Pair{[=] { return origVoid(0x001c6ff8, {r}); }, [=] { frDestroyFontRequestAfter(P<Request>(r)); return uint64_t{0}; }};
    });
    add("frFadeOutText", [](Gen& g) {
        Request* r = iface::chain(g, 0, 0);
        for (Request* q = r; q; q = q->prev.get())
            for (Text* t = q->str.get(); t; t = t->next.get()) {
                t->tp = static_cast<uint8_t>(g.below(3));
                t->color = (t->color & 0xffffff00) | (g.chance(30) ? g.below(9) : g.below(256));
            }
        uint32_t a = addr(r);
        return Pair{[=] { return orig(0x001c7c30, {a}); }, [=] { return norm(frFadeOutText(P<Request>(a))); }};
    });
    add("frDestroyFontRequestFade", [](Gen& g) {
        Request* r = iface::chain(g, 0, 0);
        for (Request* q = r; q; q = q->prev.get())
            for (Text* t = q->str.get(); t; t = t->next.get())
                t->tp = static_cast<uint8_t>(g.chance(70) ? 0 : 2);
        uint32_t a = addr(r);
        return Pair{[=] { return orig(0x001c6ec8, {a}); }, [=] { return R(frDestroyFontRequestFade(P<Request>(a))); }};
    });

    // ---- settings of a request ----
    auto requestTest = [&](const char* name, uint32_t entry, std::function<std::vector<uint64_t>(Gen&)> args,
                           std::function<void(Request&, const std::vector<uint64_t>&)> rewrite) {
        add(name, [=](Gen& g) {
            uint32_t r = addr(iface::chain(g, g.range(0, 0x1000), 0));
            std::vector<uint64_t> a = args(g);
            return Pair{[=] {
                            std::vector<uint64_t> all{r};
                            all.insert(all.end(), a.begin(), a.end());
                            switch (all.size()) {
                            case 2: return origVoid(entry, {all[0], all[1]});
                            default: return origVoid(entry, {all[0], all[1], all[2]});
                            }
                        },
                        [=] { rewrite(at<Request>(r), a); return uint64_t{0}; }};
        });
    };
    requestTest("frSetDrawSpeed", 0x001c7a60, [](Gen& g) { return std::vector<uint64_t>{g.below(256)}; },
                [](Request& r, const std::vector<uint64_t>& a) { frSetDrawSpeed(r, static_cast<uint8_t>(a[0])); });
    requestTest("frSetFontSpace", 0x001c7a88, [](Gen& g) { return std::vector<uint64_t>{I(g.range(-5, 8))}; },
                [](Request& r, const std::vector<uint64_t>& a) { frSetFontSpace(r, static_cast<int32_t>(a[0])); });
    requestTest("frSetDrawPosition", 0x001c7b30, [](Gen& g) { return std::vector<uint64_t>{I(g.range(-100, 0x2000)), I(g.range(-100, 0x1000))}; },
                [](Request& r, const std::vector<uint64_t>& a) { frSetDrawPosition(r, static_cast<int32_t>(a[0]), static_cast<int32_t>(a[1])); });
    requestTest("frSetPriority", 0x001c7b40, [](Gen& g) { return std::vector<uint64_t>{static_cast<uint32_t>(g.rng())}; },
                [](Request& r, const std::vector<uint64_t>& a) { frSetPriority(r, static_cast<uint32_t>(a[0])); });
    requestTest("frSetFontSize", 0x001c7ab8, [](Gen& g) { return std::vector<uint64_t>{I(g.range(8, 32)), I(g.range(8, 32))}; },
                [](Request& r, const std::vector<uint64_t>& a) { frSetFontSize(r, static_cast<int32_t>(a[0]), static_cast<int32_t>(a[1])); });
    requestTest("frSetFontColNo", 0x001c7b50, [](Gen& g) { return std::vector<uint64_t>{g.below(8)}; },
                [](Request& r, const std::vector<uint64_t>& a) { frSetFontColNo(&r, static_cast<uint8_t>(a[0])); });
    requestTest("frSetFontColor", 0x001c7ba8, [](Gen& g) { return std::vector<uint64_t>{static_cast<uint32_t>(g.rng())}; },
                [](Request& r, const std::vector<uint64_t>& a) { frSetFontColor(&r, static_cast<uint32_t>(a[0])); });
    add("frEnableMode", [](Gen& g) {
        uint8_t f = static_cast<uint8_t>(g.below(256));
        return Pair{[=] { return orig(0x001c7c00, {f}); }, [=] { return uint64_t{frEnableMode(f)}; }};
    });
    add("frDisableMode", [](Gen& g) {
        uint8_t f = static_cast<uint8_t>(g.below(256));
        return Pair{[=] { return orig(0x001c7c10, {f}); }, [=] { return uint64_t{frDisableMode(f)}; }};
    });
    add("frSetFontDrawOT", [](Gen& g) {
        uint32_t ot = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVoid(0x001c7c28, {ot}); }, [=] { frSetFontDrawOT(ot); return uint64_t{0}; }};
    });
    add("frSetStepY", [](Gen& g) {
        int32_t s = g.range(0, 40);
        return Pair{[=] { return origVoid(0x001c8490, {I(s)}); }, [=] { frSetStepY(s); return uint64_t{0}; }};
    });
    add("frResetStepY", [](Gen&) { return Pair{[] { return origVoid(0x001c8480, {}); }, [] { frResetStepY(); return uint64_t{0}; }}; });

    // ---- entered names ----
    add("ps2FontLoadNameBitmapBank", [](Gen& g) {
        int8_t bank = static_cast<int8_t>(g.below(4));
        bool given = g.chance(50);
        int8_t count = static_cast<int8_t>(g.range(0, 6));
        uint32_t pixels = FW_GLOBAL + 0x1d7c + 0x1200u * static_cast<uint32_t>(bank);
        return Pair{[=] { return origVoid(0x001c96d8, {I(bank), given, I(count), pixels}); },
                    [=] { LoadNameBank(bank, given, count, pixels); return uint64_t{0}; }};
    });
    add("ps2FontReferenceNameBitmapBank", [](Gen& g) {
        int8_t bank = static_cast<int8_t>(g.below(4));
        bool given = g.chance(50);
        if (g.chance(30))
            ReferenceNameBank(bank, !given);
        return Pair{[=] { return origVoid(0x001c98c0, {I(bank), given}); }, [=] { ReferenceNameBank(bank, given); return uint64_t{0}; }};
    });
    add("ps2FontReleaseNameBank", [](Gen& g) {
        int8_t bank = static_cast<int8_t>(g.below(4));
        if (g.chance(70))
            ReferenceNameBank(bank, g.chance(50));
        if (g.chance(30))
            at<int32_t>(difftest::version::dataOrDie(0x0056bd50) + 4 * static_cast<uint32_t>(bank)) = 1;
        return Pair{[=] { return origVoid(0x001c99c0, {I(bank)}); }, [=] { ReleaseNameBank(bank); return uint64_t{0}; }};
    });
    auto nameTest = [&](const char* name, uint32_t entry, std::function<Request*(int8_t, Request*, int8_t)> rewrite) {
        add(name, [=](Gen& g) {
            int8_t bank = static_cast<int8_t>(g.below(4)), col = static_cast<int8_t>(g.range(0, 5));
            uint32_t font = g.chance(50) ? addr(iface::chain(g, 0, 0)) : 0;
            return Pair{[=] { return orig(entry, {I(bank), font, I(col)}); }, [=] { return R(rewrite(bank, P<Request>(font), col)); }};
        });
    };
    nameTest("ps2FontAppendNameFirst", 0x001c9b58, AppendFamilyName);
    nameTest("ps2FontAppendNameSecond", 0x001c9c28, AppendGivenName);
    nameTest("ps2FontAppendNameBoth", 0x001c9d00, AppendFullName);
    add("ps2FontAppendNameBitmapGlyph", [](Gen& g) {
        int8_t bank = static_cast<int8_t>(g.below(4)), index = static_cast<int8_t>(g.below(12));
        ReferenceNameBank(bank, false);
        uint32_t font = g.chance(50) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001c9a98, {I(bank), I(index), font}); }, [=] { return R(AppendNameLetter(bank, index, P<Request>(font))); }};
    });
    add("ps2FontAppendResourceName", [](Gen& g) {
        int8_t bank = static_cast<int8_t>(g.below(4)), s = static_cast<int8_t>(g.range(0, 3)), col = static_cast<int8_t>(g.range(0, 5));
        uint32_t font = g.chance(50) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001c9d60, {I(bank), I(s), font, I(col)}); },
                    [=] { return R(AppendNameText(bank, s, P<Request>(font), col)); }};
    });
    // Strings with 1- and 2-byte characters the fonts have.
    static const char* const letters[] = {"Pixie", "Lv 12", "\x80\xe1\x80\xe3!", "R", "A\x80\xe5" "b"};
    add("ps2FontLinkLetters", [](Gen& g) {
        const int32_t x = g.range(-0x100, 0x2000), y = g.range(-0x100, 0x1000);
        const uint32_t z = g.chance(50) ? 0xff0051 : static_cast<uint32_t>(g.rng()), col = static_cast<uint32_t>(g.rng());
        const uint32_t s = iface::guestString(letters[g.below(5)]);
        const int8_t style = static_cast<int8_t>(g.range(0, 3)), keep = static_cast<int8_t>(g.chance(50) ? 0 : g.range(-1, 2));
        const uint32_t font = g.chance(50) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001ca0d0, {I(x), I(y), I(static_cast<int32_t>(z)), I(static_cast<int32_t>(col)), s, I(style), I(keep), font}); },
                    [=] { return R(LinkLetters(x, y, z, col, P<uint8_t>(s), style, keep, P<Request>(font))); }};
    });
    add("ps2FontLinkSpacedLetters", [](Gen& g) {
        const int32_t x = g.range(-0x100, 0x2000), y = g.range(-0x100, 0x1000);
        const uint32_t z = g.chance(50) ? 0xff0051 : static_cast<uint32_t>(g.rng()), col = static_cast<uint32_t>(g.rng());
        const uint32_t s = iface::guestString(letters[g.below(5)]);
        const uint32_t font = g.chance(50) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001ca258, {I(x), I(y), I(static_cast<int32_t>(z)), I(static_cast<int32_t>(col)), s, font}); },
                    [=] { return R(LinkSpacedLetters(x, y, z, col, P<uint8_t>(s), P<Request>(font))); }};
    });

    // ---- laying out a page ----
    add("frCreateNewHandle", [](Gen& g) {
        info(g, iface::someText(g), true);
        return Pair{[] { return origVoid(0x001c86a0, {kInfo}); }, [] { frCreateNewHandle(at<MessageInfo>(kInfo)); return uint64_t{0}; }};
    });
    add("ps2FontAdvanceMessageLine", [](Gen& g) {
        info(g, iface::someText(g), true);
        return Pair{[] { return origVoid(0x001c8730, {kInfo}); }, [] { AdvanceMessageLine(at<MessageInfo>(kInfo)); return uint64_t{0}; }};
    });
#if !NOCTURNE_JAPANESE
    add("ps2FontAppendSpecialCode", [](Gen& g) {
        info(g, iface::someText(g), true);
        uint16_t code = static_cast<uint16_t>(0x80e0 + g.below(10));
        return Pair{[=] { return origVoid(0x001c8758, {kInfo, code}); }, [=] { AppendSpecialCode(at<MessageInfo>(kInfo), code); return uint64_t{0}; }};
    });
#endif
    add("ps2FontAppendVariable", [](Gen& g) {
        info(g, iface::someText(g), true);
        uint8_t index = static_cast<uint8_t>(g.chance(5) ? 255 : g.below(32));
        return Pair{[=] { return origVoid(0x001c8508, {index, kInfo}); }, [=] { AppendVariable(index, at<MessageInfo>(kInfo)); return uint64_t{0}; }};
    });
    add("frAnalyzeTag", [](Gen& g) {
        static const char* const tags[] = {
            "\xF1\x04", "\xF1\x10", "\xF1\x11", "\xF1\x12", "\xF1\x0F", "\xF1\x13", "\xF1\x14", "\xF1\x15", "\xF1\x16",
            "\xF1\x17", "\xF1\x18", "\xF1\x0B", "\xF2\x02\x03\xFF", "\xF2\x06\x02\xFF", "\xF2\x07\x05\xFF", "\xF2\x09\x02\xFF",
            "\xF2\x03\x02\xFF", "\xF2\x03\x01\xFF", "\xF2\x0A\x02\xFF", "\xF2\x0B\x01\xFF", "\xF2\x0C\x03\xFF", "\xF2\x0D\x01\xFF",
            "\xF2\x0E\x01\xFF", "\xF2\x08\xFF\xFF", "\xF3\x05\x01\x02\x03\x04"};
        info(g, guestString(tags[g.below(25)]), true);
        MessageInfo& m = at<MessageInfo>(kInfo);
        m.pos = 1;
        uint8_t prefix = at<uint8_t>(m.text);
        settings().mode = static_cast<uint8_t>(g.below(32));
        return Pair{[=] { return orig(0x001c87c8, {prefix, kInfo}); }, [=] { return norm(frAnalyzeTag(prefix, at<MessageInfo>(kInfo))); }};
    });
    add("frAnalyzeMessage", [](Gen& g) {
        info(g, g.chance(10) ? guestString("Q\x08...skipped") : iface::someText(g), true);
        return Pair{[] { return orig(0x001c8f08, {kInfo}); }, [] { return R(frAnalyzeMessage(at<MessageInfo>(kInfo))); }};
    });
    add("MessageRequestEx", [](Gen& g) {
        int32_t x = g.range(0, 0x2000), y = g.range(0, 0x1000);
        uint32_t z = g.below(0x10000), text = iface::someText(g);
        uint8_t s = static_cast<uint8_t>(g.below(4)), col = static_cast<uint8_t>(g.below(6)), tp = static_cast<uint8_t>(g.below(3)),
                spd = static_cast<uint8_t>(g.below(140));
        uint32_t font = g.chance(40) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001c9188, {I(x), I(y), z, s, col, tp, spd, text, font}); },
                    [=] { return R(MessageRequestEx(x, y, z, s, col, tp, spd, text, P<Request>(font))); }};
    });
    add("ps2FontMessageRequest", [](Gen& g) {
        int32_t x = g.range(0, 0x2000), y = g.range(0, 0x1000);
        uint32_t text = iface::someText(g);
        uint8_t s = static_cast<uint8_t>(g.below(4)), col = static_cast<uint8_t>(g.below(6)), tp = static_cast<uint8_t>(g.below(3)),
                spd = static_cast<uint8_t>(g.below(140));
        uint32_t font = g.chance(40) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001c9140, {I(x), I(y), s, col, tp, spd, text, font}); },
                    [=] { return R(MessageRequest(x, y, s, col, tp, spd, text, P<Request>(font))); }};
    });
    add("MessageRequestPlain", [](Gen& g) {
        int32_t x = g.range(0, 0x2000), y = g.range(0, 0x1000);
        uint32_t text = iface::someText(g);
        uint32_t font = g.chance(40) ? addr(iface::chain(g, 0, 0)) : 0;
        return Pair{[=] { return orig(0x001c9108, {I(x), I(y), text, font}); }, [=] { return R(MessageRequestPlain(x, y, text, P<Request>(font))); }};
    });
    add("MessageRequestKeepSpace", [](Gen& g) {
        int32_t x = g.range(0, 0x2000), y = g.range(0, 0x1000);
        uint32_t z = g.below(0x10000), text = iface::someText(g);
        uint8_t s = static_cast<uint8_t>(g.below(4)), col = static_cast<uint8_t>(g.below(6)), tp = static_cast<uint8_t>(g.below(3)),
                spd = static_cast<uint8_t>(g.below(140));
        return Pair{[=] { return orig(0x001c91e0, {I(x), I(y), z, s, col, tp, spd, text}); },
                    [=] { return R(MessageRequestKeepSpace(x, y, z, s, col, tp, spd, text)); }};
    });
    add("frGetMessageResult", [](Gen& g) {
        uint64_t mask = g.chance(50) ? g.below(8) : g.rng();
        return Pair{[=] { return orig(0x001c9220, {mask}); }, [=] { return norm(static_cast<int32_t>(frGetMessageResult(static_cast<int64_t>(mask)))); }};
    });
    add("frSetVariableRequest", [](Gen& g) {
        int32_t i = g.range(0, 31);
        uint32_t s = static_cast<uint32_t>(g.rng());
        return Pair{[=] { return origVoid(0x001c9230, {I(i), s}); }, [=] { frSetVariableRequest(i, s); return uint64_t{0}; }};
    });
#if !NOCTURNE_JAPANESE
    add("ControlCodeLength", [](Gen& g) {
        uint16_t code = static_cast<uint16_t>(g.chance(70) ? 0xf200 + g.below(0x14) : g.below(0x10000));
        return Pair{[=] { return orig(0x001c8ce0, {code}); }, [=] { return norm(ControlCodeLength(code)); }};
    });
    add("CountMessageLines", [](Gen& g) {
        uint32_t text = iface::someText(g);
        return Pair{[=] { return orig(0x001c8e48, {text}); }, [=] { return norm(CountMessageLines(bytes(text))); }};
    });
    add("CopyMessageLine", [](Gen& g) {
        uint32_t text = iface::someText(g);
        int32_t line = g.range(0, 4);
        return Pair{[=] { return origVoid(0x001c8d28, {text, kBuffer, I(line)}); },
                    [=] { CopyMessageLine(bytes(text), &at<uint8_t>(kBuffer), line); return uint64_t{0}; }};
    });
#endif
}

} // namespace difftest


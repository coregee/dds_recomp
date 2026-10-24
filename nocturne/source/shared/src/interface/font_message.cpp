// The font engine (frFont), part two: laying out message pages.
//
// frAnalyzeMessage reads a page of a message table (docs/messages.md): ASCII
// and 2-byte characters become texts, a new line or a control code starts a
// new request, and the control codes set colors, speed, the end of the
// page, or insert variables and the names the player entered. Those names
// are drawn from 24x24 bitmaps kept in the save data, two banks of glyphs
// per name (family and given name).
#include <cstring>

#include "nocturne/external.hpp"
#include "nocturne/interface/font.hpp"

namespace nocturne::fr {

namespace {

constexpr uint32_t kEmptyString = 0x0054f430;
constexpr uint32_t kEmptyString2 = 0x0054f448;   // (another "")
constexpr uint32_t kVariables = 0x0056bbd0;      // uint32[32]: the {var n} strings
constexpr uint32_t kNameGlyphs = 0x0056bc50;     // Glyph*[4][16]
constexpr uint32_t kNameRefs = 0x0056bd50;       // int32[4]
constexpr uint32_t kSaveData = 0x0054ea20;       // pointer to the data holding the entered names
constexpr uint32_t kLastCode = 0x0054ea00;

uint32_t addressOf(const void* p) { return guest::addressOf(p); }
template <class T> T* at(uint32_t address) { return address ? guest::table<T>(address) : nullptr; }
const uint8_t* empty() { return guest::table<uint8_t>(kEmptyString); }
uint32_t& variable(uint32_t index) { return guest::table<uint32_t>(kVariables)[index]; }
uint32_t& nameGlyphAddress(int32_t slot) { return guest::table<uint32_t>(kNameGlyphs)[slot]; }
int32_t& nameRefs(int32_t bank) { return guest::table<int32_t>(kNameRefs)[bank]; }
uint16_t lastCode() { return *guest::table<uint16_t>(kLastCode); }

// The entered names in the save data: for each of 4 names, the 2-byte codes
// of its letters (16 per name, family name first), the letters' bitmaps
// (24x24, 4 bits per pixel), and how many letters each part has.
struct EnteredNames {
    uint8_t* base;
    explicit EnteredNames() : base(guest::table<uint8_t>(*guest::table<uint32_t>(kSaveData))) {}
    uint32_t address() const { return addressOf(base); }
    uint8_t familyLength(int32_t bank) const { return base[0x657c + 2 * bank]; }
    uint8_t givenLength(int32_t bank) const { return base[0x657d + 2 * bank]; }
    uint8_t length(int32_t bank, bool given) const { return given ? givenLength(bank) : familyLength(bank); }
    const uint8_t* code(int32_t slot) const { return base + 0x6584 + 2 * slot; }
    uint32_t bitmaps(int32_t bank) const { return address() + static_cast<uint32_t>(bank) * 0x1200 + 0x1d7c; }
};

} // namespace

// ---- entered names ----------------------------------------------------------------------------

// ps2FontLoadNameBitmapBank @ 0x001C96D8 (no original name)
// Puts one part of an entered name into the texture: `count` 24x24 bitmaps
// from `pixels`, as name glyphs `start`.. (the given name follows the family
// name's letters).
void LoadNameBank(int8_t bank, bool given, int8_t count, uint32_t pixels)
{
    const EnteredNames names;
    const int32_t start = given ? static_cast<int8_t>(names.familyLength(bank)) : 0;
    const int32_t clear = static_cast<int8_t>(names.length(bank, given));
    for (int32_t i = start; i < start + clear; ++i)
        nameGlyphAddress(bank * 16 + i) = 0;
    for (int32_t i = 0; i < count; ++i) {
        uint32_t copy = mem::PoolAllocate(0x120);
        std::memcpy(guest::table<uint8_t>(copy), guest::table<uint8_t>(pixels), 0x120);
        Glyph* glyph = CreateTextureGlyph(24, 24, copy, true);
        pixels += 0x120;
        nameGlyphAddress(bank * 16 + start + i) = addressOf(glyph);
        glyph->index = static_cast<uint16_t>(bank);
    }
    diag::print(diag::Message::NameTranslate, bank);
}

// ps2FontReferenceNameBitmapBank @ 0x001C98C0 (no original name)
// Loads both parts of a name on first use and counts the letters in use.
void ReferenceNameBank(int8_t bank, bool given)
{
    int32_t refs = nameRefs(bank);
    if (!refs) {
        const int8_t family = static_cast<int8_t>(EnteredNames().familyLength(bank));
        LoadNameBank(bank, false, family, EnteredNames().bitmaps(bank));
        const uint32_t pixels = EnteredNames().bitmaps(bank) + static_cast<uint32_t>(family) * 0x120;
        LoadNameBank(bank, true, static_cast<int8_t>(EnteredNames().givenLength(bank)), pixels);
        refs = nameRefs(bank);
    }
    nameRefs(bank) = refs + EnteredNames().length(bank, given);
}

// ps2FontReleaseNameBank @ 0x001C99C0 (no original name)
// One letter fewer in use; the last one frees the name's glyphs.
void ReleaseNameBank(int8_t bank)
{
    const EnteredNames names;
    const int32_t total = names.familyLength(bank) + names.givenLength(bank);
    int32_t& refs = nameRefs(bank);
    if (!refs || --refs != 0)
        return;
    for (int32_t i = 0; i < total; ++i)
        if (Glyph* glyph = at<Glyph>(nameGlyphAddress(bank * 16 + i)))
            GiveTextureCell(*glyph->cell);
    diag::print(diag::Message::NameRestore, bank);
}

// ps2FontAppendNameBitmapGlyph @ 0x001C9A98 (no original name)
// Appends letter `index` of an entered name as a control text.
Request* AppendNameLetter(int8_t bank, int8_t index, Request* pFRQ)
{
    const int32_t slot = bank * 16 + index;
    const uint8_t* p = EnteredNames().code(slot);
    const uint16_t code = static_cast<uint16_t>(p[0] << 8 | p[1]);
    RecordLastCode(code);
    Request* result = AppendControlText(nameGlyphAddress(slot), pFRQ);
    Text& text = *result->str_end;
    text.code = code;
    frGetXShiftLev(text, code - 32, false);
    result->str_end->ly = 24;
    return result;
}

namespace {

Request* appendNamePart(int8_t bank, Request* pFRQ, int8_t colno, bool given)
{
    int8_t index = given ? static_cast<int8_t>(EnteredNames().familyLength(bank)) : 0;
    ReferenceNameBank(bank, given);
    for (uint32_t k = 0; k < EnteredNames().length(bank, given); ++k) {
        pFRQ = AppendNameLetter(bank, index, pFRQ);
        index = static_cast<int8_t>(index + 1);
        pFRQ->str_end->col_no = static_cast<uint8_t>(colno);
    }
    return pFRQ;
}

} // namespace

// ps2FontAppendNameFirst @ 0x001C9B58 (no original name): {lastname n}.
Request* AppendFamilyName(int8_t bank, Request* pFRQ, int8_t colno) { return appendNamePart(bank, pFRQ, colno, false); }

// ps2FontAppendNameSecond @ 0x001C9C28 (no original name): {firstname n}.
Request* AppendGivenName(int8_t bank, Request* pFRQ, int8_t colno) { return appendNamePart(bank, pFRQ, colno, true); }

// ps2FontAppendNameBoth @ 0x001C9D00 (no original name)
// {fullname n}: the given name, half a letter of space, the family name.
Request* AppendFullName(int8_t bank, Request* pFRQ, int8_t colno)
{
    Request* given = AppendGivenName(bank, pFRQ, colno);
    given->w_pxls += 8;
    given->str_end->lw += 8;
    return AppendFamilyName(bank, given, colno);
}

// ps2FontAppendResourceName @ 0x001C9D60 (no original name)
// {name n}: an entered name as ordinary text (letters as their codes).
Request* AppendNameText(int8_t bank, int8_t styleIndex, Request* pFRQ, int8_t colno)
{
    uint8_t text[528] = {};
    const EnteredNames names;
    const uint8_t* name = names.base + 0x6604 + 20 * bank;
    uint32_t position = 0;
    for (uint32_t k = 0; k < names.base[0x6654 + bank]; ++k) {
        if (name[2 * k])
            text[position++] = name[2 * k];
        text[position++] = name[2 * k + 1];
    }
    text[position] = 0;
    frEnableMode(kModeMetrics);
    Request* result = frLinkFontString(text, styleIndex, colno, 0, pFRQ);
    frDisableMode(kModeMetrics);
    frSetFontSpace(*result, 4);
    return result;
}

// 0x001CA0D0 (no original name)
// A string as one request per character (1 or 2 bytes), each at depth z
// in `color` with 3 units of spacing, chained after `chain`; the first
// starts at x and all sit at y. Laid out with the font's own advances
// unless `keepMode` (the mode is then left as the caller set it).
Request* LinkLetters(int32_t x, int32_t y, uint32_t z, uint32_t color, const uint8_t* pStr, int8_t styleIndex,
                     int8_t keepMode, Request* chain)
{
    const int32_t length = static_cast<int32_t>(std::strlen(reinterpret_cast<const char*>(pStr)));
    if (keepMode == 0)
        frEnableMode(kModeMetrics);
    frDisableMode(kModeParsing);
    for (int32_t i = 0; i < length;) {
        uint8_t letter[3] = {pStr[i], 0, 0};
        const int32_t size = static_cast<int8_t>(pStr[i]) < 0 ? 2 : 1;
        if (size == 2)
            letter[1] = pStr[i + 1];
        Request* font = frLinkFontString(letter, styleIndex, 0, 0, nullptr);
        frSetPriority(*font, z << 4);
        frSetFontColor(font, color);
        frSetFontSpace(*font, 3);
        chain = frCombineFontRequest(chain, font);
        if (i == 0)
            font->x = x;
        i += size;
        font->y = y;
    }
    frEnableMode(kModeParsing);
    if (keepMode == 0)
        frDisableMode(kModeMetrics);
    return chain;
}

// 0x001CA258 (no original name): LinkLetters in style 1, spaced 3 apart.
Request* LinkSpacedLetters(int32_t x, int32_t y, uint32_t z, uint32_t color, const uint8_t* pStr, Request* chain)
{
    Request* font = LinkLetters(x, y, z, color, pStr, 1, 0, chain);
    frSetFontSpace(*font, 3);
    return font;
}

// ---- laying out a page -----------------------------------------------------------------------

// frCreateNewHandle @ 0x001C86A0
// Starts the request for what follows, if one is due, and places it.
void frCreateNewHandle(MessageInfo& m)
{
    Request* f = m.font.get();
    if (f && !f->str)
        m.newline = 0;
    if (m.newline) {
        Request* created = frLinkFontString(empty(), 0, m.colno, m.tp, f);
        m.font.address = addressOf(created);
        frSetDrawSpeed(*created, m.speed);
        m.newline = 0;
    }
    if (m.position) {
        frSetDrawPosition(*m.font, m.x, m.y);
        m.position = 0;
    }
}

// ps2FontAdvanceMessageLine @ 0x001C8730 (no original name): the next line.
void AdvanceMessageLine(MessageInfo& m)
{
    m.position = 1;
    m.newline = 1;
    m.y += settings().step << 3;
}

// ps2FontAppendSpecialCode @ 0x001C8758 (no original name)
// Appends one 2-byte character (a particle, docs/messages.md).
void AppendSpecialCode(MessageInfo& m, uint16_t code)
{
    const uint8_t text[3] = {static_cast<uint8_t>(code >> 8), static_cast<uint8_t>(code), 0};
    frCreateNewHandle(m);
    Request* font = frSetFontString(text, m.style, m.colno, m.tp, m.font.get(), false);
    m.font.address = addressOf(font);
    frSetFontSpace(*font, settings().space);
    frSetPriority(*m.font, m.z);
}

// ps2FontAppendVariable @ 0x001C8508 (no original name): {var index}.
void AppendVariable(uint8_t index, MessageInfo& m)
{
    const uint32_t string = variable(index);
    uint8_t text[3] = {};
    if (!string)
        return;
    const uint8_t* s = guest::table<uint8_t>(string);
    const int32_t length = static_cast<int32_t>(std::strlen(reinterpret_cast<const char*>(s)));
    int8_t previous = m.style;
    for (int32_t position = 0; position < length;) {
        const uint8_t first = s[position];
        uint16_t code = first;
        text[0] = first;
        if (first & 0x80) {
            text[1] = s[++position];
            code = static_cast<uint16_t>(first << 8 | text[1]);
        } else {
            text[1] = 0;
        }
        const int8_t styleIndex = m.style;
        if (styleIndex != previous) {   // (the style can't change here)
            Request* font = m.font.get();
            if (!font || font->str) {
                font = frLinkFontString(empty(), 0, m.colno, m.tp, font);
                m.font.address = addressOf(font);
            }
            frSetDrawSpeed(*font, m.speed);
            previous = styleIndex;
        }
        Request* font = frSetFontString(text, styleIndex, m.colno, m.tp, m.font.get(), position < 1);
        ++position;
        m.font.address = addressOf(font);
        frSetFontSpace(*font, settings().space);
        RecordLastCode(code);
    }
}

// frAnalyzeTag @ 0x001C87C8
// A control code (docs/messages.md); true when it ends the page.
bool frAnalyzeTag(uint8_t prefix, MessageInfo& m)
{
    const uint8_t* text = guest::table<uint8_t>(m.text);
    const int8_t colno = m.colno;
    const uint16_t code = static_cast<uint16_t>(prefix << 8 | text[m.pos]);
    const int32_t next = m.pos + 1;
    m.pos = next;
    Settings& set = settings();
    switch (code) {
    case 0xf104:   // {wait}
        set.result |= 1;
        return true;
    case 0xf110:   // {wait_nospeaker}
        set.result |= 2;
        return true;
    case 0xf111:   // {wait_mode8}
        if (set.mode & 8) {
            set.result |= 1;
            return true;
        }
        break;
    case 0xf112:   // {lipsync}
        set.result |= 4;
        break;
    case 0xf10f:   // {br}
        if (!(set.mode & kModeCompact))
            AdvanceMessageLine(m);
        break;
    case 0xf113:   // {particle1}..{particle3}: glyph base or base + 1 after a listed letter
    case 0xf114:
    case 0xf115: {
        const uint16_t base = code == 0xf113 ? 0x80e2 : code == 0xf114 ? 0x80e4 : 0x80e0;
        AppendSpecialCode(m, static_cast<uint16_t>(base + (FindCode416(lastCode()) < 0 ? 0 : 1)));
        break;
    }
    case 0xf116:   // {particle4}
        if (FindCode416(lastCode()) < 0)
            AppendSpecialCode(m, 0x80e2);
        break;
    case 0xf117:   // {particle5}
        AppendSpecialCode(m, FindCode416(lastCode()) < 0 ? 0x80e7 : 0x80e6);
        break;
    case 0xf118:   // {particle6}
        if (FindCode416(lastCode()) < 0 && FindCode264(lastCode()) < 0)
            AppendSpecialCode(m, 0x80e9);
        AppendSpecialCode(m, 0x80e8);
        break;
    case 0xf202:   // {color n}, {style n}, {speed n}, {tp n}: the value is stored + 1
        m.colno = static_cast<int8_t>(text[next] - 1);
        m.pos = next + 2;
        break;
    case 0xf206:
        m.style = static_cast<int8_t>(text[next] - 1);
        m.pos = next + 2;
        break;
    case 0xf207:
        m.speed = static_cast<uint8_t>(text[next] - 1);
        m.pos = next + 2;
        break;
    case 0xf209:
        m.tp = static_cast<int8_t>(text[next] - 1);
        m.pos = next + 2;
        break;
    case 0xf203:   // {var n} (the check reads below the table for n = -1)
        if (*guest::table<uint32_t>(kVariables - 4 + 4u * text[next])) {
            frCreateNewHandle(m);
            AppendVariable(static_cast<uint8_t>(text[m.pos] - 1), m);
        }
        m.pos += 2;
        break;
    case 0xf20a:   // {fullname n}, {lastname n}, {firstname n}, {name n}
    case 0xf20b:
    case 0xf20c:
    case 0xf20d: {
        const int8_t bank = static_cast<int8_t>(text[next] - 1);
        m.pos = next + 2;
        frCreateNewHandle(m);
        Request* font = m.font.get();
        if (code == 0xf20a)
            font = AppendFullName(bank, font, colno);
        else if (code == 0xf20b)
            font = AppendFamilyName(bank, font, colno);
        else if (code == 0xf20c)
            font = AppendGivenName(bank, font, colno);
        else
            font = AppendNameText(bank, m.style, font, colno);
        m.font.address = addressOf(font);
        if (code == 0xf20d)
            frEnableMode(kModeMetrics);
        frSetFontSpace(*font, set.space);
        if (code == 0xf20d)
            frSetDrawSpeed(*m.font, m.speed);
        break;
    }
    case 0xf20e:
        m.pos = next + 1;
        break;
    default:       // other codes are skipped (F2 08 starts every page)
        m.pos += ((prefix & 15) - 1) * 2;
        break;
    }
    if (!m.newline)
        m.newline = 1;
    return false;
}

// frAnalyzeMessage @ 0x001C8F08
// Lays out a page; returns its chain (by its last request). How it ended is
// in frGetMessageResult.
Request* frAnalyzeMessage(MessageInfo& m)
{
    const uint8_t* text = guest::table<uint8_t>(m.text);
    bool first = true;
    // Meant to skip a leading F2 08, but the test is inverted: it skips four
    // bytes when the page starts with a character followed by 8.
    if ((text[0] & 0xf0) != 0xf0 && text[1] == 8)
        m.pos += 4;
    settings().result &= ~7u;
    frEnableMode(kModeMetrics);
    for (;;) {
        uint16_t code = text[m.pos++];
        if (!code)
            break;
        if ((code & 0xf0) == 0xf0) {
            if (frAnalyzeTag(static_cast<uint8_t>(code), m))
                break;
            continue;
        }
        if (code == '\n') {
            if (settings().mode & kModeCompact)
                AdvanceMessageLine(m);
            first = true;
            continue;
        }
        frCreateNewHandle(m);
        int8_t styleIndex = m.style;
        uint8_t character[3] = {};
        if (code < 128) {
            character[0] = static_cast<uint8_t>(code);
            m.font.address = addressOf(frSetFontString(character, styleIndex, m.colno, m.tp, m.font.get(), first));
        } else {
            code = static_cast<uint16_t>(code << 8 | text[m.pos++]);
            if (code > 0xc07f) {   // codes from 0xC080 are style 8's (the message table's own font)
                code = static_cast<uint16_t>(code - 0x4000);
                styleIndex = 8;
            }
            character[0] = static_cast<uint8_t>(code >> 8);
            character[1] = static_cast<uint8_t>(code);
            m.font.address = addressOf(frSetFontString(character, styleIndex, m.colno, m.tp, m.font.get(), first));
            RecordLastCode(code);
        }
        first = false;
        frSetFontSpace(*m.font, settings().space);
        frSetPriority(*m.font, m.z);
    }
    frDisableMode(kModeMetrics);
    frEnableMode(kModeParsing);
    return m.font.get();
}

// MessageRequestEx @ 0x001C9188
// Lays out a page of text at x, y, appended to pFRQ (or alone).
Request* MessageRequestEx(int32_t x, int32_t y, uint32_t z, uint8_t styleIndex, uint8_t colno, uint8_t tp, uint8_t speed,
                          uint32_t text, Request* pFRQ)
{
    MessageInfo m{};
    m.x = x;
    m.y = y;
    m.z = z << 4;
    m.style = static_cast<int8_t>(styleIndex);
    m.colno = static_cast<int8_t>(colno);
    m.tp = static_cast<int8_t>(tp);
    m.speed = speed;
    m.text = text;
    m.font.address = addressOf(pFRQ);
    m.pos = 0;
    m.newline = 1;
    m.position = 1;
    return frAnalyzeMessage(m);
}

// frMessageRequest @ 0x001C9140 (no original name)
Request* MessageRequest(int32_t x, int32_t y, uint8_t styleIndex, uint8_t colno, uint8_t tp, uint8_t speed, uint32_t text,
                        Request* pFRQ)
{
    return MessageRequestEx(x, y, 0, styleIndex, colno, tp, speed, text, pFRQ);
}

// 0x001CA508 (no original name): a short string (laid out without parsing
// its codes) in style 3.
Request* StringRequest(int32_t x, int32_t y, uint32_t z, uint32_t color, uint32_t text, Request* pFRQ)
{
    Request* font = frLinkFontString(guest::table<uint8_t>(kEmptyString2), 0, 0, 0, pFRQ);
    frDisableMode(kModeParsing);
    font = frSetFontString(guest::table<uint8_t>(text), 3, 0, 0, font, false);
    frEnableMode(kModeParsing);
    frSetDrawPosition(*font, x, y);
    frSetPriority(*font, z << 4);
    frSetFontColor(font, color);
    return font;
}

// 0x001C9108 (no original name): plain text, drawn at once.
Request* MessageRequestPlain(int32_t x, int32_t y, uint32_t text, Request* pFRQ)
{
    return MessageRequestEx(x, y, 0, 0, 0, 0, 0x80, text, pFRQ);
}

// 0x001C91E0 (no original name): a new page, keeping the spacing setting.
Request* MessageRequestKeepSpace(int32_t x, int32_t y, uint32_t z, uint8_t styleIndex, uint8_t colno, uint8_t tp,
                                 uint8_t speed, uint32_t text)
{
    const int8_t space = settings().space;
    Request* result = MessageRequestEx(x, y, z, styleIndex, colno, tp, speed, text, nullptr);
    settings().space = space;
    return result;
}

// frGetMessageResult @ 0x001C9220: how the last page ended (bits of mask).
int64_t frGetMessageResult(int64_t mask) { return static_cast<int32_t>(settings().result) & mask; }

// frSetVariableRequest @ 0x001C9230: the string for {var index}.
void frSetVariableRequest(int32_t index, uint32_t pstr) { variable(static_cast<uint32_t>(index)) = pstr; }

// 0x001C8CE0 (no original name)
// How many bytes a control code takes, as the line counter sees it (F2 08
// counts as 2, though pages store it in 4).
int32_t ControlCodeLength(uint16_t code)
{
    switch (code) {
    case 0xf202: case 0xf203: case 0xf206: case 0xf207:
    case 0xf209: case 0xf20a: case 0xf20b: case 0xf20c: case 0xf20d:
        return 4;
    case 0xf20e:
        return 3;
    default:
        return 2;
    }
}

namespace {

int32_t characterLength(const uint8_t* p, bool& newline)
{
    newline = false;
    if ((p[0] & 0xf0) == 0xf0)
        return ControlCodeLength(static_cast<uint16_t>(p[0] << 8 | p[1]));
    if (p[0] == '\n') {
        newline = true;
        return 1;
    }
    return (p[0] & 0x80) ? 2 : 1;
}

} // namespace

// 0x001C8E48 (no original name): the line feeds in a page.
int32_t CountMessageLines(const uint8_t* text)
{
    int32_t lines = 0;
    while (*text) {
        bool newline;
        text += characterLength(text, newline);
        lines += newline;
    }
    return lines;
}

// 0x001C8D28 (no original name)
// Copies line `line` of a page (without its line feed) to `out`.
void CopyMessageLine(const uint8_t* text, uint8_t* out, int32_t line)
{
    int32_t lines = 0;
    while (*text) {
        bool newline;
        const int32_t length = characterLength(text, newline);
        lines += newline;
        if (lines != line) {
            text += length;
        } else if (*text == '\n') {
            ++text;                           // the line feed itself isn't copied
        } else {
            for (int32_t k = 0; k < length; ++k)
                *out++ = *text++;
        }
    }
    *out = 0;
}

} // namespace nocturne::fr

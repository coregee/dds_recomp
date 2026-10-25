// The font engine (frFont), part two: laying out message pages. The JP
// builds' (font_message_us.cpp has the US release's, docs/messages.md the
// codes).
//
// Next to the US release's: no particle codes and no last code; variables
// are all 2-byte characters; the entered names are kept 8 letters to a
// name, shown family name first, and take their palette from the caller
// (which recolors the whole chain); and the line counter's helpers are gone.

#include "nocturne/build.hpp"

#if NOCTURNE_JAPANESE

#include <cstring>

#include "nocturne/external.hpp"
#include "nocturne/address.hpp"
#include "nocturne/interface/font.hpp"

namespace nocturne::fr {

namespace {

constexpr uint32_t kEmptyString = addr(0x0054f430);
constexpr uint32_t kEmptyString2 = addr(0x0054f448);   // (another "")
constexpr uint32_t kVariables = addr(0x0056bbd0);      // uint32[32]: the {var n} strings
constexpr uint32_t kNameGlyphs = addr(0x0056bc50);     // Glyph*[4][8] (US Maniax [4][16])
constexpr uint32_t kNameRefs = addr(0x0056bd50);       // int32[4]
constexpr uint32_t kSaveData = addr(0x0054ea20);       // pointer to the data holding the entered names
constexpr int32_t kNameLetters = 8;              // letters to a name (US Maniax 16)

uint32_t addressOf(const void* p) { return guest::addressOf(p); }
template <class T> T* at(uint32_t address) { return address ? guest::table<T>(address) : nullptr; }
const uint8_t* empty() { return guest::table<uint8_t>(kEmptyString); }
uint32_t& variable(uint32_t index) { return guest::table<uint32_t>(kVariables)[index]; }
uint32_t& nameGlyphAddress(int32_t slot) { return guest::table<uint32_t>(kNameGlyphs)[slot]; }
int32_t& nameRefs(int32_t bank) { return guest::table<int32_t>(kNameRefs)[bank]; }

// The entered names in the save data: for each of 4 names, how many letters
// each part has, the 2-byte codes of its letters (8 per name, family name
// first) and their bitmaps (24x24, 4 bits per pixel); and one name as text.
struct EnteredNames {
    uint8_t* base;
    explicit EnteredNames() : base(guest::table<uint8_t>(*guest::table<uint32_t>(kSaveData))) {}
    uint32_t address() const { return addressOf(base); }
    uint8_t familyLength(int32_t bank) const { return base[0x4178 + 2 * bank]; }
    uint8_t givenLength(int32_t bank) const { return base[0x4179 + 2 * bank]; }
    uint8_t length(int32_t bank, bool given) const { return given ? givenLength(bank) : familyLength(bank); }
    const uint8_t* code(int32_t slot) const { return base + 0x4180 + 2 * slot; }
    uint32_t bitmaps(int32_t bank) const { return address() + static_cast<uint32_t>(bank) * 0x900 + 0x1d78; }
    const uint8_t* text() const { return base + 0x41c0; }
    uint8_t textLength() const { return base[0x4200]; }   // in 2-byte characters
};

} // namespace

// ---- entered names ----------------------------------------------------------------------------

// ps2FontLoadNameBitmapBank @ 0x001C96D8
// Puts one part of an entered name into the texture: `count` 24x24 bitmaps
// from `pixels`, as name glyphs `start`.. (the given name follows the family
// name's letters).
void LoadNameBank(int8_t bank, bool given, int8_t count, uint32_t pixels)
{
    const EnteredNames names;
    const int32_t start = given ? static_cast<int8_t>(names.familyLength(bank)) : 0;
    const int32_t clear = static_cast<int8_t>(names.length(bank, given));
    for (int32_t i = start; i < start + clear; ++i)
        nameGlyphAddress(bank * kNameLetters + i) = 0;
    for (int32_t i = 0; i < count; ++i) {
        uint32_t copy = mem::PoolAllocate(0x120);
        std::memcpy(guest::table<uint8_t>(copy), guest::table<uint8_t>(pixels), 0x120);
        Glyph* glyph = CreateTextureGlyph(24, 24, copy, true);
        pixels += 0x120;
        nameGlyphAddress(bank * kNameLetters + start + i) = addressOf(glyph);
        glyph->index = static_cast<uint16_t>(bank);
    }
    diag::print(diag::Message::NameTranslate, bank);
}

// ps2FontReferenceNameBitmapBank @ 0x001C98C0
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

// ps2FontReleaseNameBank @ 0x001C99C0
// One letter fewer in use; the last one frees the name's glyphs.
void ReleaseNameBank(int8_t bank)
{
    const EnteredNames names;
    const int32_t total = names.familyLength(bank) + names.givenLength(bank);
    int32_t& refs = nameRefs(bank);
    if (!refs || --refs != 0)
        return;
    for (int32_t i = 0; i < total; ++i)
        if (Glyph* glyph = at<Glyph>(nameGlyphAddress(bank * kNameLetters + i)))
            GiveTextureCell(*glyph->cell);
    diag::print(diag::Message::NameRestore, bank);
}

// ps2FontAppendNameBitmapGlyph @ 0x001C9A98
// Appends letter `index` of an entered name as a control text (code 0xFFFF),
// laid out as its glyph if its code is at most 0x83C5.
Request* AppendNameLetter(int8_t bank, int8_t index, Request* pFRQ)
{
    const int32_t slot = bank * kNameLetters + index;
    const uint8_t* p = EnteredNames().code(slot);
    const uint16_t code = static_cast<uint16_t>(p[0] << 8 | p[1]);
    Request* result = AppendControlText(nameGlyphAddress(slot), pFRQ);
    Text& text = *result->str_end;
    const uint32_t value = static_cast<uint32_t>(code) - 0x8080;
    const int32_t glyph = static_cast<int32_t>(((value & 0xff00) >> 1) + (value & 0x7f));
    text.code = 0xffff;
    if (code <= 0x83c5) {
        frGetXShiftLev(text, glyph, false);
        result->str_end->ly = shadowOffset(0, glyph);
    }
    return result;
}

namespace {

Request* appendNamePart(int8_t bank, Request* pFRQ, bool given)
{
    int8_t index = given ? static_cast<int8_t>(EnteredNames().familyLength(bank)) : 0;
    ReferenceNameBank(bank, given);
    for (uint32_t k = 0; k < EnteredNames().length(bank, given); ++k) {
        pFRQ = AppendNameLetter(bank, index, pFRQ);
        index = static_cast<int8_t>(index + 1);
    }
    return pFRQ;
}

} // namespace

// ps2FontAppendNameFirst @ 0x001C9B58: {lastname n}.
Request* AppendFamilyName(int8_t bank, Request* pFRQ, int8_t) { return appendNamePart(bank, pFRQ, false); }

// ps2FontAppendNameSecond @ 0x001C9C28: {firstname n}.
Request* AppendGivenName(int8_t bank, Request* pFRQ, int8_t) { return appendNamePart(bank, pFRQ, true); }

// ps2FontAppendNameBoth @ 0x001C9D00
// {fullname n}: the family name, half a letter of space, the given name.
Request* AppendFullName(int8_t bank, Request* pFRQ, int8_t colno)
{
    Request* family = AppendFamilyName(bank, pFRQ, colno);
    family->w_pxls += 8;
    family->str_end->lw += 8;
    return AppendGivenName(bank, family, colno);
}

// ps2FontAppendResourceName @ 0x001C9D60
// {name n}: the entered name kept as text (one, whatever n), with the
// font's own advances.
Request* AppendNameText(int8_t, int8_t styleIndex, Request* pFRQ, int8_t)
{
    const EnteredNames names;
    uint8_t text[2 * 255 + 1];
    const uint32_t bytes = 2u * names.textLength();
    std::memcpy(text, names.text(), bytes);
    text[bytes] = 0;
    frEnableMode(kModeMetrics);
    Request* result = frLinkFontString(text, styleIndex, 0, 0, pFRQ);
    frDisableMode(kModeMetrics);
    return result;
}

// 0x001CA0D0
// A string as one request per character (1 or 2 bytes), each at depth z
// in `color`, chained after `chain`; the first starts at x and all sit at
// y. A 2-byte character past glyph 0x1C5 is drawn from style 0 at 20 x 20,
// 3 pixels tighter. Laid out with the font's own advances unless `keepMode`
// (the mode is then left as the caller set it).
Request* LinkLetters(int32_t x, int32_t y, uint32_t z, uint32_t color, const uint8_t* pStr, int8_t styleIndex,
                     int8_t keepMode, Request* chain)
{
    const int32_t length = static_cast<int32_t>(std::strlen(reinterpret_cast<const char*>(pStr)));
    if (keepMode == 0)
        frEnableMode(kModeMetrics);
    frDisableMode(kModeParsing);
    for (int32_t i = 0; i < length;) {
        uint8_t letter[3] = {pStr[i], 0, 0};
        int32_t size = 1;
        uint32_t glyph = pStr[i];
        if (static_cast<int8_t>(pStr[i]) < 0) {
            size = 2;
            letter[1] = pStr[i + 1];
            const uint32_t code = static_cast<uint32_t>(pStr[i] << 8 | pStr[i + 1]);
            glyph = (((code + 0x7f80) & 0xff00) >> 1) + (code & 0x7f);
        }
        Request* font;
        if (glyph < 0x1c6) {
            font = frLinkFontString(letter, styleIndex, 0, 0, nullptr);
        } else {
            font = frLinkFontString(letter, 0, 0, 0, nullptr);
            frSetFontSize(*font, 0x14, 0x14);
            frSetFontSpace(*font, -3);
        }
        frSetPriority(*font, z << 4);
        frSetFontColor(font, color);
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

// 0x001CA258: LinkLetters in style 1.
Request* LinkSpacedLetters(int32_t x, int32_t y, uint32_t z, uint32_t color, const uint8_t* pStr, Request* chain)
{
    return LinkLetters(x, y, z, color, pStr, 1, 0, chain);
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

// ps2FontAdvanceMessageLine @ 0x001C8730: the next line.
void AdvanceMessageLine(MessageInfo& m)
{
    m.position = 1;
    m.newline = 1;
    m.y += settings().step << 3;
}

// ps2FontAppendVariable @ 0x001C8508: {var index}, two
// bytes to a character.
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
        text[0] = s[position++];
        text[1] = s[position++];
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
        Request* font = frSetFontString(text, styleIndex, m.colno, m.tp, m.font.get(), false);
        m.font.address = addressOf(font);
        frSetFontSpace(*font, settings().space);
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
    case 0xf20a:   // {fullname n}, {lastname n}, {firstname n}, {name n}, in the
    case 0xf20b:   // palette in effect: the whole chain takes it
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
        frSetFontColNo(m.font.get(), static_cast<uint8_t>(colno));
        frSetFontSpace(*m.font, set.space);
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
    // Meant to skip a leading F2 08, but the test is inverted: it skips four
    // bytes when the page starts with a character followed by 8.
    if ((text[0] & 0xf0) != 0xf0 && text[1] == 8)
        m.pos += 4;
    settings().result &= ~7u;
    frEnableMode(kModeMetrics);
    frDisableMode(kModeParsing);
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
            continue;
        }
        frCreateNewHandle(m);
        int8_t styleIndex = m.style;
        uint8_t character[3] = {};
        if (code < 128) {
            character[0] = static_cast<uint8_t>(code);
        } else {
            code = static_cast<uint16_t>(code << 8 | text[m.pos++]);
            if (code > 0xc07f) {   // codes from 0xC080 are style 8's (the message table's own font)
                code = static_cast<uint16_t>(code - 0x4000);
                styleIndex = 8;
            }
            character[0] = static_cast<uint8_t>(code >> 8);
            character[1] = static_cast<uint8_t>(code);
        }
        m.font.address = addressOf(frSetFontString(character, styleIndex, m.colno, m.tp, m.font.get(), false));
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

// frMessageRequest @ 0x001C9140
Request* MessageRequest(int32_t x, int32_t y, uint8_t styleIndex, uint8_t colno, uint8_t tp, uint8_t speed, uint32_t text,
                        Request* pFRQ)
{
    return MessageRequestEx(x, y, 0, styleIndex, colno, tp, speed, text, pFRQ);
}

// 0x001CA508: a short string (laid out without parsing
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

// 0x001C9108: plain text, drawn at once.
Request* MessageRequestPlain(int32_t x, int32_t y, uint32_t text, Request* pFRQ)
{
    return MessageRequestEx(x, y, 0, 0, 0, 0, 0x80, text, pFRQ);
}

// 0x001C91E0: a new page without spacing, keeping the
// spacing setting.
Request* MessageRequestKeepSpace(int32_t x, int32_t y, uint32_t z, uint8_t styleIndex, uint8_t colno, uint8_t tp,
                                 uint8_t speed, uint32_t text)
{
    const int8_t space = settings().space;
    settings().space = 0;
    Request* result = MessageRequestEx(x, y, z, styleIndex, colno, tp, speed, text, nullptr);
    settings().space = space;
    return result;
}

// frGetMessageResult @ 0x001C9220: how the last page
// ended (bits of mask).
int64_t frGetMessageResult(int64_t mask) { return static_cast<int32_t>(settings().result) & mask; }

// frSetVariableRequest @ 0x001C9230: the string for
// {var index}.
void frSetVariableRequest(int32_t index, uint32_t pstr) { variable(static_cast<uint32_t>(index)) = pstr; }

} // namespace nocturne::fr

#endif // NOCTURNE_JAPANESE

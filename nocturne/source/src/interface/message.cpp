// The message manager (original unit: itfMesManager).
//
// A script opens a message window (Initialize, with a message table), then
// asks for dialogs: RequestMessage lays out a page with the font engine,
// opens the panels and starts drawing; each frame CalcManagerProc fades the
// panels, waits for the button at the end of a page and moves on to the
// next, and runs a selection's cursor. Script commands (Command*) report
// "done" once the window has finished.
#include "nocturne/interface/message.hpp"

#include <cstdio>
#include <cstring>

#include "nocturne/external.hpp"

namespace nocturne {

// ---- the instance list ---------------------------------------------------------------

namespace itf {

// itfMiscLinkInit @ 0x001CAE58
// Chains `count` nodes of `size` bytes into the free list, numbering them.
void MiscLinkInit(LinkStack& stack, uint32_t nodes, int32_t count, int32_t size)
{
    uint32_t node = nodes, previous = 0;
    int8_t id = 0;
    do {
        LinkNode& n = *guest::table<LinkNode>(node);
        --count;
        n.pprev.address = previous;
        n.id = id;
        id = static_cast<int8_t>(id + 1);
        n.pnext.address = node + static_cast<uint32_t>(size);
        previous = node;
        node += static_cast<uint32_t>(size);
    } while (count > 1);
    LinkNode& last = *guest::table<LinkNode>(node);
    last.pprev.address = previous;
    last.pnext.address = 0;
    last.id = id;
    stack.freetail.address = node;
    stack.freehead.address = nodes;
    stack.head.address = 0;
    stack.tail.address = 0;
}

// itfMiscLinkTake @ 0x001CAEB8
// Moves the first free node to the end of the list in use.
LinkNode* MiscLinkTake(LinkStack& stack)
{
    LinkNode* node = stack.freehead.get();
    if (!node)
        return nullptr;
    Ptr32<LinkNode> next = node->pnext;
    if (stack.head) {
        node->pprev = stack.tail;
        stack.tail->pnext.address = guest::addressOf(node);
    } else {
        node->pprev.address = 0;
        stack.head.address = guest::addressOf(node);
    }
    node->pnext.address = 0;
    stack.tail.address = guest::addressOf(node);
    if (next)
        next->pprev.address = 0;
    else
        stack.freetail.address = 0;
    stack.freehead = next;
    return node;
}

// itfMiscLinkGive @ 0x001CAF20
// Unlinks a node and appends it to the free list.
void MiscLinkGive(LinkNode& node, LinkStack& stack)
{
    Ptr32<LinkNode> prev = node.pprev, next = node.pnext;
    if (prev)
        prev->pnext = next;
    else
        stack.head = next;
    if (next)
        next->pprev = prev;
    else
        stack.tail = prev;
    node.pnext.address = 0;
    Ptr32<LinkNode> tail = stack.freetail;
    node.pprev = tail;
    if (tail)
        tail->pnext.address = guest::addressOf(&node);
    uint32_t freehead = stack.freehead.address;
    stack.freetail.address = guest::addressOf(&node);
    if (!freehead)
        stack.freehead.address = guest::addressOf(&node);
}

} // namespace itf

namespace mes {

namespace {

constexpr uint32_t kManager = 0x0056be60;
constexpr uint32_t kPad = 0x002f5830;          // pad trigger bytes (negative: pressed this frame)
constexpr int16_t kNoSpeaker = -1;

// Pad bytes the message manager reads (tentative names from their use).
enum Pad : uint32_t {
    kPadDecide = 1,       // ends a page, picks an option
    kPadSkip = 2,         // held: pages turn by themselves after a few frames
    kPadCancel = 3,
    kPadUp = 6,           // bit 1: repeat
    kPadDown = 7,
};

int8_t pad(uint32_t index) { return *guest::table<int8_t>(kPad + index); }
uint8_t padBits(uint32_t index) { return *guest::table<uint8_t>(kPad + index); }

uint32_t addressOf(const void* p) { return guest::addressOf(p); }

fr::Request* request(uint32_t address) { return address ? guest::table<fr::Request>(address) : nullptr; }

void destroy(Ptr32<fr::Request>& pfont)
{
    if (pfont) {
        fr::DestroyFontRequestAfter(pfont.address);
        pfont.address = 0;
    }
}

void setStat(Instance& pinst, uint32_t clear, uint32_t set) { pinst.stat = (pinst.stat & ~clear) | set; }

} // namespace

Manager& manager() { return *guest::table<Manager>(kManager); }
Instance& instance(int32_t id) { return *manager().nodes[id].instance; }

// ---- construction ------------------------------------------------------------------------

// itfMesInitializeSpeaker @ 0x001CFC58
void InitializeSpeaker(Speaker& speaker, bool defaultpos)
{
    if (defaultpos) {
        speaker.pos.x = 0x430;
        speaker.pos.y = 0x9b0;
    }
    speaker.pfont.address = 0;
    speaker.num = 0xffff;
}

// itfMesInitializeMessage @ 0x001CFC80
void InitializeMessage(Message& message, bool defaultpos)
{
    if (defaultpos) {
        message.pos.x = 0x4b0;
        message.pos.y = 0xa88;
    }
    message.pbinheader.address = 0;
    message.last_spd = 0x80;
    message.pfont.address = 0;
    message.phase = 0;
    message.wait = 0;
    message.lines = 0;
    message.page = 0;
    message.maxpage = 0;
    message.last_style = 0;
    message.last_col = 0;
    message.last_tp = 0;
}

// itfMesInitializeSelect @ 0x001CFCC8
void InitializeSelect(Select& select)
{
    select.pos.x = 0x560;
    select.pos.y = 0xbc8;
    select.select_imm = -1;
    select.numdef = 0;
    select.pfont.address = 0;
    select.mask = 0;
    select.phase = 0;
    select.select = -1;
    select.lines = 0;
    select.alpha = 0;
}

// itfMesResetWindowPara @ 0x001CFED0
// The message panel's frame around the text and its color; type 1 is the
// wide window, 2 the short one. A positive alpha overrides the type's.
void ResetWindowPara(Window& window, int64_t type, int64_t alpha)
{
    int32_t value = alpha > 0 ? static_cast<int32_t>(alpha) : type == 1 ? 0x57 : type == 2 ? 0x87 : 0x66;
    if (type == 1) {
        window.mes_offset[0] = -0x1db0;
        window.mes_color[3] = value;
        window.mes_offset[1] = -0x2f8;
        window.mes_offset[2] = 0x2c30;
        window.mes_offset[3] = 0x548;
    } else {
        window.mes_color[3] = value;
        window.mes_offset[0] = -0x1390;
        window.mes_offset[1] = type == 2 ? -0x208 : -0x3d8;
        window.mes_offset[2] = 0x2a30;
        window.mes_offset[3] = type == 2 ? 0x410 : 0x590;
    }
    window.mes_color[2] = 0x7f;
    window.mes_color[0] = 0x7f;
    window.mes_color[1] = 0x7f;
}

// itfMesInitializeWindow @ 0x001CFD00
void InitializeWindow(Window& window)
{
    window.mes.address = 0;
    window.spk.address = 0;
    ResetWindowPara(window, 0, 0);
}

// itfMesInitializeVariable @ 0x001CFD28
// Clears the string pointers only (their handles stay as they were).
void InitializeVariable(Variable& variable)
{
    for (int i = 31; i >= 0; --i)
        variable.pptr[i] = 0;
}

// itfMesInitializeCurCtr @ 0x001CFD58
void InitializeCurCtr(CurCtr& curctr, bool isdisp)
{
    if (!isdisp)
        curctr.isdraw = 0;
    curctr.ctr_key = 0;
    curctr.ctr0 = 0x40;
    curctr.phase = 0;
    curctr.ctr1 = 0;
}

// itfMesResolveResourceAddress @ 0x001CF100
// Turns the table's offsets into addresses, once.
void ResolveResourceAddress(FileHeader& data)
{
    if (data.resolveaddress)
        return;
    uint32_t base = addressOf(&data);
    pac::RelocatePointers(base + 0x20, base + 0x20, base + data.ofs_addrinfo, data.size_addrinfo);
    data.resolveaddress = 1;
}

// GetTypeHeader @ 0x001CF178
TypeHeader& GetTypeHeader(Instance& pinst, int32_t index)
{
    return guest::table<TypeHeader>(pinst.pdata.address + 0x20)[index];
}

// GetTypeHeader2 @ 0x001CF190
TypeHeader2& GetTypeHeader2(FileHeader& data)
{
    return *guest::table<TypeHeader2>(addressOf(&data) + 0x20 + (data.numtypeheader << 3));
}

// itfMesMngSetResourcePtr @ 0x001CE838
// Gives the window a message table; returns the previous one.
uint32_t SetResourcePtr(int32_t id, uint32_t data)
{
    Instance& pinst = instance(id);
    FileHeader& file = *guest::table<FileHeader>(data);
    uint32_t old = pinst.pdata.address;
    pinst.pdata.address = data;
    ResolveResourceAddress(file);
    TypeHeader2& header = GetTypeHeader2(file);
    pinst.pext = file.mgc == kMagic ? header.pextdata : 0;
    return old;
}

// itfMesMngInitialize @ 0x001CDA40
// Opens a message window on a message table; returns its id.
int32_t Initialize(uint32_t data)
{
    itf::LinkNode& node = *itf::MiscLinkTake(manager().list);
    int32_t id = node.id;
    uint32_t handle = mem::HandleAllocate(sizeof(Instance));
    node.handle = handle;
    uint32_t address = mem::HandleAcquirePointer(handle);
    node.instance.address = address;
    Instance& pinst = *guest::table<Instance>(address);
    pinst.pdata.address = 0;
    SetResourcePtr(id, data);
    pinst.stat = 0;
    pinst.otindex = 0x47;
    pinst.z = 0xfffff0;
    pinst.type = 0;
    pinst.func_kuti = 0;
    InitializeSpeaker(pinst.speaker, true);
    InitializeMessage(pinst.message, true);
    InitializeSelect(pinst.select);
    InitializeWindow(pinst.window);
    InitializeVariable(pinst.variable);
    InitializeCurCtr(pinst.curctr, false);
    ++manager().count;
    return id;
}

// itfMesMngRequestMessageRelease @ 0x001CDD78
// Drops the message (and with `speaker`, the speaker's name).
void RequestMessageRelease(int32_t id, bool speaker)
{
    if (id < 0)
        return;
    Instance& pinst = instance(id);
    destroy(pinst.message.pfont);
    InitializeMessage(pinst.message, false);
    pinst.stat &= 0xfffdfff8;
    if (speaker) {
        destroy(pinst.speaker.pfont);
        InitializeSpeaker(pinst.speaker, false);
    }
}

// itfMesMngRequestSelectRelease @ 0x001CDF80
void RequestSelectRelease(int32_t id)
{
    Instance& pinst = instance(id);
    Select& select = pinst.select;
    destroy(select.pfont);
    select.mask = 0;
    uint32_t stat = pinst.stat;
    select.phase = 0;
    select.lines = 0;
    select.select = -1;
    pinst.stat = stat & 0xfffbffc7;
}

// itfMesReleaseAllWindow @ 0x001CFD88
void ReleaseAllWindow(Instance& pinst)
{
    Window& window = pinst.window;
    if (window.spk) {
        itf::PnlRelease(window.spk.address);
        window.spk.address = 0;
    }
    if (window.mes) {
        itf::PnlRelease(window.mes.address);
        window.mes.address = 0;
    }
    pinst.stat &= 0xfffff0ff;
}

// itfMesReleaseAllVariable @ 0x001CFDF8
void ReleaseAllVariable(Variable& variable)
{
    for (int i = 0; i < 32; ++i) {
        if (variable.pptr[i]) {
            mem::HandleFree(variable.pmh[i]);
            variable.pptr[i] = 0;
        }
    }
}

// itfMesMngReleaseInstance @ 0x001CF058 (no original name; perhaps the HD DestructFlow)
// Closes a window: drops everything it shows and returns its node.
void ReleaseInstance(int32_t id)
{
    Manager& m = manager();
    itf::LinkNode& node = m.nodes[id];
    if (!node.instance)
        return;
    Instance& pinst = *node.instance;
    RequestMessageRelease(id, true);
    RequestSelectRelease(id);
    ReleaseAllWindow(pinst);
    ReleaseAllVariable(pinst.variable);
    pinst.stat = 0;
    mem::HandleFree(node.handle);
    node.instance.address = 0;
    itf::MiscLinkGive(node, m.list);
    --m.count;
}

// itfMesMngRelease @ 0x001CDB38
void Release(int32_t id)
{
    if (id >= 0 && manager().nodes[id].instance)
        ReleaseInstance(id);
}

// itfMesMngInitializeManager @ 0x001CEB58
// At start-up: loads the window texture, prepares the 128 window slots and
// starts the processes that update and draw the windows.
void InitializeManager()
{
    Manager& m = manager();
    m.count = 0;
    m.frame = 0;
    m.config = 0;
    m.texture = tex::Load(0x00535b10);                    // "/itf/MESWIN.TMX"
    itf::MiscLinkInit(m.list, addressOf(m.nodes), 0x80, sizeof(itf::LinkNode));
    for (itf::LinkNode* node = m.list.freehead.get(); node; node = node->pnext.get())
        node->instance.address = 0;
    dds3::StartProcess(0x00535b20, 0x409, 0, 0, 0x001d0ff8, 0x001d10a8, 0);    // "CalcMsgMng": CalcManagerProc
    dds3::StartProcess(0x00535b30, 0x2b1a, 0, 0, 0x001d1038, 0x001d10a8, 0);   // "DrawMsgMng": DrawManagerProc
}

// ExitALL @ 0x001D10A8
// The processes' shutdown: closes every window and drops the texture.
void ExitAll()
{
    Manager& m = manager();
    if (itf::LinkNode* node = m.list.head.get()) {
        int32_t id = node->id;
        for (;;) {
            node = node->pnext.get();
            ReleaseInstance(id);
            if (!node)
                break;
            id = node->id;
        }
    }
    tex::DeferredRelease(m.texture);
    m.texture = 0;
}

// CommitVarTable @ 0x001CF440
// Hands the window's {var n} strings to the font engine.
void CommitVarTable(const Variable& variable)
{
    for (int i = 0; i < 32; ++i)
        fr::SetVariableRequest(i, variable.pptr[i]);
}

// itfMesMngGetVarLocalize @ 0x001CE510
uint32_t GetVarLocalize(int32_t id, int32_t index) { return instance(id).variable.pptr[index]; }

// ---- {var n} strings ------------------------------------------------------------------------

namespace {

constexpr uint32_t kNameBuffer = 0x0056c880;      // BuildCharacterName's output
constexpr uint32_t kSaveData = 0x0054ea20;        // pointer to the data holding the entered names

// Copies a string into a block of its own for {var index}. Without a length,
// the copy is the string's length plus 4, rounded down to a word (so it may
// take up to 3 bytes after the terminator); with one, the block is zeroed
// first.
uint32_t storeVariable(Instance& pinst, int32_t index, const char* source, int32_t length)
{
    Variable& v = pinst.variable;
    if (v.pptr[index]) {
        mem::HandleFree(v.pmh[index]);
        v.pptr[index] = 0;
    }
    uint32_t size = length > 0 ? (static_cast<uint32_t>(length) + 5) & ~3u
                               : (static_cast<uint32_t>(std::strlen(source)) + 4) & ~3u;
    uint32_t handle = mem::HandleAllocate(static_cast<int32_t>(size));
    v.pmh[index] = handle;
    uint32_t block = mem::HandleAcquirePointer(handle);
    v.pptr[index] = block;
    char* dest = guest::table<char>(block);
    if (length > 0) {
        std::memset(dest, 0, size);
        std::memcpy(dest, source, static_cast<size_t>(length));
    } else {
        std::memcpy(dest, source, size);
    }
    return block;
}

const char* guestString(uint32_t address) { return guest::table<char>(address); }

} // namespace

// SetVar @ 0x001CF320
uint32_t SetVar(Instance& pinst, int32_t index, uint32_t pstr, int32_t length)
{
    return storeVariable(pinst, index, guestString(pstr), length);
}

// itfMesMngSetVarImmediate @ 0x001CE7D8
void SetVarImmediate(int32_t id, int32_t index, uint32_t pstr) { SetVar(instance(id), index, pstr, 0); }

// itfMesMngSetVarImmediate2 @ 0x001CE808
void SetVarImmediate2(int32_t id, int32_t index, uint32_t pstr, int32_t length)
{
    SetVar(instance(id), index, pstr, length);
}

// ConvertZenkakuNumber @ 0x001CFE48
// Writes num in decimal (at most 10 digits) and returns the terminator's
// position. (The Japanese name says full-width digits; the US build writes
// ASCII.) A negative number gives one digit of its remainder.
char* ConvertZenkakuNumber(int32_t num, char* buf)
{
    int32_t digits[10];
    int count = 0;
    do {
        digits[count++] = num % 10;
        num /= 10;
    } while (num > 0 && count < 10);
    while (count > 0)
        *buf++ = static_cast<char>(static_cast<uint8_t>(digits[--count]) + '0');
    *buf = 0;
    return buf;
}

// BuildCharacterName @ 0x001CE538 (no original name)
// Copies entered name `index` (0 the hero, 1 Yuko, 2 and 3 the classmates:
// up to ten 2-byte characters; ASCII ones keep only their second byte) to
// a buffer as a string.
void BuildCharacterName(int32_t index)
{
    const uint32_t root = *guest::table<uint32_t>(kSaveData);
    const uint8_t* length = guest::table<uint8_t>(root + 0x6654 + static_cast<uint32_t>(index));
    const uint8_t* name = guest::table<uint8_t>(root + 0x6604 + static_cast<uint32_t>(index) * 20);
    uint8_t* out = guest::table<uint8_t>(kNameBuffer);
    for (int32_t k = 0; k < *length; ++k) {
        uint8_t lead = name[2 * k];
        if (lead & 0x80)
            *out++ = lead;
        *out++ = name[2 * k + 1];
    }
    *out = 0;
}

// itfMesMngSetVar @ 0x001CE5E8
// Sets {var index} to a number, a floor ("B2F", "3F", "R" above 1000) or a
// name from the game's tables.
void SetVarFormatted(int32_t id, int32_t index, int32_t num, uint64_t type)
{
    if (type >= 11)
        return;
    char buffer[0x50] = {};
    uint32_t table = 0;
    switch (static_cast<VarType>(type)) {
    case kVarNumber:
        std::snprintf(buffer, sizeof buffer, "%d", num);
        storeVariable(instance(id), index, buffer, 0);
        return;
    case kVarFloor: {
        char* floor = buffer + 0x10;
        if (num < 1001) {
            char* cursor = floor;
            if (num < 0) {
                num = static_cast<int32_t>(0u - static_cast<uint32_t>(num));
                *cursor++ = 'B';
            }
            cursor = ConvertZenkakuNumber(num, cursor);
            cursor[0] = 'F';
            cursor[1] = 0;
        } else {
            floor[0] = 'R';
            floor[1] = 0;
        }
        storeVariable(instance(id), index, floor, 0);
        return;
    }
    case kVarDevil: table = 0x003e7328; break;
    case kVarItem: table = 0x003e8170; break;
    case kVarSkill: table = 0x003e83f0; break;
    case kVarRace: table = 0x003e7930; break;
    case kVarMagatama: table = 0x003e8c30; break;
    case kVarArea:
        SetVarImmediate(id, index, 0x00311450 + static_cast<uint32_t>(num) * 32);
        return;
    case kVarSubArea:
        SetVarImmediate(id, index, 0x00311850 + static_cast<uint32_t>(num) * 32);
        return;
    case kVarCharacter:
        BuildCharacterName(num);
        SetVarImmediate2(id, index, kNameBuffer, static_cast<int32_t>(std::strlen(guestString(kNameBuffer))));
        return;
    case kVarUnused:
        return;
    }
    SetVarImmediate(id, index, *guest::table<uint32_t>(table + static_cast<uint32_t>(num) * 4));
}

// GetMessagePagePtr @ 0x001CF1A8
uint32_t GetMessagePagePtr(const MesHeader& header, int32_t page)
{
    if (page < 0 || page >= header.page)
        return 0;
    return header.addr[page];
}

// GetSpeakerName @ 0x001CF490
uint32_t GetSpeakerName(Instance& pinst)
{
    return GetTypeHeader2(*pinst.pdata).ppspkhead[pinst.speaker.num];
}

// ---- font request chains ------------------------------------------------------------------

// GetLastLinkFontHandle @ 0x001CF710
fr::Request* GetLastLinkFontHandle(fr::Request* pfont)
{
    while (pfont->next)
        pfont = pfont->next.get();
    return pfont;
}

// GetLastMessagePara @ 0x001CF748
// Remembers how the page ended, for the next page.
void GetLastMessagePara(const fr::Request& pfont, Message& message)
{
    message.last_spd = pfont.draw_spd >> 1;
    const fr::Text& last = *pfont.str_end;
    message.last_style = last.style;
    message.last_col = last.col_no;
    message.last_tp = last.tp;
}

// CountLineMessage @ 0x001CF778
// Lines between two requests of a chain (called with the last request as
// pfont_top and the first as pfont).
int32_t CountLineMessage(const fr::Request& pfont_top, const fr::Request& pfont)
{
    int32_t distance = (pfont.y - pfont_top.y) >> 3;
    if (pfont.y_size == 0)
        divideByZeroTrap();
    return distance / pfont.y_size + 1;
}

// ChangeZBuffer @ 0x001CF7E0
void ChangeZBuffer(fr::Request* pfont, uint32_t z)
{
    for (; pfont; pfont = pfont->next.get())
        pfont->priority = z;
}

// ChangeFontPosition @ 0x001CF7A8
void ChangeFontPosition(fr::Request* pfont, int32_t dx, int32_t dy)
{
    for (; pfont; pfont = pfont->next.get()) {
        int32_t x = pfont->x, y = pfont->y;
        pfont->x = x + dx;
        pfont->y = y + dy;
    }
}

// ChangeFontColorAll @ 0x001CF8B8
void ChangeFontColorAll(fr::Request* pfont, uint8_t color)
{
    for (; pfont; pfont = pfont->next.get())
        for (fr::Text* t = pfont->str.get(); t; t = t->next.get())
            t->col_no = color;
}

// ChangeFontAlpha @ 0x001CF910
void ChangeFontAlpha(fr::Request* pfont, uint32_t alpha)
{
    for (; pfont; pfont = pfont->next.get())
        for (fr::Text* t = pfont->str.get(); t; t = t->next.get())
            t->color = (t->color & 0xffffff00) | alpha;
}

// RaiseMessageSpeedMax @ 0x001CFA00
// Draws the rest of the page at once, except text with a speed of its own.
void RaiseMessageSpeedMax(fr::Request* pfont)
{
    for (; pfont; pfont = pfont->next.get())
        if (pfont->str->tp == 0)
            fr::SetDrawSpeed(addressOf(pfont), 128);
}

// RaiseMessageSpeedMaxAll @ 0x001CFA50
void RaiseMessageSpeedMaxAll(fr::Request* pfont)
{
    for (; pfont; pfont = pfont->next.get())
        fr::SetDrawSpeed(addressOf(pfont), 128);
}

// UnchainFontHandleUnit @ 0x001CF5F0
// Keeps only line `index` of `lines` (the option chosen) and destroys the
// rest; returns the first request of the line kept.
uint32_t UnchainFontHandleUnit(fr::Request* pfont, int32_t index, int32_t lines)
{
    auto drop = [](fr::Request* p) {
        fr::Request* next = p->next.get();
        p->prev.address = 0;
        p->head.address = addressOf(p);
        p->next.address = 0;
        fr::DestroyFontRequestAfter(addressOf(p));
        return next;
    };
    fr::Request* current = pfont;
    int32_t y = current->y;
    for (int32_t remaining = lines - index - 1; remaining > 0; --remaining) {
        for (;;) {
            current = drop(current);
            if (!current)
                return 0;
            if (current->y != y) {
                y = current->y;
                break;
            }
        }
    }
    fr::Request* first = current;
    fr::Request* last = current;
    fr::Request* next;
    for (;;) {
        next = last->next.get();
        if (!next || next->y != y)
            break;
        last = next;
    }
    while (next)
        next = drop(next);
    first->prev.address = 0;
    last->next.address = 0;
    for (fr::Request* p = first; p; p = p->next.get())
        p->head.address = addressOf(last);
    return addressOf(first);
}

// MarkSelectionText @ 0x001CF818 (no original name)
// Colors line `index` of `lines` (mode 1: under the cursor, 0: not).
void MarkSelectionText(fr::Request* pfont, int32_t index, int32_t lines, uint8_t mode)
{
    int32_t y = pfont->y;
    for (int32_t remaining = lines - index - 1; remaining > 0; --remaining) {
        do {
            pfont = pfont->next.get();
            if (!pfont)
                return;
        } while (pfont->y == y);
        y = pfont->y;
    }
    do {
        for (fr::Text* t = pfont->str.get(); t; t = t->next.get())
            t->col_no = mode;
        pfont = pfont->next.get();
    } while (pfont && pfont->y == y);
}

// GetMaxLineWidth @ 0x001CF960 (no original name)
// The widest line of a chain, in 1/16 pixels.
int32_t GetMaxLineWidth(fr::Request* pfont)
{
    int32_t widest = 0;
    while (pfont) {
        const int32_t y = pfont->y;
        int32_t width = 0;
        do {
            width += pfont->w_pxls;
            pfont = pfont->next.get();
        } while (pfont && pfont->y == y);
        if (widest < width)
            widest = width;
    }
    return widest << 4;
}

// GetFontHandleUnit @ 0x001CF500
// Lays out a selection's visible options one below the other (10 units
// apart), as one chain.
uint32_t GetFontHandleUnit(uint32_t ppstr, int32_t num, uint32_t mask, int32_t x, int32_t y, uint32_t z)
{
    uint32_t font = 0;
    for (const uint32_t* text = guest::table<uint32_t>(ppstr); num > 0; --num, mask >>= 1, ++text) {
        if ((mask & 1) == 0) {
            font = fr::MessageRequest(x, y, 0, 0, 0, 0x80, *text, font);
            y += request(font)->y_size * 8 + 10;
        }
    }
    if (font) {
        ChangeZBuffer(request(font), z);
        ChangeFontAlpha(request(font), 0x80);
    }
    return font;
}

// GetNumSelectItem @ 0x001CF4D0
// Options among the first `allitem` that the mask doesn't hide.
int32_t GetNumSelectItem(int32_t allitem, uint32_t mask)
{
    int32_t count = 0;
    for (; allitem > 0; --allitem, mask >>= 1)
        if ((mask & 1) == 0)
            ++count;
    return count;
}

// GetMaskedIndex @ 0x001CF9B0
// The option number of the index-th visible option.
int32_t GetMaskedIndex(int32_t index, uint32_t mask)
{
    int32_t i = 0;
    for (;;) {
        if ((mask & 1) == 0 && --index < 0)
            return i;
        ++i;
        mask >>= 1;
        if (i >= 32)
            return i;
    }
}

// ---- requests ----------------------------------------------------------------------------

// ReadytoMessage @ 0x001CF1D8
// Lays out the current page and notes how it ends.
void ReadytoMessage(Instance& pinst)
{
    Message& m = pinst.message;
    destroy(m.pfont);
    uint32_t text = GetMessagePagePtr(*m.pbinheader, m.page);
    uint32_t font = fr::MessageRequest(m.pos.x, m.pos.y, m.last_style, m.last_col, m.last_tp, m.last_spd, text, 0);
    if (!(pinst.stat & kKeepSpeed) && (manager().config & 1))
        RaiseMessageSpeedMax(request(font));
    GetLastMessagePara(*request(font), m);
    int64_t wait = fr::TestGlobalFlags(3);
    m.wait = static_cast<uint8_t>(wait);
    if (wait & 2)
        pinst.stat |= kNoSpeakerName;
    else
        pinst.stat &= ~kNoSpeakerName;
    if (fr::TestGlobalFlags(4) && pinst.func_kuti)
        guest::callFunction(pinst.func_kuti);
    ChangeZBuffer(request(font), pinst.z);
    fr::Request* last = GetLastLinkFontHandle(request(font));
    int32_t lines = CountLineMessage(*last, *request(font));
    m.pfont.address = font;
    m.lines = static_cast<int16_t>(lines);
}

// OpenMessageWindow @ 0x001CFA90
// Places the message panel around the text and starts fading it in.
void OpenMessagePanel(Instance& pinst)
{
    Window& w = pinst.window;
    if (!w.mes)
        w.mes.address = itf::PnlRegist2(pinst.type == 2 ? 8 : 6, manager().texture);
    const IVector2 pos = pinst.message.pos;
    itf::PnlSetPosition(w.mes.address, pos.x + w.mes_offset[0], pos.y + w.mes_offset[1], pos.x + w.mes_offset[2],
                        pos.y + w.mes_offset[3], pinst.z);
    itf::PnlSetColor(w.mes.address, w.mes_color[0], w.mes_color[1], w.mes_color[2], 0);
    setStat(pinst, kWindowPhaseMask, 0x100);
}

// OpenCheckSpeakerWindow @ 0x001CFB68
// Shows the panel behind the speaker's name, or fades it out when the page
// has no speaker.
void OpenSpeakerPanel(Instance& pinst)
{
    Speaker& s = pinst.speaker;
    Window& w = pinst.window;
    if (s.pfont && !(pinst.stat & kNoSpeakerName)) {
        if (!w.spk) {
            int32_t width = s.pfont->w_pxls << 4;
            uint32_t panel = itf::PnlRegist2(7, manager().texture);
            w.spk.address = panel;
            itf::PnlSetPosition(panel, s.pos.x - 720, s.pos.y - 104, s.pos.x + width + 720, s.pos.y + 232, pinst.z);
            itf::PnlSetColor(w.spk.address, 127, 127, 127, 0);
        }
        setStat(pinst, kSpeakerPhaseMask, 0x1000);
        return;
    }
    if (w.spk)
        pinst.stat |= kSpeakerPhaseMask;
}

// itfMesMngRequestMessage @ 0x001CDB80
// Starts showing `message` from `page`; 0 if the message has no pages.
int32_t RequestMessage(int32_t id, int32_t message, int32_t page)
{
    Instance& pinst = instance(id);
    Message& m = pinst.message;
    Speaker& s = pinst.speaker;
    const MesHeader& header = *guest::table<MesHeader>(GetTypeHeader(pinst, message).ptr);
    m.page = static_cast<int16_t>(page);
    m.pbinheader.address = addressOf(&header);
    m.maxpage = header.page;
    if (header.page == 0) {
        diag::print(diag::Message::NoMessagePage);
        return 0;
    }
    CommitVarTable(pinst.variable);
    if (pinst.pext)
        fr::BindMessageStyle(pinst.pext);
    ReadytoMessage(pinst);
    const uint16_t speaker = header.speaker;
    if (s.num != speaker) {
        destroy(s.pfont);
        s.num = speaker;
        if (speaker != 0xffff) {
            if (pinst.window.spk) {
                itf::PnlRelease(pinst.window.spk.address);
                pinst.window.spk.address = 0;
            }
            uint32_t text = (speaker & 0x8000) ? GetVarLocalize(id, speaker & 0x7fff) : GetSpeakerName(pinst);
            s.pfont.address = fr::MessageRequest(s.pos.x, s.pos.y, 0, 3, 0, 8, text, 0);
            fr::SetDrawPosition(s.pfont.address, s.pos.x, s.pos.y);
            fr::SetDrawSpeed(s.pfont.address, 10);
            ChangeZBuffer(s.pfont.get(), pinst.z);
        }
    }
    OpenSpeakerPanel(pinst);
    const uint32_t stat = pinst.stat, phase = stat & kWindowPhaseMask;
    if ((stat & kWindowOpen) && (phase == 0 || phase == 0x300)) {
        OpenMessagePanel(pinst);
        setStat(pinst, kMessageStateMask, 2);
    } else {
        setStat(pinst, kMessageStateMask, 3);
    }
    m.phase = 1;
    return 1;
}

// itfMesMngRequestSelect @ 0x001CDE58
// Lays out a selection's options below the message.
void RequestSelect(int32_t id, int32_t select)
{
    Instance& pinst = instance(id);
    Select& sel = pinst.select;
    TypeHeader& type = GetTypeHeader(pinst, select);
    if (type.type != 1)
        diag::print(diag::Message::NotASelection, static_cast<int32_t>(type.type));
    destroy(sel.pfont);
    const SelHeader& header = *guest::table<SelHeader>(type.ptr);
    int32_t lines = GetNumSelectItem(header.item, sel.mask);
    int32_t y = sel.pos.y;
    CommitVarTable(pinst.variable);
    if (pinst.pext)
        fr::BindMessageStyle(pinst.pext);
    uint32_t font = GetFontHandleUnit(addressOf(header.ptr), header.item, sel.mask, sel.pos.x, y + lines * -0xa0 + 0xb4,
                                      pinst.z);
    sel.phase = 1;
    sel.lines = static_cast<int16_t>(lines);
    sel.pfont.address = font;
    setStat(pinst, kSelectStateMask, 0x10);
}

// itfMesMngMarkBitStat @ 0x001CE450
// Only the high half of the status can be set or cleared this way.
void MarkBitStat(int32_t id, uint32_t flag)
{
    Instance& pinst = instance(id);
    pinst.stat |= flag & 0xffff0000;
}

// itfMesMngClearBitStat @ 0x001CE480
void ClearBitStat(int32_t id, uint32_t flag)
{
    Instance& pinst = instance(id);
    pinst.stat &= ~flag | 0xffff;
}

// itfMesMngMsgWndCls @ 0x001CD670
// Closes the window: panels fade out, message and selection are dropped.
void MsgWndCls(int32_t id)
{
    Instance& pinst = instance(id);
    const uint32_t stat = pinst.stat;
    if (stat & kWindowPhaseMask)
        pinst.stat = stat | kWindowPhaseMask;
    if (stat & kSpeakerPhaseMask)
        pinst.stat |= kSpeakerPhaseMask;
    RequestMessageRelease(id, true);
    RequestSelectRelease(id);
    pinst.stat &= ~kWindowOpen;
}

// itfMesMngSetMesPosition @ 0x001CE190
void SetMesPosition(int32_t id, int32_t x, int32_t y)
{
    Instance& pinst = instance(id);
    const int32_t dx = x - pinst.message.pos.x, dy = y - pinst.message.pos.y;
    if (dx != 0 || dy != 0) {
        ChangeFontPosition(pinst.message.pfont.get(), dx, dy);
        pinst.message.pos.x = x;
        pinst.message.pos.y = y;
    }
}

// itfMesMngMoveMessagePanel @ 0x001CD380 (no original name; not in the HD remaster)
// Moves the message panel down by y.
void MoveMessagePanel(int32_t id, int32_t y) { itf::PnlSetPositionOffset(instance(id).window.mes.address, 0, y, 0, 0, 0); }

// itfMesMngChangeWindowType @ 0x001CE908
// While no speaker panel is fading, changes the window type and its alpha;
// the message panel is rebuilt on the next page.
void ChangeWindowType(int32_t id, int32_t type, int32_t alpha)
{
    Instance& pinst = instance(id);
    if (pinst.stat & kSpeakerPhaseMask)
        return;
    if (pinst.type == type && pinst.window.mes_color[3] == alpha)
        return;
    pinst.type = static_cast<int16_t>(type);
    ResetWindowPara(pinst.window, type, alpha);
    if (pinst.window.mes) {
        itf::PnlRelease(pinst.window.mes.address);
        pinst.window.mes.address = 0;
    }
}

// itfMesMngSetSelectDefKey @ 0x001CE990
// Makes `key` pick option `index`; not for the buttons that move or confirm.
bool SetSelectDefKey(int32_t id, uint16_t key, uint16_t index)
{
    Select& sel = instance(id).select;
    if (key >= 0x10 || key == kPadDecide || key == kPadUp || key == kPadDown)
        return false;
    DefKey* entry = nullptr;
    for (int32_t i = 0; i < sel.numdef; ++i)
        if (static_cast<uint16_t>(sel.defkey[i].key) == key) {
            entry = &sel.defkey[i];
            break;
        }
    if (!entry) {
        if (sel.numdef > 14)
            return false;
        entry = &sel.defkey[sel.numdef];
        ++sel.numdef;
    }
    entry->index = static_cast<int16_t>(index);
    entry->key = static_cast<int16_t>(key);
    return true;
}

// itfMesMngSetMaskSelect @ 0x001CE008
void SetMaskSelect(int32_t id, uint32_t mask) { instance(id).select.mask = mask; }

// itfMesMngSetSelect @ 0x001CE028
// Puts the cursor on option `selno` (counted among the visible ones).
void SetSelect(int32_t id, int32_t selno)
{
    Select& sel = instance(id).select;
    uint32_t mask = sel.mask;
    uint16_t visible = (mask & 1) == 0;
    for (int32_t i = 0; i < selno; ++i) {
        mask >>= 1;
        if ((mask & 1) == 0)
            ++visible;
    }
    int16_t index = (mask & 1) == 0 ? static_cast<int16_t>(visible - 1) : 0;
    sel.select_imm = index;
    sel.select = index;
}

// itfMesMngSetDefaultSpeed @ 0x001CEB18
void SetDefaultSpeed(int32_t id, uint8_t speed) { instance(id).message.last_spd = speed; }

// itfMesMngSetKutiCallback @ 0x001CEB38
void SetKutiCallback(int32_t id, uint32_t function) { instance(id).func_kuti = function; }

// itfMesMngGetConfig @ 0x001CEC68 (no original name)
uint16_t GetConfig() { return manager().config; }

// itfMesMngGetMessageWidth @ 0x001CEA58 (no original name)
// The width of a message page as laid out, in 1/16 pixels; 0 for none.
int32_t GetMessageWidth(int32_t id, int32_t message, int32_t page)
{
    Instance& pinst = instance(id);
    const MesHeader& header = *guest::table<MesHeader>(GetTypeHeader(pinst, message).ptr);
    if (header.page == 0)
        return 0;
    CommitVarTable(pinst.variable);
    if (pinst.pext)
        fr::BindMessageStyle(pinst.pext);
    uint32_t text = GetMessagePagePtr(header, page);
    if (!text)
        return 0;
    uint32_t font = fr::MessageRequestPlain(0, 0, text, 0);
    int32_t width = GetMaxLineWidth(request(font));
    fr::DestroyFontRequestAfter(font);
    return width;
}

// ---- each frame -------------------------------------------------------------------------

// ForceSetCurCtr @ 0x001CFD78
void ForceSetCurCtr(CurCtr& pcurctr, int16_t phase, int16_t ctr0, int16_t ctr1)
{
    pcurctr.ctr1 = ctr1;
    pcurctr.phase = phase;
    pcurctr.ctr0 = ctr0;
}

// CalcWindow @ 0x001CFFD0
// Fades the message panel (in by 24, out by 8 a frame) and the speaker's
// panel (by 32, up to 200).
void CalcWindow(Instance& pinst)
{
    uint32_t stat = pinst.stat;
    itf::Panel* mes = pinst.window.mes.get();
    switch (stat & kWindowPhaseMask) {
    case 0x100: {
        int32_t alpha = mes->color[3] + 24;
        mes->color[3] = alpha;
        if (alpha < pinst.window.mes_color[3]) {
            stat = pinst.stat;
        } else {
            mes->color[3] = pinst.window.mes_color[3];
            stat = (pinst.stat & 0xfffffcf8) | 0x203;
            pinst.stat = stat;
        }
        break;
    }
    case 0x300: {
        int32_t alpha = mes->color[3] - 8;
        mes->color[3] = alpha;
        if (alpha > 0) {
            stat = pinst.stat;
        } else {
            mes->color[3] = 0;
            stat = pinst.stat & ~kWindowPhaseMask;
            pinst.stat = stat;
        }
        break;
    }
    }
    itf::Panel* spk = pinst.window.spk.get();
    switch (stat & kSpeakerPhaseMask) {
    case 0x1000: {
        int32_t alpha = spk->color[3] + 32;
        spk->color[3] = alpha;
        if (alpha >= 200) {
            spk->color[3] = 200;
            setStat(pinst, kSpeakerPhaseMask, 0x2000);
        }
        break;
    }
    case 0x3000: {
        int32_t alpha = spk->color[3] - 32;
        spk->color[3] = alpha;
        if (alpha <= 0) {
            spk->color[3] = 0;
            pinst.stat &= ~kSpeakerPhaseMask;
            itf::PnlRelease(addressOf(spk));
            pinst.window.spk.address = 0;
        }
        break;
    }
    }
}

// CalcMessage @ 0x001D0118
// At the end of a page, waits for the button (or the skip button, held five
// frames), then lays out the next page or finishes. While drawing, the
// buttons draw the rest of the page at once.
void CalcMessage(Instance& pinst)
{
    Message& m = pinst.message;
    if (m.phase != 1)
        return;
    const uint32_t stat = pinst.stat;
    if ((stat & kMessageStateMask) == 4) {
        uint32_t count = ++pinst.curctr.ctr_key;
        if (stat & kAutoNext) {
            m.phase = -1;
            return;
        }
        if (!(stat & kNoCursor))
            pinst.curctr.isdraw = 1;
        if (pad(kPadDecide) >= 0 && pad(kPadCancel) >= 0 && (pad(kPadSkip) == 0 || count < 5) && m.wait)
            return;
        if (m.wait)
            snd::Play(9, 127, 63);
        InitializeCurCtr(pinst.curctr, false);
        ++m.page;
        if (m.page >= m.maxpage) {
            m.phase = -1;
            return;
        }
        CommitVarTable(pinst.variable);
        if (pinst.pext)
            fr::BindMessageStyle(pinst.pext);
        ReadytoMessage(pinst);
        OpenSpeakerPanel(pinst);
        setStat(pinst, kMessageStateMask, 3);
    } else if ((pad(kPadDecide) < 0 || pad(kPadCancel) < 0 || pad(kPadSkip) != 0) && !(stat & kKeepSpeed)) {
        RaiseMessageSpeedMaxAll(m.pfont.get());
        if (pinst.speaker.pfont)
            fr::SetDrawSpeed(pinst.speaker.pfont.address, 128);
    }
}

// SelectItemMove @ 0x001D0740
// Moves the cursor up (direct < 0) or down, wrapping around.
void SelectItemMove(Select& psel, int32_t direct)
{
    int32_t index = psel.select;
    MarkSelectionText(psel.pfont.get(), index, psel.lines, 0);
    if (direct < 0) {
        if (--index < 0)
            index = psel.lines - 1;
    } else {
        if (++index >= psel.lines)
            index = 0;
    }
    MarkSelectionText(psel.pfont.get(), index, psel.lines, 1);
    psel.select_imm = static_cast<int16_t>(index);
    psel.select = static_cast<int16_t>(index);
    snd::Play(1, 127, 63);
}

// SelectItemDefKey @ 0x001D07F0
// The option of the first direct button pressed (counted among the visible
// options), or -1.
int32_t SelectItemDefKey(Select& psel)
{
    for (int32_t i = 0; i < psel.numdef; ++i) {
        const DefKey& d = psel.defkey[i];
        if (pad(static_cast<uint32_t>(d.key)) >= 0)
            continue;
        uint32_t mask = psel.mask;
        int32_t index = 0;
        for (int32_t bit = d.index; bit > 0; --bit) {
            index += (mask & 1) == 0;
            mask >>= 1;
        }
        if (!(mask & 1))
            return index;
    }
    return -1;
}

// SelectItem @ 0x001D05F0
// Handles the pad while choosing; 1 once an option is picked.
int32_t SelectItem(Instance& pinst)
{
    Select& s = pinst.select;
    int32_t direction = 0;
    if (padBits(kPadUp) & 2) {
        if (s.select != 0 || (padBits(kPadUp) & 0x80))
            direction = -1;
    } else if ((padBits(kPadDown) & 2) && (s.select != s.lines - 1 || (padBits(kPadDown) & 0x80))) {
        direction = 1;
    }
    if (direction) {
        SelectItemMove(s, direction);
        InitializeCurCtr(pinst.curctr, true);
    }
    if (pad(kPadDecide) < 0) {
        snd::Play(8, 127, 63);
        return 1;
    }
    if (s.numdef <= 0)
        return 0;
    int32_t key = SelectItemDefKey(s);
    if (key < 0)
        return 0;
    snd::Play(8, 127, 63);
    int32_t index = s.select;
    if (key == index)
        return 1;
    MarkSelectionText(s.pfont.get(), index, s.lines, 0);
    MarkSelectionText(s.pfont.get(), key, s.lines, 1);
    s.select = static_cast<int16_t>(key);
    s.select_imm = static_cast<int16_t>(key);
    return 1;
}

// SlideUpDownMessage @ 0x001D0518
// Scrolls the message, its panels and the speaker's name by y.
void SlideUpDownMessage(Instance& pinst, int32_t y)
{
    pinst.message.pos.y += y;
    ChangeFontPosition(pinst.message.pfont.get(), 0, y);
    if (pinst.window.mes)
        itf::PnlSetPositionOffset(pinst.window.mes.address, 0, y, 0, 0, 0);
    if (pinst.window.spk)
        itf::PnlSetPositionOffset(pinst.window.spk.address, 0, y, 0, y, 0);
    if (pinst.speaker.pfont) {
        pinst.speaker.pos.y += y;
        ChangeFontPosition(pinst.speaker.pfont.get(), 0, y);
    }
}

// CalcSelect @ 0x001D02C0
// A selection: the message scrolls up to make room, the options light up,
// the player picks one, the others fade, the message scrolls back.
void CalcSelect(Instance& pinst)
{
    Select& s = pinst.select;
    Message& m = pinst.message;
    uint32_t stat = pinst.stat;
    switch (s.phase) {
    case 1: {
        int32_t top = s.pos.y - (s.lines * 160 - 160);
        int32_t bottom = m.pos.y + m.lines * 160;
        if (m.pfont && top < bottom) {
            SlideUpDownMessage(pinst, -64);
            return;
        }
        if ((stat & kSelectKeyMask) == 0x400)
            return;
        if (m.pfont) {
            ChangeFontColorAll(m.pfont.get(), 3);
            stat = pinst.stat;
        }
        s.phase = 2;
        pinst.stat = (stat & ~kSelectStateMask) | 0x18;
        return;
    }
    case 2:
        if ((stat & kSelectStateMask) != 0x20 || SelectItem(pinst) != 1)
            return;
        s.pfont.address = UnchainFontHandleUnit(s.pfont.get(), s.select, s.lines);
        if ((stat & kSelectKeyMask) == 0x800)
            pinst.stat |= kSelectKeyMask;
        s.select = static_cast<int16_t>(GetMaskedIndex(s.select, s.mask));
        s.numdef = 0;
        ForceSetCurCtr(pinst.curctr, 1, 127, 0);
        s.phase = 3;
        setStat(pinst, kSelectStateMask, 0x28);
        s.alpha = 128;
        return;
    case 3:
        s.alpha = static_cast<int16_t>(s.alpha - 16);
        if (s.alpha <= 0) {
            s.alpha = 0;
            s.phase = 4;
            InitializeCurCtr(pinst.curctr, false);
        }
        ChangeFontAlpha(s.pfont.get(), static_cast<uint32_t>(s.alpha));
        return;
    case 4:
        if (!m.pfont || m.pos.y >= 0xa88) {
            s.phase = -1;
            return;
        }
        SlideUpDownMessage(pinst, 64);
        return;
    }
}

// CalcCurCtr @ 0x001D0880
// The cursor's pulse: alpha up to 255, then down to 32 (64 while waiting at
// the end of a page), with a shrinking expansion.
void CalcCurCtr(Instance& pinst)
{
    CurCtr& c = pinst.curctr;
    if (!c.isdraw)
        return;
    if (c.ctr1 > 0)
        c.ctr1 = static_cast<int16_t>(c.ctr1 - 8);
    if (c.phase == 0) {
        c.ctr0 = static_cast<int16_t>(c.ctr0 + 8);
        if (c.ctr0 >= 255) {
            c.phase = 1;
            c.ctr1 = 128;
            c.ctr0 = 255;
        }
    } else if (c.phase == 1) {
        int32_t minimum = (c.isdraw & 1) ? 32 : 64;
        c.ctr0 = static_cast<int16_t>(c.ctr0 - 8);
        if (c.ctr0 <= minimum) {
            c.ctr0 = static_cast<int16_t>(minimum);
            c.phase = 0;
        }
    }
}

// CalcMesFlow @ 0x001CFF98
void CalcMesFlow(Instance& pinst)
{
    CalcWindow(pinst);
    CalcMessage(pinst);
    CalcSelect(pinst);
    CalcCurCtr(pinst);
}

// CalcManagerProc @ 0x001D0FF8
// The manager's process: updates every window, each frame.
void CalcManagerProc()
{
    for (itf::LinkNode* node = manager().list.head.get(); node; node = node->pnext.get())
        CalcMesFlow(*node->instance);
}

// ---- script commands ---------------------------------------------------------------------

// itfMesMngMessage @ 0x001CD2E0
// MESSAGE(n): shows message n; done once it has finished.
int32_t CommandMessage()
{
    int32_t id = scr::GetMessageHandle();
    if (id < 0)
        return 1;
    Instance& pinst = instance(id);
    int32_t message = scr::GetIntPara(0);
    int8_t phase = pinst.message.phase;
    if (phase == 0)
        return RequestMessage(id, message, 0) ? 0 : 1;
    if (phase >= 0)
        return 0;
    pinst.message.phase = 0;
    return 1;
}

// itfMesMngGetPhase @ 0x001CD3C8
int32_t CommandGetPhase(int32_t msgid) { return instance(msgid).message.phase; }
// itfMesMngSetPhase @ 0x001CD3E8
void CommandSetPhase(int32_t msgid, int8_t phase) { instance(msgid).message.phase = phase; }

// itfMesMngSelect @ 0x001CD408
// SELECT(n): shows selection n; done once an option is picked, which
// becomes the command's result.
int32_t CommandSelect()
{
    int32_t id = scr::GetMessageHandle();
    if (id < 0)
        return 1;
    Instance& pinst = instance(id);
    int32_t select = scr::GetIntPara(0);
    int16_t phase = pinst.select.phase;
    if (phase == 0) {
        RequestSelect(id, select);
        return 0;
    }
    if (phase >= 0)
        return 0;
    pinst.select.phase = 0;
    scr::SetIntReturnValue(pinst.select.select);
    RequestSelectRelease(id);
    return 1;
}

// itfMesMngGetSelPhase @ 0x001CD4B0
int16_t CommandGetSelPhase(int32_t msgid) { return instance(msgid).select.phase; }
// itfMesMngSetSelPhase @ 0x001CD4D0
void CommandSetSelPhase(int32_t msgid, int16_t phase) { instance(msgid).select.phase = phase; }
// itfMesMngGetSelectNo @ 0x001CD4F0
int16_t CommandGetSelectNo(int32_t msgid) { return instance(msgid).select.select; }

// itfMesMngMaskSelect @ 0x001CD510: MASK_SELECT(mask) hides options.
int32_t CommandMaskSelect()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0)
        SetMaskSelect(id, static_cast<uint32_t>(scr::GetIntPara(0)));
    return 1;
}

// itfMesMng_SEL_SELNO @ 0x001CD560: SEL_SELNO(n) puts the cursor on option n.
int32_t CommandSetSelectNo()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0)
        SetSelect(id, scr::GetIntPara(0));
    return 1;
}

// itfMesMngOpenWindow @ 0x001CD5B0
// OPEN_MSG_WIN: the next message fades the window in.
int32_t CommandOpenWindow()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0)
        MarkBitStat(id, kWindowOpen);
    return 1;
}

// itfMesMngCloseWindow @ 0x001CD5F8
// CLOSE_MSG_WIN: fades the window out; done once it is gone.
int32_t CommandCloseWindow()
{
    int32_t id = scr::GetMessageHandle();
    if (id < 0)
        return 1;
    uint32_t phase = instance(id).stat & kWindowPhaseMask;
    if (phase == 0x100 || phase == 0x200)
        MsgWndCls(id);
    return phase == 0;
}

// itfMesMngOpenSelectWindow @ 0x001CD700 (does nothing on the PS2)
int32_t CommandOpenSelectWindow() { return 1; }
// itfMesMngCloseSelectWindow @ 0x001CD708 (does nothing on the PS2)
int32_t CommandCloseSelectWindow() { return 1; }

// itfMesMngIgnoreConfig @ 0x001CD790
// IGNORE_CONFIG(on): the player's message speed doesn't hurry the text.
int32_t CommandIgnoreConfig()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0) {
        if (scr::GetIntPara(0) == 0)
            ClearBitStat(id, kKeepSpeed);
        else
            MarkBitStat(id, kKeepSpeed);
    }
    return 1;
}

// itfMesMngSetMesPositionScript @ 0x001CD7F8: MSG_POS(x, y) in pixels.
int32_t CommandSetMesPosition()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0) {
        int32_t x = scr::GetIntPara(0);
        int32_t y = scr::GetIntPara(1);
        SetMesPosition(id, x << 4, y << 3);
    }
    return 1;
}

// itfMesMngSetMesPosDefault @ 0x001CD860
int32_t CommandSetMesPosDefault()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0)
        SetMesPosition(id, 0x4b0, 0xa88);
    return 1;
}

// itfMesMngValidateNext @ 0x001CD8A0
// VALIDATE_NEXT(on): 0 makes pages end without waiting for the button.
int32_t CommandValidateNext()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0) {
        if (scr::GetIntPara(0) == 0) {
            MarkBitStat(id, kAutoNext);
            MarkBitStat(id, kNoCursor);
        } else {
            ClearBitStat(id, kAutoNext);
            ClearBitStat(id, kNoCursor);
        }
    }
    return 1;
}

// itfMesMngWindowType @ 0x001CD920
int32_t CommandWindowType()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0)
        ChangeWindowType(id, scr::GetIntPara(0), 0);
    return 1;
}

// itfMesMngWindowTypeAlpha @ 0x001CD970
int32_t CommandWindowTypeAlpha()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0) {
        int32_t type = scr::GetIntPara(0);
        int32_t alpha = scr::GetIntPara(1);
        ChangeWindowType(id, type, alpha);
    }
    return 1;
}

// itfMesMngSelectDefKey @ 0x001CD9D8: SELECT_DEFKEY(key, option).
int32_t CommandSelectDefKey()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0) {
        int32_t key = scr::GetIntPara(0);
        int32_t index = scr::GetIntPara(1);
        SetSelectDefKey(id, static_cast<uint16_t>(key), static_cast<uint16_t>(index));
    }
    return 1;
}


// itfMesMngSetVarScr @ 0x001CD710: SET_VAR(index, value, type).
int32_t CommandSetVar()
{
    int32_t id = scr::GetMessageHandle();
    if (id >= 0) {
        int32_t index = scr::GetIntPara(0);
        int32_t number = scr::GetIntPara(1);
        int32_t type = scr::GetIntPara(2);
        SetVarFormatted(id, index, number, static_cast<uint64_t>(static_cast<int64_t>(type)));
    }
    return 1;
}

} // namespace mes
} // namespace nocturne

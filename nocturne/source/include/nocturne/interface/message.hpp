// The message manager (original unit: itfMesManager): message windows that
// show dialogs from a message table (MSG1, docs/messages.md) page by page,
// selections, the speaker's name, and the script commands that drive them.
//
// Records are in their PS2 layout; field names are the HD remaster's.
#pragma once

#include <cstddef>
#include <cstdint>

#include "nocturne/guest.hpp"
#include "nocturne/interface/font.hpp"
#include "nocturne/interface/panel.hpp"

namespace nocturne {

// ---- the message table, as loaded ------------------------------------------------

namespace mes {

// itfMesBinFileHeader_t
struct FileHeader {
    uint8_t filetype;           // 7
    uint8_t format;
    int16_t user_id;
    uint32_t filesize;
    uint32_t mgc;               // "MSG1"
    uint32_t extsize;
    uint32_t ofs_addrinfo;      // the relocation table
    uint32_t size_addrinfo;
    uint32_t numtypeheader;     // dialog count
    uint8_t resolveaddress;     // 1 once the offsets are pointers
    uint8_t reserved0;
    uint16_t version;
};
static_assert(sizeof(FileHeader) == 0x20);

constexpr uint32_t kMagic = 0x3147534d;   // "MSG1"

// itfMesBinTypeHeader_t: one per dialog, after the file header.
struct TypeHeader {
    uint32_t type;              // 0 message, 1 selection
    uint32_t ptr;               // the dialog (a MesHeader or SelHeader)
};

// itfMesBinTypeHeader2_t: after the type headers.
struct TypeHeader2 {
    Ptr32<uint32_t> ppspkhead;  // speaker name pointers
    int32_t spknum;
    uint32_t pextdata;          // a style binding (0 on disc)
    uint32_t reserved;
};

// itfMesBinMesHeader_t: a message.
struct MesHeader {
    char label[24];
    int16_t page;               // page count
    uint16_t speaker;           // a speaker index, 0x8000 | variable, 0xFFFF none
    uint32_t addr[1];           // [page]: the pages' text
};
static_assert(offsetof(MesHeader, page) == 0x18 && offsetof(MesHeader, addr) == 0x1c);

// itfMesBinSelHeader_t: a selection.
struct SelHeader {
    char label[24];
    int16_t ext;
    int16_t item;               // option count
    int16_t pattern;
    uint16_t reserved;
    uint32_t ptr[1];            // [item]: the options' text
};
static_assert(offsetof(SelHeader, item) == 0x1a && offsetof(SelHeader, ptr) == 0x20);

// ---- a message window ----------------------------------------------------------------

struct IVector2 {
    int32_t x, y;
};

// Speaker_tag: the speaker's name.
struct Speaker {
    IVector2 pos;
    Ptr32<fr::Request> pfont;
    uint16_t num;               // the speaker shown (0xFFFF none)
    uint16_t pad;
};
static_assert(sizeof(Speaker) == 0x10);

// message_tag: the message being shown.
struct Message {
    IVector2 pos;
    Ptr32<MesHeader> pbinheader;
    Ptr32<fr::Request> pfont;    // the current page
    int8_t phase;               // 0 idle, 1 showing, -1 finished
    uint8_t wait;               // the page ends waiting for the button (bits 0 / 1)
    uint8_t last_style, last_col, last_tp, last_spd;   // carried to the next page
    int16_t lines;
    int16_t page, maxpage;
};
static_assert(sizeof(Message) == 0x1c);

// defkey_tag: a button that picks an option directly.
struct DefKey {
    int16_t key;                // the pad button (index into the trigger bytes)
    int16_t index;              // the option
};

// select_tag: the selection being shown.
struct Select {
    IVector2 pos;
    Ptr32<fr::Request> pfont;
    uint32_t mask;              // options hidden (bit per option)
    int16_t phase;              // 0 idle, 1 opening, 2 choosing, 3 fading, 4 closing, -1 done
    int16_t select;             // the option chosen, among the visible ones
    int16_t select_imm;         // the option under the cursor
    int16_t lines;              // visible options
    int16_t alpha;
    int16_t numdef;
    DefKey defkey[16];
};
static_assert(sizeof(Select) == 0x5c);

// window_tag: the panels behind the speaker's name and the message.
struct Window {
    Ptr32<itf::Panel> spk;
    Ptr32<itf::Panel> mes;
    int32_t mes_offset[4];      // the message panel around the text position
    int32_t mes_color[4];       // r, g, b, alpha
};
static_assert(sizeof(Window) == 0x28);

// variable_tag: strings for the `{var n}` codes.
struct Variable {
    uint32_t pptr[32];
    uint32_t pmh[32];           // their memory handles
};

// curctr_tag: the blinking "next" / selection cursor.
struct CurCtr {
    uint8_t isdraw;
    uint8_t pad;
    int16_t phase;
    int16_t ctr0;               // alpha
    int16_t ctr1;               // expansion
    uint32_t ctr_key;           // frames spent waiting for the button
};
static_assert(sizeof(CurCtr) == 0xc);

// Bits of Instance::stat.
enum : uint32_t {
    kMessageStateMask = 0x7,      // 2 opening, 3 drawing, 4 waiting for the button
    kSelectStateMask = 0x38,      // 0x10 opening, 0x18 choosing, 0x20 input, 0x28 closing
    kWindowPhaseMask = 0x300,     // message panel: 0x100 fading in, 0x200 shown, 0x300 fading out
    kSelectKeyMask = 0xc00,
    kSpeakerPhaseMask = 0x3000,   // speaker panel: 0x1000 in, 0x2000 shown, 0x3000 out
    kNoSpeakerName = 0x10000,     // this page hides the speaker's name ({wait_nospeaker})
    kMessageOpen = 0x20000,
    kSelectOpen = 0x40000,
    kWindowOpen = 0x200000,       // itfMesMngOpenWindow
    kKeepSpeed = 0x400000,        // itfMesMngIgnoreConfig: don't hurry the text
    kAutoNext = 0x800000,         // itfMesMngValidateNext(0): pages end without input
    kNoCursor = 0x100000,
};

// instanceMes_tag: one message window (0x1D4 bytes, from a memory handle).
struct Instance {
    uint32_t stat;
    Ptr32<FileHeader> pdata;    // the message table
    uint32_t pext;              // its style binding
    uint32_t z;
    int16_t otindex;
    int16_t type;               // window type (itfMesMngChangeWindowType)
    Speaker speaker;
    Message message;
    Select select;
    Window window;
    Variable variable;
    CurCtr curctr;
    uint32_t mouthCallback;     // mouth-movement callback ({lipsync}) (HD: func_kuti)
};
static_assert(offsetof(Instance, speaker) == 0x14 && offsetof(Instance, message) == 0x24);
static_assert(offsetof(Instance, select) == 0x40 && offsetof(Instance, window) == 0x9c);
static_assert(offsetof(Instance, variable) == 0xc4 && offsetof(Instance, curctr) == 0x1c4);
static_assert(sizeof(Instance) == 0x1d4);

} // namespace mes

// ---- the instance list (itfMisc) ---------------------------------------------------------

namespace itf {

// itfmisclinkheader_t and the 20-byte nodes of the message manager's list.
struct LinkNode {
    Ptr32<LinkNode> pprev, pnext;
    int32_t id;
    Ptr32<mes::Instance> instance;
    uint32_t handle;
};
static_assert(sizeof(LinkNode) == 0x14);

// A list of nodes in use and a list of free ones.
struct LinkStack {
    Ptr32<LinkNode> head, tail;
    Ptr32<LinkNode> freehead, freetail;
};

void MiscLinkInit(LinkStack& stack, uint32_t nodes, int32_t count, int32_t size);
LinkNode* MiscLinkTake(LinkStack& stack);
void MiscLinkGive(LinkNode& node, LinkStack& stack);

} // namespace itf

// ---- the manager -------------------------------------------------------------------------

namespace mes {

// Manager globals at 0x56BE60.
struct Manager {
    int32_t count;              // instances
    uint32_t texture;           // the window texture
    int32_t frame;              // frames drawn
    uint16_t config;            // bit 0: hurry the text (the player's message speed)
    uint16_t pad;
    itf::LinkStack list;
    itf::LinkNode nodes[0x80];
};
static_assert(offsetof(Manager, list) == 0x10 && offsetof(Manager, nodes) == 0x20);

Manager& manager();
Instance& instance(int32_t id);

// Construction and the table
void InitializeManager();
void ExitAll();
int32_t Initialize(uint32_t data);
void Release(int32_t id);
void ReleaseInstance(int32_t id);
uint32_t SetResourcePtr(int32_t id, uint32_t data);
void ResolveResourceAddress(FileHeader& data);
TypeHeader& GetTypeHeader(Instance& pinst, int32_t index);
TypeHeader2& GetTypeHeader2(FileHeader& data);
uint32_t GetMessagePagePtr(const MesHeader& header, int32_t page);
uint32_t GetSpeakerName(Instance& pinst);
void InitializeSpeaker(Speaker& speaker, bool defaultpos);
void InitializeMessage(Message& message, bool defaultpos);
void InitializeSelect(Select& select);
void InitializeWindow(Window& window);
void ResetWindowPara(Window& window, int64_t type, int64_t alpha);
void InitializeVariable(Variable& variable);
void InitializeCurCtr(CurCtr& curctr, bool isdisp);
void ReleaseAllWindow(Instance& pinst);
void ReleaseAllVariable(Variable& variable);
void CommitVarTable(const Variable& variable);
uint32_t GetVarLocalize(int32_t id, int32_t index);

// {var n} strings
uint32_t SetVar(Instance& pinst, int32_t index, uint32_t pstr, int32_t length);
void SetVarImmediate(int32_t id, int32_t index, uint32_t pstr);
void SetVarImmediate2(int32_t id, int32_t index, uint32_t pstr, int32_t length);
void SetVarFormatted(int32_t id, int32_t index, int32_t num, uint64_t type);
char* ConvertZenkakuNumber(int32_t num, char* buf);
void BuildCharacterName(int32_t index);

// Variable types for SetVarFormatted (itfMesMngSetVar).
enum VarType : uint32_t {
    kVarNumber, kVarDevil, kVarUnused, kVarItem, kVarFloor, kVarSkill,
    kVarArea, kVarSubArea, kVarRace, kVarMagatama, kVarCharacter,
};

// Requests
int32_t RequestMessage(int32_t id, int32_t message, int32_t page);
void RequestMessageRelease(int32_t id, bool speaker);
void RequestSelect(int32_t id, int32_t select);
void RequestSelectRelease(int32_t id);
void ReadytoMessage(Instance& pinst);
void OpenMessagePanel(Instance& pinst);
void OpenSpeakerPanel(Instance& pinst);
void MarkBitStat(int32_t id, uint32_t flag);
void ClearBitStat(int32_t id, uint32_t flag);
void MsgWndCls(int32_t id);
void SetMesPosition(int32_t id, int32_t x, int32_t y);
void MoveMessagePanel(int32_t id, int32_t y);
void ChangeWindowType(int32_t id, int32_t type, int32_t alpha);
bool SetSelectDefKey(int32_t id, uint16_t key, uint16_t index);
void SetMaskSelect(int32_t id, uint32_t mask);
void SetSelect(int32_t id, int32_t selno);
void SetDefaultSpeed(int32_t id, uint8_t speed);
void setMouthCallback(int32_t id, uint32_t function);
uint16_t GetConfig();
int32_t GetMessageWidth(int32_t id, int32_t message, int32_t page);

// Font request chains
fr::Request* GetLastLinkFontHandle(fr::Request* pfont);
void GetLastMessagePara(const fr::Request& pfont, Message& message);
int32_t CountLineMessage(const fr::Request& pfont_top, const fr::Request& pfont);
void ChangeZBuffer(fr::Request* pfont, uint32_t z);
void ChangeFontPosition(fr::Request* pfont, int32_t dx, int32_t dy);
void ChangeFontColorAll(fr::Request* pfont, uint8_t color);
void ChangeFontAlpha(fr::Request* pfont, uint32_t alpha);
void RaiseMessageSpeedMax(fr::Request* pfont);
void RaiseMessageSpeedMaxAll(fr::Request* pfont);
uint32_t UnchainFontHandleUnit(fr::Request* pfont, int32_t index, int32_t lines);
void MarkSelectionText(fr::Request* pfont, int32_t index, int32_t lines, uint8_t mode);
int32_t GetMaxLineWidth(fr::Request* pfont);
uint32_t GetFontHandleUnit(uint32_t ppstr, int32_t num, uint32_t mask, int32_t x, int32_t y, uint32_t z);
int32_t GetNumSelectItem(int32_t allitem, uint32_t mask);
int32_t GetMaskedIndex(int32_t index, uint32_t mask);

// Each frame
void CalcManagerProc();
void CalcMesFlow(Instance& pinst);
void CalcWindow(Instance& pinst);
void CalcMessage(Instance& pinst);
void CalcSelect(Instance& pinst);
int32_t SelectItem(Instance& pinst);
void SelectItemMove(Select& psel, int32_t direct);
int32_t SelectItemDefKey(Select& psel);
void SlideUpDownMessage(Instance& pinst, int32_t y);
void CalcCurCtr(Instance& pinst);
void ForceSetCurCtr(CurCtr& pcurctr, int16_t phase, int16_t ctr0, int16_t ctr1);

// Script commands (return 1 when done, 0 to be called again next frame)
int32_t CommandMessage();
int32_t CommandGetPhase(int32_t msgid);
void CommandSetPhase(int32_t msgid, int8_t phase);
int32_t CommandSelect();
int16_t CommandGetSelPhase(int32_t msgid);
void CommandSetSelPhase(int32_t msgid, int16_t phase);
int16_t CommandGetSelectNo(int32_t msgid);
int32_t CommandMaskSelect();
int32_t CommandSetSelectNo();
int32_t CommandOpenWindow();
int32_t CommandCloseWindow();
int32_t CommandOpenSelectWindow();
int32_t CommandCloseSelectWindow();
int32_t CommandIgnoreConfig();
int32_t CommandSetMesPosition();
int32_t CommandSetMesPosDefault();
int32_t CommandValidateNext();
int32_t CommandWindowType();
int32_t CommandWindowTypeAlpha();
int32_t CommandSelectDefKey();
int32_t CommandSetVar();

} // namespace mes
} // namespace nocturne

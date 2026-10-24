// The battle's sounds (original unit: nbSound). Rewritten from the original
// instructions.
#include "nocturne/battle/sound.hpp"

#include <cstdio>
#include <cstring>

#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/encount.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/data/tables.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"
#include "nocturne/script/vm.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kSoundModels = 0x003e7028;   // uint16_t[]: the unit whose banks a unit uses
constexpr uint32_t kSoundPath = 0x00575450;     // char[]: a bank's file name
constexpr uint32_t kHandleSize = 0x002a8fe8;    // (no C yet) a memory handle's size
constexpr uint32_t kSharedBank = 0x10000;       // requested with the table
constexpr uint32_t kStatMotionSound = 0x200;    // MainProcessData::stat: a motion's bank was sent

// The battle music's state (gp globals at 0x551524).
struct MusicState {
    int32_t piece;        // the piece played
    int32_t second;       // a second piece's channel, switched to once (0 none)
    int32_t partner;      // the piece faded out with it
    int32_t counter;      // which of the normal battles' pieces comes next
    uint32_t bank;        // the main bank
    uint32_t pieceBank;   // the pieces' bank
    int32_t phase;        // loading step (HD: bgmloadphase)
    int32_t done;         // both banks loaded (HD: bgmdone)
};
static_assert(sizeof(MusicState) == 0x20);

MusicState& music() { return *guest::table<MusicState>(0x00551524); }

// The normal battles' pieces (types 1..3), one per battle in turn.
constexpr uint32_t kTypeOnePieces[7] = {0x160000, 0x170000, 0x180000, 0x190000, 0x1a0000, 0x1b0000, 0x1c0000};
constexpr uint32_t kTypeTwoPieces[8] = {0x200000, 0x210000, 0x220000, 0x230000, 0x240000, 0x250000, 0x260000, 0x270000};
constexpr uint32_t kTypeThreePieces[8] = {0x50000, 0x60000, 0x70000, 0x80000, 0x90000, 0xa0000, 0xb0000, 0xc0000};

SoundEntry& entryAt(uint32_t table, int32_t index)
{
    return *guest::table<SoundEntry>(table + static_cast<uint32_t>(index) * sizeof(SoundEntry));
}

SoundEntry& entryAt(int32_t index) { return entryAt(GetMainProcessData()->sound, index); }

// A loaded bank sent to sound memory.
void sendBank(uint32_t handle)
{
    const int32_t size = static_cast<int32_t>(guest::callOriginal(kHandleSize, handle));
    snd::SetBankSource(mem::HandleAcquirePointer(handle), size);
}

// A bank's file requested.
uint32_t requestBank(uint32_t bank)
{
    std::snprintf(guest::table<char>(kSoundPath), 32, "/sound/MIDI%04X.SMG", bank >> 16);
    return file::Request(kSoundPath);
}

} // namespace

// GetUnitID @ 0x0028D070
int32_t formationUnitId(const Formation& form) { return unitModelId(*GetUnitWorkFromFormindex(form.formindex)); }

// nbGetMotionSeNo @ 0x0028D0B0: the motion's piece in the model's record.
int32_t motionSound(int32_t model, int32_t motion)
{
    const uint32_t visual =
        model == 0 ? dat::address::DefaultUnitVisual : dat::address::UnitVisual + static_cast<uint32_t>(model) * sizeof(UnitVisual);
    return *guest::table<int8_t>(visual + offsetof(UnitVisual, motion) + static_cast<uint32_t>(motion) * sizeof(UnitMotion) +
                                 offsetof(UnitMotion, sound));
}

// GetMotionMIDI @ 0x0028D100: bank 0x1000 + model * 16 + the piece. (Debug
// bit 0xC0F is read and changes nothing.)
uint32_t motionBank(int32_t id, int32_t motion)
{
    const uint16_t model = guest::table<const uint16_t>(kSoundModels)[id];
    const int32_t sound = motionSound(model, motion);
    if (sound < 0)
        return 0;
    evt::BitCheck(0xc0f);
    return static_cast<uint32_t>(model * 16 + sound + 0x1000) << 16;
}

// nbGetMotionMIDI @ 0x0028D178
uint32_t formationMotionBank(const Formation& form, int32_t motion) { return motionBank(formationUnitId(form), motion); }

// GetNegoMIDI @ 0x0028D1A8: bank 0x500 + the unit.
uint32_t talkBank(int32_t id) { return static_cast<uint32_t>(id + 0x500) << 16; }

// nbGetNegoMIDI @ 0x0028D1B8
uint32_t formationTalkBank(const Formation& form) { return talkBank(formationUnitId(form)); }

// nbMemoryLoadNegoSe @ 0x0028D1D8: true when the bank is (or is going) in
// sound memory.
bool loadTalkSound(const Formation& form)
{
    GetMainProcessData();
    if (snd::BankStatus(formationTalkBank(form)) != 0) {
        scr::scrPrintf(0x00545bc0);   // "negoSE_ok!"
        return true;
    }
    const int32_t index = findUnitSounds(static_cast<uint32_t>(formationUnitId(form)));
    if (index < 0)
        return false;
    const uint32_t handle = entryAt(index).talkHandle;
    if (handle == 0)
        return false;
    sendBank(handle);
    return true;
}

// nbMemoryLoadMotionSe @ 0x0028D298
bool loadMotionSound(const Formation& form, int32_t motion)
{
    MainProcessData& main = *GetMainProcessData();
    if (motion < 0)
        return false;
    const uint32_t bank = formationMotionBank(form, motion);
    if (bank == 0)
        return false;
    diag::print(diag::Message::MotionMidi, static_cast<int32_t>(bank));
    if (snd::BankStatus(bank) != 0) {
        scr::scrPrintf(0x00545be0);   // "motSE_ok!"
        return true;
    }
    const int32_t index = findUnitSounds(static_cast<uint32_t>(formationUnitId(form)));
    if (index < 0)
        return false;
    const uint32_t handle = *guest::table<uint32_t>(guest::addressOf(&entryAt(main.sound, index)) + offsetof(SoundEntry, handles) +
                                                    static_cast<uint32_t>(motion) * 4);
    if (handle == 0)
        return false;
    sendBank(handle);
    main.stat |= kStatMotionSound;
    return true;
}

// 0x0028D3A8 (no original name)
void releaseUnitSounds(uint32_t id)
{
    MainProcessData& main = *GetMainProcessData();
    const int32_t index = findUnitSounds(id);
    if (index >= 0 && --entryAt(main.sound, index).refs == 0)
        clearSoundEntry(main, index);
}

// 0x0028D418 (no original name): with no free entry, the one before the
// table is written.
SoundEntry* retainUnitSounds(uint32_t id)
{
    MainProcessData& main = *GetMainProcessData();
    const int32_t index = findUnitSounds(id);
    if (index >= 0) {
        ++entryAt(main.sound, index).refs;
        return nullptr;
    }
    SoundEntry& e = entryAt(main.sound, emptySoundEntry());
    e.used = 1;
    e.unitid = static_cast<uint16_t>(id);
    e.refs = 1;
    return &e;
}

// 0x0028D4B8 (no original name): each motion's bank and the talk bank.
int32_t requestUnitSounds(uint32_t id)
{
    GetMainProcessData();
    SoundEntry* e = retainUnitSounds(id);
    if (!e)
        return 1;
    for (int32_t i = 0; i < kMotionSounds; ++i) {
        const uint32_t bank = motionBank(static_cast<int32_t>(id), i);
        if (bank == 0)
            continue;
        e->requests[i] = requestBank(bank);
        scr::scrPrintf(0x00545c08, kSoundPath);   // "load %s"
    }
    e->talkRequest = requestBank(talkBank(static_cast<int32_t>(id)));
    return 1;
}

// nbUpdateSoundTable @ 0x0028D5C0
void updateSoundTable(MainProcessData& data)
{
    for (int32_t i = 0; i < kSoundEntries; ++i) {
        SoundEntry& e = entryAt(data.sound, i);
        if (e.used == 0)
            continue;
        for (int32_t k = 0; k < kMotionSounds; ++k) {
            if (e.requests[k] != 0 && file::CheckEnd(e.requests[k])) {
                e.handles[k] = file::GetMemHandle(e.requests[k]);
                file::RequestRelease(e.requests[k]);
                e.requests[k] = 0;
            }
        }
        if (e.talkRequest != 0 && file::CheckEnd(e.talkRequest)) {
            e.talkHandle = file::GetMemHandle(e.talkRequest);
            file::RequestRelease(e.talkRequest);
            e.talkRequest = 0;
        }
    }
}

// 0x0028D6C0 (no original name)
int32_t emptySoundEntry()
{
    for (int32_t i = 0; i < kSoundEntries; ++i)
        if (entryAt(i).used == 0)
            return i;
    return -1;
}

// 0x0028D718 (no original name)
int32_t findUnitSounds(uint32_t id)
{
    for (int32_t i = 0; i < kSoundEntries; ++i) {
        const SoundEntry& e = entryAt(i);
        if (e.used != 0 && e.unitid == id)
            return i;
    }
    return -1;
}

// nbFreeSound1 @ 0x0028D778: its banks' memory and files let go.
void clearSoundEntry(MainProcessData& data, int32_t index)
{
    SoundEntry& e = entryAt(data.sound, index);
    if (e.used == 0)
        return;
    for (int32_t k = 0; k < kMotionSounds; ++k) {
        if (e.handles[k] != 0)
            mem::HandleFree(e.handles[k]);
        const uint32_t request = e.requests[k];
        e.handles[k] = 0;
        if (request != 0)
            file::RequestRelease(request);
        e.requests[k] = 0;
    }
    if (e.talkHandle != 0)
        mem::HandleFree(e.talkHandle);
    const uint32_t request = e.talkRequest;
    e.talkHandle = 0;
    if (request != 0)
        file::RequestRelease(request);
    e.refs = 0;
    e.talkRequest = 0;
    e.unitid = 0;
    e.used = 0;
}

// nbFreeSound @ 0x0028D850
void freeSounds(MainProcessData& data)
{
    for (int32_t i = 0; i < kSoundEntries; ++i)
        clearSoundEntry(data, i);
    mem::HandleFree(data.sound_mem);
    data.sound = 0;
    data.sound_mem = 0;
}

// nbInitSound @ 0x0028D8B0
void initSounds(MainProcessData& data)
{
    data.sound_mem = mem::HandleAllocate(kSoundEntries * sizeof(SoundEntry));
    data.sound = mem::HandleAcquirePointer(data.sound_mem);
    std::memset(guest::table<uint8_t>(data.sound), 0, kSoundEntries * sizeof(SoundEntry));
    if (snd::BankStatus(kSharedBank) == 0)
        snd::EnsureBank(kSharedBank);
}

// nbBgmLoadChk @ 0x0028D918: the main bank loaded, then the pieces' bank
// requested and loaded (one step a call).
bool musicLoaded()
{
    MusicState& m = music();
    if (m.done == 1)
        return true;
    switch (m.phase) {
    case 1:
        if (snd::BankStatus(m.bank) == 1)
            ++m.phase;
        return false;
    case 2:
        m.phase = 3;
        return false;
    case 3:
        if (snd::BankStatus(m.pieceBank) != 0) {
            m.phase = 5;
            return false;
        }
        snd::EnsureBank(m.pieceBank);
        ++m.phase;
        return false;
    case 4:
        if (snd::BankStatus(m.pieceBank) == 1)
            ++m.phase;
        return false;
    case 5:
        m.phase = 0;
        m.done = 1;
        return true;
    default:
        return false;
    }
}

// nbBgmLoad @ 0x0028D9E0: a battle's music (encdata 0) or a field
// encounter's. Types 1..3 are the normal battles: their main piece's
// bank holds the battle theme, and one of seven or eight pieces is picked
// by the counter.
void loadMusic(uint32_t encdata)
{
    MusicState& m = music();
    if (m.phase != 0)
        return;
    const int32_t type = encdata == 0 ? battleMusic() : fieldMusic(encdata);
    m.done = 0;
    // The other types: a main bank X and a pieces' bank Y, as X << 16 and
    // Y << 16; most play piece 1 of the main bank.
    auto single = [&](uint32_t bank, uint32_t pieces, bool firstPiece) {
        m.bank = bank;
        m.pieceBank = pieces;
        m.piece = static_cast<int32_t>(firstPiece ? bank | 1 : bank);
        m.second = 0;
        m.partner = m.piece;
    };
    switch (type) {
    case 1:
        m.piece = 0x150001;
        m.partner = 0x150002;
        m.second = 0x150002;
        m.bank = 0x150000;
        m.pieceBank = kTypeOnePieces[m.counter % 7];
        break;
    case 2:
        m.piece = 0x1f0001;
        m.partner = 0x1f0002;
        m.bank = 0x1f0000;
        m.second = 0x1f0002;
        m.pieceBank = kTypeTwoPieces[m.counter % 8];
        break;
    case 3:
        m.partner = 0x40001;
        m.bank = 0x40000;
        m.piece = 0x40001;
        m.second = 0;
        m.pieceBank = kTypeThreePieces[m.counter % 8];
        break;
    case 4: single(0x110000, 0x120000, false); break;
    case 5: single(0x1d0000, 0x1e0000, true); break;
    case 6: single(0x280000, 0x290000, true); break;
    case 7: single(0xd0000, 0xe0000, true); break;
    case 8: single(0xf0000, 0x100000, true); break;
    case 9: single(0x130000, 0x140000, true); break;
    case 10: single(0x840000, 0x850000, false); break;
    case 11: single(0x860000, 0x870000, false); break;
    case 12: single(0x880000, 0x890000, false); break;
    case 13: single(0x8a0000, 0x8b0000, false); break;
    case 14: single(0x820000, 0x830000, false); break;
    case 15: single(0x800000, 0x810000, true); break;
    default: break;
    }
    if (snd::BankStatus(m.bank) == 0) {
        snd::EnsureBank(m.bank);
        m.phase = 1;
    } else {
        m.phase = 3;
    }
}

// nbBgmNext @ 0x0028DD50
void nextMusic() { ++music().counter; }

// nbBgmPlay @ 0x0028DD60
void playMusic() { snd::PlayMidi(music().piece); }

// nbBgmTrans @ 0x0028DD78 (tentative: the HD name in order; Ghidra's
// unsourced name was nbStopMotionSe)
void switchMusic()
{
    MusicState& m = music();
    if (m.second > 0) {
        snd::SelectOutput(m.second);
        m.second = 0;
    }
}

// nbBgmFadeOut @ 0x0028DDA8 (tentative: the HD name in order)
void fadeOutMusic()
{
    snd::FadeOutMidi(music().piece);
    snd::FadeOutMidi(music().partner);
}

// nbBgmStop @ 0x0028DDD0 (its debug print's name)
void stopMusic()
{
    const MusicState& m = music();
    diag::print(diag::Message::BgmStop, m.second, m.partner);
    snd::FadeOutMidi(m.piece);
    snd::FadeOutMidi(m.partner);
    snd::FadeOutMidi(0x2b0000);
}

// 0x0028DE28 (no original name)
void resetMusicChannel() { snd::SelectChannel(0); }

} // namespace nocturne::nb

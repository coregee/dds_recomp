// The battle's sounds (original unit: nbSound): the units' sound banks and
// the battle music.
//
// Each unit's motions have their own sound banks (one file each,
// "/sound/MIDI%04X.SMG"), and a demon's talks one more. The battle keeps a
// table of ten units' banks (MainProcessData::sound, 0x8C0 bytes in a
// memory handle): the files are requested when a unit joins, collected as
// they load, and sent to sound memory when a motion or a talk needs them.
//
// A bank is named by its file number in the upper half of a word (the
// lower half picks a piece in it).
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbSound_t: one unit's banks (0xE0 bytes).
struct SoundEntry {
    int16_t used;             // (HD: exist)
    uint16_t unitid;          // (HD: id)
    int32_t refs;             // the units sharing it (HD: linkcnt)
    uint32_t requests[26];    // each motion's file, while it loads
    uint32_t handles[26];     // ... then its memory handle (HD: motse_h)
    uint32_t talkRequest;     // the talk's file, while it loads
    uint32_t talkHandle;      // ... then its memory handle
};
static_assert(sizeof(SoundEntry) == 0xe0);

inline constexpr int32_t kSoundEntries = 10;
inline constexpr int32_t kMotionSounds = 26;

// The units' banks.
int32_t formationUnitId(const Formation& form);             // GetUnitID: the unit's id for its model
int32_t motionSound(int32_t model, int32_t motion);         // nbGetMotionSeNo: the motion's piece (-1 none)
uint32_t motionBank(int32_t id, int32_t motion);            // GetMotionMIDI: its bank (0 none)
uint32_t formationMotionBank(const Formation& form, int32_t motion);   // nbGetMotionMIDI
uint32_t talkBank(int32_t id);                              // GetNegoMIDI: a demon's talk bank
uint32_t formationTalkBank(const Formation& form);          // nbGetNegoMIDI
bool loadTalkSound(const Formation& form);                  // nbMemoryLoadNegoSe: the talk bank sent to sound memory
bool loadMotionSound(const Formation& form, int32_t motion);   // nbMemoryLoadMotionSe: ... a motion's
int32_t emptySoundEntry();                                  // a free entry (-1 none)
// (The entry helpers below have no original names.)
int32_t findUnitSounds(uint32_t id);                        // the unit's entry (-1 none)
SoundEntry* retainUnitSounds(uint32_t id);                  // one more user: a new entry, or null if it had one
void releaseUnitSounds(uint32_t id);                        // one fewer: freed with the last
int32_t requestUnitSounds(uint32_t id);                     // its files requested (a new entry)
void updateSoundTable(MainProcessData& data);               // nbUpdateSoundTable: the files loaded collected
void clearSoundEntry(MainProcessData& data, int32_t index); // nbFreeSound1
void freeSounds(MainProcessData& data);                     // nbFreeSound: every entry, and the table
void initSounds(MainProcessData& data);                     // nbInitSound: the table, and bank 1 requested

// The battle music. An encounter names a music type (encount.hpp); each
// type has a main bank, maybe a second bank of pieces (the normal battles
// pick one by a counter), and the pieces played.
bool musicLoaded();                                         // nbBgmLoadChk: both banks loaded (one step a call)
void loadMusic(uint32_t encdata);                           // nbBgmLoad: the banks chosen, the main one requested
void nextMusic();                                           // nbBgmNext: the next normal battle's piece
void playMusic();                                           // nbBgmPlay
void switchMusic();                                         // nbBgmTrans (tentative): the second piece's channel
void fadeOutMusic();                                        // nbBgmFadeOut (tentative)
void stopMusic();                                           // nbBgmStop: ... and piece 0x2B0000 too
void resetMusicChannel();                                   // (no original name) channel 0 chosen

} // namespace nocturne::nb

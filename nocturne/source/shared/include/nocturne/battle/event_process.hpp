// The battle's events (original unit: nbEventProcess): a death's or a
// script's event (MainProcessData::eventno) runs as a process ("nb_event")
// whose step functions come from the event table; it loads the event's
// pack and sound bank beforehand, plays its music, and on shutdown puts the
// units back in their wait motions.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"

namespace nocturne::nb {

// nbEventFuncList_t: an event (the table at 0x527260, by eventno % 100).
struct EventEntry {
    int32_t resource;      // its pack (0 none)
    uint32_t func;         // its process function (0 none)
    int32_t encno;         // the encounter it belongs to (for the loads ahead)
    int32_t seBank;        // its music: a sound bank (0 none) ...
    int32_t seIndex;       // ... and the piece in it (HD: seid, the two in one)
    uint16_t fadetime, fadeout, fadestop, fadein;
};
static_assert(sizeof(EventEntry) == 0x1c);

// nbEventProcessData_t (0x28 bytes, from the pool).
struct EventProcessData {
    Ptr32<MainProcessData> data;
    int32_t eventrid;       // the event's pack
    int32_t time;           // frames since it started
    int32_t seq, seqtime;   // the event's step, and frames in it
    uint32_t userdata;      // a block the event's function may allocate (released at shutdown)
    uint32_t usershutdown;  // ... and a function to call then
    uint32_t file, pfile;   // its file and pack requests
    uint32_t mem;           // a memory handle
};
static_assert(sizeof(EventProcessData) == 0x28);

const EventEntry& eventEntry(int32_t eventno);
void startEventSound(MainProcessData& data);            // nbStartBattleEventSound
void stopEventSound(MainProcessData& data);             // nbStopBattleEventSound
void loadEventPacks(MainProcessData& data);             // nbLoadBattleEventPackInit: this encounter's packs and banks
bool eventPacksLoaded(MainProcessData& data);           // nbLoadBattleEventPack
void countEventTime(uint32_t process);                  // nbUpdateEventProcessData: a frame
void nextEventStep(EventProcessData* ed);               // nbNextEventSeq
Formation* eventForm();                                 // nbGetEventForm: the first enemy present
uint32_t createBasicEffect(uint32_t p, uint32_t pos, uint32_t rot);   // nbCreateBasicEffect
void resetWaitMotions(EventProcessData& ed);            // ResetWaitMotion: every unit present
void setWaitMotions(EventProcessData& ed);              // SetWaitMotion: ... and its motion restarted
int32_t deadEventFadeTime(int32_t eventno);             // nbGetDeadEventFadeTime
int32_t deadEventFadeOutFrame(int32_t eventno);         // nbGetDeadEventFadeOutFrame
int32_t deadEventFadeInFrame(int32_t eventno);          // nbGetDeadEventFadeInFrame
int32_t deadEventFadeStopFrame(int32_t eventno);        // nbGetDeadEventFadeStopFrame

// The process: each returns the next process function (0 the same, -1 done).
uint32_t runEventStart(uint32_t process);               // nbEventProcess1
uint32_t runEventSetup(uint32_t process);               // nbEventProcess3: then the event's own function
void shutdownEvent(uint32_t process);                   // nbEventShutdown
void startEvent(MainProcessData& data);                 // nbInitEventProcess

} // namespace nocturne::nb

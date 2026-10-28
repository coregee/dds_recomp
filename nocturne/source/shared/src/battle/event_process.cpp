// The battle's events (original unit: nbEventProcess). Rewritten from the
// original instructions.
#include "nocturne/battle/combatant.hpp"
#include "nocturne/battle/event_process.hpp"

#include <cstddef>

#include "nocturne/address.hpp"
#include "nocturne/battle/kouka.hpp"
#include "nocturne/external.hpp"
#include "nocturne/build.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kEvents = addr(0x00527260);          // EventEntry[100]
constexpr uint32_t kProcessName = addr(0x00545dc8);     // "nb_event"
constexpr uint32_t kRunEventStart = addr(0x0028fe48);
constexpr uint32_t kRunEventSetup = addr(0x0028fd18);
constexpr uint32_t kShutdownEvent = addr(0x0028fec8);
constexpr uint32_t kLoadEventPack = addr(0x001fac78);   // (no C yet) starts a pack's loading process: it
constexpr uint32_t kEventPackState = addr(0x001fa1f0);  // ... and its state (2 loaded)
constexpr uint32_t kCreateEffect = addr(0x00114770);    // (no C yet) the effect library's basic effect
constexpr uint32_t kStatEvent = 0x1000;           // MainProcessData::stat: an event runs
constexpr int32_t kEventPacks = kBuild.vanilla ? 14 : 16;   // the entries with packs to load

static_assert(offsetof(MainProcessData, EventProcessID) == 0x118 && offsetof(MainProcessData, encno) == 0x34);

const EventEntry* events() { return guest::table<const EventEntry>(kEvents); }

EventProcessData& eventData(uint32_t process) { return *guest::table<EventProcessData>(dds3::GetProcessData(process)); }

Formation& formAt(MainProcessData& main, int32_t index) { return guest::table<Formation>(main.form.address)[index]; }

} // namespace

const EventEntry& eventEntry(int32_t eventno) { return events()[eventno]; }

// nbStartBattleEventSound @ 0x0028F7E8
void startEventSound(MainProcessData& data)
{
    const EventEntry& e = eventEntry(data.eventno);
    if (e.seBank != 0)
        snd::PlayMidi(e.seBank + e.seIndex);
}

// nbStopBattleEventSound @ 0x0028F840
void stopEventSound(MainProcessData& data)
{
    const EventEntry& e = eventEntry(data.eventno);
    if (e.seIndex != 0 && e.seBank != 0)
        snd::FadeOutMidi(e.seBank + e.seIndex);
}

// nbLoadBattleEventPack @ 0x0028F890: every pack and bank of the
// encounter's events (the first sixteen; the first release's fourteen) in
// memory.
bool eventPacksLoaded(MainProcessData& data)
{
    for (int32_t i = 0; i < kEventPacks; ++i) {
        const EventEntry& e = events()[i];
        if (e.encno == 0 || e.encno != data.encno)
            continue;
        if (e.resource != 0 && static_cast<int32_t>(guest::callOriginal(kEventPackState, static_cast<uint32_t>(e.resource))) != 2)
            return false;
        if (e.seBank != 0 && snd::BankStatus(static_cast<uint32_t>(e.seBank)) != 1)   // (in memory, not on its way)
            return false;
    }
    return true;
}

// nbLoadBattleEventPackInit @ 0x0028F958: their loading started (the packs'
// processes children of the battle).
void loadEventPacks(MainProcessData& data)
{
    for (int32_t i = 0; i < kEventPacks; ++i) {
        const EventEntry& e = events()[i];
        if (e.encno == 0 || e.encno != data.encno)
            continue;
        if (e.resource != 0)
            dds3::LinkProcess(data.MainProcessID, guest::callOriginal(kLoadEventPack, static_cast<uint32_t>(e.resource)));
        if (e.seBank != 0)
            snd::EnsureBank(static_cast<uint32_t>(e.seBank));
    }
}

// nbUpdateEventProcessData @ 0x0028F9F0
void countEventTime(uint32_t process)
{
    if (const uint32_t data = dds3::GetProcessData(process)) {
        EventProcessData& ed = *guest::table<EventProcessData>(data);
        ++ed.time;
        ++ed.seqtime;
    }
}

// nbNextEventSeq @ 0x0028FA48
void nextEventStep(EventProcessData* ed)
{
    if (ed) {
        ed->seqtime = 0;
        ++ed->seq;
    }
}

// nbGetEventForm @ 0x0028FA80
Formation* eventForm()
{
    MainProcessData& main = *GetMainProcessData();
    for (int32_t i = 4; i < 14; ++i)
        if (formAt(main, i).stat & 1)
            return &formAt(main, i);
    return nullptr;
}

// nbCreateBasicEffect @ 0x0028FAD8: the effect, marked (its state's bit 1).
uint32_t createBasicEffect(uint32_t p, uint32_t pos, uint32_t rot)
{
    const uint32_t effect = guest::callOriginal(kCreateEffect, p, pos, rot);
    *guest::table<uint32_t>(*guest::table<uint32_t>(effect + 0x18) + 4) |= 1;   // (0x115060)
    return effect;
}

// ResetWaitMotion @ 0x0028FB10
void resetWaitMotions(EventProcessData& ed)
{
    for (int32_t i = 0; i < 14; ++i) {
        Formation& form = formAt(*ed.data, i);
        if ((form.stat & 1) && (form.stat & 2))
            setWaitMotion(form, 0, ee::Float::fromBits(0x3f800000));
    }
}

// SetWaitMotion @ 0x0028FB90
void setWaitMotions(EventProcessData& ed)
{
    for (int32_t i = 0; i < 14; ++i) {
        Formation& form = formAt(*ed.data, i);
        if ((form.stat & 1) && (form.stat & 2)) {
            setWaitMotion(form, 0, ee::Float::fromBits(0x3f800000));
            startMotion(form, 0, 0, ee::Float::fromBits(0x3f800000));
        }
    }
}

// nbGetDeadEventFadeTime @ 0x0028FC38
int32_t deadEventFadeTime(int32_t eventno) { return eventEntry(eventno % 100).fadetime; }
// nbGetDeadEventFadeOutFrame @ 0x0028FC70
int32_t deadEventFadeOutFrame(int32_t eventno) { return eventEntry(eventno % 100).fadeout; }
// nbGetDeadEventFadeInFrame @ 0x0028FCA8
int32_t deadEventFadeInFrame(int32_t eventno) { return eventEntry(eventno % 100).fadein; }
// nbGetDeadEventFadeStopFrame @ 0x0028FCE0
int32_t deadEventFadeStopFrame(int32_t eventno) { return eventEntry(eventno % 100).fadestop; }

// nbEventProcess3 @ 0x0028FD18: enemies' ailments cured, every unit in its
// wait motion and stat bit 8 cleared; then the event's own function, its
// music started (none: the event is over).
uint32_t runEventSetup(uint32_t process)
{
    EventProcessData& ed = eventData(process);
    MainProcessData& main = *ed.data;
    for (int32_t i = 4; i < 14; ++i) {
        Formation& form = formAt(main, i);
        if (!(form.stat & 1))
            continue;
        const UnitWork* unit = GetUnitWorkFromFormindex(i);
        if (unit && (unit->badstat & 0xfff))
            makeAilmentCurePackets(0, 0, form);
    }
    resetWaitMotions(ed);
    for (int32_t i = 0; i < 14; ++i)
        formAt(main, i).stat &= ~8u;
    const uint32_t func = eventEntry(main.eventno).func;
    if (func == 0)
        return 0xffffffffu;
    ed.usershutdown = 0;
    startEventSound(main);
    return func;
}

// nbEventProcess1 @ 0x0028FE48: the event's pack noted.
uint32_t runEventStart(uint32_t process)
{
    MainProcessData& main = *GetMainProcessData();
    EventProcessData& ed = eventData(process);
    diag::print(diag::Message::BattleEvent, main.eventno);
    const int32_t resource = eventEntry(main.eventno).resource;
    main.eventrid = resource;
    if (resource > 0)
        ed.eventrid = resource;
    return kRunEventSetup;
}

// nbEventShutdown @ 0x0028FEC8: the music faded, the battle's event
// cleared, the units in their wait motions, and the event's memory, files
// and own shutdown let go.
void shutdownEvent(uint32_t process)
{
    MainProcessData& main = *GetMainProcessData();
    stopEventSound(main);
    main.EventProcessID = 0;
    main.eventno = 0;
    main.stat &= ~kStatEvent;
    EventProcessData& ed = eventData(process);
    setWaitMotions(ed);
    if (ed.mem != 0) {
        mem::HandleFree(ed.mem);
        ed.mem = 0;
    }
    if (ed.file != 0) {
        file::WaitIdle();
        file::RequestRelease(ed.file);
        ed.file = 0;
    }
    if (ed.pfile != 0) {
        file::WaitIdle();
        if (kBuild.vanilla)
            file::RequestRelease(ed.pfile);   // (the first release frees a pack as any file)
        else
            file::PacRequestFree(ed.pfile);
        ed.pfile = 0;
    }
    if (ed.usershutdown != 0)
        guest::callOriginal(ed.usershutdown, process);
    if (ed.userdata != 0)
        mem::PoolRelease(ed.userdata);
    mem::PoolRelease(guest::addressOf(&ed));
}

// nbInitEventProcess @ 0x0028FFB0
void startEvent(MainProcessData& data)
{
    const uint32_t address = mem::PoolAllocate(sizeof(EventProcessData));
    EventProcessData& ed = *guest::table<EventProcessData>(address);
    ed = EventProcessData{};
    ed.data.address = guest::addressOf(&data);
    data.endtype = 0;
    data.stat |= kStatEvent;
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 1, 1, kRunEventStart, kShutdownEvent, address);
    dds3::LinkProcess(data.MainProcessID, process);
    data.EventProcessID = process;
}

} // namespace nocturne::nb

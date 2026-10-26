// A skill's effect and its cuts (original unit: effBTL): the frame queries
// and setters. Rewritten from the original instructions.
#include "nocturne/effect/cut.hpp"

#include <cstddef>

#include "nocturne/address.hpp"
#include "nocturne/battle/camera.hpp"
#include "nocturne/battle/process.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

static_assert(sizeof(BattleCut) == 0x20 && offsetof(BattleCut, description) == 0x1c);

namespace {

constexpr uint32_t kDescriptionSize = 0x618;   // cut 2's description follows cut 1's
constexpr uint32_t kSkillState = addr(0x00551d80);    // uint32 (gp-relative): effBTLSkillSetState's state
constexpr uint32_t kSkillInvoker = addr(0x005698e0);  // Formation*: the unit using the skill
constexpr uint32_t kCutCameraStates = addr(0x0031b8c0);   // uint16[3] by cut number

uint32_t word(uint32_t address) { return *guest::table<const uint32_t>(address); }

uint32_t description(uint32_t effect, uint16_t cutNo) { return effect + (cutNo < 2 ? 0 : kDescriptionSize); }

} // namespace

// effBTLGetMotionChangeFrame @ 0x0016AB70
uint32_t motionChangeFrame(uint32_t effect, uint16_t cutNo) { return word(description(effect, cutNo) + 0x50); }

// effBTLGetCutEndFrame @ 0x0016ABA0
uint32_t cutEndFrame(uint32_t effect, uint16_t cutNo) { return word(description(effect, cutNo) + 8); }

// effBTLCutGetMotionChangeFrame @ 0x0016AEC0 (the description's, which starts
// 8 bytes into the effect's)
uint32_t motionChangeFrame(const BattleCut& cut) { return word(cut.description + 0x48); }

// effBTLCutGetCutEndFrame @ 0x0016AEE8
uint32_t cutEndFrame(const BattleCut& cut) { return cut.cutEndFrame; }

// effBTLCutGetFrame @ 0x0016AEA0
uint32_t frame(const BattleCut& cut) { return cut.frame; }

// effBTLCutSetCutEndFrame @ 0x0016AED0
void setCutEndFrame(BattleCut& cut, uint32_t frame)
{
    cut.cutEndFrame = frame;
    if (cut.cutNo == 0)
        cut.drawEndFrame = frame;
}

// effBTLCutSetDrawEndFrame @ 0x0016AEF0 (tentative: HD has it and
// SetCutEndFrame, and this one writes the field Create fills from the
// description's draw length)
void setDrawEndFrame(BattleCut& cut, uint32_t frame)
{
    if (cut.cutNo == 1) {
        if (frame < cut.drawEndFrame)
            cut.drawEndFrame = frame;
    } else {
        cut.drawEndFrame = frame;
    }
}

// effBTLSystemCut1Draw @ 0x001740A0
void drawSystemCut(uint32_t cut) { BTLCutDraw(cut); }

// effBTLEncountStart @ 0x001741A0 (name as enc_process noted it, tentative)
void startEncounterEffect() { BTLSkillStart(0x200, 0); }

// effBTLCutSetCameraState @ 0x0016B090: not while the camera is held (0x1000).
void setCutCameraState(const BattleCut& cut)
{
    if (!(nb::GetMainProcessData()->stat & 0x1000) && cut.cutNo < 3)
        nb::setCameraState(guest::table<const uint16_t>(kCutCameraStates)[cut.cutNo]);
}

// effBTLSkillGetInvokeFormation @ 0x0016B940
nb::Formation& skillInvoker()
{
    if (const uint32_t invoker = *guest::table<const uint32_t>(kSkillInvoker))
        return *guest::table<nb::Formation>(invoker);
    nb::MainProcessData& main = *nb::GetMainProcessData();
    diag::print(diag::Message::NoInvoker);
    return *main.form;
}

// effBTLSkillSetState @ 0x0016BA40
void setSkillState(uint32_t state)
{
    *guest::table<uint32_t>(kSkillState) = state;
    diag::print(diag::Message::SkillState, state);
}

} // namespace nocturne::eff

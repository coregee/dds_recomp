// The battle's effect process (original unit: effBattle). Rewritten from the
// original instructions.
#include "nocturne/effect/battle_process.hpp"

#include "nocturne/address.hpp"
#include "nocturne/external.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::nb {

namespace {

constexpr uint32_t kProcessName = addr(0x00533058);   // "nb_effect"
constexpr uint32_t kDrawName = addr(0x00533068);      // "nb_effect_draw"
constexpr uint32_t kStep = addr(0x0016c4b8), kShutdown = addr(0x0016c500), kDraw = addr(0x0016c4e0);   // (no C here yet)

// What the start sets up (names from smt3-decomp; no C here yet).
constexpr uint32_t kSkillInit = addr(0x0016b770);          // effBTLSkillInit
constexpr uint32_t kFieldColorInit = addr(0x0016ba78);     // effBTLFieldColorInit
constexpr uint32_t kPointLightInit = addr(0x0016f490);     // effBTLPointLightInit
constexpr uint32_t kModelShowInit = addr(0x0016de10);      // effBTLModelShowInit
constexpr uint32_t kPartHandleCreate = addr(0x00174490);   // effBTLSystemPartHandleCreate

} // namespace

// nbInitEffectProcess @ 0x0016C528
void startEffectProcess(MainProcessData& main)
{
    const uint32_t process = dds3::StartProcess(kProcessName, 0x3f9, 2, 1, kStep, kShutdown, 0);
    dds3::LinkProcess(main.MainProcessID, process);
    main.EffectProcessID = process;
    dds3::LinkProcess(process, dds3::StartProcess(kDrawName, 0x2b0e, 1, 1, kDraw, 0, 0));
    for (const uint32_t init : {kSkillInit, kFieldColorInit, kPointLightInit, kModelShowInit, kPartHandleCreate})
        guest::callOriginal(init);
}

} // namespace nocturne::nb

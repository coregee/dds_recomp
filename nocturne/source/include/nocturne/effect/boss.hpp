// Boss effects (original unit: effPCPBoss), as far as rewritten: the
// lengths of Ongyo-Ki's effects. Creating and drawing them is the effect
// library's part (external.hpp).
//
// Names are the HD remaster's.
#pragma once

#include <cstdint>

namespace nocturne::eff {

// The effects' parameters (formations, as addresses).
struct PCPBossONGYParam {      // effPCPBossONGYParam_t: Ongyo-Ki leaves the field
    uint32_t pFormation;
};
struct PCPBossONGY2Param {     // effPCPBossONGY2Param_t: a clone leaves the field
    uint32_t pFormation;
};
struct PCPBossBUNSINParam {    // effPCPBossBUNSINParam_t: Ongyo-Ki splits off a clone
    uint32_t pStartForm, pEndForm;
};
struct PCPBossBUNSIN2Param {   // effPCPBossBUNSIN2Param_t: ... into three
    uint32_t pStartForm, pForm1, pForm2L, pForm2R;
};

// Their lengths in frames.
int32_t effPCPBossONGYGetLength();      // 22
int32_t effPCPBossONGY2GetLength();     // 27
int32_t effPCPBossBUNSINGetLength();    // 24
int32_t effPCPBossBUNSIN2GetLength();   // twice BUNSIN's

} // namespace nocturne::eff

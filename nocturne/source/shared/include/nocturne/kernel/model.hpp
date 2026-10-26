// Models (original unit: mdl*). Only what the rewrite calls so far.
#pragma once

#include <cstdint>

namespace nocturne::mdl {

// mdlGetMinorNum: a model's minor number (its data +0xA).
uint16_t GetMinorNum(uint32_t model);

} // namespace nocturne::mdl

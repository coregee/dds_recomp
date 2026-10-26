// Models (original unit: mdl*). Rewritten from the original instructions.
#include "nocturne/kernel/model.hpp"

#include "nocturne/guest.hpp"

namespace nocturne::mdl {

// mdlGetMinorNum @ 0x001DDB78
uint16_t GetMinorNum(uint32_t model)
{
    const uint32_t data = *guest::table<const uint32_t>(model + 0xc);
    return *guest::table<const uint16_t>(data + 0xa);
}

} // namespace nocturne::mdl

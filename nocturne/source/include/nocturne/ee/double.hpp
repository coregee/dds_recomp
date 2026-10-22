// Double precision as the game computes it.
//
// The EE has no double-precision hardware; the game's few double operations
// go through its software floating-point library (libgcc), whose rounding
// differs from IEEE hardware. ee::Double wraps those routines (recovered in
// legacy/src) so formulas keep the original results.
#pragma once

#include <cstdint>

#include "nocturne/ee/float.hpp"

extern "C" {
uint64_t ps2SoftDoubleFromFloat(float value);
float ps2SoftDoubleToFloat(uint64_t bits);
uint64_t ps2SoftDoubleFromInt(int32_t value);
int32_t ps2SoftDoubleToInt(uint64_t bits);
uint64_t ps2SoftDoubleMul(uint64_t left, uint64_t right);
uint64_t ps2SoftDoubleAdd(uint64_t left, uint64_t right);
int32_t ps2SoftDoubleCompare(uint64_t left, uint64_t right);
}

namespace nocturne::ee {

class Double {
public:
    static constexpr Double fromBits(uint64_t bits) { Double d; d.bits_ = bits; return d; }
    static Double fromFloat(Float value) { return fromBits(ps2SoftDoubleFromFloat(value.value())); }
    static Double fromInt(int32_t value) { return fromBits(ps2SoftDoubleFromInt(value)); }

    Float toFloat() const { return Float(ps2SoftDoubleToFloat(bits_)); }
    int32_t toInt() const { return ps2SoftDoubleToInt(bits_); }
    constexpr uint64_t bits() const { return bits_; }

    friend Double operator*(Double a, Double b) { return fromBits(ps2SoftDoubleMul(a.bits_, b.bits_)); }
    friend Double operator+(Double a, Double b) { return fromBits(ps2SoftDoubleAdd(a.bits_, b.bits_)); }
    // libgcc's comparison: negative, zero or positive (IEEE rules: denormals count, -0 == 0).
    friend int32_t compare(Double a, Double b) { return ps2SoftDoubleCompare(a.bits_, b.bits_); }

private:
    uint64_t bits_ = 0;
};

} // namespace nocturne::ee

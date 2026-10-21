// PS2 Emotion Engine single-precision float.
//
// The EE's COP1 unit is *not* IEEE-754: it has no NaN, infinity or denormals,
// and arithmetic rounds toward zero. Most game formulas end in a truncation to
// int (a percentage, a damage value), so a host `float` computing the same
// expression can land one unit away from what the PS2 produced.
//
// ee::Float lets formulas read like ordinary arithmetic while every operation
// is routed through the EE FPU primitives. Literal constants convert exactly
// (all constants the game uses are representable floats).
#pragma once

#include <bit>
#include <cstdint>

extern "C" {
uint32_t EE_FPU_CVT_S_W(uint32_t signed_word_bits);
uint32_t EE_FPU_CVT_W_S(uint32_t single_bits);
uint32_t EE_FPU_ADD_S(uint32_t left_bits, uint32_t right_bits);
uint32_t EE_FPU_SUB_S(uint32_t left_bits, uint32_t right_bits);
uint32_t EE_FPU_MUL_S(uint32_t left_bits, uint32_t right_bits);
uint32_t EE_FPU_DIV_S(uint32_t left_bits, uint32_t right_bits);
uint32_t EE_FPU_COMPARE_S(uint32_t left_bits, uint32_t right_bits, unsigned predicate);
}

namespace nocturne::ee {

class Float {
public:
    constexpr Float() = default;
    constexpr Float(float value) : bits_(std::bit_cast<uint32_t>(value)) {}

    static constexpr Float fromBits(uint32_t bits) { Float f; f.bits_ = bits; return f; }
    // CVT.S.W
    static Float fromInt(int32_t value) { return fromBits(EE_FPU_CVT_S_W(static_cast<uint32_t>(value))); }

    // CVT.W.S: truncates toward zero, saturating at the int32 range.
    int32_t toInt() const { return static_cast<int32_t>(EE_FPU_CVT_W_S(bits_)); }
    float value() const { return std::bit_cast<float>(bits_); }
    constexpr uint32_t bits() const { return bits_; }
    Float abs() const { return fromBits(bits_ & 0x7fffffffu); }

    friend Float operator+(Float a, Float b) { return fromBits(EE_FPU_ADD_S(a.bits_, b.bits_)); }
    friend Float operator-(Float a, Float b) { return fromBits(EE_FPU_SUB_S(a.bits_, b.bits_)); }
    friend Float operator*(Float a, Float b) { return fromBits(EE_FPU_MUL_S(a.bits_, b.bits_)); }
    friend Float operator/(Float a, Float b) { return fromBits(EE_FPU_DIV_S(a.bits_, b.bits_)); }
    Float& operator+=(Float o) { return *this = *this + o; }
    Float& operator-=(Float o) { return *this = *this - o; }
    Float& operator*=(Float o) { return *this = *this * o; }
    Float& operator/=(Float o) { return *this = *this / o; }

    // C.LT.S / C.LE.S
    friend bool operator<(Float a, Float b) { return EE_FPU_COMPARE_S(a.bits_, b.bits_, 1) != 0; }
    friend bool operator<=(Float a, Float b) { return EE_FPU_COMPARE_S(a.bits_, b.bits_, 2) != 0; }
    friend bool operator>(Float a, Float b) { return b < a; }
    friend bool operator>=(Float a, Float b) { return b <= a; }

private:
    uint32_t bits_ = 0;
};

static_assert(sizeof(Float) == 4);

// A float constant as the original toolchain stored it. Its compiler rounded
// decimal literals toward zero, so 0.6 is 0x3f199999 where a modern compiler
// gives 0x3f19999a. Use this for every non-exact constant from the game.
consteval Float literal(double value)
{
    float nearest = static_cast<float>(value);
    uint32_t bits = std::bit_cast<uint32_t>(nearest);
    double magnitude = value < 0 ? -value : value;
    double rounded = nearest < 0 ? -static_cast<double>(nearest) : static_cast<double>(nearest);
    if (rounded > magnitude)
        --bits;   // one step toward zero
    return Float::fromBits(bits);
}

static_assert(literal(0.6).bits() == 0x3f199999);
static_assert(literal(0.1).bits() == 0x3dcccccc);
static_assert(literal(0.01).bits() == 0x3c23d70a);
static_assert(literal(1.3).bits() == 0x3fa66666);

} // namespace nocturne::ee

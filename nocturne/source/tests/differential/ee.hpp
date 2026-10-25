// A small Emotion Engine interpreter: runs the original instructions of
// SLUS_209.11 (loaded into the fake RAM by fw_load_elf) so a rewrite can be
// compared with the game's own code where no legacy C exists.
//
// Integer instructions, LQ / SQ, the COP1 FPU and VU0 macro mode (with the
// EE's own float rules, through the same EE_FPU_* primitives as ee::Float),
// and the MMI packing instructions the game uses with VU0 (PPACH, PPACB). Registers follow the R5900's rules (32-bit results
// sign-extended, three-operand MULT, DIV by zero without a trap). Calls to hooked addresses run a host function instead (the shared
// fakes of fake_world.c); calls into `interpreted` ranges run the original
// callee; any other call is a test setup error.
#pragma once

#include <cstdint>
#include <functional>
#include <initializer_list>
#include <unordered_map>
#include <utility>
#include <vector>

#include "version_map.hpp"

namespace difftest::ee {

struct Cpu {
    uint64_t r[32]{};
    uint64_t upper[32]{};        // bits 64..127 (LQ / SQ only)
    uint64_t hi = 0, lo = 0;
    uint64_t hi1 = 0, lo1 = 0;   // the second multiply / divide pipeline (MULT1, DIV1 ...)
    uint32_t f[32]{};            // COP1 registers, as bits
    uint32_t acc = 0;            // COP1 accumulator
    bool fcc = false;            // COP1 condition
    uint32_t vf[32][4]{};        // VU0 registers in macro mode (lanes x y z w, as bits); vf0 is (0, 0, 0, 1)
    uint32_t vacc[4]{};          // VU0 ACC
    uint32_t q = 0;              // VU0 Q

    // Arguments of a hooked call: a0..a3, then t0..t3 (the EE ABI).
    uint64_t arg(int index) const { return r[index < 4 ? 4 + index : 8 + index - 4]; }
};

using Hook = std::function<uint64_t(Cpu&)>;

class Interpreter {
public:
    // Calls to these addresses run the host function; its result goes in v0.
    // Addresses are US Maniax's, mapped for another build (version_map.hpp):
    // a function the version doesn't have is left out.
    void hook(uint32_t address, Hook function)
    {
        if (const uint32_t at = version::code(address))
            hooks_[at] = std::move(function);
    }
    // A hook into US Maniax's legacy C, which reads US Maniax's addresses:
    // on another build the function's own instructions run instead.
    void hookUs(uint32_t address, Hook function)
    {
        if (!version::active())
            hook(address, std::move(function));
        else if (const uint32_t size = version::functionSize(address))
            interpret(address, address + size);
    }
    // Calls into [begin, end) run the original code.
    void interpret(uint32_t begin, uint32_t end)
    {
        const uint32_t from = version::codeBegin(begin), to = version::codeEnd(end);
        if (from && to > from)
            ranges_.push_back({from, to});
    }

    // Runs the function at `entry`; arguments after the eighth go on the stack,
    // float arguments in f12, f13... Returns v0 (a float result is in cpu.f[0]).
    // `ownEntry`: the entry's own instructions run even where a hook sits
    // there (a function whose callers the harness fakes, tested itself).
    uint64_t call(uint32_t entry, std::initializer_list<uint64_t> args = {}, std::initializer_list<uint32_t> floatArgs = {},
                  bool ownEntry = false);
    // Calls run so far, by any interpreter (a test's original side either runs
    // the executable's instructions or the legacy C).
    static uint64_t calls() { return calls_; }

    Cpu cpu;

private:
    bool interpreted(uint32_t address) const;
    void step();
    void vu0(uint32_t pc, uint32_t op);
    static void multiplyDivide(uint32_t funct, uint64_t s, uint64_t t, uint64_t* d, uint64_t& hi, uint64_t& lo);
    uint32_t vf(uint32_t reg, int lane) const;
    void setVf(uint32_t reg, int lane, uint32_t value);

    static inline uint64_t calls_ = 0;
    std::unordered_map<uint32_t, Hook> hooks_;
    std::vector<std::pair<uint32_t, uint32_t>> ranges_;
    uint32_t pc_ = 0, npc_ = 0;
};

} // namespace difftest::ee

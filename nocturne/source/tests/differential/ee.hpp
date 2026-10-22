// A small Emotion Engine interpreter: runs the original instructions of
// SLUS_209.11 (loaded into the fake RAM by fw_load_elf) so a rewrite can be
// compared with the game's own code where no legacy C exists.
//
// Integer instructions, LQ / SQ and the COP1 FPU (with the EE's own float
// rules, through the same EE_FPU_* primitives as ee::Float); no VU0 or MMI
// arithmetic. Registers follow the R5900's rules (32-bit results
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

namespace difftest::ee {

struct Cpu {
    uint64_t r[32]{};
    uint64_t upper[32]{};        // bits 64..127 (LQ / SQ only)
    uint64_t hi = 0, lo = 0;
    uint32_t f[32]{};            // COP1 registers, as bits
    uint32_t acc = 0;            // COP1 accumulator
    bool fcc = false;            // COP1 condition

    // Arguments of a hooked call: a0..a3, then t0..t3 (the EE ABI).
    uint64_t arg(int index) const { return r[index < 4 ? 4 + index : 8 + index - 4]; }
};

using Hook = std::function<uint64_t(Cpu&)>;

class Interpreter {
public:
    // Calls to these addresses run the host function; its result goes in v0.
    void hook(uint32_t address, Hook function) { hooks_[address] = std::move(function); }
    // Calls into [begin, end) run the original code.
    void interpret(uint32_t begin, uint32_t end) { ranges_.push_back({begin, end}); }

    // Runs the function at `entry`; arguments after the eighth go on the stack,
    // float arguments in f12, f13... Returns v0 (a float result is in cpu.f[0]).
    uint64_t call(uint32_t entry, std::initializer_list<uint64_t> args = {}, std::initializer_list<uint32_t> floatArgs = {});

    Cpu cpu;

private:
    bool interpreted(uint32_t address) const;
    void step();

    std::unordered_map<uint32_t, Hook> hooks_;
    std::vector<std::pair<uint32_t, uint32_t>> ranges_;
    uint32_t pc_ = 0, npc_ = 0;
};

} // namespace difftest::ee

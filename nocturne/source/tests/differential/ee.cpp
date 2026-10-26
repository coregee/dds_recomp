#include "ee.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "fake_world.h"

extern "C" {
uint32_t EE_FPU_CVT_S_W(uint32_t);
uint32_t EE_FPU_CVT_W_S(uint32_t);
uint32_t EE_FPU_ADD_S(uint32_t, uint32_t);
uint32_t EE_FPU_SUB_S(uint32_t, uint32_t);
uint32_t EE_FPU_MUL_S(uint32_t, uint32_t);
uint32_t EE_FPU_DIV_S(uint32_t, uint32_t);
uint32_t EE_FPU_RSQRT_S(uint32_t, uint32_t);
uint32_t EE_FPU_COMPARE_S(uint32_t, uint32_t, unsigned);
}

namespace difftest::ee {

namespace {

constexpr uint32_t kReturn = 0xfffffff0u;          // ra of the outermost call

[[noreturn]] void fail(const char* what, uint32_t pc, uint32_t op)
{
    std::fprintf(stderr, "ee: %s at %08x (%08x)\n", what, pc, op);
    std::abort();
}

uint64_t sx32(uint64_t v) { return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(v))); }
int64_t s64(uint64_t v) { return static_cast<int64_t>(v); }

uint32_t current_pc;   // for the message when an access leaves guest RAM

void* resolve(uint32_t address, uint32_t bytes)
{
    if (address >= FW_RAM_SIZE || FW_RAM_SIZE - address < bytes)
        fail("access outside guest RAM", current_pc, address);
    return fw_resolve(address);
}

template <class T> T load(uint32_t address)
{
    T value;
    std::memcpy(&value, resolve(address, sizeof value), sizeof value);
    return value;
}

template <class T> void store(uint32_t address, T value) { std::memcpy(resolve(address, sizeof value), &value, sizeof value); }

} // namespace

bool Interpreter::interpreted(uint32_t address) const
{
    for (const auto& [begin, end] : ranges_)
        if (address >= begin && address < end)
            return true;
    return false;
}

uint64_t Interpreter::call(uint32_t entry, std::initializer_list<uint64_t> args, std::initializer_list<uint32_t> floatArgs,
                          const std::vector<uint32_t>& own)
{
    ++calls_;
    cpu = Cpu{};
    for (const auto& [reg, lanes] : presetVf_)
        for (int k = 0; k < 4; ++k)
            cpu.vf[reg][k] = lanes[k];
    presetVf_.clear();
    int f = 12;
    for (uint32_t bits : floatArgs)
        cpu.f[f++] = bits;
    int i = 0;
    for (uint64_t a : args) {
        if (i < 8)
            cpu.r[i < 4 ? 4 + i : 8 + i - 4] = a;
        else   // the rest on the stack, in 8-byte slots from sp
            store<uint64_t>(fw_stack_top() + 8u * static_cast<uint32_t>(i - 8), a);
        ++i;
    }
    cpu.r[28] = version::globalPointer();
    cpu.r[29] = fw_stack_top();
    cpu.r[31] = kReturn;
    pc_ = entry;
    npc_ = entry + 4;
    uint64_t steps = 0;
    while (pc_ != kReturn) {
        if (++steps > 100000000)
            fail("more than 100 million instructions", pc_, 0);
        auto hooked = hooks_.find(pc_);
        if (hooked != hooks_.end() && std::find(own.begin(), own.end(), pc_) == own.end()) {
            cpu.r[2] = hooked->second(cpu);
            pc_ = static_cast<uint32_t>(cpu.r[31]);
            npc_ = pc_ + 4;
            continue;
        }
        if (!interpreted(pc_)) {
            // Another build: a function the harness doesn't map yet fails
            // the case (trap 99), naming it once, instead of the run.
            if (version::active()) {
                static std::unordered_map<uint32_t, bool> reported;
                if (!reported[pc_]) {
                    reported[pc_] = true;
                    std::fprintf(stderr, "ee: call outside the interpreted code at %08x (US Maniax %08x)\n", pc_,
                                 version::maniax(pc_));
                }
                fw_trap(99);
            }
            fail("call outside the interpreted code", pc_, 0);
        }
        step();
    }
    return cpu.r[2];
}

// MULT, MULTU (three-operand: also into rd), DIV, DIVU on one pipeline's HI / LO.
void Interpreter::multiplyDivide(uint32_t funct, uint64_t s, uint64_t t, uint64_t* d, uint64_t& hi, uint64_t& lo)
{
    switch (funct) {
    case 0x18: {                                                                // MULT
        const int64_t p = static_cast<int64_t>(static_cast<int32_t>(s)) * static_cast<int32_t>(t);
        lo = sx32(static_cast<uint64_t>(p));
        hi = sx32(static_cast<uint64_t>(p) >> 32);
        if (d) *d = lo;
        break;
    }
    case 0x19: {                                                                // MULTU
        const uint64_t p = static_cast<uint64_t>(static_cast<uint32_t>(s)) * static_cast<uint32_t>(t);
        lo = sx32(p);
        hi = sx32(p >> 32);
        if (d) *d = lo;
        break;
    }
    case 0x1a: {                                                                // DIV
        const int32_t a = static_cast<int32_t>(s), b = static_cast<int32_t>(t);
        if (b == 0) { lo = a < 0 ? 1 : ~0ull; hi = sx32(static_cast<uint32_t>(a)); }
        else if (a == INT32_MIN && b == -1) { lo = sx32(static_cast<uint32_t>(a)); hi = 0; }
        else { lo = sx32(static_cast<uint32_t>(a / b)); hi = sx32(static_cast<uint32_t>(a % b)); }
        break;
    }
    default: {                                                                  // DIVU
        const uint32_t a = static_cast<uint32_t>(s), b = static_cast<uint32_t>(t);
        if (b == 0) { lo = ~0ull; hi = sx32(a); }
        else { lo = sx32(a / b); hi = sx32(a % b); }
        break;
    }
    }
}

uint32_t Interpreter::vf(uint32_t reg, int lane) const
{
    static const uint32_t zero[4] = {0, 0, 0, 0x3f800000};
    return reg ? cpu.vf[reg][lane] : zero[lane];
}

void Interpreter::setVf(uint32_t reg, int lane, uint32_t value)
{
    if (reg)
        cpu.vf[reg][lane] = value;
}

// A VU0 macro instruction (COP2 with bit 25 set): the arithmetic, ACC and
// conversion instructions, lane by lane on the destination mask; flags, the
// I register and the square roots are not modelled.
void Interpreter::vu0(uint32_t pc, uint32_t op)
{
    const uint32_t dest = op >> 21 & 15, ft = op >> 16 & 31, fs = op >> 11 & 31, fd = op >> 6 & 31;
    const int bc = static_cast<int>(op & 3);
    auto lanes = [&](auto f) {
        for (int i = 0; i < 4; ++i)
            if (dest >> (3 - i) & 1)
                f(i);
    };
    using Op = uint32_t (*)(uint32_t, uint32_t);
    const Op add = [](uint32_t a, uint32_t b) { return EE_FPU_ADD_S(a, b); };
    const Op sub = [](uint32_t a, uint32_t b) { return EE_FPU_SUB_S(a, b); };
    const Op mul = [](uint32_t a, uint32_t b) { return EE_FPU_MUL_S(a, b); };
    auto mulAdd = [](bool subtract, uint32_t acc, uint32_t a, uint32_t b) {
        return subtract ? EE_FPU_SUB_S(acc, EE_FPU_MUL_S(a, b)) : EE_FPU_ADD_S(acc, EE_FPU_MUL_S(a, b));
    };
    // The second operand: one lane of ft broadcast, Q, or ft's same lane.
    enum Source { kBroadcast, kQ, kLane };
    auto operand = [&](Source source, int lane) { return source == kBroadcast ? vf(ft, bc) : source == kQ ? cpu.q : vf(ft, lane); };
    auto toFd = [&](Op f, Source source) {
        uint32_t out[4] = {};
        lanes([&](int i) { out[i] = f(vf(fs, i), operand(source, i)); });
        lanes([&](int i) { setVf(fd, i, out[i]); });
    };
    auto toAcc = [&](Op f, Source source) { lanes([&](int i) { cpu.vacc[i] = f(vf(fs, i), operand(source, i)); }); };
    auto maddFd = [&](bool subtract, Source source) {
        uint32_t out[4] = {};
        lanes([&](int i) { out[i] = mulAdd(subtract, cpu.vacc[i], vf(fs, i), operand(source, i)); });
        lanes([&](int i) { setVf(fd, i, out[i]); });
    };
    auto maddAcc = [&](bool subtract, Source source) {
        lanes([&](int i) { cpu.vacc[i] = mulAdd(subtract, cpu.vacc[i], vf(fs, i), operand(source, i)); });
    };
    // The outer product's operands: (fs.y, fs.z, fs.x) and (ft.z, ft.x, ft.y).
    auto cross = [&](int i, bool left) { return left ? vf(fs, (i + 1) % 3) : vf(ft, (i + 2) % 3); };
    const uint32_t funct = op & 63;
    if (funct < 0x3c) {
        switch (funct) {
        case 0x00: case 0x01: case 0x02: case 0x03: toFd(add, kBroadcast); return;    // VADDbc
        case 0x04: case 0x05: case 0x06: case 0x07: toFd(sub, kBroadcast); return;    // VSUBbc
        case 0x08: case 0x09: case 0x0a: case 0x0b: maddFd(false, kBroadcast); return; // VMADDbc
        case 0x0c: case 0x0d: case 0x0e: case 0x0f: maddFd(true, kBroadcast); return;  // VMSUBbc
        case 0x18: case 0x19: case 0x1a: case 0x1b: toFd(mul, kBroadcast); return;    // VMULbc
        case 0x1c: toFd(mul, kQ); return;                                              // VMULq
        case 0x20: toFd(add, kQ); return;                                              // VADDq
        case 0x21: maddFd(false, kQ); return;                                          // VMADDq
        case 0x24: toFd(sub, kQ); return;                                              // VSUBq
        case 0x25: maddFd(true, kQ); return;                                           // VMSUBq
        case 0x28: toFd(add, kLane); return;                                           // VADD
        case 0x29: maddFd(false, kLane); return;                                       // VMADD
        case 0x2a: toFd(mul, kLane); return;                                           // VMUL
        case 0x2c: toFd(sub, kLane); return;                                           // VSUB
        case 0x2d: maddFd(true, kLane); return;                                        // VMSUB
        case 0x2e: {                                                                   // VOPMSUB: ACC - fs x ft
            uint32_t out[3];
            for (int i = 0; i < 3; ++i)
                out[i] = mulAdd(true, cpu.vacc[i], cross(i, true), cross(i, false));
            for (int i = 0; i < 3; ++i)
                if (dest >> (3 - i) & 1)
                    setVf(fd, i, out[i]);
            return;
        }
        default: fail("unsupported VU0 instruction", pc, op);
        }
    }
    switch ((op >> 6 & 31) << 2 | (funct & 3)) {
    case 0x00: case 0x01: case 0x02: case 0x03: toAcc(add, kBroadcast); return;       // VADDAbc
    case 0x04: case 0x05: case 0x06: case 0x07: toAcc(sub, kBroadcast); return;       // VSUBAbc
    case 0x08: case 0x09: case 0x0a: case 0x0b: maddAcc(false, kBroadcast); return;   // VMADDAbc
    case 0x0c: case 0x0d: case 0x0e: case 0x0f: maddAcc(true, kBroadcast); return;    // VMSUBAbc
    case 0x10: case 0x11: case 0x12: case 0x13: {                                      // VITOF0/4/12/15
        static const uint32_t scale[4] = {0x3f800000, 0x3d800000, 0x39800000, 0x38000000};   // 1, 1/16, 1/4096, 1/32768
        lanes([&](int i) {
            const uint32_t v = EE_FPU_CVT_S_W(vf(fs, i));
            setVf(ft, i, (funct & 3) ? EE_FPU_MUL_S(v, scale[funct & 3]) : v);
        });
        return;
    }
    case 0x14: case 0x15: case 0x16: case 0x17: {                                      // VFTOI0/4/12/15
        static const uint32_t scale[4] = {0x3f800000, 0x41800000, 0x45800000, 0x47000000};   // 1, 16, 4096, 32768
        lanes([&](int i) {
            const uint32_t v = vf(fs, i);
            setVf(ft, i, EE_FPU_CVT_W_S((funct & 3) ? EE_FPU_MUL_S(v, scale[funct & 3]) : v));
        });
        return;
    }
    case 0x18: case 0x19: case 0x1a: case 0x1b: toAcc(mul, kBroadcast); return;       // VMULAbc
    case 0x1c: toAcc(mul, kQ); return;                                                 // VMULAq
    case 0x1d: lanes([&](int i) { setVf(ft, i, vf(fs, i) & 0x7fffffffu); }); return;   // VABS
    case 0x20: toAcc(add, kQ); return;                                                 // VADDAq
    case 0x21: maddAcc(false, kQ); return;                                             // VMADDAq
    case 0x24: toAcc(sub, kQ); return;                                                 // VSUBAq
    case 0x25: maddAcc(true, kQ); return;                                              // VMSUBAq
    case 0x28: toAcc(add, kLane); return;                                              // VADDA
    case 0x29: maddAcc(false, kLane); return;                                          // VMADDA
    case 0x2a: toAcc(mul, kLane); return;                                              // VMULA
    case 0x2c: toAcc(sub, kLane); return;                                              // VSUBA
    case 0x2d: maddAcc(true, kLane); return;                                           // VMSUBA
    case 0x2e:                                                                         // VOPMULA: fs x ft
        for (int i = 0; i < 3; ++i)
            if (dest >> (3 - i) & 1)
                cpu.vacc[i] = mul(cross(i, true), cross(i, false));
        return;
    case 0x2f: return;                                                                 // VNOP
    case 0x30: lanes([&](int i) { setVf(ft, i, vf(fs, i)); }); return;                // VMOVE
    case 0x31: {                                                                       // VMR32: lanes rotated
        uint32_t out[4] = {};
        lanes([&](int i) { out[i] = vf(fs, (i + 1) & 3); });
        lanes([&](int i) { setVf(ft, i, out[i]); });
        return;
    }
    case 0x38:                                                                         // VDIV: Q = fs.fsf / ft.ftf
        cpu.q = EE_FPU_DIV_S(vf(fs, static_cast<int>(op >> 21 & 3)), vf(ft, static_cast<int>(op >> 23 & 3)));
        return;
    case 0x3a:                                                                         // VRSQRT: Q = fs.fsf / sqrt(ft.ftf)
        cpu.q = EE_FPU_RSQRT_S(vf(fs, static_cast<int>(op >> 21 & 3)), vf(ft, static_cast<int>(op >> 23 & 3)));
        return;
    case 0x3b: return;                                                                 // VWAITQ
    default: fail("unsupported VU0 instruction", pc, op);
    }
}

void Interpreter::step()
{
    const uint32_t pc = pc_;
    current_pc = pc;
    const uint32_t op = load<uint32_t>(pc);
#pragma warning(suppress : 4996)
    static const bool trace = std::getenv("EE_TRACE") != nullptr;
    if (trace)
        std::fprintf(stderr, "%08x %08x  a0=%llx a1=%llx a2=%llx a3=%llx v0=%llx v1=%llx sp=%llx\n", pc, op,
                     (unsigned long long)cpu.r[4], (unsigned long long)cpu.r[5], (unsigned long long)cpu.r[6],
                     (unsigned long long)cpu.r[7], (unsigned long long)cpu.r[2], (unsigned long long)cpu.r[3],
                     (unsigned long long)cpu.r[29]);
    uint32_t next = npc_;
    npc_ += 4;

    const uint32_t rs = op >> 21 & 31, rt = op >> 16 & 31, rd = op >> 11 & 31, sa = op >> 6 & 31;
    const uint64_t s = cpu.r[rs], t = cpu.r[rt];
    const int64_t simm = static_cast<int16_t>(op & 0xffff);
    const uint64_t zimm = op & 0xffff;
    const uint32_t address = static_cast<uint32_t>(s + static_cast<uint64_t>(simm));
    const uint32_t target = (pc & 0xf0000000u) | (op & 0x03ffffffu) << 2;
    const uint32_t branch = pc + 4 + static_cast<uint32_t>(simm << 2);
    uint64_t* const d = rd ? &cpu.r[rd] : nullptr;
    uint64_t* const dt = rt ? &cpu.r[rt] : nullptr;
    bool skipDelaySlot = false;

    auto take = [&](bool condition) { if (condition) npc_ = branch; };
    auto likely = [&](bool condition) { if (condition) npc_ = branch; else skipDelaySlot = true; };
    auto setD = [&](uint64_t v) { if (d) *d = v; };
    auto setT = [&](uint64_t v) { if (dt) *dt = v; };

    switch (op >> 26) {
    case 0x00:   // SPECIAL
        switch (op & 63) {
        case 0x00: setD(sx32(static_cast<uint32_t>(t) << sa)); break;                       // SLL
        case 0x02: setD(sx32(static_cast<uint32_t>(t) >> sa)); break;                       // SRL
        case 0x03: setD(sx32(static_cast<uint32_t>(static_cast<int32_t>(t) >> sa))); break; // SRA
        case 0x04: setD(sx32(static_cast<uint32_t>(t) << (s & 31))); break;                 // SLLV
        case 0x06: setD(sx32(static_cast<uint32_t>(t) >> (s & 31))); break;                 // SRLV
        case 0x07: setD(sx32(static_cast<uint32_t>(static_cast<int32_t>(t) >> (s & 31)))); break;
        case 0x08: npc_ = static_cast<uint32_t>(s); break;                                  // JR
        case 0x09: setD(pc + 8); npc_ = static_cast<uint32_t>(s); break;                    // JALR
        case 0x0a: if (t == 0) setD(s); break;                                              // MOVZ
        case 0x0b: if (t != 0) setD(s); break;                                              // MOVN
        case 0x0d: {                                                                        // BREAK
            // The code is in bits 16..25 (break 7, 0) or 6..15 (break 7).
            const uint32_t code = op >> 6 & 0xfffff;
            fw_trap(code > 0x3ff ? code >> 10 : code);
        }
        case 0x0f: break;                                                                   // SYNC
        case 0x10: setD(cpu.hi); break;
        case 0x11: cpu.hi = s; break;
        case 0x12: setD(cpu.lo); break;
        case 0x13: cpu.lo = s; break;
        case 0x14: setD(t << (s & 63)); break;                                              // DSLLV
        case 0x16: setD(t >> (s & 63)); break;                                              // DSRLV
        case 0x17: setD(static_cast<uint64_t>(s64(t) >> (s & 63))); break;                  // DSRAV
        case 0x18: case 0x19: case 0x1a: case 0x1b:                                         // MULT(U), DIV(U)
            multiplyDivide(op & 63, s, t, d, cpu.hi, cpu.lo);
            break;
        case 0x20: case 0x21: setD(sx32(s + t)); break;                                     // ADD(U)
        case 0x22: case 0x23: setD(sx32(s - t)); break;                                     // SUB(U)
        case 0x24: setD(s & t); break;
        case 0x25: setD(s | t); break;
        case 0x26: setD(s ^ t); break;
        case 0x27: setD(~(s | t)); break;
        case 0x2a: setD(s64(s) < s64(t)); break;                                            // SLT
        case 0x2b: setD(s < t); break;                                                      // SLTU
        case 0x2c: case 0x2d: setD(s + t); break;                                           // DADD(U)
        case 0x2e: case 0x2f: setD(s - t); break;                                           // DSUB(U)
        case 0x38: setD(t << sa); break;                                                    // DSLL
        case 0x3a: setD(t >> sa); break;                                                    // DSRL
        case 0x3b: setD(static_cast<uint64_t>(s64(t) >> sa)); break;                        // DSRA
        case 0x3c: setD(t << (sa + 32)); break;                                             // DSLL32
        case 0x3e: setD(t >> (sa + 32)); break;                                             // DSRL32
        case 0x3f: setD(static_cast<uint64_t>(s64(t) >> (sa + 32))); break;                 // DSRA32
        default: fail("unsupported SPECIAL instruction", pc, op);
        }
        break;
    case 0x01:   // REGIMM
        switch (rt) {
        case 0x00: take(s64(s) < 0); break;                       // BLTZ
        case 0x01: take(s64(s) >= 0); break;                      // BGEZ
        case 0x02: likely(s64(s) < 0); break;                     // BLTZL
        case 0x03: likely(s64(s) >= 0); break;                    // BGEZL
        case 0x10: cpu.r[31] = pc + 8; take(s64(s) < 0); break;   // BLTZAL
        case 0x11: cpu.r[31] = pc + 8; take(s64(s) >= 0); break;  // BGEZAL
        default: fail("unsupported REGIMM instruction", pc, op);
        }
        break;
    case 0x02: npc_ = target; break;                              // J
    case 0x03: cpu.r[31] = pc + 8; npc_ = target; break;          // JAL
    case 0x04: take(s == t); break;
    case 0x05: take(s != t); break;
    case 0x06: take(s64(s) <= 0); break;
    case 0x07: take(s64(s) > 0); break;
    case 0x08: case 0x09: setT(sx32(s + static_cast<uint64_t>(simm))); break;   // ADDI(U)
    case 0x0a: setT(s64(s) < simm); break;                                      // SLTI
    case 0x0b: setT(s < static_cast<uint64_t>(simm)); break;                    // SLTIU
    case 0x0c: setT(s & zimm); break;
    case 0x0d: setT(s | zimm); break;
    case 0x0e: setT(s ^ zimm); break;
    case 0x0f: setT(sx32(zimm << 16)); break;                                   // LUI
    case 0x14: likely(s == t); break;
    case 0x15: likely(s != t); break;
    case 0x16: likely(s64(s) <= 0); break;
    case 0x17: likely(s64(s) > 0); break;
    case 0x18: case 0x19: setT(s + static_cast<uint64_t>(simm)); break;         // DADDI(U)
    case 0x20: setT(static_cast<uint64_t>(static_cast<int64_t>(load<int8_t>(address)))); break;
    case 0x21: setT(static_cast<uint64_t>(static_cast<int64_t>(load<int16_t>(address)))); break;
    case 0x23: setT(sx32(load<uint32_t>(address))); break;
    case 0x24: setT(load<uint8_t>(address)); break;
    case 0x25: setT(load<uint16_t>(address)); break;
    case 0x27: setT(load<uint32_t>(address)); break;                            // LWU
    case 0x28: store<uint8_t>(address, static_cast<uint8_t>(t)); break;
    case 0x29: store<uint16_t>(address, static_cast<uint16_t>(t)); break;
    case 0x2b: store<uint32_t>(address, static_cast<uint32_t>(t)); break;
    case 0x2f: break;                                                           // CACHE
    case 0x33: break;                                                           // PREF
    case 0x37: setT(load<uint64_t>(address)); break;                            // LD
    case 0x3f: store<uint64_t>(address, t); break;                              // SD

    // Unaligned loads and stores (little-endian), as PCSX2 implements them.
    case 0x22: {                                                                // LWL
        const uint32_t shift = address & 3, mem = load<uint32_t>(address & ~3u);
        static const uint32_t mask[4] = {0x00ffffff, 0x0000ffff, 0x000000ff, 0};
        setT(sx32((static_cast<uint32_t>(t) & mask[shift]) | mem << (24 - 8 * shift)));
        break;
    }
    case 0x26: {                                                                // LWR
        const uint32_t shift = address & 3, mem = load<uint32_t>(address & ~3u);
        static const uint32_t mask[4] = {0, 0xff000000, 0xffff0000, 0xffffff00};
        if (shift == 0)
            setT(sx32(mem));
        else
            setT((t & 0xffffffff00000000ull) | ((static_cast<uint32_t>(t) & mask[shift]) | mem >> (8 * shift)));
        break;
    }
    case 0x2a: {                                                                // SWL
        const uint32_t shift = address & 3, mem = load<uint32_t>(address & ~3u);
        static const uint32_t mask[4] = {0xffffff00, 0xffff0000, 0xff000000, 0};
        store<uint32_t>(address & ~3u, static_cast<uint32_t>(t) >> (24 - 8 * shift) | (mem & mask[shift]));
        break;
    }
    case 0x2e: {                                                                // SWR
        const uint32_t shift = address & 3, mem = load<uint32_t>(address & ~3u);
        static const uint32_t mask[4] = {0, 0xff, 0xffff, 0xffffff};
        store<uint32_t>(address & ~3u, static_cast<uint32_t>(t) << (8 * shift) | (mem & mask[shift]));
        break;
    }
    case 0x1a: {                                                                // LDL
        const uint32_t shift = address & 7;
        const uint64_t mem = load<uint64_t>(address & ~7u);
        const uint64_t mask = shift == 7 ? 0 : 0x00ffffffffffffffull >> (8 * shift);
        setT((t & mask) | mem << (56 - 8 * shift));
        break;
    }
    case 0x1b: {                                                                // LDR
        const uint32_t shift = address & 7;
        const uint64_t mem = load<uint64_t>(address & ~7u);
        const uint64_t mask = shift == 0 ? 0 : ~0ull << (64 - 8 * shift);
        setT((t & mask) | mem >> (8 * shift));
        break;
    }
    case 0x2c: {                                                                // SDL
        const uint32_t shift = address & 7;
        const uint64_t mem = load<uint64_t>(address & ~7u);
        const uint64_t mask = shift == 7 ? 0 : ~0ull << (8 * (shift + 1));
        store<uint64_t>(address & ~7u, t >> (56 - 8 * shift) | (mem & mask));
        break;
    }
    case 0x2d: {                                                                // SDR
        const uint32_t shift = address & 7;
        const uint64_t mem = load<uint64_t>(address & ~7u);
        const uint64_t mask = shift == 0 ? 0 : ~0ull >> (64 - 8 * shift);
        store<uint64_t>(address & ~7u, t << (8 * shift) | (mem & mask));
        break;
    }
    case 0x1e:                                                                  // LQ
        if (rt) {
            cpu.r[rt] = load<uint64_t>(address & ~15u);
            cpu.upper[rt] = load<uint64_t>((address & ~15u) + 8);
        }
        break;
    case 0x1f:                                                                  // SQ
        store<uint64_t>(address & ~15u, t);
        store<uint64_t>((address & ~15u) + 8, rt ? cpu.upper[rt] : 0);
        break;

    // COP1: single precision with the EE's rules.
    case 0x31: cpu.f[rt] = load<uint32_t>(address); break;                     // LWC1
    case 0x39: store<uint32_t>(address, cpu.f[rt]); break;                     // SWC1
    case 0x11: {
        const uint32_t ft = rt, fs = rd, fd = sa;
        switch (rs) {
        case 0x00: setT(sx32(cpu.f[fs])); break;                               // MFC1
        case 0x04: cpu.f[fs] = static_cast<uint32_t>(t); break;                // MTC1
        case 0x02: setT(fs == 31 ? (cpu.fcc ? 0x00800000u : 0u) : 0u); break;  // CFC1
        case 0x06: if (fs == 31) cpu.fcc = (t & 0x00800000) != 0; break;      // CTC1
        case 0x08:                                                              // BC1F/T(L)
            switch (rt) {
            case 0: take(!cpu.fcc); break;
            case 1: take(cpu.fcc); break;
            case 2: likely(!cpu.fcc); break;
            case 3: likely(cpu.fcc); break;
            default: fail("unsupported BC1", pc, op);
            }
            break;
        case 0x10: {                                                            // S format
            const uint32_t a = cpu.f[fs], b = cpu.f[ft];
            switch (op & 63) {
            case 0x00: cpu.f[fd] = EE_FPU_ADD_S(a, b); break;
            case 0x01: cpu.f[fd] = EE_FPU_SUB_S(a, b); break;
            case 0x02: cpu.f[fd] = EE_FPU_MUL_S(a, b); break;
            case 0x03: cpu.f[fd] = EE_FPU_DIV_S(a, b); break;
            case 0x05: cpu.f[fd] = a & 0x7fffffffu; break;                     // ABS
            case 0x06: cpu.f[fd] = a; break;                                    // MOV
            case 0x07: cpu.f[fd] = a ^ 0x80000000u; break;                     // NEG
            case 0x24: cpu.f[fd] = EE_FPU_CVT_W_S(a); break;                    // CVT.W.S
            case 0x28: cpu.f[fd] = EE_FPU_COMPARE_S(a, b, 1) ? b : a; break;    // MAX
            case 0x29: cpu.f[fd] = EE_FPU_COMPARE_S(a, b, 1) ? a : b; break;    // MIN
            case 0x30: cpu.fcc = false; break;                                  // C.F
            case 0x32: cpu.fcc = EE_FPU_COMPARE_S(a, b, 0) != 0; break;         // C.EQ
            case 0x34: cpu.fcc = EE_FPU_COMPARE_S(a, b, 1) != 0; break;         // C.LT
            case 0x36: cpu.fcc = EE_FPU_COMPARE_S(a, b, 2) != 0; break;         // C.LE
            default: fail("unsupported COP1.S instruction", pc, op);
            }
            break;
        }
        case 0x14:                                                              // W format
            if ((op & 63) == 0x20) { cpu.f[fd] = EE_FPU_CVT_S_W(cpu.f[fs]); break; }
            fail("unsupported COP1.W instruction", pc, op);
        default: fail("unsupported COP1 instruction", pc, op);
        }
        break;
    }
    // COP2: VU0 in macro mode.
    case 0x36:                                                                  // LQC2
        for (int i = 0; i < 4; ++i)
            setVf(rt, i, load<uint32_t>((address & ~15u) + 4u * static_cast<uint32_t>(i)));
        break;
    case 0x3e:                                                                  // SQC2
        for (int i = 0; i < 4; ++i)
            store<uint32_t>((address & ~15u) + 4u * static_cast<uint32_t>(i), vf(rt, i));
        break;
    case 0x12:
        if (rs & 0x10) {
            vu0(pc, op);
            break;
        }
        switch (rs) {
        case 0x01:                                                              // QMFC2
            setT(static_cast<uint64_t>(vf(rd, 1)) << 32 | vf(rd, 0));
            if (rt)
                cpu.upper[rt] = static_cast<uint64_t>(vf(rd, 3)) << 32 | vf(rd, 2);
            break;
        case 0x05:                                                              // QMTC2
            setVf(rd, 0, static_cast<uint32_t>(t));
            setVf(rd, 1, static_cast<uint32_t>(t >> 32));
            setVf(rd, 2, rt ? static_cast<uint32_t>(cpu.upper[rt]) : 0);
            setVf(rd, 3, rt ? static_cast<uint32_t>(cpu.upper[rt] >> 32) : 0);
            break;
        default: fail("unsupported COP2 transfer", pc, op);
        }
        break;

    // MMI: the second multiply pipeline and the packing instructions.
    case 0x1c:
        switch (op & 63) {
        case 0x10: setD(cpu.hi1); goto done;                                    // MFHI1
        case 0x11: cpu.hi1 = s; goto done;                                      // MTHI1
        case 0x12: setD(cpu.lo1); goto done;                                    // MFLO1
        case 0x13: cpu.lo1 = s; goto done;                                      // MTLO1
        case 0x18: case 0x19: case 0x1a: case 0x1b:                             // MULT1, MULTU1, DIV1, DIVU1
            multiplyDivide(op & 63, s, t, d, cpu.hi1, cpu.lo1);
            goto done;
        case 0x00: case 0x01: case 0x20: case 0x21: {                           // MADD, MADDU, MADD1, MADDU1
            // HI:LO (32 bits each) plus the 32 x 32-bit product; rd gets the new LO.
            uint64_t& hi = (op & 0x20) ? cpu.hi1 : cpu.hi;
            uint64_t& lo = (op & 0x20) ? cpu.lo1 : cpu.lo;
            const uint64_t acc = static_cast<uint64_t>(static_cast<uint32_t>(hi)) << 32 | static_cast<uint32_t>(lo);
            const uint64_t product = (op & 1) ? static_cast<uint64_t>(static_cast<uint32_t>(s)) * static_cast<uint32_t>(t)
                                              : static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(s)) *
                                                                      static_cast<int32_t>(t));
            const uint64_t sum = acc + product;
            lo = sx32(sum & 0xffffffffu);
            hi = sx32(sum >> 32);
            if (d)
                *d = lo;
            goto done;
        }
        default: break;
        }
        if ((op & 63) == 0x08 && (sa == 0x17 || sa == 0x1b)) {
            const uint64_t low[2] = {t, rt ? cpu.upper[rt] : 0}, high[2] = {s, rs ? cpu.upper[rs] : 0};
            auto pack = [&](const uint64_t (&v)[2]) {
                uint64_t out = 0;
                if (sa == 0x17) {   // PPACH: the even halfwords
                    for (int i = 0; i < 4; ++i)
                        out |= (v[i / 2] >> (32 * (i % 2)) & 0xffff) << (16 * i);
                } else {            // PPACB: the even bytes
                    for (int i = 0; i < 8; ++i)
                        out |= (v[i / 4] >> (16 * (i % 4)) & 0xff) << (8 * i);
                }
                return out;
            };
            if (rd) {
                const uint64_t lo = pack(low), hi = pack(high);
                cpu.r[rd] = lo;
                cpu.upper[rd] = hi;
            }
            break;
        }
        if ((op & 63) == 0x08 && (sa == 0x16 || sa == 0x1a)) {
            // PEXTLH / PEXTLB: the low halves of rt and rs interleaved, rt's
            // element first (halfwords for PEXTLH, bytes for PEXTLB).
            const int bits = sa == 0x16 ? 16 : 8, count = 64 / bits;
            const uint64_t mask = (uint64_t{1} << bits) - 1;
            uint64_t out[2] = {0, 0};
            for (int i = 0; i < count; ++i) {
                const int k = 2 * i;   // the result's element for rt's; rs's is k + 1
                const uint64_t from[2] = {t >> (bits * i) & mask, s >> (bits * i) & mask};
                for (int j = 0; j < 2; ++j) {
                    const int e = k + j;
                    out[e / count] |= from[j] << (bits * (e % count));
                }
            }
            if (rd) {
                cpu.r[rd] = out[0];
                cpu.upper[rd] = out[1];
            }
            break;
        }
        if ((op & 63) == 0x09 && (sa == 0x1e || sa == 0x1f)) {                  // PEXEW, PROT3W
            const uint32_t w[4] = {static_cast<uint32_t>(t), static_cast<uint32_t>(t >> 32),
                                   rt ? static_cast<uint32_t>(cpu.upper[rt]) : 0u, rt ? static_cast<uint32_t>(cpu.upper[rt] >> 32) : 0u};
            const uint32_t out[4] = {sa == 0x1e ? w[2] : w[1], sa == 0x1e ? w[1] : w[2], w[0], w[3]};
            if (rd) {
                cpu.r[rd] = static_cast<uint64_t>(out[1]) << 32 | out[0];
                cpu.upper[rd] = static_cast<uint64_t>(out[3]) << 32 | out[2];
            }
            break;
        }
        fail("unsupported MMI instruction", pc, op);
    default: fail("unsupported instruction", pc, op);
    }

done:
    if (skipDelaySlot) {
        next = npc_;
        npc_ = next + 4;
    }
    pc_ = next;
}

} // namespace difftest::ee

// Shared pieces of the differential test (see main.cpp).
#pragma once

#include <cstdint>
#include <cstring>
#include <functional>
#include <random>
#include <vector>

#include "fake_world.h"
#include "nocturne/data/records.hpp"

struct datUnitWork_PS2;

namespace difftest {

using namespace nocturne;

template <class T> T& at(uint32_t address) { return *static_cast<T*>(fw_resolve(address)); }

inline uint64_t floatBits(float f) { uint32_t b; std::memcpy(&b, &f, 4); return b; }
inline uint64_t norm(uint64_t legacyRegister) { return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(legacyRegister))); }
inline uint64_t norm(int32_t value) { return static_cast<uint64_t>(static_cast<int64_t>(value)); }
inline uint64_t norm(bool value) { return value ? 1 : 0; }
inline uint64_t sx(int32_t v) { return static_cast<uint64_t>(static_cast<int64_t>(v)); }

inline datUnitWork_PS2* legacyUnit(uint32_t address) { return static_cast<datUnitWork_PS2*>(fw_resolve(address)); }
inline UnitWork& unitAt(uint32_t address) { return at<UnitWork>(address); }

struct Gen {
    std::mt19937_64 rng;
    uint32_t below(uint32_t n) { return static_cast<uint32_t>(rng() % n); }
    int32_t range(int32_t lo, int32_t hi) { return lo + static_cast<int32_t>(below(static_cast<uint32_t>(hi - lo + 1))); }
    bool chance(uint32_t percent) { return below(100) < percent; }
    template <class T, size_t N> T pick(const T (&values)[N]) { return values[below(N)]; }
};

// The legacy and rewritten calls for one case; both return the result as a
// normalised 64-bit value.
struct Pair {
    std::function<uint64_t()> legacy, rewrite;
};

struct TestCase {
    const char* name;
    std::function<Pair(Gen&)> make;
};

int32_t interestingSkill(Gen& g);
void randomUnit(Gen& g, UnitWork& u, bool enemy);

// A random save game: stock, stock list, Magatama, Reason points (fusion_tests.cpp).
void randomStock(Gen& g);
uint16_t randomDevil(Gen& g);

void addFusionTests(std::vector<TestCase>& t);        // fusion_tests.cpp
void addProgressionTests(std::vector<TestCase>& t);   // progression_tests.cpp
void addFusionCoreTests(std::vector<TestCase>& t);    // fusion_core_tests.cpp
void addMagatamaTests(std::vector<TestCase>& t);      // magatama_tests.cpp
void addAiTests(std::vector<TestCase>& t);            // ai_tests.cpp
void addMessageTests(std::vector<TestCase>& t);       // message_tests.cpp
void loadMessageTables(const char* elfPath);           // message_tests.cpp

} // namespace difftest

#include "version_map.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "nocturne/build.hpp"
#include "nocturne/variant.hpp"

namespace difftest::version {

namespace {

constexpr uint32_t kFirstData = 0x002f5000;   // US Maniax's data segment

struct Function {
    uint32_t other, size;
    bool sameCode;   // matched instruction for instruction (exact, masked, ordered): places inside map too
};

bool gActive = false;
uint32_t gGlobalPointer = 0;
std::map<uint32_t, Function> gFunctions;     // by US Maniax start
std::map<uint32_t, uint32_t> gData;          // US Maniax -> version, where the code formed it
std::map<uint32_t, uint32_t> gCodeBack;      // version -> US Maniax: function starts
std::map<uint32_t, uint32_t> gDataBack;      // ... and data

const char* versionName()
{
    switch (nocturne::kVariant) {
    case nocturne::Variant::Maniax: return "maniax";
    case nocturne::Variant::Chronicle: return "chronicle";
    case nocturne::Variant::Vanilla: return "vanilla";
    default: return nullptr;
    }
}

std::vector<std::vector<std::string>> rows(const std::filesystem::path& path)
{
    std::vector<std::vector<std::string>> out;
    std::ifstream in(path);
    std::string line;
    std::getline(in, line);   // header
    while (std::getline(in, line)) {
        std::vector<std::string> cols;
        std::stringstream s(line);
        std::string col;
        while (std::getline(s, col, '\t'))
            cols.push_back(col);
        if (line.back() == '\t')
            cols.push_back("");
        out.push_back(std::move(cols));
    }
    return out;
}

uint32_t hex(const std::string& s) { return static_cast<uint32_t>(std::strtoul(s.c_str(), nullptr, 16)); }

// By the delta the nearest neighbours below and above agree on.
uint32_t between(const std::map<uint32_t, uint32_t>& map, uint32_t address)
{
    auto above = map.lower_bound(address);
    if (above != map.end() && above->first == address)
        return above->second;
    if (above == map.begin() || above == map.end())
        return 0;
    auto below = std::prev(above);
    const int64_t d1 = int64_t(below->second) - below->first, d2 = int64_t(above->second) - above->first;
    return d1 == d2 ? static_cast<uint32_t>(address + d1) : 0;
}

} // namespace

bool load(const char* elfPath)
{
    // gp: the last word of the .reginfo segment.
    std::ifstream elf(elfPath, std::ios::binary);
    std::vector<char> bytes((std::istreambuf_iterator<char>(elf)), std::istreambuf_iterator<char>());
    auto word = [&](size_t at) { uint32_t v = 0; std::memcpy(&v, bytes.data() + at, 4); return v; };
    auto half = [&](size_t at) { uint16_t v = 0; std::memcpy(&v, bytes.data() + at, 2); return v; };
    if (bytes.size() >= 0x34)
        for (uint32_t i = 0, ph = word(0x1c); i < half(0x2c); ++i)
            if (word(ph + 32 * i) == 0x70000000)
                gGlobalPointer = word(word(ph + 32 * i + 4) + 0x14);
    if (gGlobalPointer == 0) {
        std::fprintf(stderr, "no .reginfo (gp) in %s\n", elfPath);
        return false;
    }
    const char* name = versionName();
    if (!name)
        return true;
    gActive = true;
    std::filesystem::path root = std::filesystem::absolute(elfPath).parent_path();
    while (!root.empty() && !std::filesystem::exists(root / "reference" / "versions") && root != root.root_path())
        root = root.parent_path();
    const auto folder = root / "reference" / "versions";
    const auto functions = folder / (std::string(name) + "-function-map.tsv");
    const auto data = folder / (std::string(name) + "-data-map.tsv");
    if (!std::filesystem::exists(functions) || !std::filesystem::exists(data)) {
        std::fprintf(stderr, "no %s maps under %s (tools/match_functions.py, match_data.py)\n", name, folder.string().c_str());
        return false;
    }
    for (const auto& r : rows(functions)) {
        if (r.size() < 4 || r[1].empty())
            continue;
        const uint32_t a = hex(r[0]), b = hex(r[1]);
        gFunctions[a] = {b, static_cast<uint32_t>(std::atoi(r[2].c_str())), r[3] == "exact" || r[3] == "masked" || r[3] == "ordered"};
        gCodeBack[b] = a;
    }
    for (const auto& r : rows(data)) {
        if (r.size() < 4 || std::atof(r[3].c_str()) < 0.99)
            continue;
        const uint32_t a = hex(r[0]), b = hex(r[1]);
        if (a >= kFirstData) {
            gData[a] = b;
            gDataBack.emplace(b, a);
        }
    }
    return true;
}

bool active() { return gActive; }
uint32_t globalPointer() { return gGlobalPointer; }

void requireUsText()
{
    if constexpr (nocturne::kBuild.japanese) {
#pragma warning(suppress : 4996)
        const bool runPending = std::getenv("DIFF_PENDING") != nullptr;
        if (!runPending)
            throw UsTextOnly{};
    }
}

uint32_t code(uint32_t maniax)
{
    if (!gActive)
        return maniax;
    auto it = gFunctions.upper_bound(maniax);
    if (it == gFunctions.begin())
        return 0;
    --it;
    if (it->first == maniax)
        return it->second.other;
    if (it->second.sameCode && maniax < it->first + it->second.size)
        return it->second.other + (maniax - it->first);
    return 0;
}

uint32_t codeBegin(uint32_t maniax)
{
    if (const uint32_t start = code(maniax))
        return start;
    const auto next = gFunctions.lower_bound(maniax);
    return next == gFunctions.end() ? 0 : next->second.other;
}

uint32_t codeEnd(uint32_t maniax)
{
    if (!gActive)
        return maniax;
    if (const uint32_t start = code(maniax))
        return start;
    // The end of the last function in the range, or a place in the padding
    // after it.
    auto it = gFunctions.lower_bound(maniax);
    if (it == gFunctions.begin())
        return 0;
    const auto next = it;
    --it;
    const uint32_t end = it->first + it->second.size;
    if (it->second.sameCode && end <= maniax && (next == gFunctions.end() || maniax <= next->first))
        return it->second.other + it->second.size + (maniax - end);
    return 0;
}

uint32_t functionSize(uint32_t maniax)
{
    const auto it = gFunctions.find(maniax);
    return it == gFunctions.end() ? 0 : it->second.size;
}

uint32_t data(uint32_t maniax)
{
    if (!gActive)
        return maniax;
    return between(gData, maniax);
}

uint32_t maniax(uint32_t address)
{
    if (!gActive)
        return address;
    if (address < kFirstData - 0x10000) {
        // Code: a function's start, or a place in one that matched.
        auto it = gCodeBack.upper_bound(address);
        if (it == gCodeBack.begin())
            return 0;
        --it;
        if (it->first == address)
            return it->second;
        const auto f = gFunctions.find(it->second);
        if (f != gFunctions.end() && f->second.sameCode && address < it->first + f->second.size)
            return it->second + (address - it->first);
        return 0;
    }
    return between(gDataBack, address);
}

uint32_t maniaxCodeOrDie(uint32_t address)
{
    const uint32_t us = maniax(address);
    if (!us)
        throw NoCounterpart{address, true};
    return us;
}

uint32_t codeOrDie(uint32_t maniax)
{
    const uint32_t address = code(maniax);
    if (address == 0)
        throw NoCounterpart{maniax, true};
    return address;
}

uint32_t dataOrDie(uint32_t maniax)
{
    const uint32_t address = data(maniax);
    if (address == 0)
        throw NoCounterpart{maniax, false};
    return address;
}

} // namespace difftest::version

extern "C" uint32_t fw_maniax_address(uint32_t address) { return difftest::version::maniax(address); }
extern "C" int fw_other_version(void) { return difftest::version::active() ? 1 : 0; }
extern "C" uint32_t fw_data(uint32_t maniax) { return difftest::version::data(maniax); }

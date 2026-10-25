// Fixed guest addresses, by version.
//
// The shared source writes US Maniax's addresses (SLUS_209.11) and reads
// each through addr(): the same address for US Maniax and Hardtype (which
// keeps them), another version's from its generated table
// (source/<version>/include/nocturne/version_addresses.hpp, written by
// tools/version_addresses.py). Both run at compile time: an address the
// table has no counterpart for is a compile error where it's used.
// optionalAddr() is for what a version may lack (a debug print's format):
// 0 there.
#pragma once

#include <cstddef>
#include <cstdint>
#include <iterator>

namespace nocturne {

struct AddressPair {
    uint32_t maniax, version;
};

} // namespace nocturne

#if __has_include("nocturne/version_addresses.hpp")
#include "nocturne/version_addresses.hpp"
#define NOCTURNE_ADDRESS_TABLE 1
#endif

namespace nocturne {

#ifdef NOCTURNE_ADDRESS_TABLE
// The version's address for `maniax`: 0 for none, ~0 if not in the table.
constexpr uint32_t lookupAddress(uint32_t maniax)
{
    std::size_t low = 0, high = std::size(kVersionAddresses);
    while (low < high) {
        const std::size_t middle = (low + high) / 2;
        if (kVersionAddresses[middle].maniax < maniax)
            low = middle + 1;
        else
            high = middle;
    }
    return low < std::size(kVersionAddresses) && kVersionAddresses[low].maniax == maniax ? kVersionAddresses[low].version
                                                                                       : ~0u;
}
#else
constexpr uint32_t lookupAddress(uint32_t maniax) { return maniax; }
#endif

consteval uint32_t optionalAddr(uint32_t maniax)
{
    const uint32_t address = lookupAddress(maniax);
    if (address == ~0u)
        throw "address not in the version table: run tools/version_addresses.py";
    return address;
}

consteval uint32_t addr(uint32_t maniax)
{
    const uint32_t address = optionalAddr(maniax);
    if (address == 0)
        throw "this version has no counterpart for the address";
    return address;
}

} // namespace nocturne

// Fixed guest addresses, by version.
//
// The source writes US Maniax's addresses (SLUS_209.11) and reads each
// through addr(): the same address for the US release and Hardtype (which
// keeps them), another version's from its generated table
// (source/generated/<version>/include/nocturne/version_addresses.hpp, written by
// tools/version_addresses.py). optionalAddr() is for what a version may lack
// (a debug print's format): 0 there. What only the JP builds have, the JP
// builds write by JP Maniax's address (SLPM_654.62) through jpAddr(),
// mapped the same way. All run at compile time: an address the table has no
// counterpart for is a compile error where it's used.
#pragma once

#include <cstddef>
#include <cstdint>
#include <iterator>

namespace nocturne {

struct AddressPair {
    uint32_t key, version;
};

} // namespace nocturne

#if __has_include("nocturne/version_addresses.hpp")
#include "nocturne/version_addresses.hpp"
#define NOCTURNE_ADDRESS_TABLE 1
#endif

namespace nocturne {

// The version's address for `key` in a sorted table: 0 for none, ~0 if not
// in it.
template <std::size_t N>
constexpr uint32_t lookupAddress(const AddressPair (&table)[N], uint32_t key)
{
    std::size_t low = 0, high = N;
    while (low < high) {
        const std::size_t middle = (low + high) / 2;
        if (table[middle].key < key)
            low = middle + 1;
        else
            high = middle;
    }
    return low < N && table[low].key == key ? table[low].version : ~0u;
}

#ifdef NOCTURNE_ADDRESS_TABLE
constexpr uint32_t lookupAddress(uint32_t maniax) { return lookupAddress(kVersionAddresses, maniax); }
constexpr uint32_t lookupJpAddress(uint32_t jp) { return lookupAddress(kJpAddresses, jp); }
#else
constexpr uint32_t lookupAddress(uint32_t maniax) { return maniax; }
constexpr uint32_t lookupJpAddress(uint32_t) { return ~0u; }   // (a US build has no JP-only data)
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

// A JP Maniax address another JP build may lack (a debug print's format): 0 there.
consteval uint32_t optionalJpAddr(uint32_t jp)
{
    const uint32_t address = lookupJpAddress(jp);
    if (address == ~0u)
        throw "no counterpart for the JP Maniax address: run tools/version_addresses.py";
    return address;
}

consteval uint32_t jpAddr(uint32_t jp)
{
    const uint32_t address = optionalJpAddr(jp);
    if (address == 0)
        throw "no counterpart for the JP Maniax address: run tools/version_addresses.py";
    return address;
}

} // namespace nocturne

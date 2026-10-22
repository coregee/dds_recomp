// Access to PS2 memory from rewritten code.
//
// Game structures are kept in their original PS2 layout so they can be shared
// with the legacy recovered C and with original data files. Pointers *inside*
// those structures are 32-bit PS2 addresses; Ptr32<T> wraps one so it can be
// used like a normal pointer. Fixed tables in the executable are reached
// through guest::table<T>(address).
//
// On a real PS2 build guest::resolve is the identity. Host builds (tests,
// ports) provide an implementation that maps a PS2 address into host memory.
#pragma once

#include <cstddef>
#include <cstdint>

namespace nocturne::guest {

void* resolve(uint32_t address);
uint32_t addressOf(const void* pointer);   // inverse of resolve; 0 for null

template <class T>
T* table(uint32_t address) { return static_cast<T*>(resolve(address)); }

} // namespace nocturne::guest

namespace nocturne {

template <class T>
struct Ptr32 {
    uint32_t address;

    T* get() const { return address ? guest::table<T>(address) : nullptr; }
    T* operator->() const { return get(); }
    T& operator*() const { return *get(); }
    T& operator[](std::size_t index) const { return get()[index]; }
    explicit operator bool() const { return address != 0; }
};

static_assert(sizeof(Ptr32<int>) == 4);

} // namespace nocturne

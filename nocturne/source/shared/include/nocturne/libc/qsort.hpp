// The PS2 C library's qsort (0x2D4860, the BSD/newlib Bentley-McIlroy
// quicksort). The game sorts records with equal keys, and their final order
// depends on this exact algorithm, so it is reproduced rather than replaced
// by std::sort.
#pragma once

#include <cstdint>

namespace nocturne::libc {

// Returns <0, 0 or >0 like strcmp.
using CompareFunction = int (*)(const void* left, const void* right);

void qsort(void* base, uint32_t count, uint32_t size, CompareFunction compare);

} // namespace nocturne::libc

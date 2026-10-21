// The PS2 C library's qsort (BSD 4.4 / newlib, after Bentley & McIlroy,
// "Engineering a Sort Function", 1993).
#include "nocturne/libc/qsort.hpp"

#include <cstring>

namespace nocturne::libc {

namespace {

using Byte = unsigned char;

void swap(Byte* a, Byte* b, uint32_t size)
{
    Byte temp[64];
    while (size) {
        uint32_t chunk = size < sizeof temp ? size : static_cast<uint32_t>(sizeof temp);
        std::memcpy(temp, a, chunk);
        std::memmove(a, b, chunk);
        std::memcpy(b, temp, chunk);
        a += chunk;
        b += chunk;
        size -= chunk;
    }
}

// Swap the n bytes at a with the n bytes at b (n may be 0).
void swapRange(Byte* a, Byte* b, intptr_t n)
{
    if (n > 0)
        swap(a, b, static_cast<uint32_t>(n));
}

Byte* medianOfThree(Byte* a, Byte* b, Byte* c, CompareFunction compare)
{
    return compare(a, b) < 0 ? (compare(b, c) < 0 ? b : (compare(a, c) < 0 ? c : a))
                             : (compare(b, c) > 0 ? b : (compare(a, c) < 0 ? a : c));
}

void insertionSort(Byte* base, uint32_t count, uint32_t size, CompareFunction compare)
{
    for (Byte* m = base + size; m < base + count * size; m += size)
        for (Byte* l = m; l > base && compare(l - size, l) > 0; l -= size)
            swap(l, l - size, size);
}

} // namespace

// qsort @ 0x002D4860
void qsort(void* array, uint32_t count, uint32_t size, CompareFunction compare)
{
    Byte* base = static_cast<Byte*>(array);
    for (;;) {
        if (count < 7) {
            insertionSort(base, count, size, compare);
            return;
        }

        // Pivot: the middle element, or a median of three (of three, for
        // more than 40 elements); moved to the front.
        Byte* middle = base + (count / 2) * size;
        if (count > 7) {
            Byte* low = base;
            Byte* high = base + (count - 1) * size;
            if (count > 40) {
                uint32_t step = (count / 8) * size;
                low = medianOfThree(low, low + step, low + 2 * step, compare);
                middle = medianOfThree(middle - step, middle, middle + step, compare);
                high = medianOfThree(high - 2 * step, high - step, high, compare);
            }
            middle = medianOfThree(low, middle, high, compare);
        }
        swap(base, middle, size);

        // Three-way partition: elements equal to the pivot collect at both
        // ends ([base, a) and (d, end)), smaller ones after a, larger before d.
        Byte* a = base + size;
        Byte* b = a;
        Byte* c = base + (count - 1) * size;
        Byte* d = c;
        bool swapped = false;
        for (;;) {
            int result;
            while (b <= c && (result = compare(b, base)) <= 0) {
                if (result == 0) {
                    swapped = true;
                    swap(a, b, size);
                    a += size;
                }
                b += size;
            }
            while (b <= c && (result = compare(c, base)) >= 0) {
                if (result == 0) {
                    swapped = true;
                    swap(c, d, size);
                    d -= size;
                }
                c -= size;
            }
            if (b > c)
                break;
            swap(b, c, size);
            swapped = true;
            b += size;
            c -= size;
        }
        if (!swapped) {   // already partitioned: probably nearly sorted
            insertionSort(base, count, size, compare);
            return;
        }

        // Move the equal runs into the middle.
        Byte* end = base + count * size;
        intptr_t n = (a - base) < (b - a) ? (a - base) : (b - a);
        swapRange(base, b - n, n);
        n = (d - c) < (end - d - static_cast<intptr_t>(size)) ? (d - c) : (end - d - static_cast<intptr_t>(size));
        swapRange(b, end - n, n);

        // Recurse on the smaller-than part, loop on the greater-than part.
        if ((n = b - a) > static_cast<intptr_t>(size))
            qsort(base, static_cast<uint32_t>(n / size), size, compare);
        if ((n = d - c) <= static_cast<intptr_t>(size))
            return;
        base = end - n;
        count = static_cast<uint32_t>(n / size);
    }
}

} // namespace nocturne::libc

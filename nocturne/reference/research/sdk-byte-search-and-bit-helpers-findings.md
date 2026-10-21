# SDK byte search and bit helpers

Seven complete original library/runtime leaves are recovered in
`src/ps2_sdk_frontier.c/.h`. All 19,686 new original-instruction comparisons pass,
included in the checkpoint of 211 compiled functions and 152,996 cases.
These names are chosen behavior aliases, separately recorded in
`library-identifications.tsv`; historical library/compiler symbols and HD
counterparts are unclaimed.

| Original entry | Source alias | Cases |
|---|---|---:|
| `002da4b8` | `ps2WidenByte` | 4,696 |
| `002da4ec` | `ps2Memchr` | 10,375 |
| `002da8e0` | `ps2CountLeadingZeroBits` | 580 |
| `002da960` | `ps2RemoveTrailingZeroBits` | 580 |
| `002daec0` | `ps2CompareLimbArrays` | 915 |
| `002db5e8` | `ps2IsDoubleInfBits` | 1,270 |
| `002db630` | `ps2IsDoubleNaNBits` | 1,270 |

All 207 original instruction words /828 bytes independently re-encode exactly.
Complete spans, primary ELF/PC image hashes and retained artifact hashes are in
`drafts/next_sdk_frontier/body-evidence.json` and the independent review.
The saved 46-routine Ghidra register-storage audit passes, including the full 64-bit
fourth A3 argument of widening and full 64-bit A0 of both double predicates.

## Recovered interfaces

Widening ignores A0. NULL source returns 0 without memory access; otherwise
all 64 bits of A3 qualify availability, with zero returning -1. It reads one
unsigned byte, stores one complete word to A1 or private scratch, rereads the
source byte, then returns whether that reread is nonzero. Source aliases at
output+1/+2/+3 can change the result after the word store. The C has no restrict
qualifier and retains this ordering.

Byte search narrows its target to low8. Count 0 permits NULL and performs no
memory access. A 16-byte aligned cursor with at least 16 remaining bytes executes
a full LQ block and the original MMIXOR/PSUBB zero detector, then rescans a
matching block bytewise to return the first matching pointer. Unaligned and
short paths use byte reads. No block extends beyond the qualified count.
The host source expresses the full block read through memcpy; no bus-width
atomicity, MMIO semantics or access-trace equivalence is asserted.

Leading-zero counting requires the original canonical signed 32 extension into
A0 because its final BLTZ tests full64 bits. Under that interface it counts
low32 leading zeros, with zero returning 32. Separately retained zero-extended
high-bit register probes produce different original results and are outside
this declared C interface. Trailing-zero removal reads one word; zero returns 32
and odd values return 0 without a store. Nonzero even words shift logically to
an odd value, write once and return the shift count.

Limb records have opaque bytes 0..15, count word at 16 and least-significant-first
limbs at 20. Unequal counts return their exact low32 SUBU difference as signed 32.
Equal positive counts compare unsigned limbs from highest to lowest; equal0
executes the original do-while path and rereads both count words. Unequal count
headers may have any raw32 encoding, since no limb is followed. Equal counts
must be nonnegative with every followed limb backed and no pointer wrap.
Exact self and read-only overlapping inputs retain their aliases.

The double predicates use integer instructions only. With sign removed,
exact 7FF0000000000000 is infinity; a greater unsigned magnitude is NaN.
All64 encoding bits and payloads are retained without host float conversions
or FCSR operations; returns are exact 0/1.

## Captures and limits

Each call captures the entire 4096-byte arena and both 16-byte guards before and
after actual original ELF instruction execution. Raw registers use fixed 16-hex
strings, preserving signed extension and full64 availability/double inputs.
The host translates only real pointer arguments through one aligned arena,
preserving aliases, and normalizes byte-search results to NULL or arena offset.
Unexpected pointers, unsupported counts, malformed captures and unbacked spans
are rejected. No host globals are rebound.

Cases enumerate all byte values and widening output-byte aliases; all 16 search
alignments, boundary counts, targets and hit positions; aligned LQ lane hits;
zero/extreme/alternating/one-bit words; count-header wraps and every selected
limb position; raw double exponents, signs and payload bits; plus fixed-seed
random values. Generator and adapter restore all arena/guard bytes in finally
blocks. Separate self-authored actual-word development probes add no canonical
original-instruction cases.

`sdk-byte-search-and-bit-helpers-validation.json` binds the results to current
source/verifier/vector/body/snapshot hashes. Ordinary stable little-endian RAM,
aligned word/header objects and bounded backing are the scope; PS2 runtime,
hardware flags, access traces and matching binaries remain unverified.

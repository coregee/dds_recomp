# Software-double support

The MP calculation exposed a compiler-support module whose arithmetic results had incorrect inferred `void` types. Twelve routines are reconstructed in `src/ps2_soft_double.c`, independently identified in Ghidra, and recorded in `library-identifications.tsv`. Names are chosen behavioral aliases; original library symbols and compiler version remain unconfirmed.

| PS2 entry | Recovered alias | Original-instruction comparisons |
|---|---|---:|
| `0x002D34A0` | `ps2SoftDoublePack` | 2,000 |
| `0x002D3578` | `ps2SoftDoubleUnpack` | 4,120 |
| `0x002D1B88` | `ps2SoftDoubleFromInt` | 1,000 |
| `0x002D1C40` | `ps2SoftDoubleToInt` | 4,120 |
| `0x002D18B0` | `ps2SoftDoubleMul` | 2,000 |
| `0x002D3398` | `ps2Mul64` | 1,000 |
| `0x002D1590` | `ps2SoftDoubleAddParts` | 2,000 |
| `0x002D17F0` | `ps2SoftDoubleAdd` | 2,000 |
| `0x002D1848` | `ps2SoftDoubleSub` | 2,000 |
| `0x002D1D68` | `ps2SoftDoubleToUint` | 4,120 |
| `0x002D3638` | `ps2SoftDoubleCompareParts` | 2,000 |
| `0x002D1B38` | `ps2SoftDoubleCompare` | 2,000 |

The 24-byte parts record has 32-bit class at `+0`, sign at `+4`, signed exponent at `+8`, padding at `+12`, and 64-bit fraction at `+16`. Classes are signaling NaN 0, quiet NaN 1, zero 2, finite 3 and infinity 4. Normal fractions have the implicit bit at 60 and eight low guard bits; exponent bias is 1023. `software-double-layout.txt` records the applied type.

At `0x002D1B04`, multiply calls the packer and preserves V0 through its return. The add/subtract wrappers also return packed bits in V0. `software-double-abi.json` checks the saved register storage: 64-bit results use `v0:8`, binary-operation inputs use `a0:8` and `a1:8`, and pointers/signed32 values use the low four bytes. These are integer bit interfaces; a generic double prototype could assign a floating-point register incorrectly.

The packer drops guard bits without rounding and flushes too-small exponents to signed zero. The unpacker treats every exponent-zero input as zero and preserves pre-existing exponent/fraction/padding on that branch. Multiplication propagates NaN payloads and combines signs according to the original paths. Infinity times zero uses the immutable all-zero parts record at `0x0054B460`, which packs to positive quiet NaN `0x7FF8000000000000`. `ps2Mul64` keeps the low 64 product bits for arbitrary full-width operands, including overflow.

## Addition and unsigned conversion

At `0x002D1590`, A0/A1 point to operands and A2 to a result record. V0 can return the left operand, right operand, output, or the immutable invalid-operation record at `0x0054B460`. The first NaN wins; otherwise a second NaN is selected. Opposite infinities select invalid parts. Two zeros copy all 24 bytes from the left operand and AND their sign words, preserving negative zero only when both signs are negative.

For finite nonzero operands, exponent differences of 64 or more discard the smaller fraction. Smaller differences align using repeated `(fraction & 1) | (fraction >> 1)` shifts, retaining a sticky low bit. Equal signs add magnitudes; opposite signs subtract and normalize nonzero results to bit 60. Exact cancellation yields positive zero when packed. Arithmetic writes class/sign/exponent/fraction while preserving output padding. The subtraction wrapper at `0x002D1848` XORs the second unpacked sign with 1 before this shared path, including for zero, infinity and NaN.

At `0x002D1D68`, NaN, zero and every negative operand convert to unsigned zero. Positive infinity or exponent 32 and above saturate at `UINT32_MAX`; finite exponents 0 through 31 truncate by shifting the fraction. This must not be replaced by an unchecked host float-to-unsigned cast.

At `0x002D3638`, parts comparison returns -1, 0 or 1 for ordered operands, with sign reversing finite magnitude order. Zero signs compare equal. Either NaN returns 1. The wrapper at `0x002D1B38` unpacks both 64-bit operands and preserves that signed32 result in V0; its previous inferred `void` type hid predicates from callers. Both direct parts and bit-pattern interfaces pass comparison cases, including equality and cancellation-derived zeros.

## Validation and transfer

The 28,360 library comparisons cover all 2,048 binary64 exponent fields with both signs for unpacking and signed/unsigned conversion, NaN payloads, signed zeros, flushed subnormals, overflow boundaries, integer saturation, full-width products and cancellation. Direct parts-addition tests compare returned pointer roles, returned 24-byte records, and complete backing buffers including padding. They cover all class pairs, bounded exponents, normalized fractions, and disjoint input/output records; malformed parts and arbitrary aliasing are outside that direct helper's validated contract.

Expected results come from original ELF instructions without replacing arithmetic helpers in the emulator. The double/product routines retain their 28,360 cases; the connected float helpers add 14,200. See `behavior-validation.json` for current whole-suite totals and source hashes. This establishes instruction-model agreement, not console or matching-binary validation.

The class structure and algorithms resemble [GCC 2.95.3 fp-bit.c](https://github.com/gcc-mirror/gcc/blob/releases/gcc-2.95.3/gcc/config/fp-bit.c). That source includes rounding and denormal handling absent from the inspected PS2 helpers, so it is a structural reference rather than a verified source/version match. Recoveries here follow the PS2 instructions.

The six neighboring float/double conversion and field-pack wrappers are now reconstructed and annotated. `software-float-findings.md` records the 16-byte parts type, F12 input/F0 return storage, all-exponent comparisons and exceptional encoding behavior. In particular, float exponent255 is treated as finite during widening; an IEEE host cast changes the result. Together the eighteen compiler-support identities form a transfer candidate independent of Unity matching. Recheck bodies, register ABI and exceptional bit behavior in each other executable before reusing them.

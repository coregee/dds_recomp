# Float encodings and conversion ABI

Six reconstructed routines in `src/ps2_soft_float.c` add 14,200 original-instruction comparisons. They are separate compiler-support identities, with chosen behavioral names rather than verified original library symbols.

| PS2 entry | Alias | Native interface | Cases |
|---|---|---|---:|
| `0x002D3410` | `ps2SoftFloatUnpack` | Pointer arguments in A0/A1; no result | 1,540 |
| `0x002D3758` | `ps2SoftFloatPack` | Pointer in A0; encoded float in F0 | 2,000 |
| `0x002D1CE0` | `ps2SoftDoublePackFields` | A0/A1/A2 low32, A3 full64; result V0 full64 | 2,000 |
| `0x002D3470` | `ps2SoftFloatPackFields` | Four integer arguments; float result F0 | 2,000 |
| `0x002D1550` | `ps2SoftDoubleFromFloat` | Float encoding in F12; binary64 bits in V0 | 1,540 |
| `0x002D1D10` | `ps2SoftDoubleToFloat` | Binary64 bits in A0; float encoding in F0 | 5,120 |

The 16-byte float parts record uses class/sign/exponent/fraction at offsets 0/4/8/12. Exponent bias is 127, the implicit fraction bit is 30, and seven guard bits are discarded when packing. The unpacker classifies exponent-zero inputs as zero, writing only class and sign. Every other exponent becomes class 3, including exponent 255; existing exponent/fraction bytes remain untouched on the zero branch.

Packing treats class 2, fraction zero and exponent below -126 as signed zero. Exponents above 128, or exponent 128 with fraction bit31 set, produce exponent255 with zero fraction. Otherwise the seven guard bits are truncated and the exponent/fraction encoding is preserved, including fractional exponent255 patterns. There is no special class0/1/4 handling analogous to the double packer.

The widening helper's `SWC1 F12` at `0x002D1564` establishes the actual argument register. It shifts the unpacked fraction by30 bits before double packing. The encoded input `0x7F800000` yields finite binary64 `0x47F0000000000000`; `0x7FC00000` yields finite `0x47F8000000000000`. Ordinary host IEEE casts would classify those inputs differently. This agrees with the extended-range conversion strategy in [PCSX2's primary conversion source](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/x86/iFPUd.cpp), which handles encodings that IEEE views as infinity/NaN by adjusting the exponent around conversion. That comparison does not identify the game's original compiler/library version.

The narrowing helper takes fraction bits30..61 and ORs a sticky low bit when any of the discarded low30 bits are nonzero. The float field packer finishes the encoding and returns F0. At `0x002D3800`, the raw packer explicitly executes `MTC1` into F0; the old inferred integer return was incorrect. `software-double-abi.json` audits these registers from the saved program, together with the twelve earlier double/product routines.

Recovered C uses native float-facing signatures and `memcpy` for bit transport, with no host floating arithmetic or casts in these conversions. Host-only bit adapters in `tests/host_bindings.c` call the actual recovered functions and prevent Python float promotion from altering payloads. Validation sweeps all 256 float exponents with both signs for unpacking/widening, all 2,048 double exponents with both signs for narrowing, plus boundary patterns, randomized fractions and preserved backing buffers.

These helpers use only bit operations and floating-register transfers. Their comparisons do not validate the entire R5900 arithmetic pipeline: native FPU add/multiply/divide, rounding, clamping and flags need separate review before generic IEEE emulation can support broader claims. Shared-SMT transfer must check both encodings and the F12/F0 versus integer-register ABI in the other executable.

# Numeric dependencies of the SDK formatter

Eight complete routines in `src/compiler_numeric.c` now compile and pass11,264
original-instruction comparisons. They cover6,992 recognized original body bytes.
Working Ghidra interfaces were saved, independently reopened, and all eight
selected exports were refreshed in the current8,958-function inventory.
These are descriptive aliases and raw EE bit interfaces, not recovered original
compiler symbols or a matching executable.

| Nocturne entry | Recovered role | DDS complete-span candidate | Cases |
| --- | --- | --- | ---: |
| 002e5320 | Signed64 quotient | 00313ea0 | 2,048 |
| 002e59b8 | Signed64 remainder | 00314538 | 2,048 |
| 002e6048 | Unsigned64 quotient | 00314bc8 | 2,048 |
| 002e65c8 | Unsigned64 remainder | 00315148 | 2,048 |
| 002e6c48 | Software-double division | 003158e8 | 1,024 |
| 002e6d88 | Signed64 to software-double | 003156b0 | 512 |
| 002e6b30 | Software-double to unsigned64 | 00315758 | 1,024 |
| 002dd540 | SDK rounded word from double bits | 0030c0c0 | 512 |

The integer C uses unsigned magnitudes to retain signed quotient/remainder
behavior without undefined C overflow. Signed quotient truncates toward zero;
the remainder follows the dividend's sign. INT64_MIN divided by-1 retains the
original wrapped64-bit result. There are132 zero-divisor cases. Original code
reaches BREAK7; the host raises the corresponding nonreturning exception boundary,
observed through a test wrapper. Neither invents an ordinary division result.
The test does not model a physical exception handler or resuming after BREAK.
Original integer code performs normalized32/16-bit limb division and corrections;
the recovered C expresses the resulting quotient/remainder with host unsigned
division. It does not reproduce those internal correction steps or claim the
same instruction trace or compiler output.

Software-double division invokes the existing actual unpack/pack code. NaN-class
operands return before sign XOR; zero/zero and infinity/infinity use immutable
invalid-operation parts. Normal division produces61 quotient bits before the
original truncating pack. It keeps flushed subnormals and original NaN/sign/
overflow behavior, with no host floating arithmetic.

The64-bit-to-double helper is signed: its upper word is converted as signed32,
multiplied by65536 twice, then added to the unsigned-adjusted lower word. This
explains the unsigned conversion helper's half-and-double workaround when its
upper-word candidate has bit63 set. That helper builds the upper word separately,
subtracts its software-double representation from the input and adds or subtracts
the converted residual. Negative input returns0. All calls use the actual
existing software-double conversion, multiply, add, subtract and compare bodies.

The SDK word-rounding helper ignores the sign bit. For a negative internal
exponent it shifts by(-exponent-2)&63, then increments only if both low guard
bits are set. Thus1.5 truncates to1 while1.75 produces2. Variable shifts retain
the original63 mask, including the wrap for an internal exponent of-1; output
is a sign-extended32-bit word. Small exponents return0 and internal exponents
of13 or greater return9999. It is not ordinary host round-to-nearest.

The capture executes2,574,849 original steps. Returning cases compare all64
return bits and preserve saved registers, stack pointer, GP, RA and Status.
All non-delay PCs were reached for double division, signed64-to-double and
SDK rounding. Four integer routines have19 or24 unobserved PCs apiece, including
instructions after divisor-zero BREAK and rare quotient-correction paths.
The unsigned conversion's seven-instruction negative-residual correction remains
unobserved and is retained in source. Integer correction coverage describes the
original execution paths, which the C abstracts as division; the report records
those gaps rather than asserting exhaustive equivalence.
Fixed shipped bit-length tables and invalid-operation parts are part of the
evidence. Private stack bytes, scratch registers, exhaustive input coverage,
physical CPU exceptions and runtime behavior remain unproved.

All eight DDS spans match uniquely under explicit J/JAL and immutable-data
address relocations. Every referenced256-byte bit-length table agrees and is
independently equal to the byte-valued bit length of0..255. The24-byte invalid
parts agree and are all zero. Both calls from DDS unsigned conversion to the
signed conversion helper agree. DDS is read-only in this investigation.
The complete comparisons are recorded in `compiler-numeric-transfer.json`.

The next SDK formatter dependencies are serial output002dd420, newline wrapper
002dd508, buffered output002dd458, kernel string command002e4a50/002dc2d0, and
floating format002dd5d0. The main formatter002dd738 and printf wrappers002ddd28/
002ddd60 can then execute those actual dependencies. Its independently decoded
73-entry table at54bb10 supports0,c,d,e,f,h,l,o,s,u,x; other entries skip the
character. Both e/f route to the same float path. Scientific constants54baf8/
54bb00 are0.1 and54bb08 is1,000,000; format strings at54bae0/54bae8/54baf0 are
`0.%d`, `e+%d`, `e%d`. The original float path passes unsigned conversion output
directly to the raw-bit rounding helper. Preserve that call sequence when
recovering the formatter, and validate its output before interpreting its intent.
The independent libc printf002d4748->002d6600 is also still required by archive
readiness/retry diagnostics. No printf or movie-reader function is promoted here.

Current integration is628 functions/536,476 aggregated comparisons. The last
full suite is413 functions/462,684 cases; this numeric group adds focused
evidence without repeating the unrelated full regression. Full executable
recovery, PS2/IOP/filesystem execution and binary equivalence remain incomplete.

# Native dtoa bigint recovery

Eleven complete C bodies are recovered in `src/libc_bigint.c`, with 3,152 summed
recognized body bytes and 4,096 passing focused comparisons. Native heap allocation,
locks/sbrk, memory copy/clear, limb comparison and bit-count helpers execute in both
original instruction capture and the compiled recovered implementation. Numeric
results, all 100,500 declared RAM bytes per case, Status and ordered kernel and
interrupt traces agree. This is source recovery and instruction emulation evidence;
physical PS2 execution and matching executable bytes remain unproved.

| PS2 entry | Recovered function | Recognized bytes | Cases | DDS entry |
|---|---|---:|---:|---|
| `002db840` | `ps2LibcCallocReentrant` | 176 | 256 | `00309fa0` |
| `002da5d0` | `ps2LibcBigintAllocate` | 164 | 256 | `00307a68` |
| `002da678` | `ps2LibcBigintFree` | 44 | 128 | `00307b10` |
| `002daa20` | `ps2LibcBigintFromWord` | 56 | 128 | `00307eb8` |
| `002da6a8` | `ps2LibcBigintMultiplyAdd` | 264 | 512 | `00307b40` |
| `002daa58` | `ps2LibcBigintMultiply` | 524 | 512 | `00307ef0` |
| `002dac68` | `ps2LibcBigintPowerOfFive` | 248 | 256 | `00308100` |
| `002dad68` | `ps2LibcBigintShiftLeft` | 344 | 512 | `00308200` |
| `002daf28` | `ps2LibcBigintDifference` | 400 | 512 | `003083c0` |
| `002db320` | `ps2LibcBigintFromDoubleBits` | 380 | 512 | `003087b8` |
| `002d8148` | `ps2LibcBigintQuotientRemainder` | 552 | 512 | `00305db8` |

## Native structures and behavior

The reentrancy record holds a power-of-five cache at offset72 and a free-list
pointer at76. The latter points to sixteen word heads allocated as calloc4*16.
Bigint records contain next0, class4, capacity8, sign12, wordcount16 and limbs20.
Allocation reserves20 +4*(1<<class) bytes; reused records clear sign/count only.
Free returns a record to its class head, retaining its other fields and limbs.
Calloc multiplies its operands with native word wrapping and clears the usable
heap extent derived from the actual chunk header, including allocation padding.

Multiply/add and multiplication use the original half-limb partial products,
word wrapping and ordered halfword writes. Growth executes actual Memcpy from
sign/count/limbs at+12 before recycling the previous record. Shift always allocates
a new record, stores whole-word zeros and a trailing carry (including zero), then
recycles its input. Difference preserves magnitude/sign and count trimming.
Power-of-five consumes the low two exponent bits through5/25/125, then caches625
and successive squares through next0; replaced running operands enter free lists.
Raw64 input pointers are returned intact when multiply/add or pow5 leaves the
original record in place, rather than always normalizing to a32-bit pointer.

Double extraction uses raw bits, not host floating conversion. It removes sign,
extracts the encoded exponent and hidden mantissa bit, and calls the recovered
trailing-/leading-zero routines. It retains zero, subnormal, normal, infinity/NaN
bit patterns and selected exponent/significant-count output aliases. The original
private stack scratch placement and a broader FPU argument transport are unproved.

Quotient/remainder retains high/(denominator_high+1), half-limb subtraction and a
single correction. Its first trimming branch tests the cached pre-subtraction
high word, never a fresh load. Its output can therefore retain a leading zero;
this implementation preserves that behavior. The native zero divisor reaches
BEQL/BREAK7 before MFLO: eight cases compare exception code7 and the memory prefix,
with no ordinary return or callee-save claim. Ghidra INT_REM0 otherwise fails before
that native branch, so only DIVU at2d81b4 is bypassed on those eight cases. Its LO/HI
values have no consumer before BREAK and are explicitly unobserved. All ordinary
nonzero divisions execute from original instructions; no library returns are hooked.

## Coverage and verification

The rolling capture visits3,706,868 original instruction positions and records
61,724 kernel/interrupt trace words. It reaches670 of682 selected non-delay PCs.
The twelve remaining PCs have explicit static explanations:

- Calloc2db8b4/2db8b8/2db8bc require usable extent36 (chunk40). Valid native heap
  extents are multiples16, yielding small usable extents12/28 and then44, which
  takes Memset. The original branch is retained for malformed chunk metadata.
- Quorem2d8248/2d8250/2d8254/2d8258/2d8260/2d8264/2d8268/2d826c/2d8274 require
  cached high=0 after quotient!=0. A nonzero divisor gives0/divisor=0; a zero
  divisor terminates at BREAK before MFLO. The subtraction loop never modifies
  that cached register, so this path is unreachable.

All other selected non-delay PCs are reached, including the separate correction
trimming loop. Fixtures include class reuse/new allocation/table and record OOM,
heap padding clear, limb growth, zero counts, operand self-alias, carry/borrow
chains, cached/new power chains, word/bit shifts, positive/negative/equal differences,
nonfinite and subnormal bit patterns and exception termination. Captures check guest
writes remain inside declared RAM or private stack and returning roots preserve
callee-saved registers, GP/SP/RA and zero. Host/guest alignment is checked.

The C builds with warnings treated as errors. Existing numeric adapters also pass
11,264 comparisons after extending their exception observer for the quorem root.
No new full-suite run or full capture is claimed. One current bigint capture and
one current report are maintained in place; no checkpoint/project backup was made.
Unrestricted malformed records, failure dereferences in native callers without
checks, arbitrary negative powers/shifts, concurrency and hardware remain unproved.

## Transfer and next work

All eleven complete contiguous DDS instruction spans resolve uniquely. Twenty-three
call links agree, and Nocturne table54b91c and DDS table3b83bc contain the same5/25/125
entries. Only code/data address immediates are relocated; field offsets, indexed
power-table arithmetic, branch geometry, constants and all other native words stay
fixed. DDS heap malloc and dtoa have no complete-span match with the current mask;
that does not disprove broader equivalence. DDS execution and original library
symbol spelling are not claimed. Shared structure fingerprints are recorded in
`analysis/shared-smt-signatures.tsv`.

Next recover full dtoa002d8378 (4,632 recognized bytes) and its20 actual dependencies,
then cvt002d7ce8 and the complete libc printf chain002d4748->002d6600->002d6678,
including local-buffer __sbprintf002d6548 and movie/archive diagnostics. All20 dtoa
callees now have recovered source, subject to the existing ABI/domain limits;
the full dtoa control flow, rounding, cached output lifetime and output records
remain unrecovered. The HD native reference remains useful for game functions;
this PS2 library cohort is identified from native instructions and the DDS matches.

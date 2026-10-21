# Skill RNG, level growth and result resources

Five reconstructed functions add 2,944 original-instruction comparisons to the
216-function / 155,940-case checkpoint. Four identities come from named native
Unity counterparts. `ps2AddLevelUpParam` is a chosen descriptive alias for an
original PS2 wrapper whose historical spelling remains unproved.

| Original entry | Native reference | Recovered function | Cases |
|---|---|---|---:|
| `00220d58` | `1822810b0` | `rstRndGetPowerUpSkill` | 1,024 |
| `00222e00` | `182277dc0` | `cmbAddLevelUpParamEx` | 768 |
| `00223520` | `18227b6b0` | `cmbGetMutationSkill` | 384 |
| `002201a0` | `182281880` | `rstSetMaxHpMp` | 512 |
| `00223080` | Unestablished | `ps2AddLevelUpParam` | 256 |

All 356 listed instructions were independently re-encoded against the primary
ELF. The full spans contain 357 words / 1,428 bytes, including the omitted NOP
at `00222fdc`. The C builds with MSVC C11 `/W4 /WX /O2`. Expectations come from
executing the original ELF instructions under the documented corrected DIVU
and instruction-value model, with real dependency calls. This does not establish
PS2 console execution, access timing or matching machine code.

## Selection and mutation

Power-up selection scans the original unsigned normal-skill count, maps each
nonzero skill through the actual fixed 55-row upgrade lookup, retains duplicates
as separate candidates and remembers their original slot bytes. No candidates
leave RNG and output unchanged. A nonempty list consumes exactly one draw and
uses unsigned modulo. The original index pointer is optional and can alias a
writable unit byte: its store happens after gathering and RNG, before reading
the selected private candidate. The source preserves that order. Counts through
24 are supported; exceeding the private arrays is not given a repaired behavior.

Mutation performs up to 64 actual draws modulo the fixed 227-row inheritance
level table. Each draw calls the real level lookup and skill-owner query, then
the rate query when ownership permits it. Rate, same-ID and level gates precede
a success. The original skill level is genuinely queried twice on the passing
path. Both level results are unsigned bytes, proved by the dependency's LBU and
default literal 1; the older parent pseudocode's signed-char casts are wrong.
Exhaustion returns zero with all 64 RNG updates retained.

Cases exercise first-match duplicate table rows, high unsigned levels, normal
skill ownership, rate/motion gates, actual success and 64-draw exhaustion.
Candidates and original IDs have complete table backing. Motion-compatible
level zero would execute the original rate dependency's BREAK7 and is outside
these returning comparisons; level zero with an incompatible motion is valid.
The largest captured mutation call executes 240,461 instruction steps. Its
dedicated ceiling is one million; the ordinary leaf ceiling remains unchanged.

## Weighted parameter growth

Growth values are unsigned bytes from the six-byte prefix of the supplied
102-byte demon skill row, or the equipped player's 66-byte Hearts row at offset
`12` hex. Lane 1 is excluded. Every lane still executes the real parameter
query; growth zero or its low-byte result equal to 40 marks an excluded quotient
of -1 without initializing that lane's private weight.

Eligible lanes use signed level-up bytes divided by positive growth, signed
16-bit quotients and unsigned 16-bit growth-minus-remainder weights. Selection
uses the minimum quotient, an actual RNG draw modulo the total and a threshold
narrowed to a byte. The cumulative sum also narrows after each addition. The
Unity port uses wider accumulation; copying it changes PS2 results.

Byte wrapping can make every candidate comparison fail and return 6 without a
write. The original comparison uses threshold <= cumulative, preserving its
zero-remainder boundary. Mode zero increments the selected parameter byte with
wrapping; any nonzero signed mode skips that store. The PS2-only wrapper calls
the same routine with mode zero and preserves V0.

The deterministic recovered interface excludes a minimum eligible quotient of
-1. That value also matches excluded lanes and observes their uninitialized
private weights in the original. No invented initialization, default weight or
clamp is added. Nonnegative level-up bytes satisfy the condition; the suite also
includes defined negative minima below -1. Cases cover all 256 growth bytes,
player/demon backing, ties, caps, lane exclusion, return 6, all signed modes and
127-to-128 byte increments.

## Resource updates and the result view

`rstSetMaxHpMp` first runs the real full custom-copy into private scratch,
including its two maximum-resource calls. It then loads the result pointer from
original slot `00551f88`, adds six result bytes at `129f` hex to the scratch
parameters with low-byte wrapping, and makes two more real resource calls.

Mode zero with a nonzero signed result byte at `26` hex refills current HP/MP
when storing their new maxima. Other paths update maxima only. Both finish by
unsigned current-resource clamps. The original unit's parameter bytes retain
their values; only the private copy receives deltas.

`rstResourceWork_PS2` proves an accessed extent of `12a5` bytes, with unknown
gaps preserved. It is not a complete allocation size. The host pointer binding
adapts the original slot; native managed layouts and references are not imported.
Cases cover every signed mode, zero and nonzero refill flags, negative flags,
byte deltas, ushort resource/level extremes, flag4/20 and status200 behavior,
real skill bonuses and full-unit copy/resource dependencies.

## Capture and replay scope

The fixture snapshots complete work, RNG, unit, partial result extent and index
output, with guards around the latter three. It also records complete before
bytes and before/after hashes for seven shared table spans, plus both original
pointer slots. Host replay keeps the exact existing table/work/RNG owners and
the interior Hearts skill-row pointer. It compares captured returns, every
space and guard byte, immutable table hashes and all participating bindings.
Every owner and binding is restored after a case, including on exceptions.

The 2,944-case isolated preflight is retained as development evidence; it is not
added to the canonical count a second time. The canonical report records the
fresh full replay and all source/verifier/vector hashes. The preceding
211-function checkpoint and its 83 input files remain under
`analysis/checkpoints/211-functions/`.

Six connected skill-power callers are now strict-built drafts under
`analysis/drafts/rst_power_chain/`. Their 183 complete-span words are checked,
but their behavior is outside this checkpoint. The PS2 party query overwrites
its result for each qualifying unit; native code accumulates OR. The original
chance routine also uses zero-based modulo thresholds while native adds one.
Those differences must survive the caller reconstruction.

# Native physical, magic, healing and HP power

Five complete routines in `src/battle_power.c` and `.h` compile and pass
**1,536 original-instruction comparisons**, executing **20,589,433 steps**
and every **472 main instruction address**. They contribute **2,172
recognized body bytes**. Actual work getters, support ratios, parameters,
base HP, event bits, default RNG, software-double routines and the original
printf/formatter/cvt/dtoa/bigint/heap/string dependencies execute.

| Original entry | Recovered role | Recognized bytes | Cases |
|---|---|---:|---:|
| `00268620` | `nbGetButuriAttack` | 652 | 384 |
| `002688B8` | `nbGetButuriKaifuku` | 20 | 128 |
| `002688D0` | `nbGetMagicAttack` | 908 | 384 |
| `00268C60` | `nbGetMagicKaifuku` | 252 | 256 |
| `00268D60` | `nbGetMaxHpWazaPoint` | 340 | 384 |

## Original contracts and important HD differences

The physical evaluator resolves both units, obtains source support ratio4
and target ratio7, then calls `datGetNormalAtkPow` and `datGetDefPow` even
though their results are discarded. It doubles the source level and actual
parameter0 separately in COP1 before adding them. Only the **full64 zero
skill** takes the basic-attack branch; a dirty high lane with lowword0 takes
the skill-power branch. Skill power is converted from its low signed word.

Unit flag20 selects the enemy coefficients and subtracts the **integer**
quotient48 or50 divided by `LHUlevel+10`, depending on skill-zero/nonzero.
The denominator is10..65545, so its retained division trap cannot fire for
the native unsigned16 level. A clear original event bitAF2 applies the
additional coefficient. The player branches have distinct coefficients.
The table at RAM `0054E554` / ELF file `0044F554` is read as exact raw float
words; decimal-looking replacements are not used. Two actual diagnostic
printf calls report the support ratios. The final two COP1 multiplications
and `CVT.W.S` produce a sign-extended word return.

Physical healing is an **unconditional20-byte tail call** to that same
physical evaluator. Unity duplicates the physical calculation in its managed
healing method. The recovered PS2 source retains the shared call.

The magic evaluator obtains source ratio5 and target ratio7. The native
action descriptor is at `003D7998 + low_skill*3C`; magic base and limit are
**signed LH fields at +38/+3A**. Its initial rate combines the base with
the wrapping word product `level * low_power *2` divided by21.0, then applies
a strict C.LT.S limit check. Its stat adjustment uses actual parameter2,
level capped to160, and the original5.0/4.0/2.5/100.0 COP1 sequence. The
result converts through the real compiler software-double routines and
the full64 coefficient at `00544D20` before returning to a float value.

For non-flag20 units above level100, the loop counter starts100 and controls
the number of repetitions. **Each PS2 iteration reads the current unit level
for both the power product and stat adjustment. It does not use the loop
counter as a hypothetical level.** The alternate full64 factor is loaded
from `00544D28`, and a strict comparison keeps the greater result. In retail,
the two factors contain the same64-bit value just below0.8. The fixtures also
vary the alternate factor to exercise the conditional maximum update.
Unity instead advances hypothetical level/power across this loop. Importing
that HD implementation would alter original PS2 behavior.

Flag20 magic uses the native0.75 multiplier and **floating**50.0 divided by
`LHUlevel+10`, followed by the originalAF2 coefficient when the bit is clear.
Its two real support-ratio diagnostics and final conversion are retained.
The comparisons exercise **2,976 native magic-loop iterations** and
**6,336 C.LT.S comparisons**. The condition bit and preserved FCSR bits are
checked; arithmetic exception flags and timing are outside the value model.

Magic healing resolves both units even though the target value is unused,
obtains source ratio5 and actual parameter2, then consumes one real default
RNG call with bound8. It forms the wrapping word numerator
`parameter2*4 + LHUlevel + random`, divides by10.0, multiplies the lowword
power and support ratio in original order, and converts the result. Its real
mixed diagnostic varargs contain the raw power, software-double ratio and
sign-extended result. **256 real healing RNG calls** are covered; their
state changes are included in full RAM comparison. Unity's visible call
order differs, which is another reason to retain the PS2 instructions.

The HP power evaluator obtains source ratio4 and target ratio7. Flag20 uses
actual `datGetBaseMaxHp` and the enemy coefficient/correction path; other
units read **unsigned stored maxHP at +8** and use the player coefficients.
The flag20 correction is floating50.0/(level+10), and the originalAF2 gate
remains. Both skill and the resolved target unit value are otherwise unused.

## Evidence and integration

Unity roles are reviewed at `182644890`, `182644C10`, `182648F20`,
`1826494F0` and `1826499E0`, respectively. All five bodies decompile with
no opaque lock stubs or lock calls. Managed layouts, difficulty configuration
and the advancing-level magic loop differ; these are semantic roles, not
byte-identical functions or proof of original C typedefs.

The [DDS battle-table documentation](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
at revision `bec33411543cdc487bad9debdf758f0090a2242c` supplies contextual
magic-base/limit and calculation-coefficient vocabulary. Its action rows
are0x38 bytes, whereas original Nocturne uses **0x3C** here. The signed
field widths and offsets come from native loads, not a layout transfer.
The [randomizer's USA research notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
at revision `f74e85c0f632b751eaf278046884961c618c8541` identify the supported
`SLUS_209.11` build. Sources, content hashes, native coefficient bytes and
the checked magic-loop instructions are recorded in
`battle-power-community.json`. RAM `003D7998` maps to ELF file `002D8998`
for the original checked segment. No game patch was applied.

All111 native COP1 sites, including the actual ratio dependency and
branch-delay arithmetic, are body/opcode pinned. The original interpreter
also checks **F25 preservation**, in addition to the existing integer,
F20..F24, GP, SP, RA and zero checks. The new optional libc boundary records
only kernel operands/results and synchronous CPU primitives. No game or
library result is replaced. The actual diagnostics use a separate bounded
stdout context/buffer, with real allocation/cache behavior; **39,168 ordered
kernel/CPU trace words** agree. Full declared RAM, raw64 returns, Status,
processor primitives and VM traces also agree.

All five Ghidra interfaces are saved in the existing working project and
independently reopened. Five current selected exports decompile and merge
into the8,979-entry inventory. Strict complete-span DDS search leaves the
four formula bodies unresolved. The20-byte tail wrapper has147 unconstrained
shape candidates, so no selected counterpart is promoted. Several already
known library dependencies remain separate candidates.

The existing support/affinity/targeting/filter/work cohorts pass **13,696
comparisons again** against their current rolling captures after test routing changes.
Their cases are retained in the original reports and are not counted again.
No checkpoint, duplicate capture, new full-suite run, physical IO/gameplay
or matching-executable result is claimed. Bounded backed indices, signed
parameters, level/cap boundaries, dirty argument lanes, conversion extremes,
AF2/flag20 branches, real RNG, valid string stdout and finite loops are
covered. Arbitrary malformed pointers/cache/heap, private stack aliases,
unbounded loops and arithmetic FCSR flags/timing remain unproved.

Current source hashes agree across **109 focused reports**: **1,440 unique
integrated routines**, **218,853 focused cases** and **681,537 aggregate
cases**, including the historical462,684-case full run. The direct AI frontier
has **13 unresolved bodies /8,312 bytes**, with no missing exports. Continue
hit/HP/MP/status/support estimates `00266130`, `00266350`, `00266878`,
`00266D60`, `00267180`, `00268030`, then estimator `00268F68`, scorer
`00286B68`, single/group and automatic targeting. The existing minimum-bound
raw Ghidra switch-rendering limitation remains separate from tested source
recovery.

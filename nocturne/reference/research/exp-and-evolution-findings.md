# EXP, unit construction and evolution

Twelve additional PS2 routines now compile and pass **5,184** comparisons against
their original ELF instructions: four EXP routines contribute 3,584 cases and
eight unit/evolution routines contribute 1,600. The complete source suite passes
**83,997 cases across 131 routines**. Ten new HD counterparts bring that ledger
to 154; two new game routines use chosen PS2 aliases in a separate ledger.

## EXP

`src/exp.c/.h` reconstructs base EXP at 00223628, scaled EXP at 00223668, next-level
threshold at 00223728 and level-up count at 00223928. `next-exp-leads.md` records
all 104 original words, body hashes, native signatures and coefficient addresses.

The base wraps the signed32 cube through two MULT/LO operations. It then performs
the original conversion, ordered multiplication by A, addition of minus 5 and
integer truncation, rejecting signed-negative results. The scaler retains the
flag4 shortcut, direct unsigned descriptor-level byte, saved factorB-C*D, two
separate integer truncation boundaries and ancestral EXP addition. The wrapper
passes stored FFFF as requested 65536. Count uses the real custom copier, unsigned
threshold comparison and previous-level 255 cap; it preserves the caller unit.

| Base level | PS2 original-instruction result under EE value model | HD integer formula |
|---:|---:|---:|
| 10 | 1414 | 1415 |
| 100 | 1419994 | 1419995 |
| 255 | 23545544 | 23545547 |
| 256 | 23823638 | 23823641 |

The PS2 inputs at 0054e434/38/3c have words3fb5c28f,3c8b4395,402ccccc. B is one
encoding below ordinary 2.7f. Replacing the original operations with the HD
integer formula, ordinary host float or a simple rounding-mode change loses
behavior. In particular, the EE multiplier's carry-save correction preserves
operand-order effects. See `ee-fpu-exp-model.md` for pinned primary evidence.

The host value provider and Java primitive model pass 172 published PS2 capture
cases and140,000 Java/C probes. These are separate evidence classes; Java/C
agreement tests implementation consistency of the same research algorithm.
Only low32 result words are validated. FCSR flags, timing, traps and other COP1
operations remain outside this model. An actual game/console run is unperformed.

The isolated language replaces only five COP1 value constructors and DIVU;
original game call bodies execute intact. The harness copies `.lit4` and asserts
the original coefficient bytes, preserves saved F20 in every EXP case, and compares
whole unit/global buffers and read-only descriptor/coefficient data. The initial
run that omitted `.lit4` is retained as invalid evidence, not counted in progress.

`ee-fpu-pcode-audit/report.json` also passes: 29 byte-decoded original COP1 sites,
15 value sites with exact operand order and four-byte widths, five synthetic
destination aliases and 111 single-instruction executions from published anchors.
Sentinel FCSR preservation checks the value-model contract only.

## Unit and evolution

`src/unit_neighbors.c/.h` reconstructs the supplied-level skill builder00222828,
evolution attention/cancellation/target-level/required-level queries002230a0,
00223110,00223180,002231f8, default unit constructor001fee68, full unit clear
001ff050 and evolution copier002233d0. The draft manifest contains complete body
hashes and native references; two descriptive aliases do not assert original names.

Default construction clears all 236 bytes, loads unsigned descriptor level and
six signed default parameters, fills HP before MP, then builds supplied-ID skills.
The unsigned level builder includes skill0 and duplicates and uses the existing
24-byte partial skill clear. Attention uses type 7 and `required <= low8(level)`;
cancellation uses type 5 and strict `<`. The target getter reads the selected
descriptor's signed level; the other getter reads the event's signed level.

Evolution copies to aligned scratch, propagates flag 200 before capturing the
old flags, preserves old uniqueID/priorID, adds EXP with low32 wrap and stores
ancestral EXP. It appends each old skill whose real inheritance rate is nonzero,
without a random trial. The partial clear leaves upper 12 skill slots intact until
overwritten; final copy recalculates resources and fills both. Managed HD layouts,
full-array clears and edition-specific table remaps are port differences.

Comparisons cover all 24 event positions, no/first/later matches, equality,
unsigned high-bit eligibility versus signed getters, skill0/duplicates, raw padding,
flag/history/EXP boundaries, guarded buffers, both word-aligned residues0/4 modulo8,
disjoint copies and 24 exact-self evolution cases. Real clear, copy, resource and
inheritance-rate callees execute. Skill counts stay within 24 and divisors are
nonzero. Arbitrary overlap, byte misalignment and invalid backing are unclaimed.

`shared-smt-signatures.tsv` now records both EXP and evolution fingerprints.
Offsets, constants, layouts and edition gates must be checked again in each
other SMT executable; no cross-game mapping is claimed.

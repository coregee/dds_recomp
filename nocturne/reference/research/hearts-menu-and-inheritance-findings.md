# Menu, stats, stock and inheritance recovery

These eighteen connected routines extend the recovered Magatama and unit modules. Addresses and layouts refer to the inspected `SLUS_209.11` ELF. Native HD code provides counterpart names and algorithms; original PS2 instructions determine field widths, tables, side effects and return values.

| Recovered group | PS2 entries | Source |
|---|---|---|
| Future-skill list and menu | 221ef8, 220508, 232920, 232cc8 | `src/hearts_menu.c` |
| Classification, stats, membership and copy | 221f20, 221e70, 221d00, 221d70, 220728, 1fef20 | `src/rst_stats.c` |
| Skill construction, stock queries and inheritance | 1ff070, 222788, 2228d8, 222928, 222aa0, 222b70, 222bb0, 222bf0 | `src/stat_neighbors.c` |

## Future skills and icons

`rstSkillInfo_PS2` occupies 74 bytes: signed count at 0, twenty-four unsigned target levels at 1, an untouched padding byte at 25, and twenty-four ushort skills at 26. NULL unit leaves the entire output untouched. Otherwise the builder resets only count and writes appended entries; unused slots and padding remain unchanged.

For the player, the builder scans the remaining eight Hearts slots from the global low-nibble learned count. It appends nonzero, unowned skills without a level test. For demons, it directly indexes the 102-byte row at `333cf8 + ID*102`, scanning twenty-four events after six unknown prefix bytes. It selects type 1 when `hensinmae==0`, otherwise type 6, and requires signed entry level greater than unsigned unit level plus signed 8-bit offset. This branch can append skill zero. The unit fields are reread inside the loop, matching the original loads.

HD widens the offset to 16 bits and adds skill-165 event gates and an edition-specific C0-to-BF table remap. Those changes are absent from the PS2 routines. The membership wrapper has an uninitialized stack-count path for NULL unit; its recovered comparison contract requires a non-NULL unit.

The menu selection byte is at `+31`; it searches twenty-seven physical position rows and keeps the first match to the unsigned equipped byte at global `+1cfa`. It invokes the ID getter twice per consumed row. Icon initialization uses twenty-five 52-byte payloads beginning at menu `+1278`. The partial C menu view ends at `178c`; the original parent allocates `1f8c` bytes. Padding and unrelated menu bytes are preserved.

Owned icons use the first future-skill target: unsigned target equal to player level+1 gives movement 2; target at most level+4 gives movement 1; otherwise 0. Hearts ID 1 with exactly one future skill and event 8c1 clear suppresses that movement. Initialization consumes exactly fifty raw default-RNG draws, two per icon, each masked to 31. HD adds a history wrapper. PS2 color constants remain their original raw values; the HD rendering meaning is unverified.

## Classification, stats and full-unit copy

Classification counts mastered owned descriptors with flag classes 1, 0 and 4 in three byte buckets, then compares signed bucket values. Equal class-1/class-4 counts yield class 0. Class 0 also wins when its count exceeds both others; otherwise the larger class-1/class-4 bucket wins. Other descriptor classes still contribute to the separate mastery tier: mastered count below 6 divided by 2, 6..11 gives 3, 12..24 gives 4, exactly 25 gives 5. The tier pointer may be NULL. Numeric classes and races are recorded without inventing English labels.

Player `cmbGetParamBase` subtracts the signed effective equipped-Hearts parameter from the raw signed unit parameter and returns the full integer. Values +255 and -255 must survive. `cmbGetParam` returns the raw player byte without that subtraction. Both demon branches use existing `datGetParam`, preserving its flag, status and 1..40 clamp rules.

Custom demon copy transfers all 236 bytes, including unknown gaps, as seven 32-byte load-before-store chunks and a twelve-byte tail. It recalculates maximum HP/MP, stores their truncated ushort values, clamps unsigned current resources against those stored values, and sets flag 1. Tests cover disjoint and exact-self records with addresses 0 or 4 modulo 8. General partial overlap and arbitrary byte misalignment remain outside the contract.

`copy-pcode-audit/summary.json` independently verifies the fresh comparison program's zero pairing context and all twenty separate LDL/LDR/SDL/SDR merge instructions. Their masked P-code was not collapsed into paired accesses. This checks the instruction model; it does not validate hardware alignment exceptions.

## Skill clear and stock queries

PS2 `cmbClearSkill` passes **24 bytes**, not 24 elements, to the original clear routine. It clears only skills 0..11, then resets the ushort count. HD clears all twenty-four managed elements. Default-skill construction subsequently appends every type-1, level-0 event from the supplied ID's row, including zero IDs and duplicates. Untouched upper slots retain their prior bytes.

Stock search uses flag 1 and ushort ID equality; flag 4 does not exclude a match. Count uses flag 1 with flag 4 clear. Both consume unsigned 8-bit counts and return signed 8-bit results. Search returns an index relative to its base pointer; HD adds a managed-array start index. Zero count avoids reading the pointer. Comparisons with separately allocated arrays through 255 entries verify narrowing and signed returns without claiming that the global stock has that capacity.

## Inherited-skill tables and rate

| Partial data | PS2 base / stride | Confirmed fields |
|---|---|---|
| Skill descriptor | 3d6998 / 8 | Signed attribute byte +0x00, ushort form +0x04 |
| Demon descriptor | 3497c0 / 60 | Unsigned level byte +0x05, signed inheritance type +0x26, ushort form +0x28 |
| Level rules | 339658 / 4 | Ushort skill +0x00, unsigned level +0x02; exactly 227 scanned rows |
| Score matrix backing | 3399e8 | Sixteen searched column keys, twelve legitimate data rows, original adjacent bytes |

Motion compatibility tests only the **lowest set skill-form bit**. Thus skill form 3 with demon form 2 returns zero even though the masks intersect. Level lookup returns the first matching rule or 1 if absent.

Score lookup narrows its keys to signed shorts. Missing attribute gives column index 16; missing type gives row index 13. An examined row at index 12 is zero padding after the twelve legitimate rows. The result byte is `backing[36 + 2*column + 34*row]`, reaching offset 510. The binding retains a 512-byte raw span so these original reads into neighboring data remain reproducible. HD clamps missing keys to the final legitimate row/column. In shipped bytes, attribute 11/type 0 returns 118 and attribute 11/type 32767 returns 135; those are adjacent-data reads, not extra score rows.

Rate obtains the score before the motion gate. Compatible forms return low8 of `min(99, low8(score / divisor) + unit_level - descriptor_level + 1)`, with a signed upper-cap comparison and no lower clamp. Negative totals wrap on return. Original divisor zero reaches a BREAK 7 sequence, retained as a host trap. The generic division P-code can fail before that instruction, so zero-divisor behavior is statically reviewed rather than claimed as an observed trap comparison.

## Evidence and transfer

The full source suite passes 78,813 original-instruction comparisons across 119 compiled C functions. These eighteen additions contribute 13,349 cases: 2,304 menu/list cases, 6,274 classification/stat/copy cases and 4,771 construction/stock/inheritance cases. The current progress builder verifies the saved source, verifier and vector hashes before counting them as validated. The exporter writes JSON directly to disk to avoid constructing a second gigabyte-scale serialized string in Java's heap.

`recovered-boundary-evidence.json` records a separate read-only inspection of the passing vectors: actual -255/+255 stat returns, rate results 98/99 and negative wraps, shipped missing-header results 118/135, all 256 partial-clear cases preserving upper skills, all four word-aligned copy pairs and 128 exact-self copies.

`function-matches.tsv` records all eighteen native counterparts. `hearts-menu-source-audit.md` and `stat-neighbors-source-audit.md` independently check 288 and 234 original instruction words against the ELF. `rst-stats-validation-plan.md` records boundary and buffer contracts. `behavior-validation.json` is the authoritative compiled comparison result, with addresses and source/verifier/vector hashes; consult its current counts rather than treating static audits as executed tests.

Table strides, signedness, copy partitioning, clear lengths and search predicates are useful shared-engine fingerprints. Re-establish every address, row layout, constant, capacity and return contract in DDS or another SMT executable. No cross-game match is claimed.

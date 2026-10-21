# Next connected stock / inherited-skill recovery leads

Reviewed 2026-10-03 against the complete exported PS2 instruction bodies, their C/JSON exports, native HD C/JSON, IL2CPP method signatures, and read-only ELF table bytes. The eight entries below were absent from the canonical ledger and source at review, and exclude the six entries in `next-rst-leads.md`. This is static research with isolated source drafts: no canonical source, tests, ledger, Ghidra, game, or runtime state was modified.

All eight PS2 exports report `decompile_completed=true`; together they contain 234 instructions / 936 bytes. Each HD counterpart reports `status=decompiled`, `opaque_lock_stub=false`, and exactly one method declaration. The proposed PS2 signatures follow the actual register arguments and inline layouts; managed references and new HD offset parameters must not be copied into them.

| PS2 entry | HD VA / method | Proposed PS2 prototype | Retained identity evidence / next dependency |
|---|---|---|---|
| `001ff070` | `1824106f0` / `fclCombineCalcCore$$cmbClearSkill` | `void cmbClearSkill(datUnitWork_PS2 *unit)` | Clear skill storage and count; directly called by the default-skill and evolution-copy routines. **PS2 clears only 24 bytes, unlike HD's 24 elements.** |
| `00222788` | `18227a220` / `rstCalcCore$$cmbCreateDefaultSkill` | `void cmbCreateDefaultSkill(uint16_t devil_id, datUnitWork_PS2 *unit)` | Clear skills, scan 24 entries in the already reviewed 102-byte demon-skill row, append type-1 / level-0 skills. |
| `002228d8` | `182279ce0` / `rstCalcCore$$cmbChkStockDevil` | `int8_t cmbChkStockDevil(uint16_t devil_id, const datUnitWork_PS2 *units, uint8_t count)` | First occupied slot with matching ushort ID, otherwise -1; same first-match search and flag-1 test. |
| `00222928` | `182279c70` / `rstCalcCore$$cmbChkStockDevilNums` | `int8_t cmbChkStockDevilNums(const datUnitWork_PS2 *units, uint8_t count)` | Count entries with flag 1 set and flag 4 clear; low8 count returned signed. |
| `00222aa0` | `18227b0c0` / `rstCalcCore$$cmbGetKeisyoSkillScore` | `uint8_t cmbGetKeisyoSkillScore(int16_t skill_attr, int16_t inheritance_type)` | Search signed-short column/row headers, return the low byte of their score intersection. Port fallback behavior differs. |
| `00222b70` | `18227b080` / `rstCalcCore$$cmbGetKeisyoSkillMotion` | `uint8_t cmbGetKeisyoSkillMotion(uint16_t skill_form, uint16_t devil_form)` | Find the **lowest** set skill-form bit, return whether that single bit is supported by the devil-form mask; no set bit returns 0. |
| `00222bb0` | `18227af30` / `rstCalcCore$$cmbGetKeisyoSkillLevel` | `uint8_t cmbGetKeisyoSkillLevel(uint16_t skill_id)` | First matching skill in a 227-row four-byte table, return unsigned level byte; otherwise 1. |
| `00222bf0` | `182278680` / `rstCalcCore$$cmbCalcKeisyoSkillRate` | `uint8_t cmbCalcKeisyoSkillRate(const datUnitWork_PS2 *unit, uint16_t skill_id)` | Score, motion gate, level divisor, `(score/divisor)+unit_level-descriptor_level+1`, upper cap 99, low8 result. Depends on the preceding three helpers and two partial descriptor views. |

## Clear and rebuild: 001ff070 / 00222788

The complete 13-instruction clear routine calls `002d4558(unit+3a,0,18)` and writes ushort zero to `unit+38`. Its third argument is a **byte count**: the complete callee performs byte stores on this normally unaligned `unit+3a` path and aligned stores using the same byte-size accounting. Thus it clears `skill[0..11]`, leaves `skill[12..23]` untouched, and resets `skillcnt`; it does not clear inherited skills, attributes, or the rest of the unit. The HD body instead allocates a fresh 24-element Int32 array, zeroes all 24 entries, and resets its Int32 count. A source recovery that adopts HD's full-array clear would fail complete-buffer PS2 comparisons.

The default builder's complete 40 instructions mask its supplied devil ID to ushort, call this clear routine, and select `00333cf8 + 102*devil_id`. It examines exactly 24 four-byte entries after the six-byte prefix: LBU level at row+6+4*i, LBU type at +7+4*i, and LHU skill at +8+4*i. Every type-1, level-0 entry is appended, including skill ID 0 and duplicates. It increments the ushort count and writes the ushort skill at `unit+3a+2*old_count`; there is no ownership test, unit-level test, random selection, or additional capacity check. The maximum 24 appends fits the existing unit's 24 slots. The supplied ID chooses the row even if it differs from `unit->id`.

HD retains the type-1, level-0 selection and 24-entry scan, then appends the widened Int32 skills. It dereferences its managed `ref` unit once; PS2 uses a direct unit pointer. Its `tblSkill.Get` call at `181717dd0` introduces the already reviewed C0-to-BF remap when outside Zensyo mode and event E80 is set. PS2 directly indexes the supplied ID without that remap. Remaining HD array/null checks do not establish PS2 null/index behavior.

Tests worth adding: patterned full-unit buffers to prove the 24-byte clear and preserved upper 12 skills; no / one / twelve / thirteen / all-24 append cases; independent level/type rejection; zero and high-bit ushort skills; duplicates; distinct argument ID versus unit ID; BF/C0 table rows; complete unrelated-unit/global/table preservation. Execute the real clear callee in original-instruction comparisons. Existing memset user-op support should cover that dependency without a high-level replacement.

## Stock queries: 002228d8 / 00222928

Both PS2 bodies walk inline units with stride EC. The search narrows A0 to ushort and A2 to unsigned8; it inspects flag bit 1, then ushort ID+4, and returns the first low8 index sign-extended. Flag 4 does **not** exclude a search match. Zero count returns -1 without reading the unit pointer. Existing callers `001fe388`, `001fe410`, `00202b98`, and `002210f0` pass `global+a54` with count 16, corroborating the start of the existing inline stock view.

The count routine narrows A1 to unsigned8 and increments a byte count only when flag 1 is set and flag 4 is clear. Zero count returns 0 without reading the pointer. It returns the accumulated low8 as signed8; for a deliberately allocated 255-entry array, counts 128..255 therefore become negative. Normal observed global-stock calls use at most 16 entries.

HD adds a `top` argument to the search and returns the absolute managed-array index beginning at top. For a PS2 equivalence comparison, HD top=0 corresponds to the PS2 base pointer; a nonzero HD top corresponds to explicitly pre-offsetting the PS2 pointer, with the PS2 result remaining relative. HD's count signature has `(array,top,count)`, but the inspected native body leaves top unused and scans the first count entries. PS2's actual count arguments are `(units,count)`, not the HD order. Both HD routines use managed object references and bounds/null checks.

Tests: count 0/1/16; no occupied slots, first/last matches, duplicate IDs, matching IDs in unoccupied slots, flag 1|4 accepted by search but excluded by count, high-bit IDs and untouched full arrays. If testing byte-count wrapping beyond 16, allocate the corresponding full array and label it a PS2 query contract rather than a global-stock capacity claim.

## Inheritance helpers: 00222aa0 / 00222b70 / 00222bb0

The score table starts at `003399e8`, with 17 signed shorts per row (34 bytes). Read-only ELF bytes show this column header:

`0, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15`

The first short is the row-label column. The 12 legitimate data-row labels are 1..12. The PS2 accessor compares the remaining 16 header values at table+2; attribute match index i=0..15 supplies offset 2*i. It compares inheritance labels starting at table+0x22 with stride 0x22; row index j=0..11 covers labels 1..12. The returned byte is exactly `table[0x24 + 2*i + 34*j]`; inputs are narrowed/sign-extended to short. The original byte read returns the low8 of a short score rather than a full short.

**Missing-header behavior needs deliberate preservation.** A missing attribute stops with i=16, selecting the following row's label column rather than clamping to the last legitimate score. The type loop examines j=12 as well: at `00339ba2` ELF bytes are three padding zeros, followed by the adjacent skill-form data beginning at `00339ba8`. Type 0 can therefore match that padding location. A wholly absent type stops at j=13 and reads still farther into the adjacent table. The maximum result offset is 510; a raw 512-byte backing span is sufficient to preserve the full accessor's reads, while a typed 13x17-short table alone is insufficient for these malformed-header paths. Do not claim extra score rows merely because the accessor can reach adjacent bytes.

HD's constructor `181eb6d20` allocates exactly 13 rows of 17 shorts: one header and 12 data rows. Its accessor scans starting at column/row 1 and clamps an absent header to the last existing column/row. Thus only legitimate header members directly have the same table-selection algorithm; invalid/missing headers have concrete port differences. Recovery can first use valid attribute/header contracts, then separately preserve the original raw backing for the broader PS2 reads. Duplicate synthetic headers must select the first match.

The motion helper masks both arguments to ushort and scans bit indexes 0..15. On the first set bit in skill_form it returns `(devil_form >> i)&1`. Consequently `skill_form=3, devil_form=2` returns 0 although the masks intersect. This predicate is not a general intersection check; the HD body retains the same lowest-bit selection. Inputs narrowed from wider registers and all 16 first-set-bit positions are useful comparisons.

The level helper scans exactly 227 records at `00339658`, each `ushort skill_id; byte level; byte unknown`. It returns the first matching unsigned level, otherwise 1. Read-only ELF records begin `(1,1)` and `(2,4)`, and record 226 is skill `01a3`, level 6. The HD accessor searches its managed record array and returns the same field/default; constructor `181eb03a0` independently starts with `(1,1)` and `(2,4)`. The fourth PS2 byte is not read. Test first/last/absent/duplicate IDs, skill 0/FFFF, and synthetic levels 0/128/255; divisor 0 is an exceptional path of the parent rather than a safe rate input.

## Connected rate: 00222bf0

The complete 64-instruction body supplies exact partial descriptors beyond the current source views:

| Data | PS2 location | Native HD counterpart field |
|---|---|---|
| Skill attribute | signed byte `003d6998 + 8*skill_id + 0` | skill object+10, signed byte |
| Skill form | ushort same row+4 | skill object+14, ushort |
| Demon descriptor level | unsigned byte `003497c0 + 0x3c*unit->id + 5` | format object+15, Byte |
| Inheritance type | signed short same row+26 | format object+30, Int16 |
| Demon form | ushort same row+28 | format object+32, UInt16 |

It obtains the score before checking the motion predicate. If the predicate returns zero, the parent returns zero without calling the level helper. Otherwise it performs unsigned `DIVU score,skill_level`; divisor zero triggers original `break 7`. It masks the quotient to low8, adds unsigned unit level, subtracts unsigned descriptor level, adds 1, caps only results >=100 to 99, and returns low8. Negative intermediate values are not clamped upward and therefore wrap on return. The valid score/divisor range already fits unsigned8, but retain the explicit narrowing rather than inventing different arithmetic. There is no RNG call, ownership scan, or mutation.

HD preserves the named score/level helpers and inlines the lowest-bit motion test. It uses the same descriptor fields through `datDevilFormat.Get(id,true)`; that lookup's edition/event-specific selection should be treated as an inherited HD difference, not added to the direct PS2 table lookup. The C source can extend the existing partial demon-descriptor view with level/type/form, add an eight-byte partial skill descriptor, and bind the immutable score/level tables. It does not need the large fusion or result state machines.

Meaningful comparisons: incompatible form yields 0; all first-set-bit positions, including contradictory higher bits; each legitimate score row/column and every shipped skill-level row; unit levels below/equal/above descriptor level; cap boundaries 98/99/100; negative intermediate wrap; synthetic divisor/score values in a nonzero-divisor contract; complete unit/global/table preservation. Retain some tests with the real three original callees, so table addressing and signed-header conversions cannot be hidden by hooks. A separate zero-divisor trap case should assert break 7 rather than introduce a clean return.

## Deferred adjacent families

`00222828` is a second clear-and-build routine that selects type-1 entries with unsigned entry level <= supplied unsigned8 level. It is recoverable PS2 behavior, but the checked rstCalcCore method inventory has no separate named native declaration for this third-argument version; retain an unpaired descriptive alias until evidence improves.

The EXP neighborhood `00223628`, `00223668`, `00223728`, and `00223928` also has readable named HD bodies, but merits its own FPU-focused pass. Original constants at `0054e434/38/3c` are binary32 1.4199999570846558, 0.016999999061226845, and 2.6999998092651367. HD replaces the cube-times-float base calculation with unsigned integer `level^3*142/100-5` and converts the scaling factor to an integer percentage; PS2 performs intermediate float truncations. PS2 always subtracts the descriptor-level baseline and adds hensinmaeexp on the non-flag-4 path, whereas HD skips that adjustment for descriptor level 1. These are leads, not a claim of bit-identical HD formulas. The current custom-copy recovery is a dependency of the level-count wrapper.

## Isolated draft status

Drafts are saved in `analysis/drafts/stat_neighbors/stat_neighbors.c` and `.h`. They reuse `nocturne.h` / `hearts_menu.h`, the existing demon-table binding via its byte representation, and the new demon-skill rows. Three proposed additional host bindings cover the eight-byte skill descriptors, 227 four-byte inheritance-level rules, and 512 raw bytes beginning at the score-table base. The draft header asserts all new sizes/offsets and documents argument narrowing, negative scalar keys, raw missing-header reads, and caller backing contracts. The eight C functions pass MSVC 2022 C11 syntax checking with `/W4 /WX /Zs` and the canonical `src` include path. No original-instruction behavior comparisons or recovered-routine counts are claimed by that check.

Evidence: PS2 `analysis/ps2/whole-program/functions/{001ff070,00222788,002228d8,00222928,00222aa0,00222b70,00222bb0,00222bf0,002d4558}.asm/.c/.json`; native `pc/ghidra/corpus/{1824106f0,18227a220,182279ce0,182279c70,18227b0c0,18227b080,18227af30,182278680,181717dd0,181eb6d20,181eb03a0}.c/.json`; `pc/il2cpp/script.json`, `pc/metadata/game-methods.tsv`, and read-only ELF PT_LOAD-mapped bytes from `game/SLUS_209.11`.

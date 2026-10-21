# Stock and inherited-skill recovery

Thirteen more PS2 routines have reviewed native HD counterparts and compilable C in `src/unit_batch.c/.h`. All 3,328 new original-instruction cases pass; the complete source checkpoint is 158 functions and 94,113 cases (1.768% of 8,935 recognized functions). These routines reuse the established 236-byte unit, global stock list, descriptor/event tables and recovered copy, clear, ownership and rate dependencies; no new table binding is needed.

| PS2 entry | Recovered interface | HD native address |
|---|---|---|
| `001fdda8` | `cmbGetKeisyoSkillEndIndex` | `182411f40` |
| `001ff0a8` | `cmbClearKeisyoSkill` | `1824106d0` |
| `001fed00` | `cmbAddSkill` | `18240deb0` |
| `001fea98` | `cmbGetEmptyStockIndex` | `182411ee0` |
| `001fead8` | `cmbGetStockDevilIndex` | `182412580` |
| `001ff178` | `cmbDeleteUnitFromStockList` | `182410cb0` |
| `001ff1f8` | `cmbAddUnitToStockList` | `18240df70` |
| `001ff218` | `cmbDeleteDevilFromStock` | `1824109f0` |
| `001ff298` | `cmbAddDefaultDevilToStock` | `18240db40` |
| `001ff328` | `cmbAddCustomDevilToStock` | `18240da70` |
| `001ff3b8` | `cmbCalcTotalKeisyoSkillRate` | `18240f240` |
| `00222a28` | `cmbChkLevelUpEvent` | `1822796e0` |
| `001fe9e0` | `cmbChkIkenieIllegalDevil` | `1824103d0` |

The level-event method belongs to `rstCalcCore`; the other twelve belong to `fclCombineCalcCore`. `function-matches.tsv` records the evidence and platform differences. `drafts/next_unit_batch/body-evidence.json` pins the original ELF, complete native references and saved instruction bodies. All 308 listed instructions and four omitted internal NOPs were independently re-encoded against the ELF: 1,232 listed body bytes, 1,248 enclosing span bytes. The missing NOPs are at `001fddcc`, `001fed4c`, `001feabc` and `001feb0c`. Enclosing spans must not be confused with Ghidra's summed body sizes.

## Skill and stock predicates

The inherited end query returns the first zero among all 24 halfwords at unit offset `0x86`, or signed byte `-1`. Clearing calls the original recovered `ps2Memset` for exactly 48 bytes and preserves the following 24 attribute bytes at `0xb6`. Neither operation uses the normal skill count.

Normal skill insertion first calls the actual ownership query over the declared count. A duplicate returns `-2`; otherwise only the first eight normal slots at `0x3a` are considered. The first zero receives the low 16-bit skill, the halfword count increments, and the signed slot index returns. Eight occupied slots return `-1` even when later backed slots are empty. Skill zero and an initial count of 24 retain the original behavior, including a successful count increase to 25 when an early hole is available.

Empty-stock lookup requires the entire flag word to be zero, regardless of ID. The separate stock-ID lookup accepts any nonzero flag, including flag 4 alone. Both scan an unsigned byte count with stride `0xec` and return a signed byte index. Thus a backed match at index 128 returns `-128`, and index 254 returns `-2`. Count zero reads no stock pointer and permits NULL. Deliberately backing 255 records establishes these widths, not a global capacity of 255.

## List and wrapper ordering

The global byte list begins at `0x1914`; its signed 32-bit count is at `0x1924`. Deletion copies each source byte to its compacted position before reloading the global pointer, source byte and count. It compares an unsigned stored byte with the signed query: stored `0xff` does not equal query `-1`. It always decrements the count exactly once, including absent values, duplicate values, and zero or negative counts, and leaves stale tail bytes. Negative counts skip the loop and retain the original low-word decrement, including `INT32_MIN` wrapping to `INT32_MAX`.

Append writes the byte at the old count before storing count plus one. Successful insertion wrappers append signed low-byte `index - supplied_count + 16` before executing the real default construction or custom copy. The deletion wrapper uses the flag-1 stock query, performs list deletion first, then clears the entire selected unit; success returns `-1`, failure returns zero. All three wrappers test the signed index, so a found slot 128 follows their failure branch.

Custom-copy sources include a disjoint unit, another stock record, exact self, and a global stock record. A complete work-backed source image over the stock list also makes append-before-copy ordering observable: the append and count store modify bytes subsequently read by the real copy. The copy reads source representation bytes, and its resource calculations use the copied destination. Partial record overlap and arbitrary byte misalignment are outside the recovered record-copy contract.

Positive list-deletion counts are constrained by the established 16-byte backing; append requires old count 0 through 15. The source introduces no capacity checks or malformed-loop repair. Count values at least 128 can make the original signed-byte deletion loop nonterminating and are not host comparison inputs.

## Rate, level events and descriptor flags

Total inheritance rate scans all 24 nonzero inherited slots, including duplicates and entries after holes, and calls the original recovered rate calculation for each. That helper's final `ANDI 0xff` makes contributions unsigned. The sum is 0 through 6,120; the saved generic decompiler's `char` cast would corrupt contributions at least 128. Synthetic table fixtures retain real lookups and nonzero divisors.

The level-event query captures the unsigned unit ID and low byte of level, then scans 24 four-byte entries at row offset 6 in the 102-byte demon table. Raw level equality alone selects events, irrespective of type or skill. The result is the address of the first matching entry, or NULL. An optional output receives one byte containing the total number of matches after all input reads. That output may alias one mutable unit byte. The HD method instead returns a managed array, records the first index in managed state and writes its output unconditionally; those port interfaces are excluded from the PS2 source.

The sacrifice exclusion predicate reads the unsigned race byte at descriptor offset 4. Race zero returns one without reading flags. Otherwise descriptor flag `0x20` decides the result. The existing 60-byte descriptor's unknown first four bytes are read through unsigned character representation, avoiding an incompatible struct cast. No English interpretation of race categories is inferred.

## Instruction comparisons and saved analysis

`tooling/ghidra/StockInheritanceVectors.java` generates 3,328 cases, 256 per routine. `tests/compare_stock_inheritance.py` preserves original relative pointer offsets in one aligned 64 KiB arena and reuses the main suite's table, work and RNG allocations. Comparisons include every arena byte and guard, complete global work, default RNG, table contents through hashes and bound pointers. Event results normalize to table offsets or NULL rather than comparing host pointer bits. Expected state comes from execution of the original ELF, with real recovered dependencies executed in both programs. `stock-inheritance-validation.json` records this subset of the canonical result: 64 NULL event outputs, 128 unit-byte output aliases, 29 successful work-list source aliases and total-rate results spanning 0 through 6,120. These cases are included in the 94,113 total.

Fixtures include every first matching event slot, signed indexes 127/128/254, normal-skill holes and duplicate ownership, all 24 inherited slots, count-zero NULL stock, negative list counts, absent/duplicate list values, real construction and copy side effects, optional event output and unit-byte aliases. A separate disposable arithmetic/byte model also compared these 3,328 fixture cases with C to check the adapter; that is fixture-development evidence, not an additional original-instruction or hardware count.

The saved PS2 snapshot is `backups/SLUS_209.11-2026-10-03-211811.gzf`, SHA-256 `e97f3f788e08d67274b3237832e821c69024712f00a943a802a4ec777d06dce8`. It contains 174 reviewed HD counterparts and the new four-byte event-entry type. The existing 25 library register interfaces pass the snapshot ABI audit. All 8,935 recognized functions were freshly exported with corrected unsigned DIVU and no decompiler failures. The open PC analysis transaction remains active and has been preserved.

These routines supply transfer candidates for other SMT PS2 executables. Each game's original instructions must independently establish unit and global offsets, table extents, signed return widths, flag predicates and side-effect order before reusing the implementations.

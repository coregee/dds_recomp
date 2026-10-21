# Event and target cursors

Seven recovered functions in `src/rst_event_cursor.c/.h` add **5,888 passing original-instruction comparisons** and 924 original body bytes. All 231 complete-span instruction words independently re-encode against the unchanged ELF. The complete checkpoint is **238 C functions / 173,084 comparisons**.

| PS2 entry | Native reference | Function | Cases |
|---|---|---|---:|
|0021f788|1822840e0|rstChkLevelUpTarget|512|
|0021f7d8|1822841d0|rstChkResultEntry|768|
|0021f838|182283f90|rstCalcLevelFromExp|1,024|
|0021f898|182283ec0|rstCalcExpFromLevel|512|
|002203d0|1822812a0|rstSetCurrentDevil|1,024|
|00220860|18227c330|rstCalcEventInfo|1,024|
|00220ba8|182280820|rstGetDefaultSkill|1,024|

## Original behavior

Target eligibility checks flag1 and status800 before calling the real EXP/count chain; rejected paths do not read descriptor rows. Entry eligibility scans all 16 physical EC-stride units, independent of stock-list order. Level-from-EXP subtracts the current EXP modulo32 and adds the actual count to the original low-byte level. EXP-from-level retains the complete signed32 request.

Current-demon selection follows the 16 signed stock-list bytes instead. It increments signed cursor72 before each lookup, skips negative entries, executes the real count setup and parameter/resource query, and stores the original32-bit unit pointer only after success. Exhaustion returns0 and preserves the old pointer; successful outcomes return1 or2. Stock_count is unread.

The event helper counts all matching level entries and returns the first pointer. The PS2 iterator reads consecutive four-byte records from that pointer using signed index21. It does not refilter intervening records when matches are noncontiguous. Exhaustion clears count20 and advances the real preview level to the current-level or99 boundary. Default-skill selection accepts type1 for an unevolved unit and type6 for an evolved unit, consumes other types, and uses the real owner/count query. An already-owned accepted event decrements byte1B modulo8 before continuing.

The partial result view proves accesses at1C/20/21/22/72/16C and the full236-byte inline preview170..25B. It shares the existing result owner. Host address conversion maps original unit and table pointers to backed owners without supplying dependency outcomes. Output is NULL, a complete disjoint ushort, or proposal22; pointer/count/index overlap variants remain outside the fixture contract.

## Validation and capture provenance

Fresh fixtures cover all16 physical/list positions, first successes and exhaustion, raw32 EXP values, real private-copy/count/resource calls, all256 signed event indexes, cap99 boundaries, contiguous/noncontiguous event rows, negative types, NULL/proposal output aliases, and real skill-owner outcomes0/1/2. Returns and every captured owner, table, pointer binding and guard are compared. Failure-injection restoration and20 malformed-row rejection probes pass.

The full compiled C regression reran all173,084 comparisons. Its original-instruction inputs comprise167,196 immutable rows from the preserved231-function capture and5,888 freshly captured rows for this batch. Hashes pin55 source and46 verifier inputs, the original ELF, fresh capture manifest and19 capture inputs, prior code/providers, compiled language and unchanged emulator/register setup. Two positive controls pass and14 deliberate drift cases are rejected. The MMI invocation counters describe the baseline capture only.

The guarded extension is `tooling/verify-extended.ps1`; the original full fresh capture remains `tooling/verify-recovered.ps1`. Changes to old code, providers, fixtures, language or engine setup require the full fresh path. Fresh DIVU/COP1 audits,172 published result captures and140,000 Java/C value probes also pass. These are instruction-model and host comparisons, with no PS2 runtime, matching binary or hardware FCSR validation.

Saved annotated project: `ghidra/checkpoints/238-functions/Nocturne.gpr`. Snapshot: `backups/SLUS_209.11-2026-10-04-192213.gzf`, SHA256 `0044f2f757249105d062555193ae4072731ae79aa423ab377e0ed15fbbd15dea`. All46 library ABI checks pass. The refreshed full export decompiles8,935 recognized functions with zero failures.

Evidence: `event-target-cursor-validation.json`, `drafts/rst_event_cursor/canonical-body-evidence.json`, `behavior-validation.json`, and its explicit capture provenance. Three transfer families raise `shared-smt-signatures.tsv` to60. Other SMT executables still require independent instruction/layout checks.

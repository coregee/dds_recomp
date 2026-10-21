# Inheritance queries and PS2 memory/string routines

This batch adds fourteen reconstructed routines: seven HD-supported game queries and seven independently identified PS2 library leaves. All 145 recovered C routines compile with MSVC C11 `/O2 /W4 /WX` and pass90,785 original-instruction comparisons. The new routines contribute6,788 cases:2,048 query cases and4,740 memory/string cases. This is1.623% of the8,935 recognized functions. Hardware/runtime and matching-binary validation remain separate and currently zero.

## Reviewed functions

| PS2 entry | Recovered interface | HD native reference / cases |
|---|---|---|
| `001fedf0` | `cmbChkKeisyoSkillOwner` | `1824104e0`, `fclCombineCalcCore`,256 |
| `001fee30` | `cmbChkKeisyoSkillNums` | `182410480`, `fclCombineCalcCore`,256 |
| `00222970` | `cmbChkEvoNeedFlag` | `182278fc0`, `rstCalcCore`,256 |
| `00222cf0` | `cmbChkDarkDevil` | `182278bd0`, `rstCalcCore`,256 |
| `00222d38` | `cmbChkStockDarkDevilNums` | `182279b90`, `rstCalcCore`,256 |
| `00223398` | `cmbChkEvoDevilLev` | `182278f70`, `rstCalcCore`,512 |
| `002234e0` | `cmbGetPowerUpSkill` | `18227bb90`, `rstCalcCore`,256 |
| `002d4310` | `ps2Memcmp` | Chosen library alias,358 |
| `002d43a4` | `ps2Memcpy` | Chosen library alias,1,126 |
| `002d4454` | `ps2Memmove` | Chosen library alias,1,126 |
| `002d4558` | `ps2Memset` | Chosen library alias,310 |
| `002d5ab4` | `ps2Strcmp` | Chosen library alias,378 |
| `002d5bf8` | `ps2Strcpy` | Chosen library alias,1,146 |
| `002d5d0c` | `ps2Strlen` | Chosen library alias,296 |

Source is in `src/inheritance_queries.c/.h` and `src/ps2_memory.c/.h`. The canonical ledgers now contain161 HD counterparts,25 independent library identities and two chosen game aliases. Library names describe behavior; their original spelling, compiler and source-library version remain unconfirmed.

## Fixed PS2 query behavior

Inherited skills are24 unsigned16 entries at unit+0x86. Owner search returns the first exact match, including skill0, or signed-1. Count scans all24 slots, including values after holes, independently of the normal skill count. Both preserve input and global bytes.

Evolution requirements scan six devil/event pairs and pass the full unsigned16 event ID to the real event-bit routine. A matching set bit continues the scan; a later duplicate with an unset bit still returns1. Dark-stock counting calls the real37-ID membership predicate only when flag1 is set and flag4 is clear. Its low8 result returns signed:128 matching units produce-128. Zero count reads no unit, permitting NULL. Separately backed255-unit fixtures do not establish the global stock capacity.

The evolution level gate returns the signed minimum of `evolved.level-player.level-4` and a limit. Negative signed32 event levels use limit255 and never read stock, permitting stock=NULL. Other values use the original low32 subtraction `99-(stock.level-event_level)`, including negative wrapped limits nearINT32_MAX. There is no lower clamp or byte narrowing. Fixtures include 48 positive-event aliases: player/stock, player/evolved, stock/evolved and all three equal.

Power-up lookup scans exactly55 source/target ushort pairs. First match wins; target0 and an absent source both return0. HD managed null/bounds checks and array lengths do not replace the original PS2 scan counts or inline layouts.

| Read-only binding | Original span | SHA256 |
|---|---|---|
| `g_cmbEvoFlagRequirements` | `00339640`,24 bytes | `e73913ca99c398d0861dafd9c45d9a32333b519230bc563d03ca521e05e9ae98` |
| `g_cmbDarkDevilIds` | `00339ba8`,74 bytes | `ad4138495b22c77d2d0156eb21084582d18bbbb6e39d696bb2a859f16a51411d` |
| `g_cmbPowerUpSkills` | `00339c20`,220 bytes | `339bf5a896b83d15010f81d20f90c30e9b9124b45159ad786f6423ffcf84b1d1` |

The dark table extends10 bytes beyond the previous512-byte score backing, so it has its own complete binding. Query fixtures compare all tables, input units and guards, separately backed stock, global work and RNG state, including complete synthetic table overrides. The saved Ghidra unit view now includes the established growth-parameter,24 inherited-skill and24 attribute fields without overwriting unrelated typed fields.

## Original memory and string behavior

Memory comparisons return exact unsigned-byte differences. Copies return the original destination, including count0. Every byte alignment is supported. Zero-count memory calls permit NULL and perform no memory access.

Aligned `memcpy` with count>=32 loads/stores its first16-byte stage before loading/storing the next16 bytes. Only that entry path gets an8-byte tail. Other paths copy forward bytes. Forward overlap consequently propagates data; replacing this implementation with host libc would lose that behavior. `memmove` selects backward bytes only for `source < destination < source+count`. Fill truncates the value to a byte and uses aligned16-/8-byte stages followed by bytes.

String paths select16-/8-byte blocks from initial alignment, with complete reads through the block containing NUL. `strcmp` retains its initial redundant right8-byte read and equal-block rereads; scalar comparison ends with an unsigned-byte difference. `strcpy` writes through NUL and preserves forward stages; fixtures cover exact self and finite overlap with destination before source. `strlen` uses the original low32 address difference. Tests back and compare the entire4,096-byte arena and guards, including nonzero bytes beyond terminators, all detector/mismatch lanes and every two-pointer alignment pair.

Portable C snapshots preserve stage order and ordinary RAM results, while explicit byte accesses prevent host-libc folding and eliminated self stores. They do not reproduce atomic EE bus transactions. MMIO, concurrent mutation and32-bit address wrap are outside these interfaces; strings must terminate within their readable backing.

## Evidence and validation infrastructure

The query audit checks138 original words/552 bytes. The separate reproducible SDK audit re-encodes all422 words/1,688 bytes and compares compiled C with an independent interpreter of those actual ELF words on12,524 additional probes with zero mismatches. Those probes are separate from the90,785 canonical Ghidra comparisons. Complete body hashes, callers and reproduction instructions are in `drafts/inheritance_queries/manifest.md` and `drafts/ps2_memory/manifest.md`; the independent SDK interpreter and result are retained alongside the latter.

`InheritanceQueryVectors.java` and `MemoryBehaviorVectors.java` execute original instructions in the isolated program. No high-level copy, fill, comparison or string routine is hooked. Seven opaque MMI instruction operations are implemented in the harness: PCPYH/LD/UD, lane-modular PSUBB/W and128-bit PXOR/PAND. Their source semantics were checked against [pinned PCSX2 MMI](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/MMI.cpp). The original PNOR with RS=zero already lowers to generic128-bit negate in the installed processor. All seven callbacks execute in the canonical fixtures; their counts are recorded in `behavior-validation.json`. The independent `mmi-sdk-audit/notes.md` review checks all 40 relevant original MMI words and 70,910 callback/lane-model comparisons with zero mismatches; those model comparisons are separate from routine and hardware evidence. Initial full-width GPR values are defined in the isolated harness, including otherwise unused upper lanes.

Fixtures now stream one row at a time to `analysis/ps2/behavior-vectors.jsonl`, with metadata on the first line. Python compares one row at a time and hashes files through a stream. Successful validation promotes both pending fixtures and report; the prior JSON baseline and failed PNOR-assert export remain preserved. The failure was an overly broad callback-coverage assertion, not a C mismatch. Source, verifier and vector hashes qualify the current145-function result.

The saved PS2 snapshot is `backups/SLUS_209.11-2026-10-03-204301.gzf`, SHA256 `d3352c25a8b7a54f55b3dc790c1ec7fc6597d15831904b829383ca597103d2e9`. Its25 library register ABIs pass; new library pointers/counts occupy the original32-bit EE argument/result registers. All8,935 functions have fresh corrected-DIVU exports with zero decompiler failures. The PC GUI still has an active native analysis transaction and has been preserved.

The review matcher ranks144/161 held-out pairs first, 157 top5 and 158 top10, excluding25 libraries and two game aliases. Its8,109 candidates remain review leads. Memory-stage patterns and the fixed query/table interfaces are shared-SMT candidates; verify each other game's bytes, layouts and tables before assigning identities.

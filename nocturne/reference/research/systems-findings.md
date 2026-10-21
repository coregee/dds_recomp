Current verified checkpoint: **413 functions /462684 fresh original-instruction cases**. [Findings](texture-environment-findings.md) · [Next frontier](texture-environment-next-frontier.md). Earlier checkpoint narratives below are retained as historical records.

# Shared system findings

Evidence is from the inspected SLUS_209.11 ELF and static HD native code. `function-matches.tsv` contains the complete reviewed function ledger, including platform differences. The earlier calculation report remains useful for damage and affinity details.

## Unit and global work

The unit stride is `0xEC`, established by unit initialization's 236-byte clear and stock iteration. The initial 34-byte prefix has been replaced in reviewed prototypes by a partial full-size `datUnitWork_PS2`. Unknown bytes remain untyped. Compendium `SetElem` now proves fixed 24-element skill and inheritance arrays; see [compendium-findings.md](compendium-findings.md) for the instruction ranges and record correspondence. Ghidra keeps conservative partial field views; recovered C contains the proved inline arrays.

| PS2 unit field | Offset | Width |
|---|---:|---:|
| Flags / demon ID | `0x00` / `0x04` | 32 / 16 bits |
| HP / maximum HP | `0x06` / `0x08` | 16 bits |
| MP / maximum MP | `0x0A` / `0x0C` | 16 bits |
| Status / experience / level | `0x0E` / `0x10` / `0x14` | 16 / 32 / 16 bits |
| Six base / skill parameters | `0x16` / `0x1C` | Signed bytes |
| Unique ID / skill count | `0x22` / `0x38` | 16 bits |
| Six mitama parameters | `0x7A` | Signed bytes |
| Twenty-four skills | `0x3A` | 16-bit elements |
| Six level-up parameters | `0x80` | Signed bytes |
| Twenty-four inherited skills / attributes | `0x86` / `0xB6` | 16-bit / byte elements |
| Pre-transformation ID / experience | `0xCE` / `0xD8` | 16 / 32 bits |

The global-work pointer is stored at `0x0054EA20`. With GP `0x00554170`, accesses through `gp-0x5750` resolve to that pointer. Confirmed offsets within its pointee:

| Field | Offset | Evidence |
|---|---:|---|
| Event bits | `0x840` | 128 32-bit words; four bit routines |
| Moon status / raw phase / move word | `0xA40` / `0xA41` / `0xA44` | Byte status and phase; 32-bit movement bits |
| Currency | `0xA48` | Signed add and clamp to 0..9,999,999 |
| Stock capacity | `0xA50` | Demon insertion and stock-full check |
| Sixteen units | `0xA54` | `0xEC` stride, ending at `0x1914` |
| Stock index storage / count | `0x1914` / `0x1924` | Byte indexes and signed 32-bit count |
| Item counts | `0x1928` | ID-indexed bytes; initial clear spans `0xA0` bytes |
| Boss results | `0x19C8` | Forty pairs of signed 16-bit best/last results |
| Reason points | `0x1CEC` | Three type-indexed bytes, capped at 128 |
| Equipped / owned Hearts | `0x1CFA` / `0x1CFB` | Equipping, duplicate checks and ownership list |
| Hearts skill/mastery state | `0x1D3B` | Low nibble learned count, bit80 mastery; bits4..6 unclassified |
| Owned Hearts count | `0x1D7B` | List append count |
| Hearts learned skills | `0x11AC0` | Twelve ushort slots per ID; whole state-byte increment |
| Hearts parameter upgrades | `0x11DC0` | Six unsigned bytes per ID, added then signed8 wrapped |
| Compendium count / records | `0x11E80` / `0x11E90` | Signed count and 184 inline `0xB0`-byte records |

The C global-work view now ends after the compendium records at `0x19D10`, leaving the intervening unknown region explicit. A table row is not permission to treat every later field as fully reconstructed. The HD managed object changes arrays, references, and widths; subtracting its object header is only valid for the reviewed initial unit prefix.

## RNG and status behavior

`sdfGetRand` shifts four 32-bit state words and calculates:

```text
next = ((old1 << 2) | (old0 >> 30)) XOR ((old3 << 1) | (old2 >> 31))
new state = [next, old0, old1, old2]
```

A null PS2 state pointer selects four words at `0x00529BD8`. Float output masks 24 bits and multiplies by exactly `2^-24`. Integer output uses unsigned modulo; PS2 limit zero executes BREAK 7 after advancing the generator, whereas HD returns zero. `dds3KernelCore` contains HD wrappers around the `sdfRand` implementation; those wrappers must not replace the core's identity.

Status overwrite preserves the high nibble and replaces the low twelve bits, except `0x8000` sets its distinct high bit. Status set compares the low twelve-bit numeric value against the incoming unsigned value before replacing it. Converting that operation into ordinary flag OR would change behavior. HP/MP updates perform wrapping 32-bit addition followed by signed lower and upper clamps; the recovered C preserves that order.

## Stock and boss routines

Stock deletion clears one 236-byte unit, shifts the stock-index list, then compacts physical units. `cmpReplaceStockGBWK` preserves an unusual original counter: it increments on empty-slot removal and stops when that counter equals stock-list count. The final shifted-out stock-list byte is not cleared by `cmpDeleteStockListGBWK`.

PS2 `datDelDevil` masks its ID to sixteen bits and tail-calls `cmpRemoveDevilEx`, propagating success 0/1. HD invokes removal but returns the original supplied ID. This is a confirmed return-contract difference, not an inferred prototype adjustment.

Boss-table entries at `0x003FA430` have stride sixteen: availability event bit, new-record event bit, enemy ID, and initial press count. Forty signed-short result pairs live separately in global work. Type zero returns positive best or 999; type one requires the availability event and returns last result, with zero converted to one; other types return the table's initial count. Updates remap enemy `0x3E1` to `0x1D8` and `0x3E0` to `0x14E`, normalize zero press to one, and update best/event only when the new result is lower. HD widens saved results to managed 32-bit array elements.

## Parameter, item and unit queries

`datGetBaseParam` sums signed base and skill parameters, adds mitama only when flag4 is clear, and clamps to 1..40. `datGetParam` forces one for status `0x200` except parameter4. The status-to-attribute function compares whole status values; combined masks generally return -1.

The low-HP predicate uses integer `HP*100/maxHP < 25`; maximum HP zero executes BREAK7. Item counts are unsigned bytes, IDs below `0x70` are full at 99, and later IDs are full whenever nonzero. `datCheckItem` compares the requested signed quantity directly, including nonpositive quantities.

Player level comes from unit0 without the draw-level cap. Stock-full counts flag1 in physical slots4..15 and compares against signed capacity, independently of stock-list count. Unique demon lookup scans all 16 units for active flag1, flag4 clear, flag`0x400` set and an exact unique-ID match, returning the first demon ID or -1. Nine recovered queries each pass 100 original-instruction comparisons with signed-byte, threshold, flag and wider-ID cases.

## Battle, skills and resource calculations

[battle-moon-findings.md](battle-moon-findings.md) records the new event-to-battle-flag map, moon controls, descriptor skills, party lookup, resource bonuses and negotiation HP request. The test suite executes original event, RNG, ownership and software-double calls. Descriptor skills start at table base `0x003497C0` plus `0x16`, with stride60 and eight entries; the complete descriptor/table size is unproved. The battle process-data type is a prefix through its flag at `+0x60`, not a complete layout.

The original MP calculation also identifies [software-double support](software-double-leads.md). Its multiply helper's inferred void return is wrong: original instructions preserve packed bits in V0 for the next conversion. Eighteen double/product/float routines are now reconstructed with independent bit comparisons; [float findings](software-float-findings.md) include the distinct F12/F0 register interfaces and exponent255 behavior.

[Magatama findings](hearts-parameters-findings.md) record the connected ownership/mastery, parameter and skill paths, packed 66-byte descriptor and 8-byte position rows. HD's managed layouts, DLC gates and color constants differ. [Menu and inheritance findings](hearts-menu-and-inheritance-findings.md) extend compiled recovery through future-skill lists, icon initialization, classification/stat queries, full demon copy, stock queries and inheritance rate. They preserve the PS2 partial skill clear, signed parameter returns, 50 raw RNG draws, lowest-set-bit motion test and missing-header reads into adjacent score-table data.

[EXP and evolution findings](exp-and-evolution-findings.md) add twelve compiled routines and original-instruction comparisons. At level 10, the PS2 base threshold is 1414 under the qualified EE value model; the HD integer formula yields 1415. At level 256 the values are 23823638 and 23823641. The distinction includes operand-order-dependent multiplication precision and two integer conversion boundaries. Unit defaults clear all 236 bytes; evolution inherits every nonzero-rate skill without RNG, preserves original flag/uniqueID/EXP history and heals both resources. Eligibility reads unsigned levels while evolution getters return signed bytes.

## Processor correction and test model

The installed `mips.sinc` DIVU body uses `s/` and `s%`. These encode signed P-code operations; [Ghidra's SLEIGH reference](https://ghidra.re/ghidra_docs/languages/html/sleigh_ref.html) defines `/` and `%` as their unsigned counterparts. The workspace correction changes only those two operators and retains sign extension of the 32-bit HI/LO results, consistent with the [PCSX2 EE division implementation](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/R5900OpcodeImpl.cpp). It affects 271 DIVU instructions in 166 currently recognized functions. Hardware division edge cases beyond the tested nonzero divisors still need separate review.

Two packed instructions used by the original memory-clear routine are opaque Ghidra userops. The isolated comparison harness implements PCPYH halfword broadcasts and PCPYLD low-doubleword composition using the lane semantics in the [PCSX2 MMI interpreter](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/MMI.cpp). It executes the original clear/copy instruction paths and records the tested memory regions; it does not substitute the reconstructed stock routines or a host memset for them. Compendium comparisons cover the entire `0x19D10` global-work view, unit and destination record, including unknown gaps. Lossless compression reduces the vector JSON size without omitting memory. Only external printf output is captured through a binding on the full-registry error path.

Five raw-word COP1 value operations now replace generic IEEE arithmetic only in the isolated instruction harness. `ee-fpu-validation.json` separates 172 published PS2 result captures from 140,000 Java/C consistency probes. FCSR, timing and traps are excluded. The original `.lit4` section is copied and EXP coefficient words are asserted before comparisons. The third-party reference and test notices live under `tooling/reference/ps2float`; these processor helpers are not counted as recovered game functions.

## Transfer to other SMT PS2 executables

`shared-smt-signatures.tsv` captures algorithm and call-graph fingerprints separately from Nocturne addresses. Matching DDS should begin with the four-word RNG, event-bit quartet, unit clear/stride, and stock-list operations, then grow into calculation and battle helpers. Re-establish field offsets, table contents, ABI details and return contracts in each game. No cross-game matches are claimed yet.

## Inheritance queries and memory/string leaves

The preceding fourteen-routine batch established a checkpoint of 145 functions and 90,785 cases. `inheritance-and-memory-findings.md` records the seven fixed-table queries, seven independent library identities and portable memory-stage contracts. New read-only spans are339640/24,339ba8/74 and 339c20/220 bytes. Inherited queries scan all 24 slots; dark counts return signed low8; the event-level gate preserves signedlow32 wrap and an ignored stock pointer for negative events. Tests include 48 positive-event unit aliases. Memory/string tests cover all byte alignments, zero-count NULL, overlap and padded terminating blocks through the real original leaves.

That batch uses streaming JSONL export and comparison. Its PS2 snapshot `SLUS_209.11-2026-10-03-204301.gzf` contains 161 HD identities, 25 independent library identities and two chosen game aliases. All 25 library register ABIs pass. Additional actual-word SDK probes are a separate 12,524-case model audit, not hardware validation or part of the 90,785 canonical count. Per-game instruction/table/layout checks remain required for SMT transfer.

## Stock and inherited-skill neighbors

The thirteen-routine stock batch established a checkpoint of 158 functions and 94,113 original-instruction cases, with 174 reviewed HD counterparts. [Stock and inherited-skill findings](stock-and-inheritance-findings.md) record whole-flag versus flag-1 lookups, signed indexes at 128/254, list deletion that always decrements once, append-before-copy ordering and unsigned inherited rates totaling up to 6,120. The level-event query returns the first matching inline entry and optionally writes a byte count after all reads; 128 unit-byte output aliases pass.

At that checkpoint the source/verifier/vector hashes were verified. The saved snapshot `SLUS_209.11-2026-10-03-211811.gzf` includes the four-byte event-entry type and passes all 25 library ABI checks. Backed arrays beyond 16 establish argument/return widths without changing the global capacity contract. Hardware execution and matching PS2 binaries remain unverified.

## Strings, LEB decoding and stock compaction

Eight more SDK routines and the PS2-only stock compactor established a checkpoint of 167 functions and 110,205 passing original-instruction comparisons. [String and LEB findings](sdk-strings-and-leb-findings.md) preserve whole-block reads, the unusual first-block strncpy zero detector and masked variable shifts. [Stock compaction findings](stock-compaction-findings.md) preserve ID-based selection, untouched prefixes and nonblanket tail clearing through the real custom-copy/clear dependencies.

That checkpoint snapshot `SLUS_209.11-2026-10-03-215024.gzf` contains 174 reviewed HD identities, 33 independent library identities and three chosen game aliases, and passes all 33 library ABI checks. Raw export covers all 8,935 recognized functions; compiled source covers 1.87%. The subsequent field batch is documented below.

## RNG and field flags

The RNG/field-flag batch established a checkpoint of 185 functions and 118,033 passing original-instruction cases, with 192 reviewed HD counterparts. [RNG and field-flag findings](kernel-and-field-flags-findings.md) add eighteen routines. The primary ELF GP word confirms sequence/process words at `0054eb80`/`0054eb88` and the LightMa condition at `0054eafc`; the effect word is global work+A4C and runtime flags are `002fbf94`. The original seed XOR/rotate stages differ from the Unity port. Generic masks retain the qualified EE register extension, and the conditional enabled-word load is covered by 32 NULL-proxy short-circuit cases.

The saved snapshot `SLUS_209.11-2026-10-04-081407.gzf` contains the new partial field types and passes all 33 library ABI checks. Compiled recovery covers 2.071% of recognized functions and 22,880 summed original body bytes. Matching binaries and PS2 runtime checks remain outstanding.

## Field selection, process checks and SDK neighbors

The preceding batch established a checkpoint of 202 functions and 131,262 passing original-instruction cases, with 203 reviewed HD counterparts, 39 independent library identities and three chosen PS2 game aliases. [Field selection and process findings](field-selection-and-process-findings.md) add eleven routines and 5,376 cases. They establish signed selection index/count at 0054EB48, signed waits at 0054EB68, the consuming camp byte at 0054FDD4 and full signed automap mode at 0054EE60. Selection scans all 16 physical units independently of stock-list count/capacity; Next wraps32 before comparing signed values. ClearMsg keeps its real Clear call before the runtime update, and wait/camp shortcuts skip their actual subordinate reads.

[SDK case, float-sign and range findings](sdk-case-float-and-ranges-findings.md) add six original library/runtime leaves and 7,853 cases. Case comparison retains signed-loop versus unsigned-final class indexes into exact 384-byte backing. Abs and CopySign transport raw F12/F13/F0 payload bits. Range chains preserve conditional fields, finite backward steps and modular unsigned range tests; the runtime getter reads only its pointer slot. These are descriptive aliases without a claimed compiler/library version.

That checkpoint uses snapshot `SLUS_209.11-2026-10-04-085044.gzf`, SHA256 `0e9d60810475fe03e3641cbd5a504abed201affb6dd824990335f12eff2dd1f8`. It preserves the selection/wait partial types and passes all 39 library ABI checks. At that checkpoint the source/verifier/vector hashes passed progress checks, covering 2.261% of recognized functions and 24,236 summed original function-body bytes. Full raw export still covers all 8,935 recognized functions. Shared fingerprints record these algorithms separately from game-specific addresses, fields and constants; cross-game equivalence, matching binaries and PS2 runtime remain unverified.

## Selection deletion and SDK bit/byte leaves

The preceding deletion/SDK batch established 211 compiled functions and 152,996 passing original-instruction cases, with 205 reviewed HD counterparts, 46 separate library identities and three PS2 game aliases. [Selection deletion](field-selection-deletion-findings.md) adds 2,048 comparisons, retaining ordinal eligibility selection, signed parameter/event qualification, work-pointer reread, first listed ID removal, actual packing and the script wrapper's unconditional1. Duplicate IDs and ID0 can remove a different physical record. The packer's aligned branch is unreachable for adjacent236-byte records; the real unaligned copy and memset paths execute.

[Byte search and bit helpers](sdk-byte-search-and-bit-helpers-findings.md) add 19,686 comparisons. Widening retains all 64 bits of A3 and its read-store-reread alias behavior; byte search uses the real aligned LQ/MMI detector and first-hit rescan. CLZ preserves canonical signed register extension. Trailing-zero removal preserves its write qualification; limb comparison retains exact wrapped count differences and equal0 rereads. Integer-only double predicates retain all sign/payload encodings.

The saved snapshot `SLUS_209.11-2026-10-04-093313.gzf`, SHA256 `5d445ad603a77f9906affed43e5362aa4239094ad09854b6c2cb2a8cb7cbffa9`, passes 46 library register-storage checks, including full 64-bit fourth argument A3. Fresh export still decompiles all 8,935 recognized functions with zero failures. At that checkpoint the source/verifier/vector hashes passed the progress builder: 2.361% of recognized functions and 25,292 summed original body bytes. The six new transfer fingerprints bring the ledger to 46; DDS/other-game equivalence remains unverified.

Those four drafts and the PS2-only mode-zero wrapper have now been integrated and tested in the following checkpoint. Hardware/runtime and matching binaries remain outstanding.

## Skill RNG, weighted growth and result resources

The preceding stats/result batch established 216 compiled functions and 155,940 passing original-instruction cases, with 209 reviewed HD counterparts, 46 separate library identities and four chosen PS2 game aliases. [Stats, skill and result findings](stats-skill-and-result-findings.md) adds 2,944 cases through actual RNG, upgrade lookup, ownership, inheritance, parameter, custom-copy and maximum-resource dependencies. Skill selection retains duplicate candidates and optional late index aliases; mutation retains unsigned byte levels, repeated original-level lookups and all 64 exhaustion draws. The weighted-growth source retains PS2 low-byte cumulative wrapping and return6, while excluding the original uninitialized minimum-minus1 interface. Resource updates preserve private-copy deltas, signed refill gates, store order and final clamps.

The saved snapshot `SLUS_209.11-2026-10-04-104221.gzf`, SHA256 `69b46d856bd201eb7b51fa4272d19b807760bf16ae63e347c0af8d8af2ada11a`, includes the new partial result view and passes all 46 library ABI checks. The complete refreshed export still decompiles all 8,935 recognized functions without failures. At that checkpoint the source/verifier/vector hashes passed the progress checks: 2.417% of recognized functions and 26,716 summed original body bytes. Four new transfer fingerprints bring the ledger to 50; related-game equivalence remains unverified.

Those six callers are now integrated and verified in the following checkpoint.

## Result skill-power chain

The preceding skill-power batch established 222 compiled functions and 161,052 passing original-instruction cases, with 215 reviewed HD counterparts, 46 independent library identities and four chosen PS2 aliases. [Result skill-power findings](skill-power-chain-findings.md) add 5,112 cases through real selection, before-list, chance, ownership, party and mutation dependencies. Original zero-based modulo boundaries and last-eligible party overwrite differ from HD. Every core return path and successful/exhausted mutation are captured; both result views share one owner and preserve the embedded four-byte address.

The saved snapshot `SLUS_209.11-2026-10-04-173849.gzf`, SHA256 `fd12b2e6d58d1f91bc4c6bee97ad48dd868f604dc29d5c42f25f4d6e124a5c21`, preserves the new identities and partial result view and passes all 46 library ABI checks. Fresh export decompiles all 8,935 recognized functions with zero failures. At that checkpoint source/verifier/vector hashes passed progress checks, covering 2.485% of recognized functions and 27,440 summed original body bytes. Three transfer fingerprints bring the ledger to 53; related-game equivalence remains unverified.

## Level and result chain

The preceding level/result batch established 231 compiled functions and 167,196 passing original-instruction cases, with 223 reviewed HD counterparts, 46 independent library identities and five chosen PS2 aliases. Nine level/result routines now add 6,144 passing original-instruction cases in [level and result findings](level-result-chain-findings.md). They preserve all raw level/count bytes, signed preview levels, real EXP/copy/growth/resource calls, exact preview aliases and all four diagnostic arguments.

At that checkpoint all 95 source/verifier inputs and the vector hash passed checks, covering 2.585% of recognized functions and 28,620 summed original body bytes. Four transfer families raise the ledger to 57; no cross-game equivalence is established. Snapshot `backups/SLUS_209.11-2026-10-04-183402.gzf`, SHA256 `e44b7e88de88f7697b29b5f0f50dfdd85f138b427669db6ed4f23bc9c0056153`, passes all 46 library ABIs. The independently saved annotated project is `ghidra/checkpoints/231-functions/Nocturne.gpr`.

## Event and target cursors

The preceding event/target batch established 238 compiled functions and 173,084 passing original-instruction comparisons, with 230 reviewed HD counterparts, 46 separate library identities and five chosen PS2 aliases. Seven event/target cursor routines add 5,888 passing original-instruction comparisons in [event and target findings](event-target-cursor-findings.md). They retain the distinct physical and stock-list scans, signed event indexes, consecutive records after the first match, byte-wrapped level differences and real EXP/resource/skill-owner dependencies.

All 173,084 compiled C comparisons were rerun. Instruction inputs combine 167,196 immutable rows from the preserved 231-function capture and 5,888 fresh event/target rows. Capture provenance pins the unchanged prior code, providers, fixtures, compiled language and engine/register setup, with 19 fresh capture inputs. Two positive controls and 14 drift-rejection probes pass. The MMI invocation counters describe the baseline capture only. `tooling/verify-extended.ps1` supports guarded additive batches; changes to earlier code or capture setup require `tooling/verify-recovered.ps1` for a complete fresh capture.

At that checkpoint all 101 source/verifier inputs and the vector hash passed progress checks, covering 2.664% of recognized functions and 29,544 summed original body bytes. Three transfer families raise the ledger to 60; cross-game equivalence remains unverified. Saved project: `ghidra/checkpoints/238-functions/Nocturne.gpr`. Snapshot `backups/SLUS_209.11-2026-10-04-192213.gzf`, SHA256 `0044f2f757249105d062555193ae4072731ae79aa423ab377e0ed15fbbd15dea`, passes all 46 library ABI checks. Fresh raw export still decompiles all 8,935 recognized functions with zero failures.


## Motion requests and PS2 state leaves

The preceding motion/state batch established 243 compiled functions and 179,228 passing original-instruction comparisons, with 233 reviewed HD counterparts, 46 independent library identities and seven chosen PS2 aliases. Five motion/state routines add 6,144 fresh original-instruction comparisons in [motion and state findings](motion-state-findings.md). They retain the mixed A0/F12/F13/A1 setter ABI, raw float payloads, signed table types, mode-only cancellation and two separately named PS2 flag/state leaves.

All 179,228 compiled C comparisons were rerun. Instruction inputs combine 173,084 preserved rows from the 238-function checkpoint and 6,144 fresh motion rows. Capture provenance pins the unchanged prior code, providers, fixtures, compiled language and engine/register setup, with 19 fresh capture inputs. Two positive controls and 14 drift-rejection probes pass. The MMI invocation counters describe the original baseline capture only. `tooling/verify-extended.ps1` supports guarded additive batches; changes to earlier code or capture setup require `tooling/verify-recovered.ps1` for a complete fresh capture.

All 105 source/verifier inputs and the vector hash pass progress checks, covering 2.720% of recognized functions and 29,784 summed original body bytes. Two transfer families raise the ledger to 62; cross-game equivalence remains unverified. Saved project: `ghidra/checkpoints/243-functions/Nocturne.gpr`. Snapshot `backups/SLUS_209.11-2026-10-04-194553.gzf`, SHA256 `112dbaac328672e69ef2de48ac1b49df1edbb429df469be2cfd41bb96a0bcd93`, passes all 46 library ABIs and a separate saved mixed-motion ABI audit. Fresh full export still decompiles all 8,935 recognized functions with zero failures.

Nine status-model accessor/update drafts in `analysis/drafts/cmp_status_model/` compile strictly but remain uncounted. Static review checks 170 original words, including three unowned table-update entry candidates missed by the earlier discovery scan. The next batch must publish supported function entries and pass fresh original-instruction comparisons before changing the current count.


## Status-model table and vector updates

Nine status-model routines add 12,288 fresh original-instruction comparisons in [model table findings](cmp-model-findings.md). They preserve raw float words, full-width integer conversions, sequential overlapping outputs and the original global-slot widths. Three byte-checked missing entries are saved; the speed updater remains anonymous and outside recovered C pending its real motion dependencies.

All 191,516 compiled C comparisons were rerun. Instruction inputs combine 179,228 preserved rows from the 243-function checkpoint and 12,288 fresh model rows. Capture provenance pins the unchanged prior code, providers, fixtures, compiled language and engine/register setup, with 19 fresh capture inputs. Two positive controls and 14 drift-rejection probes pass. The MMI invocation counters describe the original baseline capture only. `tooling/verify-extended.ps1` supports guarded additive batches; changes to earlier code or capture setup require `tooling/verify-recovered.ps1` for a complete fresh capture.

The preceding model batch established 252 compiled C functions, 191,516 passing comparisons, 242 reviewed HD counterparts, 46 library identities and seven chosen PS2 aliases. All 109 current input hashes agree. Validated source covers 2.819% of recognized functions and 30,308 summed original bytes. Three transfer families raise the ledger to 65. The saved 252-function project contains 8,938 recognized functions; all export successfully, and its model interfaces and 46 library ABIs pass after reopen. Snapshot `backups/SLUS_209.11-2026-10-04-203120.gzf`, SHA256 `5dbde1bfa91bdd52f9e21510cd7b5ef5077f1fa27289f186af113d3fe255868a`.


## PIB record traversal and item sentinels

Four PIB chunk routines add 7,168 fresh original-instruction comparisons in [chunk reader and lookup findings](pib-chunk-findings.md). They preserve unsigned counts, complete-word sentinels, zero strides, raw 32-bit address slots and the real variable-record lookup. The tests execute 65,535-record last-match and exhausted searches; the native GetSize lead is rejected and the first native XOR sentinel is decoded from DLL bytes.

All 198,684 compiled C comparisons were rerun. Instruction inputs combine 191,516 preserved rows from the 252-function checkpoint and 7,168 fresh chunk rows. Capture provenance pins the unchanged prior code, providers, fixtures, compiled language and engine/register setup, with 19 fresh capture inputs. Two positive controls and 14 drift-rejection probes pass. The initial standalone chunk capture lacked canonical name/index metadata and was retained unpromoted; an independent recapture reproduced every instruction input, result and memory byte. The MMI invocation counters describe the original baseline capture only. `tooling/verify-extended.ps1` supports guarded additive batches; changes to earlier code or capture setup require `tooling/verify-recovered.ps1` for a complete fresh capture.

The preceding PIB batch established 256 compiled C functions and 198,684 passing comparisons, with 246 reviewed HD counterparts, 46 library identities and 7 chosen PS2 aliases. All 113 current input hashes agree. Validated source covers2.864% of recognized functions and 30,488 summed original bytes. Two transfer families raise the ledger to67. The saved 256-function project preserves all 8,938 recognized functions, all export successfully, and its four PIB interfaces and 46 library ABIs pass after reopen. Snapshot `backups/SLUS_209.11-2026-10-04-210924.gzf`, SHA256 `b8a2a42eba98560f8b878ffc748989659161970b51fa212b52fca3a1cd76531f`. The speed updater still awaits actual motion allocation, cleanup and channel callbacks.


## Motion callback pointer stores and raw quadword backups

Five motion callbacks add 5,120 fresh original-instruction comparisons in [motion callback findings](motion-callback-findings.md). Two raw-address stores retain reviewed HD roles; three full quadword copies have descriptive PS2 aliases because HD copies reverse direction. One dispatcher boundary is corrected and six net entries are added; all five new interfaces, nine prior model interfaces, four PIB interfaces and 46 library ABIs pass after reopening.

All 203,804 compiled C comparisons were rerun. Instruction inputs combine 198,684 preserved rows from the 256-function checkpoint and 5,120 freshly executed callback rows. Capture provenance pins the unchanged prior code, providers, fixtures, compiled language and engine/register setup, with 19 fresh capture inputs. Two positive guard controls and 14 drift-rejection probes pass. The new cases cover all valid four-byte word-store alignments and aligned quadword aliases. The MMI invocation counters describe the original baseline capture only. `tooling/verify-extended.ps1` supports guarded additive batches; changes to earlier code or capture setup require `tooling/verify-recovered.ps1` for a complete fresh capture.

The preceding callback checkpoint established 261 compiled C functions (2.918% of 8,944 recognized functions), 203,804 passing comparisons and 30,592 summed original bytes. Its 117 certified input hashes are preserved in the 261 archive. That checkpoint had 248 reviewed HD counterparts, 46 library identities, 10 chosen PS2 aliases and 69 transfer fingerprints. All 8,944 recognized functions exported and decompiled with zero failures. At that point key search still required a validated division model; it is now promoted in the 262 checkpoint described below. Historical snapshot `backups/SLUS_209.11-2026-10-04-220150.gzf`, SHA256 `d1118b7200f42e7ff9aee814d53e47d4e125e9811209d005981e57cd26aa679f`.

[Motion key search recovery](motion-key-search-findings.md) is now promoted:66 original words/264 bytes and 8,192 key cases, including backed aliases and raw division. The preserved key checkpoint established262 compiled C functions, 211,996 complete fresh comparisons and 30,856 summed original body bytes. There are249 reviewed HD pairs and 70 transfer fingerprints. [Material motion frontier](motion-material-frontier.md) pins the next real scalar callback chain.

All 211,996 original-instruction rows were freshly captured under the updated six-operation EE value model, and all compiled C comparisons pass. No old vector rows were reused. The capture verifies 141 input hashes before and after execution; the comparison report pins 65 source and 59 verifier files. Fresh unsigned DIVU and COP1 mapping audits pass, including 38 original COP1 sites, 20 value sites and six alias probes. The FPU provider passes 208 published result words and 180,000 separately labelled Java/C probes. Comparison semantics remain in a separate draft; FCSR flags, timing and hardware/runtime execution remain unclaimed.

[Scalar/material motion recovery](material-motion-findings.md) establishes four dirty-flag setters, exact ordered scalar interpolation and real apply/blend key callbacks. At the scalar/material checkpoint recovery was269 compiled C functions, 236,572 comparisons and 31,124 summed original body bytes;253 HD pairs, 13 descriptive game aliases and 72 transfer fingerprints. That269-function suite passed236,572 comparisons:211,996 immutable instruction rows from the 262 checkpoint plus24,576 freshly executed scalar/material rows. All compiled C comparisons were rerun. Exact guards establish unchanged prior engine, setup, provider and all 16 processor-language files; no old expected row is recalculated. The new capture attests23 inputs before and after execution, while the whole comparison report pins 67 source and 63 verifier files. Fresh unsigned DIVU/COP1 mapping audits pass, as do208 published FPU result words and 180,000 separately labelled Java/C probes. Comparison semantics remain a separate draft. FCSR flags/timing/hardware/runtime and matching binary remain unclaimed.

## Material word setters (274 checkpoint)

[Material-setter findings](material-setter-findings.md) add five raw32 setters, preserving the byte+6 flag read before the word store and flag write in the return delay slot. At that checkpoint recovery contained274 compiled functions, 246,812 passing comparisons, 31,224 summed original body bytes, 253 HD pairs, 46 library identities, 18 descriptive PS2 aliases and 73 transfer fingerprints. All 134 current source/verifier inputs are pinned;236,572 prior expected rows remain immutable and 10,240 setter rows were captured freshly. The independent saved 274 project reopens with all new and prior ABI audits passing; all 8,944 functions export and decompile without failures.

[VU transport findings](vu-transport-findings.md) identify truncated quadword transfers and reversed lane aliases. A separate draft passes 11 published anchors, one extra ignored-write case and 16,384 generated comparisons. Canonical language and historical captures are unchanged. Masked/broadcast arithmetic, accumulator inputs, conversions and packed-integer operations still need independent validation before color recovery.

## Packed material-color motion (285 checkpoint)

[Packed color findings](material-color-motion-findings.md) add eleven complete bodies, 321 independently encoded words and 32,768 original cases. At that checkpoint, all 285 routines passed279,580 completely fresh instruction comparisons under corrected explicit VU value contracts;historical 274 captures remain immutable. Recovery covers32,508 summed original body bytes (~3.19% of8,944 recognized functions), with 29 descriptive PS2 aliases and 75 transferable patterns. No new direct HD identities are asserted. Original color packing preserves the half-unit bias, ordered MAC overflow priority, signed truncation and low-byte wrapping. Unity material-node generation returns null in the reference;the next allocator/transform branch requires PS2 reconstruction beyond fuzzy matching.

## Five-word material and pool branch (305 checkpoint)

[Material/pool findings](material-fiveword-pool-findings.md) add twenty complete functions and 34,816 original cases. The new305-function suite passes 314,396 fully fresh instruction comparisons and covers34,128 summed original body bytes. Lazy24-byte material records initialize20 bytes; size-class allocation executes actual page/freed-slot/bump-slot calls and indirect dispatch, with interrupt-state restoration. Five-word stores preserve partial-alias order. Three original callback tables establish both36-byte five-word node constructors and the separate20-byte packedcolor constructor.

The primitive audit found and corrected PLZCW/MFC0 writes to registerzero in an isolated language copy;74,880 decoded value cases pass. General privileged exceptions, IRQ timing/bus effects and console runtime remain unverified. Transfer fingerprints reach 80. At the 305-function checkpoint, the 16-byte scalar save at `002b5388` was missing from the 8,944-function inventory and outside the recovered count. It is recovered in the 326 checkpoint with nine other newly bounded callbacks.

## Material construction, node binding and pool release

The preceding 326 checkpoint contained 326 reconstructed C functions and 404,508 completely fresh comparisons over 8,954 recognized boundaries, with zero raw export failures. [Material construction and release findings](material-construction-release-findings.md) record21 additional functions, 90,112 separate fresh cases and 1,540 independently encoded original bytes. The summed validated body extent is35,668 bytes. The identity ledgers contain254 HD counterparts, 46 library identities and 69 descriptive aliases; the transfer ledger contains 84 patterns.

The 72-byte material constructor clears80 bytes through rounded quadword zeroing, marks dirtyFF, allocates two 160-byte packet buffers, retains five VIF command words andthree80808080 colour defaults, then zeroes its scalar pair. The HD constructor retains the command/default constellation while changing allocation order and managed layout. Pool release handles active/available page unlinking, full-page reopening, empty-page recycling and freed-slot chaining with conditional interrupt-state restoration.

All new mixed A/F custom storage, raw32 return values and separate72-byte material/8-byte source/16-byte quadword views pass saved reopen checks. Earlier64-byte material, 36-byte five-word node, 32-byte node and 12/24-byte class/page views remain intact. The ten new callback bodies are separately byte-gated, closed and nonoverlapping. Exact 305 sources, providers, host DLL and capture vectors are archived; discarded pointer-overlap and signed-ABI fixture runs are retained separately. IRQ timing, privileged exceptions, allocation failure, private stack, hardware execution and matching binaries remain outside the claim.

## Material definitions, lifetime and handle pointers (332 checkpoint)

Historical checkpoint: **332 / 8,954 recognized functions (3.71%)**, **421,404 completely fresh original-instruction cases**, 36,356 summed original body bytes, 254 reviewed HD counterparts, 46 identified library routines, 75 descriptive PS2 aliases and 88 transfer patterns. Saved project: `ghidra/checkpoints/332-functions/Nocturne.gpr`. Full or near-full recovery remains unfinished.

[The six-body findings](material-lists-findings.md) record the original eleven-field parser and exact load/store order, real material release through the pool allocator, packet-header/scalar transport and wrapping reference counts. The parser captures its flags after storing the header, advances its cursor in ascending flag order and rereads the texture array after prior setters. Five scalar words are captured before each lazy getter/setter. Immediate release decrements the material counter before freeing packet 8, then rereads each remaining owned pointer.

New partial Ghidra views describe only the accessed array header, packed definition header, memory handle, packet header and scalar output. Earlier material, motion-node and pool views remain intact. Six new custom A0..A2/V0 raw32 interfaces and all ten earlier audit groups pass saved reopen checks. The six routines add six descriptive aliases and four transfer patterns, with no new recognized boundaries or HD identities. The exact 326 checkpoint remains archived with its 400 artifacts and 404,508 original rows.

## Memory allocation, arrays and immediate material lists (345 checkpoint)

Current verified checkpoint: **345 / 8,954 recognized functions (3.85%)**, **443,420 completely fresh original-instruction cases**, 38,160 summed original body bytes, 254 reviewed HD counterparts, 46 identified library routines, 88 descriptive PS2 aliases and 92 transfer patterns. Saved project: `ghidra/checkpoints/345-functions/Nocturne.gpr`. Full or near-full recovery remains unfinished.

[The thirteen-body findings](memory-array-lists-findings.md) document stable descriptor addresses during real allocate/copy/free relocation, ordered free coalescing, signed halfword array policy and the packed material-list maker. Actual pool page transitions, pointer counts, raw float fields, live post-call reads and RAM aliases are retained. The state-2 pressure path conditionally restores interrupts before its callback and resumes scanning; the fixture calls the actual recovered empty target002b58b8. Arbitrary callback and failure semantics remain outside that proof.

Thirteen new low32 interfaces and eleven earlier saved audit groups reopen successfully. All 8,954 recognized bodies export and decompile. Four new transfer patterns cover extent allocation/coalescing, stable-address relocation, signed generic arrays and material-list lifetime; the ledger contains 92 patterns. Exact preceding 332 evidence retains 899 artifacts and421,404 original rows. Unity new/add/make methods remain structural references with documented PS2 differences.

## Draw packets and ordering records, checkpoint388

Ten original render/order routines retain packet-ID byte writes,28-bit links, payload reads after an overlapping quadword clear, state-slot live rereads and two raw ordering callbacks. [Evidence and limits](render-chain-findings.md) separate neutral PS2 slot names from Unity light/fog role leads.

## Ordering flush and list closures, checkpoint394

Six original routines preserve post-delay callback arguments, live post-call reads, final END byte/tail reread order and distinct node/packet-list interfaces. [Evidence and limits](ordering-flush-findings.md) retain the480 actual callback observations and static16-body DDS cohort.

## Packet/environment closure, checkpoint410

Sixteen routines preserve raw64 GIF arguments, the ninth raw32 stack slot, sign extension, word wraps, live mode/configuration reloads and a separate BSS word binding. [Evidence and limits](packet-environment-findings.md) retain17 saved ABI groups, the full fresh regression and32-body static DDS cohort.

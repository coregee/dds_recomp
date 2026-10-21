# Next rstCalcCore / rstcalc counterparts

Reviewed 2026-10-03 from the existing local PS2 whole-program ASM/C/JSON, native HD corpus C/JSON, `script.json`, `dump.cs`, `il2cpp.h`, and metadata TSVs. The canonical ledger had 126 matches at review start. This batch excludes its entries and the four routines in `hearts-menu-leads.md`. Only this report was written; no source, ledger, tests, Ghidra, game, or runtime state was changed. These are static findings, with proposed instruction-comparison contracts rather than executed comparisons.

## Six directly supported identities

All six PS2 JSON files have `decompile_completed=true`. All six HD JSON files have `status=decompiled` and `opaque_lock_stub=false`. The identifiers below were checked against native behavior and script signatures, not candidate ranks or placeholder method bodies. The sixth is a dependency of the separate protected skill-check parent.

| PS2 entry | HD VA / method | Proposed PS2 prototype | Identifying retained behavior |
|---|---|---|---|
| `00221f20` | `1822798c0` / `rstCalcCore$$cmbChkMasterHeartsStatNums` | `uint8_t cmbChkMasterHeartsStatNums(uint8_t *tier)` | Count mastered owned entries by descriptor classes 1/0/4; return dominant class; derive tier using boundaries 6, 12, 25. |
| `00221e70` | `18227baf0` / `rstCalcCore$$cmbGetPlayerRaceID` | `uint8_t cmbGetPlayerRaceID(datUnitWork_PS2 *unused_unit)` | Call classification/tier helper; tier 0 returns 0; otherwise map three classes into `(tier-1)*3+1/2/3`. |
| `00221d00` | `18227b8e0` / `rstCalcCore$$cmbGetParamBase` | `int cmbGetParamBase(datUnitWork_PS2 *unit, int index)` | Player returns signed raw parameter minus equipped Hearts parameter; demon delegates to datGetParam. |
| `00221d70` | `18227ba50` / `rstCalcCore$$cmbGetParam` | `int cmbGetParam(datUnitWork_PS2 *unit, int index)` | Player returns signed raw parameter without subtraction; demon delegates to datGetParam, inlined in HD. |
| `00220728` | `18227f9d0` / `rstcalc$$rstChkBeforeSkillOwner` | `int8_t rstChkBeforeSkillOwner(uint16_t skill, int8_t level_offset, datUnitWork_PS2 *unit)` | Build future-skill list using equipped Hearts; scan its ushort IDs; return 1 on match, otherwise 0. |
| `001fef20` | `182410730` / `fclCombineCalcCore$$cmbCopyCustomDevilToStock` | `void cmbCopyCustomDevilToStock(datUnitWork_PS2 *destination, const datUnitWork_PS2 *source)` | Copy unit, recompute maximum HP/MP, clamp current HP/MP downward, OR flag 1. |

The PS2 race getter does not consume A0. Its pointer-shaped proposed parameter is supported by existing callers, including `002446b0` passing `global+a54`, and the corresponding HD declaration, which also leaves its `ref datUnitWork_t` parameter unused. A zero-argument behavioral helper is possible, but do not propagate HD pointer-to-pointer parameters into direct-pointer PS2 callers. The race getter explicitly returns unsigned low8. The classification's literal 0/1/4 and future-skill predicate's literal 0/1 alone cannot prove their original return declaration widths; HD metadata supplies UInt8 and SByte respectively.

## Classification and race: 221f20 / 221e70

The full 103-instruction classification routine first clears exactly three scratch bytes through `002d4558(sp,0,3)`. Its complete callee ASM establishes that this is a byte-fill operation on the size-3 path. It then reads unsigned ownership count at `global+1d7b` and signed ownership IDs at `global+1cfb+i`. Each ID is converted to unsigned8 for mastery call `00222140`, then passed as signed8 to descriptor-class call `00221ef8`. Only mastered entries contribute to the three counters:

| Scratch byte | Counted descriptor result |
|---|---|
| `+00` | 1 |
| `+01` | 0 |
| `+02` | 4 |

The class accessor selects `00339e00+66*(int8_t)id`, reads the descriptor Flag byte at row+0 and masks 7. It is already reviewed in `hearts-menu-leads.md`; the master predicate is already canonical. Classes 2/3/5/6/7 contribute to none of these counters, but their mastered entries still contribute to the later independent mastery-count call `00222160`. Ownership entries are counted as supplied, including repeated IDs; there is no deduplication.

Let the three counts be C1, C0, C4. All comparison loads are signed `LB`, while increments store only low8. Return class is 0 when C1==C4, or when C0>C1 and C0>C4. Otherwise return 1 when C1>C4, else 4. Do not use a unique-maximum algorithm: C1==C0>C4 returns 1, and C4==C0>C1 returns 4. The independent signed8 master count M gives tier:

| M under normal count 0..25 | Stored tier |
|---|---:|
| 0..5 | M/2, signed division toward zero |
| 6..11 | 3 |
| 12..24 | 4 |
| 25 | 5 |

The optional output is exactly one byte. The PS2 branch-likely store at `00222094..98` is annulled for NULL, so `tier==NULL` still returns the class without a write. HD uses a managed three-element scratch array with the same class increments, signed comparisons, mastery-call boundaries, and output value, but unconditionally dereferences its `ref byte` output. HD also loads the declared Byte ownership count as signed char in this native body; malformed count values 128..255 are therefore outside the claimed cross-port contract. PS2 loops on LBU count even for such values and keeps byte wrap/sign semantics. Neither routine changes ownership or mastery.

The complete 33-instruction PS2 race getter obtains the classification and tier into a local byte. Tier 0 yields 0. Otherwise it computes low8 `(tier-1)*3 + suffix`, with suffix 1 for class 1, 3 for class 4, and 2 for any other class. Each nonzero exit masks FF; its return is unsigned8. HD preserves this mapping and zero case. Normal tiers yield race IDs 0..15. These bodies establish numeric descriptor classes and the race mapping; they do not establish English alignment/race names.

Meaningful comparisons: enumerate C1/C0/C4 combinations whose total is <=25, checking equal maxima and neutral ties; mix mastered/unmastered entries and classes not counted in the three buckets; include duplicates; test M=0/1/2/5/6/11/12/24/25; compare a NULL tier pointer against the same nonnull input; verify exactly one output byte and unchanged global buffers. Test all class/tier race combinations through controlled classifier results, plus full retained-helper cases. High-bit/malformed counts are a separate PS2-only contract, not evidence of HD equivalence.

## Parameter wrappers: 221d00 / 221d70

Both complete bodies branch on ushort `unit+4` (ID). For player ID 0, both load raw parameter with signed `LB unit+16+index`. The Base wrapper alone reads unsigned equipped ID `global+1cfa`; if nonzero it sign-extends the ID and low8 index, calls already named `002223a0 cmbGetHeartsParam`, and subtracts that signed8 result from the signed raw parameter. The result remains Int32; it is not narrowed or clamped after subtraction. Thus a synthetic negative raw stat is preserved and a negative Hearts bonus is subtracted algebraically. The full-width index chooses the raw unit byte; low8 index selects the Hearts helper. Valid indices 0..5 avoid inventing a broader index contract.

For demon ID nonzero, both pass the original unit pointer and full Int32 index unchanged to canonical `00243ee0 datGetParam`. Its already reviewed implementation uses signed six-byte base/skill/mitama arrays, conditionally excludes mitama for unit flag 4, clamps the sum to 1..40, and applies status `(badstat&fff)==200` to force indices other than 4 to 1. The wrappers do not subtract equipped Hearts parameters in this path. HD Base calls the same named datGetParam; HD Param has its retained implementation inlined.

| Field | PS2 location | HD managed field/location |
|---|---|---|
| ID | ushort `unit+04` | `id`, object+14 |
| Raw parameters | six signed bytes `unit+16` | `param` array, object+28 |
| Skill parameters | six signed bytes `unit+1c` | `skillparam` array, object+30 |
| Mitama parameters | six signed bytes `unit+7a` | `mitamaparam` array, object+68 |
| Flag | UInt32 `unit+00` | object+10 |
| Status | ushort `unit+0e` | `badstatus`, object+1e |
| Equipped Hearts | byte `global+1cfa` | `heartsequip`, global object+a2 |

`script.json`/native Base use a managed reference (`datUnitWork_t **`), dereferenced once; PS2 directly receives its 0xec-byte inline unit. HD Param receives a direct managed object. Both HD bodies add managed null/array checks; PS2 checks neither unit nor index. All wrapper paths are read-only.

Meaningful comparisons: player equipped 0/nonzero; all six indices; negative raw parameters; distinct normal/master descriptor arrays and upgrades; subtraction outside signed8 range, preserving full Int32 result; demon flag-4 branches, signed sums below1 and above40, status200 with index4 and others; verify complete unit/global buffers unchanged. Test the existing datGetPlayerParam counterpart against the Base wrapper on the same player as a cross-check, without confusing the distinct identities.

## Future-list membership: 220728

The complete 32-instruction body masks incoming skill to FFFF and narrows/sign-extends incoming level offset to signed8 (`sll24; sra24`). It reads equipped Hearts with `LB global+1cfa`, then calls only `00220508 rstCreateBeforeSkillList(id,unit,offset,sp)`. The caller allocates a 0x60-byte frame; its list view is the already proved 0x4a-byte payload: signed8 count at scratch+0, ushort IDs at scratch+1a with stride2, and target-level bytes at+1. The predicate never reads the target-level array itself. Count <=0 returns0; otherwise it searches the counted ID prefix and returns literal1 on the first equality, else0. It does not search current unit ownership directly or update learned state.

HD creates a managed `rstSkillInfo_t` and two 24-element arrays, calls the same named builder with the global equipped ID, and scans its SByte count/object+10 and UInt16[]/object+20. It widens `LevelOfs` to signed16, a concrete interface difference. Its result inherits the builder's HD player skill165 E80/E86 gate and `tblSkill.Get` ID c0/bf remap described in `hearts-menu-leads.md`. PS2 accepts the equipped byte even on the demon path; that builder subsequently ignores it for demons.

**Null-unit limit:** PS2 builder returns on unit NULL before initializing count. This caller does not initialize its stack list before the call, then performs `LB sp+0`. There is no deterministic NULL-unit query contract; do not add a clean return0 and call it recovery. HD scratch allocation initializes count, so its NULL result can differ.

Meaningful comparisons: a nonnull valid unit; empty/one/full24 counted IDs, matches at first/last position, absent and repeated/high-bit ushort skills; real player and demon builder paths; both demon type1/type6 branches; level equality and offsets -128/-1/0/1/127; verify incoming offset's low8 conversion with wider register values; unchanged unit/global buffers. A builder-hook membership test can isolate the predicate, but retain some comparisons that execute the original builder so an incorrect +1a layout or offset forwarding cannot be hidden by the hook. NULL unit remains outside the deterministic fixture contract.

## Custom unit copy dependency: 1fef20

The complete 75-instruction PS2 routine copies exactly 0xec bytes from source to destination: seven 32-byte chunks through source+e0, then the final 12 bytes. It chooses aligned `LD/SD` versus unaligned `LDL/LDR/SDL/SDR` operations using `(source|destination)&7`. This preserves unknown/padding bytes as well as known fields. It is a forward chunk copy, not a proved general overlapping memmove.

After copying, it calls canonical `00243c28 datGetMaxHp(destination)` and `00243d28 datGetMaxMp(destination)`, writes ushort maxima at destination+8/+c, clamps unsigned current HP+6/MP+a when above those maxima, and ORs UInt32 flag+0 with1. Maxima writes and clamps are unconditional/conditional respectively; the source is unchanged for disjoint valid buffers. This is the precise scratch-copy helper reached by PS2 skill parent `00221350`.

HD `182410730` calls `newdata_H.datUnitWork_t.Copy` at `18260c310`, recomputes named maxima, writes native object+18/+1c, clamps current values+16/+1a, and ORs flag+10 with1. The complete readable Copy body copies scalar fields and array elements into existing destination arrays: six parameter/skill/mitama/level-up bytes, 24 skill Int32s, 24 inherited ushorts/attribute bytes, eight name/full-name chars, and four getdevilhearts ushorts. It does not copy PS2 unknown padding or replace destination array references. If source skillparam is NULL, that native Copy exits after base fields/parameters and skips the remaining copy; the PS2 copy is unconditional. Ordinary fully constructed HD units avoid that difference. The managed widths/field-copy behavior are port differences, not a reason to shorten the PS2 0xec copy.

Meaningful comparisons: disjoint patterned 0xec buffers with guard bytes, both aligned and unaligned addresses; every untouched/padding byte copied; resource values below/equal/above recomputed maxima; flag0/1/other bits; complete destination buffer and unchanged source/global buffers; exact self-alias if supported by the test harness. Keep arbitrary partial overlap separate and retain actual chunk semantics instead of implementing memmove by assumption.

## Readable protected skill parent: separate candidate

`00221350` strongly identifies `18227fe50 rstcalc$$rstChkHeartsSkill`, proposed PS2 `uint16_t rstChkHeartsSkill(datUnitWork_PS2 *unit)`. Its full 38-instruction body first calls the custom-copy helper above into a stack unit, then calls canonical `002226b8 cmbChkGetHeartsSkill(global+1cfa,&scratch)`. Literal skill165 is rejected when event8c1 is clear. It then rejects skill0 or skills owned by the original unit (`001feda0`), and returns the skill only if signed8 `rst_work+27 < rst_work+1b`.

HD preserves the copy, candidate call, own event gate, owner check against the original `*pStock`, and progress comparison. Its script signature uses a managed unit reference. `result2_H.rstData_t` metadata identifies HD +37 as SByte HeartsSkFlag and +26 as Int16 LevelUpCnt; corresponding PS2 reads+27/+1b are **both signed8**. Neighbor callers increment/store the PS2 fields consistently. The parent query itself does not increment either counter and does not write its caller's unit.

The HD parent's skill/event constants are XOR-decoded globals. Read-only current GameAssembly disk bytes corroborate the expected literals: file offset555133e value2414 XOR2571 yields165; file offset5551342 valueffffffbf XORfffff77e yields8c1. The callee's protected skill constant at file offset555132a value4824 XOR4941 also yields165. These are static disk decodes; live protected-global persistence was not verified. Keep this body outside the clean six-entry table, and do not represent decoded initialization bytes as live runtime evidence.

A concrete port difference follows from the native callee's E80/E86 filter: place eligible165 before a later eligible ordinary skill. With both HD events clear, HD can skip165 and return the later skill. PS2 candidate lookup returns165 first, and when8c1 is clear this outer parent returns0 **without rescanning**. The own8c1 gate is retained; the changed candidate set is inherited from the port. Meaningful tests cover these combinations, zero/owned candidate, first-eligible order, both sides/equality of the signed progress comparison, and full original-unit/global preservation. Progress128..32767 is representable in HD's widened count but not equivalent to the signed8 PS2 field.

## Other separate limits

- Gift query `00221e30` has a plausible native identity `182279460 rstCalcCore$$cmbChkGiftHeartsDevil`, PS2 prototype `int8_t cmbChkGiftHeartsDevil(uint16_t id)`. Its complete 15 instructions mask FFFF, inspect one four-byte row at00339df8 with LHU ID+0, return LB HeartsID+2 on equality, otherwise0. A branch-likely increments the loop index only on mismatch; this is one row, not an open-ended sentinel search. Read-only ELF bytes for that row are `00 00 00 00`, so every shipped return is0. HD scans managed table length, and its readable pseudocode loads DevilID+10 as **signed char**, while `fclGiftHearts_t` metadata declares UInt16 DevilID and Byte HeartsID; its constructor writes ushort+10 and byte+12, both0, in the first row. Resolve the native width discrepancy before claiming generalized HD behavior. Shipped all-zero results cannot validate ushort-ID comparison or signed return; PS2-only synthetic nonzero/8000 IDs and high-bit output bytes would be needed.
- `00221550` and `00221558` are distinct complete two-instruction PS2 no-ops. HD `rstLoadHeartsSkill` and `rstStoreHeartsSkill` share `1810d6760` with 244 other method declarations, a native `RETURN` body, and no unique prototype. Equip2453e8 calls21550 after assigning the equipped ID/applying its parameters; remove245380 calls21558 after parameter subtraction and before clearing the equipped byte. This supports tentative load/store names respectively, but keep shared-native no-op aliases separate from unique reviewed counterparts. No skill transfer or learning occurs in these bodies.
- Previously reviewed `00222408` remains a six-byte add-parameter PS2 operation whose HD alias182277bc0 is `opaque_lock_stub=true`; this review does not promote it. Previously unpaired `00222210` remains the direct skill-slot accessor with signed8 index<8 and no negative-index rejection. No named rstCalcCore counterpart was found in the checked method inventory.

Evidence: `analysis/ps2/whole-program/functions/{00221f20,00221e70,00221d00,00221d70,00220728,001fef20,00221350,00221e30,00221550,00221558,002d4558}.asm/.c/.json`; native corpus `{1822798c0,18227baf0,18227b8e0,18227ba50,18227f9d0,182410730,18260c310,18227fe50,182279460,181ea7730,1810d6760}.c/.json`; `pc/il2cpp/script.json`; `dump.cs` (rstCalcCore declarations187668..187705, rstData fields201173..201203); `il2cpp.h` (gift fields136463..136466, unit fields137533..137566, global fields154576..154619); `pc/metadata/game-methods.tsv`, `game-fields.tsv`; read-only `game/SLUS_209.11` and current `pc/input/GameAssembly.dll` bytes.

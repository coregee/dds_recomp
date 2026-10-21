# Hearts menu and future-skill list: static review

Reviewed 2026-10-03 using only existing local PS2 ASM/C/JSON, HD native corpus bodies/JSON, IL2CPP metadata, and the previously read PS2 descriptor/position bytes. No canonical ledger, source, tests, Ghidra data, or game files were changed. No behavior comparisons were run for this batch.

## Four directly supported counterparts

| PS2 | HD VA / method | Proposed PS2 prototype | Status |
|---|---|---|---|
| `00221ef8` | `182279650` / `rstCalcCore$$cmbChkHeartsStat` | `uint8_t cmbChkHeartsStat(int8_t id)` | Complete10-instruction PS2 body and readable HD body agree on descriptor Flag&7. |
| `00220508` | `182280460` / `rstcalc$$rstCreateBeforeSkillList` | `void rstCreateBeforeSkillList(int8_t id, datUnitWork_PS2 *unit, int8_t level_offset, rstSkillInfo_PS2 *info)` | Complete135-instruction PS2 body; both player/demon paths retained in HD; concrete port additions below. |
| `00232920` | `1822dfeb0` / `cmpInitDH$$cmpSetEquipHeartsSelectPos` | `void cmpSetEquipHeartsSelectPos(cmpDataDH_PS2 *data)` | Complete29-instruction PS2 body; duplicate position getter calls and select/default stores agree. |
| `00232cc8` | `1822df730` / `cmpInitDH$$cmpInitHeartsIcon` | `void cmpInitHeartsIcon(cmpDataDH_PS2 *data)` | Complete114-instruction PS2 body; ownership, level states, exception event, RNG draws, and every icon-field store agree structurally. |

All four PS2 JSON files report `decompile_completed=true`; all four HD JSON files report `status=decompiled` and `opaque_lock_stub=false`. Names come from native corpus declarations and `script.json`, with behavior verified independently. Proposed `cmpDataDH_PS2` may remain an opaque menu-work view: this review establishes selected fields and a minimum accessed extent, not the entire enclosing structure.

## Descriptor Flag accessor: 221ef8

PS2 explicitly sign-extends the low8 ID (`sll24; sra24`), multiplies by66 (`id<<5; +id; <<1`), performs `LBU` at `00339e00+66*id`, and returns `byte&7`. There is no ID-zero fast path, no ownership/master check, and no clamp. The result is unsigned0..7.

HD182279650 selects `tblHearts` row by signed8 ID, reads `result2_H.fclHearts_t.Flag` at native object+10, and applies `&7`; its additional class/null/bounds checks belong to the managed port. The descriptor Flag is distinct from the per-ID acquired/master/learned-skill byte at global+1d3b. Neighboring PS2 caller221f20 first checks mastery and then classifies this Flag result as1,0,4. That supports a descriptor classification use; it does not establish English labels for those classes. Existing shipped descriptor data has only0,1,4 in the logical1..25 rows, but preserve the `&7` operation for other flag bytes.

## Future-skill list: 220508

The function is a list builder. It does not acquire or learn skills and does not update global Hearts state. Its initial behavior matters: if `unit==NULL`, it returns without changing even `info->count`. Otherwise it clears only that count byte. It does not clear the output arrays or their padding.

### Output view proven by PS2 stores

| Offset | Storage | Evidence / behavior |
|---|---|---|
| `+00` | Signed8 `SkillCnt` | Initial SB zero; append index read with LB; count increments with byte SB. |
| `+01..18` | Byte `TargetLevel[24]` | Store required level at `+1+old_count`. |
| `+19` | One padding byte | Not written here; ushort array begins at +1a. |
| `+1a..49` | UInt16 `SkillID[24]` | Old count sign-extended and multiplied2 (`sll24; sra23`); SH at +1a+2*count. |

The smallest view covering these stores is `0x4a` bytes. Both arrays have capacity24: the demon path examines exactly24 entries; the player path at most8. HD18227c020 `result2_H.rstSkillInfo_t..ctor` independently allocates24-element arrays. HD metadata declares SByte `SkillCnt`, Byte[] `TargetLevel`, UInt16[] `SkillID`; native builder fields are object+10/+18/+20. No new capacity/bounds checks should be added to the PS2 reconstruction without explicitly changing its contract.

### Player path (`unit->id==0`)

ID is signed8 at entry. ID zero leaves the newly cleared count0 and returns. Otherwise `cmbGetHeartsAfterSkillNums((uint8_t)id)` at221d0 supplies the low-nibble start index; indexes>=8 produce an empty list. The descriptor is `00339e00+66*(int8_t)id`. For each remaining slot through7:

1. Read required level with signed `LB` at descriptor+1a+4*slot, and skill with `LHU` at+1c+4*slot.
2. Skip skill0.
3. Call `cmbChkSkillOwner(skill,unit)` at1feda0 and skip nonnegative returns.
4. Append the raw required-level byte and skill ushort, incrementing the byte count.

There is **no level-eligibility predicate** on this path: future skills can be listed irrespective of `unit->level`, required level0, or `level_offset`. The offset parameter is ignored for the player path. It also does not test the master flag. Do not substitute the different `cmbChkGetHeartsSkill` first-eligible-skill algorithm at226b8.

HD182280460 preserves this scan and its unowned predicate. It additionally treats skill`0x165` specially: it includes that skill only when event`e80` or`e86` is enabled. Unlike the protected neighboring SkillNums/next-skill bodies, this native body exposes the skill ID directly. No corresponding gate/call exists in PS2 220508.

### Demon path (`unit->id!=0`)

PS2 ignores the incoming Hearts ID. It computes `unit->id *102` using a zero-extended ushort ID and selects packed row `00333cf8+102*ID`. The row begins with six bytes; the checked event list follows:

| Packed row offset | Use / HD field identification |
|---|---|
| `+00..05` | Six growth parameters; not read by this builder. HD `fclSkill_t.GrowParamTbl` corroborates the row-prefix interpretation. |
| `+06+4*i` | Signed-loaded required-level byte (`LB`); HD `fclSkillParam_t.TargetLevel` is declared Byte. |
| `+07+4*i` | Unsigned event type byte; HD `fclSkillParam_t.Type`. |
| `+08+4*i` | UInt16 skill/event parameter; HD `fclSkillParam_t.Param`. |

There are24 four-byte entries (`i=0..23`); six prefix bytes plus96 event bytes gives the independently computed102-byte row stride. If unit ushort `hensinmae` at+ce is0, only type1 entries qualify; otherwise only type6. A qualifying entry is included when `(int32_t)(uint16_t)unit->level + (int32_t)(int8_t)level_offset < (int32_t)(int8_t)required_level` and skill-owner returns negative. The offset is signed8 in the actual PS2 entry instructions (`sll24; sra24`), whereas HD metadata/native signature uses signed16 `SkillLevOfs`.

The demon path contains **no explicit nonzero-skill predicate**. For a synthetic row with matching type and future level, skill0 is passed to the owner search and can be appended if absent. Do not import the player path's zero filter into this branch. This code does not prove meanings for all other event types.

HD preserves the24 iterations, type1/type6 selection using unit `hensinmae` at native+88, signed required-level comparison, owner call, and output appends. It replaces direct packed-table addressing with `tblSkill.Get(unit->id)` at181717dd0, followed by managed `Event` array objects. Its checked child fields are +10 required level, +11 type, +12 UInt16 parameter.

`tblSkill.Get` has real behavior beyond managed array lookup: it calls `fclCombineUpdate.IsZensyoMode`; for IDs`bf` and`c0` that mode keeps the respective direct rows. Outside that mode, ID`c0` maps to row`bf` when event`e80` is set. PS2 220508 always selects the direct numeric ID*102 row. This is a second concrete port difference, independent of the player-path skill165 gate.

### Verified dependencies

| PS2 call | HD retained call | Evidence |
|---|---|---|
| `002221d0` | `18227a960 rstCalcCore$$cmbGetHeartsAfterSkillNums` | Same acquired-state low-nibble start accessor; both used only on player path. |
| `001feda0` | `182410660 fclCombineCalcCore$$cmbChkSkillOwner` | First skill index or -1; PS2 ushort count+38/list+3a; HD Int32 count+48/managed Int32[]+50. |

There is no unresolved PS2 callee on the builder path. HD also reaches EventBit checks, tblSkill.Get, class-init and managed exception helpers. Those HD-only dependencies should be recorded as differences rather than invented PS2 calls.

## Equipped selection: 232920

The PS2 routine initializes index0 and consumes position rows0..26. Each iteration calls `cmpGetHeartsFromPos` twice on the same signed8 index and ignores the first result. It compares the second signed return with unsigned-byte `global+1cfa` (equipped Hearts ID). The first match stores the index byte at `data+31` and returns. If no match among27 rows, it stores0 at that byte. It does not check ownership or whether an icon was initialized for that position.

The position table is at00345e58, stride8: signed ID+0, signed IconType+1, raw UInt32 Color+4. Previously checked PS2 bytes give IDs1..27 in order. Thus equipped0 defaults to selection0, equipped1..25 selects0..24, and the physically present26/27 rows would select25/26. The latter are table behavior, not evidence of27 logical owned Magatama.

HD1822dfeb0 also calls the getter twice, compares against global managed `heartsequip` at+a2, stores SByte `SelectPos` at menu object+39, and defaults0. Its scan ends at managed table length instead of a literal27. HD static initializer1822ddf80 constructs27 indexed rows and stores the table at class static+28, including IDs26/27; native pseudocode omits the allocator's length argument, so the writes prove at least27 populated slots rather than conclusively proving the allocation has no extra slots. The entire enclosing PS2 menu-work layout remains unestablished; +31 is independently proved here.

## Icon initialization: 232cc8

This routine processes exactly25 positions0..24 and obtains the first-party unit at global+a54. For each position it calls the ID getter232998 and ownership predicate2328c8. Unowned entries receive icon type-1, color0 and MoveType0. Owned entries obtain the table type/color, build a future-skill list with `rstCreateBeforeSkillList(id,player,0,&info)`, and compute movement state from its first listed level:

| Condition | Stored MoveType byte |
|---|---:|
| Empty list | 0 |
| First target level <= player level+1 | 2 |
| Otherwise, first target level <= player level+4 | 1 |
| Later skill | 0 |

If the list has exactly1 skill, ID is1, and event`8c1` is clear, force MoveType0. PS2 uses unsigned-byte target level in this comparison (`LBU`), even though the builder read the descriptor with LB before storing its low byte. The two branch-likely delay slots at232dc8 and232dd0 do not change the special ID test into -1: when count==1 the annulled first delay slot leaves V0=1 for the ID comparison.

### Exact52-byte icon view

Assembly S2 starts at `data+1270` but its first actual store is at S2+8. Normalize all independent cursors to **icon payload base `data+1278`**, stride`0x34`, then every field fits exactly into a52-byte record. The last of25 records ends at exclusive menu offset`178c`. The two padding regions are not written by this routine.

| PS2 payload offset | Width / HD field name | Initial value | HD native object offset |
|---|---|---|---|
| `00` | SByte `Stat` | 0 | `10` |
| `01` | SByte `IconType` | Table type, or -1 | `11` |
| `02..03` | Padding | Preserved | `12..13` |
| `04` | UInt32 `IconColor` | Raw table color, or0 | `14` |
| `08` | SByte `MoveType` | Computed0/1/2 | `18` |
| `09` | SByte `Axis` | 0 | `19` |
| `0a..0b` | Padding | Preserved | `1a..1b` |
| `0c` | Int32 `AxisChg` | -1 | `1c` |
| `10` | Int32 `Wait1st` | First RNG result&31 | `20` |
| `14` | Int32 `Wait` | Second RNG result&31 | `24` |
| `18` | Float `Angle` | Raw zero bits | `28` |
| `1c` | Float `DefAng` | Raw zero bits | `2c` |
| `20` | Float `DistAng` | Raw zero bits | `30` |
| `24` | Int32 `DefCnt` | 0 | `34` |
| `28` | Int32 `Cnt` | 0 | `38` |
| `2c` | Int32 `Timer` | 0 | `3c` |
| `30` | Int32 `TimerSpd` | 6 | `40` |

Field names/types come from `camp_H.cmpHeartsIcon_t` metadata and match every native HD write. PS2 instructions establish offsets/widths/raw values independently; zero stores alone would not distinguish float from integer without that corroboration. The HD menu object holds a managed icon array at+60. Its initializer allocates a managed scratch `rstSkillInfo_t`; PS2 uses its stack scratch buffer. Both initialize25 icons.

### Raw table-data and RNG differences

HD static initializer1822ddf80 retains all27 position IDs and icon types but changes the first25 raw Color words. PS2 has`80808080` for every physical row; HD colors for IDs1..25 are `1,2,0,0,1,2,2,0,1,1,0,2,0,2,1,2,0,1,0,2,1,0,1,2,3`. HD IDs26/27 retain`80808080`. The getter algorithm corresponds, but its backing constants differ. The meanings/rendering of HD small color values have not been verified; keep their classification as raw UInt32 data and retain the PS2 constants in a PS2 recovery.

PS2 calls the already matched `sdfGetRand` at002c0ba8 with NULL twice per icon, therefore50 draws total. NULL selects global four-word RNG at00529bd8. HD calls `fclMisc.FCL_RAND` at1821690d0, which invokes the matched `sdfRand.sdfGetRand` at18230c550 once, records the returned draw through `dds3KernelCore.SetRandHistory`, and returns it. The two masked draws and core RNG correspond; history recording is an extra HD side effect. HD's player-list gate for165 can also change icon MoveType indirectly through the resulting list count/first level.

## Remaining limits

These findings establish the four identities and local data views. Full PS2 menu-work extent/other fields, descriptor/table logical capacities outside checked caller contracts, meanings of unhandled demon event types, and HD color rendering remain unknown. Parent routine null/bounds behavior is managed-port behavior; the PS2 menu routines have no explicit data-pointer null check. The scratch builder checks unitNULL but relies on a valid output pointer when unit is nonnull. The exact HD table allocation length remains obscured in its allocator call, while its27 populated rows are explicit. No gameplay/runtime equivalence or new instruction-vector result is claimed here.

Evidence files: `analysis/ps2/whole-program/functions/{00221ef8,00220508,00232920,00232cc8,001feda0,002221d0,002c0ba8}.asm/.c/.json`; `pc/ghidra/corpus/{182279650,182280460,1822dfeb0,1822df730,181717dd0,1821690d0,18227c020,1822ddf80,18230c550}.c/.json`; `pc/metadata/game-methods.tsv`, `game-fields.tsv`; `pc/il2cpp/script.json`, `il2cpp.h` (fclSkill fields136350..136376, skillinfo136558..136561, icon155089..155105, menu155151..155169).

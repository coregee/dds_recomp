# Next Hearts counterparts: local static review

Reviewed 2026-10-03 against the complete SLUS_209.11 function export and HD native corpus. No Ghidra, canonical ledger, or recovered-source changes were made by this review. These are static counterpart findings; no new instruction vectors or runtime checks were run.

The PS2 export summary reports `status=complete`, 8,935 exported/decompiled functions, and zero failures. Every PS2 entry below has its complete ASM/C/JSON and `decompile_completed=true`. Each proposed HD match was checked against its corpus C body, JSON method declaration/status, `script.json`, and relevant managed field declarations in `il2cpp.h`. Matcher ranks were not used as evidence.

## Fifteen ledger-ready static candidates

Primitive prototypes below describe PS2 behavior. Return-width inference is qualified where the instructions determine values more tightly than they determine the original C declaration. The opaque HD add-parameter method is deliberately outside this table.

| PS2 entry | HD VA | HD method / proposed PS2 name | Proposed PS2 prototype | Retained identifying behavior |
|---|---|---|---|---|
| `00221dd8` | `182279370` | `rstCalcCore$$cmbChkGetHearts` | `int8_t cmbChkGetHearts(int8_t id)` | Scan owned list `global+1cfb` using count `+1d7b`; compare with signed8 ID; return 0/1. |
| `002220c0` | `18227adb0` | `rstCalcCore$$cmbGetHeartsSkillNums` | `int16_t cmbGetHeartsSkillNums(uint8_t id)` | ID zero returns zero; count eight nonzero descriptor skill ushorts at `00339e1c+id*66+4*i`; count narrowed to signed8 internally. HD metadata return is Int16. |
| `00222140` | `1822795c0` | `rstCalcCore$$cmbChkHeartsMaster` | `int8_t cmbChkHeartsMaster(uint8_t id)` | Read byte `global+1d3b+low8(id)`; return whether bit `80` is set. |
| `00222160` | `18227b590` | `rstCalcCore$$cmbGetMasterHeartsNums` | `int8_t cmbGetMasterHeartsNums(void)` | Iterate the owned list, call the preceding master predicate, count true results, signed8 return. |
| `002221e8` | `18227bd10` | `rstCalcCore$$cmbSetHeartsMaster` | `void cmbSetHeartsMaster(int8_t id)` | Signed8 ID; OR `80` into the same state byte; preserve all other bits. |
| `00222290` | `18227a9f0` | `rstCalcCore$$cmbGetHeartsAisyo` | `int16_t cmbGetHeartsAisyo(uint8_t id)` | ID zero returns zero; signed16 table load at `00339e02+id*66`. |
| `002222c0` | `18227aa90` | `rstCalcCore$$cmbGetHeartsDefaultParam` | `int8_t cmbGetHeartsDefaultParam(int8_t id, int8_t index, int8_t type)` | Signed8 ID/index; choose `00339e06` for low8(type)==0 or `00339e0c` otherwise; stride66, byte element, signed8 load. |
| `00222318` | `18227abe0` | `rstCalcCore$$cmbGetHeartsParamEx` | `int8_t cmbGetHeartsParamEx(int8_t id, int8_t index, int8_t mode)` | Normalize low8(mode) to 0/1, call default accessor, add byte `global+11dc0+id*6+index`, signed8 final wrap. |
| `002223a0` | `18227ad00` | `rstCalcCore$$cmbGetHeartsParam` | `int8_t cmbGetHeartsParam(int8_t id, int8_t index)` | Master predicate selects mode 0/1 passed to ParamEx; V0 from ParamEx remains the return value. |
| `00222470` | `18227bda0` | `rstCalcCore$$cmbSubHeartsParam` | `void cmbSubHeartsParam(uint8_t id, datUnitWork_PS2 *unit)` | Six iterations, subtract per-index GetHeartsParam result from byte `unit+16+i`, low8 store. PS2 explicitly sign-extends ID before the signed accessor. |
| `002226b8` | `182279130` | `rstCalcCore$$cmbChkGetHeartsSkill` | `uint16_t cmbChkGetHeartsSkill(uint8_t id, datUnitWork_PS2 *unit)` | Start at AfterSkillNums; scan to slot7; require nonzero skill, nonzero required level, level<=unit level, and skill-owner return<0; return first eligible skill or zero. |
| `001feda0` | `182410660` | `fclCombineCalcCore$$cmbChkSkillOwner` | `int8_t cmbChkSkillOwner(uint16_t skill, datUnitWork_PS2 *unit)` | Scan `unit->skillcnt` ushort at +38 and ushorts at +3a; return matching index narrowed to signed8, else -1. This is the direct 226b8 callee. |
| `00232998` | `1822df2c0` | `cmpInitDH$$cmpGetHeartsFromPos` | `int8_t cmpGetHeartsFromPos(int8_t index)` | Signed8 index, eight-byte position row, signed byte at `00345e58+8*index`. |
| `002329b8` | `1822df3e0` | `cmpInitDH$$cmpGetHeartsIconTypeFromPos` | `int8_t cmpGetHeartsIconTypeFromPos(int8_t index)` | Same signed8 index/stride; signed byte at row+1. |
| `002329d8` | `1822df350` | `cmpInitDH$$cmpGetHeartsIconColorFromPos` | `uint32_t cmpGetHeartsIconColorFromPos(int8_t index)` | Same signed8 index/stride; word at row+4. |

HD native methods use managed objects/arrays and add class initialization, null checks, and bounds exceptions. Those are not present in the PS2 routines and must not be introduced into a behavioral reconstruction silently. Logical Hearts IDs remain 0..25 unless a separately checked caller permits another range.

## Instruction and type evidence

### Ownership and master state

`00221dd8` begins with `sll a0,24; sra a0,24`, `lbu ...,+1d7b`, then scans `lbu ...,+1cfb` entries and compares each to the full sign-extended ID. It is a second ownership query, distinct from the already named `cmpChkHaveHearts` at 2328c8; HD also has the two distinct names. The HD rst ownership body reads the managed ownership array at global object+`a8` and its count at +`b8`. For ordinary IDs/counts its scan and return match; HD pseudocode displays signed-char ownership/count expressions while metadata identifies those storage fields as byte/byte[]. This review does not claim malformed/high-bit list values behave identically between ports.

`00222140` is seven instructions: unsigned8 ID, unsigned state-byte load, mask `80`, `sltu result,zero,result`. HD 1822795c0 reads the same `heartsskcnt` managed array (object+`b0`) and returns whether the selected signed byte is negative, equivalent to bit7. `002221e8` sign-extends ID, reads the same byte, `ori 80`, and stores it back. HD 18227bd10 performs the same OR. Thus bit7 of the previously partially unknown upper nibble is now the master flag; bits4..6 remain unclassified. The low nibble remains the already identified learned/after-skill count. Incrementing the entire byte in AddHeartsSkill must still be preserved.

`00222160` calls 22140 on each byte in the ownership list, conditionally increments its accumulator via `movn`, and finally sign-extends its low byte. HD 18227b590 has the same ownership-list/master-query loop and SByte accumulator/return. For count0 it returns0. It counts list entries rather than deduplicated IDs.

### Descriptor and parameter tables

The multiplier sequence `id<<5; +id; <<1` proves stride66 independently in SkillNums, Aisyo, DefaultParam and ChkGetHeartsSkill. Direct read-only ELF program-header mapping of `nocturne/game/SLUS_209.11` confirms a 26-row descriptor span starting at `00339e00`:

| Descriptor-relative offset | Checked field/use |
|---|---|
| `+00` | Flag byte; neighboring unpaired 221ef8 masks this with7. |
| `+02` | Signed16 AisyoID accessed by 22290. IDs1..25 hold384,386,...,432. |
| `+04` | Signed16 values385,387,...,433; HD type calls this MasterAisyoID, but no setter/accessor here proves its use. |
| `+06..0b` | Six signed normal growth parameters, accessed by DefaultParam(type0). |
| `+0c..11` | Six signed master growth parameters, accessed by DefaultParam(nonzero type). |
| `+1a+4*i` | Required level byte for eight skills. |
| `+1c+4*i` | Skill ushort for eight skills. |

The HD `result2_H.fclHearts_t` declares `Flag`, Int16 `AisyoID`, Int16 `MasterAisyoID`, SByte[] `GrowParamTbl`, SByte[] `MasterGrowParamTbl`, and `Skill`. HD `fclHeartsSkill_t` declares Byte `TargetLevel` and UInt16 `ID`. HD native Aisyo at18227a9f0 returns the row's signed16 +12; DefaultParam at18227aa90 selects managed arrays at row+18/+20; SkillNums and ChkGetHeartsSkill read row+38 skill arrays and child +12 ID/+10 level. These native offsets agree with the generated managed class field order, not the packed PS2 offsets.

Important validation consequence: all shipped rows0..25 have **identical normal/master parameter arrays**. ID1, for example, has `(2,-1,1,2,1,1)` in both. Ordinary table tests therefore cannot detect a swapped type/master branch. Synthetic table variants are needed for a meaningful branch comparison. Skill counts for IDs0..25 are `0,6,5,3,4,4,5,4,4,5,4,4,4,6,5,3,5,5,5,3,5,3,5,4,5,7`.

ParamEx at22318 calls222c0, computes ID*6+index, uses `lbu` at global+11dc0, adds, then `sll/sra24` to force signed8 wrap. HD18227abe0 calls the same named default accessor and adds the selected managed `hearts_up_param` sbyte to its SByte result. Signed versus unsigned load does not affect the final low byte, but C signed-overflow behavior must not replace the observed low-byte wrap.

GetHeartsParam at223a0 calls22140 and22318; its export incorrectly says `void` because the callee prototypes were unresolved. The original instructions at223d8/223e8 call ParamEx, then only restore S0/S1/RA/SP before `jr ra`; they leave V0 intact. Callers22408/22470 immediately consume V0 in byte addition/subtraction, providing independent return-use evidence. HD18227ad00 retains the master-query/default selection and inlines ParamEx's default-plus-upgrade core.

SubHeartsParam at22470 has `unit+16`, six iterations, `jal223a0`, `lbu`, `subu`, and `sb`. HD18227bda0 reads `newdata_H.datUnitWork_s.param` (native object+28), calls GetHeartsParam for indexes0..5, and stores the signed-byte subtraction. HD metadata declares HeartsID Byte; PS2 passes the sign-extended low byte into the signed8 accessor. A reconstruction can expose the Byte argument while explicitly converting it to signed8 at that call.

### Skill eligibility and its verified callee

The original 226b8 instructions retain the current `AfterSkillNums` in S2; they do not write count/state or consume a skill. At each slot they `lhu` skill, skip zero, `lb` level, skip zero, `lhu` unit level at +14, skip if unit level is lower, and call `001feda0(skill,unit)`. `bgez` rejects already-owned skills; a negative owner-search result returns the candidate ushort. Exhaustion returns0.

`001feda0` is a complete 19-instruction helper. Its first `lhu +38(a1)` obtains skill count; the input skill is masked to ushort. It scans the inline ushort list at unit+3a, returns the first index via `sll/sra24`, and uses `li v0,-1` on exhaustion. HD182410660 declares the corresponding SByte/UInt16/unit method, scans the unit's Int32 skill count at+48 and managed Int32[] skill array at+50, compares each with the zero-extended incoming ushort, and returns low8 index or -1. The wider HD list/count is a concrete layout difference. No unresolved callee identification remains on this next-skill path.

HD18227adb0 and182279130 additionally suppress a protected skill unless event `e80` or `e86` is enabled. The skill identity is decoded from protected globals/XOR constants in these bodies, so this report deliberately does not assign a numeric skill ID from a literal-XOR guess. These event gates are absent from the PS2 SkillNums and ChkGetHeartsSkill instructions. PS2 eligibility reads required levels with `LB`; HD body also compares a signed8 level expression even though its metadata field is Byte. Preserve the demonstrated PS2 signed comparison in edge-case instruction tests.

### Menu position getters and ownership caller cross-checks

All three PS2 getters compute `sll index,24; sra index,21`, producing `8*(int8_t)index`. Native HD methods1822df2c0/3e0/350 select `cmpHeartsPosTbl[index]` and read object+10/+11/+14. The managed type `camp_H.cmpHeartsPosTbl_t` declares SByte `HeartsID`, SByte `IconType`, and UInt32 `Color`, matching each read and signedness.

Direct ELF bytes give row indexes0..24 IDs1..25. Icon types are `16,8,0,1,17,9,10,2,18,19,3,11,4,12,20,13,5,21,6,14,22,7,23,15,24`; every raw color is `80808080`. Two immediately following physical rows carry IDs26 and27, icon type0, and the same color. This establishes data and physical layout, not ownership capacity.

The next medium ownership caller `00232cc8` strongly corresponds to HD1822df730 `cmpInitDH$$cmpInitHeartsIcon`. Its full114-instruction body and readable HD body have:

- Exactly25 icon iterations.
- Position ID getter followed by the already named ownership predicate; unowned rows get icon type-1, color0, and learnability state0.
- Owned rows call the type/color getters, then PS2 `00220508(id,player,0,&skillinfo)` / HD `rstCreateBeforeSkillList`.
- First-party unit `global+a54`; skillinfo empty gives state0; first skill level<=unit level+1 gives state2; otherwise <=level+4 gives state1; later gives state0.
- A single-skill, ID1 exception gated on event `8c1`.
- Both RNG results masked with`1f`, and matching initialization of flags, type/color/state, -1 sentinel, zero fields, and terminal6.
- PS2 inline icon record stride`34`, with actual payload base `pData+1278`; HD managed icon objects at pData+60. PS2 payload+00=0, +01=type, +04=color, +08=state, +09=0, +0c=-1, +10/+14=rand&31, +18/+1c/+20/+24/+28/+2c=0, +30=6. This maps exactly to HD object fields+10..40, whose payload starts after its16-byte object header.

The cursor detail needs care: S2 starts at pData+1270 but writes its first payload byte at+8; S5 starts at pData+12a8, i.e. actual payload base+30, and stores6 there before advancing by34. Normalizing these independent cursors to pData+1278 resolves the complete52-byte payload without crossing an entry boundary. This medium routine is supplied as a connected caller review in addition to the fifteen small reconstruction candidates; its proposed PS2 prototype is `void cmpInitHeartsIcon(cmpDataDH_PS2 *data)` with an opaque/recovered menu-work view until the enclosing type is established.

`00232920` also strongly corresponds to HD1822dfeb0 `cmpSetEquipHeartsSelectPos`: both call the position getter twice per index, compare the second return to equipped ID, write the index on the first match, else default0. PS2 stores pData+31 and scans a fixed27 rows; HD stores pData+39 and uses the managed table length. This is additional caller evidence for the ID getter. Neither caller's mapping is inferred solely from method-order proximity.

## Provisional and unpaired queue

- `00222408` has a fully known six-byte addition loop symmetric to22470 and is the evident PS2 add-parameter operation. Its metadata alias is HD182277bc0 `rstCalcCore$$cmbAddHeartsParam`, but the exported native body is only `LOCK(); UNLOCK(); return;`, with `opaque_lock_stub=true`. Treat its PS2 behavior as recoverable independently and the HD alias as provisional. Do not assert a reviewed HD behavioral counterpart from this stub.
- `00222210` returns a descriptor skill ushort from `00339e1c+id*66+index*4` if signed8(index)<8; indexes>=8 return0, while negative indexes are **not** rejected. Its complete instructions prove this accessor, but no corresponding named rstCalcCore method appears in metadata. Retain a PS2 descriptive alias until a real native counterpart is found.
- `00221ef8` reads descriptor flag&7 and likely pairs with HD182279650 `cmbChkHeartsStat`; its native body has not been reviewed here, so that is a lead only.

## Suggested instruction comparisons for the next reconstruction

Master getter: all256 state bytes and IDs0..25. Setter: all256 incoming state bytes, verify only bit7 changes and all unrelated memory stays untouched. Master count: empty and mixed ownership lists, including repeated IDs, while retaining valid count contracts. SkillNums: table zero/nonzero masks and ID0 fast path, plus synthetic nonzero high-bit skill IDs. Default/ParamEx/Param: all six indexes, both mode choices, synthetic distinct normal/master arrays, negative defaults, upgrade bytes that cross signed8 boundaries, and preservation of state/other global bytes. Sub/Add: six-byte wraps with complete-unit buffer comparison. Next-skill: skip each exclusion branch independently, duplicate skill indices, signed required-level values, starting count0..15, first eligible selection versus exhausted return0, and full buffers unchanged. Position getters: compare all27 physically consumed rows and all three fields; malformed/negative table indexing must remain a separate contract decision.

Evidence paths: `analysis/ps2/whole-program/functions/<PS2 address>.asm/.c/.json`; `pc/ghidra/corpus/<HD VA>.c/.json`; `pc/il2cpp/script.json`; `pc/il2cpp/il2cpp.h` (Hearts fields around136485..136539, unit fields137533..137566, global fields154576..154619, menu row fields155066..155070); `pc/metadata/game-methods.tsv`; and read-only packed data from `game/SLUS_209.11`.

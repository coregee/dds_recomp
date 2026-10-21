# Calculation and skill-effect counterparts

25 additional PS2 functions have strong static counterparts in the named HD `datCalc` methods, bringing the recorded total to 29. [calculation-matches.tsv](calculation-matches.tsv) lists every PS2 entry, HD native VA, signature family, evidence, and known differences. Names identify counterpart roles; their exact spelling in the unavailable original PS2 source is inferred from HD metadata. No live gameplay validation or matching recompilation has been performed.

## Main effect path

| PS2 entry | HD native VA | Recovered role |
| --- | --- | --- |
| `0x00243368` | `0x181CCE1E0` | `datGetSkillKouka`: compute a signed HP or MP effect |
| `0x00243760` | `0x181CCDB40` | `datGetSkillBadKouka`: compute status application/removal |
| `0x00243998` | `0x181CCC020` | `datExecSkill`: compute and apply HP, MP, and status effects |
| `0x00242E00` | `0x181CC73C0` | `GetButuriAttack`: physical calculation |
| `0x00242FF8` | `0x181CC7700` | `GetMagicAttack`: magical calculation |
| `0x002432D0` | `0x181CC72C0` | `GetAisyoRitu`: convert packed affinity to a float multiplier |

`datGetSkillKouka` allocates a `0x50`-byte stack frame. It preserves skill index `a0` in `s1`, source pointer `a2` in `s3`, destination pointer `a3` in `s2`, and initially preserves the HP/MP selector `a1` in `s0`. The call at `0x002433B4` returns affinity in `f0`, copied into preserved `f20`. This supports the float return independently of metadata.

The HP path at `0x002433E8` computes the record offset as:

```text
sll  s0,s1,4       # nskill * 16
subu v0,s0,s1     # nskill * 15
sll  v0,v0,2      # nskill * 60 = nskill * 0x3C
```

It reads destination maximum HP with `lhu t0,0x8(s2)` at `0x002433EC` and current HP with `lhu a0,0x6(s2)` at `0x002433F4`. The selected skill formula and power are loaded with `lhu` and signed `lh`, respectively. The MP path uses destination offsets `0xC`/`0xA` and the adjacent formula/power fields. These instruction-level distinctions establish field width and signedness.

The first switch has 16 cases. It dispatches physical and magical effects, constant changes, current/max-resource percentages, maximum-HP-based effects, and random healing. For physical damage, source status is masked with `0xFFF`; statuses `0x40` and `0x200` halve the result. The later switch always reads the skill's **HP formula field**, even on the MP path. For formula values 1, 6, and 12 it applies damage variation and affinity; values 2 and 7 scale positive healing by affinity. Both versions retain this structure. The return selects negative damage or nonnegative healing, with a nonzero damage floor of one.

`datExecSkill` calls the effect routine twice with selectors 0 and 1, then the status routine. Status modes 1 and 3 call `datSetBadStat`; other modes call `datResetBadStat`. HP and MP changes go through the already named clamping helpers. Zero HP sets status `0x800`. Special effect values 8..11 OR bits 1, 2, 4, and 8 into a global work field.

## Unit layout evidence

The existing `datUnitWork_PS2_prefix` now spans the examined bytes through `0x21`. Unknown bytes `0x10..0x13` remain undefined. The API adds type prefixes to new field names (`wLevel`, `wBadstat`, `cParam0`, etc.). The offsets below are the substantive evidence.

| Logical field | PS2 offset | Evidence |
| --- | --- | --- |
| flag | `0x00`, uint | Conditional cap, parameter and skill-list selection |
| ID | `0x04`, ushort | `datCheckSyojiSkill` uses it to index devil-format records |
| HP / maximum HP | `0x06` / `0x08`, ushort | Effect selector and clamping helpers |
| MP / maximum MP | `0x0A` / `0x0C`, ushort | Effect selector and clamping helpers |
| bad status | `0x0E`, ushort | Status setters and effect mask |
| level | `0x14`, ushort | Base resource, physical/magic, hit and evasion calculations |
| base parameters | `0x16..0x1B`, signed bytes | `datGetBaseParam`; observed parameter indices 0..5 |
| skill parameters | `0x1C..0x21`, signed bytes | Same indexed sum and clamping |
| owned skill count | `0x38`, ushort | Counted skill scan; documented, outside the prefix |
| owned skills | `0x3A`, ushort elements | Counted skill scan; maximum capacity not established |
| additional parameters | `0x7A`, signed bytes | Included in the stat sum unless flag bit 4; outside the prefix |

The parameter sum is clamped to 1..40. `datGetParam` further forces 1 under status `0x200`, except parameter index 4. HD represents parameter/skill lists through managed arrays, so later fields cannot be transferred using a fixed offset adjustment.

## Table fields

These are address-and-access-derived fields. Full table counts and unknown fields have not been inferred from adjacency, and no guessed arrays were applied to Ghidra.

| Table | Base | Record stride | Known access |
| --- | --- | --- | --- |
| Skill attributes | `0x003D6998` | `0x08` | Signed attribute byte at offset 0 |
| Skill calculations | `0x003D7998` | `0x3C` | Fields below |
| Packed affinities | `0x003A7FE0` | `0x40` | 32-bit packed affinity per attribute; 16 entries fit a row |

| Skill field | Record offset | Access type |
| --- | --- | --- |
| Physical/magic category | `0x02` | byte, values 0 and 1 in dispatch |
| HP formula | `0x16` | ushort |
| HP power | `0x18` | signed short |
| MP formula | `0x1A` | ushort |
| MP power | `0x1C` | signed short |
| Flat HP adjustment | `0x1E` | signed short |
| Flat MP adjustment | `0x20` | signed short |
| Status mode | `0x24` | byte |
| Status chance | `0x25` | byte |
| Status mask | `0x26` | ushort |
| Special effect | `0x30` | uint |
| Magic base | `0x38` | signed short |
| Magic limit | `0x3A` | signed short |

## Constants and limits

The ELF's GP value is `0x00554170`. `lwc1 f3,-0x5CC4(gp)` at `0x002436B8` therefore reads `0x0054E4AC`, whose IEEE float value is approximately `0.05`. The following value at `0x0054E4B0` is approximately `0.7`, used by the status-chance correction. Affinity uses approximately `0.01` at `0x0054E4A8`; maximum-HP-based effects use approximately `69.6` at `0x0054E49C`/`0x0054E4A4`.

Several HD constants are expressed as XORs with globals. Reading the inspected DLL's static bytes resolves these independently:

| HD address | Disk value | XOR operand | Decoded value |
| --- | --- | --- | --- |
| `0x18C2C3AE0` | `0x31C93148` | `0x31C93048` | `0x100` |
| `0x18C2C3AE4` | `0x4B3349C0` | `0x4B3349C8` | `8` |
| `0x18C2C3AE8` | `0x49013338` | `0x49013331` | `9` |
| `0x18C2C3AEC` | `0x00E08389` | `0x00E08383` | `10` |
| `0x18C2C3AF0` | `0x48560000` | `0x48560002` | `2` |
| `0x191FB6558` (low halfword) | `0x6589` | `0x6A76` | `0xFFF` |
| `0x191FB655C` (low halfword) | `0x8D48` | `0x8948` | `0x400` |
| `0x191FB6560` | `0x48FA8FEE` | `0x48FA8FE9` | `7` |
| `0x191FB6564` | `0xC3243487` | `0xC3243407` | `0x80` |

These support the affinity/status counterparts, but HD also changes behavior. It maps status `0x800` to attribute 5 where PS2 returns -1, and higher-status mapping includes `cfgGetBit(9)`. HD `datCheckDying` includes null and event-bit checks absent from the PS2 routine. Status setters include extra HD bookkeeping/achievement calls. These additions were documented rather than copied into PS2 annotations as original behavior.

PS2 floating point instruction semantics still matter: `cvt.w.S` conversions in the effect routine depend on the floating-point control state. Decompiler C casts do not establish identical rounding. Some other PS2 formulas use software double helpers while HD uses floats or integer arithmetic. Exact numeric equivalence needs a separate validation pass.

## Reproduction and next targets

`tooling/record_calculation_matches.py` verifies the PS2 executable hash, compares the first 16 candidate bytes with the open program, preserves unrelated function names, and applies the reviewed TSV. It can also correct HD metadata signatures with opaque managed pointers and the hidden method argument. `tooling/export_calculation_reference.py` exports candidate information, instructions, callees, and decompiler output with explicit program selection. GUI script execution is disabled in this installation, so these operations use the local API's individual annotation methods.

Verification reread all 25 saved names/signatures and paired native metadata entries. The annotation export contains 29 user-defined function signatures and 184 total rows. Both open programs were saved. PS2 snapshot `backups/SLUS_209.11-2026-10-03-120541.gzf` is 11,312,775 bytes, SHA256 `032c45df1c7d7ca4e9c7ded800427adbf119e27fd94e53ab661862b545b2008b`.

The unnamed PS2 routines at `0x00242BC8`, `0x00242C48`, and `0x00244078` remain separate leads. In particular, `0x00242BC8` is not `datGetMagicHitPow`: its formula differs. Caller expansion from `datExecSkill`, battle result construction, random-number helpers, and a table-count/layout pass are the next useful targets. This establishes a substantial retained calculation cluster, not a whole-program reconstruction.

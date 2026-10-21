# Magatama mastery, parameters and skill eligibility

Seventeen routines in `src/hearts_parameters.c` pass 8,832 comparisons against isolated execution of their original PS2 instructions. Fifteen have reviewed native Unity counterparts; `ps2HeartsSkillAt` and `ps2HeartsAddParam` are chosen PS2 source aliases outside the counterpart ledger. The HD add-parameter method is an opaque protection stub. No original symbol spelling is asserted for either alias.

| PS2 entry | Recovered routine | Instruction cases |
|---|---|---:|
| `00221DD8` | `cmbChkGetHearts` | 256 |
| `002220C0` | `cmbGetHeartsSkillNums` | 512 |
| `00222140` | `cmbChkHeartsMaster` | 256 |
| `00222160` | `cmbGetMasterHeartsNums` | 128 |
| `002221E8` | `cmbSetHeartsMaster` | 256 |
| `00222210` | `ps2HeartsSkillAt` | 256 |
| `00222290` | `cmbGetHeartsAisyo` | 256 |
| `002222C0` | `cmbGetHeartsDefaultParam` | 1,024 |
| `00222318` | `cmbGetHeartsParamEx` | 1,024 |
| `002223A0` | `cmbGetHeartsParam` | 1,024 |
| `00222408` | `ps2HeartsAddParam` | 512 |
| `00222470` | `cmbSubHeartsParam` | 512 |
| `001FEDA0` | `cmbChkSkillOwner` | 512 |
| `002226B8` | `cmbChkGetHeartsSkill` | 1,536 |
| `00232998` | `cmpGetHeartsFromPos` | 256 |
| `002329B8` | `cmpGetHeartsIconTypeFromPos` | 256 |
| `002329D8` | `cmpGetHeartsIconColorFromPos` | 256 |

The current complete suite passes 65,464 cases across 101 compiled C routines. `behavior-validation.json` records every routine's PS2 entry, source and verifier hashes, and vector counts. Instruction-model agreement is separate from console execution and matching-binary recovery.

## State and descriptor fields

The state at global `+1D3B+ID` has mastery in bit `80`, proved by the mask/test at `00222150..158` and OR/store at `002221FC..22208`. The low nibble is the previously recovered learned-skill count. Bits4..6 remain unclassified. Master count iterates ownership entries and counts the mastery predicate; it does not deduplicate the list. The setter changes only bit7.

The shift/add sequence `ID<<5; +ID; <<1` establishes descriptor stride66. The checked view starts at `00339E00`:

| Offset | Established access |
|---|---|
| `+02` | Signed16 affinity; ID0 accessor returns0 |
| `+06` | Six signed normal parameter bytes |
| `+0C` | Six signed mastered parameter bytes |
| `+1A+slot*4` | Signed required-level byte |
| `+1C+slot*4` | Unsigned16 skill ID |

Other bytes remain unknown in `cmbHeartsRecord_PS2`. This view and the four-byte skill entry are saved as checked partial Ghidra types. `hearts-layouts.txt` records their layouts. The older skill-row view begins26 bytes into this descriptor; both host bindings now share the same backing buffer.

`cmbGetHeartsParamEx` adds an unsigned upgrade byte from global `+11DC0+ID*6+index` to the selected signed default, then sign-extends the low byte. `cmbGetHeartsParam` chooses the mastered default when bit7 is set. Its old inferred `void` return was wrong: calls at `002223D8/3E8` preserve V0 through the epilogue, and both parameter update loops consume it. The add/subtract routines update all six unit bytes at `+16`, preserving byte wrapping without saturation.

All shipped normal/master arrays are identical. Synthetic rows give the two arrays different signed values, with all256 upgrade-byte values represented, so tests can detect a reversed selection. Synthetic affinity and skill masks also test signed16 returns and high-bit skill IDs. They modify only isolated data fixtures; the code bytes and original files remain unchanged.

## Skills and icon table

Skill count inspects eight nonzero ushort IDs, ignoring required levels; ID0 returns0. The PS2 internally narrows the count to signed8, but its only results are0..8. The reconstructed signed16 return follows HD metadata; the original PS2 declaration width is not independently proved.

The owner helper at `001FEDA0` scans the unit's ushort count `+38` and inline ushort list `+3A`, returning the first matching index as signed8 or -1. Next-skill query starts at the global low-nibble count and scans through slot7. It skips zero IDs, zero required levels, levels above the unit's unsigned16 level, and already owned skills. It returns the first eligible ushort without modifying state. Required levels use PS2 `LB`, so negative synthetic level bytes follow a signed comparison.

The skill-query fixtures separately cover all256 level-eligibility masks, zero-ID masks and ownership masks, plus starting counts0..15 and signed-level boundaries. Unit/global buffers and auxiliary state must remain unchanged. Default acquisition fixtures now also run through `datAddHearts`, `datAddItem` and `fclAddItem` with selected level-zero skills and the unit inside global work, covering completion-event updates and duplicate suppression.

Position getters read the table at `00345E58`: signed ID at+0, signed icon type at+1, raw32 color at+4, stride8. The equipped-position caller consumes27 physical rows. Synthetic getter fixtures cover all signed byte values and color-bit boundaries while using valid indexes0..26.

## Port differences and transfer

HD uses managed arrays and objects. Unit skill count/list are wider there, and skill count/eligibility add protected DLC-event checks absent from the PS2 instructions. Parameter upgrades are signed managed bytes in HD; the final low-byte sum matches the PS2 unsigned load. These differences are recorded per function in `function-matches.tsv`.

Table contents also differ: every shipped PS2 position color is `80808080`; HD's first25 rows use values0..3 and only its final two rows retain `80808080`. Keep the PS2 table and raw32 interface when reconstructing this executable.

Transfer candidates are the mastery/count bit split, descriptor access pattern, byte-wrapping parameter path and owner/eligibility call chain. Re-establish all offsets, strides, capacities, IDs and table contents in each SMT executable. `hearts-menu-leads.md` records the next connected menu/skill-list batch; those leads are not counted as recovered source.

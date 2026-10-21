# DDS1 game data tables (USA SLUS-20974)

This is a map for the extracted `game/DDS3.DDT` and `game/DDS3.IMG`. It applies to the local USA v1.00 executable `SLUS_209.74` (MD5 `5c357d5afe565bea62c4ca613470f678`). No emulator state was changed for this investigation. File offsets below are relative to `DDS3.IMG`, not the disc ISO or EE memory.

## Archive and evidence

`DDS3.DDT` indexes paths in `DDS3.IMG`. A file entry is 12 little-endian bytes: name-string offset (`u32`), IMG sector (`u32`), and file size (`i32`); a negative size marks a directory and its absolute DDT child-entry offset occupies the sector field. IMG sectors are `0x800` bytes. The new `tooling/dds3_extract.py` can list or extract entries without loading the full IMG.

| Archive path | IMG offset | Size | Contents |
| --- | ---: | ---: | --- |
| `battle/AICALC.TBL` | `0x00068800` | 340,016 | Enemy action lists and scripts |
| `battle/ENCOUNT.TBL` | `0x000C2800` | 135,136 | Formations and zone encounter lists |
| `battle/MSG.TBL` | `0x000E3800` | 214,256 | Unit, item, skill names and Analyze text |
| `battle/SKILL.TBL` | `0x00118000` | 34,496 | Skill records and item definitions |
| `battle/UNIT.TBL` | `0x00195800` | 67,600 | Enemy stats, skills, drops, affinities |
| `fld/f/bin/FLDALL.TBL` | `0x18FDA000` | 79,184 | Includes chest definitions |

The four battle tables above (excluding MSG) use blocks with a `u32` byte count, payload, then padding to the next 16-byte boundary. Parsing their block sizes lands exactly at each file end. The local MD5 values for `SKILL.TBL`, `MSG.TBL`, `UNIT.TBL`, `ENCOUNT.TBL`, and `AICALC.TBL` match the [DDS1 Randomizer's source-file hashes](https://github.com/Astolfothetrapgod/DDS1-Randomizer/blob/main/randomizer/iso.py). Its [research notes](https://github.com/Astolfothetrapgod/DDS1-Randomizer/blob/main/NOTES.md) report in-game edits of enemy records, formations, zone lists, and skill power. Our field checks below independently read the unmodified local IMG.

## Skills

`SKILL.TBL` block 0 begins at file `+0x0004` and holds 608 `u16` element/category entries. Block 1 begins at file `+0x04D4` and holds **512 records of `0x38` bytes**. Skill ID `i` therefore starts at **IMG `0x1184D4 + i * 0x38`**. English names are ID-indexed in `MSG.TBL` block 7 (file `+0x17F04`, 624 slots of 17 bytes). The extra name slots include passive skills, which have no block-1 record.

| Record offset | Proposed meaning | Evidence |
| ---: | --- | --- |
| `+0x03` | Cost type: 1 = HP, 2 = MP | Encoded examples; `ApplySkillResourceCost` at executable `0x001D3238` indexes records by `skillId * 0x38` and branches on this byte at `0x001D32DC` |
| `+0x04` | Cost in MP or percent of maximum HP | Agi 3 MP, Maragi 8 MP, Venom Claw 12% HP; randomizer reports in-game cost checks |
| `+0x08` | Target, 0 = one, 1 = all | Agi 0, Maragi 1; inferred from records |
| `+0x11` | Accuracy percentage | Agi 99, Venom Claw 96, Hama 65; `ResolveSkillHit` at executable `0x001A7548` reads this field when resolving a skill hit |
| `+0x14`, `+0x15` | Minimum/maximum hits | Mad Rush 2/4, Venom Claw 1/1; inferred from records |
| `+0x16` | Effect nature, including 1 = direct damage and 8 = current-HP fraction | Randomizer's game edit confirms the nature-8 power behavior; other cases remain partly inferred |
| `+0x18` (`u16`) | Power | Agi 30, Maragi 25, Bufu 25; randomizer reports an in-game power edit |
| `+0x24..0x26` | Ailment enabled, chance percentage, ailment mask | Bufu `01 0F 04` (15% Freeze); Venom Claw `01 23 80` (35% Poison); values match reference tables |
| `+0x34` (`u8`) | Critical rate percentage | **All 26** player physical skills with numeric critical rates on the [Japanese DDS1 skill page](https://w.atwiki.jp/ddsat/pages/112.html) match; no other byte offset matched 15; live critical-roll behavior has not been traced |

The randomizer's savestates placed block 1 at EE `0x00F6AF80`; treat this as an observed load address, not a stable executable address. Ghidra shows that the cost routine reads the table pointer via `gp - 0x62A0` (global address `0x003BAA50` with this executable's GP `0x003C0CF0`).

A live breakpoint at `CalculateBaseSkillEffect` identified Materadyne as skill ID `0x2A`, matching its `MSG.TBL` name slot. Its record at IMG `0x118E04` matches the sampled live record at EE `0x00F6B8B0` (`0x00F6AF80 + 0x2A * 0x38`): accuracy `99` at `+0x11`, power `90` at `+0x18`, and effect multiplier `100` at `+0x22`. The separate element entry is `0x0006` at IMG `0x118058` and EE `0x00F6AAD4`. This establishes that the observed EE table is a loaded copy of the on-disc skill data for this record. An earlier paused HP effect was associated with skill ID `0x52`, whose `MSG.TBL` slot is the placeholder `0x052`; its power `75` and element code `0x000B` must not be attributed to Materadyne.

At the same live cast's return from `CalculateBaseSkillEffect` (`0x001A5F30`), `v0 = 0xFFFFFFD4` gave a signed base HP effect of `-44`. The formula VM's result at `0x003C2E80` was `44`, with a floating-point intermediate of about `44.1`. The four multiplier registers used immediately afterward (`f20` through `f23`) were each `1.0`. Serph's target stats were at EE `0x00EBD8A0`, with current/max HP `334/999` before this effect. The user confirmed the resulting 44 HP loss, ending at 290/999 HP.

| ID | Skill | Cost | Power | Crit | Other local bytes |
| ---: | --- | ---: | ---: | ---: | --- |
| 1 | Agi | 3 MP | 30 | 0 | accuracy 99 |
| 4 | Maragi | 8 MP | 25 | 0 | all targets, accuracy 99 |
| 10 | Bufu | 3 MP | 25 | 0 | 15% Freeze |
| 115 | Venom Claw | 12% HP | 18 | 10 | 35% Poison, accuracy 96 |
| 119 | Mad Rush | 15% HP | 11 | 2 | 2–4 hits |
| 129 | Chi Blast | 24% HP | 22 | 25 | accuracy 96 |

The linked [Fandom list](https://megamitensei.fandom.com/wiki/List_of_Digital_Devil_Saga:_Avatar_Tuner_Skills), [Megatenwiki list](https://megatenwiki.com/wiki/Skills_in_Digital_Devil_Saga:_Avatar_Tuner), and [Japanese physical table](https://w.atwiki.jp/ddsat/pages/112.html) disagree in places. The local records resolve four useful checks: Sakura Rage (ID 125) has 20% ailment chance; Death Blow (128) costs 22% HP and has 15% ailment chance; Vile Blade (134) has 14% critical rate; Venom Fang (135) has power 15. The Japanese site also has separate [magic](https://w.atwiki.jp/ddsat/pages/113.html), [combination](https://w.atwiki.jp/ddsat/pages/116.html), and [enemy-only](https://w.atwiki.jp/ddsat/pages/117.html) skill pages. Names can occur at multiple IDs: Maragi appears at IDs 4 and 432 with different records.

## Enemies, encounters, and items

`UNIT.TBL` block 3 starts at file `+0x23F4`, or **IMG `0x197BF4`**, with 384 enemy records of `0x4C` bytes. The [randomizer notes](https://github.com/Astolfothetrapgod/DDS1-Randomizer/blob/main/NOTES.md) and local bytes identify `+0x04` race, `+0x05` level, `+0x06/+0x08` current/max HP, `+0x0A/+0x0C` current/max MP, `+0x10..0x14` the five stats, eight `u16` skill IDs at `+0x18`, `+0x28` Macca, and `+0x2C` Karma. Block 4 (file `+0x9604`) has 19 affinity words per enemy. Unit names are in `MSG.TBL` block 3; `MSG.TBL` block 2 holds Analyze text.

Additional local matches identify `UNIT.TBL` block-3 `+0x2E/+0x30` as normal/hunt AP (`u16` each), `+0x3E/+0x3F` as two item IDs (`u8` each), and `+0x40/+0x41` as their drop percentages (`u8` each). **Twelve varied units matched** the [Japanese DDS1 enemy stat list](https://w.atwiki.jp/ddsat/pages/126.html), including bosses, with no counterexample. Isis (unit 2) reads AP 2700/5400 and bytes `67 56 0F 0A`: Theory Cell (item 103) 15% and MP Noise (86) 10%. Tutorial Ghoul (284) reads `01 00 64 00`: Ration (1) 100%. The actual drop-roll code has not yet been traced.

`ENCOUNT.TBL` block 0 begins at file `+0x0004`: 1024 formations of `0x28` bytes, with up to seven `u16` unit IDs at `+0x06`. Block 2 begins at file `+0xD064`: 128 zone records of `0x20C` bytes, each with four weighted encounter lists beginning at `+0x1C + list * 0x7C`. The randomizer reports in-game tests for formation slots and zone weights. Its [parser](https://github.com/Astolfothetrapgod/DDS1-Randomizer/blob/main/randomizer/tables.py) also maps `AICALC.TBL` actions, so an enemy's listed skills need not equal its scripted casts. [Japanese dungeon pages](https://w.atwiki.jp/ddsat/pages/159.html) list which enemies appear, but do not show formation combinations or weights; the older [GameFAQs bestiary](https://gamefaqs.gamespot.com/ps2/920605-shin-megami-tensei-digital-devil-saga/faqs/37764) offers an English area roster and notes incomplete drop coverage.

`SKILL.TBL` block 5 begins at file `+0x7EA4`: 192 item records of 8 bytes. Item names are in `MSG.TBL` block 4 (192 slots of 25 bytes). Local item 1 (Ration) is `03 04 10 01 32 00 00 00`: usage 3, triggered skill 272, base value 50. The [randomizer notes](https://github.com/Astolfothetrapgod/DDS1-Randomizer/blob/main/NOTES.md) map chests to `FLDALL.TBL +0xDAD8` (256 records of 16 bytes); shop stock and Karma Temple bonus tables instead reside in the executable at file offsets `0x269CF0` and `0x26AA88`. Mantra definitions also reside in the executable, at file `0x2917B4` (98 records of 28 bytes, with up to ten skill IDs at record `+0x08`). These executable offsets are **file offsets**, not EE addresses.

## Next checks

- Trace the skill critical-roll reader to confirm `+0x34` in executable code and distinguish base rate from modifiers.
- Trace item-drop selection and AP award readers to confirm `UNIT.TBL +0x2E/+0x30/+0x3E..+0x41` semantics.
- Use a user-driven paused battle breakpoint to tie an encounter's zone ID and formation ID to the `ENCOUNT.TBL` records. No breakpoints or guest state were changed in this pass.

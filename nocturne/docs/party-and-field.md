# The party outside battle

How the save game's party is changed outside battle: skills used from the
menu, damage from the field (dungeon traps, Amala pipes), the stock, Macca,
items, boss refights, and the FlowScript commands that drive them
(`scrParameterCommand`, the `prm_*` commands).

Source: `source/shared/src/data/field_skill.cpp`, `source/shared/src/data/progression.cpp`
(original unit `datCalc`), `source/shared/src/script/parameter_commands.cpp`.
Tested against the original instructions (`data_tests.cpp`,
`script_tests.cpp`).

## Skills from the menu

`datExecSkill` uses a skill on a unit with the battle formulas
([battle-mechanics.md](battle-mechanics.md)), simplified: no buffs, no
difficulty multiplier, no debug prints, and the user's own stats rather than
a battle slot's.

- Physical: (2 Lv + 2 St) x 1.33 for a normal attack or x power / 23.2 for a
  skill, x 0.8 (x 0.6 and minus 48 or 50 / (Lv + 10) for an enemy user).
- Magic: as in battle, but the level is not capped at 160.
- Healing magic: (4 Ma + Lv + rand(8)) / 10 x power.
- Damage from power gets the +-5% spread and the target's affinity (as a
  rate; elements 12..14 and no element count as 100%).

Quirks kept: the spread and affinity step follows the skill's HP type even
for MP; damage is never 0; and a skill whose HP type changed nothing (for
example "reduce to 1" on a unit already at 1) returns 1, which heals 1 HP.
Skills with `program` 8..11 set bits 0..3 of an unidentified global word
(`GlobalWork+0xA4C`) even without a user or target.

## The field's damage

| Function | Mode | Effect on party members with HP left |
|---|---|---|
| `datPartyDamage` | 1, 4, 5, 6 | lose a tenth of their HP; 4..6 then poisoned, stunned, muted |
| | 2 | lose half |
| | 3 | down to 1 HP (not Dante) |
| `datPartyDamageFld` | 1 | the poisoned lose 3% |
| | 2 | everyone loses 3% |
| | 3 | 1% or 2% at random (no difficulty) |
| | 4 | half (no difficulty) |
| `datPartyDamagePipe(big, small)` | | big x a tenth + small x 3% |

Damage is tripled on Hard and never kills: at least 1 HP is left.
`datPartyKaifuku` restores every stock member's HP and MP and clears its
ailment.

## Stock, Macca, items

- Macca is kept in 0..9,999,999. `prm_MAKA_PLUS_PER` changes it by a
  percentage.
- Items below 0x70 stack to 99; the others are held once.
- Story demons carry a unique ID (flag 0x400); the first Pixie is unique
  ID 1 and also flag 0x1000 (`prm_*_PIKUKO`). `prm_UDV_DELETE_NG` sets 0x800
  (tentatively: can't be dismissed).
- `prm_STOCK_PLUS` grows the stock up to 12.
- `prm_DV_PLUS(devil, join, unique)` adds a demon unless one of its kind is
  in the stock (join 2: into the party without a compendium entry); with a
  unique ID it always adds one.

## Boss refights

The 40 `datBossPress_t` entries at 0x3FA430 (`flag`, `flag2`, `encid`,
`dbest`) are the refightable bosses: `flag` is the event bit that opens the
refight, `flag2` the bit a new record sets, `dbest` the press turns to beat.
The save keeps each refight's best and last press turns.
`datBossRashChk` tells the battle code that a fight is a refight (lower
rewards); two story encounters (0x3E0, 0x3E1) count as their refights' for
records.

## Skills that would do nothing (`nbSkillError`)

Before a skill is used, in battle or from the menu, the game refuses one
that can't change its targets (`source/shared/src/battle/skill_error.cpp`):

- HP healing with every target at full HP, MP healing at full MP, and the
  full restores with both full: "no effect" (error 1).
- A cure for an ailment none of the targets has (error 1).
- Revival (0x31, 0x32) with no one in the stock dead (error 2).
- A buff whose every counter is already at its limit (errors 3 and 4).
- From the menu, a single dead target for anything but revival (error 1),
  and Estoma, Riberama, Liftoma or Lightoma while it is already in effect
  (error 4; the global work's `fieldskills` bits 1, 2, 4, 8).

Errors 2 and 4 say so on the help line; errors 1, 2 and 4 make the error
sound (13). In battle, the always-hit debug bit skips the check.

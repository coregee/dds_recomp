# Magatama and the compendium

As established by `source/shared/src/data/magatama.cpp` and
`source/shared/src/facility/compendium.cpp` (original names in parentheses).

## Magatama

Magatama 1..25 are described by `fclHearts_tbl` (0x339E00, `MagatamaData`);
0 means none. Masakados is 25, so "all normal Magatama" means 1..24.

**Owning.** `GlobalWork::hearts_owned` lists owned Magatama in the order they
were obtained (`hearts_owned_count` entries). Items 0x40..0x58 are Magatama:
`fclItemHeartsTbl` (0x53D6E8) maps them (`fclChkItemHearts`), and picking one
up (`datAddItem`, `fclAddItem`) adds it instead of counting an item
(`datAddHearts`). A new Magatama would teach the Demi-fiend its level-0 skills
at once, but no Magatama has any in the shipped data; owning all of 1..24 sets
event 0x860.

**Stat bonuses.** While equipped, a Magatama adds its `growparam` to the
Demi-fiend's stats (`mastergrowparam` once mastered), plus a per-Magatama
upgrade in `hearts_param_upgrades` (`cmbGetHeartsParam`). The bonus is added
to `UnitWork::param` on equipping and taken off on unequipping
(`ps2HeartsAddParam`, `cmbSubHeartsParam`, called from `datEquipHearts` /
`datRemoveHearts`), so code that wants the Demi-fiend's own stat subtracts it
again (`cmbGetParamBase`, `datGetPlayerParam`). Its `aisyoid` replaces the
Demi-fiend's affinity row (`cmbGetHeartsAisyo`), and `autoasignparam` weights the Demi-fiend's level-up stat gains.

**Skills.** Each Magatama has 8 skill slots `{level, skill}`, learned in
order: `hearts_skill_state[id]` counts the learned ones in its low nibble
(`cmbGetHeartsAfterSkillNums`) and bit 7 marks mastery
(`cmbChkHeartsMaster`); `hearts_learned_skills[id]` lists them. The next
skill is the first unlearned slot whose level is reached and that the
Demi-fiend doesn't know (`cmbChkGetHeartsSkill`). The results screen lists
what is still to come (`rstCreateBeforeSkillList`; for demons, the growth
table's skills above their level).

**The Demi-fiend's "race"** (`cmbGetPlayerRaceID`, used for the Demi-fiend's alignment
in `datGetPlayerLND`) comes from mastered Magatama. Each has a stat class
(`flag & 7`); among mastered ones, class 1 or class 4 dominates if it
outnumbers the other and isn't itself outnumbered by class 0
(`cmbChkMasterHeartsStatNums`). A tier comes from how many are mastered:
half the count below 6, 3 below 12, then 4, and 5 for all 25. The race is
0 with no tier, else 3 × (tier − 1) + 1, 2 or 3 for class 1, neither, or
class 4; `datGetPlayerLND` reduces it to (race − 1) mod 3.

## The compendium (`fclEncyc`)

Up to 184 records (`fclencyceelem_t`, 0xB0 bytes) in
`GlobalWork::encyc_records`, one per devil ID, in registration order, with
the count in `encyc_count`. A record is a snapshot of a demon: max HP/MP, EXP,
level, stats and bonuses, skills, inherited skills, evolution data, and flags
0x40 and 0x200 only (`fclEncyc_SetElem`).

- **Registering** (`fclEncycRegist`) adds a new record (result 0) or, if
  allowed, overwrites the existing one (result 1); -1 otherwise, or when all
  184 are used (with a "FATAL!! The encyclopedia record is bound to burst"
  debug message). New demons are registered automatically (`datAddDevil`).
  Event 0x913 tracks 100% completion; the percentage is count × 100 / 184,
  but at least 1 once anything is registered (`fclEncycGetRatio2`).
- **Out of date** (`GetValidUnitIndex`): stock demons that are alive and not
  flagged 0x10 and differ from their record. `CompareUnitToRecord` reports the
  first difference (1 flags, 2 max HP, 3 max MP, 4 EXP, 5 level, 6–9 stats,
  skill bonuses, Mitama bonuses, level-up counters — stat 1 is skipped — 10
  skill count, 11 skills, compared as sets, 12–13 evolution data). A demon
  with no record is compared with the bytes before the record array, so it
  normally counts as out of date.
- **Summoning** (`SetRecordToUnit`) rebuilds a demon from the species
  defaults and its record, at full HP/MP.
- **Sorting** for the menu: by race then highest level, or by highest level
  then race (`CreateSortIndexByRace` / `ByLevel`, through the game's `qsort`).
- `fclEncycDebugRegist` registers the whole stock with Strength one lower,
  apparently to test the update path.

# Fusion and demon growth

How the Cathedral of Shadows and demon progression work, as established by
the rewritten code (`source/shared/src/fusion/`, `source/shared/src/data/progression.cpp`).
Original function names are in parentheses; all tables are in
`source/maniax/src/data/fusion_table.cpp`, `growth_table.cpp`, `inheritance_table.cpp`.

## A fusion, step by step (`cmbGetBirthDevil`, `cmb::fuse`)

1. **Refusals.** Dante can't be fused (`cmbChkDante`), nor two of the same
   devil, nor a sacrifice identical to either parent.
2. **Order.** The parents are ordered higher level first (ties: the second
   parent first). This order matters for the sacrifice patterns below.
3. **The result devil:**
   - *Two devils* (`cmbCalcDevil2`), first rule that applies:
     1. A fixed pair (`fclExtPatternTbl`, either order), e.g. Rangda + Barong.
     2. An **Element** with any devil (except a Fiend) moves that devil one
        rank up or down its own race (`fclRankUpDownTbl` gives the direction
        per Element and race; cursed fusion reverses it). Two Elements make a
        **Mitama** (`fclBirthSpiritTbl`).
     3. A **Mitama** with a devil: the devil itself, with stats raised (below).
        Two Mitama: whatever the race table says (nothing).
     4. Different races: **normal fusion.** Same race: an **Element**.
   - *With a sacrifice* (full Kagutsuchi): a fixed trio
     (`fclIkenieExtPatternDevTbl`), then "normal result + sacrifice"
     (`...Dev2Tbl`), then "devil + race of the other + race of the sacrifice"
     (`...DevRaceTbl`), then three races (`fclIkenieExtPatternTbl`, giving a
     race; the devil is chosen as in normal fusion from the three-way average),
     and otherwise the two-devil rules — except that a Mitama boost or a
     devil listed by `cmbChkIkenieIllegalDevil` gives nothing.
4. **Fiends.** If the result came from normal fusion (with or without a
   sacrifice), the Demi-fiend carries a **Deathstone** (item 0x8D) and the
   result's race and the Kagutsuchi phase select an entry of
   `fclCombineManinTbl`, the result becomes that Fiend — unless a parent is a
   Fiend, in which case the fusion fails (`cmbCalcCombineManin`).
5. **Accidents** (only when the caller allows them, and only for normal,
   Element, Mitama, rank-shift and plain sacrificial fusions): probability
   1/16 at new or full Kagutsuchi, 1/256 otherwise (`cmbChkAccident`). The
   result is replaced by a random devil 1..168 that is not a Corpus, not
   event-locked, between 15 levels below and 3 above the Demi-fiend, not
   already owned and not special-fusion-only (16 tries, then the last entry of
   `fclAccidentFailTbl` not owned). Accidents skip the sacrifice's EXP.
6. **Building the devil** (`cmb::fuse`): a fresh devil of the result species
   (or, for a Mitama boost, a copy of the boosted devil), the parents'
   inheritable skills offered, a sacrifice's EXP and skills added, then
   inherited skills learned at random. A cursed parent makes a cursed result
   (`UnitWork::flag` 0x1000).

Event-locked devils (`fclEventDevilTbl`, until an event bit is set),
special-fusion results and special-fusion-only devils (`DevilFormat::flag`
0x2) are never chosen by the general rules.

## Normal fusion

- **Race:** `fclCombineTbl[lower race − 1][higher race − 1]` (cursed fusion
  uses `fclCombineCurseTbl`); Fiends count as Tyrants. On the diagonal the
  table holds an Element's *devil ID* (36–39), which is how same-race fusion
  makes an Element.
- **Level:** (a + b + 1) / 2 + 1, or (a + b + c + 2) / 3 with a sacrifice,
  from the species' base levels — or the units' current levels in the mode
  the caller selects.
- **Devil:** among fusible devils of that race sorted by level (highest
  first), the weakest whose level is at least the target; if none, the
  strongest (`cmbGetTargetDevil`). Ties keep the order of the C library's
  `qsort` (not stable), which is why `libc::qsort` is reproduced exactly.
- Devil 0xCD (Sakahagi) only results from cursed fusion.

Element rank shifts walk the same sorted list (`cmbGetRankUpDownDevil`); the
first entry of the list is never a result. Races 31 and 33–39 (boss races)
have no Element entry; fusing one with an Element would loop forever, which
only can't happen because such devils can't be owned.

## Mitama boosts (`cmbCalcParamPowerUp`)

Each Mitama raises two stats (`fclSpiritParamUpTbl`) by adding to the devil's
`mitamaparam`: rate% of the stat minus the stat (at least +1), added to the
current bonus, never more than doubling the stat and keeping stat + bonus ≤ 40.

## Skill inheritance

- **Offered skills** (`cmbAddKeisyoSkillFromSkill`): each parent's first 8
  skill slots, if the result doesn't know the skill and can inherit it
  (rate > 0). A skill offered twice is marked in `keiattr`.
- **Rate** (`cmbCalcKeisyoSkillRate`): the score for (the result's
  inheritance type, the skill's element) from `InheritanceScores`, divided by
  the skill's inheritance level, plus (unit level − species level) + 1,
  capped at 99; 0 if the skill's form mask excludes the result's body type.
- **How many are learned** (`cmbRndAddKeisyoSkillToSkill`): (total skill
  count of the parents and sacrifice + 2.7) / 3.7, truncated, and never past
  8 skills in all. Each pick is weighted by rate (`cmbRndGetKeisyoSkill`).

## Sacrifice EXP (`cmbCalcIkenieExp`)

The result gains 1.5 × the sacrifice's EXP — and also, apparently by
mistake, the total EXP for its current level. The levels gained (capped at
255) each give a random stat point as at a normal level-up, but without
advancing the level-up counters. The result is flagged 0x200.

## Growth (`fusion/growth.cpp`)

- **EXP to reach level L** (`cmbCalcLevelUpExp`): base(L) = 1.42 L³ − 5. The
  Demi-fiend needs base(L); a demon of species level S needs
  base(L)·k − base(S)·k with k = 2.7 − 0.017 S, plus any EXP it had before
  evolving.
- **Stat gains** (`cmbAddLevelUpParamEx`): each stat has a weight (the
  species' `growparam`; for the Demi-fiend, the equipped Magatama's
  `autoasignparam`) and a counter. Stats with the fewest completed weight
  cycles compete, each in proportion to what it still lacks of its cycle.
  Stat 1 and stats at 40 never rise.
- **Skills** are learned from the growth table (`fclSkill`, event type 1) at
  their level; type 5 is evolution into another devil, type 7 its notice.
  Evolution keeps the devil's flags, unique ID and EXP (remembered as
  `hensinmaeexp`) and every old skill the new form can inherit.

## Party upkeep (`data/progression.cpp`)

- New demons go to the first free stock slot (`units[4..]`) and the display
  list; they join the party if it has fewer than four active members (the
  Demi-fiend included).
- Life/Mana Aid, Victory Cry and Life/Mana Refill restore max HP or MP divided
  by the skill's `datSpecialSkill` value.
- Lucky Find: on each check, every active member who has it rolls a random
  0..31 against Luck × 128 / 100 (raw Luck, an optional event bit can
  disable it).
- Reason points are capped at 128; ranking breaks ties with a coin flip each
  time two Reasons are compared.

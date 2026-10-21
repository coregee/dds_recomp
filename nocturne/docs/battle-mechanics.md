# Findings from the rewrite

Things that became clear while turning the legacy code into readable code.
Mechanics notes are about the PS2 US release (`SLUS_209.11`); the HD remaster
differs in places.

## Corrections for the legacy sources

These do not affect the legacy code's behaviour (it is validated against the
original instructions), only its names and comments. `legacy/` is frozen, so
they are recorded here and fixed in Ghidra and `source/` instead:

- **`nbMainProcessData_PS2_prefix::flag` at +0x60 is `stat`.** The HD
  `SetDebugFlag` writes the same bits to `stat` (HD +0x7C), and the HD field
  order places `stat` at PS2 +0x60 and `flag` at +0x64.
- **`ps2CombatCheckPlayerInitiative_00269AD8` (nbCheckSensei) returns 1 when
  the enemies act first.** Its caller (0x247DA0) sets battle-stat bit 0x80 on
  a nonzero result, then rolls the back attack. "Player initiative" reads the
  wrong way round.
- **`ps2CombatCheckEnemyInitiative_00269D20` is nbCheckBackAttack** (ambush),
  not an initiative check; it only runs after the enemies won the initiative.
- **`ps2CombatCheckEscape_00269E98` returns 1 on a successful escape**
  (caller 0x257230 sets `endtype = 3`).
- **`ps2CombatEffectType` "classification" (`descriptor+2`) is `koukatype`**:
  0 physical, 1 magic, matching the 物理/魔法ヒット率 debug strings.

## Mechanics

- **First strike** (nbCheckSensei): the player keeps the initiative with
  probability `chance/128`, `chance = clamp(72 + playerScore - enemyScore, 70, 85)`,
  `score = Level + Luck/2 + Agility` (Demi-fiend vs. encounter averages).
  Unless the Demi-fiend is 15+ levels above, an area table coefficient
  (1, 0.9, 0.8, 0.6, 0, 3) scales it. On Normal, a lost roll gets a second
  50/50. Encounter flags 0x04/0x02 force player/enemy first.
- **Ambush** (nbCheckBackAttack): a flat 12% (4% with Mind's Eye). The
  level/stat scores are computed but only printed — they never affect the roll.
- **Escape** (nbCheckEscape): certain if the encounter allows it or no enemy
  can act (shocked, frozen, asleep, bound, stunned or stoned). Otherwise
  `2 x (20 x attempts + 20 x party(Ag+Lu)/enemy(Ag+Lu))` percent, x1.5 with
  Fast Retreat. **On Hard it always fails** past the certain cases. Under a
  full Kagutsuchi a successful roll must also pass a further 5/8 check; that
  check tests the Normal flag again, which is always set by then.
- **Criticals**: physical only. Shocked/Frozen targets x100 (effectively
  certain), Sleep/Bind x8, Might x3 on normal attacks; Bright/Dark Might are
  guaranteed when they activate. A weakness hit takes priority over a crit.
- **Accuracy**: physical `100 - failpoint + (agilityScore diff)/16`; magic
  `100 (95 for enemies) + (100 - 100 x evasion/magicAccuracy)/2`. Then buffs,
  the skill's `hitlevel`%, clamp 50..100, and x0.25 if the attacker is
  stunned (applied *after* the clamp). Helpless targets are always hit.
- **Normal-mode mercy**: skills with `hptype 3 / hpn 1` (e.g. Evil Gaze) hit
  the player's side at 70% of their usual accuracy.
- **Freeze** removes physical Null/Repel/Drain. **Pierce** ignores Null and
  Drain on physical skills but not Repel.
- **Stone shatter**: Physical or Force on a stoned target kills with chance
  `100 - Luck/((Level+20)/5) x (40 Demi-fiend / 20 demons)`, at least 20%.
- **Ailment recovery** at turn end: Shock and Freeze always clear; Sleep,
  Panic/Bind and Charm clear with `20/30/40 x Luck/((Level+20)/5)` percent.
- **EXP penalty**: outlevelling an enemy (below level 70) by 6-11 divides its
  EXP by 1.3, by 12+ by 1.8. Enemies of level 70+ only get /1.3 from 6 up.
  Boss refights give a tenth of EXP and Macca and no items.
- **Drops**: at most one item per enemy: special drop (event-gated), else the
  two ordinary drops, else Bead, else Life Stone. The Bead and Life Stone
  rolls consume RNG even when something already dropped. A fifth distinct item
  is lost; the encounter's guaranteed item instead pushes the oldest out.
- **HP model scale**: combatants shrink linearly with HP, down to half size.
- **Consecutive encounters**: each area table entry has its own chance and
  successor. Global-work bit `0xA4C & 2` quintuples the chance (unknown
  source). Encounter flag 0x10 forces encounter 0x149.
- Encounters 0x10B and 0x11C cap rewards at 20,000 EXP / 10,000 Macca.

## Data

- Two float constants in the executable were rounded toward zero by the
  original toolchain (`0.1` = `0x3dcccccc`, `0.001` = `0x3a83126e`), one ulp
  below what a modern compiler produces for `0.1f` / `0.001f`.
- The encounter-pack table (`datEncountPack`, 0x3BADE0, 420 bytes) is a
  20-byte header plus four 100-byte `datEncountTbl`s of twelve 8-byte
  `datEncountRitu` entries, exactly as in the HD field lists.

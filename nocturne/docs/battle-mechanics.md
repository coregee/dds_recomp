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

## Damage

Source: `source/src/battle/damage.cpp`, `affinity.cpp`, `buffs.cpp`.

- **Physical power** (nbGetButuriAttack): `2 Lv + 2 St`, then for the normal
  attack `x 1.33 x k`, for skills `x power / 23.2 x k`, with `k = 0.8` on the
  player's side and `0.6` for enemies. Enemies also lose `48/(Lv+10)` (`50` for
  skills, integer division) and get `x1.34` on Hard. Times the attacker's
  Attack buff and the defender's Defense buff.
- **Magic power** (nbGetMagicAttack): `magicbase + 2 Lv power / 21`, capped at
  `magiclimit`, then `+ base/100 x 2.5 (Ma - (min(Lv,160)/5 + 4))` and `x0.8`
  (in software double precision). Enemies: `x0.75 - 50/(Lv+10)`, `x1.34` on
  Hard. Times Magic and Defense buffs.
- **Magic healing**: `(4 Ma + Lv + rand(8)) / 10 x power x Magic buff`.
  Physical healing reuses the physical formula.
- **Max-HP skills** (hptype 6/7): `maxHP / 69.6 x power x 0.8` (enemies: base
  max HP `x0.6 - 50/(Lv+10)`, `x1.34` on Hard).
- **Final HP damage** (nbGetKoukaHp): power + `hpbase`; poisoned attackers do
  half physical damage, Fly a tenth; spread ±5% (physical) or ±10% (magic);
  times the affinity ratio; on Normal, damage from enemies `x0.7`. HP damage
  is never 0 (minimum 1). Drain types (12/13) are capped at the target's max
  HP, MP damage at its current MP. hptype 14 splits damage between targets.
  Other hptypes: 3 reduce to `power` (Evil Gaze: to 1), 4/13 fixed, 5 fixed
  heal, 8–11 percentage of current/max, 15 `rand(power)` heal.
- **Affinity ratio** (nbGetAisyoRitu): `rate/100`. Repel/Drain entries with no
  rate count as 100%. Against a frozen target, or with Pierce, physical
  skills treat resistance as 100%. Son's Oath, or Fire/Ice/Elec/Force Boost for
  their element, multiply by 1.5.
- **Affinity resolution** (nbGetAisyo), in order: the party's current
  affinity row (the Demi-fiend's comes from his Magatama); an override row from
  buff counter 19; the Fly row (200% everything) or Stone row (10% Fire/Ice/Elec,
  Null to Expel..Mind); temporary nulls (counters 9–12, e.g. Tetraja for Expel
  and Death); Tetrakarn/Makarakarn add Repel to physical/magic skills of any
  element but Almighty; then passives: Void-X adds Null, X Drain / X Repel
  (Phys..Force only), Anti-X halves the rate. Priority when several apply:
  Repel > Drain > Null.

## Buffs

- Counters 4–8 (Attack, Magic, Evasion, Defense, Accuracy) run −4..+4.
  Multiplier: raised `n` → `1 + n/4`; lowered → `1 − n/8`. Defense and Evasion
  are applied to the *opponent's* roll, inverted: Rakukaja +n cuts incoming
  damage to `1 − n/8`, Rakunda −n raises it to `1 + n/4`.
- Focus (counter 15) makes the next physical attack `x2.5`.
- Dekaja/Dekunda (hojotype bits 10/18) zero the raised/lowered counters; they
  run after the other changes and even in AI preview mode.
- Devil 0x125's buff counters shift with the moon: `+(age − 4)/2`.

## Ailments

- **Infliction** (nbGetKoukaBadDamage): blocked by Null/Repel/Drain on the
  ailment's element (Shock: Elec, Freeze: Ice, Sleep/Panic/Charm: Mind,
  Bind/Stun: Nerve, Mute/Poison: Curse, Stone: Death, Fly: Almighty).
  Chance `badlevel% x element rate` (instant death uses the damage ratio
  instead). Against the player's side: `x0.7` on Normal (instant death on the
  Demi-fiend `x0.5`); on Hard, instant death `x1.5` (`x1.3` on the
  Demi-fiend). The ailment only lands if it outranks the target's current one.
  Special cases: skill 0x110 picks from a fixed distribution; Stinger (and Holy/Evil
  Melody's instant kill) fail in boss battles (battle stat bit 1, tentative); 0x103/0x104 fail if the target resists Death;
  0x04F (Pestilence) needs a poisoned target.
- **Curing** (nbGetKoukaBadKaifuku): would roll `badlevel% x (caster Ma +
  Lu/4) / (target Ma + Lu/4)`, but every curing skill in the US data has
  badlevel 255, so cures always work.
- **Endure / Never Yield**: survive a fatal hit once; party flag 0x200 marks
  it fired, 0x400 spent for the battle.

## Data

- The original toolchain rounded decimal constants toward zero, so many
  differ by one ulp from a modern compiler's (`0.6` = `0x3f199999`, `0.1` =
  `0x3dcccccc`, the double `0.8` = `0x3fe9999999999999`). `ee::literal()`
  reproduces this at compile time.
- The encounter-pack table (`datEncountPack`, 0x3BADE0, 420 bytes) is a
  20-byte header plus four 100-byte `datEncountTbl`s of twelve 8-byte
  `datEncountRitu` entries, exactly as in the HD field lists.

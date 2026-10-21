# Enemy AI

As established by `source/src/battle/ai.cpp`, `ai_script.cpp` and
`targeting.cpp` (original names in parentheses). The data is
`source/src/data/devil_ai_table.cpp` (`datDevilAI`, 0x3989E0).

## The AI record

Every devil ID has a `DevilAI` record (`datDevilAI_t`):

- `scriptid`: an AI script (a flowscript run instead of the table AI), or 0.
  244 of the 384 devils have one (122 share script 70); scripts use the same
  building blocks through the `nbCommand_AI_*` commands below, including
  `AI`, which runs the table AI.
- `ailevel`: how targets are chosen when the action doesn't name a selector
  (0 anyone, 1 the best estimated effect, 2 the best among targets that
  don't nullify / repel / drain it), and whether skill costs are respected
  (levels 1 and 2 only). **Every devil has level 0 in the shipped data**, so
  the effect-scoring target choice and the cost checks are dormant code.
- `aichk[3]`: checks tried in order. Each has two conditions and an action
  table; the first check whose conditions both hold picks its table,
  otherwise table 0 (`nbRunAi`, `nbAiAiChk`).
- `aitable[3][5]`: actions `{weight, skill, target}`. The skill is a skill
  ID, or a command: 0x8000 attack, 0x8001 escape, 0x8002 pass, 0x8003
  command 9; 0x9xxx..0xFxxx call for help (skills 0xE2, 0xE3, 0xE5, 0xE6,
  0xFC, 0xDE) with the devil to call in the low 12 bits (`nbAiSetKoudou`).
  The target is `(selector << 16) | parameter`.

## A turn of the table AI (`nbRunAiSub`)

1. Draw an action from the table by weight, among those not yet struck off
   this turn (`nbAiGetKoudou`, one RNG draw).
2. Make it the unit's command (`UnitWork::nowcommand` / `nowindex`).
3. If the unit can pay for it — or its AI level ignores costs — choose
   targets (`nbSetAiTarget`). Otherwise, or if no target qualifies, strike
   the action off and draw again.
4. With nothing left, the unit passes (command 3).

## Conditions

`(type << 16) | n`; type 0 always holds. A condition that holds also marks
the combatants it is about in `ActionProcessData::aiselect` (one bit per
formation index); the second condition of a check narrows the first one's
marks. "Enemies" are the player's side (formations 0..3), "allies" the AI's.

| Type | Condition | Holds when |
|---:|---|---|
| 1 | MYHP | own HP ≤ n % |
| 2 | FRHP | an ally's HP ≤ n % (marks them) |
| 3 | DMGCNT | hit ≥ n times (buff counter 0) |
| 4, 21 | CHKCNT | this check evaluated ≥ n times (counters 1..3; type 4 resets on success) |
| 5 / 6 | FRCNT / ENCNT | at most n allies / enemies |
| 7 / 8 / 9 | MYBAD / FRBAD / ENBAD | own / an ally's / an enemy's ailment is n |
| 10 | ENALLBAD | every enemy has ailment n |
| 11 / 12 | ENID / FRID | an enemy / another ally is devil n |
| 13 / 14 | ENHOJO / FRHOJO | an enemy / ally has buff code n |
| 25 / 26 | ENHOJOMAX / FRHOJOMAX | ... at its limit |
| 15 | BA | back attack (BattleStat 0x10) |
| 23 | SENSEI | the enemies struck first (BattleStat 0x80) |
| 16 / 17 | ENLIGHT / ENDARK | an enemy demon of Light / Dark alignment |
| 18 | POW | own Focus |
| 19 / 20 | PLV / PPARTYLV | Demi-fiend's level / the player side's average level ≥ n |
| 22 | TURN | turn ≥ n |
| 24 | MYMP | own MP ≤ n (a value, not a percentage) |
| 27 | ENHAMAMHK | an enemy without Null/Repel/Drain against Expel |
| 28 | SKILLNOMP | can't pay for skill n |

Buff codes: 0..9 are -kaja (even) / -nda (odd) for the counters 4..8
(attack, magic, evasion, defense, accuracy); 11..17 the counters 9..15
(temporary nulls, Makarakarn, Tetrakarn, Focus); 10 and 18+ never hold.

## Targets

`nbGetTargetTypeRuleArea` reads the action's targeting from its skill
(type: one / group / all; rule: self only, not self, empty summon slots;
area: own side, other side). `nbSetSelectOkMark` marks the targetable
slots (`FormationStat::Selectable`). Then the selector narrows them
(`nbSetSingleTarget2`):

| Selector | Picks |
|---:|---|
| 0 | by AI level (`nbAiSelAi`) |
| 1 | lowest HP |
| 2 | ailment n |
| 3 | devil n |
| 4 / 5 | Light / Dark demons |
| 6 | the Demi-fiend |
| 7 | whoever the conditions marked |
| 8 | anyone (then one at random) |
| 9 | lowest level, not flying |
| 10 | lowest level |

If a selector marks nobody, the AI level decides; with several marked, one
is kept at random. Group actions take everyone targetable.

Quirk: with AI level 2, the best-scoring target is found among the
non-immune targets but then located by counting *all* targetable slots, so
an immune slot earlier in the line shifts the choice to a different
combatant.

## Calls for help

A summon action marks empty enemy slots, up to the encounter's party size,
as summon slots (`nbSetEnemySummonFormation`, when the battle allows it)
and sizes them for the devil to be called.

## Script commands

`AI_CHK_*` evaluate a condition (parameter from the script) and return the
result; `AI_GET_*` return the turn, the "press" counter (buff counter 18),
own level, own affinity row, or the Kagutsuchi phase; `AI_ACT_*` set
attack / escape / skill / summon; `AI_TAR_AI` chooses targets;
`AI_SET_CRITICAL` makes the next hit critical; `AI` runs the table AI; and
`BTL_AI_ROT_*` keep a counter for rotating through actions. `BTL_PNL_ON`
and `BTL_CAM_ORG` do nothing on the PS2.

## Normal attacks

Before attacking, `nbSetNormalSkill0` rewrites skill 0 (the normal attack)
in the skill tables for the attacker: its element and hit count come from
the devil's `attackattr` / `attackcnt`, and Attack All makes it hit
everyone. Skills 0xA4..0xA7 get the same treatment.

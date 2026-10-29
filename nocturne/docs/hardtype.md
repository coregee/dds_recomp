# Hardtype 1.5.1

A fan rebalance of US Maniax, distributed as a patch: the executable keeps
every US Maniax address, so its delta is the bytes it changes.

- **Data:** about 91,000 bytes, almost all in tables the source already
  models (devils, skills, encounters, affinities, growth, fusion, AI).
  `python tools/gen_tables.py --variant hardtype` writes the tables that
  differ into `source/generated/hardtype/src/data/`; `NOCTURNE_VARIANT=hardtype` with
  `source/tests/tables/build.cmd` proves them byte for byte.
- **Code:** 73 functions patched (62 of them rewritten in the base so far).
  Most patches are short jumps into about 5.7 KB of new code that Hardtype
  places in space that is empty in US Maniax (0x2FDC20..0x2FF388). Its own
  small state lives there too (`nocturne/hardtype.hpp`).

`tools/ghidra/ExportVariantDiff.java` lists the patched functions with
their changed instructions, and the new code (import the executable into the
Ghidra project as `/hardtype/SLUS_209.11` first).

## What it changes beyond values

Several tables keep their address and size but change their layout, so the
records differ by version (`nocturne/data/version_tables.hpp` and `devil_ai.hpp`, under
`NOCTURNE_HARDTYPE`):

- **fclEventDevilTbl:** 68 four-byte rows instead of 34 eight-byte ones.
- **fclKeisyoSkillLevel:** 302 three-byte rows instead of 227 four-byte
  ones, read with unaligned halfword loads.
- **datDevilAI:** a table of record pointers by devil (at 0x3989E4, each
  4 past its record) and variable-length records, instead of 384 records of
  0xA4 bytes: a header (check count, table count, script, level at +0xA),
  16-byte checks of three conditions and a table address, then the tables
  back to back (a count and a byte, then the actions); the death script and
  event sit just before the next record. `AiRecord` reads either layout.
- **datEncountPack:** the packs keep their size, but the tables are read
  188 bytes apart with 24 entries each (`kEncounterTableSize`,
  `kEncounterEntries`), so a table's last entry overlaps the next's start.

Some patches depend on what a register happened to hold, which the port
reproduces: Hardtype's inheritance level lookup no longer clears its row
counter, so it counts from what the caller left (the RNG's carry bit, the
unit's level less its devil's, the previous lookup's position).

Hardtype nbAiAiChk also clears the wrong byte: it writes a zero at
(check + 1) + 0x190 instead of clearing the unit's selection, and its
press-gauge conditions (types 60 and 61) leave the selection mask at
(gauge byte << 4) + 0x190. Its nbRunAiSub reads the drawn action's targets
with the index from the wrong register, left by nbAiChkClose: 0 when the
skill is usable, so an AI unit takes the targets of its table's first
action whatever it chose. The port does the same.

Three more of its patches read leftover registers:

- **The command menu** (SetCommList) gives every unit the demons to
  summon, and the items to the unit whose devil ID is 0, meant as the
  Demi-fiend. But the ID is read 4 past a register left by the skill list:
  the unit only when a skill's cost was the last thing looked up, otherwise
  the party flag's bit 2, the battle's record, 16, or the RNG's state word.
- **The buff limits** (nbGetHojoCounterMax / Min) for the stat counters
  depend on the low half of the caller's s1 + s4: at or past 0xDB00 they are
  4 and -2, below 2 and -4. nbSetHojoAddCounter leaves the counters'
  address plus the new value, CheckHojo the party's address plus the number
  of parties, the AI's checks 128 x the slot plus 1. (Presumably meant to
  tell the two sides apart by where their counters sit.)
- **nbCheckBattleSkillError3** refuses fourteen more skills when nothing
  they change can move; a fifteenth (0xE4) is compared with a register that
  holds a float constant's upper half, so it never matches.

Encounters also change: the moon table applies only when the table chosen
without it has a weighted first entry; in Kagutsuchi's phase 8 the
encounter threshold is at least 420 (210 for a low base); and Estoma lets
through only groups whose average level is above half the Demi-fiend's
(plus 1, at most 100), or twice it once he holds 25 Magatama. Devils
0xE0..0xE5 borrow the models of Momunofu, Metatron, Beelzebub (Fly),
Lucifer, Ose and Shikigami.

## Battle

- **Stand-in skills.** 28 skills play as another (0x2FE3E0: the skill and
  its stand-in): READY swaps the chosen skill for its stand-in and notes the
  pair (0x2FE91C). The acting skill decides the costs, the checks, the hit
  order and the effect's results; the stand-in the motion, the effect data
  and the targeting. Four skills also take another motion type unless the
  unit is one of the two devils listed with them; one pair starts its
  effect as another. Nothing clears the pair but a press result
  (nbMakeNewPressPacket), where acting skill 0x10E counts as result type 3
  and 0x86 takes 8 press icons of each kind; actions that note nothing keep
  the last pair.
- **Damage.** Magic power is (base + 2 Lv power) / 210, with the stat
  correction taken at level 50 at most; skills based on max HP use, on the
  party's side, 6 (Lv + St) times how full the HP was before the hit; enemy
  heals scale with their level; skill -1's power doubles; and power% of
  HP can't kill and is scaled by the last affinity word (a register).
- **Accuracy and criticals.** Physical accuracy and the critical chance are
  ratios of the two units' Agility (and Luck), magic accuracy one of the
  caster's magic accuracy and the target's evasion; buffs above 1 count a
  fifth. Bright and Dark Might note themselves instead of critting.
- **Affinities.** New passives: 0x16B (Fire to Force), 0x16D and 0x16F
  (Curse to Mind), 0x171 (a quarter, Expel to Mind), and boosts 0x173,
  0x174, 0x177 at x1.3046875 (boosts were x1.5). A rate under 100% also
  scales the affinity word's flags into it. Pierce and Son's Oath work for
  the elements up to Almighty, magic ones through Null only.
- **Ailments.** The chance is weighed by both units' Luck and shifted by
  the last affinity word's flags; physical hits end Shock and Freeze.
- **Initiative:** the first strike weighs Level + 3 Luck + 4 Agility on
  both sides from 70 x the area's coefficient, without the level-gap
  exemption; enemies' own talks can be switched off by the option byte.
- **Escape** weighs attempts and stats 15 instead of 20 and is possible on
  Hard; scattered Macca is 1/50 of the party's; summons by the Demi-fiend's
  demons use motion type 0; a summon keeps Focus; Drain Attack fires after
  another passive.

The AI gains three condition types: 29 (Kagutsuchi's phase is n), 60 and 61
(the press gauge is at least / at most n).

Hardtype reads the global work at its fixed address 0x1248500 (as the game
allocates it): the moon phase (+0xA41), its move bits (+0xA44), the
Demi-fiend's unit (0x1248F54) and the Magatama owned (0x124A213). An option
byte at 0x2FF388, which no code writes (presumably set by the patch's
cheats), turns some changes on.

## Outside battle

- **Experience:** demons in stock earn three quarters of the battle's
  experience, or all of it with the skill 0x162 (US Maniax: none without
  it, and the skill's divisor with it).
- **Shops:** Hard doubles the buy price instead of tripling it.

## On a console

Hardtype freezes on a PS2 where PCSX2 plays it: the EE raises an address
error for a misaligned halfword, word or doubleword access, which PCSX2
lets through. `EE_ALIGN=1` makes the differential test's interpreter report
each such instruction it runs. Hardtype's own:

- **0x2FDD3C** (nbAiAiChk's new prologue): `sw zero,0x190(s0)` runs in the
  jump's delay slot before `s0` holds the AI work, so it stores to nbRunAi's
  check counter + 0x190: 0x191 on the first check, a misaligned store into
  the kernel's low memory, before every AI unit's first action.
- **The AI records:** 189 of the 385 records in the repacked datDevilAI
  start 2 past a word, and nbAiAiChk (0x2867E4..EC), nbRunAiSub (0x287C10)
  and nbRunAi (0x287D38) read their checks and actions with word loads.
- **fclKeisyoSkillLevel's 3-byte rows** (cmbGetKeisyoSkillLevel 0x222BC0,
  cmbGetMutationSkill 0x223580): halfword loads at odd addresses.
- **SetCommList** (Beckon Call with a demon to summon): the halfword 4 past
  the RNG's state word, in effect a random address.

US Maniax runs none of these.

`python tools/hardtype_console_fix.py <SLUS_209.11> <output>` patches
Hardtype 1.5.1's executable for the AI ones, in code only, so it plays as
it does on PCSX2: the stray store becomes a nop, the record word loads
become LWR/LWL pairs (in unused space in Hardtype's code area) and
nbRunAiSub reads its two halfwords as halfwords. The differential suite
passes on the patched executable with no AI access misaligned. Realigning
the records instead would change eight bosses: Kin-Ki, Sui-Ki, Fuu-Ki,
Aciel, Futomimi, Koumoku, Zouchou and Thor 2 have checks but no action
tables, and their scripts call AI(), which takes the bytes after the
record (the death script as the count, then the next devil's record) as
the table. The fusion and Beckon Call reads stay as they are.

## Status

Ported and proven against Hardtype's own instructions (`variant_tests.cpp`,
`ai_tests.cpp`): datGetBaseParam, datGetMagicHitPow, datGetSakePow,
datGetBaseMaxMp, datAddHp, datGetSkillCost, datGetItemSkillNo,
cmbChkEventDevil, cmbCalcIkenieExp, cmbGetKeisyoSkillLevel,
cmbCalcKeisyoSkillRate, cmbGetMutationSkill, nbGetTargetTypeRuleArea, and
the AI's checks and actions (nbAiAiChk, its conditions, the action choice and
cost checks), the death checks, SetCommList, nbCheckBattleSkillError3, the
buff limits, the encounter functions, the unit models, the action process
(NON, READY, SKILL, SetAllPacket, the press results, escape, Macca), the
battle reward (nbResultAddExp), the shop price (shpCalcItemPrice), and nbCalc's
damage, accuracy, critical, affinity and ailment functions (their
"(instructions)" tests in `main.cpp`).

The full differential suite passes on Hardtype against its own
instructions, with the tests against US Maniax's legacy C skipped (a
function a version changes gets an "(instructions)" test that runs on
both). `kHardtypePending` in `source/tests/differential/main.cpp` lists
tests of patches not yet followed (none now).

Every Hardtype change to a function the rewrite has is ported. The
patched functions the base hasn't rewritten yet (a command choice and some
field and fusion functions) follow their base rewrites. The AI's effect estimates (AI levels 1 to 3, which
Hardtype's own data never uses) run through the ported functions and pass
too.

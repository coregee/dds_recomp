# source/ — the readable reconstruction

C++20 code that reads like the game's source while behaving exactly like the
original. Each function is rewritten from the validated legacy C (or from the
original instructions) and proven equivalent by a differential test. The game
data tables are source too, generated from the executable and checked
byte-for-byte against it.

## Layout

One tree builds every version of the game
([docs/versions.md](../docs/versions.md)). Where versions differ, the unit
holds each version's alternative side by side, chosen by the build's traits
(`nocturne/build.hpp`: `NOCTURNE_US`, `NOCTURNE_VANILLA`, `NOCTURNE_CHRONICLE`,
`NOCTURNE_HARDTYPE`):

```
shared/      the source: include/ and src/ below
generated/   what is generated from each version's executable:
  <build>/src/data/*_table.cpp                 its data tables (US Maniax's when it has none)
  <build>/include/nocturne/version_addresses.hpp  its addresses (JP builds)
scripts/     FlowScript, below
tests/       the tests, built once per version
```

Within `shared/`:

```
include/nocturne/
  guest.hpp              PS2 memory: Ptr32<T> for in-structure pointers, table lookup
  ee/float.hpp           ee::Float (PS2 FPU arithmetic), ee::literal (toolchain rounding)
  ee/double.hpp          ee::Double (the game's software double precision)
  data/types.hpp         vocabulary: Param, Attribute, Ailment, Affinity, flags
  data/ids.hpp           devil::, skill::, item:: IDs and Race (generated)
  data/records.hpp       game records: UnitWork, NormalSkill, SkillInfo, DevilFormat, Encount ...
  data/tables.hpp        the data tables: contents (src/data) and accessors
  data/unit.hpp          datCalc: stats, derived powers, max HP/MP, affinity, ailments
  data/progression.hpp   datCalc: the party and stock, items, Reason points, recovery skills
  data/magatama.hpp      Magatama: bonuses, skills, mastery, the Demi-fiend's race
  facility/compendium.hpp the demon compendium (fclEncyc)
  battle/process.hpp     battle state: MainProcessData, Party, Formation
  battle/combatant.hpp   per-combatant queries: ailment, side, passives, Endure
  battle/buffs.hpp       -kaja/-nda counters and multipliers
  battle/affinity.hpp    affinity resolution and the damage ratio
  battle/damage.hpp      physical/magic power, HP/MP effects, ailment rolls
  battle/calc.hpp        hit/crit rolls, initiative, escape, rewards
  battle/targeting.hpp   which combatants an action can target
  battle/ai.hpp          enemy AI: conditions, actions, target choice
  battle/ai_script.hpp   AI script commands (nbCommand_AI_*)
  fusion/stock.hpp       the devil stock: creating, copying, finding units
  fusion/growth.hpp      skills, EXP, level-up stats, evolution, skill power-ups
  fusion/inheritance.hpp skill inheritance rates and the inherited-skill list
  fusion/rules.hpp       which devil a fusion makes (races, Elements, Mitama, sacrifices, Fiends)
  fusion/combine.hpp     building the fused devil; cmbGetBirthDevil
  fusion/accident.hpp    fusion accidents
  fusion/sort.hpp        inherited-skill and devil-list sorting
  libc/qsort.hpp         the PS2 C library qsort (its tie order is observable)
  interface/message.hpp  message windows (itfMesManager)
  interface/panel.hpp    window backgrounds (itfPanel)
  interface/font.hpp     the font engine (frFont)
  script/vm.hpp          the FlowScript VM: processes, opcodes, argument access
  script/commands.hpp    the commands every script uses (scrCommonCommand, scrParameterCommand)
  data/field_skill.hpp   skills used outside battle, field damage to the party
  battle/kouka.hpp       the battle's presentation queue (kouka packets)
  battle/kouka_process.hpp  the kouka process: plays the queue every frame
  battle/talk.hpp        talks with demons: the record and its helpers
  battle/action.hpp      an action's state machine and time list
  battle/bad_ai.hpp      what an ailing (charmed, panicked, cursed) unit does
  battle/camera.hpp      the battle camera: its named states
  event/state.hpp        the event flags and Kagutsuchi's phase (evt)
  kernel/draw.hpp        the kernel's screen state: quake, blur, effect fades, lights, fog
  kernel/main_loop.hpp   the kernel's main loop: stop and slow motion
  effect/event.hpp       the event screen effects' switches and settings (effEvent)
  effect/boss.hpp        boss effects (effPCPBoss): Ongyo-Ki's effects' lengths
  effect/cut.hpp         a skill effect's cuts (effBTL): their frames, draw end, camera, the skill state
  external.hpp           engine functions not rewritten yet (bridged to legacy C)
src/
  data/unit.cpp, progression.cpp   datCalc
  data/magatama.cpp                 Magatama (cmb/cmp/rst/dat functions)
  facility/*.cpp                    fcl: facilities (compendium)
  battle/*.cpp                      nbCalc, by topic
  fusion/*.cpp                      cmb / fclCombineCalcCore, by topic
  interface/message.cpp             itfMesManager: message windows, selections
  interface/font*.cpp               frFont: text layout, glyph cache, message pages
                                    (font_layout_jp/_us, font_message_jp/_us: each engine whole)
  hardtype.cpp                      the functions Hardtype adds (docs/hardtype.md)
  script/vm.cpp                     ScrScriptProcess, ScrTraceCode
  script/commands.cpp               scrCommonCommand
  script/parameter_commands.cpp     scrParameterCommand: the prm_* commands
  data/field_skill.cpp              datCalc: skills from the menu, the field's damage to the party
  battle/kouka.cpp                  nbKoukaProcess, nbMakePacket: queueing an action's presentation
  battle/kouka_process.cpp          nbKoukaProcess: the process and its packet players
  battle/talk.cpp                   nbNegoProcess: the talks' process and helpers (docs/talks.md)
  battle/talk_flow.cpp              the talks' steps: each group's flow
  battle/talk_opening.cpp           NbNegoFlowOne: a talk's opening (group 1)
  battle/talk_fullmoon.cpp          NbNegoFlowFullMoon: talks under a full Kagutsuchi (group 2)
  battle/talk_kin.cpp               NbNegoFlowDouchara: the demon meets its own kind (group 4)
  battle/talk_fated.cpp             NbNegoFlowInnen: a fated pair meets (group 5)
  battle/talk_bargain.cpp           NbNegoFlowTwo: the bargaining (group 6)
  battle/talk_question.cpp          NbNegoFlowQuestion: the demon's questions (group 7)
  battle/talk_fight.cpp             NbNegoFlowFight: a refusal, and the debug menu's fights (group 8)
  battle/talk_deal.cpp              NbNegoFlowOk: the deal struck (group 9)
  battle/talk_nodeal.cpp            NbNegoFlowNg: no deal, partings and the Death Pact (group 10)
  battle/talk_drain.cpp             NbNegoFlowDrain: the demon drains the talker (group 11)
  battle/talk_speaksup.cpp          NbNegoFlowMukan: the last enemy speaks up (group 12)
  battle/talk_ambush.cpp            NbNegoFlowSensei: a demon that ambushed the party (group 13)
  battle/talk_mercy.cpp             NbNegoFlowInoti: the last enemy begs for its life (group 15)
  battle/talk_minor.cpp             the short groups 3, 14 (asking to join) and 16 (a taunt)
  battle/action.cpp                 nbActionProcess: states, the time list, result helpers
  battle/action_events.cpp          nbActionProcess: counters, talks, death scripts
  battle/bad_ai.cpp                 nbBadAi: ailments that take the turn
  battle/battle_panel.cpp           nbPanelProcess: the party panel shown or hidden
  battle/formation.cpp              nbFormation: formations shown, hidden, put back in place
  battle/event_process.cpp          nbEventProcess: the battle's events (deaths', scripts')
  battle/macca_window.cpp           nbMakaProcess: the Macca window (its process, fade and drawing)
  battle/sound.cpp                  nbSound: the units' sound banks and the battle music
  battle/encount.cpp                nbEncount: random encounters in the field, the music type
  battle/enc_process.cpp            nbEncProcess: the encounter's opening (models loaded, units appearing)
  battle/camera.cpp                 nbCameraProcess: camera states
  battle/target_select.cpp          nbTarSelProcess: choosing a target
  battle/skill_error.cpp            nbSkillError: skills that would do nothing
  battle/help.cpp                   nbHelpProcess: the help line's text
  battle/comm_select.cpp            nbCommSelProcess: the command menu's lists and cursor
  event/state.cpp                   evt: the event flags and Kagutsuchi's phase (callers still reach the
                                    harness's fakes through external.hpp)
  kernel/draw.cpp                   dds3KernelDraw: screen state set by the scripts
  kernel/main_loop.cpp              dds3KernelMain: stop, slow motion
  effect/event.cpp                  effEvent
  effect/boss.cpp                   effPCPBoss: effect lengths
  effect/cut.cpp                    effBTL: cut frames and state
  libc/*.cpp                        C library functions whose exact behaviour matters
  platform/legacy_bridge.cpp        external.hpp -> legacy C ABI
scripts/                 FlowScript: .flow (readable) and .flowasm (exact) per script,
                         .msg its message table (docs/messages.md);
                         exe/ai.flow is the enemy AI (see docs/flowscript.md)
tests/
  differential/          every rewritten function vs. its legacy C or the original
                         instructions (ee.hpp, an EE interpreter), on the real game data
  tables/                generated tables vs. the executable's bytes; Ghidra header vs. records
```

Modules follow the original translation units (the HD remaster keeps them
as classes: `nbCalc`, `datCalc` …) and split large ones by topic. Original
prefixes: `dat` data, `nb` battle, `evt` events, `fcl` facilities, `cmp`/`cmb`
menus, `sdf` system. See `../docs/glossary.md`.

## Conventions

- **PS2 layout.** Structures keep their exact PS2 size and offsets
  (`static_assert`ed), so they work with the legacy code, save data and the
  executable's tables. Pointers inside game structures are `Ptr32<T>`.
- **Names.** Everything gets a plain English name: functions, types, enum
  constants and fields (no romanized Japanese like `nbGetJyokyoMes`; that
  one is `statusMessage`). The original name stays findable for the HD
  remaster and Ghidra. A function's original name and address go in a
  comment directly above the definition, which `tools/function_map.py` reads:
  ```cpp
  // nbCheckEscape @ 0x00269E98
  bool rollEscape(MainProcessData& data)
  ```
  A field whose original name (from `reference/hd/il2cpp/dump.cs`) differs
  notes it in its comment, `int32_t macca;   // Macca on hand (HD: maka)`,
  and a type in its leading comment. Names that are already English, like
  `badstat` or `hitlevel`, keep the original spelling.
  Unnamed originals use `// 0x00259658 (unnamed): ...`.
- **IDs by name.** Use `skill::Pierce`, `devil::Pixie`, `item::Bead`
  (generated into `data/ids.hpp`), never bare numbers.
- **Uncertainty is visible.** Unknown fields are `unknown_<offset>`; inferred
  names say *tentative*. Promote a guess only with evidence (symbol, string,
  data table, caller).
- **Floats.** Use `ee::Float` for anything the original did on the FPU and
  `ee::literal(x)` for its non-exact constants (the original toolchain rounded
  toward zero: `0.6` is `0x3f199999`). Double precision goes through
  `ee::Double`.
- **Same observable behaviour,** including RNG draw order and count. Keep
  original quirks (dead computations, redundant checks) and explain them in a
  comment instead of fixing them.

## Data tables

`generated/us/src/data/*_table.cpp` and
`shared/include/nocturne/data/ids.hpp` are generated by `tools/gen_tables.py`
from `game/SLUS_209.11` (a version's differing tables into
`generated/<version>/` with `--variant`), with names from
`reference/names/`. Regenerate after changing the generator or names; never
edit them by hand.

## Testing

```
tests\tables\build.cmd
tests\differential\build.cmd [cases-per-function] [seed] [name filter]
```

The tables test compiles the generated tables and compares them with the
executable byte for byte; it also checks that the Ghidra type header
(`tools/ghidra/nocturne_types.h`) matches the records.

The differential test loads `game/SLUS_209.11` into fake PS2 RAM (so all
static tables are real game data), generates random game states, runs each
legacy function and its rewrite on identical copies, and compares return
values, traps, RNG draws, debug prints and every byte of dynamic RAM. Callees
are real code on both sides; only the engine boundary (unit lookup, RNG,
event flags, printf) is faked, in `fake_world.c`.

Status: every rewritten function (nbCalc, datCalc, cmb/fusion, qsort) matches
its legacy C over thousands of random states each, and mutation checks show
the tests notice small deliberate changes; 30 tables match the executable
exactly. Some original addresses legitimately differ from the legacy file
they were compared with (e.g. libc qsort is checked through the fusion sorts).

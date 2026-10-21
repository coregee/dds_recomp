# Shin Megami Tensei III: Nocturne — source reconstruction

The goal is a readable source-code equivalent of the US PS2 executable
(`SLUS_209.11`) and of the game's code-like resources on disc (data tables,
event and battle scripts): sensible modules and types, intuitive functions,
and documentation of how the game works.

## Where things are

| Folder | What it is |
|---|---|
| [source/](source/README.md) | **The reconstruction.** C++20, original PS2 data layouts, readable code. Every function is proven equivalent to the legacy C. |
| [legacy/](legacy/README.md) | The earlier instruction-faithful C recovery (~3,000 functions). Correct but hard to read; the raw material for `source/`. Frozen. |
| [docs/](docs/) | How the game works and what the names mean: [glossary](docs/glossary.md), [battle mechanics](docs/battle-mechanics.md), [Ghidra notes](docs/ghidra.md), [disc and resources](docs/disc-resources.md). |
| [reference/](reference/README.md) | Evidence: the function map, Ghidra annotation export, HD-remaster symbol dump, per-function disassembly, archived research notes. |
| [tools/](tools/README.md) | Disc/archive extraction, Ghidra export scripts, emulator helpers. |
| `third_party/` | Vendored PS2 FPU model (`ps2float`, LGPL) used to reproduce EE float behaviour on a PC. |
| `ghidra/` | The Ghidra project (`Nocturne.gpr`, program `candidate`). Local only. |
| `game/` | The extracted disc. Local only. |

## Progress

[reference/function-map.tsv](reference/function-map.tsv) lists all 9,067
functions Ghidra recognises, with their state:

| State | Functions | Meaning |
|---|---:|---|
| rewritten | 349 | readable implementation in `source/`, differential-tested |
| legacy | 2,702 | instruction-faithful C in `legacy/src/` only |
| named | 268 | identified and named in Ghidra, no C yet |
| unknown | 5,748 | not yet identified |

Refresh it with `tools/ghidra/export-annotations.ps1` after Ghidra work.

Rewritten so far: the battle calculations (`nbCalc`: hit, crit, ailments,
initiative, escape, rewards, damage, affinity, buffs, skill costs), unit stats
and party progression (`datCalc`: stats, the stock, Magatama, Reason points,
recovery skills), demon growth (EXP curve, level-up stats, skills, evolution)
and the whole of fusion (`fclCombineCalcCore`: rules, skill inheritance,
sacrifices, accidents, Fiends), Magatama (bonuses, skills, mastery, the
Demi-fiend's race), the compendium (`fclEncyc`) and the enemy AI (`nbAi`:
conditions, action tables, target choice, AI script commands, targeting),
plus the C library `qsort` the game sorts with.
Scripts as source: every FlowScript — the enemy AI scripts embedded in the
executable and the 191 event / field / facility scripts on disc — decompiled
into `source/scripts/` and verified to recompile to the original code
([docs/flowscript.md](docs/flowscript.md)), with every message table as
text that encodes back to the original bytes ([docs/messages.md](docs/messages.md)).
Game data as source: devils, skills, items, level-up/growth tables, Magatama,
encounters, affinities, enemy AI, inheritance and every fusion table (`source/src/data/`);
see [docs/fusion.md](docs/fusion.md) for how fusion works and
[docs/magatama-and-compendium.md](docs/magatama-and-compendium.md) and
[docs/enemy-ai.md](docs/enemy-ai.md).

## Setting up

1. Put the US ISO in this folder (`Shin Megami Tensei - Nocturne.iso`) and run
   `python tools/disc_extract.py`. It extracts to `game/` and checks every file
   against `tools/disc-sha256.json`.
2. Extract archive files as needed:
   `python tools/dds3_archive.py all --filter .bf` (see
   [disc and resources](docs/disc-resources.md)).
3. Build and run the tests: `source\tests\tables\build.cmd` and
   `source\tests\differential\build.cmd` (Visual Studio 2022 Build Tools).
4. Optional: open `ghidra/Nocturne.gpr` in Ghidra 11 with the
   `ghidra-emotionengine-reloaded` extension. Read [docs/ghidra.md](docs/ghidra.md) first.

## How work proceeds

See [AGENTS.md](AGENTS.md). In short: pick a module, find its original names,
rewrite it into `source/` with typed records, and prove it with the
differential test against `legacy/` (or, for code with no legacy C, against
the original instructions).

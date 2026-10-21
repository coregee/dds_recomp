# Working on the Nocturne reconstruction

Goal: a readable, well-typed source equivalent of `SLUS_209.11` and of the
game's code-like disc resources. Readability is the point; correctness is
proven, not assumed.

## Layout rules

- New code goes in `source/` (C++20). Follow `source/README.md`: PS2 record
  layouts with `static_assert`ed offsets, original field names, English
  function names with the original name and address in a `// name @ 0xADDR`
  comment directly above the definition (tools/function_map.py reads it).
- `legacy/` is frozen reference material. Read it, compile units of it into
  tests, never edit it. When a whole legacy unit is rewritten, leave it in
  place; the function map tracks which implementation is current.
- Don't commit game data, disc files, Ghidra databases or emulator captures.
  Generated output goes in `build/` (ignored).
- Keep the repository small. Validation runs generate data on the fly; do
  not store large capture files, checkpoints, numbered snapshots or
  per-milestone reports. One current export of each thing, overwritten.

## Rewriting a module

1. **Choose.** Prefer legacy units whose callees are already rewritten or are
   simple, and subsystems that share records with finished work. Check
   `reference/function-map.tsv` for status.
2. **Find names.** In order of authority: the HD remaster
   (`reference/hd/il2cpp/dump.cs` for struct fields and function lists,
   `reference/hd/metadata/game-methods.tsv` for signatures,
   `reference/hd/ghidra/corpus/<va>.c` for HD decompiles), Ghidra's current
   names, `reference/ps2/identification/` (including the unverified
   `hd-name-leads-unverified.tsv`), then community sources listed in
   `reference/research/community-research.md`. HD offsets differ from PS2
   (16-byte object header, 8-byte pointers); field *order* carries over.
3. **Confirm meanings** against the executable and game data, not just
   names: read the table in `game/SLUS_209.11` (RAM = file offset + 0xFF000
   for the data segment), look at callers in
   `reference/ps2/whole-program/functions/<addr>.asm`, check debug strings
   (EUC-JP). Record evidence in `docs/glossary.md`.
4. **Rewrite** into `source/`. Unrewritten callees go into
   `source/include/nocturne/external.hpp` and are bridged in
   `source/src/platform/legacy_bridge.cpp`.
5. **Prove it.** Add every function to the differential test
   (`source/tests/differential/`: `main.cpp` for battle/unit code,
   `fusion_tests.cpp`, `fusion_core_tests.cpp`, `progression_tests.cpp`,
   `magatama_tests.cpp`;
   shared helpers in `harness.hpp`, engine fakes in `fake_world.c`) and run
   `source\tests\differential\build.cmd`. Results, traps, RNG draw
   order, debug prints and all written RAM must match the legacy C. Make sure
   the generator reaches the interesting branches; a quick mutation (change a
   constant, confirm a failure) shows the test can see the change.
6. **Teach Ghidra.** Add each rewritten function's typed prototype (original
   name, HD parameter names) to `tools/ghidra/nocturne_signatures.tsv`, and new
   record types to `tools/ghidra/nocturne_types.h` (the tables test checks it
   against the C++ records). Run `tools/ghidra/import-types.ps1`, then
   `tools/ghidra/export-annotations.ps1` to refresh the function map.
7. **Record** mechanics in `docs/`, corrections to legacy names in
   `docs/battle-mechanics.md` (or a new topic file).

## Data tables

Tables in the executable become source through `tools/gen_tables.py`: add the
record to `records.hpp`, its field spec and output to the generator, the
table to `source/tests/tables/main.cpp`, and regenerate. The test must show
the compiled table equal to the executable's bytes. Names for IDs go in
`reference/names/*.tsv`.

## Code with no legacy C

About two thirds of the executable has no C yet. For those functions the
reference is the original code itself: decompile in Ghidra, write the
readable version, and validate by running the original instructions (PCSX2
via the MCP tools, see `reference/research/runtime-workflow.md`) or an EE
emulator harness against the same inputs. Build such harnesses to generate
inputs on the fly instead of storing captures.

## Ghidra

- One project: `ghidra/Nocturne.gpr`, program `candidate`. Save in place.
- Read `docs/ghidra.md`: the installed EE processor decodes `DIVU` as signed,
  so the decompiler is wrong for unsigned division unless you use the patched
  language for exports.
- After naming work, run `tools/ghidra/export-annotations.ps1` (close the GUI
  first). Its text export is the backup of the Ghidra work and is committed.
- Names: use the original name when the HD remaster or a string proves it.
  Otherwise use a descriptive English name with no address suffix and say in
  the function comment how sure it is.

## Evidence

Distinguish what is proven (instructions, data, differential tests) from what
is inferred. Mark tentative names as such in code and docs. Community findings
are leads until checked against the PS2 bytes; cite them with a link and
revision.

## Emulator

PCSX2 (MCP build) can be driven for live checks; `tools/pcsx2_controls.mjs`
maps controller input and `tools/configure_pcsx2_runtime.py` sets up the
emulator. Only one session should own PCSX2 or the Ghidra project at a time.

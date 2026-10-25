# Versions of the game

The rewrite builds five versions from one source tree:

| Build | Version | Executable | Addresses |
|---|---|---|---|
| `vanilla` | JP Nocturne, the first release (2003; no Amala, Fiends or difficulty) | SLPM_652.42 | its own |
| `maniax` | JP Nocturne Maniax (2004; Dante, the Labyrinth of Amala) | SLPM_654.62 | its own |
| `chronicle` | JP Nocturne Maniax Chronicle Edition (2008; Raidou in place of Dante) | SLPM_666.81 | its own |
| `maniax-us` | US Shin Megami Tensei III: Nocturne (Maniax, 2004) | SLUS_209.11 | the reference |
| `hardtype` | the fan rebalance Hardtype 1.5.1, a patch of the US release | SLUS_209.11 | the US release's |

## The source tree

Every build compiles the same source, `source/shared/`. Where versions
differ, the unit holds each version's alternative side by side, so a
reader sees at one place what each version does:

```cpp
#if NOCTURNE_HARDTYPE
// nbCheckEscape @ 0x00269E98: attempts and the stat ratio weigh 15 ...
int32_t escapeWeight() { return 15; }
#else
// nbCheckEscape @ 0x00269E98: attempts and the stat ratio weigh 20 ...
int32_t escapeWeight() { return 20; }
#endif
```

- **Traits, not build names.** Code tests what sets a build apart
  (`nocturne/build.hpp`), never which build it is:
  - `NOCTURNE_JAPANESE` / `kBuild.japanese`: the JP releases (vanilla,
    Maniax, Chronicle): Japanese text and font engine, their global work
    and window layout, their own addresses.
  - `NOCTURNE_CHRONICLE` / `kBuild.chronicle`: the Chronicle Edition's own
    changes.
  - `NOCTURNE_HARDTYPE` / `kBuild.hardtype`: the Hardtype patch.

  A small step that differs is `if constexpr` or a constant
  (`kBuild.japanese ? 0x19 : 0x14`); whole alternatives, and anything that
  names an address or type only some builds have, are `#if`. A unit's
  alternatives sit in its "By version" section, the most specific first.
- **Whole engines** that share nothing but their interface sit in sibling
  files, each compiled only by its builds: `interface/font_layout_jp.cpp`
  and `font_layout_us.cpp`, `font_message_jp.cpp` and
  `font_message_us.cpp`.
- **Record layouts** that differ are chosen in the record's header
  (`records.hpp` `GlobalWork`, `interface/font.hpp`,
  `data/version_tables.hpp`, `data/devil_ai.hpp`).
- **Addresses.** The source writes US Maniax's addresses through
  `nocturne/address.hpp`: `addr(0x...)` for what every version has,
  `optionalAddr(0x...)` for what a version may lack (debug print formats;
  0 there, and the print is skipped). What only the JP builds have is
  written by JP Maniax's address, `jpAddr(0x...)`. All are evaluated at
  compile time: the US release and Hardtype keep the US address, a JP build
  looks it up in its generated
  `source/generated/<build>/include/nocturne/version_addresses.hpp`
  (`python tools/version_addresses.py <build>`), and an address with no
  counterpart is a compile error where it's used.
- **Tables** are generated per version into `source/generated/<build>/src/data/`:
  `python tools/gen_tables.py` writes the US release's, and
  `python tools/gen_tables.py --variant hardtype` Hardtype's that differ. A
  build without its own takes the US release's (`tools/sources.py`).
- **A version not ported yet** has no alternative of its own: a function
  only some builds have written says `// (not ported for this version
  yet)`, and that build fails to link until it is.

## Getting the discs

The ISOs sit in `nocturne/` under the names in `tools/disc_extract.py`:

```
python tools/disc_extract.py --variant hardtype
```

This extracts a version to `game/<folder>/` (the US release to `game/`,
JP Maniax to `game/jpmaniax/`) and checks it against
`tools/disc-sha256-<build>.json`. Disc files are never committed.

## Building and testing a version

Set `NOCTURNE_VARIANT` before running the build scripts (empty: `maniax-us`).
Each version builds into its own `build/*-<build>/` folder and runs against
its own executable:

```
set NOCTURNE_VARIANT=hardtype
source\tests\tables\build.cmd
source\tests\differential\build.cmd 300 31
```

To record which functions each build proves, set
`DIFF_RESULTS=reference/verification/<build>.tsv` for the run, then
`python tools/function_map.py`: the map gets a column per build (ok,
differ, pending, or legacy for a test only of US Maniax's legacy C).

The tables test proves a version's tables byte for byte. The differential
test runs each rewritten function against that version's own instructions;
the tests against the legacy C (the US release only) are skipped for the
other versions, and their count printed. `variant_tests.cpp` and the
"(instructions)" tests cover what the versions change.

## Status

- **hardtype:** every change to a function the rewrite has is ported and
  proven against Hardtype's own instructions; see
  [hardtype.md](hardtype.md).
- **chronicle:** builds and runs its differential suite against its own
  instructions (below); the font and message engine and a few changed
  functions are still to port.
- **maniax (JP):** extracted and mapped (its function and data maps, its
  address table); its font and message engine is Chronicle's. Not built yet: it still needs its own side of the
  hooks only the US release has been checked for (affinity, field skills)
  and its harness data.
- **vanilla:** extracted and surveyed (below); no build yet.

## Chronicle and Vanilla: what the survey shows

Both are separate builds of the same source tree, so their code is mostly
US Maniax's at other addresses. `tools/match_functions.py <name>` finds each
US Maniax function in the other executable by its instructions, with the
placement-dependent bits masked, and writes
`reference/versions/<name>-function-map.tsv`; `tools/match_data.py <name>`
maps data addresses from the matched code pairs
(`reference/versions/<name>-data-map.tsv`), and `tools/version_diff.py
<name> [function]` lines up a function that didn't match with its
counterpart (with a small disassembler, `tools/mips.py`).

| | Chronicle (SLPM_666.81) | Vanilla (SLPM_652.42) |
|---|---|---|
| functions matched | 8,819 of 9,068 | 8,079 of 9,068 |
| ... and paired by place (differing) | 182 | 307 |
| rewritten ones that differ | 99 | 177 |
| gp | 0x552770 (US 0x554170) | 0x533DF0 |
| data tables | -0x370 (skills, devils, encounters), +0x2B0 (fusion, growth) | shifted by -0x69D0 .. -0xB420; several resized |

Chronicle's differences, as far as seen:

- **Record layouts.** The global work is 4 bytes shorter before its event
  bits (at 0x83C, not 0x840), so every later field sits 4 lower (macca at
  0xA44, units at 0xA50, the Magatama at 0x1CF6 ...). The script process and
  a font record shift too. A build needs these layouts by version.
- **Debug prints.** Most of the battle's debug strings ("HP damage = %d",
  "MISS!!!" ...) are gone: the prints were removed, so `diag::print`
  calls need to know which messages a version has.
- **Japanese text.** The font engine, message windows and the talks' and
  help line's data are the Japanese versions; the rewrite's font and
  message modules (English) will need their own versions.
- **Compiler noise.** Most other differing functions differ only by
  register allocation, plus the shifted record offsets.

`tools/version_addresses.py <name>` maps the addresses the source uses
(`addr()`, `optionalAddr()`): code through the function map (a function's
start, or a place inside one matched instruction for instruction), data
exactly where the code was seen forming it, else by the delta its
neighbours agree on, else by its bytes. The matcher also pairs functions
that differ by their place between matched neighbours (match `gap`), and
the data matcher lines up those functions' addresses in order when both
form as many.

## The Chronicle build

```
python tools/match_functions.py chronicle
python tools/match_data.py chronicle
python tools/version_addresses.py chronicle
set NOCTURNE_VARIANT=chronicle
source\tests\differential\build.cmd
```

What the port has so far (most of it under `NOCTURNE_JAPANESE`, which JP
Maniax shares instruction for instruction):

- **Layouts.** The JP builds' global work sits 4 lower from the script
  variables on and 0x2450 lower from the options on.
- **The font and message engine.** The JP builds' own (`font_layout_jp.cpp`,
  `font_message_jp.cpp`):
  a 0x20-byte style record and a shorter settings record; no size override
  for styles 0 and 1, no code lists, last code or name tables; a mode bit
  that halves ASCII; a per-glyph shadow offset; full-width digits and floor
  names; entered names 8 letters long, family name first; no particle codes;
  taller message windows (their default positions, option lines and speaker
  panel); a default line step of 25.
- **Hooks.** Son's Oath pierces resistance like Pierce, and the party
  damage that leaves 1 HP spares no one (Chronicle's; JP Maniax's own
  differ again and are still to port).
- **Constants.** RunSeKouka stops music 0x1C04xxxx for the event boss's
  repelled skill 0x107 (Maniax 0x1C07xxxx: Dante's fight).

The harness runs the same tests at Chronicle's addresses
(`source/tests/differential/version_map.cpp`): hooks, interpreted ranges,
entry points and the tests' static addresses are US Maniax's, mapped
through `reference/versions/chronicle-*.tsv` when it starts; gp comes from
the executable, and the fonts and message files from `game/chronicle/dds3/`
(`tools/dds3_archive.py --ddt game/chronicle/DDS3.DDT ...`). Hooks that call
US Maniax's legacy C run Chronicle's own instructions instead (`hookUs`).
A test that reaches a function Chronicle has no counterpart for counts as
pending, as do the script tests (their world writes US addresses) and
those listed in `kChroniclePending` (`main.cpp`), with what each still
differs by. Still to port: the action states READY, COMM and SKILL
(rewritten in Chronicle) and the AI script's start.

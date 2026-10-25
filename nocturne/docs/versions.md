# Versions of the game

The rewrite builds four versions from one source tree:

| Name | Version | Executable | Layout |
|---|---|---|---|
| `maniax` | US Shin Megami Tensei III: Nocturne (Maniax) | SLUS_209.11 | the reference |
| `hardtype` | the fan rebalance Hardtype 1.5.1, a patch of US Maniax | SLUS_209.11 | US Maniax's addresses |
| `chronicle` | JP Nocturne Maniax Chronicle Edition (Raidou in place of Dante) | SLPM_666.81 | its own build |
| `vanilla` | JP Nocturne, the first release (no Amala, Fiends or difficulty) | SLPM_652.42 | its own build |

## The source tree

```
source/
  shared/     the code every version shares (src/, include/)
  maniax/     US Maniax's own: its data tables, and its side of every
              point where the versions differ
  hardtype/   Hardtype's own: the same files where it differs, and what it adds
  chronicle/  vanilla/   likewise
  tests/      the tests, built once per version
```

So the executable a piece of code comes from is the folder it is in.

- **Shared code never tests the version.** Where versions differ, shared
  code calls a function its header marks `[version]`, and each version
  defines it in a file at the same path under its own folder (shared
  `src/data/unit.cpp` and `maniax/src/data/unit.cpp`,
  `hardtype/src/data/unit.cpp`). A version file holds whole functions when
  they differ substantially, small hooks when only a step does.
- **A version falls back to US Maniax** for any file it doesn't have
  (`tools/sources.py`): Chronicle, close to US Maniax, will hold little.
- **Headers** are searched in the version's `include/` first, then
  `maniax/include/`, then `shared/include/`. A version's own record layouts
  (`nocturne/data/version_tables.hpp`, `nocturne/data/devil_ai.hpp`) and
  its helpers (`nocturne/hardtype.hpp`) live there.
- **Addresses.** Shared code writes US Maniax's addresses through
  `nocturne/address.hpp`: `addr(0x...)` for what every version has,
  `optionalAddr(0x...)` for what a version may lack (debug print formats;
  0 there, and the print is skipped). Both are evaluated at compile time:
  US Maniax and Hardtype keep the address, another version looks it up in
  its generated `source/<name>/include/nocturne/version_addresses.hpp`
  (`python tools/version_addresses.py <name>`), and an address with no
  counterpart is a compile error where `addr()` uses it. Small constants
  that differ (a music ID, the global work's offsets) are in each version's
  `nocturne/version_constants.hpp`.
- **Tables** are generated per version: `python tools/gen_tables.py` writes
  US Maniax's into `maniax/src/data/`, and
  `python tools/gen_tables.py --variant hardtype` writes Hardtype's that
  differ into `hardtype/src/data/`.

## Getting the discs

The ISOs sit in `nocturne/` under the names in `tools/disc_extract.py`:

```
python tools/disc_extract.py --variant hardtype
```

This extracts a version to `game/<name>/` and checks it against
`tools/disc-sha256-<name>.json`. Disc files are never committed.

## Building and testing a version

Set `NOCTURNE_VARIANT` before running the build scripts. Each version builds
into its own `build/*-<name>/` folder and runs against its own executable:

```
set NOCTURNE_VARIANT=hardtype
source\tests\tables\build.cmd
source\tests\differential\build.cmd 300 31
```

The tables test proves a version's tables byte for byte. The differential
test runs each rewritten function against that version's own instructions;
the tests against the legacy C (US Maniax only) are skipped for the other
versions, and their count printed. `variant_tests.cpp` and the
"(instructions)" tests cover what the versions change.

## Status

- **hardtype:** every change to a function the rewrite has is ported and
  proven against Hardtype's own instructions; see
  `source/hardtype/README.md`.
- **chronicle:** builds and runs its differential suite against its own
  instructions (below); the font and message engine and a few changed
  functions are still to port.
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

On 2026-10-25 the suite ran 412 tests against Chronicle's instructions,
all passing; 878 were pending (most because their worlds set up the US
font and message engine, which the script and help tests share) and 361
compare against US Maniax's legacy C only.

What the port has so far:

- **Layouts.** The global work's fields sit 4 lower from the event bits
  on and 0x2450 lower from the options on (`kGlobalWorkShift`,
  `kGlobalWorkTailShift`).
- **Constants.** RunSeKouka stops music 0x1C04xxxx for the event boss's
  repelled skill 0x107 (US 0x1C07xxxx).
- **US-only font data.** What only the US font engine has (the 416- and
  264-code tables, the last code laid out, the loaded styles, its pools,
  the character name buffer) is `optionalAddr`, 0 in Chronicle: its font
  engine is another (about 40 of the font and message functions differ),
  still to port.

The harness runs the same tests at Chronicle's addresses
(`source/tests/differential/version_map.cpp`): hooks, interpreted ranges,
entry points and the tests' static addresses are US Maniax's, mapped
through `reference/versions/chronicle-*.tsv` when it starts; gp comes from
the executable. Hooks that call US Maniax's legacy C run Chronicle's own
instructions instead (`hookUs`). A test that reaches a function Chronicle
has no counterpart for, or sets up the US font and message world, counts as
pending, as do those listed in `kChroniclePending` (`main.cpp`), with what
each still differs by.

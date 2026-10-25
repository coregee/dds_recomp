# Versions of the game

The rewrite builds five versions from one source tree. The source reads as
JP Maniax, the reference: the release every other one differs from least
(Chronicle and the US release are built on it, Hardtype on the US release,
and Vanilla is what came before it).

| Build | Version | Executable | Addresses |
|---|---|---|---|
| `maniax` | JP Nocturne Maniax (2004; Dante, the Labyrinth of Amala): the reference | SLPM_654.62 | its own |
| `vanilla` | JP Nocturne, the first release (2003; no Amala, Fiends or difficulty) | SLPM_652.42 | its own |
| `chronicle` | JP Nocturne Maniax Chronicle Edition (2008; Raidou in place of Dante) | SLPM_666.81 | its own |
| `us` | US Shin Megami Tensei III: Nocturne (Maniax, 2004) | SLUS_209.11 | the address keys (below) |
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

- **Traits, not build names.** Code tests how a build departs from JP
  Maniax (`nocturne/build.hpp`), never which build it is:
  - `NOCTURNE_US` / `kBuild.us`: the US release and Hardtype: English text
    and font engine, their global work and window layout, their constants.
  - `NOCTURNE_VANILLA` / `kBuild.vanilla`: the first release, without what
    Maniax added.
  - `NOCTURNE_CHRONICLE` / `kBuild.chronicle`: the Chronicle Edition's own
    changes.
  - `NOCTURNE_HARDTYPE` / `kBuild.hardtype`: the Hardtype patch.

  A small step that differs is `if constexpr` or a constant
  (`kBuild.us ? 0x14 : 0x19`); whole alternatives, and anything that names
  an address or type only some builds have, are `#if`, the departures
  first and JP Maniax's in `#else`. A unit's alternatives sit in its "By
  version" section, the most specific first.
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

Set `NOCTURNE_VARIANT` before running the build scripts (empty: `maniax`).
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
- **maniax (JP):** builds and runs its differential suite against its own
  instructions (fonts and message files from `game/jpmaniax/dds3/`, made
  as Chronicle's are). Its font and message engine is Chronicle's; its
  affinity and party damage are the US release's (Son's Oath and the
  spared Dante are Chronicle's changes); it keeps battle debug prints the
  US release and Chronicle removed (`SetAllPacket`'s hit names, Macca
  thrown, Ongyo-Ki's clones), outside `NOCTURNE_US` and `NOCTURNE_CHRONICLE`.
- **vanilla:** builds and runs its suite (876 tests pass, 84 differ, 384
  pending at 20 cases). `NOCTURNE_VANILLA` leaves out what Maniax added:
  eleven script commands, the AI's rotation commands, the boss refights,
  the race sacrifices and the Fiends (and Dante, and curse passing, in
  fusion). Its own tables, from `gen_tables.py --variant vanilla`, are the
  fusion tables (17 sacrifice results, 20 event-locked devils); the tables
  test proves them, and the inheritance tables, byte for byte.
  - **Skill IDs.** Maniax inserted skills 0x100..0x11F, so Vanilla
    numbers the passives (US 0x120..0x17F) 0x20 lower: `skill::` constants
    there go through `skill::maniaxId`, as does the passives' record index
    (0x108, not 0x128). Normal skills and devils keep their IDs (some
    rebalanced). A skill number written as a bare constant in the rewrite
    is a place to check.
  - **Still to port:** most of what differs is the talks' steps (Vanilla's
    negotiation differs widely), then battle formulas (magic attack, max
    HP, the effect's HP, escape, the player's chance to flee an ambush),
    rewards, the shop price and a few action and kouka steps.

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

What the port has so far (most of it JP Maniax's own code, which JP
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
  damage that leaves 1 HP spares no one (Chronicle's own; JP Maniax keeps
  the US release's).
- **Constants.** RunSeKouka stops music 0x1C04xxxx for the event boss's
  repelled skill 0x107 (Maniax 0x1C07xxxx: Dante's fight).

The harness runs the same tests at a JP build's addresses
(`source/tests/differential/version_map.cpp`): hooks, interpreted ranges,
entry points and the tests' static addresses are US Maniax's, mapped
through `reference/versions/<build>-*.tsv` when it starts; gp comes from
the executable, and the fonts and message files from `game/<folder>/dds3/`
(`tools/dds3_archive.py --ddt game/chronicle/DDS3.DDT ...`). Hooks that call
US Maniax's legacy C run the build's own instructions instead (`hookUs`).
A code address read from the build's memory (a step table's, the script
command table's) is the build's own: the tests take it back to US Maniax's
(`version::maniax`, `maniaxCodeOrDie`) before handing it to what maps
addresses. Functions the matcher can't pair (alike stubs, a function the
JP global work's shift reorders, the action states the JP builds changed)
are paired by hand in `reference/versions/<build>-function-pairs.tsv`, and
data in `<build>-data-pairs.tsv` (a debug print's format a build keeps as
a string but no longer prints maps to 0 there). Where a print's arguments
cost a call, the rewrite tests `diag::kept(message)` first: a build
without the print makes no call for it either.

A test that reaches a function the build has no counterpart for counts as
pending, as do those listed in `kJapanesePending` and `kChroniclePending`
(`main.cpp`), with what each still differs by (none at present). The JP
builds' changes to the action states are ported: their debug prints (JP
Maniax keeps more than the US release), Chronicle's speed for devil 0xC0
(Raidou, where Maniax exempts Dante) and the frames of the event boss's
skills 0x106..0x108 in `SetAllPacket`.

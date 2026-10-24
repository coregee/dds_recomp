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
- **chronicle, vanilla:** extracted; their functions are still to be matched
  to US Maniax's (they are separate builds, so every address differs).

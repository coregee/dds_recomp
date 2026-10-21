# Disc and code resources

The US disc (`tools/disc-sha256.json` lists every file):

| File | Size | Contents |
|---|---:|---|
| `SLUS_209.11` | 4.4 MB | the executable (EE) |
| `DDS3.DDT` / `DDS3.IMG` | 0.2 MB / 2.5 GB | index and data of the main archive (9,685 files) |
| `MOVIE/` | 968 MB | FMV |
| `IRX/`, `SOUNDIRX/`, `USERIRX/` | 1 MB | IOP modules |
| `DUMMY.DAT` | 600 MB | padding |

## What counts as code

The reconstruction covers the executable and the resources that behave like
code or define game rules. Art, models, sound and movies are assets and stay
out of scope.

**Inside the executable** (most of the rule data): skills (`datNormalSkill`,
0x3D7998), devils (`datDevilFormat`, 0x3497C0), encounters (`datEncount`,
0x3AEFE0), area encounter tables (`datEncountPack`, 0x3BADE0), affinities
(0x3A7FE0), passive-skill numbers (`datSpecialSkill`, 0x3DC1E0) and more.
Their record types are in `source/include/nocturne/data/`; their contents
are generated as source by `tools/gen_tables.py` into `source/src/data/`
(skills `datSkill` and `datNormalSkill`, passives `datSpecialSkill`, devils,
encounters, encounter tables, affinities) and checked byte-for-byte against
the executable by `source/tests/tables`. Also generated: items, level-up / growth
tables, Magatama, inheritance, every fusion table and the enemy AI records.
Still to do: shops.

**In the archive** (`python tools/dds3_archive.py list`):

| Type | Count | What |
|---|---:|---|
| `.bf` | 191 | compiled Atlus flowscript: events (133), field (44), facilities (7), negotiation (4), battle, result |
| `.bmd` | 31 | message tables used by scripts |
| `.inf`, `.npl`, `.dat` | ~125 | field/area configuration (not yet decoded) |

All `.bf` and `.bmd` files are extracted under `game/dds3/`. Flowscript is a
bytecode for a VM in the executable (`scr*` functions); `tools/flowscript.py`
decompiles all of them (and the AI scripts embedded in the executable) into
`source/scripts/`, verified against the original code. See
[flowscript.md](flowscript.md). The message tables (`.bmd`, MSG1) are kept
raw for now; decoding their text is still to do.

Not code: `.tb` (field texture banks, 826 files / 360 MB), `.tmx`, `.pb`,
`.lb`, `.smg`, `.f1/.f2`, `.d3p`, `.p2a`, `.bed`, `.pm1/.pm2`.

A few index entries are zero-length notes with Shift-JIS names; the
extractor lists but never writes them.

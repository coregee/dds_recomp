# Battle work access and original enemy AI startup bridge

Six complete routines add 1,664 passing original-instruction comparisons and
648 recognized body bytes. The host build passes `/W4 /WX`; interfaces were
saved in the working Ghidra project, independently reopened and checked. All six
selected exports decompile and merge into the 8,979-function inventory.

| PS2 RAM entry | Recovered role | Cases |
|---|---|---:|
| `00101978` | `dds3SearchProcessPriority` | 256 |
| `002469A0` | `nbGetMainProcessData` | 256 |
| `002469C0` | `nbGetUnitWorkPointer` | 256 |
| `00246A40` | `nbGetPartyFromFormindex` | 256 |
| `00246AB8` | `nbGetUnitWorkFromFormindex` | 256 |
| `00253C40` | `ps2BattleStartActorAi`, descriptive native name | 384 |

The [rolling report](battle-work-access-validation.json) covers 2,675,392
original instruction steps. Full declared RAM, defined raw64 returns, Status,
processor primitives, returning callee saves and ordered VM calls agree. All
128 reachable main addresses execute. Two of the scheduler search's 130 total
main addresses are separately proved impossible: its fixed selector can only
be0,1,2, whereas those generic switch fall-through branches require another
value. Delay slots execute normally; no original function return is supplied
by a test hook.

## Community findings checked against the executable

The [randomizer implementation](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/nocturne.py)
uses ELF file offset `002999E0` for AI rows, but its notes give `002999E4`.
The [community engine audit](community-engine-audit.json) checks the actual
MIPS multiply/load instructions: record RAM base is `003989E0`, stride `A4`,
procedure halfword at `+0`, targeting selector at `+2`, decision data at `+4`.
The native startup bridge resets actor action `+6A` to `FFFF` and skill `+6C`
to0, then passes the procedure halfword into actual `nbInitAiScript`.

Each of the 383 community demon IDs1..383, plus native row0, now traverses this
bridge and the recovered startup using its unchanged original AI record and
embedded BF. Every procedure index lies within the original141-procedure BF.
Comparisons include real constructors, message actor-name allocation, user data,
parent linking and publication of the new process in main work at `+104`.
They prove construction/startup for this inspected domain, not decision-script
execution or the entire AI table's allocated extent.

The [DDS community kernel source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/kernel/dds3KernelCore.c)
independently corroborates queue search and process links. The selected priority
search resolves to DDS1 `00101938`: all140 bytes agree after exactly three
queue-head GP relocations. A full relocated-byte search finds that span uniquely
in DDS executable segments. The [transfer report](battle-work-access-transfer.json)
records those individual words; the generic finder did not relax unconfigured
GP operands. Other selected battle-work bodies do not resolve under its current
strict masks. This is not DDS execution or evidence for identical battle layouts.

## Native work access

The scheduler searches delayed-start, active and delayed-destroy heads in that
order: `54E850`, `54E868`, `54E85C`. Priority is a sign-extended LW at process
`+20`, compared to the full raw64 input; next is `+3C`. High-lane mismatches and
duplicate priorities retain the first native match. Main work uses priority
`3FA` and unconditionally tail-calls the existing data getter. No HD null guard
is added; a missing main process is outside the backed successful cases.

Forms have stride `F0`; flags at `+78` require both bits1 and40 for party lookup.
Signed16 party index at `+90` selects a stride80 record from main work `+10`.
The raw signed64 form guard only tests `<16`, so negative inputs and high lanes
matter. Backed negative-prefix cases preserve those original accesses.

Party flags are LHU at `+0`; signed16 unit index is at `+4`. Bit1 is required;
bit2 takes precedence over bit4 and selects strideEC units from main work `+8`.
Otherwise bit4 rejects access, or lookup uses global work `54EA20` plus `A54`.
Form indices at least16 use that global unit array directly. Below16, the native
unit getter resolves main work twice through actual party lookup; it retains
all calls and reloads.

Five reviewed Unity roles provide names, while native instructions determine
these offsets, signed guards and wrapping arithmetic. Managed arrays, bounds
checks, null/type guards and HD pointer widths are not imported into PS2 C.

## Current boundary

Current integrated recovery is **1,404 / 8,979 functions (15.636%)**, 198,456
recognized body bytes and 667,969 aggregated comparisons. The last full run
remains413 /462,684; 104 focused reports add205,285 cases. Counts include
repeated dependency/integration cases, not unique gameplay scenarios.

The [AI frontier](battle-ai-frontier.json) has49 unresolved direct bodies /
16,624 bytes at source-current boundaries. Continue native target flags,
eligibility, battle data access and scoring before automatic targeting002879F0
and command52. Original AI decision execution, scheduling, a matching executable
and physical PS2 behavior remain unproved. Working project and one current
subsystem capture are updated in place; no checkpoint or project copy is made.

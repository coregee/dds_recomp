# Native status, skill attributes and support-counter primitives

Seven complete PS2 bodies in `src/battle_support_access.c` and `.h` compile
and pass **1,792 original-instruction comparisons**, executing **54,950 steps**
and every **60 main instruction address**. **64 connected setter/getter
sequences** run the actual original store before the actual original read.
Actual priority-process lookup, process data and party/unit resolution execute;
no callee's game result is supplied by a fixture.

| PS2 entry | Role | Recognized bytes | Cases |
|---|---|---:|---:|
| `00267788` | `nbGetBadStat` | 44 | 256 |
| `00267E38` | `nbGetNormalSkillAttr` | 24 | 256 |
| `00267E50` | `nbSetHojoCounter` | 64 | 256 |
| `00267E90` | `nbGetHojoCounter` | 56 | 256 |
| `00267EC8` | `nbGetHojoCounterMax` | 72 | 256 |
| `00267F18` | `nbGetHojoCounterMin` | 56 | 256 |
| `0026A468` | `nbCheckFormationPlayerSide` | 8 | 256 |

The total is **324 recognized body bytes**. The two support-bound switches
now own their previously missing case instructions. Their contiguous spans
also contain one four-byte padding word each, excluded from the recognized
bodies. The recognized function count remains8,979.

## Verified native contracts

`nbGetBadStat` resolves a formation index through the actual unit getter,
returns0 for a null result, and otherwise reads unit `+E` as an unsigned
halfword masked withFFF. It does not return a signed halfword status.

`nbGetNormalSkillAttr` reads a **signed byte** at
`3D6998 + low_skill_id * 8`. The descriptor stride and byte signedness come
from SLL/LB instructions; a managed HD object field does not establish the
original layout. Compared inputs include a backed negative prefix index,
IDs0/1/511, high argument lanes and bytes00/7F/80/FF.

The support setter/getter call the actual party resolver. A null party skips
the store or returns0. Otherwise they access `party + 8 + low_type * 2`, with
no separate type bound: the setter stores low16, while the getter uses **signed
LH**, returning a sign-extended raw64 value. Cases cover negative backed type
offsets, upper argument lanes, positive/negative halfwords and actual stores
followed by reads. Raw formation inputs preserve the original signed64 guard
of the party and unit resolvers, including backed negative indices and
high-lane cases.

The bound switches use a **full64 unsigned** type<20 guard:

| Type | Maximum | Minimum |
|---|---:|---:|
| 0..3 | 127 | 0 |
| 4..8 | 4 | -4 |
| 9..15 | 1 | 0 |
| 16..18 | 127 | 0 |
| 19 | 32,767 | 0 |
| All other raw64 values | 0 | 0 |

`nbCheckFormationPlayerSide` is the original signed64 comparison against4.
Negative values return1. This small helper is distinct from the AI player
filter, which classifies a unit by flag4.

## Original switch ownership and export limitation

`RepairBattleSupportSwitches.java` checks the original executable hash, both
contiguous code hashes and both80-byte dispatch-table hashes. It restores
the20-entry tables at `544C60` and `544CB0`, checks all original destinations,
decodes the arms, adds computed-jump references, and checks for foreign owners
and unexpected padding. Both functions now own their complete instruction
ranges,72 and56 bytes. No original instruction or table byte is modified.

All twenty types execute through the original switches and agree with the
recovered C. The maximum's refreshed Ghidra pseudocode shows the expected
cases. The minimum's basic destination override incorrectly rendered only
case4 as-4, omitting the repeated cases5..8. That override was removed. Its raw
Ghidra pseudocode still renders an unresolved indirect dispatch. **The canonical
C and original-instruction comparisons cover the complete minimum function;
the raw decompiler rendering remains a separate limitation.** Do not treat
that export as a complete reconstructed switch. The current AI frontier records
this rendering issue separately from unresolved source bodies.

The project is saved in place. All seven names and raw interfaces pass an
independent reopen check; all seven selected exports merge into the inventory.
These operations establish source/interface recovery, not a matching PS2
executable or physical hardware behavior.

## Unity, community context and transfer

Seven decompiled Unity counterparts are reviewed in
[battle-support-access-matches.json](battle-support-access-matches.json).
They are `nbCalc.nbGetBadStat`, `nbGetNormalSkillAttr`, `nbSetHojoCounter`,
`nbGetHojoCounter`, `nbGetHojoCounterMax`, `nbGetHojoCounterMin` and
`nbCheckFormationPlayerSide`. HD names constrain roles; original readers decide
field widths, unchecked index behavior and raw64 interfaces. HD bounds/null
checks and managed array indirection are not imported.

The pinned [DDS battle-table research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
at revision `bec33411543cdc487bad9debdf758f0090a2242c` supplies related-engine
action-attribute and support-effect context. The pinned
[Nocturne randomizer notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
at `f74e85c0f632b751eaf278046884961c618c8541` distinguish basic weighted AI
records from embedded BF. Their inspected URLs/revisions/hashes are retained
in [the community context audit](battle-ai-filters-community.json), referenced
and hashed by this batch's Unity review. These sources do not establish
identical DDS selector domains or layouts. The strict complete-span search
finds no selected DDS counterpart here; shared semantics may still use
different instructions or data arrangements.

## Current evidence and next work

- [Focused proof](battle-support-access-validation.json): per-entry cases,
  all coverage addresses, declared RAM, raw64 returns, Status, primitives,
  callee saves, VM target order, independent return/store oracles and hashes.
- [Original switch specification](battle-support-switches.json) and
  [rolling ownership repair result](battle-support-switch-repair.json).
- [Interfaces](battle-support-access-interfaces.json) and
  [independent Ghidra check](battle-support-access-abi.json).
- [DDS transfer search](battle-support-access-transfer.json).
- Driver `tooling/recover_battle_support_access.py`, with `prepare`, `pin`,
  `compare`, `transfer`, `publish`; one current capture at
  `analysis/battle-support-access/vectors.jsonl`.

The current audit records **1,431 /8,979 integrated routines (15.937%)**,
**202,476 recognized body bytes**, **677,441 aggregate comparisons**, and107
focused reports/214,757 focused cases. The last full run remains413/462,684.
Aggregate cases include repeated dependencies and integrations. Current
ledgers contain667 PS2/HD roles,756 descriptive aliases and280 signatures.
The previously recovered ten filters were also rechecked against their
current original capture after the shared test-address router changed.

The selected AI graph has **22 unresolved bodies /12,644 bytes**, with no
missing exports. Continue support ratios, affinity/estimate calculation and
scorer `00286B68`, then single/group dispatch and automatic target selection.
The minimum's raw export needs improved switch reconstruction as noted above.
The compared domain is finite backed data, acyclic queues and declared aliases;
arbitrary invalid/private addresses, full gameplay, scheduling, a matching
binary and physical PS2 execution remain unproved. No new full-suite run,
checkpoint, project copy or duplicate capture was made.

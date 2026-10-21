# Native AI target filters

Ten complete original PS2 bodies are integrated in `src/battle_ai_filters.c`
and `.h`. They pass **2,560 original-instruction comparisons**, executing
**6,565,974 steps** and every **342 main instruction address**. There are no
excluded main addresses or substitute game-result hooks.

**640 cases** first execute actual `nbSetSelectOkMark`, including eligibility,
named manager lookup, list creation and ordering, before running a filter.
These connected cases execute **16,320 original C.LT.S comparisons** and check
the FCSR condition bit. The filters themselves contain no floating-point or
RNG operation. Actual scheduler priority lookup, process data, party/unit
resolution and the previously recovered alignment reader execute as required.

| PS2 entry | Recovered role / Unity method | Body bytes | Cases |
|---|---|---:|---:|
| `00286EC0` | `nbAiSelLifeMin` / `nbAi.Sel_LIFEMIN` | 200 | 256 |
| `00286F88` | `nbAiSelBaarLv` / `nbAi.Sel_BAARLV` | 232 | 256 |
| `00287070` | `nbAiSelLvMin` / `nbAi.Sel_LVMIN` | 200 | 256 |
| `00287138` | `nbAiSelBad` / `nbAi.Sel_BAD` | 156 | 256 |
| `002871D8` | `nbAiSelId` / `nbAi.Sel_ID` | 172 | 256 |
| `00287288` | `nbAiSelLight` / `nbAi.Sel_LIGHT` | 176 | 256 |
| `00287338` | `nbAiSelDark` / `nbAi.Sel_DARK` | 176 | 256 |
| `002873E8` | `nbAiSelPlayer` / `nbAi.Sel_PLAYER` | 144 | 256 |
| `00287478` | `nbAiSelJoken` / `nbAi.Sel_JOKEN` | 76 | 256 |
| `002874C8` | `nbAiSelRnd` / `nbAi.Sel_RND` | 60 | 256 |

The total is **1,592 recognized body bytes**. The original selector table
`00545800`, owner `00287508`, independently links selectors1..10 to these
ten leaf calls. The table order is LIFEMIN, BAD, ID, LIGHT, DARK, PLAYER, JOKEN,
RND, BAARLV, LVMIN. Selector0 and the fallback scorer are still unrecovered.

## Contracts that matter for source recovery

All filters traverse sixteen slots of strideF0, testing slot flag4 and adding
flag8. They retain other flag bits and existing flag8 marks. Selection flag8
is not globally cleared by these filters.

LIFEMIN reads unsigned halfword unit `+6`; LVMIN and BAARLV read unit `+14`.
Their initial minimum is **10,000**, and replacement uses strict comparison:
all candidates at or above10,000 produce no new mark, and the first equal
minimum wins. BAARLV additionally skips status whose low twelve bits equal200.
Compared cases include no eligible units, ties, threshold boundaries and
halfword values through65,535.

BAD compares the zero-extended low twelve status bits with the full raw64
argument. ID also compares its unsigned halfword demon ID with the full raw64
argument, and skips unit flag4. High lanes therefore cannot simply be discarded
from these requested values. Player classification tests **unit flag4**, rather
than assuming it from slot index or side.

LIGHT and DARK skip unit flag4, call the actual original alignment reader,
and match1 or full-width-1. The reader gives demon flag40 precedence over80;
it is not replaced with a fixture result or Unity's managed object model.

JOKEN caches the slot base but reads context `+190` for each eligible slot.
The tested mask alias overlaps slot0's flags: a mark at an earlier slot can
change a condition bit observed by a later slot. The recovered C preserves that
load/store order. RND marks every eligible slot and makes **no RNG call**;
random singleton choice belongs to the later dispatcher, not this leaf.

## Community research, Unity and transfer

[Randomizer notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
are pinned to `f74e85c0f632b751eaf278046884961c618c8541`, and
[DDS battle-table research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
to `bec33411543cdc487bad9debdf758f0090a2242c`. The randomizer distinguishes
weighted skill records from the embedded BF resource; DDS documentation gives
related-engine table and targeting context. Neither establishes the PS2 filter
implementation or a shared numeric selector domain by itself.

The independently checked original Nocturne AI header view at3989E0, strideA4,
has selector halfword `+2` equal to0 in all384 inspected rows. Therefore those
retail headers alone would not cover selectors1..10. The constructed filter
cases and connected eligibility/list cases cover those native bodies directly;
full original BF-to-automatic-target execution remains future work. Community
URLs, retrieved hashes, the original selector table and header histogram are
recorded in [battle-ai-filters-community.json](battle-ai-filters-community.json).

Ten decompiled Unity counterparts are reviewed in
[battle-ai-filters-matches.json](battle-ai-filters-matches.json). Their names
constrain semantic roles, while PS2 instructions establish offsets, raw widths
and ordering. HD array bounds, null guards and managed layouts are not imported.
The strict selected full-span DDS search finds no complete counterpart for
these bodies. That result does not rule out shared semantics implemented with
different layouts or instructions. The shared signature ledger records the
checked Nocturne behavior with those transfer limits.

## Evidence and remaining work

- [Focused validation](battle-ai-filters-validation.json) checks all declared
  RAM, Status, primitives, callee saves, ordered VM targets, FCSR condition,
  independent flag oracles, source/verifier hashes and original capture hashes.
- [Interfaces](battle-ai-filters-interfaces.json) and
  [independent reopened Ghidra check](battle-ai-filters-abi.json) cover all ten
  routines. The current ten exports decompile and merge into the inventory.
- [DDS transfer search](battle-ai-filters-transfer.json) and
  [current AI frontier](battle-ai-frontier.json).
- Driver `tooling/recover_battle_ai_filters.py` provides `prepare`, `pin`,
  `compare`, `transfer`, `publish`. Its capture is overwritten in place at
  `analysis/battle-ai-filters/vectors.jsonl`.

At this milestone the current audit records **1,424 /8,979 routines
(15.859%)**, **202,152 recognized integrated bytes**, **675,649 aggregate
comparisons**, and106 focused reports/212,965 focused cases. The last full run
remains413/462,684; aggregate counts include repeated dependency/integration
cases. There are660 PS2/HD mappings,756 descriptive aliases and279 signatures.

The selected original AI graph now has **29 unresolved bodies /12,928 bytes**.
Next are status, normal-skill attributes and support-counter primitives, then
scoring before single/group and automatic target dispatch. Backed acyclic
queues and nonnull eligible-unit resolution are the compared domain. Missing
main processes, arbitrary invalid private aliases, full gameplay, scheduling,
a matching PS2 executable and physical hardware execution remain unproved.
Work and captures stay in place; no new checkpoint or full-suite run.

# Evolution and negotiation flow

The [publication](evolution-negotiation-publication.json) adds five complete
PS2 routines: evolution `00223258`, queue `0026A8A0`, message state `0026A998`,
payment `00270110` and outcome selection `00270300`. They contain 487 original
instructions, 1,948 recognized bytes and 1,980 span bytes. At this publication,
recovery reached
2,620/9,060 functions (28.918%), with 436,868 recognized bytes and 529 source
units. The full program remains incomplete.

Unity identifies `rstCalcCore.cmbCalcEvoEvent`, `NbNegoFlowTwo.Flow6_22` and
`Flow6_24`. Queue and message helpers retain descriptive PS2-only names.
The pinned randomizer [notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
at revision `f74e85c0f632b751eaf278046884961c618c8541` supply evolution-record
and recruitment context. Their recruitment patch locations `00270584` and
`002705D8` fall inside the original outcome routine. Patch behavior is kept
separate from retail PS2 behavior; uncertain file/RAM offsets are not imported.
The [evolution](evolution-event-source-review.json) and
[flow](negotiation-flow-source-review.json) reviews pin the inspected sources.

Evolution consumes a flat event record: primary species at +2, type at +5 and
alternate species at +6. Nonzero low-byte mode and type 5 compare dark stock
against half of occupied stock. Its output is nullable and its interface is
void; incidental V0 values do not define a selected-species return. A real
default-unit constructor runs before the source level is reread. Exact
source/output alias therefore sees the newly constructed level and skips
raising it. Distinct output can receive real EXP and weighted parameter growth,
with the original cap check and final flag 0x200. No post-growth refill is added.

Queue capacity uses signed count <8 without a lower bound. At count -1, the
command store aliases the count itself, which the original reloads before
incrementing. The message setter stores low words but tests its flag argument
across all 64 bits. Payment queues commands before rereading its request kind
and calls the original item, Hearts and currency algorithms. The Hearts path
requires the skill view at `00339E1A` and game RAM through +0x11D30. Outcome
selection uses genuine skill weights, signed wrapping adjustments, inclusive
cumulative comparisons, actual RNG advancement and the original bucket-4-to-2
fallback. These functions produce queue and continuation data; they do not
execute the VM or dialogue consumers.

All [3,161 original cases](evolution-negotiation-original.json), over 11,012,079
instruction steps, pass in the isolated probe and the
[529-unit main build](evolution-negotiation-main-C-validation.json). Sixty-four
connected payment/outcome cases add 64 calls per build. Comparisons include
414,381,812 mutable RAM bytes per build, checked immutable original tables,
defined Flow returns, Status, condition/value FCSR and CPU primitives. The
original runner checks native callee saves. The
[results review](evolution-negotiation-results-review.json) reconstructs the
authored BEFORE states, checks null/self/distinct output and majority paths,
and confirms every selected non-delay PC was observed. Embedded delay slots
are not separately instrumented in the PC census.

All five [native interfaces](evolution-negotiation-native-ghidra.json) were
saved, independently reopened and exported, including actual void return
storage for evolution. The [retained 22-function replay](evolution-negotiation-focused-regressions.json)
passes all 3,057 cases on this main DLL. All earlier 527 object files remain
unchanged; the last full 413-function/462,684-case regression belongs to the
525-unit epoch. Full volatile banks, private frames, HI/LO, arithmetic FCSR
flags, physical timing, exhaustive aliases and whole-game execution remain
outside this finite semantic proof.

Two new entries in [shared SMT fingerprints](shared-smt-signatures.tsv) record
the evolution composition and negotiation queue/payment/outcome patterns.
They are search leads: each game still needs independent layout, table, ABI,
RNG and instruction checks. No DDS identity credit is inferred.

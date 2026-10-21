# Shared emitter and track-polygon prerequisites

Seventeen complete original bodies /4,420 recognized bytes are integrated into
[the C source](../src/polygon_prerequisites.c). All 4,352 original-instruction
comparisons pass. Working interfaces were saved and independently reopened;
all seventeen exports decompile and merge into the current inventory.

The full executable remains the target. This batch closes prerequisites for
the shared initializer and actual copy constructors; it does not recover the
outer constructors, rendering, scheduling or a matching executable.

## Community findings incorporated

The reviewed Megami-Decomps revision is
`bec33411543cdc487bad9debdf758f0090a2242c`. Six directly inspected files are
pinned with content hashes in [the reference review](polygon-prerequisites-matches.json).
Its [particle manager](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/parManager.c)
defines the three-colour ramp and shared `0x150` emitter header. Native Nocturne
instructions corroborate the masked RGB fields, alpha/fade durations, mode1/2
early returns and interleaved COP1 slopes. This establishes useful context where
the proposed Unity colour setter was a different routine.

The [history definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/par_table.h)
and [effect definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff.h)
corroborate sixteen-byte slots/owners, twenty-byte vertex cells and a forty-four-
byte vertex-system footer. Native allocation and reset consumers retain dirty
padding, scale and unused fields. The sixty-four-byte state allocator clears
only age/color at `+20/+24`, not its entire payload.

The [cell API](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/par_cell_api.h)
and [polygon manager](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/polyManager.c)
supply topology and ownership context. The shared thirteen constructor families
lead through emitter infrastructure; their tails must not be conflated with the
four special polygon families. Existing descriptive polygon aliases remain
entry-address aliases, rather than a claim that every shared record belongs
exclusively to polygons. Continue using the corroborated emitter header when
recovering the common initializer and copies.

Twelve Unity roles are reviewed. Proposed identities for `00163F00` with HD
`dds3TrackPolyColorSet` and `00166100` with HD `dds3TrackPolyInit` are rejected:
those HD bodies update one cell colour and global draw state, respectively.
Neither establishes the native timed ramp or individual cell reset algorithm.
No upstream implementation is linked or executed as a game dependency.

## Original bodies and dispatch

| Native entry | Recovered role |
|---|---|
| `0015DEC0` | Owned sixty-four-byte state cells |
| `00163F00` | Timed three-colour/fade ramp setup |
| `00164420` | Owned point-history slabs and sixteen-byte records |
| `00165A38` | Original return-zero sample lookup |
| `00165EB8` | Topology-dependent vertex-system allocation/material setup |
| `00166100` | Individual vertex-cell reset |
| `00167890` | Submission-mode halfword setter |
| `00167898` | Actual unchanged vertex colour property dispatch |
| `00166790`, `001667F0`, `00166940` | Pair constant, VU fade and rise/fall colours |
| `00166B08`, `00166B78`, `00166E30` | Triple constant, dual VU fade and integer rise/fall |
| `00167258`, `001672B8`, `00167370` | Quad constant, integer fade and rise/fall |

All fifteen original pointer slots at `00317600` are inspected. Kinds0/1/3
have three real callbacks each; kinds2/4 retain null slots. The canonical
dispatcher preserves the unchecked original table selection. The host bridge
executes the nine recovered bodies and aborts for unsupported targets rather
than supplying a synthesized callback.

[Boundary discovery](polygon-vertex-discovery.json) recognizes five missing
table targets. Earlier heuristic fragments at `00166800` and `00166950` started
sixteen bytes late and are replaced by `001667F0` and `00166940`. Their complete
spans retain original unreachable alignment NOP bytes while ownership excludes
the NOP gaps. Three additional leaf functions bring the inventory from8,982
to8,985. Boundary discovery alone adds no compiled recovery credit.

## Verification and transfer

[The focused proof](polygon-prerequisites-validation.json) compares full
declared RAM, raw defined returns, Status, callee saves, COP1 condition and
defined VU/ACC/Q state. It executes616,223 original steps,108,201 vector
instructions,205 C.EQ.S comparisons,271 real property callbacks and15 connected
vertex-constructor-to-colour sequences. All887 reachable selected main
addresses execute. The other82 of969 main addresses have separate original
byte-mask/logical-shift dead-path proofs; the negative conversion arms in the
pair/triple fade bodies execute using zero-owner fixtures.

All244 quad BREAK7 cases agree, including nested dispatch. Six reviewed DIVU/
DIVU1 zero sites use the processor primitive's published zero-divisor result;
the original following branch and BREAK still execute. The observer supplies
no game return and claims no normal exception unwinding. Only VF2.ZW unused
implicit CPU upper scratch is excluded when scalar QMTC2 actually executes;
other defined vector/ACC/Q words remain compared.

[Static DDS transfer](polygon-prerequisites-transfer.json) resolves sixteen
complete spans. Four require explicit address-pair checks beyond the generic
scanner: two VU constant references, a reused LUI with two ADDIU consumers and
the indexed property-table load. All other words, including alignment NOPs,
agree. Six independently matched full callback bodies constrain the entire
fifteen-slot table. The eight-byte return-zero function retains166 possible
counterparts and is not promoted. Static transfer does not prove DDS execution.

[Affected regressions](polygon-prerequisites-regressions.json) check24,528 prior
Magatuhi, billboard, motion, retail and ownership cases against the current
host. Existing negative-count track-gradient coverage remains explicitly
unvisited. No fresh full-suite or physical runtime execution is claimed.

The [current progress audit](recovery-progress.json) records1,837/8,985 functions
(20.445%),310,867 focused and773,551 aggregated comparisons across136 focused
reports. The expanded [motion-effect frontier](model-motion-effect-frontier.json)
has57 pending recognized descendants /7,988 bytes and no missing exports at its
inspected boundaries. This graph overlaps other frontiers and must not be summed.

## Next work

Recover the original common emitter initializer `0015DF58`, its actual billboard
clone/mode dependencies and track-owner/reset paths. Preserve the kind-four
parameter frame's input-derived private bytes before exercising that path.
Then recover the thirteen common and four special copy constructors, generic
copy kinds0..2 and the outer motion-effect change at `001DD440`. Continue
checking original asset associations and community definitions alongside Unity.
Returning bounded allocation/count/colour inputs are covered here; arbitrary
aliasing, overflow/exhaustion, processor timing/full flags, runtime selection,
physical rendering and whole-program/binary matching remain unproved.

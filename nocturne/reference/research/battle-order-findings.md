# Battle turn order

Four complete original PS2 bodies are reconstructed in `src/battle_order.c`:
183 recognized instructions, 732 recognized bytes and 736 span bytes. They
have passed all 768 original/probe/main cases and are registered. The
[publication](battle-order-publication.json) takes recovery to 2,702/9,062
functions and 460,140 recognized bytes. All four native interfaces were saved,
freshly reopened and exported; all 544 earlier objects and sources are
unchanged. All 1,632 retained compendium restore and roster cases pass.

| PS2 entry | Unity role | Native interface |
| --- | --- | --- |
| 00258048 | nbMisc.nbAddOrder, 18274B650 | void(raw64 actor index) |
| 00258280 | nbMisc.nbSetOrderSide, 18274F0C0 | void(raw64 side) |
| 002583D8 | nbMisc.nbSetOrder, 18274F2F0 | void() |
| 00258418 | nbMisc.nbSetNextOrder, 18274EC40 | void() |

The existing recovered 002580E8 is `nbSortOrder`, corresponding to Unity
18274F760. It executes as a real dependency. The source and HD study distinguish
that sorter from the newly recovered insertion routine.

## Native structures and control

The real process lookup searches the original three queues for priority 03FA.
It returns Main process data through the recovered process-list code. Main+0
points to 240-byte actors, Main+10 points to 128-byte formation entries, and
the separate game unit records have a 236-byte stride. These are distinct
structures; the actor stride follows the original word shifts/subtraction.

Main+48 contains twelve signed order bytes. Main+54 is a signed byte cursor,
Main+1C is the selected signed formation index stored as a halfword, and
Main+60 bit 8 selects the default side. AddOrder requires both actor flag bits
01 and 40 at actor+78, reads the signed halfword at actor+90 and stores its
low byte into the first negative order vacancy after the current cursor.
Only native word arithmetic narrows the raw actor-index argument. There is
no additional actor-index cap in the recovered source.

SetOrderSide tests all 64 argument bits against zero. Zero scans formations
0 through 3; any nonzero value scans 4 through 13. It clears exactly twelve
order bytes and accepts formation flag 01 while excluding flag 20. A nonempty
list sets cursor zero, runs the real sorter and publishes its first index.
An empty list stores FFFF as selection and FF as cursor.

SetOrder reads the Main side flag and tail-calls SetOrderSide. The second
original process lookup remains a real call. SetNextOrder rebuilds immediately
for a negative cursor; otherwise it increments with the native signed-byte
wrap, skips negative entries and rebuilds when the cursor reaches twelve.
After an empty rebuild on the latter path, it reads Main+47 through cursor FF
and stores that signed byte as selection. This unusual read is retained.
Cursor 127 also wraps to -128 before its subsequent indexed read; the authored
cohort backs that address explicitly rather than adding a guard.

The existing sorter uses real parameter-4 evaluation from the referenced unit,
including native flag behavior and clamping, followed by the signed formation
tie field. The tests supply units and formation records, not speeds or sorted
results. All four new interfaces are genuinely void; incidental V0 values do
not become return values.

## Evidence and validation boundary

[Source review](battle-order-source-review.json) binds every selected body to
the original ELF and instruction listing. The [Unity/community study](battle-order-HD-community-study.json)
records actual retained HD bodies and their managed-layout, bounds and null
check differences. Its pinned [Nocturne Randomizer notes](https://raw.githubusercontent.com/nmarkro/Nocturne-Randomizer/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
identify SLUS_209.11 file-table formats and distinguish file offsets from RAM
addresses. Those notes provide battle-data context, not exact symbols or
authority for the native actor/order layout. Modified recruitment policies
are excluded from the original behavior contract.

The independently authored BEFORE cohort contains 768 primary cases and
48 connected sequences with 272 additional void calls, for 1,040 actual call
positions per replay. It includes all three queue placements, eight formation
eligibility worlds, raw upper argument bits, actor flag guards, insertion
vacancies and full tails, signed cursors, empty rebuilds and connected state
changes. Complete declared ordinary RAM totals 119,583,744 bytes per replay.
Expected outputs and previously captured results do not author the inputs.

The final independent results review checks all 768 original ordinary-RAM
states against source-derived order and genuine sorter/parameter effects.
Original capture executes 1,311,990 instruction steps. All 149 visible
non-delay selected PCs are reached; 34 folded delay instructions are qualified
separately, without claiming exhaustive edge or input coverage. The retained
roster/restore replay adds 1,987 actual call positions and compares 237,301,376
ordinary-RAM bytes against the unchanged original vectors.

The actual comparison covers all primary and connected void completions,
ordinary RAM, immutable original data, Status/FCSR condition, primitive counts,
callee saves, guest stack balance and provider restoration. It does not claim
exhaustive inputs, complete volatile or private-frame equality, arithmetic FCSR
flags, physical gameplay or a demonstrated counterpart in Digital Devil Saga.
Related SMT games must independently verify strides, offsets, ABI and control
before reusing these search fingerprints.

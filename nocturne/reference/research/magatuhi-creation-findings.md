# Magatuhi construction, history ownership and copying

Fourteen complete original bodies are integrated in `src/magatuhi_creation.c`,
adding 3,628 recognized body bytes. [The comparison](magatuhi-creation-validation.json)
passes 2,560 original-instruction cases. It reaches 798/804 selected main
addresses; the six remaining addresses form a signed-negative conversion arm
that cannot follow the original zero-extending halfword load.

| Entry | Recovered role | Cases |
|---|---|---:|
| `001A52C8` | Reset one history slot | 128 |
| `001A5328` | Allocate the shared value/history arrays | 256 |
| `001A51E0` | Copy seven parameters and retain the history owner | 128 |
| `001A5CB0` | Fill history colours through the actual packed-colour helper | 256 |
| `001ABD90` | Allocate the 56-byte math slots and their owner footer | 128 |
| `001A5DA0` | Smoke-convergence constructor | 128 |
| `001A6780` | Four-point constructor | 128 |
| `001A70F0` | Cylinder constructor | 128 |
| `001A7958` | Spiral constructor | 128 |
| `001A81C8` | Smoke constructor | 128 |
| `001A8BD0` | Dispatch to the original particle constructor | 256 |
| `001A8E58` | Copy the particle effect's parameter data | 256 |
| `0015AF10` | Copy the generic effect through its original table | 256 |
| `001DF600` | Copy and retain a model's generic effect resource | 256 |

## Community research changes the identification

The `00320040` table was initially labelled as line constructors. The DDS
[Magatuhi source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/effMagatuhi.c)
and [record definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff.h)
identify the five particle families and shared history owner independently.
Original Nocturne allocation offsets and consumers corroborate that context,
and fourteen named Unity bodies supply reviewed semantic roles. The current
[frontier](model-motion-effect-frontier.json) now calls these Magatuhi
constructors. Earlier line terminology remains historical rather than a type.

The source review also inspected `effMath.c`, `effManager.c` and the source-unit
notes at revision `bec33411543cdc487bad9debdf758f0090a2242c`. Direct links and
content hashes are recorded in [the reference review](magatuhi-creation-matches.json).
Upstream material guided recovery and input records; it was not copied or linked
as the implementation. Managed allocations, guards and field layouts remain
distinct from the original program.

## Native layouts and behavior

The shared arrays precede a `0x38`-byte footer. The allocation contains positions,
history colours, another per-history word array, slot colours, two halfword
cursor/count arrays and sixteen-byte angle rows. The footer retains their raw
addresses, the original texture-reader result and allocation handle. Each
creation also writes the original fifteen UV records at `0056AF30`.

The history owner copies seven words, creates those arrays and fills colours
starting at fraction zero. The fraction accumulates `1/historyCount`; its last
nominal sample remains below one. The actual native packed-colour routine
executes, preserving operand order and rounding. A zero history count still
performs the division before skipping the loop, as in the original instructions.

The five particle strides are `30`, `4`, `18`, `1C` and `30` bytes in hexadecimal.
Smoke convergence and smoke place their work after the particle array; the other
families place particles after their work. Copied parameter records are `17C`,
`180`, `DC`, `E0` and `DC` bytes. Thirty-two-byte load/store groups and final
twenty-eight-byte groups are snapshotted in the original order. Cases exercise
both eight-byte aligned and four-byte aligned source records.

Only the copied signed delay modulus clamps to one when nonpositive. The caller's
source record remains unchanged. Each particle advances the four-word RNG at
`00316FE0`, computes the unsigned remainder and stores its negative as the initial
age. This is separate from the default RNG at `00529BD8`. Tests independently
derive all 4,535 advances and resulting particle ages from the initial input,
in addition to comparing full native/C RAM.

## Connected verification and evidence boundaries

The 2,560 cases execute 2,517,229 original steps, 209,952 vector instructions,
8,590 COP1 comparisons, 1,452 ordered actual constructor/generic-copy callbacks
and 416 construction-to-release sequences. The sequences call previously
recovered destructors and the real handle coalescer and pool release routines.
Another 168 original part/PCP copy callbacks and 168 recursive cleanup callbacks
execute through generic kind four.

Full declared RAM, defined raw returns, Status/CPU primitives, callee saves and
defined processor values agree. The 347,832 checked VU/ACC/Q words retain the
previously documented scalar-QMTC2 boundary: only unused VF2.ZW implicit CPU
upper-half scratch is excluded on paths that actually execute that colour code.
Other lanes and rows without that path remain checked.

Six colour-fill addresses `001A5D00` through `001A5D14` are independently dead:
`LHU` at `001A5CE0` sets S0 to `0..65535`, and the immediately following `BLTZ`
reads that same register. The [interface specification](magatuhi-creation-interfaces.json)
retains the original words and proof. This does not reclassify the earlier six
unvisited negative-count gradient instructions, which remain an explicit gap.

For sequences ending in a void destructor, the defined root return is compared
against its own captured chain value. The final void call's incidental V0 is
excluded; every call, call count, RAM and processor/operand check still runs.
The 416 root returns and 416 final void values are separately recorded.

[Affected regressions](magatuhi-creation-regressions.json) pass 21,968 existing
billboard, motion, retail, Magatuhi-release and recursive-effect cases on the
same rebuilt host. Current source, verifier, input, DLL and capture pins agree.
[All fourteen saved interfaces](magatuhi-creation-abi.json) pass after reopening;
all fourteen corrected decompilations were exported and merged.

The generic copier's canonical body retains the complete original unchecked
table selection. Host comparisons execute its real Magatuhi and part/PCP
callbacks, kinds three and four. Polygon kinds zero through two retain pending
actual callbacks and abort in the host adapter rather than provide fake results.
Their source recovery remains required before the full model-effect composite.

## Shared-engine transfer and next work

[Complete-span static comparison](magatuhi-creation-transfer.json) resolves six
DDS bodies: shared value allocation `00189220`, history owner `001890D8`, colour
fill `00189BA8`, particle copy `0018CD50`, generic copy `0014FEB0` and model
resource copy `00219E68`. Eight call links are checked. Across the complete
116-byte generic copier, only the allocator JAL at offset20 and indexed-table
LUI/LW address immediates at offsets68/76 differ. The previously checked generic
delete establishes the table bases; the independently complete kind-three copy
confirms the corresponding copy column. This resolves the incoming model
wrapper's two candidates without carrying the billboard identity into generic
copying. The five particle constructors, slot reset, math allocator and outer
factory have no full-span candidate. Community names and compatible layouts do
not justify treating those as exact matches or DDS execution.

The expanded [motion-effect frontier](model-motion-effect-frontier.json) has
65 pending recognized descendants /9,924 bytes, with no missing exports among
the inspected roots. The direct hit-effect graph remains thirteen pending
bodies /2,036 bytes; the part/PCP prefixes have 292 pending bodies /48,232 bytes
and seven missing exports. These graphs overlap and must not be summed.

Continue the actual common/special polygon copy constructors and their shared
initializer, then effect-record creation, unlink/free and motion change at
`001DD440`. Bounded returning counts and valid owned allocations are compared;
negative/overflow counts, malformed ownership and aliases, exhaustion, asset
selection, physical PS2/GS scheduling/rendering, full processor timing/flags and
a matching executable remain unproved. Whole-program recovery is incomplete.
One rolling capture was used; no checkpoints or backup copies were created.

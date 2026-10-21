# Complete original mesh renderer

`002B9178` is recovered as `ps2RenderMesh` and integrated into the main library.
Its 160 fresh original-instruction comparisons cover all 510 main addresses,
including type7, type8, CPU weighted, shape and packed paths. The comparison
executes every real dependency, including the original 177-pair VU producer,
packet construction, both material/auxiliary passes and finalization.

There are 100 producer batches and 104 nonzero packet results. All declared
RAM, vector registers, ACC/overflow/Q, clip history, FCSR, Status, raw64 results,
5,120 CPU upper words and 8,960 meaningful private-frame words agree. Callee
saves and the stack pointer are checked by the original capture. Two controlled
negative-base cases exercise the unusual first weighted point loop without
adding a guard or replacing its result.

Fourteen affected families add 28,194 passing retained cases on the rebuilt
library. The broad 413-function comparison also passes all 462,684 existing
original-instruction vectors. That comparison reuses the retained compressed
capture; it is not a new whole-program instruction capture. No checkpoints,
project copies or frozen source trees were created.

## Interface and routing

The renderer takes six raw64 integer arguments in A0/A1/A2/A3/T0/T1 and two
float words in F12/F13. They represent model, mesh, mask, colour, frame, reverse
winding and two lighting biases. V0 is the finalizer's raw64 result; invalid
shape header/selector paths return zero without dispatching or finalizing a
packet. The mixed interface was applied, checked after reopening Ghidra and
exported in place.

The original 320-byte frame carries a render context. Mesh kinds 7 and 8 take
priority over the CPU paths. Otherwise the unmasked high flag halfword chooses
weighted `800`, shape `1000`, or packed handling. Low effective flags separately
control clipping/UV and packet passes. Keeping those two flag domains separate
prevents a mask from silently disabling source layout selection.

Type7 copies view/light matrices, seven quads per selected bone, UV material
pairs and lighting vectors into VU memory before DMA. Type8 composes the object
matrix and normal basis before preparing the same producer. The paths use
different GPRs for their lighting copies: type7 uses V0/V1/V0; type8 uses V0 for
all three. The full comparison caught and corrected that difference when no
triangle emission overwrote V1 afterward.

## CPU paths and boundaries

The CPU weighted path advances past normals only when flag `80` is set. Its
first normal-bearing helper prefetches another position and packed normal even
on the final iteration; the accumulating helper requires a backed positive
count of at least two for an ordinary finite run. The point-only first helper
branches on its advancing output/control address rather than count. These
original behaviors remain intact; the controlled negative-base fixtures do
not establish that such inputs are authored retail meshes.

Shape selection uses high16(mesh+8) against the signed count at header+4. The
original executes exactly two delta pairs. It tests weight strictly above raw
`358637BD` (approximately one millionth), then only signed index < low16(mesh+8).
The selected block is `(index+1)*stride`. Negative indices and the last admitted
index are preserved, with explicit backing in the comparison; the latter can
select bytes after the authored block region. Equal-threshold and next-word
weights are also exercised. No stronger bound is added.

Native load/store order is retained for material and frame aliases: type8
reloads its material pointer for each LD/SQ, type7 caches it, type7 caches the
bone frame offset once, and the CPU weighted path reloads that offset per node.
The shape threshold is loaded once before both delta pairs. Helper CPU transport
now carries the real LQ/PCPYLD/QMFC2/packed-colour upper halves through the entire
renderer. The default host profiles retain their previous behavior.

## Community, Unity and DDS evidence

[DDS3 Model Studio](https://github.com/tge-was-taken/DDS3-Model-Studio/tree/92f350749ab24dcfd7c35b8fac105a5c1883d771/Source/DDS3ModelLibrary/Models/MeshTypes)
provides independently checked mesh layouts. Retail CPU examples are pinned
from `model/event/e614/reiko.PB`: two weighted meshes each have 12 vertices,
16 triangles and two nodes; two packed meshes each have six vertices and four
triangles. The parser's high16 name `Material2Index` differs from the native
shape-selector use, so the native role is qualified rather than renamed as an
exact community identity.

[Megami-Decomps model research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfModel.c)
supplies additional context. The full DDS peer at `002E0820` has 50 constrained
callee/global relocation words; all other bytes agree. Twenty complete direct
dependency spans are independently checked. The shared SMT ledger records the
renderer context, flag domains, stream progression, shape rules and processor
boundaries. This is not live DDS validation. The inspected Unity VU wrappers
are return-only and do not supply this PS2 implementation.

## Limits and remaining work

The selected VIF profile assumes unmasked cycle1/1 and mode0. DMA readiness is
external finite input, and micro stages finish at E before macro reads. The
renderer transfer profile rejects unsupported ACC overflow instead of inventing
state. Concurrent EE/VU timing, cache coherence, physical VIF/GIF/VU1 execution,
actual full-renderer runtime equivalence and a matching executable remain
unproved.

The 2,372-byte contiguous span includes seven unowned zero words between
recognized basic blocks. They were not observed as main PCs and are excluded
from the 2,344-byte recognized-code credit. Ghidra's function extent is retained.

Continue the outer placement/update dispatcher at `002B1DB8` with its real model
and part callbacks. The type7 direct frontier now has 32 pending bodies totaling
11,800 bytes. The whole executable remains unfinished.

Evidence: [validation](model-renderer-validation.json),
[regressions](model-renderer-regressions.json),
[reopened interface](model-renderer-abi-check.json),
[independent leads](model-renderer-leads.json),
[extent review](model-renderer-extent.json) and
[current progress](recovery-progress.json).

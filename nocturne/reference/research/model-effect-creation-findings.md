# Original PIB effect attachment, motion changes and cleanup

Eight complete PS2 bodies /1,360 recognized bytes are integrated in
[model_effect_creation.c](../src/model_effect_creation.c). All 1,024 fresh
original-instruction comparisons pass, including 128 construction-to-cleanup
sequences. Eight saved interfaces independently reopen and export. The
inspected motion-effect dependency graph has no pending recognized bodies or
missing exports at its current boundaries. Whole-program recovery, real asset
associations and physical rendering/scheduling remain incomplete.

## Bodies and execution evidence

| Entry | Recovered behavior |
|---|---|
| `001DF670` | Resource/position lookup, actual T0 copy callback and attachment controller |
| `001DF770` | Thirteen-word model-track parameter record and actual child creation |
| `001DF848` | Cached-resource lookup, busy-byte gate and type-three controller |
| `001DF968` | Original five-kind PIB item dispatch |
| `001DFA00` | Original chunk/item traversal and effect generation |
| `001DFA78` | Type-specific object destruction followed by controller-node release |
| `001DFB00` | Signed group matching and linked-list unlinking through actual destruction |
| `001DD440` | Motion search/create, real cut/blend change, old-group cleanup and new PIB generation |

[The comparison](model-effect-creation-validation.json) checks complete declared
RAM, defined ABI values, Status, callee saves, COP1 and defined VU/ACC/Q state.
It executes 777,298 original steps and 72,928 vector instructions. The run
includes 326 actual attachment-copy callbacks, 188 track parameter calls,
192 generic-copy callbacks, 100 colour callbacks, 189 recursive cleanup
callbacks and 128 motion factory/capture/bind callbacks. Actual kernel/CPU
trace words also agree. All 277 reachable main addresses execute; two remaining
addresses have pinned original branch/domain proofs.

The 128 connected cases release newly created attachments through the original
group unlinker. Independently checked list heads return to zero. Nonempty
motion books exercise actual model-visible node creation, capture and cut
binding. Other inputs exercise missing resources/positions/chunks, busy cached
resources, matched and missing motion groups, short versus extended copy items,
ordinary/special model tracks and controller types zero through three.

Another 21,568 [affected comparisons](model-effect-creation-regressions.json)
also pass on the current DLL. Their eight retained groups cover common/special copies, recursive
ownership, model cleanup, motion/controller/track creation and billboard
ownership. Earlier negative-count gradient addresses remain explicit; this is
not a fresh full-suite run.

## Research and original differences

[The reference review](model-effect-creation-matches.json) incorporates six
named Unity roles and five community files at revision
`bec33411543cdc487bad9debdf758f0090a2242c`.
[Motion API definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/mdl_motion_api.h),
[motion bindings](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_motion_bindings.h)
and [motion source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfMotion.c)
inform controller/book/cut and callback terminology.
[Track research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/effModelTrackPoly.c)
and [source-unit notes](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md)
supply shared ownership and engine context. Original Nocturne instructions and
actual consumers determine the recovered fields and ordering.

Unity's `mdlCreateEffect_IPU` aliases an empty body, so it supplies no algorithm
for `001DF848`. The actual dependency `002AC0D8` searches a resource list;
it is not an IPU constructor. The native path sets a busy byte and publishes
a type-three node only after successful lookups. Unlinking frees that node
without silently clearing the resource byte. Native generation returns void;
the managed Boolean status is not imported. The native unlinker also retains
its descriptive name rather than inheriting an empty stop-effect implementation.

The model-track child copies an original unassigned private word. A preceding
controller allocation passes type two; its allocator saves S0=2 with an SD,
placing high32 zero at the child's later private offset. The host derives zero
from these independently checked input/store instructions. No captured game
result supplies padding, callback returns or resource outcomes.

The original controller type is loaded with LHU. Reaching `001DFAA8` would
require type!=1, type<2 and type!=0, an empty 65,536-value domain. The null
fallback at `001DD4B4` is also unreachable: the earlier BEQL routes null
directly to creation; a matching path annuls the only intervening A0 reload,
leaving A0 nonnull for the later BNEL. Exact original words are pinned.

## Integration findings and transfer limits

The connected runs exposed fixture issues that creation-only comparisons
could not: overlapping resource-global declarations, malformed item stride/
sentinel placement, shared unowned billboards and uninitialized deferred queue
headers. These were corrected as independent inputs. Plain copies now use the
actual cache-clone ownership route, and releases append to independently
declared empty material/texture queues. Neither native outputs nor substitute
game dependencies are used to make those paths pass.

[All eight complete DDS spans](model-effect-creation-transfer.json) resolve,
with twenty agreeing call/callback constraints. Native branch geometry,
field offsets and allocation classes remain fixed. Static correspondence does
not establish DDS execution or a matching executable.

The [current frontier](model-motion-effect-frontier.json) is closed only for its
inspected roots and original callback prefixes. Retail model/root/position/
resource and PIB associations, other indirect tables, actual update/render
scheduling, raw noncanonical IDs, zero-count copy loops, malformed/alias/OOM
states and complete hardware flags/timing remain unproved. Continue original
asset associations and connected transitions, then expand the broader recovery
frontiers. Work stays in place with rolling captures and no checkpoints.

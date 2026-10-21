# Native model draw commands and full construction

Thirteen complete original bodies are integrated in `src/model_draw_commands.c`:

| PS2 entry | Recovered interface | DDS counterpart |
| --- | --- | --- |
| `002B0438` | `ps2ModelEnsureWorkspace` | `002D78B8` |
| `002B0470` | `ps2ModelFreeCommandLists` | `002D78F0` |
| `002B09B8` | `ps2ModelWriteReturnPacket` | `002D7E38` |
| `002B09D0` | `ps2ModelWriteIndexedAssetPacket` | `002D7E50` |
| `002B0A00` | `ps2ModelMeasureCommandList` | `002D7E80` |
| `002B0AC0` | `ps2ModelBuildIndexedPayload` | `002D7F40` |
| `002B0B30` | `ps2ModelBuildNodeRefsPayload` | `002D7FB0` |
| `002B0F08` | `ps2ModelPrependCommandNode` | `002D8388` |
| `002B0F78` | `ps2ModelBuildCommandList` | `002D83F8` |
| `002B1260` | `ps2ModelNodeSetCommands` | `002D86E0` |
| `002B1380` | `ps2ModelResetCommands` | `002D8800` |
| `002B1588` | `ps2ModelMake` | `002D8A08` |
| `002B9AC0` | `ps2ModelEnsureReferencedWorkspaces` | `002E1168` |

The full builder now runs the real root/material/node construction, then applies
pose and command setup to each eighty-byte item. Item mode zero supplies three
inline command-list pointers at `+44/+48/+4C`; mode one supplies a null-terminated
pointer table at `+44`. Both forms run twice, for the two buffered passes. The
table pointer is reloaded between passes as in the original instructions.

Command headers combine a low-halfword count with an optional high-halfword
selector. Measuring kinds one/two reserves packet bytes; kind three increments
an incoming count word; kinds four through eight contribute separate command
space. The builder executes the original kind-specific paths, creates real
memory-handle packet allocations and chip-sized nodes, and prepends them in
native order. Allocated headers contain next `+0`, kind `+4`, selector `+5`,
quadword count `+6`, payload `+8`, and owning handle `+C`. Freeing follows both
lists and releases the actual allocation type, retaining the original head
words rather than clearing them.

Indexed payloads write the real material/asset reference header and masked
28-bit address. Kind two also looks up each referenced node, ensures its
256-byte lighting workspace, and writes the per-frame DMA/VIF references,
counter payload and final asset reference. Partial halfword and control-byte
writes preserve the remaining dirty bytes. Its reference loop executes at
least once, so the selected valid inputs have positive counts. Kinds five/seven
can ensure additional workspaces through the original `800` flag and halfword
index array.

## Incoming private count and connected execution

The original measure adds to its first output word for a nonnull command list.
The builder does not initialize that word. During item setup, it overlaps the
preceding Euler routine's saved F21: item-set frame `40` plus base-set frame
`20` plus Euler frame `60`, with the F21 spill at Euler `+20`, reaches parent
SP minus `A0`. The later command-builder frame reaches the same address. Later
measures reuse the word; a null list resets it. Full construction adds its own
outer frame to both paths without changing this overlap.

Tests explicitly declare incoming F21 and standalone builder/reset private
words before original execution. The host adapter transports those inputs and
prior measured counts. All **1,477 actual original count reads** agree with
that independent transport. Original stack observations are comparison
evidence, not values fed back into the recovered code. Reset tests start with
empty list heads; free tests separately release lists produced by actual pool
and handle allocation preludes. More combined reset/frame histories remain
unverified.

Eighty nonempty full-model cases continue directly to transform evaluation.
Both executions bind evaluation's model argument to their own actual preceding
return. No expected model address or captured return is supplied as an input.
These connected cases exercise original constructed hierarchy, allocated
workspaces and lighting packets, including **180 CPU reciprocal square roots**.

## References and transfer

[Two Unity control roles and five community files](model-draw-commands-matches.json)
are reviewed with inspected revisions and hashes. The Unity item setter retains
the three-slot/two-pass structure, and its model builder loops through items.
The HD bodies add managed/archive behavior and do not supply the original DMA
implementation.

Pinned community [model code](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfModel.c)
and [item definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_model.h)
guide command kinds, size measurement and item setup. Original Nocturne
instructions decide execution and write order. Reviewed
[draw-node definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_draw.h),
[asset references](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_asset_packets.h)
and [DMA tag fields](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_dma_tag.h)
provide additional structure context.

[All thirteen complete DDS spans](model-draw-commands-transfer.json) resolve
with 28 agreeing direct-call constraints. Nocturne kind tables at `00549550`
and `00549570` correspond to DDS `003B44D0` and `003B44F0`. All sixteen targets
retain the same offsets inside the matched measuring/building routines; these
data bytes independently constrain the relocated table references. No DDS
execution is claimed.

## Validation and remaining work

[864 comparisons](model-draw-commands-validation.json) pass, reaching all **474
main instruction addresses** over 710,045 original steps and 25,992 vector
instructions. There are 105 real allocation/list preludes, 80 full-construction
continuations, and 7,072 other COP1 arithmetic comparisons. Declared RAM,
defined returns, Status, COP1, defined VU/ACC/Q and allocator primitives agree;
no uninitialized reads are reported. The existing scalar QMT check excludes
only implicit VF2 Z/W scratch lanes, while written RAM and lighting packet W
lanes remain checked. Arithmetic agreement uses the existing pinned result
model, not independent physical flags/timing evidence.

The thirteen Ghidra interfaces are saved and independently reopened, and
exports are merged. [6,630 affected regression cases](model-draw-commands-regressions.json)
pass on the same rebuilt host using retained pose, root, cleanup and D3P
captures. Recognized body credit is **2,236 bytes**; compared contiguous spans
total **2,268 bytes**. No new full-suite run is claimed.

Recovery is **1,935 /8,986 functions (21.533%)**, **326,995 focused cases**,
**789,679 aggregate cases**, and **146 reports**. The expanded bootstrap,
including command reset, now uses the same full-plus-focused membership as the
whole recovery audit: **60 pending bodies /7,280 bytes**, zero missing exports.
Earlier frontier versions excluded the historical full report and overstated
pending support bodies already recovered there; this correction adds no
function credit. Continue texture-list cloning `002B2BD0`, outer model bootstrap,
remaining model/PCP part constructors and unchanged retail relocation/execution.
Malformed counts/indices, exhaustion, combined reset histories, complete retail
lifecycle, physical DMA/rendering and a matching executable remain unproved.
Rolling outputs are saved in place without checkpoints or backup copies.

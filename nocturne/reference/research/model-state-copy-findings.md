# Complete parent-to-child model-state copy

`002B2268` is recovered as `ps2ModelCopyState` in
[model_state_copy.c](../src/model_state_copy.c): 612 recognized code bytes in a
616-byte contiguous span. Zero padding at `002B2474` is unowned and excluded
from recovery credit. The terminal return and its delay instruction are included.

The integrated host passes 528 fresh original-instruction cases. They execute
the actual material/list copy, option-buffer copy, native memcpy, getters and
pool allocation, with no supplied game outputs. All 143 non-delay instruction
addresses are reached; the other ten recognized addresses are branch/return
delay slots executed by the instruction provider. The padding is never reached.
All declared RAM, all 32 VF registers, ACC/overflow/Q/clip state, FCSR, interrupt
Status, primitive counts and all 32 GPR upper halves compare. Original callee-save
checks run during capture; this does not certify every incidental low GPR/FPR
value in the recovered C host.

## Original ordering and layout

The actual material-list copy runs before the root reloads its option-list pair.
The option-buffer copy then runs before any root flags or matrix fields are read.
The destination flag byte at `+19` is stored before the source mask at `+1A` and
colour at `+1C` are loaded. Those two fields are loaded before their stores.
Four VF rows snapshot the root matrix at `+20` before any destination row is
written. Root quads at `+60` and `+70` are copied in sequence, so the second load
can observe the first store.

The frame byte at `00551842` is signed. Source fields `+80/+88` are loaded and
the destination container at `+0` is cached, then those two fields are stored.
The source container at `+0` is loaded **after** those stores. Source `+84/+8C`
are loaded and the destination container's signed count at `+4` is cached before
their stores. Both array bases at container `+C` are loaded afterward, including
for nonpositive counts. Count and bases stay cached throughout the loop.

Each iteration loads the source node slot, then the destination node slot.
Node flags at `+14` and colour at `+1C` are loaded before either store; the mask
at source `+16` is read afterward. Quads `+50/+60/+70` copy sequentially. Local
matrix `+80` snapshots all four rows before storing, followed by a fresh snapshot
of world matrix `+C0`. An earlier local-matrix store can therefore change a
later world-matrix load. Final VF28..31 hold that last source world snapshot,
or the root matrix when the destination node count is nonpositive.

The destination workspace pointer at node `+30` is read after those matrix
copies. Zero skips the source workspace read. Otherwise both pointers add the
signed frame times 128, and the original aligned/unaligned paths copy **four
32-byte snapshots**. Each snapshot loads four 64-bit words before storing them;
later snapshots see earlier stores under forward overlap. This is not a whole
128-byte snapshot or memmove. Later node-array entries remain live after these
writes, even if a workspace aliases an array or its container header.

Root field `+94` is not directly copied. The child's existing `1000.0f` value
remains intact in these fixtures. Other deliberately aliased buffers can still
change retained fields indirectly; this is not a universal no-write guarantee.

## Processor transport

Native memcpy's aligned loop writes V1 and V0 as full quads. The host diagnostic
reads the last 32-byte block **actually written by recovered memcpy**, immediately
after that call, to retain those upper halves. The later eight-byte tail starts
beyond this block. This observation neither supplies copied output nor changes
RAM. The root's later quad loads replace V0 upper halves; V1 can retain memcpy's
last first-quad upper words. Scalar/64-bit operations retain other upper halves.
The pool/getter closure has no additional full-quad clobber.

This diagnostic is qualified to linear ordinary RAM and excludes private frame
aliases: a native callee's saved-register stores could otherwise change a header
after the observer's cache point. Busy VU timelines, volatile/MMIO accesses,
aligned surrounding reads/writes for unaligned transfer faults and physical
hardware timing are not modeled.

## Community and Unity evidence

The [independent audit](model-state-copy-leads.json) rechecks the complete root,
seven dependency spans, pinned community/processor sources and three Unity
exports. DDS `002D9748` differs only at two JAL words and the frame's GP offset.
ELF REGINFO resolves Nocturne GP `00554170` /frame `00551842`, versus DDS GP
`003C0CF0` /frame `003BD2EA`. Callee behavior remains separately qualified.

[Community SdfModel/SdfDrawNode definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_draw.h)
corroborate the model/node layout. Community `sdfModelCopyData` names the small
option-buffer copy, rather than this full state copy. Unity `ModelCopy.GetCopy`
and `mdlLinkBlur` corroborate child/trail snapshots, but clone GameObjects and
managed children. They do not supply this native field-copy algorithm.

The final 208 alias cases include root/node self copies, aligned overlapping root
and node views, workspace forward/backward overlap, a root store changing the
source container, cached header mutation and live next-node slots. A 128-byte
write to the destination array also covers the nearby source array: both sets
of replacement pointers are explicitly backed. The complete write is retained.

Current compiled proof is in [model-state-copy-validation.json](model-state-copy-validation.json).
Reopened raw64/void Ghidra interfaces, current exports,13,369 affected comparisons
and all413 baseline functions/462,684 retained cases pass on the final DLL.
Renderer160 andouter201 originalcaptures were refreshed for the extended capture
profile. [Publication evidence](model-state-copy-publication.json) binds these checks. The whole executable and the context's child
population/anchor logic remain unfinished. No checkpoint or backup was created.

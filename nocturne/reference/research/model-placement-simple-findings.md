# Original reference-mesh placement

`002B1950`, now `ps2ModelPlaceReferenceMeshes`, is recovered as a complete
1,128-byte body with two raw64 arguments and a void return. Its 512 fresh
original-instruction cases reach all 248 measured addresses. Reopened Ghidra
interfaces and the current export pass. Another 17,152 affected retained cases
pass on the rebuilt host.

The routine updates the material list, filters model nodes, composes their
projection matrices, optionally rejects bounds, builds reference DMA packets,
and submits the resulting chains through the installed surface callbacks.
Validation executes the real recovered allocator, material, matrix, bounds,
lighting, chain-append and ordering bodies. No game output is supplied in place
of those dependencies. The four surfaces receive their real callbacks from
`002C8188`; submission reaches `002C7F88`.

The comparison checks full declared RAM, all 128 vector words, ACC, overflow and
Q, clip history, Status/FCSR, the defined 80-byte root-local prefix, and the
actual ordered callback arguments. It includes 1,395 surface submissions and
1,395 lighting packets, 70,144 VU/ACC/overflow/Q values, 40,960 private bytes and
4,576 clip-state observations. There are 32 aliases with the private group
table and 16 allocations that overwrite a matrix before the original reload.

The original allocates one chain per selected bucket before inspecting that
group's command list. An empty command list can therefore still submit a
header. Zero bucket selectors choose bucket 0 or 1 from the sign of the saved
packed colour; nonzero selectors use their raw high16 index. Four local bucket
words are cleared per processed node and after each callback. The source adds
no bucket clamp. Node matrix and root-array reloads remain in their original
positions, including the allocation overlap cases. Frame selection uses the
signed byte encoding; node iteration uses a live signed halfword count.

The first diagnostic trace read A0 before the JALR delay slot and consequently
recorded the surface table. The original delay slot moves V1, the actual
surface, into A0. The corrected observation reads that V1 value at the pinned
call site; a fresh capture then agrees with the source callback trace.

## Community context and transfer

[The attributed lead report](model-placement-simple-leads.json) checks the
entire Nocturne body against DDS `002D8DD0`: every changed word is one of seven
decoded GP offsets, two words constructing the projection-matrix address, or
ten constrained call relocations. Fourteen root/dependency spans are reviewed.
This establishes a strong transferable placement pattern, while the separately
documented DDS material base-copy branch remains a game-specific difference.

The report pins [Megami-Decomps DDS research](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c)
and [DDS3 Model Studio layouts](https://github.com/tge-was-taken/DDS3-Model-Studio/tree/92f350749ab24dcfd7c35b8fac105a5c1883d771).
Their model, material and reference-packet definitions guide field roles and
fixtures; original Nocturne instructions decide the behavior. Calling the
packed colour sign an alpha classification remains an inference. No complete
Unity placement implementation is claimed for this PS2 packet path.

The full `002B9178` renderer, its remaining packet/DMA consumers, placement
`002B1DB8`, and the outer context/update path remain pending. These constructed
cases do not establish arbitrary malformed selectors, additional callbacks,
DMA execution, rendered appearance, timing, or physical PS2 behavior. Work is
saved in place without checkpoints, savestates or backup copies.

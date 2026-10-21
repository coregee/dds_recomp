# Weighted slot and mesh packet consumer

The complete 600-byte body at `002B0CB0` is recovered as
`ps2ModelAppendWeightedMeshPackets` in `src/model_packet_list.c`. Its raw64
four-argument/void interface is saved in the working project, checked after
reopening, and present in the current whole-program export. The inspected caller
at `002B2114` ignores its incidental return.

The node's +10 backlink selects a model. Model+10 supplies a slot-list record,
whose +C pointer holds two index/weight pairs per 16-byte slot. The low16 bits
of command+4 select the slot; the high16 select the material. Each weight passes
the actual original COP1 `threshold < weight` comparison against raw `358637BD`
at `0054E744`, approximately 1e-6. Selection preserves pair order and copies
complete eight-byte pairs, including original private-frame overlap behavior.

The original allocator reserves `64 + (selected + 1) * 16 * descriptorCount`
bytes. The model backlink is reloaded after allocation. That read is observable
when the node's +10 word aliases the mutable allocation cursor; a cached pointer
would produce different behavior.

The real indexed-material helper writes its partial 16-byte reference header.
The consumer follows it with a 32-byte weight/VIF packet. For every descriptor it
then emits the selected target references, in pair order, followed by the base
reference. Address masking, unsigned halfword QWC loads, zero upper doublewords,
live descriptor reads and the final 16-byte terminator preserve native order.
The actual chain append links the new range through head+4/tail+8 and converts
an existing tail to a NEXT tag.

Descriptor count is an unsigned halfword and the outer loop enters unconditionally.
Zero is therefore not an empty-list no-op. The recovered source retains the
wrapping equality exit, while validation uses backed positive counts 1..4.

[Validation](model-packet-list-validation.json) passes 512 original cases and
all 137 measured main instruction addresses. There are 255/199/58 cases selecting
zero/one/two slots, 315 final defined private pairs, 776 independent scalar
oracles, 16 private-copy overlaps and 32 cursor/model-reload overlaps. The cases
execute 632 consumer calls, including 120 consecutive two-stream sequences,
2,582 mesh references and 124 actual material-update preludes. Complete declared
ordinary RAM, Status and modeled FCSR condition compare. Only assigned private
pairs are compared; unassigned stack/callee-save bytes and incidental void returns
are excluded. The capture helper's new private-frame input/output fields are
restricted to this entry and explicitly enabled by this specification.

[Affected regressions](model-packet-list-regressions.json) pass 9,312 retained
original cases on the rebuilt host: command construction, material/UV updates,
ordering and draw prerequisites. No full-suite recapture or backups were created.

[Community/Unity and peer evidence](model-packet-list-leads.json) attributes the
pinned Megami-Decomps definitions for two-slot entries, model/resource ownership
and material-reference DMA headers. These records guide nonempty fixtures, while
the command selector/count/descriptor route remains instruction-derived. The HD
`sdfModelMakeMorphList` candidate shares a return-only export and supplies no
complete native packet implementation.

The consumer's complete DDS peer at `002D8130`, and four complete dependency
spans, match with only independently decoded call and GP relocations. Original
threshold bytes match; the allocator cursor is identified as mutable state,
not a constant. Whole model placement, VU/DMA execution, rendered appearance,
context children and spawn-once update remain pending.

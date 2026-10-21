# Original model and material parameter copies

The complete bodies at `002B2238`, `002B3AB0` and `002B39A0` are recovered in
[model_copy_helpers.c](../src/model_copy_helpers.c): 48, 112 and 272 bytes,
respectively. The integrated host passes 864 fresh original-instruction cases
(288 per routine), covering all 95 main instruction addresses. Actual native
memcpy, lazy material getters, pool allocation and interrupt primitives execute
in the original comparison; no game output is supplied by a callback fixture.
Ghidra's reopened interfaces use two raw 64-bit arguments and void returns.

## Behavior and ordering

`ps2ModelCopyOptionBuffer` checks the entire raw destination argument for zero.
Its signed destination halfword at `+4` controls the copy; nonpositive counts
avoid reading the source buffer. Positive counts copy `count * 16` bytes through
the original forward memcpy, with both `+C` buffer pointers loaded first. The
source count is irrelevant. Forward overlap is retained, rather than converted
to a whole-buffer snapshot.

`ps2MaterialCopyListParameters` caches the signed destination count and both
array bases at `+C`, including when the count is nonpositive. Each iteration
reads the destination slot and source slot anew before the actual material copy.
An earlier copy can therefore change a later slot, but changing a header count
or array base does not change the cached traversal.

`ps2MaterialCopyParameters` writes dirty byte `+6 = FF` first. It preserves the
original interleaving of scalar loads and stores, including raw COP1 words.
The source primary pointer at `+38` is cached before later header stores. A
nonnull pointer invokes the actual lazy destination getter, then loads all three
64-bit words of its 24-byte payload before any payload store. Allocation can
publish a destination pointer that aliases the source payload before that
snapshot. The secondary pointer at source `+3C` is read **after** the first
getter/copy, so the first copy can change which secondary payload is used.
Finally source `+40` is loaded and stored before source `+44` is read.

The native payload copy is **24 bytes**. The getter's initializer fills only
20 bytes; its sixth word is opaque and remains unchanged until copied. Neither
the five-field vocabulary nor a managed HD object justifies shortening the copy.
The draw pointer at `+8` and unrelated material fields are not copied by this
routine.

## Evidence and transfer to DDS

The [independent audit](model-copy-helpers-leads.json) checks seven complete
native/DDS spans, seven pinned primary/community source texts, and three Unity
exports. The three DDS roots at `002D9718`, `002DB158` and `002DB048` differ
from these Nocturne roots only in four JAL instruction words. Native memcpy
`002D43A4` and DDS `002FFFEC` agree over their complete 176-byte bodies.
Callee behavior and allocation still require their own evidence.

The pinned [community sdfModel.c](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfModel.c#L404)
names the small copy `sdfModelCopyData`. That name refers to `002B2238`, not
the full parent/child state copy at `002B2268`. Community `SdfAsset` and
`SdfSubParam` definitions and symbol names help establish the material role;
the inspected source units do not provide complete community C for both asset
copy bodies. Original instructions remain the algorithm reference.

Inspected Unity `sdfMatNew`/`sdfMatSet` exports supply material and dirty-state
vocabulary. Their managed constructors are not exact native copy bodies; the
shared return-only export adds no copy algorithm. This batch is recorded as
PS2-only recovery with a qualified shared SMT signature.

## Validation scope

The [current comparison](model-copy-helpers-validation.json) checks all declared
ordinary RAM, interrupt Status, FCSR condition, primitive counts and complete
main instruction coverage. Cases include raw upper argument bits, signed empty
counts, self/forward overlap, unaligned 24-byte payloads, lazy allocation and
reuse, header/payload overlap, changing later list slots and cached-list headers.
The independent audit's 768-case observation is historical; the final capture
and integrated comparison contain 864 cases.

[Affected regressions](model-copy-helpers-regressions.json) identify the current
DLL and exact retained captures replayed. The previous 413-function/462,684-case
full baseline is historical; it was not rerun for this small guarded addition.
Publication is recorded separately in
[model-copy-helpers-publication.json](model-copy-helpers-publication.json),
without modifying the audit pinned by the comparison.

These checks do not establish arbitrary malformed pointers, MMIO/access faults,
CPU upper-register transport across memcpy, timing/cache behavior or physical
hardware execution. Full parent/child copy `002B2268` was the next unfinished
caller at this milestone. Its subsequent [complete recovery](model-state-copy-findings.md)
checks the ordered root/node matrices, signed frame, native 128-byte workspace
copy and CPU/VU state transport through these actual dependencies. Context child
population and connected state handoff remain unfinished. Work proceeds in place
without checkpoints or backups.

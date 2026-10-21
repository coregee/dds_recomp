# Triangle clipping and two-pass packet construction

Four complete original PS2 bodies are compiled and compared: `002B7498`
(`ps2RenderBuildDeferredTriangles`), `002B7A80`
(`ps2RenderBuildFrontTriangles`), `002B8068`
(`ps2RenderBuildBackTriangles`) and `002B8E98` (`ps2RenderBuildPacket`).
They add 4,576 recognized instruction bytes; the full contiguous spans total
4,624 bytes. The distinction includes original gaps/delay words and does not
add recognition credit. Source is in `src/model_render_clipping.c`.

The [fresh comparison](model-render-clipping-validation.json) passes 2,048
cases and all 1,000 measured non-delay addresses. Original delay operations
also execute in the capture. It compares full declared RAM, all 128 VU lanes,
ACC/overflow/Q, clip history, FCSR, Status, seven CPU upper halves and defined
private words. Totals include 280,576 vector/ACC/overflow/Q values, 28,672 CPU
upper words and 9,216 private words; untouched stack bytes and callee-save
spills are not source outputs. The dispatcher saves its three VU rows only
on its two-sided branch, so those private words are compared on that branch.

There are 8,126 independent topology/link/source-pointer checks, 306 backed
overlaps and 78 aliases between the initial tail-link destination and pool
capacity. All original dependencies execute: clipped-edge interpolation,
UV/colour interpolation, lighting, buffer configuration and all emission
passes. The full nonempty two-sided dispatcher runs with these real callees.
The [affected regression report](model-render-clipping-regressions.json)
records 25,344 passing retained cases on the current DLL. Four raw64 interfaces
were applied in place, independently reopened and checked, then exported into
the current 9,059-entry inventory. No checkpoints or project copies were made.

## Original behavior

All three selectors use 96-byte records: position at `+00`, normal at `+10`,
colour at `+20`, UV at `+30`, generated-record link at `+40`, directed edge
source pointers at `+44/+48`, Q at `+4C`, axis classification at `+50` and
clip mask at `+51`. Input indices are unsigned 16-bit triples. Input and
output triangle counts are signed 16-bit context fields `+40/+50`; `+52`
holds the deferred count. The output pointer-triple table is `00581030` and
the deferred ordinal list is `0058D030`.

The first two selectors reject a shared clipping plane with mask `3F` and
any Z clipping with mask `30`. Their native VU cross/dot sequence, scalar
multiply by context `+AC` and COP1 comparison decide winding. The deferred
prepass records negative-winding ordinals; the front selector omits them.
The back selector trusts the ordinal list and performs neither rejection
nor winding calculation.

Equal classifications, or the cached global override at `0055189C`, emit
the original triangle. Otherwise cyclic rotation selects the original
split branch. A zero-versus-repeated-side classification produces three
triangles and two edge records. Opposite nonzero sides or all three distinct
classifications produce five triangles and four edge records. The exact
ordered tuples and directed edges appear in the
[independent lead report](model-render-clipping-leads.json). Classification
bytes outside ordinary 0/1/2 can make the original rotation loop nonterminating;
the recovered source retains that loop.

The allocator reads the next capacity before storing the preceding link.
Intermediate records write the link before updating the tail slot; the final
record updates the tail slot first. Capacity is decremented and stored before
loading the next record cursor. These native orders are preserved, including
the transition to context `+6C/+74`. Opposite nonzero classifications allocate
and interpolate the first pair, write the first triangle, then allocate and
interpolate the reverse pair. All-distinct classifications allocate all four
records before interpolation. The front selector retains allocations and
links from its deferred prepass, then builds the front output table again.

`VADDZ.X` during selector setup uses VF2.Z carried in a CPU register's upper
64 bits through `MFC1/QMTC2`. It does not use the scalar F0 lane. The front
selector transports V0; the back selector transports A0. The new observed
A0 boundary also required preserving the actual packed-colour expansion in
`002B6968` and `QMFC2 A0,VF2` in `002B7370`. Existing emission/packet source
now exposes those processor transports; retained profiles that do not observe
A0 keep their prior comparison scope. All affected comparisons pass.

The dispatcher gets the real work cursor, rounds to 64 bytes, puts the header
at aligned `+30`, and forms payload `((aligned+40)&0FFFFFFF)|30000000`.
It writes context `+80/+84/+8C/+88` in original order. With flag `4000` it
saves VF24..26, builds/emits the front pass, reconfigures buffers, restores
those rows, relights original records, then builds/emits the deferred pass.
Otherwise it builds/emits the front pass alone. Finalization remains the
separate recovered `002B8F70` body.

## Community and SMT transfer

The lead report pins source URLs and revisions from
[Megami-Decomps/dds-decomp](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c),
[DDS3 Model Studio](https://github.com/tge-was-taken/DDS3-Model-Studio/tree/92f350749ab24dcfd7c35b8fac105a5c1883d771)
and [PCSX2](https://github.com/PCSX2/pcsx2/tree/b4d6e2aa7b9069162fa0e7cbc45ae95fc2566f39).
They supply model/mesh context, symbol candidates and independent processor
semantics. Unity is useful for model vocabulary; it does not establish these
PS2 pool, clipping or packet algorithms.

Every word in four DDS root spans and five dependency spans is checked.
The root mapping is Nocturne `2B7498/7A80/8068/8E98` to DDS
`2DEB40/DF128/DF710/E0540`. Every differing word is a constrained global or
call relocation. The triple and deferred tables map to DDS `3EB860/3F7860`.
The record fields, ordered split topology, prepass behavior and two-pass
dispatch enter `shared-smt-signatures.tsv` with these qualifications.
Zero initial file values and nearby address spacing do not establish runtime
contents or semantic capacity.

## Remaining work

The tested tagged payload view has separate backing from the low physical
view. These comparisons do not prove physical cache-alias coherence, DMA
completion, VIF/GIF execution, VU pipeline timing or rendering on a PS2.
Invalid counts, cyclic links and nonterminating classifications are outside
the finite fixture domain; the source retains the original unchecked behavior.

The current audit records 2,246/9,059 functions (24.793%) and 322,796 recognized
integrated bytes. Type7 has 34 pending direct bodies /14,448 bytes. Full
renderer `002B9178` now has one pending direct helper: DMA/VU consumer
`002B9048`. Recover its original hardware boundaries and uploaded program
inputs, then complete the renderer, placement `002B1DB8` and outer context/update.
The whole executable goal remains unfinished.

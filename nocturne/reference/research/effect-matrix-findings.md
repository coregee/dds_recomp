# Native effect matrix consumers

Thirteen complete source bodies /760 recognized bytes are integrated in
[`effect_matrix.c`](../src/effect_matrix.c). They pass 2,048 comparisons against
unchanged `SLUS_209.11` instructions. Saved Ghidra interfaces were reopened and
checked; all thirteen current exports are merged. This recovers prerequisites
for the remaining composite PCP constructors, without crediting those
constructors or claiming whole-program recovery.

| PS2 address | Recovered role |
| --- | --- |
| `002B6550` | VU matrix composition |
| `00164F10` | Particle matrix composition and store |
| `00165590` | Exp-particle tail wrapper |
| `00169E90` | Special-polygon composition and store |
| `001A8D20` | Track matrix dispatch |
| `001A7728`, `001A7F78`, `001A88D0` | Track type 2/3/4 matrix stores |
| `00175B78` | Part matrix dispatch |
| `00175EB0` | Model-part three-row store |
| `00176160` | PCP matrix dispatch |
| `0015ACB8` | Major-effect matrix dispatch |
| `0015D7E8` | Material-billboard matrix store |

Original instructions determine the native implementation. Major/part/PCP
matrix slots are at table offset 24; track matrix slots are at offset 20, distinct
from colour 16 and scale 12. The major call is unconditional, while the other
dispatchers test the original callback pointer. Kind widths remain LW for
major/PCP/track and LHU for parts. Raw high matrix-argument bits are preserved
through callbacks; child LW arguments are sign-extended.

Every matrix consumer loads all four input rows into VF28..31 before stores.
Particle composition loads the object's source matrix at 100 and writes output
at B0; the special-polygon offsets are 70 and 20. Composition uses original
MULAx/MADDAy/MADDAz/MADDw ordering, retaining ACC overflow and temporary
VF2..4 writes. The final result goes directly to VF31 before the temporary
rows are copied into VF28..30. There is no host matrix approximation.

The model-part consumer stores only the first three rows at root 20/30/40.
It reloads context+18 between stores, which matters when the first store
overwrites that pointer. Eight such alias cases execute against the original
instructions. Material billboards store four rows at 40; track leaves store
four at 0. Another 256 cases exercise input/output or source-basis overlap.

Six named Unity methods were inspected: the part/model/PCP matrix setters,
particle/exp-particle setters and special-polygon setter. These establish
semantic roles, not byte/layout identity. HD has managed bounds/type/null
guards and Matrix4x4 storage; its model setter preserves translation through
row operations, while the PS2 setter writes only three native rows. HD's
exp-particle body also differs from the native tail wrapper. See
[the attributed match review](effect-matrix-matches.json).

Two community source files were reviewed at DDS decompilation revision
`bec33411543cdc487bad9debdf758f0090a2242c`:

- [`parManager.c`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/parManager.c)
  documents the particle matrixB0/source100 layout and actual VU composition.
- [`effManager.c`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/effManager.c)
  supplies independent context for type-table transform dispatch.

Reviewed terms, revision and fetched file hashes are retained in the match
review. Their definitions inform identities, native field interpretations
and matrix/alias validation; no upstream source was executed or adopted
wholesale. Original bytes still decide the target behavior.

[Static DDS comparison](effect-matrix-transfer.json) resolves all thirteen
complete counterparts with three direct-call constraints and 24 original
matrix-table slot constraints. Four dispatch wrappers differ only at two
individually checked table-address immediates, with every other word equal.
Three otherwise identical four-row copy leaves are resolved through independently
anchored incoming track slots. This establishes static transfer, not DDS
runtime execution or a matching rebuilt binary.

[Focused validation](effect-matrix-validation.json) compares full declared
RAM, Status, all 128 VU words, ACC 4/overflow 4 and Q: 280,576 vector-state values
and 30,547 original vector instructions. The unchanged original tables drive
353 callbacks, with 2,047 actual native function-entry observations checked.
There are 45,786 original execution steps. No game function is intercepted,
and no captured matrix result is supplied to recovered code.

Coverage reaches166/168 main addresses. PCP nonnull main addresses
`0017618C` and `00176194` remain explicitly unvisited, along with their
`00176190` delay instruction: all seven inspected unchanged original PCP
matrix slots are zero in both Nocturne and DDS. The nonnull branch remains
in source; this finite-domain fact does not establish global unreachability
or add native bounds. Every other selected main address executes.

[Targeted regressions](effect-matrix-regressions.json) add9,968 passing
retained cases on the same current DLL: model memory 496, libm 3,328 and
basic pose 6,144. Physical timing/rendering, exceptional flags beyond the
reviewed value model, the remaining PCP constructors, complete executable
reconstruction and matching-binary proof remain outstanding.

The current progress audit reports 2,042/8,992 integrated functions (22.709%),
300,300 recognized integrated bytes, 153 focused reports and 335,395 focused
/798,079 aggregate comparisons. Expanded original matrix and part-copy slots
make the model bootstrap frontier 25 pending bodies /5,120 bytes, without
missing exports. This corrects the earlier 24-body estimate, which omitted
indirect matrix/copy roots. Continue actual PCP constructors/gradients,
descriptor and initialization helpers, model/material clones and native
worker arrivals. Work remains in place with one rolling subsystem capture
and no checkpoints.

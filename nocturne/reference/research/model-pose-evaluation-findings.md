# Native model poses, recursive transforms and lighting packets

Eight complete original bodies are integrated in `src/model_pose_evaluation.c`:

| PS2 entry | Recovered interface | DDS counterpart |
| --- | --- | --- |
| `002B1180` | `sdfModelMakeLocalTm` | `002D8600` |
| `002B11D0` | `ps2ModelNodeBaseSet` | `002D8650` |
| `002B1610` | `sdfModelMakeEarly` | `002D8A90` |
| `002B16A0` | `sdfModelEvalNode` | `002D8B20` |
| `002B1780` | `sdfModelEvalTm2` | `002D8C00` |
| `002B17E8` | `sdfModelEvalTm` | `002D8C68` |
| `002B65A8` | `ps2ModelComposeVuMatrices` | `002DDC50` |
| `002BA910` | `ps2ModelWriteLightingPacket` | `002E1FF8` |

The base setter reads the eighty-byte model item: ID at `+8`, Euler rotation
at `+10/+14/+18`, translation at `+20`, scale at `+30`, and bounds pointer at
`+40`. It retains the source pointer at runtime node `+38`, builds the real
quaternion at `+50`, copies translation/scale to `+60/+70`, forces translation
W to one, builds the local matrix at `+80`, and stores bounds at node `+34`.
Unity's named base setter aliases an empty body; original instructions supply
this implementation.

Early construction calls the recovered root builder, sets root flag `400`
through byte `+19`, then applies the base setter to every item. Full construction
at `002B1588` and its draw-command setter `002B1260` remain pending; this alternate
builder does not establish their behavior.

Recursive evaluation scales all four lanes of each local basis row by the
corresponding node scale component, composes against the parent, and writes
the world matrix at node `+C0`. Optional node workspace `+30` selects a
128-byte packet with `workspace + (frame << 7)`. Child traversal follows the
original link at `+4`, reloading the parent's child head at `+C` after each
recursive call. Root evaluation scales XYZ components of the root basis while
preserving W, constructs its actual private matrix, and evaluates the first
node through root array `+0`, array data `+C`. It has no empty-array guard.
The current-frame wrapper sign-extends the byte at Nocturne RAM `00551842`.

The lighting packet retains the world matrix at `+0..3F`, writes normalized
basis vectors at `+40/+50/+60`, and installs words `04000010`, `14000000`, zero
and zero at `+70/+74/+78/+7C`. Column squared lengths feed one CPU reciprocal
square root for X and two VU reciprocal square roots for Y/Z. Original QMT
transport preserves the preceding QMFC2 upper doubleword; unwritten packet W
lanes retain their implicit incoming values. These lanes and ACC state are
checked rather than initialized to convenient defaults.

## Community references and transfer

[Five positive Unity bodies and four pinned community files](model-pose-evaluation-matches.json)
are reviewed with source hashes. Community
[model records](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_model.h),
[draw structures](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_draw.h)
and [lighting packet definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_vu_lighting.h)
corroborate fields and packet shape. The reviewed
[DDS model source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfModel.c)
names its traversal link `next`; Nocturne executes a load from `+4`, mapped as
previous in the recovered native hierarchy. Preserve the address mapping when
transferring the names. Source correspondence alone does not settle this naming
disagreement or replace the original traversal instruction.

[All eight complete DDS spans](model-pose-evaluation-transfer.json) resolve
with ten agreeing call constraints. The complete 32-byte current-frame wrapper
differs only in its GP load displacement and the known tail-jump target.
Original ELF REGINFO GP values constrain the globals: Nocturne GP `00554170`
loads frame `00551842`; DDS GP `003C0CF0` loads frame `003BD2EA`. Mutable frame
contents are inputs, not a fixed data equivalence proof. No DDS execution is
claimed.

## Validation and remaining work

[544 original-instruction comparisons](model-pose-evaluation-validation.json)
pass, reaching all 210 main instruction addresses over 336,432 original steps
and 41,570 vector instructions. Tests cover finite Euler poses, forced position
W, real early construction/material parsing, acyclic child rings, absent/present
lighting workspaces, signed frames including `-128/127`, zero scale, aliased
packet destinations, and preserved W lanes. All declared RAM, defined returns,
Status, COP1 and defined VU/ACC/Q values agree, with no uninitialized reads.
The comparisons include 379 actual COP1 reciprocal-square-root operations and
6,871 other COP1 arithmetic comparisons.

The CPU and VU arithmetic results use separate Java/C adaptations of pinned
arithmetic research already retained by the project. This validates agreement
with the captured result model; it is not independent physical PS2 evidence
for flags, timing or rendering. The added full-lane VU multiply/MAC and Q-add
handling preserves masked lanes and accumulator overflow behavior.

All eight interfaces are saved in Ghidra and independently reopened; current
exports are merged. [13,440 affected regression cases](model-pose-evaluation-regressions.json)
pass on the same rebuilt host using existing root creation, motion sampling,
basic pose and camera captures. Recognized body credit and compared full spans
both total 928 bytes. No new full-suite run is claimed.

Recovery is **1,922 / 8,986 functions (21.389%)**, with **326,131 focused cases**,
**788,815 aggregate cases**, and **145 reports**. Counts include historical
captures and repeated dependency comparisons. The expanded bootstrap frontier
includes full/early builders and current-frame evaluation, with **162 pending
bodies /24,180 bytes** and zero missing exports at its inspected boundaries.
Continue actual draw-command construction, resource arrays and remaining
model/PCP factories before unchanged retail MD/D3P construction and evaluation.
Constructor-to-evaluation sequences, invalid/cyclic inputs, exhaustion, extreme
floats, full lifecycle, physical runtime and a matching executable remain
unproved. Rolling outputs are retained without checkpoints or backup copies.

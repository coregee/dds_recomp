# Native model roots and hierarchy construction

Eight complete bodies are integrated in `src/model_root_creation.c`:

| PS2 entry | Recovered interface | DDS counterpart |
| --- | --- | --- |
| `002B03B0` | `sdfModelNodeNew` | `002D7830` |
| `002B0540` | `sdfModelRootNew` | `002D79C0`, allocation variant |
| `002B06D0` | `sdfModelAllocNodeList` | `002D7B50` |
| `002B0758` | `sdfModelNodeAdd` | `002D7BD8` |
| `002B07E8` | `sdfModelNodeUnlink` | `002D7C68` |
| `002B0850` | `sdfModelNodeSetParent` | `002D7CD0` |
| `002B1410` | `ps2ModelMakeMorphList` | `002D8890` |
| `002B1498` | `sdfModelMakeRoot` | `002D8918` |

Node creation clears 256 bytes, installs self links at zero/four, the native
`FFFF` halfword and `80808080` colour, VF0 translation/quaternion vectors,
unit scale and an identity matrix. Root creation clears exactly 152 bytes,
creates the actual four-byte node array with growth 32, and installs its own
native defaults. VF10 changes and the original packed identity transport are
included in the comparison.

The model definition contains four words: node-list pointer, material-definition
pointer, signed morph/slot-pair count, and extra-data pointer. Node records
follow a sixteen-byte list header at an eighty-byte stride. Construction reads
the signed parent index at record `+C`, attaches to an already constructed
parent or the root chain, then stores record `+8` as the node ID. Actual material
creation/parsing and optional zeroed sixteen-byte morph/slot-pair arrays run.
Pose and draw-command setup occur later and are not added by this root builder.

Definition `+C` is borrowed directly into runtime root `+90`, establishing the
transport used by the MPOS/effect attachment lookup. This confirms the earlier
retail association without treating serialized definition `+90` as that pointer.

Hierarchy helpers preserve original write order, full register pointer equality
and signed halfword array counts. Root chains and circular child rings use node
`+C` differently. Unlink leaves the node's parent field unchanged; null-parent
assignment does not call unlink and does not clear an existing child pointer
when the root head is empty. These behaviors are preserved, including tested
dirty upper register words; managed reference behavior is not substituted.

## References and transfer

[Seven Unity bodies and four community files](model-root-creation-matches.json)
are reviewed with direct links, inspected revision and hashes. Unity's morph-list
method aliases an empty body and supplies no implementation.

Pinned community [model definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_model.h)
corroborate four-word definition fields, eighty-byte items, signed parent indices
and IDs. [Model source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfModel.c)
corroborates slot-pair allocation and separates construction from pose/draw
setup. Source-unit notes provide build-specific projection context, not recovery
counts or replacement identities.

[Seven complete DDS instruction spans](model-root-creation-transfer.json) match
with only checked call relocations. The remaining complete root constructor is
independently constrained by the matching caller and its two resolved callees:
only two JAL targets and the original allocation immediate differ. Nocturne
requests/clears `98` bytes; DDS requests/clears `9C`. Fifteen direct-call
constraints agree. Community [DDS draw definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_draw.h)
describe a LOD byte at `+98`; this does not prove whether Nocturne has or uses
that field. Preserve the target's constructor size when transferring research.
No DDS execution or byte-identical root-constructor claim is made.

## Validation and next work

[544 original-instruction comparisons](model-root-creation-validation.json)
pass, reaching all 225 main instruction addresses. Inputs cover zero/nonzero
definition counts, ordered chains and branches, root insertion and child rings,
empty/nonempty new parents, unlink/reparent no-op paths, pointer upper words,
actual capacity growth, bounded signed capacities/counts, material counts
zero/one/three and several material flag forms. Material texture-reference
association is not exercised by these root cases.

Complete declared RAM, defined returns, Status, COP1, defined VU/ACC/Q and
original callees agree; no uninitialized reads are reported. The capture runs
198,236 original steps and 4,016 vector instructions. All eight interfaces are
saved in Ghidra and independently reopened; current exports are merged.
[Another 9,126 affected comparisons](model-root-creation-regressions.json) pass
on the same rebuilt host using existing cleanup, motion-creation and D3P
captures. Recognized body credit is 1,064 bytes; the full contiguous instruction
spans compared total 1,072 bytes.

Recovery is **1,914 / 8,986 functions (21.300%)**, with **325,587 focused cases**,
**788,271 aggregate cases**, and **144 reports**. Aggregates combine registered
historical captures and do not represent a new full run.

The expanded resource bootstrap has **164 pending recognized bodies /24,396
bytes**, with zero missing exports. Continue model pose/draw setup, resource
arrays and remaining model/PCP part constructors before unchanged retail MD/D3P
construction. Invalid/forward/self parents, cycles, allocation failure,
negative/huge definition loops, complete lifecycle, physical rendering and a
matching executable remain unproved. One rolling capture is retained; no
checkpoints or backup copies were created.

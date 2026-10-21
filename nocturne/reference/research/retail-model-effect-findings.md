# Original model archives, PIB records and bootstrap requirements

The [asset census](retail-model-effect-assets.json) reads 688 original PB/AB
files directly from DDS3.IMG. It checks 625 PIB payloads, 627 model definitions
and 4,641 stored mark positions. No assets are copied or patched.

All 625 PIB headers' declared effect counts agree with their local D3P/IPU
records; their motion counts agree with the local MT00 books. All referenced
effect indices are within the declared counts. The observed items are 225
generic-copy records, 46 model-track records, four colour transitions and one
cached-resource/IPU record. No type-one billboard-only item appears in this
selected asset set. These are static associations, not native loader execution.

## Geometry and provenance

Original PAC framing identifies raw type-one PIB/D3P/IPU records and relocated
type-six MD/type-eight motion data. PIB headers and items follow the recovered
native count/chunk/first/next consumers. Reviewed Unity header/item readers
corroborate version, chunk/effect/motion counts, mark IDs, copy count/resource
indices and optional offset words. Native field widths remain authoritative.

The model maker's original `002B14D8` load and `002B14EC` store transport model
definition+`0xC` to runtime root+`0x90`. That pointer is an original relocation
in the selected model definitions. Walking its unchanged extra-data chunks
locates MPOS structurally; their `16 + count*64` sizes agree with original tag
and position consumers. This replaces a byte-string search with a checked
pointer/stride chain. Model-root construction itself remains unrecovered.

[Pinned community motion/track definitions](retail-model-effect-assets.json)
provide related-engine vocabulary and contextual record ownership. Source URLs,
revision `bec33411543cdc487bad9debdf758f0090a2242c`, source hashes and inspected
Unity reader hashes remain in the census. Neither community layouts nor managed
runtime offsets replace the original PS2 bytes.

## Unchanged retail execution

[The reader comparison](retail-pib-records-validation.json) executes all 625
complete unchanged PIB payloads through original instructions and the actual
recovered C, in 1,882 cases. Count, successful/missing chunk lookup, first item
and next/sentinel results agree with independently decoded offsets. All declared
RAM remains unchanged; no uninitialized reads occur. Constructed handle/model
pointer backing transports the original payload; no expected game return is
supplied to a dependency.

The retail set does not exercise the hypothetical missing-PIB-pointer branch
at `001DEA88`; its coverage gap remains explicit. Existing earlier function
validation covers broader constructed inputs. This integration report adds
execution evidence and 1,882 focused cases without new function credit,
Ghidra changes, DLL changes or a new full-suite run.

## Discrepancies and next recovery

Eight stored attachment records request IDs missing from local MPOS data.
Seven request one absent ID; the boss `model/devil/boss/0x100.PB`, group eight,
contains a 65,535-count record with 65,521 missing local IDs. Original unsigned
counts and lookup skips must be retained. This census does not determine
author intent, runtime selection or dynamic additions to model marks.

Ninety-three chunks use default group `-1`; every other selected group is a
valid local motion-cut slot. The original caller `001DD0D0` invokes generation
with both cut and play group `-1`, corroborating a separate creation-time path
from the recovered motion-change caller. Recovering that caller and resource
bootstrap is required for full retail attachment execution.

[The expanded bootstrap frontier](retail-model-loader-frontier.json) has 146
pending recognized descendants /22,668 bytes and no missing exports at its
inspected boundaries. It includes model construction, resource-array creation,
raw D3P loading/version conversion and five actual major creation callbacks.
The already recovered copy routines do not prove that loading pipeline. Relevant
constructors, default-effect initialization and original model/resource order
are the next priorities. Other indirect tables may expand the graph further.

Compiled recovery remains 1,897/8,986 functions (21.111%). Current 141 focused
reports contribute 323,629 cases, or 786,313 including the earlier full run.
Entire executable recovery, physical scheduling/rendering and matching binary
remain outstanding. Working outputs roll forward without checkpoints.

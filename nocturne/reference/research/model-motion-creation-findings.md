# Original model motion creation, capture and cut binding

Nineteen complete routines in `src/model_motion_creation.c` add 1,896 recognized body bytes. All 3,584 original-instruction comparisons pass, reaching all 397 selected main addresses and executing 405,543 original steps. The build passes with warnings treated as errors. Full declared RAM, defined raw returns, Status, allocator primitives and ordered callback targets/operands agree. The comparisons execute 2,973 actual factory/capture/bind callbacks through unchanged original tables, 512 original C.LT.S comparisons and 128 connected controller-construction preludes.

The affected effect provider's 3,328 existing cases pass on the rebuilt host. [Current regression evidence](model-motion-creation-regressions.json) checks sources, verifiers, inputs, vectors and DLL hashes. All nineteen interfaces were saved in the working Ghidra project, checked after reopening and merged into corrected exports. `sdfMotionChangeBlend` uses three A-register raw64 arguments and F12/F13 float32 arguments. The host bit-transport wrapper receives no extra function credit.

## Community and Unity references

Thirteen Unity bodies provide reviewed semantic roles. Original instructions establish layouts, integer widths, unchecked access, initialization and callback ordering. Six native descriptive aliases have no claimed original spelling. Managed bounds checks and HD initialization differences are not imported.

The pinned Megami-Decomps DDS repository supplies independently useful motion terminology and structural research at revision `bec33411543cdc487bad9debdf758f0090a2242c`:

- [Motion bindings](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_motion_bindings.h) describe release, bind, sample, capture and blend callback slots, common controller/key/target words and captured values.
- [Motion types](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_motion.h) and [model API](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/mdl_motion_api.h) inform controller/book and model-group investigations.
- [Motion source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfMotion.c) provides allocation, initialization, capture and binding context; [source-unit research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md) supplies compiler/transfer context.

[The reference review](model-motion-creation-matches.json) retains fetched hashes, revisions, direct source links and corroborated fields. These sources were inspected as reference material; upstream code is not copied, linked or executed. No complete Nocturne format parser or retail motion-asset association is inferred. Community findings informed controller, callback and key-record fixture structures, checked independently against original Nocturne instructions and table bytes.

## Checked native behavior

- A controller allocates 52 zeroed bytes, publishes its root list link before constructing nodes, creates an actual native array through the pool/heap path, and iterates unsigned book command counts. Major command high16 and basic-model low16 dispatch select actual original factories.
- Five basic model-node factories allocate 32-byte vector nodes or a 20-byte visibility node. Their common initializer installs the original vtable/controller and resolves the model target through the actual native search. Newly allocated payload remains dirty where the original leaves it untouched.
- Positive blend duration captures each node through vtable offset C before binding. The cut index is stored as a halfword but pointer selection uses its low32 value. Timing fields retain raw F12/F13 bits, including original sign inversion. A missing cut sets state5 and zero frame count. Key-record stride is reloaded after each real binding callback.
- Model groups select native definition records and signed slot indices; original unchecked negative-index behavior is retained for backed cases. Effect-controller insertion and effect-resource lookup preserve original list and signed comparison behavior.
- Model search selects indexed or full64 ID lookup from the original flag. Tag lookup returns the original incoming raw64 pointer on a first-record match; after advancing, the original ADDU produces a sign-extended pointer. This distinction was exposed by native comparisons and corrected in C.
- Root tag and MPOS item searches, the global resource-ID chain, and active motion-cut lookup execute original dependencies. The active-cut query returns a cut number or raw64 -1, rather than a frame count.

The fixture arena covers seven allocator class records and a backed free heap block. Extending an earlier fixture's class descriptors into the following heap-head global was corrected before capture. Native capture completed without ERROR or uninitialized reads. The exporter retains its known temporary-language `rom0` block error; the fresh summary independently confirms nineteen complete successful corrected exports, unchanged recognized inventory and unsigned DIVU. Interface application and reopen logs are clean.

## Transfer and remaining work

[Static DDS checks](model-motion-creation-transfer.json) resolve eighteen complete selected counterpart spans. Independent major/minor factory positions constrain six ambiguous identities, and ten original basic-model bind/capture positions have complete byte-identical 8/28-byte callbacks. The resource-ID list lookup remains unresolved. These are static executable correspondences, not DDS execution or proof that all global data agrees.

The [motion indirect frontier](model-motion-creation-frontier.json) at that creation milestone tracked three major and five basic factory prefixes plus five original callback vtables: fourteen pending recognized descendants /1,912 bytes, including sample/blend paths and material/morph factories. Their further indirect tables, full table extents, retail asset selection, complete motion/effect attachment and outer hit/model constructors remain unresolved. At that milestone, the [hit-effect frontier](battle-check1-effect-frontier.json) had 21 pending descendants /3,692 bytes and the [action frontier](battle-action-dispatch-frontier.json) has 379 /91,028 bytes. The separate part/PCP prefixes then exposed 310 pending /51,496 bytes and seven missing exports. These graphs overlap; their counts must not be summed.

Keep checking relevant community research as these remaining subsystems become recovery targets. Complete physical runtime, malformed ownership/cycles, arbitrary aliases, all FCSR flags/timing and a matching executable remain unproved. One rolling native capture was used; no project/source copies or checkpoints were created.

The subsequent [sampling recovery](model-motion-sampling-findings.md) completes the five basic-model sample/blend paths and expands the rolling motion frontier into material/morph tables. Consult that newer result for current recovery and frontier counts.

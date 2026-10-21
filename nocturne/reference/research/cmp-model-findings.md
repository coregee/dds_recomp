# Status-model recovery

**Nine recovered model routines add 12,288 fresh original-instruction comparisons and 524 bytes of original code.** The complete checkpoint is **252 recovered C functions /191,516 passing cases**, with242 reviewed HD counterparts,46 library identities and7 chosen PS2 aliases.

| PS2 entry | Native reference | Function | Cases |
|---|---|---|---:|
|0023f8c8|18223ba00|cmpSetModelMoveMode|768|
|0023f8e0|182237c10|cmpGetStatusModelHandle|1,024|
|0023f8e8|182237bb0|cmpGetModelMinorNo|1,024|
|0023fb90|18223a7e0|cmpModelTblGetMotNo|768|
|0023fbc0|18223a870|cmpModelTblGetMotSpd|1,536|
|0023fbf0|18223a900|cmpModelTblGetPos|1,536|
|0023fc40|18223aad0|cmpModelTblGetRot|1,536|
|0023fa98|18223b020|cmpModelTblSetPos|2,048|
|0023fb10|18223b1e0|cmpModelTblSetRot|2,048|

The original model table starts at345F70 with44-byte records. Reviewed fields are motion byte0, speed word8, position wordsC/10/14 and rotation words1C/20/24. Unknown fields remain unknown. Index arguments use the low unsigned16 bits. Synthetic full-range backing exercises high indexes without claiming the shipped table contains65,536 records.

Position and rotation getters perform three ordered load/store pairs. An output one word beyond the first source propagates the first value into later words; a bulk copy changes this behavior. The comparator tests17 aligned neighboring output offsets plus disjoint output and checks the entire2,883,719-byte table allocation on every call. Setters convert all three signed32 integers first through EE CVT.S.W and then perform ordered EE ADD.S operations. Float getters preserve raw words, including encodings Python float conversion can alter.

The move-mode setter tests the full32-bit integer, then normalizes its byte to0 or1. The handle getter returns an opaque original32-bit pointer unchanged. Minor-number access zero extends the original ushort. Native managed arrays and pointers provide semantic leads, not the PS2 interface.

Three missing entries at23F9F8,23FA98 and23FB10 have complete byte-checked spans of156,120 and124 bytes. The first begins before its stack prologue. It is the speed-update candidate but remains anonymous and outside the recovered-C count: it calls the actual model-motion engine. The two vector updates are independently validated and named. Discovery now records454 entries; the recognized inventory is8,938.

All191,516 C comparisons were rerun against179,228 preserved baseline instruction rows plus12,288 fresh model rows. The109 current hashes cover59 source and50 verifier files. All19 capture-input hashes reproduce; two positive guard controls and14 intentional drift cases pass. Twenty-one malformed fixtures are rejected, and injected call failure restores all owners and bindings. Raw speed fixtures cover every exponent with both signs, neighboring aliases include85 propagation cases per getter, and3,129 high-index cases pass. Fresh DIVU/COP1 audits,172 published EE values and140,000 Java/C probes pass. Console execution, FCSR, timing and matching binaries remain separate work.

Saved project: `ghidra/checkpoints/252-functions/Nocturne.gpr`. Snapshot: `backups/SLUS_209.11-2026-10-04-203120.gzf`, SHA256 `5dbde1bfa91bdd52f9e21510cd7b5ef5077f1fa27289f186af113d3fe255868a`. Nine model interfaces pass after reopen, including F0 float return and original32-bit pointer width; all46 library ABIs pass. Fresh full export decompiles all8,938 recognized functions with zero failures.

See `cmp-model-validation.json`, `cmp-model-abi.json` and `drafts/cmp_status_model/canonical-body-evidence.json`. The243 checkpoint retains105 exact historical inputs and its immutable vectors. Three new transfer families bring the signature ledger to65; equivalent routines in other SMT games still need independent verification.

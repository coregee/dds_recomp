# Additional material setters: 274-function checkpoint

Five original PS2 leaves now compile as C11 and pass 10,240 fresh comparisons against their original instructions. Together with the unchanged 269-function baseline, the complete host suite passes 246,812 comparisons across 274 routines (3.064% of 8,944 recognized functions). This remains early source recovery.

| Original entry | Recovered descriptive name | Raw word offset | Flag mask at byte+6 |
| --- | --- | --- | --- |
| 002b2ec0 | ps2MatSetWord28 | 0x28 | 0x03 |
| 002b2ef0 | ps2MatSetWord2C | 0x2C | 0x03 |
| 002b3068 | ps2MatSetWord18 | 0x18 | 0x30 |
| 002b3080 | ps2MatSetWord34 | 0x34 | 0x30 |
| 002b3098 | ps2MatSetWord30 | 0x30 | 0x30 |

Each leaf takes the material pointer in A0 and an uninterpreted 32-bit word in A1, returning void. The original order is flag load, word store, flag OR, return, flag store in the delay slot. Recovered C preserves this order. Twenty-five independently encoded words pin all 100 original body bytes. Native HD identities and field roles remain unresolved; the names describe only proven offsets.

The fixtures exercise every flag byte, four word-aligned residues modulo 16, fixed raw-word patterns and randomized words, with randomized caller memory and surrounding canaries. The comparison checks the complete memory arena. Ten malformed fixtures are rejected, and both successful and failing comparisons restore the host arena owner. The guards exclude unbacked pointers, misalignment, concurrency and MMIO.

The saved Ghidra project is `../ghidra/checkpoints/274-functions/Nocturne.gpr`. A separate 56-byte `materialWordSetterView_PS2` expresses the accessed offsets; the earlier 36-byte scalar view remains unchanged. Reopened audits validate all five new A0/A1 signatures and the prior scalar, key, callback, model, PIB and 46 library interfaces. The fresh whole export contains 8,944 decompiled functions with zero failures.

[Validation certificate](material-setter-validation.json) pins 134 current source/verifier inputs, 23 before/after-attested fresh capture inputs, the saved snapshot, original-word evidence and ABI reports. The 236,572 prior instruction rows are preserved exactly; 10,240 additional rows were freshly captured under the same engine/provider and 16-file language. Historical 269 source/verifier inputs and vectors remain in `checkpoints/269-functions/`. All compiled C comparisons were rerun. This is agreement with the isolated instruction model, without runtime or matching-binary certification.

One new shared-SMT fingerprint brings the ledger to 73. The dirty-mask split is a useful structural search clue for related games; no cross-game equivalence is established yet. The next connected routines require the [VU transport and arithmetic prerequisite](vu-transport-findings.md).

# Scalar and material motion recovery

Seven routines are recovered in `src/material_motion_scalars.c/.h`, compiled with MSVC C11 `/W4 /WX /O2`, and saved in `ghidra/checkpoints/269-functions/Nocturne.gpr`. The current total is **269 recovered C functions /236,572 passing instruction comparisons**, about3.01% of8,944 recognized functions. Raw pseudocode exports cover all8,944 functions with zero decompilation failures; these remain separate from compilable source recovery.

| PS2 entry | Recovered name | Evidence |
|---|---|---|
|002b2e78|sdfMatSetAmbient|HD1825e57b0; raw color at+10|
|002b2e90|sdfMatSetDiffuse|HD1825e57e0; raw color at+14|
|002b2ea8|sdfMatSetSpecular|HD1825e5800; raw color at+20|
|002b2ed8|sdfMatSetConstant|HD1825e57d0; raw F12 word at+1C|
|002b4230|ps2MotionInterpolateScalar|Descriptive PS2 alias; direct key-pair A0 and F0 result|
|002b52f0|ps2MotionApplyMaterialConstant|Real key search, scalar interpolation and constant setter|
|002b5330|ps2MotionBlendMaterialConstant|Real key search, saved node+10 scalar, F13 blend and constant setter|

All67 original instruction words /268 body bytes were independently encoded and compared with the ELF. `drafts/material_motion_scalars/body-evidence.json` pins this proof; `pre-annotation-inputs.json` resolves the old anonymous function metadata to preserved copies. Each setter reads old flagbyte+6 before its word store and writes `old_flags|3` in the return delay slot. Matched HD fields add10hex for the managed header. HD NULL checks differ from the unchecked original backed-pointer path. Channel packing and full material allocation are unproved.

The scalar helper loads next value and interpolation, then computes `next_product=MUL(next,alpha)`, `previous_product=MUL(previous,alpha)`, `sum=ADD(previous,next_product)`, `result=SUB(sum,previous_product)`. Its last subtraction executes in the return delay slot. An ordinary lerp rewrite or swapped multiplier operands changes some EE raw results. Both callbacks execute the complete original key helper; the blend callback performs the same ordered arithmetic again against node+10, and loads the material address between its two multiplications.

The24576-case fresh capture includes1024 cases per setter (all256 flag values and four aligned residues),12288 scalar cases (8000 raw-edge triples plus random/header aliases), and4096 cases per callback. Callbacks cover eight counts including backed zero-count behavior, four aligned byte strides, ordered/equal/extreme/random time patterns, loop/nonloop controls, selected-minus-one reads, raw frame/blend encodings and material aliases into node/controller/cut/data. Every executed callback's original stack key pair has backed aligned scalar addresses and independently matches compiled `sdfMotGetKey`;8192 witnesses pass. Full4096-byte caller RAM and64 guard bytes are compared. Original capture checks low64 S0,SP,RA and raw F20 restoration per case. Twelve malformed row probes are rejected, and injected host failure restores owner and address bindings.

The current269-function suite passes236,572 comparisons:211,996 immutable instruction rows from the262 checkpoint plus24,576 freshly executed scalar/material rows. All compiled C comparisons were rerun. Exact guards establish unchanged prior engine, setup, provider and all16 processor-language files; no old expected row is recalculated. The new capture attests23 inputs before and after execution, while the whole comparison report pins67 source and63 verifier files. Fresh unsigned DIVU/COP1 mapping audits pass, as do208 published FPU result words and180,000 separately labelled Java/C probes. Comparison semantics remain a separate draft. FCSR flags/timing/hardware/runtime and matching binary remain unclaimed.

The saved checkpoint was reopened separately. Its seven custom ABIs, all67 words and partial36-byte material view pass; the prior key, callback, model, PIB and46 library ABI audits also pass. Host C uses raw float words; target signatures bind float F12/F13/F0 explicitly. Node+10 remains a raw saved-value region in the existing node view. The snapshot is `backups/SLUS_209.11-2026-10-05-193731.gzf`, SHA256 `a951d061da33a37eef9c64f0646135dd7925908359136f8d872621e2a08361e4`.

Four new pairs raise the HD ledger to253, three aliases raise the PS2-only game ledger to13, and two shared-engine fingerprints raise `shared-smt-signatures.tsv` to72. These are transfer candidates, with target offsets and register storage to be re-established per executable. No cross-game equivalence is claimed.

Next are the remaining material setter leaves at002b2ec0/002b2ef0/002b3068/002b3080/002b3098, followed by color/vector interpolation. Color helper002b42b0 and blend callback002b51d0 require independently validated packed-byte/halfword operations and VU accumulator/conversion semantics; the existing scalar COP1 model does not certify these. Private callee stack frames, MMIO/concurrency/address wrap, exhaustive inputs, full FCSR state/timing and hardware/runtime/matching binary are outside this checkpoint.

## Follow-up: 274 checkpoint

The five remaining setter leaves are now recovered and validated in [material-setter-findings.md](material-setter-findings.md). Their descriptive names preserve unresolved HD identities. The original lead evidence above remains historical. Color recovery now proceeds through the independently audited [VU transport prerequisite](vu-transport-findings.md); masked arithmetic and accumulator behavior remain outstanding.

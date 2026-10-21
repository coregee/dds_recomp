# Material construction, callback and pool release recovery

This document records the historical 326-function checkpoint. [Current recovery](memory-array-lists-findings.md) is 345 functions and 443,420 completely fresh comparisons. The links below resolve the 326 certificate and integrity records to their preserved archive.

The saved checkpoint contains **326 / 8,954 recognized PS2 functions (3.64%)**, validated by **404,508 completely fresh original-instruction cases**. This batch contributes 21 functions, 90,112 separate cases and 1,540 original body bytes. It adds ten closed callback boundaries, one reviewed HD material constructor counterpart, 20 descriptive aliases and four transfer patterns. Full/near-full reconstruction remains unfinished.

Source is in `src/material_callback_saves.c/.h` and `src/material_construction_release.c/.h`. [The batch certificate](checkpoints/326-functions/inputs/analysis/material-construction-release-validation.json), [canonical regression](checkpoints/326-functions/behavior-validation.json) and [final integrity](checkpoints/326-functions/inputs/analysis/checkpoint-326-integrity.json) pin the current evidence. The saved project is `ghidra/checkpoints/326-functions/Nocturne.gpr`.

## Recovered functions

| PS2 entry | C function | Separate fresh cases |
|---|---|---:|
| `002b4c08` | `ps2MotionSaveMaterialFlag14` | 8,192 |
| `002b4e60` | `ps2MotionSaveMaterialWord14` | 8,192 |
| `002b4fc0` | `ps2MotionSaveMaterialWord10` | 8,192 |
| `002b5120` | `ps2MotionSaveMaterialWord20` | 8,192 |
| `002b5280` | `ps2MotionSaveMaterialWord28` | 8,192 |
| `002b5388` | `ps2MotionSaveMaterialScalar1C` | 8,192 |
| `002b57d8` | `ps2MotionSaveMaterialWord18` | 8,192 |
| `002b58b8` | `ps2MotionEmptyMaterialCallback58B8` | 8,192 |
| `002b5990` | `ps2MotionEmptyMaterialCallback5990` | 8,192 |
| `002b5ca0` | `ps2MotionSaveMaterialFirstFourWords` | 8,192 |
| `002b2f80` | `ps2MatSetFiveScalars38` | 512 |
| `002b30e8` | `ps2MatSetFiveScalars3C` | 512 |
| `002b31d0` | `ps2MatSetScalars40And44` | 512 |
| `002b4cb8` | `ps2MotionBindMaterialNode` | 512 |
| `002b5398` | `ps2MotionCreateMaterialFiveWords38Node` | 512 |
| `002b5510` | `ps2MotionCreateMaterialFiveWords3CNode` | 512 |
| `002b5688` | `ps2MotionCreateMaterialWord18Node` | 512 |
| `002a8ba8` | `ps2PoolAllocateZeroed` | 512 |
| `002bfce8` | `ps2ZeroQuadwords` | 1,024 |
| `002a8bd8` | `ps2PoolRelease` | 2,048 |
| `002b31e8` | `ps2MatCreate` | 1,024 |

## Material and node behavior

The five-scalar setters load their lazy38/3C targets, store the fifth word first, then the first four, and reread/set the dirty byte last. The pair setter reads the dirty byte before storing at 40/44. Raw float payloads remain intact. The binder runs base initialization before walking source+4 → controller+C → owner+C → indexed material pointer. This order is retained on overlapping records. Node creators allocate36/36/20 bytes and bind the original tables529588/5295A0/5295B8; A1 is unused while A2 supplies the index.

Six short callbacks save one raw word from material14/10/20/28/1C/18 to node10. The flag save inverts bit4 of the material halfword14 and writes node byte10. Two callbacks contain only JR/NOP and access no memory. The 16-byte save completes both LDL/LDR pairs before either SDL/SDR store pair, retaining snapshot semantics for every source byte residue and partial overlap.

The material constructor allocates a zeroed72-byte record; rounded quadword clearing affects80 bytes. It marks dirtyFF, allocates two 160-byte packets, writes6E05C000/6005C005/640CC00A/0400000C/14000000 and one zero packet word, sets three 80808080 colour defaults and clears the scalar pair. Unwritten packet bytes retain their previous contents. The material counter increments before allocation.

## Unity correspondence and transfer

PS2 `002b31e8` now has a reviewed counterpart at HD `1825e55b0`, `sdfMat$$sdfMatNew`. Evaluating the retained HD packet helpers yields the same five command words. The two-packet loop, dirty flag, three colour defaults, zero scalar pair and counter update also agree. The C name remains descriptive because the original PS2 symbol spelling is unproved. HD uses managed arrays/handles and 64-bit pointers, a changed packet tail layout, and a counter increment after managed construction. This is behavioral correspondence rather than exact source equivalence.

Four new SMT transfer patterns cover save callbacks, scalar setters/node binding, rounded zeroing/pool release and the material packet constructor. The ledger contains 84 patterns. Relocation-masked21-body draft signatures are retained as a search aid; they have not established cross-game matches, and empty/short bodies require table/callgraph context.

## Pool behavior and verification

Zeroed allocation rounds with a wrapping signed32 size+15 followed by arithmetic shift4. The zero helper clears four quadwords per loop, then a backwards1..3 tail; negative counts access no memory. Signed32 integer arguments occupy sign-extended low64 EE registers. Pool release derives a24-byte header from signed truncated(slot-arena)/4096,decrements used16,reopens a full page, or unlinks/recycles an empty page. Surviving pages prepend the freed slot through slot+8. The prior interrupt state controls restoration.

The callback pass covers81,920 cases and all 4,096 caller bytes with 64 C canary bytes. The connected pass covers8,192 cases, five mutable RAM spans totaling 20,864 bytes, 320 C canary bytes, return values, Status and primitive-call counts. Original calls through getters, allocation, JALR dispatch, node initialization, zeroing and release execute in the capture. Saved S0..S8,F20..F24 as applicable, SP, RA and zero are checked. Host owners, bindings, status and counters restore after success, rejection and mismatch checks;27 malformed standalone rows and 8 malformed canonical rows are rejected.

The complete canonical326-function capture pins 177 exact inputs before/after execution, including77 source and 83 verification inputs and the same16 audited language files. All 404,508 rows are fresh; no historical expected row is reused. DIVU/COP1 audits, 208 published FPU words, 180,000 Java/C probes and the existing 74,880-case primitive value audit pass. New and earlier ABIs reopen successfully in the saved 8954-function project, whose full export has zero failures.

Exact 305 artifacts remain archived with 152 certified source/verifier inputs, 169 capture inputs, 314,396 original rows, canonical host DLL, prior reference DLL and publication documents. Both invalid draft fixture runs are preserved; accepted standalone captures correct the overwritten pointer and signed-argument extension errors and contain no uninitialized-memory reads.

A discarded full capture exposed a callback-counter observation error: already decoded primitive instructions retained the earlier callback map, while the connected fixture group collected counts through a newly registered map. Return values, RAM and Status agreed in the first mismatching case. The exporter now retains a single shared counter map across groups. A separate8,192-case original-PC warmup regression compares all connected RAM, returns, Status and primitive counts successfully. The discarded404,508-row capture is archived as diagnostic evidence; none of its expected rows are reused in the accepted complete fresh run.

[Next frontier](material-construction-next-frontier.md) continues through pool initialization, material-list/lifetime routines and their callers. Hardware interrupt timing, privileged exceptions, allocation failure, private callee stack, runtime and matching executable are unproved.

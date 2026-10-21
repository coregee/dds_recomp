# Material construction, release and callback draft recovery

The current published checkpoint remains **305 functions**, validated by **314,396** original-instruction cases. This separate batch adds **21 independently validated C drafts**: ten newly bounded callback leaves and eleven already recognized connected functions. It passed **90,112 fresh cases**, with no C mismatches. The new bodies total **1,540 original bytes**. No new function boundary, source file, Unity identity or transfer signature has been promoted into the authoritative ledgers.

The callback pass compares all4,096 caller bytes plus64 C canary bytes per case. It checks partial overlaps, raw float words (including special bit patterns), both halfword residues for the flag load, all eight byte residues for the merge-load snapshot, and empty callbacks with null or arbitrary unused pointers. All nine saved low64 GPRs,SP,RA,F20 and architectural zero were checked during original execution.

The connected pass compares five complete mutable RAM spans totaling20,864 bytes,320 C canary bytes, return values, Status and DI/EI/SYNC/PLZCW call counts. It executes actual internal PS2 calls through getters, allocation, JALR dispatch, node initialization and quadword clearing. It checks S0..S8,F20..F24,SP,RA and zero each case. Host owners, bindings, status and counters are restored after success, rejection and mismatch checks.

| PS2 entry | Draft C function | Fresh cases |
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

`ps2MatCreate` allocates a zeroed72-byte material (the helper clears80 bytes), marks byte6 asFF, allocates two160-byte packet buffers, and writes five retained VIF command words and three80808080 colour words. The original material counter increments before allocation. Unwritten packet bytes retain their earlier contents.

The HD `sdfMat$$sdfMatNew` at1825e55b0 is a strong reviewed counterpart for PS2 002b31e8. Evaluating the retained HD helpers yields6E05C000,6005C005,640CC00A,0400000C and14000000, matching the PS2 constructor. Both initialize two packets, the dirty flag, three colour words, two zero scalar words and a material counter. HD uses managed objects/arrays/handles and a different packet tail layout; its counter increments after managed allocation. The correspondence is recorded as a naming lead, with zero newly promoted identities.

Pool release derives a24-byte page header from a signed page index, decrements the signed16-bit used count, reopens a previously full page, or removes an empty page from the active/available list and returns it to the global free-page list. A surviving page receives the freed slot through slot+8. The prior interrupt-enable state controls restoration. Fixtures include null release, head/interior removal, full-page reopening, count wrap and a negative fractional page offset.

The scalar setters at002b2f80/002b30e8 store the fifth float word first, then the first four, and only then reread/set the dirty byte. The pair setter at002b31d0 reads the dirty byte before storing at40/44. The binder at002b4cb8 runs base initialization before walking source+4 → controller+C → owner+C → indexed material pointer, which matters when the node aliases the source chain. Node creators allocate36/36/20 bytes and store original callback tables529588/5295A0/5295B8.

Two invalid fixture runs were retained under `analysis/checkpoints/material-callback-invalid-pointer-fixture` and `analysis/checkpoints/material-connected-first-abi-fixture`. The first accidentally overwrote a material pointer while preparing an overlap; the second zero-extended signed int32 arguments. Accepted captures correct both errors and contain no uninitialized-memory reads. These discarded rows are excluded from all validation totals.

Exact305 artifacts were archived under `analysis/checkpoints/305-functions`:152 certified source/verifier inputs,169 capture inputs,345 preserved artifacts, the canonical305 DLL, prior285 reference DLL, publication documents including README, ledgers, and original314,396-row vector file. The saved Ghidra305 checkpoint is unchanged, and its integrity check still passes.

Next promotion must create only the ten byte-gated callback boundaries in an isolated checkpoint, add all21 mixed ABI annotations without replacing earlier partial views, integrate both C modules/adapters, and pass the complete canonical regression. The prospective count is326 functions over8,954 recognized boundaries, with404,508 rows if this entire fixture batch is retained. These are prospective values, not current completion totals.

Hardware timing, asynchronous interrupts, privileged exceptions, allocation failure and private callee stack contents remain outside this static value comparison. Full executable reconstruction is still in progress.

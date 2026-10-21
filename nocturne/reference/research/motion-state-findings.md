# Motion requests and PS2 state leaves

Five recovered functions in `src/rst_motion_leaves.c/.h` add **6,144 fresh original-instruction comparisons** and240 original body bytes. All60 complete-span words independently re-encode against the ELF. Three functions have reviewed native counterparts; two have chosen descriptive PS2 aliases. The complete checkpoint is **243 recovered C functions /179,228 passing comparisons**.

| PS2 entry | Native reference | Function | Cases |
|---|---|---|---:|
|0021fd40|Chosen PS2 alias|ps2RstConsumeBusyState|512|
|0021fd78|Chosen PS2 alias|ps2RstMarkObjectFlag|768|
|0021fe30|182281b70|rstSetMotionReq|2,048|
|0021ff38|18227f820|rstCancelMotionReq|768|
|0021ff48|182281a80|rstSetMotionReqFromTbl|2,048|

## Original behavior and port differences

The state leaf reads original54FCEC:1 returns1 without clearing;2 clears to0 and returns0; every other raw byte returns0 unchanged. Both indexed callers test for zero. The object-flag leaf reads nullable original54FCE8 and ORs10 into object byte0. Unity animation-end/gift functions differ substantially, so these two leaves retain descriptive PS2-only aliases.

The motion setter stores motion byte22E5, mode byte22E6 and raw frame words22E8/22EC. Its original arguments use A0:1,F12:4,F13:4,A1:1. The mixed register layout was applied explicitly and verified after reopening the saved project; the initial pseudocode inferred the argument ordering incorrectly. C bit adapters prevent Python float promotion from changing payloads. Cancellation changes only mode to2. The native setter has an extra gift-control reset absent from the original.

The table wrapper uses the current unsigned ushort ID and signed low-byte Type to select `(ID*7+Type)*3` at332458. It loads a signed motion number and two unsigned frame bytes, converts the frame bytes through original CVT.S.W, then tail-calls the real setter with mode0. Every byte frame converts exactly; signed Type remains signed, including complete backed cross-row accesses. The193-by7 test span is backing for these cases, not a ushortID capacity claim. Result22F0 is a partial accessed extent, not the complete result allocation.

## Validation

Fresh captures cover all256 busy-state and object-flag bytes, NULL and writable unit/result aliases, all256 motion/mode bytes, every float exponent with both signs and raw payloads, all193-by7 table records, all256 signed Type values with backed accesses, and standalone/physical/preview unit pointers. Full owner bytes, surrounding guards, result pointer slot and state bindings agree. Seventeen malformed rows are rejected; injected host-call failure restores all owners, pointers and mappings. Fixture preparation reproduces all19 captured input hashes and the manifest exactly.

All179,228 compiled C comparisons reran. Instruction inputs comprise173,084 preserved baseline rows and6,144 freshly executed motion rows. The105 current hashes cover57 source and48 verifier inputs; capture provenance separately pins the original ELF, compiled language, old code/fixtures/providers and unchanged engine/register setup. Two positive controls and14 deliberate drift cases pass. The earlier MMI invocation metadata describes the original baseline capture only. Fresh DIVU/COP1 audits,172 published captures and140,000 Java/C value probes also pass. Hardware/FCSR behavior, PS2 execution and matching binaries remain unverified.

Saved project: `ghidra/checkpoints/243-functions/Nocturne.gpr`. Snapshot: `backups/SLUS_209.11-2026-10-04-194553.gzf`, SHA256 `112dbaac328672e69ef2de48ac1b49df1edbb429df469be2cfd41bb96a0bcd93`. All46 library ABIs and the saved mixed motion ABI pass. Fresh full export decompiles8,935 recognized functions with zero failures.

See `motion-state-validation.json`, `rst-motion-abi.json`, `drafts/rst_motion_leaves/canonical-body-evidence.json` and `behavior-validation.json`. The238-function report and all101 old inputs are preserved under `checkpoints/238-functions/`. Two families bring the transfer ledger to62; related games still need independent instruction and layout checks.

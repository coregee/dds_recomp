# Level and result chain

Nine functions in `src/rst_level_chain.c/.h` add 6,144 passing original-instruction cases and 1,180 original body bytes. The full checkpoint is **231 recovered C functions / 167,196 instruction comparisons**. All 295 original span words were independently re-encoded against the ELF; eight identities use named native references and one is a chosen PS2-only alias.

| PS2 entry | Native reference | Function | Cases |
|---|---|---|---:|
|0021fd98|18227c150|rstAddLevel|1,024|
|0021ffb8|18227f940|rstChkAddSkill|768|
|00220000|182280930|rstGetEquipHeartsAisyo|512|
|00220020|182281440|rstSetDestroySkillMaxHpMp|768|
|00220288|1822800b0|rstChkParamLimitAll|512|
|002202f8|182281680|rstSetLevelUpCount|768|
|00220480|182280b40|rstInitWorkStock|768|
|0021f8d0|Chosen PS2 alias|ps2ClearResultParamDeltas|512|
|002207a8|18227c180|rstAutoAsignDevilParam|512|

## Original behavior and port differences

**rstAddLevel**: Previous unsigned ushort level<255 gates raw low16 addition; resulting sum is not clamped. Full 7 words/28 bytes independently re-encoded. Original nonnull full unit required; native null checks do not transfer.

**rstChkAddSkill**: Real owner query first; owned returns 0, otherwise unsigned skill count<8 returns 1, else 2. Full 18 words/72 bytes independently re-encoded. Current result unit is an embedded original 32-bit address, including physical work and preview aliases.

**rstGetEquipHeartsAisyo**: Global work equipped LBU feeds actual Hearts affinity accessor and its real ID0 shortcut. Full 8 words/32 bytes independently re-encoded. Original table layout and signed16 return retained; no managed layout transfer.

**rstSetDestroySkillMaxHpMp**: Plain 236-byte private copy; clear skill count, real maxHP/maxMP, selected skill only, real maxima again. Modular ushort delta additions change maxima only. Formatter 53DAB0, skill and both raw 32-bit deltas captured. Full 95 words/380 bytes independently re-encoded. Do not substitute custom-copy resource repair. External formatter adaptation captures all four words; SDK stdout source is not established.

**rstChkParamLimitAll**: Five real non-lane1 base queries require>=40; first failure 0, otherwise real mode0 resource updater then 1. Full 28 words/112 bytes independently re-encoded. Original one-argument ABI always updates after success; native optional second argument is absent.

**rstSetLevelUpCount**: Low8 old level/count into 1A/1B/18/19; real EXP loop; flag 200 real default-copy excess; real signed-byte addition BEFORE status 800 exit. Low8 excess adjustments then actual resource update. Full 53 words/212 bytes independently re-encoded. Native wide result fields and point-animation call do not transfer. Stored byte count sign and original operation order retained.

**rstInitWorkStock**: Clear result 20; real custom-copy into inline preview 170; signed LB original level 1A+1 as ushort. Nonzero mode plus flag 200 replaces preview level with real default-copy level. Full 33 words/132 bytes independently re-encoded. Native extra static-byte clear absent. Exact preview self alias allowed; other accessed result overlaps excluded.

**rstAutoAsignDevilParam**: Real six-byte clear 129F; private real custom-copy; signed positive point 18 iteration count reread each loop; actual weighted growth mutates scratch level-up bytes. Real parameter+signed output delta<40 gates increment. Full 45 words/180 bytes independently re-encoded. Original growth minimum-not-minus1 and return lane<6 contracts. No invented clamps; native wider count/growth behavior does not transfer.

**ps2ClearResultParamDeltas**: Full eight original words independently re-encoded. Tail real memset(result+129F,0,6), returning the interior original pointer. Chosen descriptive PS2-only alias; historical spelling and distinct HD body are unproved. Complete stable result backing required.

## Verification and scope

Fixtures capture complete work, RNG, unit, result and output owners, guard bytes, eight dependency tables including the existing EXP coefficient owner, original pointer slots and all shared host bindings. Existing resource, skill-power and level views share the same result allocation. Embedded addresses remain four bytes and map only to backed original owners, including exact preview self aliases.

Targeted inputs cover every stored level-count byte; all signed count bytes and preview level bytes; unsigned level boundaries and full signed additions; real EXP loops and default/custom copies; all 16 physical stock positions; skill ownership/count boundaries; real growth draws and parameter caps; and all four formatter arguments, including the original 53DAB0 format. The adapter rejects 18 malformed rows and restores complete owners, table pointers, address bases and diagnostic state after an injected failure.

The result view establishes offsets 18/19/1A/1B/20/22/24/16C, a complete inline 236-byte preview 170..25B, and signed delta bytes 129F..12A4. Its accessed extent 12A5 and host tail padding do not establish the complete allocation. Auto assignment retains the original minimum-minus1 exclusion and requires returned growth lanes below 6; unproved byte-wrapped fallthrough interfaces are not silently repaired.

All 95 source/verifier hashes and vector SHA256 `631c97a9b77683d6dc8975e3c47cad0cffc1e3c18293f32c88d5b40437024a73` pass. Saved project: `ghidra/checkpoints/231-functions/Nocturne.gpr`. Snapshot: `backups/SLUS_209.11-2026-10-04-183402.gzf`, SHA256 `e44b7e88de88f7697b29b5f0f50dfdd85f138b427669db6ed4f23bc9c0056153`. All 46 library register ABIs pass; the fresh raw export decompiles 8,935/8,935 recognized functions with zero failures.

The disconnected GUI bridge could not supply the original project during this batch. An independently saved project copy contains the new annotations; the earlier primary project is retained. The saved copy and snapshot are the current annotation evidence. Successful PS2 persistence does not establish earlier PC GUI persistence.

Full program recovery remains in progress. No console run, matching PS2 binary or cross-game equivalence is claimed. Four transferable fingerprint families raise the SMT ledger to 57; every related-game body and layout still requires independent verification. Detailed hashes and contracts are in `level-result-chain-validation.json`.

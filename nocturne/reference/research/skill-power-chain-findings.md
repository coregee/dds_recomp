# Result skill-power chain

Six connected functions are recovered in `src/rst_power_chain.c/.h`. The full checkpoint is **222 compiled functions / 161,052 passing original-instruction cases**. These six add 5,112 cases and 724 summed original body bytes. Independent instruction re-encoding verifies 181 listed and 183 full-span words, including the omitted NOPs at 220D0C/220FE4. Named native counterparts supply identities; original instructions determine behavior.

| PS2 entry | Native reference | Recovered function | Cases |
|---|---|---|---:|
|00220C50|182280220|rstChkSkillPowerUp1|512|
|00220CB0|182280340|rstChkSkillPowerUp2|1,016|
|00220E68|18227FB20|rstChkDevilSkillPowerUp|256|
|00220E78|182280150|rstChkPartyDevilSkillPowerUp|1,536|
|00220EF8|18227E100|rstCalcSkillPowerUpCore|1,024|
|00221018|18227E5F0|rstCalcSkillPowerUp|768|

## Original gates and native differences

The first gate reads the global player's unsigned level before result/unit reads. Below 7 it returns 0 without RNG or dereferencing even an invalid embedded unit address. Otherwise unitID0 consumes one real draw and returns 1; other IDs require low2 draw bits0.

The second gate consumes one unsigned draw modulo254. Player remainders0..111 return 0 and 112..253 return 1; other IDs use 0..127 and 128..253. HD adds 1 before comparing, shifting the boundary. Fixtures enumerate every remainder for both ID classes, including raw high unsigned draws. Original reserved return 2 branches remain in the source, although ordinary modulo bounds cannot reach them.

The unit query reads the complete flag word and extracts bit 40 as 0/1. The party query scans all 16 inline 236-byte units, qualifying flags 1 and 2 while excluding 4. Every qualifying original MOVE replaces the previous answer: the last eligible demon wins. A later eligible unmarked demon clears an earlier positive. HD OR-accumulates instead. Fixtures cover all positions, complete flag predicates, high bits and every ordered/reversed pair.

## Complete dependency chain

The core executes the real upgrade picker and writes result+76 even when no candidate exists. The picker writes the original slot to+74 only on success. It then calls the real before-list query with the negated unsigned byte at+1B narrowed to signed 8-bit; targeted demon fixtures exercise all 256 source-byte values. Real chance, owner, current-flag and party dependencies choose between marking flag 40 and mutation. Mutation reads the original selected skill and executes the actual64-attempt routine. Successful marking returns 1, mutation 2, exhaustion 3, and early eligibility failures 0. A failed mutation leaves the recorded upgrade proposal intact. The wrapper executes the first gate and the entire core when allowed, preserving all draws.

Original captures include every return 0/1/2/3 path, candidate stores on failures, real successful and64-draw exhausted mutation, current-unit aliases into the global party and signed level offsets. Both resource/result views use the same owner. No RNG, lookup, inheritance, before-list, ownership, copy or mutation result is supplied by a replacement callback.

## Layout, replay and limits

`rstSkillPowerWork_PS2` proves byte 1B, signed slot 74, ushort proposal 76 and the embedded original32-bit unit address at 16C. Its accessed extent 170 does not prove the complete result allocation. The address stays four bytes on 64-bit hosts; a test-only resolver maps it to the existing standalone unit or an aligned physical unit in global work. It supplies address translation only and preserves aliases.

Replay compares complete work, unit, result and RNG storage, all seven participating tables, guard bytes, both original pointer slots and every shared binding/address-map base. The adapter restores complete owners and bindings after each call and injected failures. Seventeen malformed rows are rejected. The isolated preflight is separate from canonical counts; the full regression passes all 222 functions. All 91 source/verifier hashes and the complete vector hash are checked before publishing.

The saved snapshot is `backups/SLUS_209.11-2026-10-04-173849.gzf`, SHA256 `fd12b2e6d58d1f91bc4c6bee97ad48dd868f604dc29d5c42f25f4d6e124a5c21`. All 46 library register ABIs pass. The fresh raw export decompiles 8,935/8,935 recognized functions with zero failures. The vector SHA256 is `8725b24b46258a44a4bda1bb696b94621a3512a63e89fce5e70acc237566cbfb`. Detailed evidence is in `skill-power-chain-validation.json` and `drafts/rst_power_chain/canonical-body-evidence.json`.

Contracts require ordinary aligned, fully backed stable RAM and valid dependency tables/counts. The below-level7 early-read exception is explicit. Existing mutation traps and uninitialized weighted-growth interfaces retain their documented limits. Matching PS2 binaries, console execution and hardware bus/FCSR behavior remain unverified. Three transfer fingerprints raise the ledger to 53; every related-game instruction/layout must be checked independently.

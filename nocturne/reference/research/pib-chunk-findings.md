# PIB chunk readers and lookup

**Four recovered functions add 7,168 fresh original-instruction comparisons and 180 bytes of original code.** The complete checkpoint is **256 recovered C functions /198,684 passing comparisons**, with 246 reviewed HD counterparts, 46 library identities and seven chosen PS2 aliases.

| PS2 entry | Native reference | Function | Cases |
|---|---|---|---:|
|001dea60|181c1aec0|mdlPibGetChunkCount|1,024|
|001deae8|181c1b170|mdlPibGetFirstChunkItem|2,048|
|001deb00|181c1b2b0|mdlPibGetNextChunkItem|2,048|
|001dea68|181c1af70|mdlPibGetChunk|2,048|

The count getter reads an unsigned halfword at header +C. Unity's `pibChunk_t.GetSize` at18110CB40 returns constant8 and is explicitly rejected as a counterpart. Native `mdlPibGetChunkCount` reads the corresponding count after its managed object header.

The lookup reads the original handle +C model-data address and model-data +A4 PIB address. A missing PIB returns NULL. Otherwise it calls the real count getter, advances by the current record's word at +4 before each group test, and returns the first full32-bit group match or NULL after count exhaustion. Tests execute 65,535 records for both last match and an exhausted search; the original path reaches 458,765 instruction steps. Duplicate groups return the first matching record.

First-item access returns pointer +8 unless the complete word there is0000FFFF. Next-item access adds the unsigned stride at +4 and uses the same complete-word predicate. Zero stride retains the same item unless its first word is the sentinel. Values such as0001FFFF,8000FFFF,FFFF0000 andFFFFFFFF are distinct from0000FFFF; masking to16 bits changes behavior. Native methods use managed data-position arguments rather than the original direct pointer interface.

The first native sentinel is stored as global18E08288C XOR30B076B6. Immutable GameAssembly.dll bytes at file offset231468684 contain30B08949; XOR yields0000FFFF. `native-sentinel-evidence.json` pins the DLL hash and PE mapping. This is disk evidence; mutation of that global during PC execution is not claimed.

The host lookup uses a read-only mapping from original32-bit RAM addresses to backed bytes. The mapping supplies no lookup result. A32-bit target build directly uses the original addresses. Raw pointer slots remain32 bits on the host, permitting instruction-level comparison without enlarging original records. Partial saved views cover header16 bytes, item8 bytes, handle16 bytes and model data throughA8; none establishes a complete allocation.

All198,684 compiled C comparisons reran against191,516 preserved baseline instruction rows and7,168 freshly executed rows. The113 current hashes cover61 source and52 verifier files. All19 capture-input hashes reproduce; two positive guard controls and14 drift cases pass. Full1,048,623-byte host backing and guards are compared every call; successful and failed calls restore memory and address bindings. Eighteen malformed fixtures are rejected. The initial standalone capture lacked canonical fixture identifiers, so it was retained unpromoted and independently recaptured; every instruction input, result and memory byte agrees, with only name/index metadata added. Fresh DIVU/COP1 audits,172 published EE values and140,000 Java/C probes pass.

Saved project: `ghidra/checkpoints/256-functions/Nocturne.gpr`. Snapshot: `backups/SLUS_209.11-2026-10-04-210924.gzf`, SHA256 `b8a2a42eba98560f8b878ffc748989659161970b51fa212b52fca3a1cd76531f`. Four saved PIB ABIs and all46 library ABIs pass. Fresh full export decompiles all8,938 recognized functions with zero failures.

See `pib-chunk-validation.json`, `pib-chunk-abi.json` and `drafts/pib_chunk_leaves/canonical-body-evidence.json`. The252 checkpoint preserves109 historical inputs and its immutable vectors. Two new transfer families raise the ledger to67. The actual model motion allocation, cleanup and channel callbacks still require recovery; these readers are part of that chain, not a replacement for it.

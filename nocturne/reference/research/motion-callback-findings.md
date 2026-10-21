# Motion callbacks and dispatcher repair

**Five recovered C functions add 5,120 fresh original-instruction comparisons and 104 bytes of original code.** The saved checkpoint has **261 C functions /203,804 passing comparisons**, 248 reviewed HD counterparts, 46 library identities and ten chosen PS2 aliases.

| Entry | Name | Identity basis | Cases |
|---|---|---|---:|
|002b3b78|sdfMotionNodeBaseInit|HD 1825ed370|1,024|
|002b4118|sdfMotCLBK_SetCut|HD 1825eb6e0|1,024|
|002b4c28|ps2MotionSaveValue60|descriptive PS2 alias|1,024|
|002b4c48|ps2MotionSaveValue50|descriptive PS2 alias|1,024|
|002b4c68|ps2MotionSaveValue70|descriptive PS2 alias|1,024|

The base initializer writes controller and vtable raw32-bit address words in original order. The cut callback is an eight-byte JR RA/store-delay-slot leaf. Both native methods retain the corresponding managed payload role, with different headers and NULL behavior. The three vector callbacks read node+C, load model+60/50/70 and store all128 bits at node+10. They preserve arbitrary fourth words and load-before-store aliases. HD model initialization leads copy in the reverse direction; their names are not promoted as equivalent PS2 bodies.

Tests cover every valid4-byte alignment for the word stores, full16-byte alignment for LQ/SQ, raw address argument edges, exact source/output aliases, adjacent blocks, source overlapping the node header and disjoint records. Every case compares the complete2,063-byte host allocation, including the2,048-byte original RAM and alignment slack; memory and two mapping bindings restore after successful and injected failed calls. Fifteen malformed rows reject before execution. Address mapping translates ordinary backed RAM only and supplies no game outcome; a32-bit build uses original addresses directly.

All203,804 compiled C comparisons reran. The original inputs consist of198,684 preserved rows from the256 archive and5,120 newly executed rows using the identical pinned language and existing engine/register setup. The117 input hashes cover63 source and54 verifier files. All19 fresh capture inputs agree; two positive guard controls and14 deliberate drift cases pass. Fresh DIVU/COP1 audits,172 published arithmetic values and140,000 independent Java/C value probes pass. Original comparison semantics remain in a separate draft; no shared language change or full FCSR claim is introduced.

The saved project repairs one dispatcher boundary from002b43ac to002b43a8: the actual selector ANDI occurs before the stack frame. Six additional entries are byte-gated and separately recorded: two category dispatchers, the cut store and three vector callbacks. Discovery evidence now has460 supported entries and the inventory has8,944 functions. Five new ABIs, nine prior model ABIs, four PIB ABIs and all46 library ABIs pass after reopening. Every recognized function exports and decompiles, with zero failures.

Saved project: `ghidra/checkpoints/261-functions/Nocturne.gpr`. Snapshot: `backups/SLUS_209.11-2026-10-04-220150.gzf`, SHA256 `d1118b7200f42e7ff9aee814d53e47d4e125e9811209d005981e57cd26aa679f`. `motion-callback-validation.json` pins the source, instruction provenance, ABI reports and original bytes. The256 archive retains all113 historical source/verifier inputs and immutable vectors. Two transfer families raise the ledger to69; no cross-game equivalence is assumed.

The complete allocation and nonempty seek/blend paths remain to recover. The actual key-search helper at002b4120 also uses DIV.S, which requires independently validated raw EE division before source promotion. Raw generated pseudocode and these callbacks do not establish complete program recovery.

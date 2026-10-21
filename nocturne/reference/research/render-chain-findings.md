Current verified checkpoint: **413 functions /462684 fresh original-instruction cases**. [Findings](texture-environment-findings.md) · [Next frontier](texture-environment-next-frontier.md). Earlier checkpoint narratives below are retained as historical records.

Historical checkpoint document: its batch counts and unresolved states describe the earlier checkpoint. Current evidence is linked above.

# Render packets, draw chains and ordering records

Current checkpoint: **388 reconstructed functions**, **456,284 entirely fresh original-instruction comparisons**, **44,556 validated original function bytes**. There are8,955 recognized functions; compiled source covers approximately4.33%. Full or near-full recovery remains unfinished.

This batch adds ten complete original bodies/820 active bytes, with sixteen excluded unreachable NOP bytes across836 contiguous bytes. No function boundaries change. The [saved Ghidra project](../ghidra/checkpoints/388-functions/Nocturne.gpr), [batch certificate](render-chain-validation.json) and [integrity report](checkpoint-388-integrity.json) retain the evidence.

| Entry | Recovered alias | Active bytes |
|---|---|---:|
| `002acc28` | `ps2DrawTagAppendReference` | 60 |
| `002acc68` | `ps2DrawTagAppendPacket48` | 52 |
| `002acca0` | `ps2DrawTagAppendCall` | 60 |
| `002acce0` | `ps2DrawChainPrepend` | 96 |
| `002acd40` | `ps2DrawChainAppend` | 84 |
| `002acd98` | `ps2DrawChainPrependOnMode1` | 36 |
| `002acdc0` | `ps2DrawOrderingInitialize` | 116 |
| `002ace38` | `ps2DrawBuildReferencePacket` | 100 |
| `002acea0` | `ps2DrawLinkReferencePacket` | 72 |
| `002acee8` | `ps2DrawTagLinkState` | 144 |

## Recovered behavior

Three append variants capture the previous tail, assign head when empty and otherwise turn the previous packet into a NEXT link with the original28-bit mask. The REF and CALL variants write their tag ID byte before reading the live tail and select tag+16 as the new tail. The other variant selects tag+48. Partial aliases distinguish these read/write orders.

The reference builder obtains32 bytes through the actual recovered work-buffer routine. It reads the source16-bit quadword count and stores a64-bit REF tag containing the masked source+16 address. It then clears the entire packet+16 quadword before reading the source+8 payload and copying it to packet+8. Overlapping source/output cases confirm that the payload read must stay after the clear. The linking wrapper changes the previous tag ID, stores the masked new address and returns packet+16. These ordinary RAM comparisons do not establish physical quadword atomicity or live DMA.

The state linker first compares slot16 and captures the previous tail in the branch delay slot. A missing next state inherits the previous state; a differing nonzero next state emits a reference packet for the next state. It then rereads both slot20 values after the first actual builder call. Finally it writes the tail ID byte before reading the live next head and linking it. The header tail is not updated by this routine. Unity names suggest light/fog roles; source retains neutral packet-state slots until an exact correspondence is justified.

Prepend accepts only a tag with a nonzero tail. Append accepts only a tag with a nonzero head and stores the previous node.next before calling the actual state linker. The conditional prepend callback uses A0=list,A1=mode,A2=tag and forwards the third argument only for mode1; the decompiler alone did not expose this interface. The fixtures execute actual recovered callees.

Ordering initialization decrements count before processing the first32-byte record, installs the actual append and conditional-prepend callback addresses, clears the accessed fields, links the following records and terminates the final next pointer. The word at+28 remains untouched. Counts1..16 are compared; count0 would underflow into the enormous original loop and is outside this corpus. No guard was added to the reconstructed behavior.

## Unity acceleration and SMT transfer

The [native Unity review](draw-reference-leads.json) provides named draw-tag, DMA-tag, packet-header and ordering-table roles. It supports following the PS2 chain without searching all functions by raw instruction similarity. Unity uses managed references, delegate dispatch and altered initialization values, so it cannot supply literal PS2 offsets or platform semantics. No new exact HD counterpart is promoted by this batch.

There are254 reviewed HD pairs,46 independent library identities and131 descriptive PS2 aliases. Four added shared-SMT patterns cover the append variants, reference construction, state reconciliation/list splicing and two-callback ordering records; the ledger now contains106 patterns. These are transfer fingerprints, requiring each target executable to be checked before names, layouts or behavior are carried across.

The [disk-only transfer review](drafts/render_chain/transfer-review.json) finds one DDS whole-body candidate for each of the ten closed rendering bodies and six private ordering/list bodies. All sixteen entries and every direct call/jump target shift by00027480; relative branches, packet-field offsets, tag literals and masks remain exact. This supports a shared render-engine cohort. DDS function boundaries, globals, indirect callback identities and original/C behavior are not yet validated, so no DDS identities are promoted.

## Verification and preservation

Ten canonical routines pass2,560 focused comparisons against freshly executed original instructions. Every comparison includes all nine RAM spans totaling1,124,848 bytes,4,608 canary bytes, raw returned bits, Status and primitive/kernel/indirect traces. All selected path modes have both initial IRQ states. Thirteen malformed rows are rejected; state restores after success, rejection and an injected output mismatch. The actual focused host DLL is frozen separately.

All388 canonical routines pass456,284 completely fresh comparisons, with no reused expected rows. The report pins91 C/header and100 verifier/input files; full capture pins208 inputs before and after execution. Fifteen ABI audit groups independently reopen the saved project. All8,955 recognized functions export and decompile with zero failures.

The exact preceding378 checkpoint preserves2,232 artifacts,185 source/verifier inputs,202 capture inputs and453,724 original rows, plus its project and snapshot. Earlier364 and preceding archives remain intact. The original runtime-state getter source/name/ABI remains reused. The2,004 historical uninitialized STOP-capture warning lines retain the same ordered sequence; the new focused capture has none.

Selected coherent packet states and aliases do not establish arbitrary callback mutation, concurrency, scheduling, physical DMA/runtime, exhaustive inputs, private-stack equivalence or a matching executable. Complete code/data discovery and full or near-full compilable source remain unfinished. [Next frontier](render-chain-next-frontier.md) identifies ordering flush, final END tags and draw-list closures.

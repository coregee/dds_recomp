Current verified checkpoint: **413 functions /462684 fresh original-instruction cases**. [Findings](texture-environment-findings.md) · [Next frontier](texture-environment-next-frontier.md). Earlier checkpoint narratives below are retained as historical records.

Historical checkpoint document: its batch counts and unresolved states describe the earlier checkpoint. Current evidence is linked above.

# Ordering flush, state prepend and draw lists

Current checkpoint: **394 reconstructed functions**, **457,820 entirely fresh original-instruction comparisons**, **44,972 validated original body bytes**. There are8,955 recognized functions; compiled source covers approximately4.40%. Full or near-full recovery remains unfinished.

This batch adds six complete original bodies/416 active bytes, with eight excluded unreachable NOP bytes across424 contiguous bytes. No function boundaries change. The [saved Ghidra project](../ghidra/checkpoints/394-functions/Nocturne.gpr), [batch certificate](ordering-flush-validation.json) and [integrity report](checkpoint-394-integrity.json) retain the evidence.

| Entry | Recovered alias | Active bytes |
|---|---|---:|
| `002acf78` | `ps2DrawTagPrependStateReferences` | 152 |
| `002ad010` | `ps2DrawOrderingFlush` | 168 |
| `002ad0c0` | `ps2DrawNodeListInitialize` | 20 |
| `002ad0d8` | `ps2DrawNodeListAppend` | 28 |
| `002ad0f8` | `ps2DrawPacketListInitialize` | 12 |
| `002ad108` | `ps2DrawPacketListAppend` | 36 |

## Recovered behavior

State prepend reads slot20 first. A nonzero slot builds a reference packet through the actual recovered allocator/builder, reads the live head after that call, replaces the head and writes the NEXT link at packet+16. It then rereads slot16 and repeats. Selected aliases preserve these live reads; the source retains neutral state-slot names.

Ordering flush calls each record callback withA0=record,A1=0,A2=0, as established by the original delay slot. It reads head after the callback, prepends state references for the first nonempty chain and joins later chains through the actual state linker. It captures record.tail after the call and reads next last. At completion it writes END byte70 at tail+3, then rereads the tail before zeroing its address word. It returns the first head.

The original callback executes without an emulator function hook. A passive observer records480 entries and their three arguments after the delay slot. The host DLL relocates the reviewed installed conditional-prepend target to its actual C implementation through an explicit boundary; unsupported raw targets abort. Selected acyclic chains contain0..4 records. Arbitrary callbacks or mutation are not established by these cases.

The node-list initializer clears fields12/0/4/8 in order. Its append captures oldtail, links or sets head, updates tail and clears node.next last. The separate packet-list initializer clears4/0. Its append reads the previous descriptor tail, then the live incoming descriptor tail, stores the latter at the captured old packet location and updates the list descriptor. Partial aliases distinguish the interfaces and read/write order. The saved project records separate accessed views for their16-byte and8-byte headers.

## Unity acceleration and SMT transfer

The [Unity draw review](draw-reference-leads.json) supplies named draw-tag, DMA-tag, packet-header and ordering-table roles that narrow the search. Managed Unity references, delegates and initialization values differ from the raw PS2 layouts. No new exact HD pair is promoted. The ledgers now contain254 reviewed HD pairs,46 independent library identities,137 descriptive PS2 aliases and109 transferable SMT patterns.

The [disk-only DDS cohort review](drafts/render_chain/transfer-review.json) finds one whole-body candidate for each of the preceding ten render routines and these six ordering/list routines. All sixteen entries and eleven direct call/jump targets share offset00027480, while relative branches, field offsets, tag literals and masks remain exact. DDS boundaries, globals, indirect targets and original/C behavior still require validation before names or layouts are transferred.

The [next private proof](draw-environment-private-review.json) adds sixteen candidates/1,764 active bytes across4,096 fresh original/C comparisons: five packet leaves and eleven actual callers/global-state routines. The leaf ABI includes raw64 arguments and a ninth raw32 argument atSP+0. Caller proofs preserve original configuration reloads and include a further4-byte BSS RAM span. Canonical integration, full regression and saved ABI reopening remain pending, so these do not increase the394 count. The expanded static DDS scan finds32 unique bodies and30 consistent direct call/jump targets with the same27480 offset; no DDS identity is promoted.

## Verification and preservation

The six canonical routines pass1,536 focused original/C cases. Comparisons cover all nine RAM spans totaling1,124,848 bytes,4,608 canary bytes, raw returned bits, Status and independent primitive/kernel/deferred/order traces. Every selected path mode has both initial IRQ states. Fifteen malformed rows are rejected and state restores after success, rejection and an injected mismatch. The actual focused DLL is frozen separately.

All394 compiled routines pass457,820 entirely fresh original-instruction comparisons with no reused rows. The report pins93 C/header and104 verifier/input files; full capture pins214 inputs before and after execution. Sixteen independently reopened ABI groups pass. All8,955 recognized functions export and decompile with zero failures.

The exact preceding388 checkpoint preserves1,579 artifacts,191 source/verifier inputs,208 capture inputs and456,284 original rows, plus its project and snapshot. Earlier archives remain intact. The original runtime-state getter is retained. The2,004 historical uninitialized STOP-capture warning lines retain the same ordered sequence; the new focused capture has none. The first focused comparison exposed a generated trace-length typo before source execution; its complete original capture and failed adapter are [preserved](diagnostics/ordering-flush-adapter/archive.json), and the corrected verifier used a new complete capture.

Selected RAM paths do not establish arbitrary callback behavior, concurrency, physical GS/DMA/runtime, private-stack equivalence, exhaustive states or a matching executable. Complete code/data discovery and full or near-full compilable source remain unfinished. [Next frontier](ordering-flush-next-frontier.md) pins adjacent packet builders and connected callers.

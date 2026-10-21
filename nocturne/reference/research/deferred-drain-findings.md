Current verified checkpoint: **413 functions /462684 fresh original-instruction cases**. [Findings](texture-environment-findings.md) · [Next frontier](texture-environment-next-frontier.md). Earlier checkpoint narratives below are retained as historical records.

Historical checkpoint document: its batch counts and unresolved states describe the earlier checkpoint. Current evidence is linked above.

# Deferred draining, work buffers and DMA links

Current checkpoint: **378 reconstructed functions**, **453,724 entirely fresh original-instruction cases**, **43,736 validated original function bytes**. There are8,955 recognized functions; compiled source covers approximately4.22%. Full or near-full recovery remains unfinished.

This batch adds14 complete original bodies/900 active bytes. The remaining-byte getter at002ACB40 was previously undefined; its16-byte return/delay-slot body now has an independently audited function boundary. The [saved Ghidra project](../ghidra/checkpoints/378-functions/Nocturne.gpr), [batch certificate](deferred-drain-validation.json) and [integrity report](checkpoint-378-integrity.json) retain the evidence.

| Entry | Recovered alias | Active bytes |
|---|---|---:|
| `002ac880` | `ps2DeferredQueueDetachActive` | 60 |
| `002ac8c0` | `ps2DeferredQueueDrain` | 208 |
| `002ac990` | `ps2DeferredQueueAdvance` | 116 |
| `002aca08` | `ps2DeferredQueueIsBusy` | 92 |
| `002aca68` | `ps2DeferredQueueIsBusyAtomic` | 72 |
| `002acab0` | `ps2WorkBufferReplace` | 108 |
| `002acb20` | `ps2WorkBufferSelect` | 32 |
| `002acb50` | `ps2WorkBufferTake` | 32 |
| `002acb70` | `ps2WorkBufferGetCursor` | 8 |
| `002acb78` | `ps2WorkBufferSetCursor` | 20 |
| `002acb90` | `ps2DmaChainInitialize` | 40 |
| `002acbb8` | `ps2DmaChainAppend` | 48 |
| `002acbf0` | `ps2DmaChainAppendWithTail` | 48 |
| `002acb40` | `ps2WorkBufferGetRemaining` | 16 |

## Recovered behavior

Detach captures and clears the active chain, then clears each owning queue node pointer through live next pointers. Drain captures each owner callback, executes real recovered empty, memory-free or array-free callbacks for the selected fixtures, reads the previous block after those calls, and releases actual pool blocks and nodes. It executes at least one callback for a nonnull block even when its wrapping used count iszero; the loop compares sign-extended32 counters as signed64 values. Older blocks contain63 payload slots.

The pump writes only the processing low byte, waits on the shared semaphore, drains the oldest generation, shifts pending to oldest once and detaches active into pending. It rereads the semaphore before storing pending, signals and clears the low flag byte. The busy query checks the flag, active chain and two older generations. Its atomic wrapper disables interrupts, samples once and restores the original enabled state; it does not wait for idle.

Work-buffer replacement frees an old handle, rounds the requested half size up128 with raw32 wrapping, allocates twice that size, acquires the actual pointer and stores two halves. Selection captures the extent before the indexed half-pointer read. Taking space rounds16 and returns the previous cursor; setting the cursor rounds16. Remaining bytes are raw end-minus-cursor, including wraparound. These routines contain no added bounds checks.

DMA-chain initialization preserves the original store sequence across the32-byte record. Append captures the old tail; a nonnull tail receives byte20 at+3 and a28-bit masked link at+4 before the final tail store. The three-argument variant uses an explicitly supplied tail. Inputs include partial aliases to the chain and work-buffer globals, so byte width and live store order are checked. NEXT-ID interpretation is supported by the [primary PS2SDK DMA tag header](https://raw.githubusercontent.com/ps2dev/ps2sdk/master/ee/dma/include/dma_tags.h); the game-specific mask is retained.

## Unity reference and transfer

The [named native Unity review](draw-reference-leads.json) adds useful draw-tag roles. `sdfDrawTagInit` clears managed next/head/tail and packet state; `sdfDrawTagLink` chooses the head when empty, otherwise changes the previous DMA tag to NEXT and replaces the tail. The PS2 initializer uses raw0000FFFF, while Unity represents65535 as float477FFF00. Managed objects, array checks and64-bit references differ from PS2 fields. These are recorded leads; no new HD counterpart is counted.

The ledger retains254 reviewed HD pairs and46 independently identified library routines;14 new descriptive aliases bring the alias count to121. Five added shared-SMT patterns cover detaching/generation advancement, captured-callback draining, the IRQ-restored busy snapshot, double work buffers and DMA tail linking. There are102 transfer patterns.

The static DDS scan finds10 unique masked body candidates. Additional pump and selector candidates differ only in displacements reached through computed GP bases, which the strict direct-GP mask leaves untouched. The tiny cursor getter is nonunique. These are target investigation leads; DDS boundaries, globals, callees and behavior remain unvalidated.

## Verification and preservation

The canonical14-function suite passes4,352 freshly executed original/C cases. It compares all nine RAM spans totaling1,124,848 bytes,4,608 canary bytes, returned bits, Status, instruction primitive counts and kernel/indirect-call traces. Selected paths have both initial IRQ states. Thirteen malformed rows are rejected; owners, bindings, counters and traces restore after success, rejection and an injected output mismatch. A frozen copy of the actual focused host DLL is retained.

All378 canonical functions pass453,724 completely fresh cases, with zero reused expected rows. The source report pins89 C/header and96 verifier/input files; full capture pins202 inputs before and after execution. Fourteen saved ABI audit groups independently reopen the new project. All8,955 recognized functions export and decompile with zero failures.

The preceding364 checkpoint retains1,657 exact artifacts,179 source/verifier inputs,196 capture inputs and449,372 original rows, with its saved project and snapshot intact. The original runtime-state getter source/name/ABI is reused. Older345 and preceding archives remain separate. The2,004 old uninitialized STOP-capture warning lines have the same ordered sequence as before; the new focused4352-row capture has none.

Explicit syscall values do not establish physical scheduling, concurrency or interrupt timing. Arbitrary callback mutation/reentrancy, private stack, exhaustive inputs, hardware DMA/runtime, complete code/data discovery, near-full compilable source and a matching executable remain unfinished. [Next frontier](deferred-drain-next-frontier.md) records the unresolved render/order chain and callers.

Current verified checkpoint: **413 functions /462684 fresh original-instruction cases**. [Findings](texture-environment-findings.md) · [Next frontier](texture-environment-next-frontier.md). Earlier checkpoint narratives below are retained as historical records.

Historical checkpoint document: its batch counts and unresolved states describe the earlier checkpoint. Current evidence is linked above.

# PS2 heap, arena initialization and deferred enqueue

Current checkpoint: **364 reconstructed functions**, **449,372 entirely fresh original-instruction cases**, **42,836 validated original function bytes**. The executable has8,954 recognized functions; source coverage is approximately4.07%. Full/near-full recovery remains unfinished.

This batch adds 19 complete bodies totaling 4,676 function bytes and reuses the previously recovered runtime-state getter. The [saved Ghidra project](../ghidra/checkpoints/364-functions/Nocturne.gpr), [batch certificate](heap-queue-validation.json) and [integrity report](checkpoint-364-integrity.json) retain the original byte, source, ABI and fresh execution evidence.

| Entry | Recovered alias | Function bytes |
|---|---|---:|
| `002a8f00` | `ps2MemoryArenaInitialize` | 180 |
| `002d38f0` | `ps2HeapMalloc` | 84 |
| `002d3be8` | `ps2HeapMallocReentrant` | 1788 |
| `002d3990` | `ps2HeapGrow` | 584 |
| `002d9998` | `ps2HeapFree` | 744 |
| `002d9c90` | `ps2HeapTrim` | 364 |
| `002d5250` | `ps2HeapSbrkReentrant` | 88 |
| `002dc5a0` | `ps2HeapSbrk` | 172 |
| `002dbd90` | `ps2KernelGetThreadId` | 16 |
| `002dbee0` | `ps2KernelWaitSema` | 16 |
| `002dbec0` | `ps2KernelSignalSema` | 16 |
| `002dbe80` | `ps2KernelEndOfHeap` | 16 |
| `002dbea0` | `ps2KernelCreateSema` | 16 |
| `002d4618` | `ps2HeapLock` | 124 |
| `002d4698` | `ps2HeapUnlock` | 76 |
| `002a8080` | `ps2CreateSemaphore` | 40 |
| `002ac760` | `ps2DeferredQueueInitialize` | 80 |
| `002ac7b0` | `ps2DeferredQueueAppend` | 208 |
| `002b2db0` | `ps2MatListReleasePolicy` | 64 |

## Recovered behavior

The arena initializer executes the recovered underlying malloc, retains requested size and raw base, allocates a real16-byte pool descriptor, rounds its usable extent to128-byte boundaries, initializes the root/tail links and creates the memory-free deferred queue. The original initializer has no malloc-failure guard before writing descriptor state.

The underlying heap uses16-byte allocation alignment and eight-byte chunk headers. It normalizes wrapping request+19 to a minimum16, tries small exact bins or sorted large bins, splits/rebins a last remainder, scans a grouped bitmap and finally splits the top chunk. Size indexing changes at5,21,85,341 and1365 units of512 bytes. The reconstructed code retains the original index<63 scan skip and signed64 extent-difference comparisons. Free coalesces adjacent free chunks, preserves last-remainder ownership, writes the footer, and inserts into size bins or the top.

Heap growth requests real break updates, handles contiguous and discontiguous extents, aligns payloads to16 and the end to4096, and fences/releases the old top. Trimming checks the current break, attempts a page reduction and re-queries on failure. Selected failure cases alias the reentrancy error head with allocator globals. The32-bit total wraps; maximum statistics compare its sign-extended value as unsigned64. The global error slot can differ from the current reentrancy error head.

Reentrant locking obtains the thread identifier, waits only when owner differs, stores the owner before rereading depth, and increments wrapping depth. Unlock decrements before branching and resets ownership before signalling when depth becomeszero. The malloc wrapper nests a lock around the internal allocator lock.

Deferred enqueue waits on the shared semaphore, creates a real16-byte queue node when absent, and chains real256-byte blocks holding63 raw entries each. NULL enqueue is a no-op. The append captures the semaphore identifier before the final payload/count stores. Material-list policy now calls this real enqueue path or immediate generic-array free. Queue draining and callback execution remain the next connected work.

## Unity reference and SMT transfer

The named Unity `sdfMemory` initializer constructs managed handles, a list and a capacity256 array. Those objects guide structural investigation, while the PS2 libc bins, break growth and semaphore locks require original PS2 evidence. No new HD counterpart is promoted. The existing254 reviewed HD pairs and46 library identities remain;19 new descriptive aliases bring the PS2 alias ledger to107.

Five new shared-SMT fingerprints cover libc size bins, break growth/trimming, reentrant locks, deferred enqueue and arena initialization. The transfer ledger contains97 patterns. The [read-only DDS scan](drafts/heap_queue/reference-review.json) retains relative branches, syscall selectors and ordinary constants while masking relocations. Its candidates are not DDS behavior validation. Several underlying heap bodies have no complete masked match, and small pointer-getter patterns are nonunique.

The five syscall selectors agree with the [primary PS2SDK syscall table](https://raw.githubusercontent.com/ps2dev/ps2sdk/master/ee/kernel/include/syscallnr.h): thread ID2F, end of heap3E, semaphore creation40, signal42 and wait44. This supports the service names; the original game library version remains unconfirmed.

## Verification and preservation

The focused20-body suite passes5,952 freshly executed original/C cases. It compares nine complete mutable RAM spans totaling1,124,848 bytes,4,608 canary bytes, observable raw32 returns, Status, instruction primitive counts and syscall argument/result traces. Inputs cover large size-bin boundaries, wraparound, coalescing, nested locks, allocation/growth failures, trimming recovery, queue block boundaries and immediate/deferred release. Every selected path has both initial IRQ states. Original saved registers and return state are checked; the full capture also varies saved floating-point registers.

The canonical adapter calls all 20 real exports, including the existing `ps2GetRuntimeState` pointer getter. Its original source, library identity and saved ABI are retained. Twelve malformed rows are rejected, and owners, bindings, Status, primitive values, traces and counters restore after success, rejection and an injected output mismatch. The first out-of-pool immediate-release fixture is preserved as rejected diagnostic evidence. A passing 4,096-case suite and the first canonical preflight are also preserved. A later 365-name comparison passed but contained the already recovered runtime getter under a second alias; the annotation guard rejected it before mutation. That unpublished attempt is preserved, and this checkpoint freshly reruns all rows with 364 unique functions.

All364 canonical functions pass449,372 entirely fresh original-instruction comparisons, with zero reused expected rows. The source report pins87 C/header and92 verifier/input files; capture pins196 inputs before and after execution. Thirteen saved ABI groups reopen independently. All8,954 recognized functions export and decompile with zero failures; function boundaries are retained.

The preceding345 checkpoint retains1,246 exact artifacts,172 source/verifier inputs,189 capture inputs and443,420 original rows. Its saved project and snapshot remain intact. The332/326 and earlier archives remain preserved.

The kernel boundary supplies explicit syscall return sequences and compares the arguments and results. It excludes physical scheduling, timing and unwritten semaphore fields; only the original initialized CreateSema fields4/8/20 enter the trace. Private callee stack, exhaustive inputs/valid heap states, hardware/runtime and a matching executable remain separate.

[The next frontier](heap-queue-next-frontier.md) pins deferred detachment/draining, the three-generation queue pump, idle queries and work-buffer lifetime. Full/near-full recovery remains the active goal.


A [separate private review](deferred-drain-private-review.json) now validates 13 queue-draining, work-buffer and DMA-chain routines in 3,840 cases. It also records a previously unrecognized 16-byte remaining-space getter at002ACB40 that passes512 cases. These candidates are not included in the saved364-function checkpoint; their integration and the new boundary audit remain the next work.

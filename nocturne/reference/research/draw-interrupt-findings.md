# Draw cleanup interrupt prerequisites

Seven PS2 routines are integrated in `src/draw_interrupt.c`, compile as C11 with
MSVC `/W4 /WX /O2`, and pass **3,584 original-instruction comparisons**,512 each.
Interfaces were saved in the working Ghidra project and independently reopened;
seven selected exports decompile with zero failures. No game-function hooks supply
wake or handler-wrapper results; actual original bodies and canonical C execute.

| Nocturne entry | Chosen alias | Bytes | Constrained DDS candidate |
| --- | --- | ---: | --- |
| 002aad88 | ps2DrawResetCompletedRecord | 20 | 002d2128 |
| 002aada0 | ps2DrawDmaInterrupt | 40 | 002d2140 |
| 002dcd50 | ps2DrawWakeThread | 148 | 0030b8d0 |
| 002dbde0 | ps2KernelInterruptWakeThread | 16 | 0030a960 |
| 002dbed0 | ps2KernelInterruptSignalSema | 16 | 0030aa50 |
| 002dbbc0 | ps2KernelAddDmaHandler | 16 | 0030a740 |
| 002dbbd0 | ps2KernelRemoveDmaHandler | 16 | 0030a750 |

Current recovery is **452 /8,956 recognized functions (5.05%)**,51,724 summed
original body bytes and **474,972 aggregated comparisons**. Last full validation
remains413/462,684; seven focused groups add39 functions/12,288 cases. This is
not a new full run. There are256 reviewed HD counterparts,46 library identities,
193 descriptive PS2 aliases and135 transfer patterns. These seven are chosen
PS2 aliases/raw EE interfaces, not exact Unity counterparts or original typedefs.

Record reset clears offsets10/4/8/chex in that order and retains word0. The DMA
interrupt callback ignores A0, passes complete A1 to the actual wake dispatcher,
then executes SYNC0 and EI on every path and returns sign-extended-1. EI updates
Status only when permitted by the existing instruction value model; its instruction
still executes when blocked. Comparisons include232 changed and280 unchanged
callback Status cases, raw ignored-channel bits and pre-EI syscall/SYNC snapshots.

The dispatcher queries the kernel with sign-extended selector-2fhex and compares
the full64 current-thread value with the full64 target. Other-thread calls execute
actual-34hex wrapper and forward its raw syscall return. Self calls require an
unsigned current<100hex and nonzero full word52c2ac; otherwise they return-1.
Eligible self calls load and sign-extend signal handle59b170 before queue writes,
read cursor59b17c, mask its old value1ff, write masked_index+1 without another
mask, then store byte pair0/low8(current) at59b180+2*old_masked_index. The actual
-43hex signal wrapper executes after those stores; its result is ignored and the
original current-thread value is returned. Stored cursor200hex is intentional.

All four syscall wrappers retain raw arguments/returns and full sign-extended
negative selectors. Add/remove handler selectors12/13hex take four/two argument
lanes. The controlled syscall boundary changes only V0 and records selectors,
declared arguments, supplied return, queue cursor/pair and processor Status.
These snapshots establish queue writes before the signal call, and syscall/SYNC
order before EI, within the value model. Original kernel code, scheduling and
asynchronous interrupt delivery are not executed.

Tests compare all **1,392 declared memory bytes**, raw64 results, full boundary
traces, EI counts and Status. Reset cases include384 global/queue aliases. Across
dispatcher/callback cases there are128 eligible self enqueues,128 disabled-self
cases,128 each above-limit/negative/high-lane self cases and384 other-thread cases,
including equal low words with different high words. Thread values include0/255
and the rejected256 boundary. Raw cursors include0/1/510/511/512/80000000/ffffffff;
36 eligible cases retain stored512. The two syscall-result slots cover ignored
signal returns and forwarded wake returns. Backed finite addresses, supplied kernel
values and the existing EI/SYNC value model do not establish PS2 runtime, physical
synchronization, parent cleanup behavior or a matching executable.

`draw-interrupt-transfer.json` compares these seven bodies and their340-byte
cleanup caller002aadc8 against the DDS executable. There are eight constrained
body anchors, six agreeing direct-call constraints and one agreeing callback
address constructor. The AddDmaHandler pattern alone has two DDS candidates,
0030a730/0030a740; the unique cleanup caller002d2168 calls0030a740. Both raw candidates
remain recorded rather than being erased. All other bodies have one candidate.
Only J/JAL, GP-relative loads and explicitly listed address-construction immediates
are masked; other words/constants/registers/relative branches agree. Wake globals
map to DDS enable39c454, queue406ff8 and signal handle406ff0. These are static DDS
leads; no DDS import, annotations, C/runtime comparison or original names are claimed.

Evidence is one current `draw-interrupt/` capture, validation/interface/ABI reports,
the static transfer report and three shared SMT patterns. Existing canonical source
and bindings were not changed, so broader regression was not repeated.

Next integrate the actual cleanup002aadc8 and then consumer002adb98 with populated
fixtures. Cleanup caches list/packet/tag under the semaphore, invokes actual reset,
signals the semaphore, optionally installs the actual callback and submits a DMA
chain, sleeps and removes the handler, then releases list payloads/nodes using
cached next links. Its002a8bd8 release callee is recovered `ps2PoolRelease` from
`material_construction_release.c`, not the general heap-free implementation;
type1 uses actual `ps2MemoryHandleFree`, type2 releases the pointer at node+4, and every node is
pool-released. Preserve real page/class/refcount and interrupt behavior when
building the populated fixture. Frame relocation for a nested console renderer
must use the caller's actual SP rather than the standalone test's fixed entry SP.

Subsequent integration: [populated cleanup findings](draw-cleanup-findings.md)
records512 cleanup cases and128 actual callback deliveries at a controlled
SleepThread boundary. The standalone batch totals and next-step text above
describe the prerequisite batch at its publication; current totals are in
`recovery-progress.json`.

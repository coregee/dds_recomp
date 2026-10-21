# Tracked interrupt removal and movie-system startup

Five complete routines in `src/interrupt_lifecycle.c` add 396 recognized body
bytes and 320 passing original-instruction/C comparisons. All 71 non-delay root
instruction addresses are reached. The C compiles with warnings treated as
errors. Interfaces are saved in the working project, independently reopened,
and all five selected exports are merged into the current executable inventory.

| PS2 entry | Recovered routine | Body bytes | Complete DDS counterpart |
| --- | --- | ---: | --- |
| 002dbb30 | ps2KernelRemoveSbusHandler | 16 | 0030a6b0 |
| 002a83f8 | ps2InterruptHandlerRemove | 212 | unresolved |
| 002a84d8 | ps2InterruptHandlersClear | 48 | unresolved |
| 0022b840 | ps2MovieSystemInitialize | 64 | 002700d0 |
| 0022b808 | ps2MovieUpdateProcess | 56 | 00270098, initializer-anchored |

Removal compares the sign-extended current pointer with the full requested EE
value. It unlinks a matched node before issuing kernel calls. Kind 0 disables
INTC, performs SYNC0, then removes its handler; kind 1 removes DMAC; kind 2 removes
SBUS using only the cause. Cause and handler words are sign-extended on loading.
Other kind words skip kernel removal but still release a matched node, unlike
registration's fatal handling of unsupported kinds. Actual pool or memory-handle
pointer release executes, including the final pool slot's page release.

The original non-head traversal is unusual. After a mismatch, BNEL's delay slot
moves the requested pointer into the link slot and reloads that requested node's
next pointer. It does not advance from the current node. A terminal requested
non-head therefore returns without removal; a nonzero different successor can
repeat indefinitely. A self-successor can match on the second iteration and
release the requested node while leaving the original global head unchanged.
These finite behaviors and same-low-pointer/raw64 identity mismatches are tested.
The source preserves repeated volatile LW/SW accesses rather than replacing
this with a conventional list unlink. Arbitrary infinite cases remain unverified.

Bulk clear repeatedly reloads head 00551820 and removes that head. Empty and
mixed lists of one through four nodes include supported and unsupported kinds,
pool slots and a memory-backed handler. Independent checks account for 166
actual releases, exact kernel argument order, page use counts, cleared handle
state and the final head. The bulk loop works through head removal and does not
depend on the unusual non-head traversal.

Movie-system initialization executes the real IPU/handler/DMA-enable/thread
startup, then the actual process constructor with name 0053f3d8, priority 0x385,
start delay 1, shutdown delay 0, callback 0022b808, null shutdown callback and data.
Its raw result is the process pointer returned by the constructor. Independent
checks verify all 64 process descriptors and insertion before or after an existing
process, plus 640 ordered FIFO quadwords and the underlying handler/thread packets.
The constructor does not dispatch the delayed process in these comparisons.

The callback's original entry is 0022b808. Ghidra previously began at 0022b810,
omitting `LHU v0,GP-0x5944` and `LI a0,60` before DIV. The initializer's literal
callback address and original bytes establish the correct start. The old entry
is retired in place, and its 48-byte body becomes 56 bytes without changing the
8,956-function inventory. The discovery ledger and rolling exports use the
corrected entry. This restores eight previously unowned instruction bytes.

The callback divides 60 by the halfword at 0054e82c, passes the quotient to the
actual frame-update routine and returns zero. Its 64 cases cover divisors from
1 through 65,535, quotient zero, empty and two-decoder owned lists, state/rate
accumulation, both frame slots, frame availability, loop reset and populated
upload queues. Independent checks verify frame counts and accumulators through
real delivery, semaphore-protected upload linking and frame consumption. A zero
rate retains the original BREAK7 exception path; that delay-slot trap is untested.

The 320 cases execute 73,643 original steps, 18,628 trace words and 128 MMI
instructions. Full declared RAM, defined raw64 results, Status and ordered
kernel/interrupt/MMIO/FIFO observations agree. Game/library callees execute;
kernel results and incoming finite hardware values are external. Physical
interrupt delivery, IPU/DMA/cache behavior, scheduler dispatch, playback,
malformed pointers, exhaustion and a matching executable remain unverified.
The affected nine-function frame group also passes its 576 current comparisons;
those repeated checks do not add new cases to the aggregate below.

DDS has three complete counterpart spans. The complete initializer uniquely
anchors callback 00270098. All 56 callback bytes agree after masking only its
explicit GP-relative rate displacement and JAL destination. Original ELF REGINFO
gives Nocturne GP 00554170 and DDS GP 003c0cf0; rate addresses are consequently
0054e82c and 003ba72c. Both callbacks use the same constant 60 and division/return
sequence. DDS startup 002ec850 and frame update 002ec5e0 are caller-derived leads
without complete-body equivalence. Removal/clear remain unresolved under the
current full-span search. These are static findings, not DDS execution proof.
Unity's managed movie implementation does not establish identities for these
native platform bodies; no HD counterpart is added in this batch.

Current recovery is 817/8,956 functions (9.12%), 574,167 aggregated comparisons
and 131,048 summed recognized body bytes. The last full run remains 413/462,684;
404 additional routines contribute 111,483 focused cases. This is focused
evidence, not a new full-suite run. Continue movie script wrappers
0022b880/0022b8a8/0022b8c8/0022b8f0 and their actual VM argument/result helpers
0010b5c8/0010b790, then broader script and field execution using the HD reference.

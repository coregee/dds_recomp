# Populated draw cleanup

`src/draw_cleanup.c` recovers `002aadc8`, chosen alias
`ps2DrawCleanupCompleted`, a 340-byte body. It compiles under MSVC C11
`/W4 /WX /O2` and passes **512 comparisons against original instructions**.
The saved void interface was independently reopened in the working Ghidra
project; the selected export decompiles without failure. The original callers
ignore incidental V0, so void is a chosen verification interface.

Current recovery is **453 /8,956 recognized functions (5.06%)**, with
52,064 summed original body bytes and **475,484 aggregated comparisons**.
The last full run remains413/462,684; eight focused groups add40 routines and
12,800 cases. There are256 reviewed HD counterparts,46 library identities,
194 descriptive PS2 aliases and136 shared SMT patterns. These totals do not
establish full source recovery, complete code discovery or a matching executable.

Cleanup waits on record581018's semaphore, then caches list+4, packet+chex and
tag+10hex before calling the actual ordered reset. It signals using a late load
of semaphore word0. When a packet exists it queries the thread, installs the
actual DMA callback, writes zero to tag+8 before writing005293a020000000 to tag,
sets channel1 control bit40hex, flushes the cache, sends the chain, sleeps and
removes the handler. The thread word is sign-extended into the handler argument;
the handler result remains full64 through removal.

The cached list is walked after submission. Each node's byte12 type and word0
next pointer are loaded before releases: type1 frees its memory handle at+8,
type2 pool-releases the pointer at+4, and every node is pool-released. Actual
`ps2PoolRelease`, descriptor unlink/coalescing and related pool callees execute.
The release at002a8bd8 is a pool operation, not general heap free.

Fixtures cover409 populated lists with zero through four nodes, allocated and
free neighboring descriptors, empty/held/full pool pages,256 submissions,
32 tag/shared-record aliases and26 tag/node-type aliases. Thirteen spans totaling
97,892 bytes are compared, along with ordered syscall arguments/results,
DMA register reads/writes, DI/EI/SYNC and Status. Cached links must survive
release-time changes; type reads retain the effect of overlapping tag stores.

**128 deliveries execute the actual interrupt callback and wake dispatcher**.
Delivery is a controlled stimulus at the SleepThread syscall return. The
original emulator saves interrupted128-bit register lanes and Status, runs
002aada0 and its actual callees, then restores the interrupted context and
resumes cleanup. The canonical boundary does the corresponding callback and
Status restoration. Both self/other-thread paths and queue cursor boundaries
are included. No callback or high-level release function is replaced by a stub.
Kernel return values and ready DMA register reads remain supplied external
boundaries. This does not execute original kernel scheduling, physical DMA or
an actual hardware interrupt.

Affected existing draw/support, DMA, graphics and interrupt comparisons pass
3,328/1,024/768/3,584 cases respectively against their retained original captures.
Existing canonical callees remain unchanged. No new full regression is claimed.
One current cleanup capture is kept, and Ghidra changes were saved in place;
no checkpoint, project copy or duplicate capture was created.

The constrained DDS body candidate002d2168 and its call/callback relationships
are already recorded in `draw-interrupt-transfer.json`. The new shared pattern
describes cached release and interrupt submission order. DDS source/runtime
equivalence and an exact Unity counterpart are unproved.

Next recover the1152-byte request consumer002adb98 using these actual callees,
populated requests and controlled external boundaries. Nested console rendering
must relocate against the consumer's actual SP, rather than its standalone
fixture's fixed entry SP.

Evidence: `draw-cleanup-validation.json`, `draw-cleanup-interfaces.json`,
`draw-cleanup-abi.json`, the current `draw-cleanup/` capture, selected export
`ps2/whole-program/functions/002aadc8.json`, and
[interrupt and DDS constraints](draw-interrupt-findings.md).

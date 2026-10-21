# Native file open, close, seek, read and write

Five complete C bodies add2,912 original body bytes and pass1,920 comparisons
against original PS2 instructions. All defined root returns, the local result word,
62,808 bytes of declared storage, Status and kernel/cache/SIF/MMIO/handler/interrupt
traces agree. The host C build passes with warnings treated as errors. Existing
initialization, lock/descriptor, RPC/cache/packet, response/completion and copy bodies
execute directly.84 Open cases enter the actual initialization chain. The tests
include904 actual client-response arrivals and520 actual file-completion arrivals,
including186 early completion arrivals in asynchronous seek/read/write cases.

Open preserves live bounded path copying, the6fffffff flag mask, descriptor
reservation and flags/handle commit after completion. Failed submissions retain
the reserved descriptor as the original does. Close clears flags after accepted
RPC submission, even when the later uncached acceptance word iszero. Seek/read/
write preserve first-free pending-ID reservation, negative semaphore encoding,
full-table behavior, async returns and native failure cleanup. Read retains its
additional record/request cache flushes. Write computes the short unaligned prefix
with signed full64 size comparison, copies from uncached memory and preserves
cached/uncached distinction. Raw high pointer lanes, sizes, invalid raw64 descriptor
IDs, errors, path limits/aliases, buffer residues and pending positions are covered.

Four complete DDS bodies match uniquely under explicitly enumerated absolute
address and J/JAL relocation masks, with44 agreeing actual callee targets. Native
read has no complete DDS match; no DDS identity is assigned. Shared request and
client relationships agree, but nearby data offsets differ:

| Relative layout | Nocturne | DDS |
|---|---:|---:|
| Request buffer from RPC queue | +0x80 | +0x80 |
| Client from descriptor table | +0x200 | +0x200 |
| Cached reply from descriptor table | -0x480 | -0x8c0 |
| Initialized flag from descriptor semaphore | -0x8 | -0xc |
| Pending table from descriptor semaphore | -0x88 | -0x90 |
| Async semaphore from descriptor semaphore | +0x4 | +0x4 |

Kernel/syscall/MMIO values, ordinary reply bytes and arrival order are boundaries.
The runner invokes the original response/completion instruction bodies during waits;
the host bindings invoke their recovered C counterparts. This does not execute the
IOP, filesystem, hardware transfer, scheduling or cache coherence. Fresh/repeated
service setup and returning DI states are bounded by the prior initialization model.
The initial local result word and never-written RPC semaphore option are explicit
stack operands. This matters when operation-semaphore creation fails: the original
does not check that failure directly, and the result word can remain untouched.
That behavior is preserved, rather than assigning an invented file result. Host
stack-result addresses are adapted to backed storage; arbitrary malformed pointers,
physical runtime and matching-executable validation remain outstanding.

The generic worker002be8c8 calls all five recovered APIs. Close/detach002be838
and its error wrapper002be878 are now connected next targets, followed by the worker
loop, movie-specific services, loader scheduler/pump and moon integration. Working
Ghidra interfaces and current exports are saved in place; no checkpoints were made.

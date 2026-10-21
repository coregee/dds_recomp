# Libc stream records, callbacks and buffer setup

Eighteen complete native bodies are reconstructed in `src/libc_stream.c` and
its header, adding 1,756 original body bytes and 1,408 passing comparisons.
The affected C builds with warnings treated as errors. Interfaces were saved
in the working Ghidra project, reopened and checked, and all eighteen current
assembly/pseudocode exports merged into the rolling index. No checkpoint or
project copy was made.

| PS2 entry | Recovered function | DDS complete-span result |
| --- | --- | --- |
| 002d96f8 | ps2LibcStreamRecordInitialize | 002fe578 |
| 002d9908 | ps2LibcStreamsInitialize | 002fe788 |
| 002da308 | ps2LibcLocaleRecord | 29 candidates; unresolved |
| 002da340 | ps2LibcLocaleConvention | 3 candidates; unresolved |
| 002dc650 | ps2LibcIsatty | 0030b1d0 |
| 002dc658 | ps2LibcFstatStub | 0030b1d8 |
| 002db950 | ps2LibcFstatReentrant | 002ff2e8 |
| 002dc588 | ps2LibcCloseUnsupported | 0030b108 |
| 002dc598 | ps2LibcSeekUnsupported | 0030b118 |
| 002db8f8 | ps2LibcCloseReentrant | 00305d60 |
| 002db9b0 | ps2LibcSeekReentrant | 003078f0 |
| 002db7c0 | ps2LibcStreamClose | 00301780 |
| 002db758 | ps2LibcStreamSeek | 00301718 |
| 002d95e0 | ps2LibcFlush | 002fe460 |
| 002da1e0 | ps2LibcStreamWalk | 002ff348 |
| 002d98c8 | ps2LibcStreamsCleanup | 002fe748 |
| 002da360 | ps2LibcMakeBuffer | 002ff3e0 |
| 002d8038 | ps2LibcPrepareWrite | 00305c18 |

These names describe the observed PS2 behavior. Exact SDK version, original
source spelling and Unity identities are not established for this group.

## Stream layout and native behavior

A stream record is 88 bytes. Pointer/read count/write count are at 0/4/8;
flags and descriptor are halfwords at 12/14; buffer base/size/line buffer are
at 16/20/24. Cookie is at 28, with read/write/seek/close callbacks at
32/36/40/44. Unget storage is at 48, its inline buffer at 64, the fallback
byte at 67, seek block at 76, cached offset at 80 and reentrancy context at 84.
Record initialization preserves fields it does not write. Context initialization
sets cleanup at 60 and initialized at 56, builds the three records at
484/572/660, then writes the glue node at 472/476/480.

The original descriptor bodies are literal stubs: isatty returns one; stat
writes eight zero bytes at output+72 and mode 0x2000 at output+4, then returns
zero; close and seek return minus one without setting errno. Reentrant adapters
clear global errno at 0x552178 before executing these real stubs. Stream seek
clears its valid-offset bit on failure. The unreachable success and errno paths
remain in the complete source rather than being replaced by host libc behavior.

Flush normalizes the context and initializes it when needed. It rewinds the
stream pointer before executing the current write callback and preserves the
original order of count subtraction and full 64-bit return testing. Failure
sets flag 0x40. The stream walker caches count and record pointer per glue node,
steps by 88 bytes, combines full callback returns with OR and reloads the next
node after callbacks. Cleanup invokes that real walker with Flush.

Buffer setup executes the actual stat adapters and recovered heap allocator.
A successful 1,024-byte allocation is line buffered for the native character
mode; allocation failure or the unbuffered flag selects the inline fallback
byte. Prepare-write converts read state, releases dynamic unget storage through
the real recovered heap, and preserves signed counts and word wrapping.

## Comparison evidence and limits

`libc-stream-validation.json` records 79,654 original instruction steps and
6,379 ordered trace words across the 1,408 cases. Defined returns, all 100,500
declared RAM bytes, Status and callback/kernel/interrupt/SYNC traces agree.
Actual recovered heap, descriptor stubs, errno adapters and selected callbacks
execute. The callback set includes Flush, StreamClose, Isatty, unsupported Close
and PollSema; the complete TTY read/write backend and main formatter remain
unfinished. External kernel results are supplied at the kernel boundary.

The current DLL also passes the retained 5,952 heap, 1,344 disc-platform and
2,250 CD cases affected by the test adapter changes. These reuse existing
captures and do not add duplicate cases to the recovery totals. The last full
source comparison remains unchanged; its verifier hashes differ because the
adapters changed. No new full-suite comparison is claimed.

The private 80-byte C stat output is temporarily registered at a guest-local
address so the real stat bodies can write it. This validates its consumed data;
it does not establish identical private stack layout.

Thirteen selected non-delay instruction addresses cannot execute with the linked
native stubs: three in FstatReentrant require stat failure; two in StreamSeek
require seek success; eight in MakeBuffer require stat failure or regular-file
mode. Their addresses and reasons are explicit in the report. Every other
selected non-delay address is reached. This is not a claim of every possible
branch traversal, malformed or cyclic glue handling, arbitrary asynchronous
reentrancy, physical PS2 behavior or a matching rebuilt executable.

## Transfer and next dependencies

`libc-stream-transfer.json` uniquely resolves sixteen of eighteen complete DDS
spans. Thirty call/callback links and ten repeated global-address constraints
agree. Only explicit address construction and J/JAL destinations are masked;
record stride, field offsets, flags, branch geometry and other instruction words
remain fixed. The two tiny locale helpers retain 29 and three candidates.

Seven additional read/write/errno/console/free bodies have unique static matches
and remain leads, without source promotion. The malloc dependency has no
complete-span match. These results are static comparison evidence, not DDS
runtime validation; the DDS executable and project were not changed.

Next recover actual stream read/write and console transport, vector writes and
the main printf formatter, including its floating conversion dependencies. This
will let movie archive readiness, seek and sector reads execute their complete
diagnostic paths. The native fatal body at 002a82b0 saves arguments and spins
forever; it must remain nonreturning.

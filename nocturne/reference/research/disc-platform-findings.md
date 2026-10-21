# Disc and movie platform prerequisites

Nine complete routines are now recovered in `src/disc_platform.c`. They add
496 original body bytes and 1,344 passing original-instruction/C comparisons.
The saved working Ghidra project was reopened to check all nine interfaces;
all nine current exports were refreshed and merged into the 8,958-function
inventory. The instruction capture and host build are rolling outputs.

| PS2 entry | Recovered role | Comparisons |
| --- | --- | ---: |
| 002def38 | Serial-aware RPC busy check | 256 |
| 002cb6f0 | Disc semaphore initialization | 128 |
| 002dbef0 | PollSema syscall wrapper | 64 |
| 002dbda0 | ReferThreadStatus syscall wrapper | 64 |
| 002dbc20 | Alarm syscall wrapper, selector FC | 64 |
| 002cb328 | Disc alarm semaphore callback | 128 |
| 002cb350 | Disc temporary-semaphore delay | 256 |
| 002a8508 | File alarm thread-wakeup callback | 128 |
| 002a8520 | File cancel/alarm/sleep delay | 256 |

The RPC check first reads the client's packet pointer. A null pointer is idle;
otherwise the client's word4 serial must equal the packet's word24 serial before
packet word16 bit0 can report activity. This protects against a packet being
reused for a different request. Tests include mismatched serials, packet/client
field aliases, unaligned backed addresses and raw argument high lanes.

Disc initialization reads globals52a028/52a02c. If either is -1 it recreates all
three semaphores, including overwriting any previously valid handle. Each has
maximum1 and option0; initial counts are1,1,0. It writes N/S/completion handles
at52a028/52a02c/52a020, then clears busy52a030. Kernel failures do not introduce
a new early return or rollback.

The disc delay creates a temporary semaphore, installs callback002cb328 with
the semaphore in A2, waits, then deletes the semaphore. These calls still occur
if an earlier call returned failure. The callback calls actual interrupt
SignalSema, then performs SYNC0 and EI regardless of its result. The file delay
instead gets its current thread, cancels pending wakeups, installs callback002a8508
with the thread in A2, then sleeps. Its callback tail-calls the recovered wake
routine, including its full-width equality test and deferred wakeup queue.
Both delay arguments are masked to16 bits. Duration units remain unestablished;
the source does not add a milliseconds conversion.

All new non-delay instruction addresses were reached. The tests compare the
complete5,296-byte declared RAM, defined returns, ordered syscall and SYNC
traces, Status, and EI counts. There are28,592 original steps and54,522 trace
words. For128 disc delays and128 file delays the actual original callback is
delivered at the wait/sleep syscall boundary; the host runs the corresponding
actual C callback. Interrupted registers and Status are restored afterward.
These are finite supplied alarm arrivals, not a kernel scheduler or hardware
timing test. Existing CreateSema/GetThreadId/WaitSema interfaces consume ABI int
results, so those supplied kernel results are sign-extended32-bit values.

The changed host service adapters also pass their retained comparisons for
native file operations1,920, the full generic worker/cleanup1,024, display
control576, and cleanup/interrupt prerequisites3,584. This is focused affected
coverage; the last full suite remains413 functions/462,684 cases.

DDS has complete matching spans for eight routines under the explicitly listed
address/jump relocations in `disc-platform-transfer.json`. Seven initially have
a unique candidate. The disc alarm callback initially has two candidates;
the literal callback installed by the uniquely matched delay identifies002f2ed0.
The independent file delay literal identifies002cf8c8. Both delay functions
call the matched DDS alarm wrapper0030a7a0. The semaphore initializer has no
complete-span candidate under this search and remains unresolved in DDS.
These comparisons are read-only static evidence, not DDS execution or original
symbol spelling. No additional Unity function counterpart is promoted here.

Continue the movie/archive dependencies002bd9c8 lookup,002bd838 CD lookup,
002bd6a0 seek,002bd750 sector read,002bd5d8 disc readiness, and native CD stream
commands. Their N/S preflight and wait services can now use the recovered
semaphore, polling, busy and delay routines. Remaining debug-print dependencies
must also be recovered: SDK printf002ddd60 routes to002dd738 and its numeric/
float helpers; the separate libc printf002d4748 routes to002d6600. Fatal diagnostic
002a82b0 is nonreturning. These dependencies must execute their own source rather
than receive supplied game-function return values before the movie reader and
worker can be promoted. The scheduler/pump and full moon initializer follow.
Full executable recovery, physical PS2/IOP/filesystem behavior and a matching
executable remain incomplete.

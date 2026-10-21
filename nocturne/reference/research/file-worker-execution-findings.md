# Generic file worker and terminal cleanup

The complete generic worker `002be8c8` and its two returning helpers,
`002be838` close/detach and `002be878` error/callback, are now integrated in
[`file_worker_execution.c`](../src/file_worker_execution.c). The worker has
connected original-instruction checks through actual RPC, response/completion,
allocation, queue and callback bodies. Its Ghidra interface is void and marked
nonreturning; the original infinite loop is preserved.

The original nine-entry table at `00549670` independently establishes dispatch:

| Command | Native operation | Success state / callback cause |
| --- | --- | --- |
| 1 | Open read-only | 7 / 2 |
| 2 | Open with flags `0x202`, job mode | 7 / 2 |
| 3 | Seek with job offset and origin | 7 / 3 |
| 4 | Save position, seek end, restore position | 7 / 4 |
| 5 | Read; add actual result to progress word | 7 / 5 |
| 6 | Write; add actual result to progress word | 7 / 6 |
| 7 | Close, detach and complete | 8 / 7 |
| 8 | Open/read/close/complete, optional allocation | 8 / 8 |
| 9 | Open/write/close/complete | 8 / 8 |

Every fetched job command byte is cleared, including invalid commands. Empty
queues simply wait again. Native return checks use signed full64 values, while
job fields loaded with `LW` sign-extend their low words. Progress addition wraps
at 32 bits. Job statuses retain opening2, seeking3, reading4, writing5, closing6,
ready7, complete8 and error9.

Load command8 uses a negative requested size to query end and rewind. It
allocates through the actual memory-handle allocator/acquire-pointer bodies
when a nonzero read has no destination. Zero-size requests skip the transfer.
Store command9 also skips a zero-size transfer; a negative size still reaches
the native write API. Both ignore the final close result, detach, complete,
invoke cause8 and signal the worker semaphore. Explicit close command7 detaches
even on close error, then takes the error path without closing again. Successful
open/seek/read/write commands keep the job queued and ready.

Close/detach sets handle word40 to `-1` **before** calling native Close for a
nonnegative old signed32 handle, ignores that return, and tail-calls actual job
completion. Error stores low error word44 and status9 before cleanup, then
reloads callback word56 after completion. Its five arguments are job, cause0,
buffer0, result0 and sign-extended user-data word60. Real callbacks may mutate
the terminal status; the checked retry callback changes9 to7.

## Evidence and verification boundary

The host C build passes with warnings treated as errors. A rolling original
instruction capture and C comparison pass **1,024 cases**:128 per returning
helper and768 finite observations of the infinite worker. All declared RAM
(377,652 bytes), defined helper returns, full64 callback arguments, syscall,
cache, handler and IRQ traces and final Status agree. The executions total
689,726 native steps,59,283 syscall trace words,42,966 cache trace words and
16,596 interrupt trace words. All212 worker non-delay instruction addresses are
reached; their73 delay slots execute inside the stepped branch instructions.
No high-level game-function return is supplied.

The returning helpers exercise negative/skipped and nonnegative/actual-close
branches, initialized/zero-flags and uninitialized Close rejection, empty and
nonempty following queues, optional callbacks, high argument lanes and signed
payloads. Successful RPC Close is independently covered by the existing
[native file-operation checks](file-operations-findings.md). Their256 cases are
registered in `file-worker-error-validation.json`.

The first256 worker observations exercise all nine commands through actual
native API rejection, invalid/empty commands, optional callbacks and subsequent
empty/zero-command waits. Another512 connected RPC observations cover successful
commands and later failures: every size-query failure position, read/write
failure, zero-size transfers, negative-size store, allocation-backed load,
progress wrap, ignored final-close failure, and callbacks that request an actual
close command. There are14 allocation-backed loads and534 real callback
invocations in the full group, including203 calls of the real Close command
callback (its status guard decides whether a new command is enqueued).

The actual response and file-completion handlers execute971 and887 times,
respectively. Async descriptor variants execute the real pending/negative-sema
path, both with and without an early completion arrival. Every supplied reply
is checked against the command in the actual submitted packet.971 native
result-stack operands are captured at the original request-header stores, so
each nested API uses its real frame address and initial word. The host adapter
maps those operands; it does not replace an API return. Per-call unwritten RPC
semaphore-option words also come from the native stack. Ordinary IOP reply bytes,
handler arrival timing and kernel/CPU instruction values form the external
boundary. Bulk filesystem/IOP execution is not simulated by these checks.

The observations stop **before the third worker WaitSema syscall**
at `002dbee4`; the host test uses a longjmp at the same kernel boundary. This is
an observation of the original nonreturning loop, not a returning worker or a
one-command replacement. All768 worker observations are registered in
`file-worker-execution-validation.json`; the256 returning helper cases remain
registered separately and are not counted twice. The unchanged native file API
source also passes its1,920 retained original-instruction comparisons with the
updated test adapters.

DDS has a unique complete corresponding span for each function:

| Nocturne | DDS | Contiguous bytes compared |
| --- | --- | --- |
| `002be838` | `002e6020` | 64 |
| `002be878` | `002e6060` | 80 |
| `002be8c8` | `002e60b0` | 1160 |

Only absolute J/JAL targets and the worker's jump-table address are masked.
All literal flags, statuses, events, field offsets, registers, delay slots and
relative branches remain exact, including unowned alignment NOPs. All nine DDS
dispatch offsets and23 previously identified callees agree. This is static
transfer evidence; it does not establish DDS runtime behavior.

The two Read call sites in the complete DDS worker both point to `0030ef30`.
That is a related Read-role candidate, despite the earlier failure to find a
full matching Read body. Its interval to the known Write entry `0030f190` is
608 bytes, versus624 for Nocturne Read. Keep this inferred role separate from
the exact complete-span cohort until the DDS body differences are reviewed.

Unity `libsdf_H.sdfFileCmdHandle_t` corroborates the linked pairs, device/cmd/stat,
buffer, command parameter, descriptor/error/progress, callback and user-data
roles. The managed `sdfFileCmdCallback_t.Invoke` signature independently retains
the five handle/cause/buffer/length/user-data arguments (`pc/il2cpp/dump.cs:204939`).
HD's short offset/length fields differ from PS2's word24/28 operands. No new HD
worker function identity is promoted.

Next: recover the movie-specific archive services and worker, then connect the
loader scheduler/pump and full moon initializer. Add actual terminal job release
and longer scheduler-controlled sequences as those callers become canonical.
Physical IOP, filesystem, kernel scheduling, hardware and matching executable
validation remain outstanding.

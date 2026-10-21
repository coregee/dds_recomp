# Native RPC and file completion

Four complete C routines add 1,320 original body bytes and pass 1,536 comparisons
against original PS2 instructions: SIF response002de808, server request002decb8,
file completion002df5c0 and notification002dfaa8. The server request was missing
from Ghidra's recognized inventory; its existing instructions and closed flow
now form a140-byte body. The working project is saved in place and exports updated.

The response executes real recovered packet release and selected retry callbacks.
The server request retains native head/tail linking, field copies and the existing
thread-wakeup implementation. The completion executes actual memcpy, preserves
live edge counts and staged loads before stores for overlapping block copies,
caps applicable replies at1,024 bytes, and clears only the first pending-ID match.
All25 original jump-table routes are checked. Notification retains callback
execution, SYNC0 and the original permission-dependent EI behavior.

The comparisons include128 actual RPC submission-to-response sequences and64
that also invoke file completion. Reply bytes are supplied in ordinary RAM.
All declared RAM, kernel/cache/interrupt/callback traces, defined sequence returns
and status transitions agree. The host C build passes with warnings treated as errors.
No high-level completion or copy replacement supplies these results.

Three complete DDS instruction spans match uniquely under J/JAL relocation,
with three agreeing known callee links. File completion has no complete DDS match
under the explicitly listed address masks; no DDS identity is assigned to it.
Native reply/pending layouts and uncached-bit constants are checked separately.
Two shared SMT patterns record both the corroborated behavior and this limit.

RPC-submit fixtures use entry status values where DisableInterrupts returns.
A denied DI with IE already set leaves the original wait loop running; the earlier
bounded capture exposed that behavior and was replaced by the current returning
fixture capture. Handler-only cases still cover interrupt permissions. Cached and
uncached memory are separately backed, without a coherence model. Kernel return
values and CPU/cache effects are external boundaries. These results do not prove
IOP execution, asynchronous scheduling, actual file I/O or PS2 hardware behavior.

Continue command/RPC/file initialization and native file operations, then worker
execution and loader scheduler/pump integration. Full executable recovery remains
unfinished; no checkpoint, frozen source tree or backup was made for this batch.

Command/RPC/file initialization is now recovered in the [initialization findings](sif-initialization-findings.md). Native file operations are the next dependency chain.

# CD requests and streaming

The initial nine complete original bodies are reconstructed in `src/cd_stream.c` and
`src/cd_stream.h`: 2,040 recognized body bytes across 2,048 contiguous bytes.
The C compiles with warnings treated as errors. That initial instruction capture
and compiled comparison passed 580 cases, reaching all 387 new non-delay
instruction addresses, executing 25,631,088 original steps and 180 actual native
RPC response handlers. Defined returns, all 70,424 declared RAM bytes, Status,
primitive counts and 58,279 ordered trace words agree.

The current rolling group has 35 complete bodies/2,250 passing comparisons.
See [lifecycle findings](cd-lifecycle-findings.md) and the single current
`cd-stream-validation.json` for updated coverage and totals.

| PS2 entry | Recovered body | DDS full-span counterpart |
| --- | --- | --- |
| 002cbc88 | ps2CdNPreflight | 002f3830 |
| 002cbfa0 | ps2CdSPreflight | 002f3b48 |
| 002cbe90 | ps2CdNWait | 002f3a38 |
| 002cbf30 | ps2CdSWait | 002f3ad8 |
| 002ccd28 | ps2CdStreamCommand | 002f48d0 |
| 002cc9e0 | ps2CdStreamStart | 002f4588 |
| 002cca78 | ps2CdStreamStop | 002f4620 |
| 002ccab0 | ps2CdStreamRead | 002f4658 |
| 002cc748 | ps2CdGetError | 002f42f0 |

## Preserved behavior

N and S requests poll separate semaphores and compare the full result against
the sign-extended, reloaded handle. A successful poll stores the new command
before ReferThreadStatus and the real busy check. Busy failure releases the
semaphore; successful preflight holds it for the request. N checks its extra
busy word before serial-aware RPC activity. Blocking N/S waits use CdDelay(60).

Negative binding flags invoke real RPC bind to services 80000595 and 80000593.
A negative bind result and a nonnegative result with a zero server both retry.
Each path executes the original 1,048,577-iteration decrement/NOP delay in the
capture; no loop shortcut or supplied bind-function result is used. Cold RPC
initialization, all-three disc semaphore recreation, packet exhaustion,
CreateSema failure and DMA failure also have connected cases.

Streaming holds N preflight command 15, writes the 20-byte shared packet, and
submits RPC command 9. Sector/count/buffer/operation are low words; the three
mode bytes are loaded and stored in order, preserving overlapping inputs.
The fourth mode byte is left untouched. The return loads the uncached reply
before SignalSema. Start sets active to 1 before submission; stop sets it to 0.
Neither rolls the flag back on failure.

StreamRead initially logs count and mode using the actual SDK formatter. Its
second diagnostic operand is the incoming A2 register, which is still live at
the original call. An inactive stream returns without touching the error word.
Active reads flush the requested byte span with wrapped word count shifted by
11. Mode zero performs one command. Blocking mode accumulates the low 16 bits
as the read count, treats the upper 16 bits as error, retains the last nonzero
error and advances count/buffer with word arithmetic. Zero count and no error
invoke actual CdDelay(8). Completion compares the accumulated sign-extended
word against the original full-width count, or exits on error plus zero chunk.
Even a requested count of zero issues a command and takes the zero-chunk delay.
Error-output aliases with the reply and active flag are compared.

GetError uses S preflight command 2, RPC command 12 and an uncached reply loaded
before semaphore release. Failures return -1. Debug level at least 2 logs the
literal status message without consuming stale argument registers.

## Dependencies and transfer

Real original and recovered semaphore, RPC initializer/bind/call/packet/cache,
RPC response, timer and SDK formatter/output bodies execute. The host adapter
supplies kernel results, ordinary reply memory and busy-state progress during
blocking waits. The native response handler releases packets and signals the
semaphore; its result is not substituted. The otherwise unwritten RPC semaphore
option is explicitly supplied as zero in both executions. Cached and uncached
memory spans are compared separately.

The six affected existing comparisons also pass with the new mode inactive:
SDK output 1,792; disc platform 1,344; RPC transport 2,880; completion 1,536;
SIF initialization 1,024; file operations 1,920. Existing original captures are
reused; no full-suite recapture is claimed.

All nine DDS counterparts match complete spans uniquely, with 40 agreeing
new/shared callee destinations. Only address immediates and jump destinations
are masked; service IDs, field offsets, branch geometry, NOP delays and
cached/uncached formation remain constrained. GetError's success-only LUI/addiu
address pair is recorded explicitly because its failure-only immediate would
clobber that register in a naive linear provenance scan. DDS is read-only.

The current rolling report now includes14 further bodies,23 total/1480 cases;
see [search/readiness/control findings](cd-services-findings.md).
Current evidence: `cd-stream-validation.json`, `cd-stream-transfer.json`,
`cd-stream-interfaces.json`, `cd-stream-abi.json`; rolling capture under
`cd-stream/`. Interfaces are saved in the working project, independently
reopened and checked; the current23 selected exports merge into the existing inventory.
No checkpoint, project copy, frozen source or duplicate capture is created.

Kernel scheduling, physical disc/IOP operation, arbitrary asynchronous
reentrancy, original library-wide type declarations and a matching PS2
executable remain unproved. Next: continue the CD read/search/status/initialize
operations and movie/archive callers using these complete dependencies.

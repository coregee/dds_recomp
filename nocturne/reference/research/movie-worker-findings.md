# Complete movie worker and transfer leads

`ps2MovieWorkerRun` at `002bed50` is integrated in `src/movie_worker.c` and the
shared host build. Its full original nonreturning body has 604 recognized bytes
in a 620-byte contiguous span, including 16 bytes outside its recognized body.
The saved no-return interface passes after reopening the working Ghidra
project; the selected export decompiles and merges into the current inventory.

All 384 connected original-instruction/C observations pass: 575,732 original
steps, 400,389 ordered trace words and 360 MMI instructions. The comparisons
reach 106 of 109 non-delay root addresses. `002bef48`, `002bef4c` and `002bef54`
belong to the whole-load negative-read error branch and remain unexecuted.
The source retains that branch; the size-query path obtains a nonnegative
size after a successful open in these immutable-archive cases. A negative
direct read request with no cached bytes safely exercises the separate
command-5 error path without a data copy.

## Native commands and lifetime

The worker waits on `worker+4`, loads `worker+8`, reads and clears job command
byte 21, and dispatches commands 1–9 through the original table at `5496a0`.
Null jobs, command zero and out-of-range commands wait again. Actual command
routes are listed in [movie file/cache findings](movie-file-findings.md).

Open sets state 2, calls the real archive-backed movie open, and on success
sets state 7, resets progress word 48 and emits callback event 2. Open failure
uses the actual generic worker error helper with error zero. Size captures the
callback before setting ready state; without a callback it does not call Size
at all. Read calls the real movie file layer, adds its result to the word
progress with wraparound, sets ready state and emits event 5. Negative reads
go through the actual error helper with the returned error.

Close sets state 6, closes the real movie file, completes the actual linked
queue job, then sets state 8 and emits event 7. Whole-file load opens first,
uses Size for a negative requested count, allocates and acquires a missing
buffer through the actual memory-handle allocator, and skips Read for zero
size. It then closes, sets job descriptor word 40 to all ones, completes,
sets state 8 and emits event 8. Commands 2, 3, 6 and 9 use the actual generic
error helper with zero. Unlike the generic file worker's load route, this
worker does not signal its own semaphore after completion.

Five raw 64-bit callback arguments retain the original job, event, buffer,
result and sign-extended word-60 payload. Selected native Retry and Close
callbacks execute actual recovered C. A Close callback on a ready Open/Read
job requests command 7, which the next worker iteration executes. Retry can
reset an error-state job after actual queue completion. Existing queue links
and a following job are compared in the same address space as CD, cache and
allocator state.

## Full shipped-file observations

The original `DDS3.DDT` remains shared and unchanged. Four original image
windows include every byte of the files used by the movie-file tests, rounded
to sector boundaries: 40,960, 14,336, 14,336 and 10,240 bytes, totaling 79,872.
Each window is loaded once and hash-checked. Eight size-query/allocation cases
load `agi01.BED` (40,752 bytes), `ken.BED` (13,488), `nego_kai.BED` (14,016)
and `zan01.BED` (8,304) in full, twice each. Output bytes have independent
original-file hashes. Partial, unaligned, cached and overlapping reads also
execute through the actual movie file functions.

The shared host and original interpreter compare seventeen declared RAM
spans, CPU Status, primitive calls, raw kernel values, ordered callback/data
events, consumed replies and the media sector cursor. The interpreter checks
that no original write escapes declared RAM or private stack, and the DDT
cannot receive writes. Actual archive, CD/RPC/response, queue, error,
allocation/acquire and callback bodies execute; no game return is substituted.

The external observer ends after the fourth worker WaitSema syscall, following
three worker iterations. The source remains an infinite nonreturning worker.
Kernel outcomes and ordinary incoming IOP bytes are external inputs. Direct
`cdrom` lookup, the null-handle size fatal spin, unbounded/malformed copies,
physical PS2/IOP scheduling and a matching executable remain unverified.

Affected original/C comparisons also pass: movie files 384, movie disc retries
288, generic worker/cleanup 1,024 and CD stream/lifecycle 2,250. These refresh
current focused reports, without claiming a new full-suite run or saving
project/capture copies.

## DDS transfer evidence

DDS `002e6538` uniquely matches the complete 620-byte worker span under the
listed call and table-address relocation mask. Literal field offsets,
command/state/event values, registers, relative branches, delay slots and
gap bytes agree. The relocated table at `003b45c0` has all nine corresponding
dispatch offsets. Five calls agree with independently matched WaitSema,
memory-handle AcquirePointer and error-helper bodies.

Calls from that matched worker supply four DDS role candidates:

| Nocturne body | DDS caller-derived candidate |
| --- | --- |
| Movie Open `002bdb80` | `002e5310` |
| Movie Read `002bdbd0` | `002e5398` |
| Movie Close `002bde18` | `002e55e0` |
| Movie Size `002bdea8` | `002e5670` |

These four bodies have no complete identical-span match under the existing
movie-file mask. The caller establishes useful roles to investigate their
differences; it does not establish equivalent DDS implementations or runtime
behavior. `movie-worker-transfer.json` and the shared SMT signature ledger
record that distinction.

## Higher-level Unity lead and a PS2 entry defect

The HD `mviManager.moviePlayFile` native body at `1828156a0` starts process type
`0x2afb`, and the PS2 launcher at `0022b710` uses the same type through the
already recovered process constructor `001015b0`. It passes the literal name
`movieDraw`, callback `0022b6e0`, and saves the process at `gp-43dc`. PS2 index
wrapper `0022b768` uses a 24-byte movie-table stride at `343be8`; stop wrapper
`0022b7a0` closes movie control `343e40`, ends the saved process and clears it.
These are retained graph/role leads, not promoted HD function identities.

The launcher references `0022b6e0`; the inventory previously started its
callback at `0022b6e8`. Original ELF words at the missing prefix are
`3c040034` and `3c05002f` (`lui a0,0x34; lui a1,0x2f`). Together with the
existing body's additions they supply constants `343e40` and `2f6638` to
`002c5170`, then return zero. That entry is now corrected to the full 44-byte
body, with a zero-argument interface and tested source through the actual draw
routine. See [movie draw/queue findings](movie-draw-findings.md). The worker
recovery does not depend on that callback.

Current recovery is tracked in `recovery-progress.json`.
The last full comparison remains 413/462,684. Current worker
reports, source, mappings and exports are saved in place; its original vectors
occupy the single rolling `movie-worker/vectors.jsonl`.

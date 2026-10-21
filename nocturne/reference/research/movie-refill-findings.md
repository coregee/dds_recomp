# Decoder refill, DMA callbacks and completion worker

Six complete routines in `src/movie_refill.c` add 1,276 recognized body bytes and
384 passing original-instruction/C comparisons. All 261 recognized non-delay root
instruction addresses are reached. The affected C compiles with warnings treated
as errors; the saved interfaces are independently reopened and six current exports
are merged into the whole-program inventory. Current compiled recovery is 793/8,960
functions, 8.85%, with 572,631 aggregated comparisons.

| PS2 entry | Recovered routine | Body bytes |
| --- | --- | ---: |
| 002c43e8 | ps2MovieDecoderRefill | 536 |
| 002c4b40 | ps2MovieInputDmaInterrupt | 152 |
| 002c4b10 | ps2MovieOutputDmaInterrupt | 44 |
| 002c4a40 | ps2MovieDecoderCompletionThread | 204 |
| 002c4c28 | ps2MovieDecoderFrameConsumed | 132 |
| 002c5098 | ps2MovieAudioReserve | 208 |

The output-DMA callback was incorrectly recognized at 002c4b14. Initialization
002c4f80 registers 002c4b10, whose first instruction loads thread 00552164 into A0.
The corrected 44-byte body calls the actual wake wrapper, executes SYNC/EI and
returns 0. The function count remains 8,960; the retired entry and exports are removed.

Refill queries the real ordinary/IPS consumer and requests at most 8,192 bytes per
slot. Seven ready slots occupy an eight-slot ring. Partial EOF, exact-slot EOF,
not-yet-ready input and stopped consumers preserve the original flag/count rules.
Slot 7 also copies its last 256 bytes to the window immediately before the staging
buffer, including the original aligned/unaligned 32-byte batch order. The tests use
nineteen original IPS packet windows; an independent cyclic stream oracle checks
507,905 consumed bytes against their source ring. Full declared RAM also agrees.

The input-DMA callback snapshots the current display frame to 00552144 and clears
input owner 00552158 before refill. A consumed input slot advances with the original
byte wrap and decrements the ready count. The actual input-DMA setup follows;
every exit executes SYNC/EI.

The completion worker remains infinite in both original instructions and C. Each
wake saves the IPU context, updates input/frame flags and completed-frame count,
clears the active decoder, and applies frame-limit stop/loop behavior. Eligible
decoders are requeued through actual FIFO insertion and scheduling. Observation
ends externally at a finite SleepThread boundary. Actual output-DMA and
frame-consumed callbacks are delivered at selected wakes; no return is added to the
worker and no callback, allocation or scheduling result is fabricated.

Frame consumption decrements the completed count, toggles the output buffer,
increments the display counter and reschedules. The audio reservation callback,
registered by the recovered draw-packet body 002c5170, consumes staged bytes before
the semaphore-protected secondary IPS ring. Signed full 64-bit request comparisons,
word arithmetic, 65,536-byte wrap and insufficient-data tracking are preserved.
Names remain descriptive PS2 aliases; original symbol spellings are unknown.

Two complete DDS spans resolve: refill 002ebc98 and frame consumption 002ec4d8.
Two interrupt-helper call links agree. Other bodies remain unresolved under the
current mask. These are static transfer findings, not DDS execution proof.

Affected checks pass for the movie manager (256 cases), streaming (1,344), CD (2,250),
disc/alarm platform (1,344) and decoder/close (3,456) against the current library.
The last full-suite result remains 413 functions / 462,684 cases.
No checkpoint or backup is created.

Cached and uncached addresses are separate declared test views; physical cache
coherence is not established. Video decoding, physical IPU/DMA/IOP scheduling,
malformed or endless rings, PS2 runtime and matching executable remain unproved.
The Unity VideoPlayer implementation supplies no retained native IPU body here.

Continue the frame-output pipeline 002c4cb0/002c4d30 and its allocation/conversion
dependencies, then decoder startup/handler registration 002c4f80. The source now has
actual refill and completion prerequisites for those paths. See
[validation](movie-refill-validation.json), [transfer search](movie-refill-transfer.json)
and [corrected entry](movie-refill-entry-applied.json).

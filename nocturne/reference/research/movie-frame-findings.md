# Movie frame delivery and update

Nine complete routines in `src/movie_frame.c` add 2,128 recognized body bytes and
576 passing original-instruction/C comparisons. The affected C compiles with
warnings treated as errors. All 436 returning-path root instruction addresses
are reached; six allocator-exhaustion addresses remain outside the tested paths.
The saved interfaces are independently reopened and nine current exports are
merged into the executable inventory. Current compiled recovery is 802/8,956
functions (8.95%), with 573,207 aggregated comparisons and 128,980 summed body bytes.
This is additional focused validation, not a new full-suite run.

| PS2 entry | Recovered routine | Body bytes | Unique DDS span |
| --- | --- | ---: | --- |
| 002aa350 | ps2VramFormatBits | 76 | 002d16f0 |
| 002aa438 | ps2VramAllocateFront | 288 | unresolved |
| 002aa678 | ps2VramSurfaceAllocate | 152 | 002d1a18 |
| 002c3c60 | ps2MovieDecoderAllocateFrames | 100 | 002eb510 |
| 002c3da0 | ps2MovieDecoderBuildUploadPackets | 624 | 002eb650 |
| 002c4178 | ps2MovieDecoderReadStreamHeader | 312 | 002eba28 |
| 002aac50 | ps2MovieUploadQueueAppend | 124 | 002d1ff0 |
| 002c4cb0 | ps2MovieDecoderDeliverFrame | 124 | 002ec560 |
| 002c4d30 | ps2MovieDecoderUpdate | 328 | unresolved |

The literal 59-entry table at 00549050 selects four constant-return arms and the
default zero return. Ghidra had counted arms 002aa378/380/388/390 as independent
functions. Their original bytes and table targets establish ownership by
002aa350; the corrected body excludes padding 002aa374 and includes the arms.
The recognized inventory falls from 8,960 to 8,956 without losing recognized
instruction bytes. All 59 format inputs and five out-of-range raw64 values are
tested. This lookup differs from the previously recovered texture-format helper:
unsupported values return zero.

The front VRAM allocator scans previous links from 00552090 and splits a free
extent at its low end. Its existing back allocator counterpart scans next links
from 00552094 and splits at the high end. Surface allocation multiplies the low
words of width, height and format bit count, applies the original arithmetic
shift by five, selects either allocator, and records dimensions and format.
Actual pool allocation and IRQ ownership execute; no allocator result is supplied
by the comparison adapter. Valid exact-fit, split, occupied and too-small nodes,
raw64 categories and signed request boundaries are tested. Exhaustion still
reaches the original callback/unchecked null access; that path is unverified here.

The stream header consumes exactly 16 bytes through the actual ordinary or IPS
ring consumer. Width at header+8, height at +10 and frame count at +12 populate
decoder+60/+62/+64. Four shipped IPU headers from ALPHA, E500_002, E731 and G_OVER
decode independently to their literal dimensions/counts, including 512x448 frames.
Synthetic cases cover partial headers, previously-read headers, ring wrap,
existing VRAM, width rounding at 64, and height rounding at 32 or 64. The header
magic is not checked by this original routine. New surfaces and both CPU frame
buffers use the actual recovered allocators; successful headers enter the real
decoder FIFO. Only private header-buffer addresses are normalized in the trace.

The upload builder allocates both packet chains and writes complete GS register
and image/reference records for 16x16 macroblocks. BITBLTBUF, TRXREG, TRXPOS and
TRXDIR register identifiers are 0x50, 0x52, 0x51 and 0x53. A macroblock transfers
64 QWC for the default output mode and 32 for either nonzero mode. The native
macroblock counter decreases across both packet passes without being reset: the
first chain's final image record receives the end bit, while the second chain
retains the original counter behavior. Every declared packet byte agrees with
the original instructions; the recovered source preserves that behavior.

The upload queue shares semaphore 00581018 and head/tail 00581024/00581028 with
the existing texture upload path. Appending to a nonempty chain replaces its tail
with a 0x20000000 link tag whose high word contains the masked packet address,
and clears the following doubleword. Frame delivery selects one of the two packet
slots, builds absent chains, links the selected chain and calls actual frame
consumption/scheduling. A zero completed-frame count returns zero without linking.

The update loop retries stalled input DMA, walks the owned decoder list, decrements
the display hold byte, handles first-frame and rate-accumulator states, delivers
eligible frames, reads stream headers, refills under the original IRQ ownership,
invokes the actual consumer's read-pump event and schedules decoding. Tests cover
empty and multiple-decoder lists, byte wrap, raw64 deltas, both packet slots,
existing/missing packets and real refill/start dependencies. No game/library return
substitutes are used. The batch executes 1,176,646 original steps; full declared
RAM, defined raw64 results, Status and ordered kernel/IRQ/consumer/MMIO events agree.

Seven complete DDS spans and 18 call constraints agree. The front allocator and
update loop remain unresolved under the current mask; they are not forced into
the transfer map. These are static DDS findings, not DDS execution proof.
The HD corpus retains three empty mdlEffect IPU methods and an IPU callback delegate
constructor, while the movie manager uses Unity VideoPlayer. No equivalent native
HD GS/IPU body is established for these routines, so their names remain descriptive
PS2 aliases.

Affected existing refill/completion (384 cases) and decoder/close (3,456 cases)
comparisons also pass against the current library. Physical GS uploads, IPU/DMA
decoding, cache coherence, allocator exhaustion, malformed/unbounded lists or
geometry, PS2 playback and a matching executable remain unverified. Cached and
uncached test views remain separate. No checkpoint or backup is created.

Next recover decoder startup 002c4f80, IPU initialization 002cda58/002cd9f0 and
handler registration 002a8310, then the preloaded-IPU path 002c4080/002c3cc8.
Existing thread creation/start and DMA-enable helpers supply part of that chain.
See [validation](movie-frame-validation.json), [DDS transfer](movie-frame-transfer.json),
[switch repair](movie-frame-entry-applied.json) and [saved interfaces](movie-frame-abi.json).

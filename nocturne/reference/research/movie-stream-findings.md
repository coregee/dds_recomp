# Ordinary and IPS movie streaming

Seven complete routines are recovered in `src/movie_stream.c`. The affected C
and comparison bindings compile with warnings treated as errors and link into
the current recovered library. Each routine passes 192 original-instruction/C
comparisons, for 1,344 cases. The interfaces are saved in place in
`ghidra/working/Nocturne.gpr`, independently reopened and exported into the
current whole-program inventory.

| PS2 entry | Recovered routine | Body bytes |
| --- | --- | ---: |
| 002c53c8 | ps2MovieOrdinaryReadPump | 140 |
| 002c5460 | ps2MovieOrdinaryFileCallback | 384 |
| 002c5a18 | ps2MovieOrdinaryConsume | 368 |
| 002c55f0 | ps2MovieIpsReadPump | 140 |
| 002c5688 | ps2MovieIpsFileCallback | 896 |
| 002c5bb8 | ps2MovieIpsConsume | 360 |
| 002c5b98 | ps2MovieIpsCopy | 28 |

The seven bodies total 2,316 bytes. The IPS callback's contiguous capture also
includes gaps between its recognized chunks; all original instructions and its
eight-target table at 0054a2f0 are retained. Descriptive names do not imply exact
Unity symbol equivalence.

## File states and rings

The ordinary pump fills a 0x20000-byte ring in requests of at most 0x4000 bytes.
Record fields +4/+8/+c/+10 hold start, read cursor, write cursor and filled
bytes. A signed capacity check stalls in state5 when fewer than 0x4000 bytes
are available. The consumer splits copies across the ring end and resumes a
stalled pump on event2. Event0 reports buffered bytes and writes the EOF flag
when stopped or when no file bytes remain.

The IPS callback first requests a 64-byte header, allocates and acquires the
metadata handle, then reads the rest of the header block. Header word +0x18
contains the complete header-block size; +0x1c contains packet size. The record
stores metadata handle/pointer/packet index at +0x40/+0x44/+0x48.

Each packet's mask bit selects one of two 0x10000-byte rings. A clear bit copies
contiguously into the first ring, using read offset +0x58 and filled count
+0x5c. The original performs one wrap subtraction before that copy; it does
not split a packet at this ring's end. Interrupt ownership protects the update.
A set bit copies into the second ring under semaphore00551b48, splits at its
end, clamps buffered bytes to 65536 and advances its base when overwriting.
The source retains the original signed word arithmetic and truncating mask
index division, including the distinction between the two wrap paths.

Both callbacks preserve cancellation, raw64 event equality, remaining-byte
updates and real size/read/close commands. A close-complete event releases the
actual terminal file job and changes state7 to state6. Allocators, copies,
command helpers, job release, interrupt helpers and semaphore wrappers execute
their recovered bodies; comparison inputs supply kernel outcomes.

## Original assets and validation

All nineteen shipped IPS files supply their original headers, metadata and
first four packet windows: 362,496 bytes in total. Nineteen cases validate real
metadata allocation. Another nineteen distribute the first two packets of
each file, with expected output independently assembled from its mask bits
and original packet bytes. The remaining cases cover state/event combinations,
stopping, EOF, capacity thresholds, wraparound, overwrite and resume paths.

Full declared RAM, defined raw64 results, interrupt Status and ordered
kernel/cache/trap events agree. Original writes are checked against declared
RAM/private stack, and the original archive index remains unchanged. The
rolling report is `analysis/movie-stream-validation.json`; it records execution
totals and current source/input hashes.

The cases reach 449 of 450 non-delay root PCs. The remaining branch002c54d8
cannot execute: the dispatcher loads an unsigned state byte, handles state1
first, then branches on state0. No other byte value is less than2. This is a
structural unreachable branch, recorded explicitly in the report.

Four zero packet-size cases reach the original BREAK7. Ghidra's default DIV
p-code otherwise fails before the compiler's zero check. A scoped CPU adapter
checks the exact original DIV instruction002c57fc, writes the EE zero-divisor
HI/LO values, and advances into the original BEQL/BREAK delay slot. Its
semantics follow the [PCSX2 DIV implementation](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/R5900OpcodeImpl.cpp).
The C observer catches the matching nonreturning exception; it supplies no
ordinary callback return. These cases use positive dividends and do not test
an exception handler or resumed execution.

The IPS copy wrapper uses canonical bounded counts. The underlying native
memcpy first tests a raw64 count and then decrements words; an aligned count
with a high word and a low word below32 can enter a wrapping, enormous copy.
That malformed input is outside this comparison domain. Zero/negative packet
counts can also enter the callback's original do/while loop without terminating
within a useful bound. Those paths are preserved but unproved.

Affected initialization and worker comparisons still pass (768 and384 cases),
as do the 11,264 compiler-numeric cases after updating the exception observer.
Current aggregate recovery is783/8,960 routines and571,991 comparisons. The
last full comparison remains413 routines/462,684 cases.

## Transfer and remaining work

Six complete DDS spans match uniquely, with21 agreeing callee constraints and
two global constraints. The IPS file callback has no complete-body candidate
under the current mask, which retains GP data displacements. These are static
transfer results, recorded in `analysis/movie-stream-transfer.json`; DDS
execution and exact Unity identity are unproved.

Decoder scheduling, shutdown002c42b0 and control close002c5f38 are now recovered;
see [decoder and close findings](movie-decoder-findings.md). Physical IPU/GS/IOP
behavior, asynchronous scheduler integration,
complete media decoding, PS2 runtime validation and a matching executable are
unfinished. The Unity movie manager's process/launcher graph remains useful
for higher-level identity leads; these streaming bodies are PS2-specific
recovery, not inferred Unity API replacements.

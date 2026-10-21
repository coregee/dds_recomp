# Full vector writing and exponent formatting

Three complete C bodies in `src/libc_vector.c` add 1,252 recognized body bytes:
full vector writer 002d9e00, its sprint wrapper 002d6500 and exponent helper
002d7ea8. All 768 new comparisons pass, reaching all 245 selected non-delay
instruction addresses. The affected C builds with warnings treated as errors.
The working project was saved in place, its 21 current console/vector/exponent
interfaces reopened and checked, and current exports merged without creating
functions, checkpoints or project copies.

| PS2 entry | Recovered function | DDS span result |
| --- | --- | --- |
| 002d9e00 | ps2LibcWriteVectors | 00307428 |
| 002d6500 | ps2LibcSprint | 00302580 / 003032f0; unresolved |
| 002d7ea8 | ps2LibcFormatExponent | 00304c98 |

The names describe native behavior. Exact Unity identities and original
compiler/library source version are not claimed. The two identical DDS sprint
candidates remain explicit; a shared tiny wrapper is insufficient to choose one.

## Full vector writer

The UIO record holds vector pointer/count/residual at 0/4/8. Each descriptor
holds source pointer and byte count at 0/4, with eight-byte stride. The writer
skips zero-length descriptors and continues until the freshly loaded residual
becomes zero. It does not add bounds or a vector-count check absent in native
code. A zero initial residual returns before stream preparation.

If the stream lacks write mode or a buffer, the actual recovered PrepareWrite
body executes. Its failure returns -1 without the later writer error-flag store.
Cases cover denied write mode, write-mode permission and the real inline
unbuffered setup; this group does not exercise new heap-backed preparation paths.

Unbuffered mode submits chunks capped at 1,024 bytes through the current real
callback. Normal buffering chooses partial fill/Flush, direct callback or a
buffer copy. Line buffering searches through the real Memchr body, retains the
newline distance until consumed and flushes at a completed line. String mode
0x200 copies only available space but consumes the whole descriptor byte count,
including bytes truncated from the destination.

The implementation executes the actual recovered Memmove, Memchr, PrepareWrite
and Flush bodies. Callback entries include real stream write/console transport,
PollSema, literal Isatty and unsupported Close. No write-return replacement is
used. Full 64-bit callback positivity controls success; pointer, remaining and
residual arithmetic wraps as original words. Normal buffering reloads flags on
continuation, and error paths set a freshly loaded FILE flag 0x40.

The cases include forward/reverse overlap, aligned search/copy, empty descriptors,
zero and full-width callback returns, partial console sends, direct-write and
Flush failures, all four modes and raw high argument lanes. The sprint wrapper
clears vector count and residual after either write result; its zero-residual
path clears count only.

## Exponent helper

The helper writes the low marker byte, chooses sign from the initial full
64-bit register and emits at least two exponent digits without a terminator.
The negative path first performs word-width subtraction. The initial less-than-
ten test uses the full register; subsequent divisions consume signed words.
Those widths produce unusual output for noncanonical wide inputs and INT32_MIN;
for a marker `e`, the latter retains native `e-00`. These are preserved rather
than substituted with host number formatting. The 128 cases include signed
boundaries, wide registers, random marker bytes and output alignments.

The private C digit array represents the original private scratch values. Its
stack placement is not claimed to match the executable. The original 220-byte
contiguous span contains 212 recognized body bytes; the fixed divisor cannot
reach its zero-divisor BREAK path.

## Rolling evidence and transfer

The single current console/vector capture now covers 21 recovered bodies and
128 existing Flush integrations: 3,008 passing cases, 1,584,554 original steps,
231,005 ordered trace words, 854 completion arrivals and 99 input arrivals.
All 696 selected non-delay instruction addresses are reached. Defined returns,
all 36,672 declared RAM bytes, Status and ordered normalized kernel packet,
callback, diagnostic and interrupt traces agree. Original guest writes remain
inside declared RAM and private stack.

Aligned Memchr executes 3,459 original MMI instructions using the existing
reviewed instruction-value callbacks. The matching C memory/search bodies
execute directly; there is no Memchr or copy-function return hook. Guest/host
alignment is checked. This does not establish atomic bus access or hardware
MMI behavior.

Twenty of the twenty-one canonical DDS spans resolve uniquely, with 42 agreeing
call/callback and 18 repeated global-address constraints. The remaining sprint
has two candidates. The four Memmove/PrepareWrite/Flush/Memchr dependency spans
also match uniquely. The main formatter has no complete-span match under the
current address mask and remains an investigation lead, not a source promotion.
DDS is read only. Finite backed vectors, stable ordinary memory and supplied
external kernel/callback events do not prove exhausted/malformed descriptor
handling, arbitrary concurrency, physical PS2/IOP or a matching executable.

The recovery index adds 768 cases and three routines from this extension. It
retains the earlier console cases and excludes the overlapping Flush function
from aggregate additions. Current source recovery is 711/8,960 functions.
Next complete the dtoa/bigint chain and main formatter
002d4748->002d6600->002d6678, then integrate the unbuffered printf wrapper
002d6548 and movie archive diagnostic paths.

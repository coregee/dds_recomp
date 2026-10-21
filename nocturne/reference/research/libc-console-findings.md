# Libc read/write adapters and native console transport

Eighteen complete bodies in `src/libc_console.c` add 2,200 original body bytes.
All 2,112 new-body comparisons and 128 integrations through the existing Flush
body pass. The affected C builds with warnings treated as errors. Eighteen
interfaces were saved in place, reopened and checked, then their current exports
merged into the rolling Ghidra inventory. No checkpoint or project copy was made.

| PS2 entry | Recovered function | DDS complete-span match |
| --- | --- | --- |
| 002db670 | ps2LibcStreamRead | 00301630 |
| 002db6d8 | ps2LibcStreamWrite | 00301698 |
| 002dba10 | ps2LibcReadReentrant | 00308a80 |
| 002db7e0 | ps2LibcWriteReentrant | 00305bb8 |
| 002dc4e8 | ps2LibcConsoleRead | 0030b068 |
| 002dc468 | ps2LibcConsoleWrite | 0030afe8 |
| 002dd360 | ps2ConsoleInitialize | 0030bee0 |
| 002dd140 | ps2ConsoleWrite | 0030bcc0 |
| 002dd290 | ps2ConsoleRead | 0030be10 |
| 002dcf00 | ps2ConsoleRingInitialize | 0030ba80 |
| 002dcf28 | ps2ConsoleRingProduce | 0030baa8 |
| 002dcf68 | ps2ConsoleRingConsume | 0030bae8 |
| 002dcfa8 | ps2ConsoleCommandCallback | 0030bb28 |
| 002e4898 | ps2ConsoleRegisterCommand | 00313430 |
| 002e4908 | ps2ConsoleSendCommand | 003134a0 |
| 002e4938 | ps2ConsolePollCommand | 003134d0 |
| 002e4960 | ps2ConsoleReceiveBytes | 003134f8 |
| 002e4998 | ps2ConsoleSendBytes | 00313530 |

These are descriptive PS2 aliases, with no exact Unity counterpart or original
SDK source-version claim. All eighteen DDS instruction spans match uniquely
under the documented relocations.

The current rolling report now includes full vector writing, sprint and exponent
formatting: 21 recovered bodies and 3,008 passing comparisons. See
[vector findings](libc-vector-findings.md) for updated totals and transfer limits;
the initial eighteen-body results above describe the original console batch.

## Stream adapters

Read uses the signed descriptor halfword at FILE+14 and context word at +84.
It narrows the console return to a signed word, adds successful reads to cached
offset +80 and clears valid-offset flag 0x1000 on negative reads. Write tests
append flag 0x100 and executes the real unsupported-seek adapter, reloads flags,
descriptor and context, clears 0x1000 before the real write and narrows its result.

The reentrant wrappers clear global errno 0x552178 before actual console calls.
Only full return -1 and fresh nonzero errno cause a context error write. Write
accepts word-normalized descriptor values one and two; read requires the full
64-bit descriptor to equal zero. Both use the lazy initialization flag 0x52c2a4.
No host read/write calls replace these original bodies.

## Console state and kernel packets

The state at 0x59b690 has channel at 0, pending output length at 4, accumulated
input length at 8, busy flag at 12, output pointer at 16, input pointer at 20 and
ring pointer at 24. The ring at 0x59b580 stores capacity/count/read cursor/write
cursor at 0/4/8/12, followed by data at 16. Producer and consumer wrap only when
the incremented cursor equals the computed end, without overflow or underflow
checks.

Initialization executes the real FlushCache wrapper and registers service
0x210 with the actual console callback. A signed low-word channel failure
returns zero. Success initializes uncached packet 0x2059b6c0 with type 0x210,
command bytes 0x45/0x48 and a 256-byte ring.

The actual raw kernel command wrapper uses selector 0x7c. Commands 1, 3, 4,
-5 and -6 pass registration, send-command, poll, receive-byte and send-byte
packets. Service/count fields narrow to 16 bits, channels/pointers to words,
and the send-command byte sign extends. Tests normalize the private stack
packet pointer to the exact words consumed by the kernel boundary.

## Input, partial output and completion

Output rejects a busy state, executes the recovered interrupt-disable body,
sets busy and fills at most 256 bytes. It inserts CR before LF and counts
consumed input separately: a CR that fills the last packet byte leaves the LF
unconsumed for the next call. A failed send clears busy, enables interrupts
and returns -1. Successful sends execute real poll packets until actual
completion callbacks clear busy; the original unconditional enable is retained.

Read tests the full count before reading. It waits for a nonempty ring, copies
the current byte, executes the actual ring consumer, then reloads the output
byte before testing LF/CR. Positive wide counts still follow the original word
counter. The host test adapter delivers finite input only at this read wait;
ordinary address resolution does not trigger arrivals on initialization stores.

Callback operation 3 submits pending bytes and updates pointer/remaining length
from the actual kernel result. Operation 4 diagnoses leftover bytes and clears
busy. Positive operations below three either receive more packet bytes or feed
payload into the real ring producer. Four alias fixtures make the producer
change the state input pointer: the callback retains its original header pointer
while reloading the payload pointer on continuation. Diagnostic failure paths
execute the already recovered SDK formatter and buffered output bodies.

## Evidence and remaining work

`libc-console-validation.json` records 1,125,090 original instruction steps,
73,735 ordered trace words, 712 completion arrivals and 99 input arrivals.
All 451 selected non-delay instruction addresses are reached. Defined returns,
all 36,672 declared RAM bytes, Status and normalized kernel packet, actual
callback, SDK diagnostic and interrupt traces agree. Original guest RAM writes
are checked against the declared spans and private stack; emulator registers
and temporary values are excluded from that RAM check.

The 128 Flush integrations repeatedly execute its actual stream write callback
through partial console sends and error paths. The recovery index adds only the
2,112 cases for the eighteen new bodies, avoiding double counting the existing
Flush function. Affected stream, SDK formatter, CD and draw-platform comparisons
reuse their retained captures; no new full-suite run is claimed.

The transfer report resolves all eighteen complete DDS spans, with 31 agreeing
call/callback links and 16 repeated global-address constraints. Address masking
includes explicit LUI address construction, copied bases and an independently
checked LUI branch-delay back edge. Flags, field offsets, packet shapes, counts,
branch geometry and every other native instruction word remain fixed. Six
additional recovered dependencies have unique matching spans. DDS is read only.

Finite external kernel values and callback arrivals do not prove arbitrary
concurrent scheduling, malformed or exhausted ring behavior, actual IOP/PS2
hardware or a matching executable. Private stack packet placement is unproved.
Vector write 002d9e00 is now recovered. Next complete the main libc formatter
002d4748->002d6600->002d6678, including dtoa 002d8378 and its bigint dependencies.
The SDK diagnostic formatter and libc printf are separate native code paths.

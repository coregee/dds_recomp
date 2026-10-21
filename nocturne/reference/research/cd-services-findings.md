# CD search, readiness and remaining stream controls

Fourteen complete EE functions are now reconstructed in `src/cd_services.c` and
`src/cd_services.h`, adding 2,608 recognized body bytes and 900 comparisons.
They share the existing rolling CD capture with the previous nine functions.
The initial 23-body comparison passed 1,480 cases, all 904 new non-delay
instruction addresses, 52,074,613 original steps, 638 real native RPC response
handler calls, all 72,856 declared RAM bytes and 187,649 ordered trace words.
The affected C compiles with warnings treated as errors. The current group is
35 bodies/2,250 passing cases; see [lifecycle findings](cd-lifecycle-findings.md)
and the single current `cd-stream-validation.json` for updated coverage/totals.

| Nocturne entry | Recovered function | DDS full-span counterpart |
| --- | --- | --- |
| 002cb950 | ps2CdSearchFileExtended | 002f34f8 |
| 002cbc68 | ps2CdSearchFile | 002f3810 |
| 002cc3f0 | ps2CdDiskReady | 002f3f98 |
| 002cbdf8 | ps2CdNCommand14 | 002f39a0 |
| 002cc5e8 | ps2CdSCommand22 | 002f4190 |
| 002cc6b0 | ps2CdGetDiskType | 002f4258 |
| 002cc800 | ps2CdSCommand21OutputWord | 002f43a8 |
| 002cc8b8 | ps2CdReadClock | 002f4460 |
| 002cc9b0 | ps2CdStreamInitialize | 002f4558 |
| 002cca18 | ps2CdStreamSeekFast | 002f45c0 |
| 002cca48 | ps2CdStreamSeek | 002f45f0 |
| 002ccc38 | ps2CdStreamPause | 002f47e0 |
| 002ccc88 | ps2CdStreamResume | 002f4830 |
| 002ccce0 | ps2CdStreamStatus | 002f4888 |

## Search and readiness

Search retains the polled N semaphore, stores command 1 before thread-status
and N-wait checks, and binds client 598e40 to service 80000597 when flag 52a040
is negative. The 300-byte packet at 598cc0 contains a 36-byte result record,
a 256-byte path at offset 36, its own pointer at offset 292, and the low layer
word at offset 296. The two-argument wrapper supplies layer zero.

The path copies one byte at a time, stopping at a terminator or 256 bytes.
At the latter limit byte 255 is forcibly terminated. Cases exercise lengths
0, 1, 5, 255, 256 and 300. Empty paths leave the remaining bytes untouched.
RPC command 0 receives a four-byte status at 598e00. Ordinary IOP arrival also
writes the uncached 36-byte record, then the actual response handler releases
the packet and signals its semaphore.

Four uncached doublewords are loaded before any of their output stores. The
final word is loaded afterward. This ordering is preserved for unaligned and
overlapping outputs, including overlaps with the record, cached pathname and
uncached status. Debug messages use the actual SDK formatter and re-read debug
level between name, size and sector prints. The return word is loaded only
after output and diagnostics, before releasing the N semaphore.

DiskReady retains the S semaphore, checks actual S RPC activity, and binds
client 598e90 to service 8000059a through flag 52a044. It flushes a four-byte mode
packet at 598ed0 and uses RPC command 0 with a four-byte status reply at 52b200.
A failed poll returns 6 for every mode. Later failures return -1 only if the
full 64-bit input equals 8; 0x100000008 returns 6 despite having the same low
word. Success loads the uncached status before release. Both failed-bind and
empty-server retry paths execute the full original 1,048,577-iteration delay
in the capture, as do the existing N/S preflight retries.

## Control, clock and streaming

N command 14 uses preflight command 2. Disk type uses S preflight command 1 and
RPC command 3. S command 22 uses preflight/RPC command 34 and a four-byte mode
packet at 52b640. Names without independently retained SDK spellings remain
descriptive rather than assuming the public API declaration.

S command 21 receives eight bytes. It stores reply word 1 to the caller before
reloading reply word 0 as its return, preserving output aliases with the reply
and semaphore. Clock uses S preflight command 15, RPC command 1 and a 16-byte
receive buffer. It loads and stores exactly eight bytes from uncached reply+4,
then reads debug level and status again. Output overlaps with the reply and
debug globals are compared.

The remaining stream wrappers execute the existing complete StreamCommand:
operation 5 initializes from the original incoming A0/A1/A2 and clears active;
operations 9 and 4 seek; 7 pauses and clears active; 8 resumes and sets active;
6 reports status without changing active. Flag updates precede request failure
and diagnostics, matching the original bodies.

## Evidence and limits

Current reports remain `cd-stream-validation.json`, `cd-stream-transfer.json`,
`cd-stream-interfaces.json` and `cd-stream-abi.json`, with one rolling capture
under `cd-stream/`. The previous capture was overwritten, not duplicated.
Working interfaces are saved in place, independently reopened and checked;
23 selected exports are merged into the existing 8,958-entry inventory.

All 23 full DDS spans match uniquely with 84 agreeing callee destinations.
Only explicit address immediates and J/JAL targets are masked. Service IDs,
packet sizes and offsets, branch geometry, copy instructions, NOP delay loops
and cached/uncached address formation stay constrained. Alternate-path address
LUI definitions are masked explicitly; a linear scan alone can hide their use
behind another branch's definition. DDS files are read-only.

A search of the extracted Unity method inventories for sceCd/CdSearch,
DiskReady/CdSt and cdvd names finds no retained direct CD SDK identities.
These platform functions therefore use PS2 instruction evidence and the DDS
transfer comparison, without claiming a Unity counterpart.

Actual recovered RPC/bind/response/cache/semaphore/timer/init/debug bodies run.
Kernel results, finite ordinary IOP reply/busy memory arrivals and zero for the
otherwise unwritten RPC semaphore option are external operand boundaries.
Physical disc/PS2/IOP execution, timing, arbitrary interrupt reentrancy and a
matching executable remain unproved. CD initialize/exit/callback functions are
now recovered in the same rolling group. Movie/archive callers and their
separate libc formatter and nonreturning fatal spin remain next.

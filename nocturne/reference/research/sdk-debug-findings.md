# Connected SDK formatter and output recovery

Nine complete routines in `src/sdk_debug.c` now pass1,792 original-instruction/C
comparisons, covering2,356 recognized body bytes. Every one of their450 non-delay
instruction addresses was reached. All nine interfaces were saved in the working
Ghidra project, independently reopened and checked, and their current exports
merged into the8,958-function inventory. No new HD counterpart is claimed for
these platform routines; names are descriptive aliases.

| Nocturne | Recovered role | DDS complete-span candidate | Cases |
| --- | --- | --- | ---: |
| 002dd420 | Serial character output | 0030bfa0 | 128 |
| 002dd508 | Serial CR-before-LF wrapper | 0030c088 | 128 |
| 002dd458 | Buffered character output | 0030bfd8 | 256 |
| 002dc2d0 | Raw kernel command, selector7C | 0030ae50 | 64 |
| 002e4a50 | Kernel string command16 | 003135e8 | 128 |
| 002dd5d0 | SDK float-format path | 0030c150 | 64 |
| 002dd738 | SDK variable-argument formatter | 0030c2b8 | 512 |
| 002ddd28 | Seven-slot printf wrapper | 0030c8a8 | 256 |
| 002ddd60 | Buffered printf wrapper | 0030c8e0 | 256 |

The formatter saves seven64-bit integer argument slots. Each consumed argument
advances by8 bytes. Default numeric conversions read a word, h reads a halfword,
and l reads all64 bits; d sign-extends while o/x/u zero-extend. Character conversion
reads a signed byte. String conversion reads a32-bit pointer, dereferences it
before testing for emptiness, and emits `(null)` for an empty string. A null pointer
is not given an invented fallback. The original73-entry table supports only
0,c,d,e,f,h,l,o,s,u,x. Unknown conversions are skipped, including `%X`, `%i` and
`%%`. Zero-fill widths use one or two following digits and cap at31.

Signed decimal output invokes the actual recovered signed division/remainder
helpers, including the original INT64_MIN magnitude overflow and resulting digit
quirk. Unsigned decimal invokes the actual unsigned helpers. Octal and lowercase
hex retain bit extraction. The callback at52c2b4 is loaded freshly for every
character. Tests execute the real serial, newline or buffered callback bodies;
they do not supply callback results or rendered strings.

Serial output polls1000f130 bit8000, then writes one byte to1000f180. The newline
wrapper inserts CR only when the entire raw64-bit argument equals10; a different
raw value whose low byte is10 does not trigger CR. Buffered output uses59b940 and
cursor52c2b0. Signed cursors>=126 clear the cursor and byte127, invoke kernel
string output, then reload the cursor. Raw LF clears the cursor, appends LF/NUL
and tail-calls the same string service. Kernel command16 passes one low32-bit
string-address word through selector7C.

The formatter disables interrupts through the actual recovered helper and restores
them only when its initial saved enabled flag was nonzero. The buffered printf
wrapper temporarily installs callback002dd458, then restores the original callback
word. Supplied ordinary kernel mutations change the cursor and callback at a
flush; later characters follow the reloaded state. Tests include argument/cursor
aliases and a format sharing the output buffer. All new non-delay PCs are reached
with returning interrupt contexts; nonterminating unprivileged DI is untested.

The float route consumes the low single-precision word, treats both signed zeros
as zero in the tested equality model, then invokes the actual soft-float-to-double
and numeric helpers. Both e/f use the same path. It normalizes a finite magnitude
into0.1..1, multiplies by1,000,000, converts to unsigned64, and passes that integer
word directly to the raw-double-bit rounding helper before formatting `0.%d`.
This call sequence produces a zero mantissa in all tested direct float-format
cases, followed by its computed exponent; the reconstructed code retains it.
Do not replace the sequence with host printf or repair its apparent intent.
Direct zero/NaN/infinite helper inputs and subnormal single comparisons are not
returning cases in this validation. Their original loops are not rewritten with
a new success return or iteration cap.

The capture executes4,317,357 original steps. It checks the full5,328-byte declared
RAM, defined raw returns, Status, and317,845 ordered trace words. There are19,907
actual callback invocations,1,040 kernel commands,12,685 serial-status reads and
129 observed single-precision zero comparisons. Kernel command packets use a
typed host stack pointer normalized to the consumed string-address word; private
PS2 stack addresses and unused packet fields are not claimed equivalent. Finite
serial-ready values, kernel results and cursor/callback mutations are external
service inputs. Physical UART/kernel/IOP behavior, FCSR side flags, invalid strings,
malformed trailing formats and exhaustive data aliases remain unproved.

All nine complete DDS instruction spans match uniquely with only explicit global,
callback/data-address and J/JAL relocations masked. Fixed MMIO addresses, flags,
widths, branches, registers and character literals agree. All73 relative dispatch
routes, scientific constants and formats, the installed buffered callback, and
19 connected output/numeric calls agree independently. Relocated storage is
cursor39c458, callback39c45c and buffer4077c0. DDS remains read-only; these are static
comparisons, not DDS runtime or original symbol recovery. See
`sdk-debug-transfer.json` and `sdk-debug-validation.json`.

The changed interrupt-value adapter also passes the retained disc-platform1,344
and display-control576 comparisons. This is affected focused coverage, not a
new full-suite run. Integration is637 functions/538,268 aggregated comparisons;
the last full suite remains413 functions/462,684 cases.

Next: recover CD N/S preflight002cbc88/002cbfa0, wait002cbe90/002cbf30 and stream
commands through the actual now-recovered SDK printf, RPC busy, semaphore and
timer services, then movie/archive lookup/seek/read. The separate libc printf
002d4748->002d6600, fatal diagnostic002a82b0, CD lookup and readiness services
remain real dependencies. The movie reader/worker, scheduler/pump, full moon
initializer, full executable source, PS2 runtime and matching binary remain open.

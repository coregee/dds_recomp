# Native dtoa recovery

The complete native body at002d8378 is reconstructed in `src/libc_dtoa.c` and
compiles with warnings treated as errors. Its original join labels remain to
support instruction review, while the recovered state has names for numerator,
denominator, margins, digit limits and output/cache records. It calls the actual
recovered bigint, heap, memory and software-double implementations; it does not
use a host floating formatter. All4,096 returning-call comparisons pass against
the original instructions, covering131,852,974 instruction positions and389,674
ordered trace words. No arithmetic traps or zero-DIVU bypasses occur in this batch.

## Native state and paths

Seven raw64 slots carry context, double bits, mode, precision, decimal-point word,
sign word and optional end-pointer word. Mode/precision/output pointers saved with
SW use their low words; sign inspection uses the original double high word.
Reentrancy64 holds the previous output buffer and68 its allocation class. Each call
restores that cached record's class/capacity from68, recycles it through Bfree and
clears64 before inspecting zero, infinity or NaN. Those early returns use the
original static strings54b898/54b880/54b890, with decimal-point1/9999, a sign word
and optional end pointer. Normal output is a NUL-terminated guest buffer held in64.

All three conversion paths are retained: quick scaled-double/error-bound tests,
small-integer quotient/remainder, and full normalized bigint division/margins.
Modes0/1 use shortest-digit margins, with mode0 allowing equality/tie-to-even tests;
2/4 limit significant digits (at least1),3/5 use requested fractional positions,
and6..9 map to2..5 while disabling the quick path. Values outside0..9 become0.
The code retains fallback from quick to bigint work, whole-word/bit normalization,
asymmetric margins for powers of two, trailing-zero trimming and carry through9s.
Software-double operations use the recovered raw-bit routines throughout.

Private d2b scratch is temporarily represented by two mapped guest words. This
preserves actual recovered helper execution while leaving private stack placement
unproved. The test mode maps the additional original constants through54bbff;
its stream/heap adapter remains inactive during ordinary older test modes.

## Native negative digit-limit edge

A separate original-instruction diagnostic uses minimum-normal bits0010000000000000,
mode5 and precision-32. The native body calls pow5 with648 and then with-340.
At that second call, root b5 is308 and ilim is-339. Arithmetic right shifts of the
negative exponent never reachzero, so the pow5 loop continues growing its cache;
the diagnostic reaches1,000,000 instruction positions inside multiplication rather
than an ordinary dtoa return. Later heap exhaustion/exception behavior is unproved.
The recovered source retains the unchecked negative call and arithmetic-shift
loop. It does not add a clamp or invent a successful formatting result.

Returning-call fixtures choose positive digit limits for modes5/9. Other modes
retain negative/zero precision cases, and the negative-limit trace remains a
separate finding rather than a passing returning-call comparison. An initial
fixture issue combined a reused output with a missing free-list table, which could
not arise from a previous successful allocation; the fixtures now preserve that
native reentrancy invariant.

## DDS transfer evidence

The full contiguous dtoa span matches uniquely at DDS00305fe8 when verified indexed
lookup-table address pairs are relocated. All other instruction words, arithmetic,
branch geometry and offsets stay fixed. There are105 agreeing call links and six
repeated global-address constraints across dtoa and its dependency cohort. Eight
string/constant spans are byte-identical, including the decimal power tables; all
six mode-table targets have identical offsets relative to their respective dtoa
entries. DDS soft-double multiplication has no complete-span match with the current
mask. This is static transfer evidence, not DDS execution or matching-ELF proof.

## Current validation

The rolling4096-case capture and comparator cover original modes, raw high argument
bits, precision limits, zero/subnormal/normal/nonfinite values, adjacent decimal
rounding bit patterns, cached/new output/free-list/power states and aliased output
words. Every returning-call comparison checks the entire101,012-byte declared RAM,
raw64 result, Status and ordered heap/kernel/interrupt traces. Original guest writes
must remain in those spans or private stack, and returning roots preserve saved
registers, GP/SP/RA and zero. Output-buffer and stack layout equivalence to a compiled
PS2 executable, hardware and unbounded malformed/failure calls remain unproved.

The existing18 stream functions still pass their1408 affected comparisons after
adding the inactive dtoa address mode. No new full regression or archived capture
is claimed. Coverage reaches850 of904 non-delay addresses. The34 missing addresses
from002d8550 through002d85ec belong to subnormal normalization: actual
ps2SoftDoubleCompare first flushes subnormal operands to zero, so dtoa returns its
zero string before that branch. The other20 addresses remain explicit test gaps
in short/slow conversion, negative digit-limit adjustment and rounding ties;
their source is retained, without a claim that every branch has been exercised.
The raw64 interface is saved in the working Ghidra project and independently
reopened; its selected export decompiles successfully and merges into the current
8,960-function inventory. This adds one integrated routine, bringing recovery to
723 functions and552,998 aggregated comparisons. The last full comparison remains
413 functions/462,684 cases. Source, mappings and rolling reports were updated in
place, without checkpoint or project copies.
Next is the libc cvt wrapper
002d7ce8 and the main formatter chain002d4748->002d6600->002d6678, with its local
buffer wrapper002d6548 and movie/archive diagnostics.

# Complete native formatter recovery

Three complete bodies are now integrated in src/libc_formatter.c: main
vfprintf002d6678 (5,652 recognized bytes), stream/context wrapper002d6600 (116)
and stack-buffer wrapper002d6548 (180). All704 comparisons pass against original
instructions through actual cvt/dtoa,bigint,heap,software-double,integer division,
string,byte-widening and vector/stream bodies. The source compiles with warnings
treated as errors. Saved raw64 interfaces are independently reopened; all three
selected exports decompile and merge into the current8,960-function inventory.

## Preserved behavior

The formatter retains eight-entry pointer/count vector batches and16-byte chunks
for space/zero padding. Actual Sprint and WriteVectors execute; string-mode bit512
limits physical copies while retaining requested character counts. Zero-capacity
and short buffers therefore preserve native truncation behavior. Ordinary write
preparation, missing/default stream context, actual stdio initialization and
preexisting error flags are included. The unbuffered wrapper clears bit2 on its
private FILE,uses a1,024-byte buffer,calls the real formatter and Flush,and propagates
bit64/failure to the original stream.

Integer arguments occupy eight-byte slots. Flag16 selects full64-bit long values,
flag64 narrows to16 bits,and ordinary arguments use low32 bits. Native ll/q set
flag32,but the integer and count-store decisions ignore it; this behavior is
retained rather than changed to host printf semantics. Pointer conversion sign
extends the native32-bit pointer before hex conversion. Width/precision parsing,
star arguments,negative widths,alternate prefixes,zero/sign/space/left padding,
short/long count stores,unknown characters and trailing percent are covered.

Floating conversion calls the actual cvt/dtoa chain. Inf and NaN take separate
native string paths; f,e/E,g/G retain their own size,decimal-point and exponent
decisions. General format chooses exponent form when decimal point is below-3
or above precision. The native software comparator's subnormal-tozero behavior
is preserved. Large padding/precision cases exercise repeated batches; the code
does not use a host number formatter.

## Evidence and limits

The final rolling batch contains512 main-formatter,128 stream-wrapper and64
stack-buffer-wrapper calls:6,635,387 original instruction positions,13,120 ordered
trace words and450 original EE MMI observations. All102,036 declared bytes are
compared according to the spans recorded in libc-formatter-validation.json;
raw64 results,Status and primitive/kernel traces agree. No arithmetic traps or
zero-DIVU bypasses occur. Both wrappers reach every non-delay address (25/25 and
40/40); main coverage is987/1,124. Its137 remaining addresses are listed explicitly,
including particular batch-position flushes,some narrow/count/string decisions,
the unreachable bad-base diagnostic and the tiny leading-zero padding path.
Complete branch coverage is not claimed.

Selected output failures use the real original CloseUnsupported body as the
configured write callback. Its invocation is observed before its native instructions
execute; no callback/library result is replaced. For private stack data,the trace
compares the actual consumed byte sequence and count rather than claiming equal
compiled stack addresses. Both ordinary public-buffer pointers and private payloads
are distinguished. Actual successful console/IOP timing,unbounded malformed inputs,
allocation exhaustion and a matching compiled executable remain unproved.

DDS main vfprintf has no complete-span match under the current relocation mask.
The two wrappers each retain two candidates. Five agreeing dependency call links
and two repeated global constraints support the cohort; these are transfer leads,
not unique whole-formatter identities. The already recovered cvt/dtoa mappings
remain stronger transfer anchors.

Recovery is727/8,960 functions with554,214 aggregated comparisons (8.11%). The last
full comparison remains413/462,684; no new full-suite result is claimed. Work and
rolling evidence were updated in place,without checkpoints or project copies.
Next is the libc printf register-save entry002d4748,then the movie/archive
readiness/seek/sector/lookup paths that depend on its real diagnostics.

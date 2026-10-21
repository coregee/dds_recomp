# Movie disc readiness and stream retries

Three complete bodies are integrated in `src/movie_archive.c`:
`ps2MovieWaitForDisc` (`002bd5d8`, 200 recognized bytes),
`ps2MovieStreamSeek` (`002bd6a0`, 172 recognized bytes) and
`ps2MovieStreamRead` (`002bd750`, 228 recognized bytes).

All 288 original-instruction/C comparisons pass. The batch executes 3,021,738
original steps and compares full declared RAM, raw 64-bit returns, CPU status,
388,704 ordered trace words and actual reply consumption. All 105 recognized
non-delay root instruction addresses are reached. The seek span also contains
one four-byte gap outside its recognized function body.

Readiness holds the movie semaphore while repeatedly delaying, checking disc
readiness, printing diagnostics, checking media type and searching the requested
file. Media selector `551918 == 2` requires type 20; other values require type
18. Wrong media and failed searches retry. Successful readiness returns the
final diagnostic printf's value, which the original callers ignore.

Seek constructs four private mode bytes; the second byte is zero only when
`552110 == 1`. It locks, starts the actual CD stream and unlocks. Failed starts
query the actual error service: error 1 waits for the disc; other errors delay
before retrying. Successful seek records the low sector word at `55210c` and
leaves the full SignalSema result in V0. The older 32-bit semaphore convenience
API cannot preserve this return, so the recovered caller uses the same kernel
boundary with full-width transport.

Read keeps the original full-width count comparison and error test. Error 1
waits for disc readiness; other errors print a diagnostic and stop the stream.
Both routes seek the saved sector before retrying. The successful sector update
wraps as a word and is sign-extended in the returned register value. Cases cover
zero counts, partial reads retaining a previous error, stop/start retries,
debug output, string-stream truncation, failing buffered output and unbuffered
private output. Actual libc printf/formatter, CD preflight/search/readiness,
stream commands, RPC/response and FileDelay code executes.

The host comparison now shares one address space and ordered kernel/reply trace
between libc and CD dependencies. Each case resets its private SDK diagnostic
trace; a missing reset caused a harness-only capacity failure during this work.
Private output addresses are compared through their consumed bytes rather than
through host/native stack addresses. Kernel values, ordinary IOP memory arrivals
and the unwritten RPC semaphore option remain explicit external inputs. No
library or movie return value is substituted.

An inactive CD stream returns without writing the private read-error word; that
state is outside this returning batch. Indefinite retries, arbitrary malformed
data, physical disc/scheduler behavior, compiled stack placement and a matching
PS2 executable remain unverified. Direct disc lookup's live Open operand remains
separate work: without debug output, successful SearchFile's A2 is the raw
doubleword loaded from record bytes 24–31, not a supplied zero mode. Debug output
can clobber it and still needs a corresponding transport model.

No full-span DDS candidate matches these three movie-specific bodies under the
current relocation mask. FileDelay, SearchFile, stream start/stop/read and libc
printf retain useful static dependency candidates. The transfer report records
seven agreeing dependency global relocations; it does not prove equivalent DDS
movie callers. Unity metadata retains `mviManager.moviePlayFile`, `moviePlay`,
`movieStop` and movie script entry points as leads for higher-level recovery.

The current focused reports are `movie-disc-validation.json` and
`movie-disc-transfer.json`. Ghidra interfaces are saved in place, independently
reopened and merged into the current whole-program export. The affected CD,
formatter, printf and archive comparisons also pass with the shared host build.

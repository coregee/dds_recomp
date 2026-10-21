# Movie draw packets and command queue

Thirteen complete PS2 routines are integrated in `src/movie_draw.c`: 1,432
recognized body bytes and 1,248 passing original-instruction/C comparisons.
The capture reaches all 342 non-delay root instruction addresses, executes
139,078 original steps and compares 9,638 ordered trace words. The affected
movie-file (384), movie-worker (384), movie-disc (288) and CD (2,250) comparisons
also pass. Changes are saved directly in the working project; reports and the
single `movie-draw/vectors.jsonl` capture are rolling outputs.

| PS2 entry | Recovered routine | Body bytes |
| --- | --- | ---: |
| 0022b6e0 | ps2MovieDrawProcess | 44 |
| 002c5170 | ps2MovieBuildDrawPacket | 596 |
| 002c2218 | ps2MovieRegisterCommandCallback | 28 |
| 002c2238 | ps2MovieSetOutputMode | 68 |
| 002c10e8 | ps2MovieCommandEnqueue | 332 |
| 002c0f28 | ps2MovieCommandPump | 148 |
| 002c1238 | ps2MovieCommandTokenIgnore | 8 |
| 002c1240 | ps2MovieCommandSubmit | 52 |
| 002c6010 | ps2MovieControlCheckEnd | 28 |
| 0022b7d8 | ps2MovieCheckEnd | 28 |
| 0022b7f8 | ps2MovieCheckDrawState | 12 |
| 002ae090 | ps2DrawChainCreate | 72 |
| 002dbdd0 | ps2KernelWakeupThreadRaw | 16 |

## Corrected callback and packet construction

The launcher at `0022b710` passes callback `0022b6e0`. Ghidra previously started
that function eight bytes late at `0022b6e8`, omitting `lui a0,0x34` and
`lui a1,0x2f`. The corrected 44-byte body passes fixed movie control `343e40`
and ordering object `2f6638` to the draw routine and returns zero. Its saved
zero-argument interface and all twelve other interfaces pass after reopening;
all thirteen selected exports are merged into the current 8,960-function index.

Draw requires control byte `+34 >= 2`. Decoder startup additionally requires
nonzero `+20`, zero `+21`, and signed decoder-record word `+68 >= 4096`.
It sets `+21`, writes control to `552168`, registers callback `002c5098` and
submits the output mode from byte `+22` through the actual command queue.
Both passing and rejected startup thresholds and busy registration are tested.

The body allocates 176 bytes through the actual work-buffer routine and writes
22 doublewords of DMA/GIF/GS data. It preserves signed 16-bit coordinates,
unsigned 16-bit texture dimensions, the EE leading-sign-word size calculation,
signed-word UV shifts, raw Z/base words and the format byte at `+38`.
Native constants include `0100000a`, `5000000a00000000`,
`108b400000008009` and `ffffffff80808080`. The actual chain allocator takes
32 bytes, initializes a chain, appends the packet and invokes the selected
ordering callback `002acd40`. The callback receives the full 64-bit ordering
argument, while memory addressing uses its low word.

## Queue behavior

The ring at `590840` has 32 slots of 128 bytes. Signed halfword head/tail indexes
are at `552132/552134`; the word token at `5519d0` increments and skips zero.
Enqueue writes token at packet `+16`, copies optional payload at `+20` through
the actual memcpy and packs command/flags/length at `+12`.

The full-ring path is unusual: it performs eight WakeupThread calls, repeating
each while the live head differs from the next slot, then returns zero without
writing a packet. The comparison checks the eight calls and token increment.
Asynchronous enqueue wakes the thread at `552138`; synchronous enqueue calls
the real pump until it returns zero, then reloads the live token word.

Pump returns one for an empty ring. Otherwise it sends actual SIF command zero,
using the upper nibble of packet byte 15 as length and no payload DMA. Failure
prints the original diagnostic through the recovered printf/formatter and
returns one; success advances the head modulo 32 and returns zero. Tests include
failed-send retry followed by success and transport rejection of oversized
packets. Submit retains the enqueue result across the actual token no-op.

Callback registration stores the low pointer word but returns the full incoming
64-bit value when not busy. Output-mode submission ignores its token result.
Control end-check requires nonzero `+33` and zero `+3e`; draw-state returns the
raw byte at `343e74`. The HD draw-state helper maps its manager state to zero
or two instead, so that role does not justify substituting the HD behavior.

## Unity leads and SMT transfer

HD `mviManager.moviePlayFile` at `1828156a0` and PS2 launcher `0022b710` both
construct process type `2afb`. HD draw `182814df0` uses asset bundles and
Unity VideoPlayer; the PS2 draw constructs GS packets. The shared process graph
helps identify roles, but these routines remain descriptive PS2 aliases rather
than promoted exact HD identities.

Static full-span transfer resolves five DDS candidates: token no-op `002e88f8`,
submit `002e8900`, control end-check `002edbb8`, chain create `002d5510`, and
WakeupThread `0030a950`. Submit-to-no-op and chain-create-to-initialize calls
agree; the tiny no-op is resolved through its incoming call constraint.
Eight other bodies have no match under the current mask, which retains GP data
displacements. That absence does not establish different algorithms. These
are transfer leads, not DDS execution results.

Movie control initialize `002c5d28` and its decoder setup/list helpers now have
compiled source; see [initialization findings](movie-initialize-findings.md).
Continue the actual streaming callbacks, decoder shutdown, control close
`002c5f38`, and launcher/index/stop wrappers `0022b710/0022b768/0022b7a0`.
Those dependencies remain necessary before treating the whole movie manager
as compiled source.

## Verification limits

The comparisons use real recovered allocation, chain/list, memcpy, SIF/cache
transport and diagnostic callees. They compare all sixteen declared RAM spans,
defined raw 64-bit results, Status/primitives and ordered allocator/ordering/
kernel/cache events. Native writes are checked against those spans and the
private stack; the original archive index remains unchanged. Shared media
windows support the common interpreter setup but draw cases consume no media.

Kernel results, selected callback binding and bounded transport outcomes remain
external inputs. Malformed queue indexes, indefinite retries, arbitrary callback
allocators, physical GS/IOP/scheduling, PS2 runtime and a matching executable
remain unproved. Instruction-address coverage is not proof of every possible
path or input. Current aggregate recovery is tracked in `recovery-progress.json`;
the last full run remains 413/462,684.

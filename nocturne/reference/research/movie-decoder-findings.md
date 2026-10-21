# Decoder scheduling, IPU state and movie close

Eighteen complete routines in `src/movie_decoder.c` add2,900 recognized body
bytes and3,456 passing original-instruction/C comparisons. All597 non-delay
root PCs are reached. The affected source and bindings compile with warnings
treated as errors and link into the current library. Interfaces are saved in
place in `ghidra/working/Nocturne.gpr`, independently reopened, and all eighteen
current exports are merged into the whole-program inventory.

| PS2 entry | Recovered routine | Body bytes |
| --- | --- | ---: |
| 002a8d18 | ps2PoolContainsPointer | 32 |
| 002a96c0 | ps2MemoryHandleFindPointer | 200 |
| 002a95f8 | ps2MemoryPointerFree | 32 |
| 002a81b0 | ps2PoolOrMemoryPointerFree | 76 |
| 002aacd0 | ps2MovieDeferPointerFree | 180 |
| 002aa868 | ps2MemoryHandleDeferFree | 28 |
| 002cd680 | ps2MovieIpuFromDmaControl | 100 |
| 002cd6e8 | ps2MovieIpuToDmaControl | 100 |
| 002cd750 | ps2MovieIpuSaveContext | 228 |
| 002cd838 | ps2MovieIpuRestoreContext | 336 |
| 002cd988 | ps2MovieIpuWait | 104 |
| 002c4608 | ps2MovieDecoderInputDma | 196 |
| 002c4740 | ps2MovieIpuReadHeader | 108 |
| 002c47b0 | ps2MovieDecoderStart | 460 |
| 002c4980 | ps2MovieDecoderSchedule | 192 |
| 002c42b0 | ps2MovieDecoderDestroy | 308 |
| 002a8078 | ps2MovieClosePollHook | 8 |
| 002c5f38 | ps2MovieControlClose | 212 |

## Ownership and release

Pointer release compares the signed incoming pointer against the pool arena
bounds at00552060/64. Pool pointers execute real pool release. Other pointers
walk the handle list at00577f1c until a state1 descriptor's data pointer agrees,
then execute real handle free and its neighbour coalescing. The original lookup
has no missing-pointer return. A state2 descriptor can restore interrupts
before the walk finishes; that ordering is preserved and exercised.

Pointer deferral allocates a zeroed160-byte record and records either type2/
pool pointer or type1/memory handle. It appends under semaphore00581018 to
head/tail0058101c/20. Handle deferral uses the separate existing deferred queue
at00552098, including its actual pool-allocated blocks and semaphore wrappers.
No allocation, free or queue callee result is substituted.

Decoder destroy sets stop byte+0x0f, removes owned and queued membership, and
resets IPU/DMA state when the decoder owns active slot00552154. It frees three
direct resources, defers two pointers, frees the staging allocation through
its original pointer-minus0x100, and defers the optional handle. It schedules
the next eligible decoder after destroying the active decoder.

## IPU/DMA state and scheduling

The nine-word saved context retains To/From-IPU DMA addresses, counts and
controls, plus IPU_BP and IPU_CTRL. Restore calculates buffered quadwords as
`((BP >> 8) & 15) + ((BP >> 16) & 3)`, subtracts16 bytes per buffered quadword
from saved input MADR and adds them to QWC. Zero address/count paths and busy
polls are covered. The two DMA-control helpers unconditionally call interrupt
enable after modifying the DMA enable registers, even when entry interrupts
were disabled; the source retains this original behavior.

Input setup preserves chain mode105 with a masked tag pointer, normal mode101
with512 quadwords and the selected0x2000-byte staging half, and the no-input
flag path. Start toggles the output buffer, truncates signed byte length toward
zero on division by16, saves/restores actual context, reads the original IPU
header commands40000000/40000008, and constructs the decode command using the
configuration pair at00529ce8. Scheduling skips ineligible queued decoders,
executes real unlink/start bodies, and preserves the caller's interrupt-owner
flag.

## Close completion and comparison boundary

Close sets stop byte2, requests a close immediately for stalled state5, and
waits for state6. The called hook002a8078 is exactly JR RA/NOP in the original
executable. It does not advance a frame or itself change the file state.

Finite external IOP arrivals are supplied while the original wait loop runs.
The comparison executes the complete ordinary/IPS callbacks: cancellation
requests a close, and close completion releases the real terminal job and
changes state7 to6. It does not force state6 in memory. The192 close cases
include152 cases with arrivals,244 callback executions and92 two-callback
cancellation/completion cases. Poll counts span zero through four. Close then
frees the original ordinary/IPS handles and record, destroys the decoder,
optionally submits command100, and clears its active byte.

The capture executes718,894 original steps and compares176,209 ordered trace
words, including15,473 MMIO reads and the corresponding ordered stores.
Incoming register values and busy sequences are explicit external inputs;
every native load/store still executes. Full declared RAM, defined raw64
results, interrupt Status, primitive counts and kernel/IOP/MMIO ordering agree.
Writes remain within declared RAM/private stack, and the archive index remains
unchanged. See `analysis/movie-decoder-validation.json` for hashes and scope.

The domain uses valid backed pool/handle metadata and finite arrivals. Null
handles are canonical zero; a noncanonical high word with a zero low32 handle
passed to the existing low32 deferred-queue interface is outside this domain.
Missing-pointer walks, malformed lists, exhaustion and indefinite busy waits
remain unproved. The host arrival/MMIO bindings are external-event models,
not physical IPU, DMA, IOP or scheduler execution. Complete decoded media,
PS2 runtime and matching-executable validation remain unfinished.

Affected initialization768, worker384, streaming1,344 and draw/command1,248
comparisons still pass. Current aggregate recovery is783/8,960 routines and
571,991 comparisons; the last full comparison remains413/462,684.

## Unity and DDS transfer

The local Unity corpus confirms `mviManager$$movieStop` at182816790 pauses the
VideoPlayer and calls `release_movieobj` at182816e50; that release routine uses
VideoPlayer audio-target, stop and clip operations. Those paths do not supply
an equivalent PS2 IPU implementation. The retained movie-process graph and
type2afb remain useful for the higher-level launcher/stop identities.

Twelve complete DDS spans match uniquely, with30 agreeing call constraints and
one global constraint. The tiny empty hook is constrained by its complete
close caller's matching call site; its semantics are not inferred from a bare
NOP match. Other decoder bodies retain explicit unresolved candidates under
the current GP-sensitive mask. See `analysis/movie-decoder-transfer.json`.
These are static transfer results, not DDS runtime equivalence or exact Unity
symbol promotions.

Launcher0022b710, indexed launcher0022b768 and stop0022b7a0 now execute the
recovered process create/kill and initialize/close paths;see
[movie manager findings](movie-manager-findings.md). Decoder completion/interrupt
handlers and the worker-to-decoder payload path remain connected work.

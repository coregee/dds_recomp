# Movie launcher, stop and decoder FIFO

Four complete routines in `src/movie_manager.c` add356 original body bytes and
256 passing original-instruction/C comparisons. All71 non-delay root instruction
addresses are reached. The affected C compiles with warnings treated as errors.
Names and interfaces are saved in the working Ghidra project, independently
reopened, and the four current exports are merged into the existing inventory.

| PS2 entry | Recovered routine | Body bytes | Unity reference |
| --- | --- | ---: | --- |
| 0022b710 | ps2MoviePlayFile | 88 | 1828156a0, moviePlayFile(string, parameters, Layer) |
| 0022b768 | ps2MoviePlayIndex | 52 | 182815c00, moviePlayFile(index, Layer) |
| 0022b7a0 | ps2MovieStop | 56 | 182816790, movieStop |
| 002c3b40 | ps2MovieDecoderQueueAppend | 160 | Descriptive PS2 alias |

Play checks process slot0054fd94, initializes the fixed movie control00343e40,
and creates `movieDraw` with priority0x2afb, startup/shutdown delays1, callback
0022b6e0, and zero shutdown callback/data. The actual constructor allocates the
process and inserts it into the real starting list. Guarded calls preserve the
existing state. Indexed play uses the original table at00343be8 with24-byte
filename/inline-parameter records and wrapping32-bit multiplication. Four
backed original indices and equivalent wrapped/high-lane inputs are exercised.

Stop executes the complete movie close path, reloads the process slot, executes
the actual kill/list/unlink/pool release bodies and clears the slot. Finite
external IOP arrivals execute the recovered ordinary/IPS callbacks. The kill
diagnostic now executes the actual printf/formatter with the process name.
Empty process slots and process states0/1/2/3 are covered. Full declared RAM,
Status and ordered kernel/IRQ/MMIO/callback/output traces agree.

FIFO insertion unlinks existing membership before moving a decoder to the tail.
Cases include empty queues, different existing positions, new nodes and raw64
interrupt ownership values. All original queue operations execute.

The two Unity play overloads retain the same process priority, delays and null
shutdown/data pattern. Unity stop releases its movie object, calls process kill
with delay0 and clears its process slot. These are reviewed semantic counterparts;
Unity adds managed delegates/data, localization, Layer and VideoPlayer behavior.
The reference export reports one-byte entry bodies, so complete native reference
segmentation and byte-level equivalence are not claimed. See
[match review](movie-manager-matches.json).

No new full-span DDS counterparts resolve for these four bodies. Existing process
create/kill and close dependencies supply separate transfer anchors. The manager
and FIFO fingerprint is recorded in `shared-smt-signatures.tsv` and the unresolved
search in [transfer report](movie-manager-transfer.json).

Affected checks also pass: process creation1536, process lists2560, process
shutdown2816 and decoder/close3456 cases. These reuse the current original captures;
no new full-suite run is claimed. Physical video decoding, IPU/IOP scheduling,
exhaustion, malformed lists/indices, PS2 runtime and matching binary remain
unproved. Continue decoder completion/interrupt handlers and the worker-to-decoder
payload path.

Current compiled recovery is787/8960 functions,8.783%, with572247 aggregated
comparisons. [Validation](movie-manager-validation.json) records the current proof.

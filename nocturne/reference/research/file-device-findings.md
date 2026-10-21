# File devices, requests and worker startup

Eleven complete original routines are now canonical C, covering 1,732 recognized
body bytes. They include the full request path through actual normalization,
job construction, dual queue append and worker startup. Existing allocation,
semaphore and job routines are called directly. No game-function return or
worker result is supplied.

| Entry | Recovered routine | Body bytes |
|---|---|---:|
|002be588|ps2FileHostRoot|12|
|002befc0|ps2FileNormalizePath|576|
|002bf208|ps2FileResolvePath|276|
|002a80a8|ps2ThreadCreateWithStack|120|
|002a8120|ps2ThreadCreateAllocated|80|
|002bf8f0|ps2FileDeviceInitialize|172|
|002be5b8|ps2FileJobEnqueue|232|
|002bf3a8|ps2FileRequestRead|104|
|002bf410|ps2FileRequestStream|128|
|002dbca0|ps2KernelCreateThread|16|
|002dbcc0|ps2KernelStartThread|16|

Disc normalization prepends `cdrom0:`, converts slash to backslash, uppercases
ASCII lowercase bytes and appends `;1`. Host paths with a leading slash expand
from the mutable host root; other host paths prepend `host0:`. PFS paths prepend
`pfs0:`; image paths clone directly. Resolution retains the full-path movie
bypass for `cdrom0:/movie/`, device prefixes and the default device byte. An
unknown prefix returns minus one without writing the output. Unsupported
default devices still return their device number and store a null normalized
path, matching the original.

Read and stream requests build the actual zeroed job and enqueue it. Stream
requests only use the configured default when the full 64-bit argument is zero;
a nonzero high lane with a zero low word stores zero. Both active and per-device
list links and the wrapping 16-bit active count are preserved. Enqueue restores
the original interrupt state and only signals when the device list was empty.

Worker initialization creates semaphore `(0,255,0)` and uses the already
recovered general allocation helper at `002a8170` for a 16,384-byte stack.
The thread packet is 48 zeroed bytes with entry, stack, size, GP and priority
fields. Priority is 72. Device 3 selects the movie worker; others use the
generic worker. Negative semaphore/thread/start results retain the original
unchecked behavior. The syscall boundary records packet fields and raw start
arguments/results; it does not execute the created worker.

All 3,328 original-instruction/C comparisons passed, comparing all 327,132
declared RAM bytes, defined results, interrupt state and primitive/syscall
traces. Reviewed outputs include 256 normalized paths, 256 unsupported-device
returns, 384 resolutions, 128 rejected prefixes, 288 read jobs, 288 stream jobs,
192 rejected requests, 128 initialized devices, 128 idle devices and 384 direct
queue appends. The group checks 1,248 complete thread packets, 736 start-thread
calls and 26,224 syscall trace words. Actual string, copy, pool, handle, job,
semaphore and startup code executes; only kernel services and CPU instruction
values have external value models. Output and thread-packet pointers are
adapted to host pointers for C comparison.

DDS has ten complete new body matches and one related resolver. The 12-byte
host-root getter has 29 raw address-return candidates; its actual normalization
caller constrains it to one. Across 29 new/dependency bodies, all 49 call links
agree. Literal prefixes, host-root/device-table spacing and active count/head/
tail/default/priority/stream-limit relationships are independently constrained.
The related DDS resolver swaps S0/S1 roles while retaining ABI save slots and
adds a second movie-prefix test. All 71 retained original words, the removed
unreachable NOP, seven added DDS words and changed branch destinations are
checked. The new literal is `/movie2/`, compared for seven bytes (`/movie2`).
This difference is retained as related evidence, not an exact body match.

Unity retains `sdfFileCmdHandle_t` active/device links, device/command/status and
command-parameter roles. That corroborates the native record interpretation;
no exact HD function identity was promoted for this platform-specific chain.

The generic worker entry is `002be8c8`. Movie worker `002bed50` has a matching
executable prologue and a real startup reference, but is currently only a LAB
label outside the 8,956-entry recognized-function inventory. This is a concrete
discovery gap to resolve when recovering worker execution. Both callback entry
leads have separately checked 80-byte DDS leading patterns and the real wait-
semaphore call; their complete worker identities/source remain unproved.

Next are worker execution and file I/O, then the loader scheduler `00297460`,
pump `002976c0` and their completion callbacks. Startup agreement is not proof
of asynchronous loading, hardware execution or a matching rebuilt executable.
The source, Ghidra project and rolling evidence were updated in place without
creating a checkpoint or backup.

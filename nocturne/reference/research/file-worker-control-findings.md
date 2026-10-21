# File commands, completion and worker priority

Fourteen complete routines are recovered as compiled C, adding 1,324 summed
original body bytes. All 3,840 original-instruction comparisons pass. The working
Ghidra project is saved in place; current exports and reports are overwritten.

| Entry | Recovered routine | Body bytes |
|---|---|---:|
|002be720|ps2FileJobComplete|276|
|002bf490|ps2FileCommandSeek|96|
|002bf4f0|ps2FileCommandSize|88|
|002bf548|ps2FileCommandRead|96|
|002bf5a8|ps2FileCommandWrite|96|
|002bf608|ps2FileCommandRetry|44|
|002bf638|ps2FileCommandClose|80|
|002bf6c8|ps2FileRequestLoad|140|
|002bf758|ps2FileRequestStore|164|
|002bf800|ps2FileWorkerPriority|116|
|002bf878|ps2FileWorkerMoviePriority|32|
|002bf898|ps2FileWorkerDefaultPriority|24|
|002bf8b0|ps2FileWorkerPriorityTick|56|
|002dbd30|ps2KernelChangeThreadPriority|16|

Completion removes the job from both active and device lists, then appends it
to the completed list. Counts wrap at 16 bits. The completed count is tested as
signed after interrupt restoration: at nine or above, the real release routine
frees the completed head and its optional path through the existing pool code.
The next device job is signalled only if its head is nonzero. This preserves the
normal eight-entry completed cache and the original behavior for backed unusual
count metadata; those synthetic states do not imply universally coherent lists.

Seek, size, read, write and close requests require signed job state seven. They
write the command and parameters, signal the device semaphore and return zero.
Other states return minus one with no RAM mutation or signal. Retry requires
state nine, clears the error word and restores state seven without signalling.
Whole-file load/store use the actual resolver, job creation, allocation, queue
append and worker-startup callees. Commands are eight/nine. Store selects the
default stream size only when the entire 64-bit argument is zero; parameter
stores retain the original low 32 bits.

Priority changes compare the sign-extended current word against the full
64-bit argument, then visit exactly four 24-byte device records. Nonnegative
thread IDs receive the real ChangeThreadPriority syscall with the raw priority.
Movie priority is 120 with a three-tick byte countdown; default priority is 72.
Only a countdown transition to zero restores the default.

The comparisons check all 327,132 declared RAM bytes, defined results,
interrupt status and ordered CPU/syscall traces. Reviewed outputs include
512 completion cases with 128 old-head trims, 784 accepted and 752 rejected
command states, 576 constructed requests and 192 rejected prefixes. Ninety-six
requests continue through actual completion and release. These are helper-call
sequences: the worker never performs I/O in those tests. Kernel packet/result
values are the service boundary, and game-function results are not supplied.
The group checks 20,748 syscall trace words.

DDS contains one complete matching instruction span for each new routine.
All 19 connections to new or previously checked dependency bodies agree.
Explicit address relocations retain all other words, registers and branches.
Completion and priority use the same previously identified device table;
all five command semaphore addresses agree with its semaphore field. Active
and completed heads, tails and counts, priority/countdown and stream-default GP
offsets agree with the earlier enqueue/startup/release groups. The earlier
related DDS resolver remains explicitly distinguished from an exact body match.

Unity's `libsdf_H.sdfFileCmdHandle_t` corroborates signed status, command
parameters, error and current-offset roles. Its managed object and field widths
are not the native PS2 layout. No additional HD method identity is promoted.

The movie worker at `002bed50` is now recognized in the working project from
its existing instructions and flow, following its actual startup reference.
It adds 604 reachable body bytes (620-byte span) and raises the recognized
inventory from 8,956 to 8,957. Its current assembly and pseudocode are exported;
it is not yet canonical C. The generic/movie loops, real RPC file services,
scheduler, pump and complete asynchronous loading remain unfinished. Arbitrary
aliases, unbounded malformed lists, real kernel scheduling, PS2 runtime and a
matching executable are not proved by these comparisons.

Source: `src/file_worker_control.c` and `.h`. Current evidence:
`file-worker-control-validation.json`, `file-worker-control-matches.json`,
`file-worker-control-transfer.json`, `file-worker-control-abi.json`, and
`file-worker-discovery.json`.

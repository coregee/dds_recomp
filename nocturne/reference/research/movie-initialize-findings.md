# Complete movie and decoder initialization

Eight complete routines in `src/movie_initialize.c` add 1,084 recognized body
bytes and 768 passing original-instruction/C comparisons. All 223 non-delay
root instruction addresses are reached, including both initialization branches.
The capture executes 275,185 original steps, compares 6,856 ordered trace words
and observes 2,272 memory MMI operations. The saved interfaces pass after
reopening; all eight selected exports are merged into the working inventory.

| PS2 entry | Recovered routine | Body bytes |
| --- | --- | ---: |
| 002c5d28 | ps2MovieControlInitialize | 524 |
| 002c4010 | ps2MovieDecoderClear | 108 |
| 002c4118 | ps2MovieDecoderCreate | 96 |
| 002c4f48 | ps2MovieDecoderInitialize | 56 |
| 002c3be0 | ps2MovieDecoderListAppend | 64 |
| 002c3c20 | ps2MovieDecoderListRemove | 60 |
| 002c3ab0 | ps2MovieDecoderQueueRemove | 140 |
| 002c2288 | ps2MovieStopDecoderCommand | 36 |

## Filename discriminator and control layouts

The original constant at `551b50` is `.ips`, including the leading dot.
Initialization finds the last dot and compares the suffix case-insensitively
through the actual SDK string routines and character-class table. It clears
176 control bytes, sets active byte zero to one, sets remaining bytes at `+18`
to `7fffffff`, and copies the raw coordinate/Z/dimension fields from parameters.
Control byte `+3` records the IPS discriminator. An IPS suffix does not depend
on whether file-device resolution later succeeds.

The ordinary branch allocates a zeroed 20-byte record and a `20000`-byte memory
handle. Record words `+4/+8/+c` all retain the acquired buffer pointer. It submits
an actual file read request with callback `002c5460`, stores the job at control
`+10`, and initializes the decoder with consumer callback `002c5a18`.

The IPS branch creates semaphore `551b48` with initial/max counts one if its
existing signed word is negative, and sets `55216c` to minus one. It allocates a
zeroed 120-byte record and a `24000`-byte memory handle. Record `+50` retains the
buffer; `+54/+60` point at buffer offsets `4000/14000`, forming two 64-KiB ring
regions. Record `+70` is 32 and `+74` points to the inline record bytes at `+20`.
The file callback is `002c5688`, the decoder consumer is `002c5bb8`, and control
bytes `+20/+22` become one/127.

All allocation, pointer acquisition, path normalization, job construction and
enqueue calls execute their existing recovered bodies. Tests use initialized
device records, empty and populated job queues, mixed-case extensions, missing
extensions and recognized/unrecognized device prefixes. No allocator or file-job
return is substituted. Independent checks verify the copied fields, both buffer
layouts, actual retained allocation pointers and callback slots.

## Decoder ownership and interrupt behavior

Decoder initialization clears 140 bytes. Configuration bytes select mode zero
when the first byte is zero, mode one when only the first is nonzero, otherwise
mode two. The next two decoder bytes copy configuration bytes two and three.
The movie wrapper constructs its four-byte configuration from parameter bytes
`+10/+11`, a zero byte, and parameter byte `+12`.

Create sets decoder byte `+c` to one, stores callback/payload at `+5c/+60`, and
calls the real staging allocator for `10100` bytes. Decoder `+54` retains that
pointer plus `100`. The five-argument initialize wrapper stores its fifth
argument's low word at `+34` and appends the decoder to the owned list.

The owned list starts at `552148` and uses decoder link `+8`. Append traverses
to the tail, links the decoder and clears its next word. Remove searches for
the full incoming argument against sign-extended loaded pointers; raw upper
argument bits can therefore prevent a match. Tests retain that distinction.
Empty lists, several lengths, absent entries and removals at each position run.
Configuration aliases inside the cleared decoder also agree with native writes.

The queued list has previous/next words at decoder `+0/+4`, membership byte
`+d`, and head/tail `55215c/552160`. Remove updates neighbors or globals and
clears membership. If the caller says interrupts are already disabled, it
preserves that ownership. Otherwise it disables and restores interrupts only
when required. The native return is the loaded next pointer or the interrupt
enable helper's result, depending on the path; full defined results are checked.
The decoder-stop wrapper submits original command `100` through the actual
command queue and transport dependencies.

## Unity and DDS evidence

The retained Unity `mviManager.moviePlayFile` at `1828156a0` and PS2 launcher
`0022b710` both construct process type `2afb`. The PS2 launcher first calls the
now-recovered control initializer; the HD movie graph instead uses Unity movie
objects and asset loading. This is useful role/graph evidence, without an exact
HD identity promotion for the PS2 decoder and buffer functions.

Three complete DDS spans resolve uniquely: clear `002eb8c0`, create `002eb9c8`
and initialize `002ec818`. Five call constraints agree, including memset,
clear/create, create/initialize and the retained staging allocation/acquire
chain. The control/list bodies have no candidate under the current mask, which
retains GP data displacements. The stop wrapper has two candidates and remains
ambiguous. Static DDS transfer is distinct from DDS execution.

## Shipped assets and next connected work

The extracted `game/MOVIE` directory contains 24 files: 19 IPS and five IPU.
All nineteen IPS files have `IPS0` at header byte eight. The rolling
`movie-asset-headers.json` records their current filesystem lengths and first
64 bytes, without copying the movie payloads. `DDS.IPS` begins with header words
12, 126750720, and `IPS0`; words at `+18/+1c` are 4096/4096. Other shipped IPS
headers include 2048/4096 there. Those two words are consumed by the IPS file
callback as header-block size and packet-block size, respectively; other header
field meanings remain to be confirmed against their consumers.

Ordinary/IPS streaming and decoder shutdown/close are now recovered in the
connected batches linked below. The actual IPS headers provide inputs for
metadata allocation and packet-mask branches. Close waits for state six using
the original empty hook002a8078 and actual external file-completion callbacks;
the hook is not a frame-wait routine. Complete physical decoding remains
unfinished. See [decoder and close findings](movie-decoder-findings.md).

## Verification scope

Source builds with C11, warnings as errors, and links into the shared host DLL.
The worker (384), draw/queue (1,248), file-loader support (1,792), file-device
(3,328) and texture-construction (5,248) affected comparisons pass.
The new capture compares all eighteen declared RAM spans, defined raw 64-bit
results, Status/primitives and ordered kernel/cache events. It checks native
writes against those spans/private stack and keeps the original DDT unchanged.
Host configuration storage only relocates private stack bytes; it does not
change the configuration values or supply a recovered callee's result.

Kernel outcomes and valid initialized allocation/device metadata remain inputs.
The ordinary/IPS pumps, callbacks and ring consumers are now recovered; see
[movie streaming findings](movie-stream-findings.md). Exhaustion, malformed or
unbounded lists, complete asynchronous callback integration, IPS/IPU decoding,
physical IPU/GS/IOP/scheduling, PS2 runtime and a matching executable remain
unfinished. Current aggregate recovery is783/8,960 routines with571,991
comparisons; the last full run remains413/462,684.

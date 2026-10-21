# Movie file cache and worker leads

Four complete PS2 bodies are integrated in `src/movie_file.c` and the current
host build. Their descriptive names are PS2 aliases, not established HD matches.

| Entry | Routine | Recognized bytes | Comparisons | Reached non-delay PCs |
| --- | --- | ---: | ---: | ---: |
| `002bdb80` | `ps2MovieFileOpen` | 80 | 96 | 16/16 |
| `002bdbd0` | `ps2MovieFileRead` | 580 | 96 | 120/120 |
| `002bde18` | `ps2MovieFileClose` | 56 | 96 | 9/9 |
| `002bdea8` | `ps2MovieFileSize` | 48 | 96 | 6/9 |

All 384 original-instruction/C comparisons pass: 764 recognized body bytes,
631,832 original steps, 291,984 ordered trace words and 384 MMI instructions.
The saved Ghidra interfaces pass after reopening; all four current selected
exports decompile and merge into the 8,960-function inventory. Affected
movie-disc (288 cases) and CD-stream/lifecycle (2,250 cases) comparisons pass.
No new full-suite or physical PS2 run is claimed.

## File state and exact copy behavior

Open uses the actual archive lookup and stream seek. A missing record returns
all ones. Success stores the record at `5520f8`, remaining word at `5520fc`,
clears the cached count at `552104` and seeks the original archive sector.
The returned signed size is reloaded from the record after seek.

Read first rejects a nonpositive signed remaining word, then clamps the full
signed 64-bit request to that remaining count. It drains any cached bytes
through the actual memcpy. A 16-byte-aligned destination receives whole sectors
directly; its partial tail comes through the 2 KB scratch buffer at `58f7c0`,
whose unused bytes become the next cache. Unaligned destinations read each
sector into scratch, loading four doublewords before storing each 32-byte
batch. This load/store order matters when source and output overlap.
The remaining count wraps as a word. Exhausting it calls the real movie close
before returning the clamped byte count.

Close returns zero for a null handle. Otherwise it waits on the movie semaphore,
stops the real CD stream, signals the semaphore, clears the handle and returns
the full raw SignalSema value. Size sign-extends record bytes 8–11. Its null
handle branch enters the actual fatal spin; returning size tests do not reach
`002bdeb8`, `002bdebc` or `002bdec4`. Those three addresses are explicit gaps.

## Shipped data comparisons

The harness shares the original `DDS3.DDT` once, verifies its hash, adds only
32 deterministic padding bytes and checks that both original execution and C
leave it unchanged. Original writes must remain inside the thirteen declared
RAM spans or the private stack. The scratch span includes the last byte written
by the deliberately overlapping output at `58f7c1`.

Four 8 KB windows are read once from the shipped `DDS3.IMG`, individually
hash-checked and shared by both executions. These ordinary archive files test
the byte transport used by the movie file layer; they are not movie content.

| Archive path | Starting sector | Original file bytes | Shared test bytes |
| --- | ---: | ---: | ---: |
| `battle/bed/agi01.BED` | 832 | 40,752 | 8,192 |
| `battle/bed/ken.BED` | 893 | 13,488 | 8,192 |
| `battle/bed/nego_kai.BED` | 910 | 14,016 | 8,192 |
| `battle/bed/zan01.BED` | 925 | 8,304 | 8,192 |

The 32,768 shared media bytes arrive as external IOP memory events. Actual
archive, stream, CD/RPC/reply, memory and diagnostic source executes; no game
function result is substituted. Returns, full declared RAM, status, ordered
events and sector cursors agree. Nonoverlapping output is also checked against
independent original-file byte hashes. Eight overlapping read cases compare
the complete scratch/output state against original instruction execution.

Cases include cached-only reads, zero counts, 2,048/2,049/4,096-byte reads,
unaligned outputs, cache prefixes, a positive high-word request that clamps to
3,200 bytes, EOF close, nonpositive remaining values and cached counts larger
than the remaining size. Valid and missing archive paths, a leading slash and
directory records are checked. Direct `cdrom` lookup, the zero-handle fatal
spin, arbitrary malformed requests, physical DMA/scheduling and a matching
PS2 executable remain outside this validation.

## Transfer and Unity reference

`movie-file-transfer.json` finds no full-span DDS match for these four movie
bodies under the current relocation mask. Individually matched memcpy, fatal,
CD stop, wait and signal dependencies remain useful transfer anchors. The
shared signature records the sector-cache/EOF structure; it does not establish
equivalent DDS movie code.

The local HD native corpus retains `mviManager.moviePlayFile` at `1828156a0`.
It searches the movie table by filename, records manager state 1, creates a
delegate, starts a kernel process of type `0x2afb` and retains that process in
the manager's static field at offset `0x50`. Movie indices 10, 23 and 25 have
an extra localization route. This retained process graph is a higher-level
PS2 matching lead.

`mviManager.video_update` at `182817180` gates manager state 3 on Unity
VideoPlayer preparation/playback/first-frame properties, updates its frame
counter and calls field character visibility and sky-filter routines.
`movieStop` at `182816790` restores the normal frame rate and obtains movie
process data through the kernel before release. The port replaces the native
playback path, so these names do not identify PS2 sector/cache routines by
themselves. No movie counterpart is promoted from these leads.

## Next connected source

`src/movie_worker.c` now integrates the complete 604-byte body at `002bed50`,
strict-compiles and passes 384 connected original-instruction observations.
See [movie worker findings](movie-worker-findings.md). Its original table at
`5496a0` has these nine routes:

| Command | Target | Behavior |
| ---: | --- | --- |
| 1 | `002bedb8` | Open, ready state, event 2 |
| 2, 3, 6, 9 | `002befa8` | Actual worker error helper |
| 4 | `002bedf0` | Size callback, event 4 |
| 5 | `002bee28` | Read, wrapped progress, event 5 |
| 7 | `002bee88` | Close and actual job completion, event 7 |
| 8 | `002beed0` | Open, optional allocation/read, close/completion, event 8 |

The original infinite worker clears each command byte and waits again. Its
connected comparison observes three iterations through the fourth real wait
and executes actual completion/error/allocation/callback bodies. Zero or
out-of-range commands, missing jobs, callback-driven close commands and
close/EOF interactions now agree. Direct CD lookup at `002bd838` still needs its live
Open A2 operand resolved: SearchFile leaves record bytes 24–31 there when
debug printing is disabled; debug printf can change it.

Current outputs are `movie-file-validation.json`, `movie-file-abi.json`,
`movie-file-transfer.json`, `movie-file-interfaces.json` and the single rolling
`movie-file/vectors.jsonl` capture. Source and Ghidra changes are saved in place.

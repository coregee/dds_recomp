# Blocking file loading and file-backed script construction

Nine complete PS2 routines are now compiled, tested against original instructions and integrated in the working Ghidra project. **1,860 comparisons pass**, covering every **122 main instruction addresses**, 15,902,621 original steps and 84,660 MMI instructions. All 191 shipped BF files traverse LoadFileEx, LoadFile, AddScript3 and StartScript3. All 191 files additionally traverse six release/shutdown routes, with 764 observed real shutdown callbacks and complete file-handle coalescing. Invalid start indexes exercise twelve actual AddScript3 construction failures. These are connected archive-worker observations, not supplied loader returns.

| PS2 entry | Recovered role | Comparisons |
|---|---|---:|
| 002BE328 | Blocking completion callback | 64 |
| 002BE368 | Blocking open | 64 |
| 002BE450 | Blocking close | 64 |
| 002BE480 | Blocking read | 64 |
| 002BE4A0 | Blocking size query | 64 |
| 002C3660 | sdfDevLoadFileEx | 191 |
| 002C3718 | sdfDevLoadFile | 191 |
| 00109C58 | scrAddScript3 | 585 |
| 00109D48 | scrStartScript3 | 573 |

The callback compares the full 64-bit event value: event 3 stores the result word at 552118, event 4 stores size at 552114, and every event signals the semaphore loaded with signed LW from 551924. Open lazily creates that semaphore with initial count 0 and maximum 128, submits the actual RequestRead with callback 2BE328, waits, calls Retry and returns the original job. Close commands close, waits and releases a terminal job. Read returns the kernel wait result, not the byte count. Size returns the signed callback word after waiting. The original wrappers contain no null-job guard.

LoadFileEx opens, queries size, allocates a memory handle for the 32-bit ADDU sum of size and margin, acquires its data pointer, reads the original size and closes the job. It stores the data output before the size output. If the data output pointer is null, it releases the pointer acquisition and still returns the allocated handle. Tests cover nonzero high argument lanes, padding margins, null outputs and aliased data/size output pointers. LoadFile tails into this body with margin zero.

AddScript3 gives LoadFile a private data-output word, invokes the existing FLW0 constructor and stores the loaded handle at work+D8 only on success. A failed constructor retains the loaded allocation. StartScript3 unconditionally invokes the existing process bridge with the constructor result. Successful startup executes the real pool, message allocation/relocation, diagnostic formatter, list and process constructors. Failure-startup with an invalid work pointer is outside the returning backed cases.

Each blocking kernel wait runs the unchanged archive worker 2BED50 to its next worker wait. The original instruction harness and host harness both preserve the waiting caller context while retaining worker RAM effects. Real callback, command, queue, CD/RPC/response, archive lookup and allocator bodies execute. The external boundaries are kernel values, scheduling observation and exact incoming sectors from DDS3.IMG. Original DDT remains unchanged. Media traces record destination and sector length; full mutable RAM comparison and 433 independent output hashes check copied bytes. The fixtures have disjoint RAM extents and separate RPC response/allocator descriptor storage.

Unity AddScript3 at 1826C74E0 and StartScript3 at 1826C90A0 retain asset-bundle loading followed by AddScript2 and process startup. They provide naming and call-flow anchors; managed allocation, decoding and delegates differ. Both HD sdfDevLoadFile names share 1825E4680, whose retained native body only creates managed objects. That body supplies **no PS2 I/O algorithm**; the loader names come from method metadata and their implementation from PS2 instructions.

Four selected full spans resolve uniquely in DDS: LoadFileEx, LoadFile, AddScript3 and StartScript3. Ten call/callback links and two repeated-global constraints agree. The five blocking frontend bodies have no complete masked DDS candidate under the current rules. These are checked static transfer leads, distinct from DDS execution.

The nine interfaces were saved in place, reopened and checked, and their current exports merged into the inventory, subsequently expanded to 8,973 functions by indirect command discovery. Evidence: `script-file-validation.json`, `script-file-interfaces.json`, `script-file-matches.json`, `script-file-transfer.json`, `script-file-abi.json` and the rolling fixtures/vectors in `script-file/`. Canonical source is `src/script_file.c`.

Physical thread scheduling, generic file devices, arbitrary malformed or exhausted allocation graphs, full shipped VM execution, PS2 runtime and a matching rebuilt executable remain unproved. File-backed construction is now connected to actual shutdown/release. Next execute selected original script procedures through the recovered VM and recover the [shipped command frontier](script-command-frontier.md). The [frontier](script-process-next-frontier.md) tracks that work.

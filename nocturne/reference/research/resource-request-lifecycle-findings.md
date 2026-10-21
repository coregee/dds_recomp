# File-request lifecycle used by model acquisition

Ten complete native bodies are integrated in `src/resource_request_lifecycle.c`:

| PS2 entry | Recovered interface | DDS counterpart |
| --- | --- | --- |
| `00296738` | `ps2ResourceRequestInitialize` | `00288818` |
| `002969F0` | `ps2ResourceReadRequestCreate` | `00288AD0` |
| `002968F8` | `ps2ResourcePacRequestCreate` | `002889D8` |
| `00296648` | `ps2ResourcePacRequestRelease` | `00288728` |
| `002966A8` | `ps2ResourcePacRequestFree` | `00288788` |
| `002966C0` | `ps2ResourceRequestRelease` | `002887A0` |
| `00296B28` | `ps2ResourceWait` | `00288C08` |
| `00296B70` | `ps2ResourcePacWait` | `00288C50` |
| `001DC230` | `ps2ModelRemovePending` | Unresolved |
| `001DCA88` | `ps2ModelBuildPrefixedPath` | `00217038` |

The queue initializer stores the kind byte, actual cloned filename, callback
and parameter at request `+0/+8/+18/+1C`. It retains the incoming phase and next
link. Under the semaphore at manager `00575618`, it appends through the old
tail or installs a new head, then stores the tail and signals. Only an empty
queue kicks the real phase processor, after restoring the initializer frame.
Plain construction clears `30` bytes and stores the high-allocation byte at
`+3`; PAC construction clears `70` bytes, initializes its parser at `+30`,
and optionally sets the parser flag two. Real file jobs are submitted on the
empty-queue path.

Cleanup returns one while the phase byte differs from six. Terminal cleanup
optionally releases an attached terminal file job, releases PAC record nodes
when appropriate, and frees the actual path and request allocations. It does
not free the loaded payload handle at request `+20`. The generic releaser
delegates kind one to PAC cleanup; its wrapper restores the frame before the
tail call. Owned terminal requests are unlinked by the real queue helper in
the test setup. Both present and absent terminal jobs are exercised.

Waiting polls the real readiness predicate, sets the file worker's default
priority `48`, pumps the real resource manager and repeats. Selected PAC wait
cases begin with phase six but without the parser-end flag, then become ready
through actual terminal PAC decoding and active-list unlinking. No fabricated
readiness return or timeout replaces the loop. Nonreturning/asynchronous
production conditions remain outside this finite test domain.

Model pending removal compares the sign-extended node ID with the full incoming
minor register and removes only the first match. Actual allocated duplicate
nodes cover empty, head, interior, unmatched and dirty-upper-register cases.
The path helper copies all eight original prefix bytes, concatenates through
the recovered SDK routine, and retains the raw destination return.

## References and transfer

[Three pinned community files and Unity request types](resource-request-lifecycle-matches.json)
provide context. The community
[file-request API](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/file_request_api.h)
separates plain/PAC constructors, readiness and waiting. The
[asset-request API](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/mdl_asset_request.h)
documents queued, already-pending and ready results. The
[model manager](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/model/mdlManager.c)
connects prefixed paths, pending IDs and completion jobs. These guide the
next model-specific integration; the full acquisition facade is still pending.
Unity's retained request fields support type roles, not a named equivalent
implementation for the selected native routines.

[Nine complete DDS instruction spans](resource-request-lifecycle-transfer.json)
resolve with thirty agreeing call constraints. Three identical 44-byte
prefix wrappers initially matched. Original eight-byte data independently
selects `/model/` at Nocturne `0054F628` and DDS `003BBB60`; the other two DDS
candidates copy `/sound/` and `/voice/`. Pending removal remains unmatched.
No DDS execution or complete model-acquisition equivalence is claimed.

## Validation and next work

[640 original-instruction comparisons](resource-request-lifecycle-validation.json)
pass, reaching all **181 main addresses** over **280,208 original steps**.
The complete declared RAM, defined returns, Status, allocator primitives and
ordered kernel/cache/SDK observations agree. Tests cover empty/nonempty
enqueueing, both constructor families and flags, returning/nonterminal cleanup,
owned terminal jobs, actual PAC wait progress, allocated pending duplicates
and original prefix data. Constructor returns and fields bind subsequent calls
using each execution's own values. Original memset supplies caller phase and
job-field initialization; captured returns are comparison evidence only.
No uninitialized reads or undeclared writes are reported.

All ten interfaces are saved in Ghidra and independently reopened; exports
are merged. [5,568 affected regression cases](resource-request-lifecycle-regressions.json)
pass on the same rebuilt host for loader flow/support, file allocation/release
and model resource ownership. Recognized credit is **912 bytes**; full compared
spans total **924 bytes**. No new full-suite run is claimed.

Recovery is **1,957 /8,986 functions (21.778%)**, **328,499 focused cases**,
**791,183 aggregate cases**, and **148 reports**. The bootstrap audit now also
decodes four installed model completion callbacks from the original instruction
pairs: `001DC968`, `001DC9B8`, `001DCA30` and `001DE1A0`. Adding their descendants
expands the earlier direct-only pending count from 40 bodies /5,192 bytes to
**48 bodies /5,932 bytes**, with zero missing exports. This reveals work and
adds no compiled function credit.

Continue those real completion handlers and their registration/parsing paths,
then acquisition `001DCAB8`, blocking wrapper `001DCCE8`, outer construction
`001DD0D0` and remaining model/PCP factories. Whole asynchronous/retail loading,
physical IOP/filesystem/scheduling, exhaustion, arbitrary aliases and a matching
executable remain unproved. Rolling outputs are saved without checkpoints.

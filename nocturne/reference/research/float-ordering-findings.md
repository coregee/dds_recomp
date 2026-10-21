# Original float-key ordering and packet collection

Verified against `SLUS_209.11` instructions on 2026-10-14. Nine new C bodies
recover the installed model-surface submission/collection callbacks and their
complete float-key insertion, rotations and traversal dependencies. The existing
ordering flush executes the real newly supported callback.

The [proof](float-ordering-validation.json) passes 3,072 comparisons across ten
roots, all 263 measured main instruction addresses, complete declared ordinary
RAM, defined raw returns, Status and FCSR condition. There are 9,503 real prefix
submissions, 18,484 original COP1 comparisons, 149 installed callback/record
observations and 704 independently checked surface endpoints.384 insert/submit
cases continue into the actual collector;768 incidental void-call returns are
excluded from ABI-value comparisons rather than treated as defined results.

| Nocturne entry | Recovered role | Recognized bytes | Full contiguous bytes | DDS entry |
| --- | --- | ---: | ---: | --- |
| `002c7cb0` | Positive-side single/double rotation | 116 | 124 | `002ef858` |
| `002c7d30` | Negative-side single/double rotation | 116 | 124 | `002ef8d8` |
| `002c7db0` | Rebalance insertion and repair ancestor/root link | 252 | 252 | `002ef958` |
| `002c7eb0` | Insert/group raw float key | 212 | 216 | `002efa58` |
| `002c7f88` | Submit sorted or sentinel chain | 76 | 84 | `002efb30` |
| `002c7fe0` | Collect chain group using actual state links | 112 | 112 | `002efb88` |
| `002c8050` | Traverse first child, group, second child | 108 | 108 | `002efbf8` |
| `002c80c0` | Build surface first/last chains | 100 | 100 | `002efc68` |
| `002c8128` | Full64 mode dispatch | 84 | 92 | `002efcd0` |

The total is 1,176 recognized body bytes and 1,212 contiguous instruction bytes.
Every word of the larger spans is checked; gaps in recognized function-body
membership do not justify omitting original instructions from transfer evidence.

Surface offsets are 0 next,4 first,8 last,12 unsorted head,16 submit callback,
20 mode callback and24 tree root. A tree node is 16 bytes: first child, second
child, chain head and signed balance. A chain's word 4 determines whether submit
accepts it, and word 12 is the raw float key. Literal `0000ffff` prepends to the
unsorted queue. Other keys use native COP1 equality/less comparisons; equal keys
prepend to their group, and first-child traversal produces descending key order.
The independent finite-key checks specify descending groups, newest-first ties
and newest-first sentinel records without simulating tree insertion.

Original wrapping balance writes and single/double-rotation assignments are
retained, including the zero middle-balance branch. They are not replaced by a
standard AVL library. Single rotations return the incoming raw 64-bit child value;
double rotations return the sign-extended loaded midpoint. Mode comparisons use
the complete 64-bit argument: zero builds, one forces unsorted submission, other
values do nothing. Dirty upper lanes are therefore significant.

Collection executes the actual state-aware DMA tag linker and work-buffer
allocator, including inherited state, new reference packets and terminating
tails. The initializer's original callback words are used, with no replaced
targets or supplied game-return values. Logical ancestor/local-slot data runs
through the private guest-stack transport; callee-save bytes and absolute stack
addresses under the older collector caller are excluded. Finite backed inputs
do not establish over 32-depth/cyclic/malformed inputs, hardware DMA, rendered
appearance, concurrency or complete model drawing/update.

[DDS transfer](float-ordering-transfer.json) checks nine complete contiguous
spans plus four complete allocator/link/reference dependencies. All nonrelocated
words match. Direct/tail targets are constrained by complete callee spans, and
the allocator cursor is independently decoded using both REGINFO GP values.
The original initializer's callback pointers corroborate the two dispatch roots.
This is static transfer evidence, not DDS execution.

[Community review](float-ordering-matches.json) attributes names to the pinned
[DDS symbol file](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/config/dds1/symbol_addrs.txt).
Its 20-byte `SdfListNode` indexed/integer-key/next/prev/value layout is rejected for
these 16-byte nodes. “Release”, “free list” and “pool chain” labels identify DDS
counterparts but do not prove that these native callbacks free memory: the
matched instructions enqueue, sort and collect draw chains. Shared return-only
HD `sdfModelLinkOt` is rejected as a complete ordering implementation. No original
Nocturne symbol spelling is claimed.

The working Ghidra interfaces pass after saving and reopening, and nine current
exports merge. [Affected regressions](float-ordering-regressions.json) record
current-DLL checks for message frames, model draw prerequisites and legacy
heap/deferred/render/ordering consumers. The legacy check verifies the complete
retained gzip stream certificate while comparing only its affected subsets.
No checkpoint, backup, savestate or new full-suite capture is made.

The affected total is 20,096: message frames 2,432, model draw prerequisites 3,328,
legacy heap 5,888, deferred 4,352, packet/state links 2,560 and ordering 1,536. The
unchanged scalar runtime getter uses a different profile and is explicitly
excluded from the legacy heap selection. All 462,684 retained rows were decoded
and the stream certificate verified; this is not a new full-suite comparison.
Current recovery is 2,201/9,059 (24.296%), 310,032 integrated body bytes, 359,671
focused /822,355 aggregate comparisons across 163 focused reports.

Next recover model-node/material packet consumers and both complete placement
branches, then context anchors/children and connected spawn-once update. These
sorting/collection results close an indirect callback dependency rather than
establishing the full renderer or entire executable.

# Complete outer model placement

`002B1DB8` is recovered as `ps2ModelPlaceMeshes(surfaces, root)`. The complete
1,152-byte span contains 1,148 recognized code bytes and one unowned zero word
at `002B2124`. That word lies after an unconditional branch and its delay slot;
it is excluded from recovery credit. Function ranges were not changed.

Published after final regressions and authoritative progress audit.

The routine clears root flag `0x10`, optionally runs the real reference-mesh
placement under flag `4`, then always updates materials for the signed frame
byte at `00551842`. It reads the root's signed node count and per-frame command
list. Null lists, node flag mask `0x11`, and rejected bounding boxes skip a node.
The composed matrix supplies draw depth; node flag `2` selects a colour override.
The root mask intersects each node's mask.

Four private slots hold draw chains. A zero command selector chooses a bucket
from the colour's sign; other selectors use the complete byte without a nibble
mask. The original has no bucket validation. Each new chain receives the cached
depth and a real matrix reference/state packet. Header loads and stores retain
original order, including the private header load before the range store.

Command kind `1` appends an inline call tag; kind `2` runs the actual weighted
packet-list builder. Root flag `8` skips these two paths. Kind `3` always runs
the recovered complete renderer, passing that flag as the reverse argument.
Each populated bucket invokes the function pointer at `surface+0x10` with the
actual surface and chain, then clears its private slot. A completed outer
submission sets root flag `0x10`. A nested reference pass can set it independently.

The [fresh instruction comparison](model-placement-outer-validation.json)
passes 201 cases and all 242 measured main addresses. Cases execute 504 real
surface submissions, 18 nested reference placements, 272 renderers, 116 weighted
packet-list builders, and 178 original 177-pair VU producer batches. Eight cases
let the allocator overwrite the current node's composed matrix after depth
was cached. One backed selector9 case aliases the private first-state word; the original reads it before storing the newly allocated chain there. The existing pre-fix variant fails this case at the resulting chain state, while corrected C passes. This does not prove retail selector9 use. Full declared ordinary RAM, vector/ACC/overflow/Q/clip history,
FCSR/Status, 6,432 selected CPU upper words, 3,216 meaningful private words and
actual callback arguments compare. The original register-save checks also pass.

The host bridge admits the actual ordering, append and prepend callbacks at
`002C7F88`, `002ACD40` and `002ACCE0`; it supplies no game-function outputs.
Other callbacks, including three-argument mode dispatch at `002ACD98`, are not
claimed by this two-argument profile. Root and nested renderer ABI checks,
original byte hashes, stopped-VU/MMIO execution and exported annotations remain
separate evidence. Controller gameplay and physical rendering were not invoked.

The [independent leads](model-placement-outer-leads.json) distinguish the related
DDS counterpart at `002D9238`. DDS adds special material paths for flags `0x20`
and `0x40`, a command-selector high-nibble LOD comparison, a low-nibble bucket
mask, and different conditional prefetch. Nocturne has none of those additions.
This counterpart is not a relocation-only equivalent; transfer the shared
structure while retaining those differences. Unity names and community model
formats provide context, without establishing an exact HD implementation.

The [regression report](model-placement-outer-regressions.json) records affected
retained captures, a fresh 160-case renderer recapture, and the final broad
413-function /462,684-case comparison. Pipeline timing, concurrent EE/VU
execution, cache coherence, GIF/GS hardware execution, malformed bucket/count
domains and the retail reachability of a whole packet/private-frame overlap
remain unproved. No checkpoint, backup, project copy or full recapture was made.

Continue the outer context/update path at `001DD2C8` and its remaining model/part
callbacks. The full executable recovery goal remains unfinished.

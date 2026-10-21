# Original PAC ingestion, acquisition and outer model construction

Fourteen complete original functions are integrated: **2,408 new bytes** and
448 passing instruction/C comparisons. All 459 tracked main addresses execute.
There are no uninitialized reads or writes outside declared RAM. Another
4,448 affected cases pass on the same built host DLL. Fourteen interfaces were
saved and reopened in the working Ghidra project and their exports merged.

Current recovery is **1,988 /8,986 functions (22.123%)**, with 293,476 recognized
integrated bytes, 329,523 focused comparisons and 792,207 aggregate cases across
150 focused reports. Earlier captures remain part of those aggregates; this
milestone does not claim a new full-suite capture or physical game execution.

## Complete bodies

| Entry | Recovered role |
|---|---|
| `001DDD18` | Recognize a type-one `PIB0` PAC record |
| `001DEA58`, `001DEB80`, `001DEB88` | Read signed PIB version and unsigned effect/motion counts |
| `002C6440` | Unlink/free a PAC record and return its old next pointer |
| `001DDD48`, `001DDF00` | Legacy whole-chain and modern counted PAC registration |
| `001DE170`, `001DE1A0` | Release a completion job/request and finish a loaded PAC |
| `001DC8B8` | Pump pending loading until the registered resource can be found |
| `001DCAB8`, `001DCCE8` | Acquire a resource and its blocking wrapper |
| `001DD0D0`, `001DD538` | Construct the outer model context and initialize default motion |

Legacy registration consumes the whole record chain. PIB records supply
header/handle ownership and allocate the typed resource list. P2A and D3P
records create owned copies before releasing their payload handles. Type-nine
records replace the texture-list field; the first nonzero model and motion
handles are retained. Extra and unknown records are discarded without adding
validation or payload cleanup that the original does not perform.

Modern registration requires a first type-one `PIB0` record with a positive
**signed** version word. It consumes that record, the declared effect count,
an optional type-nine texture list, the model record, then the declared motion
count. Motion headers immediately before the payload supply resource slot,
context slot and signed cut. P2A/D3P payloads are copied and freed; IPU data and
its handle are retained. Unknown effect tags are consumed without releasing
their payload handles. The return is the first unconsumed record. The original
caller supplies valid ordering; no bounds/order checks are invented.

The IPU branch establishes that the fourth movie-appender argument carries
source size: explicit record `+1C`, or `size14 + (flag11 & F0) - 10` when zero.
This clarifies the existing appender's descriptive `callback` parameter name;
no callable pointer is interpreted there by these native callers.

Completion registers the resources before removing their pending ID under
the semaphore. With a nonzero notification, it invokes the original target
and then frees the job/request. With zero notification, it leaves that cleanup
to the request path. The real resource pump now dispatches these model
completion functions, including the earlier raw texture/model/motion callbacks.

Acquisition returns an existing resource immediately, reports an already
pending nonblocking request as `-1`, or starts loading using the original
selection/path tables. Filename handling calls original **Strrchr and
Strcasecmp**, with the original 384-byte character-class backing. The literal
is `.PB`, but `.pb`, `.PB` and a final suffix in `model.part.pb` all select
the packed route. Raw files queue the texture, model and optional motion
callbacks with their original loading-work flags.

Outer construction links a real `38`-byte context, clones its texture list,
builds the full model root/command lists, copies group scale/distance, creates
enabled resource-slot motions and initializes nonnegative secondary cuts.
Default PIB generation follows. Four context motion references and eight
resource slots remain distinct.

## Reference evidence and SMT transfer

Two Unity bodies are reviewed: `mdlManager.mdlLoad` (`182805D90`) and
`model_H.pibHeaderChunk_t.pCopy` (`182817970`). The latter corroborates version,
chunk, effect and motion fields, while the original signed load decides the
native version test. Unity's managed byte loading, guards and object lifetime
do not supply the original asynchronous filesystem behavior.

The inspected community revision is
[`bec33411543cdc487bad9debdf758f0090a2242c`](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c).
`src/dds1/model/mdlManager.c`, `include/mdl_asset_request.h`, `include/mdl.h`
and `include/mdl_resource_entries.h` provide attributed request, completion,
payload, resource ownership and construction context. Community C was not
copied into the recovered implementation. The packed-path notification at
Nocturne `002A8078` is independently checked as `JR RA/NOP`; the community
semaphore-related alias is rejected for this executable. Source revisions,
URLs and hashes are in [the reference review](model-pac-loading-matches.json).

Twelve complete spans have selected DDS counterparts, constrained by 45
call/callback links. Acquisition and PAC completion remain unmatched. The
uncredited synchronous request dependency also has a complete DDS span lead,
which supplies no runtime/recovery credit. See
[the transfer report](model-pac-loading-transfer.json).

## Validation scope and next work

The cases execute 7,454 original allocation/copy/initializer preludes. PAC nodes
are constructed by the real parser appender, and payload handles/arrays come
from actual allocators. Each execution binds its own returned pointers into
the following calls. Expected factory arguments derive from independently
checked allocation returns and original dispatch tables; no expected game
return is supplied to the program.

The runs include 112 actual billboard factories and 48 D3P constructors,
modern IPU retention with explicit/derived sizes, legacy duplicate first-handle
selection and unknown records. Real pump completion removes pending IDs in
returning wait/acquisition cases. Outer construction uses four-node model data,
both initially empty and already linked context heads, two enabled motion
slots and eleven connected creation-to-cleanup sequences. Its controllers have
empty track arrays; full retail motion playback remains separate work.

All 624 original command-frame operands agree with independent input transport.
The shared capture tool now keeps command and texture-image observations in
separate arrays; their previous common array mixed the two when both observer
options were enabled. The new notification observer reads the original call
target and delay-slot argument without intercepting the game function.
There are 384 agreeing completion/notification trace words.

[Affected regressions](model-pac-loading-regressions.json) cover loading completion
(576), draw commands (864), loader flow (480), request lifecycle (640), bootstrap
resources (864) and outer model effects (1,024), using their retained original
captures and the current DLL. No checkpoints or duplicate captures were made.

`001DE220` has complete compiled source and its nonblocking dependency path
executes, but **it is not counted as recovered here**. Its synchronous path
needs an original external-worker arrival fixture. Fresh blocking acquisition
and complete unchanged retail MD/MT loading/construction remain unproved.
The inspected bootstrap now has **17 pending bodies /1,372 bytes**, no missing
exports. Continue the synchronous request/worker boundary and remaining
model/PCP factories, then complete retail loading and construction. Physical
IO/DMA/scheduling/rendering, a matching executable and the full executable
goal remain incomplete. Keep working outputs in place.

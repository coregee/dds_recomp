# Original model loading completion and ownership

Seventeen complete original bodies are integrated: 2,152 new recognized bytes.
The focused comparison has 576 passing cases, including 32 retests of the
already recovered `mdlFreeBlur`; it adds seventeen functions, not eighteen.
All 436 tracked main instruction addresses in the new functions execute, with
no uninitialized reads or writes outside declared RAM. Another 7,136 affected
cases pass on the same built host DLL. Eighteen interfaces were saved and
reopened in the working Ghidra project; seventeen new exports were merged.

Current recovery is **1,974 /8,986 functions (21.968%)**, with 291,068 recognized
integrated bytes, 329,075 focused cases and 791,759 aggregate cases across 149
focused reports. These aggregates include earlier captures; this milestone
does not claim a new full-program run or physical PS2 execution.

## Bodies recovered

| Original entry | Recovered role |
|---|---|
| `001DC290` | Allocate and register a group resource, replacing the existing ID |
| `001DC3A8`, `001DC4C0` | Destroy a registered resource and remove by group/ID |
| `001DC5C8`, `001DC600`, `001DC650` | Release a context motion, first matching motion ID, and owner slot |
| `001DC748`, `001DC808` | Configure an owner slot and register loaded fields |
| `001DC910` | Register completed work, remove its pending ID under the semaphore, and release it |
| `001DC968` | Read a texture book, release its backing handle and request |
| `001DC9B8`, `001DCA30` | Relocate model/motion books, retain their backing handles, and complete registration |
| `001DCD00`, `001DD220` | Unlink and destroy an outer model context |
| `002C3798` | Build a texture pointer array through actual TMX copies |
| `002C3888`, `002C3928` | Relocate model/motion payloads at book `+20` |

The native group is `B4` bytes with eight sixteen-byte resource slots. Its
constructor clears each slot's flags, motion pointer and handle while leaving
the two halfwords untouched. Group destruction unlinks the resource, captures
its ownership byte, then clears that byte before repeatedly destroying the
live context head. Consequently, the final context unlink cannot recursively
destroy that same group. Owned texture lists and the primary resource handle
follow deferred release; slot handles are freed immediately. The extra typed
list and its backing handle are released regardless of the captured flag.

The context allocation is `38` bytes, with four motion-reference slots at
`20..2F`, blur ownership at `30` and distance at `34`. The group has eight
resource slots; their configured motion index selects a context slot. The
release code uses the controller's signed halfword index without adding a
bounds check. It clears a reference only when the loaded pointer equals the
full incoming motion argument, then runs actual controller cleanup. A search
releases only the first matching signed motion ID. Context and root motion
heads are reloaded after each destruction.

Texture completion copies TMX resources before freeing the loaded book's
handle. Model and motion completion relocate their payloads and retain those
handles in the loading work. Model completion waits for the separate motion
callback when byte `+6` is set; motion completion always executes registration.
Pending removal and work release happen only after registration.

## Independent reference research

Four files from [Megami-Decomps DDS research](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c)
were inspected at revision `bec33411543cdc487bad9debdf758f0090a2242c`:
`src/dds1/model/mdlManager.c`, `include/mdl.h`, `include/mdl_object_stream.h`
and `include/mdl_asset_request.h`. Its group ownership, first-match motion
release, loading payload, four context slots and live-head destruction provide
independent context for the original instructions. No community C was copied
into the recovered implementation.

The named Unity bodies `mdlUnRegistResrc` (`182808B30`), `mdlUnlinkResrc`
(`182808D00`) and `mdlFree` (`1828048A0`), plus the loading/resource types,
were reviewed. Managed layouts, null guards and Unity-specific release behavior
remain distinct. The new functions keep descriptive native aliases rather
than claiming identical HD implementations. Source links, revisions and hashes
are in [the reference review](model-loading-completion-matches.json).

Thirteen new complete original function spans match DDS through explicit
address/call relocations. The existing blur counterpart also agrees; the whole
comparison records 29 call constraints. Group creation/destruction/completion
and the ambiguous remove wrapper have no selected complete counterparts.
Shared source terminology does not resolve those differences. See
[the transfer report](model-loading-completion-transfer.json).

## Validation and remaining work

The inputs use real pool, root, controller, pointer-array, typed-list and memory
handle allocations. Original copy, memset and motion-node initializer bodies
assemble caller state using each execution's own returned pointers. There are
5,998 executed preludes; no expected game return supplies an allocation or
predicate. The controller lists are nonempty but their track arrays are empty.
The context effect loop includes an owned unknown-kind record, whose native
cleanup releases its node. Existing nonempty track/effect behavior remains
covered by the affected regression reports.

Thirty-two texture-book executions contain an unchanged first TMX record from
the original `moon.LB`: sixteen direct book reads and sixteen completion
callbacks. They execute 64 palette/image uploads. The incoming private stack
words are explicitly declared zero before execution, and the 64 observed
original image operands independently agree with the supplied words. The
synthetic book wrapper is not presented as an unchanged retail model book.
Model/motion tests use bounded, complete compressed relocation streams.

The rolling capture and [focused report](model-loading-completion-validation.json)
compare full declared RAM, defined returns, Status, processor primitives,
defined COP1/VU/ACC/Q values and existing callback/kernel observations.
[Affected regressions](model-loading-completion-regressions.json) cover bootstrap
resources (864), request lifecycle (640), outer model effects (1,024) and
model cleanup (4,608). There was no new full-suite capture or checkpoint.

The audited bootstrap now has **31 pending bodies /3,780 bytes**, with no
missing exports at its inspected boundaries. Continue the PAC completion
callback `001DE1A0` and parser/registration `001DDF00`, then acquisition
`001DCAB8`, blocking wrapper `001DCCE8` and outer construction `001DD0D0`.
Connected unchanged retail MD/MT construction, the remaining model/PCP
factories, physical scheduling/rendering and a matching executable remain
incomplete. The full executable goal stays active.

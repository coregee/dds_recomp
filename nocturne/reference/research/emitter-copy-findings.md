# Original emitter copying, resets and camera-facing initialization

Twenty-eight complete PS2 bodies /3,748 recognized bytes are integrated in
[emitter_copy.c](../src/emitter_copy.c): thirteen copy constructors, twelve
state resets, one camera-facing slot initializer and two copy dispatchers.
The existing generic-effect and model wrappers are retested without new
function credit. All 4,224 original-instruction comparisons pass; all 30 saved
interfaces reopen correctly and all 30 exports merge into the working inventory.

The [validation](emitter-copy-validation.json) checks declared RAM, defined
returns, Status, callee saves, COP1 comparisons and defined VU/ACC/Q values.
It executes 3,905,912 original steps and 309,720 vector instructions, including
768 actual emitter-copy callbacks, 256 generic-copy callbacks, 1,634 billboard
factory callbacks, 802 colour callbacks and 1,102 independently input-derived
RNG advances. All 758 reachable main addresses execute. Forty other addresses
have original-instruction proofs: 39 follow an unavoidable BREAK7 on the
nonzero-axis path; one requires an impossible unsigned-halfword kind value.
Sixty-two arithmetic-trap cases retain their actual RAM and vector effects.
Another 31,696 affected initializer, polygon, Magatuhi, billboard, motion,
retail and cleanup cases pass on the same DLL in
[the regression record](emitter-copy-regressions.json). A retail report's
dependency hash was refreshed after the controller comparison completed;
the final record checks current report, source, verifier and vector hashes.

## Research incorporated

[The reference review](emitter-copy-matches.json) retains 30 inspected Unity
roles and four community source files at revision
`bec33411543cdc487bad9debdf758f0090a2242c`.
[DDS particle-manager research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/parManager.c)
supplies independently checked common-header vocabulary: count at `0x20`,
billboard clone marker at `0x28`, drawing kind at `0x30`, scale/phase jitter at
`0x94/0x98`, billboard at `0xF4`, buffer at `0xF8` and dispatch index at `0x140`.
Its three-operation, twelve-byte dispatch-row
definition agrees with the original Nocturne copier's index arithmetic.
[Drawing-kind definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/par_kind_api.h)
and [track-list definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff_track_poly_list.h)
inform the real resource/reset dependencies. Family-specific tails remain
distinct; the community radial updater is not substituted for this native
camera-facing initializer. Unity names clarify family roles; original
instructions establish unchecked copying, widths, ordering and traps.

## Native behavior and private inputs

Each constructor allocates its original class, clears the declared object,
copies the prefix using the length at source+`0xA0`, then copies its family tail
to destination+`0x150`.
Shared initialization and actual kind resets run. Family11 allocates count*16
extra bytes before shared initialization. Family12 allocates count*12 plus
kind-width*count*16 after it; only kinds1..4 use the original width halfword.
Family9 forces count1 and time0 and does not run an age reset. Both real
dispatchers read the unchanged thirteen-row constructor table at00317270.
The expanded copier additionally clones/scales/configures the billboard for
marker-1. Generic/model wrappers exercise both original major0 and major1.

Camera-facing initialization executes actual LookAt, rigid inverse, cosine,
sine, vector transformation, per-effect RNG and drawing-kind reset. The
nonzero-axis branch starts with S1=0 and cannot return past its original
division trap. Ordinary zero-period traps also remain. Unsigned periods and
remainders exercise both native float-conversion paths.

The common initializer's twenty unassigned frame bytes are declared before
execution at independently reviewed caller depths. The preceding extra
allocator in family11 overwrites these bytes; its saved handle, rounded size
and return address are reproduced from actual C allocation state and original
stack stores. Child model-track padding derives from the preceding allocator's
S0 spill. No captured game output supplies private bytes or dependency results.

## Shared SMT evidence and remaining work

[The complete-span comparison](emitter-copy-transfer.json) resolves 27 of the
28 new bodies in DDS. Eight independently unique constructor spans establish
the corresponding thirteen-row table at0034E250. Same-index original pointers
select only already valid complete-span candidates; their original JALs then
identify otherwise identical reset bodies. Both dispatcher spans separately
check their complete instruction sequences, table-address construction and
four already matched callees. The camera-facing initializer has no accepted
complete-span counterpart. Static correspondence does not establish DDS
execution or a matching executable.

The [updated motion-effect frontier](model-motion-effect-frontier.json) has
17 pending recognized descendants /2,872 bytes, with zero missing exports at
the inspected boundaries. Continue the four special polygon constructors,
their actual resets and generic major2 copier, then outer creation/unlink/free
and motion change001DD440. Retail asset and caller-frame associations,
nonempty drawing-kind4 for the extra-allocation family, malformed/exhausted
states, complete hardware flags/timing, physical rendering/scheduling and
whole-program recovery remain unproved. Work remains in place with rolling
captures and no routine checkpoints.

[The next source review](special-polygon-copy-leads.json) inspects all four
original special constructor/reset pairs alongside community polygon-manager
source and the Unity family roles. It establishes an important width distinction:
the old family's allocator loads a word at `+0x10`, while its reset loads a
halfword there. Community structure terminology does not justify truncating
the allocation input. Three other constructors own handles and copy matrix
state through real VU instructions. The sphere reset has a division trap after
an age store. These are recovery leads with no new function credit.

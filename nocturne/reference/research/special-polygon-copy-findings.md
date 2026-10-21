# Original special polygon constructors, resets and copying

Nine complete PS2 bodies /1,512 recognized bytes are integrated in
[special_polygon_copy.c](../src/special_polygon_copy.c). Four constructors,
four resets and the actual table dispatcher pass 2,816 original-instruction
comparisons. The existing generic-effect and model wrappers are also retested
through major kind 2 without new function credit. All 358 selected main
addresses execute, and all eleven saved interfaces reopen and export correctly.

The [comparison report](special-polygon-copy-validation.json) checks declared
RAM, defined returns, Status, callee saves, COP1 and defined VU/ACC/Q values.
It executes 2,344,329 original steps and 10,672 vector instructions, including
1,792 actual constructions and colour callbacks, 768 special-copy callbacks,
512 generic callbacks and 18 arithmetic traps. The
[affected regression record](special-polygon-copy-regressions.json) checks
another 15,488 current-build cases across common emitters, shared polygon
owners, Magatuhi, billboard ownership and the other generic-copy kinds.
This is not a new full-suite run or physical runtime verification.

## Community and Unity evidence

[The source review](special-polygon-copy-matches.json) incorporates pinned
[DDS polygon-manager research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/polyManager.c)
and [cell definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/par_cell_api.h).
The revision is `bec33411543cdc487bad9debdf758f0090a2242c`; source URLs and
hashes remain with the review. Community count/cell/age/ownership terminology
is corroborated by original consumers and complete DDS spans. It guides
fixtures without supplying replacement game results.

Four Unity constructor families and three named reset methods corroborate the
original table and constructor/reset edges. The old ring's native whole reset
keeps a descriptive name: HD creation loops over a per-entry `BuffInit`, which
does not establish a direct whole-reset counterpart. The named HD copy method
corroborates the dispatcher. Managed guards and allocation layouts remain
distinct from original PS2 behavior.

## Behavior preserved

| Family | Original ownership and reset behavior |
|---|---|
| Old ring | Pool allocation `0xF0 + low32(count*4)`; clears only `0xF0`; appends four-byte ages; resets colour/state in twenty-byte cells |
| Ring | Handle-backed `0x100 + low32(count*8)`; clears requested buffer; eight-byte age records |
| Roll ring | Handle-backed `0xF0 + low32(count*8)`; clears requested buffer; eight-byte age records |
| Sphere ring | Handle-backed `0x100 + low32(count*20)`; clears requested buffer; twenty-byte age records with unsigned group modulus |

All families copy the prefix using the word at source+`0x18`, then copy the
family tail to destination+`0xC0`. They create actual cell/material owners and
invoke the unchanged colour table. The last three preserve matrix state using
the original VU loads/stores and set the actual cell mode. The copier reads
the original four-row table at `00317670`, preserves the dispatch halfword at
`0xB0`, and writes active `1` at `0xB2`.

The old allocator reads a full word at `0x10`; its reset reads a halfword there.
Standalone reset cases vary the upper half independently. Allocation inputs
remain bounded; this is not a test of huge allocations. The original age is
`FF000001`; subtraction and unsigned group handling retain their ordering.
Sphere zero-modulus traps preserve the earlier age store. The colour callback
operands and both original tables are checked independently of captured game
outputs. Zero-count cases also exercise wrapped width inputs.

The comparison corrected an initial cell-stride transcription: native
`(4*i + i) * 4` advances twenty bytes. The rolling capture's initial generic
caption mentioned twelve; the original instructions and unchanged captured
bytes establish twenty, as retained in the final C, report and saved comments.

## Shared SMT evidence and next work

[The transfer report](special-polygon-copy-transfer.json) resolves complete
spans for all nine new bodies. Four independently unique constructor matches
anchor the original DDS table at `0034E650`. The full 88-byte copier at
DDS `0015F520` differs only in its two explicitly verified table-address
immediates. All four resets match complete original spans. The existing
generic/model wrappers remain unresolved or ambiguous in this selected static
search; they add no transfer credit. DDS execution and a matching executable
remain unproved.

The [motion-effect frontier](model-motion-effect-frontier.json) now has eight
pending recognized bodies /1,360 bytes and zero missing exports at inspected
boundaries. Continue real PIB record dispatch, copied model attachment,
creation/unlink/free and outer motion change `001DD440`. Relevant community
model-effect definitions and original asset associations should inform the next
fixtures. Private caller contexts, malformed/exhausted states, outer scheduling,
physical rendering and whole-program recovery remain outstanding. Source and
project changes stay in place with rolling captures and no checkpoints.

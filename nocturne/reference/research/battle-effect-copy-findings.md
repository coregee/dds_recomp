# Original battle cuts, effect copying and scaling

Thirty-five complete bodies in `src/battle_effect_copy.c` add 2,540 recognized body bytes. All 3,328 original-instruction comparisons pass, reaching all 524 selected main addresses and executing 3,336,551 original steps. The host build passes with warnings treated as errors. The comparisons check full declared RAM, raw returns, Status, defined FPU/vector values and allocator primitives. They also check 14,353 ordered original copy/scale callback observations, including target, child argument and raw F12 scale, and 16 consecutive cut-allocation preludes with their actual original pointer returns.

The affected packet provider's existing 5,376 cases pass on the same rebuilt host. [The regression report](battle-effect-copy-regressions.json) checks current sources, verifiers, inputs, vectors and DLL hashes. All 35 interfaces are saved in the working Ghidra project, checked after reopening, and merged into current corrected exports. Floating returns use F0/32 bits; scale arguments use F12/32 bits followed by A0/64 bits. Host bit-transport wrappers receive no separate function credit.

Two original PCP43 callback pointers led to independently checked, previously unowned 16-byte bodies at `00192A70` and `00192A80`. Both set the original byte flag at `0054F1EC` and return zero. Recognizing them in place increases the inventory from 8,980 to 8,982 functions. They are counted as recovered only after the comparisons above.

## Reference context

Twelve reviewed Unity roles identify the cut constructor/end-frame query, current-skill query, model-ID and scale helpers, part handle/copy/scale and PCP copy/scale. Managed guards, HD field offsets and alternate selection logic are not imported. The remaining 23 names are descriptive native aliases, including seven hit constructors and ten length queries.

The pinned [DDS source-unit research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md) supplies shared effect/compiler context and cautions that battle units were rewritten. Its [Persona 4 transfer study](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/p4-transfer.md) also distinguishes complete checked transfers from structural and trivial-body matches. Direct links, revision and fetched hashes are retained in [the reference review](battle-effect-copy-matches.json). These sources guide identification; they do not establish Nocturne's native cut/template/PCP layouts.

Community randomizer, BF-format, archive and mod research remains part of the [open research inventory](community-research.md). This batch uses community source-unit and transfer context alongside original effect tables. The constructed effect templates are explicitly test inputs, rather than claimed community-decoded retail assets.

## Checked native behavior

- Cut creation allocates and clears 288 bytes, selects its bank from the low 16-bit cut number, links the cut before copying parts, and preserves FFFE skips, scale eligibility, native diagnostic printing and the live owner/count reload. Cases exercise both banks, up to 60 slots and consecutive calls.
- Part copying reloads its unsigned halfword kind after storing the new header. PCP copying uses either the original copy callback or its fallback initializer with the parameter-indexed asset pointer. Scale setters preserve actual delay-slot child loads and raw COP1 operands.
- All original seven-part records, the following backed zero record, the inspected 65-PCP prefix and the 87-entry model-scale switch remain byte-identical before and after every case. All 87 scale IDs are exercised, including both fixed-scale paths and the in-table default. The null part-scale path uses the original zero record; no table row is patched to supply a fake callback.
- Hit kinds 20/26/27/28/29 use the real cut constructor; kinds 24/25 copy their actual six/twelve-part structures. Five cut-frame wrappers and five literal-length bodies are independently recovered. Remaining model constructors are still pending.

Four complete DDS counterparts are checked in [the transfer report](battle-effect-copy-transfer.json): PCP0 scale `00163520`, texture getter `00151FC8`, asset copy `00186C18` and initializer `0017B180`. Scale is byte-identical across all 28 bytes and resolves an ambiguous match through the independently checked incoming PCP0 table position. The other bodies retain only documented global/table/call relocations, with the pool/getter/copy call chain checked; the initializer is also constrained by original PCP10. This is static DDS correspondence, not DDS execution.

## Remaining work and limits

The [hit-effect audit](battle-check1-effect-frontier.json) now has 32 pending direct descendants /4,876 bytes from 20 hit callback roots, down from 59 /6,800. A separate audit of the established part/PCP prefixes exposes 152 distinct create/copy/scale callback roots, 322 pending recognized descendants /52,808 bytes and seven missing exports. These graphs overlap and must not be added together. Missing callbacks need independent ownership/body discovery; the inspected prefixes do not establish full table extent or runtime selection. The action graph retains 391 pending direct bodies /92,340 bytes; CHECK1's own direct closure still has 12 /6,444.

Continue the remaining hit/model constructors and their real copy/scale dependencies before the outer CHECK1 callbacks. Unsupported host callbacks abort; they are not replaced with invented results. Asset loading/selection, general malformed ownership and pointers, arbitrary aliases, physical gameplay, complete FCSR arithmetic flags/timing and a matching executable remain unproved.

The corrected export preserves all 8,982 functions and exports/decompiles all 35 selected bodies with zero selected failures. As in earlier batches, its temporary processor-language replacement logs a `rom0` memory-block fixup error; read-only changes are discarded. Native capture and saved-interface checks have no errors or uninitialized reads. One rolling capture is retained; failed runs were replaced after correcting fixture stream backing, allocation capacity, unit backing and scale-branch coverage. No checkpoint, project/source copy, duplicate capture or new full-suite run was created.

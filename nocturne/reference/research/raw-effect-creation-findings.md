# Original raw particle and special-polygon creation

Three complete PS2 bodies are integrated in `src/raw_effect_creation.c`:

| PS2 entry | Recovered function | Unity reference | Complete static DDS counterpart |
| --- | --- | --- | --- |
| `00164B90` | `dds3ParticleCreate` | `parManager.dds3ParticleCreate`, `182563930` | `0015A378` |
| `00164FF8` | `dds3ParticleExpCreate` | `parManager.dds3ParticleExpCreate`, `182564820` | `0015A7E0` |
| `00169CD8` | `dds3SpPolyCreate` | `polyManager.dds3SpPolyCreate`, `18226BC70` | `0015F4D0` |

These are the first three constructor slots in the original five-row major
effect table at `00316EF0`, with a 48-byte row stride. Raw creation shares the
already recovered copy constructors; it does not need substitute constructors.

The common dispatcher indexes `00317270` by the low word of the incoming minor
index times twelve, calls the actual constructor with the full incoming source
register, then stores the minor index as a halfword at returned object `+140`.
The special dispatcher indexes `00317670` identically and writes minor `+B0`
and one at `+B2`. There are no added bounds, null or allocation guards.

The expanded particle header contains kind at zero and a relative offset at
four. Its emitter input is header `+10+offset`, using native word wrapping.
Only kind three with offset zero bypasses billboard creation. Other inputs write
`FFFFFFFF` into the input emitter's clone marker at `+28` before invoking the
constructor, then create the actual billboard from header `+10`, set its scale
and signed mode, apply the animation flag, and store the owned billboard at
returned emitter `+F4`. Input mutation and allocation order remain visible.

## Reference evidence

The [reference review](raw-effect-creation-matches.json) records the three Unity
bodies and four community files at revision
`bec33411543cdc487bad9debdf758f0090a2242c` with direct URLs and content hashes.
Community [particle manager source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/parManager.c)
corroborates common header, clone-marker, billboard and dispatch-index roles;
[polygon manager source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/polyManager.c)
and the particle API/table definitions supply related family terminology.
Original Nocturne instructions decide widths, addresses and behavior; Unity's
managed checks and layouts are not imported.

One signature difference is retained explicitly: community `parCreateIndexed`
is declared void. The matching native span leaves the constructor result in V0,
and Nocturne's generic creation caller at `0015AB34` stores that result as its
child pointer. The recovered Nocturne interface therefore returns the object;
the community declaration is not substituted for the original caller contract.

All three complete DDS instruction spans resolve in
[the transfer report](raw-effect-creation-transfer.json). Seventeen previously
resolved constructor bodies independently anchor the original table positions,
and four direct calls agree. Only the checked table-address immediates and JAL
targets differ. This is static transfer evidence; DDS execution is not claimed.

## Validation and current scope

[480 original-instruction comparisons](raw-effect-creation-validation.json)
pass with all 80 reachable main instruction addresses exercised. They cover all
13 common and four special families and all six shared initializer modes,
including 208 expanded resource creations, 104 actual texture uploads, 480
constructor callbacks, 220 colour callbacks, 260 declared emitter frame words,
48 model-track child private words and 44 independently checked RNG advances.
The complete declared RAM, defined returns, Status, COP1, defined VU/ACC/Q and
actual callback operands agree; no uninitialized reads are reported.

The private common-initializer prefix is independently supplied at the original
dispatcher/copy/initializer stack depth; it does not come from captured outputs.
Source inputs include the kind-three bypass and actual kind-zero TMX and
kind-one P2A paths. Native child constructors and all ownership operations run.

All three Ghidra interfaces are saved and independently reopened; current exports
are merged. Another 7,040 affected emitter/special-copy cases pass on the same
rebuilt host using existing original captures. Main recognized body credit is
376 bytes; the complete compared spans total 380 bytes including alignment.

Current recovery is **1,900 / 8,986 functions (21.144%)** with **324,109 focused
cases**, **786,793 aggregate cases** and **142 focused reports**. Those aggregate
counts combine registered historical captures; they are not a new full run.

The retail resource-bootstrap frontier now has **143 pending bodies / 22,292
recognized bytes** and zero missing exports. Continue the real generic wrapper,
D3P version conversion/loading, resource arrays, remaining major factories and
model-root creation. These cases do not execute unchanged retail D3P records;
that association remains necessary after the loading chain is recovered. Invalid
tables, exhausted allocation, outer scheduling, physical rendering, a matching
executable and whole-program recovery remain unproved. Rolling outputs replace
prior attempts; no checkpoints or backup copies were created.

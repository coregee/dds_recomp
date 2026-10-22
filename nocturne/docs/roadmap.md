# Roadmap: a full, readable decompilation

## The goal

All of SLUS_209.11, and every code-like resource on the disc, as readable,
well-typed C++ source that is proven to behave like the original. Where code
can be made legible, it is: names that say what things are, records instead
of offsets, functions that do one thing, comments that explain the game
rather than the instructions. Where it can't (hardware programming,
hand-scheduled VU code), it is isolated, documented and still tested.

**Done** means:

- every function in `reference/function-map.tsv` is `rewritten`, each one
  tested against the original instructions (the EE interpreter) or the
  legacy C on generated inputs;
- `legacy/` is no longer needed by anything and can be retired;
- scripts, messages and data tables are source that rebuilds the original
  bytes;
- the mechanics are documented in `docs/` in plain language.

Progress is the function map (`tools/ghidra/export-annotations.ps1`): 447 of
9,067 functions rewritten (4.9%) on 2026-10-22, 2,636 still only in legacy
C, 5,718 not yet identified.

## Principles

1. **Readability is the product.** Prefer the clearest code that is still
   equivalent: structured control flow, typed records, named constants. The
   original's layout is kept only where it is observable (record layouts,
   RNG draw order, the order of writes another module can see).
2. **Proven, not assumed.** No function counts as rewritten without a
   differential test that reaches its interesting branches, and a mutation
   showing the test sees a change. Quirks of the original are kept and
   commented, not fixed.
3. **Names by authority** (AGENTS.md): HD remaster, then strings and callers,
   then descriptive English names marked as such.
4. **Refactor freely, at module boundaries.** Modules follow the original
   units; split large ones by topic; move shared records into their proper
   headers; retire `external.hpp` entries as the callees are rewritten; merge
   duplicate helpers. Refactors keep the tests green.
5. **Hardware behind a platform layer.** DMA, GS packets, VU1 microcode, IOP
   and SIF code are rewritten as logic plus a small, documented platform
   interface rather than as literal register writes; VU microcode becomes
   data with a description of what it computes.
6. **Small, current repository.** No stored captures; generated output in
   `build/`; one current export of each thing.
7. **Commit by module**, when the user asks.

## Order of work

Work outward from what is finished, so each module's callees are already
rewritten or simple to fake, and grow the tools when they block progress.

1. **Tools first when they unblock a lot.**
   - The EE interpreter: add the FPU (COP1, with `ee::Float` semantics),
     128-bit loads/stores and the MMI instructions as modules need them.
   - A coverage check that lists rewritten functions without a test, and
     tests whose generator misses branches.
2. **Finish the message stack:** the font engine (`fr*`: layout, glyphs,
   variables), then panels (`itfPnl*`) and the message drawing.
3. **The script VM** (`scr*`): the interpreter, the command table and the
   commands, so the `.flow` sources are backed by readable code end to end.
4. **Battle** (`nb*`, the largest area): the turn engine (`nbAction*`), the
   remaining calculations, rewards, the battle UI.
5. **Game systems:** negotiation, shops and facilities, field movement and
   events, the menus (`cmp*`), Magatama and party screens.
6. **Engine layers:** files, CD and PAC archives, resources; models,
   materials, textures, drawing; effects, emitters, movies, sound.
7. **The C library and start-up** last, or whenever a module depends on
   their exact behaviour.

Unidentified functions are named while working through each area (HD names,
callers, strings), not in a separate pass.

## Data and resources

- More tables as source through `tools/gen_tables.py` as modules need them
  (shops, negotiation, encounters per area).
- Field data (`.inf`, `.npl`, `.dat`): decode with the code that reads it.
- The font's code-to-glyph map, to make the 60 glyph-coded message tables
  readable (docs/messages.md).

## Each module, in short

Choose → find names → read the original (legacy C, decompile, assembly) →
rewrite into `source/` → test against the original → teach Ghidra
(`nocturne_signatures.tsv`, `nocturne_types.h`) → refresh the function map →
document in `docs/` → commit when asked. AGENTS.md has the details.

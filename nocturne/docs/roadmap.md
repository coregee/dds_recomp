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

Progress is the function map (`tools/ghidra/export-annotations.ps1`): 1,632 of
9,068 functions rewritten (18.0%) on 2026-10-24, 2,094 still only in legacy
C, 5,048 not yet identified.

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
   - The EE interpreter: COP1, 128-bit loads/stores and VU0 macro mode are
     in (VU0 without flags or square roots); add the rest of MMI and the
     VU0 square roots as modules need them.
   - A coverage check that lists rewritten functions without a test, and
     tests whose generator misses branches.
2. **Finish the message stack:** the message manager and the font engine's
   text layout, glyph cache and message pages are done (docs/messages.md,
   docs/fonts.md); left are the font texture set-up and drawing
   (`frInitFontTable`, `frDrawFont*`, GS packets), drawing the panels
   (`itfPnlDraw`; the rest of `itfPanel` is done) and the message drawing,
   which need the platform layer for the GS.
3. **The script VM** (`scr*`): the interpreter, its process lifecycle and
   `scrCommonCommand` are done (docs/flowscript.md, docs/screen-effects.md).
   The parameter commands (`prm_*`) and the rest of `datCalc` behind them
   are done too (docs/party-and-field.md), and every rewritten command now
   reads its arguments through the rewritten VM. Left in the area: the
   per-frame fades (`dds3BlurUpdate`, `dds3SceneLightUpdateFirst`) and the
   effects' drawing, with the GS platform layer.
4. **Battle** (`nb*`, the largest area): the presentation queue's builders
   are done, and of the turn engine (`nbAction*`) the time list, the result
   helpers, the side events (counters, talks) and every action state
   (docs/battle-presentation.md), with the ailment AI (docs/enemy-ai.md),
   target selection, the help line's text, the command menu's lists and
   cursor, the skill effect's cut frames (`effBTLCut*`), and the kouka
   process that plays the packets, with all but six of its players, and
   the talks: their process and every step (docs/talks.md). Next: those six
   players (turns, damage numbers and words need the VU0's vector math in
   the rewrite; a devil's voice; flight, with the model loader), the
   remaining calculations, rewards, the battle UI's drawing.
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

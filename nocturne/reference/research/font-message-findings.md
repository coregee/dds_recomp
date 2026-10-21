# Native message parser and bitmap names

Ten complete routines in `src/font_message.c` now compile and pass **1,152 original-instruction comparisons**. Current integrated recovery is **1,000 / 8,973 recognized functions (11.145%)**, with 597,981 aggregated comparisons. The last full run remains 413 functions / 462,684 cases; these are focused additions, not a new full-suite result.

| PS2 entry | Recovered behavior |
|---|---|
| 001C96D8 | Load a bitmap name bank through real allocation and texture upload |
| 001C98C0 | Reference a name bank, loading it when necessary |
| 001C9A98 | Append one bank glyph and publish its native code and layout |
| 001C9B58 | Append the first name component |
| 001C9C28 | Append the second name component |
| 001C9D00 | Append both components with native spacing |
| 001C87C8 | Interpret message tags and their parameters |
| 001C8F08 | Parse mixed one- and two-byte text, tags and line breaks |
| 001C9188 | Construct a message request with explicit depth and nine arguments |
| 001C9140 | Construct a message request with default depth |

The comparison executes 4,362,384 original instructions across 3,376 recognized body bytes. It reaches **681 of 685 main instruction addresses**. The other four are compiler-generated branches in the tag dispatcher, separately proved unreachable from normal function entry by checking the original integer predicates and delay-slot behavior across their entire signed 32-bit input domain. They were not executed. The proof excludes arbitrary interior jumps, modified instructions and asynchronous register corruption.

Declared RAM, defined raw 64-bit results, CPU Status, primitive counts and callee saves agree. Actual recovered allocation, texture upload, string, control, name, variable and request-combination dependencies execute. Fourteen original FNT payloads back glyph decoding. The paths make 1,588 ordered semaphore calls and consume 794 captured ambient texture metadata words. The real printf and formatter produce 542 diagnostic lines, with all 11,924 bytes independently checked in buffered RAM.

Bitmap banks use the existing global-work pointer at `54EA20`, with images at `work+1D7C+bank*1200`, counts at `work+657C/657D+bank*2` and glyph pairs at `work+6584`. The loader retains signed-byte counts while the reference path uses unsigned counts. The 288-byte image copy preserves the original load-all/store-all ordering for each 32-byte chunk. Appending both components emits the second component first, adds eight to the measured width and final glyph, then emits the first.

The parser preserves native prefix skipping, stop tags, mode-dependent line breaks, mixed-byte decoding, style transitions and parameter cursor advancement. Deferred creation and position updates use the real prerequisite routines. The nine-argument constructor reads its final font pointer from the caller's stack; its reopened Ghidra interface records that storage explicitly. The eight-argument wrapper masks byte parameters and supplies zero depth.

One Unity role is reviewed: `001C9140` corresponds to `frFont$$MessageRequestExLocalize` at `18264C670`. Its managed construction and inlined parsing corroborate the role, while localization, exceptions and record layouts differ. The other nine retain descriptive PS2 aliases. Two complete DDS constructor spans resolve at `00196B30` and `00196AE8`, with the wrapper-to-constructor call agreeing. Other missing full matches remain unresolved.

All ten interfaces were saved in place, independently reopened and re-exported. The current Message direct dependency graph has **nine unresolved bodies / 1,812 recognized bytes**, stopping at 21 verified boundaries. Panel construction, parameters, drawing, window opening and the Message request/command remain next. Indirect panel callbacks require separate recovery beyond this direct graph.

Name bitmaps, names and message strings in these cases are generated bounded inputs. Original BMD text has not yet been exercised through this parser. Exhaustive text, arbitrary invalid or exhausted allocation graphs, physical rendering, kernel scheduling, FCSR, PS2 runtime and a matching executable remain unverified.

Evidence: `font-message-validation.json`, `font-message-dispatch-proof.json`, `font-message-interfaces.json`, `font-message-abi.json`, `font-message-matches.json`, `font-message-transfer.json` and `message-command-frontier.json`. These are rolling outputs; no checkpoint, source freeze or backup copy was created.

Subsequent [panel initialization and window opening](panel-construction-findings.md) integrates five of those direct dependencies and all thirteen non-null initialization callbacks. The current Message direct graph has four unresolved bodies / 1,020 recognized bytes. The separate rendering callbacks remain unrecovered.

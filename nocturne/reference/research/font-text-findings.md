# Native font binding and string construction

Nine complete PS2 routines now compile and pass 1,152 comparisons against original instructions. Integrated recovery is **980 / 8,973 recognized functions (10.922%)**, with **595,549 aggregated comparisons**. The last full comparison remains 413 functions / 462,684 cases; this is a focused addition.

| Native entry | Recovered behavior |
|---|---|
| 001C6B68 | Bind a shipped FNT resource, palette, optional metrics, cache and compressed glyph sections |
| 001C7088 | Glyph width, spacing and kerning through original EE floating-point values |
| 001C7408 | Allocate a texture slot and build the actual texture upload |
| 001C7568 | Increment a cached glyph reference or decode, allocate, upload and publish a new glyph |
| 001C76E0 | Create a text glyph, including caret remapping and two-byte character indexing |
| 001C7288 | Append a control glyph to a new or existing font request |
| 001C7890 | Build or append mixed-byte strings using actual length, glyph and request routines |
| 001C8108 | Combine font requests with the native mode-one splice |
| 001C7828 | Build a string request and combine it with a supplied request |

The cases back complete payloads from fourteen original font files. Cached and uncached paths execute the recovered free lists, compressed decoder, pool allocator, texture packet builder, initializers and string-length implementation. Negative style arguments preserve the selected style; the native caret maps to glyph 38, while last-code tracking records the original character. Empty strings, missing bound resources, control glyphs, supplied requests and mixed-byte strings are included.

All **529 non-delay root instruction addresses** are reached across **3,118,906 original steps**. Full declared RAM, defined raw 64-bit results, CPU Status/primitives and callee saves agree. The real upload dependency makes 972 semaphore calls; their ordered operands and supplied syscall results agree. The 486 otherwise unassigned upload metadata words are captured as explicit ambient stack inputs. EE COP1 register values use the existing pinned software value model; this does not validate FCSR flags or physical rendering.

Three reviewed Unity counterparts supply semantic names: `frFont.frSetFont`, the byte-string overload of `frFont.frSetFontString`, and `frFont.frCombineFontRequest`. Managed object layouts and HD rendering differ. The other six bodies retain descriptive native identities. Opaque shared HD lock stubs are excluded as source evidence.

Three complete new DDS spans resolve: binding at `001944A0`, texture glyph creation at `00194D20`, and cached glyph acquisition at `00194E80`. Five agreeing call links connect actual allocation, texture-slot and upload dependencies. The font context relocates from `0056BA30` to `003D6C80`. The tiny combine wrapper remains ambiguous among three spans; routines without complete DDS matches are left unresolved. These are static transfer findings, not DDS execution evidence.

All nine Ghidra names and interfaces were saved into the working project, reopened and exported into the current inventory. The main Message path now has **29 unresolved direct bodies / 6,344 recognized bytes**, stopping at 33 verified boundary routines. Next are the text parser at `001C87C8`, panel opening and their remaining dependencies before recovering the entire Message command.

Invalid or exhausted allocation graphs, exhaustive glyphs and text, kernel scheduling, PS2 runtime and a matching executable remain unproved. Evidence lives in `font-text-validation.json`, `font-text-interfaces.json`, `font-text-abi.json`, `font-text-matches.json`, `font-text-transfer.json`, `message-command-frontier.json` and `src/font_text.c`. Current files are overwritten in place; no checkpoint or backup copy was created.

Subsequent [native text prerequisites](font-parser-findings.md) recover ten more complete routines and reduce the Message graph to 19 unresolved direct bodies.

# Native message text prerequisites

Ten complete routines now compile and pass **1,280 original-instruction comparisons**, reaching all **242 non-delay root instruction addresses** across **3,236,530 original steps**. Integrated recovery is **990 / 8,973 functions (11.033%)**, with **596,829 aggregated comparisons**. The last full comparison remains 413 functions / 462,684 cases; this adds focused evidence.

| Native entry | Recovered behavior |
|---|---|
| 001C7A88 | Store spacing and remeasure the actual linked text chain |
| 001C7B40 | Store depth after the native lower-word shift by four |
| 001C7C00 / 001C7C10 | Enable / disable font mode bits, returning the previous byte |
| 001C81B8 | Bind message font context eight |
| 001C8508 | Append a selected variable string through live message style and request fields |
| 001C86A0 | Complete pending request creation and position publication |
| 001C8730 | Advance the line and mark both pending operations |
| 001C8758 | Append a special two-byte code and apply spacing/depth |
| 001C9D60 | Reconstruct a name from global-work byte pairs and append its real font request |

The native message record stores X/Y/depth at +0/+4/+8, style/color/transparency/speed bytes at +C through +F, string pointer at +10, request at +14, cursor at +18 and pending creation/position bytes at +1C/+1D. Line advance adds `word(54F40C) << 3` to Y and sets both flags. Deferred creation uses the string at `54F430`, which is empty in the original executable, and then invokes the actual request combination, speed and position routines. It does not synthesize a printable newline glyph.

Variable strings are selected from `56BBD0 + low8(index)*4`. The routine walks one- or two-byte characters, reads the current message style each iteration and retains the native handling of style transitions. The recovered paths execute actual string length, byte initialization, font binding, cached/uncached glyph creation, compressed decoding, allocation and texture upload. Generated strings and name tables are backed in ordinary RAM; the font payloads are the fourteen original FNT files.

The name routine reads the existing global-work pointer at `54EA20`. A signed-byte name index selects byte pairs at `work+6604+index*20` and the live character count at `work+6654+index`. A zero first byte emits only the second byte; otherwise both bytes are emitted. Construction enables mode bit one and then clears it, even if it was already enabled on entry. The resulting request is measured with spacing four. These name bytes are generated fixtures, not recovered original player names or a font dictionary file.

Full declared RAM, defined raw 64-bit results, CPU Status/primitives and callee saves agree. Actual dependencies make **738 semaphore calls**, with ordered arguments/results compared, and consume **369 captured ambient texture metadata words**. Original EE floating-point register values use the existing pinned software model; FCSR, physical GS rendering and kernel scheduling remain outside the comparison.

Selected message/text aliases exercise style changes. One explicit adversarial failure-state case backs low RAM: missing style-one binding returns zero, but the native variable helper still invokes unchecked spacing writes. Those writes alter the aliased message style, and the next iteration takes the null-request creation path. The C retains this native behavior. This is a modeled returning failure case, not a claim that null-pointer use is safe in a native C build or that arbitrary invalid graphs are supported.

Five Unity counterparts are reviewed: `frSetFontSpace`, `frEnableMode`, `frDisableMode`, `frCreateNewHandle` and `frMessageReturnCode`. Managed record offsets and HD line scaling differ. The other five functions keep descriptive PS2 identities. Three complete DDS spans resolve: spacing at `001953A8`, depth at `00195460` and context-eight binding at `00195BD8`; two agreeing calls connect measurement and binding. Missing full matches are left explicit rather than inferred from names.

All ten interfaces were saved into the working Ghidra project, reopened and exported. The main Message graph now has **19 unresolved direct bodies / 5,188 recognized bytes**, stopping at 38 source-current verified routines. Next are the six bitmap-bank load/reference/append routines at `001C96D8` through `001C9D00`, the tag handler `001C87C8`, string parser `001C8F08` and request constructors. Panel opening also contains indirect dispatch that the direct graph alone does not enumerate.

Evidence: `font-parser-validation.json`, `font-parser-interfaces.json`, `font-parser-abi.json`, `font-parser-matches.json`, `font-parser-transfer.json`, `message-command-frontier.json`, `src/font_parser_support.c` and current function exports. Outputs are rolling files; no checkpoint or backup copy was created. Full executable recovery, PS2 runtime validation and matching-binary validation remain unfinished.

Subsequent [native message parser and bitmap-name recovery](font-message-findings.md) integrates those ten remaining text bodies. The current Message direct graph has nine unresolved bodies / 1,812 recognized bytes; continue panel opening and Message request/command, including their indirect callbacks.

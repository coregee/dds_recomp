# Native compressed font recovery

Seventeen complete font routines (1,164 recognized body bytes) now compile and match original PS2 instructions. Integrated recovery is **971 / 8,973 functions (10.821%)**, with **594,397 aggregated comparisons**. The complete glyph decoder and its actual pool allocation wrapper are recovered; font request creation, rendering and the main Message command remain incomplete.

The rolling font report contains **2,952 passing comparisons**, reaches all **250 non-delay root instruction addresses** and records **3,083,049 original steps**. Full declared RAM, defined raw 64-bit results, CPU Status/primitives and callee saves agree. Allocation executes the real recovered 0x120-byte pool allocator and its original class/page/interrupt operations. The six-argument text initializer uses native A0–A3/T0/T1 storage. No decoder, allocation or other game-return substitutes are supplied.

| Native entry | Recovered body |
|---|---|
| 001CA9C0 / 001CA9C8 | Resource identity helper / compressed section resolution |
| 001CAA18 / 001C74E8 | Complete glyph decoder / actual decoded-glyph allocation |
| 001CABD8 / 001C6018 | Glyph free-slot take / texture free-slot unlink |
| 001C6098 / 001C60E0 | Fixed 416-entry / 264-entry codebook search |
| 001C6128 / 001C7080 | Last code recording / native 24-byte glyph storage size |
| 001C83B0 / 001C83F0 | Default / native resource font width |
| 001C8418 / 001C8458 | Default / native resource font height |
| 001C7660 / 001C76A8 | Text / font request initialization |
| 001C8230 | Linked text width plus signed-byte spacing |

The decoder resolves a tree, glyph bit-index table and packed bitstream from three section pointers. A tree node occupies six bytes, with left/right child halfwords at +2/+4; a zero left child marks a leaf whose byte value is at +4. It consumes little-endian bits from 16-bit words with a `10000` sentinel, resets to the root after each emitted byte and stores the final output count at `551EA0`. Original unaligned index-word loads, initial bit offsets, sentinel refill and partial terminal prefixes are preserved. The native loop consumes at least one bit, even for a zero requested bit count; the source retains that behavior. Zero-count underflow/nontermination and invalid trees are outside the returning fixtures.

Generated balanced and unequal-depth trees exercise bit offsets/refill paths. Both embedded codebooks are taken directly from the executable; every table entry and 64 absent codes per table are tested, preserving first-match results and the input's low 16 bits. Other cases cover signed global dimensions, raw upper argument lanes, live section-header aliases, finite slot lists, initialization store order and spacing arithmetic.

Fourteen primary original FNT files were extracted from their DDT/IMG offsets into `game/dds3/font/` and `game/dds3/font/EngFont/`. The native setup instructions at `001C6B68` explain why the compressed subresource is inside the FNT, after the palette/optional metrics/glyph descriptors. The extraction audit locates that section and independently traverses its packed bits without reproducing the native sentinel implementation. Eight glyphs per file, including early/interior/final indices, each decode to 288 bytes. All **112 sampled glyphs pass both direct decoding and allocation**, for **224 original-font cases / 64,512 independently checked output bytes**. Complete original file bytes are backed in each such fixture; these are actual shipped payloads. Native FNT setup itself is a lead rather than a recovered source body, and exhaustive glyphs, visible rendering and runtime behavior remain unproved.

Four named HD roles are reviewed: default width/height and text/font initialization. HD delegates font size to TextManager and uses managed layouts. The other thirteen bodies retain descriptive native identities; this avoids forcing PS2 compressed resources onto unrelated managed HD routines.

Seven complete DDS source bodies resolve, including the entire 288-byte decoder. Four call links agree. The decoder is anchored by the already checked allocation wrapper; all 72 contiguous words match except its decoded identity-helper JAL and output-count GP displacement. REGINFO GP resolves the relocated count global. That call reduces 33 identical resource-identity candidates to one. Native glyph-storage-size remains ambiguous among three spans, and geometry/codebook/initializer targets with no complete match remain unresolved. These checks establish static transfer evidence only.

All 17 Ghidra interfaces were saved in place and independently reopened; 17 current exports merged into the 8,973-entry inventory. The latest direct Message dependency audit now has **38 unresolved bodies / 8,788 recognized bytes**, stopping at 38 source-current verified routines. Next are native FNT binding `001C6B68`, glyph layout `001C7088` (including its real EE float conversions), glyph/text construction and the `001C87C8` parser. Preserve their actual dependencies before integrating RequestMessage/SetMessage; the full executable goal remains incomplete.

Evidence: `font-resource-validation.json`, `font-resource-assets.json`, `font-resource-interfaces.json`, `font-resource-abi.json`, `font-resource-matches.json`, `font-resource-transfer.json`, `message-command-frontier.json`, `src/font_resource.c` and current exports. Fixture preparation and capture use rolling files; no checkpoints, project copies or frozen sources were created.

Subsequent [font binding and string construction](font-text-findings.md) recovers the setup, layout, cached/uncached texture glyphs, control glyphs and string request routines. Current progress and the remaining 29-body Message graph are recorded there.

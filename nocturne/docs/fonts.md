# The font engine

As established by `source/shared/src/interface/font.cpp` and `font_message.cpp`
(original unit `frFont`, 0x1C6018..0x1CAC30); every function there is
checked against the original instructions with the game's own fonts.

## Fonts

The fonts are `.fnt` files (`game/dds3/font/`, the US build uses
`font/EngFont/`): a 0x24-byte header (glyph count, 24x24 cells, 0x120 bytes
per glyph), 16-color palettes, two per-glyph metric tables {left, right},
a zeroed array the engine uses as its glyph cache, and the glyphs,
Huffman-compressed. `font0` and `font1` have 706 / 707 glyphs, `font2` and
`font3` 340.

Nine **styles** (0x56BA30) point into loaded files. `frLoadStyleAll` loads
`/font/font0.fnt`..`font3.fnt` into styles 0..3, except that style 1
shares style 0's file (`frLoadStyle`), so `font1.fnt` is never used by it.
Style 8 is a message table's own font (`frSetExtDic`, the table's
`pextdata`); characters from code 0xC080 in a page are drawn with it.

A character's glyph number is its code - 32 for ASCII, and for 2-byte
codes ((code - 0x8080) >> 8) * 128 + (code & 0x7F). `^` is drawn as `&`.

## Building text

A string becomes a **font request** (`_FRQ`): one `_TEXT` per character,
each referring to a glyph in the texture cache. A page is a chain of
requests (a new one per line and after each control code); a chain is
handled by its *last* request, whose `prev` links lead back to the first,
which every request's `head` points at (`frCombineFontRequestEx`).

- **Advance** (`frGetXShiftLev`): styles 0 and 1 are drawn at the base width
  (20 by default, `frSetBaseWidth`) and give ASCII half the style's default
  advance (0x326060: 18, 12, 10, 13, 22); a space gets an extra
  `space_width`. With metrics mode on (as while laying out a page), the
  font's {left, right} gives the advance (right - left) and the shift
  (left * 16), scaled by width / 20 for styles 0 and 1 and truncated as the
  EE's FPU does. `!` and `1` get 2 pixels more on each side.
- **Glyph cache** (`ps2FontAcquireCachedGlyph`): a glyph used for the first
  time is decoded (`ps2FontDecodeGlyph`: a tree of 6-byte nodes, walked by
  bits read low bit first from 16-bit words) into a free 24x24 cell of the
  font texture and queued for upload; later texts share it, counting
  references. Destroying a chain releases glyphs no text uses any more.
- **Destroying**: `frDestroyFontRequestNow` frees a chain;
  `frDestroyFontRequestAfter` adds it to a list for the frame being built,
  freed once that display buffer comes round again (the frame is still
  drawing it). Texts with tp 2 can fade out first (8 alpha and 2 units
  down per frame).

## Laying out a page

`frAnalyzeMessage` reads a page of a message table (docs/messages.md):

- characters are appended to the current request; a line feed (or `{br}`)
  starts a new request on the next line (the line height is
  `gMessageStepY`, 20); in compact mode lines break by themselves and line
  feeds are ignored;
- after any control code the next character starts a new request, so a
  page is a chain even on one line;
- control codes act as in docs/messages.md; the codes that end a page set
  `frGetMessageResult` (1 wait, 2 wait without the speaker, 4 lip-sync);
- `F2 08` at the start of every page is skipped by the default case. The
  page parser does test for it, but the test is inverted: it skips four
  bytes only when the page starts with a character followed by 8.

**Entered names** (`{firstname}`, `{lastname}`, `{fullname}`) are not drawn
from the font: the name-entry screen keeps each name's letters as 24x24
bitmaps in the save data (four names, 16 letters each, family name first),
loaded into texture cells on first use and freed when no text uses them
("NAME[n] : Translate." / "Restore." in the debug output). `{name n}`
writes the same name as ordinary text.

## Helpers

`frControlCodeLength` gives a control code's length as the line counter
sees it: F202, F203, F206, F207 and F209..F20D take 4 bytes, F20E 3,
everything else 2 (F208 included, though pages store it in 4).
`frCountMessageLines` and `frCopyMessageLine` count and copy lines.

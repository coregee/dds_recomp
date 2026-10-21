# Native font and Message frame drawing

**15 complete PS2 routines** in `src/message_frame_draw.c` pass **2,432 original-instruction comparisons**, including 128 calls through the previously recovered ordering flush. The new bodies cover **4,272 recognized bytes** and all **941 main instruction addresses**. Full declared RAM, defined register returns, CPU Status, primitive operations, callee saves and ordered submission/flush callback traces agree. The affected C builds with warnings treated as errors. All fifteen interfaces are saved and independently reopened in the working Ghidra project; current exports are merged in place.

The original startup caller **00101DD8** invokes **002ACDC0** to initialize **85 ordering records**, each 32 bytes, at **002F5F18**. It installs **002ACD40** at record **+10** and **002ACD98** at **+14** (hexadecimal). Those are the actual recovered append and conditional-prepend bodies. The debug record **002F6938** belongs to this same table. Zero callback words in the initial ELF were uninitialized data, not the runtime callback identity.

Every comparison executes the real ordering initializer and real panel position/color dependencies. There are **7,461 actual draw callbacks**, **10,880 flush callbacks** and **6,385,427 original instruction steps**. All 128 frame-to-flush cases execute real message drawing before the flush. Independent walks verify **124 nonempty terminated chains**, four empty returns, all 85 initialized callback pairs per case, and the two matching RGBA values in **128 glyph packets**. No returning game callback is substituted.

| PS2 entry | Recovered role | Reviewed Unity counterpart |
| --- | --- | --- |
| 001C6338 | Font color byte swap | Descriptive PS2 alias |
| 001C6438 | Eleven-argument glyph packet builder | Descriptive PS2 alias |
| 001C7CB8 | Fade and vertical glyph effect | frFont.DrawEffect, 18264FEE0 |
| 001C7E00 | Default font draw wrapper | frFont.DrawFont, 1826502E0 |
| 001C7E18 | Font draw mode wrapper | frFont.DrawFontEx, 182650260 |
| 001C7E38 | Full font/list draw body | frFont.DrawFontEx2, 182650000 |
| 001CB7B0 | Flat sprite packet | Descriptive PS2 alias |
| 001CC2B8 | Panel state/draw/submission | Descriptive PS2 alias |
| 001CD270 | Panel draw state packet | Descriptive PS2 alias |
| 001CF818 | Selection text marking | Descriptive PS2 alias |
| 001D0930 | Message frame draw flow | itfMesManager.DrawMesFlow, 182448870 |
| 001D0AC0 | Message and speaker windows | itfMesManager.DrawWindow, 182449540 |
| 001D0B90 | Selection cursor | Descriptive PS2 alias |
| 001D0E90 | Wait cursor | Descriptive PS2 alias |
| 001D1108 | Debug window outline | itfMesManager.DebugDrawWindowLine, 182447DD0 |

Native glyph packets have eight register arguments and three signed stack words at **0/8/10**, a 144-byte packet, a fresh 32-byte chain descriptor, RGBA upper word **3F800000**, palette table **56BBA8** and common texture parameters **56BB90**. The packet uses wrapped native coordinates, signed UV words and the actual ordering callback. Native font traversal follows display root **+2C**, request **+28** and text **+28**; selection marking follows distinct Y groups through request **+24**. The global counter at **54F428** resets per request, and visible glyphs advance their original frame counters.

The HD bodies accelerate role identification but change behavior. Native fade scaling is **22**, with a zero-denominator fallback of **24**; HD uses **64** and lacks that native fallback. Native alpha clamping retains mask **FFFFFF00**. Previous text and lookahead layouts determine the delay threshold; different preceding glyph types exercise a separate branch. Bobbing follows the native five-step counter cycle. Native frame flag caching, selection phase changes, signed cursor alpha and geometry, and the full-width debug owner comparison are preserved rather than copied from managed layouts.

Five new complete DDS spans resolve with **24 agreeing callee constraints**: color swap **00193C70**, flat sprite **00198F58**, panel submission **00199A68**, draw state **0019ACE0**, and selection marking **0019D958**. The tiny default font wrapper retains fourteen unconstrained candidates and is not accepted as a resolved DDS identity. Other new bodies have no complete match under the current comparison mask.

Rolling evidence is in `message-frame-draw-validation.json`, `message-frame-draw-interfaces.json`, `message-frame-draw-abi.json`, `message-frame-draw-matches.json`, `message-frame-draw-transfer.json` and `message-frame-draw-frontier.json`. These generated fixtures exercise backed font/text/UV/palette records; they do not establish rendering of original font pixels or BMD pages. Earlier font and BMD comparisons retain their separately documented scope. Actual GS rendering, scheduler/gameplay behavior, arbitrary invalid/cyclic inputs and a matching executable remain outstanding.

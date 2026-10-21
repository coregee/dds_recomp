# Native Message command, preparation and callbacks

Six complete PS2 routines compile and pass **860 original-instruction comparisons**, including 159 executions through the existing interpreter. All **209 main instruction addresses** in the six bodies execute. The bodies total **1,080 recognized bytes**; the comparison executes 2,744,846 original steps and observes 375 VM indirect calls. Source is `src/message_request.c`; current evidence is `message-request-validation.json`.

| PS2 entry | Recovered role | Direct cases | HD reference |
|---|---|---:|---|
| 001CD2E0 | itfMesMngMessage | 127 | itfMesManager.itfMesMngMessage |
| 001CDB80 | itfMesMngRequestMessage | 127 | itfMesManager.itfMesMngRequestMessage |
| 001CF1D8 | ps2MessageReady | 127 | itfMesManager.ReadytoMessage |
| 001CF778 | CountLineMessage | 128 | itfMesManager.CountLineMessage |
| 001CEB38 | itfMesMngSetKutiCallback | 96 | itfMesManager.itfMesMngSetKutiCallback |
| 001D1640 | installed diagnostic callback | 96 | Descriptive PS2 alias |

The command uses the signed live completion byte: zero requests page zero, a positive value waits, and a negative value clears the byte and completes. A negative current message ID completes immediately. Request commits all 32 variables, prepares text, replaces speaker ownership when needed, opens the actual panels and updates native phase flags. The real resource lookup, parser, font construction, recycling, allocator, panel constructors and formatter execute; their returns are not supplied substitutes.

Preparation preserves the native dynamic line-height division and its **BREAK 7** on zero height. All 22 zero-height cases observe that trap separately. Unity's counterpart divides by constant 24. Managed localization, layout and additional guards are reference differences, not PS2 behavior to copy. Unity `SetMessage` at 18244E610 is a separate TextMeshPro UI method and is not used as the native request identity.

One unchanged first message/page from each of the **31 shipped BMD files** executes through command, request, preparation and interpreter paths: **124 original-page cases** and 7,164 independently checked page bytes. Full original resources go through the actual pointer relocator. The page bytes remain unchanged, and relocated record pointers are independently checked. These are selected pages, not exhaustive shipped text or gameplay execution.

The cases supply generated player variables, finite font/text lists and sufficient allocation space. Generated ASCII/tag cases use original FNT payloads with explicit cache readiness. Some shipped pages contain codes beyond those small font resources; their cases use an explicit broad cached-font view with shipped dimensions/palette. This tests message behavior without claiming original glyph loading or rendered appearance. Actual uncached glyph decoding has separate evidence in `font-resource-validation.json` and `font-text-validation.json`.

Caller 001D1470 installs callback 001D1640. Its real native printf prints `********* AAAA ********` followed by a newline. All 96 direct outputs match exactly; 17 additional connected invocations produce the same literal. The setter preserves the native low 32-bit function word. The other installed callback **001E52B0**, used by 001E52C8/001E5360 and calling **001E3C00**, remains unrecovered. Nine panel draw callbacks also remain separate work; the recovered direct Message graph does not imply complete display behavior.

Static comparison finds three full DDS spans: **001CD2E0 -> 0019AD50**, **001CF778 -> 0019D8B8**, and **001D1640 -> 0019FCA8**. The diagnostic's printf target agrees and its relocated literal at DDS 003A1558 is identical. Request, preparation and callback setter have no complete match under the current mask. These are checked static transfer leads, not DDS runtime validation.

The six interfaces are saved in the working Ghidra project in place, independently reopened, and merged into current exports. No checkpoint, project copy or frozen source tree is created. PS2 runtime, physical rendering, scheduler integration, exhaustive message coverage and a matching executable remain outstanding.

Subsequent [native KUTI recovery](event-kuti-findings.md) closes callback 001E52B0 and both installers, with their real scene/unit lookup and motion setters. The six-body evidence above retains its original scope; the separate panel draw graph remains unrecovered.

Subsequent [panel drawing and packet recovery](panel-draw-findings.md) closes the nine callback graphs and original dispatcher with 25 complete routines and 3,360 passing comparisons. Frame submission, actual ordering-table callbacks and physical rendering remain separate work.

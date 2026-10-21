# Message window commands and font request prerequisites

Eighteen complete native bodies (936 recognized bytes) are now compiled, compared with original instructions, saved in the working Ghidra project and exported in place. Integrated recovery is **954 / 8,973 functions (10.632%)**, with **591,445 aggregated comparisons**. This remains partial executable recovery. No gameplay or matching-binary result is established.

The rolling message/font report contains **2,560 comparisons**: 2,432 direct cases for the new bodies and 128 programs through the existing script interpreter. All **186 non-delay instruction addresses** in the new roots are reached. The original execution takes 115,441 steps and makes 320 actual VM indirect calls. Full declared RAM, defined raw 64-bit results, CPU Status/primitives, callee saves and ordered interpreter calls agree with compiled C. Cleanup calls execute the existing native-derived font recycling and message/selection initializers; no supplied game-return substitutes are used. The 256 speed cases cover every low-byte speed. Other fixtures exercise signed page counts, negative command IDs, raw upper lanes, linked requests, live overlapping variable tables and layout-record aliases.

| Native entry | Recovered body |
|---|---|
| 001CD5B0 / 001CD5F8 | OpenWindow / CloseWindow commands 1 and 2 |
| 001CD670 / 001CE450 | Message-window close transition / high-halfword flag setter |
| 00158940 | Actual empty native option hook |
| 001CF178 / 001CF1A8 | Eight-byte resource record indexing / signed page lookup |
| 001CF440 / 001C9230 | Commit 32 variable pointers / font variable setter |
| 001C9220 / 001CE510 | Full-width global flag test / local variable retrieval |
| 001CF490 / 001CF710 | Speaker-name pointer / last linked font request |
| 001CF748 / 001CF7E0 | Copy final font parameters / update linked Z values |
| 001C7B30 / 001C7A60 / 001CFA00 | Position, byte-clamped speed and linked maximum-speed controls |

OpenWindow returns one for negative message IDs and otherwise sets bit `200000`. CloseWindow returns completion from its original `flags & 300` snapshot: zero completes, phases `100` and `200` call the real close routine, and phase `300` waits. Closing preserves the native phase updates, releases both message and selection requests, then reloads flags before clearing `200000`. HD adds modern speaker/UI operations. In particular, `ChildHD.UpdateOption` has substantial HD behavior while its native call target `00158940` is genuinely empty.

Fifteen named HD semantic counterparts are recorded. Three remaining bodies use descriptive native aliases. The tempting `GetFRQString` name at HD `182449EA0` is explicitly rejected for native `001CF178`: HD reconstructs text from a linked font chain; the PS2 helper returns `resource + 20 + index*8`. HD `GetTypeHeader` at `18244A840`, called by HD RequestMessage, instead has the corresponding index/record role and is recorded as a lead for later formal promotion. HD uses managed records, localization and pointer/layout widths that must not be copied into native source.

The DDS report resolves **15 complete source spans**, three complete cleanup/header dependencies and the complete current-message getter. Ten caller links agree. The font variable setter is anchored by CommitVarTable and checked word-for-word except its decoded indexed LUI/store address pair (`56BBD0` to `3D6E20`). Both window wrappers anchor the current-message getter; its decoded REGINFO GP displacement agrees with the already checked VM current-work global. The local variable getter, global flag test and speed-max loop remain unmatched. This is static transfer evidence, not DDS runtime verification.

The main `Message` command (`001CD2E0`, command 0; 5,634 static shipped uses) is still unresolved. At this batch, the direct dependency audit found **55 unrecovered bodies / 9,952 recognized bytes**, stopping at 24 already verified boundary routines. The subsequent [font-resource batch](font-resource-findings.md) recovers seventeen more bodies, including the decoder/allocation; the current audit now has 38 unresolved bodies. The remaining core is RequestMessage `001CDB80`, SetMessage `001CF1D8`, font creation `001C9140` → `001C9188` → `001C8F08`, the parser `001C87C8`, font allocation/configuration, and panel opening `001CFA90` / `001CFB68`. Recover their actual allocation and parser paths before claiming the command works. The native GetFontHandleUnit `001CF778` also retains a real divide-by-zero BREAK path.

Evidence: `message-commands-validation.json`, `message-commands-interfaces.json`, `message-commands-abi.json`, `message-commands-matches.json`, `message-commands-transfer.json`, `message-command-frontier.json`, current function exports, and `src/message_commands.c`. Ghidra saved all 18 interfaces and independently reopened them successfully; all 18 exports merged into the 8,973-entry inventory. Rolling captures replace prior subsystem outputs. No project copies, numbered checkpoints or frozen sources were created.

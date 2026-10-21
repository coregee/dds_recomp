# Native panel drawing and packet graph

**25 complete PS2 functions** in `src/panel_draw.c` pass **3,360 original-instruction comparisons**, covering **4,580 recognized body bytes** and all **1,048 main instruction addresses**. This closes the previous 24-function panel drawing graph and adds the actual dispatcher at **001CC328**. The nine original callback words at **00326478** select the recovered bodies. Allocation, DMA-chain append, inline-register tags and texture lookup use actual recovered dependencies.

The cases include **288 dispatcher calls**, 32 per original panel type. **144** execute real panel allocation, the original position/color initialization tables, and drawing in sequence. An independent chain walk checks **1,424 packet records**, including reused chain heads and the expected packet count for each type and split-height branch. Full declared RAM, defined raw64 returns, Status, CPU primitives and native callee saves are checked. The source compiles with warnings treated as errors. The 25 signatures are saved in the working Ghidra project, independently reopened and merged into current exports.

The source preserves native packet behavior: untouched DMA padding bytes 2..7, raw register/primitive/loop lanes in packed GIF tags, wrapped coordinate offsets **7000/7900**, low32 zero-extended Z, native ordered reads and stores when selected inputs overlap output, and native signed/full-width loop decisions. Odd strip counts retain the original difference between allocated packet length and vertices written. Zero and selected negative counts retain unchecked native behavior; arbitrary positive counts whose low word is zero are not forced through billions of iterations.

Textured sprites reserve their 112-byte packet first, then append an 80-byte texture-state packet **before** the sprite in the DMA chain. The texture's word at **+28** points to the register record; getters read qwords at **+10/+20/+30**, emitted as TEX1/TEX0/CLAMP for the selected context. Facility drawing brackets a six-vertex strip with 48-byte ALPHA packets. Message2 uses signed wrapped height **8B1** and cut **458**; Pera uses height **569**, cut **2B4**, and the native wrapped `(alpha << 5) >> 7`. These constants are hexadecimal. The speaker's right rectangle retains reversed X endpoints. Plain panels index all three inset layers from one private 96-byte stack array.

Unity names require body comparison. Three named methods occupy different semantic roles from their names in the PS2 table:

| PS2 role / entry | Reviewed Unity method / address | Body anchors |
| --- | --- | --- |
| Normal / 001CC9A0 | DrawNormal / 1826616A0 | Three colored rectangles |
| Message / 001CCA50 | DrawMesWin / 182661380 | Three eight-vertex strips, six four-vertex lines |
| Selection / 001CCB60 | DrawSelWin / 182662200 | Three eight-vertex strips, two four-vertex lines |
| Plain / 001CCC70 | DrawPlain / 182661A50 | Inset geometry, fill and three five-vertex outlines |
| LeftFade / 001CCDB8 | **DrawPera1 / 1826618B0** | One rectangle, first color alpha |
| Facility / 001CCDF0 | **DrawLeftFade / 1826609E0** | ALPHA type2, six-vertex strip, ALPHA reset |
| Message2 / 001CCE78 | DrawMesWin2 / 182660BA0 | One/three textured vertical sections; HD changes scale and adds rendering calls |
| Speaker2 / 001CCFB0 | DrawSpkWin2 / 182662530 | Horizontal sections; HD uses screen-coordinate helpers and rendering calls |
| Pera / 001CD0C8 | **DrawFacility / 182660330** | Three rectangles, alpha shift, 569/2B4 textured sections |

These are reviewed semantic counterparts, not identical managed/native layouts or rendered behavior. HD divides some depths by 16, introduces managed bounds/ownership checks and changes screen sizing. The shared HD dispatcher body at **1810D6760** is not accepted as an exact identity for PS2 001CC328. The sixteen remaining PS2 entries use descriptive aliases.

Fourteen new complete DDS spans resolve, with **28 agreeing callee constraints** across new and existing dependencies:

| Nocturne | DDS | Role |
| --- | --- | --- |
| 002AB0D8 | 002D2478 | Texture filter register |
| 002AB0E8 | 002D2488 | Texture wrap register |
| 002B9C18 | 002E12C0 | Texture packet size |
| 002B9C20 | 002E12C8 | Three-register texture packet |
| 002B9CC8 | 002E1370 | Texture packet allocation/append |
| 002B9D38 | 002E13E0 | Inline byte-count packet |
| 002B9D68 | 002E1410 | Packed packet size |
| 002B9D78 | 002E1420 | Packet payload address |
| 002B9D80 | 002E1428 | Packed tag |
| 001CB250 | 00198858 | Four-vertex colored fan |
| 001CB8D8 | 00199080 | Colored triangle strip |
| 001CBA28 | 001991D0 | Colored line strip |
| 001CB4C8 | 00198C70 | Textured sprite |
| 001CB648 | 00198DF0 | Untextured sprite |

The payload-address helper initially has two candidates; agreeing caller targets select 002E1420. The ALPHA helper, nine panel callbacks and dispatcher have no complete DDS match under the current mask. DDS transfer is static evidence, not a DDS runtime claim.

Rolling evidence: `panel-draw-validation.json`, `panel-draw-interfaces.json`, `panel-draw-matches.json`, `panel-draw-transfer.json`, `panel-draw-abi.json` and `panel-draw-frontier.json`. Aggregate recovery is now **1,059 / 8,974 functions (11.801%)**, **605,210 comparisons** and **160,456 summed validated body bytes**; the last full comparison remains 413 functions / 462,684 cases. This batch is a focused comparison, not a new full-suite run.

The [current Message frame drawing graph](message-frame-draw-frontier.json) has **15 unrecovered bodies / 4,272 bytes**, five indirect-call sites and thirteen current source boundaries. Next is the actual submission path at **001CC2B8**, its state packet at **001CD270**, and the Message frame caller at **001D0930**. Panel submission calls the ordering-table callback at **OT+10**; its target must be established from actual initialization or runtime state. Both original OT records inspected in the ELF have zero callback words, so an arbitrary returning callback must not be substituted. Closing packet generation does not establish GS execution, correct rendered appearance, full frame/scheduler integration, complete assets/gameplay, PS2 runtime or a matching executable. Those remain outstanding.

Subsequent recovery: [font and Message frame drawing](message-frame-draw-findings.md) closes those fifteen bodies and establishes the ordering callbacks through the actual initializer. All 2,432 comparisons pass, including 128 connected frame-to-flush cases. The current frame graph stops at that source-current compared root. The preceding frontier paragraph records the state before this recovery; physical rendering remains outstanding.

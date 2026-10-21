# Native stock-selection renderer support

Nineteen complete original routines compile in `src/battle_panel_support.c` and
pass **4,224 original-instruction comparisons**. Their interfaces are saved in
the working Ghidra project, checked after reopening, and exported into the
current 8,980-function inventory. This closes the selected prerequisites beneath
the stock renderer; the complete renderer and action process remain pending.

The [validation report](battle-panel-support-validation.json) records 4,200
recognized body bytes, all **911 selected main instruction addresses** reached,
and 1,263,687 original steps. Current integrated recovery is **1,613/8,980
functions (17.962%)**, 234,480 recognized body bytes and 722,655 aggregate
comparisons. The aggregate includes earlier dependency and integration cases;
the last full run remains 413 functions /462,684 cases.

| Original entry | Recovered routine | Cases |
| --- | --- | ---: |
| `001ABC88` | `effColorMultiply` | 512 |
| `001C6160` | `ps2FontSetSize` | 128 |
| `001C7BA8` | `frSetFontColor` | 128 |
| `001CA298` | `ps2FontBuildDrawString` | 128 |
| `001CA430` | `ps2FontBuildPanelString` | 128 |
| `00279868` | `ps2BattlePanelSetPrimitive` | 128 |
| `00279980` | `ps2BattlePanelSetAlpha` | 128 |
| `00279A88` | `ps2BattlePanelDrawTexturedRect` | 128 |
| `00279C00` | `nbPanelBaseColorSet` | 128 |
| `0027A040` | `ps2BattlePanelDrawNumber` | 128 |
| `0027A0D8` | `ps2BattlePanelDrawName` | 128 |
| `0027A290` | `nbPanelHPColor` | 128 |
| `0027A318` | `nbPanelMPColor` | 128 |
| `0027A378` | `ps2BattlePanelDrawCursorGradient` | 128 |
| `0027FBA0` | `nbPanelStockSelectCtrl` | 1,152 |
| `002AF0F8` | `ps2DrawBuildColoredQuadPacket` | 128 |
| `002AF210` | `ps2DrawAppendColoredQuadPacket` | 128 |
| `002B9DD0` | `ps2PanelCreateTexturedSpritePacket` | 128 |
| `002C0060` | `sdfSinBits` | 512 |

## Original semantics retained

Color multiplication uses the original packed-byte expansion, integer-to-float
conversion, vector multiplication, float-to-integer conversion and packing.
Each channel is `(first * second) >> 7`, retaining its low byte without a 255
clamp. `551180` holds native ABGR; `551184` holds its reverse-byte text color.
The three color QMTC2 instructions transport full 128-bit GPR operands: 6,912
observed upper-word operands are consumed in order. These are architectural
inputs, not substituted function results. All 32 VU registers, ACC, retained
overflow bits and Q agree across 578,688 checked values and 23,040 original
vector instructions.

The font paths execute actual construction, cache lookup, measurement, drawing
and recycling dependencies. The draw-string path replaces only `FFFF` with
`8080`, keeping the original mixed single/two-byte traversal. Font-color updates
walk the live FRQ and TEXT links. Font-size positivity tests the complete signed
64-bit argument before storing the original word and byte fields.

Packet helpers retain raw tag operands, original stack-word loads, store order,
texture-before-sprite ordering and native ordering-table calls. The comparison
checks 512 ordering callbacks and 384 actual quad allocations, including the
cursor gradient's two real quad packets. The hosted allocator boundary selects
the actual recovered work allocator in these cases; the native implementation
retains the original function-pointer call.

Stock-selection input preserves the original frame gate, up/down/cancel/confirm
priority, cursor/scroll wrapping, gate-byte writes and signed table results.
Constructed cases include empty and negative counts, cursor/scroll edges,
repeat and trigger inputs, and simultaneous buttons. This does not establish
the entire renderer or gameplay stock-menu lifecycle.

HP/MP color helpers retain native halfword fields, percentage thresholds and
64 original BREAK7 observations for zero maxima. Trapped calls have no normal
return value; incidental V0 contents are excluded. The HP helper's own delayed
BREAK is unreachable after the unchanged dying predicate has already trapped
on the same zero maximum. All selected main addresses are nevertheless reached.

Sine retains native range reduction, folding, five polynomial coefficients and
COP1 operation order. All 512 cases preserve the original 28-byte coefficient
table at `54E758` before and after execution. The native comparison handler
checks 1,816 C.LT.S instructions and the final FCSR condition; tests include
ordinary radians, signed zero, subnormals and extreme raw words. Full FPU/VU
flags, timing and physical hardware behavior remain outside this value model.

## Unity and community research

Seven reviewed named Unity roles corroborate color multiplication, font color,
base color, HP/MP color, stock control and sine. Twelve other helpers retain
descriptive native aliases. HD mouse, sound and managed guards are excluded
from the PS2 recovery. The named HD sine has corresponding range reduction and
odd-polynomial structure; x86 floating-point behavior is not copied.

The [community evidence record](battle-panel-support-community.json) pins
[DDS source-unit research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md)
and [battle-table documentation](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
at revision `bec33411543cdc487bad9debdf758f0090a2242c`. They guide shared-engine
candidates and vocabulary; battle rewrites and profile-specific table layouts
prevent assuming direct transfer.

The [complete-span transfer check](battle-panel-support-transfer.json) resolves
three original DDS counterparts: Nocturne `002AF0F8` to DDS `002D6578`,
`002AF210` to `002D6690`, and `002B9DD0` to `002E1478`. Callee constraints
independently agree. Color and font-color bodies have multiple complete-span
candidates and remain ambiguous; the selected stock-control body has no complete
DDS match. No transfer is inferred solely from a shared name.

## Integration and remaining work

Another **9,598 existing comparisons** pass on the rebuilt host, recorded in the
[affected-regression report](battle-panel-support-regressions.json): frame drawing
2,432; panel drawing 3,360; action entry 1,997; action sequence 1,245; and unchanged
BF integration 564. Their original current captures are reused for these affected
C comparisons; this is not a new full-suite capture.

The [current renderer graph](battle-stock-renderer-frontier.json) has five
unresolved bodies /9,464 bytes: `0027AA40` (204), `0027AB10` (3,220),
`0027B7A8` (2,672), `0027FD18` (2,020), and `00282270` (1,348). Continue the
background/name/status row drawing, then the actual stock renderer and full
action process. Whole-program source recovery, original runtime scheduling,
physical rendering and a matching executable remain outstanding. Work and
rolling outputs are maintained in place, with no checkpoints or backups.

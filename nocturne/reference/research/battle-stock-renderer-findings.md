# Native stock and party rendering

Five complete bodies /9,464 recognized bytes are integrated in
[`src/battle_stock_renderer.c`](../src/battle_stock_renderer.c), with their native
interfaces saved in-place and independently reopened in the working Nocturne
Ghidra project. All five corrected-language exports are merged into the current
whole-program inventory. No checkpoints, project copies or capture copies were
created.

| PS2 RAM entry | Native role | Unity semantic lead |
|---|---|---|
| `0027AA40` | Empty party row background | Descriptive native alias; HD `nbPanelDrawPP0` adds an index and uses managed UI |
| `0027AB10` | Full party row, selected background, HP/MP trails, text and icons | `nbPanelProcess$$nbPanelDrawPP1` /`18238B210` |
| `0027B7A8` | Compact stock row and draw masks | `nbPanelProcess$$nbPanelDrawPP` /`18238C510` |
| `0027FD18` | Complete four-row stock selection presentation and party draw | `nbPanelProcess$$nbPanelStockSelect` /`1823950F0` |
| `00282270` | Party order, slide interpolation, damage flashes and shaking | `nbPanelProcess$$nbPanelPartyDraw` /`18238E090` |

The original target is USA `SLUS_209.11`, SHA-256
`a26e86e59cab447d9b1839ec11ab82b1557230bcc99746b78e3b5d4359dcc6ff`.
The table, opcode and ABI evidence is pinned in
[`battle-stock-renderer-interfaces.json`](battle-stock-renderer-interfaces.json).
The source recovers all seven arguments of `0027AB10`; the initial pseudocode
omitted its main-data argument. Native integer arithmetic narrows selected
coordinates and indexes at the actual instruction boundaries; the compact row's
selected argument is narrowed to32 bits, whereas the full party row tests its
complete64-bit argument.

## Original behavior

The party renderer searches the actual priority`03FA` process, traverses four
slots at main+0 with stride`F0`, and resolves signed16-bit formation/unit indexes
through main+`10`. Slot flags+`78` require both`01` and`40`. Twelve signed-byte
queue positions start at the signed cursor at main+`54`; duplicate queue entries
can overwrite an earlier assigned ordinal. Flags main+`60`/`08` suppress that
ordering pass. The queue's cursor`-1` prefix read remains native behavior.

Per-party animation state starts at`5753A0`, stride`18`: selected flag, slide,
previous HP, previous MP, HP flash and MP flash. Selection approaches slide16 by
one third of the remaining distance, with a minimum step of1; deselection applies
the corresponding native decrement and floor. Shaking uses two actual
`sdfGetRandInt(NULL,6)` calls per qualifying actor. HP/MP history and flash stores
run before the actual full row renderer, with no fabricated RNG or draw results.

The renderer's unit view is original work+unit*`EC`+`A50`: flags+4, name ID+8,
HP+`A`/max+`C`, MP+`E`/max+`10`, status+`12`. Color helpers receive that pointer+4.
Both trails retain native width arithmetic and zero-maximum BREAK7 behavior.
Full-party status drawing lets the last matching test win, so the lowest set
bit wins. Compact-row status drawing instead stops at its first match, with a
different ordered priority for bits`20` and`08`.

The compact row preserves independent draw-mask branches and the alternate MP
atlas at global`345D88` when its earlier HP view was omitted or zero. Frame-based
pulses retain native unsigned-word-to-float conversion, including the high-bit
halve/convert/double path. Actual original sine coefficients and operation order
are used.

The stock renderer calls the real pad controller, draws up to four original
`575400` unit entries, then draws the party beneath its second fade. Its globals
are counter`55120C`, slide`551210`, count`551214`, cursor`551218`, scroll`55121C`,
fade color`551204` and fade-enable byte`551208`. Original first/second fade behavior,
unsigned frame remainder25 and counter wrapping are preserved. Font construction,
formatting, drawing and recycling execute through recovered bodies. The native
party font handle at`551FDC` is included in the declared RAM comparison.

## Validation

[`battle-stock-renderer-validation.json`](battle-stock-renderer-validation.json)
passes832 original-instruction cases:128 empty rows,160 full party rows,272 compact
rows,136 stock renderers and136 complete party updates. Sixty-four cases observe
actual BREAK7 in native gauge or color dependencies; trapped calls do not compare
a normal return. Host trap observers discard only expired host-local text mappings
after the architectural exception, without changing game RAM or callee results.

All2,057 reachable main instruction addresses are reached. Twenty-two instructions
of an unaligned-copy fallback are unreachable because the fixed original source
`545320` is8-byte aligned. Six first-fade overflow-correction instructions are
unreachable because that positive-counter fade produces a scaled value in0..128.
The zero-divisor tests for constants3 and25 execute normally; only their BREAK7
delay paths are impossible. They are not excluded main instruction addresses.

The capture executes10,554,609 original steps. Full declared RAM, defined raw64
returns, Status, CPU primitives, FCSR condition and all32 VU registers plus ACC,
retained overflow and Q agree. It checks113,984 vector/ACC/Q values,263,220 native
vector instructions,78,966 observed upper-GPR color transport words,272 actual
quad allocator calls and23,433 ordering callbacks. All832 before/after pairs retain
the original UI table window, both local icon tables and sine/pulse coefficients.

The affected support provider and exception observers also pass all4,224 existing
[`battle-panel-support`](battle-panel-support-validation.json) cases on the rebuilt
host using its existing current capture. No new full-suite or physical gameplay
claim is made.

## Community and transfer evidence

The pinned [DDS source-unit research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md)
reports substantial battle-code rewrites. Its
[battle-table notes](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
provide related vocabulary rather than a Nocturne layout. Complete selected-span
comparison finds no DDS counterpart for these five bodies; see
[`battle-stock-renderer-transfer.json`](battle-stock-renderer-transfer.json).
Shared dependencies remain separately constrained transfer leads.

The [randomizer's original USA-build notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
state their file-offset basis and`FF000` RAM adjustment. Addresses above are RAM
addresses in this specific executable. Its static demon records are not substituted
for the renderer's live work records. Unity roles are separately reviewed in
[`battle-stock-renderer-matches.json`](battle-stock-renderer-matches.json); managed
UI objects, HD parameter additions and memory offsets are not copied into PS2 C.

The current [stock graph](battle-stock-renderer-frontier.json) has zero unresolved
direct bodies at compared boundaries. The broader action graph still has484
unresolved bodies /102,432 bytes. Continue the actual action process`00257CD0`,
remaining state callbacks and native message progression. Physical drawing,
complete invalid-input behavior, full floating-point flags and a matching complete
executable remain unproved.

# Native path evaluation and progression

Recovered **13 complete native routines / 2,320 recognized body bytes** in `src/path_evaluation.c` and `.h`. All **1,728 comparisons pass**, reaching every **529 main instruction addresses**. The original engine executes **276,534 steps**, including **13,896 vector/transport instructions**; **13,824 live vector lanes** are compared. Forty-eight cases construct actual splines and repeatedly advance them, with 920 prelude calls in total. All13 interfaces were saved in the working project, independently reopened and checked; current exports merge all13 without failures. The affected C builds with warnings treated as errors.

Integrated compiled recovery is **1,186 / 8,975 functions (13.214%)**, with **624,250 aggregate comparisons / 181,536 summed original body bytes**. The last full run remains413 functions /462,684 cases; 773 additional routines contribute161,566 focused cases. All90 focused reports reference unchanged current source. This is a focused result, not a new full-suite run or proof of physical PS2 execution.

## Native behavior retained

GetElement converts unsigned frame keys through the original shift/or/double path when bit31 is set. It selects `start <= frame < end`; missing intervals use segment `count-2` and weight1. Native store order is segment first, lower-key reload, inverse-weight store, then final multiplication. Backed aliases exercise segment/weight sharing a word or overwriting a key. Count-one resources retain the native negative previous-record reads; the HD position/FOV routines have different special cases.

Position uses stride12; scalar FOV uses stride4. Light interpolates ten float words in a40-byte RGBA/XYZ/XYZ record. Output aliases include the previous, next and backed negative light records. Native source loads occur between output stores. XYZ setters retain the inactive W lane, and original masked vector operations update live vf10/vf11; position finally multiplies W by zero. Absent light data zeros exactly40 bytes; absent position sets vf10 to vf0, preserving vf11.

Pause bit8 returns1 without progressing. Forward mode0 increments by1 while progress<maximum; reverse mode1 decrements by1 while0<progress. Loop bit20hex only resets at the terminal branch. There is no clamping of an overshoot. Other modes return1 unchanged. Ratio stores ratio*maximum. Pause/loop toggles preserve all unrelated flag bits.

Spline evaluation performs the native per-axis cubic Horner grouping. In the cubic branch W=1 is stored after loading the Z terms and before storing Z. Linear evaluation changes XYZ and leaves W untouched. Output aliases exercise points, next points, coefficient arrays and descriptor fields. Advancement caches segment/weight before sampling, reloads step/count afterward, uses strict1<weight, subtracts1 only once, and increments the signedLW segment lane. Its unsigned64 compare against signedLW count-1 determines whether index/weight reset. The constructor sequences exercise progression across segment boundaries using actual recovered allocation/coefficient code.

## Evidence and reference limits

Ten Unity semantic counterparts are reviewed from nonempty exports. LoopOn at18222F8B0 currently decompiles to six LOCK operations with nonsensical stores, so its name is only a lead; the native bit setter is recorded as a descriptive role. Spline evaluation/advancement are also native aliases.

The comparison executes original instructions with opcode-pinned COP1/VU instruction value adapters; it never hooks native function returns. All selected bodies and constructor dependencies are hashed. The scoped vector adapter supplies ADD/MUL/MOVE and128-bit transport/PROT3W/PEXEW values. Its lane permutations agree with [PCSX2 MMI.cpp](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/MMI.cpp). Branch delay arithmetic sites retain the emulator's original branch execution. Full declared RAM, defined returns, Status, CPU primitives, integer/FP callee saves and live vf10/vf11 agree. Private scratch registers, VU flags, FCSR exception flags, pipeline timing and physical hardware behavior remain outside this value comparison.

All **13 selected complete DDS spans resolve**, with five agreeing callee constraints. The two-instruction mode setter initially has nine identical candidates. Its equal contiguous32-byte setter/getter/ratio sequence, plus independently resolved getter and ratio neighbors, selects00117568. Static byte/call evidence establishes transfer leads; DDS runtime and a matching rebuilt PS2 executable are still unproved.

## Current outputs and remaining work

`analysis/path-evaluation-validation.json`, `-interfaces.json`, `-abi.json`, `-matches.json` and `-transfer.json` hold the current evidence. `tooling/recover_path_evaluation.py` regenerates the rolling fixtures and comparisons. No project copy, checkpoint, frozen source tree or duplicate capture was created.

`analysis/path-evaluation-next-frontier.json` records rotation00116528 through quaternion interpolation002C0AE0 and normalization002C04E8. That chain requires native ACC arithmetic and reciprocal-square-root Q values; the current simpler vector model is insufficient. Path object construction00116AD0 and camera setup001E7900 remain unpromoted. Full executable recovery, live camera movement, malformed/unbacked inputs, all production paths and matching-binary validation remain unfinished.

| PS2 entry | Function | Body bytes | DDS entry |
|---|---|---:|---|
| 00116058 | dds3PathGetElement | 340 | 00116B80 |
| 00116410 | dds3PathBasicControlGetPos | 276 | 00116F38 |
| 001165B0 | dds3PathBasicControlGetLight | 860 | 001170D8 |
| 00116910 | dds3PathBasicControlGetFovy | 128 | 00117438 |
| 00116998 | dds3PathBasicControlNextStep | 164 | 001174C0 |
| 00116A40 | dds3PathBasicControlAlterMode | 8 | 00117568 |
| 00116A50 | dds3PathBasicControlSetRatio | 16 | 00117578 |
| 00116A80 | dds3PathBasicPause | 16 | 001175A8 |
| 00116A90 | dds3PathBasicPauseOff | 20 | 001175B8 |
| 00116AA8 | dds3PathBasicLoopOn | 16 | 001175D0 |
| 00116AB8 | dds3PathBasicLoopOff | 20 | 001175E0 |
| 001B0A60 | ps2SplineEvaluate | 300 | 00192ED0 |
| 001B09C0 | ps2SplineAdvance | 156 | 00192E30 |

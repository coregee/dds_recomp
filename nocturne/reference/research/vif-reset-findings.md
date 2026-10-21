# Draw-thread VIF/GIF reset recovery

The full 104-byte routine at `002c8348` is recovered in `src/vif_reset.c` as
`ps2VifGifResetPath`. This is a descriptive alias, not a recovered SDK symbol.
The shared C build succeeds with MSVC C11 `/W4 /WX /O2`. All 64 focused
comparisons pass against the original instructions, covering all 26 instructions,
including the return delay-slot store. The working Ghidra interface was saved
in place, independently reopened and successfully re-exported.

The original writes 1 to VIF1 FBRST (`10003c10`) and 2 to VIF1 ERR
(`10003c20`), executes `SYNC 0`, reads `vc12`, ORs in `200` hex and writes
that control register, then executes `SYNC 16`. It loads a quadword from
`00529f30` and sends it to `10005000`, then loads the next quadword from
`00529f40` and sends it to the **same** FIFO address. Finally it writes 1 to
GIF CTRL (`10003000`) in the `JR` delay slot.

The recovered platform boundary preserves two 128-bit FIFO transactions.
Ghidra's language expands each `SQ` into four word writes, and its pseudocode
therefore resembles eight unrelated word assignments. That representation must
not become eight independent device transactions. PCSX2's
[VIF1 FIFO implementation](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/FiFo.cpp)
also handles each incoming quadword as one four-word VIF transfer.

Comparisons check all 4,144 declared bytes, ordered MMIO writes, synchronization
operands, the VU control write operand and both quadwords. Thirty-two cases
mutate the second input packet at the first FIFO boundary, confirming that the
second load happens after the first transfer. Eight cases use the executable's
actual static packet words. The other cases vary packet lanes and control values.
VU read values and write responses are external boundaries. A control write is
not assumed to retain its raw operand as readable state: PCSX2's
[CTC2 implementation](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/VU0.cpp)
masks the stored FBRST state and handles the reset-request bit separately.
Physical VU reset, FIFO consumption, timing and the parent draw thread are not
validated by these instruction/data-flow comparisons.

Read-only DDS comparison finds exactly one matching 104-byte body at
`002efef0`. Only the table-address constructor's LUI/ADDIU immediates (words
14 and 16) are masked. All other instructions, register choices, synchronization
constants and hardware addresses agree. Its table at `00398cb0` contains the
same eight words as Nocturne's `00529f30`:

`01000404 20000000 00000000 05000000 06000000 03000000 02000000 04000000`

This is a transferable static SDK-pattern candidate, with no DDS behavior or
runtime claim. Nocturne's direct callers are initialization `002aa1f0` and the
nonreturning draw thread `002a9ff8`. The reset removes one missing prerequisite
from both. The thread still requires original display setup, kernel scheduling
and screenshot/readback routines; a finite stub would not recover its behavior.

The related [Unity orchestration review](draw-unity-orchestration.json) establishes
that `fldDraw$$fldDrawGetOt` at `1811b9d90` shares a zero-return native body and
`itfPanel$$itfPnlDraw` at `1810d6760` shares an empty native body. Neither retains
the behavior needed to identify nontrivial PS2 ordering/drawing logic. The managed
ordering type contains only a `regFunc` delegate. `sdfDrawTagLinkOt` enters
generic delegate dispatch; its installed targets remain the useful next leads.

Current integrated recovery is **455 functions**, **53,320 summed body bytes**
and **476,060 aggregated comparisons**. The last full run remains 413 functions
and 462,684 cases; ten focused groups add 42 functions and 13,376 cases.
There are 258 reviewed HD counterparts, 194 descriptive PS2 aliases, 46 library
identities and 138 shared SMT patterns. Full or near-full source recovery,
actual PS2 runtime validation and matching-executable validation remain unfinished.

Evidence: `vif-reset-validation.json`, `vif-reset-interfaces.json`,
`vif-reset-abi.json`, `vif-reset-transfer.json` and the current `vif-reset/` capture.

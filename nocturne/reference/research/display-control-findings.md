# Display and draw-thread kernel prerequisites

Nine routines totaling 700 original bytes are now recovered in
`src/display_control.c`. The shared MSVC C11 `/W4 /WX /O2` build succeeds.
All 576 focused comparisons pass against original instructions, executing the
actual linked PutGsIMR and interrupt-disable/enable callees. The comparisons
observe 551 raw syscall boundaries, all 24 declared state/CSR bytes, ordered
loads/stores, Status, interrupt primitives and full 64-bit returns.

| PS2 entry | Recovered alias | Bytes |
| --- | --- | ---: |
| 002c81a8 | ps2GsSetDisplayMode | 400 |
| 002c8338 | ps2GsGetControlState | 12 |
| 002dbaa0 | ps2KernelSetGsCrt | 16 |
| 002dbba0 | ps2KernelRemoveIntcHandler | 16 |
| 002dbbf0 | ps2KernelDisableIntcRaw | 16 |
| 002dbc00 | ps2KernelEnableDmacRaw | 16 |
| 002dbdf0 | ps2KernelCancelWakeupThread | 16 |
| 002dc980 | ps2KernelDisableIntc | 104 |
| 002dcab8 | ps2KernelEnableDmac | 104 |

These are descriptive PS2 platform aliases and chosen raw EE verification
interfaces. Exact Unity counterparts, original SDK symbol spelling and source
typedefs are not established. Their interfaces were saved in the working Ghidra
project, independently reopened and all nine selected exports decompile.

Display setup narrows all four arguments with SLL16/SRA16. Mode 1 writes
`100` hex to the 64-bit GS CSR and returns. Mode 0 writes `200` hex, stores
the interlace halfword, reads the CSR, then stores video mode and the CSR's
eight-bit version. It calls the real PutGsIMR with `FF00`, loads the installed
flag, and stores whether the narrowed field argument is nonzero in the branch
delay slot. A nonzero flag causes real guarded DisableIntc(2), a **late**
sign-extended handler load, RemoveIntcHandler(2, handler), then zero stores to
handler and flag. Mode 5 updates the halfwords without reset or handler removal.
Both modes pass parity/low-eight-bits/parity to SetGsCrt. Field presence and
field parity differ, particularly for an argument of 2 or `8000` hex.

The state record starts at `00529f20`: four halfwords at 0/2/4/6, installed
word at 8 and handler word at 12. Its 16 bytes immediately precede the two
[reset packets](vif-reset-findings.md). Controlled kernel mutations change the
flag and handler during calls. The original and C agree on the flag decision
after PutGsIMR and the handler loaded after DisableIntc. Taking an early copy
of the record would change these behaviors.

The two guards save the entry Status interrupt-enable bit, execute the real
DI/SYNC16 loop if it was set, make their raw syscall, preserve the syscall's
complete V0, execute SYNC0 and call real EI according to **entry** Status.
Kernel-time Status changes do not replace that saved decision. Syscall outputs,
Status/state changes and CSR read values are supplied platform boundaries;
these tests do not execute the PS2 kernel or physical display. Initial enabled
DI fixtures use permitted contexts. Nonterminating unprivileged DI loops,
hardware timing, scheduling and full draw-thread behavior remain unproved.

The new shared-provider mode defaults to zero. The affected existing draw
platform and interrupt groups pass against their retained current captures:
3,328 + 3,584 cases. No old canonical C body was changed and no new full-suite
capture was made.

Read-only DDS comparison resolves all nine new routines plus three actual
prerequisites. The 400-byte display body uniquely matches `002efd50`. The
constant-state getter has 29 body-pattern candidates after masking its address
constructor; the display caller selects `002efee0`. Each guard initially has
four candidates, then its actual raw syscall callee distinguishes DisableIntc
at `0030b500` from EnableDmac at `0030b638`. The state getter constructs DDS
address `00398ca0`, exactly 16 bytes before the already matched reset packet
table `00398cb0`. Only call targets and the getter's two address immediates are
masked. These are static candidates; DDS source/runtime equivalence is unproved.

The [Unity moon movement lead](moon-movement-reference-lead.json) supplies the
next retained game-logic target: PS2 `001eac20` and named HD
`evtMoon$$evtMoonAddMove` at `1821a5bd0`. They share movement accumulation,
moon advancement, effect-clear calls and event/counter thresholds. The port
changes byte fields to integers and replaces a random 12/13 cycle-reset threshold
with fixed 12. This remains a lead pending original-body recovery and float ABI
review; no new HD identity is promoted here.

Current integrated recovery: **464 functions / 54,020 summed body bytes /
476,636 aggregated comparisons / 5.181% of recognized functions**. Eleven
focused groups add 51 functions and 13,952 cases to the unchanged last full
413-function / 462,684-case run. There are 258 reviewed HD counterparts,
203 descriptive PS2 aliases, 46 library identities and 141 shared SMT patterns.
Full or near-full recovery, runtime validation and matching binaries remain
unfinished.

Evidence: `display-control-validation.json`, `display-control-interfaces.json`,
`display-control-abi.json`, `display-control-transfer.json` and the one current
capture in `display-control/`.

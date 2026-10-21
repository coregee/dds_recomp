# DMA recovery

Four additional routines are integrated in `src/draw_dma.c`. The actual recovered
DLL compiles as C11 with `/W4 /WX /O2` and passes **1,024 focused comparisons**
against execution of the original PS2 instructions, 256 per function.
Annotations and raw register interfaces are saved in the existing working
Ghidra project. All four interfaces were checked after reopening; their selected
exports complete with zero failures and the recognized inventory remains 8,956.

| Original entry | Recovered routine | Body bytes |
| --- | --- | ---: |
| 002c9748 | ps2DmaWait | 112 |
| 002c9ee0 | ps2DmaStop | 152 |
| 002c9bd0 | ps2DmaSendChain | 104 |
| 002c9d70 | ps2DmaReceive | 124 |

This brings integrated recovery to **430 functions / 48,800 summed original
body bytes (4.80% of recognized functions)**. Evidence combines the last full
run, 413 functions and 462,684 cases, with seventeen integrated draw helpers
and 4,352 focused cases. The aggregate is **467,036 cases**, not a new full run.
There are 254 reviewed HD counterparts, 46 library identities, 173 descriptive
PS2 aliases and 122 recorded transfer patterns.

The focused comparison checks all 33,280 declared memory bytes, raw 64-bit stop
results, processor Status, real interrupt-helper counts and the order of
controller reads and stores. It includes zero through three busy reads, both
initial interrupt states, the FFFFFFFF address-store sentinel, high argument
lanes and selected channel/controller aliases. Original normalize and DI/EI
callees execute in the instruction probe; actual canonical callees execute in
the recovered DLL. Platform read-time values are supplied at individual loads.

Stop preserves the observable read at 1000e000, conditionally enables bit10000
through 1000f590, clears channel bit100 and restores the saved controller word.
Send and receive test the address register before reloading channel control.
The chain launch clears +20 and sets105 with maskFFFFFFF3; receive writes the
count's low word at +20 and sets100 with maskFFFFFFF2. These distinctions and
the protected stop sequence are recorded as two new transfer patterns.

The wait timeout is reconstructed but remains outside the executed fixture
domain. Its signed word countdown starts at 00ffffff and decrements in the busy
branch delay slot. Static recurrence review establishes that 16,777,217 busy
loads precede the first timeout. The diagnostic at 0054a8f0 is
`libdma: sync timeout\n`; the long timeout and original printf implementation
remain unexecuted. Physical DMA timing, asynchronous scheduling, arbitrary
register addresses, the complete draw consumer and matching PS2 binaries are
not established by these tests.

Current evidence: `draw-dma-validation.json`, `draw-dma-interfaces.json`,
`draw-dma-abi.json` and `ps2/whole-program/partial-export-summary.json`.
The existing small capture in `drafts/draw_dma/vectors.jsonl` is reused directly.
No project copy, checkpoint, source freeze or duplicate capture was created.

Continue with the draw consumer at002adb98, cleanup at002aadc8 and developer
console rendering at002bcfd0. [Console leads](dev-console-leads.md) correct the
earlier event-dispatch interpretation and distinguish Unity's ported text path
from the PS2 packet renderer.

# Battle and moon state

The reviewed ledger now connects battle setup, skill ownership, moon state, and negotiation HP requests. All addresses refer to SLUS_209.11. Source names qualified with `nbMainProcess_` avoid generic-name collisions. The moon-calculation disable helper uses a chosen source name and retains its anonymous Ghidra label because the HD native counterpart is protected.

## Battle setup

`0x002492E0` clears event bits `0xBF0..0xBFF`. Its HD counterpart has the same 16 iterations and clear-event call.

`0x002493A8` reads event predicates and modifies the process-data word at `+0x60`. HD modifies `+0x7C`; this difference does not establish the rest of the structure. `nbMainProcessData_PS2_prefix` models only the 100-byte prefix through that word. The full structure size is unproved.

| Event bit | Process flag |
|---|---:|
| `0xC04` | `0x00800000` |
| `0xC00` / `0xC01` / `0xC02` | `0x00020000` / `0x00010000` / `0x00040000` |
| `0xC03` | `0x00400000` |
| `0xC05` / `0xC06` / `0xC07` | `0x02000000` / `0x04000000` / `0x08000000` |
| `0xC0D` / `0xC10` / `0xC12` | `0x40000000` / `0x80000000` / `0x00008000` |

The `0xC04` mapping always runs. The remaining mappings run only when the signed word at `GP-0x594C = 0x0054E824` is nonzero; that branch also forces flag `0x01000000`. When the gate is zero, existing gated flags remain unchanged. HD removes this gate and retains the mask sequence, with some event IDs encoded by protection constants. No decoded value is assumed for those HD globals.

The comparison suite exercises all 2,048 event configurations with both gate states, for 4,096 comparisons, checking the entire test-unit backing region and global-work prefix. Initial flags vary, so the tests check clearing and preservation as well as setting.

## Moon controls

Global work has a status byte at `+0xA40`, raw phase byte at `+0xA41`, and a movement word at `+0xA44`. HD metadata names the corresponding managed fields `Stat`, `Age`, and float `MoveCnt`. The C view preserves movement bits until PS2 arithmetic establishes their full interpretation.

The folded getter at `0x001E9998` returns phase directly through eight and otherwise returns `8-(phase&7)`. `0x001E99C0` returns the raw phase. The setter at `0x001E99D0` stores the incoming low four bits and clears movement. This preserves PS2 behavior for negative arguments; HD uses signed remainder and can retain a negative value.

Calculation enable at `0x001E99E8` sets status bit1. Its PS2 disable helper at `0x001E9A00` clears bit1 and is reconstructed as `ps2MoonDisableCalc`; that alias is not a confirmed original symbol or reviewed HD pair. HD `evtDisableMoonCalc` at `0x1821A5580` has a protected native body.

Draw enable/disable at `0x001E9A18` / `0x001E9A38` set/clear status bit2 and force a separate alpha float to 1/0 at `GP-0x4A14 = 0x0054F75C`. The `Draw2` variants at `0x001E9A50` / `0x001E9A68` change only the status bit and preserve alpha. Each of these nine moon routines has 256 comparisons, covering all byte states and getter inputs, plus signed/wider setter values and exact alpha bits.

## Skill ownership and activation

`datCheckSyojiSkill` at `0x00243F40` scans the unit's skill count and inline 16-bit skills unless flag `0x20` selects eight descriptor skills. The descriptor skill address is `0x003497D6 + id*0x3C`. Race lookup at `0x00244470` reads `0x003497C4 + id*0x3C`; initialization reads level at `0x003497C5` and six parameters at `0x003497D0`. Together with the HD descriptor fields, these establish a table base of `0x003497C0`, skill offset `0x16`, and 60-byte stride. The C descriptor remains a partial view. The test backing span covers IDs0..255 and does not establish total table length.

Owned-skill lookup compares the supplied integer without truncating it to 16 bits. Party lookup at `0x00245638` checks physical slots0..15, requiring both flag1 and flag2 before calling ownership lookup. Battle activation at `0x0026A3D8` requires ownership, then folded moon eight for skill300 or zero for skill301; other owned skills succeed.

## Resource limits and negotiation

Base HP at `0x00242A88` computes `(level+parameter3)*6`. Base MP at `0x00242AE8` calls original software-double conversion, multiplication by1.5, and truncation on `2*(level+parameter2)`. Every possible unsigned-short level plus a clamped1..40 parameter produces an exactly represented integer, so recovered C computes `3*(level+parameter2)`. Both bases cap at999 unless flag `0x20` is set.

Maximum HP/MP at `0x00243C28` / `0x00243D28` add separate truncated10/20/30-percent bonuses for skills `0x122..124` / `0x125..127`, then apply the same cap. Combining percentages before division would alter rounding. The suite executes the original software-double helper instructions; it does not replace them with host math.

Negotiation HP request at `0x0026AD70` uses its third unit's maximum HP. Event8 clear selects percentage `14 + rand(8)`; event8 set selects `20 + rand(10)`. It multiplies and divides by100 using integer arithmetic, advances the default RNG, and leaves the unit unchanged. HD takes managed reference parameters and loads maximum HP before RNG; PS2 receives a direct third pointer and loads it after RNG.

These linked routines are compared through original calls to event bits, skill lookup, RNG, moon accessors and software-double helpers. No reconstructed battle or arithmetic helper is substituted into instruction execution. Hardware execution, whole-battle behavior and matching compilation remain unvalidated.

# Graphics submission and synchronization

Three console-renderer dependencies are now integrated in `src/graphics_sync.c`.
The recovered library compiles as C11 with `/W4 /WX /O2`; actual canonical C
passes **768 focused comparisons** against original PS2 instructions,256 per
routine. Saved interfaces independently reopen in the working Ghidra project;
three selected exports decompile with zero failures and8,956 functions remain.

| Original entry | Recovered alias | Body bytes |
| --- | --- | ---: |
| 002c9e70 | ps2DmaWaitOrStatus | 56 |
| 002c9c38 | ps2DmaSendNormal | 116 |
| 002c8898 | ps2GsSyncPath | 788 |

Current recovery is **439 functions /50,168 summed original body bytes (4.90%)**.
The last full comparison remains413 functions/462,684 cases. Four focused groups
add26 routines/6,656 cases, for **469,340 aggregated cases**, not a new full run.
Current ledgers have256 reviewed HD counterparts,46 library identities,
180 descriptive PS2 aliases and127 transfer patterns. These three are chosen
PS2 platform aliases; no exact Unity counterpart or original typedef is claimed.

Wait/status compares the entire64-bit mode register to1. Only that exact value
returns channel bit100 immediately; every other mode calls the real DMA wait
and returns0. Normal send calls actual normalize/wait helpers, tests the address
register at+10 againstFFFFFFFF, reloads control afterward, writes count at+20
and applies maskFFFFFFF3/flags101. It differs from both chain send and receive.

The graphics helper's nonzero mode reads five conditions in order and returns
independent flags1/2/4/8/10hex. Registers are10009000,1000a000,10003c00,VUvc13
and10003020; masks are100,100,1f000003,100 andc00. Tests cover all32 result masks,
including modes whose low word is zero and high word is nonzero. Blocking mode
checks the same five stages, retaining one shared counter rather than restarting
the timeout at each stage. Bounded fixtures exercise zero through three busy
reads per stage with unrelated word bits preserved.

The comparison checks all **37,376 declared memory bytes**, ordered controller
reads/stores, read-time VU control values, processor Status and raw results.
The original probe executes actual normalize and wait bodies. No game-function
entry is replaced with a high-level synchronization result. The CFC2 extension
operand is a register value, not a numeric register selector: the probe supplies
vc13 immediately before its original reads, then checks that the instruction
callback consumes that exact register/value. The used bit100 agrees with the
host's explicit control-read boundary. Physical VU interlock/timing is unproved.

The existing DMA test provider gained a lower graphics-register span and a larger
event capacity. Its original mappings remain unchanged. The four previously
integrated DMA helpers were rerun against their existing capture using the rebuilt
canonical library; all1,024 cases still pass. No duplicate capture was made.

Timeout behavior is reconstructed and statically reviewed, but not executed.
The counter starts0, is compared as a sign-extended word in an unsigned64 test
against01000000, and increments in every timeout-branch delay slot. In one
continuously busy stage,16,777,218 initial-plus-loop reads precede its first
timeout, and the increment leaves the same counter value at diagnostic entry.
Prior busy stages consume the same counter. Original messages identify DMA
channels1/2,VIF1,VU1 andGIF. The timeout emits its stage message, dumps ten
controller words and returns a sign-extended-1. The long wait and original printf
formatter remain unexecuted; the host diagnostic test binding rejects that path.

Hardware scheduling, arbitrary controller addresses, concurrent DMA/VU activity,
whole console rendering and matching PS2 executables remain unproved. Current
evidence is `graphics-sync-validation.json`, `graphics-sync-interfaces.json`,
`graphics-sync-abi.json` and one rolling capture/static review in `graphics-sync/`.
Changes are saved in place without checkpoints or source/project copies.

The next packet layer is002bcb40 (flush),002bcc10 (background),002bcd40 (glyph
cells),002bcee8 (double-buffer initialization) and002bcfd0 (list renderer).
Initialization additionally calls the unrecovered12-byte texture-register getter
002ab0c8: load the word pointer at record+28hex and return its qword at+20hex.
Keep that actual getter and channel-table call rather than substituting fixed
header values. The larger draw worker002adb98 and cleanup002aadc8 remain targets.

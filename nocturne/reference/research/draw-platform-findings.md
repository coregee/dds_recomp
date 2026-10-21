# Draw request publication and consumer support

Thirteen additional routines are integrated into the recovered library and saved
in `ghidra/working/Nocturne.gpr`. The actual canonical DLL passes **3,328 focused
original-instruction comparisons**, 256 per routine. Saved register interfaces
reopen correctly; all thirteen selected exports decompile successfully. No
checkpoint or backup copy was created.

This batch reached **426 tested routines / 48,308 original body bytes**, combining
the preceding full comparison (413 routines, 462,684 cases) with these thirteen
new routines. Its **466,012 cases are aggregated**, not a fresh full-suite run.
[Subsequent DMA integration](draw-dma-findings.md) brings current recovery to430
routines/467,036 aggregated cases. The recovery index checks the source associated
with each result.

| Original entry | Recovered routine | Body bytes |
| --- | --- | ---: |
| 002a8570 | ps2ReadDrawCounterWord | 16 |
| 002a8580 | ps2ReadDrawCounterDelta | 20 |
| 002ada68 | ps2DrawPublishRequest | 252 |
| 002a9f90 | ps2DrawPrepareFrameState | 52 |
| 002a9fc8 | ps2DrawCompleteFrameState | 48 |
| 002c9840 | ps2DmaNormalizeAddress | 40 |
| 002c98a0 | ps2DmaGetChannel | 40 |
| 002c96e8 | ps2GsSwapInterruptMask | 60 |
| 002c9728 | ps2GsReadInterruptMask | 28 |
| 002dbdc0 | ps2KernelSleepThread | 16 |
| 002dc120 | ps2KernelFlushCache | 16 |
| 002dc1c0 | ps2KernelGetGsIMR | 16 |
| 002dc1e0 | ps2KernelPutGsIMR | 16 |

The request publisher waits for the busy byte, records a wrapping counter delta,
disables interrupts, advances the three-slot ring and terminates the pre-draw
links before publishing the index and serial. Its only direct caller discards
V0, so the recovered source interface is void. Counter helpers retain their
observed low-word interface; support routines expose raw 64-bit EE integer values.
Those analysis interfaces are not claims about original source typedefs.

Frame preparation compares sign-extended bytes against an entire 64-bit input
and reloads the second byte after the first conditional write. Completion uses
word-wrapping GP indexing and writes its FF sentinel last. DMA normalization
examines the low-word high nibble but preserves all input bits on its other path;
the selected path ORs a sign-extended 80000000. Channel lookup compares an unsigned
64-bit index against ten and returns a sign-extended table word. The original
table at 00529f70 contains channels 10008000, 10009000, 1000a000, 1000b000,
1000b400, 1000c000, 1000c400, 1000c800, 1000d000 and 1000d400.

Kernel selectors are **hexadecimal** 32/64/70/71. The mask swap executes the real
get and put wrappers and retains the complete first return. Kernel implementation
and volatile read-time values are external boundaries, rather than replacements
for recovered game functions. Physical device timing and real PS2 execution
remain unvalidated.

Unity's named draw fields and three-object initializer support the queue/frame
interpretation. Its request and pre-draw representations do not provide these
original PS2 worker algorithms. No new exact HD identity is claimed. Four new
semantic transfer patterns are recorded in `shared-smt-signatures.tsv`; the DDS
body candidates remain static leads requiring their own verification.

The next four DMA routines are now integrated and pass **1,024 focused cases**.
They execute actual canonical normalize/DI/EI callees and compare ordered
register reads and writes, Status and complete declared memory. The wait's
sixteen-million-read timeout and original printf implementation remain unexecuted.
The original timeout message is `libdma: sync timeout\n` at 0054a8f0.

The main consumer at002adb98, cleanup at002aadc8 and console text rendering at
002bcfd0 remain the connected recovery target. The earlier event-dispatch label
was incorrect; [console leads](dev-console-leads.md) record the original glyph
packet evidence and Unity anchors. Existing raw pseudocode is not equivalent to
recovered, tested source for those functions.

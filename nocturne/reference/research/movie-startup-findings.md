# Movie IPU and decoder startup

Six complete routines in `src/movie_startup.c` add 1,100 recognized body bytes
and 384 passing original-instruction/C comparisons. Affected C compiles with
warnings treated as errors. Saved names and EE argument/result storage are
independently reopened; all six selected exports are merged into the current
inventory. The working project is saved in place.

| PS2 entry | Recovered routine | Body bytes | Unique DDS span |
| --- | --- | ---: | --- |
| 002dbb90 | ps2KernelAddIntcHandler2 | 16 | ambiguous |
| 002dbb20 | ps2KernelAddSbusHandler | 16 | 0030a6a0 |
| 002a8310 | ps2InterruptHandlerRegister | 228 | unresolved |
| 002cd9f0 | ps2MovieIpuResetInputDma | 100 | 002f55b0 |
| 002cda58 | ps2MovieIpuInitialize | 568 | 002f5618 |
| 002c4f80 | ps2MovieDecoderStartup | 172 | unresolved |

Registration selects INTC for kind 0, DMAC for kind 1 and SBUS for kind 2.
INTC/DMAC wrappers pass four full-width EE values; SBUS consumes two. These
syscall names and argument counts agree with PS2SDK's
[selectors](https://github.com/ps2dev/ps2sdk/blob/master/ee/kernel/include/syscallnr.h)
and [kernel declarations](https://github.com/ps2dev/ps2sdk/blob/master/ee/kernel/include/kernel.h).
Original wrappers and callers establish this executable's actual behavior.
Registration allocates a real 16-byte staging/pool node containing
`[previous head, kind, cause, low kernel handler ID]`, prepends it to 00551820,
and returns the sign-extended low pointer. Kernel results remain full-width
until the original low-word stores. Other kinds enter the existing fatal spin.

Input DMA reset unconditionally disables interrupts, reads live DMAE 1000f520
and sets bit 0x10000 through 1000f590, writes the requested low control word
to 1000b400, reads DMAE again and clears that bit through 1000f590. It enables
interrupts unconditionally at its tail and returns that result. The two DMAE
reads are independently supplied inputs in comparisons.

IPU initialization reads the original 112-byte table at 0052baa0..0052bb0f.
Ten full 128-bit quadwords reach input FIFO 10007010, selecting table offsets
`0,16,32,48,64,64,64,64,80,96`. After eight transfers it issues commands
0x50000000 and 0x58000000; the last two transfers precede 0x60000000 and
0x90000000. Reset/control 0x40000000 and command zero surround this sequence.
Eight busy-poll groups retain original ordering. Finite busy streams exercise
retries; selected cases perturb live table bytes to check actual table reads.

Startup initializes IPU, issues command 0x90000000 and clears owned head
00552148 and active decoder 00552154. It registers DMAC channels 3 and 4 with
callbacks 002c4b10 and 002c4b40, next -1 and argument zero, saves nodes at
0055214c/00552150, and enables both channels. The real thread constructor builds
entry 002c4a40, stack 00593f80, size 0x800, GP 00554170, priority 0x46 and
attribute zero. Startup stores the low thread ID at 00552164 and passes the
full ID to StartThread with argument zero; it returns the full StartThread result.

All 384 cases agree on declared RAM, defined full-width results, Status and
ordered kernel, interrupt and MMIO observations. They execute 60,454 original
steps, 26,006 trace words and 128 MMI instructions through real memory and
thread-descriptor dependencies. An independent table check verifies all 1,280
FIFO quadwords, registration-list fields and thread packets. Game/library
callees execute; kernel results and incoming hardware values are external.
Affected standalone display and frame groups also pass 576 cases each.

Coverage reaches 234 of 239 recognized non-delay root addresses. All IPU and
startup root addresses are reached. Untested addresses 002a8360, 002a8370,
002a83a8, 002a83ac and 002a83b4 belong to the invalid-kind fatal path,
including private stack/FPU state. Physical FIFO/IPU/DMA, cache coherence and
scheduler behavior are unverified. The created thread does not execute during
these comparisons. Actual playback and a matching executable remain unfinished.

Three complete DDS bodies resolve with three agreeing callee links. The INTC
wrapper retains two identical candidates; registration and startup have no
complete match under the current mask. These are static findings, not DDS
execution proof. No equivalent Unity native startup body is identified;
this platform path is recovered from original PS2 instructions within the
movie pipeline anchored by the HD reference.

Current compiled recovery is 808/8,956 functions (9.02%), 573,591 aggregated
comparisons and 130,080 summed recognized body bytes. The last full run remains
413/462,684; 395 additional routines contribute 110,907 focused cases. This
is focused evidence, not a new full run. Continue preloaded IPU 002c4080/002c3cc8
and the connected upload-chain consumer.

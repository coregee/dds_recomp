# Preloaded IPU movie path

Four complete routines in `src/movie_preloaded.c` add 572 recognized body bytes
and 256 passing original-instruction/C comparisons. All 122 recognized non-delay
root instruction addresses are reached. Affected C compiles with warnings treated
as errors. Names and EE interfaces are saved in the working Ghidra project,
independently reopened, and four selected exports merged into the current inventory.

| PS2 entry | Recovered routine | Body bytes | Unique DDS span |
| --- | --- | ---: | --- |
| 002c3cc8 | ps2MovieDecoderBuildInputChain | 216 | 002eb578 |
| 002c4080 | ps2MovieDecoderInitializePreloaded | 152 | 002eb930 |
| 002c4e78 | ps2MovieDecoderPreloadedCreate | 56 | 002ec748 |
| 002c4eb0 | ps2MovieDecoderPreloadedFromTexture | 148 | 002ec780 |

The input-chain builder rounds the low length word up to 16 bytes with wrapping
addition, performs the original signed division to allocate the tag array, and
stores its pointer at decoder+76. It masks the initial payload address to 28 bits,
splits at 0xFFF00 bytes per tag, writes REF type 3 for intermediate tags and REFE
type 0 for the final tag, and clears each tag's second doubleword. The high word
holds the payload address and the low 16 bits hold QWC. Address increments retain
the original low-word arithmetic. The real FlushCache(0) wrapper executes at the tail.

A rounded zero length still executes the original do-while body: zero-size pool
allocation is followed by one zero-QWC terminal tag. The source preserves this
edge rather than introducing a new early return. Cases cover lengths 0/1/15/16/17,
chunk boundaries, wrapped zero lengths, raw64 lanes and 64/65/1024/1025 tag
allocations. The 65-tag case crosses the staging allocator's 1,024-byte pool/heap
threshold. Negative allocation requests and numerator sign-overflow cases remain
unverified. The constant divisor is nonzero; its compiler BREAK delay slot is
structurally unreachable and excluded from the non-delay coverage count.

Preloaded initialization calls the actual decoder clear, reads width/header+8,
height/+10 and frame count/+12 into decoder+60/+62/+64, and allocates both CPU
frame buffers. Image+16 and byte length-16 feed the input chain. Actual FIFO append
and schedule/start run under the original conditional interrupt restoration.
The preloaded mode differs from streaming: clear leaves decoder+12 zero, so input
DMA uses the complete chain at decoder+76 instead of the streaming ring.

Creation then writes the supplied display address at decoder+52 and appends the
decoder to the actual owned list. The order matters: this store and list insertion
follow the initial scheduling call. Empty, one-node and two-node owned lists are
tested alongside empty and populated scheduling queues and an already active
decoder. No allocator, list, scheduling or other game/library return is substituted.

The texture entry copies all four configuration bytes, including unaligned source
addresses. Texture format byte +26 changes the copied first byte to zero for
format 0 or one for format 2; other values preserve it. The actual texture base
getter supplies the display address through texture+16's extent and extent+12.
Configuration residues 0..3 and formats 0/1/2/19/255 are tested, with independent
checks of the resulting decoder mode, retained configuration bytes, display address
and owned-list links. Its private four-byte host configuration is relocated only
for address resolution; original stack instructions execute in the comparison.

All declared RAM, Status and ordered kernel/interrupt/MMIO observations agree.
The 256 cases execute 393,781 original steps and 27,096 trace words. Independent
checks verify every word of 4,724 DMA tags, exactly one FlushCache(0) per call,
and 12 header observations across the four shipped ALPHA/E500_002/E731/G_OVER
IPU files. Actual game/library dependencies execute; kernel results and incoming
finite MMIO sequences are external. Supplied headers do not establish that the
complete media payload was decoded. Physical cache coherence, IPU/DMA execution,
scheduler behavior, malformed images, exhaustion and a matching binary remain
unverified. The affected startup group also passes its 384 cases after the original
instruction probe gains the FlushCache syscall boundary.

Four complete DDS spans resolve with 12 agreeing callee links, including two
links inside the existing frame-allocation dependency. DDS queue append 002eb3f0,
owned-list append 002eb490 and scheduler 002ec230 are caller-derived leads;
they have no complete-span match under the current mask and are not forced into
the resolved map. Static DDS findings are not DDS execution proof.

The HD reference's `mviManager$$create_movieobj` at 182814360 configures
Unity VideoPlayer render mode, target texture, audio routing and clip before
Prepare/Play. It provides a higher-level movie-system anchor, not the original
PS2 chain/header/IRQ implementation. No exact HD counterparts are added for these
four platform routines. The existing named manager counterparts remain the
semantic bridge to the HD release.

Current recovery is 812/8,956 recognized functions (9.07%), 573,847 aggregated
comparisons and 130,652 summed recognized body bytes. The last full run remains
413/462,684; 399 additional routines contribute 111,163 focused cases. This is
focused evidence, not a new full-suite run. Continue handler removal/shutdown
and connected movie upload/cleanup integration; cleanup 002aadc8 already has
recovered source, so the remaining work is integration rather than rediscovery.

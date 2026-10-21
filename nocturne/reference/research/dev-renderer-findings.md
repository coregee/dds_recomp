# Glyph cells and console list renderer

Two PS2 bodies are now integrated in `src/dev_renderer.c`, compile as C11 with
MSVC `/W4 /WX /O2`, and pass **1,024 comparisons against original instructions**,
512 per routine. Saved working-project interfaces independently reopen, and two
selected exports decompile with zero failures. The original probe and canonical
C execute actual initializer, background, finalizer, flush, DMA, GS-sync, texture
getter and channel lookup bodies. No game-function callback supplies their results.

| Nocturne entry | Chosen alias | Original bytes | Static DDS candidate |
| --- | --- | ---: | --- |
| 002bcd40 | ps2DevRenderGlyphCells | 424 | 002e4428 |
| 002bcfd0 | ps2DevRenderConsoleList | 104 | 002e46b8 |

Current recovery is **445 /8,956 recognized routines (4.97%)**,51,452 summed
original body bytes and **471,388 aggregated comparisons**. The last full run
remains413/462,684; six focused groups add32 routines/8,704 cases. This is not a
new full run. Ledgers contain256 reviewed HD counterparts,46 library identities,
186 descriptive PS2 aliases and132 transfer patterns. These two are chosen
PS2 aliases; exact Unity identity, original symbol spelling and typedefs remain
unclaimed. The reviewed HD `sdfDevCons$$sdfDevVprintf` body1825e44f0 uses managed
`System_String__Format` and `TextManager__Draw`, rather than this PS2 packet path.

Glyph rendering skips flag1 nodes, selects line height60/c0hex from flag4, then
reloads flags before the optional actual background call. It retains the loaded
glyph pointer, buffer current/base and sign-extended word advance. Character and
attribute are bytes; characters below20hex emit no record but still advance the
coordinates and counters. Every emitted cell calls actual flush if signed word
capacity is insufficient, reloads current/base, loads UV and color before stores,
then writes five qwords. UV+00c000c0 and both per-cell coordinate increments are
64-bit; buffer pointers and row y wrap as words. Width is loaded after every cell
and height after every row, preserving signed-halfword comparison and aliases.

List rendering reads global5518f8 before allocating a1080hex frame, initializes
the handle at frame+1040 with buffer frame+30 andsize1000, reloads global head,
renders each node, loads its next pointer after rendering, and performs the actual
final flush. The host frame binding relocates those addresses instead of replacing
the list or packets. With original entrySP0064f000, frame is0064df80, handle0064efc0
and uncached packet buffer3064dfb0. Exact resulting DMA addresses are compared.
The binding tracks entry/leave and returns to zero depth for every case, including
empty lists. Future callers with a different SP require their own binding context.

Standalone glyph cases compare all **61,476 scoped memory bytes**; list cases
compare **61,508**, including its32-byte handle and4096-byte packet buffer. The
extra handle region overlaps register saves during standalone glyph execution,
so its captured original bytes are retained but excluded from that entry's logical
memory comparison. It is fully compared for list entry. Other original ABI save
and temporary stack bytes are outside the logical-memory scope. GPR/GP/SP/RA
preservation checks still run independently in the original probe.

Tests include448 active/64 disabled glyph cases and384 populated/128 empty lists,
one through three ordinary initial nodes, background/scale flags, skipped/control
characters, raw argument high lanes and word-coordinate wrapping. Original capture
executes4,044 standalone and2,841 list glyph stores. There are34 cases with two
nonempty flushes, exercising actual packet finalization and buffer swaps. Thirty-two
alias cases deliberately change dimensions to1/1; list cases also overwrite the
next link with zero and verify only one node was rendered. Other fixtures overlap
packet/glyph-stream or packet/lookup-table storage. Synthetic backed byte indices
do not establish a256-entry semantic color/font domain in the original game.

Controller/VU values are generated at actual original read instructions and
recorded for replay against canonical C. DMA/GS waits receive bounded ready values.
The comparison checks their ordered IO/SYNC0 trace, Status, VU13, frame lifetime and
full scoped memory. Separately backed uncached memory is not a physical alias model;
SYNC ordering, DMA copying, concurrent hardware timing and physical text output
remain unproved. Nonpositive active dimensions would require enormous wrapped
loops and are not run; disabled nodes cover negative dimensions without reading
cells. Whole draw-consumer integration, PS2 runtime and matching executable remain
unverified.

The console address provider gained the renderer's handle/buffer relocation.
Six prior console helpers pass1,536 comparisons and four prior packet dependencies
pass1,024 comparisons again with the rebuilt DLL and their existing original
captures. New evidence is one rolling `dev-renderer/` capture, validation/interface/
ABI reports, and `dev-renderer-transfer.json`; no checkpoints or copies were made.

The read-only DDS comparison now has seven unique console/texture body candidates
and **nine agreeing call constraints**. DDS glyph differs in seven instruction
words: two JAL targets and five explicit table-address LUI/ADDIU immediates at
word indices56,64,66,69,70. Only those table immediates are masked; all other
constants, registers, branch offsets and instructions agree. Its96 glyph UV words
at398660 match Nocturne529900 exactly;15 colors at3987e0 match529a80 exactly,
444 table bytes in total. Both calls connect to the independently matched DDS
background/flush bodies. The list candidate calls independently matched init,
glyph and flush bodies. DDS C/runtime validation and original names are unclaimed.

Next recover draw cleanup002aadc8 and its interrupt wake chain, then the larger
consumer002adb98. `draw-cleanup-next-dependencies.json` pins seven still-unrecovered
dependencies totaling272 original bytes: ordered record reset002aad88, interrupt
callback002aada0, wake dispatcher002dcd50, and four syscall wrappers002dbde0/
002dbed0/002dbbc0/002dbbd0. The wake queue indexes its old cursor masked1ff,
writes masked_index+1 (retaining200 at the last slot), then writes the byte pair
at queue+8+2*old_masked_index. Do not use the next index for the pair or mask the
stored increment. Self/current-thread equality and the unsigned100 limit consume
full64 values. The queue uses59b178, enable word52c2ac and signal handle59b170.
This next-dependency evidence is static review, not yet recovered/tested C.

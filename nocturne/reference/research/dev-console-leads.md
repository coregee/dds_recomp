# Developer console frontier

Six source leaves below are now integrated and pass1,536 focused cases; the two
print setters are reviewed HD counterparts. See [source recovery](dev-console-findings.md)
for current evidence, interfaces and DDS transfer leads. The list renderer remains
unrecovered.

The earlier "event dispatch" description of **002bcfd0** was incorrect.
Its PS2 callees build text glyph packets and submit them to the graphics DMA
channel. The current interpretation is developer-console text rendering; this
is a static identification, not newly recovered or tested C.

002bcfd0 walks the list rooted at5518f8, initializes a 4096-byte local double
buffer through002bcee8, draws each node through002bcd40, then flushes through
002bcb40. Node+4 is loaded after drawing each node. The initializer reloads the
list head before traversal, so that reload must remain in the recovered code.

002bcd40 reads two bytes per cell: a character and an attribute. Characters
below20hex produce no glyph packet. Printable cells emit five 64-bit words,
advance horizontal coordinates byC0hex and use60/C0hex row spacing according
to flag4. Character32 starts the UV table at529900; the actual load expression
is529880+character*4. Attributes use the word table at529a80. Flag1 suppresses
drawing; flag2 invokes the background rectangle builder002bcc10. Counts at
node+0c/+0e are signed halfwords and are read during the loops. Nonpositive
counts are not a valid terminating fixture domain for those increment-first
loops. Original load/write ordering and aliases need preservation.

The Unity dump names `sdfDevCons`, `devConsTop`, `alreadyInitDevCons`,
`sdfDebugFontHandle` and `sdfDevConsColorTable`. Its `sdfDevPrintCB_t` has x, y,
z and attr at managed offsets10/14/18/1c. Two nearby PS2 helpers are strong
counterpart leads:

| PS2 entry | Unity method / native address | Retained behavior |
| --- | --- | --- |
| 002bd300 | sdfDevCons$$sdfDevSetPrintAttr /1825e4340 | Read the indexed color-table word and store the print control's attr field. PS2 field+0c maps to managed+1c. |
| 002bd318 | sdfDevCons$$sdfDevSetPrintCB /1825e43e0 | Store x/y/z and dispatch to the attribute setter. PS2 fields0/4/8 map to managed10/14/18. The fifth original argument arrives in t0. |

These are now in the reviewed counterpart ledger and compiled C. Their raw
interfaces retain PS2 indexing, argument lanes and backed pointer behavior.
PS2 writes x, then z, then y before its tail call. Unity uses x/y/z
order and checks managed null/array bounds. Those differences matter to aliases
and invalid inputs. The HD initializer creates a15-entry color array; that is
not evidence that PS2 unchecked indexing is safe outside the corresponding table.

The retained native body of `sdfDevVprintf` at1825e44f0 now formats a managed
string and calls `TextManager.Draw`, with float color and coordinate conversion.
It returns null. The PS2 variadic wrapper002bd220 calls002bd038, which builds
graphics packets through the same character table. This is a useful subsystem
anchor; it does not give an exact counterpart for the PS2 list renderer or its
DMA flush. Unity can accelerate names and interpretation, while the removed
PS2 platform path still needs instruction-based reconstruction.

The two setters and packet finalizer002bcad0 are now integrated with unlink,
clear and scroll helpers. The finalizer performs a signed word
calculation, rounds odd word counts to packet alignment, divides by5 and writes
the tag/register descriptors. Test negative count bits and handle/packet aliases;
do not replace the signed quotient or its sign-extended OR with an unsigned
packet-count assumption. Larger dependencies are002bcc10/002bcd40/002bcee8,
normal DMA send002c9c38, wait/status002c9e70 and graphics sync002c8898.

Sources are the current PS2 assembly exports, `pc/il2cpp/dump.cs` around the
`sdfDevCons` and `sdfDevPrintCB_t` declarations, and native corpus bodies
1825e3fc0/1825e4340/1825e43e0/1825e44f0. Compiled recovery counts cover the six
integrated leaves; the larger packet renderer and variadic printf path remain
static leads.

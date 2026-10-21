# Console packet dependencies

Four original PS2 functions are integrated in `src/dev_packets.c`, compiled as
C11 with `/W4 /WX /O2`, and pass **1,024 original-instruction comparisons**,
256 per function. Interfaces were saved directly in the working Ghidra project,
independently reopened, and four selected exports completed with zero failures.

| Nocturne entry | Chosen alias | Original bytes | Static DDS candidate |
| --- | --- | ---: | --- |
| 002ab0c8 | ps2TextureGetRegister | 12 | 002d2468 |
| 002bcb40 | ps2DevFlushPackets | 208 | 002e4228 |
| 002bcc10 | ps2DevBackgroundPacket | 304 | 002e42f8 |
| 002bcee8 | ps2DevInitializePackets | 232 | 002e45d0 |

These add 756 original body bytes. Current compiled/instruction-tested recovery
is **443 /8,956 recognized functions (4.95%)**, 50,924 summed original body bytes
and **470,364 aggregated comparisons**. The last full run remains 413/462,684;
five focused groups add 30 functions/7,680 cases. This is not a new full run.
There are 256 reviewed HD counterparts,46 library identities,184 descriptive
PS2 aliases and130 documented transfer patterns. These four names are chosen
PS2 aliases; no exact Unity counterpart or original typedef is established.

Flush executes the actual recovered packet finalizer. It caches the wrapped
segment/base delta, returns without submitting if its signed shift by three is
zero, waits through the actual DMA wait/status routine, sets control bit40hex,
executes a SYNC0 value boundary, and calls actual normal DMA send. The base is
loaded after synchronization and the submitted count is the cached word delta
shifted arithmetically by four. It writes the halfword toggle before reading the
selected buffer pointer, updates base/current/segment in original order, and
tail-calls actual five-stage graphics synchronization. Callers ignore incidental
V0; the chosen source interface is void.

Background also uses actual finalizer and flush bodies. It compares signed word
capacity with wrapped segment-base+80hex. Signed-halfword width/height and
unsigned x/y/line height feed packed coordinates; flag4 selects the original
vertical offsets. Coordinate operations wrap as32-bit words and then zero-extend
to packet qwords. Handle updates precede packet writes, which matters when packet
and node storage overlap. Width/height extremes, both flags, fitting and flushing
paths, and packet/node aliases are represented in the fixtures.

Initialization constructs an uncached buffer address by masking its low28 bits
and setting30000000. Its size halving is a signed word operation, including odd
and negative raw words. Ordered handle writes happen before the original global
texture lookup. The actual getter reads a pointer at texture+28hex, then its raw
qword at record+20hex. The initializer loads that value before writing the header
and calls actual channel lookup2 after the header writes. Header/handle aliases
and raw high argument lanes are checked.

The original capture and canonical C compare all **57,380 declared memory bytes**,
controller read/store traces, read-time VU13 values, processor Status, raw getter
results and SYNC0 counts and positions in the controller trace. The original probe executes every game/library callee
above; none is replaced with a high-level result. Its instruction callback accepts
the actual SYNC0 operand. The earlier SYNC16-specific registration cannot be
overridden by registering a second callback of the same name, so this focused
probe registers only its required SYNC0 and CFC2 boundaries.

Host channel lookup retains a separate table binding. These fixtures copy and
check the disjoint channel table against the original-address table span, and do
not claim table-alias behavior. The uncached buffer span is independently backed;
physical cached/uncached aliasing and DMA copying are not modeled. Synchronization
and read-time status values are controlled external boundaries, not proof of
hardware scheduling. Long timeouts, original diagnostic formatter, whole renderer,
PS2 runtime and matching executable remain unverified.

The console address provider gained the uncached buffer range. Its previous
regions are unchanged. All six earlier console helpers pass their1,536 comparisons
again with the rebuilt canonical DLL and existing original capture. No duplicate
capture or checkpoint was created.

`dev-packets-transfer.json` records a read-only DDS binary comparison. Each of
the four functions and finalizer002bcad0 has one candidate in executable loaded
ranges. All instruction words agree except explicitly masked J/JAL targets and
the initializer's GP-relative LW immediate; constants, registers and relative
branches remain exact. Finalizer maps to DDS002e41b8. Four independent call
constraints agree: flush→finalizer, background→finalizer/flush, initialize→getter.
The getter's three words agree exactly. These are static body/call leads, not DDS
runtime/C validation, annotations or recovered original names. No uniform address
displacement is assumed.

Evidence is `dev-packets-validation.json`, `dev-packets-interfaces.json`,
`dev-packets-abi.json`, `dev-packets-transfer.json`, and one rolling capture in
`dev-packets/`. Three transfer patterns describe the getter, double-buffer
initialization/submission, and packed background sprite construction.

Continue through glyph cells002bcd40 and list renderer002bcfd0. Glyph loops must
retain late signed width/height loads after packet writes, per-cell64-bit coordinate
increments and actual overflow flushes. The list renderer's stack-local handle
and4096-byte buffer need an explicit original-address relocation when comparing
DMA addresses. Larger consumer002adb98 and cleanup002aadc8 remain unrecovered.

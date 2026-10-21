# TMX construction, image transfer and GIF/DMA upload queue

Seven complete PS2 routines are integrated in `src/texture_upload.c`, adding
1,476 summed original body bytes and2,304 passing original-instruction/C cases.
The source compiles with MSVC C11 `/W4 /WX /O2`; raw interfaces are saved in
`ghidra/working/Nocturne.gpr`, independently reopened and exported in place.
No checkpoints or project/source/capture backups were created.

| Entry | Recovered role | Cases |
| --- | --- | ---: |
|002aa980|Wrapped image QWC calculation and58-entry format table|512|
|002aa9e0|Complete GIF/VIF/DMA packet builder and queued chain insertion|512|
|002ab1a8|Copy/reference image transfer with actual pool/handle ownership|512|
|002ab2b0|Palette geometry wrapper and actual image-transfer tail|256|
|002abc90|Full TMX descriptor, palette, mip transfers and register cache|256|
|002abe08|Copy-mode TMX wrapper|128|
|002abe20|Reference-mode TMX wrapper|128|

Original execution and compiled C both use the actual recovered VRAM,
descriptor, pool, memory-handle, memcpy and texture register-builder bodies.
All320,924 bytes of declared ordinary RAM, meaningful raw V0, Status and CPU
primitive counts are compared per case. The saved EE callee registers and
GP/SP/RA are checked. There are2,584 actual queue executions and15,504 checked
semaphore operand/result trace words. Kernel syscall values and CPU primitives
use existing explicit models; no game function is intercepted.

The image helper's24-byte stack work record leaves handle+4 unassigned in pool
and reference modes. The queue nevertheless copies it into packet metadata+8.
The comparison captures that ambient word at each actual image entry and supplies
it to the source as an explicit raw stack operand input:2,072 words total. Handle
ownership mode1 overwrites the word with its actual allocation. Modes0/2 retain
it. This models the original observable metadata without inventing a zero or
reading an indeterminate C variable. It does not establish the stack layout of
a newly compiled PS2 program. Captured stack operands are not callback/function
returns, fabricated handles or a replacement upload implementation.

QWC uses wrapping32-bit multiplication and arithmetic shift7. Its format input
loses high lanes through ADDIU before range/switch selection. Palette/image
transfer computes bytes as QWC<<4, then copies through the pool for signed
bytes<1025, or allocates/acquires a memory handle for larger sizes. Raw64 nonzero
reference mode bypasses copying. Ownership bytes are2/1/0 respectively. Forward
copying, negative initial counts on direct paths and later16-bit queue dimension
truncation are preserved. Seventy-five zero-byte source0 cases verify the original no-access copy path.
Huge or negative copy counts are not executed.

The queue allocates the original rounded packet demand, builds BITBLT/TRXPOS/
TRXREG/TRXDIR data and emits a do-loop of GIF/VIF/DMA REF chunks capped at0x7ff0
QWC. Source DMA addresses start masked to28 bits and subsequent increments wrap32.
Tests include zero QWC, one/multiple chunks, signed negative QWC with backed
overwrites, pitch0 normalization, old packet tail/DMA tag combinations and64
cases where the input work record aliases the newly allocated output packet.
Load/store stages are retained so those aliases match the original behavior.
Semaphore return values do not condition queue insertion in the original.

TMX creation uses signed16 dimensions and the real mip constructor. It copies
header metadata, computes data at header+(flags&f0)+64, allocates/copies retained
palette staging when count is nonzero, transfers one palette image, then all
pixel mip levels through the real queue before building the context0 register
cache. It retains the original unchecked failed-constructor path. This is the
complete routine, rather than a caller supplied with synthetic texture handles.

The six real `moon.LB` records are checked in144 original/C cases across copy
and reference modes. Every record creates a128x64 descriptor, palette staging,
two linked upload nodes and a register cache. Five format19 records contain
64-byte header +1,024 palette bytes +8,192 pixel bytes =9,280 bytes. The format20
record at0x4880 contains64+64+4,096 =4,224 bytes. Palette and pixel source bytes
match the asset exactly. Copy mode has pool palette ownership2 and handle pixel
ownership1; reference mode retains asset pointers and ownership0. These are
CPU-model results, not observed PS2 upload/rendering.

Unity retains texture field names, but its native `sdfTexSetEx`/`sdfTexSet` bodies
here omit texture decoding and only allocate managed handles. Their unused
arguments cannot resolve which PS2 default wrapper is represented. Managed
`sdfPacBin.GetNextPos` corroborates64-byte record navigation; `GetTmxIndex` is
code/index lookup, not the PS2 transfer pipeline. No HD function counterpart is
promoted merely from these names.

DDS has unique exact masked-body candidates for sizing002d1d20, queue002d1d80,
image transfer002d2548 and palette transfer002d2650. All58 QWC table destinations
agree relative to the helper. The expanded32-body cohort contains28 unique
exact-body candidates and37 agreeing direct-call constraints. The tiny TMX
wrappers alone remain14-way/6-way ambiguous.

Their common tail targets identify related DDS creator002d30c8, a448-byte body.
It adds18 explicitly checked texture-ID lookup instructions, different prologue
scheduling and two equivalent source-address temporary-register instructions.
After those explicit differences, all94 Nocturne construction-core words agree,
with all ten constructor/transfer/cache targets independently constrained. DDS
searches the registered texture tail by header.texId+1c, follows descriptor.prev+4,
and on a match increments the ownership object through texture.origin+8 and
returns the existing handle. Nocturne has no such lookup/count increment. This
connects to the additional ownership object already found in DDS's descriptor
constructor. The related creator constrains copy/reference wrappers to002d3288/
002d32a0. Raw ambiguity and the full-body differences are retained; this is not
an exact whole-body or DDS runtime equivalence claim.

Continue PAC type2 preparation, streaming/compression callbacks and completion
002c6c80, including the real handle ownership and parser callbacks. Default PAC
dispatch and asynchronous task/load/wait/close still need source before moon
initializer001eadd8 can execute its actual loader path. Full or near-full source
recovery, physical GS/game runtime and a matching executable remain incomplete.

Evidence: [validation](texture-upload-validation.json),
[interfaces](texture-upload-interfaces.json),
[saved interface check](texture-upload-abi.json),
[real moon descriptor/buffer outputs](moon-tmx-construction.json),
[Unity role review](texture-upload-matches.json),
[DDS bodies, tables, reuse differences and wrapper constraints](texture-upload-transfer.json).

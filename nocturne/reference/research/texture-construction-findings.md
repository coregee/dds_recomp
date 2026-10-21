# Texture descriptor, VRAM, palette and register construction

Fifteen complete PS2 routines are integrated in `src/texture_construction.c`:
1,612 summed original body bytes and5,248 passing original-instruction/C cases.
The source compiles as C11 with MSVC `/W4 /WX /O2`. Annotations are saved directly
in `ghidra/working/Nocturne.gpr`, independently reopened, and exported in place.
No checkpoint, project copy, frozen source tree or backup was created.

| Entry | Recovered role | Cases |
| --- | --- | ---: |
|002aa558|Interrupt-protected VRAM extent allocation|384|
|002ab360|Append texture descriptor to registered tail|256|
|002ab388|Eight-argument64-byte descriptor construction|384|
|002ab580|Palette VRAM allocation and dimensions|512|
|002ab6e8|Inclusive mip sizing, actual VRAM and descriptor construction|512|
|002aaff0|Palette count byte getter|256|
|002aaff8|Optional palette GS address getter|256|
|002ab010|Base GS address getter|256|
|002ab070|Full64 format-to-bit-depth helper|256|
|002ab658|Wrapped palette byte demand|384|
|002a8170|Pool/handle-backed staging allocation|384|
|002ab688|Palette staging allocation and descriptor stores|384|
|002ab6c8|Actual forward palette copy and destination result|384|
|002aba78|Actual64-byte GS register cache construction|384|
|002abb18|Context0 cache wrapper, pointer at descriptor+28|256|

The original instructions execute real pool allocation/zeroing, memory-handle
allocation/acquisition, memcpy and the canonical texture register builder. No
game function is intercepted or supplied a synthetic allocation result. The
comparison covers140,636 bytes of declared RAM per case, raw V0 where meaningful,
Status, DI/EI/SYNC/PLZCW counts and preserved EE callee registers. CPU primitive
values use the existing instruction model; this is not physical kernel/GS proof.
Guard data uses repeatable patterns so the single current capture stays compact.

VRAM records contain next00/prev04/state08/address0c/size10 and dimensions14/16,
format18. Allocation walks signed64 comparisons of signextended32 extent sizes,
returns an exact fit or splits an allocated record from the free extent's high
end. Tests include skipped occupied/undersized records, head/previous insertion,
exact fits, signed negative requests and interrupt states. On exhaustion the
original may call the error handler, then still load through a zero node. That
unchecked path is retained and is not tested here.

Palette creation drops the format's high lane through ADDIU before its26-entry
switch, whereas mip construction rejects a full64 format outside0..20 before
its21-entry switch. Format19/27 palettes use8x32 extents;20/36/44 use8x8. Mip
levels include level0 through the supplied count, using wrapping32-bit products,
arithmetic shifts and wrapped accumulation. Unbounded/noncanonical mip counts
are only tested when invalid format makes the original return before the loop.

Staging selects the pool using a signed64 threshold1025. The original pool then
uses a full64 small-request comparison; negative64 requests whose low words are
positive must still select class0. The adapter normalizes that class0 request
before calling the existing32-bit pool C interface. Tests include negative high
lanes with low128/1024, positive high lanes with low1, and ordinary requests on
both sides of the staging threshold. Palette copies include self and bounded
forward overlaps using the actual recovered copy implementation.

Unity retains `libsdf_H.sdfTexHandle_t` and `sdfGsMemSlice_t`, corroborating the
descriptor's dimensions, GS handles, palette count/format, pixel format, mipmap
fields, packets, palette data/size and color. Its managed fields have different
offsets and ownership. The retained native `sdfTexSetEx`18230d580 and `sdfTexSet`
18230d5d0 allocate a handle and invoke its constructor without decoding their
texture arguments. The handle constructor181cbd750 allocates two GS slice
objects. These bodies are not equivalent PS2 constructors, so no HD function
counterpart is promoted from them.

DDS has unique exact masked-body candidates for14 of these15 routines and all
eight dependency anchors. Twenty-six of27 direct-call constraints agree with
exact-body candidates. Both palette/mip tables agree at every relative branch
destination. The remaining mip tail points to DDS descriptor002d2728, whose
212-byte body adds an8-byte zeroed ownership object, sets its word+4 to1, and
stores its pointer at texture+8. Nocturne leaves that field zero. Removing only
the five explicitly checked ownership instructions and restoring two adjacent
instruction schedules makes all48 Nocturne words agree, with both relocated
calls separately checked. This is recorded as a related body with a concrete
behavior difference, not exact whole-body equivalence or DDS runtime proof.

The next connected source is full TMX creation002abc90 and its image/palette
transfer paths002ab1a8/002ab2b0, sizing002aa980 and queued GIF/DMA upload002aa9e0.
Then recover PAC type2 callbacks and asynchronous loader dependencies before
integrating moon initializer001eadd8. The recovered constructors alone do not
establish upload, archive loading, rendering, original source text or a matching
executable. Full/near-full executable recovery remains incomplete.

Evidence: [validation](texture-construction-validation.json),
[raw interfaces](texture-construction-interfaces.json),
[saved interface check](texture-construction-abi.json),
[Unity role review](texture-construction-matches.json),
[DDS word, call and table constraints](texture-construction-transfer.json).

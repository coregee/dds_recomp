# Binary PAC records and pointer relocation

Ten complete routines add 1,196 original body bytes and 2,752 passing original-instruction/compiled-C comparisons. Source is in `src/pac_binary.c`. Annotations are saved in place in `ghidra/working/Nocturne.gpr`; selected exports and validation reports are rolling outputs.

| PS2 entry | Role | Body bytes | Cases | Constrained DDS entry |
|---|---|---:|---:|---|
|002c6718|Prepare binary record|292|384|002ee2c0|
|002c65b0|Raw copied stream|132|256|002ee158|
|002c6638|Compressed stream|120|256|002ee1e0|
|002c66b0|Reference stream|104|256|002ee258|
|002c6840|Type1 initializer|48|192|002ee3e8|
|002c68d0|Type6 initializer|48|192|002ee478|
|002c6960|Type8 initializer|48|192|002ee508|
|002c6870|Type6 completion|96|256|002ee418|
|002c6900|Type8 completion|96|256|002ee4a8|
|002c39c8|Encoded pointer relocation|212|512|002eb278|

Preparation uses header.realSize+0c when nonzero; its fallback is the wrapped expression size+4 plus the upper compression nibble minus16. Reference mode appends the real result record and retains header+16 as its data pointer. Copy mode changes parser state to2, appends a real node, chooses the high/low allocator, acquires the handle and sets parser.destination1c. The lower compression nibble selects raw/decoder work; unknown values leave the callback unchanged. Types1/6/8 select distinct end callbacks.

Raw and reference streams use signed minimum(left14,rest20), return without completion at zero, and reload fields after advancing. Copied data and its handle remain owned by the result node. Compressed binary streaming uses left14, unlike the texture callback's rest20; it advances by bytes consumed and releases the actual decoder on completion without clearing rest20. Tests run actual pool, handle, parser, memcpy, decompressor, FinishRecord/Type6/Type8/Stop and returning GetProcessData bodies. No game-function returns are supplied.

The relocation table has four encodings. A clear low bit represents a one-byte word delta. Low bits01 or011 introduce two- or three-byte little-endian deltas. Low bits111 represent a run of `(firstByte >> 3)+2` consecutive words, advancing before each patch. Each target word receives the low32 base with wrapped addition. The initial limit is signed64; later consumed-byte arithmetic wraps32. A multi-byte command is read in full even when it crosses the supplied byte limit, so tests keep those bytes backed.

Types6 and8 have identical complete PS2 instructions. They adjust the retained data pointer by16, read the preceding offset/count header, relocate using body+offset, clear the count and finish. Their raw DDS body matches therefore remain ambiguous until the full static default dispatcher fixes each initializer route and the initializer's callback constructor fixes each completion identity. All ten identities are then constrained by full bodies,20 real call links,six callback constructors and three dispatcher routes. The default dispatcher itself is a static anchor, not recovered source in this group.

In 576 split synthetic whole-record integrations, all three initializer types pass through low/high copying, reference and compression. Inspection checks retained handles/data, exact payload bytes, all sixteen expected pointer patches for types6/8, count clearing, parser completion and result links. The 512 standalone relocation cases exercise all delta/run encodings, nonpositive raw limits and backed commands crossing a byte limit. Fixtures are synthetic; no shipped binary asset has been identified by these tests.

Unity retains parser/resource/header role names, but managed object references differ from the native pointer relocation layout. No equivalent native HD method is promoted. Full default dispatch, type9 texture-array callbacks and asynchronous loading remain next. Arbitrary aliases, malformed/exhausted inputs, physical runtime and a matching executable remain unproved.

Evidence: [focused comparison](pac-binary-validation.json), [actual payload inspection](pac-binary-matches.json), [DDS bodies and constraints](pac-binary-transfer.json), [saved interface check](pac-binary-abi.json).

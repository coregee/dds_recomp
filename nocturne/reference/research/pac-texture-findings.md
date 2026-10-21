# PAC texture callbacks

Six complete routines add 880 original body bytes and 2,048 passing original-instruction/compiled-C comparisons. Source is in `src/pac_texture.c`; annotations are saved directly in `ghidra/working/Nocturne.gpr` with current selected exports.

| PS2 entry | Role | Body bytes | Cases | DDS entry |
|---|---|---:|---:|---|
|002c6b50|Prepare transfer and select decoder|288|384|002ee6f8|
|002c6990|Raw copied stream|168|384|002ee538|
|002c6ad0|Direct reference stream|124|256|002ee678|
|002c6a38|Compressed stream|152|384|002ee5e0|
|002c6c80|Store completed texture and finish record|60|256|002ee828|
|002c6cc0|Allocate result/work and initialize record|88|384|002ee868|

Preparation stores the transfer at parser+28 and remaining=size-16. Flag bit 0 selects a direct input reference. Otherwise flag bit 1 chooses the actual high-end allocator; the clear bit chooses the actual low-end allocator. Both eight-byte header loads occur before the first store. Compression byte 0 selects raw copying, byte 1 allocates and initializes the real decoder, and other values leave the decoder callback unchanged after allocation.

Raw and reference streams use the signed minimum of parser.left14 and transfer.remaining0c. A zero count returns without triggering completion. Raw streams copy through the actual memcpy, then advance and reload the work fields. Completed copied streams acquire the actual buffer, build the full TMX texture and upload queue, store the texture, and clear/free the temporary handle. Reference completion builds a direct-reference TMX texture. Compressed streaming takes its input count from parser.rest20 independently of offered left14, advances by bytes actually consumed, and releases the real decompression work after completion.

Completion writes the texture to the appended result node's handle+8, releases the transfer work and runs the recovered FinishRecord routine. Its tests cover actual header callbacks returning 0,1,2,3,4, including singleton removal and the original stale tail for multiple nodes. On-end tests run the actual Complete and Stop bodies. Their returns are not supplied by the harness.

The 192 split whole-record integrations start with the recovered record initializer and feed the recovered parser's data dispatch over up to three calls. All six actual moon records pass through low-end copying, high-end copying, direct reference, and high-end compressed copying. The last path uses synthetic literal encodings of the real body bytes; the shipped records themselves are uncompressed. Inspection checks the actual result-node handle, descriptor, default register cache, exact retained palette and pixel buffers, two linked upload packets, cleared temporary handles, parser completion and ownership bytes 2/1 for copies or 0/0 for references. All 320,988 declared RAM bytes, Status, primitive observations and ordered callback/syscall traces are compared per case. The run observes 6,520 callback words, 1,020 original image scratch operands and 6,120 syscall trace words.

DDS has unique matching full bodies for all six routines, with 23 agreeing callee links and four checked callback address constructors. Only documented address/call/GP relocations are masked; fields, constants, branches and registers remain exact. Tiny copy/reference wrapper identities are constrained through the previously reviewed DDS TMX creator. DDS's ownership object and texture-ID reuse behavior still differ from Nocturne. No DDS source/runtime validation is claimed.

Unity's retained parser, resource and texture types support their roles. Managed layouts differ, and the available setter bodies omit the original native TMX path. No exact native HD counterpart has been promoted for this group.

Header completion uses the real GetProcessData routine returning zero, so this establishes the complete type-2 callback path rather than the full default archive dispatcher. Default dispatch, other record types and asynchronous loading remain the next frontier. One unused ambient image stack word plus CPU/syscall values remain explicit boundaries. Malformed/exhausted inputs, arbitrary aliases, physical GS/runtime and a matching rebuilt executable remain unproved.

Evidence: [focused comparisons](pac-texture-validation.json), [actual output inspection](pac-texture-matches.json), [DDS bodies/calls/callback pointers](pac-texture-transfer.json), [saved interface check](pac-texture-abi.json).

# Full PAC dispatch and texture arrays

Nine complete routines add 880 original body bytes and 2,432 passing original-instruction/compiled-C comparisons. Source is in `src/pac_texture_array.c`; annotations and selected exports are saved in the normal working project with rolling reports.

| PS2 entry | Role | Body bytes | Cases | Constrained DDS entry |
|---|---|---:|---:|---|
|002b2a60|Pointer array, stride4/growth4|28|256|002d9fa8|
|002b2b10|Append pointer with real growth|104|256|002da058|
|002c6d18|Prepare copied nested texture header|60|256|002ee8c0|
|002c6d58|Set up16-byte nested header copy|48|128|002ee900|
|002c6d88|Append completed item or finish array|120|256|002ee930|
|002c6e00|Skip count-table padding|104|256|002ee9a8|
|002c6e70|Read count and create actual array|136|256|002eea18|
|002c6ef8|Initialize type9 record|60|256|002eeaa0|
|002c64b0|Full default record-type dispatcher|220|512|002ee058|

The complete default dispatcher now invokes the actual recovered initializers for types1,2,6,8,9. Typeff returns1; unsupported types return3. Every nonzero full64 phase returns0 without reading the header. Actual parser/header/data/on-end/default callbacks execute; none of their return values or texture handles are supplied by the harness.

Type9 allocates48-byte work, reads a full count word whenever left14 is nonzero, advances4 bytes and creates a real stride4/growth4 pointer array. Its padding count is the wrapped expression `((count*4+0x53)&~63)-0x14`. Skip-table runs Advance even when the selected count is zero. It then copies the next16-byte nested header into work+10, prepares the texture using work+20, appends the completed texture, and either releases work/finishes or reads another nested header. Pointer append preserves signed16 growth policy, live reloads and the count store before the value store. Constructor capacity uses the typed signed32 ABI already established for ArrayCreate and actual count-word callers; noncanonical high capacity lanes are outside this test scope.

In96 whole-archive cases, the actual50,688-byte moon.LB runs through Initialize(default callback), DecodeChunk, every record callback, actual allocation/TMX/queue dependencies and the END record. Low-end copy, high-end copy and reference modes all produce six verified result-node texture handles, correct128x64 descriptors, exact retained palette/pixel bytes and twelve linked upload packets. Partial runs use chunks ending on64-byte boundaries so the original full-header read remains backed. This is complete archive decoding from supplied ordinary RAM; asynchronous file loading and physical GS execution are not established.

An additional72 complete synthetic type9 archives contain two real moon texture records. The returned actual pointer array has count/capacity2, stride/growth4, two verified texture handles, exact buffers and four upload packets. DDS full bodies agree under documented address/call/GP relocations, with18 agreeing callee links and five callback constructors. Calls from the longer count/item routines constrain otherwise ambiguous small array wrappers. Unity retains parser/resource/model-texture-list role names; no equivalent native HD function is promoted for this group.

**Compressed nested records make zero progress in this original instruction model.** The nested-header raw callback clears parser.rest20 to zero, then installs the compressed texture callback, which takes its byte count from rest20. A full DecodeChunk run reached the two-million-step limit on that path.24 bounded cases execute the real count/table/header callbacks and one real compressed-stream call: parser state stays2, left14 stays64, rest20 stays0 and input stays at the encoded body. The reconstructed source preserves that behavior. This is evidence about this original path and instruction model, not a runtime claim that all possible compressed-array callers fail. The shipped moon archive is uncompressed.

All320,988 declared RAM bytes, raw root/sequence results, Status, primitive observations and callback/syscall traces are compared. One original ambient image stack word plus CPU/syscall values remain explicit boundaries. Asynchronous loader/task/file I/O, arbitrary aliases, exhaustion/malformed loops, physical runtime and a matching rebuilt executable remain outstanding.

Evidence: [focused comparisons](pac-texture-array-validation.json), [full archive/array output inspection](pac-texture-array-matches.json), [DDS constraints](pac-texture-array-transfer.json), [saved interface check](pac-texture-array-abi.json).

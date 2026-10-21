# PAC compression and high-end allocation

Four complete routines add 1,276 original body bytes and 2,688 passing original-instruction/compiled-C comparisons. Source is in `src/pac_compression.c`. Changes are saved directly in `ghidra/working/Nocturne.gpr`; reports and selected exports are rolling outputs.

| PS2 entry | Recovered role | Body bytes | Cases | DDS entry |
|---|---|---:|---:|---|
|002a9158|High-end memory-handle allocation|300|512|002d0518|
|002a9618|Clear a handle slot, then free/coalesce|52|384|002d09d8|
|002c72f0|Initialize compression destination/state|16|256|002eee98|
|002c6f38|Full ten-state streaming decoder|908|1,536|002eeae0|

The allocator rounds with wrapped 32-bit arithmetic, walks the descriptor list backwards and splits from the high end. Its state-2 path re-enables interrupts when they were originally enabled; unlike the low-end allocator, it does not invoke a pressure callback. Clear/free stores zero to the caller's slot before running the actual free/coalescing routine.

The decoder implements literals, zero fill, repeated bytes, narrow and wide backreferences, and interleaved byte/zero output. Backreferences copy forward byte-by-byte, allowing overlapping runs. Extended lengths and split distance bytes retain their partial states. The initial count is tested as a signed 64-bit value, while subsequent decrements wrap and sign-extend 32 bits. Active calls reset the 16-slot input trace; command FF completes and E0 through FE are ignored.

Tests run actual pool, memory-handle free, memcpy, memset and interrupt dependencies. They compare all 320,924 declared RAM bytes per case, raw return values, Status and primitive observations. Cases cover partial states, raw high count lanes, ring wrap, overlapping backreferences, metadata coalescing, two backed output/state aliases and zero-length copy/fill without accessing a null destination. In 256 cases, synthetic literal streams decode the body bytes of all six real moon records exactly. **The shipped moon archive is uncompressed:** these fixtures establish handling of real bytes, rather than a compressed-file discovery.

Read-only DDS comparison finds unique complete bodies for the four new functions and seven dependency anchors, with eleven agreeing calls. All ten decoder switch-table destinations agree relative to its entry. Its relocated trace-ring store is checked through the LUI/index-add/store constructor; reset/load/store share one GP slot. Constants, registers, fields and relative branches remain exact. This supports transferring the engine pattern to DDS, without claiming DDS source/runtime validation.

Unity's retained `sdfPacDecodeCb_t.decompWork` and `decodeWork` names corroborate parser roles. Managed object offsets differ from the PS2 native words. No equivalent named HD decoder body has been promoted to the counterpart ledger.

Exhaustion, malformed positive states/command kinds, zero-length backreference/interleaved do-loops, arbitrary aliases, asynchronous loading, physical execution and a matching rebuilt executable remain unproved. The [PAC type-2 callbacks](pac-texture-findings.md) now connect these routines to the actual TMX constructors in192 split whole-record integrations. Full default record-type dispatch and asynchronous loading remain next.

Evidence: [focused comparison](pac-compression-validation.json), [DDS bodies and constraints](pac-compression-transfer.json), [managed roles and real-byte output review](pac-compression-matches.json), [saved interface check](pac-compression-abi.json).

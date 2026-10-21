# PAC streaming parser and resource records

Nine integrated C routines cover988 original body bytes and pass3,200 focused
original-instruction comparisons. They compile in the shared host DLL with
warnings as errors. Their raw interfaces are saved in the existing working
project, independently reopened and exported. The original pool, memset, memcpy
and selected callback bodies execute; no game function is intercepted.

| PS2 entry | Recovered routine | Cases | DDS static candidate |
| --- | --- | ---: | --- |
|002c6030|ps2PacInitialize|256|002edbd8|
|002c6098|ps2PacSetFlag2|256|002edc40|
|002c60a8|ps2PacReleaseRecords|256|002edc50|
|002c60e0|ps2PacStop|128|002edc88|
|002c60f0|ps2PacAdvanceBuffer|256|002edc98|
|002c6118|ps2PacReadHeader|512|002edcc0|
|002c61f0|ps2PacFinishRecord|512|002edd98|
|002c62a0|ps2PacDecodeChunk|512|002ede48|
|002c63b8|ps2PacAppendRecord|512|002edf60|

The56-byte PS2 parser starts with signed state00, flag01,16-bit block counter02,
callback04, decoder08 and completion callback0c. Input pointer10, remaining14,
total18 and pending bytes20 control streaming. Result head30/tail34 own raw pool
records. Initialization runs the real memset, sets counterffff and chooses default
callback002c64b0 only for a full64 zero callback argument. A nonzero upper argument
with low32 zero therefore stores zero rather than selecting the default.
The flag helper ORs2 into byte1.

Advance loads input/remaining/total before writing input+n, remaining-n and
total+n, with32-bit wrap. Stop writes signed byte-1. DecodeChunk always stores
low32 input and count; its first BLEZ tests the entire64-bit count, while its loop
and skip minimum use signed32 words. Positive full64 counts with a negative low32
word can enter the parser; subtracting a header can wrap that remaining word
positive. The fixtures use a real stop-returning callback for cases that would
otherwise require an enormous walk. They do not substitute a different count ABI.

State0 aligns total to64 bytes or consumes a16-byte header and increments the
16-bit counter. The original reads that full header even when fewer than16 bytes
were offered, so the backing bytes must exist. Pending body is stored size minus
(header.byte1&f0) minus16. The actual header callback receives(parser,0,header).
Exact full64 return1 stops; return2 enters state1 with pending rounded upward to64;
other returns enter state2. State1 advances the signed minimum of offered/pending
and returns to state0 at zero. State2 calls the actual decoder. Signed state-1
terminates; unrecognized states with positive remaining counts can loop forever.
That unchecked behavior is preserved, but endless cases are not run in the tests.

Finish calls the actual header callback(parser,1,tail+10) before reloading its
links. Return1 stops. Return4 removes the last record and runs the real pool release.
A one-node list clears both head and tail. A longer list walks to the predecessor
and clears its next pointer, while leaving the parser's tail pointing at the
released record. Other returns clear state to0. This stale-tail behavior is in the
original instructions and is preserved. ReleaseRecords saves each node's next
before pool release and leaves the parser head/tail words unchanged.

Append computes extra=header.byte1&f0, allocates a real zeroed extra+32 byte record,
stores parser ownership at+4, and uses the real forward memcpy to copy extra+16
bytes to node+10. It appends through head30/tail34. Tests cover all16 extended-header
lengths, empty/nonempty lists, bump/freed/new-page allocation paths, full raw argument
lanes, and headers that alias the newly zeroed allocation. Zeroing and forward
copy order can change the copied header under this alias; no disjoint-copy shortcut
is used. There is no invented allocation-NULL guard.

Unity retains named libsdf_H.sdfPacDecodeCb_t, sdfPacDecodeResrc_t and
sdfPacStdBlockHeader_t types. Their fields corroborate the parser/header/result
roles. HD callback/decoder/onEnd18/20/28 are managed delegates; srcData is an array
or object plus separate src_ptr38/srcLength3c/srcTotal40, rest54 and head78/tail80.
The HD result has managed next10/cb18/handle20/ptr28, an extra head_index30 and a
header object reference38. PS2 embeds the variable header in a raw result node.
The named HD sdfPacBin.GetNextPos1825ed480 provides separate stored-size/64-byte
buffer navigation. It is not the PS2 streaming state machine. These nine routines
keep descriptive PS2 aliases; no exact HD function identities are promoted.

The3,200 comparisons check all124,304 declared RAM bytes, raw results, Status,
CPU primitive counts and906 actual callback operand traces. Header callbacks
execute recovered GetProcessData00101ab0 against a backed data word, giving real
zero/1/2/4/sign-extended negative returns. Decoder callbacks execute the original
Stop002c60e0. They are ABI-compatible selected test callbacks, not evidence that
the game binds those routines as PAC callbacks. No callback return is supplied by
the harness. Memory-library instructions execute with the existing PCPYH/PCPYLD
value operations:256 occurrences of each are observed in the original execution.
Header/parser aliases, original moon record headers, counter wrap, signed skip and
raw high-lane boundaries are covered. The current capture has no uninitialized
memory warnings. Emulator PC observations do not separately enumerate branch
delay slots and are not a claim of physical CPU timing.

Every new routine has one full-span DDS pattern candidate. The existing zeroed
pool002cff68, pool release002cff98, memcpy002fffec, memset003001a0 and default
PAC dispatcher002ee058 also match uniquely. All ten direct callee constraints
agree. The initializer's separately decoded default-callback constructor points
at002ee058, providing an additional pointer constraint. Masks are limited to
J/JAL targets, GP loads/stores and the explicitly listed callback-address
constructor. Local offsets, register usage, branches, alignment constants and
body holes remain exact. No DDS runtime/source equivalence or annotations are made.

The default dispatcher002c64b0 and texture callbacks002c6cc0/002c6b50/002c6990/
002c6c80 still need canonical source and real integration. In particular this
batch does not create the moon's six texture handles. Asynchronous file task/load/
wait/close paths and moon initializer001eadd8 remain unrecovered. Other callbacks,
malformed membership/cycles/endless inputs, arbitrary64 callback return domains,
physical PS2/HD runtime and matching binaries remain unproved. Full executable
recovery is unfinished.

Evidence: [source](../src/pac_parser.c),
[validation](pac-parser-validation.json),
[reopened interfaces](pac-parser-abi.json),
[managed types and explicit identity limits](pac-parser-matches.json),
[DDS patterns and call/pointer constraints](pac-parser-transfer.json),
[moon asset and connected callback frontier](moon-callback-frontier.md).

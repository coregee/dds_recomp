# SIF command, RPC and file-service initialization

Nine complete C routines add1,648 original body bytes and pass1,024 comparisons
against the original PS2 instructions. Command initialization002dde38, RPC
initialization002de508 and file initialization002dfad8 now execute actual recovered
interrupt/cache/DMA/packet/bind/call/descriptor dependencies. The additional bodies
cover command-handler registration, command-register reads and four syscall veneers.
Existing FlushCache and EnableDmac bodies are reused rather than counted again.

The tests compare the full53,512 bytes of declared storage, defined returns,
Status, kernel/cache/SIF/MMIO traces and the existing EnableDmac wrapper's SYNC0.
The file initializer has208 successful cases,32 bind/semaphore/DMA failure cases
returning-1, and16 command255 submission failures returning sign-extendedfffeffff.
It retains native descriptor flag clearing, callback registration, the uncached
version-word copy and initialized-flag timing. Raw64 syscall results, command
sign tests, word-width indexing and unconditional EI on repeated init are retained.
The host C build passes with warnings treated as errors.

Eight unique complete DDS instruction spans agree under explicitly listed address
and J/JAL relocations.27 actual call targets, two RPC callback registrations,
adjacent command/RPC flags, command-state fields, handler/register tables and
three RPC buffers are corroborated. Literal hardware addresses, masks, table
sizes, uncached-bit constants and relative branch words remain exact. The file
initializer has no complete DDS span match; no DDS identity is assigned to it.
These SDK paths have descriptive PS2 aliases rather than new Unity identities.

Kernel/register/MMIO values and ordinary externally supplied ready/server/reply
bytes are boundaries. The bind's server word is supplied at its semaphore wait,
and a ready command-register word can arrive at DMA submission. This does not
execute the IOP or prove hardware transfer, synchronization, scheduling or file I/O.
Cached and uncached storage remain separate. The native RPC semaphore option is
never initialized in its packet: each original call's actual stack word is captured
and supplied only to that explicit operand boundary, because earlier nested callees
can overwrite an entry seed. Defined packet fields and game returns are computed
by the recovered source. Returning DI contexts are tested; unending hardware polls
and the1,048,577-iteration bind retry delay are statically retained, not completed
runtime test paths. Arbitrary malformed tables and hardware behavior remain unproved.

The working project is saved in place and selected exports updated. Continue native
file open/close/seek/read/write002dfd70/002dfff8/002e0178/002e03b0/002e0620, then
generic/movie workers and loader scheduler/pump integration. Full or near-full
executable recovery remains unfinished.

All five native file operations now have recovered source and actual response/completion integrations in [file-operation findings](file-operations-findings.md). Worker error/detach and execution remain next.

# Message construction and packed pointer relocation

Thirteen new complete PS2 routines are recovered in `src/message_construction.c`, adding 1,116 recognized body bytes. They use the existing 212-byte `ps2PacRelocatePointers` body in `src/pac_binary.c`, making fourteen original roots in this comparison. They cover slot-list allocation and return, resource relocation and binding, the type-header pointer, six field initializers, window parameters and the complete message-manager constructor. The affected C builds with warnings treated as errors. The focused comparison passes 1,472 cases, executes 320,502 original instruction steps and reaches all 274 non-delay root instruction addresses.

All 31 shipped standalone BMD files are extracted from their indexed DDS3 image windows and used in five original paths: packed relocation, resource resolving, type-header lookup, resource binding and complete construction. These account for 155 cases. An independent decoder expands relocation positions before checking 21,212 relocated word observations. Another 31 connected constructor-to-resolver sequences show that the relocation marker prevents a second relocation. Actual recovered pool allocation, memory-handle allocation/acquisition and field initializers execute; no game callee returns are supplied by the harness. Full declared RAM, defined raw64 returns, Status, CPU primitive counts and returning-call callee saves agree.

## Original layouts and behavior

The slot-list descriptor is at 0x56BE70, with active head/tail at +0/+4 and free head/tail at +8/+0xC. Nodes start at 0x56BE80 and have stride 20: previous +0, next +4, ID +8, state pointer +0xC and allocation handle +0x10. The count is at 0x56BE60. Taking a free node appends it to the active list; returning an active node appends it to the free list. The source preserves live reloads and original write ordering.

Construction allocates 0x1D4 bytes through the real memory-handle allocator, which rounds the extent to 512 bytes. The state contains phase +0, resource +4, type +8, flags +0xC, value 0x47 at halfword +0x10, speaker +0x14, message +0x24, select +0x40, window +0x9C, variable pointers +0xC4, cursor +0x1C4 and a cleared final word +0x1D0. The 32 variable-pointer words are cleared in descending order; the following handle array is preserved. A nonzero cursor display argument preserves its previous display byte. Position-reset arguments use their full 64-bit value, and window alpha uses a signed 64-bit positive test.

The resource marker is byte +0x1C. If zero, the resolver uses the relocation-stream offset at +0x10 and byte count at +0x14, then marks the resource resolved. Relocation starts at data+0x20 and adds that base to each selected 32-bit word, with modular arithmetic. The packed stream uses word deltas:

| Encoding | Meaning |
|---|---|
| Low bit 0 | One-byte value shifted right by 1 |
| Low bits 01 | Two-byte little-endian value shifted right by 2 |
| Low bits 011 | Three-byte little-endian value shifted right by 3 |
| Low bits 111 | Relocate the next `(byte >> 3) + 2` words |

Repeated zero deltas add the base repeatedly to the same word. The original decoder does not validate stream or pointer bounds. Nonpositive signed raw64 lengths return immediately. The type header follows the eight-byte record array at data+0x20+(header count at +0x18)*8. Binding stores the new resource and returns the sign-extended previous resource word; MSG1 magic at +8 additionally publishes the type-header word at +8 into the instance type.

Thirteen named Unity semantic counterparts are reviewed. Managed layouts, constructor arguments, coordinates and default window alpha differ. HD `ResolveResourceAddress` is a retained no-op; its name helps identify the PS2 role but provides no relocation implementation. The shared PS2 relocation body retains its existing descriptive alias rather than a claimed retained HD SDK counterpart.

Eight complete selected spans resolve uniquely in DDS, with three agreeing call links. The decoded instance-table global 0x56BE8C relocates to 0x3D6ECC. Speaker/message/select/window initialization, parameter reset and the complete constructor have no full-span match under this comparison; their constants and branch layouts are not loosened to force identities. The existing memory-handle pointer acquisition dependency also resolves. These are static transfer results, not DDS execution.

Evidence is in `message-construction-validation.json`, `message-construction-assets.json`, `message-construction-matches.json`, `message-construction-transfer.json` and `message-construction-abi.json`, with one rolling fixture/vector set in `message-construction/`. Names and interfaces are saved and reopened in the working Ghidra project, and selected exports are updated in place. The existing 2,752-case PAC binary comparison also passes through the changed host address binding, using its previous original capture and the current C/DLL; no fresh PAC capture or new full-suite run is claimed. Tests cover valid free slots, sufficient backed allocation extents and finite backed resource layouts. Cleanup now has the separate [script/message lifetime comparison](script-lifetime-findings.md). Slot exhaustion, null allocation errors, physical PS2 execution and a matching executable remain unproved. The complete constructor now removes a dependency from [script allocation and FLW0 parsing](script-process-next-frontier.md); message release and script shutdown are now recovered.

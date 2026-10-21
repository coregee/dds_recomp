# Negotiation phase recovery

The [publication](negotiation-phases-publication.json) brings recovery to
2,638/9,060 recognized functions (29.117%), 442,084 recognized bytes and 531
source units. Whole-program recovery remains incomplete.

Eighteen complete original routines implement negotiation conditions, messages,
party-member selection and phase outcomes. Seventeen have corroborated Unity
FlowOne/FlowTwo roles; the 64-row special-pair predicate retains a descriptive
PS2-only name. The [source review](negotiation-phases-source-review.json) and
[independent review](negotiation-phases-independent-source-review.json) check
all 1,304 instruction members and the 34-body direct closure. Those bodies
contain 5,216 recognized bytes and 5,280 full-span bytes. Source is in
`src/negotiation_phases.c`; the separate test transport observes real function
calls and CPU exception boundaries without supplying game results.

Unity is a role reference, not an ABI or layout template. Compatibility checks
compare the complete 64-bit argument with sign-extended `80000000`, `80000001`
and `80000002`. Zero-extended low-word versions take a different path. The
ordinary mask loop visits bits 0 through 30; three native dispatch-default
instructions cannot be reached by its one-hot shift invariant. The flag
argument is also tested across all 64 bits. Original personality records have
48-byte stride, special-pair records 60-byte stride, and party formations
128-byte stride. Each offset and table still needs independent checks in
another SMT game.

Party selection scans formations 4 through 13 and uses actual unit/status
helpers. Flag 2 takes precedence over flag 4 in the unit resolver, making
formation flags 7 a valid enemy-backed case. Filtering, exclusions, order,
uncapped RNG retry and actual RNG advancement are retained. The original
Flow1_24 reads signed Main+0x1A, subtracts one and divides 50 by that result.
When the field equals one, DIV writes processor values before a deliberate
BREAK7. Recovered C preserves preceding queue/outcome writes and stops at the
same exception boundary; it does not fabricate a normal return.

The [original run](negotiation-phases-original.json) executes 3,904 cases over
586,168 instruction steps. All pass against the isolated probe and the
[main build](negotiation-phases-main-C-validation.json): 3,900 returning cases
and four genuine BREAK7 stops. Each C build compares all 511,783,168 declared
mutable RAM bytes, original immutable tables, defined raw returns, actual
completion/traps, Status, condition/value FCSR and CPU primitives. Native
callee saves are checked on returning original calls. The
[input/capture review](negotiation-phases-input-capture-independent-review.json)
reconstructs every authored BEFORE state and verifies the exception transport.

The existing capture driver is unchanged. A temporary generated driver has
four exactly reversible edits: class name, immutable-table checks, the one
reviewed zero-divisor CPU site and observation of the actual following BREAK.
The DIV model follows the pinned upstream
[PCSX2 implementation](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/R5900OpcodeImpl.cpp#L363).
Its processor-value handling lets the original branch and BREAK execute;
HI/LO equality is not part of this semantic C proof. Temporary compilation
inputs are removed, and no project or validation snapshots are created.

All eighteen [native interfaces](negotiation-phases-native-ghidra.json) were
saved, independently reopened and exported using the original processor.
The [retained replay](negotiation-phases-focused-regressions.json) passes all
6,218 cases across the preceding 27 routines on the 531-unit main DLL. All
529 earlier object files remain unchanged. The last full 413-function/462,684
case replay remains its 525-unit epoch. Full volatile banks, private frames,
arithmetic FCSR flags, physical timing and whole-game execution remain open.
Queue/script IDs and continuation pointers remain data in these routines;
these tests do not claim VM or dialogue execution.

Eight [supplemental original/main cases](negotiation-phases-edges.json) close
thirteen feasible non-delay PC gaps from the base run. Three exercise positive
party selection using unchecked IDs 411, 412 and 510, whose original backing
bytes satisfy the personality test. These IDs are explicitly a raw-memory test
domain, not established retail species or descriptor identities. Other cases
cover the full-width special mask against a zero-extended contrast, and actual
RNG rolls 39, 40 and 41 at the race-13/mood-1 threshold. All ordinary RAM,
defined returns, completion, tables and processor-profile fields agree; base
inputs, vectors, source and shared capture driver remain unchanged.

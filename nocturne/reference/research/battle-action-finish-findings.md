# Native effect cleanup and action completion, 2026-10-12

Thirteen complete native routines (1,532 recognized body bytes) now compile and
pass 2,176 comparisons against original PS2 instructions. All 324 selected main
instruction addresses execute. The comparison includes 128 existing action
dispatcher cases invoking the actual state19 death and state21 after callbacks.
The working Ghidra interfaces were saved, independently reopened and checked;
all thirteen corrected-language exports were merged in place.

## Recovered bodies

| PS2 entry | Recovered routine | Recognized bytes |
|---|---|---:|
| 0016AB10 | effBTLDelete | 96 |
| 0016AC28 | effBTLCutListRelease | 68 |
| 0016AE08 | effBTLCutDelete | 144 |
| 0016B6C8 | effBTLPartDelete | 168 |
| 00257AC0 | nbActionCheckAfter | 72 |
| 00253D38 | nbActionCheckDeadScript | 160 |
| 002517E0 | nbActionSetTimeList | 116 |
| 0025E9C8 | nbLinkKoukaPacket | 56 |
| 0025EA48 | nbAddKoukaPacket | 168 |
| 00261CA0 | nbAddUnitColKoukaPacket | 128 |
| 00261D90 | nbAddUnitAKoukaPacket | 128 |
| 002622D0 | nbAddReturnKoukaPacket | 112 |
| 002638A0 | nbMakeUnitFadeOutPacket | 116 |

The list-unlink body's contiguous span is 72 bytes; its recognized body is
68 bytes because the original listing leaves a four-byte hole. Transfer checks
retain the whole contiguous span rather than silently skipping those bytes.

## Effect ownership and teardown

The effect's cut-list head is word+C40 and its count is word+C3C. Each cut
holds its owner at+4, successor at+11C and sixty part-pointer slots at+20..+10C.
Deletion calls the actual recovered part destructor for every nonnull slot,
unlinks the cut, decrements the live owner count, invokes the original diagnostic
formatter and releases the cut through the real pool. Unlink compares the
sign-extended loaded pointer against the complete raw64 argument; dirty upper
lanes can prevent unlink even though the later low-address release still runs.

The effect destructor captures a cut's successor before deleting it, then
releases two inline part banks separated by618 bytes. Their counts are unsigned
halfwords at+74/+68C; rows begin at+80, stride24, and markerFFFE skips deletion.
The effect's memory handle at+C38 is released through actual coalescing code.
The outer effect object itself is not freed by this routine. State21 calls that
destructor before clearing context+74 and requesting state22.

## Native packet ownership and death progression

The real pool allocates each64-byte kouka packet. Construction initializes only
bytes0..2F, preserving the final16 bytes; it sets word20 toFFFFFFFF. List head
and tail are data+8/+C, count is data+4, and packet next/previous are+C/+10.
Empty append does not initialize a previous link. Actual reload order is
retained, including the compared packet/data aliases.

Color and alpha packets use kinds5/7 and form+14, flags+2C, time+28. Return
packets use kind11, data+1C and time+28. The fade pair computes its second frame
with32-bit addition and sign extension before constructing the actual alpha
packet. These native context pointers differ from HD's unique-ID ownership.

State19 returns0 while its process at main+104 remains in the original process
queues. When absent, it clears that field, constructs the actual color/alpha
pair at frames0/10 and return packet at25, updates the timeline from the form's
signed halfword+92, requests state18 and returns1. State18 completion checks
(`CHECK1` in Unity) are still pending; the comparison ends at that real
transition request. The separate Unity `READY` methods are different roles.

Timeline slots start at context+88, stride8. Their two halfwords are handled
with signed raw64 argument comparisons followed by32-bit sign-extended addition
and wrapping halfword stores. Negative end skips the final ordering correction.
This is not replaced with the HD implementation's simpler managed arithmetic.

## Reference evidence and SMT transfer

Thirteen Unity roles are reviewed in [the reference report](battle-action-finish-matches.json).
They support identities and intent; native layouts, pointer ownership, integer
widths and unchecked behavior remain authoritative. The pinned
[randomizer notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
supply USA-build/file-offset context. The DDS community's
[source-unit research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md)
reports substantial battle-code rewrites; it supplies compiler and engine context
without proving these Nocturne packet layouts transfer.

The [independent transfer check](battle-action-finish-transfer.json) resolves
Nocturne0016B6C8 to DDS00161790 across all168 bytes, relocating only the JAL at
offset92. The already checked original part-dispatch tables independently
constrain Nocturne00175A08 to DDS001629F0; both original table hashes are checked
again. No other selected complete counterpart resolves. DDS execution is not
claimed. The structurally matching DDS accessor searches `Admini`, while our
kouka accessor searches `nb_kouka`; that dependency identity is excluded.

## Validation and remaining work

[Original-instruction comparisons](battle-action-finish-validation.json) execute
3,259,931 steps and check17,810 ordered real part/PCP callbacks,128 original
action-update callbacks, declared RAM, raw64 returns, Status, primitives and
defined floating/vector state. Cases include empty/nonempty lists,60-slot cuts,
FFFE skips, real pool allocation/free, memory-handle neighbor states, backed
aliases, dirty upper arguments and512 timer-boundary cases. Finite lists and
selected compiled callback kinds are covered; arbitrary corrupt ownership and
unrecovered callback bodies remain outside these inputs.

[Affected comparisons](battle-action-finish-regressions.json) pass another3,392
existing process/recursive-cleanup cases on the rebuilt host, with current
source, verifier, DLL and vector hashes checked. Rolling outputs were replaced
in place; no checkpoints or duplicate captures were created. Full readiness,
actor chooser, kouka execution, message progression, physical gameplay and a
matching executable remain outstanding. The current dispatch audit identifies
73 pending bodies /13,268 bytes in the state18 direct dependency closure,
including its entry/update callbacks. Its native pad gating and unsigned
countdown are checked as static leads; no additional compiled credit is claimed.

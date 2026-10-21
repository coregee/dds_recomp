# Compendium registration and list construction

The current target is eight previously unrecovered routines plus two actual
sorting callbacks. The eight bodies contain 416 instructions / 1,664 recognized
bytes. The two callbacks add 96 instructions / 384 bytes. All ten now execute
within the 538-unit main build and are [published](compendium-records-publication.json). The current union is 2,682/9,062 recognized functions, 454,044 recognized bytes. The existing 66-instruction native helper receives no additional identity credit.

The [saved-project repair and export](compendium-callback-inventory-refresh.json)
recognizes both callback functions at `00219C40` and `00219D00`, bringing the
inventory from 9,060 to 9,062. A fresh read-only reopen verifies the exact
192-byte bodies. All 9,060 earlier function metadata fingerprints and all
27,180 earlier assembly/C/JSON export files remain unchanged. Recognition alone
does not establish recovered C behavior.

The [Unity/community study](next-subsystem-after-fusion-core.json) records the
source leads and inspected community revision. Structural comparison corrects
the stale fuzzy-match winner for `00216C08`: Unity `DebugRegist`, rather than
`CalcPhaseRegistAll`, is the relevant role. The PS2 additionally decrements a
positive first parameter in its private unit copy. Community event-flag notes
provide context; native instructions establish the record layout and behavior.

The [targeted Unity callback study](compendium-records-HD-callback-study.json)
adds metadata-named native bodies `182161390` (race first) and `182161190`
(level first), exported read-only from the existing PC project. They corroborate
the key ordering, signed 16-bit indices and unsigned 16-bit saved levels. HD's
race-first comparator additionally remaps demon `00BF` to race `26`; neither
complete PS2 callback contains that rule. HD managed field offsets, object
checks and boxed indices are also distinct. These references guide naming;
the PS2 instructions remain authoritative for the reconstruction.

## Native data and control

The serialized compendium record is 176 bytes; the source unit is 236 bytes.
Game offset `11E80` holds the count, and records begin at `11E90`. The native
capacity is 184, making the record end `19D10`, within the already backed
`20000`-byte game region. Reserved bytes and the rest of ordinary RAM remain in
the comparisons.

`00216C08` is a genuine zero-argument void routine. Its 272-byte frame contains
a real guest-backed unit copy passed to registration. `002197B0` takes three
arguments and adjusts the selected list index, page position and pixel offset.
The copy routine `00219FC0` clears its destination before reading the source;
aligned, unaligned and overlapping cases retain that ordering.

Both callbacks load signed 16-bit indices, then read the live game pointer,
serialized records and original descriptors. `00219C40` sorts race ascending,
then saved level descending. `00219D00` reverses that priority. They return raw
64-bit sign-extended -1, 0 or 1. The former also clobbers T0; independent liveness
analysis checks that effect at all 24 qsort callback sites. No precomputed keys,
host sorting or supplied comparison results are used.

The probe extends only the finite callback boundary with two reversible edits.
All 618 original qsort instruction statements remain unchanged. Actual callback
receipts preserve call site, target, raw arguments and result in order. The
canonical qsort now contains those same two dispatch edits. All 535 other
previous object files remain unchanged. The updated generator reproduces the
sorter, retaining its previous arithmetic trap boundary and all old callbacks.

## First execution and dependency repair

The [original capture](compendium-records-original.json) first passed all 896
authored cases over 2,432,211 original instructions, including 24 continuations
and 40 additional calls. The first actual C run completed every case: 892 passed
and four failed at the guest diagnostic FILE cursor. It compared 29,721 real
comparator calls and 117,462,016 ordinary RAM bytes.

The [compact failure observation](compendium-records-capacity-gap.json) records
the four cases. Original full-capacity registration writes 120, 120, 60 and 180
diagnostic bytes respectively. The older typed `fclEncycRegist` projection
updates a host diagnostic counter but omits those guest FILE/buffer changes.
The original native helper at `00216A18` calls the actual formatter and disabled
diagnostic routine. It also tests the complete 64-bit overwrite argument.

The repair recovers that complete 66-instruction helper as a native variant
within this family, retaining the genuine frame and registered dependencies.
It receives zero additional identity credit because the entry was already
registered. The input plan adds 128 direct helper cases, preserving the existing
896 BEFORE rows. These cover full capacity and overwrite arguments whose low
32 bits are zero while their upper bits are nonzero.

The real unit-to-record helper uses disjoint unit and serialized-record objects
in these cases. Arbitrary partial overlap between those different representations
is a separate unproved domain. This does not restrict the explicit overlap
tests for the raw serialized-record copy routine.

## Current validation and limits

The expanded original capture passes 1,024 cases over 2,497,867 original
instructions. The repaired probe C passes all 1,024, comparing 29,721 ordered
callback receipts and 134,242,304 ordinary RAM bytes. All four prior capacity
failures and all 128 direct registered-helper cases pass. The actual 538-unit
main comparison also passes all 1,024 cases. All eleven native interfaces were
saved, reopened and exported; the existing helper receives no new identity.
The older sorting/fusion suites pass all 5,012 cases on this build. The broad
413-function/462,684-case regression also passes on the current build. Exactly ten new identities are registered, alongside six qualified shared SMT fingerprints.

The independent stored-results audit finds no unvisited non-delay instruction
addresses among the 578 recovered members in this cohort. This is address
coverage, not exhaustive branches, aliases or inputs. The reused sorter's
broader control paths have separate existing comparison evidence.

Canonical sign-extended guest pointers satisfy independently checked sorted-key
postconditions. Deliberately dirty upper-64-bit pointer cases instead preserve
the original raw behavior: qsort compares full-width addresses but also uses
word pointer arithmetic. Some such inputs return an unsorted permutation,
including case 515, without a C/original mismatch. These cases remain covered
as raw native memory domains, without claiming retail pointer validity.

Returning semantic comparisons check defined results,
completion, ordinary RAM, immutable tables, callback order, Status, FCSR
value/condition, primitive counters and stack balance. They do not establish
complete volatile banks, arithmetic FCSR exception flags, all private-frame
bytes, physical UI behavior or exhaustive inputs.

The capacity cases remain in the suite. No source loop cap, fabricated formatter
answer, altered original table or expected result replaces the original behavior.

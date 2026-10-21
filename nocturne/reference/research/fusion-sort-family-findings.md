# Native fusion sorting

The five recognized bodies at `002D4860`, `00213280`, `002132C0`,
`00213350` and `002133A0` are recovered and tested in the main build.
Two byte-bounded comparator leaves at `002131E0` and `00213230` are also
implemented and tested. They remain outside the 9,060-function census and
receive no additional identity credit.

The [publication](fusion-sort-family-publication.json) records that sorter
milestone and its historical 534-source totals. The [original/main comparison](fusion-sort-family-main-C-validation.json)
covers 1,248 cases, 153,029 actual comparator calls and 81,788,928 ordinary RAM
bytes per build. Each comparator receipt checks its original call site,
target, raw arguments and raw result in order. The 160 skill cases also check
the complete 96-byte guest scratch array, including dirty padding. All 10,122
affected older cases pass on the 534-source main build. All five native
interfaces were saved, reopened and exported as void routines.

## Source and research

The retained Unity methods corroborate pack, unpack and inheritance-skill
sorting roles. Their managed `Array.Sort` does not establish the native
algorithm or layout. The native qsort has Bentley/McIlroy structure, matching
the family in [newlib's implementation](https://chromium.googlesource.com/native_client/nacl-newlib/+/74e90df35c103a89cda36a2029cad7994190c212/newlib/libc/search/qsort.c).
This establishes a useful source lead, not the exact original SDK revision.
Inspected revisions and community context remain in the
[pre-recovery study](full-fusion-qsort-next-study.json).

Native code preserves 24 call sites, eight-byte and byte swap paths, unstable
equal-key order, left recursion and right tail iteration. It calls the actual
recovered comparators. No host sort or supplied comparison answers are used.
Pack/unpack preserve interleaved alias order. Skill records contain a skill,
attribute and untouched padding byte; zero skills sort last. Descriptor records
sort by unsigned race ascending and level descending. Their default count is
the original global value 384, rather than an invented algorithm limit.

## Limits and transfer

The [original sorter review](fusion-sort-family-results-review.json) records ten
then-unvisited non-delay instructions in the aligned multiword swap arm of the
no-swap insertion fallback. All ten are reached by twelve supplementary sorter
cases in the later [fusion review](fusion-core-results-review.json), with actual
original/current-536-source C agreement. Delayed instructions are not separately sampled.
The preserved late division/BREAK paths are outside the returning input domain.
Complete volatile registers, private save frames, HI/LO, arithmetic FCSR flags,
physical hardware and gameplay are not established by these comparisons.

The shared SMT signatures are search leads. Each other game needs its own
instruction, table, ABI and callback-order checks. The later 29 fusion bodies
are tested and registered in their [own publication](fusion-core-publication.json);
the sorter batch awards no duplicate credit for them.

# Battle order, recruitment and enemy append

Three complete native bodies are recovered as source: `002580E8` (101
instructions), `00259180` (56) and `002594B0` (59). Their 216 instructions cover
864 recognized bytes / 872 span bytes. Both strict compile profiles and the
independent source, input and transport reviews pass. The [three-function publication](battle-roster-publication.json) brought
recovery at that milestone to 2,685/9,062 functions, 454,908 recognized bytes
and 540 source units.

The [HD/community study](battle-roster-HD-community-study.json) corrects the
order counterpart to Unity `nbMisc.nbSortOrder` at `18274F760`. The earlier
`nbAddOrder` lead includes insertion before its sorting stage. Native sorting
does not insert a new order entry. Unity's enemy append also takes a third
`formindex` argument; the PS2 function has exactly two raw argument slots.

## Native structures and calls

Sorting resolves the actual priority-`3FA` process through delayed-start,
active and delayed-destroy queues. It uses the resulting Main object, its
128-byte form array at `+10`, and signed-byte order entries at `+48`. Actual
party or enemy units supply parameter 4. Higher parameter values precede lower
ones; ties use ascending signed form field `+2`. Negative order bytes are
skipped. Preserve pairwise swap order rather than replacing this with a host
sort or assuming stability.

Recruitment checks physical occupied slots 4–15 against capacity, calls the
stock search and ignores its result, then constructs a companion in the first
vacancy. It invokes the recovered native compendium helper `00216A18`, followed
by list append. The new family uses that complete helper, including actual
buffered diagnostic writes and the full-width overwrite guard.

Enemy append searches ten 236-byte units. A full array returns sign-extended
`-1`; otherwise the real companion constructor runs before flag 2 and the
original descriptor HP/MP fields are copied. Guest effective addresses use
original word arithmetic while public argument slots retain all 64 bits.

The [pinned randomizer notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
provide descriptor and recruitment context. Their 60-byte row view begins
12 bytes before the native descriptor view used here. Three explicit file
locations have been reconciled against original ELF bytes and the `FF000`
rebasing in this region. Note labels and index radix remain separate leads;
the original descriptor loads supply fixture data. Modified recruitment
policies do not supply original expected answers.

## Current evidence

The [BEFORE inputs](battle-roster-inputs.json) contain 608 roots: 256 order,
192 recruitment and 160 enemy cases. They include all vacancy positions,
coherent capacities, duplicates, full compendium diagnostics, guarded null
sources and backed inactive-destination aliases. Thirty-eight connected
sequences add 175 calls: 133 with defined raw returns and 42 genuinely void.
Every call retains its own completion/result ownership and consumes real prior
state without intermediate input patches.

The first original run passed all 608 cases over 2,455,848 instructions. The
first C comparison stopped before any target call because default Gson
serialization omitted nullable child metadata. The [compact observation](battle-roster-serialization-gap.json)
records this transport issue. The scoped driver now preserves explicit nulls;
all original fixtures and semantic comparison assertions remain unchanged.
The fresh original run also passes608/2,455,848steps. Its complete normalized rows, including all results and RAM, match the prior run exactly; only explicit null metadata differs. The actual probe and540-unit main C each pass all608 cases/783 calls and compare94,670,464 ordinary RAM bytes.

The first actual C call also exposed a missing existing process-routing activation flag. The [routing observation](battle-roster-process-routing-gap.json) and [review](battle-roster-process-routing-review.json) establish the repair: save/set/restore `g_scriptProcessActive` along with the other three modes. The actual process-data helper now reaches the same authored guest RAM through the existing ScriptProcess/ScriptConstruction/Effect resolver chain. No game helper answer, fixture relocation or canonical provider change is used.

All three native interfaces are saved/reopened/exported. All538 earlier objects remain unchanged;3,556 retained compendium/unit/work-access cases pass, including four actual expected BREAK7 cases. The broad413/462,684 proof remains the passing538-unit epoch. The independent audit observes zero unvisited non-delay PCs among216 source members, not exhaustive paths or inputs. Buffered diagnostics appear in21 cases/1,980bytes; physical console delivery remains unverified.

These finite proofs do not establish physical gameplay, exhaustive branches or
aliases, complete volatile banks, private-stack equality, arithmetic FCSR flags,
or admission of the larger battle-skill family. Shared structures remain search
fingerprints until checked independently in each related SMT executable.

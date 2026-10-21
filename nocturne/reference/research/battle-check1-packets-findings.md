# CHECK1 packet windows, model queries and death-script queue

Thirteen complete native routines in `src/battle_check1_packets.c` add2,084 recognized body bytes. All5,376 original-instruction comparisons pass, reaching all407 selected main instruction addresses and executing2,074,125 original steps. The build passes with warnings treated as errors. Full declared RAM, raw returns, Status, FCSR, allocator primitives and defined vector state agree. Actual process lookup, packet allocation/append, sound suppression, work/status/death queries and action-stack writes execute.

All thirteen interfaces are saved in the working Ghidra project, checked after reopening, and merged into the corrected current exports. The affected status provider's5,888 cases also pass against the rebuilt host, using its existing original capture. [The regression report](battle-check1-packets-regressions.json) checks current sources, verifiers, inputs and vector hashes. One rolling packet capture was replaced after adding missing combined-status branches; no checkpoint, project/source copy, duplicate capture or new full suite was created.

The read-only export logs a processor `rom0` memory-block fixup error during temporary language replacement. Its own checks preserve all8,980 functions and validate unsigned DIVU; all13 selected routines decompile with no decompiler messages and the export summary records zero failures. The temporary changes are discarded. Original-instruction capture and saved-project interface checks have no errors. This exporter diagnostic is retained in the rolling log rather than treated as evidence of a failed selected export.

## Community context and original inputs

The pinned [Nocturne randomizer implementation](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/nocturne.py) supplies the original basic-AI record boundary and A4 stride. Native death consumers independently establish unsigned script/event halfwords at+ A0/+ A2. The new queue cases reuse this checked layout:384 cases retain the entire original384-record table unchanged before and after execution. Some take the native type5 gate, so this is an unchanged-input case count rather than384 queue insertions or every ending being consumed. Another128 cases exercise constructed unsigned endings and eligibility boundaries.

All event getter cases retain the original table at00527274 and its backed prefix unchanged. Independent expected values use the signed low32 remainder to select original halfwords. Original negative event IDs can read before the nominal table; the implementation preserves that behavior.

The pinned [DDS source-unit research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md) supplies compiler and related-engine context while warning that battle code was substantially rewritten. Direct links, inspected revisions and fetched hashes are retained in [the reference review](battle-check1-packets-matches.json). Community BF command IDs do not identify packet kinds merely because the numbers agree.

The [broader research inventory](community-research.md) also adds five pinned HD mod files and twelve hook leads from MatthiewNocturne. Those are further affinity, press-turn and presentation references; their injected behavior is not incorporated as original PS2 code.

## Native behavior retained

| Area | Original behavior established by instructions and comparisons |
|---|---|
| Model controller and length | Model word+18 points to a resource whose word+14 heads a linked list. Next is word0; signed LH group+28 equals the complete incoming raw64 group. First match wins. Length reads controller word+8 then unsigned LHU header0; missing controller returns0. HD fixed-length/shared-stub/animator candidates are rejected for this native length helper. |
| Number and text windows | Original packet kinds hexadecimal10/16 use signed LB kind checks, signed word owner/form equality against full64 inputs, and signed LH start+duration compared with the full64 incoming frame. Successor word+C is cached before writes. The low16 difference is stored, then clamped to0 when bit15 is set. Actual allocation follows traversal. |
| Text sound | Full64 type exactly4 emits sound1000A through the real deduplicating sound helper. Dirty upper bits reject the predicate. There are128 consecutive-call preludes for each window routine,256 total. |
| Bad effects | Kind17 maps individual status bits1..400 to slots1..11; combined or dirty-high operands take default0. Bad-damage composition calls the actual float32 F12 helper with17.0, then effect/status packet helpers. Recovery uses the actual masked bad status, caches signed form eligibility, clears any bad status and emits cure packets only for single bits1..800 on eligible forms. Combined-mask default branches are covered. |
| Death packets | Form flags1/40 gate processing. Signed party index selects the party; actual work is cached before party flags30 are set. The event query follows. Return-packet allocation uses the original event/work flag condition or full64 force exactly1. Original unchecked accesses remain. |
| Event fade fields | Low32 signed DIV remainder by100 selects stride28 at00527274; unsigned halfwords are at+0,+2,+6,+4 for time/out/in/stop. These are integer table queries, not float/model functions. |
| Enemy death scripts | Native type5 exits early. Enemy forms4..13 require active flag1 and actual zero-HP death eligibility. Context/main/form pointers reload per iteration; unsigned nonzero death scripts are queued through actual PushAction with signed party index. |

## Shared SMT results and remaining work

The full72-byte controller body001DD5A8 is byte-identical to DDS00217E10. The complete44-byte length body001DDBA8 matches DDS00218410 with only JAL+8 relocated to that independently checked controller peer. [The transfer report](battle-check1-packets-transfer.json) checks both original spans and the exact call destinations. There are no relocated global/HD animator assumptions. This establishes a static shared role and field correspondence; DDS execution remains untested. No selected complete packet/death/queue DDS counterpart resolves. A generic process-getter peer searches `Admini` rather than `nb_kouka`, so its kouka identity remains rejected.

Current source recovery is1,704 of8,980 recognized routines (18.976%),253,168 recognized body bytes,126 focused reports and743,967 aggregate comparisons. The [direct action frontier](battle-action-dispatch-frontier.json) contains398 pending bodies /93,208 bytes. CHECK1's direct closure contains12 pending bodies /6,444 bytes, including the entry/update callbacks00257488/002577D8.

Its separate [hit-effect frontier](battle-check1-effect-frontier.json) reads the original56-byte callback rows at0031BF00: constructor+0 and frame-query+20 for ten hit-effect subtypes. All20 callback roots remain pending, with59 recognized direct descendants /6,800 bytes. This currently has no pending-body overlap with the twelve-body direct closure. Further indirect/asset-dependent calls may expand either graph. Implement the actual constructors and model/part dependencies; a small direct count does not imply CHECK1 completion.

The comparisons use bounded backed RAM and finite lists. Corrupt lists, outer scheduling, physical battle execution, a matching executable and full-program recovery remain outstanding. HD managed fields, copy-number logic and guards are retained as differences, not copied into the PS2 implementation.

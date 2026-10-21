# Unchanged original battle-script integration

All 141 procedure entries in the executable-embedded battle BF now have passing
original-instruction/C comparisons in two constructed battle states, through
both `ps2ScriptTrace` (`0010B520`) and `scrScriptProcess` (`0010A268`). The
564 cases each retain state across four initial invocations, then continue
while the original WAIT command is pending: 5,076 native invocations and
12,876,108 original instruction steps. This is integration evidence for
existing recovered bodies; it adds no new functions to the recovery count.

## Original inputs and community context

The resource is read unchanged from `SLUS_209.11` at file offset `003F1800`,
RAM `004F0800`, with section-derived extent `00035BF1`. Its SHA-256 is
`134c92c255f3b921105ca03f5639b80f4da2675da263fee80b04bdaf1990a8a7`.
The code begins at resource offset `00016A30`, RAM `00507230`; its SHA-256 is
`693315b2e1ec6360db743c5355dc39c3f64bf2904cb69615c50d7bbc804cf75a`.
The driver checks the full input and unchanged bytecode after execution.
Message-resource pointer relocation is actual native behavior.

The [community inventory](community-research.md) records inspected revisions
of the Nocturne randomizer and Atlus Script Tools. Their opcode, command and
AI-record leads informed the native layout audit and the original procedure
selection. The [original Hardtype discussion](https://gamefaqs.gamespot.com/boards/582958-shin-megami-tensei-nocturne/74938870?page=16)
identified executable-embedded BF AI separately from basic enemy decision
records. The native corpus contains 141 procedure records, 27,795 decoded
instructions and 63 used command IDs. Native section bounds and 32-byte label
records remain authoritative where generic format descriptions differ.

Of the 141 procedures, 121 have an association in inspected original AI
headers. Those associations supply actors for 484 cases across both runners.
The other 20 procedures use explicit standalone construction for 80 cases.
An AI-header association does not establish real battle scheduling or prove
that a helper is normally entered as a top-level procedure.

## What agrees

The [validation report](battle-retail-scripts-validation.json) records all
564 passing cases and all 33 selected main addresses in `ps2ScriptTrace`.
The comparison checks each invocation's raw return, final declared RAM,
Status/primitives/FCSR condition, ordered VM/predicate/libc traces, all vector
registers with ACC/overflow/Q, and native callee saves. Intermediate RAM after
each invocation is not separately captured.

Actual dependencies execute process lookup, allocation, font binding,
message initialization, AI startup, target selection, predicates, camera and
battle helpers. Observations include 33,388 VM calls, 1,732 predicate
callbacks, 95,440 VU instructions, 12,855 COP1 comparisons and 77,268 defined
vector/ACC/Q values. The test memory provider supplies one coherent address
space across those recovered modules; it does not substitute game callback
results. All 493 pinned direct dependencies and 35 VM opcode targets are
checked against original body bytes.

The two battle variants use HP 100/25, MP 100/5, level 20/80 and turn 0/8,
with original actor/skill/encounter/AI tables. Pose/control backing and a
cached font view are constructed test state. These comparisons do not prove
original glyph decoding, physical display or asset-to-frame execution.

The [affected regression report](battle-retail-scripts-regressions.json)
records another 12,732 passing comparisons against the latest host build:
battle presentation 6,400; AI startup 1,600; message request 860;
script lifetime 1,856; panel construction 2,016. Those are rechecks of existing
cases rather than new aggregate recovery credit. Canonical game source is
unchanged by this integration batch.

## Original paths reached and remaining work

The [path report](battle-retail-script-paths.json) records 6,548 of 27,795
original instruction words and 49 of 63 used command IDs reached in these
states. The separate [command-body census](battle-script-frontier.json)
already covers all 63 used command bodies and 7,178 static occurrences.
Body comparison and original-script branch coverage are different measures.

Of 282 direct-runner cases, 196 reach a terminal return within four
invocations. Initially another 86 yielded: 65 at command14/WAIT and 21 at
command0/MSG. Guarded continuations now advance all 65 WAIT cases to MSG in
each runner. The native timer advances without injected values: 2,820 extra
callbacks in total, at most 31 invocations per case. The VM yields with
return1; its process callback yields with return0. Both guards use those
actual contracts and observe the live command before calling again. The
256-additional-call limit is never reached in these states.

All 86 unfinished direct-runner cases now wait at MSG, spanning 53 procedures
with at least one yielding variant. No external action or message completion
is injected. Initial calls after a terminal return test the callback contract without
claiming that the outer scheduler would dispatch a deleted process again.

The [current frontier](battle-retail-script-frontier.json) lists the fourteen
command IDs not yet observed in original paths. Their native bodies already
have comparison evidence. Next work is to:

1. Advance MSG through recovered message/font update paths and explicit input
   boundaries while retaining original bytecode and page data.
2. Exercise additional actor, turn, HP/MP, status and support states to reach
   the remaining original branches and command IDs.
3. Recover the real actor-start callback dispatcher before treating AI-header
   associations as gameplay scheduling.

The [message-state audit](battle-message-boundary.json) observes completion
byte1 in all 86 pending cases. In 82 cases the window is opening
(phase0x100, message phase2); four have message phase3 without a window phase.
The MSG command waits for a negative completion byte. Actual window updates,
font drawing and message updates must obtain that state. Input trigger bytes
at `002F5831..33` are outside the current declared RAM spans; the next frame
integration must add explicit backing and input observations.

For example, original `ai_0` is `PROC`, `PUSHIS`, `COMM MSG`, `END` and waits
at MSG in these states. Its header association alone does not establish when
the real battle dispatcher chooses that procedure. The [new dispatch audit](battle-action-dispatch-findings.md)
confirms that the qualifying default enemy route selects ordinary AI state2
for procedure zero and scripted state3 for a nonzero header. Complete decisions,
outer scheduling, physical PS2 runtime and a matching executable remain
outstanding. Shared SMT findings still need the other executable's bytes
checked before transfer.

## Current outputs

The driver is `tooling/recover_battle_retail_scripts.py`; the path frontier
auditor is `tooling/audit_battle_retail_script_frontier.py`. Current inputs and
vectors reside in `analysis/battle-retail-scripts/` and are rolling outputs.
Captures read the working Ghidra project without mutation. The separate
action-callback discovery is saved in place. No checkpoint, project
copy, frozen source tree or duplicate capture was created.

The current progress audit remains 1,582 compiled functions, now out of 8,980
recognized functions (17.617%) after discovery of an action-table callback,
covering 229,464 recognized body bytes. Its 117 focused reports
contain 252,505 cases; combined with the earlier 462,684-case full run, the
aggregate is 715,189. This batch has not repeated the full suite.

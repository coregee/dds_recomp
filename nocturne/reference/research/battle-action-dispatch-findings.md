# Original actor AI dispatch and action callback frontier

The original battle action chooser distinguishes ordinary enemy AI from
executable-embedded BF scripts. When its default enemy route reaches
`002537DC..002537F4`, AI-header procedure zero requests action state2;
a nonzero procedure requests state3. Earlier special-action, status,
negotiation and debug branches can select other routes. This is an original
instruction finding, not a claim that every actor actually takes this branch.

Of the 384 original headers inspected using the community randomizer's A4
record lead, 140 have procedure zero and 244 have a nonzero procedure. The
nonzero headers refer to 120 distinct original BF procedures. Previously
testing all 141 procedures directly remains useful VM integration evidence,
but a zero-header association alone does not mean ordinary enemies execute
the `ai_0` BF procedure in gameplay.

The [reproducible audit](battle-action-dispatch-frontier.json) checks 32
original instruction words, the header boundary, current canonical source
hashes and ten named Unity leads. It carries the randomizer source links,
inspected revision and content hashes from the [community engine audit](community-engine-audit.json).
The original retail bytes decide dispatch; HD's managed layouts, guards and
alternate script-selection additions remain separate.

## Deferred transition and callback table

`00257CC8` writes the requested state byte at context+9. `00257CD0` performs
the deferred transition through `00257C80`; the entry dispatcher writes the
current state at +8, clears +9/+A/+C and invokes the original enter callback.
Native indices are signed bytes, multiplied by eight, with no table bounds
guard. The original table is at RAM `003FA7C0`, file `002FB7C0`.

The audit inspects 23 enter/update pairs through state22. States16/17 have
null pairs. This prefix does not prove the complete table extent or justify
adding a clamp. State2 enters `00253BF8`, which resets actor action/skill and
tail-calls the recovered ordinary decision runner `00287CB8`. State3 enters
the recovered `00253C40` header-to-BF startup bridge and updates through
`00253C88`, which waits for script-process absence before choosing the next
action state. Unity's `SetAction_AI`, `SetAction_AISCR` and
`CheckAction_AISCR` corroborate these roles.

The action process calls update callbacks through table+4, marks a deferred
transition when they return nonzero, and advances its native halfword counter
unless it has reached 65535. Recovering this process and its actual callback
dependencies is needed before claiming original battle scheduling.

## Newly recognized callback and recovery priorities

The state1 update pointer at `003FA7CC` identifies `002538A0`, a previously
unowned code entry. Its original prologue, 852-byte span and return/delay
epilogue were checked. The working Ghidra project now owns and decodes all
213 instructions, and the [discovery report](battle-action-callback-discovery.json)
records the saved change. The current assembly, metadata and raw pseudocode
exports are merged into the normal inventory. Unity's `CheckAction_COMM` is
a semantic lead; canonical C and reviewed interfaces remain pending.

The function inventory increases to 8,980. That recognition did not earn compiled
source credit. Subsequent [timeline/completion recovery](battle-action-sequence-findings.md)
adds eight complete routines and 1,245 passing comparisons, bringing compiled
recovery to 1,590 functions (17.706%). The new source covers transition requests,
current/previous sequence access, timeline clear/HP snapshots, scheduler membership,
AISCR completion and actual death-script startup. The 852-byte callback remains
pending canonical recovery.

The subsequent [action entry recovery](battle-action-entry-findings.md) adds four
complete routines and 1,997 passing comparisons. Original state0/2/3/19 enter
targets execute, with 1,229 independently checked native target/context/state
observations. Ordinary entry and its completion check are recovered together;
these explicit requests do not prove full chooser or action-process scheduling.
Current integrated recovery is 1,594 functions (17.751%).

Across the inspected action callbacks and recognized direct dependencies,
the current frontier contains 508 unresolved bodies / 116,096 recognized body
bytes at current compared boundaries. Additional indirect/unrecognized code
can expand it. This gives broader context rather than making that whole
frontier a single recovery batch. Continue the stock-selection renderer and
its actual dependencies, then integrate the action process
under qualifying actor states while following the remaining original BF
[message-progression boundary](battle-retail-script-frontier.json).

DDS action-state numbering and callback layouts remain unchecked. The new
membership routine has a uniquely verified complete DDS counterpart after three
checked queue relocations; the other seven selected timeline/completion bodies
have no complete match under the current strict constraints. Further transfer
still requires original instructions in the other game.

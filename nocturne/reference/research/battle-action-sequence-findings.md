# Native battle timeline and AI completion recovery

Eight complete original C routines compile and pass **1,245 original-instruction
comparisons**, executing 1,137,915 native steps. They cover 672 recognized body
bytes and every reachable selected main address: 128 reached, with two impossible
queue-selector branches separately proved. The interfaces are saved in the working
Ghidra project, independently reopened and exported into the rolling inventory.

| Original entry | Recovered role | Cases |
|---|---|---:|
| `00101A08` | `dds3ExistProcess`: original scheduler queue membership | 192 |
| `002514F0` | Clear 32 timeline records | 64 |
| `00251538` | Snapshot HP from 16 formation slots | 128 |
| `00253C88` | Check AI-script completion and request the next action state | 96 |
| `00253D00` | Clear/snapshot timeline and start the death script | 141 |
| `00257BF8` | Read the signed current sequence byte through process data | 272 |
| `00257C20` | Read the previous actor's sequence | 96 |
| `00257CC8` | Store the requested sequence byte | 256 |

## Original behavior and community context

The community DDS scheduler's
[`kwlnTaskIsRegistered`](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/kernel/dds3KernelCore.c)
provides the three-queue membership lead. The inspected revision is
`bec33411543cdc487bad9debdf758f0090a2242c`; its content hash and the original
randomizer AI-record references are retained in the [role review](battle-action-sequence-matches.json).
Nocturne searches delayed-start, active and delayed-destroy queues, compares the
full raw argument against each sign-extended pointer, and follows node+`3C`.
A zero argument does not match an empty queue.

The [transfer audit](battle-action-sequence-transfer.json) resolves the entire
140-byte membership body uniquely to DDS `001019C8`. Exactly three GP-relative
queue operands change; every other instruction word agrees. These relocations
come from the independently checked community scheduler boundary. The other
seven selected bodies have no complete match under the current strict constraints.
This is a useful shared-engine result, with no DDS execution or shared battle
layout/state-numbering claim.

The timeline clear writes halfwords 0/2/4 of 32 eight-byte records at context+`88`,
preserving each final halfword. The HP snapshot visits only 16 slots, clears each
destination before testing flag bits 1/`40`, and resolves signed party/unit indices
through the actual recovered unit getter. Its flag2 precedence and global-unit
path execute in the comparisons.

AI completion depends on actual scheduler membership of main+`104`. Absence clears
that pointer; zero main+`94` requests state7, while nonzero refreshes the timeline
and requests state10. The death-script entry executes actual BF/message/process
construction for every original procedure index 0..140. This checks startup,
without executing all procedure bodies or establishing gameplay selection.

Current sequences return signed bytes; transition requests store only a byte.
The previous-sequence getter subtracts one in 32 bits, maps a signed-negative
result to slot3, and otherwise retains the native unchecked index arithmetic.
HD supplies eight corroborated semantic roles, with managed guards and alternate
script resources kept separate from the original PS2 behavior.

## Evidence and remaining work

[Canonical source](../src/battle_action_sequence.c),
[comparison report](battle-action-sequence-validation.json) and
[saved interface check](battle-action-sequence-abi.json) retain the current results.
Full declared RAM, defined raw64 returns, Status, CPU primitives, returning callee
saves, ordered traces and defined FPU/VU state agree. Finite backed queues/units
and successful allocations bound these comparisons; arbitrary invalid pointers,
cycles and allocation failure remain untested.

The existing 564 unchanged-BF integration cases also pass on the rebuilt host
using their current original capture. Further work is the action enter dispatcher,
ordinary-AI entry wrapper, full action process and actual message frame progression.
Whole battle decisions, physical runtime and a matching executable remain open.

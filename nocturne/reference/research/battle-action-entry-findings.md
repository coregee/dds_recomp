# Native action entry dispatch and ordinary AI

Four complete PS2 routines now compile in `src/battle_action_entry.c` and pass
1,997 original-instruction comparisons. Their names and raw EE interfaces are
saved in the working Ghidra project, checked after reopening, and exported into
the current 8,980-function inventory. The [validation report](battle-action-entry-validation.json)
records source hashes, coverage and comparison boundaries.

| Original entry | Recovered routine | Native behavior | Cases |
| --- | --- | --- | ---: |
| `00253488` | `nbActionSetNone` | Empty state0 enter callback | 64 |
| `00253BF8` | `nbActionSetAi` | Reset actor action/skill, then tail-call the actual ordinary AI runner | 640 |
| `00253C20` | `nbActionCheckAi` | Request state7 and return1 | 64 |
| `00257C80` | `nbActionSetSeq` | Initialize sequence state and invoke the original table's enter callback | 1,229 |

The selected bodies account for 144 recognized bytes. All 30 selected main
instruction addresses execute across 11,570,505 original steps. The new batch
brings integrated recovery to 1,594/8,980 functions (17.751%), 230,280 recognized
body bytes and 718,431 aggregated comparisons. This aggregate includes earlier
dependency and integration cases; the last full run remains 413/462,684.

## Original table and memory semantics

`nbActionSetSeq` writes context byte+8, byte+9, word+C and halfword+A in that
order. Its table displacement comes from the signed low byte of the requested
state, multiplied by eight. There is no native index clamp or null-target guard.
The inspected 23-pair prefix at RAM `003FA7C0` / ELF file `002FB7C0` remains
unchanged before and after every compared call. This does not prove the complete
table extent. States16/17 contain null pairs and are outside the selected valid
requests.

The hosted dispatch executes actual recovered bodies for states0,2,3 and19;
unsupported targets abort. Native execution independently records each JALR
target, raw 64-bit context argument and signed stored state. All 1,229 such
ordered observations agree with the hosted calls. Dirty upper argument lanes
and state values differing by multiples of256 check native truncation behavior.

Ordinary AI sets actor halfword+6A to `FFFF` and +6C to zero before calling the
actual `nbRunAi`. It runs 640 times directly and640 times through state2: each
route includes all 384 unchanged original A4 records plus 256 constructed states.
State3 invokes the actual header-to-BF startup bridge for all 384 original
headers. State19 invokes the actual death-script constructor for original BF
indices0..140. In total, 1,152 cases independently verify unchanged actor records
against the executable. These are explicit entry requests; the outer chooser
and scheduler have not been demonstrated to select them through full gameplay.

The expanded comparison memory originally cleared an executable-backed native
AI switch table. Restoring original ELF bytes before applying the constructed
battle state fixed that fixture error. The current capture passes without
uninitialized reads and with declared RAM writes checked. No game behavior was
replaced to obtain the result.

## Unity and community evidence

Three named HD roles corroborate the ordinary entry, completion check and
sequence dispatcher. Original PS2 offsets and stores decide the recovery;
managed delegates and HD guards are not copied. The native empty state0 callback
has a descriptive alias: the candidate HD empty body is shared by 246 methods
and cannot establish a unique code identity. See [the reviewed mappings](battle-action-entry-matches.json).

The pinned [Nocturne randomizer](https://github.com/nmarkro/Nocturne-Randomizer/tree/f74e85c0f632b751eaf278046884961c618c8541)
supplies the A4 actor/AI record context. The existing [community inventory](community-research.md)
also connects its assembler, the Atlus Script Tools BF reference, original
Hardtype research and the independently checked executable-embedded BF. Their
record associations guide the test inputs; native header consumers determine
how startup works.

The [DDS source-unit research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md)
warns that much of the battle subsystem was rewritten and several proposed unit
projections were rejected. The selected strict complete-span comparison resolves
no new DDS identity: the native empty body has 1,196 candidates and the other
three selected bodies have none. The prior timeline batch's uniquely checked
scheduler counterpart remains valid. The new shared signature records native
entry behavior as a transfer lead, with other-game offsets and state numbers
still requiring independent evidence.

## Integration boundary and next work

All 1,245 existing timeline/completion comparisons and 564 unchanged original BF
integration cases pass on the rebuilt host using their existing current captures.
All registered canonical source hashes pass the current progress audit. Working
outputs were updated in place without checkpoints or duplicate captures.

The full action process at `00257CD0` remains unrecovered. Its flag400 path calls
the stock-selection renderer `0027FD18`; that renderer and its seven direct
dependencies need real implementations before exercising that process path.
The renderer's HD semantic lead is `nbPanelProcess$$nbPanelStockSelect` at
`1823950F0`. Its direct native dependencies are `001ABC88`, `00279A88`,
`00279C00`, `0027A378`, `0027B7A8`, `0027FBA0` and `00282270`.

The current [action dispatch frontier](battle-action-dispatch-frontier.json) has 508
unresolved recognized direct bodies / 116,096 bytes at compared boundaries.
Indirect paths can expand that inventory. Next work follows the actual stock
renderer, update callbacks and action process, together with the original BF
message frame/input progression. This batch does not establish full scheduling,
complete yielding-script decisions, physical gameplay or a matching executable.

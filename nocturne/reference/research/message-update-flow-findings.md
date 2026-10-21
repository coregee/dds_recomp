# Native Message update flow, selection and manager

Six complete bodies in `src/message_update_flow.c` pass **960 original-instruction comparisons**, covering **1,608 recognized body bytes** and all **309 main instruction addresses**. The C builds with warnings treated as errors. All six interfaces are saved directly in the working Ghidra project, independently reopened and checked; current exports are merged in place.

| PS2 entry | Recovered routine | Reviewed Unity role | Complete DDS span |
| --- | --- | --- | --- |
| 001CFF98 | ps2MessageCalcFlow | CalcMesFlow | 0019E0F8 |
| 001D0118 | ps2MessageCalcMessage | CalcMessage | No complete match under the current mask |
| 001D02C0 | ps2MessageCalcSelect | CalcSelect | No complete match under the current mask |
| 001D05F0 | ps2MessageSelectItem | SelectItem | No complete match under the current mask |
| 001D0740 | ps2MessageSelectItemMove | SelectItemMove | 0019E9D8 |
| 001D0FF8 | ps2MessageCalcManager | CalcManagerProc | 0019F660 |

The flow executes window, message, selection and cursor updates in that order. The manager reads the list head at **56BE70**, passes each node's payload at+C to that actual flow, reloads next at+4 after updating, and returns zero. Its native interface has no arguments; Unity's extra procedure argument is not used in the observed body. The native manager does not increment the draw manager's frame counter.

Message updates require signed phase byte+34 to equal one. Completion phase `(flags & 7) == 4` increments+1CC, honors the800000 stop flag and100000 cursor suppression, then checks trigger bytes **2F5831/33**, held input **2F5832** and the five-tick threshold. Sound9 is conditional on the stored font result byte. Actual cursor initialization resets the adjacent+1CC counter as well as its cursor fields. The next page is narrowed to a halfword and compared as signed16. A remaining page commits the real variable table, optionally binds style8, executes the actual page/parser/font reconstruction, updates the speaker window, and restores low phase bits to3. Noncompletion input raises the actual message and speaker request speeds unless400000 suppresses it.

Selection states1..4 preserve the native order and wrapping. State1 compares signed wrapped message/selection coordinates and may scroll by-40hex before the400 window-phase gate; this differs from the HD order. State2 uses cached entry flags to decide eligibility, executes actual input and sound, trims the real font group, converts the selected masked index, sets the cursor and transitions to phase3. State3 subtracts10hex from the narrowed alpha and compares its signed result; state4 scrolls by+40hex until the nativeA88 threshold, or completes immediately without a message font. HD scroll distances, layout and UI behavior are not substituted.

Selection input gives up priority over down, including the case where an up repeat is blocked at the edge. Repeat tests mask0x02; the signed trigger byte allows wrapping. A move clears the old font group, wraps against signed count, highlights the new group, stores current/default indices and plays sound1. The original direct-move argument is signed in the full64 register, so dirty upper lanes can change its direction. Confirm precedes default keys and plays sound8. Default-key selection executes the actual signed trigger/mask walker and real highlight changes.

The comparison uses192 message cases,192 selection-state cases,256 input cases,128 direct moves,96 complete flows and96 manager cases. It executes **68 real page reconstructions**:48 direct,12 through the complete flow and8 through the manager. The manager processes **96 message instances** across zero/one/two-node lists. These are generated two-page text fixtures with actual cached original FNT glyphs, real parser free pools and recovered dependencies; they are not an exhaustive shipped-message or gameplay test.

Full declared RAM, defined raw64 returns, Status, CPU primitives, saved registers and ordered kernel/cache observations agree. Independent checks cover page indices, counter reset, selection wrapping and each sound packet's ID/volume/pan, producer index and token. **564 actual sound plays** consume **72,192 supplied TagLo operands**. UI bank0 is resident and the command queue is asynchronous with space; bank loading and waits retain their separate sound proof. Each play's originally unwritten packet+4 word is replayed from the observed private native stack context. It is not recovered logic or evidence of matching compiled stack layout.

Three complete DDS spans resolve with four agreeing callee constraints. The complete CalcFlow caller also supplies role leads for DDS window **0019E130**, message **0019E320**, selection **0019E4F8** and cursor **0019EB18**. These callee bodies do not have complete matches under the current mask and are not promoted. The manager's list-head mapping is **56BE70 → 3D6EB0**. These are static transfer findings, not DDS execution evidence.

The current static Message update graph now has **zero unresolved bodies / zero unresolved indirect sites**, stopping at source-current compared routines. This does not establish every production callback, update scheduling, actual IOP completion, physical rendering/audio or a matching executable. Overall recovery is **1,124 / 8,975 functions (12.524%)**, with **617,178 aggregate comparisons** and476 reviewed Unity counterparts. The last full run remains **413 functions / 462,684 cases**; no new full-suite run is claimed.

Current evidence: `message-update-flow-validation.json`, `message-update-flow-interfaces.json`, `message-update-flow-abi.json`, `message-update-flow-matches.json`, `message-update-flow-transfer.json`, `message-update-frontier.json` and the rolling `message-update-flow/` capture. No checkpoint, project copy, frozen source tree or duplicate capture was created.

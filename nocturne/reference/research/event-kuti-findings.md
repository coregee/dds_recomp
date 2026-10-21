# Native scene lookup and message-driven mouth motion

Nine complete routines in `src/event_kuti.c` compile and pass **1,534 original-instruction comparisons**. All **135 main instruction addresses** execute, covering **716 recognized body bytes**. The cases execute 2,973,233 original steps and observe 533 VM indirect calls. Evidence is `event-kuti-validation.json`; this is a focused run, not a new full-suite or PS2 runtime run.

| Entry | Native role | HD role |
|---|---|---|
| 0010E548 | dds3GetActiveScene | dds3WorldBasic.dds3GetActiveScene |
| 0010F208 | dds3SearchSceneBasic | dds3SceneBasic.dds3SearchSceneBasic |
| 001E3988 | evtGetUnitHandle | evtUnitManager.evtGetUnitHandle |
| 001E3BF0 | evtSetUnitKutiMotion | evtUnitManager.evtSetUnitKutiMotion |
| 001E3C00 | evtRunUnitKutiMotion | evtUnitManager.evtRunUnitKutiMotion |
| 001E3C30 | evtSetUnitExMotion | evtUnitManager.evtSetUnitExMotion |
| 001E52B0 | installed mouth-motion callback | evtCommand.KutiFunction |
| 001E52C8 | evtCommand_KUTISET | evtCommand.evtCommand_KUTISET |
| 001E5360 | evtCommand_KUTI | evtCommand.evtCommand_KUTI |

KUTISET and KUTI are original command IDs **357** and **351**, each consuming three VM arguments. They resolve the live unit, store its selected group/motion, publish the current unit at **54F754**, and install callback **001E52B0** into the message instance at **+1D0** when a message ID exists. KUTI also requests motion immediately. The callback reloads the current unit when it executes. Missing units return completion without changing the selection or installing the callback; a negative message ID still permits unit selection and immediate motion.

The Message path now executes the actual installed mouth callback. **192 generated text cases** independently confirm the installed function word and queued motion flag. **93 original-page cases**, covering one unchanged first page from each of **31 BMD files** through preparation, request and interpreter paths, independently preserve 5,373 page bytes and check relocated record pointers. The real scene search, VM getters, callback setter, parser, font construction, recycling and panel constructors execute. These are generated engine-state tests using the explicit cached-font setup described in `message-request-findings.md`, not gameplay or rendered-character observations.

The disassembly resolves an ambiguity hidden by the pseudocode: **001E3C00 uses signed LB**, not an unsigned byte load, for both stored group **CA** and motion **CB**. Negative groups can address preceding fields. The tests retain the native store order and overlap, including a case where the motion halfword overwrites the flag byte before its mode bit is ORed. Direct motion tests also preserve full raw64 mode comparisons: only exact 0, 1 or 2 add bits 4, 8 or 10. Values with matching low words and different upper words do not select those modes. Unity uses signed character fields too; managed bounds, animator hooks and object layouts remain differences.

Active-scene lookup follows native world basic **18/data8** pointers. Scene serial lookup uses a **12-byte count/head list per type**, object ID **+4**, and next pointer **+20**. The original compares the sign-extended live ID against the complete raw64 serial argument; generated dirty-upper-lane queries correctly fail. Event unit lookup selects type **5**, then follows basic **18/data8**. The native caller presumes a valid scene, list head and unit extent. Null active-world behavior is tested in its own accessor; invalid cycles, null caller chains and unbacked arrays are not assigned invented safe behavior.

Two complete DDS spans resolve: **0010F208 -> 00110A48** and **001E3988 -> 00222090**, with the unit lookup's scene-search call agreeing. The remaining seven routines have no complete match under the current address mask. Those related roles remain useful search leads; they are not promoted to DDS behavior equivalence. Shared offsets and command relationships are recorded in `shared-smt-signatures.tsv`.

The nine interfaces are saved in the working Ghidra project in place, reopened independently and merged into current exports. The previously unresolved mouth callback is recovered. The remaining panel draw graph is now recorded in `panel-draw-frontier.json`: nine callback roots, fifteen additional unrecovered dependencies, **24 bodies / 4,532 recognized bytes**, with four existing source-current boundaries. Unity draw names are structural leads there and remain unpromoted until each body is recovered and compared. Physical animation, GS rendering, scheduler integration, exhaustive assets, PS2 runtime and a matching executable remain outstanding.

Subsequent [panel drawing and packet recovery](panel-draw-findings.md) closes the nine callback graphs and original dispatcher with 25 complete routines and 3,360 passing comparisons. Frame submission, actual ordering-table callbacks and physical rendering remain separate work.

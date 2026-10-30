# smt3-decomp names to correct

Functions smt3-decomp (`config/smt3/symbol_addrs.txt` at 730da54) names as a
neighbour, where the HD remaster's method list
(`reference/hd/metadata/game-methods.tsv`) has both names and the code shows
which is which. `smt3-decomp-conflicts.tsv` (column `hd` = `both`) lists the
candidates; these are the ones checked. To offer upstream.

| address | smt3-decomp | should be | evidence |
|---|---|---|---|
| 0x10DE28 | dds3BackupPoseSet | dds3InitPoseSetValue | resets the pose to vf0; HD `InitPoseSetValue(pPoseSet)` |
| 0x10DE50 | dds3SetRadiusPoseSet | dds3BackupPoseSet | copies position, rotation, scale to +0x80..; HD `BackupPoseSet(pPoseSet)` |
| 0x10DE88 | dds3GetRadiusPoseSet | dds3SetRadiusPoseSet | stores f12 at the pose's +0xC4; HD `SetRadiusPoseSet(pBasic, float radius)` |
| 0x10DF38 | dds3GetPosPoseSet | dds3GetPosPoseSetMCR | one argument, result in vf10; HD `GetPosPoseSetMCR(_pBasic)` |
| 0x10DF88 | dds3GetPosPoseSetMCR | dds3AddPosPoseSet | adds a vector to the position; HD `AddPosPoseSet(pBasic, Vector4 pos)` |
| 0x10E010 | dds3GetSclPoseSetMCR | dds3AddSclPoseSet | multiplies the scale by a vector; HD `AddSclPoseSet(pBasic, Vector4 scl)` |
| 0x10E248 | dds3AllocObjectId | dds3SerializeID | no argument, returns the next ID; HD `SerializeID()` |
| 0x10FA68 | dds3AreaBasicGetItemArray | dds3AreaBasicReleaseItem | takes an item, finds the array of its type (0x10FAB8) and removes it; HD `ReleaseItem(pAreaBasic, pItemBasic)` |
| 0x10FAB8 | dds3AreaBasicReleaseItem | dds3AreaBasicGetItemArray | returns `area+0x18`'s array for a type; HD `GetItemArray(pAreaBasic, itemType)` |
| 0x2C3660 | sdfDevLoadFile | sdfDevLoadFileEx | takes the fourth argument (the margin); HD `LoadFileEx(..., aMergin)` |
| 0x2C3718 | sdfDevLoadFileEx | sdfDevLoadFile | passes a margin of 0 and jumps to 0x2C3660 |
| 0x20DDD8 | rcvAppAllRecover | rcvAppRecover | full HP and MP only, returns 1; HD `rcvAppRecover` returns SByte, `rcvAppAllRecover` void |
| 0x290908 | cmpClearButtonGuide | nbCheckCampSkillError | the menu skill's error check (tested: `nbCheckCampSkillError` in source/) |
| 0x1165B0 | dds3PathBasicControlNextStep | dds3PathBasicControlGetLight | takes a control and a resource (a1), returns nothing; HD `ControlGetLight(pControl, resource)`, `NextStep` returns uint |
| 0x25F228 | RunNumEffectKouka | RunRotKouka | nbKoukaProcess runs it for the rotation packets (kRot, kHomeRot) |
| 0x2C0BA8 | dds3GetRandA | sdfGetRand | the generator's state first, as sdfGetRandInt passes it |
| 0x2C0C00 | dds3GetRandFloatA | sdfGetRandFloat | likewise |
| 0x2C0C60 | dds3GetRandIntA | sdfGetRandInt | (state, limit): HD `sdfGetRandInt(aCB, aLimit)`; `dds3GetRandIntA` takes the limit first |

## Ours to correct

| address | ours (the map's) | should be | evidence |
|---|---|---|---|
| 0x173D78 | effBTLPartDelete | effBTLSystemDelete2 | deletes a system effect through its family's table (0x31BF00) and frees the handle; HD `effBTLSystemDelete2(hEffBTLSys)`, while `effBTLPartDelete` takes a skill |
| 0x279C58 | nbPanelAutoHide | nbPanelAllHide | calls three hides (0x281E28, 0x282268, 0x27C338), as nbPanelAllShow just before it calls the three shows |
| 0x281E28 | ps2BattlePanelHideHookA | nbPanelAutoHide | one of nbPanelAllHide's three |
| 0x114038 | dds3LightObjectBasicGetControlWorkData | dds3EffectObjectBasicGetControlWorkData | between the effect object's draw procedure and dds3AddEffectObjectBasic (neighbours) |
| 0x115A70 | dds3EffectObjectBasicGetControlWorkData | dds3LightObjectBasicGetControlWorkData | between the light destructor and dds3AddLightObjectBasic (neighbours) |
| 0x116AD0 | dds3AddPathBasic | dds3AddPointBasic | after the last path function, before dds3PointBasicGetResource (neighbours; tentative) |

Every "both" row is settled: 18 of smt3-decomp's names and 6 of ours sat
one function off. Ours are renamed in Ghidra (with 0x185D88 and 0x188DA0, the
scatter and whirlwind polygon lists' deletes, swapped in our map too).

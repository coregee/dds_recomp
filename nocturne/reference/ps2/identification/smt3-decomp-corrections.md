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

The other "both" rows (the light and effect objects' control work, the path
basics, the RNG's sdf and dds3 names, effBTLPartDelete, RunRotKouka,
nbPanelAutoHide) are not checked yet.

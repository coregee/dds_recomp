# Native camera path commands and spline construction

Recovered **27 complete native routines**, spanning **3,300 recognized bytes**. All **1,984 original-instruction/C comparisons pass**, including 1,888 cases on new bodies and 96 interpreter programs split across MOVE, FOVY and WAIT. Every one of **671 main instruction addresses** is reached; the original engine executes 1,116,978 steps and 408 interpreter indirect calls. The affected C builds with warnings treated as errors. All 27 interfaces were saved in the working Ghidra project, reopened and checked; 27 current exports merged without failures.

The full executable objective remains active. This batch raises integrated recovery to **1,173 / 8,975 functions (13.070%)** and **622,522 aggregated comparisons**. The earlier full run remains 413 functions / 462,684 cases; this is a focused comparison, not a new full-suite result.

## Commands and native behavior

| Command | Native entry | Parameters | Behavior |
|---|---|---:|---|
| 19 CAM_PATH_MOVE | 001E77D8 | 2 | Negative camera ID selects the follow camera; otherwise type4 scene search. Type16 search finds the path. Link and construct its owned path control, or print the original diagnostic; return1. |
| 25 CAM_SEL_FOVY | 001E7750 | 1 | Select follow/named camera. The named-camera branch sets camera data+88 bit1 before testing the camera pointer. This is a retained unchecked access; HD adds a missing-camera guard. |
| 85 CAM_PATH_WAIT | 001E7878 | 1 | Check mover/path control. Return1 for status -1 or0; return0 for status1. Mode0 completes at ratio1, mode1 at ratio0; other modes report -1. |

VM parameters are read from the top of the native value stack: MOVE parameter0 is the top slot and parameter1 is the preceding slot. The command descriptors and jump tables are the original executable bytes.

## Native layouts and algorithms

The type4..9 control dispatcher reads basic+0F and the original six-entry jump table at530D20. Basic+18 points to object data; camera/unit/matter/light/event/effect control offsets are80/C/0/0/0/74 in hex. Control+14 contains the mover, whose data+4 owns the path control and data+C stores the path object.

The 36-byte path control holds mode0, flags4, maximum frame8, progressC, spline10, and channels14/18/1C/20. Kinds0/2/4/5 set flags1/2/4/10 in hex. The last frame key is unsigned; native conversion handles bit31 using shift/or, CVT.S.W and doubling. The constructor reloads the resource channel count after allocation and after recognized channel writes. A backed allocation/header alias exercises the zero reload. Replacing a mover path executes actual spline release, handle coalescing and pool release.

The 44-byte spline record owns handles at0/4, count8, small-curve halfwordC, points10 and coefficient arrays14/18/1C. Fields20/24 start zero; field28 loads raw constant3D4CCCCC from54CA78. The count<3 branch compares the full64 argument while sizes and stored count use its low32 word. A dirty high lane with low count2 is included. Small curves leave unrelated words untouched.

Differentials execute three axes and the native tridiagonal forward elimination/back substitution. Cubic coefficient A groups `(2*(point0-point1)) + (leftDerivative+rightDerivative)` using separate EE operations; HD grouping differs. The flat-segment variant zeros all three coefficients after native equality. The original scalar operand order is preserved for every selected arithmetic site.

## Evidence and transfer

The comparisons execute the recovered pool allocator, memory-handle split/coalescing, memset, scene/list search, parameter reads, bounded diagnostic formatter and interpreter dependencies. Full declared RAM, defined raw returns, Status, CPU primitive counts, callee saves and ordered VM targets agree. A float-facing ratio function is called through a bit-preserving host adapter; it adds no native function identity. The COP1 adapter is scoped to 47 body-hashed instruction sites.

There are **25 reviewed Unity semantic counterparts**. Native path-control and spline release remain descriptive aliases: Unity FreeControl resolves to an empty managed body, and no nonempty spline-release body is retained. Managed arrays, pointer widths, checks, garbage collection and arithmetic grouping are not imported into the PS2 C.

All **27 selected full function spans resolve in DDS**, with **43 agreeing callee constraints**. Tiny leaves are constrained by their dispatch/caller context. Six control jump-table targets have equal relative offsets. The spline constructor differs only in explicit call addresses and one GP-relative constant load: ELF .reginfo establishes Nocturne GP554170 and DDS GP3C0CF0; constant bytes at54CA78/3B93A0 agree. The MOVE error branches each construct the same relocated format address,53AD58/3AC8D0, and diagnostic bytes agree. These are static DDS comparisons, not DDS execution.

## Current source and outputs

- `src/path_control.c` and `src/path_control.h` contain the complete recovered bodies.
- `analysis/path-control-validation.json` records current comparisons and source hashes.
- `analysis/path-control-interfaces.json` and `analysis/path-control-abi.json` record the saved native interfaces.
- `analysis/path-control-matches.json` and `analysis/path-control-transfer.json` record HD and DDS evidence.
- `tooling/recover_path_control.py` maintains the rolling fixtures/results and publishes current ledgers.

No checkpoint, project copy, frozen source tree or duplicate capture was created. Failed captures were replaced at the same rolling path.

## Remaining work

Path interpolation, mode/ratio mutation, progression, pause/loop flags and camera updates are the next connected native graph. `analysis/path-control-next-frontier.json` records unpromoted leads. Physical camera movement, FCSR cause flags/timing, kernel scheduling, malformed/unbacked graphs, all production paths and a matching PS2 executable remain unproved.

## Recovered entries

| PS2 entry | Function | Body bytes | DDS entry |
|---|---|---:|---|
| 001125C8 | dds3CameraObjectBasicGetControlWorkData | 12 | 00112BB0 |
| 00112A30 | dds3UnitObjectBasicGetControlWorkData | 12 | 00113008 |
| 00113300 | dds3MatterObjectBasicGetControlWorkData | 12 | 00113CD8 |
| 00114038 | dds3LightObjectBasicGetControlWorkData | 12 | 00114A68 |
| 00115728 | dds3EventObjectBasicGetControlWorkData | 12 | 00116250 |
| 00115A70 | dds3EffectObjectBasicGetControlWorkData | 12 | 00116598 |
| 001122A0 | dds3GetBaseControlWorkData | 160 | 00112888 |
| 00110300 | dds3ObjectBaseGetControlBasic | 48 | 00111AD0 |
| 0010FEE0 | dds3MoverBasicSetPath | 12 | 001116A8 |
| 0010FEF0 | dds3MoverBasicMakePath | 64 | 001116B8 |
| 0010FF68 | dds3MoverBasicGetPathControl | 12 | 00111730 |
| 00116A48 | dds3PathBasicPathControlGetMode | 8 | 00117570 |
| 00116A60 | dds3PathBasicControlGetRatio | 28 | 00117588 |
| 00116210 | dds3PathBasicMakeControl | 440 | 00116D38 |
| 001163E0 | dds3PathBasicFreeControl | 44 | 00116F08 |
| 001B0858 | effSplInitialize2 | 280 | 00192CC8 |
| 001B0970 | ps2SplineRelease | 76 | 00192DE0 |
| 001B0CD8 | effSplineMakeCoefficientTable | 152 | 00193148 |
| 001B0D70 | effSplineMakeDifferential | 388 | 001931E0 |
| 001B0EF8 | effSplineSolveTridiagonal | 380 | 00193368 |
| 001B1078 | effSplineMakeCoefficient | 208 | 001934E8 |
| 001B1148 | effSplineMakeCoefficient2 | 236 | 001935B8 |
| 001E1C78 | evtPathLinkAndMake | 108 | 00220340 |
| 001E1CE8 | evtCheckPathStat | 164 | 002203B0 |
| 001E7750 | evtCommand_CAM_SEL_FOVY | 132 | 00226E10 |
| 001E77D8 | evtCommand_CAM_PATH_MOVE | 156 | 00226E98 |
| 001E7878 | evtCommand_CAM_PATH_WAIT | 132 | 00226F38 |

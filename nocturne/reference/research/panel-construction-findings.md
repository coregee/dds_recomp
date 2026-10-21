# Panel initialization and Message window opening

Nineteen complete routines in `src/panel_construction.c` compile and pass **2,016 original-instruction comparisons**, reaching all **557 main instruction addresses** across **2,500 recognized body bytes**. The cases execute 229,197 original instructions. Current integrated recovery is **1,019 / 8,974 recognized functions (11.355%)**, with 599,997 aggregated comparisons and 154,080 summed validated body bytes. These are focused additions; the last full run remains 413 functions / 462,684 cases.

The original geometry and color tables exposed three incomplete function entries and an omitted callback. Ghidra now starts the geometry routines at `001CC358`, `001CC3D0` and `001CC540`, replacing entries twelve, sixteen and sixteen bytes too late. The fixed-color callback at `001CC968` is newly recognized. All four boundaries were saved in place and independently exported; the recognized inventory grows by one. The old interior entries were retired from the rolling index.

The recovered functions include allocation at `001CC080`, position dispatch at `001CC1A0`, color dispatch at `001CC270`, all thirteen unique non-null initialization callbacks, the integer color scaler at `001CAF78`, and Message/speaker window opening at `001CFA90` / `001CFB68`. The setters read the live original callback pointers and execute recovered bodies; allocation executes the existing native memory-handle and pool routines. No game-return substitutes are used.

| Type | Geometry callback | Color callback | Payload bytes |
|---:|---|---|---:|
| 0 | 001CC358 | 001CC7A0 | 96 |
| 1 | 001CC3D0 | 001CC7D0 | 448 |
| 2 | 001CC540 | 001CC830 | 352 |
| 3 | 001CC688 | 001CC890 | 96 |
| 4 | 001CC688 | 001CC920 | 48 |
| 5 | 001CC6B8 | 001CC938 | 80 |
| 6 | none | none | 4 |
| 7 | none | none | 4 |
| 8 | 001CC728 | 001CC968 | 100 |

The tables reside at `00326428`, `00326450` and `003264E0`. A panel record occupies 52 bytes: its owner handle at +0, payload handle at +4, payload pointer at +8, depth at +C, four position words at +10 through +1C, four color words at +20 through +2C and type byte at +30. Allocation indexes the size table using the raw low-word type but initializes an external texture only when the full 64-bit type equals six, seven or eight. The setters dispatch using the stored byte. High argument lanes exercise this distinction.

Geometry preserves signed wrapped integer arithmetic, normal-window midpoint collapse, message-window live offset-table reads, selection/facility border construction and type-eight fixed X coordinates. Color scaling multiplies low words with native wrap, clamps only above signed `00FF0000`, then performs an arithmetic shift by sixteen. It retains negative results and live ratio reads when output overlaps the ratio table. The PS2 type-eight callback ignores incoming colors and writes fixed 115/135/255/0 values; its HD counterpart accepts supplied colors.

Message opening reuses an existing panel or creates type six; message type two creates type eight. It publishes geometry and color, then changes the phase to `100`. Speaker opening uses the measured font width and type seven, retaining the original ownership checks and `1000` / `3000` phase transitions. Cases include all nine panel types, creation/reuse, raw argument lanes, wrapped coordinates/colors, aliased payload/header records, overlapping ratio outputs and a finite allocator extent with sufficient capacity. Exhaustion is outside this comparison.

Fourteen Unity counterparts are reviewed, covering five geometry roles, six color roles and allocation/position/color dispatch. Managed array layouts, guards, some arithmetic and the type-eight color behavior differ. Five functions retain descriptive PS2 aliases. Ten complete bodies resolve in DDS: five geometry callbacks, four color callbacks and the scaler. Other bodies have no full-span match and remain unresolved for transfer; name similarity alone is not promoted.

All nineteen interfaces were saved, reopened and exported. The remaining Message direct graph now contains **four bodies / 1,020 recognized bytes**: command `001CD2E0`, request `001CDB80`, message setup `001CF1D8` and parameter publication `001CF778`. These are the next connected recovery work.

The separate draw table at `00326478` has nine non-null callbacks that are not recovered by this batch. Initialization comparisons do not establish drawing, physical GS output, kernel scheduling, full gameplay, PS2 runtime or a matching executable. Original BMD text still needs connected parser/Message execution.

Evidence: `panel-entry-repair.json`, `panel-construction-validation.json`, `panel-construction-interfaces.json`, `panel-construction-abi.json`, `panel-construction-matches.json`, `panel-construction-transfer.json` and `message-command-frontier.json`. Current exports and reports were updated in place; no checkpoint or backup copy was created.

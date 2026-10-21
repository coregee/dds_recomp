# Exact scene-name lookup and SEARCH_ID

Five complete PS2 functions now have compiled source, original-instruction comparisons, reviewed Unity roles and saved working-project interfaces:

| PS2 entry | Recovered role | DDS counterpart |
|---|---|---|
| 0010E588 | `dds3GetControlScene` | 0010FDC0 |
| 0010F6E0 | Exact name search within one type | 00110ED0 |
| 0010F790 | `dds3SceneBasicSearchName` | 00110F80 |
| 001E6D68 | `evtCommand_SEARCH_ID`, command slot 148 | 002265B8 |
| 001589F0 | `fldCommand_SEARCH_ID` | 0014DB20 |

The current-world pointer is at `0054E9C4`. A nonnull world loads its data pointer at +0x18 and the control scene at data+0x0C; a null world returns zero. Inner pointers are unchecked. The scene's data pointer at +0x18 contains a typed-list table at +8. There are 18 type slots, each a 12-byte record with its list head at +4. Objects carry an ID word at +4, a name pointer at +8, and their next link at +0x20.

The native search skips null and empty object names, compares raw bytes for **exact equality**, and returns the first matching object. All-type search visits types 0..17 in order. It has no partial-match fallback. The named HD exact helper is `dds3SceneBasicSearchNameAndType_1`; HD all-type search adds a second pass through `_2` for substring matching. Managed layouts and exception paths are reference differences, not native behavior to import.

Event command 148 reads string parameter zero and publishes the matched object's signed ID word through `scrSetIntReturnValue`. On failure it reloads the parameter for real printf with `ID : id not found!! <%s>\n`, reloads it again for the original disabled diagnostic, and publishes zero. Its command result is always one; the descriptor pops one argument. The field wrapper takes a direct raw string pointer, returns the matched signed ID directly, and on failure prints `field SEARCH_ID NotFound:[%s]\n` before returning signed -1. The HD field wrapper omits that native print and receives a managed-name reference.

**1,431 original-instruction/C comparisons pass**: 128 for each of the three helpers, 349 for each lookup wrapper, and 349 event-command/End interpreter programs. All **96 non-delay root instruction addresses** are reached. The capture executes 547,401 native steps and 1,047 actual indirect calls. It compares full declared RAM, defined raw 64-bit results, Status, callee saves and ordered VM calls. The actual name walker, script parameter/return accessors, printf/formatter/vector writer and memory helpers execute without game/library return replacements.

Static extraction identifies **221 distinct selected names** immediately pushed before command 148 in shipped BF files. Every selected original name is tested through both lookup wrappers and through the interpreter. The original asset hash, string-table offset and command PC remain attached to its fixture. These inputs establish name-byte provenance; synthetic bounded scene lists supply the objects. They do not establish gameplay object creation or the actual scene associated with a particular script.

Cases also cover all 18 type slots, null/empty names, prefix mismatches, skipped unnamed objects, duplicate names with an earlier type winning, raw high argument lanes, signed ID boundaries and 120 failure diagnostics. The diagnostics use a buffer-backed stdout FILE and the real native formatting path; physical console output is outside this experiment. Cyclic lists, invalid pointers/type indexes and full gameplay/runtime behavior remain unproved.

All five DDS bodies resolve with complete contiguous-word checks. Explicit call targets, literal addresses and decoded GP displacements are relocated; other original instructions agree. Twelve event/field/typed-search callee links and three byte-identical diagnostic literals corroborate the transfer. The disabled diagnostic's caller-anchored DDS target has a different private argument-save body; it is explicitly recorded as related but **not a complete-body match**. Static transfer is not DDS execution proof.

Production source is `src/scene_lookup.c`. Evidence is in `scene-lookup-validation.json`, `scene-lookup-matches.json`, `scene-lookup-transfer.json`, `scene-lookup-abi.json` and `scene-lookup-shipped-names.json`. `tooling/recover_scene_lookup.py` reproduces the preparation and comparison; the original capture uses `ProbeScriptCore.java`. Interfaces and exports were saved in place, independently reopened and verified. No checkpoint or backup was created.

# Reference material

Evidence used to name and understand the code. Nothing here is built.

| Path | Contents | Tracked |
|---|---|---|
| `function-map.tsv` | Every function: address, size, Ghidra name, state (rewritten / legacy / named / unknown), rewrite and legacy locations. Regenerate with `tools/ghidra/export-annotations.ps1`. | yes |
| `ps2/ghidra-annotations.tsv` | Text export of all user names, signatures, variables and comments in the Ghidra program. The backup of the Ghidra work. | yes |
| `ps2/identification/` | How functions were identified: HD-remaster matches (`function-matches.tsv`, `calculation-matches.tsv`), PS2-only and library identifications, shared SMT signatures, rejected matches, and `hd-name-leads-unverified.tsv` (proposed HD names recovered from old reports; some are misaligned, check before use). `ghidra-annotations.tsv` there is an older export. | yes |
| `ps2/layouts/` | Structure layout notes from the legacy work. | yes |
| `ps2/strings.tsv` | Strings in the executable. | yes |
| `ps2/functions-initial-export.tsv` | The first Ghidra function export (before naming). | yes |
| `ps2/hd-corpus-matches/` | Candidate PS2↔HD function matches (`candidates.json`, 32 MB, is local only). | partly |
| `ps2/whole-program/` | Per-function disassembly, decompilation and metadata for all functions (`functions/<addr>.asm/.c/.json`, `index.jsonl`). Regenerate with `tools/ghidra/export-executable.ps1`. | no (30 MB) |
| `hd/il2cpp/` | Il2CppDumper output for the HD remaster: `dump.cs` (all classes and fields), `il2cpp.h`, `script.json`, `stringliteral.json`. | no |
| `hd/metadata/` | Tables of HD types, fields and methods (`game-methods.tsv` has original function signatures). | no |
| `hd/ghidra/` | HD `GameAssembly.dll` decompiles (`corpus/<va>.c`), method list. | no |
| `hd/input/` | The HD `GameAssembly.dll` these come from. | no |
| `research/` | Archived findings from the legacy work (one file per subsystem) and `community-research.md`, the inventory of community sources (randomizers, format docs, mods). Verbose, but the facts are useful. | yes |
| `fixtures/saves/` | A PCSX2 save used for live checks. | yes |
| `manuals/` | EE core manuals (Sony). | no |

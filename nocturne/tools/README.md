# Tools

| Tool | Use |
|---|---|
| `disc_extract.py` | Extract the ISO in `nocturne/` to `game/`, checking `disc-sha256.json`. `--variant <name>`: another version's disc to `game/<name>/`. `--overwrite` to replace. |
| `sources.py` | `sources.py <version> sources|includes`: a version's source files (shared, then US Maniax's replaced by the version's own) and include path; used by the build scripts. |
| `variant.cmd` | Read `NOCTURNE_VARIANT` and set the build's defines, includes, executable and folder suffix. |
| `ghidra/ExportVariantDiff.java` | List the functions another version's executable changes against US Maniax's, and its new code. |
| `dds3_archive.py` | `list` / `extract PATH...` / `all [--filter X]` for the `DDS3.DDT`/`DDS3.IMG` archive, into `game/dds3/`. |
| `function_map.py` | Build `reference/function-map.tsv` (called by `ghidra/export-annotations.ps1`). |
| `gen_tables.py` | Generate `source/maniax/src/data/*_table.cpp` and `source/shared/include/nocturne/data/ids.hpp` (`--variant <name>`: that version's differing tables in `source/<name>/`) from the executable. |
| `ghidra/import-types.ps1` | Headless: import `nocturne_types.h` into the program, type the data tables, apply `nocturne_signatures.tsv`. Add a line there for every rewritten function. |
| `ghidra/export-annotations.ps1` | Headless, read-only: export Ghidra annotations to `reference/ps2/ghidra-annotations.tsv` and refresh the function map. Close the GUI first. |
| `ghidra/export-executable.ps1` | Headless export of every function's asm/decompile/metadata to `reference/ps2/whole-program/`. Uses the patched EE language unless `-OriginalProcessor`. |
| `ghidra/prepare-ee-divu-fix.ps1` | Build the patched EE processor (unsigned `DIVU`) into `build/ee-divu-fixed/`. See `docs/ghidra.md`. |
| `ghidra/export-hd-corpus.ps1`, `ImportIL2CppSymbols.java` | Re-create the HD remaster reference: import `GameAssembly.dll` into a Ghidra project, apply il2cpp symbols, export decompiles. |
| `il2cpp-dump/` | .NET program that produced the `reference/hd/metadata` tables. |
| `pcsx2_controls.mjs`, `configure_pcsx2_runtime.py` | Drive and configure the PCSX2 MCP build for live checks. |
